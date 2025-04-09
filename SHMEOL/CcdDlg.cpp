// CcdDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "CcdDlg.h"
#include "afxdialogex.h"
#include "Grabber\LAON\ConvertColor.h"
#include "Grabber\LAON\PixelFormat.h"

//! X축 수직선의 구분 index
#define INDEX_MTF4			0	//! MTF(N/4)
#define INDEX_MTF8			1	//! MTF(N/8)
#define INDEX_MTF50			2	//! MTF50

// CCcdDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCcdDlg, CDialogEx)

CCcdDlg::CCcdDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCcdDlg::IDD, pParent)
{
	int i, j;

	m_nUnit = UNIT_AA1;

	m_pGraphWnd = NULL;
	m_nGraphMode = 3;

	for (i = 0; i < MAX_GRAPH_OVERLAP_COUNT; i++)
	{
		for (j = 0; j < MAX_GRAPH_PIXEL_SIZE; j++)
		{
			m_dDataX[i][j] = 0.0;
			m_dDataY[i][j] = 0.0;
		}
		//m_bFlagVisible[i] = true;

		m_nDataSize[i] = 0;
		//m_dDataMTF4[i] = 0.0;
		//m_dDataMTF8[i] = 0.0;
		//m_dDataMTF50[i] = 0.0;
	}
	
	m_nMoveType = MOVE_POS;

   
	m_nMoveSize = 10;

	m_pImgBuff = NULL;
	
	m_pTempBuff1 = NULL;
	m_pTempBuff2 = NULL;
}

CCcdDlg::~CCcdDlg()
{	
	if (m_pGraphWnd != NULL)
	{
		delete m_pGraphWnd;
		m_pGraphWnd = NULL;
	}

	if(m_pImgBuff != NULL)
	{
		delete m_pImgBuff;
		m_pImgBuff = NULL;
	}

	if (m_pTempBuff1 != NULL)
	{
		delete m_pTempBuff1;
		m_pTempBuff1 = NULL;
	}

	if (m_pTempBuff2 != NULL)
	{
		delete m_pTempBuff2;
		m_pTempBuff2 = NULL;
	}
}

void CCcdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CCD_TITLE, m_clColorStaticTitle);
	DDX_Control(pDX, IDC_BUTTON_CCD_POS, m_clColorButtonPos);
	DDX_Control(pDX, IDC_BUTTON_CCD_SIZE, m_clColorButtonSize);
	DDX_Control(pDX, IDC_BUTTON_CCD_GAP, m_clColorButtonGap);
	DDX_Control(pDX, IDC_BUTTON_CCD_UP, m_clColorButtonUp);
	DDX_Control(pDX, IDC_BUTTON_CCD_DOWN, m_clColorButtonDown);
	DDX_Control(pDX, IDC_BUTTON_CCD_LEFT, m_clColorButtonLeft);
	DDX_Control(pDX, IDC_BUTTON_CCD_RIGHT, m_clColorButtonRight);
	DDX_Control(pDX, IDC_BUTTON_CCD_INIT, m_clColorButtonInit);
	DDX_Control(pDX, IDC_BUTTON_CCD_FOV_INIT, m_clColorButtonFovInit);
	
    DDX_Control(pDX, IDC_BUTTON_CCD_CIRCLE_MARK_REGIST, m_clColorButtonCircleMarkRegist);
    DDX_Control(pDX, IDC_BUTTON_CCD_FOV_MARK_VIEW, m_clColorButtonFovMarkView);

    
    DDX_Control(pDX, IDC_BUTTON_CCD_SNR_MARK_REGIST, m_clColorButtonSnrMarkRegist);
    DDX_Control(pDX, IDC_BUTTON_CCD_SNR_ROI_VIEW, m_clColorButtonSnrMarkView);
    
    DDX_Control(pDX, IDC_BUTTON_CCD_FOV_MARK_REGIST, m_clColorButtonFovMarkRegist);
    
    DDX_Control(pDX, IDC_BUTTON_CCD_INSP_AREA_SAVE, m_clColorButtonInspAreaSave);
    DDX_Control(pDX, IDC_BUTTON_CCD_PATTERN_SAVE, m_clColorButtonPatternSave);
    DDX_Control(pDX, IDC_BUTTON_CCD_PATTERN_FIND, m_clColorButtonPatternFind);

    
    DDX_Control(pDX, IDC_BUTTON_CCD_SFR_ROI_SAVE, m_clColorButtonSfrRoiSave);
	DDX_Control(pDX, IDC_BUTTON_CCD_IMAGE_LOAD, m_clColorButtonImgLoad);
	DDX_Control(pDX, IDC_BUTTON_CCD_IMAGE_SAVE, m_clColorButtonImgSave);
	DDX_Control(pDX, IDC_BUTTON_CCD_RAW_IMAGE_LOAD, m_clColorButtonRawImgLoad);
	DDX_Control(pDX, IDC_BUTTON_CCD_RAW_IMAGE_SAVE, m_clColorButtonRawImgSave);
	DDX_Control(pDX, IDC_BUTTON_CCD_JXL_DECODE, m_clColorButtonJxlDecode);
	
	DDX_Control(pDX, IDC_BUTTON_CCD_SFR_INSP, m_clColorButtonSfrInsp);
	DDX_Control(pDX, IDC_BUTTON_CCD_ROW_COL_NOISE, m_clColorButtonRowColNoiseInsp);
	DDX_Control(pDX, IDC_BUTTON_CCD_LENS_SHADING, m_clColorButtonLensShadingInsp);
	DDX_Control(pDX, IDC_BUTTON_CCD_LENS_SHADING2, m_clColorButtonLensShadingInsp2);
	
	DDX_Control(pDX, IDC_BUTTON_CCD_MES_SPEC_LOAD, m_clColorButtonMesSpecLoad);
	DDX_Control(pDX, IDC_BUTTON_CCD_INI_LOAD, m_clColorButtonIniFileLoad);
	
	
	DDX_Control(pDX, IDC_BUTTON_CCD_ACTIVE_ALIGN, m_clColorButtonActiveAlign);
	DDX_Control(pDX, IDC_BUTTON_CCD_FUSE_ID, m_clColorButtonFuseID);
	DDX_Control(pDX, IDC_BUTTON_CCD_EEPROM_TEST, m_clColorButtonEepromTest);
	//
    DDX_Control(pDX, IDC_BUTTON_CCD_BLEMISH_SPEC, m_clColorButtonBlemishSpec);
    DDX_Control(pDX, IDC_BUTTON_CCD_FOVRD_SPEC, m_clColorButtonChartSpec);
	DDX_Control(pDX, IDC_BUTTON_CCD_RELATIVEI_SPEC, m_clColorButtonRiSpec);
	DDX_Control(pDX, IDC_BUTTON_CCD_COLOR_SHADING_SPEC, m_clColorButtonColorShadingSpec);
	DDX_Control(pDX, IDC_BUTTON_CCD_COLOR_UNIFORMITY_SPEC, m_clColorButtonColorUniformitySpec);
	
    DDX_Control(pDX, IDC_BUTTON_CCD_SNR_COLORS_SPEC, m_clColorButtonSnrColorSSpec);
	DDX_Control(pDX, IDC_BUTTON_CCD_RITHRESHOLD_SPEC, m_clColorButtonRiThresholdSpec);

	DDX_Control(pDX, IDC_BUTTON_CCD_SATURATION_SPEC, m_clColorButtonSaturationSpec);
	DDX_Control(pDX, IDC_BUTTON_CCD_IRFILTER_SPEC, m_clColorButtonIrFilterSpec);
	DDX_Control(pDX, IDC_BUTTON_CCD_FPN_SPEC, m_clColorButtonFpnSpec);
	
	DDX_Control(pDX, IDC_BUTTON_CCD_COLOR_REPRODUCTION_SPEC, m_clColorButtonReproductionSpec);
	DDX_Control(pDX, IDC_BUTTON_CCD_TEMPERATURE_SPEC, m_clColorButtonTemperatureSpec);
	
	
    
    
	DDX_Control(pDX, IDC_BUTTON_CCD_RI_SPEC, m_clColorButtonRiOcSpec);
	DDX_Control(pDX, IDC_BUTTON_CCD_DEFECT_SPEC, m_clColorButtonDefectSpec);
	DDX_Control(pDX, IDC_BUTTON_CCD_SFR_SPEC, m_clColorButtonSfrSpec);
	DDX_Control(pDX, IDC_BUTTON_CCD_PIXEL_DEFECT, m_clColorButtonPixelDefect);
	DDX_Control(pDX, IDC_BUTTON_CCD_STAIN, m_clColorButtonStain);
	DDX_Control(pDX, IDC_BUTTON_CCD_UNIFORMITY, m_clColorButtonUniformity);
	DDX_Control(pDX, IDC_BUTTON_CCD_CURRENT, m_clColorButtonCurrent);
	DDX_Control(pDX, IDC_BUTTON_CCD_DYNAMIC_RANGE, m_clColorButtonDynamicRange);

	DDX_Control(pDX, IDC_BUTTON_CCD_I2C, m_clColorButtonI2C);
	DDX_Control(pDX, IDC_BUTTON_CCD_FLASHING, m_clColorButtonFlashing);
	
	DDX_Control(pDX, IDC_BUTTON_CCD_DISTORTION, m_clColorButtonDistortion);
	
	DDX_Control(pDX, IDC_BUTTON_CCD_I2C_PATTERN, m_clColorButtonI2cTestPattern);
	DDX_Control(pDX, IDC_BUTTON_CCD_SATURATION, m_clColorButtonSaturation);
	DDX_Control(pDX, IDC_BUTTON_CCD_IR_FILTER_TEST, m_clColorButtonIrFilterTest);
	DDX_Control(pDX, IDC_BUTTON_CCD_COLOR_REPRODUCTION, m_clColorButtonColorReproduction);
	DDX_Control(pDX, IDC_BUTTON_CCD_TEMPERATURE, m_clColorButtonColorTemperature);
	DDX_Control(pDX, IDC_BUTTON_CCD_MTF, m_clColorButtonMTF);
    //
	DDX_Control(pDX, IDC_BUTTON_CCD_DEFECT_RI, m_clColorButtonRi);
	DDX_Control(pDX, IDC_BUTTON_CCD_DEFECT_RI3, m_clColorButtonRi2);
	
	DDX_Control(pDX, IDC_BUTTON_CCD_SNR, m_clColorButtonSnr);
	DDX_Control(pDX, IDC_BUTTON_CCD_SNR2, m_clColorButtonSnr2);
	
	DDX_Control(pDX, IDC_BUTTON_CCD_COLOR_SENSITIVITY, m_clColorButtonRcbc);
	DDX_Control(pDX, IDC_BUTTON_CCD_COLOR_SENSITIVITY2, m_clColorButtonRcbc2);
	DDX_Control(pDX, IDC_BUTTON_CCD_COLOR_SENSITIVITY3, m_clColorButtonRcbc3);
    DDX_Control(pDX, IDC_BUTTON_CCD_IC, m_clColorButtonOc);
    DDX_Control(pDX, IDC_BUTTON_CCD_FOV_DIS_RO, m_clColorButtonFov_Dis_Ro);
    DDX_Control(pDX, IDC_BUTTON_CCD_DIS, m_clColorButtonDis);
	DDX_Control(pDX, IDC_BUTTON_CCD_VOLTAGE, m_clColorButtonVoltage);
	DDX_Control(pDX, IDC_BUTTON_CCD_SENSOR_VOLTAGE, m_clColorButtonSensorVoltage);
	
	DDX_Control(pDX, IDC_BUTTON_CCD_EEPROM_CHECKSUM, m_clColorButtonEEpromCheckSum);
	
    
	//
	DDX_Control(pDX, IDC_BUTTON_CCD_DEVICE_OPEN, m_clColorButtonDeviceOpen);
	DDX_Control(pDX, IDC_BUTTON_CCD_DEVICE_CLOSE, m_clColorButtonDeviceClose);
	DDX_Control(pDX, IDC_BUTTON_CCD_CONNECT, m_clColorButtonConnect);
	DDX_Control(pDX, IDC_BUTTON_CCD_BOARD_INIT, m_clColorButtonBoardInit);
	DDX_Control(pDX, IDC_BUTTON_CCD_SENSOR_INIT, m_clColorButtonSensorInit);
	DDX_Control(pDX, IDC_BUTTON_CCD_GRAB_START, m_clColorButtonGrabStart);
	DDX_Control(pDX, IDC_BUTTON_CCD_GRAB_STOP, m_clColorButtonGrabStop);
	DDX_Control(pDX, IDC_BUTTON_CCD_DISCONNECT, m_clColorButtonDisconnect);

	DDX_Control(pDX, IDC_BUTTON_CCD_CALIBRATION1, m_clColorCalribration1);
	DDX_Control(pDX, IDC_BUTTON_CCD_CALIBRATION2, m_clColorCalribration2);
}


