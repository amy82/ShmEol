//-----------------------------------------------------------------------------
//
//	AXTDefine.h
//
//-----------------------------------------------------------------------------
#ifndef __AXTDEFINE_H__
#define __AXTDEFINE_H__

//#define USER_DEV


#include "C:\\Program Files (x86)\\EzSoftware UC\\AXL(Library)\\C, C++\\AXL.h"
#include "C:\\Program Files (x86)\\EzSoftware UC\\AXL(Library)\\C, C++\\AXM.h"
#include "C:\\Program Files (x86)\\EzSoftware UC\\AXL(Library)\\C, C++\\AXDev.h"
#include "C:\\Program Files (x86)\\EzSoftware UC\\AXL(Library)\\C, C++\\AXHS.h"
#include "C:\\Program Files (x86)\\EzSoftware UC\\AXL(Library)\\C, C++\\AXD.h"

#pragma comment(lib, "C:\\Program Files (x86)\\EzSoftware UC\\AXL(Library)\\Library\\64Bit\\AxL.lib")




#define BOARD_CNT	1

#define ABS			1	
#define REL			0	

#define LINEAR		0		
#define STEPING		1
#define DCMOTOR		2
#define THMOTOR		3           //리밋 접점 바꾸려고 추가



#ifdef	MOTOR_ACC_TYPE_SEC	
#define ACC_CAL		1.0
#else
#define ACC_CAL		9.8 * 1000
#endif



//화상장비
//
enum MOTOR_AXIS { MOTOR_PCB_X = 0, MOTOR_PCB_Y, MOTOR_PCB_Z, MOTOR_PCB_TH, MOTOR_PCB_TX, MOTOR_PCB_TY, MAX_MOTOR_COUNT };
static int  MOTOR_AXIS_NUMBER[MAX_MOTOR_COUNT] = { 0, 1, 2, 3, 4, 5};
static TCHAR* MOTOR_NAME[MAX_MOTOR_COUNT] = { _T("PCB_X"), _T("PCB_Y"), _T("PCB_Z"), _T("PCB_TH"), _T("PCB_TX") , _T("PCB_TY") };

static int  MOTOR_SPEED_MAX[MAX_MOTOR_COUNT] = { 500 , 1000 , 50 , 50 , 50 , 50 };
static int  MOTOR_TYPE[MAX_MOTOR_COUNT] = { LINEAR, LINEAR, STEPING , STEPING , STEPING , STEPING };

// DIR CW : 시계방향(+)
// DIR CCW : 반시계 방향(-)
static long	MOTOR_HOME_DIR[MAX_MOTOR_COUNT] = { DIR_CW, DIR_CW, DIR_CW, DIR_CCW, DIR_CW, DIR_CW };
static long MOTOR_HOME_SIG[MAX_MOTOR_COUNT] = { HomeSensor, HomeSensor, HomeSensor , HomeSensor , HomeSensor , HomeSensor };
#endif

#define	MOTOR_JOG_LOW		0.1		//! JOG_SPEED_LOW
#define	MOTOR_JOG_MID		0.5		//! JOG_SPEED_MID
#define	MOTOR_JOG_HIGH		1.0		//! JOG_SPEED_HIGH

