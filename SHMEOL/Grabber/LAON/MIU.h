//-----------------------------------------------------------------------------
//
//	
//
//-----------------------------------------------------------------------------
#ifndef __MIU_H__
#define __MIU_H__


#include "LPMC500DLLEx.h"
//#include "../../Algorithm/LGIT/LibACMISCommon/ACMISCommon.h"
#include "../../Library/Inspection/Include/LibACMISCommon/ACMISCommon.h"
#define DATA_SIZE_MAX					1024
#define PAYLOAD_SIZE					1020
#define REGISTER_ADDRDATA_SIZE          4
#define MAX_REGISTER_COUNT				256

#define RESIZE_MINUSSTEP				0.95
#define RESIZE_PLUSSTEP					1.05

/******************************************************************************
*
*   MIU Data Transfer 구조체
*
*******************************************************************************/
typedef struct strArrayRegister
{
	unsigned short 		nAddress;          // Address
	unsigned short 		nData;             // Data   
} STRREGISTER, *PSTRREGISTER;


typedef union unionMIUData
{
	unsigned char   	aData[DATA_SIZE_MAX];
	STRREGISTER     	aRegisterData[MAX_REGISTER_COUNT];
} MIU_DATA, *PMIU_DATA;

//=================================================================================================
// Structure of sensor's information
//=================================================================================================
typedef struct _SENSOR_INFORMATION
{
	char				szResolution[256];		//  Resolution 
	int					nOutputWidth;           //  Image size Width
	int					nOutputHeight;          //  Image size Height
	unsigned int		iPixelFormat;           //  Pixel Format
}SENSOR_INFORMATION;

//=================================================================================================
// Structure of Sensor List
//=================================================================================================
typedef struct _IMAGESENSOR_LIST
{
	char				szSensorName[256];	// Sensor Name
	int					nInfoCount;         // Info Count
	SENSOR_INFORMATION* pInfo;	            // Sensor Information Pointer
}IMAGESENSOR_LIST;

/******************************************************************************
*
*   MIU Device 구조체
*
*******************************************************************************/
typedef struct strMIUDevice
{
	unsigned char       bRccc;
	unsigned char		bMIUOpen;
	MIU_INITIALValue	InitialValue;
	unsigned char		CurrentState;
	unsigned short		iSensorID;			// Sensor Product ID
	unsigned short		iSensorType;		// Sensor Resolution
	unsigned int		iPixelFormat;		// Sensor Out Format
	unsigned short		nMaxWidth;			// Max Width
	unsigned short		nMaxHeight;			// Max Height   
	unsigned short		nWidth;				// Sensor Width
	unsigned short		nHeight;			// Sensor Height    
	unsigned short		nBitPerPixel;		// Bit Per Pixel
	unsigned int		nFrameImageSize;	// 1 Frame Image size  ( PAYLOAD_SIZE) 
	unsigned int		nFrameRawSize;		// 1 Frame RAW size (Only Data Size)

	IplImage*			imageItp;			// Display 
	//IplImage*			image12bitRaw;		// pack raw = 12bit 
	//IplImage*			image16bitRaw;		// uppack raw = 16bit 
	IplImage*			image;				// Image Receive
	IplImage*			imageResize;		// Image Resize
	IplImage*			ColorConvertItp;	// Color Convert
	char				szWindowName[256];

	unsigned char		fResizeFlag;
	unsigned short		nDisplayWidth;  // Display Width
	unsigned short		nDisplayHeight; // Display Height

	unsigned char		iImageSave;     // Image 저장 관련 flag 0:저장 안함, 1: Still Capture, 2:동영상 저장 
	unsigned char		fSaveNewFrame;  // 저장할 Image가 있는지 알려주는 flag
} MIU_DEVICE, *PMIU_DEVICE;


typedef enum IMAGE_FILE_TYPE_t {
	IMAGE_TYPE_RAW = 0,
	IMAGE_TYPE_BMP,
	IMAGE_TYPE_JPG,
	IMAGE_TYPE_AVI_BMP,
	IMAGE_TYPE_AVI_SELECT
} IMAGE_FILE_TYPE;



#endif