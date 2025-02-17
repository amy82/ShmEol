// CcdSfrSpecDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "CcdRiOcSpecDlg.h"
#include "afxdialogex.h"


// CCcdRiOcSpecDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCcdRiOcSpecDlg, CDialogEx)

CCcdRiOcSpecDlg::CCcdRiOcSpecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCcdRiOcSpecDlg::IDD, pParent)
{
	m_nUnit = UNIT_AA1;
}

CCcdRiOcSpecDlg::~CCcdRiOcSpecDlg()
{
}

void CCcdRiOcSpecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_TOP_BAR, m_clColorStaticTopBar);

	DDX_Control(pDX, IDC_STATIC_OC_LIMIT_MIN, m_clColorStaticOcLimitMin);
	DDX_Control(pDX, IDC_STATIC_OC_LIMIT_MAX, m_clColorStaticOcLimitMax);

	DDX_Control(pDX, IDC_STATIC_ROTATE_LIMIT_MIN, m_clColorStaticRotateLimitMin);
	DDX_Control(pDX, IDC_STATIC_ROTATE_LIMIT_MAX, m_clColorStaticRotateLimitMax);
	DDX_Control(pDX, IDC_STATIC_TILTX_LIMIT_MIN,  m_clColorStaticTiltxLimitMin);
	DDX_Control(pDX, IDC_STATIC_TILTX_LIMIT_MAX,  m_clColorStaticTiltxLimitMax);
	DDX_Control(pDX, IDC_STATIC_TILTY_LIMIT_MIN,  m_clColorStaticTiltyLimitMin);
	DDX_Control(pDX, IDC_STATIC_TILTY_LIMIT_MAX,  m_clColorStaticTiltyLimitMax);

	DDX_Control(pDX, IDC_STATIC_OC_MIN_VAL, m_clColorStaticOcLimitMinVal);
	DDX_Control(pDX, IDC_STATIC_OC_MAX_VAL, m_clColorStaticOcLimitMaxVal);

	DDX_Control(pDX, IDC_STATIC_ROTATE_MIN_VAL, m_clColorStaticRotateLimitMinVal);
	DDX_Control(pDX, IDC_STATIC_ROTATE_MAX_VAL, m_clColorStaticRotateLimitMaxVal);

	DDX_Control(pDX, IDC_STATIC_TILTX_MIN_VAL, m_clColorStaticTiltxLimitMinVal);
	DDX_Control(pDX, IDC_STATIC_TILTX_MAX_VAL, m_clColorStaticTiltxLimitMaxVal);
	DDX_Control(pDX, IDC_STATIC_TILTY_MIN_VAL, m_clColorStaticTiltyLimitMinVal);
	DDX_Control(pDX, IDC_STATIC_TILTY_MAX_VAL, m_clColorStaticTiltyLimitMaxVal);




	DDX_Control(pDX, IDC_BUTTON_CCD_SFR_SPEC_SAVE, m_clColorButtonSave);
	DDX_Control(pDX, IDC_BUTTON_CCD_SFR_SPEC_CLOSE, m_clColorButtonClose);





	//
	//
	/*DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT, m_clColorStaticCenterSfrLimit);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT_VAL, m_clColorStaticCenterSfrLimitVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT, m_clColorStaticCornerSfrLimit);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT_VAL, m_clColorStaticCornerSfrLimitVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT, m_clColorStaticCornerSfrDeviationLimit);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT_VAL, m_clColorStaticCornerSfrDeviationLimitVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_XY, m_clColorStaticOCXY);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_XY_VAL, m_clColorStaticOCXYVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_TH, m_clColorStaticOCTh);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_TH_VAL, m_clColorStaticOCThVal);
	DDX_Control(pDX, IDC_STATIC_OC_OFFSET_X, m_clColorStaticOcOffsetX);
	DDX_Control(pDX, IDC_STATIC_OC_OFFSET_X_VAL, m_clColorStaticOcOffsetXVal);
	DDX_Control(pDX, IDC_STATIC_IC_OFFSET_X, m_clColorStatic_IcOffsetX);
	DDX_Control(pDX, IDC_STATIC_IC_OFFSET_Y, m_clColorStatic_IcOffsetY);
	DDX_Control(pDX, IDC_STATIC_IC_OFFSET_X_VAL, m_clColorStatic_IcOffsetXVal);
	DDX_Control(pDX, IDC_STATIC_IC_OFFSET_Y_VAL, m_clColorStatic_IcOffsetYVal);
	DDX_Control(pDX, IDC_STATIC_OC_OFFSET_Y, m_clColorStaticOcOffsetY);
	DDX_Control(pDX, IDC_STATIC_OC_OFFSET_Y_VAL, m_clColorStaticOcOffsetYVal);*/

	
	
	
}


