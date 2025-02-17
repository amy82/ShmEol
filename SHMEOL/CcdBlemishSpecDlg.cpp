// CcdSfrSpecDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "CcdBlemishSpecDlg.h"
#include "afxdialogex.h"


// CCcdBlemishSpecDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCcdBlemishSpecDlg, CDialogEx)

CCcdBlemishSpecDlg::CCcdBlemishSpecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCcdBlemishSpecDlg::IDD, pParent)
{
	m_nUnit = UNIT_AA1;
	m_brCheck.CreateSolidBrush(RGB(45, 45, 45));
}

CCcdBlemishSpecDlg::~CCcdBlemishSpecDlg()
{
}

void CCcdBlemishSpecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_TOP_BAR, m_clColorStaticTopBar);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT, m_clColorStaticCenterSfrLimit);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT_VAL, m_clColorStaticCenterSfrLimitVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT, m_clColorStaticCornerSfrLimit);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT_VAL, m_clColorStaticCornerSfrLimitVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT, m_clColorStaticCornerSfrDeviationLimit);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT_VAL, m_clColorStaticCornerSfrDeviationLimitVal);
	DDX_Control(pDX, IDC_STATIC_CCD_LCB_SPEC_OFFSET, m_clColorStaticLcbOffset);
	DDX_Control(pDX, IDC_STATIC_CCD_YMEAN_SPEC_OFFSET, m_clColorStaticYmeanOffset);
	DDX_Control(pDX, IDC_STATIC_CCD_FDF_SPEC_OFFSET, m_clColorStaticFdfOffset);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_XY_VAL, m_clColorStaticOCXYVal);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_TH, m_clColorStaticOCTh);
	DDX_Control(pDX, IDC_STATIC_CCD_SFR_SPEC_OC_TH_VAL, m_clColorStaticOCThVal);
	DDX_Control(pDX, IDC_BUTTON_CCD_SFR_SPEC_SAVE, m_clColorButtonSave);
	DDX_Control(pDX, IDC_BUTTON_CCD_SFR_SPEC_CLOSE, m_clColorButtonClose);
	//
	DDX_Control(pDX, IDC_LCB_OFFSET, m_clLcbOffset);
	DDX_Control(pDX, IDC_YMEAN_OFFSET, m_clYmeanOffset);
	DDX_Control(pDX, IDC_FDF_OFFSET, m_clFdfOffset);
	
	DDX_Control(pDX, IDC_STATIC_CCD_BLEMISH_BLACKLEVEL_VAL, m_clColorStaticBlemishBlackLevelVal);

	DDX_Control(pDX, IDC_STATIC_CCD_BLEMISH_DATAFORMAT, m_clColorStaticCcdBlemishDataformat);
	DDX_Control(pDX, IDC_STATIC_CCD_BLEMISH_OUTMODE, m_clColorStaticCcdBlemishOutmode);
	DDX_Control(pDX, IDC_STATIC_CCD_BLEMISH_SENSORTYPE, m_clColorStaticCcdBlemishSensortype);
	DDX_Control(pDX, IDC_STATIC_CCD_BLEMISH_DEMOSAIC,				m_clColorStaticCcdBlemishDemosaic);
	DDX_Control(pDX, IDC_STATIC_CONFIG_CCD_BLEMISH_BLACKLEVEL,	m_clColorStaticCcdBlemishBlacklevel);

	DDX_Control(pDX, IDC_CCD_BLEMISH_COMBO_DATAFORMAT, m_CcdBlemishComboDataFormat);
	DDX_Control(pDX, IDC_CCD_BLEMISH_COMBO_OUTMODE, m_CcdBlemishComboOutMode);
	DDX_Control(pDX, IDC_CCD_BLEMISH_COMBO_SENSORTYPE, m_CcdBlemishComboSensorType);
	DDX_Control(pDX, IDC_CCD_BLEMISH_COMBO_DEMOSAIC, m_CcdBlemishComboDemosaic);
}


