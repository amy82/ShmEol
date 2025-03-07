#include "StdAfx.h"
#include "PcbProcess.h"

CWinThread* pThread_TaskCCD = NULL;
bool bThreadCCDRun = false;
typedef struct THREADV
{
	int t_Unit;
}_threadV;

UINT Thread_TaskCCD(LPVOID parm)
{
	_threadV* getData = (_threadV*)parm;
	bThreadCCDRun = true;
	TCHAR szLog[SIZE_OF_1K];
	Sleep(300);//Sleep(1100);
	g_clLaonGrabberWrapper[getData->t_Unit].SetCurrentState(CCD_GRAB_STOP);


	if (g_clLaonGrabberWrapper[getData->t_Unit].OpenDevice() == false)
	{
		AddLog(_T("[FAIL] Device Open Fail"), 0, getData->t_Unit, false);
	}


	Sleep(500);
	if(g_clLaonGrabberWrapper[getData->t_Unit].StartGrabCcdProcess() == false)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] CCD OPEN ����. ��ǰ ���� ���� �� ��ǰ �ҷ��� Ȯ���ϼ���"));
		AddLog(szLog, 1, getData->t_Unit, true);
	}

	bThreadCCDRun = false;


	return 1;
}
CPcbProcess::CPcbProcess(void)
{
	m_bFlagSocketReq = false;
	m_nSocketCnt = 0;
	VaccumRetry = 0;
	TestPatternRetry = 0;
	mLightRetry = 0;
	VarRetry = 0;
	mOcLightChannel = 0;
	rawSumCount = 0;
	m_nDiffTestOk = false;
	nDiffRetry = 0;
	nLotProcessingComplete_ACK = -1;
	nRunOnlineControlState = false;
}


CPcbProcess::~CPcbProcess(void)
{
}



//-----------------------------------------------------------------------------
//
//	EOL ����(10000 ~ 20000)
//
//-----------------------------------------------------------------------------
int CPcbProcess::HomeProcess(int nStep)
{
	TCHAR szLog[SIZE_OF_1K];
	CString sMsg = _T("");
	int nHomeFlag = 0;
	int nRetStep = 0;
	int i = 0;
	double dPos[4] = { 0.0, 0.0, 0.0, 0.0 };
	double curPos = 0.0;
	nRetStep = nStep;
	g_clTaskWork[m_nUnit].m_bAreaSensorRun = true;	// HomeProcess

	if (g_clDioControl.CurtainDoorCheck(m_nUnit, true) == true)		//HomeProcess
	{
		g_clMotorSet.StopAxisAll(m_nUnit);
		g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1008);
		_stprintf_s(szLog, SIZE_OF_1K, _T("[ERROR] �������� �� CURTAIN ����. �Ͻ� ����"));
		nRetStep *= -1;
		AddLog(szLog, 1, m_nUnit, true);
		return nRetStep;
	}
	switch (nStep)
	{
	case 10000:
		if (g_clMesCommunication[m_nUnit].m_dEqupControlState[1] == eOnlineRemote &&
			g_clMesCommunication[m_nUnit].m_dProcessState[0] != g_clMesCommunication[m_nUnit].m_dProcessState[1])
		{
			g_clMesCommunication[m_nUnit].m_dProcessState[0] = g_clMesCommunication[m_nUnit].m_dProcessState[1];
			g_clMesCommunication[m_nUnit].m_dProcessState[1] = eIDLE;
			g_clMesCommunication[m_nUnit].m_uAlarmList.clear();

			_stprintf_s(szLog, SIZE_OF_1K, _T("[ORG] (Idle)Process State Change Report [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clTaskWork[0].bIdleTimeExceed = false;		//init
			g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(PROCESS_STATE_CHANGED_REPORT_10401);	//SEND S6F11


			CTime cTime = CTime::GetCurrentTime();
			CString strData;
			strData.Format(_T("%02d%02d%02d%02d%02d%02d"),
				cTime.GetYear(),
				cTime.GetMonth(),
				cTime.GetDay(),
				cTime.GetHour(),
				cTime.GetMinute(),
				cTime.GetSecond());
			_stprintf_s(g_clTaskWork[m_nUnit].m_szIdleStartTime, SIZE_OF_100BYTE, _T("%s"), strData);		//Auto_M_PCBLoading
			g_pCarAABonderDlg->KillTimer(WM_IDLE_REASON_TIMER);

			if (g_clMesCommunication[m_nUnit].IdleSetTimeInterval < 1)
			{
				g_clMesCommunication[m_nUnit].IdleSetTimeInterval = 5;	//min  1min = 60000
			}
			g_pCarAABonderDlg->SetTimer(WM_IDLE_REASON_TIMER, g_clMesCommunication[m_nUnit].IdleSetTimeInterval * 60000, NULL);		//30000 Step
			strData.Empty();
		}
		nRetStep = 10100;
		break;
	case 10100:

		//WhiteOcLightControl[m_nUnit].DPS_Light_OnOffLevel(LIGHT_OC_WHITE_CH1, 0, 0);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] �̹����� OFF [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		/*

		if (g_clDioControl.OCCylinderFor(m_nUnit, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB �̹����� ���� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -10100;
			break;
		}
		
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();*/
		nRetStep = 10200;
		break;

	case 10200:
		/*if (g_clDioControl.OCCylinderForCheck(m_nUnit, false) == true)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB �̹����� ���� Ȯ�� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 10300;
			break;
		}
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > 5000)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB �̹����� ���� Ȯ�� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -10100;
			break;
		}*/
		nRetStep = 10300;
		break;
	case 10300:
		//! PCB Z�� (-)Limit �̵�
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) == false)
		{
			g_clMotorSet.StopAxis(m_nUnit, MOTOR_PCB_Z);
			Sleep(100);
			break;
		}
		if (g_clMotorSet.MoveAxisLimit(m_nUnit, MOTOR_PCB_Z, (2 * -1), 0.1, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� (-)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -10300;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� (-)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 10400;
		break;

	case 10400:
		//! PCB Z�� (-)Limit �̵� Ȯ��
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && g_clMotorSet.GetNegaSensor(m_nUnit, MOTOR_PCB_Z))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� (-)Limit ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 10500;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� (-)Limit ��ġ �̵� �ð��ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -10300;
			break;
		}
		break;
	case 10500:
		/*_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] DARK CYLINDER ��� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		if (g_clDioControl.DarkPusher(m_nUnit, true) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] DARK CYLINDER ��� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -10500;
			break;
		}*/

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 10600;
		break;

	case 10600:
		nRetStep = 10700;
		break;

		/*if (g_clDioControl.DarkPusherCheck(m_nUnit, true) == true)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] DARK CYLINDER ��� Ȯ�� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			nRetStep = 10700;
			break;
		}
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > 5000)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] DARK CYLINDER ��� Ȯ�� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -10500;
			break;
		}*/
		break;

	case 10700:
		nRetStep = 10720;
		break;
	case 10720:
		nRetStep = 10730;
		break;
	case 10730:
		nRetStep = 10740;
		break;
	case 10740:

		if (g_clDioControl.PcbSensorCheck(m_nUnit) == true)
		{
			if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//���� ���� ���� Ȯ��	Home
			{
				g_clMotorSet.StopAxisAll(m_nUnit);
				g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1007);
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Vacuum Ȯ�� ���� [STEP : %d]"), nStep);
				AddLog(szLog, 1, m_nUnit, true);

				nRetStep = -10740;
				break;
			}
		}

		nRetStep = 10750;
		break;
	case 10750:
		//! PCB Y�� (-)Limit �̵�
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Y) == false)
		{
			g_clMotorSet.StopAxis(m_nUnit, MOTOR_PCB_Y);
			Sleep(100);
			break;
		}

		if (g_clMotorSet.MoveAxisLimit(m_nUnit, MOTOR_PCB_Y, (20 * -1), 0.1, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Y�� (-)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -10750;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Y�� (-)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();

		nRetStep = 10800;
		break;

	case 10800:
		//! PCB Y�� (-)Limit �̵� Ȯ��
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Y) && g_clMotorSet.GetNegaSensor(m_nUnit, MOTOR_PCB_Y))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Y�� (-)Limit ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 10840;
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Y�� (-)Limit ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -10750;
			break;
		}
		break;
	case 10840:
		//! PCB X�� (-)Limit �̵�
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_X) == false)
		{
			g_clMotorSet.StopAxis(m_nUnit, MOTOR_PCB_X);
			Sleep(100);
			break;
		} 

		if (g_clMotorSet.MoveAxisLimit(m_nUnit, MOTOR_PCB_X, (20 * -1), 0.1, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB X�� (-)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -10750;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB X�� (-)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 10900;
		
		break;

	case 10900:

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 10950;
		break;
	case 10950:
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_X) && g_clMotorSet.GetNegaSensor(m_nUnit, MOTOR_PCB_X))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB X�� (-)Limit ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			nRetStep = 11000;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB X�� (-)Limit ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -10840;
			break;
		}
		break;
	case 11000:
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 11050;
		break; 

	case 11050:
		nRetStep = 11100;
		break;
	case 11100:
		
		nRetStep = 11150;
		break;
	case 11150:
		nRetStep = 11200;
		break;
	case 11200:
		
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 11250;
		break;
	case 11250: 
		nRetStep = 11300;
		break;
	case 11300:
		//! PCB TH�� (+)Limit �̵�
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TH) == false)
		{
			g_clMotorSet.StopAxis(m_nUnit, MOTOR_PCB_TH);
			Sleep(100);
			break;
		}

		if (g_clMotorSet.MoveAxisLimit(m_nUnit, MOTOR_PCB_TH, (5 * 1), 0.1, HomeSensor, SIGNAL_UP_EDGE, SLOWDOWN_STOP) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TH�� (+)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -11300;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TH�� (+)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount(); 
		nRetStep = 11320; 
		break;
	case 11320:
		//! PCB TH�� (+)Limit �̵� Ȯ��
		if (g_clMotorSet.GetHomeSensor(m_nUnit, MOTOR_PCB_TH))
		{
			g_clMotorSet.StopAxis(m_nUnit, MOTOR_PCB_TH);
			Sleep(100);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TH�� HOME ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 11400;
			break;
		}
		if (g_clMotorSet.GetPosiSensor(m_nUnit, MOTOR_PCB_TH))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TH�� (+)Limit ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 11340;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TH�� (+)Limit ��ġ �̵� �ð��ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -11300;
			break;
		}
		 
		break;
	case 11340:
		//! PCB TH�� (-)Limit �̵�
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TH) == false)
		{
			g_clMotorSet.StopAxis(m_nUnit, MOTOR_PCB_TH);
			Sleep(100);
			break;
		}

		if (g_clMotorSet.MoveAxisLimit(m_nUnit, MOTOR_PCB_TH, (5 * -1), 0.1, HomeSensor, SIGNAL_UP_EDGE, SLOWDOWN_STOP) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TH�� (-)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -11340;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TH�� (-)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 11360;
		break;
	case 11360:
		//! PCB TH�� HOME �̵� Ȯ��
		if (g_clMotorSet.GetHomeSensor(m_nUnit, MOTOR_PCB_TH))
		{
			g_clMotorSet.StopAxis(m_nUnit, MOTOR_PCB_TH);
			Sleep(100);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TH�� HOME ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 11400;
			break;
		}
		if (g_clMotorSet.GetNegaSensor(m_nUnit, MOTOR_PCB_TH))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TH�� (-)Limit ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 11400;
			break;
		}
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TH�� HOME ��ġ �̵� �ð��ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -11360;
			break;
		}
		break;
	case 11400:
		//! PCB TX, TY�� (+)Limit �̵�
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TX) == false)
		{
			g_clMotorSet.StopAxis(m_nUnit, MOTOR_PCB_TX);
			Sleep(100);
			nRetStep = 11400;
			break;
		}
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TY) == false)
		{
			g_clMotorSet.StopAxis(m_nUnit, MOTOR_PCB_TY);
			Sleep(100);
			nRetStep = 11400;
			break;
		}
		if (g_clMotorSet.MoveAxisLimit(m_nUnit, MOTOR_PCB_TX, (5 * -1), 0.1, HomeSensor, SIGNAL_UP_EDGE, SLOWDOWN_STOP) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX�� (-)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -11100;
			break;
		}
		Sleep(100);
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX�� (-)Limit ��ġ ���� ���� [STEP : %d]"), nStep); 
		AddLog(szLog, 0, m_nUnit);

		if (g_clMotorSet.MoveAxisLimit(m_nUnit, MOTOR_PCB_TY, (5 * -1), 0.1, HomeSensor, SIGNAL_UP_EDGE, SLOWDOWN_STOP) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TY�� (-)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -11100;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TY�� (-)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

	
		nRetStep = 11500;
		break;
	case 11500:
		//! PCB TX, TY�� (+)Limit �̵� Ȯ��
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TX) && (g_clMotorSet.GetNegaSensor(m_nUnit, MOTOR_PCB_TX) || g_clMotorSet.GetHomeSensor(m_nUnit, MOTOR_PCB_TX)))
		{
			g_clMotorSet.StopAxis(m_nUnit, MOTOR_PCB_TX);
			Sleep(100);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX�� (-)Limit ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			nRetStep = 11600;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX�� (-)Limit ��ġ �̵� �ð��ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -11400;
			break;
		}
		break;
	case 11600:

		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TY) && (g_clMotorSet.GetNegaSensor(m_nUnit, MOTOR_PCB_TY) || g_clMotorSet.GetHomeSensor(m_nUnit, MOTOR_PCB_TY)))
		{
			g_clMotorSet.StopAxis(m_nUnit, MOTOR_PCB_TY);
			Sleep(100);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TY�� (-)Limit ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 11700;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TY�� (-)Limit ��ġ �̵� �ð��ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -11400;
			break;
		}
		
		break;
	case 11700:
		//! PCB TX, TY�� (-)Limit �̵�

		if (g_clMotorSet.MoveAxisLimit(m_nUnit, MOTOR_PCB_TX, (5 * 1), 0.1, HomeSensor, SIGNAL_HIGH_LEVEL, SLOWDOWN_STOP) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX�� (+)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -11700;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX�� (+)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		nRetStep = 11800;
		break;
	case 11800:
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TX) == false && g_clMotorSet.GetHomeSensor(m_nUnit, MOTOR_PCB_TX))
		{
			g_clMotorSet.StopAxis(m_nUnit, MOTOR_PCB_TX);
			Sleep(100);
			break;
		}
		if ( g_clMotorSet.GetHomeSensor(m_nUnit, MOTOR_PCB_TX))
		{
			g_clMotorSet.StopAxis(m_nUnit, MOTOR_PCB_TX);

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX�� HOME ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 11850;
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			break;
		}
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� HOME ��ġ �̵� �ð��ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -11800;
			break;
		}
		
		break;

	case 11850:
		if (g_clMotorSet.MoveAxisLimit(m_nUnit, MOTOR_PCB_TY, (5 * 1), 0.1, HomeSensor, SIGNAL_HIGH_LEVEL, SLOWDOWN_STOP) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TY�� (+)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -11850;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TY�� (+)Limit ��ġ ���� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		nRetStep = 11900;

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		break;
	case 11900:
		//! PCB TX, TY�� HOME �̵� Ȯ��
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TY) == false && g_clMotorSet.GetHomeSensor(m_nUnit, MOTOR_PCB_TY))
		{
			g_clMotorSet.StopAxis(m_nUnit, MOTOR_PCB_TY);
			Sleep(100);
			break;
		}
		
		
		if (g_clMotorSet.GetHomeSensor(m_nUnit, MOTOR_PCB_TY) )
		{
			g_clMotorSet.StopAxis(m_nUnit, MOTOR_PCB_TY);

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TY�� HOME ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 12000; 
			break;
		}
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� HOME ��ġ �̵� �ð��ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -11900;
			break;
		}
		break; 
	case 12000:

		nRetStep = 12400;
		break;
	case 12400:
		nRetStep = 12500;
		break;

	case 12500:
		//! ��ü ���� ���� ����
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] ��ü ���� �˻� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		for (i = 0; i < MAX_MOTOR_COUNT; i++)
		{
			g_clMotorSet.m_nHomeProcUsing[m_nUnit][i] = 1; 
		}
		nRetStep = 13000;
		break;

	case 13000:
		m_bHomeProc = true;
		for (i = 0; i < MAX_MOTOR_COUNT; i++)
		{
			if (g_clMotorSet.m_nHomeProcUsing[m_nUnit][i] == 1)
			{
				g_clMotorSet.m_bOrgFlag[m_nUnit][i] = false;
				if (g_clMotorSet.StartHomeSearch(m_nUnit, i) == false)
				{
					m_bHomeProc = false;

					_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] ���� ���� ���� ��� ���� [STEP : %d]"), MOTOR_NAME[i], nStep);
					AddLog(szLog, 1, m_nUnit);

					break;
				}
				else 
				{
					// ���� ������ ����
					g_clMotorSet.m_nHomeProcUsing[m_nUnit][i] = 2;
				}
			}
		}

		if (m_bHomeProc == false) {
			nRetStep = -13000; 
		}
		else {
			nRetStep = 14000;
		}
		break;
	case 14000:
		m_bHomeProc = true;
		m_bHomeError = false;
		for (i = 0; i < MAX_MOTOR_COUNT; i++)
		{
			if (g_clMotorSet.m_nHomeProcUsing[m_nUnit][i] == 2) 
			{
				nHomeFlag = g_clMotorSet.IsCompletedHomeSearch(m_nUnit, i);
				// ���� �Ϸ�
				if (nHomeFlag == 1)
				{
					g_clMotorSet.m_bOrgFlag[m_nUnit][i] = true;
				}
				// ���� �˻� ��
				else if (nHomeFlag == 2)
				{
					m_bHomeProc = false;
				}
				// ���� ���� ERROR
				else
				{
					m_bHomeError = true;


					_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] ���� HOME ���� ERROR �߻�[STEP : %d]"), MOTOR_NAME[i], nStep);
					AddLog(szLog, 1, m_nUnit);

					break;
				}
			} 
		}

		if (m_bHomeError == true)
		{
			nRetStep = -13000;
			break;
		}

		if (m_bHomeProc == true)
		{
			nRetStep = 15000;
			break;
		}
		break;

	case 15000:
		/*if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -15000;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� �����ġ �̵� ��� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();*/
		nRetStep = 16000;
		break;
	case 16000:
		//! PCB Z�� ��� ��ġ �̵� Ȯ��
		nRetStep = 18000;
		break;
		//dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_Z];
		//curPos = g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z);// -g_clSysData.m_dOrgDataset[m_nUnit][MOTOR_PCB_Z];
		//if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && (curPos - dPos[0]) < ENCORDER_GAP)
		//{
		//	_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
		//	AddLog(szLog, 0, m_nUnit);
		//	nRetStep = 18000;
		//	break;
		//}

		//if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		//{
		//	_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
		//	AddLog(szLog, 1, m_nUnit, true);

		//	nRetStep = -15000;
		//	break;
		//}
		break;
	case 18000:
		//! ��ü ���� ���� �Ϸ�
		g_pCarAABonderDlg->m_clColorButtonStartingPoint[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonStartingPoint[m_nUnit].Invalidate();
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] ��ü ���� ���� �Ϸ�[STEP : %d]"), nStep); 

		AddLog(szLog, 0, m_nUnit);
		g_ShowMsgPopup(_T("INFO"), _T("[AUTO] ��ü ���� ���� �Ϸ�"), RGB_COLOR_RED);
		nRetStep = 20000;
		break;

	default:
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] ���� ���� �̻� STEP �߻�[STEP : %d]"), nStep);
		AddLog(szLog, 1, m_nUnit, true);
		nRetStep = -10000;
		break;
	}

	return nRetStep;
}