BEGIN_MESSAGE_MAP(CCcdRiOcSpecDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_STN_CLICKED(IDC_STATIC_OC_MIN_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticOcMinVal)
	ON_STN_CLICKED(IDC_STATIC_OC_MAX_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticOcMaxVal)


	//ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_OC_SPEC_GRID_SPEC, &CCcdRiOcSpecDlg::OnNMDblClickedUniformitySpec)
	//ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_IC_SPEC_GRID_SPEC, &CCcdRiOcSpecDlg::OnNMDblClickedIcSpec)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_SAVE, &CCcdRiOcSpecDlg::OnBnClickedButtonCcdSfrSpecSave)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_CLOSE, &CCcdRiOcSpecDlg::OnBnClickedButtonCcdSfrSpecClose)


	/*ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_XY_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_TH_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal)
	ON_STN_CLICKED(IDC_STATIC_OC_OFFSET_X_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticOcOffsetXVal)
	ON_STN_CLICKED(IDC_STATIC_OC_OFFSET_Y_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticOcOffsetYVal)
	
	ON_STN_CLICKED(IDC_STATIC_IC_OFFSET_X_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticIcOffsetXVal)
	ON_STN_CLICKED(IDC_STATIC_IC_OFFSET_Y_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticIcOffsetYVal)*/
	ON_STN_CLICKED(IDC_STATIC_ROTATE_MIN_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticRotateMinVal)
	ON_STN_CLICKED(IDC_STATIC_ROTATE_MAX_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticRotateMaxVal)
	ON_STN_CLICKED(IDC_STATIC_TILTX_MIN_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticTiltxMinVal)
	ON_STN_CLICKED(IDC_STATIC_TILTX_MAX_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticTiltxMaxVal)
	ON_STN_CLICKED(IDC_STATIC_TILTY_MIN_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticTiltyMinVal)
	ON_STN_CLICKED(IDC_STATIC_TILTY_MAX_VAL, &CCcdRiOcSpecDlg::OnStnClickedStaticTiltyMaxVal)
END_MESSAGE_MAP()


// CCcdRiOcSpecDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CCcdRiOcSpecDlg::OnPaint()
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
BOOL CCcdRiOcSpecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	// 그리드 초기화
	//this->InitOCGridCtrl();
	//this->InitICGridCtrl();
	this->CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdRiOcSpecDlg::InitCtrl()
{
	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));


	m_clColorStaticOcLimitMin.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOcLimitMin.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOcLimitMin.SetFont(&m_clFontSmall);

	m_clColorStaticOcLimitMax.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOcLimitMax.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOcLimitMax.SetFont(&m_clFontSmall);


	m_clColorStaticRotateLimitMin.SetBkColor(RGB_DLG_BG);
	m_clColorStaticRotateLimitMin.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticRotateLimitMin.SetFont(&m_clFontSmall);

	m_clColorStaticRotateLimitMax.SetBkColor(RGB_DLG_BG);
	m_clColorStaticRotateLimitMax.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticRotateLimitMax.SetFont(&m_clFontSmall);

	m_clColorStaticTiltxLimitMin.SetBkColor(RGB_DLG_BG);
	m_clColorStaticTiltxLimitMin.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticTiltxLimitMin.SetFont(&m_clFontSmall);

	m_clColorStaticTiltxLimitMax.SetBkColor(RGB_DLG_BG);
	m_clColorStaticTiltxLimitMax.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticTiltxLimitMax.SetFont(&m_clFontSmall);

	m_clColorStaticTiltyLimitMin.SetBkColor(RGB_DLG_BG);
	m_clColorStaticTiltyLimitMin.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticTiltyLimitMin.SetFont(&m_clFontSmall);

	m_clColorStaticTiltyLimitMax.SetBkColor(RGB_DLG_BG);
	m_clColorStaticTiltyLimitMax.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticTiltyLimitMax.SetFont(&m_clFontSmall);



}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdRiOcSpecDlg::InitOCGridCtrl()
{
	TCHAR* pszRow[] = { _T("") ,
        _T("nFiducialMarkNum"),_T("nFiducialMarkType")
	};

	TCHAR* pszCol[] = { _T("OC"), _T("Spec") };

	CRect rect;
	int i, j;
	int DLG = IDC_STATIC_CCD_OC_SPEC_GRID_SPEC;

	CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	int SpecRow = OCMaxCount;//아래
	int SpecCol = 2;//옆
	int margin = 4;
	int gridHeight = 25;
	int gridWidth1 = 140;
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
	m_clGridOCSpec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridOCSpec.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridOCSpec.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridOCSpec.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridOCSpec.SetReference_Setting();
	m_clGridOCSpec.EnableSelection(FALSE);
	m_clGridOCSpec.SetRowCount(SpecRow);
	m_clGridOCSpec.SetColumnCount(SpecCol);
	m_clGridOCSpec.SetFixedRowCount(1);
	m_clGridOCSpec.SetFixedColumnCount(1);

	for (i = 0; i < SpecRow; i++)
	{
		m_clGridOCSpec.SetRowHeight(i, gridHeight);
		m_clGridOCSpec.SetItemText(i, 0, pszRow[i]);

		for (j = 0; j < SpecCol; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridOCSpec.SetColumnWidth(j, gridWidth1);
				}
				else
				{
					m_clGridOCSpec.SetColumnWidth(j, gridWidth2);
				}

				m_clGridOCSpec.SetItemText(i, j, pszCol[j]);
			}

			m_clGridOCSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}


