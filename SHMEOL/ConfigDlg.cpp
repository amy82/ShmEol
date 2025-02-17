// ConfigDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"


// CConfigDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CConfigDlg, CDialogEx)

CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfigDlg::IDD, pParent)
{
	m_nUnit = UNIT_AA1;
    m_brCheck.CreateSolidBrush(RGB(45, 45, 45));
}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CONFIG_SFR_X_SIZE, m_clColorStaticSfrXSize);
	DDX_Control(pDX, IDC_STATIC_CONFIG_SFR_X_SIZE_VAL, m_clColorStaticSfrXSizeVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_SFR_Y_SIZE, m_clColorStaticSfrYSize);
	DDX_Control(pDX, IDC_STATIC_CONFIG_SFR_Y_SIZE_VAL, m_clColorStaticSfrYSizeVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_CCD_CELL_SIZE, m_clColorStaticCcdCellSize);
	DDX_Control(pDX, IDC_STATIC_CONFIG_CCD_LINE_PULSE, m_clColorStaticCcdLinePulse);

	DDX_Control(pDX, IDC_STATIC_CONFIG_CCD_CELL_SIZE_VAL, m_clColorStaticCcdCellSizeVal);
	
	
	DDX_Control(pDX, IDC_STATIC_CONFIG_CCD_LINE_PULSE_VAL, m_clColorStaticCcdLinePulseVal);

	DDX_Control(pDX, IDC_STATIC_CONFIG_CCD_BLACKLEVEL, m_clColorStaticCcdBlackLevel);
	DDX_Control(pDX, IDC_STATIC_CONFIG_CCD_DEMOSAIC, m_clColorStaticCcdLineDemosaic);
	
	DDX_Control(pDX, IDC_STATIC_CONFIG_MTF_OFFSET, m_clColorStaticCircle);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MTF_OFFSET_VAL, m_clColorStaticCircleVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_TITLE, m_clColorStaticTitle);
	DDX_Control(pDX, IDC_STATIC_CONFIG_ROUGH, m_clColorStaticRough);
	DDX_Control(pDX, IDC_STATIC_CONFIG_FINE, m_clColorStaticFine);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MOVE_VEL, m_clColorStaticMoveVel);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MOVE_ACC, m_clColorStaticMoveAcc);
	DDX_Control(pDX, IDC_STATIC_CONFIG_DELAY, m_clColorStaticDelay);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MOVE_DISTANCE, m_clColorStaticMoveDistance);
	DDX_Control(pDX, IDC_STATIC_CONFIG_SFR_AVG_COUNT, m_clColorStaticSfrAvgCount);
	DDX_Control(pDX, IDC_STATIC_CONFIG_SECOND_AA_MOVE_DISTANCE, m_clColorStatic2ndAAMoveDistance);
	DDX_Control(pDX, IDC_STATIC_CONFIG_0_FIELD, m_clColorStatic0Field);
	DDX_Control(pDX, IDC_STATIC_CONFIG_08_FIELD, m_clColorStatic08Field);
	DDX_Control(pDX, IDC_STATIC_CONFIG_OK_LIMIT, m_clColorStaticOkLimit);
	DDX_Control(pDX, IDC_STATIC_CONFIG_FINE_MOVE_CHANGE, m_clColorStaticFineMoveChange);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MOVE_VEL_ROUGH, m_clColorStaticMoveVelRough);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MOVE_VEL_FINE, m_clColorStaticMoveVelFine);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MOVE_ACC_ROUGH, m_clColorStaticMoveAccRough);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MOVE_ACC_FINE, m_clColorStaticMoveAccFine);
	DDX_Control(pDX, IDC_STATIC_CONFIG_DELAY_ROUGH, m_clColorStaticDelayRough);
	DDX_Control(pDX, IDC_STATIC_CONFIG_DELAY_FINE, m_clColorStaticDelayFine);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MOVE_DISTANCE_ROUGH, m_clColorStaticMoveDistanceRough);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MOVE_DISTANCE_FINE, m_clColorStaticMoveDistanceFine);
	DDX_Control(pDX, IDC_STATIC_CONFIG_SFR_AVG_COUNT_ROUGH, m_clColorStaticSfrAvgCountRough);
	DDX_Control(pDX, IDC_STATIC_CONFIG_SFR_AVG_COUNT_FINE, m_clColorStaticSfrAvgCountFine);
	DDX_Control(pDX, IDC_STATIC_CONFIG_SECOND_AA_MOVE_DISTANCE_FINE, m_clColorStatic2ndAAMoveDistanceFine);
	DDX_Control(pDX, IDC_STATIC_CONFIG_OK_LIMIT_ROUGH, m_clColorStaticOkLimitRough);
	DDX_Control(pDX, IDC_STATIC_CONFIG_OK_LIMIT_FINE, m_clColorStaticOkLimitFine);
	DDX_Control(pDX, IDC_STATIC_CONFIG_FINE_MOVE_CHANGE_ROUGH, m_clColorStaticFineMoveChangeRough);
	DDX_Control(pDX, IDC_STATIC_CONFIG_FINE_MOVE_CHANGE_FINE, m_clColorStaticFineMoveChangeFine);
	
	DDX_Control(pDX, IDC_STATIC_CONFIG_CHECK_DATA_COUNT, m_clColorStaticCheckDataCount);
	DDX_Control(pDX, IDC_STATIC_CONFIG_CHECK_DATA_COUNT_VAL, m_clColorStaticCheckDataCountVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_SFR_MOVE_DISTANCE, m_clColorStaticSfrMoveDistance);
	DDX_Control(pDX, IDC_STATIC_CONFIG_SFR_MOVE_DISTANCE_VAL, m_clColorStaticSfrMoveDistanceVal);
	DDX_Control(pDX, IDC_COMBO_CONFIG_USE_FIELD, m_clComboField);
	DDX_Control(pDX, IDC_COMBO_CONFIG_USE_POSITION, m_clComboPosition);
	DDX_Control(pDX, IDC_STATIC_CONFIG_RETRY_COUNT, m_clColorStaticRetryCount);
	DDX_Control(pDX, IDC_STATIC_CONFIG_ALIGN_DELAY, m_clColorStaticAlignDelay);

	DDX_Control(pDX, IDC_STATIC_CONFIG_SENSOR_ALIGN_RETRY, m_clColorStaticSensorRetry);
	DDX_Control(pDX, IDC_STATIC_CONFIG_SENSOR_ALIGN_RETRY_COUNT, m_clColorStaticSensorRetryCount);
	DDX_Control(pDX, IDC_STATIC_CONFIG_SENSOR_ALIGN_DELAY, m_clColorStaticSensorDelay);

	DDX_Control(pDX, IDC_STATIC_CONFIG_CCD_DELAY, m_clColorStaticCcdDelay);
	DDX_Control(pDX, IDC_STATIC_CONFIG_CCD_RETRY_COUNT, m_clColorStaticCcdRetryCount);
	DDX_Control(pDX, IDC_STATIC_CONFIG_CCD_DELAY_VAL, m_clColorStaticCcdDelayVal);
	

	DDX_Control(pDX, IDC_STATIC_CONFIG_CONTACT_RETRY, m_clColorStaticContactRetry);
	DDX_Control(pDX, IDC_STATIC_CONFIG_CONTACT_RETRY_COUNT, m_clColorStaticContactRetryCount);
	DDX_Control(pDX, IDC_STATIC_CONFIG_CONTACT_RETRY_DELAY, m_clColorStaticContactRetryDelay);

	

	//
	DDX_Control(pDX, IDC_STATIC_CONFIG_ALIGN_SPEC_X, m_clColorStaticSensorAlignSpecXTitle);
	DDX_Control(pDX, IDC_STATIC_CONFIG_ALIGN_SPEC_Y, m_clColorStaticSensorAlignSpecYTitle);
	DDX_Control(pDX, IDC_STATIC_CONFIG_ALIGN_SPEC_TH, m_clColorStaticSensorAlignSpecTHTitle);
	DDX_Control(pDX, IDC_STATIC_CONFIG_SENSOR_ALIGN_SPEC, m_clColorStaticSensorAlignSpecTitle);
	DDX_Control(pDX, IDC_STATIC_CONFIG_LENS_ALIGN_SPEC, m_clColorStaticLensAlignSpecTitle);

	DDX_Control(pDX, IDC_STATIC_CONFIG_OC_ALIGN_SPEC_Y, m_clColorStaticOcAlignSpecYTitle);
	DDX_Control(pDX, IDC_STATIC_CONFIG_OC_ALIGN_SPEC_X_VAL, m_clColorStaticOcAlignSpecXVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_OC_ALIGN_SPEC_Y_VAL, m_clColorStaticOcAlignSpecYVal);
	
	


	DDX_Control(pDX, IDC_STATIC_CONFIG_SENSOR_ALIGN_SPEC_X, m_clColorStaticSensorAlignSpecX);
	DDX_Control(pDX, IDC_STATIC_CONFIG_SENSOR_ALIGN_SPEC_Y, m_clColorStaticSensorAlignSpecY);
	DDX_Control(pDX, IDC_STATIC_CONFIG_SENSOR_ALIGN_SPEC_TH, m_clColorStaticSensorAlignSpecTh);

	DDX_Control(pDX, IDC_STATIC_CONFIG_LENS_ALIGN_SPEC_X, m_clColorStaticLensAlignSpecX);
	DDX_Control(pDX, IDC_STATIC_CONFIG_LENS_ALIGN_SPEC_Y, m_clColorStaticLensAlignSpecY);
	DDX_Control(pDX, IDC_STATIC_CONFIG_LENS_ALIGN_SPEC_TH, m_clColorStaticLensAlignSpecTh);
	//
	DDX_Control(pDX, IDC_STATIC_CONFIG_LENS_ALIGN_RETRY, m_clColorStaticLensRetry);
	DDX_Control(pDX, IDC_STATIC_CONFIG_LENS_ALIGN_RETRY_COUNT, m_clColorStaticLensRetryCount);
	DDX_Control(pDX, IDC_STATIC_CONFIG_LENS_ALIGN_DELAY, m_clColorStaticLensDelay);


	DDX_Control(pDX, IDC_STATIC_CONFIG_LASER_RETRY, m_clColorStaticLaserRetry);
	DDX_Control(pDX, IDC_STATIC_CONFIG_DIFF_RETRY, m_clColorStaticDiffRetry);
	
	DDX_Control(pDX, IDC_STATIC_CONFIG_LASER_RETRY_COUNT, m_clColorStaticLaserRetryCount);
	DDX_Control(pDX, IDC_STATIC_CONFIG_DIFF_RETRY_COUNT, m_clColorStaticDiffRetryCount);

	DDX_Control(pDX, IDC_STATIC_CONFIG_LASER_DELAY, m_clColorStaticLaserDelay);
	DDX_Control(pDX, IDC_STATIC_CONFIG_DIFF_DELAY, m_clColorStaticDiffDelay);

	DDX_Control(pDX, IDC_STATIC_CONFIG_IN_LASER_X, m_clColorStaticInLaserX);
	DDX_Control(pDX, IDC_STATIC_CONFIG_IN_LASER_X_VAL, m_clColorStaticInLaserXVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_IN_LASER_Y, m_clColorStaticInLaserY);
	DDX_Control(pDX, IDC_STATIC_CONFIG_IN_LASER_Y_VAL, m_clColorStaticInLaserYVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_OUT_LASER_X, m_clColorStaticOutLaserX);
	DDX_Control(pDX, IDC_STATIC_CONFIG_OUT_LASER_X_VAL, m_clColorStaticOutLaserXVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_OUT_LASER_Y, m_clColorStaticOutLaserY);
	DDX_Control(pDX, IDC_STATIC_CONFIG_OUT_LASER_Y_VAL, m_clColorStaticOutLaserYVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_STAIN_WHITE_COUNT, m_clColorStaticStainWhiteCount);
	DDX_Control(pDX, IDC_STATIC_CONFIG_STAIN_BLACK_COUNT, m_clColorStaticStainBlackCount);
	DDX_Control(pDX, IDC_STATIC_CONFIG_UV_TIME, m_clColorStaticUvTime);
	DDX_Control(pDX, IDC_STATIC_CONFIG_UV_TIME_VAL, m_clColorStaticUvTimeVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PCB_Z_ESCAPE_POS, m_clColorStaticEscapePcbZ);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PCB_Z_ESCAPE_POS_VAL, m_clColorStaticEscapePcbZVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_FPS_STOP_VAL, m_clColorStaticFpsStopVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PIN_STOP_VAL, m_clColorStaticPinStopVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PRE_UV_OFFSET_LENS_X, m_clColorStaticPreUvOffsetLensX);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PRE_UV_OFFSET_LENS_X_VAL, m_clColorStaticPreUvOffsetLensXVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PRE_UV_OFFSET_LENS_Y, m_clColorStaticPreUvOffsetLensY);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PRE_UV_OFFSET_LENS_Y_VAL, m_clColorStaticPreUvOffsetLensYVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PRE_UV_OFFSET_LENS_Z, m_clColorStaticPreUvOffsetLensZ);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PRE_UV_OFFSET_LENS_Z_VAL, m_clColorStaticPreUvOffsetLensZVal);

	DDX_Control(pDX, IDC_STATIC_CONFIG_PRE_UV_OFFSET_LENS_TX, m_clColorStaticPreUvOffsetLensTx);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PRE_UV_OFFSET_LENS_TX_VAL, m_clColorStaticPreUvOffsetLensTxVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PRE_UV_OFFSET_LENS_TY, m_clColorStaticPreUvOffsetLensTy);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PRE_UV_OFFSET_LENS_TY_VAL, m_clColorStaticPreUvOffsetLensTyVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_EOL_PCB_TX,			m_clColorStaticEolPcbTx);
	DDX_Control(pDX, IDC_STATIC_CONFIG_EOL_PCB_TX_VAL,		m_clColorStaticEolPcbTxVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_EOL_PCB_TY,			m_clColorStaticEolPcbTy);
	DDX_Control(pDX, IDC_STATIC_CONFIG_EOL_PCB_TY_VAL,		m_clColorStaticEolPcbTyVal);




	DDX_Control(pDX, IDC_STATIC_CONFIG_PRE_UV_OFFSET_PCB_TH, m_clColorStaticPreUvOffsetPcbTh);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PRE_UV_OFFSET_PCB_TH_VAL, m_clColorStaticPreUvOffsetPcbThVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PCB_VACUUM_DELAY, m_clColorStaticPcbVacuumDelay);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PCB_VACUUM_DELAY_VAL, m_clColorStaticPcbVacuumDelayVal);

	DDX_Control(pDX, IDC_STATIC_CONFIG_PCB_GRIP_DELAY, m_clColorStaticPcbGripDelay);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PCB_GRIP_DELAY_VAL, m_clColorStaticPcbGripDelayVal);

	DDX_Control(pDX, IDC_STATIC_CONFIG_LENS_GRIP_DELAY, m_clColorStaticLensGripDelay);
	DDX_Control(pDX, IDC_STATIC_CONFIG_LENS_GRIP_DELAY_VAL, m_clColorStaticLensGripDelayVal);

	DDX_Control(pDX, IDC_STATIC_CONFIG_PCB_GRIP_UP_DELAY, m_clColorStaticPcbGripUpDelay);
	DDX_Control(pDX, IDC_STATIC_CONFIG_PCB_GRIP_UP_DELAY_VAL, m_clColorStaticPcbGripUpDelayVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_LASER_TIMEOUT, m_clColorStaticLaserTimeout);
	DDX_Control(pDX, IDC_STATIC_CONFIG_LASER_TIMEOUT_VAL, m_clColorStaticLaserTimeoutVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_FINAL_DELAY, m_clColorStaticFinalDelay);
	DDX_Control(pDX, IDC_STATIC_CONFIG_FINAL_DELAY_VAL, m_clColorStaticFinalDelayVal);

	DDX_Control(pDX, IDC_STATIC_CONFIG_FPS, m_clColorStaticFPS);
	DDX_Control(pDX, IDC_STATIC_CONFIG_JXL, m_clColorStaticJxl);
	DDX_Control(pDX, IDC_STATIC_CONFIG_JXL_VAL, m_clColorStaticJxlVal);
	
	DDX_Control(pDX, IDC_STATIC_CONFIG_BONDING_DELAY, m_clColorStaticBondingDelay);
	DDX_Control(pDX, IDC_STATIC_CONFIG_BONDING_DELAY_VAL, m_clColorStaticBondingDelayVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_LIGHT_PORT, m_clColorStaticLightPort);
	DDX_Control(pDX, IDC_STATIC_CONFIG_LASER_PORT1, m_clColorStaticLaserPort1);

	DDX_Control(pDX, IDC_STATIC_CONFIG_BCR_PORT, m_clColorStaticBcrPort);


	DDX_Control(pDX, IDC_COMBO_CONFIG_LASER_PORT2, m_clComboTopLight2);
	DDX_Control(pDX, IDC_STATIC_CONFIG_OC_PORT, m_clColorStaticOcPort1);

	DDX_Control(pDX, IDC_COMBO_CONFIG_OC_PORT2, m_clComboOcLight2);

	////////
	//
	DDX_Control(pDX, IDC_COMBO_CONFIG_CHART_LIGHT_PORT1, m_clComboChartLightPort1);
	DDX_Control(pDX, IDC_COMBO_CONFIG_LEFT_CHART_LIGHT_PORT, m_clComboLeftChartLightPort);
	DDX_Control(pDX, IDC_COMBO_CONFIG_RIGHT_CHART_LIGHT_PORT, m_clComboRightChartLightPort);
	
	DDX_Control(pDX, IDC_COMBO_CONFIG_EZI_PORT, m_clComboEziModule);
	DDX_Control(pDX, IDC_COMBO_CONFIG_ALIGN_LIGHT_PORT1, m_clComboAlignLightPort1);
	DDX_Control(pDX, IDC_COMBO_CONFIG_LASER_PORT1, m_clComboLaser1);

	DDX_Control(pDX, IDC_COMBO_CONFIG_BCR_PORT, m_clComboBcrPort);
	DDX_Control(pDX, IDC_COMBO_CONFIG_UV_PORT, m_clComboUvPort);

	//
	////////

	DDX_Control(pDX, IDC_STATIC_CONFIG_CHART_LIGHT_PORT1, m_clColorStaticChartPort1);
	DDX_Control(pDX, IDC_STATIC_CONFIG_LEFT_CHART_LIGHT_PORT, m_clColorStaticLeftChartPort);
	DDX_Control(pDX, IDC_STATIC_CONFIG_RIGHT_CHART_LIGHT_PORT, m_clColorStaticRightChartPort);
	
	//
	DDX_Control(pDX, IDC_STATIC_MES_FACTORY, m_clColorStaticMesFactory);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MES_FACTORY_VAL, m_clColorStaticMesFactoryVal);

	DDX_Control(pDX, IDC_STATIC_CONFIG_DEL_DAY, m_clColorStaticDelDay);
	DDX_Control(pDX, IDC_STATIC_CONFIG_DEL_DAY_VAL, m_clColorStaticDelDayVal);

	

	DDX_Control(pDX, IDC_STATIC_CONFIG_PINT_COUNT, m_clColorStaticPinCount);

	DDX_Control(pDX, IDC_STATIC_CONFIG_MES_IP,		m_clColorStaticMesIp);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MES_IP_VAL,  m_clColorStaticMesIpVal);
	
	DDX_Control(pDX, IDC_STATIC_CONFIG_MAIN_IP, m_clColorStaticMainIp);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MAIN_IP_VAL, m_clColorStaticMainIpVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MAIN_PORT, m_clColorStaticMainPort);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MAIN_PORT_VAL, m_clColorStaticMainPortVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MES_PORT, m_clColorStaticMesPort);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MES_PORT_VAL, m_clColorStaticMesPortVal);


	
	DDX_Control(pDX, IDC_STATIC_CONFIG_INSP_IP, m_clColorStaticInspIp);
	DDX_Control(pDX, IDC_STATIC_CONFIG_INSP_IP_VAL, m_clColorStaticInspIpVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_INSP_PORT, m_clColorStaticInspPort);
	DDX_Control(pDX, IDC_STATIC_CONFIG_INSP_PORT_VAL, m_clColorStaticInspPortVal);
	DDX_Control(pDX, IDC_BUTTON_CONFIG_INI_FIND, m_clColorButtonIniFind);
	DDX_Control(pDX, IDC_BUTTON_CONFIG_SAVE, m_clColorButtonSave);
	DDX_Control(pDX, IDC_BUTTON_CONFIG_VER_VIEW, m_clColorButtonVerView);

	DDX_Control(pDX, IDC_BUTTON_CONFIG_DOOR_OPEN, m_clColorButtonConfigDoorOpen);
	DDX_Control(pDX, IDC_BUTTON_CONFIG_DOOR_CLOSE, m_clColorButtonConfigDoorClose);
	
	DDX_Control(pDX, IDC_BUTTON_CONFIG_BCR_OPEN, m_clColorButtonConfigBcrOpen);
	DDX_Control(pDX, IDC_BUTTON_CONFIG_BCR_CLOSE, m_clColorButtonConfigBcrClose);
	

	DDX_Control(pDX, IDC_COMBO_CONFIG_DOME_LIGHT_PORT, m_clComboDomeLightPort);
	DDX_Control(pDX, IDC_STATIC_CONFIG_STAIN_LCB, m_clColorStaticStainLcb);
	DDX_Control(pDX, IDC_STATIC_CONFIG_STAIN_LCB_CENTER, m_clColorStaticStainLcbCenter);
	DDX_Control(pDX, IDC_STATIC_CONFIG_STAIN_LCB_CORNER, m_clColorStaticStinLcbCorner);
	DDX_Control(pDX, IDC_STATIC_CONFIG_STAIN_LCB_EDGE, m_clColorStaticStainLcbEdge);
	DDX_Control(pDX, IDC_STATIC_CONFIG_STAIN_LCB_CENTER_VAL, m_clColorStaticStainLcbCenterVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_STAIN_LCB_CORNER_VAL, m_clColorStaticStinLcbCornerVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_STAIN_LCB_EDGE_VAL, m_clColorStaticStainLcbEdgeVal);

	DDX_Control(pDX, IDC_STATIC_CONFIG_STAIN_YMEAN, m_clColorStaticStainYMean);
	DDX_Control(pDX, IDC_STATIC_CONFIG_STAIN_YMEAN_CENTER, m_clColorStaticStainYMeanCenter);
	DDX_Control(pDX, IDC_STATIC_CONFIG_STAIN_YMEAN_CORNER, m_clColorStaticStinYMeanCorner);
	DDX_Control(pDX, IDC_STATIC_CONFIG_STAIN_YMEAN_EDGE, m_clColorStaticStainYMeanEdge);
	DDX_Control(pDX, IDC_STATIC_CONFIG_STAIN_YMEAN_CENTER_VAL, m_clColorStaticStainYMeanCenterVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_STAIN_YMEAN_CORNER_VAL, m_clColorStaticStinYMeanCornerVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_STAIN_YMEAN_EDGE_VAL, m_clColorStaticStainYMeanEdgeVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MARK_NO, m_clColorStaticMarkNo);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MARK_NO_VAL, m_clColorStaticMarkNoVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MARK_MATCHING, m_clColorStaticMatching);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MARK_MATCHING_VAL, m_clColorStaticMatchingVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_OUT_COMPL_LASER_X_VAL, m_clColorStaticOutComplLaserXVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_OUT_COMPL_LASER_Y_VAL, m_clColorStaticOutComplLaserYVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_OUT_COMPL_LASER_X, m_clColorStaticOutComplLaserX);
	DDX_Control(pDX, IDC_STATIC_CONFIG_OUT_COMPL_LASER_Y, m_clColorStaticOutComplLaserY);
	DDX_Control(pDX, IDC_STATIC_MES_FACTORY_COMPL, m_clColorStaticMesFactoryCompl);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MES_FACTORY_COMPL_VAL, m_clColorStaticMesFactoryComplVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_RAW_SUMCOUNT, m_clColorStaticRawSumCount);
	DDX_Control(pDX, IDC_STATIC_CONFIG_ROW_SUMCOUNT_VAL, m_clColorStaticRawSumCountVal);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MAXSTEP_COUNT, m_clColorStaticMaxStepCount);
	DDX_Control(pDX, IDC_STATIC_CONFIG_MAXSTEP_COUNT_VAL, m_clColorStaticMaxStepCountVal);


	DDX_Control(pDX, IDC_STATIC_CONFIG_CCD_BLACKLEVEL_VAL, m_clColorStaticCcdBlackLevelVal);
	DDX_Control(pDX, IDC_COMBO_DEMOSAIC, m_ComboDemosaic);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_STATIC_CONFIG_SFR_X_SIZE_VAL, &CConfigDlg::OnStnClickedStaticConfigSfrXSizeVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_SFR_Y_SIZE_VAL, &CConfigDlg::OnStnClickedStaticConfigSfrYSizeVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_CCD_CELL_SIZE_VAL, &CConfigDlg::OnStnClickedStaticConfigCcdCellSizeVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_MTF_OFFSET_VAL, &CConfigDlg::OnStnClickedStaticConfigMtfOffsetVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_MOVE_VEL_ROUGH, &CConfigDlg::OnStnClickedStaticConfigMoveVelRough)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_MOVE_VEL_FINE, &CConfigDlg::OnStnClickedStaticConfigMoveVelFine)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_DELAY_ROUGH, &CConfigDlg::OnStnClickedStaticConfigDelayRough)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_DELAY_FINE, &CConfigDlg::OnStnClickedStaticConfigDelayFine)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_MOVE_DISTANCE_ROUGH, &CConfigDlg::OnStnClickedStaticConfigMoveDistanceRough)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_MOVE_DISTANCE_FINE, &CConfigDlg::OnStnClickedStaticConfigMoveDistanceFine)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_MOVE_ACC_ROUGH, &CConfigDlg::OnStnClickedStaticConfigMoveAccRough)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_MOVE_ACC_FINE, &CConfigDlg::OnStnClickedStaticConfigMoveAccFine)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_SFR_AVG_COUNT_ROUGH, &CConfigDlg::OnStnClickedStaticConfigSfrAvgCountRough)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_SFR_AVG_COUNT_FINE, &CConfigDlg::OnStnClickedStaticConfigSfrAvgCountFine)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_SECOND_AA_MOVE_DISTANCE_FINE, &CConfigDlg::OnStnClickedStaticConfigSecondAaMoveDistanceFine)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_OK_LIMIT_ROUGH, &CConfigDlg::OnStnClickedStaticConfigOkLimitRough)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_OK_LIMIT_FINE, &CConfigDlg::OnStnClickedStaticConfigOkLimitFine)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_FINE_MOVE_CHANGE_ROUGH, &CConfigDlg::OnStnClickedStaticConfigFineMoveChangeRough)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_CHECK_DATA_COUNT_VAL, &CConfigDlg::OnStnClickedStaticConfigCheckDataCountVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_SFR_MOVE_DISTANCE_VAL, &CConfigDlg::OnStnClickedStaticConfigSfrMoveDistanceVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_SENSOR_ALIGN_RETRY_COUNT, &CConfigDlg::OnStnClickedStaticConfigSensorAlignRetryCount)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_SENSOR_ALIGN_DELAY, &CConfigDlg::OnStnClickedStaticConfigSensorAlignDelay)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_LASER_RETRY_COUNT, &CConfigDlg::OnStnClickedStaticConfigLaserRetryCount)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_LASER_DELAY, &CConfigDlg::OnStnClickedStaticConfigLaserDelay)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_IN_LASER_X_VAL, &CConfigDlg::OnStnClickedStaticConfigInLaserXVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_IN_LASER_Y_VAL, &CConfigDlg::OnStnClickedStaticConfigInLaserYVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_OUT_LASER_X_VAL, &CConfigDlg::OnStnClickedStaticConfigOutLaserXVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_OUT_LASER_Y_VAL, &CConfigDlg::OnStnClickedStaticConfigOutLaserYVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_STAIN_WHITE_COUNT, &CConfigDlg::OnStnClickedStaticConfigStainWhiteCount)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_STAIN_BLACK_COUNT, &CConfigDlg::OnStnClickedStaticConfigStainBlackCount)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_UV_TIME_VAL, &CConfigDlg::OnStnClickedStaticConfigUvTimeVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_PCB_Z_ESCAPE_POS_VAL, &CConfigDlg::OnStnClickedStaticConfigPcbZEscapePosVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_FPS_STOP_VAL, &CConfigDlg::OnStnClickedStaticConfigFpsStopVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_PRE_UV_OFFSET_LENS_X_VAL, &CConfigDlg::OnStnClickedStaticConfigPreUvOffsetLensXVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_PRE_UV_OFFSET_LENS_Y_VAL, &CConfigDlg::OnStnClickedStaticConfigPreUvOffsetLensYVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_PRE_UV_OFFSET_LENS_Z_VAL, &CConfigDlg::OnStnClickedStaticConfigPreUvOffsetLensZVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_PRE_UV_OFFSET_LENS_TX_VAL, &CConfigDlg::OnStnClickedStaticConfigPreUvOffsetLensTxVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_PRE_UV_OFFSET_LENS_TY_VAL, &CConfigDlg::OnStnClickedStaticConfigPreUvOffsetLensTyVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_PRE_UV_OFFSET_PCB_TH_VAL, &CConfigDlg::OnStnClickedStaticConfigPreUvOffsetPcbThVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_PCB_VACUUM_DELAY_VAL, &CConfigDlg::OnStnClickedStaticConfigPcbVacuumDelayVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_PCB_GRIP_DELAY_VAL, &CConfigDlg::OnStnClickedStaticConfigPcbGripDelayVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_PCB_GRIP_UP_DELAY_VAL, &CConfigDlg::OnStnClickedStaticConfigPcbUpDownDelayVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_LASER_TIMEOUT_VAL, &CConfigDlg::OnStnClickedStaticConfigLaserTimeoutVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_FINAL_DELAY_VAL, &CConfigDlg::OnStnClickedStaticConfigFinalDelayVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_BONDING_DELAY_VAL, &CConfigDlg::OnStnClickedStaticConfigBondingDelayVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_MAIN_IP_VAL, &CConfigDlg::OnStnClickedStaticConfigMainIpVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_MAIN_PORT_VAL, &CConfigDlg::OnStnClickedStaticConfigMainPortVal)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_INI_FIND, &CConfigDlg::OnBnClickedButtonConfigIniFind)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_SAVE, &CConfigDlg::OnBnClickedButtonConfigSave)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_PIN_STOP_VAL, &CConfigDlg::OnStnClickedStaticConfigPinStopVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_INSP_IP_VAL, &CConfigDlg::OnStnClickedStaticConfigInspIpVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_INSP_PORT_VAL, &CConfigDlg::OnStnClickedStaticConfigInspPortVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_STAIN_LCB_CENTER_VAL, &CConfigDlg::OnStnClickedStaticConfigStainLcbCenterVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_STAIN_LCB_CORNER_VAL, &CConfigDlg::OnStnClickedStaticConfigStainLcbCornerVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_STAIN_LCB_EDGE_VAL, &CConfigDlg::OnStnClickedStaticConfigStainLcbEdgeVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_STAIN_YMEAN_CENTER_VAL, &CConfigDlg::OnStnClickedStaticConfigStainYmeanCenterVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_STAIN_YMEAN_CORNER_VAL, &CConfigDlg::OnStnClickedStaticConfigStainYmeanCornerVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_STAIN_YMEAN_EDGE_VAL, &CConfigDlg::OnStnClickedStaticConfigStainYmeanEdgeVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_MARK_NO_VAL, &CConfigDlg::OnStnClickedStaticConfigMarkNoVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_MARK_MATCHING_VAL, &CConfigDlg::OnStnClickedStaticConfigMarkMatchingVal)
    ON_STN_CLICKED(IDC_STATIC_CONFIG_CCD_LINE_PULSE_VAL, &CConfigDlg::OnStnClickedStaticConfigCcdLinePulseVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_MES_FACTORY_VAL, &CConfigDlg::OnStnClickedStaticConfigMesFactoryVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_LENS_ALIGN_RETRY_COUNT, &CConfigDlg::OnStnClickedStaticConfigLensAlignRetryCount)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_LENS_ALIGN_DELAY, &CConfigDlg::OnStnClickedStaticConfigLensAlignDelay)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_SENSOR_ALIGN_SPEC_X, &CConfigDlg::OnStnClickedStaticConfigSensorAlignSpecX)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_SENSOR_ALIGN_SPEC_Y, &CConfigDlg::OnStnClickedStaticConfigSensorAlignSpecY)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_SENSOR_ALIGN_SPEC_TH, &CConfigDlg::OnStnClickedStaticConfigSensorAlignSpecTh)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_LENS_ALIGN_SPEC_X, &CConfigDlg::OnStnClickedStaticConfigLensAlignSpecX)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_LENS_ALIGN_SPEC_Y, &CConfigDlg::OnStnClickedStaticConfigLensAlignSpecY)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_LENS_ALIGN_SPEC_TH, &CConfigDlg::OnStnClickedStaticConfigLensAlignSpecTh)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_LENS_GRIP_DELAY_VAL, &CConfigDlg::OnStnClickedStaticConfigLensGripDelayVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_OUT_COMPL_LASER_X_VAL, &CConfigDlg::OnStnClickedStaticConfigOutComplLaserXVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_OUT_COMPL_LASER_Y_VAL, &CConfigDlg::OnStnClickedStaticConfigOutComplLaserYVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_MES_FACTORY_COMPL_VAL, &CConfigDlg::OnStnClickedStaticConfigMesFactoryComplVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_ROW_SUMCOUNT_VAL, &CConfigDlg::OnStnClickedStaticConfigRowSumcountVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_MAXSTEP_COUNT_VAL, &CConfigDlg::OnStnClickedStaticConfigMaxstepCountVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_FINE_MOVE_CHANGE_FINE, &CConfigDlg::OnStnClickedStaticConfigFineMoveChangeFine)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_EOL_PCB_TY_VAL, &CConfigDlg::OnStnClickedStaticConfigEolPcbTyVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_EOL_PCB_TX_VAL, &CConfigDlg::OnStnClickedStaticConfigEolPcbTxVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_OC_ALIGN_SPEC_X_VAL, &CConfigDlg::OnStnClickedStaticConfigOcAlignSpecXVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_OC_ALIGN_SPEC_Y_VAL, &CConfigDlg::OnStnClickedStaticConfigOcAlignSpecYVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_MES_IP_VAL, &CConfigDlg::OnStnClickedStaticConfigMesIpVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_MES_PORT_VAL, &CConfigDlg::OnStnClickedStaticConfigMesPortVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_CCD_BLACKLEVEL_VAL, &CConfigDlg::OnStnClickedStaticConfigCcdBlacklevelVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_CCD_DELAY_VAL, &CConfigDlg::OnStnClickedStaticConfigCcdDelayVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_CONTACT_RETRY_DELAY, &CConfigDlg::OnStnClickedStaticConfigContactRetryDelay)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_CONTACT_RETRY_COUNT, &CConfigDlg::OnStnClickedStaticConfigContactRetryCount)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_DEL_DAY_VAL, &CConfigDlg::OnStnClickedStaticConfigDelDayVal)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_CCD_RETRY_COUNT, &CConfigDlg::OnStnClickedStaticConfigCcdRetryCount)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_VER_VIEW, &CConfigDlg::OnBnClickedButtonConfigVerView)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_DOOR_OPEN, &CConfigDlg::OnBnClickedButtonConfigDoorOpen)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_DOOR_CLOSE, &CConfigDlg::OnBnClickedButtonConfigDoorClose)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_DIFF_RETRY_COUNT, &CConfigDlg::OnStnClickedStaticConfigDiffRetryCount)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_DIFF_DELAY, &CConfigDlg::OnStnClickedStaticConfigDiffDelay)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_BCR_OPEN, &CConfigDlg::OnBnClickedButtonConfigBcrOpen)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_BCR_CLOSE, &CConfigDlg::OnBnClickedButtonConfigBcrClose)
	ON_STN_CLICKED(IDC_STATIC_CONFIG_JXL_VAL, &CConfigDlg::OnStnClickedStaticConfigJxlVal)
