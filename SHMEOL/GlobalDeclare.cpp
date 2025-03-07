//-----------------------------------------------------------------------------
//
//	GlobalDeclare.cpp
//
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "GlobalDeclare.h"
//#include "GlobalDefine.h"
#include <afxdb.h>
#define PI 3.141592653589793f


CAutoInspDlg* g_pCarAABonderDlg;
CMessagePopupDlg* g_pMessagePopupDlg[MAX_POPUP_COUNT];

CMessageInput* m_clTeminalMessageDlg[MAX_TERMINAL_COUNT];

CMessagePopupDlg* g_pMessageClosePopupDlg;
int g_nPopupIndex;
int g_nTerminalIindex;

CModelList ModelList;
//CModelType g_clModelType;
CSystemData g_clSysData;
CModelData g_clModelData[2];
CMarkData g_clMarkData[2];
CTaskWork g_clTaskWork[2];
CReportClass g_clReportData;
//CSFRTeachingData g_clSFRTeacingData;

CVision g_clVision;
CModelFinder g_clModelFinder;
CAxlMotorSet g_clMotorSet;
CDioControl  g_clDioControl;
//CSimpleAdo g_clAdo;

CLaonGrabberWrapper g_clLaonGrabberWrapper[MAX_UNIT_COUNT];

//CInspection_Alg g_clAlg[MAX_UNIT_COUNT];
CAps_Insp g_clPriInsp[MAX_UNIT_COUNT];

CMandoSfrSpec g_clMandoSfrSpec[MAX_UNIT_COUNT];
CMandoInspLog g_clMandoInspLog[MAX_UNIT_COUNT];

CMesCommunication g_clMesCommunication[MAX_UNIT_COUNT];
//CeepromData			eepromData[MAX_UNIT_COUNT];
//CVerifyData EEpromVerifyData;
CInterLockDlg* InterLockDlg;


CLightControl		TopChartControl[MAX_UNIT_COUNT];				//Topchart
CLightControl		BackDuLightControl[MAX_UNIT_COUNT];			//Align + 이물광원

CLightControl		LightLeftChartControl[MAX_UNIT_COUNT];		//Left Side Chart
CLightControl		LightRightChartControl[MAX_UNIT_COUNT];		//Right Side Chart


//CLightControl		WhiteOcLightControl[MAX_UNIT_COUNT];		//이물광원
//COcControl	OCControl[MAX_UNIT_COUNT * 1];	//oc white
//COcControl	IRControl[MAX_UNIT_COUNT * 1];	//IR(0,1채널) + ALIGN(2,3채널)
//CCMSMESSocket* g_clCMSMESSocket;

//CQueue<STRUC_LOG_NODE*> g_clLogQueue;
bool MesSpecLoadCheck;
bool bCurrentConnect;

int VEC_FOV_COUNT;
int VEC_FOV_FIND_COUNT;

TCHAR BASE_PATH[SIZE_OF_1K];
TCHAR BASE_DATA_PATH[SIZE_OF_1K];
TCHAR BASE_ALARM_PATH[SIZE_OF_1K];
TCHAR MIU_DIR[SIZE_OF_1K];
TCHAR FW_DIR[SIZE_OF_1K];

//-----------------------------------------------------------------------------
//
//	현재 경로 구하기
//
//-----------------------------------------------------------------------------
unsigned int g_GetCurrentPath(TCHAR* pPath)
{
	unsigned int nLength;
	int i;

	nLength = GetModuleFileName(NULL, pPath, SIZE_OF_1K);
	if (nLength != 0)
	{
		for (i = nLength; i > 0; i--)
		{
			if (pPath[i - 1] == _T('\\'))
			{
				pPath[i] = NULL;
				return i;
			}
		}
	}

	return 0;
}

bool Binary_Dump_Load(int nUnit)
{
	//string filePath = "./Dump_164627_H120.bin";
	//std::ifstream is(filePath, std::ifstream::binary);
	//if (is)
	//{
	//	// seekg를 이용한 파일 크기 추출
	//	is.seekg(0, is.end);
	//	int length = (int)is.tellg();
	//	is.seekg(0, is.beg);

	//	is.read((char*)g_clMesCommunication[nUnit].mReadEEpromData, length);
	//	is.close();
	//	return true;
	//}

	return false;
}

bool MesDataSave(int nUnit)
{
	int i = 0;
	CFileFind pFind;
	TCHAR	szLog[SIZE_OF_1K];
	TCHAR strReadIni1[SIZE_OF_1K] = { 0 };
	CString strPathIni = _T("");
	CString strMesPath = _T("");
	CString sToken = _T("");
	CString sViewLog = _T("");

	_stprintf_s(szLog, SIZE_OF_1K, _T("[설비 SPEC SAVE]"));
	AddLog(szLog, 0, 0);

//#if (____MACHINE_NAME ==  MODEL_FRONT_100)			//ok
//
//	strPathIni.Format("%s\\spec\\SPEC_SHM_100.txt", BASE_PATH);
//#else
//	strPathIni.Format("%s\\spec\\SPEC_SHM_150.txt", BASE_PATH);
//#endif

	if (ModelList.m_szCurrentModel == SHM_FRONT_100_MODEL)
	{
		strPathIni.Format("%s\\spec\\SPEC_SHM_100.txt", BASE_PATH);
	}
	else
	{
		strPathIni.Format("%s\\spec\\SPEC_SHM_150.txt", BASE_PATH);
	}


	FILE *out;
	if (fopen_s(&out, strPathIni, "w"))
	{
		//sLangChange.LoadStringA(IDS_STRING1083);
		//errMsg2(Task.AutoFlag, _T("SfrSpec Save Fail..."));
	}
	else 
	{
		for (i = 0; i < MES_VERIFY_SPEC_COUNT; i++)
		{
			//fprintf_s(out, "%d\t%s\t%s\t%s\n", i + 1, MesSpecList[i].c_str(), EEpromVerifyData.vMinData[i], EEpromVerifyData.vMaxData[i]);
		}
		if (out)	fclose(out);
	}
	return true;
}
void MesDataLoad(int nUnit)
{
#if 0
	TCHAR strReadIni1[SIZE_OF_1K] = { 0 };
	CString strPathIni = _T("");
	MesSpecLoadCheck = false;


#if (____MACHINE_NAME ==  MODEL_FRONT_100)

	strPathIni.Format("%s\\spec\\SPEC_SHM_100.txt", BASE_PATH);
#else
	strPathIni.Format("%s\\spec\\SPEC_SHM_150.txt", BASE_PATH);
#endif
	TCHAR	szLog[SIZE_OF_1K];
	//FILETIME ftCt, ftLat, ftLwt;
	//FILETIME TempTime;
	SYSTEMTIME SystemTime;
	//HANDLE h = CreateFile(strPathIni, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//GetFileTime(h, &ftCt, &ftLat, &ftLwt);
	//FileTimeToLocalFileTime(&ftCt, &TempTime);
	//FileTimeToSystemTime(&TempTime, &SystemTime);
	
	_stprintf_s(szLog, SIZE_OF_1K, _T("[MES SPEC]Path:%s "), strPathIni);
	AddLog(szLog, 0, nUnit);

	//_stprintf_s(szLog, SIZE_OF_1K, _T("[CreationTime]%d-%d-%d %d:%d:%d"), SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay, SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond);
	//AddLog(szLog, 0, nUnit);

	//FileTimeToLocalFileTime(&ftLat, &TempTime);
	//FileTimeToSystemTime(&TempTime, &SystemTime);

	//_stprintf_s(szLog, SIZE_OF_1K, _T("[LastAccessTime]%d-%d-%d %d:%d:%d"), SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay, SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond);
	//AddLog(szLog, 0, nUnit);

	//CloseHandle(h);

	std::ifstream file(strPathIni);
	//vector<string>mspec;
	CString temp;
	CString mspec;
	CString mMaxspec;
	int mLength = 0;
	int mLength2 = 0;
	int i = 0;
	vector<string> sV1;
	EEpromVerifyData.Reset();
	byte bTemp[100];
	memset(bTemp, 0x00, sizeof(bTemp));
	if (true == file.is_open())
	{
		MesSpecLoadCheck = true;
		std::string s;
		while (file)
		{
			temp.Empty();
			mspec.Empty();
			mMaxspec.Empty();
			getline(file, s);

			for (i = 0; i < MES_VERIFY_SPEC_COUNT; i++)
			{
				if (s.find(MesSpecList[i]) != string::npos)
				{
					mspec.Empty();
					mMaxspec.Empty();
					temp.Empty();
					temp.Format(_T("%s"), s.c_str());
					//

					//문자 같이와, 길이가지 비교
					AfxExtractSubString(mspec, temp, 1, _T('\t'));
					int k1 = mspec.GetLength();
					int k2 = MesSpecList[i].length();
					if (k1 != k2)
					{
						continue;
					}
					//
					
					AfxExtractSubString(mspec, temp, 2, _T('\t'));
					_stprintf_s(EEpromVerifyData.vMinData[i], SIZE_OF_100BYTE, mspec);
					mLength = _tcslen(EEpromVerifyData.vMinData[i]);
					if (mLength > 0)
					{
						// String to Hex
						//eepromData[nUnit].StringToHex(MesSpecList[i], mspec, EEpromVerifyData.vMinHexData[i], 0);
					}
					//
					//
					//
					AfxExtractSubString(mMaxspec, temp, 3, _T('\t'));
					_stprintf_s(EEpromVerifyData.vMaxData[i], SIZE_OF_100BYTE, mMaxspec);
					mLength2 = _tcslen(EEpromVerifyData.vMaxData[i]);
					if (mLength2 > 0)
					{
						// String to Hex
						//eepromData[nUnit].StringToHex(MesSpecList[i], mMaxspec, EEpromVerifyData.vMaxHexData[i], 1);
					}
					if (mLength < 1 && mLength2 < 1)
					{
						continue;
					}
					break;
				}
			}
		}
		for (i = 0; i < MES_VERIFY_SPEC_COUNT; i++)
		{
			mLength = _tcslen(EEpromVerifyData.vMinData[i]);
			mLength2 = _tcslen(EEpromVerifyData.vMaxData[i]);

			if (mLength < 1 && mLength2 < 1)
			{ 
				file.close();
				MesSpecLoadCheck = false;
				temp.Format("[MES]%s=[%s/%s] Load Fail", MesSpecList[i].c_str(), EEpromVerifyData.vMinData[i], EEpromVerifyData.vMaxData[i]);
				AddLog(temp, 1, UNIT_AA1, true);
				temp.Empty();
				mspec.Empty();
				mMaxspec.Empty();
				strPathIni.Empty();
				return;
			}
		}
		file.close();
	}
	else
	{
		temp.Format(_T("[ERROR] MES SPEC LOAD FAIL"));
		AddLog(temp, 1, UNIT_AA1, true);
		//ViewMessagePopup("INFO", temp, A_COLOR_RED); 
	}

	temp.Empty();
	mspec.Empty();
	mMaxspec.Empty();
	strPathIni.Empty();
#endif
}


void EEPROM_Temp_DumpLoad(int m_nUnit, byte* tempDumpData)
{
#if 0
	CFileFind clFinder;
	CString sFileMode = _T("");
	CFile clFile;
	FILE* fp;
	TCHAR	szLog[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szFilePath[SIZE_OF_1K];
	SYSTEMTIME stSysTime;
	::GetLocalTime(&stSysTime);

	if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
		CreateDirectory(BASE_LOG_PATH, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s"), BASE_LOG_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\tempDump.bin"), szPath);


	//string filePath = "./Dump_164627_H120.bin";

	std::string filePath = std::string(szFilePath);
	std::ifstream is(filePath, std::ifstream::binary);
	if (is)
	{
		// seekg를 이용한 파일 크기 추출
		is.seekg(0, is.end);
		int length = (int)is.tellg();
		is.seekg(0, is.beg);

		is.read((char*)g_clMesCommunication[m_nUnit].mMesGetEEpromData, length);
		is.close();

		_stprintf_s(szLog, SIZE_OF_1K, _T("[DUMP] TEMP DUMP LOAD COMPLETE "));
		AddLog(szLog, 0, m_nUnit);
		return;
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[DUMP] TEMP DUMP FILE EMPTY "));
		AddLog(szLog, 0, m_nUnit);
	}
#endif
}
void EEPROM_Temp_DumpSave(int m_nUnit, byte* tempDumpData)
{
	CFileFind clFinder;
	CString sFileMode = _T("");
	CFile clFile;
	FILE* fp;
	TCHAR	szLog[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szFilePath[SIZE_OF_1K];
	SYSTEMTIME stSysTime;
	::GetLocalTime(&stSysTime);

	if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
		CreateDirectory(BASE_LOG_PATH, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s"), BASE_LOG_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\tempDump.bin"), szPath);



	int bLength = 2457 + 1;// 1299;
	ofstream output(szFilePath, ios::out | ios::binary);
	output.write((const char*)tempDumpData, bLength);
	output.close();
	_stprintf_s(szLog, SIZE_OF_1K, _T("[DUMP] TEMP DUMP SAVE COMPLETE "));
	AddLog(szLog, 0, m_nUnit);
}
//////////////////////////////////////////////////////////////////////////
bool EEPROM_Binary_Dump_Save(int m_nUnit,  byte* TotalDumpData)
{
	CFileFind clFinder;
	CString sFileMode = _T("");
	CFile clFile;
	FILE* fp;
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szFilePath[SIZE_OF_1K];
	SYSTEMTIME stSysTime;
	::GetLocalTime(&stSysTime);

	if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
		CreateDirectory(BASE_LOG_PATH, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Dump"), BASE_LOG_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Dump\\%04d%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Dump\\%04d%02d\\%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	//
	//CString tempLotid = _T("");
	//int nindex = g_EEPROMTask[nUnit].m_sLotId.Find(':');
	//int nindex = g_clTaskWork[m_nUnit].m_szChipID.Find(':');
	//tempLotid = g_EEPROMTask[m_nUnit].m_sLotId.Mid(nindex + 1, g_EEPROMTask[nUnit].m_sLotId.GetLength());//1이면 S를 추가한다?
	//_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\MainDump_%02d%02d%02d_%s.bin"), szPath, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond, tempLotid);
	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%s_Dump_%02d%02d%02d.bin"), szPath, g_clTaskWork[m_nUnit].m_szChipID, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);


	//220405 바이너리 파일저장
	int bLength = 2457 + 1;// 1299;
	ofstream output(szFilePath, ios::out | ios::binary);//ofstream output("d:\\data.bin", ios::out | ios::binary);
	output.write((const char*)TotalDumpData, bLength);
	output.close();
	//

	return true;
}

void AddLog(CString str, int mPopupShow, int nUnit, bool buzzer, bool _View)
{
	SYSTEMTIME stSysTime;
	TCHAR sListLog[SIZE_OF_1K];
	TCHAR sMsg[SIZE_OF_1K];
	int nCount = 0;

	if (buzzer == true)
	{
		g_ShowMsgPopup(_T("ERROR"), str, RGB_COLOR_RED);
		g_clDioControl.SetBuzzer(true, BUZZER_ALARM);
		_stprintf_s(sMsg, SIZE_OF_1K, _T("#AA%d@ALARM&ERR$"), (nUnit + 1));

		g_pCarAABonderDlg->SendDataToAAMain(nUnit, sMsg);

		g_pCarAABonderDlg->m_clAlarmDlg.AddAlarm_N(str);
	}
	else if (mPopupShow == 1)
	{
		//팝업만
		g_ShowMsgPopup(_T("INFO"), str, RGB_COLOR_RED);
	}
	GetLocalTime(&stSysTime);



	_stprintf_s(sListLog, SIZE_OF_1K, _T("[%02d:%02d:%02d.%03d] %s"), stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond, stSysTime.wMilliseconds, (TCHAR*)(LPCTSTR)str);
	if (_View)
	{
		g_pCarAABonderDlg->m_clLogThread.Log(sListLog);
	}
	else
	{
		nCount = g_pCarAABonderDlg->m_clListLog[nUnit].GetCount();
		if (nCount > 500)
		{
			g_pCarAABonderDlg->m_clListLog[nUnit].DeleteString(0);
			//g_pCarAABonderDlg->m_clListLog[nUnit].ResetContent();
		}
		nCount = g_pCarAABonderDlg->m_clListLog[nUnit].AddString(sListLog);
		g_pCarAABonderDlg->m_clListLog[nUnit].SetCurSel(nCount);

		LogSave(sListLog, nUnit);
	}
	
}


void eeprom_Data_Sum(CString WriteData, int WritebyteLength, int type, byte* rtnData)
{
	unsigned char pData[MAX_PATH];
	int errorCode = 0;
	int i = 0;
	int j = 0;
	int leng = WriteData.GetLength();
	int byteLength = 0;
	int value = 0;
	float fNum = 0.0;
	double testnum = 0.0;
	CString strTemp;
	int startNum = 0;
	unsigned char szTemp[MAX_PATH];
	bool bOddCheck = false;
	memset(pData, 0, sizeof(pData));
	memset(rtnData, 0, sizeof(WritebyteLength));
	strTemp.Empty();
	if (type == FLOAT_MODE)
	{
		fNum = (float)_ttof(WriteData);//fNum = (_ttof(WriteData));//atof  //wtof
		memcpy(szTemp, &fNum, sizeof(float));//들어갈때 반대로 값이 들어간다 
	}
	else if (type == ASCII_MODE)
	{
		startNum = (WritebyteLength - leng);//(WritebyteLength - 1 - leng);
		strTemp = CovertToHex(WriteData, type);
	}
	else if (type == ASCII_MODE_2)
	{
		strTemp = CovertToHex(WriteData, type);
	}
	//ASCII_MODE_2
	strTemp.Replace(" ", "");
	byteLength = strTemp.GetLength();
	//
	switch (type)
	{
	case ASCII_MODE:
		leng = WritebyteLength;
		break;
	case ASCII_MODE_2:
		leng = 2;//3바트일경우만 쓸거라서
		memcpy(rtnData, strTemp.GetBuffer(0), byteLength);
		break;
	case FLOAT_MODE:
		leng = 4;
		for (i = 0; i < leng; i++)
		{
			strTemp.AppendFormat("%02X", szTemp[3 - i]);// szTemp[3 - x]);
		}
		break;
	case DEC_MODE:
		//
		leng = WritebyteLength;// 1;
		//
		//dec -->hex로 바꾸는 코드
		value = _ttoi(WriteData);
		//strTemp.Format("%x ", value);	//예를 들어 0x0bb8로 들어오면 0이 사라지고 bb8이는 문제가 있다 230301
		memcpy(szTemp, &value, sizeof(int));
		for (i = 0; i < leng; i++)
		{
			strTemp.AppendFormat("%02X", szTemp[leng - i - 1]);// szTemp[3 - x]);
		}

		//
		break;
	case HEX_MODE:
		leng = WritebyteLength;
		strTemp.Format("%s", WriteData);//그대로 쓰는 코드
		break;
	}
	for (int i = 0; i < leng; i++)
	{
		if (type == ASCII_MODE)
		{
			if (i >= (startNum))
			{
				//value = (int)(WriteData[i - startNum]);
				pData[i] = (unsigned char)_tcstol(strTemp.Mid((i - startNum) * 2, 2), NULL, 16);
			}
			else
			{
				pData[i] = (unsigned char)_tcstol("20", NULL, 16);
			}
		}
		else if (type == ASCII_MODE_2)
		{
			pData[i] = (unsigned char)_tcstol(strTemp.Mid(i, (i + 1)), NULL, 16);
		}
		else
		{
			pData[i] = (unsigned char)_tcstol(strTemp.Mid(i * 2, 2), NULL, 16);//hex코드로 입력했을대기존코드

		}
		rtnData[i] = pData[i];
	}
}

float CovertToFloat(CString data, int type)
{
	int i = 0;
	int leng;			// WriteData.GetLength();
	float fNum = 0.0;
	CString strTemp;
	UINT32 AAA;
	strTemp.Empty();


	leng = 4;
	for (i = 0; i < leng; i++)
	{
		strTemp.AppendFormat("%s", data.Mid(8-((i +1)*2) ,2));// szTemp[3 - x]);
	}
	sscanf_s(strTemp, "%X", &AAA);
	fNum = *((float*)&AAA);
	//
	return fNum;
}
CString CovertToHex(CString data, int type)
{
	CString rtnValue;
	CString temporary;
	unsigned char szTemp[1024];
	int value = 0;
	float fNum = 0.0;
	temporary.Empty();
	rtnValue.Empty();
	data.Replace(" ", "");
	memset(szTemp, 0x00, 1024);
	int len = 0;

	if (type == FLOAT_MODE)
	{
		fNum = (_ttof(data));
		memcpy(szTemp, &fNum, sizeof(float));
		len = 4;
	}
	else if (type == ASCII_MODE)
	{
		len = data.GetLength();
	}
	else if (type == ASCII_MODE_2)
	{
		len = 1;// data.GetLength();
	}
	else if (type == DEC_MODE)
	{
		len = 1;
	}
	for (int x = 0; x < len; x++)
	{
		if (type == FLOAT_MODE)
		{
			temporary.Format("%02X", szTemp[3 - x]);// szTemp[3 - x]);
													//Hex 로 변경
		}
		else if (type == ASCII_MODE)
		{
			value = (int)(data[x]);
			temporary.Format("%X", value);//temporary.Format("%02X", value);기존
										  //temporary.Format("%d", value);//
										  //ASCII : 입력된 String 을 ASCII Code 로 변경
		}
		else if (type == ASCII_MODE_2)
		{
			value = _ttoi(data);
			temporary.Format("%X", value);
		}
		else if (type == DEC_MODE)
		{
			value = _ttoi(data);
			temporary.Format("%X", value);
		}
		rtnValue += temporary;
	}
	return rtnValue;
}
CString CovertToChar(CString data, int mode)
{
	CString rtnValue;
	CString temporary;
	temporary.Empty();
	rtnValue.Empty();
	data.Replace(" ", "");
	int len = (int)data.GetLength();
	byte value;
	UINT32 AAA;
	float fNum = 0.0;
	if (mode == ASCII_MODE)
	{
		for (int x = 0; x < len; x++)//for (int x = 0; x < len; x += 2)
		{
			value = (byte)_tcstol(data.Mid(x * 2, 2), NULL, 16);
			temporary.Format("%c", value);
			rtnValue += temporary;
		}
	}
	else if (mode == FLOAT_MODE)
	{
		sscanf_s(data.GetBuffer(0), "%X", &AAA);
		fNum = *((float*)&AAA);
		rtnValue.Format("%f", fNum);
	}
	else if (mode == DEC_MODE)
	{
		value = (byte)_tcstol(data.Mid(0, 2), NULL, 16);
		temporary.Format("%X", value);
		rtnValue += temporary;
	}

	return rtnValue;
}



void LogSave(CString logStr , int nUnit)
{
    TCHAR szPath[SIZE_OF_1K];
	TCHAR szFilePath[SIZE_OF_1K];
    SYSTEMTIME time;
    ::GetLocalTime(&time);

    FILE *out;

	CFileFind clFinder;
	//
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Step\\%04d%02d"), BASE_LOG_PATH, time.wYear, time.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
	{
		if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
			CreateDirectory(BASE_LOG_PATH, NULL);

		_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Step"), BASE_LOG_PATH);
		if (clFinder.FindFile(szPath) == FALSE)
			CreateDirectory(szPath, NULL);

		_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Step\\%04d%02d"), BASE_LOG_PATH, time.wYear, time.wMonth);
		if (clFinder.FindFile(szPath) == FALSE)
			CreateDirectory(szPath, NULL);
	}

	TCHAR m_szModel[SIZE_OF_100BYTE];
//#if (____MACHINE_NAME == MODEL_FRONT_100)			//ok
//	_stprintf_s(m_szModel, SIZE_OF_100BYTE, _T("100"));
//#else
//	_stprintf_s(m_szModel, SIZE_OF_100BYTE, _T("150"));
//#endif

	if (ModelList.m_szCurrentModel == SHM_FRONT_100_MODEL)
	{
		_stprintf_s(m_szModel, SIZE_OF_100BYTE, _T("100"));
	}
	else
	{
		_stprintf_s(m_szModel, SIZE_OF_100BYTE, _T("150"));
	}

	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%04d%02d%02d%02d_LogData_%s.txt"), szPath, time.wYear, time.wMonth, time.wDay, time.wHour, m_szModel);
	if (!fopen_s(&out, szFilePath, "a"))
	{
		fprintf_s(out, "%s\n", logStr);
		fclose(out);
	}
	logStr.Empty();
}

void ResultSavePath(TCHAR* sPath, CString logStr)
{
	TCHAR szPath[SIZE_OF_1K];
	SYSTEMTIME time;
	::GetLocalTime(&time);

	FILE *out;

	CFileFind finder;
	BOOL IsFind;
	CString FolderName;

	FolderName.Format("%s", sPath);

	int nfindstr = FolderName.Find('.');

	FolderName = FolderName.Mid(0, nfindstr);

	IsFind = finder.FindFile(FolderName);
	if (!IsFind)
	{

	}
	finder.Close();

	//char fileName[1000];
	//wsprintf(fileName, "%s\\%04d%02d%02d_RESULT.txt", FolderName, time.wYear, time.wMonth, time.wDay);
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s_RSEULT.txt"), FolderName);
	if (!fopen_s(&out, szPath, "a"))
	{
		fprintf_s(out, "%s", logStr);
		fclose(out);
	}
}

//-----------------------------------------------------------------------------
//
//	TERMINAL 팝업창 표시
//
//-----------------------------------------------------------------------------
void g_ShowTerminalPopup(CString sTitle, CString sMsg, int nTid, COLORREF bgColor, int TimeClose, int bBuzzer)
{
	int nIndex;
	int i;
	int m_nUnit = 0;
	nIndex = g_nTerminalIindex;

	for (i = 0; i < MAX_TERMINAL_COUNT; i++)
	{
		if (m_clTeminalMessageDlg[i] != NULL)
		{
			if (m_clTeminalMessageDlg[i]->IsWindowVisible() == FALSE)
			{
				g_nTerminalIindex = i;
				break;
			}
		}
	}

	nIndex = g_nTerminalIindex;
	if (m_clTeminalMessageDlg[nIndex] != NULL)
	{
		if (m_clTeminalMessageDlg[nIndex]->IsWindowVisible() == TRUE)
		{
			m_clTeminalMessageDlg[nIndex]->ShowWindow(SW_HIDE);
		}
		if (TimeClose > 0)
		{
			//m_clTeminalMessageDlg[nIndex]->CloseTime = TimeClose;
		}
		//m_clTeminalMessageDlg[nIndex]->SetContents(sTitle, sMsg, MESSAGE_BG_COLOR, nIndex);


		g_clMesCommunication[m_nUnit].m_dTerminalId = nTid;
		m_clTeminalMessageDlg[nIndex]->nPopupId = nIndex;
		m_clTeminalMessageDlg[nIndex]->editInputReadOnly = true;
		m_clTeminalMessageDlg[nIndex]->setEditInput(_T("Terminal Services"), nTid, sMsg);


		m_clTeminalMessageDlg[nIndex]->ShowWindow(SW_SHOW);
	}


}


//-----------------------------------------------------------------------------
//
//	팝업창 표시
//
//-----------------------------------------------------------------------------
void g_ShowMsgPopup(CString sTitle, CString sMsg, COLORREF bgColor, int TimeClose, int bBuzzer)
{
	int nIndex;
	int i;

	nIndex = g_nPopupIndex;

	for (i = 0; i < MAX_POPUP_COUNT; i++)
	{
		if (g_pMessagePopupDlg[i] != NULL)
		{
			if (g_pMessagePopupDlg[i]->IsWindowVisible() == FALSE)
			{
				g_nPopupIndex = i;
				break;
			}
		}
	}

	nIndex = g_nPopupIndex;
	if (g_pMessagePopupDlg[nIndex] != NULL)
	{
		if (g_pMessagePopupDlg[nIndex]->IsWindowVisible() == TRUE)
			g_pMessagePopupDlg[nIndex]->ShowWindow(SW_HIDE);

		if (TimeClose > 0)
		{
			g_pMessagePopupDlg[nIndex]->CloseTime = TimeClose;
		}
		if (bBuzzer == 1)
		{
			g_clDioControl.SetBuzzer(true, BUZZER_ALARM);
		}
		g_pMessagePopupDlg[nIndex]->SetContents(sTitle, sMsg, MESSAGE_BG_COLOR, nIndex);
		g_pMessagePopupDlg[nIndex]->ShowWindow(SW_SHOW);
	}

	
}

void g_ShowCloseMsgPopup(CString sTitle, CString sMsg, bool bShow)
{
	int nIndex = 0;

	if (g_pMessageClosePopupDlg != NULL)
	{
		g_pMessageClosePopupDlg->SetContents(sTitle, sMsg, MESSAGE_BG_COLOR, nIndex);

		if (bShow)
		{
			g_pMessageClosePopupDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			g_pMessageClosePopupDlg->ShowWindow(SW_HIDE);
		}
		
	}
}

//-----------------------------------------------------------------------------
//
//	Modal 창 표시
//
//-----------------------------------------------------------------------------
bool g_ShowMsgModal(CString sTitle, CString sMsg, COLORREF bgColor,CString sYesBtn, CString sNoBtn )
{
	CMessageModalDlg* pDlg = new CMessageModalDlg(sTitle, sMsg, bgColor, sYesBtn, sNoBtn);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDYES)
		{
			delete pDlg;

			return true;
		}

		delete pDlg;
	}

	return false;
}

