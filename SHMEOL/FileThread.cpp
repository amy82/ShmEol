#include "StdAfx.h"
#include "FileThread.h"
#include "AutoInspDlg.h"
#include "GlobalDeclare.h"

CFileThread::CFileThread(void)
{
}


CFileThread::~CFileThread(void)
{
}

//-----------------------------------------------------------------------------
//
//	스레드 생성자
//
//-----------------------------------------------------------------------------
void CFileThread::ThreadConstructor()
{
	m_dwTickCount = 0;
}

//-----------------------------------------------------------------------------
//
//	스레드 소멸자
//
//-----------------------------------------------------------------------------
void CFileThread::TheradDestructor()
{

}

//-----------------------------------------------------------------------------
//
//	스레드 콜백
//
//-----------------------------------------------------------------------------
void CFileThread::ThreadCallBack()
{
	// 300ms 마다 표시
	if ((GetTickCount() - m_dwTickCount) > 43200000)	//1시간 = 3600 , 12시간 43200
	{
		m_dwTickCount = GetTickCount();

		RawDataDelete(0);
	}

}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CFileThread::ShowCurrDate()
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
void CFileThread::ShowCurrTime()
{
	SYSTEMTIME stSysTime;
	TCHAR szTime[SIZE_OF_100BYTE];

	GetLocalTime(&stSysTime);

	_stprintf_s(szTime, SIZE_OF_100BYTE, _T("%02d:%02d:%02d"), stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);
	g_pCarAABonderDlg->ShowCurrentTime(szTime);
}
