#include "stdafx.h"
#include "PriGrabberWrapper.h"

//-----------------------------------------------------------------------------
//
//	생성자
//
//-----------------------------------------------------------------------------
CPriGrabberWrapper::CPriGrabberWrapper()
{
	m_bOpen = false;
	m_nCurrentState = CCD_GRAB_STOP;
	m_pImgBuff8Bit = NULL;
	m_pImgBuff12Bit = NULL;
}

//-----------------------------------------------------------------------------
//
//	소멸자
//
//-----------------------------------------------------------------------------
CPriGrabberWrapper::~CPriGrabberWrapper()
{
	int i;

	for(i = 0; i < 3; i++)
	{
		if(m_pGrabBuff[i] != NULL)
			cvReleaseImage(&m_pGrabBuff[i]);

		if(m_pImageBuff[i] != NULL)
			cvReleaseImage(&m_pImageBuff[i]);
	}

	if(m_pImageInspBuff != NULL)
		cvReleaseImage(&m_pImageInspBuff);

	if(m_pImageInsp8Bit != NULL)
		cvReleaseImage(&m_pImageInsp8Bit);

	if(m_pImageInsp8Bit956 != NULL)
		cvReleaseImage(&m_pImageInsp8Bit956);

	if(m_pImgBuff8Bit != NULL)
		free(m_pImageInsp8Bit);

	if(m_pImgBuff12Bit != NULL)
		free(m_pImgBuff12Bit);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CPriGrabberWrapper::GetCcdState()
{
	if (m_nCurrentState == CCD_GRAB_LIVE && g_clTaskWork[m_nUnit].m_fFps > g_clModelData[m_nUnit].m_fFpsStopVal)
	{
		return true;
	}
	
	return false;
}

//-----------------------------------------------------------------------------
//
//	이미지 버퍼 할당
//
//-----------------------------------------------------------------------------
void CPriGrabberWrapper::AllocImageBuff()
{
	int i;

	m_pImgBuff8Bit = (unsigned char*)malloc(g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight);
	m_pImgBuff12Bit = (unsigned char*)malloc(g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight * 2);

	for (i = 0; i < 3; i++)
	{
		m_pGrabBuff[i] = cvCreateImage(cvSize(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight), IPL_DEPTH_8U, 3);
		m_pImageBuff[i] = cvCreateImage(cvSize(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight), IPL_DEPTH_8U, 1);
	}

	m_pImageInspBuff = cvCreateImage(cvSize(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight), IPL_DEPTH_8U, 3);
	m_pImageInsp8Bit = cvCreateImage(cvSize(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight), IPL_DEPTH_8U, 3);
	m_pImageInsp8Bit956 = cvCreateImage(cvSize(g_clModelData[m_nUnit].m_nWidth, (g_clModelData[m_nUnit].m_nHeight - 8)), IPL_DEPTH_8U, 3);
}

//-----------------------------------------------------------------------------
//
//	디바이스 오픈
//
//-----------------------------------------------------------------------------
bool CPriGrabberWrapper::OpenDevice()
{	
#ifndef ON_LINE_GRABBER
	return true;
#endif

	char swVersion[128];
	TCHAR szLog[SIZE_OF_1K];
	int nRetVal;

	nRetVal = m_clPciExp.DeviceOpen(m_nDevice);

	switch (nRetVal)
	{
	case STATUS_PCIEXP_NODEVICE:
		g_PushLogQueue(_T("Device Open Error : No Device Found!"), 1, m_nUnit);
		break;
	case STATUS_PCIEXP_CLOSEFIRST:
		g_PushLogQueue(_T("Device Open Error : Close Device First!"), 1, m_nUnit);
		break;
	case STATUS_PCIEXP_ALLOCERR:
		g_PushLogQueue(_T("Device Open Error : Physical Memory Allocation Failed!"), 1, m_nUnit);
		break;
	}

	if ( nRetVal != STATUS_PCIEXP_SUCCESS)
	{
		return false;
	}

	Sleep(100);

	nRetVal = m_clPciExp.DeviceReset();
	if (nRetVal != STATUS_PCIEXP_SUCCESS)
	{
		g_PushLogQueue(_T("Image Grabber Reset Fail, Check Power or Optic Cable!!"), 1, m_nUnit);
		return false;
	}
	g_PushLogQueue(_T("Image Grabber Reset. OK!"), 0, m_nUnit);

	m_clPciExp.CM_GetSWVersionInfo(&swVersion[0]);
	_stprintf_s(szLog, SIZE_OF_1K, _T("SW Version : %s"), &swVersion[0]);
	g_PushLogQueue(szLog, 0, m_nUnit);

	m_bOpen = true;

	return true;
}

//-----------------------------------------------------------------------------
//
//	디바이스 CLOSE
//
//-----------------------------------------------------------------------------
bool CPriGrabberWrapper::CloseDevice()
{
#ifndef ON_LINE_GRABBER
	return true;
#endif

	if (m_bOpen == false)
		return true;

	if (m_clPciExp.DeviceClose() != STATUS_PCIEXP_SUCCESS)
	{
		g_PushLogQueue(_T("Device Close Fail"), 1, m_nUnit);
		return false;
	}

	m_bOpen = false;
	return true;
}

//-----------------------------------------------------------------------------
//
//	디바이스 CONNECT
//
//-----------------------------------------------------------------------------
bool CPriGrabberWrapper::ConnectDevice()
{
#ifndef ON_LINE_GRABBER
	return true;
#endif

	int nRetVal;
	TCHAR szLog[SIZE_OF_1K];
	char hwVersion[16];
	char fwVersion[16];
	int nBoardID;

	if (m_bOpen == false)
	{
		g_PushLogQueue(_T("Image Grabber Device Not Opend"), 1, m_nUnit);
		return false;
	}

	nRetVal = m_clPciExp.DeviceReset();
	Sleep(100);
	if (nRetVal != STATUS_PCIEXP_SUCCESS)
	{
		g_PushLogQueue(_T("Image Grabber Init Fail. Check Power or Optic Cable"), 1, m_nUnit);
		return false;
	}

	m_clPciExp.CM_GetImageGrabberVersion(&hwVersion[0], &fwVersion[0]);
	_stprintf_s(szLog, SIZE_OF_1K, _T("Grabber Version : %s, %s"), &hwVersion[0], &fwVersion[0]);
	g_PushLogQueue(szLog, 0, m_nUnit);

	nBoardID = m_clPciExp.CM_GetImageGrabberID();
	_stprintf_s(szLog, SIZE_OF_1K, _T("Image Grabber ID : %d"), nBoardID);
	g_PushLogQueue(szLog, 0, m_nUnit);

	m_clPciExp.CM_SetGpio1P8Dir(GPIO_1P8_PORT13, 0);
	m_clPciExp.CM_SetGpio1P8Dir(GPIO_1P8_PORT15, 0);
	m_clPciExp.CM_SetGpio1P8Dir(GPIO_1P8_PORT19, 0);
	m_clPciExp.CM_SetGpio1P8Dir(GPIO_1P8_PORT21, 0);
	m_clPciExp.CM_SetGpio1P8Dir(GPIO_1P8_PORT25, 0);
	m_clPciExp.CM_SetGpio1P8Dir(GPIO_1P8_PORT27, 0);
	g_PushLogQueue(_T("Gpio1P8s are  all output"), 0, m_nUnit);

	m_clPciExp.CM_SetGpio3P3Dir(GPIO_3P3_PORT31, 1);
	m_clPciExp.CM_SetGpio3P3Dir(GPIO_3P3_PORT33, 1);
	g_PushLogQueue(_T("Gpio3P3s are  all input"), 0, m_nUnit);

	m_clPciExp.CM_SetMIPIGpio(0);

	g_PushLogQueue(_T("Image Grabber Init. OK!"), 0, m_nUnit);

	m_clPciExp.SetErrLog(1, true);

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CPriGrabberWrapper::DisconnectDevice()
{
#ifndef ON_LINE_GRABBER
	return true;
#endif

	if (m_bOpen == false)
		return true;

	m_clPciExp.CM_VoltageMeasurementEnable(0);
	m_clPciExp.CM_CurrentMeasurementEnable(0);
	
	if (m_nCurrentState == CCD_GRAB_LIVE)
	{
		this->StopGrab();
	}

	m_clPciExp.DeviceReset();

	return true;
}

//-----------------------------------------------------------------------------
//
//	보드 초기화
//
//-----------------------------------------------------------------------------
bool CPriGrabberWrapper::InitBoard()
{
#ifndef ON_LINE_GRABBER
	return true;
#endif

	TCHAR szLog[SIZE_OF_1K];
	float freq = 23.0;
	int wrFreq = 8;
	int i2cClk = 100;
	int nRetVal;
	char tap;

	if (m_bOpen == false)
	{
		g_PushLogQueue(_T("Image Grabber Device Not Opend"), 1, m_nUnit);
		return false;
	}

	m_clPciExp.CM_SetGpio1P8(GPIO_1P8_PORT13, 0);
	m_clPciExp.CM_SetGpio1P8(GPIO_1P8_PORT15, 0);
	m_clPciExp.CM_SetGpio1P8(GPIO_1P8_PORT19, 0);

	nRetVal = m_clPciExp.CM_SetMclk(1, freq);
	if (nRetVal != STATUS_PCIEXP_SUCCESS)
	{
		m_clPciExp.DeviceReset();
		g_PushLogQueue(_T("Main Clock Set Fail"), 0, m_nUnit);
	}
	g_PushLogQueue(_T("Main Clock Set Success"), 0, m_nUnit);

	nRetVal = m_clPciExp.CM_SetAuxClk(1, wrFreq);
	if (nRetVal != STATUS_PCIEXP_SUCCESS)
	{
		m_clPciExp.DeviceReset();
		g_PushLogQueue(_T("Aux Clock Set Fail"), 0, m_nUnit);
	}
	g_PushLogQueue(_T("Aux Clock Set Success"), 0, m_nUnit);

	m_clPciExp.CM_I2CSetClk(i2cClk);	// I2C clock
	_stprintf_s(szLog, SIZE_OF_1K ,_T("I2C CLOCK = %dkHz"), i2cClk);
	g_PushLogQueue(szLog, 0, m_nUnit);

	// 2. power enable
	m_clPciExp.CM_EnablePower(POWER_CH1, TRUE);
	m_clPciExp.CM_EnablePower(POWER_CH2, TRUE);
	m_clPciExp.CM_EnablePower(POWER_CH3, TRUE);
	m_clPciExp.CM_EnablePower(POWER_CH4, TRUE);
	m_clPciExp.CM_EnablePower(POWER_LED, TRUE);
	Sleep(100);
	// 3. camera module reset 		

	m_clPciExp.CM_SetGpio1P8(GPIO_1P8_PORT13, 1);	Sleep(1);
	m_clPciExp.CM_SetGpio1P8(GPIO_1P8_PORT15, 1);	Sleep(1);
	m_clPciExp.CM_SetGpio1P8(GPIO_1P8_PORT19, 1);	Sleep(1);

	// 이전 FW5.4 버전용으로
	//m_cPcie.CM_SetGpio(0, 1) ;	Sleep(1) ;
	//m_cPcie.CM_SetGpio(1, 1) ;	Sleep(1) ;
	//m_cPcie.CM_SetGpio(2, 1) ;	Sleep(1) ;

	Sleep(100);
	// 4. power monitoring
	m_clPciExp.CM_VoltageMeasurementEnable(1);
	m_clPciExp.CM_CurrentMeasurementEnable(1);
	m_clPciExp.CM_FlashPowerMeasurementEnable(1);
	
	// 5. img infomation set
	m_clPciExp.CM_GetGrabberParamPhaseTap(&tap);
	_stprintf_s(szLog, SIZE_OF_1K, _T("MIPI Signal Tap : %d"), tap);
	g_PushLogQueue(szLog, 0, m_nUnit);

	m_clPciExp.CM_SetMIPIGpio(0);

	Sleep(0);

	// output format sel.
	m_clPciExp.CM_SetOutputFormat(OUT_FORMAT_12BIT);
	//if (m_bOutFormatRaw8 == 1)	char			m_clPciExp.CM_SetOutputFormat(OUT_FORMAT_RAW8);
	//else if (m_bOutFormat12Bit == 1)	m_clPciExp.CM_SetOutputFormat(OUT_FORMAT_12BIT);
	//else	m_cPcie.CM_SetOutputFormat(OUT_FORMAT_RAW10);

	return true;

}

//-----------------------------------------------------------------------------
//
//	센서 초기화(센서 구동)
//
//-----------------------------------------------------------------------------
bool CPriGrabberWrapper::InitSensor()
{
#ifndef ON_LINE_GRABBER
	return true;
#endif

	TCHAR szLog[SIZE_OF_1K];
	unsigned char addr;
	I2C_CMD_LIST cmd[2048];
	tagI2C_RESULT i2cResult;
	unsigned int sensorOTPM[8];
	int cmdNum;
	int errorCount = 0;
	int nRetVal;
	int i;

	if (m_bOpen == false)
	{
		g_PushLogQueue(_T("Image Grabber Device Not Opend"), 1, m_nUnit);
		return false;
	}

	nRetVal = m_clPciExp.INI_GetI2cSlaveAddr(CT2A(g_clModelData[m_nUnit].m_szIniPath), &addr);
	if (nRetVal != STATUS_PCIEXP_SUCCESS)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("Grabber Ini File(%s) Error"), g_clModelData[m_nUnit].m_szIniPath);
		g_PushLogQueue(szLog, 1, m_nUnit);

		return false;
	}

	cmdNum = m_clPciExp.INI_GetI2cCommands(CT2A(g_clModelData[m_nUnit].m_szIniPath), addr, cmd, 512);
	m_clPciExp.AR0132_ReadOTPM(sensorOTPM);

	for (i = 0; i < cmdNum; i++)
	{
		if (cmd[i].cSlaveID == 0xff)
		{
			Sleep(cmd[i].snAddr);
			_stprintf_s(szLog, SIZE_OF_1K, _T("I2C Res Sleep : %d"), cmd[i].snAddr);
			g_PushLogQueue(szLog, 0, m_nUnit);
		}
		else
		{
			switch (cmd[i].nI2cMode)
			{
			case 3:		nRetVal = m_clPciExp.CM_I2CBurstWrite(0, 2, 2, addr, cmd[i].snAddr, (int*)&cmd[i].cWriteVal, 1);	break;
			case 4:		nRetVal = m_clPciExp.CM_I2CBurstWrite(0, 2, 4, addr, cmd[i].snAddr, (int*)&cmd[i].cWriteVal, 1);	break;
			default:	nRetVal = m_clPciExp.CM_I2CBurstWrite(0, 2, 1, addr, cmd[i].snAddr, (int*)&cmd[i].cWriteVal, 1);	break;
			}

			if (nRetVal == STATUS_PCIEXP_SUCCESS)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("I2C Write Ok : SlaveAddr = %.2x, RegAddr = %.4x, Data = %.8x"), addr, cmd[i].snAddr, (int)cmd[i].cWriteVal);
				g_PushLogQueue(szLog, 0, m_nUnit);
			}
			else
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("I2C Write Error : SlaveAddr = %.2x, RegAddr = %.4x, Data = %.8x"), addr, cmd[i].snAddr, (int)cmd[i].cWriteVal);
				g_PushLogQueue(szLog, 0, m_nUnit);

				m_clPciExp.CM_I2CGetWriteResult(&i2cResult);

				switch (nRetVal)
				{
				case 1:
					_stprintf_s(szLog, SIZE_OF_1K, _T("retry 1, error code : 0x%x"), i2cResult.firstTry[0]);
					g_PushLogQueue(szLog, 0, m_nUnit);
					break;
				case 2:
					_stprintf_s(szLog, SIZE_OF_1K, _T("retry 1, error code : 0x%x"), i2cResult.firstTry[0]);
					g_PushLogQueue(szLog, 0, m_nUnit);
					_stprintf_s(szLog, SIZE_OF_1K, _T("retry 2, error code : 0x%x"), i2cResult.secondTry[0]);
					g_PushLogQueue(szLog, 0, m_nUnit);
					break;
				case 3:
					_stprintf_s(szLog, SIZE_OF_1K, _T("retry 1, error code : 0x%x"), i2cResult.firstTry[0]);
					g_PushLogQueue(szLog, 0, m_nUnit);
					_stprintf_s(szLog, SIZE_OF_1K, _T("retry 2, error code : 0x%x"), i2cResult.secondTry[0]);
					g_PushLogQueue(szLog, 0, m_nUnit);
					_stprintf_s(szLog, SIZE_OF_1K, _T("retry 3, error code : 0x%x"), i2cResult.thirdTry[0]);
					g_PushLogQueue(szLog, 0, m_nUnit);
					break;
				default:
					break;
				}
				
				if ((cmd[i].snAddr != 0x3054) || (cmd[i].snAddr != 0x3ee2))	// 예외처리 ini
					errorCount++;
			}
		}
	}

	if (errorCount > 10)
	{
		g_PushLogQueue(_T("Sensor Init. Fail!"), 1, m_nUnit);
		return false;
	}

	Sleep(100);
	g_PushLogQueue(_T("Sensor Init Ok using I2C comm."), 0, m_nUnit);

	return true;
}