//-----------------------------------------------------------------------------
//
//	ASK 창 표시
//
//-----------------------------------------------------------------------------
int g_ShowMsgAsk(CString sTitle, CString sMsg, COLORREF bgColor, int nAskCount, TCHAR* pszAsk[])
{
	int nRetVal = 0;

	CMessageAskDlg* pDlg = new CMessageAskDlg(sTitle, sMsg, bgColor, nAskCount, pszAsk);
	if (pDlg != NULL)
	{
		nRetVal = (int)pDlg->DoModal();

		delete pDlg;
	}

	return nRetVal;
}
void unpackRaw12(const unsigned char *src, unsigned short *dst, int rows, int cols)
{
	for (int i = 0, j = 0; i < rows * cols; i += 2, j += 3)
	{
		dst[i + 0] = ((unsigned short)src[j + 0] << 4) | ((unsigned short)(src[j + 2] & 0xf0) >> 4);
		dst[i + 1] = ((unsigned short)src[j + 1] << 4) | ((unsigned short)(src[j + 2] & 0x0f) >> 0);
	}
}
void Raw12to8(unsigned short *pBuffer, unsigned char *pBuf, int rows, int cols)
{
	for (int i = 0; i < rows * cols; i++)
	{
		pBuf[i] = (pBuffer[i] & 0x0FF0) >> 4;
	}
}
int findMinMax(int index)
{
	int i = 0;
	int nIndex = 0;
	int m_nUnit = 0;
	double mTemp = g_clTaskWork[m_nUnit].m_stSfrInsp.dAver_Var[0];
	for (i = 0; i < g_clModelData[m_nUnit].nVarRepetCount; i++)
	{
		if (index == 0)
		{
			if (mTemp > g_clTaskWork[m_nUnit].m_stSfrInsp.dAver_Var[i])
			{
				nIndex = i;
				mTemp = g_clTaskWork[m_nUnit].m_stSfrInsp.dAver_Var[i];
			}
		}
		else
		{
			if (mTemp < g_clTaskWork[m_nUnit].m_stSfrInsp.dAver_Var[i])
			{
				nIndex = i;
				mTemp = g_clTaskWork[m_nUnit].m_stSfrInsp.dAver_Var[i];
			}
		}
	}
	return nIndex;
}
int g_CalcVaration()
{
	int m_nUnit = 0;
	int nMode = g_clModelData[m_nUnit].nVarMode;
	int tartgeIndex = 0;
	if (nMode == 0)
	{
		//MIN
		tartgeIndex = findMinMax(0);
	}
	else if (nMode == 1)
	{
		//MAX
		tartgeIndex = findMinMax(1);
	}
	else
	{
		//중간값 , 평균은 이미지 선택이 안돼서 중간값으로 변경
		std::sort(g_clTaskWork[m_nUnit].m_stSfrInsp.dAver_Var, g_clTaskWork[m_nUnit].m_stSfrInsp.dAver_Var + g_clModelData[m_nUnit].nVarRepetCount);
		// 중간값 찾기
		tartgeIndex = g_clModelData[m_nUnit].nVarRepetCount / 2;
	}

	return tartgeIndex;
}
int g_AvrGetSFR(BYTE* ChartRawImage, int mSumCount)
{
	TCHAR	szLog[SIZE_OF_1K];
	int i = 0;
	int rtnCount = 1;
	int nUnit = 0;
#ifdef ON_LINE_MIL
	g_clVision.ClearOverlay(nUnit);
#endif
	float fMaxSfrN4[MAX_SFR_INSP_COUNT] = { 0.0, };

	if (g_GetSfrRectROI(nUnit, SFR_FINAL) == false)
	{
		g_clVision.DrawOverlayAll(nUnit);
		return -1;
	}


	bool sfrRt = false;

	//new
	std::shared_ptr<CACMISResolutionSFR> m_pSFRProc = std::make_shared<CACMISResolutionSFR>();
	POINT ptROICenter[MAX_SFR_INSP_COUNT];

	int mSfrSizeX = g_clModelData[nUnit].m_nRoiSizeX + 1;
	int mSfrSizeY = g_clModelData[nUnit].m_nRoiSizeY + 1;

	int mDirect = 0;
	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		mDirect = g_clModelData[nUnit].m_nDirection[i];
		if (mDirect == SFR_ROI_HORIZONTAL)
		{
			ptROICenter[i].x = g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[i].left + (mSfrSizeX / 2);
			ptROICenter[i].y = g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[i].top + (mSfrSizeY / 2);
		}
		else
		{
			ptROICenter[i].x = g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[i].left + (mSfrSizeY / 2);
			ptROICenter[i].y = g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[i].top + (mSfrSizeX / 2);
		}
		g_clTaskWork[nUnit].m_vDirection[i] = mDirect; // 0: Vertical, 1: Horizontal
		g_clTaskWork[nUnit].m_vFrquency[i] = g_clModelData[nUnit].m_dLinePulse;//0.225
		g_clTaskWork[nUnit].m_vOffset[i] = 0.0;
		g_clTaskWork[nUnit].m_vSFR[i] = 0.0;//0.5; 
		g_clTaskWork[nUnit].m_vThreshold[i] = 0.0;
		g_clTaskWork[nUnit].m_vROI[i].ptCenter.x = ptROICenter[i].x;
		g_clTaskWork[nUnit].m_vROI[i].ptCenter.y = ptROICenter[i].y;

		if (mDirect == SFR_ROI_HORIZONTAL)
		{
			g_clTaskWork[nUnit].m_vROI[i].nROIWidth = mSfrSizeX;
			g_clTaskWork[nUnit].m_vROI[i].nROIHeight = mSfrSizeY;
		}
		else
		{
			g_clTaskWork[nUnit].m_vROI[i].nROIWidth = mSfrSizeY;
			g_clTaskWork[nUnit].m_vROI[i].nROIHeight = mSfrSizeX;
		}
	}
	TSFRSpec m_stSFRSpec;
	m_stSFRSpec.tSFRConfig.nMaxROIWidth = mSfrSizeX;
	m_stSFRSpec.tSFRConfig.nMaxROIHeight = mSfrSizeY;
	m_stSFRSpec.tSFRConfig.dMaxEdgeAngle = 45.0;
	m_stSFRSpec.tSFRConfig.dPixelSize = g_clModelData[nUnit].m_dCcdCellSize;// 3.0;
	m_stSFRSpec.tSFRConfig.eAlgorithmType = ESFRAlgorithm_ISO12233;
	m_stSFRSpec.tSFRConfig.eAlgorithmMethod = ESFRMethod_Freq2SFR;
	m_stSFRSpec.tSFRConfig.eFrequencyUnit = ESFRFreq_LinePairPerMilliMeter;					// ESFRFreq_CyclePerPixel;//ESFRFreq_LinePairPerMilliMeter
	m_stSFRSpec.eSFRDeltaAlgorithmType = ESFRDelta_Diff;
	m_stSFRSpec.dEdgeDir = g_clTaskWork[nUnit].m_vDirection.data();
	m_stSFRSpec.dFrequency = g_clTaskWork[nUnit].m_vFrquency.data();
	m_stSFRSpec.dSFR = g_clTaskWork[nUnit].m_vSFR.data();
	m_stSFRSpec.dThreshold = g_clTaskWork[nUnit].m_vThreshold.data();
	m_stSFRSpec.dGamma = 1.0;
	m_stSFRSpec.tROI.dOffset = g_clTaskWork[nUnit].m_vOffset.data();
	m_stSFRSpec.tROI.eROIType = ROIType_POINT;
	m_stSFRSpec.tROI.pROIData = g_clTaskWork[nUnit].m_vROI.data();
	m_stSFRSpec.tROI.ROICount = MAX_SFR_INSP_COUNT;
	//m_stSFRSpec.tROI.dOffset = dOffset;

	m_stSFRSpec.tDelataSpec = NULL;


	bool bUse8BitOnly = false;

	TDATASPEC& tDataSpec = g_clLaonGrabberWrapper[nUnit].dSfr_Tdataspec;

	if (g_clModelData[nUnit].m_nSfr8BitUse == 1)
	{
		bUse8BitOnly = true;
	}
	bool bRet = m_pSFRProc->Inspect(ChartRawImage, g_clModelData[nUnit].m_nWidth, g_clModelData[nUnit].m_nHeight,
		m_stSFRSpec, tDataSpec.eDataFormat, tDataSpec.eOutMode, tDataSpec.eSensorType, tDataSpec.nBlackLevel, bUse8BitOnly, false, tDataSpec.eDemosaicMethod);
	if (bRet == false)
	{
		for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
		{
			g_clMesCommunication[nUnit].m_dMesUvAfterMTF[i] = 0.0;
			g_clMesCommunication[nUnit].m_nMesUvAfterMTFResultUVAfter[i] = 1;

		}
		for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
		{
			g_clMesCommunication[nUnit].m_dMesAreaAvrMTF[i] = 0.0;
			g_clMesCommunication[nUnit].m_nMesMTFAreaAvrResult[i] = 1;

		}
		g_clMesCommunication[nUnit].m_nMesFinalResult = 0;
		return -1;
	}

	int nSfrRoiIndex[MAX_SFR_INSP_COUNT] =
	{
		0, 0, 0, 0,
		1, 1,
		2, 2,
		3, 3,
		4, 4,
		5, 5,
		6, 6,
		7, 7,
		8, 8,

	};


	int sfrMax = m_pSFRProc->GetMaxResolutionCount();
	double sfrValue = 0.0;

	for (i = 0; i < sfrMax; i++)
	{
		const TSFRROIResult* pROIResult = m_pSFRProc->GetSFRROIResult(i);
		sfrValue = pROIResult->dFinalResult[0];

		if (g_clTaskWork[nUnit].m_stSfrInsp.mChartRectFind[nSfrRoiIndex[i]] == false)
		{
			sfrValue = 0.0;
		}
		if (pROIResult)
		{
			if (!_finite(sfrValue))
			{
				g_clTaskWork[nUnit].m_stSfrInsp.dAver_MTF[i][mSumCount] = 0.0;
			}
			else
			{
				g_clTaskWork[nUnit].m_stSfrInsp.dAver_MTF[i][mSumCount] = sfrValue;		//DIFF NG로 10번 측정한 DATA만 필요하다
			}
		}
		else
		{
			g_clTaskWork[nUnit].m_stSfrInsp.dAver_MTF[i][mSumCount] = 0.0;
		}
	}
	return 1;
}
//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
int g_GetSFR(BYTE* ChartRawImage, int nUnit, int nMode)
{
	TCHAR	szLog[SIZE_OF_1K];
	int i = 0;
	int rtnCount = 1;
#ifdef ON_LINE_MIL
	g_clVision.ClearOverlay(nUnit);
#endif
	double dsfrDiffMin = 0.0;
	double dsfrDiffMax = 0.0;


#ifdef ON_LINE_MIL
	/*int nSizeX = (int)MbufInquire(g_clVision.m_MilCcdProcChild[nUnit][1], M_SIZE_X, NULL);
	int nSizeY = (int)MbufInquire(g_clVision.m_MilCcdProcChild[nUnit][1], M_SIZE_Y, NULL);
	int nPitch = (int)MbufInquire(g_clVision.m_MilCcdProcChild[nUnit][1], M_PITCH, NULL);

	if (nSizeX <= 0 || nSizeY <= 0)
	{
		AddLog(_T("MilProcImageChild 사이즈 오류."), 1, nUnit);
		return -1;
	}*/
#endif

	if (g_GetSfrRectROI(nUnit, nMode) == false) 
	{
		g_clVision.DrawOverlayAll(nUnit);
		return -1;
	}


	bool sfrRt = false;

	//new
	std::shared_ptr<CACMISResolutionSFR> m_pSFRProc = std::make_shared<CACMISResolutionSFR>();
	POINT ptROICenter[MAX_SFR_INSP_COUNT];

	int mSfrSizeX = g_clModelData[nUnit].m_nRoiSizeX + 1;
	int mSfrSizeY = g_clModelData[nUnit].m_nRoiSizeY + 1; 
	
	int mDirect = 0;
	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		mDirect = g_clModelData[nUnit].m_nDirection[i];
		if (mDirect == SFR_ROI_HORIZONTAL)
		{
			ptROICenter[i].x = g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[i].left + (mSfrSizeX / 2);
			ptROICenter[i].y = g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[i].top + (mSfrSizeY / 2);
		}
		else
		{
			ptROICenter[i].x = g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[i].left + (mSfrSizeY / 2);
			ptROICenter[i].y = g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[i].top + (mSfrSizeX / 2);
		}
		g_clTaskWork[nUnit].m_vDirection[i] = mDirect; // 0: Vertical, 1: Horizontal
		g_clTaskWork[nUnit].m_vFrquency[i] = g_clModelData[nUnit].m_dLinePulse;//0.225
		g_clTaskWork[nUnit].m_vOffset[i] = 0.0;
		g_clTaskWork[nUnit].m_vSFR[i] = 0.0;//0.5; 
		g_clTaskWork[nUnit].m_vThreshold[i] = 0.0;
		g_clTaskWork[nUnit].m_vROI[i].ptCenter.x = ptROICenter[i].x;
		g_clTaskWork[nUnit].m_vROI[i].ptCenter.y = ptROICenter[i].y;

		if (mDirect == SFR_ROI_HORIZONTAL)
		{
			g_clTaskWork[nUnit].m_vROI[i].nROIWidth = mSfrSizeX;
			g_clTaskWork[nUnit].m_vROI[i].nROIHeight = mSfrSizeY;
		}
		else 
		{
			g_clTaskWork[nUnit].m_vROI[i].nROIWidth = mSfrSizeY;
			g_clTaskWork[nUnit].m_vROI[i].nROIHeight = mSfrSizeX;
		}
	}
	TSFRSpec m_stSFRSpec;
	m_stSFRSpec.tSFRConfig.nMaxROIWidth = mSfrSizeX;
	m_stSFRSpec.tSFRConfig.nMaxROIHeight = mSfrSizeY; 
	m_stSFRSpec.tSFRConfig.dMaxEdgeAngle = 45.0;
	m_stSFRSpec.tSFRConfig.dPixelSize = g_clModelData[nUnit].m_dCcdCellSize;// 3.0;
	m_stSFRSpec.tSFRConfig.eAlgorithmType = ESFRAlgorithm_ISO12233;
	m_stSFRSpec.tSFRConfig.eAlgorithmMethod = ESFRMethod_Freq2SFR;
	m_stSFRSpec.tSFRConfig.eFrequencyUnit = ESFRFreq_LinePairPerMilliMeter;					// ESFRFreq_CyclePerPixel;//ESFRFreq_LinePairPerMilliMeter
	m_stSFRSpec.eSFRDeltaAlgorithmType = ESFRDelta_Diff;
	m_stSFRSpec.dEdgeDir = g_clTaskWork[nUnit].m_vDirection.data();
	m_stSFRSpec.dFrequency = g_clTaskWork[nUnit].m_vFrquency.data();
	m_stSFRSpec.dSFR = g_clTaskWork[nUnit].m_vSFR.data(); 
	m_stSFRSpec.dThreshold = g_clTaskWork[nUnit].m_vThreshold.data();
	m_stSFRSpec.dGamma = 1.0;
	m_stSFRSpec.tROI.dOffset = g_clTaskWork[nUnit].m_vOffset.data();
	m_stSFRSpec.tROI.eROIType = ROIType_POINT;
	m_stSFRSpec.tROI.pROIData = g_clTaskWork[nUnit].m_vROI.data();
	m_stSFRSpec.tROI.ROICount = MAX_SFR_INSP_COUNT;
	//m_stSFRSpec.tROI.dOffset = dOffset;
	
	m_stSFRSpec.tDelataSpec = NULL;

	
	bool bUse8BitOnly = false;

	TDATASPEC& tDataSpec = g_clLaonGrabberWrapper[nUnit].dSfr_Tdataspec;

	if (g_clModelData[nUnit].m_nSfr8BitUse == 1)
	{
		bUse8BitOnly = true;
	}
	bool bRet = m_pSFRProc->Inspect(ChartRawImage, g_clModelData[nUnit].m_nWidth, g_clModelData[nUnit].m_nHeight,
		m_stSFRSpec, tDataSpec.eDataFormat, tDataSpec.eOutMode, tDataSpec.eSensorType, tDataSpec.nBlackLevel, bUse8BitOnly, false, tDataSpec.eDemosaicMethod);
	if (bRet == false)
	{
		for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
		{
			g_clMesCommunication[nUnit].m_dMesUvAfterMTF[i] = 0.0;
			g_clMesCommunication[nUnit].m_nMesUvAfterMTFResultUVAfter[i] = 1;

		}
		for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
		{
			g_clMesCommunication[nUnit].m_dMesAreaAvrMTF[i] = 0.0;
			g_clMesCommunication[nUnit].m_nMesMTFAreaAvrResult[i] = 1;

		}
		g_clMesCommunication[nUnit].m_nMesFinalResult = 0;
		return -1;
	}
	//
	//g_clLaonGrabberWrapper[nUnit].dTDATASPEC_n.eSensorType,
	//4/1이미지로 측정시
	//DataFormat: 5 (DATAFORMAT_BAYER_PARALLEL_12BIT)
	//OutMode : 5 (OUTMODE_BAYER_BLACKWHITE)
	//SensorType : 3 (SENSORTYPE_RCCC)

	double dSaturationTemp[MAX_SFR_INSP_COUNT] = { 0.0, };
	int nSfrRoiIndex[MAX_SFR_INSP_COUNT] = 
	{ 
		0, 0, 0, 0,
		1, 1,
		2, 2,
		3, 3,
		4, 4,
		5, 5,
		6, 6,
		7, 7,
		8, 8,

	};


	int sfrMax = m_pSFRProc->GetMaxResolutionCount();
	double sfrValue = 0.0;

	for (i = 0; i < sfrMax; i++)
	{
		const TSFRROIResult* pROIResult = m_pSFRProc->GetSFRROIResult(i);
		sfrValue = pROIResult->dFinalResult[0];

		if (g_clTaskWork[nUnit].m_stSfrInsp.mChartRectFind[nSfrRoiIndex[i]] == false)
		{
			sfrValue = 0.0;
		}
		if (pROIResult)
		{
			if (!_finite(sfrValue))
			{
				g_clMesCommunication[nUnit].m_dMesUvAfterMTF[i] = 0.0;
			} 
			else
			{
				g_clMesCommunication[nUnit].m_dMesUvAfterMTF[i] = sfrValue;
			}
		}
		else
		{
			//g_clTaskWork[nUnit].m_stSfrInsp._64_fSfrN4[i] = 0.0;
			g_clMesCommunication[nUnit].m_dMesUvAfterMTF[i] = 0.0;
		}


		dSaturationTemp[i] = m_pSFRProc->GetSaturationResult(i);
	}
	CString NGData = _T("");
	bool sfrRtn = true;


	g_clMesCommunication[nUnit].m_dMesSaturationChart[0] = (dSaturationTemp[0] + dSaturationTemp[1] + dSaturationTemp[2] + dSaturationTemp[3]) / 4.0;
	g_clMesCommunication[nUnit].m_dMesSaturationChart[1] = (dSaturationTemp[4] + dSaturationTemp[5]) / 2.0;
	g_clMesCommunication[nUnit].m_dMesSaturationChart[2] = (dSaturationTemp[6] + dSaturationTemp[7]) / 2.0;
	g_clMesCommunication[nUnit].m_dMesSaturationChart[3] = (dSaturationTemp[8] + dSaturationTemp[9]) / 2.0;
	g_clMesCommunication[nUnit].m_dMesSaturationChart[4] = (dSaturationTemp[10] + dSaturationTemp[11]) / 2.0;
	g_clMesCommunication[nUnit].m_dMesSaturationChart[5] = (dSaturationTemp[12] + dSaturationTemp[13]) / 2.0;
	g_clMesCommunication[nUnit].m_dMesSaturationChart[6] = (dSaturationTemp[14] + dSaturationTemp[15]) / 2.0;
	g_clMesCommunication[nUnit].m_dMesSaturationChart[7] = (dSaturationTemp[16] + dSaturationTemp[17]) / 2.0;
	g_clMesCommunication[nUnit].m_dMesSaturationChart[8] = (dSaturationTemp[18] + dSaturationTemp[19]) / 2.0;
	

	int nStep = 0;// g_clTaskWork[nUnit].m_nCountOfTotalStepAA;
	int sfrIndex = 0;

	g_clTaskWork[nUnit].m_stSfrInsp._fAverSfr[0] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[0] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[1] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[2] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[3]) / 4.0;
	g_clTaskWork[nUnit].m_stSfrInsp._fAverSfr[1] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[4] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[5]) / 2.0;
	g_clTaskWork[nUnit].m_stSfrInsp._fAverSfr[2] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[6] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[7]) / 2.0;
	g_clTaskWork[nUnit].m_stSfrInsp._fAverSfr[3] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[8] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[9]) / 2.0;
	g_clTaskWork[nUnit].m_stSfrInsp._fAverSfr[4] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[10] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[11]) / 2.0;
	g_clTaskWork[nUnit].m_stSfrInsp._fAverSfr[5] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[12] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[13]) / 2.0;
	g_clTaskWork[nUnit].m_stSfrInsp._fAverSfr[6] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[14] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[15]) / 2.0;
	g_clTaskWork[nUnit].m_stSfrInsp._fAverSfr[7] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[16] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[17]) / 2.0;
	g_clTaskWork[nUnit].m_stSfrInsp._fAverSfr[8] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[18] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[19]) / 2.0;
	//---------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------
	//Spec Check
	//---------------------------------------------------------------------------------------------------

	//
	_stprintf_s(szLog, SIZE_OF_1K, _T("[SFR] SPEC CHECK!!"));
	AddLog(szLog, 0, nUnit);
	char szTmp[256];
	
	
	

	TCHAR* pszRow[] = {
		_T("[0] CT_00F_V"), _T("[1] CB_OOF_V"), _T("[2] CL_00F_H"), _T("[3] CR_00F_H"),
		_T("[4] LT_05F_V"), _T("[5] LT_05F_H"), _T("[6] RT_05F_V"), _T("[7] RT_05F_H"),
		_T("[8] LB_05F_V"), _T("[9] LB_05F_H"), _T("[10] RB_05F_V"), _T("[11] RB_05F_H"),
		_T("[12] LT_08F_V") ,_T("[13] LT_08F_H"), _T("[14] RT_08F_V"), _T("[15] RT_08F_H"),
		_T("[16] LB_08F_V"), _T("[17] LB_08F_H"), _T("[18] RB_08F_V") ,_T("[19] RB_08F_H"),
	};

	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		g_clMesCommunication[nUnit].m_nMesUvAfterMTFResultUVAfter[i] = 1;

	}
	for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
	{
		g_clMesCommunication[nUnit].m_nMesMTFAreaAvrResult[i] = 1;

	}
	
	double dSfrAverageValue[MAX_LAST_INSP_COUNT];

	dSfrAverageValue[0] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[0] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[1] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[2] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[3]) / 4;		//CENTER
	dSfrAverageValue[1] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[4] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[5]) / 2;		//0.5F T
	dSfrAverageValue[2] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[6] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[7]) / 2;		//0.5F B
	dSfrAverageValue[3] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[8] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[9]) / 2;		//0.5F L
	dSfrAverageValue[4] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[10] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[11]) / 2;	//0.5F R
	//
	dSfrAverageValue[5] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[12] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[13]) / 2;	//0.7F LT
	dSfrAverageValue[6] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[14] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[15]) / 2;	//0.7F RT
	dSfrAverageValue[7] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[16] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[17]) / 2;	//0.7F LB
	dSfrAverageValue[8] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[18] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[19]) / 2;	//0.7F RB

	for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
	{
		g_clMesCommunication[nUnit].m_dMesAreaAvrMTF[i] = dSfrAverageValue[i];
	}
	double mTempMax = 0.0;
	double mTempMin = 0.0;
	double mTempAvr = 0.0;



	
	double mMinSpec = 0.0;
	double mMaxSpec = 0.0;
	double SfrTemp = 0.0;
#if 0		
	//다른곳으로 이동
	double min = 0.0;
	double max = 0.0;

	double mDif4F = 0.0;
	double mDif7F = 0.0;
	double dEdgeAvr_4F[4];
	double dEdgeAvr_7F[4];
	dEdgeAvr_4F[0] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[4] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[5]) / 2;
	dEdgeAvr_4F[1] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[6] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[7]) / 2;
	dEdgeAvr_4F[2] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[8] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[9]) / 2;
	dEdgeAvr_4F[3] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[10] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[11]) / 2;
	//
	dEdgeAvr_7F[0] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[12] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[13]) / 2;
	dEdgeAvr_7F[1] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[14] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[15]) / 2;
	dEdgeAvr_7F[2] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[16] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[17]) / 2;
	dEdgeAvr_7F[3] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[18] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[19]) / 2;

	min = *std::min_element(dEdgeAvr_4F, dEdgeAvr_4F + 4);
	max = *std::max_element(dEdgeAvr_4F, dEdgeAvr_4F + 4);
	g_clMesCommunication[nUnit].m_dMes4F_Diff = max - min;
	
	min = *std::min_element(dEdgeAvr_7F, dEdgeAvr_7F + 4);
	max = *std::max_element(dEdgeAvr_7F, dEdgeAvr_7F + 4);
	g_clMesCommunication[nUnit].m_dMes7F_Diff = max - min;
	mMinSpec = (_ttof(EEpromVerifyData.vMinData[11]));	//04F DIFF
	mMaxSpec = (_ttof(EEpromVerifyData.vMaxData[11]));
	SfrTemp = g_clMesCommunication[nUnit].m_dMes4F_Diff;

	if (SfrTemp < mMinSpec || SfrTemp > mMaxSpec)
	{
		sfrRtn = false;
		g_clMesCommunication[nUnit].m_nMesFinalResult = 0;	//MTF//XX
		g_clMesCommunication[nUnit].m_dMes4F_DiffResult = 0;
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 04F DIFF SPEC OUT:%.3lf[%.3lf ~ %.3lf]"), SfrTemp, mMinSpec, mMaxSpec);
		AddLog(szLog, 0, nUnit);

		NGData.Format(_T("%s"), szLog);

		if (g_clMandoInspLog[nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[nUnit].m_sDispNG[g_clMandoInspLog[nUnit].m_nNGCnt] += NGData;
			g_clMandoInspLog[nUnit].m_nNGCnt++;
		}
	}
	else
	{
		g_clMesCommunication[nUnit].m_dMes4F_DiffResult = 1;
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 04F DIFF SPEC IN =  %.3lf[%.3lf ~ %.3lf]"), SfrTemp, mMinSpec, mMaxSpec);
		AddLog(szLog, 0, nUnit);
	}
	mMinSpec = (_ttof(EEpromVerifyData.vMinData[11]));	//07F DIFF
	mMaxSpec = (_ttof(EEpromVerifyData.vMaxData[11]));
	SfrTemp = g_clMesCommunication[nUnit].m_dMes7F_Diff;

	if (SfrTemp < mMinSpec || SfrTemp > mMaxSpec)
	{
		sfrRtn = false;
		g_clMesCommunication[nUnit].m_nMesFinalResult = 0;	//MTF//XX
		g_clMesCommunication[nUnit].m_dMes7F_DiffResult = 0;
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 07F DIFF SPEC OUT:%.3lf[%.3lf ~ %.3lf]"), SfrTemp, mMinSpec, mMaxSpec);
		AddLog(szLog, 0, nUnit);

		NGData.Format(_T("%s"), szLog);

		if (g_clMandoInspLog[nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[nUnit].m_sDispNG[g_clMandoInspLog[nUnit].m_nNGCnt] += NGData;
			g_clMandoInspLog[nUnit].m_nNGCnt++;
		}
	}
	else
	{
		g_clMesCommunication[nUnit].m_dMes7F_DiffResult = 1;
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 07F DIFF SPEC IN =  %.3lf[%.3lf ~ %.3lf]"), SfrTemp, mMinSpec, mMaxSpec);
		AddLog(szLog, 0, nUnit);
	}
#endif
	//_stprintf_s(szLog, SIZE_OF_1K, _T("MTF DIFF 4F : %.3lf"),  g_clMesCommunication[nUnit].m_dMes4F_Diff);// , mMinSpec, mMaxSpec);
	//AddLog(szLog, 0, nUnit);
	//_stprintf_s(szLog, SIZE_OF_1K, _T("MTF DIFF 7F : %.3lf"), g_clMesCommunication[nUnit].m_dMes7F_Diff);// , mMinSpec, mMaxSpec);
	//AddLog(szLog, 0, nUnit);
	
	//if (true)		//g_clModelData[nUnit].m_nSfrAvrCheck == 1)
	//평균으로 sfr 스펙 판정
	
	


	//nSfrRoiIndex


	const int SfrMesIndex = 4;


	TCHAR* pszSfrRow[] = {
		_T("0F T V"),	_T("0F B V"),_T("0F L H"),_T("0F R H"),
		_T("4F LT H"),_T("4F LT V"),
		_T("4F RT H"),_T("4F RT V"),
		_T("4F LB H"),_T("4F LB V"),
		_T("4F RB H"),_T("4F RB V"),
		//
		_T("7F LT H"),_T("7F LT V"),
		_T("7F RT H"),_T("7F RT V"),
		_T("7F LB H"),_T("7F LB V"),
		_T("7F RB H"),_T("7F RB V"),
	};

	int nindex = 0;
	//sfr 양불 판정 개별 
	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		nindex = nSfrRoiIndex[i];
		//mMinSpec = (_ttof(EEpromVerifyData.vMinData[nindex + SfrMesIndex]));

		//mMinSpec = (_ttof(g_clMesCommunication[nUnit].mapKeyRtn(g_clMesCommunication[nUnit].vPPRecipeSpecEquip[0], pszSfrSpecList[i]));
		//mMaxSpec = (_ttof(EEpromVerifyData.vMaxData[nindex + SfrMesIndex]));

		mMinSpec = g_clMesCommunication[nUnit].mapKeyRtn(RECIPE_PARAM_NAME[6 + nindex]);


		SfrTemp = g_clMesCommunication[nUnit].m_dMesUvAfterMTF[i];

		if (SfrTemp < mMinSpec)// || SfrTemp > mMaxSpec)
		{
			g_clTaskWork[nUnit].m_bOutputCheck[1] = false;	//MTF
			g_clMesCommunication[nUnit].m_nMesFinalResult = 0;	//MTF
			g_clMesCommunication[nUnit].m_nMesMTFResult[i] = 0;

			NGData.Format(_T("SFR[%s] SPEC NG : %lf[%.3lf ~ ]"), pszSfrRow[i], SfrTemp, mMinSpec);
			_stprintf_s(szLog, SIZE_OF_1K, _T("SFR[%s] SPEC NG : %lf[%.3lf ~ ]"), pszSfrRow[i], SfrTemp, mMinSpec);
			AddLog(szLog, 0, nUnit);
			if (g_clMandoInspLog[nUnit].m_nNGCnt < 30)
			{
				g_clMandoInspLog[nUnit].m_sDispNG[g_clMandoInspLog[nUnit].m_nNGCnt] += NGData;
				g_clMandoInspLog[nUnit].m_nNGCnt++;
			}
		}
		else
		{
			g_clMesCommunication[nUnit].m_nMesMTFResult[i] = 1;
			_stprintf_s(szLog, SIZE_OF_1K, _T("SFR[%s] SPEC IN : %lf[%.3lf ~ ]"), pszSfrRow[i], SfrTemp, mMinSpec);
			AddLog(szLog, 0, nUnit);
		}
	}

	AddLog(_T("	"), 0, nUnit);


	//_T("0F T V"),	_T("0F B V"),_T("0F L H"),_T("0F R H"),
	//l,t,r,b
	//2,0,3,1
	if (g_clMesCommunication[nUnit].m_nMesMTFResult[2] == 0)
	{
		g_clMesCommunication[nUnit].m_dEqpDefectCode.Format(_T("16"));
	}
	if (g_clMesCommunication[nUnit].m_nMesMTFResult[0] == 0)
	{
		g_clMesCommunication[nUnit].m_dEqpDefectCode.Format(_T("17"));
	}
	if (g_clMesCommunication[nUnit].m_nMesMTFResult[3] == 0)
	{
		g_clMesCommunication[nUnit].m_dEqpDefectCode.Format(_T("18"));
	}
	if (g_clMesCommunication[nUnit].m_nMesMTFResult[1] == 0)
	{
		g_clMesCommunication[nUnit].m_dEqpDefectCode.Format(_T("19"));
	}
	for (i = 0; i < 8; i++)
	{
		if (g_clMesCommunication[nUnit].m_nMesMTFResult[4 + (i * 2)] == 0 || g_clMesCommunication[nUnit].m_nMesMTFResult[4 + (i * 2) + 1] == 0)
		{
			g_clMesCommunication[nUnit].m_dEqpDefectCode.Format(_T("%d"), 20 + i);
		}
	}


    //---------------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------------
#ifdef ON_LINE_MIL
	CPoint _ccdMp;
	_ccdMp.x = g_clModelData[nUnit].m_nWidth / 2;
	_ccdMp.y = g_clModelData[nUnit].m_nHeight / 2;
	g_clVision.DrawOverlayCross(nUnit, nUnit, _ccdMp, 500, RGB(255, 0, 0), 1);


    g_clVision.DrawOverlayAll(nUnit);
#endif
	NGData.Empty();

	g_SaveLGITLog(nUnit, "SFR", m_pSFRProc->GetLogHeader(), m_pSFRProc->GetLogData(), m_pSFRProc->GetVersion());
    return 1;
}

