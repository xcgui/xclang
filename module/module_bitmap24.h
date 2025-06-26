
// Created by  南小鱼封装 (QQ 128492656)
//
//下面是定义显示的模块名称
//@模块名称  小鱼_增强位图
//@版本  0.1
//@日期  2023-03-27
//@作者  南小鱼 (QQ 128492656) 封装 
//@模块备注  来自网络
//@依赖   module_base.h
//依赖   xc_log.h
//依赖   xc_logA.h
//依赖   module_windowsApi.h

//@隐藏{
#pragma once 
#ifndef __bitmap24_h__
#define __bitmap24_h__

#include <math.h>



#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef GetRValue
	#define GetRValue(rgb)      ((BYTE)(rgb))
#endif

#ifndef GetGValue
	#define GetGValue(rgb)      ((BYTE)(((WORD)(rgb)) >> 8))
#endif

#ifndef GetBValue
#define GetBValue(rgb)      ((BYTE)((rgb)>>16))
#endif

#ifndef FRGB
	#define FRGB(r,g,b)          ((int)(((BYTE)(r)|((int)((BYTE)(g))<<8))|(((int)(BYTE)(b))<<16)))
#endif

#ifndef PI
#define PI 3.141592653
#endif
//@隐藏}

//@别名 增强位图类
class CFBitMap
{
public:

//@隐藏{
	inline CFBitMap()
	{
		m_nBitmapSize = 0;
		m_pBitmap = NULL;
		m_pBitsData = NULL;
		m_pBmpFileHeader = NULL;
		m_pBmpInfoHeader = NULL;
		m_BytesPerLine = NULL;
	}
	inline CFBitMap(const CFBitMap& o)
	{
		CreateFromMem(o.m_pBitmap,o.m_nBitmapSize);
	}
	
	inline ~CFBitMap ()
	{
		Destory ();
	}
	
	void Destory()//退出时销毁所有数据 有这个情况的话, 不能用 返回 方式返数据 要用传地址参的方式
	{
		if (m_pBitmap)
			delete [] m_pBitmap;
		m_pBitmap = NULL;
	}
//@隐藏}

//@别名 创建位图()
	BOOL CreateBitmap(int nWidth,int nHeight,int nColorBitCount)
	{
		if (nColorBitCount == 24)
			return CreateBitmap24(nWidth,nHeight);
		else
			return CreateBitmap32(nWidth,nHeight);
	}

//@隐藏{
	BOOL CreateBitmap24(int nWidth,int nHeight)
	{
		Destory();

		//只支持24位位图
		m_BytesPerLine = CalcBytesPerLine(nWidth,24);

		int nBitmapSize = 0;
		nBitmapSize = sizeof(BITMAPFILEHEADER);
		nBitmapSize = nBitmapSize + sizeof(BITMAPINFOHEADER);
		nBitmapSize = nBitmapSize + nHeight*m_BytesPerLine;
		m_pBitmap = new byte[nBitmapSize];

		//开始构造位图
		byte* pData = (byte*)m_pBitmap;
		BITMAPFILEHEADER* pBmpFileHeader =(BITMAPFILEHEADER*)pData;
		pBmpFileHeader->bfType = 0x4d42;
		pBmpFileHeader->bfSize = (DWORD)nBitmapSize;
		pBmpFileHeader->bfReserved1 = 0;
		pBmpFileHeader->bfReserved2 = 0;

		BITMAPINFOHEADER* pBmpInfoHeader = (BITMAPINFOHEADER*)( pData + sizeof(BITMAPFILEHEADER) );
		memset(pBmpInfoHeader,0,sizeof(BITMAPINFOHEADER));
		pBmpInfoHeader->biSize     = sizeof(BITMAPINFOHEADER);
		pBmpFileHeader->bfOffBits  = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
		pBmpInfoHeader->biWidth    = nWidth;
		pBmpInfoHeader->biHeight   = nHeight;
		pBmpInfoHeader->biBitCount = 24;
		pBmpInfoHeader->biPlanes   = 1;
		pBmpInfoHeader->biXPelsPerMeter = 2834;
		pBmpInfoHeader->biYPelsPerMeter = 2834;

		pBmpInfoHeader->biSizeImage = m_BytesPerLine * pBmpInfoHeader->biHeight ;

		m_nBitmapSize    = nBitmapSize;
		m_pBitsData      = pData+pBmpFileHeader->bfOffBits;
		m_pBmpFileHeader = pBmpFileHeader;
		m_pBmpInfoHeader = pBmpInfoHeader;
		
		return TRUE;

	}