BEGIN_MESSAGE_MAP(CCcdDlg, CDialogEx)
	ON_WM_PAINT()	
	ON_BN_CLICKED(IDC_BUTTON_CCD_IMAGE_LOAD, &CCcdDlg::OnBnClickedButtonCcdImageLoad)
	ON_BN_CLICKED(IDC_BUTTON_CCD_IMAGE_SAVE, &CCcdDlg::OnBnClickedButtonCcdImageSave)
	ON_BN_CLICKED(IDC_BUTTON_CCD_RAW_IMAGE_LOAD, &CCcdDlg::OnBnClickedButtonCcdRawImageLoad)
	ON_BN_CLICKED(IDC_BUTTON_CCD_RAW_IMAGE_SAVE, &CCcdDlg::OnBnClickedButtonCcdRawImageSave)
	ON_BN_CLICKED(IDC_BUTTON_CCD_POS, &CCcdDlg::OnBnClickedButtonCcdPos)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SIZE, &CCcdDlg::OnBnClickedButtonCcdSize)
	ON_BN_CLICKED(IDC_BUTTON_CCD_GAP, &CCcdDlg::OnBnClickedButtonCcdGap)
	ON_BN_CLICKED(IDC_BUTTON_CCD_UP, &CCcdDlg::OnBnClickedButtonCcdUp)
	ON_BN_CLICKED(IDC_BUTTON_CCD_DOWN, &CCcdDlg::OnBnClickedButtonCcdDown)
	ON_BN_CLICKED(IDC_BUTTON_CCD_LEFT, &CCcdDlg::OnBnClickedButtonCcdLeft)
	ON_BN_CLICKED(IDC_BUTTON_CCD_RIGHT, &CCcdDlg::OnBnClickedButtonCcdRight)
	ON_BN_CLICKED(IDC_BUTTON_CCD_INIT, &CCcdDlg::OnBnClickedButtonCcdInit)
	ON_BN_CLICKED(IDC_BUTTON_CCD_CIRCLE_MARK_REGIST, &CCcdDlg::OnBnClickedButtonCcdCircleMarkRegist)
	ON_BN_CLICKED(IDC_BUTTON_CCD_INSP_AREA_SAVE, &CCcdDlg::OnBnClickedButtonCcdInspAreaSave)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_SPEC, &CCcdDlg::OnBnClickedButtonCcdSfrSpec)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_INSP, &CCcdDlg::OnBnClickedButtonCcdSfrInsp)
	ON_BN_CLICKED(IDC_BUTTON_CCD_ACTIVE_ALIGN, &CCcdDlg::OnBnClickedButtonCcdActiveAlign)
	ON_BN_CLICKED(IDC_BUTTON_CCD_PIXEL_DEFECT, &CCcdDlg::OnBnClickedButtonCcdPixelDefect)
	ON_BN_CLICKED(IDC_BUTTON_CCD_STAIN, &CCcdDlg::OnBnClickedButtonCcdStain)
	ON_BN_CLICKED(IDC_BUTTON_CCD_UNIFORMITY, &CCcdDlg::OnBnClickedButtonCcdUniformity)
	ON_BN_CLICKED(IDC_BUTTON_CCD_CURRENT, &CCcdDlg::OnBnClickedButtonCcdCurrent)
	ON_BN_CLICKED(IDC_BUTTON_CCD_I2C_PATTERN, &CCcdDlg::OnBnClickedButtonCcdI2cPattern)
	ON_BN_CLICKED(IDC_BUTTON_CCD_MTF, &CCcdDlg::OnBnClickedButtonCcdMtf)
	ON_BN_CLICKED(IDC_BUTTON_CCD_DEVICE_OPEN, &CCcdDlg::OnBnClickedButtonCcdDeviceOpen)
	ON_BN_CLICKED(IDC_BUTTON_CCD_DEVICE_CLOSE, &CCcdDlg::OnBnClickedButtonCcdDeviceClose)
	ON_BN_CLICKED(IDC_BUTTON_CCD_CONNECT, &CCcdDlg::OnBnClickedButtonCcdConnect)
	ON_BN_CLICKED(IDC_BUTTON_CCD_BOARD_INIT, &CCcdDlg::OnBnClickedButtonCcdBoardInit)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SENSOR_INIT, &CCcdDlg::OnBnClickedButtonCcdSensorInit)
	ON_BN_CLICKED(IDC_BUTTON_CCD_GRAB_START, &CCcdDlg::OnBnClickedButtonCcdGrabStart)
	ON_BN_CLICKED(IDC_BUTTON_CCD_GRAB_STOP, &CCcdDlg::OnBnClickedButtonCcdGrabStop)
	ON_BN_CLICKED(IDC_BUTTON_CCD_DISCONNECT, &CCcdDlg::OnBnClickedButtonCcdDisconnect)
	ON_BN_CLICKED(IDC_CCD_BUTTON1, &CCcdDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CCD_BUTTON2, &CCcdDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CCD_BUTTON3, &CCcdDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_CCD_BUTTON4, &CCcdDlg::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON_CCD_PATTERN_SAVE, &CCcdDlg::OnBnClickedButtonCcdPatternSave)
    ON_BN_CLICKED(IDC_BUTTON_CCD_PATTERN_FIND, &CCcdDlg::OnBnClickedButtonCcdPatternFind)
    ON_BN_CLICKED(IDC_BUTTON_CCD_SFR_ROI_SAVE, &CCcdDlg::OnBnClickedButtonCcdSfrRoiSave)
    //
    ON_NOTIFY(NM_DBLCLK, IDC_STATIC_GRID_SFR_ROI, &CCcdDlg::OnNMDblClickedSfrSRoi)
	ON_BN_CLICKED(IDC_BUTTON_CCD_IC, &CCcdDlg::OnBnClickedButtonCcdIC)
	ON_BN_CLICKED(IDC_BUTTON_CCD_COLOR_SENSITIVITY, &CCcdDlg::OnBnClickedButtonCcdRcbc)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SNR, &CCcdDlg::OnBnClickedButtonCcdSnr)
	ON_BN_CLICKED(IDC_BUTTON_CCD_DEFECT_RI, &CCcdDlg::OnBnClickedButtonCcdDefectRi)
	ON_BN_CLICKED(IDC_BUTTON_CCD_DEFECT_SPEC, &CCcdDlg::OnBnClickedButtonCcdDefectSpec)
	ON_BN_CLICKED(IDC_BUTTON_CCD_RI_SPEC, &CCcdDlg::OnBnClickedButtonCcdRiSpec)
	ON_BN_CLICKED(IDC_BUTTON_CCD_BLEMISH_SPEC, &CCcdDlg::OnBnClickedButtonCcdBlemishSpec)
    ON_BN_CLICKED(IDC_BUTTON_CCD_FOV_DIS_RO, &CCcdDlg::OnBnClickedButtonCcdFovDisRo)
    ON_BN_CLICKED(IDC_BUTTON_CCD_FOV_MARK_REGIST, &CCcdDlg::OnBnClickedButtonCcdFovMarkRegist)
    ON_BN_CLICKED(IDC_BUTTON_CCD_FOV_MARK_VIEW, &CCcdDlg::OnBnClickedButtonCcdFovMarkView)
    ON_BN_CLICKED(IDC_BUTTON_CCD_FOVRD_SPEC, &CCcdDlg::OnBnClickedButtonCcdFovrdSpec)
    ON_BN_CLICKED(IDC_BUTTON_CCD_RELATIVEI_SPEC, &CCcdDlg::OnBnClickedButtonCcdRelativeiSpec)
    ON_BN_CLICKED(IDC_BUTTON_CCD_SNR_COLORS_SPEC, &CCcdDlg::OnBnClickedButtonCcdSnrColorsSpec)
    ON_BN_CLICKED(IDC_BUTTON_CCD_DARK_RAW_IMAGE_LOAD, &CCcdDlg::OnBnClickedButtonCcdDarkRawImageLoad)
    ON_BN_CLICKED(IDC_BUTTON_CCD_2800_RAW_IMAGE_LOAD, &CCcdDlg::OnBnClickedButtonCcd2800RawImageLoad)
    ON_BN_CLICKED(IDC_BUTTON_CCD_SNR_ROI_VIEW, &CCcdDlg::OnBnClickedButtonCcdSnrRoiView)
    ON_BN_CLICKED(IDC_BUTTON_CCD_SNR_MARK_REGIST, &CCcdDlg::OnBnClickedButtonCcdSnrMarkRegist)
    ON_BN_CLICKED(IDC_BUTTON_CCD_RITHRESHOLD_SPEC, &CCcdDlg::OnBnClickedButtonCcdRithresholdSpec)
    ON_BN_CLICKED(IDC_BUTTON_CCD_6500_RAW_IMAGE_LOAD, &CCcdDlg::OnBnClickedButtonCcd6500RawImageLoad)
    ON_BN_CLICKED(IDC_BUTTON_CCD_DIS, &CCcdDlg::OnBnClickedButtonCcdDis)
	ON_BN_CLICKED(IDC_BUTTON_CCD_CALIBRATION1, &CCcdDlg::OnBnClickedButtonCcdCalibration1)
	ON_BN_CLICKED(IDC_BUTTON_CCD_CALIBRATION2, &CCcdDlg::OnBnClickedButtonCcdCalibration2)
	ON_BN_CLICKED(IDC_BUTTON_CCD_FUSE_ID, &CCcdDlg::OnBnClickedButtonCcdFuseId)
	ON_BN_CLICKED(IDC_BUTTON_CCD_EEPROM_TEST, &CCcdDlg::OnBnClickedButtonCcdEepromTest)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SATURATION, &CCcdDlg::OnBnClickedButtonCcdSaturation)
	ON_BN_CLICKED(IDC_BUTTON_CCD_IR_FILTER_TEST, &CCcdDlg::OnBnClickedButtonCcdIrFilterTest)
	ON_BN_CLICKED(IDC_BUTTON_CCD_COLOR_REPRODUCTION, &CCcdDlg::OnBnClickedButtonCcdColorReproduction)
	ON_BN_CLICKED(IDC_BUTTON_CCD_TEMPERATURE, &CCcdDlg::OnBnClickedButtonCcdTemperature)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SATURATION_SPEC, &CCcdDlg::OnBnClickedButtonCcdSaturationSpec)
	ON_BN_CLICKED(IDC_BUTTON_CCD_IRFILTER_SPEC, &CCcdDlg::OnBnClickedButtonCcdIrfilterSpec)
	ON_BN_CLICKED(IDC_BUTTON_CCD_COLOR_REPRODUCTION_SPEC, &CCcdDlg::OnBnClickedButtonCcdColorReproductionSpec)
	ON_BN_CLICKED(IDC_BUTTON_CCD_TEMPERATURE_SPEC, &CCcdDlg::OnBnClickedButtonCcdTemperatureSpec)
	ON_BN_CLICKED(IDC_BUTTON_CCD_VOLTAGE, &CCcdDlg::OnBnClickedButtonCcdVoltage)
	ON_BN_CLICKED(IDC_BUTTON_CCD_EEPROM_CHECKSUM, &CCcdDlg::OnBnClickedButtonCcdEepromChecksum)
	ON_BN_CLICKED(IDC_BUTTON_CCD_I2C, &CCcdDlg::OnBnClickedButtonCcdI2c)
	ON_BN_CLICKED(IDC_BUTTON_CCD_DISTORTION, &CCcdDlg::OnBnClickedButtonCcdDistortion)
	ON_BN_CLICKED(IDC_BUTTON_CCD_LENS_SHADING, &CCcdDlg::OnBnClickedButtonCcdLensShading)
	ON_BN_CLICKED(IDC_BUTTON_CCD_COLOR_SHADING_SPEC, &CCcdDlg::OnBnClickedButtonCcdColorShadingSpec)
	ON_BN_CLICKED(IDC_BUTTON_CCD_COLOR_UNIFORMITY_SPEC, &CCcdDlg::OnBnClickedButtonCcdColorUniformitySpec)
	ON_BN_CLICKED(IDC_BUTTON_CCD_FPN_SPEC, &CCcdDlg::OnBnClickedButtonCcdFpnSpec)
	ON_BN_CLICKED(IDC_BUTTON_CCD_MES_SPEC_LOAD, &CCcdDlg::OnBnClickedButtonCcdMesSpecLoad)
	ON_BN_CLICKED(IDC_BUTTON_CCD_DEFECT_RI3, &CCcdDlg::OnBnClickedButtonCcdDefectRi3)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SNR2, &CCcdDlg::OnBnClickedButtonCcdSnr2)
	ON_BN_CLICKED(IDC_BUTTON_CCD_COLOR_SENSITIVITY2, &CCcdDlg::OnBnClickedButtonCcdColorSensitivity2)
	ON_BN_CLICKED(IDC_BUTTON_CCD_COLOR_SENSITIVITY3, &CCcdDlg::OnBnClickedButtonCcdColorSensitivity3)
	ON_BN_CLICKED(IDC_BUTTON_CCD_LENS_SHADING2, &CCcdDlg::OnBnClickedButtonCcdLensShading2)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_CCD_INI_LOAD, &CCcdDlg::OnBnClickedButtonCcdIniLoad)
	ON_BN_CLICKED(IDC_BUTTON_CCD_FOV_INIT, &CCcdDlg::OnBnClickedButtonCcdFovInit)
	ON_BN_CLICKED(IDC_BUTTON_CCD_SENSOR_VOLTAGE, &CCcdDlg::OnBnClickedButtonCcdSensorVoltage)
	ON_BN_CLICKED(IDC_BUTTON_CCD_JXL_DECODE, &CCcdDlg::OnBnClickedButtonCcdJxlDecode)
	ON_BN_CLICKED(IDC_BUTTON_CCD_FLASHING, &CCcdDlg::OnBnClickedButtonCcdFlashing)
END_MESSAGE_MAP()


// CCcdDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnPaint()
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
BOOL CCcdDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();
	
    this->InitGridCtrlSfrRoi();
	// ROI 초기화
	//this->InitROI();

	//
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CCcdDlg::InitCtrl()
{
	WINDOWPLACEMENT wndpl;
	CPoint clButtonPos;

	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	m_clColorStaticTitle.SetBkColor(RGB_CTRL_BG);
	m_clColorStaticTitle.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticTitle.SetFont(&m_clFontBig);
    m_clColorStaticTitle.SetFontBold(TRUE);
    m_clColorStaticTitle.SetBorder(FALSE);
    m_clColorStaticTitle.SetFontSize(15);

	m_clSfrSpecDlg.Create(IDD_DIALOG_CCD_SFR_SPEC, this);
    m_clSfrSpecDlg.ShowWindow(SW_HIDE);

	m_clDefectSpecDlg.Create(IDD_DIALOG_CCD_DEFECT_SPEC, this);
	m_clDefectSpecDlg.ShowWindow(SW_HIDE);

	m_clRiOcSpecDlg.Create(IDD_DIALOG_CCD_RI_OC_SPEC, this);
	m_clRiOcSpecDlg.ShowWindow(SW_HIDE);

	m_clBlemishSpecDlg.Create(IDD_DIALOG_CCD_BLEMISH_SPEC, this);
	m_clBlemishSpecDlg.ShowWindow(SW_HIDE);

	m_clMesSpecDlg.Create(IDD_DIALOG_CCD_MES_SPEC, this);
	m_clMesSpecDlg.ShowWindow(SW_HIDE);

	
    m_clChartSpecDlg.Create(IDD_DIALOG_CCD_CHART_SPEC, this);
    m_clChartSpecDlg.ShowWindow(SW_HIDE);

    m_clRiSpecDlg.Create(IDD_DIALOG_CCD_RI_SPEC, this);
    m_clRiSpecDlg.ShowWindow(SW_HIDE);

	m_clColorShadingSpecDlg.Create(IDD_DIALOG_CCD_COLOR_SHADING_SPEC, this);
	m_clColorShadingSpecDlg.ShowWindow(SW_HIDE);

	m_clColorUniformitySpecDlg.Create(IDD_DIALOG_CCD_COLOR_UNIFORMITY_SPEC, this);
	m_clColorUniformitySpecDlg.ShowWindow(SW_HIDE);

	//m_clFpnSpecDlg.Create(IDD_DIALOG_CCD_FPN_SPEC, this);
	//m_clFpnSpecDlg.ShowWindow(SW_HIDE);
	
	
    //m_clRiThresholdSpecDlg.Create(IDD_DIALOG_CCD_RI_THRESHOLD_SPEC, this);
    //m_clRiThresholdSpecDlg.ShowWindow(SW_HIDE);

    //m_clSnrColorSensSpecDlg.Create(IDD_DIALOG_CCD_COLORSENSITIVITY_SPEC, this);
    //m_clSnrColorSensSpecDlg.ShowWindow(SW_HIDE);

	m_clSaturationSpecDlg.Create(IDD_DIALOG_CCD_SATURATION_SPEC, this);
	m_clSaturationSpecDlg.ShowWindow(SW_HIDE);

	m_clColorReproductionSpecDlg.Create(IDD_DIALOG_CCD_COLOR_REPRODUCTION_SPEC, this);
	m_clColorReproductionSpecDlg.ShowWindow(SW_HIDE);

	m_clTemperatureSpecDlg.Create(IDD_DIALOG_CCD_TEMPERATURE_SPEC, this);
	m_clTemperatureSpecDlg.ShowWindow(SW_HIDE);

	m_clIrFilterSpecDlg.Create(IDD_DIALOG_CCD_IRFILTER_SPEC, this);
	m_clIrFilterSpecDlg.ShowWindow(SW_HIDE);
	

	
	eepromDlg.Create(IDD_DIALOG_EEPROM, this);
	eepromDlg.ShowWindow(SW_HIDE);


	m_clColorButtonActiveAlign.ShowWindow(SW_HIDE);

	

	

	GetDlgItem(IDC_BUTTON_CCD_CONNECT)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BUTTON_CCD_SENSOR_INIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_CCD_DISCONNECT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_4)->GetWindowPlacement(&wndpl);
	clButtonPos.x = wndpl.rcNormalPosition.left;
	clButtonPos.y = wndpl.rcNormalPosition.top;
	GetDlgItem(IDC_STATIC_5)->SetWindowPos(NULL, clButtonPos.x, clButtonPos.y, 0, 0, SWP_NOSIZE);

	GetDlgItem(IDC_BUTTON_CCD_SFR_INSP)->GetWindowPlacement(&wndpl);
	clButtonPos.x = wndpl.rcNormalPosition.left;
	clButtonPos.y = wndpl.rcNormalPosition.top;
	GetDlgItem(IDC_BUTTON_CCD_CALIBRATION1)->SetWindowPos(NULL, clButtonPos.x, clButtonPos.y, 0, 0, SWP_NOSIZE);

	GetDlgItem(IDC_BUTTON_CCD_STAIN)->GetWindowPlacement(&wndpl);
	clButtonPos.x = wndpl.rcNormalPosition.left;
	clButtonPos.y = wndpl.rcNormalPosition.top;

	GetDlgItem(IDC_BUTTON_CCD_CALIBRATION2)->SetWindowPos(NULL, clButtonPos.x, clButtonPos.y, 0, 0, SWP_NOSIZE);


	//m_clColorButtonOc
    m_clColorButtonPos.state = 1;
    m_clColorButtonPos.Invalidate();
}

