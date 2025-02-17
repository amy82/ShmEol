// CcdSfrSpecDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "CcdDefectSpecDlg.h"
#include "afxdialogex.h"


// CCcdDefectSpecDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCcdDefectSpecDlg, CDialogEx)

CCcdDefectSpecDlg::CCcdDefectSpecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCcdDefectSpecDlg::IDD, pParent)
{
	m_nUnit = UNIT_AA1;
}

CCcdDefectSpecDlg::~CCcdDefectSpecDlg()
{
}

void CCcdDefectSpecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_TOP_BAR, m_clColorStaticTopBar);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT, m_clColorStaticCenterSfrLimit);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT_VAL, m_clColorStaticCenterSfrLimitVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT, m_clColorStaticCornerSfrLimit);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT_VAL, m_clColorStaticCornerSfrLimitVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT, m_clColorStaticCornerSfrDeviationLimit);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT_VAL, m_clColorStaticCornerSfrDeviationLimitVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_XY, m_clColorStaticOCXY);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_XY_VAL, m_clColorStaticOCXYVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_TH, m_clColorStaticOCTh);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_TH_VAL, m_clColorStaticOCThVal);
	DDX_Control(pDX, IDC_BUTTON_CCD_SFR_SPEC_SAVE, m_clColorButtonSave);
	DDX_Control(pDX, IDC_BUTTON_CCD_SFR_SPEC_CLOSE, m_clColorButtonClose);
}


BEGIN_MESSAGE_MAP(CCcdDefectSpecDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_DEFECT_SPEC_GRID_SPEC, &CCcdDefectSpecDlg::OnNMDblClickedSfrSpec)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_UNIFORMITY_SPEC_GRID_SPEC, &CCcdDefectSpecDlg::OnNMDblClickedUniformitySpec)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_SAVE, &CCcdDefectSpecDlg::OnBnClickedButtonCcdSfrSpecSave)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_CLOSE, &CCcdDefectSpecDlg::OnBnClickedButtonCcdSfrSpecClose)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT_VAL, &CCcdDefectSpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT_VAL, &CCcdDefectSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT_VAL, &CCcdDefectSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_XY_VAL, &CCcdDefectSpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_TH_VAL, &CCcdDefectSpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal)
END_MESSAGE_MAP()


// CCcdDefectSpecDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::OnPaint()
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
BOOL CCcdDefectSpecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	// 그리드 초기화
	m_nUIDiv = 25; //UI 나눌려고 사용
	this->InitGridCtrl();
	this->InitGridCtrl2();
	this->CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::InitCtrl()
{
	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	//m_clColorStaticTopBar.SetBkColor(RGB_COLOR_BLACK);
	//m_clColorStaticTopBar.SetTextColor(RGB_COLOR_WHITE);
	
	m_clColorStaticCenterSfrLimit.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCenterSfrLimit.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCenterSfrLimit.SetFont(&m_clFontSmall);

	m_clColorStaticCenterSfrLimitVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticCenterSfrLimitVal.SetFont(&m_clFontMid);

	m_clColorStaticCornerSfrLimit.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCornerSfrLimit.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCornerSfrLimit.SetFont(&m_clFontSmall);

	m_clColorStaticCornerSfrLimitVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticCornerSfrLimitVal.SetFont(&m_clFontMid);

	m_clColorStaticCornerSfrDeviationLimit.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCornerSfrDeviationLimit.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCornerSfrDeviationLimit.SetFont(&m_clFontSmall);

	m_clColorStaticCornerSfrDeviationLimitVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticCornerSfrDeviationLimitVal.SetFont(&m_clFontMid);

	m_clColorStaticOCXY.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOCXY.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOCXY.SetFont(&m_clFontSmall);

	m_clColorStaticOCXYVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOCXYVal.SetFont(&m_clFontMid);

	m_clColorStaticOCTh.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOCTh.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOCTh.SetFont(&m_clFontSmall);

	m_clColorStaticOCThVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOCThVal.SetFont(&m_clFontMid);

}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::InitGridCtrl()
{
	//TCHAR* pszRow[] = { _T("") ,
 //        _T("BlockSizeDark"), _T("BlockSizeBright"),
	//	_T("ThresholdTypeHot"), _T("ThresholdTypeDark"), _T("ThresholdTypeBright"),
	//	_T("DefectThresholdHot"), _T("DefectThresholdDark"), _T("DefectThresholdBright"),
	//	_T("MaxHotDefectNum"), _T("MaxDarkDefectNum"), _T("MaxBrightDefectNum"),
	//	_T("MaxHotClusterNum") ,_T("MaxDarkClusterNum"), _T("MaxBrightClusterNum"),
	//	_T("EnableChannel") , _T("DefectInCouplet"),     _T("DefectInCluster") ,
	//	_T("DefectInClusterChannel"),	_T("specColumnFPN")
	//};
	//
	TCHAR* pszCol[] = { _T("Defect"), _T("Spec") };

	CRect rect;
	int i, j;
	int DLG = IDC_STATIC_CCD_DEFECT_SPEC_GRID_SPEC;

	CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	int SpecRow = m_nUIDiv + 1; //sizeof(DEFECT_SPEC_NAME) / sizeof(DEFECT_SPEC_NAME[0]) + 1;//아래
	int SpecCol = 2;//옆
	int margin = 4;
	int gridHeight = 25;
	int gridWidth1 = 200;
	int gridWidth2 = 90;
	int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + margin;
	rect.bottom = (gridHeight*SpecRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


	GetDlgItem(DLG)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridDefectSpec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridDefectSpec.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridDefectSpec.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridDefectSpec.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridDefectSpec.SetReference_Setting();
	m_clGridDefectSpec.EnableSelection(FALSE);
	m_clGridDefectSpec.SetRowCount(SpecRow);
	m_clGridDefectSpec.SetColumnCount(SpecCol);
	m_clGridDefectSpec.SetFixedRowCount(1);
	m_clGridDefectSpec.SetFixedColumnCount(1);

	for (i = 0; i < SpecRow; i++)
	{
		m_clGridDefectSpec.SetRowHeight(i, gridHeight);
		m_clGridDefectSpec.SetItemText(i+1, 0, DEFECT_SPEC_NAME[i]);

		for (j = 0; j < SpecCol; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridDefectSpec.SetColumnWidth(j, gridWidth1);
				}
				else
				{
					m_clGridDefectSpec.SetColumnWidth(j, gridWidth2);
				}

				m_clGridDefectSpec.SetItemText(i, j, pszCol[j]);
			}

			m_clGridDefectSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}

void CCcdDefectSpecDlg::InitGridCtrl2()
{
	TCHAR* pszCol[] = { _T("Defect"), _T("Spec") };

	CRect rect;
	int i, j;
	int DLG = IDC_STATIC_CCD_UNIFORMITY_SPEC_GRID_SPEC;

	CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	int SpecRow = (sizeof(DEFECT_SPEC_NAME) / sizeof(DEFECT_SPEC_NAME[0]) + 1) - m_nUIDiv;//아래
	int SpecCol = 2;//옆
	int margin = 4;
	int gridHeight = 25;
	int gridWidth1 = 200;
	int gridWidth2 = 90;
	int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
	//
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = totalWidth + margin;
	rect.bottom = (gridHeight*SpecRow) + margin;
	pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


	GetDlgItem(DLG)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridUniformitySpec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridUniformitySpec.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridUniformitySpec.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridUniformitySpec.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridUniformitySpec.SetReference_Setting();
	m_clGridUniformitySpec.EnableSelection(FALSE);
	m_clGridUniformitySpec.SetRowCount(SpecRow);
	m_clGridUniformitySpec.SetColumnCount(SpecCol);
	m_clGridUniformitySpec.SetFixedRowCount(1);
	m_clGridUniformitySpec.SetFixedColumnCount(1);

	for (i = 0; i < SpecRow; i++)
	{
		m_clGridUniformitySpec.SetRowHeight(i, gridHeight);
		m_clGridUniformitySpec.SetItemText(i + 1, 0, DEFECT_SPEC_NAME[i + m_nUIDiv]);

		for (j = 0; j < SpecCol; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridUniformitySpec.SetColumnWidth(j, gridWidth1);
				}
				else
				{
					m_clGridUniformitySpec.SetColumnWidth(j, gridWidth2);
				}

				m_clGridUniformitySpec.SetItemText(i, j, pszCol[j]);
			}

			m_clGridUniformitySpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}
//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}

//-----------------------------------------------------------------------------
//
//	OnShowWindow
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
		this->ShowDefectSpec();
		this->ShowDefectSpec2();
	}
}

