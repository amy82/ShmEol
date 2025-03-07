#include "stdafx.h"
#include "Data.h"
CModelType::CModelType()
{
	//m_nModelIndex = MODERATE_MODEL;		//NARROW

	//_tcscpy_s(m_szModelTypeName, SIZE_OF_100BYTE, _T("SHM"));
}

CModelType::~CModelType()
{
}

///////////////////////////////////////////////////////////////////////////////
//
//	ModelList
//

//-----------------------------------------------------------------------------
//
//	생성자
//
//-----------------------------------------------------------------------------
CModelList::CModelList()
{
	m_clModelList.RemoveAll();

	m_nTotalCount = 0;
	m_nCurrentNo = 0;
}

//-----------------------------------------------------------------------------
//
//	소멸자
//
//-----------------------------------------------------------------------------
CModelList::~CModelList()
{
	m_clModelList.RemoveAll();
}

//-----------------------------------------------------------------------------
//
//	Model List 로드
//
//-----------------------------------------------------------------------------
void CModelList::ModelListSave()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];
	CModelInfo clModelInfo;
	int i = 0;

	CFileFind clFinder;

	if (clFinder.FindFile(BASE_SECSGEM_PATH) == FALSE)
	{
		CreateDirectory(BASE_SECSGEM_PATH, NULL);
	}
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\ModelList.ini"), BASE_SECSGEM_PATH);// BASE_DATA_PATH);

	m_nTotalCount = m_clModelList.GetCount();
	if (m_nTotalCount > g_MaxModelCount)
	{
		m_nTotalCount = g_MaxModelCount;
	}
	if (m_nCurrentNo < 1)
	{
		m_nCurrentNo = 1;
	}
	if (m_nCurrentNo  > m_nTotalCount)
	{
		m_nCurrentNo = m_nTotalCount;
	}
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nTotalCount);
	WritePrivateProfileString(_T("ModelList"), _T("Total"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nCurrentNo);
	WritePrivateProfileString(_T("ModelList"), _T("ModelNo"), szData, szPath);


	
	for (i = 0; i < g_MaxModelCount; i++)		//MAX_MODEL_COUNT
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("Model%02d"), i + 1);
		if (i < m_nTotalCount)
		{
			_stprintf_s(szIniBuff, SIZE_OF_1K, _T("%s"), m_clModelList[i].m_szName);
		}
		else
		{
			_stprintf_s(szIniBuff, SIZE_OF_1K, _T(""));
		}
		WritePrivateProfileString(_T("ModelList"), szIniIndex, szIniBuff, szPath);
	}

}


//-----------------------------------------------------------------------------
//
//	Model List 로드
//
//-----------------------------------------------------------------------------
void CModelList::ModelListLoad()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CModelInfo clModelInfo;
	int i = 0;

	m_clModelList.RemoveAll();
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\ModelList.ini"), BASE_SECSGEM_PATH);		// BASE_DATA_PATH);

	m_nTotalCount = GetPrivateProfileInt(_T("ModelList"), _T("Total"), 0, szPath);
	m_nCurrentNo = GetPrivateProfileInt(_T("ModelList"), _T("ModelNo"), 0, szPath);
	
	for (i = 0; i < g_MaxModelCount; i++)		//MAX_MODEL_COUNT
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("Model%02d"), i + 1);
		GetPrivateProfileString(_T("ModelList"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		if (_tcslen(szIniBuff) > 0)
		{
			clModelInfo.m_nNo = i + 1;
			_tcscpy_s(clModelInfo.m_szName, SIZE_OF_100BYTE, szIniBuff);
			m_clModelList.Add(clModelInfo);
		}
	}
	int mCount = m_clModelList.GetCount();

	if ((mCount > 0) && (m_nCurrentNo > 0))
	{
		_tcscpy_s(m_szCurrentModel, SIZE_OF_100BYTE, m_clModelList[m_nCurrentNo - 1].m_szName);
	}
	else 
	{
		m_nCurrentNo = 1;
		_tcscpy_s(m_szCurrentModel, SIZE_OF_100BYTE, SHM_FRONT_100_MODEL);


		_tcscpy_s(clModelInfo.m_szName, SIZE_OF_100BYTE, SHM_FRONT_100_MODEL);	// TODO: 모델 없을 경우 하나 추가하기
		clModelInfo.m_nNo = 1;
		m_clModelList.Add(clModelInfo);

		_tcscpy_s(clModelInfo.m_szName, SIZE_OF_100BYTE, SHM_OHC_150_MODEL);	// TODO: 모델 없을 경우 하나 추가하기
		clModelInfo.m_nNo = 2;
		m_clModelList.Add(clModelInfo);

		m_nTotalCount = 2;
		ModelListSave();
	}

	//if (ModelList.m_szCurrentModel == SHM_FRONT_100_MODEL)
	if (_tcscmp(ModelList.m_szCurrentModel, SHM_FRONT_100_MODEL) == 0)
	{
		VEC_FOV_COUNT = 12;
		VEC_FOV_FIND_COUNT = 16;

		_stprintf_s(BASE_PATH, SIZE_OF_1K, _T("D:\\EVMS\\SHM_EOL_FRONT_100"));
		_stprintf_s(BASE_DATA_PATH, SIZE_OF_1K, _T("D:\\EVMS\\SHM_EOL_FRONT_100\\Data"));
		_stprintf_s(BASE_ALARM_PATH, SIZE_OF_1K, _T("D:\\EVMS\\SHM_EOL_FRONT_100\\Alarm"));
		_stprintf_s(MIU_DIR, SIZE_OF_1K, _T("D:\\EVMS\\SHM_EOL_FRONT_100\\Initialize"));
		_stprintf_s(FW_DIR, SIZE_OF_1K, _T("D:\\EVMS\\SHM_EOL_FRONT_100\\Firmware"));

		g_pCarAABonderDlg->MainTitleSet(1);
	}
	else
	{
		VEC_FOV_COUNT = 10;
		VEC_FOV_FIND_COUNT = 14;

		_stprintf_s(BASE_PATH, SIZE_OF_1K, _T("D:\\EVMS\\SHM_EOL_OHC_150"));
		_stprintf_s(BASE_DATA_PATH, SIZE_OF_1K, _T("D:\\EVMS\\SHM_EOL_OHC_150\\Data"));
		_stprintf_s(BASE_ALARM_PATH, SIZE_OF_1K, _T("D:\\EVMS\\SHM_EOL_OHC_150\\Alarm"));
		_stprintf_s(MIU_DIR, SIZE_OF_1K, _T("D:\\EVMS\\SHM_EOL_OHC_150\\Initialize"));
		_stprintf_s(FW_DIR, SIZE_OF_1K, _T("D:\\EVMS\\SHM_EOL_OHC_150\\Firmware"));

		g_pCarAABonderDlg->MainTitleSet(2);
	}
}

int CModelList::iniRecipeListLoad()
{
	TCHAR szPath[SIZE_OF_1K];
	CString folderPath;
	folderPath.Format(_T("%s"), BASE_RECIPE_PATH);

	CFileFind finder;
	CString searchPattern = folderPath + _T("\\*.ini");//_T("\\*.xml");

	BOOL bWorking = finder.FindFile(searchPattern);

	m_vRecipeVec.clear();
	int cnt = 0;
	while (bWorking) 
	{
		bWorking = finder.FindNextFile();

		if (!finder.IsDots() && !finder.IsDirectory()) 
		{
			//CString fileName = finder.GetFileName();	//.xml 포함
			CString fileName = finder.GetFileTitle();
			m_vRecipeVec.push_back(fileName.GetString());
		}

		cnt++;

		if (cnt > 200)
		{
			break;
		}
	}
	finder.Close();

	folderPath.Empty();
	searchPattern.Empty();

	int nSize = m_vRecipeVec.size();
	return nSize;
}


void CModelList::xmlRecipeCreate(CString copyPPid, CString createPPid)
{
	TCHAR szPath[SIZE_OF_1K];
	CString folderPath;
	folderPath.Format(_T("%s"), BASE_RECIPE_PATH);

	CFileFind finder;
	CString searchPattern = folderPath + _T("\\*.ini");//_T("\\*.xml");
	CString createFileFullPath;// = finder.GetFilePath();	//.xml 포함

	createFileFullPath.Format(_T("%s\\%s.ini"), folderPath, createPPid);//createFileFullPath.Format(_T("%s\\%s.xml"), folderPath, createPPid);

	BOOL bWorking = finder.FindFile(searchPattern);

	//m_vRecipeVec.clear();		//왜?
	int cnt = 0;
	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		if (!finder.IsDots() && !finder.IsDirectory())
		{
			//
			CString fileName = finder.GetFileTitle();
			if (fileName == copyPPid)
			{
				CString scrFilePath = finder.GetFilePath();	//.xml 포함

				CopyFile(scrFilePath, createFileFullPath, TRUE);


				TCHAR szLog[SIZE_OF_1K];
				_stprintf_s(szLog, SIZE_OF_1K, _T("[INFO]%s-Create ok"), createFileFullPath);
				AddLog(szLog, 0, 0);
				break;
			}
		}

		cnt++;

		if (cnt > 200)
		{
			break;
		}
	}
	finder.Close();
}
void CModelList::xmlRecipeDelete(CString PPid)
{
	TCHAR szPath[SIZE_OF_1K];
	CString folderPath;
	folderPath.Format(_T("%s"), BASE_RECIPE_PATH);

	CFileFind finder;
	CString searchPattern = folderPath + _T("\\*.ini");//_T("\\*.xml");

	BOOL bWorking = finder.FindFile(searchPattern);

	//m_vRecipeVec.clear();		//왜?
	int cnt = 0;
	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		if (!finder.IsDots() && !finder.IsDirectory())
		{
			//
			CString fileName = finder.GetFileTitle();
			if (fileName == PPid)
			{
				//CString fileName = finder.GetFileName();	//.xml 포함
				CString fileFullPath = finder.GetFilePath();	//.xml 포함
																//CFile::Remove(fileFullPath);
				BOOL bRtn = DeleteFileA(fileFullPath);
				TCHAR szLog[SIZE_OF_1K];
				if (bRtn)
				{
					int cnt = m_vRecipeVec.size();
					for (int i = 0; i < cnt; ++i)
					{
						if (m_vRecipeVec[i].c_str() == PPid)  // CModelInfo의 == 연산자가 정의되어 있어야 합니다.
						{
							m_vRecipeVec.erase(m_vRecipeVec.begin() + i);
							break;
						}
					}

					_stprintf_s(szLog, SIZE_OF_1K, _T("[INFO]%s-Delete ok"), fileFullPath);
					AddLog(szLog, 0, 0);
				}
				else
				{
					_stprintf_s(szLog, SIZE_OF_1K, _T("[INFO]%s-Delete fail"), fileFullPath);
					AddLog(szLog, 0, 0);
				}
			}
		}

		cnt++;

		if (cnt > 200)
		{
			break;
		}
	}
	finder.Close();
}
//-----------------------------------------------------------------------------
//
//	
//
//-----------------------------------------------------------------------------
void CModelList::RecipeModelLoad()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];


	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\RecipelList.ini"), BASE_SECSGEM_PATH);


//#if (____MACHINE_NAME ==  MODEL_FRONT_100)			//ok
//	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("FRONT"));
//#else
//	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("OHC"));
//#endif

	if (ModelList.m_szCurrentModel == SHM_FRONT_100_MODEL)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("FRONT"));
	}
	else
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("OHC"));
	}
	


	GetPrivateProfileString(_T("RECIPE_MODEL"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	if (_tcslen(szIniBuff) > 0)
	{
		g_clMesCommunication[0].m_sMesPPID.Format(_T("%s"), szIniBuff);
		g_clMesCommunication[0].m_sRecipeId.Format(_T("%s"), szIniBuff);		//RecipeModelLoad ini 파일 로드
	}

	
}
void CModelList::RecipeModelSave()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];
	int i = 0;
	
	CFileFind clFinder;
	
	if (clFinder.FindFile(BASE_SECSGEM_PATH) == FALSE)
	{
		CreateDirectory(BASE_SECSGEM_PATH, NULL);
	}

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\RecipelList.ini"), BASE_SECSGEM_PATH);
	
//
//#if (____MACHINE_NAME ==  MODEL_FRONT_100)			//ok
//	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("FRONT"));
//#else
//	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("OHC"));
//#endif

	if (ModelList.m_szCurrentModel == SHM_FRONT_100_MODEL)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("FRONT"));
	}
	else
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("OHC"));
	}


	_stprintf_s(szIniBuff, SIZE_OF_1K, _T("%s"), g_clMesCommunication[0].m_sMesPPID);
	WritePrivateProfileString(_T("RECIPE_MODEL"), szIniIndex, szIniBuff, szPath);
}

//-----------------------------------------------------------------------------
//
//	RECIPE List 로드
//
//-----------------------------------------------------------------------------
void CModelList::RecipeListLoad()
{

}
void CModelList::RecipeListSave()
{

}

bool CModelList::RecipeModelDel(CString PPid)
{
	int i = 0;
	TCHAR szLog[SIZE_OF_1K];

	if (PPid == g_clMesCommunication[0].m_sMesPPID)
	{
		//현재 사용중인 RECIPE 입니다.
		_stprintf_s(szLog, SIZE_OF_1K, _T("[INFO]%s - 현재 사용중인 RECIPE 입니다."), PPid);
		AddLog(szLog, 0, 0);
		return false;
	}


	int cnt = m_vRecipeVec.size();
	for (int i = 0; i < cnt; ++i)
	{
		if (m_vRecipeVec[i].c_str() == PPid)  // CModelInfo의 == 연산자가 정의되어 있어야 합니다.
		{
			m_vRecipeVec.erase(m_vRecipeVec.begin() + i);
			break;
		}
	}

	return true;
}
//-----------------------------------------------------------------------------
//
//	MODEL TYPE 로드
//
//-----------------------------------------------------------------------------
void CModelType::mTLoad()
{
	//TCHAR szPath[SIZE_OF_1K];
	//TCHAR szIniIndex[SIZE_OF_100BYTE];
	//TCHAR szIniBuff[SIZE_OF_1K];
	//CString sToken = _T("");
	//int i, j, k;

	//_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\ModelType.ini"), BASE_DATA_PATH);

	//m_nModelIndex = GetPrivateProfileInt(_T("ModelType"), _T("Model"), 0, szPath);

	//// CURRENT MODEL
	//GetPrivateProfileString(_T("CURRENT_MODEL"), _T("Name"), _T(""), m_szModelTypeName, sizeof(m_szModelName), szPath);

	//if (m_nModelIndex == MODERATE_MODEL)	//NARROW_MODEL
	//{
	//	g_pCarAABonderDlg->m_clColorStaticPcbType[0].SetWindowText(_T("MODEL #1: MODERATE"));
	//	g_pCarAABonderDlg->m_clColorStaticPcbType[1].SetWindowText(_T("MODEL #2: MODERATE"));
	//}
	//else
	//{
	//	g_pCarAABonderDlg->m_clColorStaticPcbType[0].SetWindowText(_T("MODEL #1: NARROW"));
	//	g_pCarAABonderDlg->m_clColorStaticPcbType[1].SetWindowText(_T("MODEL #2: NARROW"));
	//}

}


//-----------------------------------------------------------------------------
//
//	MODEL TYPE 저장
//
//-----------------------------------------------------------------------------
void CModelType::mTSave()
{
	//TCHAR szPath[SIZE_OF_1K];
	//TCHAR szData[SIZE_OF_1K];
	//TCHAR szIniIndex[SIZE_OF_100BYTE];
	//TCHAR szIniBuff[SIZE_OF_1K];
	//CString sToken = _T("");
	//int i, j;
	//CFileFind clFinder;
	//if (clFinder.FindFile(BASE_DATA_PATH) == FALSE)
	//{
	//	CreateDirectory(BASE_DATA_PATH, NULL);
	//}

	//_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\ModelType.ini"), BASE_DATA_PATH);


	//_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nModelIndex);
	//WritePrivateProfileString(_T("ModelType"), _T("Model"), szData, szPath);

	//// CURRENT MODEL
	//WritePrivateProfileString(_T("CURRENT_MODEL"), _T("Name"), m_szModelTypeName, szPath);
}


//-----------------------------------------------------------------------------
//
//	MODEL TYPE 파일 백업
//
//-----------------------------------------------------------------------------
void CModelType::CopyBackup()
{
	/*TCHAR szBackupPath[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];
	SYSTEMTIME stSysTime;
	CFileFind clFinder;

	GetLocalTime(&stSysTime);

	if (clFinder.FindFile(ROOT_PATH) == FALSE)
		CreateDirectory(ROOT_PATH, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup"), ROOT_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup\\%04d%02d"), ROOT_PATH, stSysTime.wYear, stSysTime.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup\\%04d%02d\\%02d"), ROOT_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szBackupPath, SIZE_OF_1K, _T("%s\\Backup\\%04d%02d\\%02d\\SystemData_%02d_%02d_%02d_%03d.ini"),
		ROOT_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond, stSysTime.wMilliseconds);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\ModelType.ini"), ROOT_PATH);

	CopyFile(szPath, szBackupPath, TRUE);*/
}


CSystemData::CSystemData()
{
	int i, j;
	m_nSysNo = 0;
	m_nUnitNo = 0;
	for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
	{
		m_dSfrBasicOffset[i] = 0.0;
		m_dSfrOutOffset[i] = 0.0;
	}

	m_dOcOffset[0] = 0.0;
	m_dOcOffset[1] = 0.0;

	_tcscpy_s(m_szPassword, SIZE_OF_100BYTE, _T("1111"));

	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		for (j = 0; j < MAX_MOTOR_COUNT; j++)
		{
			m_dMotorSpeed[i][j] = 0.0;
			m_dMotorAccTime[i][j] = 0.0;
			m_dMotorDecTime[i][j] = 0.0;
			m_dMotorResol[i][j] = 0.0;
			m_dOrgDataset[i][j] = 0.0;
		}
	} 

	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		m_clCamResol[i].x = m_clCamResol[i].y = 0.0;
		m_clCamAngle[i].x = m_clCamAngle[i].y = 0.0;
	}

	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		m_dLimitSFRBalance[i] = 0.01;
		m_clOCSpec[i].x = m_clOCSpec[i].y = 0.02;
		m_dOCSpecTh[i] = 0.02;

		m_nTopLightPort[i] = 0;
		m_nAlign_Oc_Port[i] = 0;
		m_nEzi_Port[i] = 0;
		m_nOC_IRPort[i] = 0;
		m_nLaserPort[i] = 0;
		m_nBcrPort[i] = 0;
		m_nUvPort[i] = 0;
		m_nLeftLightPort[i] = 0;
		m_nRightLightPort[i] = 0;
	}
	
	memset(m_szMesPath, 0x00, sizeof(m_szMesPath));

	_tcscpy_s(m_szFactoryCd, SIZE_OF_100BYTE, _T("FACTORY"));
	m_nMaxPinCount = 0;
}


CSystemData::~CSystemData()
{
}

