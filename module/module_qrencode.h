
// Created by  南小鱼封装 (QQ 128492656)
//
//下面是定义显示的模块名称
//@模块名称  小鱼_二维码
//@版本  0.1
//@日期  2023-03-27
//@作者  南小鱼 (QQ 128492656) 封装 
//@模块备注  来自网络 https://github.com/fukuchi/libqrencode	https://fukuchi.org/works/qrencode/
//@依赖   module_base.h
//@依赖   module_bitmap24.h
//依赖   xc_logA.h
//依赖   module_windowsApi.h
//依赖   module_xcgui.h


//https://blog.csdn.net/liulina603/article/details/42099121 二维码总结
//二维码编码库qrencode使用例子 https://blog.csdn.net/weixin_42887343/article/details/114695358?spm=1001.2101.3001.6650.6&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-6-114695358-blog-127913763.235%5Ev27%5Epc_relevant_default&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-6-114695358-blog-127913763.235%5Ev27%5Epc_relevant_default&utm_relevant_index=9

#pragma once 
//---------------------------------------------------------
//#include <windows.h>  //使用位图文件头结构体和位图信息头结构体 
#include "lib\include\qrencode.h"  //使用位图文件头结构体和位图信息头结构体 
#include <fstream>



#ifdef _WIN64
//这是动态编译需要的文件 炫暂无法判断统方式 先不处理了
//复制文件 @当前模块路径 "lib\x64\qrencode.dll"
//lib "lib\x64\qrencode.lib"


#ifdef _DEBUG

//@lib "lib\x64\qrencode-static-debug.lib"

#else

//@lib "lib\x64\qrencode-static-release.lib"

#endif  // _DEBUG 尾


#else  //win32
//这是动态编译需要的文件 炫暂无法判断统方式 先不处理了
//复制文件 @当前模块路径 "lib\win32\qrencode.dll"
//lib "lib\win32\qrencode.lib"
#ifdef _DEBUG

//@lib "lib\win32\qrencode-static-debug.lib"

#else

//@lib "lib\win32\qrencode-static-release.lib"

#endif  // _DEBUG 尾




#endif  //_win64尾



//内部使用 不显示到ide中去
//@隐藏{
inline  void QRcode2Bmp(const QRcode* qrCode, CFBitMap& bmp, int backgroundColor, int pixelColor, int nZoom)
 {
     if (!qrCode) return;
     nZoom = max (1, nZoom);
     const int qrWidth = (qrCode->width > 0 ? qrCode->width : 1);
     bmp.CreateBitmap(qrWidth * nZoom, qrWidth * nZoom, 24);
     bmp.FillBG(backgroundColor);    //白色底图
     
	 for ( int y = 0; y < qrWidth; y++)
     {
         for (int x = 0; x < qrWidth; x++)
         {
             unsigned char b = qrCode->data[y * qrWidth + x];
             if (b & 0x01)    //深色,反之留底色
             {
                 for (int x2 = 0; x2 < nZoom; x2++)
                     for (int y2 = 0; y2 < nZoom; y2++)
                         bmp.SetPixel(x * nZoom + x2, y * nZoom + y2, pixelColor);
             }
			 //XCL_log(L"x",x);	 
         }
	//XCL_log(L"y",y);	 
     }    
 }
//@隐藏}

//文件_写到文件
//@备注 将二维数据保存为.bmp的文件
//@参数 fileName 完整的保存文件名称,后缀为 .bmp
//@参数 二维码数据 生成的二维码数据内容
//@别名 二维码_保存到文件()
inline bool 二维码_保存到文件(CXText fileName,  CFBitMap& 二维码数据)
{
    CXBytes filebytes ;
	filebytes.add(二维码数据.GetBitmap(), 二维码数据.GetBitmapSize());
	std::ofstream wf;
    wf.open(fileName, std::ios::out| std::ios::binary);
    if (!wf.is_open()) { return false; }
    int index = 0;
    int addnum = filebytes.size();
    int iBuffLen = addnum< 2048 ? addnum : 2048;
    while (addnum>0) {
        char* buff = new char[addnum];
        CXBytes b =filebytes.getMid(index, iBuffLen);
        wf.write((char*)b.get(),b.size());
        index = (index+ iBuffLen)> filebytes.size()? filebytes.size(): index + iBuffLen;
        addnum = (filebytes.size()- index)>2048? 2048: filebytes.size() - index;
        delete buff;
    }
    wf.close();
    return true;
}



//@备注 以指定文本内容生成二维码图像
//@参数 二维码内容 文本型  提供所生成二维码的文本内容
//@参数 等级 整形 提供所欲使用的生成等级,1-40之间,值越大像素点越多,能表示的内容越多. 通常 10
//@参数 容错 整形 提供所生成二维码的容错等级,0-3之间. 建议值 3
//@参数 底色 整形 二维码的底色 用常用颜色输入 建议值 白色
//@参数 码颜色 整形 二维码的颜色 用常用颜色输入 建议值 黑色
//@参数 放大倍数 整形 不小于1 如果小于1 按1处理
//@参数 返回结果 CFBitMap 增强位图类
//@别名 二维码_生成二维码()
inline BOOL 二维码_生成二维码(CXText 二维码内容 , int 等级 , int 容错 , int 底色 ,int 码颜色 , int 放大倍数 , CFBitMap& 返回结果 )
{
	
	//CFBitMap bmp;
	QRcode * qrCode = QRcode_encodeString(W2A(二维码内容), 等级, (QRecLevel)容错, QR_MODE_8, 1);
	//XCL_log(L"width",qrCode->width);
	//XCL_log(L"version",qrCode->version);
	//XCL_log(L"data", qrCode->data);
	QRcode2Bmp(qrCode, 返回结果, 底色, 码颜色, 放大倍数);
	QRcode_free(qrCode);
	//XCL_log(L"bmp",sizeof(bmp));
	//XCL_log(bmp);
	return true;

	
}

//@备注 获取该库的版本信息
//@别名 二维码_取版本信息()
inline CXText 二维码_取版本信息()
{
	CXTextA ver;
	ver = QRcode_APIVersionString();
	return A2W(ver);

	
}




