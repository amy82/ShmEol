#include "StdAfx.h"
#include "VisionGrabThread.h"

LONG64   Channel[] = { M_CH0, M_CH1 };
LONG64 Counter = 0;
CVisionGrabThread::CVisionGrabThread(void)
{
	m_nUnit = 0;
}


CVisionGrabThread::~CVisionGrabThread(void)
{
}

//-----------------------------------------------------------------------------
//
//	스레드 생성자
//
//-----------------------------------------------------------------------------
void CVisionGrabThread::ThreadConstructor()
{
#ifdef ON_LINE_MIL
	//MdigControl(g_clVision.m_MilDigitizer, M_GRAB_DIRECTION_X, M_REVERSE);
	//MdigControl(g_clVision.m_MilDigitizer, M_GRAB_DIRECTION_Y, M_REVERSE);
#endif
}

//-----------------------------------------------------------------------------
//
//	스레드 소멸자
//
//-----------------------------------------------------------------------------
void CVisionGrabThread::ThreadDestructor()
{

}

//-----------------------------------------------------------------------------
//
//	스레드 콜백
//
//-----------------------------------------------------------------------------
void CVisionGrabThread::ThreadCallBack()
{
	if (g_clVision.m_nGrabMode[0] == GRAB_LIVE)
	{

		//MdigGrab(g_clVision.m_MilDigitizer, g_clVision.m_MilImage[m_nDigIndex]);
		//MdigGrabWait(g_clVision.m_MilDigitizer, M_GRAB_END);

		/*if (Counter <MAX_CAM_COUNT - 1)
			Counter++;
		else
			Counter = 0;*/
		/* Do not wait on a color-lock if the camera is monochrome. */
		/*if (Color[Counter])
		MdigControl(g_clVision.m_MilDigitizer, M_CAMERA_COLOR_LOCK, M_ENABLE);
		else
		MdigControl(g_clVision.m_MilDigitizer, M_CAMERA_COLOR_LOCK, M_DISABLE);*/
		//MdigControl(g_clVision.m_MilDigitizer, M_CAMERA_COLOR_LOCK, M_DISABLE);
		/* Switch and grab. Internaly the grab function will wait until
		the hardware is locked. */
		//MdigChannel(g_clVision.m_MilDigitizer, Channel[Counter]); 
		//
		//
		//MdigGrab(MilDigitizer, MilImageDispChild[Counter]);
		for (int i = 0; i < MAX_CAM_COUNT; i++)
		{
			MdigGrab(g_clVision.m_MilDigitizer[0][i], g_clVision.m_MilGrabImage[m_nUnit][i]);
			MdigGrabWait(g_clVision.m_MilDigitizer[0][i], M_GRAB_END);// M_GRAB_END);  M_GRAB_FRAME_END

			MimResize(g_clVision.m_MilGrabImageChild[0][i], g_clVision.MilCamSmallImageChild[0][i], CAM_REDUCE_FACTOR_X, CAM_REDUCE_FACTOR_Y, M_DEFAULT);
			::Sleep(1);
		}
	}
}