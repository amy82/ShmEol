#include "stdafx.h"
#include "MesData.h"


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
CMesCommunication::CMesCommunication()
{
	int i = 0;
	int j = 0;
	m_sMesI2C.Format(_T("0.0"));//(_T("PASS"));
	m_sStain.Format(_T("PASS"));
	m_sBlackSpot.Format(_T("PASS"));
	m_sNoise.Format(_T("PASS"));
	m_sDefect.Format(_T("PASS"));
	m_nMesI2CResult = 0;
	m_nsMesfuseIDResult = 1;

	m_dMesUVBeforeOC[0] = m_dMesUVBeforeOC[1] = 0.0;	//OC 결과.[X/Y]  UV 전
	m_dMesUVAfterOC[0] = m_dMesUVAfterOC[1] = 0.0;		//OC 결과.[X/Y]  UV 후
	m_dMesUVAfterDeltaOC[0] = m_dMesUVAfterDeltaOC[1] = 0.0;


	m_dMesShading65FC[0] = m_dMesShading65FC[1] = m_dMesShading85FC[0] = m_dMesShading85FC[1] = 0.0;
	ConversationTimeoutCount = 60;	//sec U1


	m_nMesUVBeforeOCResult = m_nMesUVAfterOCResult[0] = m_nMesUVAfterOCResult[1] = 0;

	m_nMesStainResult = 0;
	m_nMesDarkResult = 0;

	m_dTerminalId = 0;
	for (i = 0; i < 4; i++)
	{
		m_dI2cData[i] = 0x00;
		m_dI2cDataResult[i] = 0;
	}
	for (i = 0; i < 2; i++)
	{
		m_dIspData[i] = 0x00;
		m_dIspDataResult[i] = 0;
	}

	for (i = 0; i < 9; i++)
	{
		m_dChartBright[i] = 0;
		m_dChartBrightResult[i] = 0;
	}
	for (i = 0; i < 5; i++)
	{
		m_dOcBright[i] = 0;
		m_dOcBrightResult[i] = 0;
	}
	m_nMesShading65FCResult[0] = m_nMesShading65FCResult[1] = m_nMesShading85FCResult[0] = m_nMesShading85FCResult[1] = 0;

	for (i = 0; i < 4; i++)
	{
		m_nMesRICornerResult[i] = 0;
	}

	m_nMesRIDiffResult = 0;
	m_nMesRIMinDiffResult = 0;
	m_nMesRICenterRawResult = 0;

	for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
	{
		m_dMesAreaAvrMTF[i] = 0.0;
		m_nMesMTFAreaAvrResult[i] = 0;
		m_dMesAreaAvrUVBeforeMTF[i] = 0;
	}
	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		m_dMesUvBeforeMTF[i] = 0.0;			//MTF 검사 항목
		m_dMesUvAfterMTF[i] = 0.0;
	}
	m_dMesLaserTilt[0] = 0.0;
	m_dMesLaserTilt[1] = 0.0;

	m_dMes4F_Diff = 0.0;
	m_dMes7F_Diff = 0.0;
	m_dMes7FVariation = 0.0;
	m_dMes4F_DiffResult = 0;
	m_dMes7F_DiffResult = 0;

	m_dMes7FVariationResult = 0;
	for (i = 0; i < MAX_SFR_INSP_SUMAVE_CNT; i++)
	{
		m_dMesMTF_AVER[i] = 0.0;
		m_nMesMTFResult_AVER[i] = 0;
		m_nMesMTFResult_UVBeforeAVER[i] = 0;
	}
	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		m_nMesUvBeforeMTFResult[i] = 0;
		m_nMesUvAfterMTFResultUVAfter[i] = 0;
	}

	m_uAlarmList.clear();
	//======================================================================================
	//======================================================================================
	//======================================================================================
	//new Mes 190921

	m_sMesLotID = _T("EMPTY");	// 바코드 아이디
	m_nMesCnt = 0;			// 차수
	m_nMesFinalResult = 0;	// 합부 선언부분
	m_dMesCurrent = 0.0;
	//
	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		m_dMesMTF[i] = 0.0;			//MTF 검사 항목
	}
	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		m_nMesMTFResult[i] = 0;
	}
	for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
	{
		m_dMesLightChartValue[i] = 0.0;
		m_dMesLightChartResult[i] = 0;
	}

	m_dMesLightOcValue = 0.0;

	m_dMesLightOcResult = 0;

	m_dMesDistortion = 0.0;
	m_dMesSnr = 0.0;
	m_dMesDr = 0.0;
	m_dMesUvAfterRotate = 0.0;
	m_dMesUvBeforeRotate = 0.0;
	for (i = 0; i < 4; i++)
	{
		m_dMesEEPROMResult[i] = 0;			//MTF 검사 항목
	}

	for (i = 0; i < 5; i++)
	{
		m_dMesOcLightTime[i] = 0;
		m_dMesOcLightTimeResult[i] = 0;
	}

	m_nMesFirmwareVerifyResult = 0;
	m_nMesCurrentResult = 0;
	m_dMesRotateResult = 1;
	m_dMesRotateUVAfterResult = 1;
	m_dMesSnrResult = 1;
	m_dMesDrResult = 1;
	m_nMesDistortionResult = 1;

	for (i = 0; i < 2; i++)
	{
		m_dMesTiltResult[i] = 0;
		m_dMesOC[i] = 0.0;
		m_dMesDeltaOC[i] = 0.0;
		m_dMesOCResult[i] = 0;
		m_dMesDeltaOCResult[i] = 0;

		m_dMesUVAfterOC[i] = 0.0;
		m_dMesDeltaUVAfterOC[i] = 0.0;
		m_dMesUVAfterOCResult[i] = 0;
		m_dMesUVAfterDeltaOCResult[i] = 0;
		//
		m_dMesICOC[2] = 0.0;
		m_dMesICDeltaOC[2] = 0.0;
		m_dMesICOCResult[2] = 0;
		m_dMesICDeltaOCResult[2] = 0;
	}

	for (i = 0; i < 2; i++)
	{
		m_dMesFov[i] = 0.0;
		m_dMesFovResult[i] = 0;
	}
	for (i = 0; i < 12; i++)
	{
		m_nMesDefect[i] = 0;
		m_nMesDefectResult[i] = 0;
	}

	for (i = 0; i < 8; i++)
	{
		m_nMesRI[0][i] = 0.0;
		m_nMesRI[1][i] = 0.0;
		m_nMesRIResult[0][i] = 0;
		m_nMesRIResult[1][i] = 0;
	}


	m_dMesRiDiff = 0.0;
	m_dMesRiCenterRaw = 0.0;
	for (i = 0; i < 4; i++)
	{
		m_nMesRICorner[i] = 0.0;
		m_nMesRIRICornerResult[i] = 0;

		m_nMesColorReproduction[i] = 0.0;
		m_nMesColorReproductionResult[i] = 0;

	}
	m_dMesRiMinDiff = 0.0;


	for (i = 0; i < 9; i++)
	{
		m_nMesBlemishMaxDefect[i] = 0.0;
		m_nMesBlemishMaxDefectResult[i] = 1;
	}

	for (i = 0; i < 4; i++)
	{
		m_dMesTemperature[i] = 0.0;
		m_dMesTemperatureResult[i] = 1;
	}

	for (i = 0; i < 3; i++)
	{
		m_dMesSensorVoltage[i] = 0.0;
		m_nMesSensorVoltageResult[i] = 1;
	}

	m_dMesVoltage = 0.0;
	m_nMesVoltageResult = 1;


	m_dMesSaturationBrightAvg = 0.0;
	m_dMesSaturationBrightAvgResult = 1;


	for (i = 0; i < 3; i++)
	{
		m_dMesIRFilterValue[i] = 0.0;
		m_dMesIRFilterResult[i] = 1;
	}
	m_dMesIrROIBrightAvg = 0.0;
	m_dMesIrROIBrightAvgResult = 1;

	m_dMesIrRoiBrightVar = 0.0;
	m_dMesIrRoiBrightVarResult = 1;


	m_dMesDistortionResult = 1;
	m_dMesNoiseResult = 1;


	for (i = 0; i < 4; i++)
	{
		m_dGrrBeForeLaserPos[i] = 0.0;
		m_dGrrLaserPos[i] = 0.0;
	}
	for (i = 0; i < 6; i++)
	{
		m_dGrrMotorPos[i] = 0.0;
	}
	for (i = 0; i < 3; i++)
	{
		m_dGrrAlignPos[i] = 0.0;
	}


	/*for (i = 0; i < g_LotApdInfoCount; i++)
	{
		_stprintf_s(vMesFianData[i], SIZE_OF_100BYTE, _T("0"));
	}*/

	vMesApdData.clear();
	for (i = 0; i < g_MaxModelCount; i++)
	{
		_stprintf_s(vMesModelList[i], SIZE_OF_100BYTE, _T("AABBCC"));
	}
	m_sMesOperatorID.Format(_T("00000001"));
	m_sEquipmentID.Format(_T(""));
	m_sEquipmentName.Format(_T(""));//228.43

	m_sRecipeId.Format(_T(""));
	m_sLotID.Format(_T(""));
	m_sProcessID.Format(_T(""));

	m_sErcmdCode.Format(_T(""));
	m_sErcmdText.Format(_T(""));


	IdleSetTimeInterval = 5;	//min
	m_dLotProcessingState = 1;
	m_dProcessState[0] = 1;	//INIT, IDLE, SETUP, READY,EXECUTING,PAUSE
	m_dProcessState[1] = 1;
	m_bLgit_Pause_req = false;

	m_dEqupControlState[0] = eEquipmentOffline;
	m_dEqupControlState[1] = eEquipmentOffline;

	m_dEqupOperationMode[0] = 9;	//1 = Full-Auto Mode, 9=Manual Mode
	m_dEqupOperationMode[1] = 0;

	

	m_dControlStateChangeOrder = 1;
	m_sMesPPID.Format(_T(""));
	m_sMesRecipeRevision.Format(_T(""));
	m_dPPChangeArr[0] = eCreated;
	m_dPPChangeArr[1] = eOperator;		//1 = Host, 2 = Operator
	
	m_dEqpDefectCode.Format(_T("1"));
	m_dAlarmCode = 0;//1001 ~ 1080
}
std::vector<_PP_RECIPE_SPEC> CMesCommunication::RecipeIniLoad(CString recipeFilePPid)
{
	int i = 0;
	int index;
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniBuff[SIZE_OF_1K];
	CFileFind clFinder;
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s.ini"), BASE_RECIPE_PATH, recipeFilePPid);
	

	std::vector<PP_RECIPE_SPEC> specData;
	specData.clear();

	if (clFinder.FindFile(szPath) == FALSE)
	{
		return specData;
	}
	PP_RECIPE_SPEC ppRs;

	std::string firstValue, secondValue;
	//RECIPE_PARAM_NAME

	//GetPrivateProfileString(_T("RECIPE"), _T("PPID"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);

	ppRs.PPId = recipeFilePPid;		/// szIniBuff;	//따로 저장 x
	GetPrivateProfileString(_T("RECIPE"), _T("VERSION"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	ppRs.VERSION = szIniBuff;

	for (i = 0; i < g_RecipeParamCount; i++)
	{
		ppRs.parmName.push_back(RECIPE_PARAM_NAME[i]);
		
		GetPrivateProfileStringA(_T("VALUE"), RECIPE_PARAM_NAME[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);

		std::stringstream ss(szIniBuff);

		std::getline(ss, firstValue, ',');
		//ppRs.parmVal.push_back(firstValue);
		std::getline(ss, secondValue, ',');

		ppRs.parmMap[RECIPE_PARAM_NAME[i]] = firstValue;
		if (secondValue == "1" && secondValue.size() > 0)
		{
			//ppRs.parmChecked.push_back("1");
			ppRs.parmMapChk[RECIPE_PARAM_NAME[i]] = "1";
		}
		else
		{
			//ppRs.parmChecked.push_back("0");
			ppRs.parmMapChk[RECIPE_PARAM_NAME[i]] = "0";
		}
		
		
		
	}

	specData.push_back(ppRs);
	return specData;
}
double CMesCommunication::mapKeyRtn(std::string strKey)
{
	//PP_RECIPE_SPEC  pSpec, 
	if (g_clMesCommunication[0].vPPRecipeSpecEquip.size() < 1)
	{
		return 0.0;
	}
	std::string str = "";
	if (g_clMesCommunication[0].vPPRecipeSpecEquip[0].parmMap.find(strKey) != g_clMesCommunication[0].vPPRecipeSpecEquip[0].parmMap.end())
	{
		str = g_clMesCommunication[0].vPPRecipeSpecEquip[0].parmMap[strKey];
	}
	return std::stod(str);
}
bool CMesCommunication::RecipeIniSave(std::vector<_PP_RECIPE_SPEC> ppRecipeVec)
{
	if (ppRecipeVec.size() < 1)
	{
		return false;
	}
	int i = 0;
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];

	
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s.ini"), BASE_RECIPE_PATH, ppRecipeVec[0].PPId.c_str());
	//_stprintf_s(szData, SIZE_OF_1K, _T("%s"), ppRecipeVec[0].PPId.c_str());
	//WritePrivateProfileString(_T("RECIPE"), _T("PPID"), szData, szPath);		//저장 x , 파일이름이 ppid

	if (ppRecipeVec[0].VERSION.size() > 0)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%s"), ppRecipeVec[0].VERSION.c_str());
	}
	else
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("1"));
	}
	WritePrivateProfileString(_T("RECIPE"), _T("VERSION"), szData, szPath);



	int subCnt = ppRecipeVec[0].parmMap.size();
	for (i = 0; i < subCnt; i++)
	{
		//std::string combinedValue = ppRecipeVec[0].parmMap[ppRecipeVec[0].parmName[i]] + "," + ppRecipeVec[0].parmChecked[i];
		std::string combinedValue = ppRecipeVec[0].parmMap[ppRecipeVec[0].parmName[i]] + "," + ppRecipeVec[0].parmMapChk[ppRecipeVec[0].parmName[i]];

		WritePrivateProfileString(_T("VALUE"), ppRecipeVec[0].parmName[i].c_str(), combinedValue.c_str(), szPath);
	}
	//
	return true;
}
#if 0
std::vector<_PP_RECIPE_SPEC> CMesCommunication::RecipeXmlLoad(CString recipefile)
{
	std::vector<PP_RECIPE_SPEC> specData;
	specData.clear();
	TCHAR szPath[SIZE_OF_1K];
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s.xml"), BASE_RECIPE_PATH, recipefile);
	
	std::vector<PP_RECIPE_SPEC> specData;
	specData.clear();
	
	CMarkup xml;
	bool m_bLSFileLoaded = xml.Load(szPath);
	if (m_bLSFileLoaded)
	{
		PP_RECIPE_SPEC ppRs;
		ppRs.parmChecked.clear();
		ppRs.parmName.clear();
		ppRs.parmVal.clear();

		std::string tageName;
		// XML 데이터 탐색
		if (xml.FindElem("Recipe"))
		{
			// "Recipe" 태그 내부에서 "PPID" 태그 찾기
			if (xml.FindChildElem("PPID"))
			{
				ppRs.PPId = xml.GetChildData();
			}
			if (xml.FindChildElem("VERSION"))
			{
				ppRs.VERSION = xml.GetChildData();
			}
			if (xml.FindChildElem("CCodeInfoInfos")) 
			{
				tageName = xml.GetTagName();
				xml.IntoElem();
				tageName = xml.GetTagName();
				if (xml.FindChildElem("CCodeInfo"))
				{
					xml.IntoElem();
					tageName = xml.GetTagName();
					if (xml.FindChildElem("PPItems"))
					{
						tageName = xml.GetTagName();
						xml.IntoElem();
						tageName = xml.GetTagName();
						while (xml.FindChildElem("PPItem"))
						{
							xml.IntoElem();
							std::string ppName = xml.GetAttrib("PPName");
							std::string checked = xml.GetAttrib("Checked");
							std::string format = xml.GetAttrib("Format");
							std::string ppValue = xml.GetAttrib("PPValue");


							ppRs.parmChecked.push_back(checked);
							
							
							ppRs.parmName.push_back(ppName);
							ppRs.parmVal.push_back(ppValue);// std::stod(ppValue));// _ttof(ppValue));
							xml.OutOfElem();
						}
					}
				}
			}
		}
		specData.clear();
		specData.push_back(ppRs);
	}
	else 
	{
		std::cout << "Failed to load XML file!" << std::endl;
	}

	return specData;
}

