// ManualDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AutoInsp.h"
#include "ManualDlg.h"
#include "afxdialogex.h"

#define WM_UI_TIMER				WM_USER + 999

// CManualDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualDlg, CDialogEx)

CManualDlg::CManualDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualDlg::IDD, pParent)
{	
	int i;

	m_nUnit = UNIT_AA1;
	
	for(i = 0; i < MAX_UNIT_COUNT; i++)
	{
		m_nPrevDarkPusherState[i] = -1;
		m_nPrevPcbSocketState[i] = -1;
		m_nPrevPcbSocketUpState[i] = -1;
		m_nPrevPcbSocketVacuumOnState[i] = -1;
		m_nPrevPcbSocketVacuumOffState[i] = -1;
	}
}

CManualDlg::~CManualDlg()
{
}

void CManualDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_MANUAL_TITLE, m_clColorStaticTitle);
	
	
	DDX_Control(pDX, IDC_STATIC_MANUAL_PCB_IO, m_clColorStaticTitlePcbIO);
	DDX_Control(pDX, IDC_STATIC_MANUAL_PCB_IO_IN, m_clColorStaticTitlePcbIO_IN);
	
	DDX_Control(pDX, IDC_STATIC_MANUAL_LENS, m_clColorStaticTitleLENS);
	DDX_Control(pDX, IDC_STATIC_MANUAL_LENS_POSITION, m_clColorStaticTitleLensPos);
	DDX_Control(pDX, IDC_STATIC_MANUAL_LENS_Z_POSITION, m_clColorStaticTitleLensPosZ);
	DDX_Control(pDX, IDC_STATIC_MANUAL_UV_IO, m_clColorStaticTitleUvIO);
	DDX_Control(pDX, IDC_STATIC_MANUAL_ALIGN_X, m_clColorStaticAlignX);
	DDX_Control(pDX, IDC_STATIC_MANUAL_ALIGN_Y, m_clColorStaticAlignY);
	DDX_Control(pDX, IDC_STATIC_MANUAL_ALIGN_THETA, m_clColorStaticAlignTH);
	DDX_Control(pDX, IDC_STATIC_MANUAL_ALIGN_X_VAL, m_clColorStaticAlignXVal);
	DDX_Control(pDX, IDC_STATIC_MANUAL_ALIGN_Y_VAL, m_clColorStaticAlignYVal);
	DDX_Control(pDX, IDC_STATIC_MANUAL_ALIGN_THETA_VAL, m_clColorStaticAlignTHVal);
	DDX_Control(pDX, IDC_STATIC_MANUAL_BCR_TEXT, m_clColorStaticBcrText);
	//
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_CHECK, m_clColorButtonPcbCheck);


	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_VACUUM_ON, m_clColorButtonPcbVacuumOn);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_VACUUM_OFF, m_clColorButtonPcbVacuumOff);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_GRIP_FOR, m_clColorButtonPcbGripFor);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_GRIP_BACK, m_clColorButtonPcbGripBack);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_SOCKET_UP, m_clColorButtonPcbSocketUp);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_SOCKET_DOWN, m_clColorButtonPcbSocketDown);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_DARK_UP, m_clColorButtonPcbDarkUp);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_DARK_DOWN, m_clColorButtonPcbDarkDown);

	DDX_Control(pDX, IDC_BUTTON_MANUAL_LENS_GRIP, m_clColorButtonLensGrip);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LENS_UNGRIP, m_clColorButtonLensUnGrip);

	DDX_Control(pDX, IDC_BUTTON_MANUAL_EPOXY_ON, m_clColorButtonEpoxyOn);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_EPOXY_SET, m_clColorButtonEpoxySet);


	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_OC_FOR, m_clColorButtonPcbOCFor);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_OC_BACK, m_clColorButtonPcbOCBack);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LENS_GRIP_FOR,  m_clColorButtonLensGripFor);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LENS_GRIP_BACK, m_clColorButtonLensGripBack);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LENS_CENT_FOR, m_clColorButtonLensCentFor);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LENS_CENT_BACK, m_clColorButtonLensCentBack);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_UV_ON, m_clColorButtonUVOn);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_UV_OFF, m_clColorButtonUVOff);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_SOCKET_CHECK, m_clColorButtonPcbSocketCheck);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LENS_SOCKET_CHECK, m_clColorButtonLensSocketCheck);
	


	//eol 에서만 사용하는 ui
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_WAIT, m_clColorButtonPcbWaitPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_Z_WAIT, m_clColorButtonPcbZWaitPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_ALIGN, m_clColorButtonPcbAlignPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_Z_ALIGN, m_clColorButtonPcbZAlignPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_BONDING, m_clColorButtonPcbBondingPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_Z_BONDING, m_clColorButtonPcbZBondingPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_OC_TOTAL, m_clColorButtonPcbOcTotalPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_Z_OC_TOTAL, m_clColorButtonPcbZOcTotalPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_LOAD, m_clColorButtonPcbLoadPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_Z_LOAD, m_clColorButtonPcbZLoadPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_UNLOAD, m_clColorButtonPcbUnLoadPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_Z_UNLOAD, m_clColorButtonPcbZUnLoadPos);
	DDX_Control(pDX, IDC_STATIC_MANUAL_PCB, m_clColorStaticTitlePCB);
	DDX_Control(pDX, IDC_STATIC_MANUAL_LASER, m_clColorStaticTitleLaser);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LASER_IN_1, m_clColorButtonLaserIn1);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LASER_IN_2, m_clColorButtonLaserIn2);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LASER_IN_3, m_clColorButtonLaserIn3);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LASER_IN_4, m_clColorButtonLaserIn4);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LASER_IN_Z, m_clColorButtonLaserInZ);
	
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LASER_DATA_MEAS, m_clColorButtonLaserDataMeas);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LASER_AUTO, m_clColorButtonLaserAutoMeas);
	//
	
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_HOLDER_ALIGN, m_clColorButtonPcbHolderAlignPos);
	
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_DISPENSE, m_clColorButtonPcbDispensePos);


	DDX_Control(pDX, IDC_BUTTON_MANUAL_LENS_ALIGN, m_clColorButtonLensAlignPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LENS_Z_ALIGN, m_clColorButtonLensZAlignPos);

	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_LASER_IN, m_clColorButtonPcbLaserInPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_LASER_OUT, m_clColorButtonPcbLaserOutPos);
	
	
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_DARK, m_clColorButtonPcbDarkPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_DEFECT, m_clColorButtonPcbDefectPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_OC_2800, m_clColorButtonPcbOc5000kPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_OC_Z_2800, m_clColorButtonPcbZOc5000kPos);
	
	
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_Z_LASER_IN, m_clColorButtonPcbZLaserInPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_Z_LASER_OUT, m_clColorButtonPcbZLaserOutPos);

	
	
	
	
	
	
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_Z_DARK, m_clColorButtonPcbZDarkPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_Z_DEFECT, m_clColorButtonPcbZDefectPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_Z_ESCAPE, m_clColorButtonPcbZEscapePos);

	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_Z_HOLDER_ALIGN, m_clColorButtonPcbZHolderAlignPos);
	
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_Z_DISPENSE, m_clColorButtonPcbZDispensePos);

	DDX_Control(pDX, IDC_BUTTON_MANUAL_EOL_ALIGN, m_clColorButtonPcbEolAlignPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_Z_EOL_ALIGN, m_clColorButtonPcbZEolAlignPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_LASER_LOAD, m_clColorButtonPcbLaserPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_Z_LASER_LOAD, m_clColorButtonPcbZLaserPos);

	DDX_Control(pDX, IDC_BUTTON_MANUAL_LENS_WAIT, m_clColorButtonLensWaitPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LENS_LOAD, m_clColorButtonLensLoadPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LENS_BONDING, m_clColorButtonLensBondingPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LENS_Z_WAIT, m_clColorButtonLensZWaitPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LENS_Z_LOAD, m_clColorButtonLensZLoadPos);
	//DDX_Control(pDX, IDC_BUTTON_MANUAL_LENS_Z_LOAD2, m_clColorButtonLensZLoadPos2);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_LENS_Z_BONDING, m_clColorButtonLensZBondingPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_UNLOAD, m_clColorButtonUnLoadPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_Z_UNLOAD, m_clColorButtonZUnLoadPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_UV_SHUTTER_OPEN, m_clColorButtonUVShutterOpen);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_UV_SHUTTER_CLOSE, m_clColorButtonUVShutterClose);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_UV_READY_CHECK, m_clColorButtonUVReadyCheck);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_UV_ALARM_CHECK, m_clColorButtonUVAlarmCheck);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_UV_TIME_CHECK, m_clColorButtonUVTimeCheck);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_ALIGN, m_clColorButtonAlign);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_ALIGN_MOVE, m_clColorButtonAlignMove);
	
	
	
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_GRIP_UP, m_clColorButtonPcbGripUp);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_GRIP_DOWN, m_clColorButtonPcbGripDown);

	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_SOCKET_LOAD, m_clColorButtonPcbAutoLoad);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_PCB_SOCKET_UNLOAD, m_clColorButtonPcbAutoUnLoad);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_BARCODE, m_clColorButtonPcbBCRReq);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_EPOXY_INSP, m_clColorButtonEpoxyInsp);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_EOL_CHART, m_clColorButtonPcbEolChartPos);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_Z_EOL_CHART, m_clColorButtonPcbZEolChartPos);
	DDX_Control(pDX, IDC_BUTTON_CURTAIN_SENSOR, m_clColorButtonCurtainCheck);
	DDX_Control(pDX, IDC_BUTTON_LENS_BUFFER_SENSOR, m_clColorButtonLensBufferCheck);
	DDX_Control(pDX, IDC_BUTTON_LENS_BUFFER_VACUUM_ON, m_clColorButtonLensBufferVacuumOn);
	DDX_Control(pDX, IDC_BUTTON_LENS_BUFFER_VACUUM_OFF, m_clColorButtonLensBufferVacuumOff);
	
	
}


BEGIN_MESSAGE_MAP(CManualDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_VACUUM_ON, &CManualDlg::OnBnClickedButtonManualPcbVacuumOn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_VACUUM_OFF, &CManualDlg::OnBnClickedButtonManualPcbVacuumOff)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_GRIP_FOR, &CManualDlg::OnBnClickedButtonManualPcbGripFor)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_GRIP_BACK, &CManualDlg::OnBnClickedButtonManualPcbGripBack)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_DARK_UP, &CManualDlg::OnBnClickedButtonManualPcbDarkUp)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_DARK_DOWN, &CManualDlg::OnBnClickedButtonManualPcbDarkDown)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_OC_FOR, &CManualDlg::OnBnClickedButtonManualPcbOcFor)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_OC_BACK, &CManualDlg::OnBnClickedButtonManualPcbOcBack)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LENS_GRIP_FOR, &CManualDlg::OnBnClickedButtonManualLensGripFor)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LENS_GRIP_BACK, &CManualDlg::OnBnClickedButtonManualLensGripBack)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LENS_CENT_FOR, &CManualDlg::OnBnClickedButtonManualLensCentFor)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LENS_CENT_BACK, &CManualDlg::OnBnClickedButtonManualLensCentBack)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_UV_ON, &CManualDlg::OnBnClickedButtonManualUvOn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_UV_OFF, &CManualDlg::OnBnClickedButtonManualUvOff)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_WAIT, &CManualDlg::OnBnClickedButtonManualPcbWait)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_Z_WAIT, &CManualDlg::OnBnClickedButtonManualPcbZWait)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_ALIGN, &CManualDlg::OnBnClickedButtonManualPcbAlign)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_Z_ALIGN, &CManualDlg::OnBnClickedButtonManualPcbZAlign)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_LASER_IN, &CManualDlg::OnBnClickedButtonManualPcbLaserIn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_LASER_OUT, &CManualDlg::OnBnClickedButtonManualPcbLaserOut)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_Z_LASER_IN, &CManualDlg::OnBnClickedButtonManualPcbZLaserIn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_Z_LASER_OUT, &CManualDlg::OnBnClickedButtonManualPcbZLaserOut)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_LOAD, &CManualDlg::OnBnClickedButtonManualPcbLoad)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_Z_LOAD, &CManualDlg::OnBnClickedButtonManualPcbZLoad)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_BONDING, &CManualDlg::OnBnClickedButtonManualPcbBonding)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_Z_BONDING, &CManualDlg::OnBnClickedButtonManualPcbZBonding)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_DARK, &CManualDlg::OnBnClickedButtonManualPcbDark)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_Z_DARK, &CManualDlg::OnBnClickedButtonManualPcbZDark)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_DEFECT, &CManualDlg::OnBnClickedButtonManualPcbDefect)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_Z_DEFECT, &CManualDlg::OnBnClickedButtonManualPcbZDefect)

	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_Z_ESCAPE, &CManualDlg::OnBnClickedButtonManualPcbZEscape)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_UV_SHUTTER_OPEN, &CManualDlg::OnBnClickedButtonManualUvShutterOpen)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_UV_SHUTTER_CLOSE, &CManualDlg::OnBnClickedButtonManualUvShutterClose)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_ALIGN, &CManualDlg::OnBnClickedButtonManualAlign)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_ALIGN_MOVE, &CManualDlg::OnBnClickedButtonManualAlignMove)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LASER_IN_1, &CManualDlg::OnBnClickedButtonManualLaserIn1)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LASER_IN_2, &CManualDlg::OnBnClickedButtonManualLaserIn2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LASER_IN_3, &CManualDlg::OnBnClickedButtonManualLaserIn3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LASER_IN_4, &CManualDlg::OnBnClickedButtonManualLaserIn4)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LASER_DATA_MEAS, &CManualDlg::OnBnClickedButtonManualLaserAutoMeas)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LASER_AUTO, &CManualDlg::OnBnClickedButtonManualLaserAuto)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_OC_2800, &CManualDlg::OnBnClickedButtonManualPcbOc2800)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_OC_Z_2800, &CManualDlg::OnBnClickedButtonManualPcbZDefect2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_LOAD, &CManualDlg::OnBnClickedButtonManualLensLoad)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LENS_Z_LOAD, &CManualDlg::OnBnClickedButtonManualLensZLoad)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_UNLOAD, &CManualDlg::OnBnClickedButtonManualUnload)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_Z_UNLOAD, &CManualDlg::OnBnClickedButtonManualZUnload)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_GRIP_UP, &CManualDlg::OnBnClickedButtonManualPcbGripUp)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_GRIP_DOWN, &CManualDlg::OnBnClickedButtonManualPcbGripDown)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_SOCKET_LOAD, &CManualDlg::OnBnClickedButtonManualPcbSocketLoad)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_BARCODE, &CManualDlg::OnBnClickedButtonManualBarcode)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_SOCKET_UNLOAD, &CManualDlg::OnBnClickedButtonManualPcbSocketUnload)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LENS_WAIT, &CManualDlg::OnBnClickedButtonManualLensWait)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LENS_Z_WAIT, &CManualDlg::OnBnClickedButtonManualLensZWait)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LENS_LOAD, &CManualDlg::OnBnClickedButtonManualLensLoad2)
	//ON_BN_CLICKED(IDC_BUTTON_MANUAL_LENS_Z_LOAD2, &CManualDlg::OnBnClickedButtonManualLensZLoad2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LENS_BONDING, &CManualDlg::OnBnClickedButtonManualLensBonding)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LENS_Z_BONDING, &CManualDlg::OnBnClickedButtonManualLensZBonding)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LENS_GRIP, &CManualDlg::OnBnClickedButtonManualLensGrip)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LENS_UNGRIP, &CManualDlg::OnBnClickedButtonManualLensUngrip)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_EPOXY_ON, &CManualDlg::OnBnClickedButtonManualEpoxyOn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_EPOXY_SET, &CManualDlg::OnBnClickedButtonManualEpoxySet)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_OC_TOTAL, &CManualDlg::OnBnClickedButtonManualPcbOcTotal)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_DISPENSE, &CManualDlg::OnBnClickedButtonManualPcbDispense)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_Z_OC_TOTAL, &CManualDlg::OnBnClickedButtonManualPcbZOcTotal)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_Z_DISPENSE, &CManualDlg::OnBnClickedButtonManualPcbZDispense)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LENS_ALIGN, &CManualDlg::OnBnClickedButtonManualLensAlign)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LENS_Z_ALIGN, &CManualDlg::OnBnClickedButtonManualLensZAlign)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_HOLDER_ALIGN, &CManualDlg::OnBnClickedButtonManualPcbHolderAlign)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_Z_HOLDER_ALIGN, &CManualDlg::OnBnClickedButtonManualPcbZHolderAlign)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_LASER_LOAD, &CManualDlg::OnBnClickedButtonManualPcbLaserLoad)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_EOL_ALIGN, &CManualDlg::OnBnClickedButtonManualEolAlign)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_Z_LASER_LOAD, &CManualDlg::OnBnClickedButtonManualPcbZLaserLoad)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_Z_EOL_ALIGN, &CManualDlg::OnBnClickedButtonManualZEolAlign)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_EPOXY_INSP, &CManualDlg::OnBnClickedButtonManualEpoxyInsp)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_EOL_CHART, &CManualDlg::OnBnClickedButtonManualEolChart)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_Z_EOL_CHART, &CManualDlg::OnBnClickedButtonManualZEolChart)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_EPOXY_ON2, &CManualDlg::OnBnClickedButtonManualEpoxyOn2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_EPOXY_SET2, &CManualDlg::OnBnClickedButtonManualEpoxySet2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_SOCKET_UP, &CManualDlg::OnBnClickedButtonManualPcbSocketUp)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_SOCKET_DOWN, &CManualDlg::OnBnClickedButtonManualPcbSocketDown)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_UNLOAD, &CManualDlg::OnBnClickedButtonManualPcbUnload)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_PCB_Z_UNLOAD, &CManualDlg::OnBnClickedButtonManualPcbZUnload)
	ON_BN_CLICKED(IDC_BUTTON_LENS_BUFFER_VACUUM_ON, &CManualDlg::OnBnClickedButtonLensBufferVacuumSensor)
	ON_BN_CLICKED(IDC_BUTTON_LENS_BUFFER_VACUUM_OFF, &CManualDlg::OnBnClickedButtonLensBufferVacuumOff)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_LASER_IN_Z, &CManualDlg::OnBnClickedButtonManualLaserInZ)
