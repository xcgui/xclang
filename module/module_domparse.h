//@模块名称 DOM解析
//@版本 1.0
//@日期 2024-10-25
//@作者	hxznhf
//@QQ 568415950
//@模块备注  DOM解析基于DispHTMLDocument,原作者未知，代为维护

//@依赖 module_com.h
//@src "module_domparse.cpp"

namespace DOM
{

	//@分组{ 常量定义

	//@备注 代表元素
	//@别名 节点类型_元素
	const int nodeType_Element = 1;
	//@备注 代表属性
	//@别名 节点类型_属性
	const int nodeType_Attr = 2;

	//@备注 代表元素或属性中的文本内容。
	//@别名 节点类型_文本
	const int nodeType_Text = 3;
	//@备注 代表文档中的 CDATA 部分（不会由解析器解析的文本）。
	//@别名 节点类型_CDATA
	const int nodeType_CDATASection = 4;
	//@备注 代表实体引用。
	//@别名 节点类型_实体引用
	const int nodeType_EntityReference = 5;
	//@备注 代表实体。
	//@别名 节点类型_实体
	const int nodeType_Entity = 6;
	//@备注 代表处理指令。
	//@别名 节点类型_处理指令
	const int nodeType_ProcessingInstruction = 7;
	//@备注 代表注释。
	//@别名 节点类型_注释
	const int nodeType_Comment = 8;
	//@备注 代表整个文档（DOM 树的根节点）。
	//@别名 节点类型_文档
	const int nodeType_Document = 9;
	//@备注 向为文档定义的实体提供接口 。
	//@别名 节点类型_文档类型
	const int nodeType_DocumentType = 10;
	//@备注 代表轻量级的 Document 对象，能够容纳文档的某个部分
	//@别名 节点类型_文档片段
	const int nodeType_DocumentFragment = 11;

	//@备注 代表 DTD 中声明的符号。
	//@别名 节点类型_符号
	const int nodeType_Notation = 12;
	//@分组}


} // namespace name



#include "module_base.h"
#include "module_com.h"

class DOM解析;
class DOM对象数组;
class DOM解析
{
public:
	CXComObject m_object;
	DOM解析();
	~DOM解析();

	//@备注 清除对象
	//@别名 清空()
	void clear();

	//@备注 解析HTML文档，建议使用UTF16编码文档传参，避免后续编码转换麻烦
	//@返回 成功返回TRUE，失败返回FALSE
	//@别名 解析(HTML文档)
	BOOL CreateObject(CXText p_HTML);

	//@备注 设置对象，用于继承
	//@别名 置对象(CXComObject)
	void SetObject(CXComObject p_Object);

	//@备注 getElementsById() 方法可返回返回指定 ID 的第一个元素。
	//@别名 取元素从ID(元素ID)
	DOM解析 getElementById(CXText p_id);

	//@备注 getElementsByName() 方法可返回带有指定名称的对象的集合。
	//@别名 取元素从名称(元素名称)
	DOM对象数组 getElementsByName(CXText p_Name);

	//@备注 getElementsByTagName() 方法可返回带有指定标签名的对象的集合。
	//@别名 取元素从标签名(元素标签名)
	DOM对象数组 getElementsByTagName(CXText p_TagName);

	//@备注 getElementsByClassName() 方法返回文档中所有指定类名的元素集合，作为 NodeList 对象
	//@别名 取元素从类名(元素类名)
	DOM对象数组 getElementsByClassName(CXText p_ClassName);

	//@备注 getElementsByTagNameNS() 方法返回带有指定名称和命名空间的所有元素的 NodeList。
	//@别名 取元素从标签名NS(命名空间,元素名称)
	DOM对象数组 getElementsByTagNameNS(CXText p_ns, CXText p_TagName);

	//@备注 返回文档中匹配指定 CSS 选择器的全部元素。
	//@别名 取全部元素从选择器(CSS选择器)
	DOM对象数组 querySelectorAll(CXText p_Selector);

	//@备注 返回文档中匹配指定 CSS 选择器的一个元素。
	//@别名 取元素从选择器(CSS选择器)
	DOM解析 querySelector(CXText p_Selector);

	//@备注 返回当前文档上处于指定坐标位置最顶层的元素
	//@别名 取元素从坐标(坐标X,坐标Y)
	DOM解析 elementFromPoint(int p_x, int p_y);

	//@备注 返回当前文档上处于指定坐标位置最顶层的元素组
	//@别名 取全部元素从坐标(坐标X,坐标Y)
	DOM对象数组 elementsFromPoint(int p_x, int p_y);

	//@备注 firstChild 属性返回被选节点的第一个子节点。
	//@别名 首子节点()
	DOM解析 firstChild();

	//@备注 返回被选节点的最后一个子节点
	//@别名 尾子节点()
	DOM解析 lastChild();

	//@备注 previousSibling 属性返回同一树层级中指定节点的前一个节点。如果没有 previousSibling 节点，则返回值是 null。
	//@别名 前一个兄弟节点()
	DOM解析 previousSibling();