//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CCcdDlg::SetUnit(int nUnit)
{
	TCHAR szTitle[SIZE_OF_100BYTE];
	m_nUnit = nUnit;
	_stprintf_s(szTitle, SIZE_OF_100BYTE, _T("[CCD]")); //, m_nUnit + 1);


	GetDlgItem(IDC_STATIC_CCD_TITLE)->SetWindowText(szTitle);

	this->DrawGraph();

	///this->DisplaySfrData();

    this->setSfrRoi();
    
}
void CCcdDlg::SetUnitUI(int nUnit)
{
	GetDlgItem(IDC_STATIC_1)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_2)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_3)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_4)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_5)->ShowWindow(false);

	//GetDlgItem(IDC_BUTTON_CCD_INIT)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_SFR_INSP)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_SFR_SPEC)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_PIXEL_DEFECT)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_STAIN)->ShowWindow(true);
	//GetDlgItem(IDC_BUTTON_CCD_UNIFORMITY)->ShowWindow(true);
	//GetDlgItem(IDC_BUTTON_CCD_CURRENT)->ShowWindow(true);
	//GetDlgItem(IDC_BUTTON_CCD_IC)->ShowWindow(true);
	//GetDlgItem(IDC_BUTTON_CCD_COLOR_SENSITIVITY)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_POS)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_UP)->ShowWindow(true);

	GetDlgItem(IDC_BUTTON_CCD_SIZE)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_LEFT)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_GAP)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_RIGHT)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_DOWN)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_CIRCLE_MARK_REGIST)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_INSP_AREA_SAVE)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_DEFECT_RI)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_SNR)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_PATTERN_SAVE)->ShowWindow(true);

	GetDlgItem(IDC_BUTTON_CCD_PATTERN_FIND)->ShowWindow(true);

	GetDlgItem(IDC_BUTTON_CCD_SFR_ROI_SAVE)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_DEFECT_SPEC)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_RI_SPEC)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_BLEMISH_SPEC)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_FOV_DIS_RO)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_FOV_MARK_REGIST)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_FOV_MARK_VIEW)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_FOVRD_SPEC)->ShowWindow(true);

	GetDlgItem(IDC_BUTTON_CCD_RELATIVEI_SPEC)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_SNR_COLORS_SPEC)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_SNR_ROI_VIEW)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_RITHRESHOLD_SPEC)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_SNR_MARK_REGIST)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_CCD_DIS)->ShowWindow(true);

	GetDlgItem(IDC_BUTTON_CCD_CALIBRATION1)->ShowWindow(false);
	GetDlgItem(IDC_BUTTON_CCD_CALIBRATION2)->ShowWindow(false);

	m_clGridSfrEachRoi.ShowWindow(true);
	return;
	if (nUnit == 0)
	{
		
	}
	else
	{
		GetDlgItem(IDC_STATIC_1)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_2)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_3)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_4)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_5)->ShowWindow(true);

		GetDlgItem(IDC_BUTTON_CCD_INIT)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_FOV_INIT)->ShowWindow(false);
		
		GetDlgItem(IDC_BUTTON_CCD_SFR_INSP)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_SFR_SPEC)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_PIXEL_DEFECT)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_STAIN)->ShowWindow(false);
		//GetDlgItem(IDC_BUTTON_CCD_UNIFORMITY)->ShowWindow(false);
		//GetDlgItem(IDC_BUTTON_CCD_CURRENT)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_IC)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_COLOR_SENSITIVITY)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_POS)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_UP)->ShowWindow(false);

		GetDlgItem(IDC_BUTTON_CCD_SIZE)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_LEFT)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_GAP)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_RIGHT)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_DOWN)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_CIRCLE_MARK_REGIST)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_INSP_AREA_SAVE)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_DEFECT_RI)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_SNR)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_PATTERN_SAVE)->ShowWindow(false);

		GetDlgItem(IDC_BUTTON_CCD_PATTERN_FIND)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_GRID_SFR_ROI)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_SFR_ROI_SAVE)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_DEFECT_SPEC)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_RI_SPEC)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_BLEMISH_SPEC)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_FOV_DIS_RO)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_FOV_MARK_REGIST)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_FOV_MARK_VIEW)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_FOVRD_SPEC)->ShowWindow(false);

		GetDlgItem(IDC_BUTTON_CCD_RELATIVEI_SPEC)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_SNR_COLORS_SPEC)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_SNR_ROI_VIEW)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_RITHRESHOLD_SPEC)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_SNR_MARK_REGIST)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_CCD_DIS)->ShowWindow(false);

		GetDlgItem(IDC_BUTTON_CCD_CALIBRATION1)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON_CCD_CALIBRATION2)->ShowWindow(true);

		m_clGridSfrEachRoi.ShowWindow(false);
	}
}

void CCcdDlg::getSfrRoi()
{
    CString sData = _T("");
    int i;
	int mindex = 0;
	if (g_clModelData[m_nUnit].m_nPatternChartUse == 0)
	{
		mindex = 0;
	}
	else
	{
		mindex = 1;
	}
    for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
    {
        sData = m_clGridSfrEachRoi.GetItemText(i + 1, 1);
        g_clModelData[m_nUnit].m_MTF_ROI_Pos[mindex][i].x = _ttoi((TCHAR*)(LPCTSTR)sData);

		sData = m_clGridSfrEachRoi.GetItemText(i + 1, 2);
		g_clModelData[m_nUnit].m_MTF_ROI_Pos[mindex][i].y = _ttoi((TCHAR*)(LPCTSTR)sData);

		sData = m_clGridSfrEachRoi.GetItemText(i + 1, 3);
		g_clModelData[m_nUnit].m_nDirection[i] = _ttoi((TCHAR*)(LPCTSTR)sData);

    }
    
}
void CCcdDlg::OnNMDblClickedSfrSRoi(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_GRIDVIEW* pNMGridView = (NM_GRIDVIEW*)pNMHDR;
    CString sData = _T("");
    int nRow, nCol;

    nRow = pNMGridView->iRow;
    nCol = pNMGridView->iColumn;

    if (nRow >= 1 && nCol >= 1)
    {
        sData = m_clGridSfrEachRoi.GetItemText(nRow, nCol);
        CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
        if (pDlg != NULL)
        {
            if (pDlg->DoModal() == IDOK)
            {
                sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
                m_clGridSfrEachRoi.SetItemText(nRow, nCol, sData);
                m_clGridSfrEachRoi.Invalidate();
            }
            delete pDlg;
        }
    }
}

void CCcdDlg::setSfrRoi()
{
    TCHAR szNo[SIZE_OF_100BYTE];
    int i;

	GetDlgItem(IDC_STATIC_GRID_SFR_ROI)->ShowWindow(SW_SHOW);
	int mindex = 0;
	if (g_clModelData[m_nUnit].m_nPatternChartUse == 0)
	{
		mindex = 0;
	}
	else
	{
		mindex = 1;
	}
    for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
    {
        _stprintf_s(szNo, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_MTF_ROI_Pos[mindex][i].x);
        m_clGridSfrEachRoi.SetItemText(i + 1, 1, szNo);
		_stprintf_s(szNo, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_MTF_ROI_Pos[mindex][i].y);
		m_clGridSfrEachRoi.SetItemText(i + 1, 2, szNo);
		_stprintf_s(szNo, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nDirection[i]);
		m_clGridSfrEachRoi.SetItemText(i + 1, 3, szNo);
    }
    m_clGridSfrEachRoi.Invalidate();
}
void CCcdDlg::InitGridCtrlSfrRoi()
{
	static TCHAR* SFR_FIELD_NAME[MAX_SFR_INSP_COUNT + 1] = {
		_T("CT [0]"), 
		_T("CB [1]"),
		_T("CL [2]"),
		_T("CR [3]"),
		_T("04F_LT_H [4]"),
		_T("04F_LT_V [5]"),
		_T("04F_RT_H [6]"),
		_T("04F_RT_V [7]"),
		_T("04F_BL_H [8]"),
		_T("04F_BL_V [9]"),
		_T("04F_BR_H [10]"),
		_T("04F_BR_V [11]"),

		_T("07F_LT_H [12]"),
		_T("07F_LT_V [13]"),
		_T("07F_RT_H [14]"),
		_T("07F_RT_V [15]"),
		_T("07F_BL_H [16]"),
		_T("07F_BL_V [17]"),
		_T("07F_BR_H [18]"),
		_T("07F_BR_V [19]"),

	};
	

    int DLG = IDC_STATIC_GRID_SFR_ROI;
    CRect rect;
    CWnd *pWnd = (CWnd*)GetDlgItem(DLG);
    int _row = MAX_SFR_INSP_COUNT+1;
	int _col = 4;// 3;
    int margin = 4;
    int gridHeight = 25;
    int gridWidth1 = 110;
    int gridWidth2 = 50;
    int totalWidth = gridWidth1 + (gridWidth2*(_col - 1));
    //
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right = totalWidth + margin;
    rect.bottom = (gridHeight*_row) + margin;
    pWnd->MoveWindow(rect.left, rect.top, rect.right, rect.bottom);//다이얼로그의 크기와 위치값 조정을 위한 함수.

    GetDlgItem(DLG)->GetWindowRect(rect);
    ScreenToClient(rect);
    m_clGridSfrEachRoi.Create(rect, this, DLG, WS_TABSTOP | WS_VISIBLE);

    m_clGridSfrEachRoi.SetTextBkColor(RGB_COLOR_WHITE);
    m_clGridSfrEachRoi.SetFixedBkColor(GRID_COLOR_TITLE);
    m_clGridSfrEachRoi.SetFixedTextColor(RGB_COLOR_WHITE);
    m_clGridSfrEachRoi.SetReference_Setting();
    m_clGridSfrEachRoi.EnableSelection(FALSE);
    m_clGridSfrEachRoi.SetRowCount(_row);
    m_clGridSfrEachRoi.SetColumnCount(_col);
    m_clGridSfrEachRoi.SetFixedRowCount(1);
    m_clGridSfrEachRoi.SetFixedColumnCount(1);

    CString tmpStr = "";
    m_clGridSfrEachRoi.SetItemText(0, 0, "Field");
    m_clGridSfrEachRoi.SetItemText(0, 1, "X");
	m_clGridSfrEachRoi.SetItemText(0, 2, "Y");
	m_clGridSfrEachRoi.SetItemText(0, 3, "DIC");

    int i = 0, j = 0;
    for (i = 0; i < MAX_SFR_INSP_COUNT; i++)
    {
        //SFR_FIELD_NAME
        m_clGridSfrEachRoi.SetItemText(i+1, 0, SFR_FIELD_NAME[i]);
    }
    for (i = 0; i < _row; i++)
    {
        m_clGridSfrEachRoi.SetRowHeight(i, gridHeight);

        for (j = 0; j < _col; j++)
        {
            m_clGridSfrEachRoi.SetItemFormat(i, j, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            if (i == 0)
            {
                if (j == 0)
                {
                    m_clGridSfrEachRoi.SetColumnWidth(j, gridWidth1);
                }
                else {
                    m_clGridSfrEachRoi.SetColumnWidth(j, gridWidth2);
                }
            }
        }
    }
    m_clGridSfrEachRoi.Invalidate();
}
//-----------------------------------------------------------------------------
//
//	버튼 : IMAGE LOAD
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdImageLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	double dZoomX;
	double dZoomY;
	
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
	dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[m_nUnit].m_nWidth);
	dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[m_nUnit].m_nHeight);

    MIL_INT m_nMilSizeX = M_NULL;
    byte* m_pBmtBuf = new byte[g_clLaonGrabberWrapper[m_nUnit].getRawSize() * 3];
	CFileDialog* pDlg = new CFileDialog(TRUE, NULL, NULL, OFN_EXPLORER | OFN_HIDEREADONLY, _T("지원 영상 파일(*.bmp) | *.bmp||"));
    IplImage* m_pIplImg = cvCreateImage(cvSize(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight), IPL_DEPTH_8U, 3);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			MbufLoad(pDlg->GetPathName(), g_clVision.m_MilCcdGrabImage[m_nUnit]);
           // MbufGet( g_clVision.m_MilCcdGrabImage[m_nUnit], (byte*)m_pIplImg->imageData);// (char*)m_pBmtBuf);
            //MbufGet2d(g_clVision.m_MilCcdGrabImage[m_nUnit],0,0, g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight,(byte*)m_pIplImg->imageData);// (char*)m_pBmtBuf);
            MbufGetColor(g_clVision.m_MilCcdGrabImage[m_nUnit], M_PACKED+ M_BGR24, M_ALL_BANDS, (byte*)m_pIplImg->imageData);
            //cvSaveImage("D:\\bmpLoadimg.bmp", m_pIplImg);//bmp로 저장됨
            //ACMISSoftISP::xBMPtoRAW(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, (byte*)m_pIplImg->imageData,  g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight);
            //g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eOutMode
            //ACMISSoftISP::xBMPtoY(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, (byte*)m_pIplImg->imageData, g_clModelData[m_nUnit].m_nWidth, -g_clModelData[m_nUnit].m_nHeight);// , g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eOutMode);
            //

			MbufCopy(g_clVision.m_MilCcdGrabImage[m_nUnit], g_clVision.m_MilCcdProcImage[m_nUnit]);	
			MimResize(g_clVision.m_MilCcdProcImage[m_nUnit], g_clVision.m_MilSmallImage[m_nUnit], dZoomX, dZoomY, M_DEFAULT);
		}
		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : IMAGE SAVE
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdImageSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPath = _T("");
	CString sTemp = _T("");

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	double dZoomX;
	double dZoomY;

	dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[m_nUnit].m_nWidth);
	dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[m_nUnit].m_nHeight);

	CFileDialog* pDlg = new CFileDialog(FALSE, _T("*.bmp|*.BMP|"), _T("IMAGE"), OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("Image Files (*.bmp)|*.bmp|"));
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sPath = pDlg->GetPathName();
			sTemp = sPath.Right(4);

			if(sTemp.CompareNoCase(_T(".bmp")) != 0)
				sPath += _T(".bmp");

			//MIL_ID MilFinalImg;
			//MIL_INT nTransparent;

			//MbufAllocColor(g_clVision.m_MilSystem[0], 3, CCD1_DISP_SIZE_X, CCD1_DISP_SIZE_Y, 8 + M_UNSIGNED, M_IMAGE + M_PROC + M_DISP, &MilFinalImg);
			//MbufClear(MilFinalImg, 0);
			//			
			//nTransparent = MdispInquire(g_clVision.m_MilDisplay[m_nUnit], M_TRANSPARENT, M_NULL);

			//MimResize(g_clVision.m_MilCcdProcImage[m_nUnit], MilFinalImg, dZoomX, dZoomY, M_DEFAULT);
			////MbufCopy(g_clVision.m_MilCcdProcImage[m_nUnit], MilFinalImg);
			//MbufCopyCond(g_clVision.m_MilOverlay[m_nUnit], MilFinalImg, g_clVision.m_MilOverlay[m_nUnit], M_NOT_EQUAL, (double)((INT32)nTransparent));
			//MbufExport(sPath, M_BMP, MilFinalImg);
			//	
			//MbufFree(MilFinalImg);



			//MbufExport(sPath, M_BMP, g_clVision.m_MilCcdProcImage[m_nUnit]);

			ACMISSoftISP::xMakeBMP(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, (byte*)g_clLaonGrabberWrapper[m_nUnit].m_pTestBuffer,
				g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight, g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n);

			Mat MatImage = Mat(g_clModelData[m_nUnit].m_nHeight, g_clModelData[m_nUnit].m_nWidth, CV_8UC3);
			MatImage.data = g_clLaonGrabberWrapper[m_nUnit].m_pTestBuffer;

			TCHAR szPath[SIZE_OF_1K];
			_stprintf_s(szPath, SIZE_OF_1K, _T("%s"), sPath);
			imwrite(szPath, MatImage);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : RAW IMAGE LOAD
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdRawImageLoad()
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
	CFileDialog* pDlg = new CFileDialog(TRUE, NULL, NULL, OFN_EXPLORER | OFN_HIDEREADONLY, _T("지원 영상 파일(*.raw) | *.raw||"));
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			//FILE* fp;

		 	//unsigned char* pBuff = (unsigned char*)malloc(g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nFrameImageSize/*g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight * 2*/);
			//memset(pBuff, 0x00, g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nFrameImageSize/*(g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight * 2)*/);
			
			if(m_pImgBuff != NULL)
			{
				delete m_pImgBuff;
				m_pImgBuff = NULL;
			}

			//unsigned char* pBuff = NULL;
			CFile				ReadFile;
			CFileException		e;
			int					nFileLength;
		
			if(!ReadFile.Open(pDlg->GetPathName(), CFile::modeRead,&e))
			{
				e.ReportError(MB_OK);
				return ;
			}		

			int nRawSize = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize(); 

			nFileLength = ReadFile.GetLength();
			if (nRawSize != nFileLength)
			{
				g_ShowMsgPopup(_T("ERROR"), _T("Yuv / Raw ini파일 확인바랍니다.."), RGB_COLOR_RED);
				return;
			}
			m_pImgBuff = new unsigned char [nFileLength];
			ReadFile.Read(m_pImgBuff, nFileLength);
			ReadFile.Close();
		
            //
            ///
            //
            CCARawImageLoad((byte*)m_pImgBuff, MID_3000K_RAW);   
		}

		delete pDlg;
	}

//#ifdef NORINDA_MODE
//	return;
//	g_clLaonGrabberWrapper[m_nUnit].ImageEncode();	//test
//#endif
}

void CCcdDlg::CCARawImageLoad(BYTE* LoadImg , int index)
{
    double dZoomX = 0.0;
    double dZoomY = 0.0;

    dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[m_nUnit].m_nWidth);
    dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[m_nUnit].m_nHeight);

    TDATASPEC tspec;
	tspec.eOutMode = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eOutMode;					// OUTMODE_YUV422_CrYCbY;
    tspec.eDataFormat = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDataFormat;			//DATAFORMAT_BAYER_12BIT;
    tspec.eSensorType = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eSensorType;			//SENSORTYPE_RCCB;
	tspec.eDemosaicMethod = g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod;	//DEMOSAICMETHOD_BL33
	tspec.nBlackLevel = 0;


	memcpy(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, LoadImg, g_clLaonGrabberWrapper[m_nUnit].getRawSize());


	ACMISSoftISP::xMakeBMP(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, (byte*)g_clLaonGrabberWrapper[m_nUnit].m_pFrameBMPBuffer,
		g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight, tspec);



    g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.imageItp->imageData = (char*)g_clLaonGrabberWrapper[m_nUnit].m_pFrameBMPBuffer;


    cvSplit(g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.imageItp,
        g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[0],
        g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[1],
        g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[2],
        NULL);


