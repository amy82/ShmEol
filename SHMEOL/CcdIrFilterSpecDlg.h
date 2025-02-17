#pragma once

#include "afxwin.h"
#include "Utility\GridCtrl\GridCtrl.h"
#include "Utility\ButtonEx\ButtonCT.h"
#include "Utility\Label\Label.h"
// CCcdChartSpecDlg 대화 상자입니다.

class CCcdIrFilterSpecDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCcdIrFilterSpecDlg)

public:
	CCcdIrFilterSpecDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCcdIrFilterSpecDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CCD_IRFILTER_SPEC};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);
	const int IrFilterMaxCount = 8;
private:
	void InitCtrl();
	void InitIrFilterGridCtrl();

	void ShowIrFilterSpec();
	void GetIrFilterSpec();
private:
	CGridCtrl m_clGridIrFilterSpec;

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
	
	afx_msg void OnNMDblClickedIrFilterSpec(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedButtonCcdIrFilterSpecSave();
    afx_msg void OnBnClickedButtonCcdIrFilterSpecClose();

	
public:
	CLabel m_clColorStaticTopBar;
   

	CLabel m_clColorStaticHRotation;
	CLabel m_clColorStaticHRotationVal;
	
  
    CButtonCT m_clColorButtonSave;
    CButtonCT m_clColorButtonClose;

	afx_msg void OnStnClickedStaticCcdRotationVal();
};
