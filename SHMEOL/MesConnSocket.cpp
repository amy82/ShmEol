// MesConnSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "MesConnSocket.h"
#include "AutoInspDlg.h"

#define BCR_STX				0x02
#define BCR_ETX				0x03

#define BCR_CR				0x0d
// CMesConnSocket

CMesConnSocket::CMesConnSocket()
{
	m_pMainDlg = NULL;
	m_bStxState = false;
}

CMesConnSocket::~CMesConnSocket()
{
}


// CMesConnSocket 멤버 함수

//-----------------------------------------------------------------------------
//
//	OnClose
//
//-----------------------------------------------------------------------------
void CMesConnSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// MES_SOCKET = 0, BCR_SOCKET = 0, MAX_SOCKET_TYPE};
	if(m_pMainDlg != NULL)
	{
		if (IDENTITY == MES_SOCKET)
		{
			m_pMainDlg->DisConnectMes();
		}
		else if (IDENTITY == BCR_SOCKET)
		{
		}
		
	}

	CSocket::OnClose(nErrorCode);
}

//-----------------------------------------------------------------------------
//
//	OnReceive
//
//-----------------------------------------------------------------------------
void CMesConnSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	unsigned char sRecvBuff[SIZE_OF_1K];
	int nRecvLen;

	nRecvLen = this->Receive(sRecvBuff, sizeof(sRecvBuff));
	if(nRecvLen > 0)
	{
		//m_bStxState = false;
		if (IDENTITY == MES_SOCKET)
		{
			this->ParseRecvBuff(sRecvBuff, nRecvLen);
		}
		else if (IDENTITY == BCR_SOCKET)
		{
			this->ParseRecvBcrBuff(sRecvBuff, nRecvLen);
		}
		
	}

	CSocket::OnReceive(nErrorCode);
} 

//-----------------------------------------------------------------------------
//
//	패킷 파싱
//
//-----------------------------------------------------------------------------
void CMesConnSocket::ParseRecvBuff(unsigned char* pRecvBuff, int nRecvLen)
{
	CString sData = _T("");
	int i;

	for (i = 0; i < nRecvLen; i++)
	{
		// STX 안받은 상태
		if (m_bStxState == false)
		{
			// STX 수신?
			if(pRecvBuff[i] == 'H')
			{
				memset(m_sPacketBuff, 0x00, sizeof(m_sPacketBuff));
				m_nPacketBuffPosi = 0;

				m_sPacketBuff[m_nPacketBuffPosi] = pRecvBuff[i];

				m_bStxState = true;
			}
		}
		else
		{
			if (m_nPacketBuffPosi > (sizeof(m_sPacketBuff) - 1))
			{
				m_bStxState = false;
				continue;
			}

			m_nPacketBuffPosi++;
			m_sPacketBuff[m_nPacketBuffPosi] = pRecvBuff[i]; 

			//if (m_sPacketBuff[m_nPacketBuffPosi] == 'T') = mes일때
			//H*B221105F1700318*1*T
			//H*C221305T1800007*1*T
			if ((m_sPacketBuff[m_nPacketBuffPosi] == 'T')&&m_nPacketBuffPosi > 10)//8)
			{
				sData = (char*)m_sPacketBuff;

				this->ProcessPacket(sData);
				
				m_bStxState = false;
			}
		}
	}
}