void InterLockMsg(CString _title, CString _msg, COLORREF bgColor, bool bUse)
{
	int nIndex;
	nIndex = g_nPopupIndex;
	if (bUse == true)
	{
		InterLockDlg->setDlg(_title, _msg, bgColor, nIndex);
		InterLockDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		InterLockDlg->ShowWindow(SW_HIDE);
	}

	InterLockDlg->Invalidate();
}
//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool g_GetIllumination(int nUnit, BYTE* RawImage, double &dShiftX, double &dShiftY)
{
#if 0
	TCHAR	szLog[SIZE_OF_1K];
	bool bRtn = false;
	int nResult = R_RESULT_PASS;
	int nWidth = g_clModelData[nUnit].m_nWidth;
	int nHeight = g_clModelData[nUnit].m_nHeight;
	TDATASPEC& tDataSpec = g_clLaonGrabberWrapper[nUnit].dTDATASPEC_n;
	std::shared_ptr<CACMISOpticalCenterCentroid> m_pOpticalCenter = std::make_shared<CACMISOpticalCenterCentroid>();
	int specCount = 0;
	TOpticalCenter tOpticalCenter;

	tOpticalCenter.dOpticalCenterSpecX = g_clModelData[nUnit].m_ICSpec[specCount++];// 20;
	tOpticalCenter.dOpticalCenterSpecY = g_clModelData[nUnit].m_ICSpec[specCount++];//20;
	tOpticalCenter.dPixelPitch =g_clModelData[nUnit].m_ICSpec[specCount++];//3.75;  3.75;// 
	//specCount++;
	tOpticalCenter.dThresholdRatio = g_clModelData[nUnit].m_ICSpec[specCount++];//0.5;
	tOpticalCenter.nOCBlockSize = (int)g_clModelData[nUnit].m_ICSpec[specCount++];//100
	tOpticalCenter.nEdgeTopMargin = (int)g_clModelData[nUnit].m_ICSpec[specCount++];//5

	if (m_pOpticalCenter->Inspect(RawImage, nWidth, nHeight, tOpticalCenter, tDataSpec.eDataFormat, tDataSpec.eOutMode, tDataSpec.eSensorType, tDataSpec.nBlackLevel, false) == false)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("Illumination 측정 실패"));
		AddLog(szLog, 0, nUnit);
		return false;
	}

	g_clVision.ClearOverlay(nUnit);
	//g_clVision.DrawOverlayAll(nUnit);

	const DPOINT* dResultPos;
	dResultPos = m_pOpticalCenter->GetOpticalCenterResult();
	int rtnX = dResultPos->x - (nWidth / 2);
	int rtnY = dResultPos->y - (nHeight / 2);



	dShiftX = rtnX * 0.5;
	dShiftY = rtnY * 0.5;

	dShiftX *= g_clModelData[nUnit].m_dCcdCellSize / 1000;
	dShiftY *= g_clModelData[nUnit].m_dCcdCellSize / 1000;

	char strTmp[1024];

	sprintf_s(strTmp, "Shift X :%.3lf, Shift  Y :%.3lf", dShiftX, dShiftY);
	AddLog(strTmp, 0, nUnit);
	g_clVision.DrawMOverlayText(nUnit, (nWidth / 2), (nHeight / 2) - 50, strTmp, M_COLOR_BLACK, _T("Arial"), 10, 0);
	sprintf_s(strTmp, "X :%d, Y :%d", rtnX, rtnY);
	AddLog(strTmp, 0, nUnit);

	g_clVision.DrawMOverlayText(nUnit, (nWidth / 2), (nHeight / 2), strTmp, M_COLOR_BLACK, _T("Arial"), 10, 0);
	//std::cout << "[Illumination Center] x= %.3f" << dResultPos->x << std::endl;
	//std::cout << "[Illumination Center] y= %.3f" << dResultPos->y << std::endl;

	//g_clVision.ClearOverlay(nUnit);
	g_clVision.DrawOverlayAll(nUnit);
#endif
	return true;
}
//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
int g_Get_AA_MTF(int nUnit, BYTE* RawImage, int nMode)
{
	TCHAR	szLog[SIZE_OF_1K];
	int i;
#ifdef ON_LINE_MIL
	g_clVision.ClearOverlay(nUnit);


	float fMaxSfrN4[MAX_SFR_INSP_COUNT] = { 0.0, };


	int nSizeX = (int)MbufInquire(g_clVision.m_MilCcdProcChild[nUnit][1], M_SIZE_X, NULL);
	int nSizeY = (int)MbufInquire(g_clVision.m_MilCcdProcChild[nUnit][1], M_SIZE_Y, NULL);
	int nPitch = (int)MbufInquire(g_clVision.m_MilCcdProcChild[nUnit][1], M_PITCH, NULL);

	if (nSizeX <= 0 || nSizeY <= 0)
	{
		AddLog(_T("MilProcImageChild 사이즈 오류."), 0, nUnit);
		return -1;
	}

	/*for (i = 0; i < 4; i++)
	{
		g_clTaskWork[nUnit].m_stSfrInsp.clRectROI[i] = g_clModelData[nUnit].m_clSfrInfo.m_clRectCircle[i];
		g_clVision.DrawMOverlayBox(nUnit, nUnit, g_clTaskWork[nUnit].m_stSfrInsp.clRectROI[i], M_COLOR_GREEN, 1, FALSE, PS_DOT);
	
	}*/
#endif
	if (g_GetSfrRectROI(nUnit, nMode) == false)
	{
		g_clVision.DrawOverlayAll(nUnit);
		return -1;
	}

	return 1;
}

//-----------------------------------------------------------------------------
//
//	원형마크 찾은 결과를 바탕으로 SFR 사각 영역을 정한다.
//
//-----------------------------------------------------------------------------
bool g_GetSfrRectROI(int nUnit, int nMode)
{
	int nPitch, nSizeX, nSizeY;
	int nHeightX, nHeightY, nWidthX, nWidthY;
	int nModelHeightX, nModelHeightY, nModelWidthX, nModelWidthY;
	double dRadX, dRadY, dModelRadX, dModelRadY;
	double dDegX, dDegY, dModelDegX, dModelDegY;
	double dRadAvg;
    TCHAR szPos[SIZE_OF_100BYTE];
    CString sLog;

	nPitch = (int)MbufInquire(g_clVision.m_MilCcdProcChild[nUnit][1], M_PITCH, M_NULL);
	nSizeX = (int)MbufInquire(g_clVision.m_MilCcdProcChild[nUnit][1], M_SIZE_X, M_NULL);	//1820
	nSizeY = (int)MbufInquire(g_clVision.m_MilCcdProcChild[nUnit][1], M_SIZE_Y, M_NULL);	//940

    //원형마크 찾기
	bool bCircleFind = false;
	//bCircleFind = g_FindCirclePos(nUnit, g_clVision.m_pImgBuff[nUnit][1], g_clModelData[nUnit].m_clSfrInfo.m_clRectCircle);
	//bCircleFind = g_OpencvFindCirclePos(nUnit, g_clLaonGrabberWrapper[nUnit].m_pFrameRawBuffer, g_clModelData[nUnit].m_clSfrInfo.m_clRectCircle);	//func_Insp_Shm_Fov_Distortion

	bCircleFind = g_MilFindCirclePos(nUnit, g_clLaonGrabberWrapper[nUnit].m_pFrameRawBuffer, g_clModelData[nUnit].m_clSfrInfo.m_clRectCircle);		//g_GetSfrRectROI

	TCHAR szLog[SIZE_OF_1K];
	if (bCircleFind  == false)
	{ 
		_stprintf_s(szLog, SIZE_OF_1K, _T("[ERR] 원형 마크 확인 실패 "));
		AddLog(szLog, 0, nUnit);
		return false;
	}

	double dCenterPosX = 0.0;
	double dCenterPosY = 0.0;
	bool bPatRtn = false;


	
	int offsetX = ((g_clModelData[nUnit].m_nWidth / 2) - (g_clTaskWork[nUnit].m_clPtCircle[0].x + g_clTaskWork[nUnit].m_clPtCircle[1].x + g_clTaskWork[nUnit].m_clPtCircle[2].x + g_clTaskWork[nUnit].m_clPtCircle[3].x) / 4) * -1;
	int offsetY = ((g_clModelData[nUnit].m_nHeight / 2) - (g_clTaskWork[nUnit].m_clPtCircle[0].y + g_clTaskWork[nUnit].m_clPtCircle[1].y + g_clTaskWork[nUnit].m_clPtCircle[2].y + g_clTaskWork[nUnit].m_clPtCircle[3].y) / 4) * -1;


	int nShiftX = 0;
	int nShiftY = 0;
	double dCenterX = nSizeX / 2;
	double dCenterY = nSizeY / 2;

	int nSx, nSy, nEx, nEy;

	int nCount;
	int i;

    nCount = MAX_LAST_INSP_COUNT;

	for (i = 0; i < nCount; i++)
	{
		nSx = g_clModelData[nUnit].m_clSfrInfo.m_clPtOffset[i].x + offsetX; //(int)(dRealX + 0.5);
		nSy = g_clModelData[nUnit].m_clSfrInfo.m_clPtOffset[i].y + offsetY;//(int)(dRealY + 0.5);
		
		nEx = (int)(nSx + g_clModelData[nUnit].m_clSfrInfo.m_nSizeX[i]);
		nEy = (int)(nSy + g_clModelData[nUnit].m_clSfrInfo.m_nSizeY[i]);

		if (nSx < 0)	nSx = 0;
		if (nSy < 0)	nSy = 0;
		if (nEx > nSizeX)	nEx = nSizeX - 1;
		if (nEy > nSizeY)	nEy = nSizeY - 1;

		g_clTaskWork[nUnit].m_stSfrInsp.clRect[i].left = nSx;
		g_clTaskWork[nUnit].m_stSfrInsp.clRect[i].top = nSy;
		g_clTaskWork[nUnit].m_stSfrInsp.clRect[i].right = nEx;
		g_clTaskWork[nUnit].m_stSfrInsp.clRect[i].bottom = nEy;

		g_clTaskWork[nUnit].m_stSfrInsp.mChartRectFind[i] = true;


        bool rtn = false; 
//#ifdef  CHART_FIND_PATTERN_MODE
		if (g_clModelData[nUnit].m_nPatternChartUse == 1)
		{
			//패턴이미지
			rtn = findRectPosPattern(nUnit, g_clVision.m_pImgBuff[nUnit][1], nPitch, nSizeX, nSizeY, i, g_clTaskWork[nUnit].m_stSfrInsp.clRect[i]);
			if (rtn)
			{
				g_clVision.DrawMOverlayBox(nUnit, nUnit, g_clTaskWork[nUnit].m_stSfrInsp.clRect[i], M_COLOR_MAGENTA, 1, FALSE, PS_SOLID);
			}
			else
			{
				g_clTaskWork[nUnit].m_stSfrInsp.mChartRectFind[i] = false;
				g_clVision.DrawMOverlayBox(nUnit, nUnit, g_clTaskWork[nUnit].m_stSfrInsp.clRect[i], M_COLOR_RED, 1, FALSE, PS_SOLID);

				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] #%d CHART FIND FAIL "), i);
				AddLog(szLog, 0, nUnit);
			}
			//
			if (findSmallSfrRectPos(nUnit, g_clVision.m_pImgBuff[nUnit][1], nPitch, nSizeX, nSizeY, i, g_clTaskWork[nUnit].m_stSfrInsp.clRect[i]) == false)
			{
				g_clVision.DrawMOverlayBox(nUnit, nUnit, g_clTaskWork[nUnit].m_stSfrInsp.clRect[i], M_COLOR_RED, 1, FALSE, PS_DOT);
				continue;
			}
		}
		else
		{
			//자동찾기
			if (g_FindRectPos2(nUnit, g_clVision.m_pImgBuff[nUnit][1], nPitch, nSizeX, nSizeY, i, g_clTaskWork[nUnit].m_stSfrInsp.clRect[i]) == false)
			{
				g_clTaskWork[nUnit].m_stSfrInsp.mChartRectFind[i] = false;
				g_clVision.DrawMOverlayBox(nUnit, nUnit, g_clTaskWork[nUnit].m_stSfrInsp.clRect[i], M_COLOR_RED, 1, FALSE, PS_SOLID);
				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] #%d CHART FIND FAIL "), i);
				AddLog(szLog, 0, nUnit);
				continue;
			}
			else
			{
				
				g_clVision.DrawMOverlayBox(nUnit, nUnit, g_clTaskWork[nUnit].m_stSfrInsp.clRect[i], M_COLOR_DARK_CYAN, 1, FALSE, PS_SOLID);//패턴 가이드 색상
			}


			if (g_FindSfrRectPos(nUnit, g_clVision.m_pImgBuff[nUnit][1], nPitch, nSizeX, nSizeY, i, g_clTaskWork[nUnit].m_stSfrInsp.clRect[i]) == false)
			{
				g_clVision.DrawMOverlayBox(nUnit, nUnit, g_clTaskWork[nUnit].m_stSfrInsp.clRect[i], M_COLOR_RED, 1, FALSE, PS_DOT);
				continue;
			}
		}

	}

	//g_clVision.DrawOverlayAll(nUnit);

	return true;
}
//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool g_FindFovPos(int nUnit, unsigned char* pImage, int nPitch, int nSizeX, int nSizeY, CRect* clRectRoi)
{
    int maxSize = 100;

    TCHAR szLog[SIZE_OF_1K];

    if (pImage == NULL)
    {
        _stprintf_s(szLog, SIZE_OF_1K, _T("영상 버퍼가 잘못되었습니다."));
        AddLog(szLog, 0, nUnit);
        return false;
    }

    if (nSizeX <= 0 || nSizeY <= 0)
    {
        _stprintf_s(szLog, SIZE_OF_1K, _T("영상 사이즈가 잘못되었습니다. ( X : %d Y : %d )"), nSizeX, nSizeY);
        AddLog(szLog, 0, nUnit);

        return false;
    }

    int aiHistX[5000];
    int aiHistY[5000];
	double offsetX = g_clTaskWork[nUnit].m_dOcResultX;
	double offsetY = g_clTaskWork[nUnit].m_dOcResultY;// *-1;
	//double dCenterX = nSizeX / 2;
	//double dCenterY = nSizeY / 2;
	//int nShiftX = dCenterX - (g_clTaskWork[nUnit].m_clPtCircle[0].x + g_clTaskWork[nUnit].m_clPtCircle[1].x + g_clTaskWork[nUnit].m_clPtCircle[2].x + g_clTaskWork[nUnit].m_clPtCircle[3].x) / 4;
	//int nShiftY = dCenterY - (g_clTaskWork[nUnit].m_clPtCircle[0].y + g_clTaskWork[nUnit].m_clPtCircle[1].y + g_clTaskWork[nUnit].m_clPtCircle[2].y + g_clTaskWork[nUnit].m_clPtCircle[3].y) / 4;


	//int offsetX = ((g_clModelData[nUnit].m_nWidth / 2) - (g_clTaskWork[nUnit].m_clPtCircle[0].x + g_clTaskWork[nUnit].m_clPtCircle[1].x + g_clTaskWork[nUnit].m_clPtCircle[2].x + g_clTaskWork[nUnit].m_clPtCircle[3].x) / 4) * -1;
	//int offsetY = ((g_clModelData[nUnit].m_nHeight / 2) - (g_clTaskWork[nUnit].m_clPtCircle[0].y + g_clTaskWork[nUnit].m_clPtCircle[1].y + g_clTaskWork[nUnit].m_clPtCircle[2].y + g_clTaskWork[nUnit].m_clPtCircle[3].y) / 4) * -1;



	offsetX = (g_clModelData[nUnit].m_clSfrInfo.m_dFovOcX - g_clTaskWork[nUnit].m_dOcResultX) * -1;
	offsetY = (g_clModelData[nUnit].m_clSfrInfo.m_dFovOcY - g_clTaskWork[nUnit].m_dOcResultY) * -1;

	//offsetX = nShiftX * -1;
	//offsetY = nShiftY * -1;

	//CRect m_clRectFovTemp;
	//m_clRectFovTemp = g_clModelData[nUnit].m_clSfrInfo.m_clRectFov;
	/*clRectRoi->left += offsetX;
	clRectRoi->right += offsetX;
	clRectRoi->bottom += offsetY;
	clRectRoi->top += offsetY;
*/
	//g_clVision.DrawMOverlayBox(nUnit,m_clRectFovTemp,M_COLOR_DARK_YELLOW, 1, FALSE, PS_SOLID);
	//g_clVision.DrawOverlayAll(nUnit);

    for (int i = 0; i < VEC_FOV_COUNT; i++)
    {
		clRectRoi[i].left += offsetX; 
		clRectRoi[i].top += offsetY;
		clRectRoi[i].right += offsetX;
		clRectRoi[i].bottom += offsetY;

        //if (i > 2 && i < 6)continue;
		if (i > 3)continue;
        if (clRectRoi[i].left < 0 || clRectRoi[i].top < 0 || clRectRoi[i].right > nSizeX || clRectRoi[i].bottom > nSizeY)
        {
            _stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] FOV 검색 영역이 잘못되었습니다. ( L %d,  T %d,  R %d,  B %d )"), i + 1, clRectRoi[i].left, clRectRoi[i].top, clRectRoi[i].right, clRectRoi[i].bottom);
            AddLog(szLog, 0, nUnit);

            return false;
        }
		 
        int iSx, iSy, iEx, iEy;
        int x, y, iPos;
        int iMaxX = -1, iMinX = 9999;
        int iMaxY = -1, iMinY = 9999;
        int iMax_Left = -1, iMax_Right = -1, iMax_Up = -1, iMax_Down = -1;

        int iMaxX2 = -1, iMinX2 = 9999;
        int iMaxY2 = -1, iMinY2 = 9999;
        int iMax_Left2 = -1, iMax_Right2 = -1, iMax_Up2 = -1, iMax_Down2 = -1;

        int iSum;
        int iGap;

        int iSum_Left, iSum_Right;
        int iSum_Top, iSum_Bottom;

        iSx = clRectRoi[i].left;
        iSy = clRectRoi[i].top;
        iEx = clRectRoi[i].right;
        iEy = clRectRoi[i].bottom;

        ::memset(aiHistY, 0, sizeof(int)*(5000));
        ::memset(aiHistX, 0, sizeof(int)*(5000));


        /* X방향 히스토그램 */
        for (x = iSx; x < iEx; x++)
        {
            iPos = iSy * nPitch + x;
            iSum = 0;

            for (y = iSy; y < iEy; y++)
            {
                //				iSum += (ucImage[iPos]*ucImage[iPos]);
                iSum += (pImage[iPos]);
                iPos += nPitch;
            }

            aiHistX[x - iSx] = iSum;
        }

        /* X방향부터 엣지 찾기 */
        for (x = iSx + 5; x < iEx - 5; x++)
        {
            iSum_Left = aiHistX[x - iSx - 4] + aiHistX[x - iSx - 3] + aiHistX[x - iSx - 2] + aiHistX[x - iSx - 1];
            iSum_Right = aiHistX[x - iSx + 4] + aiHistX[x - iSx + 3] + aiHistX[x - iSx + 2] + aiHistX[x - iSx + 1];


            iGap = iSum_Left - iSum_Right;
			
            if (iGap > 800 && iGap > iMax_Left)
            { 
                iMax_Left = iGap;
                iMinX = x; 
            }
			
            iGap = iSum_Right - iSum_Left;
			
            if (iGap>800 && iGap > iMax_Right)
            {
                iMax_Right = iGap;
                iMaxX = x;
            }
        }


        iMax_Left = 0;
        iMinX2 = 0;
        int tmpSx = iMaxX - 400;
        int tmpEx = iMinX - 30;
        if (tmpSx < (iSx + 5))
            tmpSx = (iSx + 5);
        if (tmpEx >(iEx - 5))
            tmpEx = (iSx - 5);

        for (x = tmpSx; x < iMaxX; x++)
        {
            iSum_Left = aiHistX[x - iSx - 4] + aiHistX[x - iSx - 3] + aiHistX[x - iSx - 2] + aiHistX[x - iSx - 1];
            iSum_Right = aiHistX[x - iSx + 4] + aiHistX[x - iSx + 3] + aiHistX[x - iSx + 2] + aiHistX[x - iSx + 1];

            iGap = iSum_Left - iSum_Right;

            if (iGap>800 && iGap > iMax_Left)
            {
                iMax_Left = iGap;
                iMinX2 = x;
            }
        }


        iMax_Right = 0;
        iMaxX2 = 0;

        tmpSx = iMinX + 30;
        tmpEx = iMinX + 400;
        if (tmpSx < (iSx + 5))
            tmpSx = (iSx + 5);
        if (tmpEx >(iEx - 5))
            tmpEx = (iEx - 5);


        for (x = tmpSx; x < tmpEx; x++)
        {
            iSum_Left = aiHistX[x - iSx - 4] + aiHistX[x - iSx - 3] + aiHistX[x - iSx - 2] + aiHistX[x - iSx - 1];
            iSum_Right = aiHistX[x - iSx + 4] + aiHistX[x - iSx + 3] + aiHistX[x - iSx + 2] + aiHistX[x - iSx + 1];

            iGap = iSum_Right - iSum_Left;

			//원형마크 크게 찾느거 400에서 600으로 수정해서 해결
			if (iGap > 1000 && iGap > iMax_Right)//if (iGap > 400 && iGap > iMax_Right)
            {
                iMax_Right = iGap;
                iMaxX2 = x;
            }
        }


        if (iMaxX - iMinX > 130 && iMaxX - iMinX < maxSize && iMinX > 0)
        {
            iMinX = iMinX;
            iMaxX = iMaxX;
        }
        else if (iMaxX2 - iMinX > 130 && iMaxX2 - iMinX < maxSize && iMinX > 0)
        {
            iMinX = iMinX;
            iMaxX = iMaxX2;
        }
        else if (iMaxX - iMinX2 > 130 && iMaxX - iMinX2 < maxSize && iMinX2 > 0)
        {
            iMinX = iMinX2;
            iMaxX = iMaxX;
        }

        /* Y 방향 히스토그램 */
        for (y = iSy; y < iEy; y++)
        {
            iPos = y * nPitch + iMinX;
            iSum = 0;

            for (x = iMinX; x<iMaxX; x++)
            {
                iSum += pImage[iPos++];
            }

            aiHistY[y - iSy] = iSum;
        }

        for (y = iSy + 5; y < iEy - 5; y++)
        {
            iSum_Top = aiHistY[y - iSy - 4] + aiHistY[y - iSy - 3] + aiHistY[y - iSy - 2] + aiHistY[y - iSy - 1];
            iSum_Bottom = aiHistY[y - iSy + 4] + aiHistY[y - iSy + 3] + aiHistY[y - iSy + 2] + aiHistY[y - iSy + 1];

            iGap = iSum_Top - iSum_Bottom;

            if (iGap > iMax_Up)
            {
                iMax_Up = iGap;
                iMinY = y;
            }

            iGap = iSum_Bottom - iSum_Top;

            if (iGap > iMax_Down)
            {
                iMax_Down = iGap;
                iMaxY = y;
            }
        }


        if (iMinY >= iMaxY)
        {
            int iMinY2 = -9999;
            int iMaxY2 = -9999;
            int iMax_Up2 = 0;
            int iMax_Down2 = 0;

            int tmpSy = iMinY + 5;
            int tmpEy = iEy - 5;

            for (y = tmpSy; y < tmpEy; y++)
            {
                iSum_Top = aiHistY[y - iSy - 4] + aiHistY[y - iSy - 3] + aiHistY[y - iSy - 2] + aiHistY[y - iSy - 1];
                iSum_Bottom = aiHistY[y - iSy + 4] + aiHistY[y - iSy + 3] + aiHistY[y - iSy + 2] + aiHistY[y - iSy + 1];

                iGap = iSum_Bottom - iSum_Top;

                if (iGap > iMax_Down2 && (iGap>1000))
                {
                    iMax_Down2 = iGap;
                    iMaxY2 = y;
                }
            }


            tmpSy = iSy + 5;
            tmpEy = iMaxY - 5;

            for (y = tmpSy; y < tmpEy; y++)
            {
                iSum_Top = aiHistY[y - iSy - 4] + aiHistY[y - iSy - 3] + aiHistY[y - iSy - 2] + aiHistY[y - iSy - 1];
                iSum_Bottom = aiHistY[y - iSy + 4] + aiHistY[y - iSy + 3] + aiHistY[y - iSy + 2] + aiHistY[y - iSy + 1];

                iGap = iSum_Top - iSum_Bottom;

                if (iGap > iMax_Up2 && (iGap>1000))
                {
                    iMax_Up2 = iGap;
                    iMinY2 = y;
                }
            }

            if ((iMaxY - iMinY2) > 50 && (iMaxY - iMinY2) < 250)
            {
                iMinY = iMinY2;
            }
            else if ((iMaxY2 - iMinY) > 50 && (iMaxY2 - iMinY) < 250)
            {
                iMaxY = iMaxY2;
            }
        }
        else if ((iMaxY - iMinY) > 800)
        {
            int iMaxY2 = -9999;
            int iMinY2 = -9999;
            int iMax_Up2 = 0;
            int iMax_Down2 = 0;

            int tmpSy = iMinY + 5;
            int tmpEy = iMaxY - 5;

            for (y = tmpSy; y < tmpEy; y++)
            {
                iSum_Top = aiHistY[y - iSy - 4] + aiHistY[y - iSy - 3] + aiHistY[y - iSy - 2] + aiHistY[y - iSy - 1];
                iSum_Bottom = aiHistY[y - iSy + 4] + aiHistY[y - iSy + 3] + aiHistY[y - iSy + 2] + aiHistY[y - iSy + 1];

                iGap = iSum_Top - iSum_Bottom;

                if (iGap > iMax_Up2 && (iGap > 1000))
                {
                    iMax_Up2 = iGap;
                    iMinY2 = y;
                }

                iGap = iSum_Bottom - iSum_Top;

                if (iGap > iMax_Down2 && (iGap > 1000))
                {
                    iMax_Down2 = iGap;
                    iMaxY2 = y;
                }
            }

            if ((iMinY2 > 0) && ((iMaxY - iMinY2) > 50 && (iMaxY - iMinY2) < 250))
            {
                iMinY = iMinY2;
            }
            else if ((iMaxY2 > 0) && ((iMaxY2 - iMinY) > 50 && (iMaxY2 - iMinY) < 250))
            {
                iMaxY = iMaxY2;
            }
        }


        if (iMinX > iMaxX || (iMaxX - iMinX > maxSize))
        {
			if (iMinY == iMaxY)
			{
				iMaxY += 50;
			}
            g_clVision.DrawMOverlayBox(nUnit, nUnit, iMinX, iMinY, iMaxX, iMaxY, M_COLOR_RED,1, FALSE, PS_SOLID);

            _stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 좌우 인식 위치가 비정상 입니다. (좌 %d, 우 %d)"), i + 1, iMinX, iMaxX);
            AddLog(szLog, 0, nUnit);
            return false;
        }


        if (iMinY > iMaxY || (iMaxY - iMinY > maxSize))
        {
            g_clVision.DrawMOverlayBox(nUnit, nUnit, iMinX, iMinY, iMaxX, iMaxY, M_COLOR_RED, 2, FALSE, PS_SOLID);

            _stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 상하 인식 위치가 비정상 입니다. (상 %d, 하 %d)"), i + 1, iMinY, iMaxY);
            AddLog(szLog, 0, nUnit);
            return false;
        }


        if (iMaxX < 0 || iMaxY < 0 || iMaxX > nSizeX || iMaxY > nSizeY ||
            iMinX < 0 || iMinY < 0 || iMinX > nSizeX || iMinY > nSizeY)
        {
            _stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] Max, Min 위치를 찾지 못했습니다."), i + 1);
            AddLog(szLog, 0, nUnit);
            return false;
        }
#ifdef ON_LINE_MIL
		g_clVision.DrawMOverlayBox(nUnit, nUnit, clRectRoi[i], M_COLOR_BLUE, 1, FALSE, PS_DOT);
		//g_clVision.DrawMOverlayBox(nUnit, g_clModelData[nUnit].m_clSfrInfo.m_clRectFov[i], M_COLOR_GREEN, 1, FALSE, PS_DOT);
		g_clVision.DrawMOverlayBox(nUnit, nUnit, iMinX, iMinY, iMaxX, iMaxY, M_COLOR_YELLOW, 1, FALSE, PS_SOLID);