END_MESSAGE_MAP()


// CConfigDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	GetClientRect(rect);

	dc.FillSolidRect(rect, RGB_DLG_BG);
}

//-----------------------------------------------------------------------------
//
//	다이얼로그 초기화
//
//-----------------------------------------------------------------------------
BOOL CConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 컨트롤 초기화
	this->InitCtrl();
	this->ShowData();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CConfigDlg::InitCtrl()
{
	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_CCD_FLIP_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_DRY_RUN_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_COMPL_MODE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_UV_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_LASER_IN_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_LASER_OUT_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_UNLOAD_AFTER_1ST_AA_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_STAIN_INSP_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_DARK_INSP_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_DEFECT_INSP_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_DOORLOCK_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_EPOXY_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_EPOXY_INSP_USE)->m_hWnd, L"", L"");
	
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_FPS_STOP_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_SFR_AVERAGE)->m_hWnd, L"", L"");
	
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_PIN_STOP_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_MASTER_MODE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_INSP_PASS)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_ALIGN_PASS)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_RAW_SAVE_PASS)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_JXL_SAVE_PASS)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_IDLE_REPORT_PASS)->m_hWnd, L"", L"");
	
	
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_LASER_LOCK)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_DOME_CHART_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_UV_LAMP_ALARM_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_AA_PASS)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_INSPECTION_PASS)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_SFR_OVERLAY_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_NG_IMAGE_SAVE)->m_hWnd, L"", L"");

	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_SATURATION_INSP_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_IRFILTER_INSP_USE)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_CHECK_CONFIG_COLOR_REPRODUCTION_INSP_USE)->m_hWnd, L"", L"");
	

	m_clColorStaticTitle.SetBkColor(RGB_CTRL_BG);
	m_clColorStaticTitle.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticTitle.SetFont(&m_clFontBig);
    m_clColorStaticTitle.SetFontBold(TRUE);
    m_clColorStaticTitle.SetBorder(FALSE);
    m_clColorStaticTitle.SetFontSize(15);

	m_clColorStaticSfrXSize.SetBkColor(RGB_DLG_BG);
	m_clColorStaticSfrXSize.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticSfrXSize.SetFont(&m_clFontSmall);

	m_clColorStaticSfrXSizeVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticSfrXSizeVal.SetFont(&m_clFontSmall);

	m_clColorStaticSfrYSize.SetBkColor(RGB_DLG_BG);
	m_clColorStaticSfrYSize.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticSfrYSize.SetFont(&m_clFontSmall);

	m_clColorStaticSfrYSizeVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticSfrYSizeVal.SetFont(&m_clFontSmall);

    m_clColorStaticCcdCellSize.SetBkColor(RGB_DLG_BG);
    m_clColorStaticCcdCellSize.SetTextColor(RGB_COLOR_WHITE);
    m_clColorStaticCcdCellSize.SetFont(&m_clFontSmall);

	m_clColorStaticCcdLinePulse.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdLinePulse.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdLinePulse.SetFont(&m_clFontSmall);

	m_clColorStaticCcdBlackLevel.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdBlackLevel.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdBlackLevel.SetFont(&m_clFontSmall);

	m_clColorStaticCcdLineDemosaic.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdLineDemosaic.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdLineDemosaic.SetFont(&m_clFontSmall);
	
    m_clColorStaticCcdCellSizeVal.SetBkColor(RGB_COLOR_WHITE);
    m_clColorStaticCcdCellSizeVal.SetFont(&m_clFontSmall);

	m_clColorStaticCcdBlackLevelVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdBlackLevelVal.SetFont(&m_clFontSmall);

    m_clColorStaticCcdLinePulseVal.SetBkColor(RGB_COLOR_WHITE);
    m_clColorStaticCcdLinePulseVal.SetFont(&m_clFontSmall);


	m_clColorStaticCircle.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCircle.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCircle.SetFont(&m_clFontSmall);

	m_clColorStaticCircleVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticCircleVal.SetFont(&m_clFontSmall);

	m_clColorStaticRough.SetBkColor(RGB_DLG_BG);
	m_clColorStaticRough.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticRough.SetFont(&m_clFontSmall);

	m_clColorStaticFine.SetBkColor(RGB_DLG_BG);
	m_clColorStaticFine.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticFine.SetFont(&m_clFontSmall);

	m_clColorStaticMoveVel.SetBkColor(RGB_DLG_BG);
	m_clColorStaticMoveVel.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticMoveVel.SetFont(&m_clFontSmall);

	m_clColorStaticMoveAcc.SetBkColor(RGB_DLG_BG);
	m_clColorStaticMoveAcc.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticMoveAcc.SetFont(&m_clFontSmall);

	m_clColorStaticDelay.SetBkColor(RGB_DLG_BG);
	m_clColorStaticDelay.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticDelay.SetFont(&m_clFontSmall);

	m_clColorStaticMoveDistance.SetBkColor(RGB_DLG_BG);
	m_clColorStaticMoveDistance.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticMoveDistance.SetFont(&m_clFontSmall);

	m_clColorStaticSfrAvgCount.SetBkColor(RGB_DLG_BG);
	m_clColorStaticSfrAvgCount.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticSfrAvgCount.SetFont(&m_clFontSmall);

	m_clColorStatic2ndAAMoveDistance.SetBkColor(RGB_DLG_BG);
	m_clColorStatic2ndAAMoveDistance.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStatic2ndAAMoveDistance.SetFont(&m_clFontSmall);

	m_clColorStatic0Field.SetBkColor(RGB_DLG_BG);
	m_clColorStatic0Field.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStatic0Field.SetFont(&m_clFontSmall);

	m_clColorStatic08Field.SetBkColor(RGB_DLG_BG);
	m_clColorStatic08Field.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStatic08Field.SetFont(&m_clFontSmall);

	m_clColorStaticOkLimit.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOkLimit.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOkLimit.SetFont(&m_clFontSmall);

	m_clColorStaticFineMoveChange.SetBkColor(RGB_DLG_BG);
	m_clColorStaticFineMoveChange.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticFineMoveChange.SetFont(&m_clFontSmall);

	m_clColorStaticMoveVelRough.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticMoveVelRough.SetFont(&m_clFontSmall);

	m_clColorStaticMoveVelFine.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticMoveVelFine.SetFont(&m_clFontSmall);

	m_clColorStaticMoveAccRough.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticMoveAccRough.SetFont(&m_clFontSmall);

	m_clColorStaticMoveAccFine.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticMoveAccFine.SetFont(&m_clFontSmall);

	m_clColorStaticDelayRough.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticDelayRough.SetFont(&m_clFontSmall);

	m_clColorStaticDelayFine.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticDelayFine.SetFont(&m_clFontSmall);

	m_clColorStaticMoveDistanceRough.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticMoveDistanceRough.SetFont(&m_clFontSmall);

	m_clColorStaticMoveDistanceFine.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticMoveDistanceFine.SetFont(&m_clFontSmall);

	m_clColorStaticSfrAvgCountRough.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticSfrAvgCountRough.SetFont(&m_clFontSmall);

	m_clColorStaticSfrAvgCountFine.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticSfrAvgCountFine.SetFont(&m_clFontSmall);

	m_clColorStatic2ndAAMoveDistanceFine.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStatic2ndAAMoveDistanceFine.SetFont(&m_clFontSmall);

	m_clColorStaticOkLimitRough.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOkLimitRough.SetFont(&m_clFontSmall);

	m_clColorStaticOkLimitFine.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOkLimitFine.SetFont(&m_clFontSmall);

	m_clColorStaticFineMoveChangeRough.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticFineMoveChangeRough.SetFont(&m_clFontSmall);

	m_clColorStaticFineMoveChangeFine.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticFineMoveChangeFine.SetFont(&m_clFontSmall);

	

	m_clColorStaticCheckDataCount.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCheckDataCount.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCheckDataCount.SetFont(&m_clFontSmall);

	m_clColorStaticCheckDataCountVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticCheckDataCountVal.SetFont(&m_clFontSmall);

	m_clColorStaticSfrMoveDistance.SetBkColor(RGB_DLG_BG);
	m_clColorStaticSfrMoveDistance.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticSfrMoveDistance.SetFont(&m_clFontSmall);

	m_clColorStaticSfrMoveDistanceVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticSfrMoveDistanceVal.SetFont(&m_clFontSmall);


	m_clComboField.SetFont(&m_clFontSmall);
	m_clComboPosition.SetFont(&m_clFontSmall);

	m_clColorStaticRetryCount.SetBkColor(RGB_DLG_BG);
	m_clColorStaticRetryCount.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticRetryCount.SetFont(&m_clFontSmall);

	m_clColorStaticCcdDelay.SetBkColor(RGB_DLG_BG);
	m_clColorStaticCcdDelay.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdDelay.SetFont(&m_clFontSmall);
	m_clColorStaticCcdRetryCount.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdRetryCount.SetFont(&m_clFontSmall);



	m_clColorStaticAlignDelay.SetBkColor(RGB_DLG_BG);
	m_clColorStaticAlignDelay.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticAlignDelay.SetFont(&m_clFontSmall);

	m_clColorStaticSensorRetry.SetBkColor(RGB_DLG_BG);
	m_clColorStaticSensorRetry.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticSensorRetry.SetFont(&m_clFontSmall);

	m_clColorStaticSensorRetryCount.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticSensorRetryCount.SetFont(&m_clFontSmall);
	

	
	



	m_clColorStaticContactRetry.SetBkColor(RGB_DLG_BG);
	m_clColorStaticContactRetry.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticContactRetry.SetFont(&m_clFontSmall);
	
	m_clColorStaticContactRetryCount.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticContactRetryCount.SetFont(&m_clFontSmall);

	m_clColorStaticContactRetryDelay.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticContactRetryDelay.SetFont(&m_clFontSmall);





	m_clColorStaticOcAlignSpecYTitle.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOcAlignSpecYTitle.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOcAlignSpecYTitle.SetFont(&m_clFontSmall);

	m_clColorStaticOcAlignSpecXVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOcAlignSpecXVal.SetFont(&m_clFontSmall);

	m_clColorStaticOcAlignSpecYVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOcAlignSpecYVal.SetFont(&m_clFontSmall);


	m_clColorStaticSensorAlignSpecXTitle.SetBkColor(RGB_DLG_BG);
	m_clColorStaticSensorAlignSpecXTitle.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticSensorAlignSpecXTitle.SetFont(&m_clFontSmall);

	m_clColorStaticSensorAlignSpecYTitle.SetBkColor(RGB_DLG_BG);
	m_clColorStaticSensorAlignSpecYTitle.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticSensorAlignSpecYTitle.SetFont(&m_clFontSmall);

	m_clColorStaticSensorAlignSpecTHTitle.SetBkColor(RGB_DLG_BG);
	m_clColorStaticSensorAlignSpecTHTitle.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticSensorAlignSpecTHTitle.SetFont(&m_clFontSmall);

	m_clColorStaticSensorAlignSpecTitle.SetBkColor(RGB_DLG_BG);
	m_clColorStaticSensorAlignSpecTitle.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticSensorAlignSpecTitle.SetFont(&m_clFontSmall);

	m_clColorStaticLensAlignSpecTitle.SetBkColor(RGB_DLG_BG);
	m_clColorStaticLensAlignSpecTitle.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticLensAlignSpecTitle.SetFont(&m_clFontSmall);


	m_clColorStaticSensorDelay.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticSensorDelay.SetFont(&m_clFontSmall);

	m_clColorStaticCcdDelayVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticCcdDelayVal.SetFont(&m_clFontSmall);
	
	m_clColorStaticSensorAlignSpecX.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticSensorAlignSpecX.SetFont(&m_clFontSmall);

	m_clColorStaticSensorAlignSpecY.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticSensorAlignSpecY.SetFont(&m_clFontSmall);

	m_clColorStaticSensorAlignSpecTh.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticSensorAlignSpecTh.SetFont(&m_clFontSmall);

	m_clColorStaticLensAlignSpecX.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticLensAlignSpecX.SetFont(&m_clFontSmall);
	m_clColorStaticLensAlignSpecY.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticLensAlignSpecY.SetFont(&m_clFontSmall);
	m_clColorStaticLensAlignSpecTh.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticLensAlignSpecTh.SetFont(&m_clFontSmall);

	m_clColorStaticLensRetry.SetBkColor(RGB_DLG_BG);
	m_clColorStaticLensRetry.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticLensRetry.SetFont(&m_clFontSmall);

	m_clColorStaticLensRetryCount.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticLensRetryCount.SetFont(&m_clFontSmall);

	m_clColorStaticLensDelay.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticLensDelay.SetFont(&m_clFontSmall);

	m_clColorStaticLaserRetry.SetBkColor(RGB_DLG_BG);
	m_clColorStaticLaserRetry.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticLaserRetry.SetFont(&m_clFontSmall);

	m_clColorStaticDiffRetry.SetBkColor(RGB_DLG_BG);
	m_clColorStaticDiffRetry.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticDiffRetry.SetFont(&m_clFontSmall);

	m_clColorStaticRawSumCount.SetBkColor(RGB_DLG_BG);
	m_clColorStaticRawSumCount.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticRawSumCount.SetFont(&m_clFontSmall);


	m_clColorStaticMaxStepCount.SetBkColor(RGB_DLG_BG);
	m_clColorStaticMaxStepCount.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticMaxStepCount.SetFont(&m_clFontSmall);

	m_clColorStaticLaserRetryCount.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticLaserRetryCount.SetFont(&m_clFontSmall);

	m_clColorStaticDiffRetryCount.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticDiffRetryCount.SetFont(&m_clFontSmall);

	m_clColorStaticMaxStepCountVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticMaxStepCountVal.SetFont(&m_clFontSmall);

	m_clColorStaticLaserDelay.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticLaserDelay.SetFont(&m_clFontSmall);

	m_clColorStaticDiffDelay.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticDiffDelay.SetFont(&m_clFontSmall);

	m_clColorStaticInLaserX.SetBkColor(RGB_DLG_BG);
	m_clColorStaticInLaserX.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticInLaserX.SetFont(&m_clFontSmall);

	m_clColorStaticInLaserXVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticInLaserXVal.SetFont(&m_clFontSmall);

	m_clColorStaticInLaserY.SetBkColor(RGB_DLG_BG);
	m_clColorStaticInLaserY.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticInLaserY.SetFont(&m_clFontSmall);

	m_clColorStaticInLaserYVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticInLaserYVal.SetFont(&m_clFontSmall);

	m_clColorStaticOutLaserX.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOutLaserX.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOutLaserX.SetFont(&m_clFontSmall);

	m_clColorStaticOutLaserXVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOutLaserXVal.SetFont(&m_clFontSmall); 

	m_clColorStaticOutLaserY.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOutLaserY.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOutLaserY.SetFont(&m_clFontSmall);

	m_clColorStaticOutLaserYVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOutLaserYVal.SetFont(&m_clFontSmall);





	m_clColorStaticOutComplLaserX.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOutComplLaserX.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOutComplLaserX.SetFont(&m_clFontSmall);

	m_clColorStaticOutComplLaserXVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOutComplLaserXVal.SetFont(&m_clFontSmall);

	m_clColorStaticOutComplLaserY.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOutComplLaserY.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOutComplLaserY.SetFont(&m_clFontSmall);

	m_clColorStaticOutComplLaserYVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticOutComplLaserYVal.SetFont(&m_clFontSmall);

	m_clColorStaticStainWhiteCount.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticStainWhiteCount.SetFont(&m_clFontSmall);

	m_clColorStaticStainBlackCount.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticStainBlackCount.SetFont(&m_clFontSmall);

	m_clColorStaticUvTime.SetBkColor(RGB_DLG_BG);
	m_clColorStaticUvTime.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticUvTime.SetFont(&m_clFontSmall);

	m_clColorStaticUvTimeVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticUvTimeVal.SetFont(&m_clFontSmall);

	m_clColorStaticEscapePcbZ.SetBkColor(RGB_DLG_BG);
	m_clColorStaticEscapePcbZ.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticEscapePcbZ.SetFont(&m_clFontSmall);

	m_clColorStaticEscapePcbZVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticEscapePcbZVal.SetFont(&m_clFontSmall);

	m_clColorStaticFpsStopVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticFpsStopVal.SetFont(&m_clFontSmall);

	m_clColorStaticJxlVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticJxlVal.SetFont(&m_clFontSmall);


	
	m_clColorStaticPinStopVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticPinStopVal.SetFont(&m_clFontSmall);

	m_clColorStaticPreUvOffsetLensX.SetBkColor(RGB_DLG_BG);
	m_clColorStaticPreUvOffsetLensX.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticPreUvOffsetLensX.SetFont(&m_clFontSmall);

	m_clColorStaticPreUvOffsetLensXVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticPreUvOffsetLensXVal.SetFont(&m_clFontSmall);

	m_clColorStaticPreUvOffsetLensY.SetBkColor(RGB_DLG_BG);
	m_clColorStaticPreUvOffsetLensY.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticPreUvOffsetLensY.SetFont(&m_clFontSmall);

	m_clColorStaticPreUvOffsetLensYVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticPreUvOffsetLensYVal.SetFont(&m_clFontSmall);

	m_clColorStaticPreUvOffsetLensZ.SetBkColor(RGB_DLG_BG);
	m_clColorStaticPreUvOffsetLensZ.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticPreUvOffsetLensZ.SetFont(&m_clFontSmall);

	m_clColorStaticPreUvOffsetLensZVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticPreUvOffsetLensZVal.SetFont(&m_clFontSmall);

	m_clColorStaticPreUvOffsetLensTx.SetBkColor(RGB_DLG_BG);
	m_clColorStaticPreUvOffsetLensTx.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticPreUvOffsetLensTx.SetFont(&m_clFontSmall);

	m_clColorStaticPreUvOffsetLensTxVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticPreUvOffsetLensTxVal.SetFont(&m_clFontSmall);

	m_clColorStaticPreUvOffsetLensTy.SetBkColor(RGB_DLG_BG);
	m_clColorStaticPreUvOffsetLensTy.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticPreUvOffsetLensTy.SetFont(&m_clFontSmall);

	m_clColorStaticPreUvOffsetLensTyVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticPreUvOffsetLensTyVal.SetFont(&m_clFontSmall);

	//
	m_clColorStaticEolPcbTx.SetBkColor(RGB_DLG_BG);
	m_clColorStaticEolPcbTx.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticEolPcbTx.SetFont(&m_clFontSmall);

	m_clColorStaticEolPcbTxVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticEolPcbTxVal.SetFont(&m_clFontSmall);

	m_clColorStaticEolPcbTy.SetBkColor(RGB_DLG_BG);
	m_clColorStaticEolPcbTy.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticEolPcbTy.SetFont(&m_clFontSmall);

	m_clColorStaticEolPcbTyVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticEolPcbTyVal.SetFont(&m_clFontSmall);
	//

	m_clColorStaticPreUvOffsetPcbTh.SetBkColor(RGB_DLG_BG);
	m_clColorStaticPreUvOffsetPcbTh.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticPreUvOffsetPcbTh.SetFont(&m_clFontSmall);

	m_clColorStaticPreUvOffsetPcbThVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticPreUvOffsetPcbThVal.SetFont(&m_clFontSmall);

	m_clColorStaticPcbVacuumDelay.SetBkColor(RGB_DLG_BG);
	m_clColorStaticPcbVacuumDelay.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticPcbVacuumDelay.SetFont(&m_clFontSmall);

	m_clColorStaticPcbVacuumDelayVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticPcbVacuumDelayVal.SetFont(&m_clFontSmall);

	m_clColorStaticPcbGripDelay.SetBkColor(RGB_DLG_BG);
	m_clColorStaticPcbGripDelay.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticPcbGripDelay.SetFont(&m_clFontSmall);

	m_clColorStaticPcbGripDelayVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticPcbGripDelayVal.SetFont(&m_clFontSmall);

	m_clColorStaticLensGripDelay.SetBkColor(RGB_DLG_BG);
	m_clColorStaticLensGripDelay.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticLensGripDelay.SetFont(&m_clFontSmall);

	m_clColorStaticLensGripDelayVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticLensGripDelayVal.SetFont(&m_clFontSmall);

	m_clColorStaticPcbGripUpDelay.SetBkColor(RGB_DLG_BG);
	m_clColorStaticPcbGripUpDelay.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticPcbGripUpDelay.SetFont(&m_clFontSmall);

	m_clColorStaticPcbGripUpDelayVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticPcbGripUpDelayVal.SetFont(&m_clFontSmall);

	m_clColorStaticLaserTimeout.SetBkColor(RGB_DLG_BG);
	m_clColorStaticLaserTimeout.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticLaserTimeout.SetFont(&m_clFontSmall);

	m_clColorStaticLaserTimeoutVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticLaserTimeoutVal.SetFont(&m_clFontSmall);

	m_clColorStaticFinalDelay.SetBkColor(RGB_DLG_BG);
	m_clColorStaticFinalDelay.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticFinalDelay.SetFont(&m_clFontSmall);

	m_clColorStaticFinalDelayVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticFinalDelayVal.SetFont(&m_clFontSmall);

	m_clColorStaticFPS.SetBkColor(RGB_DLG_BG);
	m_clColorStaticFPS.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticFPS.SetFont(&m_clFontSmall);

	m_clColorStaticJxl.SetBkColor(RGB_DLG_BG);
	m_clColorStaticJxl.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticJxl.SetFont(&m_clFontSmall);
	
	

	m_clColorStaticBondingDelay.SetBkColor(RGB_DLG_BG);
	m_clColorStaticBondingDelay.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticBondingDelay.SetFont(&m_clFontSmall);

	m_clColorStaticBondingDelayVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticBondingDelayVal.SetFont(&m_clFontSmall);

	m_clColorStaticLightPort.SetBkColor(RGB_DLG_BG);
	m_clColorStaticLightPort.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticLightPort.SetFont(&m_clFontSmall);

	m_clColorStaticLaserPort1.SetBkColor(RGB_DLG_BG);
	m_clColorStaticLaserPort1.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticLaserPort1.SetFont(&m_clFontSmall);

	m_clColorStaticOcPort1.SetBkColor(RGB_DLG_BG);
	m_clColorStaticOcPort1.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticOcPort1.SetFont(&m_clFontSmall);

	m_clColorStaticChartPort1.SetBkColor(RGB_DLG_BG);
	m_clColorStaticChartPort1.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticChartPort1.SetFont(&m_clFontSmall);

	m_clColorStaticLeftChartPort.SetBkColor(RGB_DLG_BG);
	m_clColorStaticLeftChartPort.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticLeftChartPort.SetFont(&m_clFontSmall);

	m_clColorStaticRightChartPort.SetBkColor(RGB_DLG_BG);
	m_clColorStaticRightChartPort.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticRightChartPort.SetFont(&m_clFontSmall);

	


	m_clColorStaticBcrPort.SetBkColor(RGB_DLG_BG);
	m_clColorStaticBcrPort.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticBcrPort.SetFont(&m_clFontSmall);

	m_clComboChartLightPort1.SetFont(&m_clFontSmall);
	m_clComboLeftChartLightPort.SetFont(&m_clFontSmall);
	m_clComboRightChartLightPort.SetFont(&m_clFontSmall);
	m_clComboEziModule.SetFont(&m_clFontSmall);
	m_clComboAlignLightPort1.SetFont(&m_clFontSmall);
	m_clComboLaser1.SetFont(&m_clFontSmall);
	m_clComboBcrPort.SetFont(&m_clFontSmall);
	m_clComboUvPort.SetFont(&m_clFontSmall);
	
	m_clColorStaticMesFactory.SetBkColor(RGB_DLG_BG);
	m_clColorStaticMesFactory.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticMesFactory.SetFont(&m_clFontSmall);

	m_clColorStaticMesFactoryVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticMesFactoryVal.SetFont(&m_clFontSmall);

	m_clColorStaticDelDay.SetBkColor(RGB_DLG_BG);
	m_clColorStaticDelDay.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticDelDay.SetFont(&m_clFontSmall);

	m_clColorStaticDelDayVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticDelDayVal.SetFont(&m_clFontSmall);


	m_clColorStaticMesFactoryCompl.SetBkColor(RGB_DLG_BG);
	m_clColorStaticMesFactoryCompl.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticMesFactoryCompl.SetFont(&m_clFontSmall);
	m_clColorStaticMesFactoryComplVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticMesFactoryComplVal.SetFont(&m_clFontSmall);


	
	m_clColorStaticPinCount.SetBkColor(RGB_DLG_BG);
	m_clColorStaticPinCount.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticPinCount.SetFont(&m_clFontSmall);

	m_clColorStaticMainIp.SetBkColor(RGB_DLG_BG);
	m_clColorStaticMainIp.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticMainIp.SetFont(&m_clFontSmall);

	m_clColorStaticMainIpVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticMainIpVal.SetFont(&m_clFontSmall);

	m_clColorStaticMainPort.SetBkColor(RGB_DLG_BG);
	m_clColorStaticMainPort.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticMainPort.SetFont(&m_clFontSmall);

	m_clColorStaticMainPortVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticMainPortVal.SetFont(&m_clFontSmall);

	m_clColorStaticMesPort.SetBkColor(RGB_DLG_BG);
	m_clColorStaticMesPort.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticMesPort.SetFont(&m_clFontSmall);

	m_clColorStaticMesPortVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticMesPortVal.SetFont(&m_clFontSmall);

	m_clColorStaticMesIp.SetBkColor(RGB_DLG_BG);
	m_clColorStaticMesIp.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticMesIp.SetFont(&m_clFontSmall);

	m_clColorStaticMesIpVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticMesIpVal.SetFont(&m_clFontSmall);
	
	m_clColorStaticInspIp.SetBkColor(RGB_DLG_BG);
	m_clColorStaticInspIp.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticInspIp.SetFont(&m_clFontSmall);
				   
	m_clColorStaticInspIpVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticInspIpVal.SetFont(&m_clFontSmall);

	m_clColorStaticInspPort.SetBkColor(RGB_DLG_BG);
	m_clColorStaticInspPort.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticInspPort.SetFont(&m_clFontSmall);
				 
	m_clColorStaticInspPortVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticInspPortVal.SetFont(&m_clFontSmall);


	m_clColorStaticStainLcb.SetBkColor(RGB_DLG_BG);
	m_clColorStaticStainLcb.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticStainLcb.SetFont(&m_clFontSmall);

	m_clColorStaticStainLcbCenter.SetBkColor(RGB_DLG_BG);
	m_clColorStaticStainLcbCenter.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticStainLcbCenter.SetFont(&m_clFontSmall);

	m_clColorStaticStinLcbCorner.SetBkColor(RGB_DLG_BG);
	m_clColorStaticStinLcbCorner.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticStinLcbCorner.SetFont(&m_clFontSmall);

	m_clColorStaticStainLcbEdge.SetBkColor(RGB_DLG_BG);
	m_clColorStaticStainLcbEdge.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticStainLcbEdge.SetFont(&m_clFontSmall);

	m_clColorStaticStainLcbCenterVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticStainLcbCenterVal.SetFont(&m_clFontSmall);

	m_clColorStaticStinLcbCornerVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticStinLcbCornerVal.SetFont(&m_clFontSmall);

	m_clColorStaticStainLcbEdgeVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticStainLcbEdgeVal.SetFont(&m_clFontSmall);

	m_clColorStaticStainYMean.SetBkColor(RGB_DLG_BG);
	m_clColorStaticStainYMean.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticStainYMean.SetFont(&m_clFontSmall);

	m_clColorStaticStainYMeanCenter.SetBkColor(RGB_DLG_BG);
	m_clColorStaticStainYMeanCenter.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticStainYMeanCenter.SetFont(&m_clFontSmall);

	m_clColorStaticStinYMeanCorner.SetBkColor(RGB_DLG_BG);
	m_clColorStaticStinYMeanCorner.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticStinYMeanCorner.SetFont(&m_clFontSmall);

	m_clColorStaticStainYMeanEdge.SetBkColor(RGB_DLG_BG);
	m_clColorStaticStainYMeanEdge.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticStainYMeanEdge.SetFont(&m_clFontSmall);

	m_clColorStaticStainYMeanCenterVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticStainYMeanCenterVal.SetFont(&m_clFontSmall);

	m_clColorStaticStinYMeanCornerVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticStinYMeanCornerVal.SetFont(&m_clFontSmall);

	m_clColorStaticStainYMeanEdgeVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticStainYMeanEdgeVal.SetFont(&m_clFontSmall);

	m_clColorStaticMarkNo.SetBkColor(RGB_DLG_BG);
	m_clColorStaticMarkNo.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticMarkNo.SetFont(&m_clFontSmall);

	m_clColorStaticMarkNoVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticMarkNoVal.SetFont(&m_clFontSmall);

	m_clColorStaticMatching.SetBkColor(RGB_DLG_BG);
	m_clColorStaticMatching.SetTextColor(RGB_COLOR_WHITE);
	m_clColorStaticMatching.SetFont(&m_clFontSmall);

	m_clColorStaticMatchingVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticMatchingVal.SetFont(&m_clFontSmall);

	m_clColorButtonVerView.state = 3;
	//총 24개
	m_ComboDemosaic.ResetContent();
	m_ComboDemosaic.AddString(_T("DEMOSAIC_NONE"));
	m_ComboDemosaic.AddString(_T("GRADIENT"));
	m_ComboDemosaic.AddString(_T("BL33"));
	m_ComboDemosaic.AddString(_T("OPENCV_VNG"));
	m_ComboDemosaic.AddString(_T("VNG"));
	m_ComboDemosaic.AddString(_T("GR_ONLY"));
	m_ComboDemosaic.AddString(_T("GB_ONLY"));
	m_ComboDemosaic.AddString(_T("GBTF"));
	m_ComboDemosaic.AddString(_T("BLLC"));
	m_ComboDemosaic.AddString(_T("RESIDUAL"));
	m_ComboDemosaic.AddString(_T("BAYER_Y"));
	m_ComboDemosaic.AddString(_T("GRADIENT_RESIDUAL"));
	m_ComboDemosaic.AddString(_T("GBTF_RESIDUAL"));
	m_ComboDemosaic.AddString(_T("RESIDUAL_RESIDUAL"));
	m_ComboDemosaic.AddString(_T("BL33_RESIDUAL"));
	m_ComboDemosaic.AddString(_T("IR_ONLY"));
	m_ComboDemosaic.AddString(_T("GRADIENT_G_ONLY"));
	m_ComboDemosaic.AddString(_T("GBTF_G_ONLY"));
	m_ComboDemosaic.AddString(_T("RESIDUAL_G_ONLY"));
	m_ComboDemosaic.AddString(_T("BL33_G_ONLY"));
	m_ComboDemosaic.AddString(_T("GRADIENT_IR_ONLY"));
	m_ComboDemosaic.AddString(_T("GBTF_IR_ONLY"));
	m_ComboDemosaic.AddString(_T("RESIDUAL_IR_ONLY"));
	m_ComboDemosaic.AddString(_T("BL33_IR_ONLY"));

	m_ComboDemosaic.SetCurSel(0);

	GetDlgItem(IDC_STATIC_CONFIG_OC_PORT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_CONFIG_EZI_PORT)->ShowWindow(SW_HIDE);

	//
	this->HideMtfOffset(true);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CConfigDlg::SetUnit(int nUnit)
{
	TCHAR szTitle[SIZE_OF_100BYTE];

	m_nUnit = nUnit;
	_stprintf_s(szTitle, SIZE_OF_100BYTE, _T("[CONFIG]")); //, m_nUnit + 1);
	GetDlgItem(IDC_STATIC_CONFIG_TITLE)->SetWindowText(szTitle);

	this->ShowData();
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CConfigDlg::HideMtfOffset(bool bHide)
{
	if (bHide == true)
	{
		//m_clColorStaticMtfOffset.ShowWindow(SW_HIDE);
		//m_clColorStaticMtfOffsetVal.ShowWindow(SW_HIDE);

		m_clColorStaticStainWhiteCount.ShowWindow(SW_HIDE);
		m_clColorStaticStainBlackCount.ShowWindow(SW_HIDE);
	}
	else
	{
		//m_clColorStaticMtfOffset.ShowWindow(SW_SHOW);
		//m_clColorStaticMtfOffsetVal.ShowWindow(SW_SHOW);

		m_clColorStaticStainWhiteCount.ShowWindow(SW_SHOW);
		m_clColorStaticStainBlackCount.ShowWindow(SW_SHOW);
	}	
}

//-----------------------------------------------------------------------------
//
// STATIC : SFR 검사 영역 - 단변
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigSfrXSizeVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticSfrXSizeVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticSfrXSizeVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : SFR 검사 영역 - 장변
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigSfrYSizeVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticSfrYSizeVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticSfrYSizeVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : SFR 검사 영역 - CELL SIZE
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigCcdCellSizeVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticCcdCellSizeVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticCcdCellSizeVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : MTF OFFSET
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigMtfOffsetVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticCircleVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			double dTemp = pDlg->GetReturnVal();
			if (dTemp < 0.0)
			{
				dTemp = 0.0;
			}
			if (dTemp > 255.0)
			{
				dTemp = 255.0;
			}
			sData.Format(_T("%.01lf"), dTemp);
			m_clColorStaticCircleVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : ROUGH 이동 속도
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigMoveVelRough()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticMoveVelRough.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticMoveVelRough.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : FINE 이동속도
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigMoveVelFine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticMoveVelFine.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticMoveVelFine.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	STATIC : ROUCH 가감속
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigMoveAccRough()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticMoveAccRough.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticMoveAccRough.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	STATIC : FINE 가감속
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigMoveAccFine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticMoveAccFine.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticMoveAccFine.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : ROUGH DELAY
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigDelayRough()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticDelayRough.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticDelayRough.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : FINE DELAY
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigDelayFine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticDelayFine.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticDelayFine.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	STATIC : ROUGH 이동거리
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigMoveDistanceRough()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticMoveDistanceRough.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticMoveDistanceRough.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	STATIC : FINE 이동거리
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigMoveDistanceFine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticMoveDistanceFine.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticMoveDistanceFine.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : ROUGH SFR 평균 횟수
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigSfrAvgCountRough()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticSfrAvgCountRough.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticSfrAvgCountRough.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : FINE SFR 평균 횟수
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigSfrAvgCountFine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticSfrAvgCountFine.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticSfrAvgCountFine.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : 2차 AA 시작지점 이동 거리
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigSecondAaMoveDistanceFine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStatic2ndAAMoveDistanceFine.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStatic2ndAAMoveDistanceFine.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	STATIC : ROUGH OK LIMIT
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigOkLimitRough()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticOkLimitRough.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticOkLimitRough.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : FINE OK LIMIT
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigOkLimitFine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticOkLimitFine.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticOkLimitFine.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : FINE MOVE 전환
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigFineMoveChangeRough()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticFineMoveChangeRough.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticFineMoveChangeRough.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : SFR 감소시 체크 데이터 수
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigCheckDataCountVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticCheckDataCountVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticCheckDataCountVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : SFR 감소시 이동 거리
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigSfrMoveDistanceVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticSfrMoveDistanceVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticSfrMoveDistanceVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : SENSOR ALIGN RETRY COUNT
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigSensorAlignRetryCount()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticSensorRetryCount.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticSensorRetryCount.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : SENSOR ALIGN DELAY
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigSensorAlignDelay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticSensorDelay.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticSensorDelay.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : LASER ALIGN RETRY COUNT
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigLaserRetryCount()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticLaserRetryCount.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticLaserRetryCount.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : LASER DELAY
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigLaserDelay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticLaserDelay.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticLaserDelay.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : 내부 변위센서 X거리
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigInLaserXVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticInLaserXVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticInLaserXVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : 내부 변위센서 Y거리
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigInLaserYVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticInLaserYVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticInLaserYVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	STATIC : 외부 변위센서 X거리
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigOutLaserXVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticOutLaserXVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticOutLaserXVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : 외부 변위센서 Y거리
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigOutLaserYVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticOutLaserYVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticOutLaserYVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//	STATIC : STAIN WHITE COUNT
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigStainWhiteCount()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticStainWhiteCount.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticStainWhiteCount.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : STAIN BLACK COUNT
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigStainBlackCount()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticStainBlackCount.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticStainBlackCount.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : UV TIME
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigUvTimeVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticUvTimeVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticUvTimeVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : PCB Z 회피 위치
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigPcbZEscapePosVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticEscapePcbZVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticEscapePcbZVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : FPS STOP VAL
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigFpsStopVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");
	double dRetVal;

	m_clColorStaticFpsStopVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			dRetVal = pDlg->GetReturnVal();
			if (dRetVal >= 0.0 && dRetVal <= 30.0)
			{
				sData.Format(_T("%.03lf"), dRetVal);
				m_clColorStaticFpsStopVal.SetWindowText(sData);
			}
			else
			{
				AddLog(_T("[INFO] 0 ~ 30 사이 값만 입력하세요"), 1, m_nUnit);
			}
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : 포고핀 STOP VAL
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigPinStopVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");
	int nRetVal;

	m_clColorStaticPinStopVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			nRetVal = (int)pDlg->GetReturnVal();

			sData.Format(_T("%d"), nRetVal);
			m_clColorStaticPinStopVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : UV OFFSET LENS X
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigPreUvOffsetLensXVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticPreUvOffsetLensXVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticPreUvOffsetLensXVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : UV OFFSET LENS Y
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigPreUvOffsetLensYVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticPreUvOffsetLensYVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticPreUvOffsetLensYVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : UV OFFSET LENS Z
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigPreUvOffsetLensZVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticPreUvOffsetLensZVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticPreUvOffsetLensZVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : UV OFFSET LENS TX
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigPreUvOffsetLensTxVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticPreUvOffsetLensTxVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticPreUvOffsetLensTxVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : UV OFFSET LENS TY
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigPreUvOffsetLensTyVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticPreUvOffsetLensTyVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticPreUvOffsetLensTyVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : UV OFFSET PCB TH
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigPreUvOffsetPcbThVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticPreUvOffsetPcbThVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticPreUvOffsetPcbThVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : PCB VACUUM DELAY
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigPcbVacuumDelayVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticPcbVacuumDelayVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.01lf"), pDlg->GetReturnVal());
			m_clColorStaticPcbVacuumDelayVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}


