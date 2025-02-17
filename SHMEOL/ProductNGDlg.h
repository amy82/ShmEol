#pragma once

#include "afxwin.h"
#include "Utility\Label\Label.h"
#include "Utility\ButtonEx\ButtonCT.h"
// CProductNG

class CProductNGDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductNGDlg)

public:
	CProductNGDlg(CWnd* pParent = NULL);
	virtual ~CProductNGDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_NG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);

private:
	void InitCtrl();

private:
	CFont m_clFontSmall;
	CFont m_clFontMid;
	CFont m_clFontBig;
	CListCtrl m_clListCtrlNG;
	int m_nSelectList;
	int m_nUnit;

public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLvnItemchangedListNgList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonNgCancel();
	afx_msg void OnBnClickedButtonNgCheck();

public:
    CLabel m_clColorStaticTopBar;
    CLabel m_clColorStaticNGName;
	CButtonCT m_clColorButtonNGRetry;
	CButtonCT m_clColorButtonNGOk;
	CButtonCT m_clColorButtonNGPcb;
	CButtonCT m_clColorButtonNGProduct;
	CButtonCT m_clColorButtonNGCheck;
	CButtonCT m_clColorButtonNGCancel;
};


