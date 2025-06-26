#ifndef XC_FORMHELP_H

//@隐藏{
#define XC_FORMHELP_H

//#include <vector>
#include <windows.h>
#include <MsHTML.h>
#include <atlbase.h>

//@隐藏}

//@模块名称  网页填表
//@版本  1.1
//@日期  2025-02-01
//@作者  peerless
//@QQ    598762663
//@模块备注 实现对Internet Explorer_Server浏览器操作
//此模块当前示例目录中附带一个测试web和源码供参考
//注意使用前初始化COM库


//@别名 元素类型
enum web_element_type_
{
	//@别名 网页填表_元素_类名
	web_element_type_class = 0, 
	//@别名 网页填表_元素_文本
	web_element_type_inner_text = 1, 
	//@别名 网页填表_元素_名称
	web_element_type_name = 2,
	//@别名 网页填表_元素_ID
	web_element_type_id = 3,
	//@别名 网页填表_元素_标题
	web_element_type_title = 4
};

//@别名 网页填表类
class CXFillForm
{
public:
	//@隐藏{
	CXFillForm();
	~CXFillForm();
	
	#define XCL_wnd_class_name L"Internet Explorer_Server"
	//@隐藏}

	//@备注 初始化表单帮助类
	//@参数 handle 浏览器窗口句柄
	//@返回 初始化是否成功
	//@别名 初始化()
	//@doc "doc\init.txt"
	BOOL Init(const HWND handle);

	//@备注 跳转到指定URL
	//@参数 url 目标URL
	//@别名 跳转URL()
	//@doc "doc\jmp_url.txt"
	void JmpUrl(const wchar_t *url);

	//@备注 浏览器网页回退
	//@别名 后退()
	void GoBack();

	//@备注 刷新当前页面
	//@别名 刷新()
	void Refresh();

	//@备注 获取页面标题
	//@返回 页面标题
	//@别名 取标题()
	const wchar_t *GetTitle();

	//@备注 获取页面源代码
	//@返回 页面源代码
	//@别名 取源代码()
	const wchar_t *GetSrcCode();

	//@备注 获取页面文本内容
	//@返回 页面文本内容
	//@别名 取文本()
	const wchar_t *GetText();

	//@备注 获取当前页面URL
	//@返回 当前页面URL
	//@别名 取URL()
	const wchar_t *GetUrl();

	//@备注 获取当前页面域名
	//@返回 当前页面域名
	//@别名 取域名()
	const wchar_t *GetDomain();

	//@备注 执行JavaScript代码
	//@参数 js JavaScript代码
	//@返回 执行是否成功
	//@别名 执行JS()
	//@doc "doc\js.txt"
	BOOL ExecJs(const wchar_t *js);

	//@备注 点击指定链接
	//@参数 param 链接参数
	//@参数 type 元素类型
	//@别名 点击链接()
	//@doc "doc\click_link.txt"
	void ClickLink(const wchar_t *param, web_element_type_ type);

	//@备注 获取链接文本
	//@参数 param 链接参数
	//@参数 type 元素类型
	//@返回 链接文本
	//@别名 取链接文本()
	//@doc "doc\link_text.txt"
	const wchar_t *GetLinkText(const wchar_t *param, web_element_type_ type);

	//@备注 获取链接源代码
	//@参数 param 链接参数
	//@参数 type 元素类型
	//@返回 链接源代码
	//@别名 取链接源代码()
	const wchar_t *GetLinkSrcCode(const wchar_t *param, web_element_type_ type);

	//@备注 设置链接焦点
	//@参数 param 链接参数
	//@参数 type 元素类型
	//@返回 设置是否成功
	//@别名 置链接焦点()
	BOOL SetLinkFocus(const wchar_t *param, web_element_type_ type);

