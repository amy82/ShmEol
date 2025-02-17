
// CAutoInspDlg.h : 헤더 파일
//

#pragma once

#include "Utility\GraphCtrl\Graph2DWnd.h"
#include "Utility\ButtonEx\ButtonEx.h"
#include "Utility\ButtonEx\ButtonCT.h"
#include "Utility\Label\Label.h"
#include "ManualDlg.h"
#include "TeachingDlg.h"
#include "CcdDlg.h"
#include "DioDlg.h"
#include "LightDlg.h"
#include "AlarmDlg.h"
#include "ConfigDlg.h"
#include "VisionStatic.h"
#include "resource.h"
#include "afxwin.h"
#include "ClockThread.h"
#include "FileThread.h"
#include "LogThread.h"
#include "CustomThread.h"
#include "LensAxisThread.h"
#include "MonitorThread.h"
#include "SerialThread.h"
#include "ActiveAlignThread.h"
#include "CcdGrabThread.h"
#include "CcdCvtColorThread.h"
#include "AgentConnSocket.h"
#include "AgentListenSocket.h"
#include "MesConnSocket.h"
#include "InspConnSocket.h"
#include "ProductNGDlg.h"
#include "UpdateHistoryDlg.h"
#include "resource.h"
#include "CeepromData.h"
#include "VisionGrabThread.h"
#include "ModelSelectDlg.h"
#include "InterLockDlg.h"

// CAutoInspDlg 대화 상자
class CAutoInspDlg : public CDialogEx
{
// 생성입니다.
public:
    CAutoInspDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_INSP_DIALOG};
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
    CManualDlg m_clManualDlg;
    CTeachingDlg m_clTeachingDlg;
    CCcdDlg m_clCcdDlg;
    CDioDlg m_clDioDlg;
    CLightDlg m_clLightDlg;
    CAlarmDlg m_clAlarmDlg;
    CConfigDlg m_clConfigDlg;
    CProductNGDlg m_clProductNGDlg[MAX_UNIT_COUNT];
   // CUpdateHistoryDlg m_clUpdateHistoryDlg;
	//CModelSelectDlg m_clModelSelectDlg;

    CClockThread m_clClockThread;
	CFileThread m_clFileThread;
    CMonitorThread m_clMonitorThread;
    CSerialThread m_clSerialThread;
	CCustomThread m_clCustomThread[MAX_UNIT_COUNT];
    CActiveAlignThread m_clActiveAlignThread[MAX_UNIT_COUNT];
    CCcdGrabThread m_clCcdGrabThread[MAX_UNIT_COUNT];
    CCcdCvtColorThread m_clCcdCvtColorThread[MAX_UNIT_COUNT];
	CVisionGrabThread m_clVisionGrabThread[MAX_UNIT_COUNT];

	CLogThread m_clLogThread;
	//CLensAxisThread m_clLensAxisThread[MAX_UNIT_COUNT];
private:
	bool m_bMesConnect;

	CMesConnSocket m_clMesConnSocket;