//-----------------------------------------------------------------------------
//
//	EOL �����غ�(20000 ~ 30000)
//
//-----------------------------------------------------------------------------
int CPcbProcess::AutoReadyProcess(int nStep)
{
	TCHAR szLog[SIZE_OF_1K];
	int nRetStep;
	double dPos[4] = { 0.0, 0.0, 0.0, 0.0 };
	double curPos = 0.0;
	CString sMsg = _T("");
	int i = 0;
	nRetStep = nStep;
	g_clTaskWork[m_nUnit].m_bAreaSensorRun = true;	//AutoReadyProcess

	if (g_clDioControl.CurtainDoorCheck(m_nUnit, true) == true)		//AutoReadyProcess
	{
		g_clMotorSet.StopAxisAll(m_nUnit);
		_stprintf_s(szLog, SIZE_OF_1K, _T("[ERROR] ���� ���� �� CURTAIN ����. �Ͻ� ����"));
		nRetStep *= -1;
		g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1008);
		AddLog(szLog, 1, m_nUnit, true);
		return nRetStep;
	}
	switch (nStep)
	{
	case 20000:
		if (g_clMesCommunication[m_nUnit].m_dEqupControlState[1] == eOnlineRemote &&
			g_clMesCommunication[m_nUnit].m_dProcessState[0] != g_clMesCommunication[m_nUnit].m_dProcessState[1])
		{
			g_clMesCommunication[m_nUnit].m_dProcessState[0] = g_clMesCommunication[m_nUnit].m_dProcessState[1];
			g_clMesCommunication[m_nUnit].m_dProcessState[1] = eIDLE;
			g_clMesCommunication[m_nUnit].m_uAlarmList.clear();

			_stprintf_s(szLog, SIZE_OF_1K, _T("[READY] (Idle)Process State Change Report [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clTaskWork[0].bIdleTimeExceed = false;		//init
			g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(PROCESS_STATE_CHANGED_REPORT_10401);	//SEND S6F11


			CTime cTime = CTime::GetCurrentTime();
			CString strData;
			strData.Format(_T("%02d%02d%02d%02d%02d%02d"),
				cTime.GetYear(),
				cTime.GetMonth(),
				cTime.GetDay(),
				cTime.GetHour(),
				cTime.GetMinute(),
				cTime.GetSecond());
			_stprintf_s(g_clTaskWork[m_nUnit].m_szIdleStartTime, SIZE_OF_100BYTE, _T("%s"), strData);		//Auto_M_PCBLoading
			g_pCarAABonderDlg->KillTimer(WM_IDLE_REASON_TIMER);

			if (g_clMesCommunication[m_nUnit].IdleSetTimeInterval < 1)
			{
				g_clMesCommunication[m_nUnit].IdleSetTimeInterval = 5;	//min  1min = 60000
			}
			g_pCarAABonderDlg->SetTimer(WM_IDLE_REASON_TIMER, g_clMesCommunication[m_nUnit].IdleSetTimeInterval * 60000, NULL);		//30000 Step
			strData.Empty();
		}
		nRetStep = 20100;
		break;
	case 20100:
		nRetStep = 20150;
		break;
	case 20150:
		//WhiteOcLightControl[m_nUnit].DPS_Light_OnOffLevel(LIGHT_OC_WHITE_CH1, 0, 0);

		//_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] �̹����� OFF [STEP : %d]"), nStep);
		//AddLog(szLog, 0, m_nUnit);
		nRetStep = 20200;
		break;
	case 20200:
		if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS) == false)
		{
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1036);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -20200;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� �����ġ �̵� ��� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 20300;
		break;

	case 20300:
		//! PCB Z�� ��� ��ġ �̵� Ȯ��
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_Z];
		curPos = g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z);		// -g_clSysData.m_dOrgDataset[m_nUnit][MOTOR_PCB_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && (curPos - dPos[0]) < ENCORDER_GAP)
		{

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 20400;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1036);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -20200;
			break;
		}
		break;

	case 20400:
		if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, WAIT_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� WAIT_POS �̵� ��� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -20400;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� WAIT_POS �̵� ��� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 20500;
		break;

	case 20500:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_TX];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_TY];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TX) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TX) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TY) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TY) - dPos[1]) < ENCORDER_GAP)))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 20600;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� WAIT_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -20650;
			break;
		}
		break;

	case 20600:
		if (g_clDioControl.PcbSensorCheck(m_nUnit) == true)
		{
			if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//���� ���� ���� Ȯ��	Ready
			{
				g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1038);
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO READY] PCB Vacuum Ȯ�� ���� [STEP : %d]"), nStep);
				AddLog(szLog, 1, m_nUnit, true);

				nRetStep = -20600;
				break;
			}
		}
		if (g_clMotorSet.MovePcbYMotor(m_nUnit, WAIT_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO READY] PCB Y�� �����ġ �̵� ��� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -20600;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO READY] PCB Y�� �����ġ �̵� ��� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 20640;
		break;

	case 20640:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_Y];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Y) && (g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Y) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO READY] PCB Y�� �����ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 20700;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO READY] PCB Y�� �����ġ �̵� �ð��ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -20600;
			break;
		}
		break;
	case 20700:
		if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, WAIT_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO READY] PCB X,Y,T�� �����ġ �̵� ��� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -21300;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO READY] PCB X,Y,T�� �����ġ �̵� ��� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 21300;
		break;

	case 21300:
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] CCD CLOSE [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clLaonGrabberWrapper[m_nUnit].CloseDevice(); 
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 21500;
		break;
	case 21500:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_X];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_Y];
		dPos[2] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_TH];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_X) && (g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_X) - dPos[0]) < ENCORDER_GAP) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Y) && (g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Y) - dPos[1]) < ENCORDER_GAP) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TH) && (g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TH) - dPos[2]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO READY] PCB X,Y,T�� �����ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 21600;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO READY] PCB X,Y,T�� �����ġ �̵� �ð��ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -21300;
			break;
		}
		break;
	
	case 21600: 
		nRetStep = 21770;
		break;
	case 21770:
		nRetStep = 21800;
		break;
	case 21800:

		nRetStep = 21850;
		break;
	case 21850:
		nRetStep = 22000;
		break;
	case 22000:
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > 300)
		{
			g_clTaskWork[m_nUnit].m_IoRetry = 0;
			nRetStep = 22500;
		}
		
		break;
	case 22500:
		if (g_clDioControl.PcbSensorCheck(m_nUnit) == false)
		{
			//��ǰ ���� 
			//Ż�� �߰�?
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB SOCKET ��ǰ ��Ȯ�� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clDioControl.PcbVacuum(m_nUnit, false);

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB SOCKET Vacuum Ż�� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
		}
		else
		{
			//��ǰ o
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB SOCKET ��ǰ Ȯ�� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
		}
		
		nRetStep = 23000;
		break;
	case 23000:
		g_clVision.ClearOverlay(m_nUnit, VIDEO_CAM);
		g_clVision.DrawOverlayAll(m_nUnit, VIDEO_CAM);

		
		nRetStep = 23500;
		break;
	case 23500:
		for (i = 0; i < 20; i++)
		{
			g_clTaskWork[m_nUnit].m_bOutputCheck[i] = true;	//READY �ʱ�ȭ
		}
		nRetStep = 24000;
		break;
	case 24000:

		g_clVision.ClearOverlay(m_nUnit);
		g_clVision.DrawOverlayAll(m_nUnit);
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount(); 
		nRetStep = 28000;
		break;
	case 28000:
		//��Ʈ
		TopChartControl[m_nUnit + 1].dpctrlLedVolume(LIGHT_CHART_CH_1, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_TOP_CHART_1]);
		Sleep(10);
		LightLeftChartControl[m_nUnit + 1].dpctrlLedVolume(LIGHT_CHART_CH_1, g_clModelData[m_nUnit].m_nLight[LEFT_CHART_CH_1]);
		Sleep(10);
		LightRightChartControl[m_nUnit + 1].dpctrlLedVolume(LIGHT_CHART_CH_1, g_clModelData[m_nUnit].m_nLight[RIGHT_CHART_CH_1]);
		Sleep(10);
		
		//align
		BackDuLightControl[m_nUnit].ctrlLedVolume(LIGHT_BD_ALIGN_CH1, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_ALIGN_SENSOR]);
		Sleep(10);
		//�̹�����
		BackDuLightControl[m_nUnit].ctrlLedVolume(LIGHT_BD_OC_CH2, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_OC_WHITE1]);
		Sleep(10);

		nRetStep = 29000;
		break;
	case 29000:
		g_clDioControl.SetTowerLamp(LAMP_YELLOW, true);
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_READY;
		//
		//�����غ�� �ʱ�ȭ �߰�
		g_clTaskWork[m_nUnit].m_nEmission = 0;
		g_pCarAABonderDlg->ShowOkNgState(m_nUnit, g_clTaskWork[m_nUnit].m_nEmission);
		g_clTaskWork[m_nUnit].SaveData();
		//
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoRun[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoPause[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 0;

		g_pCarAABonderDlg->m_clColorButtonAutoRun[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoPause[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] �����غ� �Ϸ� [STEP : %d]"), nStep);
		g_ShowMsgPopup(_T("INFO"), _T("[AUTO] �����غ� �Ϸ�"), RGB_COLOR_RED, 1);

		AddLog(szLog, 0, m_nUnit);
		nRetStep = 30000;
		break;
	default:
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] �����غ� STEP �̻� [STEP : %d]"), nStep);
		AddLog(szLog, 1, m_nUnit, true);
		nRetStep = -20000;
		break;
	}
	return nRetStep;
}