//-----------------------------------------------------------------------------
//
// STATIC : PCB GRIP DELAY
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigPcbGripDelayVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticPcbGripDelayVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.01lf"), pDlg->GetReturnVal());
			m_clColorStaticPcbGripDelayVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : LENS GRIP DELAY
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigPcbUpDownDelayVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticPcbGripUpDelayVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.01lf"), pDlg->GetReturnVal());
			m_clColorStaticPcbGripUpDelayVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : LASER 통신 TIMEOUT
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigLaserTimeoutVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticLaserTimeoutVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.01lf"), pDlg->GetReturnVal());
			m_clColorStaticLaserTimeoutVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : FINAL DELAY
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigFinalDelayVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");
	
	m_clColorStaticFinalDelayVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.01lf"), pDlg->GetReturnVal());
			m_clColorStaticFinalDelayVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : 본딩 전 DELAY
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigBondingDelayVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticBondingDelayVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.01lf"), pDlg->GetReturnVal());
			m_clColorStaticBondingDelayVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : MAIN PC IP
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigMainIpVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CKeyBoardDlg* pDlg = new CKeyBoardDlg(20, false);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			m_clColorStaticMainIpVal.SetWindowText(pDlg->GetReturnValue());
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : MAIN PC PORT
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigMainPortVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticMainPortVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticMainPortVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : 화상검사기 PC IP
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigInspIpVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CKeyBoardDlg* pDlg = new CKeyBoardDlg(20, false);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			m_clColorStaticInspIpVal.SetWindowText(pDlg->GetReturnValue());
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// STATIC : 화상검사기 PC PORT
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigInspPortVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticInspPortVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticInspPortVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// 버튼 : 센서 구동 파일 열기
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnBnClickedButtonConfigIniFind()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog* pDlg = new CFileDialog(TRUE, NULL, NULL, OFN_EXPLORER | OFN_HIDEREADONLY, _T("센서구동 파일(*.ini) | *.ini||"));
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			GetDlgItem(IDC_EDIT_CONFIG_INI_FILE_PATH)->SetWindowText(pDlg->GetPathName());
		}

		delete pDlg;
	}
}



