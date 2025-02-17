/******************************************************************************
*	Project : Eagle Eye Project (Gigabit Ethernet Camera)
*
*
*	
*	File Name : ConvertColor.cpp 
*	author : hkkim
******************************************************************************/
 
#include "stdafx.h"
#include "ConvertColor.h"
#include "PixelFormat.h"
#include "EECvtColorEx.h"


/**************************************************************************************************
*   Shift10BitMode : Test 용 -> 10 bit 를 8bit로 shift  
*
*   @param      pImage, [in] Image Pointer
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
void Shift10BitMode(unsigned char* pImage, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight)
{
	unsigned int i,j,k;
	unsigned int nByteWidth;
	unsigned int *piDest;

	nByteWidth = nWidth * 5 / 4 ;
	piDest = (unsigned int *)pDest;
	nWidth >>= 2;

	for(i=0; i<nHeight; i++)
	{
		for(j=0, k=0; j<nWidth; j++, k+=5)
		{
			 piDest[j] = (pImage[k+3]<<24) +  (pImage[k+2]<<16) +  (pImage[k+1]<<8) +  (pImage[k]);
		}

		piDest += nWidth;
		pImage += nByteWidth;
	}
}

/**************************************************************************************************
*   Shift10BitMode : Test 용 -> 12 bit 를 8bit로 shift  
*
*   @param      pImage, [in] Image Pointer
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
void Shift12BitMode(unsigned char* pImage, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight)
{
	unsigned int	i,j,k;
	unsigned int	nByteWidth;
	unsigned short *psDest;

	nByteWidth = nWidth * 3 / 2 ;
	psDest = (unsigned short *)pDest;
	nWidth >>= 1;
	for(i=0; i<nHeight; i++)
	{
		for(j=0, k = 0; j<nWidth; j++,k+=3)
		{
			psDest[j] =  (pImage[k+1]<<8) +  (pImage[k]);			
		}
		psDest += nWidth;
		pImage += nByteWidth;
	}
}


//#define	CONVTIMECHECK

/**************************************************************************************************
*   ConvertColor : Display 하기 위해 입력 영상을 RGB로 변환 한다  
*
*   @param      iPixelFormat, [in] Pixel Format
*   @param      pSrc, [in] 변환할 Source Image (OpenCV의 IplImage*)
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      pTemp, [inout] 10bit 이상일 경우 사용하는 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
void ConvertColor(unsigned int iPixelFormat, IplImage* pSrc, IplImage* pDest, IplImage* pTemp, unsigned int nWidth, unsigned int nHeight)
{
#ifdef CONVTIMECHECK
	LARGE_INTEGER start, finish;
	LARGE_INTEGER ticksPerSec;
	double timeSec;

	if (!QueryPerformanceFrequency(&ticksPerSec))
	{ 
		return;
	} 
	QueryPerformanceCounter(&start);
#endif
	switch(iPixelFormat)
    {
		case MIU_MONO8:
			cvCvtColor(pSrc, pDest, CV_GRAY2RGB);
			break;

		case MIU_MONO10_PACKED:
			Shift10BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData,nWidth, nHeight);
			cvCvtColor(pTemp, pDest, CV_GRAY2RGB);
			break;

		case MIU_MONO12_PACKED:
			Shift12BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor(pTemp, pDest, CV_GRAY2RGB);
			break;

		case MIU_MONO14:

			break;

        case MIU_BAYERGR8:
            cvCvtColor( pSrc, pDest, CV_BayerGR2RGB);  // interpolation  
			break;

        case MIU_BAYERGB8:
            cvCvtColor( pSrc, pDest, CV_BayerGB2RGB);  // interpolation					
            break;

		 case MIU_BAYERRG8:
            cvCvtColor( pSrc, pDest, CV_BayerRG2RGB);  // interpolation  
			break;

        case MIU_BAYERBG8:
            cvCvtColor( pSrc, pDest, CV_BayerBG2RGB);  // interpolation					
            break;

		case MIU_BAYERRG10_PACKED:
			Shift10BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor( pTemp, pDest, CV_BayerRG2RGB);  // interpolation 
			break;

		case MIU_BAYERGR10_PACKED:
			Shift10BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor( pTemp, pDest, CV_BayerGR2RGB);  // interpolation 
			break;

		case MIU_BAYERBG10_PACKED:
			Shift10BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor( pTemp, pDest, CV_BayerBG2RGB);  // interpolation 
			break;

		case MIU_BAYERGB10_PACKED:
			Shift10BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor( pTemp, pDest, CV_BayerGB2RGB);  // interpolation 
			
			break;

		case MIU_BAYERGR12_PACKED:
			Shift12BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor( pTemp, pDest, CV_BayerGR2RGB);  // interpolation 
			break;

		case MIU_BAYERGB12_PACKED:
			Shift12BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor( pTemp, pDest, CV_BayerGB2RGB);  // interpolation 
			break;

		case MIU_BAYERRG12_PACKED:
			Shift12BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor( pTemp, pDest, CV_BayerRG2RGB);  // interpolation 
			break;

		case MIU_BAYERBG12_PACKED:
			Shift12BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor( pTemp, pDest, CV_BayerBG2RGB);  // interpolation 
			break;

		case MIU_YUV422_YUYV_PACKED:
			//ConvYUYVtoRGB((unsigned char*)pSrc->imageData, (unsigned char*)pDest->imageData, nWidth, nHeight);				
			break;

		case MIU_YUV422_PACKED:
			//ConvUYVYtoRGB((unsigned char*)pSrc->imageData, (unsigned char*)pDest->imageData, nWidth, nHeight);
			break;

		case MIU_RGB565:
			cvCvtColor( pSrc, pDest, CV_BGR5652BGR);   
			break;
		
		case MIU_BGR565:
			cvCvtColor( pSrc, pDest, CV_BGR5652RGB);  
			break;

		case MIU_RGB8_PACKED:
			//cvCopyImage( pSrc, pDest );
			cvCopy(pSrc, pDest);
			break;
	
		case MIU_BGR8_PACKED:
			cvCvtColor( pSrc, pDest, CV_BGR2RGB);
			break;
       
        default:
            break;
    }
#ifdef CONVTIMECHECK
	QueryPerformanceCounter(&finish);
	// 경과시간 구하기 (초단위)
	timeSec = (finish.QuadPart - start.QuadPart) / (double)ticksPerSec.QuadPart;
	TRACE("Display : %.6f\n", timeSec);
#endif
}