	BOOL CreateBitmap32(int nWidth,int nHeight)
	{
		Destory();
		
		m_BytesPerLine = CalcBytesPerLine(nWidth,32);
		
		int nBitmapSize = 0;
		nBitmapSize = sizeof(BITMAPFILEHEADER);
		nBitmapSize = nBitmapSize + sizeof(BITMAPINFOHEADER);
		nBitmapSize = nBitmapSize + nHeight*m_BytesPerLine;
		m_pBitmap = new byte[nBitmapSize];
		
		//开始构造位图
		byte* pData = (byte*)m_pBitmap;
		BITMAPFILEHEADER* pBmpFileHeader =(BITMAPFILEHEADER*)pData;
		pBmpFileHeader->bfType = 0x4d42;
		pBmpFileHeader->bfSize = (DWORD)nBitmapSize;
		pBmpFileHeader->bfReserved1 = 0;
		pBmpFileHeader->bfReserved2 = 0;
		
		BITMAPINFOHEADER* pBmpInfoHeader = (BITMAPINFOHEADER*)( pData + sizeof(BITMAPFILEHEADER) );
		memset(pBmpInfoHeader,0,sizeof(BITMAPINFOHEADER));
		pBmpInfoHeader->biSize     = sizeof(BITMAPINFOHEADER);
		pBmpFileHeader->bfOffBits  = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
		pBmpInfoHeader->biWidth    = nWidth;
		pBmpInfoHeader->biHeight   = nHeight;
		pBmpInfoHeader->biBitCount = 32;
		pBmpInfoHeader->biPlanes   = 1;
		pBmpInfoHeader->biXPelsPerMeter = 2834;
		pBmpInfoHeader->biYPelsPerMeter = 2834;
		pBmpInfoHeader->biSizeImage = m_BytesPerLine * pBmpInfoHeader->biHeight ;
		
		m_nBitmapSize    = nBitmapSize;
		m_pBitsData      = pData+pBmpFileHeader->bfOffBits;
		m_pBmpFileHeader = pBmpFileHeader;
		m_pBmpInfoHeader = pBmpInfoHeader;
		
		return TRUE;
	}



//@隐藏}


//@备注  可以通过字节集创建位图对象
//@参数 pBitMapData 位图文件指针
//@参数 nSize 位图文件大小
//@别名  从指针创建()
	BOOL CreateFromMem(void* pBitMapData,int nSize)
	{
		if (pBitMapData == NULL || nSize == 0)
			return FALSE;

		byte* pData = (byte*)pBitMapData;
		BITMAPFILEHEADER* pBmpFileHeader =(BITMAPFILEHEADER*)pData;
		if( pBmpFileHeader->bfType != 0x4d42 )
			return FALSE;
		
		if (pBmpFileHeader->bfSize != (DWORD)nSize)
			return FALSE;
		
		BITMAPINFOHEADER* pBmpInfoHeader = (BITMAPINFOHEADER*)( pData + sizeof(BITMAPFILEHEADER) );
		if (pBmpInfoHeader->biSize != sizeof(BITMAPINFOHEADER))
			return FALSE;
		
		if (pBmpInfoHeader->biBitCount == 32)
			return CreateFromBitmap32(pBitMapData,nSize);
		else if (pBmpInfoHeader->biBitCount == 24)
			return CreateFromBitmap24(pBitMapData,nSize);
		return FALSE;
	}


//@隐藏{
	BOOL CreateFromBitmap24(void* pBitMapData,int nSize)
	{
		Destory();
		m_pBitmap = new byte[nSize];
		if (m_pBitmap == NULL)
			return FALSE;
		
		memcpy(m_pBitmap,pBitMapData,nSize);
		
		byte* pData = (byte*)m_pBitmap;
		BITMAPFILEHEADER* pBmpFileHeader =(BITMAPFILEHEADER*)pData;
		if( pBmpFileHeader->bfType != 0x4d42 )
			return FALSE;
		
		BITMAPINFOHEADER* pBmpInfoHeader = (BITMAPINFOHEADER*)( pData + sizeof(BITMAPFILEHEADER) );
		if (pBmpInfoHeader->biSize != sizeof(BITMAPINFOHEADER))
			return FALSE;
		//位图数据
		byte* pBmpdata = pData+pBmpFileHeader->bfOffBits;
		//一行占多少个字节
		int bytesPerLine       = CalcBytesPerLine(pBmpInfoHeader->biWidth,pBmpInfoHeader->biBitCount);
		
		m_nBitmapSize    = pBmpFileHeader->bfSize;
		m_pBmpFileHeader = pBmpFileHeader;
		m_pBmpInfoHeader = pBmpInfoHeader;
		m_pBitsData		 = pBmpdata;
		m_BytesPerLine   = bytesPerLine;

		if (m_pBmpInfoHeader->biSizeImage == 0)
		{
			int nHeight = pBmpInfoHeader->biHeight;
			if (nHeight < 0)
				nHeight = 0 - nHeight;
			m_pBmpInfoHeader->biSizeImage = m_BytesPerLine * nHeight;
		}
		
		return TRUE;
	}
	BOOL CreateFromBitmap32(void* pBitMapData,int nSize)
	{
		Destory();
		m_pBitmap = new byte[nSize];
		if (m_pBitmap == NULL)
			return FALSE;
		
		memcpy(m_pBitmap,pBitMapData,nSize);

		byte* pData = (byte*)m_pBitmap;
		BITMAPFILEHEADER* pBmpFileHeader =(BITMAPFILEHEADER*)pData;
		if( pBmpFileHeader->bfType != 0x4d42 )
			return FALSE;
		
		BITMAPINFOHEADER* pBmpInfoHeader = (BITMAPINFOHEADER*)( pData + sizeof(BITMAPFILEHEADER) );
		if (pBmpInfoHeader->biSize != sizeof(BITMAPINFOHEADER))
			return FALSE;
		//位图数据
		byte* pBmpdata = pData+pBmpFileHeader->bfOffBits;

		//一行占多少个字节
		//32位位图，一个像素占用4个字节，所以直接用宽度*4 即可
		int bytesPerLine       = CalcBytesPerLine(pBmpInfoHeader->biWidth,pBmpInfoHeader->biBitCount);
		
		m_nBitmapSize    = pBmpFileHeader->bfSize;
		m_pBmpFileHeader = pBmpFileHeader;
		m_pBmpInfoHeader = pBmpInfoHeader;
		m_pBitsData		 = pBmpdata;
		m_BytesPerLine   = bytesPerLine;

		if (m_pBmpInfoHeader->biSizeImage == 0)
		{
			int nHeight = pBmpInfoHeader->biHeight;
			if (nHeight < 0)
				nHeight = 0 - nHeight;
			m_pBmpInfoHeader->biSizeImage = m_BytesPerLine * nHeight;
		}

		return TRUE;
	}

