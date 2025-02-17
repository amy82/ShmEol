#include "StdAfx.h"
#include "LensProcess.h"


CLensProcess::CLensProcess(void)
{
	m_bFlagSocketReq = false;
	LensIoRetryCount = 0;
}


CLensProcess::~CLensProcess(void)
{
}

//-----------------------------------------------------------------------------
//
//	LENS BUFFER에 LENS 공급 요청 동작
//
//-----------------------------------------------------------------------------
int CLensProcess::AutoLensReq(int nStep)
{
	TCHAR szLog[SIZE_OF_1K];
	CString sMsg = _T("");
	int nRetStep;
	bool bRtn = false;
	nRetStep = nStep;

	switch(nStep)
	{
	case 100000:
		//if (g_clTaskWork[m_nUnit].m_bLensInterLock == true)	//TRNASFER가 LENS 공급중
		//{
		//	break;
		//}
		
		//AA중에도 렌즈 공급 요청을 해야돼서 렌즈 위치를 따로 체크하지 않는다.		211008
		//g_ShowMsgModal(_T("확인"), _T("[AUTO]LENS 공급요청 진행하시겠습니까?"), RGB_COLOR_RED);
		nRetStep = 100200;
		break;
	case 100200:
		//렌즈 그립 체크
		if (g_clTaskWork[m_nUnit].m_bWaitLensBonding == false)
		{
			if (g_clDioControl.LensGripCheck(m_nUnit, true) == true)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS GRIP 확인 [STEP : %d]"), nStep);
				AddLog(szLog, 0, m_nUnit);

				if (g_ShowMsgModal(_T("확인"), _T("[AUTO] LENS GRIP 상태입니다. 진행하시겠습니까?"), RGB_COLOR_RED) == true)
				{
					_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] LENS GRIP 상태 진행 [STEP : %d]"), nStep);
					AddLog(szLog, 0, m_nUnit);
					nRetStep = 211500;	//JUMP
					break;
				}
				else
				{
					_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] LENS GRIP 상태 진행 실패 [STEP : %d]"), nStep);
					AddLog(szLog, 1, m_nUnit, true);
					nRetStep = -100200;
					break;
				}

			}
		}
		LensIoRetryCount = 0;
		nRetStep = 100500;
		break;
	case 100500:
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] BUFFER VACUUM ON 동작 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		if (g_clDioControl.LensBufferVacuumOn(m_nUnit, true) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] BUFFER VACUUM ON 동작 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -101000;
			break;
		}
		LensIoRetryCount++;
		nRetStep = 101000;
		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		break;
	case 101000:
		if (g_clDioControl.LensBufferSensorCheck(m_nUnit, true) == true)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] BUFFER LENS 센서 확인 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			if (g_clDioControl.LensBufferVacuumOnCheck(m_nUnit, true) == true)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] BUFFER LENS 흡착 확인 완료 [STEP : %d]"), nStep);
				AddLog(szLog, 0, m_nUnit);

				sMsg.Format(_T("#AA%d@LENS&ESC$"), (m_nUnit + g_clSysData.m_nUnitNo + g_clSysData.m_nSysNo + 1));
				bRtn = g_pCarAABonderDlg->SendDataToAAMain(m_nUnit, sMsg);
				if (bRtn == false)
				{
					_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] LENS 공급 취소 요청 실패 [STEP : %d]"), nStep);
					AddLog(szLog, 1, m_nUnit, true);
					nRetStep = -101000;
					break;

				}
				nRetStep = 190000;
				break; 
			}
			else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_WAIT_TIME)
			{
				if (LensIoRetryCount < 5)
				{
					nRetStep = 100500;
					break;
				}
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] BUFFER LENS 흡착 확인 실패 [STEP : %d]"), nStep);
				AddLog(szLog, 1, m_nUnit, true);

				nRetStep = -100500;
				break;
			}
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_WAIT_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] BUFFER LENS 미확인 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 101500;
			break;
		}
		break;	
	case 101500:

		nRetStep = 102000;
		break;
	case 102000:
		g_clTaskWork[m_nUnit].m_bLensInterLock = true;	//공급완료 변수 초기화

		nRetStep = 102500;
		break;
	// LENS 공급 요청
	case 102500:
		//sMsg.Format(_T("#AA%d@LENS&REQ$"), (g_clSysData.m_nUnitNo * 2) + m_nUnit + 1);

		sMsg.Format(_T("#AA%d@LENS&REQ$"), (m_nUnit + g_clSysData.m_nUnitNo + g_clSysData.m_nSysNo + 1));
		bRtn = g_pCarAABonderDlg->SendDataToAAMain(m_nUnit, sMsg);
		if (bRtn == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] LENS 공급 요청 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -102500;
			break;

		}
		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 103000;
		break;
	// LENS 공급 요청 응답 체크
	case 103000:
		if(g_clTaskWork[m_nUnit].m_bLensInterLock == false)
		{
			sMsg.Format(_T("#AA%d@LEN&ACK$"), (m_nUnit + g_clSysData.m_nUnitNo + g_clSysData.m_nSysNo + 1));
			g_pCarAABonderDlg->SendDataToAAMain(m_nUnit, sMsg);

			nRetStep = 103500;
			break;
		}

		if((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > 2000)
		{
			nRetStep = 102500;
			break;
		}
		break;
	// LENS STAGE 제품 확인
	case 103500:
		
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] BUFFER VACUUM ON 동작 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		if (g_clDioControl.LensBufferVacuumOn(m_nUnit, true) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] BUFFER VACUUM ON 동작 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -103500;
			break;
		}
		nRetStep = 104000;
		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		break;

	case 104000:
		if (g_clDioControl.LensBufferVacuumOnCheck(m_nUnit, true) == true)
		{
			g_clTaskWork[m_nUnit].m_bLensBufferLensOn = true;

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] BUFFER LENS 확인 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 104500; 
			break;
		}
		if (g_clDioControl.LensBufferSensorCheck(m_nUnit, true) == true)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] BUFFER LENS 센서 확인 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 104500;
			break;
		}
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_WAIT_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] BUFFER LENS 공급 후 LENS 감지 이상 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -103500;
			break;
		}
		break;
	case 104500:
		
		nRetStep = 190000;
		break;

	case 190000:
		
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] BUFFER LENS 공급 완료. [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		nRetStep = 200000;
		break;
	default:
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] LENS 공급 요청 동작 중 이상 STEP 발생 [STEP : %d]"), nStep);
		AddLog(szLog, 1, m_nUnit, true);

		nRetStep = -1;
		break;
	}

	return nRetStep;
}


//-----------------------------------------------------------------------------
//
//	LENS PICKUP 동작
//
//-----------------------------------------------------------------------------
int CLensProcess::AutoLensLoading(int nStep)
{
	
	return 0;
}