//-----------------------------------------------------------------------------
//
//	SFR SPEC 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::ShowDefectSpec()
{
	TCHAR szData[SIZE_OF_100BYTE];
	int i;

	for (i = 0; i < m_nUIDiv; i++)
	{
		m_clGridDefectSpec.SetItemText(i + 1, 1, g_clModelData[m_nUnit].m_DefectSpec[i], 3);
	}
	m_clGridDefectSpec.Invalidate();
}
//-----------------------------------------------------------------------------
//
//	UNIFORMITY SPEC 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::ShowDefectSpec2()
{
	TCHAR szData[SIZE_OF_100BYTE];
	int i;

	for (i = 0; i < g_Defectcount - m_nUIDiv; i++)
	{
		m_clGridUniformitySpec.SetItemText(i + 1, 1, g_clModelData[m_nUnit].m_DefectSpec[i + m_nUIDiv], 3);
	}
	m_clGridUniformitySpec.Invalidate();
}

//-----------------------------------------------------------------------------
//
//	CENTER SFR LIMIT
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticCenterSfrLimitVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{			
			sPos.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticCenterSfrLimitVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	CORNER SFR LIMIT
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticCornerSfrLimitVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{			
			sPos.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticCornerSfrLimitVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	코너부 SFR 편차 LIMIT
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticCornerSfrDeviationLimitVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{			
			sPos.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticCornerSfrDeviationLimitVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	광축검사 XY
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticOCXYVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{			
			sPos.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticOCXYVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	광축검사 TH
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticOCThVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{			
			sPos.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticOCThVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : SAVE
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::OnBnClickedButtonCcdSfrSpecSave()
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
	if (g_ShowMsgModal(_T("확인"), _T("DEFECT/UNIFORM SPEC 데이터를 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
		return;

	this->GetDefectSpec();
    this->GetDefectSpec2();
	//g_clSysData.Save();
	//g_clMandoSfrSpec[m_nUnit].Save();
	g_clModelData[m_nUnit].AcmisDataSave(g_clSysData.m_szModelName);
	AddLog(_T("[INFO] DEFECT/UNIFORM SPEC 저장"), 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	SFR 데이터 -> 메모리에 저장
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::GetDefectSpec()
{
	CString sData = _T("");
	int i;

	for (i = 0; i < m_nUIDiv; i++)
	{
		sData = m_clGridDefectSpec.GetItemText(i + 1, 1);
		g_clModelData[m_nUnit].m_DefectSpec[i] = _ttof((TCHAR*)(LPCTSTR)sData);
	}

	g_clSysData.sDSave();
}
//-----------------------------------------------------------------------------
//
//	UNIFORMITY 데이터 -> 메모리에 저장
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::GetDefectSpec2()
{
	CString sData = _T("");
	int i;

	for (i = 0; i < g_Defectcount - m_nUIDiv; i++)
	{
		sData = m_clGridUniformitySpec.GetItemText(i + 1, 1);
		g_clModelData[m_nUnit].m_DefectSpec[i + m_nUIDiv] = _ttof((TCHAR*)(LPCTSTR)sData);
	}
	g_clSysData.sDSave();
}

//-----------------------------------------------------------------------------
//
//	버튼 : CLOSE
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::OnBnClickedButtonCcdSfrSpecClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 더블 클릭
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::OnNMDblClickedSfrSpec(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridDefectSpec.GetItemText(nRow, nCol);
		CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
		if (pDlg != NULL)
		{
			if (pDlg->DoModal() == IDOK)
			{
				sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
				m_clGridDefectSpec.SetItemText(nRow, nCol, sData);

				m_clGridDefectSpec.Invalidate();
			}

			delete pDlg;
		}
	}
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 더블 클릭
//
//-----------------------------------------------------------------------------
void CCcdDefectSpecDlg::OnNMDblClickedUniformitySpec(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridUniformitySpec.GetItemText(nRow, nCol);
		CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
		if (pDlg != NULL)
		{
			if (pDlg->DoModal() == IDOK)
			{
				sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
				m_clGridUniformitySpec.SetItemText(nRow, nCol, sData);

				m_clGridUniformitySpec.Invalidate();
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
void CCcdDefectSpecDlg::OnLButtonDown(UINT nFlags, CPoint point)
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
BOOL CCcdDefectSpecDlg::PreTranslateMessage(MSG* pMsg)
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