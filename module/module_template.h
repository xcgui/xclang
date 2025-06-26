#pragma once

#ifdef  XC_MOUDLE
#endif

//@模块名称  测试模板-模板
//@版本  1.0  
//@日期  2020-11-20
//@作者  XCGUI  
//@模块备注  这是一个示例模块

template<typename T>
class SharedPtr : public std::shared_ptr<T>
{
public:
    template<typename U>
    void test(const SharedPtr<U>& other){}
};

struct st_abc123
{
	int  _aa2 [10+10];
};



template  <  class T1  ,  class T2  >
class CA1234
{
public:
	T1  _ca;
	T2  _cb;
	template  <  class T3  ,  class T4  >
	float Test(T3 a, T4 b)
	{
		return a+b;
	}
};


template  <  class T5  ,  class T6  >
T5 Test_abc_fun1(T5 a, T6 b)
{
	return a + (T5)b;
}
	

