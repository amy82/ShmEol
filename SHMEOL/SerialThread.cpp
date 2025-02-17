#include "stdafx.h"
#include "SerialThread.h"

#define LIGHT_STX			0x52		// 'R'
#define LIGHT_ETX			0x0A		// LF


#define BCR_STX				0x02
#define BCR_ETX				0x03

#define BCR_ACK				0x06
#define BCR_LF				0x0a
#define BCR_CR				0x0d
#define BCR_EOD				0x04
#define BCR_NAK				0x15
CSerialThread::CSerialThread()
{
	int i;
	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		m_bKeyenceOpen[i] = false;
		m_bKeyenceStxState[i] = false;

		m_bLightOpen[i] = false;
		m_bLightStxState[i] = false;

		m_bBcrOpen[i] = false;
		m_bBcrStxState[i] = false;
	}


}


CSerialThread::~CSerialThread()
{
}

//-----------------------------------------------------------------------------
//
//	스레드 생성자
//
//-----------------------------------------------------------------------------
void CSerialThread::ThreadConstructor()
{

}

//-----------------------------------------------------------------------------
//
//	스레드 소멸자
//
//-----------------------------------------------------------------------------
void CSerialThread::ThreadDestructor()
{
	int i;
	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		this->CloseKeyenceSerial(i);

		this->CloseLightSerial(i);
	}
}

//-----------------------------------------------------------------------------
//
//	스레드 콜백
//
//-----------------------------------------------------------------------------
void CSerialThread::ThreadCallBack()
{
	int i;

	for (i = 0; i < MAX_UNIT_COUNT; i++)
	{
		if (m_bKeyenceOpen[i] == true)
		{
			//this->RecvKeyenceSerial(i);
		}

		if(m_bLightOpen[i] == true)
		{
			this->RecvLightSerial(i);
		}

		if (m_bBcrOpen[i] == true)
		{
			this->RecvBcrSerial(i);
		}
		
	}	
}

//-----------------------------------------------------------------------------
//
//	레이저 변위센서 시리얼 OPEN
//
//-----------------------------------------------------------------------------
bool CSerialThread::OpenKeyenceSerial(int nUnit, int nPort, int nBaudRate)
{
	if(m_bKeyenceOpen[nUnit] == true)
		return true;

	if (m_clSerialKeyence[nUnit].Open(nPort, nBaudRate) == false)
	{
		return false;
	}

	m_bKeyenceOpen[nUnit] = true;

	return true;
}

//-----------------------------------------------------------------------------
//
//	레이저 변위센서 시리얼 CLOSE
//
//-----------------------------------------------------------------------------
void CSerialThread::CloseKeyenceSerial(int nUnit)
{
	if(m_bKeyenceOpen[nUnit] == false)
		return;

	m_clSerialKeyence[nUnit].Close();
	m_bKeyenceOpen[nUnit] = false;
}

//-----------------------------------------------------------------------------
//
//	레이저 변위센서 시리얼 수신
//
//-----------------------------------------------------------------------------
void CSerialThread::RecvKeyenceSerial(int nUnit)
{
	unsigned char sRecvBuff[SIZE_OF_1K];
	int nRecvLen;

	memset(sRecvBuff, 0x00, sizeof(sRecvBuff));
	nRecvLen = m_clSerialKeyence[nUnit].ReadData(sRecvBuff, sizeof(sRecvBuff));
	if (nRecvLen > 0)
	{
		this->ParseKeyenceSerial(nUnit, sRecvBuff, nRecvLen);
	}
}

