#pragma once
#include "afxwin.h"
#include "Utility\Label\Label.h"
#include "Utility\ButtonEx\ButtonCT.h"
#include "Utility\GridCtrl\GridCtrl.h"
#include "Utility\GraphCtrl\Graph2DWnd.h"
#include "CcdSfrSpecDlg.h"

#include "CcdDefectSpecDlg.h"
#include "CcdRiOcSpecDlg.h"
#include "CcdBlemishSpecDlg.h"
#include "CcdChartSpecDlg.h"
#include "CcdRISpecDlg.h"
#include "CcdRIThresholdSpecDlg.h"
#include "CcdSnrColorSensSpecDlg.h"
#include "CcdColorShadingSpecDlg.h"
#include "CcdColorUniformitySpecDlg.h"
#include "CcdSaturationSpecDlg.h"
#include "CcdColorReproductionSpecDlg.h"
#include "CcdIrFilterSpecDlg.h"
#include "CcdTemperatureSpecDlg.h"
#include "CcdMesSpecDlg.h"
#include "CcdFpnSpecDlg.h"

#include "EEPROMTest.h"

// CCcdDlg 대화 상자입니다.

class CCcdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCcdDlg)

public:
	CCcdDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCcdDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CCD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);
		
private:
	void InitCtrl();

	void DrawGraph();
	void DisplaySfrData();
	void Insp_Ic();
private:	
	CFont m_clFontBig;
	CFont m_clFontMid;
	CFont m_clFontSmall;

	int m_nUnit;
	int m_nGraphMode;
	int m_nMoveType;
	int m_nMoveSize;
	
	double m_dDataX[MAX_GRAPH_OVERLAP_COUNT][MAX_GRAPH_PIXEL_SIZE];
	double m_dDataY[MAX_GRAPH_OVERLAP_COUNT][MAX_GRAPH_PIXEL_SIZE];
	int m_nDataSize[MAX_GRAPH_OVERLAP_COUNT];
	//bool m_bFlagVisible[MAX_GRAPH_OVERLAP_COUNT];	//! true이면 그래프를 눈에 보이게 한다.

	//! 그래프 상의 특정 지점에 X축에 수직선을 표시한다.
	//double m_dDataMTF4[MAX_GRAPH_OVERLAP_COUNT];	//! MTF(N/4) X축 값
	//double m_dDataMTF8[MAX_GRAPH_OVERLAP_COUNT];	//! MTF(N/8) X축 값
	//double m_dDataMTF50[MAX_GRAPH_OVERLAP_COUNT];	//! MTF50	 X축 값

	CGraph2DWnd* m_pGraphWnd;	
	CGridCtrl m_clGridSfr;
	CCcdSfrSpecDlg m_clSfrSpecDlg;
	CCcdDefectSpecDlg m_clDefectSpecDlg;
	CCcdRiOcSpecDlg m_clRiOcSpecDlg;
    CCcdBlemishSpecDlg m_clBlemishSpecDlg;
	CCcdMesSpecDlg m_clMesSpecDlg;
    CCcdChartSpecDlg m_clChartSpecDlg;
    CCcdRISpecDlg m_clRiSpecDlg;
	CCcdColorShadingSpecDlg m_clColorShadingSpecDlg;
	CCcdColorUniformitySpecDlg m_clColorUniformitySpecDlg;
    //CCcdRIThresholdSpecDlg m_clRiThresholdSpecDlg;
    CCcdSnrColorSensSpecDlg m_clSnrColorSensSpecDlg;
	CCcdSaturationSpecDlg m_clSaturationSpecDlg;
	//CCcdFpnSpecDlg m_clFpnSpecDlg;

	CCcdColorReproductionSpecDlg m_clColorReproductionSpecDlg;
	CCcdTemperatureSpecDlg m_clTemperatureSpecDlg;
	CCcdIrFilterSpecDlg m_clIrFilterSpecDlg;

	CEEPROMTest eepromDlg;

	unsigned char* m_pImgBuff;
	
	unsigned char* m_pTempBuff1;
	unsigned char* m_pTempBuff2;
public:
    CGridCtrl m_clGridSfrEachRoi;
    void InitGridCtrlSfrRoi();
    void getSfrRoi();
    void setSfrRoi();
    void CCARawImageLoad(BYTE* img, int index);
	void SetUnitUI(int nUnit);
    