BEGIN_MESSAGE_MAP(CCcdBlemishSpecDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_BLEMISH_SPEC_GRID_SPEC, &CCcdBlemishSpecDlg::OnNMDblClickedSfrBlockspot)
    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_LCB_SPEC_GRID_SPEC, &CCcdBlemishSpecDlg::OnNMDblClickedSfrLcb)
    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_CCD_YMEAN_SPEC_GRID_SPEC, &CCcdBlemishSpecDlg::OnNMDblClickedSfrYmean)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_SAVE, &CCcdBlemishSpecDlg::OnBnClickedButtonCcdSfrSpecSave)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC_CLOSE, &CCcdBlemishSpecDlg::OnBnClickedButtonCcdSfrSpecClose)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CENTER_SFR_LIMIT_VAL, &CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_LIMIT_VAL, &CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_CORNER_SFR_DEVIATION_LIMIT_VAL, &CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_XY_VAL, &CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_SFR_SPEC_OC_TH_VAL, &CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal)
	ON_STN_CLICKED(IDC_STATIC_CCD_BLEMISH_BLACKLEVEL_VAL, &CCcdBlemishSpecDlg::OnStnClickedStaticCcdBlemishBlacklevelVal)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCcdBlemishSpecDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::OnPaint()
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
BOOL CCcdBlemishSpecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();

	// 그리드 초기화
    this->InitBlemishGridCtrl();
    this->InitLcbGridCtrl();
    this->InitYmeanGridCtrl();

    
	this->CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::InitCtrl()
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

	m_clColorStaticLcbOffset.SetBkColor(RGB_DLG_BG);
	m_clColorStaticLcbOffset.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticLcbOffset.SetFont(&m_clFontSmall);

	m_clColorStaticYmeanOffset.SetBkColor(RGB_DLG_BG);
	m_clColorStaticYmeanOffset.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticYmeanOffset.SetFont(&m_clFontSmall);

	m_clColorStaticFdfOffset.SetBkColor(RGB_DLG_BG);
	m_clColorStaticFdfOffset.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticFdfOffset.SetFont(&m_clFontSmall);

	m_clColorStaticOCXYVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOCXYVal.SetFont(&m_clFontMid);

	m_clColorStaticOCTh.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOCTh.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOCTh.SetFont(&m_clFontSmall);

	m_clColorStaticOCThVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOCThVal.SetFont(&m_clFontMid);

	m_clColorStaticBlemishBlackLevelVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticBlemishBlackLevelVal.SetFont(&m_clFontMid);

	m_clColorStaticCcdBlemishDataformat.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdBlemishDataformat.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdBlemishDataformat.SetFont(&m_clFontSmall);

	m_clColorStaticCcdBlemishOutmode.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdBlemishOutmode.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdBlemishOutmode.SetFont(&m_clFontSmall);

	m_clColorStaticCcdBlemishSensortype.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdBlemishSensortype.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdBlemishSensortype.SetFont(&m_clFontSmall);

	m_clColorStaticCcdBlemishDemosaic.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdBlemishDemosaic.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdBlemishDemosaic.SetFont(&m_clFontSmall);

	m_clColorStaticCcdBlemishBlacklevel.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdBlemishBlacklevel.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdBlemishBlacklevel.SetFont(&m_clFontSmall);

	SetWindowTheme(GetDlgItem(IDC_CHECK_CCD_BLEMISH_8BITUSE)->m_hWnd, L"", L"");

	/*
	1. DataFormat
	2. OutMode
	3. SensorType
	4. DemosaicMethod
	*/
	m_CcdBlemishComboDataFormat.ResetContent();
	m_CcdBlemishComboOutMode.ResetContent();
	m_CcdBlemishComboSensorType.ResetContent();
	m_CcdBlemishComboDemosaic.ResetContent();
	//
	m_CcdBlemishComboDataFormat.AddString(_T("DATAFORMAT_YUV"));
	m_CcdBlemishComboDataFormat.AddString(_T("DATAFORMAT_BAYER_8BIT"));
	m_CcdBlemishComboDataFormat.AddString(_T("DATAFORMAT_BAYER_10BIT"));
	m_CcdBlemishComboDataFormat.AddString(_T("DATAFORMAT_BAYER_PARALLEL_10BIT"));
	m_CcdBlemishComboDataFormat.AddString(_T("DATAFORMAT_BAYER_12BIT"));
	m_CcdBlemishComboDataFormat.AddString(_T("DATAFORMAT_BAYER_PARALLEL_12BIT"));
	m_CcdBlemishComboDataFormat.AddString(_T("DATAFORMAT_BAYER_16BIT"));
	m_CcdBlemishComboDataFormat.AddString(_T("DATAFORMAT_BAYER_16BIT_BE"));
	m_CcdBlemishComboDataFormat.AddString(_T("DATAFORMAT_BAYER_16BIT_PWL_HDR"));
	m_CcdBlemishComboDataFormat.AddString(_T("DATAFORMAT_BAYER_16BIT_PWL_DECOMP"));
	m_CcdBlemishComboDataFormat.AddString(_T("DATAFORMAT_BAYER_24BIT"));
	m_CcdBlemishComboDataFormat.AddString(_T("DATAFORMAT_BAYER_PARALLEL_10BIT_BE"));
	m_CcdBlemishComboDataFormat.AddString(_T("DATAFORMAT_BAYER_PARALLEL_12BIT_BE"));
	m_CcdBlemishComboDataFormat.AddString(_T("DATAFORMAT_RGB"));		//rgb = 100
																	//
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_BGGR"));	//1
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_RGGB"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_GBRG"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_GRBG"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_BLACKWHITE"));	//1
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_YUV422_YCbYCr"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_YUV422_YCrYCb"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_YUV422_CbYCrY"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_YUV422_CrYCbY"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_RGB_BGR"));		//1
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_RGB_RGB"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_BNGR"));	//1
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_RGNB"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_NBRG"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_GRBN"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_BGGN"));	//1
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_RGGN"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_GBNG"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_GRNG"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_NGGR"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_NGGB"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_GNRG"));
	m_CcdBlemishComboOutMode.AddString(_T("OUTMODE_BAYER_GNBG"));
	//
	m_CcdBlemishComboSensorType.AddString(_T("SENSORTYPE_RGGB"));
	m_CcdBlemishComboSensorType.AddString(_T("SENSORTYPE_RCCC"));
	m_CcdBlemishComboSensorType.AddString(_T("SENSORTYPE_RCCB"));
	m_CcdBlemishComboSensorType.AddString(_T("SENSORTYPE_CCCC"));
	m_CcdBlemishComboSensorType.AddString(_T("SENSORTYPE_RBCC"));
	m_CcdBlemishComboSensorType.AddString(_T("SENSORTYPE_OTHER"));
	m_CcdBlemishComboSensorType.AddString(_T("SENSORTYPE_RGBIR2"));
	//

	m_CcdBlemishComboDemosaic.AddString(_T("DEMOSAIC_NONE"));
	m_CcdBlemishComboDemosaic.AddString(_T("GRADIENT"));
	m_CcdBlemishComboDemosaic.AddString(_T("BL33"));
	m_CcdBlemishComboDemosaic.AddString(_T("OPENCV_VNG"));
	m_CcdBlemishComboDemosaic.AddString(_T("VNG"));
	m_CcdBlemishComboDemosaic.AddString(_T("GR_ONLY"));
	m_CcdBlemishComboDemosaic.AddString(_T("GB_ONLY"));
	m_CcdBlemishComboDemosaic.AddString(_T("GBTF"));
	m_CcdBlemishComboDemosaic.AddString(_T("BLLC"));
	m_CcdBlemishComboDemosaic.AddString(_T("RESIDUAL"));
	m_CcdBlemishComboDemosaic.AddString(_T("BAYER_Y"));
	m_CcdBlemishComboDemosaic.AddString(_T("GRADIENT_RESIDUAL"));
	m_CcdBlemishComboDemosaic.AddString(_T("GBTF_RESIDUAL"));
	m_CcdBlemishComboDemosaic.AddString(_T("RESIDUAL_RESIDUAL"));
	m_CcdBlemishComboDemosaic.AddString(_T("BL33_RESIDUAL"));
	m_CcdBlemishComboDemosaic.AddString(_T("IR_ONLY"));
	m_CcdBlemishComboDemosaic.AddString(_T("GRADIENT_G_ONLY"));
	m_CcdBlemishComboDemosaic.AddString(_T("GBTF_G_ONLY"));
	m_CcdBlemishComboDemosaic.AddString(_T("RESIDUAL_G_ONLY"));
	m_CcdBlemishComboDemosaic.AddString(_T("BL33_G_ONLY"));
	m_CcdBlemishComboDemosaic.AddString(_T("GRADIENT_IR_ONLY"));
	m_CcdBlemishComboDemosaic.AddString(_T("GBTF_IR_ONLY"));
	m_CcdBlemishComboDemosaic.AddString(_T("RESIDUAL_IR_ONLY"));
	m_CcdBlemishComboDemosaic.AddString(_T("BL33_IR_ONLY"));


	m_CcdBlemishComboDataFormat.SetCurSel(0);
	m_CcdBlemishComboOutMode.SetCurSel(0);
	m_CcdBlemishComboSensorType.SetCurSel(0);
	m_CcdBlemishComboDemosaic.SetCurSel(0);
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::InitBlemishGridCtrl()
{
    TCHAR* pszCol[] = { _T("FDF"), _T("Spec") };

    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_BLEMISH_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	int SpecRow = g_StainFdfcount + 1;// sizeof(STAIN_FDF_SPEC_NAME) / sizeof(STAIN_FDF_SPEC_NAME[0]) + 1;//아래
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
    m_clGridBlemishSpec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridBlemishSpec.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridBlemishSpec.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridBlemishSpec.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridBlemishSpec.SetReference_Setting();
    m_clGridBlemishSpec.EnableSelection(FALSE);
    m_clGridBlemishSpec.SetRowCount(SpecRow);
    m_clGridBlemishSpec.SetColumnCount(SpecCol);
    m_clGridBlemishSpec.SetFixedRowCount(1);
    m_clGridBlemishSpec.SetFixedColumnCount(1);

    for (i = 0; i < SpecRow; i++)
    {
        m_clGridBlemishSpec.SetRowHeight(i, gridHeight);
        m_clGridBlemishSpec.SetItemText(i + 1, 0, STAIN_FDF_SPEC_NAME[i]);

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGridBlemishSpec.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridBlemishSpec.SetColumnWidth(j, gridWidth2);
                }

                m_clGridBlemishSpec.SetItemText(i, j, pszCol[j]);
            }

            m_clGridBlemishSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}