//-----------------------------------------------------------------------------
//
//	레이저 변위센서 패킷 파싱
//
//-----------------------------------------------------------------------------
void CSerialThread::ParseKeyenceSerial(int nUnit, unsigned char* pRecvBuff, int nRecvLen)  
{
	double dValue[2];
	TCHAR szLog[SIZE_OF_1K];
	//CString szMsg[MAX_LANG_COUNT];
	CString sPacket = _T("");
	CString sToken = _T("");
	CString sToken2 = _T("");

	//pRecvBuff = 0x0000002c4ad30bb0"MM,-05.1671,0,-99.9998,2\r"
	//int i;
	sPacket = (char*)pRecvBuff;
	dValue[0] = dValue[1] = 0.0;
	AfxExtractSubString(sToken, sPacket, 0, _T(','));
	sToken.Remove(_T('\r'));
	int firstLen = -1;
	if (sToken == _T("MM") || sToken == _T("KLMM"))
	{
		firstLen = 2;
	}
	//_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER TILT 2] (%s , %d , %d)"), sToken, firstLen, sToken2);
	//AddLog(szLog, 0, nUnit);
	if (firstLen < 0)
	{
		return;
	}
	// HEAD 1
	AfxExtractSubString(sToken2, sPacket, 2, _T(','));

	if (sToken2 == _T("0"))
	{
		AfxExtractSubString(sToken, sPacket, 1, _T(','));
		dValue[0] = _ttof((TCHAR*)(LPCTSTR)sToken);
		//_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] Index (%d)"), g_clTaskWork[nUnit].m_nLaserTiltIndex);
		//AddLog(szLog, 0, nUnit);
		if ((g_clTaskWork[nUnit].m_nLaserTiltIndex >= 0) && (g_clTaskWork[nUnit].m_nLaserTiltIndex < 4))
		{
			g_clTaskWork[nUnit].m_dLaserVal[g_clTaskWork[nUnit].m_nLaserTiltIndex] = dValue[0];
			g_clTaskWork[nUnit].m_bRecvLaserTilt = true;



			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] (%d) : %.03lf"), g_clTaskWork[nUnit].m_nLaserTiltIndex + 1, dValue[0]);
			AddLog(szLog, 0, nUnit);
		}
	}


	// HEAD 2
	AfxExtractSubString(sToken2, sPacket, 4, _T(','));
	if (sToken2 == _T("0"))
	{
		AfxExtractSubString(sToken, sPacket, 3, _T(','));

		dValue[1] = _ttof((TCHAR*)(LPCTSTR)sToken);
		/*if ((g_clTaskWork[1].m_nLaserTiltIndex >= 0) && (g_clTaskWork[1].m_nLaserTiltIndex < 4))
		{
		g_clTaskWork[1].m_dLaserVal[g_clTaskWork[1].m_nLaserTiltIndex] = dValue[1];
		g_clTaskWork[1].m_bRecvLaserTilt = true;
		}*/
	}


	sPacket.Empty();
	sToken.Empty();
	sToken2.Empty();
}

