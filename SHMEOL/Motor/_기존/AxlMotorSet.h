#pragma once

#include "../StdAfx.h"
//! AjinExTek Motion Controller 클래스
//! Created, 2014/12/10
//! Recently Modified,

//! 1] 아진엑스텍 Motion Controller는 위치 제어만 지원한다. 하지만, AxmMoveVel 처럼 일정한 속도로 움직이는 기능을 제공한다. 
//! 2] RTEX 제품 (PCI-R1604)에서는 Interrupt, Software Limit을 지원하지 않는다. 
//! 3] 서보 부하율을 알 수 있는 기능은 없다. 
//! 4] PCI-R1604 A4N, A5N의 경우 비상정지 입력단이 존재하지 않는다.
//!     (모션 모듈에 있는 비상정지 입력단 으로 신호를 넣게 되며 신호가 들어오면 ESTOP을 자동으로 내려 모든 모션에 대해서 정지)

//! [주의 사항] AA Bonder Vision부 Homing에서 기구 간섭
//!		1) 배사 조명을 후진 시킨 후에 Homing을 시작해야 한다. 
//!		2) Lens Z축 Motor가 위쪽으로 올라간 후에 다른 Motor들을 Homing해야 한다.
//!		3) PCB Y축 Motor가 (-) Limit 센서 쪽으로 간 이후에, PCB X, Theta 축 Motor를 Homing해야 한다. 
//!		4) PCB Theta축 Motor를 Homing하기 전에, PCB Cover 공기압 실린더를 상승시켜야 한다. 

//! 기존의 MMC Motion Controller와 함수명을 최대한 같이 하여, 소스 코드의 수정량을 줄인다. 


//! 아래 구조체는 특정 위치 (Limit 센서나 Home 센서)에서 자동으로 멈추도록 하여 모터를 움직일 때 사용한다.
struct strMove_Input_Signal_Search
{
	double dVel;
	double dAccel;

	//! 검출 신호 설정 (아래 4개의 변수 중 1개는 true이어야 한다)
	bool bEndLimit_Positive;
	bool bEndLimit_Negative;
	bool bHomeSensor;
	bool bPhase_Encoder_Z;		//! Encoder의 Z상 신호

	//! Edge 설정 (아래 2개의 변수 중 1개는 true이어야 한다)
	bool bEdge_Down;
	bool bEdge_Up;

	//! 정지 방법 (아래 2개의 변수 중 1개는 true이어야 한다)
	bool bEmergency;
	bool bSlowDown;

	strMove_Input_Signal_Search()
	{
		InitInfo();
	}

	void InitInfo()
	{
		dVel = 0.;
		dAccel = 0.;

		bEndLimit_Positive = false;
		bEndLimit_Negative = false;
		bHomeSensor = false;
		bPhase_Encoder_Z = false;

		bEdge_Down = false;
		bEdge_Up = false;

		bEmergency = false;
		bSlowDown = false;
	}

	strMove_Input_Signal_Search& operator=(const strMove_Input_Signal_Search &input)	//! '=' 연산자 overloading
	{
		dVel   = input.dVel;
		dAccel = input.dAccel;

		bEndLimit_Positive = input.bEndLimit_Positive;
		bEndLimit_Negative = input.bEndLimit_Negative;
		bHomeSensor        = input.bHomeSensor;
		bPhase_Encoder_Z   = input.bPhase_Encoder_Z;

		bEdge_Down = input.bEdge_Down;
		bEdge_Up   = input.bEdge_Up;

		bEmergency = input.bEmergency;
		bSlowDown  = input.bSlowDown;

		return *this;
	}
};//! struct strMove_Input_Signal_Search





class AxlMotorSet
{
public:
	AxlMotorSet(void);
	~AxlMotorSet(void);

private:
	//! 해당 절대 경로의 파일에 Motion Board의 설정값을 파일로 저장 가능
	CString m_sMotionSettingFilePath;

public:
	CString sMsg;
	bool bMotorMoving[UNIT_CH][CUR_MOTOR_NO];							
	int  m_bOrgFlag[UNIT_CH][CUR_MOTOR_NO];				
	bool m_bAxisState[UNIT_CH][CUR_MOTOR_NO];

	bool bJogPlusFlag[UNIT_CH][CUR_MOTOR_NO];	//조그상태
	bool bJogMinusFlag[UNIT_CH][CUR_MOTOR_NO];	//조그상태
	bool bOldJogPlusFlag[UNIT_CH][MAX_MOTOR_NO];		
	bool bOldJogMinusFlag[UNIT_CH][MAX_MOTOR_NO];


	CCriticalSection m_criHomeProc;

	bool Axl_Init();
	void Axl_Close();
	int  Axl_Axisconfig(int iUnit);


	bool AmpEnable(int iUnit, int iAxis);				
	bool AmpEnableAll(int iUnit);						
	bool AmpDisable(int iUnit, int iAxis);				
	bool AmpDisableAll(int iUnit);
	bool GetAmpEnable(int iUnit, int iAxis);			
	bool GetAmpEnableAll(int iUnit);					

	bool AmpFaultReset(int iUnit, int iAxis);			
	bool AmpFaultResetAll(int iUnit);
	int	 AmpFaultCheck(int iUnit);						
	bool GetAmpFault(int iUnit, int iAxis);				