public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);	
	afx_msg void OnBnClickedButtonCcdImageLoad();
	afx_msg void OnBnClickedButtonCcdImageSave();
	afx_msg void OnBnClickedButtonCcdRawImageLoad();
	afx_msg void OnBnClickedButtonCcdRawImageSave();
	afx_msg void OnBnClickedButtonCcdPos();
	afx_msg void OnBnClickedButtonCcdSize();
	afx_msg void OnBnClickedButtonCcdGap();
	afx_msg void OnBnClickedButtonCcdUp();
	afx_msg void OnBnClickedButtonCcdDown();
	afx_msg void OnBnClickedButtonCcdLeft();
	afx_msg void OnBnClickedButtonCcdRight();
	afx_msg void OnBnClickedButtonCcdInit();
	afx_msg void OnBnClickedButtonCcdCircleMarkRegist();
	afx_msg void OnBnClickedButtonCcdInspAreaSave();
	afx_msg void OnBnClickedButtonCcdSfrSpec();
	afx_msg void OnBnClickedButtonCcdSfrInsp();
	afx_msg void OnBnClickedButtonCcdActiveAlign();
	afx_msg void OnBnClickedButtonCcdPixelDefect();
	afx_msg void OnBnClickedButtonCcdStain();
	afx_msg void OnBnClickedButtonCcdUniformity();
	afx_msg void OnBnClickedButtonCcdCurrent();
	afx_msg void OnBnClickedButtonCcdI2cPattern();
	afx_msg void OnBnClickedButtonCcdMtf();
	afx_msg void OnBnClickedButtonCcdDeviceOpen();
	afx_msg void OnBnClickedButtonCcdDeviceClose();
	afx_msg void OnBnClickedButtonCcdConnect();
	afx_msg void OnBnClickedButtonCcdBoardInit();
	afx_msg void OnBnClickedButtonCcdSensorInit();
	afx_msg void OnBnClickedButtonCcdGrabStart();
	afx_msg void OnBnClickedButtonCcdGrabStop();
	afx_msg void OnBnClickedButtonCcdDisconnect();