//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigStainLcbCenterVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticStainLcbCenterVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticStainLcbCenterVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigStainLcbCornerVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticStinLcbCornerVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticStinLcbCornerVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigStainLcbEdgeVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticStainLcbEdgeVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticStainLcbEdgeVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigStainYmeanCenterVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticStainYMeanCenterVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticStainYMeanCenterVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigStainYmeanCornerVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticStinYMeanCornerVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticStinYMeanCornerVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigStainYmeanEdgeVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticStainYMeanEdgeVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticStainYMeanEdgeVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigMarkNoVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticMarkNoVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticMarkNoVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnStnClickedStaticConfigMarkMatchingVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticMatchingVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticMatchingVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}

//-----------------------------------------------------------------------------
//
// 버튼 : SAVE
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnBnClickedButtonConfigSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	CKeyBoardDlg* pDlg = new CKeyBoardDlg(20, true);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			if (_tcscmp(g_clSysData.m_szPassword, (TCHAR*)(LPCTSTR)pDlg->GetReturnValue()))
			{
				AddLog(_T("비밀번호가 일치하지 않습니다."), 1, m_nUnit);
				delete pDlg;

				return;
			}
		}
		else
		{
			delete pDlg;
			return;
		}

		delete pDlg;
	}

	if (g_ShowMsgModal(_T("확인"), _T("데이터를 저장하시겠습니까?"), RGB_COLOR_RED) == false) 
	{
		return;
	}
	this->GetData();

	g_clSysData.sDSave();
	g_clSysData.commonDataSave();
	g_clSysData.commonDataLoad();

	g_clModelData[m_nUnit].Save(g_clSysData.m_szModelName);
	g_clModelData[m_nUnit].Load(g_clSysData.m_szModelName);


	ShowData();

	AddLog(_T("[INFO] 환경설정 저장"), 0, m_nUnit);

	
}

