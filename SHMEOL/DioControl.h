#pragma once

#include <afxmt.h>

#define MAX_DIO_COUNT		2
#define MAX_DIO_BYTE_COUNT		1
#define	MAX_WAIT_TIME		3000

class CDioControl
{
public:
	CDioControl(void);
	~CDioControl(void);

public:
	bool InitDio();
	void CloseDio();

	bool ReadDIn(int nModuleNo);

	int ReadBitIn(int nModuleNo, int noffset);

	bool eZiReadIn(int nModuleNo);
	int eZiReadOut(int nModuleNo, int noffset);
	bool eZiWriteOut(int nModuleNo, DWORD dwOut, DWORD dwCurOut);


	bool ReadDOut(int nModuleNo);
	bool WriteDOut(int nModuleNo, DWORD dwOut);
	bool ByteWriteDOut(int nModuleNo, int nOffset, DWORD dwOut);
	bool ReadByteOut(int nModuleNo, int nOffset);





public:
	DWORD GetDIn(int nIndex){ return m_dwDIn[nIndex];}
	DWORD GetDOut(int nIndex){ return m_dwDOut[nIndex];}

	DWORD GetEziIn(int nIndex) { return ezSInput[nIndex]; }
	DWORD GetEziOut(int nIndex);

	DWORD GetByteOut(int module, int nIndex) { return m_dByteDOutArr[module][nIndex]; }

public:
	int GetDoorState();
	bool SetTowerLamp(int nType, bool bOn);
	bool SetBuzzer(int nType);
	bool DoorUnLock(int index, bool flag);
	bool GetDoorUnLockState();
public:
	
	bool PcbSensorCheck(int nUnit, bool bWait = false);							// PCB 소켓에 제품있는지 감지

	bool LensGrip(int nUnit, bool bFlag, bool bWait = false);					// LENS GRIP / UNGRIP
	bool LensGripCheck(int nUnit, bool bFlag, bool bWait = false);				// LENS GRIP / UNGRIP  감지

	bool PcbSocketUp(int nUnit, bool bFlag, bool bWait = false);				// PCB SOCKET UP / DOWN
	bool PcbSocketUpCheck(int nUnit, bool bFlag, bool bWait = false);			// PCB SOCKET UP / DOWN 감지

	//bool PcbSocketFor(int nUnit, bool bFlag, bool bWait = false);				// PCB SOCKET FOR / BACK
	//bool PcbSocketForCheck(int nUnit, bool bFlag, bool bWait = false);		// PCB SOCKET FOR / BACK 감지

	bool LensBufferVacuumOn(int nUnit, bool bFlag, bool bWait = false);			// LENS BUFFER 흡착 / 탈착
	bool LensBufferVacuumOnCheck(int nUnit, bool bFlag, bool bWait = false);	// LENS BUFFER 흡착 / 탈착 감지
	bool LensBufferSensorCheck(int nUnit, bool bFlag, bool bWait = false);		// LENS BUFFER 센서 감지

	//
	bool ContactUp(int nUnit, bool bFlag, bool bWait = false);					// 컨택 UP / DOWN
	bool ContactUpcheck(int nUnit, bool bFlag, bool bWait = false);				// 컨택 UP / DOWN 감지

public:
	//------------ezio
	//bool EziPcbSocketFor(int nUnit, bool bFlag, bool bWait = false);			// PCB SOCKET FOR / BACK
	//bool EziPcbSocketForCheck(int nUnit, bool bFlag, bool bWait = false);		// PCB SOCKET FOR / BACK 감지

	//bool EziOcUp(int nUnit, bool bFlag, bool bWait = false);					// 이물광원 FOR / BACK
	//bool EziOcUpCheck(int nUnit, bool bFlag, bool bWait = false);				// 이물광원 FOR / BACK 감지

	//bool EziVacuumOn(int nUnit, bool bFlag, bool bWait = false);				// 흡착/탈착
	//bool EziVacuumOnCheck(int nUnit, bool bFlag, bool bWait = false);			// 흡착/탈착 감지

	//bool EziStartBtnLedOn(int nUnit, bool bFlag, bool bWait = false);			// start button led
	//bool EziStartBtnOnCheck(int nUnit,  bool bWait = false);

	//bool EziVacuumBtnLedOn(int nUnit, bool bFlag, bool bWait = false);			// Vacuum button led
	//bool EziBuzzerOn(int nUnit, bool bFlag, bool bWait = false);				// Buzzer

