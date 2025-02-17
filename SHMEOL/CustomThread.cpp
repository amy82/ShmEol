#include "StdAfx.h"
#include "CustomThread.h"
#include "AutoInspDlg.h"
#include "GlobalDeclare.h"

CCustomThread::CCustomThread(void)
{
	m_nUnit = -1;
	CustomMode = 0;
	bCustomWorkRun = false;

	m_nCustomStartStep = 0;
	m_nCustomEndStep = 0;
	m_nCustomCurrentStep = 0;
}


CCustomThread::~CCustomThread(void)
{
}


//-----------------------------------------------------------------------------
//
//	스레드 생성자
//
//-----------------------------------------------------------------------------
void CCustomThread::ThreadConstructor()
{

}

//-----------------------------------------------------------------------------
//
//	스레드 소멸자
//
//-----------------------------------------------------------------------------
void CCustomThread::ThreadDestructor()
{
	
}
void CCustomThread::CustomThreadrun(int Mode)
{
	switch (Mode)
	{
	case CCD_THREAD:
		bCustomWorkRun = true;
		m_nCustomCurrentStep = m_nCustomStartStep = 10000;
		m_nCustomEndStep = m_nCustomStartStep + 10000;	//m_nCustomEndStep = 20000;
		StartThread();
		break;

	case CCD_RETRY_THREAD:
		bCustomWorkRun = true;
		m_nCustomCurrentStep = m_nCustomStartStep = 20000;
		m_nCustomEndStep = m_nCustomStartStep + 10000; 

		StartThread();
		break;

	/*case LENS_LASER_THREAD:
		bCustomWorkRun = true;
		m_nCustomCurrentStep = m_nCustomStartStep = 30000;
		m_nCustomEndStep = m_nCustomStartStep + 10000;

		StartThread();
		break;*/
	default:
		m_nCustomCurrentStep = 0;
		m_nCustomStartStep = 0;
		m_nCustomEndStep = 0;
		break;
	}
}
//-----------------------------------------------------------------------------
//
//	스레드 콜백
//
//-----------------------------------------------------------------------------
void CCustomThread::ThreadCallBack()
{
	if (bCustomWorkRun == false) return;
	//
	if ((m_nCustomCurrentStep >= m_nCustomStartStep) && (m_nCustomCurrentStep < m_nCustomEndStep))
	{
		if (m_nCustomCurrentStep >= 10000 && m_nCustomCurrentStep < 20000)
		{
			m_nCustomCurrentStep = this->CCD_Run(m_nCustomCurrentStep);		//CCD 영상
		}
		else
		{
			bCustomWorkRun = false;
			this->EndThread();
		}
	}
	else
	{
		bCustomWorkRun = false;
		this->EndThread();
	}
}



