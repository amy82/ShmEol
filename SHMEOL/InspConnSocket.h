#pragma once

// CInspConnSocket 명령 대상입니다.
class CAutoInspDlg;

class CInspConnSocket : public CSocket
{
public:
	CInspConnSocket();
	virtual ~CInspConnSocket();

	void SetMainDlgPtr(CAutoInspDlg* pDlg){ m_pMainDlg = pDlg;}

private:
	void PareRecvBuff(unsigned char* pRecvBuff, int nRecvLen);

private:
    CAutoInspDlg* m_pMainDlg;

	unsigned char m_sPacketBuff[SIZE_OF_1K];
	int m_nPacketBuffPosi;
	bool m_bStxState;
public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


