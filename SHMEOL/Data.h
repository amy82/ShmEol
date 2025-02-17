#pragma once

#include "AXTDefine.h"
#include "Library/Inspection/Include/LibACMISCommon/ACMISCommon.h"


///////////////////////////////////////////////////////////////////////////////
//
//	ModelInfo
//
class CModelInfo
{
public:
	CModelInfo()
	{
		m_nNo = 0;
		memset(m_szName, 0x00, sizeof(m_szName));
	}

public:
	int m_nNo;
	TCHAR m_szName[SIZE_OF_100BYTE];
};
///////////////////////////////////////////////////////////////////////////////
//
//	ModelList
//
class CModelList
{
public:
	CModelList();
	~CModelList();

public:
	void ModelListLoad();
	void ModelListSave();
	void Insert(TCHAR* szModelName);
	void Delete(TCHAR* szModelName);
	CModelInfo GetModelInfo(int nIndex) { return m_clModelList[nIndex]; }

public:
	CArray<CModelInfo, CModelInfo&> m_clModelList;
	int m_nCurrentNo;
	int m_nTotalCount;

	TCHAR m_szCurrentModel[SIZE_OF_100BYTE];					// MODEL NAME



public:
	int iniRecipeListLoad();
	void xmlRecipeCreate(CString copyPPid, CString createPPid);
	void xmlRecipeDelete(CString PPid);
	void RecipeModelLoad();
	void RecipeModelSave();
	std::vector<std::string> m_vRecipeVec;



public:
	bool RecipeModelDel(CString PPid);

	void RecipeListLoad();
	void RecipeListSave();
	
	CArray<CModelInfo, CModelInfo&> m_clRecipeList;
};


class CModelType
{
public:
	CModelType();
	~CModelType();

public:
	void mTLoad();
	void mTSave();
	void CopyBackup();

public:
	//int m_nModelIndex;		//1 = MODERATE , 2 = NARROW
	//TCHAR m_szModelTypeName[SIZE_OF_100BYTE];		// 모델 명
};
///////////////////////////////////////////////////////////////////////////////
//
//	SystemData Class
//
class CSystemData
{
public:
	CSystemData();
	~CSystemData();

public:
	void sDLoad();
	void sDSave();

	void commonDataLoad();
	void commonDataSave();

	

	void sDCopyBackup();

	void SfrOffsetLoad();
	void OcOffsetLoad();
public:
	int m_nSysNo;
	int m_nUnitNo;
	TCHAR m_szModelName[SIZE_OF_100BYTE];					// MODEL NAME


	double	m_dSfrBasicOffset[MAX_LAST_INSP_COUNT];
	double	m_dSfrOutOffset[MAX_LAST_INSP_COUNT];

	double m_dOcOffset[2];

	TCHAR m_szMesIp[SIZE_OF_100BYTE];			// MES IP
	int m_nMesPort;								// MES 포트
	TCHAR m_szFactoryCd[SIZE_OF_100BYTE];		// 설비코드
	TCHAR m_szFactoryCd_RH[SIZE_OF_100BYTE];	// 설비코드

	TCHAR m_szFactoryComplCd[SIZE_OF_100BYTE];		// 설비코드
	TCHAR m_szFactoryComplCd_RH[SIZE_OF_100BYTE];	// 설비코드

	
	TCHAR m_szPassword[SIZE_OF_100BYTE];		// 비밀번호
	TCHAR m_szAAIp[SIZE_OF_100BYTE];			// MAIN PC IP
	TCHAR m_szInspIp[SIZE_OF_100BYTE];			// 화상검사기 PC IP
	
	double	m_dMotorSpeed[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];		//속도
	double	m_dMotorAccTime[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];	//가속
	double  m_dMotorDecTime[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];	//감속
	double	m_dMotorResol[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];		//전자기어비
	double	m_dOrgDataset[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];		//강제원점

	CDMPoint m_clCamResol[MAX_UNIT_COUNT];					// CAM X,Y 분해능
	CDMPoint m_clCamAngle[MAX_UNIT_COUNT];					// CAM ANGLE X,Y 분해능

	double	m_dLimitSFRBalance[MAX_UNIT_COUNT];

	CDMPoint m_clOCSpec[MAX_UNIT_COUNT];
	double m_dOCSpecTh[MAX_UNIT_COUNT];

	int m_nFileDeleteDay;
	int m_nAAPort;				// MAIN PC Port
	int m_nInspPort;			// 화상검사기 PC Port
	//Rs232
	int m_nTopLightPort[2];		// 탑차트 포트
	int m_nLeftLightPort[2];		// left 차트 포트
	int m_nRightLightPort[2];		//right차트 포트
	int m_nEzi_Port[2];			// 이물 광원 포트
	int m_nAlign_Oc_Port[2];		//ALIGN + OC  (백두 조명컨트롤러)

	int m_nOC_IRPort[2];			// IR 조명 컨트롤러 포트
	int m_nLaserPort[2];			// Laser 포트
	int m_nBcrPort[2];			// 바코드 포트
	int m_nUvPort[2];			// UV 포트
	
	//
	int m_nMaxPinCount;

	int m_nDomeLightPort[MAX_UNIT_COUNT];	// DOME 조명 컨틀롤러 포트

	int m_nSFR_Type[MAX_LAST_INSP_COUNT];

	TCHAR m_szMesPath[SIZE_OF_1K];				// MES LOF DATA 저장 경로

	//int m_nModelIndex;		//0==LH , 1 = RH
};


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
	float fLimitRoughMTF;			/* Rough 이동 Limit MTF 값 */
	float fLimitFineMTF;		/* Fine 이동 Limit MTF 값 */
	int nAvgSfrCount;			/* SFR 평균 카운트*/
}STRUC_AA_INFO;

class CSFRTeachingData
{
public:
	CSFRTeachingData();
	//~CSFRTeachingData();

public:
	double dSFRPcbX;
	double dSFRPcbY;
	double dSFRPcbZ;
	double dSFRPcbTx;
	double dSFRPcbTy;
};



