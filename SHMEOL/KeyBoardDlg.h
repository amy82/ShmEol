#pragma once

#include "afxwin.h"
#include "Utility\Label\Label.h"
#include "Utility\ButtonEx\ButtonCT.h"
// CKeyBoardDlg 대화 상자입니다.

class CKeyBoardDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CKeyBoardDlg)

public:
	CKeyBoardDlg(int nMaxCount, bool bPasswd, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CKeyBoardDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_KEYBOARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	
public:
	CString GetReturnValue() { return m_sVal; };
	void SetReturnValue(CString sTemp);
private:
	void InitCtrl();

private:
	CFont m_clFontBig;
	CFont m_clFontMid;
	CFont m_clFontSmall;

	CString m_sVal;
	CString m_sHiddenVal;
	int m_nMaxCount;
	bool m_bPasswd;
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonKeyboardDash();
	afx_msg void OnBnClickedButtonKeyboardDot();
	afx_msg void OnBnClickedButtonKeyboardDel();
	afx_msg void OnBnClickedButtonKeyboardEnter();
	afx_msg void OnBnClickedButtonKeyboardCancel();
	afx_msg void OnBnClickedButtonKeyboardClear();
	afx_msg void OnBnClickedButtonKeyboardNum(UINT nID);
	afx_msg void OnBnClickedButtonKeyboardAlpha(UINT nID);

public:
    CLabel m_clColorStaticTopBar;
    CLabel m_clColorStaticVal;
	CEdit m_edtKeyBoardVal;

	CButtonCT m_clColorButtonNum[10];
	CButtonCT m_clColorButtonAlpha[26];
	CButtonCT m_clColorButtonDash;
	CButtonCT m_clColorButtonDot;
	CButtonCT m_clColorButtonDel;
	CButtonCT m_clColorButtonEnter;
	CButtonCT m_clColorButtonCancel;
	CButtonCT m_clColorButtonClear;
};
