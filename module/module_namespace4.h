#pragma once

//@模块名称  命名空间测试4
//@版本  1.0  
//@日期  2020-11-20
//@作者  XCGUI  
//@模块备注  这是一个示例模块

//@别名 命名空间A
namespace nameA
{
	//@分组{  分组1
	int test_分组1(int a);
	//@分组}
	
		//@别名  test别名()
	static int test(int a, int b)
	{
		return  a+b;
	}
	
	//@分组{   分组1.分组2
	int test_分组2(int a);
	//@分组}
	
}

//@别名 命名空间B
namespace nameB
{
	
	//@分组{  分组1
	int test_分组1(int a);
	//@分组}
	
	static int test(int a, int b)
	{
		return  a+b;
	}
	
	//@分组{  分组2
	int test_分组2(int a);
	//@分组}
	
}


int test(int a);