void CCcdBlemishSpecDlg::InitLcbGridCtrl()
{
    TCHAR* pszCol[] = { _T("Lcb"), _T("Spec") };

    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_LCB_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
	int SpecRow = g_StainLcbcount + 1;// sizeof(STAIN_LCB_SPEC_NAME) / sizeof(STAIN_LCB_SPEC_NAME[0]) + 1;//아래
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
    m_clGridLcbSpec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridLcbSpec.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridLcbSpec.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridLcbSpec.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridLcbSpec.SetReference_Setting();
    m_clGridLcbSpec.EnableSelection(FALSE);
    m_clGridLcbSpec.SetRowCount(SpecRow);
    m_clGridLcbSpec.SetColumnCount(SpecCol);
    m_clGridLcbSpec.SetFixedRowCount(1);
    m_clGridLcbSpec.SetFixedColumnCount(1);

    for (i = 0; i < SpecRow; i++)
    {
        m_clGridLcbSpec.SetRowHeight(i, gridHeight);
        m_clGridLcbSpec.SetItemText(i + 1, 0, STAIN_LCB_SPEC_NAME[i]);

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGridLcbSpec.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridLcbSpec.SetColumnWidth(j, gridWidth2);
                }

                m_clGridLcbSpec.SetItemText(i, j, pszCol[j]);
            }

            m_clGridLcbSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}
