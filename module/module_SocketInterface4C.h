//@模块名称  HPSocket4C
//@版本  5.8.6  
//@日期  2023-03-22
//@作者  XCGUI
//@模块备注  HPSocket4C
//@依赖  module_base.h
 
//@lib   "HPSocket4C_U.lib"
//@跳过  HPSOCKET_API
//@复制文件 @当前模块路径 "HPSocket4C_U.dll"

//@启用枚举前缀


/*
 * Copyright: JessMA Open Source (ldcsaa@gmail.com)
 *
 * Author	: Bruce Liang
 * Website	: https://github.com/ldcsaa
 * Project	: https://github.com/ldcsaa/HP-Socket
 * Blog		: http://www.cnblogs.com/ldcsaa
 * Wiki		: http://www.oschina.net/p/hp-socket
 * QQ Group	: 44636872, 75375912
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
Module:  HPSocket for C

Desc: 导出纯 C 函数，让其它语言（如：C / C# / Delphi 等）能方便地使用 HPSocket

Usage:
		方法一：
		--------------------------------------------------------------------------------------
		0. （C/C++ 程序）包含 HPTypeDef.h / HPSocket4C.h 头文件
		1. 调用 ::Create_HP_XxxListener() 函数创建监听器对象()
		2. 调用 ::Create_HP_Xxx(pListener) 函数创建HPSocket对象()
		3. 调用 ::HP_Set_FN_Xxx_OnYyy(pListener, ...) 函数置监听器的回调函数
		4. 调用相关导出函数操作 HPSocket对象()
		5. ...... ......
		6. 调用 ::Destroy_HP_Xxx(pSocket) 函数销毁HPSocket对象()
		7. 调用 ::Destroy_HP_XxxListener(pListener) 函数销毁监听器对象()

		方法二：
		--------------------------------------------------------------------------------------
		1. 应用程序把需要用到的导出函数封装到特定语言的包装类中
		2. 通过包装类封装后，以面向对象()的方式使用 HPSocket

Release:
		<-- 动态链接库 -->
		1. x86/HPSocket4C.dll			- (32位/MBCS/Release)
		2. x86/HPSocket4C_D.dll			- (32位/MBCS/DeBug)
		3. x86/HPSocket4C_U.dll			- (32位/UNICODE/Release)
		4. x86/HPSocket4C_UD.dll		- (32位/UNICODE/DeBug)
		5. x64/HPSocket4C.dll			- (64位/MBCS/Release)
		6. x64/HPSocket4C_D.dll			- (64位/MBCS/DeBug)
		7. x64/HPSocket4C_U.dll			- (64位/UNICODE/Release)
		8. x64/HPSocket4C_UD.dll		- (64位/UNICODE/DeBug)

		<-- 静态链接库 -->
		!!注意!!：使用 HPSocket 静态库时，需要在工程属性中定义预处理宏 -> HPSOCKET_STATIC_LIB
		1. x86/static/HPSocket4C.lib	- (32位/MBCS/Release)
		2. x86/static/HPSocket4C_D.lib	- (32位/MBCS/DeBug)
		3. x86/static/HPSocket4C_U.lib	- (32位/UNICODE/Release)
		4. x86/static/HPSocket4C_UD.lib	- (32位/UNICODE/DeBug)
		5. x64/static/HPSocket4C.lib	- (64位/MBCS/Release)
		6. x64/static/HPSocket4C_D.lib	- (64位/MBCS/DeBug)
		7. x64/static/HPSocket4C_U.lib	- (64位/UNICODE/Release)
		8. x64/static/HPSocket4C_UD.lib	- (64位/UNICODE/DeBug)

******************************************************************************/

#pragma once

#include <winsock2.h>

//#include "HPTypeDef.h"



//#include "HPTypeDef.h" 将内容复制过来, 以便炫彩解析类型

/* HP-Socket 版本号 */
//@备注 HP-Socket 版本号
//@别名  HP主版本号
#define HP_VERSION_MAJOR		5	// 主版本号
//@别名  HP子版本号
#define HP_VERSION_MINOR		8	// 子版本号
//@别名  HP修正版本号
#define HP_VERSION_REVISE		6	// 修正版本号
//@别名  HP构建编号
#define HP_VERSION_BUILD		3	// 构建编号

//#define _UDP_DISABLED				// 禁用 UDP
//#define _SSL_DISABLED				// 禁用 SSL
//#define _HTTP_DISABLED			// 禁用 HTTP
//#define _ZLIB_DISABLED			// 禁用 ZLIB
//#define _BROTLI_DISABLED			// 禁用 BROTLI

/* 是否启用 UDP，如果定义了 _UDP_DISABLED 则禁用（默认：启用） */
#if !defined(_UDP_DISABLED)
#ifndef _UDP_SUPPORT
#define _UDP_SUPPORT
#endif
#endif

/* 是否启用 SSL，如果定义了 _SSL_DISABLED 则禁用（默认：启用） */
#if !defined(_SSL_DISABLED)
#ifndef _SSL_SUPPORT
#define _SSL_SUPPORT
#endif
#endif

/* 是否启用 HTTP，如果定义了 _HTTP_DISABLED 则禁用（默认：启用） */
#if !defined(_HTTP_DISABLED)
#ifndef _HTTP_SUPPORT
#define _HTTP_SUPPORT
#endif
#endif

/* 是否启用 ZLIB，如果定义了 _ZLIB_DISABLED 则禁用（默认：启用） */
#if !defined(_ZLIB_DISABLED)
#ifndef _ZLIB_SUPPORT
#define _ZLIB_SUPPORT
#endif
#endif

/* 是否启用 BROTLI，如果定义了 _BROTLI_DISABLED 则禁用（默认：启用） */
#if !defined(_BROTLI_DISABLED)
#ifndef _BROTLI_SUPPORT
#define _BROTLI_SUPPORT
#endif
#endif

/**************************************************/
/********** imports / exports HPSocket4C **********/

#ifdef HPSOCKET_STATIC_LIB
#define HPSOCKET_API		EXTERN_C
#else
#ifdef HPSOCKET_EXPORTS
#define HPSOCKET_API	EXTERN_C __declspec(dllexport)
#else
#define HPSOCKET_API	EXTERN_C __declspec(dllimport)
#endif
#endif

#define __HP_CALL				__stdcall

/*****************************************************************************************************************************************************/
/**************************************************************** Base Type Definitions **************************************************************/
/*****************************************************************************************************************************************************/

typedef const BYTE* LPCBYTE, PCBYTE;
typedef ULONG_PTR		TID, THR_ID, NTHR_ID, PID, PRO_ID;

/************************************************************************
名称：连接 ID 数据类型
描述：应用程序可以把 CONNID 定义为自身需要的类型（如：ULONG / ULONGLONG）
************************************************************************/

//@备注 应用程序可以把 CONNID 定义为自身需要的类型（如：ULONG / ULONGLONG）
//@别名 网络连接字符串
typedef ULONG_PTR		CONNID;
//@别名 HP_网络连接字符串
typedef ULONG_PTR		HP_CONNID;
/************************************************************************
名称：通信组件服务状态
描述：应用程序可以通过通信组件的 GetState() 方法取组件当前服务状态
************************************************************************/
//@别名  HP服务状态
typedef enum EnServiceState
{
	//@别名  正在启动
	SS_STARTING = 0,	// 正在启动
	//@别名  已经启动
	SS_STARTED = 1,	// 已经启动
	//@别名  正在停止
	SS_STOPPING = 2,	// 正在停止
	//@别名  已经停止
	SS_STOPPED = 3,	// 已经停止
} En_HP_ServiceState;

/************************************************************************
名称：Socket 操作类型
描述：应用程序的 OnClose() 事件中通过该参数标识是哪种操作导致的错误
************************************************************************/
//@别名  HP操作类型
typedef enum EnSocketOperation
{
	//@别名  未知操作
	SO_UNKNOWN = 0,	// Unknown
	//@别名  接受请求
	SO_ACCEPT = 1,	// Acccept
	//@别名  连接请求
	SO_CONNECT = 2,	// Connect
	//@别名  发送请求
	SO_SEND = 3,	// Send
	//@别名  接收请求
	SO_RECEIVE = 4,	// Receive
	//@别名  主动断开
	SO_CLOSE = 5,	// Close
} En_HP_SocketOperation;

/************************************************************************
名称：事件处理结果
描述：事件的返回值，不同的返回值会影响通信组件的后续行为
************************************************************************/
//@别名  HP事件处理结果
typedef enum EnHandleResult
{
	//@别名   成功
	HR_OK = 0,	// 成功
	//@别名   忽略
	HR_IGNORE = 1,	// 忽略
	//@别名   错误
	HR_ERROR = 2,	// 错误
} En_HP_HandleResult;

/************************************************************************
名称：数据抓取结果
描述：数据抓取操作的返回值
************************************************************************/
//@别名  HP数据抓取结果
typedef enum EnFetchResult
{
	//@别名  成功
	FR_OK = 0,	// 成功
	//@别名  长度过大
	FR_LENGTH_TOO_LONG = 1,	// 抓取长度过大
	//@别名  找不到
	FR_DATA_NOT_FOUND = 2,	// 找不到 ConnID 对应的数据
} En_HP_FetchResult;

/************************************************************************
名称：数据发送策略
描述：Server 组件和 Agent 组件的数据发送策略

* 打包发送策略（默认）	：尽量把多个发送操作的数据组合在一起发送，增加传输效率
* 安全发送策略			：尽量把多个发送操作的数据组合在一起发送，并控制传输速度，避免缓冲区溢出
* 直接发送策略			：对每一个发送操作都直接投递，适用于负载不高但要求实时性较高的场合
************************************************************************/
//@别名  HP数据发送策略
typedef enum EnSendPolicy
{
	//@别名  打包模式
	SP_PACK = 0,	// 打包模式（默认）
	//@别名  安全模式
	SP_SAFE = 1,	// 安全模式
	//@别名  直接模式
	SP_DIRECT = 2,	// 直接模式
} En_HP_SendPolicy;

/************************************************************************
名称：OnSend 事件同步策略
描述：Server 组件和 Agent 组件的 OnSend 事件同步策略

* 不同步（默认）	：不同步 OnSend 事件，可能同时触发 OnReceive 和 OnClose 事件
* 同步 OnClose	：只同步 OnClose 事件，可能同时触发 OnReceive 事件
* 同步 OnReceive	：（只用于 TCP 组件）同步 OnReceive 和 OnClose 事件，不可能同时触发 OnReceive 或 OnClose 事件
************************************************************************/
//@别名  HP发送事件同步策略
typedef enum EnOnSendSyncPolicy
{
	//@别名  不同步
	OSSP_NONE = 0,	// 不同步（默认）
	//@别名  同步关闭
	OSSP_CLOSE = 1,	// 同步 OnClose
	//@别名  同步接收
	OSSP_RECEIVE = 2,	// 同步 OnReceive（只用于 TCP 组件）	
} En_HP_OnSendSyncPolicy;

/************************************************************************
名称：地址重用选项
描述：通信组件底层 socket 的地址重用选项
************************************************************************/
//@别名  HP地址重用选项
typedef enum EnReuseAddressPolicy
{
	//@别名  不
	RAP_NONE = 0,	// 不重用
	//@别名  仅地址
	RAP_ADDR_ONLY = 1,	// 仅重用地址
	//@别名  地址和端口
	RAP_ADDR_AND_PORT = 2,	// 重用地址和端口
} En_HP_ReuseAddressPolicy;

/************************************************************************
名称：操作结果代码
描述：组件 Start() / Stop() 方法执行失败时，可通过 GetLastError() 取错误代码
************************************************************************/
//@别名  HP操作代码
typedef enum EnSocketError
{
	//@别名  成功
	SE_OK = NO_ERROR,	// 成功
	//@别名  当前状态不允许操作
	SE_ILLEGAL_STATE = 1,		// 当前状态不允许操作
	//@别名  非法参数
	SE_INVALID_PARAM = 2,		// 非法参数
	//@别名  创建网络套接字失败
	SE_SOCKET_CREATE = 3,		//@别名 创建 SOCKET 失败
	//@别名  绑定网络套接字失败
	SE_SOCKET_BIND = 4,		// 绑定 SOCKET 失败
	//@别名  置网络套接字失败
	SE_SOCKET_PREPARE = 5,		// 置 SOCKET 失败
	//@别名  监听网络套接字失败
	SE_SOCKET_LISTEN = 6,		// 监听 SOCKET 失败
	//@别名  创建完成端口失败
	SE_CP_CREATE = 7,		//@别名 创建完成端口失败
	//@别名  创建工作线程失败
	SE_WORKER_THREAD_CREATE = 8,		//@别名 创建工作线程失败
	//@别名  创建监测线程失败
	SE_DETECT_THREAD_CREATE = 9,		//@别名 创建监测线程失败
	//@别名  绑定完成端口失败
	SE_SOCKE_ATTACH_TO_CP = 10,		// 绑定完成端口失败
	//@别名  连接服务器失败
	SE_CONNECT_SERVER = 11,		// 连接服务器失败
	//@别名  网络错误
	SE_NETWORK = 12,		// 网络错误
	//@别名  数据处理错误
	SE_DATA_PROC = 13,		// 数据处理错误
	//@别名  数据发送失败
	SE_DATA_SEND = 14,		// 数据发送失败

	/***** SSL Socket 扩展操作结果代码 *****/
	//@别名  环境未就绪
	SE_SSL_ENV_NOT_READY = 101,		// SSL 环境未就绪
} En_HP_SocketError;

/************************************************************************
名称：播送模式
描述：UDP 组件的播送模式（组播或广播）
************************************************************************/
//@别名  HPUDP播送模式
typedef enum EnCastMode
{
	//@别名  单播
	CM_UNICAST = -1,	// 单播
	//@别名  组播
	CM_MULTICAST = 0,	// 组播
	//@别名  广播
	CM_BROADCAST = 1,	// 广播
} En_HP_CastMode;

/************************************************************************
名称：IP 地址类型
描述：IP 地址类型枚举值
************************************************************************/
//@别名  HPIP地址类型
typedef enum EnIPAddrType
{
	//@别名  所有
	IPT_ALL = 0,		// 所有
	//@别名  IPv4
	IPT_IPV4 = 1,		// IPv4
	//@别名  IPv6
	IPT_IPV6 = 2,		// IPv6
} En_HP_IPAddrType;

/************************************************************************
名称：IP 地址条目结构体
描述：IP 地址的地址簇/地址值结构体
************************************************************************/
//@别名  HP_IP地址结构
typedef struct TIPAddr
{
	//@别名  IP地址类型
	En_HP_IPAddrType type;
	//@别名  添加值
	LPCTSTR			 address;
} *LPTIPAddr, HP_TIPAddr, * HP_LPTIPAddr;

/************************************************************************
名称：拒绝策略
描述：调用被拒绝后的处理策略
************************************************************************/
//@别名  HP拒绝策略
typedef enum EnRejectedPolicy
{
	//@别名  失败
	TRP_CALL_FAIL = 0,	// 立刻返回失败
	//@别名  等待
	TRP_WAIT_FOR = 1,	// 等待（直到成功、超时或线程池关闭等原因导致失败）
	//@别名  执行
	TRP_CALLER_RUN = 2,	// 调用者线程直接执行
} En_HP_RejectedPolicy;

/************************************************************************
名称：任务缓冲区类型
描述：TSockeTask对象()创建和销毁时，根据不同类型的缓冲区类型作不同的处理
************************************************************************/
//@别名  HP任务缓冲区类型
typedef enum EnTaskBufferType
{
	//@别名  深拷贝
	TBT_COPY = 0,	// 深拷贝
	//@别名  浅拷贝
	TBT_REFER = 1,	// 浅拷贝
	//@别名  附属
	TBT_ATTACH = 2,	// 附属（不负责创建，但负责销毁）
} En_HP_TaskBufferType;

/************************************************************************
名称：任务处理函数
描述：任务处理入口函数
参数：pvArg -- 自定义参数
返回值：（无）
************************************************************************/
//@备注 任务处理入口函数
//@参数 pTask -- 自定义参数
//@别名  HP任务处理函数(自定义参数)
typedef VOID(__HP_CALL* Fn_TaskProc)(PVOID pvArg);
typedef Fn_TaskProc	HP_Fn_TaskProc;

struct TSocketTask;

/************************************************************************
名称：Socket 任务处理函数
描述：Socket 任务处理入口函数
参数：pTask -- Socket 任务结构体指针
返回值：（无）
************************************************************************/
//@备注 Socket 任务处理入口函数
//@参数 pTask -- HP任务结构体指针
//@别名  HP_Socket任务处理函数(HP任务结构指针)
typedef VOID(__HP_CALL* Fn_SocketTaskProc)(struct TSocketTask* pTask);
typedef Fn_SocketTaskProc	HP_Fn_SocketTaskProc;

/************************************************************************
名称：Socket 任务结构体
描述：封装 Socket 任务相关数据结构
************************************************************************/
//@别名  HP任务结构
typedef struct TSocketTask
{
	//@别名  任务处理函数
	HP_Fn_SocketTaskProc	fn;			// 任务处理函数
	//@别名  发起对象()
	PVOID					sender;		// 发起对象()
	//@别名  连接ID
	CONNID					connID;		// 连接 ID
	//@别名  数据缓冲区
	LPCBYTE					buf;		// 数据缓冲区
	//@别名  数据缓冲区长度
	INT						bufLen;		// 数据缓冲区长度
	//@别名  缓冲区类型
	En_HP_TaskBufferType	bufType;	// 缓冲区类型
	//@别名  自定义参数1
	WPARAM					wparam;		// 自定义参数
	//@别名  自定义参数2
	LPARAM					lparam;		// 自定义参数
} *LPTSocketTask, HP_TSocketTask, * HP_LPTSocketTask;

/************************************************************************
名称：取 HPSocket 版本号
描述：版本号（4 个字节分别为：主版本号，子版本号，修正版本号，构建编号）
************************************************************************/
//@备注 版本号（4 个字节分别为：主版本号，子版本号，修正版本号，构建编号）
//@别名  HP取版本号()
inline DWORD GetHPSocketVersion()
{
	return (HP_VERSION_MAJOR << 24) | (HP_VERSION_MINOR << 16) | (HP_VERSION_REVISE << 8) | HP_VERSION_BUILD;
}

/*****************************************************************************************************************************************************/
/**************************************************************** SSL Type Definitions ***************************************************************/
/*****************************************************************************************************************************************************/

#ifdef _SSL_SUPPORT

/************************************************************************
名称：SSL 工作模式
描述：标识 SSL 的工作模式，客户端模式或服务端模式
************************************************************************/
//@别名  HPSSL工作模式
typedef enum EnSSLSessionMode
{
	//@别名  客户端
	SSL_SM_CLIENT = 0,	// 客户端模式
	//@别名  服务端
	SSL_SM_SERVER = 1,	// 服务端模式
} En_HP_SSLSessionMode;

/************************************************************************
名称：SSL 验证模式
描述：SSL 验证模式选项，SSL_VM_PEER 可以和后面两个选项组合一起
************************************************************************/
//@别名  HPSSL验证模式
typedef enum EnSSLVerifyMode
{
	//@别名  无
	SSL_VM_NONE = 0x00,	// SSL_VERIFY_NONE
	//@别名  单项
	SSL_VM_PEER = 0x01,	// SSL_VERIFY_PEER
	//@别名  双向
	SSL_VM_FAIL_IF_NO_PEER_CERT = 0x02,	// SSL_VERIFY_FAIL_IF_NO_PEER_CERT
	//@别名  单次
	SSL_VM_CLIENT_ONCE = 0x04,	// SSL_VERIFY_CLIENT_ONCE
} En_HP_SSLVerifyMode;

//@备注 SSL Session 信息类型
//描述：用于 GetSSLSessionInfo()，标识输出的 Session 信息类型
//@别名  HPSSL信息类型
typedef enum EnSSLSessionInfo
{
	SSL_SSI_MIN = 0,	// 
	SSL_SSI_CTX = 0,	// SSL CTX				（输出类型：SSL_CTX*）
	SSL_SSI_CTX_METHOD = 1,	// SSL CTX Mehtod		（输出类型：SSL_METHOD*）
	SSL_SSI_CTX_CIPHERS = 2,	// SSL CTX Ciphers		（输出类型：STACK_OF(SSL_CIPHER)*）
	SSL_SSI_CTX_CERT_STORE = 3,	// SSL CTX Cert Store	（输出类型：X509_STORE*）
	SSL_SSI_SERVER_NAME_TYPE = 4,	// Server Name Type		（输出类型：int）
	SSL_SSI_SERVER_NAME = 5,	// Server Name			（输出类型：LPCSTR）
	SSL_SSI_VERSION = 6,	// SSL Version			（输出类型：LPCSTR）
	SSL_SSI_METHOD = 7,	// SSL Method			（输出类型：SSL_METHOD*）
	SSL_SSI_CERT = 8,	// SSL Cert				（输出类型：X509*）
	SSL_SSI_PKEY = 9,	// SSL Private Key		（输出类型：EVP_PKEY*）
	SSL_SSI_CURRENT_CIPHER = 10,	// SSL Current Cipher	（输出类型：SSL_CIPHER*）
	SSL_SSI_CIPHERS = 11,	// SSL Available Ciphers（输出类型：STACK_OF(SSL_CIPHER)*）
	SSL_SSI_CLIENT_CIPHERS = 12,	// SSL Client Ciphers	（输出类型：STACK_OF(SSL_CIPHER)*）
	SSL_SSI_PEER_CERT = 13,	// SSL Peer Cert		（输出类型：X509*）
	SSL_SSI_PEER_CERT_CHAIN = 14,	// SSL Peer Cert Chain	（输出类型：STACK_OF(X509)*）
	SSL_SSI_VERIFIED_CHAIN = 15,	// SSL Verified Chain	（输出类型：STACK_OF(X509)*）
	SSL_SSI_MAX = 15,	// 
} En_HP_SSLSessionInfo;

/*@声明
@别名  HP_SNI服务名称回调函数(服务器名称,回调上下文)
@备注 根据服务器名称选择 SSL 证书
@参数	lpszServerName -- 服务器名称（域名）
@参数	pContext -- 回调上下文
@返回	0	 -- 成功，使用默认 SSL 证书索引
//		正数	 -- 成功，使用返回值对应的 SNI 主机证书索引
//		负数	 -- 失败，中断 SSL 握手

*/
typedef int (__HP_CALL* Fn_SNI_ServerNameCallback)(LPCTSTR lpszServerName, PVOID pContext);
typedef Fn_SNI_ServerNameCallback	HP_Fn_SNI_ServerNameCallback;

#endif

/*****************************************************************************************************************************************************/
/**************************************************************** HTTP Type Definitions **************************************************************/
/*****************************************************************************************************************************************************/

#ifdef _HTTP_SUPPORT

/************************************************************************
名称：HTTP 版本
描述：低字节：主版本号，高字节：次版本号
************************************************************************/
//@别名  HPHTTP协议版本
typedef enum EnHttpVersion
{
	//@别名  HTTP1_0
	HV_1_0 = MAKEWORD(1, 0),	// HTTP/1.0
	//@别名  HTTP1_1
	HV_1_1 = MAKEWORD(1, 1)	// HTTP/1.1
} En_HP_HttpVersion;

/************************************************************************
名称：URL 域
描述：HTTP 请求行中 URL 段位的域定义
************************************************************************/
//@别名  HPURL字段
typedef enum EnHttpUrlField
{
	//@别名  概要
	HUF_SCHEMA = 0,	// Schema
	//@别名  主机
	HUF_HOST = 1,	// Host
	//@别名  端口
	HUF_PORT = 2,	// Port
	//@别名  路径
	HUF_PATH = 3,	// Path
	//@别名  查询
	HUF_QUERY = 4,	// Query String
	//@别名  片段
	HUF_FRAGMENT = 5,	// Fragment
	//@别名  用户信息
	HUF_USERINFO = 6,	// User Info
	//@别名  字段数量
	HUF_MAX = 7,	// (Field Count)
} En_HP_HttpUrlField;

/************************************************************************
名称：HTTP 解析结果标识
描述：指示 HTTP 解析器是否继续执行解析操作
************************************************************************/
//@别名  HPHTTP解析结果
typedef enum EnHttpParseResult
{
	//@别名  成功
	HPR_OK = 0,	// 解析成功
	//@别名  跳过当前请求
	HPR_SKIP_BODY = 1,	// 跳过当前请求 BODY（仅用于 OnHeadersComplete 事件）
	//@别名  升级协议
	HPR_UPGRADE = 2,	// 升级协议（仅用于 OnHeadersComplete 事件）
	//@别名  错误
	HPR_ERROR = -1,	// 解析错误，终止解析，断开连接
} En_HP_HttpParseResult;

//@备注 HTTP 协议升级类型
//描述：标识 HTTP 升级为哪种协议
//@别名  HPHTTP协议类型
typedef enum EnHttpUpgradeType
{
	//@别名  没有升级
	HUT_NONE = 0,	// 没有升级
	//@别名  web网络套接字
	HUT_WEB_SOCKET = 1,	// WebSocket
	//@别名  HTTP隧道
	HUT_HTTP_TUNNEL = 2,	// HTTP 隧道
	//@别名  未知类型
	HUT_UNKNOWN = -1,	// 未知类型
} En_HP_HttpUpgradeType;

/************************************************************************
名称：HTTP 状态码
描述：HTTP 标准状态码
************************************************************************/
//@别名  HPHTTP状态码
typedef enum EnHttpStatusCode
{
	//@别名 HP_继续
	HSC_CONTINUE = 100,
	//@别名 HP_交换协议
	HSC_SWITCHING_PROTOCOLS = 101,
	//@别名 HP_正在处理
	HSC_PROCESSING = 102,

	//@别名 HP_成功
	HSC_OK = 200,
	//@别名 HP_已创建
	HSC_CREATED = 201,
	//@别名 HP_已同意
	HSC_ACCEPTED = 202,
	//@别名 HP_非权威信息
	HSC_NON_AUTHORITATIVE_INFORMATION = 203,
	//@别名 HP_空内容
	HSC_NO_CONTENT = 204,
	//@别名 HP_重置内容
	HSC_RESET_CONTENT = 205,
	//@别名 HP_分块内容
	HSC_PARTIAL_CONTENT = 206,
	//@别名 HP_多状态
	HSC_MULTI_STATUS = 207,
	//@别名 HP_已报告
	HSC_ALREADY_REPORTED = 208,
	//@别名 HP_已响应
	HSC_IM_USED = 226,

	//@别名 HP_多重选择
	HSC_MULTIPLE_CHOICES = 300,
	//@别名 HP_永久重定向
	HSC_MOVED_PERMANENTLY = 301,
	//@别名 HP_临时重定向
	HSC_MOVED_TEMPORARILY = 302,
	//@别名 HP_重定向
	HSC_SEE_OTHER = 303,
	//@别名 HP_缓存
	HSC_NOT_MODIFIED = 304,
	//@别名 HP_使用代理
	HSC_USE_PROXY = 305,
	//@别名 HP_选择代理
	HSC_SWITCH_PROXY = 306,
	//@别名 HP_临时重定向_
	HSC_TEMPORARY_REDIRECT = 307,
	//@别名 HP_永久重定向_
	HSC_PERMANENT_REDIRECT = 308,

	//@别名 HP_请求无效
	HSC_BAD_REQUEST = 400,
	//@别名 HP_未授权
	HSC_UNAUTHORIZED = 401,
	//@别名 HP_需要付款
	HSC_PAYMENT_REQUIRED = 402,
	//@别名 HP_拒绝访问
	HSC_FORBIDDEN = 403,
	//@别名 HP_未找到资源
	HSC_NOT_FOUND = 404,
	//@别名 HP_不允许的请求方法
	HSC_METHOD_NOT_ALLOWED = 405,
	//@别名 HP_不允许的请求
	HSC_NOT_ACCEPTABLE = 406,
	//@别名 HP_需要代理服务器认证身份
	HSC_PROXY_AUTHENTICATION_REQUIRED = 407,
	//@别名 HP_请求超时
	HSC_REQUEST_TIMEOUT = 408,
	//@别名 HP_资源状态冲突
	HSC_CONFLICT = 409,
	//@别名 HP_资源过期
	HSC_GONE = 410,
	//@别名 HP_需要表明长度
	HSC_LENGTH_REQUIRED = 411,
	//@别名 HP_未满足先决条件
	HSC_PRECONDITION_FAILED = 412,
	//@别名 HP_请求体太大
	HSC_REQUEST_ENTITY_TOO_LARGE = 413,
	//@别名 HP_请求域太长
	HSC_REQUEST_URI_TOO_LONG = 414,
	//@别名 HP_不支持的媒体类型
	HSC_UNSUPPORTED_MEDIA_TYPE = 415,
	//@别名 HP_不满足请求范围
	HSC_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
	//@别名 HP_预期结果失败
	HSC_EXPECTATION_FAILED = 417,
	//@别名 HP_错误的请求
	HSC_MISDIRECTED_REQUEST = 421,
	//@别名 HP_无法遵循的语义错误
	HSC_UNPROCESSABLE_ENTITY = 422,
	//@别名 HP_已锁定
	HSC_LOCKED = 423,
	//@别名 HP_失败的依赖项
	HSC_FAILED_DEPENDENCY = 424,
	//@别名 HP_无序收集
	HSC_UNORDERED_COLLECTION = 425,
	//@别名 HP_需要升级协议
	HSC_UPGRADE_REQUIRED = 426,
	//@别名 HP_需要条件请求
	HSC_PRECONDITION_REQUIRED = 428,
	//@别名 HP_请求过多
	HSC_TOO_MANY_REQUESTS = 429,
	//@别名 HP_请求头过大
	HSC_REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
	//@别名 HP_因法律不可用
	HSC_UNAVAILABLE_FOR_LEGAL_REASONS = 451,
	//@别名 HP_使用重试
	HSC_RETRY_WITH = 449,

	//@别名 HP_服务器内部错误
	HSC_INTERNAL_SERVER_ERROR = 500,
	//@别名 HP_尚未实现
	HSC_NOT_IMPLEMENTED = 501,
	//@别名 HP_错误网关
	HSC_BAD_GATEWAY = 502,
	//@别名 HP_服务不可用
	HSC_SERVICE_UNAVAILABLE = 503,
	//@别名 HP_网关超时
	HSC_GATEWAY_TIMEOUT = 504,
	//@别名 HP_HTTP版本不支持
	HSC_HTTP_VERSION_NOT_SUPPORTED = 505,
	//@别名 HP_服务器存在内部配置错误
	HSC_VARIANT_ALSO_NEGOTIATES = 506,
	//@别名 HP_服务器无法存储
	HSC_INSUFFICIENT_STORAGE = 507,
	//@别名 HP_发现无穷循环
	HSC_LOOP_DETECTED = 508,
	//@别名 HP_流量超限
	HSC_BANDWIDTH_LIMIT_EXCEEDED = 509,
	//@别名 HP_未扩展
	HSC_NOT_EXTENDED = 510,
	//@别名 HP_需要网络验证
	HSC_NETWORK_AUTHENTICATION_REQUIRED = 511,

	//@别名 HP_无法解析响应头
	HSC_UNPARSEABLE_RESPONSE_HEADERS = 600
} En_HP_HttpStatusCode;

