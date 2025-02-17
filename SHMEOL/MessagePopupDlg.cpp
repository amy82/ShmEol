// MessagePopupDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "MessagePopupDlg.h"
#include "afxdialogex.h"

#define MSG_CLOSE_TIMER			1000
// CMessagePopupDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMessagePopupDlg, CDialogEx)

CMessagePopupDlg::CMessagePopupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMessagePopupDlg::IDD, pParent)
{
	m_sTitle = _T("");
	m_sMsg = _T("");
	m_bgColor = RGB_COLOR_WHITE;
	m_nIndex = 0;
	CloseTime = 0;

	m_brush.CreateSolidBrush(MESSAGE_BG_COLOR);// RGB(255, 255, 200));  // 원하는 색상으로 브러시 생성
}

CMessagePopupDlg::~CMessagePopupDlg()
{
}

void CMessagePopupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_MESSAGE_POPUP_TITLE, m_clColorStaticTitle);
	DDX_Control(pDX, IDC_STATIC_MESSAGE_POPUP_MSG, m_clColorStaticMsg);
	DDX_Control(pDX, IDC_BUTTON_MESSAGE_POPUP_CONFIRM, m_clColorButtonConfirm);

	DDX_Control(pDX, IDC_EDIT_MESSAGE_POPUP_MSG, m_edtMsg);
}


BEGIN_MESSAGE_MAP(CMessagePopupDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()	
	ON_BN_CLICKED(IDC_BUTTON_MESSAGE_POPUP_CONFIRM, &CMessagePopupDlg::OnBnClickedButtonMessagePopupConfirm)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMessagePopupDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CMessagePopupDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	GetClientRect(rect);

	dc.FillSolidRect(rect, m_bgColor);
}

//-----------------------------------------------------------------------------
//
//	다이얼로그 초기화
//
//-----------------------------------------------------------------------------
BOOL CMessagePopupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CMessagePopupDlg::InitCtrl()
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

    ///
	m_clColorStaticMsg.SetTextColor(MESSAGE_TXT_COLOR);
	m_clColorStaticMsg.SetFont(&m_clFontMid);
    m_clColorStaticMsg.SetBorder(TRUE);
    m_clColorStaticMsg.SetFontSize(25);
    m_clColorStaticMsg.SetBkColor(MESSAGE_BG_COLOR);

    m_clColorButtonConfirm.state = 100;


	CFont m_font;
	// 폰트 설정 (Arial, 크기 20)
	m_font.CreatePointFont(160, _T("Arial"));  // 크기 20포인트는 200 단위 사용
	m_edtMsg.SetFont(&m_font);
	m_edtMsg.ModifyStyle(0, ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN);
}

//-----------------------------------------------------------------------------
//
//	팝업 다이얼로그 내용 표시
//
//-----------------------------------------------------------------------------
void CMessagePopupDlg::SetContents(CString sTitle, CString sMsg, COLORREF bgColor, int nIndex)
{
	CRect rect;
	int nSizeX;
	int nSizeY;

	GetClientRect(rect);

	nSizeX = GetSystemMetrics(SM_CXSCREEN);
	nSizeY = GetSystemMetrics(SM_CYSCREEN);

	m_sTitle = sTitle;
	m_sMsg = sMsg;
	m_bgColor = bgColor;
	m_nIndex = nIndex;
	
	m_clColorStaticTitle.SetBkColor(m_bgColor);
	m_clColorStaticTitle.SetWindowText(m_sTitle);

	//m_clColorStaticMsg.SetBkColor(m_bgColor);
	//m_clColorStaticMsg.SetWindowText(m_sMsg);

	m_sMsg.Replace(_T("\n"), _T("\r\n"));
	m_edtMsg.SetWindowTextA(m_sMsg);
	//m_clColorButtonConfirm.ChangeColor(m_bgColor);
			
	rect.top = ((nSizeY - rect.bottom) / 2) + (m_nIndex * 25);
	rect.left = (nSizeX - rect.right) / 2 + (m_nIndex * 25);	

	this->SetWindowPos(NULL,rect.left, rect.top, rect.right, rect.bottom, SWP_NOSIZE);
}

//-----------------------------------------------------------------------------
//
//	버튼 : CONFIRM
//
//-----------------------------------------------------------------------------
void CMessagePopupDlg::OnBnClickedButtonMessagePopupConfirm()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_clDioControl.SetBuzzer(false);
	EndDialog(IDOK);
}

//-----------------------------------------------------------------------------
//
//	OnLButtonDown
//
//-----------------------------------------------------------------------------
void CMessagePopupDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);

	CDialogEx::OnLButtonDown(nFlags, point);
}

//-----------------------------------------------------------------------------
//
//	PreTranslateMessage
//
//-----------------------------------------------------------------------------
BOOL CMessagePopupDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMessagePopupDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nIDEvent == MSG_CLOSE_TIMER)
	{
		CloseTime = 0;
		OnBnClickedButtonMessagePopupConfirm();
		KillTimer(MSG_CLOSE_TIMER);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMessagePopupDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		if (CloseTime > 0)
		{
			SetTimer(MSG_CLOSE_TIMER, CloseTime * 1000, NULL);
		}
	}
	else
	{
		KillTimer(MSG_CLOSE_TIMER);
	}
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


HBRUSH CMessagePopupDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	// 특정 컨트롤 ID에 대해 배경색 변경
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_MESSAGE_POPUP_MSG)  // m_edtMsg와 연결된 컨트롤 ID
	{
		pDC->SetBkColor(MESSAGE_BG_COLOR);// RGB(255, 255, 200));  // 배경색 설정 (연한 노란색)
		return (HBRUSH)m_brush.GetSafeHandle();
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
