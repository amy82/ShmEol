// EEPROMTest.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EEPROMTest.h"
#include "AutoInsp.h"
#include "AutoInspDlg.h"
#include "CeepromData.h"
#include "afxdialogex.h"

// CEEPROMTest 대화 상자입니다.
#define MAX_LENGTH 1025
IMPLEMENT_DYNAMIC(CEEPROMTest, CDialogEx)

CEEPROMTest::CEEPROMTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_EEPROM, pParent)
	, m_Str_SlaveAddr(_T("0x50"))
	, m_Str_Addr(_T("0x0000"))
	, m_Str_AddrLength(2)
	, m_Str_DataLength(0)
{
	m_nUnit = UNIT_AA1;
}

CEEPROMTest::~CEEPROMTest()
{
}

void CEEPROMTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SLAVE_ADDR, m_Str_SlaveAddr);
	DDX_Text(pDX, IDC_EDIT_ADDR, m_Str_Addr);
	DDX_Text(pDX, IDC_EDIT_ADDR_LENGTH, m_Str_AddrLength);
	DDX_Text(pDX, IDC_EDIT_DATA_LENGTH, m_Str_DataLength);
	DDX_Text(pDX, IDC_EDIT_DATA, m_Str_Data_Hex);
	DDX_Text(pDX, IDC_EDIT_DATA2, m_Str_Data_Ch);
	
	DDX_Control(pDX, IDC_BTN_OUTPUT_ASCII, m_Button_Ascii);
	DDX_Control(pDX, IDC_BTN_OUTPUT_FLOAT, m_Button_Float);
	DDX_Control(pDX, IDC_BTN_OUTPUT_DEC, m_Button_Dec);
	DDX_Control(pDX, IDC_BTN_OUTPUT_HEX, m_Button_Hex);
	
}


BEGIN_MESSAGE_MAP(CEEPROMTest, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_READ, &CEEPROMTest::OnBnClickedBtnRead)
	ON_BN_CLICKED(IDC_BTN_MIU_OPEN, &CEEPROMTest::OnBnClickedBtnMiuOpen)
	ON_BN_CLICKED(IDC_BTN_MIU_STOP, &CEEPROMTest::OnBnClickedBtnMiuStop)
	ON_BN_CLICKED(IDC_BTN_MIU_CLOSE, &CEEPROMTest::OnBnClickedBtnMiuClose)
	ON_BN_CLICKED(IDC_BTN_WRITE, &CEEPROMTest::OnBnClickedBtnWrite)
	ON_BN_CLICKED(IDCANCEL, &CEEPROMTest::OnBnClickedCancel)

	ON_BN_CLICKED(IDC_BTN_OUTPUT_ASCII, &CEEPROMTest::OnBnClickedBtnOutputAscii)
	ON_BN_CLICKED(IDC_BTN_OUTPUT_FLOAT, &CEEPROMTest::OnBnClickedBtnOutputFloat)
	ON_BN_CLICKED(IDC_BTN_OUTPUT_DEC, &CEEPROMTest::OnBnClickedBtnOutputDec)
	ON_BN_CLICKED(IDC_BTN_OUTPUT_HEX, &CEEPROMTest::OnBnClickedBtnOutputHex)
	ON_BN_CLICKED(IDOK, &CEEPROMTest::OnBnClickedOk)
END_MESSAGE_MAP()


// CEEPROMTest 메시지 처리기입니다.


BOOL CEEPROMTest::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetInterface();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CEEPROMTest::SetInterface()
{
	output_Mode = ASCII_MODE;
	FuncModeChange(output_Mode);
}
///-------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------
//
//EEPROM READ
//
///-------------------------------------------------------------------------------------
void CEEPROMTest::OnBnClickedBtnRead()
{
	if (!g_clLaonGrabberWrapper[m_nUnit].m_pBoard->IsConnected())
	{
		AddLog("[CCD] Grabber Board 해제 상태", 1, m_nUnit);
		return;
	}
	
	unsigned int nSlaveAddress;
	unsigned int nAddress;
	unsigned char pData[MAX_LENGTH];
	int errorCode = 0;

	UpdateData(TRUE);
	sscanf_s(m_Str_SlaveAddr.GetBuffer(0), "%x", &nSlaveAddress);
	sscanf_s(m_Str_Addr.GetBuffer(0), "%x", &nAddress);

	m_Str_Data_Hex.Empty();
	m_Str_Data_Ch.Empty();


	UpdateData(FALSE); 

	


	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	if (!g_clLaonGrabberWrapper[m_nUnit].m_pBoard->IsConnected())
	{
		AddLog("[CCD] Grabber Board 해제 상태", 1, m_nUnit);
	}
	
	errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->ReadI2CBurst((unsigned short)nSlaveAddress, (unsigned short)nAddress, m_Str_AddrLength, pData, (unsigned short)m_Str_DataLength);
	CString tempData;
	CString tenData;
	int ten; 
	char szHex[16];
	if (errorCode)
	{
		m_Str_Data_Hex.Format("Error : %d", errorCode);
	}
	else
	{
		m_Str_Data_Hex = "";
		m_Str_Data_Ch = "";
		for (int i = 0; i < (int)m_Str_DataLength; i++)
		{
			m_Str_Data_Hex.AppendFormat("%02X", (char*)pData[i]);

		}
	}
	AddLog(m_Str_Data_Ch, 1, m_nUnit);
	UpdateData(FALSE);
}