#endif
        
         
        g_clTaskWork[nUnit].m_clPtFov[i].x = (iMaxX + iMinX) / 2;
        g_clTaskWork[nUnit].m_clPtFov[i].y = (iMaxY + iMinY) / 2;
		g_clTaskWork[nUnit].m_FindFovRect[i].left = iMinX;
		g_clTaskWork[nUnit].m_FindFovRect[i].right = iMaxX;
		g_clTaskWork[nUnit].m_FindFovRect[i].top = iMinY;
		g_clTaskWork[nUnit].m_FindFovRect[i].bottom = iMaxY;


        g_clVision.DrawMOverlayCross(nUnit, nUnit, g_clTaskWork[nUnit].m_clPtFov[i], 200, M_COLOR_GRAY, 1, FALSE);// TRUE); 

    }
    return true;
}


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool g_MilFindCirclePos(int m_nUnit, BYTE* ChartRawImage, CRect* clRectRoi, bool bAutoMode)		//int nPitch, int nSizeX, int nSizeY,
{
	TCHAR szLog[SIZE_OF_1K];
	int i = 0;
	int j = 0;


	int nImageWidth = g_clModelData[m_nUnit].m_nWidth;			// : Image width;
	int nImageHeight = g_clModelData[m_nUnit].m_nHeight;		// : Image height


	RECT rtFiducialMarkROI;// : Fiducial Mark를 찾고자 하는 ROI

	cv::Rect rtROIRect;

	BYTE* m_pBMPTempBuffer;
	m_pBMPTempBuffer = new BYTE[g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameBMPSize()];
	memset(m_pBMPTempBuffer, 0, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameBMPSize());
	ACMISSoftISP::xMakeBMP(ChartRawImage, (byte*)m_pBMPTempBuffer, g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight, g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n);

	Mat OrgImage(Size(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight), CV_8UC3);

	std::memcpy(OrgImage.data, (char*)m_pBMPTempBuffer, g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight * 3);

#ifdef _DEBUG
	//namedWindow("OrgImage", WINDOW_NORMAL);// WINDOW_AUTOSIZE);
	//imshow("OrgImage", OrgImage);

	//waitKey(0);
#endif
	TCHAR* pszCirRow[] = {
		_T("[0] Circle LT"), _T("[1] Circle RT"), _T("[2] Circle BL"), _T("[3] Circle BR")
	};

	rtROIRect.x = clRectRoi[0].left;
	rtROIRect.y = clRectRoi[0].top;

	rtROIRect.width = clRectRoi[0].right - clRectRoi[0].left + 1;
	rtROIRect.height = clRectRoi[0].bottom - clRectRoi[0].top + 1;


	_stprintf_s(szLog, SIZE_OF_1K, _T("Circle Threshold: %0.1lf "), g_clModelData[m_nUnit].m_dCircleThresh);
	AddLog(szLog, 0, m_nUnit);


	for (i = 0; i < 4; i++)
	{
		bool bCircleFinded = false;
		Mat roiimg = OrgImage(cvRect(clRectRoi[i].left, clRectRoi[i].top, clRectRoi[i].Width(), clRectRoi[i].Height()));
		Mat grayImg;

		cv::cvtColor(roiimg, grayImg, cv::COLOR_BGR2GRAY);
		
		//cv::Mat original_im(nImageHeight, nImageWidth, CV_8UC1, (void*)ChartRawImage);
		//cv::Mat crop_im(original_im, rtROIRect);
#ifdef _DEBUG
		if (false)
		{
			namedWindow("grayImg", WINDOW_NORMAL);// WINDOW_AUTOSIZE);
			imshow("grayImg", grayImg);

			waitKey(0);
		}
#endif
		cv::Mat threshold_im; 
		double tresh = g_clModelData[m_nUnit].m_dCircleThresh;// 90.0;		//이미지 밝기보다 밝으니 원이 안잡힌다.  어둡게 설정해

		cv::threshold(grayImg, threshold_im, tresh, 255.0, CV_THRESH_BINARY); // 50.0 : Image를 Thresholding 하기 위한 Threshold값으로 Image의 밝기에 따라 달라질 수 있음
		cv::Mat canny_im;
		cv::Canny(threshold_im, canny_im, 0.0, 255.0, 3);     // 그레이 이미지를 캐니로 변환


#ifdef _DEBUG
		if (bAutoMode == false)
		{
			namedWindow("canny_im", WINDOW_NORMAL);// WINDOW_AUTOSIZE);
			imshow("canny_im", canny_im);

			waitKey(0);
		}
#endif
		vector<vector<cv::Point>> contours;
		vector<cv::Vec4i> hierarchy;

		cv::findContours(canny_im, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		//CV_RETR_EXTERNAL
		//CV_RETR_CCOMP

		if ((int)contours.size() == 0) 
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("%s FIND FAIL!"), pszCirRow[i]);
			AddLog(szLog, 0, m_nUnit);
			return false;
		}

		//_stprintf_s(szLog, SIZE_OF_1K, _T("CIRCLE COUNT = %d"), (int)contours.size());
		//AddLog(szLog, 0, m_nUnit);
		for (j = 0; j < (int)contours.size(); j++)
		{
			double area = cv::contourArea(contours[j]);
			double arcCount = cv::arcLength(contours[j], false);
			cv::Rect rect = cv::boundingRect(contours[j]);


			std::vector<cv::Point> approx;
			cv::approxPolyDP(contours[j], approx, cv::arcLength(contours[j], true) * 0.02, true);


			cv::Point2f center;
			float radius = 0.0f;
			cv::minEnclosingCircle(contours[j], center, radius);
			double circleArea = CV_PI * radius * radius;
			if (arcCount == 0.0)
			{
				continue;
			}

			double circularity = (4.0 * CV_PI * area) / (arcCount * arcCount);
			double temp = 1 - (area / circleArea);
			
			if (circularity > 0.7 && radius > 10.0) // 0.7 : (타)원일 경우 일반적으로 circularity가 0.7보다 큼
			{
				bCircleFinded = true;
				double ocx = (double)center.x + (double)clRectRoi[i].left; // Fiducial Mark 중심 x 좌표
				double ocy = (double)center.y + (double)clRectRoi[i].top; // Fiducial Mark 중심 x 좌표

				//_stprintf_s(szLog, SIZE_OF_1K, _T("Circle #%d [%lf, %f, %f, %lf, %lf "), i + 1, circularity, radius, arcCount, circleArea, temp);
				//AddLog(szLog, 0, m_nUnit);
				//_stprintf_s(szLog, SIZE_OF_1K, _T("OC X = %lf"), ocx);
				//AddLog(szLog, 0, m_nUnit);
				//_stprintf_s(szLog, SIZE_OF_1K, _T("OC Y = %lf"), ocy);
				//AddLog(szLog, 0, m_nUnit);


				g_clTaskWork[m_nUnit].m_clPtCircle[i].x = ocx;				// circles[0][0] + clRectRoi[i].left;
				g_clTaskWork[m_nUnit].m_clPtCircle[i].y = ocy;				// circles[0][1] + clRectRoi[i].top;

				g_clTaskWork[m_nUnit].m_clPtRotationCircle[i].x = ocx;		//circles[0][0] + clRectRoi[i].left;
				g_clTaskWork[m_nUnit].m_clPtRotationCircle[i].y = ocy;		//circles[0][1] + clRectRoi[i].top;




				g_clTaskWork[m_nUnit].m_FindCircleRect[i].left = g_clTaskWork[m_nUnit].m_clPtCircle[i].x - radius;
				g_clTaskWork[m_nUnit].m_FindCircleRect[i].right = g_clTaskWork[m_nUnit].m_clPtCircle[i].x + radius;
				g_clTaskWork[m_nUnit].m_FindCircleRect[i].top = g_clTaskWork[m_nUnit].m_clPtCircle[i].y - radius;
				g_clTaskWork[m_nUnit].m_FindCircleRect[i].bottom = g_clTaskWork[m_nUnit].m_clPtCircle[i].y + radius;

				g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, g_clTaskWork[m_nUnit].m_FindCircleRect[i].left, g_clTaskWork[m_nUnit].m_FindCircleRect[i].top, g_clTaskWork[m_nUnit].m_FindCircleRect[i].right, g_clTaskWork[m_nUnit].m_FindCircleRect[i].bottom, M_COLOR_GRAY, 1, FALSE, PS_SOLID);

				_stprintf_s(szLog, SIZE_OF_1K, _T("%s x:%lf , y:%lf"), pszCirRow[i], g_clTaskWork[m_nUnit].m_clPtRotationCircle[i].x, g_clTaskWork[m_nUnit].m_clPtRotationCircle[i].y);
				AddLog(szLog, 0, m_nUnit);
				g_clVision.DrawMOverlayCross(m_nUnit, m_nUnit, g_clTaskWork[m_nUnit].m_clPtCircle[i], 200, M_COLOR_LIGHT_GRAY, 1, FALSE);// TRUE);
				break;
			}
		}

		if (bCircleFinded == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("%s FIND FAIL"), pszCirRow[i]);
			AddLog(szLog, 0, m_nUnit);
			return false;
		}
	}
	return true;
}


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool g_OpencvFindCirclePos(int m_nUnit, BYTE* ChartRawImage, CRect* clRectRoi , bool bAutoMode)		//int nPitch, int nSizeX, int nSizeY,
{

	TCHAR szLog[SIZE_OF_1K];
	TCHAR szFilePath[SIZE_OF_1K];
	//int nPitch = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_PITCH, M_NULL);
	//int nSizeX = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_SIZE_X, M_NULL);
	//int nSizeY = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_SIZE_Y, M_NULL);
	//int iSx, iSy, iEx, iEy;
	//int x, y, iPos;
	//int iMaxX = -1, iMinX = 9999;
	//int iMaxY = -1, iMinY = 9999;

	//opencv 로 원형마크 찾기

	BYTE* m_pBMPTempBuffer;
	m_pBMPTempBuffer = new BYTE[g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameBMPSize()];
	memset(m_pBMPTempBuffer, 0, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameBMPSize());

	ACMISSoftISP::xMakeBMP(ChartRawImage, (byte*)m_pBMPTempBuffer, g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight, g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n);

	Mat OrgImage(Size(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight), CV_8UC3);
	std::memcpy(OrgImage.data, (char*)m_pBMPTempBuffer, g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight * 3);


	TCHAR* pszCirRow[] = {
		_T("[0] Circle LT"), _T("[1] Circle RT"), _T("[2] Circle BL"), _T("[3] Circle BR")
	};
	int arrParam[] = { 120,80,170 };
	bool bCircleRtn = true;
	for (int i = 0; i < 4; i++)
	{
		if (clRectRoi[i].left < 0 || clRectRoi[i].top < 0 || clRectRoi[i].right > g_clModelData[m_nUnit].m_nWidth || clRectRoi[i].bottom > g_clModelData[m_nUnit].m_nHeight)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 원형 마크 검색 영역이 잘못되었습니다. ( L:%d, T:%d, R:%d, B:%d )"), i + 1, clRectRoi[i].left, clRectRoi[i].top, clRectRoi[i].right, clRectRoi[i].bottom);
			AddLog(szLog, 0, m_nUnit);
			return false;
		}
		Mat roiimg = OrgImage(cvRect(clRectRoi[i].left, clRectRoi[i].top, clRectRoi[i].Width(), clRectRoi[i].Height()));
		Mat grayImg;
		cv::cvtColor(roiimg, grayImg, cv::COLOR_BGR2GRAY);

		//
		//
		int mdp = 1;						//dp=1이면 입력 이미지와 동일한 해상도를 사용
		int mMinDist = grayImg.rows / 2;		// / 8;//검출된 원의 중심들 사이의 최소 거리입니다
		int mParam1 = 120;			//캐니 에지 탐지기에 전달되는 상위 임계값입니다. 
		int mParam2 = 10;					//중심 검출을 위한 누산기의 임계값입니다. 이 값이 작을수록 더 많은 원이 검출되며, 노이즈나 잘못된 원도 포함될 수 있습니다.
		int mMinRadius = 10;					//검출할 원의 최소 반지름입니다.  
		int mMaxRadius = 75;					//검출할 원의 최대 반지름입니다. 

												//원찾기
		std::vector<cv::Vec3f> circles;
		

		bCircleRtn = false;
		for (int k = 0; k < 3; k++)
		{
			mParam1 = arrParam[k];
			cv::HoughCircles(grayImg, circles, cv::HOUGH_GRADIENT, mdp, mMinDist, mParam1, mParam2, mMinRadius, mMaxRadius);
			if (circles.empty() == false)
			{
				bCircleRtn = true;
				break;
			}

		}
		if (bCircleRtn == false)
		{
			return false;
		}

		// 각 원의 중심과 반지름
		float x = circles[0][0];
		float y = circles[0][1];

		cv::Point center(cvRound(circles[0][0]), cvRound(circles[0][1]));
		int radius = cvRound(circles[0][2]);

		g_clTaskWork[m_nUnit].m_clPtCircle[i].x = circles[0][0] + clRectRoi[i].left;
		g_clTaskWork[m_nUnit].m_clPtCircle[i].y = circles[0][1] + clRectRoi[i].top;

		g_clTaskWork[m_nUnit].m_clPtRotationCircle[i].x = circles[0][0] + clRectRoi[i].left;
		g_clTaskWork[m_nUnit].m_clPtRotationCircle[i].y = circles[0][1] + clRectRoi[i].top;




		g_clTaskWork[m_nUnit].m_FindCircleRect[i].left = g_clTaskWork[m_nUnit].m_clPtCircle[i].x - radius;
		g_clTaskWork[m_nUnit].m_FindCircleRect[i].right = g_clTaskWork[m_nUnit].m_clPtCircle[i].x + radius;
		g_clTaskWork[m_nUnit].m_FindCircleRect[i].top = g_clTaskWork[m_nUnit].m_clPtCircle[i].y - radius;
		g_clTaskWork[m_nUnit].m_FindCircleRect[i].bottom = g_clTaskWork[m_nUnit].m_clPtCircle[i].y + radius;

		g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, g_clTaskWork[m_nUnit].m_FindCircleRect[i].left, g_clTaskWork[m_nUnit].m_FindCircleRect[i].top, g_clTaskWork[m_nUnit].m_FindCircleRect[i].right, g_clTaskWork[m_nUnit].m_FindCircleRect[i].bottom, M_COLOR_GRAY, 1, FALSE, PS_SOLID);

		if (bAutoMode == false)
		{
			//_stprintf_s(szLog, SIZE_OF_1K, _T("%s x:%d , y:%d"), pszCirRow[i], g_clTaskWork[m_nUnit].m_clPtCircle[i].x, g_clTaskWork[m_nUnit].m_clPtCircle[i].y);
			_stprintf_s(szLog, SIZE_OF_1K, _T("%s x:%.1lf , y:%.1lf"), pszCirRow[i], g_clTaskWork[m_nUnit].m_clPtRotationCircle[i].x, g_clTaskWork[m_nUnit].m_clPtRotationCircle[i].y);
			AddLog(szLog, 0, m_nUnit);
		}
		g_clVision.DrawMOverlayCross(m_nUnit, m_nUnit, g_clTaskWork[m_nUnit].m_clPtCircle[i], 200, M_COLOR_GRAY, 1, FALSE);// TRUE);

#ifdef _DEBUG
		if (false)//bAutoMode == false)
		{
			Mat img_corners;		//코너 찾기
			cvtColor(grayImg, img_corners, COLOR_GRAY2BGR);

			cv::Rect rect(circles[0][0] - radius, circles[0][1] - radius, radius * 2, radius * 2); // (x, y, width, height)
			circle(img_corners, center, 3, Scalar(0, 255, 0), -1, 8, 0);
			rectangle(img_corners, rect, Scalar(0, 255, 0), 1);

			_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\circle_%d.jpg"), BASE_LOG_PATH, i + 1);
			imwrite(szFilePath, img_corners);

			namedWindow("Circle Center", WINDOW_NORMAL);// WINDOW_AUTOSIZE);
			imshow("Circle Center", img_corners);

			waitKey(0);
		}

		//circles.clear();
#endif
	}

	if (m_pBMPTempBuffer)
	{
		delete m_pBMPTempBuffer;
	}
	m_pBMPTempBuffer = NULL;
	
	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool g_FindCirclePos(int nUnit, unsigned char* pImage,  CRect* clRectRoi)		//int nPitch, int nSizeX, int nSizeY,
{	
	int maxSize = 200;
	int nPitch = (int)MbufInquire(g_clVision.m_MilCcdProcChild[nUnit][1], M_PITCH, M_NULL);
	int nSizeX = (int)MbufInquire(g_clVision.m_MilCcdProcChild[nUnit][1], M_SIZE_X, M_NULL);
	int nSizeY = (int)MbufInquire(g_clVision.m_MilCcdProcChild[nUnit][1], M_SIZE_Y, M_NULL);

	TCHAR szLog[SIZE_OF_1K];

	if (pImage == NULL)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("영상 버퍼가 잘못되었습니다."));
		AddLog(szLog, 0, nUnit);
		return false;
	}

	if (nSizeX <= 0 || nSizeY <= 0)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("영상 사이즈가 잘못되었습니다. ( X : %d Y : %d )"), nSizeX, nSizeY);
		AddLog(szLog, 0, nUnit);

		return false;
	}

	int aiHistX[5000];
	int aiHistY[5000];

	int xMaxLimit = 600;
	int Gap = 400;
	int minTemp = 10;
	for (int i = 0; i<4; i++)
	{
		if (clRectRoi[i].left < 0 || clRectRoi[i].top < 0 || clRectRoi[i].right > nSizeX || clRectRoi[i].bottom > nSizeY)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 원형 마크 검색 영역이 잘못되었습니다. ( L %d,  T %d,  R %d,  B %d )"), i + 1, clRectRoi[i].left, clRectRoi[i].top, clRectRoi[i].right, clRectRoi[i].bottom);
			AddLog(szLog, 0, nUnit);

			return false;
		}

		int iSx, iSy, iEx, iEy;
		int x, y, iPos;
		int iMaxX = -1, iMinX = 9999;
		int iMaxY = -1, iMinY = 9999;
		int iMax_Left = -1, iMax_Right = -1, iMax_Up = -1, iMax_Down = -1;

		int iMaxX2 = -1, iMinX2 = 9999;
		int iMaxY2 = -1, iMinY2 = 9999;
		int iMax_Left2 = -1, iMax_Right2 = -1, iMax_Up2 = -1, iMax_Down2 = -1;

		int iSum;
		int iGap;

		int iSum_Left, iSum_Right;
		int iSum_Top, iSum_Bottom;

		iSx = clRectRoi[i].left;
		iSy = clRectRoi[i].top;
		iEx = clRectRoi[i].right;
		iEy = clRectRoi[i].bottom;

		::memset(aiHistY, 0, sizeof(int)*(5000));
		::memset(aiHistX, 0, sizeof(int)*(5000));


		/* X방향 히스토그램 */
		for (x = iSx; x < iEx; x++)
		{
			iPos = iSy * nPitch + x;
			iSum = 0;

			for (y = iSy; y < iEy; y++)
			{
				//				iSum += (ucImage[iPos]*ucImage[iPos]);
				iSum += (pImage[iPos]);
				iPos += nPitch;
			}

			aiHistX[x - iSx] = iSum;
		}

		/* X방향부터 엣지 찾기 */
		for (x = iSx + 5; x < iEx - 5; x++)
		{
			iSum_Left = aiHistX[x - iSx - 4] + aiHistX[x - iSx - 3] + aiHistX[x - iSx - 2] + aiHistX[x - iSx - 1];
			iSum_Right = aiHistX[x - iSx + 4] + aiHistX[x - iSx + 3] + aiHistX[x - iSx + 2] + aiHistX[x - iSx + 1];

			iGap = iSum_Left - iSum_Right;

			if (iGap > Gap && iGap > iMax_Left)
			{
				iMax_Left = iGap;
				iMinX = x;
			}

			iGap = iSum_Right - iSum_Left;

			if (iGap>Gap && iGap > iMax_Right)
			{
				iMax_Right = iGap;
				iMaxX = x;
			}
		}


		iMax_Left = 0;
		iMinX2 = 0;
		int tmpSx = iMaxX - xMaxLimit;
		int tmpEx = iMinX - minTemp;
		if (tmpSx < (iSx + 5))
			tmpSx = (iSx + 5);
		if (tmpEx >(iEx - 5))
			tmpEx = (iSx - 5);

		for (x = tmpSx; x < iMaxX; x++)
		{
			iSum_Left = aiHistX[x - iSx - 4] + aiHistX[x - iSx - 3] + aiHistX[x - iSx - 2] + aiHistX[x - iSx - 1];
			iSum_Right = aiHistX[x - iSx + 4] + aiHistX[x - iSx + 3] + aiHistX[x - iSx + 2] + aiHistX[x - iSx + 1];

			iGap = iSum_Left - iSum_Right;

			if (iGap>xMaxLimit && iGap > iMax_Left)
			{
				iMax_Left = iGap;
				iMinX2 = x;
			}
		}


		iMax_Right = 0;
		iMaxX2 = 0;

		tmpSx = iMinX + minTemp;
		tmpEx = iMinX + xMaxLimit;
		if (tmpSx < (iSx + 5))
			tmpSx = (iSx + 5);
		if (tmpEx >(iEx - 5))
			tmpEx = (iEx - 5);


		for (x = tmpSx; x < tmpEx; x++)
		{
			iSum_Left = aiHistX[x - iSx - 4] + aiHistX[x - iSx - 3] + aiHistX[x - iSx - 2] + aiHistX[x - iSx - 1];
			iSum_Right = aiHistX[x - iSx + 4] + aiHistX[x - iSx + 3] + aiHistX[x - iSx + 2] + aiHistX[x - iSx + 1];

			iGap = iSum_Right - iSum_Left;

			if (iGap > xMaxLimit && iGap > iMax_Right)
			{
				iMax_Right = iGap;
				iMaxX2 = x;
			}
		}


		if (iMaxX - iMinX > minTemp && iMaxX - iMinX < maxSize && iMinX > 0)
		{
			iMinX = iMinX;
			iMaxX = iMaxX;
		}
		else if (iMaxX2 - iMinX > minTemp && iMaxX2 - iMinX < maxSize && iMinX > 0)
		{
			iMinX = iMinX;
			iMaxX = iMaxX2;
		}
		else if (iMaxX - iMinX2 > minTemp && iMaxX - iMinX2 < maxSize && iMinX2 > 0)
		{
			iMinX = iMinX2;
			iMaxX = iMaxX;
		}

		/* Y 방향 히스토그램 */
		for (y = iSy; y < iEy; y++)
		{
			iPos = y * nPitch + iMinX;
			iSum = 0;

			for (x = iMinX; x<iMaxX; x++)
			{
				iSum += pImage[iPos++];
			}

			aiHistY[y - iSy] = iSum;
		}

		for (y = iSy + 5; y < iEy - 5; y++)
		{
			iSum_Top = aiHistY[y - iSy - 4] + aiHistY[y - iSy - 3] + aiHistY[y - iSy - 2] + aiHistY[y - iSy - 1];
			iSum_Bottom = aiHistY[y - iSy + 4] + aiHistY[y - iSy + 3] + aiHistY[y - iSy + 2] + aiHistY[y - iSy + 1];

			iGap = iSum_Top - iSum_Bottom;

			if (iGap > iMax_Up)
			{
				iMax_Up = iGap;
				iMinY = y;
			}

			iGap = iSum_Bottom - iSum_Top;

			if (iGap > iMax_Down)
			{
				iMax_Down = iGap;
				iMaxY = y;
			}
		}


		if (iMinY >= iMaxY)
		{
			int iMinY2 = -9999;
			int iMaxY2 = -9999;
			int iMax_Up2 = 0;
			int iMax_Down2 = 0;

			int tmpSy = iMinY + 5;
			int tmpEy = iEy - 5;

			for (y = tmpSy; y < tmpEy; y++)
			{
				iSum_Top = aiHistY[y - iSy - 4] + aiHistY[y - iSy - 3] + aiHistY[y - iSy - 2] + aiHistY[y - iSy - 1];
				iSum_Bottom = aiHistY[y - iSy + 4] + aiHistY[y - iSy + 3] + aiHistY[y - iSy + 2] + aiHistY[y - iSy + 1];

				iGap = iSum_Bottom - iSum_Top;

				if (iGap > iMax_Down2 && (iGap>1000))
				{
					iMax_Down2 = iGap;
					iMaxY2 = y;
				}
			}


			tmpSy = iSy + 5;
			tmpEy = iMaxY - 5;

			for (y = tmpSy; y < tmpEy; y++)
			{
				iSum_Top = aiHistY[y - iSy - 4] + aiHistY[y - iSy - 3] + aiHistY[y - iSy - 2] + aiHistY[y - iSy - 1];
				iSum_Bottom = aiHistY[y - iSy + 4] + aiHistY[y - iSy + 3] + aiHistY[y - iSy + 2] + aiHistY[y - iSy + 1];

				iGap = iSum_Top - iSum_Bottom;

				if (iGap > iMax_Up2 && (iGap>1000))
				{
					iMax_Up2 = iGap;
					iMinY2 = y;
				}
			}

			if ((iMaxY - iMinY2) > 50 && (iMaxY - iMinY2) < 250)
			{
				iMinY = iMinY2;
			}
			else if ((iMaxY2 - iMinY) > 50 && (iMaxY2 - iMinY) < 250)
			{
				iMaxY = iMaxY2;
			}
		}
		else if ((iMaxY - iMinY) > xMaxLimit)
		{
			int iMaxY2 = -9999;
			int iMinY2 = -9999;
			int iMax_Up2 = 0;
			int iMax_Down2 = 0;

			int tmpSy = iMinY + 5;
			int tmpEy = iMaxY - 5;

			for (y = tmpSy; y < tmpEy; y++)
			{
				iSum_Top = aiHistY[y - iSy - 4] + aiHistY[y - iSy - 3] + aiHistY[y - iSy - 2] + aiHistY[y - iSy - 1];
				iSum_Bottom = aiHistY[y - iSy + 4] + aiHistY[y - iSy + 3] + aiHistY[y - iSy + 2] + aiHistY[y - iSy + 1];

				iGap = iSum_Top - iSum_Bottom;

				if (iGap > iMax_Up2 && (iGap > 1000))
				{
					iMax_Up2 = iGap;
					iMinY2 = y;
				}

				iGap = iSum_Bottom - iSum_Top;

				if (iGap > iMax_Down2 && (iGap > 1000))
				{
					iMax_Down2 = iGap;
					iMaxY2 = y;
				}
			}

			if ((iMinY2 > 0) && ((iMaxY - iMinY2) > 50 && (iMaxY - iMinY2) < 250))
			{
				iMinY = iMinY2;
			}
			else if ((iMaxY2 > 0) && ((iMaxY2 - iMinY) > 50 && (iMaxY2 - iMinY) < 250))
			{
				iMaxY = iMaxY2;
			}
		}


		if (iMinX > iMaxX || (iMaxX - iMinX > maxSize))
		{
			g_clVision.DrawMOverlayBox(nUnit, nUnit, iMinX, iMinY, iMaxX, iMaxY, M_COLOR_RED, 2, FALSE, PS_SOLID);

			_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 좌우 인식 위치가 비정상 입니다. (좌 %d, 우 %d)"), i + 1, iMinX, iMaxX);
			AddLog(szLog, 0, nUnit);
			return false;
		}


		if (iMinY > iMaxY || (iMaxY - iMinY > maxSize))
		{
			g_clVision.DrawMOverlayBox(nUnit, nUnit, iMinX, iMinY, iMaxX, iMaxY, M_COLOR_RED, 2, FALSE, PS_SOLID);

			_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 상하 인식 위치가 비정상 입니다. (상 %d, 하 %d)"), i + 1, iMinY, iMaxY);
			AddLog(szLog, 0, nUnit);
			return false;
		}


		if (iMaxX < 0 || iMaxY < 0 || iMaxX > nSizeX || iMaxY > nSizeY ||
			iMinX < 0 || iMinY < 0 || iMinX > nSizeX || iMinY > nSizeY)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] Max, Min 위치를 찾지 못했습니다."), i + 1);
			AddLog(szLog, 0, nUnit);
			return false;
		}

		g_clVision.DrawMOverlayBox(nUnit, nUnit, iMinX, iMinY, iMaxX, iMaxY, M_COLOR_GRAY, 1, FALSE, PS_SOLID);

		g_clTaskWork[nUnit].m_clPtCircle[i].x = (iMaxX + iMinX) / 2;
		g_clTaskWork[nUnit].m_clPtCircle[i].y = (iMaxY + iMinY) / 2;

		g_clTaskWork[nUnit].m_FindCircleRect[i].left = iMinX;
		g_clTaskWork[nUnit].m_FindCircleRect[i].right = iMaxX;
		g_clTaskWork[nUnit].m_FindCircleRect[i].top = iMinY;
		g_clTaskWork[nUnit].m_FindCircleRect[i].bottom = iMaxY;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[Circle #%d] x:%d , y:%d."), i + 1, g_clTaskWork[nUnit].m_clPtCircle[i].x, g_clTaskWork[nUnit].m_clPtCircle[i].y);
		AddLog(szLog, 0, nUnit);
        g_clVision.DrawMOverlayCross(nUnit, nUnit, g_clTaskWork[nUnit].m_clPtCircle[i], 200, M_COLOR_GRAY, 1, FALSE);// TRUE);

	} 
	return true;
} 


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool g_FindRectPos(int nUnit, unsigned char* pImage, int nPitch, int nSizeX, int nSizeY, int nIndex, CRect& clRect)
{
	TCHAR szLog[SIZE_OF_1K];
	int nOffsetX, nOffsetY;

	nOffsetX = (int)((clRect.right - clRect.left) / 3);
	nOffsetY = (clRect.bottom - clRect.top) / 2;

	int nMinMaxGap = 1000;

	if (pImage == NULL)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("영상 버퍼가 잘못되었습니다."));
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if (nSizeX <= 0 || nSizeY <= 0)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("영상 사이즈가 잘못되었습니다. ( X : %d Y : %d )"), nSizeX, nSizeY);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	int nHistX[5000];
	int nHistY[5000];

	if ((clRect.left < 0) || (clRect.top < 0) || (clRect.right > nSizeX) || (clRect.bottom > nSizeY))
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("원형 마크 검색 영역이 잘못 되었습니다. ( L : %d T : %d R : %d B : %d )"), clRect.left, clRect.top, clRect.right, clRect.bottom);
		AddLog(szLog, 1, nUnit);

		return false;
	}


	int nSx, nSy, nEx, nEy, nCx, nCy;
	int x, y, nPos, nSum, nAvgX, nAvgY;

	memset(nHistY, 0, sizeof(int)*(5000));
	memset(nHistX, 0, sizeof(int)*(5000));


	nSx = clRect.left + nOffsetX;
	nEx = clRect.right - nOffsetX;
	nSy = clRect.top - nOffsetY;
	nEy = clRect.bottom + nOffsetY;
	nCy = (nSy + nEy) / 2;

	if (nSx < 0)				nSx = 0;
	if (nSy < 0)				nSy = 0;
	if (nEx >= nSizeX)			nEx = nSizeX - 1;
	if (nEy >= nSizeY)			nEy = nSizeY - 1;

	nAvgY = 0;
	for (y = nSy; y < nEy; y++)
	{
		nSum = 0;
		nPos = y * nPitch + nSx;

		for (x = nSx; x < nEx; x++)
		{
			nSum += pImage[nPos];
			nPos++;
		}

		nHistY[y] = nSum;
		nAvgY += nSum;
	}

	nAvgY = (int)(nAvgY / (nEy - nSy) * 0.9);

	int nMaxX = -1, nMinX = 9999;
	int nMaxY = -1, nMinY = 9999;
	int nMaxLeft = -1, nMaxRight = -1, nMaxTop = -1, nMaxBottom = -1;
	int nSumTop, nSumBottom;

	for (y = nCy; y > nSy + 8; y--)
	{
		if ((nHistY[y - 1] > nAvgY) && (nHistY[y - 3] > nAvgY) && (nHistY[y - 5] > nAvgY) && (nHistY[y - 7] > nAvgY))
		{
			nSumTop = nHistY[y - 7] + nHistY[y - 5] + nHistY[y - 3] + nHistY[y - 1];
			nSumBottom = nHistY[y + 7] + nHistY[y + 5] + nHistY[y + 3] + nHistY[y + 1];

			nMaxTop = nSumTop - nSumBottom;
			nMinY = y;

			break;
		}
	}

	if (y == nSy + 8)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 사각형[#%d] 상부 인식 실패."), nIndex);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	for (y = nCy; y < nEy - 8; y++)
	{
		if ((nHistY[y + 1] > nAvgY) && (nHistY[y + 3] > nAvgY) && (nHistY[y + 5] > nAvgY) && (nHistY[y + 7] > nAvgY))
		{
			nSumTop = nHistY[y - 7] + nHistY[y - 5] + nHistY[y - 3] + nHistY[y - 1];
			nSumBottom = nHistY[y + 7] + nHistY[y + 5] + nHistY[y + 3] + nHistY[y + 1];

			nMaxBottom = nSumBottom - nSumTop;
			nMaxY = y;

			break;
		}
	}

	if (y == nEy - 8)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 사각형[#%d] 하부 인식 실패."), nIndex);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if (nMaxTop < nMinMaxGap)
	{
		g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 상부 경계선이 불분명합니다. (%d)"), nIndex, nMaxTop);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if (nMaxBottom < nMinMaxGap)
	{
		g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 하부 경계선이 불분명합니다. (%d)"), nIndex, nMaxBottom);
		AddLog(szLog, 0, nUnit);

		return false;
	}

	if ((nMinY >= nMaxY) || (nMinY < 1))
	{
		g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 상하 경계선 인식 결과가 비정상 입니다. [상:%d, 하:%d]"), nIndex, nMinY, nMaxY);
		AddLog(szLog, 0, nUnit);

		return false;
	}


	nOffsetX = (clRect.right - clRect.left) / 2;
	nOffsetY = (int)((clRect.bottom - clRect.top) / 3);

	nSx = clRect.left - nOffsetX;
	nEx = clRect.right + nOffsetX;
	nSy = nMinY + nOffsetY;
	nEy = nMaxY - nOffsetY;
	nCx = (nSx + nEx) / 2;

	if (nSx < 0)			nSx = 0;
	if (nSy < 0)			nSy = 0;
	if (nEx >= nSizeX)		nEx = nSizeX - 1;
	if (nEy >= nSizeY)		nEy = nSizeY - 1;

	/* X방향 히스토그램 */
	nAvgX = 0;
	for (x = nSx; x < nEx; x++)
	{
		nSum = 0;
		nPos = nSy * nPitch + x;

		for (y = nSy; y < nEy; y++)
		{
			nSum += pImage[nPos];
			nPos += nPitch;
		}

		nHistX[x] = nSum;
		nAvgX += nSum;
	}

	nAvgX = (int)(nAvgX / ((nEx - nSx) * 0.9));

	int nSumLeft, nSumRight;

	for (x = nCx; x > nSx + 5; x--)
	{
		if ((nHistX[x - 4] > nAvgX) && (nHistX[x - 3] > nAvgX) && (nHistX[x - 2] > nAvgX) && (nHistX[x - 1] > nAvgX))
		{
			nSumLeft = nHistX[x - 4] + nHistX[x - 3] + nHistX[x - 2] + nHistX[x - 1];
			nSumRight = nHistX[x + 4] + nHistX[x + 3] + nHistX[x + 2] + nHistX[x + 1];

			nMaxLeft = nSumLeft - nSumRight;
			nMinX = x;

			break;
		}
	}

	if ((x == nSx + 5) && (nIndex != 15) && (nIndex != 18))
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 사각형[#%d] 좌측 인식 실패."), nIndex);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	for (x = nCx; x < nEx - 5; x++)
	{
		if ((nHistX[x + 1] > nAvgX) && (nHistX[x + 2] > nAvgX) && (nHistX[x + 3] > nAvgX) && (nHistX[x + 4] > nAvgX))
		{
			nSumLeft = nHistX[x - 4] + nHistX[x - 3] + nHistX[x - 2] + nHistX[x - 1];
			nSumRight = nHistX[x + 4] + nHistX[x + 3] + nHistX[x + 2] + nHistX[x + 1];

			nMaxRight = nSumRight - nSumLeft;
			nMaxX = x;

			break;
		}
	}

	if ((x == nEx - 5) && (nIndex != 16) && (nIndex != 17))
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 사각형[#%d] 우측 인식 실패."), nIndex);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if ((nIndex == 15) || (nIndex == 18))
	{
		if (nMaxRight > nMinMaxGap)
			nMinX = nMaxX - g_clModelData[nUnit].m_clSfrInfo.m_nSizeX[nIndex];
		else
			nMinX = clRect.left;
	}
	else if (nMaxLeft < nMinMaxGap)
	{
		g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 좌측 경계선이 불분명합니다. (%d)"), nIndex, nMaxLeft);
		AddLog(szLog, 1, nUnit);

		g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nCx, nCy, M_COLOR_BLUE, 1, FALSE, PS_SOLID);
		g_clVision.DrawMOverlayLine(nUnit, nMinX, clRect.top, nMinX, clRect.bottom, M_COLOR_RED, 1, FALSE, PS_SOLID);

		return false;
	}

	if ((nIndex == 16) || (nIndex == 17))
	{
		if (nMaxLeft > nMinMaxGap)
			nMaxX = nMinX + g_clModelData[nUnit].m_clSfrInfo.m_nSizeX[nIndex];
		else
			nMaxX = clRect.right;
	}
	else if (nMaxRight < nMinMaxGap)
	{
		g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 우측 경계선이 불분명합니다. (%d)"), nIndex, nMaxRight);
		AddLog(szLog, 1, nUnit);

		g_clVision.DrawMOverlayBox(nUnit, nUnit, nCx, nSy, nEx, nEy, M_COLOR_BLUE, 1, FALSE, PS_SOLID);
		g_clVision.DrawMOverlayLine(nUnit, nMaxX, clRect.top, nMaxX, clRect.bottom, M_COLOR_RED, 1, FALSE, PS_SOLID);

		return false;
	}


	if (nMinX < 5)
	{
		if ((nIndex == 15) || (nIndex == 18))
			nMinX = 5;
	}

	if ((nMinX > nMaxX) || (nMinX < 1))
	{
		g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 좌우 경계선 인식 결과가 비정상 입니다. (좌:%d 우:%d)"), nIndex, nMinX, nMaxX);
		AddLog(szLog, 1, nUnit);

		return false;
	}
	///////////////////////////////////////////////////////////////////////하이데이타

	CRect HiRect;
	CPoint point;

	HiRect.left = nMaxX - 20;
	HiRect.right = nMaxX + 20;
	HiRect.top = (nMinY + nMaxY) / 2 - 20;
	HiRect.bottom = (nMinY + nMaxY) / 2 + 20;
	//HiRect.left = nMinX - 20;
	//HiRect.right = nMinX + 20;
	//HiRect.top = (nMinY + nMaxY) / 2 - 20;
	//HiRect.bottom = (nMinY + nMaxY) / 2 + 20;


	//point.x = nMinX;
	//point.y = (nMinY + nMaxY) / 2;

	point.x = nMaxX;
	point.y = (nMinY + nMaxY) / 2;

	//g_clVision.DrawMOverlayCross(CAM_CCD, point, 200, M_COLOR_BLUE, 2, FALSE, PS_SOLID);
	//g_clVision.DrawMOverlayBox(CAM_CCD, HiRect, M_COLOR_RED, 2, FALSE, PS_SOLID);


	////////////////////////////////////////////////////////////////////////


	clRect.left = nMinX;
	clRect.right = nMaxX;
	clRect.top = nMinY;
	clRect.bottom = nMaxY;

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool g_FindRectPos2(int nUnit, unsigned char* pImage, int nPitch, int nSizeX, int nSizeY, int nIndex, CRect& clRect)
{
	TCHAR szLog[SIZE_OF_1K];
	//int offsetX = (int)((rcRoi.right-rcRoi.left) / 3);
	//int offsetY = (rcRoi.bottom-rcRoi.top) / 2;
	int nOffsetX =  (int)((clRect.right - clRect.left) / 3);//3);
	int nOffsetY =  (int)((clRect.bottom - clRect.top) / 3);


	int min_max_Gap =  1000;

	if (pImage == NULL)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("영상 버퍼가 잘못되었습니다."));
		AddLog(szLog, 1, nUnit);
		return false;
	}

	if (nSizeX <= 0 || nSizeY <= 0)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("영상 사이즈가 잘못되었습니다. ( X : %d Y : %d )"), nSizeX, nSizeY);
		AddLog(szLog, 1, nUnit);
		return false;
	}


	int aiHistX[5000];
	int aiHistY[5000];

	if (clRect.left < 0 || clRect.top < 0 || clRect.right > nSizeX || clRect.bottom > nSizeY)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("원형 마크 검색 영역이 잘못 되었습니다. ( L : %d T : %d R : %d B : %d )"), clRect.left, clRect.top, clRect.right, clRect.bottom);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	//	vision.boxlist[CCD].addList(rcRoi, PS_DOT, M_COLOR_BLUE);

	int iSx, iSy, iEx, iEy, iCx, iCy;
	int x, y, iPos, iSum, avgX, avgY;

	::memset(aiHistY, 0, sizeof(int)*(5000));
	::memset(aiHistX, 0, sizeof(int)*(5000));


	iSx = clRect.left - nOffsetX;//iSx = clRect.left + nOffsetX;
	iEx = clRect.right + nOffsetX;//iEx = clRect.right - nOffsetX;
	iSy = clRect.top - nOffsetY;
	iEy = clRect.bottom + nOffsetY;
	//iSy = rcRoi.top		- offsetY;
	//iEy = rcRoi.bottom	+ offsetY;
	iCy = (iSy + iEy) / 2;


	if (iSx<0)				iSx = 0;
	if (iSy<0)				iSy = 0;
	if (iEx >= nSizeX)			iEx = nSizeX - 1;
	if (iEy >= nSizeY)			iEy = nSizeY - 1;

	avgY = 0;
	for (y = iSy; y < iEy; y++)
	{
		iSum = 0;
		iPos = y * nPitch + iSx;

		for (x = iSx; x < iEx; x++)
		{
			iSum += pImage[iPos];
			iPos++;
		}

		aiHistY[y] = iSum;
		avgY += iSum;
	}

	avgY = (int)(avgY / (iEy - iSy) * 0.9);


	int iMaxX = -1, iMinX = 9999;
	int iMaxY = -1, iMinY = 9999;
	int iMax_Left = -1, iMax_Right = -1, iMax_Top = -1, iMax_Bottom = -1;

	int iSum_Top, iSum_Bottom;

	for (y = iCy; y > iSy + 8; y--)
	{
		if (aiHistY[y - 1] > avgY && aiHistY[y - 3] > avgY && aiHistY[y - 5] > avgY && aiHistY[y - 7] > avgY)
		{
			iSum_Top = aiHistY[y - 7] + aiHistY[y - 5] + aiHistY[y - 3] + aiHistY[y - 1];
			iSum_Bottom = aiHistY[y + 7] + aiHistY[y + 5] + aiHistY[y + 3] + aiHistY[y + 1];

			iMax_Top = iSum_Top - iSum_Bottom;
			iMinY = y;

			break;
		}
	}

	if (y == iSy + 8)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 사각형[#%d] 상부 인식 실패."), nIndex);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	// 	vision.boxlist[CCD].addList(iSx, iSy, iEx, iCy, PS_SOLID, M_COLOR_BLUE);
	// 	vision.linelist[CCD].addList(rcRoi.left, iMinY, rcRoi.right, iMinY, PS_SOLID, M_COLOR_BLUE);


	for (y = iCy; y < iEy - 8; y++)
	{
		if (aiHistY[y + 1] > avgY && aiHistY[y + 3] > avgY && aiHistY[y + 5] > avgY && aiHistY[y + 7] > avgY)
		{
			iSum_Top = aiHistY[y - 7] + aiHistY[y - 5] + aiHistY[y - 3] + aiHistY[y - 1];
			iSum_Bottom = aiHistY[y + 7] + aiHistY[y + 5] + aiHistY[y + 3] + aiHistY[y + 1];

			iMax_Bottom = iSum_Bottom - iSum_Top;
			iMaxY = y;

			break;
		}
	}

	if (y == iEy - 8)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 사각형[#%d] 하부 인식 실패."), nIndex);
		AddLog(szLog, 1, nUnit);
		return false;
	}


	//  	vision.boxlist[CCD].addList(iSx, iCy, iEx, iEy, PS_SOLID, M_COLOR_GREEN);
	//  	vision.linelist[CCD].addList(rcRoi.left, iMaxY, rcRoi.right, iMaxY, PS_SOLID, M_COLOR_GREEN);

	if (iMax_Top < min_max_Gap)
	{
		g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 상부 경계선이 불분명합니다. (%d)"), nIndex, iMax_Top);
		AddLog(szLog, 0, nUnit);
		return false;
	}

	if (iMax_Bottom < min_max_Gap)
	{
		g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 하부 경계선이 불분명합니다. (%d)"), nIndex, iMax_Bottom);
		AddLog(szLog, 0, nUnit);
		return false;
	}

	if (iMinY >= iMaxY || iMinY<1)
	{
		g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 상하 경계선 인식 결과가 비정상 입니다. [상:%d, 하:%d]"), nIndex, iMinY, iMaxY);
		AddLog(szLog, 0, nUnit);
		return false;
	}


	nOffsetX =  (int)(clRect.right - clRect.left) / 3;
	nOffsetY =  (int)((clRect.bottom - clRect.top) / 3);

	//	if(index == 8 || index==12)
	//		offsetY = 10;

	iSx = clRect.left - nOffsetX;
	iEx = clRect.right + nOffsetX;
	iSy = iMinY + nOffsetY;
	iEy = iMaxY - nOffsetY;
	iCx = (iSx + iEx) / 2;

	if (iSx < 0)			iSx = 0;
	if (iSy < 0)			iSy = 0;
	if (iEx >= nSizeX)		iEx = nSizeX - 1;
	if (iEy >= nSizeY)		iEy = nSizeY - 1;


	/* X방향 히스토그램 */
	avgX = 0;
	for (x = iSx; x < iEx; x++)
	{
		iSum = 0;
		iPos = iSy * nPitch + x;

		for (y = iSy; y < iEy; y++)
		{
			iSum += pImage[iPos];
			iPos += nPitch;
		}

		aiHistX[x] = iSum;
		avgX += iSum;
	}

	avgX = (int)(avgX / ((iEx - iSx) * 0.9));


	int iSum_Left, iSum_Right;

	for (x = iCx; x > iSx + 5; x--)
	{
		if (aiHistX[x - 4] > avgX && aiHistX[x - 3] > avgX && aiHistX[x - 2] > avgX && aiHistX[x - 1] > avgX)
		{
			iSum_Left = aiHistX[x - 4] + aiHistX[x - 3] + aiHistX[x - 2] + aiHistX[x - 1];
			iSum_Right = aiHistX[x + 4] + aiHistX[x + 3] + aiHistX[x + 2] + aiHistX[x + 1];

			iMax_Left = iSum_Left - iSum_Right;
			iMinX = x;

			break;
		}
	}

	if ((x == iSx + 5) && (nIndex != 15) && (nIndex != 18))
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 사각형[#%d] 좌측 인식 실패."), nIndex);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	// 	vision.boxlist[CCD].addList(iSx, iSy, iCx, iEy, PS_SOLID, M_COLOR_BLUE);
	// 	vision.linelist[CCD].addList(iMinX, rcRoi.top, iMinX, rcRoi.bottom, PS_SOLID, M_COLOR_RED);

	for (x = iCx; x < iEx - 5; x++)
	{
		if (aiHistX[x + 1] > avgX && aiHistX[x + 2] > avgX && aiHistX[x + 3] > avgX && aiHistX[x + 4] > avgX)
		{
			iSum_Left = aiHistX[x - 4] + aiHistX[x - 3] + aiHistX[x - 2] + aiHistX[x - 1];
			iSum_Right = aiHistX[x + 4] + aiHistX[x + 3] + aiHistX[x + 2] + aiHistX[x + 1];

			iMax_Right = iSum_Right - iSum_Left;
			iMaxX = x;

			break;
		}
	}

	if ((x == iEx - 5) && (nIndex != 16) && (nIndex != 17))
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 사각형[#%d] 우측 인식 실패."), nIndex);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	// 	vision.boxlist[CCD].addList(iCx, iSy, iEx, iEy, PS_SOLID, M_COLOR_GREEN);
	// 	vision.linelist[CCD].addList(iMaxX, rcRoi.top, iMaxX, rcRoi.bottom, PS_SOLID, M_COLOR_GREEN);


	if (nIndex == 15 || nIndex == 18)
	{
		if (iMax_Right > min_max_Gap)
			iMinX = iMaxX - g_clModelData[nUnit].m_clSfrInfo.m_nSizeX[nIndex];
		else
			iMinX = clRect.left;
	}
	else if (iMax_Left < min_max_Gap)
	{
		g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 좌측 경계선이 불분명합니다. (%d)"), nIndex, iMax_Left);
		AddLog(szLog, 0, nUnit);

		g_clVision.DrawMOverlayBox(nUnit, nUnit, iSx, iSy, iCx, iEy, M_COLOR_BLUE, 1, FALSE, PS_SOLID);
		g_clVision.DrawMOverlayLine(nUnit, iMinX, clRect.top, iMinX, clRect.bottom, M_COLOR_RED, 1, FALSE, PS_SOLID);
		return false;
	}

	if (nIndex == 16 || nIndex == 17)
	{
		if (iMax_Left > min_max_Gap)
			iMaxX = iMinX + g_clModelData[nUnit].m_clSfrInfo.m_nSizeX[nIndex];
		else
			iMaxX = clRect.right;
	}
	else if (iMax_Right < min_max_Gap)
	{
		g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 우측 경계선이 불분명합니다. (%d)"), nIndex, iMax_Right);
		AddLog(szLog, 0, nUnit);

		g_clVision.DrawMOverlayBox(nUnit, nUnit, iCx, iSy, iEx, iEy, M_COLOR_BLUE, 1, FALSE, PS_SOLID);
		g_clVision.DrawMOverlayLine(nUnit, iMaxX, clRect.top, iMaxX, clRect.bottom, M_COLOR_RED, 1, FALSE, PS_SOLID);

		return false;
	}


	if (iMinX<5)
	{
		if (nIndex == 15 || nIndex == 18)
			iMinX = 5;
	}

	if (iMinX>iMaxX || iMinX<1)
	{
		g_clVision.DrawMOverlayBox(nUnit, nUnit, clRect, M_COLOR_RED, 1, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_1K, _T("[마크 #%d] 좌우 경계선 인식 결과가 비정상 입니다. (좌:%d 우:%d)"), nIndex, iMinX, iMaxX);
		AddLog(szLog, 0, nUnit);

		return false;
	}
	///////////////////////////////////////////////////////////////////////하이데이타

	CRect HiRect;
	CPoint point;

	HiRect.left = iMaxX - 20;
	HiRect.right = iMaxX + 20;
	HiRect.top = (iMinY + iMaxY) / 2 - 20;
	HiRect.bottom = (iMinY + iMaxY) / 2 + 20;

	point.x = iMaxX;
	point.y = (iMinY + iMaxY) / 2;

	//g_clVision.DrawMOverlayCross(CAM_CCD, point, 20, M_COLOR_RED, 2, FALSE, PS_SOLID);
	//g_clVision.DrawMOverlayBox(CAM_CCD, HiRect, M_COLOR_RED, 2, FALSE, PS_SOLID);


	////////////////////////////////////////////////////////////////////////


	clRect.left = iMinX;
	clRect.right = iMaxX;
	clRect.top = iMinY;
	clRect.bottom = iMaxY;

	//	vision.crosslist[CCD].addList((iMaxX+iMinX)/2, (iMaxY + iMinY)/2, 10, M_COLOR_MAGENTA);

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool g_FindSfrRectPos(int nUnit, unsigned char* pImage, int nPitch, int nSizeX, int nSizeY, int nIndex, CRect clRectRoi)
{
	TCHAR szLog[SIZE_OF_1K];
	int nOffsetX = 0;
	int nOffsetY = 0;
	int nIndexLeft, nIndexRight, nIndexTop, nIndexBottom;
	int iWidth = 0;
	int iHeight = 0;

	if (pImage == NULL)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR  검사 영상 버퍼가 잘못되었습니다."));
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if ((nSizeX <= 0) || (nSizeY <= 0))
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 검사 영상 사이즈가 잘못되었습니다. ( X : %d Y : %d )"), nSizeX, nSizeY);
		AddLog(szLog, 1, nUnit);

		return false;
	}


	//////////////////////////////////////////////////////////////////////////////////////////
	 
	if (nIndex == 0) { nIndexLeft = 3;		nIndexRight = 4;		nIndexTop = 1;		nIndexBottom = 2; }			//CENTER

	else if (nIndex == 1) { nIndexLeft = 6;		nIndexRight = 0;		nIndexTop = 5;		nIndexBottom = 0; }		//05F LT
	else if (nIndex == 2) { nIndexLeft = 0;		nIndexRight = 8;		nIndexTop = 7;		nIndexBottom = 0; }		//05F RT
	else if (nIndex == 3) { nIndexLeft = 10;		nIndexRight = 0;		nIndexTop = 0;		nIndexBottom = 9; }	//05F LB 
	else if (nIndex == 4) { nIndexLeft = 0;	nIndexRight = 12;		nIndexTop = 0;		nIndexBottom = 11; }	//05F RB
	 
	else if (nIndex == 5) { nIndexLeft = 0;		nIndexRight = 14;		nIndexTop = 0;		nIndexBottom = 13; }		//075F LT
	else if (nIndex == 6) { nIndexLeft = 16;	nIndexRight = 0;		nIndexTop = 0;		nIndexBottom = 15; }		//075F RT
	else if (nIndex == 7) { nIndexLeft = 0;		nIndexRight = 18;		nIndexTop = 17;		nIndexBottom = 0; }	//075F LB
	else if (nIndex == 8) { nIndexLeft = 20;	nIndexRight = 0;		nIndexTop = 19;		nIndexBottom = 0; }	//075F RB 
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 검사 마크 Index가 비정상입니다. [Index %d]"), nIndex);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	nIndexLeft--;
	nIndexRight--;
	nIndexTop--;
	nIndexBottom--;

	if ((clRectRoi.right > nSizeX - 5) && (nIndex == 8 || nIndex == 9))
	{
		clRectRoi.right = nSizeX - 5;
	}

	if ((clRectRoi.left < 5) && (nIndex == 7 || nIndex == 10))
	{
		clRectRoi.left = 5;
	}

	if ((clRectRoi.left < 0) || (clRectRoi.top < 0) || (clRectRoi.right > nSizeX) || (clRectRoi.bottom > nSizeY))
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 마크 인식 위치가 비정상 입니다. ( L %d, T %d, R %d, B %d )"), clRectRoi.left, clRectRoi.top, clRectRoi.right, clRectRoi.bottom);
		AddLog(szLog, 1, nUnit);

		return false;
	}
	int RoiHalfWidth = (clRectRoi.right - clRectRoi.left) / 2;
	int RoiHalfHeight = (clRectRoi.bottom - clRectRoi.top) / 2;

	int nCx = (clRectRoi.left + clRectRoi.right) / 2;
	int nCy = (clRectRoi.top + clRectRoi.bottom) / 2;

	int nHist[1000];

	int nSx, nSy, nEx, nEy;
	int x, y, nPos, nSum, nMaxPos, nMaxVal, nTmpVal;
	int nPosTop, nPosBottom, nPosLeft, nPosRight;

	int mDirect = 0;
	mDirect = g_clModelData[nUnit].m_nDirection[nIndexTop];
	if (mDirect == SFR_ROI_HORIZONTAL)
	{
		iWidth = g_clModelData[nUnit].m_nRoiSizeX / 2;
		iHeight = g_clModelData[nUnit].m_nRoiSizeY / 2;
	}
	else
	{
		iWidth = g_clModelData[nUnit].m_nRoiSizeY / 2;
		iHeight = g_clModelData[nUnit].m_nRoiSizeX / 2;
	}
	if (nIndexTop >= 0)
	{
		
		nOffsetX = g_clModelData[nUnit].m_MTF_ROI_Pos[0][nIndexTop].x;
		nOffsetY = g_clModelData[nUnit].m_MTF_ROI_Pos[0][nIndexTop].y;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexTop].left = -1;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexTop].right = -1;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexTop].top = -1; 
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexTop].bottom = -1;

		nSx = nCx - iWidth;// g_clModelData[nUnit].m_nRoiSizeX;
		nEx = nCx + iWidth;//g_clModelData[nUnit].m_nRoiSizeX;
		nSy = clRectRoi.top - iHeight;
		nEy = clRectRoi.top + iHeight;
