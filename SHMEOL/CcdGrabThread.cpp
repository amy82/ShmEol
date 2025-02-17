#include "StdAfx.h"
#include "CcdGrabThread.h"

#include "Grabber\LAON\ConvertColor.h"

CCcdGrabThread::CCcdGrabThread(void)
{
}


CCcdGrabThread::~CCcdGrabThread(void)
{
}


//-----------------------------------------------------------------------------
//
//	스레드 생성자
//
//-----------------------------------------------------------------------------
void CCcdGrabThread::ThreadConstructor()
{	
	m_nFailCount = 0;
	m_nGrabIndex = 0;

	m_nCount = 0;
	g_clTaskWork[m_nUnit].grabFailCount = 0;
}

//-----------------------------------------------------------------------------
//
//	스레드 소멸자
//
//-----------------------------------------------------------------------------
void CCcdGrabThread::ThreadDestructor()
{
	
}

//-----------------------------------------------------------------------------
//
//	스레드 콜백
//
//-----------------------------------------------------------------------------
void CCcdGrabThread::ThreadCallBack()
{
#ifdef ON_LINE_GRABBER
//	INT64 nTimeStamp;	
	//unsigned int nFrameCount;
	//float fFrameRate = 0.0;
	//float fMbps = 0.0;
	//float fSensorFrameRate = 0.0;
	int nErrorCode = 0;			
	
	TDATASPEC tDataSpec;

	memset(&tDataSpec, 0x00, sizeof(TDATASPEC));

	// Grabber 연결 상태 체크
	if (g_clLaonGrabberWrapper[m_nUnit].GetDeviceOpen() == false)
		return;
		
	// Grabber 상태 체크
	if (g_clLaonGrabberWrapper[m_nUnit].GetCurrentState() <= CCD_GRAB_PAUSE)
		return;

	// Grabber Working Index
	if (g_clVision.m_nGrabIndex[m_nUnit] < 0)
		return;
	
	if (g_clVision.m_nCvtColorReadyIndex[m_nUnit] == 1) 
	{
		g_clVision.m_nCvtColorReadyIndex[m_nUnit] = 0;
	}
	if((GetTickCount() - m_dwTickCount) > 1000)
	{
        //fps Get
		g_clTaskWork[m_nUnit].m_fFps = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetSensorFrameRate();// fFrameRate;
		if (g_clTaskWork[m_nUnit].m_fFps < 0.1)
		{
			g_clTaskWork[m_nUnit].m_fFps = 0.01;
		}
		m_dwTickCount = GetTickCount();
		g_pCarAABonderDlg->DrawCcdFps(m_nUnit);
	}
	

    if (g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrame(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clLaonGrabberWrapper[m_nUnit].m_pFrameBMPBuffer))
    {
        g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.imageItp->imageData = (char*)g_clLaonGrabberWrapper[m_nUnit].m_pFrameBMPBuffer;
        // Grab 버퍼에 저장
        cvCopy(g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.imageItp, g_clLaonGrabberWrapper[m_nUnit].m_pGrabBuff[g_clVision.m_nGrabIndex[m_nUnit]]);

		g_clVision.m_nCvtColorReadyIndex[m_nUnit] = g_clVision.m_nGrabIndex[m_nUnit];
		g_clVision.m_nGrabIndex[m_nUnit]++;

		//g_pCarAABonderDlg->DrawCcdFps(m_nUnit);

		if (g_clVision.m_nGrabIndex[m_nUnit] >= 3)
			g_clVision.m_nGrabIndex[m_nUnit] = 0;
		m_nFailCount = 0;
		g_clTaskWork[m_nUnit].grabFailCount = 0;
		Sleep(5);
    }
#endif
}


//-----------------------------------------------------------------------------
//
//	GRAB 시작 시간 갱신
//
//-----------------------------------------------------------------------------
void CCcdGrabThread::UpdateGrabStartTime()
{
	m_dwStartTickCount = GetTickCount();
	m_nFailCount = 0;
	g_clTaskWork[m_nUnit].grabFailCount = 0;
}


//-----------------------------------------------------------------------------
//
//	GRAB Start
//
//-----------------------------------------------------------------------------
bool CCcdGrabThread::MIUCheck_process()
{
   // bThread_MIUCheckRun = true;
	TCHAR szLog[SIZE_OF_1K];
	/*if (g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.CurrentState != 0)
	{
		g_clLaonGrabberWrapper[m_nUnit].StopGrab();
	}*/
	if (g_clLaonGrabberWrapper[m_nUnit].OpenDevice() == false)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD] Device Open Fail"));
		AddLog(szLog, 1, m_nUnit);
		return false;
	}
	Sleep(500);

    
    if (g_clLaonGrabberWrapper[m_nUnit].StartGrabCcdProcess() == false)
    {
		_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD] CCD Open Process Fail"));
        AddLog(szLog, 1, m_nUnit);
    }

	g_pCarAABonderDlg->m_clCcdGrabThread[m_nUnit].UpdateGrabStartTime();








    //switch (g_clLaonGrabberWrapper[m_nUnit].GetCurrentState())
    //{
    //    // 정지상태
    //case CCD_GRAB_STOP:
    //    
    //    
    //    this->UpdateGrabStartTime();
    //    break;
    //    // 영상 GRAB 상태
    //case CCD_GRAB_LIVE:
    //    g_clLaonGrabberWrapper[m_nUnit].CloseDevice();
    //    g_clLaonGrabberWrapper[m_nUnit].SetCurrentState(CCD_GRAB_STOP);
    //    AddLog(_T("[CCD] StopGrab"), 1, m_nUnit);
    //    break;
    //    // 일시정지 상태
    //case CCD_GRAB_PAUSE:
    //    g_clLaonGrabberWrapper[m_nUnit].SetCurrentState(CCD_GRAB_LIVE);
    //    AddLog(_T("[CCD] CCD_GRAB_LIVE"), 1, m_nUnit);
    //    break;
    //default:
    //    break;
    //}

   // bThread_MIUCheckRun = false;

    return true;
}