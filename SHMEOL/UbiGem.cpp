// UbiGem.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "UbiGem.h"
#include "afxdialogex.h"

#include "DriverHelper.h"
#include <sstream>



#ifndef DEBUG
#pragma comment(lib, "UbiGEM.CLI.lib")
#else
#pragma comment(lib, "UbiGEM.CLId.lib")
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CUbiGem 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUbiGem, CDialogEx)

CUbiGem::CUbiGem(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_UBIGEM, pParent)
{
	m_pWrapper = nullptr;
	srand((unsigned int)(time(NULL)));
	m_nUnit = 0;
	opCallType = 0;
	strSendCeId = _T("");
	m_strUgcFileName = _T("");
	initChk = true;
	m_iAck = 0;
	uCtTimeOutData = 2;			//init
	UbiGemInit = true;
}

CUbiGem::~CUbiGem()
{
	OnMnuStop();
	if (m_pWrapper != nullptr)
	{
		
		delete m_pWrapper;
		m_pWrapper = nullptr;
	}
	
	_CrtSetBreakAlloc(1633);
}

void CUbiGem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_LOG, m_edtLog);

	DDX_Control(pDX, IDC_CBO_EC, m_cboEcv);
	DDX_Control(pDX, IDC_CBO_V, m_cboV);
	DDX_Control(pDX, IDC_CBO_CE, m_cboCe);
	DDX_Control(pDX, IDC_CBO_USER_MESSAGE, m_cboUserMessage);
	DDX_Control(pDX, IDC_CBO_RCMD_VIEW, m_cboRcmdView);
	

	//EDIT CONTROL
	DDX_Control(pDX, IDC_EDT_PROCESS_STATE, m_edtProcessState);
	DDX_Control(pDX, IDC_EDT_ALARM_ID, m_edtAlarmId);
	DDX_Control(pDX, IDC_EDT_ECV, m_edtECV);
	DDX_Control(pDX, IDC_EDT_V, m_edtV);
	DDX_Control(pDX, IDC_EDT_TID, m_edtTId);
	DDX_Control(pDX, IDC_EDT_TERMINAL_MESSAGE, m_edtTerminalMessage);
	
	DDX_Control(pDX, IDC_STATIC_UBIGEM_CONTROL_STATE, m_clColorStaticControlState);


	DDX_Control(pDX, IDC_EDT_ABS, m_edtAbs);
}


BEGIN_MESSAGE_MAP(CUbiGem, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UGC_OPEN, &CUbiGem::OnBnClickedButtonUgcOpen)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_CLOSE, &CUbiGem::OnBnClickedButtonUbigemClose)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_INIT, &CUbiGem::OnBnClickedButtonUbigemInit)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_START, &CUbiGem::OnBnClickedButtonUbigemStart)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_STOP, &CUbiGem::OnBnClickedButtonUbigemStop)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_PROCESS_STATE_CHANGE, &CUbiGem::OnBnClickedButtonUbigemProcessStateChange)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_ALARM_SET, &CUbiGem::OnBnClickedButtonUbigemAlarmSet)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_ALARM_CLEAR, &CUbiGem::OnBnClickedButtonUbigemAlarmClear)
	ON_CBN_SELCHANGE(IDC_CBO_EC, &CUbiGem::OnCbnSelchangeCboEc)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_V_SET, &CUbiGem::OnBnClickedButtonUbigemVSet)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_EC_SET, &CUbiGem::OnBnClickedButtonUbigemEcSet)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_USER_MESSAGE_SEND, &CUbiGem::OnBnClickedButtonUbigemUserMessageSend)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_TEST_10711, &CUbiGem::OnBnClickedButtonUbigemTest10711)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_CE_REPORT1, &CUbiGem::OnBnClickedButtonUbigemCeReport1)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_TEST_10401, &CUbiGem::OnBnClickedButtonUbigemTest10401)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_CS_OFFLINE, &CUbiGem::OnBnClickedButtonUbigemCsOffline)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_CS_ONLINE_LOCAL, &CUbiGem::OnBnClickedButtonUbigemCsOnlineLocal)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_CS_ONLINE_REMOTE, &CUbiGem::OnBnClickedButtonUbigemCsOnlineRemote)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_TERMINAL_MESSAGE_SEND, &CUbiGem::OnBnClickedButtonUbigemTerminalMessageSend)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_TEST_10701, &CUbiGem::OnBnClickedButtonUbigemTest10701)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_V_GET, &CUbiGem::OnBnClickedButtonUbigemVGet)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_RCMD_VIEW, &CUbiGem::OnBnClickedButtonUbigemRcmdView)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_TEST_IDLE_TIME, &CUbiGem::OnBnClickedButtonUbigemTestIdleTime)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_LOOPBACK, &CUbiGem::OnBnClickedButtonUbigemLoopback)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_TIME_REQUEST, &CUbiGem::OnBnClickedButtonUbigemTimeRequest)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_TEST_10710, &CUbiGem::OnBnClickedButtonUbigemTest10710)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_CS_ONLINE_ESTABLISH, &CUbiGem::OnBnClickedButtonUbigemCsOnlineEstablish)
	ON_BN_CLICKED(IDC_BUTTON_UBIGEM_TEST_FMT_PP_VERIFICATION_SEND, &CUbiGem::OnBnClickedButtonUbigemTestFmtPpVerificationSend)
END_MESSAGE_MAP()


// CUbiGem 메시지 처리기입니다.


BOOL CUbiGem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->CenterWindow();

	InitCtrl();		//UI SET
	initUbiGEMSet();
	UbisamUgcLoad();
	//UbiGEM - Configuration


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void CUbiGem::Finalexit()
{
	OnMnuStop();
	m_pWrapper->Terminate();
}
void CUbiGem::InitCtrl()
{
	int i = 0;


	// 폰트 생성

	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(23, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	m_edtAlarmId.SetWindowText(_T("0"));
	m_edtProcessState.SetWindowText(_T("0"));

	m_edtAlarmId.ModifyStyle(0, ES_NUMBER);
	m_edtProcessState.ModifyStyle(0, ES_NUMBER);

	static CFont font;
	font.CreatePointFont(100, _T("Arial"));
	m_edtECV.SetFont(&font);
	m_edtV.SetFont(&font);
	m_edtAlarmId.SetFont(&font);
	m_edtProcessState.SetFont(&font);

	m_clColorStaticControlState.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticControlState.SetFont(&m_clFontSmall);

	
	
}
void CUbiGem::initUbiGEMSet()
{
	m_pWrapper = new UbiGEMWrapper::GEMWrapper();

	m_pWrapper->SubscribeInitilaize(this);
	m_pWrapper->SubscribeGEMConnected();
	m_pWrapper->SubscribeGEMDisconnected();
	m_pWrapper->SubscribeGEMSelected();
	m_pWrapper->SubscribeGEMDeselected();
	m_pWrapper->SubscribeSECSTimeout();
	m_pWrapper->SubscribeSECST3Timeout();
	m_pWrapper->SubscribeInvalidMessageReceived();
	m_pWrapper->SubscribeReceivedUnknownMessage();
	m_pWrapper->SubscribeReceivedEstablishCommunicationsRequest();
	m_pWrapper->SubscribeReceivedRemoteCommand();
	m_pWrapper->SubscribeReceivedInvalidRemoteCommand();
	m_pWrapper->SubscribeReceivedEnhancedRemoteCommand();
	m_pWrapper->SubscribeReceivedInvalidEnhancedRemoteCommand();
	m_pWrapper->SubscribeReceivedNewECVSend();
	m_pWrapper->SubscribeReceivedLoopback();
	m_pWrapper->SubscribeReceivedTerminalMessage();
	m_pWrapper->SubscribeReceivedTerminalMultiMessage();
	m_pWrapper->SubscribeReceivedRequestOffline();
	m_pWrapper->SubscribeReceivedRequestOnline();
	m_pWrapper->SubscribeReceivedDefineReport();
	m_pWrapper->SubscribeReceivedLinkEventReport();
	m_pWrapper->SubscribeReceivedEnableDisableEventReport();
	m_pWrapper->SubscribeReceivedEnableDisableAlarmSend();
	m_pWrapper->SubscribeResponseDateTimeRequest();
	m_pWrapper->SubscribeResponseLoopback();
	m_pWrapper->SubscribeResponseEventReportAcknowledge();
	m_pWrapper->SubscribeReceivedPPLoadInquire();
	m_pWrapper->SubscribeReceivedPPSend();
	m_pWrapper->SubscribeReceivedFmtPPSend();
	m_pWrapper->SubscribeResponsePPLoadInquire();
	m_pWrapper->SubscribeResponsePPSend();
	m_pWrapper->SubscribeResponsePPRequest();
	m_pWrapper->SubscribeResponseFmtPPSend();
	m_pWrapper->SubscribeResponseFmtPPRequest();
	m_pWrapper->SubscribeResponseFmtPPVerification();
	m_pWrapper->SubscribeResponseTerminalRequest();
	m_pWrapper->SubscribeReceivedDateTimeRequest();
	m_pWrapper->SubscribeReceivedDateTimeSetRequest();
	m_pWrapper->SubscribeReceivedPPRequest();
	m_pWrapper->SubscribeReceivedFmtPPRequest();
	m_pWrapper->SubscribeReceivedDeletePPSend();
	m_pWrapper->SubscribeReceivedCurrentEPPDRequest();
	m_pWrapper->SubscribeUserPrimaryMessageReceived();
	m_pWrapper->SubscribeUserSecondaryMessageReceived();
	m_pWrapper->SubscribeCommunicationStateChanged();
	m_pWrapper->SubscribeControlStateChanged();
	m_pWrapper->SubscribeControlStateOnlineChangeFailed();
	m_pWrapper->SubscribeEquipmentProcessState();
	m_pWrapper->SubscribeSpoolStateChanged();
	m_pWrapper->SubscribeVariableUpdateRequest();
	m_pWrapper->SubscribeUserGEMMessageUpdateRequest();
	m_pWrapper->SubscribeTraceDataUpdateRequest();
	//OnReceivedTerminalMessage
	m_pWrapper->SubscribeReceivedTerminalMessage();		//250103 Add
	m_pWrapper->SubscribeResponseTerminalRequest();//250103 Add
	m_pWrapper->SubscribeReceivedTerminalMultiMessage();//250103 Add



	m_edtTId.SetWindowText(_T("1"));
	m_edtTerminalMessage.SetWindowText(_T("TerminalMessage"));
	m_edtAbs.SetWindowText(_T("0"));

	
	UpdateDialogTitle();
}

void CUbiGem::OnGEMConnected(LPCTSTR strIpAddress, int nPortNo)
{
	CString strLog;

	strLog.Format(_T("OnGEMConnected : [IP=%s,Port=%d]"), strIpAddress, nPortNo);

	UbisamAddLog(strLog);

	UpdateDialogTitle();
}
void CUbiGem::OnGEMDisconnected(LPCTSTR strIpAddress, int nPortNo)
{
	CString strLog;

	strLog.Format(_T("OnGEMDisconnected : [IP=%s,Port=%d]"), strIpAddress, nPortNo);

	UbisamAddLog(strLog);
	UpdateDialogTitle();

	g_pCarAABonderDlg->m_clMainDlg.setControlState(-1);
}
void CUbiGem::OnGEMSelected(LPCTSTR strIpAddress, int nPortNo)
{
	CString strLog;

	strLog.Format(_T("OnGEMSelected : [IP=%s,Port=%d]"), strIpAddress, nPortNo);

	UbisamAddLog(strLog);
}
void CUbiGem::OnGEMDeselected(LPCTSTR strIpAddress, int nPortNo)
{
	CString strLog;

	strLog.Format(_T("OnGEMDeselected : [IP=%s,Port=%d]"), strIpAddress, nPortNo);

	UbisamAddLog(strLog);
}
void CUbiGem::OnSECSTimeout(UbiGEMWrapper::Structure::SECSTimeoutType timeoutType)
{
	CString strLog;

	strLog.Format(_T("OnSECSTimeout : [TimeoutType=%d]"), timeoutType);

	UbisamAddLog(strLog);
}

void CUbiGem::OnSECST3Timeout(UbiGEMWrapper::Structure::SECSMessage* message)
{
	CString strLog;

	strLog.Format(_T("OnSECST3Timeout : [Message=%s(S%dF%d), SystemBytes=%d]"), message->Name, message->Stream, message->Function, message->SystemBytes);

	UbisamAddLog(strLog);
}
void CUbiGem::OnInvalidMessageReceived(UbiGEMWrapper::Structure::GEMMessageValidationError error, UbiGEMWrapper::Structure::SECSMessage* pMessage)
{
	CString strLog;

	strLog.Format(_T("OnInvalidMessageReceived : [Stream=%d,Function=%d,Name=%s]"), pMessage->Stream, pMessage->Function, pMessage->Name);

	UbisamAddLog(strLog);
}
void CUbiGem::OnReceivedUnknownMessage(UbiGEMWrapper::Structure::SECSMessage* pMessage)
{
	CString strLog;

	strLog.Format(_T("OnReceivedUnknownMessage : [Stream=%d,Function=%d]"), pMessage->Stream, pMessage->Function);

	UbisamAddLog(strLog);
}
// Host에서 S1F13(Establish Communication)이 수신될 때 발생하는 이벤트입니다.
int CUbiGem::OnReceivedEstablishCommunicationsRequest(LPCTSTR strMdln, LPCTSTR strSofRev)
{
	UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->EstablishCommunication();		//250113 우선 빼고 진행
	UbisamAddLog(_T("EstablishCommunication"), gemResult);

	Sleep(50);

	CString strLog = _T("");
	//Auto Reply
	strLog.Format(_T("OnReceivedEstablishCommunicationsRequest : [MDLN=%s,SOFTREV=%s]"), strMdln, strSofRev);

	UbisamAddLog(strLog);

	
	return m_iAck;
}



// Host에서 S2F41(Remote Command)가 수신될 때 발생하는 이벤트입니다.
// RemoteCommandInfo 의 아이템을 순회하는 코드입니다.
// RemoteCommandParameterResult 에 IRemoteCommandParameterResult 를 추가하여 parameter 별 ack를 구성할 수 있습니다.
void CUbiGem::OnReceivedRemoteCommand(UbiGEMWrapper::Structure::RemoteCommandInfo* remoteCommandInfo)
{
	UbiGEMWrapper::Structure::RemoteCommandResult* pResult = nullptr;
	UbiGEMWrapper::Structure::CommandParameterInfo* pParamInfo = nullptr;
	CString strLog;
	CString strValue;

	pResult = m_pWrapper->CreateRemoteCommandResult(m_iAck);

	strLog.AppendFormat(_T("OnReceivedRemoteCommand : [RemoteCommand=%s]"), remoteCommandInfo->RemoteCommand);

	if (pResult->Items == nullptr && m_iAck != 0)
	{
		pResult->InitializeItems();
	}

	for (int i = 0, n = remoteCommandInfo->CommandParameter->Items->GetCount(); i < n; i++)
	{
		pParamInfo = remoteCommandInfo->CommandParameter->Items->At(i);

		if (pParamInfo != nullptr)
		{
			strValue = SECSValueAsString(pParamInfo->Format, pParamInfo->Value);
			strLog.AppendFormat(_T("\r\n:   [CPNAME=%s,Format=%s,Value=%s]"), pParamInfo->Name, SECSFormatAsString(pParamInfo->Format), strValue);

			// CP 검증 후 result에 CP별 ack 를 설정합니다.
			if (m_iAck != 0)
			{
				pResult->AddParameterResult(pParamInfo->Name, m_iAck);
			}
		}
	}

	// CP 검증 후 result 에 HCACK를 설정합니다
	UbisamAddLog(strLog);

	UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyRemoteCommandAck(remoteCommandInfo, pResult);

	UbisamAddLog(_T("ReplyRemoteCommandAck"), gemResult);

	m_pWrapper->DeleteRemoteCommandResult(pResult);
	pResult = nullptr;

}


// UbiGEM Configuration 파일에 정의되지 않은 Remote Command 가 수신될 경우 발생합니다.
void CUbiGem::OnReceivedInvalidRemoteCommand(UbiGEMWrapper::Structure::RemoteCommandInfo* remoteCommandInfo)
{
	CString strLog;

	strLog.Format(_T("OnReceivedInvalidRemoteCommand : [RemoteCommand=%s]"), remoteCommandInfo->RemoteCommand);

	UbisamAddLog(strLog);
}

void CUbiGem::FormattedProcessProgramRequest(CString ppId)		//Send S7F25 Formmatted Process Program Request
{
	if (m_pWrapper != nullptr && ppId.GetAllocLength() > 0)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->RequestFmtPPRequest(ppId);

		CString strLog;

		strLog.Format(_T("RequestFmtPPRequest : [PPID=%s]"), ppId);

		UbisamAddLog(strLog, gemResult);
	}
}
void CUbiGem::ProcessCommandParameterItem(UbiGEMWrapper::Structure::EnhancedCommandParameterItem* pItem,
	UbiGEMWrapper::Structure::RemoteCommandParameterResult* pParentResult,
	CString& strLog, int level, RcmdParameter& parameter)
{
	if (pItem == nullptr) 
	{
		return;
	}

	// 처리 결과 객체 생성
	UbiGEMWrapper::Structure::RemoteCommandParameterResult* pCurrentResult = nullptr;
	if (pParentResult != nullptr && m_iAck != 0) 
	{
		pCurrentResult = m_pWrapper->CreateRemoteCommandParameterResult(pItem->Name, m_iAck);
		pParentResult->ParameterListAck->Add(pCurrentResult);
	}

	// 로그 작성
	CString indent;
	indent.Format(_T("%*s"), level * 4, _T("")); // 단계에 따라 들여쓰기 설정

	CString strValue = SECSValueAsString(pItem->Format, pItem->Value);
	strLog.AppendFormat(_T("\r\n:%s:   [CPNAME=%s,Format=%s,CEPVAL=%s]"), indent, pItem->Name, SECSFormatAsString(pItem->Format), strValue);
	indent.Empty();
	strValue.Empty();

	//
	// 현재 항목 저장
	parameter.name = pItem->Name;
	//parameter.format = pItem->Format;
	parameter.value = SECSValueAsString(pItem->Format, pItem->Value);

	//
	// 하위 항목 처리
	if (pItem->Format == UbiGEMWrapper::Structure::GEMSECSFormat_L && pItem->ChildParameterItems != nullptr) 
	{
		for (int i = 0, count = pItem->ChildParameterItems->GetCount(); i < count; i++) 
		{
			auto* pChildItem = pItem->ChildParameterItems->At(i);

			RcmdParameter childParameter;
			ProcessCommandParameterItem(pChildItem, pCurrentResult, strLog, level + 1, childParameter);
			parameter.children.push_back(childParameter); // 하위 항목 추가
		}
	}
}




