//@模块名称 内存模块加载器
//@版本  0.1.1
//@日期  2022-08-06
//@作者  欧阳逸洛 
//@模块备注 直接从内存加载动态链接库
// 仓库地址：https://gitee.com/ouyang-yiluo/xpl_memory-module-loader
// 包装源：https://github.com/scythe-io/memory-module-loader
//@隐藏{
#include "moduleloader.h"
//@隐藏}

//@src "moduleloader.c"
typedef PLOADEDMODULE 内存模块_模块句柄;
/*@声明

//@别名 内存模块_卸载(模块句柄)
void FreeLibraryResources(PLOADEDMODULE pModule);
//@别名 内存模块_取函数地址(模块句柄,函数名)
FARPROC _GetProcAddress(PLOADEDMODULE pModule, LPCSTR FuncName);
*/


//@返回 加载模块指针
//@别名 内存模块_加载(数据)
static inline PLOADEDMODULE LoadModuleFromMemory(CXBytes& 数据) {
	return LoadModuleFromMemory((void*)(数据.get()), 数据.size());
}