//-----------------------------------------------------------------------------
//
//	레이저 변위센서 패킷 처리
//
//-----------------------------------------------------------------------------
void CSerialThread::ProcessKeyencePacket(int nUnit, unsigned char* pRecvBuff, int nRecvLen)
{
	TCHAR szLog[SIZE_OF_1K];
	CString szToken;
	double dValue[2];
	int i;

	szToken.Empty();
	dValue[0] = dValue[1] = 0.0;

	_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER TILT] RECV %s"), pRecvBuff);
	AddLog(szLog, 0, nUnit);

	AfxExtractSubString(szToken, (char*)pRecvBuff, 0, _T(','));
	if (szToken == "M0")
	{
		AfxExtractSubString(szToken, (char*)pRecvBuff, 1, ',');
		for (i = 1; i < szToken.GetLength() - 1; i++)
		{
			if (szToken.GetAt(i) == '.' || szToken.GetAt(i) == '+' || szToken.GetAt(i) == '-')
				continue;

			if (szToken.GetAt(i) < '0' || szToken.GetAt(i) > '9')
				return;
		}

		dValue[0] = atof((LPSTR)(LPCTSTR)szToken);

		AfxExtractSubString(szToken, (char*)pRecvBuff, 2, ',');
		for (i = 1; i < szToken.GetLength() - 1; i++)
		{
			if (szToken.GetAt(i) == '.' || szToken.GetAt(i) == '+' || szToken.GetAt(i) == '-')
				continue;

			if (szToken.GetAt(i) < '0' || szToken.GetAt(i) > '9')
				return;
		}

		dValue[1] = atof((LPSTR)(LPCTSTR)szToken);

		if (g_clTaskWork[nUnit].m_nLaserTiltIndex >= 0 && g_clTaskWork[nUnit].m_nLaserTiltIndex < 4)
		{
			g_clTaskWork[nUnit].m_bRecvLaserTilt = true;
		}
	}
	else if (szToken == "M1")
	{
		AfxExtractSubString(szToken, (char*)pRecvBuff, 1, ',');
		for (i = 1; i < szToken.GetLength() - 1; i++)
		{
			if (szToken.GetAt(i) == '.' || szToken.GetAt(i) == '+' || szToken.GetAt(i) == '-')
				continue;

			if (szToken.GetAt(i) < '0' || szToken.GetAt(i) > '9')
				return;
		}

		dValue[0] = atof((LPSTR)(LPCTSTR)szToken);

		//20161021
		if (g_clTaskWork[nUnit].m_nLaserTiltIndex >= 0 && g_clTaskWork[nUnit].m_nLaserTiltIndex < 4)		
		{
			g_clTaskWork[nUnit].m_dLaserVal[g_clTaskWork[nUnit].m_nLaserTiltIndex] = dValue[0] / 1000;

			g_clTaskWork[nUnit].m_bRecvLaserTilt = true;
		}

		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER TILT] (%d) : %.03lf"), g_clTaskWork[nUnit].m_nLaserTiltIndex, dValue[0]);
		AddLog(szLog, 0, nUnit);
	}
	else if (szToken == "M2")
	{
		AfxExtractSubString(szToken, (char*)pRecvBuff, 2, ',');
		for (i = 1; i < szToken.GetLength() - 1; i++)
		{
			if (szToken.GetAt(i) == '.' || szToken.GetAt(i) == '+' || szToken.GetAt(i) == '-')
				continue;

			if (szToken.GetAt(i) < '0' || szToken.GetAt(i) > '9')
				return;
		}

		dValue[1] = atof((LPSTR)(LPCTSTR)szToken);

		if (g_clTaskWork[nUnit].m_nLaserTiltIndex >= 0 && g_clTaskWork[nUnit].m_nLaserTiltIndex < 4)
		{
			g_clTaskWork[nUnit].m_bRecvLaserTilt = true;
		}
	}
}

