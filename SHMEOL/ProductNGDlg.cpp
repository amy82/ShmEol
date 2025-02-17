// ProductNG.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "ProductNGDlg.h"
#include "afxdialogex.h"

// CProductNG

IMPLEMENT_DYNAMIC(CProductNGDlg, CDialogEx)

CProductNGDlg::CProductNGDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProductNGDlg::IDD, pParent)
{
	m_nSelectList = 0;
	m_nUnit = UNIT_AA1;
}

CProductNGDlg::~CProductNGDlg()
{
}

void CProductNGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NG_TOP_BAR, m_clColorStaticTopBar);
	DDX_Control(pDX, IDC_STATIC_NG_NAME, m_clColorStaticNGName);
	DDX_Control(pDX, IDC_BUTTON_NG_RETRY, m_clColorButtonNGRetry);
	DDX_Control(pDX, IDC_BUTTON_NG_OK, m_clColorButtonNGOk);
	DDX_Control(pDX, IDC_BUTTON_NG_PCB, m_clColorButtonNGPcb);
	DDX_Control(pDX, IDC_BUTTON_NG_PRODUCT, m_clColorButtonNGProduct);
	DDX_Control(pDX, IDC_BUTTON_NG_CHECK, m_clColorButtonNGCheck);
	DDX_Control(pDX, IDC_BUTTON_NG_CANCEL, m_clColorButtonNGCancel);
	DDX_Control(pDX, IDC_LIST_NG_LIST, m_clListCtrlNG);
}

BEGIN_MESSAGE_MAP(CProductNGDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_NG_CANCEL, &CProductNGDlg::OnBnClickedButtonNgCancel)
	ON_BN_CLICKED(IDC_BUTTON_NG_CHECK, &CProductNGDlg::OnBnClickedButtonNgCheck)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_NG_LIST, &CProductNGDlg::OnLvnItemchangedListNgList)
END_MESSAGE_MAP()



// CProductNG 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CProductNGDlg::OnPaint()
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
BOOL CProductNGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	this->CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CProductNGDlg::InitCtrl()
{
	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	m_clColorStaticTopBar.SetBkColor(RGB_COLOR_BLACK);
	m_clColorStaticTopBar.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticTopBar.SetFont(&m_clFontMid);

	m_clColorStaticNGName.SetBkColor(RGB_DLG_BG);
	m_clColorStaticNGName.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticNGName.SetFont(&m_clFontMid);


	m_clListCtrlNG.ModifyStyle(LVS_OWNERDRAWFIXED, 0, 0);
	m_clListCtrlNG.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_clListCtrlNG.InsertColumn(0, _T("번호"), LVCFMT_CENTER, 50, -1);
	m_clListCtrlNG.InsertColumn(1, _T("NG 내용"), LVCFMT_CENTER, 272, -1);
	m_clListCtrlNG.DeleteAllItems();
	m_clListCtrlNG.SetFont(&m_clFontSmall);

	TCHAR* szNGList[] = {_T("해상력 불량"), _T("이물 불량")/*, _T("MES 불량"), _T("EPOXY 불량")*/};
	int i;
	CString cStr;
	//for (i = 0; i < 4; i++)
	for (i = 0; i < 2; i++)
	{
		cStr.Format(_T("%d"), i+1);
		m_clListCtrlNG.InsertItem(i, cStr);
		m_clListCtrlNG.SetItem(i, 1, LVIF_TEXT, szNGList[i], 0, 0, 0, NULL);
	}
}

//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CProductNGDlg::SetUnit(int nUnit)
{
	TCHAR szTitle[SIZE_OF_100BYTE];

	if(m_nUnit != nUnit)
	{
		m_nUnit = nUnit;

		_stprintf_s(szTitle, SIZE_OF_100BYTE, _T("[INSP #%d] NG LIST"), m_nUnit + 1);
		GetDlgItem(IDC_STATIC_NG_TOP_BAR)->SetWindowText(szTitle);
	}

	m_nUnit = nUnit;
}

void CProductNGDlg::OnLvnItemchangedListNgList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	CString sMsg = _T("");

	m_nSelectList = pNMLV->iItem + 1;

	if (m_nSelectList == 1)
	{
		sMsg.Format(_T(" 선택 : 해상력 불량"));
		m_clColorStaticNGName.SetWindowText(sMsg);
	}
	else if (m_nSelectList == 2)
	{
		sMsg.Format(_T(" 선택 : 이물 불량"));
		m_clColorStaticNGName.SetWindowText(sMsg);
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : 확인
//
//-----------------------------------------------------------------------------
void CProductNGDlg::OnBnClickedButtonNgCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];

	if (m_nSelectList == 1)
	{
		g_clMesCommunication[m_nUnit].m_nMesStainResult = 1;
		g_clMesCommunication[m_nUnit].m_nMesDefectResult[1] = 1;
	}
	else if (m_nSelectList == 2)
	{
		g_clMesCommunication[m_nUnit].m_nMesStainResult = 0;
		g_clMesCommunication[m_nUnit].m_nMesDefectResult[1] = 0;
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] NG 내용을 선택해 주세요."));
		AddLog(szLog, 1, m_nUnit, false);
		return;
	}

	g_clTaskWork[m_nUnit].m_nEmission = 2;
	g_clTaskWork[m_nUnit].SaveData();
	g_pCarAABonderDlg->ShowOkNgState(m_nUnit , g_clTaskWork[m_nUnit].m_nEmission);

	m_nSelectList = 0;
	ShowWindow(SW_HIDE);
}

//-----------------------------------------------------------------------------
//
//	버튼 : 취소
//
//-----------------------------------------------------------------------------
void CProductNGDlg::OnBnClickedButtonNgCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
}

//-----------------------------------------------------------------------------
//
//	OnShowWindow
//
//-----------------------------------------------------------------------------
void CProductNGDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

}

//-----------------------------------------------------------------------------
//
//	PreTranslateMessage
//
//-----------------------------------------------------------------------------
BOOL CProductNGDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		
	}

	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
