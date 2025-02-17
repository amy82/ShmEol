#pragma once


//! 1] 아진엑스텍 Motion Controller는 위치 제어만 지원한다. 하지만, AxmMoveVel 처럼 일정한 속도로 움직이는 기능을 제공한다. 
//! 2] RTEX 제품 (PCI-R1604)에서는 Interrupt, Software Limit을 지원하지 않는다. 
//! 3] 서보 부하율을 알 수 있는 기능은 없다. 
//! 4] PCI-R1604 A4N, A5N의 경우 비상정지 입력단이 존재하지 않는다.
//!     (모션 모듈에 있는 비상정지 입력단 으로 신호를 넣게 되며 신호가 들어오면 ESTOP을 자동으로 내려 모든 모션에 대해서 정지)

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
		dVel = input.dVel;
		dAccel = input.dAccel;

		bEndLimit_Positive = input.bEndLimit_Positive;
		bEndLimit_Negative = input.bEndLimit_Negative;
		bHomeSensor = input.bHomeSensor;
		bPhase_Encoder_Z = input.bPhase_Encoder_Z;

		bEdge_Down = input.bEdge_Down;
		bEdge_Up = input.bEdge_Up;

		bEmergency = input.bEmergency;
		bSlowDown = input.bSlowDown;

		return *this;
	}
};//! struct strMove_Input_Signal_Search



class CAxlMotorSet
{
public:
	CAxlMotorSet();
	~CAxlMotorSet();


public:
	DWORD m_dwMotorTickCount;

	bool Axl_Init();
	void Axl_Close();
	int  Axl_Axisconfig(int nUnit);

	bool ReadBit(int nUnit, int nAxis, int nBit);

	bool AmpEnable(int nUnit, int nAxis);
	bool AmpEnableAll(int nUnit);
	bool AmpDisable(int nUnit, int nAxis);
	bool AmpDisableAll(int nUnit);
	bool GetAmpEnable(int nUnit, int nAxis);
	bool GetAmpEnableAll(int nUnit);

	bool GetOrgFlagAll(int nUnit);

	bool AmpFaultReset(int nUnit, int nAxis);
	bool AmpFaultResetAll(int nUnit);
	int	 AmpFaultCheck(int nUnit);
	bool GetAmpFault(int nUnit, int nAxis);
	bool GetServoOn(int nUnit, int nAxis);
	
	bool GetInposition(int nUnit, int nAxis);

	bool GetPcbYMotorPosCheck(int nUnit, int dPos);				//PCB Y 축 위치 확인
	bool GetPcbXYMotorPosCheck(int nUnit, int dPos);			//PCB X,Y 축 위치 확인
	bool GetPcbZMotorPosCheck(int nUnit, int dPos);				//PCB Z 축 위치 확인
	bool GetLensXYMotorPosCheck(int nUnit, int dPos);			//LENS X,Y 축 위치 확인
	bool GetLensZMotorPosCheck(int nUnit, int dPos);			//LENS Z 축 위치 확인
	bool GetHomeSensor(int nUnit, int nAxis);
	bool GetNegaSensor(int nUnit, int nAxis);
	bool GetPosiSensor(int nUnit, int nAxis);
	void InitialPos(int nUnit, int nAxis);

	bool ActCRC(int nUnit, int nAxis);

	bool GetStopAxis(int nUnit, int nAxis);
	bool StopAxis(int nUnit, int nAxis);
	bool StopAxisAll(int nUnit);

	double GetEncoderPos(int nUnit, int nAxis);
	double GetEncoderPos_Disp(int nUnit, int nAxis);

	double GetCommandPos(int nUnit, int nAxis);
	double GetCommandPos_Disp(int nUnit, int nAxis);
	double GetDDMotorPos(int nUnit, int nAxis);
	double GetDDMotorPos_Disp(int nUnit, int nAxis);
	double GetActPos(int nUnit, int nAxis);
	double GetEncoderPulse(int nUnit, int nAxis);
	double GetCommandPulse(int nUnit, int nAxis);

	void SetEncoderPos(int nUnit, int nAxis, double dPos);
	void SetCommandPos(int nUnit, int nAxis, double dPos);
	void SetDDMotorCalcPos(int nUnit, int nAxis, double dMaxDeg);
	void SetDDMotorPos(int nUnit, int nAxis, double dPos);
	double CalcAccFromAccTime(double dVel, double dTime);

