#include "stdAfx.h"
#include "AxlMotorSet.h"
#include "../XpengInspInsp.h"
#include "../XpengInspInspDlg.h"
#include <math.h>

AxlMotorSet::AxlMotorSet(void)
{
	int iUnit = 0, iAxis;
	dTime = dSTime = 0;

	for (iUnit = 0; iUnit < UNIT_CH; iUnit++)
	{
		for ( iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++ )
		{
			m_bOrgFlag[iUnit][iAxis] = DEF_ORIGIN_NOT;	//원점 상태 초기화
			iHomeProcUsing[iUnit][iAxis] = 0;	//개별 원점 요구 상태 초기화
			m_bAxisState[iUnit][iAxis] = 0;			//서보 On, OFF 초기화.
		}

		m_hThreadHomeAll[iUnit] = NULL;
		m_hThreadHome[iUnit] = NULL;
		m_hThreadReady[iUnit] = NULL;

		bReadyPusher[iUnit] = false;
	}	

	//! Motor 설정 정보 저장 파일의 절대 경로 (Motion Controller Library에서 지원하는 기능)
	m_sMotionSettingFilePath = _T("C:/Program Files/EzSoftware UC/EzSoftware/MotionSetting.mot");
}

AxlMotorSet::~AxlMotorSet(void)
{
	Axl_Close();
}


bool AxlMotorSet::Axl_Init()
{
	int iUnit = 0, iAxis;
	for (iUnit = 0; iUnit < UNIT_CH; iUnit++)
		for ( iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++ )
			m_bOrgFlag[iUnit][iAxis] = CUR_MOTOR_NO;	//원점상태 초기화

	DWORD dwRet = 0;
#ifdef	ON_LINE_MOTOR

	dwRet = AxlOpen(0);			//라이브러리 초기화  0 : 쓰레기값..
	if ( dwRet != AXT_RT_SUCCESS )
	{
		sMsg.Format("모션 보드 초기화를 실패 하였습니다.");
		g_PushLogQueue(sMsg, DEF_TYPE_MOTIONLOG + DEF_LOG_POPUP);
		//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_MOTIONLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
		return false;
	}

	//! 등록된 AXL 사용가능 보드의 개수를 확인한다.
	long lBoardCounts = 0;
	AxlGetBoardCount(&lBoardCounts);
	if ( lBoardCounts <= 0 )
	{
		sMsg.Format("모션 보드 인식을 실패 하였습니다.");
		g_PushLogQueue(sMsg, DEF_TYPE_MOTIONLOG + DEF_LOG_POPUP);
		::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_MOTIONLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
		return false;
	}
	sMsg.Format("AXL 모션 보드 인식 완료...[ Board Count : %d ]", lBoardCounts);
	g_PushLogQueue(sMsg, DEF_TYPE_MOTIONLOG);
	//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_MOTIONLOG, (LPARAM)&sMsg);




	TCHAR* pszPath = NULL;

	pszPath = m_sMotionSettingFilePath.GetBuffer( m_sMotionSettingFilePath.GetLength() + 1 );

	if ( IsExist_Path(m_sMotionSettingFilePath) == true )
	{	//! 모든 축의 초기 값을 지정한 파일에서 읽어 설정한다. 
		if ( AxmMotLoadParaAll(pszPath) != AXT_RT_SUCCESS )
		{
			sMsg.Format("모션 파라미터 파일이 없습니다.");
			g_PushLogQueue(sMsg, DEF_TYPE_SYSTEMLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_SYSTEMLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
			return false;
		}
	}
	else
	{	//! 모든 축의 초기 값을 파일에 저장 한다. 
		AxmMotSaveParaAll(pszPath);    
	}


	m_sMotionSettingFilePath.ReleaseBuffer();

	//! 초기 설정
	for(int iCnt = 0; iCnt < UNIT_CH; iCnt++){
		AmpDisableAll(iCnt);
		Axl_Axisconfig(iCnt);
	}


#endif


	return true;
}


void AxlMotorSet::Axl_Close()
{
	int iUnit = 0, iAxis;

#ifdef ON_LINE_MOTOR

	//! 모든 Motor를 정지한다. 
	for(iAxis=0; iAxis<CUR_MOTOR_NO*UNIT_CH; iAxis++)
		AxmMoveSStop(iAxis);		

	TCHAR* pszPath = NULL;
	pszPath = m_sMotionSettingFilePath.GetBuffer( m_sMotionSettingFilePath.GetLength() + 1 );
	//! 모든 축의 현재 설정값을 파일에 저장 한다. 
	AxmMotSaveParaAll(pszPath);
	m_sMotionSettingFilePath.ReleaseBuffer();

	AxlClose();

#endif


	for (iUnit = 0; iUnit < UNIT_CH; iUnit++)
		for ( iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++ )
			m_bOrgFlag[iUnit][iAxis] = DEF_ORIGIN_NOT;	//원점상태 초기화
}


//! 장비 전체의 Axis의 초기 설정을 진행한다. 
//! [주의 사항] 
//!    1) 반드시, 'Axl_Init' 함수의 'AxmMotLoadParaAll' 함수 호출 후에 이 함수를 호출하여야 한다. 
//!    2) PCI-R1604의 A4N, A5N서보드라이브의 경우(PM제외) Limit/Home/Servo On/Inposition의 Level을 설정 하실 수 없고 High또는 Low로 고정이 되어있습니다. 
//!		  Limit 센서의 A/B접을 바꾸고자 할때는 서보드라이브의 파라메터를 바꾸어야 합니다.
int AxlMotorSet::Axl_Axisconfig(int iUnit) 
{

#ifdef	ON_LINE_MOTOR
	DWORD Status = 0;
	DWORD dwReturn = 0;

	//! 보드내에 인터럽트 사용을 해제 시킨다. (RTEX 지원 안함)
	AxlInterruptDisable();


	//! 시스템에 장착된 축 개수를 확인
	long lAxisCount = 0;
	AxmInfoGetAxisCount(&lAxisCount);
	if ( lAxisCount != CUR_MOTOR_NO*UNIT_CH )
	{
		sMsg.Format("모터 드라이브 개수 불일치[%d / %d].", lAxisCount, CUR_MOTOR_NO*UNIT_CH);
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
		//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
		return -4;
	}

	//sMsg.Format("AXT 모터 드라이브 인식 완료- [ Count : %d ].", lAxisCount);
	//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_SYSTEMLOG , (LPARAM)&sMsg);


	int    iFailed = -1;
	int iStartAxis = CUR_MOTOR_NO * iUnit;
	int iEndAxis = CUR_MOTOR_NO * (iUnit + 1);
	for(int i=iStartAxis; i<iEndAxis; i++)
	{
// 		if(i == 4) continue;
// 		if(i == 12) continue;
		dwReturn = AxmInfoIsInvalidAxisNo(i);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ %s ] 모터 드라이브 인식 실패.",  MOTOR_NAME[i%CUR_MOTOR_NO]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
			iFailed = i;
			continue;
		}


		dwReturn = AxmMotSetMoveUnitPerPulse(i, 1, 1);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ %s ] 모터 드라이브 전자기어비 초기화 실패.", MOTOR_NAME[i%CUR_MOTOR_NO]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
			iFailed = i;	
		}


		dwReturn = AxmMotSetMaxVel(i, MOTOR_MAX_VEL[i%CUR_MOTOR_NO]);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ %s ] 모터 드라이브 최대 속도 설정 실패.", MOTOR_NAME[i%CUR_MOTOR_NO]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
			iFailed = i;			
		}


		dwReturn = AxmMotSetMinVel(i, 1);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ %s ] 모터 드라이브 최소 속도 설정 실패.", MOTOR_NAME[i%CUR_MOTOR_NO]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
			iFailed = i;			
		}

		dwReturn = AxmMotSetAccelUnit(i, UNIT_SEC2);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ %s ] 모터 드라이브 가속도 단위 설정 실패 .",  MOTOR_NAME[i%CUR_MOTOR_NO]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
			iFailed = i;			
		}


		dwReturn = AxmMotSetProfileMode(i, ASYM_S_CURVE_MODE);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ %s ] 모터 S-Curve 가감속 설정 실패.", MOTOR_NAME[i%CUR_MOTOR_NO]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
			iFailed = i;
		}


		dwReturn = AxmMotSetAbsRelMode(i, POS_ABS_MODE);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ %s ] 모터 절대 위치 이동 모드 실패.", MOTOR_NAME[i%CUR_MOTOR_NO]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
			iFailed = i;			
		}

		DWORD	dwHomLevel;
		dwReturn = AxmHomeSetSignalLevel(i, LOW);
		dwReturn = AxmHomeGetSignalLevel(i, &dwHomLevel);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ %s ] 모터 Home level 설정 실패.", MOTOR_NAME[i%CUR_MOTOR_NO]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
			iFailed = i;			
		}




		//! OneHighLowHigh      1펄스 방식, PULSE(Active High)  +방향(DIR=Low)  / -방향(DIR=High)
		//! OneHighHighLow      1펄스 방식, PULSE(Active High)  +방향(DIR=High) / -방향(DIR=Low)
		//! OneLowLowHigh       1펄스 방식, PULSE(Active Low)   +방향(DIR=Low)  / -방향(DIR=High)
		//! OneLowHighLow       1펄스 방식, PULSE(Active Low)   +방향(DIR=High) / -방향(DIR=Low)
		//! TwoCcwCwHigh        2펄스 방식, PULSE(CW:-방향)  DIR(CCW:+방향), Active High
		//! TwoCcwCwLow         2펄스 방식, PULSE(CW:-방향)  DIR(CCW:+방향), Active Low
		//! TwoCwCcwHigh        2펄스 방식, PULSE(CW:+방향)  DIR(CCW:-방향), Active High
		//! TwoCwCcwLow         2펄스 방식, PULSE(CW:+방향)  DIR(CCW:-방향), Active Low		
		if( MOTOR_TYPE[i % CUR_MOTOR_NO] == 4/*STEPING*/)				
		{// Step 모터 드라이브는 출력 방식, 리미트 설정 틀림.
			dwReturn = AxmSignalSetInpos(i, UNUSED);
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sMsg.Format("[ %s ] 모터 Inposition 설정 실패.",  MOTOR_NAME[i%CUR_MOTOR_NO]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
				iFailed = i;
			}

			//dwReturn = AxmMotSetPulseOutMethod(i, TwoCcwCwHigh);//+-
			dwReturn = AxmMotSetPulseOutMethod(i, TwoCwCcwHigh);
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sMsg.Format("[ %s ] 모터 CW/CCW 설정 실패.", MOTOR_NAME[i%CUR_MOTOR_NO]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
				iFailed = i;
			}

			dwReturn = AxmSignalSetStop(i, EMERGENCY_STOP, HIGH);
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sMsg.Format("[ %s ] 모터 비상 정지 설정 실패.", MOTOR_NAME[i%CUR_MOTOR_NO]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
				iFailed = i;			
			}

			dwReturn = AxmSignalSetLimit(i, EMERGENCY_STOP, LOW, LOW);
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sMsg.Format("[ %s ] 모터 Limit 감지 정지 설정 실패.", MOTOR_NAME[i%CUR_MOTOR_NO]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
				iFailed = i;
			}

			dwReturn = AxmMotSetEncInputMethod(i, ObverseSqr4Mode);
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sMsg.Format("[ %s ] 모터 4체배 설정 실패.", MOTOR_NAME[i%CUR_MOTOR_NO]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
				iFailed = i;			
			}


			dwReturn = AxmSignalSetServoOnLevel(i, HIGH);
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sMsg.Format("[ %s ] 모터 Servo In Level 실패.", MOTOR_NAME[i%CUR_MOTOR_NO]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
				iFailed = i;
			}
		}
		else
		{
			dwReturn = AxmSignalSetInpos(i, HIGH);
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sMsg.Format("[ %s ] 모터 Inposition 설정 실패.", MOTOR_NAME[i%CUR_MOTOR_NO]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
				iFailed = i;
			}

			dwReturn = AxmSignalSetStop(i, EMERGENCY_STOP, LOW);
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sMsg.Format("[ %s ] 모터 비상 정지 설정 실패.", MOTOR_NAME[i%CUR_MOTOR_NO]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
				iFailed = i;			
			}

			dwReturn = AxmSignalSetLimit(i, EMERGENCY_STOP, HIGH, HIGH);
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sMsg.Format("[ %s ] 모터 Limit 감지 정지 설정 실패.", MOTOR_NAME[i%CUR_MOTOR_NO]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
				iFailed = i;
			}
		}

		dwReturn = AxmSignalSetServoAlarm(i, HIGH);
		if ( dwReturn != AXT_RT_SUCCESS )
		{
			iFailed = i;			
		}
	}

	if ( iFailed >= 0 )
	{
		return (-1000 - iFailed);
	}

#endif

	return 1;
}

bool AxlMotorSet::AmpEnable(int iUnit, int iAxis)
{//! 지정 축의 Servo-On을 실시


	DWORD level = ENABLE;
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

#ifdef ON_LINE_MOTOR
	StopAxis(iUnit, iAxis);

	//! 이미 Servo On 상태인지 확인한다. 
	AxmSignalIsServoOn(iUseAxis, &level);
	if ( level == ENABLE )	
	{
		m_bAxisState[iUnit][iAxis] = true;
		return true;
	}

	m_bOrgFlag[iUnit][iAxis] = DEF_ORIGIN_NOT;
	AxmSignalServoOn(iUseAxis, ENABLE);	

	Sleep(100);

	AxmSignalIsServoOn(iUseAxis, &level);
	if ( level != ENABLE )
	{
		m_bAxisState[iUnit][iAxis] = false;
		return false;
	}
#endif
	m_bAxisState[iUnit][iAxis] = true;
	return true;
}

bool AxlMotorSet::AmpEnableAll(int iUnit)
{
	bool rtnVal = true;
	DWORD level = ENABLE;
	int i = 0;

	StopAxisAll(iUnit);

	//int iRet_Axis = Axl_Axisconfig();
	//if(iRet_Axis != 1)
	//{
	//	sMsg.Format("서보 모터 드라이브 초기화 실패..");
	//	::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_MOTIONLOG+DEF_MSGP_NG, (LPARAM)&sMsg);
	//	return	false;
	//}

	int iUseAxis; 

	for ( i = 0; i < CUR_MOTOR_NO; i++ )
	{
		if(i == MotLENS_Tx || i == MotLENS_Ty)	continue;
		iUseAxis = iUnit * CUR_MOTOR_NO + i;	//실제 보드 사용 축 번호


//		m_bOrgFlag[iUnit][i] = false;

#ifdef ON_LINE_MOTOR

		AxmSignalIsServoOn(iUseAxis, &level);
		if ( level == ENABLE )	continue;

		AxmSignalServoOn(iUseAxis, ENABLE);	

		SleepHandle(100);
		AxmSignalIsServoOn(iUseAxis, &level);
		if ( level != ENABLE )	
			rtnVal = false;

#endif		
	}

	SleepHandle(500);

	//! 1개라도 Servo On 실패가 있으면, 다시 시도한다. 
	if ( rtnVal == false )
	{

		rtnVal = true;

		for ( i = 0; i < CUR_MOTOR_NO; i++ )
		{

			iUseAxis = iUnit * CUR_MOTOR_NO + i;	//실제 보드 사용 축 번호

#ifdef ON_LINE_MOTOR
			//! 이미 Servo On 상태인지 확인한다. 
			AxmSignalIsServoOn(iUseAxis, &level);
			if ( level == ENABLE )	continue;

			AxmSignalServoOn(iUseAxis, ENABLE);	
			SleepHandle(300);
			AxmSignalIsServoOn(iUseAxis, &level);
			if ( level != ENABLE )	
				rtnVal = false;
#endif		
		}
	}

	if(!rtnVal)
	{
		sMsg.Format("[ ERROR ] AmpEnableAll 실패.");
		::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG, (LPARAM)&sMsg);
	}
	else
	{
		for ( i = 0; i < CUR_MOTOR_NO; i++ )
		{
			m_bAxisState[iUnit][i] = true;
		}
	}

	return rtnVal;
}

double AxlMotorSet::CalcAcc_G(int iUnit, int iAxis)
{
	return sysData.fMotorAcc[iUnit][iAxis] * (9.8 * 1000 * sysData.fMotorResol[iUnit][iAxis]);
}

double AxlMotorSet::CalcDec_G(int iUnit, int iAxis)
{
	return sysData.fMotorDec[iUnit][iAxis] * (9.8 * 1000 * sysData.fMotorResol[iUnit][iAxis]);

}
bool AxlMotorSet::AmpDisable(int iUnit, int iAxis)
{//! 지정 축의 Servo-Off을 실시
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

	m_bOrgFlag[iUnit][iAxis] = DEF_ORIGIN_NOT;
	double dDecel = 0.;

#ifdef ON_LINE_MOTOR

	AxmMoveStop(iUseAxis, dDecel);	
	AxmSignalServoOn(iUseAxis, DISABLE);

	SleepHandle(10);

	if(MOTOR_TYPE[iAxis] == STEPING)	AxmSignalServoAlarmReset(iUseAxis, ENABLE);

#endif

	return true;
}

bool AxlMotorSet::AmpDisableAll(int iUnit)
{
	bool rtnVal = true;
	double dDecel = 0.;
	int iUseAxis = 0;	//실제 보드 사용 축 번호

	for(int i=0; i<CUR_MOTOR_NO; i++)
	{
		iUseAxis = iUnit * CUR_MOTOR_NO + i;
		m_bOrgFlag[iUnit][i] = DEF_ORIGIN_NOT;

#ifdef ON_LINE_MOTOR
		AxmMoveStop(iUseAxis, dDecel);		
		AxmSignalServoOn(iUseAxis, DISABLE);
#endif

		//if(MOTOR_TYPE[i] == STEPING)	AxmSignalServoAlarmReset (iUseAxis, ENABLE);
	}

	SleepHandle(300);

	// 	for(int i=0; i<CUR_MOTOR_NO; i++)
	// 	{
	// 		iUseAxis = iUnit * CUR_MOTOR_NO + i;
	// 
	// 		if(MOTOR_TYPE[i] == STEPING)
	// 			AxmSignalServoAlarmReset (iUseAxis, DISABLE);

	//}

	return true;
}

bool AxlMotorSet::GetAmpEnable(int iUnit, int iAxis)
{//! 지정 축의 Servo-On 신호의 출력 상태를 반환(T=ON, F=OFF 상태)
	DWORD upStatus;
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

	// Servo 알람 확인.
	AxmSignalIsServoOn(iUseAxis, &upStatus);	// upStatus  1: Servo On
	if(upStatus == ACTIVE)	return true;

	m_bOrgFlag[iUnit][iAxis] = DEF_ORIGIN_NOT;
	return false;
}


bool AxlMotorSet::GetAmpEnableAll(int iUnit)
{//! AAB Unit별 Servo-Off 상태가 있을 경우 false
	DWORD upStatus;
	bool rtnVal = true;
	int iUseAxis = 0;	//실제 보드 사용 축 번호

	for(int i=0; i<CUR_MOTOR_NO; i++)
	{
		iUseAxis = iUnit * CUR_MOTOR_NO + i;

		AxmSignalIsServoOn(iUseAxis, &upStatus);	// upStatus  1: Servo On
		if(upStatus != ACTIVE)
		{
			m_bOrgFlag[iUnit][i] = DEF_ORIGIN_NOT;
			rtnVal = false;
		}
	}

	return rtnVal;
}



bool AxlMotorSet::AmpFaultReset(int iUnit, int iAxis)
{//! 알람 Reset후 Servo-On 실시
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호
	double dDecel = 0.;

	m_bOrgFlag[iUnit][iAxis] = DEF_ORIGIN_NOT;

#ifdef ON_LINE_MOTOR

	DWORD level;

	AxmMoveStop(iUseAxis, dDecel);	
	AxmSignalServoOn(iUseAxis, DISABLE);

	AxmSignalServoAlarmReset(iUseAxis, ENABLE);

	SleepHandle(100);

	AxmSignalServoAlarmReset(iUseAxis, DISABLE);
	AxmSignalServoOn(iUseAxis, ENABLE);	

	SleepHandle(100);

	AxmSignalIsServoOn(iUseAxis, &level);
	if ( level != ENABLE )	return false;
#endif

	return true;
}

bool AxlMotorSet::AmpFaultResetAll(int iUnit)
{	

	for(int i=0; i<CUR_MOTOR_NO; i++)
	{
		AmpDisable(iUnit, i);
	}

	SleepHandle(1000);

	for(int i=0; i<CUR_MOTOR_NO; i++)
	{
		AmpEnable(iUnit, i);
	}

	return true;
}

int	AxlMotorSet::AmpFaultCheck(int iUnit)
{//! 알람 신호 확인
	DWORD upStatus;
	int iAmpFaultFlag = 0;

	for(int i=0; i<CUR_MOTOR_NO; i++)
	{
		// 축의 알람 신호 확인
		AxmSignalReadServoAlarm( (iUnit*CUR_MOTOR_NO) + i, &upStatus );

		if(upStatus == ACTIVE)
		{
			iAmpFaultFlag += 0x01<< i;
			//ISJ
			//m_bOrgFlag[iUnit][i] = true;
			m_bOrgFlag[iUnit][i] = DEF_ORIGIN_NOT;
		}
	}

	return iAmpFaultFlag;
}


bool AxlMotorSet::GetAmpFault(int iUnit, int iAxis)
{//! 지정 축의 알람 상태 반환
	DWORD dwRet = 0, use = 0, upStatus = 0;
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호
	CString sMsg;

#ifdef	ON_LINE_MOTOR

	//kdu 150602
	// 	dwRet = AxmSignalGetServoAlarm(iUseAxis, &use);
	// 	if ( dwRet != AXT_RT_SUCCESS )
	// 	{	
	// 		sMsg.Format("알람  코드 : %d || PCB : %d, LENS : %d, LOAD : %d", dwRet, flow[iUnit].iAAStep, flow[iUnit].iLENS_Step, flow[iUnit].iLENS_LoadingStep);
	// 		::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + GetUnitNum(iUnit), (LPARAM)&sMsg);
	// 		return true;
	// 	}
	if ( use == UNUSED )	
		return true;


	// 축의 알람 신호 확인
	dwRet = AxmSignalReadServoAlarm(iUseAxis, &upStatus);
	if ( dwRet != AXT_RT_SUCCESS )
	{
		//		sMsg.Format("알람  코드 : %d || PCB : %d, LENS : %d, LOAD : %d", dwRet, flow[iUnit].iAAStep, flow[iUnit].iLENS_Step, flow[iUnit].iLENS_LoadingStep);
		//		::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + GetUnitNum(iUnit), (LPARAM)&sMsg);
		m_bOrgFlag[iUnit][iAxis] = DEF_ORIGIN_NOT;
		return true;
	}

	if(upStatus == ACTIVE)
	{
		m_bOrgFlag[iUnit][iAxis] = DEF_ORIGIN_NOT;
		return true;
	}
#endif

	return false;
}


//! Motor가 목표 지점에 도착했는지 확인
bool AxlMotorSet::GetInposition(int iUnit, int iAxis)
{//! 지정 축의 Motor가 목표 지점에 도착했는지 확인

	//m_cri_Inposition.Lock();

	DWORD dwRet = 0, use = 0;
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

#ifdef ON_LINE_MOTOR

	//! Inposition 신호 설정 확인
	dwRet = AxmSignalGetInpos(iUseAxis, &use);
	if ( dwRet != AXT_RT_SUCCESS )	
	{
		//m_cri_Inposition.Unlock();
		return false;
	}
	if ( use == UNUSED )		
	{
		//m_cri_Inposition.Unlock();
		return false;
	}

	//! Inpositon 신호의 입력 확인
	DWORD upStatus = INACTIVE;
	dwRet = AxmSignalReadInpos(iUseAxis, &upStatus);
	if ( dwRet != AXT_RT_SUCCESS )
	{
		//m_cri_Inposition.Unlock();
		return false;
	}

	if ( upStatus == INACTIVE )
	{
		//m_cri_Inposition.Unlock();
		return false;
	}

#endif

	//m_cri_Inposition.Unlock();
	return true;
}

bool AxlMotorSet::GetHomeSensor(int iUnit, int iAxis)
{//! 지정 축의 Home 센서 신호의 입력 확인
	DWORD dwRet = 0, upStatus = 0;
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호


#ifdef ON_LINE_MOTOR

	//int ret = home_switch(axis);
	//return ret ? true : false;
	//! Home 신호의 입력 확인
	dwRet = AxmHomeReadSignal(iUseAxis, &upStatus);
	if ( dwRet != AXT_RT_SUCCESS )	return false;
	if ( upStatus == INACTIVE )		return false;

#endif
	return true;
}

bool AxlMotorSet::GetNegaSensor(int iUnit, int iAxis)
{//! 지정 축의 (-)리미트 센서 신호의 입력 확인
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

#ifdef ON_LINE_MOTOR

	DWORD dwRet = 0;
	/*DWORD StopMode, PositiveLevel, NegativeLevel*/;

	//kdu 150602
	// 	dwRet = AxmSignalGetLimit(iUseAxis, &StopMode, &PositiveLevel, &NegativeLevel);
	// 	if ( dwRet != AXT_RT_SUCCESS )		return false;
	// 	if ( NegativeLevel == UNUSED )		return false;

	//return ret ? true : false;
	//! 리미트 센서 입력 상태 확인
	DWORD upPositiveLevel, upNegativeLevel;
	dwRet = AxmSignalReadLimit(iUseAxis, &upPositiveLevel, &upNegativeLevel);
	if ( dwRet != AXT_RT_SUCCESS )		return false;
	if ( upNegativeLevel == ACTIVE )	return true;
#endif

	return false;
}


bool AxlMotorSet::GetPosiSensor(int iUnit, int iAxis)
{//! 지정 축의 (+)리미트 센서 신호의 입력 확인
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

#ifdef ON_LINE_MOTOR

	DWORD dwRet = 0;
	/*DWORD StopMode, PositiveLevel, NegativeLevel*/;

	//kdu 150602
	// 	dwRet = AxmSignalGetLimit(iUseAxis, &StopMode, &PositiveLevel, &NegativeLevel);
	// 	if ( dwRet != AXT_RT_SUCCESS )		return false;
	// 	if ( PositiveLevel == UNUSED )		return false;

	//int ret = pos_switch(axis);
	//return ret ? true : false;
	//! 리미트 센서 입력 상태 확인
	DWORD upPositiveLevel, upNegativeLevel;
	dwRet = AxmSignalReadLimit(iUseAxis, &upPositiveLevel, &upNegativeLevel);
	if ( dwRet != AXT_RT_SUCCESS )		return false;
	if ( upPositiveLevel == ACTIVE )	return true;

#endif

	return false;
}