// Host에서 S2F49(Enhanced Remote Command)가 수신될 때 발생하는 이벤트입니다.
// EnhancedRemoteCommandInfo 의 아이템을 순회하는 코드입니다.
// RemoteCommandResult 에 RemoteCommandParameterResult 를 추가하여 parameter 별 ack를 구성할 수 있습니다.
void CUbiGem::OnReceivedEnhancedRemoteCommand(UbiGEMWrapper::Structure::EnhancedRemoteCommandInfo* remoteCommand)
{

	UbiGEMWrapper::Structure::RemoteCommandResult* pResult = nullptr;
	CString strLog;
	CString strValue;
	CString RecvStrData;

	CString strErrCode;
	CString strErrText;
	int RecvIntData = 0;
	int i = 0;
	RecvStrData.Empty();
	strErrCode.Empty();
	strErrText.Empty();

	pResult = m_pWrapper->CreateRemoteCommandResult(m_iAck);

	strLog.AppendFormat(_T("OnReceivedEnhancedRemoteCommand : [RemoteCommand=%s]"), remoteCommand->RemoteCommand);
	AddLog(strLog, 0, 0);
	int RcIndex = -1;
	for (i = 0; i < 14; i++)
	{
		if (_tcscmp(remoteCommand->RemoteCommand, RCMD_LIST_NAME[i]) == 0)
		{
			RcIndex = i;
			strValue.Format(_T("[%d] %s Received"), i, RCMD_LIST_NAME[i]);
			UbisamAddLog(strValue);
			break;
		}
	}

	if (RcIndex == eLGIT_OP_CALL)
	{
		//g_clReportData.rCtrlState_Chg_Req;
	}
	if (RcIndex == eLGIT_SETCODE_OFFLINE_REASON)
	{
		//g_clReportData.rSetCode_Offline_Reason.parameters.clear();
		g_clReportData.vOfflineReason.clear();
	}
	if (RcIndex == eLGIT_SETCODE_IDLE_REASON)
	{
		//g_clReportData.rSetCode_Idle_Reason.parameters.clear();
		g_clReportData.vIdleReason.clear();
	}
	if (RcIndex == eLGIT_SETCODE_MATERIAL_EXCHANGE)
	{
		//g_clReportData.rSetCode_Material_Exchange.parameters.clear();
		g_clReportData.vMaterialExchange.clear();
	}
	else if (RcIndex == eLGIT_SETCODE_MODEL_LIST)
	{
		//g_clReportData.rSetCode_Model_List.parameters.clear();
		g_clReportData.vModelLIst.clear();
	}
	if (RcIndex == eLGIT_PP_SELECT)
	{
		//g_clReportData.rPP_Select.parameters.clear();
		g_clReportData.vPPSelect.clear();
	}
	if (RcIndex == eLGIT_LOT_ID_FAIL)
	{
		//g_clReportData.rLot_Id_Fail.parameters.clear();
		g_clReportData.vLotIdFail.clear();
	}
	if (RcIndex == eLGIT_PP_UPLOAD_CONFIRM)
	{
		//g_clReportData.rPP_UpLoad_Confirm.parameters.clear();
		g_clReportData.vPPUploadConfirm.clear();
	}
	if (RcIndex == eLGIT_PP_UPLOAD_FAIL)
	{
		//g_clReportData.rPP_UpLoad_Fail.parameters.clear();
		g_clReportData.vPPUploadFail.clear();
	}
	if (RcIndex == eLGIT_LOT_START)
	{
		//g_clReportData.rLot_Start.parameters.clear();
		g_clReportData.vLotStart.clear();
	}

	// 로그 출력
	if (remoteCommand->EnhancedCommandParameter != nullptr && remoteCommand->EnhancedCommandParameter->Items != nullptr)
	{

		UbiGEMWrapper::Structure::EnhancedCommandParameterInfo* pEcpInfo = nullptr;
		UbiGEMWrapper::Structure::RemoteCommandParameterResult* pRcParamResult = nullptr;
		UbiGEMWrapper::Structure::EnhancedCommandParameterItem* pItem1 = nullptr;


		int rRootCount = remoteCommand->EnhancedCommandParameter->Items->GetCount();


		for (int i = 0; i < rRootCount; i++)
		{
			pRcParamResult = nullptr;
			pEcpInfo = remoteCommand->EnhancedCommandParameter->Items->At(i);
			if (pEcpInfo->Format == UbiGEMWrapper::Structure::GEMSECSFormat_L)		// -------------- List
			{
				strLog.AppendFormat(_T("\r\n:   [CPNAME=%s,Format=L,Count=%d]"), pEcpInfo->Name, pEcpInfo->Items->GetCount());

				if (m_iAck != 0)
				{
					pRcParamResult = m_pWrapper->CreateRemoteCommandParameterResult(pEcpInfo->Name, m_iAck);
					pResult->Items->Add(pRcParamResult);
				}
				if (pEcpInfo->Items != nullptr)
				{
					// 2차원 데이터
					int rSubCount = pEcpInfo->Items->GetCount();

					for (int j = 0; j < rSubCount; j++)		//LGIT_LOT_ID_FAIL  타입은 여기서 2개 들어온다. 그밑에 5개씩 있음.
					{
						pItem1 = pEcpInfo->Items->At(j);

						RcmdParameter parameter;
						ProcessCommandParameterItem(pItem1, pRcParamResult, strLog, 0, parameter);

						if (RcIndex == eLGIT_LOT_ID_FAIL)
						{
							//g_clReportData.rLot_Id_Fail.parameters.push_back(parameter);
							g_clReportData.vLotIdFail.push_back(parameter);
						}
						else if (RcIndex == eLGIT_PP_SELECT)
						{
							//g_clReportData.rPP_Select.parameters.push_back(parameter);
							g_clReportData.vPPSelect.push_back(parameter);
						}
						else if (RcIndex == eLGIT_PP_UPLOAD_CONFIRM)
						{
							//g_clReportData.rPP_UpLoad_Confirm.parameters.push_back(parameter);
							g_clReportData.vPPUploadConfirm.push_back(parameter);
						}
						if (RcIndex == eLGIT_SETCODE_OFFLINE_REASON)
						{
							//g_clReportData.rSetCode_Offline_Reason.parameters.push_back(parameter);
							RcmdParam1 rcmdP1;
							rcmdP1.cpName = pItem1->Name;
							rcmdP1.cepVal = SECSValueAsString(pItem1->Format, pItem1->Value);
							g_clReportData.vOfflineReason.push_back(rcmdP1);
						}
						if (RcIndex == eLGIT_SETCODE_IDLE_REASON)
						{
							///g_clReportData.rSetCode_Idle_Reason.parameters.push_back(parameter);
							RcmdParam1 rcmdP1;
							rcmdP1.cpName = pItem1->Name;
							rcmdP1.cepVal = SECSValueAsString(pItem1->Format, pItem1->Value);
							g_clReportData.vIdleReason.push_back(rcmdP1);
						}
						if (RcIndex == eLGIT_SETCODE_MODEL_LIST)
						{
							//g_clReportData.rSetCode_Model_List.parameters.push_back(parameter);
							RcmdParam1 rcmdP1;
							rcmdP1.cpName = pItem1->Name;
							rcmdP1.cepVal = SECSValueAsString(pItem1->Format, pItem1->Value);
							g_clReportData.vModelLIst.push_back(rcmdP1);
						}
						if (RcIndex == eLGIT_PP_UPLOAD_FAIL)
						{
							//g_clReportData.rPP_UpLoad_Fail.parameters.push_back(parameter);
							RcmdParam1 rcmdP1;
							rcmdP1.cpName = pItem1->Name;
							rcmdP1.cepVal = SECSValueAsString(pItem1->Format, pItem1->Value);
							g_clReportData.vPPUploadFail.push_back(rcmdP1);
						}

						//
						//
						if (RcIndex == eLGIT_SETCODE_MATERIAL_EXCHANGE)
						{
							//g_clReportData.rSetCode_Material_Exchange.parameters.push_back(parameter);
							g_clReportData.vMaterialExchange.push_back(parameter);
							
						}
						
						if (RcIndex == eLGIT_LOT_START)
						{
							//g_clReportData.rLot_Start.parameters.push_back(parameter);
							g_clReportData.vLotStart.push_back(parameter);
						}
					}
				}
			}
			else
			{
				if (RcIndex == eLGIT_PP_SELECT)
				{
					if (g_clMesCommunication[m_nUnit].m_sRecipeId != g_clMesCommunication[m_nUnit].m_sMesPPID)		//eLGIT_PP_SELECT
					{
						pResult->HostCommandAck = 4;
					}
				}
				if (pResult != nullptr && m_iAck != 0)
				{
					pResult->AddParameterResult(pEcpInfo->Name, m_iAck);
				}

				strValue = SECSValueAsString(pEcpInfo->Format, pEcpInfo->Value);

				if (_tcscmp(pEcpInfo->Name, "EQPID") == 0)
				{
					g_clMesCommunication[m_nUnit].m_sEquipmentID = strValue;
					m_pWrapper->SetVariable(_T("10001"), g_clMesCommunication[m_nUnit].m_sEquipmentID);
				}
				else if (_tcscmp(pEcpInfo->Name, "EQPNAME") == 0)
				{
					//g_clMesCommunication[m_nUnit].m_sEquipmentName = strValue;
					//m_pWrapper->SetVariable(_T("10002"), g_clMesCommunication[m_nUnit].m_sEquipmentName);
				}
				else if (_tcscmp(pEcpInfo->Name, "RECIPEID") == 0)
				{
					g_clMesCommunication[m_nUnit].m_sRecipeId = strValue;		//RECIPEID  EnhancedRemoteCommnad
				}

				if (RcIndex == eLGIT_CTRLSTATE_CHG_REQ)
				{
					if (_tcscmp(pEcpInfo->Name, "CONFIRMFLAG") == 0)
					{
						g_clReportData.rCtrlState_Chg_Req.ConfirmFlag = strValue;
					}
					else if (_tcscmp(pEcpInfo->Name, "CONTROLSTATE") == 0)
					{
						g_clReportData.rCtrlState_Chg_Req.ControlState = atoi(strValue);
					}
					else if (_tcscmp(pEcpInfo->Name, "CHANGE_CODE") == 0)
					{
						g_clReportData.rCtrlState_Chg_Req.Change_Code = strValue;
						m_pWrapper->SetVariable(_T("10006"), strValue);
					}
					else if (_tcscmp(pEcpInfo->Name, "CHANGE_TEXT") == 0)
					{
						g_clReportData.rCtrlState_Chg_Req.Change_Text = strValue;
						m_pWrapper->SetVariable(_T("10007"), strValue);
					}
					else if (_tcscmp(pEcpInfo->Name, "RESULT_CODE") == 0)
					{
						g_clReportData.rCtrlState_Chg_Req.Result_Code = strValue;
					}
					else if (_tcscmp(pEcpInfo->Name, "RESULT_TEXT") == 0)
					{
						g_clReportData.rCtrlState_Chg_Req.result_text = strValue;
					}
				}
				if (RcIndex == eLGIT_OP_CALL)
				{
					if (_tcscmp(pEcpInfo->Name, "CALLTYPE") == 0)
					{
						g_clReportData.rCtrlOp_Call.CallType = atoi(strValue);
					}
					else if (_tcscmp(pEcpInfo->Name, "OPCALL_CODE") == 0)
					{
						g_clReportData.rCtrlOp_Call.OpCall_Code = strValue;
					}
					else if (_tcscmp(pEcpInfo->Name, "OPCALL_TEXT") == 0)
					{
						g_clReportData.rCtrlOp_Call.OpCall_Text = strValue;
					}
				}
				if (RcIndex == eLGIT_LOT_ID_FAIL)
				{
					if (_tcscmp(pEcpInfo->Name, "CODE") == 0)
					{
						strErrCode = strValue;
						g_clMesCommunication[m_nUnit].m_sErcmdCode = strValue;
					}
					else if (_tcscmp(pEcpInfo->Name, "TEXT") == 0)
					{
						strErrText = strValue;
						g_clMesCommunication[m_nUnit].m_sErcmdText = strValue;
					}
				}
				if (RcIndex == eLGIT_PP_UPLOAD_CONFIRM)
				{

				}
				if (RcIndex == eLGIT_PP_UPLOAD_FAIL)
				{
					if (_tcscmp(pEcpInfo->Name, "CODE") == 0)
					{
						strErrCode = strValue;
						g_clMesCommunication[m_nUnit].m_sErcmdCode = strValue;
					}
					else if (_tcscmp(pEcpInfo->Name, "TEXT") == 0)
					{
						strErrText = strValue;
						g_clMesCommunication[m_nUnit].m_sErcmdText = strValue;
					}
				}
				if (RcIndex == eLGIT_MATERIAL_ID_CONFIRM)	//LGIT_MATERIAL_ID_CONFIRM
				{
					if (_tcscmp(pEcpInfo->Name, "MATERIALID") == 0)
					{
						g_clReportData.rMaterial_Id_Confirm.MaterialId = strValue;		//저장?
					}
					else if (_tcscmp(pEcpInfo->Name, "MATERIALTYPE") == 0)
					{
						g_clReportData.rMaterial_Id_Confirm.MaterialType = strValue;		//저장?
					}
					else if (_tcscmp(pEcpInfo->Name, "MATERIALTYPE_TEXT") == 0)
					{
						g_clReportData.rMaterial_Id_Confirm.MaterialType_Text = strValue;
					}
					else if (_tcscmp(pEcpInfo->Name, "UNITNO") == 0)
					{
						g_clReportData.rMaterial_Id_Confirm.UnitNo = atoi(strValue);
					}
					else if (_tcscmp(pEcpInfo->Name, "SLOTNO") == 0)
					{
						g_clReportData.rMaterial_Id_Confirm.SlotNo = atoi(strValue);
					}
					else if (_tcscmp(pEcpInfo->Name, "REMAINDATA") == 0)
					{
						g_clReportData.rMaterial_Id_Confirm.RemainData = strValue;
					}
				}
				if (RcIndex == eLGIT_MATERIAL_ID_FAIL)	//LGIT_MATERIAL_ID_FAIL
				{
					if (_tcscmp(pEcpInfo->Name, "MATERIALID") == 0)
					{
						g_clReportData.rMaterial_Id_Fail.MaterialId = strValue;
					}
					else if (_tcscmp(pEcpInfo->Name, "MATERIALTYPE") == 0)
					{
						g_clReportData.rMaterial_Id_Fail.MaterialType = strValue;
					}
					else if (_tcscmp(pEcpInfo->Name, "MATERIALTYPE_TEXT") == 0)
					{
						g_clReportData.rMaterial_Id_Fail.MaterialType_Text = strValue;
					}
					else if (_tcscmp(pEcpInfo->Name, "UNITNO") == 0)
					{
						g_clReportData.rMaterial_Id_Fail.UnitNo = atoi(strValue);
					}
					else if (_tcscmp(pEcpInfo->Name, "SLOTNO") == 0)
					{
						g_clReportData.rMaterial_Id_Fail.SlotNo = atoi(strValue);
					}
					else if (_tcscmp(pEcpInfo->Name, "CODE") == 0)
					{
						//g_clReportData.rMaterial_Id_Fail.Code = strValue;
						strErrCode = strValue;
						g_clMesCommunication[m_nUnit].m_sErcmdCode = strValue;
					}
					else if (_tcscmp(pEcpInfo->Name, "TEXT") == 0)
					{
						//g_clReportData.rMaterial_Id_Fail.Text = strValue;
						strErrText = strValue;
						g_clMesCommunication[m_nUnit].m_sErcmdText = strValue;
					}
				}
				if (RcIndex == eLGIT_PAUSE)	//LGIT_PAUSE
				{
					if (_tcscmp(pEcpInfo->Name, "PAUSE_CODE") == 0)
					{
						g_clReportData.rLgit_Pause.PauseCode = strValue;
					}
					else if (_tcscmp(pEcpInfo->Name, "PAUSE_TEXT") == 0)
					{
						g_clReportData.rLgit_Pause.PauteText = strValue;
					}
				}
				strLog.AppendFormat(_T("\r\n:   [CPNAME=%s,Format=%s,CEPVAL=%s]"), pEcpInfo->Name, SECSFormatAsString(pEcpInfo->Format), strValue);
			}
		}
	}

	//End
	UbisamAddLog(strLog);

	UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyEnhancedRemoteCommandAck(remoteCommand, pResult);
	UbisamAddLog(_T("ReplyEnhancedRemoteCommandAck"), gemResult);

	m_pWrapper->DeleteRemoteCommandResult(pResult);
	pResult = nullptr;


	if (RcIndex == eLGIT_OP_CALL)
	{
		//1 = Buzzer
		//g_clReportData.rCtrlOp_Call.OpCall_Code

		g_pCarAABonderDlg->m_clMessageLot.setMode(eLGIT_OP_CALL , g_clReportData.rCtrlOp_Call.CallType);
		g_pCarAABonderDlg->m_clMessageLot.setLotID(_T("OPCALL CODE"), g_clReportData.rCtrlOp_Call.OpCall_Code);
		g_pCarAABonderDlg->m_clMessageLot.setContent(g_clReportData.rCtrlOp_Call.OpCall_Text);
		g_pCarAABonderDlg->m_clMessageLot.ShowWindow(SW_SHOW);		//eLGIT_OP_CALL

		//op call 받고 perator Recognized Operator Call Message 10801    보내야된다
		//OP_RECOGNIZED_OP_CALL_REPORT_10801
	}
	else if (RcIndex == eLGIT_SETCODE_MODEL_LIST)
	{
		//g_clReportData.rSetCode_Model_List.parameters.push_back(parameter);
		//int cnt = g_clReportData.rSetCode_Model_List.parameters.size();
		int cnt = g_clReportData.vModelLIst.size();
		if (cnt > 0)
		{
			//g_pCarAABonderDlg->m_clMainDlg.ModelListDataSet(g_clReportData.rSetCode_Model_List);

			g_pCarAABonderDlg->m_clMainDlg.ModelListDataSet();

			TCHAR szLog[SIZE_OF_1K];
			_stprintf_s(szLog, SIZE_OF_1K, _T("[LGIT_SETCODE_MODEL_LIST] Model List Save!"));
			AddLog(strLog, 0, 0);
		}
	}


	else if (RcIndex == eLGIT_PAUSE)
	{
		//(Event =  Process State Change Report   ("PAUSE"))
		//g_clMesCommunication[m_nUnit].m_dProcessState[0] = g_clMesCommunication[m_nUnit].m_dProcessState[1];
		//g_clMesCommunication[m_nUnit].m_dProcessState[1] = 6;	//1 = EXECUTING //6 = PAUSE 
		//ReportFn(PROCESS_STATE_CHANGED_REPORT_10401);

		//PAUSE -> 가동후 ->> EXECUTING

		//strValue.Format(_T("[LGIT_PAUSE] ."));

		//strValue.Format(_T("[Code]:%s\n[Text]:%s"), g_clReportData.rLgit_Pause.PauseCode, g_clReportData.rLgit_Pause.PauteText);
		//g_ShowMsgPopup(_T("LGIT_PAUSE"), strValue, RGB_COLOR_RED);
		g_clMesCommunication[m_nUnit].m_bLgit_Pause_req = true;	//eLGIT_PAUSE
	}
	else if (RcIndex == eLGIT_PP_SELECT)
	{
		//Recipe ID Check 

		if (g_clMesCommunication[m_nUnit].m_sRecipeId == g_clMesCommunication[m_nUnit].m_sMesPPID)		//eLGIT_PP_SELECT
		{
			g_clTaskWork[m_nUnit].bRecv_Lgit_Pp_select = 0;		//Recv
			//S6F11 - Event Report Send
			//Evnet = Process State Change Report
			//g_clMesCommunication[m_nUnit].m_dProcessState[0] = g_clMesCommunication[m_nUnit].m_dProcessState[1];
			//g_clMesCommunication[m_nUnit].m_dProcessState[1] = eSETUP;

			//
			//g_clMesCommunication[m_nUnit].m_uAlarmList.clear();

			//EventReportSendFn(PROCESS_STATE_CHANGED_REPORT_10401);	//SEND S6F11
		}
		else
		{

			//이때 ack 1로 줘야되나?
			g_clTaskWork[m_nUnit].bRecv_Lgit_Pp_select = 1;	//Recv
			//strValue.Format(_T("[%s] 사용중인 RECIPE 와 다릅니다."), g_clMesCommunication[m_nUnit].m_sRecipeId);
			//g_ShowMsgPopup(_T("INFO"), strValue, RGB_COLOR_RED);

		}
	}
	if (RcIndex == eLGIT_LOT_ID_FAIL)	
	{
		g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start = 1;
		g_clDioControl.SetBuzzer(true, BUZZER_ALARM);
		//CTTimeout Kill
		//KillTimer(WM_CT_TIMEOUT_TIMER);	//LGIT_LOT_ID_FAIL
		//////팝업 추가
		//std::vector<RcmdList_T2> resultsT2;
		//resultsT2 = g_clReportData.T2_FindChildList(g_clReportData.rLot_Id_Fail.parameters);

		//if (resultsT2.size() > 0)
		//{
		//	for (i = 0; i < resultsT2[0].rVec.size(); i++)
		//	{
		//		if (resultsT2[0].rVec[i].cpName == "MODULEID")
		//		{
		//			g_pCarAABonderDlg->m_clMessageLot.setLotID(_T("LOT ID") , resultsT2[0].rVec[i].cepVal);		//여긴 lot id? , moduleid?
		//			break;
		//		}
		//	}
		//}
		//strValue.Format(_T("[LGIT_LOT_ID_FAIL]\nCode :%s\n%s"), strErrCode, strErrText);

		//g_pCarAABonderDlg->m_clMessageLot.setMode(RcIndex);
		//g_pCarAABonderDlg->m_clMessageLot.setLotTitle(strValue);


		//g_pCarAABonderDlg->m_clMessageLot.ShowWindow(SW_SHOW);		//test
		//g_pCarAABonderDlg->EnableWindow(FALSE);
	}
	if (RcIndex == eLGIT_PP_UPLOAD_CONFIRM)
	{
		g_clTaskWork[m_nUnit].bRecv_S2F49_PP_UpLoad_Confirm = 0;		//LGIT_PP_UPLOAD_CONFIRM
		//CTTimeout Kill
		//uCtTimeOutData = 4;			//PP_UPLOAD_COMPLETED_REPORT_10703
		//KillTimer(WM_CT_TIMEOUT_TIMER);	//eLGIT_PP_UPLOAD_CONFIRM
		//SetTimer(WM_CT_TIMEOUT_TIMER, g_clMesCommunication[m_nUnit].ConversationTimeoutCount * 1000, NULL);
		//EventReportSendFn(PP_UPLOAD_COMPLETED_REPORT_10703);//SEND S6F11
	}
	if (RcIndex == eLGIT_PP_UPLOAD_FAIL)
	{
		g_clTaskWork[m_nUnit].bRecv_S2F49_PP_UpLoad_Confirm = 1;		//LGIT_PP_UPLOAD_FAIL
		g_clDioControl.SetBuzzer(true, BUZZER_ALARM);
		//CTTimeout Kill
		//KillTimer(WM_CT_TIMEOUT_TIMER);	//eLGIT_PP_UPLOAD_FAIL
		//팝업
		//strValue.Format(_T("[LGIT_PP_UPLOAD_FAIL]\nCode :%s\n%s"), strErrCode, strErrText);

		//g_pCarAABonderDlg->m_clMessageLot.setMode(RcIndex);

		//g_pCarAABonderDlg->m_clMessageLot.setLotID(_T("RECIPE ID"), g_clMesCommunication[m_nUnit].m_sRecipeId);
		//g_pCarAABonderDlg->m_clMessageLot.setLotTitle(strValue);



		//g_pCarAABonderDlg->m_clMessageLot.ShowWindow(SW_SHOW);		//test
		//g_pCarAABonderDlg->EnableWindow(FALSE);
	}
	if (RcIndex == eLGIT_LOT_START)	
	{
		g_clTaskWork[m_nUnit].bRecv_S2F49_LG_Lot_Start = 0;
		//CTTimeout Kill
		//KillTimer(WM_CT_TIMEOUT_TIMER);	//LGIT_LOT_START
		//S6F11 - Event Report Send
		//Evnet = Process State Change Report
		//g_clMesCommunication[m_nUnit].m_dProcessState[0] = g_clMesCommunication[m_nUnit].m_dProcessState[1];
		//g_clMesCommunication[m_nUnit].m_dProcessState[1] = eEXECUTING;

		//g_clMesCommunication[m_nUnit].m_uAlarmList.clear(); 
		//g_clMesCommunication[m_nUnit].m_dLotProcessingState = eWait;

		//EventReportSendFn(PROCESS_STATE_CHANGED_REPORT_10401); //SEND S6F11

	}
	if (RcIndex == eLGIT_MATERIAL_ID_CONFIRM)
	{
		//CTTimeout Kill
		//KillTimer(WM_CT_TIMEOUT_TIMER);		//eLGIT_MATERIAL_ID_CONFIRM
		g_clMesCommunication[m_nUnit].secsGemSave();
		EventReportSendFn(MATERIAL_CHANGE_COMPLETED_REPORT_10714); //SEND S6F11
	}
	if (RcIndex == eLGIT_MATERIAL_ID_FAIL)
	{
		//CTTimeout Kill
		//KillTimer(WM_CT_TIMEOUT_TIMER);		//eLGIT_MATERIAL_ID_FAIL
		//팝업
		strValue.Format(_T("[LGIT_MATERIAL_ID_FAIL]\nCode :%s\n%s"), strErrCode, strErrText);
		g_clDioControl.SetBuzzer(true, BUZZER_ALARM);
		g_pCarAABonderDlg->m_clMessageLot.setMode(RcIndex);

		g_pCarAABonderDlg->m_clMessageLot.setLotID(_T("MATERIAL ID"), g_clReportData.rMaterial_Id_Fail.MaterialId);
		g_pCarAABonderDlg->m_clMessageLot.setContent(strValue);



		g_pCarAABonderDlg->m_clMessageLot.ShowWindow(SW_SHOW);		//test
		g_pCarAABonderDlg->EnableWindow(FALSE);
	}



	strLog.Empty();
	strValue.Empty();
	RecvStrData.Empty();

	strErrCode.Empty();
	strErrText.Empty();

}

// UbiGEM Configuration 파일에 정의되지 않은 Enhanced Remote Command 가 수신될 경우 발생합니다.
void CUbiGem::OnReceivedInvalidEnhancedRemoteCommand(UbiGEMWrapper::Structure::EnhancedRemoteCommandInfo* remoteCommandInfo)
{
	CString strLog;

	strLog.Format(_T("OnReceivedInvalidEnhancedRemoteCommand [RemoteCommand=%s]"), remoteCommandInfo->RemoteCommand);
	UbisamAddLog(strLog);
}

// Host에서 S2F15(New ECV Send)가 수신될 때 발생하는 이벤트입니다. ECID
void CUbiGem::OnReceivedNewECVSend(unsigned int systemBytes, UbiGEMWrapper::Structure::VariableCollection* newEcInfo)
{
	CString strLog;
	UbiGEMWrapper::Structure::VariableInfo* pItem;

	strLog.Format(_T("OnReceivedNewECVSend : [Count=%d]"), newEcInfo->Items->GetCount());
	AddLog(strLog, 0, 0);
	for (int i = 0, n = newEcInfo->Items->GetCount(); i < n; i++)
	{
		pItem = newEcInfo->Items->At(i);
		strLog.AppendFormat(_T("\r\n:   [Name=%s,VID=%s]"), pItem->Name, pItem->VID);

		if (_tcscmp(pItem->VID, _T("101")) == 0)
		{
			g_clMesCommunication[m_nUnit].EstablishCommunicationsTimeout = atoi(SECSValueAsString(pItem->Format, pItem->Value));

		}
		if (_tcscmp(pItem->VID, _T("102")) == 0)	//HeartBeatRate sec
		{
			g_clMesCommunication[m_nUnit].HeartBeatRate = atoi(SECSValueAsString(pItem->Format, pItem->Value));
		}
		if (_tcscmp(pItem->VID, _T("103")) == 0)	//항상 5:Enabled/Communicating
		{
			g_clMesCommunication[m_nUnit].DefaultCommState = atoi(SECSValueAsString(pItem->Format, pItem->Value));
		}
		if (_tcscmp(pItem->VID, _T("104")) == 0)	//주로 1,5번만 사용
		{
			//DefaultCtrlState (1:Equipment Offiline or 5:Online Remote)
			g_clMesCommunication[m_nUnit].DefaultCtrlState = atoi(SECSValueAsString(pItem->Format, pItem->Value));
		}
		if (_tcscmp(pItem->VID, _T("105")) == 0)		//사용x
		{
			g_clMesCommunication[m_nUnit].DefaultOfflineSubstate = atoi(SECSValueAsString(pItem->Format, pItem->Value));
		}
		if (_tcscmp(pItem->VID, _T("106")) == 0)	//사용x
		{
			g_clMesCommunication[m_nUnit].DefCtrlOfflineState = atoi(SECSValueAsString(pItem->Format, pItem->Value));
		}
		if (_tcscmp(pItem->VID, _T("107")) == 0)//0:set 12 digits format
		{
			//TimeFormat (1 or 2)
			g_clMesCommunication[m_nUnit].TimeFormat = atoi(SECSValueAsString(pItem->Format, pItem->Value));
		}
		if (_tcscmp(pItem->VID, _T("108")) == 0)//5:Remote
		{
			//DefaultOnlineSubState (4,5) 5고정사용
			g_clMesCommunication[m_nUnit].DefaultOnlineSubState = atoi(SECSValueAsString(pItem->Format, pItem->Value));
		}
		if (_tcscmp(pItem->VID, _T("109")) == 0)
		{
			g_clMesCommunication[m_nUnit].ConversationTimeoutCount = atoi(SECSValueAsString(pItem->Format, pItem->Value));
		}
		
		if (_tcscmp(pItem->VID, _T("201")) == 0) 
		{
			g_clMesCommunication[m_nUnit].m_sEquipmentID = SECSValueAsString(pItem->Format, pItem->Value);
			m_pWrapper->SetVariable(_T("10001"), g_clMesCommunication[m_nUnit].m_sEquipmentID);
		}
		if (_tcscmp(pItem->VID, _T("202")) == 0)
		{
			g_clMesCommunication[m_nUnit].m_sEquipmentName = SECSValueAsString(pItem->Format, pItem->Value);
			m_pWrapper->SetVariable(_T("10002"), g_clMesCommunication[m_nUnit].m_sEquipmentName);
		}
		if (_tcscmp(pItem->VID, _T("221")) == 0)	//"Y" or "N" IDLE reason Report 비가동 상태 사유 보고
		{
			g_clMesCommunication[m_nUnit].IdleReasonReportUsage = false;
			if (SECSValueAsString(pItem->Format, pItem->Value) == "Y")
			{
				g_clMesCommunication[m_nUnit].IdleReasonReportUsage = true;
			}
		}
		if (_tcscmp(pItem->VID, _T("222")) == 0)	//EQ Process Idle Status - report Setup Time
		{
			g_clMesCommunication[m_nUnit].IdleSetTimeInterval = atoi(SECSValueAsString(pItem->Format, pItem->Value));
		}
	}

	UbisamAddLog(strLog);

	if (m_pWrapper != nullptr)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyNewEquipmentConstantSend(systemBytes, newEcInfo, m_iAck);
		UbisamAddLog(_T("ReplyNewEquipmentConstantSend"), gemResult);
	}
}


