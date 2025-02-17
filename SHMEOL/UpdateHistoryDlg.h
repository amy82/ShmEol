#pragma once

#include "Utility\GridCtrl\GridCtrl.h"
#include "Utility\Label\Label.h"
#include "afxwin.h"

// 2018.08.31. Jpromote
// CUpdateHistoryDlg 대화 상자입니다.

class CUpdateHistoryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateHistoryDlg)

public:
	CUpdateHistoryDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUpdateHistoryDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_UPDATE_HISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	void InitCtrl();
	void InitGridCtrl();
	
private:
	CFont m_clFontSmall;
	CFont m_clFontMid;
	CFont m_clFontBig;

	CGridCtrl m_clGridCtrlUpdateContents;
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();

public:
    CLabel m_clColorStaticUpdateHistory;
    CButtonCT m_clColorButtonClose;
	afx_msg void OnBnClickedButtonUpdateHistoryClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
