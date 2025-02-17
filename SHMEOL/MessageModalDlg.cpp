// MessageModalDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "MessageModalDlg.h"
#include "afxdialogex.h"


// CMessageModalDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMessageModalDlg, CDialogEx)

CMessageModalDlg::CMessageModalDlg(CString sTitle, CString sMsg, COLORREF bgColor, CString sYesBtn, CString sNoBtn, CWnd* pParent /*=NULL*/)
	: CDialogEx(CMessageModalDlg::IDD, pParent)
{
	m_sTitle = sTitle;
	m_sMsg = sMsg;
	m_bgColor = bgColor;
	m_sLeftBtnName = sYesBtn;
	m_sRightBtnName = sNoBtn;
	m_brushEdit.CreateSolidBrush(MESSAGE_BG_COLOR);
}

CMessageModalDlg::~CMessageModalDlg()
{
}

void CMessageModalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_MESSAGE_MODAL_TITLE, m_clColorStaticTitle);
	DDX_Control(pDX, IDC_STATIC_MESSAGE_MODAL_MSG, m_clColorStaticMsg);	
	DDX_Control(pDX, IDC_BUTTON_MESSAGE_MODAL_YES, m_clColorButtonYes);
	DDX_Control(pDX, IDC_BUTTON_MESSAGE_MODAL_NO, m_clColorButtonNo);


	DDX_Control(pDX, IDC_EDIT_MESSAGE_MODAL_MSG, m_edtModalMsg);
}


BEGIN_MESSAGE_MAP(CMessageModalDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()	
	ON_BN_CLICKED(IDC_BUTTON_MESSAGE_MODAL_YES, &CMessageModalDlg::OnBnClickedButtonMessageModalYes)
	ON_BN_CLICKED(IDC_BUTTON_MESSAGE_MODAL_NO, &CMessageModalDlg::OnBnClickedButtonMessageModalNo)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMessageModalDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CMessageModalDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	GetClientRect(rect);

    dc.FillSolidRect(rect, MESSAGE_BG_COLOR);// m_bgColor);
}

//-----------------------------------------------------------------------------
//
//	다이얼로그 초기화
//
//-----------------------------------------------------------------------------
BOOL CMessageModalDlg::OnInitDialog()
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
void CMessageModalDlg::InitCtrl()
{
	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(24, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	m_clColorStaticTitle.SetBkColor(m_bgColor);
	m_clColorStaticTitle.SetTextColor(MESSAGE_TXT_COLOR);
	m_clColorStaticTitle.SetFont(&m_clFontBig);
	m_clColorStaticTitle.SetWindowText(m_sTitle);
    m_clColorStaticTitle.SetBorder(TRUE);
    m_clColorStaticTitle.SetFontSize(15);
    m_clColorStaticTitle.SetBkColor(MESSAGE_BG_COLOR);

	m_clColorStaticMsg.SetBkColor(m_bgColor);
	m_clColorStaticMsg.SetTextColor(MESSAGE_TXT_COLOR);
	m_clColorStaticMsg.SetFont(&m_clFontMid);
    m_clColorStaticMsg.SetBorder(TRUE);
    m_clColorStaticMsg.SetFontSize(27);
   // m_clColorStaticMsg.SetWindowText(m_sMsg);
    m_clColorStaticMsg.SetBkColor(MESSAGE_BG_COLOR);
    

    m_clColorButtonYes.state = 100;
    m_clColorButtonNo.state = 100;
	//m_clColorButtonYes.ChangeColor(m_bgColor);
	//m_clColorButtonNo.ChangeColor(m_bgColor);

	CFont m_font;
	// 폰트 설정 (Arial, 크기 20)
	m_font.CreatePointFont(135, _T("맑은 고딕"));  // 크기 20포인트는 200 단위 사용
	m_edtModalMsg.SetFont(&m_font);
	m_edtModalMsg.ModifyStyle(0, ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN);
	//m_edtModalMsg.col


	m_clColorButtonYes.SetWindowTextA(m_sLeftBtnName);
	m_clColorButtonNo.SetWindowTextA(m_sRightBtnName);
	m_clColorButtonYes.Invalidate();
	m_clColorButtonNo.Invalidate();


	m_sMsg.Replace(_T("\n"), _T("\r\n"));
	m_edtModalMsg.SetWindowText(m_sMsg);
	m_edtModalMsg.Invalidate();






}

//-----------------------------------------------------------------------------
//
//	버튼 : YES
//
//-----------------------------------------------------------------------------
void CMessageModalDlg::OnBnClickedButtonMessageModalYes()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(IDYES);
}

//-----------------------------------------------------------------------------
//
//	버튼 : NO
//
//-----------------------------------------------------------------------------
void CMessageModalDlg::OnBnClickedButtonMessageModalNo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(IDNO);
}

//-----------------------------------------------------------------------------
//
//	OnLButtonDown
//
//-----------------------------------------------------------------------------
void CMessageModalDlg::OnLButtonDown(UINT nFlags, CPoint point)
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
BOOL CMessageModalDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}




HBRUSH CMessageModalDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_MESSAGE_MODAL_MSG
		)
	{
		pDC->SetTextColor(RGB_COLOR_BLACK);
		pDC->SetBkColor(MESSAGE_BG_COLOR);// RGB(100, 100, 100));
		pDC->SetBkMode(TRANSPARENT);

		return (HBRUSH)m_brushEdit;
		//return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