//-----------------------------------------------------------------------------
//
//	EODL PCB �ε�(30000 ~ 40000)
//
//-----------------------------------------------------------------------------
int CPcbProcess::Auto_M_PCBLoading(int nStep)
{
	TCHAR szLog[SIZE_OF_1K];
	double dPos[3] = { 0.0, 0.0, 0.0 };
	CString sMsg = _T("");
	int nRetStep;
	double dDelay = 0.0;
	bool bRtn = false;
	nRetStep = nStep;

	switch (nStep)
	{
	case 30000:
		if (g_pCarAABonderDlg->m_clUbiGemDlg.bConnected() == false)
		{
			sMsg.Format(_T("MES DISCONNECTED"));
			AddLog(sMsg, 1, m_nUnit, true);
			nRetStep = -30000;
			break;
		}
		if (g_clMesCommunication[m_nUnit].m_dEqupControlState[1] == eOnlineRemote &&
			g_clMesCommunication[m_nUnit].m_dProcessState[0] != g_clMesCommunication[m_nUnit].m_dProcessState[1])
		{
			g_clMesCommunication[m_nUnit].m_dProcessState[0] = g_clMesCommunication[m_nUnit].m_dProcessState[1];
			g_clMesCommunication[m_nUnit].m_dProcessState[1] = eIDLE;
			g_clMesCommunication[m_nUnit].m_uAlarmList.clear();

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] (Idle)Process State Change Report [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clTaskWork[0].bIdleTimeExceed = false;		//init
			g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(PROCESS_STATE_CHANGED_REPORT_10401);	//SEND S6F11


			CTime cTime = CTime::GetCurrentTime();
			CString strData;
			strData.Format(_T("%02d%02d%02d%02d%02d%02d"),
				cTime.GetYear(),
				cTime.GetMonth(),
				cTime.GetDay(),
				cTime.GetHour(),
				cTime.GetMinute(),
				cTime.GetSecond());
			_stprintf_s(g_clTaskWork[m_nUnit].m_szIdleStartTime, SIZE_OF_100BYTE, _T("%s"), strData);		//Auto_M_PCBLoading
			g_pCarAABonderDlg->KillTimer(WM_IDLE_REASON_TIMER);

			if (g_clMesCommunication[m_nUnit].IdleSetTimeInterval < 1)
			{
				g_clMesCommunication[m_nUnit].IdleSetTimeInterval = 5;	//min  1min = 60000
			}
			g_pCarAABonderDlg->SetTimer(WM_IDLE_REASON_TIMER, g_clMesCommunication[m_nUnit].IdleSetTimeInterval * 60000, NULL);		//30000 Step
			strData.Empty();
		}
		else
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Process Control State:%d [STEP : %d]"), g_clMesCommunication[m_nUnit].m_dEqupControlState[1],  nStep);
			AddLog(szLog, 0, m_nUnit);
		}
		nRetStep = 30010;
		break;

	case 30010:

		mOcLightChannel = 1;	//channel init

		g_clTaskWork[m_nUnit].m_ContactCount = 0;		//step 30000
		g_clTaskWork[m_nUnit].m_nCcdCount = 0;			//step 30000

		g_clTaskWork[m_nUnit].m_nEmissionRun = false;
		g_clTaskWork[m_nUnit].m_bPcbInterLock = true;
		if (g_clModelData[m_nUnit].m_nPinStopUse == 1)
		{
			if (g_clTaskWork[m_nUnit].m_nUsePinCount > g_clSysData.m_nMaxPinCount)//g_clModelData[m_nUnit].m_nSensorCnt)
			{
				g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1041);
				sMsg.Format(_T("Socket PIN %d(Spec: %d) \nReset after replacement"), g_clTaskWork[m_nUnit].m_nUsePinCount, g_clSysData.m_nMaxPinCount);// g_clModelData[m_nUnit].m_nSensorCnt);
				AddLog(sMsg, 1, m_nUnit, true);
				nRetStep = -30000;
				break;
			}
		}
		if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
		{
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1042);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� ��� ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� ��� ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		nRetStep = 30020;
		mLightRetry = 0;
		break;
	case 30020:
		nRetStep = 30030;
		break;
	case 30030:

		nRetStep = 30050;
		break;
	case 30050:
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][PCB] PCB X,Y,T�� ���� ��ġ �̵� ��� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, SUPPLY_POS) == false)
		{
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1043);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][PCB] PCB X,Y,T�� ���� ��ġ �̵� ��� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30050;
			break;
		}

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 30070;
		break;
	case 30070:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[SUPPLY_POS].dPos[MOTOR_PCB_X];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[SUPPLY_POS].dPos[MOTOR_PCB_Y];
		dPos[2] = g_clModelData[m_nUnit].m_stTeachData[SUPPLY_POS].dPos[MOTOR_PCB_TH];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_X) && (g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_X) - dPos[0]) < ENCORDER_GAP) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Y) && (g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Y) - dPos[1]) < ENCORDER_GAP) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TH) && (g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TH) - dPos[2]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB X,Y,T�� SUPPLY_POS �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 30075;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB X,Y,T�� SUPPLY_POS �̵� �ð��ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30050;
			break; 
		}
		break;
	case 30075:
		if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, SUPPLY_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� SUPPLY_POS �̵� ��� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30075;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� SUPPLY_POS �̵� ��� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 30080;
		break;

	case 30080:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[SUPPLY_POS].dPos[MOTOR_PCB_TX];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[SUPPLY_POS].dPos[MOTOR_PCB_TY];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TX) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TX) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TY) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TY) - dPos[1]) < ENCORDER_GAP)))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� SUPPLY_POS ��ġ �̵� �Ϸ� [STEP : %d"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 30090;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� SUPPLY_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30075;
			break;
		}
		break;
	case 30090:

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� ���� ��ġ �̵� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		if (g_clMotorSet.MovePcbZMotor(m_nUnit, SUPPLY_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� ���� ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30090;
			break;
		}
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 30110;
		break;
	case 30110: 
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[SUPPLY_POS].dPos[MOTOR_PCB_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� SUPPLY_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 30115;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� SUPPLY_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30090;
			break;
		}

		break;
	case 30115:
		if (g_clDioControl.PcbSensorCheck(m_nUnit) == false)
		{
			g_clDioControl.PcbVacuum(m_nUnit, true);
		}

		g_clDioControl.Start_Button_LedOn(m_nUnit, true, false);
		nRetStep = 30120;
		break;

	case 30120:		//<--step ��ȣ �����
		if (g_clDioControl.StartBbCheck(m_nUnit) == true)		//��Ÿũ ��ư �����Ǹ� Start
		{
			nRetStep = 30125;

			g_clDioControl.Start_Button_LedOn(m_nUnit, false , false);

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] START PB PRESS. [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
		}
		break;
	case 30125:
		if (g_pCarAABonderDlg->LgitLicenseCheck() == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LGIT License �ν� ���� [STEP : %d]"), nStep);

			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30125;
			break;
		}

		nRetStep = 30130;
		break;
	case 30130:
		
		if (g_clDioControl.PcbSensorCheck(m_nUnit) == false)
		{
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1046);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB ��ǰ ���� ���� [STEP : %d]"), nStep);

			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30120;
			break;
		}
		else
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB ��ǰ ���� Ȯ��. [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 30150;
		}
		
		break;
	case 30150:
		if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//���� ���� ���� Ȯ��	start
		{
			g_clDioControl.PcbVacuum(m_nUnit, true);

			if (g_ShowMsgModal(_T("Ȯ��"), _T("[AUTO] ���� ���� Ȯ���� �������ּ���"), RGB_COLOR_RED) == false)
			{
				nRetStep = -30125;
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Vacuum Ȯ�� ���� [STEP : %d]"), nStep);
				AddLog(szLog, 1, m_nUnit, true);
				break;
			}
			else
			{
				nRetStep = 30200;
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Vacuum Ȯ��. [STEP : %d]"), nStep);
				AddLog(szLog, 0, m_nUnit);
			}
			break;
		}
		else
		{
			g_clTaskWork[m_nUnit].m_bPcbSocketIF[PCB_BCR] = true;
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Vacuum Ȯ�� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			//���� ���� Ȯ��
			nRetStep = 30200;
		}
		
		

		
		break;
	case 30200:
		BackDuLightControl[m_nUnit].ctrlLedVolume(LIGHT_BD_ALIGN_CH1, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_ALIGN_SENSOR]);
		nRetStep = 30400;
		break;

	case 30400:
		MbufClear(g_clVision.MilDefectOverlayImage[m_nUnit], (MIL_DOUBLE)g_clVision.m_nMilDefectTransparent[m_nUnit]);
		MbufClear(g_clVision.MilDefectImage[m_nUnit], 0);
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 30500;
		break;

	case 30500:
		nRunOnlineControlState = false;
		nRunTimeOutSec = g_clMesCommunication[m_nUnit].ConversationTimeoutCount * 1000;
		if (nRunTimeOutSec < 1)
		{
			nRunTimeOutSec = 60 * 1000;
		}
		if (g_clMesCommunication[m_nUnit].m_dEqupControlState[1] == eOnlineRemote)
		{
			nRunOnlineControlState = true;
		}
		if (nRunOnlineControlState == false)
		{
			//Offline �̸� ���� Skip
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Equipment Offline State Object Id Pass [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 32750;	//Jump Setp
			break;
		}
		nRetStep = 30600;
		break;
	case 30600:
		//OBJECT ID REPORT
		g_clTaskWork[m_nUnit].bRecv_Lgit_Pp_select = -1;
		g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start = -1;
		g_pCarAABonderDlg->KillTimer(WM_IDLE_REASON_TIMER);		//OBJECT ID REPORT start
		//
		g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(OBJECT_ID_REPORT_10701);
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Object Id Report Send [STEP : %d]"), nStep);	//-----------------------OBJECT ID REPORT start
		AddLog(szLog, 0, m_nUnit);
		nRetStep = 30700;

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		break;
	case 30700:	//ok
		if (g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start == 0) 
		{
			//g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start = -1;
			//Recv LGIT_LOT_START
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot Id Start Recv [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 31400;	//Jump Step
		}
		else if (g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start == 1)
		{
			g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start = -1;
			//Recv LGIT_LOT_ID_FAIL
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot Id Fail Recv [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			sMsg.Empty();

			//std::vector<RcmdList_T2> resultsT2;
			//resultsT2 = g_clReportData.T2_FindChildList(g_clReportData.rLot_Id_Fail.parameters);

			//if (resultsT2.size() > 0)
			//{
			//	for (int i = 0; i < resultsT2[0].rVec.size(); i++)
			//	{
			//		if (resultsT2[0].rVec[i].cpName == "MODULEID")
			//		{
			//			//g_pCarAABonderDlg->m_clMessageLot.setLotID(_T("LOT ID"), resultsT2[0].rVec[i].cepVal);		//���� lot id? , moduleid?
			//			sMsg.Format(_T("LOT ID:%s"), resultsT2[0].rVec[i].cepVal);// g_clModelData[m_nUnit].m_nSensorCnt);

			//			break;
			//		}
			//	}
			//}
			if (g_clReportData.vLotIdFail.size() > 0)
			{
				for (int i = 0; i < g_clReportData.vLotIdFail[0].children.size(); i++)
				{
					if (g_clReportData.vLotIdFail[0].children[i].name == "MODULEID")
					{
						sMsg.Format(_T("LOT ID:%s"), g_clReportData.vLotIdFail[0].children[i].value);
						break;
					}
				}
			}
			//
			//_stprintf_s(szLog, SIZE_OF_1K, _T("[RCMD L%d]Name:%s, Val:%s"), i + 1, g_clReportData.vLotIdFail[0].children[i].name, g_clReportData.vLotIdFail[0].children[i].value);
			//
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(2000);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LGIT_LOT_ID_FAIL]\n%s \nCode :%s\nText:%s\n��õ� �Ͻðڽ��ϱ�?"), sMsg,
				g_clMesCommunication[m_nUnit].m_sErcmdCode, g_clMesCommunication[m_nUnit].m_sErcmdText);

			if (g_ShowMsgModal(_T("[INFO]"), szLog, RGB_COLOR_BLUE, _T("RETRY"), _T("PAUSE")) == true)
			{
				g_clMesCommunication[m_nUnit].m_uAlarmList.clear();
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot ID Fail Retry [STEP : %d]"), nStep);
				AddLog(szLog, 0, m_nUnit);
				nRetStep = 30600;
			}
			else
			{
				nRetStep = -30600;
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO](%s) LOT id Cancel. by Host [STEP : %d]"), g_clTaskWork[m_nUnit].m_szChipID, nStep);
				AddLog(szLog, 1, m_nUnit, true);
				break;
			}

		}
		else if (g_clTaskWork[m_nUnit].bRecv_Lgit_Pp_select == 0)//LOT START �� �ü����ִ�  ��
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lgit PP Select Recv OK [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			g_clTaskWork[m_nUnit].bRecv_Lgit_Pp_select = -1;
			nRetStep = 30750;
		}
		else if (g_clTaskWork[m_nUnit].bRecv_Lgit_Pp_select == 1) 
		{
			//Recipe ID Check
			//
			//
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(2001);
			g_clDioControl.SetBuzzer(true, BUZZER_ALARM);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] ������� RECIPE (%s) �� �ٸ��ϴ�.\n��õ� �Ͻðڽ��ϱ�?"), g_clMesCommunication[m_nUnit].m_sRecipeId, g_clMesCommunication[m_nUnit].m_sMesPPID);
			if (g_ShowMsgModal(_T("[INFO]"), szLog, RGB_COLOR_BLUE, _T("RETRY"), _T("PAUSE")) == true)
			{
				g_clMesCommunication[m_nUnit].m_uAlarmList.clear();
				g_clDioControl.SetBuzzer(true, BUZZER_OFF);
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Object Id Report Retry [STEP : %d]"), nStep);
				AddLog(szLog, 0, m_nUnit);
				nRetStep = 30600;
			}
			else
			{
				nRetStep = -30600;
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] RECIPE ID Ȯ�� ���� [STEP : %d]"), nStep);
				AddLog(szLog, 1, m_nUnit, true);
				break;
			}
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > nRunTimeOutSec)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LGIT PP SELECT Ct TimeOut [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			g_pCarAABonderDlg->m_clUbiGemDlg.cTTimeOutSendFn(_T("S06F12"), _T("10701"));
			nRetStep = -30600;
			break;
		}
		
		break;
	case 30750:
		
		g_clMesCommunication[m_nUnit].m_dProcessState[0] = g_clMesCommunication[m_nUnit].m_dProcessState[1];
		g_clMesCommunication[m_nUnit].m_dProcessState[1] = eSETUP;
		g_clMesCommunication[m_nUnit].m_uAlarmList.clear();

		g_clTaskWork[m_nUnit].bRecv_S6F12_Process_State_Change = -1;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] (Setup)Process State Change Report [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);


		g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(PROCESS_STATE_CHANGED_REPORT_10401);	//SEND S6F11
																								//Event = Process State Change Report ("SETUP");
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 30800;
		
		break;
	case 30800:
		if (g_clTaskWork[m_nUnit].bRecv_S6F12_Process_State_Change == 0)	//SETUP
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] (Setup)Process State Change Send Acknowledge [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			g_clTaskWork[m_nUnit].bRecv_S6F12_Process_State_Change = -1;
			//Recipe Setup Completion
			//SV:Recipe ID Set

			g_clMesCommunication[m_nUnit].m_dProcessState[0] = g_clMesCommunication[m_nUnit].m_dProcessState[1];
			g_clMesCommunication[m_nUnit].m_dProcessState[1] = eREADY;

			g_clMesCommunication[m_nUnit].m_uAlarmList.clear();
			
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] (Ready)Process State Change Report [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(PROCESS_STATE_CHANGED_REPORT_10401); //SEND S6F11
			//S6F11 Send

			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			nRetStep = 30900;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > nRunTimeOutSec)
		{
			//g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(CT_TIMEOUT_REPORT_11002); //SEND S6F11
			g_pCarAABonderDlg->m_clUbiGemDlg.cTTimeOutSendFn(_T("S06F12"), _T("10401"));
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] (Setup)Process State Change Ct TimeOut [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30600;	//OBJECT ID REPORT Step
			break;
		}
		
		
		break;
	case 30900:
		if (g_clTaskWork[m_nUnit].bRecv_S6F12_Process_State_Change == 0)	//READY
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] (Ready)Process State Change Send Acknowledge [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			g_clTaskWork[m_nUnit].bRecv_S6F12_Process_State_Change = -1;
			g_clTaskWork[m_nUnit].bRecv_S6F12_PP_Selected = -1;
			g_clTaskWork[m_nUnit].bRecv_S7F25_Formatted_Process_Program = -1;		//<--�̸� �ʱ�ȭ
			g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start = -1;		//�̸� �ʱ�ȭ

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PP-Selected Report [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(PP_SELECTED_REPORT_10702);//SEND S6F11
			//Event - PP-Selected Report


			//�� ������ �� �� �ִ�.
			//1..���⼭ LGIT_LOT_START ���ų� Jmp
			//2..LGIT_LOT_ID_FAIL Lot ID Cancel by Host �� �� �ֵ�.
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			nRetStep = 31000;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > nRunTimeOutSec)
		{
			//g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(CT_TIMEOUT_REPORT_11002); //SEND S6F11
			g_pCarAABonderDlg->m_clUbiGemDlg.cTTimeOutSendFn(_T("S06F12"), _T("10401"));
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] (Ready)Process State Change Ct TimeOut [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30600;	//OBJECT ID REPORT Step
			break;
		}
		
		break;
	case 31000:
		
		if (g_clTaskWork[m_nUnit].bRecv_S6F12_PP_Selected == 0)		//S6F12 ���
		{
			g_clTaskWork[m_nUnit].bRecv_S6F12_PP_Selected = -1;
			//Recv PP-Select Report
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PP-Selected Send Acknowledge [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 31050;

			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		}
		
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > nRunTimeOutSec)
		{
			//g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(CT_TIMEOUT_REPORT_11002); //SEND S6F11
			g_pCarAABonderDlg->m_clUbiGemDlg.cTTimeOutSendFn(_T("S06F12"), _T("10702"));
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PP-Select Report Ct TimeOut [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30600;	//OBJECT ID REPORT Step
			break;
		}

		
		break;
	case 31050:
		//
		////Recipe Parameter Validation EQP ���ϸ� �ٷ� Lot Start �´�.
		//
		nRetStep = 31100;
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		
		break;
	case 31100:
		if (g_clTaskWork[m_nUnit].bRecv_S7F25_Formatted_Process_Program == 0)		//Ubisam ���� ������ 0���� ����
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Formatted Process Program Request [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			//���� ��� S7F25 - Formatted Process Program Request
			g_clTaskWork[m_nUnit].bRecv_S2F49_PP_UpLoad_Confirm = -1;
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			nRetStep = 31200;
		}
		else if (g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start == 0)
		{
			g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start = -1;
			//Recv LGIT_LOT_START
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot Id Start Recv [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 31400;	//Jump Step
		}
		else if (g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start == 1)
		{
			g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start = -1;
			//Recv LGIT_LOT_ID_FAIL
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot Id Fail Recv [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			sMsg.Empty();

			//std::vector<RcmdList_T2> resultsT2;
			//resultsT2 = g_clReportData.T2_FindChildList(g_clReportData.rLot_Id_Fail.parameters);
			//if (resultsT2.size() > 0)
			//{
			//	for (int i = 0; i < resultsT2[0].rVec.size(); i++)
			//	{
			//		if (resultsT2[0].rVec[i].cpName == "MODULEID")
			//		{
			//			sMsg.Format(_T("LOT ID:%s"), resultsT2[0].rVec[i].cepVal);// g_clModelData[m_nUnit].m_nSensorCnt);
			//			break;
			//		}
			//	}
			//}
			if (g_clReportData.vLotIdFail.size() > 0)
			{
				for (int i = 0; i < g_clReportData.vLotIdFail[0].children.size(); i++)
				{
					if (g_clReportData.vLotIdFail[0].children[i].name == "MODULEID")
					{
						sMsg.Format(_T("LOT ID:%s"), g_clReportData.vLotIdFail[0].children[i].value);
						break;
					}
				}
			}


			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(2002);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LGIT_LOT_ID_FAIL]\n%s \nCode :%s\nText:%s\n��õ� �Ͻðڽ��ϱ�?"), sMsg,
				g_clMesCommunication[m_nUnit].m_sErcmdCode, g_clMesCommunication[m_nUnit].m_sErcmdText);

			if (g_ShowMsgModal(_T("[INFO]"), szLog, RGB_COLOR_BLUE, _T("RETRY"), _T("PAUSE")) == true)
			{
				g_clMesCommunication[m_nUnit].m_uAlarmList.clear();
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot ID Fail Retry [STEP : %d]"), nStep);
				AddLog(szLog, 0, m_nUnit);
				nRetStep = 30600;
			}
			else
			{
				nRetStep = -30600;
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO](%s) LOT id Cancel. by Host [STEP : %d]"), g_clTaskWork[m_nUnit].m_szChipID, nStep);
				AddLog(szLog, 1, m_nUnit, true);
				break;
			}

		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > nRunTimeOutSec)
		{
			//g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(CT_TIMEOUT_REPORT_11002); //SEND S6F11
			g_pCarAABonderDlg->m_clUbiGemDlg.cTTimeOutSendFn(_T("S07F25"), _T("10702"));//<<<���� �³�
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Formatted Process Program Ct TimeOut [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30600;	//OBJECT ID REPORT Step
			break;
		}
		break;
	case 31200:
		if (g_clTaskWork[m_nUnit].bRecv_S2F49_PP_UpLoad_Confirm == 0)	//LGIT_PP_UPLOAD_CONFIRM
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PP Upload Confirm Recv [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			//LGIT_PP_UPLOAD_CONFIRM ���� S2F50������ , ���� ����
			g_clTaskWork[m_nUnit].bRecv_S2F49_PP_UpLoad_Confirm = -1;
			g_clTaskWork[m_nUnit].bRecv_S6F12_PP_UpLoad_Completed = -1;
			g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start = -1;		//�̸� �ʱ�ȭ
			

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PP Upload Completed Report [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(PP_UPLOAD_COMPLETED_REPORT_10703);//SEND S6F11
			//Event - PP Upload Completed Report
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			nRetStep = 31300;
		}
		else if (g_clTaskWork[m_nUnit].bRecv_S2F49_PP_UpLoad_Confirm == 1)	//LGIT_PP_UPLOAD_FAIL Ȯ���ʿ� 250112
		{
			//LGIT_PP_UPLOAD_FAIL ���� S2F50������,  NG (Recipe Body Cancel by Host)
			g_clTaskWork[m_nUnit].bRecv_S2F49_PP_UpLoad_Confirm = -1;

			_stprintf_s(szLog, SIZE_OF_1K, _T("RECIPE ID:%s \nLGIT_PP_UPLOAD_FAIL\nCode :%s\nText:%s\n��õ� �Ͻðڽ��ϱ�?"), 
				g_clMesCommunication[m_nUnit].m_sRecipeId, g_clMesCommunication[m_nUnit].m_sErcmdCode, g_clMesCommunication[m_nUnit].m_sErcmdText);
			if (g_ShowMsgModal(_T("[INFO]"), szLog, RGB_COLOR_BLUE, _T("RETRY"), _T("PAUSE")) == true)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PP Upload Fail Retry [STEP : %d]"), nStep);
				AddLog(szLog, 0, m_nUnit);
				nRetStep = 30600;
			}
			else
			{
				nRetStep = -30600;
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO](%s) PP Upload Fail Pause [STEP : %d]"), g_clTaskWork[m_nUnit].m_szChipID, nStep);
				AddLog(szLog, 1, m_nUnit, true);
				break;
			}
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > nRunTimeOutSec)
		{
			//g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(CT_TIMEOUT_REPORT_11002); //SEND S6F11
			g_pCarAABonderDlg->m_clUbiGemDlg.cTTimeOutSendFn(_T("S02F49"), _T("10703"));
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PP Upload Confirm Ct TimeOut [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30600;	//OBJECT ID REPORT Step
			break;
		}
		break;
	case 31300:
		if (g_clTaskWork[m_nUnit].bRecv_S6F12_PP_UpLoad_Completed == 0)
		{
			g_clTaskWork[m_nUnit].bRecv_S6F12_PP_UpLoad_Completed = -1;
			//Recv S6F12
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PP Upload Completed Send acknowledge [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 31400;
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > nRunTimeOutSec)
		{
			//g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(CT_TIMEOUT_REPORT_11002); //SEND S6F11
			g_pCarAABonderDlg->m_clUbiGemDlg.cTTimeOutSendFn(_T("S06F12"), _T("10703"));
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PP Upload Completed Ct TimeOut [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30600;	//OBJECT ID REPORT Step
			break;
		}
		break;
	case 31400:

		if (g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start == 0)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lgit Lot Start Send acknowledge [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start = -1;
			g_clTaskWork[m_nUnit].bRecv_S6F12_Process_State_Change = -1;
			//Recv LGIT_LOT_START


			//Lot Processing Start ????

			g_clMesCommunication[m_nUnit].m_dProcessState[0] = g_clMesCommunication[m_nUnit].m_dProcessState[1];
			g_clMesCommunication[m_nUnit].m_dProcessState[1] = eEXECUTING;

			g_clMesCommunication[m_nUnit].m_uAlarmList.clear();
			g_clMesCommunication[m_nUnit].m_dLotProcessingState = eWait;

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] (Executing)Process State Change Report [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(PROCESS_STATE_CHANGED_REPORT_10401); //SEND S6F11

			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			nRetStep = 31500;
		}
		else if (g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start == 1)	//Ȯ���ʿ�
		{
			//Recv LGIT_LOT_ID_FAIL
			//NG - Lot ID Cancel by Host

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot Id Fail Recv [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			sMsg.Empty();

			/*std::vector<RcmdList_T2> resultsT2;
			resultsT2 = g_clReportData.T2_FindChildList(g_clReportData.rLot_Id_Fail.parameters);
			if (resultsT2.size() > 0)
			{
				for (int i = 0; i < resultsT2[0].rVec.size(); i++)
				{
					if (resultsT2[0].rVec[i].cpName == "MODULEID")
					{
						sMsg.Format(_T("LOT ID:%s"), resultsT2[0].rVec[i].cepVal);
						break;
					}
				}
			}*/

			if (g_clReportData.vLotIdFail.size() > 0)
			{
				for (int i = 0; i < g_clReportData.vLotIdFail[0].children.size(); i++)
				{
					if (g_clReportData.vLotIdFail[0].children[i].name == "MODULEID")
					{
						sMsg.Format(_T("LOT ID:%s"), g_clReportData.vLotIdFail[0].children[i].value);
						break;
					}
				}
			}



			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(2003);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LGIT_LOT_ID_FAIL]\n%s \nCode :%s\nText:%s\n��õ� �Ͻðڽ��ϱ�?"), sMsg,
				g_clMesCommunication[m_nUnit].m_sErcmdCode, g_clMesCommunication[m_nUnit].m_sErcmdText);

			if (g_ShowMsgModal(_T("[INFO]"), szLog, RGB_COLOR_BLUE, _T("RETRY"), _T("PAUSE")) == true)
			{
				g_clMesCommunication[m_nUnit].m_uAlarmList.clear();
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot ID Fail Retry [STEP : %d]"), nStep);
				AddLog(szLog, 0, m_nUnit);
				nRetStep = 30600;
			}
			else
			{
				nRetStep = -30600;
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO](%s) LOT id Cancel. by Host [STEP : %d]"), g_clTaskWork[m_nUnit].m_szChipID, nStep);
				AddLog(szLog, 1, m_nUnit, true);
				break;
			}
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > nRunTimeOutSec)
		{
			//g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(CT_TIMEOUT_REPORT_11002); //SEND S6F11
			g_pCarAABonderDlg->m_clUbiGemDlg.cTTimeOutSendFn(_T("S02F49"), _T("10704"));
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot Start Ct TimeOut [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30600;	//OBJECT ID REPORT Step
			break;
		}
		//�� ������ �� �� �ִ�.
		//1..���⼭ LGIT_LOT_START ���ų� Jmp
		//2..LGIT_LOT_ID_FAIL Lot ID Cancel by Host �� �� �ֵ�.
		break;
	case 31500:
		if (g_clTaskWork[m_nUnit].bRecv_S6F12_Process_State_Change == 0)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] (Executing) Process State Change Acknowledge [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clTaskWork[m_nUnit].bRecv_S6F12_Process_State_Change = -1;
			g_clTaskWork[m_nUnit].bRecv_S6F12_Lot_Processing_Started = -1;
			g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start = -1;		
			nLotProcessingComplete_ACK = -1;


			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot Processing Started Report [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(LOT_PROCESSING_STARTED_REPORT_10704);//SEND S6F11 Lot Processing Started Report
			nRetStep = 31600;
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > nRunTimeOutSec)
		{
			//g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(CT_TIMEOUT_REPORT_11002); //SEND S6F11
			g_pCarAABonderDlg->m_clUbiGemDlg.cTTimeOutSendFn(_T("S06F12"), _T("10401"));
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] (Executing) Process State Change Ct TimeOut [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30600;	//OBJECT ID REPORT Step
			break;
		}
		break;
	case 31600:
		

		if (g_clTaskWork[m_nUnit].bRecv_S6F12_Lot_Processing_Started == 0)	//ack  0�ϴ븸 ��ǰ �����ؾߵȴ�.
		{
			nLotProcessingComplete_ACK = g_clTaskWork[m_nUnit].bRecv_S6F12_Lot_Processing_Started;

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot Processing Started Acknowledge,Ack:%d [STEP : %d]"), nLotProcessingComplete_ACK, nStep);
			AddLog(szLog, 0, m_nUnit);
			//ack 0 Ȯ���ϰ� �����ϸ�Ǵ���?
			//�ƴϸ� LGIT_LOT_ID_FAIL �� �� �� �ִ��� Ȯ�� �ʿ�
			nRetStep = 31700;
		}
		else if (g_clTaskWork[m_nUnit].bRecv_S6F12_Lot_Processing_Started == 1)	//nack 1�� �ƴҼ����ִ�.
		{
			//ack�� üũ�ؾߵǳ�?

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot Processing Started Fail Recv [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] LOT id Fail.\n��õ� �Ͻðڽ��ϱ�?"), g_clTaskWork[m_nUnit].m_szChipID);
			if (g_ShowMsgModal(_T("[INFO]"), szLog, RGB_COLOR_BLUE, _T("RETRY"), _T("PAUSE")) == true)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot ID Fail Retry [STEP : %d]"), nStep);
				AddLog(szLog, 0, m_nUnit);
				nRetStep = 30600;
			}
			else
			{
				nRetStep = -30600;
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO](%s) LOT id Cancel. by Host [STEP : %d]"), g_clTaskWork[m_nUnit].m_szChipID, nStep);
				AddLog(szLog, 1, m_nUnit, true);
				break;
			}

		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > nRunTimeOutSec)
		{
			//g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(CT_TIMEOUT_REPORT_11002); //SEND S6F11
			g_pCarAABonderDlg->m_clUbiGemDlg.cTTimeOutSendFn(_T("S06F12"), _T("10704"));
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot Processing Start Ct TimeOut [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -30600;	//OBJECT ID REPORT Step
			break;
		}
		break;
	case 31700:
		nRetStep = 31800;
		///
		// Lot Processing Start �ް��� Lot ID Start , Fail üũ�ؾߵǳ�?
		//nLotProcessingComplete_ACK  �� Ȯ���ؼ� ���� �Ҷ� �Ǵ�?
		//
		//
#if 0
		if (g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start == 0)
		{
			//LGIT_LOT_START
			//NG Lot ID Cancel by Host
		}else if (g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start == 1)
		{
			//LGIT_LOT_ID_FAIL
			//NG Lot ID Cancel by Host
			sMsg.Empty();
			std::vector<RcmdList_T2> resultsT2;
			resultsT2 = g_clReportData.T2_FindChildList(g_clReportData.rLot_Id_Fail.parameters);
			if (resultsT2.size() > 0)
			{
				for (int i = 0; i < resultsT2[0].rVec.size(); i++)
				{
					if (resultsT2[0].rVec[i].cpName == "MODULEID")
					{
						//g_pCarAABonderDlg->m_clMessageLot.setLotID(_T("LOT ID"), resultsT2[0].rVec[i].cepVal);		//���� lot id? , moduleid?
						sMsg.Format(_T("LOT ID:%s"), resultsT2[0].rVec[i].cepVal);// g_clModelData[m_nUnit].m_nSensorCnt);

						break;
					}
				}
			}
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LGIT_LOT_ID_FAIL]\n%s \nCode :%s\nText:%s\n��õ� �Ͻðڽ��ϱ�?"), sMsg,
				g_clMesCommunication[m_nUnit].m_sErcmdCode, g_clMesCommunication[m_nUnit].m_sErcmdText);
			if (g_ShowMsgModal(_T("[INFO]"), szLog, RGB_COLOR_BLUE, _T("RETRY"), _T("PAUSE")) == true)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot ID Fail Retry [STEP : %d]"), nStep);
				AddLog(szLog, 0, m_nUnit);
				nRetStep = 30600;
			}
			else
			{
				nRetStep = -30600;
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO](%s) LOT id Cancel. by Host [STEP : %d]"), g_clTaskWork[m_nUnit].m_szChipID, nStep);
				AddLog(szLog, 1, m_nUnit, true);
				break;
			}

		}
