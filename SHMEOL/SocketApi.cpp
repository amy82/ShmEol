#include "stdafx.h"
#include "SocketApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSocketApi::CSocketApi()
{
	m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	ResetEvent(m_hEvent);
}


CSocketApi::~CSocketApi()
{

}