	//bool SetJogSpeed(int iID_GUI, CWnd* pParentWnd, double *pOutSpeedGain);
	bool JogMove(int nUnit, int nAxis, double dVel);
	bool JogStop(int nUnit, int nAxis);

	//bool MoveAxis_To_Sensor(int nAxis, strMove_Input_Signal_Search *pstrInput);

	//bool Move_From_GUI(int axis, int iID_GUI, CWnd* pParentWnd, bool bPlus = true);	//! GUI 화면에서 설정한 길이만큼 움직인다. (상대 이동)
	bool MoveFromAbsRel(int nUnit, int nAxis, double dPos, bool bPlus);

	bool MoveAxis(int nUnit, int nAxis, int nAbsFlag, double dPos, double dVel, bool bWait = false);
	bool MoveAxis(int nUnit, int nAxis, int nAbsFlag, double dPos, double dVel, double dAcc);
	//
	//직선,곡선 연속 도포
	bool MoveStraightPcbXYAxis(int nUnit);
	//곡선 도포
	bool MoveCirclePcbXYAxis(int nUnit, int dPos);// , double dAngle, double dVel, double dAcc);
	//
	//bool MoveAxisComplete(int nAxis, int nAbsFlag, double dPos, double dVel, bool bWait = true);
	bool MoveAxisComplete(int nUnit, int nAxis, int nAbsFlag, double dPos, double dVel, int nSpeed, bool bWait = true, double dParamAcc = 0.0, double dParamDec = 0.0); //20161101
	bool MoveAxisMulti(int nUnit, int nAxisCnt, int nAxis[MAX_MOTOR_COUNT], double dPos[MAX_MOTOR_COUNT]);
	bool MoveAxisMulti(int nUnit, int nAxisCnt, int nAxis[MAX_MOTOR_COUNT], double dPos[MAX_MOTOR_COUNT], int nSpeed);
	bool MoveAxisMulti(int nUnit, int nAxisCnt, int nAxis[MAX_MOTOR_COUNT], double dPos[MAX_MOTOR_COUNT], double dSpeed);
	//bool MoveAxisMulti(int nAxisCnt, int nAxis[MAX_MOTOR_COUNT], double dPos[MAX_MOTOR_COUNT], double dSpeed, bool bWait = true);
	bool MoveAxisMulti(int nUnit, int nAxisCnt, int nAxis[MAX_MOTOR_COUNT], double dPos[MAX_MOTOR_COUNT], double dVel[MAX_MOTOR_COUNT], double dAcc[MAX_MOTOR_COUNT], double dDec[MAX_MOTOR_COUNT]);

	bool MoveAxisLimit(int nUnit, int nAxis, double dVel, double dAcc, int nLimit, int nSignal, int nStopMode);
	bool GetResultHomeSearch(int nUnit, int nAxis, CString &szResult);
	int IsCompletedHomeSearch(int nUnit, int nAxis);
	int GetHomeSearchRate(int nUnit, int nAxis);

	DWORD SetHomeSearchSpeed(int nAxis);
	bool StartHomeSearch(int nUnit, int nAxis);
	void StopHomeSearch(int nUnit, int nAxis);

	double GetAccel_Cal(int nUnit, int nAxis, double dSec);

	//bool HomeProcess(int nAxis, int nHomeDir);
	//bool HomeProcessAll();

	bool GetHomeState(int nUnit);
	bool GetHomeState(int nUnit, int nAxis);
	bool GetAmpFaultState(int nUnit);


	// AA PCB 축 이동
	bool MovePcbTMotor(int nUnit, double dOffsetTh /*= 0.0*/, bool bWait /*= false*/);
	bool MovePcbYMotor(int nUnit, int nPosi, double dOffsetY = 0.0, bool bWait = false);
	bool MovePcbYTMotor(int nUnit, int nPosi, double dOffsetY = 0.0, double dOffsetTh = 0.0, bool bWait = false, bool bManual = false);
	bool MovePcbYTMotor(int nUnit, double dOffsetY = 0.0, double dOffsetTh = 0.0, bool bWait = false);

