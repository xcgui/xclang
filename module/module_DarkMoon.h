
#ifndef  XCL_DARKMOON_H
//@隐藏{
#define  XCL_DARKMOON_H
//@隐藏}

//@模块名称  黑月界面类模块
//@版本  1.0
//@日期  2024-08-07
//@作者  情缘,易团雪,技术支持:逸辰Arne等群内大佬  
//@QQ 283279437
//@模块备注 本模块翻译与整理自易语言黑月界面类,可以无缝复制粘贴即可调用.并适配了DPI缩放
//1:控件不能声明局部变量,否则程序GG.实在要局部变量请加静态属性或者使用指针如:按钮类 *局部按钮 = new 按钮类
//2:目前很多命令都没有测试过,如发现问题请反馈.或自行修复
//3:封装已完成百分之90左右
//4:有机会在重构框架吧,目前就这样了

//@依赖  module_base.h,module_gdiplus.h
//@src "module_DarkMoon.cpp"

#if XC_MOUDLE
#include "module_base.h"
#include "module_gdiplus.h"
#endif

#pragma once
// 添加要在此处预编译的标头
//#include "TEventManage.h"
#include <CommCtrl.h>
#pragma comment (lib,"Comctl32.lib")

#include <Commdlg.h>
#pragma comment (lib,"comdlg32.lib")

//@解析头文件
#include "TWindowStyles.h"

//@分组{ 全局函数

//@别名 取功能键()
int TGetModifierKeys();

POINT 黑月坐标(int x, int y);

HMENU 黑月默认ID();
struct 黑月热键信息{
	BYTE 键代码;
	BYTE 功能键; //@备注 “热键框_”开头常量组合。
};
struct 黑月IP地址{
	BYTE D段;
	BYTE C段;
	BYTE B段;
	BYTE A段;
};
struct 黑月超列信息{
	CXText 标题; //@备注 本参数指定表项的标题文本(也即是第0列的标题)。
	int 图片索引; //图片索引用于指定“图片组”属性中的某张图片。索引值从 0 开始，-1 表示无图片。
	int 状态图片索引; //状态图片索引用于指定“状态图片组”属性中的某张图片。索引值从 0 开始，-1 表示无图片。
	vint 表项数值; //该数值与指定表项相关联。
	int 缩进数目; //“缩进数目”仅在报表型列表框才有效，用作指定显示时在表项首部增加的空白数。
	CXVector<CXText>  列标题; //从第1列开始计起的列标题，多列请按列索引次序依次写到相应的数组成员中
	CXVector<int>  列图片索引; //从第1列开始计起，可以被省略。图片索引用于指定“图片组”属性中的某张图片。索引值从 0 开始，-1 表示无图片。如果本参数被省略，默认值为 -1 。
};
struct 黑月树型框信息{
	INT_PTR 父项目句柄;
	CXText 项目文本;
	int 图片索引;
	int 选中图片索引;
	INT_PTR 项目数值;
};
/*@声明
//@别名 黑月快捷键信息
typedef struct tagACCEL {
  BYTE fVirt;//@别名 功能键状态
  WORD key;  //@别名 键代码
  WORD cmd; //@别名 ID
} ACCEL;
*/

//@别名 DPI取缩放值()
INT TGetDpiValue();
//@别名 DPI适配尺寸()
INT TAdapterDPI(INT Isize,INT _DPI);
//@隐藏{

// 抽象基类定义
class MemberFunctionCallerBase {
public:
    virtual ~MemberFunctionCallerBase() = default;
    virtual void Call() = 0;
};

// 通用类模板定义
template<typename R, typename... Args>
class MemberFunctionCaller : public MemberFunctionCallerBase {
private:
    std::function<R(Args...)> func; // 使用 std::function 存储可调用对象
public:
    // 构造函数，保存类成员函数指针
    template<typename C>
    MemberFunctionCaller(C* object, R(C::* memberFunc)(Args...)) {
        func = [object, memberFunc](Args... args) -> R {
            return (object->*memberFunc)(args...);
        };
    }

    // 构造函数，保存普通函数指针
    MemberFunctionCaller(R(__stdcall* freeFunc)(Args...)) {
        func = freeFunc;
    }

    // 调用函数
    R Call(Args... arguments) {
        return func(arguments...);
    }

    void Call() override {
        // 不使用实际参数进行调用的占位实现
        // 你可以选择抛出异常或输出错误消息
    }
};

// 工厂函数用于创建 MemberFunctionCaller 对象的指针
template<typename C, typename R, typename... Args>
MemberFunctionCallerBase* make_member_function_caller(C* object, R(C::* func)(Args...)) {
    return new MemberFunctionCaller<R, Args...>(object, func);
}

template<typename R, typename... Args>
MemberFunctionCallerBase* make_member_function_caller(R(__stdcall* func)(Args...)) {
    return new MemberFunctionCaller<R, Args...>(func);
}

// yyy__event 类定义
class TRegEvent {
public:
    // 变量定义
    int lx = 0;
    MemberFunctionCallerBase* m_pBind = nullptr;     // C++ 事件回调
    MemberFunctionCallerBase* m_pFunC = nullptr;     // C 事件回调
    char m_name[MAX_PATH]; // 函数名
    vint hwnd;

    TRegEvent(int jb, const char* pFunName) : lx(jb) {
        strncpy_s(m_name, pFunName, MAX_PATH);
    }

    // 检查事件类是否存在，是否注册了相关函数
    BOOL 检查事件类(TRegEvent* pEvent) {
        return pEvent != nullptr && (pEvent->m_pBind != nullptr || pEvent->m_pFunC != nullptr);
    }

    // 检查函数C是否存在
    BOOL 检查C(void* pFunc) {
        return pFunc != nullptr;
    }

    // 回调事件0个变整型参数//evtPtr->调用<返回值>(参数);
    template<typename t, typename... Args>
    t 调用(Args... args) {
        if (m_pBind) return static_cast<MemberFunctionCaller<t, Args...>*>(m_pBind)->Call(args...);
        if (m_pFunC) return static_cast<MemberFunctionCaller<t, Args...>*>(m_pFunC)->Call(args...);
        return 0;
    }

    // 取已注册函数名或类函数名
    char* 取函数名() {
        return m_name;
    }

    // 清除已经注册的相关函数信息
    void 清除() {
        delete m_pBind;
        delete m_pFunC;
        m_pBind = nullptr;
        m_pFunC = nullptr;
    }
};
// 注册CPP事件函数
template<typename R, typename C,  typename... Args>
vint TRegEventCPP_tt_c(C* c, R(C::* func)(Args...), const char* pFunName) {
    MemberFunctionCallerBase* pBind =new  MemberFunctionCaller<R, Args...>(c, func);
    TRegEvent* pEvent = new TRegEvent(0, pFunName);
    pEvent->m_pBind = pBind;
    return (vint)pEvent;
}
template<typename R, typename C, typename... Args>
vint  TRegEventCPP_t_a(C* object, R(C::* func)(Args...), const char* pFunName) {
    return TRegEventCPP_tt_c<R>(object, func, pFunName);
}
// 注册事件函数
template<typename R, typename... Args>
vint TRegEventC_tt_c(R(__stdcall* func)(Args...), const char* pFunName) {
    MemberFunctionCallerBase* pBind = new MemberFunctionCaller<R, Args...>(func);
    TRegEvent* pEvent = new TRegEvent(0, pFunName);
    pEvent->m_pBind = pBind;
    return (vint)pEvent;
}
template<typename R, typename... Args>
vint  TRegEventC_t_a(R(__stdcall* func)(Args...), const char* pFunName) {
    return TRegEventC_tt_c<R>(func, pFunName);
}

#define TNULLVectorUINT64 CXVector<UINT64>()
//@隐藏}

//@备注 注册C函数使用
//函数支持任意类型
//@别名 注册事件C_取地址(事件函数)
#define TRegEventC_Ptr(mFun)  TRegEventC_t_a(mFun,#mFun)
//@备注 注册类回调使用,取得事件类地址,需要使用类名一起，如:&类名::函数名
//函数支持任意类型
//@别名 注册事件CPP_取地址(事件函数)
#define TRegEventCPP_Ptr(mFun)  TRegEventCPP_t_a(this,mFun,#mFun)

//@分组}

//@分组{ 界面入口

class TMenu;
class zyform;
class TAccelTable;
class zyCtrol;
class ThIcon;
class TMonthCal;
class TEditBox;
class TMDIChildFrame;
class TListBox;
//@别名 应用程序类
class TApplications {
private:
	ULONG_PTR m_pGdiToken;
	void init();
public:
	//@隐藏{
	int AtlAxWinInit_();
	TApplications();

	//@隐藏}
	void 结束();
	//@参数 如果是写DLL，需要设置DLL的实例句柄hInstance
	//@参数 AtlAxWinInit 默认为：真
	//@参数 "通用控件类_"开头常量组合，默认为：全部
	//@备注 必须先初始化
	void 初始化(HINSTANCE 实列句柄 = NULL,bool 参数_使用ATL = true, DWORD 参数_通用控件类 = 0);
	//@参数 要运行的窗口
	//@参数 是否显示窗口，默认为：真
	//@备注 窗口的消息循环，控制整个程序的消息
	int 运行(zyform &bform,BOOL Bshow = true);
	//@备注 返回数组成员数
	int 取命令行(CXVector<CXText>& 参数_命令行参数);
	//@别名 取程序文件名()
	CXText GetFileName();
	//@别名 取程序路径()
	CXText GetRoute();
	//@别名 取程序目录()
	CXText GetDirectory();
};
//@分组}

//@分组{ 控件入口.界面基类
//@隐藏{
class zyObject {
public:
	zyObject() :m_pRefCount(new size_t(1)), m_pData(new	CXMap<CXText, vint>()) {}

	zyObject(const zyObject& other) {
		m_pData = other.m_pData;
		m_pRefCount = other.m_pRefCount;
		addRef();
	}

	~zyObject() { release(); }


	zyObject& operator=(const zyObject& other) {
		release();
		if (this != &other) {
			m_pData = other.m_pData;
			m_pRefCount = other.m_pRefCount;
			addRef();
		}
		return *this;
	}

	size_t addRef() {
		return InterlockedIncrement(m_pRefCount);
	}

	size_t release() {
		size_t n = InterlockedDecrement(m_pRefCount);
		if (n == 0) {
			delete m_pData;
			delete m_pRefCount;
		}
		return n;
	}

	CXMap<CXText, vint>* GetData() {
		return m_pData;
	}

private:
	size_t* m_pRefCount;
	CXMap<CXText, vint>* m_pData;
};
//@隐藏}
class zyBase
{
private:
	zyObject mObject;

public:
	zyObject GetObject() {
		return mObject;
	}

	void SetObject(const zyObject& object) {
		mObject = object;
	}
	BOOL HasMember(CXText name);
	void SetName(CXText Name);
	CXText GetName();
	void SetMember(CXText name, vint value);
	vint GetMember(CXText name);
	BOOL RemoveMember(CXText name);
	//@隐藏{
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam,bool* bHandle);
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual void OnNCDestroy();
	virtual void Destroy();
	void OnSize(HWND hWnd, int cx, int cy);
	//int CallDefultProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	//@隐藏}
};
//@隐藏{
class resObject;

typedef void(WINAPI* FnResDestroy)(resObject*);

class resObject {
private:
	LPVOID m_pSelf;
	size_t* m_refCount;
	LONG_PTR* m_pData;

	FnResDestroy m_fnDestroy;

	resObject() : m_pSelf(this),
				  m_refCount(new size_t(1)),
				  m_pData(new LONG_PTR[16]),
				  m_fnDestroy(nullptr) {}

	~resObject() {
		m_pSelf = nullptr;
		delete m_refCount;
		delete[] m_pData;
		m_pData = nullptr;
		m_fnDestroy = nullptr;
	}

public:
	static resObject* Create() { return new resObject(); }

public:
	void setDestroy(FnResDestroy fnDestroy) { m_fnDestroy = fnDestroy; }
	void callDestroy() {
		if (m_fnDestroy)
			m_fnDestroy(this);
	}

	BOOL checkSelf() const { return m_pSelf == this; }

	size_t getRefCount() const { return *m_refCount; }

	size_t addRef() { return InterlockedIncrement(m_refCount); };

	size_t release() {
		size_t count = InterlockedDecrement(m_refCount);
		if (count == 0) {
			if (m_fnDestroy)
				m_fnDestroy(this);
			delete this;
		}
		return count;
	}

	BOOL setDataValue(LONG_PTR value, size_t index = 0) {
		if (index >= 16) return FALSE;
		m_pData[index] = value;
		return TRUE;
	}

	LONG_PTR getDataValue(size_t index = 0) {
		if (index < 16) return m_pData[index];
		return 0;
	}

	LONG_PTR* getDataPtr() { return m_pData; }
};	
//@隐藏}
class zyRes
{
private:
	std::map<const wchar_t*, void*> Res数据绑定;

protected:
	resObject* m_obj;

public:
	zyRes() : m_obj(resObject::Create()) {
		m_obj->setDestroy((FnResDestroy)zyRes_Destroy);
	}
	~zyRes() { m_obj->release(); }

	resObject* getObject(BOOL bAddRef = FALSE) const {
		if (bAddRef) m_obj->addRef();
		return m_obj;
	}

	resObject* 取对象(BOOL 添加引用 = FALSE) const { return getObject(添加引用); }

	BOOL setObject(resObject* newObj, BOOL bAddRef = TRUE) {
		if (newObj == NULL || !m_obj->checkSelf()) return FALSE;
		if (newObj == m_obj) return TRUE;
		m_obj->release();
		m_obj = newObj;
		if (bAddRef) m_obj->addRef();
		return TRUE;
	}

	BOOL 置对象(resObject* 新对象, BOOL 添加引用 = TRUE) { return setObject(新对象, 添加引用); }
	
	void SetMenber(wchar_t* name, void* value);
	void* GetMenber(wchar_t* name);
protected:
	inline static void zyRes_Destroy(resObject* obj){}
};
class zyWindow : public zyBase 
{
public:

