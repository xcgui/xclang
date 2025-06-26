#pragma once

//@模块名称  炫WebView2
//@模块作者 hxznhf
//@版本  0.2(Beta)
//@日期  2024-11-21
//@QQ 568415950
//@依赖  module_base.h, module_xcgui.h
//@安装目录 常规
//@模块备注  WebView2浏览器模块，Windows10 2004版本及以上已内置WebView2运行库，其它系统需要自行下载安装
// 2024年11月21日：
// 移除 初始化() 和 绑定窗口() 命令，简化为 创建自元素(元素句柄)  
// 修复 改了一堆垃圾代码，并解决了透明窗口样式最小化再恢复窗口后无法正常显示的问题


//@src "XWebview2.cpp"


#ifdef _WIN64
//@lib "x64/WebView2LoaderStatic.lib"
#else
//@lib "x86/WebView2LoaderStatic.lib"
#endif


#include "module_base.h"
#include "module_xcgui.h"
#include "xc_mkStr.h"
#include "XWebview2.h"



//@启用枚举前缀

//@分组{ 类型定义


//@启用枚举前缀
//@别名 WebView2事件 
enum _Web2Event {
	//@别名 初始化完成
	Web2Event_OnInitComplete = 1,
	//@别名 收到消息
	Web2Event_OnReciveMessage = 2,
	//@别名 导航开始
	Web2Event_OnNavigationStarting = 3,
	//@别名 导航完成
	Web2Event_OnNavigationCompleted = 4,
	//@别名 新窗口请求
	Web2Event_OnNewWindowRequested = 5,

};
//@禁用枚举前缀



//@分组}

//@分组{ 数据类型


//@隐藏{

//@隐藏}


//@别名 WebView2浏览器
class XC_WebView2 {
private:
	HWND phWnd = nullptr;
	HELE hEle = nullptr;
public:
	//@隐藏{
	web2obj* web2 = nullptr;
	//@隐藏}
	XC_WebView2() {


	}
	~XC_WebView2() {

	}
	//@隐藏{
	int  OnWindowSize(HWINDOW hWindow, UINT nFlags, SIZE* pSize, BOOL* pbHandled) {
		if (!phWnd || !this->hEle)return 0;

		RECT rect{};
		XEle_GetRect(this->hEle, &rect);
		MoveWindow(phWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, FALSE);
		if (web2) {
			Web2_UpdateLayout(web2);
		}

		return 0;
	}
	int  OnSize(HELE hEle, BOOL* 是否拦截) {
		if (!phWnd || !hEle)return 0;

		RECT rect{};
		XEle_GetRect(hEle, &rect);
		MoveWindow(phWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, FALSE);
		if (web2) {
			Web2_UpdateLayout(web2);
		}

		return 0;
	}
	int  OnShow(HELE hEle, BOOL 显示, BOOL* 是否拦截) {
		if (!phWnd || !hEle)return 0;
		ShowWindow(phWnd, 显示 ? SW_SHOW : SW_HIDE);
		return 0;
	}
	//@隐藏}


	//@别名 创建自元素(元素句柄)
	//@备注 初始化浏览器对象,绑定浏览器对象到炫彩窗口中的UI控件
	//@参数 元素句柄 炫彩UI控件的句柄
	BOOL CreateFromhEle( HELE hEle) {

		if (!hEle)return FALSE;
		HWND hWnd = XWidget_GetHWND(hEle);
		this->hEle = hEle;

		//判断窗口类名是否已经注册过
		WNDCLASSEXW wc = { 0 };
		if (!GetClassInfoExW(NULL, L"XC_WIN32WEB2_BOX", &wc)) {
			//注册窗口类 XC_WIN32WEB2_BOX
			// 填充WNDCLASSEX结构以定义窗口类的属性

			wc.cbSize = sizeof(WNDCLASSEXW); // 设置结构的大小
			wc.style = CS_HREDRAW | CS_VREDRAW; // 设置窗口样式
			wc.lpfnWndProc = WndProc_XC_WIN32WEB2_BOX; // 设置窗口过程函数
			wc.cbClsExtra = 0; // 额外类内存的大小，通常设置为0
			wc.cbWndExtra = 0; // 额外窗口内存的大小，通常设置为0
			wc.hInstance = NULL; // 设置应用程序实例句柄
			wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 设置窗口图标
			wc.hCursor = LoadCursor(NULL, IDC_ARROW); // 设置窗口光标
			wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 设置窗口背景色
			wc.lpszMenuName = NULL; // 不使用菜单
			wc.lpszClassName = L"XC_WIN32WEB2_BOX"; // 设置窗口类名
			wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // 设置小图标
			if (!RegisterClassExW(&wc))
			{

				return FALSE;
			}
		}
		phWnd = CreateWindowExW(0, L"XC_WIN32WEB2_BOX", NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, (HWND)hWnd, NULL, NULL, NULL);
		if (!phWnd)
		{
			return FALSE;
		}

		XWnd_RegEventCPP1(XWidget_GetHWINDOW(hEle), WM_SIZE, &XC_WebView2::OnWindowSize);
		XEle_RegEventCPP1(hEle, XE_SIZE, &XC_WebView2::OnSize);
		XEle_RegEventCPP1(hEle, XE_SHOW, &XC_WebView2::OnShow);

		web2 = Web2_Create(phWnd);
		return !web2;
	}