int CCustomThread::CCD_Run(int nStep)
{
	TCHAR szLog[SIZE_OF_1K];
	int nHomeFlag = 0;
	int nRetStep = 0;
	int i = 0;

	nRetStep = nStep;

	switch (nStep)
	{
	case 10000:
		//영상 CCD Start
		_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD] Device Open Start"));
		AddLog(szLog, 0, m_nUnit);
		//
		//
		if (g_clLaonGrabberWrapper[m_nUnit].OpenDevice() == false)
		{
			if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
			{
				if (g_clTaskWork[m_nUnit].m_nCcdCount < g_clModelData[m_nUnit].m_nCcdRetryCount)	//CCD RUN
				{
					Sleep(100);
					g_clLaonGrabberWrapper[m_nUnit].CloseDevice();
					Sleep(300);

					g_clTaskWork[m_nUnit].m_nCcdCount++;
					int _delay = g_clModelData[m_nUnit].m_dCcdDelay * 1000;
					Sleep(_delay);
					_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD] Retry %d/%d"), g_clTaskWork[m_nUnit].m_nCcdCount, g_clModelData[m_nUnit].m_nCcdRetryCount);
					AddLog(szLog, 0, m_nUnit);
					nRetStep = 10000;
					break;
				}
			}
			
			bCustomWorkRun = false;
			_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD] Device Open Fail"));
			AddLog(szLog, 0, m_nUnit);
			nRetStep = -10000;
			break;
		}
		//
		_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD] Device Open End")); AddLog(szLog, 0, m_nUnit);
		//
		nRetStep = 10100;
		Sleep(300);
		break;
	case 10100:
		_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD] Device Grab Start"));
		AddLog(szLog, 0, m_nUnit);
		//
		//
		if (g_clLaonGrabberWrapper[m_nUnit].StartGrabCcdProcess() == false)
		{
			bCustomWorkRun = false;
			_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD] CCD GRAB START FAIL")); AddLog(szLog, 1, m_nUnit);
			
			nRetStep = -10000;
			break;
		}
		else
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD] Device Grab End")); 
			AddLog(szLog, 0, m_nUnit);
			
			g_pCarAABonderDlg->m_clButtonExCcd[m_nUnit].state = 1;
			g_pCarAABonderDlg->m_clButtonExCcd[m_nUnit].Invalidate();
			nRetStep = 30000;
			break;
		}
		break;
	default:
		//_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL][DISPENSING] 수동 도포 이상 STEP 발생 (STEP:%d)\n([MANUAL][DISPENSING] Manual application abnormal STEP occurred)"), nStep);

		nRetStep = -1;
		break;
	}
	return nRetStep;
}



int CCustomThread::CCD_Retry_Run(int nStep)
{
	TCHAR szLog[SIZE_OF_1K];
	int nHomeFlag = 0;
	int nRetStep = 0;
	int i = 0;

	nRetStep = nStep;

	switch (nStep)
	{
	case 20000:
		//영상 CCD Start
		_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD] Retry Start")); AddLog(szLog, 0, m_nUnit);
		//
		//

		nRetStep = 20050;
		break;
	case 20050:
		//커택 다운
		nRetStep = 20100;
		break;
	case 20100:
		//커택 다운 확인
		_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD] Device Grab Start")); AddLog(szLog, 0, m_nUnit);
		break;
	case 20150:
		//딜레이
		nRetStep = 20200;
		break;
	case 20200:
		//컨택 상승
		nRetStep = 20100;
		break;
	case 20250:
		//컨택 상승 확인
		nRetStep = 20300;
		break;
	case 20300:
		//open 전 딜레이
		nRetStep = 20200;
		break;
	case 20350:
		//ccd open
		nRetStep = 20200;
		break;
	case 20400:
		//delay
		nRetStep = 20200;
		break;
	case 20450:
		//ccd start
		nRetStep = 20200;
		break;
	default:
		//_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL][DISPENSING] 수동 도포 이상 STEP 발생 (STEP:%d)\n([MANUAL][DISPENSING] Manual application abnormal STEP occurred)"), nStep);

		nRetStep = -1;
		break;
	}
	return nRetStep;
}

int CCustomThread::TPTest_Run(int nStep)
{
	TCHAR szLog[SIZE_OF_1K];
	int nHomeFlag = 0;
	int nRetStep = 0;
	int i = 0;
	double dPos[4] = { 0.0, 0.0, 0.0, 0.0 };
	double curPos = 0.0;

	nRetStep = nStep;

	switch (nStep)
	{
	case 20000:

		nRetStep = 21000;
		break;
	case 21000:
		/*if (g_clPriInsp[m_nUnit].func_Insp_TestPattern(false) == false)
		{
		AddLog(_T("[수동검사] I2C 검사 실패"), 1, m_nUnit);
		nRetStep = 23000;
		break;
		}*/
		nRetStep = 22000;
		break;
	case 22000:

		nRetStep = 23000;
		break;
	case 23000:

		_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] TP TESST END [STEP : %d]"), nStep);
		AddLog(szLog, 0, m_nUnit);
		nRetStep = 30000;
		break;
	}

	return nRetStep;
}