//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdRiOcSpecDlg::InitICGridCtrl()
{
	TCHAR* pszCol[] = { _T("IC"), _T("Spec") };

	CRect rect;
	int i, j;
	int DLG = IDC_STATIC_CCD_IC_SPEC_GRID_SPEC;

	CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	int SpecRow = g_Iccount + 1;// sizeof(IC_SPEC_NAME) / sizeof(IC_SPEC_NAME[0]) + 1;//아래
	int SpecCol = 2;//옆
	int margin = 4;
	int gridHeight = 25;
	int gridWidth1 = 140;
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
	m_clGridICSpec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridICSpec.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridICSpec.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridICSpec.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridICSpec.SetReference_Setting();
	m_clGridICSpec.EnableSelection(FALSE);
	m_clGridICSpec.SetRowCount(SpecRow);
	m_clGridICSpec.SetColumnCount(SpecCol);
	m_clGridICSpec.SetFixedRowCount(1);
	m_clGridICSpec.SetFixedColumnCount(1);

	for (i = 0; i < SpecRow; i++)
	{
		m_clGridICSpec.SetRowHeight(i, gridHeight);
		m_clGridICSpec.SetItemText(i + 1, 0, IC_SPEC_NAME[i]);

		for (j = 0; j < SpecCol; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridICSpec.SetColumnWidth(j, gridWidth1);
				}
				else
				{
					m_clGridICSpec.SetColumnWidth(j, gridWidth2);
				}

				m_clGridICSpec.SetItemText(i, j, pszCol[j]);
			}

			m_clGridICSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}

//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CCcdRiOcSpecDlg::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}

//-----------------------------------------------------------------------------
//
//	OnShowWindow
//
//-----------------------------------------------------------------------------
void CCcdRiOcSpecDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
		this->ShowOcSpec();
		//this->ShowIcSpec();
	}
}

