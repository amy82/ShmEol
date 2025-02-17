#include "stdafx.h"
#include "AxlMotorSet.h"


//-----------------------------------------------------------------------------
//
//	생성자
//
//-----------------------------------------------------------------------------
CAxlMotorSet::CAxlMotorSet()
{
	int i;
	int iUnit = 0;

	m_bAxlInitResult = false;
	m_bOqaOrgFlag = false;
	for(iUnit = 0; iUnit < MAX_UNIT_COUNT; iUnit++)
	{
		for (i = 0; i < MAX_MOTOR_COUNT; i++)
		{
			m_bOrgFlag[iUnit][i] = false;	//원점 상태 초기화
			m_nHomeProcUsing[iUnit][i] = 0;	//개별 원점 요구 상태 초기화

			m_bJogPlusFlag[iUnit][i] = false;
			m_bJogMinusFlag[iUnit][i] = false;
			m_bOldJogPlusFlag[iUnit][i] = false;	//! 현재 동작 중이 (+)Jog 상태
			m_bOldJogMinusFlag[iUnit][i] = false;	//! 현재 동작 중이 (-)Jog 상태
		}
	}
	
	//! Motor 설정 정보 저장 파일의 절대 경로 (Motion Controller Library에서 지원하는 기능)
#ifdef _M_X64
	m_sMotionSettingFilePath = _T("C:/Program Files (x86)/EzSoftware RM/EzSoftware/MotionSetting.mot");
#else
	m_sMotionSettingFilePath = _T("C:/Program Files/EzSoftware RM/EzSoftware/MotionSetting.mot");
#endif
}

//-----------------------------------------------------------------------------
//
//	소멸자
//
//-----------------------------------------------------------------------------
CAxlMotorSet::~CAxlMotorSet()
{
	this->Axl_Close();
}


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::Axl_Init()
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	TCHAR szLog[SIZE_OF_1K];
	long lBoardCount;
	DWORD dwRetVal;
	CFileFind clFinder;
	int i;
	int iUnit = 0;

	lBoardCount = 0;
	dwRetVal = 0;

	// 플래그 초기화
	m_bAxlInitResult = false;
	m_bOqaOrgFlag = false;
	// 원점 상태 초기화
	for(iUnit = 0; iUnit < MAX_UNIT_COUNT; iUnit++)
	{
		for (i = 0; i < MAX_MOTOR_COUNT; i++)
		{
			m_bOrgFlag[iUnit][i] = false;
		}
	}

	//라이브러리 초기화  0 : 쓰레기값..
	dwRetVal = AxlOpen(0);
	if (dwRetVal != AXT_RT_SUCCESS)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("모션 보드 초기화를 실패 하였습니다."));
		//AddLog(szLog, 1, 999);
        AddLog(szLog, 1, 0);
        //AddLog(szLog, 1, 1);
		return false;
	}

	//! 등록된 AXL 사용가능 보드의 개수를 확인한다.	
	AxlGetBoardCount(&lBoardCount);
	if (lBoardCount < 1)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("모션 보드 인식을 실패하였습니다."));
		//AddLog(szLog, 1, 999);
        AddLog(szLog, 1, 0);
        //AddLog(szLog, 1, 1);
		return false;
	}

	_stprintf_s(szLog, SIZE_OF_1K, _T("Motor 보드 인식 완료[Count : %d]"), lBoardCount);
	//AddLog(szLog, 0, 999);
    AddLog(szLog, 0, 0);
    //AddLog(szLog, 0, 1);

	TCHAR* pszPath = NULL;
	pszPath = m_sMotionSettingFilePath.GetBuffer(m_sMotionSettingFilePath.GetLength() + 1);

	//if (IsExist_Path(m_sMotionSettingFilePath) == true)
	if(clFinder.FindFile(pszPath) == TRUE)
	{
		//! 모든 축의 초기 값을 지정한 파일에서 읽어 설정한다. 
		if (AxmMotLoadParaAll(CT2A(pszPath)) != AXT_RT_SUCCESS)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("모션 보드 파라미터 파일 설정을 실패하였습니다."));
			//AddLog(szLog, 1, 999);
            AddLog(szLog, 1, 0);
            //AddLog(szLog, 1, 1);
			return false;
		}
	}
	else
	{
		//! 모든 축의 초기 값을 파일에 저장 한다. 
		AxmMotSaveParaAll(pszPath);//AxmMotSaveParaAll(CT2A(pszPath));
	}

	m_sMotionSettingFilePath.ReleaseBuffer();




	int MAX_AA_COUNT = 1;

	
	for(iUnit = 0; iUnit < MAX_AA_COUNT; iUnit++)
	{
		//! 초기 설정
		/*this->AmpDisableAll(iUnit);*/
		// 모션보드 구성설정
		if (this->Axl_Axisconfig(iUnit) != 1)
		{
			m_bAxlInitResult = false;
		}

		this->AmpDisableAll(iUnit);
	}

	m_bAxlInitResult = true;

	return m_bAxlInitResult;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CAxlMotorSet::Axl_Close()
{
#ifndef ON_LINE_MOTOR
	return;
#endif

	int i;
	int iUnit = 0;

	int MAX_AA_COUNT = 2;
	// 모든 모터를 정지한다.
	for (i = 0; i < (MAX_MOTOR_COUNT * MAX_AA_COUNT); i++)
	{
		AxmMoveSStop(MOTOR_AXIS_NUMBER[i]);
	}

	TCHAR* pszPath = NULL;
	pszPath = m_sMotionSettingFilePath.GetBuffer(m_sMotionSettingFilePath.GetLength() + 1);
	//! 모든 축의 현재 설정값을 파일에 저장 한다. 
	AxmMotSaveParaAll(CT2A(pszPath));
	m_sMotionSettingFilePath.ReleaseBuffer();

	AxlClose();

	// 원점 상태 초기화
	for(iUnit = 0; iUnit < MAX_UNIT_COUNT; iUnit++)
	{
		for (i = 0; i < MAX_MOTOR_COUNT; i++)
		{
			m_bOrgFlag[iUnit][i] = false;
		}
	}
}

//-----------------------------------------------------------------------------
//! 장비 전체의 Axis의 초기 설정을 진행한다. 
//! [주의 사항] 
//!    1) 반드시, 'Axl_Init' 함수의 'AxmMotLoadParaAll' 함수 호출 후에 이 함수를 호출하여야 한다. 
//!    2) PCI-R1604의 A4N, A5N서보드라이브의 경우(PM제외) Limit/Home/Servo On/Inposition의 Level을 설정 하실 수 없고 High또는 Low로 고정이 되어있습니다. 
//!		  Limit 센서의 A/B접을 바꾸고자 할때는 서보드라이브의 파라메터를 바꾸어야 합니다.
//-----------------------------------------------------------------------------
int CAxlMotorSet::Axl_Axisconfig(int nUnit)
{
#ifndef ON_LINE_MOTOR
	return 1;
#endif

	TCHAR szLog[SIZE_OF_1K];
	DWORD dwStatus;
	DWORD dwRetVal;
	long lAxisCount;
	int nFailCount;
	int nUseAxis;
	int i;

	dwStatus = 0;
	dwRetVal = 0;
	lAxisCount = 0;
	nUseAxis = 0;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;
	
	//! 보드내에 인터럽트 사용을 해제 시킨다. (RTEX 지원 안함)
	AxlInterruptDisable();

	//! 시스템에 장착된 축 개수를 확인	
	AxmInfoGetAxisCount(&lAxisCount);
	int MAX_AA_COUNT = 0;
	int MotorTotalCount = 0;

	MotorTotalCount = MAX_MOTOR_COUNT;

	if (lAxisCount != MotorTotalCount)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("모터 드라이브 개수 불일치[%d / %d]"), lAxisCount, MotorTotalCount);
		AddLog(szLog, 1, nUnit);

		return -4;
	}

	_stprintf_s(szLog, SIZE_OF_1K, _T("Motor 드라이브 인식 완료[Count : %d]"), lAxisCount);
	AddLog(szLog, 0, nUnit);

	nFailCount = 0;
	for (i = 0; i < MAX_MOTOR_COUNT; i++)	
	{
		nUseAxis = (nUnit * MAX_MOTOR_COUNT) + i;

		dwRetVal = AxmInfoIsInvalidAxisNo(MOTOR_AXIS_NUMBER[nUseAxis]);
		if (dwRetVal != AXT_RT_SUCCESS)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 드라이브 인식 실패"), MOTOR_NAME[i]);
			AddLog(szLog, 1, nUnit);

			nFailCount++;

			continue;
		}

		dwRetVal = AxmMotSetMoveUnitPerPulse(MOTOR_AXIS_NUMBER[nUseAxis], 1, 1);
		if (dwRetVal != AXT_RT_SUCCESS)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 드라이브 전자기어비 초기화 실패"), MOTOR_NAME[i]);
			AddLog(szLog, 1, nUnit);

			nFailCount++;

			continue;
		}

		dwRetVal = AxmMotSetMinVel(MOTOR_AXIS_NUMBER[nUseAxis], 1);
		if (dwRetVal != AXT_RT_SUCCESS)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 드라이브 최소 속도 설정 실패"), MOTOR_NAME[i]);
			AddLog(szLog, 1, nUnit);

			nFailCount++;

			continue;
		}

#ifdef MOTOR_ACC_TYPE_SEC
		dwRetVal = AxmMotSetAccelUnit(MOTOR_AXIS_NUMBER[nUseAxis], SEC);	//
#else
		dwRetVal = AxmMotSetAccelUnit(MOTOR_AXIS_NUMBER[nUseAxis], UNIT_SEC2);	//
#endif

		if (dwRetVal != AXT_RT_SUCCESS)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 드라이브 가속도 단위 설정 실패"), MOTOR_NAME[i]);
			AddLog(szLog, 1, nUnit);

			nFailCount++;

			continue;
		}

		dwRetVal = AxmMotSetProfileMode(MOTOR_AXIS_NUMBER[nUseAxis], ASYM_S_CURVE_MODE);	//도포 구간 사용 수정;.		ASYM_TRAPEZOIDE_MODE
		if (dwRetVal != AXT_RT_SUCCESS)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 비대칭 S-Curve 가감속 설정 실패"), MOTOR_NAME[i]);
			AddLog(szLog, 1, nUnit);

			nFailCount++;

			continue;
		}

		// S-Curve Motion 구동시, Curve 비율 설정 - Default 값으로 100% 
		double dAccelJerk = 0.0, dDecelJerk = 0.0;

		dwRetVal = AxmMotSetAccelJerk(MOTOR_AXIS_NUMBER[nUseAxis], 30);
		dwRetVal = AxmMotSetDecelJerk(MOTOR_AXIS_NUMBER[nUseAxis], 30);

		AxmMotGetAccelJerk(MOTOR_AXIS_NUMBER[nUseAxis], &dAccelJerk);
		AxmMotGetDecelJerk(MOTOR_AXIS_NUMBER[nUseAxis], &dDecelJerk);

		if (dAccelJerk != 30.0 || dDecelJerk != 30.0) 
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 지정축 가속 저크값 설정 실패"), MOTOR_NAME[i]);
			AddLog(szLog, 0, nUnit);

			nFailCount++;
			continue;
		}

		dwRetVal = AxmMotSetAbsRelMode(MOTOR_AXIS_NUMBER[nUseAxis], POS_ABS_MODE);
		if (dwRetVal != AXT_RT_SUCCESS)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 절대 위치 이동 모드 설정 실패"), MOTOR_NAME[i]);
			AddLog(szLog, 0, nUnit);

			nFailCount++;
			continue;
		}

		DWORD	dwHomLevel;

		if (nUseAxis - (nUnit * MAX_MOTOR_COUNT) == MOTOR_PCB_Z || nUseAxis - (nUnit * MAX_MOTOR_COUNT) == MOTOR_PCB_TX || nUseAxis - (nUnit * MAX_MOTOR_COUNT) == MOTOR_PCB_TY)
		{
			dwRetVal = AxmHomeSetSignalLevel(MOTOR_AXIS_NUMBER[nUseAxis], HIGH);
		}
		else
		{
			dwRetVal = AxmHomeSetSignalLevel(MOTOR_AXIS_NUMBER[nUseAxis], LOW);		//기존코드
		}

		
		dwRetVal = AxmHomeGetSignalLevel(MOTOR_AXIS_NUMBER[nUseAxis], &dwHomLevel);
		if (dwRetVal != AXT_RT_SUCCESS)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 HOME LEVEL 설정 실패"), MOTOR_NAME[i]);
			AddLog(szLog, 0, nUnit);

			nFailCount++;
			continue;
		}

		DWORD	dwMaxVel;
		dwMaxVel = AxmMotSetMaxVel(MOTOR_AXIS_NUMBER[nUseAxis], MOTOR_SPEED_MAX[i] * g_clSysData.m_dMotorResol[nUnit][i]);
		if (dwRetVal != AXT_RT_SUCCESS)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 최고 속도 설정 실패"), MOTOR_NAME[i]);
			AddLog(szLog, 0, nUnit);

			nFailCount++;
			continue;
		}

		//! OneHighLowHigh      1펄스 방식, PULSE(Active High)  +방향(DIR=Low)  / -방향(DIR=High)
		//! OneHighHighLow      1펄스 방식, PULSE(Active High)  +방향(DIR=High) / -방향(DIR=Low)
		//! OneLowLowHigh       1펄스 방식, PULSE(Active Low)   +방향(DIR=Low)  / -방향(DIR=High)
		//! OneLowHighLow       1펄스 방식, PULSE(Active Low)   +방향(DIR=High) / -방향(DIR=Low)
		//! TwoCcwCwHigh        2펄스 방식, PULSE(CW:-방향)  DIR(CCW:+방향), Active High
		//! TwoCcwCwLow         2펄스 방식, PULSE(CW:-방향)  DIR(CCW:+방향), Active Low
		//! TwoCwCcwHigh        2펄스 방식, PULSE(CW:+방향)  DIR(CCW:-방향), Active High
		//! TwoCwCcwLow         2펄스 방식, PULSE(CW:+방향)  DIR(CCW:-방향), Active Low
		switch (MOTOR_TYPE[i])
		{
		case LINEAR:
			dwRetVal = AxmSignalSetInpos(MOTOR_AXIS_NUMBER[nUseAxis], HIGH);
			if (dwRetVal != AXT_RT_SUCCESS)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 Inposition 설정 실패"), MOTOR_NAME[i]);
				AddLog(szLog, 0, nUnit);

				nFailCount++;
			}

			dwRetVal = AxmSignalSetStop(MOTOR_AXIS_NUMBER[nUseAxis], EMERGENCY_STOP, LOW);
			if (dwRetVal != AXT_RT_SUCCESS)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 비상 정지 설정 실패"), MOTOR_NAME[i]);
				AddLog(szLog, 0, nUnit);

				nFailCount++;
			}
			dwRetVal = AxmSignalSetLimit(MOTOR_AXIS_NUMBER[nUseAxis], EMERGENCY_STOP, LOW, LOW);
            //if (nUseAxis - (nUnit * MAX_MOTOR_COUNT) == MOTOR_PCB_Z || nUseAxis - (nUnit * MAX_MOTOR_COUNT) == MOTOR_LENS_Z)//(nUnit * MAX_MOTOR_COUNT) + i;
            //{
            //    dwRetVal = AxmSignalSetLimit(nUseAxis, EMERGENCY_STOP, LOW, LOW);
            //}
            //else
            //{
            //    dwRetVal = AxmSignalSetLimit(nUseAxis, EMERGENCY_STOP, HIGH, HIGH);
            //}
			
			if (dwRetVal != AXT_RT_SUCCESS)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 Limit 감지 정지 설정 실패"), MOTOR_NAME[i]);
				AddLog(szLog, 0, nUnit);

				nFailCount++;
			}

			dwRetVal = AxmSignalSetServoAlarm(MOTOR_AXIS_NUMBER[nUseAxis], HIGH);
			if (dwRetVal != AXT_RT_SUCCESS)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 SERVER Alarm 감지 설정 실패"), MOTOR_NAME[i]);
				AddLog(szLog, 0, nUnit);

				nFailCount++;
			}
			break;
			//==================================================================================★★★★★★
			//
			//
			//
			//
		case STEPING:
			dwRetVal = AxmSignalSetInpos(MOTOR_AXIS_NUMBER[nUseAxis], UNUSED);
			if (dwRetVal != AXT_RT_SUCCESS)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 Inposition 설정 실패"), MOTOR_NAME[i]);
				AddLog(szLog, 0, nUnit);

				nFailCount++;
			}
			dwRetVal = AxmMotSetPulseOutMethod(MOTOR_AXIS_NUMBER[nUseAxis], TwoCcwCwHigh);
			if (dwRetVal != AXT_RT_SUCCESS)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 CW/CCW 설정 실패"), MOTOR_NAME[i]);
				AddLog(szLog, 0, nUnit);

				nFailCount++;
			}

			dwRetVal = AxmSignalSetStop(MOTOR_AXIS_NUMBER[nUseAxis], EMERGENCY_STOP, HIGH);// LOW);//
			if (dwRetVal != AXT_RT_SUCCESS)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 비상 정지 설정 실패"), MOTOR_NAME[i]);
				AddLog(szLog, 0, nUnit);

				nFailCount++;
			}
			//
			dwRetVal = AxmSignalSetLimit(MOTOR_AXIS_NUMBER[nUseAxis], EMERGENCY_STOP, LOW, LOW);
			if (dwRetVal != AXT_RT_SUCCESS)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 Limit 감지 정지 설정 실패"), MOTOR_NAME[i]);
				AddLog(szLog, 0, nUnit);

				nFailCount++;
			}

			
			//정방향 4체배
			dwRetVal = AxmMotSetEncInputMethod(MOTOR_AXIS_NUMBER[nUseAxis], ObverseSqr4Mode);
			if (dwRetVal != AXT_RT_SUCCESS)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 4체배 설정 실패"), MOTOR_NAME[i]);
				AddLog(szLog, 0, nUnit);

				nFailCount++;
			}

			dwRetVal = AxmSignalSetServoOnLevel(MOTOR_AXIS_NUMBER[nUseAxis], HIGH);
			if (dwRetVal != AXT_RT_SUCCESS)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 Servo On Level 설정 실패"), MOTOR_NAME[i]);
				AddLog(szLog, 0, nUnit);

				nFailCount++;
			}
			if (nUseAxis - (nUnit * MAX_MOTOR_COUNT) == MOTOR_PCB_Z)
			{
				dwRetVal = AxmSignalSetServoAlarm(MOTOR_AXIS_NUMBER[nUseAxis], LOW);
			}
			else
			{
				dwRetVal = AxmSignalSetServoAlarm(MOTOR_AXIS_NUMBER[nUseAxis], HIGH);
			}
			
			
			if (dwRetVal != AXT_RT_SUCCESS)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 SERVER Alarm 감지 설정 실패"), MOTOR_NAME[i]);
				AddLog(szLog, 0, nUnit);

				nFailCount++;
			}
			break;
		}
	}

	if (nFailCount > 0)
	{
		return -nFailCount;
	}

	return 1;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::ReadBit(int nUnit, int nAxis, int nBit)
{
#ifndef ON_LINE_MOTOR
	return TRUE;
#endif

	DWORD dwOn = 0;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	
	AxmSignalReadInputBit(MOTOR_AXIS_NUMBER[nUseAxis], nBit, &dwOn);

	if (dwOn == 1)
		return TRUE;
	else
		return FALSE;
}

