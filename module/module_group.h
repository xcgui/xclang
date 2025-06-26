#pragma once

#ifdef  XC_MOUDLE
#endif

//@模块名称  测试多级分组
//@版本  1.0
//@日期  2024-07-16
//@作者  XCGUI  
//@模块备注
//@依赖 "module_base.h"

#include "module_base.h"

//@分组{ 分组1
int  g_group1=10;	
//@分组}


//@分组{  分组2
int  g_group2=10;
//@分组}


//@分组{  分组1.二级分组1
int  g_group1_1=10;
//@分组}


//@分组{  分组1.二级分组2
int  g_group1_2=10;

class CA123
{
	public:
	int  _a1;
	int  _a2;
	int  add123(int a, int b);
};
//@分组}


//@分组{  分组1.二级分组1.三级分组1
int  g_group1_1_1=10;
//@分组}

//@分组{  分组1.二级分组1.三级分组1
int  g_group1_1_2=10;
//@分组}