class CSFRInfo
{
public:
	CSFRInfo()
	{
		int i;
		double dOffsetX, dOffsetY;
		for (i = 0; i < MAX_LAST_INSP_COUNT; i++)
		{
			m_nSizeX[i] = 80;// 50;
			m_nSizeY[i] = 80;// 70;
		}
		

		m_nCenSizeX = 150;
		m_nCenSizeY = 150;
		for (i = 0; i < (MAX_LAST_INSP_COUNT); i++)
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
	

	double m_dSfrOcX;
	double m_dSfrOcY;

    CRect m_clRectFov[MAX_FOV_COUNT];
   // CPoint m_clPtFov[MAX_FOV_COUNT];
	CPoint m_clPtFovOffset[MAX_FOV_COUNT];


	int m_nFovSizeX[MAX_FOV_COUNT];
	int m_nFovSizeY[MAX_FOV_COUNT];

	double m_dFovOcX;
	double m_dFovOcY;

    CRect m_clRectSnr[MAX_SNR_COUNT];
    CPoint m_clPtSnr[MAX_SNR_COUNT];
	double m_dSnrOcX[2];
	double m_dSnrOcY[2];


	CPoint m_clPtOffset[MAX_LAST_INSP_COUNT];
	int m_nSizeX[MAX_LAST_INSP_COUNT];
	int m_nSizeY[MAX_LAST_INSP_COUNT];

	int m_nCenSizeX;
	int m_nCenSizeY;
};
enum AA_SFR_SPEC {
    AA_CL_00F_V = 0, AA_CR_OOF_V, AA_CT_00F_H, AA_CB_00F_H, AA_LT_04F_V,
    AA_LT_04F_H, AA_RT_04F_V, AA_RT_04F_H, AA_RB_04F_V, AA_RB_04F_H,
    AA_LB_04F_V, AA_LB_04F_H, AA_L_04F_V, AA_L_04F_H, AA_R_04F_V,
    AA_R_04F_H, AA_LT_07F_V, AA_LT_07F_H, AA_RT_07F_V, AA_RT_07F_H,
    AA_RB_07F_V, AA_RB_07F_H, AA_LB_07F_V, AA_LB_07F_H, MAX_SFR_AA_INSP_CNT
};

enum AA_INSP_SUMAVE_SPEC {
	_CENTER = 0,
	_AVER_07F_TOP,
	_AVER_07F_BOTTOM,
	_AVER_07F_LEFT,
	_AVER_07F_RIGHT,

	MAX_SFR_INSP_SUMAVE_CNT
};

//enum AA_INSP_SUMAVE_SPEC {
//	_CENTER = 0,
//	_AVER_05F_LT,
//	_AVER_05F_RT,
//	_AVER_05F_LB,
//	_AVER_05F_RB,
//	_AVER_07F_LT,
//	_AVER_07F_RT,
//	_AVER_07F_LB,
//	_AVER_07F_RB,
//	MAX_SFR_INSP_SUMAVE_CNT
//};



///////////////////////////////////////////////////////////////////////////////
//
//	ModelData Class
//
class CModelData
{
public:
	CModelData();
	~CModelData();

public:
	void Load(TCHAR* szModelName);
	void Save(TCHAR* szModelName);

	void LoadTeachData(TCHAR* szModelName);
	void SaveTeachData(TCHAR* szModelName);

	void ModelCopyBackup(TCHAR* szModelName);
	void TeachCopyBackup(TCHAR* szModelName);

    void PatternSave(TCHAR* szModelName);
    void PatternLoad(TCHAR* szModelName);

	bool FinaLogCopy(TCHAR* szTempLog);
	void AcmisDataLoad(TCHAR* szModelName);
	void AcmisDataSave(TCHAR* szModelName);

	void LensShadingSpecLoad(TCHAR* szModelName);
	void LensShadingSpecSave(TCHAR* szModelName);
	
	void LotDataLoad();
	void LotDataSave();

	void EpoxyDataLoad(TCHAR* szModelName);
	void EpoxyDataSave(TCHAR* szModelName);
	
	void SetUnit(int nUnit);
	void ModulTypeLoad();


	void VarationLoad();
public:
	int m_nUnit;
	/*double m_LS_5000k_SpecMin[4][221];
	double m_LS_5000k_SpecMax[4][221];

	double m_LS_3000k_SpecMin[4][221];
	double m_LS_3000k_SpecMax[4][221];*/
	//-------------------------------------------------------------------------
	//
	//Epoxy 설정 
	double m_EpoxyLineSpeed;
	double m_EpoxyLineAccDec;
	double m_EpoxyCurveSpeed;
	double m_EpoxyCurveAccDec;
	double m_EpoxyOnTime;
	double m_EpoxyOffTime;

	double m_EpoxyLineLength[4];
	double m_EpoxyCurveCenterXPoint[4];
	double m_EpoxyCurveCenterYPoint[4];
	double m_EpoxyCurveEndXPoint[4];
	double m_EpoxyCurveEndYPoint[4];


	//Epoxy Inspection 설정
	CPoint m_ResingRectStart[4];			// 날개부분 검사 영역 시작지점 (mm)
	CPoint m_ResingRectSize[4];				// 날개부분 검사 영역 크기(mm)
	CDMPoint m_CircleDrawCenter[4];			// 원호 중심점
	CDMPoint	m_CircleDrawSize[4];
	CDMPoint	m_ResinDrawSize;
	CDMPoint	m_dResinInspOffset[2];			// 0:안쪽 Offset, 1:바깥 Offset
	int		m_nResinInspLimit;				// 도포 검사 OK / NG 판정 Limit

	double	m_dResinInspRectSpec;			// 날개부분 검사 Spec 추가(%)
	double	m_dResinInspGapLength;			// HOLE 연속 끊어진 구간 Spec(mm)
	double	m_dResinInspHoleSpec;			// HOLE 검사 Spec 추가(%)

