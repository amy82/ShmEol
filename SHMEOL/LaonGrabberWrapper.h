#pragma once

#include "Grabber\LAON\MIU.h"
#include "Grabber\LAON\BoardControl.h"
class CLaonGrabberWrapper
{
public:
	CLaonGrabberWrapper();
	~CLaonGrabberWrapper();

public:	
	void SetUnit(int nUnit){ m_nUnit = nUnit;}

	int SearchDevice();

	int GetDeviceCount();
	bool GetDeviceOpen() { return m_bOpen; }
	int GetCurrentState() { return m_nCurrentCcdState; }
	void SetCurrentState(int nState) { m_nCurrentCcdState = nState; }
	bool GetCcdState();
	void AllocImageBuff();
	void rawReSet(int nMode = 0);		//0 = Raw , 1 = Yuv

    void BoardtInitialize();
	void SensorListInitialize();
	bool IniAnalyze();

	void SetDevice(int nDevice) { m_nDevice = nDevice; }
	int GetDevice() { return m_nDevice; }
	bool OpenDevice();
	bool CloseDevice();
	bool StartGrab();
	bool StopGrab();

	bool StartGrabCcdProcess();
	CString GetErrorStr(int errorCode);
	/*void Shift12to16BitMode(unsigned char* p12bitRaw, unsigned char* p16bitRaw, int nWidth, int nHeight);
	void CCCR_Interpolation(unsigned short* pData, int nWidth, int nHeight);
	void Shift16to12BitMode(unsigned char* pImage, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);*/

	void RawImageSave(CString nType, BYTE* LoadImg, int index,  bool mJpgSaveUse = true);
	void JpgImageSave(IplImage* jpgImg, int index);
	void JpgMatSave(cv::Mat jpgImg, int index);

	//void EncodeCallback(const JXL_ENC_RSP* rsp);
	bool ImageEncode();
	bool ImageDecode(const char* pszFileName, const char* pszFolderName);
	void CopyInspImage(int nType, BYTE* GrabImage, bool sumImageSave = true);
	IplImage* RegionCopy(IplImage* src);

	bool GetCurrent(double* pfCurrent);
	bool ChangePatternMode(int nMode);
	bool ControlISP(bool bOn);
	bool ChangeMono();
	bool ChangeRaw();


	bool PatternImageLoad();
public:
	int m_nUnit;
	char m_cIndexArray[4];
	char m_cDeviceCount;

	TCHAR	strRawFileName[3][SIZE_OF_1K];

	MIU_DEVICE m_stMIUDevice;
	TDATASPEC dTDATASPEC_n;
	IMAGESENSOR_LIST* m_pSID;

	TDATASPEC dSfr_Tdataspec;
	TDATASPEC dBlemish_Tdataspec;
	TDATASPEC dColor_Tdataspec;
	TDATASPEC dRi_Tdataspec;

	std::vector<std::string> vImageFiles;		//¿µ¿ªº° Raw Image List


	//unsigned char* m_pImgBuff8Bit;
	//unsigned char* m_pImgBuff12Bit;

	IplImage* m_pGrabBuff[3];
	IplImage* m_pImageBuff[3];
	//IplImage* m_pImageInspBuff;
	//IplImage* m_pImageInsp8Bit;
	//IplImage* m_pImageInsp8Bit956;


	BYTE* pSumBuffer[10];
	//BYTE* vChartBuffer;
	//byte* vDefectMidBuffer_3000k;	//White Balance, Lens Shading

	BYTE* vRawChartBuffer;
	BYTE* vYuvChartBuffer;
	BYTE* vRawBuffer_3000k;

	//byte* vYuvBuffer_3000k;
	//std::vector<BYTE> vFrameBuffer1(nWidth * nHeight * 2); // mid-level Image
	//std::vector<BYTE> vFrameBuffer2(nWidth * nHeight * 2); // low-level Image

	BYTE* m_pFrameRawBuffer_TP_Ref1[2];
	int NoiseRetryCount;
private:
	bool m_bOpen;
	int m_nCurrentCcdState;
	int m_nDevice;
	int m_nSensorCount;

	bool m_bRcccMoveX;
	bool m_bRcccMoveY;
	bool m_bCheckDir;
	int m_nPixelFormat;

public:

    IBoardControl*	m_pBoard;
    //Grabber.dll
    byte* m_pFrameRawBuffer;
	byte* m_pFrameBMPBuffer;
	byte* m_pTestBuffer;


    //
    HMODULE	 m_hBoardLibrary;
    //
    CString m_strIniFileName;
    CString m_strGrabberDLLVer;
    CString m_strLPMCVer;
    CString selectedIniFile;
    //
    char m_cBoardIndex;
    //
	int getRawSize();
    bool SelectSensor();
    int UiconfigLoad(int index = 0, CString uiPath="");//index = 0 (raw) , index = 1(yuv)
	int SetIni();
    void UpdateVersionInfo();
    
	EDATAFORMAT rDataFormatType(int index);
	EOUTMODE rOutmodeType(int index);
	ESENSORTYPE rSensortypeType(int index);
	EDEMOSAICMETHOD rdemosaicmethodType(int index);
};

