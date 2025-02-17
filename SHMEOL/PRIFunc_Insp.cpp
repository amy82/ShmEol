#include <LibACMISCommon\ACMISCommon.h>
#include "StdAfx.h"
#include "PRIFunc_Insp.h"
#include "GlobalDeclare.h"
#include <random>
//#include <ppl.h>
#include <bitset>


//#define R_RESULT_PASS							0	//양품 
//#define R_RESULT_FAIL							1	//불량
//#define R_FAIL_NOISE							2
//#define R_FAIL_BLACK_SPOT						3
//#define R_FAIL_STAIN							4
//#define R_FAIL_INSPECTION						5

using namespace ACMISSoftISP;
typedef struct __TShadingSpec
{
	TRelativeUniformitySpec  m_stRelativeUniformitySpec;
	TColorSensitivitySpecN m_stColorSensitivitySpec;
	TRelativeIlluminationSpecX m_stRelativeIlluminationXSpec;
	TRelativeIlluminationSpecN m_stRelativeIlluminationNSpec;
} TShadingSpec;


CPRIFunc_Insp::CPRIFunc_Insp(void)
{
	mInspRetryCount = 0;
	//cTestPat_Ref_buf = NULL;
	//imagePattern = cvCreateImage(cvSize(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight), IPL_DEPTH_8U, 3);
}


CPRIFunc_Insp::~CPRIFunc_Insp(void)
{
	//cvReleaseImage(&imagePattern);
}
///-------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------
//
bool CPRIFunc_Insp::Func_FinalImageSave(BYTE* RawImage)
{
	int i = 0;
	
	char strTmp[1024];
	TCHAR szLog[SIZE_OF_1K];
	CvPoint pt;
	CvFont cvfont;
	/// Font Face
	int myFontFace = 0;
	int mthickness = 3;
	CvScalar mColor = Scalar(170, 0, 0);
		
	/// Font Scale
	int nWidth = g_clModelData[m_nUnit].m_nWidth;
	int nHeight = g_clModelData[m_nUnit].m_nHeight;
	

	double nModelFontScale = 1.0;
	double nRoiScale = 1.0;
	nModelFontScale = 1.0;
	nRoiScale = 1;


	double nFontSize = 1.1;
	double myFontScale = 1.2 * nModelFontScale;
	cvInitFont(&cvfont, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_NORMAL, nFontSize, nFontSize, 0, 1, 10);

	ACMISSoftISP::xMakeBMP(RawImage, (byte*)g_clLaonGrabberWrapper[m_nUnit].m_pTestBuffer,
	g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight, g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n);

	Mat MatImage = Mat(g_clModelData[m_nUnit].m_nHeight, g_clModelData[m_nUnit].m_nWidth, CV_8UC3);
	MatImage.data = g_clLaonGrabberWrapper[m_nUnit].m_pTestBuffer;
	//memcpy(testImage.data, (char*)g_clLaonGrabberWrapper[m_nUnit].m_pFrameBMPBuffer, g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight * 3);
	
	
	//eol SFR
	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		if (i < 4)
		{
			//0,1,2,3
			pt.x = (int)g_clTaskWork[m_nUnit].m_stSfrInsp._64_Sfr_Rect[0].left - (100 * nRoiScale);
			pt.y = (int)g_clTaskWork[m_nUnit].m_stSfrInsp.clRect[0].top + (280 * nRoiScale) + (60 * i);
		}
		else if (i < 6)
		{
			//4,5
			pt.x = (int)g_clTaskWork[m_nUnit].m_stSfrInsp._64_Sfr_Rect[4].left - (100 * nRoiScale);
			pt.y = (int)g_clTaskWork[m_nUnit].m_stSfrInsp.clRect[1].top + (235 * nRoiScale) +  (60 * (i - 4));
		}
		else if (i < 8)
		{
			//6,7
			pt.x = (int)g_clTaskWork[m_nUnit].m_stSfrInsp._64_Sfr_Rect[6].left - (100 * nRoiScale);
			pt.y = (int)g_clTaskWork[m_nUnit].m_stSfrInsp.clRect[2].top + (235 * nRoiScale) + (60 * (i - 6)); 
		}
		else if (i < 10)
		{
			//8,9
			pt.x = (int)g_clTaskWork[m_nUnit].m_stSfrInsp._64_Sfr_Rect[8].left - (100 * nRoiScale);
			pt.y = (int)g_clTaskWork[m_nUnit].m_stSfrInsp.clRect[3].top - (100 * nRoiScale) + (60 * (i - 8));
		}
		else if (i < 12)
		{
			//4
			pt.x = (int)g_clTaskWork[m_nUnit].m_stSfrInsp._64_Sfr_Rect[10].left - (100 * nRoiScale);
			pt.y = (int)g_clTaskWork[m_nUnit].m_stSfrInsp.clRect[4].top - (100 * nRoiScale) + (60 * (i - 10));
		}
		else if (i < 14)
		{
			//12,13
			pt.x = (int)g_clTaskWork[m_nUnit].m_stSfrInsp._64_Sfr_Rect[12].left - (100 * nRoiScale);
			pt.y = (int)g_clTaskWork[m_nUnit].m_stSfrInsp.clRect[5].top + (270 * nRoiScale) + (60 * (i - 12));
		}
		else if (i < 16)
		{
			//14,15
			pt.x = (int)g_clTaskWork[m_nUnit].m_stSfrInsp._64_Sfr_Rect[14].left - (100 * nRoiScale);
			pt.y = (int)g_clTaskWork[m_nUnit].m_stSfrInsp.clRect[6].top + (270 * nRoiScale) + (60 * (i - 14));
		}
		else if (i < 18)
		{
			//16,17
			pt.x = (int)g_clTaskWork[m_nUnit].m_stSfrInsp._64_Sfr_Rect[16].left - (100 * nRoiScale);
			pt.y = (int)g_clTaskWork[m_nUnit].m_stSfrInsp.clRect[7].top - (170 * nRoiScale) + (60 * (i - 16));
		}
		else
		{
			//18,19
			pt.x = (int)g_clTaskWork[m_nUnit].m_stSfrInsp._64_Sfr_Rect[18].left - (100 * nRoiScale);
			pt.y = (int)g_clTaskWork[m_nUnit].m_stSfrInsp.clRect[8].top - (170 * nRoiScale) + (60 * (i - 18));
		}
		sprintf_s(strTmp, "[%d] %.6lf", i, g_clMesCommunication[m_nUnit].m_dMesUvAfterMTF[i]);
		putText(MatImage, strTmp, pt, myFontFace, myFontScale, mColor, mthickness);


	
		sprintf_s(strTmp, "%d", i);
		pt.x = (int)g_clTaskWork[m_nUnit].m_stSfrInsp._64_Sfr_Rect[i].left;
		pt.y = (int)g_clTaskWork[m_nUnit].m_stSfrInsp._64_Sfr_Rect[i].top + (40);
		putText(MatImage, strTmp, pt, myFontFace, 1.1, Scalar(100, 255, 20), mthickness);	//myFontScale
		rectangle(MatImage, cvPoint((int)g_clTaskWork[m_nUnit].m_stSfrInsp._64_Sfr_Rect[i].left, (int)g_clTaskWork[m_nUnit].m_stSfrInsp._64_Sfr_Rect[i].top),
				cvPoint((int)g_clTaskWork[m_nUnit].m_stSfrInsp._64_Sfr_Rect[i].right, (int)g_clTaskWork[m_nUnit].m_stSfrInsp._64_Sfr_Rect[i].bottom), Scalar(150, 200, 150), 2);
	}
	//oc
	pt.x = (int)nWidth / 2 - (250 * nRoiScale);// 1300;
	pt.y = (int)(300 * nRoiScale);
	sprintf_s(strTmp, "OC X: %.3lf, OC Y: %.3lf", g_clMesCommunication[m_nUnit].m_dMesUVAfterDeltaOC[0], g_clMesCommunication[m_nUnit].m_dMesUVAfterDeltaOC[1]);
	putText(MatImage, strTmp, pt, myFontFace, myFontScale, mColor, mthickness);
	//FOV
	pt.x = (int)nWidth / 2 - (250 * nRoiScale);//(int)1300;
	pt.y = (int)(350 * nRoiScale);
	sprintf_s(strTmp, "TILT X: %.3lf, TILT Y: %.3lf", g_clMesCommunication[m_nUnit].m_dMesTilt[0], g_clMesCommunication[m_nUnit].m_dMesTilt[1]);
	putText(MatImage, strTmp, pt, myFontFace, myFontScale, mColor, mthickness);
	pt.x = (int)nWidth / 2 - (250 * nRoiScale);//(int)1300;
	pt.y = (int)(400 * nRoiScale);
	sprintf_s(strTmp, "ROTATION: %.3lf", g_clMesCommunication[m_nUnit].m_dMesUvAfterRotate);
	putText(MatImage, strTmp, pt, myFontFace, myFontScale, mColor, mthickness);
		


	//===============================================================================================================================
	//jpg Save Path
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szFilePath[SIZE_OF_1K];
	SYSTEMTIME stSysTime;
	CFileFind clFinder;
	CString sFileMode = _T("");
	CFile clFile;
	FILE* fp;
	int nStepNo;
	::GetLocalTime(&stSysTime);

	if (_tcslen(g_clTaskWork[m_nUnit].m_szLotID) <= 0)
		_tcscpy_s(g_clTaskWork[m_nUnit].m_szLotID, SIZE_OF_100BYTE, _T("(NULL)"));

	if (_tcslen(g_clTaskWork[m_nUnit].m_szChipID) <= 0)
		_tcscpy_s(g_clTaskWork[m_nUnit].m_szChipID, SIZE_OF_100BYTE, _T("(NULL)"));

	if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
		CreateDirectory(BASE_LOG_PATH, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE"), BASE_LOG_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE\\%04d%02d"), BASE_LOG_PATH,  stSysTime.wYear, stSysTime.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE\\%04d%02d\\%02d"), BASE_LOG_PATH,  stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE\\%04d%02d\\%02d\\%s"), BASE_LOG_PATH,  stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, g_clTaskWork[m_nUnit].m_szChipID);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);


	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%s_%d_ChartImage%02d%02d%02d.jpg"), szPath, g_clTaskWork[m_nUnit].m_szChipID, g_clSysData.m_nUnitNo, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);

	imwrite(szFilePath, MatImage);

	return true;
}
int CPRIFunc_Insp::func_ModelLotCheck(TCHAR *BcrLot)
{
	int leng = _tcslen(BcrLot);
	if (leng < 9)
	{
		return -1;
	}
#if (____MACHINE_NAME == MODEL_FRONT_100)
	const TCHAR compareStr[] = _T("002");
#else
	const TCHAR compareStr[] = _T("001");
#endif
	int nRtn = 0;
	nRtn = _tcsncmp(&BcrLot[6], compareStr, 3);		//0이면 일치
	
	return nRtn;

}
bool CPRIFunc_Insp::PPL_Func_Chart_Insp(BYTE* RawImage, bool bAutoMode)	//EOL 화상 검사
{
	TCHAR szLog[SIZE_OF_1K];
	bool TotalRtn = true;
	//
	// -SFR 
	

	return TotalRtn;
}
bool CPRIFunc_Insp::PPL_Func_OC_Insp(BYTE* RawImage, bool bAutoMode)
{
	TCHAR szLog[SIZE_OF_1K];
	bool TotalRtn = true;
	//Stain
	//Blemish 검사
	if (g_clModelData[m_nUnit].m_nStainInspUse == 0)
	{
		g_clMandoInspLog[m_nUnit].m_LogBlemishBlackSpot = 0;
		g_clMandoInspLog[m_nUnit].m_LogBlemishLcb = 0;
		g_clMandoInspLog[m_nUnit].m_LogBlemishRU_Ymean = 0;
		g_clMandoInspLog[m_nUnit].m_LogBlemishFPF = 0;
		
		g_clMesCommunication[m_nUnit].m_nMesBlemish[0] = 0;
		g_clMesCommunication[m_nUnit].m_nMesBlemish[1] = 0;
		g_clMesCommunication[m_nUnit].m_nMesBlemish[2] = 0;
		g_clMesCommunication[m_nUnit].m_nMesBlemishResult[0] = 1;
		g_clMesCommunication[m_nUnit].m_nMesBlemishResult[1] = 1;
		g_clMesCommunication[m_nUnit].m_nMesBlemishResult[2] = 1;
		////
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] Blemish 검사 PASS"));
		AddLog(szLog, 0, m_nUnit);
	}
	else
	{
		 g_clPriInsp[m_nUnit].func_Insp_Stain(RawImage, true);
	}
	

	return TotalRtn;
}
///-------------------------------------------------------------------------------------
bool CPRIFunc_Insp::func_EEprom_CheckSum_Check(bool bAutoMode)
{
#if 0
	unsigned char szTemp[MAX_PATH];
	char szData[MAX_PATH];
	unsigned int nAddress;
	unsigned int checkSumTemp = 0;
	int endCheckSum = 0;
	int totlaCount = 0;
	int leng = 0;
	int i = 0;
	int j = 0;
	bool rtn = false;
	bool bCheckSumrtn = true;
	byte ReadChecksumData[2];
	byte TotalReadData[200];
	memset(TotalReadData, 0x00, sizeof(TotalReadData));

	SYSTEMTIME eTime;
	::GetLocalTime(&eTime);
	// 
	for (i = 0; i < 4; i++)
	{
		g_clMesCommunication[m_nUnit].m_dMesEEPROMResult[i] = 1;
	}
	CString _RtnData = _T("");
	TCHAR szLog[SIZE_OF_1K];

	int startAddress = 32;
	int endAddress = 115; 		//checksum Address 114랑 115 는 checksum

	unsigned short mslaveAddr = 0x52;	//Sensor PCB Slave Address

	eepromData[m_nUnit].EEPROM_TotalRead_Type(mslaveAddr, startAddress, endAddress, TotalReadData, 1);//최대 32씩만 32 ~ 113까지 + 체크섬 2바이트

	ReadChecksumData[0] = TotalReadData[82];	//Checksum(2byte)
	ReadChecksumData[1] = TotalReadData[83];


	endCheckSum = 82;//  // 32~113 총 82개 읽어야됨 

	unsigned short crcAfter = 0;

	crcAfter = CRC_CalculateCRC16_CCIT(TotalReadData, endCheckSum);

	CString ReadCheckSum;
	CString CalCheckSum;
	ReadCheckSum.Format("%02X%02X", ReadChecksumData[1], ReadChecksumData[0]);		//1,0순서가 맞음 little endian으로 저장돼서
	CalCheckSum.Format("%04X", crcAfter);
	rtn = eepromData[m_nUnit].CompareHexData(ReadCheckSum, CalCheckSum, ASCII_MODE);
	if (rtn == true)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]CheckSum OK : %s/%s"), ReadCheckSum, CalCheckSum);
		AddLog(szLog, 0, m_nUnit);
	}
	else
	{
		g_clMesCommunication[m_nUnit].m_dMesEEPROMResult[0] = 0;
		bCheckSumrtn = false;
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]CheckSum NG : %s/%s"), ReadCheckSum, CalCheckSum);
		AddLog(szLog, 0, m_nUnit);
	}
	//고정값 비교 3가지
	/*
	[EEPROM] Signature Code	Variable	Variable	고정값 검사 필요 (5041, 2bytes)
	[EEPROM] Parameter Version	Variable	Variable	고정값 검사 필요 (02 00 00 00 00 00 00 00, 8bytes)(0200000000000000, 8bytes)
	[EEPROM] Calibration Model	Variable	Variable	고정값 검사 필요 (00 00 00 00, 4bytes)(00000000, 4bytes)

	*/
	byte SignatureData[2] = { 0x50 , 0x41 };
	int SignatureStartAddress = 0;
	//[EEPROM] Signature Code[0x50(P) , 0x41(A)] = 2byte
	for (i = 0; i < 2; i++)
	{
		if (TotalReadData[i + SignatureStartAddress] != SignatureData[i])
		{
			g_clMesCommunication[m_nUnit].m_dMesEEPROMResult[1] = 0;
			bCheckSumrtn = false;
			_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Signature Code NG %d/%d"), TotalReadData[i], SignatureData[i]);
			AddLog(szLog, 0, m_nUnit);
		}
	}
	//[EEPROM] Parameter Version
	byte ParameterVersionData[8] = { 0x02 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 };
	int ParameterVersionStartAddress = 2;
	for (i = 0; i < 8; i++)
	{
		if (TotalReadData[i + ParameterVersionStartAddress] != ParameterVersionData[i])
		{
			g_clMesCommunication[m_nUnit].m_dMesEEPROMResult[2] = 0;
			bCheckSumrtn = false;
			_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Parameter Version NG %d/%d"), TotalReadData[i + 2], ParameterVersionData[i]);
			AddLog(szLog, 0, m_nUnit);
		}
	}
	//[EEPROM] Calibration Model
	byte CalibrationModelData[4] = { 0x00 , 0x00 , 0x00 , 0x00 };
	int CalibrationModelStartAddress = 10;
	for (i = 0; i < 4; i++)
	{
		if (TotalReadData[i + CalibrationModelStartAddress] != CalibrationModelData[i])
		{
			g_clMesCommunication[m_nUnit].m_dMesEEPROMResult[3] = 0;
			bCheckSumrtn = false;
			_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Calibration Model NG %d/%d"), TotalReadData[i + 10], CalibrationModelData[i]);
			AddLog(szLog, 0, m_nUnit);
		}
	}
	//Data Read
	//여기서 읽은걸 실수로 변경

	int address = 0;

	address = 32;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 2, HEX_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Signature Code Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szSignaturecode, SIZE_OF_100BYTE, _T("%s"), _RtnData);			//2byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Signature Code:%s"), g_clMesCommunication[m_nUnit].m_szSignaturecode);
	AddLog(szLog, 0, m_nUnit);
	//
	address = 34;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 8, HEX_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Parameter Version Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szParameterVersion, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//8byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM] Parameter Version:%s"), g_clMesCommunication[m_nUnit].m_szParameterVersion);
	AddLog(szLog, 0, m_nUnit);
	//
	address = 42;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 4, HEX_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Calibration Model Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szCalibrationModel, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//4byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Calibration Model:%s"), g_clMesCommunication[m_nUnit].m_szCalibrationModel);
	AddLog(szLog, 0, m_nUnit);
	//
	address = 46;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 4, HEX_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Focal Length (fx) Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szFocalLengthFx, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//4byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Focal Length (fx):%s"), g_clMesCommunication[m_nUnit].m_szFocalLengthFx);
	AddLog(szLog, 0, m_nUnit);
	//
	address = 50;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 4, HEX_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Focal Length (fy) Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szFocalLengthFy, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//4byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Focal Length (fy):%s"), g_clMesCommunication[m_nUnit].m_szFocalLengthFx);
	AddLog(szLog, 0, m_nUnit);
	//
	address = 54;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 4, HEX_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Principal Point (cx) Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szPrincipalPointCx, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//4byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Principal Point (cx):%s"), g_clMesCommunication[m_nUnit].m_szPrincipalPointCx);
	AddLog(szLog, 0, m_nUnit);
	//
	address = 58;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 4, HEX_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Principal Point (cy) Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szPrincipalPointCy, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//4byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Principal Point (cy):%s"), g_clMesCommunication[m_nUnit].m_szPrincipalPointCy);
	AddLog(szLog, 0, m_nUnit);
	//
	address = 62;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 4, HEX_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Radial Distortion (k1) Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szRadialDistortionK1, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//4byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Radial Distortion (k1):%s"), g_clMesCommunication[m_nUnit].m_szRadialDistortionK1);
	AddLog(szLog, 0, m_nUnit);
	//
	address = 66;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 4, HEX_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Radial Distortion (k2) Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szRadialDistortionK2, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//4byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Radial Distortion (k2):%s"), g_clMesCommunication[m_nUnit].m_szRadialDistortionK2);
	AddLog(szLog, 0, m_nUnit);
	//
	address = 70;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 4, HEX_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Radial Distortion (k3) Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szRadialDistortionK3, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//4byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Radial Distortion (k3):%s"), g_clMesCommunication[m_nUnit].m_szRadialDistortionK3);
	AddLog(szLog, 0, m_nUnit);
	//
	address = 98;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 4, HEX_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Tangential Distortion (P1) Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szTangentialDistortionP1, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//4byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Tangential Distortion (P1):%s"), g_clMesCommunication[m_nUnit].m_szTangentialDistortionP1);
	AddLog(szLog, 0, m_nUnit);
	//
	address = 102;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 4, HEX_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Tangential Distortion (P2) Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szTangentialDistortionP2, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//4byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Tangential Distortion (P2):%s"), g_clMesCommunication[m_nUnit].m_szTangentialDistortionP2);
	AddLog(szLog, 0, m_nUnit);
	//
	address = 114;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 2, HEX_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Checksum Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szCheckSum, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//2byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Checksum:%s"), g_clMesCommunication[m_nUnit].m_szCheckSum);
	AddLog(szLog, 0, m_nUnit);
	//
	address = 116;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 11, ASCII_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Production date Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szProductiondate, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//11byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Production date:%s"), g_clMesCommunication[m_nUnit].m_szProductiondate);
	AddLog(szLog, 0, m_nUnit);
	//
	address = 127;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 4, HEX_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]RMS Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szRMS, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//4byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]RMS:%s"), g_clMesCommunication[m_nUnit].m_szRMS);
	AddLog(szLog, 0, m_nUnit);
	//
	address = 131;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 4, HEX_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]FOV Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szFOV, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//4byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]FOV:%s"), g_clMesCommunication[m_nUnit].m_szFOV);
	AddLog(szLog, 0, m_nUnit);
	//
	address = 135;
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 4, HEX_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Calibration Temperature Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szCalibrationTemperature, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//4byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Calibration Temperature:%s"), g_clMesCommunication[m_nUnit].m_szCalibrationTemperature);
	AddLog(szLog, 0, m_nUnit);

	//추가된값 2개 210819
	address = 139;  //16byte
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 16, ASCII_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]PCBA Part Number Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szPartNumberVersion, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//16byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]PCBA Part Number and Version :%s"), g_clMesCommunication[m_nUnit].m_szPartNumberVersion);
	AddLog(szLog, 0, m_nUnit);

	address = 155;	//13byte
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 13, ASCII_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Imager ES Version Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szImagerESVersionInfo, SIZE_OF_100BYTE, _T("%s"), _RtnData);		//13byte
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Imager ES Version Information :%s"), g_clMesCommunication[m_nUnit].m_szImagerESVersionInfo);
	AddLog(szLog, 0, m_nUnit);


	Sleep(5);
	//==============================================================================================================================================
	//
	//
	//power pcb read 값 3개 210819
	mslaveAddr = 0x50;		//Power PCB Slave Address


	address = 32;	//16byte
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 16, ASCII_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]PPCBA Part Number Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szPowerPcbPartNumberVersion, SIZE_OF_100BYTE, _T("%s"), _RtnData);
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM Power]PPCBA Part Number and Version :%s"), g_clMesCommunication[m_nUnit].m_szPowerPcbPartNumberVersion);
	AddLog(szLog, 0, m_nUnit);

	address = 48;	//13byte
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 13, ASCII_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Motional Part Number Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szPowerPcbMotionalPartNumber, SIZE_OF_100BYTE, _T("%s"), _RtnData);
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM Power]Motional Part Number :%s"), g_clMesCommunication[m_nUnit].m_szPowerPcbMotionalPartNumber);
	AddLog(szLog, 0, m_nUnit);

	address = 48;	//11byte
	_RtnData = eepromData[m_nUnit].EEPROM_Read(mslaveAddr, address, 11, ASCII_MODE, true);
	if (_RtnData == "FALSE")
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]Production date Read Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(g_clMesCommunication[m_nUnit].m_szPowerProductiondata, SIZE_OF_100BYTE, _T("%s"), _RtnData);
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM Power]Production date :%s"), g_clMesCommunication[m_nUnit].m_szPowerProductiondata);
	AddLog(szLog, 0, m_nUnit);


	//====================================================================================================================================================
	//실수 변환

	g_clMesCommunication[m_nUnit].m_dMesFocalLengthFx = CovertToFloat(g_clMesCommunication[m_nUnit].m_szFocalLengthFx, FLOAT_MODE);
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]FocalLengthFx:%lf"), g_clMesCommunication[m_nUnit].m_dMesFocalLengthFx);
	AddLog(szLog, 0, m_nUnit);
	g_clMesCommunication[m_nUnit].m_dMesFocalLengthFy = CovertToFloat(g_clMesCommunication[m_nUnit].m_szFocalLengthFy, FLOAT_MODE);
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]FocalLengthFy:%lf"), g_clMesCommunication[m_nUnit].m_dMesFocalLengthFy);
	AddLog(szLog, 0, m_nUnit);

	g_clMesCommunication[m_nUnit].m_dMesPrincipalPointCx = CovertToFloat(g_clMesCommunication[m_nUnit].m_szPrincipalPointCx, FLOAT_MODE);
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]PrincipalPointCx:%lf"), g_clMesCommunication[m_nUnit].m_dMesPrincipalPointCx);
	AddLog(szLog, 0, m_nUnit);
	g_clMesCommunication[m_nUnit].m_dMesPrincipalPointCy = CovertToFloat(g_clMesCommunication[m_nUnit].m_szPrincipalPointCy, FLOAT_MODE);
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]PrincipalPointCy:%lf"), g_clMesCommunication[m_nUnit].m_dMesPrincipalPointCy);
	AddLog(szLog, 0, m_nUnit);


	g_clMesCommunication[m_nUnit].m_dMesRadialDistortionK1 = CovertToFloat(g_clMesCommunication[m_nUnit].m_szRadialDistortionK1, FLOAT_MODE);
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]RadialDistortionK1:%lf"), g_clMesCommunication[m_nUnit].m_dMesRadialDistortionK1);
	AddLog(szLog, 0, m_nUnit);
	g_clMesCommunication[m_nUnit].m_dMesRadialDistortionK2 = CovertToFloat(g_clMesCommunication[m_nUnit].m_szRadialDistortionK2, FLOAT_MODE);
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]RadialDistortionK2:%lf"), g_clMesCommunication[m_nUnit].m_dMesRadialDistortionK2);
	AddLog(szLog, 0, m_nUnit);
	g_clMesCommunication[m_nUnit].m_dMesRadialDistortionK3 = CovertToFloat(g_clMesCommunication[m_nUnit].m_szRadialDistortionK3, FLOAT_MODE);
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]RadialDistortionK3:%lf"), g_clMesCommunication[m_nUnit].m_dMesRadialDistortionK3);
	AddLog(szLog, 0, m_nUnit);


	g_clMesCommunication[m_nUnit].m_dMesTangentialDistortionP1 = CovertToFloat(g_clMesCommunication[m_nUnit].m_szTangentialDistortionP1, FLOAT_MODE);
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]TangentialDistortionP1:%lf"), g_clMesCommunication[m_nUnit].m_dMesTangentialDistortionP1);
	AddLog(szLog, 0, m_nUnit);
	g_clMesCommunication[m_nUnit].m_dMesTangentialDistortionP2 = CovertToFloat(g_clMesCommunication[m_nUnit].m_szTangentialDistortionP2, FLOAT_MODE);
	_stprintf_s(szLog, SIZE_OF_1K, _T("EEPROM]TangentialDistortionP2:%lf"), g_clMesCommunication[m_nUnit].m_dMesTangentialDistortionP2);
	AddLog(szLog, 0, m_nUnit);

	_RtnData.Empty();
	/////delete[] TotalReadData;		//new 선언했을때 사용
	return bCheckSumrtn;
#endif
	return false;
}

int CPRIFunc_Insp::func_EEprom_Parse(TCHAR *ptszLot)
{
	int nRtn = 0;
	//_stprintf_s(g_clTaskWork[m_nUnit].m_szChipID, SIZE_OF_100BYTE, _T("00000000000000000000000PT00463985-A23040A000000000001"));	//총길이 33 + "-" +19  = 53
	int _leng = _tcslen(g_clTaskWork[m_nUnit].m_szChipID);
	if (_leng < 53)
	{
		return -1;	//문자 길이 오류

	}
	int findPos = 0;
	CString mLotTemp;
	mLotTemp.Format(_T("%s"), g_clTaskWork[m_nUnit].m_szChipID);
	findPos = mLotTemp.Find(_T("-"));	//33


	//CString temp = mLotTemp.Mid(findPos);	// = "-"
	CString FirstLot = mLotTemp.Left(findPos + 2);		//00000000000000000000000PT00463985-A
	_stprintf_s(g_clTaskWork[m_nUnit].m_szRivianPartNumber, SIZE_OF_100BYTE, _T("%s"), (TCHAR*)(LPCTSTR)FirstLot);
	_leng = _tcslen(g_clTaskWork[m_nUnit].m_szRivianPartNumber);
	if (_leng < 35) 
	{
		return -2;	//문자 길이 오류

	}
	CString LastLot = mLotTemp.Mid(findPos + 2);		//23040A000000000001
	findPos = LastLot.Find(_T("A"));		//Location Index

	//
	
	//Traceability Code - Date
	_stprintf_s(g_clTaskWork[m_nUnit].m_szTraceabilityDate, SIZE_OF_100BYTE, _T("%s"), (TCHAR*)(LPCTSTR)LastLot.Left(5));		//왼쪽 시작부터 몇개
	//Traceability Code - Location
	_stprintf_s(g_clTaskWork[m_nUnit].m_szTraceabilityLocation, SIZE_OF_100BYTE, _T("%s"), (TCHAR*)(LPCTSTR)LastLot.Mid(5,1));
	//Traceability Code - Tool Number
	_stprintf_s(g_clTaskWork[m_nUnit].m_szTraceabilityToolNumber, SIZE_OF_100BYTE, _T("%s"), (TCHAR*)(LPCTSTR)LastLot.Mid(6,6));
	//Traceability Code - Serial Numer
	_stprintf_s(g_clTaskWork[m_nUnit].m_szTraceabilitySerialNumber, SIZE_OF_100BYTE, _T("%s"), (TCHAR*)(LPCTSTR)LastLot.Right(6));	//오른쪽 끝에서 부터 몇개

	LastLot.Replace(_T("0A"), _T(""));
	_stprintf_s(g_clTaskWork[m_nUnit].m_szManufacturerSerialNumber, SIZE_OF_100BYTE, _T("%s"), (TCHAR*)(LPCTSTR)LastLot);
	_leng = _tcslen(g_clTaskWork[m_nUnit].m_szManufacturerSerialNumber);	//16개
	if (_leng < 16)
	{
		return -3;	//문자 길이 오류

	}
	mLotTemp.Empty();
	FirstLot.Empty();
	LastLot.Empty();
	return nRtn;
}

bool CPRIFunc_Insp::func_EEprom_Write(bool bAutoMode)
{

	return false;
}

///-------------------------------------------------------------------------------------
//
///-------------------------------------------------------------------------------------
bool CPRIFunc_Insp::func_EEprom_FuseID(bool bAutoMode)
{
	/*CString sLog = _T("");
	CString strData = _T("");
	CString _addr = _T("");
	CString wData = _T("");
	unsigned char szTemp[MAX_PATH];
	char szData[MAX_PATH];
	unsigned int nAddress;
	double dData = 0.0;
	int totlaCount = 0;
	int errorCode = 0;
	int wLength = 0;
	int leng = 0;
	int i = 0;
	int j = 0;
	int k = 0;

	byte rtnHexData[MAX_PATH];
	byte *totalData = new byte[2000];
	memset(rtnHexData, 0x00, sizeof(rtnHexData));

	memset(totalData, 0x00, sizeof(byte) * 2000);
	CTime cTime = CTime::GetCurrentTime();*/

	int writingByteNum;

	if (!g_clLaonGrabberWrapper[m_nUnit].m_pBoard->SetWPDisable())
	{
		AddLog(_T("[eeprom] Write Disable fail!!!!!"), 1, m_nUnit);
		return false;
	}
	else {
		AddLog(_T("[eeprom] Write Disable Success"), 1, m_nUnit);
	}

	CString m_strSlaveAddr, m_strAddr;
	CString m_strRegData;
	unsigned int nSlaveAddress;
	unsigned int nAddress;
	unsigned char pData[1025];
	int errorCode = 0;
	byte m_cAddrLength;
	DWORD m_cRegDataLength;

	nSlaveAddress = 0X10;
	nAddress = 0X301A;
	m_cAddrLength = 2;
	m_cRegDataLength = 2;

	sscanf_s(m_strSlaveAddr.GetBuffer(0), "%x", &nSlaveAddress);
	sscanf_s(m_strAddr.GetBuffer(0), "%x", &nAddress);

	errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)nSlaveAddress, (unsigned short)nAddress, m_cAddrLength, pData, (unsigned short)m_cRegDataLength);

	if (errorCode)
	{
		m_strRegData.Format("READ Error : %d", errorCode);
		m_strRegData.AppendFormat(" %s", g_clLaonGrabberWrapper[m_nUnit].GetErrorStr(errorCode));
		return false;
	}
	else
	{
		m_strRegData = "";
		for (int i = 0; i < (int)m_cRegDataLength; i++)
		{
			m_strRegData.AppendFormat("%02X ", pData[i]);
		}
	}

	if (m_strRegData == "0x10DC")
	{
		errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)nSlaveAddress, (unsigned short)nAddress, m_cAddrLength, pData, (unsigned short)m_cRegDataLength);

		if (errorCode)
		{
			m_strRegData.Format("0x10FC WRITE Error : %d", errorCode);
			m_strRegData.AppendFormat(" %s", g_clLaonGrabberWrapper[m_nUnit].GetErrorStr(errorCode));
			return false;
		}
		else
		{
		}

	}


	return true;

}