//-----------------------------------------------------------------------------
//
// OnShowWindow
//
//-----------------------------------------------------------------------------
void CConfigDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
		this->ShowData();
	}
}
void CConfigDlg::PopupShow()
{
	TCHAR szLog[SIZE_OF_1K];

	if (g_clModelData[UNIT_AA1].m_nInspOKPass == 1 && g_clModelData[UNIT_AA1].m_nMasterModeUse == 1)
	{
		//_stprintf_s(szLog, SIZE_OF_1K, _T("운전 MODE 확인 바랍니다."));
		_stprintf_s(szLog, SIZE_OF_1K, _T("EOL PASS /  MASTER MODE 입니다."));
		InterLockMsg(_T("주의"), szLog, MESSAGE_BG_COLOR, true);
	}
	else if (g_clModelData[UNIT_AA1].m_nMasterModeUse == 1)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("MASTER MODE 입니다."));
		InterLockMsg(_T("주의"), szLog, MESSAGE_BG_COLOR, true);
	}
	else
	{
		InterLockMsg(_T("주의"), szLog, MESSAGE_BG_COLOR, false);
	}
	//
	//
}

//-----------------------------------------------------------------------------
//
// 모델 데이터 표시
//
//-----------------------------------------------------------------------------
void CConfigDlg::ShowData()
{
	TCHAR szData[SIZE_OF_100BYTE];
	CButton* pButton;

	// 단변
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nRoiSizeX);
	m_clColorStaticSfrXSizeVal.SetWindowText(szData);
	// 장변
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nRoiSizeY);
	m_clColorStaticSfrYSizeVal.SetWindowText(szData);
	// CCD Cell Size
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dCcdCellSize);
	m_clColorStaticCcdCellSizeVal.SetWindowText(szData);
    //Line pulse
    _stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dLinePulse);
    m_clColorStaticCcdLinePulseVal.SetWindowText(szData);
    
	//BlackLevel
	//_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_dSfrBlackLevel);
	//m_clColorStaticCcdBlackLevelVal.SetWindowText(szData);

	//ccd delay
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.1lf"), g_clModelData[m_nUnit].m_dCcdDelay);
	m_clColorStaticCcdDelayVal.SetWindowText(szData);
	
	//Demosaic
	//m_ComboDemosaic.SetCurSel(g_clModelData[m_nUnit].m_dDemosaic);
	//


	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_CCD_FLIP_USE);
	if (g_clModelData[m_nUnit].m_nCcdFlipUse == 0)
	{
		pButton->SetCheck(0);
	}
	else
	{
		pButton->SetCheck(1);
	}

	// MTF Offset
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.01lf"), g_clModelData[m_nUnit].m_dCircleThresh);
	m_clColorStaticCircleVal.SetWindowText(szData);

	// ROUGH
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_stAFInfo[0].dMoveVel);
	m_clColorStaticMoveVelRough.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_stAFInfo[0].dMoveAcc);
	m_clColorStaticMoveAccRough.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_stAFInfo[0].nDelayTime);
	m_clColorStaticDelayRough.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_stAFInfo[0].dMoveDistance);
	m_clColorStaticMoveDistanceRough.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_stAFInfo[0].nAvgSfrCount);
	m_clColorStaticSfrAvgCountRough.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dLimitSFRCent);
	m_clColorStaticOkLimitRough.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_stAFInfo[0].fLimitRoughMTF);
	m_clColorStaticFineMoveChangeRough.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_stAFInfo[0].fLimitFineMTF);
	m_clColorStaticFineMoveChangeFine.SetWindowText(szData);

	
	
	//FINE
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_stAFInfo[1].dMoveVel);
	m_clColorStaticMoveVelFine.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_stAFInfo[1].dMoveAcc);
	m_clColorStaticMoveAccFine.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_stAFInfo[1].nDelayTime);
	m_clColorStaticDelayFine.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_stAFInfo[1].dMoveDistance);
	m_clColorStaticMoveDistanceFine.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_stAFInfo[1].nAvgSfrCount);
	m_clColorStaticSfrAvgCountFine.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_d2ndAAMoveDistance);
	m_clColorStatic2ndAAMoveDistanceFine.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dLimitSFRSide);
	m_clColorStaticOkLimitFine.SetWindowText(szData);

	// SFR값 연속 감소시 동작
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nCountOfCheckSFR);
	m_clColorStaticCheckDataCountVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dSfrMoveDistance);
	m_clColorStaticSfrMoveDistanceVal.SetWindowText(szData);

	// MODE
	m_clComboField.SetCurSel(g_clModelData[m_nUnit].m_nSfrMode);
	m_clComboPosition.SetCurSel(g_clModelData[m_nUnit].m_nSFR_N_POS);

	// LASER SIZE
	/*_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dLaserMoveX[0]);
	m_clColorStaticInLaserXVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dLaserMoveY[0]);
	m_clColorStaticInLaserYVal.SetWindowText(szData);*/
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dLaserMoveX[0]);
	m_clColorStaticOutLaserXVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dLaserMoveY[0]);
	m_clColorStaticOutLaserYVal.SetWindowText(szData);


	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dLaserComplMoveX[0]);
	m_clColorStaticOutComplLaserXVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dLaserComplMoveY[0]);
	m_clColorStaticOutComplLaserYVal.SetWindowText(szData);

	// STAIN 불량 COUNT
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nStainCount[0]);
	m_clColorStaticStainWhiteCount.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nStainCount[1]);
	m_clColorStaticStainBlackCount.SetWindowText(szData);

	// UV TIME
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_dUvTime);
	m_clColorStaticUvTimeVal.SetWindowText(szData);

	// PCB Z 회피위치
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dEscapePosPcbZ);
	m_clColorStaticEscapePcbZVal.SetWindowText(szData);

	// RETRY / DELAY
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nSensorAlignRetryCount);
	m_clColorStaticSensorRetryCount.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nCcdRetryCount);
	m_clColorStaticCcdRetryCount.SetWindowText(szData);
	

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nLensAlignRetryCount);
	m_clColorStaticLensRetryCount.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nLaserRetryCount);
	m_clColorStaticLaserRetryCount.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nDiffRetryCount);
	m_clColorStaticDiffRetryCount.SetWindowText(szData);

	//contact
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nContactRetryCount);
	m_clColorStaticContactRetryCount.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.01lf"), g_clModelData[m_nUnit].m_nContactRetryDelay);
	m_clColorStaticContactRetryDelay.SetWindowText(szData);


	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nRawSumCount);
	m_clColorStaticRawSumCountVal.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_stAFInfo[0].nMaxStepCount);
	m_clColorStaticMaxStepCountVal.SetWindowText(szData);


	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.01lf"), g_clModelData[m_nUnit].m_dSensorAlignDelay);
	m_clColorStaticSensorDelay.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.01lf"), g_clModelData[m_nUnit].m_dLensAlignDelay);
	m_clColorStaticLensDelay.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.01lf"), g_clModelData[m_nUnit].m_dLaserDelay);
	m_clColorStaticLaserDelay.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.01lf"), g_clModelData[m_nUnit].m_dDiffDelay);
	m_clColorStaticDiffDelay.SetWindowText(szData);

	//Oc Align Spec Put
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dOcAlignSpec[0]);
	m_clColorStaticOcAlignSpecXVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dOcAlignSpec[1]);
	m_clColorStaticOcAlignSpecYVal.SetWindowText(szData);

	//Align Spec Put
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dSensorAlignSpec[0]);
	m_clColorStaticSensorAlignSpecX.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dSensorAlignSpec[1]);
	m_clColorStaticSensorAlignSpecY.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dSensorAlignSpec[2]);
	m_clColorStaticSensorAlignSpecTh.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dLensAlignSpec[0]);
	m_clColorStaticLensAlignSpecX.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dLensAlignSpec[1]);
	m_clColorStaticLensAlignSpecY.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dLensAlignSpec[2]);
	m_clColorStaticLensAlignSpecTh.SetWindowText(szData);
	
	// 공운전
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_DRY_RUN_USE);
	if (g_clModelData[m_nUnit].m_nDryRunMode == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	//BCR PASS
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_MES_PASS);
	if (g_clModelData[m_nUnit].m_nMesPass == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	// 포고핀 STOP 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_PIN_STOP_USE);
	if (g_clModelData[m_nUnit].m_nPinStopUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);
	//MASTER MODE
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_MASTER_MODE);
	if (g_clModelData[m_nUnit].m_nMasterModeUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);
	//INSP PASS (양품 판정)IDC_CHECK_CONFIG_INSP_PASS
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_INSP_PASS);
	if (g_clModelData[m_nUnit].m_nInspOKPass == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	//ALIGN 보정
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_ALIGN_PASS);
	if (g_clModelData[m_nUnit].m_nAlignPass == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	//RAW SAVE PASS
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_RAW_SAVE_PASS);
	if (g_clModelData[m_nUnit].m_nRawSavePass == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	//JXL SAVE PASS
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_JXL_SAVE_PASS);
	if (g_clModelData[m_nUnit].m_nJxlSavePass == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);
	
	//IDLE REASON REPORT
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_IDLE_REPORT_PASS);
	if (g_clModelData[m_nUnit].m_nIdleReasonPass == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);
	

	// STAIN 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_STAIN_INSP_USE);
	if (g_clModelData[m_nUnit].m_nStainInspUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	// DEFECT 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_DEFECT_INSP_USE);
	if (g_clModelData[m_nUnit].m_nCcdDefectInfpUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);


	// RI 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_RI_INSP_USE);
	if (g_clModelData[m_nUnit].m_nRITestUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);


	// CURRENT 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_CURRENT_USE);
	if (g_clModelData[m_nUnit].m_nCurrentUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);


	// LASER 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_LASER_OUT_USE);
	if (g_clModelData[m_nUnit].m_nLaserOutUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);






	// UV 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_UV_USE);
	if (g_clModelData[m_nUnit].m_nUvUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	// 내부 LASER 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_LASER_IN_USE);
	if (g_clModelData[m_nUnit].m_nLaserInUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	
	// 1차 AA후 배출 기능
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_UNLOAD_AFTER_1ST_AA_USE);
	if (g_clModelData[m_nUnit].m_nUnloadAfter1stAAUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	


	// SATURATION 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_SATURATION_INSP_USE);
	if (g_clModelData[m_nUnit].m_nSaturationInspUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	// IF FILTER 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_IRFILTER_INSP_USE);
	if (g_clModelData[m_nUnit].m_nIRFilterInspUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	// COLOR REPRODUCTION 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_COLOR_REPRODUCTION_INSP_USE);
	if (g_clModelData[m_nUnit].m_nColorReproductionInspUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	//NG 이미지만 SAVE
	//
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_NG_IMAGE_SAVE);
	if (g_clModelData[m_nUnit].m_nNgImageSaveUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	// DARK 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_DARK_INSP_USE);
	if (g_clModelData[m_nUnit].m_nDarkInspUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);
	

	
	
	

	// DOOR LOCK 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_DOORLOCK_USE);
	if (g_clModelData[m_nUnit].m_nDoorLockUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	// EPOXY PASS
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_EPOXY_USE);
	if (g_clModelData[m_nUnit].m_nEpoxyPass == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	// EPOXY INSP PASS
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_EPOXY_INSP_USE);
	if (g_clModelData[m_nUnit].m_nEpoxyInspPass == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);


	//SFR 평균으로 스펙 체크
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_SFR_AVERAGE);
	if (g_clModelData[m_nUnit].m_nSfrAvrCheck == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	
	// FPS STOP 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_FPS_STOP_USE);
	if (g_clModelData[m_nUnit].m_nFpsStopUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	// 공용차트 사용 모드 (패턴)
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_COMPL_MODE);
	if (g_clModelData[m_nUnit].m_nPatternChartUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);






	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.01f"), g_clModelData[m_nUnit].m_fFpsStopVal);
	m_clColorStaticFpsStopVal.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nJxlEffort);
	m_clColorStaticJxlVal.SetWindowText(szData);


	
	
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clSysData.m_nMaxPinCount);
	m_clColorStaticPinStopVal.SetWindowText(szData);

	// LASER CONTROL LOCK
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_LASER_LOCK);
	if (g_clModelData[m_nUnit].m_nLaserControlLock == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	// DOME CHART 사용유무
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_DOME_CHART_USE);
	if (g_clModelData[m_nUnit].m_nDomeChartUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	// UV LAMP 교체 알람 사용유무
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_UV_LAMP_ALARM_USE);
	if (g_clModelData[m_nUnit].m_nUVLampAlarmUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	// AA, 검사 PASS
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_AA_PASS);
	if (g_clModelData[m_nUnit].m_nAAPass == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	// 검사 PASS
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_INSPECTION_PASS);
	if (g_clModelData[m_nUnit].m_nInspectionPass == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	// UV 경화 전 OFFSET
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dOffsetPrevUV_X);
	m_clColorStaticPreUvOffsetLensXVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dOffsetPrevUV_Y);
	m_clColorStaticPreUvOffsetLensYVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dOffsetPrevUV_Z);
	m_clColorStaticPreUvOffsetLensZVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dOffsetPrevUV_Tx);
	m_clColorStaticPreUvOffsetLensTxVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dOffsetPrevUV_Ty);
	m_clColorStaticPreUvOffsetLensTyVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dOffsetPrevUV_Th);
	m_clColorStaticPreUvOffsetPcbThVal.SetWindowText(szData);
	//
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dEolPcbOffset_Tx);
	m_clColorStaticEolPcbTxVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dEolPcbOffset_Ty);
	m_clColorStaticEolPcbTyVal.SetWindowText(szData);
	//
	// DELAY
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.01lf"), g_clModelData[m_nUnit].m_dPCBVacuumDelay);
	m_clColorStaticPcbVacuumDelayVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.01lf"), g_clModelData[m_nUnit].m_dPCBGripDelay);
	m_clColorStaticPcbGripDelayVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.01lf"), g_clModelData[m_nUnit].m_dPCBGripUpDelay);
	m_clColorStaticPcbGripUpDelayVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.01lf"), g_clModelData[m_nUnit].m_dLaserTimeOut);
	m_clColorStaticLaserTimeoutVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.01lf"), g_clModelData[m_nUnit].m_dFinalDelay);
	m_clColorStaticFinalDelayVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.01lf"), g_clModelData[m_nUnit].m_dBondingDelay);
	m_clColorStaticBondingDelayVal.SetWindowText(szData);

	//_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.01lf"), g_clModelData[m_nUnit].m_dLENSGripDelay);
	//m_clColorStaticLensGripDelayVal.SetWindowText(szData);

	// RS232
	m_clComboChartLightPort1.SetCurSel(g_clSysData.m_nTopLightPort[m_nUnit] - 1);
	m_clComboAlignLightPort1.SetCurSel(g_clSysData.m_nAlign_Oc_Port[m_nUnit] - 1);
	m_clComboEziModule.SetCurSel(g_clSysData.m_nEzi_Port[m_nUnit] - 1);
	m_clComboUvPort.SetCurSel(g_clSysData.m_nUvPort[m_nUnit] - 1);
	//

