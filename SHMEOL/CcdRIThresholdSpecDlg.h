#pragma once

#include "afxwin.h"
#include "Utility\GridCtrl\GridCtrl.h"
#include "Utility\ButtonEx\ButtonCT.h"
#include "Utility\Label\Label.h"
// CCcdRIThresholdSpecDlg 대화 상자입니다.

class CCcdRIThresholdSpecDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCcdRIThresholdSpecDlg)

public:
    CCcdRIThresholdSpecDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCcdRIThresholdSpecDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CCD_RI_THRESHOLD_SPEC};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);
    const int RIThresholdMaxCount = 17;		//17 * 13 = 총 221개

    int RiThresholdGridCount;
private:
	void InitCtrl();
    void InitRiThresholdGridCtrl1();
    void InitRiThresholdGridCtrl2();
    void InitRiThresholdGridCtrl3();
    void InitRiThresholdGridCtrl4();
    void InitRiThresholdGridCtrl5();

    void ShowRIThresholdSpec();
    void GetRIThresholdSpec();


private:
    CGridCtrl m_clGridRIThresholdSpec1;
    CGridCtrl m_clGridRIThresholdSpec2;
    CGridCtrl m_clGridRIThresholdSpec3;
    CGridCtrl m_clGridRIThresholdSpec4;
    CGridCtrl m_clGridRIThresholdSpec5;

	CFont m_clFontSmall;
	CFont m_clFontMid;
	CFont m_clFontBig;

	int m_nUnit;
	int mLensGridRow;	//17
	int mLensGridCol;	//13
	int mLensCurrentCol;	//0 ~ 12
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	

	afx_msg void OnNMDblClickedRi1Spec(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblClickedRi2Spec(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblClickedRi3Spec(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMDblClickedRi4Spec(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMDblClickedRi5Spec(NMHDR* pNMHDR, LRESULT* pResult);
	


	afx_msg void OnStnClickedStaticCcdSfrSpecCenterSfrLimitVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecCornerSfrLimitVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecCornerSfrDeviationLimitVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecOcXyVal();
	afx_msg void OnStnClickedStaticCcdSfrSpecOcThVal();
	afx_msg void OnBnClickedButtonCcdSfrSpecSave();
	afx_msg void OnBnClickedButtonCcdSfrSpecClose();
	
public:
    CLabel m_clColorStaticLensShadingIndexVal;
	


	CLabel m_clColorStaticTopBar;
    CLabel m_clColorStaticCenterSfrLimit;
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

	CButtonCT m_clColorButtonLensShadingPrev;
	CButtonCT m_clColorButtonLensShadingNext;
	
		
	afx_msg void OnBnClickedButtonCcdLensShadingPrev();
	afx_msg void OnBnClickedButtonCcdLensShadingNext();
};
