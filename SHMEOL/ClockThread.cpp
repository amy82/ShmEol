#include "StdAfx.h"
#include "ClockThread.h"
#include "AutoInspDlg.h"
#include "GlobalDeclare.h"

CClockThread::CClockThread(void)
{
}


CClockThread::~CClockThread(void)
{
}

//-----------------------------------------------------------------------------
//
//	스레드 생성자
//
//-----------------------------------------------------------------------------
void CClockThread::ThreadConstructor()
{
	m_dwTickCount = 0;
}

//-----------------------------------------------------------------------------
//
//	스레드 소멸자
//
//-----------------------------------------------------------------------------
void CClockThread::TheradDestructor()
{

}

//-----------------------------------------------------------------------------
//
//	스레드 콜백
//
//-----------------------------------------------------------------------------
void CClockThread::ThreadCallBack()
{
	// 300ms 마다 표시
	if((GetTickCount() - m_dwTickCount) > 500)
	{
		// 현재 날짜 표시
		this->ShowCurrDate();

		// 현재 시간 표시
		this->ShowCurrTime();

		m_dwTickCount = GetTickCount();
		
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CClockThread::ShowCurrDate()
{
	SYSTEMTIME stSysTime;
	TCHAR szDate[SIZE_OF_100BYTE];

	GetLocalTime(&stSysTime);

	_stprintf_s(szDate, SIZE_OF_100BYTE, _T("%04d-%02d-%02d"), stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	g_pCarAABonderDlg->ShowCurrentDate(szDate);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CClockThread::ShowCurrTime()
{
	SYSTEMTIME stSysTime;
	TCHAR szTime[SIZE_OF_100BYTE];

	GetLocalTime(&stSysTime);

	_stprintf_s(szTime, SIZE_OF_100BYTE, _T("%02d:%02d:%02d"), stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);
	g_pCarAABonderDlg->ShowCurrentTime(szTime);
}