	int  GetColorBitCount()
	{
		return m_pBmpInfoHeader->biBitCount;
	}
//@隐藏}

//判断当前位图对象是否存在数据
//@别名 是否存在()
	BOOL IsValid()
	{
		return m_pBitmap?TRUE:FALSE;
	}
	
//@隐藏{
	int CalcBytesPerLine(int nWidth,int nBitCount)
	{
		return (nWidth* nBitCount+31)/32*4;
	}
//@隐藏}

//@别名 取宽度()
	int GetWidth()
	{
		return m_pBmpInfoHeader->biWidth < 0 ? 0 - m_pBmpInfoHeader->biWidth: m_pBmpInfoHeader->biWidth;
	}
	
//@别名 取高度()
	int GetHeight()
	{
		return m_pBmpInfoHeader->biHeight < 0 ? 0 - m_pBmpInfoHeader->biHeight:m_pBmpInfoHeader->biHeight;
	}

//@别名 取像素数据缓冲指针()
	VOID* GetBitsData()
	{
		return m_pBitsData;
	}

//@别名 取像素数据数量()
	int GetBitsCount()
	{
		return m_pBmpInfoHeader->biSizeImage;
	}
	
//@隐藏{
	int GetPixOffset(int x,int y)
	{
		int nReturn = 0;

		if (m_pBmpInfoHeader->biHeight < 0)
		{
			//要正着读取
			if (GetColorBitCount() == 24)
			{
				//24位位图
				nReturn = y*m_BytesPerLine+x*3;
			}else
			{
				//32位位图
				nReturn = y*m_BytesPerLine+x*4;
			}

		}else
		{
			//要倒着读取
			if (GetColorBitCount() == 24)
			{
				//24位位图
				nReturn = (GetHeight()-y-1) *m_BytesPerLine+x*3;
			}else
			{
				//32位位图
				nReturn = (GetHeight()-y-1) *m_BytesPerLine+x*4;
			}
		}

		return nReturn;
	}
//@隐藏}

//@别名 取坐标红色()
	BYTE GetR(int x,int y)
	{
		return m_pBitsData[GetPixOffset(x,y)+2];
	}


//@别名 取坐标绿色()
	BYTE GetG(int x,int y)
	{
		return m_pBitsData[GetPixOffset(x,y)+1];
	}


//@别名 取坐标蓝色()
	BYTE GetB(int x,int y)
	{
		return m_pBitsData[GetPixOffset(x,y)];
	}

//@别名 取坐标透明度()
	BYTE GetAlpha(int x,int y)
	{
		if (GetColorBitCount() == 32)
			return m_pBitsData[GetPixOffset(x,y)+3];
		return 0;
	}

//@别名 置坐标红色()
	void SetR(int x,int y,BYTE v)
	{
		 m_pBitsData[GetPixOffset(x,y)+2] = v;
	}
	
//@别名 置坐标绿色()
	void SetG(int x,int y,BYTE v)
	{
		m_pBitsData[GetPixOffset(x,y)+1] = v;
	}
	
	
//@别名 置坐标蓝色()
	void SetB(int x,int y,BYTE v)
	{
		m_pBitsData[GetPixOffset(x,y)] = v;
	}

//@别名 置坐标透明度()
	void SetAlpha(int x,int y,BYTE v)
	{
		if (GetColorBitCount() == 32)
			m_pBitsData[GetPixOffset(x,y)+3] = v;
	}


//@隐藏{
	BYTE GetR(int index)
	{
		return m_pBitsData[index+2];
	}
	BYTE GetG(int index)
	{
		return m_pBitsData[index+1];
	}
	BYTE GetB(int index)
	{
		return m_pBitsData[index];
	}
	BYTE GetAlpha(int index)
	{
		if (GetColorBitCount() == 32)
			return m_pBitsData[index+3];
		return 0;
	}
	void SetR(int index,BYTE v)
	{
		m_pBitsData[index+2] = v;
	}
	void SetG(int index,BYTE v)
	{
		m_pBitsData[index+1] = v;
	}
	void SetB(int index,BYTE v)
	{
		m_pBitsData[index] = v;
	}
	void SetAlpha(int index,BYTE v)
	{
		if (GetColorBitCount() == 32)
			m_pBitsData[index+3] = v;
	}



