#ifndef XC_WORDHELP_H

//@隐藏{
#define XC_WORDHELP_H

//@依赖   module_base.h

#include <iostream>
#include <vector>

#if XC_MOUDLE
#include "module_base.h"
#endif

//@隐藏}

//@src   "pugixml.cpp"
//@src   "zip.c"


//@模块名称  word操作
//@版本  1.1
//@日期  2025-1-10
//@作者  peerless
//@QQ    598762663
//@模块备注 word文档操作
// 目前只支持docx格式
// 文档标题、内容和图片提取


//@别名 word操作类
//@备注 对象初始化传入docx文档全路径 文本型A
class WordHelp
{
public:
//@隐藏{
	explicit WordHelp(const char* file_path);
	~WordHelp();
//@隐藏}

	//@备注 读取word文档内容
	//@别名 载入文档()
	bool LoadWord();
	//@备注 导出图片到指定目录文本型A，目录结尾不带斜杠
	//@别名 导出图片(导出目录)
	bool ExportPic(const char* out_dir);
	//@备注 获取word正文内容，文本型vector
	//@别名 取内容()
	CXVector<CXText> GetContent();
	//@备注 获取word一级标题，文本型vector
	//@别名 取标题1()
	CXVector<CXText> GetHead1();
	//@备注 获取word二级标题，文本型vector
	//@别名 取标题2()
	CXVector<CXText> GetHead2();
	//@备注 获取word三级标题，文本型vector
	//@别名 取标题3()
	CXVector<CXText> GetHead3();

private:
	bool createDirRecursive(const std::string dir);
	std::string m_path;
	std::string documentXML;
	CXVector<CXText> m_content;
	CXVector<CXText> m_head1;
	CXVector<CXText> m_head2;
	CXVector<CXText> m_head3;

};


//@src "WordHelp.cpp"

#endif