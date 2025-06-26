#pragma once
//@模块名称  MFC基础模块
//@版本  1.0  
//@日期  2023-12-18
//@作者  XCGUI  
//@模块备注  MFC基础模块, MFC对话框程序, 提供给需要使用MFC的用户参考
//炫语言 MFC对话框程序 示例
//对话框资源 和 图标, 添加在exe.rc中
//也可以 用炫彩界面库 附加到MFC窗口,把MFC窗口变成炫彩的
//*注意, MFC模块需要放在基础模块前面, 不然会提示 重复包含 windows.h

//@src "module_mfc.cpp"

//@隐藏{
//#include "resource.h"
// 关闭 MFC 的一些常见且经常可放心忽略的隐藏警告消息

#if !defined(_WIN32_WINNT) && !defined(_CHICAGO_)
#define  _WIN32_WINNT   0x0A00
#endif

#define _AFX_ALL_WARNINGS
#define  _AFXDLL
#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC 支持功能区和控制条

#define         IDD_DIALOG1    128

extern int AFXAPI AfxWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine, int nCmdShow);
	
class CMFCApplication1App : public CWinApp
{
public:
	CMFCApplication1App();

	// 重写
public:
	virtual BOOL InitInstance();

	// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication1App theApp;


// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
	// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 标准构造函数
// 	CMFCApplication1Dlg() {
// 	}

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};

//@隐藏}