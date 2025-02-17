#pragma once
#include "afxwin.h"
#include "Utility\GridCtrl\GridCtrl.h"
#include "Utility\Label\Label.h"
// CDioDlg 대화 상자입니다.

class CDioDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDioDlg)

public:
	CDioDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDioDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_DIO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);

private:
	void InitCtrl();
    void InitInGridCtrl();
    void InitOutGridCtrl();

	void ShowDIOName();
	void ShowDIONum();
	void ShowDInState();
	void ShowDOutState();

private:
	CFont m_clFontBig;
	CFont m_clFontMid;
	CFont m_clFontSmall;

	int m_nUnit;

	CGridCtrl m_clGridCtrlDIn;
	CGridCtrl m_clGridCtrlDOut;

	DWORD m_dwPrevDIn;
	DWORD m_dwPrevDOut;

public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMDblClickedDOut(NMHDR* pNMHDR, LRESULT* pResult);

public:
    CLabel m_clColorStaticTitle;
};