//-----------------------------------------------------------------------------
//
//	개별 축 AMP ENABLE
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::AmpEnable(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	DWORD dwLevel = ENABLE;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	this->StopAxis(nUnit, nAxis);

	//! 이미 Servo On 상태인지 확인한다. 
	AxmSignalIsServoOn(MOTOR_AXIS_NUMBER[nUseAxis], &dwLevel);
	if (dwLevel == ENABLE)
		return true;

	m_bOrgFlag[nUnit][nAxis] = false;
	AxmSignalServoOn(MOTOR_AXIS_NUMBER[nUseAxis], ENABLE);

	Sleep(150);

	AxmSignalIsServoOn(MOTOR_AXIS_NUMBER[nUseAxis], &dwLevel);
	if (dwLevel != ENABLE) {
		return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
//
//	UNIT 전체 AMP ENABLE
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::AmpEnableAll(int nUnit)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	TCHAR szLog[SIZE_OF_1K];
	DWORD dwLevel;
	bool bRetVal;
	int i;
	int nUseAxis = 0;

	dwLevel = ENABLE;
	bRetVal = true;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	this->StopAxisAll(nUnit);
	Sleep(1000);
	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		nUseAxis = (nUnit * MAX_MOTOR_COUNT) + i;
		m_bOrgFlag[nUnit][i] = false;

		AxmSignalIsServoOn(MOTOR_AXIS_NUMBER[nUseAxis], &dwLevel);
		if (dwLevel == ENABLE)
			continue;

		AxmSignalServoOn(MOTOR_AXIS_NUMBER[nUseAxis], ENABLE);
		Sleep(200);

		AxmSignalIsServoOn(MOTOR_AXIS_NUMBER[nUseAxis], &dwLevel);

		

		if (dwLevel != ENABLE)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[ERROR] Servo On 실패[%d]"), i);
			AddLog(szLog, 1, nUnit);
			bRetVal = false;
			//break;
		}
	}

	if (bRetVal == false)
	{
		//DoSleepEvents();

		for (i = 0; i < MAX_MOTOR_COUNT; i++)
		{
			nUseAxis = (nUnit * MAX_MOTOR_COUNT) + i;
			m_bOrgFlag[nUnit][i] = false;

			AxmSignalIsServoOn(MOTOR_AXIS_NUMBER[nUseAxis], &dwLevel);
			if (dwLevel == ENABLE)
				continue;

			AxmSignalServoOn(MOTOR_AXIS_NUMBER[nUseAxis], ENABLE);
			Sleep(200);

			AxmSignalIsServoOn(MOTOR_AXIS_NUMBER[nUseAxis], &dwLevel);
			if (dwLevel != ENABLE)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[ERROR] Servo On 실패[%d]"), i);
				AddLog(szLog, 1, nUnit);
				bRetVal = false;
				//break;
			}
		}
	}

	if (bRetVal == false)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[ERROR] AmpEnableAll 실패"));
		AddLog(szLog, 1, nUnit);
	}

	return bRetVal;
}

//-----------------------------------------------------------------------------
//
//! 지정 축의 Servo-Off을 실시
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::AmpDisable(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	double dDecel = 0.;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	m_bOrgFlag[nUnit][nAxis] = false;

	AxmMoveStop(MOTOR_AXIS_NUMBER[nUseAxis], dDecel);
	AxmSignalServoOn(MOTOR_AXIS_NUMBER[nUseAxis], DISABLE);

	//DoSleepEvents();
	Sleep(300);

	if (MOTOR_TYPE[nAxis] == STEPING)
		AxmSignalServoAlarmReset(MOTOR_AXIS_NUMBER[nUseAxis], ENABLE);

	return true;
}

//-----------------------------------------------------------------------------
//
//	UNIT 전체 축 SERVO OFF
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::AmpDisableAll(int nUnit)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	double dDecel = 0.0;
	int nUseAxis = 0;
	int i;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		nUseAxis = (nUnit * MAX_MOTOR_COUNT) + i;

		AxmMoveStop(MOTOR_AXIS_NUMBER[nUseAxis], dDecel);
		AxmSignalServoOn(MOTOR_AXIS_NUMBER[nUseAxis], DISABLE);


		AxmSignalServoAlarmReset(MOTOR_AXIS_NUMBER[nUseAxis], ENABLE);
		Sleep(100);

		AxmSignalServoAlarmReset(MOTOR_AXIS_NUMBER[nUseAxis], DISABLE);
		////if (MOTOR_TYPE[i] == STEPING) 
		//{

		//	AxmSignalServoAlarmReset(MOTOR_AXIS_NUMBER[nUseAxis], ENABLE);
		//}
		Sleep(200);
	}
	

	return true;
}

//-----------------------------------------------------------------------------
//
//	지정 축의 Servo-On 신호의 출력 상태를 반환(T=ON, F=OFF 상태)
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::GetAmpEnable(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	DWORD dwStatus = 0;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	
	// Servo 알람 확인.
	AxmSignalIsServoOn(MOTOR_AXIS_NUMBER[nUseAxis], &dwStatus);	// upStatus  1: Servo On
	if (dwStatus == ACTIVE)
	{
		return true;
	}

	m_bOrgFlag[nUnit][nAxis] = false;

	return false;
}

//-----------------------------------------------------------------------------
//
//	Servo-Off 상태가 있을 경우 false
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::GetAmpEnableAll(int nUnit)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	DWORD dwStatus = 0;
	int nUseAxis = 0;
	bool bRetVal = true;
	int i;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		nUseAxis = (nUnit * MAX_MOTOR_COUNT) + i;

		AxmSignalIsServoOn(MOTOR_AXIS_NUMBER[nUseAxis], &dwStatus);	// upStatus  1: Servo On
		if (dwStatus != ACTIVE)
		{
			m_bOrgFlag[nUnit][i] = false;
			bRetVal = false;
			break;
		}
	}

	return bRetVal;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::GetOrgFlagAll(int nUnit)
{
	int i;
	bool bRetVal = true;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	for(i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if(m_bOrgFlag[nUnit][i] == false)
		{
			bRetVal = false;
			break;
		}
	}

	return bRetVal;
}

//-----------------------------------------------------------------------------
//
//	지정 축 알람 Reset후 Servo-On
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::AmpFaultReset(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	double dDecel = 0.0;
	DWORD dwLevel = 0;
	int nUseAxis = 0;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	// 원점 플래그 초기화
	m_bOrgFlag[nUnit][nAxis] = false;

	AxmMoveStop(MOTOR_AXIS_NUMBER[nUseAxis], dDecel);
	AxmSignalServoOn(MOTOR_AXIS_NUMBER[nUseAxis], DISABLE);

	AxmSignalServoAlarmReset(MOTOR_AXIS_NUMBER[nUseAxis], ENABLE);

	//DoSleepEvents();
	Sleep(100);

	AxmSignalServoAlarmReset(MOTOR_AXIS_NUMBER[nUseAxis], DISABLE);
	AxmSignalServoOn(MOTOR_AXIS_NUMBER[nUseAxis], ENABLE);

	//DoSleepEvents();
	Sleep(100);

	AxmSignalIsServoOn(MOTOR_AXIS_NUMBER[nUseAxis], &dwLevel);
	if (dwLevel != ENABLE)
		return false;

	return true;
}

//-----------------------------------------------------------------------------
//
//	UNIT 전체 축 알람 Reset후 Servo-On 실시
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::AmpFaultResetAll(int nUnit)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	int i;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;	

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		this->AmpDisable(nUnit, i);
	}

	//DoSleepEvents();
	Sleep(1000);

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		this->AmpEnable(nUnit, i);
	}

	return true;
}