///-------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------
//
///-------------------------------------------------------------------------------------
bool CPRIFunc_Insp::FnShmFastCornerFind(BYTE* ChartRawImage, bool bAutoMode)
{
	int i = 0;
	int j = 0;
	TCHAR szLog[SIZE_OF_1K];
	TCHAR szPos[SIZE_OF_100BYTE];
	TCHAR szFilePath[SIZE_OF_1K];

	

	TDATASPEC tspec;
	tspec.eOutMode = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eOutMode;
	tspec.eDataFormat = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDataFormat;
	tspec.eSensorType = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eSensorType;
	tspec.eDemosaicMethod = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod;

	BYTE* m_pBMPTempBuffer;

	m_pBMPTempBuffer = new BYTE[g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameBMPSize()];
	memset(m_pBMPTempBuffer, 0, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameBMPSize());

	ACMISSoftISP::xMakeBMP(ChartRawImage, (byte*)m_pBMPTempBuffer, g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight, tspec);

	Mat OrgImage(Size(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight), CV_8UC3);
	std::memcpy(OrgImage.data, (char*)m_pBMPTempBuffer, g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight * 3);

	//MbufGet(vision.MilGrabImageChild[3], OrgImage.data);//MbufGet(vision.MilGrabImageChild[1], OrgImage.data);
	if (bAutoMode == false)
	{
		imwrite("d:\\OrgImage.jpg", OrgImage);
	}
	if (m_pBMPTempBuffer)
	{
		delete m_pBMPTempBuffer;
	}
	m_pBMPTempBuffer = NULL;

	int thresh_value = 50;// 70;  //기존 12.28 = 70
	int max_value = 255;
	//
	int mRoiX = 0;
	int mRoiY = 0;

	int dDrawTextX = 0;
	int dDrawTextY = 0;

	int mRoiWidth = g_clModelData[m_nUnit].m_nWidth - mRoiX;
	int mRoiHeight = g_clModelData[m_nUnit].m_nHeight - mRoiY;
	
	int offsetX = ((g_clModelData[m_nUnit].m_nWidth/2) - (g_clTaskWork[m_nUnit].m_clPtCircle[0].x + g_clTaskWork[m_nUnit].m_clPtCircle[1].x + g_clTaskWork[m_nUnit].m_clPtCircle[2].x + g_clTaskWork[m_nUnit].m_clPtCircle[3].x) / 4) * -1;
	int offsetY = ((g_clModelData[m_nUnit].m_nHeight / 2) - (g_clTaskWork[m_nUnit].m_clPtCircle[0].y + g_clTaskWork[m_nUnit].m_clPtCircle[1].y + g_clTaskWork[m_nUnit].m_clPtCircle[2].y + g_clTaskWork[m_nUnit].m_clPtCircle[3].y) / 4) * -1;

	// Shi-Tomasi 코너 검출 파라미터 설정
#if (____MACHINE_NAME == MODEL_FRONT_100)
	//100도는 8개 전부 원형 마크
	//new 16개 꼭짓점
	FOV_AREA_CHECK nFovMode[MAX_FOV_FIND_COUNT] = {
		LT_FOV_PIONT, RT_FOV_PIONT,
		LT_FOV_PIONT, BR_FOV_PIONT,
		LT_FOV_PIONT, BR_FOV_PIONT,
		BL_FOV_PIONT, RT_FOV_PIONT,
		LT_FOV_PIONT, RT_FOV_PIONT,BL_FOV_PIONT, BR_FOV_PIONT,
		BR_FOV_PIONT, BL_FOV_PIONT,RT_FOV_PIONT, LT_FOV_PIONT,
	};
	int maxCorners = 6;					//검출할 코너의 최대 개수입니다.
#else
	//150도는 2개 원형 , 6개 꼭짓점
	//new 14개 꼭짓점
	FOV_AREA_CHECK nFovMode[MAX_FOV_FIND_COUNT] = {
		BL_FOV_PIONT, RT_FOV_PIONT,
		LT_FOV_PIONT, BR_FOV_PIONT,
		LT_FOV_PIONT, BR_FOV_PIONT,
		BL_FOV_PIONT, RT_FOV_PIONT,
		BL_FOV_PIONT, BR_FOV_PIONT,LT_FOV_PIONT, RT_FOV_PIONT,
		LT_FOV_PIONT, BR_FOV_PIONT };// , LT_FOV_PIONT, BR_FOV_PIONT
	int maxCorners = 4;					//검출할 코너의 최대 개수입니다.
#endif
	
	int nIndex = 0;
	Mat grayImg;
	CPoint m_clPtFov[MAX_FOV_COUNT];



	double qualityLevel = 0.05;//0.05;			//코너 품질을 평가하는 값입니다. 일반적으로 0과 1 사이의 값을 사용
	double minDistance = 50;//80;			//검출된 코너들 사이의 최소 거리입니다. 
	int blockSize = 3;					//코너 검출을 위한 블록의 크기입니다. 
	bool useHarrisDetector = false;		//true로 설정하면 Harris 코너 검출기를 사용하고, false로 설정하면 Shi-Tomasi 검출기를 사용합니다.
	double kvalue = 0.04;				//useHarrisDetector가 true일 때만 사용,일반적으로 0.04에서 0.06 사이의 값을 사용

	




	for (int k = 0; k < MAX_FOV_COUNT; k++)
	{
		mRoiX = g_clModelData[m_nUnit].m_clSfrInfo.m_clPtFovOffset[k].x + offsetX;
		mRoiY = g_clModelData[m_nUnit].m_clSfrInfo.m_clPtFovOffset[k].y + offsetY;
		if (mRoiX < 0) mRoiX = 0;
		if (mRoiY < 0) mRoiY = 0;

		mRoiWidth = (int)(g_clModelData[m_nUnit].m_clSfrInfo.m_nFovSizeX[k]);
		mRoiHeight = (int)(g_clModelData[m_nUnit].m_clSfrInfo.m_nFovSizeY[k]);

		if ((mRoiX + mRoiWidth) >= g_clModelData[m_nUnit].m_nWidth)
		{
			mRoiWidth = g_clModelData[m_nUnit].m_nWidth - mRoiX - 1;
		}

		if ((mRoiY + mRoiHeight) >= g_clModelData[m_nUnit].m_nHeight)
		{
			mRoiHeight = g_clModelData[m_nUnit].m_nHeight - mRoiY - 1;
		}
		if (mRoiWidth < 0) mRoiWidth = 1;
		if (mRoiHeight < 0) mRoiHeight = 1;
		

		Mat roiimg = OrgImage(cvRect(mRoiX, mRoiY, mRoiWidth, mRoiHeight));
		cv::cvtColor(roiimg, grayImg, cv::COLOR_BGR2GRAY);
		

		// 코너 찾기 특징점 벡터
		vector<Point2f> corners;
		Mat img_corners;		//코너 찾기

		//원찾기
		std::vector<cv::Vec3f> circles;

		
		cvtColor(grayImg, img_corners, COLOR_GRAY2BGR);
		
		{
			// Shi-Tomasi 코너 검출
			goodFeaturesToTrack(grayImg, corners, maxCorners, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, kvalue);
			if (corners.empty())
			{
				return false;
			}
			int msize = corners.size();
			if (msize < 1) msize = 1;
			CPoint m_clPtCornerTemp[MAX_FOV_FIND_COUNT];
			//sort(corners.begin(), corners.end(), [](const Point2f& p1, const Point2f& p2) {
				//return p1.x < p2.x;
			//});

			Point2f topLeft = corners[0];		// TL 꼭짓점 찾기
			Point2f bottomLeft = corners[0];	// BR 꼭짓점 찾기
			Point2f topRight = corners[0];		// TR 꼭짓점 찾기
			Point2f bottomRight = corners[0];	// BR 꼭짓점 찾기

			int nCornerSize = corners.size();
			for (i = 0; i < nCornerSize; i++)
			{
				if (corners[i].x + corners[i].y < topLeft.x + topLeft.y)
				{
					topLeft = corners[i];
				}
				if (corners[i].x - corners[i].y > topRight.x - topRight.y)
				{
					topRight = corners[i];
				}
				if (corners[i].x + corners[i].y > bottomRight.x + bottomRight.y) 
				{
					bottomRight = corners[i];
				}
				if (corners[i].x - corners[i].y < bottomLeft.x - bottomLeft.y) 
				{
					bottomLeft = corners[i];
				}
				circle(img_corners, corners[i], 5, Scalar(0, 255, 0), 2, 8, 0);
				if (i < MAX_FOV_FIND_COUNT)
				{
					m_clPtCornerTemp[i].x = corners[i].x;
					m_clPtCornerTemp[i].y = corners[i].y;
				}

				g_clMandoInspLog[m_nUnit].m_ChartVertex[k].Pos[i].x = corners[i].x + mRoiX;
				g_clMandoInspLog[m_nUnit].m_ChartVertex[k].Pos[i].y = corners[i].y + mRoiY;

				/*_stprintf_s(szLog, SIZE_OF_1K, _T("[Fov Corner #%d] x:%d, y:%d"), k,
					g_clMandoInspLog[m_nUnit].m_ChartVertex[k].Pos[i].x, g_clMandoInspLog[m_nUnit].m_ChartVertex[k].Pos[i].y);

				AddLog(szLog, 0, m_nUnit);*/
			}

			m_clPtFov[LT_FOV_PIONT].x = topLeft.x + mRoiX;
			m_clPtFov[LT_FOV_PIONT].y = topLeft.y + mRoiY;

			m_clPtFov[RT_FOV_PIONT].x = topRight.x + mRoiX;
			m_clPtFov[RT_FOV_PIONT].y = topRight.y + mRoiY;

			m_clPtFov[BL_FOV_PIONT].x = bottomLeft.x + mRoiX;
			m_clPtFov[BL_FOV_PIONT].y = bottomLeft.y + mRoiY;

			m_clPtFov[BR_FOV_PIONT].x = bottomRight.x + mRoiX;
			m_clPtFov[BR_FOV_PIONT].y = bottomRight.y + mRoiY;


			dDrawTextX = 10;
			if (m_clPtFov[nFovMode[nIndex]].x > (g_clModelData[m_nUnit].m_nWidth / 2))
			{
				dDrawTextX = -50;

			}
			if (k < 4)
			{
				//여기는 2개씩
				g_clMandoInspLog[m_nUnit].m_ShmFovPoint[nIndex].x = m_clPtFov[nFovMode[nIndex]].x;
				g_clMandoInspLog[m_nUnit].m_ShmFovPoint[nIndex].y = m_clPtFov[nFovMode[nIndex]].y;
				g_clVision.DrawMOverlayCross(m_nUnit, m_nUnit, m_clPtFov[nFovMode[nIndex]], 20, M_COLOR_CYAN, 2);// TRUE); 
				_stprintf_s(szPos, SIZE_OF_100BYTE, _T("H-%d"), nIndex);
				_stprintf_s(szLog, SIZE_OF_1K, _T("[Fov %s] x:%d, y:%d"), szPos, g_clMandoInspLog[m_nUnit].m_ShmFovPoint[nIndex].x, g_clMandoInspLog[m_nUnit].m_ShmFovPoint[nIndex].y);

				AddLog(szLog, 0, m_nUnit);
				g_clVision.DrawMOverlayText(m_nUnit, m_clPtFov[nFovMode[nIndex]].x + dDrawTextX, m_clPtFov[nFovMode[nIndex]].y - 40, szPos, M_COLOR_GREEN, _T("Arial"), 13, 17);
				nIndex++;
				g_clMandoInspLog[m_nUnit].m_ShmFovPoint[nIndex].x = m_clPtFov[nFovMode[nIndex]].x;
				g_clMandoInspLog[m_nUnit].m_ShmFovPoint[nIndex].y = m_clPtFov[nFovMode[nIndex]].y;
				g_clVision.DrawMOverlayCross(m_nUnit, m_nUnit, m_clPtFov[nFovMode[nIndex]], 20, M_COLOR_CYAN, 2);// TRUE); 
				_stprintf_s(szPos, SIZE_OF_100BYTE, _T("H-%d"), nIndex);
				_stprintf_s(szLog, SIZE_OF_1K, _T("[Fov %s] x:%d, y:%d"), szPos, g_clMandoInspLog[m_nUnit].m_ShmFovPoint[nIndex].x, g_clMandoInspLog[m_nUnit].m_ShmFovPoint[nIndex].y);

				AddLog(szLog, 0, m_nUnit);
				g_clVision.DrawMOverlayText(m_nUnit, m_clPtFov[nFovMode[nIndex]].x + dDrawTextX, m_clPtFov[nFovMode[nIndex]].y - 40, szPos, M_COLOR_GREEN, _T("Arial"), 13, 17);
				nIndex++;
			}
			else
			{
				 
				//K = 4,5,6,7
				//8,9,10,11
				g_clMandoInspLog[m_nUnit].m_ShmFovPoint[nIndex].x = m_clPtFov[nFovMode[nIndex]].x;
				g_clMandoInspLog[m_nUnit].m_ShmFovPoint[nIndex].y = m_clPtFov[nFovMode[nIndex]].y;
				g_clVision.DrawMOverlayCross(m_nUnit, m_nUnit, m_clPtFov[nFovMode[nIndex]], 20, M_COLOR_CYAN, 2);// TRUE); 
				_stprintf_s(szPos, SIZE_OF_100BYTE, _T("V-%d"), nIndex - 8);

				_stprintf_s(szLog, SIZE_OF_1K, _T("[Fov %s] x:%d, y:%d"), szPos, g_clMandoInspLog[m_nUnit].m_ShmFovPoint[nIndex].x, g_clMandoInspLog[m_nUnit].m_ShmFovPoint[nIndex].y);

				AddLog(szLog, 0, m_nUnit);
				g_clVision.DrawMOverlayText(m_nUnit, m_clPtFov[nFovMode[nIndex]].x + dDrawTextX, m_clPtFov[nFovMode[nIndex]].y - 40, szPos, M_COLOR_GREEN, _T("Arial"), 13, 17);
				nIndex++;
			}


		}

#if 0		//원 찾을 때만
		if (nFovMode[k] == CIRCLE_FOV_PIONT)	//k < 4)
		{
			// Hough Circle Transform 적용
			int mdp = 1;						//dp=1이면 입력 이미지와 동일한 해상도를 사용
			int mMinDist = grayImg.rows/2;		// / 8;//검출된 원의 중심들 사이의 최소 거리입니다
			int mParam1 = 100;// 200;			//캐니 에지 탐지기에 전달되는 상위 임계값입니다. 
			int mParam2 = 10;					//중심 검출을 위한 누산기의 임계값입니다. 이 값이 작을수록 더 많은 원이 검출되며, 노이즈나 잘못된 원도 포함될 수 있습니다.
			int mMinRadius = 10;					//검출할 원의 최소 반지름입니다. 
			int mMaxRadius = 35;					//검출할 원의 최대 반지름입니다.   사각형이 잡혀서 max 사이즈 중요함
			cv::HoughCircles(grayImg, circles, cv::HOUGH_GRADIENT, mdp, mMinDist, mParam1, mParam2, mMinRadius, mMaxRadius);
			if (circles.empty() )
			{ 
				return false;
			}
			cv::Point center(cvRound(circles[0][0]), cvRound(circles[0][1]));
			int radius = cvRound(circles[0][2]);
			g_clMandoInspLog[m_nUnit].m_ChartVertex[k].Pos[0].x = circles[0][0] + mRoiX;
			g_clMandoInspLog[m_nUnit].m_ChartVertex[k].Pos[0].y = circles[0][1] + mRoiY;

			_stprintf_s(szLog, SIZE_OF_1K, _T("[Fov Circle #%d] x:%d, y:%d"), k,
				g_clMandoInspLog[m_nUnit].m_ChartVertex[k].Pos[0].x, g_clMandoInspLog[m_nUnit].m_ChartVertex[k].Pos[0].y);
			AddLog(szLog, 0, m_nUnit);

			circle(img_corners, center, 3, Scalar(0, 255, 0), -1, 8, 0);


			m_clPtFov[k].x = circles[0][0] + mRoiX;
			m_clPtFov[k].y = circles[0][1] + mRoiY;
		}

		else
#endif
		
		
		


		
		//여기서 여러개중에 하나 고르면 될듯 
		//
		if (bAutoMode == false)
		{


			_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\fovroi%d.jpg"), BASE_LOG_PATH,  k + 1);
			imwrite(szFilePath, img_corners);

			//namedWindow("Shi-Tomasi Corners", WINDOW_NORMAL);// WINDOW_AUTOSIZE);
			//imshow("Shi-Tomasi Corners", img_corners);

			//waitKey(0);
		}
	}
	if (bAutoMode == false)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] FOV IMAGE SAVE :%s"), BASE_LOG_PATH);
		AddLog(szLog, 0, m_nUnit);
	}

	g_clVision.DrawOverlayAll(m_nUnit);

	return true;
}


///-------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------
//
///-------------------------------------------------------------------------------------
bool CPRIFunc_Insp::FnShmCornerFind(BYTE* ChartRawImage, bool bAutoMode)
{
	int i = 0;
	int j = 0;
	TCHAR szLog[SIZE_OF_1K];
	TCHAR szFilePath[SIZE_OF_1K];


	TDATASPEC tspec;
	tspec.eOutMode = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eOutMode;
	tspec.eDataFormat = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDataFormat;
	tspec.eSensorType = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eSensorType;
	tspec.eDemosaicMethod = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod;

	BYTE* m_pBMPTempBuffer;

	m_pBMPTempBuffer = new BYTE[g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameBMPSize()];
	memset(m_pBMPTempBuffer, 0, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameBMPSize());

	ACMISSoftISP::xMakeBMP(ChartRawImage, (byte*)m_pBMPTempBuffer, g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight, tspec);

	Mat OrgImage(Size(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight), CV_8UC3);
	std::memcpy(OrgImage.data, (char*)m_pBMPTempBuffer, g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight * 3);

	//MbufGet(vision.MilGrabImageChild[3], OrgImage.data);//MbufGet(vision.MilGrabImageChild[1], OrgImage.data);
	if (bAutoMode == false)
	{
		imwrite("d:\\OrgImage.jpg", OrgImage);
	}
	if (m_pBMPTempBuffer)
	{
		delete m_pBMPTempBuffer;
	}
	m_pBMPTempBuffer = NULL;

	int thresh_value = 50;// 70;  //기존 12.28 = 70
	int max_value = 255;
	//
	int mRoiX = 0;
	int mRoiY = 0;

	int mRoiWidth = g_clModelData[m_nUnit].m_nWidth - mRoiX;
	int mRoiHeight = g_clModelData[m_nUnit].m_nHeight - mRoiY;

	int k = 0;
	int thresh = 245;
	for (k = 0; k < MAX_FOV_COUNT; k++)
	{
		mRoiX = g_clModelData[m_nUnit].m_clSfrInfo.m_clPtFovOffset[k].x;
		mRoiY = g_clModelData[m_nUnit].m_clSfrInfo.m_clPtFovOffset[k].y;

		mRoiWidth = (int)(g_clModelData[m_nUnit].m_clSfrInfo.m_nFovSizeX[k]);
		mRoiHeight = (int)(g_clModelData[m_nUnit].m_clSfrInfo.m_nFovSizeY[k]);

		Mat im = OrgImage(cvRect(mRoiX, mRoiY, mRoiWidth, mRoiHeight));
		//Mat im = OrgImage(cvRect(0, 0, g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight));
		//Mat GaussianImage = Mat::zeros(im.rows, im.cols, CV_8UC3);//CV_8UC1);
		//GaussianBlur(im, GaussianImage, Size(7, 7), 1);

		cv::Mat grayImage;
		cv::cvtColor(im, grayImage, cv::COLOR_BGR2GRAY);

		namedWindow("grayImage", WINDOW_NORMAL);
		imshow("grayImage", grayImage);
		waitKey(0);
		Mat harris = Mat::zeros(grayImage.size(), CV_32FC1);//CV_8UC1);

		Mat binaryImage = Mat::zeros(grayImage.rows, grayImage.cols, CV_8UC1);
		//threshold(GaussianImage, binaryImage, thresh_value, max_value, THRESH_BINARY);// THRESH_BINARY); THRESH_BINARY_INV
		threshold(grayImage, binaryImage, thresh_value, max_value, THRESH_BINARY);

		namedWindow("binaryImage", WINDOW_NORMAL);
		imshow("binaryImage", binaryImage);
		waitKey(0);
		//cornerHarris(grayimg, harris, 3, 3, 0.84);
		// Harris Corner
		// cornerHarris(입력 이미지(Grayscale), 출력 이미지, 인접 픽셀 크기(Blocksize), Sobel ksize, Harris parameter, 픽셀 보간법)
		cornerHarris(binaryImage, harris, 2, 5, 0.05, BORDER_DEFAULT);	//2,5,0.05
		//harris = cv::dilate(harris, None);
		cv:dilate(harris, harris, cv::Mat(), cv::Point(-1, -1), 1);  
		//cv:erode(harris, harris, cv::Mat(), cv::Point(-1, -1), 1);


		//namedWindow("harris", WINDOW_NORMAL);
		//imshow("harris", harris);
		waitKey(0);
		Mat harris_norm;
		//normalize(harris, harris_norm, 0, 255, NORM_MINMAX, CV_8U);
		// 정규화(Normalizing)
		// normalize(입력 이미지, 출력 이미지, normalize range(low), normalize range(high), 픽셀 보간법) 
		normalize(harris, harris_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
		Mat cs_abs;
		//convertScaleAbs(harris_norm, cs_abs);
		// 미분한 결과에 절대값을 적용하여 8bit의 unsigned int형으로 바꾸어 표현
		convertScaleAbs(harris_norm, cs_abs);
		// Drawing a circle around corners

		for (int j = 0; j < harris_norm.rows; j += 1)
		{
			for (int i = 0; i < harris_norm.cols; i += 1)
			{
				if ((int)harris_norm.at<float>(j, i) >= thresh) 
				{
					circle(cs_abs, Point(i, j), 7, Scalar(255, 255, 255), 1, 8, 0);

					_stprintf_s(szLog, SIZE_OF_1K, _T("[Corner] x:%d, y:%d"), i + mRoiX, j + mRoiY);
					AddLog(szLog, 0, m_nUnit);
				}
			}
		}
		namedWindow("cs_absImage", WINDOW_NORMAL);
		imshow("cs_absImage", cs_abs);
		waitKey(0);

		break;
	}

	if (bAutoMode == false)
	{
		_stprintf_s(szFilePath, SIZE_OF_1K, _T("d:\\fovResult.jpg"));
		imwrite(szFilePath, OrgImage);
	}

	return false;
}
///-------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------
//
///-------------------------------------------------------------------------------------
bool CPRIFunc_Insp::FnShmEdgeFind(BYTE* ChartRawImage, bool bAutoMode)
{
	int i = 0;
	int j = 0;
	TCHAR szLog[SIZE_OF_1K];
	TCHAR szFilePath[SIZE_OF_1K];


	TDATASPEC tspec;
	tspec.eOutMode = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eOutMode;
	tspec.eDataFormat = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDataFormat;
	tspec.eSensorType = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eSensorType;
	tspec.eDemosaicMethod = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod;

	BYTE* m_pBMPTempBuffer;

	m_pBMPTempBuffer = new BYTE[g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameBMPSize()];
	memset(m_pBMPTempBuffer, 0, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameBMPSize());

	ACMISSoftISP::xMakeBMP(ChartRawImage, (byte*)m_pBMPTempBuffer, g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight, tspec);

	Mat OrgImage(Size(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight), CV_8UC3);
	std::memcpy(OrgImage.data, (char*)m_pBMPTempBuffer, g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight * 3);

	//MbufGet(vision.MilGrabImageChild[3], OrgImage.data);//MbufGet(vision.MilGrabImageChild[1], OrgImage.data);
	if (bAutoMode == false)
	{
		imwrite("d:\\OrgImage.jpg", OrgImage);
	}
	if (m_pBMPTempBuffer)
		delete m_pBMPTempBuffer;
	m_pBMPTempBuffer = NULL;

	//double centX = Task.d_mark_pos_x[PCB_Holder_MARK][1];
	//double centY = Task.d_mark_pos_y[PCB_Holder_MARK][1];
	int mRoiX = 0;
	int mRoiY = 0;

	int mRoiWidth = g_clModelData[m_nUnit].m_nWidth - mRoiX;
	int mRoiHeight = g_clModelData[m_nUnit].m_nHeight - mRoiY;

	int pimplescount = 0;
	int mParam1 = 10;	//높은 threshold , 
	int mPrarm2 = 10;	//threshold 값이 가장 큰 원부터 반환 
	int mMinRadius = 200;
	int mMaxRadius = 400;
	int StatinCount = 0;
	int nFindCount = 0;
	int thresh_value = 77;// 70;  //기존 12.28 = 70
	int max_value = 255;
	Point topStart(0, 0);
	Point topEnd(mRoiWidth, 0);
	Scalar white = Scalar(255);
	char strTmp[1024];
	double area = 0.0;
	int mcount = 0;
	int crosssize = 4;
	int cx = 0;
	int cy = 0;
	int minSize = 200;
	int maxSize = 650;
	int xLimit = 0;
	int yLimit = 0;
	int boundWidMax = 300;
	int linewidth = 1;


	size_t mcircleSize = 0;
	// 스크래치 영역 표시
	Scalar color(0, 0, 0); // 초록색
	cv::Point mPoint[10];
	bool bCenterCheck = false;
	int myFontFace = 0;
	double myFontScale = 1.1;
	int mthickness = 3;
	CvScalar mColor = Scalar(150, 200, 150);
	CvScalar mCircleColor;
	int colordiff = 2;


	

	int k = 0;
	for (k = 0; k < MAX_FOV_COUNT; k++)
	{
		mRoiX = g_clModelData[m_nUnit].m_clSfrInfo.m_clPtFovOffset[k].x;
		mRoiY = g_clModelData[m_nUnit].m_clSfrInfo.m_clPtFovOffset[k].y;

		mRoiWidth = (int)(g_clModelData[m_nUnit].m_clSfrInfo.m_nFovSizeX[k]);
		mRoiHeight = (int)( g_clModelData[m_nUnit].m_clSfrInfo.m_nFovSizeY[k]);

		Mat im = OrgImage(cvRect(mRoiX, mRoiY, mRoiWidth, mRoiHeight));
		Mat GaussianImage = Mat::zeros(im.rows, im.cols, CV_8UC3);//CV_8UC1);
		GaussianBlur(im, GaussianImage, Size(7, 7), 1);
		if (bAutoMode == false)
		{
			_stprintf_s(szFilePath, SIZE_OF_1K, _T("d:\\fovroi%d.jpg"), k+1);
			imwrite(szFilePath, GaussianImage);
		}
		// 그레이스케일로 변환
		cv::Mat grayImage;
		cv::cvtColor(GaussianImage, grayImage, cv::COLOR_BGR2GRAY);
		std::vector<cv::Vec3f> circles;
		Mat binaryImage = Mat::zeros(grayImage.rows, grayImage.cols, CV_8UC1);
		//threshold(GaussianImage, binaryImage, thresh_value, max_value, THRESH_BINARY);// THRESH_BINARY); THRESH_BINARY_INV
		threshold(grayImage, binaryImage, thresh_value, max_value, THRESH_BINARY);
		//thresh_value 값보다 크면 max_value 값으로 바꾼다.

		if (bAutoMode == false)
		{
			imwrite("d:\\binaryImage.jpg", binaryImage);
		}



		std::vector<std::vector<Point>> contours;	//RETR_LIST, RETR_EXTERNAL
		vector<Point> approx;
		cv::findContours(binaryImage, contours, RETR_TREE, CHAIN_APPROX_NONE);		//RETR_CCOMP, RETR_LIST
		//CHAIN_APPROX_NONE , CHAIN_APPROX_SIMPLE

		for (size_t i = 0; i < contours.size(); i++)
		{
			if (!contours[i].empty())
			{
				area = contourArea(contours[i]);
				//if (area > 0.0 && area < 10000.0)//if (area > 특정_면적_임계값) 
				mcircleSize = contours[i].size();
				Rect boundingRectData = boundingRect(contours[i]);

				Moments mmt = moments(contours[i]);
				double cx = mmt.m10 / mmt.m00 + g_clModelData[m_nUnit].m_clSfrInfo.m_clPtFovOffset[k].x;
				double cy = mmt.m01 / mmt.m00 + g_clModelData[m_nUnit].m_clSfrInfo.m_clPtFovOffset[k].y;



				contours[i].clear();
				boundingRectData.x = boundingRectData.x + g_clModelData[m_nUnit].m_clSfrInfo.m_clPtFovOffset[k].x;
				boundingRectData.y = boundingRectData.y + g_clModelData[m_nUnit].m_clSfrInfo.m_clPtFovOffset[k].y;
				
				rectangle(OrgImage, boundingRectData, Scalar(0, 0, 255), 3, 8, 0);

				int nIndex = 0;
				sprintf_s(strTmp, "[%d]", k+1);
				cv::putText(OrgImage, strTmp, Point(cx - 40, cy + 15), myFontFace, myFontScale, mColor, mthickness);

				
			}

		}
	}



	
//#if (____MACHINE_NAME == MODEL_FRONT_100)
//	minSize = 50;
//	maxSize = 1000;
//	xLimit = 0;
//	yLimit = 0;
//	boundWidMax = 300;
//
//	//top
//	topStart.x = 0;
//	topStart.y = 0;
//	topEnd.x = mRoiWidth;
//	topEnd.y = 0;
//	line(binaryImage, topStart, topEnd, white, linewidth);
//	//bottom
//	topStart.x = 0;
//	topStart.y = mRoiHeight - linewidth;
//	topEnd.x = mRoiWidth;
//	topEnd.y = mRoiHeight - linewidth;
//	line(binaryImage, topStart, topEnd, white, linewidth);
//	//left
//	topStart.x = 0;
//	topStart.y = 0;
//	topEnd.x = 0;
//	topEnd.y = mRoiHeight;
//	line(binaryImage, topStart, topEnd, white, linewidth);
//	//right
//	topStart.x = mRoiWidth - 1;
//	topStart.y = 0;
//	topEnd.x = mRoiWidth - 1;
//	topEnd.y = mRoiHeight;
//	line(binaryImage, topStart, topEnd, white, linewidth);
//#else
//	minSize = 200;
//	maxSize = 650;
//	xLimit = 0;
//	yLimit = 0;
//	boundWidMax = 300;
//
//
//	//LT
//	topStart.x = 200;
//	topStart.y = 200;//190;
//	topEnd.x = 400;
//	topEnd.y = 190;
//	line(binaryImage, topStart, topEnd, white, linewidth);
//
//	//RT
//	topStart.x = 1550;
//	topStart.y = 200;
//	topEnd.x = 1750;
//	topEnd.y = 200;
//	line(binaryImage, topStart, topEnd, white, linewidth);
//	//BL
//	topStart.x = 200;
//	topStart.y = 880;//884;
//	topEnd.x = 400;
//	topEnd.y = 880;//884;
//	line(binaryImage, topStart, topEnd, white, linewidth);
//	//BR
//	topStart.x = 1550;
//	topStart.y = 890;
//	topEnd.x = 1750;
//	topEnd.y = 890;
//	line(binaryImage, topStart, topEnd, white, linewidth);
//#endif


	
#if 1
	//size_t mcircleSize = 0;
	//// 스크래치 영역 표시
	//Scalar color(0, 0, 0); // 초록색
	//cv::Point mPoint[10];
	//bool bCenterCheck = false;
	//int myFontFace = 0;
	//double myFontScale = 1.1;
	//int mthickness = 3;
	//CvScalar mColor = Scalar(150, 200, 150);
	//CvScalar mCircleColor;
	//int colordiff = 2;

	//

	//std::vector<std::vector<Point>> contours;	//RETR_LIST, RETR_EXTERNAL
	//vector<Point> approx;
	//cv::findContours(binaryImage, contours, RETR_LIST, CHAIN_APPROX_NONE);

	//for (size_t i = 0; i < contours.size(); i++)
	//{
	//	if (!contours[i].empty())
	//	{
	//		area = contourArea(contours[i]);
	//		//if (area > 0.0 && area < 10000.0)//if (area > 특정_면적_임계값) 
	//		mcircleSize = contours[i].size();
	//		Rect boundingRectData = boundingRect(contours[i]);

	//		contours[i].clear();
	//	}

	//}
	return true;

#else
	//
	//
	//
	//
	//
	//
	// 윤곽 찾기
	std::vector<std::vector<Point>> contours;	//RETR_LIST, RETR_EXTERNAL
	vector<Point> approx;
	//findContours(binaryImage, contours, RETR_LIST, CHAIN_APPROX_NONE);//CHAIN_APPROX_SIMPLE, CHAIN_APPROX_NONE
	findContours(binaryImage, contours, RETR_LIST, CHAIN_APPROX_NONE);// CHAIN_APPROX_NONE); 


	size_t mcircleSize = 0;
	// 스크래치 영역 표시
	Scalar color(0, 0, 0); // 초록색
	cv::Point mPoint[10];
	bool bCenterCheck = false;
	int myFontFace = 0;
	double myFontScale = 1.1;
	int mthickness = 3;
	CvScalar mColor = Scalar(150, 200, 150);
	CvScalar mCircleColor;
	int colordiff = 2;
	for (size_t i = 0; i < contours.size(); i++)
	{
		if (!contours[i].empty())
		{
			area = contourArea(contours[i]);
			//if (area > 0.0 && area < 10000.0)//if (area > 특정_면적_임계값) 
			mcircleSize = contours[i].size();
			Rect boundingRectData = boundingRect(contours[i]);

			if (mcircleSize > minSize && mcircleSize < maxSize && boundingRectData.width < boundWidMax)//300)//mcircleSize > minSize && mcircleSize < maxSize)
			{

				Moments mmt = moments(contours[i]);
				double cx = mmt.m10 / mmt.m00;
				double cy = mmt.m01 / mmt.m00;


				int nIndex = 0;// sfrBoundCheck(cx, cy);
				//nIndex > 0  && 
				if (nIndex > 0 && cy > yLimit && cx > xLimit && cx < g_clModelData[m_nUnit].m_nWidth - xLimit&& cy < g_clModelData[m_nUnit].m_nHeight - yLimit)		//좌측 빛샘 때문에 100 추가
				{
					//drawContours(OrgImage, contours, static_cast<int>(i), color, 3);

					rectangle(OrgImage, boundingRectData, Scalar(0, 0, 255), 3, 8, 0);
					//line(OrgImage, Point(cx - crosssize, cy - crosssize), Point(cx + crosssize, cy + crosssize), Scalar::all(255), 2, 8, 0);
					//line(OrgImage, Point(cx + crosssize, cy - crosssize), Point(cx - crosssize, cy + crosssize), Scalar::all(255), 2, 8, 0);
					sprintf_s(strTmp, "[%d]", nIndex);
					putText(OrgImage, strTmp, Point(cx - 40, cy + 15), myFontFace, myFontScale, mColor, mthickness);

					_stprintf_s(szLog, SIZE_OF_1K, _T("[Box #%d]Center:%.3lf, %.3lf / Size:%zu"), nIndex, cx, cy, mcircleSize);
					AddLog(szLog, 0, m_nUnit);
					mcount++;


					approxPolyDP(contours[i], approx, arcLength(contours[i], true) * 0.02, true);
					//sfrPosCheck(approx);

					//std::sort(approx.begin(), approx.end(), [](const Point& a, const Point& b) {
					//return a.x < b.x;
					//});

					std::sort(approx.begin(), approx.end(), [](const Point& a, const Point& b)
					{
						if (a.x != b.x) {
							return a.x < b.x;  // y 좌표를 기준으로 정렬
						}
						return a.y < b.y;  // y 좌표가 동일한 경우 x 좌표를 기준으로 정렬
					});

					for (j = 0; j < approx.size(); ++j)
					{
						mPoint[j].x = approx.at(j).x;
						mPoint[j].y = approx.at(j).y;
					}
					//int Centerx = approx.at(0).x + (approx.at(3).x - approx.at(0).x);
					cv::Point tempPoint;
					if (approx.size() > 3)
					{
						if (mPoint[0].y > mPoint[1].y)
						{
							tempPoint = mPoint[0];
							mPoint[0] = mPoint[1];
							mPoint[1] = tempPoint;
						}
						if (mPoint[2].y > mPoint[3].y)
						{
							tempPoint = mPoint[2];
							mPoint[2] = mPoint[3];
							mPoint[3] = tempPoint;
						}
					}



				}





			}
			contours[i].clear();
		}

	}
	nFindCount = mcount;
	_stprintf_s(szLog, SIZE_OF_1K, _T("[Circle]Find Count : %d"), nFindCount);// contours[i][0].x, contours[i][0].y);
	AddLog(szLog, 0, m_nUnit);

	return false;
#endif
}


bool CPRIFunc_Insp::func_Insp_Illumination(BYTE * img, bool bAutoMode, bool bUse8BitOnly)
{
	//TRelativeIlluminationSpecX& _Spec,
	bool bRes = true;
	int i = 0;
	int nResult = R_RESULT_PASS;
	char strTmp[1024];
	CString szLog;
	//TCHAR szLog[SIZE_OF_1K];
	int nWidth = g_clModelData[m_nUnit].m_nWidth;  //gMIUDevice.nWidth;
	int nHeight = g_clModelData[m_nUnit].m_nHeight;  //gMIUDevice.nHeight;
	TDATASPEC& tDataSpec = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n;  
	//gMIUDevice.dTDATASPEC_n;
	//TRelativeIlluminationSpecX& _Spec,

	// Image information
	//RawImgInfo stImgInfo;
	// Spec information
	TShadingSpec tShadingSpec;

	//std::cout << std::endl;
	//std::cout << __FUNCTION__ << std::endl;

	//GetImageData(MODEL_NIO, tDataSpec, stImgInfo);

	// Image buffers
	std::vector<BYTE> vFrameBuffer(nWidth * nHeight * 2);

	memset(&tShadingSpec, 0x00, sizeof(TShadingSpec));


	//----------------------------------------------------------------------
	// Spec - Relative Illumination
	//----------------------------------------------------------------------

	// Initialize ROI regions and offset values
	std::vector<TROISPoint> vROI_field(100);//기존 모두 5
	std::vector<double> vOffset(100);
	std::vector<double> vCH0_thd(100);
	std::vector<double> vCH1_thd(100);
	std::vector<double> vCH2_thd(100);
	std::vector<double> vCH3_thd(100);

	//vector <CBlobRect> *m_vecBlob;	
	//g_clModelData[m_nUnit].m_RISpec[_x][_y] 11,9
	// Center
	int specCount = 0;
	int _xIndex = 0;
	int _x = 0;
	int _y = 0;

	for (_y = 0; _y < 100; _y++)
	{
		vROI_field[_y].ptStart.x = g_clModelData[m_nUnit].m_RirOI[_y][0] * 2;// 0
		vROI_field[_y].ptStart.y = g_clModelData[m_nUnit].m_RirOI[_y][1] * 2;//1
		vROI_field[_y].nROIWidth = g_clModelData[m_nUnit].m_RirOI[_y][2];//2
		vROI_field[_y].nROIHeight = g_clModelData[m_nUnit].m_RirOI[_y][3];//3

		vCH0_thd[_y] = g_clModelData[m_nUnit].m_RirOI[_y][4];//4
		vCH1_thd[_y] = g_clModelData[m_nUnit].m_RirOI[_y][5];//5
		vCH2_thd[_y] = g_clModelData[m_nUnit].m_RirOI[_y][6];//6
		vCH3_thd[_y] = g_clModelData[m_nUnit].m_RirOI[_y][7];//7

		vOffset[_y] = g_clModelData[m_nUnit].m_RirOI[_y][8];//8
	}
	//----------------------------------------------------------------------
	// Spec - Relative Illumination X
	//----------------------------------------------------------------------
	tShadingSpec.m_stRelativeIlluminationXSpec.nSpecPixelCntInBlock = g_clModelData[m_nUnit].m_RISpec[0];// 8;
	tShadingSpec.m_stRelativeIlluminationXSpec.nEnableChannel = g_clModelData[m_nUnit].m_RISpec[1];// 8;
	tShadingSpec.m_stRelativeIlluminationXSpec.dSpecCenterIntensity[0] = g_clModelData[m_nUnit].m_RISpec[2];//200;
	tShadingSpec.m_stRelativeIlluminationXSpec.dSpecCenterIntensity[1] = g_clModelData[m_nUnit].m_RISpec[3];//200;
	tShadingSpec.m_stRelativeIlluminationXSpec.dSpecCenterIntensity[2] = g_clModelData[m_nUnit].m_RISpec[4];//200;
	tShadingSpec.m_stRelativeIlluminationXSpec.dSpecCenterIntensity[3] = g_clModelData[m_nUnit].m_RISpec[5];//200;

	tShadingSpec.m_stRelativeIlluminationXSpec.tROI.eROIType = ROIType_SPOINT;// ROIType_FIELD;
	tShadingSpec.m_stRelativeIlluminationXSpec.tROI.ROICount = 100;
	tShadingSpec.m_stRelativeIlluminationXSpec.tROI.dOffset = vOffset.data();
	tShadingSpec.m_stRelativeIlluminationXSpec.tROI.pROIData = vROI_field.data();
	tShadingSpec.m_stRelativeIlluminationXSpec.dSpecCH0Threshold = vCH0_thd.data();
	tShadingSpec.m_stRelativeIlluminationXSpec.dSpecCH1Threshold = vCH1_thd.data();
	tShadingSpec.m_stRelativeIlluminationXSpec.dSpecCH2Threshold = vCH2_thd.data();
	tShadingSpec.m_stRelativeIlluminationXSpec.dSpecCH3Threshold = vCH3_thd.data();

	bool bRaw = true;
	bool bEnableRelativeIllumination = true;
	bool bEnableRelativeIlluminationX = true;
	bool bEnableRelativeUniformity = true;
	bool bEnableColorSensitivity = true;
	bool bSaveResultImage = false;
	//----------------------------------------------------------------------
	// Inspect Main Camera
	//----------------------------------------------------------------------

	int nResultRI = -1, nResultRU = -1, nResultCS = -1, nResultRI_X;
	char title[100];

	// Image buffers
	std::vector<BYTE> vBmpBuffer(nWidth * nHeight * 3, 0);

	// output image
	IplImage *cvImgShading = cvCreateImage(cvSize(nWidth, nHeight), 8, 3);
	cvImgShading->imageData = (char*)vBmpBuffer.data();

	// for display
	if (bRaw)
	{
		ACMISSoftISP::xMakeBMP(img, vBmpBuffer.data(), nWidth, nHeight, tDataSpec);
	}
	else
	{
		//std::copy(img, img + sizeof(BYTE) * nWidth * nHeight * 3, vBmpBuffer.data());
	}


	if (bEnableRelativeIlluminationX)
	{
		nResultRI_X = Inspect_RelativeIlluminationX(img, nWidth, nHeight, tShadingSpec.m_stRelativeIlluminationXSpec, tDataSpec, cvImgShading, bUse8BitOnly);
		//std::cout << "nResult Relative Illumination X =" << nResultRI_X << std::endl;
		// _stprintf_s(szLog, SIZE_OF_1K, _T("	nResult Relative Illumination X = %d"), nResultRI_X);
		szLog.Format("	nResult Relative Illumination X = %d", nResultRI_X);
		AddLog(szLog, 0, m_nUnit, false);
		//theApp.MainDlg->putListLog(szLog);
	}


	/*if (ImagePath != nullptr && bSaveResultImage == true)
	{
	char filename[100];
	char *tmp = (char *)strrchr(ImagePath, '.');

	if (tmp != nullptr)
	{
	strncpy_s(filename, ImagePath, (int)(tmp - ImagePath));
	}
	else
	{
	strcpy_s(filename, ImagePath);
	}
	strcat_s(filename, "_Shading_result.bmp");
	printf("Saving Result image: %s\n", filename);
	cvSaveImage(filename, cvImgShading);
	}
	*/
	//sprintf(title, "Shading%s%s", ImagePath != nullptr ? " - " : "", ImagePath != nullptr ? ImagePath : "");
	sprintf(title, "RI");
	if (bAutoMode == false)
	{
		cvShowImage(title, cvImgShading);
		cvWaitKey(0);
	}

	cvReleaseImage(&cvImgShading);

	return bRes;
}



///-------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------
//
///-------------------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_Shm_Fov_Distortion(BYTE* img, bool bAutoMode)
{

	TCHAR szLog[SIZE_OF_1K];
	int i = 0;
	int nPitch = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_PITCH, M_NULL);
	int nSizeX = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_SIZE_X, M_NULL);
	int nSizeY = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_SIZE_Y, M_NULL);

	//g_CalcImageAlign(m_nUnit);

	int nWidth = g_clModelData[m_nUnit].m_nWidth;
	int nHeight = g_clModelData[m_nUnit].m_nHeight;

	std::shared_ptr<CACMISFiducialMark> m_pChartProc = std::make_shared<CACMISFiducialMark>();

	_stprintf_s(szLog, SIZE_OF_1K, _T("[FOV]CACMISFiducialMark Version: %s"), m_pChartProc->GetVersion());
	AddLog(szLog, 0, m_nUnit);


	TFiducialMarkInfoN spec;
	spec.nFiducialMarkType = FIDUCIALMARKTYPE_SHM_CORNER;
	spec.nInspectItem = FIDUCIALMARK_INSPECT_FOV;
	spec.nAlgorithmIndex = FOV_METHOD_SHM_CORNER;

