#pragma once

#include "Utility\Label\Label.h"
#include "Utility\ButtonEx\ButtonCT.h"
#include "afxwin.h"

// CMessageModalDlg 대화 상자입니다.

class CMessageModalDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMessageModalDlg)

public:
	CMessageModalDlg(CString sTitle, CString sMsg, COLORREF bgColor, CString sYesBtn = _T("Yes"), CString sNoBtn = _T("No"), CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMessageModalDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_MESSAGE_MODAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	void InitCtrl();

private:
	CFont m_clFontBig;
	CFont m_clFontMid;
	CFont m_clFontSmall;

	CString m_sTitle;
	CString m_sMsg;


	CString m_sLeftBtnName;

	CString m_sRightBtnName;
	COLORREF m_bgColor;
	CBrush m_brushEdit;  // 배경색 브러시

public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonMessageModalYes();
	afx_msg void OnBnClickedButtonMessageModalNo();

public:
    CLabel m_clColorStaticTitle;
    CLabel m_clColorStaticMsg;
	CEdit m_edtModalMsg;
	//IDC_EDIT_MESSAGE_MODAL_MSG
    CButtonCT m_clColorButtonYes;
    CButtonCT m_clColorButtonNo;
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