public:
    CLabel m_clColorStaticTitle;
    //
	CButtonCT m_clColorButtonPos;
	CButtonCT m_clColorButtonSize;
	CButtonCT m_clColorButtonGap;
	CButtonCT m_clColorButtonUp;
	CButtonCT m_clColorButtonDown;
	CButtonCT m_clColorButtonLeft;
	CButtonCT m_clColorButtonRight;
	CButtonCT m_clColorButtonInit;
	CButtonCT m_clColorButtonFovInit;
    CButtonCT m_clColorButtonFovMarkView;
    CButtonCT m_clColorButtonSnrMarkView;
    CButtonCT m_clColorButtonFovMarkRegist;
    CButtonCT m_clColorButtonSnrMarkRegist;

    
	CButtonCT m_clColorButtonCircleMarkRegist;
    CButtonCT m_clColorButtonInspAreaSave;
    CButtonCT m_clColorButtonPatternSave;
    CButtonCT m_clColorButtonPatternFind;
	CButtonCT m_clColorButtonImgLoad;
	CButtonCT m_clColorButtonMesSpecLoad;
	CButtonCT m_clColorButtonIniFileLoad;
	CButtonCT m_clColorButtonImgSave;
	CButtonCT m_clColorButtonRawImgLoad;
	CButtonCT m_clColorButtonRawImgSave;
	CButtonCT m_clColorButtonJxlDecode;
	CButtonCT m_clColorButtonSfrInsp;
	CButtonCT m_clColorButtonRowColNoiseInsp;
	CButtonCT m_clColorButtonLensShadingInsp;
	CButtonCT m_clColorButtonLensShadingInsp2;
	CButtonCT m_clColorButtonActiveAlign;
	CButtonCT m_clColorButtonFuseID;
	CButtonCT m_clColorButtonEepromTest;

    CButtonCT m_clColorButtonSnrColorSSpec;
    CButtonCT m_clColorButtonRiSpec;
	CButtonCT m_clColorButtonColorShadingSpec;
	CButtonCT m_clColorButtonColorUniformitySpec;
    CButtonCT m_clColorButtonRiThresholdSpec;
	CButtonCT m_clColorButtonChartSpec;

	CButtonCT m_clColorButtonSaturationSpec;
	CButtonCT m_clColorButtonIrFilterSpec;
	CButtonCT m_clColorButtonFpnSpec;
	CButtonCT m_clColorButtonReproductionSpec;
	CButtonCT m_clColorButtonTemperatureSpec;


	CButtonCT m_clColorButtonBlemishSpec;
	CButtonCT m_clColorButtonRiOcSpec;
	CButtonCT m_clColorButtonDefectSpec;
	CButtonCT m_clColorButtonSfrSpec;
    CButtonCT m_clColorButtonSfrRoiSave;
	CButtonCT m_clColorButtonPixelDefect;
	CButtonCT m_clColorButtonStain;
	CButtonCT m_clColorButtonUniformity;
	CButtonCT m_clColorButtonCurrent;
	CButtonCT m_clColorButtonDynamicRange;
	CButtonCT m_clColorButtonI2cTestPattern;

	CButtonCT m_clColorButtonI2C;
	CButtonCT m_clColorButtonFlashing;
	CButtonCT m_clColorButtonDistortion;


	CButtonCT m_clColorButtonSaturation;
	CButtonCT m_clColorButtonIrFilterTest;
	CButtonCT m_clColorButtonColorReproduction;
	CButtonCT m_clColorButtonColorTemperature;
	
	CButtonCT m_clColorButtonMTF;
	CButtonCT m_clColorButtonRi;
	CButtonCT m_clColorButtonRi2;
	CButtonCT m_clColorButtonVoltage;
	CButtonCT m_clColorButtonSensorVoltage;
	CButtonCT m_clColorButtonSnr;
	CButtonCT m_clColorButtonSnr2;
	
	CButtonCT m_clColorButtonRcbc;
	CButtonCT m_clColorButtonRcbc2;
	CButtonCT m_clColorButtonRcbc3;
	CButtonCT m_clColorButtonOc;
    CButtonCT m_clColorButtonFov_Dis_Ro;
    CButtonCT m_clColorButtonDis;
	CButtonCT m_clColorButtonEEpromCheckSum;

	CButtonCT m_clColorButtonDeviceOpen;
	CButtonCT m_clColorButtonDeviceClose;
	CButtonCT m_clColorButtonConnect;
	CButtonCT m_clColorButtonBoardInit;
	CButtonCT m_clColorButtonSensorInit;
	CButtonCT m_clColorButtonGrabStart;
	CButtonCT m_clColorButtonGrabStop;
	CButtonCT m_clColorButtonDisconnect;

	CButtonCT m_clColorCalribration1;
	CButtonCT m_clColorCalribration2;
    //
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
    afx_msg void OnBnClickedButtonCcdPatternSave();
    afx_msg void OnBnClickedButtonCcdPatternFind();
    afx_msg void OnBnClickedButtonCcdSfrRoiSave();
    //
    afx_msg void OnNMDblClickedSfrSRoi(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonCcdOpticalCenter();
	afx_msg void OnBnClickedButtonCcdIC();
	afx_msg void OnBnClickedButtonCcdRcbc();
	afx_msg void OnBnClickedButtonCcdSnr();
	afx_msg void OnBnClickedButtonCcdDefectRi();
	afx_msg void OnBnClickedButtonCcdDefectSpec();
	afx_msg void OnBnClickedButtonCcdRiSpec();
	afx_msg void OnBnClickedButtonCcdBlemishSpec();
    afx_msg void OnBnClickedButtonCcdFovDisRo();
    afx_msg void OnBnClickedButtonCcdFovMarkRegist();
    afx_msg void OnBnClickedButtonCcdFovMarkView();
    afx_msg void OnBnClickedButtonCcdFovrdSpec();
    afx_msg void OnBnClickedButtonCcdRelativeiSpec();
    afx_msg void OnBnClickedButtonCcdSnrColorsSpec();
    afx_msg void OnBnClickedButtonCcdDarkRawImageLoad();
    afx_msg void OnBnClickedButtonCcd2800RawImageLoad();
    afx_msg void OnBnClickedButtonCcdSnrRoiView();
    afx_msg void OnBnClickedButtonCcdSnrMarkRegist();
    afx_msg void OnBnClickedButtonCcdRithresholdSpec();
    afx_msg void OnBnClickedButtonCcd6500RawImageLoad();
    afx_msg void OnBnClickedButtonCcdDis();
	afx_msg void OnBnClickedButtonCcdCalibration1();
	afx_msg void OnBnClickedButtonCcdCalibration2();
	afx_msg void OnBnClickedButtonCcdFuseId();
	afx_msg void OnBnClickedButtonCcdEepromTest();
	afx_msg void OnBnClickedButtonCcdSaturation();
	afx_msg void OnBnClickedButtonCcdIrFilterTest();
	afx_msg void OnBnClickedButtonCcdColorReproduction();
	afx_msg void OnBnClickedButtonCcdTemperature();
	afx_msg void OnBnClickedButtonCcdSaturationSpec();
	afx_msg void OnBnClickedButtonCcdIrfilterSpec();
	afx_msg void OnBnClickedButtonCcdColorReproductionSpec();
	afx_msg void OnBnClickedButtonCcdTemperatureSpec();
	afx_msg void OnBnClickedButtonCcdVoltage();
	afx_msg void OnBnClickedButtonCcdEepromChecksum();
	afx_msg void OnBnClickedButtonCcdI2c();
	afx_msg void OnBnClickedButtonCcdDistortion();
	afx_msg void OnBnClickedButtonCcdLensShading();
	afx_msg void OnBnClickedButtonCcdColorShadingSpec();
	afx_msg void OnBnClickedButtonCcdColorUniformitySpec();
	afx_msg void OnBnClickedButtonCcdFpnSpec();
	afx_msg void OnBnClickedButtonCcdMesSpecLoad();
	afx_msg void OnBnClickedButtonCcdDefectRi3();
	afx_msg void OnBnClickedButtonCcdSnr2();
	afx_msg void OnBnClickedButtonCcdColorSensitivity2();
	afx_msg void OnBnClickedButtonCcdColorSensitivity3();
	afx_msg void OnBnClickedButtonCcdLensShading2();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonCcdIniLoad();
	afx_msg void OnBnClickedButtonCcdFovInit();
	afx_msg void OnBnClickedButtonCcdSensorVoltage();
	afx_msg void OnBnClickedButtonCcdJxlDecode();
	afx_msg void OnBnClickedButtonCcdFlashing();
};
