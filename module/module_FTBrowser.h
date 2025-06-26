
#pragma once
#include <string>
#include <vector>
//#pragma comment  (lib,"FTBrowser.lib")
#ifdef  _WIN64
//@lib "x64\FTBrowser.lib"
//@复制文件 @当前模块路径 "x64\FTBrowser.dll"
#else
//@lib "x86\FTBrowser.lib"
//@复制文件 @当前模块路径 "x86\FTBrowser.dll"
#endif

//@模块名称  FTBrowser  
//@版本  1.0  
//@日期  2022-11-3
//@作者  易团雪  
//@模块备注 作为图形设备接口的GDI+使得应用程序开发人员在输出屏幕和打印机信息的时候无需考虑具体显示设备的细节,
//他们只需调用GDI+库输出的类的一些方法即可完成图形操作,真正的绘图工作由这些方法交给特定的设备驱动程序来完成,
//GDI+使得图形硬件和应用程序相互隔离.从而使开发人员编写设备无关的应用程序变得非常容易。
//WindowsXP需要带上GDI+1.1的DLL，Windows7系统自带，所以可以直接使用。

#define  FT_API extern "C"
//#define WINAPIV __cdecl
//@跳过 FT_API
/////////////////////句柄类型定义//////////////////////////////////////
#ifndef DECLARE_HANDLEX
#define DECLARE_HANDLEX(name) struct name##__ { int unused; }; typedef struct name##__ *name
#endif

typedef void* HWEBVIEW;  //浏览器指针
DECLARE_HANDLEX(HCOMMAND); //命令行句柄
DECLARE_HANDLEX(HV8VALUE); //V8值句柄
DECLARE_HANDLEX(HV8CONTEXE);//V8环境句柄
DECLARE_HANDLEX(HFRAME);//框架句柄
DECLARE_HANDLEX(HBROWSER);//浏览器句柄
DECLARE_HANDLEX(HCOOKIE);
DECLARE_HANDLEX(HMENUMODEL);//菜单句柄
DECLARE_HANDLEX(HREQUEST);
DECLARE_HANDLEX(HREQUESTCONTEXE);
DECLARE_HANDLEX(HRESPONSE);
DECLARE_HANDLEX(HPOSTDATA);

struct FTSettings {
	LPCWSTR cache_path;
	LPCWSTR user_data_path;
	LPCWSTR user_agent;
	int remote_debugging_port;
	LPCWSTR browser_subprocess_path;
	bool persist_user_preferences;
	bool multi_threaded_message_loop;
	int log_severity;
	LPCWSTR locale;
	LPCWSTR accept_language_list;
	bool windowless_rendering_enabled;
	bool persist_session_cookies;
	int external_message_pump;
    bool no_sandbox;
};
struct FTWindowInfo {
    int x;
    int y;
    int w;
    int h;
    HWND hWnd;
 };
struct FTTime {
  int year;          // Four or five digit year "2007" (1601 to 30827 on
                     //   Windows, 1970 to 2038 on 32-bit POSIX)
  int month;         // 1-based month (values 1 = January, etc.)
  int day_of_week;   // 0-based day of week (0 = Sunday, etc.)
  int day_of_month;  // 1-based day of month (1-31)
  int hour;          // Hour within the current day (0-23)
  int minute;        // Minute within the current hour (0-59)
  int second;        // Second within the current minute (0-59 plus leap
                     //   seconds which may take it up to 60).
  int millisecond;   // Milliseconds within the current second (0-999)
};
struct FTCookie {
    const wchar_t* name;//名称
    const wchar_t* value;//值
    const wchar_t* domain;//域名
    const wchar_t* path;//路径
    int secure;//仅安全链接使用
	int httponly;//仅普通链接使用
	FTTime creation;//创建时间
	FTTime last_access;//访问时间
	int has_expires;//是否会过期
	FTTime expires;//过期时间
	int same_site;//同站值
	int priority;//优先级值
};