// Host에서 S2F25(Loopback)이 수신될 때 발생하는 이벤트입니다.
void CUbiGem::OnReceivedLoopback(UbiGEMWrapper::Structure::List<unsigned char>* receiveData)
{
	CString strLog;
	CString strReceiveData;

	strLog.Format(_T("OnReceivedLoopback : [Count=%d]"), receiveData->GetCount());

	for (int i = 0; i < receiveData->GetCount(); i++)
	{
		strLog.AppendFormat(_T(" %d"), receiveData->At(i));
	}

	UbisamAddLog(strLog);
}


// Host에서 S10F3(Terminal Message Single)이 수신될 때 발생하는 이벤트입니다
void CUbiGem::OnReceivedTerminalMessage(unsigned int systemBytes, int tid, LPCTSTR strTerminalMessage)
{
	CString strLog;

	strLog.AppendFormat(_T("OnReceivedTerminalMessage: [TID=%d,Tmsg=%s,systemBytes=%d]"), tid, strTerminalMessage, systemBytes);
	UbisamAddLog(strLog);
	AddLog(strLog, 0, 0);

	if (m_pWrapper != nullptr)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyTerminalMessageAck(systemBytes, this->m_iAck);
		UbisamAddLog(_T("ReplyTerminalMessageAck"), gemResult);



		//Terminal Message Display !!! 
		//메세지창 띄워라
		//Confirm 버튼
		///CWnd* pMainWnd = AfxGetMainWnd();  // 메인 윈도우 가져오기
		///pMainWnd->MessageBox(strTerminalMessage, _T("Terminal Services"), MB_OK | MB_ICONINFORMATION | MB_SERVICE_NOTIFICATION);



		//Message 창이 떠있는 데 또 올 수도 있다.
		//
#if 1
		TCHAR szLog[SIZE_OF_1K];
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Terminal Services] %s"), strTerminalMessage);
		g_pCarAABonderDlg->m_clAlarmDlg.AddAlarm_N(szLog);
		g_ShowTerminalPopup(_T("INFO"), strTerminalMessage, tid, RGB_COLOR_RED);
		
#else
		if (g_pCarAABonderDlg->m_clMessageInput.IsWindowVisible() == true)
		{
			//중첩해서 뜨도록 수정 250109
		}
		TCHAR szLog[SIZE_OF_1K];
		_stprintf_s(szLog, SIZE_OF_1K, _T("[Terminal Services] %s"), strTerminalMessage);
		AddLog(szLog, 0, m_nUnit);
		g_pCarAABonderDlg->m_clAlarmDlg.AddAlarm_N(szLog);

		g_clMesCommunication[m_nUnit].m_dTerminalId = tid;
		g_pCarAABonderDlg->m_clMessageInput.editInputReadOnly = true;
		g_pCarAABonderDlg->m_clMessageInput.setEditInput(_T("Terminal Services"), strTerminalMessage);
		g_pCarAABonderDlg->m_clMessageInput.ShowWindow(SW_SHOW);
#endif
	}

}

// Host에서 S10F5(Terminal Message Multi)가 수신될 때 발생하는 이벤트입니다
void CUbiGem::OnReceivedTerminalMultiMessage(unsigned int systemBytes, int tid, UbiGEMWrapper::Structure::List<LPCTSTR>* strTerminalMessages)
{
	CString strLog;

	size_t length = strTerminalMessages->GetCount();

	strLog.AppendFormat(_T("OnReceivedTerminalMultiMessage: [TID=%d]"), tid);

	for (int i = 0; i < length; i++)
	{
		strLog.AppendFormat(_T("\r\n:   [Tmsg=%s]"), strTerminalMessages->At(i));
	}

	UbisamAddLog(strLog);

	if (m_pWrapper != nullptr)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyTerminalMultiMessageAck(systemBytes, this->m_iAck);
		UbisamAddLog(_T("ReplyTerminalMultiMessageAck"), gemResult);
	}

}

// Host에서 S1F15(Offline Request)가 수신될 때 발생하는 이벤트입니다.
void CUbiGem::OnReceivedRequestOffline(unsigned int systemBytes)
{
	CString strLog;

	strLog.Format(_T("OnReceivedRequestOffline"));
	AddLog(strLog, 0, 0);

	UbisamAddLog(strLog);

	if (m_pWrapper != nullptr)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyRequestOfflineAck(systemBytes, m_iAck);

		UbisamAddLog(_T("ReplyRequestOfflickAck"), gemResult);

		//1 = Equipment Offline
		//2 = Attempt Online
		//3 = Host Offline
		//4 = Online Local
		//5 = Online Remote
		//enum eCURRENT_CONTROL_STATE { eEquipmentOffline = 1, eAttemprtOnline, eHostOffline, eOnlineLocal, eOnlineRemote };

		//UpdateDialogTitle() 여기에서 m_dEqupControlState[1] 상태가 먼저 바껴있어서 Prev로 if문 수정
		//
		if (g_clMesCommunication[m_nUnit].m_dEqupControlState[0] == eOnlineLocal || 
			g_clMesCommunication[m_nUnit].m_dEqupControlState[0] == eOnlineRemote)
		{
			//S6F11 - Send Event Report
			//Event - Offline Changed Report
			//OFFLINE_CHANGED_REPORT_10102


			g_clMesCommunication[m_nUnit].m_dControlStateChangeOrder = 1;		//by Host


			m_pWrapper->SetVariable(_T("10006"), _T("HOST001"));	//ControlStateChangeReasonCode
			m_pWrapper->SetVariable(_T("10007"), _T("Host에서 OFF-LINE 전환 하였습니다."));	//ControlStateChangeReasonText
			OnBnClickedButtonUbigemCsOffline();
			///EventReportSendFn(OFFLINE_CHANGED_REPORT_10102);
		}
	}
}

// Host에서 S1F17(Online Request)가 수신될 때 발생하는 이벤트입니다.
void CUbiGem::OnReceivedRequestOnline(unsigned int systemBytes)
{
	CString strLog;

	strLog.Format(_T("OnReceivedRequestOnline"));

	UbisamAddLog(strLog); 

	if (m_pWrapper != nullptr)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyRequestOnlineAck(systemBytes, m_iAck);

		UbisamAddLog(_T("ReplyRequestOnlineAck"), gemResult);
	}
}

// S2F33(Define Report)가 수신될 경우 발생하는 이벤트입니다.
void CUbiGem::OnReceivedDefineReport()
{
	CString strLog;

	strLog.Format(_T("OnReceivedDefineReport"));

	UbisamAddLog(strLog);
}

// S2F35(Link Event Report)가 수신될 경우 발생하는 이벤트입니다.
void CUbiGem::OnReceivedLinkEventReport()
{
	CString strLog;

	strLog.Format(_T("OnReceivedLinkEventReport"));

	UbisamAddLog(strLog);
}

// S2F37(Event Report Enable/Disable)이 수신될 경우 발생하는 이벤트입니다.
void CUbiGem::OnReceivedEnableDisableEventReport()
{
	CString strLog;

	strLog.Format(_T("OnReceivedEnableDisableEventReport"));

	UbisamAddLog(strLog);
}

// S5F3(Alarm Enable/Disable Send)가 수신될 경우 발생하는 이벤트입니다.
void CUbiGem::OnReceivedEnableDisableAlarmSend()
{
	CString strLog;

	strLog.Format(_T("OnReceivedEnableDisableAlarmSend S5F3 RECV"));

	UbisamAddLog(strLog);
}

// S7F17(Date Time Reqeust)를 발송 후 Host에서 S7F18이 수신될 때 발생하는 이벤트입니다.
//Process Program Delete Request (by Host)
//Delete PPS
bool CUbiGem::OnResponseDateTimeRequest(UbiGEMWrapper::Structure::DateTime* timeData)
{
	CString strLog;

	strLog.AppendFormat(_T("OnResponseDateTimeRequest : [%04d-%02d-%02d  %02d:%02d:%02d:%02d]"), 
		timeData->Year, timeData->Month, timeData->Day, timeData->Hour, timeData->Minute, timeData->Second, timeData->MilliSecond / 10);

	UbisamAddLog(strLog);

	return true;
}

// S2F25(Loopback)을 발송 후 Host에서 S2F26이 수신될 때 발생하는 이벤트입니다.
void CUbiGem::OnResponseLoopback(UbiGEMWrapper::Structure::List<unsigned char>* receiveData, UbiGEMWrapper::Structure::List<unsigned char>* sendData)
{
	CString strLog;

	strLog.Format(_T("OnResponseLoopback : [receiveData=%d,sendData=%d]"), receiveData->GetCount(), sendData->GetCount());

	UbisamAddLog(strLog);
}

// S6F11(Event Report)의 Secondary Message(S6F12)가 수신될 경우 발생하는 이벤트입니다.
//RECV S6F12
void CUbiGem::OnResponseEventReportAcknowledge(LPCTSTR ceid, int ack)
{
	CString strLog;

	strLog.Format(_T("OnResponseEventReportAcknowledge : [CEID=%s,ACKC6=%d]"), ceid, ack);

	AddLog(strLog, 0, 0);
	if (_tcscmp(ceid, _T("10201")) == 0)
	{
		//EAC 
		if (ack == 0)
		{ 

		}
	}
	if (_tcscmp(ceid, OFFLINE_CHANGED_REPORT_10102) == 0)
	{
		//Offline Changed Report
		//offline 상태
	}
	if (_tcscmp(ceid, PROCESS_STATE_CHANGED_REPORT_10401) == 0)	//Lot Operation
	{
		g_clTaskWork[m_nUnit].bRecv_S6F12_Process_State_Change = 0;
		//
		//
		if (g_clMesCommunication[m_nUnit].m_dProcessState[1] == eSETUP)
		{

			//Ready를 보내기전에 

			//g_clMesCommunication[m_nUnit].m_dProcessState[0] = g_clMesCommunication[m_nUnit].m_dProcessState[1];
			//g_clMesCommunication[m_nUnit].m_dProcessState[1] = eREADY;

			//g_clMesCommunication[m_nUnit].m_uAlarmList.clear();

			//EventReportSendFn(PROCESS_STATE_CHANGED_REPORT_10401); //SEND S6F11
		}
		else if (g_clMesCommunication[m_nUnit].m_dProcessState[1] == eREADY)
		{
			//EventReportSendFn(PP_SELECTED_REPORT_10702);//SEND S6F11

		}
		else if (g_clMesCommunication[m_nUnit].m_dProcessState[1] == eEXECUTING)
		{
			//EventReportSendFn(LOT_PROCESSING_STARTED_REPORT_10704);//SEND S6F11 Lot Processing Started Report

		}
		else if (g_clMesCommunication[m_nUnit].m_dProcessState[1] == ePAUSE)
		{
			//Resume 가능하게 팝업 추가
			//Resume 되면 S6f11 다시 전송
			//eEXECUTING 로 변경
			if (g_ShowMsgModal(_T("확인"), _T("[AUTO] 자동운전 시작 하시겠습니까?"), RGB_COLOR_RED) == true)
			{
				g_clMesCommunication[m_nUnit].m_dProcessState[0] = g_clMesCommunication[m_nUnit].m_dProcessState[1];
				g_clMesCommunication[m_nUnit].m_dProcessState[1] = eEXECUTING;

				g_clMesCommunication[m_nUnit].m_uAlarmList.clear();

				g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(PROCESS_STATE_CHANGED_REPORT_10401, "");//SEND S6F11


				g_pCarAABonderDlg->OnBnClickedButtonMainAutoRun1();
			}


		}
		
	}
	if (_tcscmp(ceid, OBJECT_ID_REPORT_10701) == 0)
	{
		//uCtTimeOutData = 2;			//OBJECT_ID_REPORT_10701
		//KillTimer(WM_CT_TIMEOUT_TIMER);
		//SetTimer(WM_CT_TIMEOUT_TIMER, g_clMesCommunication[m_nUnit].ConversationTimeoutCount * 1000, NULL);
		//Object ID Report Return


	}
	if (_tcscmp(ceid, PP_SELECTED_REPORT_10702) == 0)
	{
		g_clTaskWork[m_nUnit].bRecv_S6F12_PP_Selected = 0;
	}
	if (_tcscmp(ceid, PP_UPLOAD_COMPLETED_REPORT_10703) == 0)
	{
		g_clTaskWork[m_nUnit].bRecv_S6F12_PP_UpLoad_Completed = 0;
	}
	
	if (_tcscmp(ceid, LOT_PROCESSING_STARTED_REPORT_10704) == 0)
	{
		g_clTaskWork[m_nUnit].bRecv_S6F12_Lot_Processing_Started = ack;		//ack 받는게 맞나?
		//착공 완료 상태
		//자동 운전 Start
		//이 다음에 LOT ID CANCEL이 될 수도 있다.
		if (ack == 0)
		{
			//이때 sTART?
		}
	}
	
	if (_tcscmp(ceid, LOT_PROCESSING_COMPLETED_REPORT_10710) == 0)	//Lot Processing Completed Report
	{
		g_clTaskWork[m_nUnit].bRecv_S6F12_Lot_Processing_Completed = 0;
		g_clTaskWork[m_nUnit].bRecv_S6F12_Lot_Processing_Completed_Ack = ack;
		
		if (ack != 0)
		{
			//팝업 
			//MES Lot Complted Failure!!!
			//LOT ID = 
			//버튼 2개
			//Close , Retry
			//g_pCarAABonderDlg->m_clMessageLot.setLotID(_T("111"));
			//g_pCarAABonderDlg->m_clMessageLot.ShowWindow(SW_SHOW);		//test
			//g_pCarAABonderDlg->EnableWindow(FALSE);
			//CString strValue;
			//
			//strValue.Format(_T("Lot Processing Completed Fail"));
			//g_ShowMsgPopup(_T("[INFO] command received from Host!!!"), strValue, RGB_COLOR_RED);

		}
	}
	if (_tcscmp(ceid, LOT_APD_REPORT_10711) == 0)	//Lot Apd Report
	{
		g_clTaskWork[m_nUnit].bRecv_S6F12_Lot_Apd = 0;
		///EventReportSendFn(LOT_PROCESSING_COMPLETED_REPORT_10710);//SEND S6F11
	}
	if (_tcscmp(ceid, OP_RECOGNIZED_TERMINAL_REPORT_10901) == 0)
	{
		//Enter Terminal Message !!! 
		//Optional Message

		//g_pCarAABonderDlg->m_clMessageInput.editInputReadOnly = false;
		//g_pCarAABonderDlg->m_clMessageInput.setEditInput(_T("Terminal Services"), _T("Enter Terminal Message !!!"));
		//g_pCarAABonderDlg->m_clMessageInput.ShowWindow(SW_SHOW);

	}
	
	UbisamAddLog(strLog);
}

// Host에서 S7F1(PP Load Inquire)가 수신될 때 발생하는 이벤트입니다.
void CUbiGem::OnReceivedPPLoadInquire(unsigned int systemBytes, LPCTSTR ppid, int length)
{
	CString strLog;

	strLog.AppendFormat(_T("OnReceivedPPLoadInquire : [SystemByte=%d,PPID=%s,LENGTH=%d]"), systemBytes, ppid, length);

	UbisamAddLog(strLog);

	if (m_pWrapper != nullptr)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyPPLoadInquireAck(systemBytes, m_iAck);

		UbisamAddLog(_T("ReplyPPLoadInquireAck"), gemResult);
	}
}

// Host에서 S7F3(PP Send)가 수신될 때 발생하는 이벤트입니다
void CUbiGem::OnReceivedPPSend(unsigned int systemBytes, LPCTSTR ppid, UbiGEMWrapper::Structure::List<unsigned char>* ppbody)
{
	CString strLog;

	strLog.AppendFormat(_T("OnReceivedPPSend : [PPID=%s]"), ppid);
	UbisamAddLog(strLog);

	if (m_pWrapper != nullptr)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyPPSendAck(systemBytes, m_iAck);
		UbisamAddLog(_T("ReplyPPSendAck"), gemResult);
	}

}

// Host에서 S7F23(Formatted PP Send)가 수신될 때 발생하는 이벤트입니다. Formatted Process Program
void CUbiGem::OnReceivedFmtPPSend(unsigned int systemBytes, UbiGEMWrapper::Structure::FmtPPCollection* fmtPPCollection)
{
	TCHAR szLog[SIZE_OF_1K];
	CString strLog;
	strLog.Empty();
	strLog.AppendFormat(_T("OnReceivedFmtPPSend: [PPID=%s]"), fmtPPCollection->PPID);
	int i = 0;
	int j = 0;

	UbiGEMWrapper::Structure::RemoteCommandResult* pResult = nullptr;
	
	CString RecvStrData;
	CString RecvPPId;
	RecvPPId.Empty();
	int RecvIntData = 0;
	RecvStrData.Empty();

	
	////pResult = m_pWrapper->CreateRemoteCommandResult(m_iAck);

	_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] OnReceivedFmtPPSend Recv"), fmtPPCollection->PPID);
	AddLog(szLog, 0, 0);


	PP_RECIPE_SPEC ppRsOnReceived;
	std::string sCommandCode;

	if (fmtPPCollection->Items != nullptr) 
	{
		UbiGEMWrapper::Structure::FmtPPCCodeInfo* pFPPInfo = nullptr;

		
		
		ppRsOnReceived.parmName.clear();
		ppRsOnReceived.parmMap.clear();
		ppRsOnReceived.parmMapChk.clear();
		
		ppRsOnReceived.PPId = fmtPPCollection->PPID;
		ppRsOnReceived.VERSION = fmtPPCollection->SOFTREV;

		int rRootCount = fmtPPCollection->Items->GetCount();
		int subCount = 0;
		if (rRootCount > 0)
		{
			for (i = 0; i < 1; i++)//Commandcode 하나로만 들어온다.
			{
				strLog.AppendFormat(_T("\r\n:   [CommandCode=%s]"), fmtPPCollection->GetFmtPPCCodeInfo(i)->CommandCode);

				pFPPInfo = fmtPPCollection->Items->At(i);
				sCommandCode = fmtPPCollection->GetFmtPPCCodeInfo(i)->CommandCode;
				subCount = pFPPInfo->Items->GetCount();

				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] CommandCode:%s"), fmtPPCollection->PPID, sCommandCode.c_str());
				AddLog(szLog, 0, 0);

				if (sCommandCode == "CREATE")	//5.11.6 New Process Program Creation (by Host)
				{
					g_clMesCommunication[m_nUnit].m_dPPChangeArr[0] = eCreated;		//2 = Created
					g_clMesCommunication[m_nUnit].m_dPPChangeArr[1] = eHost;		//1 = Host, 2 = Operator
				}
				else if (sCommandCode == "SET_VALUE")	//Change Parameter Value by Host
				{
					g_clMesCommunication[m_nUnit].m_dPPChangeArr[0] = eEdited;		//2 = Edited
					g_clMesCommunication[m_nUnit].m_dPPChangeArr[1] = eHost;		//1 = Host, 2 = Operator



					//if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO || g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
					//{
					//	UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyFmtPPSendAck(systemBytes, 1);// m_iAck);		//자동중 확인필요 막을건지
					//	UbisamAddLog(_T("ReplyFmtPPSend Nack "), gemResult);
					//	return;
					//}
				}
				else if (sCommandCode == "CHANGE_UPLOAD_LIST")		//항목이 다 안올수도있다.
				{
					g_clMesCommunication[m_nUnit].m_dPPChangeArr[0] = eUploadListChanged;		//4 = UploadListChanged
					g_clMesCommunication[m_nUnit].m_dPPChangeArr[1] = eHost;		//1 = Host, 2 = Operator

					//해당 PPID XML파일을 불러와서 세팅해놓고 for문에 타는건 check  = true
				}

				else if (sCommandCode == "CHANGE_UPLOAD_LIST_ALL")		//CHANGE_UPLOAD_LIST_ALL <--host에서 Recipe 만들때 사용
				{
					g_clMesCommunication[m_nUnit].m_dPPChangeArr[0] = eUploadListChanged;		//4 = UploadListChanged
					g_clMesCommunication[m_nUnit].m_dPPChangeArr[1] = eHost;		//1 = Host, 2 = Operator
				}

				for (j = 0; j < subCount; j++)
				{
					strLog.AppendFormat(_T("\r\n:      [CPNAME=%s,Format=%s,Count=%s]"), pFPPInfo->Items->At(j)->PPName,SECSFormatAsString(pFPPInfo->Items->At(j)->Format),pFPPInfo->Items->At(j)->PPValue);


					ppRsOnReceived.parmName.push_back(pFPPInfo->Items->At(j)->PPName);
					ppRsOnReceived.parmMapChk[pFPPInfo->Items->At(j)->PPName] = "1";
					ppRsOnReceived.parmMap[pFPPInfo->Items->At(j)->PPName] = pFPPInfo->Items->At(j)->PPValue;
					//
					//
					if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip.size() > 0 && sCommandCode == "SET_VALUE")	//==||==
					{
						if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].PPId == ppRsOnReceived.PPId)
						{
							g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmMap[pFPPInfo->Items->At(j)->PPName] = pFPPInfo->Items->At(j)->PPValue;
						}
					}
					
				}

				if (subCount > 0)
				{
					std::vector<_PP_RECIPE_SPEC> vFmtPPSend__HostSepc;
					
					vFmtPPSend__HostSepc.clear();
					vFmtPPSend__HostSepc.push_back(ppRsOnReceived);

					//----------------------------------------------------------------------------------------
					//
					if (sCommandCode == "SET_VALUE")		//==||==
					{
						//RecipeIniSave = 있는 항목은 수정되고, 없으면 추가된다 INI파일이라서
						if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].PPId == ppRsOnReceived.PPId)
						{
							g_clMesCommunication[m_nUnit].RecipeIniSave(g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip);		//Equip
						}
						else
						{
							g_clMesCommunication[m_nUnit].RecipeIniSave(vFmtPPSend__HostSepc);		//host
						}
					}
					else if (sCommandCode == "CREATE")
					{
						g_clMesCommunication[m_nUnit].RecipeIniSave(vFmtPPSend__HostSepc);		//host

						ModelList.iniRecipeListLoad();	//XML 파일 생성후 전체 LIST LOAD
						g_pCarAABonderDlg->m_clMainDlg.setRecipeComboBox();	//Recipe 콤보박스 갱신

					}
					else if (sCommandCode == "CHANGE_UPLOAD_LIST" || sCommandCode == "CHANGE_UPLOAD_LIST_ALL")
					{
						int pCnt = ppRsOnReceived.parmMap.size();
						if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].PPId == ppRsOnReceived.PPId)
						{
							for (auto& pair : g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmMapChk)
							{
								pair.second = "0";  // 모든 값(value)을 "0"으로 변경
							}
							//현재 레시피
							for (i = 0; i < pCnt; i++)
							{
								g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmMapChk[ppRsOnReceived.parmName[i]] = "1";
							}
							g_clMesCommunication[m_nUnit].RecipeIniSave(g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip);		//Equip
						}
						else
						{
							//미사용 레시피는 로드해서 적용하고 저장
							vFmtPPSend__HostSepc.clear();
							vFmtPPSend__HostSepc = g_clMesCommunication[m_nUnit].RecipeIniLoad(ppRsOnReceived.PPId.c_str());
							if (vFmtPPSend__HostSepc.size() > 0)
							{
								for (auto& pair : vFmtPPSend__HostSepc[0].parmMapChk)
								{
									pair.second = "0";  // 모든 값(value)을 "0"으로 변경
								}
								for (i = 0; i < pCnt; i++)
								{
									vFmtPPSend__HostSepc[0].parmMapChk[ppRsOnReceived.parmName[i]] = "1";
								}
								g_clMesCommunication[m_nUnit].RecipeIniSave(vFmtPPSend__HostSepc);		//host
							}
						}
					}
					g_pCarAABonderDlg->m_clMainDlg.showRecipeGrid();	//Grid Refresh
				}//end If, subCount
			}//end For
		}//end rRootCount
	}//if (fmtPPCollection->Items != nullptr) 

	//End
	UbisamAddLog(strLog);
	UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyFmtPPSendAck(systemBytes, m_iAck);		//SEND S7F24 (전체적으로 불가하다는걸 명기)
	UbisamAddLog(_T("ReplyFmtPPSendAck"), gemResult);

	///m_pWrapper->DeleteRemoteCommandResult(pResult);//250114
	///pResult = nullptr;
	if (m_pWrapper != nullptr)
	{
		//여기서 바로 S6F11?
		
		if (sCommandCode == "SET_VALUE")		//==||==
		{
			//Host 에서 Parameter 적용요청했는데 불가할 경우 전송 // TODO:S7F27 SET_VALUE 적용불가시 전송하기 250217
			// 
			//RequestFmtPPVerificationSend 는 SET_VALUE에만 대응 250115
			//HOST 로 받은 parameter 적용
			

			//S7F27 보내 Process Program Verification Send
			//ProcessProgramStateChangedReport Send
			//RequestFmtPPVerificationSend
			UbiGEMWrapper::Structure::FmtPPVerificationCollection* pFmtPPVerificationCollection;
			pFmtPPVerificationCollection = m_pWrapper->CreateFmtPPVerificationCollection(fmtPPCollection->PPID);

			if (g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip.size() < 1)	//없을 때만 보냄
			{
				//적용 실패
				CString strValue;
				//
				strValue.Format(_T("[%s] Recipe Save Fail"), fmtPPCollection->PPID);
				g_ShowMsgPopup(_T("[OnReceivedFmtPPSend] command received from Host!!!"), strValue, RGB_COLOR_RED);
				AddLog(strValue, 0, 0);


				int count = ppRsOnReceived.parmMap.size();
				for (i = 0; i < count; i++)
				{
					pFmtPPVerificationCollection->AddFmtPPVerificationInfo(1, i, "EMPTY");
					//g_clMesCommunication[m_nUnit].vPPRecipeSpecEquip[0].parmMapChk[ppRsOnReceived.parmName[i]] = "1";
				}
				///pFmtPPVerificationCollection->AddFmtPPVerificationInfo(0, 1, "test");


				//
			}
				UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->RequestFmtPPVerificationSend(pFmtPPVerificationCollection);	// SEND S7F27 (
				UbisamAddLog(_T("RequestFmtPPVerificationSend"), gemResult);

				AddLog(_T("RequestFmtPPVerificationSend"), 0, 0);

				m_pWrapper->DeleteFmtPPVerificationCollection(pFmtPPVerificationCollection);

			
		}
		else
		{
			AddLog(_T("PROCESS_PROGRAM_STATE_CHANGED_REPORT_10601 Send"), 0, 0);
			EventReportSendFn(PROCESS_PROGRAM_STATE_CHANGED_REPORT_10601, fmtPPCollection->PPID); //SEND S6F11
		}
	}
}

