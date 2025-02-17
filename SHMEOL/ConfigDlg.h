#pragma once
#include "afxwin.h"
#include "Utility\Label\Label.h"
#include "Utility\ButtonEx\ButtonCT.h"
// CConfigDlg 대화 상자입니다.

class CConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CConfigDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetUnit(int nUnit);
	void HideMtfOffset(bool bHide);
	void GetData();

private:
	void InitCtrl();
	void ShowData();
	void PopupShow();
private:
	CFont m_clFontBig;
	CFont m_clFontMid;
	CFont m_clFontSmall;

	int m_nUnit;
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnStnClickedStaticConfigSfrXSizeVal();
	afx_msg void OnStnClickedStaticConfigSfrYSizeVal();
	afx_msg void OnStnClickedStaticConfigCcdCellSizeVal();
	afx_msg void OnStnClickedStaticConfigMtfOffsetVal();
	afx_msg void OnStnClickedStaticConfigMoveVelRough();
	afx_msg void OnStnClickedStaticConfigMoveVelFine();
	afx_msg void OnStnClickedStaticConfigDelayRough();
	afx_msg void OnStnClickedStaticConfigDelayFine();
	afx_msg void OnStnClickedStaticConfigMoveDistanceRough();
	afx_msg void OnStnClickedStaticConfigMoveDistanceFine();
	afx_msg void OnStnClickedStaticConfigSfrAvgCountRough();
	afx_msg void OnStnClickedStaticConfigSfrAvgCountFine();
	afx_msg void OnStnClickedStaticConfigSecondAaMoveDistanceFine();
	afx_msg void OnStnClickedStaticConfigOkLimitRough();
	afx_msg void OnStnClickedStaticConfigOkLimitFine();
	afx_msg void OnStnClickedStaticConfigFineMoveChangeRough();
	afx_msg void OnStnClickedStaticConfigCheckDataCountVal();
	afx_msg void OnStnClickedStaticConfigSfrMoveDistanceVal();
	afx_msg void OnStnClickedStaticConfigSensorAlignRetryCount();
	afx_msg void OnStnClickedStaticConfigSensorAlignDelay();
	afx_msg void OnStnClickedStaticConfigLaserRetryCount();
	afx_msg void OnStnClickedStaticConfigLaserDelay();
	afx_msg void OnStnClickedStaticConfigInLaserXVal();
	afx_msg void OnStnClickedStaticConfigInLaserYVal();
	afx_msg void OnStnClickedStaticConfigOutLaserXVal();
	afx_msg void OnStnClickedStaticConfigOutLaserYVal();
	afx_msg void OnStnClickedStaticConfigStainWhiteCount();
	afx_msg void OnStnClickedStaticConfigStainBlackCount();
	afx_msg void OnStnClickedStaticConfigUvTimeVal();
	afx_msg void OnStnClickedStaticConfigPcbZEscapePosVal();
	afx_msg void OnStnClickedStaticConfigFpsStopVal();
	afx_msg void OnStnClickedStaticConfigPreUvOffsetLensXVal();
	afx_msg void OnStnClickedStaticConfigPreUvOffsetLensYVal();
	afx_msg void OnStnClickedStaticConfigPreUvOffsetLensZVal();
	afx_msg void OnStnClickedStaticConfigPreUvOffsetLensTxVal();
	afx_msg void OnStnClickedStaticConfigPreUvOffsetLensTyVal();
	afx_msg void OnStnClickedStaticConfigPreUvOffsetPcbThVal();
	afx_msg void OnStnClickedStaticConfigPcbVacuumDelayVal();
	afx_msg void OnStnClickedStaticConfigPcbGripDelayVal();
	afx_msg void OnStnClickedStaticConfigPcbUpDownDelayVal();
	afx_msg void OnStnClickedStaticConfigLaserTimeoutVal();
	afx_msg void OnStnClickedStaticConfigFinalDelayVal();
	afx_msg void OnStnClickedStaticConfigBondingDelayVal();
	afx_msg void OnStnClickedStaticConfigMainIpVal();
	afx_msg void OnStnClickedStaticConfigMainPortVal();
	afx_msg void OnBnClickedButtonConfigIniFind();
	afx_msg void OnBnClickedButtonConfigSave();
	afx_msg void OnStnClickedStaticConfigPinStopVal();
	afx_msg void OnStnClickedStaticConfigMoveAccRough();
	afx_msg void OnStnClickedStaticConfigMoveAccFine();
	afx_msg void OnStnClickedStaticConfigInspIpVal();
	afx_msg void OnStnClickedStaticConfigInspPortVal();
	afx_msg void OnStnClickedStaticConfigStainLcbCenterVal();
	afx_msg void OnStnClickedStaticConfigStainLcbCornerVal();
	afx_msg void OnStnClickedStaticConfigStainLcbEdgeVal();
	afx_msg void OnStnClickedStaticConfigStainYmeanCenterVal();
	afx_msg void OnStnClickedStaticConfigStainYmeanCornerVal();
	afx_msg void OnStnClickedStaticConfigStainYmeanEdgeVal();
	afx_msg void OnStnClickedStaticConfigMarkNoVal();
	afx_msg void OnStnClickedStaticConfigMarkMatchingVal();
