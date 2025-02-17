#pragma once

#include "utility\basethread\basethread.h"

class CCcdCvtColorThread :
	public CBaseThread
{
public:
	CCcdCvtColorThread(void);
	~CCcdCvtColorThread(void);

public:
	void SetUnit(int nUnit){ m_nUnit = nUnit; }

protected:
	virtual void ThreadConstructor();
	virtual void ThreadDestructor();
	virtual void ThreadCallBack();

private:
	int m_nUnit;
};