// S7F1(PP Load Inquire)를 발송 후 Host에서 S7F2가 수신될 때 발생하는 이벤트입니다.
void CUbiGem::OnResponsePPLoadInquire(int ppgnt, LPCTSTR ppid)
{
	CString strLog;

	strLog.AppendFormat(_T("OnResponsePPLoadInquire: [PPGNT=%d,PPID=%s]"), ppgnt, ppid);

	UbisamAddLog(strLog);
}

// S7F3(PP Send)를 발송 후 Host에서 S7F4가 수신될 때 발생하는 이벤트입니다.
void CUbiGem::OnResponsePPSend(int ack, LPCTSTR ppid)
{
	CString strLog;

	strLog.AppendFormat(_T("OnResponsePPLoadInquire: [ACKC7=%d,PPID=%s]"), ack, ppid);

	UbisamAddLog(strLog);
}

// S7F5(PP Request)를 발송 후 Host에서 S7F6이 수신될 때 발생하는 이벤트입니다.
void CUbiGem::OnResponsePPRequest(LPCTSTR ppid, UbiGEMWrapper::Structure::List<unsigned char>* ppbody)
{
	CString strLog;

	byte* pArrBuf;
	size_t lCount;

	pArrBuf = nullptr;

	strLog.AppendFormat(_T("OnResponsePPRequest: [PPID=%s]"), ppid);

	if (ppbody != nullptr)
	{
		lCount = ppbody->GetCount();

		if (lCount > 0)
		{
			pArrBuf = new byte[lCount];

			for (int i = 0; i < lCount; i++)
			{
				pArrBuf[i] = ppbody->At(i);
			}

			// pArrBuf를 File로 저장 또는 다른 처리

			delete[] pArrBuf;
			pArrBuf = nullptr;
		}
	}

	UbisamAddLog(strLog);
}

// S7F25(Formatted PP Send)를 발송 후 Host에서 S7F26이 수신될 때 발생하는 이벤트입니다.
void CUbiGem::OnResponseFmtPPSend(int ack, UbiGEMWrapper::Structure::FmtPPCollection* fmtPPCollection)
{
	CString strLog;

	strLog.Format(_T("OnResponseFmtPPSend : [ACKC6=%d,PPID=%s]"), ack, fmtPPCollection->PPID); 

	UbisamAddLog(strLog);
}

// S2F23(Formatted PP Request) 발송 후 Host에서 S2F24가 수신될 때 발생하는 이벤트입니다.
//설비에서 DOWNLOAD REQ 요청 후 받는 곳
//설비에서 S7F25 발송 후 S7S26 수신될때 
void CUbiGem::OnResponseFmtPPRequest(UbiGEMWrapper::Structure::FmtPPCollection* fmtPpCollection)
{
	CString strLog;

	strLog.Format(_T("OnResponseFmtPPRequest : [PPID=%s]"), fmtPpCollection->PPID);


#if 1
	int i = 0;
	int j = 0;
	if (fmtPpCollection != nullptr)
	{
		if (fmtPpCollection->Items != nullptr)
		{
			UbiGEMWrapper::Structure::FmtPPCCodeInfo* pFPPInfo = nullptr;
			UbiGEMWrapper::Structure::FmtPPItem* pFFItem = nullptr;

			///pEcpInfo = remoteCommand->EnhancedCommandParameter->Items->At(i);
			///if (pEcpInfo->Format == UbiGEMWrapper::Structure::GEMSECSFormat_L)		// -------------- List

			PP_RECIPE_SPEC ppRs;

			ppRs.parmName.clear();
			//ppRs.parmVal.clear();
			ppRs.PPId = fmtPpCollection->PPID;

			std::vector<_PP_RECIPE_SPEC> vPPRecipeSpec__Host;
			vPPRecipeSpec__Host.clear();
			//g_clMesCommunication[m_nUnit].vPPRecipeSpecHost = g_clMesCommunication[m_nUnit].RecipeXmlLoad(fmtPpCollection->PPID);
			vPPRecipeSpec__Host = g_clMesCommunication[m_nUnit].RecipeIniLoad(fmtPpCollection->PPID);	////RecipeIniLoad 한 상태에서 push_back 하면 중복된다.
			////RecipeIniLoad 한 상태에서 push_back 하면 중복된다.

			int nLoadCount = vPPRecipeSpec__Host.size();
			if (nLoadCount > 0)
			{
				ppRs = vPPRecipeSpec__Host[0];
				ppRs.parmName.clear();
				//ppRs.parmVal.clear();
				ppRs.parmMapChk.clear();
				ppRs.parmMap.clear();
				
			}
			else
			{
				ppRs.PPId = fmtPpCollection->PPID;
				ppRs.VERSION = "1";
			}
			
			int rRecvCount = fmtPpCollection->Items->GetCount();
			if (rRecvCount > 0)
			{
				for (i = 0; i < 1; i++)//Commandcode 하나로만 들어온다.
				{
					strLog.AppendFormat(_T("\r\n:   [CommandCode=%s]"), fmtPpCollection->GetFmtPPCCodeInfo(i)->CommandCode);
					pFPPInfo = fmtPpCollection->Items->At(i);
					int subCount = pFPPInfo->Items->GetCount();
					for (j = 0; j < subCount; j++)
					{
						strLog.AppendFormat(_T("\r\n:      [CPNAME=%s,Format=%s,Count=%s]"), pFPPInfo->Items->At(j)->PPName, SECSFormatAsString(pFPPInfo->Items->At(j)->Format), pFPPInfo->Items->At(j)->PPValue);

						//_stprintf_s(ppRs.sName, SIZE_OF_100BYTE, _T("%s"), pFPPInfo->Items->At(j)->PPName);
						///ppRs.parmChecked.push_back(true);	//<--확인필요 위에서 적용

						if (nLoadCount < 1 || ppRs.parmMapChk.size() < 1)
						{
							//ppRs.parmChecked.push_back("1");
							ppRs.parmMapChk[pFPPInfo->Items->At(j)->PPName] = "1";
						}
						
						ppRs.parmName.push_back(pFPPInfo->Items->At(j)->PPName);//RecipeIniLoad 한 상태에서 push_back 하면 중복된다.
						//ppRs.parmVal.push_back(pFPPInfo->Items->At(j)->PPValue);
						
						
						ppRs.parmMap[pFPPInfo->Items->At(j)->PPName] = pFPPInfo->Items->At(j)->PPValue;

					}



				}
				vPPRecipeSpec__Host.clear();
				vPPRecipeSpec__Host.push_back(ppRs);

				//S7F26 받은 apply , cancel 팝업
				//apply 클릭후 
				//S6F11 - Send Event Report
				//Event = Process Program State Changed Report

				//int result = AfxMessageBox(_T("Apply Host Recipe Confirm!!!"), MB_YESNO | MB_ICONQUESTION);
				CWnd* pMainWnd = AfxGetMainWnd();  // 메인 윈도우 가져오기

												   // 메시지 박스 표시 (제목을 "Confirmation"으로 설정)
				//SetWindowPos(pMainWnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				g_pCarAABonderDlg->EnableWindow(FALSE);
				int result = pMainWnd->MessageBox(_T("Apply Host Recipe Parameter Value?"), _T("Apply Host Recipe Confirm!!!"), MB_YESNO | MB_ICONQUESTION | MB_SERVICE_NOTIFICATION);
				g_pCarAABonderDlg->EnableWindow(TRUE);

				if (result == IDYES) 
				{
					
					g_clMesCommunication[m_nUnit].m_dPPChangeArr[0] = eEdited;		//2 (Edited)
					g_clMesCommunication[m_nUnit].m_dPPChangeArr[1] = eOperator;		//1 = Host, 2 = Operator


					g_clMesCommunication[m_nUnit].RecipeIniSave(vPPRecipeSpec__Host);	// 

					EventReportSendFn(PROCESS_PROGRAM_STATE_CHANGED_REPORT_10601, vPPRecipeSpec__Host[0].PPId.c_str()); //SEND S6F11
				}
				else if (result == IDNO) 
				{
					// 사용자가 No를 선택한 경우
					//AfxMessageBox(_T("You clicked No."));
				}
			}
			else
			{
				TCHAR szLog[SIZE_OF_1K];

				_stprintf_s(szLog, SIZE_OF_1K, _T("[%s] RECIPE EMPTY!"), fmtPpCollection->PPID);
				AddLog(szLog, 0, 0);
				g_ShowMsgPopup(_T("INFO"), szLog, RGB_COLOR_RED, 0, opCallType);
			}
		}
	}
#endif
	UbisamAddLog(strLog);
}

// S2F27(Formatted PP Verification Send)를 발송 후 Host에서 S2F28이 수신될 때 발생하는 이벤트입니다.
void CUbiGem::OnResponseFmtPPVerification(UbiGEMWrapper::Structure::FmtPPVerificationCollection* fmtPPVerificationCollection)
{
	CString strLog;

	strLog.Format(_T("OnResponseFmtPPVerification : [PPID=%s]"), fmtPPVerificationCollection->PPID);

	UbisamAddLog(strLog);
}

void CUbiGem::OnResponseTerminalRequest(int ack)
{
	CString strLog;

	strLog.Format(_T("OnResponseTerminalRequest : [ACKC10=%d]"), ack);

	UbisamAddLog(strLog);
}

// S2F17(Date Time Reqeust)가 수신될 경우 발생하는 이벤트입니다.
void CUbiGem::OnReceivedDateTimeRequest(unsigned int systemBytes, UbiGEMWrapper::Structure::DateTime* timeData)
{
	CTime time;
	CString strLog;

	if (m_pWrapper != nullptr)
	{
		time = CTime::GetCurrentTime();
		timeData->Year = time.GetYear();
		timeData->Month = time.GetMonth();
		timeData->Day = time.GetDay();
		timeData->Hour = time.GetHour();
		timeData->Minute = time.GetMinute();
		timeData->Second = time.GetSecond();

		strLog.AppendFormat(_T("OnReceivedDateTimeRequest : [TimeData=%04d-%02d-%02d  %02d:%02d:%02d]"), timeData->Year, timeData->Month, timeData->Day, timeData->Hour, timeData->Minute, timeData->Second);

		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyDateTimeRequest(systemBytes, timeData);

		UbisamAddLog(_T("ReplyDateTimeRequest"), gemResult);
	}
}

// S2F31(Date Time Set Request)가 수신될 경우 발생하는 이벤트입니다.
void CUbiGem::OnReceivedDateTimeSetRequest(unsigned int systemBytes, UbiGEMWrapper::Structure::DateTime* timeData)
{
	CString strLog;

	if (timeData != nullptr)
	{
		strLog.AppendFormat(_T("OnReceivedDataTimeSetRequest : [TimeData=%04d-%02d-%02d  %02d:%02d:%02d:%02d]"), timeData->Year, timeData->Month, timeData->Day, timeData->Hour, timeData->Minute, timeData->Second, timeData->MilliSecond / 10);

		SYSTEMTIME st;
		GetLocalTime(&st); // 현재 로컬 시간 가져오기 (초기값 참고용)
		st.wYear = timeData->Year;
		st.wMonth = timeData->Month;
		st.wDay = timeData->Day;
		st.wHour = timeData->Hour;
		st.wMinute = timeData->Minute;
		st.wSecond = timeData->Second;
		// 시스템 로컬 시간 설정


		CString strTimeLog;
		if (!SetLocalTime(&st)) 
		{
			//AfxMessageBox(_T("시간 설정 실패. 관리자 권한이 필요합니다."));
			strTimeLog.Format(_T("Time setting failed. Administrator privileges are required."));
			UbisamAddLog(strTimeLog);
		}
		else 
		{
			//AfxMessageBox(_T("시간이 성공적으로 변경되었습니다."));
			strTimeLog.Format(_T("Time has been changed successfully."));
			UbisamAddLog(strTimeLog);
		}
	}
	else
	{
		strLog.AppendFormat(_T("OnReceivedDataTimeSetRequest : [TimeData is null]"));
	}

	UbisamAddLog(strLog);

	if (m_pWrapper != nullptr)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyDateTimeSetRequest(systemBytes, this->m_iAck, timeData);
		UbisamAddLog(_T("ReplyDateTimeSetRequest"), gemResult);
	}
}

// S7F5(PP Reqeust)가 수신될 경우 발생하는 이벤트입니다
void CUbiGem::OnReceivedPPRequest(unsigned int systemBytes, LPCTSTR ppid)
{
	CString strLog;
	UbiGEMWrapper::Structure::List<uint8_t>* ppBody;

	strLog.AppendFormat(_T("OnReceivedPPRequest : [PPID=%s]"), ppid);
	UbisamAddLog(strLog);

	bool result = true;

	if (m_pWrapper != nullptr)
	{
		// Recipe(Process Program)을 못찾을 경우 result 를 false 로 설정
		// result = false;
		ppBody = m_pWrapper->CreateU1List();
		MakePPBody(ppBody);

		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyPPRequestAck(systemBytes, ppid, ppBody, result);

		m_pWrapper->DeleteU1List(ppBody);
		ppBody = nullptr;

		UbisamAddLog(_T("ReplyPPreqeustAck"), gemResult);
	}
}

// S7F25(Formatted PP Reqeust)가 수신될 경우 발생하는 이벤트입니다
// HOST에서 S7F25 Formatted Process Program Request 보낼 때
//
void CUbiGem::OnReceivedFmtPPRequest(unsigned int systemBytes, LPCTSTR ppid)
{
	CString strLog;
	UbiGEMWrapper::Structure::FmtPPCollection* pFmtPPCollection;
	bool result = true;

	strLog.AppendFormat(_T("OnReceivedFmtPPRequest : [PPID=%s]"), ppid);
	UbisamAddLog(strLog);

	if (m_pWrapper != nullptr)
	{
		//uCtTimeOutData = 3;		//S7F26 Host로 보내는 부분 OnReceivedFmtPPRequest
		//KillTimer(WM_CT_TIMEOUT_TIMER);
		//SetTimer(WM_CT_TIMEOUT_TIMER, g_clMesCommunication[m_nUnit].ConversationTimeoutCount * 1000, NULL);
		// Recipe(Process Program)을 못찾을 경우 result 를 false 로 설정
		// result = false;
		

		//PPID 에 대한 값 요청
		//xml Load

		std::vector<PP_RECIPE_SPEC> LoadData;
		LoadData = g_clMesCommunication[m_nUnit].RecipeIniLoad(ppid);///S7F25  OnReceivedFmtPPRequest
		pFmtPPCollection = m_pWrapper->CreateFmtPPCollection(ppid);
		bool rtn = true;
		
		if (LoadData.size() < 1)
		{
			rtn = false;
		}
		ProcessProgramParsing(rtn, pFmtPPCollection, LoadData);	//ini파일에서 로드한 값을 host로 보낸다.

		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyFmtPPRequestAck(systemBytes, ppid, pFmtPPCollection, rtn);// result);

		if (pFmtPPCollection != nullptr)
		{
			m_pWrapper->DeleteFmtPPCollection(pFmtPPCollection);
		}
		pFmtPPCollection = nullptr;


		UbisamAddLog(_T("ReplyFmtPPRequestAck"), gemResult);
		
		g_clTaskWork[m_nUnit].bRecv_S7F25_Formatted_Process_Program = 0;
	}
}

// S7F17(Delete PP Send)가 수신될 경우 발생하는 이벤트입니다.
void CUbiGem::OnReceivedDeletePPSend(unsigned int systemBytes, UbiGEMWrapper::Structure::List<LPCTSTR>* ppids)
{
	CString strLog;
	CString delPPid = _T("");
	if (ppids != nullptr)
	{
		strLog.AppendFormat(_T("OnReceivedDeletePPSend : [Count=%d]"), ppids->GetCount());

		for (int i = 0; i < ppids->GetCount(); i++)
		{
			// ppid에 해당하는 Recipe(Process Program) 파일 삭제 진행
			strLog.AppendFormat(_T("\r\n%s "), ppids->At(i));
			delPPid.Format(_T("%s") , ppids->At(i));
			ModelList.xmlRecipeDelete(ppids->At(i));		//RECIPE XML FILE DELETE
		}
	}
	else
	{
		strLog.AppendFormat(_T("OnReceivedDeletePPSend : [ppids is null]"), ppids->GetCount());
	}

	UbisamAddLog(strLog);

	if (m_pWrapper != nullptr)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyPPDeleteAck(systemBytes, m_iAck);
		UbisamAddLog(_T("ReplyPPDeleteAck"), gemResult);




		//
		//S6F11 - Send Event Report
		//Event = Process Program State Changed Report - Deleted
		//해당 PPID 파일을 삭제해야한다.
		g_clMesCommunication[m_nUnit].m_dPPChangeArr[0] = eDeleted;		//3 (Deleted)
		g_clMesCommunication[m_nUnit].m_dPPChangeArr[1] = eHost;		//1 = Host, 2 = Operator


		EventReportSendFn(PROCESS_PROGRAM_STATE_CHANGED_REPORT_10601, delPPid);	//Delete xxxxx
	}
}
// S7F19(Current EPPD Request)가 수신될 경우 발생하는 이벤트입니다.
void CUbiGem::OnReceivedCurrentEPPDRequest(unsigned int systemBytes)
{
	CString strLog;
	UbiGEMWrapper::Structure::List<LPCTSTR>* ppids;

	strLog.Format(_T("ReceivedCurrentEPPDRequest"));
	UbisamAddLog(strLog);

	if (m_pWrapper != nullptr)
	{
		ppids = m_pWrapper->CreateStringList();

		// 현재 저장되어 있는 Recipe(Process Program) 파일의 목록을 사용해야 합니다.

		//int mCount = ModelList.m_clRecipeList.GetCount();
		int mCount = ModelList.m_vRecipeVec.size();

		
		for (int i = 0; i < mCount; i++)
		{
			//ppids->Add(ModelList.m_clRecipeList[i].m_szName);
			ppids->Add(ModelList.m_vRecipeVec[i].c_str());
		}

		//ppids->Add(RECIPE_LIST_NAME[0]);
		//ppids->Add(RECIPE_LIST_NAME[1]);
		//ppids->Add(_T("PPID03"));

		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReplyCurrentEPPDRequestAck(systemBytes, ppids, true);

		m_pWrapper->DeleteStringList(ppids, false);

		UbisamAddLog(_T("ReplyCurrentEPPDRequestAck"), gemResult);
		ppids = nullptr;
	}

}
// 사용자 정의 Message로 등록한 Stream, Function 중 Primary 메시지가 수신될 경우 발생하는 이벤트입니다.
void CUbiGem::OnUserPrimaryMessageReceived(UbiGEMWrapper::Structure::SECSMessage* pPrimaryMessage)
{
	CString strLog;
	UbiGEMWrapper::Structure::SECSMessage* pSecondaryMessage;

	strLog.AppendFormat(_T("OnUserPrimaryMessageReceived : [Stream=%d,Function=%d,Name=%s]"), pPrimaryMessage->Stream, pPrimaryMessage->Function, pPrimaryMessage->Name);

	UbisamAddLog(strLog);

	if (m_pWrapper != nullptr)
	{
		if (pPrimaryMessage->Stream == 99 && pPrimaryMessage->Function == 1)
		{
			pSecondaryMessage = m_pWrapper->CreateUserMessage(_T("S99F2"), pPrimaryMessage->Stream, pPrimaryMessage->Function + 1, false, true);

			if (pSecondaryMessage != nullptr)
			{
				pSecondaryMessage->Body->AddSECSItem(_T("ACKC99"), UbiGEMWrapper::Structure::GEMSECSFormat_B, m_iAck);
				m_pWrapper->ReplySECSMessage(pPrimaryMessage, pSecondaryMessage);

				m_pWrapper->DeleteSECSMessage(pSecondaryMessage);
				pSecondaryMessage = nullptr;
			}
		}
	}
}
// 사용자 정의 Message로 등록한 Stream, Function 중 Secondary 메시지가 수신될 경우 발생하는 이벤트입니다.
void CUbiGem::OnUserSecondaryMessageReceived(UbiGEMWrapper::Structure::SECSMessage* primaryMessage, UbiGEMWrapper::Structure::SECSMessage* secondaryMessage)
{
	CString strLog;

	strLog.AppendFormat(_T("OnUserSecondaryMessageReceived"));

	if (primaryMessage == nullptr)
	{
		strLog.AppendFormat(_T("\r\n:   PrimaryMessage is null"));
	}
	else
	{
		strLog.AppendFormat(_T("\r\n:   PrimaryMessage : [Stream=%d,Function=%d,Name=%s]"), primaryMessage->Stream, primaryMessage->Function, primaryMessage->Name);
	}

	if (secondaryMessage == nullptr)
	{
		strLog.AppendFormat(_T("\r\n:   SecondaryMessage is null"));
	}
	else
	{
		strLog.AppendFormat(_T("\r\n:   SecondaryMessage : [Stream=%d,Function=%d,Name=%s]"), secondaryMessage->Stream, secondaryMessage->Function, secondaryMessage->Name);
	}

	UbisamAddLog(strLog);
}

// Communication State가 변경될 경우 발생하는 이벤트입니다.
void CUbiGem::OnCommunicationStateChanged(UbiGEMWrapper::Structure::GEMCommunicationState communicationState)
{
	CString strLog;

	strLog.AppendFormat(_T("OnCommunicationStateChanged : [CommunicationState=%d]"), communicationState);

	UbisamAddLog(strLog);

}
// Control State가 변경될 경우 발생하는 이벤트입니다.
void CUbiGem::OnControlStateChanged(UbiGEMWrapper::Structure::GEMControlState controlState)
{
	CString strLog;

	strLog.Format(_T("OnControlStateChanged : [ControlState=%d]"), controlState);

	UbisamAddLog(strLog);

	UpdateDialogTitle();
}
void CUbiGem::OnControlStateOnlineChangeFailed()
{
	CString strLog;

	strLog.Format(_T("OnControlStateOnlineChangeFailed"));

	UbisamAddLog(strLog);

	UpdateDialogTitle();
}