//-----------------------------------------------------------------------------
//
//	레이저 변위센서 측정 명령 송신
//
//-----------------------------------------------------------------------------
bool CSerialThread::SendKeyenceMeasureSet(int nUnit)
{
	unsigned char sSendBuff[SIZE_OF_1K];
	TCHAR szLog[SIZE_OF_1K];
	int nSendSize = 0;
	int nRetVal = 0;

	if (m_bKeyenceOpen[nUnit] == false)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER SENSOR] COM%d PORT CLOSED"), g_clSysData.m_nTopLightPort[nUnit]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	nSendSize = 0;
	nRetVal = 0;
	sSendBuff[0] = 'M';
	sSendBuff[1] = 'M';
	sSendBuff[2] = ',';
	sSendBuff[3] = '1';
	sSendBuff[4] = ',';
	//
	sSendBuff[5] = '1';
	sSendBuff[6] = '1';
	sSendBuff[7] = '0';
	sSendBuff[8] = '0';
	sSendBuff[9] = '0';
	sSendBuff[10] = '0';
	sSendBuff[11] = '0';
	sSendBuff[12] = '0';
	sSendBuff[13] = '\r';

	nSendSize = 14;
	if (g_clTaskWork[nUnit].m_nAutoFlag != MODE_AUTO) 
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] SEND:%s"), (char*)sSendBuff);
		AddLog(szLog, 0, nUnit);
	}
	nRetVal = m_clSerialKeyence[nUnit].SendData(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
	{
		if (g_clTaskWork[nUnit].m_nAutoFlag != MODE_AUTO) {
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] SEND FAIL: %d/%d"), nRetVal, nSendSize);
			AddLog(szLog, 0, nUnit);
		}
		return false;
	}
	if (g_clTaskWork[nUnit].m_nAutoFlag != MODE_AUTO)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] SEND OK: %d/%d"), nRetVal, nSendSize);
		AddLog(szLog, 0, nUnit);
	}
	//-----------------------------------------------------------------------------------
	//191024_1 
	//test
	Sleep(100);
	unsigned char sRecvBuff[SIZE_OF_1K];
	int nRecvLen = 0;

	memset(sRecvBuff, 0x00, sizeof(sRecvBuff));
	nRecvLen = m_clSerialKeyence[nUnit].ReadData(sRecvBuff, sizeof(sRecvBuff));
	if (g_clTaskWork[nUnit].m_nAutoFlag != MODE_AUTO)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] RECV LENGH: %d"), nRecvLen);
		AddLog(szLog, 0, nUnit);
	}
	if (nRecvLen > 0)
	{
		if (g_clTaskWork[nUnit].m_nAutoFlag != MODE_AUTO)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER] RECV : %s"), sRecvBuff);
			AddLog(szLog, 0, nUnit);
		}
		this->ParseKeyenceSerial(nUnit, sRecvBuff, nRecvLen);

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//
//	레이저 변위센서 LOCK 명령 송신
//
//-----------------------------------------------------------------------------
bool CSerialThread::SendKeyLockSet(int nUnit, bool bLock)
{
	unsigned char sSendBuff[SIZE_OF_1K];
	TCHAR szLog[SIZE_OF_1K];
	int nSendSize;
	int nRetVal;

	if (m_bKeyenceOpen[nUnit] == false)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER SENSOR] COM%d PORT CLOSED"), g_clSysData.m_nTopLightPort[nUnit]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	nSendSize = 0;
	nRetVal = 0;

	sSendBuff[0] = 'K';
	sSendBuff[1] = 'L';
	sSendBuff[2] = ',';
	if(bLock == true)
		sSendBuff[3] = '1';
	else
		sSendBuff[3] = '0';
	sSendBuff[4] = '\r';

	nSendSize = 5;

	nRetVal = m_clSerialKeyence[nUnit].SendData(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
	{
		return false;
	}

	_stprintf_s(szLog, SIZE_OF_1K, _T("[LASER SENSOR] %s"), (char*)sSendBuff);
	AddLog(szLog, 0, nUnit);

	return true;
}

//-----------------------------------------------------------------------------
//
//	DOME 조명 시리얼 오픈
//
//-----------------------------------------------------------------------------
bool CSerialThread::OpenLightSerial(int nUnit, int nPort, int nBaudRate)
{
	if(m_bLightOpen[nUnit] == true)
		return true;

	if (m_clSerialLight[nUnit].Open(nPort, nBaudRate) == false)
	{
		return false;
	}

	m_bLightOpen[nUnit] = true;

	return true;
}

//-----------------------------------------------------------------------------
//
//	DOME 조명 시리얼 CLOSE
//
//-----------------------------------------------------------------------------
void CSerialThread::CloseLightSerial(int nUnit)
{
	if(m_bLightOpen[nUnit] == false)
		return;

	m_clSerialLight[nUnit].Close();
	m_bLightOpen[nUnit] = false;
}