//-----------------------------------------------------------------------------
//
//	알람 신호 확인
//
//-----------------------------------------------------------------------------
int	CAxlMotorSet::AmpFaultCheck(int nUnit)
{
#ifndef ON_LINE_MOTOR
	return 0;
#endif

	DWORD dwStatus = 0;
	int nAmpFaultFlag = 0;
	int nUseAxis = 0;
	int i;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;	

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		nUseAxis = (nUnit * MAX_MOTOR_COUNT) + i;
		// 축의 알람 신호 확인
		AxmSignalReadServoAlarm(MOTOR_AXIS_NUMBER[nUseAxis], &dwStatus);
		if (dwStatus == ACTIVE)
		{
			nAmpFaultFlag += 0x01 << i;
			m_bOrgFlag[nUnit][i] = true;
		}
	}

	return nAmpFaultFlag;
}
bool CAxlMotorSet::GetServoOn(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return false;
#endif

	DWORD dwLevel = 0;
	int nUseAxis = 0;

	if ((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if ((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = nUnit * MAX_MOTOR_COUNT + nAxis;

	AxmSignalIsServoOn(MOTOR_AXIS_NUMBER[nUseAxis], &dwLevel);
	if (dwLevel == ENABLE)
		return true;

	return false;
}

//-----------------------------------------------------------------------------
//
//	지정 축의 알람 상태 반환
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::GetAmpFault(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return false;
#endif

	DWORD dwRetVal = 0;
	DWORD dwStatus = 0;
	DWORD dwUse = 0;
	int nUseAxis = 0;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = nUnit * MAX_MOTOR_COUNT + nAxis;
	
	dwRetVal = AxmSignalGetServoAlarm(MOTOR_AXIS_NUMBER[nUseAxis], &dwUse);
	if (dwRetVal != AXT_RT_SUCCESS)
	{
		return true;
	}

	if (dwUse == UNUSED)
		return true;


	// 축의 알람 신호 확인
	dwRetVal = AxmSignalReadServoAlarm(MOTOR_AXIS_NUMBER[nUseAxis], &dwStatus);
	if (dwRetVal != AXT_RT_SUCCESS)
	{
		m_bOrgFlag[nUnit][nAxis] = false;
		return true;
	}

	if (dwStatus == ACTIVE)
	{
		m_bOrgFlag[nUnit][nAxis] = false;
		return true;
	}

	return false;
}


//! Motor가 목표 지점에 도착했는지 확인
//-----------------------------------------------------------------------------
//
// 지정 축의 Motor가 목표 지점에 도착했는지 확인
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::GetInposition(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	DWORD dwRetVal = 0;
	DWORD dwStatus = 0;
	DWORD dwUse = 0;
	bool bRetVal = true;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	
	//! Inposition 신호 설정 확인
	//dwRet = AxmSignalGetInpos(iUseAxis, &use);
	//if ( dwRet != AXT_RT_SUCCESS )	return false;
	//if ( use == UNUSED )				return false;

	//! Inpositon 신호의 입력 확인	
	dwRetVal = AxmSignalReadInpos(MOTOR_AXIS_NUMBER[nUseAxis], &dwStatus);
	if (dwRetVal != AXT_RT_SUCCESS)
	{
		bRetVal = false;
	}

	if (dwStatus == INACTIVE)
	{
		bRetVal = false;
	}

	return bRetVal;
}

//-----------------------------------------------------------------------------
//
// 지정 축의 Motor가 목표 지점에 도착했는지 확인( Encord값으로 확인)
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::GetPcbYMotorPosCheck(int nUnit, int dPos)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	double dCurPos = 0.0;
	double dMotorPos = 0.0;

	if ((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;


	dCurPos = this->GetEncoderPos(nUnit, MOTOR_PCB_Y);
	dMotorPos = g_clModelData[nUnit].m_stTeachData[dPos].dPos[MOTOR_PCB_Y];
	if (fabs(dMotorPos - dCurPos) > ENCORDER_GAP)
	{
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------
//
// 지정 축의 Motor가 목표 지점에 도착했는지 확인( Encord값으로 확인)
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::GetPcbXYMotorPosCheck(int nUnit,int dPos)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	double dCurPos = 0.0;
	double dMotorPos = 0.0;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;


	if (dPos == LASER_POS)
	{
		double dLaserPosX[4];
		double dLaserPosY[4];
		double currentX = this->GetEncoderPos(nUnit, MOTOR_PCB_X);
		double currentY = this->GetEncoderPos(nUnit, MOTOR_PCB_Y);
		dLaserPosX[0] = g_clModelData[nUnit].m_stTeachData[LASER_POS].dPos[MOTOR_PCB_X];
		dLaserPosX[1] = g_clModelData[nUnit].m_stTeachData[LASER_POS].dPos[MOTOR_PCB_X] - (g_clModelData[nUnit].m_dLaserMoveX[0] * -1);
		dLaserPosX[2] = g_clModelData[nUnit].m_stTeachData[LASER_POS].dPos[MOTOR_PCB_X] - (g_clModelData[nUnit].m_dLaserMoveX[0] * -1);
		dLaserPosX[3] = g_clModelData[nUnit].m_stTeachData[LASER_POS].dPos[MOTOR_PCB_X];

		dLaserPosY[0] = g_clModelData[nUnit].m_stTeachData[LASER_POS].dPos[MOTOR_PCB_Y];
		dLaserPosY[1] = g_clModelData[nUnit].m_stTeachData[LASER_POS].dPos[MOTOR_PCB_Y];
		dLaserPosY[2] = g_clModelData[nUnit].m_stTeachData[LASER_POS].dPos[MOTOR_PCB_Y] + g_clModelData[nUnit].m_dLaserMoveY[0];
		dLaserPosY[3] = g_clModelData[nUnit].m_stTeachData[LASER_POS].dPos[MOTOR_PCB_Y] + g_clModelData[nUnit].m_dLaserMoveY[0];
		for (int i = 0; i < 4; i++)
		{
			if (fabs(currentX - dLaserPosX[i]) < ENCORDER_GAP && fabs(currentY - dLaserPosY[i]) < ENCORDER_GAP)
			{
				return true;
			}
		}
	}
	else
	{
		for (int nAxis = MOTOR_PCB_X; nAxis < MOTOR_PCB_Y; nAxis++)
		{
			dCurPos = this->GetEncoderPos(nUnit, nAxis);
			dMotorPos = g_clModelData[nUnit].m_stTeachData[dPos].dPos[nAxis];
			if (fabs(dMotorPos - dCurPos) > ENCORDER_GAP)
			{
				return false;
			}
		}
	}
	return true;
}
bool CAxlMotorSet::GetLensXYMotorPosCheck(int nUnit, int dPos)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	return true;
}

bool CAxlMotorSet::GetPcbZMotorPosCheck(int nUnit, int dPos)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif


	double dCurPos = 0.0;
	double dMotorPos = 0.0;

	if ((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	dCurPos = this->GetEncoderPos(nUnit, MOTOR_PCB_Z);
	dMotorPos = g_clModelData[nUnit].m_stTeachData[dPos].dPos[MOTOR_PCB_Z];
	if (fabs(dMotorPos - dCurPos) > ENCORDER_GAP)
	{
		return false;
	}
	return true;
}

bool CAxlMotorSet::GetLensZMotorPosCheck(int nUnit, int dPos)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	return true;
}
//-----------------------------------------------------------------------------
//
// 지정 축의 Home 센서 신호의 입력 확인
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::GetHomeSensor(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	DWORD dwRetVal = 0;
	DWORD dwStatus = 0;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;

	//int ret = home_switch(axis);
	//return ret ? true : false;
	//! Home 신호의 입력 확인
	dwRetVal = AxmHomeReadSignal(MOTOR_AXIS_NUMBER[nUseAxis], &dwStatus);
	if (dwRetVal != AXT_RT_SUCCESS)
		return false;

	if (dwStatus == INACTIVE)
		return false;


	return true;
}

//-----------------------------------------------------------------------------
//
// 지정 축의 (-)리미트 센서 신호의 입력 확인
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::GetNegaSensor(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	DWORD dwRetVal = 0;
	DWORD dwStopMode = 0;
	DWORD dwPositiveLevel = 0;
	DWORD dwNegativeLevel = 0;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	dwRetVal = AxmSignalGetLimit(MOTOR_AXIS_NUMBER[nUseAxis], &dwStopMode, &dwPositiveLevel, &dwNegativeLevel);
	if (dwRetVal != AXT_RT_SUCCESS)
		return false;

	if (dwNegativeLevel == UNUSED)
		return false;

	//return ret ? true : false;
	//! 리미트 센서 입력 상태 확인

	dwRetVal = AxmSignalReadLimit(MOTOR_AXIS_NUMBER[nUseAxis], &dwPositiveLevel, &dwNegativeLevel);
	if (dwRetVal != AXT_RT_SUCCESS)
		return false;

	if (dwNegativeLevel == ACTIVE)
		return true;

	return false;
}

//-----------------------------------------------------------------------------
//
// 지정 축의 (+)리미트 센서 신호의 입력 확인
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::GetPosiSensor(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	DWORD dwRetVal = 0;
	DWORD dwStopMode = 0;
	DWORD dwPositiveLevel = 0;
	DWORD dwNegativeLevel = 0;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;	
	dwRetVal = AxmSignalGetLimit(MOTOR_AXIS_NUMBER[nUseAxis], &dwStopMode, &dwPositiveLevel, &dwNegativeLevel);
	if (dwRetVal != AXT_RT_SUCCESS)
		return false;

	if (dwPositiveLevel == UNUSED)
		return false;

	//int ret = pos_switch(axis);
	//return ret ? true : false;
	//! 리미트 센서 입력 상태 확인

	dwRetVal = AxmSignalReadLimit(MOTOR_AXIS_NUMBER[nUseAxis], &dwPositiveLevel, &dwNegativeLevel);
	if (dwRetVal != AXT_RT_SUCCESS)
		return false;

	if (dwPositiveLevel == ACTIVE)
		return true;

	return false;
}

//-----------------------------------------------------------------------------
//
// 모터위치 '0' SET
//
//-----------------------------------------------------------------------------
void CAxlMotorSet::InitialPos(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return;
#endif
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	
	AxmStatusSetActPos(MOTOR_AXIS_NUMBER[nUseAxis], 0.0);
	AxmStatusSetCmdPos(MOTOR_AXIS_NUMBER[nUseAxis], 0.0);
}


//! CRC 신호 설정(펄스 출력형 모션 제어기에 한정된 기능)
//! 특정 서보팩의 경우 구동이 완료된 시점에서 또는 리미트센서를 감지한 경우에 
//! 외부에서 CRC(Current Remaining Clear)신호를 받아 서보팩이 가지고 있는 잔여 펄스를 지워주어야 하는 경우가 발생한다.
//! [주의 사항] CRC 신호 설정 기능은 펄스 출력형 모션제어기(PCI-N804/404, RTEX-PM)에서만 사용할 수 있는 기능이다.
//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::ActCRC(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	DWORD dwRetVal = 0;
	long  lBoardNo = 0;
	long  lModulePos = 0;
	DWORD dwModuleID = 0;
	DWORD dwLevel = 0;
	DWORD dwMethod = 0;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;
	
	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	//! ModuleID (Module의 종류)
	//! 'AXHS.h' 파일 : 'C:\Program Files\EzSoftware RM\AXL(Library)\C, C++' 폴더안에 있음 (AXT_FUNC_MODULE)	
	//!      AXT_SMC_R1V04    = 0x09,   // CAMC-QI, 1 Axis, For RTEX SLAVE only	
	dwRetVal = AxmInfoGetAxis(MOTOR_AXIS_NUMBER[nUseAxis], &lBoardNo, &lModulePos, &dwModuleID);
	if (dwRetVal != AXT_RT_SUCCESS)
		return false;

	if (dwModuleID != AXT_SMC_R1V04)
		return false;


	//! 지정 축에 CRC 신호 사용 여부 설정을 반환 한다.
	dwRetVal = AxmCrcGetMaskLevel(MOTOR_AXIS_NUMBER[nUseAxis], &dwLevel, &dwMethod);
	if (dwRetVal != AXT_RT_SUCCESS)
		return false;

	//! CRC 신호 사용안함
	if (dwLevel == UNUSED)
		return false;


	//! 지정 축에 CRC 신호를 강제적으로 출력을 발생시킨다. (일정 시간 동안만 작용시킴)
	AxmCrcSetOutput(MOTOR_AXIS_NUMBER[nUseAxis], ENABLE);
	Sleep(10);
	AxmCrcSetOutput(MOTOR_AXIS_NUMBER[nUseAxis], DISABLE);

	return true;
}


//-----------------------------------------------------------------------------
//
//	지정축의 모터 정지여부 반환
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::GetStopAxis(int nUnit, int nAxis)
{//! 모터 정지 상태 반환(T=정지, F=구동중)
#ifndef ON_LINE_MOTOR
	return true;
#endif

	DWORD dwRetVal = 0;
	DWORD dwStatus = 0;
	bool bRetVal = false;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;	
	//! 축의 구동 상태를 확인
	dwRetVal = AxmStatusReadInMotion(MOTOR_AXIS_NUMBER[nUseAxis], &dwStatus);
	if (dwRetVal != AXT_RT_SUCCESS)
	{
		bRetVal = false;
	}

	if (dwStatus == FALSE)
	{
		bRetVal = true;
	}
	
	return bRetVal;
}


//-----------------------------------------------------------------------------
//
//	감속 정지
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::StopAxis(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	TCHAR szLog[SIZE_OF_1K];
	DWORD dwTickCount;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	AxmMoveStop(MOTOR_AXIS_NUMBER[nUseAxis] , 0.0);
	/*AxmMoveSStop(MOTOR_AXIS_NUMBER[nUseAxis]);*/
	//Stop_Home_Search(iAxis);

	dwTickCount = GetTickCount();
	while (!this->GetStopAxis(nUnit, nAxis))
	{
		if((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[FAIL][%s] 모터 정지 시간 초과"), MOTOR_NAME[nAxis]);
			AddLog(szLog, 1, nUnit);

			return false;
		}

		Sleep(5);
	}

	return true;
}

//-----------------------------------------------------------------------------
//
//	UNIT 전체 축 정지
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::StopAxisAll(int nUnit)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	bool bRunFlag[MAX_MOTOR_COUNT] = { false, };
	TCHAR szLog[SIZE_OF_1K];
	DWORD dwTickCount;
	int nUseAxis;	//실제 보드 사용 축 번호
	int i;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;	
	
	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		//! 현재 구동 중인 처음에 사용자가 입력한 가속도만큼 모션 동작을 감속하면서 정지하는 함수이다. 
		nUseAxis = (nUnit * MAX_MOTOR_COUNT) + i;
		AxmMoveSStop(MOTOR_AXIS_NUMBER[nUseAxis]);

		bRunFlag[i] = true;
	}

	dwTickCount = GetTickCount();
	while (1)
	{
		if ((GetTickCount() - dwTickCount) > 1000)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("전체 모터 정지 시간 초과[1 sec]"));
			AddLog(szLog, 1, nUnit);

			return false;
		}

		for (i = 0; i< MAX_MOTOR_COUNT; i++)
		{
			if (bRunFlag[i])
			{
				if (this->GetStopAxis(nUnit, i))
				{
					bRunFlag[i] = false;
					break;
				}
			}
		}

		if (i == MAX_MOTOR_COUNT)
			break;

		//DoSleepEvents();
		Sleep(5);
	}

	return true;
}

//-----------------------------------------------------------------------------
//
// Linear 모터 위치 좌표 반환
//
//-----------------------------------------------------------------------------
double CAxlMotorSet::GetEncoderPos(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return 0.0;
#endif

	double dPos = 0.0;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return dPos;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return dPos;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;	
	if (MOTOR_TYPE[nAxis] == STEPING)
	{
		//if (nAxis == MotIndex_T)
		//{
		//	dPos = GetDDMotorPos(nAxis);
		//}
		//else
		//{
		AxmStatusGetCmdPos(MOTOR_AXIS_NUMBER[nUseAxis], &dPos);
		//dPos /= g_clSysData.m_dMotorResol[nAxis];
		//}
	}
	else
	{
		AxmStatusGetActPos(MOTOR_AXIS_NUMBER[nUseAxis], &dPos);
		//AxmStatusGetCmdPos(nAxis, &dPos);
	}
	dPos /= g_clSysData.m_dMotorResol[nUnit][nAxis];

	//	m_csEncoder.Unlock();

	return dPos; 
}

//-----------------------------------------------------------------------------
//
//	Linear 모터 위치좌표에서 강제 원점 좌표까지 계산된 좌표 반환
//
//-----------------------------------------------------------------------------
double CAxlMotorSet::GetEncoderPos_Disp(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return 0.0;
#endif

	double dPos = 0.0;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return dPos;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return dPos;

	nUseAxis = nUnit * MAX_MOTOR_COUNT + nAxis;
	if (MOTOR_TYPE[nAxis] == STEPING)
	{
		/*if (nAxis == MotIndex_T)
		{
		dPos = GetDDMotorPos_Disp(nAxis);
		return dPos;
		}
		else
		{*/
		AxmStatusGetCmdPos(MOTOR_AXIS_NUMBER[nUseAxis], &dPos);
		//}
		//return (float)pos;
	}
	else
	{
		AxmStatusGetActPos(MOTOR_AXIS_NUMBER[nUseAxis], &dPos);
	}

	dPos /= g_clSysData.m_dMotorResol[nUnit][nAxis];
	dPos -= g_clSysData.m_dOrgDataset[nUnit][nAxis];

	return dPos;
}

//-----------------------------------------------------------------------------
//
// Steping 모터 위치 좌표 반환
//
//-----------------------------------------------------------------------------
double CAxlMotorSet::GetCommandPos(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return 0.0;
#endif

	double dPos = 0.0;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return dPos;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return dPos;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	AxmStatusGetCmdPos(MOTOR_AXIS_NUMBER[nUseAxis], &dPos);

	dPos /= g_clSysData.m_dMotorResol[nUnit][nAxis];

	return dPos;
}

//-----------------------------------------------------------------------------
//
// Steping 모터 위치좌표에서 강제 원점 좌표까지 계산된 좌표 반환	
//
//-----------------------------------------------------------------------------
double CAxlMotorSet::GetCommandPos_Disp(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return 0.0;
#endif

	double dPos = 0.0;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return dPos;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return dPos;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	AxmStatusGetCmdPos(MOTOR_AXIS_NUMBER[nUseAxis], &dPos);

	dPos /= g_clSysData.m_dMotorResol[nUnit][nAxis];
	dPos -= g_clSysData.m_dOrgDataset[nUnit][nAxis];

	return dPos;
}

//-----------------------------------------------------------------------------
//
// Linear 모터 위치 좌표 Setting
//
//-----------------------------------------------------------------------------
void CAxlMotorSet::SetEncoderPos(int nUnit, int nAxis, double dPos)
{
#ifndef ON_LINE_MOTOR
	return;
#endif
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;	
	AxmStatusSetActPos(MOTOR_AXIS_NUMBER[nUseAxis], dPos);
	AxmStatusSetCmdPos(MOTOR_AXIS_NUMBER[nUseAxis], dPos);
}

//-----------------------------------------------------------------------------
//
// Steping 모터 위치 좌표 Setting
//
//-----------------------------------------------------------------------------
void CAxlMotorSet::SetCommandPos(int nUnit, int nAxis, double dPos)
{
#ifndef ON_LINE_MOTOR
	return;
#endif
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	//Steping 모터는 전원 Off후 좌표 Setting 해야함.
	this->AmpDisable(nUnit, nAxis);
	Sleep(100);

	AxmStatusSetActPos(MOTOR_AXIS_NUMBER[nUseAxis], dPos);
	AxmStatusSetCmdPos(MOTOR_AXIS_NUMBER[nUseAxis], dPos);
	Sleep(100);

	AmpEnable(nUnit, nAxis);
}

//-----------------------------------------------------------------------------
//
//	DD 모터 위치 좌표 Setting
//
//-----------------------------------------------------------------------------
double CAxlMotorSet::GetDDMotorPos(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return 0.0;
#endif

	double dPos = 0.0;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return dPos;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return dPos;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	AxmStatusGetCmdPos(MOTOR_AXIS_NUMBER[nUseAxis], &dPos);

	dPos /= g_clSysData.m_dMotorResol[nUnit][nAxis];

	return dPos;
}

//-----------------------------------------------------------------------------
//
// DD 모터 위치 좌표에서 강제 원점 좌표까지 계산된 좌표 반환
//
//-----------------------------------------------------------------------------
double CAxlMotorSet::GetDDMotorPos_Disp(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return 0.0;
#endif

	double dPos = 0.0;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return dPos;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return dPos;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	AxmStatusGetCmdPos(MOTOR_AXIS_NUMBER[nUseAxis], &dPos);

	dPos /= g_clSysData.m_dMotorResol[nUnit][nAxis];
	dPos -= g_clSysData.m_dOrgDataset[nUnit][nAxis];

	return dPos;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
double CAxlMotorSet::GetActPos(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return 0.0;
#endif

	double dPos = 0.0;
	int nUseAxis =0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return dPos;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return dPos;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	AxmStatusGetCmdPos(MOTOR_AXIS_NUMBER[nUseAxis], &dPos);

	return dPos;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
double CAxlMotorSet::GetEncoderPulse(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return 0.0;
#endif

	double dPos = 0.0;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return dPos;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return dPos;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	
	if (MOTOR_TYPE[nAxis] == STEPING)
		AxmStatusGetCmdPos(MOTOR_AXIS_NUMBER[nUseAxis], &dPos);
	else
		AxmStatusGetActPos(MOTOR_AXIS_NUMBER[nUseAxis], &dPos);

	return dPos;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
double CAxlMotorSet::GetCommandPulse(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return 0.0;
#endif

	double dPos = 0.0;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return dPos;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return dPos;	

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	AxmStatusGetCmdPos(MOTOR_AXIS_NUMBER[nUseAxis], &dPos);

	return dPos;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CAxlMotorSet::SetDDMotorCalcPos(int nUnit, int nAxis, double dMaxDeg)
{
	double dCurEncoder = 0.0;
	double dCalEncoder = 0.0;
	double dResultEncoder = 0.0;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return;	

	dCurEncoder = GetActPos(nUnit , nAxis);
	dCalEncoder = dMaxDeg * g_clSysData.m_dMotorResol[nUnit][nAxis];

	//dResultEncoder = GetDoubleModulus(dCurEncoder, dCalEncoder);

	this->SetDDMotorPos(nUnit, nAxis, dResultEncoder);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CAxlMotorSet::SetDDMotorPos(int nUnit, int nAxis, double dPos)
{
#ifndef ON_LINE_MOTOR
	return;
#endif
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;	
	if (this->GetStopAxis(nUnit, nAxis))
	{
		AxmStatusSetPosMatch(MOTOR_AXIS_NUMBER[nUseAxis], dPos);
	}
}

//-----------------------------------------------------------------------------
//
//! 가속도 = 속도/(가속 시간)으로 계산
//
//-----------------------------------------------------------------------------
double CAxlMotorSet::CalcAccFromAccTime(double dVel, double dTime)
{
	double dRetVal;

	dRetVal = 0.;

	if (fabs(dTime) < 0.001)
	{
		dRetVal = dVel / 2.;		//! 가속 시간이 너무 짧아서 강제로 가속 시간을 2 sec로 고정
	}
	else
	{
		dRetVal = dVel / dTime;
		dRetVal *= 1000.;			//! 단위 변환 msec -> sec
	}

	return dRetVal;
}

//-----------------------------------------------------------------------------
//
//	설정한 속도로 구동한다.
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::JogMove(int nUnit, int nAxis, double dVel)
{
#ifndef	ON_LINE_MOTOR
	return true;
#endif

	DWORD dwRetVal = 0;
	double dAcc = 0.0;
	bool bRetVal = true;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = nUnit * MAX_MOTOR_COUNT + nAxis;	

	if (this->GetAmpFault(nUnit, nAxis) == true)
		return false;


#ifdef MOTOR_ACC_TYPE_SEC
	dAcc = (g_clSysData.m_dMotorAccTime[nUnit][nAxis]);
#else
	dAcc = g_clSysData.m_dMotorAccTime[nUnit][nAxis] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis]);		//! 가속 
#endif

	dwRetVal = AxmMoveVel(MOTOR_AXIS_NUMBER[nUseAxis], dVel, dAcc, dAcc);
	if (dwRetVal != AXT_RT_SUCCESS)
	{
		bRetVal = false;
	}

	return bRetVal;
}

//-----------------------------------------------------------------------------
//
// 지정한 축의 구동을 감속정지합니다.
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::JogStop(int nUnit, int nAxis)
{
#ifndef	ON_LINE_MOTOR
	return true;
#endif

	TCHAR szLog[SIZE_OF_1K];
	DWORD dwTickCount;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;	
	AxmMoveSStop(MOTOR_AXIS_NUMBER[nUseAxis]);

	dwTickCount = GetTickCount();
	while (!GetStopAxis(nUnit, nAxis))
	{
		//DoSleepEvents();
		Sleep(10);

		if ((GetTickCount() - dwTickCount) > 1000)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[FAIL][%s] JOG 이동 정지 시간 초과[1 sec]"), MOTOR_NAME[nAxis]);
			AddLog(szLog, 1, nUnit);

			return false;
		}
	}

	return true;
}


//! 특정 위치 (Limit 센서나 Home 센서)에서 자동으로 멈추도록 하여 모터를 움직일 때 사용한다.
//! 지정 축에서 설정된 신호를 검출한다
//! 리미트 센서신호나 원점 센서신호, 서보 드라이버의 Z상 신호 또는 범용 입력 신호들의 Edge를 검출할 수 있다.
//! 주로 원점검색 구동 함수 구현 시 사용하는 함수이다.
//! [주의 사항] 
//!		1) End Limit 센서를 찾을 경우, 신호의 Active Level 상태를 검출한다.
//!     2) Emergency Stop으로 사용할 경우, 가감속이 무시되며 지정된 속도로 가속 급정지하게된다.
//-----------------------------------------------------------------------------
//
// 특정 위치 (Limit 센서나 Home 센서)에서 자동으로 멈추도록 하여 모터를 움직일 때 사용한다.
//
//-----------------------------------------------------------------------------
//bool CAxlMotorSet::MoveAxis_To_Sensor(int axis, strMove_Input_Signal_Search *pstrInput)
//{
//#ifndef ON_LINE_MOTOR
//	return true;
//#endif
//
//	DWORD dwRetVal;
//	double dVel;
//	double dAccel;
//	long lDetectSignal, lSignalEdge, lSignalMethod;
//
//	lDetectSignal = lSignalEdge = lSignalMethod = -1;
//
//	if (pstrInput == NULL)
//		return false;
//
//	dwRetVal = 0;
//	dVel = pstrInput->dVel;
//	dAccel = 0.0;
//
//#ifdef MOTOR_ACC_TYPE_SEC
//	dAccel = pstrInput->dAccel;
//#else
//	dAccel = pstrInput->dAccel * (9.8 * 1000 * g_clSysData.m_dMotorResol[axis]);		//! 가속 
//#endif
//
//	
//	//! lDetectSignal 설정
//	if (pstrInput->bEndLimit_Negative == true)
//		lDetectSignal = NegEndLimit;
//
//	if (pstrInput->bEndLimit_Positive == true)
//		lDetectSignal = PosEndLimit;
//
//	if (pstrInput->bHomeSensor == true)
//		lDetectSignal = HomeSensor;
//
//	if (pstrInput->bPhase_Encoder_Z == true)
//		lDetectSignal = EncodZPhase;
//
//	//! lSignalEdge 설정
//	if (pstrInput->bEdge_Down == true)
//		lSignalEdge = SIGNAL_DOWN_EDGE;
//
//	if (pstrInput->bEdge_Up == true)
//		lSignalEdge = SIGNAL_UP_EDGE;
//
//	//! lSignalMethod 설정
//	if (pstrInput->bEmergency == true)
//		lSignalMethod = EMERGENCY_STOP;
//	if (pstrInput->bSlowDown == true)
//		lSignalMethod = SLOWDOWN_STOP;
//
//	//! 입력값 확인
//	if (lDetectSignal == NegEndLimit)
//		dVel = -1 * fabs(pstrInput->dVel);
//	else
//		dVel = fabs(pstrInput->dVel);
//
//
//	if (dAccel < 0.)
//		return false;
//
//	if (lDetectSignal < 0)
//		return false;
//	
//	if (lSignalEdge < 0)
//		return false;
//	
//	if (lSignalMethod < 0)
//		return false;
//		
//	//! 지정 축에서 설정된 신호를 검출할 때까지 모터를 움직인다. 
//	dwRetVal = AxmMoveSignalSearch(axis, dVel, dAccel, lDetectSignal, lSignalEdge, lSignalMethod);
//	if (dwRetVal != AXT_RT_SUCCESS)
//		return false;
//
//	return true;
//}


//! GUI 화면에서 설정한 길이만큼 움직인다. (상대 이동)
//! GUI 화면에서 많이 사용되는 기능이라서 따로 함수를 만들다. 
//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
//bool CAxlMotorSet::Move_From_GUI(int axis, int iID_GUI, CWnd* pParentWnd, bool bPlus)
//{//! GUI 화면에서 설정한 길이만큼 움직인다. (상대 이동)
//	if (pParentWnd == NULL)			return false;
//	if (bMotorMoving[axis] == true)	return false;
//	bMotorMoving[axis] = true;
//
//	CString sGetTemp = _T("");
//	GetString_FromUI(iID_GUI, pParentWnd, sGetTemp);
//
//	double dGetTemp = atof(sGetTemp);
//	if (dGetTemp > 3.)		dGetTemp = 3.;
//	else if (dGetTemp < -3)	dGetTemp = -3;
//
//	if (bPlus == false)	dGetTemp *= (-1.);
//
//	MoveAxis(axis, REL, dGetTemp, 4/*, 20*/);
//	bMotorMoving[axis] = false;
//
//	return true;
//}
//

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveFromAbsRel(int nUnit, int nAxis, double dPos, bool bPlus)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	static DWORD dwTickCount;
	double dCurrPos = 0.0;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;
	
	if (bPlus == false)
		dPos *= -1.;

	dCurrPos = this->GetEncoderPos(nUnit, nAxis);

	this->MoveAxis(nUnit, nAxis, REL, dPos, g_clSysData.m_dMotorSpeed[nUnit][nAxis]);

	dwTickCount = GetTickCount();
	while (1)
	{
		if (this->GetStopAxis(nUnit, nAxis))
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > AXIS_MOVE_TIME)
		{
			return false;
		}
		
		Sleep(10);
	}

	return true;
}

bool CAxlMotorSet::MovePcbDispenseStraightLineMotor(int nUnit, int nAxis, int nAbsFlag, double dPos, double dVel, double dAcc, bool bWait)
{
	// abs 1:absolute, 0:increment
#ifndef ON_LINE_MOTOR
	return true;
#endif
	return true;
}

//-----------------------------------------------------------------------------
//
//	지정 축을 절대 구동 또는 상대 구동으로 이동한다. 
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveAxis(int nUnit, int nAxis, int nAbsFlag, double dPos, double dVel, bool bWait)
{
	// abs 1:absolute, 0:increment
#ifndef ON_LINE_MOTOR
	return true;
#endif

	TCHAR szLog[SIZE_OF_1K];
	double dCurrPos = 0.0;
	double dAcc = 0.0;
	double dDec = 0.0;
	static DWORD dwTickCount;
	int nUseAxis = 0;
	int nStep = 100;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;

	if (this->GetAmpFault(nUnit, nAxis))
	{
		m_bOrgFlag[nUnit][nAxis] = false;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 AMP ALARM 발생. MoveAxis 동작 실패"), MOTOR_NAME[nAxis]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if (!this->GetAmpEnable(nUnit, nAxis))
	{
		m_bOrgFlag[nUnit][nAxis] = false;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 SERVO OFF 상태 입니다. MoveAxis 동작 실패"), MOTOR_NAME[nAxis]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if (nAbsFlag == ABS)
	{
		if (MOTOR_TYPE[nAxis] == STEPING)
			dCurrPos = GetCommandPos(nUnit, nAxis);
		else
			dCurrPos = GetEncoderPos(nUnit, nAxis);

		if (fabs(dCurrPos - dPos) < 0.0001)
			return true;

		if (m_bOrgFlag[nUnit][nAxis] == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 원점복귀를 먼저 실행하십시오."), MOTOR_NAME[nAxis]);
			AddLog(szLog, 1, nUnit);

			return false;
		}
	}
	else if (nAbsFlag == REL)
	{
		if (MOTOR_TYPE[nAxis] == STEPING)
			dPos += GetCommandPos(nUnit, nAxis);
		else
			dPos += GetEncoderPos(nUnit, nAxis);
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 이동 명령 비정상"), MOTOR_NAME[nAxis]);
		AddLog(szLog, 1, nUnit);

		return false; 
	}  
	//double tempResol = 5000.0;// g_clSysData.m_dMotorResol[nUnit][nAxis];     
	dPos *= g_clSysData.m_dMotorResol[nUnit][nAxis];
	if (dPos > 0)   
		dPos = (int)(dPos + 0.5);    

	//dPos += dCurrPos;

	dVel = dVel * g_clSysData.m_dMotorResol[nUnit][nAxis];	//이동 속도 

#ifdef MOTOR_ACC_TYPE_SEC
	dAcc = g_clSysData.m_dMotorAccTime[nUnit][nAxis];		//! 가속 
	dDec = g_clSysData.m_dMotorDecTime[nUnit][nAxis];		//! 감속
#else
													/*가속도 단위 (G)
													-> 9.8m/s^2  X 1000mm/m   X   2000plses/mm     =      pls/s^2   */
	dAcc = g_clSysData.m_dMotorAccTime[nUnit][nAxis] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis]);		//! 가속 
	dDec = g_clSysData.m_dMotorDecTime[nUnit][nAxis] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis]);		//! 감속
