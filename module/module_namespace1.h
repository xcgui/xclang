#pragma once

#ifdef  XC_MOUDLE
#endif

//@模块名称  命名空间模块1
//@版本  1.0  
//@日期  2020-11-20
//@作者  XCGUI  
//@模块备注  这是一个示例模块

//@命名空间      nameA
//@命名空间别名  模块A

//@隐藏{
namespace nameA
{
//@隐藏}
	static int test(int a, int b)
	{
		return  a+b;
	}

	class CA123
	{
	public:
		static int _var1;
		int Add(int a, int b){
			return a+b;
		}
	};
	template<class T>
	class CATEMP
	{
	public:
		T  _var;
	};

	enum  AASS_{
	AASS_1,
	AASS_2,
	};
	
//@隐藏{
}
//@隐藏}