//-----------------------------------------------------------------------------
//
//	UNIFORMITY SPEC 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdRiOcSpecDlg::ShowOcSpec()
{
	TCHAR szData[SIZE_OF_100BYTE];
	int i;

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.02lf"), g_clModelData[m_nUnit].m_dOCSpecLimit[0]);
	m_clColorStaticOcLimitMinVal.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.02lf"), g_clModelData[m_nUnit].m_dOCSpecLimit[1]);
	m_clColorStaticOcLimitMaxVal.SetWindowText(szData);

	//rotate
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.02lf"), g_clModelData[m_nUnit].m_dRotateSpecLimit[0]);
	m_clColorStaticRotateLimitMinVal.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.02lf"), g_clModelData[m_nUnit].m_dRotateSpecLimit[1]);
	m_clColorStaticRotateLimitMaxVal.SetWindowText(szData);

	//tilt
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.02lf"), g_clModelData[m_nUnit].m_dTiltxSpecLimit[0]);
	m_clColorStaticTiltxLimitMinVal.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.02lf"), g_clModelData[m_nUnit].m_dTiltxSpecLimit[1]);
	m_clColorStaticTiltxLimitMaxVal.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.02lf"), g_clModelData[m_nUnit].m_dTiltySpecLimit[0]);
	m_clColorStaticTiltyLimitMinVal.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.02lf"), g_clModelData[m_nUnit].m_dTiltySpecLimit[1]);
	m_clColorStaticTiltyLimitMaxVal.SetWindowText(szData);
	
}

//-----------------------------------------------------------------------------
//
//	IC SPEC 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdRiOcSpecDlg::ShowIcSpec()
{
	TCHAR szData[SIZE_OF_100BYTE];
	int i;


	
}


//-----------------------------------------------------------------------------
//
//	버튼 : SAVE
//
//-----------------------------------------------------------------------------
void CCcdRiOcSpecDlg::OnBnClickedButtonCcdSfrSpecSave()
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

	if (g_ShowMsgModal(_T("확인"), _T("OC SPEC 데이터를 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
		return;

	this->GetOcSpec();
	//this->GetIcSpec();

	g_clModelData[m_nUnit].AcmisDataSave(g_clSysData.m_szModelName);
	AddLog(_T("[INFO] OC SPEC 저장"), 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	UNIFORMITY 데이터 -> 메모리에 저장
//
//-----------------------------------------------------------------------------
void CCcdRiOcSpecDlg::GetOcSpec()
{
	CString sData = _T("");
	int i;

	//ok
	GetDlgItem(IDC_STATIC_OC_MIN_VAL)->GetWindowText(sData);
	g_clModelData[m_nUnit].m_dOCSpecLimit[0] = _ttof((TCHAR*)(LPCTSTR)sData);

	GetDlgItem(IDC_STATIC_OC_MAX_VAL)->GetWindowText(sData);
	g_clModelData[m_nUnit].m_dOCSpecLimit[1] = _ttof((TCHAR*)(LPCTSTR)sData);
	
	//rotate
	GetDlgItem(IDC_STATIC_ROTATE_MIN_VAL)->GetWindowText(sData);
	g_clModelData[m_nUnit].m_dRotateSpecLimit[0] = _ttof((TCHAR*)(LPCTSTR)sData);

	GetDlgItem(IDC_STATIC_ROTATE_MAX_VAL)->GetWindowText(sData);
	g_clModelData[m_nUnit].m_dRotateSpecLimit[1] = _ttof((TCHAR*)(LPCTSTR)sData);
	//tilt
	GetDlgItem(IDC_STATIC_TILTX_MIN_VAL)->GetWindowText(sData);
	g_clModelData[m_nUnit].m_dTiltxSpecLimit[0] = _ttof((TCHAR*)(LPCTSTR)sData);

	GetDlgItem(IDC_STATIC_TILTX_MAX_VAL)->GetWindowText(sData);
	g_clModelData[m_nUnit].m_dTiltxSpecLimit[1] = _ttof((TCHAR*)(LPCTSTR)sData);

	GetDlgItem(IDC_STATIC_TILTY_MIN_VAL)->GetWindowText(sData);
	g_clModelData[m_nUnit].m_dTiltySpecLimit[0] = _ttof((TCHAR*)(LPCTSTR)sData);

	GetDlgItem(IDC_STATIC_TILTY_MAX_VAL)->GetWindowText(sData);
	g_clModelData[m_nUnit].m_dTiltySpecLimit[1] = _ttof((TCHAR*)(LPCTSTR)sData);

	sData.Empty();
}
//-----------------------------------------------------------------------------
//
//	UNIFORMITY 데이터 -> 메모리에 저장
//
//-----------------------------------------------------------------------------
void CCcdRiOcSpecDlg::GetIcSpec()
{
	//CString sData = _T("");
	//int i;

	/*for (i = 0; i < g_Iccount; i++)
	{
		sData = m_clGridICSpec.GetItemText(i + 1, 1);
		g_clModelData[m_nUnit].m_ICSpec[i] = _ttof((TCHAR*)(LPCTSTR)sData);
	}*/
	//g_clSysData.Save();
}
//-----------------------------------------------------------------------------
//
//	버튼 : CLOSE
//
//-----------------------------------------------------------------------------
void CCcdRiOcSpecDlg::OnBnClickedButtonCcdSfrSpecClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
}


//-----------------------------------------------------------------------------
//
//	OnLButtonDown
//
//-----------------------------------------------------------------------------
void CCcdRiOcSpecDlg::OnLButtonDown(UINT nFlags, CPoint point)
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
BOOL CCcdRiOcSpecDlg::PreTranslateMessage(MSG* pMsg)
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


void CCcdRiOcSpecDlg::OnStnClickedStaticOcMinVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	GetDlgItem(IDC_STATIC_OC_MIN_VAL)->GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.02lf"), pDlg->GetReturnVal());
			GetDlgItem(IDC_STATIC_OC_MIN_VAL)->SetWindowText(sData);
			sData.Empty();
		}

		delete pDlg;
	}
}