#endif

	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.
	AxmMoveStartPos(MOTOR_AXIS_NUMBER[nUseAxis], dPos, dVel, dAcc, dDec);//z축 작동한다.



	if(bWait == false)
		return true;

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
		case 100:
			if ((this->GetStopAxis(nUnit, nAxis) == true) && ((this->GetEncoderPos(nUnit, nAxis) - dPos) < ENCORDER_GAP))
			{
				dwTickCount = GetTickCount();
				nStep = 200;
			}
			break;
		default:
			break;
		}

		if (nStep >= 200)
			break;

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			return false;
		}

		Sleep(10);
	}

	return true;
}
//-----------------------------------------------------------------------------
//
//	직선 , 곡선 정지없이 연속 도포
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveStraightPcbXYAxis(int nUnit)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif
	if ((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;
#if 0
	TCHAR szLog[SIZE_OF_1K];
	long MOTOR_DIR = DIR_CW;
	long   axisAll[2] = { 0, };
	double posAll[2] = { 0, };
	double velAll[1] = { 0, };
	double accAll[1] = { 0, };
	double decAll[1] = { 0, };



	double dAngle = 0.0;
	double CircleSpeed = 0.0;
	double TrinityCircleRadius = 0.0;
	double dPos[2];
	double dMidPos[2];
	double dEndPos[2];
	dMidPos[0] = dMidPos[1] = 0.0;
	dEndPos[0] = dEndPos[1] = 0.0;
	dPos[0] = dPos[1] = 0.0;
	int cnt = 2;

	axisAll[0] = (nUnit * MAX_MOTOR_COUNT) + MOTOR_PCB_X;
	axisAll[1] = (nUnit * MAX_MOTOR_COUNT) + MOTOR_PCB_Y;

	velAll[0] = g_clModelData[nUnit].m_EpoxyLineSpeed * g_clSysData.m_dMotorResol[nUnit][axisAll[0]];


#ifdef MOTOR_ACC_TYPE_SEC
	accAll[0] = g_clModelData[nUnit].m_EpoxyLineAccDec;		//! 가속 
	decAll[0] = g_clModelData[nUnit].m_EpoxyLineAccDec;		//! 감속 
#else
	/*가속도 단위 (G)
	-> 9.8m/s^2  X 1000mm/m   X   2000plses/mm     =      pls/s^2   */
	decAll[0] = g_clModelData[nUnit].m_EpoxyLineAccDec * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][axisAll[0]]);		//! 가속 
	accAll[0] = g_clModelData[nUnit].m_EpoxyLineAccDec * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][axisAll[0]]);		//! 감속
#endif
	long  lPosSize = 2;
	long  lCoordinate = 0;

	//AxmMotSetMoveUnitPerPulse(MOTOR_PCB_X, 1, 10000);	//Unit/Pulse 변경 - X 
	//AxmMotSetMoveUnitPerPulse(MOTOR_PCB_Y, 1, 10000);	//					Y 

	 
	AxmContiWriteClear(lCoordinate);
	AxmContiSetAxisMap(lCoordinate, lPosSize, axisAll);

	// 상대위치 구동등록.
	AxmContiSetAbsRelMode(lCoordinate, 1);
	AxmContiBeginNode(lCoordinate);

	int mCircleResol = g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_X];//2000
	//===================================================================================================================================
	//동작 1 
	//하단 가로 직선
	posAll[0] = posAll[1] = 0.0;
	posAll[0] = g_clModelData[nUnit].m_EpoxyLineLength[0] * -1;
	posAll[0] *= g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_X];
	//
	if (posAll[0]>0) posAll[0] = (int)(posAll[0] + 0.5);

	posAll[1] *= g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_Y];


	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);
	//===================================================================================================================================
	//동작 2
	//우측 하단 커브

	CircleSpeed = g_clModelData[nUnit].m_EpoxyCurveSpeed * mCircleResol;// g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_X];
	dMidPos[0] = g_clModelData[nUnit].m_EpoxyCurveCenterXPoint[0] * mCircleResol;
	dMidPos[1] = g_clModelData[nUnit].m_EpoxyCurveCenterYPoint[0] * mCircleResol;
	dEndPos[0] = g_clModelData[nUnit].m_EpoxyCurveEndXPoint[0] * mCircleResol;
	dEndPos[1] = g_clModelData[nUnit].m_EpoxyCurveEndYPoint[0] * mCircleResol;
	MOTOR_DIR = DIR_CW;
	AxmCircleCenterMove(lCoordinate, axisAll, dMidPos, dEndPos, CircleSpeed, accAll[0], decAll[0], MOTOR_DIR);
	//===================================================================================================================================
	//동작 3
	//우측 세로 직선

	posAll[0] = posAll[1] = 0.0;
	posAll[0] *= g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_X];

	posAll[1] = g_clModelData[nUnit].m_EpoxyLineLength[1] * -1;
	posAll[1] *= g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_Y];
	if (posAll[1]>0)					posAll[1] = (int)(posAll[1] + 0.5);

	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);
	//===================================================================================================================================
	//동작 4
	//우측 상단 커브

	CircleSpeed = g_clModelData[nUnit].m_EpoxyCurveSpeed * mCircleResol;// g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_X];
	dMidPos[0] = g_clModelData[nUnit].m_EpoxyCurveCenterXPoint[1] * mCircleResol;
	dMidPos[1] = g_clModelData[nUnit].m_EpoxyCurveCenterYPoint[1] * mCircleResol;
	dEndPos[0] = g_clModelData[nUnit].m_EpoxyCurveEndXPoint[1] * mCircleResol;
	dEndPos[1] = g_clModelData[nUnit].m_EpoxyCurveEndYPoint[1] * mCircleResol; 
	MOTOR_DIR = DIR_CW;
	AxmCircleCenterMove(lCoordinate, axisAll, dMidPos, dEndPos, CircleSpeed, accAll[0], decAll[0], MOTOR_DIR);
	//===================================================================================================================================
	//동작 5 
	//상단 가로 직선

	posAll[0] = posAll[1] = 0.0;
	posAll[0] = g_clModelData[nUnit].m_EpoxyLineLength[2] * 1; 
	posAll[0] *= g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_X];
	//
	if (posAll[0]>0) posAll[0] = (int)(posAll[0] + 0.5);
	posAll[1] *= g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_Y];


	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);
	//===================================================================================================================================
	//동작 6
	//좌측 상단 커브

	CircleSpeed = g_clModelData[nUnit].m_EpoxyCurveSpeed *mCircleResol;//g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_X];
	dMidPos[0] = g_clModelData[nUnit].m_EpoxyCurveCenterXPoint[2] * mCircleResol;
	dMidPos[1] = g_clModelData[nUnit].m_EpoxyCurveCenterYPoint[2] * mCircleResol;
	dEndPos[0] = g_clModelData[nUnit].m_EpoxyCurveEndXPoint[2] * mCircleResol;
	dEndPos[1] = g_clModelData[nUnit].m_EpoxyCurveEndYPoint[2] * mCircleResol;
	MOTOR_DIR = DIR_CW;
	AxmCircleCenterMove(lCoordinate, axisAll, dMidPos, dEndPos, CircleSpeed, accAll[0], decAll[0], MOTOR_DIR);
	//===================================================================================================================================
	//동작 7 
	//좌측 세로 직선

	posAll[0] = posAll[1] = 0.0;
	posAll[0] *= g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_X];

	posAll[1] = g_clModelData[nUnit].m_EpoxyLineLength[3] * 1;
	posAll[1] *= g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_Y];
	if (posAll[1]>0)					posAll[1] = (int)(posAll[1] + 0.5);

	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);
	//===================================================================================================================================
	//동작 8
	//좌측 하단 커브


	CircleSpeed = g_clModelData[nUnit].m_EpoxyCurveSpeed *mCircleResol;//g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_X]; 
	dMidPos[0] = g_clModelData[nUnit].m_EpoxyCurveCenterXPoint[3] * mCircleResol;
	dMidPos[1] = g_clModelData[nUnit].m_EpoxyCurveCenterYPoint[3] * mCircleResol;
	dEndPos[0] = g_clModelData[nUnit].m_EpoxyCurveEndXPoint[3] * mCircleResol; 
	dEndPos[1] = g_clModelData[nUnit].m_EpoxyCurveEndYPoint[3] * mCircleResol;
	MOTOR_DIR = DIR_CW;
	AxmCircleCenterMove(lCoordinate, axisAll, dMidPos, dEndPos, CircleSpeed, accAll[0], decAll[0], MOTOR_DIR);
	//===================================================================================================================================

	//===================================================================================================================================
	//동작 9 
	//도포후 라인
	posAll[0] = posAll[1] = 0.0;
	posAll[0] = -0.4;// (g_clModelData[nUnit].m_EpoxyLineLength[0] / 4) * -1; 
	posAll[0] *= g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_X];
	//
	if (posAll[0]>0) posAll[0] = (int)(posAll[0] + 0.5);

	posAll[1] *= g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_Y];


	AxmLineMove(lCoordinate, posAll, velAll[0], accAll[0], decAll[0]);  

	//===================================================================================================================================
	AxmContiEndNode(lCoordinate);
	// 상대위치 구동시작.
	AxmContiSetAbsRelMode(lCoordinate, 1);
	// 연속보간구동 시작.
	AxmContiStart(lCoordinate, 0, 0);

	Sleep(10);
#endif
	return true;
}
//-----------------------------------------------------------------------------
//
//	지정 축을 절대 구동 또는 상대 구동으로 이동한다. 
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveCirclePcbXYAxis(int nUnit, int dPos)//, double dAngle, double dVel, double dAcc)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif
#if 0
	TCHAR szLog[SIZE_OF_1K];
	long MOTOR_DIR = DIR_CW;
	long   lAxisAll[2] = { 0, };
	double dPosAll[1] = { 0.0 };
	double dVelAll[1] = { 0.0 };
	double dAccAll[1] = { 0.0 };
	double dDecAll[1] = { 0.0 };
	double dCurrPos = 0.0;
	int nUseAxis = 0;
	

	if ((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;
	for (int nAxis = 0; nAxis <= MOTOR_PCB_Y; nAxis++)
	{
		// abs 1:absolute, 0:increment
		if (this->GetAmpFault(nUnit, nAxis))
		{
			m_bOrgFlag[nUnit][nAxis] = false;

			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] AMP ALARM 발생. MoveAxis 동작 실패"), MOTOR_NAME[nAxis]);
			AddLog(szLog, 1, nUnit);

			return false;
		}

		if (!this->GetAmpEnable(nUnit, nAxis))
		{
			m_bOrgFlag[nUnit][nAxis] = false;

			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] SERVO OFF 발생. MoveAxis 동작 실패"), MOTOR_NAME[nAxis]);
			AddLog(szLog, 1, nUnit);

			return false;
		}
	}

	lAxisAll[0] = (nUnit * MAX_MOTOR_COUNT) + MOTOR_PCB_X;
	lAxisAll[1] = (nUnit * MAX_MOTOR_COUNT) + MOTOR_PCB_Y;
//#ifdef MOTOR_ACC_TYPE_SEC
//	dAccAll[0] = g_clModelData[nUnit].m_EpoxyCurveAccDec;//	dAcc;		//! 가속 
//	dDecAll[0] = g_clModelData[nUnit].m_EpoxyCurveAccDec;//dAcc;		//! 감속
//#else
//	/*가속도 단위 (G)
//	-> 9.8m/s^2  X 1000mm/m   X   2000plses/mm     =      pls/s^2   */
//	dAccAll[0] = g_clModelData[nUnit].m_EpoxyCurveAccDec * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_X]);		//! 가속 
//	dDecAll[0] = g_clModelData[nUnit].m_EpoxyCurveAccDec * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_Y]);		//! 감속
//#endif
//
//	dVelAll[0] = g_clModelData[nUnit].m_EpoxyCurveSpeed * g_clSysData.m_dMotorResol[nUnit][MOTOR_PCB_X];	//이동 속도 



	dAccAll[0] = g_clModelData[nUnit].m_EpoxyCurveAccDec;		//! 가속 
	dDecAll[0] = g_clModelData[nUnit].m_EpoxyCurveAccDec;		//! 감속

	dVelAll[0] = g_clModelData[nUnit].m_EpoxyCurveSpeed;//이동 속도 

	


	//지정된 좌표계에 시작점, 회전각도와 반지름을 지정하여 원호 보간 하는 함수이다.구동 시작 후 함수를 벗어난다.
	double dCenterPos[2];
	double dEndPos[2];

	if (dPos < E_RIGHT_DOWN_SITE || dPos >= MAX_EPOXY_POSITION_TYPE)
	{
		return false;
	}

	dCenterPos[0] = g_clModelData[nUnit].m_EpoxyCurveCenterXPoint[dPos];
	dCenterPos[1] = g_clModelData[nUnit].m_EpoxyCurveCenterYPoint[dPos];
	dEndPos[0] = g_clModelData[nUnit].m_EpoxyCurveEndXPoint[dPos]; 
	dEndPos[1] = g_clModelData[nUnit].m_EpoxyCurveEndYPoint[dPos];
	switch (dPos)
	{
	case E_RIGHT_DOWN_SITE:
		MOTOR_DIR = DIR_CW;//DIR_CW; = 모터자체가 시계방향으로 회전		//DIR_CCW
		break;
	case E_RIGHT_UP_SITE:
		MOTOR_DIR = DIR_CW;
		break;
	case E_LEFT_UP_SITE:
		MOTOR_DIR = DIR_CW; 
		break;
	case E_LEFT_DOWN_SITE:
		MOTOR_DIR = DIR_CW;
		break;
	default:
		MOTOR_DIR = DIR_CW;  
		break; 
	}

	AxmMotSetMoveUnitPerPulse(MOTOR_PCB_X, 1, 10000);	//Unit/Pulse 변경 - X  
	AxmMotSetMoveUnitPerPulse(MOTOR_PCB_Y, 1, 10000);	//					Y  

	Sleep(10);
	long lCoordinate = 0;
	long lPosSize = 2;
	DWORD uAbsRelMode = 1;


	AxmContiWriteClear(lCoordinate);
	AxmContiSetAxisMap(lCoordinate, lPosSize, lAxisAll);  
	AxmContiSetAbsRelMode(lCoordinate, uAbsRelMode);   // 1 = 상대위치구동.  
	Sleep(10);
	DWORD dwReturn = 0;
	dwReturn = AxmCircleCenterMove(lCoordinate, lAxisAll, dCenterPos, dEndPos, dVelAll[0], dAccAll[0], dDecAll[0], MOTOR_DIR);
	//dwReturn = AxmCircleAngleMove(lCoordinate, lAxisAll, dCenterPos, 90, dVelAll[0], dAccAll[0], dDecAll[0], MOTOR_DIR); 
	int nStep = 0;
	DWORD dwTickCount;
	while (true)
	{
		switch (nStep)
		{
		case 0:
			nStep = 100;
			dwTickCount = GetTickCount();
			break;
		case 100:
			if (GetStopAxis(nUnit, MOTOR_PCB_X) == true && GetStopAxis(nUnit, MOTOR_PCB_Y) == true)
			{

				nStep = 200;
			}
			break;
		case 200:
			AxmMotSetMoveUnitPerPulse(MOTOR_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
			AxmMotSetMoveUnitPerPulse(MOTOR_PCB_Y, 1, 1); 
			nStep = 900;
			break;
		default:
			break;
		}

		if (nStep == 900)		break;
		if ((GetTickCount() - dwTickCount) > 60000 * 3)
		{
			StopAxis(nUnit, MOTOR_PCB_X);
			StopAxis(nUnit, MOTOR_PCB_Y);

			AxmMotSetMoveUnitPerPulse(MOTOR_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
			AxmMotSetMoveUnitPerPulse(MOTOR_PCB_Y, 1, 1);
			return false;
		}
			
		Sleep(10);
	}

	

#endif
	return true;
}
//-----------------------------------------------------------------------------
//
//	지정 축을 절대 구동 또는 상대 구동으로 이동한다. 
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveAxis(int nUnit, int nAxis, int nAbsFlag, double dPos, double dVel, double dAcc)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	TCHAR szLog[SIZE_OF_1K];
	double dPosAll[1] = { 0.0 };
	double dVelAll[1] = { 0.0 };
	double dAccAll[1] = { 0.0 };
	double dDecAll[1] = { 0.0 };
	double dCurrPos = 0.0;
	int nUseAxis = 0;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;
	
	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;

	// abs 1:absolute, 0:increment
	if (this->GetAmpFault(nUnit, nAxis))
	{
		m_bOrgFlag[nUnit][nAxis] = false;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] AMP ALARM 발생. MoveAxis 동작 실패"), MOTOR_NAME[nAxis]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if (!this->GetAmpEnable(nUnit, nAxis))
	{
		m_bOrgFlag[nUnit][nAxis] = false;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] SERVO OFF 발생. MoveAxis 동작 실패"), MOTOR_NAME[nAxis]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if (nAbsFlag == ABS)
	{
		if (MOTOR_TYPE[nAxis] == STEPING)
			dCurrPos = this->GetCommandPos(nUnit, nAxis);
		else
			dCurrPos = this->GetEncoderPos(nUnit, nAxis);

		if (fabs(dCurrPos - dPos) < 0.0001)
			return true;

		if (m_bOrgFlag[nUnit][nAxis] == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터  원점 복귀가 되지 않았습니다."), MOTOR_NAME[nAxis]);
			AddLog(szLog, 1, nUnit);

			return false;
		}
	}
	else if (nAbsFlag == REL)
	{
		if (MOTOR_TYPE[nAxis] == STEPING)
			dPos += GetCommandPos(nUnit, nAxis);
		else
			dPos += GetEncoderPos(nUnit, nAxis);
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 이동 명령 비정상."), MOTOR_NAME[nAxis]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	dPos *= g_clSysData.m_dMotorResol[nUnit][nAxis];
	if (dPos > 0)
		dPos = (int)(dPos + 0.5);

	dPosAll[0] = dPos;
	dVelAll[0] = dVel * g_clSysData.m_dMotorResol[nUnit][nAxis];	//이동 속도

#ifdef MOTOR_ACC_TYPE_SEC
	dAccAll[0] = dAcc;		//! 가속 
	dDecAll[0] = dAcc;		//! 감속
#else
															/*가속도 단위 (G)
															-> 9.8m/s^2  X 1000mm/m   X   2000plses/mm     =      pls/s^2   */
	dAccAll[0] = dAcc * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis]);		//! 가속 
	dDecAll[0] = dAcc * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis]);		//! 감속
