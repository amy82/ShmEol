#include "StdAfx.h"
#include "MonitorThread.h"


CMonitorThread::CMonitorThread(void)
{
	int i = 0;

	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		m_bPrevOrgFlag[i] = false;
	}
	m_bPrevDoorState = 0;
	m_bPrevVacuumState = false;
	m_bPrevArea = false;
	m_bLampFlick = false;

	iSlaveNo = 0;
	uLatch = 0;


	m_nPortNo = 7;// ConfigData.iCommPort[COMM_SENSOR_LIGHT];
}


CMonitorThread::~CMonitorThread(void)
{
}


//-----------------------------------------------------------------------------
//
//	
//
//-----------------------------------------------------------------------------
void CMonitorThread::ThreadConstructor()
{

}

//-----------------------------------------------------------------------------
//
//	스레드 소멸자
//
//-----------------------------------------------------------------------------
void CMonitorThread::ThreadDestructor()
{

}

//-----------------------------------------------------------------------------
//
//	스레드 콜백
//
//-----------------------------------------------------------------------------
void CMonitorThread::ThreadCallBack()
{	
#ifdef ON_LINE_DIO


	g_clDioControl.ReadDIn(0);

	this->CheckDioState();
	// 운전상태 체크(타워램프)
	this->CheckAutoRunState();
	

	this->CheckCurtainState();
	this->CheckPcbVacuumBbState();




	if (m_bPrevArea != g_clTaskWork[0].m_bAreaSensorRun)
	{
		if (g_clTaskWork[0].m_bAreaSensorRun == true)		//CMonitorThread
		{
			g_pCarAABonderDlg->m_clButtonExArea[0].state = 11;
		}
		else
		{
			g_pCarAABonderDlg->m_clButtonExArea[0].state = 0;
			
		}
	}
	if (m_bPrevArea != g_clTaskWork[0].m_bAreaSensorRun)
	{
		m_bPrevArea = g_clTaskWork[0].m_bAreaSensorRun;
		g_pCarAABonderDlg->m_clButtonExArea[0].Invalidate();
	}
	Sleep(10);


	
#endif

}
//-----------------------------------------------------------------------------
//
//   운전상태 체크(타워램프)
//
//-----------------------------------------------------------------------------
void CMonitorThread::CheckAutoRunState()
{
	int i = 0; 
	//bool bAutocheck = true;
	//for (i = 0; i < MAX_UNIT_COUNT; i++)
	//{
	//	if (g_clTaskWork[UNIT_AA1].m_nAutoFlag != MODE_AUTO)
	//	{
	//		bAutocheck = false;
	//	}
	//}
	//if (bAutocheck == true)
	//{
	//	//두파라 모도 자동운전중
	//}
	if (g_clTaskWork[UNIT_AA1].m_nAutoFlag == MODE_AUTO)
	{
		return;
	}

	if (g_clTaskWork[UNIT_AA1].m_nAutoFlag == MODE_PAUSE)
	{
		// LAMP RED FLICK

		if ((GetTickCount() - m_dwTickCount) > 300)
		{
			if (m_bLampFlick == false)
			{
				g_clDioControl.SetTowerLamp(LAMP_RED, true);
			}
			else
			{
				g_clDioControl.SetTowerLamp(LAMP_OFF, false);
			}
			m_bLampFlick = !m_bLampFlick;

			m_dwTickCount = GetTickCount();
		}
	}
	if (g_clTaskWork[UNIT_AA1].m_nAutoFlag == MODE_AUTO)
	{
		g_clDioControl.SetTowerLamp(LAMP_GREEN, true);
	}

	//
	//

#if 0
	if (g_clTaskWork[UNIT_AA1].m_nAutoFlag == MODE_STOP)
	{
		g_clDioControl.SetTowerLamp(LAMP_RED, true);
	}
	else if (g_clTaskWork[UNIT_AA1].m_nAutoFlag == MODE_AUTO)
	{
		g_clDioControl.SetTowerLamp(LAMP_GREEN, true);
	}
	else if (g_clTaskWork[UNIT_AA1].m_nAutoFlag == MODE_READY)
	{
		// LAMP GREEN FLICK

		if ((GetTickCount() - m_dwTickCount) > 300)
		{
			if (m_bLampFlick == false) 
			{
				g_clDioControl.SetTowerLamp(LAMP_YELLOW, true);
			}
			else 
			{
				g_clDioControl.SetTowerLamp(LAMP_OFF, false);
			}
			m_bLampFlick = !m_bLampFlick;

			m_dwTickCount = GetTickCount();
		}
	}
	else if (g_clTaskWork[UNIT_AA1].m_nAutoFlag == MODE_PAUSE)
	{
		// LAMP GREEN FLICK

		if ((GetTickCount() - m_dwTickCount) > 300)
		{
			if (m_bLampFlick == false)
			{
				g_clDioControl.SetTowerLamp(LAMP_RED, true);
			}
			else
			{
				g_clDioControl.SetTowerLamp(LAMP_OFF, false);
			}
			m_bLampFlick = !m_bLampFlick;

			m_dwTickCount = GetTickCount();
		}
	}
	else
	{
		g_clDioControl.SetTowerLamp(LAMP_YELLOW, true);
	}
#endif
}