	//@备注 设置链接可见性
	//@参数 param 链接参数
	//@参数 type 元素类型
	//@参数 hide 是否隐藏
	//@返回 设置是否成功
	//@别名 置链接可见性()
	//@doc "doc\link_visiable.txt"
	BOOL SetLinkVisiable(const wchar_t *param, web_element_type_ type, BOOL hide);

	//@备注 点击指定DIV元素
	//@参数 param DIV参数
	//@参数 type 元素类型
	//@别名 点击DIV()
	void ClickDiv(const wchar_t *param, web_element_type_ type);

	//@备注 获取DIV文本
	//@参数 param DIV参数
	//@参数 type 元素类型
	//@返回 DIV文本
	//@别名 取DIV文本()
	const wchar_t *GetDivText(const wchar_t *param, web_element_type_ type);

	//@备注 获取DIV源代码
	//@参数 param DIV参数
	//@参数 type 元素类型
	//@返回 DIV源代码
	//@别名 取DIV源代码()
	const wchar_t *GetDivSrcCode(const wchar_t *param, web_element_type_ type);

	//@备注 设置DIV内部HTML
	//@参数 param DIV参数
	//@参数 type 元素类型
	//@参数 html HTML内容
	//@返回 设置是否成功
	//@别名 置DIV内部HTML()
	BOOL SetDivInnerHTML(const wchar_t *param, web_element_type_ type, const wchar_t *html);

	//@备注 设置DIV可见性
	//@参数 param DIV参数
	//@参数 type 元素类型
	//@参数 hide 是否隐藏
	//@返回 设置是否成功
	//@别名 置DIV可见性()
	BOOL SetDivVisiable(const wchar_t *param, web_element_type_ type, BOOL hide);

	//@备注 点击指定SPAN元素
	//@参数 param SPAN参数
	//@参数 type 元素类型
	//@别名 点击SPAN()
	void ClickSpan(const wchar_t *param, web_element_type_ type);

	//@备注 获取SPAN文本
	//@参数 param SPAN参数
	//@参数 type 元素类型
	//@返回 SPAN文本
	//@别名 取SPAN文本()
	const wchar_t *GetSpanText(const wchar_t *param, web_element_type_ type);

	//@备注 获取SPAN源代码
	//@参数 param SPAN参数
	//@参数 type 元素类型
	//@返回 SPAN源代码
	//@别名 取SPAN源代码()
	const wchar_t *GetSpanSrcCode(const wchar_t *param, web_element_type_ type);

	//@备注 设置SPAN内部HTML
	//@参数 param SPAN参数
	//@参数 type 元素类型
	//@参数 html HTML内容
	//@返回 设置是否成功
	//@别名 置SPAN内部HTML()
	BOOL SetSpanInnerHTML(const wchar_t *param, web_element_type_ type, const wchar_t *html);

	//@备注 设置SPAN可见性
	//@参数 param SPAN参数
	//@参数 type 元素类型
	//@参数 hide 是否隐藏
	//@返回 设置是否成功
	//@别名 置SPAN可见性()
	BOOL SetSpanVisiable(const wchar_t *param, web_element_type_ type, BOOL hide);

	//@备注 点击指定LI元素
	//@参数 param LI参数
	//@参数 type 元素类型
	//@别名 点击LI()
	void ClickLi(const wchar_t *param, web_element_type_ type);

	//@备注 点击指定BUTTON元素
	//@参数 param BUTTON参数
	//@参数 type 元素类型
	//@别名 点击BUTTON()
	void ClickButton(const wchar_t *param, web_element_type_ type);

	//@备注 设置BUTTON可见性
	//@参数 param BUTTON参数
	//@参数 type 元素类型
	//@参数 hide 是否隐藏
	//@返回 设置是否成功
	//@别名 置BUTTON可见性()
	BOOL SetButtonVisiable(const wchar_t *param, web_element_type_ type, BOOL hide);

	//@备注 设置BUTTON焦点
	//@参数 param BUTTON参数
	//@参数 type 元素类型
	//@返回 设置是否成功
	//@别名 置BUTTON焦点()
	BOOL SetButtonFocus(const wchar_t *param, web_element_type_ type);