#if 1
#if (____MACHINE_NAME == MODEL_OHC100)
	spec.vParam = { 50.46, 61.65, 91.42, 108.61, 99.66, 55.69, 114.81 };		//100
#else
	spec.vParam = { 82.83, 84.4, 118.11, 112.58, 133.8, 83.8, 145.7 };		//150
#endif

	spec.dRealGapX = 0.0;
	spec.dRealGapY = 0.0;
	//spec.dRealSubGapX = 0.0;
	//spec.dRealSubGapY = 0.0;
	//spec.dDistanceXFromCenter = 0.0;
	//spec.dDistanceYFromCenter = 0.0;
	spec.dModuleChartDistance = 0.0;
	spec.dPixelSize = 3.0;

#if (____MACHINE_NAME == MODEL_OHC100)
	spec.dEFL = 8400.0;		//100
#else
	spec.dEFL = 19800.0;		//150
#endif
	spec.dRadius = 0.7;
	spec.dBinaryThreshold = 70.0;
	spec.dMaxDeviation = 50.0;
	spec.nROIBoxSize = 10;
	spec.nMaxROIBoxSize = 100;

	g_pCarAABonderDlg->m_clLogThread.CreateLogFolder("14");

	std::vector<POINT> vMark(MAX_FOV_FIND_COUNT);


#if (____MACHINE_NAME == MODEL_OHC100)

	int forIndex[MAX_FOV_FIND_COUNT] = { 1,2,5,6,0,3,4,7,8,9,10,11,12,13,14,15 };
#else
	int forIndex[MAX_FOV_FIND_COUNT] = { 1,2,5,6,0,3,4,7,12,13,8,9,10,11 };
#endif

	int cnt = 0;
	for (i = 0; i < MAX_FOV_FIND_COUNT; i++)
	{
		cnt = forIndex[i];

		vMark[i].x = g_clMandoInspLog[m_nUnit].m_ShmFovPoint[cnt].x;
		vMark[i].y = g_clMandoInspLog[m_nUnit].m_ShmFovPoint[cnt].y;
	}
#else
	spec.vParam = { 82.83, 84.4, 118.11, 122.58, 133.8, 83.8, 145.7 };
	spec.dRealGapX = 0.0;
	spec.dRealGapY = 0.0;
	spec.dRealSubGapX = 0.0;
	spec.dRealSubGapY = 0.0;
	spec.dDistanceXFromCenter = 0.0;
	spec.dDistanceYFromCenter = 0.0;
	spec.dModuleChartDistance = 0.0;
	spec.dPixelSize = 0.0;
	spec.dEFL = 0.0;
	spec.dRadius = 0.7;
	spec.dBinaryThreshold = 70.0;
	spec.dMaxDeviation = 50.0;
	spec.nROIBoxSize = 10;
	spec.nMaxROIBoxSize = 100;
	std::vector<POINT> vMark = {

		{ 546, 217 },

		{ 1378, 212 },

		{ 548,871 },

		{ 1381,868 },

		{ 484,300 },

		{ 1441,295 },

		{ 486,789 },

		{ 1442,786 },

		{ 156,496 },

		{ 1768,586 },

		{ 175,203 },

		{ 1746,202 },

		{ 179,884 },

		{ 1748,872 }

	};
#endif

	m_pChartProc->SetFiducialMarkSpec(spec, vMark, nWidth, nHeight);
	m_pChartProc->CalcDFOV();

	////m_pChartProc->CalcDistortion();
	////m_pChartProc->CalcTiltAndRotation();


	bool bFovRtn = true;
	
	g_clMesCommunication[m_nUnit].m_dMesFov[0] = m_pChartProc->GetHFOV();
	g_clMesCommunication[m_nUnit].m_dMesFov[1] = m_pChartProc->GetVFOV();


	double mFovValue = 0.0;
	double mFovMin = 0.1;
	double mFovMax = 10.0;

	mFovValue = g_clMesCommunication[m_nUnit].m_dMesFov[0];
	mFovMin = (_ttof(EEpromVerifyData.vMinData[18]));
	mFovMax = (_ttof(EEpromVerifyData.vMaxData[18]));


	if (mFovValue < mFovMin || mFovValue > mFovMax)
	{
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;	//HFOV
		g_clMesCommunication[m_nUnit].m_dMesFovResult[0] = 0;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[Fov] HFov Spec Out: %.6lf [%.3lf~%.3lf]"), mFovValue, mFovMin, mFovMax);
		AddLog(szLog, 0, m_nUnit);
		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [HFov NG]");
		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG HFov :%.3lf [%.3lf~%.3lf]"), mFovValue, mFovMin, mFovMax);
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}

		g_clMandoInspLog[m_nUnit].m_bInspRes = false;
		g_clTaskWork[m_nUnit].m_bOutputCheck[2] = false;	//OC

	}
	else 
	{
		g_clMesCommunication[m_nUnit].m_dMesFovResult[0] = 1;
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Fov] HFov Spec In: %.3lf [%.3lf~%.3lf]"), mFovValue, mFovMin, mFovMax);
		AddLog(szLog, 0, m_nUnit);
	}

	mFovValue = g_clMesCommunication[m_nUnit].m_dMesFov[1];
	mFovMin = (_ttof(EEpromVerifyData.vMinData[19]));
	mFovMax = (_ttof(EEpromVerifyData.vMaxData[19]));


	if (mFovValue < mFovMin || mFovValue > mFovMax)
	{
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;	//VFOV
		g_clMesCommunication[m_nUnit].m_dMesFovResult[1] = 0;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[Fov] VFov Spec Out: %.6lf [%.3lf~%.3lf]"), mFovValue, mFovMin, mFovMax);
		AddLog(szLog, 0, m_nUnit);
		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [VFov NG]");
		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG VFov :%.3lf [%.3lf~%.3lf]"), mFovValue, mFovMin, mFovMax);
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}

		g_clMandoInspLog[m_nUnit].m_bInspRes = false;
		g_clTaskWork[m_nUnit].m_bOutputCheck[2] = false;	//OC

	}
	else
	{
		g_clMesCommunication[m_nUnit].m_dMesFovResult[1] = 1;
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Fov] VFov Spec In: %.3lf [%.3lf~%.3lf]"), mFovValue, mFovMin, mFovMax);
		AddLog(szLog, 0, m_nUnit);
	}


	g_SaveLGITLog(m_nUnit, "FOV", m_pChartProc->GetLogHeader(), m_pChartProc->GetLogData(), m_pChartProc->GetVersion());
	g_clVision.DrawOverlayAll(m_nUnit);
	return false;
}

//-----------------------------------------------------------------------------
//
//	Lens Shading (Relative Illumination X) 3000k , 5000k
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_LensShading(BYTE* pBuffer,int index,  bool bAutoMode)	//R/C,B/C,Cr/Cb
{

	return true;
}

//-----------------------------------------------------------------------------
//
//	White Balance (Color Sensitivity) 3000 , 5000K , Dark 세번 검사
//
//-----------------------------------------------------------------------------
//bool CPRIFunc_Insp::func_Insp_ColorSensitivity(BYTE* _____img, int index, bool bAutoMode)	//R/C,B/C,Cr/Cb
bool CPRIFunc_Insp::func_Insp_WhiteBalance(BYTE* _____img, int index, bool bAutoMode)	//R/C,B/C,Cr/Cb
{
	
	return false;
}
//-----------------------------------------------------------------------------
//
//	SNR & Row/Col.Noise  = FPN검사 (5000, Dark)
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_SnrRowColNoise(BYTE* pBuffer, int index, bool bAutoMode)
{
	
	return false;
}


//-----------------------------------------------------------------------------
//
//	Relative Illumination (RI) 검사
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_Shm_Illumination(BYTE* rawImage, bool bAutoMode)
{
	//TRelativeIlluminationSpecX& _Spec,
	bool bRes = true;
	int i = 0;
	int nResult = R_RESULT_PASS;
	char strTmp[1024];
	TCHAR szLog[SIZE_OF_1K];

	int nWidth = g_clModelData[m_nUnit].m_nWidth;
	int nHeight = g_clModelData[m_nUnit].m_nHeight;

	bool bUse8BitOnly = false;
	TDATASPEC& tDataSpec = g_clLaonGrabberWrapper[m_nUnit].dRi_Tdataspec;

	if (g_clModelData[m_nUnit].m_nRi8BitUse == 1)
	{
		bUse8BitOnly = true;
	}
	TRelativeIlluminationSpecN tRelativeIlluminationSpecN;
	// Image buffers
	std::vector<RECT> vROI;
	std::vector<double> vOffset;

	memset(&tRelativeIlluminationSpecN, 0x00, sizeof(tRelativeIlluminationSpecN));

	//TROIData tROI;
	tRelativeIlluminationSpecN.dSpecRIcornerMin = g_clModelData[m_nUnit].m_RISpec[0];// 60.0;		//g_clModelData[m_nUnit].m_RISpec[i]
	tRelativeIlluminationSpecN.dSpecRIcornerMax = g_clModelData[m_nUnit].m_RISpec[1];//100.0;
	tRelativeIlluminationSpecN.dSpecRIminMin = g_clModelData[m_nUnit].m_RISpec[2];//5;
	tRelativeIlluminationSpecN.dSpecRIminMax = g_clModelData[m_nUnit].m_RISpec[3];//100;
	tRelativeIlluminationSpecN.dCenterIntensity = g_clModelData[m_nUnit].m_RISpec[4];//2000;
	tRelativeIlluminationSpecN.nSpecRINormalizeIndex = g_clModelData[m_nUnit].m_RISpec[5];//0;

	tRelativeIlluminationSpecN.tROI.ROICount = 5;
	vROI.resize(tRelativeIlluminationSpecN.tROI.ROICount);
	tRelativeIlluminationSpecN.tROI.pROIData = vROI.data();
	tRelativeIlluminationSpecN.tROI.eROIType = ROIType_RECT;
	tRelativeIlluminationSpecN.tROI.dOffset = vOffset.data();

	g_clVision.ClearOverlay(m_nUnit);
	RECT rtRefEdge;
	int roiSize = 50;
	double nfield = 0.85;
	int fieldGapW = (nWidth * nfield);
	int fieldGapH = (nHeight * nfield);

	vROI[0].left = 935;		// nWidth / 2 - (roiSize / 2);
	vROI[0].top = 515;		// nHeight / 2 - (roiSize / 2);
	vROI[0].right = vROI[0].left + roiSize;
	vROI[0].bottom = vROI[0].top + roiSize;

	sprintf_s(strTmp, "#1");
	g_clVision.DrawMOverlayText(m_nUnit, vROI[0].left+10, vROI[0].top-50, strTmp, M_COLOR_CYAN, _T("Arial"), 8, 0);

	//LT
	vROI[1].left = 118;	// nWidth - fieldGapW;
	vROI[1].top = 55;	// nHeight - fieldGapH;
	vROI[1].right = vROI[1].left + roiSize;
	vROI[1].bottom = vROI[1].top + roiSize;

	sprintf_s(strTmp, "#2");
	g_clVision.DrawMOverlayText(m_nUnit, vROI[1].left+12, vROI[1].bottom + 10, strTmp, M_COLOR_CYAN, _T("Arial"), 8, 0);

	//RT
	vROI[2].left = 1751;	// fieldGapW;
	vROI[2].top = 55;		// nHeight - fieldGapH;
	vROI[2].right = vROI[2].left + roiSize;
	vROI[2].bottom = vROI[2].top + roiSize;

	sprintf_s(strTmp, "#3");
	g_clVision.DrawMOverlayText(m_nUnit, vROI[2].left+12, vROI[2].bottom + 10, strTmp, M_COLOR_CYAN, _T("Arial"), 8, 0);

	//BL
	vROI[3].left = 118;	// nWidth - fieldGapW;
	vROI[3].top = 974;	// fieldGapH;
	vROI[3].right = vROI[3].left + roiSize;
	vROI[3].bottom = vROI[3].top + roiSize;

	sprintf_s(strTmp, "#4");
	g_clVision.DrawMOverlayText(m_nUnit, vROI[3].left+5, vROI[3].top - 50, strTmp, M_COLOR_CYAN, _T("Arial"), 8, 0);
	//BR
	vROI[4].left = 1751;	// fieldGapW;
	vROI[4].top = 974;	// fieldGapH;
	vROI[4].right = vROI[4].left + roiSize;
	vROI[4].bottom = vROI[4].top + roiSize;

	sprintf_s(strTmp, "#5");
	g_clVision.DrawMOverlayText(m_nUnit, vROI[4].left+5, vROI[4].top - 50, strTmp, M_COLOR_CYAN, _T("Arial"), 8, 0);

	
	for (i = 0; i < 5; i++)
	{
		rtRefEdge.left = vROI[i].left;
		rtRefEdge.top = vROI[i].top;
		rtRefEdge.right = vROI[i].right;
		rtRefEdge.bottom = vROI[i].bottom;

		g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, rtRefEdge.left, rtRefEdge.top, rtRefEdge.right, rtRefEdge.bottom, M_COLOR_BLUE, 1, FALSE);
		//vision.boxlist[CCD].addList(rtRefEdge, PS_SOLID, M_COLOR_BLUE);
	}
	bool bRaw = true;
	bool bEnableRelativeIllumination = true;
	bool bEnableRelativeIlluminationX = true;
	bool bEnableRelativeUniformity = true;
	bool bEnableColorSensitivity = true;
	bool bSaveResultImage = false;
	//----------------------------------------------------------------------
	// Inspect Main Camera
	//----------------------------------------------------------------------

	std::shared_ptr<CACMISShadingRelativeIllumination> m_pRelativeIllumination = std::make_shared<CACMISShadingRelativeIllumination>();

	//Inspection
	if (!m_pRelativeIllumination->Inspect(rawImage, nWidth, nHeight, tRelativeIlluminationSpecN, tDataSpec.eDataFormat, tDataSpec.eOutMode, tDataSpec.eSensorType, tDataSpec.nBlackLevel, 
		bUse8BitOnly, false, tDataSpec.eDemosaicMethod))
	{
		return false;
	}

	TRelativeIlluminationResultN m_stRelativeIlluminationResult;
	m_stRelativeIlluminationResult = *m_pRelativeIllumination->GetInspectionResult(0);  //dRicorner

	g_clMesCommunication[m_nUnit].m_nMesRICorner[0] = m_stRelativeIlluminationResult.dRIcornerRatio[1];
	g_clMesCommunication[m_nUnit].m_nMesRICorner[1] = m_stRelativeIlluminationResult.dRIcornerRatio[2];
	g_clMesCommunication[m_nUnit].m_nMesRICorner[2] = m_stRelativeIlluminationResult.dRIcornerRatio[3];
	g_clMesCommunication[m_nUnit].m_nMesRICorner[3] = m_stRelativeIlluminationResult.dRIcornerRatio[4];

	g_clMesCommunication[m_nUnit].m_dMesRiDiff = m_pRelativeIllumination->GetMaxDiff();
	_stprintf_s(szLog, SIZE_OF_1K, _T("[RI] MaxDiff : %.6lf"), g_clMesCommunication[m_nUnit].m_dMesRiDiff);
	AddLog(szLog, 0, m_nUnit);


	g_clMesCommunication[m_nUnit].m_dMesRiCenterRaw = m_stRelativeIlluminationResult.dRIcenterRAW;
	_stprintf_s(szLog, SIZE_OF_1K, _T("[RI] RIcenterRAW : %.6lf"), g_clMesCommunication[m_nUnit].m_dMesRiCenterRaw);
	AddLog(szLog, 0, m_nUnit);



	double dMinTemp = g_clMesCommunication[m_nUnit].m_nMesRICorner[0];
	for (i = 0; i < 4; i++)
	{
		if (dMinTemp > g_clMesCommunication[m_nUnit].m_nMesRICorner[i])
		{
			dMinTemp = g_clMesCommunication[m_nUnit].m_nMesRICorner[i];
		}
	}

	g_clMesCommunication[m_nUnit].m_dMesRiMinDiff = dMinTemp;

	double mRi_Value = 0.0;

	double mRi_SpecMin = 0.0;
	double mRi_SpecMax = 0.0;



	//mRi_Value = g_clMesCommunication[m_nUnit].m_dMesRiCenterRaw;
	//mRi_SpecMin = (_ttof(EEpromVerifyData.vMinData[34]));
	//mRi_SpecMax = (_ttof(EEpromVerifyData.vMaxData[34]));


	//if (mRi_Value < mRi_SpecMin || mRi_Value > mRi_SpecMax)
	//{
	//	g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;
	//	g_clMesCommunication[m_nUnit].m_nMesRICenterRawResult = 0;

	//	_stprintf_s(szLog, SIZE_OF_1K, _T("[RI] RIcenterRAW Spec Out: %.6lf [%.2lf~%.2lf]"), mRi_Value, mRi_SpecMin, mRi_SpecMax);
	//	AddLog(szLog, 0, m_nUnit);
	//	g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [RIcenterRAW NG]");
	//	if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
	//	{
	//		g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG RIcenterRAW :%.6lf [%.2lf~%.2lf]"), mRi_Value, mRi_SpecMin, mRi_SpecMax);
	//		g_clMandoInspLog[m_nUnit].m_nNGCnt++;
	//	}
	//	//g_clMesCommunication[m_nUnit].m_nMesRIRICornerResult[0] = 0;

	//	g_clMandoInspLog[m_nUnit].m_bInspRes = false;
	//}
	//else
	//{
	//	g_clMesCommunication[m_nUnit].m_nMesRICenterRawResult = 1;
	//	_stprintf_s(szLog, SIZE_OF_1K, _T("[RI] RIcenterRAW Spec In: %.6lf [%.2lf~%.2lf]"), mRi_Value, mRi_SpecMin, mRi_SpecMax);
	//	AddLog(szLog, 0, m_nUnit);
	//}
	
	for (i = 0; i < 4; i++)
	{
		mRi_Value = g_clMesCommunication[m_nUnit].m_nMesRICorner[i];
		mRi_SpecMin = (_ttof(EEpromVerifyData.vMinData[34 + i]));
		mRi_SpecMax = (_ttof(EEpromVerifyData.vMaxData[34 + i]));

		if (mRi_Value < mRi_SpecMin || mRi_Value > mRi_SpecMax)
		{
			g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;//XX
			g_clMesCommunication[m_nUnit].m_nMesRICornerResult[i] = 0;
			_stprintf_s(szLog, SIZE_OF_1K, _T("[RI] RIcorner %d Spec Out: %.6lf [%.2lf~%.2lf]"),i,  mRi_Value, mRi_SpecMin, mRi_SpecMax);
			AddLog(szLog, 0, m_nUnit);
			g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [RIcorner NG]");
			if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
			{
				g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG RIcorner %d :%.6lf [%.2lf~%.2lf]"), i, mRi_Value, mRi_SpecMin, mRi_SpecMax);
				g_clMandoInspLog[m_nUnit].m_nNGCnt++;
			}
			//g_clMesCommunication[m_nUnit].m_nMesRIRICornerResult[0] = 0;

			g_clMandoInspLog[m_nUnit].m_bInspRes = false;
			g_clTaskWork[m_nUnit].m_bOutputCheck[2] = false;	//OC

		}
		else
		{
			g_clMesCommunication[m_nUnit].m_nMesRICornerResult[i] = 1;
			_stprintf_s(szLog, SIZE_OF_1K, _T("[RI] RIcorner %d Spec In: %.6lf [%.2lf~%.2lf]"), i, mRi_Value, mRi_SpecMin, mRi_SpecMax);
			AddLog(szLog, 0, m_nUnit);
		}
	}


	

	//mRi_Value = g_clMesCommunication[m_nUnit].m_dMesRiDiff;
	//mRi_SpecMin = (_ttof(EEpromVerifyData.vMinData[36]));
	//mRi_SpecMax = (_ttof(EEpromVerifyData.vMaxData[36]));


	//if (mRi_Value < mRi_SpecMin || mRi_Value > mRi_SpecMax)
	//{
	//	g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;//XX
	//	g_clMesCommunication[m_nUnit].m_nMesRIDiffResult = 0;

	//	_stprintf_s(szLog, SIZE_OF_1K, _T("[RI] MaxDiff Spec Out: %.6lf [%.2lf~%.2lf]"), mRi_Value, mRi_SpecMin, mRi_SpecMax);
	//	AddLog(szLog, 0, m_nUnit);
	//	g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [MaxDiff NG]");
	//	if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
	//	{
	//		g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG MaxDiff :%.6lf [%.2lf~%.2lf]"), mRi_Value, mRi_SpecMin, mRi_SpecMax);
	//		g_clMandoInspLog[m_nUnit].m_nNGCnt++;
	//	}
	//	//g_clMesCommunication[m_nUnit].m_nMesRIRICornerResult[0] = 0;

	//	g_clMandoInspLog[m_nUnit].m_bInspRes = false;
	//	g_clTaskWork[m_nUnit].m_bOutputCheck[2] = false;	//OC

	//}
	//else
	//{
	//	g_clMesCommunication[m_nUnit].m_nMesRIDiffResult = 1;
	//	_stprintf_s(szLog, SIZE_OF_1K, _T("[RI] MaxDiff Spec In: %.6lf [%.2lf~%.2lf]"), mRi_Value, mRi_SpecMin, mRi_SpecMax);
	//	AddLog(szLog, 0, m_nUnit);
	//}


	mRi_Value = g_clMesCommunication[m_nUnit].m_dMesRiMinDiff;
	mRi_SpecMin = (_ttof(EEpromVerifyData.vMinData[38]));
	mRi_SpecMax = (_ttof(EEpromVerifyData.vMaxData[38]));

	if (mRi_Value < mRi_SpecMin)
	{
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;
		g_clMesCommunication[m_nUnit].m_nMesRIMinDiffResult = 0;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[RI] RICorner Min Spec Out: %.6lf [%.2lf ~]"), mRi_Value, mRi_SpecMin);
		AddLog(szLog, 0, m_nUnit);
		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [RICorner Min NG]");
		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG RICorner Min :%.6lf [%.2lf]"), mRi_Value, mRi_SpecMin);
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		} 
		//g_clMesCommunication[m_nUnit].m_nMesRIRICornerResult[0] = 0; 

		g_clMandoInspLog[m_nUnit].m_bInspRes = false;
	}
	else
	{
		g_clMesCommunication[m_nUnit].m_nMesRIMinDiffResult = 1;
		_stprintf_s(szLog, SIZE_OF_1K, _T("[RI] RICorner Min Spec In: %.6lf [%.2lf ~ ]"), mRi_Value, mRi_SpecMin);
		AddLog(szLog, 0, m_nUnit);
	}

	
	g_clVision.DrawOverlayAll(m_nUnit);
	//if (MandoInspLog.dRiDiff < MandoSfrSpec.INSP_RIDiff_Spec)
	//{
	//	sTemp.Format("RI MaxDiff Spec NG: %.6lf (Spec:%.6lf)", MandoInspLog.dRiDiff, MandoSfrSpec.INSP_RIDiff_Spec);
	//	//! Main Display화면 Overlay NG List
	//	MandoInspLog.sDispNG[MandoInspLog.iNGCnt].Format("RI MaxDiff fail: %.6lf (Spec:%.6lf)", MandoInspLog.dRiDiff, MandoSfrSpec.INSP_RIDiff_Spec);
	//	MandoInspLog.iNGCnt++;
	//	MandoInspLog.bInspRes = false;//LCB
	//								  //bResult = false;
	//	theApp.MainDlg->putListLog(sTemp);
	//	MandoInspLog.sNGList += sTemp;
	//}
	//else
	//{
	//	sTemp.Format("RI MaxDiff Spec IN: %.6lf (Spec:%.6lf)", MandoInspLog.dRiDiff, MandoSfrSpec.INSP_RIDiff_Spec);
	//	theApp.MainDlg->putListLog(sTemp);
	//}


	g_SaveLGITLog(m_nUnit, "RI", m_pRelativeIllumination->GetLogHeader(), m_pRelativeIllumination->GetLogData(), m_pRelativeIllumination->GetVersion());
	return true;
}

bool CPRIFunc_Insp::func_Insp_ColorShading(BYTE* pBuffer, int index, bool bAutoMode)
{
	
	return false;
}


//-----------------------------------------------------------------------------
//
//	IR Filter IR 광원 밝기 검사
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_IRFilterTest(const BYTE* pBuffer, bool bAutoMode)
{
	
	return false;
}

