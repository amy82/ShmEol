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
//	스레드 생성자
//
//-----------------------------------------------------------------------------
void CActiveAlignThread::ThreadConstructor()
{
	m_nStep = 10000;
}

//-----------------------------------------------------------------------------
//
//	스레드 소멸자
//
//-----------------------------------------------------------------------------
void CActiveAlignThread::ThreadDestructor()
{

}

//-----------------------------------------------------------------------------
//
//	스레드 콜백
//
//-----------------------------------------------------------------------------
void CActiveAlignThread::ThreadCallBack()
{
#ifdef ON_LINE_SOCKET
	//TCHAR szLog[SIZE_OF_1K];

	//if (g_pCarAABonderDlg->GetAAMainConnect() == false)
	//{//! Main과 통신이 끊어졌을 경우 일시정지.
	//	g_pCarAABonderDlg->PauseAutoProcess(m_nUnit);
	//	_stprintf_s(szLog, SIZE_OF_1K, _T("[AUTO] MAIN PC 통신이 끊어졌습니다."));
	//	//AddLog(szLog, 1, 999);
 //       AddLog(szLog, 1, 0);
 //       AddLog(szLog, 1, 1);
	//	return;
	//}
#endif
	
	// PCB 동작
	if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= g_clTaskWork[m_nUnit].m_nStartStep && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < g_clTaskWork[m_nUnit].m_nEndStep)
	{
		if ((g_clTaskWork[m_nUnit].m_nAutoFlag != MODE_AUTO) && (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 30000)) 
		{
			g_pCarAABonderDlg->StopAutoProcess(m_nUnit);
			return;
		}

		// 원점 버튼 깜빡임
		if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 10000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 20000)
		{
			if ((GetTickCount() - m_dwTickCount[0]) > 500)
			{
				g_pCarAABonderDlg->ShowHomeState(m_nUnit);
				m_dwTickCount[0] = GetTickCount();
			}
		}

		// 운전준비 버튼 깜빡임
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
		// 원점 복귀
		if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 10000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 20000)
		{
			g_clTaskWork[m_nUnit].m_nCurrentPcbStep = m_clPcbProcess.HomeProcess(g_clTaskWork[m_nUnit].m_nCurrentPcbStep);
		}
		//	운전 준비
		else if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 20000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 30000)
		{
			g_clTaskWork[m_nUnit].m_nCurrentPcbStep = m_clPcbProcess.AutoReadyProcess(g_clTaskWork[m_nUnit].m_nCurrentPcbStep);
		} 
		//	제품 로딩	
		else if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 30000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 40000)
		{
			g_clTaskWork[m_nUnit].m_nCurrentPcbStep = m_clPcbProcess.Auto_M_PCBLoading(g_clTaskWork[m_nUnit].m_nCurrentPcbStep);
		}
		//align  -> 차트 -> 다크 -> 이물광원
		//
		//align - Laser - 이물 - chart
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
			//레이저
			//
			g_clTaskWork[m_nUnit].m_nCurrentPcbStep = m_clPcbProcess.AutoPcbLaser(g_clTaskWork[m_nUnit].m_nCurrentPcbStep);
		}
		else if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 60000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 70000)
		{
			//차트
			//
			g_clTaskWork[m_nUnit].m_nCurrentPcbStep = m_clPcbProcess.AutoChartInsp(g_clTaskWork[m_nUnit].m_nCurrentPcbStep);    //sfr , oc , rotate , fov, distortion
		}
		else if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 80000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 90000)
		{
			//이물광원
			//
			g_clTaskWork[m_nUnit].m_nCurrentPcbStep = m_clPcbProcess.Auto_OC_Insp(g_clTaskWork[m_nUnit].m_nCurrentPcbStep);
		}
		else if (g_clTaskWork[m_nUnit].m_nCurrentPcbStep >= 90000 && g_clTaskWork[m_nUnit].m_nCurrentPcbStep < 100000)
		{
			//점프
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