#endif

	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.
	AxmMoveStartPos(MOTOR_AXIS_NUMBER[nUseAxis], dPos, dVelAll[0], dAccAll[0], dDecAll[0]);

	return true;
}

//-----------------------------------------------------------------------------
//
//	지정 축을 절대 구동 또는 상대 구동으로 이동한다. 
//
//-----------------------------------------------------------------------------
//bool CAxlMotorSet::MoveAxis(int nAxis, int nAbsFlag, double dPos, double dVel, bool bWait/* = true*/)
//{
//	// abs 1:absolute, 0:increment
//#ifndef ON_LINE_MOTOR
//	return true;
//#endif
//
//	char szLog[SIZE_OF_1K];
//	static DWORD dwTickCount;
//	double dCurrPos;
//	double dAcc;
//	double dDec;
//	int nStep;
//
//	if (nAxis < 0 || nAxis >= MAX_MOTOR_COUNT)
//		return false;
//
//	dCurrPos = 0.0;
//	dAcc = dDec = 0.0;
//
//	if (GetAmpFault(nAxis))
//	{
//		m_bOrgFlag[nAxis] = false;
//
//		sprintf_s(szLog, SIZE_OF_1K, "[%s] 모터 AMP ALARM 발생. MoveAxis 동작 실패", g_szMotorName[nAxis]);
//		g_AddListLog(szLog);
//
//		return false;
//	}
//
//	if (!GetAmpEnable(nAxis))
//	{
//		m_bOrgFlag[nAxis] = false;
//
//		sprintf_s(szLog, SIZE_OF_1K, "[%s] 모터 SERVO OFF 상태 입니다. MoveAxis 동작 실패", g_szMotorName[nAxis]);
//		g_AddListLog(szLog);
//
//		return false;
//	}
//
//	if (nAbsFlag == ABS)
//	{
//		if (MOTOR_TYPE[nAxis] == STEPING)
//			dCurrPos = GetCommandPos(nAxis);
//		else
//			dCurrPos = GetEncoderPos(nAxis);
//
//		if (fabs(dCurrPos - dPos) < 0.0001)
//			return true;
//
//		if (m_bOrgFlag[nAxis] == false)
//		{
//			sprintf_s(szLog, SIZE_OF_1K, "[%s] 모터 원점복귀를 먼저 실행하십시오.", g_szMotorName[nAxis]);
//			g_AddListLog(szLog);
//
//			return false;
//		}
//	}
//	else if (nAbsFlag == REL)
//	{
//		if (MOTOR_TYPE[nAxis] == STEPING)
//			dPos += GetCommandPos(nAxis);
//		else
//			dPos += GetEncoderPos(nAxis);
//	}
//	else
//	{
//		sprintf_s(szLog, SIZE_OF_1K, "[%s] 모터 이동 명령 비정상", g_szMotorName[nAxis]);
//		g_AddListLog(szLog);
//
//		return false;
//	}
//
//	dPos *= g_clSysData.m_dMotorResol[nAxis];
//	if (dPos > 0)
//		dPos = (int)(dPos + 0.5);
//
//	dPos += dCurrPos;
//
//	dVel = dVel * g_clSysData.m_dMotorResol[nAxis];	//이동 속도
//
//#ifdef MOTOR_ACC_TYPE_SEC
//	dAcc = g_clSysData.m_dMotorAccTime[nAxis];		//! 가속 
//	dDec = g_clSysData.m_dMotorDecTime[nAxis];		//! 감속
//#else
//	/*가속도 단위 (G)
//	-> 9.8m/s^2  X 1000mm/m   X   2000plses/mm     =      pls/s^2   */
//	dAcc = g_clSysData.m_dMotorAccTime[nAxis] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nAxis]);		//! 가속 
//	dDec = g_clSysData.m_dMotorDecTime[nAxis] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nAxis]);		//! 감속
//#endif
//
//	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
//	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
//	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
//	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.
//	AxmMoveStartPos(nAxis, dPos, dVel, dAcc, dDec);
//	
//	if (bWait == true)
//	{
//		nStep = 100;
//		dwTickCount = GetTickCount();
//
//		while (1)
//		{
//			switch (nStep)
//			{
//			case 100:
//				TRACE("%lf %lf\n", this->GetEncoderPos(nAxis), dPos);
//				if ((this->GetStopAxis(nAxis) == true) && ((this->GetEncoderPos(nAxis) - (dPos / g_clSysData.m_dMotorResol[nAxis])) < ENCORDER_GAP))
//				{
//					nStep = 200;
//				}
//				break;
//			default:
//				break;
//			}
//
//			if (nStep < 0)
//			{
//				return false;
//			}
//
//			if (nStep >= 200)
//			{
//				break;
//			}
//
//			if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
//			{
//				return false;
//			}
//
//			Sleep(10);
//		}
//	}
//
//	return true;
//}

//-----------------------------------------------------------------------------
//
//	지정 축을 절대 구동 또는 상대 구동으로 이동한다. 
//
//-----------------------------------------------------------------------------
//bool CAxlMotorSet::MoveAxisComplete(int nAxis, int nAbsFlag, double dPos, double dVel, bool bWait/* = true*/)
bool CAxlMotorSet::MoveAxisComplete(int nUnit, int nAxis, int nAbsFlag, double dPos, double dVel, int nSpeed, bool bWait/* = true*/, double dParamAcc/* = 0.0*/, double dParamDec/* = 0.0*/) //20161101
{
	// abs 1:absolute, 0:increment
#ifndef ON_LINE_MOTOR
	return true;
#endif

	static DWORD dwTickCount;
	TCHAR szLog[SIZE_OF_1K];
	double dCurrPos = 0.0;
	double dAcc = 0.0;
	double dDec = 0.0;	
	int nRetStep;
	int nUseAxis = 0;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;

	if (this->GetAmpFault(nUnit, nAxis))
	{
		m_bOrgFlag[nUnit][nAxis] = false;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 AMP ALARM 발생. MoveAxis 동작 실패"), MOTOR_NAME[nAxis]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if (!this->GetAmpEnable(nUnit, nAxis))
	{
		m_bOrgFlag[nUnit][nAxis] = false;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 SERVO OFF 상태 입니다. MoveAxis 동작 실패"), MOTOR_NAME[nAxis]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if (nAbsFlag == ABS)
	{
		//if (MOTOR_TYPE[nAxis] == STEPING)
		//	dCurrPos = this->GetCommandPos(nUnit, nAxis);
		//else
			dCurrPos = this->GetEncoderPos(nUnit, nAxis);

		if (fabs(dCurrPos - dPos) < 0.0001)
			return true;

		if (m_bOrgFlag[nUnit][nAxis] == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 원점복귀를 먼저 실행하십시오."), MOTOR_NAME[nAxis]);
			AddLog(szLog, 1, nUnit);

			return false;
		}
	}
	else if (nAbsFlag == REL)
	{
		//if (MOTOR_TYPE[nAxis] == STEPING)
		//	dPos += this->GetCommandPos(nUnit, nAxis);
		//else
			dPos += this->GetEncoderPos(nUnit, nAxis);
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 이동 명령 비정상"), MOTOR_NAME[nAxis]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	dPos *= g_clSysData.m_dMotorResol[nUnit][nAxis];
	if (dPos > 0)
		dPos = (int)(dPos + 0.5);

	//dPos += dCurrPos;

	if ((dParamAcc == 0.0) && (dParamDec == 0.0))
	{
		dVel = g_clSysData.m_dMotorSpeed[nUnit][nAxis];
		dVel = dVel * g_clSysData.m_dMotorResol[nUnit][nAxis];	//이동 속도
	}
	else
	{
		dVel = dVel * g_clSysData.m_dMotorResol[nUnit][nAxis];	//이동 속도
	}

#ifdef MOTOR_ACC_TYPE_SEC
	dAcc = g_clSysData.m_dMotorAccTime[nUnit][nAxis];		//! 가속 
	dDec = g_clSysData.m_dMotorDecTime[nUnit][nAxis];		//! 감속
#else
	/*가속도 단위 (G)
	-> 9.8m/s^2  X 1000mm/m   X   2000plses/mm     =      pls/s^2   */
	if ((dParamAcc == 0.0) && (dParamDec == 0.0))
	{
		dAcc = g_clSysData.m_dMotorAccTime[nUnit][nAxis] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis]);		//! 가속 
		dDec = g_clSysData.m_dMotorDecTime[nUnit][nAxis] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis]);		//! 감속
	}
	else
	{
		dAcc = dParamAcc * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis]);		//! 가속 
		dDec = dParamDec * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis]);		//! 감속
	}
#endif

	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.
	AxmMoveStartPos(MOTOR_AXIS_NUMBER[nUseAxis], dPos, dVel, dAcc, dDec);

	if (bWait == true)
	{
		dwTickCount = GetTickCount();
		nRetStep = 100;

		while (1)
		{
			switch (nRetStep)
			{
			case 100:
				if ((this->GetStopAxis(nUnit, nAxis) == true) && ((this->GetEncoderPos(nUnit, nAxis) - (dPos / g_clSysData.m_dMotorResol[nUnit][nAxis])) < ENCORDER_GAP))
				{
					nRetStep = 200;
				}
				break;
			default:
				break;
			}

			if (nRetStep < 0)
			{
				return false;
			}

			if (nRetStep >= 200)
			{
				break;
			}

			if ((GetTickCount() - dwTickCount) > AXIS_MOVE_TIME)
			{
				return false;
			}

			Sleep(10);
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
//
//	여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveAxisMulti(int nUnit, int nAxisCnt, int nAxis[MAX_MOTOR_COUNT], double dPos[MAX_MOTOR_COUNT])
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	TCHAR szLog[SIZE_OF_1K];
	long   lAxisAll[MAX_MOTOR_COUNT] = { 0, };
	double dPosAll[MAX_MOTOR_COUNT] = { 0, };
	double dVelAll[MAX_MOTOR_COUNT] = { 0, };
	double dAccAll[MAX_MOTOR_COUNT] = { 0, };
	double dDecAll[MAX_MOTOR_COUNT] = { 0, };
	double dCurrPos = 0.0;
	int nCount;
	int i;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if (nAxisCnt > MAX_MOTOR_COUNT)
		return false;

	for (i = 0, nCount = 0; i < nAxisCnt; i++)
	{
		if (!m_bOrgFlag[nUnit][nAxis[i]])
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 원점 복귀가 되지 않았습니다."), MOTOR_NAME[nAxis[i]]);
			AddLog(szLog, 1, nUnit);

			return false;
		}

		if (!GetStopAxis(nUnit, nAxis[i]))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 동작 중 이동 명령이 호출되었습니다.(MoveAxisMulti)"), MOTOR_NAME[nAxis[i]]);
			AddLog(szLog, 1, nUnit);

			return false;
		}

		if (MOTOR_TYPE[nAxis[i]] == STEPING)
			dCurrPos = GetCommandPos(nUnit, nAxis[i]);
		else
			dCurrPos = GetEncoderPos(nUnit, nAxis[i]);


		//! Motor의 이동 목표 위치, 속도, 가속도/감속도 등을 알아낸다.   MOTOR_AXIS_NUMBER
		lAxisAll[nCount] = MOTOR_AXIS_NUMBER[(nUnit * MAX_MOTOR_COUNT) + nAxis[i]];// (nUnit * MAX_MOTOR_COUNT) + nAxis[i];
		dPosAll[nCount] = dPos[i] * g_clSysData.m_dMotorResol[nUnit][nAxis[i]];
		dVelAll[nCount] = g_clSysData.m_dMotorSpeed[nUnit][nAxis[i]] * g_clSysData.m_dMotorResol[nUnit][nAxis[i]];

		// 이동할 위치에서 5um 이상 차이가 없을때는 움직이지 않음.
		if (fabs(dPosAll[nCount] - dCurrPos) < 0.005)
			continue;

#ifdef MOTOR_ACC_TYPE_SEC
		dAccAll[nCount] = g_clSysData.m_dMotorAccTime[nUnit][nAxis[i]];	//! 가속도
		dDecAll[nCount] = g_clSysData.m_dMotorDecTime[nUnit][nAxis[i]];	//! 감속도
#else
		/*가속도 단위 (G)
		-> 9.8m/s^2  X 1000mm/m   X   2000plses/mm     =      pls/s^2   */
		dAccAll[nCount] = g_clSysData.m_dMotorAccTime[nUnit][nAxis[i]] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis[i]]);//! 가속도 
		dDecAll[nCount] = g_clSysData.m_dMotorDecTime[nUnit][nAxis[i]] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis[i]]);//! 감속도
#endif

		nCount++;
	}

	//이동 범위가 없을 경우 Return
	if (nCount == 0)
		return true;

	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.
	AxmMoveStartMultiPos(nCount, lAxisAll, dPosAll, dVelAll, dAccAll, dDecAll);

	return true;
}


//-----------------------------------------------------------------------------
//
//	여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveAxisMulti(int nUnit, int nAxisCnt, int nAxis[MAX_MOTOR_COUNT], double dPos[MAX_MOTOR_COUNT], int nSpeed)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	TCHAR szLog[SIZE_OF_1K];
	long   lAxisAll[MAX_MOTOR_COUNT] = { 0, };
	double dPosAll[MAX_MOTOR_COUNT] = { 0, };
	double dVelAll[MAX_MOTOR_COUNT] = { 0, };
	double dAccAll[MAX_MOTOR_COUNT] = { 0, };
	double dDecAll[MAX_MOTOR_COUNT] = { 0, };
	double dCurrPos = 0.0;
	int nCount;
	int i;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if (nAxisCnt > MAX_MOTOR_COUNT)
		return false;

	for (i = 0, nCount = 0; i < nAxisCnt; i++)
	{
		if (!m_bOrgFlag[nUnit][nAxis[i]])
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 원점 복귀가 되지 않았습니다."), MOTOR_NAME[nAxis[i]]);
			AddLog(szLog, 1, nUnit);

			return false;
		}

		if (!GetStopAxis(nUnit, nAxis[i]))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 동작 중 이동 명령이 호출되었습니다.(MoveAxisMulti)"), MOTOR_NAME[nAxis[i]]);
			AddLog(szLog, 1, nUnit);

			return false;
		}

		if (MOTOR_TYPE[nAxis[i]] == STEPING)
			dCurrPos = GetCommandPos(nUnit, nAxis[i]);
		else
			dCurrPos = GetEncoderPos(nUnit, nAxis[i]);


		//! Motor의 이동 목표 위치, 속도, 가속도/감속도 등을 알아낸다. 
		lAxisAll[nCount] = (nUnit * MAX_MOTOR_COUNT) + nAxis[i];
		dPosAll[nCount] = dPos[i] * g_clSysData.m_dMotorResol[nUnit][nAxis[i]];
		dVelAll[nCount] = g_clSysData.m_dMotorSpeed[nUnit][nAxis[i]] * g_clSysData.m_dMotorResol[nUnit][nAxis[i]];

		// 이동할 위치에서 5um 이상 차이가 없을때는 움직이지 않음.
		if (fabs(dPosAll[nCount] - dCurrPos) < 0.005)
			continue;

#ifdef MOTOR_ACC_TYPE_SEC
		dAccAll[nCount] = g_clSysData.m_dMotorAccTime[nUnit][nAxis[i]];	//! 가속도
		dDecAll[nCount] = g_clSysData.m_dMotorDecTime[nUnit][nAxis[i]];	//! 감속도
#else
		/*가속도 단위 (G)
		-> 9.8m/s^2  X 1000mm/m   X   2000plses/mm     =      pls/s^2   */
		dAccAll[nCount] = g_clSysData.m_dMotorAccTime[nUnit][nAxis[i]] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis[i]]);//! 가속도 
		dDecAll[nCount] = g_clSysData.m_dMotorDecTime[nUnit][nAxis[i]] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis[i]]);//! 감속도
#endif

		nCount++;
	}

	//이동 범위가 없을 경우 Return
	if (nCount == 0)
		return true;

	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.
	AxmMoveStartMultiPos(nCount, lAxisAll, dPosAll, dVelAll, dAccAll, dDecAll);

	return true;
}