//-----------------------------------------------------------------------------
//
//	Color Reproduction 검사
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_Color_reproduction(const BYTE* pBuffer, bool bAutoMode)
{
	TCHAR szLog[SIZE_OF_1K];
	int i = 0;
	int nResult = R_RESULT_PASS;
	int nWidth = g_clModelData[m_nUnit].m_nWidth;
	int nHeight = g_clModelData[m_nUnit].m_nHeight;
	TDATASPEC& tDataSpec = g_clLaonGrabberWrapper[m_nUnit].dColor_Tdataspec;
	bool bUse8BitOnly = false;

	if (g_clModelData[m_nUnit].m_nColor8BitUse == 1)
	{
		bUse8BitOnly = true;
	}

	g_clVision.ClearOverlay(m_nUnit);
	CACMISColorReproduction *m_pColorReproduction = new CACMISColorReproduction();

	std::vector<RECT> vROI;
	std::vector<double> vOffset;
	std::vector<double> vThreshold;
	std::vector<TColorLab> vColorLab;

	//TColorReproductionSpecN m_stColorReproductionSpec;
	TColorReproductionSpecN m_stColorReproductionSpec;
	m_stColorReproductionSpec.tROI.ROICount = 4;
	vROI.resize(m_stColorReproductionSpec.tROI.ROICount);
	vOffset.resize(m_stColorReproductionSpec.tROI.ROICount);
	vThreshold.resize(m_stColorReproductionSpec.tROI.ROICount);
	vColorLab.resize(m_stColorReproductionSpec.tROI.ROICount);

	

	vThreshold[0] = g_clModelData[m_nUnit].m_ColorReproductionSpec[0];//20.0;
	vThreshold[1] = g_clModelData[m_nUnit].m_ColorReproductionSpec[1];//20.0;
	vThreshold[2] = g_clModelData[m_nUnit].m_ColorReproductionSpec[2];//20.0;
	vThreshold[3] = g_clModelData[m_nUnit].m_ColorReproductionSpec[3];//20.0;


	vColorLab[0].L = g_clModelData[m_nUnit].m_ColorReproductionSpec[4];//32.404;
	vColorLab[0].a = g_clModelData[m_nUnit].m_ColorReproductionSpec[5];//44.222;
	vColorLab[0].b = g_clModelData[m_nUnit].m_ColorReproductionSpec[6];//37.356;

	vColorLab[1].L = g_clModelData[m_nUnit].m_ColorReproductionSpec[7];//11.326;
	vColorLab[1].a = g_clModelData[m_nUnit].m_ColorReproductionSpec[8];//33.245;
	vColorLab[1].b = g_clModelData[m_nUnit].m_ColorReproductionSpec[9];//-51.351;

	vColorLab[2].L = g_clModelData[m_nUnit].m_ColorReproductionSpec[10];//2.151;
	vColorLab[2].a = g_clModelData[m_nUnit].m_ColorReproductionSpec[11];//0.0;
	vColorLab[2].b = g_clModelData[m_nUnit].m_ColorReproductionSpec[12];//-0.001;

	vColorLab[3].L = g_clModelData[m_nUnit].m_ColorReproductionSpec[13];//26.191;
	vColorLab[3].a = g_clModelData[m_nUnit].m_ColorReproductionSpec[14];//-25.316;
	vColorLab[3].b = g_clModelData[m_nUnit].m_ColorReproductionSpec[15];//28.054;

	int offsetX = ((g_clModelData[m_nUnit].m_nWidth / 2) - (g_clTaskWork[m_nUnit].m_clPtCircle[0].x + g_clTaskWork[m_nUnit].m_clPtCircle[1].x + g_clTaskWork[m_nUnit].m_clPtCircle[2].x + g_clTaskWork[m_nUnit].m_clPtCircle[3].x) / 4) * -1;
	int offsetY = ((g_clModelData[m_nUnit].m_nHeight / 2) - (g_clTaskWork[m_nUnit].m_clPtCircle[0].y + g_clTaskWork[m_nUnit].m_clPtCircle[1].y + g_clTaskWork[m_nUnit].m_clPtCircle[2].y + g_clTaskWork[m_nUnit].m_clPtCircle[3].y) / 4) * -1;

	vROI[0].left = g_clModelData[m_nUnit].m_ColorReproductionSpec[16] + offsetX;
	vROI[0].top = g_clModelData[m_nUnit].m_ColorReproductionSpec[17] + offsetY;
	vROI[0].right = g_clModelData[m_nUnit].m_ColorReproductionSpec[18] + offsetX;
	vROI[0].bottom = g_clModelData[m_nUnit].m_ColorReproductionSpec[19] + offsetY;
	//
	vROI[1].left = g_clModelData[m_nUnit].m_ColorReproductionSpec[20] + offsetX;
	vROI[1].top = g_clModelData[m_nUnit].m_ColorReproductionSpec[21] + offsetY;
	vROI[1].right = g_clModelData[m_nUnit].m_ColorReproductionSpec[22] + offsetX;
	vROI[1].bottom = g_clModelData[m_nUnit].m_ColorReproductionSpec[23] + offsetY;
	//
	vROI[2].left = g_clModelData[m_nUnit].m_ColorReproductionSpec[24] + offsetX;
	vROI[2].top = g_clModelData[m_nUnit].m_ColorReproductionSpec[25] + offsetY;
	vROI[2].right = g_clModelData[m_nUnit].m_ColorReproductionSpec[26] + offsetX;
	vROI[2].bottom = g_clModelData[m_nUnit].m_ColorReproductionSpec[27] + offsetY;
	//
	vROI[3].left = g_clModelData[m_nUnit].m_ColorReproductionSpec[28] + offsetX;
	vROI[3].top = g_clModelData[m_nUnit].m_ColorReproductionSpec[29] + offsetY;
	vROI[3].right = g_clModelData[m_nUnit].m_ColorReproductionSpec[30] + offsetX;
	vROI[3].bottom = g_clModelData[m_nUnit].m_ColorReproductionSpec[31] + offsetY;


	m_stColorReproductionSpec.tROI.pROIData = vROI.data();
	m_stColorReproductionSpec.tROI.dOffset = vOffset.data();
	m_stColorReproductionSpec.tROI.eROIType = ROIType_RECT;
	m_stColorReproductionSpec.pdThresholdDelta = vThreshold.data();

	m_stColorReproductionSpec.ptRefColorLab = vColorLab.data();
	for (int i = 0; i < 4; i++)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[ColorReproduction] Roi #%d / Left:%d,Top:%d,Right:%d,Bottom:%d"), i + 1, vROI[i].left, vROI[i].top, vROI[i].right, vROI[i].bottom);
		AddLog(szLog, 0, m_nUnit);
	}
	
	char strTmp[1024];
	
	int dTextX = 0;
	int dTextY = 0;

	dTextX = vROI[0].left;
	dTextY = vROI[0].top - 60;
	if (dTextY < 0)
	{
		dTextY = 0;
	}
	sprintf_s(strTmp, "#1");
	g_clVision.DrawMOverlayText(m_nUnit, dTextX, dTextY, strTmp, M_COLOR_CYAN, _T("Arial"), 8, 0);
	//g_clVision.DrawMOverlayText(m_nUnit, vROI[4].left, vROI[4].top - 50, strTmp, M_COLOR_CYAN, _T("Arial"), 8, 0);
	dTextX = vROI[1].left;
	dTextY = vROI[1].top - 60;
	if (dTextY < 0)
	{
		dTextY = 0;
	}
	sprintf_s(strTmp, "#2");
	g_clVision.DrawMOverlayText(m_nUnit, dTextX, dTextY, strTmp, M_COLOR_CYAN, _T("Arial"), 8, 0);
	dTextX = vROI[2].left;
	dTextY = vROI[2].top - 60;
	if (dTextY < 0)
	{
		dTextY = 0;
	}
	sprintf_s(strTmp, "#3");
	g_clVision.DrawMOverlayText(m_nUnit, dTextX, dTextY, strTmp, M_COLOR_CYAN, _T("Arial"), 8, 0);
	dTextX = vROI[3].left;
	dTextY = vROI[3].top - 60;
	if (dTextY < 0)
	{
		dTextY = 0;
	}
	sprintf_s(strTmp, "#4");
	g_clVision.DrawMOverlayText(m_nUnit, dTextX, dTextY, strTmp, M_COLOR_CYAN, _T("Arial"), 8, 0);
	//
	g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, vROI[0].left, vROI[0].top, vROI[0].right, vROI[0].bottom, M_COLOR_BLUE, 1, FALSE);
	g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, vROI[1].left, vROI[1].top, vROI[1].right, vROI[1].bottom, M_COLOR_BLUE, 1, FALSE);
	g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, vROI[2].left, vROI[2].top, vROI[2].right, vROI[2].bottom, M_COLOR_BLUE, 1, FALSE);
	g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, vROI[3].left, vROI[3].top, vROI[3].right, vROI[3].bottom, M_COLOR_BLUE, 1, FALSE);

	//ROI VIEW
	vOffset[0] = 0.0;
	vOffset[1] = 0.0;
	vOffset[2] = 0.0;
	vOffset[3] = 0.0;

	for (int i = 0; i < 4; i++)
	{
		g_clMesCommunication[m_nUnit].m_nMesColorReproduction[i] = 0.0;
		g_clMesCommunication[m_nUnit].m_nMesColorReproductionResult[i] = 1;
	}
	double mColorValue = 0.0;
	double mColorSpec = 0.0;
	int mIndex = 0;

	bool result = m_pColorReproduction->Inspect(pBuffer, nWidth, nHeight, m_stColorReproductionSpec, 
		tDataSpec.eDataFormat, tDataSpec.eOutMode, tDataSpec.eSensorType, tDataSpec.nBlackLevel, bUse8BitOnly, 
		false, tDataSpec.eDemosaicMethod);
	
	for (int i = 0; i < m_pColorReproduction->GetInspectionRegionCount(); i++)
	{
		const TColorReproductionResult* pResult = m_pColorReproduction->GetInspectionResult(i); // 결과 값
		//printf(“[ColorReproduction]Region = %d, ROI(% 4d, % 4d, % 4d % 4d), Delta = %.3f, L = %.3f, a = %.3f, b = %.3f\n”,
		//	pResult->nIndex, pResult->rtROI.left, pResult->rtROI.top, pResult->rtROI.right, pResult->rtROI.bottom, pResult ->dDelta, pResult->tColorLab.L, pResult->tColorLab.a, pResult->tColorLab.b);

		g_clMandoInspLog[m_nUnit].m_dColorReproductionResult[i] = pResult->dDelta;
		g_clMesCommunication[m_nUnit].m_nMesColorReproduction[i] = pResult->dDelta;

		_stprintf_s(szLog, SIZE_OF_1K, _T("	[ColorReproduction] Region = %d, ROI(%4d, %4d, %4d %4d), Delta = %.3f, L = %.3f, a = %.3f, b = %.3f"),
			pResult->nIndex, pResult->rtROI.left, pResult->rtROI.top, pResult->rtROI.right, pResult->rtROI.bottom, pResult->dDelta, pResult->tColorLab.L, pResult->tColorLab.a, pResult->tColorLab.b);
		AddLog(szLog, 0, m_nUnit);
	}

	double mColor_Value = 0.0;
	double mColor_SpecMin = 0.0;
	double mColor_SpecMax = 0.0;


	for (i = 0; i < 4; i++)
	{
		mColor_Value = g_clMesCommunication[m_nUnit].m_nMesColorReproduction[i];
		//mColor_SpecMin = (_ttof(EEpromVerifyData.vMinData[20 + i]));
		mColor_SpecMax = (_ttof(EEpromVerifyData.vMaxData[20 + i]));

		if (mColor_Value > mColor_SpecMax)
		{
			g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;	//ColorReproduction
			g_clMesCommunication[m_nUnit].m_nMesColorReproductionResult[i] = 0;
			_stprintf_s(szLog, SIZE_OF_1K, _T("[ColorReproduction] Region = %d,  Delta Spec Out: %.6lf [ ~ %.3lf]"), i+1, mColor_Value, mColor_SpecMax);
			AddLog(szLog, 0, m_nUnit);
			g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [ColorReproduction NG]");
			if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
			{
				g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG ColorReproduction %d :%.6lf [ ~ %.3lf]"), i + 1, mColor_Value, mColor_SpecMax);
				g_clMandoInspLog[m_nUnit].m_nNGCnt++;
			}

			g_clMandoInspLog[m_nUnit].m_bInspRes = false;
			g_clTaskWork[m_nUnit].m_bOutputCheck[2] = false;

		}
		else
		{
			g_clMesCommunication[m_nUnit].m_nMesColorReproductionResult[i] = 1;
			_stprintf_s(szLog, SIZE_OF_1K, _T("[ColorReproduction] Region = %d,  Delta Spec In: %.6lf [ ~ %.3lf]"), i + 1, mColor_Value, mColor_SpecMax);
			AddLog(szLog, 0, m_nUnit);
		}
	}
	
	g_clVision.DrawOverlayAll(m_nUnit);
	

	g_SaveLGITLog(m_nUnit, "Color Reproduction", m_pColorReproduction->GetLogHeader(), m_pColorReproduction->GetLogData(), m_pColorReproduction->GetVersion());

	delete m_pColorReproduction;
	return true;
}

int CPRIFunc_Insp::Inspect_RelativeIlluminationX(const BYTE * pBuffer, int nImageWidth, int nImageHeight, TRelativeIlluminationSpecX & _Spec, TDATASPEC & tDataSpec, IplImage * cvImgRI, bool bUse8BitOnly)
{
	int nResult = R_RESULT_PASS;
	TCHAR	szLog[SIZE_OF_1K];
	std::shared_ptr<CACMISShadingRelativeIllumination_X> m_pRelativeIlluminationX = std::make_shared<CACMISShadingRelativeIllumination_X>();

	//std::cout << "[Relative Illumination X] Version = " << m_pRelativeIlluminationX->GetVersion() << std::endl;
	_stprintf_s(szLog, SIZE_OF_1K, _T("[Relative Illumination X] Version %s"), m_pRelativeIlluminationX->GetVersion());
	AddLog(szLog, 0, m_nUnit, false);
	//theApp.MainDlg->putListLog(szLog);
	//szLog.Format("[Relative Illumination X] Version %s", m_pRelativeIlluminationX->GetVersion());
	//Inspection
	if (!m_pRelativeIlluminationX->Inspect(pBuffer, nImageWidth, nImageHeight, _Spec, tDataSpec.eDataFormat, tDataSpec.eOutMode, tDataSpec.eSensorType, tDataSpec.nBlackLevel, bUse8BitOnly))
	{
		//std::cout << "[Relative Illumination X] Inspection Fail! " << std::endl;
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[Relative Illumination X] Inspection Fail!"));
		AddLog(szLog, 0, m_nUnit, false);
		//AddLog(szLog, 0, m_nUnit);
		//theApp.MainDlg->putListLog(szLog);
		return FALSE;
	}

	//Result
	TRelativeIlluminationResultX stCenterResult = *m_pRelativeIlluminationX->GetInspectionCenterResult();
	RECT rt;

	rt.left = stCenterResult.rtROI.left * 2;
	rt.top = stCenterResult.rtROI.top * 2;
	rt.right = stCenterResult.rtROI.right * 2;
	rt.bottom = stCenterResult.rtROI.bottom * 2;
	cvRectangle(cvImgRI, cvPoint(rt.left, rt.top), cvPoint(rt.right, rt.bottom), CV_RGB(100, 100, 100));

	//Logging
	std::cout << "[Relative Illumination X] Center= " << stCenterResult.dRIRawResult[0] << "," << stCenterResult.dRIRawResult[1] << "," << stCenterResult.dRIRawResult[2] << "," << stCenterResult.dRIRawResult[3] << "," << std::endl;


	_stprintf_s(szLog, SIZE_OF_1K, _T("	[Relative Illumination X] Center=%lf,%lf,%lf,%lf"), stCenterResult.dRIRawResult[0], stCenterResult.dRIRawResult[1], stCenterResult.dRIRawResult[2], stCenterResult.dRIRawResult[3]);
	//AddLog(szLog, 0, m_nUnit);
	//theApp.MainDlg->putListLog(szLog);
	AddLog(szLog, 0, m_nUnit, false);
	double CornerVarTemp = 0.0;

	g_clMandoInspLog[m_nUnit].m_Log_RI_Center_R = stCenterResult.dRIRawResult[1];
	g_clMandoInspLog[m_nUnit].m_Log_RI_Center_Cr = stCenterResult.dRIRawResult[0];
	g_clMandoInspLog[m_nUnit].m_Log_RI_Center_Cb = stCenterResult.dRIRawResult[3];
	g_clMandoInspLog[m_nUnit].m_Log_RI_Center_B = stCenterResult.dRIRawResult[2];

	g_clMandoInspLog[m_nUnit].m_Log_RI_CornerVar_R = _finite(m_pRelativeIlluminationX->GetCornerVariation(1)) ? m_pRelativeIlluminationX->GetCornerVariation(1) : 0.0;
	g_clMandoInspLog[m_nUnit].m_Log_RI_CornerVar_Cr = _finite(m_pRelativeIlluminationX->GetCornerVariation(0)) ? m_pRelativeIlluminationX->GetCornerVariation(0) : 0.0;
	g_clMandoInspLog[m_nUnit].m_Log_RI_CornerVar_Cb = _finite(m_pRelativeIlluminationX->GetCornerVariation(3)) ? m_pRelativeIlluminationX->GetCornerVariation(3) : 0.0;
	g_clMandoInspLog[m_nUnit].m_Log_RI_CornerVar_B = _finite(m_pRelativeIlluminationX->GetCornerVariation(2)) ? m_pRelativeIlluminationX->GetCornerVariation(2) : 0.0;
	//if (!_finite(dbXData))



	//spec Check
	CornerVarTemp = g_clMandoInspLog[m_nUnit].m_Log_RI_CornerVar_R;
	if (CornerVarTemp < g_clModelData[m_nUnit].m_RISpec[6] || CornerVarTemp >= g_clModelData[m_nUnit].m_RISpec[7])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[RI] CornerVar_R Spec Out %lf [%.1lf~%.1lf]"), CornerVarTemp, g_clModelData[m_nUnit].m_RISpec[6], g_clModelData[m_nUnit].m_RISpec[7]);
		AddLog(szLog, 0, m_nUnit, false);
		//theApp.MainDlg->putListLog(szLog);
		g_clMandoInspLog[m_nUnit].sDispNG[g_clMandoInspLog[m_nUnit].iNGCnt].Format("[RI] CornerVar_R Spec Out: %lf [%.1lf~%.1lf])", CornerVarTemp, g_clModelData[m_nUnit].m_RISpec[6], g_clModelData[m_nUnit].m_RISpec[7]);
		g_clMandoInspLog[m_nUnit].iNGCnt++;
		g_clMandoInspLog[m_nUnit].m_bInspRes = false;	//RI
		g_clMandoInspLog[m_nUnit].m_sNGList += szLog;
	}
	CornerVarTemp = g_clMandoInspLog[m_nUnit].m_Log_RI_CornerVar_Cr;
	if (CornerVarTemp < g_clModelData[m_nUnit].m_RISpec[6] || CornerVarTemp >= g_clModelData[m_nUnit].m_RISpec[7])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[RI] CornerVar_Cr Spec Out %lf [%.1lf~%.1lf]"), CornerVarTemp, g_clModelData[m_nUnit].m_RISpec[6], g_clModelData[m_nUnit].m_RISpec[7]);
		AddLog(szLog, 0, m_nUnit, false);
		//theApp.MainDlg->putListLog(szLog);
		g_clMandoInspLog[m_nUnit].sDispNG[g_clMandoInspLog[m_nUnit].iNGCnt].Format("[RI] CornerVar_Cr Spec Out: %lf [%.1lf~%.1lf])", CornerVarTemp, g_clModelData[m_nUnit].m_RISpec[6], g_clModelData[m_nUnit].m_RISpec[7]);
		g_clMandoInspLog[m_nUnit].iNGCnt++;
		g_clMandoInspLog[m_nUnit].m_bInspRes = false;	//RI
		g_clMandoInspLog[m_nUnit].m_sNGList += szLog;
	}
	CornerVarTemp = g_clMandoInspLog[m_nUnit].m_Log_RI_CornerVar_Cb;
	if (CornerVarTemp < g_clModelData[m_nUnit].m_RISpec[6] || CornerVarTemp >= g_clModelData[m_nUnit].m_RISpec[7])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[RI] CornerVar_Cb Spec Out %lf [%.1lf~%.1lf]"), CornerVarTemp, g_clModelData[m_nUnit].m_RISpec[6], g_clModelData[m_nUnit].m_RISpec[7]);
		AddLog(szLog, 0, m_nUnit, false);
		//theApp.MainDlg->putListLog(szLog);
		g_clMandoInspLog[m_nUnit].sDispNG[g_clMandoInspLog[m_nUnit].iNGCnt].Format("[RI] CornerVar_Cb Spec Out: %lf [%.1lf~%.1lf])", CornerVarTemp, g_clModelData[m_nUnit].m_RISpec[6], g_clModelData[m_nUnit].m_RISpec[7]);
		g_clMandoInspLog[m_nUnit].iNGCnt++;
		g_clMandoInspLog[m_nUnit].m_bInspRes = false;	//RI
		g_clMandoInspLog[m_nUnit].m_sNGList += szLog;
	}
	CornerVarTemp = g_clMandoInspLog[m_nUnit].m_Log_RI_CornerVar_B;
	if (CornerVarTemp < g_clModelData[m_nUnit].m_RISpec[6] || CornerVarTemp >= g_clModelData[m_nUnit].m_RISpec[7])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[RI] CornerVar_B Spec Out: %lf [%.1lf~%.1lf]"), CornerVarTemp, g_clModelData[m_nUnit].m_RISpec[6], g_clModelData[m_nUnit].m_RISpec[7]);
		AddLog(szLog, 0, m_nUnit, false);
		//theApp.MainDlg->putListLog(szLog);
		g_clMandoInspLog[m_nUnit].sDispNG[g_clMandoInspLog[m_nUnit].iNGCnt].Format("[RI] CornerVar_B Spec Out: %lf [%.1lf~%.1lf])", CornerVarTemp, g_clModelData[m_nUnit].m_RISpec[6], g_clModelData[m_nUnit].m_RISpec[7]);
		g_clMandoInspLog[m_nUnit].iNGCnt++;
		g_clMandoInspLog[m_nUnit].m_bInspRes = false;	//RI
		g_clMandoInspLog[m_nUnit].m_sNGList += szLog;
	}
	//

	if (g_clMandoInspLog[m_nUnit].m_Log_RI_Center_R < _Spec.dSpecCenterIntensity[1])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[RI] RED Spec Out: %lf [%.1lf]"), g_clMandoInspLog[m_nUnit].m_Log_RI_Center_R, _Spec.dSpecCenterIntensity[1]);
		AddLog(szLog, 0, m_nUnit, false);
		//theApp.MainDlg->putListLog(szLog);
		g_clMandoInspLog[m_nUnit].sDispNG[g_clMandoInspLog[m_nUnit].iNGCnt].Format("[RI] RED Spec Out:%lf [%.1lf])", g_clMandoInspLog[m_nUnit].m_Log_RI_Center_R, _Spec.dSpecCenterIntensity[1]);
		g_clMandoInspLog[m_nUnit].iNGCnt++;
		g_clMandoInspLog[m_nUnit].m_bInspRes = false;	//RI
		g_clMandoInspLog[m_nUnit].m_sNGList += szLog;
	}
	if (g_clMandoInspLog[m_nUnit].m_Log_RI_Center_Cr < _Spec.dSpecCenterIntensity[0])
	{
		//g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;//XX
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[RI] CLEARR Spec Out: %lf [%.1lf]"), g_clMandoInspLog[m_nUnit].m_Log_RI_Center_Cr, _Spec.dSpecCenterIntensity[0]);
		//theApp.MainDlg->putListLog(szLog);
		g_clMandoInspLog[m_nUnit].sDispNG[g_clMandoInspLog[m_nUnit].iNGCnt].Format("[RI] clearr Spec Out:%lf [%.1lf])", g_clMandoInspLog[m_nUnit].m_Log_RI_Center_Cr, _Spec.dSpecCenterIntensity[0]);
		g_clMandoInspLog[m_nUnit].iNGCnt++;
		g_clMandoInspLog[m_nUnit].m_bInspRes = false;	//RI
		g_clMandoInspLog[m_nUnit].m_sNGList += szLog;
	}
	if (g_clMandoInspLog[m_nUnit].m_Log_RI_Center_Cb < _Spec.dSpecCenterIntensity[3])
	{
		//g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;//XX
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[RI] CLEARB Spec Out: %lf [%.1lf]"), g_clMandoInspLog[m_nUnit].m_Log_RI_Center_Cb, _Spec.dSpecCenterIntensity[3]);
		AddLog(szLog, 0, m_nUnit, false);
		//theApp.MainDlg->putListLog(szLog);
		g_clMandoInspLog[m_nUnit].sDispNG[g_clMandoInspLog[m_nUnit].iNGCnt].Format("[RI] clearb Spec Out:%lf [%.1lf])", g_clMandoInspLog[m_nUnit].m_Log_RI_Center_Cb, _Spec.dSpecCenterIntensity[3]);
		g_clMandoInspLog[m_nUnit].iNGCnt++;
		g_clMandoInspLog[m_nUnit].m_bInspRes = false;	//RI
		g_clMandoInspLog[m_nUnit].m_sNGList += szLog;
	}
	if (g_clMandoInspLog[m_nUnit].m_Log_RI_Center_B < _Spec.dSpecCenterIntensity[2])
	{
		//g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;//XX
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[RI] BLUE Spec Out: %lf [%.1lf]"), g_clMandoInspLog[m_nUnit].m_Log_RI_Center_B, _Spec.dSpecCenterIntensity[2]);
		AddLog(szLog, 0, m_nUnit, false);
		//theApp.MainDlg->putListLog(szLog);
		g_clMandoInspLog[m_nUnit].sDispNG[g_clMandoInspLog[m_nUnit].iNGCnt].Format("[RI] blue Spec Out:%lf [%.1lf])", g_clMandoInspLog[m_nUnit].m_Log_RI_Center_B, _Spec.dSpecCenterIntensity[2]);
		g_clMandoInspLog[m_nUnit].iNGCnt++;
		g_clMandoInspLog[m_nUnit].m_bInspRes = false;	//RI
		g_clMandoInspLog[m_nUnit].m_sNGList += szLog;
	}
	int regionCount = (int)m_pRelativeIlluminationX->GetInspectionRegionCount();
	for (int i = 0; i < regionCount; i++)
	{
		bool bSpecIn = m_pRelativeIlluminationX->InSpec(i);
		TRelativeIlluminationResultX result = *m_pRelativeIlluminationX->GetInspectionResult(i);

		rt.left = result.rtROI.left * 2;
		rt.top = result.rtROI.top * 2;
		rt.right = result.rtROI.right * 2;
		rt.bottom = result.rtROI.bottom * 2;

		if (result.bPass)
			cvRectangle(cvImgRI, cvPoint(rt.left, rt.top), cvPoint(rt.right, rt.bottom), CV_RGB(0, 255, 0));
		else
			cvRectangle(cvImgRI, cvPoint(rt.left, rt.top), cvPoint(rt.right, rt.bottom), CV_RGB(255, 0, 0));

		/*printf("[%d] %d(%.1f),%d(%.1f),%d(%.1f),%d(%.1f)\n", i, (int)result.dRIRawResult[0], result.dRINormalResult[0],
		(int)result.dRIRawResult[1], result.dRINormalResult[1], (int)result.dRIRawResult[2], result.dRINormalResult[2],
		(int)result.dRIRawResult[3], result.dRINormalResult[3]);*/

		g_clMandoInspLog[m_nUnit].m_Log_RI_RED[i] = result.dRINormalResult[1];
		g_clMandoInspLog[m_nUnit].m_Log_RI_CLEARR[i] = result.dRINormalResult[0];
		g_clMandoInspLog[m_nUnit].m_Log_RI_CLEARB[i] = result.dRINormalResult[3];
		g_clMandoInspLog[m_nUnit].m_Log_RI_BLUE[i] = result.dRINormalResult[2];
	}
		g_clMesCommunication[m_nUnit].m_nMesRICorner[0] = g_clMandoInspLog[m_nUnit].m_Log_RI_CornerVar_R;
		g_clMesCommunication[m_nUnit].m_nMesRICorner[1] = g_clMandoInspLog[m_nUnit].m_Log_RI_CornerVar_Cr;
		g_clMesCommunication[m_nUnit].m_nMesRICorner[2] = g_clMandoInspLog[m_nUnit].m_Log_RI_CornerVar_Cb;
		g_clMesCommunication[m_nUnit].m_nMesRICorner[3] = g_clMandoInspLog[m_nUnit].m_Log_RI_CornerVar_B;


		g_clMesCommunication[m_nUnit].m_nMesSHMRI[0] = g_clMandoInspLog[m_nUnit].m_Log_RI_Center_R;
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[1] = g_clMandoInspLog[m_nUnit].m_Log_RI_Center_Cr;
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[2] = g_clMandoInspLog[m_nUnit].m_Log_RI_Center_Cb;
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[3] = g_clMandoInspLog[m_nUnit].m_Log_RI_Center_B;
	//								
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[4] = g_clMandoInspLog[m_nUnit].m_Log_RI_RED[0];
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[5] = g_clMandoInspLog[m_nUnit].m_Log_RI_CLEARR[0];
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[6] = g_clMandoInspLog[m_nUnit].m_Log_RI_CLEARB[0];
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[7] = g_clMandoInspLog[m_nUnit].m_Log_RI_BLUE[0];
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[8] = g_clMandoInspLog[m_nUnit].m_Log_RI_RED[9];
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[9] = g_clMandoInspLog[m_nUnit].m_Log_RI_CLEARR[9];
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[10] = g_clMandoInspLog[m_nUnit].m_Log_RI_CLEARB[9];
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[11] = g_clMandoInspLog[m_nUnit].m_Log_RI_BLUE[9];
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[12] = g_clMandoInspLog[m_nUnit].m_Log_RI_RED[90];
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[13] = g_clMandoInspLog[m_nUnit].m_Log_RI_CLEARR[90];
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[14] = g_clMandoInspLog[m_nUnit].m_Log_RI_CLEARB[90];
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[15] = g_clMandoInspLog[m_nUnit].m_Log_RI_BLUE[90];
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[16] = g_clMandoInspLog[m_nUnit].m_Log_RI_RED[99];
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[17] = g_clMandoInspLog[m_nUnit].m_Log_RI_CLEARR[99];
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[18] = g_clMandoInspLog[m_nUnit].m_Log_RI_CLEARB[99];
		g_clMesCommunication[m_nUnit].m_nMesSHMRI[19] = g_clMandoInspLog[m_nUnit].m_Log_RI_BLUE[99];

	TCHAR* pszlgitCol[2] = { _T("RelativeIlluminationX_3000k"),  _T("RelativeIlluminationX_5000k") };
	g_SaveLGITLog(m_nUnit, "RI", pszlgitCol[0], m_pRelativeIlluminationX->GetLogHeader(), m_pRelativeIlluminationX->GetLogData());
	//g_SaveLGITLog(m_nUnit, pszlgitCol[0], m_pChartProc->GetLogHeader(), m_pChartProc->GetLogData(), m_pChartProc->GetVersion());
	return nResult;
}
int CPRIFunc_Insp::Inspect_RelativeUniformity(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TRelativeUniformitySpec& _Spec, TDATASPEC& tDataSpec, IplImage *cvImgRU, bool bUse8BitOnly)
{
	int nResult = R_RESULT_PASS;

	std::shared_ptr<CACMISShadingRelativeUniformity> m_pRelativeUniformity = std::make_shared<CACMISShadingRelativeUniformity>();

	//Logging
	std::cout << "[Relative Uniformity] Version = " << m_pRelativeUniformity->GetVersion() << std::endl;


	//Inspection
	if (!m_pRelativeUniformity->Inspect(pBuffer, nImageWidth, nImageHeight, _Spec, tDataSpec.eDataFormat, tDataSpec.eOutMode, tDataSpec.eSensorType, tDataSpec.nBlackLevel, bUse8BitOnly))
	{
		std::cout << "[Relative Uniformity] Inspection Fail! " << std::endl;
		return FALSE;
	}

	//Result 
	TRelativeUniformityResult m_stRelativeUniformityResult;

	m_stRelativeUniformityResult = *m_pRelativeUniformity->GetInspectionResult();

	int roiSize = _Spec.nROISize;
	if (_Spec.dSpecMax < m_stRelativeUniformityResult.dResultMax)
		nResult = R_RESULT_FAIL;

	//Logging
	std::cout << "[Relative Uniformity] Max= " << m_stRelativeUniformityResult.dResultMax << std::endl;
	std::cout << "[Relative Uniformity] Block( " << m_stRelativeUniformityResult.nMaxBlockX << " , " << m_stRelativeUniformityResult.nMaxBlockY << " )";
	std::cout << "X= " << (m_stRelativeUniformityResult.nMaxBlockX)*(_Spec.nROISize) << ", ";
	std::cout << "Y= " << (m_stRelativeUniformityResult.nMaxBlockY)*(_Spec.nROISize) << ", ";
	std::cout << "Width= " << _Spec.nROISize << ", " << "Height= " << _Spec.nROISize << std::endl;
	std::cout << "[Relative Uniformity] Ref Block( " << m_stRelativeUniformityResult.nRefBlockX << " , " << m_stRelativeUniformityResult.nRefBlockY << " )";
	std::cout << "X= " << (m_stRelativeUniformityResult.nRefBlockX)*(_Spec.nROISize) << ", ";
	std::cout << "Y= " << (m_stRelativeUniformityResult.nRefBlockY)*(_Spec.nROISize) << ", ";
	std::cout << "Width= " << _Spec.nROISize << ", " << "Height= " << _Spec.nROISize << std::endl;

	//Graphic
	RECT rect, rectRef;

	rect.left = m_stRelativeUniformityResult.nMaxBlockX * roiSize;
	rect.top = m_stRelativeUniformityResult.nMaxBlockY * roiSize;
	rect.right = rect.left + roiSize;
	rect.bottom = rect.top + roiSize;

	rectRef.left = m_stRelativeUniformityResult.nRefBlockX * roiSize;
	rectRef.top = m_stRelativeUniformityResult.nRefBlockY * roiSize;
	rectRef.right = rectRef.left + roiSize;
	rectRef.bottom = rectRef.top + roiSize;

	cvRectangle(cvImgRU, cvPoint(rect.left, rect.top), cvPoint(rect.right, rect.bottom), CV_LIGHTGREEN);
	cvRectangle(cvImgRU, cvPoint(rectRef.left, rectRef.top), cvPoint(rectRef.right, rectRef.bottom), CV_YELLOW);

	return nResult;
}
int CPRIFunc_Insp::Inspect_ColorSensitivity(const BYTE* pBuffer,  bool bUse8BitOnly)
{
    int nWidth = g_clModelData[m_nUnit].m_nWidth;
    int nHeight = g_clModelData[m_nUnit].m_nHeight;
    TDATASPEC& tDataSpec = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n;

	int nResult = R_RESULT_PASS;
	int i;
    int nResultRI = -1, nResultRU = -1, nResultCS = -1, nResultRI_X;
    char title[100];

    // Image buffers
    std::vector<BYTE> vBmpBuffer(nWidth * nHeight * 3, 0);

    // output image
    //IplImage *cvImgShading = cvCreateImage(cvSize(nWidth, nHeight), 8, 3);
   // cvImgShading->imageData = (char*)vBmpBuffer.data();

    // for display
    //if (bRaw)
    //{
    //    ACMISSoftISP::xMakeBMP(pBuffer, vBmpBuffer.data(), nWidth, nHeight, tDataSpec);
    //}
    //else
    //{
    //   // std::copy(pBuffer, pBuffer + sizeof(BYTE) * nWidth * nHeight * 3, vBmpBuffer.data());
    //}
    // Spec information
    TShadingSpec tShadingSpec;
    memset(&tShadingSpec, 0x00, sizeof(TShadingSpec));
    //----------------------------------------------------------------------
    // Spec - Color Sensitivity
    //----------------------------------------------------------------------

    // Initialize ROI regions and offset values
    RECT rtRoi;
    double dOffset = 0.0;

    SetRect(&rtRoi, 856, 432, 965, 507);

    tShadingSpec.m_stColorSensitivitySpec.tROI.eROIType = ROIType_RECT;
    tShadingSpec.m_stColorSensitivitySpec.tROI.ROICount = 1;
    tShadingSpec.m_stColorSensitivitySpec.tROI.dOffset = &dOffset;
    tShadingSpec.m_stColorSensitivitySpec.tROI.pROIData = &rtRoi;

    tShadingSpec.m_stColorSensitivitySpec.dSpecDevMaxRG =   1.000000;
    tShadingSpec.m_stColorSensitivitySpec.dSpecDevMinRG =   1.000000;
    tShadingSpec.m_stColorSensitivitySpec.dSpecDevMaxBG =   1.000000;
    tShadingSpec.m_stColorSensitivitySpec.dSpecDevMinBG =   1.000000;
    tShadingSpec.m_stColorSensitivitySpec.dSpecDevMaxGrGb = 1.000000;
    tShadingSpec.m_stColorSensitivitySpec.dSpecDevMinGrGb = 1.000000;
    tShadingSpec.m_stColorSensitivitySpec.nTypicalValueType = 0;

    /*nResultCS = Inspect_ColorSensitivity(pBuffer, nWidth, nHeight, tShadingSpec.m_stColorSensitivitySpec, 
        tDataSpec.eDataFormat, tDataSpec.eOutMode, tDataSpec.eSensorType, tDataSpec.nBlackLevel, cvImgShading, bUse8BitOnly);
    std::cout << "nResult Color Sensitivity =" << nResultCS << std::endl;*/

    std::shared_ptr<CACMISShadingColorSensitivity> m_pColorSensitivity = std::make_shared<CACMISShadingColorSensitivity>();

    std::cout << "[Color Sensitivity] Version = " << m_pColorSensitivity->GetVersion() << std::endl;

    //Inspection
    /*if (!m_pColorSensitivity->Inspect(pBuffer, nWidth, nHeight, tShadingSpec.m_stColorSensitivitySpec, 
        tDataSpec.eDataFormat, tDataSpec.eOutMode, tDataSpec.eSensorType, tDataSpec.nBlackLevel, cvImgShading, bUse8BitOnly))
    {
        std::cout << "[Color Sensitivity] Inspection Fail! " << std::endl;
        return FALSE;
    }*/

    //Result
    //std::vector<TColorSensitivityResult> m_stColorSensitivityResult;
    //for (i = 0; i < _Spec.tROI.ROICount; i++)
    //{
    //    m_stColorSensitivityResult.push_back(*m_pColorSensitivity->GetInspectionResult(i));

    //    // Check Color Sensitivity RG
    //    if ((_Spec.dSpecDevMinRG > m_stColorSensitivityResult[i].tAdjustColorRatio.RG) || (_Spec.dSpecDevMaxRG < m_stColorSensitivityResult[i].tAdjustColorRatio.RG))
    //        nResult = R_RESULT_FAIL;
    //    // Check Color Sensitivity BG
    //    if ((_Spec.dSpecDevMinBG > m_stColorSensitivityResult[i].tAdjustColorRatio.BG) || (_Spec.dSpecDevMaxBG < m_stColorSensitivityResult[i].tAdjustColorRatio.BG))
    //        nResult = R_RESULT_FAIL;
    //    // Check Color Sensitivity GrGb
    //    if ((_Spec.dSpecDevMinGrGb > m_stColorSensitivityResult[i].tAdjustColorRatio.GrGb) || (_Spec.dSpecDevMaxGrGb < m_stColorSensitivityResult[i].tAdjustColorRatio.GrGb))
    //        nResult = R_RESULT_FAIL;

    //    //Logging
    //    TColorSensitivityResult* pResult = &m_stColorSensitivityResult[i];
    //    //printf("[Color Sensitivity] RG=%.4f, BG=%.4f, GrGb=%.4f \n", pResult->tColorRatio.RG, pResult->tColorRatio.BG, pResult->tColorRatio.GrGb);
    //    //printf("[Color Sensitivity] R=%.4f, B=%.4f, B=%.4f \n", pResult->tColorRatio.R, pResult->tColorRatio.G, pResult->tColorRatio.B);
    //    //printf("[Color Sensitivity] Gr=%.4f, Gb=%.4f \n", pResult->tColorRatio.Gr, pResult->tColorRatio.Gb);

    //    //Graphic
    //    const RECT* rt = m_pColorSensitivity->GetInspectionROI((EPos)i);
    //    cvRectangle(cvImgRI, cvPoint(rt->left, rt->top), cvPoint(rt->right, rt->bottom), CV_RGB(0, 0, 255));
    //}



   /* if (ImagePath != nullptr && bSaveResultImage == true)
    {
        char filename[100];
        char *tmp = (char *)strrchr(ImagePath, '.');

        if (tmp != nullptr)
        {
            strncpy_s(filename, ImagePath, (int)(tmp - ImagePath));
        }
        else
        {
            strcpy_s(filename, ImagePath);
        }
        strcat_s(filename, "_Shading_result.bmp");
        printf("Saving Result image: %s\n", filename);
        cvSaveImage(filename, cvImgShading);
    }*/

    /*sprintf(title, "Shading%s%s", ImagePath != nullptr ? " - " : "", ImagePath != nullptr ? ImagePath : "");
    cvShowImage(title, cvImgShading);
    cvReleaseImage(&cvImgShading);
    cvWaitKey(0);*/
	//std::shared_ptr<CACMISShadingColorSensitivity> m_pColorSensitivity = std::make_shared<CACMISShadingColorSensitivity>();

	//std::cout << "[Color Sensitivity] Version = " << m_pColorSensitivity->GetVersion() << std::endl;

	////Inspection
	//if (!m_pColorSensitivity->Inspect(pBuffer, nWidth, nHeight, _Spec, tDataSpec.eDataFormat, tDataSpec.eOutMode, tDataSpec.eSensorType, tDataSpec.nBlackLevel, bUse8BitOnly))
	//{
	//	std::cout << "[Color Sensitivity] Inspection Fail! " << std::endl;
	//	return FALSE;
	//}

	////Result
	//std::vector<TColorSensitivityResult> m_stColorSensitivityResult;
	//for (i = 0; i < _Spec.tROI.ROICount; i++)
	//{
	//	m_stColorSensitivityResult.push_back(*m_pColorSensitivity->GetInspectionResult(i));

	//	// Check Color Sensitivity RG
	//	if ((_Spec.dSpecDevMinRG > m_stColorSensitivityResult[i].tAdjustColorRatio.RG) || (_Spec.dSpecDevMaxRG < m_stColorSensitivityResult[i].tAdjustColorRatio.RG))
	//		nResult = R_RESULT_FAIL;
	//	// Check Color Sensitivity BG
	//	if ((_Spec.dSpecDevMinBG > m_stColorSensitivityResult[i].tAdjustColorRatio.BG) || (_Spec.dSpecDevMaxBG < m_stColorSensitivityResult[i].tAdjustColorRatio.BG))
	//		nResult = R_RESULT_FAIL;
	//	// Check Color Sensitivity GrGb
	//	if ((_Spec.dSpecDevMinGrGb > m_stColorSensitivityResult[i].tAdjustColorRatio.GrGb) || (_Spec.dSpecDevMaxGrGb < m_stColorSensitivityResult[i].tAdjustColorRatio.GrGb))
	//		nResult = R_RESULT_FAIL;

	//	//Logging
	//	TColorSensitivityResult* pResult = &m_stColorSensitivityResult[i];
	//	printf("[Color Sensitivity] RG=%.4f, BG=%.4f, GrGb=%.4f \n", pResult->tColorRatio.RG, pResult->tColorRatio.BG, pResult->tColorRatio.GrGb);
	//	printf("[Color Sensitivity] R=%.4f, B=%.4f, B=%.4f \n", pResult->tColorRatio.R, pResult->tColorRatio.G, pResult->tColorRatio.B);
	//	printf("[Color Sensitivity] Gr=%.4f, Gb=%.4f \n", pResult->tColorRatio.Gr, pResult->tColorRatio.Gb);

	//	//Graphic
	//	const RECT* rt = m_pColorSensitivity->GetInspectionROI((EPos)i);
	//	cvRectangle(cvImgRI, cvPoint(rt->left, rt->top), cvPoint(rt->right, rt->bottom), CV_RGB(0, 0, 255));
	//}

	return nResult;
}




