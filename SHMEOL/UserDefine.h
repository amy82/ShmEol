//-----------------------------------------------------------------------------
//
//	GlobalDefine.h
//
//-----------------------------------------------------------------------------
#ifndef __USERDEFINE_H__
#define __USERDEFINE_H__

#define DEF_TITLE					_T("XPENG")
//
#define DEF_VERSION					_T("AutoInsp_190718_2")         //다이얼로그 추가전

#define ON_LINE_MODE
//#define USER_DEBUG
#define		NORINDA_MODE

#ifdef NORINDA_MODE
	//#define		ON_LINE_VISION
#else
		#ifdef		ON_LINE_MODE
		#define		ON_LINE_MOTOR
		#define		ON_LINE_LAN
		#define		ON_LINE_DIO
		#define		ON_LINE_VISION
		////	////////#define		ON_LINE_UV_LAMP
		#define		ON_LINE_KEYENCE
		#define		ON_LINE_MONITOR
		#endif
#endif

#ifdef USER_DEBUG
#define DEBUG_SLEEP_INTERVAL		500
#endif

#define UNIT_AA1					0
#define UNIT_AA2					1

///////////////////////////////////////////////////////////////////////////////
//
//	Program Path
//
#define BASE_DATA_PATH				_T("D:\\EVMS\\TP\\Data")
#define BASE_MODEL_PATH				_T("D:\\EVMS\\TP\\Data\\Model")
#define BASE_LOG_PATH				_T("D:\\EVMS\\TP\\Log")
#define BASE_INSP_PATH				_T("D:\\EVMS\\TP\\Log\\Inspection")
#define BASE_ALARM_PATH				_T("D:\\EVMS\\TP\\Alarm")

///////////////////////////////////////////////////////////////////////////////
//
//
//
enum MODE_TYPE						{ MODE_STOP = 0, MODE_READY, MODE_AUTO, MODE_PAUSE, MODE_ERR };	//!! 모드 상태 변수 0=정지상태, 1=운전준비상태, 2=자동운전상태, 3=일시정지상태

enum LIGHT_TYPE						{ LIGHT_CHART_CH1 = 0, LIGHT_CHART_CH2, LIGHT_OC_SENSOR, LIGHT_OC_COMPL, MAX_LIGHT_COUNT };


enum LIGHT_CH						{ LIGHT_CH_CHART2_1 = 0, LIGHT_CH_CHART2_2 = 1, LIGHT_CH_OC2 = 2, LIGHT_CH_CHART1_1 = 4, LIGHT_CH_CHART1_2 = 5, LIGHT_CH_OC1 = 6};

enum MOTOR_SPEED					{ SPEED_AUTO_H = 0, SPEED_AUTO_L, SPEED_MANUAL, MOTOR_SPEED_COUNT };				//!! 모터 구동 속도
enum TEACH_POS						{ WAIT_POS = 0, SUPPLY_POS, SENSOR_ALIGN_POS, LASER_IN_POS, LASER_OUT_POS, BONDING_POS, DARK_POS, DEFECT_POS, MAX_POS_COUNT };

static TCHAR* POS_NAME[MAX_POS_COUNT] = { _T("대기위치"), _T("공급위치"), _T("SENSOR ALIGN"), _T("LASER IN"), _T("LASER OUT") ,_T("BONDING위치") ,_T("DARK위치"), _T("DEFECT위치") };
static TCHAR* POS_NAME2[MAX_POS_COUNT] = { _T("WAIT_POS"), _T("SUPPLY_POS"), _T("SENSOR_ALIGN_POS"), _T("LASER_IN_POS"), _T("LASER_OUT_POS") ,_T("BONDING_POS") ,_T("DARK_POS"), _T("DEFECT_POS") };