#ifdef _DEBUG
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nEx, nEy, M_COLOR_DARK_GREEN, 1, 1, PS_SOLID);
#endif
		if (nSx < 0)				nSx = 0;
		if (nSy < 0)				nSy = 0;
		if (nEx >= nSizeX)			nEx = nSizeX - 1;
		if (nEy >= nSizeY)			nEy = nSizeY - 1;
		 

		memset(nHist, 0, sizeof(int)*(1000));

		for (y = nSy; y < nEy; y++)
		{
			nSum = 0;
			nPos = y * nPitch + nSx;

			for (x = nSx; x < nEx; x++)
			{
				nSum += pImage[nPos];
				nPos++;
			}

			nHist[y - nSy] = nSum;
		}

		nMaxPos = -1;
		nMaxVal = 0;

		for (y = nSy + 5; y < nEy - 5; y++)
		{
			nTmpVal = (nHist[y - nSy] + nHist[y - nSy - 1] + nHist[y - nSy - 2] + nHist[y - nSy - 3]) - (nHist[y - nSy + 1] + nHist[y - nSy + 2] + nHist[y - nSy + 3] + nHist[y - nSy + 4]);

			if (nTmpVal > nMaxVal)
			{
				nMaxVal = nTmpVal;
				nMaxPos = y;
			}
		}

		nPosTop = nMaxPos;

		

		//vision.crosslist[CCD].addList(cx, cy, 10, M_COLOR_MAGENTA);
		//g_clVision.DrawMOverlayCross(nUnit, nUnit, nCx, nCy, 10, M_COLOR_MAGENTA, 1, FALSE, PS_SOLID);	//패턴 센터 십자가

		/*nSx = nCx - g_clModelData[nUnit].m_nRoiSizeY + nOffsetX;
		nEx = nCx + g_clModelData[nUnit].m_nRoiSizeY + nOffsetX;
		nSy = nMaxPos - g_clModelData[nUnit].m_nRoiSizeX + nOffsetX;
		nEy = nMaxPos + g_clModelData[nUnit].m_nRoiSizeX + nOffsetX;
*/
		nSx = nCx - iWidth +nOffsetX;
		nEx = nCx + iWidth +nOffsetX;
		nSy = nMaxPos - iHeight + nOffsetY;//nOffsetY; 
		nEy = nMaxPos + iHeight + nOffsetY;//nOffsetY;

		if (nSx < 5)			nSx = 5;
		if (nSy < 5)			nSy = 5;
		if (nEx > nSizeX - 5)	nEx = nSizeX - 5;
		if (nEy > nSizeY - 5)	nEy = nSizeY - 5;

		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexTop].left = nSx;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexTop].right = nEx;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexTop].top = nSy;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexTop].bottom = nEy;

		//g_clVision.DrawMOverlayCross(CAM_CCD, (nSx + nEx) / 2, nMaxPos, 30, M_COLOR_RED, 3, FALSE, PS_SOLID);
        _stprintf_s(szLog, SIZE_OF_100BYTE, _T("%d"), nIndexTop);
        //g_clVision.DrawMOverlayText(nUnit, nSx + 5, nSy, szLog, M_COLOR_CYAN, _T("Arial"), 5, 20);
		g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nEx, nEy, M_COLOR_CYAN, 1, FALSE, PS_SOLID);
		if (g_clTaskWork[nUnit].m_nAutoFlag != MODE_AUTO)
		{
			g_clVision.SaveSfrImage(nUnit, pImage, nPitch, iWidth, iHeight, nIndexTop, g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexTop]);
		}


	}
	
	if (nIndexBottom >= 0)
	{
		nOffsetX = g_clModelData[nUnit].m_MTF_ROI_Pos[0][nIndexBottom].x;
		nOffsetY = g_clModelData[nUnit].m_MTF_ROI_Pos[0][nIndexBottom].y;
		/*if (g_clModelData[nUnit].m_nPatternChartUse == 1)
		{
			nOffsetX = g_clModelData[nUnit].m_MTF_ROI_Pos[0][nIndexBottom].x;
			nOffsetY = g_clModelData[nUnit].m_MTF_ROI_Pos[0][nIndexBottom].y;
			
		}
		else
		{
			nOffsetX = 0;
			nOffsetY = 0;
		}*/
		

		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexBottom].left = -1;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexBottom].right = -1;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexBottom].top = -1;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexBottom].bottom = -1;

		nSx = nCx - iWidth;
		nEx = nCx + iWidth;
		nSy = clRectRoi.bottom - iHeight;
		nEy = clRectRoi.bottom + iHeight;
#ifdef _DEBUG
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nEx, nEy, M_COLOR_DARK_GREEN, 1, 1, PS_SOLID);
#endif
		if (nSx < 0)				nSx = 0;
		if (nSy < 0)				nSy = 0;
		if (nEx >= nSizeX)			nEx = nSizeX - 1;
		if (nEy >= nSizeY)			nEy = nSizeY - 1;

		memset(nHist, 0, sizeof(int)*(1000));

		for (y = nSy; y < nEy; y++)
		{
			nSum = 0;
			nPos = y * nPitch + nSx;

			for (x = nSx; x < nEx; x++)
			{
				nSum += pImage[nPos];
				nPos++;
			}
			nHist[y - nSy] = nSum;
		}

		nMaxPos = -1;
		nMaxVal = 0;

		for (y = nSy + 5; y < nEy - 5; y++)
		{
			nTmpVal = (nHist[y - nSy] + nHist[y - nSy + 1] + nHist[y - nSy + 2] + nHist[y - nSy + 3]) - (nHist[y - nSy - 1] + nHist[y - nSy - 2] + nHist[y - nSy - 3] + nHist[y - nSy - 4]);

			if (nTmpVal > nMaxVal)
			{
				nMaxVal = nTmpVal;
				nMaxPos = y;
			}
		}

		nPosBottom = nMaxPos;

		

		//vision.crosslist[CCD].addList(cx, cy, 10, M_COLOR_MAGENTA);
		//g_clVision.DrawMOverlayCross(nUnit, nUnit, nCx, nCy, 10, M_COLOR_MAGENTA, 1, FALSE, PS_SOLID);

		nSx = nCx - iWidth + nOffsetX;
		nEx = nCx + iWidth + nOffsetX;
		nSy = nMaxPos - iHeight + nOffsetY;
		nEy = nMaxPos + iHeight + nOffsetY;

		if (nSx < 5)				nSx = 5;
		if (nSy < 5)				nSy = 5;
		if (nEx > nSizeX - 5)		nEx = nSizeX - 5;
		if (nEy > nSizeY - 5)		nEy = nSizeY - 5;

		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexBottom].left = nSx;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexBottom].right = nEx;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexBottom].top = nSy;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexBottom].bottom = nEy;

		//g_clVision.DrawMOverlayCross(CAM_CCD, (nSx + nEx) / 2, nMaxPos, 30, M_COLOR_MAGENTA, 3, FALSE, PS_SOLID);
        _stprintf_s(szLog, SIZE_OF_100BYTE, _T("%d"), nIndexBottom);
        //g_clVision.DrawMOverlayText(nUnit, nSx + 5, nSy, szLog, M_COLOR_CYAN, _T("Arial"), 5, 20);
		g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nEx, nEy, M_COLOR_CYAN, 1, FALSE, PS_SOLID);
		if (g_clTaskWork[nUnit].m_nAutoFlag != MODE_AUTO)
		{
			g_clVision.SaveSfrImage(nUnit, pImage, nPitch, iWidth, iHeight, nIndexBottom, g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexBottom]);
		}
	}

	if (nIndexLeft >= 0)
	{
		nOffsetX = g_clModelData[nUnit].m_MTF_ROI_Pos[0][nIndexLeft].x;
		nOffsetY = g_clModelData[nUnit].m_MTF_ROI_Pos[0][nIndexLeft].y;
		/*if (g_clModelData[nUnit].m_nPatternChartUse == 1)
		{
			nOffsetX = g_clModelData[nUnit].m_MTF_ROI_Pos[0][nIndexLeft].x;
			nOffsetY = g_clModelData[nUnit].m_MTF_ROI_Pos[0][nIndexLeft].y;
			
		}
		else
		{
			nOffsetX = 0;
			nOffsetY = 0;
		}*/
		

		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexLeft].left = -1;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexLeft].right = -1;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexLeft].top = -1;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexLeft].bottom = -1;

		nSx = clRectRoi.left - iWidth;
		nEx = clRectRoi.left + iWidth;
		nSy = nCy - iHeight;
		nEy = nCy + iHeight;
#ifdef _DEBUG
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nEx, nEy, M_COLOR_DARK_GREEN, 1, 1, PS_SOLID);
#endif
		if (nSx < 0)				nSx = 0;
		if (nSy < 0)				nSy = 0;
		if (nEx >= nSizeX)			nEx = nSizeX - 1;
		if (nEy >= nSizeY)			nEy = nSizeY - 1;

		memset(nHist, 0, sizeof(int)*(1000));

		for (x = nSx; x < nEx; x++)
		{
			nSum = 0;
			nPos = nSy * nPitch + x;

			for (y = nSy; y < nEy; y++)
			{
				nSum += pImage[nPos];
				nPos += nPitch;
			}

			nHist[x - nSx] = nSum;
		}

		nMaxPos = -1;
		nMaxVal = 0;

		for (x = nSx + 5; x < nEx - 5; x++)
		{
			nTmpVal = (nHist[x - nSx] + nHist[x - nSx - 1] + nHist[x - nSx - 2] + nHist[x - nSx - 3]) - (nHist[x - nSx + 1] + nHist[x - nSx + 2] + nHist[x - nSx + 3] + nHist[x - nSx + 4]);

			if (nTmpVal > nMaxVal)
			{
				nMaxVal = nTmpVal;
				nMaxPos = x;
			}
		}

		nPosLeft = nMaxPos;

		nSx = nMaxPos - iWidth + nOffsetX;
		nEx = nMaxPos + iWidth + nOffsetX;
		nSy = nCy - iHeight + nOffsetY;
		nEy = nCy + iHeight + nOffsetY;

		if (nSx < 5)				nSx = 5;
		if (nSy < 5)				nSy = 5;
		if (nEx > nSizeX - 5)		nEx = nSizeX - 5;
		if (nEy > nSizeY - 5)		nEy = nSizeY - 5;

		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexLeft].left = nSx;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexLeft].right = nEx;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexLeft].top = nSy;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexLeft].bottom = nEy;

		//g_clVision.DrawMOverlayCross(CAM_CCD, nMaxPos, (nSy + nEy) / 2, 30, M_COLOR_MAGENTA, 3, FALSE, PS_SOLID);

		_stprintf_s(szLog, SIZE_OF_100BYTE, _T("%d"), nIndexLeft);
		//g_clVision.DrawMOverlayText(nUnit, nSx + 5, nSy, szLog, M_COLOR_CYAN, _T("Arial"), 5, 20);
		g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nEx, nEy, M_COLOR_CYAN, 1, FALSE, PS_SOLID);
		if (g_clTaskWork[nUnit].m_nAutoFlag != MODE_AUTO)
		{
			g_clVision.SaveSfrImage(nUnit, pImage, nPitch, iWidth, iHeight, nIndexLeft, g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexLeft]);
		}
	}


	if (nIndexRight >= 0)
	{
		nOffsetX = g_clModelData[nUnit].m_MTF_ROI_Pos[0][nIndexRight].x;
		nOffsetY = g_clModelData[nUnit].m_MTF_ROI_Pos[0][nIndexRight].y;
		/*if (g_clModelData[nUnit].m_nPatternChartUse == 1)
		{
			nOffsetX = g_clModelData[nUnit].m_MTF_ROI_Pos[0][nIndexRight].x;
			nOffsetY = g_clModelData[nUnit].m_MTF_ROI_Pos[0][nIndexRight].y;
			
		}
		else
		{
			nOffsetX = 0;
			nOffsetY = 0;
		}*/
		

		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexRight].left = -1;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexRight].right = -1;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexRight].top = -1;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexRight].bottom = -1;

		nSx = clRectRoi.right - iWidth;
		nEx = clRectRoi.right + iWidth;
		nSy = nCy - iHeight;
		nEy = nCy + iHeight;
#ifdef _DEBUG
		//g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nEx, nEy, M_COLOR_DARK_GREEN, 1, 1, PS_SOLID);
