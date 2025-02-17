#pragma once
#pragma once
#include "SocketApi.h"

class CCMSMESSocket :
	public CSocketApi
{
public:
	CCMSMESSocket();
	~CCMSMESSocket();

private:
	int		doOpen(const char* czIpAddr, int nPort);




public:
	// 순수 가상 함수
	int				doConnect(const char* czIpAddr, int nPort);
	int			    doConnectClient();
	bool			doDisonnect();
	void			Run_Listen();
	bool			doSend(char* czSend, char& czRecv, bool bWait = false, DWORD dwWaitTime = 5000);
	bool			doSendCmd(CString strCmd);

	virtual void doParsingMsg(CString strMsg) { return; };

	CString			m_strRecvName;
	bool			m_bOnlineCheck;
	bool			m_bTrackInCheck;
	bool			m_bTrackOutCheck;
	bool			m_bAlarmCheck;
	CString			m_strBarcode;
	CString			m_strLotID;
	CString			m_strProdID;
	CString			m_strProCID;
};