//! CRC 신호 설정(펄스 출력형 모션 제어기에 한정된 기능)
//! 특정 서보팩의 경우 구동이 완료된 시점에서 또는 리미트센서를 감지한 경우에 
//! 외부에서 CRC(Current Remaining Clear)신호를 받아 서보팩이 가지고 있는 잔여 펄스를 지워주어야 하는 경우가 발생한다.
//! [주의 사항] CRC 신호 설정 기능은 펄스 출력형 모션제어기(PCI-N804/404, RTEX-PM)에서만 사용할 수 있는 기능이다.
bool AxlMotorSet::ActCRC(int iUnit, int iAxis)
{
	DWORD dwReturn = 0;
	long  BoardNo = 0;
	long  ModulePos = 0;
	DWORD ModuleID = 0;
	DWORD uLevel, uMethod;
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

	//! ModuleID (Module의 종류)
	//! 'AXHS.h' 파일 : 'C:\Program Files\EzSoftware UC\AXL(Library)\C, C++' 폴더안에 있음 (AXT_FUNC_MODULE)	
	//!      AXT_SMC_R1V04    = 0x09,   // CAMC-QI, 1 Axis, For RTEX SLAVE only	
	dwReturn = AxmInfoGetAxis(iUseAxis, &BoardNo, &ModulePos, &ModuleID);
	if ( dwReturn != AXT_RT_SUCCESS )	return false;
	if ( ModuleID != AXT_SMC_R1V04 )	return false;


	//! 지정 축에 CRC 신호 사용 여부 설정을 반환 한다.
	dwReturn = AxmCrcGetMaskLevel(iUseAxis, &uLevel, &uMethod);
	if ( dwReturn != AXT_RT_SUCCESS )	return false;
	//! CRC 신호 사용안함
	if ( uLevel == UNUSED )				return false;


	//! 지정 축에 CRC 신호를 강제적으로 출력을 발생시킨다. (일정 시간 동안만 작용시킴)
	AxmCrcSetOutput(iUseAxis, ENABLE);
	SleepHandle(10);
	AxmCrcSetOutput(iUseAxis, DISABLE);

	return true;
}

bool AxlMotorSet::GetStopAxis(int iUnit, int iAxis)
{//! 모터 정지 상태 반환(T=정지, F=구동중)

	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

#ifdef ON_LINE_MOTOR
	//! 축의 구동 상태를 확인
	DWORD Status;
	DWORD dwRet = AxmStatusReadInMotion(iUseAxis, &Status);
	if ( dwRet != AXT_RT_SUCCESS )			return false;
	if (Status == FALSE)					return true;	//! 모터가 정지하였습니다.
#endif

	return false;
}



bool AxlMotorSet::StopAxis(int iUnit, int iAxis)
{//! 감속 정지
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

#ifdef ON_LINE_MOTOR

	AxmMoveSStop(iUseAxis);
	//Stop_Home_Search(iUnit, iAxis);

	double t_duration = 0.;
	while(!GetStopAxis(iUnit, iAxis))
	{
		DoSleepEvents();

		//t_duration = timeChk.Measure_Time(0);

		if(t_duration>1000)
		{
			sMsg.Format("[ %s ] 모터 정지 시간 초과.", MOTOR_NAME[iAxis]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);

			return false;
		}

		SleepHandle(5);
	}	
#endif

	return true;
}

bool AxlMotorSet::StopAxisAll(int iUnit)
{
	bool runFlag[CUR_MOTOR_NO] = {0, };
	int iUseAxis = 0;	//실제 보드 사용 축 번호

#ifdef ON_LINE_MOTOR
	for(int i=0; i<CUR_MOTOR_NO; i++)
	{
		iUseAxis = iUnit * CUR_MOTOR_NO + i;	

		//! 현재 구동 중인 처음에 사용자가 입력한 가속도만큼 모션 동작을 감속하면서 정지하는 함수이다. 
		AxmMoveSStop(iUseAxis);

		runFlag[i] = 1;
	}
#endif

	double t_duration = 0.0;
	int i = 0;
	while(1)
	{
		if(t_duration>1000)
		{
			sMsg.Format("전체 모터 정지 시간 초과. [1 sec]");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
			return false;
		}

		for(i=0; i<CUR_MOTOR_NO; i++)
		{
			if (runFlag[i])
			{
#ifdef ON_LINE_MOTOR
				if(!GetStopAxis( iUnit, i ))
#endif
				{
					runFlag[i] = 0;
					break;
				}
			}
		}

		if(i==CUR_MOTOR_NO)	break;

		DoSleepEvents();

		SleepHandle(5);
	}

	return true;
}


double AxlMotorSet::GetEncoderPos(int iUnit, int iAxis)
{//! Linear 모터 위치 좌표 반환
	double pos = 0;
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

#ifdef ON_LINE_MOTOR
	if( MOTOR_TYPE[iAxis] == STEPING )	AxmStatusGetCmdPos(iUseAxis, &pos);	
	else								AxmStatusGetActPos(iUseAxis, &pos);
#endif

	pos /= sysData.fMotorResol[iUnit][iAxis];

	return (float)pos;
}

double AxlMotorSet::GetEncoderPos_Disp(int iUnit, int iAxis)
{//! Linear 모터 위치좌표에서 강제 원점 좌표까지 계산된 좌표 반환
	double pos = 0;
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

#ifdef ON_LINE_MOTOR
	AxmStatusGetActPos(iUseAxis, &pos);
#endif

	pos /= sysData.fMotorResol[iUnit][iAxis];
	pos -= sysData.dOrgDataset[iUnit][iAxis];

	return (float)pos;
}

double AxlMotorSet::GetCommandPos(int iUnit, int iAxis)
{//! Steping 모터 위치 좌표 반환
	double pos = 0;
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

#ifdef ON_LINE_MOTOR

	AxmStatusGetCmdPos(iUseAxis, &pos);	
#endif

	pos /= sysData.fMotorResol[iUnit][iAxis];

	return (float)pos;
}

double AxlMotorSet::GetCommandPos_Disp(int iUnit, int iAxis)
{//! Steping 모터 위치좌표에서 강제 원점 좌표까지 계산된 좌표 반환	
	double pos = 0;
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

#ifdef ON_LINE_MOTOR

	AxmStatusGetCmdPos(iUseAxis, &pos);	
#endif

	pos /= sysData.fMotorResol[iUnit][iAxis];
	pos -= sysData.dOrgDataset[iUnit][iAxis];

	return (float)pos;
}

int AxlMotorSet::GetEncoderPulse(int iUnit, int iAxis)
{
   double pos = 0.0;
   int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;   //실제 보드 사용 축 번호

#ifdef ON_LINE_MOTOR
   if( MOTOR_TYPE[iAxis] == STEPING )   AxmStatusGetCmdPos(iUseAxis, &pos);   
   else                       			AxmStatusGetActPos(iUseAxis, &pos);
#endif

   return (int)pos;
}

int AxlMotorSet::GetCommandPulse(int iUnit, int iAxis)
{
   double pos = 0.0;
   int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;   //실제 보드 사용 축 번호

#ifdef ON_LINE_MOTOR
   AxmStatusGetCmdPos(iUseAxis, &pos);   
#endif

   return (int)pos;
}


double AxlMotorSet::CalcAccFromAccTime(double dVel, double dTime)
{//! 가속도 = 속도/(가속 시간)으로 계산
	double dRet = 0.;

	if ( fabs(dTime) < 0.001 )
	{						
		dRet = dVel / 2.;		//! 가속 시간이 너무 짧아서 강제로 가속 시간을 2 sec로 고정
	}
	else
	{
		dRet = dVel / dTime;
		dRet *= 1000.;			//! 단위 변환 msec -> sec
	}

	return dRet;
}



BOOL AxlMotorSet::JogMove(int iUnit, int iAxis, double dVel)
{//! 설정한 속도로 구동한다.
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

	if(GetAmpFault(iUnit, iAxis))	
		return FALSE;

	double dAcc = CalcAcc_G(iUnit,iAxis); //sysData.fMotorAcc[iUnit][iAxis];
	double dDec = CalcDec_G(iUnit,iAxis); //sysData.fMotorDec[iUnit][iAxis];

	int ret = 0;
	DWORD dwRet = 0;
#ifdef	ON_LINE_MOTOR
	dwRet = AxmMoveVel(iUseAxis, dVel, dAcc, dDec);
#endif
	ret = dwRet;

	return ret;
}

BOOL AxlMotorSet::JogStop(int iUnit, int iAxis)
{//! 지정한 축의 구동을 감속정지합니다.
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

	AxmMoveSStop(iUseAxis);

#ifdef	ON_LINE_MOTOR
	//CTimeChecker timeChk;

	//timeChk.Init_Time();
	//timeChk.Start_Time();
	double t_duration = 0.0;

	while(!GetStopAxis(iUnit, iAxis))
	{
		DoSleepEvents();

		//t_duration = timeChk.Measure_Time(0);

		if(t_duration > 1000)
		{
			sMsg.Format("JOG 이동 정지 시간 초과. [1 sec]");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP, (LPARAM)&sMsg);
			return false;
		}
	}
#endif

	return true;
}


//! 특정 위치 (Limit 센서나 Home 센서)에서 자동으로 멈추도록 하여 모터를 움직일 때 사용한다.
//! 지정 축에서 설정된 신호를 검출한다
//! 리미트 센서신호나 원점 센서신호, 서보 드라이버의 Z상 신호 또는 범용 입력 신호들의 Edge를 검출할 수 있다.
//! 주로 원점검색 구동 함수 구현 시 사용하는 함수이다.
//! [주의 사항] 
//!		1) End Limit 센서를 찾을 경우, 신호의 Active Level 상태를 검출한다.
//!     2) Emergency Stop으로 사용할 경우, 가감속이 무시되며 지정된 속도로 가속 급정지하게된다.
bool AxlMotorSet::MoveAxis_To_Sensor(int axis, strMove_Input_Signal_Search *pstrInput)
{//! 특정 위치 (Limit 센서나 Home 센서)에서 자동으로 멈추도록 하여 모터를 움직일 때 사용한다.

	//! 입력값 확인
	if ( pstrInput == NULL )	return false;

	double dVel   = pstrInput->dVel;
	double dAccel = pstrInput->dAccel;
	long lDetectSignal = -1, lSignalEdge = -1, lSignalMethod = -1;


	//! lDetectSignal 설정
	if ( pstrInput->bEndLimit_Negative == true )	lDetectSignal = NegEndLimit;
	if ( pstrInput->bEndLimit_Positive == true )	lDetectSignal = PosEndLimit;
	if ( pstrInput->bHomeSensor == true )			lDetectSignal = HomeSensor;
	if ( pstrInput->bPhase_Encoder_Z == true )		lDetectSignal = EncodZPhase;

	//! lSignalEdge 설정
	if ( pstrInput->bEdge_Down == true )			lSignalEdge = SIGNAL_DOWN_EDGE;
	if ( pstrInput->bEdge_Up == true )				lSignalEdge = SIGNAL_UP_EDGE;

	//! lSignalMethod 설정
	if ( pstrInput->bEmergency == true )			lSignalMethod = EMERGENCY_STOP;
	if ( pstrInput->bSlowDown == true )				lSignalMethod = SLOWDOWN_STOP;


	//! 입력값 확인
	if ( lDetectSignal == NegEndLimit )		dVel = -1 * fabs(pstrInput->dVel);
	else									dVel = fabs(pstrInput->dVel);


	if ( dAccel < 0. )			return false;
	if ( lDetectSignal < 0 )	return false;
	if ( lSignalEdge < 0 )		return false;
	if ( lSignalMethod < 0 )	return false;


	DWORD dwReturn = 0;
	//! 지정 축에서 설정된 신호를 검출할 때까지 모터를 움직인다. 
	dwReturn = AxmMoveSignalSearch(axis, dVel, dAccel, lDetectSignal, lSignalEdge, lSignalMethod);
	if ( dwReturn != AXT_RT_SUCCESS )	return false;

	return true;
}


////! GUI 화면에서 설정한 길이만큼 움직인다. (상대 이동)
////! GUI 화면에서 많이 사용되는 기능이라서 따로 함수를 만들다. 
//bool AxlMotorSet::Move_From_GUI(int iUnit, int axis, int iID_GUI, CWnd* pParentWnd, bool bPlus)
//{//! GUI 화면에서 설정한 길이만큼 움직인다. (상대 이동)
//	if ( pParentWnd == NULL )			return false;
//	if ( bMotorMoving[iUnit][axis] == true )	return false;
//	bMotorMoving[iUnit][axis] = true;
//
//	CString sGetTemp = _T("");
//	GetString_FromUI(iID_GUI, pParentWnd, sGetTemp);
//
//	double dGetTemp = atof(sGetTemp);
//	if ( dGetTemp > 3. )		dGetTemp = 3.;	
//	else if (dGetTemp < -3 )	dGetTemp = -3;
//
//	if ( bPlus == false )	dGetTemp *= (-1.);
//
//	MoveAxis(iUnit, axis, REL, dGetTemp, 4);
//	bMotorMoving[iUnit][axis] = false;
//
//	return true;
//}

bool AxlMotorSet::Move_From_AbsRel(int iUnit, int iAxis, double dVal, bool bPlus)
{
	if ( bMotorMoving[iUnit][iAxis] == true )	return false;

	bMotorMoving[iUnit][iAxis] = true;
	if( bPlus == false )	dVal *= (-1.);

	if( Task[iUnit].AutoFlag == 1 )		MoveAxis(iUnit, iAxis, REL, dVal, sysData.fMotorSpeed_Auto[iUnit][iAxis]);
	else								MoveAxis(iUnit, iAxis, REL, dVal, sysData.fMotorSpeed[iUnit][iAxis]);



	double dStartTime;
	dStartTime = ::func_TimeChecker_CurrentTime(true);

	while (1)
	{
		if(GetStopAxis(iUnit, iAxis))
		{
			break;
		}
		else if( ::func_TimeChecker_Compare(10000, dStartTime) == true )
		{
			CString sMsg="";
			//sMsg.Format("[ ERROR ] %s축 이동 시간 초과..", MOTOR_NAME[iAxis]);
			//::SendMessage(hMainDlg, WM_SEND_POPMSG, DEF_TYPE_NG, (LPARAM)&sMsg);
			break;
		}
		SleepHandle(SleepTimeDelay);
	}

	bMotorMoving[iUnit][iAxis] = false;
	return true;
}

bool AxlMotorSet::MoveAxis(int iUnit, int iAxis, bool AbSFlag, double dPos, double dVel)
{//! 지정 축을 절대 구동 또는 상대 구동으로 이동한다. 
	// abs 1:absolute, 0:increment 

	int iUseAxis = 0;
	iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;

	if(GetAmpFault(iUnit, iAxis))
	{
		m_bOrgFlag[iUnit][iAxis] = DEF_ORIGIN_NOT;
		sMsg.Format(" AMP Alarm 발생. MoveAxis 동작 실패.");
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
		return false;
	}

	if(!GetAmpEnable(iUnit, iAxis))
	{
		m_bOrgFlag[iUnit][iAxis] = DEF_ORIGIN_NOT;

		sMsg.Format("[ %s ] 모터 Servo Off 상태 입니다. MoveAxis 동작 실패.", MOTOR_NAME[iAxis]);
		//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_LOG_ALARM_NG_MGL, (LPARAM)&sMsg);
		//DoModal 로 변경
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
		return false;
	}

	if(AbSFlag == ABS)
	{
		double curPos;

		if( MOTOR_TYPE[iAxis] == STEPING )	curPos = GetCommandPos(iUnit, iAxis);
		else								curPos = GetEncoderPos(iUnit, iAxis);
		if(fabs(curPos - dPos) < 0.0001)	return true;

		dPos *= sysData.fMotorResol[iUnit][iAxis];

		//if(m_bOrgFlag[iUnit][iAxis]==DEF_ORIGIN_NOT)
		//{
		//	char	motorMSG[256];
		//	wsprintf(motorMSG, "☞  모터 원점 복귀를 먼저 실행 하십시요. [ %s 축 ]", MOTOR_NAME[iAxis]);
		//	return false;
		//}
	}
	else if(AbSFlag==REL)
	{
      int iGetPos;
      if( MOTOR_TYPE[iAxis] == STEPING)   iGetPos = GetCommandPulse(iUnit, iAxis);//mm
      else								  iGetPos = GetEncoderPulse(iUnit, iAxis);

      dPos = (int)(dPos * sysData.fMotorResol[iUnit][iAxis]);
      dPos += iGetPos;
    }
	//else if(AbSFlag==REL)
	//{
	//	if( MOTOR_TYPE[iAxis] == STEPING)	dPos += GetCommandPos(iUnit, iAxis);
	//	else								dPos += GetEncoderPos(iUnit, iAxis);	
	//}
	else
	{
		sMsg.Format("[ %s ] 모터 이동 명령 비정상.", MOTOR_NAME[iAxis]);
		//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_LOG_ALARM_NG_MGL, (LPARAM)&sMsg);
		//DoModal 로 변경
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
		return false;
	}

	
	//if(dPos>0)			dPos = (int)(dPos+0.5);

#ifdef ON_LINE_MOTOR
	long   axisAll[CUR_MOTOR_NO] = {0, };
	double posAll[CUR_MOTOR_NO] = {0, };
	double velAll[CUR_MOTOR_NO] = {0, };
	double accAll[CUR_MOTOR_NO] = {0, };
	double decAll[CUR_MOTOR_NO] = {0, };
	axisAll[0] = iUseAxis;
	posAll[0] = dPos;
	velAll[0] = dVel * sysData.fMotorResol[iUnit][iAxis];	//이동 속도
	accAll[0] = CalcAcc_G(iUnit,iAxis);//sysData.fMotorAcc[iUnit][iAxis];		//! 가속 가속도
	decAll[0] = CalcDec_G(iUnit,iAxis); //sysData.fMotorDec[iUnit][iAxis];

	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.

	//AxmMoveStartMultiPos(1, axisAll, posAll, velAll, accAll, decAll);
	AxmMoveStartPos(axisAll[0], posAll[0], velAll[0], accAll[0], decAll[0]);
#endif
	//SleepHandle(5);
	return true;
}

bool AxlMotorSet::MoveAxisMulti(int iUnit, int iAxisCnt, short iAxis[CUR_MOTOR_NO], double pos[CUR_MOTOR_NO])
{//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다
	long   axis2[CUR_MOTOR_NO] = {0, };
	double pos2[CUR_MOTOR_NO] = {0, };
	double vel[CUR_MOTOR_NO] = {0, };
	double acc[CUR_MOTOR_NO] = {0, };
	double dec[CUR_MOTOR_NO] = {0, };

	int iCnt =0;
	double curPos;


	for(int i=0; i<iAxisCnt; i++)
	{
		double dEncordChk = 0.0;

		if(!GetStopAxis(iUnit, iAxis[i]))
		{
			SleepHandle(200);
			if(!GetStopAxis(iUnit, iAxis[i]))
			{
				//sMsg.Format("[ %s ] 모터 이동 중 이동 명령이 호출 되었습니다. [%d],[%d],[%d]", MOTOR_NAME[iAxis[i]], flow[iUnit].iAAStep, flow[iUnit].iLENS_Step, flow[iUnit].iLENS_LoadingStep);
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + GetUnitNum(iUnit), (LPARAM)&sMsg);
				return false;
			}
		}

		if(MOTOR_TYPE[ iAxis[i] ] == STEPING)	curPos = GetCommandPos(iUnit, iAxis[i]);
		else									curPos = GetEncoderPos(iUnit, iAxis[i]); 


		//! Motor의 이동 목표 위치, 속도, 가속도/감속도 등을 알아낸다. 
		axis2[iCnt] = iAxis[i] + (iUnit * CUR_MOTOR_NO);
		pos2[iCnt] = pos[i] * sysData.fMotorResol[iUnit][iAxis[i]];
		dEncordChk = pos[i] * sysData.fMotorResol[iUnit][iAxis[i]];

		if(Task[iUnit].AutoFlag == 1)	vel[iCnt] = sysData.fMotorSpeed_Auto[iUnit][iAxis[i]] * sysData.fMotorResol[iUnit][iAxis[i]];
		else							vel[iCnt] = sysData.fMotorSpeed[iUnit][iAxis[i]] * sysData.fMotorResol[iUnit][iAxis[i]];

		acc[iCnt] = CalcAcc_G(iUnit,iAxis[i]);// sysData.fMotorAcc[iUnit][iAxis[i]]; //! 가속 가속도
		dec[iCnt] = CalcDec_G(iUnit,iAxis[i]); //sysData.fMotorDec[iUnit][iAxis[i]];

		//if( fabs(dEncordChk-curPos) < 0.005) 			// 이동할 위치에서 5um 이상 차이가 없을때는 움직이지 않음.
		if( fabs(dEncordChk-curPos) < 0.001) 			// 이동할 위치에서 1um 이상 차이가 없을때는 움직이지 않음.	jjc 2015 12 29 업뎃할때 넣자
			continue;
		else
			iCnt++;
	}

	if(iCnt == 0)
		return true;
	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.
#ifdef ON_LINE_MOTOR
	AxmMoveStartMultiPos(iCnt, axis2, pos2, vel, acc, dec);
#endif

	return true;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
// MOTOR HOME 관련

bool AxlMotorSet::GetResult_Home_Search(int iUnit, int iAxis, CString &sResult)
{//! Home 검색 작업 결과 문자열을 알아낸다. 
	DWORD uHomeResult;
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

	AxmHomeGetResult(iUseAxis, &uHomeResult);

	bool bRet = false;

	switch(uHomeResult)
	{
	case HOME_SUCCESS:
		{
			sResult = _T("원점 검색이 성공적으로 종료 됐을 경우");
			bRet = true;
		}
		break;
	case HOME_SEARCHING:
		{
			sResult = _T("현재 원점검색이 진행중일 경우");
		}
		break;
	case HOME_ERR_GNT_RANGE:
		{
			sResult = _T("겐트리 구동축의 Master축과 Slave축의 원점검색 결과가 설정한 OffsetRange를 벗어났을경우");
		}
		break;
	case HOME_ERR_USER_BREAK:
		{
			sResult = _T("원점 검색중 사용자가 정지 명령을 실행했을 경우");
		}
		break;
	case HOME_ERR_VELOCITY:
		{
			sResult = _T("원점 검색의 속도 설정 값 중 한 개라도 0보다 작거나 같을경우");
		}
		break;
	case HOME_ERR_AMP_FAULT:
		{
			sResult = _T("원점 검색중 서보팩 알람이 발생할 경우");
		}
		break;
	case HOME_ERR_NEG_LIMIT:
		{
			sResult = _T("(+)방향으로 원점센서 검출 중 (-)리미트 센서가 감지될 경우");
		}
		break;
	case HOME_ERR_POS_LIMIT:
		{
			sResult = _T("(-)방향으로 원점센서 검출 중 (+)리미트 센서가 감지될 경우");
		}
		break;
	case HOME_ERR_NOT_DETECT:
		{
			sResult = _T("원점센서가 감지되지 않을경우");
		}
		break;
	case HOME_ERR_UNKNOWN:
		{
			sResult = _T("알수없는 채널(축) 번호(0 ~ (최대축수 - 1))로 원점검색을 시작하려 했을경우");
		}
		break;
	default:
		{
			sResult = _T("Error");
		}
		break;
	}

	return bRet;
}

int AxlMotorSet::IsCompleted_Home_Search(int iUnit, int iAxis)
{//! Home검색 상태 확인(0=Fail, 1=Success, 2=Searching)
	DWORD dwReturn = 0;
	DWORD uHomeResult;
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

	AxmHomeGetResult(iUseAxis, &uHomeResult);

	//! 현재 원점검색이 진행중일 경우
	if ( uHomeResult == HOME_SEARCHING )		return 2;
	if ( uHomeResult == HOME_SUCCESS )			return 1; 
	if ( uHomeResult == HOME_ERR_AMP_FAULT)		return -1;
	if ( uHomeResult == HOME_ERR_NOT_DETECT)	return -2;
	if ( uHomeResult == HOME_ERR_NEG_LIMIT)		return -3;
	if ( uHomeResult == HOME_ERR_POS_LIMIT)		return -4;
	if ( uHomeResult == HOME_ERR_UNKNOWN)		return -5;

	return 0;
}

int AxlMotorSet::GetRate_Home_Search(int iUnit, int iAxis)
{//! Home 검색 작업 중의 진행 정도, 단위 %로 반환된다. 
	DWORD dwReturn = 0;
	DWORD uHomeStepNumber,uHomeMainStepNumber;
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

	//! 원점검색 시작되면 진행율을 확인할 수 있다. 원점검색이 완료되면 성공여부와 관계없이 100을 반환하게 된다.
	//! uHomeMainStepNumber은 겐트리일 경우 마스터,슬레이브가 동작하는지 확인할 때 이용한다.
	//!  (마스터축 동작일 때는 0을 리턴, 슬레이브동작일 때는 10을 리턴한다.)
	dwReturn = AxmHomeGetRate(iUseAxis, &uHomeMainStepNumber, &uHomeStepNumber);

	//! 원점검색 진행율(단위: %)
	return uHomeStepNumber;
}

void AxlMotorSet::Stop_Home_Search(int iUnit, int iAxis)
{//! Home 검색 중에 강제로 중지 시킴
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

	AxmHomeSetResult(iUseAxis, HOME_ERR_USER_BREAK);
	StopAxis(iUnit, iUseAxis);
}

