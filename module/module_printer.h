#pragma once

//@模块名称  打印机
//@版本  1.0
//@日期  2025-1-10
//@作者  XCGUI
//@模块备注  2024-12-28
//1.使用Cleanup函数集中管理资源的释放，确保在析构函数中调用
//2.增加了对CreateFont和LoadImage等函数的返回值检查，避免空指针异常
//3.减少了不必要的系统调用和资源分配
//@依赖  module_base.h
//@QQ 154460336
//@src  "module_printer.cpp"

#if XC_MODULE
#include <windows.h>
#include "module_base.h"
#endif

#include "Commdlg.h"
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")   // 链接GDI+库
#pragma comment(lib, "comdlg32.lib")  // 链接通用对话框库

//@别名  打印机类
class CXPrinter
{
public:
    CXPrinter();
    ~CXPrinter();



    // 打印功能

	//@别名 打印开始()
	//@参数 句柄，可用取HWND()获取
	//@参数 作业名称
	BOOL StartPrint(HWND hWnd,const wchar_t* printerName);

	//@别名 打印设置()
	void PrintSet(HWND hwnd);

	//@别名 打印页开始()
	void StartPrintPage();

	//@别名 打印页结束()
	void EndPrintPage();

	//@别名 打印结束()
	void EndPrint();

	//@别名 置字体()
	//@参数 字体名称
	//@参数 字体大小
	//@参数 字体粗细，在0到1000之间指定字体的权值，如400表示标准体，700表示黑（粗）体，省略为400
	//@参数 是否斜体，如果设置为TRUE，则字体设置为斜体，省略为FALSE
	//@参数 是否下划线，如果设置为TRUE，则字体增加下划线，省略为FALSE
	//@参数 是否删除线，如果设置为TRUE，则字体增加删除线，省略为FALSE
	//@返回 如果函数调用成功，返回值是一种逻辑字体句柄；如果函数调用失败，返回值为NULL
	BOOL SetFont(const wchar_t* pFontName, int nFontSize, int FnWeight=FW_NORMAL, bool fdwItalic=FALSE, bool fdwUnderline=FALSE, bool fdwStrikeOut=FALSE);

	//@别名 置颜色()
	//@参数 如 RGB(255, 0, 0)
	void SetTextColor(COLORREF color);

	//@别名 打印文本()
	void PrintText(int x, int y, const wchar_t* pString);

	//@别名 打印图片()
	void PrintImage(int x, int y, const wchar_t* pFileName);
	
	//@别名 打印图片扩展()
	void PrintImageEx(int x, int y, int width, int height, const wchar_t* pFileName);

	//@备注 注意 如果是QQ截图保存的位图, 可能需要用其他工具重新保存以下, 否则会失败
	//@别名 打印位图()
	void PrintBitmap(int x, int y, const wchar_t* pFileName);

    //@别名 打印窗口()
    void PrintWindow(HWND hWnd);                          // 打印窗口内容

private:
    HDC m_hDC_Print;                                       // 打印机设备上下文
    HFONT m_hFont;                                         // 当前字体
    HFONT m_hOldFont;                                      // 旧字体（用于恢复）
    RECT m_rcMargin;                                       // 打印边距
    ULONG_PTR m_gdiplusToken;                              // GDI+令牌
    Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;    // GDI+启动参数
    PRINTDLG m_printDlg;                                   // 打印对话框结构
    float m_fScaleX;                                       // 水平缩放比例

    void Cleanup();                                        // 清理资源
    void InitializeGdiplus();                              // 初始化GDI+
    void ShutdownGdiplus();                                // 关闭GDI+
    void InitializePrintDlg(HWND hWnd);                    // 初始化打印对话框
    void InitializePageSetupDlg(HWND hwnd, PAGESETUPDLG& psd); // 初始化页面设置对话框
    void CalculateScalingFactors(HDC hdc);                 // 计算缩放比例
};