	int nVarRepetCount;		//반복횟수
	int nVarMode;			//0 = Min , 1 = Max , 2 = Average 

	CDMPoint	m_sfrOffset[20];//sfr 값에 x는 곱하기 , y는 더해주기

	//-------------------------------------------------------------------------
	int sfrParameter[4];	//0.DataFormat , 1.OutMode , 2.SensorType , 3.DemosaicMethod
	int blemishParameter[4];
	int colorParameter[4];
	int riParameter[4];

	int	m_dSfrBlackLevel;
	int	m_dBlemishBlackLevel;
	int	m_dColorBlackLevel;
	int	m_dRiBlackLevel;

	int m_nSfr8BitUse;
	int m_nBlemish8BitUse;
	int m_nColor8BitUse;
	int m_nRi8BitUse;

	//-------------------------------------------------------------------------
	//
	//★ACMIS 검사 Spec Data
	//-------------------------------------------------------------------------
//TAllDefectPixel_ONSEMI_RCCB m_DefectSpec;
	int n_DefectCountLimit;
	int n_ClusterCountLimit;
	//Stain

	//fov , distortion 
	double m_FovSpec[9];//

    //oc , rotate
    double m_OcSpec[2];//

    //Color Sensitivity ColorMean WhiteBalance
    //double m_ColorSensitivitySpec[3][g_ColorSenscount];//	 0 = 3000k , 1 = 5000k ,2 = Dark

    //SNR
    double m_SnrSpec[2];//

	//Uniform 
	//double m_UniformSpec[g_ColorUniformitycount];// [14];//

	//Fpn snr row column noise 
	//double m_FpnSpec[g_Fpncount];
	//Relative Illumination  
	double m_RIlluminationSpec[5];//

	//Blemish Stain  
	//double m_BlemishSpec[g_Blemishcount];
	//double m_LcbSpec[g_StainLcbcount];
	//double m_YmeanSpec[g_StainYmeancount];
	//double m_FDFSpec[g_StainFdfcount];

	int m_LcbOffsetSpec[4];
	int m_YmeanOffsetSpec[4];
	int m_FDFOffsetSpec[4];

	//Defect
	//double m_DefectSpec[g_Defectcount];
	//double m_ICSpec[g_Iccount];
	//Chart  
	double m_ChartSpec[8];
	//Saturation  
	double m_SaturationSpec[6];
	//IR FILTER
	//double m_IrFilterSpec[g_Ircount];

	//Color Reproduction  
	double m_ColorReproductionSpec[32];

	//TEMPERATURE
	double m_TemperatureSpec[8];

	//TEMPERATURE
	double INSP_Voltage_Spec;
	double m_VoltageSpec[8];
    //RI  
   // double m_RISpec[g_Ricount];//m_RISpec[6] = CornerVariationMin , m_RISpec[7] = CornerVariationMax
	//COLOR SHADING  
    //double m_ColorShadingSpec[g_ColorShadingcount];

	//Lens shading Roi 총 221개 (가로 17개 , 세로 13개)
	CRect m_LensShadingRoi[221];


	


    double m_RirOI[100][10];
	//OC Offset X,Y
	double m_dOcOffsetX[2];
	double m_dOcOffsetY[2];
	//IC Offset X,Y
	double m_d_IC_OffsetX[2];	//결과값에 퍼센트 곱하기
	double m_d_IC_OffsetY[2];

	//oc limit min,max
	double m_dOCSpecLimit[2];	//0 = min , 1 = max
	//Current 
	double m_CurrentSpec[2];//
	double m_7FVariation[2];
	double m_dRotateSpecLimit[2];	//0 = min , 1 = max

	double m_dTiltxSpecLimit[2];	//0 = min , 1 = max
	double m_dTiltySpecLimit[2];	//0 = min , 1 = max
	//-------------------------------------------------------------------------
	//
	//-------------------------------------------------------------------------
	TCHAR m_szIniPath[SIZE_OF_1K];				// 센서구동 Ini파일 경로
	int m_nWidth;								// CCD SENSOR SIZE X
	int m_nHeight;								// CCD SENSOR SIZE Y


	int DefectSizeX;
	int DefectSizeY;


	CSFRInfo m_clSfrInfo;
	STRUC_TEACH_DATA m_stTeachData[MAX_POS_COUNT];

	int m_nRoiSizeX;
	int m_nRoiSizeY;
	double m_dCcdCellSize;

	int m_nMTF_FinalMode;			//MTF Final 측정시 Point 수(17P=0, 24P=1)
	int m_nCcdFlipUse;				//CCD 영상 반전 사용여부	
	int m_nOldChartMTF;				//구차트 MTF 검사 여부(0=미사용, 1=사용)

	double m_dMTFOffset;			//신규 차트 MTF OFFSET 가중치
	double m_dCircleThresh;
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

	double m_dLaserComplMoveX[2];	// 완제품 모드 -> 0 : 내측, 1 : 외측
	double m_dLaserComplMoveY[2];	// 완제품 모드 -> 0 : 내측, 1 : 외측

	
	int m_nStainCount[2];			//! Stain 불량 카운트 [0] 화이트  [1] 블랙	
	
	int m_dUvTime;
	
	double m_dEscapePosPcbZ;
	
	int m_nSensorAlignRetryCount;
	double m_dSensorAlignDelay;
	int m_nLensAlignRetryCount;
	double m_dLensAlignDelay;
	int m_nCcdRetryCount;

	int m_nContactRetryCount;
	double m_nContactRetryDelay;

	int m_nLaserRetryCount;			// Laser Retry Count
	double m_dLaserDelay;

	int m_nDiffRetryCount;			// Diff Retry Count
	double m_dDiffDelay;
		
	int m_nRawSumCount;				// Raw Sum Count

	double m_dOcAlignSpec[2];		//Oc Spec X , Y