bool CMesCommunication::RecipeXmlSave(std::vector<_PP_RECIPE_SPEC> ppRecipeVec)
{

	if (ppRecipeVec.size() < 1)
	{
		return false;
	}
	TCHAR szPath[SIZE_OF_1K];
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s.xml"), BASE_RECIPE_PATH, ppRecipeVec[0].PPId.c_str());

	CMarkup xml;

	// XML 파일 생성
	xml.AddElem("Recipe");


	// "PPID" 태그 추가
	xml.IntoElem();
	xml.AddElem("PPID", ppRecipeVec[0].PPId.c_str());// "SHM_OHC_150_1");

	// "VERSION" 태그 추가
	if (ppRecipeVec[0].VERSION.size() < 1)
	{
		ppRecipeVec[0].VERSION = "1";
	}
	xml.AddElem("VERSION", ppRecipeVec[0].VERSION.c_str());

	// "CCodeInfoInfos" 태그 추가
	xml.AddElem("CCodeInfoInfos");
	xml.IntoElem();  // CCodeInfoInfos 내부로 들어감

	// "CCodeInfo" 태그 추가
	xml.AddElem("CCodeInfo");
	xml.AddAttrib("CommandCode", "DATA");
	xml.IntoElem();  // CCodeInfo 내부로 들어감

	// "PPItems" 태그 추가
	xml.AddElem("PPItems");
	xml.IntoElem();  // PPItems 내부로 들어감


	// 여러 개의 "PPItem" 태그 추가

	int subCnt = ppRecipeVec[0].parmVal.size();

	for (int j = 0; j < subCnt; j++)
	{
		xml.AddElem("PPItem");

		xml.AddAttrib("PPName", ppRecipeVec[0].parmName[j].c_str());// "CURRENT_MIN");
		if (ppRecipeVec[0].parmChecked[j] == "1")
		{
			xml.AddAttrib("Checked", "1");
		}
		else
		{
			xml.AddAttrib("Checked", "0");
		}
		
		xml.AddAttrib("Format", "A");
		xml.AddAttrib("PPValue", ppRecipeVec[0].parmVal[j].c_str());// "0.040000");
	}





	xml.OutOfElem();  // PPItems 밖으로 나옴
	xml.OutOfElem();  // CCodeInfo 밖으로 나옴
	xml.OutOfElem();  // CCodeInfoInfos 밖으로 나옴
	xml.OutOfElem();  // Recipe 밖으로 나옴

	// XML 파일로 저장
	if (xml.Save(szPath))
	{
		std::cout << "XML saved successfully!" << std::endl;
	}
	else 
	{
		std::cout << "Failed to save XML!" << std::endl;
	}

	return true;
}
#endif


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
CMesCommunication::~CMesCommunication()
{

}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CMesCommunication::Insp()
{

}


