﻿#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT 27015

def int main()
	//----------------------
	// Declare and initialize variables.
	WSAData wsaData
	int iResult

	SOCKET ConnectSocket = INVALID_SOCKET
	SOCKADDR_IN_ULONG clientService
	const char *sendbuf = A"this is a test"
	char recvbuf[DEFAULT_BUFLEN]
	int recvlen = DEFAULT_BUFLEN

	//----------------------
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(1, 1), &wsaData)
	if (iResult != 0)
		xcl_log("WSAStartup failed:", iResult, WSAGetLastErrorMessage())
		return 1

	//----------------------
	// Create a SOCKET for connecting to server
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)
	if (INVALID_SOCKET == ConnectSocket)
		xcl_log("socket failed: %ld\n", WSAGetLastErrorMessage())
		WSACleanup();
		return 1

	//----------------------
	// The sockaddr_in structure specifies the address family,
	// IP address, and port of the server to be connected to.
	clientService.sin_family = AF_INET;
	clientService.sin_addr.S_addr = inet_addr(A"127.0.0.1")
	clientService.sin_port = htons(DEFAULT_PORT)
	
	//----------------------
	// Connect to server.
	iResult = connect(ConnectSocket, (SOCKADDR*) &clientService, sizeof(clientService))
	if (SOCKET_ERROR == iResult)
		closesocket(ConnectSocket)
		xcl_log("connect failed:", WSAGetLastErrorMessage())
		WSACleanup()
		return 1

	// Send an initial buffer
	iResult = send(ConnectSocket, sendbuf, strlen(sendbuf), 0);
	if (SOCKET_ERROR == iResult)
		xcl_log("send failed:", WSAGetLastErrorMessage())
		closesocket(ConnectSocket)
		WSACleanup()
		return 1

	xcl_log("Bytes Sent:", iResult)

	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (SOCKET_ERROR == iResult)
		xcl_log("shutdown failed:", WSAGetLastErrorMessage());
		closesocket(ConnectSocket)
		WSACleanup()
		return 1

	// Receive until the peer closes the connection
	iResult = 1;
	while (iResult > 0)
		iResult = recv(ConnectSocket, recvbuf, recvlen, 0);
		if (iResult > 0)
			xcl_log("Bytes received:", iResult)
		else (0 == iResult)
			xcl_log("Connection closed")
		else
			xcl_log("Connection closed:", WSAGetLastErrorMessage())

		pass

	// cleanup
	closesocket(ConnectSocket)
	WSACleanup()
	控制台暂停()
	return 0

//炫语言手册:   http://www.xcgui.com/doc/

//动态库入口函数参考: https://docs.microsoft.com/zh-cn/windows/win32/dlls/dllmain?redirectedfrom=MSDN

//调试快捷键:   F5: 编译和调试, F7: 编译, F9:下断点, F10: 单步, F11: 步入
//函数参数展开: Ctrl+回车: 展开收缩, 表格内回车:收缩, ESC: 取消展开
//TAB:          缩进
//TAB + SHIFT: 减少缩进
//"/":      注释/取消注释
//Ctrl + G: 跳转到指定行
//Ctrl + F: 搜索和替换
//F12:      跳转到定义
//Alt + ↑: 向上交换行
//Alt + ↓: 向下交换行
//home:     移到光标到行首
//end:      移动光标到行尾
//双击打开项目: 系统设置->关联炫彩文件类型

//关于文本编码
//  首先你确定他是一个字符串
//  if你是二进制数据存在字节集里, 那么显示字符串是乱码的
//  取地址 是单字符型;
//  首先你要指定你字节集里存的是不是文本
//  是单字节 的 还是双字节的
//  文本文件 读到内存 都是单字节字符串 char*;
//  你需要把他转换为 unicode 双字节字符串 wchar_t*
//  XCL_logA 是单字节文本
//  你用 单文本型
//  不然你要转换下
//  文本文件一般都是单字节
//  A 与 W 转换
//  ascii和unicode都不清楚的吗
//  A2W()
//  W2A()
//  我一般都用 双字节 字符处理, 比较简单
//  因为中文 if单字节 会占多个字节
//  还得判断
//
//  文本型    双字节字符串  =  A2W_(data.取地址(),-1)
//  A2W() 就是把易那种字符串 转换为 unicode
//  分割文本, 你就用宽字符串  w wchar_t
//  
//  A =  char  =  单字节
//  w = wchar_t = 双字节 = UNICODE
//
//  你看系统API 都有两个版本
//  CreateWindowA()
//  CreateWindowW()
//  
//  炫语言代码文件是utf-8, 默认编译没有加utf-8选项, 所以ascii文本运行输入任然是ascii文本
//
//  两个文件中结构体类型互相包含导致冲突, 请将结构体定义移动到一个独立文件中