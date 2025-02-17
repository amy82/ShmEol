// CcdSfrSpecDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "CcdSfrSpecDlg.h"
#include "afxdialogex.h"


// CCcdSfrSpecDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCcdSfrSpecDlg, CDialogEx)

CCcdSfrSpecDlg::CCcdSfrSpecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCcdSfrSpecDlg::IDD, pParent)
{
	m_nUnit = UNIT_AA1;
	m_brCheck.CreateSolidBrush(RGB(45, 45, 45));
}

CCcdSfrSpecDlg::~CCcdSfrSpecDlg()
{
}

void CCcdSfrSpecDlg::DoDataExchange(CDataExchange* pDX)
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

	DDX_Control(pDX, IDC_STATIC_CCD_CURRENT_SPEC_MIN,		m_clColorStaticCurrentMin);
	DDX_Control(pDX, IDC_STATIC_CCD_CURRENT_SPEC_MIN_VAL,	m_clColorStaticCurrentMinVal);
	DDX_Control(pDX, IDC_STATIC_CCD_CURRENT_SPEC_MAX,		m_clColorStaticCurrentMax);
	DDX_Control(pDX, IDC_STATIC_CCD_CURRENT_SPEC_MAX_VAL,	m_clColorStaticCurrentMaxVal);

	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_7VAR_MIN, m_clColorStatic7VariationMin);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_7VAR_MIN_VAL, m_clColorStatic7VariationMinVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_7VAR_MAX, m_clColorStatic7VariationMax);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_7VAR_MAX_VAL, m_clColorStatic7VariationMaxVal);

	DDX_Control(pDX, IDC_STATIC_CCD_SFR_DATAFORMAT,			m_clColorStaticCcdSfrDataformat);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_OUTMODE,			m_clColorStaticCcdSfrOutmode);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SENSORTYPE,			m_clColorStaticCcdSfrSensortype);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_DEMOSAIC,			m_clColorStaticCcdSfrDemosaic);
	DDX_Control(pDX, IDC_STATIC_CONFIG_CCD_SFR_BLACKLEVEL,	m_clColorStaticCcdSfrBlacklevel);
	
		
	
	DDX_Control(pDX, IDC_CCD_SFR_COMBO_DATAFORMAT, m_CcdSfrComboDataFormat);
	DDX_Control(pDX, IDC_CCD_SFR_COMBO_OUTMODE, m_CcdSfrComboOutMode);
	DDX_Control(pDX, IDC_CCD_SFR_COMBO_SENSORTYPE, m_CcdSfrComboSensorType);
	DDX_Control(pDX, IDC_CCD_SFR_COMBO_DEMOSAIC, m_CcdSfrComboDemosaic);

	DDX_Control(pDX, IDC_STATIC_CCD_SFR_BLACKLEVEL_VAL, m_clColorStaticSfrBlackLevelVal);

	DDX_Control(pDX, IDC_BUTTON_CCD_SFR_SPEC_SAVE, m_clColorButtonSave);
	DDX_Control(pDX, IDC_BUTTON_CCD_SFR_SPEC_CLOSE, m_clColorButtonClose);

	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_DATE_PLUS, m_clColorStaticDataPlus);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_DATA_PLUS_VAL, m_clColorStaticDataPlusVal);
}