//-----------------------------------------------------------------------------
//
//	여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveAxisMulti(int nUnit, int nAxisCnt, int nAxis[MAX_MOTOR_COUNT], double dPos[MAX_MOTOR_COUNT], double dSpeed)
{
	TCHAR szLog[SIZE_OF_1K];
	long lAxisAll[MAX_MOTOR_COUNT] = { 0, };
	double dPosAll[MAX_MOTOR_COUNT] = { 0, };
	double dVelAll[MAX_MOTOR_COUNT] = { 0, };
	double dAccAll[MAX_MOTOR_COUNT] = { 0, };
	double dDecAll[MAX_MOTOR_COUNT] = { 0, };
	double dCurrPos = 0.0;
	int nCount;
	int i;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if (nAxisCnt > MAX_MOTOR_COUNT)
		return false;

	for (i = 0, nCount = 0; i < nAxisCnt; i++)
	{
		if (!m_bOrgFlag[nUnit][nAxis[i]])
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 원점복귀가 되지 않았습니다."), MOTOR_NAME[nAxis[i]]);
			AddLog(szLog, 1, nUnit);

			return false;
		}

		if (!GetStopAxis(nUnit, nAxis[i]))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 동작 중 이동 명령이 호출되었습니다.(MoveAxisMulti)"), MOTOR_NAME[nAxis[i]]);
			AddLog(szLog, 1, nUnit);

			return false;
		}

		if (MOTOR_TYPE[nAxis[i]] == STEPING)
			dCurrPos = GetCommandPos(nUnit, nAxis[i]);
		else
			dCurrPos = GetEncoderPos(nUnit, nAxis[i]);

		//! Motor의 이동 목표 위치, 속도, 가속도/감속도 등을 알아낸다. 
		lAxisAll[nCount] = (nUnit * MAX_MOTOR_COUNT) + nAxis[i];
		dPosAll[nCount] = dPos[i] * g_clSysData.m_dMotorResol[nUnit][nAxis[i]];
		dVelAll[nCount] = dSpeed * g_clSysData.m_dMotorResol[nUnit][nAxis[i]];

		// 이동할 위치에서 5um 이상 차이가 없을때는 움직이지 않음.
		if (fabs(dPosAll[nCount] - dCurrPos) < 0.005)
			continue;

#ifdef MOTOR_ACC_TYPE_SEC
		dAccAll[nCount] = g_clSysData.m_dMotorAccTime[nUnit][nAxis[i]];	//! 가속도
		dDecAll[nCount] = g_clSysData.m_dMotorDecTime[nUnit][nAxis[i]];	//! 감속도
#else
		/*가속도 단위 (G)
		-> 9.8m/s^2  X 1000mm/m   X   2000plses/mm     =      pls/s^2   */
		dAccAll[nCount] = g_clSysData.m_dMotorAccTime[nUnit][nAxis[i]] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis[i]]);//! 가속도 
		dDecAll[nCount] = g_clSysData.m_dMotorDecTime[nUnit][nAxis[i]] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis[i]]);//! 감속도
#endif
		nCount++;
	}

	//이동 범위가 없을 경우 Return
	if (nCount == 0)
		return true;

	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.
	AxmMoveStartMultiPos(nCount, lAxisAll, dPosAll, dVelAll, dAccAll, dDecAll);

	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveAxisMulti(int nUnit, int nAxisCnt, int nAxis[MAX_MOTOR_COUNT], double dPos[MAX_MOTOR_COUNT], double dVel[MAX_MOTOR_COUNT], double dAcc[MAX_MOTOR_COUNT], double dDec[MAX_MOTOR_COUNT])
{
	TCHAR szLog[SIZE_OF_1K];
	long lAxisAll[MAX_MOTOR_COUNT] = { 0, };
	double dPosAll[MAX_MOTOR_COUNT] = { 0, };
	double dVelAll[MAX_MOTOR_COUNT] = { 0, };
	double dAccAll[MAX_MOTOR_COUNT] = { 0, };
	double dDecAll[MAX_MOTOR_COUNT] = { 0, };
	double dCurrPos = 0;
	int nCount;
	int i;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if (nAxisCnt > MAX_MOTOR_COUNT)
		return false;

	for (i = 0, nCount = 0; i < nAxisCnt; i++)
	{
		if (!m_bOrgFlag[nUnit][nAxis[i]])
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 원점복귀가 되지 않았습니다."), MOTOR_NAME[nAxis[i]]);
			AddLog(szLog, 1, nUnit);

			return false;
		}

		if (!GetStopAxis(nUnit, nAxis[i]))
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 동작 중 이동 명령이 호출되었습니다.(MoveAxisMulti)"), MOTOR_NAME[nAxis[i]]);
			AddLog(szLog, 1, nUnit);

			return false;
		}

		if (MOTOR_TYPE[nAxis[i]] == STEPING)
			dCurrPos = GetCommandPos(nUnit, nAxis[i]);
		else
			dCurrPos = GetEncoderPos(nUnit, nAxis[i]);

		//! Motor의 이동 목표 위치, 속도, 가속도/감속도 등을 알아낸다. 
		lAxisAll[nCount] = (nUnit * MAX_MOTOR_COUNT) + nAxis[i];
		dPosAll[nCount] = dPos[i] * g_clSysData.m_dMotorResol[nUnit][nAxis[i]];
		dVelAll[nCount] = dVel[i] * g_clSysData.m_dMotorResol[nUnit][nAxis[i]];

		// 이동할 위치에서 5um 이상 차이가 없을때는 움직이지 않음.
		if (fabs(dPosAll[nCount] - dCurrPos) < 0.005)
			continue;

#ifdef MOTOR_ACC_TYPE_SEC
		dAccAll[nCount] = dAcc[i];	//! 가속도
		dDecAll[nCount] = dDec[i];	//! 감속도
#else
		/*가속도 단위 (G)
		-> 9.8m/s^2  X 1000mm/m   X   2000plses/mm     =      pls/s^2   */
		//dAccAll[nCount] = dAcc[nAxis[i]] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nAxis[i]]);//! 가속도 
		//dDecAll[nCount] = dDec[nAxis[i]] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nAxis[i]]);//! 감속도
		dAccAll[nCount] = dAcc[i] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis[i]]);//! 가속도 
		dDecAll[nCount] = dDec[i] * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis[i]]);//! 감속도
#endif
		nCount++;
	}

	//이동 범위가 없을 경우 Return
	if (nCount == 0)
		return true;

	//! 여러 개의 축에 대해서 현재의 위치에서 지정한 거리만큼 이동을 동시에 시작한다. 
	//! 이 함수를 사용하면 여러 개의 축이 동시에 작업을 시작한다. 
	//! 이 함수는 여러 축이 동기를 맞추어 작업을 시작해야 하는 경우에 사용한다. 
	//! 펄스 출력이 시작되는 시점에서 함수를 벗어난다.
	AxmMoveStartMultiPos(nCount, lAxisAll, dPosAll, dVelAll, dAccAll, dDecAll);

	return true;
}

//-----------------------------------------------------------------------------
//
//	+/- Limit신호가 들어올때까지 축 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveAxisLimit(int nUnit, int nAxis, double dVel, double dAcc, int nLimit, int nSignal, int nStopMode)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	TCHAR szLog[SIZE_OF_1K];
	DWORD dwRetVal = 0;
	int nUseAxis = 0;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;

	dVel = dVel * g_clSysData.m_dMotorResol[nUnit][nAxis];
	
#ifndef MOTOR_ACC_TYPE_SEC
	/*가속도 단위 (G)
	-> 9.8m/s^2  X 1000mm/m   X   2000plses/mm     =      pls/s^2   */
	dAcc = dAcc * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis]);//! 가속도 	
#endif

	dwRetVal = AxmMoveSignalSearch(MOTOR_AXIS_NUMBER[nUseAxis], dVel, dAcc, nLimit, nSignal, nStopMode);
	if (dwRetVal != AXT_RT_SUCCESS)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 Limit 위치 이동 실패"), MOTOR_NAME[nAxis]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// MOTOR HOME 관련

//-----------------------------------------------------------------------------
//
//	Home 검색 작업 결과 문자열을 알아낸다. 
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::GetResultHomeSearch(int nUnit, int nAxis, CString &szResult)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	DWORD dwHomeResult = 0;
	int nUseAxis = 0;
	bool bRetVal = false;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	AxmHomeGetResult(MOTOR_AXIS_NUMBER[nUseAxis], &dwHomeResult);

	switch (dwHomeResult)
	{
	case HOME_SUCCESS:
		szResult = _T("원점 검색이 성공적으로 종료 됐을 경우");
		bRetVal = true;
		break;
	case HOME_SEARCHING:
		szResult = _T("현재 원점검색이 진행중일 경우");
		break;
	case HOME_ERR_GNT_RANGE:
		szResult = _T("겐트리 구동축의 Master축과 Slave축의 원점검색 결과가 설정한 OffsetRange를 벗어났을경우");
		break;
	case HOME_ERR_USER_BREAK:
		szResult = _T("원점 검색중 사용자가 정지 명령을 실행했을 경우");
		break;
	case HOME_ERR_VELOCITY:
		szResult = _T("원점 검색의 속도 설정 값 중 한 개라도 0보다 작거나 같을경우");
		break;
	case HOME_ERR_AMP_FAULT:
		szResult = _T("원점 검색중 서보팩 알람이 발생할 경우");
		break;
	case HOME_ERR_NEG_LIMIT:
		szResult = _T("(+)방향으로 원점센서 검출 중 (-)리미트 센서가 감지될 경우");
		break;
	case HOME_ERR_POS_LIMIT:
		szResult = _T("(-)방향으로 원점센서 검출 중 (+)리미트 센서가 감지될 경우");
		break;
	case HOME_ERR_NOT_DETECT:
		szResult = _T("원점센서가 감지되지 않을경우");
		break;
	case HOME_ERR_UNKNOWN:
		szResult = _T("알수없는 채널(축) 번호(0 ~ (최대축수 - 1))로 원점검색을 시작하려 했을경우");
		break;
	default:
		szResult = _T("Error");
		break;
	}

	return bRetVal;
}

//-----------------------------------------------------------------------------
//
//! Home검색 상태 확인(0=Fail, 1=Success, 2=Searching)
//
//-----------------------------------------------------------------------------
int CAxlMotorSet::IsCompletedHomeSearch(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return 1;
#endif

	DWORD dwRetVal = 0;
	DWORD dwHomeResult = 0;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return dwRetVal;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return dwRetVal;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	AxmHomeGetResult(MOTOR_AXIS_NUMBER[nUseAxis], &dwHomeResult);

	switch (dwHomeResult)
	{
	case HOME_SEARCHING:		dwRetVal = 2;	break;
	case HOME_SUCCESS:			dwRetVal = 1;	break;
	case HOME_ERR_AMP_FAULT:	dwRetVal = -1;	break;
	case HOME_ERR_NOT_DETECT:	dwRetVal = -2;	break;
	case HOME_ERR_NEG_LIMIT:	dwRetVal = -3;	break;
	case HOME_ERR_POS_LIMIT:	dwRetVal = -4;	break;
	case HOME_ERR_UNKNOWN:		dwRetVal = -5;	break;
	default:					dwRetVal = 0;	break;
	}

	return (int)dwRetVal;
}

//-----------------------------------------------------------------------------
//
// Home 검색 작업 중의 진행 정도, 단위 %로 반환된다. 
//
//-----------------------------------------------------------------------------
int CAxlMotorSet::GetHomeSearchRate(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return 100;
#endif

	DWORD dwHomeMainStepNumber = 0;
	DWORD dwHomeStepNumber = 0;
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return dwHomeStepNumber;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return dwHomeStepNumber;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;	

	//! 원점검색 시작되면 진행율을 확인할 수 있다. 원점검색이 완료되면 성공여부와 관계없이 100을 반환하게 된다.
	//! uHomeMainStepNumber은 겐트리일 경우 마스터,슬레이브가 동작하는지 확인할 때 이용한다.
	//!  (마스터축 동작일 때는 0을 리턴, 슬레이브동작일 때는 10을 리턴한다.)
	AxmHomeGetRate(MOTOR_AXIS_NUMBER[nUseAxis], &dwHomeMainStepNumber, &dwHomeStepNumber);

	//! 원점검색 진행율(단위: %)
	return dwHomeStepNumber;
}


//-----------------------------------------------------------------------------
//
//! 원점 검색시 사용되는 속도 설정
//
//-----------------------------------------------------------------------------
DWORD CAxlMotorSet::SetHomeSearchSpeed(int nAxis)
{
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
	double dAccCalFirst = 0.0;
	double dAccCalSecond = 0.0;
	int nUnit = 0;
	int nUseAxis = 0;
	
	nUnit = nAxis / MAX_MOTOR_COUNT;
	nUseAxis = nAxis % MAX_MOTOR_COUNT;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return AXT_RT_INVALID_MODULE_POS;

	if ((nUseAxis < 0) || (nUseAxis >= MAX_MOTOR_COUNT))
		return AXT_RT_INVALID_MODULE_POS;
	
	//! 원점 속도 조절 할것.	
	switch (nUseAxis)
	{
	//Y , TH , Z
	case MOTOR_PCB_X:
		dVelFirst = 5000;		dVelSecond = 1000.;		dVelThird = 500;		dvelLast = 100.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;
	case MOTOR_PCB_Y:
		dVelFirst = 10000;		dVelSecond = 2000.;		dVelThird = 1000;		dvelLast = 200.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;
	case MOTOR_PCB_Z:
		dVelFirst = 4000;		dVelSecond = 1000.;		dVelThird = 200;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;
	case MOTOR_PCB_TH:
		dVelFirst = 4000;		dVelSecond = 2000;		dVelThird = 1000;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;
	case MOTOR_PCB_TY:
		dVelFirst = 4000;		dVelSecond = 2000;		dVelThird = 1000;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;
	case MOTOR_PCB_TX:
		dVelFirst = 4000;		dVelSecond = 2000;		dVelThird = 1000;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;

	
	/*case MOTOR_PCB_TY:
		dVelFirst = 4000;		dVelSecond = 2000.;		dVelThird = 1000;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;
	case MOTOR_PCB_TX:
		dVelFirst = 4000;		dVelSecond = 2000.;		dVelThird = 1000;		dvelLast = 50.;		dAccFirst = 0.1;	dAccSecond = 0.1;
		break;*/
	
	}

#ifdef MOTOR_ACC_TYPE_SEC
	dAccCalFirst = dAccFirst;
	dAccCalSecond = dAccSecond; 
#else
	dAccCalFirst = dAccFirst * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nUseAxis]);
 	dAccCalSecond = dAccFirst * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nUseAxis]);		//! 가속 
#endif	

	dwReturn = AxmHomeSetVel(MOTOR_AXIS_NUMBER[nAxis], dVelFirst, dVelSecond, dVelThird, dvelLast, dAccCalFirst, dAccCalSecond);

	return dwReturn;
}


//-----------------------------------------------------------------------------
//
//	Home 검색 작업 시작
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::StartHomeSearch(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	TCHAR szLog[SIZE_OF_1K];
	DWORD dwRetVal = 0;
	DWORD dwLevel = 0;
	int nUseAxis = 0;

	long    lHmDir = DIR_CW;			//! 원점검색을 초기에 진행할 방향설정
	DWORD   dwHmSig = HomeSensor;		//! 원점 검색에 사용 할 신호설정
	DWORD   dwZphas = DISABLE;			//! 1차 원점검색 완료 후 엔코더 Z상 검출 유무 설정
	double  dHClrTim = 2000.0;			//! 원점검색 완료 후 지령위치와 Encoder위치를 Clear하기 위해 대기하는 시간설정 [mSec단위]
	double  dHOffset = 0.0;				//! 원점검색이 완료된 후 기구 원점으로 이동 후 원점 재설정 할 위치
	CString szResult = _T("");

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return false;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;
	
	dwRetVal = AxmSignalIsServoOn(MOTOR_AXIS_NUMBER[nUseAxis], &dwLevel);
	if (dwRetVal != AXT_RT_SUCCESS)
	{
		return false;
	}

	if (dwLevel != ENABLE)
	{
		dwRetVal = AxmSignalServoOn(MOTOR_AXIS_NUMBER[nUseAxis], ENABLE);
		if (dwRetVal == AXT_RT_SUCCESS)
		{
			dwRetVal = AxmSignalIsServoOn(MOTOR_AXIS_NUMBER[nUseAxis], &dwLevel);
			if (dwRetVal == AXT_RT_SUCCESS)
			{
				if (dwLevel != ENABLE)
				{
					_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 원점 검색 SERVO ON 실패"), MOTOR_NAME[nAxis]);
					AddLog(szLog, 1, nUnit);

					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
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


	lHmDir = MOTOR_HOME_DIR[nAxis];
	dwHmSig = MOTOR_HOME_SIG[nAxis];

	dwRetVal = AxmHomeSetMethod(MOTOR_AXIS_NUMBER[nUseAxis], lHmDir, dwHmSig, dwZphas, dHClrTim, dHOffset);
	if (dwRetVal != AXT_RT_SUCCESS)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 원점 검색 설정 실패"), MOTOR_NAME[nAxis]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	//원점 검색 속도 설정
	dwRetVal = SetHomeSearchSpeed(nUseAxis);
	if (dwRetVal != AXT_RT_SUCCESS)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 원점 속도 설정 실패"), MOTOR_NAME[nAxis]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	dwRetVal = AxmHomeSetStart(MOTOR_AXIS_NUMBER[nUseAxis]);
	if (dwRetVal != AXT_RT_SUCCESS)
	{ 
		this->GetResultHomeSearch(nUnit, nAxis, szResult);
		_stprintf_s(szLog, SIZE_OF_1K, _T("%s"), (TCHAR*)(LPCTSTR)szResult);
		AddLog(szLog, 0, nUnit);

		return false;
	}

	return true;
}


//-----------------------------------------------------------------------------
//
// Home 검색 중에 강제로 중지 시킴
//
//-----------------------------------------------------------------------------
void CAxlMotorSet::StopHomeSearch(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return;
#endif
	int nUseAxis = 0;
	
	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return;

	nUseAxis = (nUnit * MAX_MOTOR_COUNT) + nAxis;

	//AxmMoveSStop(iAxis)
	AxmHomeSetResult(MOTOR_AXIS_NUMBER[nUseAxis], HOME_ERR_USER_BREAK);
	this->StopAxis(nUnit, nAxis);
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
double CAxlMotorSet::GetAccel_Cal(int nUnit, int nAxis, double dSec)
{
	double dRtnAcc = 0.0;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return dRtnAcc;

	if((nAxis < 0) || (nAxis >= MAX_MOTOR_COUNT))
		return dRtnAcc;

#ifdef MOTOR_ACC_TYPE_SEC
	dRtnAcc = dSec;
#else
	dRtnAcc = dSec * (9.8 * 1000 * g_clSysData.m_dMotorResol[nUnit][nAxis]);
#endif

	return dRtnAcc;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::GetHomeState(int nUnit)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	bool bRetVal = true;
	int i;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (m_bOrgFlag[nUnit][i] == false)
		{
			bRetVal = false;
			break;
		}
	}

	return bRetVal;


}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::GetHomeState(int nUnit, int nAxis)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	bool bRetVal = true;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if (m_bOrgFlag[nUnit][nAxis] == false)
	{
		bRetVal = false;
	}

	return bRetVal;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::GetAmpFaultState(int nUnit)
{
#ifndef ON_LINE_MOTOR
	return false;
#endif

	bool bRetVal = false;
	int i;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (this->GetAmpFault(nUnit, i) == true)
		{
			bRetVal = true;
			break;
		}
	}

	return bRetVal;
}

//-----------------------------------------------------------------------------
//
//	AAB : PCB X,Y축 티칭위치 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MovePcbXYMotor(int nUnit, int nPosi, double dOffsetX /*= 0.0*/, double dOffsetY /*= 0.0*/,  bool bWait /*= false*/, bool bManual /*false*/)
{
#ifndef ON_LINE_MODE
	return true;
#endif


	static DWORD dwTickCount;
	TCHAR szLog[SIZE_OF_1K];
	int nAxis[2];
	double dPos[2];
	int nStep;
	int i;

	if (this->GetAmpFault(nUnit, MOTOR_PCB_Z))
	{
		m_bOrgFlag[nUnit][MOTOR_PCB_Z] = false;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 AMP ALARM 발생. MoveAxis 동작 실패"), MOTOR_NAME[MOTOR_PCB_Z]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if (!this->GetAmpEnable(nUnit, MOTOR_PCB_Z))
	{
		m_bOrgFlag[nUnit][MOTOR_PCB_Z] = false;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 SERVO OFF 상태 입니다. MoveAxis 동작 실패"), MOTOR_NAME[MOTOR_PCB_Z]);
		AddLog(szLog, 1, nUnit);

		return false;
	}
	if ((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if ((nPosi < 0) || (nPosi >= MAX_POS_COUNT))
		return false;

	for (i = 0; i < 2; i++)
	{
		nAxis[i] = 0;
		dPos[i] = 0.0;
	}

	if (fabs(dOffsetX) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_X])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB X축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_X], dOffsetX);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	if (fabs(dOffsetY) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Y])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB Y축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Y], dOffsetY);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	if (nPosi == CHART_POS)
	{
		/*if (g_clDioControl.PcbGripCheck(nUnit, false, false) == true)
		{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[INFO] PCB부 GRIP이 열려 있습니다."));
		AddLog(szLog, 1, nUnit, (g_clTaskWork[nUnit].m_nAutoFlag == MODE_AUTO) ? true : false);

		return false;
		}*/

	}

	nAxis[0] = MOTOR_PCB_X;
	nAxis[1] = MOTOR_PCB_Y;

	dPos[0] = g_clModelData[nUnit].m_stTeachData[nPosi].dPos[MOTOR_PCB_X] + dOffsetX;
	dPos[1] = g_clModelData[nUnit].m_stTeachData[nPosi].dPos[MOTOR_PCB_Y] + dOffsetY;
	



	if (this->MoveAxisMulti(nUnit, 2, nAxis, dPos) == false)
	{
		return false;
	}

	if (bWait == true)
	{
		nStep = 100;
		dwTickCount = GetTickCount();

		while (1)
		{
			switch (nStep)
			{
			case 100:
				nStep = 200;
				break;
			case 200:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_X) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_X) - dPos[0]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 300;
				}
				break;
			case 300:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_Y) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_Y) - dPos[1]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 400;
				}
				break;
			default:
				break;
			}

			if (nStep >= 400)
				break;

			if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
			{
				this->StopAxisAll(nUnit);
				return false;
			}

			Sleep(10);
		}
	}
	return true;
}


