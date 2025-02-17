// CcdSfrSpecDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "CcdRISpecDlg.h"
#include "afxdialogex.h"


// CCcdRISpecDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCcdRISpecDlg, CDialogEx)

CCcdRISpecDlg::CCcdRISpecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCcdRISpecDlg::IDD, pParent)
{
	m_nUnit = UNIT_AA1;
	m_brCheck.CreateSolidBrush(RGB(45, 45, 45));
}

CCcdRISpecDlg::~CCcdRISpecDlg()
{
}

void CCcdRISpecDlg::DoDataExchange(CDataExchange* pDX)
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


	DDX_Control(pDX, IDC_STATIC_CCD_RI_DATAFORMAT,			m_clColorStaticCcdRiDataformat);
	DDX_Control(pDX, IDC_STATIC_CCD_RI_OUTMODE,				m_clColorStaticCcdRiOutmode);
	DDX_Control(pDX, IDC_STATIC_CCD_RI_SENSORTYPE,			m_clColorStaticCcdRiSensortype);
	DDX_Control(pDX, IDC_STATIC_CCD_RI_DEMOSAIC,			m_clColorStaticCcdRiDemosaic);
	DDX_Control(pDX, IDC_STATIC_CONFIG_CCD_RI_BLACKLEVEL,	m_clColorStaticCcdRiBlacklevel);
	DDX_Control(pDX, IDC_STATIC_CCD_RI_BLACKLEVEL_VAL, m_clColorStaticRiBlackLevelVal);

	DDX_Control(pDX, IDC_CCD_RI_COMBO_DATAFORMAT,			m_CcdRiComboDataFormat);
	DDX_Control(pDX, IDC_CCD_RI_COMBO_OUTMODE,				m_CcdRiComboOutMode);
	DDX_Control(pDX, IDC_CCD_RI_COMBO_SENSORTYPE,			m_CcdRiComboSensorType);
	DDX_Control(pDX, IDC_CCD_RI_COMBO_DEMOSAIC,				m_CcdRiComboDemosaic);

}


BEGIN_MESSAGE_MAP(CCcdRISpecDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_RI_SPEC_GRID_SPEC, &CCcdRISpecDlg::OnNMDblClickedRiSpec)

	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_SAVE, &CCcdRISpecDlg::OnBnClickedButtonCcdSfrSpecSave)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_CLOSE, &CCcdRISpecDlg::OnBnClickedButtonCcdSfrSpecClose)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT_VAL, &CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT_VAL, &CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT_VAL, &CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_XY_VAL, &CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_TH_VAL, &CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal)
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_STATIC_CCD_RI_BLACKLEVEL_VAL, &CCcdRISpecDlg::OnStnClickedStaticCcdRiBlacklevelVal)
END_MESSAGE_MAP()


// CCcdRISpecDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::OnPaint()
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
BOOL CCcdRISpecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	// 그리드 초기화

	this->InitRI4GridCtrl();
	this->CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::InitCtrl()
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

	m_clColorStaticCcdRiDataformat.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdRiDataformat.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdRiDataformat.SetFont(&m_clFontSmall);

	m_clColorStaticCcdRiOutmode.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdRiOutmode.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdRiOutmode.SetFont(&m_clFontSmall);

	m_clColorStaticCcdRiSensortype.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdRiSensortype.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdRiSensortype.SetFont(&m_clFontSmall);

	m_clColorStaticCcdRiDemosaic.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdRiDemosaic.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdRiDemosaic.SetFont(&m_clFontSmall);

	m_clColorStaticCcdRiBlacklevel.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdRiBlacklevel.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdRiBlacklevel.SetFont(&m_clFontSmall);

	SetWindowTheme(GetDlgItem(IDC_CHECK_CCD_RI_8BITUSE)->m_hWnd, L"", L"");

	/*
	1. DataFormat
	2. OutMode
	3. SensorType
	4. DemosaicMethod
	*/
	m_CcdRiComboDataFormat.ResetContent();
	m_CcdRiComboOutMode.ResetContent();
	m_CcdRiComboSensorType.ResetContent();
	m_CcdRiComboDemosaic.ResetContent();

	m_CcdRiComboDataFormat.AddString(_T("DATAFORMAT_YUV"));
	m_CcdRiComboDataFormat.AddString(_T("DATAFORMAT_BAYER_8BIT"));
	m_CcdRiComboDataFormat.AddString(_T("DATAFORMAT_BAYER_10BIT"));
	m_CcdRiComboDataFormat.AddString(_T("DATAFORMAT_BAYER_PARALLEL_10BIT"));
	m_CcdRiComboDataFormat.AddString(_T("DATAFORMAT_BAYER_12BIT"));
	m_CcdRiComboDataFormat.AddString(_T("DATAFORMAT_BAYER_PARALLEL_12BIT"));
	m_CcdRiComboDataFormat.AddString(_T("DATAFORMAT_BAYER_16BIT"));
	m_CcdRiComboDataFormat.AddString(_T("DATAFORMAT_BAYER_16BIT_BE"));
	m_CcdRiComboDataFormat.AddString(_T("DATAFORMAT_BAYER_16BIT_PWL_HDR"));
	m_CcdRiComboDataFormat.AddString(_T("DATAFORMAT_BAYER_16BIT_PWL_DECOMP"));
	m_CcdRiComboDataFormat.AddString(_T("DATAFORMAT_BAYER_24BIT"));
	m_CcdRiComboDataFormat.AddString(_T("DATAFORMAT_BAYER_PARALLEL_10BIT_BE"));
	m_CcdRiComboDataFormat.AddString(_T("DATAFORMAT_BAYER_PARALLEL_12BIT_BE"));
	m_CcdRiComboDataFormat.AddString(_T("DATAFORMAT_RGB"));		//rgb = 100
																	//
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_BGGR"));	//1
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_RGGB"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_GBRG"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_GRBG"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_BLACKWHITE"));	//1
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_YUV422_YCbYCr"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_YUV422_YCrYCb"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_YUV422_CbYCrY"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_YUV422_CrYCbY"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_RGB_BGR"));		//1
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_RGB_RGB"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_BNGR"));	//1
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_RGNB"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_NBRG"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_GRBN"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_BGGN"));	//1
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_RGGN"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_GBNG"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_GRNG"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_NGGR"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_NGGB"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_GNRG"));
	m_CcdRiComboOutMode.AddString(_T("OUTMODE_BAYER_GNBG"));
	//
	m_CcdRiComboSensorType.AddString(_T("SENSORTYPE_RGGB"));
	m_CcdRiComboSensorType.AddString(_T("SENSORTYPE_RCCC"));
	m_CcdRiComboSensorType.AddString(_T("SENSORTYPE_RCCB"));
	m_CcdRiComboSensorType.AddString(_T("SENSORTYPE_CCCC"));
	m_CcdRiComboSensorType.AddString(_T("SENSORTYPE_RBCC"));
	m_CcdRiComboSensorType.AddString(_T("SENSORTYPE_OTHER"));
	m_CcdRiComboSensorType.AddString(_T("SENSORTYPE_RGBIR2"));
	//

	m_CcdRiComboDemosaic.AddString(_T("DEMOSAIC_NONE"));
	m_CcdRiComboDemosaic.AddString(_T("GRADIENT"));
	m_CcdRiComboDemosaic.AddString(_T("BL33"));
	m_CcdRiComboDemosaic.AddString(_T("OPENCV_VNG"));
	m_CcdRiComboDemosaic.AddString(_T("VNG"));
	m_CcdRiComboDemosaic.AddString(_T("GR_ONLY"));
	m_CcdRiComboDemosaic.AddString(_T("GB_ONLY"));
	m_CcdRiComboDemosaic.AddString(_T("GBTF"));
	m_CcdRiComboDemosaic.AddString(_T("BLLC"));
	m_CcdRiComboDemosaic.AddString(_T("RESIDUAL"));
	m_CcdRiComboDemosaic.AddString(_T("BAYER_Y"));
	m_CcdRiComboDemosaic.AddString(_T("GRADIENT_RESIDUAL"));
	m_CcdRiComboDemosaic.AddString(_T("GBTF_RESIDUAL"));
	m_CcdRiComboDemosaic.AddString(_T("RESIDUAL_RESIDUAL"));
	m_CcdRiComboDemosaic.AddString(_T("BL33_RESIDUAL"));
	m_CcdRiComboDemosaic.AddString(_T("IR_ONLY"));
	m_CcdRiComboDemosaic.AddString(_T("GRADIENT_G_ONLY"));
	m_CcdRiComboDemosaic.AddString(_T("GBTF_G_ONLY"));
	m_CcdRiComboDemosaic.AddString(_T("RESIDUAL_G_ONLY"));
	m_CcdRiComboDemosaic.AddString(_T("BL33_G_ONLY"));
	m_CcdRiComboDemosaic.AddString(_T("GRADIENT_IR_ONLY"));
	m_CcdRiComboDemosaic.AddString(_T("GBTF_IR_ONLY"));
	m_CcdRiComboDemosaic.AddString(_T("RESIDUAL_IR_ONLY"));
	m_CcdRiComboDemosaic.AddString(_T("BL33_IR_ONLY"));


	m_CcdRiComboDataFormat.SetCurSel(0);
	m_CcdRiComboOutMode.SetCurSel(0);
	m_CcdRiComboSensorType.SetCurSel(0);
	m_CcdRiComboDemosaic.SetCurSel(0);

}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------

