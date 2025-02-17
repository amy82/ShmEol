#include "StdAfx.h"
#include "LensAxisThread.h"
#include "AutoInspDlg.h"
#include "GlobalDeclare.h"

CLensAxisThread::CLensAxisThread(void)
{
	m_nUnit = -1;
	LensMode = 0;
	bLensWorkRun = false;

	m_nLensStartStep = 0;
	m_nLensEndStep = 0;
	m_nLensCurrentStep = 0;
}


CLensAxisThread::~CLensAxisThread(void)
{
}


//-----------------------------------------------------------------------------
//
//	스레드 생성자
//
//-----------------------------------------------------------------------------
void CLensAxisThread::ThreadConstructor()
{

}

//-----------------------------------------------------------------------------
//
//	스레드 소멸자
//
//-----------------------------------------------------------------------------
void CLensAxisThread::ThreadDestructor()
{
	
}
void CLensAxisThread::LensThreadrun(int Mode)
{
	switch (Mode)
	{
	case LENS_LASER_THREAD:
		bLensWorkRun = true;
		g_clTaskWork[m_nUnit].m_nCurrentLensStep = m_nLensStartStep = 10000;

		m_nLensEndStep = 100000;

		StartThread();
		break;
	default:
		g_clTaskWork[m_nUnit].m_nCurrentLensStep = 0;
		m_nLensStartStep = 0;
		m_nLensEndStep = 0;
		break;
	}
}
//-----------------------------------------------------------------------------
//
//	스레드 콜백
//
//-----------------------------------------------------------------------------
void CLensAxisThread::ThreadCallBack()
{
	if (bLensWorkRun == false) return;
	//
	if ((g_clTaskWork[m_nUnit].m_nCurrentLensStep >= m_nLensStartStep) && (g_clTaskWork[m_nUnit].m_nCurrentLensStep < m_nLensEndStep))
	{
		if (g_clTaskWork[m_nUnit].m_nCurrentLensStep >= 10000 && g_clTaskWork[m_nUnit].m_nCurrentLensStep < 100000)
		{
			g_clTaskWork[m_nUnit].m_nCurrentLensStep = this->Lens_Laser_Run(g_clTaskWork[m_nUnit].m_nCurrentLensStep);
		}
		else
		{
			bLensWorkRun = false;
			this->EndThread();
		}
	}

	else if (g_clTaskWork[m_nUnit].m_nCurrentLensStep == -1)
	{
		bLensWorkRun = false;
		this->EndThread();
	}
	else if (g_clTaskWork[m_nUnit].m_nCurrentLensStep < 0)
	{
		g_pCarAABonderDlg->PauseAutoProcess(m_nUnit);
	}
	else
	{
		bLensWorkRun = false;
		this->EndThread();
	}
}

