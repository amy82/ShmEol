#pragma once

#include "PciExpWrapper.h"
#include "pci_error.h"

class CPriGrabberWrapper
{
public:
	CPriGrabberWrapper();
	~CPriGrabberWrapper();

public:
	void SetUnit(int nUnit){ m_nUnit = nUnit;}
	
	bool GetDeviceOpen() { return m_bOpen; }
	int GetCurrentState() { return m_nCurrentState; }
	void SetCurrentState(int nState) { m_nCurrentState = nState; }
	int GetWidth() { return m_nWidth; }
	int GetHeight() { return m_nHeight; }
	bool GetCcdState();
	void AllocImageBuff();

	void SetDevice(int nDevice) { m_nDevice = nDevice; }
	bool OpenDevice();
	bool CloseDevice();
	bool ConnectDevice();
	bool DisconnectDevice();
	bool InitBoard();
	bool InitSensor();
	bool StartGrab();
	bool StopGrab();

	bool OpenCcdProcess();
	
	int ChkGrabDone(int* nCurrentIndex);
	int CopyImgInfo(int nIndexNum);
	int InfoIsValidFrame();
	int InfoGetFrameCnt(int* pFrameCount);
	int ImageCopySafe(int nIndexNum, int** nBuffer);
	void Bit12ToRaw8(unsigned char *p12Bit, unsigned char *pRaw8);
	void Raw10ToRaw8(unsigned char *pRaw10, unsigned char *pRaw8);
	//void Raw12ToRaw8(unsigned char* pRaw12, unsigned char* pRaw8, int nSizeX, int nSizeY);
	//void RawToBmp(unsigned char *pRaw8, unsigned char *pBMP, int image_width, int image_height, int bayer_format);

	//void Raw12BitToRaw8(unsigned char *pRaw10, unsigned char *pRaw8, int nWidth, int nHeight);
	//void RawToBmp(unsigned char *pRaw8, unsigned char *pBMP, int nWidth, int nHeight, int nBayerFormat);

	void PriCopyInspImage(int nType);
	IplImage* RegionCopy(IplImage* src);

	bool GetCurrent(float* pdCurrent);
	bool ChangePatternMode(int nMode);
	
private:
	int m_nUnit;
	bool m_bOpen;
	int m_nCurrentState;
	int m_nDevice;
	int m_nWidth;
	int m_nHeight;
	CPciExpWrapper m_clPciExp;
	

public:
	unsigned char* m_pImgBuff8Bit;
	unsigned char* m_pImgBuff12Bit;

	IplImage* m_pGrabBuff[3];
	IplImage* m_pImageBuff[3];
	IplImage* m_pImageInspBuff;
	IplImage* m_pImageInsp8Bit;
	IplImage* m_pImageInsp8Bit956;	
};