#endif
		break;
	case 31800:
		nRetStep = 31900;
		break;
	case 31900:
		nRetStep = 32000;
		break;

	case 32000:
		nRetStep = 32500;
		break;
	case 32500:
		
		nRetStep = 32600;
		
		break;
	case 32600:
		nRetStep = 32750;
		break;
	case 32750:		//jump sTep Offline
		// ���ڵ尪 ����
		if (g_clPriInsp[m_nUnit].func_ModelLotCheck(g_clTaskWork[m_nUnit].m_szChipID) == 0)
		{
//#if (____MACHINE_NAME == MODEL_FRONT_100)			//ok
//			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO]BCR Ȯ�� �Ϸ�:%s[002]"), g_clTaskWork[m_nUnit].m_szChipID);
//#else
//			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO]BCR Ȯ�� �Ϸ�:%s[001]"), g_clTaskWork[m_nUnit].m_szChipID);
//#endif
			if (_tcscmp(ModelList.m_szCurrentModel, SHM_FRONT_100_MODEL) == 0)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO]BCR Ȯ�� �Ϸ�:%s[002]"), g_clTaskWork[m_nUnit].m_szChipID);
			}
			else
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO]BCR Ȯ�� �Ϸ�:%s[001]"), g_clTaskWork[m_nUnit].m_szChipID);
			}
			AddLog(szLog, 0, m_nUnit);
		}
		else
		{
//#if (____MACHINE_NAME == MODEL_FRONT_100)			//ok
//			_stprintf_s(szLog, SIZE_OF_1K, _T("[BCR] 100H ���α׷��Դϴ�. �� Ȯ�� �ٶ��ϴ�. (002)\n��� �����Ͻðڽ��ϱ�?"));
//#else
//			_stprintf_s(szLog, SIZE_OF_1K, _T("[BCR] 150H ���α׷��Դϴ�. �� Ȯ�� �ٶ��ϴ�. (001)\n��� �����Ͻðڽ��ϱ�?"));
//#endif
			if (_tcscmp(ModelList.m_szCurrentModel, SHM_FRONT_100_MODEL) == 0)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[BCR] 100H ���α׷��Դϴ�. �� Ȯ�� �ٶ��ϴ�. (002)\n��� �����Ͻðڽ��ϱ�?"));
			}
			else
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[BCR] 150H ���α׷��Դϴ�. �� Ȯ�� �ٶ��ϴ�. (001)\n��� �����Ͻðڽ��ϱ�?"));
			}

			if (g_ShowMsgModal(_T("Ȯ��"), szLog, RGB_COLOR_BLUE) == false)
			{
				g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1047);
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] BCR �� Ȯ�� ���� [STEP : %d]"), nStep);
				AddLog(szLog, 1, m_nUnit, true);

				nRetStep = -32750;
				break;
			}


			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO]BCR CHECK PASS"));
			AddLog(szLog, 0, m_nUnit);
		}
		

		g_pCarAABonderDlg->ShowBarcode(m_nUnit);
		g_clModelData[m_nUnit].LotDataSave();
		nRetStep = 32755;
		break;

		//if ((g_clTaskWork[m_nUnit].m_bPcbSocketIF[PCB_BCR] == true && _tcslen(g_clTaskWork[m_nUnit].m_szChipID) > 0))//11))/// || g_clModelData[m_nUnit].m_nMesPass == 1)
		//{
		//	_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO]BCR Ȯ��:%s [STEP : %d]"), g_clTaskWork[m_nUnit].m_szChipID, nStep);
		//	AddLog(szLog, 0, m_nUnit);
		//	g_pCarAABonderDlg->ShowBarcode(m_nUnit);
		//	g_clModelData[m_nUnit].LotDataSave();
		//	nRetStep = 32755;
		//	break;
		//}
		//else if (GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount > 6000)
		//{
		//	_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB BCR Ȯ�� ���� [STEP : %d]"), nStep);
		//	AddLog(szLog, 1, m_nUnit, true);
		//	nRetStep = -36000;
		//}
		
		break;
	case 32755:
		nRetStep = 32770;
		break;
	case 32770:
		nRetStep = 32780;
		break;
	case 32780:
		nRetStep = 32900;
		break;
	case 32900://jump step
#ifdef ON_LINE_MIL
		g_clVision.ClearOverlay(m_nUnit);
		g_clVision.DrawOverlayAll(m_nUnit);
#endif
		for (int i = 0; i < 20; i++)
		{
			g_clTaskWork[m_nUnit].m_bOutputCheck[i] = true; // LOADING �ʱ�ȭ
		}
		//MES ��� �ʱ�ȭ
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 1;	//�����Ҵ� �ʱ�ȭ�κ� EOL
		
		//�̹������� �ʱ�ȭ
		g_clLaonGrabberWrapper[m_nUnit].CopyInspImage(999, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer);	//�ʱ�ȭ

		g_clTaskWork[m_nUnit].m_nEmission = 0;
		g_clTaskWork[m_nUnit].SaveData();
		g_pCarAABonderDlg->ShowOkNgState(m_nUnit, g_clTaskWork[m_nUnit].m_nEmission); 
		nRetStep = 33000;

		break;
	case 33000:
		g_clTaskWork[m_nUnit].m_dwCycleTactStartTime = GetTickCount();
		nRetStep = 33500;

		break;
	case 33500:
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 35500;
		break;
	case 35500:

		dDelay = g_clModelData[m_nUnit].m_dCcdDelay;
		if (dDelay > 100.0)
		{
			dDelay = dDelay / 1000.0;
		}
		if (dDelay < 0.3)
		{
			dDelay = 0.3;
		}
		if (GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount > dDelay * 1000)//1000)
		{
			nRetStep = 36000;
		} 
		
		break;

	case 36000:
		g_clLaonGrabberWrapper[m_nUnit].UiconfigLoad(INI_YUV_IMAGE);	//YUV AUTO start
		g_clLaonGrabberWrapper[m_nUnit].SelectSensor();
		g_clLaonGrabberWrapper[m_nUnit].AllocImageBuff();
		g_clLaonGrabberWrapper[m_nUnit].rawReSet(1);					//1.YUV Auto_M_PCBLoading

		nRetStep = 36500;
		

		break;
	case 36500:
		
		nRetStep = 36510;
		break;
	case 36510:
		g_clMesCommunication[m_nUnit].m_dwCycleTactStartTime = GetTickCount();

		g_pCarAABonderDlg->m_clCustomThread[m_nUnit].CustomThreadrun(CCD_THREAD);

		g_pCarAABonderDlg->m_clCcdGrabThread[m_nUnit].UpdateGrabStartTime();

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] CCD OPEN Start [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);


		g_clMandoInspLog[m_nUnit].InitData();
		g_pCarAABonderDlg->_DrawBarGraph(m_nUnit);

		// ������ ��뷮 ����
		g_clTaskWork[m_nUnit].m_nUsePinCount++;
		g_pCarAABonderDlg->ShowPinCount(m_nUnit);
		
		g_clTaskWork[m_nUnit].PinSaveData();
		////g_clTaskWork[m_nUnit].SaveData();
		nRetStep = 37500;
		break;

	case 37500:
		
		if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -37500;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PRODUCT PCB LOADING �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		 
		g_clTaskWork[m_nUnit].m_nRetryCount = 0;
		nRetStep = 38000;
		break;

	case 38000:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 38500;

			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -37500;
			break;
		}
		break;
	case 38500:

		nRetStep = 39000;
		break;
	case 39000:
		g_clVision.ClearOverlay(m_nUnit);
		g_clVision.DrawOverlayAll(m_nUnit);


		/*if (g_clModelData[m_nUnit].m_nMasterModeUse == 1)
		{
			if (g_ShowMsgModal(_T("Ȯ��"), _T("[AUTO] MASTER MODE �Դϴ�. �����Ͻðڽ��ϱ�?"), RGB_COLOR_RED) == false)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] MASTER MODE STOP [STEP : %d]"), nStep);
				AddLog(szLog, 0, m_nUnit);
				nRetStep = -39000;
				break;
			}
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] MASTER MODE START [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
		}*/

		
		nRetStep = 40000;
		break;
	default:
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PRODUCT PCB LOADING �̻� STEP �߻� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit, true);
		nRetStep = -1;
		break;
	}

	return nRetStep;
}

//-----------------------------------------------------------------------------
//
// PCB SENSOR ALIGN(40000 ~ 50000)
//
//-----------------------------------------------------------------------------
int CPcbProcess::AutoPcbSensorAlign(int nStep)
{
	TCHAR szLog[SIZE_OF_1K];
	double dPos[3] = { 0.0, 0.0, 0.0 };
	CString sMsg = _T("");
	CDMotor clDmAlign;
	CDMPoint clDpFind;
	bool bRtn = false;
	int nRetVal = 0;
	int nRetStep;
	int i = 0;
	nRetStep = nStep;

	switch (nStep)
	{
	case 40000:
		g_clVision.ClearOverlay(m_nUnit, VIDEO_CAM);
		g_clVision.DrawOverlayAll(m_nUnit, VIDEO_CAM);

		g_pCarAABonderDlg->CAMChangeHandler(0, VIDEO_CAM);

		
		nRetStep = 40500;
		break;
	case 40500:
		if (g_clDioControl.PcbSensorCheck(m_nUnit) == true)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] ��ǰ Ȯ�� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
		}

		
		
		g_clTaskWork[m_nUnit].m_nRetryCount = 0;


		g_clTaskWork[m_nUnit].m_dAADataX = 0.0;
		g_clTaskWork[m_nUnit].m_dAADataY = 0.0;
		g_clTaskWork[m_nUnit].m_dAADataTh = 0.0;

		g_clTaskWork[m_nUnit].m_dAlignData.x = 0.0;
		g_clTaskWork[m_nUnit].m_dAlignData.y = 0.0;
		g_clTaskWork[m_nUnit].m_dAlignData.t = 0.0;

		g_clTaskWork[m_nUnit].dpFind.x = 0.0;
		g_clTaskWork[m_nUnit].dpFind.y = 0.0;


		g_clTaskWork[m_nUnit].m_dSensorAlign[0] = 0.0;
		g_clTaskWork[m_nUnit].m_dSensorAlign[1] = 0.0;
		g_clTaskWork[m_nUnit].m_dSensorAlign[2] = 0.0;


		
		nRetStep = 41000;
		break;

	case 41000:
		//! PCB Z�� ��� ��ġ �̵�
		if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -41000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 41500;
		break;

	case 41500:
		//! PCB Z�� ��� ��ġ �̵� Ȯ��

		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 42000;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -41000;
			break;
		}
		break;
	case 42000:
		if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//���� ���� ���� Ȯ��  align
		{
			g_clMotorSet.StopAxisAll(m_nUnit);

			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1007);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Vacuum Ȯ�� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -42000;
			break;
		}
		if (g_clModelData[m_nUnit].m_nAlignPass == 1)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Align ���� Pass [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 47000;
			break;
		}
		
		//! PCB SENSOR Align ��ġ �̵�
		if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, SENSOR_ALIGN_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB X,Y,T�� SENSOR ALIGN ��ġ �̵� ��� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -42000;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB X,Y,T�� SENSOR ALIGN ��ġ �̵� ��� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 42500;
		break;

	case 42500:
		//! PCB SENSOR Align ��ġ �̵� Ȯ��
		if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//���� ���� ���� Ȯ��  align
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1007);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Vacuum Ȯ�� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -42500;
			break;
		}