/************************************************************************
名称：Name/Value 结构体
描述：字符串名值对结构体
************************************************************************/
//@别名  HP请求头结构
typedef struct TNVPair
{
	//@别名  名称
	LPCSTR name;
	//@别名  值
	LPCSTR value;
}	HP_TNVPair,
TParam, HP_TParam, * LPPARAM, * HP_LPPARAM,
THeader, HP_THeader, * LPHEADER, * HP_LPHEADER,
TCookie, HP_TCookie, * LPCOOKIE, * HP_LPCOOKIE;

#endif

/*@声明
@备注 回调处理过程中产生的数据输出
@参数 pData		-- 数据缓冲区
@参数 iLength		-- 数据长度
@参数 pContext	-- 回调上下文

@返回	TRUE	-- 成功
//		FALSE	-- 失败
@别名  HP数据回调函数(数据缓冲区,数据长度,回调上下文)
*/
typedef BOOL(__HP_CALL* Fn_DataCallback)(const BYTE* pData, int iLength, PVOID pContext);
typedef Fn_DataCallback	Fn_CompressDataCallback;
typedef Fn_DataCallback	Fn_DecompressDataCallback;
typedef Fn_DataCallback	HP_Fn_DataCallback;
typedef Fn_DataCallback	HP_Fn_CompressDataCallback;
typedef Fn_DataCallback	HP_Fn_DecompressDataCallback;

//---------------end HPTypeDef.h--------------------------------------------

/************************************************************************
名称：定义 Socket对象()指针类型别名
描述：把 Socket对象()指针定义为更直观的别名
************************************************************************/
//@别名 HP_对象
typedef PVOID		HP_Object;
//@别名 HP_服务端
typedef HP_Object	HP_Server;
//@别名 HP_代理端
typedef HP_Object	HP_Agent;
//@别名 HP_客户端
typedef HP_Object	HP_Client;
//@别名 HP_节点
typedef HP_Object	HP_Node;
//@别名 HP_Tcp服务端
typedef HP_Object	HP_TcpServer;
//@别名 HP_Tcp代理端
typedef HP_Object	HP_TcpAgent;
//@别名 HP_Tcp客户端
typedef HP_Object	HP_TcpClient;
//@别名 HP_拉套接字
typedef HP_Object	HP_PullSocket;
//@别名 HP_拉客户端
typedef HP_Object	HP_PullClient;
//@别名 HP_拉服务端
typedef HP_Object	HP_TcpPullServer;
//@别名 HP_Tcp拉代理端
typedef HP_Object	HP_TcpPullAgent;
//@别名 HP_Tcp拉客户端
typedef HP_Object	HP_TcpPullClient;
//@别名 HP_包套接字
typedef HP_Object	HP_PackSocket;
//@别名 HP_包客户端
typedef HP_Object	HP_PackClient;
//@别名 HP_TCP包服务端
typedef HP_Object	HP_TcpPackServer;
//@别名 HP_TCP包代理端
typedef HP_Object	HP_TcpPackAgent;
//@别名 HP_TCP包客户端
typedef HP_Object	HP_TcpPackClient;
//@别名 HP_线程池
typedef HP_Object	HP_ThreadPool;
//@别名 HP_监听
typedef HP_Object	HP_Listener;
//@别名 HP_服务端监听
typedef HP_Object	HP_ServerListener;
//@别名 HP_代理端监听
typedef HP_Object	HP_AgentListener;
//@别名 HP_客户端端监听
typedef HP_Object	HP_ClientListener;
//@别名	HP_Tcp服务端监听
typedef HP_Object	HP_TcpServerListener;
//@别名	HP_Tcp代理端监听
typedef HP_Object	HP_TcpAgentListener;
//@别名	HP_Tcp客户端监听
typedef HP_Object	HP_TcpClientListener;
//@别名	HP_拉套接字监听
typedef HP_Object	HP_PullSocketListener;
//@别名	HP_拉客户端监听
typedef HP_Object	HP_PullClientListener;
//@别名	HP_Tcp拉服务端监听
typedef HP_Object	HP_TcpPullServerListener;
//@别名	HP_Tcp拉代理端监听
typedef HP_Object	HP_TcpPullAgentListener;
//@别名	HP_Tcp拉代客户监听
typedef HP_Object	HP_TcpPullClientListener;
//@别名	HP_包套接字监听
typedef HP_Object	HP_PackSocketListener;
//@别名	HP_包客户端监听
typedef HP_Object	HP_PackClientListener;
//@别名	HP_包服务端监听
typedef HP_Object	HP_TcpPackServerListener;
//@别名	HP_包代理端监听
typedef HP_Object	HP_TcpPackAgentListener;
//@别名	HP_Tcp包客户端监听
typedef HP_Object	HP_TcpPackClientListener;
//@别名	HP_线程池监听
typedef HP_Object	HP_ThreadPoolListener;

#ifdef _UDP_SUPPORT
//@别名	HP_UDP服务端
typedef HP_Object	HP_UdpServer;
//@别名	HP_UDP客户端
typedef HP_Object	HP_UdpClient;
typedef HP_Object	HP_UdpCast;
typedef HP_Object	HP_UdpNode;
//@别名	HP_UDP自动重连服务端
typedef HP_Object	HP_UdpArqServer;
//@别名	HP_UDP自动重连客户端
typedef HP_Object	HP_UdpArqClient;
//@别名	HP_UDP服务端监听
typedef HP_Object	HP_UdpServerListener;
//@别名	HP_UDP客户端监听
typedef HP_Object	HP_UdpClientListener;
//@别名	HP_UDPCast端监听
typedef HP_Object	HP_UdpCastListener;
//@别名	HP_UDPNode端监听
typedef HP_Object	HP_UdpNodeListener;
//@别名	HP_UDP自动重连服务端监听
typedef HP_Object	HP_UdpArqServerListener;
//@别名	HP_UDP自动重连客户端监听
typedef HP_Object	HP_UdpArqClientListener;

#endif

#ifdef _HTTP_SUPPORT

typedef HP_Object	HP_Http;
//@别名	HP_Http服务端
typedef HP_Object	HP_HttpServer;
//@别名	HP_Http代理端
typedef HP_Object	HP_HttpAgent;
//@别名	HP_Http客户端
typedef HP_Object	HP_HttpClient;
//@别名	HP_Http同步客户端
typedef HP_Object	HP_HttpSyncClient;
//@别名	HP_Http服务端监听
typedef HP_Object	HP_HttpServerListener;
//@别名	HP_Http代理端监听
typedef HP_Object	HP_HttpAgentListener;
//@别名	HP_Http客户端监听
typedef HP_Object	HP_HttpClientListener;

#endif

/*****************************************************************************************************************************************************/
/****************************************************************** TCP/UDP Exports ******************************************************************/
/*****************************************************************************************************************************************************/

/****************************************************/
/***************** TCP/UDP 回调函数 ******************/

/* Server 回调函数 */
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Server_OnPrepareListen)	(HP_Server pSender, UINT_PTR soListen);
// 如果为 TCP 连接，pClient为 SOCKET 句柄；如果为 UDP 连接，pClient为 SOCKADDR 指针；
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Server_OnAccept)			(HP_Server pSender, HP_CONNID dwConnID, UINT_PTR pClient);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Server_OnHandShake)		(HP_Server pSender, HP_CONNID dwConnID);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Server_OnSend)				(HP_Server pSender, HP_CONNID dwConnID, const BYTE* pData, int iLength);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Server_OnReceive)			(HP_Server pSender, HP_CONNID dwConnID, const BYTE* pData, int iLength);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Server_OnPullReceive)		(HP_Server pSender, HP_CONNID dwConnID, int iLength);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Server_OnClose)			(HP_Server pSender, HP_CONNID dwConnID, En_HP_SocketOperation enOperation, int iErrorCode);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Server_OnShutdown)			(HP_Server pSender);

/* Agent 回调函数 */
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Agent_OnPrepareConnect)	(HP_Agent pSender, HP_CONNID dwConnID, UINT_PTR socket);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Agent_OnConnect)			(HP_Agent pSender, HP_CONNID dwConnID);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Agent_OnHandShake)			(HP_Agent pSender, HP_CONNID dwConnID);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Agent_OnSend)				(HP_Agent pSender, HP_CONNID dwConnID, const BYTE* pData, int iLength);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Agent_OnReceive)			(HP_Agent pSender, HP_CONNID dwConnID, const BYTE* pData, int iLength);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Agent_OnPullReceive)		(HP_Agent pSender, HP_CONNID dwConnID, int iLength);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Agent_OnClose)				(HP_Agent pSender, HP_CONNID dwConnID, En_HP_SocketOperation enOperation, int iErrorCode);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Agent_OnShutdown)			(HP_Agent pSender);

/* Client 回调函数 */
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Client_OnPrepareConnect)	(HP_Client pSender, HP_CONNID dwConnID, UINT_PTR socket);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Client_OnConnect)			(HP_Client pSender, HP_CONNID dwConnID);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Client_OnHandShake)		(HP_Client pSender, HP_CONNID dwConnID);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Client_OnSend)				(HP_Client pSender, HP_CONNID dwConnID, const BYTE* pData, int iLength);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Client_OnReceive)			(HP_Client pSender, HP_CONNID dwConnID, const BYTE* pData, int iLength);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Client_OnPullReceive)		(HP_Client pSender, HP_CONNID dwConnID, int iLength);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_Client_OnClose)			(HP_Client pSender, HP_CONNID dwConnID, En_HP_SocketOperation enOperation, int iErrorCode);

#ifdef _UDP_SUPPORT

/* UdpNode 回调函数 */
typedef En_HP_HandleResult (__HP_CALL *HP_FN_UdpNode_OnPrepareListen)	(HP_UdpNode pSender, UINT_PTR soListen);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_UdpNode_OnSend)			(HP_UdpNode pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_UdpNode_OnReceive)			(HP_UdpNode pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_UdpNode_OnError)			(HP_UdpNode pSender, En_HP_SocketOperation enOperation, int iErrorCode, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength);
typedef En_HP_HandleResult (__HP_CALL *HP_FN_UdpNode_OnShutdown)		(HP_UdpNode pSender);

#endif

/****************************************************/
/*************** TCP/UDP对象()创建函数 ****************/

//@备注 HP_创建HP_TcpServer对象()
//@别名 HP_Tcp服务端对象创建()
HPSOCKET_API HP_TcpServer __HP_CALL Create_HP_TcpServer(HP_TcpServerListener pListener);
//@备注 HP_创建HP_TcpAgent对象()
//@别名 HP_Tcp代理端对象创建()
HPSOCKET_API HP_TcpAgent __HP_CALL Create_HP_TcpAgent(HP_TcpAgentListener pListener);
//@备注 HP_创建HP_TcpClient对象()
//@别名 HP_Tcp客户端对象创建()
HPSOCKET_API HP_TcpClient __HP_CALL Create_HP_TcpClient(HP_TcpClientListener pListener);
//@备注 HP_创建HP_TcpPullServer对象()
//@别名 HP_Tcp拉服务端对象创建()
HPSOCKET_API HP_TcpPullServer __HP_CALL Create_HP_TcpPullServer(HP_TcpPullServerListener pListener);
//@备注 HP_创建HP_TcpPullAgent对象()
//@别名 HP_Tcp拉代理端对象创建()
HPSOCKET_API HP_TcpPullAgent __HP_CALL Create_HP_TcpPullAgent(HP_TcpPullAgentListener pListener);
//@备注 HP_创建HP_TcpPullClient对象()
//@别名 HP_Tcp拉客户端对象创建()
HPSOCKET_API HP_TcpPullClient __HP_CALL Create_HP_TcpPullClient(HP_TcpPullClientListener pListener);
//@备注 HP_创建HP_TcpPackServer对象()
//@别名 HP_Tcp包服务端对象创建()
HPSOCKET_API HP_TcpPackServer __HP_CALL Create_HP_TcpPackServer(HP_TcpServerListener pListener);
//@备注 HP_创建HP_TcpPackAgent对象()
//@别名 HP_Tcp包代理端对象创建()
HPSOCKET_API HP_TcpPackAgent __HP_CALL Create_HP_TcpPackAgent(HP_TcpAgentListener pListener);
//@备注 HP_创建HP_TcpPackClient对象()
//@别名 HP_Tcp包客户端对象创建()
HPSOCKET_API HP_TcpPackClient __HP_CALL Create_HP_TcpPackClient(HP_TcpClientListener pListener);

//@备注 HP_销毁HP_TcpServer对象()
//@别名 HP_Tcp服务端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpServer(HP_TcpServer pServer);
//@备注 HP_销毁HP_TcpAgent对象()
//@别名 HP_Tcp代理端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpAgent(HP_TcpAgent pAgent);
//@备注 HP_销毁HP_TcpClient对象()
//@别名 HP_Tcp客户端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpClient(HP_TcpClient pClient);
//@备注 HP_销毁HP_TcpPullServer对象()
//@别名 HP_Tcp拉服务端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpPullServer(HP_TcpPullServer pServer);
//@备注 HP_销毁HP_TcpPullAgent对象()
//@别名 HP_Tcp拉代理端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpPullAgent(HP_TcpPullAgent pAgent);
//@备注 HP_销毁HP_TcpPullClient对象()
//@别名 HP_Tcp拉客户端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpPullClient(HP_TcpPullClient pClient);
//@备注 HP_销毁HP_TcpPackServer对象()
//@别名 HP_Tcp包服务端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpPackServer(HP_TcpPackServer pServer);
//@备注 HP_销毁HP_TcpPackAgent对象()
//@别名 HP_Tcp包代理端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpPackAgent(HP_TcpPackAgent pAgent);
//@备注 HP_销毁HP_TcpPackClient对象()
//@别名 HP_Tcp包客户端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpPackClient(HP_TcpPackClient pClient);
//@备注 HP_创建HP_TcpServerListener对象()
//@别名 HP_Tcp服务端侦听器对象创建()
HPSOCKET_API HP_TcpServerListener __HP_CALL Create_HP_TcpServerListener();
//@备注 HP_创建HP_TcpAgentListener对象()
//@别名 HP_Tcp代理端侦听器对象创建()
HPSOCKET_API HP_TcpAgentListener __HP_CALL Create_HP_TcpAgentListener();
//@备注 HP_创建HP_TcpClientListener对象()
//@别名 HP_Tcp客户端侦听器对象创建()
HPSOCKET_API HP_TcpClientListener __HP_CALL Create_HP_TcpClientListener();
//@备注 HP_创建HP_TcpPullServerListener对象()
//@别名 HP_Tcp拉服务端侦听器对象创建()
HPSOCKET_API HP_TcpPullServerListener __HP_CALL Create_HP_TcpPullServerListener();
//@备注 HP_创建HP_TcpPullAgentListener对象()
//@别名 HP_Tcp拉代理端侦听器对象创建()
HPSOCKET_API HP_TcpPullAgentListener __HP_CALL Create_HP_TcpPullAgentListener();
//@备注 HP_创建HP_TcpPullClientListener对象()
//@别名 HP_Tcp拉客户端侦听器对象创建()
HPSOCKET_API HP_TcpPullClientListener __HP_CALL Create_HP_TcpPullClientListener();
//@备注 HP_创建HP_TcpPackServerListener对象()
//@别名 HP_Tcp包服务端侦听器对象创建()
HPSOCKET_API HP_TcpPackServerListener __HP_CALL Create_HP_TcpPackServerListener();
//@备注 HP_创建HP_TcpPackAgentListener对象()
//@别名 HP_Tcp包代理端侦听器对象创建()
HPSOCKET_API HP_TcpPackAgentListener __HP_CALL Create_HP_TcpPackAgentListener();
//@备注 HP_创建HP_TcpPackClientListener对象()
//@别名 HP_Tcp包客户端侦听器对象创建()
HPSOCKET_API HP_TcpPackClientListener __HP_CALL Create_HP_TcpPackClientListener();
//@备注 HP_销毁HP_TcpServerListener对象()
//@别名 HP_Tcp服务端侦听器对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpServerListener(HP_TcpServerListener pListener);
//@备注 HP_销毁HP_TcpAgentListener对象()
//@别名 HP_Tcp代理服务端侦听器对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpAgentListener(HP_TcpAgentListener pListener);
//@备注 HP_销毁HP_TcpClientListener对象()
//@别名 HP_Tcp客户端侦听器对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpClientListener(HP_TcpClientListener pListener);
//@备注 HP_销毁HP_TcpPullServerListener对象()
//@别名 HP_Tcp拉服务端侦听器对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpPullServerListener(HP_TcpPullServerListener pListener);
//@备注 HP_销毁HP_TcpPullAgentListener对象()
//@别名 HP_Tcp拉代理端侦听器对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpPullAgentListener(HP_TcpPullAgentListener pListener);
//@备注 HP_销毁HP_TcpPullClientListener对象()
//@别名 HP_Tcp拉客户端侦听器对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpPullClientListener(HP_TcpPullClientListener pListener);
//@备注 HP_销毁HP_TcpPackServerListener对象()
//@别名 HP_Tcp包服务端侦听器对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpPackServerListener(HP_TcpPackServerListener pListener);
//@备注 HP_销毁HP_TcpPackAgentListener对象()
//@别名 HP_Tcp包代理端侦听器对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpPackAgentListener(HP_TcpPackAgentListener pListener);
//@备注 HP_销毁HP_TcpPackClientListener对象()
//@别名 HP_P_Tcp包客户端侦听器对象销毁H()
HPSOCKET_API void __HP_CALL Destroy_HP_TcpPackClientListener(HP_TcpPackClientListener pListener);

#ifdef _UDP_SUPPORT

//@备注 HP_创建HP_UdpServer对象()
//@别名 HP_udp服务端对象创建()
HPSOCKET_API HP_UdpServer __HP_CALL Create_HP_UdpServer(HP_UdpServerListener pListener);
//@备注 HP_创建HP_UdpClient对象()
//@别名 HP_udp客户端对象创建()
HPSOCKET_API HP_UdpClient __HP_CALL Create_HP_UdpClient(HP_UdpClientListener pListener);
//@备注 HP_创建HP_UdpCast对象()
//@别名 HP_udpCast端对象创建()
HPSOCKET_API HP_UdpCast __HP_CALL Create_HP_UdpCast(HP_UdpCastListener pListener);
//@备注 HP_创建HP_UdpNode对象()
//@别名 HP_udp节点端对象创建()
HPSOCKET_API HP_UdpNode __HP_CALL Create_HP_UdpNode(HP_UdpNodeListener pListener);
//@备注 HP_创建HP_UdpArqServer对象()
//@别名 HP_udp代理服务端对象创建()
HPSOCKET_API HP_UdpArqServer __HP_CALL Create_HP_UdpArqServer(HP_UdpServerListener pListener);
//@备注 HP_创建HP_UdpArqClient对象()
//@别名 HP_udp代理客户端对象创建()
HPSOCKET_API HP_UdpArqClient __HP_CALL Create_HP_UdpArqClient(HP_UdpClientListener pListener);

//@备注 HP_销毁HP_UdpServer对象()
//@别名 HP_Udp服务端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_UdpServer(HP_UdpServer pServer);
//@备注 HP_销毁HP_UdpClient对象()
//@别名 HP_Udp客户端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_UdpClient(HP_UdpClient pClient);
//@备注 HP_销毁HP_UdpCast对象()
//@别名 HP_UdpCast端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_UdpCast(HP_UdpCast pCast);
//@备注 HP_销毁HP_UdpNode对象()
//@别名 HP_udp节点端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_UdpNode(HP_UdpNode pNode);
//@备注 HP_销毁HP_UdpArqServer对象()
//@别名 HP_udp代理服务端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_UdpArqServer(HP_UdpArqServer pServer);
//@备注 HP_销毁HP_UdpArqClient对象()
//@别名 HP_udp代理客户端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_UdpArqClient(HP_UdpArqClient pClient);

//@备注 HP_创建HP_UdpServerListener对象()
//@别名 HP_udp服务端侦听器对象创建()
HPSOCKET_API HP_UdpServerListener __HP_CALL Create_HP_UdpServerListener();
//@备注 HP_创建HP_UdpClientListener对象()
//@别名 HP_udp客户端侦听器对象创建()
HPSOCKET_API HP_UdpClientListener __HP_CALL Create_HP_UdpClientListener();
//@备注 HP_创建HP_UdpCastListener对象()
//@别名 HP_udpCast端侦听器对象创建()
HPSOCKET_API HP_UdpCastListener __HP_CALL Create_HP_UdpCastListener();
//@备注 HP_创建HP_UdpNodeListener对象()
//@别名 HP_udp节点端侦听对象创建()
HPSOCKET_API HP_UdpNodeListener __HP_CALL Create_HP_UdpNodeListener();
//@备注 HP_创建HP_UdpArqServerListener对象()
//@别名 HP_udp代理服务端侦听对象创建()
HPSOCKET_API HP_UdpArqServerListener __HP_CALL Create_HP_UdpArqServerListener();
//@备注 HP_创建HP_UdpArqClientListener对象()
//@别名 HP_udp代理客户端侦听对象创建()
HPSOCKET_API HP_UdpArqClientListener __HP_CALL Create_HP_UdpArqClientListener();

//@备注 HP_销毁HP_UdpServerListener对象()
//@别名 HP_udp服务端侦听器对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_UdpServerListener(HP_UdpServerListener pListener);
//@备注 HP_销毁HP_UdpClientListener对象()
//@别名 HP_udp客户端侦听器对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_UdpClientListener(HP_UdpClientListener pListener);
//@备注 HP_销毁HP_UdpCastListener对象()
//@别名 HP_udpCas端侦听器对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_UdpCastListener(HP_UdpCastListener pListener);
//@备注 HP_销毁HP_UdpNodeListener对象()
//@别名 HP_udp节点端侦听器对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_UdpNodeListener(HP_UdpNodeListener pListener);
//@备注 HP_销毁HP_UdpArqServerListener对象()
//@别名 HP_udp代理服务端侦听对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_UdpArqServerListener(HP_UdpArqServerListener pListener);
//@备注 HP_销毁HP_UdpArqClientListener对象()
//@别名 HP_udp代理客户端侦听对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_UdpArqClientListener(HP_UdpArqClientListener pListener);

#endif

/**********************************************************************************/
/***************************** Server 回调函数置方法 *****************************/

