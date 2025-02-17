//-----------------------------------------------------------------------------
//
//	GlobalDefine.h
//
//-----------------------------------------------------------------------------
#ifndef __GLOBALDEFINE_H__
#define __GLOBALDEFINE_H__


//#define         NORINDA_MODE
//
//
//
//
//
//#define         KUMI_TEST_MODE			//150만 왜곡 , 100는 동일 영상 (구미샘플 맞추려는 의도)
//
//
//
#define  MODEL_FRONT_100					21000			//SHM100  OHC = 150
#define  MODEL_OHC_150						32000			//SHM150  FRONT = 100
//
//
#define ____MACHINE_NAME					MODEL_FRONT_100		//MODEL_IP150

//versionList
//oqa 좌측이 0번ch in , 우측이 1번 out신호
//====================================================================================================
#define				VER_STR										_T("241220_1")			//raw 눈띄울때, 기다리는 시간 40초로 변경
//#define				VER_STR										_T("241217_1")
//#define				VER_STR										_T("241217_1")				//펌웨어 검사중 팝업추가, m_bFirmwareStop

//#define				VER_STR										_T("241214_1")			//z축 홈잡는 속도 줄임
//#define				VER_STR										_T("241213_1")					//IsCertified 라이센서 확인추가 , 이물검사 실패시 리턴

//#define				VER_STR										_T("241125_1")					//원점 동작시 제품 감지될 때만 흡착 확인 1, 1, 1, 3
//#define				VER_STR										_T("241112_1")						//TCHAR m_szBinaryFile[SIZE_OF_1K];  파일명보다 길어서 개수 수정
//#define				VER_STR										_T("241112_1")					//f/w verify 수정 , ri roi 수정 배포[FILE VER:1.2.2.1]

//#define				VER_STR										_T("241107_1")				//LGIT_GRABBER_20240715_01_v2.2.3 변경 펌웨어 확인 , f/w verify 추가중 , ri roi 수정(유동명)
// #define				VER_STR										_T("241030_1")				//jxl, raw 옵션 저장안돼서 다시 공유
//#define				VER_STR										_T("241030_1")				//모터 이동할때마다 흡착확인(auto, manual), 공유함
//#define				VER_STR										_T("241029_1")				//jxl 다시 디코드 확인 , ENC_JXL_SetEncEffort 안에 ui추가
//#define			VER_STR										_T("241028_1")			//ri , fov , color 검사 fail시 변수 초기화 0 , 모터 이동시 흡착확인 , 레이저 측정값 못 얻으면 알람


//#define			VER_STR										_T("241024_1")				//[20241016]Distribute_V2.7.3.7_VS2015  dll 다시 적용
//#define			VER_STR										_T("241022_1")						//ri roi 수정(이미지 중심점으로부터 0.85F 계산, 폴더명 변경, ccd retry 수정
//#define			VER_STR										_T("241016_1")				//[20241016]Distribute_V2.7.3.5_VS2015 다시 적용, [20241016]Distribute_V2.7.3.6_VS2015


//#define			VER_STR										_T("240909_1")			//dll 변경 [20240902]Distribute_V2.7.1.2_VS2015
//#define			VER_STR										_T("240826_1")					//g_clPriInsp[m_nUnit].func_Insp_Version_Read();//AUTO   스텝제외돼서 다시 추가
//#define			VER_STR										_T("240820_1")
//#define			VER_STR										_T("240819_1")
//#define			VER_STR										_T("240813_1")				//[20240716]Distribute_V2.6.9.10_VS2015  dll변경 , 원찾는 코드 변경, g_MilFindCirclePos 원형마크 찾기 변경
//#define			VER_STR										_T("240725_1")			//sfr 그래프 7f추가 , 원형마크 찾는 밝기 변경 , lot으로 모델 체크 추가
//#define			VER_STR										_T("240724_1")				//HoughCircles  param1 바꿔가며 원형마크 찾기
//#define			VER_STR										_T("240722_1")				//바코드 lot으로 모델 체크
//#define			VER_STR										_T("240719_2")			//일시정지일때 빨간불 깜빡
//#define			VER_STR										_T("240719_1")				//배포
//#define			VER_STR										_T("240718_4")			//dll 경로 변경 , sensor voltage 추가 , fov roi 초기화 수정  eol 150도만 yuv 확대
//#define			VER_STR										_T("240718_3")			//th보정 10초과시 알람
//#define			VER_STR										_T("240718_2")			//이물 밝기 센터만 측정
//#define			VER_STR										_T("240718_1")			//bcr 연결,해제 추가 항상 찍히게 수정 , TEST 모드도 배포
//#define			VER_STR										_T("240717_1")			//전류측정 스펙 소수점 3자리로 변경
//#define			VER_STR										_T("240716_4")
//#define			VER_STR										_T("240716_2")			////레이저 4포인트로 다시 변경  ,roi 초기화 수정 , 100도 상/하 반전
//#define			VER_STR										_T("240716_1")				//ri min 최소값 스펙 체크추가 , GetSaturationResult 은 출력만 양불판정x (최규정)
//#define			VER_STR										_T("240715_1")				//전류 최종값에 0.47 나눠라
//#define			VER_STR										_T("240712_1")					//sfr 위치 표기 로그 변경
//#define			VER_STR										_T("240711_3")				//
//#define			VER_STR										_T("240711_2")			//oqa start
//#define			VER_STR										_T("240711_1")			//배열 정리
//#define			VER_STR										_T("240710_2")				//차트검사후 이물검사로 변경 , 이물YUV 삭제 , KUMI_TEST_MODE 모드 추가
//#define			VER_STR										_T("240710_1")				//i2c bit 단위로 읽기 추가
//#define			VER_STR										_T("240709_4")			//YUV OC, COLOR 버튼추가 , RAW 사이즈 체크 검사 유무확인
//#define			VER_STR										_T("240709_3")		//숙소 수정 , SENSOR ID 추가
//#define			VER_STR										_T("240709_2")					//I2C 검사 , CHART BRIGHT , OC BRIGH 검사
//#define			VER_STR										_T("240709_1")				//레이저 위치 변경 우측상단이 1번
//#define			VER_STR										_T("240708_1")					//Laser 3포인트로 변경 , 100도 제품 180도 회전된다고함

//#define			VER_STR										_T("240703_1")				//fov 기존대로 좌표만 남기기 홍석중, 최규정	
//#define			VER_STR										_T("240701_1")				//반복성옵션, g_Grr____LaserMotorPos	반복성 값 저장 로그
//#define			VER_STR										_T("240628_1")			//diff 평균적용, Saturation 적용
//#define			VER_STR										_T("240627_1")			//티칭 값 MOTOR_DATA.ini 파일로 변경 , 밝기값 스펙 적용(g_CheckEolLight)
//#define			VER_STR										_T("240626_1")		//spec 저장, roi reset 추가
//#define			VER_STR										_T("240625_1")			//검사 스펙 정리 , 스펙 적용 완료 , 로그 출력 thread , 큐 변경