BEGIN_MESSAGE_MAP(CCcdSfrSpecDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_SFR_SPEC_GRID_SPEC, &CCcdSfrSpecDlg::OnNMDblClickedSfrSpec)
	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_SFR_SPEC_GRID_SUM_SPEC, &CCcdSfrSpecDlg::OnNMDblClickedSfrSumAveSpec)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_SAVE, &CCcdSfrSpecDlg::OnBnClickedButtonCcdSfrSpecSave)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_CLOSE, &CCcdSfrSpecDlg::OnBnClickedButtonCcdSfrSpecClose)	
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT_VAL, &CCcdSfrSpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT_VAL, &CCcdSfrSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT_VAL, &CCcdSfrSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_XY_VAL, &CCcdSfrSpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_TH_VAL, &CCcdSfrSpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal)
	ON_STN_DBLCLK(IDC_STATIC_CCD_SFR_SPEC_DATA_PLUS_VAL, &CCcdSfrSpecDlg::OnStnDblclickStaticCcdSfrSpecDataPlusVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_CURRENT_SPEC_MIN_VAL, &CCcdSfrSpecDlg::OnStnClickedStaticCcdCurrentSpecMinVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_CURRENT_SPEC_MAX_VAL, &CCcdSfrSpecDlg::OnStnClickedStaticCcdCurrentSpecMaxVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_7VAR_MIN_VAL, &CCcdSfrSpecDlg::OnStnClickedStaticCcdSfrSpec7varMinVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_7VAR_MAX_VAL, &CCcdSfrSpecDlg::OnStnClickedStaticCcdSfrSpec7varMaxVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_BLACKLEVEL_VAL, &CCcdSfrSpecDlg::OnStnClickedStaticCcdSfrBlacklevelVal)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCcdSfrSpecDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CCcdSfrSpecDlg::OnPaint()
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
BOOL CCcdSfrSpecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	// 그리드 초기화
	this->InitGridCtrl();

	this->CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdSfrSpecDlg::InitCtrl()
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


	m_clColorStaticCurrentMin.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCurrentMin.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCurrentMin.SetFont(&m_clFontSmall);

	m_clColorStaticCurrentMinVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticCurrentMinVal.SetFont(&m_clFontMid);

	m_clColorStaticSfrBlackLevelVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticSfrBlackLevelVal.SetFont(&m_clFontMid);
	
	m_clColorStaticCurrentMax.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCurrentMax.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCurrentMax.SetFont(&m_clFontSmall);

	m_clColorStaticCurrentMaxVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticCurrentMaxVal.SetFont(&m_clFontMid);

	//
	m_clColorStatic7VariationMin.SetBkColor(RGB_DLG_BG);
	m_clColorStatic7VariationMin.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStatic7VariationMin.SetFont(&m_clFontSmall);


	m_clColorStatic7VariationMinVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStatic7VariationMinVal.SetFont(&m_clFontMid);

	m_clColorStatic7VariationMax.SetBkColor(RGB_DLG_BG);
	m_clColorStatic7VariationMax.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStatic7VariationMax.SetFont(&m_clFontSmall);

	m_clColorStatic7VariationMaxVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStatic7VariationMaxVal.SetFont(&m_clFontMid);


	m_clColorStaticDataPlus.SetBkColor(RGB_DLG_BG);
	m_clColorStaticDataPlus.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticDataPlus.SetFont(&m_clFontSmall);

	m_clColorStaticDataPlusVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticDataPlusVal.SetFont(&m_clFontMid);

	m_clColorStaticCcdSfrDataformat.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdSfrDataformat.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdSfrDataformat.SetFont(&m_clFontSmall);

	m_clColorStaticCcdSfrOutmode.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdSfrOutmode.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdSfrOutmode.SetFont(&m_clFontSmall);

	m_clColorStaticCcdSfrSensortype.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdSfrSensortype.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdSfrSensortype.SetFont(&m_clFontSmall);

	m_clColorStaticCcdSfrDemosaic.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdSfrDemosaic.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdSfrDemosaic.SetFont(&m_clFontSmall);

	m_clColorStaticCcdSfrBlacklevel.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdSfrBlacklevel.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdSfrBlacklevel.SetFont(&m_clFontSmall);
	
	SetWindowTheme(GetDlgItem(IDC_CHECK_CCD_SFR_8BITUSE)->m_hWnd, L"", L"");

	/*
	1. DataFormat
	2. OutMode
	3. SensorType
	4. DemosaicMethod
	*/
	m_CcdSfrComboDataFormat.ResetContent();
	m_CcdSfrComboOutMode.ResetContent();
	m_CcdSfrComboSensorType.ResetContent();
	m_CcdSfrComboDemosaic.ResetContent();
	//
	m_CcdSfrComboDataFormat.AddString(_T("DATAFORMAT_YUV"));
	m_CcdSfrComboDataFormat.AddString(_T("DATAFORMAT_BAYER_8BIT"));
	m_CcdSfrComboDataFormat.AddString(_T("DATAFORMAT_BAYER_10BIT"));
	m_CcdSfrComboDataFormat.AddString(_T("DATAFORMAT_BAYER_PARALLEL_10BIT"));
	m_CcdSfrComboDataFormat.AddString(_T("DATAFORMAT_BAYER_12BIT"));
	m_CcdSfrComboDataFormat.AddString(_T("DATAFORMAT_BAYER_PARALLEL_12BIT"));
	m_CcdSfrComboDataFormat.AddString(_T("DATAFORMAT_BAYER_16BIT"));
	m_CcdSfrComboDataFormat.AddString(_T("DATAFORMAT_BAYER_16BIT_BE"));
	m_CcdSfrComboDataFormat.AddString(_T("DATAFORMAT_BAYER_16BIT_PWL_HDR"));
	m_CcdSfrComboDataFormat.AddString(_T("DATAFORMAT_BAYER_16BIT_PWL_DECOMP"));
	m_CcdSfrComboDataFormat.AddString(_T("DATAFORMAT_BAYER_24BIT"));
	m_CcdSfrComboDataFormat.AddString(_T("DATAFORMAT_BAYER_PARALLEL_10BIT_BE"));
	m_CcdSfrComboDataFormat.AddString(_T("DATAFORMAT_BAYER_PARALLEL_12BIT_BE"));
	m_CcdSfrComboDataFormat.AddString(_T("DATAFORMAT_RGB"));		//rgb = 100
	//
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_BGGR"));	//1
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_RGGB"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_GBRG"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_GRBG"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_BLACKWHITE"));	//1
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_YUV422_YCbYCr"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_YUV422_YCrYCb"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_YUV422_CbYCrY"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_YUV422_CrYCbY"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_RGB_BGR"));		//1
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_RGB_RGB"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_BNGR"));	//1
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_RGNB"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_NBRG"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_GRBN"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_BGGN"));	//1
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_RGGN"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_GBNG"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_GRNG"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_NGGR"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_NGGB"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_GNRG"));
	m_CcdSfrComboOutMode.AddString(_T("OUTMODE_BAYER_GNBG"));
	//
	m_CcdSfrComboSensorType.AddString(_T("SENSORTYPE_RGGB"));
	m_CcdSfrComboSensorType.AddString(_T("SENSORTYPE_RCCC"));
	m_CcdSfrComboSensorType.AddString(_T("SENSORTYPE_RCCB"));
	m_CcdSfrComboSensorType.AddString(_T("SENSORTYPE_CCCC"));
	m_CcdSfrComboSensorType.AddString(_T("SENSORTYPE_RBCC"));
	m_CcdSfrComboSensorType.AddString(_T("SENSORTYPE_OTHER"));
	m_CcdSfrComboSensorType.AddString(_T("SENSORTYPE_RGBIR2"));
	//

	m_CcdSfrComboDemosaic.AddString(_T("DEMOSAIC_NONE"));
	m_CcdSfrComboDemosaic.AddString(_T("GRADIENT"));
	m_CcdSfrComboDemosaic.AddString(_T("BL33"));
	m_CcdSfrComboDemosaic.AddString(_T("OPENCV_VNG"));
	m_CcdSfrComboDemosaic.AddString(_T("VNG"));
	m_CcdSfrComboDemosaic.AddString(_T("GR_ONLY"));
	m_CcdSfrComboDemosaic.AddString(_T("GB_ONLY"));
	m_CcdSfrComboDemosaic.AddString(_T("GBTF"));
	m_CcdSfrComboDemosaic.AddString(_T("BLLC"));
	m_CcdSfrComboDemosaic.AddString(_T("RESIDUAL"));
	m_CcdSfrComboDemosaic.AddString(_T("BAYER_Y"));
	m_CcdSfrComboDemosaic.AddString(_T("GRADIENT_RESIDUAL"));
	m_CcdSfrComboDemosaic.AddString(_T("GBTF_RESIDUAL"));
	m_CcdSfrComboDemosaic.AddString(_T("RESIDUAL_RESIDUAL"));
	m_CcdSfrComboDemosaic.AddString(_T("BL33_RESIDUAL"));
	m_CcdSfrComboDemosaic.AddString(_T("IR_ONLY"));
	m_CcdSfrComboDemosaic.AddString(_T("GRADIENT_G_ONLY"));
	m_CcdSfrComboDemosaic.AddString(_T("GBTF_G_ONLY"));
	m_CcdSfrComboDemosaic.AddString(_T("RESIDUAL_G_ONLY"));
	m_CcdSfrComboDemosaic.AddString(_T("BL33_G_ONLY"));
	m_CcdSfrComboDemosaic.AddString(_T("GRADIENT_IR_ONLY"));
	m_CcdSfrComboDemosaic.AddString(_T("GBTF_IR_ONLY"));
	m_CcdSfrComboDemosaic.AddString(_T("RESIDUAL_IR_ONLY"));
	m_CcdSfrComboDemosaic.AddString(_T("BL33_IR_ONLY"));


	m_CcdSfrComboDataFormat.SetCurSel(0);
	m_CcdSfrComboOutMode.SetCurSel(0);
	m_CcdSfrComboSensorType.SetCurSel(0);
	m_CcdSfrComboDemosaic.SetCurSel(0);

}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdSfrSpecDlg::InitGridCtrl()
{
	TCHAR* pszRow[MAX_SFR_INSP_COUNT + 1] = { _T(""),
		_T("[0] C_OF_T"), 
		_T("[1] C_OF_B"),
		_T("[2] C_OF_L"), 
		_T("[3] C_OF_R"),

		_T("[4] LT_05F_H"),
		_T("[5] LT_05F_V"),
		_T("[6] RT_05F_H"),
		_T("[7] RT_05F_V"),
		_T("[8] BL_05F_H"),
		_T("[9] BL_05F_V"),
		_T("[10] BR_05F_H"),
		_T("[11] BR_05F_V"),

		_T("[12] LT_07F_H"),
		_T("[13] LT_07F_V"),
		_T("[14] RT_07F_H"),
		_T("[15] RT_07F_V"),
		_T("[16] BL_07F_H"),
		_T("[17] BL_07F_V"),
		_T("[18] BR_07F_H"),
		_T("[19] BR_07F_V")
	};
	
	TCHAR* pszCol[] = { _T("FIELD"), _T("EOL") };
	

    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_SFR_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    int SpecRow = MAX_SFR_INSP_COUNT +1;//아래
    int SpecCol = 2;//옆
    int margin = 4;
    int gridHeight = 25;
    int gridWidth1 = 120;
    int gridWidth2 = 70;
    int totalWidth = gridWidth1 + (gridWidth2*(SpecCol - 1));
    //
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + margin;
    rect.bottom = (gridHeight*SpecRow) + margin;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.


	GetDlgItem(DLG)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_clGridSfrSpec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

	m_clGridSfrSpec.SetTextBkColor(RGB_COLOR_WHITE);
	m_clGridSfrSpec.SetFixedBkColor(GRID_COLOR_TITLE);
	m_clGridSfrSpec.SetFixedTextColor(RGB_COLOR_WHITE);
	m_clGridSfrSpec.SetReference_Setting();
	m_clGridSfrSpec.EnableSelection(FALSE);
	m_clGridSfrSpec.SetRowCount(SpecRow);
	m_clGridSfrSpec.SetColumnCount(SpecCol);
	m_clGridSfrSpec.SetFixedRowCount(1);
	m_clGridSfrSpec.SetFixedColumnCount(1);

	for (i = 0; i < SpecRow; i++)
	{
		m_clGridSfrSpec.SetRowHeight(i, gridHeight);
		m_clGridSfrSpec.SetItemText(i, 0, pszRow[i]);

		for (j = 0; j < SpecCol; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					m_clGridSfrSpec.SetColumnWidth(j, gridWidth1);
				}
				else
				{
					m_clGridSfrSpec.SetColumnWidth(j, gridWidth2);
				}

				m_clGridSfrSpec.SetItemText(i, j, pszCol[j]);
			}

			m_clGridSfrSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}

	pWnd = NULL;
	delete pWnd;
	
	CString sData;
	sData.Format(_T("%.5f"), g_clMandoSfrSpec[m_nUnit].m_dSfrOffsetMultiply);
	
	GetDlgItem(IDC_STATIC_CCD_SFR_SPEC_DATA_PLUS_VAL)->SetWindowText(sData);

}

