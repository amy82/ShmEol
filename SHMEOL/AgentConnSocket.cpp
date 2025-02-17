// AgentConnSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "AgentConnSocket.h"
#include "AutoInspDlg.h"

// CAgentConnSocket

CAgentConnSocket::CAgentConnSocket()
{
	m_pMainDlg = NULL;
	m_bStxState = false;
}

CAgentConnSocket::~CAgentConnSocket()
{
}


// CAgentConnSocket 멤버 함수

//-----------------------------------------------------------------------------
//
//	OnClose
//
//-----------------------------------------------------------------------------
void CAgentConnSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(m_pMainDlg != NULL)
	{
		m_pMainDlg->CloseAAMain();
	}

	CSocket::OnClose(nErrorCode);
}

//-----------------------------------------------------------------------------
//
//	OnReceive
//
//-----------------------------------------------------------------------------
void CAgentConnSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	unsigned char sRecvBuff[SIZE_OF_1K];
	int nRecvLen;

	nRecvLen = this->Receive(sRecvBuff, sizeof(sRecvBuff));
	if(nRecvLen > 0)
	{
		this->PareRecvBuff(sRecvBuff, nRecvLen);
	}

	CSocket::OnReceive(nErrorCode);
}

//-----------------------------------------------------------------------------
//
//	패킷 파싱
//
//-----------------------------------------------------------------------------
void CAgentConnSocket::PareRecvBuff(unsigned char* pRecvBuff, int nRecvLen)
{
	CString sData = _T("");
	int i;

	for(i = 0; i < nRecvLen; i++)
	{
		// STX 안 받은 상태
		if(m_bStxState == false)
		{
			// STX 수신?
			if(/*pRecvBuff[i] == '@' || */pRecvBuff[i] == '#')
			{
				// 패킷 버퍼 초기화
				memset(m_sPacketBuff, 0x00, sizeof(m_sPacketBuff));
				m_nPacketBuffPosi = 0;

				// STX를 패킷 버퍼에 담는다.
				m_sPacketBuff[m_nPacketBuffPosi] = pRecvBuff[i];

				// STX 수신 플래그를 올린다.
				m_bStxState = true;
			}
		}
		// STX 받은 상태
		else
		{
			// 패킷 버퍼 오버플로우 체크
			if(m_nPacketBuffPosi > (sizeof(m_sPacketBuff) - 1))
			{
				m_bStxState = false;
				continue;
			}

			m_nPacketBuffPosi++;
			m_sPacketBuff[m_nPacketBuffPosi] = pRecvBuff[i];

			// ETX 체크
			if(m_sPacketBuff[m_nPacketBuffPosi] == '$')
			{
				sData = CA2T((char*)m_sPacketBuff);
				m_pMainDlg->RecvAAMainData(sData);

				m_bStxState = false;
			}
		}
	}
}