#endif
		if (nSx < 0)				nSx = 0;
		if (nSy < 0)				nSy = 0;
		if (nEx >= nSizeX)			nEx = nSizeX - 1;
		if (nEy >= nSizeY)			nEy = nSizeY - 1;

		memset(nHist, 0, sizeof(int)*(1000));

		for (x = nSx; x < nEx; x++)
		{
			nSum = 0;
			nPos = nSy * nPitch + x;

			for (y = nSy; y < nEy; y++)
			{
				nSum += pImage[nPos];
				nPos += nPitch;
			}
			nHist[x - nSx] = nSum;
		}

		nMaxPos = -1;
		nMaxVal = 0;

		for (x = nSx + 5; x < nEx - 5; x++)
		{
			nTmpVal = (nHist[x - nSx] + nHist[x - nSx + 1] + nHist[x - nSx + 2] + nHist[x - nSx + 3]) - (nHist[x - nSx - 1] + nHist[x - nSx - 2] + nHist[x - nSx - 3] + nHist[x - nSx - 4]);

			if (nTmpVal > nMaxVal)
			{
				nMaxVal = nTmpVal;
				nMaxPos = x;
			}
		}

		nPosRight = nMaxPos;


		nSx = nMaxPos - iWidth + nOffsetX;
		nEx = nMaxPos + iWidth + nOffsetX;
		nSy = nCy - iHeight + nOffsetY;
		nEy = nCy + iHeight + nOffsetY;

		if (nSx < 5)				nSx = 5;
		if (nSy < 5)				nSy = 5;
		if (nEx > nSizeX - 5)		nEx = nSizeX - 5;
		if (nEy > nSizeY - 5)		nEy = nSizeY - 5;

		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexRight].left = nSx;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexRight].right = nEx;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexRight].top = nSy;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexRight].bottom = nEy;

		//g_clVision.DrawMOverlayCross(CAM_CCD, nMaxPos, (nSy + nEy) / 2, 30, M_COLOR_MAGENTA, 3, FALSE, PS_SOLID);
        _stprintf_s(szLog, SIZE_OF_100BYTE, _T("%d"), nIndexRight);
        //g_clVision.DrawMOverlayText(nUnit, nSx + 5, nSy, szLog, M_COLOR_CYAN, _T("Arial"), 5, 20);//10, 0); 
		g_clVision.DrawMOverlayBox(nUnit, nUnit, nSx, nSy, nEx, nEy, M_COLOR_CYAN, 1, FALSE, PS_SOLID);
		if (g_clTaskWork[nUnit].m_nAutoFlag != MODE_AUTO)
		{
			g_clVision.SaveSfrImage(nUnit, pImage, nPitch, iWidth, iHeight, nIndexRight, g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[nIndexRight]);
		}
	}

	return true; 
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool findSmallSfrRectPos(int nUnit, unsigned char* ucImage, int pitch, int sizeX, int sizeY, int nIndex, CRect rcRoi)
{
    int iSfrIndex = 0;
    int iWidth = 0;
    int iHeight = 0;
    int initNum = 0;
	int nIndexLeft, nIndexRight, nIndexTop, nIndexBottom;
    TCHAR szPos[SIZE_OF_100BYTE];
	TCHAR szLog[SIZE_OF_1K];
	int nTop = 0;
	int nLeft = 0;

	int boxIndex[MAX_LAST_INSP_COUNT] =
	{
		/*SFR_CENTER_INDEX_4,
		MAX_SFR_INSP_COUNT - 15 , MAX_SFR_INSP_COUNT - 13,
		MAX_SFR_INSP_COUNT - 11 , MAX_SFR_INSP_COUNT - 9,
		MAX_SFR_INSP_COUNT - 7 , MAX_SFR_INSP_COUNT - 5,
		MAX_SFR_INSP_COUNT - 3 , MAX_SFR_INSP_COUNT - 1,*/
		3,5,7,9,11,13,15,17,19
	};
	//Top = 0 , Bottom = 1 , Left = 2 , Right = 3

	
//#if (____MACHINE_NAME == MODEL_FRONT_100)		//ok
//
//#ifdef KUMI_TEST_MODE
//	int roiPos[MAX_SFR_INSP_COUNT] = {
//		0,1,2,3,			//CENTER  
//		1,3,1,2,0,3,0,2,	//4F
//		0,2,0,3,1,2,1,3
//	};
//#else
//	int roiPos[MAX_SFR_INSP_COUNT] = {
//		1,0,2,3,			//CENTER  0,1,2,3,
//		0,3,0,2,1,3,1,2,	//4F//1,3,1,2,0,3,0,2,	//4F
//		1,2,1,3,0,2,0,3//0,2,0,3,1,2,1,3
//};	
//#endif
//#else
//	int roiPos[MAX_SFR_INSP_COUNT] = {
//		0,1,2,3,			//CENTER
//		0,2,0,3,1,2,1,3,	//4F
//		1,3,1,2,0,3,0,2 };	//7F
//#endif

	std::vector<int> roiPos;
	if (ModelList.m_szCurrentModel == SHM_FRONT_100_MODEL)
	{
		roiPos = {
			1,0,2,3,			//CENTER  0,1,2,3,
			0,3,0,2,1,3,1,2,	//4F//1,3,1,2,0,3,0,2,	//4F
			1,2,1,3,0,2,0,3		//0,2,0,3,1,2,1,3
		};
	}
	else
	{
		roiPos = {
			0,1,2,3,			//CENTER
			0,2,0,3,1,2,1,3,	//4F
			1,3,1,2,0,3,0,2 };	//7F
	}


    if (nIndex == 0)
    {
        initNum = 0;
    }
    else
    {
        initNum = boxIndex[nIndex] - 1;
    }
    


	int mDirect = 0;

	for (iSfrIndex = initNum; iSfrIndex <= boxIndex[nIndex]; iSfrIndex++)
	{
		mDirect = g_clModelData[nUnit].m_nDirection[iSfrIndex];
		if (mDirect == SFR_ROI_HORIZONTAL)
		{
			iWidth = g_clModelData[nUnit].m_nRoiSizeX;
			iHeight = g_clModelData[nUnit].m_nRoiSizeY;
		}
		else
		{
			iWidth = g_clModelData[nUnit].m_nRoiSizeY;
			iHeight = g_clModelData[nUnit].m_nRoiSizeX;
		}


		if (roiPos[iSfrIndex] == 0)	//TOP,H
		{
			nTop = (rcRoi.top - (iHeight / 2));
			nLeft = (rcRoi.left + rcRoi .Width() /2 - (iWidth / 2));
		}else if (roiPos[iSfrIndex] == 1)	//BOTTOM,H
		{
			nTop = (rcRoi.bottom - (iHeight / 2));
			nLeft = (rcRoi.left + rcRoi.Width() / 2 - (iWidth / 2));
		}
		else if (roiPos[iSfrIndex] == 2)	//LEFT,V
		{
			nTop = (rcRoi.top + rcRoi.Height() / 2 - (iHeight / 2));
			nLeft = (rcRoi.left - (iWidth / 2));
		}
		else if (roiPos[iSfrIndex] == 3)	//RIGHR, V
		{
			nTop = (rcRoi.top + rcRoi.Height() / 2 - (iHeight / 2));
			nLeft = (rcRoi.right - (iWidth / 2));
		}

		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[iSfrIndex].left = nLeft + g_clModelData[nUnit].m_MTF_ROI_Pos[1][iSfrIndex].x;
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[iSfrIndex].top = nTop + g_clModelData[nUnit].m_MTF_ROI_Pos[1][iSfrIndex].y;

		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[iSfrIndex].right = g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[iSfrIndex].left + (iWidth);
		g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[iSfrIndex].bottom = g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[iSfrIndex].top + (iHeight);

		g_clVision.DrawMOverlayBox(nUnit, nUnit, g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[iSfrIndex], M_COLOR_YELLOW, 1, FALSE);
		_stprintf_s(szPos, SIZE_OF_100BYTE, _T("%d"), iSfrIndex);

		g_clVision.DrawMOverlayText(nUnit, g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[iSfrIndex].left + 10, g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[iSfrIndex].top + 10, szPos, M_COLOR_GREEN, _T("Arial"), 10, 12, FALSE);


		if (g_clTaskWork[nUnit].m_nAutoFlag != MODE_AUTO)
		{
			g_clVision.SaveSfrImage(nUnit, ucImage, pitch, iWidth, iHeight, iSfrIndex, g_clTaskWork[nUnit].m_stSfrInsp._64_Sfr_Rect[iSfrIndex]);
		}
    }
     
    //
    return true;
}

bool findRectPosPattern(int nUnit, unsigned char* ucImage, int pitch, int sizeX, int sizeY, int index, CRect& rcRoi)
{
    TCHAR szLog[SIZE_OF_1K];
    int offsetX = (int)((rcRoi.right - rcRoi.left) / 3);
    int offsetY = (rcRoi.bottom - rcRoi.top) / 2;

    if (ucImage == NULL)
    {
        _stprintf_s(szLog, SIZE_OF_1K, _T("SFR 영상 버퍼가 잘못되었습니다."));
        AddLog(szLog, 1, nUnit);
        return false;
    }

    if (sizeX <= 0 || sizeY <= 0)
    {
        _stprintf_s(szLog, SIZE_OF_1K, _T("영상 사이즈가 잘못되었습니다. "));
        AddLog(szLog, 1, nUnit);
        return false;
    }

    if (rcRoi.left < 0 || rcRoi.top < 0 || rcRoi.right > sizeX || rcRoi.bottom > sizeY)
    {
        _stprintf_s(szLog, SIZE_OF_1K, _T("ROI 검색 영역이 잘못 되었습니다."));
        AddLog(szLog, 1, nUnit);
        return false;
    }


    double dCenterPosX, dCenterPosY, dAngle, dRate;
    int i = index;
    {
        if (FieldPatternMatching(nUnit, i, dCenterPosX, dCenterPosY, dAngle, dRate))
        {
            rcRoi.left = dCenterPosX - g_clModelData[nUnit].m_nPatternSize[i].x / 2;
            rcRoi.right = dCenterPosX + g_clModelData[nUnit].m_nPatternSize[i].x / 2;
            rcRoi.top = dCenterPosY - g_clModelData[nUnit].m_nPatternSize[i].y / 2;
            rcRoi.bottom = dCenterPosY + g_clModelData[nUnit].m_nPatternSize[i].y / 2;
        }
    }
    return true;
}

bool CenterFieldPatternMatching(int nUnit, double &dCenterPosX, double &dCenterPosY)
{
	CRect rcArea;
	CDMPoint Center;
	double dRate;
	bool bResult = false;
	rcArea.left = (int)g_clModelData[nUnit].m_nPatternPos[0].x - 100;
	rcArea.top = (int)g_clModelData[nUnit].m_nPatternPos[0].y - 100;
	rcArea.right = (int)g_clModelData[nUnit].m_nPatternPos[0].x + g_clModelData[nUnit].m_nPatternSize[0].x + 100;
	rcArea.bottom = (int)g_clModelData[nUnit].m_nPatternPos[0].y + g_clModelData[nUnit].m_nPatternSize[0].y + 100;

	rcArea.left = (rcArea.left<0) ? 0 : rcArea.left;
	rcArea.top = (rcArea.top<0) ? 0 : rcArea.top;
	rcArea.right = (rcArea.right>g_clModelData[nUnit].m_nWidth) ? g_clModelData[nUnit].m_nWidth : rcArea.right;
	rcArea.bottom = (rcArea.bottom>g_clModelData[nUnit].m_nHeight) ? g_clModelData[nUnit].m_nHeight : rcArea.bottom;

	if (g_clVision.FieldPatternResult[nUnit][0])
	{
		MpatFree(g_clVision.FieldPatternResult[nUnit][0]);
		g_clVision.FieldPatternResult[nUnit][0] = NULL;
	}

	MpatAllocResult(g_clVision.m_MilSystem[0], M_DEFAULT, &g_clVision.FieldPatternResult[nUnit][0]);
	MpatSetPosition(g_clVision.FieldPatternImage[nUnit][0],
		rcArea.left, rcArea.top, g_clModelData[nUnit].m_nPatternSize[0].x + 100, g_clModelData[nUnit].m_nPatternSize[0].y + 100);
	MpatSetAcceptance(g_clVision.FieldPatternImage[nUnit][0], 80);
	MpatSetAccuracy(g_clVision.FieldPatternImage[nUnit][0], M_LOW);
	MpatSetCertainty(g_clVision.FieldPatternImage[nUnit][0], 70);
	MpatSetNumber(g_clVision.FieldPatternImage[nUnit][0], 1L);
	MpatSetSpeed(g_clVision.FieldPatternImage[nUnit][0], M_HIGH);
	MpatSetSearchParameter(g_clVision.FieldPatternImage[nUnit][0], M_FAST_FIND, M_DISABLE);

	/* Activate the search model angle mode. */
	MpatSetAngle(g_clVision.FieldPatternImage[nUnit][0], M_SEARCH_ANGLE_MODE, M_ENABLE);

	/* Set the search model range angle. */
	MpatSetAngle(g_clVision.FieldPatternImage[nUnit][0], M_SEARCH_ANGLE_DELTA_NEG, 10);
	MpatSetAngle(g_clVision.FieldPatternImage[nUnit][0], M_SEARCH_ANGLE_DELTA_POS, 10);

	/* Set the search model angle accuracy. */
	MpatSetAngle(g_clVision.FieldPatternImage[nUnit][0], M_SEARCH_ANGLE_ACCURACY, 0.25);

	/* Set the search model angle interpolation mode to bilinear. */
	MpatSetAngle(g_clVision.FieldPatternImage[nUnit][0], M_SEARCH_ANGLE_INTERPOLATION_MODE, M_BILINEAR);

	MpatPreprocModel(g_clVision.m_MilCcdProcChild[nUnit][2], g_clVision.FieldPatternImage[nUnit][0], M_DEFAULT);


#if 1

	//MimRotate(g_clVision.m_MilCcdProcChild[nUnit][2], g_clVision.FieldPatternImage[nUnit][0], 10, M_DEFAULT,M_DEFAULT, M_DEFAULT, M_DEFAULT, M_BILINEAR + M_OVERSCAN_CLEAR);
#endif
	MpatFindModel(g_clVision.m_MilCcdProcChild[nUnit][2], g_clVision.FieldPatternImage[nUnit][0], g_clVision.FieldPatternResult[nUnit][0]);

	double px;
	double dAngle;
	if (MpatGetNumber(g_clVision.FieldPatternResult[nUnit][0], M_NULL) == 1L)
	{
		MpatGetResult(g_clVision.FieldPatternResult[nUnit][0], M_POSITION_X, &Center.x);
		MpatGetResult(g_clVision.FieldPatternResult[nUnit][0], M_POSITION_Y, &Center.y);
		MpatGetResult(g_clVision.FieldPatternResult[nUnit][0], M_ANGLE, &dAngle);
		MpatGetResult(g_clVision.FieldPatternResult[nUnit][0], M_SCORE, &dRate);
	}
	else
	{
		dCenterPosX = 0.0;
		dCenterPosY = 0.0;
		//Center.x = (unsigned char)g_clModelData[nUnit].m_nWidth >> 1;
		//Center.y = (unsigned char)g_clModelData[nUnit].m_nHeight >> 1;
		//dRate = 0.0;
		return false;
	}

	dCenterPosX = (Center.x - (g_clModelData[nUnit].m_nWidth / 2) ) * 1;
	dCenterPosY = (Center.y - (g_clModelData[nUnit].m_nHeight / 2) ) * 1; 
	//MpatFree(g_clVision.FieldPatternResult[nUnit][0]);
	//g_clVision.FieldPatternResult[nUnit][0] = NULL;
	return true;
}



bool FieldPatternMatching(int nUnit, int iFieldNo, double &dCenterPosX, double &dCenterPosY, double &dAngle, double &dRate)
{
    CRect rcArea;
    bool bResult = false;
    rcArea.left = (int)g_clModelData[nUnit].m_nPatternPos[iFieldNo].x - 100;
    rcArea.top = (int)g_clModelData[nUnit].m_nPatternPos[iFieldNo].y - 100;
    rcArea.right = (int)g_clModelData[nUnit].m_nPatternPos[iFieldNo].x + g_clModelData[nUnit].m_nPatternSize[iFieldNo].x + 100;
    rcArea.bottom = (int)g_clModelData[nUnit].m_nPatternPos[iFieldNo].y + g_clModelData[nUnit].m_nPatternSize[iFieldNo].y + 100;
	 
    rcArea.left = (rcArea.left<0) ? 0 : rcArea.left;
    rcArea.top = (rcArea.top<0) ? 0 : rcArea.top;
    rcArea.right = (rcArea.right>g_clModelData[nUnit].m_nWidth) ? g_clModelData[nUnit].m_nWidth : rcArea.right;
    rcArea.bottom = (rcArea.bottom>g_clModelData[nUnit].m_nHeight) ? g_clModelData[nUnit].m_nHeight : rcArea.bottom;

    if (g_clVision.FieldPatternResult[nUnit][iFieldNo])
    {
        MpatFree(g_clVision.FieldPatternResult[nUnit][iFieldNo]);
        g_clVision.FieldPatternResult[nUnit][iFieldNo] = NULL;
    }

    MpatAllocResult(g_clVision.m_MilSystem[0], M_DEFAULT, &g_clVision.FieldPatternResult[nUnit][iFieldNo]);
	if (iFieldNo == 0) {
		MpatSetPosition(g_clVision.FieldPatternImage[nUnit][iFieldNo], 
		rcArea.left, rcArea.top, g_clModelData[nUnit].m_nPatternSize[iFieldNo].x + 100, g_clModelData[nUnit].m_nPatternSize[iFieldNo].y + 100);
	}
	else {
		MpatSetPosition(g_clVision.FieldPatternImage[nUnit][iFieldNo],
		rcArea.left, rcArea.top, g_clModelData[nUnit].m_nPatternSize[iFieldNo].x + 100, g_clModelData[nUnit].m_nPatternSize[iFieldNo].y + 100);
	}
    MpatSetAcceptance(g_clVision.FieldPatternImage[nUnit][iFieldNo], 80);
    MpatSetAccuracy(g_clVision.FieldPatternImage[nUnit][iFieldNo], M_LOW);
    MpatSetCertainty(g_clVision.FieldPatternImage[nUnit][iFieldNo], 70);
    MpatSetNumber(g_clVision.FieldPatternImage[nUnit][iFieldNo], 1L);
    MpatSetSpeed(g_clVision.FieldPatternImage[nUnit][iFieldNo], M_HIGH);
    MpatSetSearchParameter(g_clVision.FieldPatternImage[nUnit][iFieldNo], M_FAST_FIND, M_DISABLE);

    MpatPreprocModel(g_clVision.m_MilCcdProcChild[nUnit][2], g_clVision.FieldPatternImage[nUnit][iFieldNo], M_DEFAULT);
    MpatFindModel(g_clVision.m_MilCcdProcChild[nUnit][2], g_clVision.FieldPatternImage[nUnit][iFieldNo], g_clVision.FieldPatternResult[nUnit][iFieldNo]);

    double px;
    if (MpatGetNumber(g_clVision.FieldPatternResult[nUnit][iFieldNo], M_NULL) == 1L)
    {
        MpatGetResult(g_clVision.FieldPatternResult[nUnit][iFieldNo], M_POSITION_X, &dCenterPosX);
        MpatGetResult(g_clVision.FieldPatternResult[nUnit][iFieldNo], M_POSITION_Y, &dCenterPosY);
        //MpatGetResult(g_clVision.FieldPatternResult[nUnit][iFieldNo], M_ANGLE, &dAngle);
        MpatGetResult(g_clVision.FieldPatternResult[nUnit][iFieldNo], M_SCORE, &dRate);

        bResult = true;
    }
    else
    {
        dCenterPosX = (unsigned char)g_clModelData[nUnit].m_nWidth >> 1;
        dCenterPosY = (unsigned char)g_clModelData[nUnit].m_nHeight >> 1;
        dRate = 0.0;
        bResult = false;
    }
    MpatFree(g_clVision.FieldPatternResult[nUnit][iFieldNo]);
    g_clVision.FieldPatternResult[nUnit][iFieldNo] = NULL;
    return bResult;
}





//-----------------------------------------------------------------------------
//
//	INDEX BOTTOM LEFT
//
//-----------------------------------------------------------------------------
CRect g_GetField_RectLeft(int nUnit, unsigned char* pImage, int nPitch, int nSizeX, int nSizeY, CRect rcRoi, CPoint clCenter)
{
	CSize	siOffset = CSize(10, 10);
	int		x = 0, y = 0, sum = 0, pos = 0;
	int		maxPos = -1, maxVal = 0, tmpVal = 0;
	int		sx = 0, sy = 0, ex = 0, ey = 0;
	int		cx = 0, cy = 0;
	int		tmpHist[1000];
	CRect	rcResult = CRect(-1, -1, -1, -1);
	CRect rcRect;

	::memset(tmpHist, 0, sizeof(int)*(1000));

	rcRect.left = rcRoi.left;
	rcRect.top = rcRoi.top;
	rcRect.right = clCenter.x;
	rcRect.bottom = rcRoi.bottom;

	//cx	= (rcRoi.left + rcRoi.right) / 2;
	//cy	= (rcRoi.top + rcRoi.bottom) / 2;
	cx = clCenter.x;
	cy = clCenter.y;

	sx = rcRect.left - siOffset.cx;//(rcRect.left + rcRect.Width() / 4) - siOffset.cx;
	ex = rcRect.right + siOffset.cx;// (rcRect.left + rcRect.Width() / 4) + siOffset.cx;
	sy	= rcRect.top - siOffset.cy;
	ey	= rcRect.bottom + siOffset.cy;

	g_clVision.DrawMOverlayBox(nUnit, nUnit, rcRect, M_COLOR_GREEN, 1, 1, PS_DOT);
	g_clVision.DrawMOverlayBox(nUnit, nUnit, sx, sy, ex, ey, M_COLOR_RED, 1, 1, PS_SOLID);

	if (sx < 0)			sx = 0;
	if (sy < 0)			sy = 0;
	if (ex >= nSizeX)	ex = nSizeX - 1;
	if (ey >= nSizeY)	ey = nSizeY - 1;

	for (y = sy; y < ey; y++)
	{
		sum = 0;

		for (x = sx; x < ex; x++)
		{
			pos = y * nPitch + x;
			sum += pImage[pos];
		}
		tmpHist[y - sy] = sum;
	}

	for (y = sy + 5; y < ey - 5; y++)
	{
		tmpVal = tmpHist[y - sy] + tmpHist[y - sy - 1] - (tmpHist[y - sy + 1] + tmpHist[y - sy + 2]);

		if (tmpVal > maxVal)
		{
			maxVal = tmpVal;
			maxPos = y;
		}
	}

	sx	= ((rcRect.left + rcRect.Width() / 4) - g_clModelData[nUnit].m_nRoiSizeX);
	ex	= ((rcRect.left + rcRect.Width() / 4) + g_clModelData[nUnit].m_nRoiSizeX);
	sy	= (maxPos - g_clModelData[nUnit].m_nRoiSizeY);
	ey	= (maxPos + g_clModelData[nUnit].m_nRoiSizeY);
	if (sx < 5)				sx = 5;
	if (sy < 5)				sy = 5;
	if (ex >= nSizeX - 5)	ex = nSizeX - 5;
	if (ey >= nSizeY - 5)	ey = nSizeY - 5;


	rcResult.left	= sx;
	rcResult.right	= ex;
	rcResult.top	= sy;
	rcResult.bottom = ey;

	return rcResult;
}

//-----------------------------------------------------------------------------
//
//	INDEX BOTTOM RIGHT
//
//-----------------------------------------------------------------------------
CRect g_GetField_RectRight(int nUnit, unsigned char* pImage, int nPitch, int nSizeX, int nSizeY, CRect rcRoi)
{
	CSize	siOffset = CSize(50, 50);
	int		x = 0, y = 0, sum = 0, pos = 0;
	int		minPos = -1, minVal = 0, tmpVal = 0;
	int		sx = 0, sy = 0, ex = 0, ey = 0;
	int		cx = 0, cy = 0;
	int		tmpHist[1000];
	CRect	rcResult = CRect(-1, -1, -1, -1);

	::memset(tmpHist, 0, sizeof(int)*(1000));

	cx	= (rcRoi.left + rcRoi.right) / 2;
	cy	= (rcRoi.top + rcRoi.bottom) / 2;

	sx	= (rcRoi.right - rcRoi.Width() / 4) - siOffset.cx;
	ex	= (rcRoi.right - rcRoi.Width() / 4) + siOffset.cx;
	sy	= cy - siOffset.cy;
	ey	= cy + siOffset.cy;
	if (sx < 0)			sx = 0;
	if (sy < 0)			sy = 0;
	if (ex >= nSizeX)	ex = nSizeX - 1;
	if (ey >= nSizeY)	ey = nSizeY - 1;

	for (y = sy; y < ey; y++)
	{
		sum = 0;

		for (x = sx; x < ex; x++)
		{
			pos = y * nPitch + x;
			sum += pImage[pos];
		}
		tmpHist[y - sy] = sum;
	}

	for (y = sy + 5; y < ey - 5; y++)
	{
		tmpVal = tmpHist[y - sy] + tmpHist[y - sy - 1] - (tmpHist[y - sy + 1] + tmpHist[y - sy + 2]);

		if (tmpVal < minVal)
		{
			minVal = tmpVal;
			minPos = y;
		}
	}

	sx	= ((rcRoi.right - rcRoi.Width() / 4) - g_clModelData[nUnit].m_nRoiSizeX);
	ex	= ((rcRoi.right - rcRoi.Width() / 4) + g_clModelData[nUnit].m_nRoiSizeX);
	sy	= (minPos - g_clModelData[nUnit].m_nRoiSizeY);
	ey	= (minPos + g_clModelData[nUnit].m_nRoiSizeY);
	if (sx < 5)				sx = 5;
	if (sy < 5)				sy = 5;
	if (ex >= nSizeX - 5)	ex = nSizeX - 5;
	if (ey >= nSizeY - 5)	ey = nSizeY - 5;


	rcResult.left	= sx;
	rcResult.right	= ex;
	rcResult.top	= sy;
	rcResult.bottom = ey;

	return rcResult;
}

//-----------------------------------------------------------------------------
//
//	INDEX BOTTOM TOP
//
//-----------------------------------------------------------------------------
CRect g_GetField_RectTop(int nUnit, unsigned char* pImage, int nPitch, int nSizeX, int nSizeY, CRect rcRoi)
{
	CSize	siOffset = CSize(50, 50);
	int		x = 0, y = 0, sum = 0, pos = 0;
	int		maxPos = -1, maxVal = 0, tmpVal = 0;
	int		sx = 0, sy = 0, ex = 0, ey = 0;
	int		cx = 0, cy = 0;
	int		tmpHist[1000];
	CRect	rcResult = CRect(-1, -1, -1, -1);

	::memset(tmpHist, 0, sizeof(int)*(1000));

	cx	= (rcRoi.left + rcRoi.right) / 2;
	cy	= (rcRoi.top + rcRoi.bottom) / 2;

	sx	= cx - siOffset.cx;
	ex	= cx + siOffset.cx;
	sy	= (rcRoi.top + rcRoi.Height() / 4) - siOffset.cy;
	ey	= (rcRoi.top + rcRoi.Height() / 4) + siOffset.cy;
	if (sx < 0)			sx = 0;
	if (sy < 0)			sy = 0;
	if (ex >= nSizeX)	ex = nSizeX - 1;
	if (ey >= nSizeY)	ey = nSizeY - 1;

	for (x = sx; x < ex; x++)
	{	
		sum = 0;

		for (y = sy; y < ey; y++)
		{
			pos = y * nPitch + x;
			sum += pImage[pos];
		}
		tmpHist[x - sx] = sum;
	}

	for (x = sx + 5; x < ex - 5; x++)
	{
		tmpVal = tmpHist[x - sx] + tmpHist[x - sx - 1] - (tmpHist[x - sx + 1] + tmpHist[x - sx + 2]);

		if (tmpVal > maxVal)
		{
			maxVal = tmpVal;
			maxPos = x;
		}
	}

	sx	= (maxPos - g_clModelData[nUnit].m_nRoiSizeY);
	ex	= (maxPos + g_clModelData[nUnit].m_nRoiSizeY);
	sy	= ((rcRoi.top + rcRoi.Height() / 4) - g_clModelData[nUnit].m_nRoiSizeX);
	ey	= ((rcRoi.top + rcRoi.Height() / 4) + g_clModelData[nUnit].m_nRoiSizeX);
	if (sx < 5)				sx = 5;
	if (sy < 5)				sy = 5;
	if (ex >= nSizeX - 5)	ex = nSizeX - 5;
	if (ey >= nSizeY - 5)	ey = nSizeY - 5;

	rcResult.left	= sx;
	rcResult.right	= ex;
	rcResult.top	= sy;
	rcResult.bottom = ey;

	return rcResult;
}

//-----------------------------------------------------------------------------
//
//	INDEX BOTTOM FIELD
//
//-----------------------------------------------------------------------------
CRect g_GetField_RectBot(int nUnit, unsigned char* pImage, int nPitch, int nSizeX, int nSizeY, CRect rcRoi)
{
	CSize	siOffset = CSize(50, 50);
	int		x = 0, y = 0, sum = 0, pos = 0;
	int		minPos = -1, minVal = 0, tmpVal = 0;
	int		sx = 0, sy = 0, ex = 0, ey = 0;
	int		cx = 0, cy = 0;
	int		tmpHist[1000];
	CRect	rcResult = CRect(-1, -1, -1, -1);

	::memset(tmpHist, 0, sizeof(int)*(1000));

	cx	= (rcRoi.left + rcRoi.right) / 2;
	cy	= (rcRoi.top + rcRoi.bottom) / 2;

	sx	= cx - siOffset.cx;
	ex	= cx + siOffset.cx;
	sy	= (rcRoi.bottom - rcRoi.Width() / 4) - siOffset.cy;
	ey	= (rcRoi.bottom - rcRoi.Width() / 4) + siOffset.cy;
	if (sx < 0)			sx = 0;
	if (sy < 0)			sy = 0;
	if (ex >= nSizeX)	ex = nSizeX - 1;
	if (ey >= nSizeY)	ey = nSizeY - 1;

	for (x = sx; x < ex; x++)
	{
		sum = 0;

		for (y = sy; y < ey; y++)
		{
			pos = y * nPitch + x;
			sum += pImage[pos];
		}
		tmpHist[x - sx] = sum;
	}

	for (x = ex - 5; x > sx + 5; x--)
	{
		tmpVal = tmpHist[x - sx] + tmpHist[x - sx - 1] - (tmpHist[x - sx + 1] + tmpHist[x - sx + 2]);

		if (tmpVal < minVal)
		{
			minVal = tmpVal;
			minPos = x;
		}
	}

	sx	= (minPos - g_clModelData[nUnit].m_nRoiSizeY);
	ex	= (minPos + g_clModelData[nUnit].m_nRoiSizeY);
	sy	= ((rcRoi.bottom - rcRoi.Height() / 4) - g_clModelData[nUnit].m_nRoiSizeX);
	ey	= ((rcRoi.bottom - rcRoi.Height() / 4) + g_clModelData[nUnit].m_nRoiSizeX);
	if (sx < 5)				sx = 5;
	if (sy < 5)				sy = 5;
	if (ex >= nSizeX - 5)	ex = nSizeX - 5;
	if (ey >= nSizeY - 5)	ey = nSizeY - 5;

	rcResult.left	= sx;
	rcResult.right	= ex;
	rcResult.top	= sy;
	rcResult.bottom = ey;

	return rcResult;
}


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool g_GetPatchCenterAndSFR(int nUnit, int nIndex)
{
	
	return true;
}

//-----------------------------------------------------------------------------
//
//	광축검사
//
//-----------------------------------------------------------------------------
bool g_FindOpticalCenter(int nUnit)
{
	TCHAR szLog[SIZE_OF_1K];
	double dShiftX, dShiftY;
	CRect roi;
	bool bRetVal;

	roi.left = (int)(g_clModelData[nUnit].m_nWidth * 0.1 + 0.5);
	roi.top = (int)((g_clModelData[nUnit].m_nHeight - 4) * 0.1 + 0.5);
	roi.right = (int)(g_clModelData[nUnit].m_nWidth * 0.9 + 0.5);
	roi.bottom = (int)((g_clModelData[nUnit].m_nHeight - 4) * 0.9 + 0.5);

	g_clVision.ClearOverlay(nUnit);

	bRetVal = g_GetOpticAxis(nUnit, 4, 0, dShiftX, dShiftY);	

	if (bRetVal == true)
	{
		g_clVision.DrawMOverlayCross(nUnit, nUnit, (int)dShiftX, (int)dShiftY, 500, M_COLOR_RED, 1, FALSE, PS_SOLID);
		g_clVision.DrawOverlayAll(nUnit);
		
		_stprintf_s(szLog, SIZE_OF_1K, _T("광축 Shift (%.01f, %.01f) 검사 완료."), dShiftX, dShiftY);
		AddLog(szLog, 0, nUnit);
	}
	else
	{		
		//g_SaveInspImage(OPTIC_IMAGE_SAVE, g_clTaskWork[nUnit].m_nCurrentPcbStep);
		AddLog(_T("광축 검사 실패."), 1, nUnit);
		return false;
	}

	g_clTaskWork[nUnit].m_dOpticalPosX = dShiftX;
	g_clTaskWork[nUnit].m_dOpticalPosY = dShiftY;

	g_clTaskWork[nUnit].m_dOpticalShiftX = (g_clModelData[nUnit].m_nWidth / 2 - dShiftX) * g_clModelData[nUnit].m_dCcdCellSize / 1000;
	g_clTaskWork[nUnit].m_dOpticalShiftY = ((g_clModelData[nUnit].m_nHeight - 4) / 2 - dShiftY) * g_clModelData[nUnit].m_dCcdCellSize / 1000;

	if (fabs(g_clTaskWork[nUnit].m_dOpticalShiftX) > 1 || fabs(g_clTaskWork[nUnit].m_dOpticalShiftY) > 1)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("광축 Shift(%.03lf, %.03lf) Spec Over"), g_clTaskWork[nUnit].m_dOpticalShiftX, g_clTaskWork[nUnit].m_dOpticalShiftY);
		AddLog(szLog, 0, nUnit);

		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------