void CMonitorThread::CheckCurtainState()
{
	if (g_clTaskWork[UNIT_AA1].m_nCurrentPcbStep >= 30120 && g_clTaskWork[UNIT_AA1].m_nCurrentPcbStep < 30125)
	{
		g_clTaskWork[0].m_bAreaSensorRun = false;		//CheckCurtainState
		return;
	}

	if (g_clTaskWork[UNIT_AA1].m_nAutoFlag == MODE_AUTO)
	{
		g_clTaskWork[0].m_bAreaSensorRun = true;	//CheckCurtainState
		if (g_clDioControl.CurtainDoorCheck(UNIT_AA1, true) == true)		//CMonitorThread
		{
			TCHAR szLog[SIZE_OF_1K];
			g_pCarAABonderDlg->PauseAutoProcess(UNIT_AA1);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[ERROR] 자동 운전 중 CURTAIN 감지. 일시 정지"));
			AddLog(szLog, 1, UNIT_AA1, true);
			return;
		}
	}




}

//-----------------------------------------------------------------------------
//
//   DIO 상태 모니터
//
//-----------------------------------------------------------------------------
void CMonitorThread::CheckDioState()
{
#ifdef ON_LINE_DIO
	TCHAR szLog[SIZE_OF_1K];
	int bState = 0;

	bState = g_clDioControl.GetDoorState();	// 다 닫겨있으면 true, 열리면 false.

	if (bState != m_bPrevDoorState)			// 초기 m_bPrevDoorState = false;
	{
		if (bState > 0)//// == false)
		{
			//g_clDioControl.LGDoorSignalOn(true);

			g_pCarAABonderDlg->m_clButtonExDoor[UNIT_AA1].state = 1;

			if (g_clModelData[UNIT_AA1].m_nDoorLockUse == 1)
			{
				if (g_clTaskWork[UNIT_AA1].m_nAutoFlag == MODE_AUTO)
				{
					g_pCarAABonderDlg->PauseAutoProcess(UNIT_AA1);
					_stprintf_s(szLog, SIZE_OF_1K, _T("[ERROR] 자동 운전 중 DOOR 열림. UNIT%d 일시 정지함") , UNIT_AA1 + 1);
					AddLog(szLog, 1, UNIT_AA1, true);
				}
			}
		}
		else
		{
			//g_clDioControl.LGDoorSignalOn(false);
			g_pCarAABonderDlg->m_clButtonExDoor[UNIT_AA1].state = 0;
		}

	}

	if (m_bPrevDoorState != bState)
	{
		m_bPrevDoorState = bState;
		g_pCarAABonderDlg->m_clButtonExDoor[UNIT_AA1].Invalidate();
	}
#endif
}

void CMonitorThread::CheckPcbVacuumBbState()
{
#ifdef ON_LINE_DIO
		if (g_clTaskWork[UNIT_AA1].m_nAutoFlag == MODE_AUTO && g_clTaskWork[UNIT_AA1].m_nCurrentPcbStep != 30120)
		{
			return;
		}
		bool bState = false;
		bState = g_clDioControl.PcbStopButtonCheck(UNIT_AA1, true);
		if (bState != m_bPrevVacuumState)
		{
			if (bState == true)
			{
				int offset = 8;		// DIO_OUT_PCB_VACUUM_ON
				int nrtn = g_clDioControl.ReadBitIn(1, offset);	//흡착 , 탈착 OUT 신호 확인

				if (nrtn == 1)	//DIO_OUT_PCB_VACUUM_ON : ON 상태
				{
					g_clDioControl.PcbVacuum(UNIT_AA1, false);
				}
				else if (nrtn == 0)	//DIO_OUT_PCB_VACUUM : OFF 상태
				{
					g_clDioControl.PcbVacuum(UNIT_AA1, true);
				}
			}
			//흡착 , 탈착
			//DIO_OUT_PCB_VACUUM_ON = on상태면 off
			//DIO_OUT_PCB_VACUUM_OFF = off 상태면 on 하기
			m_bPrevVacuumState = bState;
		}

#endif
}
//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
