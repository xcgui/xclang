//================================================
//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永无BUG
//
//
//
//================================================
//
// Created by Huiyi on 2022/10/31.
//
//@模块名称 易炫彩WebSocket服务器
//@版本   1.0
//@日期   2022-10-28
//@作者   Huiyi
//@QQ    Huiyi
//@模块备注 基于websocketpp的websocket服务器模块封装


#pragma once

#ifndef XL_XWEBSOCKET_H
//@隐藏{
#define XL_XWEBSOCKET_H    //防止复用

////_MSC_VER
//#if _MSC_VER<1928
//#ifndef XL_XWEBSOCKET_FORCE_COMPILE
//#error 易炫彩WebSocket支持库: 由于异步IO使用了C++14特性等原因,所以请使用VS2019及以上工具集. 若想强制编译,请定义宏 XL_XWEBSOCKET_FORCE_COMPILE.
//#endif
//#endif


#if XC_MOUDLE
#include "module_base.h"
#endif
#include <thread>
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"
class XCWebSocketpp;
//typedef websocketpp::server<websocketpp::config::asio> XCLServer;
//@隐藏}

//@解析头文件
#include "ws_help.h"

//@src "serverMessage.cpp"
//@src "websocketServer.cpp"
//@src "misc.cpp"
//@src "Connection.cpp"

//@src "ErrorCode.cpp"
//@分组{ 辅助类型

//@隐藏{
#define __WS连接标志_ websocketpp::connection<websocketpp::config::asio>*
//@隐藏}

//@别名 WS连接标志
typedef __WS连接标志_ XCConnectionHanderPtr;

//@分组} 辅助类型
//@分组{ 回调原型

/*@声明

//@别名 WS_回调类型_服务器收到消息(会话指针,消息体)
typedef void(*XCMessageFunc)(XCConnection*, XCMessage*);
//@别名 WS_回调类型_服务器建立连接(会话指针)
typedef void(*XCOpenFunc)(XCConnection*);
//@别名 WS_回调类型_服务器关闭连接(会话指针)
typedef void(*XCCloseFunc)(XCConnection*);
//@别名 WS_回调类型_服务器连接失败(会话指针)
typedef void(*XCFailFunc)(XCConnection*);
//@别名 WS_回调类型_服务器Ping(会话指针,交换信息)
typedef bool(*XCPingFunc)(XCConnection*,const char*);
//@别名 WS_回调类型_服务器Pong(会话指针,交换信息)
typedef void(*XCPongFunc)(XCConnection*,const char*);
//@别名 WS_回调类型_服务器PongTimeOut(会话指针,交换信息)
typedef void(*XCPongTimeOutFunc)(XCConnection*,const char*);
*/



//@分组}
//@分组{ 核心类型

//@别名 WS连接
class XCConnection 
	: public XCErrorAutoTry {
private:
	std::shared_ptr<websocketpp::connection<websocketpp::config::asio>> m_connect;
	XCWebSocketpp* m_appPtr;
public:
	//@隐藏{

	XCConnection(void* appPtr, std::shared_ptr<websocketpp::connection<websocketpp::config::asio>> c) {
		m_appPtr = (XCWebSocketpp*)appPtr; m_connect = c;
	};

	//@隐藏}

	//@备注 获取请求的客户端IP
	//@别名 取客户端IP()
	CXTextA GetClientIP();

	//@备注 获取请求中的uri
	//@别名 取请求URI()
	CXTextA GetUri();

	//@备注 向客户端发送文本。
	// .注意: 如果是中文数据则需要进行UTF-8编码,WebSocket的Text协议不会识别GBK的中文
	//@别名 发送文本A()
	XCErrorCode ResponseStr(CXTextA str);

	//@备注 向客户端发送字节集数据。
	// .注意: 如果是中文数据则需要进行UTF-8编码,WebSocket的Text协议不会识别GBK的中文
	//@别名 发送字节集()
	XCErrorCode ResponseBinary(XCConnectionHanderPtr connect, const void* data, size_t dataLen);

	//@备注 取长连接在内存中地址
	//@别名 取连接标志()
	XCConnectionHanderPtr GetConnect();
	
	//@别名 关闭连接(关闭代码,原因)
	void Close(XCWebSocketCloseStatus code= XCWebSocketCloseStatus(1000), const char* reason = "");


	//@备注 对客户端进行Ping请求,成功客户端返回Pong
	//@别名 Ping(发送载荷)
	void Ping(const char* payload = "ping");

	//@备注 对客户端进行Pong回复
	//@别名 Pong(发送载荷)
	void Pong(const char* payload = "ok");

	//@别名 置最后错误(错误信息)
	void SetLastError(const char* str) { m_LastError = str; };
	//@别名 取最后错误()
	CXTextA GetLastError() { GetAutoError(); };
	
};