	//@备注 nextSibling 属性可返回某个元素之后紧跟的节点（处于同一树层级中）。如果没有 nextSibling 节点，则返回值是 null。
	//@别名 后一个兄弟节点()
	DOM解析 nextSibling();

	//@备注 返回元素父节点
	//@别名 父节点()
	DOM解析 parentNode();

	//@备注 childNodes 属性返回包含被选节点的子节点的 NodeList。
	//@别名 子节点()
	DOM对象数组 childNodes();

	//@备注 images 集合返回当前文档中所有图片的数组。
	//@别名 图片()
	DOM对象数组 images();

	//@备注 applets 按顺序返回当前文档中所有的applet对象。
	DOM对象数组 applets();

	//@备注 links 集合返回当前文档所有链接的数组。
	//@别名 链接()
	DOM对象数组 links();

	//@备注 forms 集合返回当前页面所有表单的数组集合。
	//@别名 表单元素()
	DOM对象数组 forms();

	//@备注 scripts 集合返回文档中所有 <script> 元素的集合。
	//@别名 脚本元素()
	DOM对象数组 scripts();

	//@备注 frames 属性返回窗口中所有命名的框架。
	//@别名 框架()
	DOM对象数组 frames();

	//@备注 embeds 返回文档中所有 <embeds> 元素的集合。
	//@别名 嵌入元素()
	DOM对象数组 embeds();

	//@备注 all 集合返回对文档中所有 HTML 元素的引用。
	//@别名 全部元素()
	DOM对象数组 all();

	//@备注 Body 对象代表了 HTML body 元素。
	//@别名 主体()
	DOM解析 body();

	//@备注 head 对象代表了 HTML head 元素。
	//@别名 头部()
	DOM解析 head();

	//@备注 hasAttribute() 方法用于判断是否有指定的属性存在，如果存在返回 true，否则返回 false。
	//@别名 是否有属性(属性名)
	BOOL hasAttribute(CXText p_attributename);

	//@备注 hasAttributes() 方法如果某节点有任何属性时返回 true，否则返回 false。
	//@别名 是否有属性()
	BOOL hasAttributes();

	//@备注 nodeType 属性返回节点的节点类型。请使用"nodeType_ 或 节点类型_ "开头的常量查询类型
	//@别名 节点类型()
	int nodeType();
	//@备注 hasChildNodes() 方法可在某节点用于任何子节点时返回 true，否则返回 false。
	//@别名 是否有子节点()
	BOOL hasChildNodes();

	//@备注 getAttribute() 方法通过名称获取属性的值。
	//@别名 取属性(属性名)
	CXText getAttribute(CXText p_attributename);

	//@备注 tagName 属性返回元素的标签名。
	//@别名 标签名()
	CXText tagName();

	//@备注 title 属性可返回当前文档的标题（ HTML title 元素中的文本）。
	//@别名 标题()
	CXText title();

	//@备注 id 属性设置或者返回元素的 id。
	//@别名 ID()
	CXText ID();

	//@备注 className 属性设置或返回元素的 class 属性。
	//@别名 类名()
	CXText className();

	//@备注 href 属性规定外部资源（通常是样式表文件）的位置（URL）。
	//@别名 href()
	CXText href();

	//@备注 在读取文本值时，outerText 与 innerText 的结果完全一样。但在写模式下，outerText 就完全不同了：outerText 不只是替换调用它的元素的子节点，而是会替换整个元素（包括子节点）。
	//@别名 outerText()
	CXText outerText();

	//@备注 innerHTML可获取或设置指定元素标签内的 html内容，从该元素标签的起始位置到终止位置的全部内容(包含html标签)。
	//@别名 innerText()
	CXText innerText();

	//@备注 textContent 属性设置或者返回指定节点的文本内容。
	//@别名 取节点文本()
	CXText textContent();

	//@备注 innerHTML 属性设置或返回表格行的开始和结束标签之间的 HTML。
	//@别名 innerHTML()
	CXText innerHTML();



	//@备注 outerHTML属性获取描述元素（包括其后代）的序列化HTML片段。
	//@别名 outerHTML()
	CXText outerHTML();

	//@备注 characterSet 只读属性返回当前文档的字符编码。该字符编码是用于渲染此文档的字符集，可能与该页面指定的编码不同。（用户可以重写编码方式。）
	//@别名 字符编码()
	CXText characterSet();
	//@备注 nodeName 属性指定节点的节点名称。 对于其他节点类型，nodeName 属性返回不同节点类型的不同名称。
	//@别名 节点名称()
	CXText nodeName();
	//@备注 localName 属性返回节点名称的本地部分。
	//@别名 本地名称()
	CXText localName();

	//@别名 到文本()
	CXText toString();

	//@备注 type 属性规定菜单的类型。
	//@别名 类型()
	CXText type();
};
class DOM对象数组
{
private:
public:
	//@隐藏{
	CXComObject m_object;
	DOM对象数组();
	~DOM对象数组();
	void SetObject(CXComObject p_Object);
	//@隐藏}

	//@备注 成员数量
	//@别名 成员数()
	int Length();
	//@备注 取成员 0开始
	//@别名 取成员(序号)
	DOM解析 Item(int p_item);
};