	int GetPixel(int nIndex)
	{
		DWORD color = 0;
		BYTE* pPix = &m_pBitsData[nIndex];
		
		BYTE* pDes =(BYTE*)&color;
		pDes[0] = pPix[2];  //R
		pDes[1] = pPix[1];  //G
		pDes[2] = pPix[0];  //B

		return color;
	}
//@隐藏}

//@别名 取坐标颜色()
	int GetPixel(int x,int y)
	{
		DWORD color = 0;
		BYTE* pPix = &m_pBitsData[GetPixOffset(x,y)];

		BYTE* pDes =(BYTE*)&color;
		pDes[0] = pPix[2];  //R
		pDes[1] = pPix[1];  //G
		pDes[2] = pPix[0];  //B

		return color;
	}
	
	
//@隐藏{
	VOID SetPixel(int nIndex,int color)
	{
		BYTE* pPix = &m_pBitsData[nIndex];
		
		BYTE* pSrc = (BYTE*)&color;
		
		if (GetColorBitCount() == 32)
			pPix[3] = pSrc[3]; //R
		pPix[0] = pSrc[2]; //B
		pPix[1] = pSrc[1]; //G
		pPix[2] = pSrc[0]; //R
	}
//@隐藏}

//@别名 置坐标颜色()
	VOID SetPixel(int x,int y,int color)
	{
		BYTE* pPix = &m_pBitsData[GetPixOffset(x,y)];

		BYTE* pSrc = (BYTE*)&color;

		if (GetColorBitCount() == 32)
			pPix[3] = pSrc[3]; //R
		pPix[0] = pSrc[2]; //B
		pPix[1] = pSrc[1]; //G
		pPix[2] = pSrc[0]; //R
	}

