#pragma once


// UXGraph

//! 그래프 컨트롤 클래스 선언
#define BUFFER_SIZE_GRAPH_2D		3
#define BUFFER_SIZE_GRAPH_OVERLAP	5
#define BUFFER_SIZE_PIXEL_GRAPH		1024//8192

class CGraph2DWnd;

class UXGraph : public CWnd
{
	DECLARE_DYNAMIC(UXGraph)

public:
	UXGraph();
	virtual ~UXGraph();

protected:
	DECLARE_MESSAGE_MAP()
	//! 그래프 커서를 가지고 있는 그래프의 index, 0 based
	int m_aiIndex_Overlap_Cursor[2];

	CGraph2DWnd *m_apGraphWnd[2];
public:
	void init();
	afx_msg void OnPaint();

	//
	//
	bool MakeGraphWnd();
	int    m_aiCount_Visible[BUFFER_SIZE_GRAPH_2D];							//! 눈에 보이는 그래프의 개수
	bool Init_Buffser(int iIndex_Plot, int iIndex_Overlap);
	bool   m_abFlag_Visible[BUFFER_SIZE_GRAPH_2D][BUFFER_SIZE_GRAPH_OVERLAP];	//! true이면 그래프를 눈에 보이게 한다.
																				//! =========================================================================================================
																				//! 그래프 입력 데이터 버퍼	
	double m_adDataX[BUFFER_SIZE_GRAPH_2D][BUFFER_SIZE_GRAPH_OVERLAP][BUFFER_SIZE_PIXEL_GRAPH];
	double m_adDataY[BUFFER_SIZE_GRAPH_2D][BUFFER_SIZE_GRAPH_OVERLAP][BUFFER_SIZE_PIXEL_GRAPH];
	int    m_aiDataSize[BUFFER_SIZE_GRAPH_2D][BUFFER_SIZE_GRAPH_OVERLAP];

	//! 그래프 상의 특정 지점에 X축에 수직선을 표시한다.
	double m_adData_MTF4[BUFFER_SIZE_GRAPH_2D][BUFFER_SIZE_GRAPH_OVERLAP];	//! MTF(N/4) X축 값
	double m_adData_MTF8[BUFFER_SIZE_GRAPH_2D][BUFFER_SIZE_GRAPH_OVERLAP];	//! MTF(N/8) X축 값
	double m_adData_MTF50[BUFFER_SIZE_GRAPH_2D][BUFFER_SIZE_GRAPH_OVERLAP];	//! MTF50	 X축 값

	int DrawGraph(int iIndex_Plot);				/* iMode 0 : 수동모드 1 : 자동모드 */
	void DrawBarGraph(int nID);
	int GetWindowRect_FromUI(int iUID, CWnd* pParentWnd, CRect &rcRet);
	void ReleaseGraphWnd();

};
