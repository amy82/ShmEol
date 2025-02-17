#include "StdAfx.h"
#include "LightControl.h"

#define BCR_STX				0x02
#define BCR_ETX				0x03

#define BCR_ACK				0x06
#define BCR_NAK				0x15


CLightControl::CLightControl(void)
{
	m_iRecvSize = 0;
	memset(m_acRecvStorage, 0, sizeof(m_acRecvStorage));
		
	m_iNo_Machine = -1;
}


CLightControl::~CLightControl(void)
{
	Close_Device();
}

//! RS-232C 통신이 연결된 후에 맨 처음 1번 만 실행해야 할 기능을 구현하다. 
void CLightControl::ReadyDevice()
{
}

//! 수신 처리 본체 함수
void CLightControl::ProcessReceiveData(void *pProcPtr, BYTE *pbyBuff, int iSize, bool bFlag_Active, int iCnt_Recv)
{
	if ( m_iNo_Machine < 0 )
	{
		return;
	}
	if ( pProcPtr == NULL || pbyBuff == NULL || iSize <= 0 )
	{
		return;
	}
	
	TCHAR acRecvTmp[8192];
	memset(acRecvTmp, 0, sizeof(acRecvTmp));
	_tcscpy_s(acRecvTmp, m_acRecvStorage);	//! 저번 함수 호출 때에 남은 데이터를 가져온다. 

	int iRecvCnt = m_iRecvSize;
	if ( iRecvCnt < 0 )
	{
		iRecvCnt = 0;
	}

	int i = 0;
	byte mEndChar = 0x00;
	for (i = 0; i < iSize - 1; i++)
	{
		mEndChar += pbyBuff[i];
	}
	byte bLogView = 0x00;
	byte bLightCh = 0x00;
	for ( i = 0; i < iSize; i++ )
	{
		if ((pbyBuff[i] == 0x59))		//! 시작//if ( (pbyBuff[i] == ']')  && (iRecvCnt == 0) )		//! 시작
		{
			iRecvCnt = 0;
			memset(acRecvTmp, 0, sizeof(acRecvTmp));
			acRecvTmp[iRecvCnt] = (TCHAR)(pbyBuff[i]);	//! pbyBuff -> acRecvTmp 버퍼로 데이터를 옮긴다. 
		}
		else if ((pbyBuff[i] == mEndChar))	//! 마침//else if ( (pbyBuff[i] == ']') && (iRecvCnt > 0) )	//! 마침
		{
			///acRecvTmp[iRecvCnt] = 0x00;
			if (pbyBuff[3] == 0x50 || pbyBuff[3] == 0x51)
			{
				TCHAR szLogCh[SIZE_OF_100BYTE];
				bLightCh = pbyBuff[2];		//ch 0x01 ~ 0x04
				bLogView = pbyBuff[3];

				_stprintf_s(szLogCh, SIZE_OF_100BYTE, _T("Ch:%d ,Command:%d "), bLightCh, bLogView);		//OC___LIGHT___OLD
				AddLog(szLogCh, 0, 0);
			}
			if ( bFlag_Active == true )
			{
				//! 준비된 수신 문자열을 실제로 사용한다. 
				OutputRecvData(pProcPtr, acRecvTmp, iRecvCnt, iCnt_Recv);
			}

			///memset(acRecvTmp, 0, sizeof(acRecvTmp));
			//iRecvCnt = 0;			
		}
		acRecvTmp[iRecvCnt] = (TCHAR)(pbyBuff[i]);	//! pbyBuff -> acRecvTmp 버퍼로 데이터를 옮긴다. 
		iRecvCnt++;
	}

	acRecvTmp[iRecvCnt] = 0x00;
	m_iRecvSize = iRecvCnt;
	 
	memset(m_acRecvStorage, 0, sizeof(m_acRecvStorage)); 
	_tcscpy_s(m_acRecvStorage, acRecvTmp);	//! 처리하고 남은 데이터를 다음 함수 호출때를 위해 저장해 둔다. 
	TCHAR szLog[SIZE_OF_1K];
	unsigned short mtime = 0x0000;
	if (bLogView == 0x50 && bLightCh < 5)
	{
		int mch = bLightCh - 1;		// 1 ~ 4로 들어온다.
		if (mch < 0) mch = 0;
		if (mch > 3) mch = 3;
		//
		g_clTaskWork[0].m_LightTimeCheck = 1;
		mtime = (pbyBuff[4] << 8) + pbyBuff[5];
		g_clMesCommunication[0].m_dMesOcLightTime[mch] = mtime;
		_stprintf_s(szLog, SIZE_OF_1K, _T("%d Channel 점등 시간 : %d (h)") , mch + 1, g_clMesCommunication[0].m_dMesOcLightTime[mch]);
		AddLog(szLog, 0, 0);
		if (pbyBuff[4] == 0xFF && pbyBuff[5] == 0xFF)
		{
			//보증 시간 초과
			g_clTaskWork[0].m_LightTimeCheck = -1;
		}
		//g_pCarAABonderDlg->m_clLightDlg.setOcTime(mtime);
	}
	else if (bLogView == 0x51)
	{
		mtime = (pbyBuff[4]<<8) + pbyBuff[5];
		_stprintf_s(szLog, SIZE_OF_1K, _T("보증 시간 : %d (h)") , mtime);
		AddLog(szLog, 0, 0);
	}
}