public:
    CLabel m_clColorStaticBcr[2];
    CLabel m_clColorStaticOutput[2];
    CLabel m_clColorStaticPin[2];
    CLabel m_clColorStaticFps[2];
    //
    CLabel m_clColorStaticTitle[2];
    CLabel m_clColorStaticVersion[2];
    CLabel m_clColorStaticModelNo[2];
    CLabel m_clColorStaticLotID[2];
    CLabel m_clColorStaticCcdID[2];
	CLabel m_clColorStaticCurrMode[2];
	CLabel m_clColorStaticCurrAlignMode[2];
	
    
    CLabel m_clColorStaticBcrVal[2];
    CLabel m_clColorStaticOutputVal[2];
    CLabel m_clColorStaticPinVal[2];
    CLabel m_clColorStaticFpsVal[2];
	CLabel m_clColorStaticPcbType[2];

	//운전 메뉴
	CButtonCT m_clColorButtonStartingPoint[2];
	CButtonCT m_clColorButtonAutoReady[2];
	CButtonCT m_clColorButtonAutoRun[2];
	CButtonCT m_clColorButtonComplOk[2];
	CButtonCT m_clColorButtonComplEmission[2];
	CButtonCT m_clColorButtonAutoStop[2];
	CButtonCT m_clColorButtonAutoPause[2];
	CButtonCT m_clColorButtonComplNg[2];
    
	//마스터샘플 모드
	CButtonCT m_clColorButtonMasterMode[2];

	//도포완료 
	CButtonCT m_clColorButtonEpoxyCompl[2];

	//LENS 넘김 완료
	CButtonCT m_clColorButtonLensLoading[2];
	
	// MODEL SELECT 
	CButtonCT m_clColorButtonModelSelect;

	//하단 메뉴
	CButtonCT m_clColorButtonUnitChange;
    CButtonCT m_clColorButtonMain;
    CButtonCT m_clColorButtonManual;
    CButtonCT m_clColorButtonTeaching;
    CButtonCT m_clColorButtonCcd;
    CButtonCT m_clColorButtonDio;
    CButtonCT m_clColorButtonLight;
	CButtonCT m_clColorButtonAlarm;
	CButtonCT m_clColorButtonConfig;
    CButtonCT m_clColorButtonMinimize;
    CButtonCT m_clColorButtonExit;
	//통신
	CButtonCT m_clButtonExLan;
	CButtonCT m_clButtonExInspLan;
	//CCD
	CButtonCT m_clButtonExLink[2];
	CButtonCT m_clButtonExCcd[2];
	//MES
	CButtonCT m_clButtonMes[2];
	//CAM
	CButtonCT m_clButtonCAMChange[2];
	CButtonCT m_clButtonCCDChange[2];
	//DOOR
	CButtonCT m_clButtonExDoor[2];
	CButtonCT m_clButtonExArea[2];
	
	//
    CLabel m_clColorStaticCurrentDate;
    CLabel m_clColorStaticCurrentTime;
    
	CLabel m_clColorStaticAA_Input[2];
	CLabel m_clColorStaticAA_Output[2];
    
    CListBox m_clListLog[2];
	CVisionStatic m_clVisionStaticCcd[2];
	CVisionStatic m_clVisionStaticCam[2];
    CLabel m_clColorStaticMsg;


private:
	void InitializeService();
	void PrintVersionInfo();

    void FinishService();
    void CreateSubDlg();
    void SetCtrlPos();
    void InitCtrl();
    void MakeGraphWnd();
    void ReleaseGraphWnd();

    void InitMilLib();
    void InitMotorLib();
    void InitDioLib();
    void InitGrabberLib();
    void InitSocket();

    void ShowDialog(int nDlg);

    bool CreateListenSocket();
    void CloseAllSocket();

	void InformationState();
	bool SkipLog(CString strLog);

public:
	bool m_bMasterModeState[2];
	int m_bCamState[2];
private:
    CFont m_clFontBig;
    CFont m_clFontMid;
	CFont m_clFontSmall;
	CFont m_clFontBcrSmall;
    CFont m_clListFontSmall;
    CGraph2DWnd* m_pGraphWnd[MAX_UNIT_COUNT][MAX_GRAPH_COUNT];
    //! 그래프 입력 데이터 버퍼	
    double m_dDataX[MAX_UNIT_COUNT][MAX_GRAPH_COUNT][MAX_GRAPH_OVERLAP_COUNT][MAX_GRAPH_PIXEL_SIZE];
    double m_dDataY[MAX_UNIT_COUNT][MAX_GRAPH_COUNT][MAX_GRAPH_OVERLAP_COUNT][MAX_GRAPH_PIXEL_SIZE];
    int    m_nDataSize[MAX_UNIT_COUNT][MAX_GRAPH_COUNT][MAX_GRAPH_OVERLAP_COUNT];
    //bool   m_bFlagVisible[MAX_UNIT_COUNT][MAX_GRAPH_COUNT][MAX_GRAPH_OVERLAP_COUNT];	//! true이면 그래프를 눈에 보이게 한다.

    CMap<CString, LPCTSTR, CPoint, CPoint&> m_clCtrlPos[MAX_UNIT_COUNT];

    int m_nCurrentUnit;
    int m_nCurrentDlg;
	int m_nSignal[2];
	int m_nModelType;

	int Graph_Width;
	int Graph_Height;

    CAgentConnSocket m_clAgentConnSocket;
    bool m_bConnectMain;
    bool m_bPrevCcdState[2];
    bool m_bPrevLinkState[2];
	
    CAgentListenSocket m_clAgentListenSocket;
    CInspConnSocket* m_pInspConnSocket;
    CPtrList m_clInspSocketList;

    double m_dInspAlignData[3];		// X,Y,T
    double m_dInspInTiltData[2];	// 내부 TILT 
    double m_dInspOutTiltData[2];	// 외부 TILT