void CCcdRISpecDlg::InitRI4GridCtrl()
{
	TCHAR* pszCol[] = { _T("RI"), _T("Spec") };

	CRect rect;
	int i, j;
	int DLG = IDC_STATIC_CCD_RI_SPEC_GRID_SPEC;//IDC_STATIC_CCD_RI4_SPEC_GRID_SPEC

	CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	int SpecRow = g_Ricount + 1;
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
	m_clGridRISpec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridRISpec.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridRISpec.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridRISpec.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridRISpec.SetReference_Setting();
	m_clGridRISpec.EnableSelection(FALSE);
	m_clGridRISpec.SetRowCount(SpecRow);
	m_clGridRISpec.SetColumnCount(SpecCol);
	m_clGridRISpec.SetFixedRowCount(1);
	m_clGridRISpec.SetFixedColumnCount(1);

	for (i = 0; i < SpecRow; i++)
	{
		m_clGridRISpec.SetRowHeight(i, gridHeight);
		m_clGridRISpec.SetItemText(i + 1, 0, RI_SPEC_NAME[i]);

		for (j = 0; j < SpecCol; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridRISpec.SetColumnWidth(j, gridWidth1);
				}
				else
				{
					m_clGridRISpec.SetColumnWidth(j, gridWidth2);
				}

				m_clGridRISpec.SetItemText(i, j, pszCol[j]);
			}

			m_clGridRISpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}
//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}

//-----------------------------------------------------------------------------
//
//	OnShowWindow
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
		this->ShowRI4Spec();
	}
}

//-----------------------------------------------------------------------------
//
//	RI SPEC 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::ShowRI4Spec()
{
	TCHAR szData[SIZE_OF_100BYTE];
	CButton* pButton;
	int i = 0;
	for (i = 0; i < g_Ricount; i++)
	{
		m_clGridRISpec.SetItemText(i + 1, 1, g_clModelData[m_nUnit].m_RISpec[i], 3);
	}
	m_clGridRISpec.Invalidate();


	pButton = (CButton*)GetDlgItem(IDC_CHECK_CCD_RI_8BITUSE);
	if (g_clModelData[m_nUnit].m_nRi8BitUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_dRiBlackLevel);
	m_clColorStaticRiBlackLevelVal.SetWindowText(szData);


	m_CcdRiComboDataFormat.SetCurSel(g_clModelData[m_nUnit].riParameter[0]);
	m_CcdRiComboOutMode.SetCurSel(g_clModelData[m_nUnit].riParameter[1]);
	m_CcdRiComboSensorType.SetCurSel(g_clModelData[m_nUnit].riParameter[2]);
	m_CcdRiComboDemosaic.SetCurSel(g_clModelData[m_nUnit].riParameter[3]);
}
//-----------------------------------------------------------------------------
//
//	RI 데이터 -> 메모리에 저장
//
//-----------------------------------------------------------------------------

