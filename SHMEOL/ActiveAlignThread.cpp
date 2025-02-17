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
	m_clLensProcess.SetUnit(nUnit);
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

