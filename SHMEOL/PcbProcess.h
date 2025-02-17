#pragma once
class CPcbProcess
{
public:
	CPcbProcess(void);
	~CPcbProcess(void);

public:
	void SetUnit(int nUnit){ m_nUnit = nUnit;}

	//EOL
	int HomeProcess(int nStep);					//  원점(10000 ~ 20000)
	int AutoReadyProcess(int nStep);			//  운전준비(20000 ~ 30000)
	//-------------------------------------------------------------------------------------------------------------------
	int Auto_M_PCBLoading(int nStep);			//  MAIN -> PCB 로딩            (30000 ~ 40000)					  		
	int AutoPcbSensorAlign(int nStep);			//  그립전 Lens Holder Align	(40000 ~ 50000)
	int AutoPcbLaser(int nStep);				//  Pcb 완제품 검사시 Laser		(50000 ~ 60000)
	int Auto_OC_Insp(int nStep);				//	이물검사					(60000 ~ 70000)
    int AutoChartInsp(int nStep);			    //  CHART검사					(80000 ~ 90000)
	int AutoEOLFinalSFR(int nStep);				//  Final SFR					(110000 ~ 120000)
	
	//OQA
	int OqaHomeProcess(int nStep);					//  원점					(10000 ~ 20000)
	int OqaAutoReadyProcess(int nStep);				//  운전준비				(20000 ~ 30000)
	int OqaAuto_M_PCBLoading(int nStep);			//  MAIN -> PCB 로딩            (30000 ~ 40000)			
	int OqaAuto_OC_Insp(int nStep);					//	이물검사				(60000 ~ 70000)
	int OqaAutoEOLFinalSFR(int nStep);				//  Final SFR				(110000 ~ 120000)
	//-------------------------------------------------------------------------------------------------------------------
	//AA
	int AutoChartMoving(int nStep);				//  Pcb , Lens 동시 Chart이동		(60000 ~ 70000)
	int AutoFocus(int nStep);					//  AA(60000 ~ 70000)
	int AutoUV(int nStep);						//  UV(70000 ~ 80000)		
	int AutoLensLoading(int nStep);				//  Lens Loading					(50000 ~ 60000)
	
	

	//EOL
	int AutoEpoxyLensLaser(int nStep);				//  Pcb Epoxy , Lens Laser동시		(60000 ~ 70000)
	int HomeProcess_IMAGE(int nStep);			//  원점(10000 ~ 20000)	화상장비
	int Auto_DarkImage_Get(int nStep);			//90000 ~ 99000
	//완제품검사

	int AutoBrightInsp(int nStep);			//이물광원 밝기 검사 (SATURATION , IR FILTER)




	int AutoPcbAlign(int nStep);				//  Holder Align                (40000 ~ 50000)
	int AutoPcbBcr(int nStep);					//  Holder BCR                (50000 ~ 60000)
    int AutoPcbLaserTilt(int nStep);			//  LaserTilt->Holder Align     (50000 ~ 60000)		//사용 XXXXXXXXXXXXX
    //
    int AutoDarkInsp(int nStep);			    //  Dark 검사     (60000 ~ 70000)
    int AutoOC6500KInsp(int nStep);			    //  Defect , stain,RI,Color Uniformity, R/C,B/C,Cr/Cb 검사     (70000 ~ 80000)
    //

	

    //
	//ColorSensitivity = 검사만 5000k , 6500k 
	//
	

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

