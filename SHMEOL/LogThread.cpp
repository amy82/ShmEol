#include "StdAfx.h"
#include "LogThread.h"
#include "AutoInspDlg.h"
#include "GlobalDeclare.h"

CLogThread::CLogThread(void)
{
	nCount = 0;
	nUnit = 0;
}


CLogThread::~CLogThread(void)
{
}


//-----------------------------------------------------------------------------
//
//	스레드 생성자
//
//-----------------------------------------------------------------------------
void CLogThread::ThreadConstructor()
{

}

//-----------------------------------------------------------------------------
//
//	스레드 소멸자
//
//-----------------------------------------------------------------------------
void CLogThread::ThreadDestructor()
{
	//g_clLogQueue.RemoveAll();
}

//-----------------------------------------------------------------------------
//
//	스레드 콜백
//
//-----------------------------------------------------------------------------
void CLogThread::ThreadCallBack()
{
	// 로그 처리
	this->ProcessLog();
}


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CLogThread::CreateLogFolder(CString strLog)
{
	TCHAR szPath[SIZE_OF_1K];
	SYSTEMTIME stSysTime;
	CFileFind clFinder;
	int i;

	GetLocalTime(&stSysTime);

	if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
		CreateDirectory(BASE_LOG_PATH, NULL);

	for(i = 0; i < MAX_UNIT_COUNT; i++)
	{
		_stprintf_s(szPath, SIZE_OF_1K, _T("%s"), BASE_LOG_PATH);
		if (clFinder.FindFile(szPath) == FALSE)
			CreateDirectory(szPath, NULL);

		_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Step"), BASE_LOG_PATH);
		if (clFinder.FindFile(szPath) == FALSE)
			CreateDirectory(szPath, NULL);

		_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Step\\%04d%02d"), BASE_LOG_PATH,  stSysTime.wYear, stSysTime.wMonth);
		if (clFinder.FindFile(szPath) == FALSE)
			CreateDirectory(szPath, NULL);		
	}


	TCHAR m_szModel[SIZE_OF_100BYTE];
#if (____MACHINE_NAME == MODEL_FRONT_100)
	_stprintf_s(m_szModel, SIZE_OF_100BYTE, _T("100"));
#else
	_stprintf_s(m_szModel, SIZE_OF_100BYTE, _T("150"));
#endif

	TCHAR szFilePath[SIZE_OF_1K];

	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%04d%02d%02d%02d_LogData_%s.txt"), szPath, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, m_szModel);
	logFile.open(szFilePath, std::ios::out | std::ios::app);
	if (!logFile.is_open())
	{
		throw std::runtime_error("Failed to open log file");
	}
	else
	{
		logFile << strLog << std::endl;
	}
	logFile.close();
}

void CLogThread::Log(const std::string& message)
{
	{
		std::lock_guard<std::mutex> lock(queueMutex);
		logQueue.push(message);
	}
	logCondition.notify_one();
}

