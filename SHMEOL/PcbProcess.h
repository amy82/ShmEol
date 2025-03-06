#pragma once
class CPcbProcess
{
public:
	CPcbProcess(void);
	~CPcbProcess(void);

public:
	void SetUnit(int nUnit){ m_nUnit = nUnit;}

	//EOL
	int HomeProcess(int nStep);					//  ����(10000 ~ 20000)
	int AutoReadyProcess(int nStep);			//  �����غ�(20000 ~ 30000)
	//-------------------------------------------------------------------------------------------------------------------
	int Auto_M_PCBLoading(int nStep);			//  MAIN -> PCB �ε�            (30000 ~ 40000)					  		
	int AutoPcbSensorAlign(int nStep);			//  �׸��� Lens Holder Align	(40000 ~ 50000)
	int AutoPcbLaser(int nStep);				//  Pcb ����ǰ �˻�� Laser		(50000 ~ 60000)
	int Auto_OC_Insp(int nStep);				//	�̹��˻�					(60000 ~ 70000)
    int AutoChartInsp(int nStep);			    //  CHART�˻�					(80000 ~ 90000)
	int AutoEOLFinalSFR(int nStep);				//  Final SFR					(110000 ~ 120000)
	
	//-------------------------------------------------------------------------------------------------------------------
	//AA
	int AutoChartMoving(int nStep);				//  Pcb , Lens ���� Chart�̵�		(60000 ~ 70000)
	int AutoFocus(int nStep);					//  AA(60000 ~ 70000)
	int AutoUV(int nStep);						//  UV(70000 ~ 80000)		
	int AutoLensLoading(int nStep);				//  Lens Loading					(50000 ~ 60000)
	
	
	bool nRunOnlineControlState;		//true = Online , false = Offline 
	int nRunTimeOutSec;			//Default = 60;
	int nLotProcessingComplete_ACK;
	//g_clMesCommunication[m_nUnit].ConversationTimeoutCount
	//
	int VaccumRetry;
	bool m_nDiffTestOk;
private:
	bool CheckDecreaseSFR();
	bool GetSfrMaxPos();
private:
	int mOcLightChannel;
	int mLightRetry;
	bool m_bHomeProc;
	bool m_bHomeError;	
	int m_nUnit;
	bool m_bFlagSocketReq;
	int	m_nSocketCnt;
	DWORD m_dwDelayCount;
	int m_nBCR_Recount;
	double m_dBCR_Error_Offset;
	CString m_strCalTotalResult;
	CString m_strCalResult;
	CString sSendMsg;

	int nDiffRetry;

	int rawSumCount;
	int TestPatternRetry;
	int VarRetry;
};

