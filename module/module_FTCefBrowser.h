#ifndef  FTBrowser_H
#define  FTBrowser_H

#pragma once

//@模块名称  FTBrowser_class 
//@版本  1.0  
//@日期  2022-11-3
//@作者  易团雪  
//@模块备注 作为图形设备接口的GDI+使得应用程序开发人员在输出屏幕和打印机信息的时候无需考虑具体显示设备的细节,
//他们只需调用GDI+库输出的类的一些方法即可完成图形操作,真正的绘图工作由这些方法交给特定的设备驱动程序来完成,
//GDI+使得图形硬件和应用程序相互隔离.从而使开发人员编写设备无关的应用程序变得非常容易。
//WindowsXP需要带上GDI+1.1的DLL，Windows7系统自带，所以可以直接使用。
//@依赖  module_FTBrowser.h

class XCCefBrowser {
public:
	//@隐藏{
	XCCefBrowser();
	~XCCefBrowser();
	static XCCefBrowser* GetInstance();
	//@隐藏}
	HELE CefCreate(int x,int y,int w,int h,LPCWSTR url,HXCGUI hParent) ;
	void CefGoBack();
	void CefGoForward();
	void CefLoadUrl(LPCWSTR url);
	BOOL CefExecJs(wchar_t* url);
	void CefRefresh();
	const wchar_t* CefGetUrl();
	const wchar_t* CefGetName();
	int GetFrameCount();
	HANDLE GetMframe();
	HANDLE GetFframe();
	const wchar_t* GetWebcode();
	const wchar_t* GetWebText();
	BOOL EnumAllCookies(const TCHAR* szMatchURL, BOOL blpOnlyHttp);
	virtual void OnBrowserCreated(HELE hele,HWEBVIEW hWebView) {}
	virtual void OnBrowserTitleChange(HELE hele,const TCHAR* title) {}
	virtual void OnBrowserUrlChange(HELE hele,const TCHAR* url) {}
	virtual void OnBrowserLoadEnd(HELE hele,int httpStatusCode) {}
	virtual void OnBrowserLoadStart(HELE hele,int transition_type){}
	virtual void OnBrowserLoadingStateChange(HELE hele,bool isLoading,bool canGoBack,bool canGoForward){}
	virtual void OnBrowserStatusMessage(HELE hele,const TCHAR* value){}
	virtual void OnBrowserLoadError(HELE hele,int errorCode,const TCHAR* errorText,const TCHAR* failedUrl) {}
	virtual void OnBFaviconURLChange(HELE hele,const TCHAR* url,const TCHAR* url2){}
	virtual void OnBEnumAllCookies(FTCookie& cook,int upResult){}
protected:	//受保护的
	HBITMAP hbitmap;
	HWEBVIEW hWebView;
	void CefSetCursor(DWORD dwCursorType);
	int OnImeStartComposition(HELE hEle,WPARAM wParam,LPARAM lParam);

	static BOOL CALLBACK OnCefCallback(int uMsg, HWEBVIEW handler, LONG_PTR hObj, LONG_PTR attach1, LONG_PTR attach2, LONG_PTR attach3, LONG_PTR attach4, LONG_PTR attach5,void* callbackParam);
	static void CALLBACK OnEnumAllCookies(FTCookie& cooks,LONG_PTR upResult,void* hCallParam);
	int OnEventProc(HELE hEle,UINT nEvent, WPARAM wParam, LPARAM lParam, BOOL *pbHandled);
	int OnDraw(HELE hEle, HDRAW hDraw,BOOL *pbHandled) ;
};


#endif