int AxlMotorSet::Start_Home_Search(int iUnit, int iAxis)
{//! Home 검색 작업 시작
	m_criHomeProc.Lock();

	DWORD dwReturn = 0;
	DWORD level;
	int iUseAxis = iUnit * CUR_MOTOR_NO + iAxis;	//실제 보드 사용 축 번호

	AxmSignalIsServoOn(iUseAxis, &level);
	if ( level != ENABLE )
	{
		AxmSignalServoOn(iUseAxis, ENABLE);	

		for(int i=0; i<20; i++)
		{
			SleepHandle(5);
			CheckHandle();
		}

		AxmSignalIsServoOn(iUseAxis, &level);
		if ( level != ENABLE )
		{
			sMsg.Format("[ %s ] 모터 원점 검색 서보 ON 실패.!!", MOTOR_NAME[iAxis]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  +DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  +DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			m_criHomeProc.Unlock();
			return -3;
		}
	}


	//! +++++++++++++++++++++++++++++++++++++++++++++++++++++
	//!    DIR_CCW    00h     (-) 방향
	//!    DIR_CW     01h     (+) 방향
	//! [lHmsig]
	//!    PosEndLimit  00h   +Elm(End limit) +방향 리미트 센서 신호
	//!    NegEndLimit  01h   -Elm(End limit) -방향 리미트 센서 신호
	//!    HomeSensor   04h   IN0(ORG)  원점 센서 신호
	//! [dwZphas]
	//!    DISABLE      00h   Z상 검출 사용하지 않음
	//!    + 방향       01h   Z상 검출 +방향사용
	//!    - 방향       02h   Z상 검출 -방향사용

	long    lHmDir = DIR_CW;			//! 원점검색을 초기에 진행할 방향설정
	DWORD   lHmsig =  HomeSensor;		//! 원점 검색에 사용 할 신호설정
	DWORD   dwZphas = DISABLE;			//! 1차 원점검색 완료 후 엔코더 Z상 검출 유무 설정
	double  dwHClrTim = 2000.0;			//! 원점검색 완료 후 지령위치와 Encoder위치를 Clear하기 위해 대기하는 시간설정 [mSec단위]
	double  dwHOffset = 0.0;			//! 원점검색이 완료된 후 기구 원점으로 이동 후 원점 재설정 할 위치

	lHmDir = MOTOR_HOME_DIR[iAxis];
	lHmsig = MOTOR_HOME_SIG[iAxis];

	//if (iAxis == MotPCB_Y)			// 20160318 
	//{
	//	lHmDir = DIR_CCW;
	//}

	dwReturn = AxmHomeSetMethod(iUseAxis, lHmDir, lHmsig, dwZphas, dwHClrTim, dwHOffset);
	if ( dwReturn != AXT_RT_SUCCESS )
	{
		sMsg.Format("[ %s ] 모터 원점 검색 설정 실패.!!(code : %d)", MOTOR_NAME[iAxis], (int)(dwReturn));
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
		m_criHomeProc.Unlock();
		return -4;
	}

	dwReturn = SetHomeSearchSpeed(iUseAxis);	//원점 검색 속도 설정
	if ( dwReturn != AXT_RT_SUCCESS )
	{
		sMsg.Format("[ %s ] 모터 원점 속도 설정 실패.!!", MOTOR_NAME[iAxis]);
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
		m_criHomeProc.Unlock();
		return -6;
	}

	dwReturn = AxmHomeSetStart(iUseAxis);
	if ( dwReturn != AXT_RT_SUCCESS )
	{
		//! Error Code 확인
		//kdu 확인요.
		CString sError = _T("");
		GetResult_Home_Search(iUnit, iAxis, sError);
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
		m_criHomeProc.Unlock();
		return -7;
	}

	m_criHomeProc.Unlock();
	return 1;
}

DWORD AxlMotorSet::SetHomeSearchSpeed(int iUseAxis)
{//! 원점 검색시 사용되는 속도 설정
	/*
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 원점을 빠르고 정밀하게 검색하기 위해 여러 단계의 스탭으로 검출한다. 이때 각 스탭에 사용 될 속도를 설정한다. 
	// 이 속도들의 설정값에 따라 원점검색 시간과, 원점검색 정밀도가 결정된다. 
	// 각 스탭별 속도들을 적절히 바꿔가면서 각 축의 원점검색 속도를 설정하면 된다. 
	// (자세한 내용은 AxmMotSaveParaAll 설명 부분 참조)
	// 원점검색시 사용될 속도를 설정하는 함수
	// [dVelFirst]- 1차구동속도   [dVelSecond]-검출후속도   [dVelThird]- 마지막 속도  [dvelLast]- index검색및 정밀하게 검색하기위해. 
	// [dAccFirst]- 1차구동가속도 [dAccSecond]-검출후가속도 
	*/
	DWORD dwReturn = 0;
	double dVelFirst = 20000.;		
	double dVelSecond = 10000.;
	double dVelThird = 4000.;
	double dvelLast = 500.;	

	double dAccFirst = 0.1;		
	double dAccSecond = 0.1;

	//ISJ
	int iAxis = iUseAxis%CUR_MOTOR_NO;
	int iUnit = iUseAxis/CUR_MOTOR_NO;


	switch(iAxis)
	{
// 	case MotPCB_X:
// 	dVelFirst = 4000.;		dVelSecond = 1000.;	dVelThird = 500.;		dvelLast = 50.;
// 	break;
	case MotPCB_Y:
	dVelFirst = 50000;		dVelSecond = 20000;	dVelThird = 300;		dvelLast = 50;	
	break;
	case MotPCB_T:
	dVelFirst = 14000.;		dVelSecond = 7000.;	dVelThird = 300;		dvelLast = 50.;	
	break;
	case MotLENS_X:
	dVelFirst = 14000.;		dVelSecond = 10001;	dVelThird = 300;		dvelLast = 50.;	

	break;
	case MotLENS_Y:
	dVelFirst = 50000;		dVelSecond = 20000;	dVelThird = 300;		dvelLast = 50;	
	break;
	case MotLENS_Z:
	dVelFirst = 20000;		dVelSecond = 4000;	dVelThird = 300;		dvelLast = 50.;	
	break;
	case MotLENS_Tx:
	dVelFirst = 1000.;		dVelSecond = 500.;	dVelThird = 300;		dvelLast = 50.;	
	break;
	case MotLENS_Ty:
	dVelFirst = 200;		dVelSecond = 100.;	dVelThird = 40.;		dvelLast = 15.;	
	break;
	case MotCL_Y:
	dVelFirst = 50000;		dVelSecond = 20000;	dVelThird = 300;		dvelLast = 50;	
	break;
	default://유효하지 않는 모터 번호
	dwReturn = AXT_RT_INVALID_MODULE_POS;
	break;	
	}


	if(dwReturn == 0)  
	{
	dwReturn = AxmHomeSetVel(iUseAxis, dVelFirst, dVelSecond, dVelThird, dvelLast, CalcAcc_G(iUnit,iAxis), CalcAcc_G(iUnit,iAxis));
	//dwReturn = AxmHomeSetVel(iUseAxis, dVelFirst, dVelSecond, dVelThird, dvelLast, dVelFirst, dVelSecond);
	}

	return dwReturn;
}

bool AxlMotorSet::HomeReadyProcess(int iUnit, int iType)
{
	CString sMsg;
	DWORD dwThreadID, dwExitCode = 0;
	int	nCurIdx=0;
	CCPreFocusingAADlg* pFrame = (CCPreFocusingAADlg*)AfxGetApp()->m_pMainWnd;

	GetExitCodeThread(m_hThreadAutoFocus[iUnit], &dwExitCode);
	if( dwExitCode == STILL_ACTIVE )
	{
		sMsg.Format(_T("AUTO MODE 동작 PROCESS가 이미 동작 중입니다.."));
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
		//::SendMessage(hMainDlg,WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP,(LPARAM)&sMsg);
		return false;
	}
	if( (Motor.m_hThreadHomeAll[iUnit] != NULL) ||  ( Motor.m_hThreadHome[iUnit] != NULL ) )
	{
		sMsg.Format("원점 복귀중에 불가능한 동작입니다. ");
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg,WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
		return false;
	}

	long  AxisCount;
	DWORD dwRet = 0;
	dwRet = AxmInfoGetAxisCount(&AxisCount);
	if ( dwRet != AXT_RT_SUCCESS )
	{//! Servo 전원이 떨어지면 모든 상황을 정지 하여야 한다
		sMsg.Format("[ ERROR ] AXT Board 인식 실패.. 원점 검색 동작을 정지 합니다.");
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg,WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
		return false;
	}
	if ( AxisCount <= 0 )
	{
		sMsg.Format("[ ERROR ] 모터 드라이브 개수 이상.. 원점 검색 동작을 정지 합니다.");
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg,WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
		return false;
	}


	for(int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++)
	{
		if( !GetStopAxis(iUnit, iAxis) )
		{
			sMsg.Format("[ %s ] 모터 동작 중 입니다.\n 구동 정지 후 원점 진행 하세요.", MOTOR_NAME[iAxis]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			return false;
		}

		if( GetAmpFault(iUnit, iAxis) )
		{//AmpFaultReset => MESSAGE창으로 자동으로 알람 해제 해도 됨. 일단 알람만 발생.
			sMsg.Format("[ %s ] 모터 알람 발생 중입니다.\n 알람 해제 후 원점 진행 하세요.", MOTOR_NAME[iAxis]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			return false;
		}
	} 

	if( Task[iUnit].AutoFlag == 1)
	{
		sMsg.Format("자동운전중에 불가능한 동작입니다. " );
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT1));
		//::SendMessage(hMainDlg,WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT1), (LPARAM)&sMsg);
		return false;
	}

	if( !AmpEnableAll(iUnit) )
	{
		Sleep(200);
		if( !AmpEnableAll(iUnit) )
		{
			sMsg.Format(" 모터 전체 서보 ON 실패.");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			return false;
		}
	}

	
	iHomeUseStep = 1000;
	if(iType == 0)		//원점
	{
		for(int i=0; i<CUR_MOTOR_NO; i++)
			Motor.iHomeProcUsing[iUnit][i] = 1;

		iHomeEndStep = 10000;

		if( iUnit == UNIT1 )
		{
			m_hThreadHomeAll[UNIT1] = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)Thread_HomeReadyProcess1, 
				this, 0, &dwThreadID);
		}
		else if( iUnit == UNIT2 )
		{
			m_hThreadHomeAll[UNIT2] = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)Thread_HomeReadyProcess2, 
				this, 0, &dwThreadID);
		}
	}
	else if(iType == 1)		//운전 준비
	{
 		bool OrgRes = true; 
 		for(int Axis=0; Axis<(CUR_MOTOR_NO); Axis++)
 		{
 			if( Motor.m_bOrgFlag[iUnit][Axis] != DEF_ORIGIN_COMPLETE )
 				OrgRes = false;
 		}

 		if(OrgRes)		//원점이 잡혔을 경우
		{//운전 준비로 이동
			iHomeUseStep = 10000;
			iHomeEndStep = 25000;

			if( iUnit == UNIT1 )
			{
				m_hThreadReady[UNIT1] = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)Thread_ReadyProcess1, 
					this, 0, &dwThreadID);
			}
			else if( iUnit == UNIT2 )
			{
				m_hThreadReady[UNIT2] = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)Thread_ReadyProcess2, 
					this, 0, &dwThreadID);
			}

		}
		else		//원점이 안 잡혔을 경우
		{
			sMsg.Format("운전준비전 원점이 잡혀있지 않습니다.");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			return false;
		}
	}

// 	if( iUnit == UNIT1 )
// 	{
// 		m_hThreadHomeAll[UNIT1] = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)Thread_HomeReadyProcess1, 
// 			this, 0, &dwThreadID);
// 	}
// 	else if( iUnit == UNIT2 )
// 	{
// 		m_hThreadHomeAll[UNIT2] = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)Thread_HomeReadyProcess2, 
// 			this, 0, &dwThreadID);
// 	}

	return true;
}

DWORD Thread_HomeReadyProcess1(AxlMotorSet* pAxlMotorSet)	
{// [ iUnit ] 전체 원점 동작
	int iUnit = UNIT1;

	CString sMsg, str;
	int iThreadStep = 0, iThreadEndStep = 0, iHomFlag = 0;
	DWORD dwRet = 0;
	long AxisCount = 0;

//	char szVer[SIZE_OF_100BYTE];		//20160828 JJC

	iThreadStep = pAxlMotorSet->iHomeUseStep;
	iThreadEndStep = pAxlMotorSet->iHomeEndStep;

	CCPreFocusingAADlg* pFrame = (CCPreFocusingAADlg*)AfxGetApp()->m_pMainWnd;

	//운전준비 풀기
	Task[UNIT1].bRunningReady = false;

	pAxlMotorSet->bThreadHomeAll[iUnit] = true;

	while(pAxlMotorSet->bThreadHomeAll[iUnit])
	{
		Sleep(5);

		dwRet = AxmInfoGetAxisCount(&AxisCount);
		if ( dwRet != AXT_RT_SUCCESS )
		{//! Servo 전원이 떨어지면 모든 상황을 정지 하여야 한다.
			sMsg.Format("[ ERROR ][ 원점 검색 ] AXT Board 인식 실패.. 원점 검색 동작을 정지 합니다.");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);

			pAxlMotorSet->bThreadHomeAll[iUnit] = false;
			break;
		}

		bool bAlarmLimit = true;
		for(int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++)
		{
			if(pAxlMotorSet->iHomeProcUsing[iUnit][iAxis] == 2)
			{
				if( pAxlMotorSet->GetAmpFault(iUnit, iAxis) == true ){
					sMsg.Format("[ 전체원점] 원점 검색 중 AMP 알람 발생.");
					g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);

					pAxlMotorSet->bThreadHomeAll[iUnit] = false;
					bAlarmLimit = false;
					break;
				}

				if( pAxlMotorSet->GetAmpEnable(iUnit, iAxis) == false ){
					sMsg.Format("[ 전체원점] 원점 검색 중 Servo Off 알람 발생.");
					g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);

					pAxlMotorSet->bThreadHomeAll[iUnit] = false;
					bAlarmLimit = false;
					break;
				}

			}
		}
		if( bAlarmLimit == false )	break;

		
		str.Format("[ STEP : %d ]", iThreadStep);
		//pFrame->m_btn_title1.CallFlashFunction("Version", "%s", str);
		//sprintf_s(szVer, SIZE_OF_100BYTE, "[ STEP : %d ]", iThreadStep);			//20160828 JJC
		pFrame->stcVersion[iUnit].SetWindowTextA(str);

		if(iThreadStep >= 1000 && iThreadStep <10000)		iThreadStep = pAxlMotorSet->HomeAllProcess_UNIT1(iThreadStep);		//전체원점
//		else if(iThreadStep >= 10000 && iThreadStep < 25000)	iThreadStep = pAxlMotorSet->ReadyAllProcess_UNIT1(iThreadStep);		//운전 준비

		if(iThreadStep < 0)
		{//에러 발생 동작 정지
			for(int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++)
			{
				iHomFlag = pAxlMotorSet->IsCompleted_Home_Search(iUnit, iAxis);
				if( iHomFlag == 2 )
				{
					pAxlMotorSet->Stop_Home_Search(iUnit, iAxis);
					pAxlMotorSet->m_bOrgFlag[iUnit][iAxis] = false;
				}
			}
			break;
		}

		if( iThreadStep == 99999  ||  iThreadStep >= iThreadEndStep)
		{	//KYH 전체축 홈검색 및 운전준비 완료 Message 추가
			//KYH Progress창 제거.
			break;
		}


	}//while

	for(int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++)
		pAxlMotorSet->iHomeProcUsing[iUnit][iAxis] = 0;	//전체 원점 요청 초기화

	pAxlMotorSet->m_hThreadHomeAll[iUnit] = NULL;
	pAxlMotorSet->bThreadHomeAll[iUnit] = false;

	return true;
}

DWORD Thread_HomeReadyProcess2(AxlMotorSet* pAxlMotorSet)	
{// [ iUnit ] 전체 원점 동작
	int iUnit = UNIT2;

	CString sMsg, str;
	int iThreadStep = 0, iThreadEndStep = 0, iHomFlag = 0;
	DWORD dwRet = 0;
	long AxisCount = 0;

//	char szVer[SIZE_OF_100BYTE];		//20160828 JJC

	iThreadStep = pAxlMotorSet->iHomeUseStep;
	iThreadEndStep = pAxlMotorSet->iHomeEndStep;

	CCPreFocusingAADlg* pFrame = (CCPreFocusingAADlg*)AfxGetApp()->m_pMainWnd;


	//운전준비 풀기
	Task[UNIT2].bRunningReady = false;

	pAxlMotorSet->bThreadHomeAll[iUnit] = true;

	while(pAxlMotorSet->bThreadHomeAll[iUnit])
	{
		Sleep(5);

		dwRet = AxmInfoGetAxisCount(&AxisCount);
		if ( dwRet != AXT_RT_SUCCESS )
		{//! Servo 전원이 떨어지면 모든 상황을 정지 하여야 한다.
			sMsg.Format("[ ERROR ][ 원점 검색 ] AXT Board 인식 실패.. 원점 검색 동작을 정지 합니다.");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);

			pAxlMotorSet->bThreadHomeAll[iUnit] = false;
			break;
		}

		bool bAlarmLimit = true;
		for(int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++)
		{
			if(pAxlMotorSet->iHomeProcUsing[iUnit][iAxis] == 2)
			{
				if( pAxlMotorSet->GetAmpFault(iUnit, iAxis) == true ){
					sMsg.Format("[ 전체원점] 원점 검색 중 AMP 알람 발생.");
					g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);

					pAxlMotorSet->bThreadHomeAll[iUnit] = false;
					bAlarmLimit = false;
					break;
				}

				if( pAxlMotorSet->GetAmpEnable(iUnit, iAxis) == false ){
					sMsg.Format("[ 전체원점] 원점 검색 중 Servo Off 알람 발생.");
					g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);

					pAxlMotorSet->bThreadHomeAll[iUnit] = false;
					bAlarmLimit = false;
					break;
				}

			}
		}
		if( bAlarmLimit == false )	break;

		str.Format("[ STEP : %d ]", iThreadStep);
	//	pFrame->m_btn_title2.CallFlashFunction("Version", "%s", str);
		//sprintf_s(szVer, SIZE_OF_100BYTE, "[ STEP : %d ]", iThreadStep);			//20160828 JJC
		pFrame->stcVersion[iUnit].SetWindowTextA(str);


		if(iThreadStep >= 1000 && iThreadStep <10000)		iThreadStep = pAxlMotorSet->HomeAllProcess_UNIT2(iThreadStep);		//전체원점
	//	else if(iThreadStep >= 10000 && iThreadStep < 25000)	iThreadStep = pAxlMotorSet->ReadyAllProcess_UNIT2(iThreadStep);		//운전 준비

		if(iThreadStep < 0)
		{//에러 발생 동작 정지
			for(int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++)
			{
				iHomFlag = pAxlMotorSet->IsCompleted_Home_Search(iUnit, iAxis);
				if( iHomFlag == 2 )
				{
					pAxlMotorSet->Stop_Home_Search(iUnit, iAxis);
					pAxlMotorSet->m_bOrgFlag[iUnit][iAxis] = false;
				}
			}
			break;
		}

		if( iThreadStep == 99999  ||  iThreadStep >= iThreadEndStep)
		{	//KYH 전체축 홈검색 및 운전준비 완료 Message 추가
			//KYH Progress창 제거.
			break;
		}


	}//while





	for(int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++)
		pAxlMotorSet->iHomeProcUsing[iUnit][iAxis] = 0;	//전체 원점 요청 초기화

	pAxlMotorSet->m_hThreadHomeAll[iUnit] = NULL;
	pAxlMotorSet->bThreadHomeAll[iUnit] = false;

	return true;
}
//----------------------------------------------------------------------------------운 전 준 비
DWORD Thread_ReadyProcess1(AxlMotorSet* pAxlMotorSet)	
{// [ iUnit ] 운전 준비 동작
	int iUnit = UNIT1;

	CString sMsg, str;
	int iThreadStep = 0, iThreadEndStep = 0, iHomFlag = 0;
	DWORD dwRet = 0;
	long AxisCount = 0;

//	char szVer[SIZE_OF_100BYTE];		//20160828 JJC

	iThreadStep = pAxlMotorSet->iHomeUseStep;
	iThreadEndStep = pAxlMotorSet->iHomeEndStep;

	CCPreFocusingAADlg* pFrame = (CCPreFocusingAADlg*)AfxGetApp()->m_pMainWnd;


	pAxlMotorSet->bThreadReady[iUnit] = true;

	while(pAxlMotorSet->bThreadReady[iUnit])
	{
		Sleep(5);

		dwRet = AxmInfoGetAxisCount(&AxisCount);
		if ( dwRet != AXT_RT_SUCCESS )
		{//! Servo 전원이 떨어지면 모든 상황을 정지 하여야 한다.
			sMsg.Format("[ ERROR ][ 원점 검색 ] AXT Board 인식 실패.. 원점 검색 동작을 정지 합니다.");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);

			pAxlMotorSet->bThreadReady[iUnit] = false;
			break;
		}

		bool bAlarmLimit = true;
		for(int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++)
		{
			if(pAxlMotorSet->iHomeProcUsing[iUnit][iAxis] == 2)
			{
				if( pAxlMotorSet->GetAmpFault(iUnit, iAxis) == true ){
					sMsg.Format("[ 전체원점] 원점 검색 중 AMP 알람 발생.");
					g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);

					pAxlMotorSet->bThreadReady[iUnit] = false;
					bAlarmLimit = false;
					break;
				}

				if( pAxlMotorSet->GetAmpEnable(iUnit, iAxis) == false ){
					sMsg.Format("[ 전체원점] 원점 검색 중 Servo Off 알람 발생.");
					g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);

					pAxlMotorSet->bThreadReady[iUnit] = false;
					bAlarmLimit = false;
					break;
				}

			}
		}
		if( bAlarmLimit == false )	break;


		str.Format("[ STEP : %d ]", iThreadStep);
		//pFrame->m_btn_title1.CallFlashFunction("Version", "%s", str);

		//sprintf_s(szVer, SIZE_OF_100BYTE, "[ STEP : %d ]", iThreadStep);			//20160828 JJC
		pFrame->stcVersion[iUnit].SetWindowTextA(str);

		if(iThreadStep >= 10000 && iThreadStep < 27000/*25000*/)	iThreadStep = pAxlMotorSet->ReadyAllProcess_UNIT1(iThreadStep);		//운전 준비

		if(iThreadStep < 0)
		{//에러 발생 동작 정지
			for(int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++)
			{
				AxmMoveEStop(iAxis + (0 * CUR_MOTOR_NO));
			}
			break;
		}

		if( iThreadStep == 99999  ||  iThreadStep >= iThreadEndStep)
		{	//KYH 전체축 홈검색 및 운전준비 완료 Message 추가
			//KYH Progress창 제거.
			break;
		}


	}//while	 

	pAxlMotorSet->m_hThreadReady[iUnit] = NULL;
	pAxlMotorSet->bThreadReady[iUnit] = false;

	return true;
}

DWORD Thread_ReadyProcess2(AxlMotorSet* pAxlMotorSet)	
{// [ iUnit ] 전체 원점 동작
	int iUnit = UNIT2;

	CString sMsg, str;
	int iThreadStep = 0, iThreadEndStep = 0, iHomFlag = 0;
	DWORD dwRet = 0;
	long AxisCount = 0;

//	char szVer[SIZE_OF_100BYTE];		//20160828 JJC

	iThreadStep = pAxlMotorSet->iHomeUseStep;
	iThreadEndStep = pAxlMotorSet->iHomeEndStep;

	CCPreFocusingAADlg* pFrame = (CCPreFocusingAADlg*)AfxGetApp()->m_pMainWnd;


	pAxlMotorSet->bThreadReady[iUnit] = true;

	while(pAxlMotorSet->bThreadReady[iUnit])
	{
		Sleep(5);

		dwRet = AxmInfoGetAxisCount(&AxisCount);
		if ( dwRet != AXT_RT_SUCCESS )
		{//! Servo 전원이 떨어지면 모든 상황을 정지 하여야 한다.
			sMsg.Format("[ ERROR ][ 원점 검색 ] AXT Board 인식 실패.. 원점 검색 동작을 정지 합니다.");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);

			pAxlMotorSet->bThreadReady[iUnit] = false;
			break;
		}

		bool bAlarmLimit = true;
		for(int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++)
		{
			if(pAxlMotorSet->iHomeProcUsing[iUnit][iAxis] == 2)
			{
				if( pAxlMotorSet->GetAmpFault(iUnit, iAxis) == true ){
					sMsg.Format("[ 전체원점] 원점 검색 중 AMP 알람 발생.");
					g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);

					pAxlMotorSet->bThreadReady[iUnit] = false;
					bAlarmLimit = false;
					break;
				}

				if( pAxlMotorSet->GetAmpEnable(iUnit, iAxis) == false ){
					sMsg.Format("[ 전체원점] 원점 검색 중 Servo Off 알람 발생.");
					g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);

					pAxlMotorSet->bThreadReady[iUnit] = false;
					bAlarmLimit = false;
					break;
				}

			}
		}
		if( bAlarmLimit == false )	break;


		str.Format("[ STEP : %d ]", iThreadStep);
	//	pFrame->m_btn_title2.CallFlashFunction("Version", "%s", str);
		//sprintf_s(szVer, SIZE_OF_100BYTE, "[ STEP : %d ]", iThreadStep);			//20160828 JJC
		pFrame->stcVersion[iUnit].SetWindowTextA(str);

		//	if(iThreadStep >= 1000 && iThreadStep <10000)		iThreadStep = pAxlMotorSet->HomeAllProcess_UNIT1(iThreadStep);		//전체원점
		//	else 
		if(iThreadStep >= 10000 && iThreadStep < 25000)	iThreadStep = pAxlMotorSet->ReadyAllProcess_UNIT2(iThreadStep);		//운전 준비
		//if(iThreadStep >= 10000 && iThreadStep < 27000)	iThreadStep = pAxlMotorSet->ReadyAllProcess_UNIT2(iThreadStep);		//운전 준비

		if(iThreadStep < 0)
		{//에러 발생 동작 정지
			for(int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++)
			{
				AxmMoveEStop(iAxis + (1 * CUR_MOTOR_NO));
			}
			break;
		}

		if( iThreadStep == 99999  ||  iThreadStep >= iThreadEndStep)
		{	//KYH 전체축 홈검색 및 운전준비 완료 Message 추가
			//KYH Progress창 제거.
			break;
		}


	}//while

	pAxlMotorSet->m_hThreadReady[iUnit] = NULL;
	pAxlMotorSet->bThreadReady[iUnit] = false;

	return true;
}



//----------------------------------------------------------------------------------------------------------


