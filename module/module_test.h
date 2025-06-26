#pragma once

//@模块名称  测试1
//@版本  1.0  
//@日期  2020-11-20
//@作者  XCGUI  
//@模块备注  这是一个示例模块

static int WINAPI socket123(int af, int type, int protocol)
{
	return 0;
}

//@别名  特殊ADD()
int add123(int a=10, int b=20)
{
	return a+b;
}


/*@声明
int fputs2(const char *str, FILE *stream=stdout);

*/


class CT
{
public:
	RECT* GetRect(){
		return NULL;
	}
};


class CA123
{
public:
	static CT* GetCT(int a, int b){
		return NULL;
	}
};