//-----------------------------------------------------------------------------
//
//	UNIFORMITY 검사 5000K
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_Uniformity(BYTE* pBuffer, int index, bool bAutoMode)
{
	//Color Uniformity 5000k 검사
	bool bRes = false;
	int i = 0;
	int nResult = R_RESULT_PASS;
	TCHAR szLog[SIZE_OF_1K];

	int nWidth = g_clModelData[m_nUnit].m_nWidth;
	int nHeight = g_clModelData[m_nUnit].m_nHeight;
	TDATASPEC& tDataSpec = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n;

	int nuiIndex = 0;
	//5000k 검사
	_stprintf_s(szLog, SIZE_OF_1K, _T("Color Uniformity 5000K Image Test)"));
	AddLog(szLog, 0, m_nUnit);
	nuiIndex = 0;

	TColorUniformitySpecN tColorUniformitySpec;
	memset(&tColorUniformitySpec, 0x00, sizeof(TColorUniformitySpec));

	ACMISSoftISP::xMakeBMP(pBuffer, (byte*)g_clLaonGrabberWrapper[m_nUnit].m_pTestBuffer,
		g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight, g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n);

	Mat cvImgColorUniformity = Mat(g_clModelData[m_nUnit].m_nHeight, g_clModelData[m_nUnit].m_nWidth, CV_8UC3);
	cvImgColorUniformity.data = g_clLaonGrabberWrapper[m_nUnit].m_pTestBuffer;
	//----------------------------------------------------------------------
	// Spec - Color Uniformity
	//----------------------------------------------------------------------
	int specCount = 0;
	tColorUniformitySpec.nTypicalValueType = TypicalValue_Mean;
	//tColorUniformitySpec.nColorSpaceType = 0;
	tColorUniformitySpec.nUseOverlap = 1;
	//
	tColorUniformitySpec.nGridSizeX = g_clModelData[m_nUnit].m_UniformSpec[0];// nWidth / 10;      //ui로
	tColorUniformitySpec.nGridSizeY = g_clModelData[m_nUnit].m_UniformSpec[1];//nHeight / 10;      //ui로
	tColorUniformitySpec.nColorSpaceType = g_clModelData[m_nUnit].m_UniformSpec[2];//ColorSpace_RGB;
	tColorUniformitySpec.nMaxDiffType = g_clModelData[m_nUnit].m_UniformSpec[3];//0;                //ui로
	//
	tColorUniformitySpec.dSpecMaxDiffRG = g_clModelData[m_nUnit].m_UniformSpec[4];
	tColorUniformitySpec.dSpecMaxDiffBG = g_clModelData[m_nUnit].m_UniformSpec[5];
	tColorUniformitySpec.dSpecMaxDiffRB = g_clModelData[m_nUnit].m_UniformSpec[6];
	tColorUniformitySpec.dSpecMaxDiffGrGb = g_clModelData[m_nUnit].m_UniformSpec[7];
	//
	tColorUniformitySpec.dSpecMinDiffRG = g_clModelData[m_nUnit].m_UniformSpec[8];
	tColorUniformitySpec.dSpecMinDiffBG = g_clModelData[m_nUnit].m_UniformSpec[9];
	tColorUniformitySpec.dSpecMinDiffRB = g_clModelData[m_nUnit].m_UniformSpec[10];
	tColorUniformitySpec.dSpecMinDiffGrGb = g_clModelData[m_nUnit].m_UniformSpec[11];



	double mColorUniformityValue = 0.0;
	double mColorUniformitySpec = 0.0;
	bool UfCheckFinal = true;
	std::shared_ptr< CACMISShadingColorUniformity > m_pColorUniformity = std::make_shared<CACMISShadingColorUniformity >();
//#if (____MACHINE_NAME ==  MODEL_FOV_80)
//	int nBlackLevel = 240;
//#else
//	int nBlackLevel = 64;
//#endif
	int nBlackLevel = 64;

	if (index == LOW_LEVEL_RAW)
	{
		nBlackLevel = 0;
	}
	bool result = m_pColorUniformity->Inspect(pBuffer, nWidth, nHeight, tColorUniformitySpec,
		tDataSpec.eDataFormat, tDataSpec.eOutMode, tDataSpec.eSensorType, nBlackLevel, 0, 0);

	//for (int i = 0; i < m_pColorUniformity->GetInspectionRegionCount(); i++)
	//{
	//	//const TColorUniformityResult* pResult = m_pColorUniformity->GetInspectionResult(i);
	//	const TColorUniformityResultN* m_stColorUniformityResult = m_pColorUniformity->GetInspectionResult(i);
	//}
	//
	//const TColorUniformityResultN *pResult = m_pColorUniformity->GetInspectionResult(0);


	//TColorUniformityResultN m_stColorUniformityResult;
	//m_stColorUniformityResult = m_pColorUniformity->GetInspectionMaxResult(); // 결과 값

	TColorUniformityResultN m_stColorUniformityResult = m_pColorUniformity->GetInspectionMaxResult();
	
	//const TColorShadingResult* m_stColorShadingResult = m_pAlgorithmShading->GetInspectionResult();
	//const TColorUniformityResultN pResult* = GetInspectionMaxResult()
	double mIrMin = 0.0;
	double mIrMax = 0.0;

	//화면에 표시
	double MaxDeltaRG =  m_stColorUniformityResult.dMaxEachDiffRG;
	double MaxDeltaBG = m_stColorUniformityResult.dMaxEachDiffBG;
	double MaxDeltaRB = m_stColorUniformityResult.dMaxEachDiffRB;
	double MaxDeltaGrGb = m_stColorUniformityResult.dMaxEachDiffGrGb;
	double MaxSum = m_stColorUniformityResult.dMaxTotalDiffRG + m_stColorUniformityResult.dMaxTotalDiffRB + m_stColorUniformityResult.dMaxTotalDiffBG + m_stColorUniformityResult.dMaxTotalDiffGrGb;
	double MinDeltaRG = m_stColorUniformityResult.dMinEachDiffRG;
	double MinDeltaBG = m_stColorUniformityResult.dMinEachDiffBG;
	double MinDeltaRB = m_stColorUniformityResult.dMinEachDiffRB;
	double MinDeltaGrGb = m_stColorUniformityResult.dMinEachDiffGrGb;
	double MinSum = m_stColorUniformityResult.dMinTotalDiffRG + m_stColorUniformityResult.dMinTotalDiffRB + m_stColorUniformityResult.dMinTotalDiffBG + m_stColorUniformityResult.dMinTotalDiffGrGb;

	g_clMandoInspLog[m_nUnit].m_Uniformity[0] = MaxDeltaRG;
	g_clMandoInspLog[m_nUnit].m_Uniformity[1] = MaxDeltaBG;
	g_clMandoInspLog[m_nUnit].m_Uniformity[2] = MaxDeltaRB;
	g_clMandoInspLog[m_nUnit].m_Uniformity[3] = MaxDeltaGrGb;
	g_clMandoInspLog[m_nUnit].m_Uniformity[4] = MaxSum;
	g_clMandoInspLog[m_nUnit].m_Uniformity[5] = MinDeltaRG;
	g_clMandoInspLog[m_nUnit].m_Uniformity[6] = MinDeltaBG;
	g_clMandoInspLog[m_nUnit].m_Uniformity[7] = MinDeltaRB;
	g_clMandoInspLog[m_nUnit].m_Uniformity[8] = MinDeltaGrGb;
	g_clMandoInspLog[m_nUnit].m_Uniformity[9] = MinSum;


	g_clMesCommunication[m_nUnit].m_nMesColorUniformity[0] = MinSum;
	g_clMesCommunication[m_nUnit].m_nMesColorUniformity[1] = MaxSum;		//양불 o 기존
	g_clMesCommunication[m_nUnit].m_nMesColorUniformity[2] = MinDeltaRG;
	g_clMesCommunication[m_nUnit].m_nMesColorUniformity[3] = MaxDeltaRG;	//양불 o 추가 240130
	g_clMesCommunication[m_nUnit].m_nMesColorUniformity[4] = MinDeltaBG;
	g_clMesCommunication[m_nUnit].m_nMesColorUniformity[5] = MaxDeltaBG;	//양불 o 추가 240130
	g_clMesCommunication[m_nUnit].m_nMesColorUniformity[6] = MinDeltaGrGb;
	g_clMesCommunication[m_nUnit].m_nMesColorUniformity[7] = MaxDeltaGrGb;	//양불 o 추가 240130
	for (i = 0; i < 8; i++)
	{
		g_clMesCommunication[m_nUnit].m_nMesColorUniformityResult[i] = 1;
	}

	mColorUniformityValue = MinSum;
	mColorUniformitySpec = g_clModelData[m_nUnit].m_UniformSpec[12];
	_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MinSum :%.3lf"), mColorUniformityValue);
	AddLog(szLog, 0, m_nUnit);
	/*if (mColorUniformityValue < mColorUniformitySpec)
	{
		UfCheckFinal = false;
		g_clMesCommunication[m_nUnit].m_nMesColorUniformityResult[0] = 0;
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MinSum Spec Out:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);

		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [Uniformity MinSum NG]");

		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG Uniformity MinSum:%3lf [%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MinSum Spec In:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);
	}*/
	mColorUniformityValue = g_clMesCommunication[m_nUnit].m_nMesColorUniformity[1];// MaxSum;
	mColorUniformitySpec = (_ttof(EEpromVerifyData.vMaxData[23]));	//[CU] Delta SumMax//g_clModelData[m_nUnit].m_UniformSpec[13];

	if (mColorUniformityValue > mColorUniformitySpec)
	{
		UfCheckFinal = false;
		g_clMesCommunication[m_nUnit].m_nMesColorUniformityResult[1] = 0;
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;//XX
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MaxSum Spec Out:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);

		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [Uniformity MaxSum NG]");

		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG Uniformity MaxSum:%3lf [%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MaxSum Spec In:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);
	}
	//
	mColorUniformityValue = g_clMesCommunication[m_nUnit].m_nMesColorUniformity[3];//MaxDeltaRG;
	mColorUniformitySpec = (_ttof(EEpromVerifyData.vMaxData[24])); //[CU] Delta RGMax//tColorUniformitySpec.dSpecMaxDiffRG;
	if (mColorUniformityValue > mColorUniformitySpec)
	{
		UfCheckFinal = false;
		g_clMesCommunication[m_nUnit].m_nMesColorUniformityResult[3] = 0;
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;//XX
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MaxRG Spec Out:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);

		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [Uniformity MaxRG NG]");

		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG Uniformity MaxRG:%3lf [%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MaxRG Spec In:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);
	}
	mColorUniformityValue = g_clMesCommunication[m_nUnit].m_nMesColorUniformity[5];//MaxDeltaBG;
	mColorUniformitySpec = (_ttof(EEpromVerifyData.vMaxData[25])); //[CU] Delta BGMax	//mColorUniformitySpec = tColorUniformitySpec.dSpecMaxDiffBG;
	if (mColorUniformityValue > mColorUniformitySpec)
	{
		UfCheckFinal = false;
		g_clMesCommunication[m_nUnit].m_nMesColorUniformityResult[5] = 0;
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;//XX
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MaxBG Spec Out:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);

		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [Uniformity MaxBG NG]");

		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG Uniformity MaxBG:%3lf [%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MaxBG Spec In:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);
	}
	
	mColorUniformityValue = g_clMesCommunication[m_nUnit].m_nMesColorUniformity[7];//MaxDeltaGrGb;
	mColorUniformitySpec = (_ttof(EEpromVerifyData.vMaxData[26])); //[CU] Delta GrGbMax	//mColorUniformitySpec = tColorUniformitySpec.dSpecMaxDiffGrGb;
	if (mColorUniformityValue > mColorUniformitySpec)
	{
		UfCheckFinal = false;
		g_clMesCommunication[m_nUnit].m_nMesColorUniformityResult[7] = 0;
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;//XX
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MaxGrGb Spec Out:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);

		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [Uniformity MaxGrGb NG]");

		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG Uniformity MaxGrGb:%3lf [%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MaxGrGb Spec In:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);
	}
	mColorUniformityValue = MaxDeltaRB;
	mColorUniformitySpec = tColorUniformitySpec.dSpecMaxDiffRB;
	_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MaxRB :%.3lf"), mColorUniformityValue);
	AddLog(szLog, 0, m_nUnit);
	/*if (mColorUniformityValue > mColorUniformitySpec)
	{
	UfCheckFinal = false;
	_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MaxRB Spec Out:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
	AddLog(szLog, 0, m_nUnit);

	g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [Uniformity MaxRB NG]");

	if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
	{
	g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG Uniformity MaxRB:%3lf [%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
	g_clMandoInspLog[m_nUnit].m_nNGCnt++;
	}
	}
	else
	{
	_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MaxRB Spec In:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
	AddLog(szLog, 0, m_nUnit);
	}*/

	mColorUniformityValue = MinDeltaRG;
	mColorUniformitySpec = tColorUniformitySpec.dSpecMinDiffRG;
	_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MinRG :%.3lf"), mColorUniformityValue);
	AddLog(szLog, 0, m_nUnit);
	/*if (mColorUniformityValue < mColorUniformitySpec)
	{
		UfCheckFinal = false;
		g_clMesCommunication[m_nUnit].m_nMesColorUniformityResult[2] = 0;
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MinRG Spec Out:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);

		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [Uniformity MinRG NG]");

		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG Uniformity MinRG:%3lf [%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MinRG Spec In:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);
	}*/
	mColorUniformityValue = MinDeltaBG;
	mColorUniformitySpec = tColorUniformitySpec.dSpecMinDiffBG;
	_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MinBG :%.3lf"), mColorUniformityValue);
	AddLog(szLog, 0, m_nUnit);
	/*if (mColorUniformityValue < mColorUniformitySpec)
	{
		UfCheckFinal = false;
		g_clMesCommunication[m_nUnit].m_nMesColorUniformityResult[4] = 0;
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MinBG Spec Out:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);

		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [Uniformity MinBG NG]");

		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG Uniformity MinBG:%3lf [%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MinBG Spec In:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);
	}*/
	mColorUniformityValue = MinDeltaRB;
	mColorUniformitySpec = tColorUniformitySpec.dSpecMinDiffRB;
	_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MinRB :%.3lf"), mColorUniformityValue);
	AddLog(szLog, 0, m_nUnit);

	/*if (mColorUniformityValue < mColorUniformitySpec)
	{
		UfCheckFinal = false;
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MinRB Spec Out:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);

		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [Uniformity MinRB NG]");

		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG Uniformity MinRB:%3lf [%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MinRB Spec In:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);
	}*/
	mColorUniformityValue = MinDeltaGrGb;
	mColorUniformitySpec = tColorUniformitySpec.dSpecMinDiffGrGb;
	_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MinGrGb :%.3lf"), mColorUniformityValue);
	AddLog(szLog, 0, m_nUnit);

	/*if (mColorUniformityValue < mColorUniformitySpec)
	{
		UfCheckFinal = false;
		
		g_clMesCommunication[m_nUnit].m_nMesColorUniformityResult[6] = 0;
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MinGrGb Spec Out:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);

		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [Uniformity MinGrGb NG]");

		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG Uniformity MinGrGb:%3lf [%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("Uniformity MinGrGb Spec In:%.3lf[%.3lf]"), mColorUniformityValue, mColorUniformitySpec);
		AddLog(szLog, 0, m_nUnit);
	}*/

	g_SaveLGITLog(m_nUnit, _T("Color Uniformity_5000k"), m_pColorUniformity->GetLogHeader(), m_pColorUniformity->GetLogData(), m_pColorUniformity->GetVersion());

	if (UfCheckFinal == false)
	{
		g_clTaskWork[m_nUnit].m_bOutputCheck[7] = false;		//CU
	}
	return UfCheckFinal;
}



CString CPRIFunc_Insp::SetDir_Check(CString sPath)
{
	CString sRtn = _T(""), FolderName = _T("");
	CFileFind finder;
	BOOL IsFind;

	SYSTEMTIME time;
	::GetLocalTime(&time);

	FolderName.Format(_T("%s\\%04d%02d"), (TCHAR*)(LPCTSTR)sPath, time.wYear, time.wMonth);
	IsFind = finder.FindFile(FolderName);
	if (!IsFind)
	{
		CreateDirectory(FolderName, NULL);
	}

	sRtn.Format(_T("%s\\%04d%02d\\%02d"), (TCHAR*)(LPCTSTR)sPath, time.wYear, time.wMonth, time.wDay);
	IsFind = finder.FindFile(sRtn);
	if (!IsFind)
	{
		CreateDirectory(sRtn, NULL);
	}

	sRtn.Format(_T("%s\\%04d%02d\\%02d\\"), (TCHAR*)(LPCTSTR)sPath, time.wYear, time.wMonth, time.wDay);

	return sRtn;
}


//-----------------------------------------------------------------------------
//
//	이물(stain) 검사
//
//-----------------------------------------------------------------------------

bool CPRIFunc_Insp::func_Insp_Stain(BYTE* img, bool bAutoMode, int mRCount, bool bUse8BitOnly)
{
    int nBlackLevel = 0;
    int nWidth = g_clModelData[m_nUnit].m_nWidth;
    int nHeight = g_clModelData[m_nUnit].m_nHeight;
	int nResult1 = 0;
	int nResult2 = 0;
	int nResult3 = 0;
    TDATASPEC& tDataSpec = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n;
    //
   // IplImage *cvStainImg = cvCreateImage(cvSize(nWidth, nHeight), 8, 3); // bmp for display

	

	g_clMesCommunication[m_nUnit].m_nMesBlemishResult[0] = 1;
	g_clMesCommunication[m_nUnit].m_nMesBlemishResult[1] = 1;
	g_clMesCommunication[m_nUnit].m_nMesBlemishResult[2] = 1;
    //
	//nResult1 = BlackSpotInsp((BYTE*)img, nWidth, nHeight, tDataSpec, cvStainImg, mRCount);

	/*nResult1 = LCBInsp((BYTE*)img,  mRCount);

	nResult2 = Blemish_YmeanInsp((BYTE*)img); 

	nResult3 = FDFInsp((BYTE*)img);*/
	//



    return true;
}


int CPRIFunc_Insp::BlackSpotInsp(BYTE* bsimg, int nWidth, int nHeight, TDATASPEC& tDataSpec, IplImage* _timg, int mRetryCount)
{
    CString szLog;
    int nBlackLevel = 0;
    TBlackSpotContrastN tBlackSpotSpec;
    TCircleSpecN tStainSpec;

	Mat cvImgBlackSpot = Mat(g_clModelData[m_nUnit].m_nHeight, g_clModelData[m_nUnit].m_nWidth, CV_8UC3);
	ACMISSoftISP::xMakeBMP(bsimg, (byte*)cvImgBlackSpot.data,
		g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight, g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n);


    int specCount = 0;
    tBlackSpotSpec.nBlockWidth = g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//0;32;
    tBlackSpotSpec.nBlockHeight = (int)g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//32;
    tBlackSpotSpec.nClusterSize = (int)g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//5;
    tBlackSpotSpec.nDefectInCluster = (int)g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//5;
    tBlackSpotSpec.dDefectRatio = g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//0.45000;
    tBlackSpotSpec.nMaxSingleDefectNum = (int)g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//100000;	// noise image
    //
    tBlackSpotSpec.tCircleSpec.bEnableCircle = (bool)g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//false;
    tBlackSpotSpec.tCircleSpec.nPosOffsetX = (int)g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//5;
    tBlackSpotSpec.tCircleSpec.nPosOffsetY = (int)g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//5;
    tBlackSpotSpec.tCircleSpec.dRadiusRatioX = g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//0.45;
    tBlackSpotSpec.tCircleSpec.dRadiusRatioY = g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//0.45;
    tBlackSpotSpec.tCircleSpec.dThresholdRatio = g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//0.5;
    tBlackSpotSpec.tCircleSpec.dROIRange = g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//0.5;
    tBlackSpotSpec.tCircleSpec.nUsedFixedCircle = (int)g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//0;
    //
    tBlackSpotSpec.tMultiCircleSpec.bEnableMultiCircle = (int)g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//0;
    tBlackSpotSpec.tMultiCircleSpec.dZoneSizeRatio[0] = g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//0.2;
    tBlackSpotSpec.tMultiCircleSpec.dZoneSizeRatio[1] = g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//0.4;
    tBlackSpotSpec.tMultiCircleSpec.dZoneSizeRatio[2] = g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//0.52;
    tBlackSpotSpec.tMultiCircleSpec.dThreshold[0] = g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//0.45;
    tBlackSpotSpec.tMultiCircleSpec.dThreshold[1] = g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//0.45;
    tBlackSpotSpec.tMultiCircleSpec.dThreshold[2] = g_clModelData[m_nUnit].m_BlemishSpec[specCount++];//0.8;
    tBlackSpotSpec.tMultiCircleSpec.nBlobSize[0] = 0;//0;
    tBlackSpotSpec.tMultiCircleSpec.nBlobSize[1] = 0;//0;
    tBlackSpotSpec.tMultiCircleSpec.nBlobSize[2] = 0;//0;

    int nResult = R_RESULT_PASS;
    std::shared_ptr<CACMISImageBlackSpotContrastCommon> pInspectBlackSpot = std::make_shared<CACMISImageBlackSpotContrastCommon>();

    // inspection
    int nDefectCount = pInspectBlackSpot->Inspect((BYTE*)bsimg, nWidth, nHeight, tBlackSpotSpec, tDataSpec.eDataFormat, tDataSpec.eOutMode, tDataSpec.eSensorType, nBlackLevel,0,0);

    // logging
    //std::cout << "[BlackSpot] Version: " << pInspectBlackSpot->GetVersion() << std::endl;
    //std::cout << "[BlackSpot] DefectCount=" << nDefectCount << std::endl;
    //std::cout << "[BlackSpot] SingleDefectCount=" << pInspectBlackSpot->GetSingleDefectCount() << std::endl;
    //std::cout << "[BlackSpot] BlobCount=" << pInspectBlackSpot->GetDefectBlobCount() << std::endl;
	int BlackSpotBlobCount = pInspectBlackSpot->GetDefectBlobCount();
	
    szLog.Format("[BlackSpot] BlackSpot %s", pInspectBlackSpot->GetVersion());
    AddLog(szLog, 1, m_nUnit, false);
    szLog.Format("[BlackSpot] DefectCount %d", nDefectCount);
    AddLog(szLog, 1, m_nUnit, false);
    szLog.Format("[BlackSpot] SingleDefectCount %d", pInspectBlackSpot->GetSingleDefectCount());
    AddLog(szLog, 1, m_nUnit, false);
    szLog.Format("[BlackSpot] BlobCount %d", BlackSpotBlobCount);
    AddLog(szLog, 1, m_nUnit, false);
   
	if (mRetryCount == 0 && BlackSpotBlobCount > 0)
	{
		szLog.Format("[BlackSpot] Retry");
		AddLog(szLog, 1, m_nUnit, false);
		return BlackSpotBlobCount;
	}
    g_clMandoInspLog[m_nUnit].m_LogBlemishBlackSpot = BlackSpotBlobCount;

	g_clMesCommunication[m_nUnit].m_nMesBlemish[0] = g_clMandoInspLog[m_nUnit].m_LogBlemishBlackSpot;
	//
	g_clMandoInspLog[m_nUnit].m_LogBlemishBlackSpotMaxCenter = pInspectBlackSpot->GetMaxDefectResult(EIMAGEREGION_CENTER)->dValue;

	//g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[0] = pInspectBlackSpot->GetMaxDefectResult(EIMAGEREGION_CENTER)->dValue;
	
	
	//
	if (g_clMesCommunication[m_nUnit].m_nMesBlemish[0] > 0)
	{
		g_clTaskWork[m_nUnit].m_bOutputCheck[3] = false;	//STAIN BLACKSPOT
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;	//XX
		g_clMesCommunication[m_nUnit].m_nMesBlemishResult[0] = 0;
	}
	else
	{
		g_clMesCommunication[m_nUnit].m_nMesBlemishResult[0] = 1;
	}
	CvFont cvfont;
	CvPoint pt;
	int scale = (nWidth > 640 ? 1 : 2);
	double nFontSize = 1 / scale;
	//CString sTemp;
	char strTmp[1024];
	cvInitFont(&cvfont, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_NORMAL, nFontSize, nFontSize, 0, 1, 10);
	sprintf_s(strTmp, "BlackSpot BlobCount : %d", BlackSpotBlobCount);
	pt.x = 50;
	pt.y = 50;
	putText(cvImgBlackSpot, strTmp, pt, 0, 1.5, Scalar(10, 10, 10) , 3);
    if (pInspectBlackSpot->GetSingleDefectCount() > tBlackSpotSpec.nMaxSingleDefectNum) 
    {
        nResult = R_FAIL_NOISE;
    }

	double dFactorX = 0.0;
	double dFactorY = 0.0;

	dFactorX = ((double)g_clModelData[m_nUnit].DefectSizeX / (double)g_clModelData[m_nUnit].m_nWidth);
	dFactorY = ((double)g_clModelData[m_nUnit].DefectSizeY / (double)g_clModelData[m_nUnit].m_nHeight);

	
    if (BlackSpotBlobCount > 0)
    {
		CRect rcReduceBox;
		g_clMesCommunication[m_nUnit].m_sBlackSpot.Format(_T("FAIL"));
        nResult = R_FAIL_BLACK_SPOT; 
		g_clMandoInspLog[m_nUnit].m_bInspRes = false;
		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [STAIN BLACKSPOT NG]");

		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG [LCB BLOBCOUNT:%d]"), BlackSpotBlobCount);
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}

		MgraColor(M_DEFAULT, M_COLOR_BLUE);
		for (int i = 0; i < BlackSpotBlobCount; i++)
		{
			const RECT* rt = pInspectBlackSpot->GetDefectBlobRect(i);
			//cvRectangle(cvImgBlackSpot, cvPoint(rt->left, rt->top), cvPoint(rt->right, rt->bottom), CV_RGB(255, 0, 0), 2);
			rectangle(cvImgBlackSpot, cvPoint(rt->left, rt->top), cvPoint(rt->right, rt->bottom), CV_RGB(255, 0, 0), 2);
			g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, rt->left, rt->top, rt->right, rt->bottom, M_COLOR_BLUE, 1, FALSE);

			rcReduceBox.left = (int)(rt->left	* dFactorX + 0.5);
			rcReduceBox.top = (int)(rt->top		* dFactorY + 0.5);
			rcReduceBox.right = (int)(rt->right	* dFactorX + 0.5);
			rcReduceBox.bottom = (int)(rt->bottom	* dFactorY + 0.5);

			MgraRect(M_DEFAULT, g_clVision.MilDefectOverlayImage[m_nUnit], rcReduceBox.left, rcReduceBox.top, rcReduceBox.right, rcReduceBox.bottom);
		}
	}
	else
	{
		g_clMesCommunication[m_nUnit].m_sBlackSpot.Format(_T("PASS"));
	}
    if (nResult)
    {
        

        const TDefectResult* pMaxResult = pInspectBlackSpot->GetMaxDefectResult();

        int crossSize = 20;

		line(cvImgBlackSpot, cvPoint(pMaxResult->ptPos.x - crossSize, pMaxResult->ptPos.y - crossSize),cvPoint(pMaxResult->ptPos.x + crossSize, pMaxResult->ptPos.y + crossSize), CV_RGB(255, 0, 0));
		line(cvImgBlackSpot, cvPoint(pMaxResult->ptPos.x + crossSize, pMaxResult->ptPos.y - crossSize),cvPoint(pMaxResult->ptPos.x - crossSize, pMaxResult->ptPos.y + crossSize), CV_RGB(255, 0, 0));

        if (tBlackSpotSpec.tCircleSpec.bEnableCircle)
        {
            int ocx = (int)pMaxResult->dContrastMaxR;
            int ocy = (int)pMaxResult->dContrastMaxGb;
            int radx = (int)pMaxResult->dContrastMaxGr;
            int rady = (int)pMaxResult->dContrastMaxB;

            int nZone_X = (int)(radx * tBlackSpotSpec.tCircleSpec.dRadiusRatioX);
            int nZone_Y = (int)(rady * tBlackSpotSpec.tCircleSpec.dRadiusRatioY);


           // std::cout << "[BlackSpot] ocx=" << ocx << "ocy = " << ocy << "radx = " << nZone_X << "rady = " << nZone_Y << std::endl;
            //std::cout << "[BlackSpot] posx=" << pMaxResult->ptPos.x << "poxy = " << pMaxResult->ptPos.y << std::endl;

			ellipse(cvImgBlackSpot, cvPoint(ocx, ocy), cvSize(nZone_X, nZone_Y), 0, 0, 360, CV_RGB(0, 255, 255));
        }

        if (tBlackSpotSpec.tMultiCircleSpec.bEnableMultiCircle)
        {
            double dRadYRatio = 1.0;
            if (tBlackSpotSpec.tCircleSpec.nUsedFixedCircle)
            {
                dRadYRatio = tBlackSpotSpec.tCircleSpec.dRadiusRatioY / tBlackSpotSpec.tCircleSpec.dRadiusRatioX;
            }

            int ocx = (int)pMaxResult->dContrastMaxR;
            int ocy = (int)pMaxResult->dContrastMaxGb;
            int radx = (int)pMaxResult->dContrastMaxGr;
            int rady = (int)pMaxResult->dContrastMaxB;

            int nZoneA_X = (int)(radx * tBlackSpotSpec.tMultiCircleSpec.dZoneSizeRatio[0]);
            int nZoneA_Y = (int)(rady * tBlackSpotSpec.tMultiCircleSpec.dZoneSizeRatio[0] * dRadYRatio);
            int nZoneB_X = (int)(radx * tBlackSpotSpec.tMultiCircleSpec.dZoneSizeRatio[1]);
            int nZoneB_Y = (int)(rady * tBlackSpotSpec.tMultiCircleSpec.dZoneSizeRatio[1] * dRadYRatio);
            int nZoneC_X = (int)(radx * tBlackSpotSpec.tMultiCircleSpec.dZoneSizeRatio[2]);
            int nZoneC_Y = (int)(rady * tBlackSpotSpec.tMultiCircleSpec.dZoneSizeRatio[2] * dRadYRatio);

			ellipse(cvImgBlackSpot, cvPoint(ocx, ocy), cvSize(nZoneA_X, nZoneA_Y), 0, 0, 360, CV_RGB(0, 255, 255));
			ellipse(cvImgBlackSpot, cvPoint(ocx, ocy), cvSize(nZoneB_X, nZoneB_Y), 0, 0, 360, CV_RGB(0, 255, 255));
			ellipse(cvImgBlackSpot, cvPoint(ocx, ocy), cvSize(nZoneC_X, nZoneC_Y), 0, 0, 360, CV_RGB(0, 255, 255));

        }

        if ((tBlackSpotSpec.tMultiCircleSpec.bEnableMultiCircle || tBlackSpotSpec.tCircleSpec.bEnableCircle) && tBlackSpotSpec.tCircleSpec.nUsedFixedCircle)
        {
            RECT rtRefEdge;
            RECT rtCenter;
            //oc threshold test roi - top
            rtRefEdge.left = max(nWidth / 2 - 100 / 2, 0);
            rtRefEdge.top = (LONG)(0.1 * nHeight / 2);
            rtRefEdge.right = min(rtRefEdge.left + 100 - 1, (LONG)nWidth - 1);
            rtRefEdge.bottom = min(rtRefEdge.top + 100 - 1, (LONG)nHeight - 1);

            //oc threshold test roi - center
            rtCenter.left = rtRefEdge.left;
            rtCenter.top = max(nHeight / 2 - 100 / 2, 0);
            rtCenter.right = rtRefEdge.right;
            rtCenter.bottom = min(nHeight / 2 + 100 / 2 - 1, nHeight - 1);

			rectangle(cvImgBlackSpot, cvPoint(rtRefEdge.left, rtRefEdge.top), cvPoint(rtRefEdge.right, rtRefEdge.bottom), CV_RGB(255, 86, 12), 2);
			rectangle(cvImgBlackSpot, cvPoint(rtCenter.left, rtCenter.top), cvPoint(rtCenter.right, rtCenter.bottom), CV_RGB(255, 86, 12), 2);
        }
    }
	if (g_clModelData[m_nUnit].m_nNgImageSaveUse == 1)
	{
		if (BlackSpotBlobCount > 0)
		{
			g_clLaonGrabberWrapper[m_nUnit].JpgMatSave(cvImgBlackSpot, 0);
		}
	}
	else
	{
		g_clLaonGrabberWrapper[m_nUnit].JpgMatSave(cvImgBlackSpot, 0);
	}
    g_SaveLGITLog(m_nUnit, "BlackSpot", pInspectBlackSpot->GetLogHeader(), pInspectBlackSpot->GetLogData(), pInspectBlackSpot->GetVersion());
    //cvSaveImage("D:\\cvImgBlackSpot.bmp", cvImgBlackSpot);
    return BlackSpotBlobCount;
}