//-----------------개별 원점-----------------------------------------------
bool AxlMotorSet::HomeSingleProcess(int iUnit, int iAxis)
{
	CString sMsg;
	DWORD dwThreadID=0, dwExitCode=0;
	
	GetExitCodeThread(m_hThreadHome[iUnit], &dwExitCode);
	if(dwExitCode == STILL_ACTIVE)
	{
		sMsg.Format(_T("[ 개별원점 ]개별 원점 동작 PROCESS가 이미 동작 중입니다.."));
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
		return false;
	}

	for(int iAxiss = 0; iAxiss < CUR_MOTOR_NO; iAxiss++)
	{
		if( !GetStopAxis(iUnit, iAxiss) )
		{
			sMsg.Format("[ %s ] 모터 동작 중 입니다.\n 구동 정지 후 원점 진행 하세요.", MOTOR_NAME[iAxiss]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			return false;
		}
		m_bOrgFlag[iUnit][iAxiss] = DEF_ORIGIN_NOT;

		if( GetAmpFault(iUnit, iAxiss) )
		{
			sMsg.Format("[ %s ] 모터 알람 발생 중입니다.\n 알람 해제 후 원점 진행 하세요.", MOTOR_NAME[iAxiss]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			return false;
		}
	}

	//20151026 ksg
	if( Task[UNIT1].AutoFlag == 1) 
	{
		sMsg.Format("자동운전중에 불가능한 동작입니다. " );
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT1));
		//::SendMessage(hMainDlg,WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT1), (LPARAM)&sMsg);
		return false;
	}

	if( !AmpEnableAll(iUnit) )
	{
		Sleep(200);
		if( !AmpEnableAll(iUnit) )
		{
			sMsg.Format(" 모터 전체 서보 ON 실패.");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			return false;
		}
	}


//	iHomeProcUsing[iUnit][iAxis] = 1;

	if( iUnit == UNIT1 )
	{
		m_hThreadHome[UNIT1] = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)ThreadHomeProcessAA1, 
			this, 0, &dwThreadID);
	}
	else if( iUnit == UNIT2 )
	{
		m_hThreadHome[UNIT2] = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)ThreadHomeProcessAA2, 
			this, 0, &dwThreadID);
	}
	return true;
}

int AxlMotorSet::HomeSingleProcess_UNIT1(int iUseStep)
{// [ UNIT1 ] 개별 원점 동작
	int iUnit = UNIT1;
	CString sMsg;
	int iThreadStep = 0, iHomFlag = 0;
	double dVel,dAcc;
	double dFTime = 0;
	DWORD dwReturn;

	iThreadStep = iUseStep;
	//현재 개별원점을 실행할 번호를 선택한다.
	int iSelectAxis = iSelectAxisss[iUnit];

	// 	for( int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++){	
	// 		if(iHomeProcUsing[iUnit][iAxis] == 1 )		//요구 신호 확인
	// 		{
	// 			iSelectAxis	= iAxis;	
	// 			break;
	// 		}
	// 	}	

	switch(iThreadStep)
	{
	case 1000:  //CL Y   -리밋으로 이동
		iThreadStep = 2000;
		break;
		dVel = 10 * sysData.fMotorResol[iUnit][MotCL_Y];
		dAcc = Motor.CalcAcc_G(iUnit,MotCL_Y);

		dwReturn = AxmMoveSignalSearch(MotCL_Y  + (CUR_MOTOR_NO * iUnit), -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ 개별원점] %s (-) Limit 이동 지령 실패.", MOTOR_NAME[MotCL_Y]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -1000;
		}
		else
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 1500;
		}
		break;

	case 1500:// CL Y -리밋 센서 신호 확인

		if( GetStopAxis(iUnit, MotCL_Y) &&
			GetNegaSensor(iUnit, MotCL_Y) )
		{
			iThreadStep = 2000;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dFTime))	
		{
			sMsg.Format("[ 개별원점] CL Y (-) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -1000;	
		}
		break;

	case 2000:
		if(ProcLENS[iUnit].OUT_LensGrip(BACKWARD))
		{
			iThreadStep = 2500;
			dFTime = func_TimeChecker_CurrentTime(true);
		}
		else
		{
			sMsg.Format("[ 개별원점] LENS GRIP 후진 실패");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -2000;
		}
		break;

	//20151108 ksg // 원점 복귀 그립후 딜레이 추가
	case 2500:
		if(ProcLENS[iUnit].IN_LensGrip(BACKWARD))
		{
			iThreadStep = 2600; //3000;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dFTime))
		{
			sMsg.Format("[ 개별원점] LENS GRIP 후진 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -1000;
		}
		break;

	//20151117 ksg
	case 2600:
		if(::func_TimeChecker_Compare(model.SilinderDelay[iUnit][DELAY_GRIP], dFTime))
		{
			iThreadStep = 2700;
		}
		break;

	//실린더 추가
	case 2700:
		if(ProcLENS[iUnit].OUT_Lens_Pusher(CYL_UP))
		{
			iThreadStep = 2800;
			dFTime = func_TimeChecker_CurrentTime(true);
		}
		else
		{
			sMsg.Format("[ 전체원점] LENS PUSHER 상승 실패");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -2700;
		}
		break;

	case 2800:
		if(ProcLENS[iUnit].IN_Lens_Pusher(CYL_UP))
		{
			iThreadStep = 3000;
			dFTime = func_TimeChecker_CurrentTime(true);
		}
		else if(::func_TimeChecker_Compare(TIME_AXIS, dFTime))
		{
			sMsg.Format("[ 전체원점] LENS PUSHER 상승 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -2700;
		}
		break;

	case 3000:
		//LENS Z가 원점이 잡혀있으면 대기위치, 아니면 리밋까지.
		if(Motor.GetAmpEnable(iUnit,MotLENS_Z ) == false)
		{
			if(Motor.AmpEnable(iUnit ,MotLENS_Z))		
				Motor.m_bAxisState[iUnit][MotLENS_Z] = true;
		}

		dVel = sysData.fMotorSpeed[iUnit][MotLENS_Z] * sysData.fMotorResol[iUnit][MotLENS_Z];
		dAcc = Motor.CalcAcc_G(iUnit,MotLENS_Z);

		dwReturn = AxmMoveSignalSearch(MotLENS_Z + (CUR_MOTOR_NO * iUnit), dVel, dAcc, PosEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{ 
			sMsg.Format("[ 개별원점] %s (+) Limit 이동 지령 실패.", MOTOR_NAME[MotLENS_Z]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -3000;
		}
		else
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 3500;			
		}

		break;

	case 3500://! Lens Z축 (+)Limit센서 신호 확인
		if( GetStopAxis(iUnit, MotLENS_Z) &&
			GetPosiSensor(iUnit, MotLENS_Z) )
		{

			if(iSelectAxis == MotLENS_X || iSelectAxis == MotLENS_Z || iSelectAxis == MotLENS_Tx || iSelectAxis == MotLENS_Ty)
			{
				iThreadStep = 4000;
			}
			else
			{
				iThreadStep = 5000;
			}
		}			
		else if(func_TimeChecker_Compare(TIME_DELAY + 5000, dFTime))	//시간 초과
		{
			sMsg.Format("[ 개별원점] LENS Z축 (+)LIMIT 이동 시간 초과");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -3000;
		}
		break;

	case 4000:  //LENS Y   +리밋으로 이동
		if(Motor.GetAmpEnable(iUnit,MotLENS_Y ) == false)
		{
			if(Motor.AmpEnable(iUnit ,MotLENS_Y))		
				Motor.m_bAxisState[iUnit][MotLENS_Y] = true;
		}

		dVel = sysData.fMotorSpeed[iUnit][MotLENS_Y] * sysData.fMotorResol[iUnit][MotLENS_Y];
		dAcc = Motor.CalcAcc_G(iUnit,MotLENS_Y); 

		dwReturn = AxmMoveSignalSearch(MotLENS_Y  + (CUR_MOTOR_NO * iUnit ), dVel, dAcc, PosEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ 개별원점] %s (-) Limit 이동 지령 실패.", MOTOR_NAME[MotLENS_Y]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -4000;
		}
		else
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 4500;
		}
		break;

	case 4500:// LENS Y +리밋 센서 신호 확인

		if( GetStopAxis(iUnit, MotLENS_Y) &&
			GetPosiSensor(iUnit, MotLENS_Y) )
		{
			iThreadStep = 5000;
		}
		else if(func_TimeChecker_Compare(TIME_DELAY + 10000, dFTime))	//시간 초과
		{
			sMsg.Format("[ 개별원점] LENS Y (-) LIMIT 센서 신호 확인 시간 초과");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -3000;
		}

		break;

	case 5000:
		//! PCB T축 리미트까지 이동
		if( MotPCB_T == iSelectAxis )
		{
			/*dVel = 50 * sysData.fMotorResol[iUnit][MotPCB_T];
			dAcc = 1;
			dwReturn = AxmMoveSignalSearch(MotPCB_T + (CUR_MOTOR_NO*iUnit), -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);*/

			dVel = 10 * sysData.fMotorResol[iUnit][MotPCB_T];
			dAcc = Motor.CalcAcc_G(iUnit,MotPCB_T);

			dwReturn = AxmMoveSignalSearch(MotPCB_T + (CUR_MOTOR_NO * iUnit), -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);
			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sMsg.Format("[ 개별원점] %s (-) Limit 이동 지령 실패.", MOTOR_NAME[MotPCB_T]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
				iThreadStep = -5000;
			}
			else
			{
				iThreadStep = 5500;
				dFTime = func_TimeChecker_CurrentTime(true);
			}
		}
		else 
		{
			iThreadStep = 6000;
		}

		break;

	case 5500:
		if( GetStopAxis(iUnit, MotPCB_T) &&
			GetNegaSensor(iUnit, MotPCB_T) )
		{
			iThreadStep = 6000;
		}
		else if(func_TimeChecker_Compare(TIME_DELAY, dFTime))	//시간 초과
		{
			StopAxis(iUnit,MotPCB_T);			//정지    20160318 JJC
			sMsg.Format("[ 개별원점] PCB T (-) LIMIT 센서 신호 확인 시간 초과");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -5000;
		}
		break;

	case 6000:

		//선택된 축 홈찾기 진행
		if(Start_Home_Search(iUnit, iSelectAxis) < 0 )
		{	//에러시 
			sMsg.Format("[ 개별원점 ] 원점 동작 지령 실패.");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -6000;
		}
		else{	//성공일때 Using를 진행중으로 바꿈
			iHomeProcUsing[iUnit][iSelectAxis] = 2;
			iThreadStep = 7000;
		}

		break;

	case 7000:

		if( iHomeProcUsing[iUnit][iSelectAxis] != 0 )
		{
			iHomFlag = IsCompleted_Home_Search(iUnit, iSelectAxis);
			if( iHomFlag < 1 )
			{
				sMsg.Format("[ 개별원점 ] 원점 동작 Error 발생 정지.");
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
				iThreadStep = -7000;
				break;

			}
			if( iHomFlag == 1 ){
				m_bOrgFlag[iUnit][iSelectAxis] = DEF_ORIGIN_COMPLETE;
				iThreadStep = 10000;
			}
		}

		break;


	case 10000:	//완료 종료
		sMsg.Format("[ 개별원점 ] 원점 복귀 동작이 완료되었습니다.");
		g_PushLogQueue(sMsg, DEF_TYPE_MOTIONLOG  + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_MOTIONLOG  + GetUnitNum(iUnit), (LPARAM)&sMsg);
		break;

	default:
		iThreadStep = -8000;

		break;
	}

	return iThreadStep;
}


int AxlMotorSet::HomeSingleProcess_UNIT2(int iUseStep)
{// [ UNIT1 ] 개별 원점 동작
	int iUnit = UNIT2;
	CString sMsg;
	int iThreadStep = 0, iHomFlag = 0;
	double dVel,dAcc;
	double dFTime = 0;
	DWORD dwReturn;

	iThreadStep = iUseStep;
	//현재 개별원점을 실행할 번호를 선택한다.
	int iSelectAxis = iSelectAxisss[iUnit];

	// 	for( int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++){	
	// 		if(iHomeProcUsing[iUnit][iAxis] == 1 )		//요구 신호 확인
	// 		{
	// 			iSelectAxis	= iAxis;	
	// 			break;
	// 		}
	// 	}	

	switch(iThreadStep)
	{
	case 1000:  //CL Y   -리밋으로 이동
		iThreadStep = 2000;
		break;
		dVel = 10 * sysData.fMotorResol[iUnit][MotCL_Y];
		dAcc = Motor.CalcAcc_G(iUnit,MotCL_Y);

		dwReturn = AxmMoveSignalSearch(MotCL_Y  + (CUR_MOTOR_NO * iUnit), -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ 개별원점] %s (-) Limit 이동 지령 실패.", MOTOR_NAME[MotCL_Y]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -1000;
		}
		else
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 1500;
		}
		break;

	case 1500:// CL Y -리밋 센서 신호 확인

		if( GetStopAxis(iUnit, MotCL_Y) &&
			GetNegaSensor(iUnit, MotCL_Y) )
		{
			iThreadStep = 2000;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dFTime))	
		{
			sMsg.Format("[ 개별원점] CL Y (-) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -1000;	
		}
		break;

	case 2000:
		if(ProcLENS[iUnit].OUT_LensGrip(BACKWARD))
		{
			iThreadStep = 2500;
			dFTime = func_TimeChecker_CurrentTime(true);
		}
		else
		{
			sMsg.Format("[ 개별원점] LENS GRIP 후진 실패");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -2000;
		}
		break;

		//20151108 ksg // 원점 복귀 그립후 딜레이 추가
	case 2500:
		if(ProcLENS[iUnit].IN_LensGrip(BACKWARD))
		{
			iThreadStep = 2600; //3000;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dFTime))
		{
			sMsg.Format("[ 개별원점] LENS GRIP 후진 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -1000;
		}
		break;

		//20151117 ksg
	case 2600:
		if(::func_TimeChecker_Compare(model.SilinderDelay[iUnit][DELAY_GRIP], dFTime))
		{
			iThreadStep = 2700;
		}
		break;

		//실린더 추가
	case 2700:
		if(ProcLENS[iUnit].OUT_Lens_Pusher(CYL_UP))
		{
			iThreadStep = 2800;
			dFTime = func_TimeChecker_CurrentTime(true);
		}
		else
		{
			sMsg.Format("[ 전체원점] LENS PUSHER 상승 실패");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -2700;
		}
		break;

	case 2800:
		if(ProcLENS[iUnit].IN_Lens_Pusher(CYL_UP))
		{
			iThreadStep = 3000;
			dFTime = func_TimeChecker_CurrentTime(true);
		}
		else if(::func_TimeChecker_Compare(TIME_AXIS, dFTime))
		{
			sMsg.Format("[ 전체원점] LENS PUSHER 상승 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -2700;
		}
		break;

	case 3000:
		//LENS Z가 원점이 잡혀있으면 대기위치, 아니면 리밋까지.
		if(Motor.GetAmpEnable(iUnit,MotLENS_Z ) == false)
		{
			if(Motor.AmpEnable(iUnit ,MotLENS_Z))		
				Motor.m_bAxisState[iUnit][MotLENS_Z] = true;
		}

		dVel = sysData.fMotorSpeed[iUnit][MotLENS_Z] * sysData.fMotorResol[iUnit][MotLENS_Z];
		dAcc = Motor.CalcAcc_G(iUnit,MotLENS_Z);

		dwReturn = AxmMoveSignalSearch(MotLENS_Z + (CUR_MOTOR_NO * iUnit), dVel, dAcc, PosEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{ 
			sMsg.Format("[ 개별원점] %s (+) Limit 이동 지령 실패.", MOTOR_NAME[MotLENS_Z]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -3000;
		}
		else
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 3500;			
		}

		break;

	case 3500://! Lens Z축 (+)Limit센서 신호 확인
		if( GetStopAxis(iUnit, MotLENS_Z) &&
			GetPosiSensor(iUnit, MotLENS_Z) )
		{

			if(iSelectAxis == MotLENS_X || iSelectAxis == MotLENS_Z || iSelectAxis == MotLENS_Tx || iSelectAxis == MotLENS_Ty)
			{
				iThreadStep = 4000;
			}
			else
			{
				iThreadStep = 5000;
			}
		}			
		else if(func_TimeChecker_Compare(TIME_DELAY + 5000, dFTime))	//시간 초과
		{
			sMsg.Format("[ 개별원점] LENS Z축 (+)LIMIT 이동 시간 초과");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -3000;
		}
		break;

	case 4000:  //LENS Y   +리밋으로 이동
		if(Motor.GetAmpEnable(iUnit,MotLENS_Y ) == false)
		{
			if(Motor.AmpEnable(iUnit ,MotLENS_Y))		
				Motor.m_bAxisState[iUnit][MotLENS_Y] = true;
		}

		dVel = sysData.fMotorSpeed[iUnit][MotLENS_Y] * sysData.fMotorResol[iUnit][MotLENS_Y];
		dAcc = Motor.CalcAcc_G(iUnit,MotLENS_Y); 

		dwReturn = AxmMoveSignalSearch(MotLENS_Y  + (CUR_MOTOR_NO * iUnit ), dVel, dAcc, PosEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ 개별원점] %s (-) Limit 이동 지령 실패.", MOTOR_NAME[MotLENS_Y]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -4000;
		}
		else
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 4500;
		}
		break;

	case 4500:// LENS Y +리밋 센서 신호 확인

		if( GetStopAxis(iUnit, MotLENS_Y) &&
			GetPosiSensor(iUnit, MotLENS_Y) )
		{
			iThreadStep = 5000;
		}
		else if(func_TimeChecker_Compare(TIME_DELAY + 10000, dFTime))	//시간 초과
		{
			sMsg.Format("[ 개별원점] LENS Y (-) LIMIT 센서 신호 확인 시간 초과");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -3000;
		}

		break;

	case 5000:
		//! PCB T축 리미트까지 이동
		if( MotPCB_T == iSelectAxis )
		{
			/*dVel = 50 * sysData.fMotorResol[iUnit][MotPCB_T];
			dAcc = 1;
			dwReturn = AxmMoveSignalSearch(MotPCB_T + (CUR_MOTOR_NO*iUnit), -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);*/

			dVel = 10 * sysData.fMotorResol[iUnit][MotPCB_T];
			dAcc = Motor.CalcAcc_G(iUnit,MotPCB_T);

			dwReturn = AxmMoveSignalSearch(MotPCB_T + (CUR_MOTOR_NO * iUnit), -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

			if ( dwReturn != AXT_RT_SUCCESS )
			{
				sMsg.Format("[ 개별원점] %s (-) Limit 이동 지령 실패.", MOTOR_NAME[MotPCB_T]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
				iThreadStep = -5000;
			}
			else
			{
				iThreadStep = 5500;
				dFTime = func_TimeChecker_CurrentTime(true);
			}
		}
		else 
		{
			iThreadStep = 6000;
		}
		break;

	case 5500:
		if( GetStopAxis(iUnit, MotPCB_T) &&
			GetNegaSensor(iUnit, MotPCB_T) )
		{
			iThreadStep = 6000;
		}
		else if(func_TimeChecker_Compare(TIME_DELAY, dFTime))	//시간 초과
		{
			sMsg.Format("[ 개별원점] PCB T (-) LIMIT 센서 신호 확인 시간 초과");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -5000;
		}
		break;

	case 6000:

		//선택된 축 홈찾기 진행
		if(Start_Home_Search(iUnit, iSelectAxis) < 0 )
		{	//에러시 
			sMsg.Format("[ 개별원점 ] 원점 동작 지령 실패.");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -6000;
		}
		else{	//성공일때 Using를 진행중으로 바꿈
			iHomeProcUsing[iUnit][iSelectAxis] = 2;
			iThreadStep = 7000;
		}
		break;

	case 7000:

		if( iHomeProcUsing[iUnit][iSelectAxis] != 0 )
		{
			iHomFlag = IsCompleted_Home_Search(iUnit, iSelectAxis);
			if( iHomFlag < 1 )
			{
				sMsg.Format("[ 개별원점 ] 원점 동작 Error 발생 정지.");
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
				iThreadStep = -7000;
				break;
			}
			if( iHomFlag == 1 ){
				m_bOrgFlag[iUnit][iSelectAxis] = DEF_ORIGIN_COMPLETE;
				iThreadStep = 10000;
			}
		}
		break;

	case 10000:	//완료 종료
		sMsg.Format("[ 개별원점 ] 원점 복귀 동작이 완료되었습니다.");
		g_PushLogQueue(sMsg, DEF_TYPE_MOTIONLOG  + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_MOTIONLOG  + GetUnitNum(iUnit), (LPARAM)&sMsg);
		break;

	default:
		iThreadStep = -8000;

		break;
	}

	return iThreadStep;
}

DWORD ThreadHomeProcessAA1(AxlMotorSet* pAxlMotorSet)	
{// [ UNIT1 ] 개별 원점 동작
	int iUnit = UNIT1;

	CString sMsg;
	int iThreadStep = 1000, iHomFlag = 0;
	double dFTime = 0;

	//현재 개별원점을 실행할 번호를 선택한다.
	int iSelectAxis;

	for( int iAxiss = 0; iAxiss < CUR_MOTOR_NO; iAxiss++){	
		if( pAxlMotorSet->iHomeProcUsing[iUnit][iAxiss] == 1 )		//요구 신호 확인
		{
			pAxlMotorSet->iSelectAxisss[iUnit]	= iAxiss;	
			break;
		}
	}

	iSelectAxis = pAxlMotorSet->iSelectAxisss[iUnit];

	if(iSelectAxis < 0 || iSelectAxis > 8)
		return TRUE;

	pAxlMotorSet->bThreadHome[iUnit] = true;
	while(pAxlMotorSet->bThreadHome[iUnit])
	{

		Sleep(5);

		//원점 찾기가 시작되었을 시점부터 검사
		if(pAxlMotorSet->iHomeProcUsing[iUnit][iSelectAxis] == 2)
		{
			//Amp 알람 체크
			if( pAxlMotorSet->GetAmpFault(iUnit, iSelectAxis) == true )
			{
				sMsg.Format("[ 개별원점] 원점 검색 중 AMP 알람 발생.");
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
				pAxlMotorSet->bThreadHome[iUnit] = false;
				break;
			}

			//서보온 체크
			if( pAxlMotorSet->GetAmpEnable(iUnit, iSelectAxis) == false )
			{
				sMsg.Format("[ 개별원점] 원점 검색 중 Servo Off 알람 발생.");
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);

				pAxlMotorSet->bThreadHome[iUnit] = false;
				break;
			}	

		}
		
		if(iThreadStep >= 1000 && iThreadStep < 10000)		
			iThreadStep = pAxlMotorSet->HomeSingleProcess_UNIT1(iThreadStep);
		else
		{
			//원점 Thread 완료 동작
			break;
		}

		if( iThreadStep < 0 )
		{//에러 발생 동작 정지.

			iHomFlag = pAxlMotorSet->IsCompleted_Home_Search(iUnit, iSelectAxis);
			if( iHomFlag == 2 )
			{
				pAxlMotorSet->Stop_Home_Search(iUnit, iSelectAxis);
				pAxlMotorSet->m_bOrgFlag[iUnit][iSelectAxis] = false;
			}	
			break;	
		}

	}

	pAxlMotorSet->iHomeProcUsing[iUnit][iSelectAxis] = 0;	//개별 원점 요청 초기화

	pAxlMotorSet->m_hThreadHome[iUnit] = NULL;

	pAxlMotorSet->bThreadHome[iUnit] = false;

	return TRUE;
}

DWORD ThreadHomeProcessAA2(AxlMotorSet* pAxlMotorSet)	
{// [ UNIT2 ] 개별 원점 동작
	int iUnit = UNIT2;

	CString sMsg;
	int iThreadStep = 1000, iHomFlag = 0;
	double dFTime = 0;

	//현재 개별원점을 실행할 번호를 선택한다.
	int iSelectAxis;

	for( int iAxiss = 0; iAxiss < CUR_MOTOR_NO; iAxiss++){	
		if( pAxlMotorSet->iHomeProcUsing[iUnit][iAxiss] == 1 )		//요구 신호 확인
		{
			pAxlMotorSet->iSelectAxisss[iUnit]	= iAxiss;	
			break;
		}
	}

	iSelectAxis = pAxlMotorSet->iSelectAxisss[iUnit];

	if(iSelectAxis < 0 || iSelectAxis > 8)
		return TRUE;

	pAxlMotorSet->bThreadHome[iUnit] = true;

	while(pAxlMotorSet->bThreadHome[iUnit])
	{

		Sleep(5);

		//원점 찾기가 시작되었을 시점부터 검사
		//iSelectAxis = 5;
		if(pAxlMotorSet->iHomeProcUsing[iUnit][iSelectAxis] == 2)
		{
			//Amp 알람 체크
			if( pAxlMotorSet->GetAmpFault(iUnit, iSelectAxis) == true )
			{
				sMsg.Format("[ 개별원점] 원점 검색 중 AMP 알람 발생.");
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
				pAxlMotorSet->bThreadHome[iUnit] = false;
				break;
			}

			//서보온 체크
			if( pAxlMotorSet->GetAmpEnable(iUnit, iSelectAxis) == false )
			{
				sMsg.Format("[ 개별원점] 원점 검색 중 Servo Off 알람 발생.");
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);

				pAxlMotorSet->bThreadHome[iUnit] = false;
				break;
			}	

		}

		if(iThreadStep >= 1000 && iThreadStep < 10000)		
			iThreadStep = pAxlMotorSet->HomeSingleProcess_UNIT2(iThreadStep);
		else
		{
			//원점 Thread 완료 동작
			break;
		}

		if( iThreadStep < 0 )
		{//에러 발생 동작 정지.

			iHomFlag = pAxlMotorSet->IsCompleted_Home_Search(iUnit, iSelectAxis);
			if( iHomFlag == 2 )
			{
				pAxlMotorSet->Stop_Home_Search(iUnit, iSelectAxis);
				pAxlMotorSet->m_bOrgFlag[iUnit][iSelectAxis] = false;
			}	
			break;	
		}

	}

	pAxlMotorSet->iHomeProcUsing[iUnit][iSelectAxis] = 0;	//개별 원점 요청 초기화

	pAxlMotorSet->m_hThreadHome[iUnit] = NULL;

	pAxlMotorSet->bThreadHome[iUnit] = false;

	return TRUE;
}

//---------------------------매뉴얼 AA ----------------------------------
DWORD ThreadManualFocusUNIT1(AxlMotorSet* pAxlMotorSet)
{
	//int iUnit = UNIT1;
	CString sMsg, str;
	int iRtnStep = 0;

	CCPreFocusingAADlg* pFrame = (CCPreFocusingAADlg*)AfxGetApp()->m_pMainWnd;

	DWORD dwRet = 0;
	long  AxisCount;

	Task[UNIT1].AutoFlag = 1;			//자동 플래그 온
	Task[UNIT1].bRunningReady = false;	//운전준비 풀기

	pAxlMotorSet->iManualStep[UNIT1] = 130000;

	while(pAxlMotorSet->m_hThreadManualFocus[UNIT1])
	{
		Sleep(5);
		int bChk = 0;

		dwRet = AxmInfoGetAxisCount(&AxisCount);
		if ( dwRet != AXT_RT_SUCCESS )
		{//! Servo 전원이 떨어지면 모든 상황을 정지 하여야 한다.
			sMsg.Format("[ ERROR ] AXT Board 인식 실패.. 매뉴얼 AA 동작을 정지 합니다.");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT1));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT1), (LPARAM)&sMsg);
			pAxlMotorSet->m_bThreadManualFocus[UNIT1] = false;
			pAxlMotorSet->m_hThreadManualFocus[UNIT1] = NULL;
			return FALSE;
		}

		bool bAlarmLimit = true;
		for (int i=0; i<CUR_MOTOR_NO; i++)
		{
			if( pAxlMotorSet->GetAmpFault(UNIT1, i) )
			{
				sMsg.Format("[ ERROR ] 매뉴얼 AA 동작 중 AMP 알람 감지 AXIS : %s",MOTOR_NAME[i]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT1));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(UNIT1), (LPARAM)&sMsg);
				pAxlMotorSet->m_bThreadManualFocus[UNIT1] = false;
				pAxlMotorSet->m_hThreadManualFocus[UNIT1] = NULL;
				return FALSE;
			}

			if( !Motor.GetAmpEnable(UNIT1, i) )		//TRUE : ON
			{
				sMsg.Format("[ ERROR ] 매뉴얼 AA 동작 중 SERVO OFF 감지 AXIS : %s",MOTOR_NAME[i]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT1));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(UNIT1), (LPARAM)&sMsg);
				pAxlMotorSet->m_bThreadManualFocus[UNIT1] = false;
				pAxlMotorSet->m_hThreadManualFocus[UNIT1] = NULL;
				return FALSE;
			}

			if( Motor.GetNegaSensor(UNIT1, i) )
			{//kdu 리밋 감지시 일시정지
				sMsg.Format("[ ERROR ] 매뉴얼 AA 동작 중 ( - ) Limit 감지 AXIS : %s",MOTOR_NAME[i]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT1));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(UNIT1), (LPARAM)&sMsg);
				pAxlMotorSet->m_bThreadManualFocus[UNIT1] = false;
				pAxlMotorSet->m_hThreadManualFocus[UNIT1] = NULL;
				return FALSE;
			}

			if( Motor.GetPosiSensor(UNIT1, i) )
			{//kdu 리밋 감지시 일시정지
				sMsg.Format("[ ERROR ] 매뉴얼 AA 동작 중 ( + ) Limit 감지 AXIS : %s",MOTOR_NAME[i]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT1));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(UNIT1), (LPARAM)&sMsg);
				pAxlMotorSet->m_bThreadManualFocus[UNIT1] = false;
				pAxlMotorSet->m_hThreadManualFocus[UNIT1] = NULL;
				return FALSE;
			}
		}
		if(Task[UNIT1].AutoFlag == 0 || Task[UNIT1].AutoFlag == 2)			break;

		if(pAxlMotorSet->iManualStep[UNIT1] >= 130000 && pAxlMotorSet->iManualStep[UNIT1] < 160000)			iRtnStep = ProcAA[UNIT1].RunProc_Manual_AA(pAxlMotorSet->iManualStep[UNIT1])	;					//0

		//!! Thread 다음 동작 처리 및 상태 처리.(0 이하 일 경우 Alarm 발생 상태)
		pAxlMotorSet->iManualStep[UNIT1] = abs(iRtnStep);	//Error 발생.. iRunStep에서 -1을 곱하면 재동작시 시작 번호가됨.

		if( iRtnStep < 0 || iRtnStep > 159000)
		{
			pAxlMotorSet->m_bThreadManualFocus[UNIT1] = false;
			//정지
			Task[UNIT1].AutoFlag = 0;
			break;
		}

		Sleep(5);
		DoSleepEvents();

	}

	pAxlMotorSet->m_bThreadManualFocus[UNIT1] = false;
	pAxlMotorSet->m_hThreadManualFocus[UNIT1] = NULL;

	return TRUE;
}