// EquipmentProcess State가 변경될 경우 발생하는 이벤트입니다.
void CUbiGem::OnEquipmentProcessState(unsigned char equipmentProcessState)
{
	CString strLog;

	strLog.Format(_T("OnEquipmentProcessState : [EquipmentProcessstate=%d]"), equipmentProcessState);

	UbisamAddLog(strLog);
}


// ReportCollectionEvent 메소드를 호출하고, Variable 정보의 Update가 필요할 때 발생하는 이벤트입니다.
// variables 순회하고, Value를 assign 하는 코드입니다.
// DLL 내부에서 데이터의 타입에 따라 변환합니다.
void CUbiGem::OnVariableUpdateRequest(UbiGEMWrapper::Structure::GEMVariableUpdateType updateType, UbiGEMWrapper::Structure::List<LPCTSTR>* vids)
{
	CString strLog = _T("");

	strLog.Format(_T("OnVariableUpdateRequest : [Count=%d]"), vids->GetCount());
	UbisamAddLog(strLog);

	CString strCEID = _T("");
	strCEID.Format(_T("%s"), strSendCeId);
	int i = 0;
	int j = 0;
	int nVid = 0;

	if (m_pWrapper != nullptr)
	{
		for (i = 0, j = 0; i < vids->GetCount(); i++)
		{
			CString vid = vids->At(i);
			nVid = atoi(vid);

			if (vid == _T("10001"))	//EquipmentID
			{
				//UbiGEMWrapper::Structure::VariableInfo* dataValue;

				//
				//dataValue = m_pWrapper->CreateVariable(vid, UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("EquipmentID"));
				//dataValue->SetValue(g_clMesCommunication[m_nUnit].m_sEquipmentID);
				//m_pWrapper->SetVariable(dataValue); 
			}
			if (vid == _T("10002"))	//EquipmentName
			{
				//UbiGEMWrapper::Structure::VariableInfo* dataValue;

				//
				//dataValue = m_pWrapper->CreateVariable(vid, UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("EquipmentName"));
				//dataValue->SetValue(g_clMesCommunication[m_nUnit].m_sEquipmentName);
				//m_pWrapper->SetVariable(dataValue);
			}
			if (vid == _T("10003"))	//Time
			{
				CTime cTime = CTime::GetCurrentTime();
				CString strData = _T(""); 
				strData.Format(_T("%02d%02d%02d%02d%02d%02d"),
					cTime.GetYear()%100,
					cTime.GetMonth(),
					cTime.GetDay(),
					cTime.GetHour(),
					cTime.GetMinute(),
					cTime.GetSecond());


				//dataValue = m_pWrapper->CreateVariable(vid, UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("Time"));
				//dataValue->SetValue(strData);
				//m_pWrapper->SetVariable(dataValue);

				m_pWrapper->SetVariable(vid, strData);
			}
			if (vid == _T("10008"))	//OperatorID
			{
				//UbiGEMWrapper::Structure::VariableInfo* dataValue;

				//
				//dataValue = m_pWrapper->CreateVariable(vid, UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("OperatorID"));
				//dataValue->SetValue(g_clMesCommunication[m_nUnit].m_sMesOperatorID);

				m_pWrapper->SetVariable(vid, g_clMesCommunication[m_nUnit].m_sMesOperatorID);
			}
			if (vid == _T("10010"))	//ControlStateChangeOrder 
			{
				UbiGEMWrapper::Structure::VariableInfo* dataValue;

				//
				dataValue = m_pWrapper->CreateVariable(vid, UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("ControlStateChangeOrder"));
				dataValue->SetValue((uint8_t)g_clMesCommunication[m_nUnit].m_dControlStateChangeOrder);// 2);
				m_pWrapper->SetVariable(dataValue);
			}
			if(vid == _T("10014"))
			{
				UbiGEMWrapper::Structure::VariableInfo* dataMainList = m_pWrapper->CreateVariable(vid, UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("CurrentPPIDInfo"));
				UbiGEMWrapper::Structure::VariableInfo* dataValue;

				
				dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("EquipmentID"));
				dataValue->SetValue(g_clMesCommunication[m_nUnit].m_sEquipmentID);
				dataMainList->AddChildVariableInfo(dataValue);
				dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("EquipmentName"));
				dataValue->SetValue(g_clMesCommunication[m_nUnit].m_sEquipmentName);
				dataMainList->AddChildVariableInfo(dataValue);
				dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("CurrentPPID"));
				dataValue->SetValue(g_clMesCommunication[m_nUnit].m_sMesPPID);
				dataMainList->AddChildVariableInfo(dataValue);
				dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("CurrentPPIDVersion"));
				dataValue->SetValue(g_clMesCommunication[m_nUnit].m_sMesRecipeRevision);
				dataMainList->AddChildVariableInfo(dataValue);

				m_pWrapper->SetVariable(dataMainList);
			}
			if (vid == _T("10024"))	//LotInfo
			{
				//LotInfo 10024
				//LotInfo-L,9,LotInfo
				//sub 9개
				//vid = 10024
				UbiGEMWrapper::Structure::VariableInfo* dataMainList = m_pWrapper->CreateVariable(vid, UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("LotList"));
				UbiGEMWrapper::Structure::VariableInfo* dataSubList = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("LotInfo"));
				UbiGEMWrapper::Structure::VariableInfo* dataValue;

				//std::vector<RcmdList_T2> resultsT2;
				//std::vector<RcmdList_T2_N> results_T2_n;
				std::vector<RcmdParameter> vSet2;
				std::vector<RcmdParameter> vSet_3;



				std::string carId;
				std::string lotId;
				std::string moduleId;
				std::string pcId;
				std::string pdId;
				//resultsT2.clear();
				//results_T2_n.clear();
				vSet2.clear();
				vSet_3.clear();
				//<Lot Processing State Code Definition>
				//1 = Scan (Lot ID Report ~ PP-SELECT)
				//2 = Ready (PP-Selected Report ~ START)
				//3 = Wait (START ~ Lot Processing Started)
				//4 = Processing (Lot Processing Started ~ Lot Processing Completed)
				//5 = Completed (Lot Processing Completed ~ MGZ Output Completed)
				//eScan = 1, eReady, eWait, eProcessing, eCompleted};



				if (strCEID == LOT_PROCESSING_STARTED_REPORT_10704)
				{
					g_clMesCommunication[m_nUnit].m_dLotProcessingState = eProcessing;
				}
				if (strCEID == LOT_PROCESSING_COMPLETED_REPORT_10710)
				{
					g_clMesCommunication[m_nUnit].m_dLotProcessingState = eCompleted;
				}

				if (strCEID == PP_SELECTED_REPORT_10702)
				{
					g_clMesCommunication[m_nUnit].m_dLotProcessingState = eScan;
					//resultsT2 = g_clReportData.T2_FindChildList(g_clReportData.rPP_Select.parameters);

					vSet2 = g_clReportData.vPPSelect;
				}
				if (strCEID == PP_UPLOAD_COMPLETED_REPORT_10703)
				{
					//resultsT2 = g_clReportData.T2_FindChildList(g_clReportData.rPP_UpLoad_Confirm.parameters);
					vSet2 = g_clReportData.vPPUploadConfirm;
				}
				if (strCEID == LOT_PROCESSING_STARTED_REPORT_10704 || strCEID == LOT_PROCESSING_COMPLETED_REPORT_10710 || strCEID == LOT_APD_REPORT_10711)
				{
					//results_T2_n = g_clReportData.T2N_FindChildList(g_clReportData.rLot_Start.parameters, 14);

					vSet_3 = g_clReportData.vLotStart;
				}

				/*if (resultsT2.size() > 0)
				{
					for (i = 0; i < resultsT2[0].rVec.size(); i++)
					{
						if (resultsT2[0].rVec[i].cpName == "LOTID")
						{
							lotId = resultsT2[0].rVec[i].cepVal;
						}
						if (resultsT2[0].rVec[i].cpName == "CARRIERID")
						{
							carId = resultsT2[0].rVec[i].cepVal;
						}
						if (resultsT2[0].rVec[i].cpName == "PROCID")
						{
							pcId = resultsT2[0].rVec[i].cepVal;
						}
						if (resultsT2[0].rVec[i].cpName == "PRODID")
						{
							pdId = resultsT2[0].rVec[i].cepVal;
						}
					}
				}*/
				/*if (results_T2_n.size() > 0)
				{
				for (i = 0; i < results_T2_n[0].rVec.size(); i++)
				{
				if (results_T2_n[0].rVec[i].cpName == "LOTID")
				{
				lotId = results_T2_n[0].rVec[i].cepVal;
				}
				if (results_T2_n[0].rVec[i].cpName == "PROCID")
				{
				pcId = results_T2_n[0].rVec[i].cepVal;
				}
				if (results_T2_n[0].rVec[i].cpName == "PRODID")
				{
				pdId = results_T2_n[0].rVec[i].cepVal;
				}
				}
				}*/
				if (vSet2.size() > 0)
				{
					for (i = 0; i < vSet2[0].children.size(); i++)
					{
						if (vSet2[0].children[i].name == "LOTID")
						{
							lotId = vSet2[0].children[i].value;
						}
						if (vSet2[0].children[i].name == "CARRIERID")
						{
							carId = vSet2[0].children[i].value;
						}
						if (vSet2[0].children[i].name == "MODULEID")
						{
							moduleId = vSet2[0].children[i].value;
						}
						if (vSet2[0].children[i].name == "PROCID")
						{
							pcId = vSet2[0].children[i].value;
						}
						if (vSet2[0].children[i].name == "PRODID")
						{
							pdId = vSet2[0].children[i].value;
						}
					}
				}
				
				if (vSet_3.size() > 0)
				{
					for (i = 0; i < vSet_3[0].children.size(); i++)
					{
						if (vSet_3[0].children[i].name == "LOTID")
						{
							lotId = vSet_3[0].children[i].value;
						}
						if (vSet_3[0].children[i].name == "PROCID")
						{
							pcId = vSet_3[0].children[i].value;
						}
						if (vSet_3[0].children[i].name == "PRODID")
						{
							pdId = vSet_3[0].children[i].value;
						}
					}
				}
				

				if (strCEID == OBJECT_ID_REPORT_10701) 
				{
					g_clMesCommunication[m_nUnit].m_dLotProcessingState = eScan;	//object id report
					pdId = ModelList.m_szCurrentModel;	//가장 아래에서 받아야 된다.
				}
				if (strCEID == ABORTED_REPORT_10712)	//Aborted Report
				{
					lotId = g_clReportData.strAbortedLot;// "C124C10V0500001";// 입력 받을수 있게 해야된다
					pcId = "CA4TS03051";
					pdId = ModelList.m_szCurrentModel;
				}
				//
				dataMainList->AddChildVariableInfo(dataSubList);

				dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U4, _T("PortID"));
				dataValue->SetValue((uint8_t)1);		//PortID 1로 고정
				dataSubList->AddChildVariableInfo(dataValue);
				//
				//
				dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("LotID"));	//mes id //PP 에서 받은
				dataValue->SetValue(lotId.c_str());		// g_clMesCommunication[m_nUnit].m_sLotID);
				dataSubList->AddChildVariableInfo(dataValue);
				//
				dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("PocketID"));
				dataValue->SetValue("");
				dataSubList->AddChildVariableInfo(dataValue);
				dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("ModuleID"));	//BCR ID
				dataValue->SetValue(g_clTaskWork[m_nUnit].m_szChipID);
				dataSubList->AddChildVariableInfo(dataValue);
				dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("ProcessID"));	//PP 에서 받은
				dataValue->SetValue(pcId.c_str());	// g_clMesCommunication[m_nUnit].m_sProcessID);
				dataSubList->AddChildVariableInfo(dataValue);
				dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("ProductID"));	//PP 에서 받은
				dataValue->SetValue(pdId.c_str());	//ModelList.m_szCurrentModel);	//object만 m_szCurrentModel 설정된걸로
				dataSubList->AddChildVariableInfo(dataValue);
				dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("LotProcessingState"));
				dataValue->SetValue((uint8_t)g_clMesCommunication[m_nUnit].m_dLotProcessingState);
				

				//<Lot Processing State Code Definition>
				//1 = Scan (Lot ID Report ~ PP-SELECT)
				//2 = Ready (PP-Selected Report ~ START)
				//3 = Wait (START ~ Lot Processing Started)
				//4 = Processing (Lot Processing Started ~ Lot Processing Completed)
				//5 = Completed (Lot Processing Completed ~ MGZ Output Completed)
				//
				dataSubList->AddChildVariableInfo(dataValue);
				dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("RecipeID"));	//스펙별 코드 명
				dataValue->SetValue(g_clMesCommunication[m_nUnit].m_sRecipeId);		//LotInfo 보고 10024
				dataSubList->AddChildVariableInfo(dataValue);
				dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("RecipeIDVersion"));	//xx
				dataValue->SetValue("");
				dataSubList->AddChildVariableInfo(dataValue);
				//
				m_pWrapper->SetVariable(dataMainList);



			}
		}

	}
	strCEID.Empty();
	strLog.Empty();
}

// 사용자 정의 GEM Message의 업데이트가 필요할 경우 발생합니다.
void CUbiGem::OnUserGEMMessageUpdateRequest(UbiGEMWrapper::Structure::SECSMessage* pMessage)
{
	CString strLog;

	strLog.AppendFormat(_T("OnUserGEMMessageUpdateRequest: [Stream=%d,Function=%d]"), pMessage->Stream, pMessage->Function);

	UbisamAddLog(strLog);
}