	//@备注 获取表单源代码
	//@参数 param 表单参数
	//@参数 type 元素类型
	//@返回 表单源代码
	//@别名 取表单源代码()
	const wchar_t *GetFormSrcCode(const wchar_t *param, web_element_type_ type);

	//@备注 提交表单
	//@参数 param 表单参数
	//@参数 type 元素类型
	//@返回 提交是否成功
	//@别名 提交表单()
	BOOL SubmitForm(const wchar_t *param, web_element_type_ type);

	//@备注 获取表单提交方法
	//@参数 param 表单参数
	//@参数 type 元素类型
	//@返回 表单提交方法
	//@别名 取表单提交方法()
	const wchar_t *GetFormMethod(const wchar_t *param, web_element_type_ type);

	//@备注 获取表单提交地址
	//@参数 param 表单参数
	//@参数 type 元素类型
	//@返回 表单提交地址
	//@别名 取表单提交地址()
	const wchar_t *GetFormAction(const wchar_t *param, web_element_type_ type);

	//@备注 获取单选按钮状态
	//@参数 param 单选按钮参数
	//@参数 type 元素类型
	//@返回 单选按钮状态
	//@别名 取单选按钮状态()
	BOOL GetRadioState(const wchar_t *param, web_element_type_ type);

	//@备注 设置单选按钮焦点
	//@参数 param 单选按钮参数
	//@参数 type 元素类型
	//@返回 设置是否成功
	//@别名 置单选按钮焦点()
	BOOL SetRadioFocus(const wchar_t *param, web_element_type_ type);

	//@备注 设置单选按钮可见性
	//@参数 param 单选按钮参数
	//@参数 type 元素类型
	//@参数 hide 是否隐藏
	//@返回 设置是否成功
	//@别名 置单选按钮可见性()
	BOOL SetRadioVisiable(const wchar_t *param, web_element_type_ type, BOOL hide);

	//@备注 设置单选按钮选中状态
	//@参数 param 单选按钮参数
	//@参数 type 元素类型
	//@返回 设置是否成功
	//@别名 置单选按钮选中()
	BOOL SetRadioChecked(const wchar_t *param, web_element_type_ type);

	//@备注 取消单选按钮选中状态
	//@参数 param 单选按钮参数
	//@参数 type 元素类型
	//@返回 取消是否成功
	//@别名 取消单选按钮选中()
	BOOL SetRadioUnChecked(const wchar_t *param, web_element_type_ type);

	//@备注 获取复选框状态
	//@参数 param 复选框参数
	//@参数 type 元素类型
	//@返回 复选框状态
	//@别名 取复选框状态()
	BOOL GetCheckBoxState(const wchar_t *param, web_element_type_ type);

	//@备注 设置复选框焦点
	//@参数 param 复选框参数
	//@参数 type 元素类型
	//@返回 设置是否成功
	//@别名 置复选框焦点()
	BOOL SetCheckBoxFocus(const wchar_t *param, web_element_type_ type);

	//@备注 设置复选框可见性
	//@参数 param 复选框参数
	//@参数 type 元素类型
	//@参数 hide 是否隐藏
	//@返回 设置是否成功
	//@别名 置复选框可见性()
	BOOL SetCheckBoxVisiable(const wchar_t *param, web_element_type_ type, BOOL hide);

	//@备注 设置复选框选中状态
	//@参数 param 复选框参数
	//@参数 type 元素类型
	//@返回 设置是否成功
	//@别名 置复选框选中()
	BOOL SetCheckBoxChecked(const wchar_t *param, web_element_type_ type);

	//@备注 取消复选框选中状态
	//@参数 param 复选框参数
	//@参数 type 元素类型
	//@返回 取消是否成功
	//@别名 取消复选框选中()
	BOOL SetCheckBoxUnChecked(const wchar_t *param, web_element_type_ type);

