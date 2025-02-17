#pragma once

#include "afxwin.h"
#include "Utility\GridCtrl\GridCtrl.h"
#include "Utility\ButtonEx\ButtonCT.h"
#include "Utility\Label\Label.h"
// CCcdRiOcSpecDlg 대화 상자입니다.

class CCcdRiOcSpecDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCcdRiOcSpecDlg)

public:
	CCcdRiOcSpecDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCcdRiOcSpecDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CCD_RI_OC_SPEC};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);
	const int RIMaxCount = 5;
	const int OCMaxCount = 3;
private:
	void InitCtrl();
	void InitOCGridCtrl();
	void InitICGridCtrl();
	void ShowOcSpec();
	void ShowIcSpec();
	void GetOcSpec();
	void GetIcSpec();
private:
	CGridCtrl m_clGridOCSpec;
	CGridCtrl m_clGridICSpec;

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
	afx_msg void OnBnClickedButtonCcdSfrSpecSave();
	afx_msg void OnBnClickedButtonCcdSfrSpecClose();
	afx_msg void OnStnClickedStaticOcMinVal();
	afx_msg void OnStnClickedStaticOcMaxVal();



	
	
	
public:
	CLabel m_clColorStaticTopBar;
	CLabel m_clColorStaticOcLimitMin;
	CLabel m_clColorStaticOcLimitMax;

	CLabel m_clColorStaticRotateLimitMin;
	CLabel m_clColorStaticRotateLimitMax;

	CLabel m_clColorStaticTiltxLimitMin;
	CLabel m_clColorStaticTiltxLimitMax;
	CLabel m_clColorStaticTiltyLimitMin;
	CLabel m_clColorStaticTiltyLimitMax;

	CLabel m_clColorStaticOcLimitMinVal;
	CLabel m_clColorStaticOcLimitMaxVal;

	CLabel m_clColorStaticRotateLimitMinVal;
	CLabel m_clColorStaticRotateLimitMaxVal;

	CLabel m_clColorStaticTiltxLimitMinVal;
	CLabel m_clColorStaticTiltxLimitMaxVal;
	CLabel m_clColorStaticTiltyLimitMinVal;
	CLabel m_clColorStaticTiltyLimitMaxVal;



	CButtonCT m_clColorButtonSave;
	CButtonCT m_clColorButtonClose;






/*
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
	CLabel m_clColorStaticOcOffsetX;
	CLabel m_clColorStaticOcOffsetXVal;

	CLabel m_clColorStatic_IcOffsetX;
	CLabel m_clColorStatic_IcOffsetY;
	
	CLabel m_clColorStatic_IcOffsetXVal;
	CLabel m_clColorStatic_IcOffsetYVal;
	

	CLabel m_clColorStaticOcOffsetY;
	CLabel m_clColorStaticOcOffsetYVal;*/

	

	
	/*afx_msg void OnNMDblClickedUniformitySpec(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblClickedIcSpec(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecOcXyVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecOcThVal();
	afx_msg void OnStnClickedStaticOcOffsetXVal();
	afx_msg void OnStnClickedStaticOcOffsetYVal();
	afx_msg void OnStnClickedStaticIcOffsetXVal();
	afx_msg void OnStnClickedStaticIcOffsetYVal();*/
	afx_msg void OnStnClickedStaticRotateMinVal();
	afx_msg void OnStnClickedStaticRotateMaxVal();
	afx_msg void OnStnClickedStaticTiltxMinVal();
	afx_msg void OnStnClickedStaticTiltxMaxVal();
	afx_msg void OnStnClickedStaticTiltyMinVal();
	afx_msg void OnStnClickedStaticTiltyMaxVal();
};