DWORD ThreadManualFocusUNIT2(AxlMotorSet* pAxlMotorSet)
{
	//int iUnit = UNIT2;
	CString sMsg, str;
	int iRtnStep = 0;

	CCPreFocusingAADlg* pFrame = (CCPreFocusingAADlg*)AfxGetApp()->m_pMainWnd;

	DWORD dwRet = 0;
	long  AxisCount;

	Task[UNIT2].AutoFlag = 1;			//자동 플래그 온
	Task[UNIT2].bRunningReady = false;	//운전준비 풀기

	pAxlMotorSet->iManualStep[UNIT2] = 130000;

	while(pAxlMotorSet->m_hThreadManualFocus[UNIT2])
	{
		Sleep(5);
		int bChk = 0;

		dwRet = AxmInfoGetAxisCount(&AxisCount);
		if ( dwRet != AXT_RT_SUCCESS )
		{//! Servo 전원이 떨어지면 모든 상황을 정지 하여야 한다.
			sMsg.Format("[ ERROR ] AXT Board 인식 실패.. 자동 동작을 정지 합니다.");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT2));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT2), (LPARAM)&sMsg);
			pAxlMotorSet->m_bThreadManualFocus[UNIT2] = false;
			pAxlMotorSet->m_hThreadManualFocus[UNIT2] = NULL;
			return FALSE;
		}

		bool bAlarmLimit = true;
		for (int i=0; i<CUR_MOTOR_NO; i++)
		{
			if( pAxlMotorSet->GetAmpFault(UNIT2, i) )
			{
				sMsg.Format("[ ERROR ] 매뉴얼 AA 동작 중 AMP 알람 감지 AXIS : %s",MOTOR_NAME[i]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT2));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(UNIT2), (LPARAM)&sMsg);
				pAxlMotorSet->m_bThreadManualFocus[UNIT2] = false;
				pAxlMotorSet->m_hThreadManualFocus[UNIT2] = NULL;
				return FALSE;
			}

			if( !Motor.GetAmpEnable(UNIT2, i) )		//TRUE : ON
			{
				sMsg.Format("[ ERROR ] 매뉴얼 AA 동작 중 SERVO OFF 감지 AXIS : %s",MOTOR_NAME[i]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT2));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(UNIT2), (LPARAM)&sMsg);
				pAxlMotorSet->m_bThreadManualFocus[UNIT2] = false;
				pAxlMotorSet->m_hThreadManualFocus[UNIT2] = NULL;
				return FALSE;
			}

			if( Motor.GetNegaSensor(UNIT2, i) )
			{//kdu 리밋 감지시 일시정지
				sMsg.Format("[ ERROR ] 매뉴얼 AA 동작 중 ( - ) Limit 감지 AXIS : %s",MOTOR_NAME[i]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT2));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(UNIT2), (LPARAM)&sMsg);
				pAxlMotorSet->m_bThreadManualFocus[UNIT2] = false;
				pAxlMotorSet->m_hThreadManualFocus[UNIT2] = NULL;
				return FALSE;
			}

			if( Motor.GetPosiSensor(UNIT2, i) )
			{//kdu 리밋 감지시 일시정지
				sMsg.Format("[ ERROR ] 매뉴얼 AA 동작 중 ( + ) Limit 감지 AXIS : %s",MOTOR_NAME[i]);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT2));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(UNIT2), (LPARAM)&sMsg);
				pAxlMotorSet->m_bThreadManualFocus[UNIT2] = false;
				pAxlMotorSet->m_hThreadManualFocus[UNIT2] = NULL;
				return FALSE;
			}
		}
		if(Task[UNIT2].AutoFlag == 0 || Task[UNIT2].AutoFlag == 2)			break;

		if(pAxlMotorSet->iManualStep[UNIT2] >= 130000 && pAxlMotorSet->iManualStep[UNIT2] < 160000)			iRtnStep = ProcAA[UNIT2].RunProc_Manual_AA(pAxlMotorSet->iManualStep[UNIT2])	;					//0

		//!! Thread 다음 동작 처리 및 상태 처리.(0 이하 일 경우 Alarm 발생 상태)
		pAxlMotorSet->iManualStep[UNIT2] = abs(iRtnStep);	//Error 발생.. iRunStep에서 -1을 곱하면 재동작시 시작 번호가됨.

		if( iRtnStep < 0 || iRtnStep > 159000)
		{
			pAxlMotorSet->m_bThreadManualFocus[UNIT2] = false;
			//정지
			Task[UNIT2].AutoFlag = 0;
			break;
		}

		Sleep(5);
		DoSleepEvents();

	}

	pAxlMotorSet->m_bThreadManualFocus[UNIT2] = false;
	pAxlMotorSet->m_hThreadManualFocus[UNIT2] = NULL;

	return TRUE;
}

//-----------------------------------------------------------------------
 

//---------------------------자아동
DWORD ThreadAutoFocusUNIT1(AxlMotorSet* pAxlMotorSet)
{
	//int iUnit = UNIT1;
	CString sMsg, str;
	int iRtnStep = 0;
//	char szVer[SIZE_OF_100BYTE];		//20160828 JJC
	CCPreFocusingAADlg* pFrame = (CCPreFocusingAADlg*)AfxGetApp()->m_pMainWnd;

	DWORD dwRet = 0;
	//long  AxisCount;

	if( Task[UNIT1].AutoFlag != 2 )		//일시 정지가 아닐때.
	{
		if(Task[UNIT1].iLensStatus != 0)
		{
			if(Task[UNIT1].iLensStatus == 1)		//완제품 배출
			{
				ProcAA[UNIT1].bInspOk = true;
			}
			else if(Task[UNIT1].iLensStatus == 2)	//불량 배출
			{
				ProcAA[UNIT1].bInspOk = false;
			}

			//소켓언로딩
			pAxlMotorSet->iRunStep[UNIT1] = 250000;
		}
	}

	if( Task[UNIT1].AutoFlag == 2 )		//일시정지시 
	{
		str.Format("###%d", Task[UNIT1].iExhaust);
		g_PushLogQueue(str, DEF_TYPE_ERRORLOG + GetUnitNum(UNIT1));
		//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + GetUnitNum(UNIT1), (LPARAM)&str);

		if(Task[UNIT1].iExhaust != 0)		// 배출
		{
			pAxlMotorSet->iRunStep[UNIT1] = 400000;
		}
	}

	Task[UNIT1].AutoFlag = 1;			//자동 플래그 온
	Task[UNIT1].bRunningReady = false;	//운전준비 풀기

	while(pAxlMotorSet->m_hThreadAutoFocus[UNIT1])
	{
		Sleep(5);
		int bChk = 0;

		//dwRet = AxmInfoGetAxisCount(&AxisCount);
		//if ( dwRet != AXT_RT_SUCCESS )
		//{//! Servo 전원이 떨어지면 모든 상황을 정지 하여야 한다.
		//	sMsg.Format("[ ERROR ] AXT Board 인식 실패.. 자동 동작을 정지 합니다.");
		//	::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT1), (LPARAM)&sMsg);
		//	pAxlMotorSet->m_bThreadAutoFocus[UNIT1] = false;
		//	pAxlMotorSet->m_hThreadAutoFocus[UNIT1] = NULL;
		//	return FALSE;
		//}

		//bool bAlarmLimit = true;
		//for (int i=0; i<CUR_MOTOR_NO; i++)
		//{
		//	if( pAxlMotorSet->GetAmpFault(UNIT1, i) )
		//	{
		//		sMsg.Format("[ ERROR ][ 자동운전 ] 자동 운전 중 AMP 알람 감지 AXIS : %s",MOTOR_NAME[i]);
		//		::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(UNIT1), (LPARAM)&sMsg);
		//		pAxlMotorSet->m_bThreadAutoFocus[UNIT1] = false;
		//		pAxlMotorSet->m_hThreadAutoFocus[UNIT1] = NULL;
		//		return FALSE;
		//	}

		//	if( !Motor.GetAmpEnable(UNIT1, i) )		//TRUE : ON
		//	{
		//		sMsg.Format("[ ERROR ][ 자동운전 ] 자동 운전 중 SERVO OFF 감지 AXIS : %s",MOTOR_NAME[i]);
		//		::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(UNIT1), (LPARAM)&sMsg);
		//		pAxlMotorSet->m_bThreadAutoFocus[UNIT1] = false;
		//		pAxlMotorSet->m_hThreadAutoFocus[UNIT1] = NULL;
		//		return FALSE;
		//	}

		//	if( Motor.GetNegaSensor(UNIT1, i) )
		//	{//kdu 리밋 감지시 일시정지
		//		sMsg.Format("[ ERROR ][ 자동운전 ] 자동 운전 중 ( - ) Limit 감지 AXIS : %s",MOTOR_NAME[i]);
		//		::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(UNIT1), (LPARAM)&sMsg);
		//		pAxlMotorSet->m_bThreadAutoFocus[UNIT1] = false;
		//		pAxlMotorSet->m_hThreadAutoFocus[UNIT1] = NULL;
		//		return FALSE;
		//	}

		//	if( Motor.GetPosiSensor(UNIT1, i) )
		//	{//kdu 리밋 감지시 일시정지
		//		sMsg.Format("[ ERROR ][ 자동운전] 자동 운전 중 ( + ) Limit 감지 AXIS : %s",MOTOR_NAME[i]);
		//		::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(UNIT1), (LPARAM)&sMsg);
		//		pAxlMotorSet->m_bThreadAutoFocus[UNIT1] = false;
		//		pAxlMotorSet->m_hThreadAutoFocus[UNIT1] = NULL;
		//		return FALSE;
		//	}
		//}

		/*
		Lens Socket Loading : 받아서 센터링 전진까지
		PCB_Bonding  : 센터링 전진상태 부터 본딩위치 까지
		Lens_Loading : 공급위치에서 보정값 받고 집어서 그립전진
		Lens_Bonding : 본딩위치로 이동
		Lens_Release : UV 쏜 후 그립 해제 상승 까지만.
		PCB_Unloading : LENS, PCB 둘다 배출,대기위치로 이동.
		ULD_MODE :  본딩에서 GRIP 잡지 않고 이모드로 빠짐.(렌즈위치는 일단 대기위치)


		//푸셔,
		Align 후 PCB T 돌리는것 ( 그립잡고 T 돌리고) <-- RunProc_Lens_Loading 

		Align 
		보정량 측정
		체결 측정 -> Lens_Loading전에 
		도포 검사
		*/
		if( Task[UNIT1].AutoFlag == 0 )			break;
		
		if( Task[UNIT1].AutoFlag == MODE_PAUSE )
		{
			if( pAxlMotorSet->iRunStep[UNIT1] >= 198000 && pAxlMotorSet->iRunStep[UNIT1] < 210000 )
			{//! 일시 정지변경에서. UV_ON일경우 끝나고 빠지기
				iRtnStep = ProcUV[UNIT1].RunProc_UV(pAxlMotorSet->iRunStep[UNIT1]);	

				pAxlMotorSet->iRunStepOrg[UNIT1] = pAxlMotorSet->iRunStep[UNIT1];
				pAxlMotorSet->iRunStep[UNIT1] = abs(iRtnStep);	//Error 발생.. iRunStep에서 -1을 곱하면 재동작시 시작 번호가됨.

				if( iRtnStep < 0 )
				{//- 알람 발생시, 정지
					ProcLENS[UNIT1].OUT_UV_LAMP(UV_OFF);
					pAxlMotorSet->m_bThreadAutoFocus[UNIT1] = false;
					break;
				}
			}
			else
			{
				pAxlMotorSet->m_bThreadAutoFocus[UNIT1] = false;
				break;
			}

			continue;
		}

		if( Task[UNIT1].AutoFlag != 1 )
		{
			pAxlMotorSet->m_bThreadAutoFocus[UNIT1] = false;
			Task[UNIT1].AutoFlag = 2;		
			break;
		}

		str.Format("[ AUTO STEP : %d ]", pAxlMotorSet->iRunStep[UNIT1]);
	//	pFrame->m_btn_title1.CallFlashFunction("Version", "%s", str);
		//sprintf_s(szVer, SIZE_OF_100BYTE, "[ STEP : %d ]", iRunStep[UNIT1]);			//20160828 JJC
		pFrame->stcVersion[UNIT1].SetWindowTextA(str);


		if(pAxlMotorSet->iRunStep[UNIT1] >= 10000 && pAxlMotorSet->iRunStep[UNIT1] < 30000)			iRtnStep = ProcPCB[UNIT1].RunProc_Socket_Loading(pAxlMotorSet->iRunStep[UNIT1])	;					//0
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 30000 && pAxlMotorSet->iRunStep[UNIT1] < 50000)	iRtnStep = ProcPCB[UNIT1].RunProc_Bonding(pAxlMotorSet->iRunStep[UNIT1]);							//O

		else if(pAxlMotorSet->iRunStep[UNIT1] >= 50000 && pAxlMotorSet->iRunStep[UNIT1] < 60000)	iRtnStep = ProcAA[UNIT1].AlignProc_Barrel(pAxlMotorSet->iRunStep[UNIT1]);																			
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 60000 && pAxlMotorSet->iRunStep[UNIT1] < 70000)	iRtnStep = ProcAA[UNIT1].AlignProc_Cylinder(pAxlMotorSet->iRunStep[UNIT1]);	
		//else if(pAxlMotorSet->iRunStep[UNIT1] >= 70000 && pAxlMotorSet->iRunStep[UNIT1] < 80000)		iRtnStep = ProcAA[UNIT1].AlignProc_Lens(pAxlMotorSet->iRunStep[UNIT1]);		//20160111JJC NV UT 플로우 합침	
#ifdef ON_MODEL_NV
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 70000 && pAxlMotorSet->iRunStep[UNIT1] < 79000)	iRtnStep = ProcAA[UNIT1].AlignProc_NVLens(pAxlMotorSet->iRunStep[UNIT1]);																			
#else
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 70000 && pAxlMotorSet->iRunStep[UNIT1] < 79000)	iRtnStep = ProcAA[UNIT1].AlignProc_Lens(pAxlMotorSet->iRunStep[UNIT1]);																			
#endif
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 79000 && pAxlMotorSet->iRunStep[UNIT1] < 90000)	iRtnStep = ProcAA[UNIT1].AlignProc_Chart(pAxlMotorSet->iRunStep[UNIT1]);																			

		//else if(pAxlMotorSet->iRunStep[UNIT1] >= 50000 && pAxlMotorSet->iRunStep[UNIT1] < 90000)	iRtnStep = ProcAA[UNIT1].RunProc_Align(pAxlMotorSet->iRunStep[UNIT1]);																			
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 90000 && pAxlMotorSet->iRunStep[UNIT1] < 110000)	iRtnStep = ProcLENS[UNIT1].RunProc_Lens_Loading(pAxlMotorSet->iRunStep[UNIT1]);//Lens Loading		//O
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 110000 && pAxlMotorSet->iRunStep[UNIT1] < 130000)	iRtnStep = ProcLENS[UNIT1].RunProc_Bonding(pAxlMotorSet->iRunStep[UNIT1]);	//Lens Bonding			//O
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 130000 && pAxlMotorSet->iRunStep[UNIT1] < 170000)	iRtnStep = ProcAA[UNIT1].RunProc_AA(pAxlMotorSet->iRunStep[UNIT1]);//AA								//O
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 170000 && pAxlMotorSet->iRunStep[UNIT1] < 190000)	iRtnStep = ProcAA[UNIT1].RunProc_ThroughFocus(pAxlMotorSet->iRunStep[UNIT1]);						//O
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 190000 && pAxlMotorSet->iRunStep[UNIT1] < 210000)	iRtnStep = ProcUV[UNIT1].RunProc_UV(pAxlMotorSet->iRunStep[UNIT1]);									//O
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 210000 && pAxlMotorSet->iRunStep[UNIT1] < 230000)	iRtnStep = ProcLENS[UNIT1].RunProc_Release(pAxlMotorSet->iRunStep[UNIT1]);							//O	
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 230000 && pAxlMotorSet->iRunStep[UNIT1] < 250000)	iRtnStep = ProcPCB[UNIT1].RunProc_UnLoading(pAxlMotorSet->iRunStep[UNIT1]);//PCB_UnLoading			//O
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 250000 && pAxlMotorSet->iRunStep[UNIT1] < 270000)	iRtnStep = ProcPCB[UNIT1].RunProc_Socket_Unloading(pAxlMotorSet->iRunStep[UNIT1]);					//0
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 300000 && pAxlMotorSet->iRunStep[UNIT1] < 330000)	iRtnStep = ProcAA[UNIT1].RunProc_ULD_MODE(pAxlMotorSet->iRunStep[UNIT1]);	//ULD MODE				//O
		//else if(pAxlMotorSet->iRunStep[UNIT1] >= 400000 && pAxlMotorSet->iRunStep[UNIT1] < 410000)	iRtnStep = ProcAA[UNIT1].RunProc_NG_MODE(pAxlMotorSet->iRunStep[UNIT1]);
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 400000 && pAxlMotorSet->iRunStep[UNIT1] < 406000)	iRtnStep = ProcAA[UNIT1].RunProc_NG_MODE(pAxlMotorSet->iRunStep[UNIT1]);//20160126JJC
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 410000 && pAxlMotorSet->iRunStep[UNIT1] < 415000)	iRtnStep = ProcPCB[UNIT1].RunProc_TiltSpecOut_Retry(pAxlMotorSet->iRunStep[UNIT1]);	//20160126JJC
		else if(pAxlMotorSet->iRunStep[UNIT1] >= 420000 && pAxlMotorSet->iRunStep[UNIT1] < 430000)	iRtnStep = ProcAA[UNIT1].AlignProc_AA_After_Align(pAxlMotorSet->iRunStep[UNIT1]);


		pAxlMotorSet->iRunStepOrg[UNIT1] = pAxlMotorSet->iRunStep[UNIT1];
		//!! Thread 다음 동작 처리 및 상태 처리.(0 이하 일 경우 Alarm 발생 상태)
		pAxlMotorSet->iRunStep[UNIT1] = abs(iRtnStep);	//Error 발생.. iRunStep에서 -1을 곱하면 재동작시 시작 번호가됨.

		if( iRtnStep < 0 )
		{
			CCPreFocusingAADlg* pFrame =(CCPreFocusingAADlg*)AfxGetApp()->m_pMainWnd;
			sMsg.Format("#AA%d@ALARM&ERR$", (sysData.m_iUnitNo*2)+UNIT1+1);
			pFrame->HidataSocket_ClientSend(UNIT1, sMsg);

			ProcLENS[UNIT1].OUT_UV_LAMP(UV_OFF);
			gCommUV.UV_Trigger(UNIT1 , 2 , DIO_OFF , model.iUVLightVal[UNIT1]);
			pAxlMotorSet->m_bThreadAutoFocus[UNIT1] = false;
			//일시정지에 불들어오게.
			Task[UNIT1].AutoFlag = 2;
			break;
		}

		Sleep(5);
		DoSleepEvents();

	}

	pAxlMotorSet->m_bThreadAutoFocus[UNIT1] = false;
	pAxlMotorSet->m_hThreadAutoFocus[UNIT1] = NULL;

	return TRUE;
}