// Trace Data를 발송하기 위해 Variable의 Update가 필요한 경우 발생합니다.
void CUbiGem::OnTraceDataUpdateRequest(UbiGEMWrapper::Structure::List<LPCTSTR>* vids)
{
	CString strLog;
	UbiGEMWrapper::Structure::VariableInfo* variableInfo;

	if (vids == nullptr)
	{
		strLog.AppendFormat(_T("OnTraceDataUpdateRequest: [vids is null]"));
	}
	else
	{
		strLog.AppendFormat(_T("OnTraceDataUpdateRequest: [Count=%d]"), vids->GetCount());
	}

	UbisamAddLog(strLog);

	if (m_pWrapper != nullptr)
	{
		for (int i = 0; i < vids->GetCount(); i++)
		{
			variableInfo = m_pWrapper->GetVariable(vids->At(i));

			// Trace에 등록한 VID와 비교하고, 현재 값을 Set 합니다
			if (_tcscmp(vids->At(i), SAMPLE_VID_ControlState) == 0)
			{
				variableInfo->SetValue(5);
			}

			m_pWrapper->SetVariable(variableInfo);

			m_pWrapper->DeleteVariableInfo(variableInfo);
			variableInfo = nullptr;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
//
//
//
//
//
//
//-------------------------------------------------------------------------------------------------------------------------------------------------

void CUbiGem::InitializeControls()
{
	if (m_pWrapper != nullptr)
	{
		CString strItem;

		m_cboEcv.ResetContent();
		m_cboV.ResetContent();

		// GetAll********* API는 Sample 내의 UI에 Item을 추가하기 위해 사용하는 메소드입니다.
		UbiGEMWrapper::Structure::VariableCollection* pVariables = m_pWrapper->GetAllVariable();

		if (pVariables != nullptr)
		{
			UbiGEMWrapper::Structure::VariableInfo* pVariable;

			for (int i = 0, n = pVariables->Items->GetCount(); i < n; i++)
			{
				pVariable = pVariables->Items->At(i);

				if (pVariable != nullptr)
				{
					strItem.Format(_T("%s : %s"), pVariable->VID, pVariable->Name);

					if (pVariable->VIDType == UbiGEMWrapper::Structure::GEMVariable_ECV)
					{
						m_cboEcv.AddString(strItem);
					}
					else
					{
						m_cboV.AddString(strItem);
					}
				}
			}
			if (m_cboEcv.GetCount() > 0)
			{
				m_cboEcv.SetCurSel(0);
			}
			if (m_cboV.GetCount() > 0)
			{
				m_cboV.SetCurSel(0);
			}
			// GetAllVariable() 로 가져온 데이터는 Driver 의 소멸자에서 자동으로 해제 됩니다.
			pVariables = nullptr;
		}

		m_cboCe.ResetContent();

		// GetAll********* API는 Sample 내의 UI에 Item을 추가하기 위해 사용하는 메소드입니다.

		UbiGEMWrapper::Structure::CollectionEventCollection* pCollectionEvents = m_pWrapper->GetAllCollectionEventInfo();

		if (pCollectionEvents != nullptr)
		{
			UbiGEMWrapper::Structure::CollectionEventInfo* pCollectionEvent;

			for (int i = 0, n = pCollectionEvents->Items->GetCount(); i < n; i++)
			{
				pCollectionEvent = pCollectionEvents->Items->At(i);

				if (pCollectionEvent != nullptr)
				{
					strItem.Format(_T("%s : %s"), pCollectionEvent->CEID, pCollectionEvent->Name);

					m_cboCe.AddString(strItem);
				}
			}

			if (m_cboCe.GetCount() > 0)
			{
				m_cboCe.SetCurSel(0);
			}
			// GetAllCollectionEventInfo() 로 가져온 데이터는 Driver 의 소멸자에서 자동으로 해제 됩니다.
			pCollectionEvents = nullptr;
		}

		m_cboUserMessage.AddString(_T("UserTestMessage"));



		m_cboRcmdView.ResetContent();
		for (int i = 0; i < 14; i++)
		{
			m_cboRcmdView.AddString(RCMD_LIST_NAME[i]);
		}
		m_cboRcmdView.SetCurSel(0);
	}
}

void CUbiGem::MakePPBody(UbiGEMWrapper::Structure::List<unsigned char>* ppBody)
{
	int start_number = 0;
	int end_number = 100;
	size_t count = rand() % 999;

	if (ppBody != nullptr)
	{
		for (int i = 0; i < count; i++)
		{
			ppBody->Add((rand() % (end_number - start_number + 1)) + start_number);
		}
	}
}

void CUbiGem::ProcessProgramParsing(bool withoutValue, UbiGEMWrapper::Structure::FmtPPCollection* fmtPpCollection, std::vector<PP_RECIPE_SPEC> specData)
{
	if (fmtPpCollection != nullptr)
	{

#if 1
		int i = 0;
		int j = 0;
		
		
		if (withoutValue == false)
		{
			//pData->AddFmtPPItem(_T(""), _T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A);
			//fmtPpCollection->MDLN = "";
			//fmtPpCollection->SOFTREV = "";
			return;
		}

		UbiGEMWrapper::Structure::FmtPPCCodeInfo* pData = m_pWrapper->CreateFmtPPCCodeInfo(_T(""));
		fmtPpCollection->AddFmtPPCCodeInfo(pData);
		int totalCnt = specData.size();
		
		if (totalCnt > 0)
		{
			for (i = 0; i < 1; i++)//for (i = 0; i < totalCnt; i++)  1로 고정
			{
				int subCnt = specData[i].parmMap.size();//specData[i].parmName.size();
				for (j = 0; j < subCnt; j++)
				{
					if (specData[i].parmMapChk[specData[i].parmName[j]] == "1")//if (specData[i].parmChecked[j] == "1")
					{
						pData->AddFmtPPItem(
							specData[i].parmName[j].c_str(),
							specData[i].parmMap[specData[i].parmName[j]].c_str(),	//specData[i].parmVal[j].c_str(),
							UbiGEMWrapper::Structure::GEMSECSFormat_A);
					}
				}



			}
		}
#else
		UbiGEMWrapper::Structure::FmtPPCCodeInfo* pCameraIsUse = m_pWrapper->CreateFmtPPCCodeInfo(_T("CAMERA_IS_USE"));
		fmtPpCollection->AddFmtPPCCodeInfo(pCameraIsUse);

		pCameraIsUse->AddFmtPPItem(_T("CAMERA1"), _T("True"), UbiGEMWrapper::Structure::GEMSECSFormat_Boolean);
		pCameraIsUse->AddFmtPPItem(_T("CAMERA2"), _T("True"), UbiGEMWrapper::Structure::GEMSECSFormat_Boolean);
		pCameraIsUse->AddFmtPPItem(_T("CAMERA3"), _T("True"), UbiGEMWrapper::Structure::GEMSECSFormat_Boolean);
		pCameraIsUse->AddFmtPPItem(_T("CAMERA4"), _T("True"), UbiGEMWrapper::Structure::GEMSECSFormat_Boolean);
		pCameraIsUse->AddFmtPPItem(_T("CAMERA5"), _T("True"), UbiGEMWrapper::Structure::GEMSECSFormat_Boolean);

		UbiGEMWrapper::Structure::FmtPPCCodeInfo* pCameraLigthValue = m_pWrapper->CreateFmtPPCCodeInfo(_T("CAMERA_LIGHT_VALUE"));
		fmtPpCollection->AddFmtPPCCodeInfo(pCameraLigthValue);

		pCameraLigthValue->AddFmtPPItem(_T("CAMERA1"), _T("10"), UbiGEMWrapper::Structure::GEMSECSFormat_U1);
		pCameraLigthValue->AddFmtPPItem(_T("CAMERA2"), _T("20"), UbiGEMWrapper::Structure::GEMSECSFormat_U2);
		pCameraLigthValue->AddFmtPPItem(_T("CAMERA3"), _T("30"), UbiGEMWrapper::Structure::GEMSECSFormat_U4);
		pCameraLigthValue->AddFmtPPItem(_T("CAMERA4"), _T("40"), UbiGEMWrapper::Structure::GEMSECSFormat_U8);
		pCameraLigthValue->AddFmtPPItem(_T("CAMERA5"), _T("0"), UbiGEMWrapper::Structure::GEMSECSFormat_I1);

		UbiGEMWrapper::Structure::FmtPPCCodeInfo* pBeamProfiler = m_pWrapper->CreateFmtPPCCodeInfo(_T("BEAM_PROFILER"));
		fmtPpCollection->AddFmtPPCCodeInfo(pBeamProfiler);

		pBeamProfiler->AddFmtPPItem(_T("CNTPERMM"), _T("100.0000000000"), UbiGEMWrapper::Structure::GEMSECSFormat_F4);
		pBeamProfiler->AddFmtPPItem(_T("SPDRATIO"), _T("0.0000000000"), UbiGEMWrapper::Structure::GEMSECSFormat_F8);
		pBeamProfiler->AddFmtPPItem(_T("ACCDCC"), _T("0"), UbiGEMWrapper::Structure::GEMSECSFormat_I2);
		pBeamProfiler->AddFmtPPItem(_T("LENGTH"), _T("500"), UbiGEMWrapper::Structure::GEMSECSFormat_I4);

		UbiGEMWrapper::Structure::FmtPPCCodeInfo* pData = m_pWrapper->CreateFmtPPCCodeInfo(_T("DATA"));
		fmtPpCollection->AddFmtPPCCodeInfo(pData);

		pData->AddFmtPPItem(_T("GLOBAL_SIZE"), _T("100.2500, 50.3500"), UbiGEMWrapper::Structure::GEMSECSFormat_A);
		pData->AddFmtPPItem(_T("MARK_SIZE"), _T("1.0000, 1.0000"), UbiGEMWrapper::Structure::GEMSECSFormat_A);
		pData->AddFmtPPItem(_T("MARK_DISTANCE"), _T("77"), UbiGEMWrapper::Structure::GEMSECSFormat_I8);

#endif
	}
}
bool CUbiGem::bConnected()
{
	return m_pWrapper->GetConnected();
}
void CUbiGem::UpdateDialogTitle()
{
	CString strControlState = _T("");
	CString strTitle = _T("");
	strTitle = _T("UbiGEM) UGC FILE PATH : ");//strTitle = _T("UbiGEM Sample : ");

	if (g_pCarAABonderDlg->m_clMainDlg.m_hWnd == NULL)
	{
		return;
	}

	if (m_pWrapper != nullptr)
	{
		
		if (m_pWrapper->GetConnected() == true)		//GEM Driver의 통신 연결 상태를 가져온다.
		{
			UbiGemInit = false;
			
			g_clMesCommunication[m_nUnit].m_dEqupControlState[0] = g_clMesCommunication[m_nUnit].m_dEqupControlState[1];
			//
			switch (m_pWrapper->GetControlState())
			{
			case UbiGEMWrapper::Structure::GEMControlState_OnlineRemote:		//5
				strControlState.Append(_T("Connected / OnlineRemote"));
				
				g_clMesCommunication[m_nUnit].m_dEqupControlState[1] = eOnlineRemote;

				//m_pWrapper->RequestOnlineRemote();
				break;
			case UbiGEMWrapper::Structure::GEMControlState_OnlineLocal:			//4
				strControlState.Append(_T("Connected / OnlineLocal"));
				g_clMesCommunication[m_nUnit].m_dEqupControlState[1] = eOnlineLocal;
				break;
			case UbiGEMWrapper::Structure::GEMControlState_HostOffline:			//3
				strControlState.Append(_T("Connected / HostOffline"));
				g_clMesCommunication[m_nUnit].m_dEqupControlState[1] = eHostOffline;
				break;
			case UbiGEMWrapper::Structure::GEMControlState_AttemptOnline:		//2
				strControlState.Append(_T("Connected / AttemptOnline"));
				g_clMesCommunication[m_nUnit].m_dEqupControlState[1] = eAttemprtOnline;
				break;
			default:
				strControlState.Append(_T("Connected / EquipmentOffline"));
				g_clMesCommunication[m_nUnit].m_dEqupControlState[1] = eEquipmentOffline;
				break;
			}
			g_pCarAABonderDlg->m_clMainDlg.setControlState(m_pWrapper->GetControlState());
			g_pCarAABonderDlg->m_clMainDlg.setCommunicationState(m_pWrapper->GetCommunicationState());
		}
		else
		{
			
			g_clMesCommunication[m_nUnit].m_dEqupControlState[1] = eEquipmentOffline;
			strControlState.Append(_T("Disconnected"));

			g_pCarAABonderDlg->m_clMainDlg.setControlState(-1);
			g_pCarAABonderDlg->m_clMainDlg.setCommunicationState(3);

			UbiGemInit = true;
		}
		
		
		
	}

	strTitle.AppendFormat(_T(" - %s"), m_strUgcFileName);		//UGC FILE PATH


	SetWindowText(strTitle);// strTitle);
	m_clColorStaticControlState.SetWindowText(strControlState);
}

CString CUbiGem::SECSFormatAsString(UbiGEMWrapper::Structure::GEMSECSFormat format)
{
	CString result;

	result.Append(UbiGEMWrapper::SECSItemFormatAsString(format));

	return result;
}


CString CUbiGem::SECSValueAsString(UbiGEMWrapper::Structure::GEMSECSFormat format, UbiGEMWrapper::Structure::SECSValue* value)
{
	CString result;

	if (value != nullptr)
	{
		switch (format)
		{
		case UbiGEMWrapper::Structure::GEMSECSFormat_A:
		case UbiGEMWrapper::Structure::GEMSECSFormat_J:
			if (value->Length > 0)
			{
				result.Format(_T("%s"), value->GetValueString());
			}
			break;
		case UbiGEMWrapper::Structure::GEMSECSFormat_B:
			if (value->Length == 1)
			{
				result.Format(_T("%d"), value->GetValueB());
			}
			else if (value->Length > 1)
			{
				uint8_t* arr = value->GetValueBArray();

				for (int i = 0; i < value->Length; i++)
				{
					result.AppendFormat(_T("%d "), arr[i]);
				}
			}
			break;
		case UbiGEMWrapper::Structure::GEMSECSFormat_Boolean:
			if (value->Length == 1)
			{
				result.Format(_T("%s"), value->GetValueBool() == true ? _T("T") : _T("F"));
			}
			else if (value->Length > 1)
			{
				bool* arr = value->GetValueBoolArray();

				for (int i = 0; i < value->Length; i++)
				{
					result.AppendFormat(_T("%s "), arr[i] == true ? _T("T") : _T("F"));
				}
			}
			break;
		case UbiGEMWrapper::Structure::GEMSECSFormat_F4:
			if (value->Length == 1)
			{
				result.Format(_T("%f"), value->GetValueF4());
			}
			else if (value->Length > 1)
			{
				float* arr = value->GetValueF4Array();

				for (int i = 0; i < value->Length; i++)
				{
					result.AppendFormat(_T("%s "), arr[i]);
				}
			}
			break;
		case UbiGEMWrapper::Structure::GEMSECSFormat_F8:
			if (value->Length == 1)
			{
				result.Format(_T("%f"), value->GetValueF8());
			}
			else if (value->Length > 1)
			{
				double* arr = value->GetValueF8Array();

				for (int i = 0; i < value->Length; i++)
				{
					result.AppendFormat(_T("%f "), arr[i]);
				}
			}

			break;
		case UbiGEMWrapper::Structure::GEMSECSFormat_I1:
			if (value->Length == 1)
			{
				result.Format(_T("%d"), value->GetValueI1());
			}
			else if (value->Length > 1)
			{
				int8_t* arr = value->GetValueI1Array();

				for (int i = 0; i < value->Length; i++)
				{
					result.AppendFormat(_T("%d "), arr[i]);
				}
			}
			break;
		case UbiGEMWrapper::Structure::GEMSECSFormat_I2:
			if (value->Length == 1)
			{
				result.Format(_T("%d"), value->GetValueI2());
			}
			else if (value->Length > 1)
			{
				int16_t* arr = value->GetValueI2Array();

				for (int i = 0; i < value->Length; i++)
				{
					result.AppendFormat(_T("%d "), arr[i]);
				}
			}
			break;
		case UbiGEMWrapper::Structure::GEMSECSFormat_I4:
			if (value->Length == 1)
			{
				result.Format(_T("%d"), value->GetValueI4());
			}
			else if (value->Length > 1)
			{
				int32_t* arr = value->GetValueI4Array();

				for (int i = 0; i < value->Length; i++)
				{
					result.AppendFormat(_T("%d "), arr[i]);
				}
			}

			break;
		case UbiGEMWrapper::Structure::GEMSECSFormat_I8:
			if (value->Length == 1)
			{
				result.Format(_T("%lld"), value->GetValueI8());
			}
			else if (value->Length > 1)
			{
				int64_t* arr = value->GetValueI8Array();

				for (int i = 0; i < value->Length; i++)
				{
					result.AppendFormat(_T("%lld "), arr[i]);
				}
			}

			break;
		case UbiGEMWrapper::Structure::GEMSECSFormat_U1:
			if (value->Length == 1)
			{
				result.Format(_T("%u"), value->GetValueU1());
			}
			else if (value->Length > 1)
			{
				uint8_t* arr = value->GetValueU1Array();

				for (int i = 0; i < value->Length; i++)
				{
					result.AppendFormat(_T("%u "), arr[i]);
				}
			}

			break;
		case UbiGEMWrapper::Structure::GEMSECSFormat_U2:
			if (value->Length == 1)
			{
				result.Format(_T("%u"), value->GetValueU2());
			}
			else if (value->Length > 1)
			{
				uint16_t* arr = value->GetValueU2Array();

				for (int i = 0; i < value->Length; i++)
				{
					result.AppendFormat(_T("%u "), arr[i]);
				}
			}
			break;
		case UbiGEMWrapper::Structure::GEMSECSFormat_U4:
			if (value->Length == 1)
			{
				result.Format(_T("%u"), value->GetValueU4());
			}
			else if (value->Length > 1)
			{
				uint32_t* arr = value->GetValueU4Array();

				for (int i = 0; i < value->Length; i++)
				{
					result.AppendFormat(_T("%u "), arr[i]);
				}
			}
			break;
		case UbiGEMWrapper::Structure::GEMSECSFormat_U8:
			if (value->Length == 1)
			{
				result.Format(_T("%llu"), value->GetValueU8());
			}
			else if (value->Length > 1)
			{
				uint64_t* arr = value->GetValueU8Array();

				for (int i = 0; i < value->Length; i++)
				{
					result.AppendFormat(_T("%llu "), arr[i]);
				}
			}
			break;
		case UbiGEMWrapper::Structure::GEMSECSFormat_L:
		case UbiGEMWrapper::Structure::GEMSECSFormat_X:
		case UbiGEMWrapper::Structure::GEMSECSFormat_None:
		default:
			break;
		}
	}

	return result;
}
CString CUbiGem::ConvertDriverResult(UbiGEMWrapper::Structure::GEMResult gemResult)
{
	CString strResult = _T("");

	switch (gemResult)
	{
	case UbiGEMWrapper::Structure::GEMResult_Ok:
		strResult = _T("OK");
		break;
	case UbiGEMWrapper::Structure::GEMResult_Unknown:
		strResult = _T("Unknown");
		break;
	case UbiGEMWrapper::Structure::GEMResult_NotExistDriverName:
		strResult = _T("Not Exist Driver Name");
		break;
	case UbiGEMWrapper::Structure::GEMResult_NotExistFile:
		strResult = _T("Not Exist File");
		break;
	case UbiGEMWrapper::Structure::GEMResult_FileLoadFailed:
		strResult = _T("File Load Failed");
		break;
	case UbiGEMWrapper::Structure::GEMResult_FileSaveFailed:
		strResult = _T("File Save Failed");
		break;
	case UbiGEMWrapper::Structure::GEMResult_InvalidConfiguration:
		strResult = _T("Invalid Configuration");
		break;
	case UbiGEMWrapper::Structure::GEMResult_AlreadyConnected:
		strResult = _T("Already Connected");
		break;
	case UbiGEMWrapper::Structure::GEMResult_SocketException:
		strResult = _T("Socket Exception");
		break;
	case UbiGEMWrapper::Structure::GEMResult_LicenseVerificationFailed:
		strResult = _T("License Verification Failed");
		break;
	case UbiGEMWrapper::Structure::GEMResult_Disconnected:
		strResult = _T("Disconnected");
		break;
	case UbiGEMWrapper::Structure::GEMResult_ControlStateIsOffline:
		strResult = _T("Control State Is Offline");
		break;
	case UbiGEMWrapper::Structure::GEMResult_SameState:
		strResult = _T("Same State");
		break;
	case UbiGEMWrapper::Structure::GEMResult_Undefined:
		strResult = _T("Undefined");
		break;
	case UbiGEMWrapper::Structure::GEMResult_Disabled:
		strResult = _T("Disabled");
		break;
	case UbiGEMWrapper::Structure::GEMResult_HSMSDriverError:
		strResult = _T("HSMS Driver Error");
		break;
	case UbiGEMWrapper::Structure::GEMResult_HSMSDriverDisconnected:
		strResult = _T("HSMS Driver Disconnected");
		break;
	case UbiGEMWrapper::Structure::GEMResult_NotCommunicating:
		strResult = _T("Not Communicating");
		break;
	case UbiGEMWrapper::Structure::GEMResult_MessageMakeFailed:
		strResult = _T("Message Make Failed");
		break;
	case UbiGEMWrapper::Structure::GEMResult_Exception:
		strResult = _T("Exception");
		break;
	case UbiGEMWrapper::Structure::GEMResult_Mismatch:
		strResult = _T("Mismatch");
		break;
	case UbiGEMWrapper::Structure::GEMResult_HostDenied:
		strResult = _T("Host Denied");
		break;
	case UbiGEMWrapper::Structure::GEMResult_InvalidFormat:
		strResult = _T("Invalid Format");
		break;
	default:
		strResult = _T("Undefined");
		break;
	}

	return strResult;
}

void CUbiGem::UbisamAddLog(CString strLog)
{
	CString strData;
	CTime cTime = CTime::GetCurrentTime();

	strData.AppendFormat(_T("[%04d-%02d-%02d "),
		cTime.GetYear(),
		cTime.GetMonth(),
		cTime.GetDay());

	strData.AppendFormat(_T("%02d:%02d:%02d]"),
		cTime.GetHour(),
		cTime.GetMinute(),
		cTime.GetSecond());

	strData.AppendFormat(_T(" %s\r\n"), strLog);

	if (m_edtLog.m_hWnd != nullptr)
	{

		//const int MAX_LOG_SIZE = 100;  // 최대 로그 길이 (예시)
		//if (m_edtLog.GetWindowTextLength() > MAX_LOG_SIZE) {
		//	CString strLog;
		//	m_edtLog.GetWindowText(strLog);

		//	// 앞부분 일부 삭제
		//	strLog.Delete(0, strLog.GetLength() / 2);
		//	m_edtLog.SetWindowText(strLog);  // 텍스트 재설정
		//}

		m_edtLog.SetSel(-2, -1);
		m_edtLog.ReplaceSel(strData);

		//AddLog(strLog, 0, 0);
	}
}

void CUbiGem::UbisamAddLog(CString strLog, UbiGEMWrapper::Structure::GEMResult gemResult)
{
	CString strData;
	CTime cTime = CTime::GetCurrentTime();

	strData.AppendFormat(_T("[%04d-%02d-%02d "),
		cTime.GetYear(),
		cTime.GetMonth(),
		cTime.GetDay());

	strData.AppendFormat(_T("%02d:%02d:%02d]"),
		cTime.GetHour(),
		cTime.GetMinute(),
		cTime.GetSecond());

	strData.AppendFormat(_T(" [Result=%s] : %s\r\n"), ConvertDriverResult(gemResult), strLog);

	if (m_edtLog.m_hWnd != nullptr)
	{
		m_edtLog.SetSel(-2, -1);
		m_edtLog.ReplaceSel(strData); 

		strData.Format(_T("%s %s") , ConvertDriverResult(gemResult), strLog);

		//AddLog(strData, 0, 0);
	}
	strData.Empty();

}

//-------------------------------------------------------------------------------------------------------------------------------------------------
//
//
// UGC FILE OPEN BUTTON
//
//
//-------------------------------------------------------------------------------------------------------------------------------------------------
int CUbiGem::UbisamUgcLoad()
{
	char szTemp[MAX_PATH];
	CString uiFile = _T("");
	uiFile.Format(_T("%s\\UIConfig\\UIConfig.ini"), BASE_UBISAM_PATH);
	DWORD result = GetPrivateProfileString(_T("UIConfig"), _T("UbiSamSetFile"), _T("Default.ini"), szTemp, MAX_PATH, uiFile);
	uiFile.Empty();

	TCHAR szLog[SIZE_OF_1K];
	

	if (result > 0)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[UGC] iniFile: %s"), szTemp); 
		AddLog(szLog, 0, m_nUnit);
		m_strUgcFileName.Format(_T("%s\\%s"), BASE_UBISAM_PATH, szTemp);
		OnMnuInitilaize();
		OnMnuStart();
	}
	else
	{
		
		_stprintf_s(szLog, SIZE_OF_1K, _T("[UGC] File Load Fail"));
		AddLog(szLog, 0, m_nUnit);
	}

	return 1;
}
void CUbiGem::OnBnClickedButtonUgcOpen()
{
	CString filter = _T("Sample(*.ugc)|*.ugc||");
	CFileDialog dlg(TRUE, _T(""), _T(""), OFN_HIDEREADONLY, filter);
	//dlg.m_ofn.lpstrInitialDir = "C:\Users\ubisam007\Documents\UbiSam\UbiGEM\Samples";

	if (dlg.DoModal() == IDOK)
	{
		CString strTitle;
		m_strUgcFileName = dlg.GetPathName();

		OnMnuInitilaize();
	}

	UpdateDialogTitle();


	
}
void CUbiGem::OnMnuInitilaize()
{
	CString strLog;
	CString strError;

	UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->Initialize(m_strUgcFileName);

	if (gemResult == UbiGEMWrapper::Structure::GEMResult_Ok)
	{
		InitializeControls();
		strLog.Format(_T("Driver Initilaize"));
	}
	else
	{
		strError = m_pWrapper->GetInitializeError();
		strLog.Format(_T("Driver Initialize Fail. [Reason=%s]"), strError);
	}

	UbisamAddLog(strLog, gemResult);
}
void CUbiGem::OnMnuStart()
{
	if (m_pWrapper != nullptr)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->Start();

		UbisamAddLog(_T("Driver Start"), gemResult);

		m_pWrapper->SetVariable(_T("10012"), 9);		//9 = Manual Mode EquipmentOperationMode
	}
}

void CUbiGem::OnMnuStop()
{
	if (m_pWrapper != nullptr)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->Stop();

		UbisamAddLog(_T("Driver Stop"), gemResult);
	}
}
void CUbiGem::OnBnClickedButtonUbigemClose()
{
	this->ShowWindow(SW_HIDE);
}


CString CUbiGem::GetGUIString(CComboBox* pTarget)
{
	CString strInputValue;
	CString strSelectedItem;

	pTarget->GetWindowText(strSelectedItem);

	if (strSelectedItem.GetAllocLength() > 0)
	{
		CString strToken;
		int nTokenPos = 0;

		strInputValue = strSelectedItem.Tokenize(_T(":"), nTokenPos).Trim();
	}
	else
	{
		strInputValue = _T("");
	}

	return strInputValue;
}

CString CUbiGem::GetGUIString(CEdit* pTarget)
{
	CString strSelectedItem;
	pTarget->GetWindowText(strSelectedItem);
	return strSelectedItem;
}


CString CUbiGem::CheckValidationParameterItem(UbiGEMWrapper::Structure::EnhancedCommandParameterItem* enhancedCommandParameterItem, UbiGEMWrapper::Structure::RemoteCommandParameterResult* paramResult)
{
	CString result;
	UbiGEMWrapper::Structure::EnhancedCommandParameterItem* item;

	if (enhancedCommandParameterItem->Format == UbiGEMWrapper::Structure::GEMSECSFormat_L && enhancedCommandParameterItem->ChildParameterItems != nullptr)
	{
		for (int i = 0; i < enhancedCommandParameterItem->ChildParameterItems->GetCount(); i++)
		{
			item = enhancedCommandParameterItem->ChildParameterItems->At(i);

			result.AppendFormat(_T("\r\n:   [CPNAME=%s,Format=%s,CEPVAL=%s]"), item->Name, SECSFormatAsString(item->Format), item->Value);

			if (paramResult != nullptr)
			{
				paramResult->AddChildParameterResult(item->Name, m_iAck);
			}
			result.Append(CheckValidationParameterItem(item, paramResult));
		}
	}

	return result;
}


void CUbiGem::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // 그리기 메시지에 대해서는 __super::OnPaint()을(를) 호출하지 마십시오.
}