int CPRIFunc_Insp::LCBInsp(BYTE* img, int mRetryCount, bool bAutoMode)
{
    int nResult = R_RESULT_PASS;
    int nResultLCB = 0;
    
	int nWidth = g_clModelData[m_nUnit].m_nWidth;
	int nHeight = g_clModelData[m_nUnit].m_nHeight;
	TDATASPEC& tDataSpec = g_clLaonGrabberWrapper[m_nUnit].dBlemish_Tdataspec;
	bool bUse8BitOnly = false;

	if (g_clModelData[m_nUnit].m_nBlemish8BitUse == 1)
	{
		bUse8BitOnly = true;
	}





	TCHAR szLog[SIZE_OF_1K];
    TLCBSpecN tStainSpec;
    memset(&tStainSpec, 0x00, sizeof(TLCBSpecN));
    int specCount = 0;
	//IplImage *bmpImg = cvCreateImage(cvSize(nWidth, nHeight), 8, 3); // bmp for display
	//bmpImg->imageData = (char*)g_clLaonGrabberWrapper[m_nUnit].m_pFrameBMPBuffer;

	ACMISSoftISP::xMakeBMP(img, (byte*)g_clLaonGrabberWrapper[m_nUnit].m_pTestBuffer,
		g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight, g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n);
	Mat bmpImg = Mat(g_clModelData[m_nUnit].m_nHeight, g_clModelData[m_nUnit].m_nWidth, CV_8UC3);
	bmpImg.data = g_clLaonGrabberWrapper[m_nUnit].m_pTestBuffer;
    //----------------------------------------------------------------------
    // Spec - LCB
    //----------------------------------------------------------------------
    tStainSpec.dCenterThreshold = g_clModelData[m_nUnit].m_LcbSpec[specCount++];// 35.0;
    tStainSpec.dEdgeThreshold = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//13.5;
    tStainSpec.dCornerThreshold = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//40.5;
    tStainSpec.nMaxSingleDefectNum = (int)g_clModelData[m_nUnit].m_LcbSpec[specCount++];//50000;
    tStainSpec.nMinDefectWidthHeight = (int)g_clModelData[m_nUnit].m_LcbSpec[specCount++];//12;
	tStainSpec.dCenterMaxR = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//9;
	tStainSpec.dCenterMaxGr = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0;
	tStainSpec.dCenterMaxGb = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0;
	tStainSpec.dCenterMaxB = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//9;
	tStainSpec.dEdgeMaxR = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0;
	tStainSpec.dEdgeMaxGr = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0;
	tStainSpec.dEdgeMaxGb = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0;
	tStainSpec.dEdgeMaxB = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0;
	tStainSpec.dCornerMaxR = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0;
	tStainSpec.dCornerMaxGr = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0;
	tStainSpec.dCornerMaxGb = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0;
	tStainSpec.dCornerMaxB = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0;
    tStainSpec.tCircleSpec.bEnableCircle = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//true;
    tStainSpec.tCircleSpec.nPosOffsetX = (int)g_clModelData[m_nUnit].m_LcbSpec[specCount++];//5;
    tStainSpec.tCircleSpec.nPosOffsetY = (int)g_clModelData[m_nUnit].m_LcbSpec[specCount++];//5;
    tStainSpec.tCircleSpec.dRadiusRatioX = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0.5;
    tStainSpec.tCircleSpec.dRadiusRatioY = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0.5;
    tStainSpec.tCircleSpec.dThresholdRatio = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0.5;
    tStainSpec.tCircleSpec.dROIRange = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0.5;
    tStainSpec.tCircleSpec.nUsedFixedCircle = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//false;
    tStainSpec.tMultiCircleSpec.bEnableMultiCircle = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//false;
    tStainSpec.tMultiCircleSpec.dZoneSizeRatio[0] = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0.25;
    tStainSpec.tMultiCircleSpec.dZoneSizeRatio[1] = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0.35;
    tStainSpec.tMultiCircleSpec.dZoneSizeRatio[2] = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//0.45;
    tStainSpec.tMultiCircleSpec.dThreshold[0] = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//9.0;
    tStainSpec.tMultiCircleSpec.dThreshold[1] = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//15.0;
    tStainSpec.tMultiCircleSpec.dThreshold[2] = g_clModelData[m_nUnit].m_LcbSpec[specCount++];//50.0;
    tStainSpec.tMultiCircleSpec.nBlobSize[0] = g_clModelData[m_nUnit].m_LcbSpec[specCount++];
    tStainSpec.tMultiCircleSpec.nBlobSize[1] = g_clModelData[m_nUnit].m_LcbSpec[specCount++];
    tStainSpec.tMultiCircleSpec.nBlobSize[2] = g_clModelData[m_nUnit].m_LcbSpec[specCount++];

    std::shared_ptr<CACMISImageStainLCBCommon> pInspectLCB = std::make_shared<CACMISImageStainLCBCommon>();

	pInspectLCB->SetInspectPosOffset(g_clModelData[m_nUnit].m_LcbOffsetSpec[0], g_clModelData[m_nUnit].m_LcbOffsetSpec[1], g_clModelData[m_nUnit].m_LcbOffsetSpec[2], g_clModelData[m_nUnit].m_LcbOffsetSpec[3]);

    nResultLCB = pInspectLCB->Inspect((BYTE*)img, nWidth, nHeight, tStainSpec,tDataSpec.eDataFormat, tDataSpec.eOutMode, tDataSpec.eSensorType, tDataSpec.nBlackLevel, bUse8BitOnly, false, tDataSpec.eDemosaicMethod);

    if (nResultLCB > 0)
    {
        nResult = R_FAIL_STAIN;
    }
	int LCBBlobCount = pInspectLCB->GetDefectBlobCount();
	g_clMesCommunication[m_nUnit].m_dMesSaturationOc = pInspectLCB->GetSaturationResult(0);


	_stprintf_s(szLog, SIZE_OF_1K, _T("[LCB] Version %s"), pInspectLCB->GetVersion());
    AddLog(szLog, 0, m_nUnit);


    int ocx = 0, ocy = 0, radx = 0, rady = 0;
   
	//CvFont cvfont;
	CvPoint pt;
	int scale = (nWidth > 640 ? 1 : 2);
	double nFontSize = 1 / scale;
	//CString sTemp;

	//cvInitFont(&cvfont, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_NORMAL, nFontSize, nFontSize, 0, 1, 10);
	//sTemp.Format("LCB BlobCount : %d", LCBBlobCount);
	char strTmp[1024];
	sprintf_s(strTmp, "LCB BlobCount : %d", LCBBlobCount);
	pt.x = 50;
	pt.y = 80;
	//cvPutText(bmpImg, sTemp, pt, &cvfont, CV_BLUE);
	putText(bmpImg, strTmp, pt, 0, 1.5, Scalar(10, 10, 10), 3);

	double dFactorX = 0.0;
	double dFactorY = 0.0;

	dFactorX = ((double)g_clModelData[m_nUnit].DefectSizeX / (double)g_clModelData[m_nUnit].m_nWidth);
	dFactorY = ((double)g_clModelData[m_nUnit].DefectSizeY / (double)g_clModelData[m_nUnit].m_nHeight);

	CRect rcReduceBox;

	double dLcbSpecMin = 0.0;
	double dLcbSpecMax = 0.0;

	g_clMandoInspLog[m_nUnit].m_LogBlemishLcb = LCBBlobCount;
	g_clMesCommunication[m_nUnit].m_nMesBlemish[1] = g_clMandoInspLog[m_nUnit].m_LogBlemishLcb;

	dLcbSpecMin = (_ttof(EEpromVerifyData.vMinData[39]));	//lcb
	dLcbSpecMax = (_ttof(EEpromVerifyData.vMaxData[39]));


    if (LCBBlobCount < dLcbSpecMin || LCBBlobCount > dLcbSpecMax)
    {
        //이물불량
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[LCB] BlobCount Spec Out %d [%.1lf~%.1lf]"), LCBBlobCount, dLcbSpecMin, dLcbSpecMax);
		AddLog(szLog, 0, m_nUnit);

		g_clMesCommunication[m_nUnit].m_sStain.Format(_T("FAIL"));
		g_clTaskWork[m_nUnit].m_bOutputCheck[3] = false;	//STAIN LCB

		g_clMesCommunication[m_nUnit].m_nMesBlemishResult[1] = 0;
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;		//LCB


        g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [STAIN LCB NG]");
		g_clMandoInspLog[m_nUnit].m_bInspRes = false;
        if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
        {
            g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG [LCB BLOBCOUNT:%d]"), LCBBlobCount);
            g_clMandoInspLog[m_nUnit].m_nNGCnt++;
        }
		MgraColor(M_DEFAULT, M_COLOR_RED);
		for (int i = 0; i < LCBBlobCount; i++)
		{
			const RECT* rt = pInspectLCB->GetDefectBlobRect(i);
			//cvRectangle(bmpImg, cvPoint(rt->left, rt->top), cvPoint(rt->right, rt->bottom), CV_RGB(0, 0, 255), 2);
			if (bAutoMode == false)
			{
				g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, rt->left, rt->top, rt->right, rt->bottom, M_COLOR_BLUE, 1, FALSE);
			}
			rectangle(bmpImg, cvPoint(rt->left, rt->top), cvPoint(rt->right, rt->bottom), CV_RGB(0, 0, 255), 2);

			//

			rcReduceBox.left = (int)(rt->left	* dFactorX + 0.5);
			rcReduceBox.top = (int)(rt->top		* dFactorY + 0.5);
			rcReduceBox.right = (int)(rt->right	* dFactorX + 0.5);
			rcReduceBox.bottom = (int)(rt->bottom	* dFactorY + 0.5);
			MgraRect(M_DEFAULT, g_clVision.MilDefectOverlayImage[m_nUnit], rcReduceBox.left, rcReduceBox.top, rcReduceBox.right, rcReduceBox.bottom);

		}
		
		g_clVision.DrawOverlayAll(m_nUnit);
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[LCB] BlobCount Spec In %d [%.1lf~%.1lf]"), LCBBlobCount, dLcbSpecMin, dLcbSpecMax);
		AddLog(szLog, 0, m_nUnit);

		g_clMesCommunication[m_nUnit].m_nMesBlemishResult[1] = 1;
		g_clMesCommunication[m_nUnit].m_sStain.Format(_T("PASS"));
	}

    



    if (tStainSpec.tCircleSpec.bEnableCircle || tStainSpec.tMultiCircleSpec.bEnableMultiCircle)
    {
        const TDefectResult* pCircleMaxResult = pInspectLCB->GetMaxDefectResult(EIMAGEREGION_CIRCLE);
        ocx = (int)pCircleMaxResult->dContrastMaxR;
        ocy = (int)pCircleMaxResult->dContrastMaxGb;
        radx = (int)pCircleMaxResult->dContrastMaxGr * tStainSpec.tCircleSpec.dRadiusRatioX;
        rady = (int)pCircleMaxResult->dContrastMaxB  *tStainSpec.tCircleSpec.dRadiusRatioY;
       
        if (tStainSpec.tCircleSpec.bEnableCircle)
        {
			ellipse(bmpImg, cvPoint(ocx, ocy), cvSize(radx, rady), 0, 0, 360, CV_RGB(0, 255, 255), 2);
            g_clVision.DrawMOverlayCircle(m_nUnit, ocx - radx, ocy - rady, ocx + radx, ocy + rady, M_COLOR_MAGENTA, 1, FALSE);
        }
        else
        {
            double dRadYRatio = 1.0;
            if (tStainSpec.tCircleSpec.nUsedFixedCircle)
            {
                dRadYRatio = tStainSpec.tCircleSpec.dRadiusRatioY / tStainSpec.tCircleSpec.dRadiusRatioX;
            }
            //반지름x
            //반지름y
            int nZoneA_X = (int)(radx * tStainSpec.tMultiCircleSpec.dZoneSizeRatio[0]);
            int nZoneA_Y = (int)(rady * tStainSpec.tMultiCircleSpec.dZoneSizeRatio[0] * dRadYRatio);
            int nZoneB_X = (int)(radx * tStainSpec.tMultiCircleSpec.dZoneSizeRatio[1]);
            int nZoneB_Y = (int)(rady * tStainSpec.tMultiCircleSpec.dZoneSizeRatio[1] * dRadYRatio);
            int nZoneC_X = (int)(radx * tStainSpec.tMultiCircleSpec.dZoneSizeRatio[2]);
            int nZoneC_Y = (int)(rady * tStainSpec.tMultiCircleSpec.dZoneSizeRatio[2] * dRadYRatio);

			ellipse(bmpImg, cvPoint(ocx, ocy), cvSize(nZoneA_X, nZoneA_Y), 0, 0, 360, CV_RGB(0, 255, 255), 2);
			ellipse(bmpImg, cvPoint(ocx, ocy), cvSize(nZoneB_X, nZoneB_Y), 0, 0, 360, CV_RGB(0, 255, 255), 2);
			ellipse(bmpImg, cvPoint(ocx, ocy), cvSize(nZoneC_X, nZoneC_Y), 0, 0, 360, CV_RGB(0, 255, 255), 2);
            //
            g_clVision.DrawMOverlayCircle(m_nUnit, ocx - nZoneA_X, ocy - nZoneA_Y, ocx + nZoneA_X, ocy + nZoneA_Y, M_COLOR_MAGENTA, 1, FALSE);
            g_clVision.DrawMOverlayCircle(m_nUnit, ocx - nZoneB_X, ocy - nZoneB_Y, ocx + nZoneB_X, ocy + nZoneB_Y, M_COLOR_MAGENTA, 1, FALSE);
            g_clVision.DrawMOverlayCircle(m_nUnit, ocx - nZoneC_X, ocy - nZoneC_Y, ocx + nZoneC_X, ocy + nZoneC_Y, M_COLOR_MAGENTA, 1, FALSE);
            //vision.ellipselist[CCD].addList(CPoint(ocx - nZoneA_X, ocy - nZoneA_Y), CPoint(ocx + nZoneA_X, ocy + nZoneA_Y), PS_SOLID, M_COLOR_CYAN);

        }
        if (tStainSpec.tCircleSpec.nUsedFixedCircle)
        {
            RECT rtRefEdge;
            RECT rtCenter;
            //oc threshold test roi - top
            rtRefEdge.left = max(nWidth / 2 - 100 / 2, 0);
            rtRefEdge.top = (LONG)(0.1 * nHeight / 2);
            rtRefEdge.right = min(rtRefEdge.left + 100 - 1, (LONG)nWidth - 1);
            rtRefEdge.bottom = min(rtRefEdge.top + 100 - 1, (LONG)nHeight - 1);

            //oc threshold test roi - center
            rtCenter.left = rtRefEdge.left;
            rtCenter.top = max(nHeight / 2 - 100 / 2, 0);
            rtCenter.right = rtRefEdge.right;
            rtCenter.bottom = min(nHeight / 2 + 100 / 2 - 1, nHeight - 1);

            //cvRectangle(bmpImg, cvPoint(rtRefEdge.left, rtRefEdge.top), cvPoint(rtRefEdge.right, rtRefEdge.bottom), CV_RGB(255, 86, 12), 2);
            //cvRectangle(bmpImg, cvPoint(rtCenter.left, rtCenter.top), cvPoint(rtCenter.right, rtCenter.bottom), CV_RGB(255, 86, 12), 2);

			rectangle(bmpImg, cvPoint(rtRefEdge.left, rtRefEdge.top), cvPoint(rtRefEdge.right, rtRefEdge.bottom), CV_RGB(255, 86, 12), 2);
			rectangle(bmpImg, cvPoint(rtCenter.left, rtCenter.top), cvPoint(rtCenter.right, rtCenter.bottom), CV_RGB(255, 86, 12), 2);
            g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, rtRefEdge.left, rtRefEdge.top, rtRefEdge.right, rtRefEdge.bottom, M_COLOR_BLUE, 1, FALSE);
            g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, rtCenter.left, rtCenter.top, rtCenter.right, rtCenter.bottom, M_COLOR_BLUE, 1, FALSE);
        }
        
    }

	int nCenterCount = pInspectLCB->GetDefectCount(EIMAGEREGION_CENTER);
	const TDefectResult* pCenterMaxResult = pInspectLCB->GetMaxDefectResult(EIMAGEREGION_CENTER);

	g_clMandoInspLog[m_nUnit].m_LogBlemishLcbMaxCenter = pInspectLCB->GetMaxDefectResult(EIMAGEREGION_CENTER)->dValue;
	g_clMandoInspLog[m_nUnit].m_LogBlemishLcbMaxEdge = pInspectLCB->GetMaxDefectResult(EIMAGEREGION_EDGE)->dValue;
	g_clMandoInspLog[m_nUnit].m_LogBlemishLcbMaxCorner = pInspectLCB->GetMaxDefectResult(EIMAGEREGION_CORNER)->dValue;

	g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[0] = pInspectLCB->GetMaxDefectResult(EIMAGEREGION_CENTER)->dValue;
	g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[1] = pInspectLCB->GetMaxDefectResult(EIMAGEREGION_EDGE)->dValue;
	g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[2] = pInspectLCB->GetMaxDefectResult(EIMAGEREGION_CORNER)->dValue;

	_stprintf_s(szLog, SIZE_OF_1K, _T("[LCB] Max Value (Center) %.6lf"), g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[0]);
	AddLog(szLog, 0, m_nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[LCB] Max Value (Edge) %.6lf"), g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[1]);
	AddLog(szLog, 0, m_nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[LCB] Max Value (Corner) %.6lf"), g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[2]);
	AddLog(szLog, 0, m_nUnit);

    if (nResult)
    {
        if (tStainSpec.tCircleSpec.bEnableCircle || tStainSpec.tMultiCircleSpec.bEnableMultiCircle)
        {
            int nCircleCount = pInspectLCB->GetDefectCount(EIMAGEREGION_CIRCLE);
            if (tStainSpec.tCircleSpec.nUsedFixedCircle)
            {
                RECT rtRefEdge;
                RECT rtCenter;
                //oc threshold test roi - top
                rtRefEdge.left = max(g_clModelData[m_nUnit].m_nWidth / 2 - 100 / 2, 0);
                rtRefEdge.top = (LONG)(0.1 * g_clModelData[m_nUnit].m_nHeight / 2);
                rtRefEdge.right = min(rtRefEdge.left + 100 - 1, (LONG)g_clModelData[m_nUnit].m_nWidth - 1);
                rtRefEdge.bottom = min(rtRefEdge.top + 100 - 1, (LONG)g_clModelData[m_nUnit].m_nHeight - 1);

                //oc threshold test roi - center
                rtCenter.left = rtRefEdge.left;
                rtCenter.top = max(g_clModelData[m_nUnit].m_nHeight / 2 - 100 / 2, 0);
                rtCenter.right = rtRefEdge.right;
                rtCenter.bottom = min(g_clModelData[m_nUnit].m_nHeight / 2 + 100 / 2 - 1, g_clModelData[m_nUnit].m_nHeight - 1);

                //cvRectangle(bmpImg, cvPoint(rtRefEdge.left, rtRefEdge.top), cvPoint(rtRefEdge.right, rtRefEdge.bottom), CV_RGB(255, 86, 12) , 2);
                //cvRectangle(bmpImg, cvPoint(rtCenter.left, rtCenter.top), cvPoint(rtCenter.right, rtCenter.bottom), CV_RGB(255, 86, 12), 2);

				rectangle(bmpImg, cvPoint(rtRefEdge.left, rtRefEdge.top), cvPoint(rtRefEdge.right, rtRefEdge.bottom), CV_RGB(255, 86, 12), 2);
				rectangle(bmpImg, cvPoint(rtCenter.left, rtCenter.top), cvPoint(rtCenter.right, rtCenter.bottom), CV_RGB(255, 86, 12), 2);
                g_clVision.DrawMOverlayBox(m_nUnit,  m_nUnit, rtRefEdge, M_COLOR_RED, 1, FALSE, PS_SOLID);
                g_clVision.DrawMOverlayBox(m_nUnit,  m_nUnit, rtCenter, M_COLOR_RED, 1, FALSE, PS_SOLID);
                //vision.boxlist[CCD].addList(rtRefEdge, PS_SOLID, M_COLOR_RED);
                //vision.boxlist[CCD].addList(rtCenter, PS_SOLID, M_COLOR_RED);

            }
        }
    }

	if (g_clModelData[m_nUnit].m_nNgImageSaveUse == 1)
	{
		if (LCBBlobCount > 0)
		{
			g_clLaonGrabberWrapper[m_nUnit].JpgMatSave(bmpImg, 1);
		}
	}else
	{

		g_clLaonGrabberWrapper[m_nUnit].JpgMatSave(bmpImg, 1);
	}
	
    g_SaveLGITLog(m_nUnit, "LCB", pInspectLCB->GetLogHeader(), pInspectLCB->GetLogData(), pInspectLCB->GetVersion());
    return LCBBlobCount;
}

int CPRIFunc_Insp::FDFInsp(BYTE* img, bool bAutoMode)
{
	int nResult = R_RESULT_PASS;

	int nBlackLevel = 0;
	//CString szLog = "";
	TCHAR szLog[SIZE_OF_1K];
	TFDFSpec stSpecFDF;
	memset(&stSpecFDF, 0x00, sizeof(TFDFSpec));
	int specCount = 0;
	int nWidth = g_clModelData[m_nUnit].m_nWidth;
	int nHeight = g_clModelData[m_nUnit].m_nHeight;

	TDATASPEC& tDataSpec = g_clLaonGrabberWrapper[m_nUnit].dBlemish_Tdataspec;
	bool bUse8BitOnly = false;
	
	if (g_clModelData[m_nUnit].m_nBlemish8BitUse == 1)
	{
		bUse8BitOnly = true;
	}

	ACMISSoftISP::xMakeBMP(img, (byte*)g_clLaonGrabberWrapper[m_nUnit].m_pTestBuffer,
		g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight, g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n);
	Mat bmpImg = Mat(g_clModelData[m_nUnit].m_nHeight, g_clModelData[m_nUnit].m_nWidth, CV_8UC3);

	bmpImg.data = g_clLaonGrabberWrapper[m_nUnit].m_pTestBuffer;
	//----------------------------------------------------------------------
	// Spec - FDF
	//----------------------------------------------------------------------
	stSpecFDF.dCenterThreshold = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//10.75;
	stSpecFDF.dEdgeThreshold = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//15.0;
	stSpecFDF.dCornerThreshold = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//15.0;
	stSpecFDF.nMedianFilterWidth = (int)g_clModelData[m_nUnit].m_FDFSpec[specCount++];//0;
	stSpecFDF.nMedianFilterHeight = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//1000;
	stSpecFDF.nWidthScaleRatio = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//70.0;
	stSpecFDF.nHeightScaleRatio = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//4.2;
	stSpecFDF.nMinDefectWidthHeight = (int)g_clModelData[m_nUnit].m_FDFSpec[specCount++];//64;
	stSpecFDF.nWindowSize = (int)g_clModelData[m_nUnit].m_FDFSpec[specCount++];// 100;
	stSpecFDF.nEdgeSize = (int)g_clModelData[m_nUnit].m_FDFSpec[specCount++];
	stSpecFDF.bEnableChannel = (bool)g_clModelData[m_nUnit].m_FDFSpec[specCount++];
	stSpecFDF.nMaxSingleDefectNum = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//15;

	stSpecFDF.tCircleSpec.bEnableCircle = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//false;
	stSpecFDF.tCircleSpec.nPosOffsetX = (int)g_clModelData[m_nUnit].m_FDFSpec[specCount++];//5;
	stSpecFDF.tCircleSpec.nPosOffsetY = (int)g_clModelData[m_nUnit].m_FDFSpec[specCount++];//5;
	stSpecFDF.tCircleSpec.dRadiusRatioX = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//0.45;
	stSpecFDF.tCircleSpec.dRadiusRatioY = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//0.45;
	stSpecFDF.tCircleSpec.dThresholdRatio = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//0.5;
	stSpecFDF.tCircleSpec.dROIRange = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//0.5;
	stSpecFDF.tCircleSpec.nUsedFixedCircle = (int)g_clModelData[m_nUnit].m_FDFSpec[specCount++];//0;

	stSpecFDF.tMultiCircleSpec.bEnableMultiCircle = (int)g_clModelData[m_nUnit].m_FDFSpec[specCount++];//false;
	stSpecFDF.tMultiCircleSpec.dZoneSizeRatio[0] = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//0.2;
	stSpecFDF.tMultiCircleSpec.dZoneSizeRatio[1] = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//0.4;
	stSpecFDF.tMultiCircleSpec.dZoneSizeRatio[2] = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//0.52;
	stSpecFDF.tMultiCircleSpec.dThreshold[0] = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//0.45;
	stSpecFDF.tMultiCircleSpec.dThreshold[1] = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//0.45;
	stSpecFDF.tMultiCircleSpec.dThreshold[2] = g_clModelData[m_nUnit].m_FDFSpec[specCount++];//0.8;
	stSpecFDF.tMultiCircleSpec.nBlobSize[0] = g_clModelData[m_nUnit].m_FDFSpec[specCount++];
	stSpecFDF.tMultiCircleSpec.nBlobSize[1] = g_clModelData[m_nUnit].m_FDFSpec[specCount++];
	stSpecFDF.tMultiCircleSpec.nBlobSize[2] = g_clModelData[m_nUnit].m_FDFSpec[specCount++];

	//std::shared_ptr<CACMISImageStainRU_YmeanCommon> pInspectBlemish_Ymean = std::make_shared<CACMISImageStainRU_YmeanCommon>();//delete,x
	std::shared_ptr<CACMISImageFastDifferenceFiltering> m_pFDF = std::make_shared<CACMISImageFastDifferenceFiltering>();
	
	m_pFDF->SetInspectPosOffset(g_clModelData[m_nUnit].m_FDFOffsetSpec[0], g_clModelData[m_nUnit].m_FDFOffsetSpec[1], g_clModelData[m_nUnit].m_FDFOffsetSpec[2], g_clModelData[m_nUnit].m_FDFOffsetSpec[3]);
	m_pFDF->Inspect((BYTE*)img, nWidth, nHeight, stSpecFDF, tDataSpec.eDataFormat, tDataSpec.eOutMode, tDataSpec.eSensorType, tDataSpec.nBlackLevel, bUse8BitOnly, false, tDataSpec.eDemosaicMethod);
	int FdfBlobCount = 0;
	FdfBlobCount = m_pFDF->GetDefectBlobCount();

	//CvFont cvfont;
	CvPoint pt;
	int scale = (nWidth > 640 ? 1 : 2);
	double nFontSize = 1 / scale;
	//CString sTemp;
	//cvInitFont(&cvfont, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_NORMAL, nFontSize, nFontSize, 0, 1, 10);
	//sTemp.Format("Ymean BlobCount : %d", FdfBlobCount);
	char strTmp[1024];
	sprintf_s(strTmp, "FDF BlobCount : %d", FdfBlobCount);
	pt.x = 50;
	pt.y = 110;
	//cvPutText(bmpImg, sTemp, pt, &cvfont, CV_BLUE);
	putText(bmpImg, strTmp, pt, 0, 1.5, Scalar(10, 10, 10), 3);


	double dFdfSpecMin = 0.0;
	double dFdfSpecMax = 0.0;
	g_clMandoInspLog[m_nUnit].m_LogBlemishFPF = FdfBlobCount;

	g_clMesCommunication[m_nUnit].m_nMesBlemish[0] = FdfBlobCount;

	dFdfSpecMin = (_ttof(EEpromVerifyData.vMinData[41]));	//FDF
	dFdfSpecMax = (_ttof(EEpromVerifyData.vMaxData[41]));

	if (FdfBlobCount < dFdfSpecMin || FdfBlobCount > dFdfSpecMax)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[FDF] BlobCount Spec Out %d [%.1lf~%.1lf]"), FdfBlobCount, dFdfSpecMin, dFdfSpecMax);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_bOutputCheck[3] = false;	//STAIN FDF
		g_clMesCommunication[m_nUnit].m_nMesBlemishResult[0] = 0;
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;//STAIN FDF
		nResult = R_FAIL_STAIN;// R_FAIL_BLACK_SPOT;
							   //이물불량
		g_clMandoInspLog[m_nUnit].m_bInspRes = false;
		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [STAIN FDF NG]");
		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG [FDF BLOBCOUNT:%d]"), FdfBlobCount);
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}
		
		for (int i = 0; i < FdfBlobCount; i++)
		{
			const RECT* rt = m_pFDF->GetDefectBlobRect(i);
			//cvRectangle(bmpImg, cvPoint(rt->left, rt->top), cvPoint(rt->right, rt->bottom), CV_RGB(138, 43, 226), 2);
			rectangle(bmpImg, cvPoint(rt->left, rt->top), cvPoint(rt->right, rt->bottom), CV_RGB(138, 43, 226), 2);
			if (bAutoMode == false)
			{
				g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, rt->left, rt->top, rt->right, rt->bottom, M_COLOR_BLUE, 1, FALSE);
				//vision.boxlist[CCD].addList(rt, PS_SOLID, M_COLOR_CYAN);
			}
		}
		
	}
	else
	{
		g_clMesCommunication[m_nUnit].m_nMesBlemishResult[0] = 1;
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[FDF] BlobCount Spec In %d [%.1lf~%.1lf]"), FdfBlobCount, dFdfSpecMin, dFdfSpecMax);
		AddLog(szLog, 0, m_nUnit);
	}

	//szLog.Format("[FDF] Version %s", m_pFDF->GetVersion());
	_stprintf_s(szLog, SIZE_OF_1K, _T("[FDF] Version %s"), m_pFDF->GetVersion());
	AddLog(szLog, 0, m_nUnit, false);
	//szLog.Format("[FDF] GetDefectBlobCount %d", FdfBlobCount);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[FDF] GetDefectBlobCount  %d"), FdfBlobCount);
	AddLog(szLog, 0, m_nUnit, false);
	

	

	if (stSpecFDF.tCircleSpec.bEnableCircle || stSpecFDF.tMultiCircleSpec.bEnableMultiCircle)
	{
		int ocx = 0, ocy = 0, radx = 0, rady = 0;
		const TDefectResult* pCircleMaxResult = m_pFDF->GetMaxDefectResult(EIMAGEREGION_CIRCLE);
		

		ocx = (int)pCircleMaxResult->dContrastMaxR;
		ocy = (int)pCircleMaxResult->dContrastMaxGb;
		radx = (int)pCircleMaxResult->dContrastMaxGr* stSpecFDF.tCircleSpec.dRadiusRatioX;
		rady = (int)pCircleMaxResult->dContrastMaxB *stSpecFDF.tCircleSpec.dRadiusRatioY;

		if (stSpecFDF.tCircleSpec.bEnableCircle)
		{
			//std::cout << "[RUYMean] ocx=" << ocx << "ocy = " << ocy << "radx = " << radx << "rady = " << rady << std::endl;
			//cvEllipse(bmpImg, cvPoint(ocx, ocy), cvSize(radx, rady), 0, 0, 360, CV_RGB(0, 255, 255));
			ellipse(bmpImg, cvPoint(ocx, ocy), cvSize(radx, rady), 0, 0, 360, CV_RGB(0, 255, 255));
			g_clVision.DrawMOverlayCircle(m_nUnit, ocx - radx, ocy - rady, ocx + radx, ocy + rady, M_COLOR_MAGENTA, 1, FALSE);
			//vision.ellipselist[CCD].addList(CPoint(ocx - radx, ocy - rady), CPoint(ocx + radx, ocy + rady), PS_SOLID, M_COLOR_CYAN);
		}
	}
	int nCircleCount = m_pFDF->GetDefectCount(EIMAGEREGION_CIRCLE);

	g_clMandoInspLog[m_nUnit].m_LogBlemishFdfMaxCenter = m_pFDF->GetMaxDefectResult(EIMAGEREGION_CENTER)->dValue;
	g_clMandoInspLog[m_nUnit].m_LogBlemishFdfMaxEdge = m_pFDF->GetMaxDefectResult(EIMAGEREGION_EDGE)->dValue;
	g_clMandoInspLog[m_nUnit].m_LogBlemishFdfMaxCorner = m_pFDF->GetMaxDefectResult(EIMAGEREGION_CORNER)->dValue;

	g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[3] = m_pFDF->GetMaxDefectResult(EIMAGEREGION_CENTER)->dValue;
	g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[4] = m_pFDF->GetMaxDefectResult(EIMAGEREGION_EDGE)->dValue;
	g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[5] = m_pFDF->GetMaxDefectResult(EIMAGEREGION_CORNER)->dValue;

	_stprintf_s(szLog, SIZE_OF_1K, _T("[FDF] Max Value (Center) %.6lf"), g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[3]);
	AddLog(szLog, 0, m_nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[FDF] Max Value (Edge) %.6lf"), g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[4]);
	AddLog(szLog, 0, m_nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[FDF] Max Value (Corner) %.6lf"), g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[5]);
	AddLog(szLog, 0, m_nUnit);
	if (g_clModelData[m_nUnit].m_nNgImageSaveUse == 1)
	{
		if (FdfBlobCount > 0)
		{
			g_clLaonGrabberWrapper[m_nUnit].JpgMatSave(bmpImg, 0);
		}
	}
	else
	{

		g_clLaonGrabberWrapper[m_nUnit].JpgMatSave(bmpImg, 0);
	}
	//cvReleaseImage(&bmpImg);
	g_SaveLGITLog(m_nUnit, "FDF", m_pFDF->GetLogHeader(), m_pFDF->GetLogData(), m_pFDF->GetVersion());
	return FdfBlobCount;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
int CPRIFunc_Insp::Blemish_YmeanInsp(BYTE* img, bool bAutoMode)
{
	
    int nResult = R_RESULT_PASS;
   
    int nBlackLevel = 0;
    //CString szLog = "";
	TCHAR szLog[SIZE_OF_1K];
    //TStainSpec tStainSpec;
    TRU_YmeanSpecN stSpecYmean;
    memset(&stSpecYmean, 0x00, sizeof(TRU_YmeanSpecN));
    int specCount = 0;
	int nWidth = g_clModelData[m_nUnit].m_nWidth;
	int nHeight = g_clModelData[m_nUnit].m_nHeight;
	TDATASPEC& tDataSpec = g_clLaonGrabberWrapper[m_nUnit].dBlemish_Tdataspec;
	bool bUse8BitOnly = false;


	if (g_clModelData[m_nUnit].m_nBlemish8BitUse == 1)
	{
		bUse8BitOnly = true;
	}
	//IplImage *bmpImg = cvCreateImage(cvSize(nWidth, nHeight), 8, 3); // bmp for display
	//bmpImg->imageData=	(char*)g_clLaonGrabberWrapper[m_nUnit].m_pFrameBMPBuffer;

	ACMISSoftISP::xMakeBMP(img, (byte*)g_clLaonGrabberWrapper[m_nUnit].m_pTestBuffer,
		g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight, g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n);
	Mat bmpImg = Mat(g_clModelData[m_nUnit].m_nHeight, g_clModelData[m_nUnit].m_nWidth, CV_8UC3);
	bmpImg.data = g_clLaonGrabberWrapper[m_nUnit].m_pTestBuffer;
    //----------------------------------------------------------------------
    // Spec - Ymean
    //----------------------------------------------------------------------
    stSpecYmean.nEdgeSize = (int)g_clModelData[m_nUnit].m_YmeanSpec[specCount++];// 100;
    stSpecYmean.fCenterThreshold = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//10.75;
    stSpecYmean.fEdgeThreshold = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//15.0;
    stSpecYmean.fCornerThreshold = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//15.0;
    stSpecYmean.nDefectBlockSize = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//15;
    stSpecYmean.nLscBlockSize = (int)g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//64;
    stSpecYmean.nCalcType = (int)g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//0;
    stSpecYmean.nMaxRecursiveCount = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//1000;
    stSpecYmean.dMaxDefectSize = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//70.0;
    stSpecYmean.dPixelSize = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//4.2;

    stSpecYmean.tCircleSpec.bEnableCircle = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//false;
    stSpecYmean.tCircleSpec.nPosOffsetX = (int)g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//5;
    stSpecYmean.tCircleSpec.nPosOffsetY = (int)g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//5;
    stSpecYmean.tCircleSpec.dRadiusRatioX = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//0.45;
    stSpecYmean.tCircleSpec.dRadiusRatioY = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//0.45;
    stSpecYmean.tCircleSpec.dThresholdRatio = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//0.5;
    stSpecYmean.tCircleSpec.dROIRange = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//0.5;
    stSpecYmean.tCircleSpec.nUsedFixedCircle = (int)g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//0;
    stSpecYmean.tMultiCircleSpec.bEnableMultiCircle = (int)g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//false;
    stSpecYmean.tMultiCircleSpec.dZoneSizeRatio[0] = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//0.2;
    stSpecYmean.tMultiCircleSpec.dZoneSizeRatio[1] = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//0.4;
    stSpecYmean.tMultiCircleSpec.dZoneSizeRatio[2] = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//0.52;
    stSpecYmean.tMultiCircleSpec.dThreshold[0] = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//0.45;
    stSpecYmean.tMultiCircleSpec.dThreshold[1] = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//0.45;
    stSpecYmean.tMultiCircleSpec.dThreshold[2] = g_clModelData[m_nUnit].m_YmeanSpec[specCount++];//0.8;
    stSpecYmean.tMultiCircleSpec.nBlobSize[0] =  g_clModelData[m_nUnit].m_YmeanSpec[specCount++];
    stSpecYmean.tMultiCircleSpec.nBlobSize[1] =  g_clModelData[m_nUnit].m_YmeanSpec[specCount++];
    stSpecYmean.tMultiCircleSpec.nBlobSize[2] =  g_clModelData[m_nUnit].m_YmeanSpec[specCount++];

    std::shared_ptr<CACMISImageStainRU_YmeanCommon> pInspectBlemish_Ymean = std::make_shared<CACMISImageStainRU_YmeanCommon>();//delete,x
	
	pInspectBlemish_Ymean->SetInspectPosOffset(g_clModelData[m_nUnit].m_YmeanOffsetSpec[0], g_clModelData[m_nUnit].m_YmeanOffsetSpec[1], g_clModelData[m_nUnit].m_YmeanOffsetSpec[2], g_clModelData[m_nUnit].m_YmeanOffsetSpec[3]);

    pInspectBlemish_Ymean->Inspect((BYTE*)img, nWidth, nHeight, stSpecYmean, tDataSpec.eDataFormat, tDataSpec.eOutMode, tDataSpec.eSensorType, tDataSpec.nBlackLevel, bUse8BitOnly, false, tDataSpec.eDemosaicMethod);
	int YmeanBlobCount = 0;
	YmeanBlobCount = pInspectBlemish_Ymean->GetDefectBlobCount();

	//CvFont cvfont;
	CvPoint pt;
	int scale = (nWidth > 640 ? 1 : 2);
	double nFontSize = 1 / scale;
	//CString sTemp;
	//cvInitFont(&cvfont, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_NORMAL, nFontSize, nFontSize, 0, 1, 10);
	//sTemp.Format("Ymean BlobCount : %d", YmeanBlobCount);

	char strTmp[1024];
	sprintf_s(strTmp, "Ymean BlobCount : %d", YmeanBlobCount);
	pt.x = 50;
	pt.y = 110;
	//cvPutText(bmpImg, sTemp, pt, &cvfont, CV_BLUE);
	putText(bmpImg, strTmp, pt, 0, 1.5, Scalar(10, 10, 10), 3);


	double dYmeanSpecMin = 0.0;
	double dYmeanSpecMax = 0.0;
	g_clMandoInspLog[m_nUnit].m_LogBlemishRU_Ymean = YmeanBlobCount;
	g_clMesCommunication[m_nUnit].m_nMesBlemish[2] = g_clMandoInspLog[m_nUnit].m_LogBlemishRU_Ymean;

	dYmeanSpecMin = (_ttof(EEpromVerifyData.vMinData[40]));	//Ymean
	dYmeanSpecMax = (_ttof(EEpromVerifyData.vMaxData[40]));
    if (YmeanBlobCount < dYmeanSpecMin || YmeanBlobCount > dYmeanSpecMax)
    {
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[Ymean] BlobCount Spec Out %d [%.1lf ~ %.1lf]"), YmeanBlobCount, dYmeanSpecMin, dYmeanSpecMax);
		AddLog(szLog, 0, m_nUnit);

		g_clTaskWork[m_nUnit].m_bOutputCheck[3] = false;	//STAIN YMEAN
		g_clMesCommunication[m_nUnit].m_nMesBlemishResult[2] = 0;
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;		//STAIN YMEAN

        nResult = R_FAIL_STAIN;// R_FAIL_BLACK_SPOT;
        //이물불량
		g_clMandoInspLog[m_nUnit].m_bInspRes = false;
        g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [STAIN YMEAN NG]");
        if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
        {
            g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG [YMEAN BLOBCOUNT:%d]"), YmeanBlobCount);
            g_clMandoInspLog[m_nUnit].m_nNGCnt++;
        }
		
			for (int i = 0; i < YmeanBlobCount; i++)
			{
				const RECT* rt = pInspectBlemish_Ymean->GetDefectBlobRect(i);
				//cvRectangle(bmpImg, cvPoint(rt->left, rt->top), cvPoint(rt->right, rt->bottom), CV_RGB(138, 43, 226), 2);
				rectangle(bmpImg, cvPoint(rt->left, rt->top), cvPoint(rt->right, rt->bottom), CV_RGB(138, 43, 226), 2);
				if (bAutoMode == false)
				{
					g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit, rt->left, rt->top, rt->right, rt->bottom, M_COLOR_BLUE, 1, FALSE);
					//vision.boxlist[CCD].addList(rt, PS_SOLID, M_COLOR_CYAN);
				}
			}
		
	}
	else
	{
		g_clMesCommunication[m_nUnit].m_nMesBlemishResult[2] = 1;
		_stprintf_s(szLog, SIZE_OF_1K, _T("	[Ymean] BlobCount Spec In %d [%.1lf ~ %.1lf]"), YmeanBlobCount, dYmeanSpecMin, dYmeanSpecMax);
		AddLog(szLog, 0, m_nUnit);
	}

	_stprintf_s(szLog, SIZE_OF_1K, _T("[RUYMean] Version %s"), pInspectBlemish_Ymean->GetVersion());
    AddLog(szLog, 0, m_nUnit, false);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[RUYMean] GetDefectBlobCount %d"), YmeanBlobCount);
    AddLog(szLog, 0, m_nUnit, false);
    

	

	if (stSpecYmean.tCircleSpec.bEnableCircle || stSpecYmean.tMultiCircleSpec.bEnableMultiCircle)
	{
		int ocx = 0, ocy = 0, radx = 0, rady = 0;
		
		const TDefectResult* pCircleMaxResult = pInspectBlemish_Ymean->GetMaxDefectResult(EIMAGEREGION_CIRCLE);

		ocx = (int)pCircleMaxResult->dContrastMaxR;
		ocy = (int)pCircleMaxResult->dContrastMaxGb;
		radx = (int)pCircleMaxResult->dContrastMaxGr* stSpecYmean.tCircleSpec.dRadiusRatioX;
		rady = (int)pCircleMaxResult->dContrastMaxB *stSpecYmean.tCircleSpec.dRadiusRatioY;

		if (stSpecYmean.tCircleSpec.bEnableCircle)
		{
			//std::cout << "[RUYMean] ocx=" << ocx << "ocy = " << ocy << "radx = " << radx << "rady = " << rady << std::endl;
			//cvEllipse(bmpImg, cvPoint(ocx, ocy), cvSize(radx, rady), 0, 0, 360, CV_RGB(0, 255, 255));
			ellipse(bmpImg, cvPoint(ocx, ocy), cvSize(radx, rady), 0, 0, 360, CV_RGB(0, 255, 255));
			g_clVision.DrawMOverlayCircle(m_nUnit, ocx - radx, ocy - rady, ocx + radx, ocy + rady, M_COLOR_MAGENTA, 1, FALSE);
			//vision.ellipselist[CCD].addList(CPoint(ocx - radx, ocy - rady), CPoint(ocx + radx, ocy + rady), PS_SOLID, M_COLOR_CYAN);
		}
	}

	int nCircleCount = pInspectBlemish_Ymean->GetDefectCount(EIMAGEREGION_CIRCLE);

	g_clMandoInspLog[m_nUnit].m_LogBlemishYmeanMaxCenter = pInspectBlemish_Ymean->GetMaxDefectResult(EIMAGEREGION_CENTER)->dValue;
	g_clMandoInspLog[m_nUnit].m_LogBlemishYmeanMaxEdge = pInspectBlemish_Ymean->GetMaxDefectResult(EIMAGEREGION_EDGE)->dValue;
	g_clMandoInspLog[m_nUnit].m_LogBlemishYmeanMaxCorner = pInspectBlemish_Ymean->GetMaxDefectResult(EIMAGEREGION_CORNER)->dValue;

	g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[6] = pInspectBlemish_Ymean->GetMaxDefectResult(EIMAGEREGION_CENTER)->dValue;
	g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[7] = pInspectBlemish_Ymean->GetMaxDefectResult(EIMAGEREGION_EDGE)->dValue;
	g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[8] = pInspectBlemish_Ymean->GetMaxDefectResult(EIMAGEREGION_CORNER)->dValue;


	_stprintf_s(szLog, SIZE_OF_1K, _T("[Ymean] Max Value (Center) %.6lf"), g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[6]);
	AddLog(szLog, 0, m_nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[Ymean] Max Value (Edge) %.6lf"), g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[7]);
	AddLog(szLog, 0, m_nUnit);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[Ymean] Max Value (Corner) %.6lf"), g_clMesCommunication[m_nUnit].m_nMesBlemishMaxDefect[8]);
	AddLog(szLog, 0, m_nUnit);

	if (g_clModelData[m_nUnit].m_nNgImageSaveUse == 1)
	{
		if (YmeanBlobCount > 0)
		{
			g_clLaonGrabberWrapper[m_nUnit].JpgMatSave(bmpImg, 2);
		}
	}
	else
	{

		g_clLaonGrabberWrapper[m_nUnit].JpgMatSave(bmpImg, 2);
	}
	//cvReleaseImage(&bmpImg);
    //CalibrationInspLog.func_LogSave_Stain("[RU_Ymean]", pInspectBlemish_Ymean->GetLogHeader(), pInspectBlemish_Ymean->GetLogData());
    g_SaveLGITLog(m_nUnit, "RUYMean", pInspectBlemish_Ymean->GetLogHeader(), pInspectBlemish_Ymean->GetLogData(), pInspectBlemish_Ymean->GetVersion());
    return YmeanBlobCount;
}
//-----------------------------------------------------------------------------
//
//	전류 측정 랜덤
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Random_CurrentMeasure(bool bLogDraw, bool bAutoMode)
{
	//TCHAR szLog[SIZE_OF_1K];
	////double _ran = (double)rand()/ RAND_MAX;
	////double _ranCur = (82.0 + _ran * (85.0 - 82.0));
	//random_device rd;
	//mt19937 gen(rd());
	////uniform_int_distribution<int> dis(5, 10);
	//uniform_real_distribution<double> dis(355.0, 480.0);

	//double m_cur = dis(gen);

	//g_clMandoInspLog[m_nUnit].m_dCurrent = m_cur;
	//g_clMesCommunication[m_nUnit].m_dMesCurrent = m_cur;
	//g_clMesCommunication[m_nUnit].m_nMesCurrentResult = 1;

	//_stprintf_s(szLog, SIZE_OF_1K, _T("	전류 측정치 : %.03lf"), g_clMesCommunication[m_nUnit].m_dMesCurrent);
	//AddLog(szLog, 0, m_nUnit);

	return true;
}

//-----------------------------------------------------------------------------
//
//	전류 측정
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_Ultra_CurrentMeasure(bool bLogDraw, bool bAutoMode)
{
	

	return false;
}


//-----------------------------------------------------------------------------
//
//	전류 측정
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_CurrentMeasure(bool bAutoMode)
{
	double cur = 0.0;
	bool	bRes = true;
	TCHAR szLog[SIZE_OF_1K];

	TCHAR	szPath[SIZE_OF_1K];

	double currentValue[5];
	double dCurrentVal = 0.0;


	int errorCode = 0;
	bool bInspRtn = true;

	byte WData[1];
	int i = 0;
	byte pVolData1[8];
	memset(pVolData1, 0x00, 8);

	unsigned int nSlaveAddress = 0x41;
	unsigned int nAddress = 0x01;


	errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)nSlaveAddress, (unsigned short)nAddress, 1, pVolData1, (unsigned short)2);	//Temperature1

	std::bitset<8> binaryByte1(pVolData1[0]);
	std::bitset<8> binaryByte2(pVolData1[1]);
	// 2진수 변환
	std::bitset<16> combinedBinaryValue((binaryByte1.to_ulong() << 8) | binaryByte2.to_ulong());
	//2의 보수 변환
	std::bitset<16> twosComplement = ~combinedBinaryValue;
	twosComplement = twosComplement.to_ulong() + 1;
	//3 ~ 14 bit만사용
	std::bitset<12> maskedValue = (twosComplement.to_ulong() >> 3) & ~(1 << 12);
	//진수 변환
	int decimalValue = static_cast<int>(maskedValue.to_ulong());

	dCurrentVal = (decimalValue * 0.00004) / 0.47;

	g_clMesCommunication[m_nUnit].m_dMesCurrent = dCurrentVal;


	double mCurrent_Value = 0.0;
	double mCurrent_SpecMin = 0.0;
	double mCurrent_SpecMax = 0.0;

	mCurrent_Value = g_clMesCommunication[m_nUnit].m_dMesCurrent;
	mCurrent_SpecMin = (_ttof(EEpromVerifyData.vMinData[0]));
	mCurrent_SpecMax = (_ttof(EEpromVerifyData.vMaxData[0]));


	if (mCurrent_Value < mCurrent_SpecMin || mCurrent_Value > mCurrent_SpecMax)
	{
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;	//CURRENT
		g_clMesCommunication[m_nUnit].m_nMesCurrentResult = 0;
		_stprintf_s(szLog, SIZE_OF_1K, _T("[CURRENT] Spec Out: %.6lf [%.3lf~%.3lf]"), mCurrent_Value, mCurrent_SpecMin, mCurrent_SpecMax);
		AddLog(szLog, 0, m_nUnit);
		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [CURRENT NG]");
		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG CURRENT :%.6lf [%.3lf~%.3lf]"), mCurrent_Value, mCurrent_SpecMin, mCurrent_SpecMax);
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}
		//g_clMesCommunication[m_nUnit].m_nMesRIRICornerResult[0] = 0;

		g_clMandoInspLog[m_nUnit].m_bInspRes = false;
		g_clTaskWork[m_nUnit].m_bOutputCheck[2] = false;	//OC

	}
	else
	{
		g_clMesCommunication[m_nUnit].m_nMesCurrentResult = 1;
		_stprintf_s(szLog, SIZE_OF_1K, _T("[CURRENT] Spec In: %.6lf [%.3lf~%.3lf]"), mCurrent_Value, mCurrent_SpecMin, mCurrent_SpecMax);
		AddLog(szLog, 0, m_nUnit);
	}
	return true;
}