enum FT_MSG_Browser {
	type_BCreated = 1, //<浏览器创建完成
	type_browserdraw = 2, //<浏览器绘制
	type_Setcursor = 3, //<设置光标样式
	type_KeyboardRequested = 4,//虚拟键盘请求,文本输入类型
	type_MenuCreated = 5,//菜单即将被创建
	type_MenuCommand = 6,//菜单项被点击
	type_TitleChange = 7,//标题被改变
	type_AddressChange = 8,//地址被改变
	type_LoadEnd = 9,//加载完成
	type_LoadStart = 10,//加载开始
	type_LoadingStateChange = 11,//加载状态被改变
	type_StatusMessage = 12,//接收到状态信息
	type_LoadError = 13,//加载错误
	type_FaviconURLChange = 14,//网页图标被改变
	type_BeforePopup = 15,//即将打开新窗口
	type_DoClose = 16,//关闭浏览器
	type_ = 17,
};
enum FT_MSG_Init {
	type_CommandLine = 1, //<即将处理命令行
	type_ContextCreated = 2,//渲染_即将创建V8环境
	type_ContextReleased = 3,//即将释放V8环境
	type_WebKitInitialized = 4,//即将初始化WebKit
};
//typedef bool(WINAPI* FTCallbaFT)(int uMsg, LONG_PTR hWeBView, LONG_PTR hObj, LONG_PTR attach1, LONG_PTR attach2, LONG_PTR attach3, LONG_PTR attach4, bool* pbHWEBVIEWd,void* lParam);
//typedef void(WINAPI* FTCallCookie)(FTCookie& Cooks,bool blpIsLastCookie,int &attach1,void* lParam);

FT_API char* WINAPI FT_WCharToChar(const wchar_t* pwszUnicode);
FT_API wchar_t* WINAPI FT_CharToWChar(char *lpSrcBuffer) ;

//typedef bool CALLBAFT OnBeforeInit(int uMsg, LONG_PTR hWeBView, LONG_PTR hObj, LONG_PTR attach1, LONG_PTR attach2, LONG_PTR attach3, LONG_PTR attach4, bool* pbHWEBVIEWd,void* lParam)
FT_API int WINAPI FT_Browser_Init(HMODULE hModule, LPCWSTR subprocess_path, LPCWSTR cache_path, LPCWSTR user_agent, int debugging_port, void* pfun, void* lParam);
FT_API int WINAPI FT_Init(HMODULE hModule,FTSettings& basicinfo,void* pfun,void* hParam);

FT_API void WINAPI FT_RunMessageLoop();
FT_API void WINAPI FT_Shutdown();
FT_API void WINAPI FT_QuitMessageLoop();
//浏览器集
FT_API HWEBVIEW WINAPI FT_Browser_Create(HWND Parent,LONG_PTR hObj, RECT* Rect, int bcolor, LPCWSTR Url,HREQUESTCONTEXE rContext,void* pfun,void* lParam);
FT_API void WINAPI FT_Browser_Close(HWEBVIEW hWeBView);

FT_API void WINAPI FT_Browser_SendMouse(HWEBVIEW hWeBView, int uMsg, int wParam, int lParam);
FT_API void WINAPI FT_Browser_SendKey(HWEBVIEW hWeBView, int uMsg, int wParam, int lParam);
FT_API void WINAPI FT_Browser_Focus(HWEBVIEW hWeBView, bool IsFocus);
FT_API void WINAPI FT_Browser_Move(HWEBVIEW hWeBView, int left, int top, int nWidth, int nHeight);
FT_API BOOL WINAPI FT_Browser_GoBack(HWEBVIEW hWeBView);
FT_API BOOL WINAPI FT_Browser_GoForward(HWEBVIEW hWeBView);
FT_API BOOL WINAPI FT_Browser_IsBack(HWEBVIEW hWeBView);
FT_API BOOL WINAPI FT_Browser_IsForward(HWEBVIEW hWeBView);
FT_API BOOL WINAPI FT_Browser_IsLoading(HWEBVIEW hWeBView);
FT_API void WINAPI FT_Browser_ReloadIgnoreCache(HWEBVIEW hWeBView);
FT_API void WINAPI FT_Browser_StopLoad(HWEBVIEW hWeBView);
FT_API void WINAPI FT_Browser_Release(HWEBVIEW hWeBView);
FT_API void WINAPI FT_Browser_Refresh(HWEBVIEW hWeBView);
FT_API int WINAPI FT_Browser_GetFrameCount(HWEBVIEW hWeBView);
FT_API HFRAME WINAPI FT_Browser_GetMframe(HWEBVIEW hWeBView);
FT_API HFRAME WINAPI FT_Browser_GetFframe(HWEBVIEW hWeBView);
FT_API int WINAPI FT_Browser_GetIdentifier(HWEBVIEW hWeBView);
FT_API HFRAME WINAPI FT_Browser_GetFrame(HWEBVIEW hWeBView,wchar_t* pFrame);
FT_API void WINAPI FT_Browser_StartDownload(HWEBVIEW hWeBView,LPCWSTR pURL);
FT_API BOOL WINAPI FT_Browser_IsSame(HWEBVIEW hWeBView,HBROWSER hBrowser);
//框架集
FT_API void WINAPI FT_Frame_LoadUrl(HFRAME frame, const wchar_t* url);
FT_API const wchar_t* WINAPI FT_Frame_GetUrl(HFRAME frame);
FT_API BOOL WINAPI FT_Frame_ExecJs(HFRAME frame, LPCWSTR wszScript, LPCWSTR kurl,int cor);
FT_API LPCWSTR WINAPI FT_Frame_GetName(HFRAME frame);
FT_API LPCWSTR WINAPI FT_Frame_GetWebcode(HFRAME frame);
FT_API LPCWSTR WINAPI FT_Frame_GetWebText(HFRAME frame);
FT_API HFRAME WINAPI FT_Frame_GetParent(HFRAME frame);
FT_API BOOL WINAPI FT_Frame_IsFocused(HFRAME frame);
FT_API BOOL WINAPI FT_Frame_IsMain(HFRAME frame);
FT_API void WINAPI FT_Frame_ViewSource(HFRAME frame);