//-----------------------------------------------------------------------------
//
//	패킷 파싱
//
//-----------------------------------------------------------------------------
void CMesConnSocket::ParseRecvBcrBuff(unsigned char* pRecvBuff, int nRecvLen)
{
	CString sData = _T("");
	int i;

	for (i = 0; i < nRecvLen; i++)
	{
		// STX 안받은 상태
		if (m_bStxState == false)
		{
			// STX 수신?
			if (pRecvBuff[i] == BCR_STX)
			{
				memset(m_sPacketBuff, 0x00, sizeof(m_sPacketBuff));
				m_nPacketBuffPosi = 0;

				m_sPacketBuff[m_nPacketBuffPosi] = pRecvBuff[i];

				m_bStxState = true;
			}
		}
		else
		{
			if (m_nPacketBuffPosi > (sizeof(m_sPacketBuff) - 1))
			{
				m_bStxState = false;
				continue;
			}

			m_nPacketBuffPosi++;
			m_sPacketBuff[m_nPacketBuffPosi] = pRecvBuff[i];

			if (m_sPacketBuff[m_nPacketBuffPosi] == BCR_ETX)
			{
				sData = (char*)m_sPacketBuff;
				sData = sData.Mid(1, m_nPacketBuffPosi - 1);
				this->ProcessPacket(sData);

				m_bStxState = false;
			}
		}
	}
}
//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CMesConnSocket::ProcessPacket(CString sData)
{	
	CString sToken = _T("");
	CString sMsg = _T("");
	TCHAR szLog[SIZE_OF_1K];
	// 수신 로그
	AddLog((TCHAR*)(LPCTSTR)sData, 0, UNIT_AA1, false);

	if (sData.Left(2) == _T("H*"))
	{
		AfxExtractSubString(sToken, sData, 1, _T('*'));
		AddLog((TCHAR*)(LPCTSTR)sToken, 0, UNIT_AA1, false);
		//
		TCHAR m_szLotTemp[SIZE_OF_100BYTE];
		_stprintf_s(m_szLotTemp, _T("%s"), (TCHAR*)(LPCTSTR)sToken);
		g_clMesCommunication[UNIT_AA1].m_sMesLotID.Format(_T("%s"), m_szLotTemp);//recv mes
		
		AfxExtractSubString(sToken, sData, 2, _T('*'));
		//
		g_clMesCommunication[UNIT_AA1].m_nMesCnt = _ttoi((TCHAR*)(LPCTSTR)sToken);

		g_clTaskWork[UNIT_AA1].m_bPcbSocketIF[PCB_MES_ACK] = true;	//착공
		
		g_pCarAABonderDlg->m_clColorStaticBcrVal[UNIT_AA1].SetWindowText(g_clMesCommunication[UNIT_AA1].m_sMesLotID);
		//
	}
	//else
	//{
	//	g_clTaskWork.m_clTransferTask.m_bBcrRead = true;
	//	_stprintf_s(g_clTaskWork.m_clTransferTask.m_szLoadBcr, SIZE_OF_100BYTE, _T("%s"), (TCHAR*)(LPCTSTR)sData);
	//	_stprintf_s(szLog, SIZE_OF_100BYTE, _T("BCR - %s"), (TCHAR*)(LPCTSTR)g_clTaskWork.m_clTransferTask.m_szLoadBcr);
	//	AddLog(szLog, 0, false, TRANSFER_UNIT);
	//	m_pMainDlg->ShowBarcode(g_clTaskWork.m_clTransferTask.m_szLoadBcr);
	//	//
	//	//
	//	char szBuff[SIZE_OF_100BYTE];
	//	if (g_clSysData.m_nMesUse == 1)	//m_clSerialThread.m_bMesBcrOpen == true && 
	//	{
	//		//Mes사용시 가상포트로 보낸후 mes에서 리턴받고 AA로 보낸다.
	//		sprintf_s(szBuff, SIZE_OF_100BYTE, "%s\r", g_clTaskWork.m_clTransferTask.m_szLoadBcr);
	//		m_pMainDlg->m_clSerialThread.SendMesBcrReadSet(szBuff);
	//		_stprintf_s(szLog, SIZE_OF_100BYTE, _T("Send to 가상 Mes - %s"), (TCHAR*)(LPCTSTR)g_clTaskWork.m_clTransferTask.m_szLoadBcr);
	//		AddLog(szLog, 0, false, TRANSFER_UNIT);
	//		g_clTaskWork.m_bRecvMesBcr = false;
	//	}
	//	m_pMainDlg->m_clManualDlg.m_clTransferDlg.ShowRecvBcr();
	//	//else if (g_clSysData.m_nMesUse == 0)
	//	//{
	//	//	//Mes 미사용시 제품 투입시 AA로 보낸다
	//	//	sMsg.Format(_T("#AA%d@PCB_BCR&%s,%d,%d$"), AA_UNI1 + 1, g_clTaskWork.m_clTransferTask.m_szLoadBcr, 0, 0);
	//	//	m_pMainDlg->SendPacketToAgent(AA_UNI1, sMsg);
	//	//}
	//}
}