	double m_dSensorAlignSpec[3];		//SensorAlign Spec X , Y , Th
	double m_dHolderAlign[3];			//HolderAlign Spec X , Y , Th
	double m_dLensAlignSpec[3];			//LensAlign Spec   X , Y , Th
	
	int m_nDryRunMode;					// 0 : NORMAL / 1 : 공운전 모드
	int m_nCOMPLETE_MODE;				// 0 : AA Mode / 1 : 완제품 모드

	int m_nUvUse;					// UV 경화 사용여부

	int m_nLaserInUse;				// LASER 내부 사용여부
	int m_nLaserOutUse;				// LASER 외부 사용여부
	int m_nUnloadAfter1stAAUse;		// 1차 AA후 배출 사용여부
    //
	int m_nStainInspUse;			// STAIN 검사 사용여부
	int m_nDarkInspUse;				// DARK 검사 사용여부
	int m_nNgImageSaveUse;

	int m_nSaturationInspUse;		// SATURATION 검사 사용여부
	int m_nIRFilterInspUse;			// IR FILTER 검사 사용여부.
	int m_nColorReproductionInspUse;// COLOR REPRODUCTION 검사 사용여부.





	//
	int m_nRITestUse;				//ri검사
	int m_nCurrentUse;				//전류 측정 사용여부
    int m_nSnrInspUse;
    int m_nDefectInspUse;
    int m_nRIInspUse;
    int m_nColorUniformityInspUse;
    int m_m_nColorSensitivityInspUse;
	//
	int m_nMesPass;			//1이면 사용안함
    //
    //

	int m_nDoorLockUse;				//DOOR LOCK 사용여부
	int m_nCcdDefectInfpUse;		// CCD 이물검사 사용여부
	int m_nFpsStopUse;				// FPS 일정 값 이하시 CCD STOP 사용여부
	int m_nPatternChartUse;
	int m_nSfrAvrCheck;				//SFR 판정 평균으로 판정
	float m_fFpsStopVal;			// FPS 설정 값
	int m_nJxlEffort;
	int m_nLaserControlLock;		// Laser Control 사용여부
	int m_nMtfOverlayUse;
	int m_nDomeChartUse;
	int m_nUVLampAlarmUse;
	int m_nAAPass;
	int m_nInspectionPass;
	int m_nEpoxyPass;
	int m_nEpoxyInspPass;

	double m_dOffsetPrevUV_X;
	double m_dOffsetPrevUV_Y;
	double m_dOffsetPrevUV_Z;
	double m_dOffsetPrevUV_Tx;
	double m_dOffsetPrevUV_Ty;
	double m_dOffsetPrevUV_Th;
	
	double m_dEolPcbOffset_Tx;
	double m_dEolPcbOffset_Ty;

	double m_dPCBVacuumDelay;
	double m_dPCBGripDelay;
	double m_dLENSGripDelay;
	double m_dPCBGripUpDelay;
	double m_dLaserTimeOut;
	double m_dFinalDelay;
	double m_dBondingDelay;
	double m_dCcdDelay;
	
	int m_nPinStopUse;				// 포거핀 사용량 STOP 사용여부
	int m_nSensorCnt;				// 포거핀 사용량
	int m_nLight[MAX_LIGHT_COUNT];
	int m_CurrentChartIndex;
	int m_nMasterModeUse;
	int m_nInspOKPass;				//eol insp 양품 판정 패스 투입 후 바코드 확인 후 바로 배출요청
	int m_nAlignPass;
	int m_nRawSavePass;
	int m_nJxlSavePass;
	int m_nIdleReasonPass;


	int m_LxData[2];		//0 = 5000k , 1 = 6500K
	int m_LxVal;
	//double m_dOcOffsetX;
	//double m_dOcOffsetY;

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

	int m_nDirection[MAX_SFR_INSP_COUNT];
	int m_nPatternDirection[MAX_SFR_INSP_COUNT];
    
    double m_dLinePulse;
	
	int		m_dDemosaic;

    CPoint m_nPatternPos[MAX_LAST_INSP_COUNT];
    CPoint m_nPatternSize[MAX_LAST_INSP_COUNT];
    CPoint m_MTF_ROI_Pos[2][MAX_SFR_INSP_COUNT];		//0 = 자동 찾기 1 = 패턴이미지 찾기

	double m_dChartRotation;

    double m_dChartHfovMin;
    double m_dChartHfovMax;

    double m_dChartVfovMin;
    double m_dChartVfovMax;

	double m_dChartDistortionMin;
	double m_dChartDistortionMax;




	

	//int m_nModelType;
};


typedef struct STRUC_SFR_INSP
{
	int nDataCount[MAX_SFR_INSP_COUNT];

	float fMotorPos[MAX_CCD_STEP_COUNT][6];
	float fImageAlign[MAX_CCD_STEP_COUNT][4];

	CRect clRectROI[4];

	CRect	clRect[MAX_LAST_INSP_COUNT];			// 챠트에 보이는 19개 사각형 인식 좌표..
	CRect	_64_Sfr_Rect[MAX_SFR_INSP_COUNT];		// 챠트에 보이는 64개 SFR 검사 영역..

	bool mChartRectFind[MAX_LAST_INSP_COUNT];



	CDMPoint	Sfr_Pos[MAX_CCD_STEP_COUNT][MAX_LAST_INSP_COUNT];			// AA Tile 계산 용 코너 부 마크 좌표
	float	fSFR_AVR_N4[MAX_CCD_STEP_COUNT][MAX_LAST_INSP_COUNT];
	int nMaxIndex[MAX_LAST_INSP_COUNT];
	double dMaxPos[MAX_LAST_INSP_COUNT];


	float	fSfrN8[MAX_CCD_STEP_COUNT][5];

	float	fSftAll[MAX_CCD_STEP_COUNT][20];


	double dAver_MTF[MAX_SFR_INSP_COUNT][10];	//max 10회
	double dAver_Var[10];//max 20회

	float	_64_fSfrN4[MAX_SFR_INSP_COUNT];
	float	_64_fSfrN8[MAX_SFR_INSP_COUNT];

    double	_fAverSfr[MAX_LAST_INSP_COUNT];

	double dSfrDataX[MAX_SFR_INSP_COUNT][MAX_SFR_DATA_COUNT];
	double dSfrDataY[MAX_SFR_INSP_COUNT][MAX_SFR_DATA_COUNT];

	

	double dTiltX;
	double dTiltY;
	double dLogTiltX[2];
	double dLogTiltY[2];
	double dLogMotorTX;
	double dLogMotorTY;


} STRUC_SFR_INSP;



///////////////////////////////////////////////////////////////////////////////
//
//	MarkData Class
//
class CMarkData
{
public:
	CMarkData();
	~CMarkData();