//-----------------------------------------------------------------------------
//
//	DOME 조명 시리얼 수신
//
//-----------------------------------------------------------------------------
void CSerialThread::RecvLightSerial(int nUnit)
{
	unsigned char sRecvBuff[SIZE_OF_1K];
	int nRecvLen;

	nRecvLen = m_clSerialLight[nUnit].ReadData(sRecvBuff, sizeof(sRecvBuff));
	if(nRecvLen > 0)
	{
		this->ParseLightSerial(nUnit, sRecvBuff, nRecvLen);
	}
}

//-----------------------------------------------------------------------------
//
//	DOME 조명 시리얼 패킷 파싱
//
//-----------------------------------------------------------------------------
void CSerialThread::ParseLightSerial(int nUnit, unsigned char* pRecvBuff, int nRecvLen)
{
	TCHAR szLog[SIZE_OF_1K];
	int i;

	for(i = 0; i < nRecvLen; i++)
	{
		// STX 안받은 상태
		if(m_bLightStxState == false)
		{
			memset(m_sLightPacketBuff[nUnit], 0x00, sizeof(m_sLightPacketBuff[nUnit]));
			m_nLightBuffPosi[nUnit] = 0;

			m_sLightPacketBuff[nUnit][m_nLightBuffPosi[nUnit]] = pRecvBuff[i];

			m_bLightStxState[nUnit] = true;
		}
		// STX 받은 상태
		else
		{
			// 패킷 버퍼 오버플로우 검사
			if(m_nLightBuffPosi[nUnit] >= (sizeof(m_sLightPacketBuff[nUnit]) - 1))
			{
				m_bLightStxState[nUnit] = false;
				continue;
			}

			m_nLightBuffPosi[nUnit]++;
			m_sLightPacketBuff[nUnit][m_nLightBuffPosi[nUnit]] = pRecvBuff[i];

			if(m_sLightPacketBuff[nUnit][m_nLightBuffPosi[nUnit]] == LIGHT_ETX)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("(<-DOME) %s"), (char*)m_sLightPacketBuff[nUnit]);
				
				AddLog(szLog, 0, nUnit);
				
				m_bLightStxState[nUnit] = false;
			}
		}
	}
}

//-----------------------------------------------------------------------------
//
//	DOME 조명 ON/OFF 패킷 송신
//
//-----------------------------------------------------------------------------
bool CSerialThread::SendLightOnOffSet(int nUnit, unsigned char cCmd, int nCh, bool bOn/* = true*/, bool bAllCh/* = false*/)
{
	TCHAR szLog[SIZE_OF_1K];
	unsigned char sSendBuff[SIZE_OF_100BYTE];
	int nSendSize = 0;
	int nRetVal;

	if(m_bLightOpen == false)
		return false;

	memset(sSendBuff, 0x00, sizeof(sSendBuff));

	sSendBuff[0] = cCmd;
	if(bAllCh == true)
		sSendBuff[1] = 'T';
	else
		sSendBuff[1] = (unsigned char)(0x30 + nCh);
	if(bOn == true)
	{
		sSendBuff[2] = 'O';
		sSendBuff[3] = 'N';
	}
	else
	{
		sSendBuff[2] = 'O';
		sSendBuff[3] = 'F';
	}
	sSendBuff[4] = 0x0D;
	sSendBuff[5] = LIGHT_ETX;

	nSendSize = 6;

	nRetVal = m_clSerialLight[nUnit].SendData(sSendBuff, nSendSize);
	if(nRetVal != nSendSize)
	{
		return false;
	}

	_stprintf_s(szLog, SIZE_OF_1K, _T("(->DOME) %s"), sSendBuff);
	AddLog(szLog, 0, nUnit);

	return true;
}
//-----------------------------------------------------------------------------
//
//	DOME 조명 조명 설정 패킷 송신
//
//-----------------------------------------------------------------------------
bool CSerialThread::SendLightSet(int nUnit, unsigned char cCmd, int nCh, int nChVal, bool bAllCh/* = false*/)
{
	TCHAR szLog[SIZE_OF_1K];
	unsigned char sSendBuff[SIZE_OF_100BYTE];
	int nSendSize = 0;
	int nRetVal;

	if(m_bLightOpen == false)
		return false;

	memset(sSendBuff, 0x00, sizeof(sSendBuff));

	sSendBuff[0] = cCmd;
	if(bAllCh == true)
		sSendBuff[1] = 'T';
	else
		sSendBuff[1] = (unsigned char)(0x30 + nCh);
	sSendBuff[2] = (unsigned char)((nChVal & 0xF0) >> 4);
	if(sSendBuff[2] >= 0 && sSendBuff[2] <= 9)
		sSendBuff[2] += 0x30;
	else if(sSendBuff[2] >= 0x0A && sSendBuff[2] <= 0x0F)
		sSendBuff[2] += (0x41 - 0x0A);
	else
		return false;

	sSendBuff[3] = (unsigned char)(nChVal & 0x0F);
	if(sSendBuff[3] >= 0 && sSendBuff[3] <= 9)
		sSendBuff[3] += 0x30;
	else if(sSendBuff[3] >= 0x0A && sSendBuff[3] <= 0x0F)
		sSendBuff[3] += (0x41 - 0x0A);
	else
		return false;

	sSendBuff[4] = 0x0D;
	sSendBuff[5] = LIGHT_ETX;

	nSendSize = 6;

	nRetVal = m_clSerialLight[nUnit].SendData(sSendBuff, nSendSize);
	if(nRetVal != nSendSize)
	{
		return false;
	}

	_stprintf_s(szLog, SIZE_OF_1K, _T("(->DOME) %s"), sSendBuff);
	AddLog(szLog, 0, nUnit);

	return true;
}



