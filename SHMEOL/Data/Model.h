#pragma once
#include "../AXTDefine.h"


typedef struct STRUC_TEACH_DATA
{
	double dPos[MAX_MOTOR_COUNT];
	double dOffset[MAX_MOTOR_COUNT];
} STRUC_TEACH_DATA;

typedef struct STRUC_AA_INFO
{
	double dMoveVel;			/* 이동 속도 */
	double dMoveAcc;			/* 가감속 */
	double dMoveDistance;		/* 이동거리 : mm */
	int	nDelayTime;				/* 단위 : msec */
	int	nMaxStepCount;			/* MAX STEP 수*/
	float fLimitMTF;			/* Rough 이동 Limit MTF 값 */
	int nAvgSfrCount;			/* SFR 평균 카운트*/
}STRUC_AA_INFO;


class CSFRInfo
{
public:
	CSFRInfo()
	{
		int i;
		double dOffsetX, dOffsetY;

		m_nSizeX = 80;// 50;
		m_nSizeY = 80;// 70;

		for (i = 0; i < (MAX_LAST_INSP_COUNT + MAX_DOME_INSP_ADD); i++)
		{
			m_clPtOffset[i].x = m_clPtOffset[i].y = 0;

			switch (i)
			{
			case 0:		dOffsetX = 2.15;	dOffsetY = 2.31;	break;
			case 1:		dOffsetX = 4.25;	dOffsetY = 4.82;	break;
			case 2:		dOffsetX = 1.38;	dOffsetY = 4.82;	break;
			case 3:		dOffsetX = 1.38;	dOffsetY = 1.53;	break;
			case 4:		dOffsetX = 4.25;	dOffsetY = 1.53;	break;
			case 5:		dOffsetX = 1.51;	dOffsetY = 2.41;	break;
			case 6:		dOffsetX = 3.20;	dOffsetY = 2.41;	break;
			case 7:		dOffsetX = 19.2;	dOffsetY = 20.6;	break;
			case 8:		dOffsetX = 1.15;	dOffsetY = 19.0;	break;
			case 9:		dOffsetX = 1.15;	dOffsetY = 1.27;	break;
			case 10:	dOffsetX = 20.9;	dOffsetY = 1.28;	break;
			case 11:	dOffsetX = 2.19/*1.36*/;	dOffsetY = 20.6/*1.50*/;	break;
			case 12:	dOffsetX = 2.19;	dOffsetY = 1.23;	break;
				/*case 13:	dOffsetX = 5.61;	dOffsetY = 1.51;	break;
				case 14:	dOffsetX = 11.1;	dOffsetY = 2.41;	break;
				case 15:	dOffsetX = 19.2;	dOffsetY = 20.6;	break;
				case 16:	dOffsetX = 1.15;	dOffsetY = 19.0;	break;
				case 17:	dOffsetX = 1.15;	dOffsetY = 1.27;	break;
				case 18:	dOffsetX = 20.9;	dOffsetY = 1.28;	break;*/
			}

			m_clPtOffset[i].x = (LONG)((double)CCD2_CAM_SIZE_X / dOffsetX);
			m_clPtOffset[i].y = (LONG)((double)(CCD2_CAM_SIZE_Y/* - 4*/) / dOffsetY);
		}

		m_clRectCircle[0].left = (LONG)((double)CCD2_CAM_SIZE_X * 0.25);
		m_clRectCircle[0].top = (LONG)((double)(CCD2_CAM_SIZE_Y/* - 4*/) * 0.03);
		m_clRectCircle[0].right = (LONG)((double)CCD2_CAM_SIZE_X * 0.41);
		m_clRectCircle[0].bottom = (LONG)((double)(CCD2_CAM_SIZE_Y - 4) * 0.28);

		m_clRectCircle[1].left = (LONG)((double)CCD2_CAM_SIZE_X * 0.59);
		m_clRectCircle[1].top = (LONG)((double)(CCD2_CAM_SIZE_Y/* - 4*/) * 0.03);
		m_clRectCircle[1].right = (LONG)((double)CCD2_CAM_SIZE_X * 0.73);
		m_clRectCircle[1].bottom = (LONG)((double)(CCD2_CAM_SIZE_Y/* - 4*/) * 0.28);

		m_clRectCircle[2].left = (LONG)((double)CCD2_CAM_SIZE_X * 0.25);
		m_clRectCircle[2].top = (LONG)((double)(CCD2_CAM_SIZE_Y/* - 4*/) * 0.72);
		m_clRectCircle[2].right = (LONG)((double)CCD2_CAM_SIZE_X * 0.41);
		m_clRectCircle[2].bottom = (LONG)((double)(CCD2_CAM_SIZE_Y/* - 4*/) * 0.97);

		m_clRectCircle[3].left = (LONG)((double)CCD2_CAM_SIZE_X * 0.59);
		m_clRectCircle[3].top = (LONG)((double)(CCD2_CAM_SIZE_Y/* - 4*/) * 0.72);
		m_clRectCircle[3].right = (LONG)((double)CCD2_CAM_SIZE_X * 0.73);
		m_clRectCircle[3].bottom = (LONG)((double)(CCD2_CAM_SIZE_Y/* - 4*/) * 0.97);
	}

public:
	CRect m_clRectCircle[4];
	CPoint m_clPtCircle[4];
	CPoint m_clPtOffset[MAX_LAST_INSP_COUNT + MAX_DOME_INSP_ADD];
	int m_nSizeX;
	int m_nSizeY;

};
class CModelData
{
public:
	CModelData();
	~CModelData();

public:
	void Load(TCHAR* szModelName);
	void Save(TCHAR* szModelName);
	void SaveTeachData(TCHAR* szModelName);
	void CopyBackup(TCHAR* szModelName);