//#define			VER_STR										_T("240621_2")			//ri 스펙 정리중 멈춤	
//#define			VER_STR										_T("240621_1")			//도어 수정 , th보정 가중치
//#define			VER_STR										_T("240620_2")			//sfr 평균 검사 추가
//#define			VER_STR										_T("240620_1")			//oqa어느정도 완료	
//#define			VER_STR										_T("240619_1")			//
//#define			VER_STR										_T("240618_1")
//#define			VER_STR										_T("240617_2")			//goodFeaturesToTrack 추가
//#define			VER_STR										_T("240617_2")			//opencv 346 으로 변경
//#define			VER_STR										_T("240617_1")			//ini 파일 로드 추가 yuv ,raw 분리
//#define			VER_STR										_T("240614_1")			//fov roi 추가중
//#define			VER_STR										_T("240613_1")				//eol , oqa 통합 사용
//#define			VER_STR										_T("240611_1")
//#define			VER_STR										_T("240509_1")			//[20240111]Distribute_V2.6.7.8_VS2015  dll 변경
//#define			VER_STR										_T("240507_1")			//DataFormat, OutMode, SensorType, demosic , blacklevel , 8bituse ui추가


//#define			VER_STR										_T("240430_2")				//Voltage 검사 APS_K2 가져옴
//#define			VER_STR									_T("240430_1")				//RI 검사 APS_K2 가져옴
//#define			VER_STR									_T("240429_1")				//SHM 장비 밑작업


//#define ON_DRY_RUN_MODE
//#define OC___LIGHT___OLD				//이물광원 점등시간 채널 분리전 컨트롤러 사용시 정의해라
//

#define ON_LINE_MODE


#ifdef NORINDA_MODE
//#define ON_LINE_SOCKET	
	//#define ON_LINE_MOTOR
	//#define ON_LINE_LASER
	//#define ON_LINE_DIO
	//#define ON_LINE_LIGHT
	#define ON_LINE_CAM
	#define ON_LINE_MIL
	#define ON_LINE_GRABBER
	
#else
	#ifdef ON_LINE_MODE
		#define ON_LINE_DIO
		#define ON_LINE_MOTOR
		#define ON_LINE_CAM
		#define ON_LINE_LASER
		#define ON_LINE_MIL
		#define ON_LINE_GRABBER
		#define ON_LINE_LIGHT
		#define ON_LINE_SOCKET
	#endif
#endif


//=======================================================================

//#define	 ON_ACCESS_DB

#define MOTOR_ACC_TYPE_SEC

#define PCB_TILT_AA		1
#define LENS_TILT_AA	2


//#define ____AA_WAY	PCB_TILT_AA				//<-------Mobis Pcb AA 방식
#define ____AA_WAY	LENS_TILT_AA


#define     GRAPH_NO_USE



#define UNIT_AA1					0
#define UNIT_AA2					1

///////////////////////////////////////////////////////////////////////////////
//
//	Program Path
//

	//EOL , GP12 
#ifdef KUMI_TEST_MODE
	#if (____MACHINE_NAME ==  MODEL_FRONT_100)
	#define BASE_PATH					_T("D:\\EVMS\\TEST_IMAGE_FRONT_100")
	#define BASE_DATA_PATH				_T("D:\\EVMS\\TEST_IMAGE_FRONT_100\\Data")
	#define BASE_ALARM_PATH				_T("D:\\EVMS\\TEST_IMAGE_FRONT_100\\Alarm")
	#define	MIU_DIR				        _T("D:\\EVMS\\TEST_IMAGE_FRONT_100\\Initialize")

#else
	#define BASE_PATH					_T("D:\\EVMS\\TEST_IMAGE_OHC_150")
	#define BASE_DATA_PATH				_T("D:\\EVMS\\TEST_IMAGE_OHC_150\\Data")
	#define BASE_ALARM_PATH				_T("D:\\EVMS\\TEST_IMAGE_OHC_150\\Alarm")
	#define	MIU_DIR				        _T("D:\\EVMS\\TEST_IMAGE_OHC_150\\Initialize")

	#endif
#else
#if (____MACHINE_NAME ==  MODEL_FRONT_100)
	#define BASE_PATH					_T("D:\\EVMS\\SHM_EOL_FRONT_100")
	#define BASE_DATA_PATH				_T("D:\\EVMS\\SHM_EOL_FRONT_100\\Data")
	#define BASE_ALARM_PATH				_T("D:\\EVMS\\SHM_EOL_FRONT_100\\Alarm")
	#define	MIU_DIR						_T("D:\\EVMS\\SHM_EOL_FRONT_100\\Initialize")
	#define	FW_DIR						_T("D:\\EVMS\\SHM_EOL_FRONT_100\\Firmware")

#else
	#define BASE_PATH					_T("D:\\EVMS\\SHM_EOL_OHC_150")
	#define BASE_DATA_PATH				_T("D:\\EVMS\\SHM_EOL_OHC_150\\Data")
	#define BASE_ALARM_PATH				_T("D:\\EVMS\\SHM_EOL_OHC_150\\Alarm")
	#define	MIU_DIR						_T("D:\\EVMS\\SHM_EOL_OHC_150\\Initialize")
	#define	FW_DIR						_T("D:\\EVMS\\SHM_EOL_OHC_150\\Firmware")
	
#endif
#endif


#define	MES_SPEC_DIR				_T("C:\\BMS_MES\\spec")
#define ROOT_PATH					_T("D:\\EVMS")
#define BASE_COMMON_PATH			_T("D:\\EVMS\\Common")
#define BASE_LOG_PATH				_T("D:\\EVMS\\Log")
#define BASE_LOG_TEMP_PATH			_T("D:\\EVMS\\Log\\finalTemp")
#define BASE_INSP_PATH				_T("D:\\EVMS\\Log\\Inspection")
#define BASE_IMAGE_PATH				_T("D:\\EVMS\\Log\\Image")

#define	BASE_DUMP_DIR				_T("D:\\EVMS\\Log\\DumpFile")





///////////////////////////////////////////////////////////////////////////////
#define		MES_VERIFY_SPEC_COUNT		45//42

const int N_RAW_SIZE = 3110400;
const int N_YUV_SIZE = 4147200;