#ifdef ON_LINE_MOTOR
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[SENSOR_ALIGN_POS].dPos[MOTOR_PCB_X];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[SENSOR_ALIGN_POS].dPos[MOTOR_PCB_Y];
		dPos[2] = g_clModelData[m_nUnit].m_stTeachData[SENSOR_ALIGN_POS].dPos[MOTOR_PCB_TH];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_X) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_X) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Y) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Y) - dPos[1]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TH) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TH) - dPos[2]) < ENCORDER_GAP)))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB X,Y,T�� SENSOR ALIGN ��ġ �̵� �Ϸ� [STEP : %d"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 42600;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB X,Y,T�� SENSOR ALIGN ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -42000;
			break;
		}
#else
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB X,Y,T�� SENSOR ALIGN ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		nRetStep = 42600;
#endif
		break;

	case 42600:
		if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, SENSOR_ALIGN_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� SENSOR ALIGN �̵� ��� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -42600;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� SENSOR ALIGN �̵� ��� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		nRetStep = 42700;
		break;

	case 42700:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[SENSOR_ALIGN_POS].dPos[MOTOR_PCB_TX];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[SENSOR_ALIGN_POS].dPos[MOTOR_PCB_TY];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TX) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TX) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TY) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TY) - dPos[1]) < ENCORDER_GAP)))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� SENSOR ALIGN ��ġ �̵� �Ϸ� [STEP : %d"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 43000;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� SENSOR ALIGN ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -42600;
			break;
		}
		
		break;
	case 43000:
		//! PCB Z�� HOLDER ALIGN ��ġ �̵�
		if (g_clMotorSet.MovePcbZMotor(m_nUnit, SENSOR_ALIGN_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� SENSOR ALIGN ��ġ �̵� ��� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -43000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� SENSOR ALIGN ��ġ �̵� ��� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 43500;
		break;

	case 43500:
		//! PCB Z�� HOLDER ALIGN ��ġ �̵� Ȯ��
#ifdef ON_LINE_MOTOR
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[SENSOR_ALIGN_POS].dPos[MOTOR_PCB_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� SENSOR ALIGN ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 43700;
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� SENSOR ALIGN ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -43000;
			break;
		}
#else
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� SENSOR ALIGN ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		nRetStep = 43700;
#endif
		break;
	case 43700:
		

		nRetStep = 44000;
		break;
	case 44000:
		
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 44500;
		break;

	case 44500:
		//! ALIGN�� Delay
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > (DWORD)g_clModelData[m_nUnit].m_dSensorAlignDelay * 1000)
		{
			nRetStep = 45000;
		}
		break;
	case 45000:
		bRtn = g_clVision.CalcSingleMarkAlign(m_nUnit, SENSOR_ALIGN_MARK, 0, g_clTaskWork[m_nUnit].m_dAlignData, g_clTaskWork[m_nUnit].dpFind);
		//if (g_clModelData[m_nUnit].m_nDryRunMode == 1)//0)
		//{
		//	//g_clTaskWork[m_nUnit].m_dAlignData.t = 0.0;//240328  �ٽ� th ���� ����
		//}

		g_clTaskWork[m_nUnit].m_dAlignData.t = 0.0;


		if (bRtn == false)
		{
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Mark Find Fail [STEP : %d]"),  nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -44500;
			break;
		}
		nRetVal = g_CheckAlignSpec(m_nUnit, SENSOR_ALIGN_MARK, g_clTaskWork[m_nUnit].m_dAlignData.x, g_clTaskWork[m_nUnit].m_dAlignData.y, g_clTaskWork[m_nUnit].m_dAlignData.t);//

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Sensor Align ������(X:%.03lf, Y:%.03lf)[STEP : %d]"), g_clTaskWork[m_nUnit].m_dAlignData.x, g_clTaskWork[m_nUnit].m_dAlignData.y, nStep);//, g_clTaskWork[m_nUnit].m_dAlignData.t
		AddLog(szLog, 0, m_nUnit);


		if (g_clModelData[m_nUnit].m_nDryRunMode == 1 && g_clTaskWork[m_nUnit].m_nRetryCount == 0)	//�ݺ��� Align ����
		{
			g_clMesCommunication[m_nUnit].m_dGrrAlignPos[0] = g_clTaskWork[m_nUnit].m_dAlignData.x;
			g_clMesCommunication[m_nUnit].m_dGrrAlignPos[1] = g_clTaskWork[m_nUnit].m_dAlignData.y;
			g_clMesCommunication[m_nUnit].m_dGrrAlignPos[2] = g_clTaskWork[m_nUnit].m_dAlignData.t;
		}
		if (nRetVal == 0)
		{
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1051);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Sensor Align ������ �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit , true);
			//
			g_clTaskWork[m_nUnit].m_dSensorAlign[0] = 0.0; 
			g_clTaskWork[m_nUnit].m_dSensorAlign[1] = 0.0;
			g_clTaskWork[m_nUnit].m_dSensorAlign[2] = 0.0;
			g_clTaskWork[m_nUnit].m_nRetryCount = 0;
			//
			//
			//��ũ �߸� �׸��� rotation ���� ���Ҽ� �־� ƼĪ �� �״�� ���� �ǰ� ���� 240621
			//
			//
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			nRetStep = -44500;
			break;
		}
		else if (nRetVal == 2)
		{
			//Spec In
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Sensor Align �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clTaskWork[m_nUnit].m_nRetryCount = 0;
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();

			nRetStep = 47000;
			break;
		}
		else
		{
			//nRetVal = 1 �̸� retry
		}
		g_clTaskWork[m_nUnit].m_dSensorAlign[0] += g_clTaskWork[m_nUnit].m_dAlignData.x;
		g_clTaskWork[m_nUnit].m_dSensorAlign[1] += g_clTaskWork[m_nUnit].m_dAlignData.y;
		g_clTaskWork[m_nUnit].m_dSensorAlign[2] = 0.0;		/// g_clTaskWork[m_nUnit].m_dAlignData.t;			// 0.0;		// 



		//_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Sensor Align �����̵�(X:%.03lf, Y:%.03lf, TH:%.03lf) [STEP : %d]"), g_clTaskWork[m_nUnit].m_dSensorAlign[0], g_clTaskWork[m_nUnit].m_dSensorAlign[1], g_clTaskWork[m_nUnit].m_dSensorAlign[2], nStep);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Sensor Align �����̵�(X:%.03lf, Y:%.03lf) [STEP : %d]"), g_clTaskWork[m_nUnit].m_dSensorAlign[0], g_clTaskWork[m_nUnit].m_dSensorAlign[1], nStep);
		AddLog(szLog, 0, m_nUnit);
		nRetStep = 45200;
		break;
	case 45200: 

		if (g_clTaskWork[m_nUnit].m_nRetryCount > (g_clModelData[m_nUnit].m_nSensorAlignRetryCount - 1))
		{
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1052);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB SENSOR ALIGN RETRY Ƚ��(%d) �ʰ� [STEP : %d]"), g_clModelData[m_nUnit].m_nSensorAlignRetryCount, nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -44000;
			break;
		}

		g_clTaskWork[m_nUnit].m_nRetryCount++;
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB SENSOR ALIGN RETRY %dȸ [STEP : %d]"), g_clTaskWork[m_nUnit].m_nRetryCount, nStep);
		AddLog(szLog, 0, m_nUnit);
		nRetStep = 46000;
		break;

	case 46000:
		//! ���� �̵� �� ALIGN ������
		if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, SENSOR_ALIGN_POS, g_clTaskWork[m_nUnit].m_dSensorAlign[0], g_clTaskWork[m_nUnit].m_dSensorAlign[1], g_clTaskWork[m_nUnit].m_dSensorAlign[2], true) == false)
		{
			//_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB SENSOR ALIGN ���� ��ġ(%.03lf, %.03lf, %.03lf) �̵� ���� [STEP : %d]"),
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB SENSOR ALIGN ���� ��ġ(%.03lf, %.03lf) �̵� ���� [STEP : %d]"),
				g_clTaskWork[m_nUnit].m_dSensorAlign[0], g_clTaskWork[m_nUnit].m_dSensorAlign[1], nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -46000;
			break;
		}

		//_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB SENSOR ALIGN ���� ��ġ(%.03lf, %.03lf, %.03lf) �̵� �Ϸ� [STEP : %d]"),
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB SENSOR ALIGN ���� ��ġ(%.03lf, %.03lf) �̵� �Ϸ� [STEP : %d]"),
			g_clTaskWork[m_nUnit].m_dSensorAlign[0], g_clTaskWork[m_nUnit].m_dSensorAlign[1], nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 44000;
		break;

	case 47000:
		//! PCB Z�� �����ġ �̵�
		if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS) == false) 
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -47000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 47500;
		break;
	case 47500:
		//! PCB Z�� �����ġ �̵� Ȯ��
#ifdef ON_LINE_MOTOR
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] CCD ���� �����... [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 48000;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -47000;
			break;
		}
#else
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS �̵� �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		nRetStep = 48000;
#endif
		break;
	case 48000:
		BackDuLightControl[m_nUnit].ctrlLedVolume(LIGHT_BD_ALIGN_CH1, 0);
		nRetStep = 48500;

		break;
	case 48500:
		nRetStep = 49000;
		break;
	case 49000:
		g_clVision.ClearOverlay(m_nUnit, VIDEO_CAM);
		g_clVision.DrawOverlayAll(m_nUnit, VIDEO_CAM);
		nRetStep = 50000;
		break;

	default:
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] SENSOR ALIGN STEP �̻� �߻� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		nRetStep = -1;
		break;
	}

	return nRetStep;
}



//-----------------------------------------------------------------------------
//
//	Lens �ε�(50000 ~ 60000)
//
//-----------------------------------------------------------------------------
int CPcbProcess::AutoLensLoading(int nStep)
{

	TCHAR szLog[SIZE_OF_1K];
	double dPos[3] = { 0.0, 0.0, 0.0 };
	CString sMsg = _T("");
	int nRetStep = nStep;

	return nRetStep;

}

