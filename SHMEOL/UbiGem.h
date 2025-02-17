#pragma once



#include "Utility\Label\Label.h"
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <GEMStructure.h>
#include <GEMWrapper.h>



// CUbiGem 대화 상자입니다.

class CUbiGem : public CDialogEx, UbiGEMWrapper::IGEMDriverEvents
{
	DECLARE_DYNAMIC(CUbiGem)

public:
	CUbiGem(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUbiGem();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UBIGEM };
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
private:
	UbiGEMWrapper::GEMWrapper* m_pWrapper;
	CString m_strUgcFileName;
	std::vector<int64_t> m_setAlarmList;
	int m_iAck;

	CFont m_clFontBig;
	CFont m_clFontMid;
	CFont m_clFontSmall;

	CLabel m_clColorStaticControlState;


	CComboBox m_cboEcv;
	CComboBox m_cboV;
	CComboBox m_cboCe;
	CComboBox m_cboUserMessage;
	CComboBox m_cboRcmdView;

	CEdit m_edtProcessState;
	CEdit m_edtAlarmId;
	CEdit m_edtECV;
	CEdit m_edtV;
	CEdit m_edtTId;
	CEdit m_edtTerminalMessage;

	CEdit m_edtAbs;
public:
	void InitCtrl();
	void initUbiGEMSet();
	int UbisamUgcLoad();
	bool EventReportSendFn(CString strCEID, CString parameter = _T(""));
	void AlarmSendFn(int nAlarmID);
	void cTTimeOutSendFn(LPCTSTR strMexp, LPCTSTR strEdId);
	void AlarmClearSendFn();


	void OnMnuInitilaize();	//Initialize
	void OnMnuStart();		//Start
	void OnMnuStop();		//Stop
private:
	int m_nUnit;
	CEdit m_edtLog;
	bool initChk;
	void UbisamAddLog(CString strLog);
	void UbisamAddLog(CString strLog, UbiGEMWrapper::Structure::GEMResult eResult);

	CString strSendCeId;
private:
	void OnGEMConnected(LPCTSTR strIpAddress, int nPortNo);
	void OnGEMDisconnected(LPCTSTR strIpAddress, int nPortNo);
	void OnGEMSelected(LPCTSTR strIpAddress, int nPortNo);
	void OnGEMDeselected(LPCTSTR strIpAddress, int nPortNo);

	void OnSECSTimeout(UbiGEMWrapper::Structure::SECSTimeoutType timeoutType);
	void OnSECST3Timeout(UbiGEMWrapper::Structure::SECSMessage* message);

	void OnInvalidMessageReceived(UbiGEMWrapper::Structure::GEMMessageValidationError error, UbiGEMWrapper::Structure::SECSMessage* message);
	void OnReceivedUnknownMessage(UbiGEMWrapper::Structure::SECSMessage* message);
	int OnReceivedEstablishCommunicationsRequest(LPCTSTR strMdln, LPCTSTR strSofRev);
	void OnReceivedRemoteCommand(UbiGEMWrapper::Structure::RemoteCommandInfo* remoteCommandInfo);
	void OnReceivedInvalidRemoteCommand(UbiGEMWrapper::Structure::RemoteCommandInfo* remoteCommandInfo);
	void OnReceivedEnhancedRemoteCommand(UbiGEMWrapper::Structure::EnhancedRemoteCommandInfo* remoteCommandInfo);
	void OnReceivedInvalidEnhancedRemoteCommand(UbiGEMWrapper::Structure::EnhancedRemoteCommandInfo* remoteCommandInfo);
	void OnReceivedNewECVSend(unsigned int systemBytes, UbiGEMWrapper::Structure::VariableCollection* newEcInfo);
	void OnReceivedLoopback(UbiGEMWrapper::Structure::List<unsigned char>* receiveData);
	void OnReceivedTerminalMessage(unsigned int systemBytes, int tid, LPCTSTR strTerminalMessage);
	void OnReceivedTerminalMultiMessage(unsigned int systemBytes, int tid, UbiGEMWrapper::Structure::List<LPCTSTR>* strTerminalMessages);
	void OnReceivedRequestOffline(unsigned int systemBytes);
	void OnReceivedRequestOnline(unsigned int systemBytes);
	void OnReceivedDefineReport();
	void OnReceivedLinkEventReport();
	void OnReceivedEnableDisableEventReport();
	void OnReceivedEnableDisableAlarmSend();
	bool OnResponseDateTimeRequest(UbiGEMWrapper::Structure::DateTime* timeData);
	void OnResponseLoopback(UbiGEMWrapper::Structure::List<unsigned char>* receiveData, UbiGEMWrapper::Structure::List<unsigned char>* sendData);
	void OnResponseEventReportAcknowledge(LPCTSTR ceid, int ack);
	void OnReceivedPPLoadInquire(unsigned int systemBytes, LPCTSTR ppid, int length);
	void OnReceivedPPSend(unsigned int systemBytes, LPCTSTR ppid, UbiGEMWrapper::Structure::List<unsigned char>* ppbody);
	void OnReceivedFmtPPSend(unsigned int systemBytes, UbiGEMWrapper::Structure::FmtPPCollection* fmtPPCollection);
	void OnResponsePPLoadInquire(int ppgnt, LPCTSTR ppid);
	void OnResponsePPSend(int ack, LPCTSTR ppid);
	void OnResponsePPRequest(LPCTSTR ppid, UbiGEMWrapper::Structure::List<unsigned char>* ppbody);
	void OnResponseFmtPPSend(int ack, UbiGEMWrapper::Structure::FmtPPCollection* fmtPPCollection);
	void OnResponseFmtPPRequest(UbiGEMWrapper::Structure::FmtPPCollection* fmtPPCollection);
	void OnResponseFmtPPVerification(UbiGEMWrapper::Structure::FmtPPVerificationCollection* fmtPPVerificationCollection);
	void OnResponseTerminalRequest(int ack);
	void OnReceivedDateTimeRequest(unsigned int systemBytes, UbiGEMWrapper::Structure::DateTime* timeData);
	void OnReceivedDateTimeSetRequest(unsigned int systemBytes, UbiGEMWrapper::Structure::DateTime* timeData);
	void OnReceivedPPRequest(unsigned int systemBytes, LPCTSTR ppid);
	void OnReceivedFmtPPRequest(unsigned int systemBytes, LPCTSTR ppid);
	void OnReceivedDeletePPSend(unsigned int systemBytes, UbiGEMWrapper::Structure::List<LPCTSTR>* ppids);
	void OnReceivedCurrentEPPDRequest(unsigned int systemBytes);
	void OnUserPrimaryMessageReceived(UbiGEMWrapper::Structure::SECSMessage* message);
	void OnUserSecondaryMessageReceived(UbiGEMWrapper::Structure::SECSMessage* primaryMessage, UbiGEMWrapper::Structure::SECSMessage* secondaryMessage);
	void OnCommunicationStateChanged(UbiGEMWrapper::Structure::GEMCommunicationState communicationState);
	void OnControlStateChanged(UbiGEMWrapper::Structure::GEMControlState controlState);
	void OnControlStateOnlineChangeFailed();
	void OnEquipmentProcessState(unsigned char equipmentProcessState);
	//void OnSpoolStateChanged(UbiGEMWrapper::Structure::GEMSpoolState spoolState);
	void OnVariableUpdateRequest(UbiGEMWrapper::Structure::GEMVariableUpdateType updateType, UbiGEMWrapper::Structure::List<LPCTSTR>* vids);
	void OnUserGEMMessageUpdateRequest(UbiGEMWrapper::Structure::SECSMessage* message);
	void OnTraceDataUpdateRequest(UbiGEMWrapper::Structure::List<LPCTSTR>* vids);


private:
	void InitializeControls();