#if 1
static string MesSpecList[MES_VERIFY_SPEC_COUNT] =
{
	"[Current] Current(mA)",
	"[Voltage] Voltage1 (V)",
	"[Nor Flash Memory] ISP Version Check",
	"[Nor Flash Memory] ISP Model Check",
	"[SFR] 0.0F",
	"[SFR] 0.4F LT",
	"[SFR] 0.4F LB",
	"[SFR] 0.4F RB",
	"[SFR] 0.4F RT",
	"[SFR] 0.7F LT",
	"[SFR] 0.7F LB",
	"[SFR] 0.7F RB",
	"[SFR] 0.7F RT",
	"[SFR] 0.4F DIFF",
	"[SFR] 0.7F DIFF",
	"[OC] Optical Center X",
	"[OC] Optical Center Y",
	"[Rotate] Rotate",
	"[FoV] HFoV",
	"[FoV] VFoV",
	"[ColorReproduction] Red",
	"[ColorReproduction] Blue",
	"[ColorReproduction] Green",
	"[ColorReproduction] Black",
	"[Saturation] TOP_Chart_Bright_LT",
	"[Saturation] TOP_Chart_Bright_LB",
	"[Saturation] TOP_Chart_Bright_RB",
	"[Saturation] TOP_Chart_Bright_RT",
	"[Saturation] Side_Chart_Bright_LT",
	"[Saturation] Side_Chart_Bright_LB",
	"[Saturation] Side_Chart_Bright_RT",
	"[Saturation] Side_Chart_Bright_RB",
	"[Saturation] TOP_Chart_Bright_Avg",
	"[Saturation] OC_Bright_Center",
	"[RI] OC_LT_Ratio",
	"[RI] OC_LB_Ratio",
	"[RI] OC_RB_Ratio",
	"[RI] OC_RT_Ratio",
	"[RI] OC_Min_Ratio",
	"[Blemish] LCB",
	"[Blemish] Ymean",
	"[Blemish] FDF",
	"[Sensor Voltage] AVDD",
	"[Sensor Voltage] OVDD",
	"[Sensor Voltage] DVDD"
};
#else
#define		MES_VERIFY_SPEC_COUNT		69
static string strArr[MES_VERIFY_SPEC_COUNT] = {
	"Current",														//0
	"[SFR] 0.0F ROI 1",						"[SFR] 0.0F ROI 2",					//2
	"[SFR] 0.0F ROI 3",						"[SFR] 0.0F ROI 4",					//4
	"[SFR] 0.4F ROI 1",						"[SFR] 0.4F ROI 2",					//6
	"[SFR] 0.4F ROI 3",						"[SFR] 0.4F ROI 4",					//8
	"[SFR] 0.4F ROI 5",						"[SFR] 0.4F ROI 6",					//10
	"[SFR] 0.4F ROI 7",						"[SFR] 0.4F ROI 8",					//12
	"[SFR] 0.7F ROI 1",						"[SFR] 0.7F ROI 2",					//14
	"[SFR] 0.7F ROI 3",						"[SFR] 0.7F ROI 4",					//16
	"[SFR] 0.7F ROI 5",						"[SFR] 0.7F ROI 6",					//18
	"[SFR] 0.7F ROI 7",						"[SFR] 0.7F ROI 8",					//20
	"[SFR] 0.4F DIFF",						"[SFR] 0.7F DIFF",					//22
	"[OC] Delta X",							"[OC] Delta Y",						//24
	"[Rotation] Rotation",					"[FoV] HFoV",						//26
	"[FoV] VFoV",							"[Blemish] FDF",					
	"[Blemish] LCB",						"[Blemish] Ymean",					//28
	"[RI] Center Intensity",				"[RI] RI ROI 1",					//30
	"[RI] RI ROI 2",						"[RI] RI ROI 3",					//32
	"[RI] RI ROI 4",						"[RI] RI Diff",						//34
	"[RI] RI Min Diff",
	"[ColorReproduction] ROI 1",			"[ColorReproduction] ROI 2",		//36
	"[ColorReproduction] ROI 3",			"[ColorReproduction] ROI 4",		//38
	"Voltage",								"[LIGHT]SFR1",
	"[LIGHT]SFR2",							"[LIGHT]SFR3",
	"[LIGHT]SFR4",							"[LIGHT]SFR5",
	"[LIGHT]SFR6",							"[LIGHT]SFR7",
	"[LIGHT]SFR8",							"[LIGHT]SFR9",
	"[LIGHT]OC",							"[Saturation] TOP_Chart_Bright_LT",	
	"[Saturation] TOP_Chart_Bright_LB",		"[Saturation] TOP_Chart_Bright_RB",
	"[Saturation] TOP_Chart_Bright_RT",		"[Saturation] Side_Chart_Bright_LT",
	"[Saturation] Side_Chart_Bright_LB",	"[Saturation] Side_Chart_Bright_RT",
	"[Saturation] Side_Chart_Bright_RB",	"[Saturation] TOP_Chart_Bright_Avg",
	"[RI] OC_LT_Ratio",						"[RI] OC_LB_Ratio",
	"[RI] OC_RB_Ratio",						"[RI] OC_RT_Ratio",
	"[RI] OC_Min_Ratio",					"[Nor Flash Memory] ISP Version Check",
	"[Nor Flash Memory] ISP Model Check"
};
#endif
enum MODE_TYPE	{ MODE_STOP = 0, MODE_READY, MODE_AUTO, MODE_PAUSE, MODE_ERR };	//!! 모드 상태 변수 0=정지상태, 1=운전준비상태, 2=자동운전상태, 3=일시정지상태
enum LIGHT_DATA_INDEX { 
	LIGHT_DATA_TOP_CHART_1 = 0, LIGHT_DATA_OC_WHITE1, LIGHT_DATA_ALIGN_SENSOR, LIGHT_DATA_ALIGN_HOLDER, LIGHT_DATA_ALIGN_LENS,
	LIGHT_DATA_SIDE_CHART_LEFT, LIGHT_DATA_SIDE_CHART_RIGHT, MAX_LIGHT_COUNT };
//
enum EPOXY_POSITION_TYPE { E_RIGHT_DOWN_SITE = 0, E_RIGHT_UP_SITE, E_LEFT_UP_SITE, E_LEFT_DOWN_SITE, MAX_EPOXY_POSITION_TYPE};
//
enum CHART_LIGHT_CH { LIGHT_CHART_CH_1 = 0, LIGHT_CHART_CH_2, LIGHT_CHART_CH_3, LIGHT_CHART_CH_4,
	LIGHT_CHART_CH_5,
	LIGHT_CHART_CH_6,
	LIGHT_CHART_CH_7,
	LIGHT_CHART_CH_8,
	LIGHT_CHART_CH_9,
	LIGHT_CHART_CH_10,
	LIGHT_CHART_CH_11,
	LIGHT_CHART_CH_12,
	LIGHT_CHART_CH_13,
	MAX_CHART_LIGHT_CH
};

enum LEFT_CHART_LIGHT_CH {
	LEFT_CHART_CH_1 = 0, MAX_LEFT_CHART_LIGHT_CH };

enum RIGHT_CHART_LIGHT_CH {
	RIGHT_CHART_CH_1 = 0, MAX_RIGHT_CHART_LIGHT_CH };

enum BACKDU_LIGHT_INDEX { LIGHT_BD_ALIGN_CH1 = 0, LIGHT_BD_OC_CH2, MAX_BACKDU_LIGHT_INDEX};	//LIGHT_OC_CH1

enum FOV_AREA_CHECK { LT_FOV_PIONT = 0, RT_FOV_PIONT, BL_FOV_PIONT, BR_FOV_PIONT, CIRCLE_FOV_PIONT, MAX_FOV_AREA_CHECK };

enum SIDE_OC_LIGHT_INDEX {LIGHT_CHART_LEFT_CH1, LIGHT_CHART_RIGHT_CH2, MAX_SIDE_OC_LIGHT_INDEX };
enum WHITE_LIGHT_INDEX { LIGHT_OC_WHITE_CH1 = 0, LIGHT_OC_WHITE_CH2, LIGHT_OC_WHITE_CH3, LIGHT_OC_WHITE_CH4, MAX_WHITE_LIGHT_COUNT };
enum IR_LIGHT_INDEX {LIGHT_OC_IR_CH1 = 0, LIGHT_OC_IR_CH2, MAX_IR_LIGHT_COUNT };