END_MESSAGE_MAP()


// CManualDlg 메시지 처리기입니다.

//-----------------------------------------------------------------------------
//
//	OnPaint
//
//-----------------------------------------------------------------------------
void CManualDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	GetClientRect(rect);

	dc.FillSolidRect(rect, RGB_DLG_BG);
}

//-----------------------------------------------------------------------------
//
//	다이얼로그 초기화
//
//-----------------------------------------------------------------------------
BOOL CManualDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	// 컨트롤 초기화
	this->InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//-----------------------------------------------------------------------------
//
//	컨트롤 초기화
//
//-----------------------------------------------------------------------------
void CManualDlg::InitCtrl()
{
	CButton* pButton;
	WINDOWPLACEMENT wndpl;


	// 폰트 생성
	m_clFontSmall.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontMid.CreateFont(20, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
	m_clFontBig.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));

	SetWindowTheme(GetDlgItem(IDC_RADIO_MANUAL_LASER_1)->m_hWnd, L"", L"");
	SetWindowTheme(GetDlgItem(IDC_RADIO_MANUAL_LASER_2)->m_hWnd, L"", L"");

	m_clColorStaticTitle.SetBkColor(RGB_CTRL_BG);
	m_clColorStaticTitle.SetTextColor(RGB_COLOR_WHITE);
    m_clColorStaticTitle.SetFont(&m_clFontBig);
    m_clColorStaticTitle.SetFontBold(TRUE);
    m_clColorStaticTitle.SetBorder(FALSE);
    m_clColorStaticTitle.SetFontSize(15);

	//m_clColorStaticTitlePCB.SetBkColor(RGB_COLOR_WHITE);
	//m_clColorStaticTitlePCB.SetTextColor(RGB_CTRL_BG);
	//m_clColorStaticTitlePCB.SetFont(&m_clFontMid);
    m_clColorStaticTitlePCB.SetFontBold(TRUE).SetBkColor(RGB_COLOR_WHITE);

	m_clColorStaticTitleLENS.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticTitleLENS.SetTextColor(RGB_CTRL_BG);
	m_clColorStaticTitleLENS.SetFont(&m_clFontMid);

    m_clColorStaticTitlePcbIO.SetFontBold(TRUE).SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticTitlePcbIO_IN.SetFontBold(TRUE).SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticTitleUvIO.SetFontBold(TRUE).SetBkColor(RGB_COLOR_WHITE);
    m_clColorStaticTitleLaser.SetFontBold(TRUE).SetBkColor(RGB_COLOR_WHITE);

	m_clColorStaticTitleLensPos.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticTitleLensPos.SetTextColor(RGB_CTRL_BG);
	m_clColorStaticTitleLensPos.SetFont(&m_clFontMid);

	m_clColorStaticTitleLensPosZ.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticTitleLensPosZ.SetTextColor(RGB_CTRL_BG);
	m_clColorStaticTitleLensPosZ.SetFont(&m_clFontMid);

	/*m_clColorStaticTitleUvIO.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticTitleUvIO.SetTextColor(RGB_CTRL_BG);
	m_clColorStaticTitleUvIO.SetFont(&m_clFontMid);*/

	m_clColorStaticAlignX.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticAlignX.SetTextColor(RGB_COLOR_BLACK);
	m_clColorStaticAlignX.SetFont(&m_clFontSmall);

	m_clColorStaticAlignY.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticAlignY.SetTextColor(RGB_COLOR_BLACK);
	m_clColorStaticAlignY.SetFont(&m_clFontSmall);

	m_clColorStaticAlignTH.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticAlignTH.SetTextColor(RGB_COLOR_BLACK);
	m_clColorStaticAlignTH.SetFont(&m_clFontSmall);

	m_clColorStaticAlignXVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticAlignXVal.SetTextColor(RGB_COLOR_BLACK);
	m_clColorStaticAlignXVal.SetFont(&m_clFontSmall);

	m_clColorStaticAlignYVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticAlignYVal.SetTextColor(RGB_COLOR_BLACK);
	m_clColorStaticAlignYVal.SetFont(&m_clFontSmall);

	m_clColorStaticAlignTHVal.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticAlignTHVal.SetTextColor(RGB_COLOR_BLACK);
	m_clColorStaticAlignTHVal.SetFont(&m_clFontSmall);

	m_clColorStaticBcrText.SetBkColor(RGB_COLOR_WHITE);
	m_clColorStaticBcrText.SetTextColor(RGB_COLOR_BLACK);
	m_clColorStaticBcrText.SetFont(&m_clFontSmall);

	pButton = (CButton*)GetDlgItem(IDC_RADIO_MANUAL_LASER_1);
	pButton->SetCheck(1);

	//g_clDioControl.PcbVacuum(UNIT_AA1, false, false);
	//g_clDioControl.PcbVacuum(UNIT_AA2, false, false); 

	GetDlgItem(IDC_BUTTON_MANUAL_PCB_ALIGN)->GetWindowPlacement(&wndpl);
	clButtonPos[0].x = wndpl.rcNormalPosition.left;
	clButtonPos[0].y = wndpl.rcNormalPosition.top;

	GetDlgItem(IDC_BUTTON_MANUAL_PCB_LASER_OUT)->GetWindowPlacement(&wndpl);
	clButtonPos[1].x = wndpl.rcNormalPosition.left;
	clButtonPos[1].y = wndpl.rcNormalPosition.top;

	GetDlgItem(IDC_BUTTON_MANUAL_PCB_BONDING)->GetWindowPlacement(&wndpl);
	clButtonPos[2].x = wndpl.rcNormalPosition.left;
	clButtonPos[2].y = wndpl.rcNormalPosition.top;

	GetDlgItem(IDC_BUTTON_MANUAL_PCB_LOAD)->GetWindowPlacement(&wndpl);
	clButtonPos[3].x = wndpl.rcNormalPosition.left;
	clButtonPos[3].y = wndpl.rcNormalPosition.top;

	GetDlgItem(IDC_BUTTON_MANUAL_UNLOAD)->GetWindowPlacement(&wndpl);
	clButtonPos[4].x = wndpl.rcNormalPosition.left;
	clButtonPos[4].y = wndpl.rcNormalPosition.top;

	GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_ALIGN)->GetWindowPlacement(&wndpl);
	clButtonZPos[0].x = wndpl.rcNormalPosition.left;
	clButtonZPos[0].y = wndpl.rcNormalPosition.top;

	GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_LASER_OUT)->GetWindowPlacement(&wndpl);
	clButtonZPos[1].x = wndpl.rcNormalPosition.left;
	clButtonZPos[1].y = wndpl.rcNormalPosition.top;

	GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_BONDING)->GetWindowPlacement(&wndpl);
	clButtonZPos[2].x = wndpl.rcNormalPosition.left;
	clButtonZPos[2].y = wndpl.rcNormalPosition.top;

	GetDlgItem(IDC_BUTTON_MANUAL_LENS_Z_LOAD)->GetWindowPlacement(&wndpl);
	clButtonZPos[3].x = wndpl.rcNormalPosition.left;
	clButtonZPos[3].y = wndpl.rcNormalPosition.top;

	GetDlgItem(IDC_BUTTON_MANUAL_Z_UNLOAD)->GetWindowPlacement(&wndpl);
	clButtonZPos[4].x = wndpl.rcNormalPosition.left;
	clButtonZPos[4].y = wndpl.rcNormalPosition.top;



	//m_clMarkViewDlg.Create(IDD_DIALOG_CCD_MARK_VIEW, this);
	////m_clMarkViewDlg.SetWindowPos(NULL, wndpl.rcNormalPosition.right - 60, wndpl.rcNormalPosition.bottom + 10, 0, 0, SWP_NOSIZE);
	//m_clMarkViewDlg.SetWindowPos(NULL, 30, 720, 0, 0, SWP_NOSIZE);

	//m_clMarkViewDlg.ShowWindow(SW_SHOW);
	m_clEpoxySetDlg.Create(IDD_DIALOG_EPOXY, this);
	m_clEpoxySetDlg.ShowWindow(SW_HIDE);

	
	int PcbTitleWidth = 0;
	//GetDlgItem(IDC_BUTTON_MANUAL_PCB_WAIT)->GetWindowPlacement(&wndpl);
	//PcbTitleWidth = wndpl.rcNormalPosition.right - wndpl.rcNormalPosition.left;
	//GetDlgItem(IDC_STATIC_MANUAL_PCB)->GetWindowPlacement(&wndpl);
	//GetDlgItem(IDC_STATIC_MANUAL_PCB)->SetWindowPos(&CWnd::wndTop, wndpl.rcNormalPosition.left, wndpl.rcNormalPosition.top, PcbTitleWidth, wndpl.rcNormalPosition.bottom - wndpl.rcNormalPosition.top, SWP_SHOWWINDOW);

	GetDlgItem(IDC_BUTTON_MANUAL_PCB_CHECK)->GetWindowPlacement(&wndpl);
	PcbTitleWidth = wndpl.rcNormalPosition.right - wndpl.rcNormalPosition.left;
	//GetDlgItem(IDC_STATIC_MANUAL_PCB_IO_IN)->GetWindowPlacement(&wndpl);
	//GetDlgItem(IDC_STATIC_MANUAL_PCB_IO_IN)->SetWindowPos(&CWnd::wndTop, wndpl.rcNormalPosition.left, wndpl.rcNormalPosition.top, PcbTitleWidth, wndpl.rcNormalPosition.bottom - wndpl.rcNormalPosition.top, SWP_SHOWWINDOW);

	
	wndpl.rcNormalPosition.right = 591;
	wndpl.rcNormalPosition.bottom = 746;

	m_clMarkViewDlg.Create(IDD_DIALOG_CCD_MARK_VIEW, this);
	//m_clMarkViewDlg.SetWindowPos(NULL, wndpl.rcNormalPosition.right - 60, wndpl.rcNormalPosition.bottom + 10, 0, 0, SWP_NOSIZE);
	m_clMarkViewDlg.SetWindowPos(NULL, 20, 700, 0, 0, SWP_NOSIZE);
	m_clMarkViewDlg.ShowWindow(SW_SHOW);

	m_clColorButtonPcbSocketUp.ShowWindow(SW_HIDE);
	m_clColorButtonPcbSocketDown.ShowWindow(SW_HIDE);
	m_clColorButtonPcbGripFor.ShowWindow(SW_HIDE);
	m_clColorButtonPcbGripBack.ShowWindow(SW_HIDE);
	
	m_clColorButtonLensGripFor.ShowWindow(SW_HIDE);
	m_clColorButtonLensGripBack.ShowWindow(SW_HIDE);
	
	m_clColorStaticTitleLENS.ShowWindow(SW_HIDE);
	m_clColorButtonLensBufferCheck.ShowWindow(SW_HIDE);
	m_clColorButtonLensBufferVacuumOn.ShowWindow(SW_HIDE);
	m_clColorButtonLensBufferVacuumOff.ShowWindow(SW_HIDE);
	m_clColorStaticTitleUvIO.ShowWindow(SW_HIDE);
	m_clColorButtonUVShutterOpen.ShowWindow(SW_HIDE);
	m_clColorButtonUVShutterClose.ShowWindow(SW_HIDE);
	
	m_clColorButtonLensWaitPos.ShowWindow(SW_HIDE);
	m_clColorButtonLensLoadPos.ShowWindow(SW_HIDE);
	m_clColorButtonLensBondingPos.ShowWindow(SW_HIDE);
	m_clColorButtonLensZWaitPos.ShowWindow(SW_HIDE);
	m_clColorButtonLensZLoadPos.ShowWindow(SW_HIDE);
	m_clColorButtonLensZBondingPos.ShowWindow(SW_HIDE);

	//

	
	//if(g_clModelData[m_nUnit].m_nDomeChartUse == 1)
		//m_clMarkViewDlg.ShowWindow(SW_SHOW);
	//else
		//m_clMarkViewDlg.ShowWindow(SW_HIDE);
}