	//@备注 点击指定图片元素
	//@参数 param 图片参数
	//@参数 type 元素类型
	//@别名 点击图片()
	void ClickImg(const wchar_t *param, web_element_type_ type);

	//@备注 设置图片可见性
	//@参数 param 图片参数
	//@参数 type 元素类型
	//@参数 hide 是否隐藏
	//@返回 设置是否成功
	//@别名 置图片可见性()
	BOOL SetImgVisiable(const wchar_t *param, web_element_type_ type, BOOL hide);

	//@备注 获取输入框的值
	//@参数 param 输入框参数
	//@参数 type 元素类型
	//@返回 输入框的值
	//@别名 取输入框值()
	const wchar_t *GetInputValue(const wchar_t *param, web_element_type_ type);

	//@备注 设置输入框的值
	//@参数 param 输入框参数
	//@参数 type 元素类型
	//@参数 value 输入框的值
	//@返回 设置是否成功
	//@别名 置输入框值()
	BOOL SetInputValue(const wchar_t *param, web_element_type_ type, const wchar_t *value);

	//@备注 设置输入框焦点
	//@参数 param 输入框参数
	//@参数 type 元素类型
	//@返回 设置是否成功
	//@别名 置输入框焦点()
	BOOL SetInputFocus(const wchar_t *param, web_element_type_ type);

private:
	//点击元素
	void ClickElement(const wchar_t *element, const wchar_t *param, web_element_type_ type);
	//获取元素文本
	const wchar_t *GetElementText(const wchar_t *element, const wchar_t *param, web_element_type_ type);
	//获取元素代码
	const wchar_t *GetElementSrcCode(const wchar_t *element, const wchar_t *param, web_element_type_ type);
	//获取元素外部代码
	const wchar_t *GetElementOutSrcCode(const wchar_t *element, const wchar_t *param, web_element_type_ type);
	//获取元素内部代码
	BOOL SetElementInnerHTML(const wchar_t *element, const wchar_t *param, web_element_type_ type, const wchar_t *html);
	//设置元素可见性
	BOOL SetElementVisiable(const wchar_t *element, const wchar_t *param, web_element_type_ type, BOOL hide);
	//设置元素焦点
	BOOL SetElementFocus(const wchar_t *element, const wchar_t *param, web_element_type_ type);
	//获取输入文本
	const wchar_t *GetInputText(const wchar_t *element, const wchar_t *param, web_element_type_ type);
	//设置输入文本
	BOOL SetInputText(const wchar_t *element, const wchar_t *param, web_element_type_ type, const wchar_t *content);
	//提交
	BOOL Submit(const wchar_t *element, const wchar_t *param, web_element_type_ type);
	//获取表单方法
	const wchar_t *GetFormMethod(const wchar_t *element, const wchar_t *param, web_element_type_ type);
	//获取表单地址
	const wchar_t *GetFormAction(const wchar_t *element, const wchar_t *param, web_element_type_ type);
	//获取元素状态
	BOOL GetState(const wchar_t *element, const wchar_t *param, web_element_type_ type);
	//设置元素选中
	BOOL SetElementChecked(const wchar_t *element, const wchar_t *param, web_element_type_ type);
	//设置元素未选中
	BOOL SetElementUnChecked(const wchar_t *element, const wchar_t *param, web_element_type_ type);
	//获取元素对象
	CComPtr<IHTMLElement> GetElementObject(const wchar_t *element, const wchar_t *param, web_element_type_ type, int skip_num = 0);
	//获取浏览器对象
	BOOL GetBrowserObject();
	//获取IE窗口句柄
	HWND GetIEWndHandle(HWND hd);
	void DoEvents();

	HWND m_browser_hd;
	CComPtr<IHTMLDocument2> pHtmlDoc;
	//std::vector<std::wstring> m_link_vec;
};



//@src "FormHelp.cpp"

#endif