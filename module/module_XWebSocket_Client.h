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
//@模块名称 易炫彩WebSocket客户端
//@版本   1.0
//@日期   2022-10-28
//@作者   Huiyi
//@QQ    Huiyi
//@模块备注 基于websocketpp的websocket模块封装


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
#include "websocketpp/config/asio_no_tls_client.hpp"
#include "websocketpp/client.hpp"
class XCWebSocketpp;
//@隐藏}

//@解析头文件
#include "ws_help.h"
//@src "websocketClient.cpp"
//@分组{ 辅助类型

//@隐藏{
#define __WS客户端连接标志_ websocketpp::connection<websocketpp::config::asio_client>*
//@隐藏}

//@别名 WS客户端连接标志
typedef __WS客户端连接标志_ XCClientConnectionHanderPtr;

//@分组} 辅助类型
//@分组{ 回调原型

/*@声明

//@别名 WS_回调类型_客户端建立连接(连接指针)
typedef void(*XCClientOpenFunc)(XCClientConnection*);
//@别名 WS_回调类型_客户端关闭连接(连接指针)
typedef void(*XCClientCloseFunc)(XCClientConnection*);
//@别名 WS_回调类型_客户端Ping(连接指针)
typedef bool(*XCClientPingFunc)(XCClientConnection*,const char*);
//@别名 WS_回调类型_客户端Pong(连接指针)
typedef bool(*XCClientPongFunc)(XCClientConnection*,const char*);

*/


//@分组}
//@分组{ 核心类型

//@隐藏{
class XCWebSocketppClient;
//@隐藏}

//@别名 WS客户端操作
class XCClientHandle {
private:
	XCWebSocketppClient* m_client=NULL;
public:

	//@隐藏{
	XCClientHandle(XCWebSocketppClient* c) { m_client = c; };
	//@隐藏}

};

//@别名 WS客户端连接
class XCClientConnection:public XCErrorAutoTry {
private:
	websocketpp::lib::weak_ptr<void> m_connect;
	XCWebSocketppClient* m_appPtr;
public:
	//@隐藏{