#ifdef ON_LINE_MIL
    MbufPut(g_clVision.m_MilCcdProcChild[m_nUnit][0], g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[2]->imageData);
    MbufPut(g_clVision.m_MilCcdProcChild[m_nUnit][1], g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[1]->imageData);
    MbufPut(g_clVision.m_MilCcdProcChild[m_nUnit][2], g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[0]->imageData);

    MimResize(g_clVision.m_MilCcdProcImage[m_nUnit], g_clVision.m_MilSmallImage[m_nUnit], dZoomX, dZoomY, M_DEFAULT);



#endif
}
//-----------------------------------------------------------------------------
//
//	버튼 : RAW IMAGE SAVE
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdRawImageSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog* pDlg = new CFileDialog(FALSE, _T("*.raw|*.raw|"), _T("IMAGE"), OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("Image Files (*.raw)|*.raw|"));
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			CFile           savefile;
			CFileException  e;

			if( !savefile.Open(pDlg->GetPathName(), CFile::modeCreate | CFile::modeWrite, &e ))
			{
				AfxMessageBox( "File open fail:" + e.m_cause );
				delete pDlg;
				return;
			}

			//savefile.Write(g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.image->imageData , g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nFrameRawSize);

			savefile.Write(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize());

			
			savefile.Close();			
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : POS
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdPos()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nMoveType = MOVE_POS;

	m_clColorButtonPos.state = 1;
	m_clColorButtonSize.state = 0;
    m_clColorButtonPos.Invalidate();
    m_clColorButtonSize.Invalidate();
}

//-----------------------------------------------------------------------------
//
//	버튼 : SIZE
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdSize()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nMoveType = MOVE_SIZE;

	m_clColorButtonPos.state = 0;
	m_clColorButtonSize.state = 1;
    m_clColorButtonPos.Invalidate();
    m_clColorButtonSize.Invalidate();
}

//-----------------------------------------------------------------------------
//
//	버튼 : 1/10/20/50(MOVE GAP)
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdGap()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szData[SIZE_OF_100BYTE];

	switch (m_nMoveSize)
	{
	case 1:		m_nMoveSize = 10;	break;
	case 10:	m_nMoveSize = 20;	break;
	case 20:	m_nMoveSize = 50;	break;
	case 50:	m_nMoveSize = 1;	break;
	}

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), m_nMoveSize);
	m_clColorButtonGap.SetWindowText(szData);
}

//-----------------------------------------------------------------------------
//
//	버튼 : △
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_FovSetMode == true)
    {
        g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].MoveRectFov(m_nMoveType, MOVE_UP, m_nMoveSize);
    }
    else if (g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_SnrSetMode == true)
    {
        g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].MoveRectSnr(m_nMoveType, MOVE_UP, m_nMoveSize);
    }
    else
    {
        g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].MoveRectSfr(m_nMoveType, MOVE_UP, m_nMoveSize);
    }
}

//-----------------------------------------------------------------------------
//
//	버튼 : ▽
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_FovSetMode == true)
    {
        g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].MoveRectFov(m_nMoveType, MOVE_DOWN, m_nMoveSize);
    }
    else if (g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_SnrSetMode == true)
    {
        g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].MoveRectSnr(m_nMoveType, MOVE_DOWN, m_nMoveSize);
    }
    else
    {
        g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].MoveRectSfr(m_nMoveType, MOVE_DOWN, m_nMoveSize);
    }
}

//-----------------------------------------------------------------------------
//
//	버튼 : ◁
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_FovSetMode == true)
    {
        g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].MoveRectFov(m_nMoveType, MOVE_LEFT, m_nMoveSize);
    }
    else if (g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_SnrSetMode == true)
    {
        g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].MoveRectSnr(m_nMoveType, MOVE_LEFT, m_nMoveSize);
    }
    else
    {
        g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].MoveRectSfr(m_nMoveType, MOVE_LEFT, m_nMoveSize);
    }
}

//-----------------------------------------------------------------------------
//
//	버튼 : ▷
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_FovSetMode == true)
    {
        g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].MoveRectFov(m_nMoveType, MOVE_RIGHT, m_nMoveSize);
    }
    else if (g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_SnrSetMode == true)
    {
        g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].MoveRectSnr(m_nMoveType, MOVE_RIGHT, m_nMoveSize);
    }
    else
    {
        g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].MoveRectSfr(m_nMoveType, MOVE_RIGHT, m_nMoveSize);
    }
	
}

//-----------------------------------------------------------------------------
//
//	버튼 : 초기화
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdInit()
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
	m_clColorButtonFovMarkView.state = 0;
	g_clVision.ClearOverlay(m_nUnit);
	g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_FovSetMode = false;

	g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].DrawRectSfr(999);

	m_clColorButtonSnrMarkView.Invalidate();
	m_clColorButtonFovMarkView.Invalidate();

	g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].InitSfrRoi();
	
}

//-----------------------------------------------------------------------------
//
//	버튼 : 원형마크 등록
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdCircleMarkRegist()
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

	if (g_ShowMsgModal(_T("확인"), _T("원형 마크 위치를 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
		return;

	g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].RegistCircleMark();

	AddLog(_T("[SAVE] 원형 마크 위치 저장"), 0, m_nUnit);
	
}

//-----------------------------------------------------------------------------
//
//	버튼 : 검사영역 저장
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdInspAreaSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("자동 운전 중 사용불가합니다."), RGB_COLOR_RED);
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	/*if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}*/

	if (g_ShowMsgModal(_T("확인"), _T("SFR 검사영역을 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
		return;

	g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].SaveSfrRoi();

	AddLog(_T("[SAVE] SFR ROI 영역 저장"), false, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	버튼 : SFR SPEC
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdSfrSpec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_clSfrSpecDlg.SetUnit(m_nUnit);
	m_clSfrSpecDlg.ShowWindow(SW_SHOW);
}

//-----------------------------------------------------------------------------
//
//	버튼 : SFR 검사
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdSfrInsp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit, true);
		return;
	}
#ifdef ON_LINE_MIL
    g_clVision.ClearOverlay(m_nUnit);
#endif

	int nRawSize = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize();

	if (nRawSize > 4000000)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("Raw 영상에서 측정가능합니다."), RGB_COLOR_RED);
		return;
	}

	g_clTaskWork[m_nUnit].InitSfrInsp();
	//g_pCarAABonderDlg->DrawGraph(m_nUnit, 0);
	//g_pCarAABonderDlg->DrawGraph(m_nUnit, 1); 
	

	AddLog(_T("	"), 0, m_nUnit);
	AddLog(_T("[수동검사] SFR 측정"), 0, m_nUnit);
	AddLog(_T("	"), 0, m_nUnit);


	if (g_GetSFR(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, m_nUnit, SFR_FINAL) != -1)
	{
		g_clTaskWork[m_nUnit].m_nCountOfTotalStepAA = 0;
		g_CheckEolLight(m_nUnit, 0);
		g_CalcImageAlign(m_nUnit);
		g_CheckEolOc(m_nUnit);			//MANUAL EOL OC CHECK
		//g_CheckEolRotation(m_nUnit);	//MANUAL EOL ROTATION

		g_GetSfrMinMaxValue(m_nUnit,false);
		g_pCarAABonderDlg->_DrawBarGraph(m_nUnit);
	}
 
    


	//g_clPriInsp[m_nUnit].func_Insp_RotateTilt(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, true);

	//g_clPriInsp[m_nUnit].Func_FinalImageSave(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer);		//230428 chart jpg 이미지에 roi,sfr 값남기기


	//g_clPriInsp[m_nUnit].Func_FinalImageSave(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, 0, false);

	//g_Get_AA_MTF(m_nUnit, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, SFR_FIRST);
}

//-----------------------------------------------------------------------------
//
//	SFR 그래프를 그린다.
//
//-----------------------------------------------------------------------------
void CCcdDlg::DrawGraph()
{
#ifdef GRAPH_NO_USE
    return;
#endif
	strGraph2D_Y_Axis_Info strAxisYInfo;	//! Y축
	strValueLineXInfo      strXLineInfo;	//! X축
	int nIndexLineX_MTF4 = 0;
	int nIndexLineX_MTF8 = 0;
	int nIndexLineX_MTF50 = 0;
	int i, j;
		

	//! 1) 그래프에 데이터를 입력한다. 
	//! 2) 만약, 커서 (Mouse로 조작 가능한 그래프 데이터 표시 기능)가 없으면 추가한다. 
	//! 3) 그래프를 다시 그린다. 

	if (m_pGraphWnd != NULL)
	{
		if (m_nGraphMode == 1)
		{
			for (i = 0; i < MAX_GRAPH_OVERLAP_COUNT; i++)
			{
				//! <-----------------------------------------------------------
				//! 그래프가 눈에 보이는 여부를 설정한다.
				m_pGraphWnd->GetResourceYInfo(strAxisYInfo, i);

				m_nDataSize[i] = g_clTaskWork[m_nUnit].m_nCountOfStepAA;

				if (m_nDataSize[i] <= 0)
				{
					strAxisYInfo.bShowGraph = false;
				}
				else
				{
					strAxisYInfo.bShowGraph = true;//m_bFlagVisible[i];
				}

				m_pGraphWnd->SetResourceYInfo(strAxisYInfo, i);

				for (j = 0; j < m_nDataSize[i]; j++)
				{
#if (____AA_WAY == PCB_TILT_AA)
					m_dDataX[i][j] = g_clTaskWork[m_nUnit].m_stSfrInsp.fMotorPos[j][2] * -1;
					//m_adDataX[iIndex_Plot][j][i_tmp - iIndex] = Task.SFR.fMotorPos[i_tmp][theApp.MainDlg->TITLE_MOTOR_Z] * -1;
#elif (____AA_WAY == LENS_TILT_AA)
					m_dDataX[i][j] = g_clTaskWork[m_nUnit].m_stSfrInsp.fMotorPos[j][2];//4];
					//m_adDataX[iIndex_Plot][j][i_tmp - iIndex] = Task.SFR.fMotorPos[i_tmp][theApp.MainDlg->TITLE_MOTOR_Z];
					//움직이는 Z축 값 부호에 따라 다르게 
#endif
					//m_dDataX[i][j] = g_clTaskWork[m_nUnit].m_stSfrInsp.fMotorPos[j][2];					
					m_dDataY[i][j] = g_clTaskWork[m_nUnit].m_stSfrInsp.fSFR_AVR_N4[j][i];
				}

				//! 그래프에 데이터 입력
				//m_apGraphWnd[i]->SetPlotData(m_adDataX[i], m_adDataY[i], m_aiDataSize[i]);
				m_pGraphWnd->SetPlotData(m_dDataX[i], m_dDataY[i], m_nDataSize[i], i);
				
				//! <-----------------------------------------------------------------------------------------------------------------------------------------
				//! X축 특정값 표시선 관련

				//! [추가 설명] X축 특정값 표시선 정보는 입력된 순서대로 내부에서 CArray~ 방식으로 저장되므로, 입력된 순서값을 이용하여 다시 불러올 수 있다.
				nIndexLineX_MTF4 = (i * 3) + INDEX_MTF4;
				nIndexLineX_MTF8 = (i * 3) + INDEX_MTF8;
				nIndexLineX_MTF50 = (i * 3) + INDEX_MTF50;

				m_pGraphWnd->GetXValueLineInfo(nIndexLineX_MTF4, strXLineInfo);

				if (m_nDataSize[i] <= 0)
				{
					strXLineInfo.bShow = false;
				}
				else
				{
					strXLineInfo.bShow = true;//m_bFlagVisible[i];
				}

				strXLineInfo.dbValue = 0.125;

				m_pGraphWnd->SetXValueLineInfo(nIndexLineX_MTF4, strXLineInfo);
			}
			//! <-----------------------------------------------------------------------------------------------------------------------------------------
		}
		else if (m_nGraphMode == 2)
		{
			for (i = 0; i < MAX_GRAPH_OVERLAP_COUNT; i++)
			{
				//! <-----------------------------------------------------------
				//! 그래프가 눈에 보이는 여부를 설정한다.
				m_pGraphWnd->GetResourceYInfo(strAxisYInfo, i);

				m_nDataSize[i] = g_clTaskWork[m_nUnit].m_nCountOfStepAA;

				if (m_nDataSize[i] <= 0)
				{
					strAxisYInfo.bShowGraph = false;
				}
				else
				{
					strAxisYInfo.bShowGraph = true;//m_bFlagVisible[i];
				}

				m_pGraphWnd->SetResourceYInfo(strAxisYInfo, i);

				for (j = 0; j < m_nDataSize[i]; j++)
				{
#if (____AA_WAY == PCB_TILT_AA)
					m_dDataX[i][j] = g_clTaskWork[m_nUnit].m_stSfrInsp.fMotorPos[j][2] * -1;
#else
					m_dDataX[i][j] = g_clTaskWork[m_nUnit].m_stSfrInsp.fMotorPos[j][2];//4];
#endif
					m_dDataY[i][j] = g_clTaskWork[m_nUnit].m_stSfrInsp.fSfrN8[j][i];
				}

				//! 그래프에 데이터 입력
				//m_apGraphWnd[i]->SetPlotData(m_adDataX[i], m_adDataY[i], m_aiDataSize[i]);
				m_pGraphWnd->SetPlotData(m_dDataX[i], m_dDataY[i], m_nDataSize[i], i);

				//! <-----------------------------------------------------------------------------------------------------------------------------------------
				//! X축 특정값 표시선 관련

				//! [추가 설명] X축 특정값 표시선 정보는 입력된 순서대로 내부에서 CArray~ 방식으로 저장되므로, 입력된 순서값을 이용하여 다시 불러올 수 있다.
				nIndexLineX_MTF4 = (i * 3) + INDEX_MTF4;
				nIndexLineX_MTF8 = (i * 3) + INDEX_MTF8;
				nIndexLineX_MTF50 = (i * 3) + INDEX_MTF50;

				m_pGraphWnd->GetXValueLineInfo(nIndexLineX_MTF4, strXLineInfo);

				if (m_nDataSize[i] <= 0)
				{
					strXLineInfo.bShow = false;
				}
				else
				{
					strXLineInfo.bShow = true;//m_bFlagVisible[i];
				}

				strXLineInfo.dbValue = 0.125;

				m_pGraphWnd->SetXValueLineInfo(nIndexLineX_MTF4, strXLineInfo);
			}
			//! <-----------------------------------------------------------------------------------------------------------------------------------------
		}
		else
		{
			for (i = 0; i < MAX_GRAPH_OVERLAP_COUNT; i++)
			{
				//! <-----------------------------------------------------------
				//! 그래프가 눈에 보이는 여부를 설정한다.
				m_pGraphWnd->GetResourceYInfo(strAxisYInfo, i);

				m_nDataSize[i] = g_clTaskWork[m_nUnit].m_stSfrInsp.nDataCount[i];

				if (m_nDataSize[i] <= 0)
				{
					strAxisYInfo.bShowGraph = false;
				}
				else
				{
					strAxisYInfo.bShowGraph = true;//m_bFlagVisible[i];
				}

				m_pGraphWnd->SetResourceYInfo(strAxisYInfo, i);

				for (j = 0; j < g_clTaskWork[m_nUnit].m_stSfrInsp.nDataCount[i]; j++)
				{
					m_dDataY[i][g_clTaskWork[m_nUnit].m_stSfrInsp.nDataCount[i] - j - 1] = m_dDataY[i][g_clTaskWork[m_nUnit].m_stSfrInsp.nDataCount[i] + j] = g_clTaskWork[m_nUnit].m_stSfrInsp.dSfrDataY[i][j];
					m_dDataX[i][g_clTaskWork[m_nUnit].m_stSfrInsp.nDataCount[i] - j - 1] = -g_clTaskWork[m_nUnit].m_stSfrInsp.dSfrDataX[i][j];
					m_dDataX[i][g_clTaskWork[m_nUnit].m_stSfrInsp.nDataCount[i] + j] = g_clTaskWork[m_nUnit].m_stSfrInsp.dSfrDataX[i][j];
				}

				//! 그래프에 데이터 입력
				//m_apGraphWnd[i]->SetPlotData(m_adDataX[i], m_adDataY[i], m_aiDataSize[i]);
				m_pGraphWnd->SetPlotData(m_dDataX[i], m_dDataY[i], g_clTaskWork[m_nUnit].m_stSfrInsp.nDataCount[i] * 2, i);

				//! <-----------------------------------------------------------------------------------------------------------------------------------------
				//! X축 특정값 표시선 관련

				//! [추가 설명] X축 특정값 표시선 정보는 입력된 순서대로 내부에서 CArray~ 방식으로 저장되므로, 입력된 순서값을 이용하여 다시 불러올 수 있다.
				nIndexLineX_MTF4 = (i * 3) + INDEX_MTF4;
				nIndexLineX_MTF8 = (i * 3) + INDEX_MTF8;
				nIndexLineX_MTF50 = (i * 3) + INDEX_MTF50;

				m_pGraphWnd->GetXValueLineInfo(nIndexLineX_MTF4, strXLineInfo);

				if (m_nDataSize[i] <= 0)
				{
					strXLineInfo.bShow = false;
				}
				else
				{
					strXLineInfo.bShow = true;//m_bFlagVisible[i];
				}

				strXLineInfo.dbValue = 0.125;

				m_pGraphWnd->SetXValueLineInfo(nIndexLineX_MTF4, strXLineInfo);
				//! <-----------------------------------------------------------------------------------------------------------------------------------------
			}//! for ( j = 0; j < iBufSize_Graph_Overlap; j++ )
		}

		//! 커서가 없으면, 추가한다.
		//if ( m_apGraphWnd[i]->GetCurrentCursorSize() <= 0 )
		//{
		//	bRet = m_apGraphWnd[i]->AddCursorInDataIndex(0, false);
		//  m_apGraphWnd[i]->SetCursorValueVisible(0, false, false, false);
		//}

		m_pGraphWnd->m_bChanged = true;
		m_pGraphWnd->Invalidate();
	}
}

