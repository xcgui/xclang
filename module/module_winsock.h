#pragma once

//@模块名称  WinSocket
//@版本  1.0.0
//@日期  2023-04-8
//@作者  Bestkakkoii (QQ: 1642687802)
//@QQ  1642687802
//@模块备注 封装自微软(Microsoft) 网路API WinSocket(第一版)，详细请参阅: https://learn.microsoft.com/zh-cn/windows/win32/api/winsock/
//@依赖  module_base.h

#ifndef CXWINSOCK_H
//@隐藏{
#define CXWINSOCK_H
//@隐藏}

#ifndef _WINSOCK2API_
#include <winsock.h>
#pragma comment(lib, "wsock32.lib")
#endif
#pragma comment(lib, "iphlpapi.lib")

//@分组{ winsock2.h补充宏定义
#ifndef _WINSOCK2API_
#define SD_RECEIVE      0x00 //@备注 关闭接收
#define SD_SEND         0x01 //@备注 关闭发送
#define SD_BOTH         0x02 //@备注 关闭接收和发送
#else
#pragma comment(lib, "ws2_32.lib")
#endif
//@分组}

//@分组{ 适配炫彩的地址结构
//
// IPv4 Internet address
// This is an 'on-wire' format structure.
//
//@备注 用于存储IPV4地址(4个无符号字节)
struct in_addr_uchar {
	u_char s_b1;
	u_char s_b2;
	u_char s_b3;
	u_char s_b4;
};

//@备注 用于存储IPV4地址(2个无符号短整型)
struct in_addr_ushort {
	u_short s_w1;
	u_short s_w2;
};

//@备注 用于存储IPV4地址(1个无符号长整型)
struct in_addr_ulong {
	u_long S_addr;
};

struct sockaddr_in_uchar {
        short sin_family; //@备注 指定地址家族，例如AF_INET表示IP地址族
        u_short sin_port; //@备注 端口号，以网络字节序表示
        struct in_addr_uchar sin_addr; //@备注 IP地址，以网络字节序表示
        char sin_zero[8]; //@备注 未使用，用于填充结构体，以满足内存对齐的要求
};

struct sockaddr_in_ushort {
        short sin_family; //@备注 指定地址家族，例如AF_INET表示IP地址族
        u_short sin_port; //@备注 端口号，以网络字节序表示
        struct in_addr_ushort sin_addr; //@备注 IP地址，以网络字节序表示
        char sin_zero[8]; //@备注 未使用，用于填充结构体，以满足内存对齐的要求
};

struct sockaddr_in_ulong {
        short sin_family; //@备注 指定地址家族，例如AF_INET表示IP地址族
        u_short sin_port; //@备注 端口号，以网络字节序表示
        struct in_addr_ulong sin_addr; //@备注 IP地址，以网络字节序表示
        char sin_zero[8]; //@备注 未使用，用于填充结构体，以满足内存对齐的要求
};

typedef struct sockaddr_in_uchar SOCKADDR_IN_UCHAR;
typedef struct sockaddr_in_uchar *PSOCKADDR_IN_UCHAR;
typedef struct sockaddr_in_uchar *LPSOCKADDR_IN_UCHAR;

typedef struct sockaddr_in_ushort SOCKADDR_IN_USHORT;
typedef struct sockaddr_in_ushort *PSOCKADDR_IN_USHORT;
typedef struct sockaddr_in_ushort *LPSOCKADDR_IN_USHORT;

typedef struct sockaddr_in_ulong SOCKADDR_IN_ULONG;
typedef struct sockaddr_in_ulong *PSOCKADDR_IN_ULONG;
typedef struct sockaddr_in_ulong *LPSOCKADDR_IN_ULONG;

/*@声明
//@备注  IP地址结构, 在系统内部是联合体,但是炫语言不支持联合体, 所以具体到实际类型,例如:
// in_addr_ulong,  in_addr_ushort, in_addr_uchar
struct in_addr {
	ULONG S_addr;
};
*/

//@分组}