//-----------------------------------------------------------------------------
//
//	유닛 설정
//
//-----------------------------------------------------------------------------
void CManualDlg::SetUnit(int nUnit)
{
	TCHAR szTitle[SIZE_OF_100BYTE];
	m_nUnit = nUnit;

	_stprintf_s(szTitle, SIZE_OF_100BYTE, _T("[MANUAL]")); //, m_nUnit + 1);

	GetDlgItem(IDC_STATIC_MANUAL_TITLE)->SetWindowText(szTitle);

}
void CManualDlg::SetUnitUI(int nUnit)
{
	//GetDlgItem(IDC_STATIC_1)->ShowWindow(true);
	//GetDlgItem(IDC_STATIC_2)->ShowWindow(true);

	GetDlgItem(IDC_STATIC_MANUAL_ALIGN_X)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_MANUAL_ALIGN_X_VAL)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_MANUAL_ALIGN_Y)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_MANUAL_ALIGN_Y_VAL)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_MANUAL_ALIGN_THETA)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_MANUAL_ALIGN_THETA_VAL)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_MANUAL_ALIGN)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_MANUAL_ALIGN_MOVE)->ShowWindow(true);
	//GetDlgItem(IDC_BUTTON_MANUAL_BARCODE)->ShowWindow(true);
	//GetDlgItem(IDC_STATIC_MANUAL_BCR_TEXT)->ShowWindow(true);

	GetDlgItem(IDC_BUTTON_MANUAL_PCB_ALIGN)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_MANUAL_PCB_LASER_OUT)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_MANUAL_PCB_DARK)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_MANUAL_PCB_DEFECT)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_MANUAL_PCB_OC_2800)->ShowWindow(true);

	GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_ALIGN)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_LASER_OUT)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_DARK)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_DEFECT)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON_MANUAL_PCB_OC_Z_2800)->ShowWindow(true);

	GetDlgItem(IDC_BUTTON_MANUAL_PCB_BONDING)->SetWindowPos(NULL, clButtonPos[2].x, clButtonPos[2].y, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_BUTTON_MANUAL_PCB_LOAD)->SetWindowPos(NULL, clButtonPos[3].x, clButtonPos[3].y, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_BUTTON_MANUAL_UNLOAD)->SetWindowPos(NULL, clButtonPos[4].x, clButtonPos[4].y, 0, 0, SWP_NOSIZE);

	GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_BONDING)->SetWindowPos(NULL, clButtonZPos[2].x, clButtonZPos[2].y, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_BUTTON_MANUAL_LENS_Z_LOAD)->SetWindowPos(NULL, clButtonZPos[3].x, clButtonZPos[3].y, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_BUTTON_MANUAL_Z_UNLOAD)->SetWindowPos(NULL, clButtonZPos[4].x, clButtonZPos[4].y, 0, 0, SWP_NOSIZE);

	return;

	if (nUnit == 0)
	{
		//GetDlgItem(IDC_STATIC_1)->ShowWindow(true);
		//GetDlgItem(IDC_STATIC_2)->ShowWindow(true);

		GetDlgItem(IDC_STATIC_MANUAL_ALIGN_X)->ShowWindow(true);
		GetDlgItem(IDC_STATIC_MANUAL_ALIGN_X_VAL)->ShowWindow(true);
		GetDlgItem(IDC_STATIC_MANUAL_ALIGN_Y)->ShowWindow(true);
		GetDlgItem(IDC_STATIC_MANUAL_ALIGN_Y_VAL)->ShowWindow(true);
		GetDlgItem(IDC_STATIC_MANUAL_ALIGN_THETA)->ShowWindow(true);
		GetDlgItem(IDC_STATIC_MANUAL_ALIGN_THETA_VAL)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON_MANUAL_ALIGN)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON_MANUAL_ALIGN_MOVE)->ShowWindow(true);
		//GetDlgItem(IDC_BUTTON_MANUAL_BARCODE)->ShowWindow(true);
		//GetDlgItem(IDC_STATIC_MANUAL_BCR_TEXT)->ShowWindow(true);

		GetDlgItem(IDC_BUTTON_MANUAL_PCB_ALIGN)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_LASER_OUT)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_DARK)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_DEFECT)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_OC_2800)->ShowWindow(true);

		GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_ALIGN)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_LASER_OUT)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_DARK)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_DEFECT)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_OC_Z_2800)->ShowWindow(true);

		GetDlgItem(IDC_BUTTON_MANUAL_PCB_BONDING)->SetWindowPos(NULL, clButtonPos[2].x, clButtonPos[2].y, 0, 0, SWP_NOSIZE);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_LOAD)->SetWindowPos(NULL, clButtonPos[3].x, clButtonPos[3].y, 0, 0, SWP_NOSIZE);
		GetDlgItem(IDC_BUTTON_MANUAL_UNLOAD)->SetWindowPos(NULL, clButtonPos[4].x, clButtonPos[4].y, 0, 0, SWP_NOSIZE);

		GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_BONDING)->SetWindowPos(NULL, clButtonZPos[2].x, clButtonZPos[2].y, 0, 0, SWP_NOSIZE);
		GetDlgItem(IDC_BUTTON_MANUAL_LENS_Z_LOAD)->SetWindowPos(NULL, clButtonZPos[3].x, clButtonZPos[3].y, 0, 0, SWP_NOSIZE);
		GetDlgItem(IDC_BUTTON_MANUAL_Z_UNLOAD)->SetWindowPos(NULL, clButtonZPos[4].x, clButtonZPos[4].y, 0, 0, SWP_NOSIZE);
	}
	else
	{
		//GetDlgItem(IDC_STATIC_1)->ShowWindow(false);
		//GetDlgItem(IDC_STATIC_2)->ShowWindow(false);

		GetDlgItem(IDC_STATIC_MANUAL_ALIGN_X)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_MANUAL_ALIGN_X_VAL)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_MANUAL_ALIGN_Y)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_MANUAL_ALIGN_Y_VAL)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_MANUAL_ALIGN_THETA)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_MANUAL_ALIGN_THETA_VAL)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_MANUAL_ALIGN)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_MANUAL_ALIGN_MOVE)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_MANUAL_BARCODE)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_MANUAL_BCR_TEXT)->ShowWindow(false);

		GetDlgItem(IDC_BUTTON_MANUAL_PCB_ALIGN)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_LASER_OUT)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_DARK)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_DEFECT)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_OC_2800)->ShowWindow(false);

		GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_ALIGN)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_LASER_OUT)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_DARK)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_DEFECT)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_OC_Z_2800)->ShowWindow(false);

		GetDlgItem(IDC_BUTTON_MANUAL_PCB_BONDING)->SetWindowPos(NULL, clButtonPos[0].x, clButtonPos[0].y, 0, 0, SWP_NOSIZE);
		GetDlgItem(IDC_BUTTON_MANUAL_PCB_LOAD)->SetWindowPos(NULL, clButtonPos[1].x, clButtonPos[1].y, 0, 0, SWP_NOSIZE);
		GetDlgItem(IDC_BUTTON_MANUAL_UNLOAD)->SetWindowPos(NULL, clButtonPos[2].x, clButtonPos[2].y, 0, 0, SWP_NOSIZE);

		GetDlgItem(IDC_BUTTON_MANUAL_PCB_Z_BONDING)->SetWindowPos(NULL, clButtonZPos[0].x, clButtonZPos[0].y, 0, 0, SWP_NOSIZE);
		GetDlgItem(IDC_BUTTON_MANUAL_LENS_Z_LOAD)->SetWindowPos(NULL, clButtonZPos[1].x, clButtonZPos[1].y, 0, 0, SWP_NOSIZE);
		GetDlgItem(IDC_BUTTON_MANUAL_Z_UNLOAD)->SetWindowPos(NULL, clButtonZPos[2].x, clButtonZPos[2].y, 0, 0, SWP_NOSIZE);

	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB Vacuum On
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbVacuumOn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	//if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	//{
	//	AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
	//	return;
	//}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}
	g_clDioControl.PcbVacuum(m_nUnit, true);

	
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB Vacuum Off
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbVacuumOff()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	//if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	//{
	//	AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
	//	return;
	//}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	g_clDioControl.PcbVacuum(m_nUnit, false);

}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB Grip 전진
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbGripFor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}
	/*if (g_clDioControl.PcbSocketUpCheck(m_nUnit, false) == false)
	{
		AddLog(_T("Socket 하강 상태가 아닙니다."), 1, m_nUnit);
		g_ShowMsgPopup(_T("확인"), _T("Socket 하강 상태 확인 실패."), RGB_COLOR_RED);
		return;
	}
	if (g_clDioControl.ContactUpcheck(m_nUnit, false) == false)
	{
		AddLog(_T("CONTACT 하강 상태가 아닙니다."), 1, m_nUnit);
		g_ShowMsgPopup(_T("확인"), _T("CONTACT 하강 상태 확인 실패."), RGB_COLOR_RED);
		return;
	}*/
	/*if (g_clDioControl.EziOcUpCheck(m_nUnit, true) == false)
	{
		AddLog(_T("이물광원 상승 상태가 아닙니다."), 0, m_nUnit);
		g_ShowMsgPopup(_T("확인"), _T("이물광원 상승 상태 확인 실패."), RGB_COLOR_RED);
		return;
	}*/
	TCHAR szLog[SIZE_OF_1K];
	_stprintf_s(szLog, SIZE_OF_1K, _T("	[MANUAL] PCB SOCKET 전진"));
	AddLog(szLog, 0, m_nUnit);

	//g_clDioControl.EziPcbSocketFor(m_nUnit, true);
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB Grip 후진
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbGripBack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();


	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}
	/*if (g_clDioControl.PcbSocketUpCheck(m_nUnit, false) == false)
	{
		AddLog(_T("Socket 하강 상태가 아닙니다."), 1, m_nUnit);
		g_ShowMsgPopup(_T("확인"), _T("Socket 하강 상태 확인 실패."), RGB_COLOR_RED);
		return;
	}
	if (g_clDioControl.ContactUpcheck(m_nUnit, false) == false)
	{
		AddLog(_T("CONTACT 하강 상태가 아닙니다."), 1, m_nUnit);
		g_ShowMsgPopup(_T("확인"), _T("CONTACT 하강 상태 확인 실패."), RGB_COLOR_RED);
		return;
	}*/
	/*if (g_clDioControl.EziOcUpCheck(m_nUnit, true) == false)
	{
		AddLog(_T("이물광원 상승 상태가 아닙니다."), 0, m_nUnit);
		g_ShowMsgPopup(_T("확인"), _T("이물광원 상승 상태 확인 실패."), RGB_COLOR_RED);
		return;
	}
	TCHAR szLog[SIZE_OF_1K];
	_stprintf_s(szLog, SIZE_OF_1K, _T("	[MANUAL] PCB SOCKET 후진"));
	AddLog(szLog, 0, m_nUnit);

	g_clDioControl.EziPcbSocketFor(m_nUnit, false);*/

}

//-----------------------------------------------------------------------------
//
//	버튼 : Dark Pusher 상승
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbDarkUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	g_clDioControl.DarkPusher(m_nUnit, true);
}

//-----------------------------------------------------------------------------
//
//	버튼 : Dark Pusher 하강
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbDarkDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	g_clDioControl.DarkPusher(m_nUnit, false);
}

//-----------------------------------------------------------------------------
//
//	버튼 : OC 실린더 전진
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbOcFor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}
	TCHAR szLog[SIZE_OF_1K];

	_stprintf_s(szLog, SIZE_OF_1K, _T("	[MANUAL] OC 전진"));
	g_clDioControl.ContactUp(m_nUnit, true); 
	
	
	
	AddLog(szLog, 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	버튼 : OC 실린더 후진
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbOcBack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}
	TCHAR szLog[SIZE_OF_1K];

	_stprintf_s(szLog, SIZE_OF_1K, _T("	[MANUAL] OC 상승"));
	g_clDioControl.ContactUp(m_nUnit, false);
	AddLog(szLog, 0, m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	버튼 : Lens Grip 전진
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualLensGripFor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}
	TCHAR szLog[SIZE_OF_1K];
	_stprintf_s(szLog, SIZE_OF_1K, _T("	[MANUAL] LENS GRIP"));
	AddLog(szLog, 0, m_nUnit);
	g_clDioControl.LensGrip(m_nUnit, true);


	g_clTaskWork[m_nUnit].m_nLensLoading = 1;
	g_pCarAABonderDlg->LensLoadingChange(m_nUnit); 
}

//-----------------------------------------------------------------------------
//
//	버튼 : Lens Grip 후진
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualLensGripBack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	TCHAR szLog[SIZE_OF_1K];
	_stprintf_s(szLog, SIZE_OF_1K, _T("	[MANUAL] LENS UNGRIP"));
	AddLog(szLog, 0, m_nUnit);

	g_clDioControl.LensGrip(m_nUnit, false);

	g_clTaskWork[UNIT_AA1].m_nLensLoading = 0;
	g_pCarAABonderDlg->m_clColorButtonLensLoading[UNIT_AA1].SetWindowTextA(_T("LENS 넘김 미완료"));
	g_pCarAABonderDlg->m_clColorButtonLensLoading[UNIT_AA1].state = 0;
	g_pCarAABonderDlg->m_clColorButtonLensLoading[UNIT_AA1].Invalidate();
}

//-----------------------------------------------------------------------------
//
//	버튼 : Lens Centering 전진
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualLensCentFor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	g_clDioControl.LensStageGrip(m_nUnit, true, true);
}

//-----------------------------------------------------------------------------
//
//	버튼 : Lens Centering 후진
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualLensCentBack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	g_clDioControl.LensStageGrip(m_nUnit, false, true);
}

//-----------------------------------------------------------------------------
//
//	버튼 : UV ON
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualUvOn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].ChangeColor(3);
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	g_clDioControl.UVOn(m_nUnit, true, true);
	*/
}

//-----------------------------------------------------------------------------
//
//	버튼 : UV OFF
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualUvOff()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	g_clDioControl.UVOn(m_nUnit, false, true);
}

//-----------------------------------------------------------------------------
//
//	버튼 : UV SHUTTER OPEN
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualUvShutterOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	/*if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}*/

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}
	//g_pCarAABonderDlg->m_clSerialThread.UV_Shutter_Open(m_nUnit);

	g_clDioControl.UVOn(m_nUnit, true);
}

//-----------------------------------------------------------------------------
//
//	버튼 : UV SHUTTER CLOSE
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualUvShutterClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}
	g_clDioControl.UVOn(m_nUnit, false);
	//g_pCarAABonderDlg->m_clSerialThread.UV_Shutter_Close(m_nUnit);
}


