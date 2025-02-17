// InspConnSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "InspConnSocket.h"
#include "AutoInspDlg.h"

// CInspConnSocket

CInspConnSocket::CInspConnSocket()
{
	m_pMainDlg = NULL;
	m_bStxState = false;
}

CInspConnSocket::~CInspConnSocket()
{
}


// CInspConnSocket 멤버 함수

//-----------------------------------------------------------------------------
//
//	OnClose
//
//-----------------------------------------------------------------------------
void CInspConnSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(m_pMainDlg != NULL)
	{
		m_pMainDlg->CloseInspConn(this, false);
	}

	CSocket::OnClose(nErrorCode);
}

//-----------------------------------------------------------------------------
//
//	OnReceive
//
//-----------------------------------------------------------------------------
void CInspConnSocket::OnReceive(int nErrorCode)
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
//	패킷 버퍼 파싱
//
//-----------------------------------------------------------------------------
void CInspConnSocket::PareRecvBuff(unsigned char* pRecvBuff, int nRecvLen)
{
	CString sPacket = _T("");
	int i;

	for(i = 0; i < nRecvLen; i++)
	{
		// STX 안받은 상태
		if(m_bStxState == false)
		{
			if(pRecvBuff[i] == '#')
			{
				m_nPacketBuffPosi = 0;
				memset(m_sPacketBuff, 0x00, sizeof(m_sPacketBuff));

				m_sPacketBuff[m_nPacketBuffPosi] = pRecvBuff[i];

				m_bStxState = true;
			}
		}
		// STX 받은 상태
		else
		{
			// 패킷 버퍼 오버플로우 검사
			if(m_nPacketBuffPosi >= (sizeof(m_sPacketBuff) - 1))
			{
				m_bStxState = false;
				continue;
			}

			m_nPacketBuffPosi++;
			m_sPacketBuff[m_nPacketBuffPosi] = pRecvBuff[i];

			// ETX 검사
			if(m_sPacketBuff[m_nPacketBuffPosi] == '@')
			{
				sPacket = CA2T((char*)m_sPacketBuff);
				g_pCarAABonderDlg->ProcessInspPacket(sPacket);

				m_bStxState = false;
			}
		}
	}
}