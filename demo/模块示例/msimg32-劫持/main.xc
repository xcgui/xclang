
// 这是对 32 位的 msimg32.dll 的劫持源码  南小鱼 QQ128492656
#头文件	"msimg32.cpp" 


#嵌入代码
namespace AheadLib
{

BOOL WINAPI Load();
VOID WINAPI Free();
}
#嵌入代码_结束


函数 整型 入口函数_动态库()


	如果 DLL_进程附加 == 被调用原因
		#嵌入代码
		
		DisableThreadLibraryCalls(模块句柄);
		AheadLib::Load();
		#嵌入代码_结束
		消息框("加载dll成功,这是对 32 位的 msimg32.dll 的劫持源码  南小鱼 QQ128492656")
		占位

	否则 DLL_线程附加 == 被调用原因
		占位
	否则 DLL_线程分离 == 被调用原因
		占位
	否则 DLL_进程分离 == 被调用原因
		#嵌入代码
		AheadLib::Free();
		#嵌入代码_结束
		消息框("dll退出,这是对 32 位的 msimg32.dll 的劫持源码  南小鱼 QQ128492656")
		占位
	返回 真 //成功返回真

//动态库入口函数参考
//https://docs.microsoft.com/zh-cn/windows/win32/dlls/dllmain?redirectedfrom=MSDN