	bool MovePcbXYMotor(int nUnit, int nPosi, double dOffsetX = 0.0, double dOffsetY = 0.0, bool bWait = false, bool bManual = false);

	bool MovePcbXYTMotor(int nUnit, int nPosi, double dOffsetX = 0.0, double dOffsetY = 0.0, double dOffsetTh = 0.0, bool bWait = false , bool bManual = false);
	bool MovePcbXYTMotor(int nUnit, double dOffsetX = 0.0, double dOffsetY = 0.0, double dOffsetTh = 0.0, bool bWait = false);
	bool MovePcbXTMotor(int nUnit, int nPosi, double dOffsetX = 0.0, double dOffsetTh = 0.0, bool bWait = false);
	bool MovePcbXTMotor(int nUnit, double dOffsetX = 0.0, double dOffsetTh = 0.0, bool bWait = false);


	bool MovePcbZMotor(int nUnit, int nPosi, double dOffsetZ = 0.0, bool bWait = false, bool bManual = false);
	bool MovePcbZMotor(int nUnit, double dPos, bool bWait = false);
	bool MovePcbZMotorComplete(int nUnit, double dOffsetZ = 0.0, double dVel = 0.1, double dAcc = 0.1);
	bool MovePcbTxTyMotor(int nUnit, int nPosi, double dOffsetTx = 0.0, double dOffsetTy = 0.0, bool bWait = false);
	bool MovePcbTxTyMotor(int nUnit, double dOffsetTx = 0.0, double dOffsetTy = 0.0, bool bWait = false);

	// AA LENS 축 이동
	bool MoveLensXYMotor(int nUnit, int nPosi, double dOffsetX = 0.0, double dOffsetY = 0.0, bool bWait = false);
	bool MoveLensXYMotor(int nUnit, double dOffsetX = 0.0, double dOffsetY = 0.0, bool bWait = false);

	bool MoveLensXMotor(int nUnit, int nPosi, double dOffsetX = 0.0, bool bWait = false);
	bool MoveLensYMotor(int nUnit, int nPosi, double dOffsetY = 0.0, bool bWait = false);
	bool MoveLensZMotor(int nUnit, int nPosi, double dOffsetZ = 0.0, bool bWait = false);
	bool MoveLensZMotor(int nUnit, double dOffsetZ = 0.0, double dVel = 0.1, bool bWait = false);
	bool MoveLensZMotorComplete(int nUnit, double dOffsetZ = 0.0, double dVel = 0.1, double dAcc = 0.1);
	bool MoveLensTxTyMotor(int nUnit, int nPosi, double dOffsetTx = 0.0, double dOffsetTy = 0.0, bool bWait = false);
	bool MoveLensTxTyMotor(int nUnit, double dOffsetTx = 0.0, double dOffsetTy = 0.0, bool bWait = false);

	bool MoveLensZAAMotor(int nUnit, double dPos, double dOffsetZ = 0.0, bool bWait = false);

	bool MoveLensZMotorCompleteAA(int nUnit, double dOffsetZ = 0.0, double dVel = 0.1, double dAcc = 0.1);


	//EPOXY 
	bool Epoxy_Rect_Circle_Draw(int nUnit);		//사각 , 원 포함 도포
	bool Epoxy_Circle_Draw(int nUnit);			//원도포
	bool Epoxy_Rect_Draw(int nUnit);				//사각도포
	bool MovePcbDispenseStraightLineMotor(int nUnit, int nAxis, int bAbsFlag, double dPos, double dVel, double dAcc, bool bWait = false);
	//func_Epoxy_Rect_Circle_Draw();



private:
	//! 해당 절대 경로의 파일에 Motion Board의 설정값을 파일로 저장 가능
	CString m_sMotionSettingFilePath;

public:
	bool m_bOrgFlag[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];
	bool m_bMotorMoving[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];
	bool m_bJogPlusFlag[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];
	bool m_bJogMinusFlag[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];
	bool m_bOldJogPlusFlag[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];
	bool m_bOldJogMinusFlag[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];

	int	m_nHomeProcUsing[MAX_UNIT_COUNT][MAX_MOTOR_COUNT];

	bool m_bAxlInitResult;

	bool m_bOqaOrgFlag;
};