/*@声明


//@分组{ 类型定义

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr *PSOCKADDR;
typedef struct sockaddr *LPSOCKADDR;

typedef struct linger LINGER;
typedef struct linger *PLINGER;
typedef struct linger *LPLINGER;

//typedef struct fd_set FD_SET;

typedef struct fd_set *PFD_SET;
typedef struct fd_set *LPFD_SET;

typedef struct hostent HOSTENT;
typedef struct hostent *PHOSTENT;
typedef struct hostent *LPHOSTENT;

typedef struct servent SERVENT;
typedef struct servent *PSERVENT;
typedef struct servent *LPSERVENT;

typedef struct protoent PROTOENT;
typedef struct protoent *PPROTOENT;
typedef struct protoent *LPPROTOENT;

typedef struct timeval TIMEVAL;
typedef struct timeval *PTIMEVAL;
typedef struct timeval *LPTIMEVAL;
//@分组}


//@分组{ 基础类型
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;

typedef void *HANDLE;
typedef HANDLE *PHANDLE;

typedef unsigned int UINT_PTR, *PUINT_PTR;

//@别名 套接字
typedef UINT_PTR        SOCKET;

//@分组}

//@分组{ 结构体
//@备注 用于存储一组描述符集的结构体
struct fd_set {
        u_int fd_count; //@备注 描述符集中所包含的描述符数量
        SOCKET fd_array[64]; //@备注 描述符数组，用于存储所有描述符的值
};

//@备注 表示一段时间的结构体
struct timeval {
        long tv_sec; //@备注 秒数部分
        long tv_usec; //@备注 微秒数部分
};

//@备注 用于存储主机信息的结构体
struct hostent {
        char * h_name; //@备注 主机名称
        char ** h_aliases; //@备注 主机别名列表
        short h_addrtype; //@备注 主机地址类型，如AF_INET
        short h_length; //@备注 主机地址的长度，单位为字节
        char ** h_addr_list; //@备注 主机地址列表，以网络字节序存储
        #define h_addr h_addr_list[0] //@备注 用于向后兼容，表示第一个主机地址
};

//@备注 用于存储服务信息的结构体
struct servent {
        char * s_name; //@备注 服务名称
        char ** s_aliases; //@备注 服务别名列表
#ifdef _WIN64
        char * s_proto; //@备注 服务所使用的协议名称
        short s_port; //@备注 服务使用的端口号
#else
        short s_port; //@备注 服务使用的端口号
        char * s_proto; //@备注 服务所使用的协议名称
#endif
};

//@备注 用于存储协议信息的结构体
struct protoent {
        char * p_name; //@备注 协议名称
        char ** p_aliases; //@备注 协议别名列表
        short p_proto; //@备注 协议号
};

//@备注  //@备注 结构体用于描述IP地址和端口号的组合，是socket地址的具体实现
struct sockaddr_in {
        short sin_family; //@备注 指定地址家族，例如AF_INET表示IP地址族
        u_short sin_port; //@备注 端口号，以网络字节序表示
        struct in_addr sin_addr; //@备注 IP地址，以网络字节序表示
        char sin_zero[8]; //@备注 未使用，用于填充结构体，以满足内存对齐的要求
};

//@备注  WSAData 结构体 用于存储网络信息
typedef struct WSAData {
		WORD wVersion; //@备注 版本号的低位字节，表示调用的Winsock DLL的版本号，例如0x0202代表Winsock 2.2。
		WORD wHighVersion; //@备注 版本号的高位字节，表示调用的Winsock DLL的最高版本号，例如0x0202代表Winsock 2.2。
#ifdef _WIN64
		unsigned short iMaxSockets; //@备注 此实现支持打开的套接字数量的最大值。
		unsigned short iMaxUdpDg; //@备注 此实现支持数据报大小的最大值。
		char* lpVendorInfo; //@备注 保留供厂商使用。
		char szDescription[257]; //@备注 描述Winsock实现的字符串。
		char szSystemStatus[129]; //@备注 包含对Winsock实现状态的描述。
#else
		char szDescription[257]; //@备注 描述Winsock实现的字符串。
		char szSystemStatus[129]; //@备注 包含对Winsock实现状态的描述。
		unsigned short iMaxSockets; //@备注 此实现支持打开的套接字数量的最大值。
		unsigned short iMaxUdpDg; //@备注 此实现支持数据报大小的最大值。
		char* lpVendorInfo; //@备注 保留供厂商使用。
#endif
} WSADATA;

typedef WSADATA *LPWSADATA;

//@备注 用于加入多播组的IP地址和本地接口的IP地址
struct ip_mreq {
		struct in_addr imr_multiaddr; //@备注 多播组IP地址。
		struct in_addr imr_interface; //@备注 本地网络接口的IP地址。
};

//@备注 用于表示通用的网络地址结构，包括地址家族和具体地址信息等
struct sockaddr {
	u_short sa_family;     //@备注 指定地址家族，例如AF_INET表示IP地址族
	char sa_data[14];      //@备注 存储地址信息的具体数据，例如IPv4地址和端口号等
};

//@备注 用于表示通用的协议结构，包括协议家族和协议号等
struct sockproto {
	u_short sp_family;     //@备注 与socket地址相同，指定协议族，例如AF_INET表示IP协议族
	u_short sp_protocol;   //@备注 协议号，例如IP协议号为0x0800
};

//@备注 用于设置SO_LINGER选项，用于控制socket关闭后，如果还有未发送完的数据，是否继续等待一段时间再关闭，以及等待时间的长度。
struct linger {
	u_short l_onoff;       //@备注 linger选项是否开启，0表示关闭，非0表示开启
	u_short l_linger;      //@备注 延迟时间，单位为秒
};

//@备注 用于存储文件信息缓冲区结构体
typedef struct _TRANSMIT_FILE_BUFFERS {
	PVOID Head;            //@备注 指向文件内容开始的缓冲区指针
	DWORD HeadLength;      //@备注 缓冲区大小，单位为字节，表示要发送的文件内容的长度
	PVOID Tail;            //@备注 指向文件内容结尾的缓冲区指针
	DWORD TailLength;      //@备注 缓冲区大小，单位为字节，表示要发送的文件内容末尾的额外数据长度
} TRANSMIT_FILE_BUFFERS, *PTRANSMIT_FILE_BUFFERS, *LPTRANSMIT_FILE_BUFFERS;

//@备注 OVERLAPPED用于异步IO
typedef struct _OVERLAPPED {
	ULONG_PTR Internal;    //@备注 内核使用的保留字段
	ULONG_PTR InternalHigh;//@备注 内核使用的保留字段
	DWORD Offset;          //@备注 文件指针偏移量，表示本次IO操作在文件中的起始位置
	DWORD OffsetHigh;      //@备注 文件指针偏移量，表示本次IO操作在文件中的起始位置
	HANDLE  hEvent;        //@备注 句柄，用于关联事件对象，以实现异步通信
} OVERLAPPED, *LPOVERLAPPED;

//@分组}


//@分组{ 宏定义

#define FD_SETSIZE      64 //@备注 常量宏，用于定义fd_set结构体中fd_array数组的大小
#define FD_CLR(fd, set) do {    u_int __i;    for (__i = 0; __i < ((fd_set  *)(set))->fd_count ; __i++) {   if (((fd_set  *)(set))->fd_array[__i] == fd) {  while (__i < ((fd_set  *)(set))->fd_count-1) { ((fd_set  *)(set))->fd_array[__i] =((fd_set *)(set))->fd_array[__i+1]; __i++;  }  ((fd_set  *)(set))->fd_count--;  break;   }    }} while(0) //@备注 从fd_set结构体中删除指定的fd
#define FD_SET(fd, set) do {if (((fd_set*)(set))->fd_count < FD_SETSIZE)((fd_set*)(set))->fd_array[((fd_set*)(set))->fd_count++]=(fd);\} while(0) //@备注 将指定的fd添加到fd_set结构体中
#define FD_ZERO(set) (((fd_set*)(set))->fd_count=0) //@备注 清空fd_set结构体
#define FD_ISSET(fd, set) __WSAFDIsSet((SOCKET)(fd), (fd_set*)(set)) //@备注 判断fd_set结构体中是否包含指定的fd

#define timerisset(tvp)         ((tvp)->tv_sec || (tvp)->tv_usec) //@备注 判断timeval结构体中的tv_sec和tv_usec是否都为0
#define timercmp(tvp, uvp, cmp) ((tvp)->tv_sec cmp (uvp)->tv_sec ||(tvp)->tv_sec == (uvp)->tv_sec && (tvp)->tv_usec cmp (uvp)->tv_usec) //@备注 比较两个timeval结构体中的tv_sec和tv_usec
#define timerclear(tvp)         (tvp)->tv_sec = (tvp)->tv_usec = 0 //@备注 将timeval结构体中的tv_sec和tv_usec都设置为0

#define IOCPARM_MASK    0x7f           //@备注 用于ioctl函数的第三个参数，用于指定参数的长度
#define IOC_VOID        0x20000000     //@备注 用于ioctl函数的第三个参数，用于指定参数的类型为void
#define IOC_OUT         0x40000000     //@备注 用于ioctl函数的第三个参数，用于指定参数的类型为输出
#define IOC_IN          0x80000000     //@备注 用于ioctl函数的第三个参数，用于指定参数的类型为输入
#define IOC_INOUT       (IOC_IN|IOC_OUT) //@备注 用于ioctl函数的第三个参数，用于指定参数的类型为输入输出
#define _IO(x,y) (IOC_VOID|((x)<<8)|(y)) //@备注 定义一个无参数的ioctl命令

#define _IOR(x,y,t) (IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y)) //@备注 定义一个读取参数的ioctl命令

#define _IOW(x,y,t) (IOC_IN|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y)) //@备注 定义一个写入参数的ioctl命令

#define FIONREAD _IOR('f', 127, u_long) //@备注 获取输入缓冲区中的字节数

#define FIONBIO _IOW('f', 126, u_long) //@备注 设置套接字的阻塞/非阻塞模式

#define FIOASYNC _IOW('f', 125, u_long) //@备注 设置套接字的异步通知模式

#define SIOCSHIWAT _IOW('s', 0, u_long) //@备注 设置套接字的高位标志

#define SIOCGHIWAT _IOR('s', 1, u_long) //@备注 获取套接字的高位标志

#define SIOCSLOWAT _IOW('s', 2, u_long) //@备注 设置套接字的低位标志

#define SIOCGLOWAT _IOR('s', 3, u_long) //@备注 获取套接字的低位标志

#define SIOCATMARK _IOR('s', 7, u_long) //@备注 获取TCP连接中是否还有带外数据需要接收

#define IPPROTO_IP 0 //@备注 Internet协议
#define IPPROTO_ICMP 1 //@备注 ICMP协议
#define IPPROTO_IGMP 2 //@备注 IGMP协议
#define IPPROTO_GGP 3 //@备注 GGP协议
#define IPPROTO_TCP 6 //@备注 TCP协议
#define IPPROTO_PUP 12 //@备注 PUP协议
#define IPPROTO_UDP 17 //@备注 UDP协议
#define IPPROTO_IDP 22 //@备注 XNS IDP协议
#define IPPROTO_ND 77 //@备注 UNOFFICIAL net disk protocol

#define IPPROTO_RAW             255 //@备注 Raw IP Packet协议
#define IPPROTO_MAX             256 //@备注 协议最大编号

#define IPPORT_ECHO             7   //@备注 Echo协议端口号
#define IPPORT_DISCARD          9   //@备注 Discard协议端口号
#define IPPORT_SYSTAT           11  //@备注 System Status协议端口号
#define IPPORT_DAYTIME          13  //@备注 Daytime协议端口号
#define IPPORT_NETSTAT          15  //@备注 Network Status协议端口号
#define IPPORT_FTP              21  //@备注 FTP协议端口号
#define IPPORT_TELNET           23  //@备注 Telnet协议端口号
#define IPPORT_SMTP             25  //@备注 SMTP协议端口号
#define IPPORT_TIMESERVER       37  //@备注 Time服务端口号
#define IPPORT_NAMESERVER       42  //@备注 Host Name Server协议端口号
#define IPPORT_WHOIS            43  //@备注 Whois协议端口号
#define IPPORT_MTP              57  //@备注 MTP协议端口号

#define IPPORT_TFTP             69  //@备注 TFTP协议端口号
#define IPPORT_RJE              77  //@备注 Remote Job Entry协议端口号
#define IPPORT_FINGER           79  //@备注 Finger协议端口号
#define IPPORT_TTYLINK          87  //@备注 TTYLINK协议端口号
#define IPPORT_SUPDUP           95  //@备注 SUPDUP协议端口号

#define IPPORT_EXECSERVER       512 //@备注 Remote process execution服务端口号
#define IPPORT_LOGINSERVER      513 //@备注 Remote login服务端口号
#define IPPORT_CMDSERVER        514 //@备注 Remote commands服务端口号
#define IPPORT_EFSSERVER        520 //@备注 Extended File Name Server服务端口号

#define IPPORT_BIFFUDP          512 //@备注 biff服务的UDP端口号
#define IPPORT_WHOSERVER        513 //@备注 who服务端口号
#define IPPORT_ROUTESERVER      520 //@备注 路由服务器服务端口号

#define IPPORT_RESERVED         1024 //@备注 保留端口号

#define IMPLINK_IP              155 //@备注 ARPA Internet Protocol协议实现
#define IMPLINK_LOWEXPER        156 //@备注 轻型交互体验官协议实现
#define IMPLINK_HIGHEXPER       158 //@备注 重型交互体验官协议实现


#define IN_CLASSA(i)            (((long)(i) & 0x80000000) == 0) //@备注 判断是否为A类IP地址
#define IN_CLASSA_NET           0xff000000 //@备注 A类IP地址的网络号掩码
#define IN_CLASSA_NSHIFT        24 //@备注 A类IP地址的网络号位移量
#define IN_CLASSA_HOST          0x00ffffff //@备注 A类IP地址的主机号掩码
#define IN_CLASSA_MAX           128 //@备注 A类IP地址的最大数量

#define IN_CLASSB(i)            (((long)(i) & 0xc0000000) == 0x80000000) //@备注 判断是否为B类IP地址
#define IN_CLASSB_NET           0xffff0000 //@备注 B类IP地址的网络号掩码
#define IN_CLASSB_NSHIFT        16 //@备注 B类IP地址的网络号位移量
#define IN_CLASSB_HOST          0x0000ffff //@备注 B类IP地址的主机号掩码
#define IN_CLASSB_MAX           65536 //@备注 B类IP地址的最大数量

#define IN_CLASSC(i)            (((long)(i) & 0xe0000000) == 0xc0000000) //@备注 判断是否为C类IP地址
#define IN_CLASSC_NET           0xffffff00 //@备注 C类IP地址的网络号掩码
#define IN_CLASSC_NSHIFT        8 //@备注 C类IP地址的网络号位移量
#define IN_CLASSC_HOST          0x000000ff //@备注 C类IP地址的主机号掩码

#define INADDR_ANY              (u_long)0x00000000 //@备注 任何IP地址
#define INADDR_LOOPBACK         0x7f000001 //@备注 回环IP地址
#define INADDR_BROADCAST        (u_long)0xffffffff //@备注 广播IP地址
#define INADDR_NONE             0xffffffff //@备注 无效IP地址


#define WSADESCRIPTION_LEN      256 //@备注 WSAPROTOCOL_INFO结构体的描述信息长度
#define WSASYS_STATUS_LEN       128 //@备注 WSAPROTOCOL_INFO结构体的系统状态信息长度

#define IP_OPTIONS          1       //@备注 选项设置
#define IP_MULTICAST_IF     2       //@备注 多播接口
#define IP_MULTICAST_TTL    3       //@备注 多播TTL
#define IP_MULTICAST_LOOP   4       //@备注 多播环回
#define IP_ADD_MEMBERSHIP   5       //@备注 加入多播组
#define IP_DROP_MEMBERSHIP  6       //@备注 离开多播组
#define IP_TTL              7       //@备注 IP数据包的TTL
#define IP_TOS              8       //@备注 IP数据包的服务类型
#define IP_DONTFRAGMENT     9       //@备注 数据包是否分片

#define IP_DEFAULT_MULTICAST_TTL   1 //@备注 默认多播TTL
#define IP_DEFAULT_MULTICAST_LOOP  1 //@备注 默认多播环回
#define IP_MAX_MEMBERSHIPS         20 //@备注 支持的最大多播组数量


//@别名 无效的套接字
#define INVALID_SOCKET  (SOCKET)(~0) //@备注 无效的socket
//@别名 套接字错误
#define SOCKET_ERROR            (-1) //@备注 socket操作出错

#define SOCK_STREAM     1           //@备注 流套接字
#define SOCK_DGRAM      2           //@备注 数据报套接字
#define SOCK_RAW        3           //@备注 原始套接字
#define SOCK_RDM        4           //@备注 RDM（可靠数据报）套接字
#define SOCK_SEQPACKET  5           //@备注 顺序包套接字

#define SO_DEBUG        0x0001      //@备注 调试信息
#define SO_ACCEPTCONN   0x0002      //@备注 是否支持连接请求
#define SO_REUSEADDR    0x0004      //@备注 地址重复利用
#define SO_KEEPALIVE    0x0008      //@备注 开启心跳包检测
#define SO_DONTROUTE    0x0010      //@备注 不使用路由
#define SO_BROADCAST    0x0020      //@备注 广播
#define SO_USELOOPBACK  0x0040      //@备注 回环
#define SO_LINGER       0x0080      //@备注 延迟关闭
#define SO_OOBINLINE    0x0100      //@备注 在正常数据流之外发送和接收OOB数据


#define SO_DONTLINGER   (u_int)(~SO_LINGER) //@备注 关闭延迟关闭

#define SO_SNDBUF       0x1001     //@备注 发送缓冲区大小
#define SO_RCVBUF       0x1002     //@备注 接收缓冲区大小
#define SO_SNDLOWAT     0x1003     //@备注 发送低位标记
#define SO_RCVLOWAT     0x1004     //@备注 接收低位标记
#define SO_SNDTIMEO     0x1005     //@备注 发送超时时间
#define SO_RCVTIMEO     0x1006     //@备注 接收超时时间
#define SO_ERROR        0x1007     //@备注 错误状态
#define SO_TYPE         0x1008     //@备注 套接字类型

#define SO_CONNDATA     0x7000     //@备注 连接数据
#define SO_CONNOPT      0x7001     //@备注 连接选项
#define SO_DISCDATA     0x7002     //@备注 断开连接数据
#define SO_DISCOPT      0x7003     //@备注 断开连接选项
#define SO_CONNDATALEN  0x7004     //@备注 连接数据长度
#define SO_CONNOPTLEN   0x7005     //@备注 连接选项长度
#define SO_DISCDATALEN  0x7006     //@备注 断开连接数据长度
#define SO_DISCOPTLEN   0x7007     //@备注 断开连接选项长度


#define SO_OPENTYPE     0x7008     //@备注 打开类型

#define SO_SYNCHRONOUS_ALERT    0x10 //@备注 异步通知方式，且允许在阻塞操作时唤醒 I/O 完成例程
#define SO_SYNCHRONOUS_NONALERT 0x20 //@备注 异步通知方式，但不允许在阻塞操作时唤醒 I/O 完成例程

#define SO_MAXDG        0x7009     //@备注 数据报传输的最大长度
#define SO_MAXPATHDG    0x700A     //@备注 数据报传输的最大路径长度
#define SO_UPDATE_ACCEPT_CONTEXT 0x700B //@备注 接受套接字的上下文
#define SO_CONNECT_TIME 0x700C     //@备注 用于获取套接字的连接时间

#define TCP_NODELAY     0x0001     //@备注 禁用 Nagle 算法
#define TCP_BSDURGENT   0x7000     //@备注 启用 BSD 兼容的紧急模式

#define AF_UNSPEC       0  //@备注 未指定地址族
#define AF_UNIX         1  //@备注 Unix 套接字地址族
#define AF_INET         2  //@备注 IPv4 地址族
#define AF_IMPLINK      3  //@备注 ARPANET IMP 地址族
#define AF_PUP          4  //@备注 PUP 协议地址族
#define AF_CHAOS        5  //@备注 Chaos 地址族
#define AF_IPX          6  //@备注 IPX 地址族
#define AF_NS           6  //@备注 Xerox NS 协议地址族
#define AF_ISO          7  //@备注 ISO 协议地址族
#define AF_OSI          AF_ISO //@备注 OSI 地址族
#define AF_ECMA         8  //@备注 European Computer Manufacturers 地址族
#define AF_DATAKIT      9  //@备注 Datakit 地址族
#define AF_CCITT        10 //@备注 CCITT 地址族
#define AF_SNA          11 //@备注 SNA 地址族
#define AF_DECnet       12 //@备注 DECnet 地址族
#define AF_DLI          13 //@备注 Direct data-link interface 地址族
#define AF_LAT          14 //@备注 LAT 地址族
#define AF_HYLINK       15 //@备注 NSC Hyperchannel 地址族
#define AF_APPLETALK    16 //@备注 AppleTalk 地址族
#define AF_NETBIOS      17 //@备注 NetBios 地址族
#define AF_VOICEVIEW    18 //@备注 VoiceView 地址族
#define AF_FIREFOX      19 //@备注 Firefox 地址族
#define AF_UNKNOWN1     20 //@备注 未知地址族
#define AF_BAN          21 //@备注 Banyan 地址族


#define AF_MAX          22 //@备注 地址族的最大值

#define PF_UNSPEC       AF_UNSPEC //@备注 未指定协议族
#define PF_UNIX         AF_UNIX //@备注 Unix 套接字协议族
#define PF_INET         AF_INET //@备注 IPv4 协议族
#define PF_IMPLINK      AF_IMPLINK //@备注 ARPANET IMP 协议族
#define PF_PUP          AF_PUP //@备注 PUP 协议族
#define PF_CHAOS        AF_CHAOS //@备注 Chaos 协议族
#define PF_NS           AF_NS //@备注 Xerox NS 协议族
#define PF_IPX          AF_IPX //@备注 IPX 协议族
#define PF_ISO          AF_ISO //@备注 ISO 协议族
#define PF_OSI          AF_OSI //@备注 OSI 协议族
#define PF_ECMA         AF_ECMA //@备注 European Computer Manufacturers 协议族
#define PF_DATAKIT      AF_DATAKIT //@备注 Datakit 协议族
#define PF_CCITT        AF_CCITT //@备注 CCITT 协议族
#define PF_SNA          AF_SNA //@备注 SNA 协议族
#define PF_DECnet       AF_DECnet //@备注 DECnet 协议族
#define PF_DLI          AF_DLI //@备注 Direct data-link interface 协议族
#define PF_LAT          AF_LAT //@备注 LAT 协议族
#define PF_HYLINK       AF_HYLINK //@备注 NSC Hyperchannel 协议族
#define PF_APPLETALK    AF_APPLETALK //@备注 AppleTalk 协议族
#define PF_VOICEVIEW    AF_VOICEVIEW //@备注 VoiceView 协议族
#define PF_FIREFOX      AF_FIREFOX //@备注 Firefox 协议族
#define PF_UNKNOWN1     AF_UNKNOWN1 //@备注 未知协议族
#define PF_BAN          AF_BAN //@备注 Banyan 协议族


#define SOL_SOCKET      0xffff //@备注 套接字选项层
#define SOMAXCONN       5      //@备注 侦听的最大连接数

#define MSG_OOB         0x1    //@备注 处理带外数据
#define MSG_PEEK        0x2    //@备注 接收数据但不将其从接收队列中删除
#define MSG_DONTROUTE   0x4    //@备注 不使用路由查找来发送数据

#define MSG_MAXIOVLEN   16     //@备注 支持的 IOV 缓冲区的最大数目

#define MSG_PARTIAL     0x8000 //@备注 接收到的数据是部分的

#define MAXGETHOSTSTRUCT        1024 //@备注 gethostbyname 函数的最大缓冲区长度

#define FD_READ         0x01   //@备注 指示套接字是否可读
#define FD_WRITE        0x02   //@备注 指示套接字是否可写
#define FD_OOB          0x04   //@备注 指示套接字是否有带外数据等待读取
#define FD_ACCEPT       0x08   //@备注 指示监听套接字是否已准备好接受新连接
#define FD_CONNECT      0x10   //@备注 指示是否已成功连接套接字
#define FD_CLOSE        0x20   //@备注 指示是否已关闭套接字


#define h_errno         WSAGetLastError() //@备注 错误代码
#define HOST_NOT_FOUND          WSAHOST_NOT_FOUND //@备注 主机未找到
#define TRY_AGAIN               WSATRY_AGAIN //@备注 请再试一次
#define NO_RECOVERY             WSANO_RECOVERY //@备注 无法恢复
#define NO_DATA                 WSANO_DATA //@备注 无数据记录

#define WSANO_ADDRESS           WSANO_DATA //@备注 无地址记录
#define NO_ADDRESS              WSANO_ADDRESS //@备注 无地址

#define PASCAL __stdcall //@备注 宏定义函数调用方式

#define TF_DISCONNECT       0x01 //@备注 断开连接并在底层套接字上释放本地地址
#define TF_REUSE_SOCKET     0x02 //@备注 重用底层套接字
#define TF_WRITE_BEHIND     0x04 //@备注 允许系统延迟写操作，以优化输出情况下的性能


#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8)) //@备注 将两个 BYTE 组成一个 WORD
#define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16)) //@备注 将两个 WORD 组成一个 LONG
#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff)) //@备注 获取 LONG 的低位 WORD
#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff)) //@备注 获取 LONG 的高位 WORD
#define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff)) //@备注 获取 WORD 的低位 BYTE
#define HIBYTE(w)           ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff)) //@备注 获取 WORD 的高位 BYTE

#define WSAMAKEASYNCREPLY(buflen,error)     MAKELONG(buflen,error) //@备注 为异步突发模式操作的完成创建 LONG 值
#define WSAMAKESELECTREPLY(event,error)     MAKELONG(event,error) //@备注 为选择模式操作的完成创建 LONG 值
#define WSAGETASYNCBUFLEN(lParam)           LOWORD(lParam) //@备注 获取异步突发模式操作的缓冲区长度
#define WSAGETASYNCERROR(lParam)            HIWORD(lParam) //@备注 获取异步突发模式操作的错误代码
#define WSAGETSELECTEVENT(lParam)           LOWORD(lParam) //@备注 获取选择模式操作的事件句柄
#define WSAGETSELECTERROR(lParam)           HIWORD(lParam) //@备注 获取选择模式操作的错误代码


//@分组}

//@分组{ 函数

//@备注 接受一个已经连接的套接字，并返回一个新的套接字用于数据交换
//@参数 s - 一个绑定到本地地址且已经监听的套接字
//@参数 addr - 用来接收远程主机地址信息的缓存区
//@参数 addrlen - 缓存区的长度
//@返回 如果调用成功，返回一个新的客户端套接字；如果调用失败，返回INVALID_SOCKET
//@别名 网络_接受(套接字, IP地址缓存, 缓存长度)
SOCKET PASCAL accept (SOCKET s,struct sockaddr *addr,int *addrlen);

//@备注 将一个套接字与特定的本地地址绑定起来
//@参数 s - 一个已经创建的套接字
//@参数 addr - 指向一个本地地址结构的指针
//@参数 namelen - 指定本地地址结构的长度
//@返回 如果调用成功，则返回0。如果调用失败，则返回SOCKET_ERROR
//@别名 网络_绑定(套接字, 本地地址结构指针, 地址结构长度)
int PASCAL bind (SOCKET s,const struct sockaddr *addr,int namelen);

//@备注 关闭套接字
//@参数 s - 要关闭的套接字
//@返回 如果调用成功，返回0；如果调用失败，返回SOCKET_ERROR
//@别名 网络_关闭套接字(套接字)
int PASCAL closesocket (  SOCKET s);

//@备注 尝试与一个远程套接字建立连接
//@参数 s - 一个绑定到本地地址的套接字
//@参数 name - 指向要连接的套接字的地址结构的指针
//@参数 namelen - 地址结构的长度
//@返回 如果调用成功，返回0；如果调用失败，返回SOCKET_ERROR
//@别名 网络_连接(套接字, 地址指针, 地址长度)
int PASCAL connect (SOCKET s,const struct sockaddr *name,int namelen);

//@备注 设置套接字的IO控制模式
//@参数 s - 目标套接字
//@参数 cmd - 控制命令
//@参数 argp - 控制命令参数
//@返回 如果调用成功，返回0；如果调用失败，返回SOCKET_ERROR
//@别名 网络_设置套接字IO模式(套接字, 控制命令, 参数)
int PASCAL ioctlsocket (SOCKET s,long cmd,u_long *argp);

//@备注 获取套接字对端的地址信息
//@参数 s - 要获取对端地址信息的套接字
//@参数 name - 指向缓存区，用于存储获取的地址信息
//@参数 namelen - 指定缓存区的长度
//@返回 如果调用成功，返回0；如果调用失败，返回SOCKET_ERROR
//@别名 网络_获取对端地址信息(套接字, 地址缓存, 缓存长度)
int PASCAL getpeername (SOCKET s,struct sockaddr *name,int * namelen);

//@备注 获取一个套接字的本地地址信息。
//@参数 s - 套接字描述符
//@参数 name - 用于接收本地地址信息的缓存区
//@参数 namelen - 缓存区的长度
//@返回 如果调用成功，返回0；如果调用失败，返回SOCKET_ERROR
//@别名 网络_获取套接字本地地址(套接字, 地址缓存, 缓存长度)
int PASCAL getsockname (SOCKET s,struct sockaddr *name,int * namelen);

//@备注 获取套接字选项信息
//@参数 s - 套接字描述符
//@参数 level - 选项的协议层
//@参数 optname - 选项名称
//@参数 optval - 存储选项值的缓存区
//@参数 optlen - 缓存区长度
//@返回 如果调用成功，返回0；如果调用失败，返回SOCKET_ERROR
//@别名 网络_获取套接字选项(套接字, 协议层, 选项名, 选项缓存, 缓存长度)
int PASCAL getsockopt (SOCKET s,int level,int optname,char * optval,int *optlen);

//@备注 将32位主机字节序的数值转换为网络字节序的数值。
//@参数 hostlong - 主机字节序的数值
//@返回 转换为网络字节序的数值
//@别名 网络_主机字节序转网络字节序(数值)
u_long PASCAL htonl ( u_long hostlong);

//@备注 将16位端口字节顺序的值转换为16位网络字节顺序的值
//@参数 hostshort - 16位主机字节顺序的值
//@返回 16位网络字节顺序的值
//@别名 网络_端口到网络短整型(主机字节顺序)
u_short PASCAL htons (u_short hostshort);

//@备注 将一个字符串点分十进制的IP地址转换成一个无符号长整型数值。
//@参数 cp - 字符串点分十进制格式的IP地址字符串
//@返回 如果调用成功，返回转换后的无符号长整型数值；如果调用失败，返回INADDR_NONE
//@别名 网络_字符串IP转整型(IP地址字符串)
unsigned long PASCAL inet_addr (const char * cp);

//@备注 将网络字节序的IP地址转换成点分十进制的IP地址
//@参数 in - 一个指向in_addr结构体的指针，其中包含了需要转换的IP地址
//@返回 返回一个指向点分十进制字符串的指针，若出错则返回NULL
//@别名 网络_转换IP地址为字符串(in_addr结构)
char * PASCAL inet_ntoa (struct in_addr in);

//@备注 开始在指定的套接字上监听传入的连接请求
//@参数 s - 绑定到本地地址的套接字描述符
//@参数 backlog - 指定已完成连接队列的最大长度
//@返回 如果调用成功，返回0；如果调用失败，返回SOCKET_ERROR
//@别名 网络_监听连接(套接字, 连接队列长度)
int PASCAL listen (SOCKET s,int backlog);

//@备注 将32位无符号长整型数从网络字节序转换为主机字节序
//@参数 netlong - 需要转换的网络字节序长整型数
//@返回 转换后的主机字节序长整型数
//@别名 网络_网络字节序转主机字节序_长整型(网络长整型数)
u_long PASCAL ntohl (u_long netlong);

//@备注 将网络字节序转换为主机字节序，16位数据
//@参数 netshort - 网络字节序的16位数据
//@返回 返回主机字节序的16位数据
//@别名 网络_网络字节序转主机字节序_16位(网络短整型数)
u_short PASCAL ntohs (u_short netshort);

//@备注 接收指定套接字上的数据
//@参数 s - 套接字描述符
//@参数 buf - 接收数据的缓冲区
//@参数 len - 接收数据缓冲区的长度
//@参数 flags - 接收数据时使用的选项
//@返回 如果调用成功，返回接收到的字节数；如果连接已关闭，返回0；如果调用失败，返回SOCKET_ERROR
//@别名 网络_接收(套接字, 接收缓存, 缓存长度, 选项)
int PASCAL recv (SOCKET s,char * buf,int len,int flags);

//@备注 接收指定套接字上的数据，并存储到缓冲区中。如果缓冲区中没有数据，该函数将被阻塞，直到数据到来
//@参数 s - 套接字描述符
//@参数 buf - 用于存储接收到的数据的缓存区
//@参数 len - 缓存区长度
//@参数 flags - 接收标志
//@参数 from - 用于接收远程主机地址信息的缓存区
//@参数 fromlen - 缓存区长度
//@返回 如果调用成功，返回接收到的字节数；如果连接关闭，返回0；如果调用失败，返回SOCKET_ERROR
//@别名 网络_接收UDP数据(套接字, 缓存区, 缓存长度, 接收标志, 地址缓存, 缓存长度)
int PASCAL recvfrom (
SOCKET s,
char * buf,
int len,
int flags,struct sockaddr * from,int * fromlen);

//@备注 等待一组套接字中的任何一个进入可读、可写或错误就绪状态
//@参数 nfds - 需要检查的最大套接字描述符数目
//@参数 readfds - 套接字描述符集合，检查是否有套接字准备好读取
//@参数 writefds - 套接字描述符集合，检查是否有套接字准备好写入
//@参数 exceptfds - 套接字描述符集合，检查是否有发生异常的套接字
//@参数 timeout - 超时时间（秒和微秒）。如果为 NULL，则表示无限等待
//@返回 函数调用成功时，返回准备就绪描述符的总数（即readfds、writefds和exceptfds中所有准备就绪描述符的总和）；如果超时返回0；如果发生错误返回SOCKET_ERROR
//@别名 网络_等待套接字就绪状态(最大描述符数目, 可读描述符集, 可写描述符集, 异常描述符集, 超时时间)
int PASCAL select (
int nfds,
fd_set *readfds,
fd_set *writefds,
fd_set *exceptfds,
const struct timeval *timeout);

//@备注 发送数据
//@参数 s - 套接字描述符
//@参数 buf - 数据缓存区
//@参数 len - 数据长度
//@参数 flags - 调用方式
//@返回 如果调用成功，则返回已发送的字节数；如果失败，则返回SOCKET_ERROR
//@别名 网络_发送(套接字, 数据缓存区, 数据长度, 调用方式)
int PASCAL send (SOCKET s, const char * buf, int len, int flags);

//@备注 发送数据到指定地址。
//@参数 s - 套接字描述符
//@参数 buf - 指向发送缓存区的指针
//@参数 len - 发送缓存区的长度
//@参数 flags - 标志位
//@参数 to - 指向目标地址的指针
//@参数 tolen - 目标地址长度
//@返回 如果调用成功，返回发送数据的字节数；如果调用失败，返回SOCKET_ERROR
//@别名 网络_发送UDP数据(套接字, 缓存区, 缓存长度, 标志位, 目标地址, 目标地址长度)
int PASCAL sendto (
SOCKET s,
const char * buf,
int len,
int flags,
const struct sockaddr *to,
int tolen);

//@备注 设置指定套接字选项的值
//@参数 s - 套接字描述符
//@参数 level - 选项所在的协议层
//@参数 optname - 选项名
//@参数 optval - 指向包含选项值的缓存区
//@参数 optlen - 缓存区的长度
//@返回 如果调用成功，返回0；如果调用失败，返回SOCKET_ERROR
//@别名 网络_设置套接字选项(套接字, 选项协议层, 选项名, 选项值, 选项值长度)
int PASCAL setsockopt (
 SOCKET s,
 int level,
 int optname,
 const char * optval,
 int optlen);

//@备注 关闭一个已连接的套接字IO
//@参数 s - 套接字描述符
//@参数 how - 关闭方式，0表示禁止发送，1表示禁止接收，2表示禁止双向通信
//@返回 如果调用成功，返回0；如果调用失败，返回SOCKET_ERROR
//@别名 网络_关闭套接字IO(套接字, 关闭方式)
int PASCAL shutdown (SOCKET s, int how);

//@备注 创建一个新的套接字
//@参数 af - 地址族，如AF_INET（TCP/IP IPv4地址族），AF_INET6（TCP/IP IPv6地址族），AF_IRDA（IrDA地址族）等。
//@参数 type - 套接字类型，如SOCK_STREAM（TCP流套接字），SOCK_DGRAM（UDP数据报套接字），SOCK_RAW（原始套接字）等。
//@参数 protocol - 与套接字类型相关的特定协议。通常情况下，此参数为0，以使用默认协议。
//@返回 如果调用成功，返回新套接字的描述符；如果调用失败，返回INVALID_SOCKET。
//@别名 网络_创建套接字(地址族, 套接字类型, 特定协议)
SOCKET PASCAL socket (int af, int type, int protocol);

//@备注 根据IP地址获取主机名信息。
//@参数 addr - IP地址，网络字节序
//@参数 len - 地址长度
//@参数 type - 地址类型，AF_INET、AF_INET6等
//@返回 如果调用成功，返回一个指向hostent结构的指针；如果调用失败，返回NULL
//@别名 网络_根据地址获取主机信息(IP地址, 地址长度, 地址类型)
struct hostent * PASCAL gethostbyaddr(
const char * addr,
int len,
int type);

//@备注 根据主机名称获取主机信息。
//@参数 name - 主机名称
//@返回 如果调用成功，返回主机信息结构体指针；如果调用失败，返回NULL
//@别名 网络_根据主机名获取主机信息(主机名)
struct hostent * PASCAL gethostbyname(const char * name);

//@备注 获取本地计算机主机名。
//@参数 name - 用于接收主机名信息的缓存区
//@参数 namelen - 缓存区的长度
//@返回 如果调用成功，返回0；如果调用失败，返回SOCKET_ERROR
//@别名 网络_获取主机名(主机名缓存, 缓存长度)
int PASCAL gethostname (
char * name,
int namelen);

//@备注 通过给定的端口号和协议类型获取服务信息
//@参数 port - 端口号
//@参数 proto - 协议类型，"tcp" 或 "udp"
//@返回 返回一个指向 servent 结构体的指针，表示获取到的服务信息。如果调用失败，返回 NULL。
//@别名 网络_获取服务信息(端口号, 协议类型)
struct servent * PASCAL getservbyport(
int port,
const char * proto);

//@备注 根据服务名称和协议名称查找服务信息
//@参数 name - 服务名称
//@参数 proto - 协议名称
//@返回 如果查找成功，返回一个指向 servent 结构的指针；如果调用失败，返回 NULL。
//@别名 网络_根据服务名和协议名查找服务信息(服务名, 协议名)
struct servent * PASCAL getservbyname(
const char * name,
const char * proto);

//@备注 根据协议号获取协议信息
//@参数 proto - 协议号
//@返回 返回指向 protoent 结构体的指针，如果失败则返回 NULL。
//@别名 网络_获取协议信息(协议号)
struct protoent * PASCAL getprotobynumber(int proto);

//@备注 根据协议号获取协议信息。
//@参数 proto - 协议号。
//@返回 返回协议信息。
//@别名 网络_通过协议号获取协议信息(协议号)
struct protoent * PASCAL getprotobyname(const char * name);

//@备注 初始化Winsock DLL并指定所需的版本号
//@参数 wVersionRequired - 所需的Winsock版本号
//@参数 lpWSAData - 一个指向WSADATA结构的指针，该结构将接收Winsock启动信息
//@返回 如果成功，则返回0；否则返回错误代码
//@别名 网络_初始化(版本号, WSADATA结构指针)
int PASCAL WSAStartup(WORD wVersionRequired, LPWSADATA lpWSAData);

//@备注 关闭Windows套接字库，释放资源
//@返回 如果调用成功，返回0；如果调用失败，返回错误代码
//@别名 网络_清理()
int PASCAL WSACleanup(void);

//@备注 设置指定的错误代码为最后一次错误
//@参数 iError - 错误代码
//@返回 无
//@别名 网络_设置最后错误码(错误代码)
void PASCAL WSASetLastError(int iError);

//@备注 获取最近一次网络操作的错误码。
//@返回 返回错误码。
//@别名 网络_获取最后错误码()
int PASCAL WSAGetLastError(void);

//@备注 判断当前是否处于阻塞状态
//@返回 如果当前处于阻塞状态，返回TRUE；如果当前没有处于阻塞状态，返回FALSE。
//@别名 网络_判断阻塞状态()
BOOL PASCAL WSAIsBlocking(void);

//@备注 取消阻塞钩子程序的挂钩操作
//@返回 如果调用成功，则返回0，否则返回SOCKET_ERROR
//@别名 网络_取消阻塞钩子挂钩()
int PASCAL WSAUnhookBlockingHook(void);

//@备注 设置阻塞回调函数
//@参数 lpBlockFunc - 指向回调函数的指针
//@返回 如果调用成功，返回以前的回调函数地址；如果调用失败，返回NULL
//@别名 网络_设置阻塞回调函数(回调函数指针)
FARPROC PASCAL WSASetBlockingHook(FARPROC lpBlockFunc);

//@备注 取消所有正在进行的阻塞操作，以及阻塞操作的进程会抛出WSAEINTR异常。
//@返回 如果调用成功，返回0；如果调用失败，返回SOCKET_ERROR
//@别名 网络_取消阻塞回调()
int PASCAL WSACancelBlockingCall(void);

//@备注 异步获取服务端口号对应服务名的操作
//@参数 hWnd - 接收通知消息的窗口句柄
//@参数 wMsg - 通知消息的消息类型
//@参数 name - 服务名
//@参数 proto - 协议名称
//@参数 buf - 用于接收服务名的缓冲区指针
//@参数 buflen - 缓冲区长度
//@返回 返回操作句柄
//@别名 网络_异步名称获取服务端资讯(窗口句柄, 通知消息类型, 服务名, 协议名, 缓冲区, 缓冲区长度)
HANDLE PASCAL WSAAsyncGetServByName(
HWND hWnd,
u_int wMsg,
const char * name,
const char * proto,
char * buf,
int buflen);

//@备注 异步获取服务名字。这个函数发起一个服务名字解析的异步操作，然后立即返回
//@参数 hWnd - 接收通知的窗口句柄
//@参数 wMsg - 用于通知消息的消息标识符
//@参数 name - 服务名字字符串
//@参数 proto - 协议字符串
//@参数 buf - 用于接收结果的缓冲区
//@参数 buflen - 缓冲区长度
//@返回 如果调用成功，返回一个操作句柄；如果调用失败，返回INVALID_HANDLE_VALUE
//@别名 网络_异步端口获取服务端资讯(窗口句柄, 通知消息, 服务名字, 协议名字, 结果缓存, 缓存长度)
HANDLE PASCAL WSAAsyncGetServByPort(
HWND hWnd,
u_int wMsg,
int port,
const char * proto,
char * buf,
int buflen);

//@备注 异步获取指定协议名的协议信息
//@参数 hWnd - 接收消息的窗口句柄
//@参数 wMsg - 接收消息的消息ID
//@参数 name - 要查找的协议名
//@参数 buf - 用于接收协议信息的缓存区
//@参数 buflen - 缓存区长度
//@返回 返回一个句柄，用于取消操作或在操作完成时等待
//@别名 网络_异步名称获取协议信息(窗口句柄, 消息ID, 协议名, 缓存区, 缓存区长度)
HANDLE PASCAL WSAAsyncGetProtoByName(
HWND hWnd,
u_int wMsg,
const char * name,
char * buf,
int buflen);

//@备注 异步获取协议信息，包括协议名称和协议编号。
//@参数 hWnd - 指定窗口句柄，接收异步消息通知。
//@参数 wMsg - 指定自定义消息，用于异步消息通知时的消息参数。
//@参数 name - 协议名称或编号，具体意义由参数"number"或参数"proto"决定。
//@参数 proto - 一个指向协议名称的字符串，或一个指向包含协议名称的指针。
//@参数 number - 一个指向协议编号的整型指针，或一个指向包含协议编号的指针。
//@参数 buf - 接收协议信息的缓存区指针。
//@参数 buflen - 缓存区长度。
//@返回 返回句柄，用于取消异步操作或查询异步操作状态。
//@别名 网络_异步编号获取协议信息(窗口句柄, 消息, 协议名或编号, 协议名称, 协议编号, 结果缓存, 缓存长度)
HANDLE PASCAL WSAAsyncGetProtoByNumber(
 HWND hWnd,
 u_int wMsg,
 int number,
 char * buf,
 int buflen);

//@备注 异步地通过主机名获取主机信息。
//@参数 hWnd - 接收结果的窗口句柄
//@参数 wMsg - 接收结果的消息
//@参数 name - 主机名
//@参数 buf - 用于接收结果的缓存区
//@参数 buflen - 缓存区的长度
//@返回 如果调用成功，返回HANDLE；如果调用失败，返回NULL。
//@别名 网络_异步主机名获取主机信息(窗口句柄, 消息, 主机名, 结果缓存, 缓存长度)
HANDLE PASCAL WSAAsyncGetHostByName(
HWND hWnd,
u_int wMsg,
const char * name,
char * buf,
int buflen);

//@备注 异步获取主机信息，包括主机名和IP地址
//@参数 hWnd - 指定用来接收通知消息的窗口句柄
//@参数 wMsg - 指定接收到通知消息时发送的消息类型
//@参数 name/addr - 指定主机名或IP地址
//@参数 buflen - 缓冲区长度
//@返回 返回句柄以标识请求；如果出现错误，则返回INVALID_HANDLE_VALUE
//@别名 网络_异步IP地址获取主机信息(窗口句柄, 消息类型, IP地址, 缓存区, 缓存长度)
HANDLE PASCAL WSAAsyncGetHostByAddr(
HWND hWnd,
u_int wMsg,
const char * addr,
int len,
int type,
char * buf,
int buflen);

//@备注 取消异步网络请求
//@参数 hAsyncTaskHandle 异步网络请求的句柄
//@返回 如果调用成功，返回0；如果调用失败，返回SOCKET_ERROR
//@别名 网络_取消异步请求(异步请求句柄)
int PASCAL WSACancelAsyncRequest(HANDLE hAsyncTaskHandle);

//@备注 注册异步窗口消息通知事件
//@参数 s - 套接字描述符
//@参数 hWnd - 接收消息的窗口句柄
//@参数 wMsg - 指定的消息类型
//@参数 lEvent - 需要通知的异步事件类型
//@返回 如果调用成功，返回0；如果调用失败，返回SOCKET_ERROR
//@别名 网络_异步窗口消息通知事件(套接字, 窗口句柄, 消息类型, 事件类型)
int PASCAL WSAAsyncSelect(
SOCKET s,
HWND hWnd,
u_int wMsg,
long lEvent);

//@备注 该函数用于在Windows Sockets 2中从套接字接收数据。与recv不同，WSARecvEx函数在套接字上使用I/O完成例程来完成异步处理。除了具有与WSARecv相同的功能外，它还支持控制在接收数据时完成的一些选项。
//@参数 s - 用于接收数据的套接字
//@参数 buf - 指向缓冲区的指针，该缓冲区将包含接收到的数据
//@参数 len - 指定buf指向的缓冲区长度
//@参数 flags - 指定调用选项的附加标志
//@返回 如果调用成功，则返回0；如果失败，则返回SOCKET_ERROR。如果在WSARecvEx完成之前关闭了s，则WSARecvEx将失败，并返回一个错误指示中止操作
//@别名 网络_接收数据扩展(套接字, 数据缓存, 缓存长度, 附加标志)
int PASCAL WSARecvEx (
SOCKET s,
char * buf,
int len,
int *flags);

//@备注 将指定文件中的数据发送到已连接的套接字。
//@参数 hSocket - 已连接的套接字。
//@参数 hFile - 打开并准备发送的文件句柄。
//@参数 nNumberOfBytesToWrite - 发送的字节数。
//@参数 nNumberOfBytesPerSend - 每次发送的字节数。
//@参数 lpOverlapped - 用于异步操作的 OVERLAPPED 结构体指针。
//@参数 lpTransmitBuffers - 用于发送文件头和文件尾的数据缓冲区的指针。
//@参数 dwReserved - 保留，必须为 0。
//@返回 如果函数调用成功，则返回非零值。 如果调用失败，则返回零。
//@别名 网络_发送文件(套接字, 文件句柄, 发送字节数, 每次发送字节数, OVERLAPPED指针, 缓冲区指针, 保留)
BOOL
PASCAL
TransmitFile (
	SOCKET hSocket,
	HANDLE hFile,
	DWORD nNumberOfBytesToWrite,
	DWORD nNumberOfBytesPerSend,
	LPOVERLAPPED lpOverlapped,
	LPTRANSMIT_FILE_BUFFERS lpTransmitBuffers,
	DWORD dwReserved
	);

//@备注 使用I/O操作接受一个传入连接请求，并创建一个新的套接字用于与传入客户端进行通信
//@参数 sListenSocket - 监听套接字
//@参数 sAcceptSocket - 接受传入请求的套接字
//@参数 lpOutputBuffer - 缓冲区指针，用于接收传入数据
//@参数 dwReceiveDataLength - 接收数据长度
//@参数 dwLocalAddressLength - 本地地址信息长度
//@参数 dwRemoteAddressLength - 远程地址信息长度
//@参数 lpdwBytesReceived - 接收到的字节数
//@参数 lpOverlapped - 指向一个重叠体的指针
//@返回 如果调用成功，返回TRUE；如果调用失败，返回FALSE
//@别名 网络_接受扩展(监听套接字, 接收传入请求的套接字, 缓冲区指针, 接收数据长度, 本地地址信息长度, 远程地址信息长度, 接收到的字节数指针, 重叠体指针)
BOOL
PASCAL
AcceptEx (
	SOCKET sListenSocket,
	SOCKET sAcceptSocket,
	PVOID lpOutputBuffer,
	DWORD dwReceiveDataLength,
	DWORD dwLocalAddressLength,
	DWORD dwRemoteAddressLength,
	LPDWORD lpdwBytesReceived,
	LPOVERLAPPED lpOverlapped
	);

//@备注 从AcceptEx返回的结果中提取本地和远程套接字地址信息。
//@参数 lpOutputBuffer - AcceptEx的输出缓冲区指针。
//@参数 dwReceiveDataLength - 接收数据缓冲区的长度。
//@参数 dwLocalAddressLength - 本地套接字地址结构的长度。
//@参数 dwRemoteAddressLength - 远程套接字地址结构的长度。
//@参数 LocalSockaddr - 指向接收本地套接字地址结构的指针。
//@参数 LocalSockaddrLength - 本地套接字地址结构的长度。
//@参数 RemoteSockaddr - 指向接收远程套接字地址结构的指针。
//@参数 RemoteSockaddrLength - 远程套接字地址结构的长度。
//@别名 网络_获取接受扩展返回的本地和远程套接字地址信息(输出缓冲区, 数据缓存区长度, 本地地址长度, 远程地址长度, 本地套接字地址指针, 远程套接字地址指针, 远程套接字地址长度指针)
VOID
PASCAL
GetAcceptExSockaddrs (
	PVOID lpOutputBuffer,
	DWORD dwReceiveDataLength,
	DWORD dwLocalAddressLength,
	DWORD dwRemoteAddressLength,
	struct sockaddr **LocalSockaddr,
	LPINT LocalSockaddrLength,
	struct sockaddr **RemoteSockaddr,
	LPINT RemoteSockaddrLength
	);

//@分组}

//@分组{ 其他
#define s_addr  S_addr //can be used for most tcp & ip code
#define s_host  s_b2 // host on imp
#define s_net   s_b1 // network
#define s_imp   s_w2 // imp
#define s_impno s_b4 // imp #
#define s_lh    s_b3 // logical host
//@分组}

*/

