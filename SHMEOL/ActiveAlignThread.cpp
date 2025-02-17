#include "StdAfx.h"
#include "ActiveAlignThread.h"


CActiveAlignThread::CActiveAlignThread(void)
{
}


CActiveAlignThread::~CActiveAlignThread(void)
{
}


//-----------------------------------------------------------------------------
//
//
//
//-----------------------------------------------------------------------------
void CActiveAlignThread::SetUnit(int nUnit)
{
	m_nUnit = nUnit;

	m_clPcbProcess.SetUnit(nUnit);
}

//-----------------------------------------------------------------------------
//
//	������ ������
//
//-----------------------------------------------------------------------------
void CActiveAlignThread::ThreadConstructor()
{
	m_nStep = 10000;
}

//-----------------------------------------------------------------------------
//
//	������ �Ҹ���
//
//-----------------------------------------------------------------------------
void CActiveAlignThread::ThreadDestructor()
{

}

//-----------------------------------------------------------------------------
//
//	������ �ݹ�
//
//-----------------------------------------------------------------------------
void CActiveAlignThread::ThreadCallBack()
{
#ifdef ON_LINE_SOCKET
	//TCHAR szLog[SIZE_OF_1K];

	//if (g_pCarAABonderDlg->GetAAMainConnect() == false)
	//{//! Main�� ����� �������� ��� �Ͻ�����.
	//	g_pCarAABonderDlg->PauseAutoProcess(m_nUnit);
	//	_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] MAIN PC ����� ���������ϴ�."));
	//	//AddLog(szLog, 1, 999);
 //       AddLog(szLog, 1, 0);
 //       AddLog(szLog, 1, 1);
	//	return;
	//}
#endif
	
	// PCB ����
	if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= g_clTaskWork[m_nUnit].m_nStartStep && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < g_clTaskWork[m_nUnit].m_nEndStep)
	{
		if ((g_clTaskWork[m_nUnit].m_nAutoFlag != MODE_AUTO) && (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 30000)) 
		{
			g_pCarAABonderDlg->StopAutoProcess(m_nUnit);
			return;
		}

		// ���� ��ư ������
		if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 10000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 20000)
		{
			if ((GetTickCount() - m_dwTickCount[0]) > 500)
			{
				g_pCarAABonderDlg->ShowHomeState(m_nUnit);
				m_dwTickCount[0] = GetTickCount();
			}
		}

		// �����غ� ��ư ������
		if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 20000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 30000)
		{
			if ((GetTickCount() - m_dwTickCount[1]) > 200)
			{
				g_pCarAABonderDlg->ShowAutoReadyState(m_nUnit);
				m_dwTickCount[1] = GetTickCount();
			}
		}
		if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 20000)
		{
			if (g_clMesCommunication[m_nUnit].m_bLgit_Pause_req == true && g_clMotorSet.GetPcbZMotorPosCheck(m_nUnit, WAIT_POS))		//Z�� ��� ��ġ�϶� ������
			{
				g_clMesCommunication[m_nUnit].m_bLgit_Pause_req = false;	//thread
				g_clDioControl.SetBuzzer(true, BUZZER_ALARM);
				//S6F11 Process State Change Report (EXECUTING)
				g_clMesCommunication[m_nUnit].m_dProcessState[0] = g_clMesCommunication[m_nUnit].m_dProcessState[1];
				g_clMesCommunication[m_nUnit].m_dProcessState[1] = ePAUSE;

				g_clMesCommunication[m_nUnit].m_uAlarmList.clear();

				g_pCarAABonderDlg->m_clUbiGemDlg.EventReportSendFn(PROCESS_STATE_CHANGED_REPORT_10401, "");		//Heavy Alarm�϶��� ���� pause �����Ѵ�.

				//�׸��� s6f25 ������ Resume �˾� �߰�
				TCHAR szLog[SIZE_OF_1K];

				_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] PAUSE COMMAND RECEIVE [STEP : %d]"), g_clTaskWork[m_nUnit].m_nCurrentPcbStep);
				//���⿡ �ڵ����� ���� ���ð����� ��ư �ʿ�
				AddLog(szLog, 0, m_nUnit);

				CString strValue;
				strValue.Format(_T("[Code]:%s\n[Text]:%s"), g_clReportData.rLgit_Pause.PauseCode, g_clReportData.rLgit_Pause.PauteText);
				g_ShowMsgPopup(_T("LGIT_PAUSE"), strValue, RGB_COLOR_RED);


				g_clTaskWork[m_nUnit].m_nCurrentPcbStep = abs(g_clTaskWork[m_nUnit].m_nCurrentPcbStep) * -1;
			}
		}
		//
		//EOL Mode
		// ���� ����
		if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 10000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 20000)
		{
			g_clTaskWork[m_nUnit].m_nCurrentPcbStep = m_clPcbProcess.HomeProcess(g_clTaskWork[m_nUnit].m_nCurrentPcbStep);
		}
		//	���� �غ�
		else if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 20000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 30000)
		{
			g_clTaskWork[m_nUnit].m_nCurrentPcbStep = m_clPcbProcess.AutoReadyProcess(g_clTaskWork[m_nUnit].m_nCurrentPcbStep);
		} 
		//	��ǰ �ε�	
		else if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 30000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 40000)
		{
			g_clTaskWork[m_nUnit].m_nCurrentPcbStep = m_clPcbProcess.Auto_M_PCBLoading(g_clTaskWork[m_nUnit].m_nCurrentPcbStep);
		}
		//align  -> ��Ʈ -> ��ũ -> �̹�����
		//
		//align - Laser - �̹� - chart
		//
		//
		if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 40000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 50000)
		{
			//ALIGN
			//
			g_clTaskWork[m_nUnit].m_nCurrentPcbStep = m_clPcbProcess.AutoPcbSensorAlign(g_clTaskWork[m_nUnit].m_nCurrentPcbStep);
		}
		else if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 50000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 60000)
		{
			//������
			//
			g_clTaskWork[m_nUnit].m_nCurrentPcbStep = m_clPcbProcess.AutoPcbLaser(g_clTaskWork[m_nUnit].m_nCurrentPcbStep);
		}
		else if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 60000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 70000)
		{
			//��Ʈ
			//
			g_clTaskWork[m_nUnit].m_nCurrentPcbStep = m_clPcbProcess.AutoChartInsp(g_clTaskWork[m_nUnit].m_nCurrentPcbStep);    //sfr , oc , rotate , fov, distortion
		}
		else if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 80000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 90000)
		{
			//�̹�����
			//
			g_clTaskWork[m_nUnit].m_nCurrentPcbStep = m_clPcbProcess.Auto_OC_Insp(g_clTaskWork[m_nUnit].m_nCurrentPcbStep);
		}
		else if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 90000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 100000)
		{
			//����
			//
			g_clTaskWork[m_nUnit].m_nCurrentPcbStep = 110000;
		}
		else if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 110000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 120000)
		{
			//end
			g_clTaskWork[m_nUnit].m_nCurrentPcbStep = m_clPcbProcess.AutoEOLFinalSFR(g_clTaskWork[m_nUnit].m_nCurrentPcbStep);
		}
	}
	else if(g_clTaskWork[m_nUnit].m_nCurrentPcbStep == -1 || g_clTaskWork[m_nUnit].m_nCurrentLensStep == -1)
	{
		g_clTaskWork[0].m_bAreaSensorRun = false;		//Active Thread
		g_pCarAABonderDlg->StopAutoProcess(m_nUnit);
	}
	else if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 0 || g_clTaskWork[m_nUnit].m_nCurrentLensStep < 0)
	{
		g_clTaskWork[0].m_bAreaSensorRun = false;		//Active Thread
		g_pCarAABonderDlg->PauseAutoProcess(m_nUnit);
	}
	else
	{
		this->EndThread();
	}
}

