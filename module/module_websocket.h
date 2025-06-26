/**
 *                             _ooOoo_
 *                            o8888888o
 *                            88" . "88
 *                            (| -_- |)
 *                            O\  =  /O
 *                         ____/`---'\____
 *                       .'  \\|     |//  `.
 *                      /  \\|||  :  |||//  \
 *                     /  _||||| -:- |||||-  \
 *                     |   | \\\  -  /// |   |
 *                     | \_|  ''\---/''  |   |
 *                     \  .-\__  `-`  ___/-. /
 *                   ___`. .'  /--.--\  `. . __
 *                ."" '<  `.___\_<|>_/___.'  >'"".
 *               | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *               \  \ `-.   \_ __\ /__ _/   .-` /  /
 *          ======`-.____`-.___\_____/___.-`____.-'======
 *                             `=---='
 *          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *                     佛祖保佑        永无BUG
 *            佛曰:
 *                   写字楼里写字间，写字间里程序员；
 *                   程序人员写程序，又拿程序换酒钱。
 *                   酒醒只在网上坐，酒醉还来网下眠；
 *                   酒醉酒醒日复日，网上网下年复年。
 *                   但愿老死电脑间，不愿鞠躬老板前；
 *                   奔驰宝马贵者趣，公交自行程序员。
 *                   别人笑我忒疯癫，我笑自己命太贱；
 *                   不见满街漂亮妹，哪个归得程序员？
 */
#ifndef XC_WEBSOCKET_H
#define XC_WEBSOCKET_H


//@依赖   module_base.h

//@模块名称  WebSocket
//@版本  1.0 
//@日期  2020-07-05
//@作者  回忆(huiyi)
//@模块备注  WebSocket封装
//注意：此库非线程安全，多线程操作请注意加锁！！！
//@依赖  module_base.h

//#include "module_base.h"
#include "easywsclient.hpp"
//@src "websocket.cpp"
//@src "easywsclient.cpp"

#ifdef _WIN32
#pragma comment(lib, "ws2_32" )
#include <WinSock2.h>
#endif

//@别名 WS类
class WebSocketPackage {
private:
    bool bInit = false;

    
    //@隐藏{
    easywsclient::WebSocket::pointer pWs;
    //@隐藏}

public:
    WebSocketPackage();
    WebSocketPackage(CXTextA Uri);
    ~WebSocketPackage();

    //@别名 初始化(地址)
    bool Init(CXTextA Uri);

    void UnInit();

    //@别名 发送(文本信息)
    void Send(CXTextA message);
};

#endif  // XC_WEBSOCKET_H