HCURSOR CUbiGem::OnQueryDragIcon()
{
	return __super::OnQueryDragIcon();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
//
//
// INITILAIZE BUTTON
//
//
//-------------------------------------------------------------------------------------------------------------------------------------------------

void CUbiGem::OnBnClickedButtonUbigemInit()
{
	OnMnuInitilaize();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
//
//
// START BUTTON
//
//
//-------------------------------------------------------------------------------------------------------------------------------------------------

void CUbiGem::OnBnClickedButtonUbigemStart()
{
	OnMnuStart();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
//
//
//STOP BUTTON
//
//
//-------------------------------------------------------------------------------------------------------------------------------------------------

void CUbiGem::OnBnClickedButtonUbigemStop()
{
	OnMnuStop();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
//
//
//Process State Change BUTTON
//
//
//-------------------------------------------------------------------------------------------------------------------------------------------------

void CUbiGem::OnBnClickedButtonUbigemProcessStateChange()
{
	CString str;
	CString strLog;
	m_edtProcessState.GetWindowText(str);
	int istr;
	istr = _ttoi(str);

	UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportEquipmentProcessingState(istr);

	strLog.Format(_T("ReportEquipmentProcessingState : [State=%d]"), istr);
	UbisamAddLog(strLog, gemResult);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------
//
//
// Alarm Set, Clear BUTTON
//
//
//-------------------------------------------------------------------------------------------------------------------------------------------------
void CUbiGem::AlarmSendFn(int nAlarmID)
{
	if (g_clMesCommunication[m_nUnit].m_dEqupControlState[1] == eEquipmentOffline)
	{
		return;
	}
	int i = 0;
	CString strLog;

	bool bHighAlarm = false;
	g_clMesCommunication[m_nUnit].m_uAlarmList.clear();
	g_clMesCommunication[m_nUnit].m_uAlarmList.push_back(nAlarmID);
	for (int i = 0; i < g_clMesCommunication[m_nUnit].m_uAlarmList.size(); i++)
	{
		strLog.Format(_T("AlarmSet : [ALID=%lld]"), g_clMesCommunication[m_nUnit].m_uAlarmList[i]);
		if (g_clMesCommunication[m_nUnit].m_uAlarmList[i] == 1008 ||
			g_clMesCommunication[m_nUnit].m_uAlarmList[i] == 1046 ||
			g_clMesCommunication[m_nUnit].m_uAlarmList[i] == 1059 ||
			g_clMesCommunication[m_nUnit].m_uAlarmList[i] == 1080)
		{
			bHighAlarm = true;
		}
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportAlarmSet((uint32_t)g_clMesCommunication[m_nUnit].m_uAlarmList[i]);
		UbisamAddLog(strLog, gemResult);
	}


	Sleep(300);
	if (bHighAlarm)
	{
		g_clMesCommunication[m_nUnit].m_dProcessState[0] = g_clMesCommunication[m_nUnit].m_dProcessState[1];
		g_clMesCommunication[m_nUnit].m_dProcessState[1] = ePAUSE;

		/////g_clMesCommunication[m_nUnit].m_uAlarmList.clear();

		g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(PROCESS_STATE_CHANGED_REPORT_10401, "");//SEND S6F11
	}
}
void CUbiGem::AlarmClearSendFn()
{
	int i = 0;
	CString strLog;
	for (int i = 0; i < g_clMesCommunication[m_nUnit].m_uAlarmList.size(); i++)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportAlarmClear(g_clMesCommunication[m_nUnit].m_uAlarmList[i]);

		strLog.Format(_T("AlarmClear : [ALID=%d]"), g_clMesCommunication[m_nUnit].m_uAlarmList[i]);
		UbisamAddLog(strLog, gemResult);
	}

	g_clMesCommunication[m_nUnit].m_uAlarmList.clear();
}
//S9F13(Conversation Timeout)를 송신합니다.
//CtTimeout
void CUbiGem::cTTimeOutSendFn(LPCTSTR strMexp, LPCTSTR strEdId)	//SxFy , 데이터의 ID
{
	int i = 0;
	CString strLog;
	UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportConversationTimeout(strMexp, strEdId);

	strLog.Format(_T("ReportConversationTimeout : [%s,%s]"), strMexp, strEdId);
	UbisamAddLog(strLog, gemResult);
}
void CUbiGem::OnBnClickedButtonUbigemAlarmSet()
{
	CString str;
	CString strLog;
	m_edtAlarmId.GetWindowText(str);
	int64_t alarmID = _ttoi64(str);
#if 1
	m_setAlarmList.clear();
	m_setAlarmList.push_back(alarmID);
	UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportAlarmSet(alarmID);
	//UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportAlarmSet(alarmID, 1001,"alarm test");

	strLog.Format(_T("AlarmSet : [ALID=%lld]"), alarmID);
	UbisamAddLog(strLog, gemResult);
#else

	std::vector<int64_t>::iterator it = std::find(m_setAlarmList.begin(), m_setAlarmList.end(), alarmID);

	if (it == m_setAlarmList.end())
	{
		m_setAlarmList.push_back(alarmID);

		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportAlarmSet(alarmID);

		strLog.Format(_T("AlarmSet : [ALID=%lld]"), alarmID);
		UbisamAddLog(strLog, gemResult);
	}
#endif
}


void CUbiGem::OnBnClickedButtonUbigemAlarmClear()
{
	CString str;
	CString strLog;
	m_edtAlarmId.GetWindowText(str);
	int64_t alarmID = _ttoi64(str);

	std::vector<int64_t>::iterator it = std::find(m_setAlarmList.begin(), m_setAlarmList.end(), alarmID);

	if (it != m_setAlarmList.end())
	{
		m_setAlarmList.erase(it);
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportAlarmClear(alarmID);

		strLog.Format(_T("AlarmClear : [ALID=%lld]"), alarmID);
		UbisamAddLog(strLog, gemResult);
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------
//
//
// ECV COMBO BOX SEL CHANGE EVENT
//
//
//-------------------------------------------------------------------------------------------------------------------------------------------------


void CUbiGem::OnCbnSelchangeCboEc()
{
	if (m_pWrapper != nullptr)
	{
		CString str;
		CString strEcid = GetGUIString(&m_cboEcv);

		UbiGEMWrapper::Structure::VariableInfo *pVariableInfo = m_pWrapper->GetVariable(strEcid);

		if (pVariableInfo != nullptr)
		{
			switch (pVariableInfo->Value->Format)
			{
			case UbiGEMWrapper::Structure::GEMSECSFormat_Boolean:
				if (pVariableInfo->Value->GetValueBool() == true)
				{
					str.Format(_T("True"));
				}
				else
				{
					str.Format(_T("False"));
				}
				m_edtECV.SetWindowText(str);
				break;
			case UbiGEMWrapper::Structure::GEMSECSFormat_A:
				str.Format(_T("%s"), pVariableInfo->Value->GetValueString());
				m_edtECV.SetWindowText(str);
				break;
			case UbiGEMWrapper::Structure::GEMSECSFormat_I1:
				str.Format(_T("%d"), pVariableInfo->Value->GetValueI1());
				m_edtECV.SetWindowText(str);
				break;
			case UbiGEMWrapper::Structure::GEMSECSFormat_I2:
				str.Format(_T("%d"), pVariableInfo->Value->GetValueI2());
				m_edtECV.SetWindowText(str);
				break;
			case UbiGEMWrapper::Structure::GEMSECSFormat_I4:
				str.Format(_T("%d"), pVariableInfo->Value->GetValueI4());
				m_edtECV.SetWindowText(str);
				break;
			case UbiGEMWrapper::Structure::GEMSECSFormat_I8:
				str.Format(_T("%lld"), pVariableInfo->Value->GetValueI8());
				m_edtECV.SetWindowText(str);
				break;
			case UbiGEMWrapper::Structure::GEMSECSFormat_U1:
				str.Format(_T("%u"), pVariableInfo->Value->GetValueU1());
				m_edtECV.SetWindowText(str);
				break;
			case UbiGEMWrapper::Structure::GEMSECSFormat_U2:
				str.Format(_T("%u"), pVariableInfo->Value->GetValueU2());
				m_edtECV.SetWindowText(str);
				break;
			case UbiGEMWrapper::Structure::GEMSECSFormat_U4:
				str.Format(_T("%u"), pVariableInfo->Value->GetValueU4());
				m_edtECV.SetWindowText(str);
				break;
			case UbiGEMWrapper::Structure::GEMSECSFormat_U8:
				str.Format(_T("%llu"), pVariableInfo->Value->GetValueU8());
				m_edtECV.SetWindowText(str);
				break;
			case UbiGEMWrapper::Structure::GEMSECSFormat_X:
				break;
			default:
				break;
			}

			m_pWrapper->DeleteVariableInfo(pVariableInfo);
			pVariableInfo = nullptr;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
//
//
// EC SET BUTTON
//
//
//-------------------------------------------------------------------------------------------------------------------------------------------------


void CUbiGem::OnBnClickedButtonUbigemEcSet()
{
	if (m_pWrapper != nullptr)
	{
		CString strEcid = GetGUIString(&m_cboEcv);
		CString strEcv = GetGUIString(&m_edtECV);
		CString strLog;

		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->SetEquipmentConstant(strEcid, strEcv);

		strLog.Format(_T("Set EquipmentConstant : [ECID=%s,ECV=%s]"), strEcid, strEcv);

		UbisamAddLog(strLog, gemResult);
	}
}


//-------------------------------------------------------------------------------------------------------------------------------------------------
//
//
// V SET BUTTON
//
//
//-------------------------------------------------------------------------------------------------------------------------------------------------

void CUbiGem::OnBnClickedButtonUbigemVSet()
{
	CString strLog;
	CString strVid = GetGUIString(&m_cboV);
	CString strValue = GetGUIString(&m_edtV);
	UbiGEMWrapper::Structure::GEMResult gemResult;

	if (m_pWrapper != nullptr)
	{
		gemResult = m_pWrapper->SetVariable(strVid, strValue);

		strLog.Format(_T("Set Variable : [VID=%s,SV=%s])"), strVid, strValue);

		UbisamAddLog(strLog, gemResult);
	}
}



//-------------------------------------------------------------------------------------------------------------------------------------------------
//
//
// USER MESSAGE SEND BUTTON
//
//
//-------------------------------------------------------------------------------------------------------------------------------------------------

void CUbiGem::OnBnClickedButtonUbigemUserMessageSend()
{
	CString strBlank = _T("");
	CString strName;

	UbiGEMWrapper::Structure::SECSMessage* pMessage = m_pWrapper->GetUserMessage(99, 1, true);

	if (m_pWrapper != nullptr && pMessage != nullptr)
	{
		pMessage->Body->InitializeItems();

		// 아래 형식의 User Defined Message를 송신하고자 할 경우
		// <L, 2
		//     <B, 1 '2'>
		//     <A, 2 'OK'>
		// >
		pMessage->Body->AddListItem(_T(""), 2);
		pMessage->Body->AddSECSItem(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_B, 1);
		pMessage->Body->AddSECSItem(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("OK"));

		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->SendSECSMessage(pMessage);

		UbisamAddLog(_T("SendUserMessage"), gemResult);

		m_pWrapper->DeleteSECSMessage(pMessage);
		pMessage = nullptr;
	}
	else
	{
		UbisamAddLog(_T("SendUserMessage failed. [Reason=Not found]"));
	}
}


//-------------------------------------------------------------------------------------------------------------------------------------------------
//
//
// CE Report CE #1 BUTTON
//
//
//-------------------------------------------------------------------------------------------------------------------------------------------------
void CUbiGem::ReportFn(CString strCENumber, CString param)
{
	int i = 0; 
	int j = 0;
	//strSendCeId = strCENumber;
	strSendCeId.Format(_T("%s"), strCENumber);
	if (strCENumber == OFFLINE_CHANGED_REPORT_10102)	// _T("10102"))	//Offline Changed Report
	{
		//여긴만 보내면 HOST에서 반응 X
		//10005	10005	PreviousControlState U1
		//10004	10004	CurrentControlState U1
		//10006	10006	ControlStateChangeReasonCode A
		//10007	10007	ControlStateChangeReasonText A
		//10010	10010	ControlStateChangeOrder U1

		
		UbiGEMWrapper::Structure::VariableInfo* dataValue;
		
		//<Control State Code Definition>
		//1 = Equipment Offline
		//2 = Attempt Online
		//3 = Host Offline
		//4 = Online Local
		//5 = Online Remote
		

		dataValue = m_pWrapper->CreateVariable(_T("10005"), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("PreviousControlState"));
		dataValue->SetValue((uint8_t)g_clMesCommunication[m_nUnit].m_dEqupControlState[0]);
		m_pWrapper->SetVariable(dataValue);

		dataValue = m_pWrapper->CreateVariable(_T("10004"), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("CurrentControlState"));
		dataValue->SetValue((uint8_t)g_clMesCommunication[m_nUnit].m_dEqupControlState[1]);
		m_pWrapper->SetVariable(dataValue);

		m_pWrapper->SetVariable(_T("10006"), g_clReportData.rCtrlState_Chg_Req.Change_Code);	//ControlStateChangeReasonCode
		m_pWrapper->SetVariable(_T("10007"), g_clReportData.rCtrlState_Chg_Req.Change_Text);	//ControlStateChangeReasonText
		m_pWrapper->SetVariable(_T("10010"), g_clMesCommunication[m_nUnit].m_dControlStateChangeOrder);		//ControlStateChangeOrder, by Host = 1, Op = 2, Equip, 3 = auto
		////ControlStateChangeOrder, 
		//by Host = 1, Op = 2, Equip, 3 = auto

		m_pWrapper->SetVariable(dataValue);

		
		
		//1 = by Host
		//2 = by Operator
		//3 = by Equipment automatically

	}
	else if (strCENumber == _T("10104"))//Online Remote Changed Report  xx
	{
		/*
		10005	10005	PreviousControlState
		10004	10004	CurrentControlState
		10010	10010	ControlStateChangeOrder

		*/
		//10104만 보내면 반응없고, s1f1 AreYouThere을 먼저 보내야한다.

		m_pWrapper->SetVariable(_T("10005"), g_clMesCommunication[m_nUnit].m_dEqupControlState[0]);
		m_pWrapper->SetVariable(_T("10004"), g_clMesCommunication[m_nUnit].m_dEqupControlState[1]);
		m_pWrapper->SetVariable(_T("10010"), g_clMesCommunication[m_nUnit].m_dControlStateChangeOrder);// 2);	//ControlStateChangeOrder
	}
	else if (strCENumber == _T("10201"))//Equipment Constant Changed Report
	{
		/*
		10020	10020	ChangedECList
		10021	10021	ECChangeOrderType
		*/
		//L->L2[U1 ECID, Any ECV]

		UbiGEMWrapper::Structure::VariableInfo* dataValue;

		UbiGEMWrapper::Structure::VariableInfo* dataMainList = m_pWrapper->CreateVariable(_T("10020"), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("ChangedECList"));
		UbiGEMWrapper::Structure::VariableInfo* dataSubList1 = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("ChangedECInfo"));
		UbiGEMWrapper::Structure::VariableInfo* dataSubList2 = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("ChangedECInfo"));



		dataMainList->AddChildVariableInfo(dataSubList1);
		dataMainList->AddChildVariableInfo(dataSubList2);
		
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("ECID"));
		dataValue->SetValue((uint8_t)107);//TimeFormat
		dataSubList2->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("ECV"));
		dataValue->SetValue((uint8_t)0);
		dataSubList2->AddChildVariableInfo(dataValue);

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("ECID"));
		dataValue->SetValue((uint8_t)108);	//DefaultOnlineSubState
		dataSubList1->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("ECV"));
		dataValue->SetValue((uint8_t)5);
		dataSubList1->AddChildVariableInfo(dataValue);

		//219,  EquipmentID_1, g_clMesCommunication[m_nUnit].m_sEquipmentID
		//
		m_pWrapper->SetVariable(dataMainList);

		m_pWrapper->SetVariable(_T("10021"), 1);//by Host ECChangeOrderType
	}
	else if (strCENumber == EQUIPMENT_OPERATION_MODE_CHANGED_REPORT)//_T("10301"))//Equipment Operation Mode Changed Report
	{
		/*
		10012	10012	EquipmentOperationMode U1
		10013	10013	EqpOperationModeChangeOrderType U1

		*/
		//EquipmentOperationMode (0 ~ 9)
		//0 = Undefined
		//1 = Full-Auto Mode
		//2 = Semi-Auto Mode
		//3 = Dry Running Mode
		//4 = Skip Mode (Bypass Mode)
		//5 = Prototype Module Mode (LaserMarking, Underfill Only)
		//6 ~ 8 = Reserved
		//9 = Manual Mode

		m_pWrapper->SetVariable(_T("10012"), g_clMesCommunication[m_nUnit].m_dEqupOperationMode[0]);// 9);	//EquipmentOperationMode 1, 9 주로 사용
		m_pWrapper->SetVariable(_T("10013"), g_clMesCommunication[m_nUnit].m_dEqupOperationMode[1]);//0);
	}
	else if (strCENumber == PROCESS_STATE_CHANGED_REPORT_10401)	//Process State Changed Report
	{
		/*
		10011	10011	ProcerssStateInfo L2-(U1,U1)
		10022	10022	AlarmSetList Ln-(U4)

		*/
		if (g_clMesCommunication[m_nUnit].m_dProcessState[0] == g_clMesCommunication[m_nUnit].m_dProcessState[1])
		{
			return;
		}
		UbiGEMWrapper::Structure::VariableInfo* dataMainList;
		UbiGEMWrapper::Structure::VariableInfo* dataValue;

		dataMainList = m_pWrapper->CreateVariable(_T("10011"), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("ProcerssStateInfo"));
		
		//<Process State Code Definition>
		//1 = INIT
		//2 = IDLE
		//3 = SETUP
		//4 = READY
		//5 = EXECUTING
		//6 = PAUSE (알람 동반)
		
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("CurrentProcessState"));
		dataValue->SetValue((uint8_t)g_clMesCommunication[m_nUnit].m_dProcessState[1]);
		dataMainList->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("PreviousProcessState"));
		dataValue->SetValue((uint8_t)g_clMesCommunication[m_nUnit].m_dProcessState[0]);
		dataMainList->AddChildVariableInfo(dataValue);

		m_pWrapper->SetVariable(dataMainList);
		///m_pWrapper->DeleteVariableInfo(dataMainList);

		//
		dataMainList = m_pWrapper->CreateVariable(_T("10022"), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("AlarmSetList"));
		////dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U4, _T("ALID"));
		////dataValue->SetValue((uint32_t)g_clMesCommunication[m_nUnit].m_dAlarmCode);// 1001);
		//dataMainList->AddChildVariableInfo(dataValue);
		//
		for (int i = 0; i < g_clMesCommunication[m_nUnit].m_uAlarmList.size(); i++)
		{
			dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U4, _T("ALID"));
			dataValue->SetValue((uint32_t)g_clMesCommunication[m_nUnit].m_uAlarmList[i]);
			dataMainList->AddChildVariableInfo(dataValue);
		}
		//

		

		m_pWrapper->SetVariable(dataMainList);

	}
	else if (strCENumber == IDLE_REASON_REPORT_10402)//_T("10402"))//Idle Reason Report
	{
		//10037	10037	IdleReasonInfo L6-(A, A, A, A, A, A)

		UbiGEMWrapper::Structure::VariableInfo* dataMainList;
		UbiGEMWrapper::Structure::VariableInfo* dataValue;

		dataMainList = m_pWrapper->CreateVariable(_T("10037"), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("IdleReasonInfo"));


		CString szStr;



		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("OperatorID"));
		dataValue->SetValue(g_clMesCommunication[m_nUnit].m_sMesOperatorID);
		dataMainList->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("IDLECODE"));
		AfxExtractSubString(szStr, param, 0, _T(','));
		dataValue->SetValue(szStr);
		dataMainList->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("IDLETEXT"));
		AfxExtractSubString(szStr, param, 1, _T(','));
		dataValue->SetValue(szStr);
		dataMainList->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("IDLESTARTTIME"));
		AfxExtractSubString(szStr, param, 2, _T(','));
		dataValue->SetValue(szStr);
		dataMainList->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("IDLEENDTIME"));
		AfxExtractSubString(szStr, param, 3, _T(','));
		dataValue->SetValue(szStr);
		dataMainList->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("IDLENOTE"));
		AfxExtractSubString(szStr, param, 4, _T(','));
		dataValue->SetValue(szStr);
		dataMainList->AddChildVariableInfo(dataValue);

		m_pWrapper->SetVariable(dataMainList);

	}
	else if (strCENumber == PROCESS_PROGRAM_STATE_CHANGED_REPORT_10601)
	{
		//10016 PPStateChangedPPIDInfo
		//g_clMesCommunication[m_nUnit].m_dPPChangeArr[0]

		UbiGEMWrapper::Structure::VariableInfo* dataMainList;
		UbiGEMWrapper::Structure::VariableInfo* dataValue;


		dataMainList = m_pWrapper->CreateVariable(_T("10016"), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("PPStateChangedPPIDInfo"));

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("PPStateChangedPPID"));
		dataValue->SetValue(param);
		dataMainList->AddChildVariableInfo(dataValue);
		
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("PPStateChangedPPIDVersion"));
		dataValue->SetValue(g_clMesCommunication[m_nUnit].m_sMesRecipeRevision);	//ReportFn
		dataMainList->AddChildVariableInfo(dataValue);

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("PPChangedState"));
		dataValue->SetValue((uint8_t)g_clMesCommunication[m_nUnit].m_dPPChangeArr[0]);
		dataMainList->AddChildVariableInfo(dataValue);

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("PPChangeOrderType"));
		dataValue->SetValue((uint8_t)g_clMesCommunication[m_nUnit].m_dPPChangeArr[1]);
		dataMainList->AddChildVariableInfo(dataValue);

		m_pWrapper->SetVariable(dataMainList);
	}
	else if (strCENumber == OBJECT_ID_REPORT_10701)//_T("10701"))//Object ID Report
	{
		//10024	10024	LotInfo
		
	}
	else if (strCENumber == PP_SELECTED_REPORT_10702 || strCENumber == PP_UPLOAD_COMPLETED_REPORT_10703)
	{
		//PP-Selected Report 10702
		//PP Upload Completed Report 10703
		/*
		10024	10024	LotInfo
		10026	10026	CarrierInfo

		*/

		UbiGEMWrapper::Structure::VariableInfo* dataMainList;
		
		
		dataMainList = m_pWrapper->CreateVariable(_T("10026"), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("CarrierInfo"));

#if 0		//CarrierInfo 는 사용 안함
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U4, _T("PortID"));
		dataValue->SetValue((uint64_t)1);
		dataMainList->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("LotID"));
		dataValue->SetValue(lotId.c_str());// g_clTaskWork[m_nUnit].m_szChipID);
		dataMainList->AddChildVariableInfo(dataValue);
		//g_clMesCommunication[nUnit].m_sMesLotID


		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("CarrierID")); 
		dataValue->SetValue(carId.c_str());
		dataMainList->AddChildVariableInfo(dataValue);

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("ProcessID"));
		dataValue->SetValue(pcId.c_str());
		dataMainList->AddChildVariableInfo(dataValue);

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("ProductID")); 
		dataValue->SetValue(pdId.c_str());	/// ModelList.m_szCurrentModel);
		dataMainList->AddChildVariableInfo(dataValue);

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("LotProcessingState"));
		g_clMesCommunication[m_nUnit].m_dLotProcessingState = 2;
		dataValue->SetValue((uint8_t)g_clMesCommunication[m_nUnit].m_dLotProcessingState);
		dataMainList->AddChildVariableInfo(dataValue);
		
		//<Lot Processing State Code Definition>
		//1 = Scan (Lot ID Report ~ PP-SELECT)
		//2 = Ready (PP-Selected Report ~ START)
		//3 = Wait (START ~ Lot Processing Started)
		//4 = Processing (Lot Processing Started ~ Lot Processing Completed)
		//5 = Completed (Lot Processing Completed ~ MGZ Output Completed)
		


		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("RecipeID"));
		dataValue->SetValue(g_clMesCommunication[m_nUnit].m_sRecipeId);	//xxx 사용 안함
		dataMainList->AddChildVariableInfo(dataValue);

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("RecipeIDVersion"));
		dataValue->SetValue(_T(""));
		dataMainList->AddChildVariableInfo(dataValue);

		dataSubList1 = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("LotList"));
		dataMainList->AddChildVariableInfo(dataSubList1);
		//
		dataSubList2 = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("LotInfo"));
		dataSubList1->AddChildVariableInfo(dataSubList2);

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("LotID"));
		dataValue->SetValue(_T(""));
		dataSubList2->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("PocketID"));
		dataValue->SetValue(_T(""));
		dataSubList2->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("ModuleID"));
		dataValue->SetValue(_T(""));
		dataSubList2->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("Judge"));
		dataValue->SetValue(_T(""));
		dataSubList2->AddChildVariableInfo(dataValue);
#endif
		m_pWrapper->SetVariable(dataMainList);
	}
	else if (strCENumber == LOT_PROCESSING_STARTED_REPORT_10704)// _T("10704"))//Lot Processing Started Report
	{
		//10024	10024	LotInfo

	}
	else if (strCENumber == LOT_PROCESSING_COMPLETED_REPORT_10710)///_T("10710"))//Lot Processing Completed Report
	{
		/*
		10024	10024	LotInfo
		10051	10051	TraceabilityInfo_Lot

		*/
		UbiGEMWrapper::Structure::VariableInfo* dataMainList;
		UbiGEMWrapper::Structure::VariableInfo* dataSubList1;

		UbiGEMWrapper::Structure::VariableInfo* dataSubSubList1;
		UbiGEMWrapper::Structure::VariableInfo* dataSubSubList2;
		UbiGEMWrapper::Structure::VariableInfo* dataSubSubList3;
		UbiGEMWrapper::Structure::VariableInfo* dataSubSubSubList1;
		UbiGEMWrapper::Structure::VariableInfo* dataValue;

		//std::vector<RcmdList_T2_N> resultsT2_n;
		std::vector<RcmdParameter> vSet_3;
		vSet_3 = g_clReportData.vLotStart;
		//resultsT2_n = g_clReportData.T2N_FindChildList(g_clReportData.rLot_Start.parameters, 14);

		std::string lotId;
		std::string pcId;
		std::string pkId;
		std::string pdId;
		std::string moId;
		

		/*if (resultsT2_n.size() > 0)
		{
			for (i = 0; i < resultsT2_n[0].rVec.size(); i++)
			{
				if (resultsT2_n[0].rVec[i].cpName == "LOTID")
				{
					lotId = resultsT2_n[0].rVec[i].cepVal;
				}
				if (resultsT2_n[0].rVec[i].cpName == "PROCID")
				{
					pcId = resultsT2_n[0].rVec[i].cepVal;
				}
				if (resultsT2_n[0].rVec[i].cpName == "PRODID")
				{
					pdId = resultsT2_n[0].rVec[i].cepVal;
				}
				if (resultsT2_n[0].rVec[i].cpName == "POCKETID")
				{
					pkId = resultsT2_n[0].rVec[i].cepVal;
				}
				if (resultsT2_n[0].rVec[i].cpName == "MODULEID")
				{
					moId = resultsT2_n[0].rVec[i].cepVal;
				}
			}
		}*/
		if (vSet_3.size() > 0)
		{
			for (i = 0; i < vSet_3[0].children.size(); i++)
			{
				if (vSet_3[0].children[i].name == "LOTID")
				{
					lotId = vSet_3[0].children[i].value;
				}
				if (vSet_3[0].children[i].name == "PROCID")
				{
					pcId = vSet_3[0].children[i].value;
				}
				if (vSet_3[0].children[i].name == "PRODID")
				{
					pdId = vSet_3[0].children[i].value;
				}
				if (vSet_3[0].children[i].name == "POCKETID")
				{
					pkId = vSet_3[0].children[i].value;
				}
				if (vSet_3[0].children[i].name == "MODULEID")
				{
					moId = vSet_3[0].children[i].value;
				}
			}
		}

		dataMainList = m_pWrapper->CreateVariable(_T("10051"), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("LotList"));
		dataSubList1 = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("LotInfo"));
		dataMainList->AddChildVariableInfo(dataSubList1);
		//
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U4, _T("PortID"));
		dataValue->SetValue((uint64_t)1);
		dataSubList1->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("LotID"));	//mes id?
		dataValue->SetValue(lotId.c_str());
		dataSubList1->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("CarrierID"));
		dataValue->SetValue(_T(""));
		dataSubList1->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("PocketID"));
		dataValue->SetValue(_T(""));
		dataSubList1->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("ModuleID"));
		dataValue->SetValue(g_clTaskWork[m_nUnit].m_szChipID);
		dataSubList1->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("ProcessID"));
		dataValue->SetValue(pcId.c_str());
		dataSubList1->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("ProductID"));	//model
		dataValue->SetValue(pdId.c_str());// ModelList.m_szCurrentModel);
		dataSubList1->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("ModuleJudgeCode"));

		if (g_clMesCommunication[m_nUnit].m_nMesFinalResult == 1)
		{
			g_clMesCommunication[m_nUnit].m_dEqpDefectCode.Format(_T(""));
			dataValue->SetValue(_T("OK"));		//OK
		}
		else
		{
			dataValue->SetValue(_T("NG"));		//NG
		}
		
		dataSubList1->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("ModuleDefectCode"));
		dataValue->SetValue(g_clMesCommunication[m_nUnit].m_dEqpDefectCode);
		dataSubList1->AddChildVariableInfo(dataValue);

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("EndType"));		//End Type

		if (g_clMesCommunication[m_nUnit].m_nMesFinalResult == 1)
		{
			dataValue->SetValue((uint8_t)0);//0 or 5주로 사용
		}
		else
		{
			dataValue->SetValue((uint8_t)5);//0 or 5주로 사용
		}
		
		dataSubList1->AddChildVariableInfo(dataValue);

		dataSubSubList1 = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("ModuleProcessedUnitList"));
		dataSubList1->AddChildVariableInfo(dataSubSubList1);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U4, _T("ModuleProcessedUnitID"));
		dataValue->SetValue((uint64_t)0);
		dataSubSubList1->AddChildVariableInfo(dataValue);


		dataSubSubList2 = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("UserDataList"));
		dataSubList1->AddChildVariableInfo(dataSubSubList2);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("UserData"));
		dataValue->SetValue(_T(""));
		dataSubSubList2->AddChildVariableInfo(dataValue);

		//
		dataSubSubList3 = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("UsedMaterialList"));	//설비에서 사용하는 자재 리스트
		dataSubList1->AddChildVariableInfo(dataSubSubList3);
#if 1

		//MaterialID 이게 없으면 임시 주석처림 보내라
		//임시 주석처리함 250106
		dataSubSubSubList1 = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("KeyMaterialLocationInfo"));
		dataSubSubList3->AddChildVariableInfo(dataSubSubSubList1);

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U4, _T("UnitNo"));
		dataValue->SetValue((uint64_t)1);
		dataSubSubSubList1->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("SlotNo"));
		dataValue->SetValue((uint8_t)1);
		dataSubSubSubList1->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("MaterialID"));
		dataValue->SetValue(g_clReportData.rMaterial_Id_Confirm.MaterialId);// _T("SOCKET01"));	//<---저장해야되나 save 
		dataSubSubSubList1->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("MaterialType"));
		dataValue->SetValue(g_clReportData.rMaterial_Id_Confirm.MaterialType);// _T("31"));
		dataSubSubSubList1->AddChildVariableInfo(dataValue);
