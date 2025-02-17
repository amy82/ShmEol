// UXGraph.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "../../AutoInsp.h"
#include "../../AutoInspDlg.h"
#include "UXGraph.h"
#include "Graph2D\Graph2DExtendWnd.h"
// UXGraph

IMPLEMENT_DYNAMIC(UXGraph, CWnd)

UXGraph::UXGraph()
{
	int i = 0, j = 0;
	/*for (i = 0; i < BUFFER_SIZE_GRAPH_2D; i++)
	{
		m_apGraphWnd[i] = NULL;

		m_aiIndex_Overlap_Cursor[i] = 0;

		m_aiCount_Visible[i] = BUFFER_SIZE_GRAPH_OVERLAP;

		for (j = 0; j < BUFFER_SIZE_GRAPH_OVERLAP; j++)
		{
			Init_Buffser(i, j);

			m_abFlag_Visible[i][j] = true;
		}
	}*/
	
}

UXGraph::~UXGraph()
{
}


BEGIN_MESSAGE_MAP(UXGraph, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()
void UXGraph::init()
{
	//MakeGraphWnd();
}


void UXGraph::OnPaint()
{
	
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CWnd::OnPaint()을(를) 호출하지 마십시오.
}
void UXGraph::DrawBarGraph(int nID)
{
	CString sTemp;
	HWND hWnd = theApp.MainDlg->GetDlgItem(nID)->m_hWnd;
	CDC pDC;
	HDC hDC = ::GetDC(hWnd);
	pDC.Attach(hDC);

	CRect rcClient;
	theApp.MainDlg->GetDlgItem(nID)->GetClientRect(rcClient);
	CBrush Brush;
	CBrush* pOldBrush;
	Brush.CreateSolidBrush(RGB(255, 255, 255));//그래프 배경색
	pOldBrush = pDC.SelectObject(&Brush);
	pDC.FillRect(rcClient, &Brush);

	int TopGap = 50;
	int BottomGap = 20;
	int Graph_Width = rcClient.right - rcClient.left;
	int Graph_Height = rcClient.bottom - rcClient.top;
	int barGraphX = 0;
	int barWidth = 20;

	CPen* pOldPen; 
	CPen pen_LineBase; CPen pen_LineVertical; 

	CFont font_LimitVal; CFont font_BarName; CFont* pOldFont;
	CFont font_Value;
	pen_LineBase.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	//
	pen_LineVertical.CreatePen(PS_SOLID, 1, RGB(200, 200, 200));		//가로 옅은 선
	pOldPen = pDC.SelectObject(&pen_LineBase);
	//그래프 하단 짙은선
	pDC.MoveTo(5, Graph_Height - BottomGap);
	pDC.LineTo(Graph_Width - 5, Graph_Height - BottomGap);
	//
	pOldPen = pDC.SelectObject(&pen_LineVertical);
	//가로 점선 세팅
	int startX = 35;//가로라인 시작 위치 x
	int poxY = 0;
	int endGap = 20;
	int lineYGap = (Graph_Height - BottomGap - TopGap) / 5;
	CSize fontSize;
	sTemp = "0.1";
	pDC.SetBkMode(TRANSPARENT);//글자색 배경 투명
							   //
	double gapNum = 0.0;
	font_Value.CreateFont(15, 6, 0, 0, FW_DONTCARE, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_STROKE_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "arial");
	pOldFont = pDC.SelectObject(&font_Value);
	pDC.SetTextColor(RGB(100, 100, 100));
	for (int i = 0; i < 5; i++)
	{
		gapNum = ((5-i) / 5.0);//(i % 5);
		sTemp.Format("%.1lf", gapNum);

		poxY = (lineYGap * i) + TopGap;
		pDC.MoveTo(startX, poxY);
		pDC.LineTo(Graph_Width - endGap, poxY);
		fontSize = pDC.GetTextExtent(sTemp);
		pDC.TextOut(10, poxY - (fontSize.cy / 2), sTemp);
	}

	//
	font_LimitVal.CreateFont(16, 7, 0, 0, FW_DONTCARE, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_STROKE_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "arial");
	pOldFont = pDC.SelectObject(&font_LimitVal);


	//막대 그래프 셋
	font_BarName.CreateFont(15, 6, 0, 0, FW_DONTCARE, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_STROKE_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "arial");
	//
	pOldFont = pDC.SelectObject(&font_BarName);
	pDC.SetTextColor(RGB(0, 0, 0));
	double MtfSfr[5];
	if (nID == IDC_PIC_BARGRAPH1)//if (sysData.m_iProductComp == 1)
	{
		MtfSfr[0] = 1.0;//(MandoInspLog.dMTF_PostUV[0] + MandoInspLog.dMTF_PostUV[1] + MandoInspLog.dMTF_PostUV[2] + MandoInspLog.dMTF_PostUV[3]) / 4;
		MtfSfr[1] = 0.8;//(MandoInspLog.dMTF_PostUV[4] + MandoInspLog.dMTF_PostUV[5]) / 2;
		MtfSfr[2] = 0.6;//(MandoInspLog.dMTF_PostUV[6] + MandoInspLog.dMTF_PostUV[7]) / 2;
		MtfSfr[3] = 0.4;//(MandoInspLog.dMTF_PostUV[8] + MandoInspLog.dMTF_PostUV[9]) / 2;
		MtfSfr[4] = 0.2;//(MandoInspLog.dMTF_PostUV[10] + MandoInspLog.dMTF_PostUV[11]) / 2;
	}
	else
	{
		MtfSfr[0] = 0.9;
		MtfSfr[1] = 0.7;
		MtfSfr[2] = 0.6;
		MtfSfr[3] = 0.5;
		MtfSfr[4] = 0.3;
	}
	COLORREF _BarColor;
	const char *labels[] = { "Center", "top", "Bottom", "Left", "Right" };
	int textX = 0;
	CSize display_size;

	for (int i = 0; i < 5; i++)//for (int i = 0; i<MAX_MTF_NO; i++)
	{

		if (i == 0)			_BarColor = RGB(0, 0, 255);
		else if (i == 1)	_BarColor = RGB(255, 0, 0);
		else if (i == 2)	_BarColor = RGB(0, 255, 0);
		else if (i == 3)	_BarColor = RGB(63, 0, 153);
		else if (i == 4)	_BarColor = RGB(0, 216, 255);
		CPen BarPen;
		CBrush Barbrush;
		BarPen.CreatePen(PS_DOT, 3, _BarColor);    // 빨간색 펜을 생성
		CPen* BaroldPen = pDC.SelectObject(&BarPen);
		Barbrush.CreateSolidBrush(_BarColor);     // 오렌지색 채움색을 생성
		CBrush* BaroldBrush = pDC.SelectObject(&Barbrush);
		barGraphX = (Graph_Width - 5) / 6 * (i + 1);
		pDC.Rectangle(
			barGraphX,
			(Graph_Height - BottomGap) - (int)(MtfSfr[i] * (Graph_Height - BottomGap - TopGap) + 0.5) + 1,
			barGraphX + barWidth,
			Graph_Height - BottomGap - 1);
		pDC.SelectObject(BaroldBrush);
		pDC.SelectObject(BaroldPen);

		//////////////////////////////////////////////////////////////////////////////////////////
		if (MtfSfr[i] < 0.0) MtfSfr[i] = 0.0;
		if (MtfSfr[i] > 1.0) MtfSfr[i] = 1.0;
		sTemp.Format("%.3lf", MtfSfr[i]);
		display_size = pDC.GetTextExtent(sTemp);
		textX = barGraphX + (barWidth / 2) - (display_size.cx / 2);

		pDC.SetBkMode(TRANSPARENT);//글자색 배경 투명
		pDC.SetTextColor(RGB(0, 0, 0));
		pDC.TextOut(textX, (Graph_Height - BottomGap) - (int)(MtfSfr[i] * (Graph_Height - BottomGap - TopGap) + 0.5) - 15, sTemp);

		pDC.SetTextColor(_BarColor);
		textX = barGraphX + (barWidth / 2) - (display_size.cx / 2);
		display_size = pDC.GetTextExtent(labels[i]);
		pDC.TextOut(barGraphX + (barWidth / 2) - (display_size.cx / 2), (Graph_Height - BottomGap) + 2, labels[i]);
		//pDC.DrawText(labels[i], CRect(100, 100, 320, 240), NULL);
		//////////////////////////////////////////////////////////////////////////////////////////
	}

	pDC.SelectObject(pOldPen);
	pen_LineBase.DeleteObject();
	pen_LineVertical.DeleteObject();

	pDC.SelectObject(pOldBrush);
	Brush.DeleteObject();

	pDC.SelectObject(pOldFont);
	font_Value.DeleteObject();
	font_LimitVal.DeleteObject();
	font_BarName.DeleteObject();

	pDC.Detach();
	::ReleaseDC(hWnd, hDC);
}

// !그래프 컨트롤 생성
bool UXGraph::MakeGraphWnd()
{
	ReleaseGraphWnd();

	int iIndex_Failed = -1;
	int iRet = 0;
	int i = 0, j = 0;
    CAutoInspDlg* pMainDlg = (CAutoInspDlg*)::AfxGetMainWnd();
	for (i = 0; i < BUFFER_SIZE_GRAPH_2D; i++)
	{
		m_apGraphWnd[i] = new CGraph2DWnd;
		if (m_apGraphWnd[i] == NULL)
		{
			iIndex_Failed = i;
			break;
		}
	}
	if (iIndex_Failed >= 0)
	{
		return false;
	}

	BOOL bCreateWnd = FALSE;
	for (i = 0; i < BUFFER_SIZE_GRAPH_2D; i++)
	{
		bCreateWnd = m_apGraphWnd[i]->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, CRect(0, 0, 0, 0), pMainDlg, 0x0000, NULL);
		if (bCreateWnd == FALSE)
		{
			iIndex_Failed = i;
			break;
		}
	}
	if (iIndex_Failed >= 0)
	{
		return false;
	}

	strGraph2D_Y_Axis_Info strAxisYInfo;	//! Y축
	strGraph2DResourceInfo strResourceInfo;	//! X축

	for (i = 0; i < BUFFER_SIZE_GRAPH_2D; i++)
	{
		//! 각각 리소스 정보를 갖도록 함
		m_apGraphWnd[i]->MakeResourcePtr();

		//! 5개의 그래프를 그릴 수 있게 한다.
		m_apGraphWnd[i]->MakePlotBuffer(BUFFER_SIZE_GRAPH_OVERLAP);

		//! 그래프 컨트롤의 고유 식별 index를 설정
		m_apGraphWnd[i]->SetPlotIndex(i);

		//! 여러 개의 그래프라도 Y축은 1개이다.
		m_apGraphWnd[i]->m_bMultiPlotOneAxis = true;

		m_apGraphWnd[i]->m_bCursorEventMsg = true;
		m_apGraphWnd[i]->m_bRegionCursorEventMsg = false;
		m_apGraphWnd[i]->m_bRegionCursorRMouseDownChk = false;
		m_apGraphWnd[i]->m_bXAutoRangeRegionCursor = false;
		m_apGraphWnd[i]->m_bYAutoRangeRegionCursor = false;

		//! 추가 될 커서 선 표시 방식 설정
		m_apGraphWnd[i]->m_eCursorLineMode = E_GRAPH2D_CUROSR_LINE_X;

		m_apGraphWnd[i]->m_eCursorAllSearchMode = E_GRAPH2D_CURSOR_ALL_SEARCH_NONE;
		m_apGraphWnd[i]->m_bXValueLineRMouseDownChk = false;
		m_apGraphWnd[i]->m_bChildCursorRMouseDownChk = false;
		m_apGraphWnd[i]->m_bAutoDrawCompleteMsg = false;
		m_apGraphWnd[i]->m_bAxisYEventMsg = false;
		m_apGraphWnd[i]->m_bAuxCursorRMouseDownChk = false;

		for (j = 0; j < BUFFER_SIZE_GRAPH_OVERLAP; j++)
		{
			m_apGraphWnd[i]->GetResourceYInfo(strAxisYInfo, j);
			strAxisYInfo.bShowGraph = false;

			//! 그래프 색상
			switch (j)
			{
			case 0:
			{
				strAxisYInfo.clrData = RGB(0, 0, 255);
			}
			break;
			case 1:
			{
				strAxisYInfo.clrData = RGB(255, 0, 0);
			}
			break;
			case 2:
			{
				strAxisYInfo.clrData = RGB(0, 255, 0);
			}
			break;
			case 3:
			{
				strAxisYInfo.clrData = RGB(63, 0, 153);
			}
			break;
			case 4:
			{
				strAxisYInfo.clrData = RGB(0, 216, 255);
			}
			break;
			}//! switch(j)

			 //! 그래프에서 Y축 Range는 그래프 데이터가 튀지 않는 한에는 '0 ~ 1'로 고정한다. 
			strAxisYInfo.strAxisInfo.eAutoRangeReservedMax = E_GRAPH2D_AUTO_RANGE_RESERVED_CONSIDER;
			strAxisYInfo.strAxisInfo.eAutoRangeReservedMin = E_GRAPH2D_AUTO_RANGE_RESERVED_CONSIDER;
			strAxisYInfo.strAxisInfo.eMarginType = E_GRAPH2D_RANGE_MARGIN_NONE;
			strAxisYInfo.strAxisInfo.dbAutoRangeReservedMax = 1.0;
			strAxisYInfo.strAxisInfo.dbAutoRangeReservedMin = 0.;
			strAxisYInfo.iLineWidth = 3;

			strAxisYInfo.strAxisInfo.iGridTextPrecision = 3;
			strAxisYInfo.strAxisInfo.iCursorTextPrecision = 3;
			m_apGraphWnd[i]->SetResourceYInfo(strAxisYInfo, j);

		}//! for ( j = 0; j < BUFFER_SIZE_GRAPH_OVERLAP; j++ )




		 ////////////////////// 정재호 수정..
		m_apGraphWnd[i]->GetResourceInfo(strResourceInfo);
		strResourceInfo.iAxisThickness = 1;
		strResourceInfo.clrEntireBackGround = RGB(231, 231, 231);	//! 그래프 바탕 색상
		strResourceInfo.strAxisInfoX.iCursorTextPrecision = 0;

		/* LKS */
		//////////////////////////////////////////////////////////////////////////
		if (i < 2)
		{
			strResourceInfo.strAxisInfoX.eGridTextType = E_GRAPH2D_GRID_DOUBLE;	//E_GRAPH2D_GRID_INTEGER;
			strResourceInfo.strAxisInfoX.bIncrementGrid = false;	//! Modify by LHW (2013/3/26)
			strResourceInfo.strAxisInfoX.dbIncrementGrid = -5.0;
			strResourceInfo.strAxisInfoX.iGridTextPrecision = 3;//0;
			strResourceInfo.strAxisInfoX.bDirection_Plus = false;	//! Added by LHW (2013/3/26)
		}
		else
		{
			strResourceInfo.strAxisInfoX.eGridTextType = E_GRAPH2D_GRID_DOUBLE;//E_GRAPH2D_GRID_INTEGER;
			strResourceInfo.strAxisInfoX.bIncrementGrid = false;
			strResourceInfo.strAxisInfoX.dbIncrementGrid = 5.0;
			strResourceInfo.strAxisInfoX.iGridTextPrecision = 3;//0;
			strResourceInfo.strAxisInfoX.bDirection_Plus = true;		//! Added by LHW (2013/3/26)
		}
		//////////////////////////////////////////////////////////////////////////

		strResourceInfo.strMainTitleInfo.bShow = true;
		strResourceInfo.strMainTitleInfo.eAlign = E_GRAPH2D_TITLE_ALIGN_CENTER;
		m_apGraphWnd[i]->SetResourceInfo(strResourceInfo);

		//! <------------------------------------------------------------
		//! X축 특정값 표시선 추가, X축에 수직선
		//! 추가되는 순서에 주의한다. 
		strValueLineXInfo strXLineInfo;

		strXLineInfo.InitInfo();
		strXLineInfo.bShow = false;
		strXLineInfo.dbValue = 0.;
		strXLineInfo.clrValue = RGB(255, 0, 0);
		strXLineInfo.iLineWidth = 1;
		strXLineInfo.szText.Format(_T("[%d] MTF(N/4)"), j + 1);
		m_apGraphWnd[i]->AddXValueLine(strXLineInfo);

		strXLineInfo.InitInfo();
		strXLineInfo.bShow = false;
		strXLineInfo.dbValue = 0.;
		strXLineInfo.clrValue = RGB(0, 0, 255);
		strXLineInfo.iLineWidth = 1;
		strXLineInfo.szText.Format(_T("[%d] MTF(N/8)"), j + 1);
		m_apGraphWnd[i]->AddXValueLine(strXLineInfo);

		strXLineInfo.InitInfo();
		strXLineInfo.bShow = false;
		strXLineInfo.dbValue = 0.;
		strXLineInfo.clrValue = RGB(255, 128, 0);
		strXLineInfo.iLineWidth = 1;
		strXLineInfo.szText.Format(_T("[%d] MTF50"), j + 1);
		m_apGraphWnd[i]->AddXValueLine(strXLineInfo);
		//! <------------------------------------------------------------

		//! 그래프의 X, Y축 이름을 설정
		m_apGraphWnd[i]->SetCaptionX(_T(""));
		m_apGraphWnd[i]->SetCaptionY(_T("MTF"), _T(""));

		m_apGraphWnd[i]->GetResourceInfo(strResourceInfo);
		strResourceInfo.strMainTitleInfo.szTitle = _T("SFR");
		m_apGraphWnd[i]->SetResourceInfo(strResourceInfo);

		//! 메시지를 받을 핸들 설정
		m_apGraphWnd[i]->m_hMsgHandle = theApp.MainDlg->m_hWnd;
	}

	CRect rcGraph;
	
	/* Through Graph */
	//iRet = GetWindowRect_FromUI(IDC_STATIC_GRAPH1, pMainDlg, rcGraph);
	//theApp.MainDlg->ScreenToClient(rcGraph);
	//m_apGraphWnd[0]->MoveWindow(rcGraph);
	/* Fine Graph */
	//iRet = GetWindowRect_FromUI(IDC_STATIC_GRAPH3, pMainDlg, rcGraph);
	//theApp.MainDlg->ScreenToClient(rcGraph);
	//m_apGraphWnd[1]->MoveWindow(rcGraph);
	/* SFR Graph */
	//iRet = GetWindowRect_FromUI(IDC_STATIC_GRAPH2, pMainDlg, rcGraph);
	//theApp.MainDlg->ScreenToClient(rcGraph);
	//m_apGraphWnd[2]->MoveWindow(rcGraph);

	for (i = 0; i < BUFFER_SIZE_GRAPH_2D; i++)
	{
		m_apGraphWnd[i]->m_bChanged = true;
	}

	return true;
}
void UXGraph::ReleaseGraphWnd()
{
	int i = 0;
	for (i = 0; i < BUFFER_SIZE_GRAPH_2D; i++)
	{
		if (m_apGraphWnd[i] != NULL)
		{
			m_apGraphWnd[i]->DestroyWindow();

			delete m_apGraphWnd[i];
			m_apGraphWnd[i] = NULL;
		}
	}
}
//! 그래프에 데이터를 입력한다. 
int UXGraph::DrawGraph(int iIndex_Plot)
{
	if (iIndex_Plot < 0 || iIndex_Plot >= BUFFER_SIZE_GRAPH_2D)
	{
		return -1;
	}

	int j = 0;
	//	bool bRet = false;
	int iIndex_Line_X_MTF4 = 0;
	int iIndex_Line_X_MTF8 = 0;
	int iIndex_Line_X_MTF50 = 0;

	strGraph2D_Y_Axis_Info strAxisYInfo;	//! Y축
	strValueLineXInfo      strXLineInfo;	//! X축

											//! 1) 그래프에 데이터를 입력한다. 
											//! 2) 만약, 커서 (Mouse로 조작 가능한 그래프 데이터 표시 기능)가 없으면 추가한다. 
											//! 3) 그래프를 다시 그린다. 

	if (m_apGraphWnd[iIndex_Plot] != NULL)
	{
		if (iIndex_Plot == 0)
		{
			for (j = 0; j < BUFFER_SIZE_GRAPH_OVERLAP; j++)
			{
				//! <-----------------------------------------------------------
				//! 그래프가 눈에 보이는 여부를 설정한다.
				m_apGraphWnd[iIndex_Plot]->GetResourceYInfo(strAxisYInfo, j);

				m_aiDataSize[iIndex_Plot][j] = 50;// Task.m_iCnt_Step_AA_Total;

				if (m_aiDataSize[iIndex_Plot][j] <= 0)
				{
					strAxisYInfo.bShowGraph = false;
				}
				else
				{
					strAxisYInfo.bShowGraph = m_abFlag_Visible[iIndex_Plot][j];
				}

				m_apGraphWnd[iIndex_Plot]->SetResourceYInfo(strAxisYInfo, j);

				int iIndex = 0;

				if (true)//if (Task.m_bFlag_Decrease_SFR == true)
				{
					iIndex = 10;// model.m_iCnt_Check_SFR;
				}

				for (int i_tmp = iIndex; i_tmp<m_aiDataSize[iIndex_Plot][j]; i_tmp++)
				{
#if (____MODEL_NAME == VISTEON) //pcb Tilt
					m_adDataX[iIndex_Plot][j][i_tmp - iIndex] = 3.5* -1;// Task.SFR.fMotorPos[i_tmp][theApp.MainDlg->TITLE_MOTOR_Z] * -1;
#elif  (____MODEL_NAME == CONTISIDEMIRRO) //Lens Tilt
					m_adDataX[iIndex_Plot][j][i_tmp - iIndex] = Task.SFR.fMotorPos[i_tmp][theApp.MainDlg->TITLE_MOTOR_Z];
					//움직이는 Z축 값 부호에 따라 다르게 
#endif

					m_adDataY[iIndex_Plot][j][i_tmp - iIndex] = 0.01;// Task.SFR.fSfrN4[i_tmp][j];
				}

				//! 그래프에 데이터 입력
				//m_apGraphWnd[i]->SetPlotData(m_adDataX[i], m_adDataY[i], m_aiDataSize[i]);
				m_apGraphWnd[iIndex_Plot]->SetPlotData(m_adDataX[iIndex_Plot][j], m_adDataY[iIndex_Plot][j], m_aiDataSize[iIndex_Plot][j] - iIndex, j);

			}
			//! <-----------------------------------------------------------------------------------------------------------------------------------------



		}
		else if (iIndex_Plot == 1)
		{
			for (j = 0; j < BUFFER_SIZE_GRAPH_OVERLAP; j++)
			{
				//! <-----------------------------------------------------------
				//! 그래프가 눈에 보이는 여부를 설정한다.
				m_apGraphWnd[iIndex_Plot]->GetResourceYInfo(strAxisYInfo, j);

				m_aiDataSize[iIndex_Plot][j] = 12;// Task.m_iCnt_Step_AA_Total - Task.m_iCnt_Second_AA_Start;

				if (m_aiDataSize[iIndex_Plot][j] <= 0)
				{
					strAxisYInfo.bShowGraph = false;
				}
				else
				{
					strAxisYInfo.bShowGraph = m_abFlag_Visible[iIndex_Plot][j];
				}

				m_apGraphWnd[iIndex_Plot]->SetResourceYInfo(strAxisYInfo, j);

				for (int i_tmp = 0; i_tmp<m_aiDataSize[iIndex_Plot][j]; i_tmp++)
				{
#if (____MODEL_NAME == VISTEON ) //pcb Tilt
					m_adDataX[iIndex_Plot][j][i_tmp] = 3.4 * -1;// Task.SFR.fMotorPos[i_tmp + Task.m_iCnt_Second_AA_Start][theApp.MainDlg->TITLE_MOTOR_Z] * -1;
#elif  (____MODEL_NAME == CONTISIDEMIRRO) //Lens Tilt
					m_adDataX[iIndex_Plot][j][i_tmp] = Task.SFR.fMotorPos[i_tmp + Task.m_iCnt_Second_AA_Start][theApp.MainDlg->TITLE_MOTOR_Z];
#endif


					m_adDataY[iIndex_Plot][j][i_tmp] = 1.11;// Task.SFR.fSfrN4[i_tmp + Task.m_iCnt_Second_AA_Start][j];
															//////////////////////////////////////////////////////////////////////////////////////////
				}

				m_apGraphWnd[iIndex_Plot]->SetPlotData(m_adDataX[iIndex_Plot][j], m_adDataY[iIndex_Plot][j], m_aiDataSize[iIndex_Plot][j], j);
			}
		}


		m_apGraphWnd[iIndex_Plot]->m_bChanged = true;
		m_apGraphWnd[iIndex_Plot]->Invalidate();
	}

	return 1;
}
// UXGraph.cpp : 구현 파일입니다.
//
//! 입력한 리소스의 사각 영역을 가져온다.
int UXGraph::GetWindowRect_FromUI(int iUID, CWnd* pParentWnd, CRect &rcRet)
{
	rcRet.SetRectEmpty();

	//! 입력값의 유효성 검사
	if (pParentWnd == NULL)
	{
		return -1;
	}

	//! 리소스 ID에 해당하는 컨트롤의 유효성 검사
	CWnd* pWnd = NULL;
	pWnd = pParentWnd->GetDlgItem(iUID);
	if (pWnd == NULL)
	{
		return -2;
	}

	pWnd->GetWindowRect(&rcRet);

	return 1;
}


bool UXGraph::Init_Buffser(int iIndex_Plot, int iIndex_Overlap)
{
	if (iIndex_Plot < 0 || iIndex_Plot >= BUFFER_SIZE_GRAPH_2D)
	{
		return false;
	}
	if (iIndex_Overlap < 0 || iIndex_Overlap >= BUFFER_SIZE_GRAPH_OVERLAP)
	{
		return false;
	}

	int i = 0;
	for (i = 0; i < BUFFER_SIZE_PIXEL_GRAPH; i++)
	{
		m_adDataX[iIndex_Plot][iIndex_Overlap][i] = 0.;
		m_adDataY[iIndex_Plot][iIndex_Overlap][i] = 0.;
	}

	m_aiDataSize[iIndex_Plot][iIndex_Overlap] = 0;

	m_adData_MTF4[iIndex_Plot][iIndex_Overlap] = 0.;
	m_adData_MTF8[iIndex_Plot][iIndex_Overlap] = 0.;
	m_adData_MTF50[iIndex_Plot][iIndex_Overlap] = 0.;

	return true;
}