	void SetUnit(int nUnit) { m_nUnit = nUnit; }
	void LoadData(TCHAR* szModelName);
	void SaveData(TCHAR* szModelName);
	void CopyBackup(TCHAR* szModelName);

public:
	int m_nSmooth[MAX_MARK_COUNT];
	CRect m_clRectRoi[MAX_MARK_COUNT];
	int m_nUnit;
};


///////////////////////////////////////////////////////////////////////////////
//
//	TaskWork Calss
//
class CTaskWork
{
public:
	CTaskWork();
	~CTaskWork();

public:
	void LoadData();
	void SaveData();

	void PinLoadData();
	void PinSaveData();
    void InitLogSet();
	void InitSfrInsp();
    void InitSfrSpec();
	void SetUnit(int nUnit);
public:
	int bRecv_Lgit_Pp_select;

	int bRecv_S6F12_Process_State_Change;
	int bRecv_S6F12_PP_Selected;
	int bRecv_S6F12_PP_UpLoad_Completed;
	int bRecv_S6F12_Lot_Processing_Started;
	int bRecv_S6F12_Lot_Apd;
	int bRecv_S6F12_Lot_Processing_Completed;
	int bRecv_S6F12_Lot_Processing_Completed_Ack;

	int bRecv_S7F25_Formatted_Process_Program;

	int bRecv_S2F49_PP_UpLoad_Confirm;		//Confirm or Fail
	int bRecv_S2F49_LG_Lot_Start;	//Start or Id Fail
public:
	int m_nUnit;							// UNIT NO

	TCHAR m_szLotID[SIZE_OF_100BYTE];		// LOT ID
	TCHAR m_szChipID[SIZE_OF_100BYTE];		// CHIIP ID(BCR)

	TCHAR m_szBinaryFile[SIZE_OF_1K];		// 펌웨어 비교 원본 파일명
	//EEPROM
	//00000000000000000000000PT00463986-A23010A000000000001
	TCHAR m_szManufacturerSerialNumber[SIZE_OF_100BYTE];		//=2304000000000001
	TCHAR m_szRivianPartNumber[SIZE_OF_100BYTE];				//=00000000000000000000000PT00463986-A
	TCHAR m_szTraceabilityDate[SIZE_OF_100BYTE];				//=23010
	TCHAR m_szTraceabilityLocation[SIZE_OF_100BYTE];			//=A
	TCHAR m_szTraceabilityToolNumber[SIZE_OF_100BYTE];			//=000000 
	TCHAR m_szTraceabilitySerialNumber[SIZE_OF_100BYTE];		//=000001
	TCHAR m_szImagePath[SIZE_OF_1K];		// ADD 

	TCHAR m_szI2cSensorLot[SIZE_OF_100BYTE];	//I2C Sensor Id Read


	TCHAR m_szFuseId[SIZE_OF_100BYTE];	//I2C Sensor Id Read
	int m_nAutoFlag;						// AUTO 
	int m_nStartStep;
	int m_nEndStep;

	bool m_bAreaSensorRun;

	int m_nStartLensStep;
	int m_nEndLensStep;

	int m_nCurrentPcbStep;
	int m_nCurrentLensStep;

	DWORD m_dwTickCount;
	DWORD m_dwLensTickCount;
	DWORD m_dwPcbTickCount;
	DWORD m_dwSupportTickCount;

	int mVariationIndex;
	int m_LightTimeCheck;
	
	int mRepetCount;
	int m_ManualMarkIndex;			//수동으로 마크 보정할때 사용 , pcb 보정이냐 , lens 보정이냐 
	bool m_bDispenseCompleteCheck;
	bool m_bLensLaserCompleteCheck;

	int m_nDrawBarStep;
	int m_nCountOfTotalStepAA;
	int m_nCountOfStepAA;
	int m_nCountOfSecondStepAA;
	bool m_bFlagDecreaseSFR;
	bool m_bSecondAA;
	bool m_bFlagFineMove;
	bool m_bFlagRoughMove;
	bool m_bSfrResult;
	int m_nResultCode;

	bool m_bRecvMesBcr;				//mes bcr 수신 여부.

	CRect m_FindCircleRect[MAX_FOV_COUNT];
	CRect m_FindFovRect[MAX_FOV_COUNT];
	CPoint m_clPtCircle[4];

	CDMPoint m_clPtRotationCircle[4];
	CDMPoint m_clPtChartOc;


    CPoint m_clPtFov[MAX_FOV_COUNT];
    CPoint m_clPtSnr[MAX_FOV_COUNT];
	double m_dFOV[5];

	double m_dOpticalPosX;
	double m_dOpticalPosY;
	double m_dOpticalShiftX;
	double m_dOpticalShiftY;

	double m_dOutTx;
	double m_dOutTy;

	int m_nOpticalTh;
	CRect m_clOpticalRoi;

	int m_nTotalWorkCount;
	int m_nTotalOkCount;
	int m_nTotalNgCount;
	int m_nUsePinCount;
	int m_nCcdCount;

	int m_MinMaxIndex[12];
	double m_AligData[MAX_SFR_INSP_COUNT];