//@分组{ 额外自定义函数
//@备注 获取最后一次错误信息
//@参数 无
//@返回 错误信息
//@别名 网络_获取最后错误信息()
static CXText WINAPI WSAGetLastErrorMessage()
{
        int nError = WSAGetLastError();
        do
        {
                if (nError == 0)
                        break;
                LPWSTR lpMsgBuf = NULL;
                FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL, nError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&lpMsgBuf, 0, NULL);
                if (lpMsgBuf == NULL)
                        break;
                std::wstring strMsg = lpMsgBuf;
                LocalFree(lpMsgBuf);
                return CXText(strMsg.c_str());
        }while(false);
        return L"";
}

//@备注 获取最后一次错误信息A
//@参数 无
//@返回 错误信息
//@别名 网络_获取最后错误信息A()
static CXTextA WINAPI WSAGetLastErrorMessageA()
{
        int nError = WSAGetLastError();
        do
        {
                if (nError == 0)
                        break;
                LPSTR lpMsgBuf = NULL;
                FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL, nError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&lpMsgBuf, 0, NULL);
                if (lpMsgBuf == NULL)
                        break;
                std::string strMsg = lpMsgBuf;
                LocalFree(lpMsgBuf);
                return CXTextA(strMsg.c_str());
        }while(false);
        return "";
}

//@分组}

#endif // CXWINSOCK