//-----------------------------------------------------------------------------
//
//	그리드에 SFR 데이터 표시
//
//-----------------------------------------------------------------------------
void CCcdDlg::DisplaySfrData()
{
	/*TCHAR szData[SIZE_OF_100BYTE];
	int i;

	for (i = 0; i < 5; i++)
	{
		_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), (int)(g_clTaskWork[m_nUnit].m_stSfrInsp.Sfr_Pos[0][i].x + 0.5));
		m_clGridSfr.SetItemText(i + 1, 1, szData);

		_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), (int)(g_clTaskWork[m_nUnit].m_stSfrInsp.Sfr_Pos[0][i].y + 0.5));
		m_clGridSfr.SetItemText(i + 1, 2, szData);

		_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03f"), g_clTaskWork[m_nUnit].m_stSfrInsp.fSFR_AVR_N4[0][i]);
		m_clGridSfr.SetItemText(i + 1, 3, szData);

		_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03f"), g_clTaskWork[m_nUnit].m_stSfrInsp.fSfrN8[0][i]);
		m_clGridSfr.SetItemText(i + 1, 4, szData);
		
		_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03f"), g_clTaskWork[m_nUnit].m_stSfrInsp.fImageAlign[0][0]);
		m_clGridSfr.SetItemText(i + 1, 5, szData);

		_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03f"), g_clTaskWork[m_nUnit].m_stSfrInsp.fImageAlign[0][1]);
		m_clGridSfr.SetItemText(i + 1, 6, szData);

		_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03f"), g_clTaskWork[m_nUnit].m_stSfrInsp.fImageAlign[0][2]);
		m_clGridSfr.SetItemText(i + 1, 7, szData);

		_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03f"), g_clTaskWork[m_nUnit].m_stSfrInsp.fImageAlign[0][3]);
		m_clGridSfr.SetItemText(i + 1, 8, szData);
	}

	m_clGridSfr.Invalidate();*/
}

//-----------------------------------------------------------------------------
//
//	버튼 : ACTIVE ALIGN
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdActiveAlign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}

//-----------------------------------------------------------------------------
//
//	버튼 : PIXEL DEFECT
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdPixelDefect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

    g_clVision.ClearOverlay(m_nUnit); 

	g_clVision.DrawOverlayAll(m_nUnit);
	AddLog(_T("[수동검사] Dead-pixel 검사 완료"), 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	버튼 : STAIN
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdStain()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

#ifdef ON_LINE_GRABBER
	/*if (g_clLaonGrabberWrapper[m_nUnit].GetDeviceOpen() == false)
	{
		AddLog(_T("[수동검사] FRAME GRABBER 연결 해제 상태"), 1, m_nUnit);
		return;
	}

	if (g_clLaonGrabberWrapper[m_nUnit].GetCurrentState() != CCD_GRAB_LIVE)
	{
		AddLog(_T("[수동검사] CCD 동영상 획득 실패"), 1, m_nUnit);
		return;
	}*/
#endif
    g_clVision.ClearOverlay(m_nUnit);

	//MbufClear(g_clVision.MilDefectOverlayImage[m_nUnit], (MIL_DOUBLE)g_clVision.m_nMilDefectTransparent[m_nUnit]);
	//MbufClear(g_clVision.MilDefectImage[m_nUnit], 0);

	//g_clPriInsp[m_nUnit].func_Insp_Stain(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, false, 999);


	g_clPriInsp[m_nUnit].LCBInsp((BYTE*)g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer);

	g_clPriInsp[m_nUnit].FDFInsp((BYTE*)g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer);

	g_clPriInsp[m_nUnit].Blemish_YmeanInsp((BYTE*)g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer);

	g_CheckEolLight(m_nUnit, 1);


	AddLog(_T("[MANUAL] STAIN TEST 완료"), 0, m_nUnit);
    g_clVision.DrawOverlayAll(m_nUnit);
	
}

//-----------------------------------------------------------------------------
//
//	버튼 : UNIFORMITY
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdUniformity()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit, true);
		return;
	}


 //   g_clVision.ClearOverlay(m_nUnit);
	////Color Uniformity 5000k 검사
	//if (g_clPriInsp[m_nUnit].func_Insp_Uniformity(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, MID_5000k_RAW, false) == false)//MID_5000k_RAW, LOW_LEVEL_RAW 
	//{
	//	AddLog(_T("[수동검사] COLOR UNIFORMITY 검사 실패"), 0, m_nUnit);
	//}

	//AddLog(_T("[수동검사] COLOR UNIFORMITY 검사 완료"), 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	버튼 : CURRENT
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdCurrent()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	//if (g_clPriInsp[m_nUnit].func_Insp_CurrentMeasure(true, false) == false)
	//if (g_clPriInsp[m_nUnit].func_Insp_Ultra_CurrentMeasure(true, false) == false)
	//if(g_pCarAABonderDlg->CurrentInsp() == false)
	if (g_clPriInsp[m_nUnit].func_Insp_CurrentMeasure(true) == false)
	{
		AddLog(_T("[수동검사] Current 측정 실패"), 0, m_nUnit);
		return;
	}

	AddLog(_T("[수동검사] Current 측정 완료"), 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	버튼 : I2C PATTERN
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdI2cPattern()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	bool nRetVal = false;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

#ifdef ON_LINE_GRABBER
	if (g_clLaonGrabberWrapper[m_nUnit].GetDeviceOpen() == false)
	{
		AddLog(_T("[수동검사] FRAME GRABBER 연결 해제 상태"), 1, m_nUnit);
		return;
	}

	/*if (g_clLaonGrabberWrapper[m_nUnit].GetCurrentState() != CCD_GRAB_LIVE)
	{
		AddLog(_T("[수동검사] CCD 동영상 획득 실패"), 1, m_nUnit);
		return;
	}	*/

#endif
	nRetVal = g_clPriInsp[m_nUnit].func_Insp_ErrorFlag_Read(false);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[수동검사] ERROR FLAG READ 완료(%d)"), nRetVal);
	AddLog(szLog, 0, m_nUnit);



}

//-----------------------------------------------------------------------------
//
//	버튼 : MTF
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdMtf()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#ifndef _M_X64
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

#ifdef ON_LINE_GRABBER
	if (g_clLaonGrabberWrapper[m_nUnit].GetDeviceOpen() == false)
	{
		AddLog(_T("[수동검사] FRAME GRABBER 연결 해제 상태"), 1, m_nUnit);
		return;
	}

	if (g_clLaonGrabberWrapper[m_nUnit].GetCurrentState() != CCD_GRAB_LIVE)
	{
		AddLog(_T("[수동검사] CCD 동영상 획득 실패") ,1, m_nUnit);
		return;
	}
#endif

	_stprintf_s(szPath, SIZE_OF_1K, _T("D:\\LKAS"));
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("D:\\LKAS\\RESULT"));
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("D:\\LKAS\\RESULT\\MTF"));
	if (clFinder.FindFile(szPath) == FALSE)
		CreateDirectory(szPath, NULL);

	_stprintf_s(szPath, SIZE_OF_1K, _T("D:\\LKAS\\RESULT\\MTF"));

	if (g_clMandoFinalSFR[m_nUnit].func_check_MandoSFR_Final(g_clLaonGrabberWrapper[m_nUnit].m_pImageInspBuff, g_clLaonGrabberWrapper[m_nUnit].m_pImgBuff12Bit, szPath, true, false, false) != 0)
	{
		AddLog(_T("[수동검사] FINAL 검사 실패"), 1, m_nUnit);
		return;
	}

	AddLog(_T("[수동검사] FINAL 검사 완료"), 0, m_nUnit);
#endif
}

//-----------------------------------------------------------------------------
//
//	버튼 : DARK
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
//	버튼 : DEVICE OPEN
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdDeviceOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#ifdef ON_LINE_GRABBER
    g_clLaonGrabberWrapper[m_nUnit].OpenDevice();
	
#endif


	//
}

//-----------------------------------------------------------------------------
//
//	버튼 : DEVICE CLOSE
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdDeviceClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#ifdef ON_LINE_GRABBER
    g_clLaonGrabberWrapper[m_nUnit].CloseDevice();
#endif
}

//-----------------------------------------------------------------------------
//
//	버튼 : CONNECT
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#ifndef ON_LINE_GRABBER
	return;
#endif
}

//-----------------------------------------------------------------------------
//
//	버튼 : BOARD INIT
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdBoardInit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	bool nRetVal = false;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

#ifdef ON_LINE_GRABBER
	if (g_clLaonGrabberWrapper[m_nUnit].GetDeviceOpen() == false)
	{
		AddLog(_T("[수동검사] FRAME GRABBER 연결 해제 상태"), 1, m_nUnit);
		return;
	}

#endif
	nRetVal = g_clPriInsp[m_nUnit].func_Insp_Test_SensorRead(false);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[수동검사] SENSOR ID READ 완료(%d)"), nRetVal);
	AddLog(szLog, 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	버튼 : SENSOR INIT
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdSensorInit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#ifndef ON_LINE_GRABBER
	return;
#endif

	g_clLaonGrabberWrapper[m_nUnit].IniAnalyze();
}

//-----------------------------------------------------------------------------
//
//	버튼 : GRAB START
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdGrabStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#ifndef ON_LINE_GRABBER
	return;
#endif

	g_clLaonGrabberWrapper[m_nUnit].StartGrabCcdProcess();// StartGrab();
	g_pCarAABonderDlg->m_clCcdGrabThread[m_nUnit].UpdateGrabStartTime();
}

//-----------------------------------------------------------------------------
//
//	버튼 : GRAB STOP
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdGrabStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#ifndef ON_LINE_GRABBER
	return;
#endif

	g_clLaonGrabberWrapper[m_nUnit].StopGrab();
}

//-----------------------------------------------------------------------------
//
//	버튼 : DISCONNECT
//
//-----------------------------------------------------------------------------
void CCcdDlg::OnBnClickedButtonCcdDisconnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#ifndef ON_LINE_GRABBER
	return;
#endif
}