//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CCcdSfrSpecDlg::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}

//-----------------------------------------------------------------------------
//
//	OnShowWindow
//
//-----------------------------------------------------------------------------
void CCcdSfrSpecDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
		this->ShowSfrSpec();
		GetDlgItem(IDC_STATIC_CCD_SFR_SPEC_DATE_PLUS)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_CCD_SFR_SPEC_DATA_PLUS_VAL)->ShowWindow(false);
	}
}

//-----------------------------------------------------------------------------
//
//	SFR 데이터 -> 메모리에 저장
//
//-----------------------------------------------------------------------------
void CCcdSfrSpecDlg::GetSfrSpec()
{
    CString sData = _T("");
	CButton* pButton;
    int i;

	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
    {
		sData = m_clGridSfrSpec.GetItemText(i + 1, 1);
		g_clMandoSfrSpec[m_nUnit].m_dAASFR_Spec[i][0] = _ttof((TCHAR*)(LPCTSTR)sData);
    }

	GetDlgItem(IDC_STATIC_CCD_CURRENT_SPEC_MIN_VAL)->GetWindowText(sData);
	g_clModelData[m_nUnit].m_CurrentSpec[0] = _ttof((TCHAR*)(LPCTSTR)sData);

	GetDlgItem(IDC_STATIC_CCD_CURRENT_SPEC_MAX_VAL)->GetWindowText(sData);
	g_clModelData[m_nUnit].m_CurrentSpec[1] = _ttof((TCHAR*)(LPCTSTR)sData);

	GetDlgItem(IDC_STATIC_CCD_SFR_SPEC_7VAR_MIN_VAL)->GetWindowText(sData);
	g_clModelData[m_nUnit].m_7FVariation[0] = _ttof((TCHAR*)(LPCTSTR)sData);

	GetDlgItem(IDC_STATIC_CCD_SFR_SPEC_7VAR_MAX_VAL)->GetWindowText(sData);
	g_clModelData[m_nUnit].m_7FVariation[1] = _ttof((TCHAR*)(LPCTSTR)sData);

	
	GetDlgItem(IDC_STATIC_CCD_SFR_BLACKLEVEL_VAL)->GetWindowText(sData);
	g_clModelData[m_nUnit].m_dSfrBlackLevel = _ttoi((TCHAR*)(LPCTSTR)sData);


	//int sfrParameter[4];	
	//0.DataFormat
	//1.OutMode
	//2.SensorType
	//3.DemosaicMethod

	pButton = (CButton*)GetDlgItem(IDC_CHECK_CCD_SFR_8BITUSE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nSfr8BitUse = 1;
	else
		g_clModelData[m_nUnit].m_nSfr8BitUse = 0;


	g_clModelData[m_nUnit].sfrParameter[0] = m_CcdSfrComboDataFormat.GetCurSel();
	g_clModelData[m_nUnit].sfrParameter[1] = m_CcdSfrComboOutMode.GetCurSel();
	g_clModelData[m_nUnit].sfrParameter[2] = m_CcdSfrComboSensorType.GetCurSel();
	g_clModelData[m_nUnit].sfrParameter[3] = m_CcdSfrComboDemosaic.GetCurSel();

	g_clLaonGrabberWrapper[m_nUnit].dSfr_Tdataspec.eDataFormat = g_clLaonGrabberWrapper[m_nUnit].rDataFormatType(g_clModelData[m_nUnit].sfrParameter[0]);
	g_clLaonGrabberWrapper[m_nUnit].dSfr_Tdataspec.eOutMode = g_clLaonGrabberWrapper[m_nUnit].rOutmodeType(g_clModelData[m_nUnit].sfrParameter[1]);
	g_clLaonGrabberWrapper[m_nUnit].dSfr_Tdataspec.eSensorType = g_clLaonGrabberWrapper[m_nUnit].rSensortypeType(g_clModelData[m_nUnit].sfrParameter[2]);
	g_clLaonGrabberWrapper[m_nUnit].dSfr_Tdataspec.eDemosaicMethod = g_clLaonGrabberWrapper[m_nUnit].rdemosaicmethodType(g_clModelData[m_nUnit].sfrParameter[3]);
	g_clLaonGrabberWrapper[m_nUnit].dSfr_Tdataspec.nBlackLevel = g_clModelData[m_nUnit].m_dSfrBlackLevel;
	//
	//
	sData.Empty();
}

//-----------------------------------------------------------------------------
//
//	SFR SPEC 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdSfrSpecDlg::ShowSfrSpec()
{
	TCHAR szData[SIZE_OF_100BYTE];
	CButton* pButton;
	int i;


	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_CurrentSpec[0]);
	m_clColorStaticCurrentMinVal.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_CurrentSpec[1]);
	m_clColorStaticCurrentMaxVal.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_7FVariation[0]);
	m_clColorStatic7VariationMinVal.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_7FVariation[1]);
	m_clColorStatic7VariationMaxVal.SetWindowText(szData);
	
	for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
	{
		m_clGridSfrSpec.SetItemText(i + 1, 1, g_clMandoSfrSpec[m_nUnit].m_dAASFR_Spec[i][0], 3);
	}




	m_clGridSfrSpec.Invalidate();
	
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CCD_SFR_8BITUSE);
	if (g_clModelData[m_nUnit].m_nSfr8BitUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_dSfrBlackLevel);
	m_clColorStaticSfrBlackLevelVal.SetWindowText(szData);

	m_CcdSfrComboDataFormat.SetCurSel(g_clModelData[m_nUnit].sfrParameter[0]);
	m_CcdSfrComboOutMode.SetCurSel(g_clModelData[m_nUnit].sfrParameter[1]);
	m_CcdSfrComboSensorType.SetCurSel(g_clModelData[m_nUnit].sfrParameter[2]);
	m_CcdSfrComboDemosaic.SetCurSel(g_clModelData[m_nUnit].sfrParameter[3]);
}

