#include "common__.h"
#include "main__.h"
extern int 公共数据;
int 公共数据 = 0;
DWORD WINAPI 线程函数1(void* 用户数据)
{
	xcl_log2(L"线程1运行, 参数: ", (int)用户数据);
	{int i = 0; auto __var_for_count__1 = i + 100;
	for (;i<__var_for_count__1;i++)
	{
		公共数据 ++;
		xcl_log(L"线程1:", 公共数据);
	}}
	xcl_log(L"线程1退出");
	return 0;
}
DWORD WINAPI 线程函数2(void* 用户数据)
{
	xcl_log2(L"线程2运行, 参数: ", (int)用户数据);
	{int i = 0; auto __var_for_count__1 = i + 100;
	for (;i<__var_for_count__1;i++)
	{
		公共数据 ++;
		xcl_log(L"线程2:", 公共数据);
	}}
	xcl_log(L"线程2退出");
	return 0;
}
int WINAPI wWinMain(HINSTANCE 模块句柄, HINSTANCE 先前句柄, wchar_t* 命令行, int 窗口显示标识)
{
	int data = 100;
	HANDLE hThread1 = xcl_CreateThread(线程函数1, (void*)data, 0);
	int data2 = 200;
	HANDLE hThread2 = xcl_CreateThread(线程函数2, (void*)data2, 0);
	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	return 0;
}