void CCcdBlemishSpecDlg::InitYmeanGridCtrl()
{
    TCHAR* pszRow[] = { _T("") ,
        _T("AnEdgeSize"), _T("AdCenterThreshold"), _T("AdEdgeThreshold"), _T("AdCornerThreshold"),
        _T("AnDefecBlockSize"), _T("AnLscBlockSize"), _T("AnCalcType"),
        _T("AnnMaxRecursiveCount"), _T("AdMaxDefectSize"), _T("AdPixelSize"),
        _T("AbEnableCircle"), _T("AnPosOffsetX"), _T("AnPosOffsetY"),
        _T("AdRadiusRatioX"), _T("AdRadiusRatioY"), _T("AdThresholdRatio"),
        _T("AdROIRange"), _T("AnUsedFixedCircle"), _T("AbEnableMultiCircle"),
        _T("dZoneSizeRatio1") ,_T("dZoneSizeRatio2"), _T("dZoneSizeRatio3"),
        _T("dThreshold1") ,_T("dThreshold2"), _T("dThreshold3")
    };

    TCHAR* pszCol[] = { _T("Ymean"), _T("Spec") };

    CRect rect;
    int i, j;
    int DLG = IDC_STATIC_CCD_YMEAN_SPEC_GRID_SPEC;

    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    int SpecRow = sizeof(STAIN_YMEAN_SPEC_NAME) / sizeof(STAIN_YMEAN_SPEC_NAME[0]) + 1;//아래
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
    m_clGridYmenaSpec.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridYmenaSpec.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridYmenaSpec.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridYmenaSpec.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridYmenaSpec.SetReference_Setting();
    m_clGridYmenaSpec.EnableSelection(FALSE);
    m_clGridYmenaSpec.SetRowCount(SpecRow);
    m_clGridYmenaSpec.SetColumnCount(SpecCol);
    m_clGridYmenaSpec.SetFixedRowCount(1);
    m_clGridYmenaSpec.SetFixedColumnCount(1);

    for (i = 0; i < SpecRow; i++)
    {
        m_clGridYmenaSpec.SetRowHeight(i, gridHeight);
        m_clGridYmenaSpec.SetItemText(i + 1, 0, STAIN_YMEAN_SPEC_NAME[i]);

        for (j = 0; j < SpecCol; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGridYmenaSpec.SetColumnWidth(j, gridWidth1);
                }
                else
                {
                    m_clGridYmenaSpec.SetColumnWidth(j, gridWidth2);
                }

                m_clGridYmenaSpec.SetItemText(i, j, pszCol[j]);
            }

            m_clGridYmenaSpec.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}
