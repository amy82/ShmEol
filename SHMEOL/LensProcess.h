#pragma once
class CLensProcess
{
public:
	CLensProcess(void);
	~CLensProcess(void);

public:
	void SetUnit(int nUnit){ m_nUnit = nUnit;}

	int AutoLensReq(int nStep);
	int AutoLensLoading(int nStep);

	//int AutoLensPickup(int nStep);



	int LensIoRetryCount;
private:
	int m_nUnit;
	bool m_bFlagSocketReq;
};