//-----------------------------------------------------------------------------
//
//	버튼 : PCB 5축 대기위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbWait()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{		
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//소켓 흡착 상태 확인  Laser
	{
		AddLog(_T("[INFO] PCB Vacuum 확인 실패"), 1, m_nUnit, true);

		return;
	}


	//if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	//{
	//	AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
	//	return;
	//}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// LENS Z축 대기위치 이동
		case 100:

			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// PCB Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 250;
			break;
		case 250:
			if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, WAIT_POS, 0.0, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//PCB X,Y,T축 이동
		case 300:

			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, WAIT_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if(nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}
		
		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 대기위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 대기위치 이동 완료"), 0, m_nUnit);
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB Z축 대기위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbZWait()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	/*if (g_clMotorSet.GetPcbXYMotorPosCheck(m_nUnit, WAIT_POS) == false)
	{
		AddLog(_T("PCB X,Y 대기위치가 아닙니다."), 1, m_nUnit);

		return;
	}
*/
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 대기위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 대기위치 이동 완료"), 0, m_nUnit);
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB 5축 Align위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbAlign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{		
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}
	if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//소켓 흡착 상태 확인  Laser
	{
		AddLog(_T("[INFO] PCB Vacuum 확인 실패"), 1, m_nUnit, true);

		return;
	}

	/*if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}*/

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// LENS Z축 대기위치 이동
		case 100:

			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// PCB Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//PCB X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, SENSOR_ALIGN_POS, 0.0, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, SENSOR_ALIGN_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if(nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}
		
		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 SENSOR ALIGN위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 SENSOR ALIGN위치 이동 완료"), 0, m_nUnit);
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB Z축 Align위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbZAlign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clMotorSet.GetPcbXYMotorPosCheck(m_nUnit, SENSOR_ALIGN_POS) == false)
	{
		AddLog(_T("PCB X,Y SENSOR ALIGN 위치가 아닙니다."), 1, m_nUnit);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, SENSOR_ALIGN_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 SENSOR ALIGN 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 SENSOR ALIGN 위치 이동 완료"), 0, m_nUnit);
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB 5축 Laser In위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbLaserIn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;
	double dCurYpos = 0.0;
	double dChartYpos = 0.0;
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
		case 100:

			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// LENS Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MoveLensZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 220;
			break;
		case 220:
			//LENS Y 가 차트 위치보다 아래쪽이면 X->
			dCurYpos = g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Y);
			dChartYpos = g_clModelData[m_nUnit].m_stTeachData[CHART_POS].dPos[MOTOR_LENS_Y];

			if (dCurYpos < dChartYpos - 30.0)
			{
				dwTickCount = GetTickCount();
				nStep = 300;
				break;
			}
			//CL LENS 간섭 때문에 대기위치에서 올때 X축 (+ Limit) 쪽으로 최대한 이동후 진행
			if (g_clMotorSet.MoveLensXMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -220;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 240;
			break;
		case 240:
			if (g_clMotorSet.MoveLensYMotor(m_nUnit, LASER_IN_POS, 0.0, true) == false)
			{
				nStep = -240;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//LENS X,Y축 이동
		case 300:
			if (g_clMotorSet.MoveLensXYMotor(m_nUnit, LASER_IN_POS, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// LENS TX,TY축 이동
		case 400:
			if (g_clMotorSet.MoveLensTxTyMotor(m_nUnit, LASER_IN_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if (nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] LENS부 LENS LASER 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] LENS부 LENS LASER 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB Z축 Laser In위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbZLaserIn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clMotorSet.GetLensXYMotorPosCheck(m_nUnit, LASER_IN_POS) == false)
	{
		AddLog(_T("LENS X,Y LASER 위치가 아닙니다."), 1, m_nUnit);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// Lens Z축 이동
		case 100:
			if (g_clMotorSet.MoveLensZMotor(m_nUnit, LASER_IN_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] LENS부 Z축 LASER 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] LENS부 Z축 LASER 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB 5축 Laser Out위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbLaserOut()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{		
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// LENS Z축 대기위치 이동
		case 100:
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// PCB Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//PCB X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbYTMotor(m_nUnit, HOLDER_BCR_POS, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, HOLDER_BCR_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if(nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}
		
		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 BCR 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 BCR 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB Z축 Laser Out위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbZLaserOut()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, HOLDER_BCR_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 BCR 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 BCR 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}


//-----------------------------------------------------------------------------
//
//	버튼 : PCB 5축 공급위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{		
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}
	if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//소켓 흡착 상태 확인  Laser
	{
		AddLog(_T("[INFO] PCB Vacuum 확인 실패"), 1, m_nUnit, true);

		return;
	}
	/*if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}*/

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
		case 100:
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// PCB Z축 대기 위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//PCB X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, SUPPLY_POS, 0.0, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, SUPPLY_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if(nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}
		
		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 공급 위치 이동 실패"), 1, m_nUnit); 
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 공급 위치 이동 완료"), 0, m_nUnit);
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB Z축 공급위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbZLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}
	if (g_clMotorSet.GetPcbXYMotorPosCheck(m_nUnit, SUPPLY_POS) == false)
	{
		AddLog(_T("PCB X,Y SUPPLY_POS 위치가 아닙니다."), 1, m_nUnit);

		return;
	}
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, SUPPLY_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 공급 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 공급 위치 이동 완료"), 0, m_nUnit);
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB 5축 본딩위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbBonding()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{		
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}
	if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//소켓 흡착 상태 확인  Laser
	{
		AddLog(_T("[INFO] PCB Vacuum 확인 실패"), 1, m_nUnit, true);

		return;
	}
	/*if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}
*/
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// LENS Z축 대기위치 이동
		case 100:
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// PCB Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}

			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//PCB X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, CHART_POS, 0.0, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}

			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, CHART_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if(nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}
		
		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 CHART 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 CHART 위치 이동 완료"), 0, m_nUnit);
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB Z축 본딩위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbZBonding()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clMotorSet.GetPcbXYMotorPosCheck(m_nUnit, CHART_POS) == false)
	{
		AddLog(_T("PCB X,Y CHART 위치가 아닙니다."), 1, m_nUnit);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, CHART_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 CHART 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 CHART 위치 이동 완료"), 0, m_nUnit);
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB 5축 Dark 검사위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbDark()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{		
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	/*if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}*/

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// LENS Z축 대기위치 이동
		case 100:
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// PCB Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}

			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//PCB X,Y,T축 이동
		case 300:
			/*if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, DARK_POS, 0.0, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}*/

			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			/*if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, DARK_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}*/
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if(nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}
		
		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 DARK검사 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 DARK검사 위치 이동 완료"), 0, m_nUnit);
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB Z축 Dark 검사위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbZDark()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}
	/*if (g_clMotorSet.GetPcbXYMotorPosCheck(m_nUnit, DARK_POS) == false)
	{
		AddLog(_T("PCB X,Y DARK 위치가 아닙니다."), 1, m_nUnit);

		return;
	}*/
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			/*if (g_clMotorSet.MovePcbZMotor(m_nUnit, DARK_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}*/
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 DARK검사 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 DARK검사 위치 이동 완료"), 0, m_nUnit);
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB 5축 이물 검사위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbDefect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{		
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// LENS Z축 대기위치 이동
		case 100:
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// PCB Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//PCB X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbYTMotor(m_nUnit, OC_6500K_POS, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, OC_6500K_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if(nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}
		
		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 DEFECT검사 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 DEFECT검사 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB Z축 이물 검사위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbZDefect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, OC_6500K_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 DEFECT검사 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 DEFECT검사 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}

//-----------------------------------------------------------------------------
//
//	버튼 : PCB Z축 회피 위치 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualPcbZEscape()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, g_clModelData[m_nUnit].m_dEscapePosPcbZ, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 회피 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 회피 위치 이동 완료"), 0, m_nUnit);
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : ALIGN 요청
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualAlign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//TCHAR szLog[SIZE_OF_1K];
	//TCHAR szData[SIZE_OF_100BYTE];
	//double dPos[MAX_MOTOR_COUNT];
	CString sMsg = _T("");
	//DWORD dwTickCount;
	//int nStep;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[MANUAL] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[MANUAL] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}
	//AA장비는 Y , TH 보정
	//화상장비는 X , Y , TH 보정
	//(UNIT_AA2 + g_clSysData.m_nUnitNo + g_clSysData.m_nSysNo + 1));
	sMsg.Format(_T("#AA%d@PCB_ALR&REQ$"), (m_nUnit + g_clSysData.m_nUnitNo + g_clSysData.m_nSysNo + 1));
	if (g_pCarAABonderDlg->SendDataToAAMain(m_nUnit, sMsg) == true)
	{
		AddLog(_T("[MANUAL] ALIGN 보정값 요청."), 1, m_nUnit);
	}
}

//-----------------------------------------------------------------------------
//
//	버튼 : ALIGN 보정값 이동
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualAlignMove()
{
	TCHAR szLog[SIZE_OF_1K];
	double dOffset[3];
	CString sData = _T("");
	int i;

	for (i = 0; i < 3; i++)
	{
		dOffset[i] = 0.0;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	m_clColorStaticAlignXVal.GetWindowText(sData);
	dOffset[0] = _ttof((TCHAR*)(LPCTSTR)sData);

	m_clColorStaticAlignYVal.GetWindowText(sData);
	dOffset[1] = _ttof((TCHAR*)(LPCTSTR)sData);

	m_clColorStaticAlignTHVal.GetWindowText(sData);
	dOffset[2] = 0.0;// _ttof((TCHAR*)(LPCTSTR)sData);


	if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, dOffset[0], dOffset[1], dOffset[2],true) == true)
	{
		//_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] PCB ALIGN(x:%.03lf, y:%.03lf, th:%.03lf) 보정 이동 완료"), dOffset[0], dOffset[1], dOffset[2]);
		_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] PCB ALIGN(x:%.03lf, y:%.03lf) 보정 이동 완료"), dOffset[0], dOffset[1]);
		AddLog(szLog, 0, m_nUnit);
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] PCB ALIGN(x:%.03lf, y:%.03lf) 보정 이동 실패"), dOffset[0], dOffset[1]);
		AddLog(szLog, 0, m_nUnit);
	}
	g_clTaskWork[m_nUnit].m_dAADataX = 0.0;
	g_clTaskWork[m_nUnit].m_dAADataY = 0.0;
	g_clTaskWork[m_nUnit].m_dAADataTh = 0.0;
	TCHAR szData[SIZE_OF_100BYTE];
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clTaskWork[m_nUnit].m_dAADataX);
	m_clColorStaticAlignXVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clTaskWork[m_nUnit].m_dAADataY);
	m_clColorStaticAlignYVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clTaskWork[m_nUnit].m_dAADataTh);
	m_clColorStaticAlignTHVal.SetWindowText(szData);
	
}

//-----------------------------------------------------------------------------
//
//	버튼 : 내부 - 1
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualLaserIn1()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	DWORD dwTickCount;
	int nStep = 100;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[INFO] 원점 복귀가 완료되지 않았습니다."));
		AddLog(szLog, 1, m_nUnit, true);

		return;
	}

	if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//소켓 흡착 상태 확인  Laser
	{
		AddLog(_T("[INFO] PCB Vacuum 확인 실패"), 1, m_nUnit, true);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	// DARK CAP 하강 상태면 return
#ifdef ON_LINE_DIO
	/*if (g_clDioControl.DarkPusherCheck(m_nUnit, false, false) == true)
	{
		AddLog(_T("[MANUAL] DARK PUSHER 하강 상태입니다."), 1, m_nUnit);
		return;
	}*/
#endif
	g_clTaskWork[m_nUnit].m_nLaserTiltIndex = 0;
	dwTickCount = GetTickCount();

	while (1)
	{
		switch (nStep)
		{
			// LENS Z축 대기위치 이동
		case 100:

			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// LENS Z축 회피위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			// LENS X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, LASER_POS, 0.0, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// LENS TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, LASER_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
			// LENS Z축 이동
		case 500:
			/*if (g_clMotorSet.MovePcbZMotor(m_nUnit, LASER_POS, 0.0, true) == false)
			{
				nStep = -500;
				break;
			}*/
			dwTickCount = GetTickCount();
			nStep = 600;
			break;
			// 측정명령전 딜레이
		case 600:
			if ((GetTickCount() - dwTickCount) > (DWORD)(g_clModelData[m_nUnit].m_dLaserDelay * 1000))
			{
				nStep = 700;
			}
			break;
			// 측정
		case 700:
			//g_pCarAABonderDlg->SendLaserMeasurePacket(m_nUnit);

			nStep = 800;
			break;
		default:
			break;
		}

		if (nStep >= 800)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == true)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] PCB부 LASER POS 1 위치 이동 완료"));
		AddLog(szLog, 0, m_nUnit);
		m_clColorButtonLaserIn1.state = 1;
        m_clColorButtonLaserIn2.state = 0;
		m_clColorButtonLaserIn3.state = 0;
		m_clColorButtonLaserIn4.state = 0;
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] PCB부 LASER POS 1 위치 이동 실패"));
		AddLog(szLog, 1, m_nUnit);

		m_clColorButtonLaserIn1.state = 0;
	}
	m_clColorButtonLaserIn1.Invalidate();
	m_clColorButtonLaserIn2.Invalidate();
	m_clColorButtonLaserIn3.Invalidate();
	m_clColorButtonLaserIn4.Invalidate();
}

//-----------------------------------------------------------------------------
//
//	버튼 : 내부 - 2
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualLaserIn2()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	DWORD dwTickCount;
	int nStep = 100;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[INFO] 원점 복귀가 완료되지 않았습니다."));
		AddLog(szLog, 1, m_nUnit, true);

		return;
	}

	if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//소켓 흡착 상태 확인  Laser
	{
		AddLog(_T("[INFO] PCB Vacuum 확인 실패"), 1, m_nUnit, true);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	// DARK CAP 하강 상태면 상승
#ifdef ON_LINE_DIO
	/*if (g_clDioControl.DarkPusherCheck(m_nUnit, false, false) == true)
	{
		AddLog(_T("[MANUAL] DARK PUSHER 하강 상태입니다."), 1, m_nUnit);
		return;
	}*/
#endif
	g_clTaskWork[m_nUnit].m_nLaserTiltIndex = 0;
	dwTickCount = GetTickCount();

	while (1)
	{
		switch (nStep)
		{
			// LENS Z 축 대기위치
		case 100:
			
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// PCB Z축 회피위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			// PCB X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, LASER_POS, (g_clModelData[m_nUnit].m_dLaserMoveX[0] * -1), 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, LASER_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
			// PCB Z축 이동
		case 500:
			/*if (g_clMotorSet.MovePcbZMotor(m_nUnit, LASER_POS, 0.0, true) == false)
			{
				nStep = -500;
				break;
			}*/
			dwTickCount = GetTickCount();
			nStep = 600;
			break;
			// 측정 전 딜레이
		case 600:
			if ((GetTickCount() - dwTickCount) > (DWORD)(g_clModelData[m_nUnit].m_dLaserDelay * 1000))
			{
				nStep = 700;
			}
			break;
			// 측정
		case 700:
			//g_pCarAABonderDlg->SendLaserMeasurePacket(m_nUnit);

			nStep = 800;
			break;
		default:
			break;
		}

		if (nStep >= 800)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == true)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] PCB부 LASER POS 2 위치 이동 완료"));
		AddLog(szLog, 0, m_nUnit);

		m_clColorButtonLaserIn1.state = 0;
		m_clColorButtonLaserIn2.state = 1;
		m_clColorButtonLaserIn3.state = 0;
		m_clColorButtonLaserIn4.state = 0;
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] PCB부 LASER POS 2 위치 이동 실패"));
		AddLog(szLog, 1, m_nUnit);
		m_clColorButtonLaserIn2.state = 0;
	}
	m_clColorButtonLaserIn1.Invalidate();
	m_clColorButtonLaserIn2.Invalidate();
	m_clColorButtonLaserIn3.Invalidate();
	m_clColorButtonLaserIn4.Invalidate();

}