//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}

//-----------------------------------------------------------------------------
//
//	OnShowWindow
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
        this->ShowFdfSpec();
        this->ShowLcbSpec();
        this->ShowYmeanSpec();
	}
}

//-----------------------------------------------------------------------------
//
//	SFR SPEC 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::ShowFdfSpec()
{
	TCHAR szData[SIZE_OF_100BYTE];
	int i;


	for (i = 0; i < g_StainFdfcount; i++)
	{
		m_clGridBlemishSpec.SetItemText(i + 1, 1, g_clModelData[m_nUnit].m_FDFSpec[i], 3);
	}
	m_clFdfOffset.SetAddress(g_clModelData[m_nUnit].m_FDFOffsetSpec[0], g_clModelData[m_nUnit].m_FDFOffsetSpec[1], g_clModelData[m_nUnit].m_FDFOffsetSpec[2], g_clModelData[m_nUnit].m_FDFOffsetSpec[3]);

	m_clGridBlemishSpec.Invalidate();
}
void CCcdBlemishSpecDlg::ShowLcbSpec()
{
    TCHAR szData[SIZE_OF_100BYTE];
    int i;

    for (i = 0; i < g_StainLcbcount; i++)
    {
        m_clGridLcbSpec.SetItemText(i + 1, 1, g_clModelData[m_nUnit].m_LcbSpec[i], 3);
    }

	m_clLcbOffset.SetAddress(g_clModelData[m_nUnit].m_LcbOffsetSpec[0], g_clModelData[m_nUnit].m_LcbOffsetSpec[1], g_clModelData[m_nUnit].m_LcbOffsetSpec[2], g_clModelData[m_nUnit].m_LcbOffsetSpec[3]);
    m_clGridLcbSpec.Invalidate();
}
void CCcdBlemishSpecDlg::ShowYmeanSpec()
{
    TCHAR szData[SIZE_OF_100BYTE];
	CButton* pButton;
    int i;

    for (i = 0; i < g_StainYmeancount; i++)
    {
        m_clGridYmenaSpec.SetItemText(i + 1, 1, g_clModelData[m_nUnit].m_YmeanSpec[i], 3);
    }
	m_clYmeanOffset.SetAddress(g_clModelData[m_nUnit].m_YmeanOffsetSpec[0], g_clModelData[m_nUnit].m_YmeanOffsetSpec[1], g_clModelData[m_nUnit].m_YmeanOffsetSpec[2], g_clModelData[m_nUnit].m_YmeanOffsetSpec[3]);
    m_clGridYmenaSpec.Invalidate();

	pButton = (CButton*)GetDlgItem(IDC_CHECK_CCD_BLEMISH_8BITUSE);
	if (g_clModelData[m_nUnit].m_nBlemish8BitUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_dBlemishBlackLevel);
	m_clColorStaticBlemishBlackLevelVal.SetWindowText(szData);

	m_CcdBlemishComboDataFormat.SetCurSel(g_clModelData[m_nUnit].blemishParameter[0]);
	m_CcdBlemishComboOutMode.SetCurSel(g_clModelData[m_nUnit].blemishParameter[1]);
	m_CcdBlemishComboSensorType.SetCurSel(g_clModelData[m_nUnit].blemishParameter[2]);
	m_CcdBlemishComboDemosaic.SetCurSel(g_clModelData[m_nUnit].blemishParameter[3]);
}


