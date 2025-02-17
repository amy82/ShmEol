#pragma once

#include "resource.h"
#include "afxwin.h"
#include "Utility\Label\Label.h"
#include "Utility\ButtonEx\ButtonCT.h"
#include "Utility\Label\Label.h"
#include "CcdMarkViewDlg.h"
#include "CcdMarkViewDlg.h"
#include "EpoxySet.h"

// CManualDlg 대화 상자입니다.

class CManualDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualDlg)

public:
	CManualDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_MANUAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);
	
	void ShowMotorPositionState();
	void ShowDioState();
	void ShowAlignValue();
	void ShowLaserSelect();
	void SetUnitUI(int nUnit);
	CPoint clButtonPos[5];
	CPoint clButtonZPos[5];

public:
	CCcdMarkViewDlg m_clMarkViewDlg;
	CEpoxySet m_clEpoxySetDlg;
private:
	void InitCtrl();

private:
	CFont m_clFontBig;
	CFont m_clFontMid;
	CFont m_clFontSmall;

	int m_nUnit;
	int m_nPrevDarkPusherState[MAX_UNIT_COUNT];
	int m_nPrevPcbSocketState[MAX_UNIT_COUNT];
	int m_nPrevPcbSocketUpState[MAX_UNIT_COUNT];
	int m_nPrevPcbSocketVacuumOnState[MAX_UNIT_COUNT];
	int m_nPrevPcbSocketVacuumOffState[MAX_UNIT_COUNT];
	//bool m_bPrevLensSocketState[MAX_UNIT_COUNT];
	//bool m_bPrevUVReadyState[MAX_UNIT_COUNT];
	//bool m_bPrevUVAlarmState[MAX_UNIT_COUNT];
	//bool m_bPrevUVTimeState[MAX_UNIT_COUNT];
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonManualPcbVacuumOn();
	afx_msg void OnBnClickedButtonManualPcbVacuumOff();
	afx_msg void OnBnClickedButtonManualPcbGripFor();
	afx_msg void OnBnClickedButtonManualPcbGripBack();
	afx_msg void OnBnClickedButtonManualPcbDarkUp();
	afx_msg void OnBnClickedButtonManualPcbDarkDown();
	afx_msg void OnBnClickedButtonManualPcbOcFor();
	afx_msg void OnBnClickedButtonManualPcbOcBack();
	afx_msg void OnBnClickedButtonManualLensGripFor();
	afx_msg void OnBnClickedButtonManualLensGripBack();
	afx_msg void OnBnClickedButtonManualLensCentFor();
	afx_msg void OnBnClickedButtonManualLensCentBack();
	afx_msg void OnBnClickedButtonManualUvOn();
	afx_msg void OnBnClickedButtonManualUvOff();
	afx_msg void OnBnClickedButtonManualPcbWait();
	afx_msg void OnBnClickedButtonManualPcbZWait();
	afx_msg void OnBnClickedButtonManualPcbAlign();
	afx_msg void OnBnClickedButtonManualPcbZAlign();
	afx_msg void OnBnClickedButtonManualPcbLaserIn();
	afx_msg void OnBnClickedButtonManualPcbZLaserIn();
	afx_msg void OnBnClickedButtonManualPcbLaserOut();
	afx_msg void OnBnClickedButtonManualPcbZLaserOut();
	afx_msg void OnBnClickedButtonManualPcbLoad();
	afx_msg void OnBnClickedButtonManualPcbZLoad();
	afx_msg void OnBnClickedButtonManualPcbBonding();
	afx_msg void OnBnClickedButtonManualPcbZBonding();
	afx_msg void OnBnClickedButtonManualPcbDark();
	afx_msg void OnBnClickedButtonManualPcbZDark();
	afx_msg void OnBnClickedButtonManualPcbDefect();
	afx_msg void OnBnClickedButtonManualPcbZDefect();
	afx_msg void OnBnClickedButtonManualPcbZEscape();
	afx_msg void OnBnClickedButtonManualUvShutterOpen();
	afx_msg void OnBnClickedButtonManualUvShutterClose();
	afx_msg void OnBnClickedButtonManualAlign();
	afx_msg void OnBnClickedButtonManualAlignMove();
	afx_msg void OnBnClickedButtonManualLaserIn1();
	afx_msg void OnBnClickedButtonManualLaserIn2();
	afx_msg void OnBnClickedButtonManualLaserIn3();
	afx_msg void OnBnClickedButtonManualLaserIn4();
	afx_msg void OnBnClickedButtonManualLaserAutoMeas();
	afx_msg void OnBnClickedButtonManualLaserAuto();

