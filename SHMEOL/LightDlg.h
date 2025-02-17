#pragma once
#include "afxwin.h"
#include "Utility\SliderCtrlEx\SliderCtrlEx.h"
#include "Utility\ButtonEx\ButtonCT.h"
#include "Utility\Label\Label.h"
// CLightDlg 대화 상자입니다.

class CLightDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLightDlg)

public:
	CLightDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLightDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_LIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);
	void TopChart_Change(int index, int nValue);
	void LeftChart_Change(int index, int nValue);
	void RightChart_Change(int index, int nValue);


	void SideChart_Change(int index, int nValue);
	void OcWhite_Change(int index, int nValue);
	void OcIr_Change(int index, int nValue);
	void Align_Change(int index, int nValue);

	void setOcTime(int mtime);
private:
	void InitCtrl();
	
	void ShowLightData();
	void ShowOCLightData();
	void GetLightData(int ChartIndex);//0 = topchart , 1 = ocWhite , 2 = ir , 3 = Align
	void OC_LX_Change(int LxData);
	void OC_CHANNEL_Change(int OC_CH);
private:
	CFont m_clFontBig;
	CFont m_clFontMid;
	CFont m_clFontSmall;

	int m_nUnit;
	int ocLux;
	int ocVal;
	int oc_CHANNEL;		//0 = 5000K , 1 = 6500K

	int m_CurrentTopChartIndex;
	int m_CurrentLeftChartIndex;
	int m_CurrentRightChartIndex;

	int m_CurrentOcWhiteIndex;
	int m_CurrentBackduIndex;
	//int m_CurrentSideChartIndex;
	int m_CurrentOcIcIndex;
	int m_CurrentAlignIndex;
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnStnClickedStaticLightChartVal();
	afx_msg void OnStnClickedStaticLightOcVal();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnCbnSelchangeComboLightDome();

public:
	CLabel m_clColorStaticTitle;
	CLabel m_clColorStaticChart[2];
	//CLabel m_clColorStaticChartVal[3];
	CLabel m_clColorStaticTopChartVal;
	CLabel m_clColorStaticLeftChartVal;
	CLabel m_clColorStaticRightChartVal;


	CLabel m_clColorStaticSideChartVal;
	CLabel m_clColorStaticAlignVal;
	CLabel m_clColorStaticOCWhiteVal;
	CLabel m_clColorStaticOCWhiteTimeVal;
	CLabel m_clColorStaticOCIrVal;
	
	CLabel m_clColorStaticOC[2];
	CLabel m_clColorStaticOCVal[2];
	//CSliderCtrlEx m_clSliderCtrlChart[3];
	CSliderCtrlEx m_clSliderCtrlTopChart;
	CSliderCtrlEx m_clSliderCtrlSideChart;
	CSliderCtrlEx m_clSliderCtrlLeftChart;
	CSliderCtrlEx m_clSliderCtrlRightChart;

	CSliderCtrlEx m_clSliderCtrlAlign;
	CSliderCtrlEx m_clSliderCtrlOcWhite;
	CSliderCtrlEx m_clSliderCtrlOcIr;
	CSliderCtrlEx m_clSliderCtrlOC[2];
	CComboBox m_clComboDomeChannel;

	CButtonCT m_clColorButtonTopChartSave;
	CButtonCT m_clColorButtonOcWhiteSave;
	CButtonCT m_clColorButtonLeftChartSave;
	CButtonCT m_clColorButtonRightChartSave;

	CButtonCT m_clColorButtonIrWhiteSave;
	CButtonCT m_clColorButtonAlignSave;

	CButtonCT m_clColorButtonLx1;
	CButtonCT m_clColorButtonTopChart[1];

	CButtonCT m_clColorButtonOcWhite[4];
	CButtonCT m_clColorButtonOcWhiteTime;
	CButtonCT m_clColorButtonLeftChart;
	CButtonCT m_clColorButtonRightChart;

	
	CButtonCT m_clColorButtonOcWhitePowerOn;
	CButtonCT m_clColorButtonOcWhitePowerOff;
	
	CButtonCT m_clColorButtonOcIr[2];
	CButtonCT m_clColorButtonAlign[3];
	
	CButtonCT m_clColorButtonLx2;
	CButtonCT m_clColorButtonLx3;
	CButtonCT m_clColorButtonLx4;

	CButtonCT m_clColorButtonChChange;

	CButtonCT m_clColorButtonUp;
	CButtonCT m_clColorButtonDown;
	
	afx_msg void OnStnClickedStaticLightChartVal2();
    afx_msg void OnStnClickedStaticLightRightChartValue();
	afx_msg void OnBnClickedButtonLightLx1();
	afx_msg void OnBnClickedButtonLightLx2();
	afx_msg void OnBnClickedButtonLightLx3();
	afx_msg void OnBnClickedButtonLightLx4();
	afx_msg void OnBnClickedButtonLightValueUp();
	afx_msg void OnBnClickedButtonLightValueDown();
	afx_msg void OnBnClickedButtonLightChChange();
	afx_msg void OnBnClickedButtonLightTopChart1();
	afx_msg void OnBnClickedButtonLightTopChart2();
	afx_msg void OnBnClickedButtonLightTopChart3();
	afx_msg void OnBnClickedButtonLightTopChart4();
	afx_msg void OnStnClickedStaticLightAlignValue();
	afx_msg void OnBnClickedButtonLightTopChart5();
	afx_msg void OnBnClickedButtonLightTopChart6();
	afx_msg void OnBnClickedButtonLightTopChart7();
	afx_msg void OnBnClickedButtonLightTopChart8();
	afx_msg void OnStnClickedStaticLightOcIrVal();
	afx_msg void OnBnClickedButtonLightOcWhiteCh1();
	afx_msg void OnBnClickedButtonLightOcWhiteCh2();
	afx_msg void OnBnClickedButtonLightOcIrCh1();
	afx_msg void OnBnClickedButtonLightOcIrCh2();
	afx_msg void OnBnClickedButtonLightAlignSensorCh();
	afx_msg void OnBnClickedButtonLightAlignHolderCh();
	afx_msg void OnBnClickedButtonLightAlignLensCh();
	afx_msg void OnBnClickedButtonTopChartLightSave();
	afx_msg void OnBnClickedButtonOcWhiteLightSave();
	afx_msg void OnBnClickedButtonIrWhiteLightSave();
	afx_msg void OnBnClickedButtonAlignLightSave();
	afx_msg void OnBnClickedButtonLightSideChartLeft();
	afx_msg void OnBnClickedButtonLightSideChartRight();
	afx_msg void OnStnClickedStaticLightSideChartValue();
	afx_msg void OnBnClickedButtonSideChartLightSave();
	afx_msg void OnBnClickedButtonLightTopChart9();
	afx_msg void OnBnClickedButtonLightTopChart10();
	afx_msg void OnBnClickedButtonLightTopChart11();
	afx_msg void OnBnClickedButtonLightTopChart12();
	afx_msg void OnBnClickedButtonLightTopChart13();
	afx_msg void OnBnClickedButtonLightOcWhiteGetTime();
	afx_msg void OnBnClickedButtonLightOcWhiteCh3();
	afx_msg void OnBnClickedButtonLightOcWhiteCh4();
	afx_msg void OnBnClickedButtonLightOcWhitePowerOff();
	afx_msg void OnBnClickedButtonLightOcWhitePowerOn();
	afx_msg void OnBnClickedButtonRightChartLightSave();
};