	//@别名 加载网页(url)
	//@备注 加载网页
	//@参数 url 网页地址
	BOOL LoadUrl(const wchar_t* url) {
		if (!web2)return false;
		return Web2_LoadUrl(web2, url);
	}

	//@别名 执行JS(代码,返回结果)
	//@备注 执行JS代码
	//@参数 代码 JS代码
	//@参数 返回结果 返回值
	BOOL ExecJs(const wchar_t* js, CXText& result) {
		if (!web2)return false;
		std::wstring ret;
		bool success = Web2_RunJs2(web2, js, &ret);

		result.resize(0);
		result.append(ret.c_str());
		return success;
	}

	//@别名 执行JS异步(代码)
	//@备注 执行JS代码
	//@参数 代码 JS代码
	//@参数 结果回调函数,定义：(整型 错误代码,常量 字符型* 结果文本)
	BOOL ExecJs(const wchar_t* js, void* callback) {
		if (!web2)return false;
		std::wstring ret;
		bool success = Web2_RunJs(web2, js, callback);

		return success;
	}


	//@别名 置用户代理(用户代理)
	//@备注 设置浏览器的用户代理（UserAgent）
	//@参数 用户代理 用户代理文本
	void SetUserAgent(const wchar_t* ua) {
		if (!web2)return;
		Web2_SetUserAgent(web2, ua);
	}

	//@别名 取用户代理()
	//@备注 获取浏览器的用户代理（UserAgent）
	CXText GetUserAgent() {
		if (!web2)return  CXText();
		LPWSTR ua = nullptr;
		Web2_GetUserAgent(web2, &ua);
		CXText ret;
		ret.append(ua);

		return ret;
	}


	//@别名 启用开发者工具(启用)
	//@备注 启用开发者工具
	void EnableDevTools(BOOL 启用) {
		if (!web2)return;
		Web2_EnableDevTools(web2, 启用);
	}
	//@别名 启用右键菜单(启用)
	//@备注 启用浏览器页面的右键菜单
	void EnableContextMenu(BOOL 启用) {
		if (!web2)return;
		Web2_EnableContextMenus(web2, 启用);
	}

	//@别名 启用JS(启用)
	//@备注 允许JS脚本
	//@参数 启用 启用
	void EnableJs(BOOL 启用) {
		if (!web2)return;
		Web2_EnableScript(web2, 启用);
	}

	//@别名 绑定事件(事件类型,事件回调函数)
	//@备注 绑定浏览器事件
	//@参数 事件类型 WebView2事件
	//@参数 事件回调函数
	void BindEvent(int eventTpye, void* func) {
		if (!web2)return;
		Web2_BindEvent(web2, (Web2Event)eventTpye, func);
	}


	//@别名 发送WEB消息(消息)
	void SendWebMessage(const wchar_t* msg) {
		if (!web2)return;
		Web2_PostMessage(web2, msg);
	}

	//@别名 发送JSON消息(JSON)
	void SendJsonMessage(const wchar_t* json) {
		if (!web2)return;
		Web2_PostMessageJSON(web2, json);
	}