///-------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------
//
//EEPROM WRITE
//
///-------------------------------------------------------------------------------------
void CEEPROMTest::OnBnClickedBtnWrite()
{
	unsigned int nSlaveAddress;
	unsigned int nAddress;
	unsigned char pData[MAX_LENGTH];
	unsigned char charStr[MAX_PATH];
	int errorCode = 0;
	byte rtnData[MAX_PATH];
	UpdateData(TRUE);

	sscanf_s(m_Str_SlaveAddr.GetBuffer(0), "%x", &nSlaveAddress);
	sscanf_s(m_Str_Addr.GetBuffer(0), "%x", &nAddress);

	/*if (!g_clLaonGrabberWrapper[m_nUnit].m_pBoard->SetWPDisable()) {
		theApp.MainDlg->putListLog("Write Disable fail!!!!!");
	}
	else {
		theApp.MainDlg->putListLog("Write Disable Success");
	}*/
	errorCode = g_clLaonGrabberWrapper[m_nUnit].m_pBoard->WriteI2CBurst((unsigned short)0x50, (unsigned short)nAddress, 2, rtnData, (unsigned short)m_Str_DataLength);
	//
	//

	/*if (!g_clLaonGrabberWrapper[m_nUnit].m_pBoard->SetWPEnable()) {
		theApp.MainDlg->putListLog("Write Enable fail!!!!!");
	}
	else {
		theApp.MainDlg->putListLog("Write Enable Success");
	}*/

	if (errorCode)
	{
		m_Str_Data_Hex.Format("Error : %d", errorCode);
	}
	else
	{
		AddLog("wright ok!", 1, m_nUnit);
	}
	return;
	
}
///-------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------
//
//
//
///-------------------------------------------------------------------------------------

void CEEPROMTest::OnBnClickedBtnMiuOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int errorCode = -1;
	CString strErrCount;
	CString selectedIniFile;

	bool rtn = false;
	rtn = g_clLaonGrabberWrapper[m_nUnit].OpenDevice();

	if (!rtn)
	{
		strErrCount.Format("OpenBoard Fail");
	}
	else
	{
		strErrCount.Format("OpenBoard Success");
	}
	AddLog("strErrCount", 1, m_nUnit);
}


void CEEPROMTest::OnBnClickedBtnMiuStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#ifndef ON_LINE_GRABBER
	return;
#endif

	g_clLaonGrabberWrapper[m_nUnit].StopGrab();
}


void CEEPROMTest::OnBnClickedBtnMiuClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#ifdef ON_LINE_GRABBER
	g_clLaonGrabberWrapper[m_nUnit].CloseDevice();
#endif
}

//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CEEPROMTest::SetUnit(int nUnit)
{
	m_nUnit = nUnit;
}



void CEEPROMTest::OnBnClickedCancel()
{
	/*if (!MIU.m_pBoard->SetWPDisable())
		AfxMessageBox("Write fail!!!!!");
	else
		AfxMessageBox("Write Success");*/

	//return;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CEEPROMTest::FuncModeChange(int type)
{
	m_Button_Ascii.m_iStateBtn = 0;
	m_Button_Float.m_iStateBtn = 0;
	m_Button_Dec.m_iStateBtn = 0;
	m_Button_Hex.m_iStateBtn = 0;
	switch (type)
	{
	case ASCII_MODE:
		m_Button_Ascii.m_iStateBtn = 1;
		break;
	case FLOAT_MODE:
		m_Button_Float.m_iStateBtn = 1;
		break;

	case DEC_MODE:
		m_Button_Dec.m_iStateBtn = 1;
		break;
	case HEX_MODE:
		m_Button_Hex.m_iStateBtn = 1;
		break;
	}
	m_Button_Ascii.Invalidate();
	m_Button_Float.Invalidate();
	m_Button_Dec.Invalidate();
	m_Button_Hex.Invalidate();
}
void CEEPROMTest::OnBnClickedBtnOutputAscii()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	output_Mode = ASCII_MODE;//hex
	AddLog("Ascii Output", 1, m_nUnit, false);
	FuncModeChange(output_Mode);
}
void CEEPROMTest::OnBnClickedBtnOutputHex()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	output_Mode = HEX_MODE;//hex
	AddLog("hex Output", 1, m_nUnit, false);
	FuncModeChange(output_Mode);
}


void CEEPROMTest::OnBnClickedBtnOutputFloat()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	output_Mode = FLOAT_MODE;//float
	AddLog("float Output", 1, m_nUnit, false);
	FuncModeChange(output_Mode);
}


void CEEPROMTest::OnBnClickedBtnOutputDec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	output_Mode = DEC_MODE;//float
	AddLog("dec Output", 1, m_nUnit, false);
	FuncModeChange(output_Mode);
}


void CEEPROMTest::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