int CLensAxisThread::Lens_Laser_Run(int nStep)
{
	TCHAR szLog[SIZE_OF_1K];
	int nHomeFlag = 0;
	int nRetStep = 0;
	int i = 0;
	double dPos[4] = { 0.0, 0.0, 0.0, 0.0 };
	double curPos = 0.0;
	double dLaserTx = 0.0;
	double dLaserTy = 0.0;
	int nRetVal = 0;
#if 0
	nRetStep = nStep;
	//Lens Align -> Lens Laser -> Lens Align
	switch (nStep)
	{
	case 10000:
		g_clTaskWork[m_nUnit].m_bLensLaserCompleteCheck = false;
		OCControl[m_nUnit].Send_12CHChannel_Value(LIGHT_BD_ALIGN_CH1, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_ALIGN_LENS]);
		nRetStep = 10500;
		break;
	case 10500:
		//Lens Align Start
		if (g_clMotorSet.MoveLensZMotor(m_nUnit, WAIT_POS, 0.0, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 WAIT_POS 위치 이동 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -41000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 WAIT_POS 위치 이동 완료 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 11000;
		break;
	case 11000:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_LENS_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 WAIT_POS 위치 이동 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 11500;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 WAIT_POS 위치 이동 시간 초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -10500;
			break;
		}
		
		break;


	// LENS 넘김 상태로 인해 , 대기위치 에서 올수도 있으니, 동시이동 x
	// LENS X축 대기위치 이동 후 Y축 ALIGN 위치.
	case 11500:
		if (g_clMotorSet.MoveLensXMotor(m_nUnit, WAIT_POS, 0.0, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X WAIT_POS 이동 명령 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -11500;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X WAIT_POS 이동 명령 성공 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 11600;
		break;

	case 11600:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_LENS_X];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_X) && (g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_X) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X축 대기위치 이동 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 11700;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X축 대기위치 이동 시간초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -11500;
			break;
		}
		break;

	case 11700:
		if (g_clMotorSet.MoveLensYMotor(m_nUnit, LENS_ALIGN_POS, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Y LENS ALIGN 위치 이동 명령 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -11700;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Y LENS ALIGN 이동 명령 성공 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 11800;
		break;


	case 11800:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[LENS_ALIGN_POS].dPos[MOTOR_LENS_Y];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_Y) && (g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Y) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Y축 LENS ALIGN 위치 이동 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 11900;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Y축 LENS ALIGN 위치 이동 시간초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -11700;
			break;
		}
		break;

	case 11900:
		if (g_clMotorSet.MoveLensXYMotor(m_nUnit, LENS_ALIGN_POS, 0.0, 0.0, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X,Y축 LENS ALIGN 위치 이동 명령 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -11900;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X,Y축 LENS ALIGN 위치 이동 명령 성공 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 12000;
		break;


	case 12000:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[LENS_ALIGN_POS].dPos[MOTOR_LENS_X];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[LENS_ALIGN_POS].dPos[MOTOR_LENS_Y];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_X) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_X) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_Y) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Y) - dPos[1]) < ENCORDER_GAP)))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X,Y축 LENS ALIGN 위치 이동 완료 [STEP : %d"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 12500;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X,Y축 LENS ALIGN 위치 이동 시간 초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -11500;
			break;
		}
		
		break;
	case 12500:
		if (g_clMotorSet.MoveLensTxTyMotor(m_nUnit, LENS_ALIGN_POS, 0.0, 0.0, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS TX,TY축 LENS ALIGN 이동 명령 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -12500;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS TX,TY축 LENS ALIGN 이동 명령 성공 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 13000;
		break;
	case 13000:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[LENS_ALIGN_POS].dPos[MOTOR_LENS_TX];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[LENS_ALIGN_POS].dPos[MOTOR_LENS_TY];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_TX) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_TX) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_TY) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_TY) - dPos[1]) < ENCORDER_GAP)))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS TX,TY축 LENS ALIGN 위치 이동 완료 [STEP : %d"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 13500;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS TX,TY축 LENS ALIGN 위치 이동 시간 초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -12500;
			break;
		}
		break;
	case 13500:
		if (g_clMotorSet.MoveLensZMotor(m_nUnit, LENS_ALIGN_POS, 0.0, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 LENS ALIGN 위치 이동 명령 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -13500;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 LENS ALIGN 위치 이동 명령 성공 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 14000;
		break;
	case 14000:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[LENS_ALIGN_POS].dPos[MOTOR_LENS_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 LENS ALIGN 위치 이동 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 14500;
			g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 LENS ALIGN 위치 이동 시간 초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -13500;
			break;
		}
		break;
	case 14500:
		g_clVision.ClearOverlay(m_nUnit, VIDEO_CAM);
		g_clVision.DrawOverlayAll(m_nUnit, VIDEO_CAM);
		
		g_clTaskWork[m_nUnit].m_nRetryCount = 0;

		g_clTaskWork[m_nUnit].m_dAADataX = 0.0;
		g_clTaskWork[m_nUnit].m_dAADataY = 0.0;
		g_clTaskWork[m_nUnit].m_dAADataTh = 0.0;

		g_clTaskWork[m_nUnit].m_dAlignData.x = 0.0;
		g_clTaskWork[m_nUnit].m_dAlignData.y = 0.0;
		g_clTaskWork[m_nUnit].m_dAlignData.t = 0.0;

		g_clTaskWork[m_nUnit].dpFind.x = 0.0;
		g_clTaskWork[m_nUnit].dpFind.y = 0.0;


		g_clTaskWork[m_nUnit].m_dLensAlign[0] = 0.0;
		g_clTaskWork[m_nUnit].m_dLensAlign[1] = 0.0;
		g_clTaskWork[m_nUnit].m_dLensAlign[2] = 0.0;

		nRetStep = 15000;
		break;
	case 15000:
		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 15500;
		break;
	case 15500:
		//! ALIGN전 Delay
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > (DWORD)g_clModelData[m_nUnit].m_dSensorAlignDelay * 1000)
		{
			nRetStep = 16000;
		}
		break;
	case 16000:
		
		g_clVision.CalcSingleMarkAlign(m_nUnit, LENS_ALIGN_MARK, 0, g_clTaskWork[m_nUnit].m_dAlignData, g_clTaskWork[m_nUnit].dpFind);

		nRetVal = g_CheckAlignSpec(m_nUnit, g_clTaskWork[m_nUnit].m_dAlignData.y, 0.0);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lens Align 보정량(X:%.03lf, Y:%.03lf)[STEP : %d]"), g_clTaskWork[m_nUnit].m_dAlignData.x, g_clTaskWork[m_nUnit].m_dAlignData.y, nStep);
		AddLog(szLog, 0, m_nUnit);

		if (nRetVal == 0)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lens Align 보정량 초과 Offset 0.0 진행 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			//
			g_clTaskWork[m_nUnit].m_dLensAlign[0] = 0.0;
			g_clTaskWork[m_nUnit].m_dLensAlign[1] = 0.0;
			g_clTaskWork[m_nUnit].m_dLensAlign[2] = 0.0;
			g_clTaskWork[m_nUnit].m_nRetryCount = 0;

			g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
			nRetStep = 18000;
			break;
		}
		else if (nRetVal == 2)
		{
			//Spec In
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lens Align 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clTaskWork[m_nUnit].m_nRetryCount = 0;
			g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();

			nRetStep = 18000;
			break;
		}
		else
		{
			//nRetVal = 1 이면 retry
		}
		g_clTaskWork[m_nUnit].m_dLensAlign[0] += g_clTaskWork[m_nUnit].m_dAlignData.x;
		g_clTaskWork[m_nUnit].m_dLensAlign[1] += g_clTaskWork[m_nUnit].m_dAlignData.y;
		g_clTaskWork[m_nUnit].m_dLensAlign[2] += 0.0;



		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lens Align 보정이동(X:%.03lf, Y:%.03lf) [STEP : %d]"), g_clTaskWork[m_nUnit].m_dSensorAlign[0], g_clTaskWork[m_nUnit].m_dSensorAlign[1], nStep);
		AddLog(szLog, 0, m_nUnit);
		nRetStep = 16500;

		break;
	case 16500:

		nRetStep = 17000;
		break;
	case 17000:
		if (g_clTaskWork[m_nUnit].m_nRetryCount > (g_clModelData[m_nUnit].m_nLensAlignRetryCount - 1))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS ALIGN RETRY 횟수(%d) 초과 [STEP : %d]"), g_clModelData[m_nUnit].m_nLensAlignRetryCount, nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -17000;
			break;
		}

		g_clTaskWork[m_nUnit].m_nRetryCount++;
		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS ALIGN RETRY %d회 [STEP : %d]"), g_clTaskWork[m_nUnit].m_nRetryCount, nStep);
		AddLog(szLog, 0, m_nUnit);

		nRetStep = 17500;
		break;
	case 17500:
		//! 보정 이동 및 ALIGN 재측정
		if (g_clMotorSet.MoveLensXYMotor(m_nUnit, LENS_ALIGN_POS, g_clTaskWork[m_nUnit].m_dLensAlign[0], g_clTaskWork[m_nUnit].m_dLensAlign[1], true) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS ALIGN 보정 위치(%.03lf, %.03lf) 이동 실패 [STEP : %d]"),
				g_clTaskWork[m_nUnit].m_dLensAlign[0], g_clTaskWork[m_nUnit].m_dLensAlign[1], nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -17500;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS ALIGN 보정 위치(%.03lf, %.03lf) 이동 완료 [STEP : %d]"),
			g_clTaskWork[m_nUnit].m_dLensAlign[0], g_clTaskWork[m_nUnit].m_dLensAlign[1], nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 15000;	//step Back 리트라이

		break;
	case 18000:
		g_clVision.ClearOverlay(m_nUnit, VIDEO_CAM);
		g_clVision.DrawOverlayAll(m_nUnit, VIDEO_CAM);
		OCControl[m_nUnit].Send_12CHChannel_Value(LIGHT_BD_ALIGN_CH1, 0);
		if (g_clMotorSet.MoveLensZMotor(m_nUnit, WAIT_POS, 0.0, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 WAIT_POS 위치 이동 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -18000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 WAIT_POS 위치 이동 완료 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 18500;
		break;
	case 18500:
		//LENS Z축 대기위치 확인
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_LENS_Z];
		curPos = g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Z);// -g_clSysData.m_dOrgDataset[m_nUnit][MOTOR_LENS_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_Z) && (curPos - dPos[0]) < ENCORDER_GAP)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS Z축 WAIT 위치 이동 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 19000;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS Z축 WAIT 위치 이동 시간 초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -18000;
			break;
		}
		
		break;
	case 19000:
		if (g_clMotorSet.MoveLensTxTyMotor(m_nUnit, LASER_IN_POS, 0.0, 0.0, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS TX,TY축 LENS LASER_IN_POS 이동 명령 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -19000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS TX,TY축 LENS LASER_IN_POS 이동 명령 성공 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 19200;
		break;

	case 19200:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[LASER_IN_POS].dPos[MOTOR_LENS_TX];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[LASER_IN_POS].dPos[MOTOR_LENS_TY];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_TX) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_TX) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_TY) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_TY) - dPos[1]) < ENCORDER_GAP)))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS TX,TY축 LENS LASER_IN_POS 위치 이동 완료 [STEP : %d"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 19500;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS TX,TY축 LENS ALIGN 위치 이동 시간 초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -19000;
			break;
		}
		break;








	case 19500:
		 
		//Lens Align End
		nRetStep = 20000;
		break;

	case 20000:
		//LENS LASER START
		// LASER 변수 초기화
		g_clTaskWork[m_nUnit].m_nLaserTiltIndex = 0;

		g_clTaskWork[m_nUnit].m_dLaserTiltX[0] = 0.0;
		g_clTaskWork[m_nUnit].m_dLaserTiltY[0] = 0.0;

		for (i = 0; i < 4; i++)
		{
			g_clTaskWork[m_nUnit].m_dLaserVal[i] = 0.0;
			g_clTaskWork[m_nUnit].m_clDpLaserPos[i].x = 0.0;
			g_clTaskWork[m_nUnit].m_clDpLaserPos[i].y = 0.0;
		}

		g_clTaskWork[m_nUnit].m_nRetryCount = 0;
		nRetStep = 20500;
		break;

	case 20500:
		nRetStep = 21500;
		break;

		if (g_clMotorSet.MoveLensZMotor(m_nUnit, WAIT_POS, 0.0, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS Z축 WAIT 위치 이동 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -20500;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS Z축 WAIT 위치 이동 명령 성공 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 21000;

		break;
	case 21000:
		//LENS Z축 대기위치 확인
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_LENS_Z];
		curPos = g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Z);// -g_clSysData.m_dOrgDataset[m_nUnit][MOTOR_LENS_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_Z) && (curPos - dPos[0]) < ENCORDER_GAP)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS Z축 WAIT 위치 이동 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 21500;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS Z축 WAIT 위치 이동 시간 초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -20500;
			break;
		}

		break;
	case 21500:
		//LENS X,Y LASER POS 1이동
		if (g_clMotorSet.MoveLensXYMotor(m_nUnit, LASER_IN_POS, g_clTaskWork[m_nUnit].m_dLensAlign[0], g_clTaskWork[m_nUnit].m_dLensAlign[1], false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS X,Y축 LASER POS 1  위치 이동 명령 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -22000;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS X,Y축 LASER POS 1 위치 이동 명령 성공 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();

		nRetStep = 22000;
		break;

	case 22000:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[LASER_IN_POS].dPos[MOTOR_LENS_X] + g_clTaskWork[m_nUnit].m_dLensAlign[0];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[LASER_IN_POS].dPos[MOTOR_LENS_Y] + g_clTaskWork[m_nUnit].m_dLensAlign[1];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_X) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_X) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_Y) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Y) - dPos[1]) < ENCORDER_GAP)))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS X,Y축 LASER 보정위치(%.03lf, %.03lf) 이동 완료 [STEP : %d]"),
				g_clTaskWork[m_nUnit].m_dLensAlign[0], g_clTaskWork[m_nUnit].m_dLensAlign[1], nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 22200;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS X,Y축 LASER 보정위치(%.03lf, %.03lf) 이동 시간초과 [STEP : %d]"),
				g_clTaskWork[m_nUnit].m_dLensAlign[0], g_clTaskWork[m_nUnit].m_dLensAlign[1], nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -21500;
			break;
		}
		break;








	case 22200:
		if (g_clTaskWork[m_nUnit].m_nLaserTiltIndex > 0)
		{
			nRetStep = 23000;

			g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
			break;
		}
		if (g_clMotorSet.MoveLensZMotor(m_nUnit, LASER_IN_POS, 0.0, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS Z축 LASER 위치 이동 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -22200;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS Z축 LASER 위치 이동 명령 성공 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 22500;
		break;

	case 22500:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[LASER_IN_POS].dPos[MOTOR_LENS_Z];
		curPos = g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Z);// -g_clSysData.m_dOrgDataset[m_nUnit][MOTOR_LENS_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_Z) && (curPos - dPos[0]) < ENCORDER_GAP)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS Z축 LASER 위치 이동 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 23000;

			g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS Z축 LASER 위치 이동 시간 초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -22500;
			break;
		}
		break;
	case 23000:
		//! 측정 전 DELAY
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > (DWORD)(g_clModelData[m_nUnit].m_dLaserDelay * 1000) &&
			g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_X) && g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_Y))
		{
			nRetStep = 23500;
			Sleep(200);
		}
		break;
	case 23500:
		//레이저 측정
		g_clTaskWork[m_nUnit].m_bRecvLaserTilt = false;
		g_clTaskWork[m_nUnit].m_clDpLaserPos[g_clTaskWork[m_nUnit].m_nLaserTiltIndex].x = g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_X);
		g_clTaskWork[m_nUnit].m_clDpLaserPos[g_clTaskWork[m_nUnit].m_nLaserTiltIndex].y = g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Y);

		if (g_pCarAABonderDlg->SendLaserMeasurePacket(m_nUnit) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] 변위센서 측정 명령 송신 실패. [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -23500;
			break;
		}
		//g_clTaskWork[nUnit].m_dLaserVal[g_clTaskWork[nUnit].m_nLaserTiltIndex] = dValue[0];

		

		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] 변위센서 측정 명령 송신 성공 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 24000;
		break;
	case 24000:
		if (g_clTaskWork[m_nUnit].m_nLaserTiltIndex > 3)
		{
			nRetStep = 24500;
			break;
		}
		g_clTaskWork[m_nUnit].m_nLaserTiltIndex++;
		// X축 -방향
		if (g_clTaskWork[m_nUnit].m_nLaserTiltIndex == 1)
		{
			if (g_clMotorSet.MoveAxisComplete(m_nUnit, MOTOR_LENS_X, REL, (g_clModelData[m_nUnit].m_dLaserMoveX[0] * -1), g_clSysData.m_dMotorSpeed[m_nUnit][MOTOR_LENS_X], true) == false)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] 변위센서 %d번째 위치 이동 실패 [STEP : %d]"), g_clTaskWork[m_nUnit].m_nLaserTiltIndex + 1, nStep);
				AddLog(szLog, 1, m_nUnit, true);

				nRetStep = -24500;
				break;
			}

			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] 변위센서 %d번째 위치 이동 완료 [STEP : %d]"), g_clTaskWork[m_nUnit].m_nLaserTiltIndex + 1, nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
			nRetStep = 23000;

		}
		else if (g_clTaskWork[m_nUnit].m_nLaserTiltIndex == 2)
		{
			if (g_clMotorSet.MoveAxisComplete(m_nUnit, MOTOR_LENS_Y, REL, g_clModelData[m_nUnit].m_dLaserMoveY[0], g_clSysData.m_dMotorSpeed[m_nUnit][MOTOR_LENS_Y], true) == false)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] 변위센서 %d번째 위치 이동 실패 [STEP : %d]"), g_clTaskWork[m_nUnit].m_nLaserTiltIndex + 1, nStep);
				AddLog(szLog, 1, m_nUnit, true);

				nRetStep = -24500;
				break;
			}

			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] 변위센서 %d번째 위치 이동 완료 [STEP : %d]"), g_clTaskWork[m_nUnit].m_nLaserTiltIndex + 1, nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
			nRetStep = 23000;
		}
		else if (g_clTaskWork[m_nUnit].m_nLaserTiltIndex == 3)
		{
			if (g_clMotorSet.MoveAxisComplete(m_nUnit, MOTOR_LENS_X, REL, (g_clModelData[m_nUnit].m_dLaserMoveX[0] * 1), g_clSysData.m_dMotorSpeed[m_nUnit][MOTOR_LENS_X], true) == false)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] 변위센서 %d번째 위치 이동 실패 [STEP : %d]"), g_clTaskWork[m_nUnit].m_nLaserTiltIndex + 1, nStep);
				AddLog(szLog, 1, m_nUnit, true);

				nRetStep = -24500;
				break;
			}

			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] 변위센서 %d번째 위치 이동 완료 [STEP : %d]"), g_clTaskWork[m_nUnit].m_nLaserTiltIndex + 1, nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
			nRetStep = 23000;
		}
		break;
	case 24500:

		//! TX,TY 보정량 계산
		g_CalcLaserTilt(m_nUnit, dLaserTx, dLaserTy);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] 변위센서 보정량(TX : %.03lf, TY : %.03lf) [STEP : %d]"), dLaserTx, dLaserTy, nStep);
		AddLog(szLog, 0, m_nUnit);

		nRetVal = g_CheckTiltLimit(m_nUnit, 1, dLaserTx, dLaserTy);

		g_clTaskWork[m_nUnit].m_dLaserTiltX[0] = dLaserTx * 0.55;
		g_clTaskWork[m_nUnit].m_dLaserTiltY[0] = dLaserTy * 0.55;

		/*if ((fabs(dLaserTx) < g_clModelData[m_nUnit].m_dOkLimit[MOTOR_LENS_TX]))
			g_clTaskWork[m_nUnit].m_dLaserTiltX[0] = 0.0;

		if ((fabs(dLaserTy) < g_clModelData[m_nUnit].m_dOkLimit[MOTOR_LENS_TY]))
			g_clTaskWork[m_nUnit].m_dLaserTiltY[0] = 0.0;*/


		if (nRetVal == 1)	// 보정이동
		{
			nRetStep = 25000;
		}

		else if (nRetVal == 2)	// OK
		{
			g_clTaskWork[m_nUnit].m_nRetryCount = 0; 

			nRetStep = 26000;
			break;
		}
		// 보정 LIMIT 초과
		else
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] TILT 보정값 LIMIT 초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -20000;
			break;
		}

		break;
	case 25000:
		//! TX,TY 보정 

		if (g_clMotorSet.MoveLensTxTyMotor(m_nUnit, g_clTaskWork[m_nUnit].m_dLaserTiltX[0], g_clTaskWork[m_nUnit].m_dLaserTiltY[0], true) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] TILT TX(%.03lf), TY(%.03lf) 보정 이동 실패 [STEP : %d]"),
				g_clTaskWork[m_nUnit].m_dLaserTiltX[0], g_clTaskWork[m_nUnit].m_dLaserTiltY[0], nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -25000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] TILT TX(%.03lf), TY(%.03lf) 보정 이동 완료 [STEP : %d]"),
			g_clTaskWork[m_nUnit].m_dLaserTiltX[0], g_clTaskWork[m_nUnit].m_dLaserTiltY[0], nStep);
		AddLog(szLog, 0, m_nUnit);

		nRetStep = 25500;

		break;
	case 25500:
		if (g_clTaskWork[m_nUnit].m_nRetryCount > (g_clModelData[m_nUnit].m_nLaserRetryCount - 1))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] TILT 보정 횟수(%d) 초과 [STEP : %d]"), g_clModelData[m_nUnit].m_nLaserRetryCount, nStep);
			AddLog(szLog, 1, m_nUnit, true);

			g_clTaskWork[m_nUnit].m_nRetryCount = 0;

			nRetStep = -25500;
			break;
		}

		g_clTaskWork[m_nUnit].m_nRetryCount++;
		g_clTaskWork[m_nUnit].m_nLaserTiltIndex = 0;
		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();

		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] TILT %d회 재시도 [STEP : %d]"), g_clTaskWork[m_nUnit].m_nRetryCount, nStep);
		AddLog(szLog, 0, m_nUnit);

		nRetStep = 21500;
		break;
	case 26000:
		OCControl[m_nUnit].Send_12CHChannel_Value(LIGHT_BD_ALIGN_CH1, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_ALIGN_LENS]);
		nRetStep = 26500;
		break;
	case 26500:
		if (g_clMotorSet.MoveLensZMotor(m_nUnit, WAIT_POS, 0.0, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS Z축 WAIT 위치 이동 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -26500;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS Z축 WAIT 위치 이동 명령 성공 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 27000;
		break; 
	case 27000: 
		//LENS Z축 대기위치 확인
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_LENS_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 WAIT_POS 위치 이동 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 28000;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 WAIT_POS 위치 이동 시간 초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -26500;
			break;
		}
		break;
	case 28000:
		//Laser 보정 완료 
		nRetStep = 29000;
		break;
	case 29000:
		nRetStep = 30000;
		break;
	case 30000:

		//Laser 틸트후 Align
		nRetStep = 31500; 
		break;
	case 31500:
		if (g_clMotorSet.MoveLensXYMotor(m_nUnit, LENS_ALIGN_POS, 0.0, 0.0, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X,Y축 LENS ALIGN 위치 이동 명령 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -31500;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X,Y축 LENS ALIGN 위치 이동 명령 성공 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 32000;
		break; 
	case 32000:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[LENS_ALIGN_POS].dPos[MOTOR_LENS_X];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[LENS_ALIGN_POS].dPos[MOTOR_LENS_Y];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_X) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_X) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_Y) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Y) - dPos[1]) < ENCORDER_GAP)))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X,Y축 LENS ALIGN 위치 이동 완료 [STEP : %d"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 32500;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X,Y축 LENS ALIGN 위치 이동 시간 초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -31500;
			break;
		}

		break;
	case 32500:
		//레이저 보정한 상태라서 주석처리
		/*if (g_clMotorSet.MoveLensTxTyMotor(m_nUnit, LENS_ALIGN_POS, 0.0, 0.0, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS TX,TY축 LENS ALIGN 이동 명령 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -32500;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS TX,TY축 LENS ALIGN 이동 명령 성공 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);*/

		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 33000;
		break;
	case 33000:
		nRetStep = 33500;
		break;
		/*dPos[0] = g_clModelData[m_nUnit].m_stTeachData[LENS_ALIGN_POS].dPos[MOTOR_LENS_TX];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[LENS_ALIGN_POS].dPos[MOTOR_LENS_TY];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_TX) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_TX) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_TY) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_TY) - dPos[1]) < ENCORDER_GAP)))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS TX,TY축 LENS ALIGN 위치 이동 완료 [STEP : %d"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 33500;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS TX,TY축 LENS ALIGN 위치 이동 시간 초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -32500;
			break;
		}*/
		break;
	case 33500:
		if (g_clMotorSet.MoveLensZMotor(m_nUnit, LENS_ALIGN_POS, 0.0, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 LENS ALIGN 위치 이동 명령 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -33500;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 LENS ALIGN 위치 이동 명령 성공 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 34000;
		break;
	case 34000:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[LENS_ALIGN_POS].dPos[MOTOR_LENS_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 LENS ALIGN 위치 이동 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 34500;
			g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 LENS ALIGN 위치 이동 시간 초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -33500;
			break;
		}
		break;
	case 34500:
		g_clTaskWork[m_nUnit].m_nRetryCount = 0;

		g_clTaskWork[m_nUnit].m_dAADataX = 0.0;
		g_clTaskWork[m_nUnit].m_dAADataY = 0.0;
		g_clTaskWork[m_nUnit].m_dAADataTh = 0.0;

		g_clTaskWork[m_nUnit].m_dAlignData.x = 0.0;
		g_clTaskWork[m_nUnit].m_dAlignData.y = 0.0;
		g_clTaskWork[m_nUnit].m_dAlignData.t = 0.0;

		g_clTaskWork[m_nUnit].dpFind.x = 0.0;
		g_clTaskWork[m_nUnit].dpFind.y = 0.0;


		g_clTaskWork[m_nUnit].m_dLensAlign[0] = 0.0;
		g_clTaskWork[m_nUnit].m_dLensAlign[1] = 0.0;
		g_clTaskWork[m_nUnit].m_dLensAlign[2] = 0.0;

		nRetStep = 35000;
		break;
	case 35000:
		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 35500;
		break;
	case 35500:
		//! ALIGN전 Delay
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > (DWORD)g_clModelData[m_nUnit].m_dSensorAlignDelay * 1000)
		{
			nRetStep = 36000;
		}
		break;
	case 36000:
		g_clVision.ClearOverlay(m_nUnit);
		g_clVision.CalcSingleMarkAlign(m_nUnit, LENS_ALIGN_MARK, 0, g_clTaskWork[m_nUnit].m_dAlignData, g_clTaskWork[m_nUnit].dpFind);

		nRetVal = g_CheckAlignSpec(m_nUnit, g_clTaskWork[m_nUnit].m_dAlignData.y, 0.0);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lens Align 보정량(X:%.03lf, Y:%.03lf)[STEP : %d]"), g_clTaskWork[m_nUnit].m_dAlignData.x, g_clTaskWork[m_nUnit].m_dAlignData.y, nStep);
		AddLog(szLog, 0, m_nUnit);

		if (nRetVal == 0)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lens Align 보정량 초과 Offset 0.0 진행 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			//
			g_clTaskWork[m_nUnit].m_dLensAlign[0] = 0.0;
			g_clTaskWork[m_nUnit].m_dLensAlign[1] = 0.0;
			g_clTaskWork[m_nUnit].m_dLensAlign[2] = 0.0;
			g_clTaskWork[m_nUnit].m_nRetryCount = 0;

			g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
			nRetStep = 38000;
			break;
		}
		else if (nRetVal == 2)
		{
			//Spec In
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lens Align 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clTaskWork[m_nUnit].m_nRetryCount = 0;
			g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();

			nRetStep = 38000;
			break;
		}
		else
		{
			//nRetVal = 1 이면 retry
		}
		g_clTaskWork[m_nUnit].m_dLensAlign[0] += g_clTaskWork[m_nUnit].m_dAlignData.x;
		g_clTaskWork[m_nUnit].m_dLensAlign[1] += g_clTaskWork[m_nUnit].m_dAlignData.y;
		g_clTaskWork[m_nUnit].m_dLensAlign[2] += 0.0;



		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lens Align 보정이동(X:%.03lf, Y:%.03lf) [STEP : %d]"), g_clTaskWork[m_nUnit].m_dSensorAlign[0], g_clTaskWork[m_nUnit].m_dSensorAlign[1], nStep);
		AddLog(szLog, 0, m_nUnit);
		nRetStep = 36500;

		break;
	case 36500:

		nRetStep = 37000;
		break;
	case 37000:
		if (g_clTaskWork[m_nUnit].m_nRetryCount > (g_clModelData[m_nUnit].m_nLensAlignRetryCount - 1))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS ALIGN RETRY 횟수(%d) 초과 [STEP : %d]"), g_clModelData[m_nUnit].m_nLensAlignRetryCount, nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -37000;
			break;
		}

		g_clTaskWork[m_nUnit].m_nRetryCount++;
		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS ALIGN RETRY %d회 [STEP : %d]"), g_clTaskWork[m_nUnit].m_nRetryCount, nStep);
		AddLog(szLog, 0, m_nUnit);

		nRetStep = 37500;
		break;
	case 37500:
		//! 보정 이동 및 ALIGN 재측정
		if (g_clMotorSet.MoveLensXYMotor(m_nUnit, LENS_ALIGN_POS, g_clTaskWork[m_nUnit].m_dLensAlign[0], g_clTaskWork[m_nUnit].m_dLensAlign[1], true) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS ALIGN 보정 위치(%.03lf, %.03lf) 이동 실패 [STEP : %d]"),
				g_clTaskWork[m_nUnit].m_dLensAlign[0], g_clTaskWork[m_nUnit].m_dLensAlign[1], nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -37500;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS ALIGN 보정 위치(%.03lf, %.03lf) 이동 완료 [STEP : %d]"),
			g_clTaskWork[m_nUnit].m_dLensAlign[0], g_clTaskWork[m_nUnit].m_dLensAlign[1], nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 35000;	//step Back 리트라이

		break;
	case 38000:
		if (g_clMotorSet.MoveLensZMotor(m_nUnit, WAIT_POS, 0.0, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 WAIT_POS 위치 이동 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -38000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Z축 WAIT_POS 위치 이동 완료 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwLensTickCount = GetTickCount();
		nRetStep = 38500;
		break;
	case 38500:
		//LENS Z축 대기위치 확인
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_LENS_Z];
		curPos = g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Z);
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_Z) && (curPos - dPos[0]) < ENCORDER_GAP)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS Z축 WAIT 위치 이동 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 38600;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] LENS Z축 WAIT 위치 이동 시간 초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -38000;
			break;
		}

		break; 
	case 38600:
		if (g_clMotorSet.MoveLensXMotor(m_nUnit, WAIT_POS, 0.0, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X WAIT_POS 이동 명령 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -38600;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X WAIT_POS 이동 명령 성공 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 38700;
		break;
	case 38700:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_LENS_X];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_X) && (g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_X) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X축 대기위치 이동 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 38800;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X축 대기위치 이동 시간초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -38700;
			break;
		}
		break;
	case 38800:
		if (g_clMotorSet.MoveLensYMotor(m_nUnit, CHART_POS, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Y CHART_POS 이동 명령 실패 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -38800;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Y CHART_POS 이동 명령 성공 [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 38900;
		break;
	case 38900:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[CHART_POS].dPos[MOTOR_LENS_Y];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_Y) && (g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Y) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Y축 CHART_POS 이동 완료 [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 39000;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS Y축 CHART_POS 이동 시간초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -38900;
			break;
		}
		break;
	case 39000:
		if (g_clMotorSet.MoveLensXYMotor(m_nUnit, CHART_POS, g_clTaskWork[m_nUnit].m_dLensAlign[0], g_clTaskWork[m_nUnit].m_dLensAlign[1], true) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS CHART 보정 위치(%.03lf, %.03lf) 이동 실패 [STEP : %d]"),
				g_clTaskWork[m_nUnit].m_dLensAlign[0], g_clTaskWork[m_nUnit].m_dLensAlign[1], nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -39000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS CHART 보정 위치(%.03lf, %.03lf) 이동 완료 [STEP : %d]"), 
			g_clTaskWork[m_nUnit].m_dLensAlign[0], g_clTaskWork[m_nUnit].m_dLensAlign[1], nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 39200;
		break;
	case 39200:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[CHART_POS].dPos[MOTOR_LENS_X] + g_clTaskWork[m_nUnit].m_dLensAlign[0];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[CHART_POS].dPos[MOTOR_LENS_Y] + g_clTaskWork[m_nUnit].m_dLensAlign[1];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_X) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_X) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_LENS_Y) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Y) - dPos[1]) < ENCORDER_GAP)))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X,Y축 CHART 위치 이동 완료 [STEP : %d"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 39400;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwLensTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LENS X,Y축 CHART 위치 이동 시간 초과 [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -39000;
			break;
		}
		break;
	case 39400:
		nRetStep = 39600;
		break;
	case 39600:
		g_clTaskWork[m_nUnit].m_bLensLaserCompleteCheck = true;
		nRetStep = 40000;
		break;
	default:
		nRetStep = -1;
		break;
	}
#endif
	return nRetStep;
}

