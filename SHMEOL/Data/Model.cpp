#include "stdafx.h"
#include "Model.h"


CModelData::CModelData()
{
	int i;

	m_nUnit = 0;

	memset(m_szIniPath, 0x00, sizeof(m_szIniPath));
	m_nWidth = 0;
	m_nHeight = 0;

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
		m_nStainCount[i] = 0;
	}

	m_dwUvTime = 50;

	m_dEscapePosPcbZ = 0.0;

	m_nSensorAlignRetryCount = 0;
	m_dSensorAlignDelay = 0.0;
	m_nLaserRetryCount = 0;
	m_dLaserDelay = 0.0;

	m_nRunMode = 0;
	m_nComplMode = 0;
	m_nUvUse = 0;
	m_nLaserInUse = 0;
	m_nLaserOutUse = 0;
	m_nUnloadAfter1stAAUse = 0;
	m_nStainInspUse = 0;
	m_nDarkInspUse = 0;
	m_nCcdDefectInfpUse = 0;
	m_nFpsStopUse = 0;
	m_nPinStopUse = 0;
	m_fFpsStopVal = 5.0;
	m_nLaserControlLock = 0;
	m_nDomeChartUse = 0;
	m_nUVLampAlarmUse = 0;
	m_nAAPass = 0;
	m_nInspectionPass = 0;

	m_dOffsetPrevUV_X = 0.0;
	m_dOffsetPrevUV_Y = 0.0;
	m_dOffsetPrevUV_Z = 0.0;
	m_dOffsetPrevUV_Tx = 0.0;
	m_dOffsetPrevUV_Ty = 0.0;
	m_dOffsetPrevUV_Th = 0.0;

	m_dPCBVacuumDelay = 0.0;
	m_dPCBGripDelay = 0.0;
	m_dLensGripDelay = 0.0;
	m_dLaserTimeOut = 0.0;
	m_dFinalDelay = 0.0;
	m_dBondingDelay = 0.0;

	m_nSensorCnt = 1;

	for (i = 0; i < MAX_LIGHT_COUNT; i++)
	{
		m_nLight[i] = 0;
	}

	for (i = 0; i < 14; i++)
	{
		m_nDomeLightVal[i] = 0;
	}

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
}
CModelData::~CModelData()
{

}
void CModelData::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}
void CModelData::Load(TCHAR* szModelName)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szIniBuff[SIZE_OF_1K];
	CString sToken = _T("");
	int i, j;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s\\%s_AA%d.ini"), BASE_MODEL_PATH, szModelName, szModelName, m_nUnit + 1);

	// 센서 구동 파일
	GetPrivateProfileString(_T("SensorInit"), _T("Path"), _T(""), m_szIniPath, sizeof(m_szIniPath), szPath);

	// TEACH DATA
	for (i = 0; i < MAX_POS_COUNT; i++)
	{
		GetPrivateProfileString(_T("TEACH"), POS_NAME2[i], _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		for (j = 0; j < MAX_MOTOR_COUNT; j++)
		{
			AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
			m_stTeachData[i].dPos[j] = _ttof((TCHAR*)(LPCTSTR)sToken);
		}
	}

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

	for (i = 0; i < 2; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("AF%d"), i + 1);
		GetPrivateProfileString(_T("ACTIVE_ALIGN"), szIniIndex, _T(""), szIniBuff, sizeof(szIniBuff), szPath);
		for (j = 0; j < 7; j++)
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
					m_stAFInfo[i].nMaxStepCount = 60;
				break;
				// Limit MTF
			case 5:		m_stAFInfo[i].fLimitMTF = (float)_ttof((TCHAR*)(LPCTSTR)sToken);	break;
				// SFR 평균 카운트
			case 6:		m_stAFInfo[i].nAvgSfrCount = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
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
	m_dwUvTime = GetPrivateProfileInt(_T("UV"), _T("Time"), 50, szPath);

	// PCB Z축 회피 위치
	GetPrivateProfileString(_T("ESCAPE_POS"), _T("PcbZ"), _T("0.0"), szIniBuff, sizeof(szIniBuff), szPath);
	m_dEscapePosPcbZ = _ttof(szIniBuff);

	m_nSensorAlignRetryCount = GetPrivateProfileInt(_T("ALIGN_RETRY"), _T("Retry_Count"), 0, szPath);
	m_nLaserRetryCount = GetPrivateProfileInt(_T("LASER_CONTROL"), _T("Retry_Count"), 0, szPath);

	// Delay Time 관련
	GetPrivateProfileString(_T("DelayTime"), _T("Time"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (j = 0; j < 8; j++)
	{
		AfxExtractSubString(sToken, szIniBuff, j, _T('/'));
		switch (j)
		{
		case 0:		m_dPCBVacuumDelay = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 1:		m_dPCBGripDelay = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 2:		m_dLensGripDelay = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 3:		m_dLaserDelay = _ttof((TCHAR*)(LPCTSTR)sToken);			break;
		case 4:		m_dSensorAlignDelay = _ttof((TCHAR*)(LPCTSTR)sToken);	break;
		case 5:		m_dLaserTimeOut = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 6:		m_dFinalDelay = _ttof((TCHAR*)(LPCTSTR)sToken);			break;
		case 7:		m_dBondingDelay = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		}
	}

	m_nRunMode = GetPrivateProfileInt(_T("RUN_MODE"), _T("Mode"), 0, szPath);
	m_nComplMode = GetPrivateProfileInt(_T("COMPL_MODE"), _T("Use"), 0, szPath);
	m_nUvUse = GetPrivateProfileInt(_T("UV"), _T("Use"), 1, szPath);
	m_nLaserInUse = GetPrivateProfileInt(_T("LASER_IN"), _T("Use"), 1, szPath);
	m_nLaserOutUse = GetPrivateProfileInt(_T("LASER_OUT"), _T("Use"), 1, szPath);
	m_nUnloadAfter1stAAUse = GetPrivateProfileInt(_T("UNLOAD_AFTER_1ST_AA"), _T("Use"), 0, szPath);
	m_nStainInspUse = GetPrivateProfileInt(_T("STAIN_INSP"), _T("Use"), 1, szPath);
	m_nDarkInspUse = GetPrivateProfileInt(_T("DARK_INSP"), _T("Use"), 0, szPath);
	m_nCcdDefectInfpUse = GetPrivateProfileInt(_T("CCD_DEFECT_INSP"), _T("Use"), 1, szPath);
	m_nFpsStopUse = GetPrivateProfileInt(_T("FPS_STOP"), _T("Use"), 0, szPath);
	GetPrivateProfileString(_T("FPS_STOP"), _T("Value"), _T("5.0"), szIniBuff, sizeof(szIniBuff), szPath);
	m_fFpsStopVal = (float)_ttof(szIniBuff);
	m_nLaserControlLock = GetPrivateProfileInt(_T("LASER_CONTROL"), _T("Use"), 0, szPath);
	m_nDomeChartUse = GetPrivateProfileInt(_T("DOME_CHART"), _T("Use"), 0, szPath);
	m_nUVLampAlarmUse = GetPrivateProfileInt(_T("UV_LAMP_ALARM"), _T("Use"), 0, szPath);
	m_nAAPass = GetPrivateProfileInt(_T("AA_PASS"), _T("Use"), 0, szPath);
	m_nInspectionPass = GetPrivateProfileInt(_T("INSPECTION_PASS"), _T("Use"), 0, szPath);

	if (m_nDomeChartUse == 1)
	{
		m_nWidth = GetPrivateProfileInt(_T("SENSOR"), _T("SENSOR_SIZE_X"), CCD1_CAM_SIZE_X, m_szIniPath);
		m_nHeight = GetPrivateProfileInt(_T("SENSOR"), _T("SENSOR_SIZE_Y"), CCD1_CAM_SIZE_Y, m_szIniPath);
	}
	else
	{
		m_nWidth = GetPrivateProfileInt(_T("SENSOR"), _T("SENSOR_SIZE_X"), CCD2_CAM_SIZE_X, m_szIniPath);
		m_nHeight = GetPrivateProfileInt(_T("SENSOR"), _T("SENSOR_SIZE_Y"), CCD2_CAM_SIZE_Y, m_szIniPath);
	}

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

	m_nPinStopUse = GetPrivateProfileInt(_T("SENSOR_COUNT"), _T("Use"), 0, szPath);
	m_nSensorCnt = GetPrivateProfileInt(_T("SENSOR_COUNT"), _T("Count"), 0, szPath);

	// 조명 데이터
	for (i = 0; i < MAX_LIGHT_COUNT; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("%02d"), i + 1);
		m_nLight[i] = GetPrivateProfileInt(_T("Light"), szIniIndex, 0, szPath);
	}

	// DOME 조명 DATA
	GetPrivateProfileString(_T("DOME_LIGHT"), _T("Value"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < 14; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		switch (i)
		{
		case 0:		m_nDomeLightVal[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 1:		m_nDomeLightVal[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 2:		m_nDomeLightVal[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 3:		m_nDomeLightVal[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 4:		m_nDomeLightVal[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 5:		m_nDomeLightVal[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 6:		m_nDomeLightVal[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 7:		m_nDomeLightVal[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 8:		m_nDomeLightVal[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 9:		m_nDomeLightVal[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 10:	m_nDomeLightVal[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 11:	m_nDomeLightVal[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 12:	m_nDomeLightVal[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		case 13:	m_nDomeLightVal[i] = _ttof((TCHAR*)(LPCTSTR)sToken);		break;
		}
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

	m_clSfrInfo.m_nSizeX = GetPrivateProfileInt(_T("SFR_SIZE"), _T("SIZE_X"), 50, szPath);
	m_clSfrInfo.m_nSizeY = GetPrivateProfileInt(_T("SFR_SIZE"), _T("SIZE_Y"), 57, szPath);

	m_nRoiSizeX = GetPrivateProfileInt(_T("ROI_SIZE"), _T("SIZE_X"), 50, szPath);
	m_nRoiSizeY = GetPrivateProfileInt(_T("ROI_SIZE"), _T("SIZE_Y"), 70, szPath);

	for (i = 0; i < (MAX_LAST_INSP_COUNT + MAX_DOME_INSP_ADD); i++)
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
			case 1:		m_clSfrInfo.m_clRectCircle[i].top = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
			case 2:		m_clSfrInfo.m_clRectCircle[i].right = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
			case 3:		m_clSfrInfo.m_clRectCircle[i].bottom = _ttoi((TCHAR*)(LPCTSTR)sToken);	break;
			}
		}
	}

	m_nMtfOverlayUse = GetPrivateProfileInt(_T("SfrOverlay"), _T("Use"), 0, szPath);

	GetPrivateProfileString(_T("StainLSB"), _T("Threshold"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < 3; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		switch (i)
		{
		case 0:
			m_dStainLsbCenter = _ttof((TCHAR*)(LPCTSTR)sToken);
			if (m_dStainLsbCenter == 0.0)
				m_dStainLsbCenter = 29.0;
			break;
		case 1:
			m_dStainLsbCorner = _ttof((TCHAR*)(LPCTSTR)sToken);
			if (m_dStainLsbCorner == 0.0)
				m_dStainLsbCorner = 65.0;
			break;
		case 2:
			m_dStainLsbEdge = _ttof((TCHAR*)(LPCTSTR)sToken);
			if (m_dStainLsbEdge == 0.0)
				m_dStainLsbEdge = 80.0;
			break;
		}

	}

	GetPrivateProfileString(_T("StainYMean"), _T("Threshold"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
	for (i = 0; i < 3; i++)
	{
		AfxExtractSubString(sToken, szIniBuff, i, _T('/'));
		switch (i)
		{
		case 0:
			m_dStainYMeanCenter = _ttof((TCHAR*)(LPCTSTR)sToken);
			if (m_dStainYMeanCenter == 0.0)
				m_dStainYMeanCenter = 3.0;
			break;
		case 1:
			m_dStainYMeanCorner = _ttof((TCHAR*)(LPCTSTR)sToken);
			if (m_dStainYMeanCorner == 0.0)
				m_dStainYMeanCorner = 6.0;
			break;
		case 2:
			m_dStainYMeanEdge = _ttof((TCHAR*)(LPCTSTR)sToken);
			if (m_dStainYMeanEdge == 0.0)
				m_dStainYMeanEdge = 6.0;
			break;
		}
	}

	m_nMarkNo = GetPrivateProfileInt(_T("Vision"), _T("MarkNo"), 0, szPath);
	m_nMinMatching = GetPrivateProfileInt(_T("Vision"), _T("Mathcing"), 80, szPath);
}
void CModelData::Save(TCHAR* szModelName)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szIniIndex[SIZE_OF_100BYTE];
	TCHAR szData[SIZE_OF_1K];
	int i;

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s\\%s_AA%d.ini"), BASE_MODEL_PATH, szModelName, szModelName, m_nUnit + 1);

	// 센서 구동 파일
	WritePrivateProfileString(_T("SensorInit"), _T("Path"), m_szIniPath, szPath);

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

	for (i = 0; i < 2; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("AF%d"), i + 1);
		_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf / %d / %.03lf / %d / %.03lf / %d"),
			m_stAFInfo[i].dMoveVel, m_stAFInfo[i].dMoveAcc, m_stAFInfo[i].nDelayTime, m_stAFInfo[i].dMoveDistance, m_stAFInfo[i].nMaxStepCount, m_stAFInfo[i].fLimitMTF, m_stAFInfo[i].nAvgSfrCount);
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

	_stprintf_s(szData, SIZE_OF_1K, _T("%d / %.03lf"), m_nCountOfCheckSFR, m_dSfrMoveDistance);
	WritePrivateProfileString(_T("SFR_DECREASE"), _T("Decrease"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d / %.03lf"), m_nCountOfCheckSFR, m_dSfrMoveDistance);
	WritePrivateProfileString(_T("SFR_DECREASE"), _T("Decrease"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nSfrMode);
	WritePrivateProfileString(_T("SFR_MODE"), _T("Mode"), szData, szPath);

	// SFR POSITION
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nSFR_N_POS);
	WritePrivateProfileString(_T("SFR_POS"), _T("Type"), szData, szPath);

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
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_dwUvTime);
	WritePrivateProfileString(_T("UV"), _T("Time"), szData, szPath);

	// PCB Z축 회피 위치
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf"), m_dEscapePosPcbZ);
	WritePrivateProfileString(_T("ESCAPE_POS"), _T("PcbZ"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nSensorAlignRetryCount);
	WritePrivateProfileString(_T("ALIGN_RETRY"), _T("Retry_Count"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nLaserRetryCount);
	WritePrivateProfileString(_T("LASER_CONTROL"), _T("Retry_Count"), szData, szPath);

	// Delay Time 관련
	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf / %.03lf / %.03lf / %.03lf / %.03lf / %.03lf / %.03lf"), m_dPCBVacuumDelay, m_dPCBGripDelay,
		m_dLensGripDelay, m_dLaserDelay, m_dSensorAlignDelay, m_dLaserTimeOut, m_dFinalDelay, m_dBondingDelay);
	WritePrivateProfileString(_T("DelayTime"), _T("Time"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nRunMode);
	WritePrivateProfileString(_T("RUN_MODE"), _T("Mode"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nComplMode);
	WritePrivateProfileString(_T("COMPL_MODE"), _T("Use"), szData, szPath);
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
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nDarkInspUse);
	WritePrivateProfileString(_T("DARK_INSP"), _T("Use"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nCcdDefectInfpUse);
	WritePrivateProfileString(_T("CCD_DEFECT_INSP"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nFpsStopUse);
	WritePrivateProfileString(_T("FPS_STOP"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%.03f"), m_fFpsStopVal);
	WritePrivateProfileString(_T("FPS_STOP"), _T("Value"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nLaserControlLock);
	WritePrivateProfileString(_T("LASER_CONTROL"), _T("Use"), szData, szPath);

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

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nPinStopUse);
	WritePrivateProfileString(_T("SENSOR_COUNT"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nSensorCnt);
	WritePrivateProfileString(_T("SENSOR_COUNT"), _T("Count"), szData, szPath);

	// 조명값
	for (i = 0; i < MAX_LIGHT_COUNT; i++)
	{
		_stprintf_s(szIniIndex, SIZE_OF_100BYTE, _T("%02d"), i + 1);
		_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nLight[i]);
		WritePrivateProfileString(_T("Light"), szIniIndex, szData, szPath);
	}

	// DOME 조명값
	_stprintf_s(szData, SIZE_OF_1K, _T("%d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d / %d"), m_nDomeLightVal[0], m_nDomeLightVal[1], m_nDomeLightVal[2],
		m_nDomeLightVal[3], m_nDomeLightVal[4], m_nDomeLightVal[5], m_nDomeLightVal[6], m_nDomeLightVal[7], m_nDomeLightVal[8], m_nDomeLightVal[9], m_nDomeLightVal[10],
		m_nDomeLightVal[11], m_nDomeLightVal[12], m_nDomeLightVal[13]);
	WritePrivateProfileString(_T("DOME_LIGHT"), _T("Value"), szData, szPath);

	// 보정량 LIMIT
	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf"), m_dOkLimit[i], m_dErrLimit[i]);
		WritePrivateProfileString(_T("AlignLimit"), MOTOR_NAME[i], szData, szPath);
	}

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_clSfrInfo.m_nSizeX);
	WritePrivateProfileString(_T("SFR_SIZE"), _T("SIZE_X"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_clSfrInfo.m_nSizeY);
	WritePrivateProfileString(_T("SFR_SIZE"), _T("SIZE_Y"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nRoiSizeX);
	WritePrivateProfileString(_T("ROI_SIZE"), _T("SIZE_X"), szData, szPath);
	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nRoiSizeY);
	WritePrivateProfileString(_T("ROI_SIZE"), _T("SIZE_Y"), szData, szPath);

	// 검사영역 OFFSET
	for (i = 0; i < (MAX_LAST_INSP_COUNT + MAX_DOME_INSP_ADD); i++)
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

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nMtfOverlayUse);
	WritePrivateProfileString(_T("SfrOverlay"), _T("Use"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf / %.03lf"), m_dStainLsbCenter, m_dStainLsbCorner, m_dStainLsbEdge);
	WritePrivateProfileString(_T("StainLSB"), _T("Threshold"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%.03lf / %.03lf / %.03lf"), m_dStainYMeanCenter, m_dStainYMeanCorner, m_dStainYMeanEdge);
	WritePrivateProfileString(_T("StainYMean"), _T("Threshold"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nMarkNo);
	WritePrivateProfileString(_T("Vision"), _T("MarkNo"), szData, szPath);

	_stprintf_s(szData, SIZE_OF_1K, _T("%d"), m_nMinMatching);
	WritePrivateProfileString(_T("Vision"), _T("Mathcing"), szData, szPath);

	this->CopyBackup(szModelName);
}

void CModelData::SaveTeachData(TCHAR* szModelName)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_1K];
	int nPosi;
	int i, j;

	this->CopyBackup(szModelName);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s\\%s_AA%d.ini"), BASE_MODEL_PATH, szModelName, szModelName, m_nUnit + 1);

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

		WritePrivateProfileString(_T("TEACH"), POS_NAME2[i], szData, szPath);
	}
}
void CModelData::CopyBackup(TCHAR* szModelName)
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

	_stprintf_s(szBackupPath, SIZE_OF_1K, _T("%s\\Backup\\%s\\%04d%02d\\%02d\\%s_%02d_%02d_%02d_%02d_%03d.ini"),
		BASE_DATA_PATH, szModelName, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, szModelName, stSysTime.wDay, stSysTime.wHour,
		stSysTime.wMinute, stSysTime.wSecond, stSysTime.wMilliseconds);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\%s\\%s_AA%d.ini"), BASE_MODEL_PATH, szModelName, szModelName, m_nUnit);

	CopyFile(szPath, szBackupPath, TRUE);

}