//-----------------------------------------------------------------------------
//
//	BCR 시리얼 OPEN
//
//-----------------------------------------------------------------------------
bool CSerialThread::OpenBcrSerial(int nUnit, int nPort, int nBaudRate)
{
	if (m_bBcrOpen[nUnit] == true)
	{
		return true;
	}
	if (m_clSerialBcr[nUnit].Open(nPort, nBaudRate) == false)
	{
		return false;
	}

	m_bBcrOpen[nUnit] = true;

	return true;
}

//-----------------------------------------------------------------------------
//
//	BCR 시리얼 CLOSE
//
//-----------------------------------------------------------------------------
void CSerialThread::CloseBcrSerial(int nUnit)
{
	if (m_bBcrOpen[nUnit] == false)
		return;

	m_clSerialBcr[nUnit].Close();
	m_bBcrOpen[nUnit] = false;
}
//-----------------------------------------------------------------------------
//
//	BCR 시리얼 송신
//
//-----------------------------------------------------------------------------
bool CSerialThread::TransmitBcrSerial(int nUnit, CString sBcrData)
{
	char sRecvBuff[SIZE_OF_1K];
	int nRecvLen = 0;
	int nSendSize = 0;
	memset(sRecvBuff, 0x00, sizeof(sRecvBuff));
	sprintf_s(sRecvBuff, SIZE_OF_100BYTE, "%s\r", sBcrData);//sprintf_s(sRecvBuff, SIZE_OF_100BYTE, "%s\r\n", sBcrData); 
	nSendSize = sBcrData.GetAllocLength() + 1;
	nRecvLen = m_clSerialBcr[nUnit].SendData((unsigned char*)sRecvBuff, nSendSize);
	if (nRecvLen != nSendSize) {
		return false; 
	}
	return true;
}


//-----------------------------------------------------------------------------
//
//	BCR 시리얼 수신
//
//-----------------------------------------------------------------------------
void CSerialThread::RecvBcrSerial(int nUnit)
{
	unsigned char sRecvBuff[SIZE_OF_1K];
	int nRecvLen;

	memset(sRecvBuff, 0x00, sizeof(sRecvBuff));
	nRecvLen = m_clSerialBcr[nUnit].ReadData(sRecvBuff, sizeof(sRecvBuff));
	if (nRecvLen > 0)// && ( g_clTaskWork[nUnit].m_nCurrentPcbStep == 33000 || g_clTaskWork[UNIT_AA1].m_nAutoFlag == MODE_STOP) )
	{
		m_bBcrStxState[nUnit] = false;
		this->ParseBcrSerial(nUnit, sRecvBuff, nRecvLen);
	}
}