	// flase 黑色
	// ture  白色

//@别名 填充颜色()
	void FillBG(int nColor)
	{
		BYTE* pData =(BYTE*)m_pBitmap;
		for (int nRow = 0; nRow < GetHeight(); nRow++)
		{
			for (int nCol = 0; nCol < GetWidth(); nCol++)
				SetPixel(nCol,nRow,nColor);
		}
	}

	//调整亮度
//@别名 调整亮度()
	void SetBrightness(int nLight)
	{
		int _brightness = max(-255, min(255, nLight));
		
		for (LONG dwRow = 0; dwRow < GetHeight(); dwRow++)
		{
			for (LONG dwCol = 0; dwCol < GetWidth(); dwCol++)
			{
				BYTE bPixB = GetB(dwCol,dwRow);
				BYTE bPixG = GetG(dwCol,dwRow);
				BYTE bPixR = GetR(dwCol,dwRow);
				
				bPixR = (BYTE)max(0, min(bPixR+_brightness, 255));
				bPixG = (BYTE)max(0, min(bPixG+_brightness, 255));
				bPixB = (BYTE)max(0, min(bPixB+_brightness, 255));
				
				SetR(dwCol,dwRow,bPixR);
				SetG(dwCol,dwRow,bPixG);
				SetB(dwCol,dwRow,bPixB);
			}
		}
	}



//@别名 取红色通道数组()
	void GetRedChannel(int channel[256])
	{
		memset(channel, 0, 256*sizeof(int));

		for (LONG dwRow = 0; dwRow < GetHeight(); dwRow++)
		{
			for (LONG dwCol = 0; dwCol < GetWidth(); dwCol++)
			{
				BYTE bPixR = GetR(dwCol,dwRow);
				channel[bPixR]++;
			}
		}
	}
	
	
//@别名 取绿色通道数组()	
	void GetGreenChannel(int channel[256])
	{
		memset(channel, 0, 256*sizeof(int));

		for (LONG dwRow = 0; dwRow < GetHeight(); dwRow++)
		{
			for (LONG dwCol = 0; dwCol < GetWidth(); dwCol++)
			{
				BYTE bPixR = GetG(dwCol,dwRow);
				channel[bPixR]++;
			}
		}
	}


//@别名 取蓝色通道数组()	
	void GetBlueChannel(int channel[256])
	{
		memset(channel, 0, 256*sizeof(int));

		for (LONG dwRow = 0; dwRow < GetHeight(); dwRow++)
		{
			for (LONG dwCol = 0; dwCol < GetWidth(); dwCol++)
			{
				BYTE bPixR = GetG(dwCol,dwRow);
				channel[bPixR]++;
			}
		}
	}

//@参数 threshold 范围0-255
//@别名 二值化()
	void BlackAndWhite(int threshold)
	{
		for (LONG dwRow = 0; dwRow < GetHeight(); dwRow++)
		{
			for (LONG dwCol = 0; dwCol < GetWidth(); dwCol++)
			{
				BYTE bPixB = GetB(dwCol,dwRow);
				BYTE bPixG = GetG(dwCol,dwRow);
				BYTE bPixR = GetR(dwCol,dwRow);
				
				double v = bPixR*0.299+bPixG*0.587+bPixB*0.114;
				if (v > threshold)
					SetPixel(dwCol,dwRow,RGB(255,255,255));
				else
					SetPixel(dwCol,dwRow,0);
			}
		}
	}


//@备注 对当前位图进行灰度处理
//@别名 灰度()
	void Gray()
	{
		for (LONG dwRow = 0; dwRow < GetHeight(); dwRow++)
		{
			for (LONG dwCol = 0; dwCol < GetWidth(); dwCol++)
			{
				BYTE bPixB = GetB(dwCol,dwRow);
				BYTE bPixG = GetG(dwCol,dwRow);
				BYTE bPixR = GetR(dwCol,dwRow);
				BYTE v  = (BYTE)(bPixR*0.299+bPixG*0.587+bPixB*0.114);
				SetR(dwCol,dwRow,v);
				SetG(dwCol,dwRow,v);
				SetB(dwCol,dwRow,v);
			}
		}
	}

//@别名 旋转()
	void xuanzhuan(int angle,CFBitMap& NewBitmap)
	{
		//摘自 https://blog.csdn.net/qq_36752072/article/details/78151770
		int width = GetWidth();
		int height = GetHeight();

		if (angle % 360 == 270)
			angle++;
		double thelta = (double)(angle * PI / 180);
		int newWidth  = abs( (int)(  (double)width * cos(thelta) + (double)height * sin(thelta)) );
		int newHeight = abs( (int)(  (double)width * sin(thelta) + (double)height * cos(thelta)) );

		int rotateX = width / 2;
	    int rotateY = height / 2;
		//旋转中心点
		int write_rotateX = newWidth / 2;
	    int write_rotateY = newHeight / 2;

		int l_width = GetBytesPerLine();

		NewBitmap.CreateBitmap(newWidth,newHeight,GetColorBitCount());
		// step 3 : 完成将图像信息的迁移
		for (int hnum = 0; hnum < newHeight; ++ hnum){    
				for (int wnum = 0; wnum < newWidth; ++ wnum){
					// 新数据的下标为index
					int index = NewBitmap.GetPixOffset(wnum,hnum);
					// 利用公式计算这个原来的点的地方
					double d_original_img_hnum = (wnum - write_rotateX) * sin(thelta) + (hnum - write_rotateY) * cos(thelta) + rotateY;
					double d_original_img_wnum = (wnum - write_rotateX) * cos(thelta) - (hnum - write_rotateY) * sin(thelta) + rotateX;    

					if (d_original_img_hnum < 0 || d_original_img_hnum > height || d_original_img_wnum < 0 || d_original_img_wnum > width){
						NewBitmap.SetPixel(index,0);
						continue;
					}else{
						// 我们在这里使用双线性插值法来完成对应
						int i_original_img_hnum = (int)d_original_img_hnum;
						int i_original_img_wnum = (int)d_original_img_wnum;
						double distance_to_a_X = d_original_img_wnum - i_original_img_wnum;
						double distance_to_a_Y = d_original_img_hnum - i_original_img_hnum;

						int original_point_A = GetPixOffset(i_original_img_wnum,i_original_img_hnum);
						int original_point_B = GetPixOffset(i_original_img_wnum+1,i_original_img_hnum);
						int original_point_C = GetPixOffset(i_original_img_wnum,i_original_img_hnum+1);
						int original_point_D = GetPixOffset(i_original_img_wnum+1,i_original_img_hnum+1);

						if (i_original_img_wnum == width - 1){
							original_point_A = original_point_B;
							original_point_C = original_point_D;
						}
						if (i_original_img_hnum == height - 1){
							original_point_C = original_point_A;
							original_point_D = original_point_B;
						}
						
						double pixelB = (1 - distance_to_a_X) * (1 - distance_to_a_Y) * GetB(original_point_A)
							+ (1 - distance_to_a_X) * distance_to_a_Y * GetB(original_point_B)
							+ distance_to_a_X * (1 - distance_to_a_Y) * GetB(original_point_C)
							+ distance_to_a_X * distance_to_a_Y * GetB(original_point_D);
												
						double pixelG = (1 - distance_to_a_X) * (1 - distance_to_a_Y) * GetG(original_point_A )
							+ (1 - distance_to_a_X) * distance_to_a_Y * GetG(original_point_B )
							+ distance_to_a_X * (1 - distance_to_a_Y) * GetG(original_point_C )
							+ distance_to_a_X * distance_to_a_Y * GetG(original_point_D );
						
						double pixelR = (1 - distance_to_a_X) * (1 - distance_to_a_Y) * GetR(original_point_A )
							+ (1 - distance_to_a_X) * distance_to_a_Y * GetR(original_point_B )
							+ distance_to_a_X * (1 - distance_to_a_Y) * GetR(original_point_C )
											+ distance_to_a_X * distance_to_a_Y * GetR(original_point_D );
						NewBitmap.SetB(index,(BYTE)pixelB);
						NewBitmap.SetG(index,(BYTE)pixelG);
						NewBitmap.SetR(index,(BYTE)pixelR);
					}    
				}
			}
	}
	//算法来源 https://blog.csdn.net/weixinhum/article/details/38963705?utm_source=blogxgwz5
	//上面收费了，找到一个不收费的 https://blog.csdn.net/baidu_37503452/article/details/73498139

//@别名 缩放()
	void Zoom(int MYDRAW_WIDTH,int MYDRAW_HEIGHT,CFBitMap& NewBitmap)
	{
		int height = GetHeight();
		int width  = GetWidth();
		NewBitmap.CreateBitmap(MYDRAW_WIDTH,MYDRAW_HEIGHT,GetColorBitCount());
		int l_width = GetBytesPerLine();

		for (int hnum = 0; hnum < MYDRAW_HEIGHT; hnum++)
			for (int wnum = 0; wnum < MYDRAW_WIDTH; wnum++)
			{
				double d_original_img_hnum = hnum*height / (double)MYDRAW_HEIGHT;
				double d_original_img_wnum = wnum*width / (double)MYDRAW_WIDTH;
				int i_original_img_hnum = (int)d_original_img_hnum;
				int i_original_img_wnum = (int)d_original_img_wnum;
				double distance_to_a_x = d_original_img_wnum - i_original_img_wnum;//在原图像中与a点的水平距离  
				double distance_to_a_y = d_original_img_hnum - i_original_img_hnum;//在原图像中与a点的垂直距离  
				
				int original_point_a = GetPixOffset(i_original_img_wnum,i_original_img_hnum);
				int original_point_b = GetPixOffset(i_original_img_wnum+1,i_original_img_hnum);
				int original_point_c = GetPixOffset(i_original_img_wnum,i_original_img_hnum+1);
				int original_point_d = GetPixOffset(i_original_img_wnum+1,i_original_img_hnum+1);

				//if (i_original_img_hnum +1 == MYDRAW_HEIGHT - 1)
				if (i_original_img_hnum + 1 >= height)
				{
					original_point_c = original_point_a;
					original_point_d = original_point_b;
				}
				if (i_original_img_wnum +1 >= width)
				{
					original_point_b = original_point_a;
					original_point_d = original_point_c;
				}
				
				int pixel_point = NewBitmap.GetPixOffset(wnum,hnum);

				double pixelB =
					GetB(original_point_a) * (1 - distance_to_a_x)*(1 - distance_to_a_y) +
					GetB(original_point_b) * distance_to_a_x*(1 - distance_to_a_y) +
					GetB(original_point_c) * distance_to_a_y*(1 - distance_to_a_x) +
					GetB(original_point_d) * distance_to_a_y*distance_to_a_x;
				double pixelG =
					GetG(original_point_a) * (1 - distance_to_a_x)*(1 - distance_to_a_y) +
					GetG(original_point_b) * distance_to_a_x*(1 - distance_to_a_y) +
					GetG(original_point_c) * distance_to_a_y*(1 - distance_to_a_x) +
					GetG(original_point_d) * distance_to_a_y*distance_to_a_x;
				double pixelR =
					GetR(original_point_a) * (1 - distance_to_a_x)*(1 - distance_to_a_y) +
					GetR(original_point_b) * distance_to_a_x*(1 - distance_to_a_y) +
					GetR(original_point_c) * distance_to_a_y*(1 - distance_to_a_x) +
					GetR(original_point_d) * distance_to_a_y*distance_to_a_x;

				NewBitmap.SetB(pixel_point,(BYTE)pixelB);
				NewBitmap.SetG(pixel_point,(BYTE)pixelG);
				NewBitmap.SetR(pixel_point,(BYTE)pixelR);
		}
	}

//@隐藏{
	int GetBytesPerLine()
	{
		return m_BytesPerLine;
	}
//@隐藏}


//@别名 取位图指针()
	void* GetBitmap()
	{
		return m_pBitmap;
	}

//@别名 取位图大小()
	int GetBitmapSize()
	{
		return m_nBitmapSize;
	}

protected:
	void* m_pBitmap;
	int   m_nBitmapSize;
	byte* m_pBitsData;
	BITMAPFILEHEADER* m_pBmpFileHeader;
	BITMAPINFOHEADER* m_pBmpInfoHeader;
	int m_BytesPerLine;
};

#endif // __bitmap24_h__