//-----------------------------------------------------------------------------
//
//	버튼 : 내부 - 3
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualLaserIn3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	DWORD dwTickCount;
	int nStep = 100;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[INFO] 원점 복귀가 완료되지 않았습니다."));
		AddLog(szLog, 1, m_nUnit, true);

		return;
	}
	if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//소켓 흡착 상태 확인  Laser
	{
		AddLog(_T("[INFO] PCB Vacuum 확인 실패"), 1, m_nUnit, true);

		return;
	}
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	// DARK CAP 하강 상태면 상승
#ifdef ON_LINE_DIO
	/*if (g_clDioControl.DarkPusherCheck(m_nUnit, false, false) == true)
	{
		AddLog(_T("[MANUAL] DARK PUSHER 하강 상태입니다."), 1, m_nUnit);
		return;
	}*/
#endif
	g_clTaskWork[m_nUnit].m_nLaserTiltIndex = 0;
	dwTickCount = GetTickCount();

	while (1)
	{
		switch (nStep)
		{
			// LENS Z축 대기위치
		case 100:
			
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// Lens Z축 회피위치
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			// Lens X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, LASER_POS, (g_clModelData[m_nUnit].m_dLaserMoveX[0] * -1), g_clModelData[m_nUnit].m_dLaserMoveY[0], 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// Lens TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, LASER_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
			// Lens Z축 이동
		case 500:
			/*if (g_clMotorSet.MovePcbZMotor(m_nUnit, LASER_POS, 0.0, true) == false)
			{
				nStep = -500;
				break;
			}*/
			dwTickCount = GetTickCount();
			nStep = 600;
			break;
			// 측정 전 딜레이
		case 600:
			if ((GetTickCount() - dwTickCount) > (DWORD)(g_clModelData[m_nUnit].m_dLaserDelay * 1000))
			{
				nStep = 700;
			}
			break;
			// 측정
		case 700:
			//g_pCarAABonderDlg->SendLaserMeasurePacket(m_nUnit);

			nStep = 800;
			break;
		default:
			break;
		}

		if (nStep >= 800)
		{
			bRetVal = true;
			break;
		}
		else if(nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == true)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] PCB부 LASER POS 3 위치 이동 완료"));
		AddLog(szLog, 0, m_nUnit);
		m_clColorButtonLaserIn1.state = 0;
		m_clColorButtonLaserIn2.state = 0;
		m_clColorButtonLaserIn3.state = 1;
		m_clColorButtonLaserIn4.state = 0;
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] PCB부 LASER POS 3 위치 이동 실패"));
		AddLog(szLog, 1, m_nUnit);

		m_clColorButtonLaserIn3.state = 0;
	}
	m_clColorButtonLaserIn1.Invalidate();
	m_clColorButtonLaserIn2.Invalidate();
	m_clColorButtonLaserIn3.Invalidate();
	m_clColorButtonLaserIn4.Invalidate();
}

//-----------------------------------------------------------------------------
//
//	버튼 : 내부 - 4
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualLaserIn4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	DWORD dwTickCount;
	int nStep = 100;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[INFO] 원점 복귀가 완료되지 않았습니다."));
		AddLog(szLog, 1, m_nUnit, true);

		return;
	}
	if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//소켓 흡착 상태 확인  Laser
	{
		AddLog(_T("[INFO] PCB Vacuum 확인 실패"), 1, m_nUnit, true);

		return;
	}
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	// DARK CAP 하강 상태면 상승
#ifdef ON_LINE_DIO
	/*if (g_clDioControl.DarkPusherCheck(m_nUnit, false, false) == true)
	{
		AddLog(_T("[MANUAL] DARK PUSHER 하강 상태입니다."), 1, m_nUnit);
		return;
	}
	*/
#endif
	g_clTaskWork[m_nUnit].m_nLaserTiltIndex = 0;
	dwTickCount = GetTickCount();

	while (1)
	{
		switch (nStep)
		{
			// LENS Z축 대기위치
		case 100:
			
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// Lens Z축 회피위치
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			// Lens X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, LASER_POS, 0.0, g_clModelData[m_nUnit].m_dLaserMoveY[0], 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// Lens TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, LASER_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
			// Lens Z축 이동
		case 500:
			/*if (g_clMotorSet.MovePcbZMotor(m_nUnit, LASER_POS, 0.0, true) == false)
			{
				nStep = -500;
				break;
			}*/
			dwTickCount = GetTickCount();
			nStep = 600;
			break;
			// 측정 전 딜레이
		case 600:
			if ((GetTickCount() - dwTickCount) > (DWORD)(g_clModelData[m_nUnit].m_dLaserDelay * 1000))
			{
				nStep = 700;
			}
			break;
			// 측정
		case 700:
			//g_pCarAABonderDlg->SendLaserMeasurePacket(m_nUnit);

			nStep = 800;
			break;
		default:
			break;
		}

		if (nStep >= 800)
		{
			bRetVal = true;
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == true)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] PCB부 LASER POS 4 위치 이동 완료"));
		AddLog(szLog, 0, m_nUnit);
		

		m_clColorButtonLaserIn1.state = 0;
		m_clColorButtonLaserIn2.state = 0;
		m_clColorButtonLaserIn3.state = 0;
		m_clColorButtonLaserIn4.state = 1;
	}
	else
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] PCB부 LASER POS 4 위치 이동 실패"));
		AddLog(szLog, 1, m_nUnit);

		m_clColorButtonLaserIn4.state = 0;
	}
	m_clColorButtonLaserIn1.Invalidate();
	m_clColorButtonLaserIn2.Invalidate();
	m_clColorButtonLaserIn3.Invalidate();
	m_clColorButtonLaserIn4.Invalidate();
}

//-----------------------------------------------------------------------------
//
//	버튼 : 수동 측정
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualLaserAutoMeas()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	g_pCarAABonderDlg->SendLaserMeasurePacket(m_nUnit);
}

//-----------------------------------------------------------------------------
//
//	버튼 : 자동 측정
//
//-----------------------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualLaserAuto()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szLog[SIZE_OF_1K];
	DWORD dwTickCount;
	int nStep = 100;
	double dTx = 0.0;
	double dTy = 0.0;
	bool bRetVal = false;
	int i;


	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit, true);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[INFO] 원점 복귀가 완료되지 않았습니다."));
		AddLog(szLog, 1, m_nUnit, true);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	// DARK CAP 하강 상태면 상승
#ifdef ON_LINE_DIO
	//if (g_clDioControl.DarkPusherCheck(m_nUnit, false, false) == true)
	//{
	//	AddLog(_T("[MANUAL] DARK PUSHER 하강 상태입니다."), 1, m_nUnit);
	//	return;
	//}
#endif

	dwTickCount = GetTickCount();
	nStep = 100;
	//--------------------------------------------------------------new
	g_clTaskWork[m_nUnit].m_nLaserTiltIndex = 0;
	g_clTaskWork[m_nUnit].m_dLaserTiltX[0] = g_clTaskWork[m_nUnit].m_dLaserTiltY[0] = 0.0;
	g_clTaskWork[m_nUnit].m_dLaserTiltX[1] = g_clTaskWork[m_nUnit].m_dLaserTiltY[1] = 0.0;

	if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
	{
		//모터 이동 실패
		return;
	}
	

	int dicX = 1;
	int dicY = 1;
	double posX = 0.0;
	double posY = 0.0;
	for (int iNo = 0; iNo < 4; iNo++)
	{
		nStep = 100;
		g_clTaskWork[m_nUnit].m_dLaserVal[iNo] = 0.0;
		g_clTaskWork[m_nUnit].m_clDpLaserPos[iNo].x = 0.0;
		g_clTaskWork[m_nUnit].m_clDpLaserPos[iNo].y = 0.0;

		if (iNo == 1)
		{ 
			posX = g_clModelData[m_nUnit].m_dLaserMoveX[0] * -1;
			posY = 0.0;
		}
		else if (iNo == 2)
		{
			posX = g_clModelData[m_nUnit].m_dLaserMoveX[0] * -1;
			posY = g_clModelData[m_nUnit].m_dLaserMoveY[0] * 1;
		}
		else if (iNo == 3)
		{
			posX = 0.0;
			posY = g_clModelData[m_nUnit].m_dLaserMoveY[0] * 1;
		}

		if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, LASER_POS, posX, posY, 0.0, true) == false)
		{
			//모터 이동 실패
			break;
		}

		if (g_clMotorSet.MovePcbZMotor(m_nUnit, LASER_POS, 0.0, true) == false)
		{
			//모터 이동 실패
			break;
		}

		dwTickCount = GetTickCount();
		while (1)
		{
			switch (nStep)
			{
				// 데이터 초기화
			case 100:
				nStep = 200;
				break;
			case 200:

				if ((GetTickCount() - dwTickCount) >(DWORD)(g_clModelData[m_nUnit].m_dLaserDelay * 1000))
				{
					if (g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_X) && g_clMotorSet.GetStopAxis(m_nUnit, MOTOR_PCB_Y))
					{
						_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] PCB X,Y축 LASER 위치 이동 완료 [POS : %d]"), (iNo + 1));
						AddLog(szLog, 0, m_nUnit, false);
						dwTickCount = GetTickCount();
						nStep = 300;
						break;
					}
					

					if ((GetTickCount() - g_clTaskWork[m_nUnit].m_dwPcbTickCount) > MAX_MOTOR_MOVE_TIME)
					{
						_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] LENS X,Y축 LASER 위치 이동 시간 초과 [POS : %d]"), (iNo + 1));
						AddLog(szLog, 1, m_nUnit, true);
						break;
					}
				}
				
				break;
			case 300:
				g_clTaskWork[m_nUnit].m_bRecvLaserTilt = false;
				g_clTaskWork[m_nUnit].m_clDpLaserPos[iNo].x = g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_X);
				g_clTaskWork[m_nUnit].m_clDpLaserPos[iNo].y = g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_PCB_Y);
				
				if (g_pCarAABonderDlg->SendLaserMeasurePacket(m_nUnit) == false)
				{
					_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] LASER 변위센서 수신 실패"));
					//g_clTaskWork[m_nUnit].m_dLaserTiltX[1], g_clTaskWork[m_nUnit].m_dLaserTiltY[1]);
					AddLog(szLog, 0, m_nUnit);
					nStep = -300;
					break;
				}
				dwTickCount = GetTickCount();
				nStep = 400;
				break;
			case 400:
				if (g_clTaskWork[m_nUnit].m_bRecvLaserTilt == true)
				{ 
					g_clTaskWork[m_nUnit].m_nLaserTiltIndex++;
					nStep = 500;
					break;
				}

				// 5초 동안 대기
				if ((GetTickCount() - dwTickCount) > (DWORD)(g_clModelData[m_nUnit].m_dLaserTimeOut * 1000))
				{
					_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] LASER 변위센서 %d번째 측정 데이터 수신 실패"), g_clTaskWork[m_nUnit].m_nLaserTiltIndex + 1);
					AddLog(szLog, 0, m_nUnit);

					nStep = -400;
				}
				break;
			default:
				break;
			}
			if (nStep >= 500)
			{
				bRetVal = true;
				break;
			}
			else if (nStep < 0)
			{
				break;
			}

			if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
			{
				g_clMotorSet.StopAxisAll(m_nUnit);
				bRetVal = false;
				break;
			}

			Sleep(10);
		
		}
		
	}
	//

	//----------------------------------------------------------------------------------------------------
	if (g_CalcLaserTilt(m_nUnit, dTx, dTy) == true)
	{ 
		g_clTaskWork[m_nUnit].m_dLaserTiltX[0] = dTx; 
		g_clTaskWork[m_nUnit].m_dLaserTiltY[0] = dTy;
		_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] LASER 변위센서 보정량(TX : %.03lf, TY : %.03lf)"), dTx, dTy);
		//g_clTaskWork[m_nUnit].m_dLaserTiltX[1], g_clTaskWork[m_nUnit].m_dLaserTiltY[1]);
		AddLog(szLog, 0, m_nUnit);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------------
	int nRetVal = g_CheckTiltLimit(m_nUnit, 0, dTx, dTy);//g_clTaskWork[m_nUnit].m_dLaserTiltX[0], g_clTaskWork[m_nUnit].m_dLaserTiltY[0]);
	// 보정이동
	if (nRetVal == 0)
	{
		//if (nRetVal == 1)
		//{
		//}
		//// OK
		//else if (nRetVal == 2)
		//{
		//}
		//// 보정 LIMIT 초과
		_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] LASER IN TILT 보정값 LIMIT 초과 [STEP : %d]"), nStep);
		AddLog(szLog, 1, m_nUnit, true);
		return;
	} 
	//-------------------------------------------------------------------------------------------------------------------------------------------
	//
	if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, g_clTaskWork[m_nUnit].m_dLaserTiltX[0], g_clTaskWork[m_nUnit].m_dLaserTiltY[0], true) == true)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("[MANUAL] LASER 변위센서 보정 완료")); 
		AddLog(szLog, 0, m_nUnit);
	}
	return;

}
 
//-----------------------------------------------------------------------------
//
// OnShowWindow
//
//-----------------------------------------------------------------------------
void CManualDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
		g_pCarAABonderDlg->m_clVisionStaticCam[m_nUnit].SetDragUse(true);
		g_pCarAABonderDlg->m_clVisionStaticCam[m_nUnit].SetDragFlag(MOUSE_DRAG);
		SetTimer(WM_UI_TIMER, 200, NULL);
	}
	else
	{
		g_pCarAABonderDlg->m_clVisionStaticCam[m_nUnit].SetDragUse(false);
		KillTimer(WM_UI_TIMER);
	}
}

