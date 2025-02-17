// MessageAskDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "MessageAskDlg.h"
#include "afxdialogex.h"


// CMessageAskDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMessageAskDlg, CDialogEx)

CMessageAskDlg::CMessageAskDlg(CString sTitle, CString sMsg, COLORREF bgColor, int nAskCount, TCHAR* pszAsk[], CWnd* pParent /*=NULL*/)
	: CDialogEx(CMessageAskDlg::IDD, pParent)
{
	int nIndex;
	int i;

	m_sTitle = sTitle;
	m_sMsg = sMsg;
	m_bgColor = bgColor;
	m_nAskCount = nAskCount;
	if(m_nAskCount > 4)
		m_nAskCount = 4;

	nIndex = 4 - m_nAskCount;

	for(i = 0; i < 4; i++)
	{
		if(i >= nIndex)
			m_sAnswer[i].Format(_T("%s"), pszAsk[i - nIndex]);
	}
}

CMessageAskDlg::~CMessageAskDlg()
{
}

void CMessageAskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_MESSAGE_ASK_TITLE, m_clColorStaticTitle);
	DDX_Control(pDX, IDC_STATIC_MESSAGE_ASK_MSG, m_clColorStaticMsg);
	DDX_Control(pDX, IDC_BUTTON_MESSAGE_ASK_ANSWER1, m_clColorButtonAnswer[0]);
	DDX_Control(pDX, IDC_BUTTON_MESSAGE_ASK_ANSWER2, m_clColorButtonAnswer[1]);
	DDX_Control(pDX, IDC_BUTTON_MESSAGE_ASK_ANSWER3, m_clColorButtonAnswer[2]);
	DDX_Control(pDX, IDC_BUTTON_MESSAGE_ASK_ANSWER4, m_clColorButtonAnswer[3]);	
}


BEGIN_MESSAGE_MAP(CMessageAskDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()	
	ON_BN_CLICKED(IDC_BUTTON_MESSAGE_ASK_ANSWER1, &CMessageAskDlg::OnBnClickedButtonMessageAskAnswer1)
	ON_BN_CLICKED(IDC_BUTTON_MESSAGE_ASK_ANSWER2, &CMessageAskDlg::OnBnClickedButtonMessageAskAnswer2)
	ON_BN_CLICKED(IDC_BUTTON_MESSAGE_ASK_ANSWER3, &CMessageAskDlg::OnBnClickedButtonMessageAskAnswer3)
	ON_BN_CLICKED(IDC_BUTTON_MESSAGE_ASK_ANSWER4, &CMessageAskDlg::OnBnClickedButtonMessageAskAnswer4)
END_MESSAGE_MAP()


// CMessageAskDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CMessageAskDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	int nIndex;
	int i;

	GetClientRect(rect);

    dc.FillSolidRect(rect, MESSAGE_BG_COLOR);// m_bgColor);
}

//-----------------------------------------------------------------------------
//
//	다이얼로그 초기화
//
//-----------------------------------------------------------------------------
BOOL CMessageAskDlg::OnInitDialog()
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
void CMessageAskDlg::InitCtrl()
{
	int nIndex;
	int i;

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
	m_clColorStaticTitle.Invalidate();
    //
	m_clColorStaticMsg.SetBkColor(m_bgColor);
	m_clColorStaticMsg.SetTextColor(MESSAGE_TXT_COLOR);
	m_clColorStaticMsg.SetFont(&m_clFontMid);
    m_clColorStaticMsg.SetBorder(TRUE);
    m_clColorStaticMsg.SetFontSize(20);
    m_clColorStaticMsg.SetWindowText(m_sMsg);
    m_clColorStaticMsg.SetBkColor(MESSAGE_BG_COLOR);
	m_clColorStaticMsg.Invalidate();
	nIndex = 4 - m_nAskCount;

	for (i = 0; i < 4; i++)
	{
        m_clColorButtonAnswer[i].state = 100;

		if (i >= nIndex)
		{
			m_clColorButtonAnswer[i].SetWindowText(m_sAnswer[i]);
			m_clColorButtonAnswer[i].ShowWindow(SW_SHOW);
		}
		else
		{
			m_clColorButtonAnswer[i].SetWindowText(m_sAnswer[i]);
			m_clColorButtonAnswer[i].ShowWindow(SW_HIDE);
		}		
	}
}

//-----------------------------------------------------------------------------
//
//	STATIC : ANSWER 1
//
//-----------------------------------------------------------------------------
void CMessageAskDlg::OnBnClickedButtonMessageAskAnswer1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(1);
}

//-----------------------------------------------------------------------------
//
//	STATIC : ANSWER 2
//
//-----------------------------------------------------------------------------
void CMessageAskDlg::OnBnClickedButtonMessageAskAnswer2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(2);
}

//-----------------------------------------------------------------------------
//
//	STATIC : ANSWER 3
//
//-----------------------------------------------------------------------------
void CMessageAskDlg::OnBnClickedButtonMessageAskAnswer3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(3);
}

//-----------------------------------------------------------------------------
//
//	STATIC : ANSWER 4
//
//-----------------------------------------------------------------------------
void CMessageAskDlg::OnBnClickedButtonMessageAskAnswer4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(4);
}

//-----------------------------------------------------------------------------
//
//	OnLButtonDown
//
//-----------------------------------------------------------------------------
void CMessageAskDlg::OnLButtonDown(UINT nFlags, CPoint point)
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
BOOL CMessageAskDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