//-----------------------------------------------------------------------------
//
//	PCB LASER(50000 ~ 60000)
//
//-----------------------------------------------------------------------------
int CPcbProcess::AutoPcbLaser(int nStep)
{
	TCHAR szLog[SIZE_OF_1K];
	double dPos[4] = { 0.0, 0.0, 0.0, 0.0 };
	double dLaserTx = 0.0;
	double dLaserTy = 0.0;
	double curPos = 0.0;
	int nRetVal = 0;
	int nRetStep;
	int i = 0;

	nRetStep = nStep;

	switch (nStep)
	{
	case 50000:
		BackDuLightControl[m_nUnit].ctrlLedVolume(LIGHT_BD_ALIGN_CH1, 0);
		g_pCarAABonderDlg->CAMChangeHandler(0, VIDEO_CCD);
		g_clVision.ClearOverlay(m_nUnit);
		g_clVision.DrawOverlayAll(m_nUnit);

		g_clMesCommunication[m_nUnit].m_dMesLaserTilt[0] = 0.0;
		g_clMesCommunication[m_nUnit].m_dMesLaserTilt[1] = 0.0;
		nRetStep = 50200;
		break;
	case 50200:
		if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -50200;
			break;
		} 

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 50400;
		break;
	case 50400:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 51000;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -50200;
			break;
		}
		break;
	case 51000:
		
		if (g_clModelData[m_nUnit].m_nLaserOutUse == 0)	//������ ��� x
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LASER TILT PASS [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 59400;
			break;
		}

		//PCB LASER START
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
		nRetStep = 52000;

		break;
	case 52000:
		//! PCB TX,TY Align ��ġ �̵�
		if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, LASER_POS, 0.0, 0.0, false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� LASER_POS �̵� ��� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -52000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� LASER_POS �̵� ��� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 53000;

		break;
	case 53000:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[LASER_POS].dPos[MOTOR_PCB_TX];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[LASER_POS].dPos[MOTOR_PCB_TY];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TX) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TX) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TY) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TY) - dPos[1]) < ENCORDER_GAP)))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� LASER_POS ��ġ �̵� �Ϸ� [STEP : %d"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 54000;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� LASER_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -52000;
			break;
		}
		
		break;
	case 54000:
		if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//���� ���� ���� Ȯ��  Laser
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1007);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Vacuum Ȯ�� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -54000;
			break;
		}

		//PCB X,Y LASER POS 1�̵�
		if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, LASER_POS, g_clTaskWork[m_nUnit].m_dSensorAlign[0], g_clTaskWork[m_nUnit].m_dSensorAlign[1], g_clTaskWork[m_nUnit].m_dSensorAlign[2], false) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] PCB X,Y�� LASER POS ��ġ �̵� ��� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -54000;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] PCB X,Y�� LASER POS ��ġ �̵� ��� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();

		nRetStep = 54200;
		break;

	case 54200:

		if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//���� ���� ���� Ȯ��  Laser
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1007);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Vacuum Ȯ�� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -54200;
			break;
		}


		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[LASER_POS].dPos[MOTOR_PCB_X] + g_clTaskWork[m_nUnit].m_dSensorAlign[0];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[LASER_POS].dPos[MOTOR_PCB_Y] + g_clTaskWork[m_nUnit].m_dSensorAlign[1];
		dPos[2] = g_clModelData[m_nUnit].m_stTeachData[LASER_POS].dPos[MOTOR_PCB_TH] + g_clTaskWork[m_nUnit].m_dSensorAlign[2];

		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_X) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_X) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Y) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Y) - dPos[1]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TH) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TH) - dPos[2]) < ENCORDER_GAP))
			)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] PCB X,Y,TH�� LASER ������ġ(%.03lf, %.03lf, %.03lf) �̵� �Ϸ� [STEP : %d]"),
				g_clTaskWork[m_nUnit].m_dSensorAlign[0], g_clTaskWork[m_nUnit].m_dSensorAlign[1], g_clTaskWork[m_nUnit].m_dSensorAlign[2], nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 54400;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] PCB Y�� LASER ������ġ(%.03lf, %.03lf, %.03lf) �̵� �ð��ʰ� [STEP : %d]"),
				g_clTaskWork[m_nUnit].m_dSensorAlign[0], g_clTaskWork[m_nUnit].m_dSensorAlign[1], g_clTaskWork[m_nUnit].m_dSensorAlign[2], nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -54200;
			break;
		}
		break;
	case 54400:
		if (g_clTaskWork[m_nUnit].m_nLaserTiltIndex > 0)
		{
			nRetStep = 54800;

			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			break;
		}
		if (g_clMotorSet.MovePcbZMotor(m_nUnit, LASER_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] PCB Z�� LASER ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -54400;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] PCB Z�� LASER ��ġ �̵� ��� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 54600;
		break;

	case 54600:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[LASER_POS].dPos[MOTOR_PCB_Z];
		curPos = g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z);
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && (curPos - dPos[0]) < ENCORDER_GAP)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] PCB Z�� LASER ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 54800;

			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] PCB Z�� LASER ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -54600;
			break;
		}
		break;
	case 54800:
		//! ���� �� DELAY
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > (DWORD)(g_clModelData[m_nUnit].m_dLaserDelay * 1000))
		{
			nRetStep = 55000;
		}
		break;
	case 55000:
		//������ ����
		g_clTaskWork[m_nUnit].m_bRecvLaserTilt = false;
		g_clTaskWork[m_nUnit].m_clDpLaserPos[g_clTaskWork[m_nUnit].m_nLaserTiltIndex].x = g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_X);
		g_clTaskWork[m_nUnit].m_clDpLaserPos[g_clTaskWork[m_nUnit].m_nLaserTiltIndex].y = g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Y);

		if (g_pCarAABonderDlg->SendLaserMeasurePacket(m_nUnit) == false)
		{
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1057);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] �������� ���� ��� �۽� ����. [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -55000;
			break;
		}

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 55100;		// 55200;	241028
		break;

	case 55100:
		if (g_clTaskWork[m_nUnit].m_bRecvLaserTilt == true)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] �������� ���� ��� �۽� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 55200;
			break;
		}
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > 5000)
		{
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1058);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] �������� %d��° ���� ������ ���� ����"), g_clTaskWork[m_nUnit].m_nLaserTiltIndex + 1);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -55000;
		}
		break;
	case 55200:
		if (g_clTaskWork[m_nUnit].m_nLaserTiltIndex > 3) 
		{
			nRetStep = 55400;
			break;
		}


		if (g_clModelData[m_nUnit].m_nDryRunMode == 1 && g_clTaskWork[m_nUnit].m_nRetryCount == 0)	//�ݺ��� Laser ����
		{
			g_clMesCommunication[m_nUnit].m_dGrrLaserPos[g_clTaskWork[m_nUnit].m_nLaserTiltIndex] = g_clTaskWork[m_nUnit].m_dLaserVal[g_clTaskWork[m_nUnit].m_nLaserTiltIndex];
		}
		if (g_clModelData[m_nUnit].m_nDryRunMode == 1)	//�ݺ��� Laser ����
		{
			g_clMesCommunication[m_nUnit].m_dGrrBeForeLaserPos[g_clTaskWork[m_nUnit].m_nLaserTiltIndex] = g_clTaskWork[m_nUnit].m_dLaserVal[g_clTaskWork[m_nUnit].m_nLaserTiltIndex];
		}
		g_clTaskWork[m_nUnit].m_nLaserTiltIndex++;
		// X�� -����
		if (g_clTaskWork[m_nUnit].m_nLaserTiltIndex == 1)
		{
			if (g_clMotorSet.MoveAxisComplete(m_nUnit, MOTOR_PCB_X, REL, (g_clModelData[m_nUnit].m_dLaserMoveX[0] * -1), g_clSysData.m_dMotorSpeed[m_nUnit][MOTOR_PCB_X], true) == false)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] �������� %d��° ��ġ �̵� ���� [STEP : %d]"), g_clTaskWork[m_nUnit].m_nLaserTiltIndex + 1, nStep);
				AddLog(szLog, 1, m_nUnit, true);

				nRetStep = -55200;
				break;
			}

			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] �������� %d��° ��ġ �̵� �Ϸ� [STEP : %d]"), g_clTaskWork[m_nUnit].m_nLaserTiltIndex + 1, nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			nRetStep = 54800;

		}
		else if (g_clTaskWork[m_nUnit].m_nLaserTiltIndex == 2)
		{
			if (g_clMotorSet.MoveAxisComplete(m_nUnit, MOTOR_PCB_Y, REL, g_clModelData[m_nUnit].m_dLaserMoveY[0], g_clSysData.m_dMotorSpeed[m_nUnit][MOTOR_PCB_Y], true) == false)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] �������� %d��° ��ġ �̵� ���� [STEP : %d]"), g_clTaskWork[m_nUnit].m_nLaserTiltIndex + 1, nStep);
				AddLog(szLog, 1, m_nUnit, true);

				nRetStep = -55200;
				break;
			}

			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] �������� %d��° ��ġ �̵� �Ϸ� [STEP : %d]"), g_clTaskWork[m_nUnit].m_nLaserTiltIndex + 1, nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			nRetStep = 54800;
		}
		else if (g_clTaskWork[m_nUnit].m_nLaserTiltIndex == 3)
		{
			if (g_clMotorSet.MoveAxisComplete(m_nUnit, MOTOR_PCB_X, REL, (g_clModelData[m_nUnit].m_dLaserMoveX[0] * 1), g_clSysData.m_dMotorSpeed[m_nUnit][MOTOR_PCB_X], true) == false)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] �������� %d��° ��ġ �̵� ���� [STEP : %d]"), g_clTaskWork[m_nUnit].m_nLaserTiltIndex + 1, nStep);
				AddLog(szLog, 1, m_nUnit, true);

				nRetStep = -55200;
				break;
			}

			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] �������� %d��° ��ġ �̵� �Ϸ� [STEP : %d]"), g_clTaskWork[m_nUnit].m_nLaserTiltIndex + 1, nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			nRetStep = 54800;
		} 
		break;
	case 55400:
		//! TX,TY ������ ���
		g_CalcLaserTilt(m_nUnit, dLaserTx, dLaserTy);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] �������� ������(TX : %.03lf, TY : %.03lf) [STEP : %d]"), dLaserTx, dLaserTy, nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dLaserTiltX[0] = dLaserTx;
		g_clTaskWork[m_nUnit].m_dLaserTiltY[0] = dLaserTy ;		//PCB TY , LENS TY ����ݴ�� 

		g_clMesCommunication[m_nUnit].m_dMesLaserTilt[0] += dLaserTx;
		g_clMesCommunication[m_nUnit].m_dMesLaserTilt[1] += dLaserTy;

		nRetVal = g_CheckTiltLimit(m_nUnit, 0, dLaserTx, dLaserTy);

		if (nRetVal == 1)	// �����̵�
		{
			nRetStep = 55600;
		}

		else if (nRetVal == 2)	// OK
		{
			g_clTaskWork[m_nUnit].m_nRetryCount = 0;
			nRetStep = 56500;
			break;
		}
		// ���� LIMIT �ʰ�
		else
		{
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1063);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] TILT ������ LIMIT �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -53000;		// -55400;
			break;
		}
		break;
	case 55600:
		//! TX,TY ���� 
		if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, g_clTaskWork[m_nUnit].m_dLaserTiltX[0], g_clTaskWork[m_nUnit].m_dLaserTiltY[0], true) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] TILT TX(%.03lf), TY(%.03lf) ���� �̵� ���� [STEP : %d]"),
				g_clTaskWork[m_nUnit].m_dLaserTiltX[0], g_clTaskWork[m_nUnit].m_dLaserTiltY[0], nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -55600;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] TILT TX(%.03lf), TY(%.03lf) ���� �̵� �Ϸ� [STEP : %d]"),
			g_clTaskWork[m_nUnit].m_dLaserTiltX[0], g_clTaskWork[m_nUnit].m_dLaserTiltY[0], nStep);
		AddLog(szLog, 0, m_nUnit);

		nRetStep = 56000;

		break;
	case 56000:
		if (g_clTaskWork[m_nUnit].m_nRetryCount > (g_clModelData[m_nUnit].m_nLaserRetryCount - 1))
		{
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1065);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] TILT ���� Ƚ��(%d) �ʰ� [STEP : %d]"), g_clModelData[m_nUnit].m_nLaserRetryCount, nStep);
			AddLog(szLog, 1, m_nUnit, true);

			g_clTaskWork[m_nUnit].m_nRetryCount = 0;

			nRetStep = -56000;
			break;
		}

		g_clTaskWork[m_nUnit].m_nRetryCount++;
		g_clTaskWork[m_nUnit].m_nLaserTiltIndex = 0;
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();

		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] TILT %dȸ ��õ� [STEP : %d]"), g_clTaskWork[m_nUnit].m_nRetryCount, nStep);
		AddLog(szLog, 0, m_nUnit);

		nRetStep = 54000;
		break;
	case 56500: 
		

		g_clMesCommunication[m_nUnit].m_dMesLaserTilt[0] += dLaserTx;
		g_clMesCommunication[m_nUnit].m_dMesLaserTilt[1] += dLaserTy;


		nRetStep = 56700;
		break;
	case 56700:
	
		nRetStep = 57000;
		break;
	case 57000:

		nRetStep = 57200;
		break;
	case 57200:
		
		nRetStep = 59400;
		break;
	case 59400:

		if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -59400;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();

		nRetStep = 59600;
		break;

	case 59600:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 59900;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -59400;
			break;
		}
		break;
	case 59900:
		g_clVision.ClearOverlay(m_nUnit, VIDEO_CAM);
		g_clVision.DrawOverlayAll(m_nUnit, VIDEO_CAM);
		nRetStep = 60000; 
		break; 
	default:
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LASER STEP �̻� �߻� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		nRetStep = -1;
		break;
	}

	return nRetStep;

}


//-----------------------------------------------------------------------------
//
//	LENS , PCB CHART �̵�(60000 ~ 70000)
//
//-----------------------------------------------------------------------------
int CPcbProcess::AutoChartMoving(int nStep)
{
	TCHAR szLog[SIZE_OF_1K];
	double dPos[3] = { 0.0, 0.0, 0.0 };
	double curPos = 0.0;
	int i = 0;
	CString sMsg = _T("");
	int nRetVal = 0;
	int nRetStep;
	bool bResult = false;

	return 0;
}

//-----------------------------------------------------------------------------
//
//	�̹����� 3000,5000,6500,IR �̹����� �˻�(100000 ~ 110000)	
//
//-----------------------------------------------------------------------------

int CPcbProcess::Auto_OC_Insp(int nStep)
{
	TCHAR szLog[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;
	CString sMsg = _T("");
	double dMoveDist = 0.0;
	double dMoveVel = 0.0;
	double dMoveAcc = 0.0;
	double dPos[3] = { 0.0, 0.0, 0.0 };
	int nRetVal = 0;
	int nRetStep = 0;
	int i = 0;
	double dCenterPosX = 0.0;
	double dCenterPosY = 0.0;
	double dZoomX  = 0.0;
	double dZoomY = 0.0;
	bool bInspRtn = false;
	nRetStep = nStep;


	switch (nStep)
	{
	case 80000:
		g_pCarAABonderDlg->CAMChangeHandler(m_nUnit, VIDEO_CCD);
		g_clVision.ClearOverlay(m_nUnit);
		g_clVision.DrawOverlayAll(m_nUnit);

		g_clTaskWork[m_nUnit].m_dwTotalTactTime = GetTickCount();
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();

		BackDuLightControl[m_nUnit].ctrlLedVolume(LIGHT_BD_OC_CH2, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_OC_WHITE1]);
		nRetStep = 80200;
		break;
	case 80200:
		if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -80200;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 80400;

		break;
	case 80400:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 81000;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -80400;
			break;
		}
		break;
	
	case 81000:
		if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//���� ���� ���� Ȯ��  Oc
		{
			g_clMotorSet.StopAxisAll(m_nUnit);

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Vacuum Ȯ�� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -81000;
			break;
		}
		if (g_clModelData[m_nUnit].m_nDryRunMode == 1)	//�ݺ��� �������� �̹����� ���� pass
		{
			nRetStep = 85100;
			break;
		}
		//MN DARK POS �̵�
		if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, OC_LIGHT_POS, g_clTaskWork[m_nUnit].m_dSensorAlign[0], g_clTaskWork[m_nUnit].m_dSensorAlign[1], g_clTaskWork[m_nUnit].m_dSensorAlign[2]) == false)		//��Ʈ ������ �ѻ��¶� �Ȱ���.
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][PCB] PCB WHITE POS �˻� ��ġ �̵� ��� ���� [STEP : %d]"), nStep); 
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -81000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][PCB] PCB WHITE POS �˻� ��ġ �̵� ��� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 81500;
		break;
	case 81500:
		if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//���� ���� ���� Ȯ��  oc
		{
			g_clMotorSet.StopAxisAll(m_nUnit);

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Vacuum Ȯ�� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -81500;
			break;
		}
		//! PCB X,Y,T�� Chart �˻� ��ġ �̵� Ȯ��
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[OC_LIGHT_POS].dPos[MOTOR_PCB_X] + g_clTaskWork[m_nUnit].m_dSensorAlign[0];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[OC_LIGHT_POS].dPos[MOTOR_PCB_Y] + g_clTaskWork[m_nUnit].m_dSensorAlign[1];
		dPos[2] = g_clModelData[m_nUnit].m_stTeachData[OC_LIGHT_POS].dPos[MOTOR_PCB_TH] + g_clTaskWork[m_nUnit].m_dSensorAlign[2];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_X) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_X) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Y) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Y) - dPos[1]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TH) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TH) - dPos[2]) < ENCORDER_GAP))
			)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB WHITE POS �˻���ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			nRetStep = 82000;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB WHITE POS �˻� ��ġ  �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -81000;
			break;
		}

		break;
	case 82000:
		if (g_clModelData[m_nUnit].m_nLaserOutUse == 1)	//������ ��� o
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LASER TILT PASS [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 83000;
			break;
		}
		if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, OC_LIGHT_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� OC_LIGHT_POS �̵� ��� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -82000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� OC_LIGHT_POS �̵� ��� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 82500;
		break;
	case 82500:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[OC_LIGHT_POS].dPos[MOTOR_PCB_TX];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[OC_LIGHT_POS].dPos[MOTOR_PCB_TY];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TX) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TX) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TY) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TY) - dPos[1]) < ENCORDER_GAP)))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� OC_LIGHT_POS ��ġ �̵� �Ϸ� [STEP : %d"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 83000;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� OC_LIGHT_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -82000;
			break;
		}
		break;
	case 83000:
		
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 83100;
		break;
	case 83100:
		if (g_clLaonGrabberWrapper[m_nUnit].GetCurrentState() == CCD_GRAB_LIVE)
		{
			Sleep(500);

			if (g_clModelData[m_nUnit].m_nFpsStopUse == 1)
			{
				if (g_clTaskWork[m_nUnit].m_fFps >= g_clModelData[m_nUnit].m_fFpsStopVal)
				{
					_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] CCD IMAGE GRAB(FPS:%.f/%.f) ���� [STEP : %d]"), g_clTaskWork[m_nUnit].m_fFps, g_clModelData[m_nUnit].m_fFpsStopVal, nStep);
					AddLog(szLog, 0, m_nUnit);
					g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
					nRetStep = 83200;
				}
				else
				{
					if (g_ShowMsgModal(_T("Ȯ��"), _T("[AUTO] FPS���� �����ϴ�. �����Ͻðڽ��ϱ�?"), RGB_COLOR_RED) == false)
					{
						g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1076);
						_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] FPS:%.f ERROR. ��ǰ ���� Ȯ���ϼ��� [STEP : %d]"), g_clTaskWork[m_nUnit].m_fFps, nStep);
						AddLog(szLog, 1, m_nUnit, true);
						nRetStep = -83100;
						break;
					}
					else
					{
						g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
						nRetStep = 83200;
						break;
					}
				}
			}
			else
			{
				g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
				nRetStep = 83200;
				break;
			}
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > 10000)	//10��
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] CCD OPEN ����. ��ǰ ���� ���� �� ��ǰ �ҷ��� Ȯ���ϼ���. [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -83100;
			break;
		}
		
		break;
	case 83200:

		nRetStep = 83500;
		break;
	case 83500:
		if (g_clMotorSet.MovePcbZMotor(m_nUnit, OC_LIGHT_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� OC_LIGHT_POS ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -83500;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� OC_LIGHT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		nRetStep = 84000;
		break;
	case 84000:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[OC_LIGHT_POS].dPos[MOTOR_PCB_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� OC_LIGHT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 84500;

			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� OC_LIGHT_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -83500;
			break;
		}
		break;
	case 84500:
		nRetStep = 84600;
		break;
	case 84600:
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 84700;
		break;
	case 84700:
		//�̹� �̹��� Get
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > 500)
		{
			g_clLaonGrabberWrapper[m_nUnit].CopyInspImage(OC_RAW_IMAGE, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer);			//�̹�����

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Oc Raw Image Save Ok [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			if (g_clModelData[m_nUnit].m_nJxlSavePass == 0)
			{
				g_clLaonGrabberWrapper[m_nUnit].ImageEncode();		//auto
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Jxl File Save Ok [STEP : %d]"), nStep);
				AddLog(szLog, 0, m_nUnit);
			}

			g_clPriInsp[m_nUnit].func_Insp_LightTest(1);
			double dFactorX = 0.0;
			double dFactorY = 0.0;

			dFactorX = ((double)g_clModelData[m_nUnit].DefectSizeX / (double)g_clModelData[m_nUnit].m_nWidth);
			dFactorY = ((double)g_clModelData[m_nUnit].DefectSizeY / (double)g_clModelData[m_nUnit].m_nHeight);

			MimResize(g_clVision.m_MilCcdProcImage[m_nUnit], g_clVision.MilDefectImage[m_nUnit], dFactorX, dFactorY, M_DEFAULT);
			
			nRetStep = 84800;
			break;
		}
		break;
	case 84800:
		//Raw image
		g_clPriInsp[m_nUnit].LCBInsp(g_clLaonGrabberWrapper[m_nUnit].vRawBuffer_3000k, 0, true);// mRCount);
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] STAIN LCB �˻� �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clPriInsp[m_nUnit].FDFInsp(g_clLaonGrabberWrapper[m_nUnit].vRawBuffer_3000k, true);
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] STAIN FDF �˻� �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clPriInsp[m_nUnit].Blemish_YmeanInsp(g_clLaonGrabberWrapper[m_nUnit].vRawBuffer_3000k, true);
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] STAIN YMEAN �˻� �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		bInspRtn = g_clPriInsp[m_nUnit].func_Insp_Shm_Illumination(g_clLaonGrabberWrapper[m_nUnit].vRawBuffer_3000k, true);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Relative Illumination �˻� �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		

		nRetStep = 84900;
		break;
	case 84900:
		nRetStep = 85000;
		break;
	case 85000:
		
		nRetStep = 85100;
		break;
	case 85100:
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 85200;
		break;
	case 85200:
		nRetStep = 85400;

		break;
	case 85400:
		nRetStep = 85600;

		
		break;
	case 85600:
		nRetStep = 85800;

		break;
	case 85800:
		
		nRetStep = 89000;
		break;
	case 89000:
		if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -89000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� ��� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 89200;
		break;

	case 89200:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 89400;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -89000;
			break;
		}
		
		
		break; 
	case 89400:
		nRetStep = 89600;
		break;
	case 89600:
		nRetStep = 89800;
		break;
	case 89800:
		nRetStep = 89900;
		break;
	case 89900:
		BackDuLightControl[m_nUnit].ctrlLedVolume(LIGHT_BD_OC_CH2, 0);

		g_clVision.ClearOverlay(m_nUnit);
		g_clVision.DrawOverlayAll(m_nUnit);

		nRetStep = 90000;
		break;
	default:
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] OC INSP �̻� STEP �߻� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		nRetStep = -1;
		break;
	}
	//

	return nRetStep;
}