/*@声明
//@别名 WS消息_服务器
class XCMessageServer {
	//@备注 取回本次交互中的文本负载
	//@别名 取文本数据A()
	CXTextA& GetTextA();
};
*/

//@隐藏{
typedef XCMessage<websocketpp::server<websocketpp::config::asio>::message_ptr>  XCMessageServer;
typedef std::function<void(XCConnection*, XCMessageServer*)> XCMessageFunc;
typedef std::function <void(XCConnection*)> XCOpenFunc;
typedef std::function <void(XCConnection*)> XCCloseFunc;
typedef std::function <void(XCConnection*)> XCFailFunc;
typedef std::function <void(const char*)> XCLogFunc;
typedef std::function <bool(XCConnection*,const char*)> XCPingFunc;
typedef std::function <void(XCConnection*,const char*)> XCPongFunc;
typedef std::function <void(XCConnection*,const char*)> XCPongTimeOutFunc;
//@隐藏}


//@别名 WS服务器
class XCWebSocketpp
	:public XCErrorAutoTry
{
private:
	//@隐藏{
	std::shared_ptr<websocketpp::server<websocketpp::config::asio>> m_app;
	bool isRun = false;						//是否已经启动
	bool isInit = false;					//是否已经初始化
	std::thread* m_thread = NULL;			//异步下线程
	XCOpenFunc m_onOpen = NULL;				//打开连接回调
	XCCloseFunc m_onClose = NULL;			//关闭连接回调
	XCMessageFunc m_onMessage = NULL;		//收到消息回调
	XCFailFunc m_onFail = NULL;				//连接失败回调
	XCLogFunc m_AccOutFunc=NULL;			//常规日志回调
	XCLogFunc m_ErrOutFunc=NULL;			//错误日志回调
	XCPingFunc m_onPing=NULL;				//Ping回调
	XCPongFunc m_onPong=NULL;				//Pong回调
	XCPongTimeOutFunc m_onPongTimeOut=NULL;	//Pong超时回调
	std::string m_host="";					//绑定端口
	std::string m_service="";				//服务描述
	//std::ostream* m_ErrOutStream=NULL;
	//std::ostream* m_AccOutStream = NULL;
	//WSOutStrBuf m_ErrOut;					//错误日志缓冲区
	//WSOutStrBuf m_AccOut;					//正确日志缓冲区
	void RegisterCallBack();
	//@隐藏}
public:
	//@隐藏{
	//websocketpp::server<websocketpp::config::asio>* m_server;
	//打开连接
	void onOpen(websocketpp::connection_hdl connect) {
		if (m_onOpen == nullptr) { return; }
		XCConnection co(this, m_app->get_con_from_hdl(connect));
		m_onOpen(&co);
	};
	//关闭连接
	void onClose(websocketpp::connection_hdl connect) {
		if (m_onClose == nullptr) { return; }
		XCConnection co(this, m_app->get_con_from_hdl(connect));
		m_onClose(&co);
	};
	//收到消息
	void onMessage(websocketpp::connection_hdl connect,
		websocketpp::server<websocketpp::config::asio>::message_ptr msg) {
		if (m_onMessage == nullptr) { return; }
		XCConnection co(this, m_app->get_con_from_hdl(connect));
		XCMessageServer xmsg(msg);
		m_onMessage(&co, &xmsg);
	};
	//连接失败
	void onFail(websocketpp::connection_hdl connect) {
		if (m_onFail == nullptr) { return; }
		XCConnection co(this, m_app->get_con_from_hdl(connect));
		m_onFail(&co);
	};
	bool onPingCallBackFunc(websocketpp::connection_hdl connect,std::string str) {
		if (m_onPing == nullptr) { return false; }
		XCConnection co(this, m_app->get_con_from_hdl(connect));
		return m_onPing(&co, str.c_str());
	}
	void onPongCallBackFunc(websocketpp::connection_hdl connect, std::string str) {
		if (m_onPong == nullptr) { return; }
		XCConnection co(this, m_app->get_con_from_hdl(connect));
		m_onPong(&co, str.c_str());
	}
	void onPongTimeoutCallBackFunc(websocketpp::connection_hdl connect, std::string str) {
		if (m_onPongTimeOut == nullptr) { return; }
		XCConnection co(this, m_app->get_con_from_hdl(connect));
		m_onPongTimeOut(&co, str.c_str());
	}
	//@隐藏}


	XCWebSocketpp();
	~XCWebSocketpp();

	//@备注 监听前请初始化IO
	//@别名 初始化IO()
	bool InitIO();

	//@备注 监听本机某端口或服务
	//@备注 绑定地址 可以是ip地址也可以是域名, 如127.0.0.1或者0.0.0.0
	//@备注 服务描述 可以是端口也可以是服务, 如8089
	//@别名 绑定服务(绑定地址,服务描述)
	void Listen(CXTextA host, CXTextA services);

	//@备注 运行ws并开始接收消息
	//@别名 运行()
	bool Run();

	//@备注 异步不阻塞的方式运行ws并开始接收消息
	//@别名 运行_异步()
	void RunAsync();
	//@别名 停止()
	bool Stop();
	//@备注 正在运行返回真,否则返回假
	//@别名 取运行状态()
	bool IsRun();
	//@备注 与客户端建立连接时会触发回调
	//@别名 回调事件_建立连接(回调事件)
	void SetOpenHandler(XCOpenFunc func);

	//@备注 关闭连接时的回调
	//@别名 回调事件_关闭连接(回调事件)
	void SetCloseHandler(XCCloseFunc func);

	//@备注 收到消息时的回调
	//@别名 回调事件_收到消息(回调事件)
	void SetMessageHandler(XCMessageFunc func);

	//@备注 建立连接失败时的回调
	//@别名 回调事件_连接失败(回调事件)
	void SetFailHandler(XCCloseFunc func);

	//@备注 Ping时回调
	//@别名 回调事件_Ping(回调事件)
	void SetPingHandler(XCPingFunc func);
	//@备注 Pong时回调
	//@别名 回调事件_Pong(回调事件)
	void SetPongHandler(XCPongFunc func);
	//@备注 Pong超时时回调
	//@别名 回调事件_Pong超时(回调事件)
	void SetPongTimeOutHandler(XCPongTimeOutFunc func);

	//@备注 关闭某一个连接,可以是 WS连接* 也可以是 WS连接取回的连接标志
	//@别名 断开连接(连接标志或连接指针)
	bool CloseConnect(XCConnection* connect, XCWebSocketCloseStatus code = XCWebSocketCloseStatus(1000), const char* msgStr = "");
	//@隐藏{
	bool CloseConnect(XCConnectionHanderPtr connect, XCWebSocketCloseStatus code = XCWebSocketCloseStatus(1000), const char* msgStr = "");
	//@隐藏}
	

	//@备注 向客户端发送文本。
	// .注意: 如果是中文数据则需要进行UTF-8编码,WebSocket的Text协议不会识别GBK的中文
	//@别名 发送文本A(连接标志或连接指针,文本数据)
	XCErrorCode ResponseStrA(XCConnection* connect, const char* str);
	//@隐藏{
	XCErrorCode ResponseStrA(XCConnectionHanderPtr connect, const char* str);
	//@隐藏}

	//@备注 向客户端发送字节集数据。
	//@别名 发送字节集(连接标志或连接指针,字节集数据,字节集长度)
	//@隐藏{
	XCErrorCode ResponseBinary(XCConnection* connect, const void* data, size_t dataLen);
	//@隐藏}
	XCErrorCode ResponseBinary(XCConnectionHanderPtr connect, const void* data, size_t dataLen);

	//@备注 对客户端进行Ping请求,成功客户端返回Pong
	//@别名 Ping(连接标志或连接指针,发送载荷)
	bool Ping(XCConnection* connect, const char* payload ="ping");
	//@隐藏{
	bool Ping(XCConnectionHanderPtr connect, const char* payload = "ping");
	//@隐藏}
	
	//@备注 对客户端进行Pong回复
	//@别名 Pong(连接标志或连接指针,发送载荷)
	bool Pong(XCConnection* connect, const char* payload = "ok");
	//@隐藏{
	bool Pong(XCConnectionHanderPtr connect, const char* payload = "ok");
	//@隐藏}

	//@别名 置最后错误(错误信息)
	void SetLastError(const char* str) { m_LastError = str; };
	//@别名 取最后错误()
	CXTextA GetLastError() { GetAutoError(); };

};



//@分组}




#endif //XL_XWEBSOCKET_H
