// AgentListenSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "AgentListenSocket.h"
#include "AutoInspDlg.h"

// CAgentListenSocket

CAgentListenSocket::CAgentListenSocket()
{
	m_pMainDlg =  NULL;
}

CAgentListenSocket::~CAgentListenSocket()
{
}


// CAgentListenSocket 멤버 함수

//-----------------------------------------------------------------------------
//
//	OnAccept
//
//-----------------------------------------------------------------------------
void CAgentListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(m_pMainDlg != NULL)
	{
		m_pMainDlg->AcceptInspConn();
	}

	CSocket::OnAccept(nErrorCode);
}
