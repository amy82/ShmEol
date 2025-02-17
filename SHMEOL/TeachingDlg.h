#pragma once
#include "afxwin.h"
#include "Utility\Label\Label.h"
#include "Utility\ButtonEx\ButtonCT.h"
#include "Utility\GridCtrl\GridCtrl.h"
#include "AXTDefine.h"

// CTeachingDlg 대화 상자입니다.

class CTeachingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTeachingDlg)

public:
	CTeachingDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTeachingDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_TEACHING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);

private:
	void InitCtrl();
	void InitGridCtrl();

	void ShowTeachingData();
	void ShowMotorState();
	void ChangeMode();
	void GetTeachData();

	void MoveMotorJog();
	void ShowSelectedAxis();
    void changeMotorNo(int MotorNo);
private:
    int GridRow;
    int GridCol;

	CFont m_clFontBig;
	CFont m_clFontMid;
	CFont m_clFontSmall;

	int m_nUnit;

	CGridCtrl m_clGridTeach;
	int m_nSelectAxis;
	double m_dJogSpeed;
	bool m_bMode;
	
	bool m_bPrevHomeState[MAX_MOTOR_COUNT];
	bool m_bPrevAlarm[MAX_MOTOR_COUNT];
	bool m_bPreNegLimit[MAX_MOTOR_COUNT];
	bool m_bPrePosLimit[MAX_MOTOR_COUNT];
	bool m_bPrevHome[MAX_MOTOR_COUNT];
	bool m_bPrevServoState[MAX_MOTOR_COUNT];

	bool m_bJogPosDir[MAX_MOTOR_COUNT];
	bool m_bPrevJogPosDir[MAX_MOTOR_COUNT];
	bool m_bJogNegDir[MAX_MOTOR_COUNT];
	bool m_bPrevJogNegDir[MAX_MOTOR_COUNT];

public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonTeachingJogStop();
	afx_msg void OnBnClickedButtonTeachingSpeedLow();
	afx_msg void OnBnClickedButtonTeachingSpeedMid();
	afx_msg void OnBnClickedButtonTeachingSpeedHigh();
	afx_msg void OnBnClickedButtonTeachingChangeMode();
	afx_msg void OnBnClickedButtonTeachingMoveMinus();
	afx_msg void OnBnClickedButtonTeachingMovePlus();
	afx_msg void OnStnClickedStaticTeachingMoveValue();
	afx_msg void OnBnClickedButtonTeachingServoOn();
	afx_msg void OnBnClickedButtonTeachingServoOff();
	afx_msg void OnBnClickedButtonTeachingServoReset();
	afx_msg void OnBnClickedButtonTeachingSave();
	afx_msg void OnNMClickedTeach(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDbclickedTeach(NMHDR* pNMHDR, LRESULT* pResult);

public:
    CLabel m_clColorStaticTitle;
    CLabel m_clColorStaticMoveVal;
    CLabel m_clColorStaticSelectedAxis;

	CButtonCT m_clColorButtonServoOn;
	CButtonCT m_clColorButtonServoOff;
	CButtonCT m_clColorButtonServoReset;

	CButtonCT m_clColorButtonAllServoOn;
	CButtonCT m_clColorButtonAllServoOff;
	CButtonCT m_clColorButtonAllServoReset;

	CButtonCT m_clColorButtonSpeedLow;
	CButtonCT m_clColorButtonSpeedMid;
	CButtonCT m_clColorButtonSpeedHigh;
	CButtonCT m_clColorButtonChangeMode;
	CButtonCT m_clColorButtonChangeMode2;
	CButtonCT m_clColorButtonJogMinus;
	CButtonCT m_clColorButtonJogStop;
	CButtonCT m_clColorButtonJogPlus;
	CButtonCT m_clColorButtonMoveMinus;
	CButtonCT m_clColorButtonMovePlus;
    CButtonCT m_clColorButtonSave;
	CButtonCT m_clColorButtonCrossImage;

    CButtonCT m_clColorButtonMotorX;
    CButtonCT m_clColorButtonMotorY;
    CButtonCT m_clColorButtonMotorZ;
    CButtonCT m_clColorButtonMotorTH;
    CButtonCT m_clColorButtonMotorTX;
    CButtonCT m_clColorButtonMotorTY;

	CButtonCT m_clColorButtonLensMotorX;
	CButtonCT m_clColorButtonLensMotorY;
	CButtonCT m_clColorButtonLensMotorZ;
	CButtonCT m_clColorButtonLensMotorTX;
	CButtonCT m_clColorButtonLensMotorTY;

    afx_msg void OnBnClickedButtonTeachingPcbX();
    afx_msg void OnBnClickedButtonTeachingPcbY();
    afx_msg void OnBnClickedButtonTeachingPcbZ();
    afx_msg void OnBnClickedButtonTeachingPcbTh();
    afx_msg void OnBnClickedButtonTeachingPcbTx();
    afx_msg void OnBnClickedButtonTeachingPcbTy();
	afx_msg void OnBnClickedButtonTeachingCross();
	afx_msg void OnBnClickedButtonTeachingLensX();
	afx_msg void OnBnClickedButtonTeachingLensY();
	afx_msg void OnBnClickedButtonTeachingLensZ();
	afx_msg void OnBnClickedButtonTeachingLensTx();
	afx_msg void OnBnClickedButtonTeachingLensTy();
	afx_msg void OnBnClickedButtonTeachingChangeMode2();
	afx_msg void OnBnClickedButtonTeachingAllServoOn();
	afx_msg void OnBnClickedButtonTeachingAllServoOff();
	afx_msg void OnBnClickedButtonTeachingAllServoReset();
};
