#include "common__.h"
#include "main__.h"
int 主窗口类::运行()
{
	{
	HMODULE __hModule = GetModuleHandle(NULL);
	UINT __size = 0;
	void* __data = rc_findFileByID(IDR_UI_ZIP, &__size, __hModule);
	if (__data) {
		m_hWindow = (HWINDOW)XC_LoadLayoutZipMemEx(__data, __size, _布局文件, NULL, NULL, NULL, NULL, NULL);
	}
#ifdef _DEBUG
	if(NULL==m_hWindow) {MessageBox(NULL, L"句柄为空:\"m_hWindow\"", L"提示", 0); return 0;}
#endif
	_百度一下.m_hEle = (HELE)XC_GetObjectByName(L"百度一下");
	_按钮_回到顶部.m_hEle = (HELE)XC_GetObjectByName(L"回到顶部");
	_搜索框.m_hEle = (HELE)XC_GetObjectByName(L"搜索框");
	_按钮_新闻.m_hEle = (HELE)XC_GetObjectByName(L"新闻");
#ifdef _DEBUG
if(NULL==_百度一下.m_hEle) {MessageBox(NULL, L"绑定变量句柄为空:\"_百度一下\"", L"提示", 0); return 0;}
if(NULL==_按钮_回到顶部.m_hEle) {MessageBox(NULL, L"绑定变量句柄为空:\"_按钮_回到顶部\"", L"提示", 0); return 0;}
if(NULL==_搜索框.m_hEle) {MessageBox(NULL, L"绑定变量句柄为空:\"_搜索框\"", L"提示", 0); return 0;}
if(NULL==_按钮_新闻.m_hEle) {MessageBox(NULL, L"绑定变量句柄为空:\"_按钮_新闻\"", L"提示", 0); return 0;}
#endif
	XEle_RegEventCPP(_百度一下.m_hEle, XE_BNCLICK, &主窗口类::按钮点击_百度一下);
	XEle_RegEventCPP(_按钮_回到顶部.m_hEle, XE_BNCLICK, &主窗口类::按钮点击_回到顶部);
	XEle_RegEventCPP(_搜索框.m_hEle, XE_EDIT_CHANGED, &主窗口类::编辑框_内容改变);
	XEle_RegEventCPP(_按钮_新闻.m_hEle, XE_BNCLICK, &主窗口类::按钮点击_新闻);
	}
	_搜索框.EnableEvent_XE_MOUSEWHEEL(FALSE);
	Show(TRUE);
	return 0;
}
int 主窗口类::按钮点击_新闻(BOOL* 是否拦截)
{
	xcl_log(L"按钮点击_新闻");
	return 0;
}
int 主窗口类::按钮点击_百度一下(BOOL* 是否拦截)
{
	xcl_log(L"按钮点击_百度一下");
	return 0;
}
int 主窗口类::编辑框_内容改变(BOOL* 是否拦截)
{
	xcl_log(L"编辑框_内容改变");
	xcl_log(_搜索框.GetText());
	return 0;
}
int 主窗口类::按钮点击_回到顶部(BOOL* 是否拦截)
{
	xcl_log(L"按钮点击_回到顶部");
	HELE 布局框架 = (HELE)XC_GetObjectByName(L"布局框架");
	XSView_ScrollTop(布局框架);
	return 0;
}
int WINAPI wWinMain(HINSTANCE 模块句柄, HINSTANCE 先前句柄, wchar_t* 命令行, int 窗口显示标识)
{
	XInitXCGUI(TRUE);
	XC_EnableAutoRedrawUI(TRUE);
	HMODULE __hModule = GetModuleHandle(NULL);
	UINT __size = 0;
	void* __data = rc_findFileByID(IDR_UI_ZIP, &__size, __hModule);
	BOOL __bRetRes = XC_LoadResourceZipMem(__data, __size, LR"--(resource.res)--");
	if(0==__bRetRes) xcl_log(L"*加载资源文件失败: resource.res");
	主窗口类 主窗口;
	主窗口.运行();
	XRunXCGUI();
	XExitXCGUI();
	return 0;
}
