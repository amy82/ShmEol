#pragma once

#include "afxwin.h"
#include "Utility\Label\Label.h"
#include "Utility\ButtonEx\ButtonCT.h"
// CKeyPadDlg 대화 상자입니다.

class CKeyPadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CKeyPadDlg)

public:
	CKeyPadDlg(CString sVal, int nMaxCount, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CKeyPadDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_KEYPAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	double GetReturnVal(){ return _ttof((TCHAR*)(LPCTSTR)m_sVal);}

private:
	void InitCtrl();

private:
	CFont m_clFontBig;
	CFont m_clFontMid;
	CFont m_clFontSmall;

	CString m_sVal;
	CString m_sCalcVal;
	int m_nMaxCount;
	bool m_bInit;
	
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonKeypadPlus();
	afx_msg void OnBnClickedButtonKeypadMinus();
	afx_msg void OnBnClickedButtonKeypadEqual();
	afx_msg void OnBnClickedButtonKeypadDel();
	afx_msg void OnBnClickedButtonKeypadDot();
	afx_msg void OnBnClickedButtonKeypadSign();
	afx_msg void OnBnClickedButtonKeypadClear();
	afx_msg void OnBnClickedButtonKeypadCancel();
	afx_msg void OnBnClickedButtonKeypadEnter();
	afx_msg void OnBnClickedButtonKeypadNum(UINT nID);

public:
    CLabel m_clColorStaticCalcVal;
    CLabel m_clColorStaticVal;
	CButtonCT m_clColorButtonNum[10];
	CButtonCT m_clColorButtonDot;
	CButtonCT m_clColorButtonSign;
	CButtonCT m_clColorButtonPlus;
	CButtonCT m_clColorButtonMinus;
	CButtonCT m_clColorButtonEqual;
	CButtonCT m_clColorButtonDel;
	CButtonCT m_clColorButtonClear;
	CButtonCT m_clColorButtonCancel;
	CButtonCT m_clColorButtonEnter;
	
};