void CCcdRISpecDlg::GetRI4Spec()
{
	CString sData = _T("");
	CButton* pButton;
	int i;
	int _x = 0;
	int _y = 0;
	int riTotal = g_Ricount;
	for (i = 0; i < riTotal; i++)
	{
		sData = m_clGridRISpec.GetItemText(i + 1, 1);
		g_clModelData[m_nUnit].m_RISpec[i] = _ttof((TCHAR*)(LPCTSTR)sData);
	}

	GetDlgItem(IDC_STATIC_CCD_RI_BLACKLEVEL_VAL)->GetWindowText(sData);
	g_clModelData[m_nUnit].m_dRiBlackLevel = _ttoi((TCHAR*)(LPCTSTR)sData);


	pButton = (CButton*)GetDlgItem(IDC_CHECK_CCD_RI_8BITUSE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nRi8BitUse = 1;
	else
		g_clModelData[m_nUnit].m_nRi8BitUse = 0;


	g_clModelData[m_nUnit].riParameter[0] = m_CcdRiComboDataFormat.GetCurSel();
	g_clModelData[m_nUnit].riParameter[1] = m_CcdRiComboOutMode.GetCurSel();
	g_clModelData[m_nUnit].riParameter[2] = m_CcdRiComboSensorType.GetCurSel();
	g_clModelData[m_nUnit].riParameter[3] = m_CcdRiComboDemosaic.GetCurSel();

	g_clLaonGrabberWrapper[m_nUnit].dRi_Tdataspec.eDataFormat = g_clLaonGrabberWrapper[m_nUnit].rDataFormatType(g_clModelData[m_nUnit].riParameter[0]);
	g_clLaonGrabberWrapper[m_nUnit].dRi_Tdataspec.eOutMode = g_clLaonGrabberWrapper[m_nUnit].rOutmodeType(g_clModelData[m_nUnit].riParameter[1]);
	g_clLaonGrabberWrapper[m_nUnit].dRi_Tdataspec.eSensorType = g_clLaonGrabberWrapper[m_nUnit].rSensortypeType(g_clModelData[m_nUnit].riParameter[2]);
	g_clLaonGrabberWrapper[m_nUnit].dRi_Tdataspec.eDemosaicMethod = g_clLaonGrabberWrapper[m_nUnit].rdemosaicmethodType(g_clModelData[m_nUnit].riParameter[3]);
	g_clLaonGrabberWrapper[m_nUnit].dRi_Tdataspec.nBlackLevel = g_clModelData[m_nUnit].m_dRiBlackLevel;
	//
}
//-----------------------------------------------------------------------------
//
//	CENTER SFR LIMIT
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal()
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
void CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal()
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
void CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal()
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
void CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal()
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
void CCcdRISpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal()
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
void CCcdRISpecDlg::OnBnClickedButtonCcdSfrSpecSave()
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

	if (g_ShowMsgModal(_T("확인"), _T("RI SPEC 데이터를 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
		return;

	this->GetRI4Spec();

	//g_clSysData.Save();
	//g_clMandoSfrSpec[m_nUnit].Save();
	g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);
	g_clModelData[m_nUnit].AcmisDataSave(g_clSysData.m_szModelName);
	AddLog(_T("[INFO] RI SPEC 저장"), 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	버튼 : CLOSE
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::OnBnClickedButtonCcdSfrSpecClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 더블 클릭
//
//-----------------------------------------------------------------------------
void CCcdRISpecDlg::OnNMDblClickedRiSpec(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridRISpec.GetItemText(nRow, nCol);
		CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
		if (pDlg != NULL)
		{
			if (pDlg->DoModal() == IDOK)
			{
				sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
				m_clGridRISpec.SetItemText(nRow, nCol, sData);

				m_clGridRISpec.Invalidate();
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
void CCcdRISpecDlg::OnLButtonDown(UINT nFlags, CPoint point)
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
BOOL CCcdRISpecDlg::PreTranslateMessage(MSG* pMsg)
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

HBRUSH CCcdRISpecDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (pWnd->GetDlgCtrlID() == IDC_CHECK_CCD_RI_8BITUSE
		)
	{
		pDC->SetTextColor(RGB_COLOR_WHITE);
		pDC->SetBkColor(RGB(100, 100, 100));
		pDC->SetBkMode(TRANSPARENT);

		return (HBRUSH)m_brCheck;
		//return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CCcdRISpecDlg::OnStnClickedStaticCcdRiBlacklevelVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticRiBlackLevelVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sPos.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticRiBlackLevelVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
	sPos.Empty();
}
