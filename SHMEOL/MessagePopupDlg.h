#pragma once

#include "Utility\Label\Label.h"
#include "afxwin.h"

// CMessagePopupDlg 대화 상자입니다.

class CMessagePopupDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMessagePopupDlg)

public:
	CMessagePopupDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMessagePopupDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_MESSAGE_POPUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetContents(CString sTitle, CString sMsg, COLORREF bgColor, int nIndex);

private:
	void InitCtrl();

private:
	CFont m_clFontBig;
	CFont m_clFontMid;
	CFont m_clFontSmall;

	CString m_sTitle;
	CString m_sMsg;
	COLORREF m_bgColor;
	int m_nIndex;
		
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonMessagePopupConfirm();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	int CloseTime;
    CLabel m_clColorStaticTitle;
    CLabel m_clColorStaticMsg;
    CButtonCT m_clColorButtonConfirm;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