	void SetUnit(int nUnit);

public:
	int m_nUnit;

	TCHAR m_szIniPath[SIZE_OF_1K];				// 센서구동 Ini파일 경로
	int m_nWidth;								// CCD SENSOR SIZE X
	int m_nHeight;								// CCD SENSOR SIZE Y

	CSFRInfo m_clSfrInfo;
	STRUC_TEACH_DATA m_stTeachData[MAX_POS_COUNT];

	int m_nRoiSizeX;
	int m_nRoiSizeY;
	double m_dCcdCellSize;

	int m_nMTF_FinalMode;			//MTF Final 측정시 Point 수(17P=0, 24P=1)
	int m_nCcdFlipUse;				//CCD 영상 반전 사용여부	
	int m_nOldChartMTF;				//구차트 MTF 검사 여부(0=미사용, 1=사용)

	double m_dMTFOffset;			//신규 차트 MTF OFFSET 가중치

	STRUC_AA_INFO m_stAFInfo[2];			/* AutoFocus Rough/Fine */
	double	m_dLimitSFRCent;
	double m_d2ndAAMoveDistance;				// 2차 AA 시작 지점 이동 거리
	double	m_dLimitSFRSide;

	int m_nCountOfCheckSFR;					// SFR 감소 판단 데이터 카운트
	double m_dSfrMoveDistance;				// SFR 감소시 이동 거리

	int m_nSfrMode;							// SFR 모드

	int m_nSFR_N_POS;

	double m_dLaserMoveX[2];		// 0 : 내측, 1 : 외측
	double m_dLaserMoveY[2];		// 0 : 내측, 1 : 외측

	int m_nStainCount[2];			//! Stain 불량 카운트 [0] 화이트  [1] 블랙	

	DWORD m_dwUvTime;

	double m_dEscapePosPcbZ;

	int m_nSensorAlignRetryCount;
	double m_dSensorAlignDelay;
	int m_nLaserRetryCount;			// Laser Retry Count
	double m_dLaserDelay;

	int m_nRunMode;					// 0 : NORMAL / 1 : 공운전 모드
	int m_nComplMode;				// 0 : NORMAL / 1 : 완제품 모드

	int m_nUvUse;					// UV 경화 사용여부

	int m_nLaserInUse;				// LASER 내부 사용여부
	int m_nLaserOutUse;				// LASER 외부 사용여부
	int m_nUnloadAfter1stAAUse;		// 1차 AA후 배출 사용여부
	int m_nStainInspUse;			// STAIN 검사 사용여부
	int m_nDarkInspUse;				// DARK 검사 사용여부
	int m_nCcdDefectInfpUse;		// CCD 이물검사 사용여부
	int m_nFpsStopUse;				// FPS 일정 값 이하시 CCD STOP 사용여부
	float m_fFpsStopVal;			// FPS 설정 값
	int m_nLaserControlLock;		// Laser Control 사용여부
	int m_nMtfOverlayUse;
	int m_nDomeChartUse;
	int m_nUVLampAlarmUse;
	int m_nAAPass;
	int m_nInspectionPass;

	double m_dOffsetPrevUV_X;
	double m_dOffsetPrevUV_Y;
	double m_dOffsetPrevUV_Z;
	double m_dOffsetPrevUV_Tx;
	double m_dOffsetPrevUV_Ty;
	double m_dOffsetPrevUV_Th;

	double m_dPCBVacuumDelay;
	double m_dPCBGripDelay;
	double m_dLensGripDelay;
	double m_dLaserTimeOut;
	double m_dFinalDelay;
	double m_dBondingDelay;

	int m_nPinStopUse;				// 포거핀 사용량 STOP 사용여부
	int m_nSensorCnt;				// 포거핀 사용량
	int m_nLight[MAX_LIGHT_COUNT];
	int m_nDomeLightVal[14];

	double m_dOcOffsetX;
	double m_dOcOffsetY;

	double m_dOkLimit[MAX_MOTOR_COUNT];
	double m_dErrLimit[MAX_MOTOR_COUNT];

	double m_dStainLsbCenter;
	double m_dStainLsbCorner;
	double m_dStainLsbEdge;

	double m_dStainYMeanCenter;
	double m_dStainYMeanCorner;
	double m_dStainYMeanEdge;

	int m_nMarkNo;
	int m_nMinMatching;
};