///	m_clComboAlignLightPort1.SetCurSel(g_clSysData.m_nOC_IRPort[m_nUnit] - 1);

	m_clComboLaser1.SetCurSel(g_clSysData.m_nLaserPort[m_nUnit] - 1);
	m_clComboBcrPort.SetCurSel(g_clSysData.m_nBcrPort[m_nUnit] - 1);
	m_clComboLeftChartLightPort.SetCurSel(g_clSysData.m_nLeftLightPort[m_nUnit] - 1);
	m_clComboRightChartLightPort.SetCurSel(g_clSysData.m_nRightLightPort[m_nUnit] - 1);
	//m_clComboDomeLightPort.SetCurSel(g_clSysData.m_nDomeLightPort[m_nUnit] - 1);
	//m_clComboTopLight2.SetCurSel(g_clSysData.m_nTopLightPort[1] - 1);
	//m_clComboOcLight2.SetCurSel(g_clSysData.m_nOCPort[1] - 1);

	//MES
	m_clColorStaticMesFactoryVal.SetWindowText(g_clSysData.m_szFactoryCd);
	m_clColorStaticMesFactoryComplVal.SetWindowText(g_clSysData.m_szFactoryComplCd);


	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clSysData.m_nMesPort);
	m_clColorStaticMesPortVal.SetWindowText(szData);
	m_clColorStaticMesIpVal.SetWindowText(g_clSysData.m_szMesIp);


	//FILE DELETE
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clSysData.m_nFileDeleteDay);
	m_clColorStaticDelDayVal.SetWindowText(szData);
	

	// MAIN PC
	m_clColorStaticMainIpVal.SetWindowText(g_clSysData.m_szAAIp);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clSysData.m_nAAPort);
	m_clColorStaticMainPortVal.SetWindowText(szData);

	// 화상검사기 PC
	m_clColorStaticInspIpVal.SetWindowText(g_clSysData.m_szInspIp);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clSysData.m_nInspPort);
	m_clColorStaticInspPortVal.SetWindowText(szData);

	// 센서 구동 파일
	GetDlgItem(IDC_EDIT_CONFIG_INI_FILE_PATH)->SetWindowText(g_clModelData[m_nUnit].m_szIniPath);

	// MES LOG DATA 저장 경로

	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_SFR_OVERLAY_USE);
	if(g_clModelData[m_nUnit].m_nMtfOverlayUse == 1)
		pButton->SetCheck(1);
	else
		pButton->SetCheck(0);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dStainLsbCenter);
	m_clColorStaticStainLcbCenterVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dStainLsbCorner);
	m_clColorStaticStinLcbCornerVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dStainLsbEdge);
	m_clColorStaticStainLcbEdgeVal.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dStainYMeanCenter);
	m_clColorStaticStainYMeanCenterVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dStainYMeanCorner);
	m_clColorStaticStinYMeanCornerVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clModelData[m_nUnit].m_dStainYMeanEdge);
	m_clColorStaticStainYMeanEdgeVal.SetWindowText(szData);

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nMarkNo + 1);
	m_clColorStaticMarkNoVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].m_nMinMatching);
	m_clColorStaticMatchingVal.SetWindowText(szData);


}