//-----------------------------------------------------------------------------
//
//	BCR 시리얼 패킷 파싱
//
//-----------------------------------------------------------------------------
void CSerialThread::ParseBcrSerial(int nUnit, unsigned char* pRecvBuff, int nRecvLen)
{
	TCHAR szLog[SIZE_OF_1K];
	int i;

	for (i = 0; i < nRecvLen; i++)
	{
		// STX 안받은 상태
		if (m_bBcrStxState[nUnit] == false)
		{
			// STX 수신?
			if (true)	//	pRecvBuff[i] == BCR_STX)
			{
				memset(m_sLBcrPacketBuff[nUnit], 0x00, sizeof(m_sLBcrPacketBuff[nUnit]));
				m_nBcrBuffPosi[nUnit] = 0;

				m_sLBcrPacketBuff[nUnit][m_nBcrBuffPosi[nUnit]] = pRecvBuff[i];

				m_bBcrStxState[nUnit] = true;
			}
		}
		// STX 받은 상태
		else
		{
			// 패킷 버퍼 오버플로우 검사
			if (m_nBcrBuffPosi[nUnit] >= (sizeof(m_sLBcrPacketBuff[nUnit]) - 1))
			{
				m_bBcrStxState[nUnit] = false;
				continue;
			}

			m_nBcrBuffPosi[nUnit]++;
			m_sLBcrPacketBuff[nUnit][m_nBcrBuffPosi[nUnit]] = pRecvBuff[i];

			if (m_sLBcrPacketBuff[nUnit][m_nBcrBuffPosi[nUnit]] == BCR_CR)//m_sLBcrPacketBuff[nUnit][m_nBcrBuffPosi[nUnit]] == BCR_LF && m_sLBcrPacketBuff[nUnit][m_nBcrBuffPosi[nUnit] - 1] == BCR_CR)
			{
				m_sLBcrPacketBuff[nUnit][m_nBcrBuffPosi[nUnit]] = 0x00;
				_stprintf_s(szLog, SIZE_OF_1K, _T("[BCR] REV:%s"), (char*)m_sLBcrPacketBuff[nUnit]);

				AddLog(szLog,0, nUnit, false);


				_stprintf_s(g_clTaskWork[nUnit].m_szChipID, SIZE_OF_100BYTE, _T("%s"), (char*)m_sLBcrPacketBuff[nUnit]);
				g_pCarAABonderDlg->ShowBarcode(nUnit);

				m_bBcrStxState[nUnit] = false;
			}
		}
	}
}



//-----------------------------------------------------------------------------
//
//	Uv 시리얼 OPEN
//
//-----------------------------------------------------------------------------
bool CSerialThread::OpenUvSerial(int nUnit, int nPort, int nBaudRate)
{
	if (m_bUvOpen[nUnit] == true)
		return true;

	if (m_clSerialUv[nUnit].Open(nPort, nBaudRate) == false)
	{
		return false;
	}

	m_bUvOpen[nUnit] = true;

	return true;
}

//-----------------------------------------------------------------------------
//
//	레이저 변위센서 시리얼 CLOSE
//
//-----------------------------------------------------------------------------
void CSerialThread::CloseUvSerial(int nUnit)
{
	if (m_bUvOpen[nUnit] == false)
		return;

	m_clSerialUv[nUnit].Close();
	m_bUvOpen[nUnit] = false;
}


