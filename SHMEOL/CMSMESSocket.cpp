#include "stdafx.h"
#include "CMSMESSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCMSMESSocket::CCMSMESSocket()
{
}


CCMSMESSocket::~CCMSMESSocket()
{
	WSACleanup();
}


/////////////////////////////////////////////////////////////////////////////////////////
int CCMSMESSocket::doOpen(const char* czIpAddr, int nPort)
{
	int				nResult = 0;
	//SOCKADDR_IN		tAddr = { 0 }; 
	struct sockaddr_in	tAddr;

	m_hServer = INVALID_SOCKET;
	m_hClient = INVALID_SOCKET;

	//  Check port number.
	if (nPort == 21 || nPort == 80 || nPort == 8080)	return ERROR_WRONG_PORT;

	// Winsock 사용 시작
	if (WSAStartup(MAKEWORD(2, 2), &m_wsaData) != NO_ERROR)	// Socket을 사용하기 위한 Init 작업, 반드시 호출 필요
	{
		WSACleanup();

		nResult = WSAGetLastError();
		return nResult;
	}

	// create socket
	m_hServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	// TCP Socket 생성
															//m_hServer = socket(PF_INET, SOCK_STREAM, 0);
	if (m_hServer == INVALID_SOCKET)
	{
		WSACleanup();

		nResult = WSAGetLastError();
		return nResult;
	}

	// 소켓에 부여할 서버의 IP 주소와 포트 번호 설정
	memset(&tAddr, 0x00, sizeof(tAddr));

	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons((short)nPort);
	//tAddr.sin_addr.s_addr = INADDR_ANY;
	inet_pton(AF_INET, czIpAddr, &tAddr.sin_addr);

	// 주소와 소켓을 연결
	if (::bind(m_hServer, (SOCKADDR*)&tAddr, sizeof(tAddr)) != NO_ERROR)
	{
		nResult = WSAGetLastError();
		return nResult;
	}

	// 소켓이 클라이언트 접속을 기다림.
	if (listen(m_hServer, 5) != NO_ERROR)
	{
		closesocket(m_hServer);
		nResult = WSAGetLastError();
		return nResult;
	}

	return 0;

}


// Server 인 경우에는 strIP 는 무시된다 (현재 PC 의 IP 로 설정해야 한다.)
int CCMSMESSocket::doConnect(const char* czIpAddr, int nPort)
{
	if (m_bConnected == true)
		return 0;

	int nRet = doOpen(czIpAddr, nPort);
	if (nRet == 0)
	{
		memset(&m_czIP, 0x00, sizeof(char)*PACKET_SIZE);
		memcpy(m_czIP, czIpAddr, sizeof(char)*strlen(czIpAddr));
		m_nPort = nPort;

		m_bConnected = true;
		m_Thread_Run = true;
		m_thread_Listen = std::thread(&CCMSMESSocket::Run_Listen, this);

	}

	return nRet;
}

int CCMSMESSocket::doConnectClient()
{
	return doConnect(m_czIP, m_nPort);
}

bool CCMSMESSocket::doDisonnect()
{
	int nResult = 0;
	m_Thread_Run = false;


	DWORD	dwStart = GetTickCount();

	while (1)
	{
		if (m_Thread_End == true)	   break;
		if (GetTickCount() - dwStart > 5000)	break;
	}

	closesocket(m_hServer);
	closesocket(m_hClient);

	Sleep(200);
	m_bConnected = false;

	if (m_thread_Listen.joinable())
		m_thread_Listen.detach();

	WSACleanup();
	return true;
}