//Cookies集
FT_API HCOOKIE WINAPI FT_Cookies_GetGlobalManager();
//回调类型
//typedef void CALLBAFT OnEnumAllCookies(FTCookie& Cooks,bool blpIsLastCookie,int &attach1,void* lParam)
FT_API BOOL WINAPI FT_Cookies_EnumAll (HCOOKIE manager,const TCHAR* szMatchURL, BOOL blpOnlyHttp, void* pfun, void* hParam);
FT_API BOOL WINAPI FT_Cookies_Set (HCOOKIE manager,const TCHAR* szMatchURL, FTCookie& pcookie);
FT_API BOOL WINAPI FT_Cookies_Delete (HCOOKIE manager,const TCHAR* szMatchURL, const TCHAR* name);
FT_API BOOL WINAPI FT_Cookies_FlushStore (HCOOKIE manager);
FT_API void WINAPI FT_Cookies_SetSupportedSchemes (HCOOKIE manager,wchar_t** schemes,bool include_defaults);
//V8值对象
FT_API HV8VALUE WINAPI FT_V8CreateString(LPCWSTR pValue);
FT_API HV8VALUE WINAPI FT_V8CreateInt(int pValue);
FT_API HV8VALUE WINAPI FT_V8CreateFunction(LPCWSTR Funname,void* pfun, void* hParam);
FT_API HV8VALUE WINAPI FT_V8CreateObject(void* pfun, void* hParam) ;
FT_API const wchar_t* WINAPI FT_V8GetStringValue(HV8VALUE V8Value);
FT_API bool WINAPI FT_V8SetValue(HV8VALUE V8Value, LPCWSTR key, HV8VALUE pValue, int attribute);
FT_API bool WINAPI FT_V8IsFunction(HV8VALUE V8Value);
FT_API bool WINAPI FT_V8IsString(HV8VALUE V8Value);
FT_API bool WINAPI FT_V8IsInt(HV8VALUE V8Value);
FT_API int WINAPI FT_V8GetIntValue(HV8VALUE V8Value);
FT_API HV8VALUE WINAPI FT_V8ExecuteFunction_Int(HV8VALUE V8Value, int* pargs,int hCount);
FT_API HV8VALUE WINAPI FT_V8ExecuteFunction_String(HV8VALUE V8Value, wchar_t** pargs,int hCount);
FT_API bool WINAPI FT_V8SetValueEx(HV8VALUE V8Value, LPCWSTR key, int settings, int attribute);
FT_API bool WINAPI FT_V8SetValueindex(HV8VALUE V8Value,int index,HV8VALUE pValue);
FT_API bool WINAPI FT_V8IsObject(HV8VALUE V8Value);
FT_API bool WINAPI FT_V8IsNull(HV8VALUE V8Value);
//V8环境对象
FT_API HV8VALUE WINAPI FT_V8ContextGetGlobal(HV8CONTEXE context);
FT_API bool WINAPI FT_V8ContextEnter(HV8CONTEXE context) ;
FT_API bool WINAPI FT_V8ContextExit(HV8CONTEXE context);
FT_API bool WINAPI FT_V8ContextEval(HV8CONTEXE context,LPCWSTR code,LPCWSTR script_url,int start_line,uintptr_t* retval) ;
FT_API bool WINAPI FT_V8ContextIsSame(HV8CONTEXE context, HV8CONTEXE hcontext);
FT_API bool WINAPI FT_V8ContextIsValid(HV8CONTEXE context);
FT_API bool WINAPI FT_V8ContextInContext(HV8CONTEXE context);
FT_API void* WINAPI FT_V8ContextGetTaskRunner(HV8CONTEXE context);