#endif
		m_pWrapper->SetVariable(dataMainList);

	}
	else if (strCENumber == LOT_APD_REPORT_10711)//_T("10711"))//Lot APD Report
	{
		/*
		10024	10024	LotInfo
		40001	40001	Lot Process Data #1
		~	~	~
		49999	49999	Lot Process Data #n

		*/

		int i = 0;
		int vidCnt = 40002;
		CString strVid;
		for (i = 0; i < g_LotApdInfoCount; i++)
		{
			strVid.Format(_T("%d"), vidCnt + i);
			UbiGEMWrapper::Structure::VariableInfo* dataList = m_pWrapper->CreateVariable(strVid, UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("LotAPDInfo"));

			UbiGEMWrapper::Structure::VariableInfo* dataID = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("DATANAME"));
			dataID->SetValue(LOT_APD_INFO[i]);
			dataList->AddChildVariableInfo(dataID);

			UbiGEMWrapper::Structure::VariableInfo* subDataCount = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("DATAVALUE"));
			if (i < g_clMesCommunication[m_nUnit].vMesApdData.size())
			{
				subDataCount->SetValue(g_clMesCommunication[m_nUnit].vMesApdData[i].c_str());
			}
			else
			{
				subDataCount->SetValue(_T("0.00000"));
			}

			dataList->AddChildVariableInfo(subDataCount);

			m_pWrapper->SetVariable(dataList);

		}
		strVid.Empty();

	}
	else if (strCENumber == ABORTED_REPORT_10712)//_T("10712"))//Aborted Report
	{
		//10024	10024	LotInfo

	}
	else if (strCENumber == MATERIAL_ID_REPORT_10713 || strCENumber == MATERIAL_CHANGE_COMPLETED_REPORT_10714)
	{
		//Material ID Report 10713
		//Material Change Completed Report 10714

		UbiGEMWrapper::Structure::VariableInfo* dataMainList;
		UbiGEMWrapper::Structure::VariableInfo* dataValue;

		dataMainList = m_pWrapper->CreateVariable(_T("10035"), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("ChangedMaterialInfo"));

		//g_clReportData.rMaterial_Id_Confirm.MaterialId.Format(_T("SOCKET02"));

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("MaterialID"));
		dataValue->SetValue(g_clReportData.rMaterial_Id_Confirm.MaterialId);// _T("SOCKET01")); //받은값으로 보내라
		dataMainList->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U4, _T("UnitNo"));
		dataValue->SetValue((uint64_t)1);// g_clReportData.rMaterial_Id_Confirm.UnitNo);
		dataMainList->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("SlotNo"));
		dataValue->SetValue((uint8_t)1);//g_clReportData.rMaterial_Id_Confirm.SlotNo);
		dataMainList->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("MaterialType"));
		dataValue->SetValue(g_clReportData.rMaterial_Id_Confirm.MaterialType);	//일단 31
		dataMainList->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("RemainUseData"));
		dataValue->SetValue(g_clReportData.rMaterial_Id_Confirm.RemainData);
		dataMainList->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("ExchangeReason"));
		dataValue->SetValue(_T(""));
		dataMainList->AddChildVariableInfo(dataValue);

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("ProductID"));		//250217 추가
		dataValue->SetValue(ModelList.m_szCurrentModel);
		dataMainList->AddChildVariableInfo(dataValue);

		

		m_pWrapper->SetVariable(dataMainList);

		m_pWrapper->SetVariable(_T("10053"), _T(""));
	}
	else if (strCENumber == _T("10801"))//Operator Recognized Operator Call Message
	{
		//10038	10038	LastOperatorCallInfo

		UbiGEMWrapper::Structure::VariableInfo* dataMainList;
		UbiGEMWrapper::Structure::VariableInfo* dataValue;

		dataMainList = m_pWrapper->CreateVariable(_T("10038"), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("LastOperatorCallInfo"));

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("OPCALL_TYPE"));
		dataValue->SetValue((uint8_t)g_clReportData.rCtrlOp_Call.CallType);
		dataMainList->AddChildVariableInfo(dataValue);

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("OPCALL_CODE"));
		dataValue->SetValue(g_clReportData.rCtrlOp_Call.OpCall_Code);//opcall에서 받은값 그대로 다시 보낸다
		dataMainList->AddChildVariableInfo(dataValue);

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("OPCALL_TEXT"));
		dataValue->SetValue(g_clReportData.rCtrlOp_Call.OpCall_Text);//opcall에서 받은값 그대로 다시 보낸다
		dataMainList->AddChildVariableInfo(dataValue);

		 
		m_pWrapper->SetVariable(dataMainList);
	}
	else if (strCENumber == OP_RECOGNIZED_TERMINAL_REPORT_10901)//_T("10901"))//Operator Recognized Terminal Message
	{
		//10039	10039	HostTerminalMessage

		m_pWrapper->SetVariable(_T("10039"), param);
	}
	else if (strCENumber == T3_TIMEOUT_REPORT_11001)		////T3 Timeout Report
	{
		//10017	10017	T3TimeoutData

		m_pWrapper->SetVariable(_T("10017"), 1);	//T3 Timeout Data Code Definition
	}
	else if (strCENumber == CT_TIMEOUT_REPORT_11002)		//CT Timeout Report
	{
		//10018	10018	CTTimeoutData u1

		m_pWrapper->SetVariable(_T("10018"), uCtTimeOutData);//CT Timeout Data Code Definition

		
		//1 = section #1: S6F11- Carrier ID Report ~ S2F49 (LGIT_PP_SELECT / LGIT_CARRIER_LOT_START / LGIT_LOT_ID_FAIL)
		//2 = section #1: S6F11- Object ID Report ~ S2F49 (LGIT_PP_SELECT / LGIT_LOT_START / LGIT_LOT_ID_FAIL)
		//3 = section #3: S7F26 - Formatted Process Program Data ~ S2F49 (LGIT_PP_UPLOAD_CONFIRM / LGIT_PP_UPLOAD_FAIL)
		//4 = section #4 : S6F11- PP Upload Completed Report event ~ S2F49 (LGIT_CARRIER_LOT_START / LGIT_LOT_START)
		//5 = section #7: S6F11- Material ID Report event ~ S2F49 (LGIT_MATERIAL_ID_CONFIRM/LGIT_MATERIAL_ID_FAIL)
		//6 = section #9 : S6F11-Offline Change Request ~ S2F49 (LGIT_CTRLSTATE_CHG_REQ)
		
	}


	UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportCollectionEvent(strCENumber, true);
	//OnVariableUpdateRequest 호출

	UbisamAddLog(_T("ReportCollectionEvent2"), gemResult);
}
void CUbiGem::OnBnClickedButtonUbigemCeReport1()
{

	CString strCEID = GetGUIString(&m_cboCe);
	strSendCeId = strCEID;
	// EquipmentConstantChanged 관련 Collection Event 는 직접적으로 호출하면 안됩니다.
	if (strCEID != SAMPLE_CEID_EquipmentConstantChanged && strCEID != SAMPLE_CEID_EquipmentConstantChangedByHost && strCEID != _T(""))
	{
		if (m_pWrapper != nullptr)
		{
			reportCommonSet();
			ReportFn(strCEID);
			// OnVariableUpdateReqeust 이벤트 발생을 원하지 않을 경우
			// UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportCollectionEvent(strCEID, false);

			//UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportCollectionEvent(strCEID, true);	
			//OnVariableUpdateRequest 호출

			//UbisamAddLog(_T("ReportCollectionEvent1"), gemResult);

		}
	}
}

void CUbiGem::reportCommonSet()
{
	CTime cTime = CTime::GetCurrentTime();
	CString strData = _T("");
	//UbiGEMWrapper::Structure::VariableInfo* dataID = m_pWrapper->CreateVariable(vid, UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("Time"));

	//10001 = EquipmentID
	//10002 = EquipmentName
	//10003 = Time
	//~
	//10008 = OperatorID

	

	m_pWrapper->SetVariable(_T("10001"), g_clMesCommunication[m_nUnit].m_sEquipmentID);
	m_pWrapper->SetVariable(_T("10002"), g_clMesCommunication[m_nUnit].m_sEquipmentName);

	strData.Format(_T("%02d%02d%02d%02d%02d%02d"),
		cTime.GetYear() % 100,
		cTime.GetMonth(),
		cTime.GetDay(),
		cTime.GetHour(),
		cTime.GetMinute(),
		cTime.GetSecond());
	m_pWrapper->SetVariable(_T("10003"), strData);

	m_pWrapper->SetVariable(_T("10008"), g_clMesCommunication[m_nUnit].m_sMesOperatorID);	//OperatorID

	strData.Empty();
}

void CUbiGem::OnBnClickedButtonUbigemTest10711()
{
	//Lot APD Report - Optional - 10711
	strSendCeId = _T("10711");
	// EquipmentConstantChanged 관련 Collection Event 는 직접적으로 호출하면 안됩니다.
	if (m_pWrapper != nullptr)
		{

			//m_pWrapper->SetVariable(SAMPLE_VID_ControlState, 3);

			//10001 = EquipmentID
			//10002 = EquipmentName
			//10003 = Time
			//10024 = LotInfo

			//CString strData = _T("");
			//CTime cTime = CTime::GetCurrentTime();
			////UbiGEMWrapper::Structure::VariableInfo* dataID = m_pWrapper->CreateVariable(vid, UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("Time"));

			//strData.AppendFormat(_T("%02d%02d%02d%02d%02d%02d"),
			//	cTime.GetYear(),
			//	cTime.GetMonth(),
			//	cTime.GetDay(),
			//	cTime.GetHour(),
			//	cTime.GetMinute(),
			//	cTime.GetSecond());

			//m_pWrapper->SetVariable(_T("10001"), _T("eqpId"));
			//m_pWrapper->SetVariable(_T("10002"), _T("eqpName"));
			//m_pWrapper->SetVariable(_T("10003"), strData);
			//m_pWrapper->SetVariable(_T("10008"), g_clMesCommunication[m_nUnit].m_sMesOperatorID);	//OperatorID

			reportCommonSet();

			int i = 0;
			int vidCnt = 40002;
			CString strVid;
			for (i = 0; i < g_LotApdInfoCount; i++)
			{
				strVid.Format(_T("%d"), vidCnt + i);
				UbiGEMWrapper::Structure::VariableInfo* dataList = m_pWrapper->CreateVariable(strVid, UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("LotAPDInfo"));

				UbiGEMWrapper::Structure::VariableInfo* dataID = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("DATANAME"));
				dataID->SetValue(LOT_APD_INFO[i]);
				dataList->AddChildVariableInfo(dataID);

				UbiGEMWrapper::Structure::VariableInfo* subDataCount = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_A, _T("DATAVALUE"));
				if (i < g_clMesCommunication[m_nUnit].vMesApdData.size())
				{
					subDataCount->SetValue(g_clMesCommunication[m_nUnit].vMesApdData[i].c_str());
				}
				else
				{
					subDataCount->SetValue(_T("0.00000"));
				}

				dataList->AddChildVariableInfo(subDataCount);

				m_pWrapper->SetVariable(dataList);

			}
			strVid.Empty();
			UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportCollectionEvent(strSendCeId, true);	//<---실행후 OnVariableUpdateRequest 호출

			// OnVariableUpdateReqeust 이벤트 발생을 원하지 않을 경우
			// UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportCollectionEvent(strSendCeId, false);


			UbisamAddLog(_T("ReportCollectionEvent 10711"), gemResult);

		}
}

void CUbiGem::OnBnClickedButtonUbigemTest10401()
{
	//Process State Changed Report	10401

	strSendCeId = PROCESS_STATE_CHANGED_REPORT_10401;		//Manual
	if (m_pWrapper != nullptr)
	{

		//10001 = EquipmentID
		//10002 = EquipmentName
		//10003 = Time
		//
		//10011 = ProcessStateInfo (1 ~ 6)
		//1 = INIT
		//2 = IDLE
		//3 = SETUP
		//4 = READY
		//5 = EXECUTING
		//6 = PAUSE
		//
		//
		UbiGEMWrapper::Structure::VariableInfo* dataMainList = m_pWrapper->CreateVariable(_T("10011"), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("ProcessStateInfo"));
		UbiGEMWrapper::Structure::VariableInfo* dataValue;

		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("CurrentProcessState"));
		dataValue->SetValue((uint8_t)g_clMesCommunication[m_nUnit].m_dProcessState[1]);
		dataMainList->AddChildVariableInfo(dataValue);
		dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U1, _T("PreviousProcessState"));
		dataValue->SetValue((uint8_t)g_clMesCommunication[m_nUnit].m_dProcessState[0]);
		dataMainList->AddChildVariableInfo(dataValue);

		m_pWrapper->SetVariable(dataMainList);

		//10022 = AlarmSetList
		if (g_clMesCommunication[m_nUnit].m_dProcessState[1] == ePAUSE)
		{
			UbiGEMWrapper::Structure::VariableInfo* alarmMainList = m_pWrapper->CreateVariable(_T("10022"), UbiGEMWrapper::Structure::GEMSECSFormat_L, _T("AlarmSetList"));

			for (int i = 0; i < g_clMesCommunication[m_nUnit].m_uAlarmList.size(); i++)
			{
				dataValue = m_pWrapper->CreateVariable(_T(""), UbiGEMWrapper::Structure::GEMSECSFormat_U4, _T("ALID"));
				dataValue->SetValue((uint32_t)g_clMesCommunication[m_nUnit].m_uAlarmList[i]);
				alarmMainList->AddChildVariableInfo(dataValue);
			}
			

			m_pWrapper->SetVariable(alarmMainList);
		}
		//
		//10008 = OperatorID

			

		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportCollectionEvent(strSendCeId, true);	
		//실행후 OnVariableUpdateRequest 호출

		UbisamAddLog(_T("ReportCollectionEvent 10401"), gemResult);

	}
	
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
//
//
// Control state - Offline BUTTON
//
//
//-------------------------------------------------------------------------------------------------------------------------------------------------

void CUbiGem::OnBnClickedButtonUbigemCsOffline()
{
	if (m_pWrapper != nullptr)
	{
		g_clMesCommunication[m_nUnit].m_dControlStateChangeOrder = 2;	//by Operator


		//m_pWrapper->SetVariable(_T("10006"), _T("OPERATOR001"));	//ControlStateChangeReasonCode
		//m_pWrapper->SetVariable(_T("10007"), _T("Equipment에서 OFF-LINE 전환 하였습니다."));	//ControlStateChangeReasonText
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->RequestOffline();

		UbisamAddLog(_T("Request Offline"), gemResult);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
//
//
// Control state - Online Local BUTTON
//
//
//-------------------------------------------------------------------------------------------------------------------------------------------------

void CUbiGem::OnBnClickedButtonUbigemCsOnlineLocal()
{
	if (m_pWrapper != nullptr)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->RequestOnlineLocal();

		UbisamAddLog(_T("RequestOnlineLocal"), gemResult);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
//
//
// Control state - Online Remote BUTTON
//
//
//-------------------------------------------------------------------------------------------------------------------------------------------------

void CUbiGem::OnBnClickedButtonUbigemCsOnlineRemote()
{
	if (m_pWrapper != nullptr)
	{

		g_clMesCommunication[m_nUnit].m_dControlStateChangeOrder = 1;	//by Operator
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->RequestOnlineRemote();
		//
		//E) S1F1:AreYouThere --> H
		//H) S1F2:IAmHere --> E
		//E) S6F11 --> H
		//H) S6F12 --> E
		UbisamAddLog(_T("RequestOnlineRemote"), gemResult);
	}
}

void CUbiGem::TerminalMessageSendRequest(int itid, CString tmsg)
{
	CString strLog;
	UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportTerminalMessage(itid, tmsg);

	strLog.Format(_T("ReportTerminalMessage : [TID=%d,TEXT=%s]"), itid, tmsg);
	UbisamAddLog(strLog, gemResult);
}
void CUbiGem::OnBnClickedButtonUbigemTerminalMessageSend()
{
	CString tid;
	
	m_edtTId.GetWindowText(tid);
	CString tmsg = GetGUIString(&m_edtTerminalMessage);
	int itid = _ttoi(tid);


	TerminalMessageSendRequest(itid, tmsg);
}


void CUbiGem::OnBnClickedButtonUbigemTest10701()
{
	//Object ID Report - 10701
	strSendCeId = OBJECT_ID_REPORT_10701;// _T("10701");
	// EquipmentConstantChanged 관련 Collection Event 는 직접적으로 호출하면 안됩니다.
	if (strSendCeId != SAMPLE_CEID_EquipmentConstantChanged && strSendCeId != SAMPLE_CEID_EquipmentConstantChangedByHost && strSendCeId != _T(""))
	{
		if (m_pWrapper != nullptr)
		{

			//m_pWrapper->SetVariable(SAMPLE_VID_ControlState, 3);

			//10001 = EquipmentID
			//10002 = EquipmentName
			//10003 = Time
			//10024 = LotInfo
			//10008 = OperatorID
	
			reportCommonSet(); 

			UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportCollectionEvent(strSendCeId, true);	//<---실행후 OnVariableUpdateRequest 호출


			UbisamAddLog(_T("ReportCollectionEvent 10711"), gemResult);

		}
	}
}


bool CUbiGem::EventReportSendFn(CString strCEID, CString parameter)
{
	// EquipmentConstantChanged 관련 Collection Event 는 직접적으로 호출하면 안됩니다.
	if (strCEID != _T(""))
	{
		if (m_pWrapper != nullptr)
		{
			reportCommonSet();
			ReportFn(strCEID, parameter);



			// OnVariableUpdateReqeust 이벤트 발생을 원하지 않을 경우
			// UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportCollectionEvent(strCEID, false);

			//UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->ReportCollectionEvent(strCEID, true);	
			//OnVariableUpdateRequest 호출

			//UbisamAddLog(_T("ReportCollectionEvent1"), gemResult);

		}
	}

	return true;
}


void CUbiGem::OnBnClickedButtonUbigemVGet()
{

	CString strLog;
	CString strVid = GetGUIString(&m_cboV);
	//UbiGEMWrapper::Structure::GEMResult gemResult;

	if (m_pWrapper != nullptr)
	{
#if 1
		UbiGEMWrapper::Structure::VariableInfo *pVariableInfo = m_pWrapper->GetVariable(strVid);
		CString sVal = SECSValueAsString(pVariableInfo->Format, pVariableInfo->Value);
#endif

		strLog.Format(_T("Get Variable : [VID=%s,SV=%s])"), strVid, sVal);

		UbisamAddLog(strLog);
	}
}



void CUbiGem::OnBnClickedButtonUbigemRcmdView()
{
	TCHAR szLog[SIZE_OF_1K];
	CString strCEID = GetGUIString(&m_cboRcmdView);


	int i = 0;
	int j = 0;
	int k = 0;

	std::string kkk = "";

	_stprintf_s(szLog, SIZE_OF_1K, _T("[RCMD] %s Load"), strCEID);
	AddLog(szLog, 0, m_nUnit);

	if (strCEID == _T("LGIT_SETCODE_MATERIAL_EXCHANGE"))
	{
		int cnt = g_clReportData.vMaterialExchange.size();
		if (cnt > 0)
		{
			cnt = g_clReportData.vMaterialExchange[0].children.size();
			
			for (i = 0; i < cnt; i++)
			{
				kkk = g_clReportData.vMaterialExchange[0].children[i].name;		//31
				kkk = g_clReportData.vMaterialExchange[0].children[i].value;	//SOCKET

				int subCnt = g_clReportData.vMaterialExchange[0].children[i].children.size();

				for (j = 0; j < subCnt; j++)
				{
					kkk = g_clReportData.vMaterialExchange[0].children[i].children[j].name;		//RESNCODE01 - RESNCODE02
					kkk = g_clReportData.vMaterialExchange[0].children[i].children[j].value;	//Power off - Power off2
				}
			}
		}
	}
	if (strCEID == _T("LGIT_LOT_ID_FAIL"))
	{
		int cnt = g_clReportData.vLotIdFail.size();
		if (cnt > 0)
		{
			for (i = 0; i < 5; i++)
			{
				if (g_clReportData.vLotIdFail[0].children[i].name == "MODULEID")
				{
					CString sMsg;
					sMsg.Format(_T("LOT ID:%s"), g_clReportData.vLotIdFail[0].children[i].value);
					break;
				}

				_stprintf_s(szLog, SIZE_OF_1K, _T("[RCMD L%d]Name:%s, Val:%s"), i + 1, g_clReportData.vLotIdFail[0].children[i].name, g_clReportData.vLotIdFail[0].children[i].value);
				AddLog(szLog, 0, m_nUnit);
			}
		}
	}
	if (strCEID == _T("LGIT_LOT_START"))
	{
		int cnt = g_clReportData.vLotStart.size();
		if (cnt > 0)
		{
			cnt = g_clReportData.vLotStart[0].children.size();
			for (i = 0; i < cnt; i++)
			{
				if (g_clReportData.vLotStart[0].children[i].name == "LOTID")
				{
					kkk = g_clReportData.vLotStart[0].children[i].value;
				}
				if (g_clReportData.vLotStart[0].children[i].name == "PROCID")
				{
					kkk = g_clReportData.vLotStart[0].children[i].value;
				}
				if (g_clReportData.vLotStart[0].children[i].name == "PRODID")
				{
					kkk = g_clReportData.vLotStart[0].children[i].value;
				}
				int subCnt = g_clReportData.vLotStart[0].children[i].children.size();
				for (j = 0; j < subCnt; j++)
				{
					kkk = g_clReportData.vLotStart[0].children[i].children[j].name;		//SpecialData #1, #2
					kkk = g_clReportData.vLotStart[0].children[i].children[j].value;	//VALUE1 , 2
				}
			}
		}
	}
	if (strCEID == _T("LGIT_SETCODE_OFFLINE_REASON"))
	{
	}
	else if (strCEID == _T("LGIT_SETCODE_IDLE_REASON"))
	{
	}
	else if (strCEID == _T("LGIT_SETCODE_MODEL_LIST"))
	{
	}
	else if (strCEID == _T("LGIT_PP_UPLOAD_FAIL"))
	{
	}
	if (strCEID == _T("LGIT_PP_SELECT"))
	{
	}
	else if (strCEID == _T("LGIT_PP_UPLOAD_CONFIRM"))
	{
	}
}


void CUbiGem::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case WM_CT_TIMEOUT_TIMER:
		KillTimer(WM_CT_TIMEOUT_TIMER);				//In OnTimer
		//EventReportSendFn(CT_TIMEOUT_REPORT_11002); //SEND S6F11
		
		//Ct Time out
		break;

	}
	__super::OnTimer(nIDEvent);
}


void CUbiGem::OnBnClickedButtonUbigemTestIdleTime()
{
}


void CUbiGem::OnBnClickedButtonUbigemLoopback()
{
	CString Abs = GetGUIString(&m_edtAbs);
	UbiGEMWrapper::Structure::List<uint8_t>* pAbs;

	int length = Abs.GetAllocLength();

	if (m_pWrapper != nullptr && length > 0)
	{
		pAbs = m_pWrapper->CreateU1List();

		for (int i = 0; i < length; i++)
		{
			pAbs->Add((uint8_t)Abs.GetAt(i));
		}

		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->RequestLoopback(pAbs);

		UbisamAddLog(_T("RequestLoopback"), gemResult);

		m_pWrapper->DeleteU1List(pAbs);
		pAbs = nullptr;
	}
}


void CUbiGem::OnBnClickedButtonUbigemTimeRequest()
{
	if (m_pWrapper != nullptr)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->RequestDateTime();

		UbisamAddLog(_T("RequestDateTime"), gemResult);
	}
}


void CUbiGem::OnBnClickedButtonUbigemTest10710()
{
	EventReportSendFn(LOT_PROCESSING_COMPLETED_REPORT_10710); //SEND S6F11
}


void CUbiGem::OnBnClickedButtonUbigemCsOnlineEstablish()
{
	if (m_pWrapper != nullptr)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->EstablishCommunication();

		UbisamAddLog(_T("EstablishCommunication"), gemResult);
	}
}


void CUbiGem::OnBnClickedButtonUbigemTestFmtPpVerificationSend()
{
	CString ppid = _T("PPID_TEST");// GetGUIString(&m_edtFmtPpid);
	CString strppid, strLog;
	strppid.Format(_T("%s"), ppid);


	UbiGEMWrapper::Structure::FmtPPVerificationCollection* pFmtPPVerificationCollection;

	pFmtPPVerificationCollection = m_pWrapper->CreateFmtPPVerificationCollection(ppid);

	if (m_pWrapper != nullptr && strppid.GetAllocLength() > 0)
	{
		UbiGEMWrapper::Structure::GEMResult gemResult = m_pWrapper->RequestFmtPPVerificationSend(pFmtPPVerificationCollection);

		strLog.Format(_T("RequestFmtPPVerificationSend : [fmtPPID=%s]"), ppid);

		UbisamAddLog(strLog, gemResult);
	}

	m_pWrapper->DeleteFmtPPVerificationCollection(pFmtPPVerificationCollection);
	pFmtPPVerificationCollection = nullptr;
}
void CUbiGem::CtTimeOut_Kill()
{
	KillTimer(WM_CT_TIMEOUT_TIMER);
}