//-----------------------------------------------------------------------------
//
//	AAB : PCB X,Y,T축 티칭위치 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MovePcbXYTMotor(int nUnit, int nPosi, double dOffsetX /*= 0.0*/, double dOffsetY /*= 0.0*/, double dOffsetTh /*= 0.0*/, bool bWait /*= false*/ ,bool bManual /*false*/)
{
#ifndef ON_LINE_MODE
	return true;
#endif

	static DWORD dwTickCount;
	TCHAR szLog[SIZE_OF_1K];
	int nAxis[3];
	double dPos[3];
	int nStep;
	int i;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if ((nPosi < 0) || (nPosi >= MAX_POS_COUNT))
		return false;


	if (this->GetAmpFault(nUnit, MOTOR_PCB_Z))
	{
		m_bOrgFlag[nUnit][MOTOR_PCB_Z] = false;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 AMP ALARM 발생. MoveAxis 동작 실패"), MOTOR_NAME[MOTOR_PCB_Z]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if (!this->GetAmpEnable(nUnit, MOTOR_PCB_Z))
	{
		m_bOrgFlag[nUnit][MOTOR_PCB_Z] = false;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 SERVO OFF 상태 입니다. MoveAxis 동작 실패"), MOTOR_NAME[MOTOR_PCB_Z]);
		AddLog(szLog, 1, nUnit);

		return false;
	}


	for (i = 0; i < 3; i++)
	{
		nAxis[i] = 0;
		dPos[i] = 0.0;
	}
	if (nPosi == LASER_POS)
	{
		double dAlignPos = g_clModelData[nUnit].m_stTeachData[SENSOR_ALIGN_POS].dPos[MOTOR_PCB_Y] - 10.0;
		if (this->GetEncoderPos(nUnit, MOTOR_PCB_Y) < dAlignPos)
		{
			if (g_clMotorSet.GetPcbZMotorPosCheck(nUnit, WAIT_POS) == false)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("[INFO] PCB Z 대기위치가 아닙니다."));
				AddLog(szLog, 1, nUnit, true);
				return false;
			}
		}
		
	}
	else
	{
		if (fabs(dOffsetX) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_X])
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("PCB X축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_X], dOffsetX);
			AddLog(szLog, 1, nUnit);
			return false;
		}

		if (fabs(dOffsetY) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Y])
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("PCB Y축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Y], dOffsetY);
			AddLog(szLog, 1, nUnit);
			return false;
		}

		if (fabs(dOffsetTh) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH])
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("PCB TH축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH], dOffsetTh);
			AddLog(szLog, 1, nUnit);
			return false;
		}


		if (g_clMotorSet.GetPcbZMotorPosCheck(nUnit, WAIT_POS) == false)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[INFO] PCB Z 대기위치가 아닙니다."));
			AddLog(szLog, 1, nUnit, true);
			return false;
		}
	}

	

	nAxis[0] = MOTOR_PCB_X;
	nAxis[1] = MOTOR_PCB_Y;
	nAxis[2] = MOTOR_PCB_TH;

	dPos[0] = g_clModelData[nUnit].m_stTeachData[nPosi].dPos[MOTOR_PCB_X] + dOffsetX;
	dPos[1] = g_clModelData[nUnit].m_stTeachData[nPosi].dPos[MOTOR_PCB_Y] + dOffsetY;
	dPos[2] = g_clModelData[nUnit].m_stTeachData[nPosi].dPos[MOTOR_PCB_TH] + dOffsetTh;
	


	if (this->MoveAxisMulti(nUnit, 3, nAxis, dPos) == false)
	{
		return false;
	}

	if (bWait == true)
	{
		nStep = 100;
		dwTickCount = GetTickCount();

		while (1)
		{
			switch (nStep)
			{
			case 100:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_TH) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_TH) - dPos[2]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 200;
				}
				break;
			case 200:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_X) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_X) - dPos[0]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 300;
				}
				break;
			case 300:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_Y) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_Y) - dPos[1]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 400;
				}
				break;
			default:
				break;
			}

			if (nStep >= 400)
				break;

			if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
			{
				this->StopAxisAll(nUnit);
				return false;
			}

			Sleep(10);
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
//
//	AAB : PCB X,Y,T축 현재위치에서 보정량 만큼 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MovePcbXYTMotor(int nUnit, double dOffsetX /*= 0.0*/, double dOffsetY /*= 0.0*/, double dOffsetTh /*= 0.0*/, bool bWait /*= false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif
	static DWORD dwTickCount;
	TCHAR szLog[SIZE_OF_1K];
	int nAxis[3];
	double dPos[3];
	int nStep;
	int i;

	if (this->GetAmpFault(nUnit, MOTOR_PCB_Z))
	{
		m_bOrgFlag[nUnit][MOTOR_PCB_Z] = false;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 AMP ALARM 발생. MoveAxis 동작 실패"), MOTOR_NAME[MOTOR_PCB_Z]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if (!this->GetAmpEnable(nUnit, MOTOR_PCB_Z))
	{
		m_bOrgFlag[nUnit][MOTOR_PCB_Z] = false;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 SERVO OFF 상태 입니다. MoveAxis 동작 실패"), MOTOR_NAME[MOTOR_PCB_Z]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	for (i = 0; i < 3; i++)
	{
		nAxis[i] = 0;
		dPos[i] = 0.0;
	}

	if (fabs(dOffsetX) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_X])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB X축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_X], dOffsetX);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	if (fabs(dOffsetY) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Y])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB Y축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Y], dOffsetY);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	if (fabs(dOffsetTh) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB TH축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH], dOffsetTh);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	nAxis[0] = MOTOR_PCB_X;
	nAxis[1] = MOTOR_PCB_Y;
	nAxis[2] = MOTOR_PCB_TH;

	dPos[0] = this->GetEncoderPos(nUnit, MOTOR_PCB_X) + dOffsetX;
	dPos[1] = this->GetEncoderPos(nUnit, MOTOR_PCB_Y) + dOffsetY;
	dPos[2] = this->GetEncoderPos(nUnit, MOTOR_PCB_TH) + dOffsetTh;

	if (this->MoveAxisMulti(nUnit, 3, nAxis, dPos) == false)
	{
		return false;
	}

	if (bWait == true)
	{
		nStep = 100;
		dwTickCount = GetTickCount();

		while (1)
		{
			switch (nStep)
			{
			case 100:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_TH) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_TH) - dPos[2]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 200;
				}
				break;
			case 200:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_X) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_X) - dPos[0]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 300;
				}
				break;
			case 300:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_Y) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_Y) - dPos[1]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 400;
				}
				break;
			default:
				break;
			}

			if (nStep >= 400)
				break;

			if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
			{
				this->StopAxisAll(nUnit);
				return false;
			}

			Sleep(10);
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
//
//	AA : PCB Y,T축 티칭위치 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MovePcbYTMotor(int nUnit, int nPosi, double dOffsetY /*= 0.0*/, double dOffsetTh /*= 0.0*/, bool bWait /*= false*/, bool bManual /*false*/)
{
#ifndef ON_LINE_MODE
	return true;
#endif

	static DWORD dwTickCount;
	TCHAR szLog[SIZE_OF_1K];
	int nAxis[2];
	double dPos[2];
	int nStep;
	int i;
	if (this->GetAmpFault(nUnit, MOTOR_PCB_Z))
	{
		m_bOrgFlag[nUnit][MOTOR_PCB_Z] = false;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 AMP ALARM 발생. MoveAxis 동작 실패"), MOTOR_NAME[MOTOR_PCB_Z]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if (!this->GetAmpEnable(nUnit, MOTOR_PCB_Z))
	{
		m_bOrgFlag[nUnit][MOTOR_PCB_Z] = false;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 SERVO OFF 상태 입니다. MoveAxis 동작 실패"), MOTOR_NAME[MOTOR_PCB_Z]);
		AddLog(szLog, 1, nUnit);

		return false;
	}
	if ((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if ((nPosi < 0) || (nPosi >= MAX_POS_COUNT))
		return false;
	if (nPosi == CHART_POS)
	{
		if (g_clDioControl.PcbSocketUpCheck(nUnit, true) == true)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("PCB SOCKET 상승 상태입니다."));
			AddLog(szLog, 1, nUnit);
			return false;
		}
	}
	for (i = 0; i < 2; i++)
	{
		nAxis[i] = 0;
		dPos[i] = 0.0;
	}

	if (fabs(dOffsetY) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Y])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB Y축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Y], dOffsetY);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	if (fabs(dOffsetTh) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB TH축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH], dOffsetTh);
		AddLog(szLog, 1, nUnit);
		return false;
	}


	nAxis[0] = MOTOR_PCB_Y;
	nAxis[1] = MOTOR_PCB_TH;

	dPos[0] = g_clModelData[nUnit].m_stTeachData[nPosi].dPos[MOTOR_PCB_Y] + dOffsetY;
	dPos[1] = g_clModelData[nUnit].m_stTeachData[nPosi].dPos[MOTOR_PCB_TH] + dOffsetTh;




	if (this->MoveAxisMulti(nUnit, 2, nAxis, dPos) == false)
	{
		return false;
	}

	if (bWait == true)
	{
		nStep = 100;
		dwTickCount = GetTickCount();

		while (1)
		{
			switch (nStep)
			{
			case 100:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_TH) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_TH) - dPos[1]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 200;
				}
				break;
			case 200:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_Y) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_Y) - dPos[0]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 300;
				}
				break;
			
			default:
				break;
			}

			if (nStep >= 300)
				break;

			if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
			{
				this->StopAxisAll(nUnit);
				return false;
			}

			Sleep(10);
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
//
//	AA : PCB Y,T축 현재위치에서 보정량 만큼 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MovePcbYTMotor(int nUnit, double dOffsetY /*= 0.0*/, double dOffsetTh /*= 0.0*/, bool bWait /*= false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	static DWORD dwTickCount;
	TCHAR szLog[SIZE_OF_1K];
	int nAxis[2];
	double dPos[2];
	int nStep;
	int i;
	
	

	if ((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	for (i = 0; i < 2; i++)
	{
		nAxis[i] = 0;
		dPos[i] = 0.0;
	}


	if (fabs(dOffsetY) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Y])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB Y축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Y], dOffsetY);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	if (fabs(dOffsetTh) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB TH축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH], dOffsetTh);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	nAxis[0] = MOTOR_PCB_Y;
	nAxis[1] = MOTOR_PCB_TH;

	dPos[0] = this->GetEncoderPos(nUnit, MOTOR_PCB_Y) + dOffsetY;
	dPos[1] = this->GetEncoderPos(nUnit, MOTOR_PCB_TH) + dOffsetTh;

	if (this->MoveAxisMulti(nUnit, 2, nAxis, dPos) == false)
	{
		return false;
	}

	if (bWait == true)
	{
		nStep = 100;
		dwTickCount = GetTickCount();

		while (1)
		{
			switch (nStep)
			{
			case 100:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_TH) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_TH) - dPos[1]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 200;
				}
				break;
			case 200:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_Y) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_Y) - dPos[0]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 300;
				}
				break;
			
			default:
				break;
			}

			if (nStep >= 300)
				break;

			if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
			{
				this->StopAxisAll(nUnit);
				return false;
			}

			Sleep(10);
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
//
//	AAB : PCB X,T축 티칭위치 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MovePcbXTMotor(int nUnit, int nPosi, double dOffsetX /*= 0.0*/, double dOffsetTh /*= 0.0*/, bool bWait /*= false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif
#if 0
	static DWORD dwTickCount;
	TCHAR szLog[SIZE_OF_1K];
	int nAxis[2];
	double dPos[2];
	int nStep;
	int i;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if ((nPosi < 0) || (nPosi >= MAX_POS_COUNT))
		return false;

	for (i = 0; i < 2; i++)
	{
		nAxis[i] = 0;
		dPos[i] = 0.0;
	}

	if (nPosi != LASER_OUT_POS && nPosi != LASER_IN_POS)
	{
		if (fabs(dOffsetX) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_X])
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("PCB X축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_X], dOffsetX);
			AddLog(szLog, 1, nUnit);
			return false;
		}
	}

	if (fabs(dOffsetTh) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB TH축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH], dOffsetTh);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	nAxis[0] = MOTOR_PCB_X;
	nAxis[1] = MOTOR_PCB_TH;

	dPos[0] = g_clModelData[nUnit].m_stTeachData[nPosi].dPos[MOTOR_PCB_X] + dOffsetX;
	dPos[1] = g_clModelData[nUnit].m_stTeachData[nPosi].dPos[MOTOR_PCB_TH] + dOffsetTh;

	if (this->MoveAxisMulti(nUnit, 2, nAxis, dPos) == false)
	{
		return false;
	}

	if (bWait == true)
	{
		nStep = 100;
		dwTickCount = GetTickCount();

		while (1)
		{
			switch (nStep)
			{
			case 100:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_TH) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_TH) - dPos[1]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 200;
				}
				break;
			case 200:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_X) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_X) - dPos[0]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 300;
				}
				break;
			case 300:
				nStep = 400;
				break;
			default:
				break;
			}

			if (nStep >= 400)
				break;

			if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
			{
				this->StopAxisAll(nUnit);
				return false;
			}

			Sleep(10);
		}
	}
#endif
	return true;
}

//-----------------------------------------------------------------------------
//
//	AAB : PCB X,T축 현재위치에서 보정량 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MovePcbXTMotor(int nUnit, double dOffsetX /*= 0.0*/, double dOffsetTh /*= 0.0*/, bool bWait /*= false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif
#if 0
	static DWORD dwTickCount;
	TCHAR szLog[SIZE_OF_1K];
	int nAxis[2];
	double dPos[2];
	int nStep;
	int i;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	for (i = 0; i < 2; i++)
	{
		nAxis[i] = 0;
		dPos[i] = 0.0;
	}

	if (fabs(dOffsetX) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_X])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB X축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_X], dOffsetX);
		AddLog(szLog, 1, nUnit);
		return false;
	}	

	if (fabs(dOffsetTh) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB TH축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH], dOffsetTh);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	nAxis[0] = MOTOR_PCB_X;
	nAxis[1] = MOTOR_PCB_TH;
	
	dPos[0] = this->GetEncoderPos(nUnit, MOTOR_PCB_X) + dOffsetX;	
	dPos[1] = this->GetEncoderPos(nUnit, MOTOR_PCB_TH) + dOffsetTh;

	if (this->MoveAxisMulti(nUnit, 2, nAxis, dPos) == false)
	{
		return false;
	}

	if (bWait == true)
	{
		nStep = 100;
		dwTickCount = GetTickCount();

		while (1)
		{
			switch (nStep)
			{
			case 100:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_TH) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_TH) - dPos[1]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 200;
				}
				break;
			case 200:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_X) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_X) - dPos[0]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 300;
				}
				break;			
			default:
				break;
			}

			if (nStep >= 300)
				break;

			if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
			{
				this->StopAxisAll(nUnit);
				return false;
			}

			Sleep(10);
		}
	}