//-----------------------------------------------------------------------------
//
//	시스템 데이터 로드
//
//-----------------------------------------------------------------------------
void CSystemData::OcOffsetLoad()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Foffset.ini"), BASE_DATA_PATH);

	//곱하기
	GetPrivateProfileString(_T("OC"), _T("xoffset"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	if (_tcslen(szIniBuff) > 0)
	{
		m_dOcOffset[0] = _ttof(szIniBuff);
	}

	GetPrivateProfileString(_T("OC"), _T("yoffset"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	if (_tcslen(szIniBuff) > 0)
	{
		m_dOcOffset[1] = _ttof(szIniBuff);
	}
	////더하기
	//GetPrivateProfileString(_T("CENTER"), _T("xpoffset"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	//if (_tcslen(szIniBuff) > 0)
	//{
	//	m_dOcOffset[2] = _ttof(szIniBuff);
	//}

	//GetPrivateProfileString(_T("CENTER"), _T("ypoffset"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	//if (_tcslen(szIniBuff) > 0)
	//{
	//	m_dOcOffset[3] = _ttof(szIniBuff);
	//}


	sToken.Format(_T("Yuv Offset [%.2lf/%.2lf]"), m_dOcOffset[0], m_dOcOffset[1]);

	AddLog(sToken, 0, UNIT_AA1);
}


//-----------------------------------------------------------------------------
//
//	시스템 데이터 로드
//
//-----------------------------------------------------------------------------
void CSystemData::SfrOffsetLoad()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Moffset.ini"), BASE_DATA_PATH);

	
	for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("BASIC%d"), i);
		GetPrivateProfileString(_T("BASIC"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		if (_tcslen(szIniBuff) > 0)
		{
			m_dSfrBasicOffset[i] = _ttof(szIniBuff);
		}

		//
		//
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("OUT%d"), i);
		GetPrivateProfileString(_T("SPECOUT"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		if (_tcslen(szIniBuff) > 0)
		{
			m_dSfrOutOffset[i] = _ttof(szIniBuff);
		}
	}

	sToken.Format(_T("BASIC [%.3lf/%.3lf/%.3lf/%.3lf/%.3lf/%.3lf/%.3lf/%.3lf/%.3lf]"),
		m_dSfrBasicOffset[0], m_dSfrBasicOffset[1], m_dSfrBasicOffset[2], m_dSfrBasicOffset[3], m_dSfrBasicOffset[4],
		m_dSfrBasicOffset[5], m_dSfrBasicOffset[6], m_dSfrBasicOffset[7], m_dSfrBasicOffset[8]);

	AddLog(sToken, 0, UNIT_AA1);

	sToken.Format(_T("OUT [%.3lf/%.3lf/%.3lf/%.3lf/%.3lf/%.3lf/%.3lf/%.3lf/%.3lf]"),
		m_dSfrOutOffset[0], m_dSfrOutOffset[1], m_dSfrOutOffset[2], m_dSfrOutOffset[3], m_dSfrOutOffset[4],
		m_dSfrOutOffset[5], m_dSfrOutOffset[6], m_dSfrOutOffset[7], m_dSfrOutOffset[8]);

	AddLog(sToken, 0, UNIT_AA1);
	
	//m_dSfrOffset

	return;
}

//-----------------------------------------------------------------------------
//
//	공용 데이터 로드
//
//-----------------------------------------------------------------------------
void CSystemData::commonDataLoad()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i, j, k;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\CommonData.ini"), BASE_COMMON_PATH);


	m_nMaxPinCount = GetPrivateProfileInt(_T("MAX_PIN_COUNT"), _T("Count"), 0, szPath);
}

//-----------------------------------------------------------------------------
//
//	공용 데이터 저장
//
//-----------------------------------------------------------------------------
void CSystemData::commonDataSave()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i, j;
	CFileFind clFinder;
	if (clFinder.FindFile(BASE_COMMON_PATH) == FALSE)
	{
		CreateDirectory(BASE_COMMON_PATH, NULL);
	}

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\CommonData.ini"), BASE_COMMON_PATH);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nMaxPinCount);
	WritePrivateProfileString(_T("MAX_PIN_COUNT"), _T("Count"), szData, szPath);
}

//-----------------------------------------------------------------------------
//
//	시스템 데이터 로드
//
//-----------------------------------------------------------------------------
void CSystemData::sDLoad()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i, j, k;
	
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\SystemData.ini"), BASE_DATA_PATH);
	// SYSTEM NO
	m_nSysNo = GetPrivateProfileInt(_T("System"), _T("No"), 0, szPath);
	// Unit No
	m_nUnitNo = GetPrivateProfileInt(_T("System"), _T("Unit"), 0, szPath);

	// Motor
	for(i = 0; i < MAX_UNIT_COUNT; i++)
	{
		for (j = 0; j < MAX_MOTOR_COUNT; j++)
		{
			if(i == 0)		GetPrivateProfileString(_T("MotorPara1"), MOTOR_NAME[j], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
			else			GetPrivateProfileString(_T("MotorPara2"), MOTOR_NAME[j], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
			
			for (k = 0; k < 5; k++)
			{
				AfxExtractSubString(sToken, szIniBuff, k, _T('/'));

				switch (k)
				{
				case 0:		m_dMotorSpeed[i][j] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				case 1:		m_dMotorAccTime[i][j] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				case 2:		m_dMotorDecTime[i][j] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				case 3:		m_dMotorResol[i][j] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				case 4:		m_dOrgDataset[i][j] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				}
			}
		}
	}

	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		if (i == 0)
		{
			// 코너 SFR 편차 LIMIT
			GetPrivateProfileString(_T("SFR_LIMIT1"), _T("CornerDeviation"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
			m_dLimitSFRBalance[i] = _ttof(szIniBuff);

			// OC SPEC X,Y,T
			GetPrivateProfileString(_T("OC_SPEC1"), _T("XYT"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
			for (j = 0; j < 3; j++)
			{
				AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
				switch (j)
				{
				case 0:		m_clOCSpec[i].x = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				case 1:		m_clOCSpec[i].y = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				case 2:		m_dOCSpecTh[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				}
			}
		}
		else
		{
			// 코너 SFR 편차 LIMIT
			GetPrivateProfileString(_T("SFR_LIMIT2"), _T("CornerDeviation"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
			m_dLimitSFRBalance[i] = _ttof(szIniBuff);

			// OC SPEC X,Y,T
			GetPrivateProfileString(_T("OC_SPEC2"), _T("XYT"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
			for (j = 0; j < 3; j++)
			{
				AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
				switch (j)
				{
				case 0:		m_clOCSpec[i].x = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				case 1:		m_clOCSpec[i].y = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				case 2:		m_dOCSpecTh[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				}
			}
		}
	}

	// MES IP
	GetPrivateProfileString(_T("MES"), _T("Ip"), _T(""), m_szMesIp, sizeof(m_szMesIp), szPath);
	// MES Port
	m_nMesPort = GetPrivateProfileInt(_T("MES"), _T("Port"), 0, szPath);
	// MES FATORY CD
	GetPrivateProfileString(_T("MES"), _T("FactoryCd"), _T(""), m_szFactoryCd, sizeof(m_szFactoryCd), szPath);
	// MES LOG DATA 저장 경로
	GetPrivateProfileString(_T("MES"), _T("Path"), _T(""), m_szMesPath, sizeof(m_szMesPath), szPath);

	// Serial Port
	GetPrivateProfileString(_T("SERIAL"), _T("PortNum"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (j = 0; j < 18; j++)
	{
		AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
		switch (j)
		{
		case 0:		m_nOC_IRPort[0] = _ttoi((TCHAR*)(LPCTSTR)sToken);			break;
		case 1:		m_nOC_IRPort[1] = _ttoi((TCHAR*)(LPCTSTR)sToken);			break;
		case 2:		m_nTopLightPort[0] = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
		case 3:		m_nTopLightPort[1] = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
		case 4:		m_nEzi_Port[0] = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
		case 5:		m_nEzi_Port[1] = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
		case 6:		m_nLaserPort[0] = _ttoi((TCHAR*)(LPCTSTR)sToken);			break;
		case 7:		m_nLaserPort[1] = _ttoi((TCHAR*)(LPCTSTR)sToken);			break;
		case 8:		m_nBcrPort[0] = _ttoi((TCHAR*)(LPCTSTR)sToken);				break;
		case 9:		m_nBcrPort[1] = _ttoi((TCHAR*)(LPCTSTR)sToken);				break;
		case 10:	m_nUvPort[0] = _ttoi((TCHAR*)(LPCTSTR)sToken);				break;
		case 11:	m_nUvPort[1] = _ttoi((TCHAR*)(LPCTSTR)sToken);				break;
		case 12:	m_nAlign_Oc_Port[0] = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
		case 13:	m_nAlign_Oc_Port[1] = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
		case 14:	m_nLeftLightPort[0] = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
		case 15:	m_nLeftLightPort[1] = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
		case 16:	m_nRightLightPort[0] = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
		case 17:	m_nRightLightPort[1] = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
		}
	}

	//FILE 
	m_nFileDeleteDay = GetPrivateProfileInt(_T("FILE"), _T("Day"), 0, szPath);
	if (m_nFileDeleteDay < 1) m_nFileDeleteDay = 100;
	// MAIN PC IP
	GetPrivateProfileString(_T("MAIN_COMM"), _T("Ip"), _T(""), m_szAAIp, sizeof(m_szAAIp), szPath);
	// MAIN PC Port
	m_nAAPort = GetPrivateProfileInt(_T("MAIN_COMM"), _T("Port"), 0, szPath);

	// 화상검사기 PC IP
	GetPrivateProfileString(_T("INSP_COMM"), _T("Ip"), _T(""), m_szInspIp, sizeof(m_szInspIp), szPath);
	// 화상검사기 PC Port
	m_nInspPort = GetPrivateProfileInt(_T("INSP_COMM"), _T("Port"), 0, szPath);

	// 비밀번호
	GetPrivateProfileString(_T("PASSWORD"), _T("Passwd"), _T(""), m_szPassword, sizeof(m_szPassword), szPath);

	

	// CAM RESOLUTION
	for (i = 0; i < MAX_CAM_COUNT; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CAM%d"), i + 1);
		GetPrivateProfileString(_T("CAM_RESOLUTION"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		if (_tcslen(szIniBuff) > 0)
		{
			for (j = 0; j < 4; j++)
			{
				AfxExtractSubString(sToken, szIniBuff, j, _T('/'));

				switch (j)
				{
				case 0:		m_clCamResol[i].x = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				case 1:		m_clCamResol[i].y = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				case 2:		m_clCamAngle[i].x = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				case 3:		m_clCamAngle[i].y = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
//
//	시스템 데이터 저장
//
//-----------------------------------------------------------------------------
void CSystemData::sDSave()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i, j;
	CFileFind clFinder;
	if (clFinder.FindFile(BASE_DATA_PATH) == FALSE)
	{
		CreateDirectory(BASE_DATA_PATH, NULL);
	}

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\SystemData.ini"), BASE_DATA_PATH);

	// Motor
	for( i = 0; i < MAX_UNIT_COUNT; i++)
	{
		for (j = 0; j < MAX_MOTOR_COUNT; j++)
		{
			_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf / %.03lf / %.03lf / %.03lf"), m_dMotorSpeed[i][j], m_dMotorAccTime[i][j], m_dMotorDecTime[i][j], m_dMotorResol[i][j], m_dOrgDataset[i][j]);
			
			if( i == 0 )	WritePrivateProfileString(_T("MotorPara1"), MOTOR_NAME[j], szData, szPath);
			else			WritePrivateProfileString(_T("MotorPara2"), MOTOR_NAME[j], szData, szPath);
		}
	}

	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		if (i == 0)
		{
			// 코너 SFR 편차 LIMIT
			_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dLimitSFRBalance[i]);
			WritePrivateProfileString(_T("SFR_LIMIT1"), _T("CornerDeviation"), szData, szPath);
			// OC SPEC X,Y,T
			_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf / %.03lf"), m_clOCSpec[i].x, m_clOCSpec[i].y, m_dOCSpecTh[i]);
			WritePrivateProfileString(_T("OC_SPEC1"), _T("XYT"), szData, szPath);
		}
		else
		{
			// 코너 SFR 편차 LIMIT
			_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dLimitSFRBalance[i]);
			WritePrivateProfileString(_T("SFR_LIMIT2"), _T("CornerDeviation"), szData, szPath);
			// OC SPEC X,Y,T
			_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf / %.03lf"), m_clOCSpec[i].x, m_clOCSpec[i].y, m_dOCSpecTh[i]);
			WritePrivateProfileString(_T("OC_SPEC2"), _T("XYT"), szData, szPath);
		}
	}

	// MES IP
	WritePrivateProfileString(_T("MES"), _T("Ip"), m_szMesIp, szPath);
	// MES Port
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nMesPort);
	WritePrivateProfileString(_T("MES"), _T("Port"), szData, szPath);
	// MES FATORY CD
	
	WritePrivateProfileString(_T("MES"), _T("FactoryCd"), m_szFactoryCd, szPath);
	//
	// MES LOG DATA 저장 경로
	WritePrivateProfileString(_T("MES"), _T("Path"), m_szMesPath, szPath);

	// Serial Port
	_stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d"), 
		m_nOC_IRPort[0] , m_nOC_IRPort[1], 
		m_nTopLightPort[0], m_nTopLightPort[1], m_nEzi_Port[0], m_nEzi_Port[1],
		m_nLaserPort[0], m_nLaserPort[1], m_nBcrPort[0], m_nBcrPort[1], m_nUvPort[0], m_nUvPort[1], 
		m_nAlign_Oc_Port[0], m_nAlign_Oc_Port[1], m_nLeftLightPort[0], m_nLeftLightPort[1], m_nRightLightPort[0], m_nRightLightPort[1]
	);
	
	WritePrivateProfileString(_T("SERIAL"), _T("PortNum"), szData, szPath);


	//FILE 
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nFileDeleteDay);
	WritePrivateProfileString(_T("FILE"), _T("Day"), szData, szPath);

	// MAIN IP
	WritePrivateProfileString(_T("MAIN_COMM"), _T("Ip"), m_szAAIp, szPath);
	// AA Port
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nAAPort);
	WritePrivateProfileString(_T("MAIN_COMM"), _T("Port"), szData, szPath);

	// MAIN IP
	WritePrivateProfileString(_T("INSP_COMM"), _T("Ip"), m_szInspIp, szPath);
	// AA Port
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nInspPort);
	WritePrivateProfileString(_T("INSP_COMM"), _T("Port"), szData, szPath);

	// 비밀번호
	WritePrivateProfileString(_T("PASSWORD"), _T("Passwd"), m_szPassword, szPath);

	

	for (i = 0; i < MAX_CAM_COUNT; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CAM%d"), i + 1);
		_stprintf_s(szIniBuff, SIZE_OF_1K, _T("%.04lf / %.04lf / %.04lf/ %.04lf"),
			m_clCamResol[i].x, m_clCamResol[i].y, m_clCamAngle[i].x, m_clCamAngle[i].y);

		WritePrivateProfileString(_T("CAM_RESOLUTION"), szIniIndex, szIniBuff, szPath);
	}

	this->sDCopyBackup();
}

//-----------------------------------------------------------------------------
//
//	시스템 설정 파일 백업
//
//-----------------------------------------------------------------------------
void CSystemData::sDCopyBackup()
{
	TCHAR szBackupPath[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];	
	SYSTEMTIME stSysTime;
	CFileFind clFinder;
		
	GetLocalTime(&stSysTime);
	
	if (clFinder.FindFile(ROOT_PATH) == FALSE)
	CreateDirectory(ROOT_PATH, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s"), BASE_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup"), BASE_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
	CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup\\%04d%02d"), BASE_PATH, stSysTime.wYear, stSysTime.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
	CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup\\%04d%02d\\%02d"), BASE_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
	CreateDirectory(szPath, NULL);

	_stprintf_s(szBackupPath, SIZE_OF_1K, _T("%s\\Backup\\%04d%02d\\%02d\\SystemData_%02d_%02d_%02d_%03d.ini"),
		BASE_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond, stSysTime.wMilliseconds);


	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\SystemData.ini"), BASE_DATA_PATH);


	CopyFile(szPath, szBackupPath, TRUE);
}

CSFRTeachingData::CSFRTeachingData()
{
	dSFRPcbX = 0.0;
	dSFRPcbY = 0.0;
	dSFRPcbY = 0.0;
	dSFRPcbTx = 0.0;
	dSFRPcbTy = 0.0;
}

//-----------------------------------------------------------------------------
//
//	모델 데이터 생성자
//
//-----------------------------------------------------------------------------
CModelData::CModelData()
{
	int i = 0;
	int j = 0;
	m_nUnit = 0;

	memset(m_szIniPath, 0x00, sizeof(m_szIniPath));
	m_nWidth = 0;
	m_nHeight = 0;
	
	DefectSizeX = 0;
	DefectSizeY = 0;

	for (i = 0; i < 9; i++)
	{
        m_FovSpec[i] = 0.0;
	}
	m_OcSpec[0] = 0.0;
	m_OcSpec[1] = 0.0;

	m_dOCSpecLimit[0] = 0.0;
	m_dOCSpecLimit[1] = 0.0;

	m_dRotateSpecLimit[0] = 0.0;
	m_dRotateSpecLimit[1] = 0.0;

	m_dTiltxSpecLimit[0] = 0.0;
	m_dTiltxSpecLimit[1] = 0.0;

	m_dTiltySpecLimit[0] = 0.0;
	m_dTiltySpecLimit[1] = 0.0;

	/*for (i = 0; i < g_ColorSenscount; i++)
	{
		m_ColorSensitivitySpec[0][i] = 0.0;
		m_ColorSensitivitySpec[1][i] = 0.0;
		m_ColorSensitivitySpec[2][i] = 0.0;
	}*/
	for (i = 0; i < 4; i++)
	{
		m_EpoxyLineLength[i] = 0.0;
		m_EpoxyCurveCenterXPoint[i] = 0.0;
		m_EpoxyCurveCenterYPoint[i] = 0.0;
		m_EpoxyCurveEndXPoint[i] = 0.0;
		m_EpoxyCurveEndYPoint[i] = 0.0;
	}

	for (i = 0; i < 4; i++)
	{
		m_LcbOffsetSpec[i] = 0;
		m_YmeanOffsetSpec[i] = 0;
		m_FDFOffsetSpec[i] = 0;
	}


	m_EpoxyLineSpeed = 0.0;
	m_EpoxyLineAccDec = 0.0;
	m_EpoxyCurveAccDec = 0.0;
	m_EpoxyOnTime = 0.0;
	m_EpoxyOffTime = 0.0;
	m_EpoxyCurveSpeed = 0.0;

	m_ResingRectStart[0].x = 0;
	m_ResingRectStart[0].y = 0;
	m_ResingRectSize[0].x = 0;
	m_ResingRectSize[0].y = 0;
	m_ResingRectStart[1].x = 0;
	m_ResingRectStart[1].y = 0;
	m_ResingRectSize[1].x = 0;
	m_ResingRectSize[1].y = 0;
	m_ResingRectStart[2].x = 0;
	m_ResingRectStart[2].y = 0;
	m_ResingRectSize[2].x = 0;
	m_ResingRectSize[2].y = 0;
	m_ResingRectStart[3].x = 0;
	m_ResingRectStart[3].y = 0;
	m_ResingRectSize[3].x = 0;
	m_ResingRectSize[3].y = 0;

	m_CircleDrawCenter[0].x = 10.0;
	m_CircleDrawCenter[0].y = 10.0;
	m_CircleDrawCenter[1].x = 10.0;
	m_CircleDrawCenter[1].y = 10.0;
	m_CircleDrawCenter[2].x = 10.0;
	m_CircleDrawCenter[2].y = 10.0;
	m_CircleDrawCenter[3].x = 10.0;
	m_CircleDrawCenter[3].y = 10.0;

	m_ResinDrawSize.x = 7.8;
	m_ResinDrawSize.y = 8.5;

	m_dResinInspOffset[0].x = 0.4;
	m_dResinInspOffset[0].y = 0.4; 
	m_dResinInspOffset[1].x = 0.4;
	m_dResinInspOffset[1].y = 0.4;

	m_nResinInspLimit = 20;
	m_dResinInspRectSpec = 40;
	m_dResinInspHoleSpec = 20;
	m_dResinInspGapLength = 0.06;

	n_DefectCountLimit = 0;
	n_ClusterCountLimit = 0;
	
	for (i = 0; i < MAX_POS_COUNT; i++)
	{
		memset(&m_stTeachData[i], 0x00, sizeof(m_stTeachData[i]));
	}



	m_nRoiSizeX = 50;
	m_nRoiSizeY = 70;
	m_dCcdCellSize = 1.12;

	m_nMTF_FinalMode = 0;
	m_nCcdFlipUse = 0;
	m_nOldChartMTF = 0;

	m_dMTFOffset = 0.0;
	m_dCircleThresh = 90.0;
	m_dLimitSFRCent = 0.6;
	m_d2ndAAMoveDistance = 0.0;
	m_dLimitSFRSide = 0.4;

	m_nCountOfCheckSFR = 0;
	m_dSfrMoveDistance = 0.0;

	m_nSfrMode = 1;

	m_nSFR_N_POS = 0;

	for (i = 0; i < 2; i++)
	{
		m_dLaserMoveX[i] = 0.0;
		m_dLaserMoveY[i] = 0.0;
	}
	for (i = 0; i < 2; i++)
	{
		m_dLaserComplMoveX[i] = 0.0;
		m_dLaserComplMoveY[i] = 0.0;
	}
	
	for (i = 0; i < 2; i++)
	{
		m_nStainCount[i] = 0;
		m_dOcAlignSpec[i] = 0.0;
		
	}

	for (i = 0; i < 3; i++)
	{
		m_dSensorAlignSpec[i] = 0.0;
		m_dLensAlignSpec[i] = 0.0;
		m_dHolderAlign[i] = 0.0;
	}
	

	m_dUvTime = 50;

	m_dEscapePosPcbZ = 0.0;

	m_nContactRetryCount = 0;
	m_nSensorAlignRetryCount = 0;
	m_nCcdRetryCount = 0;
	m_dSensorAlignDelay = 0.0;
	m_nLensAlignRetryCount = 0;
	m_dLensAlignDelay = 0.0;
	m_nLaserRetryCount = 0;
	m_dLaserDelay = 0.0;

	m_nDiffRetryCount = 0;			// Diff Retry Count
	m_dDiffDelay = 0.0;

	m_nRawSumCount = 0;

	m_nDryRunMode = 0;
	m_nCOMPLETE_MODE = 0;
	m_nUvUse = 0;
	m_nLaserInUse = 0;
	m_nLaserOutUse = 0;
	m_nUnloadAfter1stAAUse = 0;
	m_nStainInspUse = 0;
	m_nNgImageSaveUse = 0;

	m_nSaturationInspUse = 0;		
	m_nIRFilterInspUse = 0;			
	m_nColorReproductionInspUse = 0;


	m_nDarkInspUse = 0;
	m_nCurrentUse = 0;
	m_nRITestUse = 0;
	m_nMesPass = 0;
	m_nCcdDefectInfpUse = 0;
	m_nDoorLockUse = 0;
	m_nFpsStopUse = 0;
	m_nPatternChartUse = 0;
	m_nSfrAvrCheck = 0;
	m_nPinStopUse = 0;
	m_nMasterModeUse = 0;
	m_nSfr8BitUse = 0;
	m_nBlemish8BitUse = 0;
	m_nColor8BitUse = 0;
	m_nRi8BitUse = 0;
	
	m_nInspOKPass = 0;
	m_nAlignPass = 0;
	m_nRawSavePass = 0;
	m_nJxlSavePass = 0;
	m_nIdleReasonPass = 0;
	m_fFpsStopVal = 5.0;
	m_nJxlEffort = 6;
	m_nLaserControlLock = 0;
	m_nDomeChartUse = 0;
	m_nUVLampAlarmUse = 0;
	m_nAAPass = 0;
	m_nInspectionPass = 0;
	m_nEpoxyPass = 0;
	m_nEpoxyInspPass = 0;
	
	m_dOffsetPrevUV_X = 0.0;
	m_dOffsetPrevUV_Y = 0.0;
	m_dOffsetPrevUV_Z = 0.0;
	m_dOffsetPrevUV_Tx = 0.0;
	m_dOffsetPrevUV_Ty = 0.0;
	m_dOffsetPrevUV_Th = 0.0;

	m_dEolPcbOffset_Tx = 0.0;
	m_dEolPcbOffset_Ty = 0.0;

	m_dPCBVacuumDelay = 0.0;
	m_dPCBGripDelay = 0.0;
	m_dLENSGripDelay = 0.0;
	m_dPCBGripUpDelay = 0.0;
	m_dLaserTimeOut = 0.0;
	m_dFinalDelay = 0.0;
	m_dBondingDelay = 0.0;
	m_nContactRetryDelay = 0.0;
	m_nSensorCnt = 1;

	for (i = 0; i < 4; i++)
	{
		sfrParameter[i] = 0;
		blemishParameter[i] = 0;
		colorParameter[i] = 0;
		riParameter[i] = 0;
	}
	
	for (i = 0; i < MAX_LIGHT_COUNT; i++)
	{
		m_nLight[i] = 0;
	}
	m_CurrentChartIndex = LIGHT_CHART_CH_1;
	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		m_dOkLimit[i] = 0.0;
		m_dErrLimit[i] = 0.0;
	}

	m_dStainLsbCenter = 0.0;
	m_dStainLsbCorner = 0.0;
	m_dStainLsbEdge = 0.0;

	m_dStainYMeanCenter = 0.0;
	m_dStainYMeanCorner = 0.0;
	m_dStainYMeanEdge = 0.0;

	m_nMarkNo = 0;
	m_nMinMatching = 80;

    for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
    {
        m_nDirection[i] = 0;
		m_nPatternDirection[i] = 0;
		m_MTF_ROI_Pos[0][i] = 0;
		m_MTF_ROI_Pos[1][i] = 0;

		m_sfrOffset[i].x = 0.0;
		m_sfrOffset[i].y = 0.0;
    }
    m_dLinePulse = 0.0;
	m_dSfrBlackLevel = 0;
	m_dBlemishBlackLevel = 0;
	m_dColorBlackLevel = 0;
	m_dRiBlackLevel = 0;

	m_dCcdDelay = 1.0;
	m_dDemosaic = 0;
    for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
    {
        m_nPatternPos[i].x = 0;
        m_nPatternPos[i].y = 0;
        m_nPatternSize[i].x = 0;
        m_nPatternSize[i].y = 0;
    }
	m_dChartRotation = 0.0;
    m_dChartHfovMin = 0.0;
    m_dChartHfovMax = 0.0;

    m_dChartVfovMin = 0.0;
    m_dChartVfovMax = 0.0;

    m_dChartDistortionMin = 0.0;
    m_dChartDistortionMax = 0.0;



	/*for (i = 0; i < g_Defectcount; i++)
	{
		m_DefectSpec[i] = 0.0;
	}*/
	/*for (i = 0; i < g_Ricount; i++)
	{
		m_RISpec[i] = 0.0;
	}*/
	/*for (i = 0; i < g_ColorShadingcount; i++)
	{
		m_ColorShadingSpec[i] = 0.0;
	}*/

	
	m_d_IC_OffsetX[0] = 0.0;
	m_d_IC_OffsetY[0] = 0.0;
	m_d_IC_OffsetX[1] = 0.0;
	m_d_IC_OffsetY[1] = 0.0;


}

//-----------------------------------------------------------------------------
//
//	모델 데이터 소멸자
//
//-----------------------------------------------------------------------------
CModelData::~CModelData()
{

}

//-----------------------------------------------------------------------------
//
//	모델 데이터 유닛번호 설정
//
//-----------------------------------------------------------------------------
void CModelData::SetUnit(int nUnit)
{
	m_nUnit = nUnit;

	ModelChange_ModelData();
}


void CModelData::VarationLoad()
{
#if 0
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szLog[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i, j;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Variation.ini"), BASE_DATA_PATH);


	//g_clModelData[m_nUnit].nVarRepetCount
	nVarRepetCount = GetPrivateProfileInt(_T("VARIATION"), _T("COUNT"), 0, szPath);
	nVarMode = GetPrivateProfileInt(_T("VARIATION"), _T("MODE"), 0, szPath);
	if (nVarRepetCount < 1)
	{
		nVarRepetCount = 1;
	}
	if (nVarRepetCount > 20)
	{
		nVarRepetCount = 20;
	}

	if (nVarMode < 0)
	{
		nVarMode = 0;
	}
	if (nVarMode > 2)
	{
		nVarMode = 2;
	}
	TCHAR* pszVarMode[] = { _T("Min"),  _T("Max"), _T("Average") };


	_stprintf_s(szLog, SIZE_OF_1K, _T("[INFO]Variation Test Count:%d"), nVarRepetCount);
	AddLog(szLog, 0, m_nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[INFO]Variation Mode:%s"), pszVarMode[nVarMode]);
	AddLog(szLog, 0, m_nUnit);


	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("%d"), i);
		GetPrivateProfileString(_T("SFR_OFFSET"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		for (j = 0; j < 2; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));

			switch (j)
			{
				// sfr값에 곱하기
			case 0:		m_sfrOffset[i].x = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
				// sfr값에 더하기
			case 1:		m_sfrOffset[i].y = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			}
		}


	}

#endif
}

//-----------------------------------------------------------------------------
//
//	모델 데이터 로드
//
//-----------------------------------------------------------------------------
void CModelData::Load(TCHAR* szModelName)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i, j;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\DATA.ini"), BASE_DATA_PATH);
	
	
	//// TEACH DATA
	//for (i = 0; i < MAX_POS_COUNT; i++)
	//{
	//	GetPrivateProfileString(_T("TEACH"), POS_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	//	for (j = 0; j < MAX_MOTOR_COUNT; j++)
	//	{
	//		AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
	//		m_stTeachData[i].dPos[j] = _ttof((TCHAR*)(LPCTSTR)sToken);
	//	}
	//}

	GetPrivateProfileString(_T("CCD_SIZE"), _T("CellSize"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_dCcdCellSize = _ttof(szIniBuff);

	// MTF 측정 모드
	m_nMTF_FinalMode = GetPrivateProfileInt(_T("MTF_INSP"), _T("FinalMode"), 0, szPath);
	// CCD 반전
	m_nCcdFlipUse = GetPrivateProfileInt(_T("CCD_FLIP"), _T("Use"), 0, szPath);
	// 구형 차트 사용
	m_nOldChartMTF = GetPrivateProfileInt(_T("MTF_INSP"), _T("OldMTFUse"), 0, szPath);
	// MTF Offset 가중치
	GetPrivateProfileString(_T("MTF_INSP"), _T("Offset"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_dMTFOffset = _ttof((szIniBuff));

	GetPrivateProfileString(_T("CIRCLE"), _T("Threshold"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	int Length = _tcslen(szIniBuff);
	
	
	if (Length > 1)
	{
		m_dCircleThresh = _ttof((szIniBuff));
		//m_dCircleThresh = 90.0;
	}
	for (i = 0; i < 2; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("AF%d"), i + 1);
		GetPrivateProfileString(_T("ACTIVE_ALIGN"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		for (j = 0; j < 8; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));

			switch (j)
			{
				// 이동 속도
			case 0:		m_stAFInfo[i].dMoveVel = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
				// 가감속
			case 1:		m_stAFInfo[i].dMoveAcc = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
				// Delay
			case 2:		m_stAFInfo[i].nDelayTime = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
				// 이동거리
			case 3:		m_stAFInfo[i].dMoveDistance = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
				// STEP 수
			case 4:
				m_stAFInfo[i].nMaxStepCount = _ttoi((TCHAR*)(LPCTSTR)sToken);
				if (m_stAFInfo[i].nMaxStepCount == 0)
					m_stAFInfo[i].nMaxStepCount = 75;
				break;
				// Limit MTF
			case 5:		m_stAFInfo[i].fLimitRoughMTF = (float)_ttof((TCHAR*)(LPCTSTR)sToken);	break;
				// SFR 평균 카운트
			case 6:		m_stAFInfo[i].nAvgSfrCount = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
			case 7:		m_stAFInfo[i].fLimitFineMTF = (float)_ttof((TCHAR*)(LPCTSTR)sToken);	break;
			}
		}		
	}

	// CENTER SFR LIMIT
	GetPrivateProfileString(_T("SFR_LIMIT"), _T("Center"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_dLimitSFRCent = _ttof(szIniBuff);
	// 2차 AA 시작시 이동
	GetPrivateProfileString(_T("2ND_AA_MOVE"), _T("Distance"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_d2ndAAMoveDistance = _ttof(szIniBuff);
	// CORNER SFR LIMIT
	GetPrivateProfileString(_T("SFR_LIMIT"), _T("Corner"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_dLimitSFRSide = _ttof(szIniBuff);

    //
    //
    //fov , distortion  rotation 제한 spec
	GetPrivateProfileString(_T("CHART_LIMIT"), _T("Rotation"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_dChartRotation = _ttof(szIniBuff);
	
    GetPrivateProfileString(_T("CHART_LIMIT"), _T("HfovMin"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
    m_dChartHfovMin = _ttof(szIniBuff);
    GetPrivateProfileString(_T("CHART_LIMIT"), _T("HfovMax"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
    m_dChartHfovMax = _ttof(szIniBuff);
    GetPrivateProfileString(_T("CHART_LIMIT"), _T("VfovMin"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
    m_dChartVfovMin = _ttof(szIniBuff);
    GetPrivateProfileString(_T("CHART_LIMIT"), _T("VfovMax"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
    m_dChartVfovMax = _ttof(szIniBuff);
    GetPrivateProfileString(_T("CHART_LIMIT"), _T("DistortionMin"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
    m_dChartDistortionMin = _ttof(szIniBuff);
    GetPrivateProfileString(_T("CHART_LIMIT"), _T("DistortionMax"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
    m_dChartDistortionMax = _ttof(szIniBuff);

    //
    //
	GetPrivateProfileString(_T("SFR_DECREASE"), _T("Decrease"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (j = 0; j < 2; j++)
	{
		AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
		switch (j)
		{
			// 체크 데이터 수
		case 0:		m_nCountOfCheckSFR = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
			// 이동거리
		case 1:		m_dSfrMoveDistance = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		}
	}

	m_nSfrMode = GetPrivateProfileInt(_T("SFR_MODE"), _T("Mode"), 1, szPath);
	// SFR POSITION
	m_nSFR_N_POS = GetPrivateProfileInt(_T("SFR_POS"), _T("Type"), 1, szPath);



	// Laser In
	GetPrivateProfileString(_T("LASER COMPLETE"), _T("InPos"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	{
		for (j = 0; j < 2; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		m_dLaserComplMoveX[0] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
			case 1:		m_dLaserComplMoveY[0] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
			}
		}
	}

	// Laser Out
	GetPrivateProfileString(_T("LASER COMPLETE"), _T("OutPos"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (j = 0; j < 2; j++)
	{
		AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
		switch (j)
		{
		case 0:		m_dLaserComplMoveX[1] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 1:		m_dLaserComplMoveY[1] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		}
	}

	// Laser In
	GetPrivateProfileString(_T("LASER"), _T("InPos"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	{
		for (j = 0; j < 2; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		m_dLaserMoveX[0] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
			case 1:		m_dLaserMoveY[0] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
			}
		}
	}

	// Laser Out
	GetPrivateProfileString(_T("LASER"), _T("OutPos"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (j = 0; j < 2; j++)
	{
		AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
		switch (j)
		{
		case 0:		m_dLaserMoveX[1] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 1:		m_dLaserMoveY[1] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		}
	}
	

	// Stain 불량 카운트
	m_nStainCount[0] = GetPrivateProfileInt(_T("STAIN"), _T("White"), 0, szPath);
	m_nStainCount[1] = GetPrivateProfileInt(_T("STAIN"), _T("Black"), 0, szPath);

	// UV
	m_dUvTime = GetPrivateProfileInt(_T("UV"), _T("Time"), 0, szPath);

	// PCB Z축 회피 위치
	GetPrivateProfileString(_T("ESCAPE_POS"), _T("PcbZ"), _T("0.0"), szIniBuff, sizeof(szIniBuff), szPath);
	m_dEscapePosPcbZ = _ttof(szIniBuff);

	m_nSensorAlignRetryCount = GetPrivateProfileInt(_T("ALIGN_RETRY"), _T("Sensor_Retry_Count"), 0, szPath);
	m_nCcdRetryCount = GetPrivateProfileInt(_T("CCD_RETRY"), _T("CCD_Retry_Count"), 0, szPath);
	m_nLensAlignRetryCount = GetPrivateProfileInt(_T("ALIGN_RETRY"), _T("Lens_Retry_Count"), 0, szPath);
	m_nLaserRetryCount = GetPrivateProfileInt(_T("LASER_CONTROL"), _T("Retry_Count"), 0, szPath);
	m_nDiffRetryCount = GetPrivateProfileInt(_T("DIFF_RETRY"), _T("Retry_Count"), 0, szPath);
	m_nContactRetryCount = GetPrivateProfileInt(_T("CONTACT_RETRY"), _T("COUNT"), 0, szPath);


	m_nRawSumCount = GetPrivateProfileInt(_T("RAWSUM_COUNT"), _T("Rawsum_Count"), 0, szPath);

	// Delay Time 관련
	GetPrivateProfileString(_T("DelayTime"), _T("Time"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (j = 0; j < 11; j++)//for (j = 0; j < 10; j++)
	{
		AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
		switch (j)
		{
		case 0:		m_dPCBVacuumDelay = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 1:		m_dPCBGripDelay = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 2:		m_dPCBGripUpDelay = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 3:		m_dLaserDelay = _ttof((TCHAR*)(LPCTSTR)sToken);			break;
		case 4:		m_dSensorAlignDelay = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
		case 5:		m_dLaserTimeOut = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 6:		m_dFinalDelay = _ttof((TCHAR*)(LPCTSTR)sToken);			break;
		case 7:		m_dBondingDelay = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 8:		m_dLensAlignDelay = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 9:     m_dCcdDelay = _ttof((TCHAR*)(LPCTSTR)sToken);			break;
		case 10:    m_dDiffDelay = _ttof((TCHAR*)(LPCTSTR)sToken);			break;
		}
	}
	// Align Spec
	GetPrivateProfileString(_T("AlignSpec"), _T("Spec"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (j = 0; j < 6; j++)
	{
		AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
		switch (j)
		{
		case 0:		m_dSensorAlignSpec[0] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 1:		m_dSensorAlignSpec[1] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 2:		m_dSensorAlignSpec[2] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 3:		m_dLensAlignSpec[0] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 4:		m_dLensAlignSpec[1] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 5:		m_dLensAlignSpec[2] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;


		}
	}
	// Oc Align Spec
	GetPrivateProfileString(_T("OcAlignSpec"), _T("Spec"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (j = 0; j < 2; j++)
	{
		AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
		switch (j)
		{
		case 0:		m_dOcAlignSpec[0] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 1:		m_dOcAlignSpec[1] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		}
	}


	//
	//m_nDryRunMode = GetPrivateProfileInt(_T("RUN_MODE"), _T("Mode"), 0, szPath);
	//m_nCOMPLETE_MODE = GetPrivateProfileInt(_T("COMPL_MODE"), _T("Use"), 0, szPath);
	m_nUvUse = GetPrivateProfileInt(_T("UV"), _T("Use"), 1, szPath);
	m_nLaserInUse = GetPrivateProfileInt(_T("LASER_IN"), _T("Use"), 1, szPath);
	m_nLaserOutUse = GetPrivateProfileInt(_T("LASER_OUT"), _T("Use"), 1, szPath);
	m_nUnloadAfter1stAAUse = GetPrivateProfileInt(_T("UNLOAD_AFTER_1ST_AA"), _T("Use"), 0, szPath);

	m_nStainInspUse = GetPrivateProfileInt(_T("STAIN_INSP"), _T("Use"), 1, szPath);

	m_nSaturationInspUse = GetPrivateProfileInt(_T("SATURATION_INSP"), _T("Use"), 1, szPath);
	m_nIRFilterInspUse = GetPrivateProfileInt(_T("IRFILTER_INSP"), _T("Use"), 1, szPath);
	m_nColorReproductionInspUse = GetPrivateProfileInt(_T("COLORREPRODUCTION_INSP"), _T("Use"), 1, szPath);

	m_nNgImageSaveUse = GetPrivateProfileInt(_T("NG_IMAGE_SAVE"), _T("Use"), 1, szPath);
	m_nDarkInspUse = GetPrivateProfileInt(_T("DARK_INSP"), _T("Use"), 0, szPath);

	m_nCurrentUse = GetPrivateProfileInt(_T("CURRENT_INSP"), _T("Use"), 0, szPath);
	m_nRITestUse = GetPrivateProfileInt(_T("RI_INSP"), _T("Use"), 0, szPath);
	m_nMesPass = GetPrivateProfileInt(_T("MESPASS"), _T("Use"), 0, szPath);
	m_nCcdDefectInfpUse = GetPrivateProfileInt(_T("CCD_DEFECT_INSP"), _T("Use"), 1, szPath);

	m_nDoorLockUse = GetPrivateProfileInt(_T("DOOR_LOCK"), _T("Use"), 1, szPath);

	m_nEpoxyPass = GetPrivateProfileInt(_T("EPOXY"), _T("Use"), 1, szPath);
	m_nEpoxyInspPass = GetPrivateProfileInt(_T("EPOXY_INSP"), _T("Use"), 1, szPath);

	
	m_nFpsStopUse = GetPrivateProfileInt(_T("FPS_STOP"), _T("Use"), 0, szPath);
	m_nPatternChartUse = 1;// GetPrivateProfileInt(_T("PATTERN"), _T("Use"), 0, szPath);
	m_nSfrAvrCheck = GetPrivateProfileInt(_T("SFR_AVR"), _T("Use"), 0, szPath);
	GetPrivateProfileString(_T("FPS_STOP"), _T("Value"), _T("5.0"), szIniBuff, sizeof(szIniBuff), szPath);
	m_fFpsStopVal = (float)_ttof(szIniBuff);
	m_nLaserControlLock = GetPrivateProfileInt(_T("LASER_CONTROL"), _T("Use"), 0, szPath);

	m_nJxlEffort = GetPrivateProfileInt(_T("JXL"), _T("Effort"), 0, szPath);
	m_nDomeChartUse = GetPrivateProfileInt(_T("DOME_CHART"), _T("Use"), 0, szPath);
	m_nUVLampAlarmUse = GetPrivateProfileInt(_T("UV_LAMP_ALARM"), _T("Use"), 0, szPath);
	m_nAAPass = GetPrivateProfileInt(_T("AA_PASS"), _T("Use"), 0, szPath);
	m_nInspectionPass = GetPrivateProfileInt(_T("INSPECTION_PASS"), _T("Use"), 0, szPath);

	// PreUV Offset
	GetPrivateProfileString(_T("PRE_UV_OFFSET"), _T("Offset"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (j = 0; j < 6; j++)
	{
		AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
		switch (j)
		{
		case 0:		m_dOffsetPrevUV_X = _ttof((TCHAR*)(LPCTSTR)sToken);			break;
		case 1:		m_dOffsetPrevUV_Y = _ttof((TCHAR*)(LPCTSTR)sToken);			break;
		case 2:		m_dOffsetPrevUV_Z = _ttof((TCHAR*)(LPCTSTR)sToken);			break;
		case 3:		m_dOffsetPrevUV_Tx = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 4:		m_dOffsetPrevUV_Ty = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 5:		m_dOffsetPrevUV_Th = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		}
	}
	// eol Offset
	GetPrivateProfileString(_T("EOL_TILT_OFFSET"), _T("Offset"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (j = 0; j < 2; j++)
	{
		AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
		switch (j)
		{
		case 0:		m_dEolPcbOffset_Tx = _ttof((TCHAR*)(LPCTSTR)sToken);			break;
		case 1:		m_dEolPcbOffset_Ty = _ttof((TCHAR*)(LPCTSTR)sToken);			break;
		}
	}
	
	m_nPinStopUse = GetPrivateProfileInt(_T("SENSOR_COUNT"), _T("Use"), 0, szPath);
	m_nSensorCnt = GetPrivateProfileInt(_T("SENSOR_COUNT"), _T("Count"), 0, szPath);
	m_nMasterModeUse = GetPrivateProfileInt(_T("MASTER_MODE"), _T("Use"), 0, szPath);
	m_nInspOKPass = GetPrivateProfileInt(_T("INSP_OKPASS"), _T("Use"), 0, szPath);
	m_nAlignPass = GetPrivateProfileInt(_T("ALIGN_PASS"), _T("Use"), 0, szPath);
	m_nRawSavePass = GetPrivateProfileInt(_T("RAW_PASS"), _T("Use"), 0, szPath);
	m_nJxlSavePass = GetPrivateProfileInt(_T("JXL_PASS"), _T("Use"), 0, szPath);
	m_nIdleReasonPass = GetPrivateProfileInt(_T("IDLE_PASS"), _T("Use"), 0, szPath);
	//통합 oc광원
	m_LxVal = GetPrivateProfileInt(_T("OC_MERGE"), _T("LxValue"), 0, szPath);
	
	for (i = 0; i < 2; i++)
	{
		m_LxData[i] = GetPrivateProfileInt(_T("OC_MERGE"), OC_LIGHT_NAME[i], 0, szPath);
	}

	// 조명 데이터
	for (i = 0; i < MAX_LIGHT_COUNT; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("%02d"), i + 1);
		m_nLight[i] = GetPrivateProfileInt(_T("Light"), szIniIndex, 0, szPath);
	}

	
	// 보정량 LIMIT
	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		GetPrivateProfileString(_T("AlignLimit"), MOTOR_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		for (j = 0; j < 2; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		m_dOkLimit[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
			case 1:		m_dErrLimit[i] = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			}
		}
	}

	m_clSfrInfo.m_nCenSizeX = GetPrivateProfileInt(_T("SFR_SIZE"), _T("CEN_SIZE_X"), 50, szPath);
	m_clSfrInfo.m_nCenSizeY = GetPrivateProfileInt(_T("SFR_SIZE"), _T("CEN_SIZE_Y"), 57, szPath);


	GetPrivateProfileString(_T("SFR_SIZE"), _T("SizeX"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		m_clSfrInfo.m_nSizeX[i] = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}

	GetPrivateProfileString(_T("SFR_SIZE"), _T("SizeY"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		m_clSfrInfo.m_nSizeY[i] = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}

	

	m_nRoiSizeX = GetPrivateProfileInt(_T("ROI_SIZE"), _T("SIZE_X"), 50, szPath);
	m_nRoiSizeY = GetPrivateProfileInt(_T("ROI_SIZE"), _T("SIZE_Y"), 70, szPath);

	for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("%02d"), i + 1);
		GetPrivateProfileString(_T("SfrOffset"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		for (j = 0; j < 2; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		m_clSfrInfo.m_clPtOffset[i].x = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
			case 1:		m_clSfrInfo.m_clPtOffset[i].y = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
			}
		}
	}
	


	// SFR oc 위치
	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("SFR_OC"));
	GetPrivateProfileString(_T("SfrOffset"), szIniIndex, _T("0.00/0.00"), szIniBuff, sizeof(szIniBuff), szPath);



    for (i = 0; i < 4; i++)
    {
        // 원형마크 위치
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("POS%02d"), i + 1);
        GetPrivateProfileString(_T("CircleMark"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        for (j = 0; j < 2; j++)
        {
            AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
            switch (j)
            {
            case 0:		m_clSfrInfo.m_clPtCircle[i].x = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
            case 1:		m_clSfrInfo.m_clPtCircle[i].y = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
            }
        }


        // 원형마크 영역
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%02d"), i + 1);
        GetPrivateProfileString(_T("CircleMark"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        for (j = 0; j < 4; j++)
        {
            AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
            switch (j)
            {
            case 0:		m_clSfrInfo.m_clRectCircle[i].left = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
            case 1:		m_clSfrInfo.m_clRectCircle[i].top = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
            case 2:		m_clSfrInfo.m_clRectCircle[i].right = _ttoi((TCHAR*)(LPCTSTR)sToken);	break; 
            case 3:		m_clSfrInfo.m_clRectCircle[i].bottom = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
            }
        }
    }
    //------------------------------------------------------------------------------
    //fov
    //------------------------------------------------------------------------------
    for (i = 0; i < VEC_FOV_COUNT; i++)
    {
        // fov 마크 위치
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("%02d"), i + 1);
        GetPrivateProfileString(_T("FovOffset"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        for (j = 0; j < 2; j++)
        {
            AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
            switch (j)
            {
            case 0:		m_clSfrInfo.m_clPtFovOffset[i].x = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
            case 1:		m_clSfrInfo.m_clPtFovOffset[i].y = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
            }
        }


        // fov 마크 영역
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%02d"), i + 1);
        GetPrivateProfileString(_T("FovMark"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        for (j = 0; j < 4; j++)
        {
            AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
            switch (j)
            {
            case 0:		m_clSfrInfo.m_clRectFov[i].left = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
            case 1:		m_clSfrInfo.m_clRectFov[i].top = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
            case 2:		m_clSfrInfo.m_clRectFov[i].right = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
            case 3:		m_clSfrInfo.m_clRectFov[i].bottom = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
            }
        }
    }
	GetPrivateProfileString(_T("FOV_SIZE"), _T("SizeX"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < VEC_FOV_COUNT; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		m_clSfrInfo.m_nFovSizeX[i] = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}

	GetPrivateProfileString(_T("FOV_SIZE"), _T("SizeY"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < VEC_FOV_COUNT; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		m_clSfrInfo.m_nFovSizeY[i] = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}

	//
	// Fov oc 위치
	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("FOV_OC"));
	GetPrivateProfileString(_T("FovMark"), szIniIndex, _T("0.00/0.00"), szIniBuff, sizeof(szIniBuff), szPath);

	for (j = 0; j < 2; j++)
	{
		AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
		switch (j)
		{
		case 0:		m_clSfrInfo.m_dFovOcX = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
		case 1:		m_clSfrInfo.m_dFovOcY = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
		}
	}



    //------------------------------------------------------------------------------
    //
    //------------------------------------------------------------------------------
	m_nMtfOverlayUse = GetPrivateProfileInt(_T("SfrOverlay"), _T("Use"), 0, szPath);

	GetPrivateProfileString(_T("StainLSB"), _T("Threshold"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for(i = 0; i < 3; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		switch(i)
		{
		case 0:	
			m_dStainLsbCenter = _ttof((TCHAR*)(LPCTSTR)sToken); 
			if(m_dStainLsbCenter == 0.0)
				m_dStainLsbCenter = 29.0;
			break;
		case 1:
			m_dStainLsbCorner = _ttof((TCHAR*)(LPCTSTR)sToken);
			if(m_dStainLsbCorner == 0.0)
				m_dStainLsbCorner = 65.0;
			break;
		case 2:
			m_dStainLsbEdge = _ttof((TCHAR*)(LPCTSTR)sToken);
			if(m_dStainLsbEdge == 0.0)
				m_dStainLsbEdge = 80.0;
			break;
		}

	}

	GetPrivateProfileString(_T("StainYMean"), _T("Threshold"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for(i = 0; i < 3; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		switch(i)
		{
		case 0:
			m_dStainYMeanCenter = _ttof((TCHAR*)(LPCTSTR)sToken);
			if(m_dStainYMeanCenter == 0.0)
				m_dStainYMeanCenter = 3.0;
			break;
		case 1:
			m_dStainYMeanCorner = _ttof((TCHAR*)(LPCTSTR)sToken);
			if(m_dStainYMeanCorner == 0.0)
				m_dStainYMeanCorner = 6.0;
			break;
		case 2:
			m_dStainYMeanEdge = _ttof((TCHAR*)(LPCTSTR)sToken);
			if(m_dStainYMeanEdge == 0.0)
				m_dStainYMeanEdge = 6.0;
			break;
		}
	}

	m_nMarkNo = GetPrivateProfileInt(_T("Vision"), _T("MarkNo"), 0, szPath);
	m_nMinMatching = GetPrivateProfileInt(_T("Vision"), _T("Mathcing"), 80, szPath);
    //
    GetPrivateProfileString(_T("ASMI_SFR_SPEC"), _T("Direction"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
    for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
    {
        AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
        m_nDirection[i] = _ttoi((TCHAR*)(LPCTSTR)sToken);

    }
	GetPrivateProfileString(_T("ASMI_SFR_SPEC"), _T("DirectionPattern"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		m_nPatternDirection[i] = _ttoi((TCHAR*)(LPCTSTR)sToken);

	}

    //m_dLinePulse
    GetPrivateProfileString(_T("LINE_PULSE"), _T("LinePulse"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
    m_dLinePulse = _ttof(szIniBuff);

	
	//m_dDemosaic
	GetPrivateProfileString(_T("DEMOSAIC"), _T("Demosaic"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_dDemosaic = _ttoi(szIniBuff);

	for (i = 0; i < 4; i++)
	{
		GetPrivateProfileString(_T("PARAMETER_ACMIS"), _T("SFR"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		sfrParameter[i] = _ttoi((TCHAR*)(LPCTSTR)sToken);

		GetPrivateProfileString(_T("PARAMETER_ACMIS"), _T("BLEMISH"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		blemishParameter[i] = _ttoi((TCHAR*)(LPCTSTR)sToken);

		GetPrivateProfileString(_T("PARAMETER_ACMIS"), _T("COLOR"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		colorParameter[i] = _ttoi((TCHAR*)(LPCTSTR)sToken);

		GetPrivateProfileString(_T("PARAMETER_ACMIS"), _T("RI"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		riParameter[i] = _ttoi((TCHAR*)(LPCTSTR)sToken);
		
	}

	m_dSfrBlackLevel = GetPrivateProfileInt(_T("PARAMETER_ACMIS"), _T("SFRBLACKLEVEL"), 0, szPath);
	m_dBlemishBlackLevel = GetPrivateProfileInt(_T("PARAMETER_ACMIS"), _T("BLEMISHBLACKLEVEL"), 0, szPath);
	m_dColorBlackLevel = GetPrivateProfileInt(_T("PARAMETER_ACMIS"), _T("COLORBLACKLEVEL"), 0, szPath);
	m_dRiBlackLevel = GetPrivateProfileInt(_T("PARAMETER_ACMIS"), _T("RIBLACKLEVEL"), 0, szPath);
	
	m_nSfr8BitUse = GetPrivateProfileInt(_T("PARAMETER_ACMIS"), _T("SFR8BITUSE"), 0, szPath);
	m_nBlemish8BitUse = GetPrivateProfileInt(_T("PARAMETER_ACMIS"), _T("BLEMISH8BITUSE"), 0, szPath);
	m_nColor8BitUse = GetPrivateProfileInt(_T("PARAMETER_ACMIS"), _T("COLOR8BITUSE"), 0, szPath);
	m_nRi8BitUse = GetPrivateProfileInt(_T("PARAMETER_ACMIS"), _T("RI8BITUSE"), 0, szPath);

	g_clLaonGrabberWrapper[m_nUnit].dSfr_Tdataspec.eDataFormat = g_clLaonGrabberWrapper[m_nUnit].rDataFormatType(sfrParameter[0]);
	g_clLaonGrabberWrapper[m_nUnit].dSfr_Tdataspec.eOutMode = g_clLaonGrabberWrapper[m_nUnit].rOutmodeType(sfrParameter[1]);
	g_clLaonGrabberWrapper[m_nUnit].dSfr_Tdataspec.eSensorType = g_clLaonGrabberWrapper[m_nUnit].rSensortypeType(sfrParameter[2]);
	g_clLaonGrabberWrapper[m_nUnit].dSfr_Tdataspec.eDemosaicMethod = g_clLaonGrabberWrapper[m_nUnit].rdemosaicmethodType(sfrParameter[3]);
	g_clLaonGrabberWrapper[m_nUnit].dSfr_Tdataspec.nBlackLevel = m_dSfrBlackLevel;

	g_clLaonGrabberWrapper[m_nUnit].dColor_Tdataspec.eDataFormat = g_clLaonGrabberWrapper[m_nUnit].rDataFormatType(colorParameter[0]);
	g_clLaonGrabberWrapper[m_nUnit].dColor_Tdataspec.eOutMode = g_clLaonGrabberWrapper[m_nUnit].rOutmodeType(colorParameter[1]);
	g_clLaonGrabberWrapper[m_nUnit].dColor_Tdataspec.eSensorType = g_clLaonGrabberWrapper[m_nUnit].rSensortypeType(colorParameter[2]);
	g_clLaonGrabberWrapper[m_nUnit].dColor_Tdataspec.eDemosaicMethod = g_clLaonGrabberWrapper[m_nUnit].rdemosaicmethodType(colorParameter[3]);
	g_clLaonGrabberWrapper[m_nUnit].dColor_Tdataspec.nBlackLevel = m_dColorBlackLevel;

	g_clLaonGrabberWrapper[m_nUnit].dBlemish_Tdataspec.eDataFormat = g_clLaonGrabberWrapper[m_nUnit].rDataFormatType(blemishParameter[0]);
	g_clLaonGrabberWrapper[m_nUnit].dBlemish_Tdataspec.eOutMode = g_clLaonGrabberWrapper[m_nUnit].rOutmodeType(blemishParameter[1]);
	g_clLaonGrabberWrapper[m_nUnit].dBlemish_Tdataspec.eSensorType = g_clLaonGrabberWrapper[m_nUnit].rSensortypeType(blemishParameter[2]);
	g_clLaonGrabberWrapper[m_nUnit].dBlemish_Tdataspec.eDemosaicMethod = g_clLaonGrabberWrapper[m_nUnit].rdemosaicmethodType(blemishParameter[3]);
	g_clLaonGrabberWrapper[m_nUnit].dBlemish_Tdataspec.nBlackLevel = m_dBlemishBlackLevel;


	g_clLaonGrabberWrapper[m_nUnit].dRi_Tdataspec.eDataFormat = g_clLaonGrabberWrapper[m_nUnit].rDataFormatType(riParameter[0]);
	g_clLaonGrabberWrapper[m_nUnit].dRi_Tdataspec.eOutMode = g_clLaonGrabberWrapper[m_nUnit].rOutmodeType(riParameter[1]);
	g_clLaonGrabberWrapper[m_nUnit].dRi_Tdataspec.eSensorType = g_clLaonGrabberWrapper[m_nUnit].rSensortypeType(riParameter[2]);
	g_clLaonGrabberWrapper[m_nUnit].dRi_Tdataspec.eDemosaicMethod = g_clLaonGrabberWrapper[m_nUnit].rdemosaicmethodType(riParameter[3]);
	g_clLaonGrabberWrapper[m_nUnit].dRi_Tdataspec.nBlackLevel = m_dRiBlackLevel;



    //sfr 작은 박스
    for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
    {
        GetPrivateProfileString(_T("SFR_ROI_OFFSET"), _T("OffsetX"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
        m_MTF_ROI_Pos[0][i].x = _ttoi((TCHAR*)(LPCTSTR)sToken);

        GetPrivateProfileString(_T("SFR_ROI_OFFSET"), _T("OffsetY"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
        m_MTF_ROI_Pos[0][i].y = _ttoi((TCHAR*)(LPCTSTR)sToken);
    }

	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		GetPrivateProfileString(_T("SFR_ROI_OFFSET2"), _T("OffsetX"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		m_MTF_ROI_Pos[1][i].x = _ttoi((TCHAR*)(LPCTSTR)sToken);

		GetPrivateProfileString(_T("SFR_ROI_OFFSET2"), _T("OffsetY"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		m_MTF_ROI_Pos[1][i].y = _ttoi((TCHAR*)(LPCTSTR)sToken);
	}
    //
    //패턴 사이즈,위치
    for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
    {
        GetPrivateProfileString(_T("PATTERN"), _T("PatternPosX"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
        m_nPatternPos[i].x = _ttoi((TCHAR*)(LPCTSTR)sToken);
    }
    for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
    {

        GetPrivateProfileString(_T("PATTERN"), _T("PatternPosY"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
        m_nPatternPos[i].y = _ttoi((TCHAR*)(LPCTSTR)sToken);
    }
    for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
    {

        GetPrivateProfileString(_T("PATTERN"), _T("PatternSizeX"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
        m_nPatternSize[i].x = _ttoi((TCHAR*)(LPCTSTR)sToken);
    }
    for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
    {

        GetPrivateProfileString(_T("PATTERN"), _T("PatternSizeY"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
        AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
        m_nPatternSize[i].y = _ttoi((TCHAR*)(LPCTSTR)sToken);
    }
    

    

}

//-----------------------------------------------------------------------------
//
//	모델 데이터 저장
//
//-----------------------------------------------------------------------------
void CModelData::Save(TCHAR* szModelName)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szData[SIZE_OF_1K];
	CString sToken;
	int i;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\DATA.ini"), BASE_DATA_PATH);
	
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dCcdCellSize);
	WritePrivateProfileString(_T("CCD_SIZE"), _T("CellSize"), szData, szPath);

	// MTF Final 모드
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nMTF_FinalMode);
	WritePrivateProfileString(_T("MTF_INSP"), _T("FinalMode"), szData, szPath);
	// CCD 반전 사용여부
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nCcdFlipUse);
	WritePrivateProfileString(_T("CCD_FLIP"), _T("Use"), szData, szPath);
	// 구형차트 사용여부
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nOldChartMTF);
	WritePrivateProfileString(_T("MTF_INSP"), _T("OldMTFUse"), szData, szPath);
	// MTF Offset 가중치
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dMTFOffset);
	WritePrivateProfileString(_T("MTF_INSP"), _T("Offset"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%.01lf"), m_dCircleThresh);
	WritePrivateProfileString(_T("CIRCLE"), _T("Threshold"), szData, szPath);


	for (i = 0; i < 2; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("AF%d"), i + 1);
		_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf / %d / %.03lf / %d / %.03lf / %d / %.03lf "),
			m_stAFInfo[i].dMoveVel, m_stAFInfo[i].dMoveAcc, m_stAFInfo[i].nDelayTime, m_stAFInfo[i].dMoveDistance, m_stAFInfo[i].nMaxStepCount, m_stAFInfo[i].fLimitRoughMTF, m_stAFInfo[i].nAvgSfrCount, m_stAFInfo[i].fLimitFineMTF);
		WritePrivateProfileString(_T("ACTIVE_ALIGN"), szIniIndex, szData, szPath);		
	}

	// CENTER SFR LIMIT
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dLimitSFRCent);
	WritePrivateProfileString(_T("SFR_LIMIT"), _T("Center"), szData, szPath);
	// 2차 AA 시작시 이동
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_d2ndAAMoveDistance);
	WritePrivateProfileString(_T("2ND_AA_MOVE"), _T("Distance"), szData, szPath);
	// CORNER SFR LIMIT
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dLimitSFRSide);
	WritePrivateProfileString(_T("SFR_LIMIT"), _T("Corner"), szData, szPath);
    //
    //
    //fov , distortion rotation 제한 spec
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dChartRotation);
	WritePrivateProfileString(_T("CHART_LIMIT"), _T("Rotation"), szData, szPath);
	
    _stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dChartHfovMin);
    WritePrivateProfileString(_T("CHART_LIMIT"), _T("HfovMin"), szData, szPath);
    _stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dChartHfovMax);
    WritePrivateProfileString(_T("CHART_LIMIT"), _T("HfovMax"), szData, szPath);
    _stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dChartVfovMin);
    WritePrivateProfileString(_T("CHART_LIMIT"), _T("VfovMin"), szData, szPath);
    _stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dChartVfovMax);
    WritePrivateProfileString(_T("CHART_LIMIT"), _T("VfovMax"), szData, szPath);
    _stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dChartDistortionMin);
    WritePrivateProfileString(_T("CHART_LIMIT"), _T("DistortionMin"), szData, szPath);
    _stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dChartDistortionMax);
    WritePrivateProfileString(_T("CHART_LIMIT"), _T("DistortionMax"), szData, szPath);

    //

    //
	_stprintf_s(szData, SIZE_OF_1K, _T("%d / %.03lf"), m_nCountOfCheckSFR, m_dSfrMoveDistance);
	WritePrivateProfileString(_T("SFR_DECREASE"), _T("Decrease"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d / %.03lf"), m_nCountOfCheckSFR, m_dSfrMoveDistance);
	WritePrivateProfileString(_T("SFR_DECREASE"), _T("Decrease"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nSfrMode);
	WritePrivateProfileString(_T("SFR_MODE"), _T("Mode"), szData, szPath);

	// SFR POSITION
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nSFR_N_POS);
	WritePrivateProfileString(_T("SFR_POS"), _T("Type"), szData, szPath);

	//_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nCOMPLETE_MODE);
	//WritePrivateProfileString(_T("COMPL_MODE"), _T("Use"), szData, szPath);


	// Laser In
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf"), m_dLaserComplMoveX[0], m_dLaserComplMoveY[0]);
	WritePrivateProfileString(_T("LASER COMPLETE"), _T("InPos"), szData, szPath);
	// Laser Out
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf"), m_dLaserComplMoveX[1], m_dLaserComplMoveY[1]);
	WritePrivateProfileString(_T("LASER COMPLETE"), _T("OutPos"), szData, szPath);

	// Laser In
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf"), m_dLaserMoveX[0], m_dLaserMoveY[0]);
	WritePrivateProfileString(_T("LASER"), _T("InPos"), szData, szPath);
	// Laser Out
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf"), m_dLaserMoveX[1], m_dLaserMoveY[1]);
	WritePrivateProfileString(_T("LASER"), _T("OutPos"), szData, szPath);



	// Stain 불량 카운트
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nStainCount[0]);
	WritePrivateProfileString(_T("STAIN"), _T("White"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nStainCount[1]);
	WritePrivateProfileString(_T("STAIN"), _T("Black"), szData, szPath);

	// UV
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_dUvTime);
	WritePrivateProfileString(_T("UV"), _T("Time"), szData, szPath);

	// PCB Z축 회피 위치
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dEscapePosPcbZ);
	WritePrivateProfileString(_T("ESCAPE_POS"), _T("PcbZ"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nSensorAlignRetryCount);
	WritePrivateProfileString(_T("ALIGN_RETRY"), _T("Sensor_Retry_Count"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nCcdRetryCount);
	WritePrivateProfileString(_T("CCD_RETRY"), _T("CCD_Retry_Count"), szData, szPath);

	

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nLensAlignRetryCount);
	WritePrivateProfileString(_T("ALIGN_RETRY"), _T("Lens_Retry_Count"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nContactRetryCount);
	WritePrivateProfileString(_T("CONTACT_RETRY"), _T("COUNT"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nLaserRetryCount);
	WritePrivateProfileString(_T("LASER_CONTROL"), _T("Retry_Count"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nDiffRetryCount);
	WritePrivateProfileString(_T("DIFF_RETRY"), _T("Retry_Count"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nRawSumCount);
	WritePrivateProfileString(_T("RAWSUM_COUNT"), _T("Rawsum_Count"), szData, szPath);

	// Delay Time 관련
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf / %.03lf / %.03lf / %.03lf / %.03lf / %.03lf / %.03lf / %.03lf / %.03lf / %.03lf"), m_dPCBVacuumDelay, m_dPCBGripDelay,
		m_dPCBGripUpDelay, m_dLaserDelay, m_dSensorAlignDelay, m_dLaserTimeOut, m_dFinalDelay, m_dBondingDelay, m_dLensAlignDelay, m_dCcdDelay, m_dDiffDelay);
	WritePrivateProfileString(_T("DelayTime"), _T("Time"), szData, szPath);

	// Align Spec
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf / %.03lf / %.03lf / %.03lf / %.03lf"), m_dSensorAlignSpec[0], m_dSensorAlignSpec[1], m_dSensorAlignSpec[2],
		m_dLensAlignSpec[0], m_dLensAlignSpec[1], m_dLensAlignSpec[2]);
	WritePrivateProfileString(_T("AlignSpec"), _T("Spec"), szData, szPath);

	// Oc Align Spec
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf"), m_dOcAlignSpec[0], m_dOcAlignSpec[1]);
	WritePrivateProfileString(_T("OcAlignSpec"), _T("Spec"), szData, szPath);

	//_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nDryRunMode);
	//WritePrivateProfileString(_T("RUN_MODE"), _T("Mode"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nUvUse);
	WritePrivateProfileString(_T("UV"), _T("Use"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nLaserInUse);
	WritePrivateProfileString(_T("LASER_IN"), _T("Use"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nLaserOutUse);
	WritePrivateProfileString(_T("LASER_OUT"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nUnloadAfter1stAAUse);
	WritePrivateProfileString(_T("UNLOAD_AFTER_1ST_AA"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nStainInspUse);
	WritePrivateProfileString(_T("STAIN_INSP"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nSaturationInspUse);
	WritePrivateProfileString(_T("SATURATION_INSP"), _T("Use"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nIRFilterInspUse);
	WritePrivateProfileString(_T("IRFILTER_INSP"), _T("Use"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nColorReproductionInspUse);
	WritePrivateProfileString(_T("COLORREPRODUCTION_INSP"), _T("Use"), szData, szPath);


	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nNgImageSaveUse);
	WritePrivateProfileString(_T("NG_IMAGE_SAVE"), _T("Use"), szData, szPath);

	

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nDarkInspUse);
	WritePrivateProfileString(_T("DARK_INSP"), _T("Use"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nMesPass);
	WritePrivateProfileString(_T("MESPASS"), _T("Use"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nCurrentUse);
	WritePrivateProfileString(_T("CURRENT_INSP"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nRITestUse);
	WritePrivateProfileString(_T("RI_INSP"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nCcdDefectInfpUse);
	WritePrivateProfileString(_T("CCD_DEFECT_INSP"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nDoorLockUse);
	WritePrivateProfileString(_T("DOOR_LOCK"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nEpoxyPass);
	WritePrivateProfileString(_T("EPOXY"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nEpoxyInspPass);
	WritePrivateProfileString(_T("EPOXY_INSP"), _T("Use"), szData, szPath);
	
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nFpsStopUse);
	WritePrivateProfileString(_T("FPS_STOP"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nPatternChartUse);
	WritePrivateProfileString(_T("PATTERN"), _T("Use"), szData, szPath);
	
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nSfrAvrCheck);
	WritePrivateProfileString(_T("SFR_AVR"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%.03f"), m_fFpsStopVal);
	WritePrivateProfileString(_T("FPS_STOP"), _T("Value"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nLaserControlLock);
	WritePrivateProfileString(_T("LASER_CONTROL"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nJxlEffort);
	WritePrivateProfileString(_T("JXL"), _T("Effort"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nDomeChartUse);
	WritePrivateProfileString(_T("DOME_CHART"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nUVLampAlarmUse);
	WritePrivateProfileString(_T("UV_LAMP_ALARM"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nAAPass);
	WritePrivateProfileString(_T("AA_PASS"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nInspectionPass);
	WritePrivateProfileString(_T("INSPECTION_PASS"), _T("Use"), szData, szPath);
	
	// Pre UV Offset
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf / %0.3lf / %.03lf / %.03lf / %.03lf"), m_dOffsetPrevUV_X, m_dOffsetPrevUV_Y, m_dOffsetPrevUV_Z,
		m_dOffsetPrevUV_Tx, m_dOffsetPrevUV_Ty, m_dOffsetPrevUV_Th);
	WritePrivateProfileString(_T("PRE_UV_OFFSET"), _T("Offset"), szData, szPath);

	// eol Offset
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf"), m_dEolPcbOffset_Tx, m_dEolPcbOffset_Ty);
	WritePrivateProfileString(_T("EOL_TILT_OFFSET"), _T("Offset"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nPinStopUse);
	WritePrivateProfileString(_T("SENSOR_COUNT"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nSensorCnt);
	WritePrivateProfileString(_T("SENSOR_COUNT"), _T("Count"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nMasterModeUse);
	WritePrivateProfileString(_T("MASTER_MODE"), _T("Use"), szData, szPath);
	
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nInspOKPass);
	WritePrivateProfileString(_T("INSP_OKPASS"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nAlignPass);
	WritePrivateProfileString(_T("ALIGN_PASS"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nRawSavePass);
	WritePrivateProfileString(_T("RAW_PASS"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nJxlSavePass);
	WritePrivateProfileString(_T("JXL_PASS"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nIdleReasonPass);
	WritePrivateProfileString(_T("IDLE_PASS"), _T("Use"), szData, szPath);
	
	// 조명값
	for (i = 0; i < MAX_LIGHT_COUNT; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("%02d"), i + 1);
		_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nLight[i]);
		WritePrivateProfileString(_T("Light"), szIniIndex, szData, szPath);
	}


	for (i = 0; i < 2; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%d"), g_clModelData[m_nUnit].m_LxData[i]);
		WritePrivateProfileString(_T("OC_MERGE"), OC_LIGHT_NAME[i], szData, szPath);
	}
	
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), g_clModelData[m_nUnit].m_LxVal);
	WritePrivateProfileString(_T("OC_MERGE"), _T("LxValue"), szData, szPath);


	
	// 보정량 LIMIT
	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf"), m_dOkLimit[i], m_dErrLimit[i]);
		WritePrivateProfileString(_T("AlignLimit"), MOTOR_NAME[i], szData, szPath);
	}
	
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_clSfrInfo.m_nCenSizeX);
	WritePrivateProfileString(_T("SFR_SIZE"), _T("CEN_SIZE_X"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_clSfrInfo.m_nCenSizeY);
	WritePrivateProfileString(_T("SFR_SIZE"), _T("CEN_SIZE_Y"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d / %d / %d / %d / %d / %d"), m_clSfrInfo.m_nSizeX[0], m_clSfrInfo.m_nSizeX[1], m_clSfrInfo.m_nSizeX[2],
		m_clSfrInfo.m_nSizeX[3], m_clSfrInfo.m_nSizeX[4], m_clSfrInfo.m_nSizeX[5], m_clSfrInfo.m_nSizeX[6], m_clSfrInfo.m_nSizeX[7], m_clSfrInfo.m_nSizeX[8]);
	WritePrivateProfileString(_T("SFR_SIZE"), _T("SizeX"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d / %d / %d / %d / %d / %d"), m_clSfrInfo.m_nSizeY[0], m_clSfrInfo.m_nSizeY[1], m_clSfrInfo.m_nSizeY[2],
		m_clSfrInfo.m_nSizeY[3], m_clSfrInfo.m_nSizeY[4], m_clSfrInfo.m_nSizeY[5], m_clSfrInfo.m_nSizeY[6], m_clSfrInfo.m_nSizeY[7], m_clSfrInfo.m_nSizeY[8]);
	WritePrivateProfileString(_T("SFR_SIZE"), _T("SizeY"), szData, szPath);

	


	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nRoiSizeX);
	WritePrivateProfileString(_T("ROI_SIZE"), _T("SIZE_X"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nRoiSizeY);
	WritePrivateProfileString(_T("ROI_SIZE"), _T("SIZE_Y"), szData, szPath);

	// 검사영역 OFFSET
	for (i = 0; i < (MAX_LAST_INSP_COUNT); i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("%02d"), i + 1);
		_stprintf_s(szData, SIZE_OF_1K, _T("%d / %d"), m_clSfrInfo.m_clPtOffset[i].x, m_clSfrInfo.m_clPtOffset[i].y);
		WritePrivateProfileString(_T("SfrOffset"), szIniIndex, szData, szPath);
	}

    for (i = 0; i < 4; i++)
    {
        // 원형마크 위치
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("POS%02d"), i + 1);
        _stprintf_s(szData, SIZE_OF_1K, _T("%d / %d"), m_clSfrInfo.m_clPtCircle[i].x, m_clSfrInfo.m_clPtCircle[i].y);
        WritePrivateProfileString(_T("CircleMark"), szIniIndex, szData, szPath);

        // 원형마크 영역
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%02d"), i + 1);
        _stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d"), m_clSfrInfo.m_clRectCircle[i].left,
            m_clSfrInfo.m_clRectCircle[i].top, m_clSfrInfo.m_clRectCircle[i].right, m_clSfrInfo.m_clRectCircle[i].bottom);
        WritePrivateProfileString(_T("CircleMark"), szIniIndex, szData, szPath);
    }
    //------------------------------------------------------------------------------
    //fov
    //------------------------------------------------------------------------------


    for (i = 0; i < VEC_FOV_COUNT; i++)
    {
        // FOV 마크 위치
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("%02d"), i + 1);
        _stprintf_s(szData, SIZE_OF_1K, _T("%d / %d"), m_clSfrInfo.m_clPtFovOffset[i].x, m_clSfrInfo.m_clPtFovOffset[i].y);
        WritePrivateProfileString(_T("FovOffset"), szIniIndex, szData, szPath);

        // FOV 마크 영역
        _stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%02d"), i + 1);
        _stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d"), m_clSfrInfo.m_clRectFov[i].left,
            m_clSfrInfo.m_clRectFov[i].top, m_clSfrInfo.m_clRectFov[i].right, m_clSfrInfo.m_clRectFov[i].bottom);
        WritePrivateProfileString(_T("FovMark"), szIniIndex, szData, szPath);
    }
	CString addStr;
	addStr.Empty();
	for (i = 0; i < VEC_FOV_COUNT; i++)
	{
		addStr.AppendFormat(_T("%d / "), m_clSfrInfo.m_nFovSizeX[i]);
	}
	_stprintf_s(szData, SIZE_OF_1K, _T("%s"), addStr);
	WritePrivateProfileString(_T("FOV_SIZE"), _T("SizeX"), szData, szPath);
	addStr.Empty();
	for (i = 0; i < VEC_FOV_COUNT; i++)
	{
		addStr.AppendFormat(_T("%d / "), m_clSfrInfo.m_nFovSizeY[i]);
	}
	_stprintf_s(szData, SIZE_OF_1K, _T("%s"), addStr);
	WritePrivateProfileString(_T("FOV_SIZE"), _T("SizeY"), szData, szPath);

	//ADD
	// FOV OC 마크 위치
	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("FOV_OC"));
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf"), m_clSfrInfo.m_dFovOcX, m_clSfrInfo.m_dFovOcY);
	WritePrivateProfileString(_T("FovMark"), szIniIndex, szData, szPath);


    //------------------------------------------------------------------------------
    //
    //------------------------------------------------------------------------------
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nMtfOverlayUse);
	WritePrivateProfileString(_T("SfrOverlay"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf / %.03lf"), m_dStainLsbCenter, m_dStainLsbCorner, m_dStainLsbEdge);
	WritePrivateProfileString(_T("StainLSB"), _T("Threshold"), szData, szPath);
	
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf / %.03lf"), m_dStainYMeanCenter, m_dStainYMeanCorner, m_dStainYMeanEdge);
	WritePrivateProfileString(_T("StainYMean"), _T("Threshold"),szData, szPath);
	
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nMarkNo);
	WritePrivateProfileString(_T("Vision"), _T("MarkNo"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nMinMatching);
	WritePrivateProfileString(_T("Vision"), _T("Mathcing"), szData, szPath);


    _stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / "), 
        m_nDirection[0], m_nDirection[1], m_nDirection[2], m_nDirection[3], m_nDirection[4], m_nDirection[5], m_nDirection[6], m_nDirection[7], m_nDirection[8], m_nDirection[9], 
        m_nDirection[10], m_nDirection[11], m_nDirection[12], m_nDirection[13], m_nDirection[14], m_nDirection[15], m_nDirection[16], m_nDirection[17], m_nDirection[18], m_nDirection[19]);
    WritePrivateProfileString(_T("ASMI_SFR_SPEC"), _T("Direction"), szData, szPath);
    
	_stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / "),
		m_nPatternDirection[0], m_nPatternDirection[1], m_nPatternDirection[2], m_nPatternDirection[3], m_nPatternDirection[4], m_nPatternDirection[5], m_nPatternDirection[6], m_nPatternDirection[7], m_nPatternDirection[8], m_nPatternDirection[9],
		m_nPatternDirection[10], m_nPatternDirection[11], m_nPatternDirection[12], m_nPatternDirection[13], m_nPatternDirection[14], m_nPatternDirection[15], m_nPatternDirection[16], m_nPatternDirection[17], m_nPatternDirection[18], m_nPatternDirection[19]);
	WritePrivateProfileString(_T("ASMI_SFR_SPEC"), _T("DirectionPattern"), szData, szPath);

    //m_dLinePulse
    _stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dLinePulse);
    WritePrivateProfileString(_T("LINE_PULSE"), _T("Linepulse"), szData, szPath);

	
	//m_dDemosaic
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_dDemosaic);
	WritePrivateProfileString(_T("DEMOSAIC"), _T("Demosaic"), szData, szPath);
	
	_stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d /"), sfrParameter[0], sfrParameter[1], sfrParameter[2], sfrParameter[3]);
	WritePrivateProfileString(_T("PARAMETER_ACMIS"), _T("SFR"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d /"), blemishParameter[0], blemishParameter[1], blemishParameter[2], blemishParameter[3]);
	WritePrivateProfileString(_T("PARAMETER_ACMIS"), _T("BLEMISH"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d /"), colorParameter[0], colorParameter[1], colorParameter[2], colorParameter[3]);
	WritePrivateProfileString(_T("PARAMETER_ACMIS"), _T("COLOR"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d /"), riParameter[0], riParameter[1], riParameter[2], riParameter[3]);
	WritePrivateProfileString(_T("PARAMETER_ACMIS"), _T("RI"), szData, szPath);
	

	//m_dBlackLevel
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_dSfrBlackLevel);
	WritePrivateProfileString(_T("PARAMETER_ACMIS"), _T("SFRBLACKLEVEL"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_dBlemishBlackLevel);
	WritePrivateProfileString(_T("PARAMETER_ACMIS"), _T("BLEMISHBLACKLEVEL"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_dColorBlackLevel);
	WritePrivateProfileString(_T("PARAMETER_ACMIS"), _T("COLORBLACKLEVEL"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_dRiBlackLevel);
	WritePrivateProfileString(_T("PARAMETER_ACMIS"), _T("RIBLACKLEVEL"), szData, szPath);
	


	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nSfr8BitUse);
	WritePrivateProfileString(_T("PARAMETER_ACMIS"), _T("SFR8BITUSE"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nBlemish8BitUse);
	WritePrivateProfileString(_T("PARAMETER_ACMIS"), _T("BLEMISH8BITUSE"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nColor8BitUse);
	WritePrivateProfileString(_T("PARAMETER_ACMIS"), _T("COLOR8BITUSE"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nRi8BitUse);
	WritePrivateProfileString(_T("PARAMETER_ACMIS"), _T("RI8BITUSE"), szData, szPath);
	
	
    //pattern
    _stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d / %d / %d / %d / %d / %d / "),
        m_nPatternPos[0].x, m_nPatternPos[1].x, m_nPatternPos[2].x, m_nPatternPos[3].x, m_nPatternPos[4].x,
        m_nPatternPos[5].x, m_nPatternPos[6].x, m_nPatternPos[7].x, m_nPatternPos[8].x);
    WritePrivateProfileString(_T("PATTERN"), _T("PatternPosX"), szData, szPath);
    _stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d / %d / %d / %d / %d / %d / "),
        m_nPatternPos[0].y, m_nPatternPos[1].y, m_nPatternPos[2].y, m_nPatternPos[3].y, m_nPatternPos[4].y,
        m_nPatternPos[5].y, m_nPatternPos[6].y, m_nPatternPos[7].y, m_nPatternPos[8].y);
    WritePrivateProfileString(_T("PATTERN"), _T("PatternPosY"), szData, szPath);
    _stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d / %d / %d / %d / %d / %d / "),
        m_nPatternSize[0].x, m_nPatternSize[1].x, m_nPatternSize[2].x, m_nPatternSize[3].x, m_nPatternSize[4].x,
        m_nPatternSize[5].x, m_nPatternSize[6].x, m_nPatternSize[7].x, m_nPatternSize[8].x);
    WritePrivateProfileString(_T("PATTERN"), _T("PatternSizeX"), szData, szPath);
    _stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d / %d / %d / %d / %d / %d / "),
        m_nPatternSize[0].y, m_nPatternSize[1].y, m_nPatternSize[2].y, m_nPatternSize[3].y, m_nPatternSize[4].y,
        m_nPatternSize[5].y, m_nPatternSize[6].y, m_nPatternSize[7].y, m_nPatternSize[8].y);
    WritePrivateProfileString(_T("PATTERN"), _T("PatternSizeY"), szData, szPath);

    //sfr roi save
    //m_MTF_ROI_Pos[i].x
    _stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / "),
        m_MTF_ROI_Pos[0][0].x, m_MTF_ROI_Pos[0][1].x, m_MTF_ROI_Pos[0][2].x, m_MTF_ROI_Pos[0][3].x, m_MTF_ROI_Pos[0][4].x, m_MTF_ROI_Pos[0][5].x, m_MTF_ROI_Pos[0][6].x, m_MTF_ROI_Pos[0][7].x, m_MTF_ROI_Pos[0][8].x, m_MTF_ROI_Pos[0][9].x,
		m_MTF_ROI_Pos[0][10].x, m_MTF_ROI_Pos[0][11].x, m_MTF_ROI_Pos[0][12].x, m_MTF_ROI_Pos[0][13].x, m_MTF_ROI_Pos[0][14].x, m_MTF_ROI_Pos[0][15].x, m_MTF_ROI_Pos[0][16].x, m_MTF_ROI_Pos[0][17].x, m_MTF_ROI_Pos[0][18].x, m_MTF_ROI_Pos[0][19].x);
    WritePrivateProfileString(_T("SFR_ROI_OFFSET"), _T("OffsetX"), szData, szPath);

    _stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / "),
		m_MTF_ROI_Pos[0][0].y, m_MTF_ROI_Pos[0][1].y, m_MTF_ROI_Pos[0][2].y, m_MTF_ROI_Pos[0][3].y, m_MTF_ROI_Pos[0][4].y, m_MTF_ROI_Pos[0][5].y, m_MTF_ROI_Pos[0][6].y, m_MTF_ROI_Pos[0][7].y, m_MTF_ROI_Pos[0][8].y, m_MTF_ROI_Pos[0][9].y,
		m_MTF_ROI_Pos[0][10].y, m_MTF_ROI_Pos[0][11].y, m_MTF_ROI_Pos[0][12].y, m_MTF_ROI_Pos[0][13].y, m_MTF_ROI_Pos[0][14].y, m_MTF_ROI_Pos[0][15].y, m_MTF_ROI_Pos[0][16].y, m_MTF_ROI_Pos[0][17].y, m_MTF_ROI_Pos[0][18].y, m_MTF_ROI_Pos[0][19].y);
    WritePrivateProfileString(_T("SFR_ROI_OFFSET"), _T("OffsetY"), szData, szPath);
	//패턴이미지
	_stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / "),
		m_MTF_ROI_Pos[1][0].x, m_MTF_ROI_Pos[1][1].x, m_MTF_ROI_Pos[1][2].x, m_MTF_ROI_Pos[1][3].x, m_MTF_ROI_Pos[1][4].x, m_MTF_ROI_Pos[1][5].x, m_MTF_ROI_Pos[1][6].x, m_MTF_ROI_Pos[1][7].x, m_MTF_ROI_Pos[1][8].x, m_MTF_ROI_Pos[1][9].x,
		m_MTF_ROI_Pos[1][10].x, m_MTF_ROI_Pos[1][11].x, m_MTF_ROI_Pos[1][12].x, m_MTF_ROI_Pos[1][13].x, m_MTF_ROI_Pos[1][14].x, m_MTF_ROI_Pos[1][15].x, m_MTF_ROI_Pos[1][16].x, m_MTF_ROI_Pos[1][17].x, m_MTF_ROI_Pos[1][18].x, m_MTF_ROI_Pos[1][19].x);
	WritePrivateProfileString(_T("SFR_ROI_OFFSET2"), _T("OffsetX"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / "),
		m_MTF_ROI_Pos[1][0].y, m_MTF_ROI_Pos[1][1].y, m_MTF_ROI_Pos[1][2].y, m_MTF_ROI_Pos[1][3].y, m_MTF_ROI_Pos[1][4].y, m_MTF_ROI_Pos[1][5].y, m_MTF_ROI_Pos[1][6].y, m_MTF_ROI_Pos[1][7].y, m_MTF_ROI_Pos[1][8].y, m_MTF_ROI_Pos[1][9].y,
		m_MTF_ROI_Pos[1][10].y, m_MTF_ROI_Pos[1][11].y, m_MTF_ROI_Pos[1][12].y, m_MTF_ROI_Pos[1][13].y, m_MTF_ROI_Pos[1][14].y, m_MTF_ROI_Pos[1][15].y, m_MTF_ROI_Pos[1][16].y, m_MTF_ROI_Pos[1][17].y, m_MTF_ROI_Pos[1][18].y, m_MTF_ROI_Pos[1][19].y);
	WritePrivateProfileString(_T("SFR_ROI_OFFSET2"), _T("OffsetY"), szData, szPath);


	this->ModelCopyBackup(szModelName);
}

bool CModelData::FinaLogCopy(TCHAR* szTempLog)
{

	return false;
	///false 일 경우엔 해당경로에 파일이 존재 하더라도 그 파일 위에 덮어쓴다.
}

void CModelData::ModelChange_ModelData()
{
	m_clSfrInfo.m_clRectFov.resize(VEC_FOV_COUNT);
	m_clSfrInfo.m_clPtFovOffset.resize(VEC_FOV_COUNT);
	m_clSfrInfo.m_nFovSizeX.resize(VEC_FOV_COUNT);
	m_clSfrInfo.m_nFovSizeY.resize(VEC_FOV_COUNT);
}
//-----------------------------------------------------------------------------
//
//	티칭 데이터 로드
//
//-----------------------------------------------------------------------------
void CModelData::LoadTeachData(TCHAR* szModelName)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken;
	int nPosi;
	int i, j;


	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\MOTOR_DATA.ini"), BASE_DATA_PATH);

	// TEACH DATA
	for (i = 0; i < MAX_POS_COUNT; i++)
	{
		GetPrivateProfileString(_T("TEACH"), POS_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		for (j = 0; j < MAX_MOTOR_COUNT; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			m_stTeachData[i].dPos[j] = _ttof((TCHAR*)(LPCTSTR)sToken);
		}
	}
}


//-----------------------------------------------------------------------------
//
//	티칭 데이터 저장
//
//-----------------------------------------------------------------------------
void CModelData::SaveTeachData(TCHAR* szModelName)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];	
	CString sToken;
	int nPosi;
	int i, j;

	

	
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\MOTOR_DATA.ini"), BASE_DATA_PATH);

	for (i = 0; i < MAX_POS_COUNT; i++)
	{
		nPosi = 0;
		for (j = 0; j < MAX_MOTOR_COUNT; j++)
		{
			_stprintf_s(&szData[nPosi], (SIZE_OF_1K - nPosi), _T("%.03lf /"), m_stTeachData[i].dPos[j]);
			nPosi = (int)_tcslen(szData);
		}
		// 마지막 /는 뺀다.
		szData[nPosi - 1] = NULL;

		WritePrivateProfileString(_T("TEACH"), POS_NAME[i], szData, szPath);
	}

	this->TeachCopyBackup(szModelName);
}


//-----------------------------------------------------------------------------
//
//	티칭 설정 파일 백업
//
//-----------------------------------------------------------------------------
void CModelData::TeachCopyBackup(TCHAR* szModelName)
{
	TCHAR szBackupPath[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];
	SYSTEMTIME stSysTime;
	CFileFind clFinder;


	GetLocalTime(&stSysTime);

	if (clFinder.FindFile(ROOT_PATH) == FALSE)
		CreateDirectory(ROOT_PATH, NULL);


	_stprintf_s(szPath, SIZE_OF_1K, _T("%s"), BASE_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup"), BASE_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup\\%04d%02d"), BASE_PATH, stSysTime.wYear, stSysTime.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup\\%04d%02d\\%02d"), BASE_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szBackupPath, SIZE_OF_1K, _T("%s\\Backup\\%04d%02d\\%02d\\MOTOR_DATA_%02d_%02d_%02d_%02d_%03d.ini"),
		BASE_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wDay, stSysTime.wHour,
		stSysTime.wMinute, stSysTime.wSecond, stSysTime.wMilliseconds);


	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\MOTOR_DATA.ini"), BASE_DATA_PATH);

	CopyFile(szPath, szBackupPath, TRUE);

}


//-----------------------------------------------------------------------------
//
//	모델 설정 파일 백업
//
//-----------------------------------------------------------------------------
void CModelData::ModelCopyBackup(TCHAR* szModelName)
{
	TCHAR szBackupPath[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];
	SYSTEMTIME stSysTime;
	CFileFind clFinder;


	GetLocalTime(&stSysTime);

	if (clFinder.FindFile(ROOT_PATH) == FALSE)
		CreateDirectory(ROOT_PATH, NULL);


	_stprintf_s(szPath, SIZE_OF_1K, _T("%s"), BASE_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);
	
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup"), BASE_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup\\%04d%02d"), BASE_PATH, stSysTime.wYear, stSysTime.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup\\%04d%02d\\%02d"), BASE_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szBackupPath, SIZE_OF_1K, _T("%s\\Backup\\%04d%02d\\%02d\\DATA_%02d_%02d_%02d_%02d_%03d.ini"),
		BASE_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wDay, stSysTime.wHour,
		stSysTime.wMinute, stSysTime.wSecond, stSysTime.wMilliseconds);


	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\DATA.ini"), BASE_DATA_PATH);

	CopyFile(szPath, szBackupPath, TRUE);

}
//-----------------------------------------------------------------------------
//
//	패턴 이미지 로드,저장
//
//-----------------------------------------------------------------------------
void CModelData::PatternLoad(TCHAR* szModelName)
{
#ifdef ON_LINE_MIL
    TCHAR szPath[SIZE_OF_1K];
    CString strType = "CHART";
    _stprintf_s(szPath, SIZE_OF_1K, _T("%s\\CHART\\CHART_Mark_0-Mask.pat"), BASE_DATA_PATH);
    MpatRestore(g_clVision.m_MilSystem[0], szPath, &g_clVision.ChartCenterPatternImage[m_nUnit]);
    for (int i = 0; i<MAX_LAST_INSP_COUNT; i++)
    {
        _stprintf_s(szPath, SIZE_OF_1K, _T("%s\\CHART\\CHART_Mark_%d-Mask.pat"), BASE_DATA_PATH, i);
        MpatRestore(g_clVision.m_MilSystem[0], szPath, &g_clVision.FieldPatternImage[m_nUnit][i]);
    }
#endif
}
void CModelData::PatternSave(TCHAR* szModelName)
{
    TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;
    int iTemp = 0;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\CHART"), BASE_DATA_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);


    for (int i = 0; i<MAX_LAST_INSP_COUNT; i++)
    {
        g_clModelData[m_nUnit].m_nPatternPos[i].x = g_clModelData[m_nUnit].m_clSfrInfo.m_clPtOffset[i].x;
        g_clModelData[m_nUnit].m_nPatternPos[i].y = g_clModelData[m_nUnit].m_clSfrInfo.m_clPtOffset[i].y;
		g_clModelData[m_nUnit].m_nPatternSize[i].x = g_clModelData[m_nUnit].m_clSfrInfo.m_nSizeX[i];
		g_clModelData[m_nUnit].m_nPatternSize[i].y = g_clModelData[m_nUnit].m_clSfrInfo.m_nSizeY[i];
        

        //g_clVision.DrawMOverlayBox(m_nCamNo, m_clRectCircle[i], M_COLOR_MAGENTA, 1, FALSE, PS_DOT);
        g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, g_clModelData[m_nUnit].m_nPatternPos[i].x, g_clModelData[m_nUnit].m_nPatternPos[i].y,
            g_clModelData[m_nUnit].m_nPatternPos[i].x + g_clModelData[m_nUnit].m_nPatternSize[i].x,
            g_clModelData[m_nUnit].m_nPatternPos[i].y + g_clModelData[m_nUnit].m_nPatternSize[i].y, PS_SOLID, M_COLOR_BLUE);

       /* MpatFree(g_clVision.ChartCenterPatternImage[m_nUnit]);
        MpatFree(g_clVision.MilTempImage[m_nUnit]);*/
        //MbufClear(g_clVision.ChartCenterPatternImage[m_nUnit], 0);
        //MbufClear(g_clVision.MilTempImage[m_nUnit], 0);
        //g_clVision.ChartCenterPatternImage[m_nUnit] = M_NULL;
        MbufAlloc2d(g_clVision.m_MilSystem[0], 
        g_clModelData[m_nUnit].m_nPatternSize[i].x, g_clModelData[m_nUnit].m_nPatternSize[i].y, (8 + M_UNSIGNED), M_IMAGE + M_DISP + M_PROC,
            &g_clVision.MilTempImage[m_nUnit]);
        //
        MpatAllocModel(g_clVision.m_MilSystem[0], g_clVision.m_MilCcdProcChild[m_nUnit][2], 
            g_clModelData[m_nUnit].m_nPatternPos[i].x, g_clModelData[m_nUnit].m_nPatternPos[i].y, 
            g_clModelData[m_nUnit].m_nPatternSize[i].x, g_clModelData[m_nUnit].m_nPatternSize[i].y, M_NORMALIZED, 
            &g_clVision.ChartCenterPatternImage[m_nUnit]);
        //MpatDraw(M_DEFAULT, Result, GraphicList, M_DRAW_BOX+M_DRAW_POSITION,  M_DEFAULT, M_DEFAULT);

		/* Set the search accuracy to high. */
		//MpatSetAccuracy(g_clVision.ChartCenterPatternImage[m_nUnit], M_HIGH);

		///* Set the search model speed to high. */
		//MpatSetSpeed(g_clVision.ChartCenterPatternImage[m_nUnit], M_HIGH);

		///* Preprocess the model. */
		//MpatPreprocModel(g_clVision.m_MilCcdProcChild[m_nUnit][2], g_clVision.ChartCenterPatternImage[m_nUnit], M_DEFAULT);
		//
		MpatDraw(M_DEFAULT, g_clVision.ChartCenterPatternImage[m_nUnit], g_clVision.MilTempImage[m_nUnit], M_DRAW_IMAGE, M_DEFAULT, M_DEFAULT);
        MpatSetCenter(g_clVision.ChartCenterPatternImage[m_nUnit], g_clModelData[m_nUnit].m_nPatternSize[i].x / 2, g_clModelData[m_nUnit].m_nPatternSize[i].y / 2);
        //저장

		


        _stprintf_s(szPath, SIZE_OF_1K, _T("%s\\CHART\\CHART_Mark_%d-Mask.pat"), BASE_DATA_PATH, i);
        MpatSave(szPath, g_clVision.ChartCenterPatternImage[m_nUnit]);

        _stprintf_s(szPath, SIZE_OF_1K, _T("%s\\CHART\\CHART_Mark_%d-Mask.bmp"), BASE_DATA_PATH,  i);
        MbufSave(szPath, g_clVision.MilTempImage[m_nUnit]);
        //
        
        MpatFree(g_clVision.ChartCenterPatternImage[m_nUnit]);
#ifdef ON_LINE_MIL
        MbufClear(g_clVision.MilTempImage[m_nUnit], 0);
#endif
    }

    g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);
	AddLog(_T("[INFO] Chart Pattern Save Complete"), 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	ACMIS LENS SHADING SPEC LOAD
//
//-----------------------------------------------------------------------------
void CModelData::LensShadingSpecLoad(TCHAR* szModelName)
{
	//TCHAR szPath[SIZE_OF_1K];
	//TCHAR szIniIndex[SIZE_OF_100BYTE];
	//TCHAR szIniBuff[SIZE_OF_1K];
	//CString sToken = _T("");
	//int i, j;

	//_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\LENS_SHADING_SPEC.ini"), BASE_DATA_PATH);
	////LENS SHADING MIN,MAX SPEC
	//for (i = 0; i < 221; i++)		//0 = R, 1 = Gr , 2 = Gb , 3 = B
	//{
	//	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d"), i + 1);
	//	//5000k
	//	GetPrivateProfileString(_T("ACMIS_LS_5000K_MIN_SPEC"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	//	for (j = 0; j < 4; j++)
	//	{
	//		AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
	//		m_LS_5000k_SpecMin[j][i] = _ttof((TCHAR*)(LPCTSTR)sToken);
	//	}
	//}
	//for (i = 0; i < 221; i++)		//0 = R, 1 = Gr , 2 = Gb , 3 = B
	//{
	//	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d"), i + 1);
	//	GetPrivateProfileString(_T("ACMIS_LS_5000K_MAX_SPEC"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	//	for (j = 0; j < 4; j++)
	//	{
	//		AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
	//		m_LS_5000k_SpecMax[j][i] = _ttof((TCHAR*)(LPCTSTR)sToken);
	//	}
	//}
	//for (i = 0; i < 221; i++)		//0 = R, 1 = Gr , 2 = Gb , 3 = B
	//{
	//	//3000K
	//	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d"), i + 1);
	//	GetPrivateProfileString(_T("ACMIS_LS_3000K_MIN_SPEC"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	//	for (j = 0; j < 4; j++)
	//	{
	//		AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
	//		m_LS_3000k_SpecMin[j][i] = _ttof((TCHAR*)(LPCTSTR)sToken);
	//	}
	//}
	//for (i = 0; i < 221; i++)		//0 = R, 1 = Gr , 2 = Gb , 3 = B
	//{
	//	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d"), i + 1);
	//	GetPrivateProfileString(_T("ACMIS_LS_3000K_MAX_SPEC"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	//	for (j = 0; j < 4; j++)
	//	{
	//		AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
	//		m_LS_3000k_SpecMax[j][i] = _ttof((TCHAR*)(LPCTSTR)sToken);
	//	}
	//}
}

void CModelData::LensShadingSpecSave(TCHAR* szModelName)
{
	//TCHAR szPath[SIZE_OF_1K];
	//TCHAR szData[SIZE_OF_1K];
	//TCHAR szIniBuff[SIZE_OF_1K];
	//TCHAR szIniIndex[SIZE_OF_100BYTE];
	//int nPosi = 0;
	//int i = 0, j = 0;

	////this->CopyBackup(szModelName);
	//_tcscpy_s(szIniBuff, SIZE_OF_1K, _T(""));
	//_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\LENS_SHADING_SPEC.ini"), BASE_DATA_PATH);
	//for (i = 0; i < 221; i++)		//0 = R, 1 = Gr , 2 = Gb , 3 = B
	//{
	//	nPosi = 0;
	//	for (j = 0; j < 4; j++) 
	//	{
	//		_stprintf_s(&szIniBuff[nPosi], (SIZE_OF_1K - nPosi), _T("%.03lf / "), m_LS_5000k_SpecMin[j][i]);
	//		nPosi = (int)(_tcslen(szIniBuff));
	//	}
	//	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d"), i + 1);
	//	WritePrivateProfileString(_T("ACMIS_LS_5000K_MIN_SPEC"), szIniIndex, szIniBuff, szPath);
	//	
	//}
	//
	//_tcscpy_s(szIniBuff, SIZE_OF_1K, _T(""));
	//for (i = 0; i < 221; i++)		//0 = R, 1 = Gr , 2 = Gb , 3 = B
	//{
	//	nPosi = 0;
	//	for (j = 0; j < 4; j++)
	//	{
	//		_stprintf_s(&szIniBuff[nPosi], (SIZE_OF_1K - nPosi), _T("%.03lf / "), m_LS_5000k_SpecMax[j][i]);
	//		nPosi = (int)(_tcslen(szIniBuff));
	//	}
	//	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d"), i + 1);
	//	WritePrivateProfileString(_T("ACMIS_LS_5000K_MAX_SPEC"), szIniIndex, szIniBuff, szPath);
	//}
	//_tcscpy_s(szIniBuff, SIZE_OF_1K, _T(""));
	//for (i = 0; i < 221; i++)		//0 = R, 1 = Gr , 2 = Gb , 3 = B
	//{
	//	nPosi = 0;
	//	for (j = 0; j < 4; j++)
	//	{
	//		_stprintf_s(&szIniBuff[nPosi], (SIZE_OF_1K - nPosi), _T("%.03lf / "), m_LS_3000k_SpecMin[j][i]);
	//		nPosi = (int)(_tcslen(szIniBuff));
	//	}
	//	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d"), i + 1);
	//	WritePrivateProfileString(_T("ACMIS_LS_3000K_MIN_SPEC"), szIniIndex, szIniBuff, szPath);
	//}
	//_tcscpy_s(szIniBuff, SIZE_OF_1K, _T(""));
	//for (i = 0; i < 221; i++)		//0 = R, 1 = Gr , 2 = Gb , 3 = B
	//{
	//	nPosi = 0;
	//	for (j = 0; j < 4; j++)
	//	{
	//		_stprintf_s(&szIniBuff[nPosi], (SIZE_OF_1K - nPosi), _T("%.03lf / "), m_LS_3000k_SpecMax[j][i]);
	//		nPosi = (int)(_tcslen(szIniBuff));
	//	}
	//	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("ROI%d"), i + 1);
	//	WritePrivateProfileString(_T("ACMIS_LS_3000K_MAX_SPEC"), szIniIndex, szIniBuff, szPath);
	//}
}
//-----------------------------------------------------------------------------
//
//	ACMIS Dll Spec 로드,저장
//
//-----------------------------------------------------------------------------
void CModelData::AcmisDataLoad(TCHAR* szModelName)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i, j;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\ACMIS_DATA.ini"), BASE_DATA_PATH);

	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//Relative Illumination 
	//int IlluminationMax = g_Ricount;
	//for (i = 0; i < IlluminationMax; i++)
	//{
	//	GetPrivateProfileString(_T("ACMIS_RI"), RI_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	//	m_RISpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	//}
	////-------------------------------------------------------------------------------------------------------------------------------------
	////-------------------------------------------------------------------------------------------------------------------------------------
	////Color Shadings
	//int mColorShadingMax = g_ColorShadingcount;
	//for (i = 0; i < mColorShadingMax; i++)
	//{
	//	GetPrivateProfileString(_T("ACMIS_COLOR_SHADING"), COLOR_SHADING_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	//	m_ColorShadingSpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	//}
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	

	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//STAIN

	/*int lcbMax = g_StainLcbcount;
	for (i = 0; i < lcbMax; i++)
	{
		GetPrivateProfileString(_T("ACMIS_LCB"), STAIN_LCB_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_LcbSpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}
	int ymeanMax = g_StainYmeancount;
	for (i = 0; i < ymeanMax; i++)
	{
		GetPrivateProfileString(_T("ACMIS_YMEAN"), STAIN_YMEAN_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_YmeanSpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}

	int fdfMax = g_StainFdfcount;
	for (i = 0; i < fdfMax; i++)
	{
		GetPrivateProfileString(_T("ACMIS_FDF"), STAIN_FDF_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_FDFSpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}
	
	*/
	for (i = 0; i < 4; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("Offset%d"), i + 1);
		GetPrivateProfileString(_T("ACMIS_LCB"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_LcbOffsetSpec[i] = _ttoi((TCHAR*)(LPCTSTR)szIniBuff);

		GetPrivateProfileString(_T("ACMIS_YMEAN"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_YmeanOffsetSpec[i] = _ttoi((TCHAR*)(LPCTSTR)szIniBuff);

		GetPrivateProfileString(_T("ACMIS_FDF"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_FDFOffsetSpec[i] = _ttoi((TCHAR*)(LPCTSTR)szIniBuff);
	}


	////-------------------------------------------------------------------------------------------------------------------------------------
	////-------------------------------------------------------------------------------------------------------------------------------------
	////IF FILTER
	//int irMax = g_Ircount;
	//for (i = 0; i < irMax; i++)
	//{
	//	GetPrivateProfileString(_T("ACMIS_IRFILTER"), IRFILTER_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	//	m_IrFilterSpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	//}
	////-------------------------------------------------------------------------------------------------------------------------------------
	////-------------------------------------------------------------------------------------------------------------------------------------
	////COLOR REPRODUCTION
	//for (i = 0; i < 32; i++)
	//{
	//	GetPrivateProfileString(_T("ACMIS_COLOR_REPRODUCTION"), COLOR_REPRODUCTION_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	//	m_ColorReproductionSpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	//}

	////-------------------------------------------------------------------------------------------------------------------------------------
	////-------------------------------------------------------------------------------------------------------------------------------------
	//int CurrentMax = g_Currentcount;
	//for (i = 0; i < CurrentMax; i++)
	//{
	//	GetPrivateProfileString(_T("ACMIS_CURRENT"), CURRENT_SPEC_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	//	m_CurrentSpec[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	//}
    //-------------------------------------------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------------------------------------------
	return;
}
void CModelData::AcmisDataSave(TCHAR* szModelName)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];
    TCHAR szIniBuff[SIZE_OF_1K];
    TCHAR szIniIndex[SIZE_OF_100BYTE];
	int nPosi = 0;
	int i=0, j=0;

	//this->CopyBackup(szModelName);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\ACMIS_DATA.ini"), BASE_DATA_PATH);

	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//Relative Illumination 
	//int IlluminationMax = g_Ricount;// sizeof(RI_SPEC_NAME) / sizeof(RI_SPEC_NAME[0]);
	//for (i = 0; i < IlluminationMax; i++)
	//{
	//	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_RISpec[i]);
	//	WritePrivateProfileString(_T("ACMIS_RI"), RI_SPEC_NAME[i], szData, szPath);
	//}
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//Color Shading
	//int mColorShadingMax = g_ColorShadingcount;// sizeof(COLOR_SHADING_SPEC_NAME) / sizeof(COLOR_SHADING_SPEC_NAME[0]);
	//for (i = 0; i < mColorShadingMax; i++)
	//{
	//	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_ColorShadingSpec[i]);
	//	WritePrivateProfileString(_T("ACMIS_COLOR_SHADING"), COLOR_SHADING_SPEC_NAME[i], szData, szPath);
	//}


	//
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//stain
    //
	//for (i = 0; i < g_StainLcbcount; i++)
	//{
	//	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_LcbSpec[i]);
	//	WritePrivateProfileString(_T("ACMIS_LCB"), STAIN_LCB_SPEC_NAME[i], szData, szPath);
	//}
 //   //
	//for (i = 0; i < g_StainYmeancount; i++)
	//{
	//	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_YmeanSpec[i]);
	//	WritePrivateProfileString(_T("ACMIS_YMEAN"), STAIN_YMEAN_SPEC_NAME[i], szData, szPath);
	//}

	//for (i = 0; i < g_StainFdfcount; i++)
	//{
	//	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_FDFSpec[i]);
	//	WritePrivateProfileString(_T("ACMIS_FDF"), STAIN_FDF_SPEC_NAME[i], szData, szPath);
	//}

	for (i = 0; i < 4; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("Offset%d"), i + 1);
		_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_LcbOffsetSpec[i]);
		WritePrivateProfileString(_T("ACMIS_LCB"), szIniIndex, szData, szPath);

		_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_YmeanOffsetSpec[i]);
		WritePrivateProfileString(_T("ACMIS_YMEAN"), szIniIndex, szData, szPath);

		_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_FDFOffsetSpec[i]);
		WritePrivateProfileString(_T("ACMIS_FDF"), szIniIndex, szData, szPath);
	}
	
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//IR FILTER
	/*for (i = 0; i < g_Ircount; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_IrFilterSpec[i]);
		WritePrivateProfileString(_T("ACMIS_IRFILTER"), IRFILTER_SPEC_NAME[i], szData, szPath);
	}*/
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//전류측정
	/*int CurrentMax = g_Currentcount;
	for (i = 0; i < CurrentMax; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_CurrentSpec[i]);
		WritePrivateProfileString(_T("ACMIS_CURRENT"), CURRENT_SPEC_NAME[i], szData, szPath);
	}*/
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------
	//COLOR REPRODUCTION
	/*for (i = 0; i < 32; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.06lf"), m_ColorReproductionSpec[i]);
		WritePrivateProfileString(_T("ACMIS_COLOR_REPRODUCTION"), COLOR_REPRODUCTION_SPEC_NAME[i], szData, szPath);
	}*/

}


//-----------------------------------------------------------------------------
//
//	LOT 로드,저장
//
//-----------------------------------------------------------------------------
void CModelData::LotDataLoad()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i = 0;
	int j = 0;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\LOT_DATA.ini"), BASE_DATA_PATH);

	GetPrivateProfileString(_T("BCR"), _T("LOT"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	g_clMesCommunication[m_nUnit].m_sMesLotID.Format(_T("%s"), (TCHAR*)(LPCTSTR)szIniBuff);	//lotload

	_stprintf_s(g_clTaskWork[m_nUnit].m_szChipID, SIZE_OF_100BYTE, g_clMesCommunication[m_nUnit].m_sMesLotID);
}

void CModelData::LotDataSave()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];
	TCHAR szIniBuff[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	int nPosi = 0;
	int i = 0, j = 0;

	//this->CopyBackup(szModelName);  <---도포용추가해라

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\LOT_DATA.ini"), BASE_DATA_PATH);


	//_stprintf_s(szData, SIZE_OF_1K, _T("%s"), g_clMesCommunication[m_nUnit].m_sMesLotID);
	_stprintf_s(szData, SIZE_OF_1K, _T("%s"), g_clTaskWork[m_nUnit].m_szChipID);
	WritePrivateProfileString(_T("BCR"), _T("LOT"), szData, szPath);

}


//-----------------------------------------------------------------------------
//
//	Epoxy 로드,저장
//
//-----------------------------------------------------------------------------
void CModelData::EpoxyDataLoad(TCHAR* szModelName)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i = 0;
	int j = 0;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\AA%d\\EPOXY_DATA.ini"), BASE_DATA_PATH, m_nUnit + 1);

	GetPrivateProfileString(_T("EPOXY"), _T("LINE_SPEED"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_EpoxyLineSpeed = _ttof((TCHAR*)(LPCTSTR)szIniBuff);

	GetPrivateProfileString(_T("EPOXY"), _T("CURVE_SPEED"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_EpoxyCurveSpeed = _ttof((TCHAR*)(LPCTSTR)szIniBuff);

	GetPrivateProfileString(_T("EPOXY"), _T("LINE_ACC_DEC"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_EpoxyLineAccDec = _ttof((TCHAR*)(LPCTSTR)szIniBuff);

	GetPrivateProfileString(_T("EPOXY"), _T("CURVE_ACC_DEC"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_EpoxyCurveAccDec = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	
	GetPrivateProfileString(_T("EPOXY"), _T("ON_TIME"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_EpoxyOnTime = _ttof((TCHAR*)(LPCTSTR)szIniBuff);

	GetPrivateProfileString(_T("EPOXY"), _T("OFF_TIME"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_EpoxyOffTime = _ttof((TCHAR*)(LPCTSTR)szIniBuff);

	

	//도포 길이

	for (i = 0; i < 4; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("LINE_LENGTH%d"), i + 1);
		GetPrivateProfileString(_T("EPOXY"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_EpoxyLineLength[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}

	for (i = 0; i < 4; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CURVE_CENTER_X_POINT%d"), i + 1);
		GetPrivateProfileString(_T("EPOXY"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_EpoxyCurveCenterXPoint[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CURVE_CENTER_Y_POINT%d"), i + 1);
		GetPrivateProfileString(_T("EPOXY"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_EpoxyCurveCenterYPoint[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
		//
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CURVE_END_X_POINT%d"), i + 1);
		GetPrivateProfileString(_T("EPOXY"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_EpoxyCurveEndXPoint[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CURVE_END_Y_POINT%d"), i + 1);
		GetPrivateProfileString(_T("EPOXY"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		m_EpoxyCurveEndYPoint[i] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);

	}


	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("EPOXY_INSP_RECT_LEFT"));
	GetPrivateProfileString(_T("EPOXY INSP"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	if (_tcslen(szIniBuff) > 0)
	{

		for (j = 0; j < 4; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		m_ResingRectStart[0].x = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
			case 1:		m_ResingRectStart[0].y = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
			case 2:		m_ResingRectSize[0].x = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
			case 3:		m_ResingRectSize[0].y = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
			}
		}
	}

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("EPOXY_INSP_RECT_RIGHT"));
	GetPrivateProfileString(_T("EPOXY INSP"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	if (_tcslen(szIniBuff) > 0)
	{

		for (j = 0; j < 4; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		m_ResingRectStart[1].x = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
			case 1:		m_ResingRectStart[1].y = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
			case 2:		m_ResingRectSize[1].x = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
			case 3:		m_ResingRectSize[1].y = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
			}
		}
	}

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("EPOXY_INSP_RECT_TOP"));
	GetPrivateProfileString(_T("EPOXY INSP"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	if (_tcslen(szIniBuff) > 0)
	{

		for (j = 0; j < 4; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		m_ResingRectStart[2].x = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
			case 1:		m_ResingRectStart[2].y = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
			case 2:		m_ResingRectSize[2].x = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
			case 3:		m_ResingRectSize[2].y = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
			}
		}
	}

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("EPOXY_INSP_RECT_BOTTOM"));
	GetPrivateProfileString(_T("EPOXY INSP"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	if (_tcslen(szIniBuff) > 0)
	{
		for (j = 0; j < 4; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		m_ResingRectStart[3].x = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
			case 1:		m_ResingRectStart[3].y = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
			case 2:		m_ResingRectSize[3].x = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
			case 3:		m_ResingRectSize[3].y = _ttoi((TCHAR*)(LPCTSTR)sToken);		break;
			}
		}
	}

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("RESIN_DRAW_CENTER"));
	GetPrivateProfileString(_T("EPOXY INSP"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	if (_tcslen(szIniBuff) > 0)
	{
		for (j = 0; j < 8; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		m_CircleDrawCenter[0].x = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 1:		m_CircleDrawCenter[0].y = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 2:		m_CircleDrawCenter[1].x = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 3:		m_CircleDrawCenter[1].y = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 4:		m_CircleDrawCenter[2].x = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 5:		m_CircleDrawCenter[2].y = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 6:		m_CircleDrawCenter[3].x = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 7:		m_CircleDrawCenter[3].y = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			}
		}
	}

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CIRCLE_DRAW_SIZE_LT"));
	GetPrivateProfileString(_T("EPOXY INSP"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	if (_tcslen(szIniBuff) > 0)
	{
		for (j = 0; j < 2; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		m_CircleDrawSize[0].x = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 1:		m_CircleDrawSize[0].y = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			}
		}
	}

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CIRCLE_DRAW_SIZE_RT"));
	GetPrivateProfileString(_T("EPOXY INSP"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	if (_tcslen(szIniBuff) > 0)
	{
		for (j = 0; j < 2; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		m_CircleDrawSize[1].x = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 1:		m_CircleDrawSize[1].y = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			}
		}
	}

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CIRCLE_DRAW_SIZE_LB"));
	GetPrivateProfileString(_T("EPOXY INSP"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	if (_tcslen(szIniBuff) > 0)
	{
		for (j = 0; j < 2; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		m_CircleDrawSize[2].x = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 1:		m_CircleDrawSize[2].y = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			}
		}
	}

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CIRCLE_DRAW_SIZE_RB"));
	GetPrivateProfileString(_T("EPOXY INSP"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	if (_tcslen(szIniBuff) > 0)
	{
		for (j = 0; j < 2; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		m_CircleDrawSize[3].x = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 1:		m_CircleDrawSize[3].y = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			}
		}
	}


	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("RESIN_DRAW_SIZE"));
	GetPrivateProfileString(_T("EPOXY INSP"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	if (_tcslen(szIniBuff) > 0)
	{
		for (j = 0; j < 2; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		m_ResinDrawSize.x = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 1:		m_ResinDrawSize.y = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			}
		}
	}

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("RESIN_INSP_OFFSET"));
	GetPrivateProfileString(_T("EPOXY INSP"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	if (_tcslen(szIniBuff) > 0)
	{
		for (j = 0; j < 4; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		m_dResinInspOffset[0].x = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 1:		m_dResinInspOffset[0].y = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 2:		m_dResinInspOffset[1].x = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 3:		m_dResinInspOffset[1].y = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			}
		}
	}

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("RESIN_INSP_SPEC"));
	GetPrivateProfileString(_T("EPOXY INSP"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	if (_tcslen(szIniBuff) > 0)
	{
		for (j = 0; j < 3; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			switch (j)
			{
			case 0:		m_dResinInspHoleSpec = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 1:		m_dResinInspGapLength = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			case 2:		m_dResinInspRectSpec = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
			}
		}
	}
	m_nResinInspLimit = GetPrivateProfileInt(_T("EPOXY INSP"), _T("RESIN_INSP_LIMIT"), 0, szPath);

}

void CModelData::EpoxyDataSave(TCHAR* szModelName)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];
	TCHAR szIniBuff[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	int nPosi = 0;
	int i = 0, j = 0;

	//this->CopyBackup(szModelName);  <---도포용추가해라

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\AA%d\\EPOXY_DATA.ini"), BASE_DATA_PATH, m_nUnit + 1);


	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_EpoxyLineSpeed);
	WritePrivateProfileString(_T("EPOXY"), _T("LINE_SPEED"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_EpoxyCurveSpeed);
	WritePrivateProfileString(_T("EPOXY"), _T("CURVE_SPEED"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_EpoxyLineAccDec);
	WritePrivateProfileString(_T("EPOXY"), _T("LINE_ACC_DEC"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_EpoxyCurveAccDec);
	WritePrivateProfileString(_T("EPOXY"), _T("CURVE_ACC_DEC"), szData, szPath);
	
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_EpoxyOnTime);
	WritePrivateProfileString(_T("EPOXY"), _T("ON_TIME"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_EpoxyOffTime);
	WritePrivateProfileString(_T("EPOXY"), _T("OFF_TIME"), szData, szPath);

	

	for (i = 0; i < 4; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("LINE_LENGTH%d"), i + 1);
		_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_EpoxyLineLength[i]);
		WritePrivateProfileString(_T("EPOXY"), szIniIndex, szData, szPath);
	}

	for (i = 0; i < 4; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CURVE_CENTER_X_POINT%d"), i + 1);
		_stprintf_s(szData, SIZE_OF_1K, _T("%.02lf"), m_EpoxyCurveCenterXPoint[i]);
		WritePrivateProfileString(_T("EPOXY"), szIniIndex, szData, szPath);
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CURVE_CENTER_Y_POINT%d"), i + 1);
		_stprintf_s(szData, SIZE_OF_1K, _T("%.02lf"), m_EpoxyCurveCenterYPoint[i]);
		WritePrivateProfileString(_T("EPOXY"), szIniIndex, szData, szPath);
		//
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CURVE_END_X_POINT%d"), i + 1);
		_stprintf_s(szData, SIZE_OF_1K, _T("%.02lf"), m_EpoxyCurveEndXPoint[i]);
		WritePrivateProfileString(_T("EPOXY"), szIniIndex, szData, szPath);
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CURVE_END_Y_POINT%d"), i + 1);
		_stprintf_s(szData, SIZE_OF_1K, _T("%.02lf"), m_EpoxyCurveEndYPoint[i]);
		WritePrivateProfileString(_T("EPOXY"), szIniIndex, szData, szPath);

	}


	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("EPOXY_INSP_RECT_LEFT"));
	_stprintf_s(szIniBuff, SIZE_OF_1K, _T("%d / %d / %d/ %d"), m_ResingRectStart[0].x, m_ResingRectStart[0].y, m_ResingRectSize[0].x, m_ResingRectSize[0].y);
	WritePrivateProfileString(_T("EPOXY INSP"), szIniIndex, szIniBuff, szPath);

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("EPOXY_INSP_RECT_RIGHT"));
	_stprintf_s(szIniBuff, SIZE_OF_1K, _T("%d / %d / %d/ %d"), m_ResingRectStart[1].x, m_ResingRectStart[1].y, m_ResingRectSize[1].x, m_ResingRectSize[1].y);
	WritePrivateProfileString(_T("EPOXY INSP"), szIniIndex, szIniBuff, szPath);

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("EPOXY_INSP_RECT_TOP"));
	_stprintf_s(szIniBuff, SIZE_OF_1K, _T("%d / %d / %d/ %d"), m_ResingRectStart[2].x, m_ResingRectStart[2].y, m_ResingRectSize[2].x, m_ResingRectSize[2].y);
	WritePrivateProfileString(_T("EPOXY INSP"), szIniIndex, szIniBuff, szPath);

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("EPOXY_INSP_RECT_BOTTOM"));
	_stprintf_s(szIniBuff, SIZE_OF_1K, _T("%d / %d / %d/ %d"), m_ResingRectStart[3].x, m_ResingRectStart[3].y, m_ResingRectSize[3].x, m_ResingRectSize[3].y);
	WritePrivateProfileString(_T("EPOXY INSP"), szIniIndex, szIniBuff, szPath);

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("RESIN_DRAW_CENTER"));
	_stprintf_s(szIniBuff, SIZE_OF_1K, _T("%lf / %lf / %lf / %lf / %lf / %lf / %lf / %lf"), 
		m_CircleDrawCenter[0].x, m_CircleDrawCenter[0].y, m_CircleDrawCenter[1].x, m_CircleDrawCenter[1].y, 
		m_CircleDrawCenter[2].x, m_CircleDrawCenter[2].y, m_CircleDrawCenter[3].x, m_CircleDrawCenter[3].y);
	WritePrivateProfileString(_T("EPOXY INSP"), szIniIndex, szIniBuff, szPath);

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CIRCLE_DRAW_SIZE_LT"));
	_stprintf_s(szIniBuff, SIZE_OF_1K, _T("%lf / %lf"), m_CircleDrawSize[0].x, m_CircleDrawSize[0].y);
	WritePrivateProfileString(_T("EPOXY INSP"), szIniIndex, szIniBuff, szPath);

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CIRCLE_DRAW_SIZE_RT"));
	_stprintf_s(szIniBuff, SIZE_OF_1K, _T("%lf / %lf"), m_CircleDrawSize[1].x, m_CircleDrawSize[1].y);
	WritePrivateProfileString(_T("EPOXY INSP"), szIniIndex, szIniBuff, szPath);

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CIRCLE_DRAW_SIZE_LB"));
	_stprintf_s(szIniBuff, SIZE_OF_1K, _T("%lf / %lf"), m_CircleDrawSize[2].x, m_CircleDrawSize[2].y);
	WritePrivateProfileString(_T("EPOXY INSP"), szIniIndex, szIniBuff, szPath);

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("CIRCLE_DRAW_SIZE_RB"));
	_stprintf_s(szIniBuff, SIZE_OF_1K, _T("%lf / %lf"), m_CircleDrawSize[3].x, m_CircleDrawSize[3].y);
	WritePrivateProfileString(_T("EPOXY INSP"), szIniIndex, szIniBuff, szPath);

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("RESIN_DRAW_SIZE"));
	_stprintf_s(szIniBuff, SIZE_OF_1K, _T("%lf / %lf"), m_ResinDrawSize.x, m_ResinDrawSize.y);
	WritePrivateProfileString(_T("EPOXY INSP"), szIniIndex, szIniBuff, szPath);

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("RESIN_INSP_OFFSET"));
	_stprintf_s(szIniBuff, SIZE_OF_1K, _T("%lf / %lf / %lf / %lf"), m_dResinInspOffset[0].x, m_dResinInspOffset[0].y, m_dResinInspOffset[1].x, m_dResinInspOffset[1].y);
	WritePrivateProfileString(_T("EPOXY INSP"), szIniIndex, szIniBuff, szPath);


	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nResinInspLimit);
	WritePrivateProfileString(_T("EPOXY INSP"), _T("RESIN_INSP_LIMIT"), szData, szPath);

	_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("RESIN_INSP_SPEC"));
	_stprintf_s(szIniBuff, SIZE_OF_1K, _T("%f / %f / %f"), m_dResinInspHoleSpec, m_dResinInspGapLength, m_dResinInspRectSpec);
	WritePrivateProfileString(_T("EPOXY INSP"), szIniIndex, szIniBuff, szPath);


}
	//-------------------------------------------------------------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
//
//	Mark Data
//

//-----------------------------------------------------------------------------
//
//	생성자
//
//-----------------------------------------------------------------------------
CMarkData::CMarkData(void)
{
	int i;

	for (i = 0; i < MAX_MARK_COUNT; i++)
	{
		m_nSmooth[i] = 50;
		m_clRectRoi[i].left = m_clRectRoi[i].top = 10;
		m_clRectRoi[i].right = m_clRectRoi[i].bottom = 50;
	}
}

//-----------------------------------------------------------------------------
//
//	소멸자
//
//-----------------------------------------------------------------------------
CMarkData::~CMarkData(void)
{

}

//-----------------------------------------------------------------------------
//
//	마크 데이터 로드
//
//-----------------------------------------------------------------------------
void CMarkData::LoadData(TCHAR* szModelName)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	int i;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\MarkData.ini"), BASE_DATA_PATH);
	for (i = 0; i < MAX_MARK_COUNT; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("Mark%02d"), i + 1);
		m_nSmooth[i] = GetPrivateProfileInt(_T("SMOOTH"), szIniIndex, 50, szPath);

		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("Mark%02d_Top"), i + 1);
		m_clRectRoi[i].top = GetPrivateProfileInt(_T("ROI"), szIniIndex, 0, szPath);

		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("Mark%02d_Left"), i + 1);
		m_clRectRoi[i].left = GetPrivateProfileInt(_T("ROI"), szIniIndex, 0, szPath);

		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("Mark%02d_Right"), i + 1);
		m_clRectRoi[i].right = GetPrivateProfileInt(_T("ROI"), szIniIndex, 0, szPath);

		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("Mark%02d_Bottom"), i + 1);
		m_clRectRoi[i].bottom = GetPrivateProfileInt(_T("ROI"), szIniIndex, 0, szPath);
	}
}

//-----------------------------------------------------------------------------
//
//	마크 데이터 저장
//
//-----------------------------------------------------------------------------
void CMarkData::SaveData(TCHAR* szModelName)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szData[SIZE_OF_100BYTE];
	int i;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\MarkData.ini"), BASE_DATA_PATH);
	for (i = 0; i < MAX_MARK_COUNT; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("Mark%02d"), i + 1);
		_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), m_nSmooth[i]);
		WritePrivateProfileString(_T("SMOOTH"), szIniIndex, szData, szPath);

		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("Mark%02d_Top"), i + 1);
		_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), m_clRectRoi[i].top);
		WritePrivateProfileString(_T("ROI"), szIniIndex, szData, szPath);

		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("Mark%02d_Left"), i + 1);
		_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), m_clRectRoi[i].left);
		WritePrivateProfileString(_T("ROI"), szIniIndex, szData, szPath);

		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("Mark%02d_Right"), i + 1);
		_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), m_clRectRoi[i].right);
		WritePrivateProfileString(_T("ROI"), szIniIndex, szData, szPath);

		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("Mark%02d_Bottom"), i + 1);
		_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), m_clRectRoi[i].bottom);
		WritePrivateProfileString(_T("ROI"), szIniIndex, szData, szPath);
	}

	this->CopyBackup(szModelName);
}

//-----------------------------------------------------------------------------
//
//	백업 복사
//
//-----------------------------------------------------------------------------
void CMarkData::CopyBackup(TCHAR* szModelName)
{
	TCHAR szBackupPath[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];
	SYSTEMTIME stSysTime;
	CFileFind clFinder;

	GetLocalTime(&stSysTime);

	if (clFinder.FindFile(BASE_DATA_PATH) == FALSE)
		CreateDirectory(BASE_DATA_PATH, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup"), BASE_DATA_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup\\%s"), BASE_DATA_PATH, szModelName);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup\\%s\\%04d%02d"), BASE_DATA_PATH, szModelName, stSysTime.wYear, stSysTime.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup\\%s\\%04d%02d\\%02d"), BASE_DATA_PATH, szModelName, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Backup\\%s\\%04d%02d\\%02d\\AA%d"), BASE_DATA_PATH, szModelName, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, m_nUnit + 1);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szBackupPath, SIZE_OF_1K, _T("%s\\Backup\\%s\\%04d%02d\\%02d\\AA%d\\MarkData_%02d_%02d_%02d_%03d.ini"),
		BASE_DATA_PATH, szModelName, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, m_nUnit + 1, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond, stSysTime.wMilliseconds);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\MarkData.ini"), BASE_DATA_PATH);

	CopyFile(szPath, szBackupPath, TRUE);
}



//-----------------------------------------------------------------------------
//
//	Task 생성자
//
//-----------------------------------------------------------------------------
CTaskWork::CTaskWork()
{
	int i;

	bRecv_Lgit_Pp_select = -1;
	bRecv_S6F12_Process_State_Change = -1;
	bRecv_S6F12_PP_Selected = -1;
	bRecv_S7F25_Formatted_Process_Program = -1;
	bRecv_S2F49_PP_UpLoad_Confirm = -1;
	bRecv_S6F12_PP_UpLoad_Completed = -1;
	bRecv_S2F49_LG_Lot_Start = -1;
	bRecv_S6F12_Lot_Processing_Started = -1;
	bRecv_S6F12_Lot_Apd = -1;
	bRecv_S6F12_Lot_Processing_Completed = -1;
	bRecv_S6F12_Lot_Processing_Completed_Ack = -1;
	//
	//
	m_nAutoFlag = MODE_STOP;
	m_nStartStep = 0;
	m_nEndStep = 0;
	m_nStartLensStep = 0;
	m_nEndLensStep = 0;
	m_bAreaSensorRun = false;
	bIdleTimeExceed = false;
	mRepetCount = 0;
	m_nCurrentPcbStep = 0;
	mVariationIndex = 0;
	m_nCurrentLensStep = 0;
	m_LightTimeCheck = 0;
	m_nDrawBarStep = 0;
	m_nCountOfStepAA = 0;
	m_nCountOfTotalStepAA = 0;
	m_nCountOfSecondStepAA = 0;
	m_bFlagDecreaseSFR = false;
	m_bRecvMesBcr = false;

	m_ManualMarkIndex = SENSOR_ALIGN_MARK;
	m_bDispenseCompleteCheck = false;
	m_bLensLaserCompleteCheck = false;
//	memset(&m_stOsCheck, 0x00, sizeof(m_stOsCheck));
	memset(&m_stSfrInsp, 0x00, sizeof(m_stSfrInsp));
//	memset(&m_stDefectInsp, 0x00, sizeof(m_stDefectInsp));

	for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
	{
		m_stSfrInsp.mChartRectFind[i] = false;
	}
	
	

	m_clOpticalRoi.left = (LONG)(g_clModelData[m_nUnit].m_nWidth * 0.1 + 0.5);
	m_clOpticalRoi.top = (LONG)((g_clModelData[m_nUnit].m_nHeight/* - 4*/) * 0.1 + 0.5);
	m_clOpticalRoi.right = (LONG)(g_clModelData[m_nUnit].m_nWidth * 0.9 + 0.5);
	m_clOpticalRoi.bottom = (LONG)((g_clModelData[m_nUnit].m_nHeight/* - 4*/) * 0.9 + 0.5);
	
	m_nTotalWorkCount = 0;
	m_nTotalOkCount = 0;
	m_nTotalNgCount = 0;
	m_nUsePinCount = 0;

	m_dwCycleTactStartTime = 0;
	m_dwCycleTactEndTime = 0;

	m_nMTFNgCount = 0;
	m_nOCNgCount = 0;
	m_nDistortionNgCount = 0;
	m_nCurrentNgCount = 0;
	m_nTestPatternNgCount = 0;
	m_nDefectInspNgCount = 0;
	m_nStainInspNgCount = 0;
	m_nDarkInspNgCount = 0;
	m_nUniformityNgCount = 0;

	m_dDataOffsetX[0] = m_dDataOffsetX[1] = 0.0;
	m_dDataOffsetY[0] = m_dDataOffsetY[1] = 0.0;
	m_dDataOffsetTh[0] = m_dDataOffsetTh[1] = 0.0;

	m_dTotalTactTime = 0.0;
	m_dAlignTackTime = 0.0;
	m_dLaserTactTime = 0.0;
	m_dAATactTime = 0.0;
	m_dInspTactTime = 0.0;

	/*m_bFlagMoveLensBonding = false;
	m_bFlagMoveLensComplete = false;
	m_bFlagMoveLensLoading = false;*/
	m_IoRetry = 0;
	m_ContactCount = 0;
	m_bLensTransferChk = false;
	m_bWaitLensBonding = false;
	m_bMovingLens = false;		
	m_bMoveLensLoading = false;

	m_bLensMovePickup = false;
	m_bLensBufferLensOn = false;
	m_nComplType = 0;

	m_nEmission = 0;
	m_nEmissionRun = false;
	m_nEpoxyCompl = 0;
	m_nLensLoading = 0;
	m_nRetryCount = 0;

	m_nWideCenterRetryCount = 0;
	grabFailCount = 0;
	_stprintf_s(m_szChipID, SIZE_OF_100BYTE, _T("EMPTY"));
	_stprintf_s(m_szLotID, SIZE_OF_100BYTE, _T("EMPTY"));
	_stprintf_s(m_szI2cSensorLot, SIZE_OF_100BYTE, _T("EMPTY"));
	_stprintf_s(m_szFuseId, SIZE_OF_100BYTE, _T("EMPTY"));
	_stprintf_s(m_szManufacturerSerialNumber, SIZE_OF_100BYTE, _T("EMPTY"));
	_stprintf_s(m_szRivianPartNumber, SIZE_OF_100BYTE, _T("EMPTY"));


	_stprintf_s(m_szIdleStartTime, SIZE_OF_100BYTE, _T(""));
	_stprintf_s(m_szIdleEndTime, SIZE_OF_100BYTE, _T(""));


	_stprintf_s(m_szBinaryFile, SIZE_OF_100BYTE, _T("EMPTY"));
	
	for(i = 0; i < MAX_LENS_IF_COUNT; i++)
		m_bLensSocketIF[i] = false;
	
	for(i = 0 ;i < MAX_PCB_IF_COUNT; i++)
		m_bPcbSocketIF[i] = false;

	for(i = 0; i < MAX_ULD_IF_COUNT; i++)
		m_bUldSocketIF[i] = false;

	m_bDoorInterlock = false;
	m_bLensInterLock = false;
	m_bPcbInterLock = false;
	m_bManualAAMove = false;
	m_bManualLaserPos = false;	//false = 외부

	m_bManualTest = false;
	m_bInputSignal = false;
	m_bOutputSignal = false;

	m_dImgShiftX = 0.0;
	m_dImgShiftY = 0.0;
	m_dImgShiftTh = 0.0;


	m_dEolChartShiftX = 0.0;
	m_dEolChartShiftY = 0.0;


	m_dOcResultX = 0.0;
	m_dOcResultY = 0.0;

	m_dOutTx = 0.0;
	m_dOutTy = 0.0;

    m_vDirection.resize(MAX_SFR_INSP_COUNT);
    m_vFrquency.resize(MAX_SFR_INSP_COUNT);
    m_vOffset.resize(MAX_SFR_INSP_COUNT);
    m_vSFR.resize(MAX_SFR_INSP_COUNT);
    m_vThreshold.resize(MAX_SFR_INSP_COUNT);
    m_vROI.resize(MAX_SFR_INSP_COUNT);

	BinOrgBufferSize = 0;

	m_bFirmwareStop = false;
}

//-----------------------------------------------------------------------------
//
//	Task 소멸자
//
//-----------------------------------------------------------------------------
CTaskWork::~CTaskWork()
{
	m_bSfrResult = false;

	m_nCountOfTotalStepAA = 0;

	m_nCountOfStepAA = m_nCountOfSecondStepAA = 0;

	m_nResultCode = 0;
	m_dFOV[0] = m_dFOV[1] = m_dFOV[2] = m_dFOV[3] = m_dFOV[4] = 0.0;

	//memset(&m_stSfrInsp, 0x00, sizeof(STRUC_SFR_INSP));

	m_bSecondAA = false;

	//m_iRetry_Opt = m_iRetry_Opt_Lens = 0;


	m_bFlagDecreaseSFR = false;

   
}
void CTaskWork::ModelChange_TaskWork()
{
	m_FindCircleRect.resize(VEC_FOV_COUNT);
	m_FindFovRect.resize(VEC_FOV_COUNT);
	m_clPtFov.resize(VEC_FOV_COUNT);
	m_clPtSnr.resize(VEC_FOV_COUNT);
}
//-----------------------------------------------------------------------------
//
//	TASK 데이터 유닛번호 설정
//
//-----------------------------------------------------------------------------
void CTaskWork::SetUnit(int nUnit)
{
	m_nUnit = nUnit;

	ModelChange_TaskWork();
}

void CTaskWork::PinLoadData()
{
	TCHAR szPath[SIZE_OF_1K];

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\PinCount.ini"), BASE_COMMON_PATH);

	// 포거핀 사용량
	m_nUsePinCount = GetPrivateProfileInt(_T("COUNT"), _T("UsePinCnt"), 0, szPath);
}


void CTaskWork::PinSaveData()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];
	CFileFind clFind;

	if (clFind.FindFile(BASE_COMMON_PATH) == FALSE) {
		CreateDirectory(BASE_COMMON_PATH, NULL);
	}
	//
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\PinCount.ini"), BASE_COMMON_PATH);


	// 포거핀 사용량
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nUsePinCount);
	WritePrivateProfileString(_T("COUNT"), _T("UsePinCnt"), szData, szPath);
}
//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CTaskWork::LoadData()
{
	TCHAR szPath[SIZE_OF_1K];
	
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\TaskWork.ini"), BASE_DATA_PATH);

	// 생산량
	m_nTotalWorkCount = GetPrivateProfileInt(_T("COUNT"), _T("Total"), 0, szPath);

	// TOTAL OK 수량
	m_nTotalOkCount = GetPrivateProfileInt(_T("COUNT"), _T("TotalOk"), 0, szPath);

	// TOTAL NG 수량
	m_nTotalNgCount = GetPrivateProfileInt(_T("COUNT"), _T("TotalNg"), 0, szPath);

	// MTF NG 수량
	m_nMTFNgCount = GetPrivateProfileInt(_T("NG_COUNT"), _T("MtfNg"), 0, szPath);

	// OC NG 수량
	m_nOCNgCount = GetPrivateProfileInt(_T("NG_COUNT"), _T("OCNg"), 0, szPath);
	
	// DISTORTION NG 수량
	m_nDistortionNgCount = GetPrivateProfileInt(_T("NG_COUNT"), _T("DistortionNg"), 0, szPath);
	
	// CURRENT NG 수량
	m_nCurrentNgCount = GetPrivateProfileInt(_T("NG_COUNT"), _T("CurrentNg"), 0, szPath);
	
	// TEST PATTERN NG 수량
	m_nTestPatternNgCount = GetPrivateProfileInt(_T("NG_COUNT"), _T("TestPatternNg"), 0, szPath);

	// DEFECT NG 수량
	m_nDefectInspNgCount = GetPrivateProfileInt(_T("NG_COUNT"), _T("DefectNg"), 0, szPath);

	// STAIN NG 수량
	m_nStainInspNgCount = GetPrivateProfileInt(_T("NG_COUNT"), _T("StainNg"), 0, szPath);

	// DARK NG 수량
	m_nDarkInspNgCount = GetPrivateProfileInt(_T("NG_COUNT"), _T("DarkNg"), 0, szPath);
		
	// UNIFORMITY NG 수량
	m_nUniformityNgCount = GetPrivateProfileInt(_T("NG_COUNT"), _T("UniformityNg"), 0, szPath);

	// 포거핀 사용량
	///m_nUsePinCount = GetPrivateProfileInt(_T("COUNT"), _T("UsePinCnt"), 0, szPath);


	// UNIFORMITY NG 수량
	m_nEmission = GetPrivateProfileInt(_T("LOT"), _T("Emission"), 0, szPath);

	// 도포 상태.
	m_nEpoxyCompl = GetPrivateProfileInt(_T("EPOXY"), _T("Complete"), 0, szPath);

	// LENS 넘김 상태.
	m_nLensLoading = GetPrivateProfileInt(_T("LENS"), _T("Loading"), 0, szPath);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CTaskWork::SaveData()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];
	CFileFind clFind;

	if (clFind.FindFile(BASE_DATA_PATH) == FALSE)
		CreateDirectory(BASE_DATA_PATH, NULL);


	//
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\TaskWork.ini"), BASE_DATA_PATH);
	// 생산량
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nTotalWorkCount);
	WritePrivateProfileString(_T("COUNT"), _T("Total"), szData, szPath);
	
	// TOTAL OK 수량
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nTotalOkCount);
	WritePrivateProfileString(_T("COUNT"), _T("TotalOk"), szData, szPath);

	// TOTAL NG 수량
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nTotalNgCount);
	WritePrivateProfileString(_T("COUNT"), _T("TotalNg"), szData, szPath);

	// MTF NG 수량
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nMTFNgCount);
	WritePrivateProfileString(_T("NG_COUNT"), _T("MtfNg"), szData, szPath);

	// OC NG 수량
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nOCNgCount);
	WritePrivateProfileString(_T("NG_COUNT"), _T("OCNg"), szData, szPath);

	// DISTORTION NG 수량
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nDistortionNgCount);
	WritePrivateProfileString(_T("NG_COUNT"), _T("DistortionNg"), szData, szPath);

	// CURRENT NG 수량
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nCurrentNgCount);
	WritePrivateProfileString(_T("NG_COUNT"), _T("CurrentNg"), szData, szPath);

	// TEST PATTERN NG 수량
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nTestPatternNgCount);
	WritePrivateProfileString(_T("NG_COUNT"), _T("TestPatternNg"), szData, szPath);

	// DEFECT NG 수량
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nDefectInspNgCount);
	WritePrivateProfileString(_T("NG_COUNT"), _T("DefectNg"), szData, szPath);

	// STAIN NG 수량
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nStainInspNgCount);
	WritePrivateProfileString(_T("NG_COUNT"), _T("StainNg"), szData, szPath);

	// DARK NG 수량
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nDarkInspNgCount);
	WritePrivateProfileString(_T("NG_COUNT"), _T("DarkNg"), szData, szPath);
	
	// UNIFORMITY NG 수량
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nUniformityNgCount);
	WritePrivateProfileString(_T("NG_COUNT"), _T("UniformityNg"), szData, szPath);	

	// 포거핀 사용량
	//_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nUsePinCount);
	//WritePrivateProfileString(_T("COUNT"), _T("UsePinCnt"), szData, szPath);


	// 제품 상태
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nEmission);
	WritePrivateProfileString(_T("LOT"), _T("Emission"), szData, szPath);

	// 도포 상태
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nEpoxyCompl);
	WritePrivateProfileString(_T("EPOXY"), _T("Complete"), szData, szPath);

	// LENS 넘김 상태.
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nLensLoading);
	WritePrivateProfileString(_T("LENS"), _T("Loading"), szData, szPath);

	
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------

void CTaskWork::InitSfrInsp()
{
	int i = 0;
	int j = 0;
	m_bSfrResult = false;

	m_nCountOfTotalStepAA = 0;

	m_nCountOfStepAA = m_nCountOfSecondStepAA = 0;

	m_nResultCode = 0;
	m_dFOV[0] = m_dFOV[1] = m_dFOV[2] = m_dFOV[3] = m_dFOV[4] = 0.0;

	memset(&m_stSfrInsp, 0x00, sizeof(STRUC_SFR_INSP));

	m_bSecondAA = false;

	//m_iRetry_Opt = m_iRetry_Opt_Lens = 0;

	m_bFlagFineMove = false;
	m_bFlagRoughMove = true; //초기 true

	m_bFlagDecreaseSFR = false;

	g_clTaskWork[m_nUnit].m_clPtChartOc.x = 0.0;
	g_clTaskWork[m_nUnit].m_clPtChartOc.y = 0.0;

	g_clTaskWork[m_nUnit].m_clPtCircle[0].x = 0;
	g_clTaskWork[m_nUnit].m_clPtCircle[0].y = 0;

	g_clTaskWork[m_nUnit].m_clPtCircle[1].x = 0;
	g_clTaskWork[m_nUnit].m_clPtCircle[1].y = 0;

	g_clTaskWork[m_nUnit].m_clPtCircle[2].x = 0;
	g_clTaskWork[m_nUnit].m_clPtCircle[2].y = 0;

	g_clTaskWork[m_nUnit].m_clPtCircle[3].x = 0;
	g_clTaskWork[m_nUnit].m_clPtCircle[3].y = 0;

	g_clTaskWork[m_nUnit].m_clPtRotationCircle[0].x = 0.0;
	g_clTaskWork[m_nUnit].m_clPtRotationCircle[0].y = 0.0;
	g_clTaskWork[m_nUnit].m_clPtRotationCircle[1].x = 0.0;
	g_clTaskWork[m_nUnit].m_clPtRotationCircle[2].y = 0.0;
	g_clTaskWork[m_nUnit].m_clPtRotationCircle[2].x = 0.0;
	g_clTaskWork[m_nUnit].m_clPtRotationCircle[2].y = 0.0;
	g_clTaskWork[m_nUnit].m_clPtRotationCircle[3].x = 0.0;
	g_clTaskWork[m_nUnit].m_clPtRotationCircle[3].y = 0.0;
	


	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		g_clTaskWork[m_nUnit].m_stSfrInsp._64_fSfrN4[i] = 0.0;
		g_clMesCommunication[m_nUnit].m_dMesUvAfterMTF[i] = 0.0;

		for (j = 0; j < 10; j++)
		{
			g_clTaskWork[m_nUnit].m_stSfrInsp.dAver_MTF[i][j] = 0.0;
		}
		
	}
	for (i = 0; i < 10; i++)
	{
		g_clTaskWork[m_nUnit].m_stSfrInsp.dAver_Var[i] = 0.0;
	}
	
    //아래 초기화해
    //g_clMesCommunication[nUnit].m_dMesMTF[i]
    //g_clTaskWork[nUnit].m_stSfrInsp._64_fSfrN4[i]
}
//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CTaskWork::InitSfrSpec()
{

}
double CMandoInspLog::getMaxMin(int pos, int type)
{
	int i, end;
	double temp;
	int m_nUnit = 0;
	switch (pos)
	{
	case 0://0필드
		i = 0;
		end = 4;
		break;
	case 1://0.3필드
		i = 4;
		end = 12;
		break;
	case 2://0.6필드
		i = 12;
		end = 20;
		break;
	case 3://0.8필드
		i = 20;
		end = 28;
		break;
	}
	temp = g_clMesCommunication[m_nUnit].m_dMesUvAfterMTF[i]; //dMTF_PostUV[i];
	for (i; i<end; i++)
	{
		if (type == 0)//Max Return
		{
			if (g_clMesCommunication[m_nUnit].m_dMesUvAfterMTF[i] > temp)
			{
				temp = g_clMesCommunication[m_nUnit].m_dMesUvAfterMTF[i];
			}
		}
		else//Min Return
		{
			if (g_clMesCommunication[m_nUnit].m_dMesUvAfterMTF[i] < temp)
			{
				temp = g_clMesCommunication[m_nUnit].m_dMesUvAfterMTF[i];
			}
		}
	}
	return temp;
}
//-----------------------------------------------------------------------------
//
//	생성자
//
//-----------------------------------------------------------------------------
CMandoInspLog::CMandoInspLog()
{

	m_sBarcodeID = _T("EMPTY");

	this->InitData();
}

//-----------------------------------------------------------------------------
//
//	소멸자
//
//-----------------------------------------------------------------------------
CMandoInspLog::~CMandoInspLog()
{

}
void CMandoInspLog::ModelChange_Mando()
{
	m_ShmFovPoint.resize(VEC_FOV_FIND_COUNT);
}
//-----------------------------------------------------------------------------
//
//	데이터 초기화
//
//-----------------------------------------------------------------------------
void CMandoInspLog::InitData()
{
	int i = 0;
	int j = 0;
	::GetLocalTime(&m_stInspTime);	//작업 시작 시간 

	m_bInspRes = true;
	m_sNGList = _T("");
	m_sNGList.Empty();
	m_dTilteOffset[0] = m_dTilteOffset[1] = 0.0;
	m_dPCBOffset[0] = m_dPCBOffset[1] = m_dPCBOffset[2] = 0.0;


	for (i = 0; i < VEC_FOV_FIND_COUNT; i++)
	{
		m_ShmFovPoint[i].x = 0;
		m_ShmFovPoint[i].y = 0;
	}
	for (i = 0; i < 50; i++)
	{
		m_ChartVertex[i].Pos[0].x = 0;
		m_ChartVertex[i].Pos[1].x = 0;
		m_ChartVertex[i].Pos[2].x = 0;
		m_ChartVertex[i].Pos[3].x = 0;
		m_ChartVertex[i].Pos[4].x = 0;
		m_ChartVertex[i].Pos[5].x = 0;
		m_ChartVertex[i].Pos[6].x = 0;
		m_ChartVertex[i].Pos[7].x = 0;
		m_ChartVertex[i].Pos[8].x = 0;
		m_ChartVertex[i].Pos[9].x = 0;

		m_ChartVertex[i].Pos[0].y = 0;
		m_ChartVertex[i].Pos[1].y = 0;
		m_ChartVertex[i].Pos[2].y = 0;
		m_ChartVertex[i].Pos[3].y = 0;
		m_ChartVertex[i].Pos[4].y = 0;
		m_ChartVertex[i].Pos[5].y = 0;
		m_ChartVertex[i].Pos[6].y = 0;
		m_ChartVertex[i].Pos[7].y = 0;
		m_ChartVertex[i].Pos[8].y = 0;
		m_ChartVertex[i].Pos[9].y = 0;
	}


	m_dCurrent = 0.0;
	m_sI2C = _T("");

	m_TpTestResult[0] = false;
	m_TpTestResult[1] = false;


	for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
	{
		g_clTaskWork[0].m_stSfrInsp._fAverSfr[i] = 0.0;
	}

	

	m_dOCResult[0] = m_dOCResult[1] = 0.0;
	m_dTemperatureResult[0] = m_dTemperatureResult[1] = m_dTemperatureResult[2] = 0.0;
	m_dIrFilterResult[0] = m_dIrFilterResult[1] = m_dIrFilterResult[2] = 0.0;
	m_dSaturationResult[0] = m_dSaturationResult[1] = 0.0;
	for (i = 0; i < 2; i++)
	{
		m_dRiMinR[i] = 0.0;
		m_dRiMinGr[i] = 0.0;
		m_dRiMinGb[i] = 0.0;
		m_dRiMinB[i] = 0.0;

		m_dRiMinRG[i] = 0.0;
		m_dRiMinBG[i] = 0.0;
		m_dRiMaxRG[i] = 0.0;
		m_dRiMaxBG[i] = 0.0;

	}

	m_dColorReproductionResult[0] = 0.0;
	m_dColorReproductionResult[1] = 0.0;
	m_dColorReproductionResult[2] = 0.0;
	m_dColorReproductionResult[3] = 0.0;

	for (i = 0; i < 221; i++)
	{
		m_LogLensShadingR[0][i] = 0;
		m_LogLensShadingR[1][i] = 0;
		m_LogLensShadingGr[0][i] = 0;
		m_LogLensShadingGr[1][i] = 0;
		m_LogLensShadingGb[0][i] = 0;
		m_LogLensShadingGb[1][i] = 0;
		m_LogLensShadingB[0][i] = 0;
		m_LogLensShadingB[1][i] = 0;
	}
	for (i = 0; i < 12; i++)
	{
		m_LogLensShadingAvg[0][i] = 0.0;
		m_LogLensShadingAvg[1][i] = 0.0;
	}
	
	m_dVoltageVal[0] = 0.0;
	m_dVoltageVal[1] = 0.0;
	m_dVoltageVal[2] = 0.0;
	m_dVoltageVal[3] = 0.0;

	m_dHumidity = 0.0;

	m_dDistortion = 0.0;

	m_dFov = 0.0;
	m_dDistortion = 0.0;
	m_dSnr = 0.0;
	m_dRotate = 0.0;
	m_Tilt[0] = 0.0;
	m_Tilt[1] = 0.0;
	
	m_Dark = 0.0;
	m_RI = 0.0;
	m_ColorUniformity = 0.0;		//이미지 두장 필요
	m_ColorSensitivity = 0.0;

	m_dDefect[0] = m_dDefect[1] = 0.0;
	m_dStain[0] = m_dStain[1] = 0.0;
	m_dShading65FC[0] = m_dShading65FC[1] = 0.0;
	m_dShading85FC[0] = m_dShading85FC[1] = 0.0;


	//! Main화면 NG List Overlay 관련 변수
	m_nNGCnt = 0;
	for (i = 0; i < 50; i++) 
	{
		//m_sDispNG[i] = _T("");
		m_sDispNG[i].Empty();
	}
	m_sSendNGName = _T("");

	m_dMinData[0] = m_dMinData[1] = m_dMinData[2] = 0.0;

	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		m_UvBeforeSFR[i] = 0.0;
		m_UvAfterSFR[i] = 0.0;
	}
	for (i = 0; i < 10; i++)
	{
		m_Uniformity[i] = 0.0;
	}

	m_4FDiff = 0.0;
	m_7FDiff = 0.0;
	
	m_UvBeforeSFR_0F_Diff = 0.0;
	m_UvBeforeSFR_5F_Diff = 0.0;
	m_UvBeforeSFR_85F_Diff = 0.0;
	m_UvBeforeSFR_5F_Diff_A = 0.0;
	m_UvBeforeSFR_85F_Diff_A = 0.0;

	m_UvAfterSFR_0F_Diff = 0.0;
	m_UvAfterSFR_5F_Diff = 0.0;
	m_UvAfterSFR_85F_Diff = 0.0;
	m_UvAfterSFR_5F_Diff_A = 0.0;
	m_UvAfterSFR_85F_Diff_A = 0.0;

	m_LogDefectDarkInDark = 0.0;
	m_LogDefectBrightInDark = 0.0;
	m_LogDefectDarkInBright = 0.0;
	m_LogDefectBrightInBright = 0.0;
	m_LogDefectClusterDarkInDark = 0.0;
	m_LogDefectClusterBrightInDark = 0.0;
	m_LogDefectClusterDarkInBright = 0.0;
	m_LogDefectClusterBrightInBright = 0.0;
	m_Hot = 0.0;
	m_Dead = 0.0;
	m_Row = 0.0;
	m_Column = 0.0;
	


    m_LogDefectBright = 0.0;
    m_LogDefectDark = 0.0;
    m_LogDefectHot = 0.0;
	m_LogDefectBrightCouplet = 0;
	m_LogDefectDarkCouplet = 0;
	m_LogDefectHotCouplet = 0;

    m_LogDefectBrightCluster = 0.0;
    m_LogDefectDarkCluster = 0.0;
    m_LogDefectHotCluster = 0.0;
    m_LogDefectDarkHorLine = 0.0;
    m_LogDefectDarkVerLine = 0.0;
    m_LogDefectBrightHorLine = 0.0;
    m_LogDefectBrightVerLine = 0.0;
	for (i = 0; i < 4; i++)
	{
		m_LogDefectColumnFPN[i] = 0.0;
	}
   
    //
	m_UvBefore_OC_X = 8.0;          //890
	m_UvBefore_OC_Y = 0.0;          //930
	m_UvBefore_OC_DelatX = 0.0;     //-20
	m_UvBefore_OC_DelatY = 0.0;     //20
	m_UvAfter_OC_X = 8.0;          //890
	m_UvAfter_OC_Y = 0.0;          //930
	m_UvAfter_OC_DelatX = 0.0;     //-20
	m_UvAfter_OC_DelatY = 0.0;     //20

	m_LogIC_DelatX = 0.0;     //-20
	m_LogIC_DelatY = 0.0;     //20

    m_LogDistortion = 0.0;
    //
    m_LogBlemishBlackSpot = 0.0;
    m_LogBlemishLcb = 0.0;
    m_LogBlemishRU_Ymean = 0.0;
	m_LogBlemishFPF = 0.0;
	m_LogBlemishBlackSpotMaxCenter = 0.0;

	m_LogBlemishFdfMaxCenter = 0.0;
	m_LogBlemishFdfMaxEdge = 0.0;
	m_LogBlemishFdfMaxCorner = 0.0;

	m_LogBlemishLcbMaxCenter = 0.0;
	m_LogBlemishLcbMaxEdge = 0.0;
	m_LogBlemishLcbMaxCorner = 0.0;

	m_LogBlemishYmeanMaxCenter = 0.0;
	m_LogBlemishYmeanMaxEdge = 0.0;
	m_LogBlemishYmeanMaxCorner = 0.0;
    //

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 4; j++)
		{
			m_Log_ColorSensitivity_Result[i][j] = 0.0;
		}
	}


    m_Log_CS_RG_6500K = 0.0;
    m_Log_CS_BG_6500K = 0.0;
	m_Log_CS_GrGb_6500K = 0.0;
    m_Log_CS_RC_5000k = 0.0;
    m_Log_CS_BC_5000k = 0.0;
    m_Log_CS_CrCb_5000k = 0.0;

    
	for (i = 0; i < 5; i++)
	{
		m_Log_RI[i][0] = 0;
		m_Log_RI[i][1] = 0;
	}

	for (i = 0; i < 4; i++)
	{
		m_Log_Shading[i] = 0.0;
	}

	
	m_Log_RI_CenterIntensity = 0.0;
	m_Log_RI_Up_Ratio = 0.0;
	m_Log_RI_Left_Ratio = 0.0;
	m_Log_RI_Right_Ratio = 0.0;
	m_Log_RI_Down_Ratio = 0.0;
	m_Log_RI_Difference = 0.0;
    //
	m_Log_RI_CornerVar_R = 0.0;
	m_Log_RI_CornerVar_Cr = 0.0;
	m_Log_RI_CornerVar_Cb = 0.0;
	m_Log_RI_CornerVar_B = 0.0;

    m_Log_RI_Center_R = 0.0;
    m_Log_RI_Center_Cr = 0.0;
    m_Log_RI_Center_Cb = 0.0;
    m_Log_RI_Center_B = 0.0;
    m_Log_RI_LT_Ratio_R = 0.0;
    m_Log_RI_LT_Ratio_Cr = 0.0;
    m_Log_RI_LT_Ratio_Cb = 0.0;
    m_Log_RI_LT_Ratio_B = 0.0;
    m_Log_RI_RT_Ratio_R = 0.0;
    m_Log_RI_RT_Ratio_Cr = 0.0;
    m_Log_RI_RT_Ratio_Cb = 0.0;
    m_Log_RI_RT_Ratio_B = 0.0;
    m_Log_RI_LB_Ratio_R = 0.0;
    m_Log_RI_LB_Ratio_Cr = 0.0;
    m_Log_RI_LB_Ratio_Cb = 0.0;
    m_Log_RI_LB_Ratio_B = 0.0;
    m_Log_RI_RB_Ratio_R = 0.0;
    m_Log_RI_RB_Ratio_Cr = 0.0;
    m_Log_RI_RB_Ratio_Cb = 0.0;
    m_Log_RI_RB_Ratio_B = 0.0;

    //
    m_Log_SNR_SNR = 0.0;
    m_Log_SNR_DR = 0.0;
	for (i = 0; i < 3; i++)
	{
		m_Log_Fpn5000kResult[i][0] = 0.0;
		m_Log_Fpn5000kResult[i][1] = 0.0;
		m_Log_Fpn5000kResult[i][2] = 0.0;
		m_Log_Fpn5000kResult[i][3] = 0.0;

		m_Log_FpnDarkResult[i][0] = 0.0;
		m_Log_FpnDarkResult[i][1] = 0.0;
		m_Log_FpnDarkResult[i][2] = 0.0;
		m_Log_FpnDarkResult[i][3] = 0.0;

	}
	
    //
    m_Log_CU_LT_Delta_RG = 0.0;
    m_Log_CU_LT_Delta_RB = 0.0;
    m_Log_CU_LT_Delta_BG = 0.0;
    m_Log_CU_RT_Delta_RG = 0.0;
    m_Log_CU_RT_Delta_RB = 0.0;
    m_Log_CU_RT_Delta_BG = 0.0;
    m_Log_CU_LB_Delta_RG = 0.0;
    m_Log_CU_LB_Delta_RB = 0.0;
    m_Log_CU_LB_Delta_BG = 0.0;
    m_Log_CU_RB_Delta_RG = 0.0;
    m_Log_CU_RB_Delta_RB = 0.0;
    m_Log_CU_RB_Delta_BG = 0.0;
    //
    m_Log_FOV_H_FOV = 0.0;
    m_Log_FOV_V_FOV = 0.0;
    m_Log_FOV_D_FOV = 0.0;
	m_UvBefore_Rotate = 0.0;
	m_UvAfter_Rotate = 0.0;
	m_SaturationBrightAvg = 0.0;
}

//-----------------------------------------------------------------------------
//
//	AA후(UV전) 로그 저장
//
//-----------------------------------------------------------------------------
void CMandoInspLog::SaveLogAfterAA(int nUnit)
{
	
}




//-----------------------------------------------------------------------------
//
//	NG 오버레이 그리기
//
//-----------------------------------------------------------------------------
void CMandoInspLog::DrawNGOverlay(int nCh)
{
	int nGapY = 80;
	int nSX = 10;
	int nSY = 100;// 700; 

	int nCurX, nCurY;
	nCurX = nSX; 
	int nListNo = 0; 
	int i;

	m_sSendNGName = _T(""); 

	if (m_nNGCnt > 19)
	{
		m_nNGCnt = 19; 
	}

	/*if (nCh == 1)
	{
		nCurY = nSY + (nGapY * nListNo);
		g_clVision.DrawMOverlayText(nCh, nCurX, nCurY, (TCHAR*)(LPCTSTR)"Calibration Error" , M_COLOR_RED, _T("Arial"), 40, 10, FALSE);
		m_sSendNGName = _T(",ETC");
		return;
	}*/

	/*if (m_sBarcodeID == _T("BCR_READ_ERROR"))
	{
		nCurY = nSY + (nGapY * nListNo);
		g_clVision.DrawMOverlayText(nCh, nCurX, nCurY, (TCHAR*)(LPCTSTR)m_sBarcodeID, M_COLOR_RED, _T("Arial"), 40, 10, FALSE);
		m_sSendNGName = _T(",BCR");
		return;
	}*/

	for (i = 0; i < m_nNGCnt; i++)
	{
		nCurY = nSY + (nGapY * nListNo);

		//if (nCurY >((CCD2_CAM_SIZE_Y/* - 4*/) - 80))
		//{
		//	nListNo = 0;
		//	nCurY = nSY + (nGapY * nListNo);
		//	nCurX += CCD2_CAM_SIZE_X / 2-50;	//내용이 많을 경우 2줄로 표시 하기 위해
		//}
		if(m_sSendNGName == _T("")) NGCheck(m_sDispNG[i]);
		g_clVision.DrawMOverlayText(nCh, nCurX, nCurY, (TCHAR*)(LPCTSTR)m_sDispNG[i], M_COLOR_RED, _T("Arial"), 30, 10, FALSE);
		nListNo++;
	}
	if (g_clMesCommunication[nCh].m_nMesFinalResult == 0 && m_nNGCnt == 0)
	{
		if (m_sSendNGName == _T("")) NGCheck(m_sDispNG[0]);
	}
}

void CMandoInspLog::NGCheck(CString strNg)
{ 
	if (strNg.Find(_T("[Defect")) > 0)
		m_sSendNGName = _T(",DEFECT");
	else if (strNg.Find(_T("OC")) > 0)
		m_sSendNGName = _T(",SFR");
	else if (strNg.Find(_T("[Defect")) > 0)
		m_sSendNGName = _T(",STAIN");
	else 
		m_sSendNGName = _T(",ETC");
}


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
CMandoSfrSpec::CMandoSfrSpec()
{
	int i, j;

	/*for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		for (j = 0; j < 2; j++)
		{
			m_dAASFR_Spec[i][j] = 0.227;
		}
	}*/

	for (i = 0; i< MAX_SFR_INSP_COUNT; i++)
	{
		for (j = 0; j < 3; j++)
		{
			m_dINSPSFR_Spec[i][j] = 0.11;
		}
	}

	m_bInsp60Lp = false;
	m_bInsp67Lp = true;
	m_bInspCp = false;
	m_dSfrOffsetMultiply = 1.0;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
CMandoSfrSpec::~CMandoSfrSpec()
{

}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CMandoSfrSpec::Load()
{
	TCHAR szIniBuff[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];

	TCHAR* szIniIndex[] = { 
		_T("SFR_SPEC_0"),_T("SFR_SPEC_1"),
		_T("SFR_SPEC_2"),_T("SFR_SPEC_3"),
		_T("SFR_SPEC_4"),_T("SFR_SPEC_5"),
		_T("SFR_SPEC_6"),_T("SFR_SPEC_7"),
		_T("SFR_SPEC_8"),_T("SFR_SPEC_9"),
		_T("SFR_SPEC_10"),_T("SFR_SPEC_11"),
		_T("SFR_SPEC_12"),_T("SFR_SPEC_13"),
		_T("SFR_SPEC_14"),_T("SFR_SPEC_15"),
		_T("SFR_SPEC_16"),_T("SFR_SPEC_17"),
		_T("SFR_SPEC_18"),_T("SFR_SPEC_19"),
		_T("SFR_SPEC_20"),_T("SFR_SPEC_21"),
		_T("SFR_SPEC_22"),_T("SFR_SPEC_23"),
		_T("SFR_SPEC_24"),_T("SFR_SPEC_25"),

	};

	TCHAR* szIniAveIndex[] = {
		_T("AA_CENTER"),
		_T("AA_MID1"), _T("AA_MID2"), _T("AA_MID3"), _T("AA_MID4"),
		_T("AA_SIDE1"), _T("AA_SIDE2"), _T("AA_SIDE3"), _T("AA_SIDE4") };

	CString sToken = _T("");
	int i, j;
	 
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\SfrSpec.ini"), BASE_DATA_PATH);

	/*for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		GetPrivateProfileString(_T("SFR_SPEC"), szIniIndex[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		if (_tcslen(szIniBuff) > 0)
		{
			for (j = 0; j < 2; j++)
			{
				AfxExtractSubString(sToken, szIniBuff, j, _T('/'));

				switch (j)
				{
				case 0:		m_dAASFR_Spec[i][0] = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
				case 1:		m_dAASFR_Spec[i][1] = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
				}
			}
		}
	}*/
	for (i = 0; i < MAX_SFR_INSP_SUMAVE_CNT; i++)
	{
		GetPrivateProfileString(_T("SFR_AVE_SPEC"), szIniAveIndex[i], _T("1.000"), szIniBuff, sizeof(szIniBuff), szPath);
		m_dAASFR_SumAveSpec[i][0] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
		GetPrivateProfileString(_T("SFR_AVE_SPEC_EOL"), szIniAveIndex[i], _T("1.000"), szIniBuff, sizeof(szIniBuff), szPath);
		m_dAASFR_SumAveSpec[i][1] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}

	GetPrivateProfileString(_T("SFR_MUL_SPEC"), _T("MULTIPLY"), _T("1.000"), szIniBuff, sizeof(szIniBuff), szPath);
	m_dSfrOffsetMultiply = _ttof((TCHAR*)(LPCTSTR)szIniBuff);


	TCHAR* szIniDiffIndex[] = {
		_T("AA_DIFF_0F"),
		_T("AA_DIFF_05F"), _T("AA_DIFF_85F"), _T("AA_DIFF_A_5F"), _T("AA_DIFF_A_85F") };
	for (i = 0; i < 5; i++)
	{
		GetPrivateProfileString(_T("SFR_DIFF_SPEC"), szIniDiffIndex[i], _T("1.000"), szIniBuff, sizeof(szIniBuff), szPath);
		m_dAASFR_DiffMaxSpec[i][0] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
		GetPrivateProfileString(_T("SFR_DIFF_SPEC_EOL"), szIniDiffIndex[i], _T("1.000"), szIniBuff, sizeof(szIniBuff), szPath);
		m_dAASFR_DiffMaxSpec[i][1] = _ttof((TCHAR*)(LPCTSTR)szIniBuff);
	}
	
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CMandoSfrSpec::Save()
{
	TCHAR szData[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];

	TCHAR* szIniIndex[] = { 
		_T("SFR_SPEC_0"),_T("SFR_SPEC_1"),
		_T("SFR_SPEC_2"),_T("SFR_SPEC_3"),
		_T("SFR_SPEC_4"),_T("SFR_SPEC_5"),
		_T("SFR_SPEC_6"),_T("SFR_SPEC_7"),
		_T("SFR_SPEC_8"),_T("SFR_SPEC_9"),
		_T("SFR_SPEC_10"),_T("SFR_SPEC_11"),
		_T("SFR_SPEC_12"),_T("SFR_SPEC_13"),
		_T("SFR_SPEC_14"),_T("SFR_SPEC_15"),
		_T("SFR_SPEC_16"),_T("SFR_SPEC_17"),
		_T("SFR_SPEC_18"),_T("SFR_SPEC_19"),
		_T("SFR_SPEC_20"),_T("SFR_SPEC_21"),
		_T("SFR_SPEC_22"),_T("SFR_SPEC_23"),
		_T("SFR_SPEC_24"),_T("SFR_SPEC_25"), 
	};

	TCHAR* szIniAveIndex[] = {
		_T("AA_CENTER"), 
		_T("AA_MID1"), _T("AA_MID2"), _T("AA_MID3"), _T("AA_MID4"),
		_T("AA_SIDE1"), _T("AA_SIDE2"), _T("AA_SIDE3"), _T("AA_SIDE4") };

	int i;
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\SfrSpec.ini"), BASE_DATA_PATH);

	/*for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf"), m_dAASFR_Spec[i][0], m_dAASFR_Spec[i][1]);
		WritePrivateProfileString(_T("SFR_SPEC"), szIniIndex[i], szData, szPath);
	}*/

	for (i = 0; i < MAX_SFR_INSP_SUMAVE_CNT; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dAASFR_SumAveSpec[i][0]);
		WritePrivateProfileString(_T("SFR_AVE_SPEC"), szIniAveIndex[i], szData, szPath);
		_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dAASFR_SumAveSpec[i][1]);
		WritePrivateProfileString(_T("SFR_AVE_SPEC_EOL"), szIniAveIndex[i], szData, szPath);
	}
	_stprintf_s(szData, SIZE_OF_1K, _T("%.05lf"), m_dSfrOffsetMultiply);
	WritePrivateProfileString(_T("SFR_MUL_SPEC"), _T("MULTIPLY"), szData, szPath);



	TCHAR* szIniDiffIndex[] = {
		_T("AA_DIFF_0F"),
		_T("AA_DIFF_05F"), _T("AA_DIFF_85F"), _T("AA_DIFF_A_5F"), _T("AA_DIFF_A_85F") };
	for (i = 0; i < 5; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dAASFR_DiffMaxSpec[i][0]);
		WritePrivateProfileString(_T("SFR_DIFF_SPEC"), szIniDiffIndex[i], szData, szPath);
		_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dAASFR_DiffMaxSpec[i][1]);
		WritePrivateProfileString(_T("SFR_DIFF_SPEC_EOL"), szIniDiffIndex[i], szData, szPath);
	}
}