DWORD ThreadAutoFocusUNIT2(AxlMotorSet* pAxlMotorSet)
{
	//int iUnit = UNIT2;
	CString sMsg, str;
	int iRtnStep = 0;
//	char szVer[SIZE_OF_100BYTE];		//20160828 JJC
	CCPreFocusingAADlg* pFrame = (CCPreFocusingAADlg*)AfxGetApp()->m_pMainWnd;

	DWORD dwRet = 0;
	//long  AxisCount;

	if(Task[UNIT2].AutoFlag != 2)		//일시 정지가 아닐때.
	{
		if(Task[UNIT2].iLensStatus != 0)
		{
			if(Task[UNIT2].iLensStatus == 1)		//완제품 배출
			{
				ProcAA[UNIT2].bInspOk = true;
			}
			else if(Task[UNIT2].iLensStatus == 2)	//불량 배출
			{
				ProcAA[UNIT2].bInspOk = false;
			}

			//소켓언로딩
			pAxlMotorSet->iRunStep[UNIT2] = 250000;

		}
	}

	if( Task[UNIT2].AutoFlag == 2 )		//일시정지시 
	{
		if(Task[UNIT2].iExhaust != 0)		// 배출
		{
			pAxlMotorSet->iRunStep[UNIT2] = 400000;
		}
	}

	Task[UNIT2].AutoFlag = 1;
	//운전준비 풀기
	Task[UNIT2].bRunningReady = false;

	while(pAxlMotorSet->m_hThreadAutoFocus[UNIT2])
	{
		Sleep(5);
		int bChk = 0;

		//dwRet = AxmInfoGetAxisCount(&AxisCount);
		//if ( dwRet != AXT_RT_SUCCESS )
		//{//! Servo 전원이 떨어지면 모든 상황을 정지 하여야 한다.
		//	sMsg.Format("[ ERROR ] AXT Board 인식 실패.. 자동 동작을 정지 합니다.");
		//	::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT2), (LPARAM)&sMsg);
		//	pAxlMotorSet->m_bThreadAutoFocus[UNIT2] = false;
		//	pAxlMotorSet->m_hThreadAutoFocus[UNIT2] = NULL;
		//	return FALSE;
		//}

		//bool bAlarmLimit = true;
		//for (int i=0; i<CUR_MOTOR_NO; i++)
		//{

		//	if( pAxlMotorSet->GetAmpFault(UNIT2, i) )
		//	{
		//		sMsg.Format("[ ERROR ][ 자동운전 ] 자동 운전 중 AMP 알람 감지 AXIS : %s",MOTOR_NAME[i]);
		//		::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(UNIT2), (LPARAM)&sMsg);
		//		pAxlMotorSet->m_bThreadAutoFocus[UNIT2] = false;
		//		pAxlMotorSet->m_hThreadAutoFocus[UNIT2] = NULL;
		//		return FALSE;
		//	}

		//	if( !Motor.GetAmpEnable(UNIT2, i) )		//TRUE : ON
		//	{
		//		sMsg.Format("[ ERROR ][ 자동운전 ] 자동 운전 중 SERVO OFF 감지 AXIS : %s",MOTOR_NAME[i]);
		//		::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(UNIT2), (LPARAM)&sMsg);
		//		pAxlMotorSet->m_bThreadAutoFocus[UNIT2] = false;
		//		pAxlMotorSet->m_hThreadAutoFocus[UNIT2] = NULL;
		//		return FALSE;
		//	}

		//	if( Motor.GetNegaSensor(UNIT2, i) )
		//	{//kdu 리밋 감지시 일시정지
		//		sMsg.Format("[ ERROR ][ 자동운전 ] 자동 운전 중 ( - ) Limit 감지 AXIS : %s",MOTOR_NAME[i]);
		//		::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(UNIT2), (LPARAM)&sMsg);
		//		pAxlMotorSet->m_bThreadAutoFocus[UNIT2] = false;
		//		pAxlMotorSet->m_hThreadAutoFocus[UNIT2] = NULL;
		//		return FALSE;
		//	}

		//	if( Motor.GetPosiSensor(UNIT2, i) )
		//	{//kdu 리밋 감지시 일시정지
		//		sMsg.Format("[ ERROR ][ 자동운전] 자동 운전 중 ( + ) Limit 감지 AXIS : %s",MOTOR_NAME[i]);
		//		::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(UNIT2), (LPARAM)&sMsg);
		//		pAxlMotorSet->m_bThreadAutoFocus[UNIT2] = false;
		//		pAxlMotorSet->m_hThreadAutoFocus[UNIT2] = NULL;
		//		return FALSE;
		//	}
		//}

		/*
		Lens Socket Loading : 받아서 센터링 전진까지
		PCB_Bonding  : 센터링 전진상태 부터 본딩위치 까지
		Lens_Loading : 공급위치에서 보정값 받고 집어서 그립전진
		Lens_Bonding : 본딩위치로 이동
		Lens_Release : UV 쏜 후 그립 해제 상승 까지만.
		PCB_Unloading : LENS, PCB 둘다 배출,대기위치로 이동.
		ULD_MODE :  본딩에서 GRIP 잡지 않고 이모드로 빠짐.(렌즈위치는 일단 대기위치)


		//푸셔,
		Align 후 PCB T 돌리는것 ( 그립잡고 T 돌리고) <-- RunProc_Lens_Loading 
		*/

		if( Task[UNIT2].AutoFlag == 0 )			break;

		if( Task[UNIT2].AutoFlag == MODE_PAUSE )
		{
			if( pAxlMotorSet->iRunStep[UNIT2] >= 198000 && pAxlMotorSet->iRunStep[UNIT2] < 210000 )
			{//! 일시 정지변경에서. UV_ON일경우 끝나고 빠지기
				iRtnStep = ProcUV[UNIT2].RunProc_UV(pAxlMotorSet->iRunStep[UNIT2]);	

				pAxlMotorSet->iRunStepOrg[UNIT2] = pAxlMotorSet->iRunStep[UNIT2];
				pAxlMotorSet->iRunStep[UNIT2] = abs(iRtnStep);	//Error 발생.. iRunStep에서 -1을 곱하면 재동작시 시작 번호가됨.

				if( iRtnStep < 0 )
				{//- 알람 발생시, 정지
					ProcLENS[UNIT2].OUT_UV_LAMP(UV_OFF);
					pAxlMotorSet->m_bThreadAutoFocus[UNIT2] = false;
					break;
				}
			}
			else
			{
				pAxlMotorSet->m_bThreadAutoFocus[UNIT2] = false;
				break;
			}

			continue;
		}

		if( Task[UNIT2].AutoFlag != 1 )
		{
			pAxlMotorSet->m_bThreadAutoFocus[UNIT2] = false;
			Task[UNIT2].AutoFlag = 2;
			break;
		}

		str.Format("[ AUTO STEP : %d ]", pAxlMotorSet->iRunStep[UNIT2]);
	//	pFrame->m_btn_title2.CallFlashFunction("Version", "%s", str);
//		sprintf_s(szVer, SIZE_OF_100BYTE, "[ STEP : %d ]", iRunStep[UNIT2]);			//20160828 JJC
		pFrame->stcVersion[UNIT2].SetWindowTextA(str);

		if(pAxlMotorSet->iRunStep[UNIT2] >= 10000 && pAxlMotorSet->iRunStep[UNIT2] < 30000)			iRtnStep = ProcPCB[UNIT2].RunProc_Socket_Loading(pAxlMotorSet->iRunStep[UNIT2])	;					//0
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 30000 && pAxlMotorSet->iRunStep[UNIT2] < 50000)	iRtnStep = ProcPCB[UNIT2].RunProc_Bonding(pAxlMotorSet->iRunStep[UNIT2]);
		//O
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 50000 && pAxlMotorSet->iRunStep[UNIT2] < 60000)	iRtnStep = ProcAA[UNIT2].AlignProc_Barrel(pAxlMotorSet->iRunStep[UNIT2]);																			
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 60000 && pAxlMotorSet->iRunStep[UNIT2] < 70000)	iRtnStep = ProcAA[UNIT2].AlignProc_Cylinder(pAxlMotorSet->iRunStep[UNIT2]);																			
	//	else if(pAxlMotorSet->iRunStep[UNIT2] >= 70000 && pAxlMotorSet->iRunStep[UNIT2] < 80000)	iRtnStep = ProcAA[UNIT2].AlignProc_Lens(pAxlMotorSet->iRunStep[UNIT2]);		//20160115JJC
#ifdef ON_MODEL_NV		//20160115JJC
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 70000 && pAxlMotorSet->iRunStep[UNIT2] < 79000)	iRtnStep = ProcAA[UNIT2].AlignProc_NVLens(pAxlMotorSet->iRunStep[UNIT2]);	
#else
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 70000 && pAxlMotorSet->iRunStep[UNIT2] < 79000/*80000*/)	iRtnStep = ProcAA[UNIT2].AlignProc_Lens(pAxlMotorSet->iRunStep[UNIT2]);																			
#endif
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 79000/*80000*/ && pAxlMotorSet->iRunStep[UNIT2] < 90000)	iRtnStep = ProcAA[UNIT2].AlignProc_Chart(pAxlMotorSet->iRunStep[UNIT2]);																			
		//else if(pAxlMotorSet->iRunStep[UNIT2] >= 50000 && pAxlMotorSet->iRunStep[UNIT2] < 90000)	iRtnStep = ProcAA[UNIT2].RunProc_Align(pAxlMotorSet->iRunStep[UNIT2]);	

		else if(pAxlMotorSet->iRunStep[UNIT2] >= 90000 && pAxlMotorSet->iRunStep[UNIT2] < 110000)	iRtnStep = ProcLENS[UNIT2].RunProc_Lens_Loading(pAxlMotorSet->iRunStep[UNIT2]);//Lens Loading	//O
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 110000 && pAxlMotorSet->iRunStep[UNIT2] < 130000)	iRtnStep = ProcLENS[UNIT2].RunProc_Bonding(pAxlMotorSet->iRunStep[UNIT2]);	//Lens Bonding			//O //배럴 측정 추가
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 130000 && pAxlMotorSet->iRunStep[UNIT2] < 170000)	iRtnStep = ProcAA[UNIT2].RunProc_AA(pAxlMotorSet->iRunStep[UNIT2]);//AA								//O
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 170000 && pAxlMotorSet->iRunStep[UNIT2] < 190000)	iRtnStep = ProcAA[UNIT2].RunProc_ThroughFocus(pAxlMotorSet->iRunStep[UNIT2]);						//O
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 190000 && pAxlMotorSet->iRunStep[UNIT2] < 210000)	iRtnStep = ProcUV[UNIT2].RunProc_UV(pAxlMotorSet->iRunStep[UNIT2]);								//O
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 210000 && pAxlMotorSet->iRunStep[UNIT2] < 230000)	iRtnStep = ProcLENS[UNIT2].RunProc_Release(pAxlMotorSet->iRunStep[UNIT2]);							//O	
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 230000 && pAxlMotorSet->iRunStep[UNIT2] < 250000)	iRtnStep = ProcPCB[UNIT2].RunProc_UnLoading(pAxlMotorSet->iRunStep[UNIT2]);//PCB_UnLoading			//O
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 250000 && pAxlMotorSet->iRunStep[UNIT2] < 270000)	iRtnStep = ProcPCB[UNIT2].RunProc_Socket_Unloading(pAxlMotorSet->iRunStep[UNIT2]);					//0
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 300000 && pAxlMotorSet->iRunStep[UNIT2] < 330000)	iRtnStep = ProcAA[UNIT2].RunProc_ULD_MODE(pAxlMotorSet->iRunStep[UNIT2]);	//ULD MODE				//O
		//else if(pAxlMotorSet->iRunStep[UNIT2] >= 400000 && pAxlMotorSet->iRunStep[UNIT2] < 410000)	iRtnStep = ProcAA[UNIT2].RunProc_NG_MODE(pAxlMotorSet->iRunStep[UNIT2]);
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 400000 && pAxlMotorSet->iRunStep[UNIT2] < 406000)	iRtnStep = ProcAA[UNIT2].RunProc_NG_MODE(pAxlMotorSet->iRunStep[UNIT2]);			//20160126JJC
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 410000 && pAxlMotorSet->iRunStep[UNIT2] < 415000)	iRtnStep = ProcPCB[UNIT2].RunProc_TiltSpecOut_Retry(pAxlMotorSet->iRunStep[UNIT2]);	//20160126JJC
		else if(pAxlMotorSet->iRunStep[UNIT2] >= 420000 && pAxlMotorSet->iRunStep[UNIT2] < 430000)	iRtnStep = ProcAA[UNIT2].AlignProc_AA_After_Align(pAxlMotorSet->iRunStep[UNIT2]);


		pAxlMotorSet->iRunStepOrg[UNIT2] = pAxlMotorSet->iRunStep[UNIT2];
		//!! Thread 다음 동작 처리 및 상태 처리.(0 이하 일 경우 Alarm 발생 상태)
		pAxlMotorSet->iRunStep[UNIT2] = abs(iRtnStep);	//Error 발생.. iRunStep에서 -1을 곱하면 재동작시 시작 번호가됨.
		if( iRtnStep < 0 )
		{
			CCPreFocusingAADlg* pFrame =(CCPreFocusingAADlg*)AfxGetApp()->m_pMainWnd;
			sMsg.Format("#AA%d@ALARM&ERR$", (sysData.m_iUnitNo*2)+UNIT2+1);
			pFrame->HidataSocket_ClientSend(UNIT2, sMsg);

			gCommUV.UV_Trigger(UNIT2 , 2 , DIO_OFF , model.iUVLightVal[UNIT2]);
			pAxlMotorSet->m_bThreadAutoFocus[UNIT2] = false;
			//일시정지에 불들어오게.
			Task[UNIT2].AutoFlag = 2;
			break;
		}

		Sleep(5);
		DoSleepEvents();
	}

	pAxlMotorSet->m_bThreadAutoFocus[UNIT2] = false;
	pAxlMotorSet->m_hThreadAutoFocus[UNIT2] = NULL;

	return TRUE;
}

//-------------------------자동 끝

void AxlMotorSet::func_AutoProcStop(int iUnit)
{//! 자동모드 정지
	CString sMsg;
	CCPreFocusingAADlg* pFrame = (CCPreFocusingAADlg*)AfxGetApp()->m_pMainWnd;

	//마지막 누른 버튼의 번호를 기억하고 sub창 열기
	theApp.g_DlgSlideBar->iUnitStatus = iUnit;
	//for( int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++)
	//{	
	//	//AxmMoveEStop(iAxis + (0 * CUR_MOTOR_NO));
	//}

#ifdef ON_LINE_SOKET
	sMsg.Format("#AA%d@ALARM&CLR$", (sysData.m_iUnitNo*2) + iUnit + 1);
	pFrame->HidataSocket_ClientSend(iUnit, sMsg);
	sMsg.Format("#AA%d@PCB&ESC$", (sysData.m_iUnitNo*2) + iUnit + 1);
	pFrame->HidataSocket_ClientSend(iUnit, sMsg);

	Sleep(50);
	sMsg.Format("#AA%d@ULD&ESC$", (sysData.m_iUnitNo*2) + iUnit + 1);
	pFrame->HidataSocket_ClientSend(iUnit, sMsg);
	sMsg.Format("#AA%d@LEN&ESC$", (sysData.m_iUnitNo*2) + iUnit + 1);
	pFrame->HidataSocket_ClientSend(iUnit, sMsg);
#endif

	if( Task[iUnit].AutoFlag != 0 )		Task[iUnit].AutoFlag = 0;

	m_hThreadHomeAll[iUnit] = false;	//전체 원점복귀 종료
	m_hThreadHome[iUnit]	= false;	//개별 원점복귀 종료	
	m_hThreadReady[iUnit]	= false;	//운전준비 종료		
	bThreadReady[iUnit]		= false;

	Motor.iRunStep[iUnit] = 10000;
	Task[iUnit].iExhaust = 0;

	for(int i = 0; i < 50; i++)
		SocketFlow.bSocketFlag[iUnit][i] = FALSE;

	ProcLENS[iUnit].OUT_UV_LAMP(UV_OFF);
	 
	vision.SetGrabMode(iUnit, LIVE);
}

bool AxlMotorSet::ManualMode_Process(int iUnit)
{//! [전체] 매뉴얼 동작 THREAD호출
	CString sMsg;
	DWORD dwThreadID = 0, dwExitCode = 0;

	CCPreFocusingAADlg* pFrame = (CCPreFocusingAADlg*)AfxGetApp()->m_pMainWnd;

	GetExitCodeThread(m_hThreadManualFocus[iUnit], &dwExitCode);
	if(dwExitCode == STILL_ACTIVE)
	{
		sMsg.Format(_T("Manual MODE 동작 PROCESS가 이미 동작 중입니다.."));
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
		//::SendMessage(hMainDlg,WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP,(LPARAM)&sMsg);
		return false;
	}

	if( (Motor.m_hThreadHomeAll[iUnit] != NULL) ||  ( Motor.m_hThreadHome[iUnit] != NULL ) )
	{
		sMsg.Format("원점복귀중에 불가능한 동작입니다. ");
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg,WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
		return false;
	}

	if( Motor.m_hThreadReady[iUnit] != NULL)
	{
		sMsg.Format(" 운전준비중에 불가능한 동작입니다. " );
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg,WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
		return false;
	}


	m_bThreadManualFocus[iUnit] = true;

	if(iUnit == UNIT1){
		m_hThreadManualFocus[iUnit] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadManualFocusUNIT1, 
			this, 0, &dwExitCode);
	}
	else
	{
		m_hThreadManualFocus[iUnit] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadManualFocusUNIT2, 
			this, 0, &dwExitCode);
	}
	return true;

}

bool AxlMotorSet::AutoMode_Process(int iUnit)
{//! [전체] AUTO 동작 THREAD호출
	CString sMsg;
	DWORD dwThreadID = 0, dwExitCode = 0;

	CCPreFocusingAADlg* pFrame = (CCPreFocusingAADlg*)AfxGetApp()->m_pMainWnd;
	GetExitCodeThread(m_hThreadAutoFocus[iUnit], &dwExitCode);
	if(dwExitCode == STILL_ACTIVE)
	{
		sMsg.Format(_T("AUTO MODE 동작 PROCESS가 이미 동작 중입니다.."));
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP);
		//::SendMessage(hMainDlg,WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP,(LPARAM)&sMsg);
		return false;
	}

	if( (Motor.m_hThreadHomeAll[iUnit] != NULL) ||  ( Motor.m_hThreadHome[iUnit] != NULL ) )
	{
		sMsg.Format("원점복귀중에 불가능한 동작입니다. ");
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg,WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
		return false;
	}

	if( Motor.m_hThreadReady[iUnit] != NULL)
	{
		sMsg.Format(" 운전준비중에 불가능한 동작입니다. " );
		g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg,WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
		return false;
	}

	//운전 준비 확인
	bool bReady = false;
	if( Task[iUnit].AutoFlag != 2 ){		//일시정지시 운전준비 확인 안하고 넘어감
		if (ProcPCB[iUnit].MoveCompleted_Pcb_Teaching(Wait_Pos, AXIS_ALL)){
			if (ProcLENS[iUnit].MoveCompleted_Lens_Teaching(Wait_Pos, AXIS_ALL)){
				if(ProcLENS[iUnit].IN_LensGrip(BACKWARD, false) && ProcLENS[iUnit].IN_Lens_Pusher(CYL_UP, false) &&
					ProcLENS[iUnit].IN_Lens_Pusher_FB(BACKWARD, false))
				{
					bReady = true;
				}
			}
		}

		if( bReady == false)
		{
			sMsg.Format("운전준비가 완료되지 않았습니다.");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			return false;
		}
	}

	//sMsg.Format("#AA%d@ALARM&CLR$", (sysData.m_iUnitNo*2) + UNIT1 + 1);
	//pFrame->HidataSocket_ClientSend(UNIT1, sMsg);

	m_bThreadAutoFocus[iUnit] = true;

	if(iUnit == UNIT1){
		m_hThreadAutoFocus[iUnit] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadAutoFocusUNIT1, 
			this, 0, &dwExitCode);
	}
	else
	{
		m_hThreadAutoFocus[iUnit] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadAutoFocusUNIT2, 
			this, 0, &dwExitCode);
	}
// 	sMsg.Format("[ THREAD ][ VCM ] AUTO_THREAD 생성 성공. [ ID : %d ]", dwThreadID);
// 	::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_MOTIONLOG+DEF_LOG_OK, (LPARAM)&sMsg);

	return true;

}

//----------------------------전체 원점
int AxlMotorSet::HomeAllProcess_UNIT1(int iUseStep)
{// [ iUnit ] 전체 원점 동작
	int iUnit = UNIT1;

	//double dFTime = 0.0, dFTime2 = 0.0;
	CString sMsg;
	int iThreadStep = 1000, iHomFlag = 0;
	bool bHomeProc, bHomeError;
	DWORD 	dwReturn;
	double dVel, dAcc;
	DWORD dwRet = 0;

	iThreadStep = iUseStep;

	switch(iThreadStep)
	{
	case 1000:  //CL Y   +리밋으로 이동
 		dVel = 10 * sysData.fMotorResol[iUnit][MotCL_Y];
 		dAcc = Motor.CalcAcc_G(iUnit,MotCL_Y);
 
 		dwReturn = AxmMoveSignalSearch(MotCL_Y  + (CUR_MOTOR_NO * iUnit), dVel, dAcc, PosEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);
 
 		if ( dwReturn != AXT_RT_SUCCESS )
 		{
 			sMsg.Format("[ 전체원점] %s (+) Limit 이동 지령 실패.", MOTOR_NAME[MotCL_Y]);
 			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
 			iThreadStep = -1000;
 		}
 		else
 		{
 			dFTime = func_TimeChecker_CurrentTime(true);
 			iThreadStep = 1500;//2000;//1500;
 		}
		break;

	case 1500:// CL Y +리밋 센서 신호 확인

		if( GetStopAxis(iUnit, MotCL_Y) &&
			GetPosiSensor(iUnit, MotCL_Y) )
		{
			iThreadStep = 2000;
		}
		else if(::func_TimeChecker_Compare(TIME_AXIS, dFTime))	
		{
			sMsg.Format("[ 전체원점] CL Y (+) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -1000;
		}
		break;

	case 2000:
		if( ProcLENS[iUnit].OUT_LensGrip(BACKWARD) )
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 2500;
		}
		else
		{
			sMsg.Format("[ 전체원점] LENS GRIP 후진 실패");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -2000;
		}
		break;

	case 2500:
		if( ProcLENS[iUnit].IN_LensGrip(BACKWARD) )
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 2600;
		}
		else if(::func_TimeChecker_Compare(TIME_AXIS, dFTime))
		{
			sMsg.Format("[ 전체원점] LENS GRIP 후진 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -1000;
		}
		break;

	case 2600:
		if(::func_TimeChecker_Compare(model.SilinderDelay[iUnit][DELAY_GRIP], dFTime))			iThreadStep = 2700;
		break;

		//실린더 추가

	case 2700:
		if(ProcLENS[iUnit].OUT_Lens_Pusher(CYL_UP))
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 2800;
		}
		else
		{
			sMsg.Format("[ 전체원점] LENS PUSHER 상승 실패");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -2700;
		}
		break;

	case 2800:
		if( ProcLENS[iUnit].IN_Lens_Pusher(CYL_UP) )
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 2900;
		}
		else if(::func_TimeChecker_Compare(TIME_AXIS, dFTime))
		{
			sMsg.Format("[ 전체원점] LENS PUSHER 상승 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -2700;
		}
		break;

	case 2900:
		if(::func_TimeChecker_Compare(500, dFTime))			iThreadStep = 3000;
		break;

	case 3000: // Lens_Z 축 (+)Limit으로 이동
		dVel = 10 * sysData.fMotorResol[iUnit][MotLENS_Z];
		dAcc = Motor.CalcAcc_G(iUnit,MotLENS_Z);

		dwReturn = AxmMoveSignalSearch(MotLENS_Z + (CUR_MOTOR_NO * iUnit), dVel, dAcc, PosEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ 전체원점] %s (+) Limit 이동 지령 실패.", MOTOR_NAME[MotLENS_Z]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -3000;
		}
		else
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 3500;			
		}
		break;

	case 3500://! Lens Z축 (+)Limit센서 신호 확인
		if( GetStopAxis(iUnit, MotLENS_Z) &&
			GetPosiSensor(iUnit, MotLENS_Z) )
		{
			iThreadStep = 3600;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dFTime))	
		{
			sMsg.Format("[ 전체원점] LENS Z축 (+)LIMIT 이동 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -3000;
		}
		break;

	case 3600:  //PCB Y   -리밋으로 이동
		dVel = 10 * sysData.fMotorResol[iUnit][MotPCB_Y];
		dAcc = Motor.CalcAcc_G(iUnit,MotPCB_Y);

		dwReturn = AxmMoveSignalSearch(MotPCB_Y  + (CUR_MOTOR_NO * iUnit), -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ 전체원점] %s (-) Limit 이동 지령 실패.", MOTOR_NAME[MotPCB_Y]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -3600;
		}
		else
		{
			dFTime2 = func_TimeChecker_CurrentTime(true);
			iThreadStep = 3700;
		}
		break;

	case 3700:// PCB Y -리밋 센서 신호 확인

		if( GetStopAxis(iUnit, MotPCB_Y) &&
			GetNegaSensor(iUnit, MotPCB_Y) )
		{
			iThreadStep = 4000;
		}
		else{
			if(func_TimeChecker_Compare(TIME_AXIS, dFTime2))	
			{
				sMsg.Format("[ 전체원점] PCB Y (-) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
				iThreadStep = -3600;
			}
		}
		break;


		//-------------------------------

	case 4000:  //LENS X   -리밋으로 이동
		dVel = 10 * sysData.fMotorResol[iUnit][MotLENS_X];
		dAcc = Motor.CalcAcc_G(iUnit,MotLENS_X);

		dwReturn = AxmMoveSignalSearch(MotLENS_X  + (CUR_MOTOR_NO * iUnit), -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ 전체원점] %s (-) Limit 이동 지령 실패.", MOTOR_NAME[MotLENS_X]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -4000;
		}
		else
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 4500;
		}
		break;

	case 4500:// LENS X -리밋 센서 신호 확인

		if( GetStopAxis(iUnit, MotLENS_X) &&
			GetNegaSensor(iUnit, MotLENS_X) )
		{
			iThreadStep = 5000;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dFTime))	
		{
			sMsg.Format("[ 전체원점] LENS X (-) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -4000;
		}

		break;

	case 5000:  //LENS Y   +리밋으로 이동
		dVel = 10 * sysData.fMotorResol[iUnit][MotLENS_Y];
		dAcc = Motor.CalcAcc_G(iUnit,MotLENS_Y);

		dwReturn = AxmMoveSignalSearch(MotLENS_Y  + (CUR_MOTOR_NO * iUnit), dVel, dAcc, PosEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ 전체원점] %s (+) Limit 이동 지령 실패.", MOTOR_NAME[MotLENS_Y]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -5000;
		}
		else
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 5500;
		}
		break;

	case 5500:  //PCB Y   -리밋으로 이동
// 		dVel = 10 * sysData.fMotorResol[iUnit][MotPCB_Y];
// 		dAcc = Motor.CalcAcc_G(iUnit,MotPCB_Y);
// 
// 		dwReturn = AxmMoveSignalSearch(MotPCB_Y  + (CUR_MOTOR_NO * iUnit), -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);
// 
// 		if ( dwReturn != AXT_RT_SUCCESS )
// 		{
// 			sMsg.Format("[ 전체원점] %s (-) Limit 이동 지령 실패.", MOTOR_NAME[MotPCB_Y]);
// 			::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
// 			iThreadStep = -5500;
// 		}
// 		else
// 		{
// 			dFTime2 = func_TimeChecker_CurrentTime(true);
			iThreadStep = 6000;