	XCClientConnection(XCWebSocketppClient* appPtr, websocketpp::lib::weak_ptr<void> c) {
		m_appPtr = appPtr; m_connect = c;
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
	XCErrorCode ResponseBinary(XCClientConnectionHanderPtr connect, const void* data, size_t dataLen);

	//@备注 取长连接在内存中地址
	//@别名 取连接标志()
	XCClientConnectionHanderPtr GetConnect();

	//@别名 关闭连接(关闭代码,原因)
	bool Close(XCWebSocketCloseStatus code = XCWebSocketCloseStatus(1000), const char* reason = "");


	//@备注 对客户端进行Ping请求,成功客户端返回Pong
	//@别名 Ping(发送载荷)
	bool Ping(const char* payload = "ping");

	//@备注 对客户端进行Pong回复
	//@别名 Pong(发送载荷)
	bool Pong(const char* payload = "ok");


	//@别名 置最后错误(错误信息)
	void SetLastError(const char* str) { m_LastError = str; };
	//@别名 取最后错误()
	CXTextA GetLastError() { GetAutoError(); };

};

/*@声明
//@别名 WS消息_客户端
class XCMessageClient {
	//@备注 取回本次交互中的文本负载
	//@别名 取文本数据A()
	CXTextA& GetTextA();
};
*/

//@隐藏{
typedef XCMessage<websocketpp::client<websocketpp::config::asio_client>::message_ptr>  XCMessageClient;
typedef std::function <void(XCClientConnection*)> XCClientOpenFunc;
typedef std::function <void(XCClientConnection*)> XCClientCloseFunc;
typedef std::function <bool(XCClientConnection*,const char*)> XCClientPingFunc;
typedef std::function <void(XCClientConnection*,const char*)> XCClientPongFunc;
typedef std::function<void(XCClientConnection*, XCMessageClient*)> XCClientMessageFunc;
//@隐藏}

//@别名 WS客户端
class XCWebSocketppClient 
	: public XCErrorAutoTry {
private:
	std::shared_ptr<websocketpp::client<websocketpp::config::asio_client>>m_app;
	websocketpp::client<websocketpp::config::asio_client>::connection_ptr m_connect;
	bool isRun = false;						//是否已经启动
	bool isInit = false;					//是否已经初始化
	std::thread* m_thread = NULL;			//异步下线程
	CXTextA m_Uri;
	XCClientOpenFunc m_onOpen = NULL;		//建立连接回调
	XCClientCloseFunc m_onClose = NULL;		//关闭连接回调 
	XCClientPingFunc m_onPing = NULL;		//被ping时的回调
	XCClientPongFunc m_onPong = NULL;		//有pong时的回调
	XCClientMessageFunc m_onMessage = NULL;	//有消息时的回调
	void RegisterCallbackFunc();
public:
	XCWebSocketppClient();
	~XCWebSocketppClient();
	//@隐藏{
	void onOpen(websocketpp::connection_hdl hdl) {
		if (m_onOpen == nullptr) { return; }
		XCClientConnection co(this, hdl);
		m_onOpen(&co);
	};
	void onClose(websocketpp::connection_hdl hdl) {
		if (m_onClose == nullptr) { return; }
		XCClientConnection co(this, hdl);
		m_onClose(&co);
	};
	bool onPing(websocketpp::connection_hdl hdl,std::string msg) {
		if (m_onPing == nullptr) { return true; }
		XCClientConnection co(this, hdl);
		return m_onPing(&co, msg.c_str());;
	};
	void onPong(websocketpp::connection_hdl hdl, std::string msg) {
		if (m_onPing == nullptr) { return; }
		XCClientConnection co(this, hdl);
		m_onPing(&co, msg.c_str());;
	};
	void onMessage(websocketpp::connection_hdl hdl, 
		websocketpp::client<websocketpp::config::asio_client>::message_ptr msg) {
		if (m_onMessage == nullptr) { return; }
		XCClientConnection co(this, hdl);
		XCMessageClient mesage(msg);
		m_onMessage(&co, &mesage);
	}
	//@隐藏}
	
	//@别名 回调事件_建立连接(事件指针)
	void SetOpenHandler(XCClientOpenFunc func) { m_onOpen = func; };
	//@别名 回调事件_关闭连接(事件指针)
	void SetCloseHandler(XCClientCloseFunc func) { m_onClose = func; };
	//@别名 回调事件_Ping(事件指针)
	void SetPingHandler(XCClientPingFunc func) { m_onPing = func; };
	//@别名 回调事件_Pong(事件指针)
	void SetPongHandler(XCClientPongFunc func) { m_onPong = func; };
	//@别名 回调事件_收到消息(事件指针)
	void SetMessageHandler(XCClientMessageFunc func) { m_onMessage = func; };

	//@别名 取最后错误信息()
	CXTextA& GetLaseError() {return m_LastError;};

	//@别名 连接(地址)
	bool Connect(CXTextA Uri);


	//@备注 运行ws并开始接收消息
	//@别名 运行()
	bool Run();

	//@备注 异步不阻塞的方式运行ws并开始接收消息
	//@别名 运行_异步()
	void RunAsync();

	//@备注 向客户端发送文本。
	// .注意: 如果是中文数据则需要进行UTF-8编码,WebSocket的Text协议不会识别GBK的中文
	//@别名 发送文本A(文本数据)
	bool SendStrA(const char* msg);

	//@别名 取运行状态()
	WSSessionState IfisConnected() { return (WSSessionState)m_connect->get_state(); }
	//@别名 是否启动()
	bool IfisRun() {  
		return m_connect->get_state()== websocketpp::session::state::open
			|| m_connect->get_state() == websocketpp::session::state::connecting;
	}
	//@别名 Ping(负载)
	bool Ping(const char* payload="ping");
	//@别名 Pong(负载)
	bool Pong(const char* payload = "ok");

	//@别名 停止()
	bool Stop();

	//@别名 置最后错误(错误信息)
	void SetLastError(const char* str) { m_LastError = str; };
	//@别名 取最后错误()
	CXTextA GetLastError() { GetAutoError(); };
};

//@分组}




#endif //XL_XWEBSOCKET_H