//-----------------------------------------------------------------------------
//
// 설정 데이터 메모리에 저장
//
//-----------------------------------------------------------------------------
void CConfigDlg::GetData()
{
	CString sData = _T("");
	CButton* pButton;

	// 단변	
	m_clColorStaticSfrXSizeVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_nRoiSizeX = _ttoi((TCHAR*)(LPCTSTR)sData);
	// 장변	
	m_clColorStaticSfrYSizeVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_nRoiSizeY = _ttoi((TCHAR*)(LPCTSTR)sData);
	// CCD Cell Size	
	m_clColorStaticCcdCellSizeVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dCcdCellSize = _ttof((TCHAR*)(LPCTSTR)sData);
    //Line pulse
    m_clColorStaticCcdLinePulseVal.GetWindowText(sData);
    g_clModelData[m_nUnit].m_dLinePulse = _ttof((TCHAR*)(LPCTSTR)sData);


	//BlackLevel
	//m_clColorStaticCcdBlackLevelVal.GetWindowText(sData);
	//g_clModelData[m_nUnit].m_dSfrBlackLevel = _ttoi((TCHAR*)(LPCTSTR)sData);

	m_clColorStaticCcdDelayVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dCcdDelay = _ttof((TCHAR*)(LPCTSTR)sData);

	//Demosaic
	/*g_clModelData[m_nUnit].m_dDemosaic = m_ComboDemosaic.GetCurSel();
	switch (g_clModelData[m_nUnit].m_dDemosaic)
	{
	case 0:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_NONE; break;
	case 1:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GRADIENT; break;
	case 2:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_BL33; break;
	case 3:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_OPENCV_VNG; break;
	case 4:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_VNG; break;
	case 5:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GR_ONLY; break;
	case 6:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GB_ONLY; break;
	case 7:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GBTF; break;
	case 8:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_BLLC; break;
	case 9:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_RESIDUAL; break;
	case 10:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_BAYER_Y; break;
	case 11:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL; break;
	case 12:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GBTF_RESIDUAL; break;
	case 13:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_RESIDUAL_RESIDUAL; break;
	case 14:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_BL33_RESIDUAL; break;
	case 15:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_IR_ONLY; break;
	case 16:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_G_ONLY; break;
	case 17:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GBTF_G_ONLY; break;
	case 18:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_RESIDUAL_G_ONLY; break;
	case 19:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_BL33_G_ONLY; break;
	case 20:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_IR_ONLY; break;
	case 21:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_GBTF_IR_ONLY; break;
	case 22:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_RESIDUAL_IR_ONLY; break;
	case 23:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_BL33_IR_ONLY; break;
	default:
		g_clLaonGrabberWrapper[m_nUnit].dTDATASPEC_n.eDemosaicMethod = DEMOSAICMETHOD_NONE; break;
		break;
	}*/
	/*
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%d"), g_clModelData[m_nUnit].);
	.SetWindowText(szData);
	
	m_ComboDemosaic.SetCurSel(g_clModelData[m_nUnit].);
	//
	*/


	// CCD 반전
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_CCD_FLIP_USE);
	if(pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nCcdFlipUse = 1;
	else
		g_clModelData[m_nUnit].m_nCcdFlipUse = 0;

	// MTF Offset	
	m_clColorStaticCircleVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dCircleThresh = _ttof((TCHAR*)(LPCTSTR)sData); 

	// ROUGHT
	m_clColorStaticMoveVelRough.GetWindowText(sData);
	g_clModelData[m_nUnit].m_stAFInfo[0].dMoveVel = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticMoveAccRough.GetWindowText(sData);
	g_clModelData[m_nUnit].m_stAFInfo[0].dMoveAcc = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticDelayRough.GetWindowText(sData);
	g_clModelData[m_nUnit].m_stAFInfo[0].nDelayTime = _ttoi((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticMoveDistanceRough.GetWindowText(sData);
	g_clModelData[m_nUnit].m_stAFInfo[0].dMoveDistance = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticSfrAvgCountRough.GetWindowText(sData);
	g_clModelData[m_nUnit].m_stAFInfo[0].nAvgSfrCount = _ttoi((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticOkLimitRough.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dLimitSFRCent = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticFineMoveChangeRough.GetWindowText(sData);
	g_clModelData[m_nUnit].m_stAFInfo[0].fLimitRoughMTF = (float)_ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticFineMoveChangeFine.GetWindowText(sData);
	g_clModelData[m_nUnit].m_stAFInfo[0].fLimitFineMTF = (float)_ttof((TCHAR*)(LPCTSTR)sData);

	// FINE
	m_clColorStaticMoveVelFine.GetWindowText(sData);
	g_clModelData[m_nUnit].m_stAFInfo[1].dMoveVel = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticMoveAccFine.GetWindowText(sData);
	g_clModelData[m_nUnit].m_stAFInfo[1].dMoveAcc = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticDelayFine.GetWindowText(sData);
	g_clModelData[m_nUnit].m_stAFInfo[1].nDelayTime = _ttoi((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticMoveDistanceFine.GetWindowText(sData);
	g_clModelData[m_nUnit].m_stAFInfo[1].dMoveDistance = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticSfrAvgCountFine.GetWindowText(sData);
	g_clModelData[m_nUnit].m_stAFInfo[1].nAvgSfrCount = _ttoi((TCHAR*)(LPCTSTR)sData);
	m_clColorStatic2ndAAMoveDistanceFine.GetWindowText(sData);
	g_clModelData[m_nUnit].m_d2ndAAMoveDistance = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticOkLimitFine.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dLimitSFRSide = _ttof((TCHAR*)(LPCTSTR)sData);

	// SFR 연속 감소 동작
	m_clColorStaticCheckDataCountVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_nCountOfCheckSFR = _ttoi((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticSfrMoveDistanceVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dSfrMoveDistance = _ttof((TCHAR*)(LPCTSTR)sData);
	
	// MODE
	g_clModelData[m_nUnit].m_nSfrMode = m_clComboField.GetCurSel();
	g_clModelData[m_nUnit].m_nSFR_N_POS = m_clComboPosition.GetCurSel();

	// LASER SIZE
	/*m_clColorStaticInLaserXVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dLaserMoveX[0] = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticInLaserYVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dLaserMoveY[0] = _ttof((TCHAR*)(LPCTSTR)sData);*/
	m_clColorStaticOutLaserXVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dLaserMoveX[0] = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticOutLaserYVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dLaserMoveY[0] = _ttof((TCHAR*)(LPCTSTR)sData);

	m_clColorStaticOutComplLaserXVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dLaserComplMoveX[0] = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticOutComplLaserYVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dLaserComplMoveY[0] = _ttof((TCHAR*)(LPCTSTR)sData);

	// STAIN COUNT
	m_clColorStaticStainWhiteCount.GetWindowText(sData);
	g_clModelData[m_nUnit].m_nStainCount[0] = _ttoi((TCHAR*)(LPCTSTR)sData);	
	m_clColorStaticStainBlackCount.GetWindowText(sData);
	g_clModelData[m_nUnit].m_nStainCount[1] = _ttoi((TCHAR*)(LPCTSTR)sData);

	// UV TIME
	m_clColorStaticUvTimeVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dUvTime = _ttoi((TCHAR*)(LPCTSTR)sData);

	// PCB Z 회피위치
	m_clColorStaticEscapePcbZVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dEscapePosPcbZ = _ttof((TCHAR*)(LPCTSTR)sData);

	// RETRY / DELAY
	m_clColorStaticSensorRetryCount.GetWindowText(sData);
	g_clModelData[m_nUnit].m_nSensorAlignRetryCount = _ttoi((TCHAR*)(LPCTSTR)sData);

	m_clColorStaticCcdRetryCount.GetWindowText(sData);
	g_clModelData[m_nUnit].m_nCcdRetryCount = _ttoi((TCHAR*)(LPCTSTR)sData);



	m_clColorStaticLensRetryCount.GetWindowText(sData);
	g_clModelData[m_nUnit].m_nLensAlignRetryCount = _ttoi((TCHAR*)(LPCTSTR)sData);

	//contact
	m_clColorStaticContactRetryCount.GetWindowText(sData);
	g_clModelData[m_nUnit].m_nContactRetryCount = _ttoi((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticContactRetryDelay.GetWindowText(sData);
	g_clModelData[m_nUnit].m_nContactRetryDelay = _ttof((TCHAR*)(LPCTSTR)sData);


	m_clColorStaticLaserRetryCount.GetWindowText(sData);
	g_clModelData[m_nUnit].m_nLaserRetryCount = _ttoi((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticDiffRetryCount.GetWindowText(sData);
	g_clModelData[m_nUnit].m_nDiffRetryCount = _ttoi((TCHAR*)(LPCTSTR)sData);


	m_clColorStaticSensorDelay.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dSensorAlignDelay = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticDelay.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dLensAlignDelay = _ttof((TCHAR*)(LPCTSTR)sData);

	m_clColorStaticLaserDelay.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dLaserDelay = _ttof((TCHAR*)(LPCTSTR)sData);

	m_clColorStaticDiffDelay.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dDiffDelay = _ttof((TCHAR*)(LPCTSTR)sData);

	m_clColorStaticRawSumCountVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_nRawSumCount = _ttoi((TCHAR*)(LPCTSTR)sData);

	m_clColorStaticMaxStepCountVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_stAFInfo[0].nMaxStepCount = _ttoi((TCHAR*)(LPCTSTR)sData);


	//Oc Align Spec Put
	m_clColorStaticOcAlignSpecXVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dOcAlignSpec[0] = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticOcAlignSpecYVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dOcAlignSpec[1] = _ttof((TCHAR*)(LPCTSTR)sData);

	//Align Spec Get
	
	m_clColorStaticSensorAlignSpecX.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dSensorAlignSpec[0] = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticSensorAlignSpecY.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dSensorAlignSpec[1] = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticSensorAlignSpecTh.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dSensorAlignSpec[2] = _ttof((TCHAR*)(LPCTSTR)sData);

	
	m_clColorStaticLensAlignSpecX.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dLensAlignSpec[0] = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticLensAlignSpecY.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dLensAlignSpec[1] = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticLensAlignSpecTh.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dLensAlignSpec[2] = _ttof((TCHAR*)(LPCTSTR)sData);

	// 공운전
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_DRY_RUN_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nDryRunMode = 1;
	else
		g_clModelData[m_nUnit].m_nDryRunMode = 0;
	//
	// MES PASS
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_MES_PASS);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nMesPass = 1;
	else
		g_clModelData[m_nUnit].m_nMesPass = 0;

	//
	//포고핀 STOP
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_PIN_STOP_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nPinStopUse = 1;
	else
		g_clModelData[m_nUnit].m_nPinStopUse = 0;

	//master mode
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_MASTER_MODE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nMasterModeUse = 1;
	else
		g_clModelData[m_nUnit].m_nMasterModeUse = 0;
	
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_INSP_PASS);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nInspOKPass = 1;
	else
		g_clModelData[m_nUnit].m_nInspOKPass = 0;

	//align
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_ALIGN_PASS);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nAlignPass = 1;
	else
		g_clModelData[m_nUnit].m_nAlignPass = 0;

	//Raw save pass
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_RAW_SAVE_PASS);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nRawSavePass = 1;
	else
		g_clModelData[m_nUnit].m_nRawSavePass = 0;

	//jxl save pass
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_JXL_SAVE_PASS);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nJxlSavePass = 1;
	else
		g_clModelData[m_nUnit].m_nJxlSavePass = 0;

	//idle reason report
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_IDLE_REPORT_PASS);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nIdleReasonPass = 1;
	else
		g_clModelData[m_nUnit].m_nIdleReasonPass = 0;
	
	
	//sfr 평균 체크
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_SFR_AVERAGE); 
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nSfrAvrCheck = 1;
	else
		g_clModelData[m_nUnit].m_nSfrAvrCheck = 0;

	// FPS STOP
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_FPS_STOP_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nFpsStopUse = 1;
	else
		g_clModelData[m_nUnit].m_nFpsStopUse = 0;




	// 공용차트 사용 모드 (패턴)
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_COMPL_MODE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nPatternChartUse = 1;
	else
		g_clModelData[m_nUnit].m_nPatternChartUse = 0;

	//
	// STAIN 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_STAIN_INSP_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nStainInspUse = 1;
	else
		g_clModelData[m_nUnit].m_nStainInspUse = 0;


	//
	// DEFECT 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_DEFECT_INSP_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nCcdDefectInfpUse = 1;
	else
		g_clModelData[m_nUnit].m_nCcdDefectInfpUse = 0;



	// RI 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_RI_INSP_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nRITestUse = 1;
	else
		g_clModelData[m_nUnit].m_nRITestUse = 0;


	// CURRENT 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_CURRENT_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nCurrentUse = 1;
	else
		g_clModelData[m_nUnit].m_nCurrentUse = 0;

	// LASER 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_LASER_OUT_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nLaserOutUse = 1;
	else
		g_clModelData[m_nUnit].m_nLaserOutUse = 0;



	// UV 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_UV_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nUvUse = 1;
	else
		g_clModelData[m_nUnit].m_nUvUse = 0;

	// 내부 LASER 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_LASER_IN_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nLaserInUse = 1;
	else
		g_clModelData[m_nUnit].m_nLaserInUse = 0; 

	

	// 1차 AA후 배출 기능 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_UNLOAD_AFTER_1ST_AA_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nUnloadAfter1stAAUse = 1;
	else
		g_clModelData[m_nUnit].m_nUnloadAfter1stAAUse = 0;

	


	// SATURATION 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_SATURATION_INSP_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nSaturationInspUse = 1;
	else
		g_clModelData[m_nUnit].m_nSaturationInspUse = 0;

	// IR FILTER 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_IRFILTER_INSP_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nIRFilterInspUse = 1;
	else
		g_clModelData[m_nUnit].m_nIRFilterInspUse = 0;

	// COLOR REPRODUCTION 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_COLOR_REPRODUCTION_INSP_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nColorReproductionInspUse = 1;
	else
		g_clModelData[m_nUnit].m_nColorReproductionInspUse = 0;








	// NG이미지 SAVE
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_NG_IMAGE_SAVE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nNgImageSaveUse = 1;
	else
		g_clModelData[m_nUnit].m_nNgImageSaveUse = 0;

	// DARK 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_DARK_INSP_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nDarkInspUse = 1;
	else
		g_clModelData[m_nUnit].m_nDarkInspUse = 0;
	
	// DOORLOCK 검사 사용
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_DOORLOCK_USE);
	if (pButton->GetCheck() == 1)
	{
		TCHAR szLog[SIZE_OF_1K];
		int bState = -1;
		bState = g_clDioControl.GetDoorState();// 다 닫겨있으면 0
		TCHAR* pszCol[] = { _T("ALL DOOR"),
			_T("LEFT DOOR"),  _T("BACK DOOR"),  _T("LEFT+BACK DOOR"),  _T("RIGHT DOOR")
			,  _T("LEFT+RIGHT"),  _T("BACK+RIGHT DOOR") ,  _T("ALL DOOR") };
		if (bState > 0)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[CONFIG] %s OPEN 상태입니다."), pszCol[bState]);
			g_ShowMsgPopup(_T("ERROR"), szLog, RGB_COLOR_RED);
			_stprintf_s(szLog, SIZE_OF_1K, _T("[CONFIG] DOOR INTERLOCK 적용 실패"));
			g_ShowMsgPopup(_T("ERROR"), szLog, RGB_COLOR_RED);
			AddLog(szLog, 0, m_nUnit);
		}
		else
		{
			g_clModelData[m_nUnit].m_nDoorLockUse = 1;
		}

		
	}
	else
	{
		g_clModelData[m_nUnit].m_nDoorLockUse = 0;
	}
	// EPOXY PASS
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_EPOXY_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nEpoxyPass = 1;
	else
		g_clModelData[m_nUnit].m_nEpoxyPass = 0;

	// EPOXY INSPECTION PASS
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_EPOXY_INSP_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nEpoxyInspPass = 1;
	else
		g_clModelData[m_nUnit].m_nEpoxyInspPass = 0;

	
	
	m_clColorStaticFpsStopVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_fFpsStopVal = (float)_ttof((TCHAR*)(LPCTSTR)sData);

	m_clColorStaticJxlVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_nJxlEffort = (int)_ttof((TCHAR*)(LPCTSTR)sData);


	
	// 
	m_clColorStaticPinStopVal.GetWindowText(sData);
	g_clSysData.m_nMaxPinCount = _ttoi((TCHAR*)(LPCTSTR)sData);

	// LASER CONTROL LOCK
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_LASER_LOCK);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nLaserControlLock = 1;
	else
		g_clModelData[m_nUnit].m_nLaserControlLock = 0;

	// DOME CHART 사용유무
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_DOME_CHART_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nDomeChartUse = 1;
	else
		g_clModelData[m_nUnit].m_nDomeChartUse = 0;

	// UV LAMP ALARM 사용유무
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_UV_LAMP_ALARM_USE);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nUVLampAlarmUse = 1;
	else
		g_clModelData[m_nUnit].m_nUVLampAlarmUse = 0;

	// AA, 검사 PASS
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_AA_PASS);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nAAPass = 1;
	else
		g_clModelData[m_nUnit].m_nAAPass = 0;

	// AA, 검사 PASS
	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_INSPECTION_PASS);
	if (pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nInspectionPass = 1;
	else
		g_clModelData[m_nUnit].m_nInspectionPass = 0;

	// UV 전 OFFSET
	m_clColorStaticPreUvOffsetLensXVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dOffsetPrevUV_X = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticPreUvOffsetLensYVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dOffsetPrevUV_Y = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticPreUvOffsetLensZVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dOffsetPrevUV_Z = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticPreUvOffsetLensTxVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dOffsetPrevUV_Tx = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticPreUvOffsetLensTyVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dOffsetPrevUV_Ty = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticPreUvOffsetPcbThVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dOffsetPrevUV_Th = _ttof((TCHAR*)(LPCTSTR)sData);

	//
	m_clColorStaticEolPcbTxVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dEolPcbOffset_Tx = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticEolPcbTyVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dEolPcbOffset_Ty = _ttof((TCHAR*)(LPCTSTR)sData);
	// DELAY
	m_clColorStaticPcbVacuumDelayVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dPCBVacuumDelay = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticPcbGripDelayVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dPCBGripDelay = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticPcbGripUpDelayVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dPCBGripUpDelay = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticLaserTimeoutVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dLaserTimeOut = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticFinalDelayVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dFinalDelay = _ttof((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticBondingDelayVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dBondingDelay = _ttof((TCHAR*)(LPCTSTR)sData);

	//m_clColorStaticLensGripDelayVal.GetWindowText(sData);
	//g_clModelData[m_nUnit].m_dLENSGripDelay = _ttof((TCHAR*)(LPCTSTR)sData);

	// RS232
	g_clSysData.m_nTopLightPort[m_nUnit] = m_clComboChartLightPort1.GetCurSel() + 1;
	g_clSysData.m_nAlign_Oc_Port[m_nUnit] = m_clComboAlignLightPort1.GetCurSel() + 1;
	g_clSysData.m_nEzi_Port[m_nUnit] = m_clComboEziModule.GetCurSel() + 1;
	g_clSysData.m_nUvPort[m_nUnit] = m_clComboUvPort.GetCurSel() + 1;
	//

	//g_clSysData.m_nOC_IRPort[m_nUnit] = m_clComboAlignLightPort1.GetCurSel() + 1;
	g_clSysData.m_nLaserPort[m_nUnit] = m_clComboLaser1.GetCurSel() + 1;
	g_clSysData.m_nBcrPort[m_nUnit] = m_clComboBcrPort.GetCurSel() + 1;
	g_clSysData.m_nLeftLightPort[m_nUnit] = m_clComboLeftChartLightPort.GetCurSel() + 1;
	g_clSysData.m_nRightLightPort[m_nUnit] = m_clComboRightChartLightPort.GetCurSel() + 1;
	


	//g_clSysData.m_nTopLightPort[1] = m_clComboTopLight2.GetCurSel() + 1;
	//g_clSysData.m_nOCPort[1] = m_clComboOcLight2.GetCurSel() + 1;
	//g_clSysData.m_nDomeLightPort[m_nUnit] = m_clComboDomeLightPort.GetCurSel() + 1;

	
	
	//MES
	m_clColorStaticMesFactoryVal.GetWindowText(sData);
	_tcscpy_s(g_clSysData.m_szFactoryCd, SIZE_OF_100BYTE, (TCHAR*)(LPCTSTR)sData);

	//MES
	m_clColorStaticMesFactoryComplVal.GetWindowText(sData);
	_tcscpy_s(g_clSysData.m_szFactoryComplCd, SIZE_OF_100BYTE, (TCHAR*)(LPCTSTR)sData);
	m_clColorStaticMesPortVal.GetWindowText(sData);
	g_clSysData.m_nMesPort = _ttoi((TCHAR*)(LPCTSTR)sData);
	m_clColorStaticMesIpVal.GetWindowText(sData);
	_tcscpy_s(g_clSysData.m_szMesIp, SIZE_OF_100BYTE, (TCHAR*)(LPCTSTR)sData);


	//FILE DELETE
	m_clColorStaticDelDayVal.GetWindowText(sData);
	g_clSysData.m_nFileDeleteDay = _ttoi((TCHAR*)(LPCTSTR)sData);


	// MAIN PC
	m_clColorStaticMainIpVal.GetWindowText(sData);
	_tcscpy_s(g_clSysData.m_szAAIp, SIZE_OF_100BYTE, (TCHAR*)(LPCTSTR)sData);
	m_clColorStaticMainPortVal.GetWindowText(sData);
	g_clSysData.m_nAAPort = _ttoi((TCHAR*)(LPCTSTR)sData);

	// 화상검사기 PC
	m_clColorStaticInspIpVal.GetWindowText(sData);
	_tcscpy_s(g_clSysData.m_szInspIp, SIZE_OF_100BYTE, (TCHAR*)(LPCTSTR)sData);
	m_clColorStaticInspPortVal.GetWindowText(sData);
	g_clSysData.m_nInspPort = _ttoi((TCHAR*)(LPCTSTR)sData);

	// 센서 구동 파일
	GetDlgItem(IDC_EDIT_CONFIG_INI_FILE_PATH)->GetWindowText(sData);
	_tcscpy_s(g_clModelData[m_nUnit].m_szIniPath, SIZE_OF_1K, (TCHAR*)(LPCTSTR)sData);

	// MES LOG DATA 저장 경로

	pButton = (CButton*)GetDlgItem(IDC_CHECK_CONFIG_SFR_OVERLAY_USE);
	if(pButton->GetCheck() == 1)
		g_clModelData[m_nUnit].m_nMtfOverlayUse = 1;
	else
		g_clModelData[m_nUnit].m_nMtfOverlayUse = 0;

	m_clColorStaticStainLcbCenterVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dStainLsbCenter = _ttof((TCHAR*)(LPCTSTR)sData);
	
	m_clColorStaticStinLcbCornerVal.GetWindowText(sData);
	 g_clModelData[m_nUnit].m_dStainLsbCorner = _ttof((TCHAR*)(LPCTSTR)sData);
	
	m_clColorStaticStainLcbEdgeVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dStainLsbEdge = _ttof((TCHAR*)(LPCTSTR)sData);
	
	m_clColorStaticStainYMeanCenterVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dStainYMeanCenter = _ttof((TCHAR*)(LPCTSTR)sData);
	
	m_clColorStaticStinYMeanCornerVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dStainYMeanCorner = _ttof((TCHAR*)(LPCTSTR)sData);
	
	m_clColorStaticStainYMeanEdgeVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_dStainYMeanEdge  = _ttof((TCHAR*)(LPCTSTR)sData);
	
	m_clColorStaticMarkNoVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_nMarkNo = _ttoi((TCHAR*)(LPCTSTR)sData) - 1;
	
	m_clColorStaticMatchingVal.GetWindowText(sData);
	g_clModelData[m_nUnit].m_nMinMatching = _ttoi((TCHAR*)(LPCTSTR)sData);	
}

//-----------------------------------------------------------------------------
//
//	OnCtlColor
//
//-----------------------------------------------------------------------------
HBRUSH CConfigDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_DRY_RUN_USE || pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_COMPL_MODE ||
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_UV_USE || pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_LASER_IN_USE ||
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_LASER_OUT_USE || pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_STAIN_INSP_USE ||
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_DARK_INSP_USE || pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_DEFECT_INSP_USE ||
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_LASER_LOCK || pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_UNLOAD_AFTER_1ST_AA_USE ||
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_FPS_STOP_USE ||
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_SFR_AVERAGE ||
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_CCD_FLIP_USE || 
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_DOME_CHART_USE ||
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_PIN_STOP_USE || pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_UV_LAMP_ALARM_USE ||
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_MASTER_MODE || 
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_AA_PASS || pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_INSPECTION_PASS ||
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_SFR_OVERLAY_USE || pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_CURRENT_USE ||
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_NG_IMAGE_SAVE || pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_DOORLOCK_USE ||
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_MES_PASS || pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_EPOXY_USE || 
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_EPOXY_INSP_USE || pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_SATURATION_INSP_USE || 
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_IRFILTER_INSP_USE || pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_COLOR_REPRODUCTION_INSP_USE ||
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_RI_INSP_USE ||
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_INSP_PASS || pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_ALIGN_PASS||
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_RAW_SAVE_PASS || pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_JXL_SAVE_PASS||
		pWnd->GetDlgCtrlID() == IDC_CHECK_CONFIG_IDLE_REPORT_PASS

		
		)
	{
		pDC->SetTextColor(RGB_COLOR_WHITE);
        pDC->SetBkColor(RGB(100, 100, 100));
		pDC->SetBkMode(TRANSPARENT);

        return (HBRUSH)m_brCheck;
		//return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

//-----------------------------------------------------------------------------
//
//	PreTranslateMessage
//
//-----------------------------------------------------------------------------
BOOL CConfigDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CONFIG_SAVE)->m_hWnd)
		{
			//m_clColorButtonSave.SetSelected(true);
		}
	}
	else
	{
        if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CONFIG_SAVE)->m_hWnd)
		{
			//m_clColorButtonSave.SetSelected(false);
		}
	}

	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == 'H' || pMsg->wParam == 'h')
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				this->HideMtfOffset(true);
			}
		}
		else if (pMsg->wParam == 'S' || pMsg->wParam == 's')
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				this->HideMtfOffset(false);
			}
		}
		else if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CConfigDlg::OnStnClickedStaticConfigCcdLinePulseVal()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString sData = _T("");

    m_clColorStaticCcdLinePulseVal.GetWindowText(sData);
    CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
    if (pDlg != NULL)
    {
        if (pDlg->DoModal() == IDOK)
        {
            sData.Format(_T("%.3lf"), pDlg->GetReturnVal());
            m_clColorStaticCcdLinePulseVal.SetWindowText(sData);
        }

        delete pDlg;
    }
    m_clColorStaticCcdLinePulseVal.Invalidate();
}


