#include "common__.h"
#include "main__.h"
BOOL 扫描目录(CXText 目录名)
{
	xcl_log(L"->", 目录名);
	CXText 目录T = 目录名 + CXText(L"\\*.*");
	WIN32_FIND_DATAW 文件信息 = {0};
	HANDLE hFind = FindFirstFile(目录T, &文件信息);
	if(INVALID_HANDLE_VALUE == hFind)
	{
		return FALSE;
	}
	while(FindNextFile(hFind, &文件信息))
	{
		if(文件信息.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			if(L'.' != 文件信息.cFileName[0])
			{
				wchar_t 全路径[256] = {0};
				if(PathCombine(全路径, 目录名, 文件信息.cFileName))
				{
					扫描目录(全路径);
				}
			}
		}
		else if (文件信息.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE || 文件信息.dwFileAttributes & FILE_ATTRIBUTE_NORMAL)
		{
			xcl_log2(目录名, L"\\", 文件信息.cFileName);
		}
	}
	FindClose(hFind);
	return TRUE;
}
int WINAPI wWinMain(HINSTANCE 模块句柄, HINSTANCE 先前句柄, wchar_t* 命令行, int 窗口显示标识)
{
	CXText 当前目录 = xcl_getCurrentDir();
	扫描目录(当前目录);
	return 0;
}