	int 信息框(CXText 参数_提示信息,int 参数_按钮 = NULL,CXText 参数_窗口标题 = L"信息:");
	void 重画(bool 参数_擦除背景 = true);
	void 部分重画(RECT 参数_矩形,bool 参数_擦除背景 = true);
	//@别名 _创建窗口()
	bool _CreateWindow(HWND parent, CXText windowName, POINT pos, POINT size, HMENU hMenu, int style, int exStyle, CXText className);
	bool _CreateDialog(HWND parent, const wchar_t* windowName, POINT pos, POINT size, int style, int exStyle, const wchar_t* className);
	INT_PTR _LoadDialog(HWND hWndParent,const wchar_t* titleName,POINT pos, POINT size,int style,int exStyle,const wchar_t* className);
	bool _CreateDialogFormRC(HWND parent,int lpName,const wchar_t* className);
	INT_PTR _LoadDialogFormRC(HWND parent,int lpName,const wchar_t* className);
	bool _CreateMDIWindow(HWND parent, CXText windowName, POINT pos, POINT size, int style, CXText className);
	bool 绑定窗口句柄(HWND 参数_窗口句柄){return _BindhWnd (参数_窗口句柄);}
	void 取消绑定(){_UnBindWnd();}
	int 添加ZY窗口风格(int 参数_ZY窗口风格);
	int 移除ZY窗口风格(int 参数_ZY窗口风格);
	int 取ZY窗口风格(){(int)GetMember (L"zyStyle");}
	int 置ZY窗口风格(int 参数_ZY窗口风格);
	CXText 取类名();
	VOID 置鼠标指针(ThIcon& 参数_光标);
	ThIcon 取鼠标指针();
	VOID 销毁();
	RECT 取用户区矩形();
	int 取用户区宽度();
	int 取用户区高度();
	RECT 取矩形();
	VOID 禁止重画(){SendMsg (WM_SETREDRAW, 0, 0);}
	VOID 允许重画(){SendMsg (WM_SETREDRAW, 1, 0);}
	VOID 取消重画(){ValidateRect (取窗口句柄 (), 0);}
	VOID 刷新显示(){UpdateWindow (取窗口句柄 ());}
	void 移动(int 参数_左边 = 0,int 参数_顶边 = 0,int 参数_宽度 = 0,int 参数_高度 = 0,bool 参数_是否立即重画 = true);
	void 通知边框改变();
	POINT 取位置();
	void 置位置(POINT 参数_位置,bool 参数_是否立即重画 = true);
	POINT 取尺寸();
	void 置尺寸(POINT 参数_位置,bool 参数_是否立即重画 = true);
	int 左边(int 参数_左边 = 0,bool 参数_是否立即重画 = true);
	int 顶边(int 参数_顶边 = 0,bool 参数_是否立即重画 = true);
	int 宽度(int 参数_宽度 = 0,bool 参数_是否立即重画 = true);
	int 高度(int 参数_高度 = 0,bool 参数_是否立即重画 = true);
	bool 可视(bool 参数_是否可视 = false);
	bool 禁止(bool 参数_是否禁止 = false);
	int 取文本长度(){return GetWindowTextLength (取窗口句柄 ());}
	void 置字体(HFONT 参数_字体);
	HFONT 取字体();
	void 允许文件拖放(bool 参数_是否允许拖放){DragAcceptFiles (取窗口句柄 (), 参数_是否允许拖放);}
	bool 开始时钟(int 参数_时钟周期,int 参数_时钟ID = 1);
	bool 停止时钟(int 参数_时钟ID = 1);
	LRESULT 调用默认窗口过程(UINT 参数_msg,WPARAM 参数_wParam,LPARAM 参数_lParam);
	bool 置属性(CXText 参数_属性名,HANDLE 参数_属性值){return SetProp (取窗口句柄 (), 参数_属性名, 参数_属性值) != 0;}
	HANDLE 取属性(CXText 参数_属性名){return GetProp (取窗口句柄 (), 参数_属性名);}
	HANDLE 移除属性(CXText 参数_属性名){return RemoveProp (取窗口句柄 (), 参数_属性名);}
	int 取属性值列表(int 参数_属性值数组){return 0;}
	vint 边框(int 参数_边框 = 0);
	
