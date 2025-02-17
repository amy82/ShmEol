#include "stdafx.h"
#include "Log.h"


CLog::CLog()
{
}


CLog::~CLog()
{
}



//void CLog::MainLogSave(CString str, int index)
//{
	//SYSTEMTIME time;
	//::GetLocalTime(&time);

	//FILE *out;

	//CFileFind finder;
	//BOOL IsFind;
	//CString FolderName;
	////wchar_t *wChar = (wchar_t *)str.GetBuffer();
	//FolderName.Format("%s\\%04d%02d\\%02d", LOGBASE_DIR, time.wYear, time.wMonth, time.wDay);
	//IsFind = finder.FindFile(FolderName);
	//if (!IsFind)
	//{
	//	FolderName.Format("%s", BASE_DIR);
	//	IsFind = finder.FindFile(FolderName);
	//	if (!IsFind)
	//	{
	//		CreateDirectory(FolderName, NULL);
	//	}
	//	FolderName.Format("%s", LOGBASE_DIR);
	//	IsFind = finder.FindFile(FolderName);
	//	if (!IsFind)
	//	{
	//		CreateDirectory(FolderName, NULL);
	//	}

	//	FolderName.Format("%s\\%04d%02d", LOGBASE_DIR, time.wYear, time.wMonth);
	//	CreateDirectory(FolderName, NULL);
	//}
	//finder.Close();

	//char fileName[1000];
	//wsprintf(fileName, "%s\\%04d%02d%02d_LogDataAA.txt", FolderName, time.wYear, time.wMonth, time.wDay);

	//if (!fopen_s(&out, fileName, "a"))
	//{
	//	fprintf_s(out, "%02d:%02d:%02d:%03d %s\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, str);
	//	fclose(out);
	//}
//}