//-----------------------------------------------------------------------------
//
//	ISP  Version Check
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_Version_Read(bool bAutoMode)	//nMode 0 = verion,model / 1 = error flag
{
	int i = 0;
	int errorCode = 0;
	TCHAR szLog[SIZE_OF_1K];
	byte WData[1];
	CString sTemp = _T("");

	unsigned int nSlaveAddress = 0x00;
	unsigned int nAddress = 0x00;
	int nBitIndex = 0;
	const int dCheckDataCount = 2;

	int nAddrLength = 2;

	TCHAR* pszCol[] = {_T("[Nor Flash Memory] ISP Version"), _T("[Nor Flash Memory] ISP Model") };

	//0 = [Nor Flash Memory] ISP Version Check
	//1 = [Nor Flash Memory] ISP Model Check
	for (i = 0; i < dCheckDataCount; i++)			//Verify
	{
		g_clMesCommunication[m_nUnit].m_dIspData[i] = 0x00;
		g_clMesCommunication[m_nUnit].m_dIspDataResult[i] = 1;
	}
	
	int mI2c_SpecMin = 0;
	int mI2c_SpecMax = 0;

	Sleep(10);

	for (i = 0; i < dCheckDataCount; i++)			//read
	{
		switch (i)
		{
		case 0:		//[Nor Flash Memory] ISP Version Check
			nSlaveAddress = 0x1A;
			nAddress = 0xC03C;
			nAddrLength = 2;
			break;
		case 1:		//[Nor Flash Memory] ISP Model Check
			nSlaveAddress = 0x1A;
			nAddress = 0xC040;
			nAddrLength = 2;
			break;
		default:
			break;
		}
		errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)nSlaveAddress, (unsigned short)nAddress, 2, WData, (unsigned short)1);	//Temperature1

		g_clMesCommunication[m_nUnit].m_dIspData[i] = WData[0];

		mI2c_SpecMin = (_ttof(EEpromVerifyData.vMinData[2 + i]));
		mI2c_SpecMax = (_ttof(EEpromVerifyData.vMaxData[2 + i]));

		if (g_clMesCommunication[m_nUnit].m_dIspData[i] == mI2c_SpecMax && errorCode == 0)
		{
			g_clMesCommunication[m_nUnit].m_dIspDataResult[i] = 1;
			_stprintf_s(szLog, SIZE_OF_1K, _T("%s Verify Ok: %d[%d]"), pszCol[i], g_clMesCommunication[m_nUnit].m_dIspData[i], mI2c_SpecMax);
			AddLog(szLog, 0, m_nUnit);
		}
		else
		{
			g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;		//I2C
			g_clMesCommunication[m_nUnit].m_dIspDataResult[i] = 0;
			_stprintf_s(szLog, SIZE_OF_1K, _T("%s Verify Ng: %d[%d]"), pszCol[i], g_clMesCommunication[m_nUnit].m_dIspData[i], mI2c_SpecMax);
			AddLog(szLog, 0, m_nUnit);

			sTemp.Format("%s", szLog);

			g_clMandoInspLog[m_nUnit].m_sNGList += sTemp;
			g_clMandoInspLog[m_nUnit].m_bInspRes = false;
			//! Main Display화면 Overlay NG List
			if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
			{
				g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("%s"), szLog);
				g_clMandoInspLog[m_nUnit].m_nNGCnt++;
			}
		}
		sTemp.Empty();
		Sleep(15);
	}

	return true;

}




//-----------------------------------------------------------------------------
//
//	Error Flag Check
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_ErrorFlag_Read(bool bAutoMode)	//nMode 0 = verion,model / 1 = error flag
{
	int i = 0;
	int errorCode = 0;
	TCHAR szLog[SIZE_OF_1K];
	byte WData[1];
	CString sTemp = _T("");

	unsigned int nSlaveAddress = 0x00;
	unsigned int nAddress = 0x00;
	int nBitIndex = 0;
	const int dCheckDataCount = 4;

	int nAddrLength = 2;
	byte VerifyData[dCheckDataCount] = {0x01 ,0x01 ,0x00 ,0x00 };

	TCHAR* pszCol[] = {
		_T("[Error Flag Check] Image Sensor") , _T("[Error Flag Check] PMIC")
		, _T("[Error Flag Check] Serializer1") , _T("[Error Flag Check] Serializer2") };


	//0 = [Error Flag Check] Image Sensor
	//1 = [Error Flag Check] PMIC
	//2 = [Error Flag Check] Serializer1
	//3 = [Error Flag Check] Serializer2
	for (i = 0; i < dCheckDataCount; i++)			//Verify
	{
		g_clMesCommunication[m_nUnit].m_dI2cData[i] = 0x00;
		g_clMesCommunication[m_nUnit].m_dI2cDataResult[i] = 1;
	}
	int mI2c_SpecMin = 0;
	int mI2c_SpecMax = 0;

	Sleep(10);

	for (i = 0; i < dCheckDataCount; i++)			//read
	{
		switch (i)
		{
		case 0:
			nBitIndex = 3;
			nSlaveAddress = 0x42;		//[Error Flag Check] Image Sensor
			nAddress = 0x02CD;
			nAddrLength = 2;
			break;
		case 1:
			nBitIndex = 3;
			nSlaveAddress = 0x42;		//[Error Flag Check] PMIC
			nAddress = 0x02D0;
			nAddrLength = 2;
			break;
		case 2:
			nBitIndex = 3;
			nSlaveAddress = 0x42;		//[Error Flag Check] Serializer1
			nAddress = 0x001D;
			nAddrLength = 2;
			break;
		case 3:
			nBitIndex = 2;
			nSlaveAddress = 0x42;		//[Error Flag Check] Serializer2
			nAddress = 0x001F;
			nAddrLength = 2;
			break;
		default:
			break;
		}
		errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)nSlaveAddress, (unsigned short)nAddress, 2, WData, (unsigned short)1);	//Temperature1
		
		byte bitData = (WData[0] & (1 << nBitIndex)) >> nBitIndex;
		g_clMesCommunication[m_nUnit].m_dI2cData[i] = bitData;

		//bit얻기
		
		//ndata = (WData[0] & (1 << nBitIndex)) >> nBitIndex;
		//_stprintf_s(szLog, SIZE_OF_1K, _T("Data :%d"), ndata);
		//AddLog(szLog, 0, 0);
		//return (data & (1 << n번째)) >>n번째;
		//data <<= n번째;
		//data >>=7;
		//return data



		if (g_clMesCommunication[m_nUnit].m_dI2cData[i] == VerifyData[i] && errorCode == 0)
		{
			g_clMesCommunication[m_nUnit].m_dI2cDataResult[i] = 1;
			_stprintf_s(szLog, SIZE_OF_1K, _T("%s Verify Ok: %02X[%02X]"), pszCol[i], g_clMesCommunication[m_nUnit].m_dI2cData[i], VerifyData[i]);
			AddLog(szLog, 0, m_nUnit);
		}
		else
		{
			g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;		//I2C
			g_clMesCommunication[m_nUnit].m_dI2cDataResult[i] = 0;
			_stprintf_s(szLog, SIZE_OF_1K, _T("%s Verify Ng: %02X[%02X]"), pszCol[i], g_clMesCommunication[m_nUnit].m_dI2cData[i], VerifyData[i]);
			AddLog(szLog, 0, m_nUnit);

			sTemp.Format("%s", szLog);

			g_clMandoInspLog[m_nUnit].m_sNGList += sTemp;
			g_clMandoInspLog[m_nUnit].m_bInspRes = false;
			//! Main Display화면 Overlay NG List
			if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
			{
				g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("%s"), szLog);
				g_clMandoInspLog[m_nUnit].m_nNGCnt++;
			}
		}


		sTemp.Empty();
		Sleep(15);
	}
	
	return true;

}

//-----------------------------------------------------------------------------
//
//	SENSOR VOLTAGE 검사
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_Sensor_Voltage_Read(bool bAutoMode)
{
	int errorCode = 0;
	CString sTemp = _T("");
	byte WData[5];
	int i = 0;
	TCHAR szLog[SIZE_OF_1K];
	TCHAR* pszCol[] = { _T("[AVDD]"), _T("[OVDD]") , _T("[DVDD]") };

	unsigned int nSlaveAddress = 0x1A;
	unsigned int nAddress = 0x0000;


	double voltageValue = 0.0;
	double mvoltage_SpecMin = 0.0;
	double mvoltage_SpecMax = 0.0;

	//Read후 [12]bits를 10진수 변환
	//interface Voltage값 = 변환값 (mV)
	//mV -> V로 변환하여 Log 기록

	Sleep(10);
	for (i = 0; i < 3; i++)			//read
	{
		switch (i)
		{
		case 0:		//AVDD
			nSlaveAddress = 0x1A;
			nAddress = 0x1E40;
			break;
		case 1:		//OVDD
			nSlaveAddress = 0x1A;
			nAddress = 0x1E42;
			break;
		case 2:		//DVDD
			nSlaveAddress = 0x1A;
			nAddress = 0x1E44;
			break;
		default:
			break;
		}
		errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)nSlaveAddress, (unsigned short)nAddress, 2, WData, (unsigned short)2);

		//WData[0] = 0xfd;
		//WData[1] = 0x0c;
		// 두 바이트를 12비트 숫자로 결합
		// wdata[0]이 상위 8비트, wdata[1]이 하위 4비트를 포함
		//int twelveBitValue = (WData[1] << 4) | (WData[0] & 0x0F);
		int twelveBitValue = (WData[1] << 8) | WData[0];


		g_clMesCommunication[m_nUnit].m_dMesSensorVoltage[i] = twelveBitValue / 1000.0;

		mvoltage_SpecMin = (_ttof(EEpromVerifyData.vMinData[42 + i]));
		mvoltage_SpecMax = (_ttof(EEpromVerifyData.vMaxData[42 + i]));

		voltageValue = g_clMesCommunication[m_nUnit].m_dMesSensorVoltage[i];

		if (voltageValue < mvoltage_SpecMin || voltageValue > mvoltage_SpecMax || errorCode != 0)
		{
			g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;		//I2C
			g_clMesCommunication[m_nUnit].m_nMesSensorVoltageResult[i] = 0;
			_stprintf_s(szLog, SIZE_OF_1K, _T("%s Spec Out: %.3lf[%.3lf ~ %.3lf]"), pszCol[i], voltageValue, mvoltage_SpecMin, mvoltage_SpecMax);
			AddLog(szLog, 0, m_nUnit);

			sTemp.Format("%s", szLog);

			g_clMandoInspLog[m_nUnit].m_sNGList += sTemp;
			g_clMandoInspLog[m_nUnit].m_bInspRes = false;
			//! Main Display화면 Overlay NG List
			if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
			{
				g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("%s"), szLog);
				g_clMandoInspLog[m_nUnit].m_nNGCnt++;
			}

		}
		else
		{

			g_clMesCommunication[m_nUnit].m_nMesSensorVoltageResult[i] = 1;
			_stprintf_s(szLog, SIZE_OF_1K, _T("%s Spec In: %.3lf[%.3lf ~ %.3lf]"), pszCol[i], voltageValue, mvoltage_SpecMin, mvoltage_SpecMax);
			AddLog(szLog, 0, m_nUnit);
		}
		sTemp.Empty();
		Sleep(15);
	}
	sTemp.Empty();
	return false;
}




//-----------------------------------------------------------------------------
//
//	SUPPLY VOLTAGE 검사
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_Supply_Voltage_Read(bool bAutoMode)
{
	double cur = 0.0;
	//SHM 김성봉 책임모델 2312115 추가												//lim240430
	//Des Port A = 0x40 , B = 0x40 , C = 0x41 , D = 0x41 
	//Register Address A = 0x04 , B = 0x02 , C = 0x04 , D = 0x02 
	bool	bRes = false;
	int errorCode = 0;
	bool bInspRtn = true;

	byte WData[1];
	int i = 0;
	byte pVolData1[8];
	memset(pVolData1, 0x00, 8);

	unsigned int nSlaveAddress = 0x41;
	unsigned int nAddress = 0x02;
	unsigned short kkkk = 0x0000;

	Sleep(10);

	//errorCode = MIU.m_pBoard->ReadI2CBurst((unsigned short)nSlaveAddress, (unsigned short)nAddress, 1, pVolData1, (unsigned short)2);	//Temperature1
	errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)nSlaveAddress, (unsigned short)nAddress, 1, pVolData1, (unsigned short)2);	//Temperature1

	//[14-3]bits를 10진수로 변환
	//V_bus = 변환 값 * 0.008;

	int decimalValue = (pVolData1[0] << 8) | pVolData1[1];
	int sumData = (decimalValue >> 3) & ~(1 << 12);

	CString sTemp;
	double dVoltageVal = sumData * 0.008;
	g_clMesCommunication[m_nUnit].m_dMesVoltage = dVoltageVal;




	double mVoltageValue = g_clMesCommunication[m_nUnit].m_dMesVoltage;
	double mVoltage_SpecMin = 0.0;
	double mVoltage_SpecMax = 0.0;


	mVoltage_SpecMin = (_ttof(EEpromVerifyData.vMinData[1]));	//11.5
	mVoltage_SpecMax = (_ttof(EEpromVerifyData.vMaxData[1]));	//12.5

	//g_clMandoInspLog[m_nUnit].dVoltage = dVoltageVal;

	
	if (mVoltageValue < mVoltage_SpecMin || mVoltageValue > mVoltage_SpecMax)
	{
		g_clMesCommunication[m_nUnit].m_nMesVoltageResult = 0;
		
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;	//VOLTAGE//XX
		sTemp.Format("Voltage Spec NG: %.6lf [%.3lf~%.3lf]", mVoltageValue, mVoltage_SpecMin, mVoltage_SpecMax);
		//! Main Display화면 Overlay NG List
		g_clMandoInspLog[m_nUnit].sDispNG[g_clMandoInspLog[m_nUnit].iNGCnt].Format("Voltage fail: %.6lf [%.2lf~%.2lf]", mVoltageValue, mVoltage_SpecMin, mVoltage_SpecMax);
		g_clMandoInspLog[m_nUnit].iNGCnt++;
		g_clMandoInspLog[m_nUnit].m_bInspRes = false;//LCB
		AddLog(sTemp, 0, m_nUnit);  //theApp.MainDlg->putListLog(sTemp);
		g_clMandoInspLog[m_nUnit].m_sNGList += sTemp;
	}
	else
	{
		g_clMesCommunication[m_nUnit].m_nMesVoltageResult = 1;
		sTemp.Format("Voltage Spec IN: %.6lf [%.3lf~%.3lf]", mVoltageValue, mVoltage_SpecMin, mVoltage_SpecMax);
		AddLog(sTemp, 0, m_nUnit);  //theApp.MainDlg->putListLog(sTemp);
	}

	sTemp.Empty();
	return false;
}

//-----------------------------------------------------------------------------
//
//	TEMPERATURE 검사
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_Temperature(bool bAutoMode)
{
	TCHAR szLog[SIZE_OF_1K];
	int errorCode = 0;
	bool bInspRtn = true;

	byte WData[1];

	unsigned char pTemData1[6];
	memset(pTemData1, 0x00, 6);
	unsigned char pTemData2[2];
	memset(pTemData2, 0x00, 2);
	unsigned char pTemData3[2];
	memset(pTemData3, 0x00, 2);

	int	m_Str_DataLength = 2;

	unsigned int nSlaveAddress = 0x49;	//read 0x48(온도센서1), 0x49(온도센서2) , write 0x44 , read 0x44 (온습도센서 = write 후 read)
	unsigned int nAddress = 0x00;		//(Address: 0x00 , 0x00,  0x2C) 
	////
	CString strTemp;
	CString m_Str_Data_Hex = _T("");
	CString rtnString;
	int tem1 = 0;
	int tem2 = 0;
	float tem3 = 0.0;

	WData[0] = 0x06;
	Sleep(10);
	errorCode += g_clLaonGrabberWrapper[m_nUnit].m_pBoard->WriteI2CBurst((unsigned short)0x44, (unsigned short)0x2C, 1, WData, (unsigned short)1);
	Sleep(20);
	errorCode += g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)0x44, (unsigned short)0x2C, 1, pTemData1, (unsigned short)6);	//Temperature1
	Sleep(1);
	errorCode += g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)0x48, (unsigned short)0x00, 1, pTemData2, (unsigned short)2);	//Temperature2
	Sleep(1);
	errorCode += g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)0x49, (unsigned short)0x00, 1, pTemData3, (unsigned short)2);	//Temperature3
	Sleep(1);
	if (errorCode)
	{
		m_Str_Data_Hex.Format("Error : %d", errorCode);
		return false;
	}
	//Slave Address = 0x44
	//Polynomial : 0x31 (x8*x5*x4+1)

	BYTE startCrc = 0xFF;
	BYTE* tmpArrPacket = new BYTE[4];
	int nLength = 2;
	tmpArrPacket[0] = pTemData1[0];// 0xBE;
	tmpArrPacket[1] = pTemData1[1];// 0xEF;
	startCrc = g_clPriInsp[m_nUnit].CRC_CalculateCRC8(startCrc, tmpArrPacket, nLength);

	if (pTemData1[2] == startCrc)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Temperature] TempReg CRC OK R:%d / C:%d"), pTemData1[2], startCrc);
		AddLog(szLog, 0, m_nUnit);
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Temperature] TempReg CRC FAIL R:%d / C:%d"), pTemData1[2], startCrc);
		AddLog(szLog, 1, m_nUnit);
		bInspRtn = false;
	}
	

	startCrc = 0xFF;
	tmpArrPacket[0] = pTemData1[3];// 0xBE;
	tmpArrPacket[1] = pTemData1[4];// 0xEF; 
	startCrc = g_clPriInsp[m_nUnit].CRC_CalculateCRC8(startCrc, tmpArrPacket, nLength);
	if (pTemData1[5] == startCrc)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Temperature] Humidity CRC OK R:%d / C:%d"), pTemData1[5], startCrc);
		AddLog(szLog, 0, m_nUnit);
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Temperature] Humidity CRC FAIL R:%d / C:%d"), pTemData1[5], startCrc);
		AddLog(szLog, 1, m_nUnit);
		bInspRtn = false;
	}
	

	//Temperature = -45 + 175 * (Temp_reg / (2의 16승 - 1))
	//Humidity = 100 * (Humi_reg / (2의 16승 - 1))
	//2의 16승 = 65536
	//tem1 = pTemData2[0];
	unsigned short t1Temp = 0;
	t1Temp = (unsigned short)((pTemData1[0] << 8) | pTemData1[1]); 
	g_clMandoInspLog[m_nUnit].m_dTemperatureResult[0] = -45.0 + 175.0 * ((double)t1Temp / (65536 - 1));
	//double Temperature = -45 + 175 * ((unsigned short)((Temp_reg[0] << 8) | Temp_reg[1]) / (double)(65535)-1);
	

	t1Temp = (unsigned short)((pTemData1[3] << 8) | pTemData1[4]);
	g_clMandoInspLog[m_nUnit].m_dHumidity = 100.0 * ((double)t1Temp / (65536 - 1));
	//double Humidity = 100 * ((unsigned short)((Humi_reg[0] << 8) | Humi_reg[1]) / (double)(65535)-1);
	/*
	Temp_reg 2Byte, CRC 1byte,
	Humi_reg 2Byte, CRC 1byte
	CRC 검사 수행한 후 아래 수식으로 온습도 측정
	Temperature = -45 + 175 * (Temp_reg / (216-1))
	Humidity = 100 * (Humi_reg / (216 - 1) 
	*/

	//Slave Address = 0x48
	tem1 = pTemData2[0];
	pTemData2[1] = ((unsigned char)0xFF & (pTemData2[1] >> 4));
	tem2 = pTemData2[1];

	g_clMandoInspLog[m_nUnit].m_dTemperatureResult[1] = tem1 + (tem2 * 0.0625);

	//Slave Address = 0x49
	tem1 = pTemData3[0];
	pTemData3[1] = ((unsigned char)0xFF & (pTemData3[1] >> 4));
	tem2 = pTemData3[1];

	g_clMandoInspLog[m_nUnit].m_dTemperatureResult[2] = tem1 + (tem2 * 0.0625);


	double dTempValue = 0.0;
	double dMinSpec = 0.0;
	double dMaxSpec = 0.0;

	g_clMesCommunication[m_nUnit].m_dMesTemperature[0] = g_clMandoInspLog[m_nUnit].m_dTemperatureResult[0];
	g_clMesCommunication[m_nUnit].m_dMesTemperature[1] = g_clMandoInspLog[m_nUnit].m_dTemperatureResult[1];
	g_clMesCommunication[m_nUnit].m_dMesTemperature[2] = g_clMandoInspLog[m_nUnit].m_dTemperatureResult[2];
	g_clMesCommunication[m_nUnit].m_dMesTemperature[3] = g_clMandoInspLog[m_nUnit].m_dHumidity;


	g_clMesCommunication[m_nUnit].m_dMesTemperatureResult[0] = 1;
	g_clMesCommunication[m_nUnit].m_dMesTemperatureResult[1] = 1;
	g_clMesCommunication[m_nUnit].m_dMesTemperatureResult[2] = 1;
	g_clMesCommunication[m_nUnit].m_dMesTemperatureResult[3] = 1;

	dMinSpec = g_clModelData[m_nUnit].m_TemperatureSpec[0];
	dMaxSpec = g_clModelData[m_nUnit].m_TemperatureSpec[1];
	dTempValue = g_clMandoInspLog[m_nUnit].m_dTemperatureResult[0];

	if (dTempValue < dMinSpec || dTempValue > dMaxSpec)
	{
		//NG
		g_clMesCommunication[m_nUnit].m_dMesTemperatureResult[0] = 0;
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Temperature] #1 NG: %f(%.2lf~%.2lf)"), dTempValue, dMinSpec, dMaxSpec);
		AddLog(szLog, 0, m_nUnit);
		bInspRtn = false;
	}
	else
	{
		//OK
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Temperature] #1 OK : %f(%.2lf~%.2lf)"), dTempValue, dMinSpec, dMaxSpec);
		AddLog(szLog, 0, m_nUnit);
	}
	dMinSpec = g_clModelData[m_nUnit].m_TemperatureSpec[2];
	dMaxSpec = g_clModelData[m_nUnit].m_TemperatureSpec[3];
	dTempValue = g_clMandoInspLog[m_nUnit].m_dTemperatureResult[1];

	if (dTempValue < dMinSpec || dTempValue > dMaxSpec)
	{
		//NG
		g_clMesCommunication[m_nUnit].m_dMesTemperatureResult[1] = 0;
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Temperature] #2 NG: %f(%.2lf~%.2lf)"), dTempValue, dMinSpec, dMaxSpec);
		AddLog(szLog, 0, m_nUnit);
		bInspRtn = false;
	}
	else
	{
		//OK
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Temperature] #2 OK : %f(%.2lf~%.2lf)"), dTempValue, dMinSpec, dMaxSpec);
		AddLog(szLog, 0, m_nUnit);
	}
	dMinSpec = g_clModelData[m_nUnit].m_TemperatureSpec[4];
	dMaxSpec = g_clModelData[m_nUnit].m_TemperatureSpec[5];
	dTempValue = g_clMandoInspLog[m_nUnit].m_dTemperatureResult[2];

	if (dTempValue < dMinSpec || dTempValue > dMaxSpec)
	{
		//NG
		g_clMesCommunication[m_nUnit].m_dMesTemperatureResult[2] = 0;
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Temperature] #3 NG: %f(%.2lf~%.2lf)"), dTempValue, dMinSpec, dMaxSpec);
		AddLog(szLog, 0, m_nUnit);
		bInspRtn = false;
	}
	else
	{
		//OK
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Temperature] #3 OK : %f(%.2lf~%.2lf)"), dTempValue, dMinSpec, dMaxSpec);
		AddLog(szLog, 0, m_nUnit);
	}

	dMinSpec = g_clModelData[m_nUnit].m_TemperatureSpec[6];
	dMaxSpec = g_clModelData[m_nUnit].m_TemperatureSpec[7];
	dTempValue = g_clMandoInspLog[m_nUnit].m_dHumidity;

	if (dTempValue < dMinSpec || dTempValue > dMaxSpec)
	{
		//NG
		g_clMesCommunication[m_nUnit].m_dMesTemperatureResult[3] = 0;
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Humidity] NG: %f(%.2lf~%.2lf)"), dTempValue, dMinSpec, dMaxSpec);
		AddLog(szLog, 0, m_nUnit);
		bInspRtn = false;
	}
	else
	{
		//OK
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Humidity] OK : %f(%.2lf~%.2lf)"), dTempValue, dMinSpec, dMaxSpec);
		AddLog(szLog, 0, m_nUnit);
	}


	if (bInspRtn == false)
	{
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;//XX
		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [Temperature NG]");
		g_clMandoInspLog[m_nUnit].m_bInspRes = false;
		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG [Temperature]"));
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
//
//	FUSE ID READ
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_3M_Register(bool mDarkMode)
{
	TCHAR szLog[SIZE_OF_1K];
	int errorCode = 0;
	byte WData[1];

	unsigned int nSlaveAddress = 0x1A;/// 0x50;  231110 수정
	unsigned int nAddress1 = 0x8A80;
	unsigned int nAddress2 = 0xBF61;
	if (mDarkMode == true)
	{
		//Dark Test
		WData[0] = 0x00;//HCG Mode
	}
	else
	{
		//White Test
		WData[0] = 0x01;//LCG Mode
	}
	
	//레지스터(0x301A)의 5번재 bit를 1로 set해줘야 Read가능
	//0x301A Register(0x10DC --> 0x10FC)
	//Slave ID : 0x10
	Sleep(15);
	errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->WriteI2CBurst((unsigned short)nSlaveAddress, (unsigned short)nAddress1, 2, WData, (unsigned short)1);
	if (errorCode)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[0x8A80] Write Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}

	_stprintf_s(szLog, SIZE_OF_1K, _T("[0x8A80] Set = %d"), WData[0]);
	AddLog(szLog, 0, m_nUnit);
	Sleep(15);
	errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->WriteI2CBurst((unsigned short)nSlaveAddress, (unsigned short)nAddress2, 2, WData, (unsigned short)1);
	if (errorCode)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[0xBF61] Write Fail"));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	_stprintf_s(szLog, SIZE_OF_1K, _T("[0xBF61] Set = %d"), WData[0]);
	AddLog(szLog, 0, m_nUnit);
	return true;
}