//-----------------------------------------------------------------------------
//
//	Chart �̹����� �˻�(80000 ~ 90000)	
//
//-----------------------------------------------------------------------------
int CPcbProcess::AutoChartInsp(int nStep)
{
    TCHAR szLog[SIZE_OF_1K];
    TCHAR szPath[SIZE_OF_1K];
    CFileFind clFinder;
    CString sMsg = _T("");
    double dMoveDist = 0.0;
    double dMoveVel = 0.0;
    double dMoveAcc = 0.0;
    double dPos[3] = { 0.0, 0.0, 0.0 };
    int nRetVal = 0;
    int nRetStep = 0;
	bool bNgDiffView = false;
	double thcount = 0.0;
    int i = 0;
    nRetStep = nStep;
    switch (nStep)
    {
    case 60000:
		VarRetry = 0;
		nDiffRetry = 0;
		rawSumCount = 0;
		m_nDiffTestOk = false;
		g_clTaskWork[m_nUnit].m_nCcdCount = 0;
		g_pCarAABonderDlg->CAMChangeHandler(m_nUnit, VIDEO_CCD);

		g_clVision.ClearOverlay(m_nUnit);
		g_clVision.DrawOverlayAll(m_nUnit);
        g_clTaskWork[m_nUnit].m_dwTotalTactTime = GetTickCount();
        g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();

		TopChartControl[m_nUnit].dpctrlLedVolume(LIGHT_CHART_CH_1, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_TOP_CHART_1]);
        nRetStep = 60020;
        break;
	case 60020:
		LightLeftChartControl[m_nUnit].dpctrlLedVolume(LEFT_CHART_CH_1, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_SIDE_CHART_LEFT]);
		nRetStep = 60040;
		break;
	case 60040:
		LightRightChartControl[m_nUnit].dpctrlLedVolume(RIGHT_CHART_CH_1, g_clModelData[m_nUnit].m_nLight[LIGHT_DATA_SIDE_CHART_RIGHT]);
		nRetStep = 60060;
		break;
	case 60060:
		nRetStep = 61000;
		break;
    case 61000:
        //! PCB Z�� Wait ��ġ �̵�
		if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -61000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� ��� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

        g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
        nRetStep = 61500;
        break;

	case 61500:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 62000;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -61000;
			break;
		}
		break;
    case 62000:

		if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//���� ���� ���� Ȯ��  Chart
		{
			g_clMotorSet.StopAxisAll(m_nUnit);

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Vacuum Ȯ�� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -62000;
			break;
		}

		//��ü ��ȯ���� �ٲ�� 
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB CHART �˻� ��ġ�̵� ��� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		//��ũ �߸� �׸��� rotation ���� ���Ҽ� �־� ƼĪ �� �״�� ���� �ǰ� ���� 240621
		//
		//

		if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, CHART_POS, g_clTaskWork[m_nUnit].m_dSensorAlign[0], g_clTaskWork[m_nUnit].m_dSensorAlign[1], 0.0) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Chart �˻� ��ġ �̵� ��� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -62000;
			break;
		}

		nRetStep = 62500;
        break;

    case 62500:
        g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 63000;
        break;

    case 63000:
		if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//���� ���� ���� Ȯ��  Chart
		{
			g_clMotorSet.StopAxisAll(m_nUnit);

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Vacuum Ȯ�� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -63000;
			break;
		}
        //! PCB X,Y,T�� Chart �˻� ��ġ �̵� Ȯ��
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[CHART_POS].dPos[MOTOR_PCB_X] + g_clTaskWork[m_nUnit].m_dSensorAlign[0];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[CHART_POS].dPos[MOTOR_PCB_Y] + g_clTaskWork[m_nUnit].m_dSensorAlign[1];
		dPos[2] = g_clModelData[m_nUnit].m_stTeachData[CHART_POS].dPos[MOTOR_PCB_TH];// +g_clTaskWork[m_nUnit].m_dSensorAlign[2];

        if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_X) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_X) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Y) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Y) - dPos[1]) < ENCORDER_GAP)) &&
            (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TH) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TH) - dPos[2]) < ENCORDER_GAP)))
        {
            _stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Chart �˻���ġ�̵� �Ϸ� [STEP : %d]"), nStep);
            AddLog(szLog, 0, m_nUnit);

			if (g_clModelData[m_nUnit].m_nDryRunMode == 1 && g_clTaskWork[m_nUnit].m_nRetryCount == 0)	//�ݺ��� Chart Pos ����
			{
				for (i = 0; i < MAX_MOTOR_COUNT; i++)
				{
					g_clMesCommunication[m_nUnit].m_dGrrMotorPos[i] = g_clMotorSet.GetEncoderPos(m_nUnit, i);
				}
				
			}
            nRetStep = 63050;
            break;
        }
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
        {
            _stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB X,Y,T�� Chart �˻� ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
            AddLog(szLog, 1, m_nUnit, true);

            nRetStep = -62000;
            break;
        }
        break;
	case 63050:
		if (g_clModelData[m_nUnit].m_nLaserOutUse == 1)	//������ ��� o
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LASER TILT PASS [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 63150;
			break;
		}
		if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, CHART_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� CHART_POS �̵� ��� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -63050;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� CHART_POS �̵� ��� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 63100;
		break;
	case 63100:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[CHART_POS].dPos[MOTOR_PCB_TX];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[CHART_POS].dPos[MOTOR_PCB_TY];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TX) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TX) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TY) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TY) - dPos[1]) < ENCORDER_GAP)))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� CHART_POS ��ġ �̵� �Ϸ� [STEP : %d"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 63150;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� CHART_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -63050;
			break;
		}
		break;
	case 63150:

		nRetStep = 63200;
		break;

	case 63200:
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� CHART_POS ��ġ �̵� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		if (g_clMotorSet.MovePcbZMotor(m_nUnit, CHART_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� CHART_POS ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -63200;
			break;
		}

		
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 63400;
		break;
	case 63400:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[CHART_POS].dPos[MOTOR_PCB_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� CHART_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 63500;

			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� CHART_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -63200;
			break;
		}
		break;
    case 63500:

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] YUV CHART INSP START [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clPriInsp[m_nUnit].func_Insp_CurrentMeasure(true);	//eol

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] CURRENT READ �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clTaskWork[m_nUnit].m_nRetryCount = 0;
		nRetStep = 63900;/// 64000;


		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
        break;

	case 63900:
		if (g_clLaonGrabberWrapper[m_nUnit].GetCurrentState() == CCD_GRAB_LIVE)
		{
			Sleep(500);
			nRetStep = 64000;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > 40000)	//10�� ->30��
		{
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1069);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] CCD OPEN ����.��ǰ ���� ���� �� ��ǰ �ҷ��� Ȯ���ϼ���. [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -64000;
			break;
		}
		break;

	case 64000:		//<-----------RETRY �ݺ� ���� 
		//ó�� ������ ���� ��ũ ã��
		g_clVision.ClearOverlay(m_nUnit);
		
		//if (g_FindCirclePos(m_nUnit, g_clVision.m_pImgBuff[m_nUnit][1], g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle) == false)	//AutoChartInsp
		//{

		//���� ������ũ ���н� ��� 
		//if (g_OpencvFindCirclePos(m_nUnit, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle) == false)


		if (g_MilFindCirclePos(m_nUnit, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle) == false)		//YUV ROTATION
		{
			g_clVision.DrawOverlayAll(m_nUnit);
			g_clLaonGrabberWrapper[m_nUnit].CloseDevice();
			Sleep(300);

			//241022
			////if (g_clTaskWork[m_nUnit].m_nCcdCount < g_clModelData[m_nUnit].m_nCcdRetryCount)			//PROCESS
			////{
			////	g_clLaonGrabberWrapper[m_nUnit].CloseDevice();
			////	g_clTaskWork[m_nUnit].m_nCcdCount++;
			////	Sleep(1000);
			////	_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD] Retry %d/%d"), g_clTaskWork[m_nUnit].m_nCcdCount, g_clModelData[m_nUnit].m_nCcdRetryCount);
			////	AddLog(szLog, 0, m_nUnit);


			////	if (g_pCarAABonderDlg->m_clCustomThread[m_nUnit].GetThreadRunning() == false)
			////	{
			////		g_pCarAABonderDlg->m_clCustomThread[m_nUnit].CustomThreadrun(CCD_THREAD);
			////	}
			////	else
			////	{
			////		g_pCarAABonderDlg->m_clCustomThread[m_nUnit].EndThread();
			////	}

			////	nRetStep = 63900;
			////	g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			////	break;
			////}
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1070);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] ���� ��ũ Ȯ�� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -64000;
			break;
		}
		//}


		g_clVision.DrawOverlayAll(m_nUnit);

		if (g_clTaskWork[m_nUnit].m_nRetryCount == 0)
		{
			//Yuv Rotation Get
			g_CheckEolRotation(m_nUnit);		//auto
		}
		g_CalcImageAlign(m_nUnit);	//th���� ���� �߰�
		nRetStep = 64500;
		break;
	case 64500:
		//th����
		thcount = 1 - (g_clTaskWork[m_nUnit].m_nRetryCount * 0.2);
		if (thcount < 0.1)
		{
			thcount = 0.1;
		}
		if (thcount > 1.0)
		{
			thcount = 0.8;
		}
//#ifdef KUMI_TEST_MODE
//#if (____MACHINE_NAME == MODEL_OHC_150)		//ok
//		//100�� ��ǰ 180�� ȸ������ �����̼� �ݴ�
//		///thcount *= -1;
//#endif
//#else
//#if (____MACHINE_NAME == MODEL_FRONT_100)		//ok 
//		//100�� ��ǰ 180�� ȸ������ �����̼� �ݴ�
//		//thcount *= -1;
//#endif
//#endif




		if (g_clMotorSet.MovePcbTMotor(m_nUnit, g_clTaskWork[m_nUnit].m_dImgShiftTh * thcount, true) == false)
		{
			g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1071);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TH�� SFR ���� SHIFT(%.03lf) ���� ���� [STEP : %d]"),g_clTaskWork[m_nUnit].m_dImgShiftTh, nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -64500;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TH�� SFR ���� SHIFT(%.03lf) ���� [STEP : %d]"), g_clTaskWork[m_nUnit].m_dImgShiftTh, nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		g_clTaskWork[m_nUnit].m_nRetryCount++;
		nRetStep = 64600;
		break;
	case 64600:
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > 500)
		{
			nRetStep = 64700;
		}
		break;
	case 64700:
		if (fabs(g_clTaskWork[m_nUnit].m_dImgShiftTh) > 0.03)
		{
			if (g_clTaskWork[m_nUnit].m_nRetryCount < 10)
			{

				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TH�� ���� RETRY:%d [STEP : %d]"), g_clTaskWork[m_nUnit].m_nRetryCount, nStep);
				AddLog(szLog, 0, m_nUnit);
				nRetStep = 64000;
				break;
			}
			else
			{
				g_pCarAABonderDlg->m_clUbiGemDlg.AlarmSendFn(1072);
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TH�� ����(%.03lf) ���� [STEP : %d]"), g_clTaskWork[m_nUnit].m_dImgShiftTh, nStep);
				AddLog(szLog, 1, m_nUnit, true);

				nRetStep = -64500;
				break;
			}
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TH�� SFR ���� SHIFT(%.03lf) ���� �Ϸ�[STEP : %d]"), g_clTaskWork[m_nUnit].m_dImgShiftTh, nStep);
		AddLog(szLog, 0, m_nUnit);
		nRetStep = 64800;

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		break;

	case 64800:
		
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > 300)
		{
			g_clLaonGrabberWrapper[m_nUnit].CopyInspImage(CHART_YUV_IMAGE, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer);		//Yuv Chart Image
			nRetStep = 65000;
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		}

		
		break;
	case 65000:
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > 100)
		{
			nRetStep = 65100;
		}
		break;
	case 65100:

		g_clVision.ClearOverlay(m_nUnit);
		//if (g_FindCirclePos(m_nUnit, g_clVision.m_pImgBuff[m_nUnit][1], g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle) == false)		//AutoChartInsp
		//{
		//if (g_OpencvFindCirclePos(m_nUnit, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle) == false)


		if (g_MilFindCirclePos(m_nUnit, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle) == false)		//YUV OC
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] ��Ʈ ���� ��ũ Ȯ�� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -65000;
			break;
		}
		//}
		g_clVision.DrawOverlayAll(m_nUnit);
		//
		//
		//
		//Yuv Image OC ����
		//
		//
		//
		g_CheckEolOc(m_nUnit);


		nRetStep = 65200;
		break;
	
	case 65200:
		
		nRetStep = 65500;
		break;
	case 65500:
		//YUV FOV �˻� �߰�
		g_clPriInsp[m_nUnit].FnShmFastCornerFind(g_clLaonGrabberWrapper[m_nUnit].vYuvChartBuffer);					//YUV AUTO

		g_clPriInsp[m_nUnit].func_Insp_Shm_Fov_Distortion(g_clLaonGrabberWrapper[m_nUnit].vYuvChartBuffer, true);		//YUV AUTO 

		g_clMesCommunication[m_nUnit].g_FovVertexLog(m_nUnit);

		nRetStep = 66000;
		break;
    case 66000:
		nRetStep = 66300;
		break;

	case 66300:
		//Yuv image
		//--------------- Color Reproduction 
		g_clPriInsp[m_nUnit].func_Insp_Color_reproduction(g_clLaonGrabberWrapper[m_nUnit].vYuvChartBuffer, true);	//EOL YUV

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Color Reproduction �˻� �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		nRetStep = 66400;
		break;
	case 66400:
		nRetStep = 67000;
		break;

    case 67000:
		g_clPriInsp[m_nUnit].func_Insp_ErrorFlag_Read();//AUTO EOL YUV
		nRetStep = 67100;
        break;
	case 67100:
		nRetStep = 67200;
		break;
	case 67200:
		
		g_clVision.ClearOverlay(m_nUnit);
		g_clVision.DrawOverlayAll(m_nUnit);
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] YUV CHART INSP COMPLETE [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].InitSfrInsp();

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		g_clTaskWork[m_nUnit].m_nRetryCount = 0;
		nRetStep = 67300;

		break;
	case 67300:
		//Raw �� ��ȯ
		//ccd close
		g_clLaonGrabberWrapper[m_nUnit].CloseDevice();
		//ini load

		g_clLaonGrabberWrapper[m_nUnit].UiconfigLoad(INI_RAW_IMAGE);	//auto chart
		g_clLaonGrabberWrapper[m_nUnit].SelectSensor();
		g_clLaonGrabberWrapper[m_nUnit].AllocImageBuff();
		g_clLaonGrabberWrapper[m_nUnit].rawReSet(0);				//2. RAW AutoChartInsp
		
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 67400;
		break;
	case 67400:
		//ccd start
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > 100)
		{
			if (g_pCarAABonderDlg->m_clCustomThread[m_nUnit].GetThreadRunning() == false)
			{
				g_pCarAABonderDlg->m_clCustomThread[m_nUnit].CustomThreadrun(CCD_THREAD);
			}
			else
			{
				g_pCarAABonderDlg->m_clCustomThread[m_nUnit].EndThread();
			}
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			nRetStep = 67500;
		}
		
		break;
    case 67500:
		if (g_clLaonGrabberWrapper[m_nUnit].GetCurrentState() == CCD_GRAB_LIVE)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] RAW CHART INSP START [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			Sleep(200);

			nRetStep = 67550;
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > 40000)//10000)	//10��
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] CCD OPEN ����. ��ǰ ���� ���� �� ��ǰ �ҷ��� Ȯ���ϼ���. [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -67400;
			break;
		}
		
        break;
	case 67550:
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > 300)
		{
			nRetStep = 67600;

		}
		
		break;
	case 67600:
		if (g_clModelData[m_nUnit].m_nRawSumCount == 0)
		{
			g_clLaonGrabberWrapper[m_nUnit].CopyInspImage(CHART_RAW_IMAGE, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, false);//false 241125	//Raw Chart Image ,true�� ����̹���

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] CHART IMAGE CAPTURE PASS [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
		}
		else
		{
			if (rawSumCount < g_clModelData[m_nUnit].m_nRawSumCount && rawSumCount < 10)	//10�� max
			{
				memcpy(g_clLaonGrabberWrapper[m_nUnit].pSumBuffer[rawSumCount], g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize());
				rawSumCount++;
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] CHART IMAGE CAPTURE #%d [STEP : %d]"), rawSumCount, nStep);
				AddLog(szLog, 0, m_nUnit);
				nRetStep = 67550;
				g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
				break;
			}

			ACMISSoftISP::AverageImage(&g_clLaonGrabberWrapper[m_nUnit].pSumBuffer[0],
				g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nWidth,
				g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nHeight,
				g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n, g_clModelData[m_nUnit].m_nRawSumCount,
				g_clLaonGrabberWrapper[m_nUnit].vRawChartBuffer);

			g_clLaonGrabberWrapper[m_nUnit].CopyInspImage(CHART_RAW_IMAGE, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer);	//Raw Chart Image ,true�� ����̹���
			
		}
		nRetStep = 67620;
		break;

	case 67620:
		nRetStep = 67650;
		break;
	case 67650:

		g_clPriInsp[m_nUnit].func_Insp_LightTest(0);

		nRetStep = 67700;
		break;
	case 67700:
		//
		//
		g_GetSFR(g_clLaonGrabberWrapper[m_nUnit].vRawChartBuffer, m_nUnit, SFR_FINAL);		//EOL RAW IMAGE SFR �˻�

		g_pCarAABonderDlg->_DrawBarGraph(m_nUnit);
		///g_CalcImageAlign(m_nUnit);		//?240628

		nDiffRetry = 0;
		bNgDiffView = false;
		g_clTaskWork[m_nUnit].m_nRetryCount = 0;

		nRetStep = 67750;
		break;
	case 67750:
		if (g_clModelData[m_nUnit].m_nDiffRetryCount < 1 || nDiffRetry >= g_clModelData[m_nUnit].m_nDiffRetryCount)
		{
			bNgDiffView = true;		//������ ��Ʈ������ �� NG ǥ�� ����
		}
		m_nDiffTestOk = g_GetSfrMinMaxValue(m_nUnit, bNgDiffView);		//���� diff �˻�

		if (m_nDiffTestOk == true)		//DIFF SPEC IN
		{
			nRetStep = 68000;	//DIFF SPEC IN OK
			break;
		}
		else
		{
			//--DIFF NG NG
			if (nDiffRetry < g_clModelData[m_nUnit].m_nDiffRetryCount)
			{
				nDiffRetry++;
				g_clTaskWork[m_nUnit].m_nRetryCount = 0;
				_stprintf_s(szLog, SIZE_OF_1K, _T("[DIFF] RETRY :%d [STEP : %d]"), nDiffRetry, nStep);
				AddLog(szLog, 0, m_nUnit);

				g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();

				nRetStep = 67800;
				break;
			}

			nRetStep = 68000;	//DIFF RETRY OVER
			break;
		}
		
		break;
	case 67800:
		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > 30)
		{
			nRetStep = 67840;
		}
		break;
	case 67840:
		if (g_clTaskWork[m_nUnit].m_nRetryCount < 10)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[DIFF] SFR TEST :%d [STEP : %d]"), g_clTaskWork[m_nUnit].m_nRetryCount + 1, nStep);
			AddLog(szLog, 0, m_nUnit);

			g_AvrGetSFR(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clTaskWork[m_nUnit].m_nRetryCount);

			g_clTaskWork[m_nUnit].m_nRetryCount++;
			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
			nRetStep = 67800;
			break;
		}
		else
		{
			nRetStep = 67750;	//DIFF �ٽ� ����
		}
		break;
	case 67900:
		
		nRetStep = 68000;
		break;

    case 68000://jump step 
		g_clPriInsp[m_nUnit].func_Insp_Version_Read();//AUTO 
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] RAW CHART INSP COMPLETE [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

        nRetStep = 69000;
        break;

	case 69000:	
		//! PCB Z�� Wait ��ġ �̵�
		if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -69000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� ��� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 69100;
		break;

	case 69100:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 69600;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -69000;
			break;
		}
		break;
	case 69600:
		
		nRetStep = 69900;
		break;
    case 69900:
		g_clVision.ClearOverlay(m_nUnit);
		g_clVision.DrawOverlayAll(m_nUnit);
        nRetStep = 80000;
        break;
    default:
        _stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] CHART TEST �̻� STEP �߻� [STEP : %d]"), nStep);
        AddLog(szLog, 0, m_nUnit);
        nRetStep = -1;
        break;
    }

    return nRetStep;
}