//-----------------------------------------------------------------------------
//
// PreTranslateMessage
//
//-----------------------------------------------------------------------------
BOOL CCcdDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_IMAGE_LOAD)->m_hWnd)
		{
			//m_clColorButtonImgLoad.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_IMAGE_SAVE)->m_hWnd)
		{
			//m_clColorButtonImgSave.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_RAW_IMAGE_LOAD)->m_hWnd)
		{
			//m_clColorButtonRawImgLoad.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_RAW_IMAGE_SAVE)->m_hWnd)
		{
			//m_clColorButtonRawImgSave.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_UP)->m_hWnd)
		{
			//m_clColorButtonUp.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_DOWN)->m_hWnd)
		{
			//m_clColorButtonDown.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_LEFT)->m_hWnd)
		{
			//m_clColorButtonLeft.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_RIGHT)->m_hWnd)
		{
			//m_clColorButtonRight.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_SFR_INSP)->m_hWnd)
		{
			//m_clColorButtonSfrInsp.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_ACTIVE_ALIGN)->m_hWnd)
		{
			//m_clColorButtonActiveAlign.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_INIT)->m_hWnd)
		{
			//m_clColorButtonInit.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_CIRCLE_MARK_REGIST)->m_hWnd)
		{
			//m_clColorButtonCircleMarkRegist.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_INSP_AREA_SAVE)->m_hWnd)
		{
			//m_clColorButtonInspAreaSave.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_SFR_SPEC)->m_hWnd)
		{
			//m_clColorButtonSfrSpec.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_PIXEL_DEFECT)->m_hWnd)
		{
			//m_clColorButtonPixelDefect.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_STAIN)->m_hWnd)
		{
			//m_clColorButtonStain.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_UNIFORMITY)->m_hWnd)
		{
			//m_clColorButtonUniformity.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_CURRENT)->m_hWnd)
		{
			//m_clColorButtonCurrent.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_I2C_PATTERN)->m_hWnd)
		{
			//m_clColorButtonI2cTestPattern.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_MTF)->m_hWnd)
		{
			//m_clColorButtonMTF.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_DEVICE_OPEN)->m_hWnd)
		{
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_DEVICE_CLOSE)->m_hWnd)
		{
			//m_clColorButtonDeviceClose.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_CONNECT)->m_hWnd)
		{
			//m_clColorButtonConnect.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_BOARD_INIT)->m_hWnd)
		{
			//m_clColorButtonBoardInit.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_SENSOR_INIT)->m_hWnd)
		{
			//m_clColorButtonSensorInit.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_GRAB_START)->m_hWnd)
		{
			//m_clColorButtonGrabStart.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_GRAB_STOP)->m_hWnd)
		{
			//m_clColorButtonGrabStop.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_DISCONNECT)->m_hWnd)
		{
			//m_clColorButtonDisconnect.SetSelected(true);
		}
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_IMAGE_LOAD)->m_hWnd)
		{
			//m_clColorButtonImgLoad.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_IMAGE_SAVE)->m_hWnd)
		{
			//m_clColorButtonImgSave.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_RAW_IMAGE_LOAD)->m_hWnd)
		{
			//m_clColorButtonRawImgLoad.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_RAW_IMAGE_SAVE)->m_hWnd)
		{
			//m_clColorButtonRawImgSave.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_UP)->m_hWnd)
		{
			//m_clColorButtonUp.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_DOWN)->m_hWnd)
		{
			//m_clColorButtonDown.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_LEFT)->m_hWnd)
		{
			//m_clColorButtonLeft.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_RIGHT)->m_hWnd)
		{
			//m_clColorButtonRight.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_SFR_INSP)->m_hWnd)
		{
			//m_clColorButtonSfrInsp.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_ACTIVE_ALIGN)->m_hWnd)
		{
			//m_clColorButtonActiveAlign.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_INIT)->m_hWnd)
		{
			//m_clColorButtonInit.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_CIRCLE_MARK_REGIST)->m_hWnd)
		{
			//m_clColorButtonCircleMarkRegist.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_INSP_AREA_SAVE)->m_hWnd)
		{
			//m_clColorButtonInspAreaSave.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_SFR_SPEC)->m_hWnd)
		{
			//m_clColorButtonSfrSpec.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_PIXEL_DEFECT)->m_hWnd)
		{
			//m_clColorButtonPixelDefect.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_STAIN)->m_hWnd)
		{
			//m_clColorButtonStain.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_UNIFORMITY)->m_hWnd)
		{
			//m_clColorButtonUniformity.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_CURRENT)->m_hWnd)
		{
			//m_clColorButtonCurrent.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_I2C_PATTERN)->m_hWnd)
		{
			//m_clColorButtonI2cTestPattern.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_MTF)->m_hWnd)
		{
			//m_clColorButtonMTF.SetSelected(false);
		}

		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_DEVICE_OPEN)->m_hWnd)
		{
			//m_clColorButtonDeviceOpen.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_DEVICE_CLOSE)->m_hWnd)
		{
			//m_clColorButtonDeviceClose.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_CONNECT)->m_hWnd)
		{
			//m_clColorButtonConnect.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_BOARD_INIT)->m_hWnd)
		{
			//m_clColorButtonBoardInit.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_SENSOR_INIT)->m_hWnd)
		{
			//m_clColorButtonSensorInit.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_GRAB_START)->m_hWnd)
		{
			//m_clColorButtonGrabStart.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_GRAB_STOP)->m_hWnd)
		{
			//m_clColorButtonGrabStop.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCD_DISCONNECT)->m_hWnd)
		{
			//m_clColorButtonDisconnect.SetSelected(false);
		}
	}

	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}
	
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CCcdDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	double dZoomX = 0.0;
	double dZoomY = 0.0;

	dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[m_nUnit].m_nWidth);
	dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[m_nUnit].m_nHeight);

	CFileDialog* pDlg = new CFileDialog(TRUE, NULL, NULL, OFN_EXPLORER | OFN_HIDEREADONLY, _T("지원 영상 파일(*.raw) | *.raw||"));
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			if (m_pImgBuff != NULL)
			{
				delete m_pImgBuff;
				m_pImgBuff = NULL;
			}

			CFile				ReadFile;
			CFileException		e;
			int					nFileLength;
			IplImage* pImg = cvCreateImage(cvSize(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight), IPL_DEPTH_8U, 1);

			if (!ReadFile.Open(pDlg->GetPathName(), CFile::modeRead, &e))
			{
				e.ReportError(MB_OK);
				return;
			}
			nFileLength = ReadFile.GetLength();
			m_pImgBuff = new unsigned char[nFileLength];
			ReadFile.Read(m_pImgBuff, nFileLength);
			ReadFile.Close();

			pImg->imageData = (char*)m_pImgBuff;
			
			//12Bit 이미지 저장
			//memcpy(g_clLaonGrabberWrapper[m_nUnit].m_pImgBuff12Bit, m_pImgBuff, nFileLength);

			g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.iPixelFormat = MIU_MONO8;
			ConvertColor(g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.iPixelFormat,
				pImg,
				g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.imageItp,
				g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.ColorConvertItp,
				g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nWidth,
				g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nHeight);

			// 영상 FLIP
			if (g_clModelData[m_nUnit].m_nCcdFlipUse == 1)
				cvFlip(g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.imageItp, g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.imageItp, 1);

			//cvCopy(g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.imageItp, g_clLaonGrabberWrapper[m_nUnit].m_pImageInspBuff);

			cvSplit(g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.imageItp,
				g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[0],
				g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[1],
				g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[2],
				NULL);
			 
			MbufPut(g_clVision.m_MilCcdProcChild[m_nUnit][0], g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[2]->imageData);
			MbufPut(g_clVision.m_MilCcdProcChild[m_nUnit][1], g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[1]->imageData);
			MbufPut(g_clVision.m_MilCcdProcChild[m_nUnit][2], g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[0]->imageData);

			MimResize(g_clVision.m_MilCcdProcImage[m_nUnit], g_clVision.m_MilSmallImage[m_nUnit], dZoomX, dZoomY, M_DEFAULT);

			g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.iPixelFormat = MIU_BAYERBG12_PACKED;
			cvReleaseImage(&pImg);
	
		}

		delete pDlg;
	}

	//double dZoomX = 0.0;
	//double dZoomY = 0.0;
	//CFile ReadFile;
	//CFileException e;
	//int nFileLength = 0;


	//if (g_clModelData[m_nUnit].m_nDomeChartUse == 1)
	//{
	//	dZoomX = ((double)CCD1_DISP_SIZE_X / (double)g_clModelData[m_nUnit].m_nWidth);
	//	dZoomY = ((double)CCD1_DISP_SIZE_Y / (double)g_clModelData[m_nUnit].m_nHeight);
	//}
	//else
	//{
	//	dZoomX = ((double)CCD2_DISP_SIZE_X / (double)g_clModelData[m_nUnit].m_nWidth);
	//	dZoomY = ((double)CCD2_DISP_SIZE_Y / (double)g_clModelData[m_nUnit].m_nHeight);
	//}

	//CFileDialog* pDlg = new CFileDialog(TRUE, NULL, NULL, OFN_EXPLORER | OFN_HIDEREADONLY, _T("지원 영상 파일(*.raw) | *.raw||"));
	//if (pDlg != NULL)
	//{
	//	if (pDlg->DoModal() == IDOK)
	//	{			
	//		if (m_pImgBuff != NULL)
	//		{
	//			delete m_pImgBuff;
	//			m_pImgBuff = NULL;
	//		}

	//		
	//		if (!ReadFile.Open(pDlg->GetPathName(), CFile::modeRead, &e))
	//		{
	//			e.ReportError(MB_OK);
	//			delete pDlg;
	//			return;
	//		}

	//		nFileLength = ReadFile.GetLength();
	//		if (nFileLength == 0)
	//		{
	//			ReadFile.Close();
	//			delete pDlg;
	//			return;
	//		}

	//		//nFileLength = g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nFrameRawSize;

	//		m_pImgBuff = new unsigned char[nFileLength];
	//		ReadFile.Read(m_pImgBuff, nFileLength);
	//		ReadFile.Close();

	//		g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.image->imageData = (char*)m_pImgBuff;
	//		
	//		
	//		//12Bit 이미지 저장
	//		memset(g_clLaonGrabberWrapper[m_nUnit].m_pImgBuff12Bit, 0x00, sizeof(g_clLaonGrabberWrapper[m_nUnit].m_pImgBuff12Bit));
	//		memcpy(g_clLaonGrabberWrapper[m_nUnit].m_pImgBuff12Bit, m_pImgBuff, nFileLength);
	//		
	//		// 12Bit -> 16Bit 변환
	//		g_Shift12to16BitMode((unsigned char*)g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.image->imageData,
	//			(unsigned char*)g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.image16bitRaw->imageData,
	//			g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nWidth,
	//			g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nHeight);
	//		// RCCC Interpolation
	//		g_CCCR_Interpolation((unsigned short*)g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.image16bitRaw->imageData,
	//			g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nWidth,
	//			g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nHeight);
	//		// 16Bit->12Bit 변환
	//		g_Shift16to12BitMode((unsigned char*)g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.image16bitRaw->imageData,
	//			(unsigned char*)g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.image12bitRaw->imageData,
	//			g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nWidth,
	//			g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nHeight);
	//		// Convert Color
	//		ConvertColor(g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.iPixelFormat, 
	//			g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.image12bitRaw,
	//			g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.imageItp,
	//			g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.ColorConvertItp,
	//			g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nWidth,
	//			g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nHeight);
	//		
	//		// 영상 저장
	//		cvCopy(g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.imageItp, g_clLaonGrabberWrapper[m_nUnit].m_pImageInspBuff);
	//		
	//		cvSplit(g_clLaonGrabberWrapper[m_nUnit].m_pImageInspBuff,
	//			g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[0],
	//			g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[1],
	//			g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[2],
	//			NULL);

	//		MbufPut(g_clVision.m_MilCcdProcChild[m_nUnit][0], g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[2]->imageData);
	//		MbufPut(g_clVision.m_MilCcdProcChild[m_nUnit][1], g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[1]->imageData);
	//		MbufPut(g_clVision.m_MilCcdProcChild[m_nUnit][2], g_clLaonGrabberWrapper[m_nUnit].m_pImageBuff[0]->imageData);

	//		MimResize(g_clVision.m_MilCcdProcImage[m_nUnit], g_clVision.m_MilSmallImage[m_nUnit], dZoomX, dZoomY, M_DEFAULT);	
	//	}

	//	delete pDlg;
	//}
}


void CCcdDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_clLaonGrabberWrapper[m_nUnit].ChangeMono();

	//g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].PlusZoom();
	//g_clLaonGrabberWrapper[m_nUnit].ChangePatternMode(1);
	//g_clPriInsp[m_nUnit].func_Insp_OpenStainLGIT(g_clLaonGrabberWrapper[m_nUnit].m_pImgBuff12Bit, false);
	/*unsigned int	nAddress = 0x3129;
	unsigned int	nData = 0x0080;
	int				errorCode;

	nAddress = 0x30E6;
	nData = 0x0000;	
	errorCode = MIUWriteRegister(1, (MIU_REG_TYPE)1, (unsigned short)nAddress, (unsigned short)nData);

	nAddress = 0x30E7;
	nData = 0x0030;
	errorCode = MIUWriteRegister(1, (MIU_REG_TYPE)1, (unsigned short)nAddress, (unsigned short)nData);
	
	if(errorCode)
	{
		return;
	}*/

	//CFile ReadFile;
	//CFileException e;
	//int nFileLength = 0;

	//CFileDialog* pDlg = new CFileDialog(TRUE, NULL, NULL, OFN_EXPLORER | OFN_HIDEREADONLY, _T("지원 영상 파일(*.raw) | *.raw||"));
	//if (pDlg != NULL)
	//{
	//	if (pDlg->DoModal() == IDOK)
	//	{
	//		if (m_pTempBuff1 != NULL)
	//		{
	//			delete m_pTempBuff1;
	//			m_pTempBuff1 = NULL;
	//		}

	//		if (!ReadFile.Open(pDlg->GetPathName(), CFile::modeRead, &e))
	//		{
	//			e.ReportError(MB_OK);
	//			delete pDlg;
	//			return;
	//		}

	//		nFileLength = ReadFile.GetLength();
	//		if (nFileLength == 0)
	//		{
	//			ReadFile.Close();
	//			delete pDlg;
	//			return;
	//		}

	//		//nFileLength = g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nFrameRawSize;

	//		m_pTempBuff1 = new unsigned char[nFileLength];
	//		ReadFile.Read(m_pTempBuff1, nFileLength);
	//		ReadFile.Close();
	//	}

	//	delete pDlg;
	//}
}


void CCcdDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_clLaonGrabberWrapper[m_nUnit].ChangeRaw();

	//g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].MinusZoom();
	//g_clLaonGrabberWrapper[m_nUnit].ChangePatternMode(0);
	//g_pCarAABonderDlg->SelectAAData(999, _T("111111111111"));

	//CFile ReadFile;
	//CFileException e;
	//int nFileLength = 0;

	//CFileDialog* pDlg = new CFileDialog(TRUE, NULL, NULL, OFN_EXPLORER | OFN_HIDEREADONLY, _T("지원 영상 파일(*.raw) | *.raw||"));
	//if (pDlg != NULL)
	//{
	//	if (pDlg->DoModal() == IDOK)
	//	{
	//		if (m_pTempBuff2 != NULL)
	//		{
	//			delete m_pTempBuff2;
	//			m_pTempBuff2 = NULL;
	//		}

	//		if (!ReadFile.Open(pDlg->GetPathName(), CFile::modeRead, &e))
	//		{
	//			e.ReportError(MB_OK);
	//			delete pDlg;
	//			return;
	//		}

	//		nFileLength = ReadFile.GetLength();
	//		if (nFileLength == 0)
	//		{
	//			ReadFile.Close();
	//			delete pDlg;
	//			return;
	//		}

	//		//nFileLength = g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nFrameRawSize;

	//		m_pTempBuff2 = new unsigned char[nFileLength];
	//		ReadFile.Read(m_pTempBuff2, nFileLength);
	//		ReadFile.Close();
	//	}

	//	delete pDlg;
	//}
}


void CCcdDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


}

void CCcdDlg::OnBnClickedButtonCcdPatternSave()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
    {
        AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
        return;
    }

    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
    {
        AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
        return;
    }
	g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].SaveSfrRoi();
    g_clModelData[m_nUnit].PatternSave(g_clSysData.m_szModelName);
}


void CCcdDlg::OnBnClickedButtonCcdPatternFind()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
    {
        AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
        return;
    }

    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
    {
        AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
        return;
    }
    double dCenterPosX, dCenterPosY, dAngle, dRate;
    g_clVision.ClearOverlay(m_nUnit);

    CString FolderName;
    CString strPatDir;
    FolderName.Format("%s", DATA_DIR);
    TCHAR szPath[SIZE_OF_1K];
    for (int i = 0; i<MAX_LAST_INSP_COUNT; i++)
    {
        _stprintf_s(szPath, SIZE_OF_1K, _T("%s\\CHART\\CHART_Mark_%d-Mask.pat"), BASE_DATA_PATH,  i);
        MpatRestore(g_clVision.m_MilSystem[0], szPath, &g_clVision.FieldPatternImage[m_nUnit][i]);
         
        if (FieldPatternMatching(m_nUnit, i, dCenterPosX, dCenterPosY, dAngle, dRate))
        {
            //g_clVision.DrawMOverlayBox(m_nUnit, m_clRectROI[i], M_COLOR_MAGENTA, 1, FALSE);
            g_clVision.DrawMOverlayBox(m_nUnit, m_nUnit,
                dCenterPosX - g_clModelData[m_nUnit].m_nPatternSize[i].x / 2,
                dCenterPosY - g_clModelData[m_nUnit].m_nPatternSize[i].y / 2,
                dCenterPosX + g_clModelData[m_nUnit].m_nPatternSize[i].x / 2,
                dCenterPosY + g_clModelData[m_nUnit].m_nPatternSize[i].y / 2,
				M_COLOR_RED, 1, FALSE);
        }
    }
    g_clVision.DrawOverlayAll(m_nUnit);


	FolderName.Empty();
	strPatDir.Empty();
}


void CCcdDlg::OnBnClickedButtonCcdSfrRoiSave()
{
    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
    {
		g_ShowMsgPopup(_T("ERROR"), _T("자동 운전 중 사용 불가."), RGB_COLOR_RED);
        AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
        return;
    }

    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
    {
        AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
        return;
    }

    /*if (g_ShowMsgModal(_T("확인"), _T("Sfr Roi 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
        return;*/
    getSfrRoi();
    g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);
	AddLog(_T("[수동검사] Sfr Roi 저장 완료"), 0, m_nUnit);
}


void CCcdDlg::OnBnClickedButtonCcdIC()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	bool nRetVal = false;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

#ifdef ON_LINE_GRABBER
	if (g_clLaonGrabberWrapper[m_nUnit].GetDeviceOpen() == false)
	{
		AddLog(_T("[수동검사] FRAME GRABBER 연결 해제 상태"), 1, m_nUnit);
		return;
	}

	/*if (g_clLaonGrabberWrapper[m_nUnit].GetCurrentState() != CCD_GRAB_LIVE)
	{
	AddLog(_T("[수동검사] CCD 동영상 획득 실패"), 1, m_nUnit);
	return;
	}	*/

#endif
	nRetVal = g_clPriInsp[m_nUnit].func_Insp_Version_Read(false);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[수동검사] Version,Model READ 완료(%d)"), nRetVal);
	AddLog(szLog, 0, m_nUnit);
}
void CCcdDlg::Insp_Ic()
{

}

void CCcdDlg::OnBnClickedButtonCcdOpticalCenter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}
#ifdef ON_LINE_GRABBER
	//if (g_clLaonGrabberWrapper[m_nUnit].GetDeviceOpen() == false)
	//{
	//	AddLog(_T("[수동검사] FRAME GRABBER 연결 해제 상태"), 1, m_nUnit);
	//	return;
	//}

	//if (g_clLaonGrabberWrapper[m_nUnit].GetCurrentState() != CCD_GRAB_LIVE)
	//{
	//	AddLog(_T("[수동검사] CCD 동영상 획득 실패"), 1, m_nUnit);
	//	return;
	//}
#endif


}
void CCcdDlg::OnBnClickedButtonCcdRcbc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

    g_clVision.ClearOverlay(m_nUnit);
	//3000, 5000k , Dark 세번 검사 Color Sensitivity
	//MID_3000K_RAW
	//MID_5000k_RAW
	//LOW_LEVEL_RAW
    if (g_clPriInsp[m_nUnit].func_Insp_WhiteBalance(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, MID_3000K_RAW, false) == false)	//LOW_LEVEL_RAW, MID_3000K_RAW, MID_5000k_RAW  
    {
        AddLog(_T("[수동검사] Color Sensitivity 3000 검사 실패"), 0, m_nUnit);
		return;
    }

    AddLog(_T("[수동검사] Color Sensitivity 3000 검사 완료"), 0, m_nUnit);
}


void CCcdDlg::OnBnClickedButtonCcdSnr()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

    g_clVision.ClearOverlay(m_nUnit);
	//FPN,5000K 영상으로 nPatternType 변경 3회 측정 , Dark 영상으로 nPatternType 변경  3회 측정
    if (g_clPriInsp[m_nUnit].func_Insp_SnrRowColNoise(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, MID_5000k_RAW, false) == false)	//MID_5000k_RAW LOW_LEVEL_RAW 
    {
        AddLog(_T("[수동검사] SNR 5000k 검사 실패"), 0, m_nUnit);
		return;
    }

    AddLog(_T("[수동검사] SNR 5000k  검사 완료"), 0, m_nUnit);
}


void CCcdDlg::OnBnClickedButtonCcdDefectRi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

    g_clVision.ClearOverlay(m_nUnit);


	if (g_clPriInsp[m_nUnit].func_Insp_Shm_Illumination(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, false) == false)
	{
		//AddLog(_T("[수동검사] Relative Illumination 검사 실패"), 1, m_nUnit);
	}
	g_clVision.DrawOverlayAll(m_nUnit);
	AddLog(_T("[수동검사] Relative Illumination 검사 완료"), 0, m_nUnit);

}


void CCcdDlg::OnBnClickedButtonCcdDefectSpec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_clDefectSpecDlg.SetUnit(m_nUnit);
	m_clDefectSpecDlg.ShowWindow(SW_SHOW);
}


void CCcdDlg::OnBnClickedButtonCcdRiSpec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_clRiOcSpecDlg.SetUnit(m_nUnit);
	m_clRiOcSpecDlg.ShowWindow(SW_SHOW);
}


void CCcdDlg::OnBnClickedButtonCcdBlemishSpec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_clBlemishSpecDlg.SetUnit(m_nUnit);
	m_clBlemishSpecDlg.ShowWindow(SW_SHOW);
}


void CCcdDlg::OnBnClickedButtonCcdFovDisRo()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    TCHAR szPath[SIZE_OF_1K];
    CFileFind clFinder;
    // GRABBER 상태 체크
    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
    {
        AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
        return;
    }

    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
    {
        AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
        return;
    }
	
#ifdef ON_LINE_GRABBER
    /*if (g_clLaonGrabberWrapper[m_nUnit].GetDeviceOpen() == false)
    {
        AddLog(_T("[수동검사] FRAME GRABBER 연결 해제 상태"), 1, m_nUnit);
        return;
    }

    if (g_clLaonGrabberWrapper[m_nUnit].GetCurrentState() != CCD_GRAB_LIVE)
    {
        AddLog(_T("[수동검사] CCD 동영상 획득 실패"), 1, m_nUnit);
        return;
    }*/
#endif
    g_clVision.ClearOverlay(m_nUnit);
	g_clMandoInspLog[m_nUnit].InitData();

	//if (g_FindCirclePos(m_nUnit, g_clVision.m_pImgBuff[m_nUnit][1], g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle) == false)	//OnBnClickedButtonCcdFovDisRo
	//if (g_OpencvFindCirclePos(m_nUnit, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle, false) == false)

	if (g_MilFindCirclePos(m_nUnit, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle, false) == false)	//fov
	{
		AddLog(_T("[수동검사] 원형 마크 확인 실패"), 1, m_nUnit);
		return;
	}
	g_clVision.ClearOverlay(m_nUnit);

	if (g_clPriInsp[m_nUnit].FnShmFastCornerFind(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer) == false)		//MANUAL
	{
		AddLog(_T("[수동검사] FOV MARK 확인 실패"), 1, m_nUnit);
		return;
	}
	g_clPriInsp[m_nUnit].func_Insp_Shm_Fov_Distortion(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer);		//MANUAL
	g_clMesCommunication[m_nUnit].g_FovVertexLog(m_nUnit);	//MANUAL
    AddLog(_T("[수동검사] Fov 검사 완료"), 0, m_nUnit);
}


void CCcdDlg::OnBnClickedButtonCcdFovMarkRegist()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
    {
        AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
        return;
    }

    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
    {
        AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
        return;
    }

    if (g_ShowMsgModal(_T("확인"), _T("FOV 마크 위치를 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
        return;

	//g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].SetFovRoi();

    g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].RegistFovMark();

    AddLog(_T("[SAVE] FOV 마크 위치 저장"), 0, m_nUnit);
}


void CCcdDlg::OnBnClickedButtonCcdFovMarkView()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
    {
        AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
        return;
    }

    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
    {
        AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
        return;
    }
    //
    g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_FovSetMode = !g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_FovSetMode;
    //
    //
    //
    m_clColorButtonFovMarkView.state = 0;
    g_clVision.ClearOverlay(m_nUnit);


    if (g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_FovSetMode == true)
    {
        m_clColorButtonFovMarkView.state = 1;
        g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].DrawRectFov(999);
	}
	else
	{
		g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].DrawRectSfr(999);
	}

    m_clColorButtonSnrMarkView.Invalidate();
    m_clColorButtonFovMarkView.Invalidate();
}

void CCcdDlg::OnBnClickedButtonCcdFovrdSpec()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    m_clChartSpecDlg.SetUnit(m_nUnit);
    m_clChartSpecDlg.ShowWindow(SW_SHOW);
}


void CCcdDlg::OnBnClickedButtonCcdRelativeiSpec()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    m_clRiSpecDlg.SetUnit(m_nUnit);
    m_clRiSpecDlg.ShowWindow(SW_SHOW);
}


void CCcdDlg::OnBnClickedButtonCcdSnrColorsSpec()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    //m_clSnrColorSensSpecDlg.SetUnit(m_nUnit);
    //m_clSnrColorSensSpecDlg.ShowWindow(SW_SHOW);
}


void CCcdDlg::OnBnClickedButtonCcdDarkRawImageLoad()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    CFileDialog* pDlg = new CFileDialog(TRUE, NULL, NULL, OFN_EXPLORER | OFN_HIDEREADONLY, _T("지원 영상 파일(*.raw) | *.raw||"));
    if (pDlg != NULL)
    {
        if (pDlg->DoModal() == IDOK)
        {
            //FILE* fp;

            //unsigned char* pBuff = (unsigned char*)malloc(g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nFrameImageSize/*g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight * 2*/);
            //memset(pBuff, 0x00, g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nFrameImageSize/*(g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight * 2)*/);

            if (m_pImgBuff != NULL)
            {
                delete m_pImgBuff;
                m_pImgBuff = NULL;
            }

            //unsigned char* pBuff = NULL;
            CFile				ReadFile;
            CFileException		e;
            int					nFileLength;

            if (!ReadFile.Open(pDlg->GetPathName(), CFile::modeRead, &e))
            {
                e.ReportError(MB_OK);
                return;
            }
            nFileLength = ReadFile.GetLength();
            m_pImgBuff = new unsigned char[nFileLength];
            ReadFile.Read(m_pImgBuff, nFileLength);
            ReadFile.Close();

            //
            ///
            //
            CCARawImageLoad((byte*)m_pImgBuff, LOW_LEVEL_RAW);
   
        }

        delete pDlg;
    }
}


void CCcdDlg::OnBnClickedButtonCcd2800RawImageLoad()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CFileDialog* pDlg = new CFileDialog(TRUE, NULL, NULL, OFN_EXPLORER | OFN_HIDEREADONLY, _T("지원 영상 파일(*.raw) | *.raw||"));
    if (pDlg != NULL)
    {
        if (pDlg->DoModal() == IDOK)
        {
            //FILE* fp;

            //unsigned char* pBuff = (unsigned char*)malloc(g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nFrameImageSize/*g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight * 2*/);
            //memset(pBuff, 0x00, g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nFrameImageSize/*(g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight * 2)*/);

            if (m_pImgBuff != NULL)
            {
                delete m_pImgBuff;
                m_pImgBuff = NULL;
            }

            //unsigned char* pBuff = NULL;
            CFile				ReadFile;
            CFileException		e;
            int					nFileLength;

            if (!ReadFile.Open(pDlg->GetPathName(), CFile::modeRead, &e))
            {
                e.ReportError(MB_OK);
                return;
            }
            nFileLength = ReadFile.GetLength();
            m_pImgBuff = new unsigned char[nFileLength];
            ReadFile.Read(m_pImgBuff, nFileLength);
            ReadFile.Close();

            //
            //
            //
            CCARawImageLoad((byte*)m_pImgBuff, MID_5000k_RAW);

        }

        delete pDlg;
    }
}


void CCcdDlg::OnBnClickedButtonCcdSnrRoiView()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
    {
        AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
        return;
    }

    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
    {
        AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
        return;
    }
    //
    g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_FovSetMode = false;
    g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_SnrSetMode = !g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_SnrSetMode;

    //
    //
    //
   
    m_clColorButtonFovMarkView.state = 0;
    m_clColorButtonSnrMarkView.state = 0;
    g_clVision.ClearOverlay(m_nUnit);
    if (g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_SnrSetMode == true)
    {
        m_clColorButtonSnrMarkView.state = 1;
        g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].DrawRectSnr(999);
    }
    else
    {
        g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].DrawRectSfr(999);
    }
    m_clColorButtonFovMarkView.Invalidate();
    m_clColorButtonSnrMarkView.Invalidate();
}


void CCcdDlg::OnBnClickedButtonCcdSnrMarkRegist()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
    {
        AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
        return;
    }

    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
    {
        AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
        return;
    }

    if (g_ShowMsgModal(_T("확인"), _T("SNR 마크 위치를 저장하시겠습니까?"), RGB_COLOR_BLUE) == false)
        return;

    g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].RegistSnrMark();

    AddLog(_T("[SAVE] SNR 마크 위치 저장"), 0, m_nUnit);
}


void CCcdDlg::OnBnClickedButtonCcdRithresholdSpec()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    //m_clRiThresholdSpecDlg.SetUnit(m_nUnit);
    //m_clRiThresholdSpecDlg.ShowWindow(SW_SHOW);
}


void CCcdDlg::OnBnClickedButtonCcd6500RawImageLoad()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CFileDialog* pDlg = new CFileDialog(TRUE, NULL, NULL, OFN_EXPLORER | OFN_HIDEREADONLY, _T("지원 영상 파일(*.raw) | *.raw||"));
    if (pDlg != NULL)
    {
        if (pDlg->DoModal() == IDOK)
        {
            //FILE* fp;

            //unsigned char* pBuff = (unsigned char*)malloc(g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nFrameImageSize/*g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight * 2*/);
            //memset(pBuff, 0x00, g_clLaonGrabberWrapper[m_nUnit].m_stMIUDevice.nFrameImageSize/*(g_clModelData[m_nUnit].m_nWidth * g_clModelData[m_nUnit].m_nHeight * 2)*/);

            if (m_pImgBuff != NULL)
            {
                delete m_pImgBuff;
                m_pImgBuff = NULL;
            }

            //unsigned char* pBuff = NULL;
            CFile				ReadFile;
            CFileException		e;
            int					nFileLength;

            if (!ReadFile.Open(pDlg->GetPathName(), CFile::modeRead, &e))
            {
                e.ReportError(MB_OK);
                return;
            }
            nFileLength = ReadFile.GetLength();
            m_pImgBuff = new unsigned char[nFileLength];
            ReadFile.Read(m_pImgBuff, nFileLength);
            ReadFile.Close();

            //
            ///
            //
			CCARawImageLoad((byte*)m_pImgBuff, MID_5000k_RAW);// OC_WHITE_RAW);

        }

        delete pDlg;
    }
}


void CCcdDlg::OnBnClickedButtonCcdDis()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    TCHAR szPath[SIZE_OF_1K];
    CFileFind clFinder;

    // GRABBER 상태 체크
    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
    {
        AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
        return;
    }

    if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
    {
        AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
        return;
    }

    g_clVision.ClearOverlay(m_nUnit);

    
    //광각은 distortion 만 fov마크로 
    //광각 fov는 원형마크로 측정 
    /*if (g_clPriInsp[m_nUnit].func_Insp_Fov_Distortion_Rotate(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, DOT_TYPE, false , true) == false)
    {
        AddLog(_T("[수동검사] ROTATION  검사 실패"), 1, m_nUnit);
        return;
    }

	AddLog(_T("[수동검사] ROTATION 검사 완료"), 0, m_nUnit);
	g_clVision.DrawOverlayAll(m_nUnit);*/
	/*if (g_GetSfrRectROI(m_nUnit, SFR_FINAL) == false)
	{
		AddLog(_T("[수동검사] 원형마크 인식 실패"), 1, m_nUnit);
		g_clVision.DrawOverlayAll(m_nUnit);
		return;
	}*/

	//int nPitch, nSizeX, nSizeY;
	//int i;

	//nPitch = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_PITCH, M_NULL);
	//nSizeX = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_SIZE_X, M_NULL);
	//nSizeY = (int)MbufInquire(g_clVision.m_MilCcdProcChild[m_nUnit][1], M_SIZE_Y, M_NULL);
	////원형마크 찾기
	//if (g_FindCirclePos(m_nUnit, g_clVision.m_pImgBuff[m_nUnit][1], nPitch, nSizeX, nSizeY, g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle) == false)
	//{
	//	AddLog(_T("[수동검사] 원형마크 인식 실패"), 1, m_nUnit);
	//	g_clVision.DrawOverlayAll(m_nUnit);
	//	return;
	//}
		


   
}


void CCcdDlg::OnBnClickedButtonCcdCalibration1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;
	CString sResult;
	int nLen;
	

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	//g_clVision.ClearOverlay(m_nUnit);
	//
	//g_clLaonGrabberWrapper[m_nUnit].SetCurrentState(CCD_GRAB_PAUSE);

	//IplImage* cvImgBlackSpot = cvCreateImage(cvSize(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight), 8, 3);
	//cvImgBlackSpot->imageData = (char*)g_clLaonGrabberWrapper[m_nUnit].m_pFrameBMPBuffer;

	//g_clLaonGrabberWrapper[m_nUnit].JpgImageSave(cvImgBlackSpot, 3);
	//g_clLaonGrabberWrapper[m_nUnit].SetCurrentState(CCD_GRAB_LIVE);

	_stprintf_s(g_clTaskWork[m_nUnit].m_szImagePath, SIZE_OF_1K, _T("D:\\Calibration.jpg"));

	g_clVision.DrawMOverlayLine(m_nUnit, 0, (int)(g_clModelData[m_nUnit].m_nHeight / 2), g_clModelData[m_nUnit].m_nWidth, (int)(g_clModelData[m_nUnit].m_nHeight / 2), M_COLOR_RED, 1, FALSE, PS_SOLID);
	g_clVision.DrawMOverlayLine(m_nUnit, (int)(g_clModelData[m_nUnit].m_nWidth / 2), 0, (int)(g_clModelData[m_nUnit].m_nWidth / 2), g_clModelData[m_nUnit].m_nHeight, M_COLOR_RED, 1, FALSE, PS_SOLID);
	g_clVision.DrawOverlayAll(m_nUnit);

	if (g_clPriInsp[m_nUnit].func_CalibrateImageEmbedded(g_clTaskWork[m_nUnit].m_szImagePath, sResult) > 0)
	{
		AddLog(_T("[수동검사] CalibrateImageEmbedded 검사 실패"), 1, m_nUnit);
		AddLog(sResult, 0, m_nUnit);
		return;
	}
	ResultSavePath(g_clTaskWork[m_nUnit].m_szImagePath, sResult);

	AddLog(_T("[수동검사] CalibrateImageEmbedded 검사 완료"), 0, m_nUnit);
	AddLog(sResult, 0, m_nUnit);
}


void CCcdDlg::OnBnClickedButtonCcdCalibration2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;
	CString sResult;
	CString sTotalResult;
	int nLen;
	WCHAR wstrImagePath[SIZE_OF_1K];

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	//g_clVision.ClearOverlay(m_nUnit);

	//g_clLaonGrabberWrapper[m_nUnit].SetCurrentState(CCD_GRAB_PAUSE);

	//IplImage* cvImgBlackSpot = cvCreateImage(cvSize(g_clModelData[m_nUnit].m_nWidth, g_clModelData[m_nUnit].m_nHeight), 8, 3);
	//cvImgBlackSpot->imageData = (char*)g_clLaonGrabberWrapper[m_nUnit].m_pFrameBMPBuffer;

	//g_clLaonGrabberWrapper[m_nUnit].JpgImageSave(cvImgBlackSpot, 3);
	//g_clLaonGrabberWrapper[m_nUnit].SetCurrentState(CCD_GRAB_LIVE);

	if (g_clPriInsp[m_nUnit].func_EvaluateUndistortImage(g_clTaskWork[m_nUnit].m_szImagePath, sResult) > 0)
	{
		AddLog(_T("[수동검사] EvaluateUndistortImage 검사 실패"), 1, m_nUnit);
		AddLog(sResult, 0, m_nUnit);
		return;
	}
	sTotalResult += sResult;
	AddLog(sResult, 0, m_nUnit);

	if (g_clPriInsp[m_nUnit].func_EvaluateDefault(g_clTaskWork[m_nUnit].m_szImagePath, sResult) > 0)
	{
		AddLog(_T("[수동검사] EvaluateDefault 검사 실패"), 1, m_nUnit);
		AddLog(sResult, 0, m_nUnit);
		return;
	}
	sTotalResult += sResult;
	ResultSavePath(g_clTaskWork[m_nUnit].m_szImagePath, sResult);

	AddLog(_T("[수동검사] EvaluateUndistort 검사 완료"), 0, m_nUnit);
	AddLog(sResult, 0, m_nUnit);
}


void CCcdDlg::OnBnClickedButtonCcdFuseId()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("자동 운전 중 사용불가합니다."), RGB_COLOR_RED);
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	//F/W VERIFY 위한 바이너리 원본 파일 로드하기

	g_clPriInsp[m_nUnit].func_Insp_Firmware_BinFile_Read(false);

}


void CCcdDlg::OnBnClickedButtonCcdEepromTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}
	eepromDlg.SetUnit(m_nUnit);
	eepromDlg.ShowWindow(SW_SHOW);
}


void CCcdDlg::OnBnClickedButtonCcdSaturation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	int nRetVal;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}


	//g_clVision.ClearOverlay(m_nUnit);
	////if (g_clPriInsp[m_nUnit].func_Insp_Saturation(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer) == false)	//이물 광원 밝기 검사
	////{
	////	AddLog(_T("[수동검사] Saturation 검사 실패"), 1, m_nUnit);
	////	return;
	////}

	//AddLog(_T("[수동검사] Saturation 검사 완료"), 0, m_nUnit);

	//g_clVision.DrawOverlayAll(m_nUnit); 
}