	CString ConvertDriverResult(UbiGEMWrapper::Structure::GEMResult eResult);
	void UpdateDialogTitle();
	CString GetGUIString(CComboBox* cboTarget);
	CString GetGUIString(CEdit* edtTarget);
	CString CheckValidationParameterItem(UbiGEMWrapper::Structure::EnhancedCommandParameterItem* enhancedCommandParameterItem, UbiGEMWrapper::Structure::RemoteCommandParameterResult* paramResult);
	void MakePPBody(UbiGEMWrapper::Structure::List<unsigned char>* ppBody);

	void ProcessProgramParsing(bool withoutValue, UbiGEMWrapper::Structure::FmtPPCollection* fmtPpCollection, std::vector<PP_RECIPE_SPEC> specData);

	CString SECSFormatAsString(UbiGEMWrapper::Structure::GEMSECSFormat format);
	CString SECSValueAsString(UbiGEMWrapper::Structure::GEMSECSFormat format, UbiGEMWrapper::Structure::SECSValue *value);

	void reportCommonSet();

	void ReportFn(CString strCEID, CString param = _T(""));//UbiGEMWrapper::GEMWrapper* m_pWrapper;
	void ProcessCommandParameterItem(UbiGEMWrapper::Structure::EnhancedCommandParameterItem* pItem,
		UbiGEMWrapper::Structure::RemoteCommandParameterResult* pParentResult, CString& strLog, int level, RcmdParameter& parameter);

	
	//UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->RequestFmtPPRequest(ppid);
public:
	int opCallType;
	int uCtTimeOutData;
	void FormattedProcessProgramRequest(CString ppId);
	void TerminalMessageSendRequest(int nid, CString strVal);
	void CtTimeOut_Kill();
protected:

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonUgcOpen();
	afx_msg void OnBnClickedButtonUbigemClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonUbigemInit();
	afx_msg void OnBnClickedButtonUbigemStart();
	afx_msg void OnBnClickedButtonUbigemStop();
	afx_msg void OnBnClickedButtonUbigemProcessStateChange();
	afx_msg void OnBnClickedButtonUbigemAlarmSet();
	afx_msg void OnBnClickedButtonUbigemAlarmClear();
	afx_msg void OnCbnSelchangeCboEc();
	afx_msg void OnBnClickedButtonUbigemVSet();
	afx_msg void OnBnClickedButtonUbigemEcSet();
	afx_msg void OnBnClickedButtonUbigemUserMessageSend();
	afx_msg void OnBnClickedButtonUbigemTest10711();
	afx_msg void OnBnClickedButtonUbigemCeReport1();
	afx_msg void OnBnClickedButtonUbigemTest10401();
	afx_msg void OnBnClickedButtonUbigemCsOffline();
	afx_msg void OnBnClickedButtonUbigemCsOnlineLocal();
	afx_msg void OnBnClickedButtonUbigemCsOnlineRemote();
	afx_msg void OnBnClickedButtonUbigemTerminalMessageSend();
	afx_msg void OnBnClickedButtonUbigemTest10701();
	afx_msg void OnBnClickedButtonUbigemVGet();
	afx_msg void OnBnClickedButtonUbigemRcmdView();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonUbigemTestIdleTime();
	afx_msg void OnBnClickedButtonUbigemLoopback();
	afx_msg void OnBnClickedButtonUbigemTimeRequest();
	afx_msg void OnBnClickedButtonUbigemTest10710();
	afx_msg void OnBnClickedButtonUbigemCsOnlineEstablish();
	afx_msg void OnBnClickedButtonUbigemTestFmtPpVerificationSend();
};