FT_API void WINAPI FT_RegisterExtension(const wchar_t* key, LPCWSTR extensionCode);
//typedef void CALLBAFT OnRegisterExtensionEx(LPCWSTR name, HV8VALUE object, LONG_PTR arguments, HV8VALUE retval, LPCWSTR exception,bool* pbHWEBVIEWd, void* lParam)
FT_API void WINAPI FT_RegisterExtensionEx(const wchar_t* key, LPCWSTR extensionCode, void* pfun, void* hParam);
//命令行集
FT_API void WINAPI FT_CommandLine_AppendSwitch(HCOMMAND Command, const wchar_t* name);
FT_API void WINAPI FT_CommandLine_AppendSwitchWithValue(HCOMMAND Command, const wchar_t* name, const wchar_t* value);
FT_API const wchar_t* WINAPI FT_CommandLine_GetSwitchValue(HCOMMAND Command,const wchar_t * name) ;
FT_API const wchar_t* WINAPI FT_CommandLine_GetProgram(HCOMMAND Command);
FT_API bool WINAPI FT_CommandLine_HasSwitch(HCOMMAND Command, const wchar_t * name);
FT_API bool WINAPI FT_CommandLine_HasSwitches(HCOMMAND Command);
//菜单
FT_API bool WINAPI FT_Menu_Clear(HMENUMODEL menu);
FT_API int WINAPI FT_Menu_GetCount(HMENUMODEL menu);
FT_API bool WINAPI FT_Menu_AddSeparator(HMENUMODEL menu);
FT_API bool WINAPI FT_Menu_AddItem(HMENUMODEL menu,int command_id,const wchar_t* item);
FT_API bool WINAPI FT_Menu_AddCheckItem(HMENUMODEL menu,int command_id,const wchar_t* item);
FT_API bool WINAPI FT_Menu_AddRadioItem(HMENUMODEL menu, int command_id,const wchar_t* item, int groupid);
FT_API HMENUMODEL WINAPI FT_Menu_AddSubMenu(HMENUMODEL menu, int command_id,const wchar_t* item);
FT_API bool WINAPI FT_Menu_Remove(HMENUMODEL menu, int command_id);
//请求
FT_API HREQUEST WINAPI FTRequest_Create();
FT_API const wchar_t* WINAPI FTRequest_GetMethod(HREQUEST request);
FT_API bool WINAPI FTRequest_SetMethod(HREQUEST request, const wchar_t* Method);
FT_API const wchar_t* WINAPI FTRequest_GetURL(HREQUEST request);
FT_API bool WINAPI FTRequest_SetURL(HREQUEST request, const wchar_t* URL);
FT_API bool WINAPI FTRequest_IsReadOnly(HREQUEST request);
FT_API bool WINAPI FTRequest_SetReferrer(HREQUEST request,const wchar_t* URL,int policy);
FT_API const wchar_t* WINAPI FTRequest_GetReferrerURL(HREQUEST request);
FT_API int WINAPI FTRequest_GetReferrerPolicy(HREQUEST request);
FT_API HPOSTDATA WINAPI FTRequest_GetPostData(HREQUEST request);
FT_API bool WINAPI FTRequest_SetPostData(HREQUEST request, HPOSTDATA PostData);
//FT_API void WINAPI FTRequest_GetHeaderMap(HREQUEST request, std::multimap<std::wstring, std::wstring> HeaderMap);
//FT_API void WINAPI FTRequest_SetHeaderMap(HREQUEST request, std::multimap<std::wstring, std::wstring> HeaderMap);
FT_API const wchar_t* WINAPI FTRequest_GetHeaderByName(HREQUEST request, wchar_t* Name);
//请求环境
FT_API HREQUESTCONTEXE WINAPI FTRequestContext_GetGlobalContext();
FT_API bool WINAPI FTRequestContext_IsGlobal(HREQUESTCONTEXE Context);

//响应
FT_API HRESPONSE WINAPI FTResponse_Create();
FT_API bool WINAPI FTResponse_IsReadOnly(HRESPONSE response);
FT_API int WINAPI FTResponse_GetError(HRESPONSE response);
FT_API bool WINAPI FTResponse_SetError(HRESPONSE response,int error);
FT_API int WINAPI FTResponse_GetStatus(HRESPONSE response) ;
FT_API bool WINAPI FTResponse_SetStatus(HRESPONSE response, int status);
FT_API const wchar_t* WINAPI FTResponse_GetStatusText(HRESPONSE response);
FT_API void WINAPI FTResponse_SetStatusText(HRESPONSE response, wchar_t* Name);

