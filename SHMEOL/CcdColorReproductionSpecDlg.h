#pragma once

#include "afxwin.h"
#include "Utility\GridCtrl\GridCtrl.h"
#include "Utility\ButtonEx\ButtonCT.h"
#include "Utility\Label\Label.h"
// CCcdChartSpecDlg 대화 상자입니다.

class CCcdColorReproductionSpecDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCcdColorReproductionSpecDlg)

public:
	CCcdColorReproductionSpecDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCcdColorReproductionSpecDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CCD_COLOR_REPRODUCTION_SPEC};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);
	const int ColorReproductionMaxCount = 33;
private:
	void InitCtrl();
	void InitChartGridCtrl();

	void ShowColorReproductionSpec();
	void GetColorReproductionSpec();
private:
	CGridCtrl m_clGridColorReproductionSpec;

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
	
	afx_msg void OnNMDblClickedColorReproductSpec(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedButtonCcdColorReproductionSpecSave();
    afx_msg void OnBnClickedButtonCcdColorReproductionSpecClose();
    
	
	
public:
	CLabel m_clColorStaticTopBar;


	CLabel m_clColorStaticHRotation;
	CLabel m_clColorStaticHRotationVal;
	
  
    CButtonCT m_clColorButtonSave;
    CButtonCT m_clColorButtonClose;

	CLabel m_clColorStaticColorBlackLevel;
	CLabel m_clColorStaticColorBlackLevelVal;

	CLabel m_clColorStaticCcdColorDataformat;
	CLabel m_clColorStaticCcdColorOutmode;
	CLabel m_clColorStaticCcdColorSensortype;
	CLabel m_clColorStaticCcdColorDemosaic;
	CLabel m_clColorStaticCcdColorBlacklevel;
	CBrush m_brCheck;

	CComboBox m_CcdColorComboDataFormat;
	CComboBox m_CcdColorComboOutMode;
	CComboBox m_CcdColorComboSensorType;
	CComboBox m_CcdColorComboDemosaic;


	afx_msg void OnStnClickedStaticCcdRotationVal();
	afx_msg void OnStnClickedStaticCcdColorBlacklevelVal();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