bool CSerialThread::UV_Shutter_PowerSet(int nUnit, int value)
{
	unsigned char sSendBuff[SIZE_OF_1K];
	TCHAR szLog[SIZE_OF_1K];
	TCHAR szData[SIZE_OF_100BYTE];
	int nRetVal = -1;
	int nSendSize = 0;
	//sSend.Format(":EP,%d\n", value);
	
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), value);
	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	sSendBuff[0] = ':';
	sSendBuff[1] = 'E';
	sSendBuff[2] = 'P';
	sSendBuff[3] = ',';
	if (value >= 100)
	{
		sSendBuff[4] = szData[0];
		sSendBuff[5] = szData[1];
		sSendBuff[6] = szData[2];
		sSendBuff[7] = BCR_CR;// '\n';
		sSendBuff[8] = BCR_LF;// '\r';
		nSendSize = 9;
	}
	else if (value > 10)
	{
		sSendBuff[4] = szData[0];
		sSendBuff[5] = szData[1];
		sSendBuff[6] = BCR_CR;// '\n';
		sSendBuff[7] = BCR_LF;// '\r';
		nSendSize = 8;
	}
	else
	{
		sSendBuff[4] = szData[0];
		sSendBuff[5] = BCR_CR;// '\n';
		sSendBuff[6] = BCR_LF;// '\r';
		nSendSize = 6;
	}
	
	nRetVal = m_clSerialUv[nUnit].SendData(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[UV] SEND FAIL: %d/%d"), nRetVal, nSendSize);
		AddLog(szLog, 0, nUnit);
		return false;
	}
	_stprintf_s(szLog, SIZE_OF_1K, _T("[UV] SEND OK: %d/%d"), nRetVal, nSendSize);
	AddLog(szLog, 0, nUnit);
	return true;
}
bool CSerialThread::UV_Shutter_Open(int nUnit)
{
	unsigned char sSendBuff[SIZE_OF_1K];
	TCHAR szLog[SIZE_OF_1K];
	int nRetVal = -1;
	int nSendSize = 0;

	//sSend = _T(":EONT\n");
	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	sSendBuff[0] = ':';
	sSendBuff[1] = 'E';
	sSendBuff[2] = 'O';
	sSendBuff[3] = 'N';
	sSendBuff[4] = 'T';
	sSendBuff[5] = BCR_CR;
	sSendBuff[6] = BCR_LF;
	//sSendBuff[7] = BCR_EOD;// EOD

	nSendSize = 7;

	nRetVal = m_clSerialUv[nUnit].SendData(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[UV] SEND FAIL: %d/%d"), nRetVal, nSendSize);
		AddLog(szLog, 0, nUnit);
		return false;
	}
	_stprintf_s(szLog, SIZE_OF_1K, _T("[UV] SEND OK: %d/%d"), nRetVal, nSendSize);
	AddLog(szLog, 0, nUnit);

	return true;
}
bool CSerialThread::UV_Shutter_Close(int nUnit)
{
	unsigned char sSendBuff[SIZE_OF_1K];
	TCHAR szLog[SIZE_OF_1K];
	int nRetVal = -1;
	int nSendSize = 0;

	//sSend = _T("S0");
	//sSend = _T(":E0\n");
	memset(sSendBuff, 0x00, sizeof(sSendBuff));
	sSendBuff[0] = ':';
	sSendBuff[1] = 'E';
	sSendBuff[2] = '0';
	sSendBuff[3] = BCR_CR;
	sSendBuff[4] = BCR_LF; 
	//sSendBuff[5] = BCR_EOD;// EOD

	nSendSize = 5; 

	nRetVal = m_clSerialUv[nUnit].SendData(sSendBuff, nSendSize);
	if (nRetVal != nSendSize)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[UV] SEND FAIL: %d/%d"), nRetVal, nSendSize);
		AddLog(szLog, 0, nUnit);
		return false;
	}
	_stprintf_s(szLog, SIZE_OF_1K, _T("[UV] SEND OK: %d/%d"), nRetVal, nSendSize);
	AddLog(szLog, 0, nUnit);

	return true;
}