enum BOX_MOVE_TYPE					{ MOVE_POS = 0, MOVE_SIZE };
enum SFR_MOVE_TYPE					{ MOVE_UP = 0, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

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

enum PCB_SOCKET_IF					{ PCB_ITF_CHK = 0, PCB_ALR, PCB_ALR_ACK, PCB_ALR_OK, PCB_VAC_REQ, PCB_CLR_ACK, PCB_ALI, PCB_BCR, PBN_ITF_CHK, PBN_BLW_REQ, PBN_CLR_REQ, PCB_ESC, PBN_ESC_ACK,
									  PCB_ITF_ACK, PCB_PROD_CHK,MES_LOG_ACK, MAX_PCB_IF_COUNT };
enum LEN_SOCKET_IF					{ LEN_ITF_CHK, LEN_VAC_REQ, LEN_CLR_ACK, LEN_ALI, LEN_BCR, LNE_ITF_CHK, LNE_BLW_REQ, LNE_CLR_REQ, LEN_ESC, LNE_ESC_ACK, LEN_VAC_ACK, LEN_ITF_ACK, MAX_LENS_IF_COUNT };
enum ULD_SOCKET_IF					{ ULD_ITF_CHK, ULD_BLW_REQ, ULD_CLR_ACK, ULD_ESC_ACK, ULE_ITF_CHK, ULE_BLW_REQ, ULE_CLR_ACK, ULD_VAC_REQ, ULE_ESC_ACK, MAX_ULD_IF_COUNT};

enum	DialogType { DLG_MANUAL, DLG_CCD, DLG_TEACHING, DLG_IO, DLG_SET, DLG_ALARM, MAX_DLG_NO };

///////////////////////////////////////////////////////////////////////////////
//
//	COUNT DEFINE
//
#define MAX_UNIT_COUNT					2

#define MAX_POPUP_COUNT					5

#define MAX_MODEL_COUNT					20
#define MAX_MARK_COUNT					4

#define	MAX_LAST_INSP_COUNT				11		// AA 최종 이미지에서 챠트 보이는 전체 마크 중 기존 검사 마크 이외에 추가 SFR 값 측정 해야 될 마크 개수..
#define MAX_DOME_INSP_ADD				2		// DOME 차트 사용시 13개 ROI 사용
#define	MAX_SFR_INSP_COUNT				24		// AA 최종 이미지에서 SFR 값 측정 해야 될 ROI 개수..
#define MAX_CCD_STEP_COUNT				150
#define MAX_SFR_DATA_COUNT				4000
#define MAX_DEFECT_COUNT				10
///////////////////////////////////////////////////////////////////////////////
//
//	SIZE DEFINE
//
#define	M_PI							3.14159265358979323846f

#define SIZE_OF_100BYTE					100
#define SIZE_OF_1K						1024
#define SIZE_OF_5K						(SIZE_OF_1K * 5)

#define CCD1_CAM_SIZE_X					1820
#define CCD1_CAM_SIZE_Y					940

#define CCD1_DISP_SIZE_X				640
#define CCD1_DISP_SIZE_Y				330

#define CCD2_CAM_SIZE_X					1280
#define CCD2_CAM_SIZE_Y					1080

#define CCD2_DISP_SIZE_X				640
#define CCD2_DISP_SIZE_Y				540

#define MAX_MARK_SIZE_X					1000
#define MAX_MARK_SIZE_Y					900

#define AXIS_MOVE_TIME					10000
#define ENCORDER_GAP					0.01

#define MAX_MOTOR_MOVE_TIME				30000

#define MAX_GRAPH_COUNT					3
#define MAX_GRAPH_OVERLAP_COUNT			5
#define MAX_GRAPH_PIXEL_SIZE			8192
///////////////////////////////////////////////////////////////////////////////
//
//
#define		MAIN_BG_COLOR               RGB(47,60,67)// RGB(20,30,10)
#define		GRID_COLOR_TITLE			RGB(142,168,219)//RGB(0,155,155)
//
#define		GRID_COLOR_BLACK            RGB(0,0,0)
#define		GRID_COLOR_WHITE            RGB(255,255,255)
#define		GRID_COLOR_GREEN			RGB(128, 255, 128)
#define		GRID_COLOR_RED				RGB(255, 94, 164)
#define		GRID_COLOR_SPARE_MOTOR		RGB(128, 128, 128)
#define		GRID_COLOR_SELECT			RGB(244, 216, 234)
#define		GRID_COLOR_DIO_OUT			RGB(128, 255, 128)
#define		GRID_COLOR_DIO_IN			RGB(255, 94, 164)
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

#define	SFR_RIGHT_DOWN_INDEX_1_40		8
#define	SFR_RIGHT_DOWN_INDEX_2_40		9

#define	SFR_LEFT_DOWN_INDEX_1_40		10
#define	SFR_LEFT_DOWN_INDEX_2_40		11

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


//----------------------------------------------------------------

#define SOCKET_MAIN			"192.168.3.3"
#define SOCKET_AA1			"192.168.3.1"
#define SOCKET_AA2			"192.168.3.2"

#define UNIT1					0
#define UNIT2					1


#define		MAIN_DLG_WIDTH		1920
#define		MAIN_DLG_HEIGHT		1080

#define		MIN_TITLE_HEIGHT	60

#define		CCD_WIDTH		720//(MAIN_DLG_WIDTH/2) - 240
#define		CCD_HEIGHT		570//750 - 180



#if ____MODEL_NAME == VISTEON
#define		LAST_MARK_CNT				9// AA 최종 이미지에서 챠트 보이는 전체 마크 중 기존 검사 마크 이외에 추가 SFR 값 측정 해야 될 마크 개수..
#elif ____MODEL_NAME == XPENT_RVC
#define		LAST_MARK_CNT				9
#elif  (____MODEL_NAME == SALLEN_RIVIN ||____MODEL_NAME == CONTISIDEMIRRO || ____MODEL_NAME == DCY11_AVM || ____MODEL_NAME == DCY11_RVC || ____MODEL_NAME == SONY_7M  || ____MODEL_NAME == XPENT_SIDE) 
#define		LAST_MARK_CNT				5
#endif


#define		SFR_INSP_CNT				12		// AA 최종 이미지에서 SFR 값 측정 해야 될 ROI 개수..

#if ____MODEL_NAME == VISTEON
#define		MTF_INSP_CNT				20	// AA 최종 이미지에서 MTF 값 측정 해야 될 ROI 개수..
#elif ____MODEL_NAME == XPENT_RVC
#define		MTF_INSP_CNT				20	// AA 최종 이미지에서 MTF 값 측정 해야 될 ROI 개수..
#elif  (____MODEL_NAME == SALLEN_RIVIN ||____MODEL_NAME == CONTISIDEMIRRO || ____MODEL_NAME == DCY11_AVM || ____MODEL_NAME == DCY11_RVC || ____MODEL_NAME == SONY_7M  || ____MODEL_NAME == XPENT_SIDE) 
#define		MTF_INSP_CNT				12
#endif

#define		SFR_ROI_VERTICAL			1
#define		SFR_ROI_HORIZONTAL			2

// Cneter SFR 검사 Box 번호..
#define		SFR_CENTER_UP					0	
#define		SFR_CENTER_DOWN					1	
#define		SFR_CENTER_LEFT					2
#define		SFR_CENTER_RIGHT				3

#define		SFR_05_LEFT_UP_H				4	
#define		SFR_05_LEFT_UP_V				5	

#define		SFR_05_RIGHT_UP_H				6
#define		SFR_05_RIGHT_UP_V				7

#define		SFR_05_LEFT_DOWN_H				8	
#define		SFR_05_LEFT_DOWN_V				9	

#define		SFR_05_RIGHT_DOWN_H				10
#define		SFR_05_RIGHT_DOWN_V				11
//--------------------------------------------------------else
#define		SFR_07_LEFT_UP_H				12	
#define		SFR_07_LEFT_UP_V				13	

#define		SFR_07_RIGHT_UP_H				14
#define		SFR_07_RIGHT_UP_V				15

#define		SFR_07_LEFT_DOWN_H				16	
#define		SFR_07_LEFT_DOWN_V				17	

#define		SFR_07_RIGHT_DOWN_H				18
#define		SFR_07_RIGHT_DOWN_V				19
//--------------------------------------------------------


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
#define RGB_CTRL_BG						RGB(55, 73, 93)

#define RGB_COLOR_WHITE					RGB(255, 255, 255)
#define RGB_COLOR_BLACK					RGB(0, 0, 0)
#define RGB_COLOR_RED					RGB(255, 0, 0)
#define RGB_COLOR_GREEN					RGB(0, 255, 0)
#define RGB_COLOR_BLUE					RGB(0, 0, 255)
#define RGB_COLOR_GRAY					RGB(100, 100, 100)

///////////////////////////////////////////////////////////////////////////////
//
//	STRUCTURE DEFINE
//
typedef struct STRUC_LOG_NODE
{
	TCHAR szBuff[SIZE_OF_5K];
	int nBuffSize;
	int nLogType;
	int nUnit;
} STRUC_LOG_NODE;


class CDPoint
{
public:
	CDPoint()
	{
		x = y = 0.0;
	}

public:
	double x;
	double y;
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


typedef struct STRUC_MARK_POS
{
	int nMarkNo;
	double dMarkX;
	double dMarkY;
	double dAngle;
	double dScore;
	CDPoint clDPtMarkSize;
	CDPoint clDPtMarkCenter;
	TCHAR szMode[SIZE_OF_100BYTE];
} STRUC_MARK_POS;

#endif