//-----------------------------------------------------------------------------
//
//	GRAB 시작
//
//-----------------------------------------------------------------------------
bool CPriGrabberWrapper::StartGrab()
{
#ifndef ON_LINE_GRABBER
	return true;
#endif

	if (m_bOpen == false)
	{
		g_PushLogQueue(_T("Image Grabber Device Not Opend"), 1, m_nUnit);
		return false;
	}

	if (m_clPciExp.CM_GrabStart(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight, 1) != STATUS_PCIEXP_SUCCESS)
		return false;

	m_nCurrentState = CCD_GRAB_LIVE;

	return true;
}

//-----------------------------------------------------------------------------
//
//	GRAB 정지
//
//-----------------------------------------------------------------------------
bool CPriGrabberWrapper::StopGrab()
{
#ifndef ON_LINE_GRABBER
	g_clTaskWork[m_nUnit].m_fFps = 0.0;
	return true;
#endif

	m_clPciExp.CM_GrabStop();
	m_nCurrentState = CCD_GRAB_STOP;

	// 2. power enable off
	m_clPciExp.CM_EnablePower(POWER_CH1, FALSE);
	m_clPciExp.CM_EnablePower(POWER_CH2, FALSE);
	m_clPciExp.CM_EnablePower(POWER_CH3, FALSE);
	m_clPciExp.CM_EnablePower(POWER_CH4, FALSE);
	m_clPciExp.CM_EnablePower(POWER_LED, FALSE);

	Sleep(100);

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CPriGrabberWrapper::OpenCcdProcess()
{
#ifndef ON_LINE_GRABBER
	//m_clPciExp.SetSize(CCD_CAM_SIZE_X, g_clModelData.m_nHeight);
	m_nCurrentState = CCD_GRAB_LIVE;
	g_clTaskWork[m_nUnit].m_fFps = 10.0;
	return true;
#endif

	if (m_bOpen == false)
	{
		g_PushLogQueue(_T("Image Grabber Device Not Opend"), 1, m_nUnit);
		return false;
	}

	if (m_nCurrentState == CCD_GRAB_LIVE)
		return true;

	// 시작과 동시에 진행중으로 바꿈	
	m_nCurrentState = CCD_GRAB_PROCEEDING;

	if (this->ConnectDevice() == false)
	{
		g_PushLogQueue(_T("Grabber Connect 실패"), 1, m_nUnit);
		m_nCurrentState = CCD_GRAB_STOP;
		return false;
	}

#ifndef _M_X64
	if (g_clPriInsp[m_nUnit].func_Insp_CurrentMeasure(false, false))
	{
		g_PushLogQueue(_T("잔류 전류가 남아있습니다."), 1, m_nUnit);
		m_nCurrentState = CCD_GRAB_STOP;
		return false;
	}
#endif

	if (this->InitBoard() == false)
	{
		g_PushLogQueue(_T("Grabber Board Init 실패"), 1, m_nUnit);
		m_nCurrentState = CCD_GRAB_STOP;
		return false;
	}

	if (this->InitSensor() == false)
	{
		g_PushLogQueue(_T("Grabber Sensor Init 실패"), 1, m_nUnit);
		m_nCurrentState = CCD_GRAB_STOP;

		return false;
	}

	if (this->StartGrab() == false)
	{
		g_PushLogQueue(_T("Grabber Start Grab 실패"), 1, m_nUnit);
		m_nCurrentState = CCD_GRAB_STOP;

		return false;
	}
	
	// CCD Open 프로세스가 완료되면 LIVE로 바꿈...
	m_nCurrentState = CCD_GRAB_LIVE;

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
int CPriGrabberWrapper::ChkGrabDone(int* nCurrentIndex)
{
	if (m_bOpen == false)
		return -1;

	return m_clPciExp.CM_ChkGrabDone(nCurrentIndex);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
int CPriGrabberWrapper::CopyImgInfo(int nIndexNum)
{
	if (m_bOpen == false)
		return -1;

	return m_clPciExp.CM_CopyImgInfo(nIndexNum);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
int CPriGrabberWrapper::InfoIsValidFrame()
{
	if (m_bOpen == false)
		return - 1;

	return m_clPciExp.CM_InfoIsValidFrame();
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
int CPriGrabberWrapper::InfoGetFrameCnt(int* pFrameCount)
{
	if (m_bOpen == false)
		return -1;

	return m_clPciExp.CM_InfoGetFrameCnt(pFrameCount);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
int CPriGrabberWrapper::ImageCopySafe(int nIndexNum, int** nBuffer)
{
	if (m_bOpen == false)
		return -1;

	return m_clPciExp.CM_ImageCopySafe(nIndexNum, nBuffer);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CPriGrabberWrapper::Bit12ToRaw8(unsigned char *p12Bit, unsigned char *pRaw8)
{
	if (m_bOpen == false)
		return;

	m_clPciExp.CM_12BitToRaw8(p12Bit, pRaw8);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CPriGrabberWrapper::Raw10ToRaw8(unsigned char *pRaw10, unsigned char *pRaw8)
{
	if (m_bOpen == false)
		return;

	m_clPciExp.CM_Raw10ToRaw8(pRaw10, pRaw8);
}

//-----------------------------------------------------------------------------
//
//	전류 측정
//
//-----------------------------------------------------------------------------
bool CPriGrabberWrapper::GetCurrent(float* pdCurrent)
{
	float cur2, cur3, cur4;

	if (m_bOpen == false)
		return false;

	m_clPciExp.CM_GetDynamicCurrent(pdCurrent, &cur2, &cur3, &cur4);

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CPriGrabberWrapper::ChangePatternMode(int nMode)
{
	unsigned short addr;
	unsigned int data;
	
	if (m_bOpen == false)
		return false;

	// 원본 영상 모드
	if (nMode == 0)
	{
		addr = 0x3070;
		data = 0x00;
		m_clPciExp.CM_I2CBurstWrite(0, 2, 2, 0x10, addr,(int *)&data, 1);
	}
	// 테스트 패턴 모드
	else
	{
		addr = 0x3070;
		data = 0x03;
		m_clPciExp.CM_I2CBurstWrite(0, 2, 2, 0x10, addr, (int *)&data, 1);
	}
		
	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CPriGrabberWrapper::CopyInspImage(int nType)
{
	if (nType == 0)
	{
		cvCopyImage(m_pImageInspBuff, m_pImageInsp8Bit);
	}
	else
	{
		m_pImageInsp8Bit956 = this->RegionCopy(m_pImageInspBuff);
	}	
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
IplImage* CPriGrabberWrapper::RegionCopy(IplImage* src)
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

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
//void CPriGrabberWrapper::Raw12ToRaw8(unsigned char* pRaw12, unsigned char* pRaw8, int nSizeX, int nSizeY)
//{
//	register int i, j;
//	unsigned short int *pVal;
//	unsigned int nTmp;
//
//	pVal = (unsigned short int *) pRaw12;
//
//	for (i = 0; i < nSizeY; i++)
//	{
//		for (j = 0; j < nSizeX; j++)
//		{
//			nTmp = (pRaw12[i * nSizeX * 2 + i * 2 + 0] << 8) | pRaw12[i * nSizeX * 2 + i * 2 + 1];
//			pRaw8[i * nSizeX + j] = (nTmp >> 2);
//		}
//	}
//}

//void CPriGrabberWrapper::RawToBmp(unsigned char *pRaw8, unsigned char *pBMP, int image_width, int image_height, int bayer_format)
//{
//	unsigned char *pBmpBuffer;
//	unsigned char *pImageData;
//	unsigned char *pImageTemp;
//	unsigned char *pImageTemp1;
//	unsigned char *pImageTemp2;
//
//	unsigned char		r, g, b;
//	int			i, j;
//
//	//IplImage* pImage = cvCreateImage(cvSize(image_width, image_height), IPL_DEPTH_8U, 3);
//
//	pBmpBuffer = pBMP;
//	pImageData = pRaw8 + image_width*(image_height - 1);
//
//	switch (bayer_format)
//	{
//
//
//	case GRBG:				//GRGR
//							//BGBG
//							//GRGR
//							//BGBG
//		for (i = 0; i<image_height - 2; i += 2)
//		{
//			pImageTemp = pImageData;
//			pImageTemp1 = pImageData - image_width;
//			pImageTemp2 = pImageData - image_width * 2;
//			for (j = 0; j<image_width - 2; j += 2)
//			{
//				r = pImageTemp1[1];
//				b = (pImageTemp[0] + pImageTemp[2] + pImageTemp2[0] + pImageTemp2[2]) >> 2;
//				g = (pImageTemp[1] + pImageTemp1[0] + pImageTemp1[2] + pImageTemp2[1]) >> 2;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//				r = (pImageTemp1[0] + pImageTemp1[2]) >> 1;
//				b = (pImageTemp[1] + pImageTemp2[1]) >> 1;
//				g = pImageTemp1[1];
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//			}
//			for (j = 0; j<2; j++)
//			{	//2's dummy
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//			}
//			pImageData -= image_width;
//			pImageTemp = pImageData;
//			pImageTemp1 = pImageData - image_width;
//			pImageTemp2 = pImageData - image_width * 2;
//
//			for (j = 0; j<image_width - 2; j += 2) {
//				r = (pImageTemp[1] + pImageTemp2[1]) >> 1;
//				b = (pImageTemp1[0] + pImageTemp1[2]) >> 1;
//				g = pImageTemp1[1];
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//				b = pImageTemp1[1];
//				g = (pImageTemp[1] + pImageTemp1[0] + pImageTemp1[2] + pImageTemp2[1]) >> 2;
//				r = (pImageTemp[0] + pImageTemp[2] + pImageTemp2[0] + pImageTemp2[2]) >> 2;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//			}
//			for (j = 0; j<2; j++)
//			{   //2's dummy
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//			}
//			pImageData -= image_width;
//		} //end for Y axis
//		for (i = 0; i<image_width * 3; i++)	pBMP[image_width * 3 * (image_height - 2) + i] = pBMP[image_width * 3 * (image_height - 3) + i];
//		for (i = 0; i<image_width * 3; i++)	pBMP[image_width * 3 * (image_height - 1) + i] = pBMP[image_width * 3 * (image_height - 3) + i];
//
//		break;
//	case RGGB:					//RGRG
//								//GBGB
//								//RGRG
//								//GBGB
//		for (i = 0; i<image_height - 2; i += 2)
//		{
//			pImageTemp = pImageData;
//			pImageTemp1 = pImageData - image_width;
//			pImageTemp2 = pImageData - image_width * 2;
//			for (j = 0; j<image_width - 2; j += 2)
//			{
//				r = (pImageTemp1[0] + pImageTemp1[2]) >> 1;
//				b = (pImageTemp[1] + pImageTemp2[1]) >> 1;
//				g = pImageTemp1[1];
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//				r = pImageTemp1[1];
//				b = (pImageTemp[0] + pImageTemp[2] + pImageTemp2[0] + pImageTemp2[2]) >> 2;
//				g = (pImageTemp[1] + pImageTemp1[0] + pImageTemp1[2] + pImageTemp2[1]) >> 2;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//			}
//			for (j = 0; j<2; j++)
//			{	//2's dummy
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//			}
//			pImageData -= image_width;
//			pImageTemp = pImageData;
//			pImageTemp1 = pImageData - image_width;
//			pImageTemp2 = pImageData - image_width * 2;
//
//			for (j = 0; j<image_width - 2; j += 2) {
//				b = pImageTemp1[1];
//				g = (pImageTemp[1] + pImageTemp1[0] + pImageTemp1[2] + pImageTemp2[1]) >> 2;
//				r = (pImageTemp[0] + pImageTemp[2] + pImageTemp2[0] + pImageTemp2[2]) >> 2;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//				r = (pImageTemp[1] + pImageTemp2[1]) >> 1;
//				b = (pImageTemp1[0] + pImageTemp1[2]) >> 1;
//				g = pImageTemp1[1];
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//			}
//			for (j = 0; j<2; j++)
//			{   //2's dummy
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//			}
//			pImageData -= image_width;
//		} //end for Y axis
//		for (i = 0; i<image_width * 3; i++)	pBMP[image_width * 3 * (image_height - 2) + i] = pBMP[image_width * 3 * (image_height - 3) + i];
//		for (i = 0; i<image_width * 3; i++)	pBMP[image_width * 3 * (image_height - 1) + i] = pBMP[image_width * 3 * (image_height - 3) + i];
//		break;
//
//	case BGGR:					//BGBG
//								//GRGR
//								//BGBG
//								//GRGR
//		for (i = 0; i<image_height - 2; i += 2)
//		{
//			pImageTemp = pImageData;
//			pImageTemp1 = pImageData - image_width;
//			pImageTemp2 = pImageData - image_width * 2;
//			for (j = 0; j<image_width - 2; j += 2)
//			{
//				b = (pImageTemp1[0] + pImageTemp1[2]) >> 1;
//				g = pImageTemp1[1];
//				r = (pImageTemp[1] + pImageTemp2[1]) >> 1;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//				b = pImageTemp1[1];
//				g = (pImageTemp[1] + pImageTemp1[0] + pImageTemp1[2] + pImageTemp2[1]) >> 2;
//				r = (pImageTemp[0] + pImageTemp[2] + pImageTemp2[0] + pImageTemp2[2]) >> 2;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//			}
//			for (j = 0; j<2; j++)
//			{	//2's dummy
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//			}
//			pImageData -= image_width;
//			pImageTemp = pImageData;
//			pImageTemp1 = pImageData - image_width;
//			pImageTemp2 = pImageData - image_width * 2;
//
//			for (j = 0; j<image_width - 2; j += 2)
//			{
//				r = pImageTemp1[1];
//				b = (pImageTemp[0] + pImageTemp[2] + pImageTemp2[0] + pImageTemp2[2]) >> 2;
//				g = (pImageTemp[1] + pImageTemp1[0] + pImageTemp1[2] + pImageTemp2[1]) >> 2;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//				r = (pImageTemp1[0] + pImageTemp1[2]) >> 1;
//				b = (pImageTemp[1] + pImageTemp2[1]) >> 1;
//				g = pImageTemp1[1];
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//			}
//			for (j = 0; j<2; j++)
//			{   //2's dummy
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//			}
//			pImageData -= image_width;
//		} //end for Y
//		for (i = 0; i<image_width * 3; i++)	pBMP[image_width * 3 * (image_height - 2) + i] = pBMP[image_width * 3 * (image_height - 3) + i];
//		for (i = 0; i<image_width * 3; i++)	pBMP[image_width * 3 * (image_height - 1) + i] = pBMP[image_width * 3 * (image_height - 3) + i];
//
//		break;
//	case GBRG:					//GBGB
//								//RGRG
//								//GBGB
//								//RGRG
//		for (i = 0; i<image_height - 2; i += 2)
//		{
//			pImageTemp = pImageData;
//			pImageTemp1 = pImageData - image_width;
//			pImageTemp2 = pImageData - image_width * 2;
//			for (j = 0; j<image_width - 2; j += 2)
//			{
//				b = pImageTemp1[1];
//				g = (pImageTemp[1] + pImageTemp1[0] + pImageTemp1[2] + pImageTemp2[1]) >> 2;
//				r = (pImageTemp[0] + pImageTemp[2] + pImageTemp2[0] + pImageTemp2[2]) >> 2;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//				b = (pImageTemp1[0] + pImageTemp1[2]) >> 1;
//				g = pImageTemp1[1];
//				r = (pImageTemp[1] + pImageTemp2[1]) >> 1;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//			}
//			for (j = 0; j<2; j++)
//			{	//2's dummy
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//			}
//			pImageData -= image_width;
//			pImageTemp = pImageData;
//			pImageTemp1 = pImageData - image_width;
//			pImageTemp2 = pImageData - image_width * 2;
//
//			for (j = 0; j<image_width - 2; j += 2)
//			{
//				r = (pImageTemp1[0] + pImageTemp1[2]) >> 1;
//				b = (pImageTemp[1] + pImageTemp2[1]) >> 1;
//				g = pImageTemp1[1];
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//				r = pImageTemp1[1];
//				b = (pImageTemp[0] + pImageTemp[2] + pImageTemp2[0] + pImageTemp2[2]) >> 2;
//				g = (pImageTemp[1] + pImageTemp1[0] + pImageTemp1[2] + pImageTemp2[1]) >> 2;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//			}
//			for (j = 0; j<2; j++) {   //2's dummy
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//			}
//			pImageData -= image_width;
//		} //end for (m_ImageSize.xy)
//		for (i = 0; i<image_width * 3; i++)	pBMP[image_width * 3 * (image_height - 2) + i] = pBMP[image_width * 3 * (image_height - 3) + i];
//		for (i = 0; i<image_width * 3; i++)	pBMP[image_width * 3 * (image_height - 1) + i] = pBMP[image_width * 3 * (image_height - 3) + i];
//
//		/*memcpy(pImage->imageData, pBMP, image_width * image_height * 3);
//		csSaveImage("C:\\img.bmp", pImage);
//		cvReleaseImage(&pImage);*/
//		break;
//	}
//
//
//}


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
//void CPriGrabberWrapper::Raw12BitToRaw8(unsigned char *p12Bit, unsigned char *pRaw8, int nWidth, int nHeight)
//{
//	register int x, y;
//
//	for (y = 0; y < nHeight; y++)
//	{
//		for (x = 0; x < nWidth / 2; x++)
//		{
//			pRaw8[y * nWidth + x * 2] = (p12Bit[(y + 2) * nWidth * 2 + 4 * x + 0]);
//			pRaw8[y * nWidth + x * 2 + 1] = (p12Bit[(y + 2) * nWidth * 2 + 4 * x + 2]);
//		}
//	}
//}


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
//void CPriGrabberWrapper::RawToBmp(unsigned char *pRaw8, unsigned char *pBMP, int nWidth, int nHeight, int nBayerFormat)
//{
//	unsigned char *pBmpBuffer;
//	unsigned char *pImageData;
//	unsigned char *pImageTemp;
//	unsigned char *pImageTemp1;
//	unsigned char *pImageTemp2;
//	unsigned char *pTargetBuffer, *pSourceBuffer;
//	unsigned char r, g, b, temp;
//	register int i, j;
//
//
//	pTargetBuffer = pBMP;
//	pSourceBuffer = pRaw8;
//
//	pBmpBuffer = pBMP;
//	pImageData = pRaw8 + nWidth * (nHeight - 1);
//
//	switch (nBayerFormat)
//	{
//	case GRBG:				//GRGR
//							//BGBG
//							//GRGR
//							//BGBG
//		for (i = 0; i < nHeight - 2; i += 2)
//		{
//			pImageTemp = pImageData;
//			pImageTemp1 = pImageData - nWidth;
//			pImageTemp2 = pImageData - nWidth * 2;
//			for (j = 0; j < nWidth - 2; j += 2)
//			{
//				r = pImageTemp1[1];
//				b = (pImageTemp[0] + pImageTemp[2] + pImageTemp2[0] + pImageTemp2[2]) >> 2;
//				g = (pImageTemp[1] + pImageTemp1[0] + pImageTemp1[2] + pImageTemp2[1]) >> 2;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//				r = (pImageTemp1[0] + pImageTemp1[2]) >> 1;
//				b = (pImageTemp[1] + pImageTemp2[1]) >> 1;
//				g = pImageTemp1[1];
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//			}
//			for (j = 0; j < 2; j++)
//			{	//2's dummy
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//			}
//			pImageData -= nWidth;
//			pImageTemp = pImageData;
//			pImageTemp1 = pImageData - nWidth;
//			pImageTemp2 = pImageData - nWidth * 2;
//
//			for (j = 0; j < nWidth - 2; j += 2)
//			{
//				r = (pImageTemp[1] + pImageTemp2[1]) >> 1;
//				b = (pImageTemp1[0] + pImageTemp1[2]) >> 1;
//				g = pImageTemp1[1];
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//				b = pImageTemp1[1];
//				g = (pImageTemp[1] + pImageTemp1[0] + pImageTemp1[2] + pImageTemp2[1]) >> 2;
//				r = (pImageTemp[0] + pImageTemp[2] + pImageTemp2[0] + pImageTemp2[2]) >> 2;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//			}
//			for (j = 0; j < 2; j++)
//			{   //2's dummy
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//			}
//			pImageData -= nWidth;
//		} //end for Y axis
//		for (i = 0; i<nWidth * 3; i++)	pBMP[nWidth * 3 * (nHeight - 2) + i] = pBMP[nWidth * 3 * (nHeight - 3) + i];
//		for (i = 0; i<nWidth * 3; i++)	pBMP[nWidth * 3 * (nHeight - 1) + i] = pBMP[nWidth * 3 * (nHeight - 3) + i];
//
//		break;
//	case RGGB:					//RGRG
//								//GBGB
//								//RGRG
//								//GBGB
//		for (i = 0; i < nHeight - 2; i += 2)
//		{
//			pImageTemp = pImageData;
//			pImageTemp1 = pImageData - nWidth;
//			pImageTemp2 = pImageData - nWidth * 2;
//			for (j = 0; j < nWidth - 2; j += 2)
//			{
//				r = (pImageTemp1[0] + pImageTemp1[2]) >> 1;
//				b = (pImageTemp[1] + pImageTemp2[1]) >> 1;
//				g = pImageTemp1[1];
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//				r = pImageTemp1[1];
//				b = (pImageTemp[0] + pImageTemp[2] + pImageTemp2[0] + pImageTemp2[2]) >> 2;
//				g = (pImageTemp[1] + pImageTemp1[0] + pImageTemp1[2] + pImageTemp2[1]) >> 2;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//			}
//			for (j = 0; j<2; j++)
//			{	//2's dummy
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//			}
//			pImageData -= nWidth;
//			pImageTemp = pImageData;
//			pImageTemp1 = pImageData - nWidth;
//			pImageTemp2 = pImageData - nWidth * 2;
//
//			for (j = 0; j < nWidth - 2; j += 2)
//			{
//				b = pImageTemp1[1];
//				g = (pImageTemp[1] + pImageTemp1[0] + pImageTemp1[2] + pImageTemp2[1]) >> 2;
//				r = (pImageTemp[0] + pImageTemp[2] + pImageTemp2[0] + pImageTemp2[2]) >> 2;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//				r = (pImageTemp[1] + pImageTemp2[1]) >> 1;
//				b = (pImageTemp1[0] + pImageTemp1[2]) >> 1;
//				g = pImageTemp1[1];
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//			}
//			for (j = 0; j < 2; j++)
//			{   //2's dummy
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//			}
//			pImageData -= nWidth;
//		} //end for Y axis
//		for (i = 0; i < nWidth * 3; i++)	pBMP[nWidth * 3 * (nHeight - 2) + i] = pBMP[nWidth * 3 * (nHeight - 3) + i];
//		for (i = 0; i < nWidth * 3; i++)	pBMP[nWidth * 3 * (nHeight - 1) + i] = pBMP[nWidth * 3 * (nHeight - 3) + i];
//		break;
//
//	case BGGR:					//BGBG
//								//GRGR
//								//BGBG
//								//GRGR
//		for (i = 0; i < nHeight - 2; i += 2)
//		{
//			pImageTemp = pImageData;
//			pImageTemp1 = pImageData - nWidth;
//			pImageTemp2 = pImageData - nWidth * 2;
//			for (j = 0; j < nWidth - 2; j += 2)
//			{
//				b = (pImageTemp1[0] + pImageTemp1[2]) >> 1;
//				g = pImageTemp1[1];
//				r = (pImageTemp[1] + pImageTemp2[1]) >> 1;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//				b = pImageTemp1[1];
//				g = (pImageTemp[1] + pImageTemp1[0] + pImageTemp1[2] + pImageTemp2[1]) >> 2;
//				r = (pImageTemp[0] + pImageTemp[2] + pImageTemp2[0] + pImageTemp2[2]) >> 2;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//			}
//			for (j = 0; j < 2; j++)
//			{	//2's dummy
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//			}
//			pImageData -= nWidth;
//			pImageTemp = pImageData;
//			pImageTemp1 = pImageData - nWidth;
//			pImageTemp2 = pImageData - nWidth * 2;
//
//			for (j = 0; j < nWidth - 2; j += 2)
//			{
//				r = pImageTemp1[1];
//				b = (pImageTemp[0] + pImageTemp[2] + pImageTemp2[0] + pImageTemp2[2]) >> 2;
//				g = (pImageTemp[1] + pImageTemp1[0] + pImageTemp1[2] + pImageTemp2[1]) >> 2;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//				r = (pImageTemp1[0] + pImageTemp1[2]) >> 1;
//				b = (pImageTemp[1] + pImageTemp2[1]) >> 1;
//				g = pImageTemp1[1];
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//			}
//			for (j = 0; j < 2; j++)
//			{   //2's dummy
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//			}
//			pImageData -= nWidth;
//		} //end for Y
//		for (i = 0; i < nWidth * 3; i++)	pBMP[nWidth * 3 * (nHeight - 2) + i] = pBMP[nWidth * 3 * (nHeight - 3) + i];
//		for (i = 0; i < nWidth * 3; i++)	pBMP[nWidth * 3 * (nHeight - 1) + i] = pBMP[nWidth * 3 * (nHeight - 3) + i];
//
//		break;
//	case GBRG:					//GBGB
//								//RGRG
//								//GBGB
//								//RGRG
//		for (i = 0; i < nHeight - 2; i += 2)
//		{
//			pImageTemp = pImageData;
//			pImageTemp1 = pImageData - nWidth;
//			pImageTemp2 = pImageData - nWidth * 2;
//			for (j = 0; j < nWidth - 2; j += 2)
//			{
//				b = pImageTemp1[1];
//				g = (pImageTemp[1] + pImageTemp1[0] + pImageTemp1[2] + pImageTemp2[1]) >> 2;
//				r = (pImageTemp[0] + pImageTemp[2] + pImageTemp2[0] + pImageTemp2[2]) >> 2;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//				b = (pImageTemp1[0] + pImageTemp1[2]) >> 1;
//				g = pImageTemp1[1];
//				r = (pImageTemp[1] + pImageTemp2[1]) >> 1;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//			}
//			for (j = 0; j < 2; j++)
//			{	//2's dummy
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//			}
//			pImageData -= nWidth;
//			pImageTemp = pImageData;
//			pImageTemp1 = pImageData - nWidth;
//			pImageTemp2 = pImageData - nWidth * 2;
//
//			for (j = 0; j < nWidth - 2; j += 2)
//			{
//				r = (pImageTemp1[0] + pImageTemp1[2]) >> 1;
//				b = (pImageTemp[1] + pImageTemp2[1]) >> 1;
//				g = pImageTemp1[1];
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//
//				r = pImageTemp1[1];
//				b = (pImageTemp[0] + pImageTemp[2] + pImageTemp2[0] + pImageTemp2[2]) >> 2;
//				g = (pImageTemp[1] + pImageTemp1[0] + pImageTemp1[2] + pImageTemp2[1]) >> 2;
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//				pImageTemp += 1;
//				pImageTemp1 += 1;
//				pImageTemp2 += 1;
//			}
//			for (j = 0; j < 2; j++)
//			{   //2's dummy
//				*pBmpBuffer++ = b;
//				*pBmpBuffer++ = g;
//				*pBmpBuffer++ = r;
//			}
//			pImageData -= nWidth;
//		} //end for (m_ImageSize.xy)
//
//		for (i = 0; i < nWidth * 3; i++)	pBMP[nWidth * 3 * (nHeight - 2) + i] = pBMP[nWidth * 3 * (nHeight - 3) + i];
//		for (i = 0; i < nWidth * 3; i++)	pBMP[nWidth * 3 * (nHeight - 1) + i] = pBMP[nWidth * 3 * (nHeight - 3) + i];
//
//		break;
//	case RCCC:
//		for (i = 0; i < nHeight; i++)
//		{
//			for (j = 0; j < nWidth; j++)
//			{
//				if (i == 0 && j == 0)  // top_left
//				{
//
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = (BYTE)((*(pSourceBuffer + 1) + *(pSourceBuffer + nWidth)) / 2);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//				else if (i == 0 && ((j + 1) & 0x1))  // top
//				{
//
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = (BYTE)((*(pSourceBuffer + j + 1) + *(pSourceBuffer + j - 1) + *(pSourceBuffer + nWidth + j)) / 3);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//				else if (((i + 1) & 0x01) && j == 0) // left
//				{
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = (BYTE)((*(pSourceBuffer + i * nWidth + 1) + *(pSourceBuffer + (i - 1) * nWidth) + *(pSourceBuffer + (i + 1) * nWidth)) / 3);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//				else if (((i + 1) & 0x01) && ((j + 1) & 0x1))
//				{
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = (BYTE)((*(pSourceBuffer + i * nWidth + j + 1) + *(pSourceBuffer + (i - 1) * nWidth + j) + *(pSourceBuffer + (i + 1) * nWidth + j) + *(pSourceBuffer + i * nWidth + j - 1)) >> 2);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//				else
//				{
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = *(pSourceBuffer + i * nWidth + j);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//			}
//		}
//		break;
//	case CRCC:
//		for (i = 0; i < nHeight; i++)
//		{
//			for (j = 0; j < nWidth; j++)
//			{
//				if (i == 0 && j == (nWidth - 1))  // top_right
//				{
//
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = (BYTE)((*(pSourceBuffer + j - 1) + *(pSourceBuffer + nWidth + j)) / 2);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//				else if (i == 0 && (j & 0x1))  // top
//				{
//
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = (BYTE)((*(pSourceBuffer + j + 1) + *(pSourceBuffer + j - 1) + *(pSourceBuffer + nWidth + j)) / 3);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//				else if (((i + 1) & 0x01) && j == (nWidth - 1)) // right
//				{
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = (BYTE)((*(pSourceBuffer + i * nWidth + j - 1) + *(pSourceBuffer + (i - 1) * nWidth + j) + *(pSourceBuffer + (i + 1) * nWidth + j)) / 3);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//				else if (((i + 1) & 0x01) && (j & 0x1))
//				{
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = (BYTE)((*(pSourceBuffer + i * nWidth + j + 1) + *(pSourceBuffer + (i - 1) * nWidth + j) + *(pSourceBuffer + (i + 1) * nWidth + j) + *(pSourceBuffer + i * nWidth + j - 1)) >> 2);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//				else
//				{
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = *(pSourceBuffer + i * nWidth + j);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//			}
//		}
//		break;
//
//	case CCRC:
//		for (i = 0; i < nHeight; i++)
//		{
//			for (j = 0; j < nWidth; j++)
//			{
//				if (i == (nHeight - 1) && j == 0)  // bottom_left
//				{
//
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = (BYTE)((*(pSourceBuffer + (i - 1) * nWidth + j) + *(pSourceBuffer + i * nWidth + j + 1)) / 2);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//				else if (i == (nHeight - 1) && ((j + 1) & 0x1))  // bottom
//				{
//
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = (BYTE)((*(pSourceBuffer + (i - 1) * nWidth + j) + *(pSourceBuffer + i * nWidth + j + 1) + *(pSourceBuffer + i * nWidth + j - 1)) / 3);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//				else if ((i & 0x01) && j == 0) // left
//				{
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = (BYTE)((*(pSourceBuffer + i * nWidth + 1) + *(pSourceBuffer + (i - 1) * nWidth) + *(pSourceBuffer + (i + 1) * nWidth)) / 3);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//				else if ((i & 0x01) && ((j + 1) & 0x1))
//				{
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = (BYTE)((*(pSourceBuffer + i * nWidth + j + 1) + *(pSourceBuffer + (i - 1) * nWidth + j) + *(pSourceBuffer + (i + 1) * nWidth + j) + *(pSourceBuffer + i * nWidth + j - 1)) / 4);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//				else
//				{
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = *(pSourceBuffer + i * nWidth + j);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//			}
//		}
//		break;
//
//	case CCCR:
//		for (i = 0; i < nHeight; i++)
//		{
//			for (j = 0; j < nWidth; j++)
//			{
//				if (i == (nHeight - 1) && j == (nWidth - 1))  // bottom_right
//				{
//
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = (BYTE)((*(pSourceBuffer + (i - 1) * nWidth + j) + *(pSourceBuffer + i * nWidth + j - 1)) / 2);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//				else if (i == (nHeight - 1) && (j & 0x1))  // bottom
//				{
//
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = (BYTE)((*(pSourceBuffer + (i - 1) * nWidth + j) + *(pSourceBuffer + i * nWidth + j + 1) + *(pSourceBuffer + i * nWidth + j - 1)) / 3);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//				else if ((i & 0x01) && j == (nWidth - 1)) // right
//				{
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = (BYTE)((*(pSourceBuffer + i * nWidth + j - 1) + *(pSourceBuffer + (i - 1) * nWidth + j) + *(pSourceBuffer + (i + 1) * nWidth + j)) / 3);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//				else if ((i & 0x01) && (j & 0x1))
//				{
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = (BYTE)((*(pSourceBuffer + i * nWidth + j + 1) + *(pSourceBuffer + (i - 1) * nWidth + j) + *(pSourceBuffer + (i + 1) * nWidth + j) + *(pSourceBuffer + i * nWidth + j - 1)) / 4);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//				else
//				{
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3) = temp = *(pSourceBuffer + i * nWidth + j);
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 1) = temp;
//					*(pTargetBuffer + (nHeight - 1 - i) * nWidth * 3 + j * 3 + 2) = temp;
//					//*(m_pInterpolationBuffer + i * width + j)	=	temp;
//				}
//			}
//		}
//		break;
//	default:
//		break;
//
//	}
//}
