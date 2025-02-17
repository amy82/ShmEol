#include "StdAfx.h"
#include "../../GlobalDeclare.h"
#include "LaonGrabberWrapper.h"
#include "PixelFormat.h"

#define BUFFER_COUNT		7

CLaonGrabberWrapper::CLaonGrabberWrapper()
{
	memset(&m_stMIUDevice, 0x00, sizeof(m_stMIUDevice));

    m_pFrameRawBuffer = NULL;
    m_pFrameBMPBuffer = NULL;

	vChartBuffer = NULL;
	//vDefectMidBuffer_5000k = NULL;
	//vDefectMidBuffer_6500K = NULL;
	vDefectMidBuffer_3000k = NULL;
	vDefectLowBuffer = NULL;
	//vDefectMidBuffer_IR = NULL;

	//m_pFrameRawBuffer_TP_Ref1[0] = NULL;
	//m_pFrameRawBuffer_TP_Ref1[1] = NULL;
	m_pTestBuffer = NULL;
	m_bOpen = false;
	m_nCurrentCcdState = CCD_GRAB_STOP;

	m_nDevice = 0;
	m_pSID = NULL;
	m_nSensorCount = 0;
	
	memset(m_cIndexArray, 0, 4);
	m_cDeviceCount = 0;

	m_bRcccMoveX = false;
	m_bRcccMoveY = false;
	m_bCheckDir = false;

    
	//this->SensorListInitialize();
}


CLaonGrabberWrapper::~CLaonGrabberWrapper()
{
	int i;	

    if (m_pFrameRawBuffer)
    {
        delete m_pFrameRawBuffer;
    }
    m_pFrameRawBuffer = NULL;

	if (vChartBuffer)
	{
		delete vChartBuffer;
	}
	vChartBuffer = NULL;
	/*if (vDefectMidBuffer_5000k)
	{
		delete vDefectMidBuffer_5000k;
	}
	vDefectMidBuffer_5000k = NULL;
	if (vDefectMidBuffer_6500K)
	{
		delete vDefectMidBuffer_6500K;
	}
	vDefectMidBuffer_6500K = NULL;*/
	if (vDefectMidBuffer_3000k)
	{
		delete vDefectMidBuffer_3000k;
	}
	vDefectMidBuffer_3000k = NULL;
	if (vDefectLowBuffer)
	{
		delete vDefectLowBuffer;
	}
	vDefectLowBuffer = NULL;
	/*if (vDefectMidBuffer_IR)
	{
		delete vDefectMidBuffer_IR;
	}
	vDefectMidBuffer_IR = NULL;*/


	if (m_pFrameBMPBuffer)
	{
		delete m_pFrameBMPBuffer;
	}
	/*if (m_pFrameRawBuffer_TP_Ref1[0])
	{
		delete m_pFrameRawBuffer_TP_Ref1[0];
	}
	m_pFrameRawBuffer_TP_Ref1[0] = NULL;

	if (m_pFrameRawBuffer_TP_Ref1[1])
	{
		delete m_pFrameRawBuffer_TP_Ref1[1];
	}
	m_pFrameRawBuffer_TP_Ref1[1] = NULL;*/
	if (m_pTestBuffer)
	{
		delete m_pTestBuffer;
	}
	
	for(i = 0; i < 3; i++)
	{
		if(m_pGrabBuff[i] != NULL)
			cvReleaseImage(&m_pGrabBuff[i]);

		if(m_pImageBuff[i] != NULL)
			cvReleaseImage(&m_pImageBuff[i]);
	}



	for (i = 0; i < m_nSensorCount; i++)
	{
		if (m_pSID[i].pInfo != NULL)
			delete m_pSID[i].pInfo;
	}

	if (m_pSID != NULL)
		delete m_pSID;

	if (m_stMIUDevice.image != NULL)
	{		
		cvReleaseImage(&m_stMIUDevice.image);
		cvReleaseImage(&m_stMIUDevice.imageItp);

		cvReleaseImage(&m_stMIUDevice.ColorConvertItp);

		
		m_stMIUDevice.image = NULL;
		m_stMIUDevice.imageItp = NULL;

		if (m_stMIUDevice.nBitPerPixel > 8)
		{
			cvReleaseImage(&m_stMIUDevice.ColorConvertItp);
			m_stMIUDevice.ColorConvertItp = NULL;
		}
	}

	if (m_stMIUDevice.imageResize != NULL)
	{
		cvReleaseImage(&m_stMIUDevice.imageResize);
		m_stMIUDevice.imageResize = NULL;
		m_stMIUDevice.fResizeFlag = 0;
	}




	/*for (int i = 0; i < 20; i++)
	{
		if (pSumBuffer[i] != NULL)
		{
			free(pSumBuffer[i]);
			pSumBuffer[i] = 0;
		}
	}*/
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CLaonGrabberWrapper::SelectSensor()
{
	TCHAR szLog[SIZE_OF_1K];
    m_stMIUDevice.nWidth = m_pBoard->GetWidth();
    m_stMIUDevice.nHeight = m_pBoard->GetHeight();

	g_clModelData[m_nUnit].m_nWidth = m_pBoard->GetWidth();
	g_clModelData[m_nUnit].m_nHeight = m_pBoard->GetHeight();

    m_stMIUDevice.iPixelFormat = m_pBoard->GetDataFormat();
    m_stMIUDevice.nFrameImageSize = m_pBoard->GetFrameRawSize();;//PAYLOAD_SIZE * nPacketCount;

	_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD] Raw Size:%d"), m_stMIUDevice.nFrameImageSize);
	AddLog(szLog, 0, m_nUnit);
	//raw size = 3110400
	//yuv size = 4147200

    dTDATASPEC_n.eDataFormat = (EDATAFORMAT)m_pBoard->GetDataFormat();
    dTDATASPEC_n.eOutMode =  (EOUTMODE)m_pBoard->GetOutMode();
    dTDATASPEC_n.eSensorType = (ESENSORTYPE)m_pBoard->GetSensorType();
	

	dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GRADIENT;// rdemosaicmethodType(g_clModelData[m_nUnit].m_dDemosaic);
	dTDATASPEC_n.nBlackLevel = 0;	

    return true;
}
int CLaonGrabberWrapper::UiconfigLoad(int index, CString iniPath)//	CString uiFile)
{
    char szTemp[MAX_PATH];
    CString uiFile = "";
   // uiFile.Format(_T("%s\\UIConfig\\UIConfigRaw.ini"), MIU_DIR);       //m_nUnit+1
	if (index == INI_RAW_IMAGE)
	{
		//raw image
		uiFile.Format(_T("%s\\UIConfig\\UIConfigRaw.ini"), MIU_DIR);       //m_nUnit+1
	}
	else if (index == INI_YUV_IMAGE)
	{
		//yuv image
		uiFile.Format(_T("%s\\UIConfig\\UIConfigYuv.ini"), MIU_DIR);       //m_nUnit+1
	}
	else
	{
		uiFile.Format(_T("%s"), iniPath);       //m_nUnit+1
	}
	//
	//
    m_cBoardIndex = GetPrivateProfileInt(_T("UIConfig"), _T("BoardIndex"), 0, uiFile);
    GetPrivateProfileString(_T("UIConfig"), _T("GrabberINI"), _T("Default.ini"), szTemp, MAX_PATH, uiFile);
    selectedIniFile.Format(_T("%s\\%s"), MIU_DIR, szTemp);
	this->m_pBoard->SetINIFile(selectedIniFile);

	TCHAR szLog[SIZE_OF_1K];
	_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD] iniFile: %s"), szTemp);
	AddLog(szLog, 0, m_nUnit);

	uiFile.Empty();
    return 1;
}