	int m_nMTFNgCount;
	int m_nOCNgCount;
	int m_nDistortionNgCount;
	int m_nCurrentNgCount;
	int m_nTestPatternNgCount;
	int m_nDefectInspNgCount;
	int m_nStainInspNgCount;
	int m_nDarkInspNgCount;
	int m_nUniformityNgCount;

	DWORD m_dwCycleTactStartTime;
	DWORD m_dwCycleTactEndTime;

	double m_dTotalTactTime;
	DWORD m_dwTotalTactTime;
	double m_dAlignTackTime;
	DWORD m_dwAlignTackTime;
	double m_dBcrTackTime;
	DWORD m_dwBcrTackTime;
	double m_dLaserTactTime;
	DWORD m_dwLaserTactTime;
	double m_dAATactTime;
	DWORD m_dwAATactTime;
	double m_dInspTactTime;
	DWORD m_dwInspTactTime;	
		
	//STURC_OS_CHECK	m_stOsCheck;
	STRUC_SFR_INSP	m_stSfrInsp;
	//STRUC_DEFECT_INSP m_stDefectInsp;

	int m_nRecvAlignData;
	CDMotor m_dAlignData;
	CDMPoint dpFind;
	double m_dSensorAlign[3];		// X,Y,T

	double m_dHolderAlign[3];		// X,Y,T

	double m_dLensAlign[3];		// X,Y,T


	double m_dAADataX;
	double m_dAADataY;
	double m_dAADataTh;

	double m_dDBDataX;
	double m_dDBDataY;
	double m_dDBDataTh;
	double m_dDBDataInTx;
	double m_dDBDataInTy;
	double m_dDBDataOutTx;
	double m_dDBDataOutTy;

	bool m_bRecvLaserTilt;
	int m_nLaserTiltIndex;
	double m_dLaserVal[4];
	CDMPoint m_clDpLaserPos[4];
	double m_dLaserTiltX[2];
	double m_dLaserTiltY[2];
	
	double m_dDataOffsetX[2];
	double m_dDataOffsetY[2];
	double m_dDataOffsetTh[2];

	double m_dImgShiftX;
	double m_dImgShiftY;
	double m_dImgShiftTh;

	double m_dEolChartShiftX;
	double m_dEolChartShiftY;


	double m_dOcResultX;
	double m_dOcResultY;
    double m_d0cResultTH;
	int m_nRetryCount;
	int m_nWideCenterRetryCount;
	float m_fFps;
	int m_nEmission;
	bool m_nEmissionRun;
	int m_nEpoxyCompl;					// 도포 완료 했는지 확인.
	int m_nLensLoading;					// Lens 넘겼는 지 확인.

	int m_nRawSumCount;

	int grabFailCount;
	/*bool m_bFlagMoveLensBonding;
	bool m_bFlagMoveLensComplete;	
	bool m_bFlagMoveLensLoading;*/		// LENS PICKUP 이동 중..Z
	int m_ContactCount;
	int m_IoRetry;
	bool m_bLensTransferChk;			// MAIN LENS TRANSFER 위치 체크 간섭
	bool m_bWaitLensBonding;			// LENS BONDING 대기중...
	bool m_bMovingLens;					// LENS 이동중...
	bool m_bMoveLensLoading;			// LENS BUFFER에 LOADING 중...
	
	bool m_bLensMovePickup;				// LENS BUFFER에 PICKUP하러 이동중..
	bool m_bLensBufferLensOn;				// LENS BUFFER에 제품 여부 확인
	int  m_nComplType;					// 완제품 OK/이물NG/해상력NG

	bool m_bLensSocketIF[MAX_LENS_IF_COUNT];
	bool m_bPcbSocketIF[MAX_PCB_IF_COUNT];
	bool m_bUldSocketIF[MAX_ULD_IF_COUNT];
	
	bool m_bDoorInterlock;
	bool m_bLensInterLock;
	bool m_bPcbInterLock;

	bool m_bManualAAMove;
	bool m_bManualLaserPos;				// TRUE : 내부, FALSE : 외부

	bool m_bManualTest;
	bool m_bInputSignal;
	bool m_bOutputSignal;

	bool m_bPcbExist;

	bool m_bOutputCheck[20];		
	//0 = Relative Illumination			[Color Shading] 2종
	//1 = Color Uniformity				[Color Uniformity]
	//2 = SNR & Row/Col. Noise			[FPN] 2종
	//3 = Blemish						[LCB, Ymean, FDF]
	//4 = Defect (light & dark)			[All Defect Pixel (Rivian)]
	//5 = White Balance					[Relative Illumination X]
	//6 = Lens Shading					[Color Shading]
	//7 = Dark Pixel Uniformity (dark)	[Color Sensitivity - Mean]
	//8 = White Balance (dark)			[FPN]
	//9 = Row/Col. Noise (dark)			[IR Filter]
	bool bIdleTimeExceed;
	TCHAR m_szIdleStartTime[SIZE_OF_100BYTE];
	TCHAR m_szIdleEndTime[SIZE_OF_100BYTE];

	//[0]BCR , [1]전류 , [2]I2C , [3]OC , [4]MTF , [5]DISTORTION , [6]STAIN , [7]RI , [8]DEFECT
    std::vector<int> m_vDirection;
    std::vector<double> m_vFrquency;
    std::vector<double> m_vOffset;
    std::vector<double> m_vSFR;
    std::vector<double> m_vThreshold;
    std::vector<TROIPoint> m_vROI;



	std::vector<char> BinOrgBuffer;
	bool m_bFirmwareStop;
	int BinOrgBufferSize;



};




class CMandoInspLog
{
public:
	CMandoInspLog();
	~CMandoInspLog();

	void InitData();
	void SaveLogAfterAA(int nUnit);			//AA후(UV전) Log Data

	void DrawNGOverlay(int nCh);	//NG항목 Overlay Draw
	void NGCheck(CString strNg);
public:
	SYSTEMTIME	m_stInspTime;		//검사 시작 시간 저장

