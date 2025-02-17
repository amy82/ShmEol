#pragma once

#include "uxmodule\uxbutton\ButtonCT.h"
// CSetDlg 대화 상자입니다.

class CSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetDlg)

public:
	CSetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INFO};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
    virtual BOOL OnInitDialog();

public:
    CButtonCT m_Btn_Info_Load;
    CButtonCT m_Btn_Info_Save;
    CButtonCT m_Btn_Oper;
    CButtonCT m_Btn_Eng;
};