HPSOCKET_API void __HP_CALL HP_Set_FN_Server_OnPrepareListen(HP_ServerListener pListener	, HP_FN_Server_OnPrepareListen fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Server_OnAccept(HP_ServerListener pListener			, HP_FN_Server_OnAccept fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Server_OnHandShake(HP_ServerListener pListener		, HP_FN_Server_OnHandShake fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Server_OnSend(HP_ServerListener pListener				, HP_FN_Server_OnSend fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Server_OnReceive(HP_ServerListener pListener			, HP_FN_Server_OnReceive fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Server_OnPullReceive(HP_ServerListener pListener		, HP_FN_Server_OnPullReceive fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Server_OnClose(HP_ServerListener pListener			, HP_FN_Server_OnClose fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Server_OnShutdown(HP_ServerListener pListener			, HP_FN_Server_OnShutdown fn);

/**********************************************************************************/
/****************************** Agent 回调函数置方法 *****************************/

HPSOCKET_API void __HP_CALL HP_Set_FN_Agent_OnPrepareConnect(HP_AgentListener pListener		, HP_FN_Agent_OnPrepareConnect fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Agent_OnConnect(HP_AgentListener pListener			, HP_FN_Agent_OnConnect fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Agent_OnHandShake(HP_AgentListener pListener			, HP_FN_Agent_OnHandShake fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Agent_OnSend(HP_AgentListener pListener				, HP_FN_Agent_OnSend fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Agent_OnReceive(HP_AgentListener pListener			, HP_FN_Agent_OnReceive fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Agent_OnPullReceive(HP_AgentListener pListener		, HP_FN_Agent_OnPullReceive fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Agent_OnClose(HP_AgentListener pListener				, HP_FN_Agent_OnClose fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Agent_OnShutdown(HP_AgentListener pListener			, HP_FN_Agent_OnShutdown fn);

/**********************************************************************************/
/***************************** Client 回调函数置方法 *****************************/

HPSOCKET_API void __HP_CALL HP_Set_FN_Client_OnPrepareConnect(HP_ClientListener pListener	, HP_FN_Client_OnPrepareConnect fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Client_OnConnect(HP_ClientListener pListener			, HP_FN_Client_OnConnect fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Client_OnHandShake(HP_ClientListener pListener		, HP_FN_Client_OnHandShake fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Client_OnSend(HP_ClientListener pListener				, HP_FN_Client_OnSend fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Client_OnReceive(HP_ClientListener pListener			, HP_FN_Client_OnReceive fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Client_OnPullReceive(HP_ClientListener pListener		, HP_FN_Client_OnPullReceive fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_Client_OnClose(HP_ClientListener pListener			, HP_FN_Client_OnClose fn);

#ifdef _UDP_SUPPORT

/**********************************************************************************/
/***************************** UdpNode 回调函数置方法 *****************************/

HPSOCKET_API void __HP_CALL HP_Set_FN_UdpNode_OnPrepareListen(HP_UdpNodeListener pListener	, HP_FN_UdpNode_OnPrepareListen fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_UdpNode_OnSend(HP_UdpNodeListener pListener			, HP_FN_UdpNode_OnSend fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_UdpNode_OnReceive(HP_UdpNodeListener pListener		, HP_FN_UdpNode_OnReceive fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_UdpNode_OnError(HP_UdpNodeListener pListener			, HP_FN_UdpNode_OnError fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_UdpNode_OnShutdown(HP_UdpNodeListener pListener		, HP_FN_UdpNode_OnShutdown fn);

#endif

/**************************************************************************/
/***************************** Server 操作方法 *****************************/

/*
* 名称：启动通信组件
* 描述：启动服务端通信组件，启动完成后可开始接收客户端连接并收发数据
*		
* 参数：		lpszBindAddress	-- 监听地址
*			usPort			-- 监听端口
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 HP_Server_GetLastError() 取错误代码
*/
//@别名 HP_启动服务器通信组件()
HPSOCKET_API BOOL __HP_CALL HP_Server_Start(HP_Server pServer, LPCTSTR lpszBindAddress, USHORT usPort);

/*
* 名称：关闭通信组件
* 描述：关闭服务端通信组件，关闭完成后断开所有客户端连接并释放所有资源
*		
* 参数：	
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 HP_Server_GetLastError() 取错误代码
*/
//@别名 HP_关闭服务器通信组件()
HPSOCKET_API BOOL __HP_CALL HP_Server_Stop(HP_Server pServer);

/*
* 名称：等待
* 描述：等待通信组件停止运行
*		
* 参数：		dwMilliseconds	-- 超时时间（毫秒，默认：-1，永不超时）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取错误代码
*/
//@别名 HP_服务器等待()
HPSOCKET_API BOOL __HP_CALL HP_Server_Wait(HP_Server pServer, DWORD dwMilliseconds);

/*
* 名称：发送数据
* 描述：向指定连接发送数据
*		
* 参数：		dwConnID	-- 连接 ID
*			pBuffer		-- 发送缓冲区
*			iLength		-- 发送缓冲区长度
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_服务器发送数据()
HPSOCKET_API BOOL __HP_CALL HP_Server_Send(HP_Server pServer, HP_CONNID dwConnID, const BYTE* pBuffer, int iLength);

/*
* 名称：发送数据
* 描述：向指定连接发送数据
*		
* 参数：		dwConnID	-- 连接 ID
*			pBuffer		-- 发送缓冲区
*			iLength		-- 发送缓冲区长度
*			iOffset		-- 发送缓冲区指针偏移量
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_服务器发送数据部分()
HPSOCKET_API BOOL __HP_CALL HP_Server_SendPart(HP_Server pServer, HP_CONNID dwConnID, const BYTE* pBuffer, int iLength, int iOffset);

/*
* 名称：发送多组数据
* 描述：向指定连接发送多组数据
*		TCP - 顺序发送所有数据包 
*		UDP - 把所有数据包组合成一个数据包发送（数据包的总长度不能大于置的 UDP 包最大长度） 
*		
* 参数：		dwConnID	-- 连接 ID
*			pBuffers	-- 发送缓冲区数组
*			iCount		-- 发送缓冲区数目
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_服务器发送多组数据()
HPSOCKET_API BOOL __HP_CALL HP_Server_SendPackets(HP_Server pServer, HP_CONNID dwConnID, const WSABUF pBuffers[], int iCount);

/*
* 名称：暂停/恢复接收
* 描述：暂停/恢复某个连接的数据接收工作
*		
* 参数：		dwConnID	-- 连接 ID
*			bPause		-- TRUE - 暂停, FALSE - 恢复
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败
*/
//@别名 HP_服务器暂停或者恢复接收()
HPSOCKET_API BOOL __HP_CALL HP_Server_PauseReceive(HP_Server pServer, HP_CONNID dwConnID, BOOL bPause);

/*
* 名称：断开连接
* 描述：断开与某个客户端的连接
*		
* 参数：		dwConnID	-- 连接 ID
*			bForce		-- 是否强制断开连接
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败
*/
//@别名 HP_服务器断开连接()
HPSOCKET_API BOOL __HP_CALL HP_Server_Disconnect(HP_Server pServer, HP_CONNID dwConnID, BOOL bForce);

/*
* 名称：断开超时连接
* 描述：断开超过指定时长的连接
*		
* 参数：		dwPeriod	-- 时长（毫秒）
*			bForce		-- 是否强制断开连接
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败
*/
//@别名 HP_服务器断开超时连接()
HPSOCKET_API BOOL __HP_CALL HP_Server_DisconnectLongConnections(HP_Server pServer, DWORD dwPeriod, BOOL bForce);

/*
* 名称：断开静默连接
* 描述：断开超过指定时长的静默连接
*		
* 参数：		dwPeriod	-- 时长（毫秒）
*			bForce		-- 是否强制断开连接
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败
*/
//@别名 HP_服务器断开静默连接()
HPSOCKET_API BOOL __HP_CALL HP_Server_DisconnectSilenceConnections(HP_Server pServer, DWORD dwPeriod, BOOL bForce);

/******************************************************************************/
/***************************** Server 属性访问方法 *****************************/

/*
* 名称：置连接的附加数据
* 描述：是否为连接绑定附加数据或者绑定什么样的数据，均由应用程序只身决定
*		
* 参数：		dwConnID	-- 连接 ID
*			pv			-- 数据
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败（无效的连接 ID）
*/
//@别名 HP_服务器置连接的附加数据()
HPSOCKET_API BOOL __HP_CALL HP_Server_SetConnectionExtra(HP_Server pServer, HP_CONNID dwConnID, PVOID pExtra);

/*
* 名称：取连接的附加数据
* 描述：是否为连接绑定附加数据或者绑定什么样的数据，均由应用程序只身决定
*		
* 参数：		dwConnID	-- 连接 ID
*			ppv			-- 数据指针
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败（无效的连接 ID）
*/
//@别名 HP_服务器取连接的附加数据()
HPSOCKET_API BOOL __HP_CALL HP_Server_GetConnectionExtra(HP_Server pServer, HP_CONNID dwConnID, PVOID* ppExtra);

/* 检测是否为安全连接（SSL/HTTPS） */
//@别名 HP_服务器检测是否为安全连接()
HPSOCKET_API BOOL __HP_CALL HP_Server_IsSecure(HP_Server pServer);
/* 检查通信组件是否已启动 */
//@别名 HP_服务器检查通信组件是否已启动()
HPSOCKET_API BOOL __HP_CALL HP_Server_HasStarted(HP_Server pServer);
/* 查看通信组件当前状态 */
//@别名 HP_服务器查看通信组件当前状态()
HPSOCKET_API En_HP_ServiceState __HP_CALL HP_Server_GetState(HP_Server pServer);
/* 取最近一次失败操作的错误代码 */
//@别名 HP_服务器取最近一次失败操作的错误代码()
HPSOCKET_API En_HP_SocketError __HP_CALL HP_Server_GetLastError(HP_Server pServer);
/* 取最近一次失败操作的错误描述 */
//@别名 HP_服务器取最近一次失败操作的错误描述()
HPSOCKET_API LPCTSTR __HP_CALL HP_Server_GetLastErrorDesc(HP_Server pServer);
/* 取连接中未发出数据的长度 */
//@别名 HP_服务器取连接中未发出数据的长度()
HPSOCKET_API BOOL __HP_CALL HP_Server_GetPendingDataLength(HP_Server pServer, HP_CONNID dwConnID, int* piPending);
/* 取连接的数据接收状态 */
//@别名 HP_服务器取连接的数据接收状态()
HPSOCKET_API BOOL __HP_CALL HP_Server_IsPauseReceive(HP_Server pServer, HP_CONNID dwConnID, BOOL* pbPaused);
/* 检测是否有效连接 */
//@别名 HP_服务器检测是否有效连接()
HPSOCKET_API BOOL __HP_CALL HP_Server_IsConnected(HP_Server pServer, HP_CONNID dwConnID);
/* 取客户端连接数 */
//@别名 HP_服务器取客户连接数()
HPSOCKET_API DWORD __HP_CALL HP_Server_GetConnectionCount(HP_Server pServer);
/* 取所有连接的 HP_CONNID */
//@别名 HP_服务器取所有连接HP_网络连接字符串()
HPSOCKET_API BOOL __HP_CALL HP_Server_GetAllConnectionIDs(HP_Server pServer, HP_CONNID pIDs[], DWORD* pdwCount);
/* 取某个客户端连接时长（毫秒） */
//@别名 HP_服务器取客户端连接时长()
HPSOCKET_API BOOL __HP_CALL HP_Server_GetConnectPeriod(HP_Server pServer, HP_CONNID dwConnID, DWORD* pdwPeriod);
/* 取某个连接静默时间（毫秒） */
//@别名 HP_服务器取连接静默时间()
HPSOCKET_API BOOL __HP_CALL HP_Server_GetSilencePeriod(HP_Server pServer, HP_CONNID dwConnID, DWORD* pdwPeriod);
/* 取监听 Socket 的地址信息 */
//@别名 HP_服务器取监听套接字的地址信息()
HPSOCKET_API BOOL __HP_CALL HP_Server_GetListenAddress(HP_Server pServer, TCHAR lpszAddress[], int* piAddressLen, USHORT* pusPort);
/* 取某个连接的本地地址信息 */
//@别名 HP_服务器取本连接的地地址信息()
HPSOCKET_API BOOL __HP_CALL HP_Server_GetLocalAddress(HP_Server pServer, HP_CONNID dwConnID, TCHAR lpszAddress[], int* piAddressLen, USHORT* pusPort);
/* 取某个连接的远程地址信息 */
//@别名 HP_服务器取远程地址信息()
HPSOCKET_API BOOL __HP_CALL HP_Server_GetRemoteAddress(HP_Server pServer, HP_CONNID dwConnID, TCHAR lpszAddress[], int* piAddressLen, USHORT* pusPort);

/* 置地址重用选项 */
//@别名 HP_服务器置地址重用选项()
HPSOCKET_API void __HP_CALL HP_Server_SetReuseAddressPolicy(HP_Server pServer, En_HP_ReuseAddressPolicy enReusePolicy);
/* 置数据发送策略 */
//@别名 HP_服务器置数据发送策略()
HPSOCKET_API void __HP_CALL HP_Server_SetSendPolicy(HP_Server pServer, En_HP_SendPolicy enSendPolicy);
/* 置 OnSend 事件同步策略（默认：OSSP_NONE，不同步） */
//@别名 HP_服务器置OnSend事件同步策略()
HPSOCKET_API void __HP_CALL HP_Server_SetOnSendSyncPolicy(HP_Server pServer, En_HP_OnSendSyncPolicy enSyncPolicy);
/* 置 Socket 缓存对象()锁定时间（毫秒，在锁定期间该 Socket 缓存对象()不能被取使用） */
//@别名 HP_服务器置Socket缓存对象()
//@备注 置Socket缓存对象()锁定时间（毫秒，在锁定期间该 Socket 缓存对象()不能被取使用）
HPSOCKET_API void __HP_CALL HP_Server_SetFreeSocketObjLockTime(HP_Server pServer, DWORD dwFreeSocketObjLockTime);
/* 置 Socket 缓存池大小（通常置为平均并发连接数量的 1/3 - 1/2） */
//@别名 HP_服务器置套接字缓存池大小()
//@备注 置Socket缓存池大小（通常置为平均并发连接数量的 1/3 - 1/2）
HPSOCKET_API void __HP_CALL HP_Server_SetFreeSocketObjPool(HP_Server pServer, DWORD dwFreeSocketObjPool);
//@备注 置内存块缓存池大小（通常置为 Socket 缓存池大小的 2 - 3 倍） 
//@别名 HP_服务器置内存块缓存池大小()
HPSOCKET_API void __HP_CALL HP_Server_SetFreeBufferObjPool(HP_Server pServer, DWORD dwFreeBufferObjPool);
//@备注 置Socket缓存池回收阀值（通常置为 Socket 缓存池大小的 3 倍） 
//@别名 HP_服务器置Socket缓存池回收阀值()
HPSOCKET_API void __HP_CALL HP_Server_SetFreeSocketObjHold(HP_Server pServer, DWORD dwFreeSocketObjHold);
//@备注 置内存块缓存池回收阀值（通常置为内存块缓存池大小的 3 倍） 
//@别名 HP_服务器置内存块缓存池回收阀值()
HPSOCKET_API void __HP_CALL HP_Server_SetFreeBufferObjHold(HP_Server pServer, DWORD dwFreeBufferObjHold);
//@备注 置最大连接数（组件会根据置值预分配内存，因此需要根据实际情况置，不宜过大）
//@别名 HP_服务器置最大连接数()
HPSOCKET_API void __HP_CALL HP_Server_SetMaxConnectionCount(HP_Server pServer, DWORD dwMaxConnectionCount);
//@备注 置工作线程数量（通常置为 2 * CPU + 2） 
//@别名 HP_服务器置工作线程数量()
HPSOCKET_API void __HP_CALL HP_Server_SetWorkerThreadCount(HP_Server pServer, DWORD dwWorkerThreadCount);
//@备注 置是否标记静默时间（置为 TRUE 时 DisconnectSilenceConnections() 和 GetSilencePeriod() 才有效，默认：TRUE） 
//@别名 HP_服务器置是否标记静默时间()
HPSOCKET_API void __HP_CALL HP_Server_SetMarkSilence(HP_Server pServer, BOOL bMarkSilence);

//@别名 HP_服务器取地址重用选项()
HPSOCKET_API En_HP_ReuseAddressPolicy __HP_CALL HP_Server_GetReuseAddressPolicy(HP_Server pServer);
//@别名 HP_服务器取数据发送策略()
HPSOCKET_API En_HP_SendPolicy __HP_CALL HP_Server_GetSendPolicy(HP_Server pServer);
//@别名 HP_服务器取OnSend事件同步策略()
HPSOCKET_API En_HP_OnSendSyncPolicy __HP_CALL HP_Server_GetOnSendSyncPolicy(HP_Server pServer);
//@别名 HP_服务器取Socket缓存对象()锁定时间()
HPSOCKET_API DWORD __HP_CALL HP_Server_GetFreeSocketObjLockTime(HP_Server pServer);
//@别名 HP_服务器取Socket缓存池大小()
HPSOCKET_API DWORD __HP_CALL HP_Server_GetFreeSocketObjPool(HP_Server pServer);
//@别名 HP_服务器取内存块缓存池大小()
HPSOCKET_API DWORD __HP_CALL HP_Server_GetFreeBufferObjPool(HP_Server pServer);
//@别名 HP_服务器取Socket缓存池回收阀值()
HPSOCKET_API DWORD __HP_CALL HP_Server_GetFreeSocketObjHold(HP_Server pServer);
//@别名 HP_服务器取内存块缓存池回收阀值()
HPSOCKET_API DWORD __HP_CALL HP_Server_GetFreeBufferObjHold(HP_Server pServer);
//@别名 HP_服务器取最大连接数()
HPSOCKET_API DWORD __HP_CALL HP_Server_GetMaxConnectionCount(HP_Server pServer);
//@别名 HP_服务器取工作线程数量()
HPSOCKET_API DWORD __HP_CALL HP_Server_GetWorkerThreadCount(HP_Server pServer);
//@别名 HP_服务器检测是否标记静默时间()
HPSOCKET_API BOOL __HP_CALL HP_Server_IsMarkSilence(HP_Server pServer);

/**********************************************************************************/
/******************************* TCP Server 操作方法 *******************************/

/*
* 名称：发送小文件
* 描述：向指定连接发送 4096 KB 以下的小文件
*		
* 参数：		dwConnID		-- 连接 ID
*			lpszFileName	-- 文件路径
*			pHead			-- 头部附加数据
*			pTail			-- 尾部附加数据
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_TCP服务器发送小文件()
HPSOCKET_API BOOL __HP_CALL HP_TcpServer_SendSmallFile(HP_Server pServer, HP_CONNID dwConnID, LPCTSTR lpszFileName, const LPWSABUF pHead, const LPWSABUF pTail);

/**********************************************************************************/
/***************************** TCP Server 属性访问方法 *****************************/

//@备注 置监听 Socket 的等候队列大小（根据并发连接数量调整置）
//@别名 HP_tcp_服务器置监听Socket的等候队列大小()
HPSOCKET_API void __HP_CALL HP_TcpServer_SetSocketListenQueue(HP_TcpServer pServer, DWORD dwSocketListenQueue);
//@备注 置 Accept 预投递数量（根据负载调整置，Accept 预投递数量越大则支持的并发连接请求越多）
//@别名 HP_tcp_服务器置Accept预投递数量()
HPSOCKET_API void __HP_CALL HP_TcpServer_SetAcceptSocketCount(HP_TcpServer pServer, DWORD dwAcceptSocketCount);
//@备注 置通信数据缓冲区大小（根据平均通信数据包大小调整置，通常置为 1024 的倍数）
//@别名 HP_tcp_服务器置通信数据缓冲区大小()
HPSOCKET_API void __HP_CALL HP_TcpServer_SetSocketBufferSize(HP_TcpServer pServer, DWORD dwSocketBufferSize);
//@备注 置正常心跳包间隔（毫秒，0 则不发送心跳包，默认：60 * 1000）
//@别名 HP_tcp_服务器置正常心跳包间隔()
HPSOCKET_API void __HP_CALL HP_TcpServer_SetKeepAliveTime(HP_TcpServer pServer, DWORD dwKeepAliveTime);
//@备注 置异常心跳包间隔（毫秒，0 不发送心跳包，，默认：20 * 1000，如果超过若干次 [默认：WinXP 5 次, Win7 10 次] 检测不到心跳确认包则认为已断线）
//@别名 HP_tcp_服务器置异常心跳包间隔()
HPSOCKET_API void __HP_CALL HP_TcpServer_SetKeepAliveInterval(HP_TcpServer pServer, DWORD dwKeepAliveInterval);
//@备注 置是否开启无延时模式（默认：FALSE，不开启）
//@别名 HP_tcp_服务器置是否开启无延时模式()
HPSOCKET_API void __HP_CALL HP_TcpServer_SetNoDelay(HP_TcpServer pServer, BOOL bNoDelay);

//@别名 HP_tcp_服务器取Accept预投递数量()
HPSOCKET_API DWORD __HP_CALL HP_TcpServer_GetAcceptSocketCount(HP_TcpServer pServer);
//@别名 HP_tcp_服务器取通信数据缓冲区大小()
HPSOCKET_API DWORD __HP_CALL HP_TcpServer_GetSocketBufferSize(HP_TcpServer pServer);
//@别名 HP_tcp_服务器取监听Socket的等候队列大小()
HPSOCKET_API DWORD __HP_CALL HP_TcpServer_GetSocketListenQueue(HP_TcpServer pServer);
//@别名 HP_tcp_服务器取正常心跳包间隔()
HPSOCKET_API DWORD __HP_CALL HP_TcpServer_GetKeepAliveTime(HP_TcpServer pServer);
//@别名 HP_tcp_服务器取异常心跳包间隔()
HPSOCKET_API DWORD __HP_CALL HP_TcpServer_GetKeepAliveInterval(HP_TcpServer pServer);
//@别名 HP_tcp_服务器检查是否开启无延时模式()
HPSOCKET_API BOOL __HP_CALL HP_TcpServer_IsNoDelay(HP_TcpServer pServer);

#ifdef _UDP_SUPPORT

/**********************************************************************************/
/***************************** UDP Server 属性访问方法 *****************************/

//@备注 置数据报文最大长度（建议在局域网环境下不超过 1432 字节，在广域网环境下不超过 548 字节）
//@别名 HP_UDP_服务器置数据报文最大长度()
HPSOCKET_API void __HP_CALL HP_UdpServer_SetMaxDatagramSize(HP_UdpServer pServer, DWORD dwMaxDatagramSize);
/* UDP_服务器取数据报文最大长度 */
//@别名 HP_UDP_服务器取数据报文最大长度()
HPSOCKET_API DWORD __HP_CALL HP_UdpServer_GetMaxDatagramSize(HP_UdpServer pServer);
//@备注 Receive 预投递数量（根据负载调整UDP_服务器置，Receive 预投递数量越大则丢包概率越小）
//@别名 HP_UDP_服务器置Receive预投递数量()
HPSOCKET_API void __HP_CALL HP_UdpServer_SetPostReceiveCount(HP_UdpServer pServer, DWORD dwPostReceiveCount);
/* UDP_服务器取 Receive 预投递数量 */
//@别名 HP_UDP_服务器取Receive预投递数量()
HPSOCKET_API DWORD __HP_CALL HP_UdpServer_GetPostReceiveCount(HP_UdpServer pServer);
//@备注 UDP_服务器置监测包尝试次数（0 则不发送监测跳包，如果超过最大尝试次数则认为已断线）
//@别名 HP_UDP_服务器置监测包尝试次数()
HPSOCKET_API void __HP_CALL HP_UdpServer_SetDetectAttempts(HP_UdpServer pServer, DWORD dwDetectAttempts);
//@备注 UDP_服务器置监测包发送间隔（毫秒，0 不发送监测包
//@别名 HP_UDP_服务器置监测包发送间隔()
HPSOCKET_API void __HP_CALL HP_UdpServer_SetDetectInterval(HP_UdpServer pServer, DWORD dwDetectInterval);
/* UDP_服务器取心跳检查次数 */
//@别名 HP_UDP_服务器取心跳检查次数()
HPSOCKET_API DWORD __HP_CALL HP_UdpServer_GetDetectAttempts(HP_UdpServer pServer);
/* UDP_服务器取心跳检查间隔 */
//@别名 HP_UDP_服务器取心跳检查间隔()
HPSOCKET_API DWORD __HP_CALL HP_UdpServer_GetDetectInterval(HP_UdpServer pServer);

/**********************************************************************************/
/*************************** UDP ARQ Server 属性访问方法 ***************************/

//@备注 UDP丢包重传服务器置是否开启 nodelay 模式（默认：FALSE，不开启）
//@别名 HP_UDP丢包重传服务器置是否开启无延时()
HPSOCKET_API void __HP_CALL HP_UdpArqServer_SetNoDelay(HP_UdpArqServer pServer, BOOL bNoDelay);
//@备注 UDP丢包重传服务器置是否关闭拥塞控制（默认：FALSE，不关闭）
//@别名 HP_UDP丢包重传服务器置是否关闭拥塞控制()
HPSOCKET_API void __HP_CALL HP_UdpArqServer_SetTurnoffCongestCtrl(HP_UdpArqServer pServer, BOOL bTurnOff);
//@备注 UDP丢包重传服务器置数据刷新间隔（毫秒，默认：60）
//@别名 HP_UDP丢包重传服务器置数据刷新间隔()
HPSOCKET_API void __HP_CALL HP_UdpArqServer_SetFlushInterval(HP_UdpArqServer pServer, DWORD dwFlushInterval);
//@备注 UDP丢包重传服务器置快速重传 ACK 跨越次数（默认：0，关闭快速重传）
//@别名 HP_UDP丢包重传服务器置快速重传ACK跨越次数()
HPSOCKET_API void __HP_CALL HP_UdpArqServer_SetResendByAcks(HP_UdpArqServer pServer, DWORD dwResendByAcks);
//@备注 UDP丢包重传服务器置发送窗口大小（数据包数量，默认：128）
//@别名 HP_UDP丢包重传服务器置发送窗口大小()
HPSOCKET_API void __HP_CALL HP_UdpArqServer_SetSendWndSize(HP_UdpArqServer pServer, DWORD dwSendWndSize);
//@备注 UDP丢包重传服务器置接收窗口大小（数据包数量，默认：512）
//@别名 HP_UDP丢包重传服务器置接收窗口大小()
HPSOCKET_API void __HP_CALL HP_UdpArqServer_SetRecvWndSize(HP_UdpArqServer pServer, DWORD dwRecvWndSize);
//@备注 UDP丢包重传服务器置最小重传超时时间（毫秒，默认：30）
//@别名 HP_UDP丢包重传服务器置最小重传超时时间()
HPSOCKET_API void __HP_CALL HP_UdpArqServer_SetMinRto(HP_UdpArqServer pServer, DWORD dwMinRto);
//@备注 UDP丢包重传服务器置快速握手次数限制（默认：5，如果为 0 则不限制）
//@别名 HP_UDP丢包重传服务器置快速握手次数限制()
HPSOCKET_API void __HP_CALL HP_UdpArqServer_SetFastLimit(HP_UdpArqServer pServer, DWORD dwFastLimit);
//@备注 UDP丢包重传服务器置最大传输单元（默认：0，与 SetMaxDatagramSize() 一致）
//@别名 HP_UDP丢包重传服务器置最大传输单元()
HPSOCKET_API void __HP_CALL HP_UdpArqServer_SetMaxTransUnit(HP_UdpArqServer pServer, DWORD dwMaxTransUnit);
//@备注 UDP丢包重传服务器置最大数据包大小（默认：4096）
//@别名 HP_UDP丢包重传服务器置最大数据包大小()
HPSOCKET_API void __HP_CALL HP_UdpArqServer_SetMaxMessageSize(HP_UdpArqServer pServer, DWORD dwMaxMessageSize);
//@备注 UDP丢包重传服务器置握手超时时间（毫秒，默认：5000）
//@别名 HP_UDP丢包重传服务器置握手超时时间()
HPSOCKET_API void __HP_CALL HP_UdpArqServer_SetHandShakeTimeout(HP_UdpArqServer pServer, DWORD dwHandShakeTimeout);

//@别名 HP_udp丢包服务器检测是否开启无延时模式()
HPSOCKET_API BOOL __HP_CALL HP_UdpArqServer_IsNoDelay(HP_UdpArqServer pServer);
//@别名 HP_udp丢包服务器检测是否关闭拥塞控制()
HPSOCKET_API BOOL __HP_CALL HP_UdpArqServer_IsTurnoffCongestCtrl(HP_UdpArqServer pServer);
//@别名 HP_udp丢包服务器取数据刷新间隔()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqServer_GetFlushInterval(HP_UdpArqServer pServer);
//@别名 HP_udp丢包服务器取快速重传ACK跨越次数()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqServer_GetResendByAcks(HP_UdpArqServer pServer);
//@别名 HP_udp丢包服务器取发送窗口大小()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqServer_GetSendWndSize(HP_UdpArqServer pServer);
//@别名 HP_udp丢包服务器取接收窗口大小()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqServer_GetRecvWndSize(HP_UdpArqServer pServer);
//@别名 HP_udp丢包服务器取最小重传超时时间()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqServer_GetMinRto(HP_UdpArqServer pServer);
//@别名 HP_udp丢包服务器取快速握手次数限制()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqServer_GetFastLimit(HP_UdpArqServer pServer);
//@别名 HP_udp丢包服务器取最大传输单元()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqServer_GetMaxTransUnit(HP_UdpArqServer pServer);
//@别名 HP_udp丢包服务器取最大数据包大小()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqServer_GetMaxMessageSize(HP_UdpArqServer pServer);
//@别名 HP_udp丢包服务器取握手超时时间()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqServer_GetHandShakeTimeout(HP_UdpArqServer pServer);

//@别名 HP_udp丢包服务器取等待发送包数量()
HPSOCKET_API BOOL __HP_CALL HP_UdpArqServer_GetWaitingSendMessageCount(HP_UdpArqServer pServer, HP_CONNID dwConnID, int* piCount);

#endif

/**************************************************************************/
/***************************** Agent 操作方法 *****************************/

/*
* 名称：启动通信组件
* 描述：启动通信代理组件，启动完成后可开始连接远程服务器
*		
* 参数：		lpszBindAddress	-- 绑定地址（默认：nullptr，绑定任意地址）
*			bAsyncConnect	-- 是否采用异步 Connect
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 HP_Agent_GetLastError() 取错误代码
*/
//@别名 HP_启动代理通信组件()
HPSOCKET_API BOOL __HP_CALL HP_Agent_Start(HP_Agent pAgent, LPCTSTR lpszBindAddress, BOOL bAsyncConnect);

/*
* 名称：关闭通信组件
* 描述：关闭通信组件，关闭完成后断开所有连接并释放所有资源
*		
* 参数：	
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 HP_Agent_GetLastError() 取错误代码
*/
//@别名 HP_关闭代理通信组件()
HPSOCKET_API BOOL __HP_CALL HP_Agent_Stop(HP_Agent pAgent);

/*
* 名称：等待
* 描述：等待通信组件停止运行
*		
* 参数：		dwMilliseconds	-- 超时时间（毫秒，默认：-1，永不超时）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取错误代码
*/
//@别名 HP_代理通信等待()
HPSOCKET_API BOOL __HP_CALL HP_Agent_Wait(HP_Agent pAgent, DWORD dwMilliseconds);

/*
* 名称：连接服务器
* 描述：连接服务器，连接成功后 IAgentListener 会接收到 OnConnect() / OnHandShake() 事件
*		
* 参数：		lpszRemoteAddress	-- 服务端地址
*			usPort				-- 服务端端口
*			pdwConnID			-- 连接 ID（默认：nullptr，不取连接 ID）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过函数 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_代理通信连接()
HPSOCKET_API BOOL __HP_CALL HP_Agent_Connect(HP_Agent pAgent, LPCTSTR lpszRemoteAddress, USHORT usPort, HP_CONNID* pdwConnID);

/*
* 名称：连接服务器
* 描述：连接服务器，连接成功后 IAgentListener 会接收到 OnConnect() / OnHandShake() 事件
*		
* 参数：		lpszRemoteAddress	-- 服务端地址
*			usPort				-- 服务端端口
*			pdwConnID			-- 连接 ID（默认：nullptr，不取连接 ID）
*			pExtra				-- 连接附加数据（默认：nullptr）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过函数 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_代理通信使用额外连接()
HPSOCKET_API BOOL __HP_CALL HP_Agent_ConnectWithExtra(HP_Agent pAgent, LPCTSTR lpszRemoteAddress, USHORT usPort, HP_CONNID* pdwConnID, PVOID pExtra);

/*
* 名称：连接服务器
* 描述：连接服务器，连接成功后 IAgentListener 会接收到 OnConnect() / OnHandShake() 事件
*		
* 参数：		lpszRemoteAddress	-- 服务端地址
*			usPort				-- 服务端端口
*			pdwConnID			-- 连接 ID（默认：nullptr，不取连接 ID）
*			usLocalPort			-- 本地端口（默认：0）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过函数 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_代理通信连接本地端口()
HPSOCKET_API BOOL __HP_CALL HP_Agent_ConnectWithLocalPort(HP_Agent pAgent, LPCTSTR lpszRemoteAddress, USHORT usPort, HP_CONNID* pdwConnID, USHORT usLocalPort);

/*
* 名称：连接服务器
* 描述：连接服务器，连接成功后 IAgentListener 会接收到 OnConnect() / OnHandShake() 事件
*		
* 参数：		lpszRemoteAddress	-- 服务端地址
*			usPort				-- 服务端端口
*			pdwConnID			-- 连接 ID（默认：nullptr，不取连接 ID）
*			lpszLocalAddress	-- 本地地址（默认：nullptr，使用 Start() 方法中绑定的地址）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过函数 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_代理通信连接到本地地址()
HPSOCKET_API BOOL __HP_CALL HP_Agent_ConnectWithLocalAddress(HP_Agent pAgent, LPCTSTR lpszRemoteAddress, USHORT usPort, HP_CONNID* pdwConnID, LPCTSTR lpszLocalAddress);

/* 
* 名称：连接服务器
* 描述：连接服务器，连接成功后 IAgentListener 会接收到 OnConnect() / OnHandShake() 事件
*		
* 参数：		lpszRemoteAddress	-- 服务端地址
*			usPort				-- 服务端端口
*			pdwConnID			-- 连接 ID（默认：nullptr，不取连接 ID）
*			pExtra				-- 连接附加数据（默认：nullptr）
*			usLocalPort			-- 本地端口（默认：0）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过函数 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_代理通信连接外部和本地端口()
HPSOCKET_API BOOL __HP_CALL HP_Agent_ConnectWithExtraAndLocalPort(HP_Agent pAgent, LPCTSTR lpszRemoteAddress, USHORT usPort, HP_CONNID* pdwConnID, PVOID pExtra, USHORT usLocalPort);

/* 
* 名称：连接服务器
* 描述：连接服务器，连接成功后 IAgentListener 会接收到 OnConnect() / OnHandShake() 事件
*		
* 参数：		lpszRemoteAddress	-- 服务端地址
*			usPort				-- 服务端端口
*			pdwConnID			-- 连接 ID（默认：nullptr，不取连接 ID）
*			pExtra				-- 连接附加数据（默认：nullptr）
*			usLocalPort			-- 本地端口（默认：0）
*			lpszLocalAddress	-- 本地地址（默认：nullptr，使用 Start() 方法中绑定的地址）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过函数 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_代理通信连接外部和本地地址端口()
HPSOCKET_API BOOL __HP_CALL HP_Agent_ConnectWithExtraAndLocalAddressPort(HP_Agent pAgent, LPCTSTR lpszRemoteAddress, USHORT usPort, HP_CONNID* pdwConnID, PVOID pExtra, USHORT usLocalPort, LPCTSTR lpszLocalAddress);

/*
* 名称：发送数据
* 描述：向指定连接发送数据
*		
* 参数：		dwConnID	-- 连接 ID
*			pBuffer		-- 发送缓冲区
*			iLength		-- 发送缓冲区长度
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_代理通信发送数据()
HPSOCKET_API BOOL __HP_CALL HP_Agent_Send(HP_Agent pAgent, HP_CONNID dwConnID, const BYTE* pBuffer, int iLength);

/*
* 名称：发送数据
* 描述：向指定连接发送数据
*		
* 参数：		dwConnID	-- 连接 ID
*			pBuffer		-- 发送缓冲区
*			iLength		-- 发送缓冲区长度
*			iOffset		-- 发送缓冲区指针偏移量
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_代理通信发送数据part()

HPSOCKET_API BOOL __HP_CALL HP_Agent_SendPart(HP_Agent pAgent, HP_CONNID dwConnID, const BYTE* pBuffer, int iLength, int iOffset);

/*
* 名称：发送多组数据
* 描述：向指定连接发送多组数据
*		TCP - 顺序发送所有数据包 
*		UDP - 把所有数据包组合成一个数据包发送（数据包的总长度不能大于置的 UDP 包最大长度） 
*		
* 参数：		dwConnID	-- 连接 ID
*			pBuffers	-- 发送缓冲区数组
*			iCount		-- 发送缓冲区数目
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_代理通信发送多组数据()
//@备注 向指定连接发送多组数据
HPSOCKET_API BOOL __HP_CALL HP_Agent_SendPackets(HP_Agent pAgent, HP_CONNID dwConnID, const WSABUF pBuffers[], int iCount);

/*
* 名称：暂停/恢复接收
* 描述：暂停/恢复某个连接的数据接收工作
*		
* 参数：		dwConnID	-- 连接 ID
*			bPause		-- TRUE - 暂停, FALSE - 恢复
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败
*/

//@备注 暂停/恢复某个连接的数据接收工作()
//@别名 HP_代理通信暂停或恢复接收()
HPSOCKET_API BOOL __HP_CALL HP_Agent_PauseReceive(HP_Agent pAgent, HP_CONNID dwConnID, BOOL bPause);

/*
* 名称：断开连接
* 描述：断开某个连接
*		
* 参数：		dwConnID	-- 连接 ID
*			bForce		-- 是否强制断开连接
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败
*/
//@别名 HP_代理通信断开连接()
//@备注 断开某个连接
HPSOCKET_API BOOL __HP_CALL HP_Agent_Disconnect(HP_Agent pAgent, HP_CONNID dwConnID, BOOL bForce);

/*
* 名称：断开超时连接
* 描述：断开超过指定时长的连接
*		
* 参数：		dwPeriod	-- 时长（毫秒）
*			bForce		-- 是否强制断开连接
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败
*/
//@别名 HP_代理通信断开超时连接()
//@备注 断开超过指定时长的连接
HPSOCKET_API BOOL __HP_CALL HP_Agent_DisconnectLongConnections(HP_Agent pAgent, DWORD dwPeriod, BOOL bForce);

/*
* 名称：断开静默连接
* 描述：断开超过指定时长的静默连接
*		
* 参数：		dwPeriod	-- 时长（毫秒）
*			bForce		-- 是否强制断开连接
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败
*/
//@别名 HP_代理通信断开静默连接()
//@备注 断开超过指定时长的静默连接
HPSOCKET_API BOOL __HP_CALL HP_Agent_DisconnectSilenceConnections(HP_Agent pAgent, DWORD dwPeriod, BOOL bForce);

/******************************************************************************/
/***************************** Agent 属性访问方法 *****************************/

/*
* 名称：置连接的附加数据
* 描述：是否为连接绑定附加数据或者绑定什么样的数据，均由应用程序只身决定
*		
* 参数：		dwConnID	-- 连接 ID
*			pv			-- 数据
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败（无效的连接 ID）
*/
//@别名 HP_代理通信置连接的附加数据()
//@备注 是否为连接绑定附加数据或者绑定什么样的数据，均由应用程序只身决定
HPSOCKET_API BOOL __HP_CALL HP_Agent_SetConnectionExtra(HP_Agent pAgent, HP_CONNID dwConnID, PVOID pExtra);

/*
* 名称：取连接的附加数据
* 描述：是否为连接绑定附加数据或者绑定什么样的数据，均由应用程序只身决定
*		
* 参数：		dwConnID	-- 连接 ID
*			ppv			-- 数据指针
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败（无效的连接 ID）
*/
//@别名 HP_代理通信取连接的附加数据()
//@备注 是否为连接绑定附加数据或者绑定什么样的数据，均由应用程序只身决定
HPSOCKET_API BOOL __HP_CALL HP_Agent_GetConnectionExtra(HP_Agent pAgent, HP_CONNID dwConnID, PVOID* ppExtra);

//@备注 检测是否为安全连接（SSL/HTTPS）
//@别名 HP_检测代理通信是否为安全连接()
HPSOCKET_API BOOL __HP_CALL HP_Agent_IsSecure(HP_Agent pAgent);
//@别名 HP_检查代理通信组件是否已启动()
HPSOCKET_API BOOL __HP_CALL HP_Agent_HasStarted(HP_Agent pAgent);
//@别名 HP_查看代理通信组件当前状态()
HPSOCKET_API En_HP_ServiceState __HP_CALL HP_Agent_GetState(HP_Agent pAgent);
//@别名 HP_取代理通信连接数()
HPSOCKET_API DWORD __HP_CALL HP_Agent_GetConnectionCount(HP_Agent pAgent);
//@别名 HP_取代理通信所有连接的HP_网络连接字符串()
HPSOCKET_API BOOL __HP_CALL HP_Agent_GetAllConnectionIDs(HP_Agent pAgent, HP_CONNID pIDs[], DWORD* pdwCount);
//@备注 取某个连接时长（毫秒)
//@别名 HP_取代理通信某个连接时长()
HPSOCKET_API BOOL __HP_CALL HP_Agent_GetConnectPeriod(HP_Agent pAgent, HP_CONNID dwConnID, DWORD* pdwPeriod);
//@备注 取某个连接静默时间（毫秒）
//@别名 HP_取代理通信某个连接静默时间()
HPSOCKET_API BOOL __HP_CALL HP_Agent_GetSilencePeriod(HP_Agent pAgent, HP_CONNID dwConnID, DWORD* pdwPeriod);
//@别名 HP_取代理通信某个连接的本地地址信息()
HPSOCKET_API BOOL __HP_CALL HP_Agent_GetLocalAddress(HP_Agent pAgent, HP_CONNID dwConnID, TCHAR lpszAddress[], int* piAddressLen, USHORT* pusPort);
//@别名 HP_取代理通信某个连接的远程地址信息()
HPSOCKET_API BOOL __HP_CALL HP_Agent_GetRemoteAddress(HP_Agent pAgent, HP_CONNID dwConnID, TCHAR lpszAddress[], int* piAddressLen, USHORT* pusPort);
//@别名 HP_取代理通信某个连接的远程主机信息()
HPSOCKET_API BOOL __HP_CALL HP_Agent_GetRemoteHost(HP_Agent pAgent, HP_CONNID dwConnID, TCHAR lpszHost[], int* piHostLen, USHORT* pusPort);
//@别名 HP_取代理通信最近一次失败操作的错误代码()
HPSOCKET_API En_HP_SocketError __HP_CALL HP_Agent_GetLastError(HP_Agent pAgent);
//@别名 HP_取代理通信最近一次失败操作的错误描述()
HPSOCKET_API LPCTSTR __HP_CALL HP_Agent_GetLastErrorDesc(HP_Agent pAgent);
//@别名 HP_取代理通信连接中未发出数据的长度()
HPSOCKET_API BOOL __HP_CALL HP_Agent_GetPendingDataLength(HP_Agent pAgent, HP_CONNID dwConnID, int* piPending);
//@别名 HP_取代理通信连接的数据接收状态()
HPSOCKET_API BOOL __HP_CALL HP_Agent_IsPauseReceive(HP_Agent pAgent, HP_CONNID dwConnID, BOOL* pbPaused);
//@别名 HP_代理通信检测是否有效连接()
HPSOCKET_API BOOL __HP_CALL HP_Agent_IsConnected(HP_Agent pAgent, HP_CONNID dwConnID);

//@备注 置地址重用选项
//@别名 HP_代理通信置地址重用选项()
HPSOCKET_API void __HP_CALL HP_Agent_SetReuseAddressPolicy(HP_Agent pAgent, En_HP_ReuseAddressPolicy enReusePolicy);
//@备注 置数据发送策略
//@别名 HP_代理通信置数据发送策略()
HPSOCKET_API void __HP_CALL HP_Agent_SetSendPolicy(HP_Agent pAgent, En_HP_SendPolicy enSendPolicy);
//@备注 置OnSend事件同步策略（默认：OSSP_NONE，不同步）
//@别名 HP_代理通信置OnSend事件同步策略()
HPSOCKET_API void __HP_CALL HP_Agent_SetOnSendSyncPolicy(HP_Agent pAgent, En_HP_OnSendSyncPolicy enSyncPolicy);
//@备注 置Socket缓存对象()锁定时间（毫秒，在锁定期间该 Socket 缓存对象()不能被取使用）
//@别名 HP_代理通信置网络套接字缓存对象()
HPSOCKET_API void __HP_CALL HP_Agent_SetFreeSocketObjLockTime(HP_Agent pAgent, DWORD dwFreeSocketObjLockTime);
//@备注 置Socket缓存池大小（通常置为平均并发连接数量的 1/3 - 1/2）
//@别名 HP_代理通信置网络套接字缓存池大小()
HPSOCKET_API void __HP_CALL HP_Agent_SetFreeSocketObjPool(HP_Agent pAgent, DWORD dwFreeSocketObjPool);
//@备注 置内存块缓存池大小（通常置为 Socket 缓存池大小的 2 - 3 倍）
//@别名 HP_代理通信置内存块缓存池大小()
HPSOCKET_API void __HP_CALL HP_Agent_SetFreeBufferObjPool(HP_Agent pAgent, DWORD dwFreeBufferObjPool);
//@备注 置Socket缓存池回收阀值（通常置为 Socket 缓存池大小的 3 倍）
//@别名 HP_代理通信置网络套接字缓存池回收阀值()
HPSOCKET_API void __HP_CALL HP_Agent_SetFreeSocketObjHold(HP_Agent pAgent, DWORD dwFreeSocketObjHold);
//@备注 置内存块缓存池回收阀值（通常置为内存块缓存池大小的 3 倍）
//@别名 HP_代理通信置内存块缓存池回收阀值()
HPSOCKET_API void __HP_CALL HP_Agent_SetFreeBufferObjHold(HP_Agent pAgent, DWORD dwFreeBufferObjHold);
//@备注 置最大连接数（组件会根据置值预分配内存，因此需要根据实际情况置，不宜过大）
//@别名 HP_代理通信置最大连接数()
HPSOCKET_API void __HP_CALL HP_Agent_SetMaxConnectionCount(HP_Agent pAgent, DWORD dwMaxConnectionCount);
//@备注 置工作线程数量（通常置为 2 * CPU + 2）
//@别名 HP_代理通信置工作线程数量()
HPSOCKET_API void __HP_CALL HP_Agent_SetWorkerThreadCount(HP_Agent pAgent, DWORD dwWorkerThreadCount);
//@备注 置是否标记静默时间（置为 TRUE 时 DisconnectSilenceConnections() 和 GetSilencePeriod() 才有效，默认：TRUE）\
//@别名 HP_代理通信置是否标记静默时间()
HPSOCKET_API void __HP_CALL HP_Agent_SetMarkSilence(HP_Agent pAgent, BOOL bMarkSilence);

//@别名 HP_取代理地址重用选项()
HPSOCKET_API En_HP_ReuseAddressPolicy __HP_CALL HP_Agent_GetReuseAddressPolicy(HP_Agent pAgent);
//@别名 HP_取代理数据发送策略()
HPSOCKET_API En_HP_SendPolicy __HP_CALL HP_Agent_GetSendPolicy(HP_Agent pAgent);
//@别名 HP_取代理OnSend事件同步策略()
HPSOCKET_API En_HP_OnSendSyncPolicy __HP_CALL HP_Agent_GetOnSendSyncPolicy(HP_Agent pAgent);
//@备注 取代理网络套接字缓存对象()锁定时间
//@别名 HP_代理通信取代理网络套接字缓存对象()
HPSOCKET_API DWORD __HP_CALL HP_Agent_GetFreeSocketObjLockTime(HP_Agent pAgent);
//@别名 HP_取代理网络套接字缓存池大小()
HPSOCKET_API DWORD __HP_CALL HP_Agent_GetFreeSocketObjPool(HP_Agent pAgent);
//@别名 HP_取代理内存块缓存池大小()
HPSOCKET_API DWORD __HP_CALL HP_Agent_GetFreeBufferObjPool(HP_Agent pAgent);
//@别名 HP_取代理网络套接字缓存池回收阀值()
HPSOCKET_API DWORD __HP_CALL HP_Agent_GetFreeSocketObjHold(HP_Agent pAgent);
//@别名 HP_取代理内存块缓存池回收阀值()
HPSOCKET_API DWORD __HP_CALL HP_Agent_GetFreeBufferObjHold(HP_Agent pAgent);
//@别名 HP_取代理最大连接数()
HPSOCKET_API DWORD __HP_CALL HP_Agent_GetMaxConnectionCount(HP_Agent pAgent);
//@别名 HP_取代理工作线程数量()
HPSOCKET_API DWORD __HP_CALL HP_Agent_GetWorkerThreadCount(HP_Agent pAgent);
//@别名 HP_检测代理是否标记静默时间()
HPSOCKET_API BOOL __HP_CALL HP_Agent_IsMarkSilence(HP_Agent pAgent);

/**********************************************************************************/
/******************************* TCP Agent 操作方法 *******************************/

/*
* 名称：发送小文件
* 描述：向指定连接发送 4096 KB 以下的小文件
*		
* 参数：		dwConnID		-- 连接 ID
*			lpszFileName	-- 文件路径
*			pHead			-- 头部附加数据
*			pTail			-- 尾部附加数据
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_Tcp代理发送小文件()
//@备注 向指定连接发送4096 KB以下的小文件
HPSOCKET_API BOOL __HP_CALL HP_TcpAgent_SendSmallFile(HP_Agent pAgent, HP_CONNID dwConnID, LPCTSTR lpszFileName, const LPWSABUF pHead, const LPWSABUF pTail);

/**********************************************************************************/
/***************************** TCP Agent 属性访问方法 *****************************/

//@备注 Tcp代理置通信数据缓冲区大小（根据平均通信数据包大小调整Tcp代理置，通常Tcp代理置为 1024 的倍数）
//@别名 HP_Tcp代理置通信数据缓冲区大小()
HPSOCKET_API void __HP_CALL HP_TcpAgent_SetSocketBufferSize(HP_TcpAgent pAgent, DWORD dwSocketBufferSize);
//@备注 Tcp代理置正常心跳包间隔（毫秒，0 则不发送心跳包，默认：60 * 1000）
//@别名 HP_Tcp代理置正常心跳包间隔()
HPSOCKET_API void __HP_CALL HP_TcpAgent_SetKeepAliveTime(HP_TcpAgent pAgent, DWORD dwKeepAliveTime);
//@备注 Tcp代理置异常心跳包间隔（毫秒，0 不发送心跳包，，默认：20 * 1000，如果超过若干次 [默认：WinXP 5 次, Win7 10 次] 检测不到心跳确认包则认为已断线）
//@别名 HP_Tcp代理置异常心跳包间隔()
HPSOCKET_API void __HP_CALL HP_TcpAgent_SetKeepAliveInterval(HP_TcpAgent pAgent, DWORD dwKeepAliveInterval);
//@备注 Tcp代理置是否开启 nodelay 模式（默认：FALSE，不开启）
//@别名 HP_Tcp代理置是否开启无延时模式()
HPSOCKET_API void __HP_CALL HP_TcpAgent_SetNoDelay(HP_TcpAgent pAgent, BOOL bNoDelay);

//@别名 HP_Tcp代理取通信数据缓冲区大小()
HPSOCKET_API DWORD __HP_CALL HP_TcpAgent_GetSocketBufferSize(HP_TcpAgent pAgent);
//@别名 HP_Tcp代理取正常心跳包间隔()
HPSOCKET_API DWORD __HP_CALL HP_TcpAgent_GetKeepAliveTime(HP_TcpAgent pAgent);
//@别名 HP_Tcp代理取异常心跳包间隔()
HPSOCKET_API DWORD __HP_CALL HP_TcpAgent_GetKeepAliveInterval(HP_TcpAgent pAgent);
//@别名 HP_Tcp代理检查是否开启无延时模式()
HPSOCKET_API BOOL __HP_CALL HP_TcpAgent_IsNoDelay(HP_TcpAgent pAgent);

/******************************************************************************/
/***************************** Client 组件操作方法 *****************************/

/*
* 名称：启动通信组件
* 描述：启动客户端通信组件并连接服务端，启动完成后可开始收发数据
*		
* 参数：		lpszRemoteAddress	-- 服务端地址
*			usPort				-- 服务端端口
*			bAsyncConnect		-- 是否采用异步 Connect
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 HP_Client_GetLastError() 取错误代码
*/
//@别名 HP_启动客户端通信组件()
HPSOCKET_API BOOL __HP_CALL HP_Client_Start(HP_Client pClient, LPCTSTR lpszRemoteAddress, USHORT usPort, BOOL bAsyncConnect);

/*
* 名称：启动通信组件（并指定绑定地址）
* 描述：启动客户端通信组件并连接服务端，启动完成后可开始收发数据
*		
* 参数：		lpszRemoteAddress	-- 服务端地址
*			usPort				-- 服务端端口
*			bAsyncConnect		-- 是否采用异步 Connect
*			lpszBindAddress		-- 绑定地址（默认：nullptr，TcpClient/UdpClient -> 不执行绑定操作，UdpCast 绑定 -> 任意地址）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 HP_Client_GetLastError() 取错误代码
*/
//@别名 HP_启动可绑定地址客户端通信组件()
HPSOCKET_API BOOL __HP_CALL HP_Client_StartWithBindAddress(HP_Client pClient, LPCTSTR lpszRemoteAddress, USHORT usPort, BOOL bAsyncConnect, LPCTSTR lpszBindAddress);

/*
* 名称：启动通信组件（并指定绑定地址）
* 描述：启动客户端通信组件并连接服务端，启动完成后可开始收发数据
*		
* 参数：		lpszRemoteAddress	-- 服务端地址
*			usPort				-- 服务端端口
*			bAsyncConnect		-- 是否采用异步 Connect
*			lpszBindAddress		-- 绑定地址（默认：nullptr，TcpClient/UdpClient -> 不执行绑定操作，UdpCast 绑定 -> 任意地址）
*			usLocalPort			-- 本地端口（默认：0）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 HP_Client_GetLastError() 取错误代码
*/
//@别名 HP_启动可绑定地址和本地端口客户端通信组件()
HPSOCKET_API BOOL __HP_CALL HP_Client_StartWithBindAddressAndLocalPort(HP_Client pClient, LPCTSTR lpszRemoteAddress, USHORT usPort, BOOL bAsyncConnect, LPCTSTR lpszBindAddress, USHORT usLocalPort);

/*
* 名称：关闭通信组件
* 描述：关闭客户端通信组件，关闭完成后断开与服务端的连接并释放所有资源
*		
* 参数：	
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 HP_Client_GetLastError() 取错误代码
*/
//@别名 HP_关闭客户端通信组件()
HPSOCKET_API BOOL __HP_CALL HP_Client_Stop(HP_Client pClient);

/*
* 名称：发送数据
* 描述：向服务端发送数据
*		
* 参数：		pBuffer		-- 发送缓冲区
*			iLength		-- 发送缓冲区长度
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_客户端发送数据()
HPSOCKET_API BOOL __HP_CALL HP_Client_Send(HP_Client pClient, const BYTE* pBuffer, int iLength);

/*
* 名称：发送数据
* 描述：向服务端发送数据
*		
* 参数：		pBuffer		-- 发送缓冲区
*			iLength		-- 发送缓冲区长度
*			iOffset		-- 发送缓冲区指针偏移量
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_客户端发送数据Part()
HPSOCKET_API BOOL __HP_CALL HP_Client_SendPart(HP_Client pClient, const BYTE* pBuffer, int iLength, int iOffset);

/*
* 名称：发送多组数据
* 描述：向服务端发送多组数据
*		TCP - 顺序发送所有数据包 
*		UDP - 把所有数据包组合成一个数据包发送（数据包的总长度不能大于Tcp代理置的 UDP 包最大长度） 
*		
* 参数：		pBuffers	-- 发送缓冲区数组
*			iCount		-- 发送缓冲区数目
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_客户端发送多组数据()
HPSOCKET_API BOOL __HP_CALL HP_Client_SendPackets(HP_Client pClient, const WSABUF pBuffers[], int iCount);

/*
* 名称：暂停/恢复接收
* 描述：暂停/恢复某个连接的数据接收工作
*		
*			bPause	-- TRUE - 暂停, FALSE - 恢复
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败
*/
//@别名 HP_客户端暂停或者恢复接收()
HPSOCKET_API BOOL __HP_CALL HP_Client_PauseReceive(HP_Client pClient, BOOL bPause);

/*
* 名称：等待
* 描述：等待通信组件停止运行
*		
* 参数：		dwMilliseconds	-- 超时时间（毫秒，默认：-1，永不超时）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取错误代码
*/
//@别名 HP_客户端等待()
HPSOCKET_API BOOL __HP_CALL HP_Client_Wait(HP_Client pClient, DWORD dwMilliseconds);

/******************************************************************************/
/***************************** Client 属性访问方法 *****************************/

//@别名 HP_置客户端连接的附加数据()
HPSOCKET_API void __HP_CALL HP_Client_SetExtra(HP_Client pClient, PVOID pExtra);
//@别名 HP_取客户端连接的附加数据()
HPSOCKET_API PVOID __HP_CALL HP_Client_GetExtra(HP_Client pClient);

//@备注 检测客户端是否为安全连接（SSL/HTTPS）
//@别名 HP_检测客户端是否为安全连接()
HPSOCKET_API BOOL __HP_CALL HP_Client_IsSecure(HP_Client pClient);
//@别名 HP_检查客户端通信组件是否已启动()
HPSOCKET_API BOOL __HP_CALL HP_Client_HasStarted(HP_Client pClient);
//@别名 HP_查看客户端通信组件当前状态()
HPSOCKET_API En_HP_ServiceState	__HP_CALL HP_Client_GetState(HP_Client pClient);
//@别名 HP_取客户端最近一次失败操作的错误代码()
HPSOCKET_API En_HP_SocketError	__HP_CALL HP_Client_GetLastError(HP_Client pClient);
//@别名 HP_取客户端最近一次失败操作的错误描述()
HPSOCKET_API LPCTSTR __HP_CALL HP_Client_GetLastErrorDesc(HP_Client pClient);
//@备注 取客户端该组件对象()的连接ID
//@别名 HP_取客户端组件对象的连接ID()
HPSOCKET_API HP_CONNID __HP_CALL HP_Client_GetConnectionID(HP_Client pClient);
//@别名 HP_取客户端网络套接字的地址信息()
HPSOCKET_API BOOL __HP_CALL HP_Client_GetLocalAddress(HP_Client pClient, TCHAR lpszAddress[], int* piAddressLen, USHORT* pusPort);
//@别名 HP_取客户端连接的远程主机信息()
HPSOCKET_API BOOL __HP_CALL HP_Client_GetRemoteHost(HP_Client pClient, TCHAR lpszHost[], int* piHostLen, USHORT* pusPort);
//@别名 HP_取客户端连接中未发出数据的长度()
HPSOCKET_API BOOL __HP_CALL HP_Client_GetPendingDataLength(HP_Client pClient, int* piPending);
//@别名 HP_取客户端连接的数据接收状态()
HPSOCKET_API BOOL __HP_CALL HP_Client_IsPauseReceive(HP_Client pClient, BOOL* pbPaused);
//@别名 HP_检测客户端是否有效连接()
HPSOCKET_API BOOL __HP_CALL HP_Client_IsConnected(HP_Client pClient);

//@备注 置地址重用选项
//@别名 HP_置客户端地址重用选项()
HPSOCKET_API void __HP_CALL HP_Client_SetReuseAddressPolicy(HP_Client pClient, En_HP_ReuseAddressPolicy enReusePolicy);
//@备注 置内存块缓存池大小（通常Tcp代理置为 -> PUSH 模型：5 - 10；PULL 模型：10 - 20 ）
//@别名 HP_置客户端内存块缓存池大小()
HPSOCKET_API void __HP_CALL HP_Client_SetFreeBufferPoolSize(HP_Client pClient, DWORD dwFreeBufferPoolSize);
//@备注 置内存块缓存池回收阀值（通常Tcp代理置为内存块缓存池大小的 3 倍）
//@别名 HP_置客户端内存块缓存池回收阀值()
HPSOCKET_API void __HP_CALL HP_Client_SetFreeBufferPoolHold(HP_Client pClient, DWORD dwFreeBufferPoolHold);

//@别名 HP_取客户端地址重用选项()
HPSOCKET_API En_HP_ReuseAddressPolicy __HP_CALL HP_Client_GetReuseAddressPolicy(HP_Client pClient);
//@别名 HP_取客户端内存块缓存池大小()
HPSOCKET_API DWORD __HP_CALL HP_Client_GetFreeBufferPoolSize(HP_Client pClient);
//@别名 HP_取客户端内存块缓存池回收阀值()
HPSOCKET_API DWORD __HP_CALL HP_Client_GetFreeBufferPoolHold(HP_Client pClient);

/**********************************************************************************/
/******************************* TCP Client 操作方法 *******************************/

/*
* 名称：发送小文件
* 描述：向服务端发送 4096 KB 以下的小文件
*		
* 参数：		lpszFileName	-- 文件路径
*			pHead			-- 头部附加数据
*			pTail			-- 尾部附加数据
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取 Windows 错误代码
*/
//@别名 HP_TCP客户端发送小文件()
//@备注 向服务端发送4096KB以下的小文件
HPSOCKET_API BOOL __HP_CALL HP_TcpClient_SendSmallFile(HP_Client pClient, LPCTSTR lpszFileName, const LPWSABUF pHead, const LPWSABUF pTail);

/**********************************************************************************/
/***************************** TCP Client 属性访问方法 *****************************/

//@备注 置通信数据缓冲区大小（根据平均通信数据包大小调整，通常为：(N * 1024) - sizeof(TBufferObj)）
//@别名 HP_置TCP客户端通信数据缓冲区大小()
HPSOCKET_API void __HP_CALL HP_TcpClient_SetSocketBufferSize(HP_TcpClient pClient, DWORD dwSocketBufferSize);
//@备注 置正常心跳包间隔（毫秒，0 则不发送心跳包，默认：60 * 1000）
//@别名 HP_置TCP客户端正常心跳包间隔()
HPSOCKET_API void __HP_CALL HP_TcpClient_SetKeepAliveTime(HP_TcpClient pClient, DWORD dwKeepAliveTime);
//@备注 置异常心跳包间隔（毫秒，0 不发送心跳包，，默认：20 * 1000，如果超过若干次 [默认：WinXP 5 次, Win7 10 次] 检测不到心跳确认包则认为已断线）
//@别名 HP_置TCP客户端异常心跳包间隔()
HPSOCKET_API void __HP_CALL HP_TcpClient_SetKeepAliveInterval(HP_TcpClient pClient, DWORD dwKeepAliveInterval);
//@备注 置是否开启 nodelay 模式（默认：FALSE，不开启）
//@别名 HP_置TCP客户端是否开启无延时模式()
HPSOCKET_API void __HP_CALL HP_TcpClient_SetNoDelay(HP_TcpClient pClient, BOOL bNoDelay);

//@别名 HP_取Tcp客户端通信数据缓冲区大小()
HPSOCKET_API DWORD __HP_CALL HP_TcpClient_GetSocketBufferSize(HP_TcpClient pClient);
//@别名 HP_取Tcp客户端正常心跳包间隔()
HPSOCKET_API DWORD __HP_CALL HP_TcpClient_GetKeepAliveTime(HP_TcpClient pClient);
//@别名 HP_取Tcp客户端异常心跳包间隔()
HPSOCKET_API DWORD __HP_CALL HP_TcpClient_GetKeepAliveInterval(HP_TcpClient pClient);
//@备注 HP_检查Tcp客户端是否开启无延时模式
//@别名 HP_检查Tcp客户端是否开启无延时模式()
HPSOCKET_API BOOL __HP_CALL HP_TcpClient_IsNoDelay(HP_TcpClient pClient);

#ifdef _UDP_SUPPORT

/**********************************************************************************/
/***************************** UDP Client 属性访问方法 *****************************/

//@备注 置数据报文最大长度（建议在局域网环境下不超过 1432 字节，在广域网环境下不超过 548 字节）
//@别名 HP_置UDP客户端数据报文最大长度()
HPSOCKET_API void __HP_CALL HP_UdpClient_SetMaxDatagramSize(HP_UdpClient pClient, DWORD dwMaxDatagramSize);
//@备注 取数据报文最大长度
//@别名 HP_取UDP客户端数据报文最大长度()
HPSOCKET_API DWORD __HP_CALL HP_UdpClient_GetMaxDatagramSize(HP_UdpClient pClient);

//@备注 置监测包尝试次数（0 则不发送监测跳包，如果超过最大尝试次数则认为已断线）
//@别名 HP_置UDP客户端监测包尝试次数()
HPSOCKET_API void __HP_CALL HP_UdpClient_SetDetectAttempts(HP_UdpClient pClient, DWORD dwDetectAttempts);
//@备注 置监测包发送间隔（毫秒，0 不发送监测包）
//@别名 HP_置UDP客户端监测包发送间隔()
HPSOCKET_API void __HP_CALL HP_UdpClient_SetDetectInterval(HP_UdpClient pClient, DWORD dwDetectInterval);
//@备注 取心跳检查次数
//@别名 HP_取UDP客户端心跳检查次数()
HPSOCKET_API DWORD __HP_CALL HP_UdpClient_GetDetectAttempts(HP_UdpClient pClient);
//@备注 取心跳检查间隔
//@别名 HP_取UDP客户端心跳检查间隔()
HPSOCKET_API DWORD __HP_CALL HP_UdpClient_GetDetectInterval(HP_UdpClient pClient);
/**********************************************************************************/
/*************************** UDP ARQ Client 属性访问方法 ***************************/

//@备注 置是否开启 nodelay 模式（默认：FALSE，不开启）
//@别名 HP_置UDP网络自动重发客户端是否开启无延时模式()
HPSOCKET_API void __HP_CALL HP_UdpArqClient_SetNoDelay(HP_UdpArqClient pClient, BOOL bNoDelay);
//@备注 置是否关闭拥塞控制（默认：FALSE，不关闭）
//@别名 HP_置UDP网络自动重发客户端是否关闭拥塞控制()
HPSOCKET_API void __HP_CALL HP_UdpArqClient_SetTurnoffCongestCtrl(HP_UdpArqClient pClient, BOOL bTurnOff);
//@备注 置数据刷新间隔（毫秒，默认：60）
//@别名 HP_置UDP网络自动重发客户端数据刷新间隔()
HPSOCKET_API void __HP_CALL HP_UdpArqClient_SetFlushInterval(HP_UdpArqClient pClient, DWORD dwFlushInterval);
//@备注 置快速重传 ACK 跨越次数（默认：0，关闭快速重传）
//@别名 HP_置UDP网络自动重发客户端快速重传ACK跨越次数()
HPSOCKET_API void __HP_CALL HP_UdpArqClient_SetResendByAcks(HP_UdpArqClient pClient, DWORD dwResendByAcks);
//@备注 置发送窗口大小（数据包数量，默认：128）
//@别名 HP_置UDP网络自动重发客户端置发送窗口大小()
HPSOCKET_API void __HP_CALL HP_UdpArqClient_SetSendWndSize(HP_UdpArqClient pClient, DWORD dwSendWndSize);
//@备注 置接收窗口大小（数据包数量，默认：512）
//@别名 HP_置UDP网络自动重发客户端接收窗口大小()
HPSOCKET_API void __HP_CALL HP_UdpArqClient_SetRecvWndSize(HP_UdpArqClient pClient, DWORD dwRecvWndSize);
//@备注 置最小重传超时时间（毫秒，默认：30）
//@别名 HP_置UDP网络自动重发客户端最小重传超时时间()
HPSOCKET_API void __HP_CALL HP_UdpArqClient_SetMinRto(HP_UdpArqClient pClient, DWORD dwMinRto);
//@备注 置快速握手次数限制（默认：5，如果为 0 则不限制）
//@别名 HP_置UDP网络自动重发客户端置快速握手次数限制()
HPSOCKET_API void __HP_CALL HP_UdpArqClient_SetFastLimit(HP_UdpArqClient pClient, DWORD dwFastLimit);
//@备注 置最大传输单元（默认：0，与 SetMaxDatagramSize() 一致）
//@别名 HP_置UDP网络自动重发客户端最大传输单元()
HPSOCKET_API void __HP_CALL HP_UdpArqClient_SetMaxTransUnit(HP_UdpArqClient pClient, DWORD dwMaxTransUnit);
//@备注 置最大数据包大小（默认：4096）
//@别名 HP_置UDP网络自动重发客户端大数据包大小()
HPSOCKET_API void __HP_CALL HP_UdpArqClient_SetMaxMessageSize(HP_UdpArqClient pClient, DWORD dwMaxMessageSize);
//@备注 置握手超时时间（毫秒，默认：5000）
//@别名 HP_置UDP网络自动重发客户端握手超时时间()
HPSOCKET_API void __HP_CALL HP_UdpArqClient_SetHandShakeTimeout(HP_UdpArqClient pClient, DWORD dwHandShakeTimeout);

//@备注 检测是否开启 nodelay 模式
//@别名 HP_检测UDP网络自动重发客户端是否开启无延时模式()
HPSOCKET_API BOOL __HP_CALL HP_UdpArqClient_IsNoDelay(HP_UdpArqClient pClient);
//@备注 检测是否关闭拥塞控制
//@别名 HP_检测取是否关闭拥塞控制()
HPSOCKET_API BOOL __HP_CALL HP_UdpArqClient_IsTurnoffCongestCtrl(HP_UdpArqClient pClient);
//@备注 取数据刷新间隔
//@别名 HP_取UDP网络自动重发客户端数据刷新间隔()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqClient_GetFlushInterval(HP_UdpArqClient pClient);
//@备注 取快速重传 ACK 跨越次数
//@别名 HP_取UDP网络自动重发客户端快速重传ACK跨越次数()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqClient_GetResendByAcks(HP_UdpArqClient pClient);
//@备注 取发送窗口大小
//@别名 HP_取UDP网络自动重发客户端发送窗口大小()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqClient_GetSendWndSize(HP_UdpArqClient pClient);
//@备注 取接收窗口大小
//@别名 HP_取UDP网络自动重发客户端接收窗口大小()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqClient_GetRecvWndSize(HP_UdpArqClient pClient);
//@备注 取最小重传超时时间
//@别名 HP_取UDP网络自动重发客户端最小重传超时时间()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqClient_GetMinRto(HP_UdpArqClient pClient);
//@备注 取快速握手次数限制
//@别名 HP_取UDP网络自动重发客户端快速握手次数限制()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqClient_GetFastLimit(HP_UdpArqClient pClient);
//@备注 取最大传输单元
//@别名 HP_取UDP网络自动重发客户端最大传输单元()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqClient_GetMaxTransUnit(HP_UdpArqClient pClient);
//@备注 取最大数据包大小
//@别名 HP_取UDP网络自动重发客户端最大数据包大小()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqClient_GetMaxMessageSize(HP_UdpArqClient pClient);
//@备注 取握手超时时间
//@别名 HP_取UDP网络自动重发客户端握手超时时间()
HPSOCKET_API DWORD __HP_CALL HP_UdpArqClient_GetHandShakeTimeout(HP_UdpArqClient pClient);

//@备注 取等待发送包数量
//@别名 HP_取UDP网络自动重发客户端等待发送包数量()
HPSOCKET_API BOOL __HP_CALL HP_UdpArqClient_GetWaitingSendMessageCount(HP_UdpArqClient pClient, int* piCount);

/**********************************************************************************/
/****************************** UDP Cast 属性访问方法 ******************************/

//@备注 置数据报文最大长度（建议在局域网环境下不超过 1432 字节，在广域网环境下不超过 548 字节）
//@别名 HP_置UDPCast数据报文最大长度()
HPSOCKET_API void __HP_CALL HP_UdpCast_SetMaxDatagramSize(HP_UdpCast pCast, DWORD dwMaxDatagramSize);
//@备注 取数据报文最大长度
//@别名 HP_取UDPCast数据报文最大长度()
HPSOCKET_API DWORD __HP_CALL HP_UdpCast_GetMaxDatagramSize(HP_UdpCast pCast);
//@备注 取当前数据报的远程地址信息（通常在 OnReceive 事件中调用）
//@别名 HP_取UDPCast当前数据报的远程地址信息()
HPSOCKET_API BOOL __HP_CALL HP_UdpCast_GetRemoteAddress(HP_UdpCast pCast, TCHAR lpszAddress[], int* piAddressLen, USHORT* pusPort);
//@备注 置传播模式（组播或广播）
//@别名 HP_置UDPCast传播模式()
HPSOCKET_API void __HP_CALL HP_UdpCast_SetCastMode(HP_UdpCast pCast, En_HP_CastMode enCastMode);
//@备注 取传播模式
//@别名 HP_取UDPCast传播模式()
HPSOCKET_API En_HP_CastMode __HP_CALL HP_UdpCast_GetCastMode(HP_UdpCast pCast);
//@备注 置组播报文的 TTL（0 - 255）
//@别名 HP_置UDPCast组播报文的TTL()
HPSOCKET_API void __HP_CALL HP_UdpCast_SetMultiCastTtl(HP_UdpCast pCast, int iMCTtl);
//@备注 取组播报文的 TTL
//@别名 HP_取UDPCast组播报文的TTL()
HPSOCKET_API int __HP_CALL HP_UdpCast_GetMultiCastTtl(HP_UdpCast pCast);
//@备注 置是否启用组播环路（TRUE or FALSE）
//@别名 HP_置UDPCast是否启用组播环路()
HPSOCKET_API void __HP_CALL HP_UdpCast_SetMultiCastLoop(HP_UdpCast pCast, BOOL bMCLoop);
//@备注 检测是否启用组播环路
//@别名 HP_检测UDPCast是否启用组播环路()
HPSOCKET_API BOOL __HP_CALL HP_UdpCast_IsMultiCastLoop(HP_UdpCast pCast);

/**********************************************************************************/
/****************************** UDP Node 组件操作方法 ******************************/

/*
* 名称：启动通信组件
* 描述：启动 UDP 节点通信组件，启动完成后可开始收发数据
*		
* 参数：		lpszBindAddress		-- 绑定地址（默认：nullptr，绑定任意地址）
*			usPort				-- 本地端口（默认：0）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 GetLastError() 取错误代码
*/
//@别名 HP_UDP启动节点通信组件()
HPSOCKET_API BOOL __HP_CALL HP_UdpNode_Start(HP_UdpNode pNode, LPCTSTR lpszBindAddress, USHORT usPort);

/*
* 名称：启动通信组件
* 描述：启动 UDP 节点通信组件，启动完成后可开始收发数据
*		
* 参数：	lpszBindAddress		-- 绑定地址（默认：nullptr，绑定任意地址）
*			usPort				-- 本地端口（默认：0）
*			enCastMode			-- 传播模式（默认：CM_UNICAST）
*			lpszCastAddress		-- 传播地址（默认：nullptr，当 enCaseMode 为 CM_MULTICAST 或 CM_BROADCAST 时有效）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 GetLastError() 取错误代码
*/
//@别名 HP_UDP启动节点通信组件Cast()
HPSOCKET_API BOOL __HP_CALL HP_UdpNode_StartWithCast(HP_UdpNode pNode, LPCTSTR lpszBindAddress, USHORT usPort, En_HP_CastMode enCastMode, LPCTSTR lpszCastAddress);

/*
* 名称：关闭通信组件
* 描述：关闭 UDP 节点通信组件，关闭完成后释放所有资源
*		
* 参数：	
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 GetLastError() 取错误代码
*/
//@别名 HP_UDP关闭通信组件()
HPSOCKET_API BOOL __HP_CALL HP_UdpNode_Stop(HP_UdpNode pNode);

/*
* 名称：等待
* 描述：等待通信组件停止运行
*		
* 参数：		dwMilliseconds	-- 超时时间（毫秒，默认：-1，永不超时）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取错误代码
*/
//@别名 HP_UDP等待()
HPSOCKET_API BOOL __HP_CALL HP_UdpNode_Wait(HP_UdpNode pNode, DWORD dwMilliseconds);

/*
* 名称：发送数据
* 描述：向指定地址发送数据
*		
* 参数：		lpszRemoteAddress	-- 远程地址
*			usRemotePort		-- 远程端口
*			pBuffer				-- 发送缓冲区
*			iLength				-- 发送缓冲区长度
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取错误代码
*/
//@别名 HP_UDP发送数据()
HPSOCKET_API BOOL __HP_CALL HP_UdpNode_Send(HP_UdpNode pNode, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pBuffer, int iLength);

/*
* 名称：发送数据
* 描述：向指定地址发送数据
*		
* 参数：		lpszRemoteAddress	-- 远程地址
*			usRemotePort		-- 远程端口
*			pBuffer				-- 发送缓冲区
*			iLength				-- 发送缓冲区长度
*			iOffset				-- 发送缓冲区指针偏移量
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取错误代码
*/
//@别名 HP_UDP发送数据Part()
HPSOCKET_API BOOL __HP_CALL HP_UdpNode_SendPart(HP_UdpNode pNode, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pBuffer, int iLength, int iOffset);

/*
* 名称：发送多组数据
* 描述：向指定地址发送多组数据，把所有数据包组合成一个数据包发送（数据包的总长度不能大于置的 UDP 包最大长度） 
*		
* 参数：		lpszRemoteAddress	-- 远程地址
*			usRemotePort		-- 远程端口
*			pBuffers			-- 发送缓冲区数组
*			iCount				-- 发送缓冲区数目
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取错误代码
*/
//@别名 HP_UDP发送多组数据()
HPSOCKET_API BOOL __HP_CALL HP_UdpNode_SendPackets(HP_UdpNode pNode, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const WSABUF pBuffers[], int iCount);

/*
* 名称：发送数据
* 描述：向传播地址发送数据
*		
* 参数：		pBuffer		-- 发送缓冲区
*			iLength		-- 发送缓冲区长度
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取错误代码
*/
//@别名 HP_UDP发送数据Cast()
HPSOCKET_API BOOL __HP_CALL HP_UdpNode_SendCast(HP_UdpNode pNode, const BYTE* pBuffer, int iLength);

/*
* 名称：发送数据
* 描述：向传播地址发送数据
*		
* 参数：		pBuffer		-- 发送缓冲区
*			iLength		-- 发送缓冲区长度
*			iOffset		-- 发送缓冲区指针偏移量
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取错误代码
*/
//@别名 HP_UDP发送数据CastPart()
HPSOCKET_API BOOL __HP_CALL HP_UdpNode_SendCastPart(HP_UdpNode pNode, const BYTE* pBuffer, int iLength, int iOffset);

/*
* 名称：发送多组数据
* 描述：向传播地址发送多组数据，把所有数据包组合成一个数据包发送（数据包的总长度不能大于置的 UDP 包最大长度） 
*		
* 参数：		pBuffers	-- 发送缓冲区数组
*			iCount		-- 发送缓冲区数目
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取错误代码
*/
//@别名 HP_UDP发送多组数据Cast()
HPSOCKET_API BOOL __HP_CALL HP_UdpNode_SendCastPackets(HP_UdpNode pNode, const WSABUF pBuffers[], int iCount);

/**********************************************************************************/
/****************************** UDP Node 属性访问方法 ******************************/

//@别名 HP_置UDP节点附加数据()
HPSOCKET_API void __HP_CALL HP_UdpNode_SetExtra(HP_UdpNode pNode, PVOID pExtra);

//@别名 HP_取UPD节点附加数据()
HPSOCKET_API PVOID __HP_CALL HP_UdpNode_GetExtra(HP_UdpNode pNode);
//@别名 HP_检查UPD节点通信组件是否已启动()
HPSOCKET_API BOOL __HP_CALL HP_UdpNode_HasStarted(HP_UdpNode pNode);
//@别名 HP_查看UPD节点通信组件当前状态()
HPSOCKET_API En_HP_ServiceState __HP_CALL HP_UdpNode_GetState(HP_UdpNode pNode);
//@别名 HP_取UPD节点最近一次失败操作的错误代码()
HPSOCKET_API En_HP_SocketError __HP_CALL HP_UdpNode_GetLastError(HP_UdpNode pNode);
//@别名 HP_取UPD节点最近一次失败操作的错误描述()
HPSOCKET_API LPCTSTR __HP_CALL HP_UdpNode_GetLastErrorDesc(HP_UdpNode pNode);
//@别名 HP_取UPD节点本节点地址()
HPSOCKET_API BOOL __HP_CALL HP_UdpNode_GetLocalAddress(HP_UdpNode pNode, TCHAR lpszAddress[], int* piAddressLen, USHORT* pusPort);
//@别名 HP_取UPD节点本节点传播地址()
HPSOCKET_API BOOL __HP_CALL HP_UdpNode_GetCastAddress(HP_UdpNode pNode, TCHAR lpszAddress[], int* piAddressLen, USHORT* pusPort);
//@别名 HP_取UPD节点传播模式()
HPSOCKET_API En_HP_CastMode __HP_CALL HP_UdpNode_GetCastMode(HP_UdpNode pNode);
//@别名 HP_取UPD节点未发出数据的长度()
HPSOCKET_API BOOL __HP_CALL HP_UdpNode_GetPendingDataLength(HP_UdpNode pNode, int* piPending);

//@备注 置数据报文最大长度（建议在局域网环境下不超过 1432 字节，在广域网环境下不超过 548 字节）
//@别名 HP_置UPD节点数据报文最大长度()
HPSOCKET_API void __HP_CALL HP_UdpNode_SetMaxDatagramSize(HP_UdpNode pNode, DWORD dwMaxDatagramSize);
/* 取数据报文最大长度 */
//@别名 HP_取UPD节点数据报文最大长度()
HPSOCKET_API DWORD __HP_CALL HP_UdpNode_GetMaxDatagramSize(HP_UdpNode pNode);

//@备注 置组播报文的TTL（0 - 255）
//@别名 HP_置UPD节点组播报文的TTL()
HPSOCKET_API void __HP_CALL HP_UdpNode_SetMultiCastTtl(HP_UdpNode pNode, int iMCTtl);
/* 取组播报文的 TTL */
//@别名 HP_取UPD节点组播报文的TTL()
HPSOCKET_API int __HP_CALL HP_UdpNode_GetMultiCastTtl(HP_UdpNode pNode);

//@备注 置是否启用组播环路（TRUE or FALSE）
//@别名 HP_置UPD节点是否启用组播环路()
HPSOCKET_API void __HP_CALL HP_UdpNode_SetMultiCastLoop(HP_UdpNode pNode, BOOL bMCLoop);
/* 检测是否启用组播环路 */
//@别名 HP_检测UPD节点是否启用组播环路()
HPSOCKET_API BOOL __HP_CALL HP_UdpNode_IsMultiCastLoop(HP_UdpNode pNode);

/* 置地址重用选项 */
//@别名 HP_置UPD节点地址重用选项()
HPSOCKET_API void __HP_CALL HP_UdpNode_SetReuseAddressPolicy(HP_UdpNode pNode, En_HP_ReuseAddressPolicy enReusePolicy);
//@备注 置工作线程数量（通常置为 2 * CPU + 2）
//@别名 HP_置UPD节点工作线程数量()
HPSOCKET_API void __HP_CALL HP_UdpNode_SetWorkerThreadCount(HP_UdpNode pNode, DWORD dwWorkerThreadCount);
//@备注 置 Receive 预投递数量（根据负载调整置，Receive 预投递数量越大则丢包概率越小） 
//@别名 HP_置UPD节点接收预投递数量()
HPSOCKET_API void __HP_CALL HP_UdpNode_SetPostReceiveCount(HP_UdpNode pNode, DWORD dwPostReceiveCount);
//@别名 HP_置UDP节点内存块缓存池大小()
HPSOCKET_API void __HP_CALL HP_UdpNode_SetFreeBufferPoolSize(HP_UdpNode pNode, DWORD dwFreeBufferPoolSize);
//@别名 HP_置UDP节点内存块缓存池回收阀值()
HPSOCKET_API void __HP_CALL HP_UdpNode_SetFreeBufferPoolHold(HP_UdpNode pNode, DWORD dwFreeBufferPoolHold);
//@别名 HP_取UDP节点地址重用选项()
HPSOCKET_API En_HP_ReuseAddressPolicy __HP_CALL HP_UdpNode_GetReuseAddressPolicy(HP_UdpNode pNode);
//@别名 HP_取UDP节点工作线程数量()
HPSOCKET_API DWORD __HP_CALL HP_UdpNode_GetWorkerThreadCount(HP_UdpNode pNode);
//@别名 HP_取UDP节点接收预投递数量()
HPSOCKET_API DWORD __HP_CALL HP_UdpNode_GetPostReceiveCount(HP_UdpNode pNode);
//@别名 HP_取UDP节点内存块缓存池大小()
HPSOCKET_API DWORD __HP_CALL HP_UdpNode_GetFreeBufferPoolSize(HP_UdpNode pNode);
//@别名 HP_取UDP节点内存块缓存池回收阀值()
HPSOCKET_API DWORD __HP_CALL HP_UdpNode_GetFreeBufferPoolHold(HP_UdpNode pNode);

#endif

/***************************************************************************************/
/***************************** TCP Pull Server 组件操作方法 *****************************/

/*
* 名称：抓取数据
* 描述：用户通过该方法从 Socket 组件中抓取数据
*		
* 参数：		dwConnID	-- 连接 ID
*			pData		-- 抓取缓冲区
*			iLength		-- 抓取数据长度
* 返回值：	En_HP_FetchResult
*/
//@别名 HP_TCP_拉服务端从网络套接字组件中抓取数据()
HPSOCKET_API En_HP_FetchResult __HP_CALL HP_TcpPullServer_Fetch(HP_TcpPullServer pServer, HP_CONNID dwConnID, BYTE* pData, int iLength);

/*
* 名称：窥探数据（不会移除缓冲区数据）
* 描述：用户通过该方法从 Socket 组件中窥探数据
*		
* 参数：		dwConnID	-- 连接 ID
*			pData		-- 窥探缓冲区
*			iLength		-- 窥探数据长度
* 返回值：	En_HP_FetchResult
*/
//@别名 HP_TCP_拉服务端从网络套接字组件中窥探数据()
HPSOCKET_API En_HP_FetchResult __HP_CALL HP_TcpPullServer_Peek(HP_TcpPullServer pServer, HP_CONNID dwConnID, BYTE* pData, int iLength);

/***************************************************************************************/
/***************************** TCP Pull Server 属性访问方法 *****************************/

/***************************************************************************************/
/***************************** TCP Pull Agent 组件操作方法 *****************************/

/*
* 名称：抓取数据
* 描述：用户通过该方法从 Socket 组件中抓取数据
*		
* 参数：		dwConnID	-- 连接 ID
*			pData		-- 抓取缓冲区
*			iLength		-- 抓取数据长度
* 返回值：	En_HP_FetchResult
*/
//@别名 HP_TCP_拉代理端从网络套接字组件中抓取数据()
HPSOCKET_API En_HP_FetchResult __HP_CALL HP_TcpPullAgent_Fetch(HP_TcpPullAgent pAgent, HP_CONNID dwConnID, BYTE* pData, int iLength);

/*
* 名称：窥探数据（不会移除缓冲区数据）
* 描述：用户通过该方法从 Socket 组件中窥探数据
*		
* 参数：		dwConnID	-- 连接 ID
*			pData		-- 窥探缓冲区
*			iLength		-- 窥探数据长度
* 返回值：	En_HP_FetchResult
*/
//@别名 HP_TCP_拉代理端网络套接字组件中窥探数据()
HPSOCKET_API En_HP_FetchResult __HP_CALL HP_TcpPullAgent_Peek(HP_TcpPullAgent pAgent, HP_CONNID dwConnID, BYTE* pData, int iLength);

/***************************************************************************************/
/***************************** TCP Pull Agent 属性访问方法 *****************************/

/***************************************************************************************/
/***************************** TCP Pull Client 组件操作方法 *****************************/

/*
* 名称：抓取数据
* 描述：用户通过该方法从 Socket 组件中抓取数据
*		
* 参数：		dwConnID	-- 连接 ID
*			pData		-- 抓取缓冲区
*			iLength		-- 抓取数据长度
* 返回值：	En_HP_FetchResult
*/
//@别名 HP_TCP_拉客户端从Socket组件中抓取数据()
HPSOCKET_API En_HP_FetchResult __HP_CALL HP_TcpPullClient_Fetch(HP_TcpPullClient pClient, BYTE* pData, int iLength);

/*
* 名称：窥探数据（不会移除缓冲区数据）
* 描述：用户通过该方法从 Socket 组件中窥探数据
*		
* 参数：		dwConnID	-- 连接 ID
*			pData		-- 窥探缓冲区
*			iLength		-- 窥探数据长度
* 返回值：	En_HP_FetchResult
*/
//@别名 HP_TCP_拉客户端从Socket组件中窥探数据()
HPSOCKET_API En_HP_FetchResult __HP_CALL HP_TcpPullClient_Peek(HP_TcpPullClient pClient, BYTE* pData, int iLength);

/***************************************************************************************/
/***************************** TCP Pull Client 属性访问方法 *****************************/

/***************************************************************************************/
/***************************** TCP Pack Server 组件操作方法 *****************************/

/***************************************************************************************/
/***************************** TCP Pack Server 属性访问方法 *****************************/

//@备注 置数据包最大长度（有效数据包最大长度不能超过 4194303/0x3FFFFF 字节，默认：262144/0x40000）
//@别名 HP_置TCP_包服务器端数据包最大长度()
HPSOCKET_API void __HP_CALL HP_TcpPackServer_SetMaxPackSize(HP_TcpPackServer pServer, DWORD dwMaxPackSize);
//@备注 置包头标识（有效包头标识取值范围 0 ~ 1023/0x3FF，当包头标识为 0 时不校验包头，默认：0）
//@别名 HP_置TCP_包服务器端包头标识()
HPSOCKET_API void __HP_CALL HP_TcpPackServer_SetPackHeaderFlag(HP_TcpPackServer pServer, USHORT usPackHeaderFlag);

//@别名 HP_取TCP_包服务器端数据包最大长度()
HPSOCKET_API DWORD __HP_CALL HP_TcpPackServer_GetMaxPackSize(HP_TcpPackServer pServer);
//@别名 HP_取TCP_包服务器端包头标识()
HPSOCKET_API USHORT __HP_CALL HP_TcpPackServer_GetPackHeaderFlag(HP_TcpPackServer pServer);

/***************************************************************************************/
/***************************** TCP Pack Agent 组件操作方法 *****************************/

/***************************************************************************************/
/***************************** TCP Pack Agent 属性访问方法 *****************************/

//@备注 置数据包最大长度（有效数据包最大长度不能超过 4194303/0x3FFFFF 字节，默认：262144/0x40000）
//@别名 HP_置TCP_包代理端数据包最大长度()
HPSOCKET_API void __HP_CALL HP_TcpPackAgent_SetMaxPackSize(HP_TcpPackAgent pAgent, DWORD dwMaxPackSize);
//@备注 置包头标识（有效包头标识取值范围 0 ~ 1023/0x3FF，当包头标识为 0 时不校验包头，默认：0）
//@别名 HP_置TCP_包代理端包头标识()
HPSOCKET_API void __HP_CALL HP_TcpPackAgent_SetPackHeaderFlag(HP_TcpPackAgent pAgent, USHORT usPackHeaderFlag);

//@别名 HP_取TCP_包代理端数据包最大长度()
HPSOCKET_API DWORD __HP_CALL HP_TcpPackAgent_GetMaxPackSize(HP_TcpPackAgent pAgent);
//@别名 HP_取TCP_包代理端包头标识()
HPSOCKET_API USHORT __HP_CALL HP_TcpPackAgent_GetPackHeaderFlag(HP_TcpPackAgent pAgent);

/***************************************************************************************/
/***************************** TCP Pack Client 组件操作方法 *****************************/

/***************************************************************************************/
/***************************** TCP Pack Client 属性访问方法 *****************************/

//@备注 置数据包最大长度（有效数据包最大长度不能超过 4194303/0x3FFFFF 字节，默认：262144/0x40000）
//@别名 HP_置TCP_包客户端数据包最大长度()
HPSOCKET_API void __HP_CALL HP_TcpPackClient_SetMaxPackSize(HP_TcpPackClient pClient, DWORD dwMaxPackSize);
//@备注 置包头标识（有效包头标识取值范围 0 ~ 1023/0x3FF，当包头标识为 0 时不校验包头，默认：0）
//@别名 HP_置TCP_包客户端包头标识()
HPSOCKET_API void __HP_CALL HP_TcpPackClient_SetPackHeaderFlag(HP_TcpPackClient pClient, USHORT usPackHeaderFlag);

//@别名 HP_取CP_包客户端数据包最大长度()
HPSOCKET_API DWORD __HP_CALL HP_TcpPackClient_GetMaxPackSize(HP_TcpPackClient pClient);
//@别名 HP_取CP_包客户端包头标识()
HPSOCKET_API USHORT __HP_CALL HP_TcpPackClient_GetPackHeaderFlag(HP_TcpPackClient pClient);

/*****************************************************************************************************************************************************/
/*************************************************************** Global Function Exports *************************************************************/
/*****************************************************************************************************************************************************/

//@备注取 HPSocket 版本号（4 个字节分别为：主版本号，子版本号，修正版本号，构建编号）
//@别名 HP_取HPSocket版本号()
HPSOCKET_API DWORD __HP_CALL HP_GetHPSocketVersion();

//@别名 HP_取错误描述文本()
HPSOCKET_API LPCTSTR __HP_CALL HP_GetSocketErrorDesc(En_HP_SocketError enCode);
//@备注 调用系统的 GetLastError() 方法取系统错误代码
//@别名 HP_调用系统的网络错误信息()
HPSOCKET_API DWORD __HP_CALL SYS_GetLastError();
//@备注 调用系统的 WSAGetLastError() 方法取系统错误代码
//@别名 HP_调用系统的网络上次错误信息()
HPSOCKET_API int __HP_CALL SYS_WSAGetLastError();
//@备注 调用系统的 setsockopt()
//@别名 HP_调用系统的设置网络套接字的设置选项值()
HPSOCKET_API int __HP_CALL SYS_SetSocketOption(SOCKET sock, int level, int name, LPVOID val, int len);
//@备注 调用系统的 getsockopt()
//@别名 HP_调用系统的设置获取网络套接字的选项当前值()
HPSOCKET_API int __HP_CALL SYS_GetSocketOption(SOCKET sock, int level, int name, LPVOID val, int* len);
//@备注 调用系统的 ioctlsocket()
//@别名 HP_调用系统的设置控制非阻塞网络套接字的模式()
HPSOCKET_API int __HP_CALL SYS_IoctlSocket(SOCKET sock, long cmd, u_long* arg);
//@备注 调用系统的 WSAIoctl()
//@别名 HP_调用系统的设置TCP连接的心跳参数()
HPSOCKET_API int __HP_CALL SYS_WSAIoctl(SOCKET sock, DWORD dwIoControlCode, LPVOID lpvInBuffer, DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbBytesReturned);

//@备注 置 socket 选项：IPPROTO_TCP -> TCP_NODELAY
//@别名 HP_置套接字选项()
HPSOCKET_API int __HP_CALL SYS_SSO_NoDelay(SOCKET sock, BOOL bNoDelay);
//@备注 置 socket 选项：SOL_SOCKET -> SO_DONTLINGER
//@别名 HP_置网络套接字选项不查找路由()
HPSOCKET_API int __HP_CALL SYS_SSO_DontLinger(SOCKET sock, BOOL bDont);
//@备注 置 socket 选项：SOL_SOCKET -> SO_LINGER
//@别名 HP_置网络套接字选项延迟关闭连接()
HPSOCKET_API int __HP_CALL SYS_SSO_Linger(SOCKET sock, USHORT l_onoff, USHORT l_linger);
//@备注 置 socket 选项：SOL_SOCKET -> SO_RCVBUF
//@别名 HP_置网络套接字选项接收缓冲区下限()
HPSOCKET_API int __HP_CALL SYS_SSO_RecvBuffSize(SOCKET sock, int size);
//@备注 置 socket 选项：SOL_SOCKET -> SO_SNDBUF
//@别名 HP_置网络套接字选项发送缓冲区大小()
HPSOCKET_API int __HP_CALL SYS_SSO_SendBuffSize(SOCKET sock, int size);
//@备注 置 socket 选项：SOL_SOCKET -> SO_RCVTIMEO
//@别名 HP_置网络套接字选项接收超时()
HPSOCKET_API int __HP_CALL SYS_SSO_RecvTimeOut(SOCKET sock, int ms);
//@备注 置 socket 选项：SOL_SOCKET -> SO_SNDTIMEO
//@别名 HP_置网络套接字选项发送超时()
HPSOCKET_API int __HP_CALL SYS_SSO_SendTimeOut(SOCKET sock, int ms);
//@备注 置 socket 选项：SOL_SOCKET -> SO_EXCLUSIVEADDRUSE / SO_REUSEADDR
//@别名 HP_置网络套接字选项()
HPSOCKET_API int __HP_CALL SYS_SSO_ReuseAddress(SOCKET sock, En_HP_ReuseAddressPolicy opt);
//@备注 置 socket 选项：SOL_SOCKET -> SO_EXCLUSIVEADDRUSE
//@别名 HP_置网络套接字选项专用地址使用()
HPSOCKET_API int __HP_CALL SYS_SSO_ExclusiveAddressUse(SOCKET sock, BOOL bExclusive);

//@别名 HP_取网络套接字本地地址信息()
HPSOCKET_API BOOL __HP_CALL SYS_GetSocketLocalAddress(SOCKET socket, TCHAR lpszAddress[], int* piAddressLen, USHORT* pusPort);
//@别名 HP_取网络套接字远程地址信息()
HPSOCKET_API BOOL __HP_CALL SYS_GetSocketRemoteAddress(SOCKET socket, TCHAR lpszAddress[], int* piAddressLen, USHORT* pusPort);

//@别名 HP_枚举主机IP地址()
HPSOCKET_API BOOL __HP_CALL SYS_EnumHostIPAddresses(LPCTSTR lpszHost, En_HP_IPAddrType enType, HP_LPTIPAddr** lpppIPAddr, int* piIPAddrCount);
//@别名 HP_释放HP_LPT地址()
HPSOCKET_API BOOL __HP_CALL SYS_FreeHostIPAddresses(HP_LPTIPAddr* lppIPAddr);
//@别名 HP_检查字符串是否符合IP地址格式()
HPSOCKET_API BOOL __HP_CALL SYS_IsIPAddress(LPCTSTR lpszAddress, En_HP_IPAddrType* penType);
//@别名 HP_通过主机名取IP地址()
HPSOCKET_API BOOL __HP_CALL SYS_GetIPAddress(LPCTSTR lpszHost, TCHAR lpszIP[], int* piIPLenth, En_HP_IPAddrType* penType);

//@别名 HP__64位网络字节序转主机字节序()
HPSOCKET_API ULONGLONG __HP_CALL SYS_NToH64(ULONGLONG value);
//@别名 HP__64位主机字节序转网络字节序()
HPSOCKET_API ULONGLONG __HP_CALL SYS_HToN64(ULONGLONG value);
//@别名 HP_短整型高低字节交换()
HPSOCKET_API USHORT __HP_CALL SYS_SwapEndian16(USHORT value);
//@别名 HP_长整型高低字节交换()
HPSOCKET_API DWORD __HP_CALL SYS_SwapEndian32(DWORD value);
//@别名 HP_检查是否小端字节序()
HPSOCKET_API BOOL __HP_CALL SYS_IsLittleEndian();

//@别名 HP_分配内存()
HPSOCKET_API LPBYTE __HP_CALL SYS_Malloc(int size);
//@别名 HP_重新分配内存()
HPSOCKET_API LPBYTE __HP_CALL SYS_Realloc(LPBYTE p, int size);
//@别名 HP_释放内存()
HPSOCKET_API VOID __HP_CALL SYS_Free(LPBYTE p);
//@别名 HP_分配内存块()
HPSOCKET_API LPVOID __HP_CALL SYS_Calloc(int number, int size);
//@别名 HP_分配栈内存()
HPSOCKET_API LPBYTE __HP_CALL SYS_Alloca(int size);

// CP_XXX -> UNICODE
//@别名 HP_CodePage转Unicode()
HPSOCKET_API BOOL __HP_CALL SYS_CodePageToUnicode(int iCodePage, const char szSrc[], WCHAR szDest[], int* piDestLength);
// UNICODE -> CP_XXX
//@别名 HP_nicode转CodePage()
HPSOCKET_API BOOL __HP_CALL SYS_UnicodeToCodePage(int iCodePage, const WCHAR szSrc[], char szDest[], int* piDestLength);
// GBK -> UNICODE
//@别名 HP_Gbk转Unicode()
HPSOCKET_API BOOL __HP_CALL SYS_GbkToUnicode(const char szSrc[], WCHAR szDest[], int* piDestLength);
// UNICODE -> GBK
//@别名 HP_UNICODE转GBK()
HPSOCKET_API BOOL __HP_CALL SYS_UnicodeToGbk(const WCHAR szSrc[], char szDest[], int* piDestLength);
// UTF8 -> UNICODE
//@别名 HP_UTF8转UNICODE()
HPSOCKET_API BOOL __HP_CALL SYS_Utf8ToUnicode(const char szSrc[], WCHAR szDest[], int* piDestLength);
// UNICODE -> UTF8\
//@别名 HP_UNICODE转UTF8()
HPSOCKET_API BOOL __HP_CALL SYS_UnicodeToUtf8(const WCHAR szSrc[], char szDest[], int* piDestLength);
// GBK -> UTF8
//@别名 HP_Gbk转UTF8()
HPSOCKET_API BOOL __HP_CALL SYS_GbkToUtf8(const char szSrc[], char szDest[], int* piDestLength);
// UTF8 -> GBK
//@别名 HP_UTF8转GBK()
HPSOCKET_API BOOL __HP_CALL SYS_Utf8ToGbk(const char szSrc[], char szDest[], int* piDestLength);

// 计算 Base64 编码后长度
//@别名 HP_计算Base64编码后长度()
HPSOCKET_API DWORD __HP_CALL SYS_GuessBase64EncodeBound(DWORD dwSrcLen);
// 计算 Base64 解码后长度
//@别名 HP_计算Base64解码后长度()
HPSOCKET_API DWORD __HP_CALL SYS_GuessBase64DecodeBound(const BYTE* lpszSrc, DWORD dwSrcLen);
//@备注 Base64 编码（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
//@别名 HP_Base64编码()
HPSOCKET_API int __HP_CALL SYS_Base64Encode(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD* pdwDestLen);
//@备注 Base64 解码（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
//@别名 HP_Base64解码()
HPSOCKET_API int __HP_CALL SYS_Base64Decode(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD* pdwDestLen);

//@别名 HP_计算URL编码后长度()
HPSOCKET_API DWORD __HP_CALL SYS_GuessUrlEncodeBound(const BYTE* lpszSrc, DWORD dwSrcLen);
//@别名 HP_计算URL解码后长度()
HPSOCKET_API DWORD __HP_CALL SYS_GuessUrlDecodeBound(const BYTE* lpszSrc, DWORD dwSrcLen);
//@备注 URL 编码（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
//@别名 HP_URL编码()
HPSOCKET_API int __HP_CALL SYS_UrlEncode(BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD* pdwDestLen);
//@备注 URL 解码（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
//@别名 HP_URL解码()
HPSOCKET_API int __HP_CALL SYS_UrlDecode(BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD* pdwDestLen);

#ifdef _ZLIB_SUPPORT

//@备注 普通压缩（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
//@别名 HP_普通压缩()
HPSOCKET_API int __HP_CALL SYS_Compress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD* pdwDestLen);
//@备注 高级压缩（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）（默认参数：iLevel -> -1，iMethod -> 8，iWindowBits -> 15，iMemLevel -> 8，iStrategy -> 0）
//@别名 HP_高级压缩()
HPSOCKET_API int __HP_CALL SYS_CompressEx(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD* pdwDestLen, int iLevel, int iMethod, int iWindowBits, int iMemLevel, int iStrategy);
//@备注 普通解压（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
//@别名 HP_普通解压()
HPSOCKET_API int __HP_CALL SYS_Uncompress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD* pdwDestLen);
//@备注 高级解压（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）（默认参数：iWindowBits -> 15）
//@别名 HP_高级解压()
HPSOCKET_API int __HP_CALL SYS_UncompressEx(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD* pdwDestLen, int iWindowBits);
//@别名 HP_推测压缩结果长度()
HPSOCKET_API DWORD __HP_CALL SYS_GuessCompressBound(DWORD dwSrcLen, BOOL bGZip);

//@备注 Gzip 压缩（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
//@别名 HP_Gzip压缩()
HPSOCKET_API int __HP_CALL SYS_GZipCompress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD* pdwDestLen);
//@备注 Gzip 解压（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
//@别名 HP_Gzip解压()
HPSOCKET_API int __HP_CALL SYS_GZipUncompress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD* pdwDestLen);
//@备注 推测 Gzip 解压结果长度（如果返回 0 或不合理值则说明输入内容并非有效的 Gzip 格式）
//@别名 HP_推测Gzip解压结果长度()
HPSOCKET_API DWORD __HP_CALL SYS_GZipGuessUncompressBound(const BYTE* lpszSrc, DWORD dwSrcLen);

#endif

#ifdef _BROTLI_SUPPORT

//@备注 Brotli 压缩（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
//@别名 HP_Brotli压缩()
HPSOCKET_API int __HP_CALL SYS_BrotliCompress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD* pdwDestLen);
//@备注 Brotli 高级压缩（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）（默认参数：iQuality -> 11，iWindow -> 22，iMode -> 0）
//@别名 HP_Brotli高级压缩()
HPSOCKET_API int __HP_CALL SYS_BrotliCompressEx(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD* pdwDestLen, int iQuality, int iWindow, int iMode);
//@备注 Brotli 解压（返回值：0 -> 成功，-3 -> 输入数据不正确，-5 -> 输出缓冲区不足）
//@别名 HP_Brotli解压()
HPSOCKET_API int __HP_CALL SYS_BrotliUncompress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD* pdwDestLen);
//@备注 Brotli 推测压缩结果长度
//@别名 HP_Brotli推测压缩结果长度()
HPSOCKET_API DWORD __HP_CALL SYS_BrotliGuessCompressBound(DWORD dwSrcLen);

#endif

/*****************************************************************************************************************************************************/
/******************************************************************** HTTP Exports *******************************************************************/
/*****************************************************************************************************************************************************/

#ifdef _HTTP_SUPPORT

/****************************************************/
/******************* HTTP 回调函数 *******************/

/* HTTP 回调函数 */
typedef En_HP_HttpParseResult (__HP_CALL *HP_FN_Http_OnMessageBegin)	(HP_Http pSender, HP_CONNID dwConnID);
typedef En_HP_HttpParseResult (__HP_CALL *HP_FN_Http_OnRequestLine)		(HP_Http pSender, HP_CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszUrl);
typedef En_HP_HttpParseResult (__HP_CALL *HP_FN_Http_OnStatusLine)		(HP_Http pSender, HP_CONNID dwConnID, USHORT usStatusCode, LPCSTR lpszDesc);
typedef En_HP_HttpParseResult (__HP_CALL *HP_FN_Http_OnHeader)			(HP_Http pSender, HP_CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue);
typedef En_HP_HttpParseResult (__HP_CALL *HP_FN_Http_OnHeadersComplete)	(HP_Http pSender, HP_CONNID dwConnID);
typedef En_HP_HttpParseResult (__HP_CALL *HP_FN_Http_OnBody)			(HP_Http pSender, HP_CONNID dwConnID, const BYTE* pData, int iLength);
typedef En_HP_HttpParseResult (__HP_CALL *HP_FN_Http_OnChunkHeader)		(HP_Http pSender, HP_CONNID dwConnID, int iLength);
typedef En_HP_HttpParseResult (__HP_CALL *HP_FN_Http_OnChunkComplete)	(HP_Http pSender, HP_CONNID dwConnID);
typedef En_HP_HttpParseResult (__HP_CALL *HP_FN_Http_OnMessageComplete)	(HP_Http pSender, HP_CONNID dwConnID);
typedef En_HP_HttpParseResult (__HP_CALL *HP_FN_Http_OnUpgrade)			(HP_Http pSender, HP_CONNID dwConnID, En_HP_HttpUpgradeType enUpgradeType);
typedef En_HP_HttpParseResult (__HP_CALL *HP_FN_Http_OnParseError)		(HP_Http pSender, HP_CONNID dwConnID, int iErrorCode, LPCSTR lpszErrorDesc);

typedef En_HP_HandleResult	 (__HP_CALL *HP_FN_Http_OnWSMessageHeader)	(HP_Http pSender, HP_CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen);
typedef En_HP_HandleResult	 (__HP_CALL *HP_FN_Http_OnWSMessageBody)	(HP_Http pSender, HP_CONNID dwConnID, const BYTE* pData, int iLength);
typedef En_HP_HandleResult	 (__HP_CALL *HP_FN_Http_OnWSMessageComplete)(HP_Http pSender, HP_CONNID dwConnID);

/* HTTP Server 回调函数 */
typedef HP_FN_Http_OnMessageBegin			HP_FN_HttpServer_OnMessageBegin;
typedef HP_FN_Http_OnRequestLine			HP_FN_HttpServer_OnRequestLine;
typedef HP_FN_Http_OnHeader					HP_FN_HttpServer_OnHeader;
typedef HP_FN_Http_OnHeadersComplete		HP_FN_HttpServer_OnHeadersComplete;
typedef HP_FN_Http_OnBody					HP_FN_HttpServer_OnBody;
typedef HP_FN_Http_OnChunkHeader			HP_FN_HttpServer_OnChunkHeader;
typedef HP_FN_Http_OnChunkComplete			HP_FN_HttpServer_OnChunkComplete;
typedef HP_FN_Http_OnMessageComplete		HP_FN_HttpServer_OnMessageComplete;
typedef HP_FN_Http_OnUpgrade				HP_FN_HttpServer_OnUpgrade;
typedef HP_FN_Http_OnParseError				HP_FN_HttpServer_OnParseError;

typedef HP_FN_Http_OnWSMessageHeader		HP_FN_HttpServer_OnWSMessageHeader;
typedef HP_FN_Http_OnWSMessageBody			HP_FN_HttpServer_OnWSMessageBody;
typedef HP_FN_Http_OnWSMessageComplete		HP_FN_HttpServer_OnWSMessageComplete;

typedef HP_FN_Server_OnPrepareListen		HP_FN_HttpServer_OnPrepareListen;
typedef HP_FN_Server_OnAccept				HP_FN_HttpServer_OnAccept;
typedef HP_FN_Server_OnHandShake			HP_FN_HttpServer_OnHandShake;
typedef HP_FN_Server_OnReceive				HP_FN_HttpServer_OnReceive;
typedef HP_FN_Server_OnSend					HP_FN_HttpServer_OnSend;
typedef HP_FN_Server_OnClose				HP_FN_HttpServer_OnClose;
typedef HP_FN_Server_OnShutdown				HP_FN_HttpServer_OnShutdown;

/* HTTP Agent 回调函数 */
typedef HP_FN_Http_OnMessageBegin			HP_FN_HttpAgent_OnMessageBegin;
typedef HP_FN_Http_OnStatusLine				HP_FN_HttpAgent_OnStatusLine;
typedef HP_FN_Http_OnHeader					HP_FN_HttpAgent_OnHeader;
typedef HP_FN_Http_OnHeadersComplete		HP_FN_HttpAgent_OnHeadersComplete;
typedef HP_FN_Http_OnBody					HP_FN_HttpAgent_OnBody;
typedef HP_FN_Http_OnChunkHeader			HP_FN_HttpAgent_OnChunkHeader;
typedef HP_FN_Http_OnChunkComplete			HP_FN_HttpAgent_OnChunkComplete;
typedef HP_FN_Http_OnMessageComplete		HP_FN_HttpAgent_OnMessageComplete;
typedef HP_FN_Http_OnUpgrade				HP_FN_HttpAgent_OnUpgrade;
typedef HP_FN_Http_OnParseError				HP_FN_HttpAgent_OnParseError;

typedef HP_FN_Http_OnWSMessageHeader		HP_FN_HttpAgent_OnWSMessageHeader;
typedef HP_FN_Http_OnWSMessageBody			HP_FN_HttpAgent_OnWSMessageBody;
typedef HP_FN_Http_OnWSMessageComplete		HP_FN_HttpAgent_OnWSMessageComplete;

typedef HP_FN_Agent_OnPrepareConnect		HP_FN_HttpAgent_OnPrepareConnect;
typedef HP_FN_Agent_OnConnect				HP_FN_HttpAgent_OnConnect;
typedef HP_FN_Agent_OnHandShake				HP_FN_HttpAgent_OnHandShake;
typedef HP_FN_Agent_OnReceive				HP_FN_HttpAgent_OnReceive;
typedef HP_FN_Agent_OnSend					HP_FN_HttpAgent_OnSend;
typedef HP_FN_Agent_OnClose					HP_FN_HttpAgent_OnClose;
typedef HP_FN_Agent_OnShutdown				HP_FN_HttpAgent_OnShutdown;

/* HTTP Client 回调函数 */
typedef HP_FN_Http_OnMessageBegin			HP_FN_HttpClient_OnMessageBegin;
typedef HP_FN_Http_OnStatusLine				HP_FN_HttpClient_OnStatusLine;
typedef HP_FN_Http_OnHeader					HP_FN_HttpClient_OnHeader;
typedef HP_FN_Http_OnHeadersComplete		HP_FN_HttpClient_OnHeadersComplete;
typedef HP_FN_Http_OnBody					HP_FN_HttpClient_OnBody;
typedef HP_FN_Http_OnChunkHeader			HP_FN_HttpClient_OnChunkHeader;
typedef HP_FN_Http_OnChunkComplete			HP_FN_HttpClient_OnChunkComplete;
typedef HP_FN_Http_OnMessageComplete		HP_FN_HttpClient_OnMessageComplete;
typedef HP_FN_Http_OnUpgrade				HP_FN_HttpClient_OnUpgrade;
typedef HP_FN_Http_OnParseError				HP_FN_HttpClient_OnParseError;

typedef HP_FN_Http_OnWSMessageHeader		HP_FN_HttpClient_OnWSMessageHeader;
typedef HP_FN_Http_OnWSMessageBody			HP_FN_HttpClient_OnWSMessageBody;
typedef HP_FN_Http_OnWSMessageComplete		HP_FN_HttpClient_OnWSMessageComplete;

typedef HP_FN_Client_OnPrepareConnect		HP_FN_HttpClient_OnPrepareConnect;
typedef HP_FN_Client_OnConnect				HP_FN_HttpClient_OnConnect;
typedef HP_FN_Client_OnHandShake			HP_FN_HttpClient_OnHandShake;
typedef HP_FN_Client_OnReceive				HP_FN_HttpClient_OnReceive;
typedef HP_FN_Client_OnSend					HP_FN_HttpClient_OnSend;
typedef HP_FN_Client_OnClose				HP_FN_HttpClient_OnClose;

/****************************************************/
/***************** HTTP对象()创建函数 *****************/

//@别名 HP_Http服务端对象创建()
HPSOCKET_API HP_HttpServer __HP_CALL Create_HP_HttpServer(HP_HttpServerListener pListener);
//@别名 HP_Http代理端对象创建()
HPSOCKET_API HP_HttpAgent __HP_CALL Create_HP_HttpAgent(HP_HttpAgentListener pListener);
//@别名 HP_Http客户端对象创建()
HPSOCKET_API HP_HttpClient __HP_CALL Create_HP_HttpClient(HP_HttpClientListener pListener);
//@备注 HP_创建HP_HttpSyncClient对象（pListener 参数可传入 nullptr）
//@别名 HP_Http同步客户端对象创建()
HPSOCKET_API HP_HttpSyncClient __HP_CALL Create_HP_HttpSyncClient(HP_HttpClientListener pListener /*= nullptr*/);

//@别名 HP_Http服务端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_HttpServer(HP_HttpServer pServer);
//@别名 HP_Http代理端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_HttpAgent(HP_HttpAgent pAgent);
//@别名 HP_Http客户端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_HttpClient(HP_HttpClient pClient);
//@别名 HP_Http同步客户端对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_HttpSyncClient(HP_HttpSyncClient pClient);

//@别名 HP_http服务器端侦听对象创建()
HPSOCKET_API HP_HttpServerListener __HP_CALL Create_HP_HttpServerListener();
//@别名 HP_Http代理端侦听对象创建()
HPSOCKET_API HP_HttpAgentListener __HP_CALL Create_HP_HttpAgentListener();
//@别名 HP_Http客户端侦听对象创建()
HPSOCKET_API HP_HttpClientListener __HP_CALL Create_HP_HttpClientListener();

//@别名 HP_Http服务器端侦听对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_HttpServerListener(HP_HttpServerListener pListener);
//@别名 HP_Http代理端侦听对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_HttpAgentListener(HP_HttpAgentListener pListener);
//@别名 HP_Http客户端侦听对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_HttpClientListener(HP_HttpClientListener pListener);

/**********************************************************************************/
/*************************** HTTP Server 回调函数置方法 **************************/

HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnMessageBegin(HP_HttpServerListener pListener		, HP_FN_HttpServer_OnMessageBegin fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnRequestLine(HP_HttpServerListener pListener		, HP_FN_HttpServer_OnRequestLine fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnHeader(HP_HttpServerListener pListener			, HP_FN_HttpServer_OnHeader fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnHeadersComplete(HP_HttpServerListener pListener	, HP_FN_HttpServer_OnHeadersComplete fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnBody(HP_HttpServerListener pListener				, HP_FN_HttpServer_OnBody fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnChunkHeader(HP_HttpServerListener pListener		, HP_FN_HttpServer_OnChunkHeader fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnChunkComplete(HP_HttpServerListener pListener	, HP_FN_HttpServer_OnChunkComplete fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnMessageComplete(HP_HttpServerListener pListener	, HP_FN_HttpServer_OnMessageComplete fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnUpgrade(HP_HttpServerListener pListener			, HP_FN_HttpServer_OnUpgrade fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnParseError(HP_HttpServerListener pListener		, HP_FN_HttpServer_OnParseError fn);

HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnWSMessageHeader(HP_HttpServerListener pListener	, HP_FN_HttpServer_OnWSMessageHeader fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnWSMessageBody(HP_HttpServerListener pListener	, HP_FN_HttpServer_OnWSMessageBody fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnWSMessageComplete(HP_HttpServerListener pListener, HP_FN_HttpServer_OnWSMessageComplete fn);

HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnPrepareListen(HP_HttpServerListener pListener	, HP_FN_HttpServer_OnPrepareListen fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnAccept(HP_HttpServerListener pListener			, HP_FN_HttpServer_OnAccept fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnHandShake(HP_HttpServerListener pListener		, HP_FN_HttpServer_OnHandShake fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnReceive(HP_HttpServerListener pListener			, HP_FN_HttpServer_OnReceive fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnSend(HP_HttpServerListener pListener				, HP_FN_HttpServer_OnSend fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnClose(HP_HttpServerListener pListener			, HP_FN_HttpServer_OnClose fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpServer_OnShutdown(HP_HttpServerListener pListener			, HP_FN_HttpServer_OnShutdown fn);

/**********************************************************************************/
/**************************** HTTP Agent 回调函数置方法 **************************/

HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnMessageBegin(HP_HttpAgentListener pListener		, HP_FN_HttpAgent_OnMessageBegin fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnStatusLine(HP_HttpAgentListener pListener			, HP_FN_HttpAgent_OnStatusLine fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnHeader(HP_HttpAgentListener pListener				, HP_FN_HttpAgent_OnHeader fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnHeadersComplete(HP_HttpAgentListener pListener	, HP_FN_HttpAgent_OnHeadersComplete fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnBody(HP_HttpAgentListener pListener				, HP_FN_HttpAgent_OnBody fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnChunkHeader(HP_HttpAgentListener pListener		, HP_FN_HttpAgent_OnChunkHeader fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnChunkComplete(HP_HttpAgentListener pListener		, HP_FN_HttpAgent_OnChunkComplete fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnMessageComplete(HP_HttpAgentListener pListener	, HP_FN_HttpAgent_OnMessageComplete fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnUpgrade(HP_HttpAgentListener pListener			, HP_FN_HttpAgent_OnUpgrade fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnParseError(HP_HttpAgentListener pListener			, HP_FN_HttpAgent_OnParseError fn);

HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnWSMessageHeader(HP_HttpAgentListener pListener	, HP_FN_HttpAgent_OnWSMessageHeader fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnWSMessageBody(HP_HttpAgentListener pListener		, HP_FN_HttpAgent_OnWSMessageBody fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnWSMessageComplete(HP_HttpAgentListener pListener	, HP_FN_HttpAgent_OnWSMessageComplete fn);

HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnPrepareConnect(HP_HttpAgentListener pListener		, HP_FN_HttpAgent_OnPrepareConnect fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnConnect(HP_HttpAgentListener pListener			, HP_FN_HttpAgent_OnConnect fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnHandShake(HP_HttpAgentListener pListener			, HP_FN_HttpAgent_OnHandShake fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnReceive(HP_HttpAgentListener pListener			, HP_FN_HttpAgent_OnReceive fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnSend(HP_HttpAgentListener pListener				, HP_FN_HttpAgent_OnSend fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnClose(HP_HttpAgentListener pListener				, HP_FN_HttpAgent_OnClose fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpAgent_OnShutdown(HP_HttpAgentListener pListener			, HP_FN_HttpAgent_OnShutdown fn);

/**********************************************************************************/
/*************************** HTTP Client 回调函数置方法 **************************/

HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnMessageBegin(HP_HttpClientListener pListener		, HP_FN_HttpClient_OnMessageBegin fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnStatusLine(HP_HttpClientListener pListener		, HP_FN_HttpClient_OnStatusLine fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnHeader(HP_HttpClientListener pListener			, HP_FN_HttpClient_OnHeader fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnHeadersComplete(HP_HttpClientListener pListener	, HP_FN_HttpClient_OnHeadersComplete fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnBody(HP_HttpClientListener pListener				, HP_FN_HttpClient_OnBody fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnChunkHeader(HP_HttpClientListener pListener		, HP_FN_HttpClient_OnChunkHeader fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnChunkComplete(HP_HttpClientListener pListener	, HP_FN_HttpClient_OnChunkComplete fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnMessageComplete(HP_HttpClientListener pListener	, HP_FN_HttpClient_OnMessageComplete fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnUpgrade(HP_HttpClientListener pListener			, HP_FN_HttpClient_OnUpgrade fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnParseError(HP_HttpClientListener pListener		, HP_FN_HttpClient_OnParseError fn);

HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnWSMessageHeader(HP_HttpClientListener pListener	, HP_FN_HttpClient_OnWSMessageHeader fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnWSMessageBody(HP_HttpClientListener pListener	, HP_FN_HttpClient_OnWSMessageBody fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnWSMessageComplete(HP_HttpClientListener pListener, HP_FN_HttpClient_OnWSMessageComplete fn);

HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnPrepareConnect(HP_HttpClientListener pListener	, HP_FN_HttpClient_OnPrepareConnect fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnConnect(HP_HttpClientListener pListener			, HP_FN_HttpClient_OnConnect fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnHandShake(HP_HttpClientListener pListener		, HP_FN_HttpClient_OnHandShake fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnReceive(HP_HttpClientListener pListener			, HP_FN_HttpClient_OnReceive fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnSend(HP_HttpClientListener pListener				, HP_FN_HttpClient_OnSend fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_HttpClient_OnClose(HP_HttpClientListener pListener			, HP_FN_HttpClient_OnClose fn);

/**************************************************************************/
/*************************** HTTP Server 操作方法 **************************/

/*
* 名称：回复请求
* 描述：向客户端回复 HTTP 请求
*		
* 参数：		dwConnID		-- 连接 ID
*			usStatusCode	-- HTTP 状态码
*			lpszDesc		-- HTTP 状态描述
*			lpHeaders		-- 回复请求头
*			iHeaderCount	-- 回复请求头数量
*			pData			-- 回复请求体
*			iLength			-- 回复请求体长度
* 返回值：	TRUE			-- 成功
*			FALSE			-- 失败
*/
//@别名 HP_向客复户端回复HTTP请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpServer_SendResponse(HP_HttpServer pServer, HP_CONNID dwConnID, USHORT usStatusCode, LPCSTR lpszDesc, const HP_THeader lpHeaders[], int iHeaderCount, const BYTE* pData, int iLength);

/*
* 名称：发送本地文件
* 描述：向指定连接发送 4096 KB 以下的小文件
*		
* 参数：		dwConnID		-- 连接 ID
*			lpszFileName	-- 文件路径
*			usStatusCode	-- HTTP 状态码
*			lpszDesc		-- HTTP 状态描述
*			lpHeaders		-- 回复请求头
*			iHeaderCount	-- 回复请求头数量
* 返回值：	TRUE			-- 成功
*			FALSE			-- 失败
*/
//@别名 HP_向指定连接发送本地文件()
HPSOCKET_API BOOL __HP_CALL HP_HttpServer_SendLocalFile(HP_HttpServer pServer, HP_CONNID dwConnID, LPCSTR lpszFileName, USHORT usStatusCode, LPCSTR lpszDesc, const HP_THeader lpHeaders[], int iHeaderCount);

/*
* 名称：发送 Chunked 数据分片
* 描述：向对端发送 Chunked 数据分片
*		
* 参数：		dwConnID		-- 连接 ID
*			pData			-- Chunked 数据分片
*			iLength			-- 数据分片长度（为 0 表示结束分片）
*			lpszExtensions	-- 扩展属性（默认：nullptr）
* 返回值：	TRUE			-- 成功
*			FALSE			-- 失败
*/
//@别名 HP_发送分块数据分片()
HPSOCKET_API BOOL __HP_CALL HP_HttpServer_SendChunkData(HP_HttpServer pServer, HP_CONNID dwConnID, const BYTE* pData /*= nullptr*/, int iLength /*= 0*/, LPCSTR lpszExtensions /*= nullptr*/);

/*
* 名称：发送 WebSocket 消息
* 描述：向对端端发送 WebSocket 消息
*		
* 参数：		dwConnID		-- 连接 ID
*			bFinal			-- 是否结束帧
*			iReserved		-- RSV1/RSV2/RSV3 各 1 位
*			iOperationCode	-- 操作码：0x0 - 0xF
*			pData			-- 消息体数据缓冲区
*			iLength			-- 消息体数据长度
*			ullBodyLen		-- 消息总长度
* 								ullBodyLen = 0		 -> 消息总长度为 iLength
* 								ullBodyLen = iLength -> 消息总长度为 ullBodyLen
* 								ullBodyLen > iLength -> 消息总长度为 ullBodyLen，后续消息体长度为 ullBOdyLen - iLength，后续消息体通过底层方法 Send() / SendPackets() 发送
* 								ullBodyLen < iLength -> 错误参数，发送失败
* 返回值：	TRUE			-- 成功
*			FALSE			-- 失败
*/
//@别名 HP_发送Web套接字消息()
HPSOCKET_API BOOL __HP_CALL HP_HttpServer_SendWSMessage(HP_HttpServer pServer, HP_CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE* pData, int iLength, ULONGLONG ullBodyLen);

/*
* 名称：释放连接
* 描述：把连接放入释放队列，等待某个时间（通过 SetReleaseDelay() 置）关闭连接
*		
* 参数：		dwConnID		-- 连接 ID
* 返回值：	TRUE			-- 成功
*			FALSE			-- 失败
*/
//@别名 HP_释放连接()
HPSOCKET_API BOOL __HP_CALL HP_HttpServer_Release(HP_HttpServer pServer, HP_CONNID dwConnID);

/*
* 名称：启动 HTTP 通信
* 描述：当通信组件置为非自动启动 HTTP 通信时，需要调用本方法启动 HTTP 通信
*		
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取失败原因
*/
//@别名 HP_启动HTTP通信()
HPSOCKET_API BOOL __HP_CALL HP_HttpServer_StartHttp(HP_HttpServer pServer, HP_CONNID dwConnID);

/******************************************************************************/
/*************************** HTTP Server 属性访问方法 **************************/

//@备注 置HTTP服务器端连接释放延时（默认：3000 毫秒）
//@别名 HP_置HTTP服务器端连接释放延时()
HPSOCKET_API void __HP_CALL HP_HttpServer_SetReleaseDelay(HP_HttpServer pServer, DWORD dwReleaseDelay);
//@别名 HP_取HTTP服务器端连接释放延时()
HPSOCKET_API DWORD __HP_CALL HP_HttpServer_GetReleaseDelay(HP_HttpServer pServer);
//@备注 取请求行 URL 域掩码（URL 域参考：EnHttpUrlField）
//@别名 HP_取HTTP服务器端请求行的URL域掩码()
HPSOCKET_API USHORT __HP_CALL HP_HttpServer_GetUrlFieldSet(HP_HttpServer pServer, HP_CONNID dwConnID);
//@别名 HP_取http服务器端某个URL域值()
HPSOCKET_API LPCSTR __HP_CALL HP_HttpServer_GetUrlField(HP_HttpServer pServer, HP_CONNID dwConnID, En_HP_HttpUrlField enField);
//@别名 HP_取http服务器端请求方法()
HPSOCKET_API LPCSTR __HP_CALL HP_HttpServer_GetMethod(HP_HttpServer pServer, HP_CONNID dwConnID);

//@别名 HP_置http服务器端本地协议版本()
HPSOCKET_API void __HP_CALL HP_HttpServer_SetLocalVersion(HP_HttpServer pServer, En_HP_HttpVersion usVersion);
//@别名 HP_取http服务器端本地协议版本()
HPSOCKET_API En_HP_HttpVersion __HP_CALL HP_HttpServer_GetLocalVersion(HP_HttpServer pServer);

//@别名 HP_检查http服务器端是否升级协议()
HPSOCKET_API BOOL __HP_CALL HP_HttpServer_IsUpgrade(HP_HttpServer pServer, HP_CONNID dwConnID);
//@别名 HP_检查http服务器端是否有检测死连接标识()
HPSOCKET_API BOOL __HP_CALL HP_HttpServer_IsKeepAlive(HP_HttpServer pServer, HP_CONNID dwConnID);
//@别名 HP_取http服务器端协议版本()
HPSOCKET_API USHORT __HP_CALL HP_HttpServer_GetVersion(HP_HttpServer pServer, HP_CONNID dwConnID);
//@别名 HP_取http服务器端主机()
HPSOCKET_API LPCSTR __HP_CALL HP_HttpServer_GetHost(HP_HttpServer pServer, HP_CONNID dwConnID);
//@别名 HP_取http服务器端内容长度()
HPSOCKET_API ULONGLONG __HP_CALL HP_HttpServer_GetContentLength(HP_HttpServer pServer, HP_CONNID dwConnID);
//@别名 HP_取http服务器端内容类型()
HPSOCKET_API LPCSTR __HP_CALL HP_HttpServer_GetContentType(HP_HttpServer pServer, HP_CONNID dwConnID);
//@别名 HP_取http服务器端内容编码()
HPSOCKET_API LPCSTR __HP_CALL HP_HttpServer_GetContentEncoding(HP_HttpServer pServer, HP_CONNID dwConnID);
//@别名 HP_取http服务器端传输编码()
HPSOCKET_API LPCSTR __HP_CALL HP_HttpServer_GetTransferEncoding(HP_HttpServer pServer, HP_CONNID dwConnID);
//@别名 HP_取http服务器端协议升级类型()
HPSOCKET_API En_HP_HttpUpgradeType __HP_CALL HP_HttpServer_GetUpgradeType(HP_HttpServer pServer, HP_CONNID dwConnID);
//@别名 HP_取http服务器端解析错误代码()
HPSOCKET_API USHORT __HP_CALL HP_HttpServer_GetParseErrorCode(HP_HttpServer pServer, HP_CONNID dwConnID, LPCSTR* lpszErrorDesc);

//@备注 HP_取http服务器端某个请求头（单值）
//@别名 HP_取http服务器端某个请求头()
HPSOCKET_API BOOL __HP_CALL HP_HttpServer_GetHeader(HP_HttpServer pServer, HP_CONNID dwConnID, LPCSTR lpszName, LPCSTR* lpszValue);
//@备注 HP_取http服务器端某个请求头（多值）
//@别名 HP_取http服务器端某个请求头（多值）()
HPSOCKET_API BOOL __HP_CALL HP_HttpServer_GetHeaders(HP_HttpServer pServer, HP_CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue[], DWORD* pdwCount);
//@别名 HP_取http服务器端所有请求头()
HPSOCKET_API BOOL __HP_CALL HP_HttpServer_GetAllHeaders(HP_HttpServer pServer, HP_CONNID dwConnID, HP_THeader lpHeaders[], DWORD* pdwCount);
//@别名 HP_取http服务器端所有请求头名称()
HPSOCKET_API BOOL __HP_CALL HP_HttpServer_GetAllHeaderNames(HP_HttpServer pServer, HP_CONNID dwConnID, LPCSTR lpszName[], DWORD* pdwCount);

//@别名 HP_取http服务器端Cookie()
HPSOCKET_API BOOL __HP_CALL HP_HttpServer_GetCookie(HP_HttpServer pServer, HP_CONNID dwConnID, LPCSTR lpszName, LPCSTR* lpszValue);
//@别名 HP_取http服务器端所有Cookie()
HPSOCKET_API BOOL __HP_CALL HP_HttpServer_GetAllCookies(HP_HttpServer pServer, HP_CONNID dwConnID, HP_TCookie lpCookies[], DWORD* pdwCount);

//@备注 HP_取http服务器端当前 WebSocket 消息状态，传入 nullptr 则不取http服务器端相应字段()
//@别名 HP_取http服务器端当前Web套接字消息状态()
HPSOCKET_API BOOL __HP_CALL HP_HttpServer_GetWSMessageState(HP_HttpServer pServer, HP_CONNID dwConnID, BOOL* lpbFinal, BYTE* lpiReserved, BYTE* lpiOperationCode, LPCBYTE* lpszMask, ULONGLONG* lpullBodyLen, ULONGLONG* lpullBodyRemain);

//@备注 HP_置http服务器端 HTTP 启动方式（默认：TRUE，自动启动）()
//@别名 HP_置http服务器端HTTP启动方式()
HPSOCKET_API void __HP_CALL HP_HttpServer_SetHttpAutoStart(HP_HttpServer pServer, BOOL bAutoStart);
//@别名 HP_取http服务器端HTTP启动方式()
HPSOCKET_API BOOL __HP_CALL HP_HttpServer_IsHttpAutoStart(HP_HttpServer pServer);

/**************************************************************************/
/*************************** HTTP Agent 操作方法 ***************************/

/*
* 名称：发送请求
* 描述：向服务端发送 HTTP 请求
*		
* 参数：		dwConnID		-- 连接 ID
*			lpszMethod		-- 请求方法
*			lpszPath		-- 请求路径
*			lpHeaders		-- 请求头
*			iHeaderCount	-- 请求头数量
*			pBody			-- 请求体
*			iLength			-- 请求体长度
* 返回值：	TRUE			-- 成功
*			FALSE			-- 失败
*/
//@别名 HP_使用代理HTTP向服务端发送HTTP请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_SendRequest(HP_HttpAgent pAgent, HP_CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount, const BYTE* pData, int iLength);

/*
* 名称：发送本地文件
* 描述：向指定连接发送 4096 KB 以下的小文件
*		
* 参数：		dwConnID		-- 连接 ID
*			lpszFileName	-- 文件路径
*			lpszMethod		-- 请求方法
*			lpszPath		-- 请求路径
*			lpHeaders		-- 请求头
*			iHeaderCount	-- 请求头数量
* 返回值：	TRUE			-- 成功
*			FALSE			-- 失败
*/
//@别名 HP_使用代理HTTP向指定连接发本地文件()
//@备注 向指定连接发送 4096 KB 以下的小文件
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_SendLocalFile(HP_HttpAgent pAgent, HP_CONNID dwConnID, LPCSTR lpszFileName, LPCSTR lpszMethod, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount);

/*
* 名称：发送 Chunked 数据分片
* 描述：向对端发送 Chunked 数据分片
*		
* 参数：		dwConnID		-- 连接 ID
*			pData			-- Chunked 数据分片
*			iLength			-- 数据分片长度（为 0 表示结束分片）
*			lpszExtensions	-- 扩展属性（默认：nullptr）
* 返回值：	TRUE			-- 成功
*			FALSE			-- 失败
*/
//@别名 HP_使用代理HTTP发送分块数据分片()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_SendChunkData(HP_HttpAgent pAgent, HP_CONNID dwConnID, const BYTE* pData /*= nullptr*/, int iLength /*= 0*/, LPCSTR lpszExtensions /*= nullptr*/);

//@备注 发送 POST 请求
//@别名 HP_使用代理HTTP发送邮件请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_SendPost(HP_HttpAgent pAgent, HP_CONNID dwConnID, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength);
//@备注 发送 PUT 请求
//@别名 HP_使用代理HTTP发送上传请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_SendPut(HP_HttpAgent pAgent, HP_CONNID dwConnID, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength);
//@备注 发送 PATCH 请求
//@别名 HP_使用代理HTTP发送PATCH请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_SendPatch(HP_HttpAgent pAgent, HP_CONNID dwConnID, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength);
//@备注 发送 GET 请求
//@别名 HP_使用代理HTTP发送下载请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_SendGet(HP_HttpAgent pAgent, HP_CONNID dwConnID, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount);
//@备注 发送 DELETE 请求
//@别名 HP_使用代理HTTP发送删除请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_SendDelete(HP_HttpAgent pAgent, HP_CONNID dwConnID, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount);
//@备注 发送 HEAD 请求
//@别名 HP_使用代理HTTP发送HEAD请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_SendHead(HP_HttpAgent pAgent, HP_CONNID dwConnID, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount);
//@备注 发送 TRACE 请求
//@别名 HP_使用代理HTTP发送查找请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_SendTrace(HP_HttpAgent pAgent, HP_CONNID dwConnID, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount);
//@备注 发送 OPTIONS 请求
//@别名 HP_使用代理HTTP发送选项请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_SendOptions(HP_HttpAgent pAgent, HP_CONNID dwConnID, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount);
//@备注 发送 CONNECT 请求
//@别名 HP_使用代理HTTP发送连接请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_SendConnect(HP_HttpAgent pAgent, HP_CONNID dwConnID, LPCSTR lpszHost, const HP_THeader lpHeaders[], int iHeaderCount);

/*
* 名称：发送 WebSocket 消息
* 描述：向对端端发送 WebSocket 消息
*		
* 参数：		dwConnID		-- 连接 ID
*			bFinal			-- 是否结束帧
*			iReserved		-- RSV1/RSV2/RSV3 各 1 位
*			iOperationCode	-- 操作码：0x0 - 0xF
*			lpszMask		-- 掩码（nullptr 或 4 字节掩码，如果为 nullptr 则没有掩码）
*			pData			-- 消息体数据缓冲区
*			iLength			-- 消息体数据长度
*			ullBodyLen		-- 消息总长度
* 								ullBodyLen = 0		 -> 消息总长度为 iLength
* 								ullBodyLen = iLength -> 消息总长度为 ullBodyLen
* 								ullBodyLen > iLength -> 消息总长度为 ullBodyLen，后续消息体长度为 ullBOdyLen - iLength，后续消息体通过底层方法 Send() / SendPackets() 发送
* 								ullBodyLen < iLength -> 错误参数，发送失败
* 返回值：	TRUE			-- 成功
*			FALSE			-- 失败
*/
//@别名 HP_使用代理发送Web套接字消息()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_SendWSMessage(HP_HttpAgent pAgent, HP_CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], const BYTE* pData, int iLength, ULONGLONG ullBodyLen);

/*
* 名称：启动 HTTP 通信
* 描述：当通信组件置为非自动启动 HTTP 通信时，需要调用本方法启动 HTTP 通信
*		
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取失败原因
*/
//@别名 HP_使用代理启动HTTP通信()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_StartHttp(HP_HttpAgent pAgent, HP_CONNID dwConnID);

/******************************************************************************/
/*************************** HTTP Agent 属性访问方法 ***************************/

//@别名 HP_HTTP代理取HTTP状态码()
HPSOCKET_API USHORT __HP_CALL HP_HttpAgent_GetStatusCode(HP_HttpAgent pAgent, HP_CONNID dwConnID);
//@别名 HP_HTTP代理置本地协议版本()
HPSOCKET_API void __HP_CALL HP_HttpAgent_SetLocalVersion(HP_HttpAgent pAgent, En_HP_HttpVersion usVersion);
//@别名 HP_HTTP代理取本地协议版本()
HPSOCKET_API En_HP_HttpVersion __HP_CALL HP_HttpAgent_GetLocalVersion(HP_HttpAgent pAgent);
//@别名 HP_HTTP代理检查是否升级协议()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_IsUpgrade(HP_HttpAgent pAgent, HP_CONNID dwConnID);
//@别名 HP_HTTP代理检查是否有TCP检测死连接标识()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_IsKeepAlive(HP_HttpAgent pAgent, HP_CONNID dwConnID);
//@别名 HP_HTTP代理取协议版本()
HPSOCKET_API USHORT __HP_CALL HP_HttpAgent_GetVersion(HP_HttpAgent pAgent, HP_CONNID dwConnID);
//@别名 HP_HTTP代理取内容长度()
HPSOCKET_API ULONGLONG __HP_CALL HP_HttpAgent_GetContentLength(HP_HttpAgent pAgent, HP_CONNID dwConnID);
//@别名 HP_HTTP代理取内容类型()
HPSOCKET_API LPCSTR __HP_CALL HP_HttpAgent_GetContentType(HP_HttpAgent pAgent, HP_CONNID dwConnID);
//@别名 HP_HTTP代理取内容编码()
HPSOCKET_API LPCSTR __HP_CALL HP_HttpAgent_GetContentEncoding(HP_HttpAgent pAgent, HP_CONNID dwConnID);
//@别名 HP_HTTP代理取传输编码()
HPSOCKET_API LPCSTR __HP_CALL HP_HttpAgent_GetTransferEncoding(HP_HttpAgent pAgent, HP_CONNID dwConnID);
//@别名 HP_HTTP代理取协议升级类型()
HPSOCKET_API En_HP_HttpUpgradeType __HP_CALL HP_HttpAgent_GetUpgradeType(HP_HttpAgent pAgent, HP_CONNID dwConnID);
//@别名 HP_HTTP代理取解析错误代码()
HPSOCKET_API USHORT __HP_CALL HP_HttpAgent_GetParseErrorCode(HP_HttpAgent pAgent, HP_CONNID dwConnID, LPCSTR* lpszErrorDesc);

//@别名 HP_HTTP代理取某个请求头()
//@备注 HP_HTTP代理取某个请求头（单值）()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_GetHeader(HP_HttpAgent pAgent, HP_CONNID dwConnID, LPCSTR lpszName, LPCSTR* lpszValue);
//@别名 HP_HTTP代理取某个请求头（多值）()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_GetHeaders(HP_HttpAgent pAgent, HP_CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue[], DWORD* pdwCount);
//@别名 HP_HTTP代理取所有请求头()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_GetAllHeaders(HP_HttpAgent pAgent, HP_CONNID dwConnID, HP_THeader lpHeaders[], DWORD* pdwCount);
//@别名 HP_HTTP代理取所有请求头名称()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_GetAllHeaderNames(HP_HttpAgent pAgent, HP_CONNID dwConnID, LPCSTR lpszName[], DWORD* pdwCount);

//@别名 HP_HTTP代理置是否使用Cookie()
HPSOCKET_API void __HP_CALL HP_HttpAgent_SetUseCookie(HP_HttpAgent pAgent, BOOL bUseCookie);
//@别名 HP_HTTP代理检查是否使用Cookie()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_IsUseCookie(HP_HttpAgent pAgent);
//@别名 HP_HTTP代理取Cookie()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_GetCookie(HP_HttpAgent pAgent, HP_CONNID dwConnID, LPCSTR lpszName, LPCSTR* lpszValue);
//@别名 HP_HTTP代理取所有Cookie()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_GetAllCookies(HP_HttpAgent pAgent, HP_CONNID dwConnID, HP_TCookie lpCookies[], DWORD* pdwCount);

//@备注 HP_HTTP代理取当前 WebSocket 消息状态，传入 nullptr 则不取相应字段()
//@别名 HP_HTTP代理取当前Web套接字消息状态()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_GetWSMessageState(HP_HttpAgent pAgent, HP_CONNID dwConnID, BOOL* lpbFinal, BYTE* lpiReserved, BYTE* lpiOperationCode, LPCBYTE* lpszMask, ULONGLONG* lpullBodyLen, ULONGLONG* lpullBodyRemain);

//@备注 HP_HTTP代理置 HTTP启动方式（默认：TRUE，自动启动）()
//@别名 HP_HTTP代理置HTTP启动方式()
HPSOCKET_API void __HP_CALL HP_HttpAgent_SetHttpAutoStart(HP_HttpAgent pAgent, BOOL bAutoStart);
//@别名 HP_HTTP代理取HTTP启动方式()
HPSOCKET_API BOOL __HP_CALL HP_HttpAgent_IsHttpAutoStart(HP_HttpAgent pAgent);

/**************************************************************************/
/*************************** HTTP Client 操作方法 **************************/

/*
* 名称：发送请求
* 描述：向服务端发送 HTTP 请求
*		
* 参数：		lpszMethod		-- 请求方法
*			lpszPath		-- 请求路径
*			lpHeaders		-- 请求头
*			iHeaderCount	-- 请求头数量
*			pBody			-- 请求体
*			iLength			-- 请求体长度
* 返回值：	TRUE			-- 成功
*			FALSE			-- 失败
*/
//@别名 HP_HTTP客户端向服务端发送HTTP请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_SendRequest(HP_HttpClient pClient, LPCSTR lpszMethod, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength);

/*
* 名称：发送本地文件
* 描述：向指定连接发送 4096 KB 以下的小文件
*		
* 参数：		dwConnID		-- 连接 ID
*			lpszFileName	-- 文件路径
*			lpszMethod		-- 请求方法
*			lpszPath		-- 请求路径
*			lpHeaders		-- 请求头
*			iHeaderCount	-- 请求头数量
* 返回值：	TRUE			-- 成功
*			FALSE			-- 失败
*/
//@别名 HP_HTTP客户端向指定连接发送本地文件()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_SendLocalFile(HP_HttpClient pClient, LPCSTR lpszFileName, LPCSTR lpszMethod, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount);

/*
* 名称：发送 Chunked 数据分片
* 描述：向对端发送 Chunked 数据分片
*		
* 参数：		pData			-- Chunked 数据分片
*			iLength			-- 数据分片长度（为 0 表示结束分片）
*			lpszExtensions	-- 扩展属性（默认：nullptr）
* 返回值：	TRUE			-- 成功
*			FALSE			-- 失败
*/
//@别名 HP_HTTP客户端发送分块数据分片()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_SendChunkData(HP_HttpClient pClient, const BYTE* pData /*= nullptr*/, int iLength /*= 0*/, LPCSTR lpszExtensions /*= nullptr*/);

//@备注 发送 POST 请求
//@别名 HP_HTTP客户端发送邮件请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_SendPost(HP_HttpClient pClient, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength);
//@备注 发送 PUT 请求
//@别名 HP_HTTP客户端发送上传请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_SendPut(HP_HttpClient pClient, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength);
//@备注 发送 PATCH 请求
//@别名 HP_HTTP客户端发送PATCH请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_SendPatch(HP_HttpClient pClient, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength);
//@备注 发送 GET 请求
//@别名 HP_HTTP客户端发送下载请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_SendGet(HP_HttpClient pClient, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount);
//@备注 发送 DELETE 请求
//@别名 HP_HTTP客户端发送删除请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_SendDelete(HP_HttpClient pClient, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount);
//@备注 发送 HEAD 请求
//@别名 HP_HTTP客户端发送HEAD请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_SendHead(HP_HttpClient pClient, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount);
//@备注 发送 TRACE 请求
//@别名 HP_HTTP客户端发送查找请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_SendTrace(HP_HttpClient pClient, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount);
//@备注 发送 OPTIONS 请求
//@别名 HP_HTTP客户端发送选择请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_SendOptions(HP_HttpClient pClient, LPCSTR lpszPath, const HP_THeader lpHeaders[], int iHeaderCount);
//@备注 发送 CONNECT 请求
//@别名 HP_HTTP客户端发送连接请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_SendConnect(HP_HttpClient pClient, LPCSTR lpszHost, const HP_THeader lpHeaders[], int iHeaderCount);

/*
* 名称：发送 WebSocket 消息
* 描述：向对端端发送 WebSocket 消息
*		
* 参数：		bFinal			-- 是否结束帧
*			iReserved		-- RSV1/RSV2/RSV3 各 1 位
*			iOperationCode	-- 操作码：0x0 - 0xF
*			lpszMask		-- 掩码（nullptr 或 4 字节掩码，如果为 nullptr 则没有掩码）
*			pData			-- 消息体数据缓冲区
*			iLength			-- 消息体数据长度
*			ullBodyLen		-- 消息总长度
* 								ullBodyLen = 0		 -> 消息总长度为 iLength
* 								ullBodyLen = iLength -> 消息总长度为 ullBodyLen
* 								ullBodyLen > iLength -> 消息总长度为 ullBodyLen，后续消息体长度为 ullBOdyLen - iLength，后续消息体通过底层方法 Send() / SendPackets() 发送
* 								ullBodyLen < iLength -> 错误参数，发送失败
* 返回值：	TRUE			-- 成功
*			FALSE			-- 失败
*/
//@别名 HP_HTTP客户端发送Web套接字消息()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_SendWSMessage(HP_HttpClient pClient, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], const BYTE* pData, int iLength, ULONGLONG ullBodyLen);

/*
* 名称：启动 HTTP 通信
* 描述：当通信组件置为非自动启动 HTTP 通信时，需要调用本方法启动 HTTP 通信
*		
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取失败原因
*/
//@别名 HP_HTTP客户端启动HTTP通信()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_StartHttp(HP_HttpClient pClient);

/******************************************************************************/
/*************************** HTTP Client 属性访问方法 **************************/

//@别名 HP_客户端取HTTP状态码()
HPSOCKET_API USHORT __HP_CALL HP_HttpClient_GetStatusCode(HP_HttpClient pClient);

//@别名 HP_客户端置本地协议版本()
HPSOCKET_API void __HP_CALL HP_HttpClient_SetLocalVersion(HP_HttpClient pClient, En_HP_HttpVersion usVersion);
//@别名 HP_客户端取本地协议版本()
HPSOCKET_API En_HP_HttpVersion __HP_CALL HP_HttpClient_GetLocalVersion(HP_HttpClient pClient);

//@别名 HP_客户端检查是否升级协议()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_IsUpgrade(HP_HttpClient pClient);
//@别名 HP_客户端检查是否有TCP检测连接标识()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_IsKeepAlive(HP_HttpClient pClient);
//@别名 HP_客户端取协议版本()
HPSOCKET_API USHORT __HP_CALL HP_HttpClient_GetVersion(HP_HttpClient pClient);
//@别名 HP_客户端取内容长度()
HPSOCKET_API ULONGLONG __HP_CALL HP_HttpClient_GetContentLength(HP_HttpClient pClient);
//@别名 HP_客户端取内容类型()
HPSOCKET_API LPCSTR __HP_CALL HP_HttpClient_GetContentType(HP_HttpClient pClient);
//@别名 HP_客户端取内容编码()
HPSOCKET_API LPCSTR __HP_CALL HP_HttpClient_GetContentEncoding(HP_HttpClient pClient);
//@别名 HP_客户端取传输编码()
HPSOCKET_API LPCSTR __HP_CALL HP_HttpClient_GetTransferEncoding(HP_HttpClient pClient);
//@别名 HP_客户端取协议升级类型()
HPSOCKET_API En_HP_HttpUpgradeType __HP_CALL HP_HttpClient_GetUpgradeType(HP_HttpClient pClient);
//@别名 HP_客户端取解析错误代码()
HPSOCKET_API USHORT __HP_CALL HP_HttpClient_GetParseErrorCode(HP_HttpClient pClient, LPCSTR* lpszErrorDesc);

//@备注 HP_客户端取某个请求头（单值）
//@别名 HP_客户端取某个请求头()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_GetHeader(HP_HttpClient pClient, LPCSTR lpszName, LPCSTR* lpszValue);
//@别名 HP_客户端取某个请求头（多值）()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_GetHeaders(HP_HttpClient pClient, LPCSTR lpszName, LPCSTR lpszValue[], DWORD* pdwCount);
//@别名 HP_客户端取所有请求头()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_GetAllHeaders(HP_HttpClient pClient, HP_THeader lpHeaders[], DWORD* pdwCount);
//@别名 HP_客户端取所有请求头名称()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_GetAllHeaderNames(HP_HttpClient pClient, LPCSTR lpszName[], DWORD* pdwCount);

//@别名 HP_客户端置是否使用Cookie()
HPSOCKET_API void __HP_CALL HP_HttpClient_SetUseCookie(HP_HttpClient pClient, BOOL bUseCookie);
//@别名 HP_客户端检查是否使用Cookie()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_IsUseCookie(HP_HttpClient pClient);
//@别名 HP_客户端取Cookie()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_GetCookie(HP_HttpClient pClient, LPCSTR lpszName, LPCSTR* lpszValue);
//@别名 HP_客户端取所有Cookie()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_GetAllCookies(HP_HttpClient pClient, HP_TCookie lpCookies[], DWORD* pdwCount);

//@备注 取当前 WebSocket 消息状态，传入 nullptr 则不取相应字段
//@别名 HP_客户端取当前Web套接字消息状态()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_GetWSMessageState(HP_HttpClient pClient, BOOL* lpbFinal, BYTE* lpiReserved, BYTE* lpiOperationCode, LPCBYTE* lpszMask, ULONGLONG* lpullBodyLen, ULONGLONG* lpullBodyRemain);

//@备注 置 HTTP 启动方式（默认：TRUE，自动启动）
//@别名 HP_客户端置HTTP启动方式()
HPSOCKET_API void __HP_CALL HP_HttpClient_SetHttpAutoStart(HP_HttpClient pClient, BOOL bAutoStart);
/* 取 HTTP 启动方式 */
//@别名 HP_客户端取HTTP启动方式()
HPSOCKET_API BOOL __HP_CALL HP_HttpClient_IsHttpAutoStart(HP_HttpClient pClient);

/**************************************************************************/
/************************ HTTP Sync Client 操作方法 ************************/

/*
* 名称：发送 URL 请求
* 描述：向服务端发送 HTTP URL 请求
*		
* 参数：		lpszMethod		-- 请求方法
*			lpszUrl			-- 请求 URL
*			lpHeaders		-- 请求头
*			iHeaderCount	-- 请求头数量
*			pBody			-- 请求体
*			iLength			-- 请求体长度
*			bForceReconnect	-- 强制重新连接（默认：FALSE，当请求 URL 的主机和端口与现有连接一致时，重用现有连接）
* 返回值：	TRUE			-- 成功
*			FALSE			-- 失败
*/
//@别名 HP_同步客户端发送URL请求()
HPSOCKET_API BOOL __HP_CALL HP_HttpSyncClient_OpenUrl(HP_HttpSyncClient pClient, LPCSTR lpszMethod, LPCSTR lpszUrl, const HP_THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength, BOOL bForceReconnect);

/*
* 名称：清除请求结果
* 描述：清除上一次请求的响应头和响应体等结果信息（该方法会在每次发送请求前自动调用）
*
* 参数：		
* 返回值：	TRUE			-- 成功
*			FALSE			-- 失败
*/
//@别名 HP_同步客户端清除请求结果()
HPSOCKET_API BOOL __HP_CALL HP_HttpSyncClient_CleanupRequestResult(HP_HttpSyncClient pClient);

/******************************************************************************/
/************************ HTTP Sync Client 属性访问方法 ************************/

//@备注 置连接超时（毫秒，0：系统默认超时，默认：5000） 
//@别名 HP_置同步客户端连接超时()
HPSOCKET_API void __HP_CALL HP_HttpSyncClient_SetConnectTimeout(HP_HttpSyncClient pClient, DWORD dwConnectTimeout);
//@备注 置请求超时（毫秒，0：无限等待，默认：10000）
//@别名 HP_置同步客户端请求超时()
HPSOCKET_API void __HP_CALL HP_HttpSyncClient_SetRequestTimeout(HP_HttpSyncClient pClient, DWORD dwRequestTimeout);

/* 取连接超时 */
//@别名 HP_取同步客户端连接超时()
HPSOCKET_API DWORD __HP_CALL HP_HttpSyncClient_GetConnectTimeout(HP_HttpSyncClient pClient);
/* 取请求超时 */
//@别名 HP_取同步客户端请求超时()
HPSOCKET_API DWORD __HP_CALL HP_HttpSyncClient_GetRequestTimeout(HP_HttpSyncClient pClient);

/* 取响应体 */
//@别名 HP_取同步客户端响应体()
HPSOCKET_API BOOL __HP_CALL HP_HttpSyncClient_GetResponseBody(HP_HttpSyncClient pClient, LPCBYTE* lpszBody, int* piLength);

/**************************************************************************/
/*************************** HTTP Cookie 管理方法 **************************/

//@别名 HP_从文件加载Cookie()
HPSOCKET_API BOOL __HP_CALL HP_HttpCookie_MGR_LoadFromFile(LPCSTR lpszFile, BOOL bKeepExists /*= TRUE*/);
//@备注 HP_保存Cookie到文件
//@别名 HP_保存Cookie到文件()
HPSOCKET_API BOOL __HP_CALL HP_HttpCookie_MGR_SaveToFile(LPCSTR lpszFile, BOOL bKeepExists /*= TRUE*/);
//@别名 HP_清理Cookie()
HPSOCKET_API BOOL __HP_CALL HP_HttpCookie_MGR_ClearCookies(LPCSTR lpszDomain /*= nullptr*/, LPCSTR lpszPath /*= nullptr*/);
//@别名 HP_清理过期Cookie()
HPSOCKET_API BOOL __HP_CALL HP_HttpCookie_MGR_RemoveExpiredCookies(LPCSTR lpszDomain /*= nullptr*/, LPCSTR lpszPath /*= nullptr*/);
//@别名 HP_置Cookie()
HPSOCKET_API BOOL __HP_CALL HP_HttpCookie_MGR_SetCookie(LPCSTR lpszName, LPCSTR lpszValue, LPCSTR lpszDomain, LPCSTR lpszPath, int iMaxAge /*= -1*/, BOOL bHttpOnly /*= FALSE*/, BOOL bSecure /*= FALSE*/, int enSameSite /*= 0*/, BOOL bOnlyUpdateValueIfExists /*= TRUE*/);
//@别名 HP_删除Cookie()
HPSOCKET_API BOOL __HP_CALL HP_HttpCookie_MGR_DeleteCookie(LPCSTR lpszDomain, LPCSTR lpszPath, LPCSTR lpszName);
//@别名 HP_置是否允许第三方Cookie()
HPSOCKET_API void __HP_CALL HP_HttpCookie_MGR_SetEnableThirdPartyCookie(BOOL bEnableThirdPartyCookie /*= TRUE*/);
//@别名 HP_检查是否允许第三方Cookie()
HPSOCKET_API BOOL __HP_CALL HP_HttpCookie_MGR_IsEnableThirdPartyCookie();

//@别名 HP_Cookie失效字符串转换为整数()
HPSOCKET_API BOOL __HP_CALL HP_HttpCookie_HLP_ParseExpires(LPCSTR lpszExpires, __time64_t* ptmExpires);
//@别名 HP_整数转换为Cookie失效字符串()
HPSOCKET_API BOOL __HP_CALL HP_HttpCookie_HLP_MakeExpiresStr(char lpszBuff[], int* piBuffLen, __time64_t tmExpires);
//@别名 HP_生成Cookie字符串()
HPSOCKET_API BOOL __HP_CALL HP_HttpCookie_HLP_ToString(char lpszBuff[], int* piBuffLen, LPCSTR lpszName, LPCSTR lpszValue, LPCSTR lpszDomain, LPCSTR lpszPath, int iMaxAge /*= -1*/, BOOL bHttpOnly /*= FALSE*/, BOOL bSecure /*= FALSE*/, int enSameSite /*= 0*/);
//@别名 HP_取当前UTC时间()
HPSOCKET_API __time64_t __HP_CALL HP_HttpCookie_HLP_CurrentUTCTime();
//@别名 HP_Cookie最大生命周期到过期时间()
HPSOCKET_API __time64_t __HP_CALL HP_HttpCookie_HLP_MaxAgeToExpires(int iMaxAge);
//@别名 HP_Cookie过期时间到最大生命周期()
HPSOCKET_API int __HP_CALL HP_HttpCookie_HLP_ExpiresToMaxAge(__time64_t tmExpires);

/*****************************************************************************************************************************************************/
/************************************************************* HTTP Global Function Exports **********************************************************/
/*****************************************************************************************************************************************************/

#endif

/*****************************************************************************************************************************************************/
/**************************************************************** Thread Pool Exports ****************************************************************/
/*****************************************************************************************************************************************************/

/* Thread Pool 回调函数 */
typedef void (__HP_CALL *HP_FN_ThreadPool_OnStartup)			(HP_ThreadPool pThreadPool);
typedef void (__HP_CALL *HP_FN_ThreadPool_OnShutdown)			(HP_ThreadPool pThreadPool);
typedef void (__HP_CALL *HP_FN_ThreadPool_OnWorkerThreadStart)	(HP_ThreadPool pThreadPool, THR_ID dwThreadID);
typedef void (__HP_CALL *HP_FN_ThreadPool_OnWorkerThreadEnd)	(HP_ThreadPool pThreadPool, THR_ID dwThreadID);

/**********************************************************************************/
/************************** Thread Pool 回调函数置方法 ***************************/

HPSOCKET_API void __HP_CALL HP_Set_FN_ThreadPool_OnStartup(HP_ThreadPoolListener pListener				, HP_FN_ThreadPool_OnStartup fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_ThreadPool_OnShutdown(HP_ThreadPoolListener pListener				, HP_FN_ThreadPool_OnShutdown fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_ThreadPool_OnWorkerThreadStart(HP_ThreadPoolListener pListener	, HP_FN_ThreadPool_OnWorkerThreadStart fn);
HPSOCKET_API void __HP_CALL HP_Set_FN_ThreadPool_OnWorkerThreadEnd(HP_ThreadPoolListener pListener		, HP_FN_ThreadPool_OnWorkerThreadEnd fn);

/****************************************************/
/*******************对象()创建函数 ********************/

//@别名 HP_创建IHP线程池侦听器对象()
HPSOCKET_API HP_ThreadPoolListener __HP_CALL Create_HP_ThreadPoolListener();
//@别名 HP_销毁IHP线程池侦听器对象()
HPSOCKET_API void __HP_CALL Destroy_HP_ThreadPoolListener(HP_ThreadPoolListener pListener);

//@别名 HP_创建IHP线程池对象()（pListener 参数可传入 nullptr）
HPSOCKET_API HP_ThreadPool __HP_CALL Create_HP_ThreadPool(HP_ThreadPoolListener pListener /*= nullptr*/);
//@别名 HP_销毁IHP线程池对象()
HPSOCKET_API void __HP_CALL Destroy_HP_ThreadPool(HP_ThreadPool pThreadPool);

/*
* 名称：创建 TSocketTask对象()
* 描述：创建任务对象()，该对象()最终需由 HP_Destroy_SocketTaskObj() 销毁
*		
* 参数：		fnTaskProc	-- 任务处理函数
*			pSender		-- 发起对象()
*			dwConnID	-- 连接 ID
*			pBuffer		-- 数据缓冲区
*			iBuffLen	-- 数据缓冲区长度
*			enBuffType	-- 数据缓冲区类型（默认：TBT_COPY）
*							TBT_COPY	：（深拷贝）pBuffer 复制到 TSocketTask对象()。此后 TSocketTask对象()与 pBuffer 不再有任何关联
*											-> 适用于 pBuffer 不大或 pBuffer 生命周期不受控的场景
*							TBT_REFER	：（浅拷贝）pBuffer 不复制到 TSocketTask对象()，需确保 TSocketTask对象()生命周期内 pBuffer 必须有效
*											-> 适用于 pBuffer 较大或 pBuffer 可重用，并且 pBuffer 生命周期受控的场景
*							TBT_ATTACH	：（附属）执行浅拷贝，但 TSocketTask对象()会获得 pBuffer 的所有权，并负责释放 pBuffer，避免多次缓冲区拷贝
*											-> 注意：pBuffer 必须由 SYS_Malloc()/SYS_Calloc() 函数分配才能使用本类型，否则可能会发生内存访问错误
*			wParam		-- 自定义参数
*			lParam		-- 自定义参数
* 返回值：	HP_LPTSocketTask
*/
//@别名 HP_T网络套接字任务对象创建()
HPSOCKET_API HP_LPTSocketTask __HP_CALL Create_HP_SocketTaskObj(Fn_SocketTaskProc fnTaskProc, PVOID pSender, HP_CONNID dwConnID, LPCBYTE pBuffer, INT iBuffLen, En_HP_TaskBufferType enBuffType /*= TBT_COPY*/, WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/);

//@别名 HP_T网络套接字任务对象销毁()
HPSOCKET_API void __HP_CALL Destroy_HP_SocketTaskObj(HP_LPTSocketTask pTask);

/***********************************************************************/
/***************************** 组件操作方法 *****************************/

/*
* 名称：启动线程池组件
* 描述：
*		
* 参数：		dwThreadCount		-- 线程数量，（默认：0）
*									>0 -> dwThreadCount
*									=0 -> (CPU核数 * 2 + 2)
*									<0 -> (CPU核数 * (-dwThreadCount))
*			dwMaxQueueSize		-- 任务队列最大容量（默认：0，不限制）
*			enRejectedPolicy	-- 任务拒绝处理策略
*									TRP_CALL_FAIL（默认）	：立刻返回失败
*									TRP_WAIT_FOR			：等待（直到成功、超时或线程池关闭等原因导致失败）
*									TRP_CALLER_RUN			：调用者线程直接执行
*			dwStackSize			-- 线程堆栈空间大小（默认：0 -> 操作系统默认）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取系统错误代码
*/
//@别名 HP_启动线程池组件()
HPSOCKET_API BOOL __HP_CALL HP_ThreadPool_Start(HP_ThreadPool pThreadPool, DWORD dwThreadCount /*= 0*/, DWORD dwMaxQueueSize /*= 0*/, En_HP_RejectedPolicy enRejectedPolicy /*= TRP_CALL_FAIL*/, DWORD dwStackSize /*= 0*/);

/*
* 名称：关闭线程池组件
* 描述：在规定时间内关闭线程池组件，如果工作线程在最大等待时间内未能正常关闭，会尝试强制关闭，这种情况下很可能会造成系统资源泄漏
*		
* 参数：		dwMaxWait	-- 最大等待时间（毫秒，默认：INFINITE，一直等待）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取系统错误代码
*/
//@别名 HP_关闭线程池组件()
//@备注 在规定时间内关闭线程池组件，如果工作线程在最大等待时间内未能正常关闭，会尝试强制关闭，这种情况下很可能会造成系统资源泄漏
HPSOCKET_API BOOL __HP_CALL HP_ThreadPool_Stop(HP_ThreadPool pThreadPool, DWORD dwMaxWait /*= INFINITE*/);

/*
* 名称：提交任务
* 描述：向线程池提交异步任务
*		
* 参数：		fnTaskProc	-- 任务处理函数
*			pvArg		-- 任务参数
*			dwMaxWait	-- 任务提交最大等待时间（仅对 TRP_WAIT_FOR 类型线程池生效，默认：INFINITE，一直等待）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取系统错误代码
*							其中，错误码 ERROR_DESTINATION_ELEMENT_FULL 表示任务队列已满
*/
//@别名 HP_向线程池提交异步任务()
HPSOCKET_API BOOL __HP_CALL HP_ThreadPool_Submit(HP_ThreadPool pThreadPool, HP_Fn_TaskProc fnTaskProc, PVOID pvArg, DWORD dwMaxWait /*= INFINITE*/);

/*
* 名称：提交 Socket 任务
* 描述：向线程池提交异步 Socket 任务
*		
* 参数：		pTask		-- 任务参数
*			dwMaxWait	-- 任务提交最大等待时间（仅对 TRP_WAIT_FOR 类型线程池生效，默认：INFINITE，一直等待）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取系统错误代码
*							其中，错误码 ERROR_DESTINATION_ELEMENT_FULL 表示任务队列已满
*							注意：如果提交失败，需要手工调用 Destroy_HP_SocketTaskObj() 销毁 TSocketTask对象()
*/
//@别名 HP_向线程池提交异步套接字任务()
//@备注 向线程池提交异步 Socket 任务
HPSOCKET_API BOOL __HP_CALL HP_ThreadPool_Submit_Task(HP_ThreadPool pThreadPool, HP_LPTSocketTask pTask, DWORD dwMaxWait /*= INFINITE*/);

/*
* 名称：调整线程池大小
* 描述：增加或减少线程池的工作线程数量
*		
* 参数：		dwNewThreadCount	-- 线程数量
*									>0 -> dwNewThreadCount
*									=0 -> (CPU核数 * 2 + 2)
*									<0 -> (CPU核数 * (-dwNewThreadCount))
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取系统错误代码
*/
//@别名 HP_调整线程池大小()
//@备注 增加或减少线程池的工作线程数量
HPSOCKET_API BOOL __HP_CALL HP_ThreadPool_AdjustThreadCount(HP_ThreadPool pThreadPool, DWORD dwNewThreadCount);

/*
* 名称：等待
* 描述：等待线程池组件停止运行
*		
* 参数：		dwMilliseconds	-- 超时时间（毫秒，默认：-1，永不超时）
* 返回值：	TRUE	-- 成功
*			FALSE	-- 失败，可通过 SYS_GetLastError() 取错误代码
*/
//@别名 HP_线程池等待()
//@备注 等待线程池组件停止运行
HPSOCKET_API BOOL __HP_CALL HP_ThreadPool_Wait(HP_ThreadPool pThreadPool, DWORD dwMilliseconds);

/***********************************************************************/
/***************************** 属性访问方法 *****************************/

//@别名 HP_检查线程池组件是否已启动()
HPSOCKET_API BOOL __HP_CALL HP_ThreadPool_HasStarted(HP_ThreadPool pThreadPool);
//@别名 HP_查看线程池组件当前状态()
HPSOCKET_API En_HP_ServiceState	__HP_CALL HP_ThreadPool_GetState(HP_ThreadPool pThreadPool);
//@别名 HP_取当前任务等待队列大小()
HPSOCKET_API DWORD __HP_CALL HP_ThreadPool_GetQueueSize(HP_ThreadPool pThreadPool);
//@别名 HP_取当前正在执行的任务数量()
HPSOCKET_API DWORD __HP_CALL HP_ThreadPool_GetTaskCount(HP_ThreadPool pThreadPool);
//@别名 HP_取工作线程数量()
HPSOCKET_API DWORD __HP_CALL HP_ThreadPool_GetThreadCount(HP_ThreadPool pThreadPool);
//@别名 HP_取任务队列最大容量()
HPSOCKET_API DWORD __HP_CALL HP_ThreadPool_GetMaxQueueSize(HP_ThreadPool pThreadPool);
//@别名 HP_取任务拒绝处理策略()
HPSOCKET_API En_HP_RejectedPolicy __HP_CALL HP_ThreadPool_GetRejectedPolicy(HP_ThreadPool pThreadPool);