void CLaonGrabberWrapper::UpdateVersionInfo()
{
    
}
EDATAFORMAT CLaonGrabberWrapper::rDataFormatType(int index)
{
	EDATAFORMAT edata;
	switch (index)
	{
	case 0:
		edata = DATAFORMAT_YUV; break;
	case 1:
		edata = DATAFORMAT_BAYER_8BIT; break;
	case 2:
		edata = DATAFORMAT_BAYER_10BIT; break;
	case 3:
		edata = DATAFORMAT_BAYER_PARALLEL_10BIT; break;
	case 4:
		edata = DATAFORMAT_BAYER_12BIT; break;
	case 5:
		edata = DATAFORMAT_BAYER_PARALLEL_12BIT; break;
	case 6:
		edata = DATAFORMAT_BAYER_16BIT; break;
	case 7:
		edata = DATAFORMAT_BAYER_16BIT_BE; break;
	case 8:
		edata = DATAFORMAT_BAYER_16BIT_PWL_HDR; break;
	case 9:
		edata = DATAFORMAT_BAYER_16BIT_PWL_DECOMP; break;
	case 10:
		edata = DATAFORMAT_BAYER_24BIT; break;
	case 11:
		edata = DATAFORMAT_BAYER_PARALLEL_10BIT_BE; break;
	case 12:
		edata = DATAFORMAT_BAYER_PARALLEL_12BIT_BE; break;
	case 13:
		edata = DATAFORMAT_RGB; break;
	default:
		edata = DATAFORMAT_YUV; break;
		break;
	}
	return edata;
}
EOUTMODE CLaonGrabberWrapper::rOutmodeType(int index)
{
	EOUTMODE eout;
	switch (index)
	{
	case 0:
		eout = OUTMODE_BAYER_BGGR; break;
	case 1:
		eout = OUTMODE_BAYER_RGGB; break;
	case 2:
		eout = OUTMODE_BAYER_GBRG; break;
	case 3:
		eout = OUTMODE_BAYER_GRBG; break;
	case 4:
		eout = OUTMODE_BAYER_BLACKWHITE; break;
	case 5:
		eout = OUTMODE_YUV422_YCbYCr; break;
	case 6:
		eout = OUTMODE_YUV422_YCrYCb; break;
	case 7:
		eout = OUTMODE_YUV422_CbYCrY; break;
	case 8:
		eout = OUTMODE_YUV422_CrYCbY; break;
	case 9:
		eout = OUTMODE_RGB_BGR; break;
	case 10:
		eout = OUTMODE_RGB_RGB; break;
	case 11:
		eout = OUTMODE_BAYER_BNGR; break;
	case 12:
		eout = OUTMODE_BAYER_RGNB; break;
	case 13:
		eout = OUTMODE_BAYER_NBRG; break;
	case 14:
		eout = OUTMODE_BAYER_GRBN; break;
	case 15:
		eout = OUTMODE_BAYER_BGGN; break;
	case 16:
		eout = OUTMODE_BAYER_RGGN; break;
	case 17:
		eout = OUTMODE_BAYER_GBNG; break;
	case 18:
		eout = OUTMODE_BAYER_GRNG; break;
	case 19:
		eout = OUTMODE_BAYER_NGGR; break;
	case 20:
		eout = OUTMODE_BAYER_NGGB; break;
	case 21:
		eout = OUTMODE_BAYER_GNRG; break;
	case 22:
		eout = OUTMODE_BAYER_GNBG; break;
	default:
		eout = OUTMODE_BAYER_BGGR; break;
		break;
	}
	return eout;
}
ESENSORTYPE CLaonGrabberWrapper::rSensortypeType(int index)
{
	ESENSORTYPE esen;
	switch (index)
	{
	case 0:
		esen = SENSORTYPE_RGGB; break;
	case 1:
		esen = SENSORTYPE_RCCC; break;
	case 2:
		esen = SENSORTYPE_RCCB; break;
	case 3:
		esen = SENSORTYPE_CCCC; break;
	case 4:
		esen = SENSORTYPE_RBCC; break;
	case 5:
		esen = SENSORTYPE_OTHER; break;
	case 6:
		esen = SENSORTYPE_RGBIR2; break;
	default:
		esen = SENSORTYPE_RGGB; break;
		break;
	}
	return esen;
}
EDEMOSAICMETHOD CLaonGrabberWrapper::rdemosaicmethodType(int index)
{
	EDEMOSAICMETHOD edemo;
	switch (index)
	{
	case 0:
		edemo = DEMOSAICMETHOD_NONE; break;
	case 1:
		edemo = DEMOSAICMETHOD_GRADIENT; break;
	case 2:
		edemo = DEMOSAICMETHOD_BL33; break;
	case 3:
		edemo = DEMOSAICMETHOD_OPENCV_VNG; break;
	case 4:
		edemo = DEMOSAICMETHOD_VNG; break;
	case 5:
		edemo = DEMOSAICMETHOD_GR_ONLY; break;
	case 6:
		edemo = DEMOSAICMETHOD_GB_ONLY; break;
	case 7:
		edemo = DEMOSAICMETHOD_GBTF; break;
	case 8:
		edemo = DEMOSAICMETHOD_BLLC; break;
	case 9:
		edemo = DEMOSAICMETHOD_RESIDUAL; break;
	case 10:
		edemo = DEMOSAICMETHOD_BAYER_Y; break;
	case 11:
		edemo = DEMOSAICMETHOD_GRADIENT_RESIDUAL; break;
	case 12:
		edemo = DEMOSAICMETHOD_GBTF_RESIDUAL; break;
	case 13:
		edemo = DEMOSAICMETHOD_RESIDUAL_RESIDUAL; break;
	case 14:
		edemo = DEMOSAICMETHOD_BL33_RESIDUAL; break;
	case 15:
		edemo = DEMOSAICMETHOD_IR_ONLY; break;
	case 16:
		edemo = DEMOSAICMETHOD_GRADIENT_G_ONLY; break;
	case 17:
		edemo = DEMOSAICMETHOD_GBTF_G_ONLY; break;
	case 18:
		edemo = DEMOSAICMETHOD_RESIDUAL_G_ONLY; break;
	case 19:
		edemo = DEMOSAICMETHOD_BL33_G_ONLY; break;
	case 20:
		edemo = DEMOSAICMETHOD_GRADIENT_IR_ONLY; break;
	case 21:
		edemo = DEMOSAICMETHOD_GBTF_IR_ONLY; break;
	case 22:
		edemo = DEMOSAICMETHOD_RESIDUAL_IR_ONLY; break;
	case 23:
		edemo = DEMOSAICMETHOD_BL33_IR_ONLY; break;
	default:
		edemo = DEMOSAICMETHOD_NONE; break;
		break;
	}
	return edemo;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
int CLaonGrabberWrapper::SearchDevice()
{
	//TCHAR szLog[SIZE_OF_1K];
	//int errorCode;

	////errorCode = MIUGetDeviceList(&m_cDeviceCount, m_cIndexArray);
 //   //m_pBoard
	//if(errorCode)
	//{
	//	_stprintf_s(szLog, SIZE_OF_1K, _T("MIU DEVICE SEARH ERROR(CODE:0x%x)"), errorCode);

 //       //AddLog(szLog, 1, 999);
 //       AddLog(szLog, 1, 0);
 //       AddLog(szLog, 1, 1);
	//}
    m_cDeviceCount = 2;
	return (int)m_cDeviceCount;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
int CLaonGrabberWrapper::GetDeviceCount()
{
	int iErrorCode = MIU_OK;
	char cCount = 0;	
	char cIndex[2];

	memset(cIndex, 0x00, sizeof(cIndex));

    iErrorCode = MIU_OK;// MIUGetDeviceList(&cCount, cIndex);
	if ( iErrorCode != MIU_OK )
	{
		cCount = 0;		
	}

	return cCount;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CLaonGrabberWrapper::BoardtInitialize()
{
    m_hBoardLibrary = LoadLibrary("GrabberDLL.dll");
    if (m_hBoardLibrary == NULL)
    {
        //AfxMessageBox("[ERROR] Cannot Load Board Library");
        AddLog(_T("[ERROR] Cannot Load Board Library"), 1, m_nUnit);
    }

    pfnGetBoardControl fnGetInterface = (pfnGetBoardControl)GetProcAddress(m_hBoardLibrary, "GetBoardControl");
    if (fnGetInterface)
    {
        m_pBoard = (*fnGetInterface)(BOARD_TYPE_LAON);
        if (m_pBoard == NULL)
        {
            //AfxMessageBox("[ERROR] GetBoardControl Load Failed!");
            AddLog(_T("[ERROR] GetBoardControl Load Failed"), 1, m_nUnit);
        }
    }
    else
    {
        //AfxMessageBox("[ERROR] Cannot Get Board Interface");
        AddLog(_T("[ERROR] Cannot Get Board Interface"), 1, m_nUnit);
    }
}
void CLaonGrabberWrapper::SensorListInitialize()
{
	
}


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CLaonGrabberWrapper::GetCcdState()
{
	if (m_nCurrentCcdState == CCD_GRAB_LIVE && g_clTaskWork[m_nUnit].m_fFps > g_clModelData[m_nUnit].m_fFpsStopVal)
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CLaonGrabberWrapper::AllocImageBuff()
{
	int i = 0;


	for (i = 0; i < 3; i++)
	{
		if (m_pGrabBuff[i] != NULL) {
			cvReleaseImage(&m_pGrabBuff[i]);
		}
		if (m_pImageBuff[i] != NULL) {
			cvReleaseImage(&m_pImageBuff[i]);
		}
	}

	for (i = 0; i < 3; i++)
	{
		m_pGrabBuff[i] = cvCreateImage(cvSize(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight), IPL_DEPTH_8U, 3);
		m_pImageBuff[i] = cvCreateImage(cvSize(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight), IPL_DEPTH_8U, 1);
	}



	if (m_stMIUDevice.imageItp != NULL)
	{
		cvReleaseImage(&m_stMIUDevice.imageItp);
	}
    m_stMIUDevice.imageItp = cvCreateImage(cvSize(m_stMIUDevice.nWidth, m_stMIUDevice.nHeight), IPL_DEPTH_8U, 3);
}

//-----------------------------------------------------------------------------
//
//raw reset
//
//-----------------------------------------------------------------------------
void CLaonGrabberWrapper::rawReSet()
{
	int nRawSize = m_pBoard->GetFrameRawSize();

	//raw size = 3110400
	//yuv size = 4147200

	int rawsize = m_pBoard->GetFrameRawSize();
	int bmpsize = m_pBoard->GetFrameBMPSize();
	if (m_pFrameRawBuffer)
	{
		delete m_pFrameRawBuffer;
	}
	m_pFrameRawBuffer = new BYTE[nRawSize];
	memset(m_pFrameRawBuffer, 0, nRawSize);
	if (m_pFrameBMPBuffer)
	{
		delete m_pFrameBMPBuffer;
	}
	m_pFrameBMPBuffer = new BYTE[m_pBoard->GetFrameBMPSize()];
	memset(m_pFrameBMPBuffer, 0, m_pBoard->GetFrameBMPSize());
	if (m_pTestBuffer)
	{
		delete m_pTestBuffer;
	}
	m_pTestBuffer = new BYTE[m_pBoard->GetFrameBMPSize()];
	memset(m_pTestBuffer, 0, m_pBoard->GetFrameBMPSize());


	if (vChartBuffer)
	{
		delete vChartBuffer;
	}
	if (vDefectLowBuffer)
	{
		delete vDefectLowBuffer;
	}
	if (vDefectMidBuffer_3000k)
	{
		delete vDefectMidBuffer_3000k;
	}
	vChartBuffer = new BYTE[nRawSize];
	vDefectLowBuffer = new BYTE[nRawSize];
	vDefectMidBuffer_3000k = new BYTE[nRawSize];
	memset(vChartBuffer, 0, nRawSize);
	memset(vDefectMidBuffer_3000k, 0, nRawSize);
	memset(vDefectLowBuffer, 0, nRawSize);


	//vDefectMidBuffer_6500K = new BYTE[nRawSize];
	//vDefectMidBuffer_5000k = new BYTE[nRawSize];
	//vDefectMidBuffer_IR = new BYTE[nRawSize];
	//memset(vDefectMidBuffer_6500K, 0, nRawSize);
	//memset(vDefectMidBuffer_5000k, 0, nRawSize);
	//memset(vDefectMidBuffer_IR, 0, nRawSize);


	/*int i = 0;
	for (i = 0; i < 20; i++)
	{
		pSumBuffer[i] = new BYTE[nRawSize];
		memset(pSumBuffer[i], 0, nRawSize);
	}*/
}

//-----------------------------------------------------------------------------
//
//	Device Open
//
//-----------------------------------------------------------------------------
bool CLaonGrabberWrapper::OpenDevice()
{
	TCHAR szLog[SIZE_OF_1K];
	int nErrorCode;


	if (m_bOpen == true)
	{
		AddLog("[OPEN]m_bOpen true", 0, m_nUnit);
		return true;
	}
	g_pCarAABonderDlg->CurrentPowerOnOff(true);
	if (this->m_pBoard->IsGrabStarted())
	{
		StopGrab();
		Sleep(500);
		CloseDevice();
		Sleep(500);
	}
    m_bOpen = false;
	nErrorCode = m_pBoard->OpenBoard(m_cBoardIndex); //MIUOpenDevice(m_nDevice);
	if (nErrorCode)
	{
		if (nErrorCode == 9)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD]Laon AA#%d Error(Code:%02X)"), m_cBoardIndex + 1, nErrorCode);
			AddLog(szLog, 0, m_nUnit, false);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD] Á¦Ç° ÄÁÅÃor ÄÉÀÌºí »óÅÂ È®ÀÎ¹Ù¶ø´Ï´Ù."));
			AddLog(szLog, 1, m_nUnit, true);
		}
		else
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD]Laon AA#%d Error(Code:%02X)"), m_cBoardIndex + 1, nErrorCode);
			AddLog(szLog, 1, m_nUnit, true);
		}
		return false;
	}
	AddLog("[OPEN]CCD OPEN OK", 0, m_nUnit);
	m_stMIUDevice.bRccc = 1;
	m_bOpen = true;

	return true;
}
//case ERR_BOARD_GET_LIST:
//	retStr = "ERR_BOARD_GET_LIST";
//	break;
//case ERR_BOARD_NO_DEVICE:
//	retStr = "ERR_BOARD_NO_DEVICE";
//	break;
//case ERR_BOARD_OPEN:
//	retStr = "ERR_BOARD_OPEN";
//	break;
//case ERR_BOARD_INIT:
//	retStr = "ERR_BOARD_INIT";
//	break;
//case ERR_BOARD_SET_POWER_5_12:
//	retStr = "ERR_BOARD_SET_POWER_5_12";
//	break;
//case ERR_BOARD_GRAB_START:
//	retStr = "ERR_BOARD_GRAB_START";
//	break;
//case ERR_BOARD_I2C_WRITE:
//	retStr = "ERR_BOARD_I2C_WRITE";
//	break;
//case ERR_BOARD_I2C_READ:
//	retStr = "ERR_BOARD_I2C_READ";
//	break;
//case ERR_BOARD_BOOT_CAMERA:
//	retStr = "ERR_BOARD_BOOT_CAMERA";
//	break;
//case ERR_BOARD_CLOSE:
//	retStr = "ERR_BOARD_CLOSE";
//	break;
//case ERR_BOARD_LOAD_MODEL:
//	retStr = "ERR_BOARD_LOAD_MODEL";
//	break;
//-----------------------------------------------------------------------------
//
//	Device Close
//
//-----------------------------------------------------------------------------
bool CLaonGrabberWrapper::CloseDevice()
{
	int nErrorCode = -1;
	
	if (this->m_pBoard->IsGrabStarted())
	{
		StopGrab();
		Sleep(150);
	}
	Sleep(150);
	g_pCarAABonderDlg->CurrentPowerOnOff(false);
	Sleep(150);
    this->m_pBoard->CloseBoard();

	AddLog("[CCD]CLOSE GRAB", 0, m_nUnit);
	m_stMIUDevice.CurrentState = 0;
	m_nCurrentCcdState = CCD_GRAB_STOP;
	m_bOpen = false;


	UiconfigLoad(INI_RAW_IMAGE);		//CloseBoard
	g_pCarAABonderDlg->m_clButtonExCcd[m_nUnit].state = 0;
	g_pCarAABonderDlg->m_clButtonExCcd[m_nUnit].Invalidate();




	//240222 Ãß°¡
	g_clVision.m_nGrabIndex[m_nUnit] = 0;
	g_clVision.m_nCvtColorReadyIndex[m_nUnit] = 0;
	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CLaonGrabberWrapper::StartGrab()
{	
	m_stMIUDevice.CurrentState = 1; 
	m_nCurrentCcdState = CCD_GRAB_STOP;
    if (this->m_pBoard->GrabStart() == BOARD_SUCCESS)
    {
        AddLog("[CCD]START OK", 0, m_nUnit);
    }
    else
    {
        AddLog("[CCD]START FAIL", 0, m_nUnit);
        return false;
    }
	Sleep(1000);
	m_nCurrentCcdState = CCD_GRAB_LIVE;
	
	return true;
}

int CLaonGrabberWrapper::getRawSize()
{
	return this->m_pBoard->GetFrameRawSize();
}
//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CLaonGrabberWrapper::StopGrab()
{
	TCHAR szLog[SIZE_OF_1K];
	int nErrorCode;
	int i;

	if (m_bOpen == false)
	{
		m_nCurrentCcdState = CCD_GRAB_STOP;
		AddLog("[STOP]m_bOpen false", 0, m_nUnit);
		return true;
	}
	if (m_pBoard->IsGrabStarted() == false)
	{
		return false;
	}
	this->m_pBoard->GrabStop();
	AddLog("[CCD]STOP GRAB", 0, m_nUnit);


    m_bOpen = false;

	m_nCurrentCcdState = CCD_GRAB_STOP;
    m_stMIUDevice.CurrentState = 0;

    g_clTaskWork[m_nUnit].m_fFps = 0.0;
    g_pCarAABonderDlg->DrawCcdFps(m_nUnit);

	g_pCarAABonderDlg->m_clButtonExCcd[m_nUnit].state = 0;
	g_pCarAABonderDlg->m_clButtonExCcd[m_nUnit].Invalidate();
	
	

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CLaonGrabberWrapper::StartGrabCcdProcess()
{
	m_stMIUDevice.CurrentState = 1;
	m_nCurrentCcdState = CCD_GRAB_STOP;
	if (this->m_pBoard->GrabStart() == BOARD_SUCCESS)
	{
		AddLog("[CCD]START OK", 0, m_nUnit);
	}
	else
	{
		AddLog("[CCD]START FAIL", 0, m_nUnit);
		return false;
	}
	Sleep(500);
	m_nCurrentCcdState = CCD_GRAB_LIVE;

	return true;

}
//
////-----------------------------------------------------------------------------
////
////
////
////-----------------------------------------------------------------------------
//void CLaonGrabberWrapper::Shift12to16BitMode(unsigned char* p12bitRaw, unsigned char* p16bitRaw, int nWidth, int nHeight)
//{
//	int k = 0;
//	int n12bitRawSize = nWidth * nHeight * 1.5;
//	register int i;
//
//	for(i = 0; i < n12bitRawSize ; i+=3)
//	{
//		p16bitRaw[k+1] = (p12bitRaw[i] & 0xF0) >> 4 ;
//		p16bitRaw[k+0] = ((p12bitRaw[i] & 0x0F) << 4 ) +  ((p12bitRaw[i + 2]  & 0x0F )) ;
//		
//		p16bitRaw[k+3] = (p12bitRaw[i + 1] & 0xF0) >> 4 ;
//		p16bitRaw[k+2] = ((p12bitRaw[i + 1] & 0x0F) << 4 ) +  ((p12bitRaw[i + 2]  & 0xF0 ) >> 4) ;
//
//		k += 4;
//	}
//}
//
////-----------------------------------------------------------------------------
////
////
////
////-----------------------------------------------------------------------------
//void CLaonGrabberWrapper::CCCR_Interpolation(unsigned short* pData, int nWidth, int nHeight)
//{
//	int nNewValue = 0;
//	int nStartX = 1;
//	int nStartY = 1;
//	register int i, j;
//
//	if(m_bRcccMoveX == true)
//		nStartX = 2;
//
//	if(m_bRcccMoveY == true)
//		nStartY = 2;
//
//	for (i = nStartY; i < nHeight - 1; i += 2)
//	{
//		for (j = nStartX; j < nWidth - 1; j += 2)
//		{
//			if(m_bCheckDir == true)
//			{
//				int absV = abs(pData[(i - 1) * nWidth + (j + 0)] - pData[(i + 1) * nWidth + (j + 0)]);
//				int absH = abs(pData[(i + 0) * nWidth + (j - 1)] - pData[(i + 0) * nWidth + (j + 1)]);
//				pData[i * nWidth + j] = (absV < absH) ? (pData[(i - 1) * nWidth + (j + 0)] + pData[(i + 1) * nWidth + (j + 0)]) / 2 : (pData[(i + 0) * nWidth + (j - 1)] + pData[(i + 0) * nWidth + (j + 1)]) / 2;
//			}
//			else
//			{
//				nNewValue =  pData[(i - 1) * nWidth + (j + 0)] + pData[(i + 1) * nWidth + (j + 0)] + pData[(i + 0) * nWidth + (j - 1)]  + pData[(i + 0) * nWidth + (j + 1)] ;
//				
//				nNewValue = nNewValue / 4;
//				pData[i * nWidth + j] = (unsigned short) nNewValue;
//			}			
//		}
//	}
//}
//
////-----------------------------------------------------------------------------
////
////
////
////-----------------------------------------------------------------------------
//void CLaonGrabberWrapper::Shift16to12BitMode(unsigned char* pImage, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight)
//{	
//	unsigned int nScrWidth, nDestWidth;
//	unsigned char *pcDest;
//	register unsigned int i, j, k;
//
//	nDestWidth = nWidth * 3 / 2;
//	nScrWidth = nWidth * 2;
//
//	pcDest = (unsigned char *) pDest;
//
//	for(i = 0; i < nHeight; i++)
//	{
//		for(j = 0, k = 0; j < nDestWidth; j += 6, k += 8)
//		{
//			pcDest[j + 0] = ((pImage[k] & 0xF0) >> 4 ) +  ((pImage[k + 1]  & 0x0f ) << 4) ;
//			pcDest[j + 1] = ((pImage[k + 2] & 0xF0) >> 4 ) +  ((pImage[k + 3]  & 0x0f ) << 4) ;
//			pcDest[j + 2] = (pImage[k] & 0x0F) + ((pImage[k + 2]  & 0x0f ) << 4) ;
//
//			pcDest[j + 3] = ((pImage[k + 4] & 0xF0) >> 4 ) +  ((pImage[k + 5]  & 0x0f ) << 4) ;
//			pcDest[j + 4] = ((pImage[k + 6] & 0xF0) >> 4 ) +  ((pImage[k + 7]  & 0x0f ) << 4) ;
//			pcDest[j + 5] = (pImage[k + 4] & 0x0F) + ((pImage[k + 6]  & 0x0f ) << 4) ;
//		}
//
//		pcDest += nDestWidth;
//		pImage += nScrWidth;
//	}	
//}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CLaonGrabberWrapper::IniAnalyze()
{
//	TCHAR szPath[SIZE_OF_1K];
//	TCHAR szIniBuff[SIZE_OF_1K];
//	TCHAR szTemp[SIZE_OF_100BYTE];
//	TCHAR szLog[SIZE_OF_1K];
//	CStdioFile flInitialFile;
//	CFileException  e;
//	CString szLineRead;
//	char fInitMode = 0;
//	unsigned int nAddress, nData;
//	int	errorCode;
//	int	errorCount = 0;
//	BYTE BurstWriteData[2048];
//	int	BurstWriteLength = 0;
//	int	BurstWriteLengthaddr = 0;
//	unsigned short  data;
//	unsigned int bustSleep = 0;
//	BOOL m_Burst = FALSE;
//	int	i = 0;
//	int nTemp = 0;
//	DWORD dwTickCount;
//
//	_stprintf_s(szPath, SIZE_OF_1K, _T("Initialize\\AA_%d\\%s_%s.ini"), m_nUnit+1, m_pSID[0].szSensorName, m_pSID[0].pInfo[0].szResolution);
//
//	m_stMIUDevice.InitialValue.SensorMode = GetPrivateProfileInt(_T("MIUConfiguration"), _T("SensorMode"), 0, szPath);
//	m_stMIUDevice.InitialValue.nWidth = GetPrivateProfileInt(_T("MIUConfiguration"), _T("SensorWidth"), 0, szPath);
//	m_stMIUDevice.InitialValue.nHeight = GetPrivateProfileInt(_T("MIUConfiguration"), _T("SensorHeight"), 0, szPath);
//	m_stMIUDevice.nWidth = m_stMIUDevice.InitialValue.nWidth;
//	m_stMIUDevice.nHeight = m_stMIUDevice.InitialValue.nHeight;
//
//	m_stMIUDevice.nMaxWidth = GetPrivateProfileInt(_T("MIUConfiguration"), _T("MAXWidth"), 4000, szPath);;			// Max Width
//	m_stMIUDevice.nMaxHeight = GetPrivateProfileInt(_T("MIUConfiguration"), _T("MAXHeight"), 3000, szPath);;			// Max Height   
//
//	m_stMIUDevice.InitialValue.MCLKOnOff = GetPrivateProfileInt(_T("MIUConfiguration"), _T("MCLKOnOff"), 1, szPath);
//	m_stMIUDevice.InitialValue.MCLKSelection = GetPrivateProfileInt(_T("MIUConfiguration"), _T("MCLKSelection"), 1, szPath);
//	GetPrivateProfileString(_T("MIUConfiguration"), _T("MCLK"), _T("0.0"), szIniBuff, sizeof(szIniBuff), szPath);
//	m_stMIUDevice.InitialValue.MCLK = (float)_ttof((szIniBuff));
//	
//	m_stMIUDevice.InitialValue.PCLKInversion = GetPrivateProfileInt(_T("MIUConfiguration"), _T("PCLKInversion"), 0, szPath);
//	GetPrivateProfileString(_T("MIUConfiguration"), _T("IICDeviceID"), _T(""), szIniBuff, sizeof(szIniBuff), szPath);
//	_stscanf_s(szIniBuff, _T("%x"), &nTemp);
//	m_stMIUDevice.InitialValue.IICDeviceID = nTemp;
//		
//	m_stMIUDevice.InitialValue.IICMode = GetPrivateProfileInt(_T("MIUConfiguration"), _T("IICMode"), 0, szPath);
//	m_stMIUDevice.InitialValue.IICSpeed = GetPrivateProfileInt(_T("MIUConfiguration"), _T("IICSpeed"), 0, szPath);
//	m_stMIUDevice.InitialValue.IICReadRestart = GetPrivateProfileInt(_T("MIUConfiguration"), _T("IICReadRestart"), 1, szPath);
//	m_stMIUDevice.InitialValue.IICReadRestartInterval = GetPrivateProfileInt(_T("MIUConfiguration"), _T("IICReadRestartInterval"), 0, szPath);
//	m_stMIUDevice.InitialValue.IICSCKPinCheck = GetPrivateProfileInt(_T("MIUConfiguration"), _T("IICSCKPinCheck"), 0, szPath);
//	m_stMIUDevice.InitialValue.IICAddressLength = GetPrivateProfileInt(_T("MIUConfiguration"), _T("IICAddressLength"), 0, szPath);
//	m_stMIUDevice.InitialValue.IICDataLength = GetPrivateProfileInt(_T("MIUConfiguration"), _T("IICDataLength"), 0, szPath);
//
//	m_stMIUDevice.InitialValue.MIPILaneEnable = GetPrivateProfileInt(_T("MIUConfiguration"), _T("MIPILaneEnable"), 1, szPath);
//	GetPrivateProfileString(_T("MIUConfiguration"), _T("MIPIDataType"), _T("0x2B"), szIniBuff, sizeof(szIniBuff), szPath);
//	_stscanf_s(szIniBuff, _T("%x"), &nTemp);
//	m_stMIUDevice.InitialValue.MIPIDataType = nTemp;
//	
//	m_stMIUDevice.InitialValue.MIPI8bitMode = GetPrivateProfileInt(_T("MIUConfiguration"), _T("MIPI8bitMode"), 0, szPath);
//
//	GetPrivateProfileString(_T("MIUConfiguration"), _T("MIUIOVoltage"), _T("0.0"), szIniBuff, sizeof(szIniBuff), szPath);
//	m_stMIUDevice.InitialValue.MIUIOVoltage = (float)_ttof(szIniBuff);
//
//	m_stMIUDevice.InitialValue.FirstPowerChannel = GetPrivateProfileInt(_T("MIUConfiguration"), _T("1stPowerChannel"), 0, szPath);
//
//	GetPrivateProfileString(_T("MIUConfiguration"), _T("1stPowerVoltage"), _T("0.0"), szIniBuff, sizeof(szIniBuff), szPath);
//	m_stMIUDevice.InitialValue.FirstPowerVoltage = (float)_ttof(szIniBuff);
//	
//	m_stMIUDevice.InitialValue.SecondPowerChannel = GetPrivateProfileInt(_T("MIUConfiguration"), _T("2ndPowerChannel"), 0, szPath);
//
//	GetPrivateProfileString(_T("MIUConfiguration"), _T("2ndPowerVoltage"), _T("0.0"), szIniBuff, sizeof(szIniBuff), szPath);
//	m_stMIUDevice.InitialValue.SecondPowerVoltage = (float)_ttof(szIniBuff);
//
//	m_stMIUDevice.InitialValue.ThirdPowerChannel = GetPrivateProfileInt(_T("MIUConfiguration"), _T("3rdPowerChannel"), 0, szPath);
//
//	GetPrivateProfileString(_T("MIUConfiguration"), _T("3rdPowerVoltage"), _T("0.0"), szIniBuff, sizeof(szIniBuff), szPath);
//	m_stMIUDevice.InitialValue.ThirdPowerVoltage = (float)_ttof(szIniBuff);
//
//	m_stMIUDevice.InitialValue.FourthPowerChannel = GetPrivateProfileInt(_T("MIUConfiguration"), _T("4thPowerChannel"), 0, szPath);
//
//	GetPrivateProfileString(_T("MIUConfiguration"), _T("4thPowerVoltage"), _T("0.0"), szIniBuff, sizeof(szIniBuff), szPath);
//	m_stMIUDevice.InitialValue.FourthPowerVoltage = (float)_ttof(szIniBuff);
//
//	m_stMIUDevice.InitialValue.FifthPowerChannel = GetPrivateProfileInt(_T("MIUConfiguration"), _T("5thPowerChannel"), 0, szPath);
//
//	GetPrivateProfileString(_T("MIUConfiguration"), _T("5thPowerVoltage"), _T("0.0"), szIniBuff, sizeof(szIniBuff), szPath);
//	m_stMIUDevice.InitialValue.FifthPowerVoltage = (float)_ttof(szIniBuff);
//
//	m_stMIUDevice.InitialValue.Power5VoltOnOff = GetPrivateProfileInt(_T("MIUConfiguration"), _T("5VoltPowerOnOff"), 0, szPath);
//	m_stMIUDevice.InitialValue.Power12VoltOnOff = GetPrivateProfileInt(_T("MIUConfiguration"), _T("12VoltPowerOnOff"), 0, szPath);
//
//	m_stMIUDevice.InitialValue.InitialSkipCount = GetPrivateProfileInt(_T("MIUConfiguration"), _T("InitialSkipCount"), 0, szPath);
//	m_stMIUDevice.InitialValue.PreviewSkipCount = GetPrivateProfileInt(_T("MIUConfiguration"), _T("PreviewSkipCount"), 0, szPath);
//
//	m_stMIUDevice.InitialValue.ParallelSamplingMode = GetPrivateProfileInt(_T("MIUConfiguration"), _T("ParallelSamplingMode"), 0, szPath);
//	m_stMIUDevice.InitialValue.ParallelBitsPerPixel = GetPrivateProfileInt(_T("MIUConfiguration"), _T("ParallelBitsPerPixel"), 0, szPath);
//	m_stMIUDevice.InitialValue.ParallelPixelComponent = GetPrivateProfileInt(_T("MIUConfiguration"), _T("ParallelPixelComponent"), 0, szPath);
//	m_stMIUDevice.InitialValue.ParallelBitShift = GetPrivateProfileInt(_T("MIUConfiguration"), _T("ParallelBitShift"), 0, szPath);
//
//
//	MIUInitialize(m_nDevice, m_stMIUDevice.InitialValue);
//	
//	Sleep(100);
//
//	if (!flInitialFile.Open(szPath, CFile::modeRead, &e))
//	{
//		e.ReportError(MB_OK);
//		return false;
//	}
//
//	dwTickCount = GetTickCount();
//
//	flInitialFile.SeekToBegin();
//	while (flInitialFile.ReadString(szLineRead))
//	{
////		AfxMessageBox(szLineRead);
//
//		if ((szLineRead.Find(_T("[MIU]")) != -1) && (szLineRead.Find(_T("[MIU]")) < 2))
//		{
//			fInitMode = 1;
//
//		}
//		else if ((szLineRead.Find(_T("[Sensor]")) != -1) && (szLineRead.Find(_T("[Sensor]")) < 2))
//		{
//			fInitMode = 2;
//		}
//		else if (((szLineRead.Find(_T("Sleep")) != -1) && ((szLineRead.Find(_T("Sleep")) < 2))) || ((szLineRead.Find(_T("SLEEP")) != -1) && ((szLineRead.Find(_T("SLEEP")) < 2))))
//		{
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d"), szTemp, _countof(szTemp), &nData);
//			if (BurstWriteLength == 0)
//			{
//				////////////////////////// 20130711 TRACE Ãß°¡
//				TRACE("Sleep = %d \n", nData);
//				Sleep(nData);
//				bustSleep = 0;
//			}
//			else
//			{
//				bustSleep = nData;
//
//			}
//		}
//		else if (((szLineRead.Find(_T("RESET")) != -1) && ((szLineRead.Find(_T("RESET")) < 2))) || ((szLineRead.Find(_T("reset")) != -1) && ((szLineRead.Find(_T("reset")) < 2))))
//		{
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d"), szTemp, _countof(szTemp), &nData);
//			MIUWriteRegister(m_nDevice, REG_MIU, 0x04, (unsigned short)nData);
//		}
//		else if (((szLineRead.Find(_T("ENABLE")) != -1) && ((szLineRead.Find(_T("ENABLE")) < 2))) || ((szLineRead.Find(_T("enable")) != -1) && ((szLineRead.Find(_T("enable")) < 2))))
//		{
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d"), szTemp, _countof(szTemp), &nData);
//			MIUWriteRegister(m_nDevice, REG_MIU, 0x05, (unsigned short)nData);
//		}
//		else if (((szLineRead.Find(_T("GPIO0")) != -1) && ((szLineRead.Find( _T("GPIO0")) < 2))) || ((szLineRead.Find(_T("gpio0")) != -1) && ((szLineRead.Find(_T("gpio0")) < 2))))
//		{
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d"), szTemp, _countof(szTemp), &nData);
//			MIUSetGPIOStatus(m_nDevice, 0, nData);
//		}
//		else if (((szLineRead.Find(_T("GPIO1")) != -1) && ((szLineRead.Find(_T("GPIO1")) < 2))) || ((szLineRead.Find(_T("gpio1")) != -1) && ((szLineRead.Find(_T("gpio1")) < 2))))
//		{
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d"), szTemp, _countof(szTemp), &nData);
//			MIUSetGPIOStatus(m_nDevice, 1, nData);
//		}
//		else if (((szLineRead.Find(_T("GPIO2")) != -1) && ((szLineRead.Find(_T("GPIO2")) < 2))) || ((szLineRead.Find(_T("gpio2")) != -1) && ((szLineRead.Find(_T("gpio2")) < 2))))
//		{
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d"), szTemp, _countof(szTemp), &nData);
//			MIUSetGPIOStatus(m_nDevice, 2, nData);
//		}
//		else if (((szLineRead.Find(_T("GPIO3")) != -1) && ((szLineRead.Find(_T("GPIO3")) < 2))) || ((szLineRead.Find(_T("gpio3")) != -1) && ((szLineRead.Find(_T("gpio3")) < 2))))
//		{
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d"), szTemp, _countof(szTemp), &nData);
//			MIUSetGPIOStatus(m_nDevice, 3, nData);
//		}
//		else if (((szLineRead.Find(_T("GPO0")) != -1) && ((szLineRead.Find(_T("GPO0")) < 2))) || ((szLineRead.Find(_T("gpo0")) != -1) && ((szLineRead.Find(_T("gpo0")) < 2))))
//		{
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d"), szTemp, _countof(szTemp), &nData);
//			MIUSetGPOStatus(m_nDevice, 0, nData);
//		}
//		else if (((szLineRead.Find(_T("GPO1")) != -1) && ((szLineRead.Find(_T("GPO1")) < 2))) || ((szLineRead.Find(_T("gpo1")) != -1) && ((szLineRead.Find(_T("gpo1")) < 2))))
//		{
//			_stscanf_s(szLineRead.GetBuffer(0), "%s%d", szTemp, _countof(szTemp), &nData);
//			MIUSetGPOStatus(m_nDevice, 0, nData);
//		}
//		else if (((szLineRead.Find(_T("GPIOMODE0")) != -1) && ((szLineRead.Find(_T("GPIOMODE0")) < 2))) || ((szLineRead.Find(_T("gpiomode0")) != -1) && ((szLineRead.Find(_T("gpiomode0")) < 2))))
//		{
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d"), szTemp, _countof(szTemp), &nData);
//			MIUSetGPIOMode(m_nDevice, 0, nData);
//		}
//		else if (((szLineRead.Find(_T("GPIOMODE1")) != -1) && ((szLineRead.Find(_T("GPIOMODE1")) < 2))) || ((szLineRead.Find(_T("gpiomode1")) != -1) && ((szLineRead.Find(_T("gpiomode1")) < 2))))
//		{
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d"), szTemp, _countof(szTemp), &nData);
//			MIUSetGPIOMode(m_nDevice, 1, nData);
//		}
//		else if (((szLineRead.Find(_T("GPIOMODE2")) != -1) && ((szLineRead.Find(_T("GPIOMODE2")) < 2))) || ((szLineRead.Find(_T("gpiomode2")) != -1) && ((szLineRead.Find(_T("gpiomode2")) < 2))))
//		{
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d"), szTemp, _countof(szTemp), &nData);
//			MIUSetGPIOMode(m_nDevice, 2, nData);
//		}
//		else if (((szLineRead.Find(_T("GPIOMODE3")) != -1) && ((szLineRead.Find(_T("GPIOMODE3")) < 2))) || ((szLineRead.Find(_T("gpiomode3")) != -1) && ((szLineRead.Find(_T("gpiomode3")) < 2))))
//		{
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d"), szTemp, _countof(szTemp), &nData);
//			MIUSetGPIOMode(m_nDevice, 3, nData);
//		}
//		else if (((szLineRead.Find(_T("BULK")) != -1) && ((szLineRead.Find(_T("BULK")) < 2))) || ((szLineRead.Find(_T("Bulk")) != -1) && ((szLineRead.Find(_T("Bulk")) < 2))))
//		{
//			unsigned int	nCount;
//			unsigned char	pData[256];
//			CString	 strInput;
//
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d"), szTemp, _countof(szTemp), &nCount);
//
//			switch (nCount)
//			{
//			case 1:
//				_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d %x"), szTemp, _countof(szTemp), &nCount, pData);
//				break;
//			case 2:
//				_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d %x %x"), szTemp, _countof(szTemp), &nCount, &pData[0], &pData[1]);
//				break;
//			case 3:
//				_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d %x %x %x"), szTemp, _countof(szTemp), &nCount, &pData[0], &pData[1], &pData[2]);
//				break;
//			case 4:
//				_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d %x %x %x %x"), szTemp, _countof(szTemp), &nCount, &pData[0], &pData[1], &pData[2], &pData[3]);
//				break;
//			case 5:
//				_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d %x %x %x %x %x"), szTemp, _countof(szTemp), &nCount, &pData[0], &pData[1], &pData[2], &pData[3], &pData[4]);
//				break;
//			default:
//				break;
//			}
//			if (fInitMode == 2)
//			{
//				errorCode = MIUI2CBurstWrite(m_nDevice, m_stMIUDevice.InitialValue.IICDeviceID, pData[0], 1, &pData[1], nCount - 1);
//				if (errorCode)
//				{
//					errorCount++;
//					TRACE(_T("Error Code : 0x%x\n"), errorCode);
//				}
//			}
//
//		}
//		else if (((szLineRead.Find(_T("BITFIELD")) != -1) && ((szLineRead.Find(_T("BITFIELD")) < 2))) || ((szLineRead.Find(_T("Bitfield")) != -1) && ((szLineRead.Find(_T("Bitfield")) < 2))))
//		{
//			unsigned int	bitfield;
//			unsigned int    ReadValue;
//			unsigned char	value;
//			CString	 strInput;
//			//_stscanf(szLineRead.GetBuffer(0), _T("%s %x %x %d"), nAddress, &bitfield, &value);
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%x %x %d"), &nAddress, &bitfield, &value);
//			if (fInitMode == 1)
//			{
//				MIUReadRegister(m_nDevice, REG_MIU, (unsigned short)nAddress, (unsigned short*)&ReadValue);
//			}
//			else if (fInitMode == 2)
//			{
//				MIUReadRegister(m_nDevice, REG_IIC1, (unsigned short)nAddress, (unsigned short*)&ReadValue);
//			}
//
//			if (value == 0)
//			{
//				ReadValue &= bitfield ^ 0xFFFFFFFF;
//			}
//			else
//			{
//				ReadValue |= bitfield;
//			}
//
//			if (fInitMode == 1)
//			{
//				TRACE(_T("MIU Addr %x, DAta %x \n"), nAddress, ReadValue);
//				MIUWriteRegister(m_nDevice, REG_MIU, (unsigned short)nAddress, (unsigned short)ReadValue);
//			}
//			else if (fInitMode == 2)
//			{
//				TRACE(_T("Sensor Addr %x, DAta %x \n"), nAddress, ReadValue);
//				MIUWriteRegister(m_nDevice, REG_IIC1, (unsigned short)nAddress, (unsigned short)ReadValue);
//				Sleep(1);
//			}
//		}
//		else if (((szLineRead.Find(_T("0x")) != -1) || (szLineRead.Find(_T("0X")) != -1)) && (szLineRead.Find(_T("0")) == 0))
//		{
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%x%x"), &nAddress, &nData);
//
//			if (fInitMode == 1)
//			{
//				TRACE(_T("MIU Addr %x, DAta %x \n"), nAddress, nData);
//				errorCode = MIUWriteRegister(m_nDevice, REG_MIU, (unsigned short)nAddress, (unsigned short)nData);
//				if (errorCode)
//				{
//					errorCount++;
//					TRACE("Error Code : 0x%x\n", errorCode);
//				}
//			}
//			else if (fInitMode == 2)
//			{
//				// 0722
//				if (m_Burst == TRUE && (nAddress == 0x0F12 || nAddress == 0x0F14))
//				{
//					if (BurstWriteLength == 0)
//					{
//						memset(BurstWriteData, 0, sizeof(BurstWriteData));
//
//						BurstWriteData[0] = nData >> 8;
//						BurstWriteData[1] = nData & 0xFF;
//
//						BurstWriteLength = 2;
//						BurstWriteLengthaddr = 2;
//					}
//					else
//					{
//						BurstWriteData[BurstWriteLength] = nData >> 8;
//						BurstWriteData[BurstWriteLength + 1] = nData & 0xFF;
//						BurstWriteLength += 2;
//					}
//
//					if (BurstWriteLength == 2046)
//					{
//						errorCode = MIUI2CBurstWrite(m_nDevice, m_stMIUDevice.InitialValue.IICDeviceID, (unsigned short)nAddress, BurstWriteLengthaddr, BurstWriteData, BurstWriteLength);
//
//						if (errorCode)
//						{
//							errorCount++;
//							TRACE(_T("Burst Write Fail Error Code : 0x%x\n"), errorCode);
//						}
//						else
//						{
//							TRACE(_T("Burst Write Ok  : %d Byte \n"), BurstWriteLength);
//						}
//						BurstWriteLength = 0;
//						BurstWriteLengthaddr = 0;
//					}
//				}
//				else
//				{
//					if (BurstWriteLength > 0)
//					{
//						if (BurstWriteLength == 2)
//						{
//							data = (unsigned short)(BurstWriteData[0] << 8) + BurstWriteData[1];
//							TRACE(_T("Sensor Addr %x, DAta %x \n"), nAddress, data);
//							errorCode = MIUWriteRegister(m_nDevice, REG_IIC1, (unsigned short)nAddress, (unsigned short)data);
//							if (errorCode)
//							{
//								errorCount++;
//								TRACE(_T("Error Code : 0x%x\n"), errorCode);
//							}
//						}
//						else
//						{
//							errorCode = MIUI2CBurstWrite(m_nDevice, m_stMIUDevice.InitialValue.IICDeviceID, (unsigned short)nAddress, BurstWriteLengthaddr, BurstWriteData, BurstWriteLength);
//							if (errorCode)
//							{
//								errorCount++;
//								TRACE(_T("Burst Write Fail Error Code : 0x%x\n"), errorCode);
//							}
//							else
//							{
//								TRACE(_T("Burst Write Ok  : %d Byte \n"), BurstWriteLength);
//							}
//							//Sleep(400);
//						}
//
//						if (bustSleep > 0)
//						{
//							////////////////////////// 20130711 TRACE Ãß°¡
//							TRACE(_T("burst Sleep = %d \n"), bustSleep);
//							Sleep(bustSleep);
//							bustSleep = 0;
//						}
//
//						BurstWriteLength = 0;
//						BurstWriteLengthaddr = 0;
//						//Sleep(100);
//					}
//
//					TRACE(_T("Sensor Addr %x, DAta %x \n"), nAddress, nData);
//					errorCode = MIUWriteRegister(m_nDevice, REG_IIC1, (unsigned short)nAddress, (unsigned short)nData);
//					if (errorCode)
//					{
//						errorCount++;
//						TRACE(_T("Error Code : 0x%x\n"), errorCode);
//					}
//				}
//			}
//		}
//		else if (((szLineRead.Find(_T("I2C_MODE")) != -1) || (szLineRead.Find(_T("I2C_Mode")) != -1)) && (szLineRead.Find(_T("I")) == 0))
//		{
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%s%d"), szTemp, _countof(szTemp), &nData);
//			MIUSetI2CMode(m_nDevice, nData);
//			Sleep(100);
//		}
//		else if ((szLineRead.Find(_T("I2CID")) != -1) && (szLineRead.Find(_T("I")) == 0))
//		{
//			_stscanf_s(szLineRead.GetBuffer(0), _T("%s%x"), szTemp, _countof(szTemp), &nData);
//			MIUSetI2CID(m_nDevice, nData);
//		}
//		else if(szLineRead.Find(_T("0ÍÍ")) != -1)//ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ?"))
//		{
//			break;
//		}
//		else if((szLineRead.GetLength() >= 2) || (szLineRead.GetLength() == 0) || (szLineRead.Find(_T(';')) != -1) || (szLineRead.Find(_T('[')) != -1))
//		{
//			continue;
//		}
//		else
//		{
//			if((GetTickCount() - dwTickCount) > 5000)
//			{
//				break;
//			}
//		}
//	}
//		
//	flInitialFile.Close();
//
//	// 0722
//	if (BurstWriteLength > 0)
//	{
//		if (BurstWriteLength == 2)
//		{
//			data = (unsigned short)(BurstWriteData[0] << 8) + BurstWriteData[1];
//			TRACE("Sensor Addr %x, DAta %x \n", nAddress, data);
//			errorCode = MIUWriteRegister(m_nDevice, REG_IIC1, (unsigned short)nAddress, (unsigned short)data);
//			if (errorCode)
//			{
//				errorCount++;
//				TRACE("Error Code : 0x%x\n", errorCode);
//			}
//		}
//		else
//		{
//			errorCode = MIUI2CBurstWrite(m_nDevice, m_stMIUDevice.InitialValue.IICDeviceID, (unsigned short)nAddress, BurstWriteLengthaddr, BurstWriteData, BurstWriteLength);
//			if (errorCode)
//			{
//				errorCount++;
//				TRACE("Burst Write Fail Error Code : 0x%x\n", errorCode);
//			}
//			else
//			{
//				TRACE("Burst Write Ok  : %d Byte \n", BurstWriteLength);
//			}
//		}
//
//		////////////////////////// 20130711 Ãß°¡
//		if (bustSleep > 0)
//		{
//			TRACE("burst Sleep = %d \n", bustSleep);
//			Sleep(bustSleep);
//			bustSleep = 0;
//
//		}
//
//		BurstWriteLength = 0;
//		BurstWriteLengthaddr = 0;
//		//Sleep(100);
//	}
//
//	if (errorCount != 0)
//	{
//		_stprintf_s(szLog, SIZE_OF_1K, _T("[CCD] I2C & REGISTER ERROR COUNT : %d"), errorCount);
//		AddLog(szLog, 1, m_nUnit);
//
//		return false;
//	}
//
	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CLaonGrabberWrapper::GetCurrent(double* pfCurrent)
{
	//LARGE_INTEGER liCounter1, liCounter2, liFrequency;
	//
	//QueryPerformanceFrequency(&liFrequency); 
	//QueryPerformanceCounter(&liCounter1); 
	//
	//InitializeCalibration(m_nDevice);

	//QueryPerformanceCounter(&liCounter2);

	////Dynamic Mode
	//if(CurrentMeasureMode(m_nDevice, 0) != 0)
	//{
	//	return false;
	//}

	/*if(CurrentMeasureResult(m_nDevice, 0, pfCurrent, 0) != 0)
	{
		return false;
	}*/

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CLaonGrabberWrapper::ChangePatternMode(int nMode)
{
	/*unsigned int	nAddress = 0x3129;
	unsigned int	nData = 0x0080;
	int				errorCode;

	if(m_bOpen == false)
		return false;

	if(nMode == 0)
	{
		nAddress = 0x3129;
		nData = 0x0000;	
	}
	else
	{
		nAddress = 0x3129;
		nData = 0x0080;
	}
	
	errorCode = MIUWriteRegister(m_nDevice, (MIU_REG_TYPE)1, (unsigned short)nAddress, (unsigned short)nData);
	if(errorCode)
	{
		return false;
	}*/

	return true;
}


bool CLaonGrabberWrapper::PatternImageLoad()
{
#if 0
	CFile				ReadFile;
	CFileException		e;
	unsigned int nFileLength = 0;
	TCHAR szPath[SIZE_OF_1K];
	
	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\AA1\\Tp1.raw"), BASE_DATA_PATH);

	if (!ReadFile.Open(szPath, CFile::modeRead, &e))
	{
		//e.ReportError(MB_OK);
		//strLog.Format(_T("Test Pattern ÀÌ¹ÌÁö·Îµå ½ÇÆÐ!\n ÇÁ·Î±×·¥ Àç½ÃÀÛ¹Ù¶ø´Ï´Ù."));
		//GlobalClass.ViewMessagePopup("ALARM", strLog, A_COLOR_RED);
		//GlobalClass.putListLog(strLog, m_nUnit);
		return false;
	}

	//strLog.Format(_T("Test Pattern Image Load OK!"));
	//GlobalClass.putListLog(strLog, m_nUnit);
	nFileLength = (unsigned int)ReadFile.GetLength();
	m_pFrameRawBuffer_TP_Ref1[0] = new unsigned char[nFileLength];
	
	

	ReadFile.Read(m_pFrameRawBuffer_TP_Ref1[0], nFileLength);
	ReadFile.Close();

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\AA1\\Tp2.raw"), BASE_DATA_PATH);
	if (!ReadFile.Open(szPath, CFile::modeRead, &e))
	{
		//e.ReportError(MB_OK);
		//strLog.Format(_T("Test Pattern ÀÌ¹ÌÁö·Îµå ½ÇÆÐ!\n ÇÁ·Î±×·¥ Àç½ÃÀÛ¹Ù¶ø´Ï´Ù."));
		//GlobalClass.ViewMessagePopup("ALARM", strLog, A_COLOR_RED);
		//GlobalClass.putListLog(strLog, m_nUnit);
		return false;
	}
	nFileLength = (unsigned int)ReadFile.GetLength();
	m_pFrameRawBuffer_TP_Ref1[1] = new unsigned char[nFileLength];
	ReadFile.Read(m_pFrameRawBuffer_TP_Ref1[1], nFileLength);
	ReadFile.Close();
#endif
	return true;
	//CWnd* pWnd_ImageTraget = EEpromMainDlg->GetDlgItem(IDC_STATIC_IMAGE1);
}
//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CLaonGrabberWrapper::ControlISP(bool bOn)
{
	//if (bOn)
	//{
	//	unsigned short nwriteData = 0;
	//	unsigned char bLsc = 0;
	//	unsigned char bAWB = 0;
	//	unsigned char bColorCorrection = 0;
	//	unsigned char bGammaCorrection = 0;

	//	unsigned char bColorOrder = 0;
	//	unsigned char bInterpolation = 0;

	//	//bLsc = m_chkLSC;

	//	if (m_stMIUDevice.iPixelFormat == MIU_YUV422_YUYV_PACKED)
	//		bInterpolation = 1;
	//	else
	//		bInterpolation = 2;
	//	
	//	if ((m_nPixelFormat & 0x0000000F) % 4 == 0) //BG
	//		bColorOrder = 2;
	//	else if ((m_nPixelFormat & 0x0000000F) % 4 == 1) //GR
	//		bColorOrder = 1;
	//	else if ((m_nPixelFormat & 0x0000000F) % 4 == 2) //RG
	//		bColorOrder = 0;
	//	else if ((m_nPixelFormat & 0x0000000F) % 4 == 3) //GB
	//		bColorOrder = 3;
	//			
	//	Sleep(100);
	//	nwriteData = ((bAWB << 11) + (bColorCorrection << 10) + (bGammaCorrection << 9) + (bLsc << 8) + (bColorOrder << 4) + bInterpolation);

	//	MIUWriteRegister(m_nDevice, REG_MIU, 0x36, nwriteData);
	//}
	//else
	//{
	//	MIUWriteRegister(m_nDevice, REG_MIU, 0x36, 0x0000);
	//}

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CLaonGrabberWrapper::ChangeMono()
{
	int errorCode = 0;

	// Image Display Stop
	this->SetCurrentState(CCD_GRAB_PAUSE);

	m_stMIUDevice.bRccc = 0;
	
	Sleep(500);

	// Pause
	//MIUPause(m_nDevice);

	/*if (m_stMIUDevice.image != NULL)
	{
		cvReleaseImage(&m_stMIUDevice.image);
		m_stMIUDevice.image = NULL;
	}*/
	
	if (m_stMIUDevice.imageItp != NULL)
	{
		cvReleaseImage(&m_stMIUDevice.imageItp);
		m_stMIUDevice.imageItp = NULL;
	}

	/*if (m_stMIUDevice.ColorConvertItp != NULL)
	{
		cvReleaseImage(&m_stMIUDevice.ColorConvertItp);
		m_stMIUDevice.ColorConvertItp = NULL;
	}*/
	///////////////////////////////////////////////////////////////////////////////////////////////

	m_stMIUDevice.iPixelFormat = MIU_MONO8;
	m_stMIUDevice.nBitPerPixel = ((m_stMIUDevice.iPixelFormat & 0x00FF0000) >> 16);

	this->ControlISP(true);

	/*if ((m_stMIUDevice.iPixelFormat == MIU_RGB8_PACKED) || (m_stMIUDevice.iPixelFormat == MIU_BGR8_PACKED))
	{
		if(m_stMIUDevice.image == NULL)
			m_stMIUDevice.image = cvCreateImageHeader(cvSize(m_stMIUDevice.nWidth, m_stMIUDevice.nHeight), IPL_DEPTH_8U, 3);
	}
	else if ((m_stMIUDevice.iPixelFormat == MIU_RGB565) || (m_stMIUDevice.iPixelFormat == MIU_BGR565))
	{
		if (m_stMIUDevice.image == NULL)
			m_stMIUDevice.image = cvCreateImageHeader(cvSize(m_stMIUDevice.nWidth, m_stMIUDevice.nHeight), IPL_DEPTH_8U, 2);
	}
	else
	{
		if (m_stMIUDevice.image == NULL)
			m_stMIUDevice.image = cvCreateImageHeader(cvSize(m_stMIUDevice.nWidth, m_stMIUDevice.nHeight), IPL_DEPTH_8U, 1);
		
		if (m_stMIUDevice.nBitPerPixel > 8)
		{
			if(m_stMIUDevice.ColorConvertItp == NULL)
				m_stMIUDevice.ColorConvertItp = cvCreateImage(cvSize(m_stMIUDevice.nWidth, m_stMIUDevice.nHeight), IPL_DEPTH_8U, 1);
		}
	}*/

	if(m_stMIUDevice.imageItp == NULL)
		m_stMIUDevice.imageItp = cvCreateImage(cvSize(m_stMIUDevice.nWidth, m_stMIUDevice.nHeight), IPL_DEPTH_8U, 3);


	///////////////////////////////////////////////////////////////////////////////////////////////
	// Resume
	//MIUResumeChageFormat(m_nDevice, m_stMIUDevice.iPixelFormat);
	Sleep(300);

	// Image Display restart
	this->SetCurrentState(CCD_GRAB_LIVE);

	this->ChangePatternMode(1);

	return TRUE;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CLaonGrabberWrapper::ChangeRaw()
{
	int errorCode = 0;

	// Image Display Stop
	this->SetCurrentState(CCD_GRAB_PAUSE);

	m_stMIUDevice.bRccc = 1;

	// Pause
	//MIUPause(m_nDevice);

	/*if (m_stMIUDevice.image != NULL)
	{
		cvReleaseImage(&m_stMIUDevice.image);
		m_stMIUDevice.image = NULL;
	}*/

	if (m_stMIUDevice.imageItp != NULL)
	{
		cvReleaseImage(&m_stMIUDevice.imageItp);
		m_stMIUDevice.imageItp = NULL;
	}

	/*if (m_stMIUDevice.ColorConvertItp != NULL)
	{
		cvReleaseImage(&m_stMIUDevice.ColorConvertItp);
		m_stMIUDevice.ColorConvertItp = NULL;
	}*/

	m_stMIUDevice.iPixelFormat = MIU_BAYERBG12_PACKED;	// Start RAW

	m_stMIUDevice.nBitPerPixel = ((m_stMIUDevice.iPixelFormat & 0x00FF0000) >> 16);

	this->ControlISP(false);

	/*if ((m_stMIUDevice.iPixelFormat == MIU_RGB8_PACKED) || (m_stMIUDevice.iPixelFormat == MIU_BGR8_PACKED))
	{
		if(m_stMIUDevice.image == NULL)
			m_stMIUDevice.image = cvCreateImageHeader(cvSize(m_stMIUDevice.nWidth, m_stMIUDevice.nHeight), IPL_DEPTH_8U, 3);
	}
	else if ((m_stMIUDevice.iPixelFormat == MIU_RGB565) || (m_stMIUDevice.iPixelFormat == MIU_BGR565))
	{
		if(m_stMIUDevice.image == NULL)
			m_stMIUDevice.image = cvCreateImageHeader(cvSize(m_stMIUDevice.nWidth, m_stMIUDevice.nHeight), IPL_DEPTH_8U, 2);
	}
	else
	{
		if(m_stMIUDevice.image == NULL)
			m_stMIUDevice.image = cvCreateImageHeader(cvSize(m_stMIUDevice.nWidth, m_stMIUDevice.nHeight), IPL_DEPTH_8U, 1);
		if (m_stMIUDevice.nBitPerPixel > 8)
		{
			if(m_stMIUDevice.ColorConvertItp == NULL)
				m_stMIUDevice.ColorConvertItp = cvCreateImage(cvSize(m_stMIUDevice.nWidth, m_stMIUDevice.nHeight), IPL_DEPTH_8U, 1);
		}
	}*/
	
	if(m_stMIUDevice.imageItp == NULL)
		m_stMIUDevice.imageItp = cvCreateImage(cvSize(m_stMIUDevice.nWidth, m_stMIUDevice.nHeight), IPL_DEPTH_8U, 3);


	///////////////////////////////////////////////////////////////////////////////////////////////
	// Resume
	//MIUResumeChageFormat(m_nDevice, m_stMIUDevice.iPixelFormat);
	Sleep(300);

	// Image Display restart
	this->SetCurrentState(CCD_GRAB_LIVE);

	this->ChangePatternMode(0);

	return TRUE;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CLaonGrabberWrapper::CopyInspImage(int nType, BYTE* GrabImage)
{
	CString str;
	if (nType == MID_3000K_RAW)
	{
		str.Format("3000K");
		memcpy(g_clLaonGrabberWrapper[m_nUnit].vDefectMidBuffer_3000k, GrabImage, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize());
		RawImageSave(str, g_clLaonGrabberWrapper[m_nUnit].vDefectMidBuffer_3000k);
		if (g_clModelData[m_nUnit].m_nNgImageSaveUse == 0)
		{
			

		}
	}
	else if (nType == MID_6500K_RAW)
	{
		/*str.Format("6500K)");
		memcpy(g_clLaonGrabberWrapper[m_nUnit].vDefectMidBuffer_6500K, GrabImage, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize());
		RawImageSave(str, g_clLaonGrabberWrapper[m_nUnit].vDefectMidBuffer_6500K);
		if (g_clModelData[m_nUnit].m_nNgImageSaveUse == 0)
		{
			

		}*/
	}
	else if (nType == MID_5000k_RAW)
	{
		/*str.Format("5000k");
		memcpy(g_clLaonGrabberWrapper[m_nUnit].vDefectMidBuffer_5000k, GrabImage, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize());
		RawImageSave(str, g_clLaonGrabberWrapper[m_nUnit].vDefectMidBuffer_5000k);
		if (g_clModelData[m_nUnit].m_nNgImageSaveUse == 0)
		{
			

		}*/
	}
	else if (nType == LOW_LEVEL_RAW)
	{
		str.Format("dark");
		memcpy(g_clLaonGrabberWrapper[m_nUnit].vDefectLowBuffer, GrabImage, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize());
		RawImageSave(str, g_clLaonGrabberWrapper[m_nUnit].vDefectLowBuffer);
		if (g_clModelData[m_nUnit].m_nNgImageSaveUse == 0)
		{
			

		}
	}
	else if (nType == OC_IR_RAW)
	{
		/*str.Format("Ir");
		memcpy(g_clLaonGrabberWrapper[m_nUnit].vDefectMidBuffer_IR, GrabImage, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize());
		RawImageSave(str, g_clLaonGrabberWrapper[m_nUnit].vDefectMidBuffer_IR);
		if (g_clModelData[m_nUnit].m_nNgImageSaveUse == 0)
		{
			

		}*/
	}
	else if (nType == UV_BEFORE_CHART_RAW)
	{
		str.Format("UVBeforeChart");
		memcpy(g_clLaonGrabberWrapper[m_nUnit].vChartBuffer, GrabImage, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize());
		RawImageSave(str, g_clLaonGrabberWrapper[m_nUnit].vChartBuffer);
		if (g_clModelData[m_nUnit].m_nNgImageSaveUse == 0)
		{
			

		}
	}
	else if (nType == UV_AFTER_CHART_RAW)
	{
		str.Format("Chart");
		memcpy(g_clLaonGrabberWrapper[m_nUnit].vChartBuffer, GrabImage, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize());
		RawImageSave(str, g_clLaonGrabberWrapper[m_nUnit].vChartBuffer, false);		//´Ù¸¥°÷¿¡¼­ jpgÀúÀå
		if (g_clModelData[m_nUnit].m_nNgImageSaveUse == 0)
		{
			

		}
	}
	else if (nType == CHART_RAW_IMAGE)
	{
		str.Format("ChartRaw");
		memcpy(g_clLaonGrabberWrapper[m_nUnit].vChartBuffer, GrabImage, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize());
		RawImageSave(str, g_clLaonGrabberWrapper[m_nUnit].vChartBuffer, false);
	}
	else if (nType == CHART_YUV_IMAGE)
	{
		str.Format("ChartYuv");
		memcpy(g_clLaonGrabberWrapper[m_nUnit].vChartBuffer, GrabImage, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize());
		RawImageSave(str, g_clLaonGrabberWrapper[m_nUnit].vChartBuffer, false);
	}
	else
	{
		//¸ðµÎ ÃÊ±âÈ­?

		memset(g_clLaonGrabberWrapper[m_nUnit].vChartBuffer, 0, m_pBoard->GetFrameRawSize());
		memset(g_clLaonGrabberWrapper[m_nUnit].vDefectMidBuffer_3000k, 0, m_pBoard->GetFrameRawSize());
		//memset(g_clLaonGrabberWrapper[m_nUnit].vDefectMidBuffer_5000k, 0, m_pBoard->GetFrameRawSize());
		//memset(g_clLaonGrabberWrapper[m_nUnit].vDefectMidBuffer_6500K, 0, m_pBoard->GetFrameRawSize());
		memset(g_clLaonGrabberWrapper[m_nUnit].vDefectLowBuffer, 0, m_pBoard->GetFrameRawSize());
		//memset(g_clLaonGrabberWrapper[m_nUnit].vDefectMidBuffer_IR, 0, m_pBoard->GetFrameRawSize());
		return;
		
	}
	
	str.Empty();

}

void CLaonGrabberWrapper::RawImageSave(CString nType , BYTE* LoadImg, bool mJpgSaveUse)
{
	TCHAR szPath[SIZE_OF_1K];
	TCHAR szFilePath[SIZE_OF_1K];
	SYSTEMTIME stSysTime;
	CFileFind clFinder;
	CString sFileMode = _T("");
	CString cnamePath;
	CFile clFile;
	FILE* fp;

	cnamePath.Format("%s", g_clTaskWork[m_nUnit].m_szChipID);
	cnamePath.Replace(":", ";");


	int nStepNo;
	int i = 0;
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

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE\\%04d%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE\\%04d%02d\\%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE\\%04d%02d\\%02d\\%s"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, cnamePath);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	
	_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%s_%s_%02d%02d%02d.raw"), szPath, cnamePath, nType, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);

	CFile           savefile;
	CFileException  e;

	if (!savefile.Open(szFilePath, CFile::modeCreate | CFile::modeWrite, &e))
	{
		
		AddLog("RAW IMAGE SAVE FAIL", 0, m_nUnit);

		sFileMode.Empty();
		cnamePath.Empty();
		return;
	}

	savefile.Write(LoadImg, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize());

	savefile.Close();

	if (mJpgSaveUse == true)
	{
		_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%s_%s_%02d%02d%02d.jpg"), szPath, cnamePath, nType, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);
		std::string strPath = std::string(szFilePath);
		Mat jpgImage(g_clModelData[m_nUnit].m_nHeight, g_clModelData[m_nUnit].m_nWidth, CV_8UC3);

		ACMISSoftISP::xMakeBMP(LoadImg, (byte*)g_clLaonGrabberWrapper[m_nUnit].m_pTestBuffer,
			g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight, g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n);

		jpgImage.data = g_clLaonGrabberWrapper[m_nUnit].m_pTestBuffer;
		imwrite(szFilePath, jpgImage);
	}

	sFileMode.Empty();
	cnamePath.Empty();
}

void CLaonGrabberWrapper::JpgMatSave(Mat cvMatImage, int index)
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
	::GetLocalTime(&stSysTime);

	CString _name = _T("");
	if (index == 0)
	{
		_name = "FDF";
	}
	else if (index == 1)
	{
		_name = "Lcb";
	}
	else if (index == 2)
	{
		_name = "Ymean";
	}
	else if (index == 3)
	{
		_name = "DefectBright";
	}
	else if (index == 4)
	{
		_name = "DefectDark";
	}
	else if (index == 5)
	{
		_name = "RI";
	}
	else
	{
		_name = "temp";
	}

	if (_tcslen(g_clTaskWork[m_nUnit].m_szLotID) <= 0)
		_tcscpy_s(g_clTaskWork[m_nUnit].m_szLotID, SIZE_OF_100BYTE, _T("(NULL)"));

	if (_tcslen(g_clTaskWork[m_nUnit].m_szChipID) <= 0)
		_tcscpy_s(g_clTaskWork[m_nUnit].m_szChipID, SIZE_OF_100BYTE, _T("(NULL)"));

	//_tcscpy_s(g_clTaskWork[m_nUnit].m_szChipID, SIZE_OF_100BYTE, _T("L191209A615"));

	if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
		CreateDirectory(BASE_LOG_PATH, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE"), BASE_LOG_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE\\%04d%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE\\%04d%02d\\%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);


	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE\\%04d%02d\\%02d\\%s"), BASE_LOG_PATH,  stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, g_clTaskWork[m_nUnit].m_szChipID);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);


	//if (index == 3)
	//	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE\\AA%d\\%04d%02d\\%02d\\%s_%s_%04d%02d%02d%02d%02d%02d"), BASE_LOG_PATH, m_nUnit + 1, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, g_clTaskWork[m_nUnit].m_szChipID, _name, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);



	if (index == 3)
	{
		_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%s_%s_%04d%02d%02d%02d%02d%02d.jpg"), szPath, g_clTaskWork[m_nUnit].m_szChipID, _name, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);
	}
	else {
		_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%s_%d_%s_%04d%02d%02d%02d%02d%02d.jpg"), szPath, g_clTaskWork[m_nUnit].m_szChipID, g_clSysData.m_nUnitNo, _name, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);
	}
	imwrite(szFilePath, cvMatImage);
	 
	_stprintf_s(g_clTaskWork[m_nUnit].m_szImagePath, SIZE_OF_1K, szFilePath);
}

void CLaonGrabberWrapper::JpgImageSave(IplImage* jpgImg, int index)
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
	::GetLocalTime(&stSysTime);

	CString _name = _T("");
	if (index == 0)
	{
		_name = "BlackSpot";
	}
	else if (index == 1)
	{
		_name = "Lcb";
	}
	else if (index == 2)
	{
		_name = "Ymean";
	}
	else if (index == 3)
	{
		_name = "DefectBright";
	}
	else if (index == 4)
	{
		_name = "DefectDark";
	}
	else if (index == 5)
	{
		_name = "RI";
	}
	else
	{
		_name = "temp";
	}

	if (_tcslen(g_clTaskWork[m_nUnit].m_szLotID) <= 0)
		_tcscpy_s(g_clTaskWork[m_nUnit].m_szLotID, SIZE_OF_100BYTE, _T("(NULL)"));

	if (_tcslen(g_clTaskWork[m_nUnit].m_szChipID) <= 0)
		_tcscpy_s(g_clTaskWork[m_nUnit].m_szChipID, SIZE_OF_100BYTE, _T("(NULL)"));

	//_tcscpy_s(g_clTaskWork[m_nUnit].m_szChipID, SIZE_OF_100BYTE, _T("L191209A615"));

	if (clFinder.FindFile(BASE_LOG_PATH) == FALSE)
		CreateDirectory(BASE_LOG_PATH, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE"), BASE_LOG_PATH);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE\\%04d%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE\\%04d%02d\\%02d"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);


	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE\\%04d%02d\\%02d\\%s"), BASE_LOG_PATH, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, g_clTaskWork[m_nUnit].m_szChipID);
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);


	//if (index == 3)
	//	_stprintf_s(szPath, SIZE_OF_1K, _T("%s\\IMAGE\\AA%d\\%04d%02d\\%02d\\%s_%s_%04d%02d%02d%02d%02d%02d"), BASE_LOG_PATH, m_nUnit + 1, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, g_clTaskWork[m_nUnit].m_szChipID, _name, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);

	

	if (index == 3)
	{
		_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%s_%s_%04d%02d%02d%02d%02d%02d.jpg"), szPath, g_clTaskWork[m_nUnit].m_szChipID, _name, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);
	}
	else {
		_stprintf_s(szFilePath, SIZE_OF_1K, _T("%s\\%s_%d_%s_%04d%02d%02d%02d%02d%02d.jpg"), szPath, g_clTaskWork[m_nUnit].m_szChipID, g_clSysData.m_nUnitNo, _name, stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute, stSysTime.wSecond);
	}
	//cvSaveImage(szFilePath, jpgImg);

	cv::Mat imgOriginal = cvarrToMat(jpgImg);
	imwrite((LPSTR)(LPCTSTR)szFilePath, imgOriginal);

	_stprintf_s(g_clTaskWork[m_nUnit].m_szImagePath, SIZE_OF_1K, szFilePath);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
IplImage* CLaonGrabberWrapper::RegionCopy(IplImage* src)
{
	// Must have dimensions of output image 
	CvRect roi = cvRect(0, 2, g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight - 8);
	IplImage* cropped = cvCreateImage(cvSize(roi.width, roi.height), src->depth, src->nChannels);

	// Say what the source region is 
	cvSetImageROI(src, roi);

	// Do the copy 
	cvCopy(src, cropped);
	cvResetImageROI(src);

	return cropped;
}


CString CLaonGrabberWrapper::GetErrorStr(int errorCode)
{
	CString retStr;
	switch (errorCode)
	{
	case ERR_BOARD_GET_LIST:
		retStr = "ERR_BOARD_GET_LIST";
		break;
	case ERR_BOARD_NO_DEVICE:
		retStr = "ERR_BOARD_NO_DEVICE";
		break;
	case ERR_BOARD_OPEN:
		retStr = "ERR_BOARD_OPEN";
		break;
	case ERR_BOARD_INIT:
		retStr = "ERR_BOARD_INIT";
		break;
	case ERR_BOARD_SET_POWER_5_12:
		retStr = "ERR_BOARD_SET_POWER_5_12";
		break;
	case ERR_BOARD_GRAB_START:
		retStr = "ERR_BOARD_GRAB_START";
		break;
	case ERR_BOARD_I2C_WRITE:
		retStr = "ERR_BOARD_I2C_WRITE";
		break;
	case ERR_BOARD_I2C_READ:
		retStr = "ERR_BOARD_I2C_READ";
		break;
	case ERR_BOARD_BOOT_CAMERA:
		retStr = "ERR_BOARD_BOOT_CAMERA";
		break;
	case ERR_BOARD_CLOSE:
		retStr = "ERR_BOARD_CLOSE";
		break;
	case ERR_BOARD_LOAD_MODEL:
		retStr = "ERR_BOARD_LOAD_MODEL";
		break;
	default:
		break;
	}
	return retStr;
}
