#pragma once

#ifdef  XC_MOUDLE
#endif

//@模块名称  命名空间模块2
//@版本  1.0  
//@日期  2020-11-20
//@作者  XCGUI  
//@模块备注  这是一个示例模块

//@命名空间      nameB
//@命名空间别名  模块B

//@隐藏{
namespace nameB
{
//@隐藏}
	static int test(int a, int b)
	{
		return  a+b;
	}
	
	
	class CA123
	{
	public:
		int Add(int a, int b){
			return a+b;
		}
	};
//@隐藏{
}
//@隐藏}