void CCMSMESSocket::Run_Listen()
{
	char	cBuf[PACKET_SIZE] = {};
	int		nResult = 0;
	//SOCKADDR_IN	tCIntAddr = {};
	struct sockaddr_in	tCIntAddr;
	SYSTEMTIME			SystemTime;
	CString				strCom = _T(",");
	int					nComCount = 0;
	CString				strParseData[10] = {};
	CString				strTrackInData[10] = {};
	DWORD dwStart = 0, dwTimeout = 3 * 60 * 1000;
	CString strRecvMsg = _T("");

	m_Thread_End = false;
	while (m_Thread_Run)
	{
		if (m_bConnected)
		{

			int nCIntSize = sizeof(tCIntAddr);

			if (m_hClient == INVALID_SOCKET)
			{
				m_hClient = accept(m_hServer, (SOCKADDR*)&tCIntAddr, &nCIntSize);
				continue;
			}

			memset(&cBuf, 0x00, sizeof(char)*PACKET_SIZE);
			nResult = recv(m_hClient, cBuf, PACKET_SIZE, 0);
			if (nResult > 0)		//  수신됨
			{
				dwStart = GetTickCount();
				int		nPos = 0;

				strRecvMsg = (LPSTR)(LPCTSTR)cBuf;

				for (int i = 0; i < strRecvMsg.GetLength(); i++)
				{
					AfxExtractSubString(strParseData[i], strRecvMsg, i, ',');
					if (strParseData[i] == "")
						break;
				}
				if (strParseData[2] == "0000")
				{
					if (strParseData[4] == "1")
					{
						m_bOnlineCheck = true;
					}
					else
						m_bOnlineCheck = false;
				}
				else if (strParseData[2] == "0001")
				{
					if (strParseData[4] == "1")
					{
						m_bAlarmCheck = true;
					}
					else
						m_bAlarmCheck = false;
				}
				else if (strParseData[2] == "0002")
				{
					for (int i = 0; i < strParseData[4].GetLength(); i++)
					{
						AfxExtractSubString(strTrackInData[i], strParseData[4], i, '@');
						if (strTrackInData[i] == "")
							break;
					}
					if (strTrackInData[1] == "SUCCESS")
					{
						m_bTrackInCheck = true;
						m_strLotID = strTrackInData[3];
						m_strProdID = strTrackInData[4];
						m_strProCID = strTrackInData[5];
					}

					else
						m_bTrackInCheck = false;
				}
				else if (strParseData[2] == "0003")
				{
					if (strParseData[4] == "1")
					{
						m_bTrackOutCheck = true;
					}
					else
						m_bTrackOutCheck = false;
				}
				//CString		strLog = _T("");
				//strLog.Format(_T("[RECV] %s"), strRecvMsg);
				//gUserLog()->Add_Log(E_LOG_LIST_AUTO, strLog);

			}
			else if (nResult < 0)	// error
			{
				m_bConnected = false;
			}


		}
		else
		{
			ResetEvent(m_hEvent);

			closesocket(m_hServer);
			closesocket(m_hClient);
			WSACleanup();

			if (!doOpen(m_czIP, m_nPort))
				m_bConnected = true;
		}

		Sleep(10);
	}
	m_Thread_End = true;
}

bool CCMSMESSocket::doSend(char* czSend, char& czRecv, bool bWait/* = false*/, DWORD dwWaitTime/* = 5000*/)
{
	bool	bResult = false;
	SYSTEMTIME			SystemTime;

	if (m_hClient)
	{
		send(m_hClient, czSend, (int)strlen(czSend), 0);

		AddLog(ON_SEND_MSG, czSend);

		if (bWait)
		{
			DWORD ret = WaitForSingleObject(m_hEvent, dwWaitTime);

			switch (ret)
			{
			case WAIT_FAILED:		bResult = false;	break;
			case WAIT_ABANDONED:	bResult = false;	break;
			case WAIT_TIMEOUT:		bResult = false;	break;
			default:
				bResult = true;
				memcpy(&czRecv, m_stRecvMsg.recvMsg, sizeof(char)*PACKET_SIZE);
			}
		}
		else
		{
			bResult = true;
		}
	}

	return bResult;
}

bool CCMSMESSocket::doSendCmd(CString strCmd)
{
	bool bRet = true;
	char		czSend[PACKET_SIZE] = { 0x00, };
	char		czRecv[PACKET_SIZE] = { 0x00, };

	for (int i = 0; i < strCmd.GetLength(); i++)		czSend[i] = strCmd.GetAt(i);

	if (isConnected())
		bRet = doSend(czSend, *czRecv);

	return bRet;
}