//-----------------------------------------------------------------------------
//
// Timer
//
//-----------------------------------------------------------------------------
void CManualDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nIDEvent)
	{
	case WM_UI_TIMER:
		this->ShowMotorPositionState();
		this->ShowDioState();

		//TCHAR szLog[SIZE_OF_1K];
		//_stprintf_s(szLog, SIZE_OF_1K, _T("[SOCKET] MAIN PC CONNECT OK = %d"), m_nUnit);
		//AddLog(szLog, 1, m_nUnit, true);
		//this->ShowAlignValue(); 
		//this->ShowLaserSelect();
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

//-----------------------------------------------------------------------------
//
// 모터 위치 상태 표시
//
//-----------------------------------------------------------------------------
void CManualDlg::ShowMotorPositionState()
{
	double dResultVal[MAX_MOTOR_COUNT] = { 0.0, };
	double dOffsetVal[MAX_MOTOR_COUNT] = { 0.0 };
	int i, j;

	/*dOffsetVal[MOTOR_PCB_X] = g_clTaskWork[m_nUnit].m_dAlignX[CAM_PCB];
	dOffsetVal[MOTOR_PCB_Y] = g_clTaskWork[m_nUnit].m_dAlignY[CAM_PCB];
	dOffsetVal[MOTOR_PCB_TH] = g_clTaskWork[m_nUnit].m_dAlignTh[CAM_PCB];*/

	for (i = WAIT_POS; i < MAX_POS_COUNT; i++)
	{
		switch (i)
		{
			//대기 위치
		case WAIT_POS: 

			for (j = MOTOR_PCB_X; j < MAX_MOTOR_COUNT; j++)
			{
				dResultVal[j] = g_clMotorSet.GetEncoderPos(m_nUnit, j) - g_clModelData[m_nUnit].m_stTeachData[WAIT_POS].dPos[j];
			}
			if (fabs(dResultVal[MOTOR_PCB_X]) < ENCORDER_GAP && fabs(dResultVal[MOTOR_PCB_Y]) < ENCORDER_GAP && fabs(dResultVal[MOTOR_PCB_TH]) < ENCORDER_GAP)
			{
				m_clColorButtonPcbWaitPos.state = 1;
			}
			else
			{
				m_clColorButtonPcbWaitPos.state = 0;
			}

			if (fabs(dResultVal[MOTOR_PCB_Z]) < ENCORDER_GAP)
			{
				m_clColorButtonPcbZWaitPos.state = 1;
			}
			else
			{
				m_clColorButtonPcbZWaitPos.state = 0;
			}
			

			

			

			m_clColorButtonPcbWaitPos.Invalidate();
			m_clColorButtonPcbZWaitPos.Invalidate();

			break;
			//SENSOR ALIGN 위치
		case SENSOR_ALIGN_POS:

			for (j = MOTOR_PCB_X; j < MAX_MOTOR_COUNT; j++)
			{
				dResultVal[j] = g_clMotorSet.GetEncoderPos(m_nUnit, j) - g_clModelData[m_nUnit].m_stTeachData[SENSOR_ALIGN_POS].dPos[j];
			}
			if (fabs(dResultVal[MOTOR_PCB_X]) < ENCORDER_GAP && fabs(dResultVal[MOTOR_PCB_Y]) < ENCORDER_GAP && fabs(dResultVal[MOTOR_PCB_TH]) < ENCORDER_GAP)
			{
				m_clColorButtonPcbAlignPos.state = 1;
			}
			else
			{
				m_clColorButtonPcbAlignPos.state = 0;
			}
			if (fabs(dResultVal[MOTOR_PCB_Z]) < ENCORDER_GAP)
			{
				m_clColorButtonPcbZAlignPos.state = 1; 
			}
			else
			{
				m_clColorButtonPcbZAlignPos.state = 0;
			}

			m_clColorButtonPcbAlignPos.Invalidate();
			m_clColorButtonPcbZAlignPos.Invalidate();
			break;
			//공급 위치
		case SUPPLY_POS: 
			for (j = MOTOR_PCB_X; j < MAX_MOTOR_COUNT; j++)
			{
				dResultVal[j] = g_clMotorSet.GetEncoderPos(m_nUnit, j) - g_clModelData[m_nUnit].m_stTeachData[SUPPLY_POS].dPos[j];
			}

			if (fabs(dResultVal[MOTOR_PCB_X]) < ENCORDER_GAP && fabs(dResultVal[MOTOR_PCB_Y]) < ENCORDER_GAP && fabs(dResultVal[MOTOR_PCB_TH]) < ENCORDER_GAP)
			{
				m_clColorButtonPcbLoadPos.state = 1;
			}
			else
			{
				m_clColorButtonPcbLoadPos.state = 0;
			}
			if (fabs(dResultVal[MOTOR_PCB_Z]) < ENCORDER_GAP)
			{
				m_clColorButtonPcbZLoadPos.state = 1;
			}
			else
			{
				m_clColorButtonPcbZLoadPos.state = 0;
			}

			

			

			
			m_clColorButtonPcbLoadPos.Invalidate();
			m_clColorButtonPcbZLoadPos.Invalidate();
			

			//
			break;
			//배출 위치
		case UNLOAD_POS:

			for (j = MOTOR_PCB_X; j < MAX_MOTOR_COUNT; j++)
			{
				dResultVal[j] = g_clMotorSet.GetEncoderPos(m_nUnit, j) - g_clModelData[m_nUnit].m_stTeachData[UNLOAD_POS].dPos[j];
			}
			if (fabs(dResultVal[MOTOR_PCB_X]) < ENCORDER_GAP && fabs(dResultVal[MOTOR_PCB_Y]) < ENCORDER_GAP && fabs(dResultVal[MOTOR_PCB_TH]) < ENCORDER_GAP)
			{
				m_clColorButtonPcbUnLoadPos.state = 1;
			}
			else
			{
				m_clColorButtonPcbUnLoadPos.state = 0;
			}
			if (fabs(dResultVal[MOTOR_PCB_Z]) < ENCORDER_GAP)
			{
				m_clColorButtonPcbZUnLoadPos.state = 1;
			}
			else
			{
				m_clColorButtonPcbZUnLoadPos.state = 0;
			}
			

			
			
			m_clColorButtonPcbUnLoadPos.Invalidate();
			m_clColorButtonPcbZUnLoadPos.Invalidate();

			break;
			//LASER 위치
		case LASER_POS:

			for (j = MOTOR_PCB_X; j < MAX_MOTOR_COUNT; j++)
			{
				dResultVal[j] = g_clMotorSet.GetEncoderPos(m_nUnit, j) - g_clModelData[m_nUnit].m_stTeachData[LASER_POS].dPos[j];
			}
			if (fabs(dResultVal[MOTOR_PCB_X]) < ENCORDER_GAP && fabs(dResultVal[MOTOR_PCB_Y]) < ENCORDER_GAP && fabs(dResultVal[MOTOR_PCB_TH]) < ENCORDER_GAP)
			{
				m_clColorButtonPcbDarkPos.state = 1;
			}
			else
			{
				m_clColorButtonPcbDarkPos.state = 0;
			}
			if (fabs(dResultVal[MOTOR_PCB_Z]) < ENCORDER_GAP)
			{
				m_clColorButtonPcbZDarkPos.state = 1;
			}
			else
			{
				m_clColorButtonPcbZDarkPos.state = 0;
			}

			
			


			m_clColorButtonPcbDarkPos.Invalidate();
			m_clColorButtonPcbZDarkPos.Invalidate();

			break;
			//이물광원 위치
		case OC_LIGHT_POS:

			for (j = MOTOR_PCB_X; j < MAX_MOTOR_COUNT; j++)
			{
				dResultVal[j] = g_clMotorSet.GetEncoderPos(m_nUnit, j) - g_clModelData[m_nUnit].m_stTeachData[OC_LIGHT_POS].dPos[j];
			}
			if (fabs(dResultVal[MOTOR_PCB_X]) < ENCORDER_GAP && fabs(dResultVal[MOTOR_PCB_Y]) < ENCORDER_GAP && fabs(dResultVal[MOTOR_PCB_TH]) < ENCORDER_GAP)
			{
				m_clColorButtonPcbOcTotalPos.state = 1;
			}
			else
			{
				m_clColorButtonPcbOcTotalPos.state = 0;
			}
			if (fabs(dResultVal[MOTOR_PCB_Z]) < ENCORDER_GAP)
			{
				m_clColorButtonPcbZOcTotalPos.state = 1;
			}
			else
			{
				m_clColorButtonPcbZOcTotalPos.state = 0;
			}
			
			

			

			m_clColorButtonPcbOcTotalPos.Invalidate();
			m_clColorButtonPcbZOcTotalPos.Invalidate();

			break;
			
			//본딩 위치
		case CHART_POS:
			//PCB

			for (j = MOTOR_PCB_X; j < MAX_MOTOR_COUNT; j++)
			{
				dResultVal[j] = g_clMotorSet.GetEncoderPos(m_nUnit, j) - g_clModelData[m_nUnit].m_stTeachData[CHART_POS].dPos[j];
			}
			if (fabs(dResultVal[MOTOR_PCB_X]) < ENCORDER_GAP && fabs(dResultVal[MOTOR_PCB_Y]) < ENCORDER_GAP && fabs(dResultVal[MOTOR_PCB_TH]) < ENCORDER_GAP)
			{
				m_clColorButtonPcbBondingPos.state = 1;
			}
			else
			{
				m_clColorButtonPcbBondingPos.state = 0;
			}
			if (fabs(dResultVal[MOTOR_PCB_Z]) < ENCORDER_GAP)
			{
				m_clColorButtonPcbZBondingPos.state = 1;
			}
			else
			{
				m_clColorButtonPcbZBondingPos.state = 0;
			}

			

			

			

			m_clColorButtonPcbBondingPos.Invalidate();
			m_clColorButtonPcbZBondingPos.Invalidate();
			
			break;
		default:
			break;
		}
	}
}
//-----------------------------------------------------------------------------
//
// DIO 상태 표시
//
//-----------------------------------------------------------------------------
void CManualDlg::ShowDioState()
{
	bool bState[2];// MAX_UNIT_COUNT];
	bState[0] = false;
	bState[1] = false;
	//--------------------------------------------------------------------------------------------------------------------------------
	//
	//
	//소켓에 제품 감지
	//
	m_clColorButtonPcbCheck.state = 0;
	bState[m_nUnit] = g_clDioControl.PcbSensorCheck(m_nUnit, true);

	if (bState[m_nUnit] == true)
	{
		m_clColorButtonPcbCheck.state = 1;
	}
	m_clColorButtonPcbCheck.Invalidate();
	m_nPrevPcbSocketVacuumOnState[m_nUnit] = bState[m_nUnit];
	//--------------------------------------------------------------------------------------------------------------------------------
	//
	//
	// 소켓 전/후진 상태
	//

	//--------------------------------------------------------------------------------------------------------------------------------
	//
	//
	// PCB 흡착 / 탈착 상태
	//
	m_clColorButtonPcbVacuumOn.state = 0;
	m_clColorButtonPcbVacuumOff.state = 0;

	bState[m_nUnit] = g_clDioControl.PcbVacuumCheck(m_nUnit, true);

	
	if (bState[m_nUnit] == true)
	{
		m_clColorButtonPcbVacuumOn.state = 1;
	}


	if (bState[m_nUnit] == false)
	{
		m_clColorButtonPcbVacuumOff.state = 1;
	}
	m_clColorButtonPcbVacuumOn.Invalidate();
	m_clColorButtonPcbVacuumOff.Invalidate();

	//--------------------------------------------------------------------------------------------------------------------------------
	//
	//
	// 이물 광원 상승/하강 상태
	//
	//
	//--------------------------------------------------------------------------------------------------------------------------------
	//
	//
	//// DARK Cylinder 상태
	//
	
	/*m_clColorButtonPcbDarkUp.state = 0;
	m_clColorButtonPcbDarkDown.state = 0;
	bState[m_nUnit] = g_clDioControl.DarkPusherCheck(m_nUnit, true);
	if (bState[m_nUnit] == true)
	{
		m_clColorButtonPcbDarkUp.state = 1;
	}
	bState[m_nUnit] = g_clDioControl.DarkPusherCheck(m_nUnit, false);
	if (bState[m_nUnit] == true)
	{
		m_clColorButtonPcbDarkDown.state = 1;
	}
	
	m_clColorButtonPcbDarkUp.Invalidate();
	m_clColorButtonPcbDarkDown.Invalidate();*/
	
	bState[m_nUnit] = g_clDioControl.CurtainDoorCheck(m_nUnit);

	
	if (bState[m_nUnit] == true)
	{
		m_clColorButtonCurtainCheck.state = 1;
	}
	else
	{
		m_clColorButtonCurtainCheck.state = 0;

	}
	m_clColorButtonCurtainCheck.Invalidate();

	//--------------------------------------------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------------------------------------------
	//
	//
	//// CONTACT Cylinder 상태
	//

	/*m_clColorButtonPcbOCFor.state = 0;
	m_clColorButtonPcbOCBack.state = 0;
	bState[m_nUnit] = g_clDioControl.ContactUpcheck(m_nUnit, true);
	if (bState[m_nUnit] == true)
	{
		m_clColorButtonPcbOCFor.state = 1;
	}
	bState[m_nUnit] = g_clDioControl.ContactUpcheck(m_nUnit, false);
	if (bState[m_nUnit] == true)
	{
		m_clColorButtonPcbOCBack.state = 1;
	}

	m_clColorButtonPcbOCFor.Invalidate();
	m_clColorButtonPcbOCBack.Invalidate();*/
}

//-----------------------------------------------------------------------------
//
// ALIGN DATA 표시
//
//-----------------------------------------------------------------------------
void CManualDlg::ShowAlignValue()
{
	TCHAR szData[SIZE_OF_100BYTE];

	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clTaskWork[m_nUnit].m_dAADataX);
	m_clColorStaticAlignXVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clTaskWork[m_nUnit].m_dAADataY);
	m_clColorStaticAlignYVal.SetWindowText(szData);
	_stprintf_s(szData, SIZE_OF_100BYTE, _T("%.03lf"), g_clTaskWork[m_nUnit].m_dAADataTh);
	m_clColorStaticAlignTHVal.SetWindowText(szData);
}

//-----------------------------------------------------------------------------
//
// LASER 측정 내부, 외부 표시
//
//-----------------------------------------------------------------------------
void CManualDlg::ShowLaserSelect()
{
	/*CButton* pButton;

	pButton = (CButton*)GetDlgItem(IDC_RADIO_MANUAL_LASER_1);
	if(pButton->GetCheck() == 1)
	{
		m_clColorButtonLaserIn1.SetWindowText(_T("POS #1"));
		m_clColorButtonLaserIn2.SetWindowText(_T("POS #2"));
		m_clColorButtonLaserIn3.SetWindowText(_T("POS #3"));
		m_clColorButtonLaserIn4.SetWindowText(_T("POS #4"));
		g_clTaskWork[m_nUnit].m_bManualLaserPos = true;
	}
	else
	{
		m_clColorButtonLaserIn1.SetWindowText(_T("외부 - 1"));
		m_clColorButtonLaserIn2.SetWindowText(_T("외부 - 2"));
		m_clColorButtonLaserIn3.SetWindowText(_T("외부 - 3"));
		m_clColorButtonLaserIn4.SetWindowText(_T("외부 - 4"));
		g_clTaskWork[m_nUnit].m_bManualLaserPos = false;
	}*/
}