//		}
		break;

	case 6000:// LENS Y +리밋 센서 신호 확인

		if( GetStopAxis(iUnit, MotLENS_Y) &&
			GetPosiSensor(iUnit, MotLENS_Y) )
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 6500;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dFTime))	
		{
			sMsg.Format("[ 전체원점] LENS Y (+) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -5000;
		}

		break;
	case 6500:// PCB Y -리밋 센서 신호 확인

// 		if( GetStopAxis(iUnit, MotPCB_Y) &&
// 			GetNegaSensor(iUnit, MotPCB_Y) )
// 		{
			iThreadStep = 7000;
// 		}
// 		else{
// 			if(func_TimeChecker_Compare(TIME_AXIS, dFTime2))	
// 			{
// 				sMsg.Format("[ 전체원점] PCB Y (-) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
// 				::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
// 				iThreadStep = -5500;
// 			}
// 		}
		break;
//-----------------
	case 6550:  //LENS Y   -리밋으로 이동
		dVel = 10 * sysData.fMotorResol[iUnit][MotLENS_Y];
		dAcc = Motor.CalcAcc_G(iUnit,MotLENS_Y);

		dwReturn = AxmMoveSignalSearch(MotLENS_Y  + (CUR_MOTOR_NO * iUnit), -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ 전체원점] %s (-) Limit 이동 지령 실패.", MOTOR_NAME[MotLENS_Y]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -5000;
		}
		else
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 6600;
		}
		break;


	case 6600:// LENS Y -리밋 센서 신호 확인

		if( GetStopAxis(iUnit, MotLENS_Y) &&
			GetNegaSensor(iUnit, MotLENS_Y) )
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 7000;//6700;//7000;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dFTime))	
		{
			sMsg.Format("[ 전체원점] LENS Y (-) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -5000;
		}

		break;

	//case 6700:  //CL Y   +리밋으로 이동
 //		dVel = 30 * sysData.fMotorResol[iUnit][MotCL_Y];
 //		dAcc = Motor.CalcAcc_G(iUnit,MotCL_Y);
 //
 //		dwReturn = AxmMoveSignalSearch(MotCL_Y  + (CUR_MOTOR_NO * iUnit), dVel, dAcc, PosEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);
 //
 //		if ( dwReturn != AXT_RT_SUCCESS )
 //		{
 //			sMsg.Format("[ 전체원점] %s (+) Limit 이동 지령 실패.", MOTOR_NAME[MotCL_Y]);
 //			::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
 //			iThreadStep = -6700;
 //		}
 //		else
 //		{
 //			dFTime = func_TimeChecker_CurrentTime(true);
 //			iThreadStep = 6800;
 //		}
	//	break;

	//case 6800:// CL Y +리밋 센서 신호 확인

	//	if( GetStopAxis(iUnit, MotCL_Y) &&
	//		GetPosiSensor(iUnit, MotCL_Y) )
	//	{
	//		iThreadStep = 7000;
	//	}
	//	else if(::func_TimeChecker_Compare(TIME_AXIS, dFTime))	
	//	{
	//		sMsg.Format("[ 전체원점] CL Y (+) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
	//		::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
	//		iThreadStep = -6700;
	//	}
	//	break;

//-------

	case 7000:		//PCB T -리밋으로 돌리기.
		dVel = 10 * sysData.fMotorResol[iUnit][MotPCB_T];
		dAcc = Motor.CalcAcc_G(iUnit,MotPCB_T);

		dwReturn = AxmMoveSignalSearch(MotPCB_T + (CUR_MOTOR_NO * iUnit), -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ 전체원점] %s (-) Limit 이동 지령 실패.", MOTOR_NAME[MotPCB_T]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -7000;
		}
		else
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 7500;
		}

		break;

	case 7500:		//PCB T 리밋 확인.
		if( GetStopAxis(iUnit, MotPCB_T) &&
			GetNegaSensor(iUnit, MotPCB_T) )
		{
			iThreadStep = 8000;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dFTime))	
		{
			sMsg.Format("[ 전체원점] PCB T (-) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -6000;
		}
		break;

	case 8000:	//전체 원점 사전검색
		bHomeProc = true;
		for(int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++)
		{
			//if(iAxis == MotCL_Y)		continue;
			if( iHomeProcUsing[iUnit][iAxis] == 1 )
			{
				if( Start_Home_Search(iUnit, iAxis) < 0 )
				{
					bHomeProc = false;
					break;
				}
				else
				{
					iHomeProcUsing[iUnit][iAxis] = 2;
				}
			}
		}

		if( bHomeProc == false )
		{
			sMsg.Format("[ 전체 원점 ] 원점 동작 지령 실패.");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -8000;
		}
		else
		{
			iThreadStep = 9000;
			dFTime = func_TimeChecker_CurrentTime(true);
		}
		break;

	case 9000:	//전체 원점 동작 실행.
		//if(func_TimeChecker_Compare(30000, dFTime) == false)
		if(func_TimeChecker_Compare(100000, dFTime) == false)
		{
			bHomeProc = true;
			bHomeError = true;

			for( int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++)
			{
				//if(iAxis == MotCL_Y) continue;
				if( iHomeProcUsing[iUnit][iAxis] != 0 )
				{
					iHomFlag = IsCompleted_Home_Search(iUnit, iAxis);
					if( iHomFlag < 1 )	bHomeError = false;		//원점 동작 Error 정지 일 경우
					if( iHomFlag == 2 )	bHomeProc = false;		//원점 동작 진행 중일 경우.
					if( iHomFlag == 1 )	m_bOrgFlag[iUnit][iAxis] = DEF_ORIGIN_COMPLETE;	//원점 완료
				}


				if( bHomeError == false )	
				{//비정상 알람(원점 동작 정지) 
					sMsg.Format("[ 전체원점 ] 원점 동작 Error 발생 정지. 축 : %s",  MOTOR_NAME[iAxis]);
					g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
					iThreadStep = -9000;

					for( int iAxis2 = 0; iAxis2 < CUR_MOTOR_NO; iAxis2++)
					{	
						AxmMoveSStop(iAxis2 + (iUnit * CUR_MOTOR_NO));
					}

					break;
				}
			}


			if( bHomeError == true )
			{
				bool bChk_origin = true;
				for(int iChk = 0; iChk < CUR_MOTOR_NO; iChk++)
				{
					if(m_bOrgFlag[iUnit][iChk] != DEF_ORIGIN_COMPLETE)				bChk_origin = false;

				}

				if(bChk_origin == true)
				{
					StartingPoint_Status[iUnit] = true;
					sMsg.Format("[ 전체 원점 ] 원점 복귀 동작이 완료되었습니다.");
					g_PushLogQueue(sMsg, DEF_TYPE_SYSTEMLOG + GetUnitNum(iUnit));
					//::SendMessage(hMainDlg,WM_SEND_LOG, DEF_TYPE_SYSTEMLOG + GetUnitNum(iUnit), (LPARAM)&sMsg);

					iThreadStep = 9500;
				}
			}

		}
		else
		{
			sMsg.Format("[ 전체 원점 ] 원점 복귀 시간 초과.");
			g_PushLogQueue(sMsg, DEF_TYPE_SYSTEMLOG + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg,WM_SEND_LOG, DEF_TYPE_SYSTEMLOG + GetUnitNum(iUnit), (LPARAM)&sMsg);

			iThreadStep = -9000;
		}

		break;

	case 9500:	//종료
		iThreadStep = 10000;
		break;

	default:
		iThreadStep = -10000;

		break;
	}
	return iThreadStep;
}


int AxlMotorSet::HomeAllProcess_UNIT2(int iUseStep)
{// [ iUnit ] 전체 원점 동작
	int iUnit = UNIT2;

	//double dFTime = 0.0, dFTime2 = 0.0;
	CString sMsg;
	int iThreadStep = 1000, iHomFlag = 0;
	bool bHomeProc, bHomeError;
	DWORD 	dwReturn;
	double dVel, dAcc;
	DWORD dwRet = 0;

	iThreadStep = iUseStep;

	switch(iThreadStep)
	{
	case 1000:  //CL Y   +리밋으로 이동
 		dVel = 10 * sysData.fMotorResol[iUnit][MotCL_Y];
 		dAcc = Motor.CalcAcc_G(iUnit,MotCL_Y);
 
 		dwReturn = AxmMoveSignalSearch(MotCL_Y  + (CUR_MOTOR_NO * iUnit), dVel, dAcc, PosEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);
 
 		if ( dwReturn != AXT_RT_SUCCESS )
 		{
 			sMsg.Format("[ 전체원점] %s (+) Limit 이동 지령 실패.", MOTOR_NAME[MotCL_Y]);
 			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
 			iThreadStep = -1000;
 		}
 		else
 		{
 			dFTime = func_TimeChecker_CurrentTime(true);
 			iThreadStep = 1500;//2000;//1500;
 		}
		break;

	case 1500:// CL Y +리밋 센서 신호 확인

		if( GetStopAxis(iUnit, MotCL_Y) &&
			GetPosiSensor(iUnit, MotCL_Y) )
		{
			iThreadStep = 2000;
		}
		else if(::func_TimeChecker_Compare(TIME_AXIS, dFTime))	
		{
			sMsg.Format("[ 전체원점] CL Y (+) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -1000;
		}
		break;

	case 2000:
		if( ProcLENS[iUnit].OUT_LensGrip(BACKWARD) )
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 2500;
		}
		else
		{
			sMsg.Format("[ 전체원점] LENS GRIP 후진 실패");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -2000;
		}
		break;

	case 2500:
		if( ProcLENS[iUnit].IN_LensGrip(BACKWARD) )
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 2600;
		}
		else if(::func_TimeChecker_Compare(TIME_AXIS, dFTime))
		{
			sMsg.Format("[ 전체원점] LENS GRIP 후진 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -1000;
		}
		break;

	case 2600:
		if(::func_TimeChecker_Compare(model.SilinderDelay[iUnit][DELAY_GRIP], dFTime))			iThreadStep = 2700;
		break;

		//실린더 추가

	case 2700:
		if(ProcLENS[iUnit].OUT_Lens_Pusher(CYL_UP))
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 2800;
		}
		else
		{
			sMsg.Format("[ 전체원점] LENS PUSHER 상승 실패");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -2700;
		}
		break;

	case 2800:
		if( ProcLENS[iUnit].IN_Lens_Pusher(CYL_UP) )
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 2900;
		}
		else if(::func_TimeChecker_Compare(TIME_AXIS, dFTime))
		{
			sMsg.Format("[ 전체원점] LENS PUSHER 상승 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -2700;
		}
		break;

	case 2900:
		if(::func_TimeChecker_Compare(500, dFTime))			iThreadStep = 3000;
		break;

	case 3000: // Lens_Z 축 (+)Limit으로 이동
		dVel = 10 * sysData.fMotorResol[iUnit][MotLENS_Z];
		dAcc = Motor.CalcAcc_G(iUnit,MotLENS_Z);

		dwReturn = AxmMoveSignalSearch(MotLENS_Z + (CUR_MOTOR_NO * iUnit), dVel, dAcc, PosEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ 전체원점] %s (+) Limit 이동 지령 실패.", MOTOR_NAME[MotLENS_Z]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -3000;
		}
		else
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 3500;			
		}
		break;

	case 3500://! Lens Z축 (+)Limit센서 신호 확인
		if( GetStopAxis(iUnit, MotLENS_Z) &&
			GetPosiSensor(iUnit, MotLENS_Z) )
		{
			iThreadStep = 3600;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dFTime))	
		{
			sMsg.Format("[ 전체원점] LENS Z축 (+)LIMIT 이동 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -3000;
		}
		break;

	case 3600:  //PCB Y   -리밋으로 이동
		dVel = 10 * sysData.fMotorResol[iUnit][MotPCB_Y];
		dAcc = Motor.CalcAcc_G(iUnit,MotPCB_Y);

		dwReturn = AxmMoveSignalSearch(MotPCB_Y  + (CUR_MOTOR_NO * iUnit), -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ 전체원점] %s (-) Limit 이동 지령 실패.", MOTOR_NAME[MotPCB_Y]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -3600;
		}
		else
		{
			dFTime2 = func_TimeChecker_CurrentTime(true);
			iThreadStep = 3700;
		}
		break;

	case 3700:// PCB Y -리밋 센서 신호 확인

		if( GetStopAxis(iUnit, MotPCB_Y) &&
			GetNegaSensor(iUnit, MotPCB_Y) )
		{
			iThreadStep = 4000;
		}
		else{
			if(func_TimeChecker_Compare(TIME_AXIS, dFTime2))	
			{
				sMsg.Format("[ 전체원점] PCB Y (-) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
				iThreadStep = -3600;
			}
		}
		break;


		//-------------------------------

	case 4000:  //LENS X   -리밋으로 이동
		dVel = 10 * sysData.fMotorResol[iUnit][MotLENS_X];
		dAcc = Motor.CalcAcc_G(iUnit,MotLENS_X);

		dwReturn = AxmMoveSignalSearch(MotLENS_X  + (CUR_MOTOR_NO * iUnit), -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ 전체원점] %s (-) Limit 이동 지령 실패.", MOTOR_NAME[MotLENS_X]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -4000;
		}
		else
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 4500;
		}
		break;

	case 4500:// LENS X -리밋 센서 신호 확인

		if( GetStopAxis(iUnit, MotLENS_X) &&
			GetNegaSensor(iUnit, MotLENS_X) )
		{
			iThreadStep = 5000;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dFTime))	
		{
			sMsg.Format("[ 전체원점] LENS X (-) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -4000;
		}

		break;

	case 5000:  //LENS Y   +리밋으로 이동
		dVel = 10 * sysData.fMotorResol[iUnit][MotLENS_Y];
		dAcc = Motor.CalcAcc_G(iUnit,MotLENS_Y);

		dwReturn = AxmMoveSignalSearch(MotLENS_Y  + (CUR_MOTOR_NO * iUnit), dVel, dAcc, PosEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ 전체원점] %s (+) Limit 이동 지령 실패.", MOTOR_NAME[MotLENS_Y]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -5000;
		}
		else
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 5500;
		}
		break;

	case 5500:  //PCB Y   -리밋으로 이동
// 		dVel = 10 * sysData.fMotorResol[iUnit][MotPCB_Y];
// 		dAcc = Motor.CalcAcc_G(iUnit,MotPCB_Y);
// 
// 		dwReturn = AxmMoveSignalSearch(MotPCB_Y  + (CUR_MOTOR_NO * iUnit), -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);
// 
// 		if ( dwReturn != AXT_RT_SUCCESS )
// 		{
// 			sMsg.Format("[ 전체원점] %s (-) Limit 이동 지령 실패.", MOTOR_NAME[MotPCB_Y]);
// 			::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
// 			iThreadStep = -5500;
// 		}
// 		else
// 		{
// 			dFTime2 = func_TimeChecker_CurrentTime(true);
			iThreadStep = 6000;
//		}
		break;

	case 6000:// LENS Y +리밋 센서 신호 확인

		if( GetStopAxis(iUnit, MotLENS_Y) &&
			GetPosiSensor(iUnit, MotLENS_Y) )
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 6500;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dFTime))	
		{
			sMsg.Format("[ 전체원점] LENS Y (+) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -5000;
		}

		break;
	case 6500:// PCB Y -리밋 센서 신호 확인

// 		if( GetStopAxis(iUnit, MotPCB_Y) &&
// 			GetNegaSensor(iUnit, MotPCB_Y) )
// 		{
			iThreadStep = 7000;
// 		}
// 		else{
// 			if(func_TimeChecker_Compare(TIME_AXIS, dFTime2))	
// 			{
// 				sMsg.Format("[ 전체원점] PCB Y (-) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
// 				::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
// 				iThreadStep = -5500;
// 			}
// 		}
		break;
//-----------------
	case 6550:  //LENS Y   -리밋으로 이동
		dVel = 10 * sysData.fMotorResol[iUnit][MotLENS_Y];
		dAcc = Motor.CalcAcc_G(iUnit,MotLENS_Y);

		dwReturn = AxmMoveSignalSearch(MotLENS_Y  + (CUR_MOTOR_NO * iUnit), -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ 전체원점] %s (-) Limit 이동 지령 실패.", MOTOR_NAME[MotLENS_Y]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -5000;
		}
		else
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 6600;
		}
		break;


	case 6600:// LENS Y -리밋 센서 신호 확인

		if( GetStopAxis(iUnit, MotLENS_Y) &&
			GetNegaSensor(iUnit, MotLENS_Y) )
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 7000;//6700;//7000;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dFTime))	
		{
			sMsg.Format("[ 전체원점] LENS Y (-) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -5000;
		}

		break;

	//case 6700:  //CL Y   +리밋으로 이동
 //		dVel = 30 * sysData.fMotorResol[iUnit][MotCL_Y];
 //		dAcc = Motor.CalcAcc_G(iUnit,MotCL_Y);
 //
 //		dwReturn = AxmMoveSignalSearch(MotCL_Y  + (CUR_MOTOR_NO * iUnit), dVel, dAcc, PosEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);
 //
 //		if ( dwReturn != AXT_RT_SUCCESS )
 //		{
 //			sMsg.Format("[ 전체원점] %s (+) Limit 이동 지령 실패.", MOTOR_NAME[MotCL_Y]);
 //			::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
 //			iThreadStep = -6700;
 //		}
 //		else
 //		{
 //			dFTime = func_TimeChecker_CurrentTime(true);
 //			iThreadStep = 6800;
 //		}
	//	break;

	//case 6800:// CL Y +리밋 센서 신호 확인

	//	if( GetStopAxis(iUnit, MotCL_Y) &&
	//		GetPosiSensor(iUnit, MotCL_Y) )
	//	{
	//		iThreadStep = 7000;
	//	}
	//	else if(::func_TimeChecker_Compare(TIME_AXIS, dFTime))	
	//	{
	//		sMsg.Format("[ 전체원점] CL Y (+) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
	//		::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
	//		iThreadStep = -6700;
	//	}
	//	break;

//-------

	case 7000:		//PCB T -리밋으로 돌리기.
		dVel = 10 * sysData.fMotorResol[iUnit][MotPCB_T];
		dAcc = Motor.CalcAcc_G(iUnit,MotPCB_T);

		dwReturn = AxmMoveSignalSearch(MotPCB_T + (CUR_MOTOR_NO * iUnit), -dVel, dAcc, NegEndLimit, SIGNAL_UP_EDGE, SLOWDOWN_STOP);

		if ( dwReturn != AXT_RT_SUCCESS )
		{
			sMsg.Format("[ 전체원점] %s (-) Limit 이동 지령 실패.", MOTOR_NAME[MotPCB_T]);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -7000;
		}
		else
		{
			dFTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 7500;
		}

		break;

	case 7500:		//PCB T 리밋 확인.
		if( GetStopAxis(iUnit, MotPCB_T) &&
			GetNegaSensor(iUnit, MotPCB_T) )
		{
			iThreadStep = 8000;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dFTime))	
		{
			sMsg.Format("[ 전체원점] PCB T (-) LIMIT 센서 신호 확인 시간 초과 [ TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -6000;
		}
		break;

	case 8000:	//전체 원점 사전검색
		bHomeProc = true;
		for(int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++)
		{
			//if(iAxis == MotCL_Y)		continue;
			if( iHomeProcUsing[iUnit][iAxis] == 1 )
			{
				if( Start_Home_Search(iUnit, iAxis) < 0 )
				{
					bHomeProc = false;
					break;
				}
				else
				{
					iHomeProcUsing[iUnit][iAxis] = 2;
				}
			}
		}

		if( bHomeProc == false )
		{
			sMsg.Format("[ 전체 원점 ] 원점 동작 지령 실패.");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -8000;
		}
		else
		{
			iThreadStep = 9000;
			dFTime = func_TimeChecker_CurrentTime(true);
		}
		break;

	case 9000:	//전체 원점 동작 실행.
		//if(func_TimeChecker_Compare(30000, dFTime) == false)
		if(func_TimeChecker_Compare(100000, dFTime) == false)
		{
			bHomeProc = true;
			bHomeError = true;

			for( int iAxis = 0; iAxis < CUR_MOTOR_NO; iAxis++)
			{
				//if(iAxis == MotCL_Y) continue;
				if( iHomeProcUsing[iUnit][iAxis] != 0 )
				{
					iHomFlag = IsCompleted_Home_Search(iUnit, iAxis);
					if( iHomFlag < 1 )	bHomeError = false;		//원점 동작 Error 정지 일 경우
					if( iHomFlag == 2 )	bHomeProc = false;		//원점 동작 진행 중일 경우.
					if( iHomFlag == 1 )	m_bOrgFlag[iUnit][iAxis] = DEF_ORIGIN_COMPLETE;	//원점 완료
				}


				if( bHomeError == false )	
				{//비정상 알람(원점 동작 정지) 
					sMsg.Format("[ 전체원점 ] 원점 동작 Error 발생 정지. 축 : %s",  MOTOR_NAME[iAxis]);
					g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
					iThreadStep = -9000;

					for( int iAxis2 = 0; iAxis2 < CUR_MOTOR_NO; iAxis2++)
					{	
						AxmMoveSStop(iAxis2 + (iUnit * CUR_MOTOR_NO));
					}

					break;
				}
			}


			if( bHomeError == true )
			{
				bool bChk_origin = true;
				for(int iChk = 0; iChk < CUR_MOTOR_NO; iChk++)
				{
					if(m_bOrgFlag[iUnit][iChk] != DEF_ORIGIN_COMPLETE)				bChk_origin = false;

				}

				if(bChk_origin == true)
				{
					StartingPoint_Status[iUnit] = true;
					sMsg.Format("[ 전체 원점 ] 원점 복귀 동작이 완료되었습니다.");
					g_PushLogQueue(sMsg, DEF_TYPE_SYSTEMLOG + GetUnitNum(iUnit));
					//::SendMessage(hMainDlg,WM_SEND_LOG, DEF_TYPE_SYSTEMLOG + GetUnitNum(iUnit), (LPARAM)&sMsg);

					iThreadStep = 9500;
				}
			}

		}
		else
		{
			sMsg.Format("[ 전체 원점 ] 원점 복귀 시간 초과.");
			g_PushLogQueue(sMsg, DEF_TYPE_SYSTEMLOG + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg,WM_SEND_LOG, DEF_TYPE_SYSTEMLOG + GetUnitNum(iUnit), (LPARAM)&sMsg);

			iThreadStep = -9000;
		}

		break;

	case 9500:	//종료
		iThreadStep = 10000;
		break;

	default:
		iThreadStep = -10000;

		break;
	}
	return iThreadStep;

}