enum LAMP_TYPE { LAMP_OFF = 0, LAMP_RED, LAMP_GREEN, LAMP_YELLOW };
enum BUZZER_TYPE {BUZZER_OFF = 0, BUZZER_ALARM, BUZZER_ASK};
enum OC_LX_VALUE { OC_1000_LX = 0, OC_2000_LX, OC_3000_LX, OC_4000_LX, MAX_OC_LX_VALUE };
enum SOCKET_TYPE { MES_SOCKET = 0, BCR_SOCKET, MAX_SOCKET_TYPE };

enum IMAGE_TYPE { YUV_CHART = 0, RAW_CHART, RAW_OC, MAX_IMAGE_TYPE};

enum MOTOR_SPEED			{ SPEED_AUTO_H = 0, SPEED_AUTO_L, SPEED_MANUAL, MOTOR_SPEED_COUNT };				//!! 모터 구동 속도
enum TEACH_POS				{ 
	WAIT_POS = 0, 
	SENSOR_ALIGN_POS,
	SUPPLY_POS, UNLOAD_POS, 
	LASER_POS, OC_LIGHT_POS,
	CHART_POS,
	MAX_POS_COUNT };
static TCHAR* POS_NAME[MAX_POS_COUNT] = { 
	_T("WAIT_POS"), 
	_T("ALIGN_POS"),
	_T("SUPPLY_POS"), _T("UNLOAD_POS"), 
	_T("LASER_POS") ,_T("OC_LIGHT_POS") ,
	_T("CHART_POS")
};

enum MODEL_TYPE { LH_MODEL = 0, RH_MODEL, MAX_MODEL_TYPE_2 };

enum MOBIS_MODEL_TYPE { MODERATE_MODEL = 0, NARROW_MODEL, MAX_MODEL_TYPE};
//
enum FOV_TYPE { FOV_INSP = 0, DISTORTION_INSP };
enum FIDUCIAL_MARK_TYPE { DOT_TYPE = 0, GRID_TYPE = 2 };
//FiducialMarkType

enum CUSTOM_THREAD_TYPE { CCD_THREAD = 1, CCD_RETRY_THREAD, TPTEST_THREAD, LENS_LASER_THREAD};
enum CAM_TYPE { VIDEO_CAM = 0, VIDEO_CCD};

enum AA_FIELD_MODE { FILED_05_AA = 0, FIELD_085_AA };