void CCcdRiOcSpecDlg::OnStnClickedStaticOcMaxVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	GetDlgItem(IDC_STATIC_OC_MAX_VAL)->GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.02lf"), pDlg->GetReturnVal());
			GetDlgItem(IDC_STATIC_OC_MAX_VAL)->SetWindowText(sData);
			sData.Empty();
		}

		delete pDlg;
	}
}



void CCcdRiOcSpecDlg::OnStnClickedStaticRotateMinVal()
{
	// TODO: Add your control notification handler code here
	CString sData = _T("");

	GetDlgItem(IDC_STATIC_ROTATE_MIN_VAL)->GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.02lf"), pDlg->GetReturnVal());
			GetDlgItem(IDC_STATIC_ROTATE_MIN_VAL)->SetWindowText(sData);
			sData.Empty();
		}

		delete pDlg;
	}
}


void CCcdRiOcSpecDlg::OnStnClickedStaticRotateMaxVal()
{
	// TODO: Add your control notification handler code here
	CString sData = _T("");

	GetDlgItem(IDC_STATIC_ROTATE_MAX_VAL)->GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.02lf"), pDlg->GetReturnVal());
			GetDlgItem(IDC_STATIC_ROTATE_MAX_VAL)->SetWindowText(sData);
			sData.Empty();
		}

		delete pDlg;
	}
}


void CCcdRiOcSpecDlg::OnStnClickedStaticTiltxMinVal()
{
	// TODO: Add your control notification handler code here
	CString sData = _T("");

	GetDlgItem(IDC_STATIC_TILTX_MIN_VAL)->GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.02lf"), pDlg->GetReturnVal());
			GetDlgItem(IDC_STATIC_TILTX_MIN_VAL)->SetWindowText(sData);
			sData.Empty();
		}

		delete pDlg;
	}
}


void CCcdRiOcSpecDlg::OnStnClickedStaticTiltxMaxVal()
{
	// TODO: Add your control notification handler code here
	CString sData = _T("");

	GetDlgItem(IDC_STATIC_TILTX_MAX_VAL)->GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.02lf"), pDlg->GetReturnVal());
			GetDlgItem(IDC_STATIC_TILTX_MAX_VAL)->SetWindowText(sData);
			sData.Empty();
		}

		delete pDlg;
	}
}


void CCcdRiOcSpecDlg::OnStnClickedStaticTiltyMinVal()
{
	// TODO: Add your control notification handler code here
	CString sData = _T("");

	GetDlgItem(IDC_STATIC_TILTY_MIN_VAL)->GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.02lf"), pDlg->GetReturnVal());
			GetDlgItem(IDC_STATIC_TILTY_MIN_VAL)->SetWindowText(sData);
			sData.Empty();
		}

		delete pDlg;
	}
}


void CCcdRiOcSpecDlg::OnStnClickedStaticTiltyMaxVal()
{
	// TODO: Add your control notification handler code here
	CString sData = _T("");

	GetDlgItem(IDC_STATIC_TILTY_MAX_VAL)->GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.02lf"), pDlg->GetReturnVal());
			GetDlgItem(IDC_STATIC_TILTY_MAX_VAL)->SetWindowText(sData);
			sData.Empty();
		}

		delete pDlg;
	}
}
