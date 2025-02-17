#include "StdAfx.h"
#include "CcdCvtColorThread.h"


CCcdCvtColorThread::CCcdCvtColorThread(void)
{
}


CCcdCvtColorThread::~CCcdCvtColorThread(void)
{
}

//-----------------------------------------------------------------------------
//
//	스레드 생성자
//
//-----------------------------------------------------------------------------
void CCcdCvtColorThread::ThreadConstructor()
{

}

//-----------------------------------------------------------------------------
//
//	스레드 소멸자
//
//-----------------------------------------------------------------------------
void CCcdCvtColorThread::ThreadDestructor()
{

}

//-----------------------------------------------------------------------------
//
//	스레드 콜백
//
//-----------------------------------------------------------------------------
void CCcdCvtColorThread::ThreadCallBack()
{
#ifdef ON_LINE_GRABBER
	

	if (g_clLaonGrabberWrapper[m_nUnit].GetDeviceOpen() == false)
		return;

	/*if (g_clLaonGrabberWrapper[m_nUnit].GetCurrentState() <= CCD_GRAB_PAUSE)
		return;*/

	if (g_clVision.m_nGrabIndex[m_nUnit] == g_clVision.m_nCvtColorReadyIndex[m_nUnit])
	{
		Sleep(50);
		return;
	}

	if (g_clVision.m_nCvtColorReadyIndex[m_nUnit] < 0 || g_clVision.m_nCvtColorReadyIndex[m_nUnit] >= 3)
	{
		Sleep(50);
		return;
	}

	cvSplit(g_clLaonGrabberWrapper[m_nUnit].m_pGrabBuff[g_clVision.m_nCvtColorReadyIndex[m_nUnit]],
		g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[0],
		g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[1],
		g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[2],
		NULL);

#ifdef ON_LINE_MIL
		MbufPut(g_clVision.m_MilCcdProcChild[m_nUnit][0], g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[2]->imageData);
		MbufPut(g_clVision.m_MilCcdProcChild[m_nUnit][1], g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[1]->imageData);
		MbufPut(g_clVision.m_MilCcdProcChild[m_nUnit][2], g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[0]->imageData);


		double dZoomX = 0.0;
		double dZoomY = 0.0;

		dZoomX = ((double)CCD2_DISP_SIZE_X / (double)g_clModelData[m_nUnit].m_nWidth);
		dZoomY = ((double)CCD2_DISP_SIZE_Y / (double)g_clModelData[m_nUnit].m_nHeight);
		MimResize(g_clVision.m_MilCcdProcImage[m_nUnit], g_clVision.m_MilSmallImage[m_nUnit], dZoomX, dZoomY, M_DEFAULT);
#endif	

#endif

	g_clVision.m_nCvtColorReadyIndex[m_nUnit] = 1;
}