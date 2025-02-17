#pragma once
#pragma once

#include <thread>
#include <WinSock2.h>
#include <Ws2tcpip.h>

#include <thread>

#pragma comment(lib, "ws2_32")
//#pragma comment(lib, "wsock32")

// Alarm code
#define ERROR_WRONG_PORT			10000


// define value

//
#define	ON_SEND_MSG					 2
#define	ON_RECV_MSG					 1
#define ON_DISCONNECT				-1
#define PACKET_SIZE		8192

#define MAX_STR_VALUE	20


class ParseCString
{
public:
	ParseCString(int nMaxFindCount = MAX_STR_VALUE)
	{
		m_nMaxFindCnt = nMaxFindCount;
		m_pStrValue = new CString[nMaxFindCount];
		m_nFindCnt = 0;
		for (int i = 0; i < nMaxFindCount; i++)
		{
			m_pStrValue[i].Empty();
		}
	};
	~ParseCString()
	{
		for (int i = 0; i < m_nMaxFindCnt; i++)
			delete[] m_pStrValue[i];
	};

private:
	CString 	*m_pStrValue;
	int			m_nMaxFindCnt;
	int			m_nFindCnt;

public:
	bool		Parse(CString strCmd, CString Delimeter, int * pnCnt);
	CString		GetResult(int n);

};

typedef enum _E_SOCKET_LIST
{
	E_SOCKET_LIST_INVALID = -1,

	E_SOCKET_LIST_IPADDR,
	E_SOCKET_LIST_PORT,

	E_SOCKET_LIST_MAX
}_E_SOCKET_LIST;

typedef struct _ST_RECV_MSG_INFO
{
	SYSTEMTIME		systemTime;
	char			recvMsg[PACKET_SIZE];

	_ST_RECV_MSG_INFO()
	{
		ZeroMemory(this, sizeof(*this));
	}
}_ST_RECV_MSG_INFO;


class CSocketApi
{
public:
	CSocketApi();
	~CSocketApi();

protected:
	bool				m_bConnected = false;

	char				m_czIP[PACKET_SIZE];
	int					m_nPort;

	WSADATA				m_wsaData;

	SOCKET				m_hServer;
	SOCKET				m_hClient;

	HANDLE				m_hEvent = NULL;
	bool				m_Thread_Run;
	bool				m_Thread_End;

	std::thread			m_thread_Listen;


	_ST_RECV_MSG_INFO	m_stRecvMsg;

public:
	bool				isConnected() { return m_bConnected; }

public:

	//  pure virtual function
	virtual int			doConnect(const char* czIpAddr, int nPort) = 0;
	virtual bool		doDisonnect() = 0;
	virtual void		Run_Listen() = 0;

	virtual bool		doSend(char* czSend, char& czRecv, bool bWait = false, DWORD dwWaitTime = 5000) = 0;

	virtual void		AddLog(int nTxRx, char* czSend) { return; };
	virtual void		AddLog(int nTxRx, CString& strRx) { return; };

};