void CConfigDlg::OnStnClickedStaticConfigMesFactoryVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CKeyBoardDlg* pDlg = new CKeyBoardDlg(20, false);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			m_clColorStaticMesFactoryVal.SetWindowText(pDlg->GetReturnValue());
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigLensAlignRetryCount()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticLensRetryCount.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticLensRetryCount.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigLensAlignDelay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticLensDelay.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticLensDelay.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigSensorAlignSpecX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticSensorAlignSpecX.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticSensorAlignSpecX.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigSensorAlignSpecY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticSensorAlignSpecY.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticSensorAlignSpecY.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigSensorAlignSpecTh()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticSensorAlignSpecTh.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticSensorAlignSpecTh.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigLensAlignSpecX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticLensAlignSpecX.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticLensAlignSpecX.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigLensAlignSpecY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticLensAlignSpecY.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticLensAlignSpecY.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigLensAlignSpecTh()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticLensAlignSpecTh.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticLensAlignSpecTh.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigLensGripDelayVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticLensGripDelayVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.01lf"), pDlg->GetReturnVal());
			m_clColorStaticLensGripDelayVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigOutComplLaserXVal()
{
	CString sData = _T("");

	m_clColorStaticOutComplLaserXVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticOutComplLaserXVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigOutComplLaserYVal()
{
	CString sData = _T("");

	m_clColorStaticOutComplLaserYVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticOutComplLaserYVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigMesFactoryComplVal()
{
	CKeyBoardDlg* pDlg = new CKeyBoardDlg(20, false);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			m_clColorStaticMesFactoryComplVal.SetWindowText(pDlg->GetReturnValue());
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigRowSumcountVal()
{
	CString sData = _T("");
	int nVal;

	m_clColorStaticRawSumCountVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			nVal =  (int)pDlg->GetReturnVal();
			if (nVal < 1)
				nVal = 1;
			if (nVal > 10)
				nVal = 10;
			sData.Format(_T("%d"), nVal);
			m_clColorStaticRawSumCountVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigMaxstepCountVal()
{
	CString sData = _T("");
	int nVal;

	m_clColorStaticMaxStepCountVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			nVal = (int)pDlg->GetReturnVal();
			if (nVal < 1)
				nVal = 1;
			sData.Format(_T("%d"), nVal);
			m_clColorStaticMaxStepCountVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigFineMoveChangeFine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticFineMoveChangeFine.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticFineMoveChangeFine.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigEolPcbTyVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticEolPcbTyVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticEolPcbTyVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigEolPcbTxVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticEolPcbTxVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticEolPcbTxVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigOcAlignSpecXVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticOcAlignSpecXVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticOcAlignSpecXVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigOcAlignSpecYVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticOcAlignSpecYVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticOcAlignSpecYVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigMesIpVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CKeyBoardDlg* pDlg = new CKeyBoardDlg(20, false);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			m_clColorStaticMesIpVal.SetWindowText(pDlg->GetReturnValue());
		}

		delete pDlg;
	}
	
}


void CConfigDlg::OnStnClickedStaticConfigMesPortVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticMesPortVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticMesPortVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigCcdBlacklevelVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticCcdBlackLevelVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticCcdBlackLevelVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigCcdDelayVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticCcdDelayVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.01lf"), pDlg->GetReturnVal());
			m_clColorStaticCcdDelayVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigContactRetryDelay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticContactRetryDelay.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			double dtemp = pDlg->GetReturnVal();
			if (dtemp < 0.1)
			{
				dtemp = 0.1;
			}
			sData.Format(_T("%.01lf"), dtemp);
			m_clColorStaticContactRetryDelay.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigContactRetryCount()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticContactRetryCount.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			int ntemp = (int)pDlg->GetReturnVal();
			if (ntemp < 0)
			{
				ntemp = 0;
			}
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticContactRetryCount.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigDelDayVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticDelDayVal.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			int ntemp = (int)pDlg->GetReturnVal();
			if (ntemp < 1)
			{
				ntemp = 1;
			}
			sData.Format(_T("%d"), ntemp);
			m_clColorStaticDelDayVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigCcdRetryCount()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticCcdRetryCount.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticCcdRetryCount.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnBnClickedButtonConfigVerView()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("자동 운전 중 사용불가합니다."), RGB_COLOR_RED);
		return;
	}
	g_pCarAABonderDlg->versionList();
}


void CConfigDlg::OnBnClickedButtonConfigDoorOpen()
{
	// TODO: Add your control notification handler code here
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("자동 운전 중 사용불가합니다."), RGB_COLOR_RED);
		return;
	}
	if (g_clModelData[m_nUnit].m_nDoorLockUse == 1)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("DOOR INTERLOCK 사용중입니다."), RGB_COLOR_RED);
		return;
	}
	//도어락에 led가 켜지면 open상태이다.
	g_clDioControl.DoorUnLock(m_nUnit, true);
}


void CConfigDlg::OnBnClickedButtonConfigDoorClose()
{
	// TODO: Add your control notification handler code here
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("자동 운전 중 사용불가합니다."), RGB_COLOR_RED);
		return;
	}
	TCHAR szLog[SIZE_OF_1K];
	int bState = -1;
	bState = g_clDioControl.GetDoorState();	// 다 닫겨있으면 true, 열리면 false.
											// 다 닫겨있으면 0, 열리면 1,2,3.

	TCHAR* pszCol[] = { _T("ALL DOOR"),  
		_T("LEFT DOOR"),  _T("BACK DOOR"),  _T("LEFT+BACK DOOR"),  _T("RIGHT DOOR")
		,  _T("LEFT+RIGHT")
		,  _T("BACK+RIGHT DOOR") ,  _T("ALL DOOR") };
	//1 = 좌측 도어 열림
	//2 = 뒷면 도어 열림
	//3 = 좌측,뒷면 열림
	//4 = 우측만 열림
	//6 = 뒤면, 우측
	//7 = 3개다 열림
	if (bState == 0)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[CONFIG] %s CLOSE 상태입니다."), pszCol[bState]);
		g_ShowMsgPopup(_T("ERROR"), szLog, RGB_COLOR_RED);
		AddLog(szLog, 0, m_nUnit);
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[CONFIG] %s OPEN 상태입니다."), pszCol[bState]);
		g_ShowMsgPopup(_T("ERROR"), szLog, RGB_COLOR_RED);
		AddLog(szLog, 0, m_nUnit);
	}

	g_clDioControl.DoorUnLock(m_nUnit, false);
}


void CConfigDlg::OnStnClickedStaticConfigDiffRetryCount()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticDiffRetryCount.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%d"), (int)pDlg->GetReturnVal());
			m_clColorStaticDiffRetryCount.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnStnClickedStaticConfigDiffDelay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");

	m_clColorStaticDiffDelay.GetWindowText(sData);
	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);
	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			sData.Format(_T("%.03lf"), pDlg->GetReturnVal());
			m_clColorStaticDiffDelay.SetWindowText(sData);
		}

		delete pDlg;
	}
}


void CConfigDlg::OnBnClickedButtonConfigBcrOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("자동 운전 중 사용불가합니다."), RGB_COLOR_RED);
		return;
	}
	TCHAR szLog[SIZE_OF_1K];

	g_pCarAABonderDlg->m_clSerialThread.CloseBcrSerial(0);

	_stprintf_s(szLog, SIZE_OF_1K, _T("[SERIAL]BCR COM(%d) 연결 초기화"), g_clSysData.m_nBcrPort[0]);
	AddLog(szLog, 0, 0);

	Sleep(1000);
	
	if (g_pCarAABonderDlg->m_clSerialThread.OpenBcrSerial(0, g_clSysData.m_nBcrPort[0], 9600) == false)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[SERIAL] BCR COM(%d) 연결 실패"), g_clSysData.m_nBcrPort[0]);
		AddLog(szLog, 0, 0);
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[SERIAL]BCR COM(%d) 연결 성공"), g_clSysData.m_nBcrPort[0]);
		AddLog(szLog, 0, 0);
	}
}


void CConfigDlg::OnBnClickedButtonConfigBcrClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		g_ShowMsgPopup(_T("ERROR"), _T("자동 운전 중 사용불가합니다."), RGB_COLOR_RED);
		return;
	}
	TCHAR szLog[SIZE_OF_1K];

	g_pCarAABonderDlg->m_clSerialThread.CloseBcrSerial(0);

	_stprintf_s(szLog, SIZE_OF_1K, _T("[SERIAL]BCR COM(%d) 연결 해제"), g_clSysData.m_nBcrPort[0]);
	AddLog(szLog, 0, 0);
}


void CConfigDlg::OnStnClickedStaticConfigJxlVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sData = _T("");
	int dRetVal = 0;

	m_clColorStaticJxlVal.GetWindowText(sData);

	CKeyPadDlg* pDlg = new CKeyPadDlg(sData, 10);

	if (pDlg != NULL)
	{
		if (pDlg->DoModal() == IDOK)
		{
			dRetVal = (int)pDlg->GetReturnVal();
			if (dRetVal < 1)
			{
				dRetVal = 1;
			}
			if (dRetVal > 10)
			{
				dRetVal = 10;
			}


			sData.Format(_T("%d"), dRetVal);
			m_clColorStaticJxlVal.SetWindowText(sData);
		}

		delete pDlg;
	}
}