	bool GetInposition(int iUnit, int iAxis);			
	bool GetHomeSensor(int iUnit, int iAxis);			
	bool GetNegaSensor(int iUnit, int iAxis);			
	bool GetPosiSensor(int iUnit, int iAxis);			

	bool ActCRC(int iUnit, int iAxis);

	bool GetStopAxis(int iUnit, int iAxis);			
	bool StopAxis(int iUnit, int iAxis);				
	bool StopAxisAll(int iUnit);

	double GetEncoderPos(int iUnit, int iAxis);			
	double GetEncoderPos_Disp(int iUnit, int iAxis);	
	double GetCommandPos(int iUnit, int iAxis);			
	double GetCommandPos_Disp(int iUnit, int iAxis);	

	//! 20160503
	int GetEncoderPulse(int iUnit, int iAxis);   
	int GetCommandPulse(int iUnit, int iAxis);  

	double CalcAccFromAccTime(double dVel, double dTime);						
	double CalcAcc_G(int iUnit, int iAxis);							
	double CalcDec_G(int iUnit, int iAxis);

	BOOL JogMove(int iUnit, int iAxis, double dVel);								
	BOOL JogStop(int iUnit, int iAxis);												

	bool MoveAxis_To_Sensor(int axis, strMove_Input_Signal_Search *pstrInput);		

	bool Move_From_GUI(int iUnit, int axis, int iID_GUI, CWnd* pParentWnd, bool bPlus = true);	//! GUI 화면에서 설정한 길이만큼 움직인다. (상대 이동)


	bool MoveAxis(int iUnit, int iAxis, bool AbSFlag, double dPos, double dVel);		
	bool MoveAxisMulti(int iUnit, int iAxisCnt, short iAxis[CUR_MOTOR_NO], double pos[CUR_MOTOR_NO]);	


	bool GetResult_Home_Search(int iUnit, int iAxis, CString &sResult);		
	int IsCompleted_Home_Search(int iUnit, int iAxis);						
	int  GetRate_Home_Search(int iUnit, int iAxis);							

	void Stop_Home_Search(int iUnit, int iAxis);							

	int  Start_Home_Search(int iUnit, int iAxis);												
	DWORD SetHomeSearchSpeed(int iUseAxis);									


	bool HomeSingleProcess(int iUnit, int iAxis);		//개별 원점
	bool HomeReadyProcess(int iUnit, int iType);		//전체 원점 0: 원점복귀, 1: 운전준비				
	
	bool Move_From_AbsRel(int iUnit, int iAxis, double dVal, bool bPlus);

	int	iHomeUnit;
	int	iHomeUseStep;							
	int	iHomeEndStep;							
	int	iHomeProcUsing[UNIT_CH][CUR_MOTOR_NO];	
	int iRunStep[2];
	int iRunStepOrg[2];
	//kdu 매뉴얼 aa 추가
	int iManualStep[2];
	int iSelectAxisss[2];		//개별원점에서 선택된 축 저장되는 변수
	bool bReadyPusher[2];		//운전 준비시 푸셔 위치 지정 변수
	int iSocketCntChk[2];
	double  dTime;
	double  dSTime;	
	double dFTime, dFTime2;
	bool   bITF_CHK[2];			///20160629  JJC

	HANDLE	m_hThreadHomeAll[UNIT_CH];		
	HANDLE	m_hThreadHome[UNIT_CH];			
	HANDLE	m_hThreadReady[UNIT_CH];			
	HANDLE m_hThreadAutoFocus[UNIT_CH];
	//매뉴얼 동작 kdu 151123
	HANDLE m_hThreadManualFocus[UNIT_CH];

	//스레드 종료시점
	bool bThreadHomeAll[UNIT_CH];
	bool bThreadHome[UNIT_CH];
	bool bThreadReady[UNIT_CH];
	bool m_bThreadAutoFocus[UNIT_CH];
	//kdu 매뉴얼 동작 151123
	bool m_bThreadManualFocus[UNIT_CH];


	void func_AutoProcStop(int iUnit);			//! 자동모드 정지

	bool AutoMode_Process(int iUnit);	
	bool ManualMode_Process(int iUnit);

	int HomeAllProcess_UNIT1(int iUseStep);		//전체원점
	int HomeAllProcess_UNIT2(int iUseStep);

	int ReadyAllProcess_UNIT1(int iUseStep);	//운전 준비
	int ReadyAllProcess_UNIT2(int iUseStep);

	int HomeSingleProcess_UNIT1(int iUseStep);	//개별 원점
	int HomeSingleProcess_UNIT2(int iUseStep);

};//! class AxlMotorSet

DWORD ThreadHomeProcessAA1(AxlMotorSet* pAxlMotorSet);	
DWORD ThreadHomeProcessAA2(AxlMotorSet* pAxlMotorSet);	

DWORD Thread_HomeReadyProcess1(AxlMotorSet* pAxlMotorSet);	
DWORD Thread_HomeReadyProcess2(AxlMotorSet* pAxlMotorSet);		

DWORD Thread_ReadyProcess1(AxlMotorSet* pAxlMotorSet);	
DWORD Thread_ReadyProcess2(AxlMotorSet* pAxlMotorSet);		