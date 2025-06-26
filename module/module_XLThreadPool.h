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
// Created by Huiyi on 2022/10/05.
//
//@模块名称 易炫彩线程池
//@依赖   module_base.h
//@版本   1.0
//@日期   2022-10-05
//@作者   Huiyi
//@模块备注 线程池模块
//使用相关问题可前往QQ群: 594165459 反馈

#ifndef XL_THREAD_POOL_H
//@隐藏{
#define XL_THREAD_POOL_H    //防止复用
#include <map>
#include "ThreadPool.h"
//@隐藏}

#if XC_MOUDLE
#include "module_base.h"
#endif

//@src  "threadpool.cpp"



//@别名	线程池_XH
class ThreadPool_XH {
private:
	ThreadPool* m_tp;
	//@隐藏{
	//std::map<ThreadPoolResult,std::future<ThreadPoolResult>*> m_hash;
	//@隐藏}
public:
	/*@声明
	//@别名	加入任务(线程任务,任务参数)
	ThreadPoolResult enqueue(...);
	*/

	//@别名	终止()
	void Stop();

	//@别名	取线程数()
	int GetThreadSize();

	//@隐藏{
	~ThreadPool_XH();
	ThreadPool_XH();
	ThreadPool_XH(size_t i);
	void enqueue(void* func);
	void enqueue(void* func,long long a);
	void enqueue(void* func, void* a);
	void enqueue(void* func, int i, void* a);
	//@隐藏}
	
};

//@别名	互斥锁_XH
class Mutex_XH {
private:
	std::mutex m_mx;

public:

	//@备注	互斥锁上锁,注意！如果已经上锁则会阻塞！
	//@别名	加锁()
	void Lock();

	//@备注	非阻塞上锁
	//@返回	如果当前已上锁导致无法取得互斥锁则返回假
	//@别名	加锁_非阻塞()
	bool TryLock();

	//@备注	加锁后未解锁会造成死锁
	//@别名	解锁()
	void Unlock();
};


#endif //XL_THREAD_POOL_H