	//bool EziPcbCheck(int nUnit);												// 제품 감지
	//bool EziVacuumBtnCheck(int nUnit);
	//bool EziLightCurtainCheck(int nUnit);										// Light Curtain 감지

	//bool EziSetEziTowerLamp(int nUnit, int nType, bool bOn);					//TowerLamp


public:

	bool SetBuzzer(bool bOn, int nType = 3);

	bool EpoxyDischargeOn(int nUnit, bool bFlag, bool bWait = false);	//EPOXY 도포

	bool PcbVacuum(int nUnit, bool bFlag, bool bWait = false);			// PCB 흡착/탈착
	bool PcbVacuumCheck(int nUnit, bool bFlag, bool bWait = false);		// PCB 흡착/탈착 감지

	bool PcbStopButtonCheck(int nUnit, bool bFlag, bool bWait = false);		// PCB 정지 버튼 감지
	
	bool PcbGrip(int nUnit, bool bFlag, bool bWait = false);			// PCB Grip 전진/후진
	bool PcbGripCheck(int nUnit, bool bFlag, bool bWait = false);		// PCB Grip 전진/후진 감지

	bool LensSocketCheck(int nUnit, bool bWait = false);	// LENS 제품 확인

	bool Stop_Button_LedOn(int nUnit, bool bFlag, bool bWait = false);
	bool Start_Button_LedOn(int nUnit, bool bFlag, bool bWait);

	bool CurtainUpDown(int nUnit, bool bFlag, bool bWait = false);
	bool CurtainUpDownCheck(int nUnit, bool bFlag, bool bWait = false);


	bool DarkPusher(int nUnit, bool bFlag, bool bWait = false);			// Dark Pusher 상승/하강
	bool DarkPusherCheck(int nUnit, bool bFlag, bool bWait = false);	// Dark Pusher 상승/하강 감지

	bool UVShutter(int nUnit, bool bFlag, bool bWait = false);			// UV Shutter Open/Close

	bool LGDoorSignalOn(bool bOn);

	bool UVOn(int nUnit, bool bFlag, bool bWait = false);				// UV 조명 On/Off
	bool StartBbCheck(int nUnit, bool bWait = false);		// 스타트 버튼 Press 체크
	bool DoorBbCheck(int nUnit, bool bWait);
	bool CurtainDoorCheck(int nUnit, bool bWait = false);
	
	//
	bool UVOnCheck(int nUnit, bool bFlag, bool bWait = false);			// UV 조명 On/Off 감지


	bool UVShutterCheck(int nUnit, bool bFlag, bool bWait = false);		// UV Shutter Open/Close 감지

	bool UVErrorCheck(int nUnit, bool bFlag, bool bWait = false);		// UV Error 감지
	bool UVReadyCheck(int nUnit, bool bFlag, bool bWait = false);		// UV Ready 감지
	bool UVApertureCheck(int nUnit, bool bFlag, bool bWait = false);	// UV 조리개 MAX/MIN 감지
	bool UVUseTimeCheck(int nUnit, bool bFlag, bool bWait = false);		// UV Use Time Check
	
	bool LensStageGrip(int nUnit, bool bFlag, bool bWait = false);		// LENS Stage Grip 전진/후진
	bool LensStageGripCheck(int nUnit, bool bFlag, bool bWait = false);	// LENS Stage Grip 전진/후진 감지
	bool FeedMove(int nUnit, bool bFlag, bool bWait = false);			// 검사 FEED 전진/후진
	bool FeedMoveCheck(int nUnit, bool bFlag, bool bWait = false);		// 검사 FEED 전진/후진 감지
	bool PcbGripUp(int nUnit, bool bFlag, bool bWait = false);			// PCB Grip 상승/하강
	bool PcbGripUpCheck(int nUnit, bool bFlag, bool bWait = false);		// PCB Grip 상승/하강 감지
	bool PcbSocketVacuumCheck(int nUnit, bool bFlag, bool bWait = false);		// PCB 제품 확인

public:
	DWORD m_dwDIn[MAX_DIO_COUNT];
	DWORD m_dwDOut[MAX_DIO_COUNT];

	DWORD ezSInput[2];
	DWORD ezSOutput[2];

	CCriticalSection m_clByteCriticalSection[MAX_DIO_BYTE_COUNT][4];
	DWORD m_dByteDOutArr[MAX_DIO_BYTE_COUNT][4];
	CMutex m_clMutexWrite;
};