void CCcdDlg::OnBnClickedButtonCcdIrFilterTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	int nRetVal;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}


	g_clVision.ClearOverlay(m_nUnit);
	g_clPriInsp[m_nUnit].func_Insp_LightTest(0 , false);


	AddLog(_T("[수동검사] CHART BRIGHT 검사 완료"), 0, m_nUnit);
	//if (g_clPriInsp[m_nUnit].func_Insp_IRFilterTest(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer) == false)	//이물 광원 밝기 검사
	//{
	//	AddLog(_T("[수동검사] IR FILTER 검사 실패"), 0, m_nUnit);
	//	return;
	//}

	g_clVision.DrawOverlayAll(m_nUnit);
}


void CCcdDlg::OnBnClickedButtonCcdColorReproduction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	int nRetVal;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}
	int nRawSize = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize();

	if (nRawSize < 4000000)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("Yuv 영상에서 측정가능합니다."), RGB_COLOR_RED);
		return;
	}
	//if (g_OpencvFindCirclePos(m_nUnit, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle, false) == false)

	if (g_MilFindCirclePos(m_nUnit, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle, false) == false)	//color
	{
		AddLog(_T("[수동검사] 원형 마크 확인 실패"), 1, m_nUnit);
		return;
	}
	g_clVision.ClearOverlay(m_nUnit);
	//if (g_clPriInsp[m_nUnit].func_Insp_Color_reproduction(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer) == false)	//
	//{
	//	AddLog(_T("[수동검사] COLOR REPRODUCTION 검사 실패"), 1, m_nUnit);
	//	return;
	//}
	g_clPriInsp[m_nUnit].func_Insp_Color_reproduction(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer);
	AddLog(_T("[수동검사] COLOR REPRODUCTION 검사 완료"), 0, m_nUnit);

	g_clVision.DrawOverlayAll(m_nUnit);
	return; 
}