public:
    void MoveMainUI(int nType);
    void ShowCurrentDate(TCHAR* szDate);
    void ShowCurrentTime(TCHAR* szTime);
    void ShowCurrentMode(int nUnit);

    void DrawGraph(int nUnit, int nPlot);
    void _DrawBarGraph(int nUnit);
    void DrawBarGraph(int nUnit);
    void DrawCcdFps(int nUnit);

    bool StartHomeProcess(int nUnit);
    bool StartAutoReadyProcess(int nUnit);
    bool StartAutoProcess(int nUnit);
    void PauseAutoProcess(int nUnit);
    bool StopAutoProcess(int nUnit);

    bool GetAAMainConnect() { return m_bConnectMain; }
    bool ConnectAAMain();
    void CloseAAMain();
    void RecvAAMainData(CString sData);
    void ProcessAAMainPacket(int nUnit, int nAANo, CString sCmd, CString sVal);
    bool SendDataToAAMain(int nUnit, CString sData);

	bool LgitLicenseCheck();
    //void AcceptAgentConn();
    //bool IsAcceptableAgent(CAgentConnSocket* pSocket, CString sPeerAddress);
    //void CloseAgentConn(CAgentConnSocket* pSocket, bool bForce);

    void AcceptInspConn();
    bool IsAcceptableInspAgent(CInspConnSocket* pSocket, CString sPeerAddress);
    void CloseInspConn(CInspConnSocket* pSocket, bool bForce);
    void ProcessInspPacket(CString sPacket);
    bool SendDataToInsp(CString sData);

    void ShowHomeState(int nUnit);
    void ShowAutoReadyState(int nUnit);
    void ShowBarcode(int nUnit);
    void ShowOutputCount(int nUnit);
    void ShowPinCount(int nUnit);
    void ShowIconState(int nUnit);
    void ShowOkNgState(int nUnit , int _FINAL);		//_FINAL: 0 = 기본 , 1 = 양품 , 2 = 불량

    bool SendLaserMeasurePacket(int nUnit);

    bool InsertLaserTilt(int nUnit, bool bLaserIn);
    bool InsertAlignData(int nUnit);
    bool SelectAAData(int nUnit, CString sBcr);
	bool InsertEEpromData(int nUnit);
	bool InsertPcbTeachingData(int nUnit);
	bool GetPcbTeachingData(int nUnit);

	void MasterModeChangeHandler(int Unit);
	void CAMChangeHandler(int Unit , int Mode);	
	void EpoxyCompleteChange(int Unit);
	void LensLoadingChange(int Unit);

	bool EpoxyFinddispense(int nIndex);		// 도포검사
	bool InspResignRect(bool autoMode, int index, int iDirection, int iRectCnt, unsigned char *);
	bool InspQuaternHole(bool autoMode, int index, int dispMode, int iCirCnt);

	bool CDP800_Connect();
	bool CurrentPowerOnOff(bool _Work);
	bool InstrRead(CString strAddr, CString *pstrResult);
	bool InstrWrite(CString strAddr, CString strContent);
	bool CurrentInsp();
	CString m_strInstrAddr;
	bool ConnectMes();
	void DisConnectMes();
	
	int m_nAlarmcode;
	int m_nAlarmOccured;

	void SendCMSMESMessage(int message, int mAlarmIndex = 0);

	void versionList();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonMainUnitChange();
	afx_msg void OnBnClickedButtonMainMain();
	afx_msg void OnBnClickedButtonMainManual();
	afx_msg void OnBnClickedButtonMainTeaching();
	afx_msg void OnBnClickedButtonMainCcd();
	afx_msg void OnBnClickedButtonMainDio();
	afx_msg void OnBnClickedButtonMainLight();
	afx_msg void OnBnClickedButtonMainAlarm();
	afx_msg void OnBnClickedButtonMainConfig();
	afx_msg void OnBnClickedButtonMainExit();
    //
    afx_msg void OnBnClickedButtonMainLink1();
    afx_msg void OnBnClickedButtonMainCcd1();
    afx_msg void OnBnClickedButtonMainStartingPoint1();
    afx_msg void OnBnClickedButtonMainAutoReady1();
    afx_msg void OnBnClickedButtonMainAutoRun1();
    afx_msg void OnBnClickedButtonMainComplOk1();
    afx_msg void OnBnClickedButtonMainComplEmission1();
    afx_msg void OnBnClickedButtonMainAutoStop1();
    afx_msg void OnBnClickedButtonMainAutoPause1();
    afx_msg void OnBnClickedButtonMainComplNg1();
    afx_msg void OnBnClickedButtonMainLink2();
    afx_msg void OnBnClickedButtonMainCcd2();
    afx_msg void OnBnClickedButtonMainStartingPoint2();
    afx_msg void OnBnClickedButtonMainAutoReady2();
    afx_msg void OnBnClickedButtonMainAutoRun2();
    afx_msg void OnBnClickedButtonMainComplOk2();
    afx_msg void OnBnClickedButtonMainComplEmission2();
    afx_msg void OnBnClickedButtonMainAutoStop2();
    afx_msg void OnBnClickedButtonMainAutoPause2();
    afx_msg void OnBnClickedButtonMainComplNg2();
    //
    afx_msg void OnBnClickedButtonMainLan();
    afx_msg void OnStnClickedStaticMainOutput1();
    afx_msg void OnStnClickedStaticMainOutput2();
    afx_msg void OnStnClickedStaticMainVersion1();
    afx_msg void OnStnClickedStaticMainVersion2();
    afx_msg void OnStnClickedStaticMainPin1();
    afx_msg void OnStnClickedStaticMainPin2();
    afx_msg void OnStnClickedStaticMainBcrVal1();
    afx_msg void OnStnClickedStaticMainBcrVal2();
    afx_msg void OnBnClickedButtonMainMinimize();
	afx_msg void OnBnClickedButtonMasterChageMode1();
	afx_msg void OnBnClickedButtonMasterChageMode2();
	afx_msg void OnBnClickedButtonMainCamChange1();
	afx_msg void OnBnClickedButtonMainCamChange2();
	afx_msg void OnBnClickedButtonMainCcdChange1();
	afx_msg void OnBnClickedButtonMainCcdChange2();
	afx_msg void OnBnClickedButtonMainMes1();
	afx_msg void OnBnClickedButtonMainMes2();
	afx_msg void OnBnClickedButtonEpoxyComplete1();
	afx_msg void OnBnClickedButtonEpoxyComplete2();
	afx_msg void OnBnClickedButtonLensLoading1();
	afx_msg void OnBnClickedButtonLensLoading2();
	afx_msg void OnBnClickedButtonModelSelct();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnStnClickedStaticMainCurrMode1();
	afx_msg void OnStnClickedStaticMainOutputVal1();
	afx_msg void OnStnClickedStaticMainPinVal1();
	afx_msg void OnStnClickedStaticMainCurrMode3();
	afx_msg void OnBnClickedButtonMainDoor1();
};