//! [기능] 수신 받은 문자열을 Parsing하거나, 다른 곳에 전달한다.  
void CLightControl::OutputRecvData(void *pProcPtr, TCHAR *pcBuff, int iDataSize, int iCnt_Recv)
{
	//! TCHAR* -> CString 
	CString sRecv = _T("");
	sRecv.Format(_T("%s"), pcBuff);

	int iStringLength = (int)(sRecv.GetLength());
	
	if ( pProcPtr != NULL )
	{
	}
}

//! 수신 처리 후 후처리 함수
void CLightControl::PostProcRecvData()
{
}

//! 조명 컨트롤러에 연결
//! [주의 사항] 수신 데이터가 있을 경우에는, 반드시, SetReceiveProcPtr 함수로 수신 처리를 할 Dialog나 GUI 클래스를 설정하고, 이 함수를 호출한다. 
bool CLightControl::Connect_BackDu_Device(CString sPort, int iNoMachine)
{
	iNoMachine += 1;
	if (iNoMachine < 0)
	{
		return false;
	}
	/*if ( sPort.GetLength() < 8 )
	{
	return false;
	}*/
	if (sPort.Find(_T("COM"), 0) < 0)
	{
		return false;
	}

	strSetupInfo_RS232C strSerial;
	strSerial.InitInfo();
	strSerial.dwBaudRate = CBR_19200;
	strSerial.byDataBit = 8;
	strSerial.byStopBit = ONESTOPBIT;
	strSerial.byParityBit = NOPARITY;
	strSerial.sPortName = sPort;
	strSerial.eFlowControl = EHandshakeOff;
	strSerial.bFlag_Close_COM_Port = true;
	strSerial.bFlag_Use_CPU_Affinity = false;
	strSerial.bFlag_Recv_ThreadStart = false;	//! 수신 데이터 처리용 Thread를 생성하지 않음
	strSerial.iTimeOut_Close_Thread = 3000;
	int iReturn = OpenPort(&strSerial);

	if (iReturn < 0)
	{
		return false;
	}

	m_iNo_Machine = iNoMachine;
	SetChannel_OnOff(iNoMachine, true);
	return true;
}



//! 조명 컨트롤러에 연결
//! [주의 사항] 수신 데이터가 있을 경우에는, 반드시, SetReceiveProcPtr 함수로 수신 처리를 할 Dialog나 GUI 클래스를 설정하고, 이 함수를 호출한다. 
bool CLightControl::Connect_Device(CString sPort, int iNoMachine, int Baud)
{
	iNoMachine += 1;
	if (iNoMachine < 0)
	{
		return false;
	}
	/*if ( sPort.GetLength() < 8 )
	{
	return false;
	}*/
	if (sPort.Find(_T("COM"), 0) < 0)
	{
		return false;
	}

	strSetupInfo_RS232C strSerial;
	strSerial.InitInfo();
	strSerial.dwBaudRate = Baud;// CBR_9600;
	strSerial.byDataBit = 8;
	strSerial.byStopBit = ONESTOPBIT;
	strSerial.byParityBit = NOPARITY;
	strSerial.sPortName = sPort;
	strSerial.eFlowControl = EHandshakeOff;
	strSerial.bFlag_Close_COM_Port = true;
	strSerial.bFlag_Use_CPU_Affinity = false;
	strSerial.bFlag_Recv_ThreadStart = true;//false;	//! 수신 데이터 처리용 Thread를 생성하지 않음
	strSerial.iTimeOut_Close_Thread = 3000;
	int iReturn = OpenPort(&strSerial);

	if (iReturn < 0)
	{
		return false;
	}

	m_iNo_Machine = iNoMachine;
	return true;
}