	CString		m_sBarcodeID;			//바코드명
	double		m_dTilteOffset[2];	//PCB<->Lens 변위 측정 편차[TX, TY]
	double		m_dPCBOffset[3];	//PCB<->Lens Offset 편차[X/Y/T]
	bool		m_bInspRes;			//결과
	CString		m_sNGList;



	CRectPos m_ChartVertex[50];	//김성봉 책임 SHM모델사용 차트 꼭짓점 좌표 23개 사용

	CPoint m_ShmFovPoint[MAX_FOV_FIND_COUNT];
	CString		m_sI2C;				//TestPattern 검사 틀린 갯수
	bool m_TpTestResult[2];
	//-------------------------------------------------------------------------------------
	//검사 결과
	//-------------------------------------------------------------------------------------
	//RI = func_Insp_ColorShading
	double m_dRiMinR[2];	//0 = 5000k , 1 = Dark
	double m_dRiMinGr[2];	//0 = 5000k , 1 = Dark
	double m_dRiMinGb[2];	//0 = 5000k , 1 = Dark
	double m_dRiMinB[2];	//0 = 5000k , 1 = Dark

	double m_dRiMinRG[2];	//0 = 5000k , 1 = Dark
	double m_dRiMinBG[2];	//0 = 5000k , 1 = Dark
	double m_dRiMaxRG[2];	//0 = 5000k , 1 = Dark
	double m_dRiMaxBG[2];	//0 = 5000k , 1 = Dark
	//
	//
    double      m_dOCResult[2];
	double		m_dFov;
	double		m_dDistortion;
	double		m_dSnr;
	double		m_dRotate;
	double      m_Tilt[2];
	double		m_dCurrent;			//전류 측정값
	double		m_dDefect[2];		//Defect검사[White/Black]
	double		m_dStain[2];
	double		m_Dark;
	double		m_RI;
	double		m_ColorUniformity;		//이미지 두장 필요
	double      m_ColorSensitivity;

	//온도 측정
	double      m_dTemperatureResult[3];
	double      m_dHumidity;

	//voltage
	double      m_dVoltageVal[4];
	double		dVoltage;		

	//Saturation
	double      m_dSaturationResult[3];	//0 = min , 1 = max

	//Ir Filter
	double      m_dIrFilterResult[3];

	//Color reproduction
	double      m_dColorReproductionResult[4];
	//
	//Lens Shading
	int m_LogLensShadingR[2][221];
	int m_LogLensShadingGr[2][221];
	int m_LogLensShadingGb[2][221];
	int m_LogLensShadingB[2][221];

	double	m_LogLensShadingAvg[2][12];		//min , avg , max
    //-------------------------------------------------------------------------------------
    //DEFECT
	double  m_LogDefectDarkInDark;
	double  m_LogDefectBrightInDark;
	double  m_LogDefectDarkInBright;
	double  m_LogDefectBrightInBright;

	double  m_LogDefectClusterDarkInDark;
	double  m_LogDefectClusterBrightInDark;
	double  m_LogDefectClusterDarkInBright;
	double  m_LogDefectClusterBrightInBright;

	double m_Hot;
	double m_Dead;
	double m_Row;
	double m_Column;


	double  m_LogDefectBright;
    double  m_LogDefectDark;
    double  m_LogDefectHot;

	double  m_LogDefectBrightCouplet;
	double  m_LogDefectDarkCouplet;
	double  m_LogDefectHotCouplet;

    double  m_LogDefectBrightCluster;
    double  m_LogDefectDarkCluster;
    double  m_LogDefectHotCluster;

    double  m_LogDefectDarkHorLine;
    double  m_LogDefectDarkVerLine;
    double  m_LogDefectBrightHorLine;
    double  m_LogDefectBrightVerLine;
    double  m_LogDefectColumnFPN[4];//Red Cr Cb Blue 1 0 3 2
    //

	double		m_UvBefore_OC_X;          //890
	double		m_UvBefore_OC_Y;          //930
	double		m_UvBefore_OC_DelatX;     //-20
	double		m_UvBefore_OC_DelatY;     //20
	double		m_UvAfter_OC_X;          //890
	double		m_UvAfter_OC_Y;          //930
	double		m_UvAfter_OC_DelatX;     //-20
	double		m_UvAfter_OC_DelatY;     //20


	double		m_LogIC_DelatX;     //-20
	double		m_LogIC_DelatY;     //20
    //
    double      m_LogDistortion;

    //
	double   m_UvBeforeSFR[MAX_SFR_INSP_COUNT];
	double   m_UvAfterSFR[MAX_SFR_INSP_COUNT];

	double      m_4FDiff;
	double      m_7FDiff;


	double	m_Uniformity[10];
	double   m_UvBeforeSFR_0F_Diff;
	double   m_UvBeforeSFR_5F_Diff;
	double   m_UvBeforeSFR_85F_Diff;
	double   m_UvBeforeSFR_5F_Diff_A;
	double   m_UvBeforeSFR_85F_Diff_A;

	double   m_UvAfterSFR_0F_Diff;
	double   m_UvAfterSFR_5F_Diff;
	double   m_UvAfterSFR_85F_Diff;
	double   m_UvAfterSFR_5F_Diff_A;
	double   m_UvAfterSFR_85F_Diff_A;


	double  m_UvBefore_Rotate;
	double  m_UvAfter_Rotate;

	double m_SaturationBrightAvg;
    //
    double  m_LogBlemishBlackSpot;
    double  m_LogBlemishLcb;
	double  m_LogBlemishRU_Ymean;
	double  m_LogBlemishFPF;

	double  m_LogBlemishBlackSpotMaxCenter;

	double  m_LogBlemishLcbMaxCenter;
	double  m_LogBlemishLcbMaxEdge;
	double  m_LogBlemishLcbMaxCorner;

	double  m_LogBlemishYmeanMaxCenter;
	double  m_LogBlemishYmeanMaxEdge;
	double  m_LogBlemishYmeanMaxCorner;

