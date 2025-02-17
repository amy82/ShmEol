#pragma once

#include "afxwin.h"
#include "Utility\GridCtrl\GridCtrl.h"
#include "Utility\ButtonEx\ButtonCT.h"
#include "Utility\Label\Label.h"
// CCcdFpnSpecDlg 대화 상자입니다.

class CCcdFpnSpecDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCcdFpnSpecDlg)

public:
	CCcdFpnSpecDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCcdFpnSpecDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CCD_FPN_SPEC};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);

	const int RISpecCount = 9;//7;
private:
	void InitCtrl();

	void InitFpnGridCtrl();
	void InitFpnSpecGridCtrl();


	void ShowFpnSpec();
	void GetFpnSpec();
private:

	CGridCtrl m_clGridFpnSpec;
	CGridCtrl m_clGridFpnTestSpec;

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
	

	afx_msg void OnNMDblClickedFpnSpec(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblClickedFpnTestSpec(NMHDR* pNMHDR, LRESULT* pResult);

	


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
    CButtonCT m_clColorButtonSave;
    CButtonCT m_clColorButtonClose;
};