//-----------------------------------------------------------------------------
//
//	MES 데이터 로드
//
//-----------------------------------------------------------------------------
void CMesCommunication::secsGemLoad()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i = 0;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\SecGemData.ini"), BASE_SECSGEM_PATH);
	

	GetPrivateProfileString(_T("OPERATOR_ID"), _T("ID"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	m_sMesOperatorID.Format(_T("%s"), szIniBuff);

	GetPrivateProfileString(_T("MATERIAL"), _T("MATERIALID"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	g_clReportData.rMaterial_Id_Confirm.MaterialId.Format(_T("%s"), (TCHAR*)(LPCTSTR)szIniBuff);

	GetPrivateProfileString(_T("MATERIAL"), _T("MATERIALTYPE"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	g_clReportData.rMaterial_Id_Confirm.MaterialType.Format(_T("%s"), (TCHAR*)(LPCTSTR)szIniBuff);

	// MODEL LIST
	/*for (i = 0; i < g_MaxModelCount; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("%02d"), i + 1);
		GetPrivateProfileString(_T("MODEL"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		_stprintf_s(vMesModelList[i], SIZE_OF_100BYTE, _T("%s"), szIniBuff);
	}*/
}

//-----------------------------------------------------------------------------
//
//	MES 데이터 저장
//
//-----------------------------------------------------------------------------
void CMesCommunication::secsGemSave()
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i, j;
	CFileFind clFinder;
	if (clFinder.FindFile(BASE_SECSGEM_PATH) == FALSE)
	{
		CreateDirectory(BASE_SECSGEM_PATH, NULL);
	}

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\SecGemData.ini"), BASE_SECSGEM_PATH);

	_stprintf_s(szData, SIZE_OF_1K, _T("%s"), m_sMesOperatorID);
	WritePrivateProfileString(_T("OPERATOR_ID"), _T("ID"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%s"), g_clReportData.rMaterial_Id_Confirm.MaterialId);
	WritePrivateProfileString(_T("MATERIAL"), _T("MATERIALID"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%s"), g_clReportData.rMaterial_Id_Confirm.MaterialType);
	WritePrivateProfileString(_T("MATERIAL"), _T("MATERIALTYPE"), szData, szPath);
	//-------------------------------------------------------
	//
	//
	// MODEL LIST
	//
	//
	//-------------------------------------------------------
	


	//-------------------------------------------------------
	//
	/*for (i = 0; i < g_MaxModelCount; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("%02d"), i + 1);
		_stprintf_s(szData, SIZE_OF_1K, _T("%s"), vMesModelList[i]);
		WritePrivateProfileString(_T("MODEL"), szIniIndex, szData, szPath);
	}*/

}


bool CMesCommunication::g_Grr____Align(int nUnit)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szFilePath[SIZE_OF_1K];
	SYSTEMTIME stSysTime;
	CFileFind clFinder;
	CString sFileMode = _T("");
	CFile clFile;
	FILE* fp;
	int nStepNo;
	int i = 0;
	int j = 0;
	int indexX = 0;
	int indexY = 0;
	bool createBool = true;
	::GetLocalTime(&stSysTime);

	if (_tcslen(g_clTaskWork[nUnit].m_szChipID) <= 0)
		_tcscpy_s(g_clTaskWork[nUnit].m_szChipID, SIZE_OF_100BYTE, _T("(NULL)"));

	if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
		CreateDirectory(BASE_LOG_PATH, NULL);

	if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
		CreateDirectory(BASE_LOG_PATH, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Result"), BASE_LOG_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Result\\%04d%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Result\\%04d%02d\\%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	nStepNo = g_clTaskWork[nUnit].m_nCountOfTotalStepAA;

	TCHAR m_szModel[SIZE_OF_100BYTE];

#if (____MACHINE_NAME == MODEL_FRONT_100)
	_stprintf_s(m_szModel, SIZE_OF_100BYTE, _T("SHM100"));
#else
	_stprintf_s(m_szModel, SIZE_OF_100BYTE, _T("SHM150"));
#endif

	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\GrrAlignLog_%s_%04d%02d%02d.csv"), szPath, m_szModel, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);

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
	sFileMode = _T("w");
#endif

	// 파일이 없으면 헤더를 만든다.
	if (clFinder.FindFile(szFilePath) == FALSE)
	{
		_tfopen_s(&fp, szFilePath, sFileMode);
		if (fp != NULL)
		{
			_ftprintf_s(fp, _T("Time,"));
			_ftprintf_s(fp, _T("Model,				SW Version,"));
			_ftprintf_s(fp, _T("Chip ID,"));
			_ftprintf_s(fp, _T("Align X ,Align Y ,Align Th ,"));


			_ftprintf_s(fp, _T("\n"));
			fclose(fp);
		}
	}


#ifdef _UNICODE
	sFileMode = _T("a,ccs=UTF-8");
#else
	sFileMode = _T("a");
#endif

	_tfopen_s(&fp, szFilePath, sFileMode);
	if (fp != NULL)
	{
		_ftprintf_s(fp, _T("'%04d-%02d-%02d %02d:%02d:%02d,"), stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);
		_ftprintf_s(fp, _T("%s, %s,"), m_szModel, VER_STR);
		_ftprintf_s(fp, _T("%s,"), g_clTaskWork[nUnit].m_szChipID);

		for (i = 0; i < 3; i++)
		{
			_ftprintf_s(fp, _T("%lf,"), m_dGrrAlignPos[i]);
		}

		_ftprintf_s(fp, _T("\n"));
		fclose(fp);
	}
	return true;
}



bool CMesCommunication::g_Grr____LaserMotorPos(int nUnit)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szFilePath[SIZE_OF_1K];
	SYSTEMTIME stSysTime;
	CFileFind clFinder;
	CString sFileMode = _T("");
	CFile clFile;
	FILE* fp;
	int nStepNo;
	int i = 0;
	int j = 0;
	int indexX = 0;
	int indexY = 0;
	bool createBool = true;
	::GetLocalTime(&stSysTime);

	if (_tcslen(g_clTaskWork[nUnit].m_szChipID) <= 0)
		_tcscpy_s(g_clTaskWork[nUnit].m_szChipID, SIZE_OF_100BYTE, _T("(NULL)"));

	if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
		CreateDirectory(BASE_LOG_PATH, NULL);

	if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
		CreateDirectory(BASE_LOG_PATH, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Result"), BASE_LOG_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Result\\%04d%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Result\\%04d%02d\\%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	nStepNo = g_clTaskWork[nUnit].m_nCountOfTotalStepAA;

	TCHAR m_szModel[SIZE_OF_100BYTE];

#if (____MACHINE_NAME == MODEL_FRONT_100)
	_stprintf_s(m_szModel, SIZE_OF_100BYTE, _T("SHM100"));
#else
	_stprintf_s(m_szModel, SIZE_OF_100BYTE, _T("SHM150"));
#endif

	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\GrrLog_%s_%04d%02d%02d.csv"), szPath, m_szModel, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);

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
	sFileMode = _T("w");
#endif

	// 파일이 없으면 헤더를 만든다.
	if (clFinder.FindFile(szFilePath) == FALSE)
	{
		_tfopen_s(&fp, szFilePath, sFileMode);
		if (fp != NULL)
		{
			_ftprintf_s(fp, _T("Time,"));
			_ftprintf_s(fp, _T("Model,				SW Version,"));
			_ftprintf_s(fp, _T("Chip ID,"));
			_ftprintf_s(fp, _T("LASER Before POS1 ,LASER Before POS2 ,LASER Before POS3 ,"));
			_ftprintf_s(fp, _T("LASER POS1 ,LASER POS2 ,LASER POS3 ,"));
			_ftprintf_s(fp, _T("PCB X ,PCB Y ,PCB Z ,PCB Th ,PCB Tx ,PCB Ty ,"));
			_ftprintf_s(fp, _T("Align X ,Align Y ,Align Th ,"));
			_ftprintf_s(fp, _T("[SFR]0.0F AVERAGE,"));
			_ftprintf_s(fp, _T("[SFR]0.4F LT AVERAGE,[SFR]0.4F RT AVERAGE,[SFR]0.4F LB AVERAGE,[SFR]0.4F RB AVERAGE,"));
			_ftprintf_s(fp, _T("[SFR]0.7F LT AVERAGE,[SFR]0.7F RT AVERAGE,[SFR]0.7F LB AVERAGE,[SFR]0.7F RB AVERAGE,"));
			_ftprintf_s(fp, _T("[OC] OC_X ,	[OC] OC_Y,"));
			_ftprintf_s(fp, _T("[OC] OC_X DELTA ,	[OC] OC_Y DELTA,"));

			_ftprintf_s(fp, _T("\n"));
			fclose(fp);
		}
	}


#ifdef _UNICODE
	sFileMode = _T("a,ccs=UTF-8");
#else
	sFileMode = _T("a");
#endif

	_tfopen_s(&fp, szFilePath, sFileMode);
	if (fp != NULL)
	{
		_ftprintf_s(fp, _T("'%04d-%02d-%02d %02d:%02d:%02d,"), stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);
		_ftprintf_s(fp, _T("%s, %s,"), m_szModel, VER_STR);
		_ftprintf_s(fp, _T("%s,"), g_clTaskWork[nUnit].m_szChipID);

		for (i = 0; i < 3; i++)
		{
			_ftprintf_s(fp, _T("%lf,"), m_dGrrBeForeLaserPos[i]);
		}

		for (i = 0; i < 3; i++)
		{
			_ftprintf_s(fp, _T("%lf,"), m_dGrrLaserPos[i]);
		}
		for (i = 0; i < 6; i++)
		{
			_ftprintf_s(fp, _T("%lf,"), m_dGrrMotorPos[i]);
		}
		for (i = 0; i < 3; i++)
		{
			_ftprintf_s(fp, _T("%lf,"), m_dGrrAlignPos[i]);
		}
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[0] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[1] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[2] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[3]) / 4);
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[4] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[5]) / 2);
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[6] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[7]) / 2);
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[8] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[9]) / 2);
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[10] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[11]) / 2);
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[12] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[13]) / 2);
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[14] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[15]) / 2);
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[16] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[17]) / 2);
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[18] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[19]) / 2);
		_ftprintf_s(fp, _T("%0.3lf, %0.3lf,"), g_clMesCommunication[nUnit].m_dMesUVAfterOC[0], g_clMesCommunication[nUnit].m_dMesUVAfterOC[1]);
		_ftprintf_s(fp, _T("%0.3lf, %0.3lf,"), g_clMesCommunication[nUnit].m_dMesUVAfterDeltaOC[0], g_clMesCommunication[nUnit].m_dMesUVAfterDeltaOC[1]);
		//Laser 4개
		//Pcb Motor 6개
		//Align 3개
		_ftprintf_s(fp, _T("\n"));
		fclose(fp);
	}
	return true;
}