//
//	광축 검사
//
//-----------------------------------------------------------------------------
bool g_GetOpticAxis(int nUnit, int nScale, int nTh, double& dOffsetX, double& dOffsetY)
{
	CRect  centRoi, upperRoi, inspRoi;
	int* pHistX;
	int* pHistY;
	int centAvg, upperAvg, inspAvg;
	int x, y, nPos, nSum;
	int sx, ex, sy, ey;
	int nVal;

	int nPitch = (int)MbufInquire(g_clVision.m_MilCcdProcImage[nUnit], M_PITCH, NULL);
	int nSizeX = (int)MbufInquire(g_clVision.m_MilCcdProcImage[nUnit], M_SIZE_X, NULL);
	int nSizeY = (int)MbufInquire(g_clVision.m_MilCcdProcImage[nUnit], M_SIZE_Y, NULL);

	dOffsetX = nSizeX >> 1;
	dOffsetY = nSizeY >> 1;

	pHistX = new int[nSizeX];
	memset(pHistX, 0, sizeof(int) * nSizeX);
	pHistY = new int[nSizeY];
	memset(pHistY, 0, sizeof(int) * nSizeY);

	centRoi.left = (long)dOffsetX - nSizeX / 20;
	centRoi.right = (long)dOffsetX + nSizeX / 20;
	centRoi.top = (long)dOffsetY - nSizeY / 20;
	centRoi.bottom = (long)dOffsetY + nSizeY / 20;

	upperRoi.left = (long)dOffsetX - nSizeX / 20;
	upperRoi.right = (long)dOffsetX + nSizeX / 20;
	upperRoi.top = (long)0;
	upperRoi.bottom = (long)nSizeY / 20;

	inspRoi.left = (long)nSizeX / 20;
	inspRoi.right = (long)nSizeX - inspRoi.left;
	inspRoi.top = (long)nSizeY / 20;
	inspRoi.bottom = (long)nSizeY - inspRoi.top;

#ifdef ON_LINE_MIL
	g_clVision.DrawMOverlayBox(nUnit, nUnit, centRoi, M_COLOR_GREEN, 1, FALSE, PS_SOLID);
	g_clVision.DrawMOverlayBox(nUnit, nUnit, upperRoi, M_COLOR_RED, 1, FALSE, PS_SOLID);
	g_clVision.DrawMOverlayBox(nUnit, nUnit, inspRoi, M_COLOR_BLUE, 1, FALSE, PS_SOLID);
#endif

	sx = centRoi.left;
	ex = centRoi.right;
	sy = centRoi.top;
	ey = centRoi.bottom;

	nSum = 0;
	for (y = sy; y < ey; y++)
	{
		nPos = y * nPitch + sx;
		for (x = sx; x < ex; x++)
		{
			nSum += g_clVision.m_pImgBuff[nUnit][1][nPos];
			nPos++;
		}
	}
	centAvg = nSum / ((ex - sx) * (ey - sy));

	sx = upperRoi.left;
	ex = upperRoi.right;
	sy = upperRoi.top;
	ey = upperRoi.bottom;

	nSum = 0;
	for (y = sy; y < ey; y++)
	{
		nPos = y * nPitch + sx;
		for (x = sx; x < ex; x++)
		{
			nSum += g_clVision.m_pImgBuff[nUnit][1][nPos];
			nPos++;
		}
	}
	upperAvg = nSum / ((ex - sx) * (ey - sy));


	if (centAvg < 20/*60*/)	//KYH Mando Camera 측정 수정
	{
		AddLog(_T("[광축 검사 실패] 중앙부의 밝기 값이 20보다 낮습니다."), 0, nUnit);
		return false;
	}

	if (centAvg < upperAvg)
	{
		AddLog(_T("[광축 검사 실패] 중앙부의 밝기 값이 상부 밝기 값 보다 낮습니다."), 0, nUnit);
		return false;
	}

	if (centAvg - upperAvg < 10/*20*/)	//KYH Mando Camera 측정 수정
	{
		AddLog(_T("[광축 검사 실패] 중앙부와 상부의 밝기 값 차이가 10 보다 작습니다."), 0, nUnit);
		return false;
	}

	g_clTaskWork[nUnit].m_nOpticalTh = inspAvg = (centAvg + upperAvg) / 2;

	sx = inspRoi.left;
	ex = inspRoi.right;
	sy = inspRoi.top;
	ey = inspRoi.bottom;

	nSum = 0;
	for (y = sy; y < ey; y++)
	{
		nPos = y * nPitch + sx;
		for (x = sx; x < ex; x++)
		{
			nVal = g_clVision.m_pImgBuff[nUnit][1][nPos];

			if (nVal >= inspAvg)
			{
				pHistX[x]++;
				pHistY[y]++;
				nSum++;
			}
			nPos++;
		}
	}


	float fAddVal = 0;
	for (x = sx; x < ex; x++)
	{
		fAddVal += (float)(pHistX[x] * x);
	}

	float fCenterX = fAddVal / nSum;

	if ((fCenterX < (nPitch * 0.3)) || ((fCenterX > nPitch * 0.7)))
	{
		AddLog(_T("[광축 검사] X Shift 값이 비정상입니다."), 0, nUnit);
		return false;

	}


	fAddVal = 0;
	for (y = sy; y < ey; y++)
	{
		fAddVal += (float)(pHistY[y] * y);
	}

	float fCenterY = fAddVal / nSum;

	if ((fCenterY < (nSizeY * 0.3)) || ((fCenterY > nSizeY * 0.7)))
	{
		AddLog(_T("[광축 검사] Y Shift 값이 비정상입니다."), 0, nUnit);
		return false;
	}

	dOffsetX = fCenterX;
	dOffsetY = fCenterY;

	delete[] pHistX;
	pHistX = NULL;

	delete[] pHistY;
	pHistY = NULL;

	return true;
}


double ocRtn(double orgData)
{
	double temp = 0.0;
	double PointData = fabs(orgData);
	int FrontData = fabs(orgData);
	bool minusCheck = false;
	temp = PointData - FrontData;
	if (orgData < 0)
	{
		minusCheck = true;
	}
	if (temp > 0 && temp <= 0.125)
	{
		temp = 0.25;
	}
	else if (temp > 0.125 && temp <= 0.375)
	{
		temp = 0.25;
	}
	else if (temp > 0.375 && temp <= 0.625)
	{
		temp = 0.5;
	}
	else if (temp > 0.625 && temp <= 0.875)
	{
		temp = 0.75;
	}
	else if (temp > 0.875 && temp < 1.0)
	{
		temp = 0.75;
	}
	double rtnData = temp + FrontData;
	if (minusCheck == true)
	{
		rtnData *= -1;
		//rtnData += 2;
	}
	else
	{
		//rtnData -= 2;
	}
	return rtnData;
}
//-----------------------------------------------------------------------------
//
//	MTF영상으로 Shift 보정량 계산
//
//-----------------------------------------------------------------------------
double g_CalcImageAlign(int nUnit)
{
	double dShiftX, dShiftY, dOcResultX,dOcResultY;
	double dRad, dAng;
	double dWidth, dHeight;
	double dCenterX = g_clModelData[nUnit].m_nWidth / 2;
	double dCenterY = g_clModelData[nUnit].m_nHeight / 2;
	int i = 0;

	dShiftX = ((g_clTaskWork[nUnit].m_clPtCircle[0].x + g_clTaskWork[nUnit].m_clPtCircle[1].x + g_clTaskWork[nUnit].m_clPtCircle[2].x + g_clTaskWork[nUnit].m_clPtCircle[3].x) / 4.0) - dCenterX;
	dShiftY = ((g_clTaskWork[nUnit].m_clPtCircle[0].y + g_clTaskWork[nUnit].m_clPtCircle[1].y + g_clTaskWork[nUnit].m_clPtCircle[2].y + g_clTaskWork[nUnit].m_clPtCircle[3].y) / 4.0) - dCenterY;


	dOcResultX = dShiftX;
	dOcResultY = dShiftY;

	dShiftX *= g_clModelData[nUnit].m_dCcdCellSize / 1000;
	dShiftY *= g_clModelData[nUnit].m_dCcdCellSize / 1000;
	dShiftX *= -1;


	dWidth = (g_clTaskWork[nUnit].m_clPtCircle[3].x - g_clTaskWork[nUnit].m_clPtCircle[2].x) * g_clModelData[nUnit].m_dCcdCellSize /1000;
	dHeight = (g_clTaskWork[nUnit].m_clPtCircle[3].y - g_clTaskWork[nUnit].m_clPtCircle[2].y) * g_clModelData[nUnit].m_dCcdCellSize /1000;

	dRad = atan(dHeight / dWidth);
	dAng = dRad * 180.0 / M_PI;

	//if (fabs(dShiftX) > 1.0 || fabs(dShiftY) > 1.0 || fabs(dAng) > 3.0)		// 임의값...
	//{
	//	AddLog(_T("이미지 얼라인 보정값 리미트 에러."), 0, nUnit);
	//	return false;
	//}
	
	if (dAng > 5.0)
	{
		dAng = 5.0;
	}
	if (dAng < -5.0)
	{
		dAng = -5.0;
	}
	g_clTaskWork[nUnit].m_dImgShiftX = dShiftX;
	g_clTaskWork[nUnit].m_dImgShiftY = dShiftY * -1; 
	g_clTaskWork[nUnit].m_dImgShiftTh = dAng * -1;
    //
	return g_clTaskWork[nUnit].m_dImgShiftTh;
}

void g_CheckEolLight(int m_nUnit, int index)
{
	int i = 0;
	TCHAR	szLog[SIZE_OF_1K];

	double mLight_Value = 0.0;

	double Light_SpecMin = 0.0;
	double Light_SpecMax = 0.0;

	

	if (index == 0)
	{
		//차트 밝기
		for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
		{
			mLight_Value = g_clMesCommunication[m_nUnit].m_dMesSaturationChart[i];

			_stprintf_s(szLog, SIZE_OF_1K, _T("[LIGHT] CHART #%d Saturation : %.1lf"), i, mLight_Value); 
			AddLog(szLog, 0, m_nUnit);


			//Light_SpecMin = (_ttof(EEpromVerifyData.vMinData[24 + i]));		//42 ~ 50
			//Light_SpecMax = (_ttof(EEpromVerifyData.vMaxData[24 + i]));


			//if (mLight_Value < Light_SpecMin || mLight_Value > Light_SpecMax)
			//{
			//	g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;
			//	g_clMesCommunication[m_nUnit].m_dMesLightChartResult[i] = 0;

			//	_stprintf_s(szLog, SIZE_OF_1K, _T("[LIGHT] CHART #%d Saturation Spec Out: %.1lf [%.1lf~%.1lf]"), i, mLight_Value, Light_SpecMin, Light_SpecMax);
			//	AddLog(szLog, 0, m_nUnit);
			//	g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [LIGHT CHART NG]");
			//	if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
			//	{
			//		g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG LIGHT CHART #%d :%.1lf [%.1lf~%.1lf]"),i, mLight_Value, Light_SpecMin, Light_SpecMax);
			//		g_clMandoInspLog[m_nUnit].m_nNGCnt++;
			//	}

			//	g_clMandoInspLog[m_nUnit].m_bInspRes = false;
			//	g_clTaskWork[m_nUnit].m_bOutputCheck[2] = false;	//OC

			//}
			//else
			//{
			//	g_clMesCommunication[m_nUnit].m_dMesLightChartResult[i] = 1;
			//	_stprintf_s(szLog, SIZE_OF_1K, _T("[LIGHT] CHART #%d Saturation Spec In: %.1lf [%.1lf~%.1lf]"), i, mLight_Value, Light_SpecMin, Light_SpecMax);
			//	AddLog(szLog, 0, m_nUnit);
			//}
		}
	}
	else
	{
		//이물 조명 밝기

		mLight_Value = g_clMesCommunication[m_nUnit].m_dMesSaturationOc;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[LIGHT] OC Saturation : %.1lf"), mLight_Value);
		AddLog(szLog, 0, m_nUnit);

		//Light_SpecMin = (_ttof(EEpromVerifyData.vMinData[33]));		//42 ~ 50
		//Light_SpecMax = (_ttof(EEpromVerifyData.vMaxData[33]));


		//if (mLight_Value < Light_SpecMin || mLight_Value > Light_SpecMax)
		//{
		//	g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;
		//	g_clMesCommunication[m_nUnit].m_dMesLightOcResult = 0;

		//	_stprintf_s(szLog, SIZE_OF_1K, _T("[LIGHT] OC Saturation Spec Out: %.1lf [%.1lf~%.1lf]"), mLight_Value, Light_SpecMin, Light_SpecMax);
		//	AddLog(szLog, 0, m_nUnit);
		//	g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [LIGHT CHART NG]");
		//	if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		//	{
		//		g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG LIGHT OC :%.1lf [%.1lf~%.1lf]"), mLight_Value, Light_SpecMin, Light_SpecMax);
		//		g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		//	}

		//	g_clMandoInspLog[m_nUnit].m_bInspRes = false;
		//	g_clTaskWork[m_nUnit].m_bOutputCheck[2] = false;	//OC

		//}
		//else
		//{
		//	g_clMesCommunication[m_nUnit].m_dMesLightOcResult = 1;
		//	_stprintf_s(szLog, SIZE_OF_1K, _T("[LIGHT] OC Saturation Spec In: %.1lf [%.1lf~%.1lf]"), mLight_Value, Light_SpecMin, Light_SpecMax);
		//	AddLog(szLog, 0, m_nUnit);
		//}
	}
}
void g_CheckEolRotation(int m_nUnit)
{
	TCHAR	szLog[SIZE_OF_1K];
	int i = 0;


	double dRad = 0.0;
	double dAng = 0.0;
	double dWidth = 0.0;
	double dHeight = 0.0;

	dWidth = (g_clTaskWork[m_nUnit].m_clPtRotationCircle[3].x - g_clTaskWork[m_nUnit].m_clPtRotationCircle[2].x) * g_clModelData[m_nUnit].m_dCcdCellSize / 1000;
	dHeight = (g_clTaskWork[m_nUnit].m_clPtRotationCircle[3].y - g_clTaskWork[m_nUnit].m_clPtRotationCircle[2].y) * g_clModelData[m_nUnit].m_dCcdCellSize / 1000;
	

	//dWidth = (g_clTaskWork[m_nUnit].m_clPtCircle[3].x - g_clTaskWork[m_nUnit].m_clPtCircle[2].x) * g_clModelData[m_nUnit].m_dCcdCellSize / 1000;
	//dHeight = (g_clTaskWork[m_nUnit].m_clPtCircle[3].y - g_clTaskWork[m_nUnit].m_clPtCircle[2].y) * g_clModelData[m_nUnit].m_dCcdCellSize / 1000;

	dRad = atan(dHeight / dWidth);
	dAng = dRad * 180.0 / M_PI;


	double mRotation_Value = dAng * -1;

	double Rotation_SpecMin = 0.0;
	double Rotation_SpecMax = 0.0;
	g_clMesCommunication[m_nUnit].m_dMesUvAfterRotate = mRotation_Value;

	//Rotation_SpecMin = (_ttof(EEpromVerifyData.vMinData[17]));
	//Rotation_SpecMax = (_ttof(EEpromVerifyData.vMaxData[17]));
	Rotation_SpecMin = g_clMesCommunication[m_nUnit].mapKeyRtn(RECIPE_PARAM_NAME[23]);
	Rotation_SpecMax = g_clMesCommunication[m_nUnit].mapKeyRtn(RECIPE_PARAM_NAME[24]);

	if (mRotation_Value < Rotation_SpecMin || mRotation_Value > Rotation_SpecMax)
	{
		g_clMesCommunication[m_nUnit].m_dEqpDefectCode.Format(_T("31"));
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;
		g_clMesCommunication[m_nUnit].m_dMesRotateUVAfterResult = 0;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[ROTATION] Spec Out: %.6lf [%.3lf~%.3lf]"), mRotation_Value, Rotation_SpecMin, Rotation_SpecMax);
		AddLog(szLog, 0, m_nUnit);
		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [ROTATION NG]");
		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG ROTATION :%.6lf [%.3lf~%.3lf]"), mRotation_Value, Rotation_SpecMin, Rotation_SpecMax);
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}
		//g_clMesCommunication[m_nUnit].m_nMesRIRICornerResult[0] = 0;

		g_clMandoInspLog[m_nUnit].m_bInspRes = false;
		g_clTaskWork[m_nUnit].m_bOutputCheck[2] = false;	//OC

	}
	else
	{
		g_clMesCommunication[m_nUnit].m_dMesRotateUVAfterResult = 1;
		_stprintf_s(szLog, SIZE_OF_1K, _T("[ROTATION] Spec In: %.6lf [%.3lf~%.3lf]"), mRotation_Value, Rotation_SpecMin, Rotation_SpecMax);
		AddLog(szLog, 0, m_nUnit);
	}

}

bool g_GetSfrMinMaxValue(int nUnit, bool bNgDraw)
{
	//bDiffNg = true일 때 ng가 발생하면 별도 sfr값으로 계산
	//bNgDraw = true일때 , retry 마지막 때 ng 표시
	TCHAR	szLog[SIZE_OF_1K];
	CString NGData = _T("");
	double mMinSpec = 0.0;
	double mMaxSpec = 0.0;
	double mDiffValue = 0.0;
	double min = 0.0;
	double max = 0.0;

	double dEdgeAvr_4F[4];
	double dEdgeAvr_7F[4];

	bool bDiffNgRtn = true;


	dEdgeAvr_4F[0] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[4] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[5]) / 2;
	dEdgeAvr_4F[1] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[6] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[7]) / 2;
	dEdgeAvr_4F[2] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[8] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[9]) / 2;
	dEdgeAvr_4F[3] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[10] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[11]) / 2;
	//
	dEdgeAvr_7F[0] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[12] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[13]) / 2;
	dEdgeAvr_7F[1] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[14] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[15]) / 2;
	dEdgeAvr_7F[2] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[16] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[17]) / 2;
	dEdgeAvr_7F[3] = (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[18] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[19]) / 2;


	min = *std::min_element(dEdgeAvr_4F, dEdgeAvr_4F + 4);
	max = *std::max_element(dEdgeAvr_4F, dEdgeAvr_4F + 4);
	g_clMesCommunication[nUnit].m_dMes4F_Diff = max - min;

	min = *std::min_element(dEdgeAvr_7F, dEdgeAvr_7F + 4);
	max = *std::max_element(dEdgeAvr_7F, dEdgeAvr_7F + 4);
	g_clMesCommunication[nUnit].m_dMes7F_Diff = max - min;

	//mMinSpec = (_ttof(EEpromVerifyData.vMinData[13]));	//04F DIFF
	//mMaxSpec = (_ttof(EEpromVerifyData.vMaxData[13]));
	mMinSpec = g_clMesCommunication[nUnit].mapKeyRtn(RECIPE_PARAM_NAME[15]);
	mMaxSpec = g_clMesCommunication[nUnit].mapKeyRtn(RECIPE_PARAM_NAME[16]);


	mDiffValue = g_clMesCommunication[nUnit].m_dMes4F_Diff;

	if (mDiffValue < mMinSpec || mDiffValue > mMaxSpec)
	{
		g_clMesCommunication[nUnit].m_dEqpDefectCode.Format(_T("28"));
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 04F DIFF SPEC OUT:%.3lf[%.3lf ~ %.3lf]"), mDiffValue, mMinSpec, mMaxSpec);
		AddLog(szLog, 0, nUnit);

		bDiffNgRtn = false;
		if (bNgDraw == true)
		{
			g_clMesCommunication[nUnit].m_nMesFinalResult = 0;	//MTF DIFF
			g_clMesCommunication[nUnit].m_dMes4F_DiffResult = 0;

			NGData.Format(_T("%s"), szLog);
			g_clMandoInspLog[nUnit].m_sNGList += _T(" [04F DIFF NG]");
			if (g_clMandoInspLog[nUnit].m_nNGCnt < 30)
			{
				g_clMandoInspLog[nUnit].m_sDispNG[g_clMandoInspLog[nUnit].m_nNGCnt] += NGData;
				g_clMandoInspLog[nUnit].m_nNGCnt++;
			}

		}
	}
	else
	{
		g_clMesCommunication[nUnit].m_dMes4F_DiffResult = 1;
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 04F DIFF SPEC IN =  %.3lf[%.3lf ~ %.3lf]"), mDiffValue, mMinSpec, mMaxSpec);
		AddLog(szLog, 0, nUnit);
	}
	//mMinSpec = (_ttof(EEpromVerifyData.vMinData[14]));	//07F DIFF
	//mMaxSpec = (_ttof(EEpromVerifyData.vMaxData[14]));
	mMinSpec = g_clMesCommunication[nUnit].mapKeyRtn(RECIPE_PARAM_NAME[17]);
	mMaxSpec = g_clMesCommunication[nUnit].mapKeyRtn(RECIPE_PARAM_NAME[18]);

	mDiffValue = g_clMesCommunication[nUnit].m_dMes7F_Diff;

	if (mDiffValue < mMinSpec || mDiffValue > mMaxSpec)
	{
		g_clMesCommunication[nUnit].m_dEqpDefectCode.Format(_T("29"));
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 07F DIFF SPEC OUT:%.3lf[%.3lf ~ %.3lf]"), mDiffValue, mMinSpec, mMaxSpec);
		AddLog(szLog, 0, nUnit);

		bDiffNgRtn = false;
		if (bNgDraw == true)
		{
			g_clMesCommunication[nUnit].m_nMesFinalResult = 0;	//MTF DIFF
			g_clMesCommunication[nUnit].m_dMes7F_DiffResult = 0;

			NGData.Format(_T("%s"), szLog);

			g_clMandoInspLog[nUnit].m_sNGList += _T(" [07F DIFF NG]");
			if (g_clMandoInspLog[nUnit].m_nNGCnt < 30)
			{
				g_clMandoInspLog[nUnit].m_sDispNG[g_clMandoInspLog[nUnit].m_nNGCnt] += NGData;
				g_clMandoInspLog[nUnit].m_nNGCnt++;
			}
		}
	}
	else
	{
		g_clMesCommunication[nUnit].m_dMes7F_DiffResult = 1;
		_stprintf_s(szLog, SIZE_OF_1K, _T("SFR 07F DIFF SPEC IN =  %.3lf[%.3lf ~ %.3lf]"), mDiffValue, mMinSpec, mMaxSpec);
		AddLog(szLog, 0, nUnit);
	}


	NGData.Empty();
	return bDiffNgRtn;
}

double findDiffData(double sfrData[], int totalCount, int index)
{
	int i = 0;
	double dReturn = 0.0;

	dReturn = sfrData[0];
	for (i = 0; i < totalCount; i++)
	{
		if (index == 2)	//index = 0이면 Min이라서 그중에서 가장 큰 Max찾기
		{
			if (dReturn < sfrData[i])
			{
				dReturn = sfrData[i];
			}
		}
		else if (index == 1)	//index = 1이면 Max이라서 그중에서 가장 작은 Min찾기
		{
			if (dReturn > sfrData[i])
			{
				dReturn = sfrData[i];
			}
		}
		else
		{
			dReturn = 0.0;
			break;
		}
	}
	return dReturn;
}

int findMax(double sfrData[], int totalCount, int a, int b, int c, int d)
{
	int maxIndex = a;
	//double MaxSfr = sfrData[maxIndex];
	if (sfrData[b] > sfrData[maxIndex])
	{
		maxIndex = b;
	}
	if (totalCount == 2) return maxIndex;
	if (sfrData[c] > sfrData[maxIndex])
	{
		maxIndex = c;
	}
	if (totalCount == 3) return maxIndex;
	if (sfrData[d] > sfrData[maxIndex])
	{
		maxIndex = d;
	}

	return maxIndex;
}
int findMin(double sfrData[], int totalCount, int a, int b, int c, int d)
{
	int minIndex = a;
	//double MaxSfr = sfrData[minIndex];
	if (sfrData[b] < sfrData[minIndex])
	{
		minIndex = b;
	}
	if (totalCount == 2) return minIndex;
	if (sfrData[c] < sfrData[minIndex])
	{
		minIndex = c;
	}
	if (totalCount == 3) return minIndex;
	if (sfrData[d] < sfrData[minIndex])
	{
		minIndex = d;
	}

	return minIndex;
}

bool g_DiffReset()
{
	int i = 0;
	int j = 0;
	int nUnit = 0;
	int index = 0;
	int m_MinMaxCheck[MAX_SFR_INSP_COUNT];	//12개 값의 min , max체크 1이면 max값이다

	double m_AverageSfrData[MAX_SFR_INSP_COUNT];		//V,H 6개의 평균값 비교값중에 MIN , MAX 선정위해 MIN중에서 가장큰값 , MAX중에서 가장 작은값으로 DIFF 계산하기위해

	memset(g_clTaskWork[nUnit].m_MinMaxIndex, 0, sizeof(g_clTaskWork[nUnit].m_MinMaxIndex));

	memset(m_MinMaxCheck, 0, sizeof(m_MinMaxCheck));
	memset(g_clTaskWork[nUnit].m_AligData, 0.0, sizeof(g_clTaskWork[nUnit].m_AligData));
	memset(m_AverageSfrData, 0.0, sizeof(m_AverageSfrData));


	//g_clTaskWork[nUnit].m_stSfrInsp.dAver_MTF[sfr20개][10번 스캔] = 0.0;

	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		for (j = 0; j < 10; j++)
		{
			m_AverageSfrData[i] += g_clTaskWork[nUnit].m_stSfrInsp.dAver_MTF[i][j];
		}
		m_AverageSfrData[i] /= 10.0;
	}

	//4-6-8-10		(04F 수직)
	//5-7-9-11		(04F 수평)
	//12-14-16-18	(07F 수직)
	//13-15-17-19	(07F 수평)

	//---------------------------------------------------------------------------------
	//0.4F
	//
	index = findMax(m_AverageSfrData, 4, 4, 6, 8, 10);//4, 7, 8, 11);
	m_MinMaxCheck[index] = 1;
	g_clTaskWork[nUnit].m_MinMaxIndex[4] = index;
	index = findMin(m_AverageSfrData, 4, 4, 6, 8, 10);//4, 7, 8, 11);
	m_MinMaxCheck[index] = 2;
	g_clTaskWork[nUnit].m_MinMaxIndex[5] = index;

	index = findMax(m_AverageSfrData, 4, 5, 7, 9, 11);//5, 6, 9, 10);
	m_MinMaxCheck[index] = 1;
	g_clTaskWork[nUnit].m_MinMaxIndex[6] = index;
	index = findMin(m_AverageSfrData, 4, 5, 7, 9, 11);//5, 6, 9, 10);
	m_MinMaxCheck[index] = 2;
	g_clTaskWork[nUnit].m_MinMaxIndex[7] = index;

	//---------------------------------------------------------------------------------
	//0.7F
	//
	index = findMax(m_AverageSfrData, 4, 12, 14, 16, 18);//12, 15, 16, 19);
	m_MinMaxCheck[index] = 1;
	g_clTaskWork[nUnit].m_MinMaxIndex[8] = index;
	index = findMin(m_AverageSfrData, 4, 12, 14, 16, 18);//12, 15, 16, 19);
	m_MinMaxCheck[index] = 2;
	g_clTaskWork[nUnit].m_MinMaxIndex[9] = index;
	//
	index = findMax(m_AverageSfrData, 4, 13, 15, 17, 19);//13, 14, 17, 18);
	m_MinMaxCheck[index] = 1;
	g_clTaskWork[nUnit].m_MinMaxIndex[10] = index;
	index = findMin(m_AverageSfrData, 4, 13, 15, 17, 19);//13, 14, 17, 18);
	m_MinMaxCheck[index] = 2;
	g_clTaskWork[nUnit].m_MinMaxIndex[11] = index;

	//
	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		g_clTaskWork[nUnit].m_AligData[i] = findDiffData(g_clTaskWork[nUnit].m_stSfrInsp.dAver_MTF[i], 10, m_MinMaxCheck[i]);
		//10개 값중에서평균값이 MIN이면 최대값 , MAX면 최소값 찾기
	}

	int mTemp = 0;
	for (i = 4; i < 12; i++)		//4F , 7F만 적용
	{
		mTemp = g_clTaskWork[nUnit].m_MinMaxIndex[i];
		////g_clMandoInspLog[nUnit].m_UvAfterSFR[mTemp] = g_clTaskWork[nUnit].m_AligData[mTemp];
		g_clMesCommunication[nUnit].m_dMesUvAfterMTF[mTemp] = g_clTaskWork[nUnit].m_AligData[mTemp];
	}

	return true;
}
void g_CheckEolOc(int nUnit)
{
	TCHAR	szLog[SIZE_OF_1K];
	int i = 0;

	for (i = 0; i < 2; i++)
	{
		g_clMesCommunication[nUnit].m_dMesUVAfterOCResult[i] = 1;
	}

	double dShiftX, dShiftY, dOcResultX, dOcResultY;
	double dRad, dAng;
	double dWidth, dHeight;

	double dCenterX = g_clModelData[nUnit].m_nWidth / 2;
	double dCenterY = g_clModelData[nUnit].m_nHeight / 2;


	//
	/*dShiftX = ((g_clTaskWork[nUnit].m_clPtCircle[0].x + g_clTaskWork[nUnit].m_clPtCircle[1].x + g_clTaskWork[nUnit].m_clPtCircle[2].x + g_clTaskWork[nUnit].m_clPtCircle[3].x) / 4.0) - dCenterX;
	dShiftY = ((g_clTaskWork[nUnit].m_clPtCircle[0].y + g_clTaskWork[nUnit].m_clPtCircle[1].y + g_clTaskWork[nUnit].m_clPtCircle[2].y + g_clTaskWork[nUnit].m_clPtCircle[3].y) / 4.0) - dCenterY;*/

	dShiftX = ((g_clTaskWork[nUnit].m_clPtRotationCircle[0].x + g_clTaskWork[nUnit].m_clPtRotationCircle[1].x + g_clTaskWork[nUnit].m_clPtRotationCircle[2].x + g_clTaskWork[nUnit].m_clPtRotationCircle[3].x) / 4.0) - dCenterX;
	dShiftY = ((g_clTaskWork[nUnit].m_clPtRotationCircle[0].y + g_clTaskWork[nUnit].m_clPtRotationCircle[1].y + g_clTaskWork[nUnit].m_clPtRotationCircle[2].y + g_clTaskWork[nUnit].m_clPtRotationCircle[3].y) / 4.0) - dCenterY;

#ifdef KUMI_TEST_MODE
	dOcResultX = dShiftX;
	dOcResultY = dShiftY;
#else
	dOcResultX =  dShiftX + g_clSysData.m_dOcOffset[0];
	dOcResultY =  dShiftY + g_clSysData.m_dOcOffset[1];
#endif

	g_clTaskWork[nUnit].m_dImgShiftX = 0.0;
	g_clTaskWork[nUnit].m_dImgShiftY = 0.0; 
	g_clTaskWork[nUnit].m_dImgShiftTh = 0.0;
	//

	g_clMandoInspLog[nUnit].m_UvAfter_OC_DelatX = dOcResultX;// ocRtn(dOcResultX);	//DELTA 가 작은값
	g_clMandoInspLog[nUnit].m_UvAfter_OC_DelatY = dOcResultY;// ocRtn(dOcResultY);


	g_clMandoInspLog[nUnit].m_UvAfter_OC_X = dOcResultX;// ocRtn(dOcResultX) + dCenterX;
	g_clMandoInspLog[nUnit].m_UvAfter_OC_Y = dOcResultY;// ocRtn(dOcResultY) + dCenterY;


	g_clMesCommunication[nUnit].m_dMesUVAfterOC[0] = g_clMandoInspLog[nUnit].m_UvAfter_OC_X;		//EOL WIDE OC
	g_clMesCommunication[nUnit].m_dMesUVAfterOC[1] = g_clMandoInspLog[nUnit].m_UvAfter_OC_Y;		//EOL WIDE OC

	g_clMesCommunication[nUnit].m_dMesUVAfterDeltaOC[0] = g_clMandoInspLog[nUnit].m_UvAfter_OC_DelatX;		//DELTA OC
	g_clMesCommunication[nUnit].m_dMesUVAfterDeltaOC[1] = g_clMandoInspLog[nUnit].m_UvAfter_OC_DelatY;		//DELTA OC


	//_ftprintf_s(fp, _T("%0.3lf, %0.3lf,"), g_clMesCommunication[nUnit].m_dMesOC[0], g_clMesCommunication[nUnit].m_dMesOC[1]);
	//_ftprintf_s(fp, _T("%0.3lf, %0.3lf,"), g_clMesCommunication[nUnit].m_dMesDeltaOC[0], g_clMesCommunication[nUnit].m_dMesDeltaOC[1]);

	double mOcX_Value = 0.0;
	double mOcy_Value = 0.0;

	double OCX_SpecMin = 0.0;
	double OCX_SpecMax = 0.0;

	double OCY_SpecMin = 0.0;
	double OCY_SpecMax = 0.0;

	//OCX_SpecMin = (_ttof(EEpromVerifyData.vMinData[15]));
	//OCX_SpecMax = (_ttof(EEpromVerifyData.vMaxData[15]));
	OCX_SpecMin = g_clMesCommunication[nUnit].mapKeyRtn(RECIPE_PARAM_NAME[19]);
	OCX_SpecMax = g_clMesCommunication[nUnit].mapKeyRtn(RECIPE_PARAM_NAME[20]);

	//OCY_SpecMin = (_ttof(EEpromVerifyData.vMinData[16]));
	//OCY_SpecMax = (_ttof(EEpromVerifyData.vMaxData[16]));
	OCY_SpecMin = g_clMesCommunication[nUnit].mapKeyRtn(RECIPE_PARAM_NAME[21]);
	OCY_SpecMax = g_clMesCommunication[nUnit].mapKeyRtn(RECIPE_PARAM_NAME[22]);
	
	mOcX_Value = g_clMandoInspLog[nUnit].m_UvAfter_OC_DelatX;
	mOcy_Value = g_clMandoInspLog[nUnit].m_UvAfter_OC_DelatY;

	g_clTaskWork[nUnit].m_bOutputCheck[2] = true;	//OC 

	if (mOcX_Value < OCX_SpecMin || mOcX_Value > OCX_SpecMax)
	{
		g_clMesCommunication[nUnit].m_dEqpDefectCode.Format(_T("14"));
		g_clMesCommunication[nUnit].m_nMesFinalResult = 0;	//OC X
		
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[OC]OC X Spec Out %.2lf [%.2lf~%.2lf]"), mOcX_Value, OCX_SpecMin, OCX_SpecMax);
		AddLog(szLog, 0, nUnit);
		g_clMandoInspLog[nUnit].m_sNGList += _T(" [OC X NG]");
		if (g_clMandoInspLog[nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[nUnit].m_sDispNG[g_clMandoInspLog[nUnit].m_nNGCnt].Format(_T("NG OC X:%.2lf [%.2lf~%.2lf]"), mOcX_Value, OCX_SpecMin, OCX_SpecMax);
			g_clMandoInspLog[nUnit].m_nNGCnt++;
		}
		g_clMesCommunication[nUnit].m_dMesUVAfterOCResult[0] = 0; 

		g_clMandoInspLog[nUnit].m_bInspRes = false;
		g_clTaskWork[nUnit].m_bOutputCheck[2] = false;	//OC

	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[OC]OC X Spec In %.2lf [%.2lf~%.2lf]"), mOcX_Value, OCX_SpecMin, OCX_SpecMax);
		AddLog(szLog, 0, nUnit);
	}

	if (mOcy_Value < OCY_SpecMin || mOcy_Value > OCY_SpecMax)
	{
		g_clMesCommunication[nUnit].m_dEqpDefectCode.Format(_T("15"));
		g_clMesCommunication[nUnit].m_nMesFinalResult = 0;	//OC Y
		
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[OC]OC Y Spec Out %.2lf [%.2lf~%.2lf]"), mOcy_Value, OCY_SpecMin, OCY_SpecMax);
		AddLog(szLog, 0, nUnit);

		g_clMandoInspLog[nUnit].m_sNGList += _T(" [OC Y NG]");
		if (g_clMandoInspLog[nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[nUnit].m_sDispNG[g_clMandoInspLog[nUnit].m_nNGCnt].Format(_T("NG OC Y:%.2lf [%.2lf~%.2lf]"), mOcy_Value, OCY_SpecMin, OCY_SpecMax);
			g_clMandoInspLog[nUnit].m_nNGCnt++;
		}
		g_clMesCommunication[nUnit].m_dMesUVAfterOCResult[1] = 0;


		g_clMandoInspLog[nUnit].m_bInspRes = false;
		g_clTaskWork[nUnit].m_bOutputCheck[2] = false;	//OC
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[OC]OC Y Spec In %.2lf [%.2lf~%.2lf]"), mOcy_Value, OCY_SpecMin, OCY_SpecMax);
		AddLog(szLog, 0, nUnit);
	}

}


void g_CheckOc(int nUnit, bool bUvShot)
{
	

}
//-----------------------------------------------------------------------------
//
//	ALIGN Spec In Check
//
//-----------------------------------------------------------------------------
int g_CheckAlignSpec(int nUnit, int nMarkType, double dX, double dY, double dTh)
{
	TCHAR szLog[SIZE_OF_1K];

	if ((fabs(dX) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_X]) || (fabs(dY) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Y]) ||
		(fabs(dTh) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH]))
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[ERROR] PCB부 X,Y,T 보정값(%.03lf, %.03lf, %.03lf)이 보정 Limit(%.03lf, %.03lf, %.03lf)을 초과했습니다."),
			dX, dY, dTh, g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_X], g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Y], g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH]);
		AddLog(szLog, 0, nUnit);

		return 0;		//보정량 초과
	}
	double dAlignSpecX = 0.0;
	double dAlignSpecY = 0.0;
	double dAlignSpecTh = 0.0;
	if (nMarkType == SENSOR_ALIGN_MARK)
	{
		dAlignSpecX = g_clModelData[nUnit].m_dSensorAlignSpec[0];// MOTOR_PCB_X];
		dAlignSpecY = g_clModelData[nUnit].m_dSensorAlignSpec[1];// MOTOR_PCB_Y];
		dAlignSpecTh = g_clModelData[nUnit].m_dSensorAlignSpec[2];// MOTOR_PCB_TH];
	}
	if ((fabs(dX) > dAlignSpecX) || (fabs(dY) > dAlignSpecY) || (fabs(dTh) > dAlignSpecTh))
	{			
		return 1;//RETRY
	}
	
	return 2;	//SPEC IN
}
//-----------------------------------------------------------------------------
//
//	ALIGN 보정량 Limit Check
//
//-----------------------------------------------------------------------------
int g_CheckAlignLimit(int nUnit, double dX, double dY, double dTh)
{
#if 0
	TCHAR szLog[SIZE_OF_1K];

	if ((fabs(dX) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_X]) || (fabs(dY) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Y]) ||
		(fabs(dTh) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH]))
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[ERROR] PCB부 X,Y,T 보정값(%.03lf, %.03lf, %.03lf)이 보정 Limit(%.03lf, %.03lf, %.03lf)을 초과했습니다."),
			dX, dY, dTh, g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_X], g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Y], g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH]);
		AddLog(szLog, 0, nUnit);

		return 0;
	}


	if ((fabs(dX) > g_clModelData[nUnit].m_dOkLimit[MOTOR_PCB_X]) || (fabs(dY) > g_clModelData[nUnit].m_dOkLimit[MOTOR_PCB_Y]) ||
		(fabs(dTh) > g_clModelData[nUnit].m_dOkLimit[MOTOR_PCB_TH]))
	{
		return 1;
	}