void CCcdDlg::OnBnClickedButtonCcdTemperature()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	int nRetVal;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}
	

	if (g_clPriInsp[m_nUnit].func_Insp_Temperature(false) == false)
	{ 
		AddLog(_T("[수동검사] Temperature 검사 실패"), 1, m_nUnit);
	}

	AddLog(_T("[수동검사] Temperature 검사 완료"), 0, m_nUnit);
	return;
}


void CCcdDlg::OnBnClickedButtonCcdSaturationSpec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_clSaturationSpecDlg.SetUnit(m_nUnit);
	m_clSaturationSpecDlg.ShowWindow(SW_SHOW);
}


void CCcdDlg::OnBnClickedButtonCcdIrfilterSpec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_clIrFilterSpecDlg.SetUnit(m_nUnit);
	m_clIrFilterSpecDlg.ShowWindow(SW_SHOW);
}


void CCcdDlg::OnBnClickedButtonCcdColorReproductionSpec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_clColorReproductionSpecDlg.SetUnit(m_nUnit);
	m_clColorReproductionSpecDlg.ShowWindow(SW_SHOW);
}


void CCcdDlg::OnBnClickedButtonCcdTemperatureSpec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_clTemperatureSpecDlg.SetUnit(m_nUnit);
	m_clTemperatureSpecDlg.ShowWindow(SW_SHOW);
}


void CCcdDlg::OnBnClickedButtonCcdVoltage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	bool nRetVal = false;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

#ifdef ON_LINE_GRABBER
	if (g_clLaonGrabberWrapper[m_nUnit].GetDeviceOpen() == false)
	{
		AddLog(_T("[수동검사] FRAME GRABBER 연결 해제 상태"), 1, m_nUnit);
		return;
	}

	/*if (g_clLaonGrabberWrapper[m_nUnit].GetCurrentState() != CCD_GRAB_LIVE)
	{
	AddLog(_T("[수동검사] CCD 동영상 획득 실패"), 1, m_nUnit);
	return;
	}	*/

#endif
	nRetVal = g_clPriInsp[m_nUnit].func_Insp_Supply_Voltage_Read(false);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[수동검사] VOLTAGE READ 완료(%d)"), nRetVal);
	AddLog(szLog, 0, m_nUnit);
}


void CCcdDlg::OnBnClickedButtonCcdEepromChecksum()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	bool nRetVal = false;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

#ifdef ON_LINE_GRABBER
	if (g_clLaonGrabberWrapper[m_nUnit].GetDeviceOpen() == false)
	{
		AddLog(_T("[수동검사] FRAME GRABBER 연결 해제 상태"), 1, m_nUnit);
		return;
	}

#endif
	nRetVal = g_clPriInsp[m_nUnit].func_EEprom_CheckSum_Check(false);
	if (nRetVal == true)
	{
		//
		_stprintf_s(szLog, SIZE_OF_1K, _T("[수동검사] EEPROM TEST 완료(%d)"), nRetVal);
		AddLog(szLog, 0, m_nUnit);
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[수동검사] EEPROM TEST 실패(%d)"), nRetVal);
		AddLog(szLog, 1, m_nUnit);
	}
}


void CCcdDlg::OnBnClickedButtonCcdI2c()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	bool nRetVal = false;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

#ifdef ON_LINE_GRABBER
	if (g_clLaonGrabberWrapper[m_nUnit].GetDeviceOpen() == false)
	{
		AddLog(_T("[수동검사] FRAME GRABBER 연결 해제 상태"), 1, m_nUnit);
		return;
	}

	AddLog(_T("[수동검사] Firmware Verify Start"), 0, m_nUnit, false , false); 

	g_clPriInsp[m_nUnit].func_Insp_FirmwareVerify(false);

	AddLog(_T("[수동검사] Firmware Verify End"), 0, m_nUnit);
#endif
}


void CCcdDlg::OnBnClickedButtonCcdDistortion()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	
}

void CCcdDlg::OnBnClickedButtonCcdLensShading()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit, true);
		return;
	}
#ifdef ON_LINE_MIL
	g_clVision.ClearOverlay(m_nUnit);
#endif
	int nRawSize = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize();

	if (nRawSize < 4000000)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("Yuv 영상에서 측정가능합니다."), RGB_COLOR_RED);
		return;
	}
	AddLog(_T("	"), 0, m_nUnit);
	AddLog(_T("[수동검사] YUV - OC, ROTATION"), 0, m_nUnit);
	AddLog(_T("	"), 0, m_nUnit);

	//if (g_OpencvFindCirclePos(m_nUnit, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle, false) == false)

	if (g_MilFindCirclePos(m_nUnit, g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, g_clModelData[m_nUnit].m_clSfrInfo.m_clRectCircle, false) == false)	//oc,rotation
	{
		AddLog(_T("[수동검사] 원형 마크 확인 실패"), 1, m_nUnit);
		return;
	}
	///g_CalcImageAlign(m_nUnit);
	g_CheckEolOc(m_nUnit);	//MANUAL EOL OC CHECK
	g_CheckEolRotation(m_nUnit);	//MANUAL EOL ROTATION

	AddLog(_T("[수동검사] YUV - OC, ROTATION"), 0, m_nUnit);


	g_clVision.DrawOverlayAll(m_nUnit);

}

void CCcdDlg::OnBnClickedButtonCcdColorShadingSpec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_clColorShadingSpecDlg.SetUnit(m_nUnit);
	m_clColorShadingSpecDlg.ShowWindow(SW_SHOW);
}


void CCcdDlg::OnBnClickedButtonCcdColorUniformitySpec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_clColorUniformitySpecDlg.SetUnit(m_nUnit);
	m_clColorUniformitySpecDlg.ShowWindow(SW_SHOW);
}


void CCcdDlg::OnBnClickedButtonCcdFpnSpec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	int nRetVal;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}


	g_clVision.ClearOverlay(m_nUnit);
	g_clPriInsp[m_nUnit].func_Insp_LightTest(1 , false);


	AddLog(_T("[수동검사] OC BRIGHT 검사 완료"), 0, m_nUnit);
}


void CCcdDlg::OnBnClickedButtonCcdMesSpecLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("자동 운전 중 사용불가합니다."), RGB_COLOR_RED);
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	//MesDataLoad();

	m_clMesSpecDlg.SetUnit(m_nUnit);
	m_clMesSpecDlg.ShowWindow(SW_SHOW);
}


void CCcdDlg::OnBnClickedButtonCcdDefectRi3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	g_clVision.ClearOverlay(m_nUnit);

	//Relative Illumination 검사 5000k로 1회, Dark로 1회 Color Shading
	if (g_clPriInsp[m_nUnit].func_Insp_ColorShading(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, LOW_LEVEL_RAW, false) == false)//MID_5000k_RAW, LOW_LEVEL_RAW
	{
		//AddLog(_T("[수동검사] Relative Illumination 검사 실패"), 1, m_nUnit);
	}
	g_clVision.DrawOverlayAll(m_nUnit);
	AddLog(_T("[수동검사] Dark Pixel Uniformity(dark) 검사 완료"), 0, m_nUnit);
}


void CCcdDlg::OnBnClickedButtonCcdSnr2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	g_clVision.ClearOverlay(m_nUnit);
	//FPN,5000K 영상으로 nPatternType 변경 3회 측정 , Dark 영상으로 nPatternType 변경  3회 측정
	if (g_clPriInsp[m_nUnit].func_Insp_SnrRowColNoise(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, LOW_LEVEL_RAW, false) == false)	//MID_5000k_RAW LOW_LEVEL_RAW 
	{
		AddLog(_T("[수동검사] SNR dark 검사 실패"), 0, m_nUnit);
		return;
	}

	AddLog(_T("[수동검사] SNR dark  검사 완료"), 0, m_nUnit);
}


void CCcdDlg::OnBnClickedButtonCcdColorSensitivity2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	g_clVision.ClearOverlay(m_nUnit);
	//3000, 5000k , Dark 세번 검사 Color Sensitivity
	//MID_3000K_RAW
	//MID_5000k_RAW
	//LOW_LEVEL_RAW
	if (g_clPriInsp[m_nUnit].func_Insp_WhiteBalance(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, MID_5000k_RAW, false) == false)	//LOW_LEVEL_RAW, MID_3000K_RAW, MID_5000k_RAW  
	{
		AddLog(_T("[수동검사] Color Sensitivity 5000 검사 실패"), 0, m_nUnit);
		return;
	}

	AddLog(_T("[수동검사] Color Sensitivity 5000 검사 완료"), 0, m_nUnit);
}


void CCcdDlg::OnBnClickedButtonCcdColorSensitivity3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	g_clVision.ClearOverlay(m_nUnit);
	//3000, 5000k , Dark 세번 검사 Color Sensitivity
	//MID_3000K_RAW
	//MID_5000k_RAW
	//LOW_LEVEL_RAW
	if (g_clPriInsp[m_nUnit].func_Insp_WhiteBalance(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, LOW_LEVEL_RAW, false) == false)	//LOW_LEVEL_RAW, MID_3000K_RAW, MID_5000k_RAW  
	{
		AddLog(_T("[수동검사] Color Sensitivity dark 검사 실패"), 0, m_nUnit);
		return;
	}

	AddLog(_T("[수동검사] Color Sensitivity dark 검사 완료"), 0, m_nUnit);
}


void CCcdDlg::OnBnClickedButtonCcdLensShading2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szPath[SIZE_OF_1K];
	CFileFind clFinder;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	g_clVision.ClearOverlay(m_nUnit);
	//221개 검사다
	//3000 , 5000 두번 검사 CACMISShadingRelativeIllumination_X 
	if (g_clPriInsp[m_nUnit].func_Insp_LensShading(g_clLaonGrabberWrapper[m_nUnit].m_pFrameRawBuffer, MID_5000k_RAW, false) == false)	//MID_3000K_RAW, MID_5000k_RAW
	{
		AddLog(_T("[수동검사] COLOR UNIFORMITY 5000 검사 실패"), 0, m_nUnit);
	}

	AddLog(_T("[수동검사] COLOR UNIFORMITY 5000 검사 완료"), 0, m_nUnit);
}


void CCcdDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
		//this->setSfrRoi();
	}
	else
	{
		g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_FovSetMode = false;
		m_clColorButtonFovMarkView.state = 0;
		m_clColorButtonFovMarkView.Invalidate();
	}
}


void CCcdDlg::OnBnClickedButtonCcdIniLoad()
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

	if (g_clLaonGrabberWrapper[m_nUnit].m_pBoard->IsGrabStarted())
	{
		AddLog(_T("[INFO] 영상 그랩 중 사용 불가"), 1, m_nUnit);
		return;
	}


	CFileDialog* pDlg = new CFileDialog(TRUE, NULL, NULL, OFN_EXPLORER | OFN_HIDEREADONLY, _T("ini 파일(*.ini) | *.ini||"));

	CString inipath;
	inipath.Format(_T("%s\\UIConfig"), MIU_DIR);
	pDlg->m_ofn.lpstrInitialDir = inipath;


	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			inipath.Format(_T("%s"), pDlg->GetPathName());
			int dRtn = inipath.Find("UIConfig");
			if (dRtn > 0)
			{
				g_clLaonGrabberWrapper[m_nUnit].UiconfigLoad(INI_PATH_IMAGE, pDlg->GetPathName());	//manual
				g_clLaonGrabberWrapper[m_nUnit].SelectSensor();
				g_clLaonGrabberWrapper[m_nUnit].AllocImageBuff();

				int nRawSize = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->GetFrameRawSize();

				if (nRawSize < 4000000)
				{
					g_clLaonGrabberWrapper[m_nUnit].rawReSet(0);			//RAW	[CCD] ini load
				}
				else
				{
					g_clLaonGrabberWrapper[m_nUnit].rawReSet(1);			//YUV	[CCD] ini load
				}
				
			} 
		}

		delete pDlg;
	}

	inipath.Empty();
}


void CCcdDlg::OnBnClickedButtonCcdFovInit()
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
	g_clVision.ClearOverlay(m_nUnit);
	g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].m_FovSetMode = true;

	m_clColorButtonFovMarkView.state = 1;
	g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].DrawRectFov(999);

	m_clColorButtonSnrMarkView.Invalidate();
	m_clColorButtonFovMarkView.Invalidate();

	g_pCarAABonderDlg->m_clVisionStaticCcd[m_nUnit].InitFovRoi();
}


void CCcdDlg::OnBnClickedButtonCcdSensorVoltage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	bool nRetVal = false;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

#ifdef ON_LINE_GRABBER
	//if (g_clLaonGrabberWrapper[m_nUnit].GetDeviceOpen() == false)
	//{
	//	AddLog(_T("[수동검사] FRAME GRABBER 연결 해제 상태"), 1, m_nUnit);
	//	return;
	//}

	/*if (g_clLaonGrabberWrapper[m_nUnit].GetCurrentState() != CCD_GRAB_LIVE)
	{
	AddLog(_T("[수동검사] CCD 동영상 획득 실패"), 1, m_nUnit);
	return;
	}	*/

#endif
	nRetVal = g_clPriInsp[m_nUnit].func_Insp_Sensor_Voltage_Read(false);
	_stprintf_s(szLog, SIZE_OF_1K, _T("[수동검사] SENSOR VOLTAGE READ 완료(%d)"), nRetVal);
	AddLog(szLog, 0, m_nUnit);
}


void CCcdDlg::OnBnClickedButtonCcdJxlDecode()
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
	CFileDialog* pDlg = new CFileDialog(TRUE, NULL, NULL, OFN_EXPLORER | OFN_HIDEREADONLY, _T("지원 영상 파일(*.jxl) | *.jxl||"));
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			TCHAR szLog[SIZE_OF_1K];

			_stprintf_s(szLog, SIZE_OF_1K, _T("[JXL DECODE] %s"), pDlg->GetPathName());
			AddLog(szLog, 0, m_nUnit);

			g_clLaonGrabberWrapper[m_nUnit].ImageDecode(pDlg->GetPathName(), pDlg->GetFolderPath());
			
		}

		delete pDlg;
	}
}


void CCcdDlg::OnBnClickedButtonCcdFlashing()
{
	// TODO: Add your control notification handler code here
	TCHAR szLog[SIZE_OF_1K];
	bool nRetVal = false;

	// GRABBER 상태 체크
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

#ifdef ON_LINE_GRABBER
	if (g_clLaonGrabberWrapper[m_nUnit].GetDeviceOpen() == false)
	{
		AddLog(_T("[수동검사] FRAME GRABBER 연결 해제 상태"), 1, m_nUnit);
		return;
	}

	AddLog(_T("[수동검사] Flashing Verify Start"), 0, m_nUnit, false, false);

	g_clPriInsp[m_nUnit].func_Insp_Flashing(false);

	AddLog(_T("[수동검사] Flashing Verify End"), 0, m_nUnit);
#endif
}