//-----------------------------------------------------------------------------
//
//	CENTER SFR LIMIT
//
//-----------------------------------------------------------------------------
void CCcdSfrSpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal()
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
void CCcdSfrSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal()
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
void CCcdSfrSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal()
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
void CCcdSfrSpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal()
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
void CCcdSfrSpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal()
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
void CCcdSfrSpecDlg::OnBnClickedButtonCcdSfrSpecSave()
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
	if (g_ShowMsgModal(_T("확인"), _T("SFR SPEC 데이터를 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
		return;

	this->GetSfrSpec();

	g_clSysData.sDSave();
	g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);
	g_clModelData[m_nUnit].AcmisDataSave(g_clSysData.m_szModelName);
	g_clMandoSfrSpec[m_nUnit].Save();

	AddLog(_T("[INFO] SFR SPEC 저장"), 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	버튼 : CLOSE
//
//-----------------------------------------------------------------------------
void CCcdSfrSpecDlg::OnBnClickedButtonCcdSfrSpecClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 더블 클릭
//
//-----------------------------------------------------------------------------
void CCcdSfrSpecDlg::OnNMDblClickedSfrSpec(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;
	
	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridSfrSpec.GetItemText(nRow, nCol);
		CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
		if (pDlg != NULL)
		{
			if (pDlg->DoModal() == IDOK)
			{
				sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
				m_clGridSfrSpec.SetItemText(nRow, nCol, sData);

				m_clGridSfrSpec.Invalidate();
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
void CCcdSfrSpecDlg::OnNMDblClickedSfrSumAveSpec(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
	CString sData = _T("");
	int nRow, nCol;

	nRow = pNMGridView->iRow;
	nCol = pNMGridView->iColumn;

	if (nRow == 0 && nCol == 0)
	{
		GetDlgItem(IDC_STATIC_CCD_SFR_SPEC_DATE_PLUS)->ShowWindow(true);
		GetDlgItem(IDC_STATIC_CCD_SFR_SPEC_DATA_PLUS_VAL)->ShowWindow(true);
	}

	if (nRow >= 1 && nCol >= 1)
	{
		sData = m_clGridSfrSumAveSpec.GetItemText(nRow, nCol);
		CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
		if (pDlg != NULL)
		{
			if (pDlg->DoModal() == IDOK)
			{
				sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
				m_clGridSfrSumAveSpec.SetItemText(nRow, nCol, sData);

				m_clGridSfrSumAveSpec.Invalidate();
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
void CCcdSfrSpecDlg::OnLButtonDown(UINT nFlags, CPoint point)
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
BOOL CCcdSfrSpecDlg::PreTranslateMessage(MSG* pMsg)
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

void CCcdSfrSpecDlg::OnStnDblclickStaticCcdSfrSpecDataPlusVal()
{
	CString sData = _T("");

	GetDlgItem(IDC_STATIC_CCD_SFR_SPEC_DATA_PLUS_VAL)->GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			GetDlgItem(IDC_STATIC_CCD_SFR_SPEC_DATA_PLUS_VAL)->SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CCcdSfrSpecDlg::OnStnClickedStaticCcdCurrentSpecMinVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticCurrentMinVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sPos.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticCurrentMinVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
	sPos.Empty();
}


void CCcdSfrSpecDlg::OnStnClickedStaticCcdCurrentSpecMaxVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticCurrentMaxVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sPos.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticCurrentMaxVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
	sPos.Empty();
}


void CCcdSfrSpecDlg::OnStnClickedStaticCcdSfrSpec7varMinVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStatic7VariationMinVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sPos.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStatic7VariationMinVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
	sPos.Empty();
}


void CCcdSfrSpecDlg::OnStnClickedStaticCcdSfrSpec7varMaxVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStatic7VariationMaxVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sPos.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStatic7VariationMaxVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
	sPos.Empty();
}


void CCcdSfrSpecDlg::OnStnClickedStaticCcdSfrBlacklevelVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticSfrBlackLevelVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sPos.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticSfrBlackLevelVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
	sPos.Empty();
}


HBRUSH CCcdSfrSpecDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (pWnd->GetDlgCtrlID() == IDC_CHECK_CCD_SFR_8BITUSE
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
