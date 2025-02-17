// CcdSfrSpecDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "CcdIrFilterSpecDlg.h"
#include "afxdialogex.h"


// CCcdIrFilterSpecDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCcdIrFilterSpecDlg, CDialogEx)

CCcdIrFilterSpecDlg::CCcdIrFilterSpecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCcdIrFilterSpecDlg::IDD, pParent)
{
	m_nUnit = UNIT_AA1;
}

CCcdIrFilterSpecDlg::~CCcdIrFilterSpecDlg()
{
}

void CCcdIrFilterSpecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_CCD_ROTATION, m_clColorStaticHRotation);
	DDX_Control(pDX, IDC_STATIC_CCD_ROTATION_VAL, m_clColorStaticHRotationVal);
	


	DDX_Control(pDX, IDC_BUTTON_CCD_SFR_SPEC_SAVE, m_clColorButtonSave);
	DDX_Control(pDX, IDC_BUTTON_CCD_SFR_SPEC_CLOSE, m_clColorButtonClose);
}

BEGIN_MESSAGE_MAP(CCcdIrFilterSpecDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_IRFILTER_GRID_SPEC, &CCcdIrFilterSpecDlg::OnNMDblClickedIrFilterSpec)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_SAVE, &CCcdIrFilterSpecDlg::OnBnClickedButtonCcdIrFilterSpecSave)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_CLOSE, &CCcdIrFilterSpecDlg::OnBnClickedButtonCcdIrFilterSpecClose)
END_MESSAGE_MAP()


// CCcdIrFilterSpecDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CCcdIrFilterSpecDlg::OnPaint()
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
BOOL CCcdIrFilterSpecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	// 그리드 초기화
	this->InitIrFilterGridCtrl();
	this->CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdIrFilterSpecDlg::InitCtrl()
{
	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	m_clColorStaticHRotation.SetBkColor(RGB_DLG_BG);
	m_clColorStaticHRotation.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticHRotation.SetFont(&m_clFontSmall);
	
	m_clColorStaticHRotationVal.SetBkColor(RGB_COLOR_WHITE).SetFont(&m_clFontMid);


}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdIrFilterSpecDlg::InitIrFilterGridCtrl()
{
	TCHAR* pszRow[] = { _T("") ,
		_T("dMinThreshold"), _T("dMaxThreshold"), _T("dROIVarThreshold"),
		_T("nRoiLeft"), _T("nRoiTop"), 
		_T("nRoiRight"), _T("nRoiBottom"),
		_T("dFullBrightAvgMin"), _T("dFullBrightAvgMax"),
		_T("dRoiBrightAvgMin"), _T("dRoiBrightAvgMax"),
		_T("dRoiBrightVarMin"), _T("dRoiBrightVarMax")

	};
	
	TCHAR* pszCol[] = { _T("IR"), _T("spec") };

	CRect rect;
	int i, j;
	int DLG = IDC_STATIC_CCD_IRFILTER_GRID_SPEC;

	CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	int SpecRow = g_Ircount + 1;// IrFilterMaxCount;//아래
	int SpecCol = 2;//옆
	int margin = 4;
	int gridHeight = 25;
	int gridWidth1 = 180;
	int gridWidth2 = 110;
	int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + margin;
	rect.bottom = (gridHeight*SpecRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


	GetDlgItem(DLG)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridIrFilterSpec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridIrFilterSpec.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridIrFilterSpec.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridIrFilterSpec.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridIrFilterSpec.SetReference_Setting();
	m_clGridIrFilterSpec.EnableSelection(FALSE);
	m_clGridIrFilterSpec.SetRowCount(SpecRow);
	m_clGridIrFilterSpec.SetColumnCount(SpecCol);
	m_clGridIrFilterSpec.SetFixedRowCount(1);
	m_clGridIrFilterSpec.SetFixedColumnCount(1);

	for (i = 0; i < SpecRow; i++)
	{
		m_clGridIrFilterSpec.SetRowHeight(i, gridHeight);
		m_clGridIrFilterSpec.SetItemText(i, 0, pszRow[i]);

		for (j = 0; j < SpecCol; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridIrFilterSpec.SetColumnWidth(j, gridWidth1);
				}
				else
				{
					m_clGridIrFilterSpec.SetColumnWidth(j, gridWidth2);
				}

				m_clGridIrFilterSpec.SetItemText(i, j, pszCol[j]);
			}

			m_clGridIrFilterSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}
//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CCcdIrFilterSpecDlg::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}

//-----------------------------------------------------------------------------
//
//	OnShowWindow
//
//-----------------------------------------------------------------------------
void CCcdIrFilterSpecDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
		this->ShowIrFilterSpec();
	}
}

//-----------------------------------------------------------------------------
//
//	SATURATION SPEC 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdIrFilterSpecDlg::ShowIrFilterSpec()
{
	TCHAR szData[SIZE_OF_100BYTE];
	int i = 0;

   
	for (i = 0; i < g_Ircount; i++)
	{
		m_clGridIrFilterSpec.SetItemText(i + 1, 1, g_clModelData[m_nUnit].m_IrFilterSpec[i],3);
	}

	m_clGridIrFilterSpec.Invalidate();
}

//-----------------------------------------------------------------------------
//
//	버튼 : SAVE
//
//-----------------------------------------------------------------------------
void CCcdIrFilterSpecDlg::OnBnClickedButtonCcdIrFilterSpecSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("자동 운전 중 사용불가합니다."), RGB_COLOR_RED);
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("일시 정지 중 사용불가합니다."), RGB_COLOR_RED);
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_ShowMsgModal(_T("확인"), _T("IR FILTER SPEC 데이터를 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
		return;

	this->GetIrFilterSpec();

	//g_clSysData.Save();
	//g_clMandoSfrSpec[m_nUnit].Save();
    g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);
	g_clModelData[m_nUnit].AcmisDataSave(g_clSysData.m_szModelName);
	AddLog(_T("[INFO] IR FILTER SPEC 저장"), 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	SFR 데이터 -> 메모리에 저장
//
//-----------------------------------------------------------------------------
void CCcdIrFilterSpecDlg::GetIrFilterSpec()
{
	CString sData = _T("");
	int i;

	for (i = 0; i < g_Ircount; i++)
	{
		sData = m_clGridIrFilterSpec.GetItemText(i + 1, 1);
		g_clModelData[m_nUnit].m_IrFilterSpec[i] = _ttof((TCHAR*)(LPCTSTR)sData);
	}


	g_clSysData.sDSave();
}

//-----------------------------------------------------------------------------
//
//	버튼 : CLOSE
//
//-----------------------------------------------------------------------------
void CCcdIrFilterSpecDlg::OnBnClickedButtonCcdIrFilterSpecClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 더블 클릭
//
//-----------------------------------------------------------------------------
void CCcdIrFilterSpecDlg::OnNMDblClickedIrFilterSpec(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridIrFilterSpec.GetItemText(nRow, nCol);
		CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
		if (pDlg != NULL)
		{
			if (pDlg->DoModal() == IDOK)
			{
				sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
				m_clGridIrFilterSpec.SetItemText(nRow, nCol, sData);

				m_clGridIrFilterSpec.Invalidate();
			}

			delete pDlg;
		}
	}
}

//-----------------------------------------------------------------------------
//
//	OnLButtonDown
//
//-----------------------------------------------------------------------------
void CCcdIrFilterSpecDlg::OnLButtonDown(UINT nFlags, CPoint point)
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
BOOL CCcdIrFilterSpecDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
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

void CCcdIrFilterSpecDlg::OnStnClickedStaticCcdRotationVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticHRotationVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sPos.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticHRotationVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
}
