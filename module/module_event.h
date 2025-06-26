#pragma once

#ifdef  XC_MOUDLE
#endif

//@模块名称  CPP模块事件类演示
//@版本  1.0
//@日期  2022-03-02
//@作者  XCGUI  
//@模块备注  使用事件类, 定义为目标类成员变量, 即可使用IDE的 类成员变量事件函数自动生成与绑定功能

#include "module_base.h"

////////////////////////////////////////////////////
//方式1: 功能与事件处理写在同一个类中

//当该类作为目标类的成员变量时, 若是触发事件, 需要通知目标类绑定的事件接收函数, 
//但是不知道目标类的名称, 无法调用目标类成员函数, 所以需要用到模板, 
//T代表目标类名称, 当代码编译时, 编译器会自动推导出目标类名称

//@别名  事件模块类
template<class T>
class CXEvent_Test
{
public:
	CXEventMgr<T>  m_eventMgr; //用于管理事件

	
	事件定义 void OnEvnet1(int a, int b) //事件响应函数1
	{
		CXEventMgr<T>::xc_bind_event_item_<T>* pEvent = m_eventMgr.FindEvent(L"OnEvnet1"); //这里的名称必须与函数名相同
		if (pEvent)
		{
			typedef  int (T::*funType)(CXEvent_Test<T>&, int, int);
			(pEvent->pObj->*((funType)pEvent->memberFun))(*this, a, b); //调用炫语言类成员变量绑定的事件函数
		}
	}
	
	//@别名  OnEvnet2别名()
	事件定义 int OnEvnet2(int a, int b) //事件响应函数2
	{
		CXEventMgr<T>::xc_bind_event_item_<T>* pEvent = m_eventMgr.FindEvent(L"OnEvnet2");//这里的名称必须与函数名相同
		if (pEvent)
		{
			typedef  int (T::*funType)(CXEvent_Test<T>&, int, int);
			return (pEvent->pObj->*((funType)pEvent->memberFun))(*this, a, b); //调用炫语言类成员变量绑定的事件函数
		}
		return 0;
	}
};


////////////////////////////////////////////////////////////
//方式2: 采用功能类与事件类分离方式, 所有功能都在功能类, 那么传递类指针时用功能类, 就可以跳过模板
class CXMyClass1  //功能实现类
{
public:
	//这里写功能
};

//模块中的类, 用户可绑定成员变量事件
template<class T>
class CXMyClassEvent : public CXMyClass1 //事件类
{
public:
	//这里写事件处理

	CXEventMgr<T>  m_eventMgr; //用于管理事件
	事件定义 void OnEvnet1(int a, int b) //事件响应函数1
	{
		CXEventMgr<T>::xc_bind_event_item_<T>* pEvent = m_eventMgr.FindEvent(L"OnEvnet1"); //这里的名称必须与函数名相同
		if (pEvent)
		{
			typedef  int (T::*funType)(CXMyClassEvent<T>&, int, int);
			(pEvent->pObj->*((funType)pEvent->memberFun))(*this, a, b); //调用炫语言类成员变量绑定的事件函数
		}
	}
	
	事件定义 int OnEvnet2(int a, int b) //事件响应函数2
	{
		CXEventMgr<T>::xc_bind_event_item_<T>* pEvent = m_eventMgr.FindEvent(L"OnEvnet2");//这里的名称必须与函数名相同
		if (pEvent)
		{
			typedef  int (T::*funType)(CXMyClassEvent<T>&, int, int);
			return (pEvent->pObj->*((funType)pEvent->memberFun))(*this, a, b); //调用炫语言类成员变量绑定的事件函数
		}
		return 0;
	}
};