//-----------------------------------------------------------------------------
//
//	FUSE ID READ
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_Test_FuseIDRead(bool bAutoMode)
{
	TCHAR szLog[SIZE_OF_1K];
	int errorCode = 0;
	byte WData[1];

	unsigned char pData[MAX_PATH];
	memset(pData, 0x00, sizeof(pData));

	BYTE	m_Str_DataLength = (byte)8;

	unsigned int nSlaveAddress = 0x10;
	unsigned int nAddress = 0x31F4;		//(Address: 0x31F4 ~ 0x31FA) 
										//읽은 데이터를 아래와 같이 16진수 문자열로 만든다.
	g_clMesCommunication[m_nUnit].m_nMesI2CResult = 1;
	CString m_Str_Data_Hex = _T("");

	g_clMesCommunication[m_nUnit].m_sMesfuseID.Format(_T("EMPTY"));

	WData[0] = 0xFC;
	//레지스터(0x301A)의 5번재 bit를 1로 set해줘야 Read가능
	//0x301A Register(0x10DC --> 0x10FC)
	//Slave ID : 0x10
	errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->WriteI2CBurst((unsigned short)0x10, (unsigned short)0x301B, 2, WData, (unsigned short)1);
	Sleep(20);
	//errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)nSlaveAddress, (unsigned short)0x301B, 2, pData, (unsigned short)1);

	errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)nSlaveAddress, (unsigned short)nAddress, 2, pData, (unsigned short)8);
	if (errorCode)
	{
		g_clMesCommunication[m_nUnit].m_nsMesfuseIDResult = 0;
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;	//XX
		_stprintf_s(szLog, SIZE_OF_1K, _T("FUSE ID NG %d"), errorCode);
		AddLog(szLog, 0, m_nUnit);
		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [FUSE ID NG]");
		g_clMandoInspLog[m_nUnit].m_bInspRes = false;
		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG [FUSE ID]"));
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}

		return false;
	}
	else
	{
		g_clMesCommunication[m_nUnit].m_nsMesfuseIDResult = 1;
		CString strTemp;
		for (int i = 0; i < (int)m_Str_DataLength; i++)//nReadByteCount 
		{
			strTemp.AppendFormat("%02X", (char*)pData[i]);
		}
		_stprintf_s(g_clTaskWork[m_nUnit].m_szFuseId, SIZE_OF_100BYTE, _T("%s"), (TCHAR*)(LPCTSTR)strTemp);
		g_clMesCommunication[m_nUnit].m_sMesfuseID.Format(_T("%s"), g_clTaskWork[m_nUnit].m_szFuseId);
	}

	_stprintf_s(szLog, SIZE_OF_1K, _T("FUSE ID:%s"), g_clTaskWork[m_nUnit].m_szFuseId);
	AddLog(szLog, 0, m_nUnit);
	return true;


}

//-----------------------------------------------------------------------------
//
//	TEST I2C SENSOR READ 검사
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_Test_SensorRead(bool bAutoMode)
{
	TCHAR szLog[SIZE_OF_1K];
	int errorCode = 0;
	int i = 0;
	unsigned char pData[MAX_PATH];
	memset(pData, 0x00, sizeof(pData));

	BYTE	m_Str_DataLength = (byte)8;

	unsigned int nSlaveAddress = 0x1A;
	unsigned int nAddress = 0x7E82;		//0x765C;		//(Address: 0x765C ~ 0x7666) 

	//읽은 데이터를 아래와 같이 16진수 문자열로 만든다.
	g_clMesCommunication[m_nUnit].m_nMesI2CResult = 1;
	CString m_Str_Data_Hex = _T("");
	_stprintf_s(g_clMesCommunication[m_nUnit].m_sMesI2cSensorID, SIZE_OF_100BYTE, _T(""));


	Sleep(10);
	errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)nSlaveAddress, (unsigned short)nAddress, 2, pData, (unsigned short)m_Str_DataLength);
	if (errorCode)
	{
		g_clMesCommunication[m_nUnit].m_nMesI2CResult = 0;
		m_Str_Data_Hex.Format("Error : %d", errorCode);
		return false;
	}
	else
	{
		CString strTemp = _T("");
		for (int i = 0; i < (int)m_Str_DataLength; i++)//nReadByteCount 
		{
			strTemp.AppendFormat("%02X", (char*)pData[i]);
		}
		_stprintf_s(g_clMesCommunication[m_nUnit].m_sMesI2cSensorID, SIZE_OF_100BYTE, _T("%s"), (TCHAR*)(LPCTSTR)strTemp);

		//g_clMesCommunication[m_nUnit].m_sMesI2cSensorID.Format(_T("%s"), g_clTaskWork[m_nUnit].m_szI2cSensorLot);
	}
	

	if (strcmp(g_clMesCommunication[m_nUnit].m_sMesI2cSensorID, "0000000000000000") == 0)// || strcmp(g_clTaskWork[m_nUnit].m_szI2cSensorLot, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF") == 0)
	{
		g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;	//sensor id
		g_clMesCommunication[m_nUnit].m_nMesI2CResult = 0;
		_stprintf_s(szLog, SIZE_OF_1K, _T("[I2C]NG SENSOR ID:%s"), g_clMesCommunication[m_nUnit].m_sMesI2cSensorID);
		AddLog(szLog, 0, m_nUnit);
		g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [SENSOR ID NG]");
		g_clMandoInspLog[m_nUnit].m_bInspRes = false;
		if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
		{
			g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("NG [SENSOR ID]"));
			g_clMandoInspLog[m_nUnit].m_nNGCnt++;
		}
		return false;
	}
	_stprintf_s(szLog, SIZE_OF_1K, _T("[I2C] SENSOR ID:%s"), g_clMesCommunication[m_nUnit].m_sMesI2cSensorID);
	AddLog(szLog, 0, m_nUnit);
	return true;
}
//-----------------------------------------------------------------------------
//
//	DISTORTION
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_Distortion(BYTE* img, bool bAutoMode)
{
	

	return true;
}

//-----------------------------------------------------------------------------
//
//	TEST PATTERN 검사
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_TestPattern(bool bAutoMode)
{

	g_clTaskWork[m_nUnit].m_bOutputCheck[2] = true;//init

	TCHAR szLog[SIZE_OF_1K];
	TCHAR szPath[SIZE_OF_1K];
	int errorCode = 0;
	CFileFind clFinder;
	int readLen;
	byte nData[2];

	g_clMandoInspLog[m_nUnit].m_TpTestResult[0] = false;
	g_clMandoInspLog[m_nUnit].m_TpTestResult[1] = false;
	
	//-- Test Image 변경
	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			nData[0] = 0x01;
			nData[1] = 0x00;
			//nData = 0x0100;
		}
		else
		{
			nData[0] = 0x00;
			nData[1] = 0x03;
			//nData = 0x0003;
		}
		//if (m_bThreadUsed == false) return -1;  //Thread 사용 안하니 Pass
		//cTestPat_Ref_buf = (unsigned char*)malloc(g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight);

		errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->WriteI2CBurst((unsigned short)0x10, (unsigned short)0x3070, 2, nData, (unsigned short)2);
		if (errorCode)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[I2C] SET WriteI2CBurst FAIL "));
			AddLog(szLog, 0, m_nUnit);
			return false;
		}
		else
		{

			Sleep(1500);
			if (memcmp(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer_TP_Ref1[i], g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize()) == 0)		//비교
			{
				//ok
				g_clMandoInspLog[m_nUnit].m_TpTestResult[i] = true;
				if (g_clMandoInspLog[m_nUnit].m_TpTestResult[0] == true && g_clMandoInspLog[m_nUnit].m_TpTestResult[1] == true)
				{
					g_clTaskWork[m_nUnit].m_bOutputCheck[2] = true;//i2c
					g_clMandoInspLog[m_nUnit].m_sI2C.Format("OK");
					g_clMesCommunication[m_nUnit].m_sMesI2C.Format(_T("100.00"));
					g_clMesCommunication[m_nUnit].m_nMesI2CResult = 1;

					_stprintf_s(szLog, SIZE_OF_1K, _T("[I2C] TEST_PATTERN OK "));
					AddLog(szLog, 0, m_nUnit);
				}
			}
			else
			{
				//ng
				g_clTaskWork[m_nUnit].m_bOutputCheck[2] = false;
				g_clMandoInspLog[m_nUnit].m_TpTestResult[i] = false;
				_stprintf_s(szLog, SIZE_OF_1K, _T("[I2C] TEST_PATTERN TEST #%d FAIL ") , i + 1);
				AddLog(szLog, 0, m_nUnit);
			}
		}
		Sleep(500);
	}

	
	nData[0] = 0x00;
	nData[1] = 0x00;

	errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->WriteI2CBurst((unsigned short)0x10, (unsigned short)0x3070, 2, nData, (unsigned short)2);
	if (errorCode)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[I2C] INIT WriteI2CBurst FAIL "));
		AddLog(szLog, 0, m_nUnit);
		return false;
	}
	bool i2cRtn = g_clTaskWork[m_nUnit].m_bOutputCheck[2];
	return i2cRtn;
}

////////TESLA ADD
int CPRIFunc_Insp::func_CalibrateImageEmbedded(TCHAR *ptszImgPath, CString &sResult)
{
	return -1;
}
int CPRIFunc_Insp::func_EvaluateUndistortImage(TCHAR *ptszImgPath, CString &sResult)
{
	int nResult = -1;
	//DWORD dwStartTime = GetTickCount();
	//WCHAR wstrImagePath[1024];
	//int nLen = strlen(ptszImgPath) + 1;

	//MultiByteToWideChar(CP_ACP, 0, ptszImgPath, -1, wstrImagePath, nLen - 1);
	//wstrImagePath[nLen - 1] = 0;

	//EVALUATE_RESULT *ptagEvaluateResult = EvaluateUndistortImage(wstrImagePath, 36, 24, true);

	//if (ptagEvaluateResult != NULL)
	//{
	//	CString strResult = _T("Rectangle Test Result\r\n");
	//	CString strTemp;

	//	for (int i = 0; i < 12; i++)
	//	{
	//		strTemp.Format(_T("[%02d] %lf\r\n"), i, (ptagEvaluateResult->fRectangleLineResult[i]));
	//		strResult += strTemp;
	//	}

	//	strTemp.Format(_T("Col Straight Avrg : %lf\r\n"), ptagEvaluateResult->dStraightCols);
	//	strResult += strTemp;

	//	strTemp.Format(_T("Row Straight Avrg : %lf\r\n"), ptagEvaluateResult->dStraightRows);
	//	strResult += strTemp;

	//	strResult += _T("Dist (Average, Deviation, Min, Max)\r\n");

	//	strTemp.Format(_T("Col (%lf, %lf, %lf, %lf)\r\n"),
	//		ptagEvaluateResult->dColDistAverage,
	//		ptagEvaluateResult->dColDistDeviation,
	//		ptagEvaluateResult->dColDistMin,
	//		ptagEvaluateResult->dColDistMax);

	//	strResult += strTemp;

	//	strTemp.Format(_T("Row (%lf, %lf, %lf, %lf)\r\n"),
	//		ptagEvaluateResult->dRowDistAverage,
	//		ptagEvaluateResult->dRowDistDeviation,
	//		ptagEvaluateResult->dRowDistMin,
	//		ptagEvaluateResult->dRowDistMax);

	//	strResult += strTemp;

	//	DWORD dwEndTime = GetTickCount() - dwStartTime;
	//	strTemp.Format(_T("Time - %dms"), dwEndTime);

	//	strResult += strTemp;

	//	sResult = strResult;

	//	//for (auto val : ptagEvaluateResult->vecRectangleLineResult)
	//	//{
	//	//	if (val)
	//	//		delete val;
	//	//	val = NULL;
	//	//}
	//	//ptagEvaluateResult = NULL;
	//	//delete ptagEvaluateResult;
	//}
	//else
	//{
	//	CString strError;
	//	DWORD dwLastError = GetLastError();

	//	nResult = (int)dwLastError;

	//	switch (dwLastError)
	//	{
	//	case CALIBRATIONDLL_NOT_INITIALIZED:
	//		strError = _T("Blob parameters are not set.");
	//		break;
	//	case CALIBRATIONDLL_INVALID_IMAGE_PATH:
	//		strError = _T("Invalid Image Path.");
	//		break;
	//	case CALIBRATIONDLL_IMAGE_NOT_EXIST:
	//		strError = _T("Image file is not exist.");
	//		break;
	//	case CALIBRATIONDLL_EXE_NOT_EXIST:
	//		strError = _T("TeslaCal.exe is not exist.");
	//		break;
	//	case CALIBRATIONDLL_FAILED_EXE_RUN:
	//		strError = _T("Failed to run TeslaCal.exe");
	//		break;
	//	case CALIBRATIONDLL_FAILED_CALIBRATION:
	//		strError = _T("Failed to run calibraation.");
	//		break;
	//	case CALIBRATIONDLL_INVALID_OBJECT_SIZE:
	//		strError = _T("Invalid object size.");
	//		break;
	//	case CALIBRATIONDLL_FAILED_FIND_CIRCLE:
	//		strError = _T("Failed to find circles.");
	//		break;
	//	case CALIBRATIONDLL_FAILED_GENERATE_AREA:
	//		strError = _T("Failed to generate areas.");
	//		break;
	//	default:
	//		strError = _T("Unknown error.");
	//		break;
	//	}
	//	sResult = strError;
	//}

	return nResult;
}
int CPRIFunc_Insp::func_EvaluateDefault(TCHAR *ptszImgPath, CString &sResult)
{
	//int nResult = -1;
	//DWORD dwStartTime = GetTickCount();
	//WCHAR wstrImagePath[1024];
	//int nLen = strlen(ptszImgPath) + 1;

	//MultiByteToWideChar(CP_ACP, 0, ptszImgPath, -1, wstrImagePath, nLen - 1);
	//wstrImagePath[nLen - 1] = 0;

	//dwStartTime = GetTickCount();

	//EVALUATE_RESULT *ptagEvaluateDefault = EvaluateUndistortDefault(wstrImagePath, 36, 24, true);
	//if (ptagEvaluateDefault != NULL)
	//{
	//	CString strResult = _T("Rectangle Test Result - Default Value\r\n");
	//	CString strTemp;

	//	for (int i = 0; i < 12; i++)
	//	{
	//		strTemp.Format(_T("[%02d] %lf\r\n"), i, (ptagEvaluateDefault->fRectangleLineResult[i]));
	//		strResult += strTemp;
	//	}

	//	strTemp.Format(_T("Col Straight Avrg : %lf\r\n"), ptagEvaluateDefault->dStraightCols);
	//	strResult += strTemp;

	//	strTemp.Format(_T("Row Straight Avrg : %lf\r\n"), ptagEvaluateDefault->dStraightRows);
	//	strResult += strTemp;

	//	strResult += _T("Dist (Average, Deviation, Min, Max)\r\n");

	//	strTemp.Format(_T("Col (%lf, %lf, %lf, %lf)\r\n"),
	//		ptagEvaluateDefault->dColDistAverage,
	//		ptagEvaluateDefault->dColDistDeviation,
	//		ptagEvaluateDefault->dColDistMin,
	//		ptagEvaluateDefault->dColDistMax);

	//	strResult += strTemp;

	//	strTemp.Format(_T("Row (%lf, %lf, %lf, %lf)\r\n"),
	//		ptagEvaluateDefault->dRowDistAverage,
	//		ptagEvaluateDefault->dRowDistDeviation,
	//		ptagEvaluateDefault->dRowDistMin,
	//		ptagEvaluateDefault->dRowDistMax);

	//	strResult += strTemp;

	//	DWORD dwEndTime = GetTickCount() - dwStartTime;
	//	strTemp.Format(_T("Time - %dms"), dwEndTime);

	//	strResult += strTemp;

	//	sResult = strResult;

	//	//for (auto val : ptagEvaluateDefault->vecRectangleLineResult)
	//	//{
	//	//	if (val)
	//	//		delete val;
	//	//	val = NULL;
	//	//}

	//	//delete ptagEvaluateDefault;
	//}
	//else
	//{
	//	CString strError;
	//	DWORD dwLastError = GetLastError();

	//	switch (dwLastError)
	//	{
	//	case CALIBRATIONDLL_NOT_INITIALIZED:
	//		strError = _T("Blob parameters are not set.");
	//		break;
	//	case CALIBRATIONDLL_INVALID_IMAGE_PATH:
	//		strError = _T("Invalid Image Path.");
	//		break;
	//	case CALIBRATIONDLL_IMAGE_NOT_EXIST:
	//		strError = _T("Image file is not exist.");
	//		break;
	//	case CALIBRATIONDLL_EXE_NOT_EXIST:
	//		strError = _T("TeslaCal.exe is not exist.");
	//		break;
	//	case CALIBRATIONDLL_FAILED_EXE_RUN:
	//		strError = _T("Failed to run TeslaCal.exe");
	//		break;
	//	case CALIBRATIONDLL_FAILED_CALIBRATION:
	//		strError = _T("Failed to run calibraation.");
	//		break;
	//	case CALIBRATIONDLL_INVALID_OBJECT_SIZE:
	//		strError = _T("Invalid object size.");
	//		break;
	//	case CALIBRATIONDLL_FAILED_FIND_CIRCLE:
	//		strError = _T("Failed to find circles.");
	//		break;
	//	case CALIBRATIONDLL_FAILED_GENERATE_AREA:
	//		strError = _T("Failed to generate areas.");
	//		break;
	//	default:
	//		strError = _T("Unknown error.");
	//		break;
	//	}
	//	sResult = strError;
	//}
	return -1;
}
void CPRIFunc_Insp::CRC_FinalChecksum(BYTE crcValue)
{
	crcValue ^= 0x00;
}

//-----------------------------------------------------------------------------
//
//	광원 밝기 검사
//
//-----------------------------------------------------------------------------
bool CPRIFunc_Insp::func_Insp_LightTest(int mLightIndex, bool bAutoMode)
{
	TCHAR szLog[SIZE_OF_1K];
	int i = 0;
	
	int width = 0;	
	int mStartX = 0;
	int mStartY = 0;
	int nWidth = g_clModelData[m_nUnit].m_nWidth;
	int nHeight = g_clModelData[m_nUnit].m_nHeight;
	int dRoiCount = 0;
	int dGreenBright = 0;

	CPoint m_clPtBrightPos[10];

	TCHAR* pszChartCol[] = {
		_T("[Saturation] TOP_Chart_Bright_LT"), _T("[Saturation] TOP_Chart_Bright_LB") ,
		_T("[Saturation] TOP_Chart_Bright_RB") , _T("[Saturation] TOP_Chart_Bright_RT") ,
		_T("[Saturation] Side_Chart_Bright_LT") , _T("[Saturation] Side_Chart_Bright_LB"),
		_T("[Saturation] Side_Chart_Bright_RT") , _T("[Saturation] Side_Chart_Bright_RB") };

	TCHAR* pszOcCol[] = { _T("[RI] Oc_Bright_CENTER") };
		//_T("[RI] Oc_Bright_LT"), _T("[RI] Oc_Bright_LB") ,
		//_T("[RI] Oc_Bright_RB") , _T("[RI] Oc_Bright_RT")};
	if (mLightIndex == 0)
	{
		//chart RGB Light
		dRoiCount = 8;
#if (____MACHINE_NAME == MODEL_FRONT_100)
		//Top Chart LT
		m_clPtBrightPos[0].x = 610;
		m_clPtBrightPos[0].y = 260;
		//Top Chart LB
		m_clPtBrightPos[1].x = 610;
		m_clPtBrightPos[1].y = 800;
		//Top Chart RB
		m_clPtBrightPos[2].x = 1320;
		m_clPtBrightPos[2].y = 800;
		//Top Chart RT
		m_clPtBrightPos[3].x = 1320;
		m_clPtBrightPos[3].y = 260;
		//
		//
		//Side Chart LT
		m_clPtBrightPos[4].x = 150;
		m_clPtBrightPos[4].y = 240;
		//Side Chart LB
		m_clPtBrightPos[5].x = 150;
		m_clPtBrightPos[5].y = 850;
		//Side Chart RT
		m_clPtBrightPos[6].x = 1750;
		m_clPtBrightPos[6].y = 240;
		//Side Chart RB
		m_clPtBrightPos[7].x = 1750;
		m_clPtBrightPos[7].y = 850;
#else
		//Top Chart LT
		m_clPtBrightPos[0].x = 736;
		m_clPtBrightPos[0].y = 400;
		//Top Chart LB
		m_clPtBrightPos[1].x = 736;
		m_clPtBrightPos[1].y = 705;
		//Top Chart RB
		m_clPtBrightPos[2].x = 1170;
		m_clPtBrightPos[2].y = 705;
		//Top Chart RT
		m_clPtBrightPos[3].x = 1170;
		m_clPtBrightPos[3].y = 400;
		//
		//
		//Side Chart LT
		m_clPtBrightPos[4].x = 380;
		m_clPtBrightPos[4].y = 280;
		//Side Chart LB
		m_clPtBrightPos[5].x = 380;
		m_clPtBrightPos[5].y = 820;
		//Side Chart RT
		m_clPtBrightPos[6].x = 1540;
		m_clPtBrightPos[6].y = 280;
		//Side Chart RB
		m_clPtBrightPos[7].x = 1540;
		m_clPtBrightPos[7].y = 820;
#endif
	}
	else
	{
		dRoiCount = 1;
		m_clPtBrightPos[0].x = nWidth / 2;
		m_clPtBrightPos[0].y = nHeight / 2;

//#if (____MACHINE_NAME == MODEL_FRONT_100)
//		//이물광원  LT
//		m_clPtBrightPos[0].x = 420;
//		m_clPtBrightPos[0].y = 230;
//		//이물광원 LB
//		m_clPtBrightPos[1].x = 420;
//		m_clPtBrightPos[1].y = 820;
//		//이물광원 RB
//		m_clPtBrightPos[2].x = 1530;
//		m_clPtBrightPos[2].y = 820;
//		//이물광원 RT
//		m_clPtBrightPos[3].x = 1530;
//		m_clPtBrightPos[3].y = 230;
//#else
//		//이물광원  LT
//		m_clPtBrightPos[0].x = 420;
//		m_clPtBrightPos[0].y = 230;
//		//이물광원 LB
//		m_clPtBrightPos[1].x = 420;
//		m_clPtBrightPos[1].y = 820;
//		//이물광원 RB
//		m_clPtBrightPos[2].x = 1530;
//		m_clPtBrightPos[2].y = 820;
//		//이물광원 RT
//		m_clPtBrightPos[3].x = 1530;
//		m_clPtBrightPos[3].y = 230;
//#endif
	}
	int pos = 0;
	int mBrightValue = 0;
	double mBright_SpecMin = 0.0;
	double mBright_SpecMax = 0.0;


	TCHAR szPos[SIZE_OF_100BYTE];
	g_clVision.ClearOverlay(m_nUnit);
	for (i = 0; i < dRoiCount; i++)
	{
		width = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_PITCH, NULL);
		pos = (m_clPtBrightPos[i].y * width) + m_clPtBrightPos[i].x;
		if (bAutoMode == false)
		{
			g_clVision.DrawMOverlayCross(m_nUnit, m_nUnit, m_clPtBrightPos[i], 20, M_COLOR_CYAN, 2);// TRUE); 
			_stprintf_s(szPos, SIZE_OF_100BYTE, _T("Roi-%d"), i);
		}
		dGreenBright = g_clVision.m_pImgBuff[m_nUnit][1][pos];
		if (mLightIndex == 0)
		{
			mBright_SpecMin = (_ttof(EEpromVerifyData.vMinData[24 + i]));	//11.5
			mBright_SpecMax = (_ttof(EEpromVerifyData.vMaxData[24 + i]));	//12.5
			g_clMesCommunication[m_nUnit].m_dChartBright[i] = dGreenBright;

			mBrightValue = g_clMesCommunication[m_nUnit].m_dChartBright[i];
			if (mBrightValue < mBright_SpecMin || mBrightValue > mBright_SpecMax)
			{
				g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;	//BRIGHT CHART
				g_clMesCommunication[m_nUnit].m_dChartBrightResult[i] = 0;
				_stprintf_s(szLog, SIZE_OF_1K, _T("%s Bright Spec Out :%d [%.1lf~%.1lf]"), pszChartCol[i], mBrightValue, mBright_SpecMin, mBright_SpecMax);

				g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [CHART BRIGHT NG]");
				g_clMandoInspLog[m_nUnit].m_bInspRes = false;
				if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
				{
					g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("%s"), szLog);
					g_clMandoInspLog[m_nUnit].m_nNGCnt++;
				}
			}
			else
			{
				g_clMesCommunication[m_nUnit].m_dChartBrightResult[i] = 1;
				_stprintf_s(szLog, SIZE_OF_1K, _T("%s Bright Spec In :%d [%.1lf~%.1lf]"), pszChartCol[i], mBrightValue, mBright_SpecMin, mBright_SpecMax);
			}
			//CHART AVG
			AddLog(szLog, 0, m_nUnit, false);
		}
		else
		{
			mBright_SpecMin = (_ttof(EEpromVerifyData.vMinData[33 + i]));	//11.5
			mBright_SpecMax = (_ttof(EEpromVerifyData.vMaxData[33 + i]));	//12.5
			g_clMesCommunication[m_nUnit].m_dOcBright[i] = dGreenBright;

			mBrightValue = g_clMesCommunication[m_nUnit].m_dOcBright[i];
			if (mBrightValue < mBright_SpecMin || mBrightValue > mBright_SpecMax)
			{
				g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;	//BRIGHT OC
				g_clMesCommunication[m_nUnit].m_dOcBrightResult[i] = 0;
				_stprintf_s(szLog, SIZE_OF_1K, _T("%s Spec Out :%d [%.1lf~%.1lf]"), pszOcCol[i], mBrightValue, mBright_SpecMin, mBright_SpecMax);


				g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [OC BRIGHT NG]");
				g_clMandoInspLog[m_nUnit].m_bInspRes = false;
				if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
				{
					g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("%s"), szLog);
					g_clMandoInspLog[m_nUnit].m_nNGCnt++;
				}

			}
			else
			{
				g_clMesCommunication[m_nUnit].m_dOcBrightResult[i] = 1;
				_stprintf_s(szLog, SIZE_OF_1K, _T("%s Spec In :%d [%.1lf~%.1lf]"), pszOcCol[i], mBrightValue, mBright_SpecMin, mBright_SpecMax);

			}
			AddLog(szLog, 0, m_nUnit, false);
		}
	}

	mBrightValue = 0;
	if (mLightIndex == 0)
	{
		//Chart Average
		double dChartAverage = 0.0;
		for (i = 0; i < 4; i++)
		{
			dChartAverage += g_clMesCommunication[m_nUnit].m_dChartBright[i];
		}
		g_clMesCommunication[m_nUnit].m_dChartBright[8] = dChartAverage / 4;
		mBrightValue = g_clMesCommunication[m_nUnit].m_dChartBright[8];

		mBright_SpecMin = (_ttof(EEpromVerifyData.vMinData[28]));	//11.5
		mBright_SpecMax = (_ttof(EEpromVerifyData.vMaxData[28]));	//12.5

		if (mBrightValue < mBright_SpecMin || mBrightValue > mBright_SpecMax)
		{
			g_clMesCommunication[m_nUnit].m_nMesFinalResult = 0;	//BRIGHT CHART
			g_clMesCommunication[m_nUnit].m_dChartBrightResult[8] = 0;
			_stprintf_s(szLog, SIZE_OF_1K, _T("[Saturation] TOP_Chart_Bright_Avg Spec Out :%d [%.1lf~%.1lf]"), mBrightValue, mBright_SpecMin, mBright_SpecMax);

			g_clMandoInspLog[m_nUnit].m_sNGList += _T(" [CHART AVG BRIGHT NG]");
			g_clMandoInspLog[m_nUnit].m_bInspRes = false;
			if (g_clMandoInspLog[m_nUnit].m_nNGCnt < 30)
			{
				g_clMandoInspLog[m_nUnit].m_sDispNG[g_clMandoInspLog[m_nUnit].m_nNGCnt].Format(_T("%s"), szLog);
				g_clMandoInspLog[m_nUnit].m_nNGCnt++;
			}
		}
		else
		{
			g_clMesCommunication[m_nUnit].m_dChartBrightResult[8] = 1;
			_stprintf_s(szLog, SIZE_OF_1K, _T("[Saturation] TOP_Chart_Bright_Avg Spec In :%d [%.1lf~%.1lf]"), mBrightValue, mBright_SpecMin, mBright_SpecMax);
		}
		//CHART AVG
		AddLog(szLog, 0, m_nUnit, false);
	}
	g_clVision.DrawOverlayAll(m_nUnit);

	return true;
}
BYTE CPRIFunc_Insp::CRC_CalculateCRC8(BYTE Crc_StartValue8, BYTE* Crc_DataPtr, int Crc_Length)
{
	int count = 0;
	//const uint8_t crc8_table[] =
	static byte Crc8Table22[256] = 
	{
		0x00, 0x1D, 0x3A, 0x27, 0x74, 0x69, 0x4E, 0x53, 0xE8, 0xF5, 0xD2, 0xCF, 0x9C, 0x81, 0xA6, 0xBB,
		0xCD, 0xD0, 0xF7, 0xEA, 0xB9, 0xA4, 0x83, 0x9E, 0x25, 0x38, 0x1F, 0x02, 0x51, 0x4C, 0x6B, 0x76,
		0x87, 0x9A, 0xBD, 0xA0, 0xF3, 0xEE, 0xC9, 0xD4, 0x6F, 0x72, 0x55, 0x48, 0x1B, 0x06, 0x21, 0x3C,
		0x4A, 0x57, 0x70, 0x6D, 0x3E, 0x23, 0x04, 0x19, 0xA2, 0xBF, 0x98, 0x85, 0xD6, 0xCB, 0xEC, 0xF1,
		0x13, 0x0E, 0x29, 0x34, 0x67, 0x7A, 0x5D, 0x40, 0xFB, 0xE6, 0xC1, 0xDC, 0x8F, 0x92, 0xB5, 0xA8,
		0xDE, 0xC3, 0xE4, 0xF9, 0xAA, 0xB7, 0x90, 0x8D, 0x36, 0x2B, 0x0C, 0x11, 0x42, 0x5F, 0x78, 0x65,
		0x94, 0x89, 0xAE, 0xB3, 0xE0, 0xFD, 0xDA, 0xC7, 0x7C, 0x61, 0x46, 0x5B, 0x08, 0x15, 0x32, 0x2F,
		0x59, 0x44, 0x63, 0x7E, 0x2D, 0x30, 0x17, 0x0A, 0xB1, 0xAC, 0x8B, 0x96, 0xC5, 0xD8, 0xFF, 0xE2,
		0x26, 0x3B, 0x1C, 0x01, 0x52, 0x4F, 0x68, 0x75, 0xCE, 0xD3, 0xF4, 0xE9, 0xBA, 0xA7, 0x80, 0x9D,
		0xEB, 0xF6, 0xD1, 0xCC, 0x9F, 0x82, 0xA5, 0xB8, 0x03, 0x1E, 0x39, 0x24, 0x77, 0x6A, 0x4D, 0x50,
		0xA1, 0xBC, 0x9B, 0x86, 0xD5, 0xC8, 0xEF, 0xF2, 0x49, 0x54, 0x73, 0x6E, 0x3D, 0x20, 0x07, 0x1A,
		0x6C, 0x71, 0x56, 0x4B, 0x18, 0x05, 0x22, 0x3F, 0x84, 0x99, 0xBE, 0xA3, 0xF0, 0xED, 0xCA, 0xD7,
		0x35, 0x28, 0x0F, 0x12, 0x41, 0x5C, 0x7B, 0x66, 0xDD, 0xC0, 0xE7, 0xFA, 0xA9, 0xB4, 0x93, 0x8E,
		0xF8, 0xE5, 0xC2, 0xDF, 0x8C, 0x91, 0xB6, 0xAB, 0x10, 0x0D, 0x2A, 0x37, 0x64, 0x79, 0x5E, 0x43,
		0xB2, 0xAF, 0x88, 0x95, 0xC6, 0xDB, 0xFC, 0xE1, 0x5A, 0x47, 0x60, 0x7D, 0x2E, 0x33, 0x14, 0x09,
		0x7F, 0x62, 0x45, 0x58, 0x0B, 0x16, 0x31, 0x2C, 0x97, 0x8A, 0xAD, 0xB0, 0xE3, 0xFE, 0xD9, 0xC4
	};

	BYTE crc_value = Crc_StartValue8;

	for (count = 0; count < Crc_Length; count++)
	{
		crc_value = crc_value ^ Crc_DataPtr[count];
		crc_value = Crc8Table22[crc_value];// &0xFF];
	}

	return crc_value;// crc_value;
}

unsigned short CPRIFunc_Insp::CRC_CalculateCRC16_CCIT(BYTE* Crc_DataPtr, unsigned int Crc_Length)
{
	static const unsigned short Crc16Table[256] =
	{
		0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
		0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
		0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
		0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
		0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
		0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
		0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
		0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
		0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
		0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
		0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
		0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
		0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
		0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
		0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
		0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
		0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
		0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
		0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
		0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
		0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
		0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
		0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
		0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
		0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
		0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
		0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
		0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
		0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
		0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
		0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
		0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
	};
	//unsigned short col_start;
	unsigned int i = 0;
	unsigned short crc = 0;

	for (i = 0; i < Crc_Length; i++)
	{
		crc = (crc << 8) ^ Crc16Table[((crc >> 8) ^ *Crc_DataPtr++) & 0x00FF];
	}
	return crc;
}