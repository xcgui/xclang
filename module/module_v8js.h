//@模块名称  谷歌V8JS 
//@版本  1.0  
//@日期  2023-08-29
//@作者  XCGUI  
//@QQ   154460336
//@模块备注 谷歌V8 JS引擎, 可执行JS文件 或 JS文本, 提供了静态库和动态库
// 调试版为: 工具集为VS2019, 运行库为静态编译(MTd)
// 发布版为: 工具集为VS2019, 运行库为静态编译(MT)

//@依赖  module_base.h

//@src "v8js.cpp"


#pragma once

#ifndef  XCL_VS2019
#error "要求选择平台工具集为VS2019, 调试版运行库为静态编译(MTd)"
#endif

#include <windows.h>
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib, "Dbghelp.lib")

#ifdef _WIN64
#define  V8_COMPRESS_POINTERS
#endif


#ifdef  XC_MODULE
#include "module_base.h"
#endif

#include "include/v8.h"
#include "include/libplatform/libplatform.h"
//#include "v8/v8-inspector-protocol.h"
//#pragma comment(lib,"v8/v8.dll.lib")
//#pragma comment(lib,"v8/v8_libplatform.dll.lib")


#ifdef  XCL_MODULE_USE_DLL  //下面使用动态库
	#ifdef _WIN64
	//@复制文件 @当前模块路径 "x64\dynamic\icudt69.dll"
	//@复制文件 @当前模块路径 "x64\dynamic\icuin69.dll"
	//@复制文件 @当前模块路径 "x64\dynamic\icuio69.dll"
	//@复制文件 @当前模块路径 "x64\dynamic\icutu69.dll"
	//@复制文件 @当前模块路径 "x64\dynamic\icuuc69.dll"
	//@复制文件 @当前模块路径 "x64\dynamic\v8.dll"
	//@复制文件 @当前模块路径 "x64\dynamic\v8_libbase.dll"
	//@复制文件 @当前模块路径 "x64\dynamic\v8_libplatform.dll"
	//@复制文件 @当前模块路径 "x64\dynamic\zlib1.dll"
	//@复制文件 @当前模块路径 "x64\snapshot_blob.bin"

	//@lib  "x64\dynamic\v8.dll.lib"
	//@lib  "x64\dynamic\v8_libplatform.dll.lib"
	#else
	//@复制文件 @当前模块路径 "win32\dynamic\icudt69.dll"
	//@复制文件 @当前模块路径 "win32\dynamic\icuin69.dll"
	//@复制文件 @当前模块路径 "win32\dynamic\icuio69.dll"
	//@复制文件 @当前模块路径 "win32\dynamic\icutu69.dll"
	//@复制文件 @当前模块路径 "win32\dynamic\icuuc69.dll"
	//@复制文件 @当前模块路径 "win32\dynamic\v8.dll"
	//@复制文件 @当前模块路径 "win32\dynamic\v8_libbase.dll"
	//@复制文件 @当前模块路径 "win32\dynamic\v8_libplatform.dll"
	//@复制文件 @当前模块路径 "win32\dynamic\zlib1.dll"
	//@复制文件 @当前模块路径 "win32\snapshot_blob.bin"

	//@lib  "win32\dynamic\v8.dll.lib"
	//@lib  "win32\dynamic\v8_libplatform.dll.lib"
	#endif

#else  //下面使用静态库
	#ifdef _WIN64
		#ifdef DEBUG
		//@lib  "x64\static\Debug\v8_monolith.lib"
		//@lib  "x64\static\Debug\icudt.lib"
		//@lib  "x64\static\Debug\icuin.lib"
		//@lib  "x64\static\Debug\icuio.lib"
		//@lib  "x64\static\Debug\icutu.lib"
		//@lib  "x64\static\Debug\icuuc.lib"
		//@lib  "x64\static\Debug\zlib.lib"
		#else
		//@lib  "x64\static\Release\v8_monolith.lib"
		//@lib  "x64\static\Release\icudt.lib"
		//@lib  "x64\static\Release\icuin.lib"
		//@lib  "x64\static\Release\icuio.lib"
		//@lib  "x64\static\Release\icutu.lib"
		//@lib  "x64\static\Release\icuuc.lib"
		//@lib  "x64\static\Release\zlib.lib"
		#endif
	#else
		#ifdef DEBUG
		//@lib  "win32\static\Debug\v8_monolith.lib"
		//@lib  "win32\static\Debug\icudt.lib"
		//@lib  "win32\static\Debug\icuin.lib"
		//@lib  "win32\static\Debug\icuio.lib"
		//@lib  "win32\static\Debug\icutu.lib"
		//@lib  "win32\static\Debug\icuuc.lib"
		//@lib  "win32\static\Debug\zlib.lib"
		#else
		//@lib  "win32\static\Release\v8_monolith.lib"
		//@lib  "win32\static\Release\icudt.lib"
		//@lib  "win32\static\Release\icuin.lib"
		//@lib  "win32\static\Release\icuio.lib"
		//@lib  "win32\static\Release\icutu.lib"
		//@lib  "win32\static\Release\icuuc.lib"
		//@lib  "win32\static\Release\zlib.lib"	
		#endif
	#endif
#endif


//@别名  JSV8引擎类
class CJavaScript
{
public:
	CJavaScript();
	~CJavaScript();
//@隐藏{
	v8::Isolate* isolate;
	std::unique_ptr<v8::Platform> platform;
	v8::Isolate::CreateParams     create_params;
//@隐藏}

	//@别名 初始化()
	BOOL Init();

	//@别名 退出()
	void Exit();

	//@别名 执行脚本从文件(文件名)
	CXText RunJsFile(const wchar_t* pFileName);
	//@别名 执行脚本从字符串(字符串)
	CXText RunJsString(const wchar_t* pString);
	//@别名 执行脚本从字符串UTF8(字符串)
	CXText RunJsStringUtf8(const char* pString);
	//@别名  取版本号()
	CXText  GetVersion();
//@隐藏{
private:
	CXText RunJS(v8::Local<v8::String>& source, const wchar_t* pFileName);
//@隐藏}
};