//-----------------------------------------------------------------------------
//
//	FCM30_AAB AA(70000 ~ 80000)	
//
//-----------------------------------------------------------------------------
int CPcbProcess::AutoFocus(int nStep)
{
	TCHAR szLog[SIZE_OF_1K];
	double dMoveDist = 0.0;
	double dMoveVel = 0.0;
	double dMoveAcc = 0.0; 
	int nRetStep;
	
	nRetStep = nStep;

	return nRetStep;
}





//-----------------------------------------------------------------------------
//
//	EOL Final SFR(80000 ~ 90000)
//
//-----------------------------------------------------------------------------
int CPcbProcess::AutoEOLFinalSFR(int nStep)
{
	TCHAR szLog[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;
	CString sMsg = _T("");
	double dOcResult[2] = {0.0, 0.0};
	double dPos[3] = { 0.0, 0.0, 0.0 };
	int nRetStep;
	bool bRtn = false;
	nRetStep = nStep;

	switch (nStep)
	{
	case 110000:
		g_clTaskWork[m_nUnit].m_nRetryCount = 0;
		g_clTaskWork[m_nUnit].m_dwInspTactTime = GetTickCount();


		nRetStep = 111000;
		break;
	case 111000:
		if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -111000;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� ��� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 112000;
		break;
	case 112000:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[MOTOR_PCB_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 112200;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� WAIT_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -111000;
			break;
		}

		break;
	case 112200:
		if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, UNLOAD_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� UNLOAD_POS �̵� ��� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -112200;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� UNLOAD_POS �̵� ��� ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 112400;
		break;

	case 112400:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[UNLOAD_POS].dPos[MOTOR_PCB_TX];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[UNLOAD_POS].dPos[MOTOR_PCB_TY];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TX) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TX) - dPos[0]) < ENCORDER_GAP)) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TY) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TY) - dPos[1]) < ENCORDER_GAP)))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� UNLOAD_POS ��ġ �̵� �Ϸ� [STEP : %d"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 113500;
			break;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB TX,TY�� UNLOAD_POS ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -112200;
			break;
		}
		break;
	case 113500:
		if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//���� ���� ���� Ȯ��  �����
		{
			g_clMotorSet.StopAxisAll(m_nUnit);

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Vacuum Ȯ�� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -113500;
			break;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB X,Y,TH�� UNLOAD_POS �̵� ��� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, UNLOAD_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB X,Y,TH�� UNLOAD_POS �̵� ��� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -113500;
			break;
		}

		g_clPriInsp[m_nUnit].func_Insp_Test_SensorRead(true);		//eol
		nRetStep = 114000;
		break;
	case 114000:

		g_clPriInsp[m_nUnit].func_Insp_Supply_Voltage_Read(true);		//eol
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Supply VOLTAGE READ �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		

		nRetStep = 114050;
		break;
	case 114050:
		g_clPriInsp[m_nUnit].func_Insp_Sensor_Voltage_Read(true);		//eol
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Sensor VOLTAGE READ �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		

		nRetStep = 114100;
		break;
	case 114100:

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Firmware Verify ���� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		g_clVision.ClearOverlay(m_nUnit);

		g_clVision.DrawMOverlayText(0, g_clModelData[m_nUnit].m_nWidth * 0.1, 300, _T("Checking Firmware"), M_COLOR_YELLOW, _T("Arial"), 40, 80);
		g_clVision.DrawOverlayAll(m_nUnit);


		g_ShowCloseMsgPopup(_T("INFO"), _T("[AUTO] Firmware �˻� �������Դϴ�."), true);

		g_clPriInsp[m_nUnit].func_Insp_FirmwareVerify(true);

		g_ShowCloseMsgPopup(_T("INFO"), _T("[AUTO] Firmware �˻� �������Դϴ�."), false);


		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Firmware Verify �Ϸ� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);


		nRetStep = 114500;
		break;

	case 114500:
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 115000;
		break;
	case 115000:

		if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//���� ���� ���� Ȯ��  �����
		{
			g_clMotorSet.StopAxisAll(m_nUnit);

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Vacuum Ȯ�� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -115000;
			break;
		}
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[UNLOAD_POS].dPos[MOTOR_PCB_X];
		dPos[1] = g_clModelData[m_nUnit].m_stTeachData[UNLOAD_POS].dPos[MOTOR_PCB_Y];
		dPos[2] = g_clModelData[m_nUnit].m_stTeachData[UNLOAD_POS].dPos[MOTOR_PCB_TH];
		if ((g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_X) && (g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_X) - dPos[0]) < ENCORDER_GAP) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Y) && (g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Y) - dPos[1]) < ENCORDER_GAP) &&
			(g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_TH) && (g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_TH) - dPos[2]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB X,Y,TH�� UNLOAD_POS �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			if (g_clModelData[m_nUnit].m_nDryRunMode == 0)		//��� ����� ���� ����� Ż��
			{
				g_clDioControl.PcbVacuum(m_nUnit, false);//��ȸ�� ��尡 �ƴ� ���� Ż��
			}

			nRetStep = 115200;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB X,Y,TH�� UNLOAD_POS �̵� �ð��ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -113500;
			break;
		}
		
		break;
	case 115200:
		
		nRetStep = 115300;
		
		break;
	case 115300:
		
		nRetStep = 115320;
		break;
	case 115320:
		nRetStep = 115340;
		break;

	case 115340:
		nRetStep = 115400;
		break;
	case 115400:
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� ���� ��ġ �̵� [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);

		if (g_clMotorSet.MovePcbZMotor(m_nUnit, UNLOAD_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� ���� ��ġ �̵� ���� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -115400;
			break;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] CCD CLOSE [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_clLaonGrabberWrapper[m_nUnit].CloseDevice();

		nRetStep = 115600;
		break;
	case 115600:
		dPos[0] = g_clModelData[m_nUnit].m_stTeachData[UNLOAD_POS].dPos[MOTOR_PCB_Z];
		if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Z) && ((g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Z) - dPos[0]) < ENCORDER_GAP))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� ���� ��ġ �̵� �Ϸ� [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			nRetStep = 115800;
			break;
		}

		if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PCB Z�� ���� ��ġ �̵� �ð� �ʰ� [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -115400;
			break;
		}
		break;
	case 115800:
		nRetStep = 116000;
		break;
	case 116000:

		nRetStep = 116200;
		break;
	case 116200:
		
		bRtn = g_clMesCommunication[m_nUnit].g_FinalEolLog(m_nUnit);

		if (bRtn == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO]FinalLog File is Save Fail!!\n �α������� ���������� �ݾ��ּ���[STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);
			nRetStep = -116200;
			break;
		}
		else
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LOG SAVE COMPLETE! [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
		}



		//g_clMesCommunication[m_nUnit].m_dwCycleTactEndTime = GetTickCount();
		//g_clMesCommunication[m_nUnit].m_dwMesCycleTime = (g_clMesCommunication[m_nUnit].m_dwCycleTactEndTime - g_clMesCommunication[m_nUnit].m_dwCycleTactStartTime) / 1000;		//SEC

		nRetStep = 116300;
		//if (g_clMesCommunication[m_nUnit].MesEolSave(m_nUnit) == false)//mes ����
		//{
		//	_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] MES SAVE FAIL! \n��Ż���,LOT Ȯ�ιٶ��ϴ�[STEP : %d]"), nStep);
		//	AddLog(szLog, 1, m_nUnit, true);
		//	nRetStep = -116000;
		//	break;
		//}
		//else
		//{
		//	_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] MES SAVE COMPLETE! [STEP : %d]"), nStep);
		//	AddLog(szLog, 0, m_nUnit, false);

		//	nRetStep = 116500;
		//}
		break;
	case 116300:
		if (nRunOnlineControlState == false)
		{
			//Offline �̸� ���� Skip
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Equipment Offline State Apd Pass [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			nRetStep = 116500;
			break;
		}
		g_clTaskWork[m_nUnit].bRecv_S6F12_Lot_Apd = -1;
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot APD Report Send [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(LOT_APD_REPORT_10711);
		nRetStep = 116350;

		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		break;
	case 116350:
		if (g_clTaskWork[m_nUnit].bRecv_S6F12_Lot_Apd == 0)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot APD Send Acknowledge [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);

			g_clTaskWork[m_nUnit].bRecv_S6F12_Lot_Processing_Completed = -1;
			g_clTaskWork[m_nUnit].bRecv_S6F12_Lot_Processing_Completed_Ack = -1;
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot Processing Completed Report Send [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
			g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(LOT_PROCESSING_COMPLETED_REPORT_10710);//SEND S6F11
			nRetStep = 116400;

			g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > nRunTimeOutSec)
		{
			//g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(CT_TIMEOUT_REPORT_11002); //SEND S6F11
			g_pCarAABonderDlg->m_clUbiGemDlg.cTTimeOutSendFn(_T("S06F12"), _T("10711"));
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot APD Ct TimeOut [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -116300;
			break;
		}
		
		break;
	case 116400:
		g_clTaskWork[m_nUnit].m_dwPcbTickCount = GetTickCount();
		nRetStep = 116450;
		break;
	case 116450:
		if (g_clTaskWork[m_nUnit].bRecv_S6F12_Lot_Processing_Completed == 0)
		{
			if (g_clTaskWork[m_nUnit].bRecv_S6F12_Lot_Processing_Completed_Ack != 0)
			{
				//nack
				//
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot Processing Completed Fail [STEP : %d]"), nStep);
				AddLog(szLog, 0, m_nUnit);
				g_ShowMsgPopup(_T("[INFO]"), szLog, RGB_COLOR_RED);
			}
			else
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot Processing Completed OK [STEP : %d]"), nStep);
				AddLog(szLog, 0, m_nUnit);
			}


			//0 == OK, ACK
			nRetStep = 116500;
		}
		else if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > nRunTimeOutSec)
		{
			//g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(CT_TIMEOUT_REPORT_11002); //SEND S6F11
			g_pCarAABonderDlg->m_clUbiGemDlg.cTTimeOutSendFn(_T("S06F12"), _T("10710"));
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Lot Processing Completed Ct TimeOut [STEP : %d]"), nStep);
			AddLog(szLog, 1, m_nUnit, true);

			nRetStep = -116300;
			break;
		}
		
		break;

	case 116500:	//jump Step 

		g_clVision.ClearOverlay(m_nUnit);
		if (g_clMesCommunication[m_nUnit].m_nMesFinalResult == 1)	//��� ���� EOL
		{
			g_clTaskWork[m_nUnit].m_nEmission = 1; 
			g_clTaskWork[m_nUnit].SaveData();
			g_pCarAABonderDlg->ShowOkNgState(m_nUnit, g_clTaskWork[m_nUnit].m_nEmission);
			g_clVision.DrawMOverlayText(m_nUnit, 50, 100, _T("PASS"), M_COLOR_GREEN, _T("Arial"), 150, 80, FALSE);
			g_clTaskWork[m_nUnit].m_nTotalOkCount++;
			
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] ���� �Ǵ� : OK [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
		}
		else
		{
			g_clTaskWork[m_nUnit].m_nEmission = 2;
			g_clTaskWork[m_nUnit].SaveData();
			g_pCarAABonderDlg->ShowOkNgState(m_nUnit, g_clTaskWork[m_nUnit].m_nEmission);
			g_clVision.DrawMOverlayText(m_nUnit, g_clModelData[m_nUnit].m_nWidth * 0.55, 100, _T("FAIL"), M_COLOR_RED, _T("Arial"), 150, 80, FALSE);

			g_clMandoInspLog[m_nUnit].DrawNGOverlay(m_nUnit); //ȭ�� Overlay�� NG List Draw 

			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] ���� �Ǵ� : NG [STEP : %d]"), nStep);
			AddLog(szLog, 0, m_nUnit);
		}
		sprintf_s(szLog, "OC X :%.2lf / OC Y :%.2lf", g_clMandoInspLog[m_nUnit].m_UvAfter_OC_DelatX, g_clMandoInspLog[m_nUnit].m_UvAfter_OC_DelatY);
		AddLog(szLog, 0, m_nUnit);
		
		g_clVision.DrawMOverlayText(0, g_clModelData[m_nUnit].m_nWidth * 0.55, 700, szLog, M_COLOR_CYAN, _T("Arial"), 15, 20);
		g_clVision.DrawOverlayAll(m_nUnit);
		nRetStep = 117000;
		break;

	case 117000:
		g_clTaskWork[m_nUnit].m_IoRetry = 0;
		nRetStep = 117100;
		break;
	case 117100:
		nRetStep = 117200;
		break;

	case 117200:
		nRetStep = 119400;
		
		break;
	case 119400:
		//if (g_clModelData[m_nUnit].m_nDryRunMode == 1)
		//{
			//g_clMesCommunication[m_nUnit].g_Grr____LaserMotorPos(m_nUnit);
			//D:\\EVMS\\Log\\RESULT ����
		//}
		nRetStep = 119450;
		break;
	case 119450:
		nRetStep = 119500;
		break;
	case 119500:
		g_clTaskWork[m_nUnit].m_nTotalWorkCount++;
		g_clTaskWork[m_nUnit].SaveData();
		g_pCarAABonderDlg->ShowOutputCount(m_nUnit);
		nRetStep = 119800;
		break; 
	case 119800:
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] end Lot : %s [STEP : %d]"), g_clTaskWork[m_nUnit].m_szChipID, nStep);
		AddLog(szLog, 0, m_nUnit);
		if (g_clModelData[m_nUnit].m_nDryRunMode == 0)
		{
			g_clMesCommunication[m_nUnit].m_sMesLotID.Format(_T("EMPTY"));
			_stprintf_s(g_clTaskWork[m_nUnit].m_szChipID, SIZE_OF_100BYTE, _T("EMPTY")); //bcr �ʱ�ȭ
			g_pCarAABonderDlg->ShowBarcode(m_nUnit);
		}
		nRetStep = 30000;
		break;
    default:
        _stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] EOL FINAL �˻� �̻� STEP �߻�[STEP : %d]"), nStep); 
        AddLog(szLog, 0, m_nUnit);
        nRetStep = -1;
        break;
    }

    return nRetStep;

}

//-----------------------------------------------------------------------------
//
//	SFR���� �������� �϶��ϴ��� üũ
//
//-----------------------------------------------------------------------------
bool CPcbProcess::CheckDecreaseSFR()
{
	/*int nStartIndex;
	int nCheckIndex;
	int i, j;

	nCheckIndex = g_clModelData[m_nUnit].m_nCountOfCheckSFR;

	if (g_clTaskWork[m_nUnit].m_bFlagDecreaseSFR == true)
	{
		nStartIndex = g_clModelData[m_nUnit].m_nCountOfCheckSFR;
		nCheckIndex = g_clModelData[m_nUnit].m_nCountOfCheckSFR * 2;
	}
	else
	{
		nStartIndex = 0;
	}
	int FieldJumpStep = 0;

	for (i = nStartIndex; i < MAX_MTF_COUNT; i++)
	{
		if (g_clModelData[m_nUnit].m_nSfrMode == FIELD_085_AA && i > 0)
		{
			FieldJumpStep = 4;
		}
		for (j = nStartIndex; j < nCheckIndex; j++)
		{
			if (g_clTaskWork[m_nUnit].m_stSfrInsp.fSFR_AVR_N4[j][i + FieldJumpStep] >= 0.2)
				break;
		}

		if (j == nCheckIndex)
			continue;

		for (j = 1; j < nCheckIndex; j++)
		{
			if (g_clTaskWork[m_nUnit].m_stSfrInsp.fSFR_AVR_N4[j - 1][i + FieldJumpStep] - g_clTaskWork[m_nUnit].m_stSfrInsp.fSFR_AVR_N4[j][i + FieldJumpStep] < 0)
				break;
		}

		if (j == nCheckIndex)
			return false;
		else
			continue;
	}*/

	return true;
}

//-----------------------------------------------------------------------------
//
//	SFR������ MAX Z�� �� ã��
//
//-----------------------------------------------------------------------------
bool CPcbProcess::GetSfrMaxPos()
{

	return true;
}



//-----------------------------------------------------------------------------
//
//	FCM30_AAB UV(80000 ~ 90000)
//
//-----------------------------------------------------------------------------
int CPcbProcess::AutoUV(int nStep)
{
	TCHAR szLog[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];
	double dMoveDist = 0.0;
	double dMoveVel = 0.0;
	double dPos[4] = { 0.0, 0.0, 0.0, 0.0 };
	double curPos = 0.0;
	double dCenterPosX = 0.0;
	double dCenterPosY = 0.0;
	int nRetStep;
	bool mRtn = false;

	return 0;
}