public:
    CLabel m_clColorStaticTitle;
    CLabel m_clColorStaticTitlePCB;
    CLabel m_clColorStaticTitleLENS;
	CLabel m_clColorStaticTitlePcbIO;
	CLabel m_clColorStaticTitlePcbIO_IN;
    CLabel m_clColorStaticTitleLaser;
    CLabel m_clColorStaticTitleUvIO;
    CLabel m_clColorStaticTitleLensPos;
    CLabel m_clColorStaticTitleLensPosZ;


	CButtonCT m_clColorButtonPcbCheck;
	CButtonCT m_clColorButtonPcbVacuumOn;
	CButtonCT m_clColorButtonPcbVacuumOff;
	CButtonCT m_clColorButtonPcbGripFor;
	CButtonCT m_clColorButtonPcbGripBack;
	CButtonCT m_clColorButtonPcbSocketUp;
	CButtonCT m_clColorButtonPcbSocketDown;
	
	CButtonCT m_clColorButtonPcbDarkUp;
	CButtonCT m_clColorButtonPcbDarkDown;

	CButtonCT m_clColorButtonLensGrip;
	CButtonCT m_clColorButtonLensUnGrip;

	CButtonCT m_clColorButtonEpoxyOn;
	CButtonCT m_clColorButtonEpoxySet;
	

	CButtonCT m_clColorButtonPcbOCFor;
	CButtonCT m_clColorButtonPcbOCBack;
	CButtonCT m_clColorButtonPcbSocketCheck;
	CButtonCT m_clColorButtonLensGripFor;
	CButtonCT m_clColorButtonLensGripBack;
	CButtonCT m_clColorButtonLensCentFor;
	CButtonCT m_clColorButtonLensCentBack;
	CButtonCT m_clColorButtonLensSocketCheck;
	CButtonCT m_clColorButtonUVOn;
	CButtonCT m_clColorButtonUVOff;
	CButtonCT m_clColorButtonUVShutterOpen;
	CButtonCT m_clColorButtonUVShutterClose;
	CButtonCT m_clColorButtonUVReadyCheck;
	CButtonCT m_clColorButtonUVAlarmCheck;
	CButtonCT m_clColorButtonUVTimeCheck;

	CButtonCT m_clColorButtonPcbWaitPos;
	CButtonCT m_clColorButtonPcbAlignPos;
	CButtonCT m_clColorButtonPcbHolderAlignPos;
	CButtonCT m_clColorButtonPcbLaserInPos;
	CButtonCT m_clColorButtonPcbLaserOutPos;
	CButtonCT m_clColorButtonLensAlignPos;
	CButtonCT m_clColorButtonLensZAlignPos;

	
	CButtonCT m_clColorButtonPcbLoadPos;
	CButtonCT m_clColorButtonPcbUnLoadPos;
	CButtonCT m_clColorButtonPcbBondingPos;
	CButtonCT m_clColorButtonPcbDarkPos;
	CButtonCT m_clColorButtonPcbDefectPos;

	CButtonCT m_clColorButtonPcbLensAlignPos;
	CButtonCT m_clColorButtonPcbOcTotalPos;
	CButtonCT m_clColorButtonPcbDispensePos;

	CButtonCT m_clColorButtonPcbOc5000kPos;
	CButtonCT m_clColorButtonPcbZOc5000kPos;

	CButtonCT m_clColorButtonPcbZWaitPos;
	CButtonCT m_clColorButtonPcbZAlignPos;
	CButtonCT m_clColorButtonPcbZLoadPos;
	CButtonCT m_clColorButtonPcbZUnLoadPos;
	CButtonCT m_clColorButtonPcbZDarkPos;
	CButtonCT m_clColorButtonPcbZDefectPos;
	CButtonCT m_clColorButtonPcbZBondingPos;

	CButtonCT m_clColorButtonPcbZLaserInPos;
	CButtonCT m_clColorButtonPcbZLaserOutPos;
	CButtonCT m_clColorButtonPcbZEscapePos;

	CButtonCT m_clColorButtonPcbZLensAlignPos;
	CButtonCT m_clColorButtonPcbZOcTotalPos;
	CButtonCT m_clColorButtonPcbZHolderAlignPos;
	CButtonCT m_clColorButtonPcbZDispensePos;

	CButtonCT m_clColorButtonPcbEolAlignPos;
	CButtonCT m_clColorButtonPcbZEolAlignPos;
	CButtonCT m_clColorButtonPcbLaserPos;
	CButtonCT m_clColorButtonPcbZLaserPos;


	CButtonCT m_clColorButtonLensWaitPos;
	CButtonCT m_clColorButtonLensLoadPos;
	CButtonCT m_clColorButtonLensBondingPos;

	CButtonCT m_clColorButtonUnLoadPos;
	CButtonCT m_clColorButtonZUnLoadPos;

    CButtonCT m_clColorButtonLensZWaitPos;
	CButtonCT m_clColorButtonLensZLoadPos;
	//CButtonCT m_clColorButtonLensZLoadPos2;
    CButtonCT m_clColorButtonLensZBondingPos;
	
	CLabel m_clColorStaticAlignX;
	CLabel m_clColorStaticAlignY;
	CLabel m_clColorStaticAlignTH;
	CLabel m_clColorStaticAlignXVal;
	CLabel m_clColorStaticAlignYVal;
	CLabel m_clColorStaticAlignTHVal;
	CLabel m_clColorStaticBcrText;
    //

    CButtonCT m_clColorButtonAlign;
    CButtonCT m_clColorButtonAlignMove;
	CButtonCT m_clColorButtonLaserIn1;
	CButtonCT m_clColorButtonLaserIn2;
	CButtonCT m_clColorButtonLaserIn3;
	CButtonCT m_clColorButtonLaserIn4;
	CButtonCT m_clColorButtonLaserInZ;
	CButtonCT m_clColorButtonLaserDataMeas;
	CButtonCT m_clColorButtonLaserAutoMeas;

	CButtonCT m_clColorButtonPcbGripUp;
	CButtonCT m_clColorButtonPcbGripDown;

	CButtonCT m_clColorButtonPcbAutoLoad;
	CButtonCT m_clColorButtonPcbAutoUnLoad;
	CButtonCT m_clColorButtonPcbBCRReq;
	CButtonCT m_clColorButtonEpoxyInsp;

	CButtonCT m_clColorButtonPcbEolChartPos;
	CButtonCT m_clColorButtonPcbZEolChartPos;
	CButtonCT m_clColorButtonCurtainCheck;
	CButtonCT m_clColorButtonLensBufferCheck;
	CButtonCT m_clColorButtonLensBufferVacuumOn;
	CButtonCT m_clColorButtonLensBufferVacuumOff;


	afx_msg void OnBnClickedButtonManualPcbOc2800();
	afx_msg void OnBnClickedButtonManualPcbZDefect2();
	afx_msg void OnBnClickedButtonManualLensLoad();
	afx_msg void OnBnClickedButtonManualLensZLoad();
	afx_msg void OnBnClickedButtonManualUnload();
	afx_msg void OnBnClickedButtonManualZUnload();
	afx_msg void OnBnClickedButtonManualPcbGripUp();
	afx_msg void OnBnClickedButtonManualPcbGripDown();
	afx_msg void OnBnClickedButtonManualPcbSocketLoad();
	afx_msg void OnBnClickedButtonManualBarcode();
	afx_msg void OnBnClickedButtonManualPcbSocketUnload();
	afx_msg void OnBnClickedButtonManualLensWait();
	afx_msg void OnBnClickedButtonManualLensZWait();
	afx_msg void OnBnClickedButtonManualLensLoad2();
	//afx_msg void OnBnClickedButtonManualLensZLoad2();
	afx_msg void OnBnClickedButtonManualLensBonding();
	afx_msg void OnBnClickedButtonManualLensZBonding();
	afx_msg void OnBnClickedButtonManualLensGrip();
	afx_msg void OnBnClickedButtonManualLensUngrip();
	afx_msg void OnBnClickedButtonManualEpoxyOn();
	afx_msg void OnBnClickedButtonManualEpoxySet();
	afx_msg void OnBnClickedButtonManualPcbOcTotal();
	afx_msg void OnBnClickedButtonManualPcbDispense();
	afx_msg void OnBnClickedButtonManualPcbZOcTotal();
	afx_msg void OnBnClickedButtonManualPcbZDispense();
	afx_msg void OnBnClickedButtonManualLensAlign();
	afx_msg void OnBnClickedButtonManualLensZAlign();
	afx_msg void OnBnClickedButtonManualPcbHolderAlign();
	afx_msg void OnBnClickedButtonManualPcbZHolderAlign();
	afx_msg void OnBnClickedButtonManualPcbLaserLoad();
	afx_msg void OnBnClickedButtonManualEolAlign();
	afx_msg void OnBnClickedButtonManualPcbZLaserLoad();
	afx_msg void OnBnClickedButtonManualZEolAlign();
	afx_msg void OnBnClickedButtonManualEpoxyInsp();
	
	
	afx_msg void OnBnClickedButtonManualZEolChart();
	afx_msg void OnBnClickedButtonManualEolChart();
	afx_msg void OnBnClickedButtonManualEpoxyOn2();
	afx_msg void OnBnClickedButtonManualEpoxySet2();
	afx_msg void OnBnClickedButtonManualPcbSocketUp();
	afx_msg void OnBnClickedButtonManualPcbSocketDown();
	afx_msg void OnBnClickedButtonManualPcbUnload();
	afx_msg void OnBnClickedButtonManualPcbZUnload();
	afx_msg void OnBnClickedButtonLensBufferVacuumSensor();
	afx_msg void OnBnClickedButtonLensBufferVacuumOff();
	afx_msg void OnBnClickedButtonManualLaserInZ();
};
