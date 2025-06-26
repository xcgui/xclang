#pragma once

//@模块名称  Python39
//@版本  3.9 
//@日期  2020-11-20
//@作者  XCGUI  
//@模块备注  提供了python脚本支持


#include "module_base.h"


//@src  "module_python39.cpp"

#ifdef  _WIN64
//@lib  "x64\python39.lib"
//@复制文件 @当前模块路径 "x64\python39.dll"
#else
//@lib  "win32\python39.lib"
//@复制文件 @当前模块路径 "win32\python39.dll"
#endif

//@复制文件 @当前模块路径 "Python3_9.zip"

//初始化Py解释器引擎,初始化成功返回真,失败返回假
//请注意: 在您的应用生命周期内(从开始到结束),只需要初始化一次即可.无需多次初始化,除非
//您自行通过"释放"将其释放掉, 才需要再次初始化.初始化结果, 可使用属性"是否已初始化"获得.
//@别名 Python_初始化()
void Python_Init(); //Py_Initialize

//@备注 取得Python引擎是否已经初始化.
//@返回 已初始化返回真,未初始化返回假.
//@别名 Python_是否初始化()
BOOL Python_IsInit();

//@别名 Python_卸载()
void Python_Finalize();

//@别名 Python_置库路径()
void Python_SetPath(const wchar_t* pPath);

//@别名 Python_执行文件()
BOOL Python_RunFile(const wchar_t* pFileName);

//@别名 Python_执行字符串()
BOOL Python_RunString(const char* pString);

//@备注 指定路径的Py文件添加到搜索路径中
//@参数 添加的文件路径
//@别名 Python_添加模块路径()
BOOL Python_AddModulePath(const char* pString);





//置库路径  Py_SetPath()

//初始化 Py_Initialize() 
//卸载  Py_Finalize()

//运行代码  PyRun_SimpleString()
//加载PY文件  PyRun_SimpleFile()


//是否已初始化 Py_IsInitialized()

//添加模块路径 //PyRun_SimpleString("sys.path.append('.\\Debug')");



