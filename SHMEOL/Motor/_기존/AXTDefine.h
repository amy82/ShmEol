#ifdef _M_X64
	#include "C:/Program Files (x86)/EzSoftware UC/AXL(Library)/C, C++/AXM.h"
	#include "C:/Program Files (x86)/EzSoftware UC/AXL(Library)/C, C++/AXDev.h"
	#include "C:/Program Files (x86)/EzSoftware UC/AXL(Library)/C, C++/AXHS.h"
	#include "C:/Program Files (x86)/EzSoftware UC/AXL(Library)/C, C++/AXL.h"
	#include "C:/Program Files (x86)/EzSoftware UC/AXL(Library)/C, C++/AXD.h"

	#pragma comment(lib, "C:/Program Files (x86)/EzSoftware UC/AXL(Library)/Library/64Bit/AXL.lib")
#else
	#include "C:/Program Files/EzSoftware UC/AXL(Library)/C, C++/AXM.h"
	#include "C:/Program Files/EzSoftware UC/AXL(Library)/C, C++/AXDev.h"
	#include "C:/Program Files/EzSoftware UC/AXL(Library)/C, C++/AXHS.h"
	#include "C:/Program Files/EzSoftware UC/AXL(Library)/C, C++/AXL.h"
	#include "C:/Program Files/EzSoftware UC/AXL(Library)/C, C++/AXD.h"
	#pragma comment(lib, "C:/Program Files/EzSoftware UC/AXL(Library)/Library/32Bit/AXL.lib")
#endif

#define SleepTimeDelay 5

#define ABS		1	
#define REL		0	

#define LINEAR	0		
#define STEPING	4/*1*/

#define UNIT_CH		2	




#define CUR_MOTOR_NO	8


enum	MOTOR_NUM							{ MotLENS_X, MotLENS_Y, MotLENS_Z, MotLENS_Tx, MotLENS_Ty,  MotPCB_Y, MotPCB_T, MotCL_Y, MAX_MOTOR_NO};

enum	MOTOR_POS							{Wait_Pos,	Loading_Pos,  Bonding_Pos, UnLoading_Pos,  Align_Pos, Interlock_Pos, PCB_Align_Pos , MAX_POS_NO};			//20160717 JJC PCB_Align_Pos추가
enum	AXIS_INIT							{AXIS_X, AXIS_Y, AXIS_T, AXIS_Z, AXIS_XY, AXIS_XT, AXIS_XYT, AXIS_ALL};
static int  MOTOR_TYPE[MAX_MOTOR_NO] =		{LINEAR,	LINEAR,	  LINEAR,   LINEAR,    STEPING,    LINEAR,    LINEAR,     LINEAR};	

//static long	MOTOR_HOME_DIR[MAX_MOTOR_NO] =  { DIR_CCW,   DIR_CW,   DIR_CW,   DIR_CCW,    DIR_CCW,	DIR_CCW,  DIR_CCW , DIR_CW};	
static long	MOTOR_HOME_DIR[MAX_MOTOR_NO] =  { DIR_CW,   DIR_CW,   DIR_CW,   DIR_CCW,    DIR_CCW,	DIR_CW,  DIR_CCW , DIR_CW};	
static long MOTOR_HOME_SIG[MAX_MOTOR_NO] =  {HomeSensor, HomeSensor, HomeSensor, HomeSensor, HomeSensor, HomeSensor, HomeSensor, HomeSensor};	
static char MOTOR_NAME[MAX_MOTOR_NO][50] =	{"Lens X(mm)", "Lens Y(mm)","Lens Z(mm)", "Lens Tx(deg)", "Lens Ty(deg)", "PCB Y(mm)", "PCB Θ(deg)","CL Y(mm)"};
static double MOTOR_MAX_VEL[MAX_MOTOR_NO] = {700000.0,	3600000.0/*2400000.0*/,	700000.0,	700000.0,	700000.0,	3600000.0/*2400000.0*/,	700000.0,	700000.0};

static char POSITION_NAME[MAX_POS_NO][50] =	{"Wait_Pos", "Bonding_Pos", "Wait_Pos", "Loading_Pos","Bonding_Pos"};


#define SleepTimeDelay	5
#define MAX_MODULE_CNT 2 
enum	CYLINDER_IO		{ BACKWARD = 0, FORWARD, CYL_DOWN, CYL_UP};				 
/*enum	CYLINDER_IO_UD	{ CYL_DOWN = 0, CYL_UP};		 */
enum	VACUM_MODE		{ Vacuum_OFF=0, Vacuum_ON, BLOW_ON, BLOW_OFF };
//enum	UV_MODE			{ UV_OFF=0, UV_ON };			//20160314 JJC 임시 주석


#define	LENS_POSITION_WAIT			0x01
#define	LENS_POSITION_LOADING		0x02
#define	LENS_POSITION_BONDING		0x04
#define	LENS_POSITION_ALIGNLOADING	0x08

#define	LENSZ_POSITION_WAIT			0x10
#define	LENSZ_POSITION_LOADING		0x20
#define	LENSZ_POSITION_BONDING		0x40


#define	PCB_POSITION_WAIT	0x01
#define	PCB_POSITION_BONDING	0x02


class CAxis
{
public:
	double		pos[UNIT_CH][MAX_POS_NO];		
	double		m_dLimit_OK;
	double		m_dLimit_Err;

	CAxis()
	{
		for(int j=0; j< UNIT_CH; j++)
			for (int i=0; i< MAX_POS_NO; i++)
				pos[j][i] = 0;

		m_dLimit_OK = 0.05;
		m_dLimit_Err = 3.0;
	};
};