//------------------------------------------------------------------------------------------------------------------------------


bool CMesCommunication::g_FovVertexLog(int nUnit)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szFilePath[SIZE_OF_1K];
	SYSTEMTIME stSysTime;
	CFileFind clFinder;
	CString sFileMode = _T("");
	CFile clFile;
	FILE* fp;
	int nStepNo;
	int i = 0;
	int j = 0;
	int indexX = 0;
	int indexY = 0;
	bool createBool = true;
	::GetLocalTime(&stSysTime);

	if (_tcslen(g_clTaskWork[nUnit].m_szChipID) <= 0)
		_tcscpy_s(g_clTaskWork[nUnit].m_szChipID, SIZE_OF_100BYTE, _T("(NULL)"));

	if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
		CreateDirectory(BASE_LOG_PATH, NULL);

	if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
		CreateDirectory(BASE_LOG_PATH, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Result"), BASE_LOG_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Result\\%04d%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Result\\%04d%02d\\%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	nStepNo = g_clTaskWork[nUnit].m_nCountOfTotalStepAA;

	TCHAR m_szModel[SIZE_OF_100BYTE];

#if (____MACHINE_NAME == MODEL_FRONT_100)
	_stprintf_s(m_szModel, SIZE_OF_100BYTE, _T("SHM100"));
#else
	_stprintf_s(m_szModel, SIZE_OF_100BYTE, _T("SHM150"));
#endif

#ifdef KUMI_TEST_MODE
	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\Test_EolLog_Vertex_%s_%04d%02d%02d.csv"), szPath, m_szModel, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
#else
	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\EolLog_Vertex_%s_%04d%02d%02d.csv"), szPath, m_szModel, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
#endif
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
	sFileMode = _T("w");
#endif


#if (____MACHINE_NAME == MODEL_FRONT_100)
	int roiCount = 16;
	TCHAR* pszCol[] = {
		_T("VFOV_0") ,_T("VFOV_1") ,
		_T("VFOV_2") ,_T("VFOV_3") ,
		_T("VFOV_4") ,_T("VFOV_5") ,
		_T("VFOV_6") ,_T("VFOV_7") ,

		_T("HFOV_0") ,_T("HFOV_1") ,
		_T("HFOV_2") ,_T("HFOV_3") ,
		_T("HFOV_4") ,_T("HFOV_5") ,
		_T("HFOV_6") ,_T("HFOV_7")
		/*_T("TOP_CHART_LT_L") ,_T("TOP_CHART_LT_R") ,
		_T("TOP_CHART_RT_L") ,_T("TOP_CHART_RT_R") ,
		_T("TOP_CHART_BL_L") ,_T("TOP_CHART_BL_R") ,
		_T("TOP_CHART_BR_L") ,_T("TOP_CHART_BR_R") ,
		_T("LEFT_SIDE_CHART_4F_T") ,_T("LEFT_SIDE_CHART_4F_B") ,
		_T("LEFT_SIDE_CHART_7F_T") ,_T("LEFT_SIDE_CHART_7F_B") ,
		_T("RIGHT_SIDE_CHART_4F_T") ,_T("RIGHT_SIDE_CHART_4F_B"),
		_T("RIGHT_SIDE_CHART_7F_T"),_T("RIGHT_SIDE_CHART_7F_B")*/
	};
#else
	int roiCount = 14;
	TCHAR* pszCol[] = {
		_T("VFOV_0") ,_T("VFOV_1") ,
		_T("VFOV_2") ,_T("VFOV_3") ,
		_T("VFOV_4") ,_T("VFOV_5") ,
		_T("VFOV_6") ,_T("VFOV_7") ,

		_T("HFOV_0") ,_T("HFOV_1") ,
		_T("HFOV_2") ,_T("HFOV_3") ,
		_T("HFOV_4") ,_T("HFOV_5")
		/*_T("LEFT_SIDE_CHART_4F_T_BL") ,_T("LEFT_SIDE_CHART_4F_T_TR") ,
		_T("LEFT_SIDE_CHART_4F_B_TL") ,_T("LEFT_SIDE_CHART_4F_B_BR") ,
		_T("LEFT_SIDE_CHART_7F_T") ,
		_T("LEFT_SIDE_CHART_7F_M") ,
		_T("LEFT_SIDE_CHART_7F_B") ,
		_T("RIGHT_SIDE_CHART_4F_T_TL") ,_T("RIGHT_SIDE_CHART_4F_T_BR") ,
		_T("RIGHT_SIDE_CHART_4F_B_BL") ,_T("RIGHT_SIDE_CHART_4F_B_TR") ,
		_T("RIGHT_SIDE_CHART_7F_T") ,
		_T("RIGHT_SIDE_CHART_7F_M") ,
		_T("RIGHT_SIDE_CHART_7F_B") ,*/
	};
#endif
	// 파일이 없으면 헤더를 만든다.
	if (clFinder.FindFile(szFilePath) == FALSE)
	{
		_tfopen_s(&fp, szFilePath, sFileMode);
		if (fp != NULL)
		{
			_ftprintf_s(fp, _T(",,,,,"));
			for (i = 0; i < MAX_FOV_FIND_COUNT; i++)
			{
				if (i > 0)
				{
					_ftprintf_s(fp, _T(",,"));
				}
				_ftprintf_s(fp, _T("%s"), pszCol[i]);
			}
			fprintf_s(fp, "\n");
			//
			fprintf_s(fp, "Date,Time ");
			fprintf_s(fp, ",SW Version,Model");
			fprintf_s(fp, ",BarcodeID");
			for (i = 0; i < MAX_FOV_FIND_COUNT; i++)
			{
				_ftprintf_s(fp, _T(",x,y"));
			}


			fprintf_s(fp, "\n");
			fclose(fp);
		}
	}

#ifdef _UNICODE
	sFileMode = _T("a,ccs=UTF-8");
#else
	sFileMode = _T("a");
#endif
	_tfopen_s(&fp, szFilePath, sFileMode);
	if (fp != NULL)
	{
		_ftprintf_s(fp, _T("'%04d-%02d-%02d,"), stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
		_ftprintf_s(fp, _T("'%02d:%02d:%02d,"), stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);
		_ftprintf_s(fp, _T("VER.%s, %s,"), VER_STR, m_szModel);
		_ftprintf_s(fp, _T("%s,"), g_clTaskWork[nUnit].m_szChipID);
		for (i = 0; i < MAX_FOV_FIND_COUNT; i++)
		{
			fprintf_s(fp, "%d,%d,", g_clMandoInspLog[nUnit].m_ShmFovPoint[i].x, g_clMandoInspLog[nUnit].m_ShmFovPoint[i].y);
		}

		//
		_ftprintf_s(fp, _T("\n"));
		fclose(fp);
	}
	return true;
}


//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

bool CMesCommunication::g_FinalEolLog(int nUnit)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szFilePath[SIZE_OF_1K];
	SYSTEMTIME stSysTime;
	CFileFind clFinder;
	CString sFileMode = _T("");
	CFile clFile;
	FILE* fp;
	int nStepNo;
	int i = 0;
	int j = 0;
	int indexX = 0;
	int indexY = 0;
	bool createBool = true;
	::GetLocalTime(&stSysTime);

	if (_tcslen(g_clTaskWork[nUnit].m_szChipID) <= 0)
		_tcscpy_s(g_clTaskWork[nUnit].m_szChipID, SIZE_OF_100BYTE, _T("(NULL)"));

	if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
		CreateDirectory(BASE_LOG_PATH, NULL);

	if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
		CreateDirectory(BASE_LOG_PATH, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Result"), BASE_LOG_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Result\\%04d%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\Result\\%04d%02d\\%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	nStepNo = g_clTaskWork[nUnit].m_nCountOfTotalStepAA;

	TCHAR m_szModel[SIZE_OF_100BYTE];



#if (____MACHINE_NAME == MODEL_FRONT_100)
	_stprintf_s(m_szModel, SIZE_OF_100BYTE, _T("SHM100"));
#else
	_stprintf_s(m_szModel, SIZE_OF_100BYTE, _T("SHM150"));
#endif
#ifdef KUMI_TEST_MODE
	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\Test_FinalEolLog_%s_%04d%02d%02d.csv"), szPath, m_szModel, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
#else
	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\FinalEolLog_%s_%04d%02d%02d.csv"), szPath, m_szModel, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
#endif

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
	sFileMode = _T("w");
#endif

	// 파일이 없으면 헤더를 만든다.
	if (clFinder.FindFile(szFilePath) == FALSE)
	{
		_tfopen_s(&fp, szFilePath, sFileMode);
		if (fp != NULL)
		{
			_ftprintf_s(fp, _T("Time,"));
			_ftprintf_s(fp, _T("Model,				SW Version,"));
			_ftprintf_s(fp, _T("Chip ID,Sensor Serial ID,"));
			//전류, 볼테이지
			_ftprintf_s(fp, _T("CURRENT ,VOLTAGE,"));


			//MTF 개별
			_ftprintf_s(fp, _T("[SFR]0.0F T_V,		[SFR]0.0F B_V,		[SFR]0.0F L_H,		[SFR]0.0F R_H,"));
			_ftprintf_s(fp, _T("[SFR]0.4F TL H ,	[SFR]0.4F TL V,		[SFR]0.4F TR H ,	[SFR]0.4F TR V,		[SFR]0.4F BL H ,	[SFR]0.4F BL V,		[SFR]0.4F BR H ,	[SFR]0.4F BR V,"));
			_ftprintf_s(fp, _T("[SFR]0.7F TL H ,	[SFR]0.7F TL V,		[SFR]0.7F TR H ,	[SFR]0.7F TR V,		[SFR]0.7F BL H ,	[SFR]0.7F BL V,		[SFR]0.7F BR H ,	[SFR]0.7F BR V,"));
			//MTF 평균
			_ftprintf_s(fp, _T("[SFR]0.0F AVERAGE,"));
			_ftprintf_s(fp, _T("[SFR]0.4F LT AVERAGE,[SFR]0.4F RT AVERAGE,[SFR]0.4F LB AVERAGE,[SFR]0.4F RB AVERAGE,"));
			_ftprintf_s(fp, _T("[SFR]0.7F LT AVERAGE,[SFR]0.7F RT AVERAGE,[SFR]0.7F LB AVERAGE,[SFR]0.7F RB AVERAGE,"));
			_ftprintf_s(fp, _T("[SFR]0.4F DIFF,[SFR]0.7F DIFF,"));

			//OC
			_ftprintf_s(fp, _T("[OC] OC_X ,	[OC] OC_Y,"));
			_ftprintf_s(fp, _T("[OC] OC_X DELTA ,	[OC] OC_Y DELTA,"));

			_ftprintf_s(fp, _T("[FOV] Horizontal,	[FOV] Vertical,"));
			//ROTATION
			_ftprintf_s(fp, _T("ROTATE ,"));

			//STAIN 12개
			_ftprintf_s(fp, _T("[Blemish] LCB ,[Blemish] FPF ,[Blemish] Ymean ,"));
			_ftprintf_s(fp, _T("[Blemish] LCB Max Value(Center) ,[Blemish] LCB Max Value(Edge) ,[Blemish] LCB Max Value(Corner) ,"));
			_ftprintf_s(fp, _T("[Blemish] FDF Max Value(Center) ,[Blemish] FDF Max Value(Edge) ,[Blemish] FDF Max Value(Corner) ,"));
			_ftprintf_s(fp, _T("[Blemish] Ymean Max Value(Center) ,[Blemish] Ymean Max Value(Edge) ,[Blemish] Ymean Max Value(Corner) ,"));

			//Relative Illumination (Shading)
			_ftprintf_s(fp, _T("[RI] Diff ,[RI] Center Intensity,"));
			_ftprintf_s(fp, _T("[RI] RIconer0 ,[RI] RIconer1 ,[RI] RIconer2 ,[RI] RIconer3 ,[RI] RIconer Min, "));

			//ColorReproduction
			_ftprintf_s(fp, _T("[CR] ROI1 ,[CR] ROI2 ,[CR] ROI3 ,[CR] ROI4 ,"));
			_ftprintf_s(fp, _T("[SATURATION] CHART 0F ,"));
			_ftprintf_s(fp, _T("[SATURATION] CHART 4F LT ,[SATURATION] CHART 4F RT ,[SATURATION] CHART 4F BL ,[SATURATION] CHART 4F BR ,"));
			_ftprintf_s(fp, _T("[SATURATION] CHART 7F LT ,[SATURATION] CHART 7F RT ,[SATURATION] CHART 7F BL ,[SATURATION] CHART 7F BR ,"));
			_ftprintf_s(fp, _T("[SATURATION] OC ,"));
			//
			_ftprintf_s(fp, _T("[Nor Flash Memory] ISP Version ,[Nor Flash Memory] ISP Model ,"));
			_ftprintf_s(fp, _T("[Error Flag Check] Image Sensor ,[Error Flag Check] PMIC ,"));
			_ftprintf_s(fp, _T("[Error Flag Check] Serializer1 ,[Error Flag Check] Serializer2 ,"));
			//--------------------------
			_ftprintf_s(fp, _T("[Saturation] TOP_Chart_Bright_LT,	[Saturation] TOP_Chart_Bright_LB,"));
			_ftprintf_s(fp, _T("[Saturation] TOP_Chart_Bright_RB,	[Saturation] TOP_Chart_Bright_RT,"));
			_ftprintf_s(fp, _T("[Saturation] Side_Chart_Bright_LT,	[Saturation] Side_Chart_Bright_LB,"));

			_ftprintf_s(fp, _T("[Saturation] Side_Chart_Bright_RT, [Saturation] Side_Chart_Bright_RB,"));
			_ftprintf_s(fp, _T("[Saturation] TOP_Chart_Bright_Avg,"));

			_ftprintf_s(fp, _T("[RI] OC_CENTER,"));

			_ftprintf_s(fp, _T("[Sensor Voltage] AVDD,[Sensor Voltage] OVDD,[Sensor Voltage] DVDD,"));

			_ftprintf_s(fp, _T("[F/W] ORIGINAL FILE, [F/W] JUDGE,"));
			_ftprintf_s(fp, _T("[Laser] TiltX, [Laser] TiltY,"));

			_ftprintf_s(fp, _T("NG LIST,JUDGE,"));
			_ftprintf_s(fp, _T("\n"));
			fclose(fp);
		}
	}
	g_clMesCommunication[nUnit].vMesApdData.clear();

#ifdef _UNICODE
	sFileMode = _T("a,ccs=UTF-8");
#else
	sFileMode = _T("a");
#endif

	_tfopen_s(&fp, szFilePath, sFileMode);
	if (fp != NULL)
	{

		_ftprintf_s(fp, _T("'%04d-%02d-%02d %02d:%02d:%02d,"), stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);
		_ftprintf_s(fp, _T("%s, %s,"), m_szModel, VER_STR);
		_ftprintf_s(fp, _T("%s,%s,"), g_clTaskWork[nUnit].m_szChipID, g_clMesCommunication[nUnit].m_sMesI2cSensorID);

		g_clMesCommunication[nUnit].vMesApdData.push_back(g_clTaskWork[nUnit].m_szChipID);
		g_clMesCommunication[nUnit].vMesApdData.push_back(g_clMesCommunication[nUnit].m_sMesI2cSensorID);
		//CURRENT , VOL
		_ftprintf_s(fp, _T("%.6lf,%.6lf,"), g_clMesCommunication[nUnit].m_dMesCurrent, g_clMesCommunication[nUnit].m_dMesVoltage);

		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesCurrent));
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesVoltage));
		//sfr 개별
		for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
		{
			_ftprintf_s(fp, _T("%lf,"), g_clMesCommunication[nUnit].m_dMesUvAfterMTF[i]);
			g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesUvAfterMTF[i]));
		}
		//sfr 필드 평균
		for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
		{
			_ftprintf_s(fp, _T("%lf,"), g_clMesCommunication[nUnit].m_dMesAreaAvrMTF[i]);
			g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesAreaAvrMTF[i]));
		}
		/*_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[0] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[1] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[2] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[3]) / 4);
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[4] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[5]) / 2);
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[6] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[7]) / 2);
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[8] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[9]) / 2);
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[10] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[11]) / 2);
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[12] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[13]) / 2);
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[14] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[15]) / 2);
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[16] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[17]) / 2);
		_ftprintf_s(fp, _T("%lf,"), (g_clMesCommunication[nUnit].m_dMesUvAfterMTF[18] + g_clMesCommunication[nUnit].m_dMesUvAfterMTF[19]) / 2);*/

		
		_ftprintf_s(fp, _T("%lf,%lf,"), g_clMesCommunication[nUnit].m_dMes4F_Diff, g_clMesCommunication[nUnit].m_dMes7F_Diff);
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMes4F_Diff));
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMes7F_Diff));
		//OC
		_ftprintf_s(fp, _T("%0.3lf, %0.3lf,"), g_clMesCommunication[nUnit].m_dMesUVAfterOC[0], g_clMesCommunication[nUnit].m_dMesUVAfterOC[1]);
		_ftprintf_s(fp, _T("%0.3lf, %0.3lf,"), g_clMesCommunication[nUnit].m_dMesUVAfterDeltaOC[0], g_clMesCommunication[nUnit].m_dMesUVAfterDeltaOC[1]);
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesUVAfterOC[0]));
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesUVAfterOC[1]));
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesUVAfterDeltaOC[0]));
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesUVAfterDeltaOC[1]));
		//FOV
		_ftprintf_s(fp, _T("%0.3lf, %0.3lf,"), g_clMesCommunication[nUnit].m_dMesFov[0], g_clMesCommunication[nUnit].m_dMesFov[1]);
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesFov[0]));
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesFov[1]));

		//ROTATE , TILT
		_ftprintf_s(fp, _T("%.3lf,"), g_clMesCommunication[nUnit].m_dMesUvAfterRotate);
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesUvAfterRotate));

		//STAIN 0 = LCB , 1 = FDF , 2 = RU_Ymean
		_ftprintf_s(fp, _T("%.1lf,%.1lf,%.1lf,"), g_clMesCommunication[nUnit].m_nMesBlemish[0], g_clMesCommunication[nUnit].m_nMesBlemish[1], g_clMesCommunication[nUnit].m_nMesBlemish[2]);
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_nMesBlemish[0]));
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_nMesBlemish[1]));
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_nMesBlemish[2]));
		for (i = 0; i < 9; i++)
		{
			_ftprintf_s(fp, _T("%.1lf,"), g_clMesCommunication[nUnit].m_nMesBlemishMaxDefect[i]);	//lcb , fdf , ymean
			g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_nMesBlemishMaxDefect[i]));
		}


		//RI
		_ftprintf_s(fp, _T("%.3lf,%.3lf,"), g_clMesCommunication[nUnit].m_dMesRiDiff, g_clMesCommunication[nUnit].m_dMesRiCenterRaw);
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesRiDiff));
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesRiCenterRaw));
		for (i = 0; i < 4; i++)
		{
			_ftprintf_s(fp, _T("%lf,"), g_clMesCommunication[nUnit].m_nMesRICorner[i]);
			g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_nMesRICorner[i]));
		}

		_ftprintf_s(fp, _T("%lf,"), g_clMesCommunication[nUnit].m_dMesRiMinDiff);
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesRiMinDiff));

		for (i = 0; i < 4; i++)
		{
			_ftprintf_s(fp, _T("%lf,"), g_clMesCommunication[nUnit].m_nMesColorReproduction[i]);
			g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_nMesColorReproduction[i]));
		}

		for (i = 0; i < 9; i++)
		{
			_ftprintf_s(fp, _T("%lf,"), g_clMesCommunication[nUnit].m_dMesSaturationChart[i]);
			g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesSaturationChart[i]));
		}
		_ftprintf_s(fp, _T("%lf,"), g_clMesCommunication[nUnit].m_dMesSaturationOc);
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesSaturationOc));
		char buffer[10];  // 충분한 크기의 버퍼
		for (i = 0; i < 2; i++)
		{
			_ftprintf_s(fp, _T("%02X,"), g_clMesCommunication[nUnit].m_dIspData[i]);
			std::snprintf(buffer, sizeof(buffer), "%02X", g_clMesCommunication[nUnit].m_dIspData[i]);
			g_clMesCommunication[nUnit].vMesApdData.push_back(buffer);
			
		}
		//I2c
		for (i = 0; i < 4; i++)
		{
			_ftprintf_s(fp, _T("%02X,"), g_clMesCommunication[nUnit].m_dI2cData[i]);
			std::snprintf(buffer, sizeof(buffer), "%02X", g_clMesCommunication[nUnit].m_dI2cData[i]);
			g_clMesCommunication[nUnit].vMesApdData.push_back(buffer);
		}


		//차트 , oc Bright
		for (i = 0; i < 9; i++)
		{
			_ftprintf_s(fp, _T("%d,"), g_clMesCommunication[nUnit].m_dChartBright[i]);
			g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dChartBright[i]));
		}
		for (i = 0; i < 1; i++)
		{
			_ftprintf_s(fp, _T("%d,"), g_clMesCommunication[nUnit].m_dOcBright[i]);
			g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dOcBright[i]));
		}
		for (i = 0; i < 3; i++)
		{
			_ftprintf_s(fp, _T("%lf,"), g_clMesCommunication[nUnit].m_dMesSensorVoltage[i]);
			g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesSensorVoltage[i]));
		}
		//펌웨어 비교 원본 파일명
		_ftprintf_s(fp, _T("%s,"), g_clTaskWork[nUnit].m_szBinaryFile);
		g_clMesCommunication[nUnit].vMesApdData.push_back(g_clTaskWork[nUnit].m_szBinaryFile);
		if (g_clMesCommunication[nUnit].m_nMesFirmwareVerifyResult == 1)
		{
			fprintf_s(fp, "PASS,");
			g_clMesCommunication[nUnit].vMesApdData.push_back("PASS");
		}
		else
		{
			TCHAR* pszVerify[] = {
				_T("File Save"),_T(" "),
				_T("Original READ"),_T("SetWPDisable"),_T("GetCatMultiRegister"),_T("SetWPEnable"),_T("Verify") };

			fprintf_s(fp, "FAIL(%s),", pszVerify[g_clMesCommunication[nUnit].m_nMesFirmwareVerifyResult]);

			char strbuffer[100];  // 버퍼 크기는 예상 문자열 길이에 따라 조정
			std::snprintf(strbuffer, sizeof(strbuffer), "FAIL(%s),", pszVerify[g_clMesCommunication[nUnit].m_nMesFirmwareVerifyResult]);
			g_clMesCommunication[nUnit].vMesApdData.push_back(strbuffer);
		}

		_ftprintf_s(fp, _T("%lf,"), g_clMesCommunication[nUnit].m_dMesLaserTilt[0]);
		_ftprintf_s(fp, _T("%lf,"), g_clMesCommunication[nUnit].m_dMesLaserTilt[1]);

		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesLaserTilt[0]));
		g_clMesCommunication[nUnit].vMesApdData.push_back(to_string(g_clMesCommunication[nUnit].m_dMesLaserTilt[1]));
		//
		//
		if (g_clMesCommunication[nUnit].m_nMesFinalResult == 1)		fprintf_s(fp, "%s ,OK,", g_clMandoInspLog[nUnit].m_sNGList);
		else														fprintf_s(fp, "%s ,NG,", g_clMandoInspLog[nUnit].m_sNGList);
		//
		_ftprintf_s(fp, _T("\n"));
		fclose(fp);
	}

	return true;
}
bool CMesCommunication::MesEolSave(int nUnit)
{
	SYSTEMTIME stSysTime;
	CString strLine = _T("");
	CStdioFile StdFile;
	CFileException e;

	TCHAR loadPath[SIZE_OF_1K];
	TCHAR szLog[SIZE_OF_1K];
	double mMesTempValue = 0.0;
	GetLocalTime(&stSysTime);
	//if (m_sMesLotID.GetLength() < 12)
	//{
	//	_stprintf_s(szLog, SIZE_OF_1K, _T("[MES] LOT ERROR:%s"), m_sMesLotID);
	//	AddLog(szLog, 1, nUnit);
	//	return false;
	//}

	TCHAR szPath[SIZE_OF_1K];
	TCHAR szRootPath[SIZE_OF_1K];
	TCHAR szTempPath[SIZE_OF_1K];
	SYSTEMTIME time;
	::GetLocalTime(&time);


	int i = 0;
	int j = 0;
	CFileFind clFinder;
#ifdef NORINDA_MODE
	_stprintf_s(szRootPath, SIZE_OF_1K, _T("c:\\BMS_MES"));// _T("\\\\192.168.0.79\\BMS_MES"));	
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\TEMPMES"), szRootPath);
#else
	_stprintf_s(szRootPath, SIZE_OF_1K, _T("\\\\192.168.5.1\\BMS_MES"));	//EOL//_T("C:\\BMS_MES"));	//EOL
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\TEMPMES"), szRootPath);
#endif

	if (clFinder.FindFile(szPath) == FALSE)
	{
		CreateDirectory(szPath, NULL);
	}

	//_stprintf_s(szMainPath, SIZE_OF_1K, _T("\\\\192.168.5.1\\BMS_MES"));
	//------------------------------------------------------------------------------------------------------------------------------------------
	//
	//
	//이전 모델 data Load
	//
	//------------------------------------------------------------------------------------------------------------------------------------------
	_stprintf_s(szTempPath, SIZE_OF_1K, _T("%s\\%s_%d_%04d%02d%02d%02d%02d%02d.txt"), szPath, g_clSysData.m_szFactoryCd, m_nMesCnt, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s_%d_%04d%02d%02d%02d%02d%02d.txt"), szRootPath, g_clSysData.m_szFactoryCd, m_nMesCnt, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);

	//------------------------------------------------------------------------------------------------------------------------------------------
	//
	if (StdFile.Open(szTempPath, CStdioFile::modeCreate | CFile::modeReadWrite))
	{
		strLine.Format("%s,", m_sMesLotID);				// 바코드명
		StdFile.WriteString(strLine);
		strLine.Format("%d,", m_nMesCnt);					// 차수
		StdFile.WriteString(strLine);
		strLine.Format("%d,", m_nMesFinalResult);			// 최종합부
		StdFile.WriteString(strLine);

		strLine.Format("%d:%d,", m_dwMesCycleTime, 1);
		StdFile.WriteString(strLine);
		strLine.Format("%.2lf:%d,", m_dMesCurrent, m_nMesCurrentResult);
		StdFile.WriteString(strLine);

		//SFR 20개 + 9개 + 1개
		for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
		{
			strLine.Format(_T("%.03lf:%d,"), m_dMesUvAfterMTF[i], m_nMesUvAfterMTFResultUVAfter[i]);
			StdFile.WriteString(strLine);
		}
		strLine.Format(_T("%.03lf:%d,"), m_dMesAreaAvrMTF[0], m_nMesMTFAreaAvrResult[0]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%.03lf:%d,"), m_dMesAreaAvrMTF[1], m_nMesMTFAreaAvrResult[1]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%.03lf:%d,"), m_dMesAreaAvrMTF[2], m_nMesMTFAreaAvrResult[2]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%.03lf:%d,"), m_dMesAreaAvrMTF[3], m_nMesMTFAreaAvrResult[3]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%.03lf:%d,"), m_dMesAreaAvrMTF[4], m_nMesMTFAreaAvrResult[4]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%.03lf:%d,"), m_dMesAreaAvrMTF[5], m_nMesMTFAreaAvrResult[5]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%.03lf:%d,"), m_dMesAreaAvrMTF[6], m_nMesMTFAreaAvrResult[6]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%.03lf:%d,"), m_dMesAreaAvrMTF[7], m_nMesMTFAreaAvrResult[7]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%.03lf:%d,"), m_dMesAreaAvrMTF[8], m_nMesMTFAreaAvrResult[8]);
		StdFile.WriteString(strLine);

		strLine.Format(_T("%.03lf:%d,"), m_dMes7FVariation, m_dMes7FVariationResult);
		StdFile.WriteString(strLine);


		//[OC] OC_X
		//[OC] OC_Y
		//[OC] Delta_X
		//[OC] Delta_Y

		strLine.Format(_T("%.02lf:%d,"), m_dMesUVAfterOC[0], m_dMesUVAfterOCResult[0]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%.02lf:%d,"), m_dMesUVAfterOC[1], m_dMesUVAfterOCResult[1]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%.02lf:%d,"), m_dMesUVAfterDeltaOC[0], m_dMesUVAfterOCResult[0]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%.02lf:%d,"), m_dMesUVAfterDeltaOC[1], m_dMesUVAfterOCResult[1]);
		StdFile.WriteString(strLine);


		//[Rotate] Rotate(°)
		//[Tilt] Tilt_X(°)
		//[Tilt] Tilt_Y(°)

		strLine.Format(_T("%.02lf:%d,"), m_dMesUvAfterRotate, m_dMesRotateUVAfterResult);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%.02lf:%d,"), m_dMesTilt[0], m_dMesTiltResult[0]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%.02lf:%d,"), m_dMesTilt[1], m_dMesTiltResult[1]);
		StdFile.WriteString(strLine);

		//[Defect] Hot
		//[Defect] Dead
		//[Defect] Row
		//[Defect] Column
		strLine.Format(_T("%d:%d,"), m_nMesDefect[8], m_nMesDefectResult[8]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%d:%d,"), m_nMesDefect[9], m_nMesDefectResult[9]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%d:%d,"), m_nMesDefect[10], m_nMesDefectResult[10]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%d:%d,"), m_nMesDefect[11], m_nMesDefectResult[11]);
		StdFile.WriteString(strLine);

		//[Blemish] FDF
		//[Blemish] LCB
		//[Blemish] Ymean
		//[Blemish] FDF Max Value (Center)
		//[Blemish] FDF Max Value (Edge)
		//[Blemish] FDF Max Value (Corner)
		//[Blemish] LCB Max Value (Center)
		//[Blemish] LCB Max Value (Edge)
		//[Blemish] LCB Max Value (Corner)
		//[Blemish] Ymean Max Value (Center)
		//[Blemish] Ymean Max Value (Edge)
		//[Blemish] Ymean Max Value (Corner)
		for (i = 0; i < 3; i++)
		{
			strLine.Format(_T("%.01lf:%d,"), m_nMesBlemish[i], m_nMesBlemishResult[i]);
			StdFile.WriteString(strLine);
		}
		for (i = 0; i < 9; i++)
		{
			strLine.Format(_T("%.01lf:%d,"), m_nMesBlemishMaxDefect[i], m_nMesBlemishMaxDefectResult[i]);
			StdFile.WriteString(strLine);
		}

		//[CU] Delta_Sum_Min
		//[CU] Delta_Sum_Max :판정 o
		//[CU] Delta_RG_Min
		//[CU] Delta_RG_Max :판정 o
		//[CU] Delta_BG_Min
		//[CU] Delta_BG_Max :판정 o
		//[CU] Delta_GrGb_Min
		//[CU] Delta_GrGb_Max :판정 o
		for (i = 0; i < 8; i++)
		{
			strLine.Format(_T("%.03lf:%d,"), m_nMesColorUniformity[i], m_nMesColorUniformityResult[i]);
			StdFile.WriteString(strLine);
		}

		//[RI] ROI0_R
		//[RI] ROI0_Gr
		//[RI] ROI0_Gb
		//[RI] ROI0_B
		//[RI] ROI1_R
		//[RI] ROI1_Gr
		//[RI] ROI1_Gb
		//[RI] ROI1_B
		//[RI] ROI2_R
		//[RI] ROI2_Gr
		//[RI] ROI2_Gb
		//[RI] ROI2_B
		//[RI] ROI3_R
		//[RI] ROI3_Gr
		//[RI] ROI3_Gb
		//[RI] ROI3_B
		//[RI] ROI4_R
		//[RI] ROI4_Gr
		//[RI] ROI4_Gb
		//[RI] ROI4_B

		//[RI] RI_Min_R(%)
		//[RI] RI_Min_Gr(%)
		//[RI] RI_Min_Gb(%)
		//[RI] RI_Min_B(%)

		//[RI] RG_Min(%)
		//[RI] RG_Max(%)
		//[RI] BG_Min(%)
		//[RI] BG_Max(%)
		for (i = 0; i < 5; i++)
		{
			strLine.Format(_T("%.03lf:%d,"), m_nMesRIRoi[0][i][0], m_nMesRIRoiResult[0][i][0]);
			StdFile.WriteString(strLine);
			strLine.Format(_T("%.03lf:%d,"), m_nMesRIRoi[0][i][1], m_nMesRIRoiResult[0][i][1]);
			StdFile.WriteString(strLine);
			strLine.Format(_T("%.03lf:%d,"), m_nMesRIRoi[0][i][2], m_nMesRIRoiResult[0][i][2]);
			StdFile.WriteString(strLine);
			strLine.Format(_T("%.03lf:%d,"), m_nMesRIRoi[0][i][3], m_nMesRIRoiResult[0][i][3]);
			StdFile.WriteString(strLine);
		}
		for (i = 0; i < 8; i++)
		{
			strLine.Format(_T("%.03lf:%d,"), m_nMesRI[0][i], m_nMesRIResult[0][i]);
			StdFile.WriteString(strLine);
		}

		//[Dark Pixel Uniformity] ROI0_R
		//[Dark Pixel Uniformity] ROI0_Gr
		//[Dark Pixel Uniformity] ROI0_Gb
		//[Dark Pixel Uniformity] ROI0_B
		//[Dark Pixel Uniformity] ROI1_R
		//[Dark Pixel Uniformity] ROI1_Gr
		//[Dark Pixel Uniformity] ROI1_Gb
		//[Dark Pixel Uniformity] ROI1_B
		//[Dark Pixel Uniformity] ROI2_R
		//[Dark Pixel Uniformity] ROI2_Gr
		//[Dark Pixel Uniformity] ROI2_Gb
		//[Dark Pixel Uniformity] ROI2_B
		//[Dark Pixel Uniformity] ROI3_R
		//[Dark Pixel Uniformity] ROI3_Gr
		//[Dark Pixel Uniformity] ROI3_Gb
		//[Dark Pixel Uniformity] ROI3_B
		//[Dark Pixel Uniformity] ROI4_R
		//[Dark Pixel Uniformity] ROI4_Gr
		//[Dark Pixel Uniformity] ROI4_Gb
		//[Dark Pixel Uniformity] ROI4_B
		//[Dark Pixel Uniformity] RI_Min_R(%)
		//[Dark Pixel Uniformity] RI_Min_Gr(%)
		//[Dark Pixel Uniformity] RI_Min_Gb(%)
		//[Dark Pixel Uniformity] RI_Min_B(%)
		for (i = 0; i < 5; i++)
		{
			strLine.Format(_T("%.03lf:%d,"), m_nMesRIRoi[1][i][0], m_nMesRIRoiResult[1][i][0]);
			StdFile.WriteString(strLine);
			strLine.Format(_T("%.03lf:%d,"), m_nMesRIRoi[1][i][1], m_nMesRIRoiResult[1][i][1]);
			StdFile.WriteString(strLine);
			strLine.Format(_T("%.03lf:%d,"), m_nMesRIRoi[1][i][2], m_nMesRIRoiResult[1][i][2]);
			StdFile.WriteString(strLine);
			strLine.Format(_T("%.03lf:%d,"), m_nMesRIRoi[1][i][3], m_nMesRIRoiResult[1][i][3]);
			StdFile.WriteString(strLine);
		}
		for (i = 0; i < 4; i++)		//dark는 4개만
		{
			strLine.Format(_T("%.03lf:%d,"), m_nMesRI[1][i], m_nMesRIResult[1][i]);
			StdFile.WriteString(strLine);
		}
		//[SNR] SNR_R_5000K
		//[SNR] SNR_Gr_5000K
		//[SNR] SNR_Gb_5000K
		//[SNR] SNR_B_5000K

		//[FPN] C_FPN_R_5000K
		//[FPN] C_FPN_Gr_5000K
		//[FPN] C_FPN_Gb_5000K
		//[FPN] C_FPN_B_5000K

		//[FPN] R_FPN_R_5000K
		//[FPN] R_FPN_Gr_5000K
		//[FPN] R_FPN_Gb_5000K
		//[FPN] R_FPN_B_5000K
		for (i = 0; i < 4; i++)
		{
			strLine.Format(_T("%.03lf:%d,"), m_nMesFpn5000[0][i], m_nMesFpn5000Result[0][i]);
			StdFile.WriteString(strLine);
		}
		for (i = 0; i < 4; i++)
		{
			strLine.Format(_T("%.03lf:%d,"), m_nMesFpn5000[2][i], m_nMesFpn5000Result[2][i]);	//Col먼저라서 2 index
			StdFile.WriteString(strLine);
		}
		for (i = 0; i < 4; i++)
		{
			strLine.Format(_T("%.03lf:%d,"), m_nMesFpn5000[1][i], m_nMesFpn5000Result[1][i]);
			StdFile.WriteString(strLine);
		}
		//
		//[SNR] SNR_R_Dark
		//[SNR] SNR_Gr_Dark
		//[SNR] SNR_Gb_Dark
		//[SNR] SNR_B_Dark

		//[FPN] C_FPN_R_Dark
		//[FPN] C_FPN_Gr_Dark
		//[FPN] C_FPN_Gb_Dark
		//[FPN] C_FPN_B_Dark

		//[FPN] R_FPN_R_Dark
		//[FPN] R_FPN_Gr_Dark
		//[FPN] R_FPN_Gb_Dark
		//[FPN] R_FPN_B_Dark
		for (i = 0; i < 4; i++)
		{
			strLine.Format(_T("%.03lf:%d,"), m_nMesFpnDark[0][i], m_nMesFpnDarkResult[0][i]);
			StdFile.WriteString(strLine);
		}
		for (i = 0; i < 4; i++)
		{
			strLine.Format(_T("%.03lf:%d,"), m_nMesFpnDark[2][i], m_nMesFpnDarkResult[2][i]);	//Col먼저라서 2 index
			StdFile.WriteString(strLine);
		}
		for (i = 0; i < 4; i++)
		{
			strLine.Format(_T("%.03lf:%d,"), m_nMesFpnDark[1][i], m_nMesFpnDarkResult[1][i]);
			StdFile.WriteString(strLine);
		}

		//[IR] Average Brightness
		//[IR] Standard Deviation
		strLine.Format(_T("%.03lf:%d,"), m_dMesIRFilterValue[1], m_dMesIRFilterResult[1]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%.03lf:%d,"), m_dMesIRFilterValue[2], m_dMesIRFilterResult[2]);
		StdFile.WriteString(strLine);
		//[WB] R_3000K
		//[WB] Gr_3000K
		//[WB] Gb_3000K
		//[WB] B_3000K
		//[WB] R_5000K
		//[WB] Gr_5000K
		//[WB] Gb_5000K
		//[WB] B_5000K
		//[WB] R_Dark
		//[WB] Gr_Dark
		//[WB] Gb_Dark
		//[WB] B_Dark

		for (i = 0; i < 3; i++)
		{
			strLine.Format(_T("%.03lf:%d,"), m_nMesColorSensitivity[i][0], m_nMesColorSensitivityResult[i][0]);
			StdFile.WriteString(strLine);
			strLine.Format(_T("%.03lf:%d,"), m_nMesColorSensitivity[i][1], m_nMesColorSensitivityResult[i][1]);
			StdFile.WriteString(strLine);
			strLine.Format(_T("%.03lf:%d,"), m_nMesColorSensitivity[i][2], m_nMesColorSensitivityResult[i][2]);
			StdFile.WriteString(strLine);
			strLine.Format(_T("%.03lf:%d,"), m_nMesColorSensitivity[i][3], m_nMesColorSensitivityResult[i][3]);
			StdFile.WriteString(strLine);
			strLine.Format(_T("%.03lf:%d,"), m_nMesColorSensitivity[i][4], m_nMesColorSensitivityResult[i][4]);
			StdFile.WriteString(strLine);
			strLine.Format(_T("%.03lf:%d,"), m_nMesColorSensitivity[i][5], m_nMesColorSensitivityResult[i][5]);
			StdFile.WriteString(strLine);
			strLine.Format(_T("%.03lf:%d,"), m_nMesColorSensitivity[i][6], m_nMesColorSensitivityResult[i][6]);
			StdFile.WriteString(strLine);
		}
		//[Lens Shading] CH0_Min_3000K
		//[Lens Shading] CH0_Avg_3000K
		//[Lens Shading] CH0_Max_3000K
		//[Lens Shading] CH1_Min_3000K
		//[Lens Shading] CH1_Avg_3000K
		//[Lens Shading] CH1_Max_3000K
		//[Lens Shading] CH2_Min_3000K
		//[Lens Shading] CH2_Avg_3000K
		//[Lens Shading] CH2_Max_3000K
		//[Lens Shading] CH3_Min_3000K
		//[Lens Shading] CH3_Avg_3000K
		//[Lens Shading] CH3_Max_3000K
		//
		//[Lens Shading] CH0_Min_5000K
		//[Lens Shading] CH0_Avg_5000K
		//[Lens Shading] CH0_Max_5000K
		//[Lens Shading] CH1_Min_5000K
		//[Lens Shading] CH1_Avg_5000K
		//[Lens Shading] CH1_Max_5000K
		//[Lens Shading] CH2_Min_5000K
		//[Lens Shading] CH2_Avg_5000K
		//[Lens Shading] CH2_Max_5000K
		//[Lens Shading] CH3_Min_5000K
		//[Lens Shading] CH3_Avg_5000K
		//[Lens Shading] CH3_Max_5000K
		for (i = 0; i < 12; i++)
		{
			strLine.Format(_T("%.03lf:%d,"), m_nMesLensShading[0][i], m_nMesLensShadingResult[0][i]);
			StdFile.WriteString(strLine);
		}
		for (i = 0; i < 12; i++)
		{
			strLine.Format(_T("%.03lf:%d,"), m_nMesLensShading[1][i], m_nMesLensShadingResult[1][i]);
			StdFile.WriteString(strLine);
		}

		//[Mean Values] Color temperature 1
		//[Mean Values] Color temperature 2
		//[Color Shading] Horizontal grid number
		//[Color Shading] Vertical grid number
		//[Color Shading] High color temperature
		//[Color Shading] Low color temperature


		//[CRC] Mean Values
		//[CRC] Color Shading



		//[Received MES_EEPROM] 0 to 99
		//[Received MES_EEPROM] 100 to 199
		//[Received MES_EEPROM] 200 to 299
		//[Received MES_EEPROM] 300 to 345
		//g_clMesCommunication[nUnit].mMesGetEEpromData[index]

		//[EEPROM] 346 to 445
		//[EEPROM] 446 to 545
		//[EEPROM] 546 to 645
		//[EEPROM] 646 to 745
		//[EEPROM] 746 to 845
		//[EEPROM] 846 to 945
		//[EEPROM] 946 to 1045
		//[EEPROM] 1046 to 1145
		//[EEPROM] 1146 to 1245
		//[EEPROM] 1246 to 1345
		//[EEPROM] 1346 to 1445
		//[EEPROM] 1446 to 1545
		//[EEPROM] 1546 to 1645
		//[EEPROM] 1646 to 1745
		//[EEPROM] 1746 to 1845
		//[EEPROM] 1846 to 1945
		//[EEPROM] 1946 to 2045
		//[EEPROM] 2046 to 2145
		//[EEPROM] 2146 to 2245
		//[EEPROM] 2246 to 2345
		//[EEPROM] 2346 to 2445
		//[EEPROM] 2446 to 2457

		int mEolStartAddr = 346;
		int mindex = 0;




#ifdef OC___LIGHT___OLD
		strLine.Format(_T("%d:%d\r\n"), m_dMesOcLightTime[0], 1);
		StdFile.WriteString(strLine);
#else
		//oc light channel
		for (i = 0; i < 4; i++)
		{
			m_dMesOcLightTimeResult[i] = 1;
			if (m_dMesOcLightTime[i] > 20000)
			{
				m_dMesOcLightTimeResult[i] = 0;
			}
		}

		strLine.Format(_T("%d:%d,"), m_dMesOcLightTime[0], m_dMesOcLightTimeResult[0]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%d:%d,"), m_dMesOcLightTime[1], m_dMesOcLightTimeResult[1]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%d:%d,"), m_dMesOcLightTime[2], m_dMesOcLightTimeResult[2]);
		StdFile.WriteString(strLine);
		strLine.Format(_T("%d:%d\r\n"), m_dMesOcLightTime[3], m_dMesOcLightTimeResult[3]);
		StdFile.WriteString(strLine);
#endif

		//
		StdFile.Close();
	}
	else
	{

		_stprintf_s(szLog, SIZE_OF_1K, _T("[MES] 파일 생성 실패"));
		AddLog(szLog, 1, nUnit);
		return false;
	}
	//CopyFile(szTempPath, szPath, TRUE);
	MoveFile(szTempPath, szPath);
	return true;
}

bool CMesCommunication::MesAASave(int nUnit)
{

	return true;

}