//-----------------------------------------------------------------------------
//
//	SFR 데이터 -> 메모리에 저장
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::GetFdfSpec()
{
    CString sData = _T("");
    int i;

	for (i = 0; i < g_StainFdfcount; i++)
	{
		sData = m_clGridBlemishSpec.GetItemText(i + 1, 1);
		g_clModelData[m_nUnit].m_FDFSpec[i] = _ttof((TCHAR*)(LPCTSTR)sData);
	}

	BYTE ipData[4];
	m_clFdfOffset.GetAddress(ipData[0], ipData[1], ipData[2], ipData[3]);
	for (i = 0; i < 4; i++)
	{
		g_clModelData[m_nUnit].m_FDFOffsetSpec[i] = ipData[i];
	}

    g_clSysData.sDSave();
}
void CCcdBlemishSpecDlg::GetLcbSpec()
{
    CString sData = _T("");
    int i;

    for (i = 0; i < g_StainLcbcount; i++)
    {
        sData = m_clGridLcbSpec.GetItemText(i + 1, 1);
        g_clModelData[m_nUnit].m_LcbSpec[i] = _ttof((TCHAR*)(LPCTSTR)sData);
    }
	BYTE ipData[4];
	m_clLcbOffset.GetAddress(ipData[0], ipData[1], ipData[2], ipData[3]);
	for (i = 0; i < 4; i++)
	{
		g_clModelData[m_nUnit].m_LcbOffsetSpec[i] = ipData[i];
	}
    g_clSysData.sDSave();
}
void CCcdBlemishSpecDlg::GetYmeanSpec()
{
    CString sData = _T("");
	CButton* pButton;
    int i;
    for (i = 0; i < g_StainYmeancount; i++)
    {
        sData = m_clGridYmenaSpec.GetItemText(i + 1, 1);
        g_clModelData[m_nUnit].m_YmeanSpec[i] = _ttof((TCHAR*)(LPCTSTR)sData);
    }
	BYTE ipData[4];
	m_clYmeanOffset.GetAddress(ipData[0], ipData[1], ipData[2], ipData[3]);
	for (i = 0; i < 4; i++)
	{
		g_clModelData[m_nUnit].m_YmeanOffsetSpec[i] = ipData[i];
	}
    g_clSysData.sDSave();

	GetDlgItem(IDC_STATIC_CCD_BLEMISH_BLACKLEVEL_VAL)->GetWindowText(sData);
	g_clModelData[m_nUnit].m_dBlemishBlackLevel = _ttoi((TCHAR*)(LPCTSTR)sData);

	pButton = (CButton*)GetDlgItem(IDC_CHECK_CCD_BLEMISH_8BITUSE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nBlemish8BitUse = 1;
	else
		g_clModelData[m_nUnit].m_nBlemish8BitUse = 0;


	g_clModelData[m_nUnit].blemishParameter[0] = m_CcdBlemishComboDataFormat.GetCurSel();
	g_clModelData[m_nUnit].blemishParameter[1] = m_CcdBlemishComboOutMode.GetCurSel();
	g_clModelData[m_nUnit].blemishParameter[2] = m_CcdBlemishComboSensorType.GetCurSel();
	g_clModelData[m_nUnit].blemishParameter[3] = m_CcdBlemishComboDemosaic.GetCurSel();

	g_clLaonGrabberWrapper[m_nUnit].dBlemish_Tdataspec.eDataFormat = g_clLaonGrabberWrapper[m_nUnit].rDataFormatType(g_clModelData[m_nUnit].blemishParameter[0]);
	g_clLaonGrabberWrapper[m_nUnit].dBlemish_Tdataspec.eOutMode = g_clLaonGrabberWrapper[m_nUnit].rOutmodeType(g_clModelData[m_nUnit].blemishParameter[1]);
	g_clLaonGrabberWrapper[m_nUnit].dBlemish_Tdataspec.eSensorType = g_clLaonGrabberWrapper[m_nUnit].rSensortypeType(g_clModelData[m_nUnit].blemishParameter[2]);
	g_clLaonGrabberWrapper[m_nUnit].dBlemish_Tdataspec.eDemosaicMethod = g_clLaonGrabberWrapper[m_nUnit].rdemosaicmethodType(g_clModelData[m_nUnit].blemishParameter[3]);
	g_clLaonGrabberWrapper[m_nUnit].dBlemish_Tdataspec.nBlackLevel = g_clModelData[m_nUnit].m_dBlemishBlackLevel;

}
//---------------------------------------------------------------------------
//
//	CENTER SFR LIMIT
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal()
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
void CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal()
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
void CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal()
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
void CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecOcXyVal()
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
void CCcdBlemishSpecDlg::OnStnClickedStaticCcdSfrSpecOcThVal()
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
void CCcdBlemishSpecDlg::OnBnClickedButtonCcdSfrSpecSave()
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

	if (g_ShowMsgModal(_T("확인"), _T("BLEMISH SPEC 데이터를 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
		return;

    this->GetFdfSpec();
    this->GetLcbSpec();
    this->GetYmeanSpec();

	//g_clSysData.Save();
	//g_clMandoSfrSpec[m_nUnit].Save();
	g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);
	g_clModelData[m_nUnit].AcmisDataSave(g_clSysData.m_szModelName);
	AddLog(_T("[INFO] BLEMISH SPEC 저장"), 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	버튼 : CLOSE
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::OnBnClickedButtonCcdSfrSpecClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
}

//-----------------------------------------------------------------------------
//
//	그리드 컨트롤 더블 클릭
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::OnNMDblClickedSfrBlockspot(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
    CString sData = _T("");
    int nRow, nCol;

    nRow = pNMGridView->iRow;
    nCol = pNMGridView->iColumn;

    if (nRow >= 1 && nCol >= 1)
    {
        sData = m_clGridBlemishSpec.GetItemText(nRow, nCol);
        CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
        if (pDlg != NULL)
        {
            if (pDlg->DoModal() == IDOK)
            {
                sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
                m_clGridBlemishSpec.SetItemText(nRow, nCol, sData);

                m_clGridBlemishSpec.Invalidate();
            }

            delete pDlg;
        }
    }
}

void CCcdBlemishSpecDlg::OnNMDblClickedSfrLcb(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
    CString sData = _T("");
    int nRow, nCol;

    nRow = pNMGridView->iRow;
    nCol = pNMGridView->iColumn;

    if (nRow >= 1 && nCol >= 1)
    {
        sData = m_clGridLcbSpec.GetItemText(nRow, nCol);
        CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
        if (pDlg != NULL)
        {
            if (pDlg->DoModal() == IDOK)
            {
                sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
                m_clGridLcbSpec.SetItemText(nRow, nCol, sData);

                m_clGridLcbSpec.Invalidate();
            }

            delete pDlg;
        }
    }
}

void CCcdBlemishSpecDlg::OnNMDblClickedSfrYmean(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
    CString sData = _T("");
    int nRow, nCol;

    nRow = pNMGridView->iRow;
    nCol = pNMGridView->iColumn;

    if (nRow >= 1 && nCol >= 1)
    {
        sData = m_clGridYmenaSpec.GetItemText(nRow, nCol);
        CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
        if (pDlg != NULL)
        {
            if (pDlg->DoModal() == IDOK)
            {
                sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
                m_clGridYmenaSpec.SetItemText(nRow, nCol, sData);

                m_clGridYmenaSpec.Invalidate();
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


//-----------------------------------------------------------------------------
//
//	OnLButtonDown
//
//-----------------------------------------------------------------------------
void CCcdBlemishSpecDlg::OnLButtonDown(UINT nFlags, CPoint point)
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
BOOL CCcdBlemishSpecDlg::PreTranslateMessage(MSG* pMsg)
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

void CCcdBlemishSpecDlg::OnStnClickedStaticCcdBlemishBlacklevelVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos = _T("");

	m_clColorStaticBlemishBlackLevelVal.GetWindowText(sPos);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sPos, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sPos.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticBlemishBlackLevelVal.SetWindowText(sPos);
		}

		delete pDlg;
	}
	sPos.Empty();
}


HBRUSH CCcdBlemishSpecDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (pWnd->GetDlgCtrlID() == IDC_CHECK_CCD_BLEMISH_8BITUSE
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
