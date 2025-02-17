// MessageInput.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MessageInput.h"
#include "afxdialogex.h"


// CMessageInput 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMessageInput, CDialogEx)

CMessageInput::CMessageInput(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MESSAGE_TYPE1, pParent)
{
	m_nUnit = 0;
	nPopupId = 0;
	editInputReadOnly = false;
	m_bgColor = MESSAGE_BG_COLOR;
	m_brush.CreateSolidBrush(MESSAGE_BG_COLOR);// RGB(255, 255, 200));  // 원하는 색상으로 브러시 생성
}

CMessageInput::~CMessageInput()
{
}

void CMessageInput::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_EDIT_MSG_TEXT, m_edtMsgText);
	DDX_Control(pDX, IDC_STATIC_MESSAGE_TYPE1_TITLE, m_clColorStaticTitle);

	DDX_Control(pDX, IDC_BUTTON_MSG_SEND, m_clColorButtonConfirm);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMessageInput, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MSG_SEND, &CMessageInput::OnBnClickedButtonMsgSend)
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMessageInput 메시지 처리기입니다.

BOOL CMessageInput::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CMessageInput::InitCtrl()
{
	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(24, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	m_clColorStaticTitle.SetTextColor(MESSAGE_TXT_COLOR);
	m_clColorStaticTitle.SetFont(&m_clFontBig);
	m_clColorStaticTitle.SetBorder(TRUE);
	m_clColorStaticTitle.SetFontSize(15);
	m_clColorStaticTitle.SetBkColor(MESSAGE_BG_COLOR);



	CFont m_font;
	// 폰트 설정 (Arial, 크기 20)
	m_font.CreatePointFont(135, _T("맑은 고딕"));  // 크기 20포인트는 200 단위 사용
	m_edtMsgText.SetFont(&m_font);
	m_edtMsgText.ModifyStyle(0, ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN);

}
void CMessageInput::OnBnClickedButtonMsgSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//Send Button

	//S10F1 - Terminal Requeset
	int i = 0;
	CString tmsg;
	m_edtMsgText.GetWindowTextA(tmsg);


	//void CUbiGem::TerminalMessageSendRequest(int itid, CString tmsg)

	g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(OP_RECOGNIZED_TERMINAL_REPORT_10901, tmsg);
	ShowWindow(SW_HIDE);

	bool bPopupShow = false;

	for (i = 0; i < MAX_TERMINAL_COUNT; i++)
	{
		if (m_clTeminalMessageDlg[i] != NULL)
		{
			if (m_clTeminalMessageDlg[i]->IsWindowVisible() == TRUE)
			{
				bPopupShow = true;
				break;
			}
		}
	}
	if (bPopupShow == false)
	{
		g_pCarAABonderDlg->EnableWindow(TRUE);
	}

	tmsg.Empty();



	//아래 부분 Optional 부분
	//if (editInputReadOnly == true)
	//{
	//	g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(OP_RECOGNIZED_TERMINAL_REPORT_10901, tmsg);
	//}
	//else
	//{
	//	//Optional 
	//	//Enter Terminal Message !!!
	//	//g_pCarAABonderDlg->m_clUbiGemDlg.TerminalMessageSendRequest(g_clMesCommunication[m_nUnit].m_dTerminalId, tmsg);
	//}
	
}

void CMessageInput::setEditInput(CString title, int index, CString txt)
{
	//SetWindowTextA(title);
	CString str = _T("");
	str.Format(_T("Terminal Message[%d]"), index);
	m_clColorStaticTitle.SetWindowTextA(str);

	txt.Replace(_T("\n"), _T("\r\n"));
	m_edtMsgText.SetWindowTextA(txt);
	m_edtMsgText.Invalidate();
}
void CMessageInput::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.


	if (bShow)
	{
		g_pCarAABonderDlg->EnableWindow(FALSE);
		this->CenterWindow();
		if (editInputReadOnly)
		{
			m_edtMsgText.SetReadOnly(TRUE);
		}
		else
		{
			m_edtMsgText.SetReadOnly(FALSE);
		}



		CRect rect;
		this->GetWindowRect(&rect);
		int dOffsetX = 40;
		int dOffsetY = 40;
		int newX = rect.left + (dOffsetX * (nPopupId - (MAX_TERMINAL_COUNT / 2)));
		int newY = rect.top + (dOffsetY * (nPopupId - (MAX_TERMINAL_COUNT / 2)));

		// 다이얼로그 위치를 새 좌표로 설정
		this->SetWindowPos(NULL, newX, newY, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);//SWP_NOZORDER
	}
}




BOOL CMessageInput::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CMessageInput::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_MSG_TEXT)  // m_edtMsg와 연결된 컨트롤 ID
	{
		pDC->SetBkColor(MESSAGE_BG_COLOR);// RGB(255, 255, 200));  // 배경색 설정 (연한 노란색)
		return (HBRUSH)m_brush.GetSafeHandle();
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CMessageInput::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	CRect rect;
	GetClientRect(rect);

	dc.FillSolidRect(rect, m_bgColor);
}


void CMessageInput::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	CDialogEx::OnLButtonDown(nFlags, point);
}