void CLogThread::StopLogging()
{
	std::lock_guard<std::mutex> lock(queueMutex);
	isLogging = false;

	logCondition.notify_all();
	//if (logThread.joinable())
	//{
		//logThread.join();
	//}
}
//-----------------------------------------------------------------------------
//
//	로그 처리
//
//-----------------------------------------------------------------------------
void CLogThread::ProcessLog()
{	
	int i, j;
	std::unique_lock<std::mutex> lock(queueMutex);
	logCondition.wait(lock, [this] 
	{ 
		return !logQueue.empty() || !isLogging;
	});

	if (!isLogging && logQueue.empty())
	{
		return;
	}

	while (!logQueue.empty())
	{
		std::string logMessage = logQueue.front();
		logQueue.pop();
		lock.unlock();

		// 로그 출력 (콘솔에 출력, 파일에 기록 등)
		//std::cout << logMessage << std::endl;

		nCount = g_pCarAABonderDlg->m_clListLog[nUnit].GetCount();
		if (nCount > 500)
		{
			g_pCarAABonderDlg->m_clListLog[nUnit].DeleteString(0);
			//g_pCarAABonderDlg->m_clListLog[nUnit].ResetContent();
		}
		nCount = g_pCarAABonderDlg->m_clListLog[nUnit].AddString(logMessage.c_str());
		g_pCarAABonderDlg->m_clListLog[nUnit].SetCurSel(nCount);


		CreateLogFolder(logMessage.c_str());
		lock.lock();
	}
	return;
	//CString sTitle = _T("");
	//int nNodeCount = 0;
	//int nListCount;

	//nNodeCount = g_clLogQueue.GetCount();
	//for (i = 0; i < nNodeCount; i++)
	//{
	//	STRUC_LOG_NODE* pNode = g_clLogQueue.Pop();
	//	if (pNode == NULL)
	//		continue;
	//	
	//	if (pNode->nLogType != 0)
	//	{
	//		if(pNode->nUnit >= 0 && pNode->nUnit < MAX_UNIT_COUNT)
	//			sTitle.Format(_T("[ERROR] UNIT AA%d"), pNode->nUnit + 1);
	//		else
	//			sTitle.Format(_T("ERROR"));

	//		g_ShowMsgPopup(sTitle, pNode->szBuff, RGB_COLOR_RED);
	//		//g_ShowMsgPopup(_T("ERROR"), pNode->szBuff, RGB_COLOR_RED);
	//	}

	//	if(pNode->nUnit >= 0 && pNode->nUnit < MAX_UNIT_COUNT)
	//	{
	//		nListCount = g_pCarAABonderDlg->m_clListLog[pNode->nUnit].GetCount();
	//		if (nListCount > 300)
	//		{
	//			g_pCarAABonderDlg->m_clListLog[pNode->nUnit].DeleteString(0);
	//		}
	//		nListCount = g_pCarAABonderDlg->m_clListLog[pNode->nUnit].AddString(pNode->szBuff);
	//		g_pCarAABonderDlg->m_clListLog[pNode->nUnit].SetCurSel(nListCount);
	//	}
	//	else
	//	{
	//		for(j = 0; j < MAX_UNIT_COUNT; j++)
	//		{
	//			nListCount = g_pCarAABonderDlg->m_clListLog[j].GetCount();
	//			if (nListCount > 300)
	//			{
	//				g_pCarAABonderDlg->m_clListLog[j].DeleteString(0);
	//			}
	//			nListCount = g_pCarAABonderDlg->m_clListLog[j].AddString(pNode->szBuff);
	//			g_pCarAABonderDlg->m_clListLog[j].SetCurSel(nListCount);
	//		}
	//	}

	//	this->WriteLogFile(pNode);

	//	delete pNode;
	//}	
}

//-----------------------------------------------------------------------------
//
//	로그 파일에 쓰기
//
//-----------------------------------------------------------------------------
//void CLogThread::WriteLogFile(STRUC_LOG_NODE* pNode)
//{
//	TCHAR szPath[SIZE_OF_1K];
//	SYSTEMTIME stSysTime;
//	CString sWriteMode = _T("");
//	FILE* fp;
//	int i;
//
//	GetLocalTime(&stSysTime);
//
//	if(pNode->nUnit >= 0 && pNode->nUnit < MAX_UNIT_COUNT)
//	{
//		_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\AA%d\\%04d%02d\\%02d\\LogData-AA%d-%d-%02d.txt"), BASE_LOG_PATH, pNode->nUnit + 1, 
//			stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, g_clSysData.m_nSysNo + 1, pNode->nUnit + 1, stSysTime.wDay);
//
//#ifdef _UNICODE
//		sWriteMode = _T("a,ccs=UTF-8");
//#else
//		sWriteMode = _T("a+t");
//#endif
//
//		_tfopen_s(&fp, szPath, sWriteMode);
//		if (fp != NULL)
//		{
//			fwrite(pNode->szBuff, _tcslen(pNode->szBuff) * sizeof(TCHAR), 1, fp);
//			fwrite(_T("\r\n"), _tcslen(_T("\r\n")) * sizeof(TCHAR), 1, fp);
//
//			fclose(fp);
//		}
//	}
//	else
//	{
//		for(i = 0; i < MAX_UNIT_COUNT; i++)
//		{
//			_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\AA%d\\%04d%02d\\%02d\\LogData-AA%d-%d-%02d.txt"), BASE_LOG_PATH, i + 1,
//				stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, g_clSysData.m_nSysNo + 1, i + 1, stSysTime.wDay);
//
//#ifdef _UNICODE
//			sWriteMode = _T("a,ccs=UTF-8");
//#else
//			sWriteMode = _T("a+t");
//#endif
//
//			_tfopen_s(&fp, szPath, sWriteMode);
//			if (fp != NULL)
//			{
//				fwrite(pNode->szBuff, _tcslen(pNode->szBuff) * sizeof(TCHAR), 1, fp);
//				fwrite(_T("\r\n"), _tcslen(_T("\r\n")) * sizeof(TCHAR), 1, fp);
//
//				fclose(fp);
//			}
//		}
//	}
//}
