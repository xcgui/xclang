#pragma once

//@模块名称  命名空间测试3
//@版本  1.0  
//@日期  2020-11-20
//@作者  XCGUI  
//@模块备注  这是一个示例模块

int  arr_1[] = {1, 2, 3};

//@别名 命名空间A
namespace nameA
{

	static  int  g_var1=100;
	//@别名  test别名()
	static int test(int a, int b)
	{
		return  a+b;
	}

	//@别名 CA123别名
	class CA123
	{
		public:
		static int _var1;
		int Add(int a, int b){
			return a+b;
		}
		static void 控制台暂停(){}
	};
	
	class CA456
	{
		public:
		static CA123  _ca123;
		static CA123* _pca123;
		static int _var1;
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
	
	static int addA(int a, int b){ return 10;}
	
	//@别名 整型2
	typedef  int  myint;
	
	enum enum_flag{
		enum_flag_a=10,
	};
	
	static void 控制台暂停A(){}
}

static int add1(nameA::myint a, int b){ return 10;}

static int add2(int a, int b){ return 10;}

//@别名 命名空间B
namespace nameB
{
	static int test2(int a, int b)
	{
		return  a+b;
	}
	static int addA(int a, int b){ return 10;}
	
	enum enum_flag{
		enum_flag_a=20,
	};
	//@别名 整型3
	typedef  int  myint;
}

static int add3(int a, int b){ return 10;}