	double m_LogBlemishFdfMaxCenter;
	double m_LogBlemishFdfMaxEdge;
	double m_LogBlemishFdfMaxCorner;
    //
	double m_Log_ColorSensitivity_Result[3][7];//[4];	//[0 = 3000k , 1 = 5000k , 2 = Dark][0=R,1=Gr,2=Gb,3=B]
	



    double m_Log_CS_RG_6500K;
    double m_Log_CS_BG_6500K;
    double m_Log_CS_GrGb_6500K;
    double m_Log_CS_RC_5000k;
    double m_Log_CS_BC_5000k;
    double m_Log_CS_CrCb_5000k;
    
    //
    //RI
    double m_Log_RI_RED[100];
    double m_Log_RI_CLEARR[100];
    double m_Log_RI_CLEARB[100];
    double m_Log_RI_BLUE[100];
	//
	double m_Log_RI[5][2];
	double m_Log_Shading[4];		//
	//
	double m_Log_RI_CenterIntensity;
	double m_Log_RI_Up_Ratio;
	double m_Log_RI_Left_Ratio;
	double m_Log_RI_Right_Ratio;
	double m_Log_RI_Down_Ratio;
	double m_Log_RI_Difference;
	//
	double m_Log_RI_CornerVar_R;
	double m_Log_RI_CornerVar_Cr;
	double m_Log_RI_CornerVar_Cb;
	double m_Log_RI_CornerVar_B;
    //
    double m_Log_RI_Center_R;
    double m_Log_RI_Center_Cr;
    double m_Log_RI_Center_Cb;
    double m_Log_RI_Center_B;
    //
    double m_Log_RI_LT_Ratio_R;
    double m_Log_RI_LT_Ratio_Cr;
    double m_Log_RI_LT_Ratio_Cb;
    double m_Log_RI_LT_Ratio_B;
    //
    double m_Log_RI_RT_Ratio_R;
    double m_Log_RI_RT_Ratio_Cr;
    double m_Log_RI_RT_Ratio_Cb;
    double m_Log_RI_RT_Ratio_B;
    //
    double m_Log_RI_LB_Ratio_R;
    double m_Log_RI_LB_Ratio_Cr;
    double m_Log_RI_LB_Ratio_Cb;
    double m_Log_RI_LB_Ratio_B;
    //
    double m_Log_RI_RB_Ratio_R;
    double m_Log_RI_RB_Ratio_Cr;
    double m_Log_RI_RB_Ratio_Cb;
    double m_Log_RI_RB_Ratio_B;

    //
    double m_Log_SNR_SNR;
    double m_Log_SNR_DR;
	double m_Log_Fpn5000kResult[3][4];	////0 = SNR , 1 = ROW , 2 = COLUMN
	double m_Log_FpnDarkResult[3][4];	////0 = SNR , 1 = ROW , 2 = COLUMN

	//double m_Log_SnrResult[3][4];	
	//double m_Log_NoiseResult[3][4];

    //
    double  m_Log_CU_LT_Delta_RG;
    double  m_Log_CU_LT_Delta_RB;
    double  m_Log_CU_LT_Delta_BG;

    double  m_Log_CU_RT_Delta_RG;
    double  m_Log_CU_RT_Delta_RB;
    double  m_Log_CU_RT_Delta_BG;

    double  m_Log_CU_LB_Delta_RG;
    double  m_Log_CU_LB_Delta_RB;
    double  m_Log_CU_LB_Delta_BG;

    double  m_Log_CU_RB_Delta_RG;
    double  m_Log_CU_RB_Delta_RB;
    double  m_Log_CU_RB_Delta_BG;
    //
    double  m_Log_FOV_H_FOV;
    double  m_Log_FOV_V_FOV;
    double  m_Log_FOV_D_FOV;
    

    //
    //-------------------------------------------------------------------------------------

	int iNGCnt;
	CString sDispNG[200];
	double getMaxMin(int pos, int type);		//lim 240430
	//CMandoInspLog();
	

    //-------------------------------------------------------------------------------------




	double		m_dShading65FC[2];
	double		m_dShading85FC[2];





	//double		m_d60lpmm[24];		//60lp/mm (17Point)
	//double		m_d67lpmm[24];     //67lp/mm (17Point)

	double		m_dMinData[3];    //20150601

								  //! Main화면 NG List Overlay 관련 변수
	int			m_nNGCnt;
	CString		m_sDispNG[50];
	CString		m_sSendNGName;
};


class CMandoSfrSpec
{
public:
	CMandoSfrSpec();
	~CMandoSfrSpec();

	void SetUnit(int nUnit){ m_nUnit = nUnit; }

	void Load();
	void Save();
public:
	//신규 개조 -> 60LP, C/P은 제거, Only 67LP만.
	//기존 60LP, C/P 추가한 부분이 많고, C/P은 재사용할수 도 있으니
	//배열 3개는 그래도 가고, [0]배열, [2]배열은 사용 하지 않는다.
	// AA장비 변수
	//double	m_dAASFR_Spec[MAX_SFR_INSP_COUNT][2];//[3];	
	//210825
	// [INDEX][0][0]  : AA
	// [INDEX][0][1]  : EOL


	// [0][0] : UV전 60lp, [0][1] : UV전 67lp, [0][2] : UV전 C/P, 
	// [1][0] : UV후 60,   [1][1] : UV후 67lp, [1][2] : UV후 C/P
	// 화상검사기 변수

	double	m_dAASFR_SumAveSpec[MAX_SFR_INSP_SUMAVE_CNT][2];	//0 = UV전 / EOL , 1 = AA UV후만 사용
	double	m_dAASFR_DiffMaxSpec[5][2];	//0 = AA , 1 = EOL
	double m_dINSPSFR_Spec[MAX_SFR_INSP_COUNT][2];

	bool m_bInsp60Lp;
	bool m_bInsp67Lp;
	bool m_bInspCp;
	double m_dSfrOffsetMultiply;
private:
	int m_nUnit;
};