#endif
	return 2;
}
//-----------------------------------------------------------------------------
//
//	nIndex : 0 = 내측, 1 = 외측
//
//-----------------------------------------------------------------------------
//bool g_CalcLaserTilt(int nUnit, int nIndex)
bool g_CalcLaserTilt(int nUnit, double& dTx, double& dTy)
{
	double dLength[4];
	double dAvgTop, dAvgBottom;
	double dAvgLeft, dAvgRight;
	double dHeight, dWidth;
	double dRadian, dTheta;
	int i;

	dTx = 0.0;
	dTy = 0.0;


	for (i = 0; i < 4; i++) 
	{
		dLength[i] = 0.0;
	}
	dAvgTop = 0.0;
	dAvgBottom = 0.0;
	dAvgLeft = 0.0;
	dAvgRight = 0.0;
	dHeight = 0.0;
	dWidth = 0.0;
	dRadian = 0.0;
	dTheta = 0.0;

	// ======================= 계산
	//포인트간 모터 거리
	dLength[0] = abs(g_clTaskWork[nUnit].m_clDpLaserPos[0].y - g_clTaskWork[nUnit].m_clDpLaserPos[3].y);  // LEFT  
	dLength[1] = abs(g_clTaskWork[nUnit].m_clDpLaserPos[0].x - g_clTaskWork[nUnit].m_clDpLaserPos[1].x);  // TOP
	dLength[2] = abs(g_clTaskWork[nUnit].m_clDpLaserPos[1].y - g_clTaskWork[nUnit].m_clDpLaserPos[2].y);  // RIGHT
	dLength[3] = abs(g_clTaskWork[nUnit].m_clDpLaserPos[2].x - g_clTaskWork[nUnit].m_clDpLaserPos[3].x);  // BOTTOM

	// ======================= X,Y 평균( 중심 레이저)
	
	dAvgTop = (g_clTaskWork[nUnit].m_dLaserVal[0] + g_clTaskWork[nUnit].m_dLaserVal[1]) / 2;
	dAvgBottom = (g_clTaskWork[nUnit].m_dLaserVal[2] + g_clTaskWork[nUnit].m_dLaserVal[3]) / 2;
	dAvgLeft = (g_clTaskWork[nUnit].m_dLaserVal[0] + g_clTaskWork[nUnit].m_dLaserVal[3]) / 2; 
	dAvgRight = (g_clTaskWork[nUnit].m_dLaserVal[1] + g_clTaskWork[nUnit].m_dLaserVal[2]) / 2;


	// ======================= 세로 각도 계산 (TX)
	dWidth = dLength[0];                   // left
	dHeight = dAvgBottom - dAvgTop;		//+ - 부호 안맞으면 순서 바꾸기
	dRadian = atan(dHeight / dWidth);
	dTheta = dRadian * 180 / M_PI;

	dTx = -dTheta;
	// ======================= 가로 각도 계산 (TY)
	dWidth = dLength[1];                   // top 
	dHeight = dAvgRight - dAvgLeft;    //+ - 부호 안맞으면 순서 바꾸기
	dRadian = atan(dHeight / dWidth);
	dTheta = dRadian * 180 / M_PI; 
	dTy = dTheta;
	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
int g_CheckTiltLimit(int nUnit, int nType, double dTx, double dTy)
{
	if ((fabs(dTx) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TX]) || (fabs(dTy) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TY])) {
		return 0;
	}
	if ((fabs(dTx) > g_clModelData[nUnit].m_dOkLimit[MOTOR_PCB_TX]) || (fabs(dTy) > g_clModelData[nUnit].m_dOkLimit[MOTOR_PCB_TY])) {
		return 1;	//RETRY
	}

	return 2;//OK
}


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void g_CalcAlignData(int nCh, CDMPoint clDPtFindMark, double dAngle, double& dX, double& dY, double& dT)
{
	double	dRad, dAng = 0;
	double	dRealDistX, dRealDistY;
	double	dRotateX = 0;
	double	dRotateY = 0;
	double	dCosVal, dSinVal;

	CDMPoint	findP;
	CDMPoint	rotP;
	double dBaseX = (double)CAM_SIZE_X / 2.0;
	double dBaseY = (double)CAM_SIZE_Y / 2.0;

	findP.x = clDPtFindMark.x;
	findP.y = clDPtFindMark.y;

	dRad = g_clSysData.m_clCamAngle[nCh].x * M_PI / 180.0;

	dCosVal = cos(dRad);
	dSinVal = sin(dRad);

	rotP.x = (dCosVal * (findP.x - dBaseX)) + (dSinVal * (dBaseY - findP.y));
	dRad = g_clSysData.m_clCamAngle[nCh].y * M_PI / 180.0;

	dCosVal = cos(dRad);
	dSinVal = sin(dRad);

	rotP.y = (dSinVal * (findP.x - dBaseX)) - (dCosVal * (dBaseY - findP.y));

	//double tttx = 0.0215;
	//dRealDistX = (rotP.x * 0.042) + dRotateX;		//0.042
	//dRealDistY = (rotP.y * 0.0371) + dRotateY;			//0.0371
	dRealDistX = (rotP.x * g_clSysData.m_clCamResol[nCh].x) + dRotateX;
	dRealDistY = (rotP.y * g_clSysData.m_clCamResol[nCh].y) + dRotateY; 
	//dRealDistY = (rotP.y * 0.038) + dRotateY;
	dRad = dAngle * M_PI / 180.0;

	dCosVal = cos(dRad);
	dSinVal = sin(dRad);

	dX = dRealDistX;
	dY = dRealDistY;

	if (dAngle > 180)	dT = dAngle - 360;
	else				dT = dAngle;


	
	switch (nCh)
	{// mark align 부호
	case UNIT_AA1:
		dX *= -1;
		dY *= 1;
		dT *= 1;
		break;
	case UNIT_AA2:
		dX *= 1;
		dY *= 1;
		dT *= 1;
		break;
	}
#if 0	//CCD Align
		
	double dShiftX;
	double dShiftY;

	dShiftX = clDPtFindMark.x - (CCD1_CAM_SIZE_X / 2);
	dShiftY = clDPtFindMark.y - (CCD1_CAM_SIZE_Y / 2);

	dShiftX *= g_clModelData[nCh].m_dCcdCellSize / 1000;
	dShiftY *= g_clModelData[nCh].m_dCcdCellSize / 1000;
	
	dX = dShiftX;
	dY = dShiftY;

	if (dAngle > 180) dT = dAngle - 360;
	else
		dT = dAngle;		
#endif
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
double g_CalcTiltX(int nUnit)
{
#if  1
	//+ 자형 차트
	double dTopZPosA = g_clTaskWork[nUnit].m_stSfrInsp.dMaxPos[1];
	double dBottomZPosA = g_clTaskWork[nUnit].m_stSfrInsp.dMaxPos[2];


	double dTopPixelPosA = g_clTaskWork[nUnit].m_stSfrInsp.Sfr_Pos[g_clTaskWork[nUnit].m_stSfrInsp.nMaxIndex[1]][1].y;
	double dBottomPixelPosA = g_clTaskWork[nUnit].m_stSfrInsp.Sfr_Pos[g_clTaskWork[nUnit].m_stSfrInsp.nMaxIndex[2]][2].y;

#else
	
	//X 자형 차트
	double dTopZPosA = (g_clTaskWork[nUnit].m_stSfrInsp.dMaxPos[1] + g_clTaskWork[nUnit].m_stSfrInsp.dMaxPos[2]) / 2;
	double dBottomZPosA = (g_clTaskWork[nUnit].m_stSfrInsp.dMaxPos[3] + g_clTaskWork[nUnit].m_stSfrInsp.dMaxPos[4]) / 2;

	double dTopPixelPosA = (g_clTaskWork[nUnit].m_stSfrInsp.Sfr_Pos[g_clTaskWork[nUnit].m_stSfrInsp.nMaxIndex[1]][1].y + g_clTaskWork[nUnit].m_stSfrInsp.Sfr_Pos[g_clTaskWork[nUnit].m_stSfrInsp.nMaxIndex[2]][2].y) / 2;
	double dBottomPixelPosA = (g_clTaskWork[nUnit].m_stSfrInsp.Sfr_Pos[g_clTaskWork[nUnit].m_stSfrInsp.nMaxIndex[3]][3].y + g_clTaskWork[nUnit].m_stSfrInsp.Sfr_Pos[g_clTaskWork[nUnit].m_stSfrInsp.nMaxIndex[4]][4].y) / 2;

#endif
	TCHAR	szLog[SIZE_OF_1K];

	double dHeightA = dBottomZPosA - dTopZPosA;
	double dWidth_A = (dBottomPixelPosA - dTopPixelPosA) * g_clModelData[nUnit].m_dCcdCellSize / 1000;	/* CCD Cell 분해능*/

	double dTiltRadA = atan(dHeightA / dWidth_A);
	double dTiltDegA = dTiltRadA * 180.0 / M_PI;

	_stprintf_s(szLog, SIZE_OF_1K, _T("[CalcTiltX] dTopZPosA: %lf"), dTopZPosA);
	AddLog(szLog, 0, nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[CalcTiltX] dBottomZPosA: %lf"), dBottomZPosA);
	AddLog(szLog, 0, nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[CalcTiltX] dTopPixelPosA: %lf"), dTopPixelPosA);
	AddLog(szLog, 0, nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[CalcTiltX] dBottomPixelPosA: %lf"), dBottomPixelPosA);
	AddLog(szLog, 0, nUnit);

	//
	_stprintf_s(szLog, SIZE_OF_1K, _T("[CalcTiltX] dHeightA: %lf"), dHeightA);
	AddLog(szLog, 0, nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[CalcTiltX] dWidth_A: %lf"), dWidth_A);
	AddLog(szLog, 0, nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[CalcTiltX] dTiltRadA: %lf"), dTiltRadA);
	AddLog(szLog, 0, nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[CalcTiltX] dTiltDegA: %lf"), dTiltDegA);
	AddLog(szLog, 0, nUnit);
	return dTiltDegA;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
double g_CalcTiltY(int nUnit)
{
#if  1
	//+ 자형 차트
	double dLeftZPosA = g_clTaskWork[nUnit].m_stSfrInsp.dMaxPos[3];
	double dRightZPosA =  g_clTaskWork[nUnit].m_stSfrInsp.dMaxPos[4];

	double dLeftPixelPosA = g_clTaskWork[nUnit].m_stSfrInsp.Sfr_Pos[g_clTaskWork[nUnit].m_stSfrInsp.nMaxIndex[3]][3].x;
	double dRightPixelPosA = g_clTaskWork[nUnit].m_stSfrInsp.Sfr_Pos[g_clTaskWork[nUnit].m_stSfrInsp.nMaxIndex[4]][4].x;
#else
	//X 자형 차트

	double dLeftZPosA = (g_clTaskWork[nUnit].m_stSfrInsp.dMaxPos[1] + g_clTaskWork[nUnit].m_stSfrInsp.dMaxPos[3]) / 2;
	double dRightZPosA = (g_clTaskWork[nUnit].m_stSfrInsp.dMaxPos[2] + g_clTaskWork[nUnit].m_stSfrInsp.dMaxPos[4]) / 2;

	double dLeftPixelPosA = (g_clTaskWork[nUnit].m_stSfrInsp.Sfr_Pos[g_clTaskWork[nUnit].m_stSfrInsp.nMaxIndex[1]][1].x + g_clTaskWork[nUnit].m_stSfrInsp.Sfr_Pos[g_clTaskWork[nUnit].m_stSfrInsp.nMaxIndex[3]][3].x) / 2;
	double dRightPixelPosA = (g_clTaskWork[nUnit].m_stSfrInsp.Sfr_Pos[g_clTaskWork[nUnit].m_stSfrInsp.nMaxIndex[2]][2].x + g_clTaskWork[nUnit].m_stSfrInsp.Sfr_Pos[g_clTaskWork[nUnit].m_stSfrInsp.nMaxIndex[4]][4].x) / 2;

#endif
	
	double dHeightA = dRightZPosA - dLeftZPosA;
	double dWidthA = (dRightPixelPosA - dLeftPixelPosA) * g_clModelData[nUnit].m_dCcdCellSize / 1000;		/* CCD Cell 분해능*/

	double dTiltRadA = atan(dHeightA / dWidthA);
	double dTiltDegA = dTiltRadA * 180.0 / M_PI; 

	TCHAR	szLog[SIZE_OF_1K];

	_stprintf_s(szLog, SIZE_OF_1K, _T("[CalcTiltY] dLeftZPosA: %lf"), dLeftZPosA);
	AddLog(szLog, 0, nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[CalcTiltY] dRightZPosA: %lf"), dRightZPosA);
	AddLog(szLog, 0, nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[CalcTiltY] dLeftPixelPosA: %lf"), dLeftPixelPosA);
	AddLog(szLog, 0, nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[CalcTiltY] dRightPixelPosA: %lf"), dRightPixelPosA);
	AddLog(szLog, 0, nUnit);

	//
	_stprintf_s(szLog, SIZE_OF_1K, _T("[CalcTiltY] dHeightA: %lf"), dHeightA);
	AddLog(szLog, 0, nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[CalcTiltY] dWidthA: %lf"), dWidthA);
	AddLog(szLog, 0, nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[CalcTiltY] dTiltRadA: %lf"), dTiltRadA);
	AddLog(szLog, 0, nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[CalcTiltY] dTiltDegA: %lf"), dTiltDegA);
	AddLog(szLog, 0, nUnit);


	return dTiltDegA;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void g_Shift12to16BitMode(unsigned char* p12bitRaw, unsigned char* p16bitRaw, int nWidth, int nHeight)
{
	int k = 0;
	int n12bitRawSize = nWidth * nHeight * 1.5;
	register int i;

	for(i = 0; i < n12bitRawSize ; i += 3)
	{
		p16bitRaw[k + 1] = (p12bitRaw[i] & 0xF0) >> 4 ;
		p16bitRaw[k + 0] = ((p12bitRaw[i] & 0x0F) << 4 ) + ((p12bitRaw[i + 2] & 0x0F ));
		
		p16bitRaw[k + 3] = (p12bitRaw[i + 1] & 0xF0) >> 4 ;
		p16bitRaw[k + 2] = ((p12bitRaw[i + 1] & 0x0F) << 4 ) +  ((p12bitRaw[i + 2] & 0xF0 ) >> 4);

		k += 4;
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void g_CCCR_Interpolation(unsigned short* pData, int nWidth, int nHeight)
{
	int nNewValue = 0;
	int nStartX = 1;
	int nStartY = 1;
	register int x, y;

	/*if(m_bRcccMoveX == true)
		nStartX = 2;

	if(m_bRcccMoveY == true)
		nStartY = 2;*/

	for (y = nStartY; y < nHeight - 1; y += 2)
	{
		for (x = nStartX; x < nWidth - 1; x += 2)
		{
			/*if(m_bCheckDir == true)
			{
				int absV = abs(pData[(i - 1) * nWidth + (j + 0)] - pData[(i + 1) * nWidth + (j + 0)]);
				int absH = abs(pData[(i + 0) * nWidth + (j - 1)] - pData[(i + 0) * nWidth + (j + 1)]);
				pData[i * nWidth + j] = (absV < absH) ? (pData[(i - 1) * nWidth + (j + 0)] + pData[(i + 1) * nWidth + (j + 0)]) / 2 : (pData[(i + 0) * nWidth + (j - 1)] + pData[(i + 0) * nWidth + (j + 1)]) / 2;
			}
			else
			{*/
				nNewValue =  pData[(y - 1) * nWidth + (x + 0)] + pData[(y + 1) * nWidth + (x + 0)] + pData[(y + 0) * nWidth + (x - 1)]  + pData[(y + 0) * nWidth + (x + 1)] ;
				
				nNewValue = nNewValue / 4;
				pData[y * nWidth + x] = (unsigned short) nNewValue;
			//}			
		}
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void g_Shift16to12BitMode(unsigned char* pImage, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight)
{	
	unsigned int nScrWidth, nDestWidth;
	unsigned char *pcDest;
	register unsigned int i, j, k;

	nDestWidth = nWidth * 3 / 2;
	nScrWidth = nWidth * 2;

	pcDest = (unsigned char *) pDest;

	for(i = 0; i < nHeight; i++)
	{
		for(j = 0, k = 0; j < nDestWidth; j += 6, k += 8)
		{
			pcDest[j + 0] = ((pImage[k] & 0xF0) >> 4 ) +  ((pImage[k + 1]  & 0x0F ) << 4) ;
			pcDest[j + 1] = ((pImage[k + 2] & 0xF0) >> 4 ) +  ((pImage[k + 3]  & 0x0F ) << 4) ;
			pcDest[j + 2] = (pImage[k] & 0x0F) + ((pImage[k + 2]  & 0x0F ) << 4) ;

			pcDest[j + 3] = ((pImage[k + 4] & 0xF0) >> 4 ) +  ((pImage[k + 5]  & 0x0F ) << 4) ;
			pcDest[j + 4] = ((pImage[k + 6] & 0xF0) >> 4 ) +  ((pImage[k + 7]  & 0x0F ) << 4) ;
			pcDest[j + 5] = (pImage[k + 4] & 0x0F) + ((pImage[k + 6]  & 0x0F ) << 4) ;
		}

		pcDest += nDestWidth;
		pImage += nScrWidth;
	}	
}
//void CMandoInspLog::func_LogSave_Stain(CString name , CString title , CString data)//---Stain 검사시 로그  로그대대
//-----------------------------------------------------------------------------
//
//	SFR 로그 저장
//
//-----------------------------------------------------------------------------
//bool g_SaveLGITLog(int nUnit, CString lgitName, CString lgitTitle, CString lgitData, CString lgitVer)
bool g_SaveLGITLog(int nUnit, TCHAR *lgitName, string lgitTitle, string lgitData, string lgitVer)
{
    TCHAR szPath[SIZE_OF_1K];
    TCHAR szFilePath[SIZE_OF_1K];
    SYSTEMTIME stSysTime;
    CFileFind clFinder;
    CString sFileMode = _T("");
    CFile clFile;
    FILE* fp;

	TCHAR szTempLotid[SIZE_OF_1K];
	//CString cnamePath;
	//cnamePath.Format("%s", g_clTaskWork[nUnit].m_szChipID);
	//cnamePath.Replace(":", ";");

	_stprintf_s(szTempLotid, SIZE_OF_1K, _T("%s"), g_clTaskWork[nUnit].m_szChipID);



    ::GetLocalTime(&stSysTime);

    if (_tcslen(szTempLotid) <= 0)
        _tcscpy_s(szTempLotid, SIZE_OF_1K, _T("(NULL)"));

    if (_tcslen(szTempLotid) <= 0)
        _tcscpy_s(szTempLotid, SIZE_OF_1K, _T("(NULL)"));

    if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
        CreateDirectory(BASE_LOG_PATH, NULL);
    //
    _stprintf_s(szPath, SIZE_OF_1K, _T("%s"), BASE_LOG_PATH);
    if (clFinder.FindFile(szPath) == FALSE)
        CreateDirectory(szPath, NULL);

    _stprintf_s(szPath, SIZE_OF_1K, _T("%s\\ACMIS"), BASE_LOG_PATH);
    if (clFinder.FindFile(szPath) == FALSE)
        CreateDirectory(szPath, NULL);

    _stprintf_s(szPath, SIZE_OF_1K, _T("%s\\ACMIS\\%04d%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth);
    if (clFinder.FindFile(szPath) == FALSE)
        CreateDirectory(szPath, NULL);

    _stprintf_s(szPath, SIZE_OF_1K, _T("%s\\ACMIS\\%04d%02d\\%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
    if (clFinder.FindFile(szPath) == FALSE)
        CreateDirectory(szPath, NULL);

	//.c_str()
//#if (____MACHINE_NAME == MODEL_FRONT_100)		//ok
//	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%s_%s_%04d%02d%02d_%02d%02d%02d_100.csv"), szPath, lgitName, szTempLotid, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);
//
//#else
//	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%s_%s_%04d%02d%02d_%02d%02d%02d_150.csv"), szPath, lgitName, szTempLotid, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);
//
//#endif
	if (ModelList.m_szCurrentModel == SHM_FRONT_100_MODEL)
	{
		_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%s_%s_%04d%02d%02d_%02d%02d%02d_100.csv"), szPath, lgitName, szTempLotid, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);
	}
	else
	{
		_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%s_%s_%04d%02d%02d_%02d%02d%02d_150.csv"), szPath, lgitName, szTempLotid, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);
	}
    if (clFinder.FindFile(szFilePath) == TRUE)
    {
        if (clFile.Open(szFilePath, CFile::modeRead) == FALSE)
        {
            AddLog(_T("파일이 사용 중 입니다."), 1, nUnit);
            return false;
        }
        else
        {
            clFile.Close();
        }
    }
#ifdef _UNICODE
    sFileMode = _T("w,ccs=UTF-8");
#else
    sFileMode = _T("w");//_T("w");
#endif

    // 파일이 없으면 헤더를 만든다.
    if (clFinder.FindFile(szFilePath) == FALSE)
    {
        _tfopen_s(&fp, szFilePath, sFileMode);
        if (fp != NULL)
        {
            _ftprintf_s(fp, _T("항목,%s,"), lgitTitle.c_str());//(LPTSTR)(LPCTSTR)lgitTitle);
            _ftprintf_s(fp, "\n");
        }
        fclose(fp);
    }

#ifdef _UNICODE
    sFileMode = _T("a,ccs=UTF-8");
#else
    sFileMode = _T("a");
#endif

    _tfopen_s(&fp, szFilePath, sFileMode);
    if (fp != NULL)
    {
        _ftprintf_s(fp, _T("%s,%s"), lgitName, lgitData.c_str());//(LPTSTR)(LPCTSTR)lgitName,(LPTSTR)(LPCTSTR)lgitData);
        _ftprintf_s(fp, "\n");
        fclose(fp);
    }

	sFileMode.Empty();

    return true;
}
//-----------------------------------------------------------------------------
//
//	SFR 로그 저장
//
//-----------------------------------------------------------------------------
bool g_SaveSfrLog(int nUnit, int nMode)
{

	return true;
}

//-----------------------------------------------------------------------------
//
//	SFR Summary 로그 저장
//
//-----------------------------------------------------------------------------
bool g_SaveSfrSumLog(int nUnit)
{
	
	return true;
}

double getRadianFromAng(double Angle)
{
	return (PI / 180) * Angle;
}

void fileDelete(CString delFolder)
{
	BOOL bContinue = FALSE;
	CFileFind finder;
	BOOL IsFind;

	if (delFolder.Right(1) != _T("\\"))
		delFolder += _T("\\");

	delFolder += _T("*.*");

	bContinue = finder.FindFile(delFolder);
	if (bContinue == FALSE)
	{
		finder.Close();
		return;
	}
	CString sDelPath;
	while (bContinue)
	{
		bContinue = finder.FindNextFile();
		if (finder.IsDots()) // Ignore this item.
		{
			continue;
		}
		else if (finder.IsDirectory()) // Delete all sub item.
		{
			sDelPath = finder.GetFilePath();
			fileDelete(sDelPath);
			::RemoveDirectory((LPCTSTR)sDelPath);
		}
		else // Delete file.
		{
			sDelPath = finder.GetFilePath();
			::DeleteFile((LPCTSTR)sDelPath);
		}
		Sleep(15);
	}

	delFolder = delFolder.Left(delFolder.ReverseFind('\\'));
	::RemoveDirectory((LPCTSTR)delFolder);
	finder.Close();
	sDelPath.Empty();
}

void RawDataDelete(int nUnit)
{
	TCHAR	szLog[SIZE_OF_1K];

	_stprintf_s(szLog, SIZE_OF_1K, _T("Raw Data Delete"));
	AddLog(szLog, 0, nUnit);

	SYSTEMTIME SystemTime;
	::GetLocalTime(&SystemTime);

	CTime nextDay(SystemTime); //Local Time을 CTime으로 변환
	int nDelDay = g_clSysData.m_nFileDeleteDay;
	if (nDelDay < 1)
	{
		nDelDay = 1;
	}
	nextDay -= CTimeSpan(nDelDay, 0, 0, 0); //Ctime + 하루//CTimeSpan(SystemTime.wDay, 0, 0, 0); //Ctime + 하루
	SystemTime.wYear = (WORD)nextDay.GetYear();

	SystemTime.wMonth = (WORD)nextDay.GetMonth();

	SystemTime.wDay = (WORD)nextDay.GetDay();

	CString FolderName;
	FolderName.Format("%s\\IMAGE\\%04d%02d\\%02d", BASE_LOG_PATH, SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay);
	_stprintf_s(szLog, SIZE_OF_1K, _T("Delete:%s"), FolderName);
	AddLog(szLog, 0, nUnit);

	fileDelete(FolderName);
	FolderName.Empty();
}