//-----------------------------------------------------------------------------
//
//	OnCtlColor
//
//-----------------------------------------------------------------------------
HBRUSH CManualDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (pWnd->GetDlgCtrlID() == IDC_RADIO_MANUAL_LASER_1 || pWnd->GetDlgCtrlID() == IDC_RADIO_MANUAL_LASER_2)
	{
		pDC->SetTextColor(RGB_COLOR_WHITE);
		pDC->SetBkMode(TRANSPARENT);

		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

//-----------------------------------------------------------------------------
//
// PreTranslateMessage
//
//-----------------------------------------------------------------------------
BOOL CManualDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		/*if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_PCB_VACUUM_ON)->m_hWnd)
		{
			m_clColorButtonPcbVacuumOn.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_PCB_VACUUM_OFF)->m_hWnd)
		{
			m_clColorButtonPcbVacuumOff.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_PCB_GRIP_FOR)->m_hWnd)
		{
			m_clColorButtonPcbGripFor.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_PCB_GRIP_BACK)->m_hWnd)
		{
			m_clColorButtonPcbGripBack.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_PCB_DARK_UP)->m_hWnd)
		{
			m_clColorButtonPcbDarkUp.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_PCB_DARK_DOWN)->m_hWnd)
		{
			m_clColorButtonPcbDarkDown.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_PCB_OC_FOR)->m_hWnd)
		{
			m_clColorButtonPcbOCFor.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_PCB_OC_BACK)->m_hWnd)
		{
			m_clColorButtonPcbOCBack.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LENS_GRIP_FOR)->m_hWnd)
		{
			m_clColorButtonLensGripFor.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LENS_GRIP_BACK)->m_hWnd)
		{
			m_clColorButtonLensGripBack.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LENS_CENT_FOR)->m_hWnd)
		{
			m_clColorButtonLensCentFor.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LENS_CENT_BACK)->m_hWnd)
		{
			m_clColorButtonLensCentBack.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_UV_SHUTTER_OPEN)->m_hWnd)
		{
			m_clColorButtonUVShutterOpen.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_UV_SHUTTER_CLOSE)->m_hWnd)
		{
			m_clColorButtonUVShutterClose.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_ALIGN)->m_hWnd)
		{
			m_clColorButtonAlign.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_ALIGN_MOVE)->m_hWnd)
		{
			m_clColorButtonAlignMove.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LASER_IN_1)->m_hWnd)
		{
			m_clColorButtonLaserIn1.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LASER_IN_2)->m_hWnd)
		{
			m_clColorButtonLaserIn2.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LASER_IN_3)->m_hWnd)
		{
			m_clColorButtonLaserIn3.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LASER_IN_4)->m_hWnd)
		{
			m_clColorButtonLaserIn4.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LASER_DATA_MEAS)->m_hWnd)
		{
			m_clColorButtonLaserDataMeas.SetSelected(true);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LASER_AUTO)->m_hWnd)
		{
			m_clColorButtonLaserAutoMeas.SetSelected(true);
		}*/
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		/*if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_PCB_VACUUM_ON)->m_hWnd)
		{
			m_clColorButtonPcbVacuumOn.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_PCB_VACUUM_OFF)->m_hWnd)
		{
			m_clColorButtonPcbVacuumOff.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_PCB_GRIP_FOR)->m_hWnd)
		{
			m_clColorButtonPcbGripFor.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_PCB_GRIP_BACK)->m_hWnd)
		{
			m_clColorButtonPcbGripBack.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_PCB_DARK_UP)->m_hWnd)
		{
			m_clColorButtonPcbDarkUp.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_PCB_DARK_DOWN)->m_hWnd)
		{
			m_clColorButtonPcbDarkDown.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_PCB_OC_FOR)->m_hWnd)
		{
			m_clColorButtonPcbOCFor.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_PCB_OC_BACK)->m_hWnd)
		{
			m_clColorButtonPcbOCBack.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LENS_GRIP_FOR)->m_hWnd)
		{
			m_clColorButtonLensGripFor.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LENS_GRIP_BACK)->m_hWnd)
		{
			m_clColorButtonLensGripBack.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LENS_CENT_FOR)->m_hWnd)
		{
			m_clColorButtonLensCentFor.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LENS_CENT_BACK)->m_hWnd)
		{
			m_clColorButtonLensCentBack.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_UV_SHUTTER_OPEN)->m_hWnd)
		{
			m_clColorButtonUVShutterOpen.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_UV_SHUTTER_CLOSE)->m_hWnd)
		{
			m_clColorButtonUVShutterClose.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_ALIGN)->m_hWnd)
		{
			m_clColorButtonAlign.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_ALIGN_MOVE)->m_hWnd)
		{
			m_clColorButtonAlignMove.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LASER_IN_1)->m_hWnd)
		{
			m_clColorButtonLaserIn1.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LASER_IN_2)->m_hWnd)
		{
			m_clColorButtonLaserIn2.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LASER_IN_3)->m_hWnd)
		{
			m_clColorButtonLaserIn3.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LASER_IN_4)->m_hWnd)
		{
			m_clColorButtonLaserIn4.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LASER_DATA_MEAS)->m_hWnd)
		{
			m_clColorButtonLaserDataMeas.SetSelected(false);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_MANUAL_LASER_AUTO)->m_hWnd)
		{
			m_clColorButtonLaserAutoMeas.SetSelected(false);
		}*/
	}

	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CManualDlg::OnBnClickedButtonManualPcbOc2800()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// LENS Z축 대기위치 이동
		case 100:

			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		// PCB Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//PCB X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbYTMotor(m_nUnit, OC_5000k_POS, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, OC_5000k_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if (nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 OC 5000k 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 OC 5000k 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}


void CManualDlg::OnBnClickedButtonManualPcbZDefect2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, OC_5000k_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 OC 5000k POS 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 OC 5000k POS 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}


void CManualDlg::OnBnClickedButtonManualLensLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// LENS Z축 대기위치 이동
		case 100:

			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// PCB Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//PCB X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbYTMotor(m_nUnit, SUPPLY_POS, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, SUPPLY_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if (nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Loading 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Loading 위치 이동 완료"), 0, m_nUnit);
	}
}


void CManualDlg::OnBnClickedButtonManualLensZLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}
	TCHAR szLog[SIZE_OF_1K];
	if (g_clDioControl.LensGripCheck(m_nUnit, true) == true)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("LENS GRIP 확인"));
		AddLog(szLog, 0, m_nUnit);

		if (g_clDioControl.LensBufferSensorCheck(m_nUnit, true) == true)
		{
			g_ShowMsgPopup(_T("ERROR"), _T("LENS BUFFER 렌즈 확인"), RGB_COLOR_RED);
			return;
		}
		if (g_ShowMsgModal(_T("확인"), _T("[AUTO] LENS GRIP 상태입니다. 진행하시겠습니까?"), RGB_COLOR_RED) == true)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] LENS GRIP 상태 진행"));
			AddLog(szLog, 0, m_nUnit);
		}
		else
		{
			return;
		}
	}
	if (g_clMotorSet.GetLensXYMotorPosCheck(m_nUnit, SUPPLY_POS) == false)
	{
		AddLog(_T("LENS Y LENS 공급 위치가 아닙니다."), 1, m_nUnit);

		return;
	}
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MoveLensZMotor(m_nUnit, SUPPLY_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] LENS부 Z축 Loading POS 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] LENS부 Z축 Loading POS 위치 이동 완료"), 0, m_nUnit);
	}
}


void CManualDlg::OnBnClickedButtonManualUnload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// LENS Z축 대기위치 이동
		case 100:

			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// PCB Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//PCB X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbYTMotor(m_nUnit, UNLOAD_POS, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, UNLOAD_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if (nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 UnLoading 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 UnLoading 위치 이동 완료"), 0, m_nUnit);
	}
}


void CManualDlg::OnBnClickedButtonManualZUnload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, UNLOAD_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}


	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 UnLoading POS 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 UnLoading POS 위치 이동 완료"), 0, m_nUnit);
	}
}


void CManualDlg::OnBnClickedButtonManualPcbGripUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	g_clDioControl.PcbGripUp(m_nUnit, true, false);
}


void CManualDlg::OnBnClickedButtonManualPcbGripDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();


	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	g_clDioControl.PcbGripUp(m_nUnit, false, false);

	g_clLaonGrabberWrapper[m_nUnit].StopGrab();
	Sleep(100);
	g_clLaonGrabberWrapper[m_nUnit].CloseDevice();
}

void CManualDlg::OnBnClickedButtonManualPcbSocketLoad()
{
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	g_clDioControl.PcbVacuum(m_nUnit, true);

	if (g_clDioControl.PcbSocketVacuumCheck(m_nUnit, false, false) == true)
	{
		g_clDioControl.PcbVacuum(m_nUnit, false);
		g_ShowMsgPopup(_T("확인"), _T("VACUUM 제품 확인 실패."), RGB_COLOR_RED);
		return;
	}

	if( (g_clDioControl.PcbGripCheck(m_nUnit, true) == true) &&
		(g_clDioControl.PcbGripUpCheck(m_nUnit, true) == true))
	{

	}
	else
	{
		if (g_clDioControl.PcbGripUp(m_nUnit, false, true) == false)
		{
			g_ShowMsgPopup(_T("확인"), _T("GRIP UP 하강 실패."), RGB_COLOR_RED);
			return;
		}
		Sleep(300);
		if (g_clDioControl.PcbGrip(m_nUnit, true, true) == false)
		{
			g_ShowMsgPopup(_T("확인"), _T("GRIP 전진 실패."), RGB_COLOR_RED);
			return;
		}
		Sleep(300);
		if (g_clDioControl.PcbGripUp(m_nUnit, true, true) == false)
		{
			g_ShowMsgPopup(_T("확인"), _T("GRIP UP 상승 실패."), RGB_COLOR_RED);
			return;
		}
	}

	g_ShowMsgPopup(_T("확인"), _T("제품 로드 완료."), RGB_COLOR_RED);
	return;
}

void CManualDlg::OnBnClickedButtonManualBarcode()
{
	CString sMsg = _T("");

	g_clTaskWork[m_nUnit].m_bManualTest = true;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[MANUAL] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[MANUAL] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	sMsg.Format(_T("#AA%d@PCB_BCR&STR$"), (m_nUnit + g_clSysData.m_nUnitNo + g_clSysData.m_nSysNo + 1));//수동 바코드요청

	if (g_pCarAABonderDlg->SendDataToAAMain(m_nUnit, sMsg) == true)
	{
		AddLog(_T("[MANUAL] BARCODE 값 요청."), 1, m_nUnit);
	}

	//g_ShowMsgPopup(_T("확인"), _T("BARCODE 값 요청 중."), RGB_COLOR_RED);
	//Sleep(3000);
	//m_clColorStaticAlignXVal.GetWindowText(g_pCarAABonderDlg->m_clColorStaticBcrVal[m_nUnit].GetWindowTextA);
	//g_ShowMsgPopup(_T("확인"), _T("BARCODE 값 완료"), RGB_COLOR_RED);
}


void CManualDlg::OnBnClickedButtonManualPcbSocketUnload()
{
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	g_clLaonGrabberWrapper[m_nUnit].StopGrab();
	Sleep(100);
	g_clLaonGrabberWrapper[m_nUnit].CloseDevice();

	g_clDioControl.PcbVacuum(m_nUnit, true);

	if (g_clDioControl.PcbGripUp(m_nUnit, false, true) == false)
	{
		g_ShowMsgPopup(_T("확인"), _T("Socket 하강 실패."), RGB_COLOR_RED);
		return;
	}
	else
	{
		AddLog(_T("[MANUAL] SOCKET 하강 완료"), 0, m_nUnit);
	}
	Sleep(300);
	if (g_clDioControl.PcbGrip(m_nUnit, false, true) == false)
	{
		g_ShowMsgPopup(_T("확인"), _T("Socket 후진 실패."), RGB_COLOR_RED);
		return;
	}else
	{
		AddLog(_T("[MANUAL] SOCKET 후진 완료"), 0, m_nUnit);
	}

	/*if (g_clDioControl.PcbGripUp(m_nUnit, true, true) == false)
	{
		g_ShowMsgPopup(_T("확인"), _T("GRIP UP 상승 실패."), RGB_COLOR_RED);
		return;
	}*/

	g_clDioControl.PcbVacuum(m_nUnit, false);

	g_ShowMsgPopup(_T("확인"), _T("제품 언로드 완료."), RGB_COLOR_RED);
	return;
}


void CManualDlg::OnBnClickedButtonManualLensWait()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	/*if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}*/

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
		case 100:

			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// LENS Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MoveLensZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 220;
			break;
		case 220:
			//CL LENS 간섭 때문에 대기위치에서 올때 X축 (+ Limit) 쪽으로 최대한 이동후 진행
			if (g_clMotorSet.MoveLensXMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -220;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 240;
			break;
		case 240:
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//LENS X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MoveLensXYMotor(m_nUnit, WAIT_POS, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// LENS TX,TY축 이동
		case 400:
			if (g_clMotorSet.MoveLensTxTyMotor(m_nUnit, WAIT_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if (nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] LENS부 대기위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] LENS부 대기위치 이동 완료"), 0, m_nUnit);
	}
}


void CManualDlg::OnBnClickedButtonManualLensZWait()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	/*if (g_clMotorSet.GetLensXYMotorPosCheck(m_nUnit, WAIT_POS) == false)
	{
		AddLog(_T("LENS X,Y WAIT 위치가 아닙니다."), 1, m_nUnit);

		return;
	}*/

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// Lens Z축 이동
		case 100:
			if (g_clMotorSet.MoveLensZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] LENS부 Z축 대기위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] LENS부 Z축 대기위치 이동 완료"), 0, m_nUnit);
	}
}


void CManualDlg::OnBnClickedButtonManualLensLoad2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;
	double dCurYpos = 0.0;
	double dChartYpos = 0.0;
	
		

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}
	TCHAR szLog[SIZE_OF_1K];
	if (g_clDioControl.LensGripCheck(m_nUnit, true) == true)
	{
		if (g_clDioControl.LensBufferSensorCheck(m_nUnit, true) == true)
		{
			g_ShowMsgPopup(_T("ERROR"), _T("LENS BUFFER 렌즈 확인"), RGB_COLOR_RED);
			return;
		}
		_stprintf_s(szLog, SIZE_OF_1K, _T("LENS GRIP 확인"));
		AddLog(szLog, 0, m_nUnit);

		if (g_ShowMsgModal(_T("확인"), _T("[AUTO] LENS GRIP 상태입니다. 진행하시겠습니까?"), RGB_COLOR_RED) == true)
		{
			_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO][LENS] LENS GRIP 상태 진행"));
			AddLog(szLog, 0, m_nUnit);
		}
		else
		{
			return;
		}
	}
	/*if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}*/

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
		case 100:

			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// LENS Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MoveLensZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 220;
			break;
		case 220:
			if (g_clMotorSet.MoveLensYMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -240;
				break;
			}
			
			nStep = 240;
			break;
		case 240:
			if (g_clMotorSet.MoveLensXMotor(m_nUnit, SUPPLY_POS, 0.0, true) == false)
			{
				nStep = -220;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//LENS X,Y축 이동
		case 300:
			if (g_clMotorSet.MoveLensXYMotor(m_nUnit, SUPPLY_POS, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// LENS TX,TY축 이동
		case 400:
			if (g_clMotorSet.MoveLensTxTyMotor(m_nUnit, SUPPLY_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if (nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] LENS부 LENS 공급위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] LENS부 LENS 공급위치 이동 완료"), 0, m_nUnit);
	}
}



void CManualDlg::OnBnClickedButtonManualLensBonding()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


void CManualDlg::OnBnClickedButtonManualLensZBonding()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clMotorSet.GetLensXYMotorPosCheck(m_nUnit, CHART_POS) == false)
	{
		AddLog(_T("LENS X,Y CHART 위치가 아닙니다."), 1, m_nUnit);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// Lens Z축 이동
		case 100:
			if (g_clMotorSet.MoveLensZMotor(m_nUnit, CHART_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] LENS부 Z축 CHART 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] LENS부 Z축 CHART 위치 이동 완료"), 0, m_nUnit);
	}
}


void CManualDlg::OnBnClickedButtonManualLensGrip()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	g_clDioControl.LensGrip(m_nUnit, true, false);
}


void CManualDlg::OnBnClickedButtonManualLensUngrip()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	g_clDioControl.LensGrip(m_nUnit, false, false);
}


