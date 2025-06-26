#pragma once

//@模块名称  压缩解压
//@版本  0.1
//@日期  2024-09-21
//@作者  hxznhf
//@QQ   568415950
//@模块备注  基于C++ zlib库，提供压缩解压功能
//
//@依赖  module_base.h

//@src "compress.cpp"


#ifdef _WIN64
#ifdef _DEBUG
//@lib "zlib.lib"
#else
//@lib "zlibd.lib"
#endif

#else
#ifdef _DEBUG
//@lib "zlib_x86.lib"
#else
//@lib "zlibd_x86.lib"
#endif
#endif




#include "module_base.h"

//@别名 压缩解压
class xcompress
{
public:
    xcompress();
    ~xcompress();

    //@别名 压缩(数据)
    //@参数 原始字节集数据
    static CXBytes compressData(const CXBytes &data);

    //@别名 解压(数据)
    //@参数 压缩后的字节集数据

    static CXBytes decompressData(const CXBytes &compressed);
};
