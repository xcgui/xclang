#pragma once
//@模块名称  MFC模块
//@版本  1.0  
//@日期  2023-12-18
//@作者  XCGUI  
//@模块备注  MFC模块, 对话框资源 和 图标, 添加在exe.rc中
//也可以 用炫彩界面库 附加到MFC窗口,把MFC窗口变成炫彩的
//*注意, MFC模块需要放在基础模块前面, 不然会提示 重复包含 windows.h


//@复制文件 @当前模块路径 "r\\mfc140ud.lib"
//@复制文件 @当前模块路径 "r\\mfcs140ud.lib"


//@隐藏{

// 关闭 MFC 的一些常见且经常可放心忽略的隐藏警告消息
#if !defined(_WIN32_WINNT) && !defined(_CHICAGO_)
#define  _WIN32_WINNT   0x0A00
#endif

#define _AFX_ALL_WARNINGS
#define  _AFXDLL
#include <afxwin.h>         // MFC 核心组件和标准组件
int AFXAPI AfxWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine, int nCmdShow);
//@隐藏}
//@别名 窗口类
class CMyFrameWnd : public CFrameWnd{
	//@隐藏{
	DECLARE_MESSAGE_MAP()
	//@隐藏}
public:
	LRESULT OnCreate( WPARAM wParam, LPARAM IParam );
	//@隐藏{
	afx_msg void OnDestroy();
	//@隐藏}
};
//@隐藏{
BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	ON_MESSAGE( WM_CREATE, OnCreate )
	ON_WM_DESTROY()
END_MESSAGE_MAP()

LRESULT CMyFrameWnd::OnCreate(WPARAM wParam, LPARAM IParam){
	AfxMessageBox( L"WM_CREATE" );
	return 0;
}
void CMyFrameWnd::OnDestroy( ){
	PostQuitMessage(0);
}

class MyApp : public CWinApp{
public:
	MyApp(){
		
	}
	// 重写
public:
	virtual BOOL InitInstance();
};
MyApp theApp;
BOOL MyApp::InitInstance(){
    // 创建主窗口
    CMyFrameWnd* pMainFrame = new CMyFrameWnd;
	// 计算屏幕宽度和高度
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	// 计算窗口宽度和高度
	int nWidth = 500;
	int nHeight = 400;
	// 计算窗口左上角的位置
	int x = (screenWidth - nWidth) / 2;
	int y = (screenHeight - nHeight) / 2;
	pMainFrame->Create(NULL, L"MFCBase",WS_OVERLAPPEDWINDOW,RECT{x,y,x + nWidth,y + nHeight});
    m_pMainWnd = pMainFrame;
    // 显示主窗口
    pMainFrame->ShowWindow(SW_SHOW);
    pMainFrame->UpdateWindow();
    return TRUE;
}





//@隐藏}