//----------------운 전 준 비
int AxlMotorSet::ReadyAllProcess_UNIT1(int iUseStep)
{
	int iUnit = UNIT1;
	CString sMsg;
	int iThreadStep = 0, iHomFlag = 0;
	/////////////////////////////////////////////////////////////		20160629
	CCPreFocusingAADlg* pFrame = (CCPreFocusingAADlg*)AfxGetApp()->m_pMainWnd;
	//////////////////////////////////////////////////////////
	DWORD dwRet = 0;
	
	iThreadStep = iUseStep;
	switch(iThreadStep)
	{//!! 운전준비
	case 10000:
	//	gMiu.PRIGrabber_Open(UNIT1);			//20160705  JJC 운전준비 잡으면 플레임 그래버 연결
		dTime = func_TimeChecker_CurrentTime(true);
		iSocketCntChk[iUnit] = 0;
		iThreadStep = 10001;
		break;
	/////////////////////////////////////////////////////////간섭체크/////////////////////////////////////
	case 10001://case 12000:	//20160629 JJC
		if(SocketFlow.bSocketFlag[iUnit][LEN_ITF_ACK] == TRUE)
		{
			SocketFlow.bSocketFlag[iUnit][LEN_ITF_ACK] = FALSE;
			bITF_CHK[iUnit] = false;
			iThreadStep = 10050;
			break;
		}
		else
		{
			if(bITF_CHK[iUnit] == false)
			{
				bITF_CHK[iUnit] = true;
				sMsg.Format("#AA%d@LEN_ITF&CHK$", (sysData.m_iUnitNo*2)+iUnit+1);
				pFrame->HidataSocket_ClientSend(iUnit, sMsg);

				sMsg.Format("[SOCKET_LOADING] LENS 간섭 체크 요청. [ Step : %d ]", iThreadStep);
				g_PushLogQueue(sMsg, DEF_TYPE_MOTIONLOG + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_MOTIONLOG + GetUnitNum(iUnit), (LPARAM)&sMsg);

				dTime = func_TimeChecker_CurrentTime(true);
			}
			else if( func_TimeChecker_Compare(1000, dTime) )
			{
				iSocketCntChk[iUnit]++;
				bITF_CHK[iUnit] = false;

				if( iSocketCntChk[iUnit] > 10 )
				{
					sMsg.Format("운전준비 전 MAIN 간섭 확인 응답 시간 초과..\n통신 상태를 확인 하세요.");
					g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT2));
					//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT2), (LPARAM)&sMsg);	
					iThreadStep = -10000;
				}
			}
			break;
		}
		break;
		/////////////////////////////////////////////////////////간섭체크/////////////////////////////////////

		/////////////////////////////////////////////////////////UV 연결체크//////////////////////////////////
	case 10050:
		if(sysData.m_iPassUV[UNIT1] == 1)
		{
			iThreadStep = 10100;
				break;
		}
		#ifdef USE_RS232_UV		
			gCommUV.UV_Trigger(UNIT1 , 2 , DIO_OFF , model.iUVLightVal[UNIT1]);		//한번 종료 시키고 20160314 JJC
			
			
			//if(gCommUV.iRecvFlag[UNIT1] == UV_ACK)
			if(UV_Connect[UNIT1] == false)
			{
				sMsg.Format("운전준비 전 UV 컨트롤러 전원상태를 확인해주세요.");
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT1));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT1), (LPARAM)&sMsg);	
				iThreadStep = -10000;
				break;
			}
			else
			{
				iThreadStep = 10100;
				break;
			}
		#else			//요건 RS232 통신 UV 안쓸 때
			iThreadStep = 10100;
			break;
		#endif


		/////////////////////////////////////////////////////////UV 연결체크//////////////////////////////////
	case 10100:
		if( ProcLENS[iUnit].IN_LensGrip(BACKWARD))
		{
			dTime = func_TimeChecker_CurrentTime(true);	
			iThreadStep = 13100;
		}
		else
		{
			if( ProcLENS[iUnit].OUT_LensGrip(BACKWARD))
			{
				dTime = func_TimeChecker_CurrentTime(true);	
				iThreadStep = 13000;
			}
			else
			{
				sMsg.Format("[ 운전준비 ] LENS GRIP 후진 명령 실패");
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
				iThreadStep = -12000;
			}
		}
		break;

	case 13000:
		if( ProcLENS[iUnit].IN_LensGrip(BACKWARD))
		{
			dTime = func_TimeChecker_CurrentTime(true);	
			iThreadStep = 13100;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dTime))
		{
			sMsg.Format("[ 운전준비 ]LENS GRIP 후진 시간 초과 [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -12000;
		}
		break;

	case 13100:
		if(::func_TimeChecker_Compare(model.SilinderDelay[iUnit][DELAY_GRIP], dTime))
		{
			iThreadStep = 13500;
		}
		break;

	case 13500://! Pusher 상승 명령
		if(ProcLENS[iUnit].OUT_Lens_Pusher(CYL_UP))
		{
			dTime = func_TimeChecker_CurrentTime(true);	
			iThreadStep = 13700;
		}
		else
		{
			sMsg.Format("[ 운전준비 ] LENS PUSHER 상승 실패 ");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -13500;
		}
		break;

	case 13700:
		if(ProcLENS[iUnit].IN_Lens_Pusher(CYL_UP))
		{
			dTime = func_TimeChecker_CurrentTime(true);	
			iThreadStep = 13800;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dTime))
		{
			sMsg.Format("[ 운전준비 ] LENS PUSHER 상승 시간 초과 [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -13500;
		}
		break;

	case 13800:
		if(func_TimeChecker_Compare(1500, dTime))
		{
			iThreadStep = 14000;
		}
		break;

	case 14000://! Lens-Z축 대기위치 이동
		if(ProcLENS[iUnit].MotionMove_Lens_Teaching(Wait_Pos, AXIS_Z))	//! Z축 대기위치 이동 명령
		{
			dTime = func_TimeChecker_CurrentTime(true);	
			iThreadStep = 15000;
		}
		else
		{
			sMsg.Format("[ 운전준비 ] LENS_Z축 대기위치 이동 명령 실패");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -14000;
			break;
		}
		break;

	case 15000:
		if( ProcLENS[iUnit].MoveCompleted_Lens_Teaching(Wait_Pos, AXIS_Z) )	
		{
			iThreadStep = 16000;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dTime))
		{
			sMsg.Format("[ 운전준비 ] Z축 대기위치 이동 시간 초과  [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -14000;
		}
		break;


	case 16000: //! LENS Z축을 뺀 전부 대기위치 이동.. X,Y,Tx,Ty
		if(ProcLENS[iUnit].MotionMove_Lens_Teaching(Wait_Pos, AXIS_XYT))  
		{
			dTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 16500;
		}
		else
		{
			sMsg.Format("[ 운전 준비 ] LENS부 대기위치 이동 실패. [STEP:%d].", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -16000;	
		}
		break;

	case 16500:
		if(ProcLENS[iUnit].MoveCompleted_Lens_Teaching(Wait_Pos, AXIS_Z))
			iThreadStep = 17000;
		break;

	case 17000:	//! PCB X, Y, T 인터락 위치 이동
		////////////////////////////////////////////////////////////////////////////////////////20160717 JJC		움직이기전 센서확인

		if(!ProcLENS[iUnit].IN_Lens_Centering(FORWARD) && !ProcLENS[iUnit].IN_Lens_Centering(BACKWARD))
		{
			sMsg.Format("Centering 센서 신호 이상! \n Centering 센서 신호를 확인해주세요.  [ STEP : %d ]", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -17000;
			break;
		}
		else if(!ProcLENS[iUnit].IN_Lens_Pusher_FB(FORWARD) && !ProcLENS[iUnit].IN_Lens_Pusher_FB(BACKWARD))
		{
			sMsg.Format("Pusher 전후진 센서 신호 이상! \n Pusher 전후진 센서 신호를 확인해주세요.  [ STEP : %d ]", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -17000;
			break;
		}
		else if(!ProcLENS[iUnit].IN_Lens_Pusher(CYL_UP) && !ProcLENS[iUnit].IN_Lens_Pusher(CYL_DOWN))
		{
			sMsg.Format("Pusher 상승, 하강 센서 신호 이상! \n Pusher 상승, 하강 센서 신호를 확인해주세요.  [ STEP : %d ]", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -17000;
			break;
		}
		else if(!ProcLENS[iUnit].IN_LensGrip(FORWARD) && !ProcLENS[iUnit].IN_LensGrip(BACKWARD))
		{
			sMsg.Format("Grip 센서 신호 이상! \n Grip 센서 신호를 확인해주세요.  [ STEP : %d ]", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -17000;
			break;
		}
		//////////////////////////////////////////////////////////////
		if( ProcPCB[iUnit].MotionMove_Pcb_Teaching(Interlock_Pos, AXIS_ALL) )
		{
			dSTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 17100;
		}
		else
		{
			sMsg.Format("[ 운전 준비 ] PCB부 인터락 위치 이동 실패. [STEP:%d].", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -17000;	
		}
		break;
	
	case 17100:
		if( ProcPCB[iUnit].MoveCompleted_Pcb_Teaching(Interlock_Pos, AXIS_ALL) )
		{
			iThreadStep = 18000;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dTime))
		{
			sMsg.Format("[ 운전준비 ] PCB부 인터락 위치 이동 시간 초과  [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -17000;
		}
		break;
	

	case 18000:
		bReadyPusher[iUnit] = true;
		if(ProcLENS[iUnit].IN_Lens_Pusher_FB(BACKWARD) && ProcLENS[iUnit].IN_Lens_Pusher(CYL_UP))
		{
			iThreadStep = 23000;
		}
		else
		{
			if(ProcLENS[iUnit].OUT_Lens_Pusher(CYL_UP))
			{
				iThreadStep = 19000;
				dTime = func_TimeChecker_CurrentTime(true);
			}
			else
			{
				sMsg.Format("[ 운전 준비 ] LENS PUSHER 상승 실패. [STEP:%d].", iThreadStep);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
				iThreadStep = -18000;	
			}
		}
		break;

	case 19000:
		if(ProcLENS[iUnit].IN_Lens_Pusher(CYL_UP))		//상승 확인
		{
			iThreadStep = 20000;
		}
		else if(::func_TimeChecker_Compare(TIME_AXIS, dTime))
		{
			sMsg.Format("[ 운전준비 ] LENS PUSHER 상승 시간 초과  [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -18000;
		}
		break;

	case 20000:
		if(bReadyPusher[iUnit])
		{	
			if(ProcLENS[iUnit].OUT_Lens_Pusher_FB(BACKWARD))
			{
				dTime = func_TimeChecker_CurrentTime(true);
				iThreadStep = 21000;
			}
			else
			{
				sMsg.Format("[ 운전 준비 ] LENS PUSHER 후진 실패. [STEP:%d].", iThreadStep);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
				iThreadStep = -20000;	
			}
		}	
		break;

	case 21000://! Pusher 후진 확인
		if(ProcLENS[iUnit].IN_Lens_Pusher_FB(BACKWARD))	
		{
			iThreadStep = 23000;
		}
		else if(::func_TimeChecker_Compare(TIME_AXIS, dTime))
		{
			sMsg.Format("[ 운전준비 ] LENS PUSHER 전진 시간 초과  [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -20000;
		}
		break;

	case 23000://! PCB부 대기 위치 이동
		////////////////////////////////////////////////////////////////////////////////////////20160717 JJC		움직이기전 센서확인

		if(!ProcLENS[iUnit].IN_Lens_Centering(FORWARD) && !ProcLENS[iUnit].IN_Lens_Centering(BACKWARD))
		{
			sMsg.Format("Centering 센서 신호 이상! \n Centering 센서 신호를 확인해주세요.  [ STEP : %d ]", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -23000;
			break;
		}
		else if(!ProcLENS[iUnit].IN_Lens_Pusher_FB(FORWARD) && !ProcLENS[iUnit].IN_Lens_Pusher_FB(BACKWARD))
		{
			sMsg.Format("Pusher 전후진 센서 신호 이상! \n Pusher 전후진 센서 신호를 확인해주세요.  [ STEP : %d ]", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -23000;
			break;
		}
		else if(!ProcLENS[iUnit].IN_Lens_Pusher(CYL_UP) && !ProcLENS[iUnit].IN_Lens_Pusher(CYL_DOWN))
		{
			sMsg.Format("Pusher 상승, 하강 센서 신호 이상! \n Pusher 상승, 하강 센서 신호를 확인해주세요.  [ STEP : %d ]", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -23000;
			break;
		}
		else if(!ProcLENS[iUnit].IN_LensGrip(FORWARD) && !ProcLENS[iUnit].IN_LensGrip(BACKWARD))
		{
			sMsg.Format("Grip 센서 신호 이상! \n Grip 센서 신호를 확인해주세요.  [ STEP : %d ]", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -23000;
			break;
		}

		//////////////////////////////////////////////////////////////
		if( ProcPCB[iUnit].MotionMove_Pcb_Teaching(Wait_Pos, AXIS_ALL) )
		{
			dSTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 24000;
		}
		else
		{
			sMsg.Format("[ 운전 준비 ] PCB부 대기 위치 이동 실패. [STEP:%d].", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -23000;	
		}
		break;

	case 24000:
		if(ProcPCB[iUnit].MoveCompleted_Pcb_Teaching(Wait_Pos, AXIS_ALL)
			&& ProcLENS[iUnit].MoveCompleted_Lens_Teaching(Wait_Pos, AXIS_ALL))
		{
			/*
			sMsg.Format("[ 운전 준비 ] 운전 준비 완료.");
			g_PushLogQueue(sMsg, DEF_TYPE_MOTIONLOG  + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_MOTIONLOG  + GetUnitNum(iUnit), (LPARAM)&sMsg);
			Task[iUnit].bRunningReady = true;
			iThreadStep = 99999;
			*/
			iThreadStep = 24500;
		}
		else if(!ProcPCB[iUnit].MoveCompleted_Pcb_Teaching(Wait_Pos, AXIS_ALL))
		{
			if(func_TimeChecker_Compare(TIME_AXIS, dSTime))
			{
			sMsg.Format("[ 운전준비 ] PCB 대기위치 이동 시간 초과  [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -17000;
			}

		}
		else if(!ProcLENS[iUnit].MoveCompleted_Lens_Teaching(Wait_Pos, AXIS_ALL))
		{
			if(func_TimeChecker_Compare(TIME_AXIS, dTime))
			{
			sMsg.Format("[ 운전준비 ] LENS 대기위치 이동 시간 초과  [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -16000;
			}
		}
		
		break;

	case 24500:	//CL Y축 후진
 		if( ProcCL[iUnit].MotionMove_CL_Teaching(Wait_Pos))
 		{
			dTime = func_TimeChecker_CurrentTime(true);		
			iThreadStep = 24600;
 		}
 		else
 		{
 			sMsg.Format("[ 운전준비 ] CL_Y축 대기위치 이동 명령 실패");
 			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
 			iThreadStep = -24500;
 		}
		break;

	case 24600:
		if( ProcCL[iUnit].MoveCompleted_CL_Teaching(Wait_Pos))
		{
			sMsg.Format("[ 운전 준비 ] 운전 준비 완료.");
			g_PushLogQueue(sMsg, DEF_TYPE_MOTIONLOG  + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_MOTIONLOG  + GetUnitNum(iUnit), (LPARAM)&sMsg);
			Task[iUnit].bRunningReady = true;
			iThreadStep = 99999;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dTime))
		{
			sMsg.Format("[ 운전준비 ] CL_Y축 대기위치 이동 시간 초과 [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -24500;
		}
		break;

	default:
		iThreadStep = -10000;
		break;
	}
	
	return iThreadStep;
}

int AxlMotorSet::ReadyAllProcess_UNIT2(int iUseStep)
{
	int iUnit = UNIT2;
	CCPreFocusingAADlg* pFrame = (CCPreFocusingAADlg*)AfxGetApp()->m_pMainWnd;
	CString sMsg;
	int iThreadStep = 0, iHomFlag = 0;
	DWORD dwRet = 0;

	iThreadStep = iUseStep;
	switch(iThreadStep)
	{//!! 운전준비
	case 10000:
	//	gMiu.PRIGrabber_Open(UNIT2);			//20160705  JJC 운전준비 잡으면 플레임 그래버 연결
		dTime = func_TimeChecker_CurrentTime(true);
		iSocketCntChk[iUnit]	= 0;
		iThreadStep				= 10001;
		break;

	case 10001://case 12000:	//20160629 JJC
		if(SocketFlow.bSocketFlag[iUnit][LEN_ITF_ACK] == TRUE)
		{
			SocketFlow.bSocketFlag[iUnit][LEN_ITF_ACK] = FALSE;
			bITF_CHK[iUnit] = false;
			iThreadStep = 10050;
			break;
		}
		else
		{
			if(bITF_CHK[iUnit] == false)
			{
				bITF_CHK[iUnit] = true;
				sMsg.Format("#AA%d@LEN_ITF&CHK$", (sysData.m_iUnitNo*2)+iUnit+1);
				pFrame->HidataSocket_ClientSend(iUnit, sMsg);

				sMsg.Format("[SOCKET_LOADING] LENS 간섭 체크 요청. [ Step : %d ]", iThreadStep);
				g_PushLogQueue(sMsg, DEF_TYPE_MOTIONLOG + GetUnitNum(iUnit));
			//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_MOTIONLOG + GetUnitNum(iUnit), (LPARAM)&sMsg);

				dTime = func_TimeChecker_CurrentTime(true);
			}
			else if( func_TimeChecker_Compare(1000, dTime) )
			{
				iSocketCntChk[iUnit]++;
				bITF_CHK[iUnit] = false;

				if( iSocketCntChk[iUnit] > 10 )
				{
					sMsg.Format("운전준비 전 MAIN 간섭 확인 응답 시간 초과..\n통신 상태를 확인 하세요.");
					g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT2));
					//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT2), (LPARAM)&sMsg);	
					iThreadStep = -10000;
				}
			}
			break;
		}
		break;

		/////////////////////////////////////////////////////////UV 연결체크//////////////////////////////////
	case 10050:
		if(sysData.m_iPassUV[UNIT2] == 1)
		{
			iThreadStep = 10100;
				break;
		}
		#ifdef USE_RS232_UV		
			gCommUV.UV_Trigger(UNIT2 , 2 , DIO_OFF , model.iUVLightVal[UNIT2]);		//한번 종료 시키고 20160314 JJC
			
			//
			/*if(gCommUV.iRecvFlag[UNIT2] == UV_ACK)*/
			if(UV_Connect[UNIT2] == false)	
			{
				sMsg.Format("운전준비 전 UV 컨트롤러 전원상태를 확인해주세요.");
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT2));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG + DEF_LOG_POPUP + GetUnitNum(UNIT2), (LPARAM)&sMsg);	
				iThreadStep = -10000;
				break;
			}
			else
			{
				iThreadStep = 10100;
				break;
			}
		#else			//요건 RS232 통신 UV 안쓸 때
			iThreadStep = 10100;
			break;
		#endif


		/////////////////////////////////////////////////////////UV 연결체크//////////////////////////////////

	case 10100://case 12000:
		if( ProcLENS[iUnit].IN_LensGrip(BACKWARD))
		{
			iThreadStep = 13100;
			dTime = func_TimeChecker_CurrentTime(true);	
		}
		else
		{
			if( ProcLENS[iUnit].OUT_LensGrip(BACKWARD))
			{
				iThreadStep = 13000;
				dTime = func_TimeChecker_CurrentTime(true);	
			}
			else
			{
				sMsg.Format("[ 운전준비 ] LENS GRIP 후진 명령 실패");
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
				iThreadStep = -12000;
			}
		}
		break;

	case 13000:
		if( ProcLENS[iUnit].IN_LensGrip(BACKWARD))
		{
			dTime = func_TimeChecker_CurrentTime(true);	
			iThreadStep = 13100;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dTime))
		{
			sMsg.Format("[ 운전준비 ]LENS GRIP 후진 시간 초과 [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -12000;
		}
		break;

	case 13100:
		if(::func_TimeChecker_Compare(model.SilinderDelay[iUnit][DELAY_GRIP], dTime))
		{
			iThreadStep = 13500;
		}
		break;

	case 13500:
		if(ProcLENS[iUnit].OUT_Lens_Pusher(CYL_UP))
		{
			dTime = func_TimeChecker_CurrentTime(true);	
			iThreadStep = 13700;
		}
		else
		{
			sMsg.Format("[ 운전준비 ] LENS PUSHER 상승 실패 ");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -13500;
		}
		break;

	case 13700:
		if(ProcLENS[iUnit].IN_Lens_Pusher(CYL_UP))
		{
			dTime = func_TimeChecker_CurrentTime(true);	
			iThreadStep = 13800;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dTime))
		{
			sMsg.Format("[ 운전준비 ] LENS PUSHER 상승 시간 초과 [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -13500;
		}
		break;

	case 13800:
		if(func_TimeChecker_Compare(1500, dTime))
		{
			iThreadStep = 14000;
		}
		break;

	case 14000://! Lens-Z축 대기위치 이동
		if(ProcLENS[iUnit].MotionMove_Lens_Teaching(Wait_Pos, AXIS_Z))	//! Z축 대기위치 이동 명령
		{
			dTime = func_TimeChecker_CurrentTime(true);	
			iThreadStep = 15000;
		}
		else
		{
			sMsg.Format("[ 운전준비 ] LENS_Z축 대기위치 이동 명령 실패");
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -14000;
			break;
		}
		break;

	case 15000:
		if(ProcLENS[iUnit].MoveCompleted_Lens_Teaching(Wait_Pos, AXIS_Z))	//! Z축 대기위치 이동 확인
		{
			iThreadStep = 16000;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dTime))
		{
			sMsg.Format("[ 운전준비 ] Z축 대기위치 이동 시간 초과  [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -14000;
		}
		break;


	case 16000: //! LENS Z축을 뺀 전부 대기위치 이동.. X,Y,Tx,Ty 
		if(ProcLENS[iUnit].MotionMove_Lens_Teaching(Wait_Pos, AXIS_XYT))  
		{
			dTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 16500;
		}
		else
		{
			sMsg.Format("[ 운전 준비 ] LENS부 대기위치 이동 실패. [STEP:%d].", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -16000;	
		}
		break;

	case 16500:
		if(ProcLENS[iUnit].MoveCompleted_Lens_Teaching(Wait_Pos, AXIS_Z))
			iThreadStep = 17000;
		break;


	case 17000:		//! PCB X, Y, T 대기위치 이동
		////////////////////////////////////////////////////////////////////////////////////////20160717 JJC		움직이기전 센서확인

		if(!ProcLENS[iUnit].IN_Lens_Centering(FORWARD) && !ProcLENS[iUnit].IN_Lens_Centering(BACKWARD))
		{
			sMsg.Format("Centering 센서 신호 이상! \n Centering 센서 신호를 확인해주세요.  [ STEP : %d ]", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -17000;
			break;
		}
		else if(!ProcLENS[iUnit].IN_Lens_Pusher_FB(FORWARD) && !ProcLENS[iUnit].IN_Lens_Pusher_FB(BACKWARD))
		{
			sMsg.Format("Pusher 전후진 센서 신호 이상! \n Pusher 전후진 센서 신호를 확인해주세요.  [ STEP : %d ]", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -17000;
			break;
		}
		else if(!ProcLENS[iUnit].IN_Lens_Pusher(CYL_UP) && !ProcLENS[iUnit].IN_Lens_Pusher(CYL_DOWN))
		{
			sMsg.Format("Pusher 상승, 하강 센서 신호 이상! \n Pusher 상승, 하강 센서 신호를 확인해주세요.  [ STEP : %d ]", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -17000;
			break;
		}
		else if(!ProcLENS[iUnit].IN_LensGrip(FORWARD) && !ProcLENS[iUnit].IN_LensGrip(BACKWARD))
		{
			sMsg.Format("Grip 센서 신호 이상! \n Grip 센서 신호를 확인해주세요.  [ STEP : %d ]", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -17000;
			break;
		}

		//////////////////////////////////////////////////////////////
		if(ProcPCB[iUnit].MotionMove_Pcb_Teaching(Interlock_Pos, AXIS_ALL))
		{
			dSTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 17100;
		}
		else
		{
			sMsg.Format("[ 운전 준비 ] PCB부 인터락 위치 이동 실패. [STEP:%d].", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -17000;	
		}
		break;

	case 17100:
		if( ProcPCB[iUnit].MoveCompleted_Pcb_Teaching(Interlock_Pos, AXIS_ALL) )
		{
			iThreadStep = 18000;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dTime))
		{
			sMsg.Format("[ 운전준비 ] PCB부 인터락 위치 이동 시간 초과  [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -17000;
		}
		break;

	case 18000:
		bReadyPusher[iUnit] = true;
		if(ProcLENS[iUnit].IN_Lens_Pusher_FB(BACKWARD) && ProcLENS[iUnit].IN_Lens_Pusher(CYL_UP))
		{
			iThreadStep = 23000;
		}
		else
		{
			if(ProcLENS[iUnit].OUT_Lens_Pusher(CYL_UP))
			{
				dTime = func_TimeChecker_CurrentTime(true);
				iThreadStep = 19000;
			}
			else
			{
				sMsg.Format("[ 운전 준비 ] LENS PUSHER 상승 실패. [STEP:%d].", iThreadStep);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
				iThreadStep = -18000;	
			}
		}
		break;

	case 19000:
		if(ProcLENS[iUnit].IN_Lens_Pusher(CYL_UP))		//상승 확인
		{
			iThreadStep = 20000;
		}
		else if(::func_TimeChecker_Compare(TIME_AXIS, dTime))
		{
			sMsg.Format("[ 운전준비 ] LENS PUSHER 상승 시간 초과  [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -18000;
		}
		break;

	case 20000:
		if(bReadyPusher[iUnit])	
		{	
			if(ProcLENS[iUnit].OUT_Lens_Pusher_FB(BACKWARD))	// 후진 이동 명령 (작업자 쪽)
			{
				iThreadStep = 21000;
				dTime = func_TimeChecker_CurrentTime(true);
			}
			else
			{
				sMsg.Format("[ 운전 준비 ] LENS PUSHER 후진 실패. [STEP:%d].", iThreadStep);
				g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
				iThreadStep = -20000;	
			}
		}
		break;

	case 21000://! Pusher 후진 확인
		if(ProcLENS[iUnit].IN_Lens_Pusher_FB(BACKWARD))	//후진 확인
		{
			iThreadStep = 23000;
		}
		else if(::func_TimeChecker_Compare(TIME_AXIS, dTime))
		{
			sMsg.Format("[ 운전준비 ] LENS PUSHER 전진 시간 초과  [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -20000;
		}
		break;

	case 23000://! PCB부 대기 위치 이동
		////////////////////////////////////////////////////////////////////////////////////////20160717 JJC		움직이기전 센서확인

		if(!ProcLENS[iUnit].IN_Lens_Centering(FORWARD) && !ProcLENS[iUnit].IN_Lens_Centering(BACKWARD))
		{
			sMsg.Format("Centering 센서 신호 이상! \n Centering 센서 신호를 확인해주세요.  [ STEP : %d ]", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -23000;
			break;
		}
		else if(!ProcLENS[iUnit].IN_Lens_Pusher_FB(FORWARD) && !ProcLENS[iUnit].IN_Lens_Pusher_FB(BACKWARD))
		{
			sMsg.Format("Pusher 전후진 센서 신호 이상! \n Pusher 전후진 센서 신호를 확인해주세요.  [ STEP : %d ]", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -23000;
			break;
		}
		else if(!ProcLENS[iUnit].IN_Lens_Pusher(CYL_UP) && !ProcLENS[iUnit].IN_Lens_Pusher(CYL_DOWN))
		{
			sMsg.Format("Pusher 상승, 하강 센서 신호 이상! \n Pusher 상승, 하강 센서 신호를 확인해주세요.  [ STEP : %d ]", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -23000;
			break;
		}
		else if(!ProcLENS[iUnit].IN_LensGrip(FORWARD) && !ProcLENS[iUnit].IN_LensGrip(BACKWARD))
		{
			sMsg.Format("Grip 센서 신호 이상! \n Grip 센서 신호를 확인해주세요.  [ STEP : %d ]", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -23000;
			break;
		}

		//////////////////////////////////////////////////////////////
		if( ProcPCB[iUnit].MotionMove_Pcb_Teaching(Wait_Pos, AXIS_ALL) )
		{
			dSTime = func_TimeChecker_CurrentTime(true);
			iThreadStep = 24000;
		}
		else
		{
			sMsg.Format("[ 운전 준비 ] PCB부 대기 위치 이동 실패. [STEP:%d].", iThreadStep);
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -23000;	
		}
		break;

	case 24000:
		if(ProcPCB[iUnit].MoveCompleted_Pcb_Teaching(Wait_Pos, AXIS_ALL)
			&& ProcLENS[iUnit].MoveCompleted_Lens_Teaching(Wait_Pos, AXIS_ALL))
		{
			/*
			sMsg.Format("[ 운전 준비 ] 운전 준비 완료.");
			g_PushLogQueue(sMsg, DEF_TYPE_MOTIONLOG  + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_MOTIONLOG  + GetUnitNum(iUnit), (LPARAM)&sMsg);
			Task[iUnit].bRunningReady = true;
			iThreadStep = 99999;
			*/

			iThreadStep = 24500;
		}
		else if(!ProcPCB[iUnit].MoveCompleted_Pcb_Teaching(Wait_Pos, AXIS_ALL))
		{
			if(func_TimeChecker_Compare(TIME_AXIS, dSTime))
			{
			sMsg.Format("[ 운전준비 ] PCB 대기위치 이동 시간 초과  [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -17000;
			}

		}
		else if(!ProcLENS[iUnit].MoveCompleted_Lens_Teaching(Wait_Pos, AXIS_ALL))
		{
			if(func_TimeChecker_Compare(TIME_AXIS, dTime))
			{
			sMsg.Format("[ 운전준비 ] LENS 대기위치 이동 시간 초과  [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -16000;
			}
		}
		
		break;

	case 24500:	//CL Y축 후진
 		if( ProcCL[iUnit].MotionMove_CL_Teaching(Wait_Pos))
 		{
			dTime = func_TimeChecker_CurrentTime(true);		
			iThreadStep = 24600;
 		}
 		else
 		{
 			sMsg.Format("[ 운전준비 ] CL_Y축 대기위치 이동 명령 실패");
 			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
 			iThreadStep = -24500;
 		}
		break;

	case 24600:
		if( ProcCL[iUnit].MoveCompleted_CL_Teaching(Wait_Pos))
		{
			sMsg.Format("[ 운전 준비 ] 운전 준비 완료.");
			g_PushLogQueue(sMsg, DEF_TYPE_MOTIONLOG  + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_MOTIONLOG  + GetUnitNum(iUnit), (LPARAM)&sMsg);
			Task[iUnit].bRunningReady = true;
			iThreadStep = 99999;
		}
		else if(func_TimeChecker_Compare(TIME_AXIS, dTime))
		{
			sMsg.Format("[ 운전준비 ] CL_Y축 대기위치 이동 시간 초과 [TIME : %d (s)]", (TIME_AXIS / 1000));
			g_PushLogQueue(sMsg, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit));
				//::SendMessage(hMainDlg, WM_SEND_LOG, DEF_TYPE_ERRORLOG  + DEF_LOG_POPUP + GetUnitNum(iUnit), (LPARAM)&sMsg);
			iThreadStep = -24500;
		}
		break;

	default:
		iThreadStep = -10000;
		break;
	}

	return iThreadStep;
}
 