	//@别名 更新布局()
	//@备注 如果浏览器窗口位置不正常，用此方法手动更新布局
	void UpdateLayout() {
		if (!web2)return;
		Web2_UpdateLayout(web2);
	}


};


//@别名 WebView2填表
class WebView2_DOM {
	web2obj* web2 = nullptr;
public:
	WebView2_DOM() {
	}

	//@别名 初始化(WebView2浏览器)
	BOOL Init(XC_WebView2& xc_webview2) {
		if (!xc_webview2.web2)return FALSE;
		web2 = xc_webview2.web2;
		return TRUE;
	}

	//@别名 元素置Value(CSS选择器,值,成员索引)
	void Dom_SetValue(const wchar_t* selector, const wchar_t* value, int id = 0) {
		Web2_Dom_SetValue(web2, selector, value, id);
	}

	//@别名 元素置InnerHTML(CSS选择器,HTML文本,成员索引)
	void Dom_SetInnerHTML(const wchar_t* selector, const wchar_t* html, int id = 0) {
		Web2_Dom_SetInnerHTML(web2, selector, id, html);
	}

	//@别名 元素取InnerHTML(CSS选择器,返回内容,成员索引)
	void Dom_GetInnerHTML(const wchar_t* selector, CXText& html, int id = 0) {
		std::wstring ret;
		Web2_Dom_GetInnerHTML(web2, selector, id, &ret);
		html.resize(0);
		html.append(ret.c_str());
	}

	//@别名 元素置InnerText(CSS选择器,文本,成员索引)
	void Dom_SetInnerText(const wchar_t* selector, const wchar_t* text, int id = 0) {
		Web2_Dom_SetInnerText(web2, selector, id, text);
	}

	//@别名 元素取InnerText(CSS选择器,返回文本,成员索引)
	void Dom_GetInnerText(const wchar_t* selector, CXText& text, int id = 0) {
		std::wstring ret;
		Web2_Dom_GetInnerText(web2, selector, id, &ret);
		text.resize(0);
		text.append(ret.c_str());
	}

	//@别名 元素点击(CSS选择器,成员索引)
	void Dom_Click(const wchar_t* selector, int id = 0) {
		Web2_Dom_Click(web2, selector, id);
	}

	//@别名 元素滚动到(CSS选择器,成员索引)
	void Dom_ScrollTo(const wchar_t* selector, int id = 0) {
		Web2_Dom_ScrollTo(web2, selector, id);
	}

	//@别名 元素置焦点(CSS选择器,成员索引)
	void Dom_Focus(const wchar_t* selector, int id = 0) {
		Web2_Dom_Focus(web2, selector, id);
	}

	//@别名 元素置属性(CSS选择器,属性名,属性值,成员索引)
	void Dom_SetAttribute(const wchar_t* selector, const wchar_t* attrName, const wchar_t* attrValue, int id = 0) {
		Web2_Dom_SetAttribute(web2, selector, attrName, attrValue, id);
	}

	//@别名 元素取属性(CSS选择器,属性名,成员索引)
	CXText Dom_GetAttribute(const wchar_t* selector, const wchar_t* attrName, int id = 0) {
		std::wstring ret;
		Web2_Dom_GetAttribute(web2, selector, attrName, &ret, id);
		CXText attrValue;
		attrValue.resize(0);
		attrValue.append(ret.c_str());
		return attrValue;
	}

	//@别名 元素取坐标(CSS选择器,成员索引)
	RECT Dom_GetRect(const wchar_t* selector, int id = 0) {
		RECT rect{ 0,0,0,0 };
		std::wstring result;
		Web2_Dom_GetRect(web2, selector, result, id);
		CXText ret;
		ret.append2(result.c_str(), result.size());
		CXVector<CXText> text_rect =text_split(ret, L",");
		if (text_rect.size() == 4) {
			//XCL_log(L"===",text_rect[0].getPtr(), text_rect[1].getPtr(), text_rect[2].getPtr(), text_rect[3].getPtr());
			rect.left = StrToIntW(text_rect[0].getPtr() + 1);
			rect.top = StrToIntW(text_rect[1].getPtr());
			rect.right = StrToIntW(text_rect[2].getPtr());
			rect.bottom = StrToIntW(text_rect[3].getPtr());
		}

		return rect;
	}
};


//@分组}


