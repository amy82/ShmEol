#include "stdafx.h"
#include "OCControl.h"
#include "../../../AutoInspDlg.h"
#define BCR_STX				0x02
#define BCR_ETX				0x03

#define BCR_ACK				0x06
#define BCR_NAK				0x15

COcControl::COcControl()
{
	m_pMainDlg = NULL;
}
COcControl::~COcControl()
{
}
void COcControl::init()
{

}
bool COcControl::OpenLightClose()
{
	LightSerial.Close();
	return true;
}
bool COcControl::OpenLightSerial(unsigned int nPort, unsigned int nBaudRate)
{
	if (LightSerial.Open(nPort, nBaudRate) == false)
	{
		//m_pMainDlg->putListLog(_T("SERIAL OPEN FAIL!"));
		return false;
	}
	else
	{
		//m_pMainDlg->putListLog(_T("SERIAL OPEN OK!"));
		return true;
	}
}

bool COcControl::SendLightONOFF(bool Use)
{
	unsigned char sSendBuff[100];
	int nSendSize;
	int nRetVal;

	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	
	sSendBuff[0] = BCR_STX;
	sSendBuff[1] = 0x01;
	sSendBuff[2] = 0x00;
	sSendBuff[3] = 0x00;
	sSendBuff[4] = 0x00;
	sSendBuff[5] = 0x00;
	if (Use == true)
	{
		sSendBuff[6] = 1;
	}
	else
	{
		sSendBuff[6] = 0;
	}
	
	sSendBuff[7] = BCR_ETX;
	nSendSize = 8;// 1;

	nRetVal = LightSerial.SendData(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
		return false;

	return true;
}


bool COcControl::SendLightChange(int Use)
{
	unsigned char sSendBuff[100];
	int nSendSize;
	int nRetVal;

	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	sSendBuff[0] = BCR_STX;
	sSendBuff[1] = 0x02;
	if (Use == LIGHT_OC_WHITE_CH1)
	{
		sSendBuff[2] = 0x00;	//5000k
	}
	else
	{
		sSendBuff[2] = 0x01;	//6500k
	}
	sSendBuff[3] = 0x00;
	sSendBuff[4] = 0x00;
	sSendBuff[5] = 0x00;
	sSendBuff[6] = 0x00;
	sSendBuff[7] = BCR_ETX;
	nSendSize = 8;// 1;

	nRetVal = LightSerial.SendData(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
		return false;

	return true;
}


bool COcControl::SendLightValue(int data)
{
	unsigned char sSendBuff[100];
	int nSendSize;
	int nRetVal;

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

	nRetVal = LightSerial.SendData(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
		return false;

	return true;
}

bool COcControl::SendLightLxStep(int data)
{
	unsigned char sSendBuff[100];
	int nSendSize;
	int nRetVal;

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

	nRetVal = LightSerial.SendData(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
		return false;

	return true;
}

bool COcControl::LxSetDataSave()
{
	unsigned char sSendBuff[100];
	int nSendSize;
	int nRetVal;

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

	nRetVal = LightSerial.SendData(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
		return false;

	return true;
}


bool COcControl::Send_12CHLightONOFF(bool Use)
{
	unsigned char sSendBuff[100];
	int nSendSize;
	int nRetVal;

	memset(sSendBuff, 0x00, sizeof(sSendBuff));

	sSendBuff[0] = 0x5A;
	sSendBuff[1] = 0x07;
	sSendBuff[2] = 0x01;
	sSendBuff[3] = 0x05;	// Command on/off
	if (Use == true)
	{ 
		sSendBuff[4] = 0x01;		// 상위 
	}
	else
	{
		sSendBuff[4] = 0x00;		// 상위

	}
	sSendBuff[5] = 0x00;
	sSendBuff[6] = 0x88;
	nSendSize = 7;// 1; 

	nRetVal = LightSerial.SendData(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
		return false;
	return true;
}

bool COcControl::Send_12CHChannel_Value(int nCh, int data)
{
	unsigned char sSendBuff[100];
	int nSendSize;
	int nRetVal;

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

	nRetVal = LightSerial.SendData(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
		return false;

	//nRetVal = SendData_Light_Controller(sSendBuff, nSendSize); ;// LightSerial.SendData(sSendBuff, nSendSize);
	//if (nRetVal != nSendSize)
	//	return 0;
	Sleep(100);
	return true;
}