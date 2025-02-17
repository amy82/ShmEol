// UpdateHistoryDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "UpdateHistoryDlg.h"
#include "afxdialogex.h"

#define MAX_ROW_COUNT			30

// CUpdateHistoryDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUpdateHistoryDlg, CDialogEx)

CUpdateHistoryDlg::CUpdateHistoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpdateHistoryDlg::IDD, pParent)
{

}

CUpdateHistoryDlg::~CUpdateHistoryDlg()
{
}

void CUpdateHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_UPDATE_HISTORY, m_clColorStaticUpdateHistory);
	DDX_Control(pDX, IDC_BUTTON_UPDATE_HISTORY_CLOSE, m_clColorButtonClose);
}


BEGIN_MESSAGE_MAP(CUpdateHistoryDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_HISTORY_CLOSE, &CUpdateHistoryDlg::OnBnClickedButtonUpdateHistoryClose)
END_MESSAGE_MAP()


// CUpdateHistoryDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CUpdateHistoryDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;

	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB_DLG_BG);
}

//-----------------------------------------------------------------------------
//
//	다이얼로그 초기화
//
//-----------------------------------------------------------------------------
BOOL CUpdateHistoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	// 그리드 컨트롤 초기화
	this->InitGridCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CUpdateHistoryDlg::InitCtrl()
{
	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	m_clColorStaticUpdateHistory.SetBkColor(RGB_CTRL_BG);
	m_clColorStaticUpdateHistory.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticUpdateHistory.SetFont(&m_clFontBig);


}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CUpdateHistoryDlg::InitGridCtrl()
{
	CRect rect;
	int i, j;

	GetDlgItem(IDC_STATIC_UPDATE_HISTORY_GRID_CONTENTS)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridCtrlUpdateContents.Create(rect, this, IDC_STATIC_UPDATE_HISTORY_GRID_CONTENTS, WS_TABSTOP | WS_VISIBLE);

	m_clGridCtrlUpdateContents.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridCtrlUpdateContents.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridCtrlUpdateContents.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridCtrlUpdateContents.SetReference_Setting();
	m_clGridCtrlUpdateContents.EnableSelection(FALSE);
	m_clGridCtrlUpdateContents.SetRowCount(MAX_ROW_COUNT + 1);
	m_clGridCtrlUpdateContents.SetColumnCount(4);
	m_clGridCtrlUpdateContents.SetFixedRowCount(1);
	m_clGridCtrlUpdateContents.SetFixedColumnCount(1);

	m_clGridCtrlUpdateContents.SetItemText(0, 0, _T("NO"));
	m_clGridCtrlUpdateContents.SetItemText(0, 1, _T("VERSION"));
	m_clGridCtrlUpdateContents.SetItemText(0, 2, _T("DATE"));
	m_clGridCtrlUpdateContents.SetItemText(0, 3, _T("UPDATE CONTENTS"));

	for (i = 0; i < MAX_ROW_COUNT + 1; i++)
	{
		m_clGridCtrlUpdateContents.SetRowHeight(i, 27);
		m_clGridCtrlUpdateContents.SetItemText(i + 1, 0, i + 1);

		for (j = 0; j < 4; j++)
		{
			if (i == 0)
			{
				switch(j)
				{
				case 0:	m_clGridCtrlUpdateContents.SetColumnWidth(j, 60);	break;
				case 1: m_clGridCtrlUpdateContents.SetColumnWidth(j, 120);	break;
				case 2:	m_clGridCtrlUpdateContents.SetColumnWidth(j, 120);	break;
				case 3: m_clGridCtrlUpdateContents.SetColumnWidth(j, 630);	break;
				}

				m_clGridCtrlUpdateContents.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				//m_clGridSfrSpec.SetItemText(i, j, pszCol[j]);
			}
			else
			{
				if(j == 3)
					m_clGridCtrlUpdateContents.SetItemFormat(i, j, DT_VCENTER);
				else
					m_clGridCtrlUpdateContents.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
	}
	
	m_clGridCtrlUpdateContents.SetItemText(1, 1, _T("VER.1.01"));
	m_clGridCtrlUpdateContents.SetItemText(1, 2, _T("2018-10-01"));
	m_clGridCtrlUpdateContents.SetItemText(1, 3, _T("SENSOR ALIGN 실패 시 PCB GRIP 후진/전진 추가"));
	
	m_clGridCtrlUpdateContents.SetItemText(2, 1, _T("VER.1.0"));
	m_clGridCtrlUpdateContents.SetItemText(2, 2, _T("2018-09-01"));
	m_clGridCtrlUpdateContents.SetItemText(2, 3, _T("최초 개발 및 배포"));
	
}

//-----------------------------------------------------------------------------
//
//	버튼 : CLOSE
//
//-----------------------------------------------------------------------------
void CUpdateHistoryDlg::OnBnClickedButtonUpdateHistoryClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
}

//-----------------------------------------------------------------------------
//
//	PreTranslateMessage
//
//-----------------------------------------------------------------------------
BOOL CUpdateHistoryDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.


	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