	//@备注 返回值：整型【0表示放行，1表示拦截】函数 整型 OnMouseMove(HWND hWnd,整型 横坐标,整型 纵坐标,整型 功能键状态)
	void 通用事件_鼠标位置被移动(vint 参数_事件指针);
	//@备注 函数 整型 OnPaint(HWND hWnd,HDC hdc,整型 重画左边,整型 重画顶边,整型 重画右边,整型 重画底边)
	void 通用事件_重画(vint 参数_事件指针);
	//@备注 返回值：整型【0表示放行，1表示拦截】函数 整型 OnLButtonDown(HWND hWnd,整型 横坐标,整型 纵坐标,整型 功能键状态)
	void 通用事件_鼠标左键被按下(vint 参数_事件指针);
	//@备注 返回值：整型【0表示放行，1表示拦截】函数 整型 OnLButtonUp(HWND hWnd,整型 横坐标,整型 纵坐标,整型 功能键状态)
	void 通用事件_鼠标左键被放开(vint 参数_事件指针);
	//@备注 返回值：整型【0表示放行，1表示拦截】函数 整型 OnLButtonDblClk(HWND hWnd,整型 横坐标,整型 纵坐标,整型 功能键状态)
	void 通用事件_被双击(vint 参数_事件指针);
	//@备注 返回值：整型【0表示放行，1表示拦截】函数 整型 OnRButtonDown(HWND hWnd,整型 横坐标,整型 纵坐标,整型 功能键状态)
	void 通用事件_鼠标右键被按下(vint 参数_事件指针);
	//@备注 返回值：整型【0表示放行，1表示拦截】函数 整型 OnRButtonUp(HWND hWnd,整型 横坐标,整型 纵坐标,整型 功能键状态)
	void 通用事件_鼠标右键被放开(vint 参数_事件指针);
	//@备注 函数 整型 OnMouseIn(HWND hWnd)
	void 通用事件_鼠标移入(vint 参数_事件指针);
	//@备注 函数 整型 OnMouseHover(HWND hWnd)
	void 通用事件_鼠标悬停(vint 参数_事件指针);
	//@备注 函数 整型 OnMouseLeave(HWND hWnd)
	void 通用事件_鼠标离开(vint 参数_事件指针);
	//@备注 函数 整型 OnSetFocus(HWND hWnd)
	void 通用事件_获取焦点(vint 参数_事件指针);
	//@备注 函数 整型 OnKillFocus(HWND hWnd)
	void 通用事件_失去焦点(vint 参数_事件指针);
	//@备注 返回值：整型【0表示放行，1表示拦截】函数 整型 OnKeyDown(HWND hWnd,整型 键代码,整型 功能键状态)
	void 通用事件_按下某键(vint 参数_事件指针);
	//@备注 返回值：整型【0表示放行，1表示拦截】函数 整型 OnKeyUp(HWND hWnd,整型 键代码,整型 功能键状态)
	void 通用事件_放开某键(vint 参数_事件指针);
	//@备注 返回值：整型【0表示放行，1表示拦截】函数 整型 OnMouseWheel(HWND hWnd,整型 滚动距离,整型 功能键状态)
	void  通用事件_滚轮被滚动(vint 参数_事件指针);
	//@备注 返回值：整型【0表示放行，1表示拦截】函数 整型 OnChar(HWND hWnd,整型 字符代码)
	void  通用事件_字符输入(vint 参数_事件指针);
	//@备注 函数 整型 OnDropFiles(HWND hWnd,整型 文件路径【Unicode文本指针，以换行符连接】)
	void  通用事件_文件拖放(vint 参数_事件指针);
	//@备注 函数 整型 OnTimer(HWND hWnd,整型 时钟ID)
	void  通用事件_时钟(vint 参数_事件指针);
	//@备注 函数 整型 OnWndMsg(HWND hWnd,正整型 msg,WPARAM wParam,LPARAM lParam,逻辑型* 已处理)
	void  通用事件_窗口消息(vint 参数_事件指针);
	BOOL 置文本(CXText bt);
	CXText 取文本();
	//@别名 发送消息()
	INT_PTR SendMsg(UINT msg, WPARAM 短参数, LPARAM 长参数);
	//@别名 投递消息()
	INT_PTR PostMsg(UINT msg, WPARAM 短参数, LPARAM 长参数);
	//@别名 捕获鼠标()
	HWND SetCap();
	//@别名 释放捕获鼠标()
	BOOL ReleaseCap();
	//@别名 取类名()
	CXText GetCsName();
	//@别名 是否已创建()
	BOOL IsCreate();
	//@别名 获取焦点()
	VOID GetFocus();
	//@别名 是否有焦点()
	BOOL IsFocus();
	//@别名 添加扩展风格()
	DWORD AddExStyle(DWORD ExStyle);
	//@别名 移除扩展风格()
	DWORD RemoveExStyle(DWORD ExStyle);
	//@别名 置扩展风格()
	DWORD SetExStyle(DWORD ExStyle);
	//@别名 取扩展风格()
	DWORD GetExStyle();
	//@别名 移除风格()
	DWORD RemoveStyle(DWORD nStyle);
	//@别名 添加风格()
	DWORD AddStyle(DWORD Style);
	//@别名 置风格()
	DWORD SetStyle(DWORD Style);
	//@别名 取风格()
	DWORD GetStyle();
	//@别名 取父窗口()
	HWND GetParentHwnd();
	//@别名 置父窗口()
	HWND SetParentHwnd(HWND pHwnd);
	//@别名 调整层次()
	VOID AdjustInsertAfter(INT 层次类型);
	bool 显示窗口(int 参数_显示窗口 = SW_SHOW);
	HWND 取窗口句柄();
	//@隐藏{
	virtual void Destroy();
	virtual void OnNCDestroy();
	LRESULT zyWindow_OnSetCursor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	//子类化
	bool zyWindow_SubClass(HWND hWnd);
	//超类化
	BOOL zyWindow_SuperClass(CXBytes className, CXBytes newClassName);
	void _画图片(HWND hwnd,HDC hdc, int type,RECT rc, vint pBackImage, int BackColor);
	void _设置控件边框(int 参数_边框,int& 参数_风格,int& 参数_扩展风格);
	void _SetWindowBorder(int 参数_边框,int& 参数_风格,int& 参数_扩展风格);
	HWND hwnd_=0;
	ATOM MyRegisterClass(HINSTANCE hInstance, CXText 参数_类名, WNDPROC 参数_窗口过程 = nullptr, HICON 参数_图标句柄 = 0, int 参数_类风格 = 0);
	static LRESULT CALLBACK WndProc_(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK _对话框过程(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK _模态对话框过程(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool _BindhWnd(HWND jb);
	void _UnBindWnd();
	bool OnDrawBack(HWND hwnd, HDC hdc);
	static LRESULT CALLBACK _超类化窗口过程(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK _子类化窗口过程(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	//@隐藏}
};
//@分组}

//@隐藏{
extern std::map<HWND, zyBase*> 窗口数据绑定;
BOOL preTranslateMessage(HWND hWnd,zyBase* this_,MSG &msg);
BOOL _处理按钮热键(HWND hWnd, const wchar_t* className, WCHAR wchr);

extern HINSTANCE g_hInstance;

//@隐藏}

//@分组{ 控件入口.界面资源
//@别名 快捷键类
class TAccelTable : public zyRes 
{
public:

	bool 创建(CXVector<ACCEL>& 参数_快捷键结构);
	void 销毁();
	bool 载入(int 参数_资源ID);
	TAccelTable 克隆();
	int 取快捷键信息(CXVector<ACCEL>& 参数_快捷键信息);
	HACCEL 取句柄();
	void 置句柄(HACCEL hAcceleratorTable);
};
//@别名 图标类
class ThIcon : public zyRes {
public:	
	ThIcon(){SetMenber (L"hIcon",0);}
	~ThIcon(){销毁();}
	void 销毁(){
		HICON hIcon = (HICON)GetMenber (L"hIcon");
		if (hIcon != 0) {
			ICONINFO info ={0};
			GetIconInfo (hIcon, &info);
			if (info.fIcon == 0) {
				DestroyCursor (hIcon);
			} else {
				DestroyIcon (hIcon);
			}
			if (info.hbmColor != 0) {
				DeleteObject (info.hbmColor);
			}
			if (info.hbmMask != 0) {
				DeleteObject (info.hbmMask);
			}
			SetMenber (L"hIcon",0);
		}
	}
	INT_PTR 取句柄(){return (INT_PTR)GetMenber (L"hIcon");}
	void 置句柄(void* 参数_句柄){
		销毁();
		SetMenber (L"hIcon",参数_句柄);
	}
	bool 载入图标(int 参数_资源ID){
		销毁 ();
		HICON hIcon = LoadIcon (g_hInstance, MAKEINTRESOURCE(参数_资源ID));
		SetMenber (L"hIcon",hIcon);
		return hIcon != 0;
	}
	bool 载入系统图标(int 参数_类型){
		销毁 ();
		HICON hIcon = LoadIcon (0, MAKEINTRESOURCE(参数_类型));
		SetMenber (L"hIcon",hIcon);
		return hIcon != 0;
	}
	bool 载入光标(int 参数_资源ID){
		销毁 ();
		HCURSOR hIcon = LoadCursor (g_hInstance, MAKEINTRESOURCE(参数_资源ID));
		SetMenber (L"hIcon",hIcon);
		return hIcon != 0;
	}
	bool 载入系统光标(int 参数_类型){
		销毁 ();
		HCURSOR hIcon = LoadCursor (0, MAKEINTRESOURCE(参数_类型));
		SetMenber (L"hIcon",hIcon);
		return hIcon != 0;
	}
	HICON 克隆句柄(){return CopyIcon ((HICON)GetMenber (L"hIcon"));}
};
//@别名 图片组类
class TImageList : public zyRes 
{
public:
	TImageList() : m_hImageList(NULL) {}
	~TImageList() {
        if (m_hImageList != NULL) {
            ImageList_Destroy(m_hImageList);
        }
    }
	HIMAGELIST 取句柄(){
		return m_hImageList;
	}
	void 置句柄(HIMAGELIST him){
		if (m_hImageList != NULL) {
            ImageList_Destroy(m_hImageList);
        }
		m_hImageList = him;
	}
	//@别名 创建(参数_图片宽度,参数_图片高度,参数_创建标志,参数_初始图片数量)
    bool CreateImageList(int cx, int cy, UINT flags = 0, int initial = 0) {
		if(flags ==0)
			flags = 32 | 1;
        m_hImageList = ImageList_Create(cx, cy, flags, initial, initial);
		//SetMenber(L"himl",m_hImageList);
        return m_hImageList != NULL;
    }
	bool 创建自字节集(CXBytes& 参数_图片组字节集,bool 参数_是否易语言格式 = true);
	bool 创建自位图文件(CXText 参数_文件名, int 参数_宽度, int 参数_图标数, int 参数_掩码色 = -1);
	int 添加图标(ThIcon& 参数_图标);
	int 添加图标句柄(HICON 参数_图标句柄);
	int 添加文件W(CXBytes& 参数_文件名,int 参数_文件格式 =0,bool 参数_自动分割 =false);
	int 添加文件(CXText& 参数_文件名,int 参数_文件格式 =0,bool 参数_自动分割 =false);
private:
    HIMAGELIST m_hImageList;
};
//@分组}

//@分组{ 控件入口.界面基类
class zyform : public zyWindow 
{
public:
	//@隐藏{
	zyform();
	virtual void Destroy();
	virtual void OnNCDestroy();
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	void zyForm_OnClose(HWND hWnd);
	bool zyForm_DefaulCommand(int hWnd);
	VOID _开始位置到坐标(HWND parent,int StartPosition,POINT size, POINT &pos,BOOL isDialog);
	//@隐藏}
	bool 托盘气泡提示 (CXText 参数_气泡内容,CXText 参数_气泡标题 = L"",int 参数_气泡图标 = 0,int 参数_气泡显示时间 = 0);
	bool 托盘修改图标 (ThIcon& 参数_图标);
	bool 托盘修改提示文本 (CXText 参数_提示文本);
	bool 置托盘图标 (ThIcon& 参数_图标,CXText 参数_提示文本);
	bool 置外形圆角 (int 参数_圆角角度);
	int 背景图显示方式 (int 参数_图片显示方式 = 0) ;
	int 背景色 (int 参数_背景色 = 0 /*RGB*/);
	bool 置外形 (GPRegion& 参数_区域);
	bool 托盘删除图标 ();
	bool 取控件 (int 参数_控件ID, zyCtrol& 参数_控件) ;
	void 置等待鼠标 ();
	void 恢复鼠标 ();
	HWND 取控件句柄(int 参数_控件ID);
	//@备注 在窗口创建之前调用,用于决定窗口创建时的起始位置
	int 置开始位置 (int 参数_开始位置 = 0);
	ThIcon 取图标(bool 参数_是否大图标 = false);
	void 置图标(ThIcon& 参数_图标,bool 参数_是否大图标 = false);
	int 返回值(int 参数_返回值 = 0);
	bool 保持标题栏激活(bool 参数_保持标题栏激活 = false);
	void 置快捷键(TAccelTable& 参数_快捷键);
	bool 置菜单(TMenu &参数_菜单);
	TMenu 取菜单 ();
	bool 重画菜单栏();
	int 位置(int 参数_位置 = 0);
	bool Esc关闭(bool 参数_Esc关闭 = false);
	bool 随意移动(bool 参数_随意移动 = false);
	//@备注 函数 整型 OnCreate(HWND hWnd)
	void 事件_创建完毕(vint 参数_事件指针);
	//@备注 返回值：整型【0表示可关闭，1表示不可关闭】函数 整型 OnClose(HWND hWnd)
	void 事件_可否被关闭(vint 参数_事件指针);
	//@备注 函数 整型 OnMenuItemClick(HWND hWnd,整型 菜单ID)。备注：菜单或快捷键事件
	void 事件_菜单被单击(vint 参数_事件指针);
	//@备注 函数 整型 OnDestory(HWND hWnd)
	void 事件_将被销毁(vint 参数_事件指针);
	//@备注 函数 整型 OnMove(HWND hWnd,短整型 左边,短整型 顶边)
	void 事件_位置被改变(vint 参数_事件指针);
	//@备注 函数 整型 OnSize(HWND hWnd,短整型 客户区宽度,短整型 客户区高度)
	void 事件_尺寸被改变(vint 参数_事件指针);
	//@备注 函数 整型 OnActivate(HWND hWnd)
	void 事件_被激活(vint 参数_事件指针);
	//@备注 函数 整型 OnUnActivate(HWND hWnd)
	void 事件_被取消激活(vint 参数_事件指针);
	//@备注 函数 整型 OnFirstActivate(HWND hWnd)
	void 事件_首次激活(vint 参数_事件指针);
	//@备注 函数 整型 OnShow(HWND hWnd)
	void 事件_被显示(vint 参数_事件指针);
	//@备注 函数 整型 OnHide(HWND hWnd)
	void 事件_被隐藏(vint 参数_事件指针);
	//@备注 函数 整型 OnNotifIcon(HWND hWnd,整型 事件类型【“托盘_”开头常量】)
	void 事件_托盘事件(vint 参数_事件指针);
	//@备注 函数 整型 OnInitMenuPopup(HWND hWnd,HMENU 菜单句柄,整型 项目索引,逻辑型 是否系统菜单)
	void 事件_将弹出菜单(vint 参数_事件指针);
	//@备注 函数 整型 OnMenuSelect(HWND hWnd,HMENU 父菜单句柄,整型 菜单ID或索引【如果项目是弹出菜单，就是索引】,整型 菜单标志【菜单标志_ 开头常量】)
	void 事件_菜单项热点跟踪(vint 参数_事件指针);
	//@备注 返回值：整型【0表示可关闭，1表示不可关闭】函数 整型 OnUserClose(HWND hWnd) 当用户点击关闭按钮或系统菜单中的关闭菜单时触发
	void 事件_可否用户关闭(vint 参数_事件指针);
	//@备注 函数 整型 OnSysCommand(HWND hWnd,整型 ID,整型 横坐标,整型 纵坐标) 系统菜单等系统命令，触发此事件
	void 事件_系统命令(vint 参数_事件指针);
};
class zyDialogBox : public zyform 
{
	public:
	//@隐藏{
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	void _MoveToStartPosition(HWND hWnd);
	//@隐藏}
	POINT 对话框单位到像素(int 参数_对话框单位X,int 参数_对话框单位Y);
	POINT 像素到对话框单位(int 参数_对话框单位X,int 参数_对话框单位Y);
	int 取控件整数(int 参数_控件ID,BOOL& 参数_是否成功);
	bool 置控件整数(int 参数_控件ID,int 参数_整数值);
	CXText 取控件文本(int 参数_控件ID);
	bool 置控件文本(int 参数_控件ID,CXText 参数_文本);
	int 发送控件消息(int 参数_控件ID,int 参数_消息值,WPARAM 参数_wParam,LPARAM 参数_lParam);
};
///-----------------------------------------控件基类============
class zyCtrol : public zyWindow
{
public:
	//@隐藏{
	virtual void Destroy();
	virtual void OnNCDestroy();
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	static LRESULT CALLBACK _MDI客户区窗口过程(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	//@隐藏}
	bool _CreateMDIClient(HWND parent, CXText windowName, POINT pos, POINT size, HMENU id, int style, int exStyle, CXText className);
	bool _CreateCtrol(HWND parent, CXText windowName, POINT pos, POINT size, HMENU id, int style, int exStyle, CXText className);
	bool _CreateWindow(HWND parent, CXText windowName, POINT pos, POINT size, HMENU id, int style, int exStyle, CXText className);
	//@别名 取控件ID()
	int GetID();
	void 置外形 (GPRegion& 参数_区域);
	virtual bool 绑定(HWND 参数_父窗口,int 参数_资源ID,bool 参数_使用默认字体 = true);
};
class zyCommandCtrol : public zyCtrol
{
public:
	//@隐藏{
	zyCommandCtrol();
	virtual void Destroy();
	virtual void OnNCDestroy();
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	//@隐藏}
	vint 文本色(vint 参数_文本色 =0);
	vint 背景色(vint 参数_背景色 =0);
};
class zyCustomCtrol : public zyCtrol
{
public:
	//@隐藏{
	zyCustomCtrol();
	virtual void Destroy();
	virtual void OnNCDestroy();
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	//@隐藏}
	vint 背景色(vint 参数_背景色 = 0);
};
//@分组}

//@分组{ 界面入口
//@别名 时钟类
class TTimer : public zyBase 
{
public:
	TTimer() {
		SetName(L"时钟类");
	}
	
	//@参数 时钟周期必须大于0，以毫秒为单位
	//@参数 指向要通知的函数，函数模板为备注所示
	//@备注 函数 空类型 TimerProc1(HWND 窗口句柄,UINT 消息类型,UINT 时钟ID,DWORD 系统启动时间)
	bool 创建(int 参数_时钟周期,TIMERPROC 参数_周期事件);
	bool 销毁();
	int 取时钟周期();
	//@参数 以毫秒为单位,时钟周期必须大于0.0表示销毁时钟
	bool 置时钟周期(int 参数_时钟周期);
	UINT 取时钟ID();
};
//@别名 对话框类
class TDialogBox : public zyDialogBox 
{
public:
	TDialogBox() {
		SetName(L"对话框类");
		SetMember(L"StartPosition", 2);
	}
	bool 创建(HWND 参数_父窗口 = NULL, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(300,200), int 参数_窗口风格 = 0, int 参数_扩展风格 = 0, BOOL 参数_不在任务栏显示 = FALSE, CXText 参数_类名 = L"TDialogBox");
	INT_PTR 载入(HWND 参数_父窗口 = NULL, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(300,200), int 参数_窗口风格 = 0, int 参数_扩展风格 = 0, BOOL 参数_不在任务栏显示 = FALSE, CXText 参数_类名 = L"TDialogBox");
	bool 创建自资源(HWND 参数_父窗口, int 参数_资源ID, BOOL 参数_不在任务栏显示 = FALSE, CXText 参数_类名 = L"TDialogBox");
	INT_PTR 载入自资源(HWND 参数_父窗口, int 参数_资源ID, BOOL 参数_不在任务栏显示 = FALSE, CXText 参数_类名 = L"TDialogBox");
};
//@别名 文件对话框类
class TFileDialog : public zyDialogBox 
{
public:
	TFileDialog() {
		SetName(L"TFileDialog");
	}
	~TFileDialog() {
		OPENFILENAME* ofn = (OPENFILENAME*)GetMember ("pOpenFileName");
		if(ofn != nullptr){
			if(ofn->lpstrTitle != nullptr)
				delete ofn->lpstrTitle;
			if(ofn->lpstrFile != nullptr)
				delete ofn->lpstrFile;
			if(ofn->lpstrInitialDir != nullptr)
				delete ofn->lpstrInitialDir;
			if(ofn->lpstrDefExt != nullptr)
				delete ofn->lpstrDefExt;
			delete ofn;
		}
	}
	static LRESULT CALLBACK OFNHookProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam);
	bool 打开(HWND 参数_父窗口 = NULL);
	void 初始化(int 参数_选项,const CXText& 参数_标题 = L"",const CXText& 参数_文件名 = L"",const wchar_t* 参数_过滤器 = nullptr,int 参数_过滤器索引 = 1,const CXText& 参数_初始目录 = L"",const CXText& 参数_默认扩展名 = L"");
	CXText 取文件名();
	bool 保存(HWND 参数_父窗口 = NULL);
	int 取过滤器索引();
	bool 置默认扩展名(const CXText& 参数_默认扩展名 );
	//@备注 函数 整型 OnTypeChange(HWND hWnd,整型 过滤器索引)，备注：可在此方法中调用，文件对话框.置默认扩展名()
	void 事件_文件类型被改变(vint 参数_子程序){SetMember ("OnTypeChange", 参数_子程序);}
	//@备注 函数 整型 OnInitDone(HWND hWnd)，备注：当对话框的所有控件创建完成时，发送此事件
	void 事件_初始化完成(vint 参数_子程序){SetMember ("OnInitDone", 参数_子程序);}
	//@备注 返回值：整型【0表示默认处理，1表示阻止】 函数 整型 OnFlieOk(HWND hWnd,整型 文件名【Unicode文本指针】)
	void 事件_确定按钮被单击(vint 参数_子程序){SetMember ("OnFlieOk", 参数_子程序);}
};
//@别名 颜色对话框类
class TColorDialog : public zyDialogBox 
{
public:
	TColorDialog() {
		SetName(L"TColorDialog");
	}
	~TColorDialog() {
		COLORREF* custColors = (COLORREF*)GetMember ("custColors");
		if(custColors != nullptr){
			delete custColors;
		}
		CHOOSECOLOR* cc = (CHOOSECOLOR*)GetMember ("pChooseColor");
		if(cc != nullptr){
			delete cc;
		}
	}
	static LRESULT CALLBACK CCHookProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam);
	bool 打开(HWND 参数_父窗口 = NULL);
	//@参数 颜色对话框_开头常量组合。默认空
	//@参数 初始颜色。默认空
	//@参数 必须是16个成员的整数型数组，每个成员表示16个颜色值。默认空
	void 初始化(int 参数_选项 = NULL,int 参数_初始颜色 = NULL, CXVector<UINT64>& 参数_自定义颜色组 = TNULLVectorUINT64);
	int 取颜色值();
	int 取选项();
	void 取自定义颜色组(CXVector<UINT64>& 参数_自定义颜色组);
};

//@别名 窗口类
class Twidget : public zyform 
{
public:
	Twidget() {
		SetName(L"窗口");
		SetMember(L"StartPosition", 2);
	}
	//@参数 要设置的父窗口句柄，默认为空。即为主窗口
	//@参数 要设置的窗口标题，默认空文本
	//@参数 如果为-1,-1则默认居中
	//@参数 
	//@参数 "窗口风格_"开头常量，默认：窗口风格_标题栏 | 窗口风格_系统菜单 | 窗口风格_对话框边框 | 窗口风格_单边框 | 窗口风格_可视
	//@参数 "窗口扩展_"开头常量
	//@参数 默认为假，如果是弹出的子窗口需要在任务栏显示,请在 “参数_扩展风格”中设置 “窗口扩展_在任务栏显示”
	//@参数 要注册的窗口类名，默认：TWindow
	//@备注 成功返回真，失败返回假
	bool 创建(HWND 参数_父窗口 = NULL, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(-1,-1), POINT &参数_尺寸 = 黑月坐标(300,200), int 参数_窗口风格 = 0, int 参数_扩展风格 = 0, BOOL 参数_不在任务栏显示 = FALSE, CXText 参数_类名 = L"TWindow");
	bool 绑定窗口句柄(HWND 参数_窗口句柄){return _BindhWnd(参数_窗口句柄);}
	CXText 标题(CXText 参数_标题 = L"");
	bool 取资源控件 (CXText 参数_资源名 /*XML的 名称 属性,如： <按钮 名称="xxx">*/, zyWindow& 参数_控件 /*返回控件*/);
};
//@别名 面板类
class TPanel : public zyform 
{
public:
	//@隐藏{
	TPanel() {
		SetName(L"面板类");
	}
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual void Destroy();
	virtual void OnNCDestroy();
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(300,200), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(300,200), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建自资源(HWND 参数_父窗口, int 参数_资源ID, CXText 参数_类名 = L"TDialogBox");
	int 边框(int 参数_边框);
};
//@别名 菜单类
class TMenu
{
public:

	HMENU m_hMenu;
	bool 创建菜单栏();
	bool 创建弹出菜单();
	bool 绑定系统菜单(HWND  参数_窗口句柄);
	void 重置系统菜单(HWND  参数_窗口句柄);
	void 销毁();
	void _DeleteBitmaps(HMENU  hMenu);
	HMENU 取菜单句柄();
	bool 置菜单句柄(HMENU  参数_菜单句柄);
	bool 添加弹出菜单(TMenu&  参数_菜单条,wchar_t*  参数_菜单名);
	bool 插入弹出菜单(TMenu&  参数_菜单条,wchar_t*  参数_菜单名,int  参数_索引 = -1);
	bool 置窗口(HWND  参数_窗口句柄);
	bool 置菜单背景色(int  参数_颜色值,bool  参数_应用于所有子菜单 = true);
	bool 置菜单背景图(GPBitmap&  参数_图片,int  参数_图片背景色 = 0,bool  参数_应用于所有子菜单 = true);
	TMenu 取子菜单(int  参数_索引);
	int 取项目ID(int  参数_索引);
	bool 添加项目(wchar_t*  参数_菜单名,int  参数_菜单ID);
	bool 添加分割线();
	bool 插入项目(wchar_t*  参数_菜单名,int  参数_索引,int  参数_菜单ID);
	bool 插入分割线(int  参数_索引);
	bool 单选菜单(int  参数_索引,int  参数_分组起始索引,int  参数_分组结束索引);
	int 弹出菜单(int  参数_X,int  参数_Y,HWND  参数_窗口句柄,int  参数_标志 = 0);
	wchar_t* 取项目标题(int  参数_菜单ID,bool  参数_使用索引 = false);
	int 取项目风格(int  参数_菜单ID或索引,bool  参数_使用索引 = false);
	RECT 取项目矩形(HWND  参数_窗口句柄,int  参数_菜单索引);
	INT_PTR 取项目数值(int  参数_菜单ID或索引,bool  参数_使用索引 = false);
	int 取项目数();
	int 取项目状态(int  参数_菜单ID,bool  参数_使用索引 = false);
	int 取默认项目(int  参数_标志 = 0,bool  参数_使用索引 = false);
	int 取坐标项目(HWND  参数_窗口句柄,int  参数_横坐标,int  参数_纵坐标);
	bool 取项目图标(int  参数_菜单ID或索引,GPBitmap& 参数_位图,bool  参数_使用索引 = false);
	bool 取项目图标选中(int  参数_菜单ID或索引,GPBitmap& 参数_未选中位图,GPBitmap& 参数_已选中位图,bool  参数_使用索引 = false);
	bool 删除项目(int 参数_菜单ID或索引,bool 参数_使用索引 = false);
	int 选中项目(int  参数_菜单ID或索引,bool  参数_是否选中,bool  参数_使用索引 = false);
	bool 是否选中(int  参数_菜单ID或索引,bool  参数_使用索引 = false);
	bool 置项目ID(int  参数_菜单ID或索引,int  参数_新菜单ID,bool  参数_使用索引 = false);
	bool 置项目标题(int  参数_菜单ID或索引,wchar_t*  参数_菜单标题,bool  参数_使用索引 = false);
	bool 置项目风格(int  参数_菜单ID或索引,int  参数_风格,bool  参数_使用索引 = false);
	bool 载入RC资源(int  参数_菜单栏资源ID);
	bool 置项目数值(int  参数_菜单ID或索引,int  参数_菜单数值,bool  参数_使用索引 = false);
	bool 置项目图标(int  参数_菜单ID或索引,GPBitmap&  参数_图标,bool  参数_使用索引 = false);
	bool 置项目图标选中(int  参数_菜单ID或索引,GPBitmap&  参数_未选中图标,GPBitmap&  参数_已选中图标,bool  参数_使用索引 = false);
	bool 置项目状态(int  参数_菜单ID或索引,int  参数_菜单状态,bool  参数_使用索引 = false);
	bool 置默认项目(int  参数_菜单ID或索引,bool  参数_使用索引 = false);
};
//@别名 MDI框架窗口类
class TMDIFrame : public zyform 
{
public:
	TMDIFrame() {
		SetName(L"TMDIFrame");
		SetMember(L"StartPosition", 2);
	}
	static LRESULT CALLBACK _MDI框架窗口过程(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	bool 创建(HWND 参数_父窗口 = NULL, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(300,200), int 参数_窗口风格 = 0, int 参数_扩展风格 = 0, BOOL 参数_不在任务栏显示 = FALSE, CXText 参数_类名 = L"TMDIFrame");
};
//@别名 MDI客户区类
class TMDIClient : public zyCtrol 
{
public:
	//@隐藏{
	TMDIClient() {
		SetName(L"TMDIClient");
		SetMember(L"this", (vint)this);
	}
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual void Destroy();
	virtual void OnNCDestroy();
	//@隐藏}
	bool 创建(TMDIFrame& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(300,200), HMENU 参数_ID = 0,int 参数_窗口风格 = 0, int 参数_扩展风格 = 0, TMenu& 参数_子窗口列表菜单 = TMenu(), int 参数_列表菜单起始ID = 20000);
	void 置背景图(GPImage& 参数_图像,int 参数_图片显示方式){
		vint Image = GetMember ("BackImage");
		if(Image != 0){
			参数_图像.Destory();//GdipDisposeImage (Image);
		}
		//GdipCloneImage (参数_图像.取句柄 (), Image);
		SetMember ("BackImage", (vint)&参数_图像);
		SetMember ("ShowImageType", 参数_图片显示方式);
	}
	GPImage 取背景图(){
		GPImage* 局部_图像;
		vint Image = GetMember ("BackImage");
		if(Image != 0){
			//GdipCloneImage (Image, newImage);
			//局部_图像.置句柄 (newImage);
			局部_图像 = (GPImage*)Image;
		}
		return *局部_图像;
	}
	int 取背景图显示方式(){//"图片显示方式_"开头常量
		return (int)GetMember ("ShowImageType");
	}
	void 置背景图显示方式(int 参数_图片显示方式){SetMember ("ShowImageType", 参数_图片显示方式);}
	int 背景色(int 参数_背景色 = 0){//RGB颜色值
		int color = zyARGB2RGB ((int)GetMember ("BackColor"),255);
		if(参数_背景色 == 0)
			return color;
		SetMember ("BackColor", zyRGB2ARGB (参数_背景色,255));
		return color;
	}
	TMDIChildFrame 取当前子窗口();
	int 置当前子窗口(TMDIChildFrame& 参数_MDI子窗口);
	bool 层叠子窗口(int 参数_排列选项){return SendMsg (WM_MDICASCADE, 参数_排列选项, 0) != 0;}
	void 重排最小化子窗口(){SendMsg (WM_MDIICONARRANGE, 0, 0);}
	void 销毁子窗口(TMDIChildFrame& 参数_MDI子窗口);
	void 下一个子窗口(TMDIChildFrame& 参数_MDI子窗口);
	void 上一个子窗口(TMDIChildFrame& 参数_MDI子窗口);
	void 恢复子窗口(TMDIChildFrame& 参数_MDI子窗口);
	bool 平铺子窗口(int 参数_方式){return SendMsg (WM_MDITILE, 参数_方式, 0) != 0;}
	void 最大化子窗口(TMDIChildFrame& 参数_MDI子窗口);
	void 最小化子窗口(TMDIChildFrame& 参数_MDI子窗口);
	int 置菜单(TMenu& 参数_MDI框架窗口菜单,TMenu& 参数_MDI子窗口菜单){
		return (int)SendMsg (WM_MDISETMENU, (WPARAM)参数_MDI框架窗口菜单.取菜单句柄 (), (LPARAM)参数_MDI子窗口菜单.取菜单句柄 ());
	}
};
//@别名 MDI子窗口类
class TMDIChildFrame : public zyform 
{
public:
	TMDIChildFrame() {
		SetName(L"TMDIChildFrame");
		SetMember(L"this", (vint)this);
	}
	static LRESULT CALLBACK _MDI子窗口过程(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool 创建(TMDIClient& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(2147483648,2147483648), POINT &参数_尺寸 = 黑月坐标(300,200), int 参数_窗口风格 = 0,CXText 参数_类名 = L"TMDIChildFrame");
	bool 绑定窗口句柄(HWND 参数_窗口句柄){return _BindhWnd (参数_窗口句柄);}
};
//@分组}

//@分组{ 控件入口.通用控件
//@别名 影像框类
class TAnimate : public zyCtrol
{
public:
	//@隐藏{
	TAnimate() {
		SetName(L"影像框类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(100,100), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(100,100), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	//@备注 函数 整型 OnStart(HWND hWnd,整型 id)
	void 事件_开始播放(vint 参数_事件指针){SetMember(L"OnStart", 参数_事件指针);}
	//@备注 函数 整型 OnStop(HWND hWnd,整型 id)
	void 事件_停止播放(vint 参数_事件指针){SetMember(L"OnStop", 参数_事件指针);}
	bool 打开(CXText 参数_文件名);
	bool 播放(int 参数_播放次数 = -1);
	bool 打开RC资源(int 参数_资源ID){return SendMsg (ACM_OPENW, (WPARAM)g_hInstance, (LPARAM)参数_资源ID) != 0;}
	bool 是否正在播放(){return SendMsg (ACM_ISPLAYING, 0, 0) != 0;}
	bool 停止播放(){return SendMsg (ACM_STOP, 0, 0) != 0;}
};
//@别名 工具提示类
class TToolTips : public zyWindow 
{
public:
	TToolTips() {
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual void Destroy();
	virtual void OnNCDestroy();
	bool 创建(int 参数_风格 = NULL, int 参数_扩展风格 = NULL);
	bool 添加(HWND 参数_窗口句柄,CXText 参数_提示文本,bool 参数_显示在正下方 = false,bool 参数_使用绝对位置 = false);
	void 删除(HWND 参数_窗口句柄);
	int 取提示数(){return (int)SendMsg (TTM_GETTOOLCOUNT, 0, 0);}
	int 置最大宽度(int 参数_最大宽度){return (int)SendMsg (TTM_SETMAXTIPWIDTH, 0, 参数_最大宽度);}
	int 取最大宽度(){return (int)SendMsg (TTM_GETMAXTIPWIDTH, 0, 0);}
	bool 置标题(CXText 参数_提示文本,int 参数_标题图标){return SendMsg (TTM_SETTITLEW,参数_标题图标,(LPARAM)参数_提示文本.get()) !=0;}
	void 置提示文本(HWND 参数_窗口句柄,CXText 参数_提示文本);
	CXText 取提示文本(HWND 参数_窗口句柄);
	void 置延时(int 参数_延时类型,int 参数_延时){SendMsg (TTM_SETDELAYTIME, 参数_延时类型, 参数_延时);}
	int 取延时(int 参数_延时类型){return (int)SendMsg (TTM_GETDELAYTIME, 参数_延时类型, 0);}
	void 启用(bool 参数_是否启用){SendMsg (TTM_ACTIVATE, 参数_是否启用, 0);}
	bool 调节矩形(RECT 参数_矩形){return SendMsg (TTM_ADJUSTRECT, 1, (LPARAM)&参数_矩形) != 0;}
	void 置矩形(HWND 参数_窗口句柄,RECT& 参数_新矩形);
	int 背景色(int 参数_颜色值 =0);
	int 文本色(int 参数_颜色值 =0);
	int 取所有窗口(CXVector<HWND>& 参数_窗口句柄数组);
	int 取坐标窗口(int 参数_x,int 参数_y);
	POINT 取气泡尺寸(HWND 参数_窗口句柄);
	HWND 取当前窗口();
	RECT 取边距();
	void 置边距(RECT 参数_边距);
	//@备注 在最后一个鼠标位置 弹出提示，必须启用 Window通用组件6.0
	void 弹出(){SendMsg (TTM_POPUP, 0, 0);}
	void 隐藏(){SendMsg (TTM_POP, 0, 0);}
	void 置提示位置(int 参数_屏幕水平位置,int 参数_屏幕垂直位置);
	void 激活跟踪(HWND 参数_窗口句柄,bool 参数_是否激活);
	//@备注 函数 整型 OnShow(HWND hWnd)
	void 事件_被显示(vint 参数_事件指针){SetMember ("OnShow", 参数_事件指针);}
	//@备注 函数 整型 OnHide(HWND hWnd)
	void 事件_被隐藏(vint 参数_事件指针){SetMember ("OnHide", 参数_事件指针);}
};

typedef void(*元素事件_被单击)(zyWindow* 来源对象,HWND hWnd,int 链接索引,wchar_t* URL,wchar_t* ID);
//@别名 超链接框类
class TLinkBox : public zyCommandCtrol
{
public:
	//@隐藏{
	TLinkBox() {
		SetName(L"超链接框类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(100,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(100,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 置链接URL(int linkIndex, CXText url);
	CXText 取链接URL(int 参数_链接索引);
	bool 置链接ID(int 参数_链接索引, CXText 参数_ID);
	CXText 取链接ID(int 参数_链接索引);
	bool 置链接状态(int 参数_链接索引,int 参数_状态);
	int 取链接状态(int 参数_链接索引);
	int 取坐标链接(int 参数_横向坐标,int 参数_纵向坐标);
	int 取最佳高度(){return (int)SendMsg(LM_GETIDEALHEIGHT, 0, 0);}
	//@备注 函数 整型 OnClick(HWND hWnd,整型 链接索引,字符型* URL,字符型* ID)
	void 事件_被单击(vint 参数_事件指针);
	
	元素事件_被单击 被单击 = NULL;
	virtual void On元素事件_被单击(HWND hWnd,int 链接索引,wchar_t* URL,wchar_t* ID)
	{
		if(被单击)
			被单击(this,hWnd,链接索引,URL,ID);
	}
};

//@别名 超链接框模板类
template<class T>
class TLinkBox_EventMgr : public TLinkBox
{
public:
	//@隐藏{
	CXEventMgr<T>  m_eventMgr; //用于管理事件
	//@隐藏}
	//@别名 元素事件_被单击()
	事件定义 void OnClick(HWND hWnd,int 链接索引,wchar_t* URL,wchar_t* ID) {
		CXEventMgr<T>::xc_bind_event_item_<T>* pEvent = m_eventMgr.FindEvent(L"OnClick");
		if (pEvent)
		{
			typedef  int (T::* funType)(TLinkBox_EventMgr<T>*, HWND,int,wchar_t*,wchar_t*);
			(pEvent->pObj->*((funType)pEvent->memberFun))(this,hWnd,链接索引,URL,ID);
		}
	}
	//@隐藏{
	virtual void On元素事件_被单击(HWND hWnd,int 链接索引,wchar_t* URL,wchar_t* ID)
	{
		//XCL_log(L"On元素事件_被单击");
		if(被单击)
			__super::On元素事件_被单击(hWnd,链接索引,URL,ID);
		else
			OnClick(hWnd,链接索引,URL,ID);
	}
	//@隐藏}
};
//@别名 热键框类
class THotkey : public zyCtrol
{
public:
	//@隐藏{
	THotkey() {
		SetName(L"热键框类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	黑月热键信息 取热键();
	void 置热键(黑月热键信息& 参数_热键信息);
	void 置规则(int 参数_规则,int 参数_替换功能键);
	//@备注 函数 整型 OnChange(HWND hWnd,短整型 ID)
	void 事件_内容被改变(vint 参数_事件指针){SetMember ("OnChange", 参数_事件指针);}
};
//@别名 IP编辑框类
class TIPAddress : public zyCtrol
{
public:
	//@隐藏{
	TIPAddress() {
		SetName(L"IP编辑框类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	UINT _IP地址到整数(黑月IP地址& 参数_地址);
	黑月IP地址 _整数到IP地址(int address);
	CXText _IP地址到文本(黑月IP地址& 参数_IP地址);
	黑月IP地址 _文本到IP地址(CXText 参数_IP地址文本);
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 置地址(黑月IP地址& 参数_地址);
	黑月IP地址 取地址();
	CXText 取地址文本();
	bool 置地址文本(CXText 参数_IP地址文本);
	bool 清空();
	bool 是否空地址();
	bool 置焦点位置(int 参数_IP段位置);
	bool 置IP范围(int 参数_IP段位置,byte 参数_最低值,byte 参数_最高值);
	//@备注 函数 整型 OnFieldChanged(HWND hWnd,整数型 IP段位置,整数型 该段值)
	void 事件_段位置被改变(vint 参数_事件指针){SetMember ("OnFieldChanged", 参数_事件指针);}
};
//@别名 属性框类
class TPropertyGrid : public zyCtrol
{
public:
	//@隐藏{
	TPropertyGrid() {
		SetName(L"属性框类");
		SetMember(L"this", (vint)this);
	}
	#define PGC_cbSize 44
	#define PGC_Name 0
	#define PGC_Value 4
	#define PGC_DefualtValue 8
	#define PGC_Type 12
	#define PGC_Parent 16
	#define PGC_Childs 20
	#define PGC_Level 24
	#define PGC_TextColor 28
	#define PGC_Bold 32
	#define PGC_State 36
	#define PGC_lParam 40
	struct PGC_pitem{
		int State;
		CXText Name;
		int Type;
		int TextColor;
		int Level;
		LPARAM lParam;
		PGC_pitem* Parent;
		int Value;
		std::vector<PGC_pitem*> Childs;
	};
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual void Destroy();
	virtual void OnNCDestroy();
	int propertyItem_Edit_Msg(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam,bool* bHand);
	TImageList* imgList;
	TEditBox* edit;
	TListBox* list;
	Twidget* listWindow;
	std::map<int, vint> Propertys;
	void _init(HWND hWnd);
	void* _InsertProperty(int index,PGC_pitem* parent,CXText& name,int type,int state,LPARAM lParam);
	
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 置属性名列宽(int 参数_宽度);
	void* 插入项目_分组(int 参数_索引,CXText& 参数_名称,LPARAM 参数_项目数值);
};
//@别名 日期框类
class TDateTimePick : public zyCtrol
{
public:
	//@隐藏{
	TDateTimePick() {
		SetName(L"日期框类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual void Destroy();
	virtual void OnNCDestroy();
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 置日期格式(CXText 参数_格式);
	bool 是否空日期();
	DOUBLE 今天(DOUBLE 参数_今天 = 0);
	DOUBLE 最小时间(DOUBLE 参数_最小时间 =0);
	DOUBLE 最大时间(DOUBLE 参数_最大时间 =0);
	int 取月历颜色(int 参数_标志);
	bool 置月历颜色(int 参数_颜色值,int 参数_标志);
	bool 取月历(TMonthCal& 参数_月历);
	GPFont 取月历字体();
	void 置月历字体(GPFont& 参数_字体);
	//@备注 函数 整型 OnDateTimeSelChange(HWND hWnd,长整型 改变后日期,逻辑型 是否空日期)
	void 事件_选择日期被改变(vint 参数_事件指针){SetMember ("OnDateTimeSelChange", 参数_事件指针);}
	//@备注 函数 整型 OnUserString(HWND hWnd,整型 输入的文本【wchar*】,[日期时间型,参考-1] 返回日期,[逻辑型,参考-1] 是否空日期)  备注：仅当设置了 "日期框_应用程序解析"风格时，发送此事件
	void 事件_用户输入(vint 参数_事件指针){SetMember ("OnUserString", 参数_事件指针);}
};
//@别名 月历类
class TMonthCal : public zyCtrol
{
public:
	//@隐藏{
	TMonthCal() {
		SetName(L"月历类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	int 开始星期首日(int 参数_开始星期首日 = 0);
	DOUBLE 今天(DOUBLE 参数_今天日期 = 0);
	DOUBLE 最大日期(DOUBLE 参数_最大日期 =0);
	DOUBLE 最小日期(DOUBLE 参数_最小日期 =0);
	int 最多选择天数(int 参数_最多选择天数);
	bool 置选择日期范围(DOUBLE 参数_首选择日,DOUBLE 参数_尾选择日);
	bool 取选择日期范围(DOUBLE& 参数_首选择日,DOUBLE& 参数_尾选择日);
	DOUBLE 选择日期(DOUBLE 参数_选择日期);
	int 滚动月数(int 参数_滚动月数);
	bool 置颜色(int 参数_颜色值,int 参数_标志){return SendMsg (MCM_SETCOLOR, 参数_标志, 参数_颜色值) != -1;}
	int 取颜色(int 参数_标志){return (int)SendMsg (MCM_GETCOLOR, 参数_标志, 0);}
	//@备注 每一个成员的0-30比特位表示每天的状态
	bool 置天日状态(CXVector<int>& 参数_状态数组){
		return SendMsg (MCM_SETDAYSTATE, 参数_状态数组.getSize(), (LPARAM)&参数_状态数组[0]) != 0;
	}
	//@备注 函数 整型 OnDateSelChange(HWND hWnd,日期时间型 起始日期,日期时间型 结束日期)
	void 事件_选择日期被改变(vint 参数_事件指针){SetMember ("OnDateSelChange", 参数_事件指针);}
	//@备注 函数 整型 OnGetDayState(HWND hWnd,日期时间型 日期,整数型 月份数,[整数型,参考-1] 状态数组指针【每一个成员的0-30比特位表示每天的状态】)
	void 事件_取天日状态(vint 参数_事件指针){SetMember ("OnGetDayState", 参数_事件指针);}
};
//@别名 调节器类
class TUpDown : public zyCtrol
{
public:
	//@隐藏{
	TUpDown() {
		SetName(L"调节器类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	int 关联控件(zyWindow &参数_编辑控件);
	int 按钮值(int 参数_按钮值 = NULL);
	int 基数(int 参数_基数 = NULL);
	int 置按钮值范围(int 参数_最小按钮值,int 参数_最大按钮值);
	POINT 取按钮值范围();
	//@备注 返回值：整型【0允许改变，1阻止改变】 函数 整型 OnUpDown(整型  方向【向上为1,否则为-1】,整型 按钮值)
	void 事件_调节钮被按下(vint 参数_事件指针){SetMember (L"OnUpDown",参数_事件指针);}
};
//@别名 状态栏类
class TStatusBar : public zyCtrol
{
public:
	//@隐藏{
	TStatusBar() {
		SetName(L"状态栏类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	int 加入栏目(CXText 参数_栏目文本,int 参数_宽度 = NULL,CXText 参数_动态提示文本 = NULL,ThIcon& 参数_图标 = ThIcon());
	bool 清空(){
		std::vector<int> 局部_栏目宽度组(1);
		return SendMsg (SB_SETPARTS, 1, reinterpret_cast<LPARAM>(&局部_栏目宽度组[0])) != 0;
	};
	bool 删除栏目(int 参数_栏目索引);
	bool 分割栏目(CXVector<int>& 参数_分割栏宽度);
	//@参数 返回的位置数组。每一个数组成员代表每一个栏目宽度
	int 取分割栏目(CXVector<int>& 参数_分割栏位置);
	int 取栏目数(){return (int)SendMsg (SB_GETPARTS, 0, 0) ;}
	RECT 取栏目矩形(int 参数_栏目索引);
	bool 置栏目文本(int 参数_栏目索引,CXText 参数_栏目文本 =L"");
	CXText 取栏目文本(int 参数_栏目索引 = 0);
	int 置背景色(int 参数_颜色值){return (int)SendMsg (SB_SETBKCOLOR, 0, 参数_颜色值) ;}
	int 置栏目图标(int 参数_栏目索引,ThIcon& 参数_图标);
	ThIcon 取栏目图标(int 参数_栏目索引);
	//@参数 可空为第一个位置。位置从0开始
	//@参数 动态提示文本仅当栏目只有图片但没有内容文本或者内容文本不能被全部显示的情况下才有效。如果本参数被省略，默认值为空文本
	bool 置动态提示文本(int 参数_栏目索引,CXText 参数_提示文本=L"");
	CXText 取动态提示文本(int 参数_栏目索引);
	bool 置简单模式(bool 参数_是否简单模式);
	//@备注 把此方法放在窗口尺寸被改变事件里
	void 自动大小(){ SendMsg (WM_SIZE, 0, 0) ;}
	//@参数 有三个成员，第一个表示水平边界宽度；第二个表示垂直边界宽度；第三个表示边界矩形宽度
	bool 取边界(CXVector<int>& 参数_边界集);
	void 置最小高度(int 参数_最小高度){ SendMsg (SB_SETMINHEIGHT, 参数_最小高度, 0) ;}
	//@备注 函数 整型 SimpleModeChange(HWND hWnd)
	void 事件_简单模式被改变(vint 参数_事件指针){SetMember (L"SimpleModeChange",参数_事件指针);}
	//@备注 函数 整型 OnClick(HWND hWnd, 整型 栏目索引,整型 X,整型 Y)
	void 事件_被单击(vint 参数_事件指针){SetMember (L"OnClick",参数_事件指针);}
	//@备注 函数 整型 OnDBLClick(HWND hWnd, 整型 栏目索引,整型 X,整型 Y)
	void 事件_被双击(vint 参数_事件指针){SetMember (L"OnDBLClick",参数_事件指针);}
	//@备注 函数 整型 OnRClick(HWND hWnd, 整型 栏目索引,整型 X,整型 Y)
	void 事件_右键单击(vint 参数_事件指针){SetMember (L"OnRClick",参数_事件指针);}
};
//@别名 工具条类
class TToolBar : public zyCtrol
{
public:
	//@隐藏{
	TToolBar() {
		SetName(L"工具条类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual void Destroy();
	virtual void OnNCDestroy();
	bool zyToolbar_OnCustomDraw(HWND hwnd, HDC hdc,RECT& hrc);
	std::map<UINT_PTR, CXText> m_HashToolTips;
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	int 插入按钮(int 参数_插入位置,int 参数_按钮ID,CXText 参数_标题 =L"",int 参数_类型 = -1,int 参数_图片索引 = -1,CXText 参数_提示文本 =L"",int 参数_状态 = -1);
	bool 置缩进(int 参数_缩进距离);
	void 置图片组(TImageList& 参数_图片组,int 参数_类型 = -1);
	bool 绑定(HWND 参数_父窗口,int 参数_资源ID,bool 参数_使用默认字体);
	bool 绑定窗口句柄(HWND 参数_父窗口);
	int 背景图显示方式(int 参数_图片显示方式 = 0);
	int 背景色(int 参数_背景色 = 0);
	int 文本色(int 参数_文本色 = 0);
	int 取按钮数(){return (int)SendMsg (TB_BUTTONCOUNT, 0, 0);}
	int 取按钮ID(int 参数_按钮索引);
	bool 置按钮ID(int 参数_按钮索引,int 参数_按钮ID);
	int 取按钮索引(int 参数_按钮ID);
	bool 加入状态(int 参数_按钮索引,int 参数_按钮状态 = 0);
	bool 去除状态(int 参数_按钮索引,int 参数_按钮状态 = 0);
	//@备注 取回指定按钮的状态，状态值为 0 或者以下常量值任意组合(相加)： 1: 常量_选中； 2: 常量_按下； 4: 常量_禁止； 8: 常量_隐藏； 16: 常量_变灰。 可以用"位与"命令来判断指定的状态值是否被置位，如："如果真 (位与 (工具条1.取状态 (0)，常量_禁止) = 常量_禁止)"语句即可判断工具条1的第一个按钮是否已被禁止。
	int 取状态(int 参数_按钮索引);
	bool 判断状态(int 参数_按钮索引,int 参数_状态类型);
	bool 删除按钮(int 参数_按钮索引);
	CXText 取标题(int 参数_按钮索引);
	bool 置标题(int 参数_按钮索引,CXText 参数_标题 = L"");
	int 取类型(int 参数_按钮索引);
	bool 置类型(int 参数_按钮索引,int 参数_类型);
	//备注 取回指定按钮的图片索引，图片索引指向图片组属性中的某一图片，从 0 开始，-1 表示本按钮无图片标志。如果按钮是一个分割条则返回其宽度。
	int 取图片(int 参数_按钮索引);
	//@备注 设置指定按钮的图片索引，图片索引指向图片组属性中的某一图片，从 0 开始，-1 表示本按钮无图片标志。如果按钮是一个分割条则设置其宽度。
	bool 置图片(int 参数_按钮索引,int 参数_图片索引);
	//@备注 取得按钮的宽度和高度。
	POINT 取按钮尺寸();
	//@备注 设置按钮的宽度和高度。需要插入按钮之后才能设置
	bool 置按钮尺寸(int 参数_宽度,int 参数_高度);
	//@备注 取按钮在工具条里的矩形位置。
	RECT 取按钮矩形(int 参数_按钮索引);
	TImageList 取图片组(int 参数_类型);
	void 自动大小();
	bool 置按钮数值(int 参数_按钮索引,int 参数_数值);
	int 取按钮数值(int 参数_按钮索引);
	bool 置按钮宽度(int 参数_按钮索引,int 参数_宽度);
	int 取按钮宽度(int 参数_按钮索引);
	//@备注 函数 整型 OnClick(HWND hWnd ,int id)
	void 事件_被单击(vint 参数_事件指针){SetMember ("OnClick", 参数_事件指针);}
	//@备注 函数 整型 OnDropDown(HWND hWnd,整型 id,整型 X坐标,整型 Y坐标)
	void 事件_被下拉(vint 参数_事件指针){SetMember ("OnDropDown", 参数_事件指针);}
	//@备注 函数 整型 OnHotItemChange(HWND hWnd,整型 旧ID,整型 新ID,整型 改变类型【工具热点改变_ 开头常量】)
	void 事件_按钮热点被改变(vint 参数_事件指针){SetMember ("OnHotItemChange", 参数_事件指针);}
	//@备注 函数 整型 OnDeletingButton(HWND hWnd,整型 id)
	void 事件_按钮将被删除(vint 参数_事件指针){SetMember ("OnDeletingButton", 参数_事件指针);}
};
//@别名 超级列表框类
class TListView : public zyCtrol
{
public:
	//@隐藏{
	TListView() {
		SetName(L"超级列表框类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual void Destroy();
	virtual void OnNCDestroy();
	void _快速排序(CXVector<黑月超列信息>& 参数_列表框信息数组,int 参数_左边 = 1,int 参数_右边 = 0,int 参数_排序方式 = -1,int 参数_列索引 = 0,bool 参数_逆向 = false);
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	int 插入列(int 参数_插入位置 = -1,CXText 参数_标题文本 = L"",int 参数_列宽 = -1,int 参数_对齐方式 = -1,int 参数_图片索引 = -1,bool 参数_列图片是否居右 =  false);
	int 取列数();
	int 取表项数();
	int 插入表项(int 参数_插入位置 = -1,CXText 参数_标题文本 = L"",int 参数_图片索引 = -1,int 参数_状态图片索引 = -1,int 参数_缩进数目 = -1,int 参数_项目数值 = -1,int 参数_分组ID = -1);
	bool 置标题(int 参数_表项索引,int 参数_列索引 = 0,CXText 参数_欲置入标题 = L"");
	int 添加超列扩展风格(int 参数_扩展风格);
	bool 绑定(HWND 参数_父窗口,int 参数_资源ID,bool 参数_使用默认字体);
	bool 绑定窗口句柄(HWND 参数_窗口句柄);
	//@备注 必须要启用Window通用组件6.0版。成功返回分组索引，失败返回-1。要使用分组功能要先调用"超级列表框.启用分组()"，然后在 插入表项 时指定分组ID
	int 插入分组(int 参数_插入位置 = -1,int 参数_分组ID = 1,CXText 参数_组头标题 =L"",CXText 参数_页脚标题 =L"",int 参数_对齐方式 = NULL,int 参数_状态 = NULL);
	bool 启用分组(bool 参数_是否启用);
	int 取表项分组ID(int 参数_表项索引);
	bool 置表项分组ID(int 参数_表项索引,int 参数_分组ID);
	CXText 取分组头标题(int 参数_分组ID);
	CXText 取分组页脚标题(int 参数_分组ID);
	int 取分组对齐方式(int 参数_分组ID);
	bool 置分组对齐方式(int 参数_分组ID,int 参数_对齐方式);
	bool 置分组头标题(int 参数_分组ID,CXText 参数_标题);
	bool 置分组页脚标题(int 参数_分组ID,CXText 参数_标题);
	int 取分组状态(int 参数_分组ID);
	bool 置分组状态(int 参数_分组ID,int 参数_状态);
	int 取分组ID(int 参数_分组索引);
	int 取分组数(){return (int)SendMsg (LVM_GETGROUPCOUNT, 0, 0);}
	//@备注 返回值：整型【小于0表示 分组ID1< 分组ID2；大于0表示 分组ID1> 分组ID2；0相等】 (整型 分组ID1,整型 分组ID2,整型 用户数据)
	bool 排序分组(void* 参数_回调函数,LPARAM 参数_用户数据);
	CXText 取标题(int 参数_表项索引,int 参数_列索引,int 参数_长度 =260);
	//@备注 取回指定表项或子项的图片索引，图片索引指向图片组属性中的某一图片，从 0 开始，-1 表示无图片
	int 取图片(int 参数_表项索引,int 参数_列索引 =0);
	//@备注 取回指定表项的当前状态图片索引，图片索引指向状态图片组属性中的某一图片，从 0 开始，-1 表示无图片。如果有"超列扩展_显示检查框"风格，返回值是当前检查框的选中状态，1表示被选中，0表示未选中。
	int 取状态图片(int 参数_表项索引);
	int 取缩进数目(int 参数_表项索引);
	int 取表项数值(int 参数_表项索引);
	int 取表项状态(int 参数_表项索引);
	bool 置表项状态(int 参数_表项索引,int 参数_添加的状态,int 参数_移除的状态);
	bool 置图片(int 参数_表项索引,int 参数_列索引,int 参数_图片索引 = -1);
	bool 置状态图片(int 参数_表项索引,int 参数_状态图片索引 = -1);
	bool 置缩进数目(int 参数_表项索引,int 参数_缩进数目 =0);
	bool 置表项数值(int 参数_表项索引,int 参数_表项数值 = 0);
	int 取被选择表项(CXVector<int>& 参数_被选择表项数组);
	int 取被选中表项(CXVector<int>& 参数_被选中表项数组);
	int 取已选择表项数(){return (int)SendMsg (LVM_GETSELECTEDCOUNT, 0, 0);}
	bool 是否被选择(int 参数_表项索引){return SendMsg (LVM_GETITEMSTATE, 参数_表项索引, LVIS_SELECTED) == LVIS_SELECTED;}
	int 取现行选中项(){return (int)SendMsg (LVM_GETNEXTITEM, -1, LVNI_SELECTED);}
	bool 置现行选中项(int 参数_表项索引);
	bool 选择表项(int 参数_表项索引);
	bool 取消表项选择(int 参数_表项索引);
	//@备注 参数一：lParam1(表项数值1)整数型，参数二：lParam2(表项数值2)整数型，参数三：lParamSort(参数_排序参数)整数型。如果返回参数一小于参数二为由小到大排序，如果返回参数二小于参数一为由大到小排序。
	bool 排序表项(int 参数_排序参数,void* 参数_排序子程序){
		return SendMsg (LVM_SORTITEMS, 参数_排序参数, (LPARAM)参数_排序子程序) != 0;
	}
	int 删除表项(int 参数_表项索引){return (int)SendMsg (LVM_DELETEITEM, 参数_表项索引, 0);}
	int 删除列(int 参数_列索引){return (int)SendMsg (LVM_DELETECOLUMN, 参数_列索引, 0);}
	int 全部删除(){return (int)SendMsg (LVM_DELETEALLITEMS, 0, 0);}
	int 查找表项(CXText 参数_标题文本,int 参数_起始位置 = -1,bool 参数_是否精确匹配 = true,bool 参数_查找不到是否从头开始 = true);
	int 查找表项数值(int 参数_表项数值,int 参数_起始位置 = -1,bool 参数_查找不到是否从头开始 = true);
	bool 保证显示(int 参数_表项索引,bool 参数_是否保证显示 = true);
	bool 自动排列(bool 参数_对齐到网格);
	CXText 取列标题(int 参数_列索引);
	int 取列对齐方式(int 参数_列索引);
	bool 置列对齐方式(int 参数_列索引,int 参数_对齐方式);
	int 取列宽(int 参数_列索引);
	int 取现行选择列();
	void 置现行选择列(int 参数_列索引);
	int 取列图片(int 参数_列索引);
	bool 图片是否居右(int 参数_列索引);
	bool 置列标题(int 参数_列索引,CXText 参数_标题文本);
	bool 置列宽(int 参数_列索引,int 参数_欲置入宽度 = -1);
	bool 置列图片(int 参数_列索引,int 参数_图片索引 =-1);
	bool 取列矩形(int 参数_表项索引,int 参数_列索引,RECT& 参数_矩形结构,int 参数_取出类型);
	void 进入编辑(int 参数_表项索引);
	//@备注 会发送"事件_结束编辑"
	void 取消编辑(){SendMsg (LVM_CANCELEDITLABEL, 0, 0);}
	黑月超列信息 取项目数据(int 参数_表项索引);
	int 取所有项目数据(CXVector<黑月超列信息>& 参数_列表框信息数组);
	void 高速插入表项(int 参数_插入位置,CXVector<黑月超列信息>& 参数_列表框信息数组,int 参数_排序方式,int 参数_列索引 = 0,bool 参数_逆向 = false);
	bool 置表项(CXBytes &参数_表项数据);
	CXBytes 取表项();
	void 刷新显示();
	int 取可见第一项();
	int 取可见表项数();
	int 取编辑框句柄();
	void 取表项间距(short& 参数_水平间距,short& 参数_垂直间距,bool 参数_列表框类型);
	int 取坐标表项索引(int 参数_横坐标,int 参数_纵坐标,int& 参数_表项索引,int& 参数_列索引,int& 参数_分组ID);
	bool 取表项位置(int 参数_表项索引,POINT& 参数_坐标位置);
	bool 取表项矩形(int 参数_表项索引,RECT& 参数_矩形,int 参数_取出类型);
	TImageList 取图片组(int 参数_类型);
	void 置图片组(TImageList& 参数_图片组,int 参数_类型);
	TImageList 创建拖放图片组(int 参数_表项索引,POINT& 参数_参考坐标);
	bool 滚动列表框(int 参数_水平位置,int 参数_垂直位置);
	int 取超列扩展风格();
	int 移除超列扩展风格(int 参数_扩展风格);
	int 文本色(int 参数_文本色=0);
	int 文本背景色(int 参数_文本背景颜色=0);
	int 背景色(int 参数_背景色,bool 参数_是否立即重画);
	int 取显示类型();
	bool 置显示类型(int 参数_显示类型);
	TEditBox& 取编辑框();
	int 取表项索引(int 参数_标志,int 参数_起始索引 =-1);
	void 置表项坐标(int 参数_表项索引,int 参数_X,int 参数_Y);
	POINT 取表项坐标(int 参数_表项索引);
	int 置大图标间距(int 参数_水平间距,int 参数_垂直间距);
	//@备注 函数 整型 OnItemChange(HWND hWnd,整型 表项索引,整型 项目数值)
	void 事件_当前表项被改变(vint 参数_事件指针){SetMember ("OnItemChange", 参数_事件指针);}
	//@备注 返回值：整型【0允许选择，1禁止选择】 函数 整型 OnHotTrack(HWND hWnd,整型 表项索引,整型 列索引)
	void 事件_表项跟踪(vint 参数_事件指针){SetMember ("OnHotTrack", 参数_事件指针);}
	//@备注 函数 整型 OnColumnClick(HWND hWnd,整型 列索引)
	void 事件_表头被单击(vint 参数_事件指针){SetMember ("OnColumnClick", 参数_事件指针);}
	//@备注 函数 整型 OnItemActivate(HWND hWnd,整型 表项索引,整型 列索引)
	void 事件_表项被激活(vint 参数_事件指针){SetMember ("OnItemActivate", 参数_事件指针);}
	//@备注 返回值：整型【0允许编辑，1禁止编辑】函数 整型 OnBeginEdit(HWND hWnd,整型 表项索引)
	void 事件_开始编辑(vint 参数_事件指针){SetMember ("OnBeginEdit", 参数_事件指针);}
	//@备注 返回值：整型【0允许编辑，1禁止编辑】函数 整型 OnEndEdit(HWND hWnd,整型 表项索引,整型 标题[Unicode文本指针-1])
	void 事件_结束编辑(vint 参数_事件指针){SetMember ("OnEndEdit", 参数_事件指针);}
	//@备注 函数 整型 OnClick(HWND hWnd,整型 表项索引,整型 列索引,整型 X,整型 Y,整型 功能键状态[1、Alt；2、Ctrl；4、Shift-1])
	void 事件_左键单击表项(vint 参数_事件指针){SetMember ("OnClick", 参数_事件指针);}
	//@备注 返回值：整型【0默认处理，1阻止默认处理】 函数 整型 OnRClick(HWND hWnd,整型 表项索引,整型 列索引,整型 X,整型 Y,整型 功能键状态[1、Alt；2、Ctrl；4、Shift-1])
	void 事件_右键单击表项(vint 参数_事件指针){SetMember ("OnRClick", 参数_事件指针);}
	//@备注 函数 整型 OnDBClick(HWND hWnd,整型 表项索引,整型 列索引,整型 X,整型 Y,整型 功能键状态[1、Alt；2、Ctrl；4、Shift-1])
	void 事件_双击表项(vint 参数_事件指针){SetMember ("OnDBClick", 参数_事件指针);}
	//@备注 函数 整型 OnCheckChange(HWND hWnd,整型 表项索引,整型 检查框状态)
	void 事件_检查框状态被改变(vint 参数_事件指针){SetMember ("OnCheckChange", 参数_事件指针);}
	//@备注 函数 整型 OnBeginDrag(HWND hWnd,整型 表项索引)
	void 事件_开始拖放(vint 参数_事件指针){SetMember ("OnBeginDrag", 参数_事件指针);}
};
//@别名 树型框类
class TTreeView : public zyCtrol
{
public:
	//@隐藏{
	TTreeView() {
		SetName(L"树形框类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual void Destroy();
	virtual void OnNCDestroy();
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	INT_PTR 加入项目(INT_PTR 参数_父项目句柄 = 0,CXText 参数_项目文本 = L"",int 参数_图片索引 = -1,int 参数_选择图片索引 = -1,INT_PTR 参数_项目数值 = -1 ,int 参数_加入方式 = -1);
	INT_PTR 插入项目(INT_PTR 参数_父项目句柄,INT_PTR 参数_项目句柄,CXText 参数_项目文本,int 参数_图片索引=-1,int 参数_选择图片索引=-1,INT_PTR 参数_项目数值=0);
	void 扩展(INT_PTR 参数_项目句柄);
	void 收缩(INT_PTR 参数_项目句柄);
	bool 绑定(HWND 参数_父窗口,int 参数_资源ID,bool 参数_使用默认字体 = true);
	bool 绑定窗口句柄(HWND 参数_窗口句柄);
	INT_PTR 取项目句柄(int 参数_标志,INT_PTR 参数_项目句柄 = 0){return (int)SendMsg (TVM_GETNEXTITEM, 参数_标志, 参数_项目句柄);}
	void 枚举项目句柄(CXVector<int>& 参数_项目句柄数组);
	int 取项目数(){return (int)SendMsg (TVM_GETCOUNT, 0, 0);}
	int 取缩进层次(INT_PTR 参数_项目句柄);
	CXText 取项目文本(INT_PTR 参数_项目句柄);
	int 取图片(INT_PTR 参数_项目句柄);
	int 取状态图片(INT_PTR 参数_项目句柄);
	int 取选择图片(INT_PTR 参数_项目句柄);
	INT_PTR 取项目数值(INT_PTR 参数_项目句柄);
	bool 置项目文本(INT_PTR 参数_项目句柄,CXText 参数_欲置入的项目文本);
	bool 置图片(INT_PTR 参数_项目句柄,int 参数_图片索引);
	bool 置状态图片(INT_PTR 参数_项目句柄,int 参数_图片索引);
	bool 置选择图片(INT_PTR 参数_项目句柄,int 参数_图片索引);
	bool 置项目数值(INT_PTR 参数_项目句柄,INT_PTR 参数_欲置入的项目数值);
	void 保证显示(INT_PTR 参数_项目句柄);
	黑月树型框信息 取项目数据(INT_PTR 参数_项目句柄);
	RECT 取项目矩形(INT_PTR 参数_项目句柄,bool 参数_是否只包含标题);
	bool 删除项目(INT_PTR 参数_项目句柄){return SendMsg (TVM_DELETEITEM, 0, 参数_项目句柄) != 0;}
	void 清空(){SendMsg (TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT);}
	INT_PTR 取父项目(INT_PTR 参数_项目句柄){return SendMsg (TVM_GETNEXTITEM, TVGN_PARENT, 参数_项目句柄);}
	bool 是否有子项目(INT_PTR 参数_项目句柄);
	bool 是否已扩展(INT_PTR 参数_项目句柄);
	bool 加粗(INT_PTR 参数_项目句柄);
	bool 取消加粗(INT_PTR 参数_项目句柄);
	void 进入编辑(INT_PTR 参数_项目句柄){SendMsg (TVM_EDITLABELW, 0, 参数_项目句柄);}
	bool 是否选中(INT_PTR 参数_项目句柄);
	bool 置检查框状态(INT_PTR 参数_项目句柄,int 参数_状态);
	int 取检查框状态(INT_PTR 参数_项目句柄);
	void 置现行选中项(INT_PTR 参数_项目句柄){SendMsg (TVM_SELECTITEM, TVGN_CARET, 参数_项目句柄);}
	INT_PTR 取现行选中项(){return SendMsg (TVM_GETNEXTITEM, TVGN_CARET, 0);}
	int 取可显示数(){return (int)SendMsg (TVM_GETVISIBLECOUNT, 0, 0);}
	int 取可视第一项(){return (int)SendMsg (TVM_GETNEXTITEM, TVGN_FIRSTVISIBLE, 0);}
	int 取所有选中项(CXVector<INT_PTR>& 参数_选中项数组);
	bool 排序子项(INT_PTR 参数_项目句柄){return SendMsg (TVM_SORTCHILDREN, 0, 参数_项目句柄) != 0;}
	bool 排序子项回调(INT_PTR 参数_项目句柄,void* 参数_排序子程序,int 参数_排序参数);
	bool 标志插入(INT_PTR 参数_项目句柄,int 参数_插入位置);
	bool 标志删除(){return SendMsg (TVM_SETINSERTMARK, 0, 0) != 0;}
	int 标志置颜色(int 参数_颜色值){return (int)SendMsg (TVM_SETINSERTMARKCOLOR, 0, 参数_颜色值);}
	int 标志取颜色(){return (int)SendMsg (TVM_GETINSERTMARKCOLOR, 0, 0);}
	void 置图片组(TImageList& 参数_图片组,int 参数_类型 = 0);
	TImageList 取图片组(int 参数_类型);
	TImageList 创建拖放图片组(INT_PTR 参数_项目句柄);
	INT_PTR 取坐标项目(int 参数_横向坐标,int 参数_纵向坐标,int& 参数_位置信息);
	int 取子项数(INT_PTR 参数_项目句柄);
	int 取所有子项目(INT_PTR 参数_项目句柄,CXVector<INT_PTR>& 参数_子项目句柄数组,bool 参数_递归);
	CXText 取结束编辑文本();
	TEditBox& 取编辑框();
	int 项目高度(int 参数_高度 = NULL);
	int 缩进距离(int 参数_距离 = NULL);
	int 文本色(int 参数_颜色值 = NULL);
	int 背景色(int 参数_颜色值 = NULL);
	int 连线色(int 参数_颜色值 = NULL);
	//@备注 函数 整型 OnSelChanged(HWND hWnd,INT_PTR 项目句柄,整型 选择方式【0：未知  1：鼠标  2：键盘】)
	void 事件_项目被选择(vint 参数_事件指针){SetMember ("OnSelChanged", 参数_事件指针);}
	//@备注 函数 整型 OnDBClick(HWND hWnd)
	void 事件_双击项目(vint 参数_事件指针){SetMember ("OnDBClick", 参数_事件指针);}
	//@备注 返回值：整型【0允许编辑，1禁止编辑】函数 整型 OnBeginEdit(HWND hWnd,INT_PTR 项目句柄,整型 标题[Unicode文本指针-1]) 
	void 事件_开始编辑(vint 参数_事件指针){SetMember ("OnBeginEdit", 参数_事件指针);}
	//@备注 返回值：整型【0允许编辑，1禁止编辑】函数 整型 OnEndEdit(HWND hWnd,INT_PTR 项目句柄,整型 标题[Unicode文本指针-1])
	void 事件_结束编辑(vint 参数_事件指针){SetMember ("OnEndEdit", 参数_事件指针);}
	//@备注 返回值：整型【0允许扩展，1禁止扩展】函数 整型 OnItemExpand(HWND hWnd,INT_PTR 项目句柄)
	void 事件_即将扩展(vint 参数_事件指针){SetMember ("OnItemExpand", 参数_事件指针);}
	//@备注 返回值：整型【0允许收缩，1禁止收缩】函数 整型 OnItemCollapse(HWND hWnd,INT_PTR 项目句柄)
	void 事件_即将收缩(vint 参数_事件指针){SetMember ("OnItemCollapse", 参数_事件指针);}
	//@备注 返回值：整型【0默认处理】 函数 整型 OnRClick(HWND hWnd,INT_PTR 项目句柄)
	void 事件_右键单击项目(vint 参数_事件指针){SetMember ("OnRClick", 参数_事件指针);}
	//@备注 函数 整型 OnCheckChange(HWND hWnd,INT_PTR 项目句柄,整型 检查框状态)
	void 事件_检查框状态被改变(vint 参数_事件指针){SetMember ("OnCheckChange", 参数_事件指针);}
	//@备注 返回值：整型【0默认处理】 函数 整型 OnClick(HWND hWnd,INT_PTR 项目句柄)
	void 事件_左键单击项目(vint 参数_事件指针){SetMember ("OnClick", 参数_事件指针);}
};
//@别名 选择夹类
class TTabControl : public zyCustomCtrol
{
public:
	//@隐藏{
	TTabControl() {
		SetName(L"选择夹类");
		SetMember(L"this", (vint)this);
	};
	std::vector<TPanel> panels;
	std::map<UINT_PTR, CXText> m_HashToolTips;
	int g_i=1;
	void ShowPanel(HWND hWndTab,int index);
	void SetPanelSize(HWND hWndTab,LPARAM Panel);
	void SetPanelsSize(HWND hWndTab);
	bool DeleteAllPanel(HWND hWndTab);
	void DeletePanel(HWND Panel);
	virtual void Destroy();
	virtual void OnNCDestroy();
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	int 插入子夹(zyWindow& 参数_面板 = TPanel(),int 参数_子夹索引 = -1,wchar_t* 参数_子夹名称 = nullptr,int 参数_图片索引 = -1,CXText 参数_提示文本 = L"");
	HWND 取面板句柄(int 参数_子夹索引);
	int 取子夹数();
	virtual bool 绑定(HWND 参数_父窗口,int 参数_资源ID,bool 参数_使用默认字体 = true);
	bool 绑定窗口句柄(HWND 参数_窗口句柄);
	int 添加子夹(zyWindow& 参数_面板,wchar_t* 参数_子夹名称 = nullptr,int 参数_图片索引 = -1,CXText 参数_提示文本 = L"");
	int 取子夹行数();
	RECT 取子夹矩形(int 参数_子夹索引);
	CXText 取子夹名称(int 参数_子夹索引);
	bool 置子夹名称(int 参数_子夹索引,CXText 参数_子夹名称);
	bool 置提示文本(int 参数_子夹索引,CXText 参数_提示文本);
	CXText 取提示文本(int 参数_子夹索引);
	int 取子夹图片(int 参数_子夹索引);
	bool 置子夹图片(int 参数_子夹索引,int 参数_图片索引);
	bool 清空();
	bool 删除子夹(int 参数_子夹索引);
	int 取现行选中子夹();
	void 置现行选中子夹(int 参数_子夹索引);
	bool 高亮子夹(int 参数_子夹索引,bool 参数_是否高亮 = true);
	int 取坐标子夹(int 参数_横坐标,int 参数_纵坐标);
	int 置子夹头尺寸(int 参数_宽度,int 参数_高度);
	TImageList 取图片组();
	void 置图片组(TImageList& 参数_图片组);
	int 置选择夹扩展风格(int 参数_选择夹扩展风格){return (int)SendMsg (TCM_SETEXTENDEDSTYLE, 0, 参数_选择夹扩展风格);}
	int 取选择夹扩展风格(){return (int)SendMsg (TCM_GETEXTENDEDSTYLE, 0, 0);}
	int 置子夹最小宽度(int 参数_最小宽度){return (int)SendMsg (TCM_SETMINTABWIDTH, 0, 参数_最小宽度);}
	void 置子夹内边距(int 参数_水平边距,int 参数_垂直边距);
	bool 隐藏自身(bool 参数_隐藏自身);
	bool 取面板(int 参数_子夹索引,zyWindow& 参数_面板);
	void 置面板边缘扩展(RECT& 参数_边缘扩展);
	void 重置面板尺寸(){SetPanelsSize (取窗口句柄 ());}
	//@备注 函数 整型 OnClick(HWND hWnd)
	void 事件_被单击(vint 参数_事件指针){SetMember ("OnClick", 参数_事件指针);}
	//@备注 函数 整型 OnRClick(HWND hWnd)
	void 事件_右键单击(vint 参数_事件指针){SetMember ("OnRClick", 参数_事件指针);}
	//@备注 函数 整型 OnSelChange(HWND hWnd)
	void 事件_子夹被改变(vint 参数_事件指针){SetMember ("OnSelChange", 参数_事件指针);}
	//@备注 返回值：整型【非0禁止改变，0允许改变】 函数 整型 OnSelChanging(HWND hWnd)
	void 事件_将改变子夹(vint 参数_事件指针){SetMember ("OnSelChanging", 参数_事件指针);}
};
//@别名 进度条类
class TProgressBar : public zyCtrol
{
public:
	//@隐藏{
	TProgressBar() {
		SetName(L"组合框类");
		SetMember(L"this", (vint)this);
	}
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	int 位置(int 参数_位置 =  -1);
	//@备注 返回之前的范围，低16位表示最小位置，高16位表示最大位置
	int 置范围(int 参数_最小位置,int 参数_最大位置){
		return (int)SendMsg (PBM_SETRANGE, 0, MAKELPARAM (参数_最小位置, 参数_最大位置));
	}
	POINT 取范围(){
		POINT rang = {0};
		SendMsg (PBM_GETRANGE, 0, (LPARAM)&rang);
		return rang;
	}
	int 置前景色(int 参数_前景色 = 0){return (int)SendMsg (PBM_SETBARCOLOR, 0, 参数_前景色);}
	int 取前景色(){return (int)SendMsg (PBM_GETBARCOLOR, 0, 0);}
	int 置背景色(int 参数_背景色 = 0){return (int)SendMsg (PBM_SETBKCOLOR, 0, 参数_背景色);}
	int 取背景色(){return (int)SendMsg (PBM_GETBKCOLOR, 0, 0);}
	int 置跨度值(int 参数_跨度值){return (int)SendMsg (PBM_SETSTEP, 参数_跨度值, 0);}
};
//@别名 滑块条类
class TTrackBar : public zyCommandCtrol
{
public:
	//@隐藏{
	TTrackBar() {
		SetName(L"滑块条类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual void Destroy();
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	vint 背景色(vint 参数_背景色);
	int 位置(int 参数_位置 = -1);
	int 最小位置(int 参数_最小位置 = NULL);
	int 最大位置(int 参数_最大位置 = NULL);
	int 首选择位置(int 参数_首选择位置 = NULL);
	int 选择长度(int 参数_选择长度 = NULL);
	int 滑块跨度(int 参数_滑块跨度 = NULL);
	void 置刻度单位值(int 参数_刻度单位值);
	int 行改变值(int 参数_行改变值 = NULL);
	int 页改变值(int 参数_页改变值 = NULL);
	void 清除选择(){SendMsg (TBM_CLEARSEL, 0, 0);}
	void 清除刻度(){SendMsg (TBM_CLEARTICS, 0, 0);}
	//@备注 函数 整型 OnPosChange(HWND hWnd,整型 位置)
	void 事件_位置被改变(vint 参数_事件指针){SetMember (L"OnPosChange",参数_事件指针);}
};
//@分组}

//@分组{ 控件入口.标准控件
//@别名 列表框类
class TListBox : public zyCommandCtrol
{
public:
	//@隐藏{
	TListBox() {
		SetName(L"列表框类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);

	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	int 加入项目(CXText& 参数_项目文本,int 参数_项目数值 = 0);
	int 插入项目(CXText 参数_内容,int 参数_插入位置 = -1,int 参数_项目数值 = 0);
	//@备注 删除指定项目。成功返回真，失败返回假。
	bool 删除项目(int 参数_项目索引){return SendMsg (LB_DELETESTRING, 参数_项目索引, 0) != LB_ERR;}
	//@备注 删除列表框中的所有项目。成功返回真，失败返回假。
	bool 清空(){return SendMsg (LB_RESETCONTENT, 0, 0) != LB_ERR;}
	//@备注 本方法仅适用于单选列表框。在所有项目中寻找首部包含指定文本的项目，如找到，则选中它，并返回该项目的位置索引，否则返回 -1 。本命令仅在单选列表框中使用，如果在多选列表框中使用，将返回 -1 。
	int 选择项目文本(CXText 参数_欲选择的项目文本,int 参数_起始索引 = -1);
	//@备注 本方法仅适用于多选择列表框。选择指定项目索引的项目。成功返回真，失败返回假。
	bool 选择项目索引(int 参数_项目索引,bool 参数_是否选择 = true);
	//@备注 本方法仅适用于多选择列表框才能成功。选择指定起始点和结束点的项目。成功返回真，失败返回假。
	bool 选择多项(int 参数_起始索引,int 参数_结束索引,bool 参数_是否选择 = true);
	int 查找(CXText 参数_匹配文本,int 参数_起始索引 = -1);
	int 精确查找(CXText 参数_匹配文本,int 参数_起始索引 = -1);
	int 取现行选中项();
	int 置现行选中项(int 参数_项目索引);
	int 取项目数();
	int 取项目数值(int 参数_项目索引);
	bool 置项目数值(int 参数_项目索引,int 参数_数值 = 0);
	bool 是否被选择(int 参数_项目索引);
	int 取已选择项目数();
	int 取所有被选择项(CXVector<int>& 参数_索引数组);
	CXText 取项目文本(int 参数_项目索引);
	int 取顶端可见项();
	bool 置顶端可见项(int 参数_项目索引);
	int 取焦点项目();
	bool 置焦点项目(int 参数_项目索引);
	int 取项目高度();
	RECT 取项目矩形(int 参数_项目索引);
	bool 置项目高度(int 参数_高度);
	bool 置列宽度(int 参数_列宽度);
	int 取坐标项目(int 参数_横坐标,int 参数_纵坐标);
	//@备注 函数 整型 OnSelChange(HWND hWnd,整型 id)
	void 事件_列表项被选择(vint 参数_事件指针){SetMember (L"OnSelChange", 参数_事件指针);}
	//@备注 函数 整型 OnItemDBClick(HWND hWnd,整型 id)
	void 事件_点击选择(vint 参数_事件指针){SetMember (L"OnItemDBClick", 参数_事件指针);}
	//@备注 函数 整型 OnSelCancel(HWND hWnd,整型 id)
	void 事件_双击选择(vint 参数_事件指针){SetMember (L"OnSelCancel", 参数_事件指针);}
};
//@别名 滚动条类
class TScrollBar : public zyCommandCtrol
{
public:
	//@隐藏{
	TScrollBar() {
		SetName(L"滚动条类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual void Destroy();
	void _初始化滚动条();
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 绑定窗口句柄(HWND 参数_窗口句柄);
	bool 绑定(HWND 参数_父窗口,int 参数_资源ID,bool 参数_使用默认字体 = true);
	vint 背景色(vint 参数_背景色);
	int 位置(int 参数_位置 = -1);
	//@别名 行改变值()
	INT Linechangevalue(INT value);
	//@备注 取或置滚动条的最小位置
	//@参数 参数留空则取,否则位置,默认为空
	//@返回 留空则返回最小位置
	//@别名 最小位置(位置)
	INT Minimumpos(INT pos = NULL);
	//@备注 取或置滚动条的最大位置
	//@参数 参数留空则取,否则位置,默认为空
	//@返回 留空则返回最大位置
	//@别名 最大位置(位置)
	INT Maximumpos(INT pos = NULL);
	//@备注 取或置滚动条的页改变值
	//@参数 参数留空则取,否则位置,默认为空
	//@返回 留空则返回最大位置
	//@别名 页改变值(值)
	INT Pagechangevalue(INT value = NULL);
	//@备注 函数 整型 OnPosChange(HWND hWnd,整型 位置)
	void 事件_位置被改变(vint 参数_事件指针){SetMember (L"OnPosChange",参数_事件指针);}
};
//@别名 图片框类
class TPictureBox : public zyCtrol
{
public:
	//@隐藏{
	TPictureBox() {
		SetName(L"图片框类");
		SetMember(L"this", (vint)this);
		SetMember(L"ShowImageType",图片显示方式_平铺);
	}
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual void Destroy();
	virtual void OnNCDestroy();
	void zyPictureBox_OnTimer(HWND hWnd);
	bool InitGif(GPImage& image);
	bool InitGif(wchar_t* image);
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	//@别名 图片_路径()
	void BackImage(wchar_t* 路径);
	void 图片(GPImage& 图像);
	int 图片显示方式(int 参数_图片显示方式);
	bool 播放动画(bool 参数_播放动画);
	int 背景色(int 参数_背景色);
};
//@别名 编辑框类
class TEditBox : public zyCommandCtrol
{
public:
	//@隐藏{
	TEditBox() {
		SetName(L"编辑框类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual void Destroy();
	virtual void OnNCDestroy();
	//@隐藏}
	void 取光标所在行列(int &参数_行号,int &参数_列号);
	int 取坐标字符(int 参数_水平坐标,int 参数_垂直坐标);
	POINT 取字符坐标(int 参数_字符位置);
	int 取行号(int 参数_字符位置){return (int)SendMsg (EM_LINEFROMCHAR, 参数_字符位置, 0);}
	int 取行首位置(int 参数_行号 = -1){return (int)SendMsg (EM_LINEINDEX, 参数_行号, 0);}
	int 取行文本长度(int 参数_行号){return (int)SendMsg (EM_LINELENGTH, SendMsg (EM_LINEINDEX, 参数_行号, 0), 0);}
	CXText 取行文本(int 参数_行号);
	int 取行数(){return (int)SendMsg(EM_GETLINECOUNT,0,0);}
	bool 滚动到光标();
	bool 滚动(int 参数_水平字符数 = 0,int 参数_行数 = 1);
	int 取可见第一行(){return (int)SendMsg(EM_GETFIRSTVISIBLELINE,0,0);}
	void 置内容改变标志(bool 参数_是否改变){SendMsg(EM_SETMODIFY,参数_是否改变,0);}
	bool 内容是否改变(){return SendMsg(EM_GETMODIFY,0,0) != 0;}
	int 删除(){return(int)SendMsg(WM_CLEAR,0,0);}
	int 粘贴(){return(int)SendMsg(WM_PASTE,0,0);}
	int 复制(){return(int)SendMsg(WM_COPY,0,0);}
	int 剪切(){return(int)SendMsg(WM_CUT,0,0);}
	int 清除撤消缓冲区(){return (int)SendMsg(EM_EMPTYUNDOBUFFER,0,0);}
	void 撤销(){SendMsg(EM_UNDO,0,0);}
	bool 可否撤销(){return SendMsg(EM_CANUNDO,0,0) != 0;}
	void 移动(int 参数_左边 = 0,int 参数_顶边 = 0,int 参数_宽度 = 0,int 参数_高度 = 0,bool 参数_是否立即重画 = true);
	bool 垂直居中(bool 参数_垂直居中);
	void 置矩形(RECT 参数_矩形);
	RECT 取矩形();
	BOOL 置只读属性(BOOL 参数_属性值 = 1){return SendMsg(EM_SETREADONLY,参数_属性值,0) != 0;}
	void 置密码遮盖符(wchar_t *参数_遮盖符){ SendMsg(EM_SETPASSWORDCHAR ,(WPARAM)参数_遮盖符,0);}
	CXText 取密码遮盖符(){return SendMsg(EM_GETPASSWORDCHAR,0,0);}
	int 最大长度(int 参数_最大长度 =0);
	void 替换文本(CXText 参数_文本 );
	void 添加文本(CXText 参数_文本 );
	void 取被选择区(int &参数_起始位置 ,int &参数_结束位置 );
	//@参数 默认为0。-1表示取消选择，-2且结束位置为-1表示光标移动到末尾,
	//@参数 默认为-1：选择从开始位置后的所有文本
	void 置被选择文本(int 参数_起始位置 = 0,int 参数_结束位置 = -1);
	CXText 内容(CXText 参数_内容 = L"");
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	//@备注 函数 整型 OnTextChange(HWND hWnd,整型 id)
	//@别名 事件_内容被改变()
	void OnTextChange(vint 参数_事件指针);

};
//@别名 图像组合框类
class TComboBoxEx : public zyCommandCtrol
{
public:
	//@隐藏{
	TComboBoxEx() {
		SetName(L"TComboBoxEx");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual void Destroy();
	virtual void OnNCDestroy();
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	int 插入项目(int 参数_插入索引 = -1,CXText 参数_项目标题 = L"",int 参数_图片索引 = -1,int 参数_选中图片索引 = -1,int 参数_覆盖图片索引 = -1,int 参数_缩进距离 = -1,int 参数_项目数值 = 0);
	bool 置现行选中项(int 参数_项目索引);
	int 取现行选中项();
	void 置图片组(TImageList& 参数_图片组);
	int 取项目数(){return (int)SendMsg (CB_GETCOUNT, 0, 0);}
	bool 删除项目(int 参数_项目索引){return SendMsg (CBEM_DELETEITEM, 参数_项目索引, 0) != CB_ERR;}
	bool 清空(){return SendMsg (CB_RESETCONTENT, 0, 0) != 0;}
	CXText 取项目文本(int 参数_项目索引);
	bool 置项目文本(int 参数_项目索引,CXText 参数_项目文本);
	int 取图片(int 参数_项目索引);
	bool 置图片(int 参数_项目索引,int 参数_图片索引);
	int 取选中图片(int 参数_项目索引);
	bool 置选中图片(int 参数_项目索引,int 参数_选中图片索引);
	int 取覆盖图片(int 参数_项目索引);
	bool 置覆盖图片(int 参数_项目索引,int 参数_图片索引);
	INT_PTR 取项目数值(int 参数_项目索引);
	bool 置项目数值(int 参数_项目索引,INT_PTR 参数_项目数值);
	int 取项目缩进(int 参数_项目索引);
	bool 置项目缩进(int 参数_项目索引,int 参数_项目缩进);
	TComboBoxEx& 取组合框();
	TEditBox& 取编辑框();
	TImageList 取图片组();
	//@备注 函数 整型 OnSelChange(HWND hWnd,整型 id)
	void 事件_列表项被选择(vint 参数_事件指针){SetMember ("OnSelChange", 参数_事件指针);}
	//@备注 函数 整型 OnEditChange(HWND hWnd,整型 id)
	void 事件_编辑内容被改变(vint 参数_事件指针){SetMember ("OnEditChange", 参数_事件指针);}
	//@备注 函数 整型 OnDropDown(HWND hWnd,整型 id)
	void 事件_将弹出列表(vint 参数_事件指针){SetMember ("OnDropDown", 参数_事件指针);}
	//@备注 函数 整型 OnCloseUp(HWND hWnd,整型 id)
	void 事件_列表被关闭(vint 参数_事件指针){SetMember ("OnCloseUp", 参数_事件指针);}
	//@备注 函数 整型 OnDBClick(HWND hWnd,整型 id)
	void 事件_双击选择(vint 参数_事件指针){SetMember ("OnDBClick", 参数_事件指针);}
};
//@别名 组合框类
class TComboBox : public zyCommandCtrol
{
public:
	//@隐藏{
	TComboBox() {
		SetName(L"组合框类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	virtual void Destroy();
	virtual void OnNCDestroy();
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	int 加入项目(wchar_t* 参数_项目文本,int 参数_项目数值);
	int 插入项目(wchar_t* 参数_项目文本,int 参数_项目索引,int 参数_项目数值);
	bool 置现行选中项(int 参数_项目索引);
	int 取现行选中项();
	bool 置最大文本长度(int 参数_最大长度);
	CXText 取项目文本(int 参数_项目索引);
	bool 置项目文本(int 参数_项目索引,CXText 参数_项目文本);
	bool 选中指定项(CXText 参数_项目文本,int 参数_起始位置 = -1);
	int 取项目数();
	TEditBox& 取编辑框();
	TListBox& 取列表框();
	int 取项目数值(int 参数_项目索引);
	bool 置项目数值(int 参数_项目索引,int 参数_数值);
	int 删除项目(int 参数_项目索引);
	bool 清空();
	bool 显示列表(bool 参数_是否显示 = true);
	int 查找(CXText 参数_欲查找文本,int 参数_起始位置 = -1);
	int 精确查找(CXText 参数_欲查找文本,int 参数_起始位置 = -1);
	RECT 取列表矩形();
	//@备注 取组合框中列表框是否可见。返回真表示可见，否则返回假。
	bool 列表是否可见(){return SendMsg (CB_GETDROPPEDSTATE, 0, 0) != 0;}
	//@备注 返回组合框中列表框的宽度(像素点)。
	int 取列表宽度(){return (int)SendMsg (CB_GETDROPPEDWIDTH, 0, 0);}
	//@备注 设置组合框中列表框的宽度(像素点)。返回现行宽度。
	int 置列表宽度(int 参数_宽度){return (int)SendMsg (CB_SETDROPPEDWIDTH, 参数_宽度, 0);}
	//@备注 返回组合框中列表框指定项目的高度(像素点)。
	int 取项目高度(int 参数_项目索引){return (int)SendMsg (CB_GETITEMHEIGHT, 参数_项目索引, 0);}
	bool 置项目高度(int 参数_新高度){return SendMsg (CB_SETITEMHEIGHT, 0, 参数_新高度) != CB_ERR;}
	bool 置被选择文本(int 参数_起始位置,int 参数_结束位置);
	void 取被选择文本(int& 参数_起始位置,int& 参数_结束位置);
	//@备注 返回组合框中列表框的可见第一项项目索引。
	int 取首可视项(){return (int)SendMsg (CB_GETTOPINDEX, 0, 0);}
	//@备注 设置组合框中列表框的可见第一项。
	bool 置首可视项(int 参数_项目索引){return SendMsg (CB_SETTOPINDEX, 参数_项目索引, 0) != CB_ERR;}
	bool 禁止F4显示列表(bool 参数_是否禁止 = false);
	//@备注 函数 整型 OnSelChange(HWND hWnd,整型 id)
	void 事件_列表项被选择(vint 参数_事件指针){SetMember ("OnSelChange", 参数_事件指针);}
	//@备注 函数 整型 OnEditChange(HWND hWnd,整型 id)
	void 事件_编辑内容被改变(vint 参数_事件指针){SetMember ("OnEditChange", 参数_事件指针);}
	//@备注 函数 整型 OnDropDown(HWND hWnd,整型 id)
	void 事件_将弹出列表(vint 参数_事件指针){SetMember ("OnDropDown", 参数_事件指针);}
	//@备注 函数 整型 OnCloseUp(HWND hWnd,整型 id)
	void 事件_列表被关闭(vint 参数_事件指针){SetMember ("OnCloseUp", 参数_事件指针);}
	//@备注 函数 整型 OnDBClick(HWND hWnd,整型 id)
	void 事件_双击选择(vint 参数_事件指针){SetMember ("OnDBClick", 参数_事件指针);}
};
//@别名 分组框类
class TGroupBox : public zyCommandCtrol
{
public:
	//@隐藏{
	TGroupBox() {
		SetName(L"分组框类");
		SetMember(L"this", (vint)this);
	}
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	CXText 标题(CXText 参数_标题 = L"");
	bool 系统主题(bool 参数_系统主题);
};
//@别名 按钮类
class TButton : public zyCommandCtrol
{
public:
	//@隐藏{
	TButton() {
		SetName(L"按钮");
		SetMember(L"this", (vint)this);
	}
	virtual void Destroy();
	virtual void OnNCDestroy();
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	//@隐藏}
	bool 创建(HWND 参数_父窗口,const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口,const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	//@备注 函数 整型 OnClick(HWND hWnd,整型 id)
	void 事件_被单击(vint 参数_事件指针);
	CXText 标题(CXText 参数_标题 = L"");
	bool 默认按钮(bool 参数_默认按钮);
	bool 取消按钮(bool 参数_取消按钮);
	void 置图标(ThIcon& 参数_图标);
	ThIcon 取图标();
};
//@别名 选择框三态类
class TCheckB3State : public TButton
{
public:
	//@隐藏{
	TCheckB3State() {
		SetName(L"选择框三态类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	//@备注 0.未选中；1.选中；2.半选中
	int 取状态(){return (int)SendMsg (BM_GETCHECK, 0, 0);}
	//@备注 0.未选中；1.选中；2.半选中
	int 置状态(int 参数_状态){return (int)SendMsg (BM_SETCHECK, 参数_状态, 0);}
};
//@别名 单选框类
class TRadioBox : public TButton
{
public:
	//@隐藏{
	TRadioBox() {
		SetName(L"单选框类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	//@别名 选中(参数_是否选中)
	bool SetSel(bool ifSel);

};
//@别名 选择框类
class TCheckBox : public TButton
{
public:
	//@隐藏{
	TCheckBox() {
		SetName(L"选择框类");
		SetMember(L"this", (vint)this);
	}
	virtual int ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	//@别名 选中(参数_是否选中)
	bool SetSel(bool ifSel);
	//@别名 置状态(参数_状态)
	int SetChek(INT nChek);
	//@别名 取状态()
	int GetChek();
};
//@别名 外形框类
class TShapeBox : public zyCommandCtrol
{
public:
	TShapeBox() {
		SetName(L"外形框类");
		SetMember(L"this", (vint)this);
	};
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
};
//@别名 透明标签类
class TAlphaLabel : public zyCustomCtrol
{
public:
	TAlphaLabel() {
		SetName(L"透明标签");
		SetMember(L"this", (vint)this);
		SetMember(L"TextColor", 0);
		SetMember(L"TextAlign", 4);
		SetMember(L"Multiple", 0);
		SetMember(L"DirectionVertical", 0);
	};
	virtual void Destroy();
	virtual void OnNCDestroy();
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
};
//@别名 标签类
class TLabel : public zyCommandCtrol
{
public:
	//@隐藏{
	TLabel();
	virtual void Destroy();
	virtual void OnNCDestroy();
	virtual int WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* bHandle);
	//@隐藏}
	bool 创建(HWND 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	bool 创建(zyWindow& 参数_父窗口, const CXText& 参数_标题 =L"", POINT &参数_位置 = 黑月坐标(0,0), POINT &参数_尺寸 = 黑月坐标(60,26), HMENU 参数_ID = 0, int 参数_窗口风格 = 0, int 参数_扩展风格 = 0);
	CXText 标题(CXText 参数_标题 = L"");
};

//@分组}
#endif
