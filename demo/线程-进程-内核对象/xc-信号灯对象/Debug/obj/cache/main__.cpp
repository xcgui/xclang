#include "common__.h"
#include "main__.h"
extern HANDLE ghSemaphore;
HANDLE ghSemaphore;
DWORD WINAPI 线程函数(void* 用户数据)
{
	DWORD dwWaitResult;
	while(1)
	{
		Sleep(10);
		dwWaitResult = WaitForSingleObject(ghSemaphore, 0);
		if(WAIT_OBJECT_0 == dwWaitResult)
		{
			xcl_log(L"线程", GetCurrentThreadId(), L"等待成功 ok");
			ReleaseSemaphore(ghSemaphore, 1, NULL);
			break;
		}
		else if (WAIT_TIMEOUT == dwWaitResult)
		{
			xcl_log(L"线程", GetCurrentThreadId(), L"等待超时");
		}
	}
	return 0;
}
int WINAPI wWinMain(HINSTANCE 模块句柄, HINSTANCE 先前句柄, wchar_t* 命令行, int 窗口显示标识)
{
	ghSemaphore = xcl_CreateSemaphore(2, 2, NULL);
	HANDLE hThreads[10];
	{int i = 0; auto __var_for_count__1 = i + 10;
	for (;i<__var_for_count__1;i++)
	{
		hThreads[i] = xcl_CreateThread(线程函数, 0, 0);
	}}
	WaitForMultipleObjects(10, hThreads, TRUE, INFINITE) ;
	{int i = 0; auto __var_for_count__1 = i + 10;
	for (;i<__var_for_count__1;i++)
	{
		CloseHandle(hThreads[i]);
	}}
	CloseHandle(ghSemaphore);
	return 0;
}
