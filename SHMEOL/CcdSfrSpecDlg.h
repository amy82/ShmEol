#pragma once

#include "afxwin.h"
#include "Utility\GridCtrl\GridCtrl.h"
#include "Utility\ButtonEx\ButtonCT.h"
#include "Utility\Label\Label.h"
// CCcdSfrSpecDlg 대화 상자입니다.

class CCcdSfrSpecDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCcdSfrSpecDlg)

public:
	CCcdSfrSpecDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCcdSfrSpecDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CCD_SFR_SPEC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);

private:
	void InitCtrl();
	void InitGridCtrl();

	void ShowSfrSpec();
	void GetSfrSpec();

private:
	CGridCtrl m_clGridSfrSpec;
	CGridCtrl m_clGridSfrSumAveSpec;

	CFont m_clFontSmall;
	CFont m_clFontMid;
	CFont m_clFontBig;

	int m_nUnit;

public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNMDblClickedSfrSpec(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblClickedSfrSumAveSpec(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecOcXyVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecOcThVal();
	afx_msg void OnBnClickedButtonCcdSfrSpecSave();
	afx_msg void OnBnClickedButtonCcdSfrSpecClose();
	
public:
	CLabel m_clColorStaticTopBar;
    CLabel m_clColorStaticCenterSfrLimit;
    CLabel m_clColorStaticCenterSfrLimitVal;
    CLabel m_clColorStaticCornerSfrLimit;
    CLabel m_clColorStaticCornerSfrLimitVal;
    CLabel m_clColorStaticCornerSfrDeviationLimit;
    CLabel m_clColorStaticCornerSfrDeviationLimitVal;
    CLabel m_clColorStaticOCXY;
    CLabel m_clColorStaticOCXYVal;
    CLabel m_clColorStaticOCTh;
    CLabel m_clColorStaticOCThVal;
	CLabel m_clColorStaticDataPlus;
	CLabel m_clColorStaticDataPlusVal;


	CLabel m_clColorStaticCurrentMin;
	CLabel m_clColorStaticCurrentMinVal;
	CLabel m_clColorStaticCurrentMax;
	CLabel m_clColorStaticCurrentMaxVal;

	CLabel m_clColorStatic7VariationMin;
	CLabel m_clColorStatic7VariationMinVal;
	CLabel m_clColorStatic7VariationMax;
	CLabel m_clColorStatic7VariationMaxVal;
	
    CButtonCT m_clColorButtonSave;
    CButtonCT m_clColorButtonClose;

	CLabel m_clColorStaticCcdSfrDataformat;
	CLabel m_clColorStaticCcdSfrOutmode;
	CLabel m_clColorStaticCcdSfrSensortype;
	CLabel m_clColorStaticCcdSfrDemosaic;
	CLabel m_clColorStaticCcdSfrBlacklevel;
	CBrush m_brCheck;

	CComboBox m_CcdSfrComboDataFormat;
	CComboBox m_CcdSfrComboOutMode;
	CComboBox m_CcdSfrComboSensorType;
	CComboBox m_CcdSfrComboDemosaic;

	CLabel m_clColorStaticSfrBlackLevel;
	CLabel m_clColorStaticSfrBlackLevelVal;


	afx_msg void OnStnDblclickStaticCcdSfrSpecDataPlusVal();
	afx_msg void OnStnClickedStaticCcdCurrentSpecMinVal();
	afx_msg void OnStnClickedStaticCcdCurrentSpecMaxVal();
	afx_msg void OnStnClickedStaticCcdSfrSpec7varMinVal();
	afx_msg void OnStnClickedStaticCcdSfrSpec7varMaxVal();
	afx_msg void OnStnClickedStaticCcdSfrBlacklevelVal();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
