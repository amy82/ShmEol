#pragma once

#include "uxmodule\uxbutton\ButtonCT.h"
#include "uxmodule\GridCtrl\GridCtrl.h"
// CIoDlg 대화 상자입니다.

class CIoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIoDlg)

public:
	CIoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CIoDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IO};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();


    int oldInVal[4];

    bool m_bShowFlag;
    bool timerRunFlag;

    void	setInterface();
    void	initIoGrid();
    void	dispInputData();
    void	dispOutputData();

    CRect	m_rcGridDioIn;
    CRect	m_rcGridDioOut;
    //Grid
    CGridCtrl m_clGrid_IO_In;
    CGridCtrl m_clGrid_IO_Out;
    void	InitGridCtrl_In();
    void	InitGridCtrl_Out();

    int inRow;
    int inCol;
    int outRow;
    int outCol;
    int m_nCurrentCh;

    void IoInChChange();
    void IoOutChChange();

    CButtonCT	m_btn_Left;
    CButtonCT	m_btn_Right;
    virtual BOOL OnInitDialog();
};