#endif
	return true;
}
//-----------------------------------------------------------------------------
//
//	AA : PCB T축 현재위치에서 보정량 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MovePcbTMotor(int nUnit,double dOffsetTh /*= 0.0*/, bool bWait /*= false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	static DWORD dwTickCount;
	TCHAR szLog[SIZE_OF_1K];
	int nAxis[2];
	double dPos[2];
	int nStep;
	int i;

	if ((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	for (i = 0; i < 2; i++)
	{
		nAxis[i] = 0;
		dPos[i] = 0.0;
	}


	if (fabs(dOffsetTh) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB TH축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TH], dOffsetTh);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	nAxis[0] = MOTOR_PCB_TH;

	dPos[0] = this->GetEncoderPos(nUnit, MOTOR_PCB_TH) + dOffsetTh;

	if (this->MoveAxisMulti(nUnit, 1, nAxis, dPos) == false)
	{
		return false;
	}

	if (bWait == true)
	{
		nStep = 100;
		dwTickCount = GetTickCount();

		while (1)
		{
			switch (nStep)
			{
			case 100:
				if (this->GetStopAxis(nUnit, MOTOR_PCB_TH) == true)
				{
					dwTickCount = GetTickCount();

					nStep = 200;
				}
				break;
			case 200:
				nStep = 300;
				break;
			default:
				break;
			}

			if (nStep >= 300)
				break;

			if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
			{
				this->StopAxisAll(nUnit);
				return false;
			}

			Sleep(10);
		}
	}

	return true;
}
//-----------------------------------------------------------------------------
//
//	AAB : PCB Y축 티칭위치 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MovePcbYMotor(int nUnit, int nPosi, double dOffsetY /*= 0.0*/, bool bWait /*= false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	static DWORD dwTickCount;
	TCHAR szLog[SIZE_OF_1K];
	int nAxis = 0;
	double dPos = 0.0;
	int nStep;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if(nPosi < 0 || nPosi >= MAX_POS_COUNT)
		return false;
	
	if (this->GetAmpFault(nUnit, MOTOR_PCB_Z))
	{
		m_bOrgFlag[nUnit][MOTOR_PCB_Z] = false;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 AMP ALARM 발생. MoveAxis 동작 실패"), MOTOR_NAME[MOTOR_PCB_Z]);
		AddLog(szLog, 1, nUnit);

		return false;
	}

	if (!this->GetAmpEnable(nUnit, MOTOR_PCB_Z))
	{
		m_bOrgFlag[nUnit][MOTOR_PCB_Z] = false;

		_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] 모터 SERVO OFF 상태 입니다. MoveAxis 동작 실패"), MOTOR_NAME[MOTOR_PCB_Z]);
		AddLog(szLog, 1, nUnit);

		return false;
	}
	if (fabs(dOffsetY) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Y])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB Y축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Y], dOffsetY);
		AddLog(szLog, 1, nUnit);
		return false;
	}
	

	nAxis = MOTOR_PCB_Y;

	dPos = g_clModelData[nUnit].m_stTeachData[nPosi].dPos[MOTOR_PCB_Y] + dOffsetY;

	if (this->MoveAxis(nUnit, nAxis, ABS, dPos, g_clSysData.m_dMotorSpeed[nUnit][MOTOR_PCB_Y]) == false)
	{
		return false;
	}

	if (bWait == true)
	{
		nStep = 100;
		dwTickCount = GetTickCount();

		while (1)
		{
			switch (nStep)
			{
			case 100:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_Y) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_Y) - dPos) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 200;
				}
				break;			
			default:
				break;
			}

			if (nStep >= 200)
				break;

			if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
			{
				this->StopAxisAll(nUnit);
				return false;
			}

			Sleep(10);
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
//
//	AAB : PCB Z축 티칭위치 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MovePcbZMotor(int nUnit, int nPosi, double dOffsetZ /*= 0.0*/, bool bWait /*= false*/, bool bManual)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif


	static DWORD dwTickCount;
	TCHAR szLog[SIZE_OF_1K];
	int nAxis = 0;
	double dPos = 0.0;
	int nStep;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if(nPosi < 0 || nPosi >= MAX_POS_COUNT)
		return false;

	if (fabs(dOffsetZ) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Z])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB Y축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Z], dOffsetZ);
		AddLog(szLog, 1, nUnit);
		return false;
	}
	
	nAxis = MOTOR_PCB_Z;

	dPos = g_clModelData[nUnit].m_stTeachData[nPosi].dPos[MOTOR_PCB_Z] + dOffsetZ;


	if (this->MoveAxis(nUnit, nAxis, ABS, dPos, g_clSysData.m_dMotorSpeed[nUnit][MOTOR_PCB_Z]) == false)
	{
		return false;
	}

	if (bWait == true)
	{
		nStep = 100;
		dwTickCount = GetTickCount();

		while (1)
		{
			switch (nStep)
			{
			case 100:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_Z) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_Z) - dPos) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 200;
				}
				break;
			default:
				break;
			}

			if (nStep >= 200)
				break;

			if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
			{
				this->StopAxisAll(nUnit);
				return false;
			}

			Sleep(10);
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MovePcbZMotor(int nUnit, double dPos, bool bWait/* = false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif


	static DWORD dwTickCount;
	int nAxis;	
	int nStep;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	nAxis = MOTOR_PCB_Z;
	
	if (this->MoveAxis(nUnit, nAxis, ABS, dPos, g_clSysData.m_dMotorSpeed[nUnit][MOTOR_PCB_Z]) == false)
	{
		return false;
	}

	if (bWait == true)
	{
		nStep = 100;
		dwTickCount = GetTickCount();

		while (1)
		{
			switch (nStep)
			{
			case 100:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_Z) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_Z) - dPos) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 200;
				}
				break;
			default:
				break;
			}

			if (nStep >= 200)
				break;

			if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
			{
				this->StopAxisAll(nUnit);
				return false;
			}

			Sleep(10);
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
//
//	AAB : PCB TX,TY축 티칭위치 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MovePcbTxTyMotor(int nUnit, int nPosi, double dOffsetTx /*= 0.0*/, double dOffsetTy /*= 0.0*/, bool bWait /*= false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif
	static DWORD dwTickCount;
	TCHAR szLog[SIZE_OF_1K];
	int nAxis[2];
	double dPos[2];
	int nStep;
	int i;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if ((nPosi < 0) || (nPosi >= MAX_POS_COUNT))
		return false;

	for (i = 0; i < 2; i++)
	{
		nAxis[i] = 0;
		dPos[i] = 0.0;
	}

	if (fabs(dOffsetTx) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TX])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB TX축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TX], dOffsetTx);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	if (fabs(dOffsetTy) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TY])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB TY축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TY], dOffsetTy);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	nAxis[0] = MOTOR_PCB_TY;
	nAxis[1] = MOTOR_PCB_TX;

	dPos[0] = g_clModelData[nUnit].m_stTeachData[nPosi].dPos[MOTOR_PCB_TY] + dOffsetTy; 
	dPos[1] = g_clModelData[nUnit].m_stTeachData[nPosi].dPos[MOTOR_PCB_TX] + dOffsetTx;

	if (this->MoveAxisMulti(nUnit, 2, nAxis, dPos) == false)
	{
		return false;
	}

	if (bWait == true)
	{
		nStep = 100;
		dwTickCount = GetTickCount();

		while (1)
		{
			switch (nStep)
			{
			case 100:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_TX) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_TX) - dPos[1]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 200;
				}
				break;
			case 200:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_TY) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_TY) - dPos[0]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 300;
				}
				break;
			default:
				break;
			}

			if (nStep >= 300)
				break;

			if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
			{
				this->StopAxisAll(nUnit);
				return false;
			}

			Sleep(10);
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
//
//	AAB : PCB TX,TY축 현재위치에서 보정량 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MovePcbTxTyMotor(int nUnit, double dOffsetTx /*= 0.0*/, double dOffsetTy /*= 0.0*/, bool bWait /*= false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	static DWORD dwTickCount;
	TCHAR szLog[SIZE_OF_1K];
	int nAxis[2];
	double dPos[2];
	int nStep;
	int i;

	if((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	for (i = 0; i < 2; i++)
	{
		nAxis[i] = 0;
		dPos[i] = 0.0;
	}

	if (fabs(dOffsetTx) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TX])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB TX축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TX], dOffsetTx);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	if (fabs(dOffsetTy) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TY])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB TY축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_TY], dOffsetTy);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	nAxis[0] = MOTOR_PCB_TY;
	nAxis[1] = MOTOR_PCB_TX;

	dPos[0] = this->GetEncoderPos(nUnit, MOTOR_PCB_TY) + dOffsetTy;
	dPos[1] = this->GetEncoderPos(nUnit, MOTOR_PCB_TX) + dOffsetTx;

	if (this->MoveAxisMulti(nUnit, 2, nAxis, dPos) == false)
	{
		return false;
	}

	if (bWait == true)
	{
		nStep = 100;
		dwTickCount = GetTickCount();

		while (1)
		{
			switch (nStep)
			{
			case 100:
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_TY) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_TY) - dPos[0]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 200;
				}
				break;
			case 200:
				
				if ((this->GetStopAxis(nUnit, MOTOR_PCB_TX) == true) && ((this->GetEncoderPos(nUnit, MOTOR_PCB_TX) - dPos[1]) < ENCORDER_GAP))
				{
					dwTickCount = GetTickCount();

					nStep = 300; 
				}
				break;
			default:
				break;
			}

			if (nStep >= 300)
				break;

			if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
			{
				this->StopAxisAll(nUnit);
				return false;
			}

			Sleep(10);
		}
	}

	return true;
}


//-----------------------------------------------------------------------------
//
//	AAB : LENS X,Y축 티칭위치 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveLensXYMotor(int nUnit, int nPosi, double dOffsetX /*= 0.0*/, double dOffsetY /*= 0.0*/, bool bWait /*= false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	return true;
}

//-----------------------------------------------------------------------------
//
//	AAB : LENS X,Y축 현재위치에서 보정량 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveLensXYMotor(int nUnit, double dOffsetX /*= 0.0*/, double dOffsetY /*= 0.0*/, bool bWait /*= false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	return true;
}

//-----------------------------------------------------------------------------
//
//	AAB : LENS X축 티칭위치 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveLensXMotor(int nUnit, int nPosi, double dOffsetX/* = 0.0*/, bool bWait/* = false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	return true;
}

//-----------------------------------------------------------------------------
//
//	AAB : LENS Y축 티칭위치 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveLensYMotor(int nUnit, int nPosi, double dOffsetY /*= 0.0*/, bool bWait /*= false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	return true;
}


bool CAxlMotorSet::MoveLensZAAMotor(int nUnit, double dPos, double dOffsetZ /*= 0.0*/, bool bWait /*= false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	return true;
}



//-----------------------------------------------------------------------------
//
//	AAB : LENS Z축 티칭위치 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveLensZMotor(int nUnit, int nPosi, double dOffsetZ /*= 0.0*/, bool bWait /*= false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	return true;
}

//-----------------------------------------------------------------------------
//
//	AAB : LENS Z축 상대이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveLensZMotor(int nUnit, double dOffsetZ /*= 0.0*/, double dVel, bool bWait /*= false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	return true;
}

//-----------------------------------------------------------------------------
//
//	LENS Z축 Offset 위치로 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MovePcbZMotorComplete(int nUnit, double dOffsetZ/* = 0.0*/, double dVel/* = 0.1*/, double dAcc/* = 0.1*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif


	static DWORD dwTickCount;
	TCHAR szLog[SIZE_OF_1K];
	int nAxis = 0;
	double dPos = 0.0;
	int nStep;

	if ((nUnit < 0) || (nUnit >= MAX_UNIT_COUNT))
		return false;

	if (fabs(dOffsetZ) > g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Z])
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB Z축 보정값 허용 범위[± %.03lf]를 초과 하였습니다. 보정값 :%.03lf"), g_clModelData[nUnit].m_dErrLimit[MOTOR_PCB_Z], dOffsetZ);
		AddLog(szLog, 1, nUnit);
		return false;
	}

	nAxis = MOTOR_PCB_Z;

	dPos = this->GetEncoderPos(nUnit, MOTOR_PCB_Z) + dOffsetZ;

	if (this->MoveAxis(nUnit, nAxis, ABS, dPos, dVel, dAcc) == false)
	{
		return false;
	}

	nStep = 100;
	dwTickCount = GetTickCount();

	while (1)
	{
		switch (nStep)
		{
		case 100:
			if ((this->GetStopAxis(nUnit, MOTOR_PCB_Z) == true) && ((fabs(this->GetEncoderPos(nUnit, MOTOR_PCB_Z)) - fabs(dPos)) < ENCORDER_GAP))
			{
				dwTickCount = GetTickCount();

				nStep = 200;
			}
			break;
		default:
			break;
		}

		if (nStep >= 200)
			break;

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			this->StopAxisAll(nUnit);
			return false;
		}

		Sleep(10);
	}

	return true;
}


//-----------------------------------------------------------------------------
//
//	LENS Z축 Offset 위치로 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveLensZMotorComplete(int nUnit, double dOffsetZ/* = 0.0*/, double dVel/* = 0.1*/, double dAcc/* = 0.1*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	return true;
}

bool CAxlMotorSet::MoveLensZMotorCompleteAA(int nUnit, double dOffsetZ/* = 0.0*/, double dVel/* = 0.1*/, double dAcc/* = 0.1*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	return true;
}

//-----------------------------------------------------------------------------
//
//	AAB : LENS TX,TY축 티칭위치 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveLensTxTyMotor(int nUnit, int nPosi, double dOffsetTx /*= 0.0*/, double dOffsetTy /*= 0.0*/, bool bWait /*= false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	return true;
}

//-----------------------------------------------------------------------------
//
//	AAB : LENS TX,TY축 현재위치에서 보정량 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::MoveLensTxTyMotor(int nUnit, double dOffsetTx /*= 0.0*/, double dOffsetTy /*= 0.0*/, bool bWait /*= false*/)
{
#ifndef ON_LINE_MOTOR
	return true;
#endif

	return true;
}


//-----------------------------------------------------------------------------
//
//	AAB : LENS TX,TY축 현재위치에서 보정량 이동
//
//-----------------------------------------------------------------------------
bool CAxlMotorSet::Epoxy_Rect_Circle_Draw(int nUnit)		//사각 , 원 포함 도포
{
#ifndef ON_LINE_MOTOR
	return true;
#endif
#if 0
	TCHAR szLog[SIZE_OF_1K];
	double startTime = 0.0;
	double eTime = 0.0;
	double curTime = 0.0;
	DWORD dwReturn = 0;
	double dAcc = 0.0;
	double dDec = 0.0;
	double MoveStartTime = 0.0;
	double dTimeAngle = 90.0;
	double dEndDeg1ToTime = 0.0;	//1도당 걸리는 시간 
	bool mMotorRtn = false;
	double dTotalCurveTime = 0.0;
	double dTotalLineTime = 0.0;

	//1도당 걸리는 시간 = (원주율 * 속도) / 360 /   가속/감속
	// dEndDeg1ToTime = (( (dDrawLength * 1) * M_PI) / (sqrt(dCircleSpeed  * dCircleSpeed /2)) ) / 360;
	//커브
	double dCurveTotalLength = fabs(g_clModelData[nUnit].m_EpoxyCurveEndYPoint[0]);// (fabs(g_clModelData[nUnit].m_EpoxyCurveEndYPoint[0]) + fabs(g_clModelData[nUnit].m_EpoxyCurveEndYPoint[1]) + fabs(g_clModelData[nUnit].m_EpoxyCurveEndYPoint[2]) + fabs(g_clModelData[nUnit].m_EpoxyCurveEndYPoint[3]));
	dTotalCurveTime = (((dCurveTotalLength * 1) * M_PI) / (sqrt(g_clModelData[nUnit].m_EpoxyCurveSpeed  * g_clModelData[nUnit].m_EpoxyCurveSpeed / 2))) / 360;// 360;
		//dCurveTotalLength / g_clModelData[nUnit].m_EpoxyLineSpeed;
	//직선
	dTotalLineTime = (g_clModelData[nUnit].m_EpoxyLineLength[0] + g_clModelData[nUnit].m_EpoxyLineLength[1] + g_clModelData[nUnit].m_EpoxyLineLength[2] + g_clModelData[nUnit].m_EpoxyLineLength[3]) / g_clModelData[nUnit].m_EpoxyLineSpeed;

	dTotalCurveTime *= 360;
	
	dEndDeg1ToTime = dTotalCurveTime + dTotalLineTime;//g_clModelData[nUnit].m_EpoxyLineLength[3] / g_clModelData[nUnit].m_EpoxyLineSpeed; 

	dEndDeg1ToTime -= g_clModelData[nUnit].m_EpoxyOffTime;


	if (dEndDeg1ToTime < 0.0)
	{
		dEndDeg1ToTime = 0.0;
	}

	int nstep = 100;
	while (1)
	{
		switch (nstep)
		{
		case 100:
			m_dwMotorTickCount = GetTickCount();
			g_clDioControl.EpoxyDischargeOn(nUnit, true);
			Sleep(10);
			if (g_clDioControl.EpoxyDischargeOn(nUnit, true) == false)
			{
				_stprintf_s(szLog, SIZE_OF_1K, _T("EPOXY ON FAIL"));
				AddLog(szLog, 1, nUnit);
				g_clDioControl.EpoxyDischargeOn(nUnit, true);
			}
			nstep = 140;
			break;
		case 140:
			//도포 on Delay
			if (g_clModelData[nUnit].m_EpoxyOnTime == 0.0)
			{
				nstep = 170;
			}
			if ((GetTickCount() - m_dwMotorTickCount) > g_clModelData[nUnit].m_EpoxyOnTime * 1000)
			{
				nstep = 170;
			}
			break;
		case 170:
			mMotorRtn = MoveStraightPcbXYAxis(nUnit);

			if (mMotorRtn == true)
			{
				m_dwMotorTickCount = GetTickCount();
				nstep = 200;
			}
			else
			{
				nstep = 0;
			}
			break;
		case 200:
			nstep = 500;
			break;
		case 500:
			if (GetStopAxis(nUnit, MOTOR_PCB_X) == true && GetStopAxis(nUnit, MOTOR_PCB_Y) == true)
			{
				g_clDioControl.EpoxyDischargeOn(nUnit, false);
				Sleep(10);
				if (g_clDioControl.EpoxyDischargeOn(nUnit, false) == false)
				{
					_stprintf_s(szLog, SIZE_OF_1K, _T("EPOXY OFF FAIL"));
					AddLog(szLog, 1, nUnit);
					g_clDioControl.EpoxyDischargeOn(nUnit, false);
				}

				AxmMotSetMoveUnitPerPulse(MOTOR_PCB_X, 1, 1);	//Unit/Pulse 원래형태로 변경(1:1 매칭으로)
				AxmMotSetMoveUnitPerPulse(MOTOR_PCB_Y, 1, 1);
				nstep = 900;
			}
			break;
		case 900: 
			nstep = 1000;
			break;
			/*if (g_clMotorSet.MoveAxisComplete(nUnit, MOTOR_PCB_X, REL, 3.0, g_clSysData.m_dMotorSpeed[nUnit][MOTOR_PCB_X], true) == false)
			{
				nstep = 1000;
				break;
			}*/
			break;
		default:
			nstep = 1000;
			break;
		}
		if (nstep == 1000)		break;

		if ((GetTickCount() - m_dwMotorTickCount) > 100000)
		{
			if (g_clDioControl.EpoxyDischargeOn(nUnit, false) == false)
			{
				g_clDioControl.EpoxyDischargeOn(nUnit, false);
			}
			this->StopAxisAll(nUnit);
			return false;
		}
	}
#endif
	return true;
}