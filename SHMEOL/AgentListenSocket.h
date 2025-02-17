#pragma once

// CAgentListenSocket 명령 대상입니다.
class CAutoInspDlg;

class CAgentListenSocket : public CSocket
{
public:
	CAgentListenSocket();
	virtual ~CAgentListenSocket();

public:
	void SetMainDlgPtr(CAutoInspDlg* pDlg){ m_pMainDlg = pDlg;}

private:
    CAutoInspDlg* m_pMainDlg;

public:
	virtual void OnAccept(int nErrorCode);
};