enum BOX_MOVE_TYPE					{ MOVE_POS = 0, MOVE_SIZE };
enum SFR_MOVE_TYPE					{ MOVE_UP = 0, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

enum RAW_CAPTURE_TYPE               { MID_3000K_RAW =0, OC_IR_RAW, MID_6500K_RAW, LOW_LEVEL_RAW, MID_5000k_RAW, UV_BEFORE_CHART_RAW, UV_AFTER_CHART_RAW, OC_RAW_IMAGE, OC_YUV_IMAGE, CHART_RAW_IMAGE, CHART_YUV_IMAGE};

enum INI_TYPE { INI_RAW_IMAGE = 0, INI_YUV_IMAGE, INI_PATH_IMAGE};

enum SFR_TYPE						{ SFR_FIRST = 0, SFR_SECOND, SFR_FINAL, OC_INSP, SFR_BEFORE_UV, SFR_AFTER_UV, SFR_OFFSET_DATA, SFR_AFTER_OFFSET_MOVE, SFR_SHIFT, SFR_TILT};

enum MTF_POS						{ MTF_CENTER, MTF_LEFT_UPPER, MTF_RIGHT_UPPER, MTF_LEFT_BOTTOM, MTF_RIGHT_BOTTOM, MAX_MTF_COUNT };
enum MTF_INSP_MODE					{ MTF_17P = 0, MTF_24P };
enum GRAB_MODE						{ GRAB_SNAP = 0, GRAB_LIVE };
enum CCD_GRAB_MODE					{ CCD_GRAB_STOP = 0, CCD_GRAB_REQUEST, CCD_GRAB_PROCEEDING, CCD_GRAB_PAUSE, CCD_GRAB_LIVE};

enum MEASURE_TYPE					{ MEASURE_START = 0, MEASURE_END, MEASURE_COMPLETE };
enum MOUSE_CLICK_TYPE				{ MOUSE_DRAG = 0, TRACK_DRAG, DISP_MOVE, MEASURE, DIST_CHECK };
enum MOUSE_CURSOR					{ MOVE_ALL = 0, MOVE_WIDTH_LEFT, MOVE_WIDTH_RIGHT, MOVE_HEIGHT_TOP, MOVE_HEIGHT_BOTTOM, MOVE_NW, MOVE_NE, MOVE_SW, MOVE_SE };
enum SQUARE_TYPE					{ SQUARE_RESET = 0, SQUARE_CREATE, SQUARE_RESIZE, SQUARE_MOVE };
enum SQUARE_DIR						{ STANDARD = -1, CENTER, LEFT, TOP, RIGHT, BOTTOM, LEFTTOP, LEFTBOTTOM, RIGHTTOP, RIGHTBOTTOM };

enum PCB_SOCKET_IF					{ PCB_ITF_CHK = 0, PCB_ALR, PCB_ALR_ACK, PCB_ALR_OK, PCB_VAC_REQ, PCB_CLR_ACK, PCB_ALI, PCB_BCR, PCB_MES_ACK, PCB_BCR_USE, PCB_BCR_ERROR, PBN_ITF_CHK, PBN_BLW_REQ, PBN_CLR_REQ, PCB_ESC, PBN_ESC_ACK,
									  PCB_ITF_ACK, PCB_PROD_CHK,MES_ACK, MAX_PCB_IF_COUNT };
enum LEN_SOCKET_IF					{ LEN_SUPPLY_REQ, LEN_SUPPLY_ACK, LEN_CHK_REQ, LEN_CHK_ACK, LEN_CLR_ACK, LEN_ALI, LEN_BCR, LNE_ITF_CHK, LNE_BLW_REQ, LNE_CLR_REQ, LEN_ESC, LNE_ESC_ACK, LEN_VAC_ACK, LEN_ITF_ACK, MAX_LENS_IF_COUNT };
enum ULD_SOCKET_IF					{ ULD_ITF_CHK, ULD_BLW_REQ, ULD_CLR_ACK, ULD_ESC_ACK, ULE_ITF_CHK, ULE_BLW_REQ, ULE_CLR_ACK, ULD_VAC_REQ, ULE_ESC_ACK, MAX_ULD_IF_COUNT};


enum
{
	eMES_CHECK_ONLINE = 0,
	eMES_ALARM,
	eMES_ALARM_RESET,			//추가
	eMES_TRACK_IN,
	eMES_TRACK_OUT,
};


typedef enum _AlarmList {
	eMES_ALARM_TrackIn_Fail = 1,
	eMES_ALARM_TEMP2,
	eMES_ALARM_TEMP3,
	eMES_ALARM_TEMP4,
	eMES_ALARM_TEMP5,
	eMES_ALARM_TEMP6,
	//7
	//8
	//9
	//10
} AlarmList;



//enum OUTPUT_MODE { ASCII_MODE = 0, FLOAT_MODE, DEC_MODE , BLANK_MODE};
enum OUTPUT_MODE { ASCII_MODE = 0, ASCII_MODE_2, FLOAT_MODE, DEC_MODE, HEX_MODE };

enum MARK_MODE { SENSOR_ALIGN_MARK = 0, MAX_MARK_COUNT };//HOLDER_ALIGN_POS, LENS_ALIGN_POS, 

static TCHAR* MARK_ALIGN_NAME[1] =
{
	_T("Sensor Align")
};
static TCHAR* OC_LIGHT_NAME[2] = { _T("5000K"), _T("6500K") };

const int g_Defectcount = 29;
static TCHAR* DEFECT_SPEC_NAME[g_Defectcount] =
{		_T("AnThresholdTypeDarkInDark"),		_T("AnThresholdTypeDarkInBright"),				
		_T("AnThresholdTypeBrightInDark"),		_T("AnThresholdTypeBrightInBright"),		
		_T("AnThresholdTypeLineDefect"),		_T("AnAlgorithmTypeLineDefect"),	
		_T("AdDefectThresholdDarkInDark"),		_T("AdDefectThresholdDarkInBright"),
		_T("AdDefectThresholdBrightInDark"),	_T("AdDefectThresholdBrightInBright"),	
		_T("AdDefectThresholdRowInDark"),		_T("AdDefectThresholdRowInBright"),			
		_T("AdDefectThresholdColumnInDark"),	_T("AdDefectThresholdColumnInBright"),
		_T("AnMaxDarkDefectInDarkNum"),			_T("AnMaxDarkDefectInBrightNum"),		
		_T("AnMaxBrightDefectInDarkNum"),		_T("AnMaxBrightDefectInBrightNum"),		
		_T("AnMaxDarkClusterInDarkNum"),		_T("AnMaxDarkClusterInBrightNum"),
		_T("AnMaxBrightClusterInDarkNum"),		_T("AnMaxBrightClusterInBrightNum"),	
		_T("AnMaxRowDefectNumInDark"),			_T("AnMaxRowDefectNumInBright"),		
		_T("AnMaxColumnDefectNumInDark"),		_T("AnMaxColumnDefectNumInBright"),	
	_T("AnEnableChannel"),
	_T("AnDefectInCluster"),				
	_T("ADefectInClusterChannel")
};

const int g_Occount = 4;
static TCHAR* OC_SPEC_NAME[g_Occount] =
{ 
    _T("AnFiducialMarkNum"), _T("AnFiducialMarkType"),
	_T("AdMin"),			_T("AdMax")
};

static TCHAR* ROTATE_SPEC_NAME[2] =
{
	_T("AdMin"),			_T("AdMax")
};
static TCHAR* TILTX_SPEC_NAME[2] =
{
	_T("AdMin"),			_T("AdMax")
};
static TCHAR* TILTY_SPEC_NAME[2] =
{
	_T("AdMin"),			_T("AdMax")
};
//
const int g_ColorSenscount = 14;//8;
static TCHAR* COLOR_SENS_SPEC_NAME[g_ColorSenscount] =
{ 
		_T("AdSpecDevMinR"),	_T("AdSpecDevMaxR"),
		_T("AdSpecDevMinGr"),	_T("AdSpecDevMaxGr"),
		_T("AdSpecDevMinGb"),	_T("AdSpecDevMaxGb"),
		_T("AdSpecDevMinB"),	_T("AdSpecDevMaxB"),
		_T("AdSpecDevMinRG"),	_T("AdSpecDevMaxRG"),
		_T("AdSpecDevMinBG"),	_T("AdSpecDevMaxBG"),
		_T("AdSpecDevMinGrGb"),	_T("AdSpecDevMaxGrGb")
};
//
const int g_Snrcount = 2;
static TCHAR* SNR_SPEC_NAME[g_Snrcount] =
{ 
	_T("AdSNRThreshold"),_T("AdDRThreshold")
};
//
const int g_Fpncount = 63;
const int g_FpnStart5000k = 15;
const int g_FpnStartDark = 39;
static TCHAR* FPN_SPEC_NAME[g_Fpncount] =		//SNR, ROW , COLUMN NOISE
{
	_T("AnSnrThreshold"),			
	_T("AnRowThreshold"),
	_T("AnColumnThreshold"),
	_T("AnSnrRoiL"),	_T("AnSnrRoiT"),	_T("AnSnrRoiR"),	_T("AnSnrRoiB"),
	_T("AnRowRoiL"),	_T("AnRowRoiT"),	_T("AnRowRoiR"),	_T("AnRowRoiB"),
	_T("AnColumnRoiL"),	_T("AnColumnRoiT"), _T("AnColumnRoiR"), _T("AnColumnRoiB"),
	//15 = SnrRMin, 5000k
	_T("SnrRMin"), _T("SnrRMax"),_T("SnrGrMin"), _T("SnrGrMax"),_T("SnrGbMin"), _T("SnrGbMax"),_T("SnrBMin"), _T("SnrBMax"),
	_T("CFpnRMin"), _T("CFpnRMax"),_T("CFpnGrMin"), _T("CFpnGrMax"),_T("CFpnGbMin"), _T("CFpnGbMax"),_T("CFpnBMin"), _T("CFpnBMax"),
	_T("RFpnRMin"), _T("RFpnRMax"),_T("RFpnGrMin"), _T("RFpnGrMax"),_T("RFpnGbMin"), _T("RFpnGbMax"),_T("RFpnBMin"), _T("RFpnBMax"),
	//39 = SnrRMin2, Dark
	_T("SnrRMin2"), _T("SnrRMax2"),_T("SnrGrMin2"), _T("SnrGrMax2"),_T("SnrGbMin2"), _T("SnrGbMax2"),_T("SnrBMin2"), _T("SnrBMax2"),
	_T("CFpnRMin2"), _T("CFpnRMax2"),_T("CFpnGrMin2"), _T("CFpnGrMax2"),_T("CFpnGbMin2"), _T("CFpnGbMax2"),_T("CFpnBMin2"), _T("CFpnBMax2"),
	_T("RFpnRMin2"), _T("RFpnRMax2"),_T("RFpnGrMi2n"), _T("RFpnGrMax2"),_T("RFpnGbMin2"), _T("RFpnGbMax2"),_T("RFpnBMin2"), _T("RFpnBMax2")
};

const int g_ColorUniformitycount = 14;
static TCHAR* COLOR_UNIFORMITY_SPEC_NAME[g_ColorUniformitycount] =
{ 
		_T("AnGridSizeX"),			_T("AnGridSizeY"),		
		_T("AnColorSpaceType"),		_T("AnMaxDiffType"),
		_T("AspecMaxDiffRG"),		_T("AspecMaxDiffBG"),	
		_T("AspecMaxDiffRB"),		_T("AspecMaxDiffGrGb"), 
		_T("AspecMinDiffRG"),		_T("AspecMinDiffBG"),	
		_T("AspecMinDiffRB"),		_T("AspecMinDiffGrGb"), 
		_T("AspecMinSum"),			_T("AspecMaxSum")
};                                                         
//
const int g_ColorShadingcount = 8;
static TCHAR* COLOR_SHADING_SPEC_NAME[g_ColorShadingcount] =
{
	_T("AdSpecMinR"), _T("AdSpecMinGr"), _T("AdSpecMinGb"),_T("AdSpecMinB"),
	_T("AdSpecMinRG"), _T("AdSpecMinBG"), 
	_T("AdSpecMaxRG"),_T("AdSpecMaxBG")
};
const int g_Ricount = 12;
static TCHAR* RI_SPEC_NAME[g_Ricount] =
{	
	_T("AdSpecRIcornerMin"),					_T("AdSpecRIcornerMax"),
	_T("AnSpecRIminMin"),						_T("AnSpecRIminMax"),
	_T("AnCenterIntensity"),					_T("AnRINormalizeIndex"),
	_T("AnSpecRICenterIntensityMIN"),			_T("AnSpecRICenterIntensityMAX"),
	_T("AnSpecRIRatioMIN"),						_T("AnSpecRIRatioMAX"),
	_T("AnSpecDifferenceMIN"),					_T("AnSpecDifferenceMAX")
};

const int g_Blemishcount = 21;
static TCHAR* STAIN_BLEMISH_SPEC_NAME[g_Blemishcount] = //21개
{ 
    _T("AnBlockWidth"),			_T("AnBlockHeight"),		_T("AnClusterSize"),
    _T("AnDefectInCluster"),	_T("AdDefectRatio"),		_T("AnMaxSingleDefectNum"),
    _T("AbEnableCircle"),		_T("AnPosOffsetX"),			_T("AnPosOffsetY"),
    _T("AdRadiusRatioX"),		_T("AdRadiusRatioY"),		_T("AdThresholdRatio"),
    _T("AdROIRange"),			_T("AnUsedFixedCircle"),	_T("AbEnableMultiCircle"),
    _T("AdZoneSizeRatio1"),		_T("AdZoneSizeRatio2"),		_T("AdZoneSizeRatio3"),
    _T("AdThreshold1"),			_T("AdThreshold2"),			_T("AdThreshold3")
};

const int g_StainLcbcount = 35;
static TCHAR* STAIN_LCB_SPEC_NAME[g_StainLcbcount] =	//35개
{
    _T("AdCenterThreshold"),		_T("AdEdgeThreshold"),		_T("AdCornerThreshold"),		
	_T("AnMaxSingleDefectNum"),
    _T("AnMinDefectWidthHeigh"),	
	_T("AnCenterMaxR"),				_T("AnCenterMaxGR"),			_T("AnCenterMaxGB"),	_T("AnCenterMaxB"),				
	_T("AnEdgeMaxR"),				_T("AnEdgeMaxGR"),				_T("AnEdgeMaxGB"),			_T("AnEdgeMaxB"),				
	_T("AnCornerMaxR"),			_T("AnCornerMaxGR"),			_T("AnCornerMaxGB"),		_T("AnCornerMaxB"),				
	_T("AbEnableCircle"),		_T("AnPosOffsetX"),				_T("AnPosOffsetY"),			
	_T("AdRadiusRatioX"),			_T("AdRadiusRatioY"),		_T("AdThresholdRatio"),			_T("AdROIRange"),				
	_T("AnUsedFixedCircle"),		_T("AbEnableMultiCircle"),		
	_T("AdZoneSizeRatio1"),		_T("AdZoneSizeRatio2"),		_T("AdZoneSizeRatio3"),			
	_T("AdThreshold1"),				_T("AdThreshold2"),			_T("AdThreshold3"),
	_T("AnBlobSize1"),				_T("AnBlobSize2"),			_T("AnBlobSize3")
};

const int g_StainYmeancount = 28;
static TCHAR* STAIN_YMEAN_SPEC_NAME[g_StainYmeancount] =		//25개
{
    _T("AdEdgeSize"),				_T("AdCenterThreshold"),		_T("AdEdgeThreshold"),		
	_T("AdCornerThreshold"),		_T("AnDefecBlockSize"),			_T("AnLscBlockSize"),		
	_T("AnCalcType"),				_T("AnnMaxRecursiveCount"),     _T("AdMaxDefectSize"),		
	_T("AdPixelSize"),
	_T("AbEnableCircle"),
	_T("AnPosOffsetX"),				_T("AnPosOffsetY"),				
	_T("AdRadiusRatioX"),			_T("AdRadiusRatioY"),			
	_T("AdThresholdRatio"),			_T("AdROIRange"),				
	_T("AnUsedFixedCircle"),		_T("AbEnableMultiCircle"),		
	_T("AdZoneSizeRatio1"),			_T("AdZoneSizeRatio2"),			_T("AdZoneSizeRatio3"),			
	_T("AdThreshold1"),				_T("AdThreshold2"),				_T("AdThreshold3"),
	_T("AnBlobSize1"),				_T("AnBlobSize2"),			_T("AnBlobSize3")
};

const int g_StainFdfcount = 30;
static TCHAR* STAIN_FDF_SPEC_NAME[g_StainFdfcount] =		//30개
{
	_T("AdCenterThreshold"),		_T("AdEdgeThreshold"),		_T("AdCornerThreshold"),
	_T("AnMedianFilterWidth"),		_T("AnMedianFilterHeight"),
	_T("AnWidthScaleRatio"),		_T("AnHeightScaleRatio"),
	_T("AnMinDefectWidthHeight"),	_T("AnWindowSize"),
	_T("AnEdgeSize"),				_T("AbEnableChannel"),
	_T("AnMaxSingleDefectNum"),	
	_T("AbEnableCircle"),
	_T("AnPosOffsetX"),				_T("AnPosOffsetY"),
	_T("AdRadiusRatioX"),			_T("AdRadiusRatioY"),
	_T("AdThresholdRatio"),			_T("AdROIRange"),
	_T("AnUsedFixedCircle"),		
	_T("AbEnableMultiCircle"),
	_T("AdZoneSizeRatio1"),			_T("AdZoneSizeRatio2"),			_T("AdZoneSizeRatio3"),
	_T("AdThreshold1"),				_T("AdThreshold2"),				_T("AdThreshold3"),
	_T("AnBlobSize1"),				_T("AnBlobSize2"),			_T("AnBlobSize3")
};

const int g_Iccount = 6;
static TCHAR* IC_SPEC_NAME[g_Iccount] =
{
	_T("AnOpticalCenterSpecX"),		_T("AnOpticalCenterSpecY"),
	_T("AdPixelPitch"),				_T("AdThresholdRatio"),
	_T("AnOCBlocSize"),				_T("AnEdgeTopMargin")
};


const int g_Ircount = 13;// 7;
static TCHAR* IRFILTER_SPEC_NAME[g_Ircount] =
{
	_T("AdMinThreshold"),	_T("AdMaxThreshold"),   _T("AdRoiThreshold"),		
	_T("AnRoiLeft"),	_T("AnRoiTop"), 
	_T("AnRoiRight"), _T("AnRoiBottom"),
	_T("AdFullBrightAvgMin"),_T("AdFullBrightAvgMax"),
	_T("AdRoiBrightAvgMin"),_T("AdRoiBrightAvgMax"),
	_T("AdRoiBrightVarMin"),_T("AdRoiBrightVarMax")
};


const int g_Chartcount = 2;
static TCHAR* CHART_PCB_TYPE[g_Chartcount] =
{
	_T("LEFT"), _T("RIGHT")
};
const int g_Currentcount = 2;
static TCHAR* CURRENT_SPEC_NAME[g_Currentcount] =
{ 
	_T("AdMin_Spec"),		_T("AdMax_Spec") 
};

const int g_7fAvriationcount = 2;
static TCHAR* SFR_7VARIATION_SPEC_NAME[g_7fAvriationcount] =
{
	_T("AdMin_Spec"),		_T("AdMax_Spec")
};

static TCHAR* COLOR_REPRODUCTION_SPEC_NAME[32] =
{
	_T("AdThreshold1"),	_T("AdThreshold2"),   _T("AdThreshold3"), _T("AdThreshold4"),
	_T("AdColorLab1_L"),_T("AdColorLab1_a"),_T("AdColorLab1_b"),
	_T("AdColorLab2_L"),_T("AdColorLab2_a"),_T("AdColorLab2_b"),
	_T("AdColorLab3_L"),_T("AdColorLab3_a"),_T("AdColorLab3_b"),
	_T("AdColorLab4_L"),_T("AdColorLab4_a"),_T("AdColorLab4_b"),
	_T("AdRoi1_Left"),_T("AdRoi1_Top"),_T("AdRoi1_Right"),_T("AdRoi1_Bottom"),
	_T("AdRoi2_Left"),_T("AdRoi2_Top"),_T("AdRoi2_Right"),_T("AdRoi2_Bottom"),
	_T("AdRoi3_Left"),_T("AdRoi3_Top"),_T("AdRoi3_Right"),_T("AdRoi3_Bottom"),
	_T("AdRoi4_Left"),_T("AdRoi4_Top"),_T("AdRoi4_Right"),_T("AdRoi4_Bottom")
};

//
//-------------------------------------------------------------------------------------------
#define		MAIN_BG_COLOR            RGB(0,0,0)// RGB(47,60,67)
#define		TRAY_GOOD_YES            RGB(130,104,141)
#define		TRAY_GOOD_NO             RGB(100,100,100)
#define		TOP_STATIC_COLOR		 RGB(174,54,27)
#define		TOP_STATIC_TEXT_COLOR	 A_COLOR_WHITE
#define		TOP_STATIC_BARCODE_COLOR	 A_COLOR_GREEN
//
#define		SENSOR_ON_COLOR			RGB(254,132,125)
#define		SENSOR_OFF_COLOR		RGB(59,151,154)
//
#define		BOTTOM_BTN_COLOR_ON            RGB(162,158,196)
#define		BOTTOM_BTN_COLOR_OFF           RGB(100,100,100)
//메시지창
#define		MESSAGE_BG_COLOR						RGB(212,223,85)
#define		MESSAGE_TXT_COLOR						RGB(0,0,0)
#define		MESSAGE_BTN_COLOR						RGB(95,95,95)

#define CV_LAVENDER					CV_RGB(230,230,250)
#define CV_GREEN					CV_RGB(0,128,0)
#define CV_LIGHTGREEN				CV_RGB(144,238,144)
#define CV_YELLOW					CV_RGB(255,255,0)
#define CV_BLACK					CV_RGB(0,0,0)
#define CV_RED						CV_RGB(255,0,0)
#define CV_BLUE						CV_RGB(0,0,255)
//-------------------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
//
//	COUNT DEFINE
//
#define MAX_UNIT_COUNT					1//2

#define MAX_CAM_COUNT					1		//Unit 당 카메라 수

#define MAX_POPUP_COUNT					5

#define MAX_MODEL_COUNT					20
//#define MAX_MARK_COUNT					3		//0 = 홀더 Align , 1 = pcb on Lens Align , 2 = Lens Grip Lens Align

#define	MAX_LAST_INSP_COUNT				9//13		// AA 최종 이미지에서 챠트 보이는 전체 마크 중 기존 검사 마크 이외에 추가 SFR 값 측정 해야 될 마크 개수..
#define	MAX_SFR_INSP_COUNT				20//26		// AA 최종 이미지에서 SFR 값 측정 해야 될 ROI 개수..


#define MAX_CCD_STEP_COUNT				150
#define MAX_SFR_DATA_COUNT				4000
#define MAX_DEFECT_COUNT				10


#if (____MACHINE_NAME == MODEL_FRONT_100)
	#define MAX_FOV_COUNT				12		//8//12		//8개 원만 8개
	#define MAX_FOV_FIND_COUNT			16
#else
	#define MAX_FOV_COUNT				10		//8//10		//8개 2=원, 6 = 꼭짓점
	#define MAX_FOV_FIND_COUNT			14
#endif
//#define MAX_FOV_COUNT				8       //
//기존 샘플 100도 = 12 , 150 = 10개


#define MAX_SNR_COUNT				3       //흰,빨,검순서
///////////////////////////////////////////////////////////////////////////////
//
//	SIZE DEFINE
//
#define	M_PI							3.14159265358979323846f

#define		MAIN_DIALOG_SIZE_W				1920
#define		MAIN_DIALOG_SIZE_H				1080


#define SIZE_OF_100BYTE					100
#define SIZE_OF_1K						1024
#define SIZE_OF_5K						10//(SIZE_OF_1K * 5)

#define CCD1_CAM_SIZE_X					1280
#define CCD1_CAM_SIZE_Y					960

#define CCD1_DISP_SIZE_X				910//640//695//640
#define CCD1_DISP_SIZE_Y				470//480//364//330

#define CCD2_CAM_SIZE_X					1280//1280
#define CCD2_CAM_SIZE_Y					960//1080

#define CCD2_DISP_SIZE_X				910///640//695695//640
#define CCD2_DISP_SIZE_Y				470//364364//540

#define MAX_MARK_SIZE_X					1000
#define MAX_MARK_SIZE_Y					900

#define AXIS_MOVE_TIME					10000
#define ENCORDER_GAP					0.09//0.05

#define MAX_MOTOR_MOVE_TIME				50000

#define MAX_IO_TIME						3000

#define MAX_GRAPH_COUNT					3
#define MAX_GRAPH_OVERLAP_COUNT			5
#define MAX_GRAPH_PIXEL_SIZE			8192

#define CAM_SIZE_X				1280//2000//1280
#define CAM_SIZE_Y				960//1500//960

#define		SMALL_CAM_SIZE_X	640	//640			//(CAM_SIZE_X/2+20)			// 영상 화면 Display..
#define		SMALL_CAM_SIZE_Y	480	//470			//(CAM_SIZE_Y/2+15)

#define		CAM_REDUCE_FACTOR_X		(double)SMALL_CAM_SIZE_X/CAM_SIZE_X
#define		CAM_REDUCE_FACTOR_Y		(double)SMALL_CAM_SIZE_Y/CAM_SIZE_Y
///////////////////////////////////////////////////////////////////////////////
//
#define MAX_REC_SIZE 200

#define	SFR_ROI_VERTICAL			0
#define	SFR_ROI_HORIZONTAL			1
//
#define SFR_N_4_POSITION_X				0.125
#define SFR_N_8_POSITION_X				0.0625


// Cneter SFR 검사 Box 번호..
#define	SFR_CENTER_INDEX				0	
#define	SFR_CENTER_INDEX_2				1	
#define	SFR_CENTER_INDEX_3				2
#define	SFR_CENTER_INDEX_4				3

// 0.4 필드 코너부 SFR 검사 Box 번호..
#define	SFR_LEFT_UP_INDEX_1_40			4
#define	SFR_LEFT_UP_INDEX_2_40			5

#define	SFR_RIGHT_UP_INDEX_1_40			6
#define	SFR_RIGHT_UP_INDEX_2_40			7

#define	SFR_LEFT_DOWN_INDEX_1_40		8
#define	SFR_LEFT_DOWN_INDEX_2_40		9

#define	SFR_RIGHT_DOWN_INDEX_1_40		10
#define	SFR_RIGHT_DOWN_INDEX_2_40		11

#define	SFR_LEFT_UP_INDEX_1_80			12
#define	SFR_LEFT_UP_INDEX_2_80			13

#define	SFR_RIGHT_UP_INDEX_1_80			14
#define	SFR_RIGHT_UP_INDEX_2_80			15

#define	SFR_LEFT_DOWN_INDEX_1_80		16
#define	SFR_LEFT_DOWN_INDEX_2_80		17

#define	SFR_RIGHT_DOWN_INDEX_1_80		18
#define	SFR_RIGHT_DOWN_INDEX_2_80		19


#define	SFR_LEFT_CENTER_INDEX_1_40		12
#define	SFR_LEFT_CENTER_INDEX_2_40		13

#define	SFR_RIGHT_CENTER_INDEX_1_40		14
#define	SFR_RIGHT_DCENTER_INDEX_2_40	15


// 0.7 필드 코너부 SFR 검사 Box 번호..						
#define	SFR_LEFT_UP_INDEX				16
#define	SFR_LEFT_UP_INDEX_2				17

#define	SFR_RIGHT_UP_INDEX				18
#define	SFR_RIGHT_UP_INDEX_2			19

#define	SFR_RIGHT_DOWN_INDEX			20
#define	SFR_RIGHT_DOWN_INDEX_2			21

#define	SFR_LEFT_DOWN_INDEX				22
#define	SFR_LEFT_DOWN_INDEX_2			23


// Cneter SFR 검사 Box 번호..
#define	_SFR_CENTER_INDEX				0	
#define	_SFR_CENTER_INDEX_2				1	

// 0.4 필드 코너부 SFR 검사 Box 번호..
#define	_SFR_CENTER_UP_INDEX_1_40		2
#define	_SFR_CENTER_UP_INDEX_2_40		3

#define	_SFR_CENTER_DOWN_INDEX_1_40		4
#define	_SFR_CENTER_DOWN_INDEX_2_40		5

#define	_SFR_CENTER_LEFT_INDEX_1_40		6
#define	_SFR_CENTER_LEFT_INDEX_2_40		7

#define	_SFR_CENTER_RIGHT_INDEX_1_40	8
#define	_SFR_CENTER_RIGHT_INDEX_2_40	9

// 0.58필드 
#define	_SFR_LEFT_UP_INDEX_1_58			10
#define	_SFR_LEFT_UP_INDEX_2_58			11

#define	_SFR_RIGHT_UP_INDEX_1_58		12
#define	_SFR_RIGHT_UP_INDEX_2_58		13

#define	_SFR_LEFT_DOWN_INDEX_1_58		14
#define	_SFR_LEFT_DOWN_INDEX_2_58		15

#define	_SFR_RIGHT_DOWN_INDEX_1_58		16
#define	_SFR_RIGHT_DOWN_INDEX_2_58		17


// 0.90필드 
#define	_SFR_LEFT_UP_INDEX_1_90			18
#define	_SFR_LEFT_UP_INDEX_2_90			19

#define	_SFR_RIGHT_UP_INDEX_1_90		20
#define	_SFR_RIGHT_UP_INDEX_2_90		21

#define	_SFR_LEFT_DOWN_INDEX_1_90		22
#define	_SFR_LEFT_DOWN_INDEX_2_90		23

#define	_SFR_RIGHT_DOWN_INDEX_1_90		24
#define	_SFR_RIGHT_DOWN_INDEX_2_90		25


///////////////////////////////////////////////////////////////////////////////
//
// IMAGE CONVERT
//
#define	BGGR				1	//BGBG
#define RGGB				2	//RGRG
#define GBRG				3	//GBGB
#define GRBG				4	//GRGR
#define RCCC				5	//RCCC
#define CCCR				6	
#define CRCC				7
#define	CCRC				8

///////////////////////////////////////////////////////////////////////////////
//
// COLOR DEFINE
//
#define RGB_DLG_BG						RGB(40, 39, 35)
#define RGB_CTRL_BG						RGB(174,54,27)//RGB(55, 73, 93)

#define RGB_COLOR_WHITE					RGB(255, 255, 255)
#define RGB_COLOR_BLACK					RGB(0, 0, 0)
#define RGB_COLOR_RED					RGB(255, 0, 0)
#define RGB_COLOR_GREEN					RGB(0, 255, 0)
#define RGB_COLOR_BLUE					RGB(0, 0, 255)
#define RGB_COLOR_GRAY					RGB(100, 100, 100)


#define GRID_COLOR_TITLE			    RGB(142,168,219)
#define	GRID_COLOR_BLACK                RGB(0,0,0)
#define	GRID_COLOR_WHITE                RGB(255,255,255)
#define	GRID_COLOR_GREEN			    RGB(128, 255, 128)
#define	GRID_COLOR_RED				    RGB(255, 94, 164)
#define	GRID_COLOR_SPARE_MOTOR		    RGB(128, 128, 128)
#define	GRID_COLOR_SELECT			    RGB(244, 216, 234)
#define	GRID_COLOR_DIO_OUT			    RGB(128, 255, 128)
#define	GRID_COLOR_DIO_IN			    RGB(255, 94, 164)
///////////////////////////////////////////////////////////////////////////////

class CDMPoint//CDPoint
{
public:
	CDMPoint()//CDPoint()
	{
		x = y = 0.0;
	}

public:
	double x;
	double y;
};
class CRectPos
{
public:
	CPoint Pos[10];
	CRectPos()
	{
		for (int i = 0; i < 10; i++)
		{
			Pos[i].x = 0;
			Pos[i].y = 0;
		}
	}
};
class CDMotor
{
public:
	CDMotor()
	{
		x = y = t = 0.0;
	}
public:
	double x;
	double y;
	double t;
};

class CDrawBox
{
public:
	CDrawBox()
	{
		cnt = w = 0;
		left = right = 0.0;
		top = bottom = 0.0;
		centerX = centerY = 0.0;
	}

public:
	int cnt;
	int w;
	double left;
	double right;
	double top;
	double bottom;
	double centerX;
	double centerY;
	COLORREF c;
};

class CDMRect
{
public:
	CDMRect()
	{
		cnt = w = 0;
		left = right = 0.0;
		top = bottom = 0.0;
		centerX = centerY = 0.0;
	}

public:
	int cnt;
	int w;
	double left;
	double right;
	double top;
	double bottom;
	double centerX;
	double centerY;
	COLORREF c;
};

typedef struct STRUC_MARK_POS
{
	int nMarkNo;
	double dMarkCenterX;
	double dMarkCenterY;
	double dAngle;
	double dScore;
	CDMPoint clDPtMarkSize;
	CDMPoint clDPtMarkCenter;
	TCHAR szMode[SIZE_OF_100BYTE];
} STRUC_MARK_POS;

#endif