void CManualDlg::OnBnClickedButtonManualEpoxyOn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	int nStep = 0;
	bool bRetVal = false;
	int i = 0;


	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	//if (g_clMotorSet.GetPcbZMotorPosCheck(m_nUnit, WAIT_POS) == false)
	//{
	//	AddLog(_T("PCB Z 대기위치가 아닙니다."), 1, m_nUnit);
	//	return;
	//}
	TCHAR szLog[SIZE_OF_1K];
	if (g_clMotorSet.GetPcbXYMotorPosCheck(m_nUnit, DISPENSE_POS) == false)
	{
		_stprintf_s(szLog, SIZE_OF_1K, _T("PCB X,Y 도포위치가 아닙니다."));
		AddLog(szLog, 1, m_nUnit);

		g_ShowMsgPopup(_T("ERROR"), szLog, RGB_COLOR_RED);
		return;
	}


	if (g_pCarAABonderDlg->m_clCustomThread[UNIT_AA1].GetThreadRunning() == true)
	{
		/*if (g_pCarAABonderDlg->m_clCustomThread[UNIT_AA1].GetThreadPause() == true)
		{
			g_pCarAABonderDlg->m_clCustomThread[UNIT_AA1].SetThreadPause(false);
		}*/
		g_pCarAABonderDlg->m_clCustomThread[UNIT_AA1].EndThread();
		AddLog(_T("모터 동작중입니다."), 1, m_nUnit);
		return;
	}

	g_pCarAABonderDlg->m_clCustomThread[UNIT_AA1].CustomThreadrun(DISPENSE_THREAD);

	//g_clDioControl.EpoxyDischargeOn(m_nUnit, true, false);
#endif
}


void CManualDlg::OnBnClickedButtonManualEpoxySet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[수동검사] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[수동검사] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}
	m_clEpoxySetDlg.SetUnit(m_nUnit);
	m_clEpoxySetDlg.ShowWindow(SW_SHOW);
}

void CManualDlg::OnBnClickedButtonManualPcbOcTotal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}
	if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//소켓 흡착 상태 확인  Laser
	{
		AddLog(_T("[INFO] PCB Vacuum 확인 실패"), 1, m_nUnit, true);

		return;
	}
	/*if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}*/

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
		case 100:

			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// PCB Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}

			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//PCB X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, OC_LIGHT_POS, 0.0, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}

			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, OC_LIGHT_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if (nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 이물광원 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 이물광원 위치 이동 완료"), 0, m_nUnit);
	}
}


void CManualDlg::OnBnClickedButtonManualPcbDispense()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// LENS Z축 대기위치 이동
		case 100:

			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// PCB Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//PCB X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbYTMotor(m_nUnit, DISPENSE_POS, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, DISPENSE_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if (nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 DISPENSE 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 DISPENSE 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}


void CManualDlg::OnBnClickedButtonManualPcbZOcTotal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}
	if (g_clMotorSet.GetPcbXYMotorPosCheck(m_nUnit, OC_LIGHT_POS) == false)
	{
		AddLog(_T("PCB X,Y 이물광원 위치가 아닙니다."), 1, m_nUnit);

		return;
	}
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, OC_LIGHT_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 이물광원 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 이물광원 위치 이동 완료"), 0, m_nUnit);
	}
}


void CManualDlg::OnBnClickedButtonManualPcbZDispense()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clMotorSet.GetPcbXYMotorPosCheck(m_nUnit, DISPENSE_POS) == false)
	{
		AddLog(_T("PCB X,Y DISPANSE 위치가 아닙니다."), 1, m_nUnit);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, DISPENSE_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 DISPENSE 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 DISPENSE 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}


void CManualDlg::OnBnClickedButtonManualLensAlign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;
	double dCurYpos = 0.0; 
	double dChartYpos = 0.0;


	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
		case 100:

			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// LENS Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MoveLensZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 220;
			break;
		case 220:
			dCurYpos = g_clMotorSet.GetEncoderPos(m_nUnit, MOTOR_LENS_Y);
			dChartYpos = g_clModelData[m_nUnit].m_stTeachData[CHART_POS].dPos[MOTOR_LENS_Y];

			if (dCurYpos < dChartYpos - 30.0)
			{
				dwTickCount = GetTickCount();
				nStep = 300;
				break;
			}
			//CL LENS 간섭 때문에 대기위치에서 올때 X축 (+ Limit) 쪽으로 최대한 이동후 진행
			if (g_clMotorSet.MoveLensXMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -220;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 240;
			break;
		case 240:
			if (g_clMotorSet.MoveLensYMotor(m_nUnit, LENS_ALIGN_POS, 0.0, true) == false)
			{
				nStep = -240;
				break; 
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//LENS X,Y축 이동
		case 300:
			if (g_clMotorSet.MoveLensXYMotor(m_nUnit, LENS_ALIGN_POS, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// LENS TX,TY축 이동
		case 400:
			if (g_clMotorSet.MoveLensTxTyMotor(m_nUnit, LENS_ALIGN_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if (nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] LENS부 LENS ALIGN 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] LENS부 LENS ALIGN 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}


void CManualDlg::OnBnClickedButtonManualLensZAlign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clMotorSet.GetLensXYMotorPosCheck(m_nUnit, LENS_ALIGN_POS) == false)
	{
		AddLog(_T("LENS X,Y LENS ALIGN 위치가 아닙니다."), 1, m_nUnit);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// Lens Z축 이동
		case 100:
			if (g_clMotorSet.MoveLensZMotor(m_nUnit, LENS_ALIGN_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] LENS부 Z축 LENS ALIGN 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] LENS부 Z축 LENS ALIGN 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}


void CManualDlg::OnBnClickedButtonManualPcbHolderAlign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
		case 100:

			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// PCB Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//PCB X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbYTMotor(m_nUnit, HOLDER_ALIGN_POS, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, HOLDER_ALIGN_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if (nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 HOLDER ALIGN위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 HOLDER ALIGN위치 이동 완료"), 0, m_nUnit);
	}
#endif
}


void CManualDlg::OnBnClickedButtonManualPcbZHolderAlign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clMotorSet.GetPcbXYMotorPosCheck(m_nUnit, HOLDER_ALIGN_POS) == false)
	{
		AddLog(_T("PCB X,Y HOLDER ALIGN 위치가 아닙니다."), 1, m_nUnit);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, HOLDER_ALIGN_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 HOLDER ALIGN 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 HOLDER ALIGN 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}


void CManualDlg::OnBnClickedButtonManualPcbLaserLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// LENS Z축 대기위치 이동
		case 100:

			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// PCB Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//PCB X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbYTMotor(m_nUnit, LASER_IN_POS, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, LASER_IN_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if (nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 LASER 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 LASER 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}


void CManualDlg::OnBnClickedButtonManualEolAlign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// LENS Z축 대기위치 이동
		case 100:

			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// PCB Z축 회피 위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//PCB X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbYTMotor(m_nUnit, EOL_ALIGN_POS, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, EOL_ALIGN_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if (nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 완제품 ALIGN 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 완제품 ALIGN 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}


void CManualDlg::OnBnClickedButtonManualPcbZLaserLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clMotorSet.GetPcbXYMotorPosCheck(m_nUnit, LASER_IN_POS) == false)
	{
		AddLog(_T("PCB X,Y 완제품 LASER 위치가 아닙니다."), 1, m_nUnit);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, LASER_IN_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 완제품 LASER POS 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 완제품 LASER POS 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}


void CManualDlg::OnBnClickedButtonManualZEolAlign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#if 0
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clMotorSet.GetPcbXYMotorPosCheck(m_nUnit, EOL_ALIGN_POS) == false)
	{
		AddLog(_T("PCB X,Y EOL ALIGN 위치가 아닙니다."), 1, m_nUnit);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, EOL_ALIGN_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 완제품 ALIGN POS 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 완제품 ALIGN POS 위치 이동 완료"), 0, m_nUnit);
	}
#endif
}


void CManualDlg::OnBnClickedButtonManualEpoxyInsp()
{
	bool bResult;
	g_clModelData[m_nUnit].Load(g_clSysData.m_szModelName);
	
	bResult = g_pCarAABonderDlg->EpoxyFinddispense(m_nUnit);
	if (bResult) {
		g_clVision.m_clMilDrawText[m_nUnit].AddList(860, 690, 35, 15, "O K", "Arial", M_COLOR_GREEN);
	}
	else {
		g_clVision.m_clMilDrawText[m_nUnit].AddList(860, 690, 35, 15, "N G", "Arial", M_COLOR_RED);
	}
	g_clVision.DrawOverlayAll(m_nUnit);
}


void CManualDlg::OnBnClickedButtonManualEolChart()
{

}


void CManualDlg::OnBnClickedButtonManualZEolChart()
{
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clMotorSet.GetPcbXYMotorPosCheck(m_nUnit, CHART_POS) == false)
	{
		AddLog(_T("PCB X,Y EOL CHART 위치가 아닙니다."), 1, m_nUnit);

		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, CHART_POS, 0.0, true, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 완제품 CHART POS 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 완제품 CHART POS 위치 이동 완료"), 0, m_nUnit);
	}
}


void CManualDlg::OnBnClickedButtonManualEpoxyOn2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_clDioControl.EpoxyDischargeOn(0, true);
}


void CManualDlg::OnBnClickedButtonManualEpoxySet2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_clDioControl.EpoxyDischargeOn(0, false);
}


void CManualDlg::OnBnClickedButtonManualPcbSocketUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();
	}
	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	
	TCHAR szLog[SIZE_OF_1K];
	_stprintf_s(szLog, SIZE_OF_1K, _T("	[MANUAL] 이물 광원  상승"));
	AddLog(szLog, 0, m_nUnit);

	//g_clDioControl.EziOcUp(m_nUnit, true);
}


void CManualDlg::OnBnClickedButtonManualPcbSocketDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].Invalidate();
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].Invalidate();


	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}
	
	TCHAR szLog[SIZE_OF_1K];
	_stprintf_s(szLog, SIZE_OF_1K, _T("	[MANUAL] 이물 광원  하강"));
	AddLog(szLog, 0, m_nUnit);

	//g_clDioControl.EziOcUp(m_nUnit, false);
}


void CManualDlg::OnBnClickedButtonManualPcbUnload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}

	if (g_clDioControl.PcbVacuumCheck(m_nUnit, true) == false)		//소켓 흡착 상태 확인  Laser
	{
		AddLog(_T("[INFO] PCB Vacuum 확인 실패"), 1, m_nUnit, true);

		return;
	}

	/*if (g_clDioControl.DarkPusherCheck(m_nUnit, false, true) == true)
	{
		AddLog(_T("[INFO] DARK PUSHER 하강중 사용 불가"), 1, m_nUnit);
		return;
	}*/

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
		case 100:
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
			// PCB Z축 대기 위치 이동
		case 200:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, WAIT_POS, 0.0, true) == false)
			{
				nStep = -200;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 300;
			break;
			//PCB X,Y,T축 이동
		case 300:
			if (g_clMotorSet.MovePcbXYTMotor(m_nUnit, UNLOAD_POS, 0.0, 0.0, 0.0, true) == false)
			{
				nStep = -300;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 400;
			break;
			// PCB TX,TY축 이동
		case 400:
			if (g_clMotorSet.MovePcbTxTyMotor(m_nUnit, UNLOAD_POS, 0.0, 0.0, true) == false)
			{
				nStep = -400;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 500;
			break;
		default:
			break;
		}

		if (nStep >= 500)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;
			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 배출 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 배출 위치 이동 완료"), 0, m_nUnit);
	}
}


void CManualDlg::OnBnClickedButtonManualPcbZUnload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}
	if (g_clMotorSet.GetPcbXYMotorPosCheck(m_nUnit, UNLOAD_POS) == false)
	{
		AddLog(_T("PCB X,Y UNLOAD_POS 위치가 아닙니다."), 1, m_nUnit);

		return;
	}
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, UNLOAD_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 배출 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 배출 위치 이동 완료"), 0, m_nUnit);
	}
}


void CManualDlg::OnBnClickedButtonLensBufferVacuumSensor()
{
	// TODO: Add your control notification handler code here
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}
	TCHAR szLog[SIZE_OF_1K];
	_stprintf_s(szLog, SIZE_OF_1K, _T("	[MANUAL] LENS BUFFER VACUUM ON"));
	AddLog(szLog, 0, m_nUnit);
	g_clDioControl.LensBufferVacuumOn(m_nUnit, true);
}


void CManualDlg::OnBnClickedButtonLensBufferVacuumOff()
{
	// TODO: Add your control notification handler code here
	TCHAR szLog[SIZE_OF_1K];
	_stprintf_s(szLog, SIZE_OF_1K, _T("	[MANUAL] LENS BUFFER VACUUM OFF"));
	AddLog(szLog, 0, m_nUnit);
	g_clDioControl.LensBufferVacuumOn(m_nUnit, false);
}


void CManualDlg::OnBnClickedButtonManualLaserInZ()
{
	// TODO: Add your control notification handler code here
	DWORD dwTickCount;
	int nStep;
	bool bRetVal = false;
	int i;

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_AUTO)
	{
		AddLog(_T("[INFO] 자동 운전 중 사용 불가"), 1, m_nUnit);
		return;
	}

	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_PAUSE)
	{
		AddLog(_T("[INFO] 일시 정지 중 사용 불가"), 1, m_nUnit);
		return;
	}

	// 원점 복귀 상태 체크
	if (g_clMotorSet.GetHomeState(m_nUnit) == false)
	{
		AddLog(_T("[INFO] 원점 복귀가 완료되지 않았습니다."), 1, m_nUnit);

		return;
	}
	if (g_clMotorSet.GetPcbXYMotorPosCheck(m_nUnit, LASER_POS) == false)
	{
		AddLog(_T("PCB X,Y LASER 위치가 아닙니다."), 1, m_nUnit);

		return;
	}
	if (g_clTaskWork[m_nUnit].m_nAutoFlag == MODE_READY)
	{
		g_clTaskWork[m_nUnit].m_nAutoFlag = MODE_STOP;
		g_pCarAABonderDlg->m_clColorButtonAutoReady[m_nUnit].state = 0;
		g_pCarAABonderDlg->m_clColorButtonAutoStop[m_nUnit].state = 1;
	}

	for (i = 0; i < MAX_MOTOR_COUNT; i++)
	{
		if (g_clMotorSet.GetStopAxis(m_nUnit, i) == false)
		{
			AddLog(_T("모터 구동중입니다."), 1, m_nUnit);
			return;
		}
	}

	dwTickCount = GetTickCount();
	nStep = 100;

	while (1)
	{
		switch (nStep)
		{
			// PCB Z축 이동
		case 100:
			if (g_clMotorSet.MovePcbZMotor(m_nUnit, LASER_POS, 0.0, true) == false)
			{
				nStep = -100;
				break;
			}
			dwTickCount = GetTickCount();
			nStep = 200;
			break;
		default:
			break;
		}

		if (nStep >= 200)
		{
			bRetVal = true;
			break;
		}
		else if (nStep < 0)
		{
			break;
		}

		if ((GetTickCount() - dwTickCount) > MAX_MOTOR_MOVE_TIME)
		{
			g_clMotorSet.StopAxisAll(m_nUnit);
			bRetVal = false;

			break;
		}

		Sleep(10);
	}

	if (bRetVal == false)
	{
		AddLog(_T("[MANUAL] PCB부 Z축 LASER 위치 이동 실패"), 1, m_nUnit);
	}
	else
	{
		AddLog(_T("[MANUAL] PCB부 Z축 LASER 위치 이동 완료"), 0, m_nUnit);
	}
}