bool CLightControl::DPS_Check_Time()//검사초기 매회 사용시간 확인해야된다 (20,000 시간 알람기능)
{

	return false;
}

bool CLightControl::DPS_Get_State(int mode, int channel)		//상태 확인 함수 
{
	int rtnValue = -1;
	unsigned char sSendBuff[100];
	int nSendSize = 0;

	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	sSendBuff[0] = 0x59;								//Header
	sSendBuff[1] = 0x07;								//Length
	sSendBuff[2] = (char)(channel & 0x00FF);
	//[3]
	sSendBuff[4] = 0x00;		//Data-0 [MSB]
	sSendBuff[5] = 0x00;		//Data-1 [LSB]
	sSendBuff[6] = 0x00;		//BCC

	
	switch (mode)
	{
	case 1:	//1(0x3F) = Ready 상태 체크 
		sSendBuff[3] = 0x3F;
		break;
	case 2:	//2(0x42) = Level
		sSendBuff[3] = 0x42;
		break;
	case 3:	//3(0x43) = On/Off 
		sSendBuff[3] = 0x43;
		break;
	case 4:	//4(0x50) = 시간 정보 읽기 (점등 시간)
#ifdef OC___LIGHT___OLD
		sSendBuff[2] = 0x01;	//channel		여기가 채널별로 바뀐다 240202
#endif
		sSendBuff[3] = 0x50;
		break;
	case 5:	//5(0x51) = 시간 정보 읽기 (보증 시간)
		//보증시간 초과시 응답값 0xFF , 0xFF
		sSendBuff[2] = 0x01;	//0x01 보증시간은 고정
		sSendBuff[3] = 0x51;
		break;

	default:
		rtnValue = -1;
		break;
	}
	for (int i = 0; i < 6; i++)
	{
		sSendBuff[6] += sSendBuff[i];
	}
	nSendSize = 7;
	int nRetVal = SendData_Light_Controller(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
	{
		return false;
	}
	return true;
}



//! 각 Channel의 밝기값(PWM값) 조절
//! [주의 사항] 'iNoChannel' 값은 조명 컨트롤러의 실제 채널 입력값이다. 
int CLightControl::DPS_SetChannel_Value(int iNoChannel, int iValue)
{
	if (iValue < 0)
	{
		iValue = 0;
	}
	if (iValue > 255)
	{
		iValue = 255;
	}
	int nSendSize;
	int nRetVal;
	int nIndex;
#if 1
	BYTE sSendBuff[100];
	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	sSendBuff[0] = 0x59;		//ASCII 'Y'  Hex Code 0x59 로 고정
	sSendBuff[1] = 0x07;		//Header ~ Checksum까지의 byte수 , 7로 고정
	sSendBuff[2] = iNoChannel;			//채널 0x01 ~ 0x08 , 1채널모델의 경우 0x01로 고정
	sSendBuff[3] = 0x31;			//On = 0x31 , Off = 0x30 , Ready Check = 0x3F
	sSendBuff[4] = (char)((iValue >> 8) & 0x00FF);		//Value-0 , MSB, OFF인경우 값의미없음, 1024 Level의 경우 0ㅌ0000 ~ 0x03ff까지 사용가능
	sSendBuff[5] = (char)(iValue & 0x00FF);;		//Value-1 , LSB, OFF인경우 값의미없음

	for (int i = 0; i < 6; i++)
	{
		sSendBuff[6] += sSendBuff[i];		//Checksum = Header ~ Value-1까지의 합
	}

	nSendSize = 7;



#else
	CString sSend = _T("");
	sSend.Empty();
	sSend.Format(_T("[%02d%03d"), iNoChannel, iValue);
#endif
	int iRet = SendData_Light_Controller(sSendBuff, nSendSize);
	if (iRet < 0)
	{
		return (-10 + iRet);
	}

	return 1;
}
bool CLightControl::DPS_Light_OnOffLevel(int channel, int onoff, int data)
{
	//Level은 0 ~ 1023
	unsigned char sSendBuff[100];
	int nSendSize = 0;
	char mch = 0x1 + channel;
	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	sSendBuff[0] = 0x59;								//Header
	sSendBuff[1] = 0x07;								//Length
	sSendBuff[2] = (char)(mch & 0x00FF);	//Channel (0x1 ~ 0x4)
	sSendBuff[3] = (onoff == 0) ?  0x30 : 0x31;			//Command
	sSendBuff[4] = (char)((data>>8)&0x00FF);	//Data-0 [MSB]
	sSendBuff[5] = (char)(data & 0x00FF);		//Data-1 [LSB]
	sSendBuff[6] = 0x00;								//BCC
	
	for (int i = 0; i < 6; i++)
	{
		sSendBuff[6] += sSendBuff[i];
	}
	nSendSize = 7;

	Sleep(100);
	int nRetVal = SendData_Light_Controller(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
	{
		return false;
	}
	return true;
}
//! 연결 해제
void CLightControl::Close_Device()
{
	ClosePort();

	m_iNo_Machine = -1;
}

//! 문자열 직접 전송
int CLightControl::SendData_Light_Controller(BYTE *pbySend, int iSendSize)
{

#if 1
	if (pbySend == NULL || iSendSize <= 0)
	{
		return -1;
	}
	if (m_iNo_Machine < 0)
	{
		return -2;
	}

	BYTE bySendBuf[256];
	memset(bySendBuf, 0x00, sizeof(bySendBuf));

	int i = 0;
	DWORD dwSendCnt = 0;

	//bySendBuf[dwSendCnt++] = 0x0D;
	for (i = 0; i < iSendSize; i++)
	{
		bySendBuf[dwSendCnt++] = pbySend[i];
	}
	//bySendBuf[dwSendCnt++] = 0x0D;

	DWORD dwRet = WriteComm(bySendBuf, dwSendCnt);
	if (dwRet < dwSendCnt)
	{
		return -3;
	}

	return dwRet;
#else
	if ( pbySend == NULL || iSendSize <= 0 )
	{
		return -1;
	}
	if ( m_iNo_Machine < 0 )
	{
		return -2;
	}
	
	BYTE bySendBuf[256];
	memset(bySendBuf, 0x00, sizeof(bySendBuf));

	int i = 0;
	DWORD dwSendCnt = 0;
	
	//bySendBuf[dwSendCnt++] = 0x0D;
	for ( i = 0; i < iSendSize; i++ )
	{
		bySendBuf[dwSendCnt++] = pbySend[i];
	}
	//bySendBuf[dwSendCnt++] = 0x0D;

	DWORD dwRet = WriteComm(bySendBuf, dwSendCnt);
	if ( dwRet < dwSendCnt )
	{
		return -3;
	}

	return 1;
#endif
}

//! 문자열 직접 전송
int CLightControl::SendData_Light_Controller(CString sSend)
{
	int iStringSize = sSend.GetLength();
	if ( iStringSize <= 0 )
	{
		return -1;
	}

	BYTE bySendBuffer[256];
	memset(bySendBuffer, 0x00, sizeof(bySendBuffer));

	int i = 0;
	for ( i = 0; i < iStringSize; i++ )
	{
		bySendBuffer[i] = (BYTE)(sSend.GetAt(i));
	}

	int iRet = SendData_Light_Controller(bySendBuffer, iStringSize);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}

//! Channel On/Off
//! [주의 사항] 'iNoChannel' 값은 조명 컨트롤러의 실제 채널 입력값이다. 
int CLightControl::SetChannel_OnOff(int iNoChannel, bool bSwitch_On)
{
	CString sSend = _T("");
    sSend.Format(_T("]%02d"), iNoChannel);
    //ex) "]011" = ch1 on
    //ex) "]010" = ch1 off
	if ( bSwitch_On == true )
	{
		sSend += _T("1");
	}
	else
	{
		sSend += _T("0");
	}

	int iRet = SendData_Light_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	return 1;
}

//! 각 Channel의 밝기값(PWM값) 조절
//! [주의 사항] 'iNoChannel' 값은 조명 컨트롤러의 실제 채널 입력값이다. 
int CLightControl::SetChannel_Value(int nCh, int data)
{
#if 0
	unsigned char sSendBuff[100];
	int nSendSize;
	int nRetVal;
	int nChVal;

	//if (nCh == 0)
	//	nChVal = 0xF0;

	unsigned char lightData[2];
	unsigned char chData;
	memset(lightData, 0x00, sizeof(lightData));
	chData = ((unsigned char)0xFF & (nCh << 4));
	lightData[0] = ((unsigned char)0xFF & (data >> 8));
	lightData[1] = ((unsigned char)0xFF & data);
	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	sSendBuff[0] = 0x5A;
	sSendBuff[1] = 0x07;
	sSendBuff[2] = 0x01;
	sSendBuff[3] = 0x06;			// Command 06 = 개별 채널 pow 조절 , 03 = 전채널 pow조절
									//
	sSendBuff[4] = chData + lightData[0];			// 상위	( 채널)
	sSendBuff[5] = lightData[1];
	//
	//
	sSendBuff[6] = 0x88; 
	nSendSize = 7;

	nRetVal = SendData_Light_Controller(sSendBuff, nSendSize); ;// LightSerial.SendData(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
		return 0;
#else
	if (data < 0 )
	{
		data = 0;
	}
	if (data > 255 )
	{
		data = 255;
	}

	CString sSend = _T("");
	sSend.Format(_T("[%02d%03d"), nCh, data);

	int iRet = SendData_Light_Controller(sSend);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}
#endif
	return 1;
}


void CLightControl::dpctrlLedVolume(int iChannel, int iValue)
{
	int chNo = iChannel + 1;
	Sleep(10);
	DPS_SetChannel_Value(chNo, iValue);
}

void CLightControl::ctrlLedVolume(int iChannel, int iValue)
{
    int chNo = iChannel + 1; 
    SetChannel_OnOff(chNo, true);
	Sleep(10); 
	//DPS_SetChannel_Value(chNo, iValue);
    SetChannel_Value(chNo, iValue);
}


bool CLightControl::SendLightValue(int data)
{
	unsigned char sSendBuff[100];
	int nSendSize = 0;

	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	sSendBuff[0] = BCR_STX;
	sSendBuff[1] = 0x03;		//value up/down
	sSendBuff[2] = 0x00;
	sSendBuff[3] = 0x00;
	sSendBuff[4] = 0x00;
	sSendBuff[5] = 0x00;
	sSendBuff[6] = data;
	sSendBuff[7] = BCR_ETX;
	nSendSize = 8;// 1;


	int nRetVal = SendData_Light_Controller(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
	{
		return false;
	}

	//nRetVal = LightSerial.SendData(sSendBuff, nSendSize);
	//if (nRetVal != nSendSize)
	//	return false;

	return true;
}

bool CLightControl::LxSetDataSave()
{
	unsigned char sSendBuff[100];
	int nSendSize = 0;

	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	sSendBuff[0] = BCR_STX;
	sSendBuff[1] = 0x05;		//State data Save E2P
	sSendBuff[2] = 0x00;
	sSendBuff[3] = 0x00;
	sSendBuff[4] = 0x00;
	sSendBuff[5] = 0x00;
	sSendBuff[6] = 0x00;
	sSendBuff[7] = BCR_ETX;
	nSendSize = 8;

	int nRetVal = SendData_Light_Controller(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
	{
		return false;
	}

	/*nRetVal = LightSerial.SendData(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
	return false;*/

	return true;
}

bool CLightControl::SendLightLxStep(int data)
{
	unsigned char sSendBuff[100];
	int nSendSize = 0;

	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	sSendBuff[0] = BCR_STX;
	sSendBuff[1] = 0x09;		//Lx Step Set
	sSendBuff[2] = 0x00;
	sSendBuff[3] = data;
	sSendBuff[4] = 0x00;
	sSendBuff[5] = 0x00;
	sSendBuff[6] = 0x00;
	sSendBuff[7] = BCR_ETX;
	nSendSize = 8;// 1;

	int nRetVal = SendData_Light_Controller(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
	{
		return false;
	}

	/*nRetVal = LightSerial.SendData(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
	return false;*/

	return true;
}


bool CLightControl::SendLightChange(int Use)
{
	unsigned char sSendBuff[100];
	int nSendSize = 0;

	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	sSendBuff[0] = BCR_STX;
	sSendBuff[1] = 0x02;
	if (Use == 0)//OC_LIGHT_5000K)
	{
		sSendBuff[2] = 0x00;
	}
	else
	{
		sSendBuff[2] = 0x01;
	}
	sSendBuff[3] = 0x00;
	sSendBuff[4] = 0x00;
	sSendBuff[5] = 0x00;
	sSendBuff[6] = 0x00;
	sSendBuff[7] = BCR_ETX;
	nSendSize = 8;// 1;

	int nRetVal = SendData_Light_Controller(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
	{
		return false;
	}

	/*nRetVal = LightSerial.SendData(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
	return false;*/

	return true;
}

bool CLightControl::SendDomeChartLightONOFF(bool Use)
{
	unsigned char sSendBuff[100];
	int nSendSize;
	int nRetVal;

	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	sSendBuff[0] = 0x48;		//H
	sSendBuff[1] = 0x54;		//T
	sSendBuff[2] = 0x4F;		//O
	if (Use == true)
	{
		sSendBuff[3] = 0x4E;		//N
	}
	else
	{
		sSendBuff[3] = 0x46;		//F
	}
	sSendBuff[4] = 0x0D;		//CR
	sSendBuff[5] = 0x0A;		//LF
	nSendSize = 6;


	nRetVal = SendData_Light_Controller(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
	{
		return false;
	}

	return true;
}


bool CLightControl::SendDomeChartLightValue(int mCh, int mValue)
{
	unsigned char sSendBuff[100];
	byte forData;
	byte backData;
	int nSendSize;
	int nRetVal;

	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	sSendBuff[0] = 0x43;	//C
	if (mCh > 8)
	{
		sSendBuff[1] = 0x41 + mCh - 9 ;		//1~9, A~G(10~16) Channel number
	}
	else
	{
		sSendBuff[1] = 0x30 + mCh + 1;		//1~9, A~G(10~16) Channel number
	}
	forData = ((unsigned char)0xF & (mValue >> 4));
	backData = ((unsigned char)0xF & mValue);
	if (forData >= 0x0a)
	{
		forData += 7;
	}
	if (backData >= 0x0a)
	{
		backData += 7;
	}
	sSendBuff[2] = 0x30 + forData;				//High data nibble(0~F)
	sSendBuff[3] = 0x30 + backData;				//Low data nibble(0~F)
	sSendBuff[4] = 0x0D;//0x0D;	0x44	//CR 
	sSendBuff[5] = 0x0A;//0x0A;	0x41	//LF
	nSendSize = 6;


	nRetVal = SendData_Light_Controller(sSendBuff, nSendSize);
	/*CString mSenddata;
	mSenddata.Format(_T("C1AADA"));
	nRetVal = SendData_Light_Controller(mSenddata);*/
	if (nRetVal != nSendSize) 
	{
		return false;
	}

	return true;
}



bool CLightControl::SendLightONOFF(bool Use)
{
	unsigned char sSendBuff[100];
	int nSendSize;
	int nRetVal;

	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	sSendBuff[0] = 0x48;		//H
	sSendBuff[1] = 0x54;		//T
	sSendBuff[2] = 0x4F;		//O
	if (Use == true)
	{
		sSendBuff[3] = 0x4E;		//N
	}
	else
	{
		sSendBuff[3] = 0x46;		//F
	}
	sSendBuff[4] = 0x0D;		//CR
	sSendBuff[5] = 0x0A;		//LF
	nSendSize = 6;
	

	nRetVal = SendData_Light_Controller(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
	{
		return false;
	}

	return true;
}