public:
    CLabel m_clColorStaticTitle;

	CLabel m_clColorStaticSfrXSize;
	CLabel m_clColorStaticSfrXSizeVal;
	CLabel m_clColorStaticSfrYSize;
	CLabel m_clColorStaticSfrYSizeVal;
	CLabel m_clColorStaticCcdCellSize;
	CLabel m_clColorStaticCcdLinePulse;
	CLabel m_clColorStaticCcdBlackLevel;
	CLabel m_clColorStaticCcdLineDemosaic;
	
	CLabel m_clColorStaticCcdCellSizeVal;
    CLabel m_clColorStaticCcdLinePulseVal;

    CLabel m_clColorStaticCircle;
    CLabel m_clColorStaticCircleVal;

	CLabel m_clColorStaticRough;
	CLabel m_clColorStaticFine;
	CLabel m_clColorStaticMoveVel;
	CLabel m_clColorStaticMoveAcc;
	CLabel m_clColorStaticDelay;
	CLabel m_clColorStaticMoveDistance;
	CLabel m_clColorStaticSfrAvgCount;
	CLabel m_clColorStatic2ndAAMoveDistance;
	CLabel m_clColorStatic0Field;
	CLabel m_clColorStatic08Field;
	CLabel m_clColorStaticOkLimit;
	CLabel m_clColorStaticFineMoveChange;
	CLabel m_clColorStaticMoveVelRough;
	CLabel m_clColorStaticMoveVelFine;
	CLabel m_clColorStaticMoveAccRough;
	CLabel m_clColorStaticMoveAccFine;
	CLabel m_clColorStaticDelayRough;
	CLabel m_clColorStaticDelayFine;
	CLabel m_clColorStaticMoveDistanceRough;
	CLabel m_clColorStaticMoveDistanceFine;
	CLabel m_clColorStaticSfrAvgCountRough;
	CLabel m_clColorStaticSfrAvgCountFine;
	CLabel m_clColorStatic2ndAAMoveDistanceFine;
	CLabel m_clColorStaticOkLimitRough;
	CLabel m_clColorStaticOkLimitFine;
	CLabel m_clColorStaticFineMoveChangeRough;
	CLabel m_clColorStaticFineMoveChangeFine;

    CLabel m_clColorStaticCheckDataCount;
    CLabel m_clColorStaticCheckDataCountVal;
    CLabel m_clColorStaticSfrMoveDistance;
    CLabel m_clColorStaticSfrMoveDistanceVal;

    //CLabel m_clColorStaticField;
    //CLabel m_clColorStaticPosition;
	CComboBox m_clComboField;
	CComboBox m_clComboPosition;

    CLabel m_clColorStaticRetryCount;
    CLabel m_clColorStaticAlignDelay;
	CLabel m_clColorStaticSensorRetry;
	CLabel m_clColorStaticSensorRetryCount;
	CLabel m_clColorStaticContactRetry;
	CLabel m_clColorStaticContactRetryCount;
	CLabel m_clColorStaticContactRetryDelay;
	
	CLabel m_clColorStaticSensorDelay;

	CLabel m_clColorStaticCcdDelay;
	CLabel m_clColorStaticCcdRetryCount;
	CLabel m_clColorStaticCcdDelayVal;
	

	CLabel m_clColorStaticSensorAlignSpecXTitle;
	CLabel m_clColorStaticSensorAlignSpecYTitle;
	CLabel m_clColorStaticSensorAlignSpecTHTitle;
	CLabel m_clColorStaticSensorAlignSpecTitle;
	CLabel m_clColorStaticLensAlignSpecTitle;
	

	//CLabel m_clColorStaticOcAlignSpecTitle;
	//CLabel m_clColorStaticOcAlignSpecXTitle;
	CLabel m_clColorStaticOcAlignSpecYTitle;
	CLabel m_clColorStaticOcAlignSpecXVal;
	CLabel m_clColorStaticOcAlignSpecYVal;
	
		


	CLabel m_clColorStaticSensorAlignSpecX;
	CLabel m_clColorStaticSensorAlignSpecY;
	CLabel m_clColorStaticSensorAlignSpecTh;

	CLabel m_clColorStaticLensAlignSpecX;
	CLabel m_clColorStaticLensAlignSpecY;
	CLabel m_clColorStaticLensAlignSpecTh;
	
	CLabel m_clColorStaticLensRetry;
	CLabel m_clColorStaticLensRetryCount;
	CLabel m_clColorStaticLensDelay;

	CLabel m_clColorStaticLaserRetry;
	CLabel m_clColorStaticLaserRetryCount;
	CLabel m_clColorStaticLaserDelay;

	CLabel m_clColorStaticDiffRetry;
	CLabel m_clColorStaticDiffRetryCount;
	CLabel m_clColorStaticDiffDelay;

	CLabel m_clColorStaticInLaserX;
	CLabel m_clColorStaticInLaserXVal;
	CLabel m_clColorStaticInLaserY;
	CLabel m_clColorStaticInLaserYVal;
	CLabel m_clColorStaticOutLaserX;
	CLabel m_clColorStaticOutLaserXVal;
	CLabel m_clColorStaticOutLaserY;
	CLabel m_clColorStaticOutLaserYVal;

    CLabel m_clColorStaticStainWhite;
    CLabel m_clColorStaticStainWhiteCount;
    CLabel m_clColorStaticStainBlackCount;

    CLabel m_clColorStaticUvTime;
    CLabel m_clColorStaticUvTimeVal;

    CLabel m_clColorStaticEscapePcbZ;
    CLabel m_clColorStaticEscapePcbZVal;

    CLabel m_clColorStaticFpsStopVal;
    CLabel m_clColorStaticPinStopVal;

	CLabel m_clColorStaticPreUvOffsetLensX;
	CLabel m_clColorStaticPreUvOffsetLensXVal;
	CLabel m_clColorStaticPreUvOffsetLensY;
	CLabel m_clColorStaticPreUvOffsetLensYVal;
	CLabel m_clColorStaticPreUvOffsetLensZ;
	CLabel m_clColorStaticPreUvOffsetLensZVal;
	CLabel m_clColorStaticPreUvOffsetLensTx;
	CLabel m_clColorStaticPreUvOffsetLensTxVal;
	CLabel m_clColorStaticPreUvOffsetLensTy;
	CLabel m_clColorStaticPreUvOffsetLensTyVal;
	CLabel m_clColorStaticEolPcbTx;
	CLabel m_clColorStaticEolPcbTxVal;
	CLabel m_clColorStaticEolPcbTy;
	CLabel m_clColorStaticEolPcbTyVal;
	CLabel m_clColorStaticPreUvOffsetPcbTh;
	CLabel m_clColorStaticPreUvOffsetPcbThVal;

	CLabel m_clColorStaticPcbVacuumDelay;
	CLabel m_clColorStaticPcbVacuumDelayVal;
	CLabel m_clColorStaticPcbGripDelay;
	CLabel m_clColorStaticPcbGripDelayVal;

	CLabel m_clColorStaticLensGripDelay;
	CLabel m_clColorStaticLensGripDelayVal;

	CLabel m_clColorStaticPcbGripUpDelay;
	CLabel m_clColorStaticPcbGripUpDelayVal;
	CLabel m_clColorStaticLaserTimeout;
	CLabel m_clColorStaticLaserTimeoutVal;
	CLabel m_clColorStaticFinalDelay;
	CLabel m_clColorStaticFinalDelayVal;
	CLabel m_clColorStaticBondingDelay;
	CLabel m_clColorStaticBondingDelayVal;
	CLabel m_clColorStaticFPS;
	CLabel m_clColorStaticJxl;
	CLabel m_clColorStaticJxlVal;


	CLabel m_clColorStaticLightPort;
	CLabel m_clColorStaticLaserPort1;
    //CLabel m_clColorStaticLaserPort2;
	CLabel m_clColorStaticOcPort1;
	//CLabel m_clColorStaticOcPort2;
	CLabel m_clColorStaticChartPort1;
	CLabel m_clColorStaticLeftChartPort;
	CLabel m_clColorStaticRightChartPort;
	CLabel m_clColorStaticBcrPort;
	//CLabel m_clColorStaticUvPort;

	//
	//M3 3개만 사용
	CComboBox m_clComboChartLightPort1;	//AA)W = TOPCHART , M,N = TOPCHART + OC
	CComboBox m_clComboLeftChartLightPort;
	CComboBox m_clComboRightChartLightPort;
	CComboBox m_clComboEziModule;
	CComboBox m_clComboUvPort;
	//


	CComboBox m_clComboAlignLightPort1;
	CComboBox m_clComboTopLight1;
	CComboBox m_clComboTopLight2;
	CComboBox m_clComboOcLight2;
	CComboBox m_clComboLaser1;
	CComboBox m_clComboBcrPort;


	CLabel m_clColorStaticMesFactory;
	CLabel m_clColorStaticMesFactoryVal;

	CLabel m_clColorStaticDelDay;
	CLabel m_clColorStaticDelDayVal;
	
	CLabel m_clColorStaticPinCount;
	CLabel m_clColorStaticMainIp;
	CLabel m_clColorStaticMainIpVal;
	CLabel m_clColorStaticMainPort;
	CLabel m_clColorStaticMainPortVal;

	CLabel m_clColorStaticMesPort;
	CLabel m_clColorStaticMesPortVal;
	CLabel m_clColorStaticMesIp;
	CLabel m_clColorStaticMesIpVal;

    CLabel m_clColorStaticInspIp;
    CLabel m_clColorStaticInspIpVal;
    CLabel m_clColorStaticInspPort;
    CLabel m_clColorStaticInspPortVal;

	CButtonCT m_clColorButtonIniFind;
    CButtonCT m_clColorButtonSave;
	CButtonCT m_clColorButtonVerView;

	CButtonCT m_clColorButtonConfigDoorOpen;
	CButtonCT m_clColorButtonConfigDoorClose;

	CButtonCT m_clColorButtonConfigBcrOpen;
	CButtonCT m_clColorButtonConfigBcrClose;
	
    //CLabel m_clColorStaticDomeLightPort;
	CComboBox m_clComboDomeLightPort;

	CLabel m_clColorStaticStainLcb;
	CLabel m_clColorStaticStainLcbCenter;
	CLabel m_clColorStaticStinLcbCorner;
	CLabel m_clColorStaticStainLcbEdge;
	CLabel m_clColorStaticStainLcbCenterVal;
	CLabel m_clColorStaticStinLcbCornerVal;
	CLabel m_clColorStaticStainLcbEdgeVal;

	CLabel m_clColorStaticStainYMean;
	CLabel m_clColorStaticStainYMeanCenter;
	CLabel m_clColorStaticStinYMeanCorner;
	CLabel m_clColorStaticStainYMeanEdge;
	CLabel m_clColorStaticStainYMeanCenterVal;
	CLabel m_clColorStaticStinYMeanCornerVal;
	CLabel m_clColorStaticStainYMeanEdgeVal;

    CLabel m_clColorStaticMarkNo;
    CLabel m_clColorStaticMarkNoVal;
    CLabel m_clColorStaticMatching;
    CLabel m_clColorStaticMatchingVal;
	
	CLabel m_clColorStaticOutComplLaserXVal;
	CLabel m_clColorStaticOutComplLaserYVal;
	CLabel m_clColorStaticOutComplLaserX;
	CLabel m_clColorStaticOutComplLaserY;

    CBrush m_brCheck;
    afx_msg void OnStnClickedStaticConfigCcdLinePulseVal();
	afx_msg void OnStnClickedStaticConfigMesFactoryVal();
	afx_msg void OnStnClickedStaticConfigLensAlignRetryCount();
	afx_msg void OnStnClickedStaticConfigLensAlignDelay();
	afx_msg void OnStnClickedStaticConfigSensorAlignSpecX();
	afx_msg void OnStnClickedStaticConfigSensorAlignSpecY();
	afx_msg void OnStnClickedStaticConfigSensorAlignSpecTh();
	afx_msg void OnStnClickedStaticConfigLensAlignSpecX();
	afx_msg void OnStnClickedStaticConfigLensAlignSpecY();
	afx_msg void OnStnClickedStaticConfigLensAlignSpecTh();
	afx_msg void OnStnClickedStaticConfigLensGripDelayVal();

	afx_msg void OnStnClickedStaticConfigOutComplLaserXVal();
	afx_msg void OnStnClickedStaticConfigOutComplLaserYVal();
	CLabel m_clColorStaticMesFactoryCompl;
	CLabel m_clColorStaticMesFactoryComplVal;
	afx_msg void OnStnClickedStaticConfigMesFactoryComplVal();
	CLabel m_clColorStaticRawSumCount;
	CLabel m_clColorStaticRawSumCountVal;
	afx_msg void OnStnClickedStaticConfigRowSumcountVal();
	CLabel m_clColorStaticMaxStepCount;
	CLabel m_clColorStaticMaxStepCountVal;

	CLabel m_clColorStaticCcdBlackLevelVal;
	CComboBox m_ComboDemosaic;
	afx_msg void OnStnClickedStaticConfigMaxstepCountVal();
	afx_msg void OnStnClickedStaticConfigFineMoveChangeFine();
	afx_msg void OnStnClickedStaticConfigEolPcbTyVal();
	afx_msg void OnStnClickedStaticConfigEolPcbTxVal();
	afx_msg void OnStnClickedStaticConfigOcAlignSpecXVal();
	afx_msg void OnStnClickedStaticConfigOcAlignSpecYVal();
	afx_msg void OnStnClickedStaticConfigMesIpVal();
	afx_msg void OnStnClickedStaticConfigMesPortVal();
	afx_msg void OnStnClickedStaticConfigCcdBlacklevelVal();
	afx_msg void OnStnClickedStaticConfigCcdDelayVal();
	afx_msg void OnStnClickedStaticConfigContactRetryDelay();
	afx_msg void OnStnClickedStaticConfigContactRetryCount();
	afx_msg void OnStnClickedStaticConfigDelDayVal();
	afx_msg void OnStnClickedStaticConfigCcdRetryCount();
	afx_msg void OnBnClickedButtonConfigVerView();
	afx_msg void OnBnClickedButtonConfigDoorOpen();
	afx_msg void OnBnClickedButtonConfigDoorClose();
	afx_msg void OnStnClickedStaticConfigDiffRetryCount();
	afx_msg void OnStnClickedStaticConfigDiffDelay();
	afx_msg void OnBnClickedButtonConfigBcrOpen();
	afx_msg void OnBnClickedButtonConfigBcrClose();
	afx_msg void OnStnClickedStaticConfigJxlVal();
};
