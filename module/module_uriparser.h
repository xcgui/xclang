//@模块名称 URI解析器
//@版本 0.1.2
//@日期 2022-10-31
//@作者 欧阳逸洛
//@模块备注 示例或测试在模块目录
//仓库地址：https://gitee.com/ouyang-yiluo/xc-uriparser
//问题反馈：https://gitee.com/ouyang-yiluo/xc-uriparser/issues
//包装源：https://github.com/uriparser/uriparser
//包装源许可证：https://github.com/uriparser/uriparser/blob/master/COPYING

//@依赖 module_base.h

#ifdef _WIN64 //x64
//@lib "x64/uriparser.lib"
//@复制文件 @当前模块路径 "x64/uriparser.dll"

#else // x86 
//@lib "x86/uriparser.lib"
//@复制文件 @当前模块路径 "x86/uriparser.dll"
#endif

//@隐藏{
#pragma once

#ifdef _WIN64 //x64
#ifdef XC_MODULE_DEV
#pragma comment(lib,"x64/uriparser.lib")
#endif //XC_MODULE_DEV

#else // x86 
#ifdef XC_MODULE_DEV
#pragma comment(lib,"x86/uriparser.lib")
#endif //XC_MODULE_DEV
#endif

#include "include/uriparser/Uri.h"

//@隐藏}

//@隐藏{
template <class Result, class UriTextRange>
Result uriTextRangeToString(UriTextRange& range)
{
    if (range.first == nullptr || (range.afterLast == nullptr))
    {
        return Result();
    }
    return Result(range.first, range.afterLast);
}

static inline CXTextA uriTextRangeToStringA(UriTextRangeA range) {
    return uriTextRangeToString<std::string>(range);
}

static inline CXText uriTextRangeToStringW(UriTextRangeW range) {
    return uriTextRangeToString<std::wstring>(range);
}

//template<typename UriType, typename StringType, typename CharType>
//int UriToString(const UriType* uri, CXTextA& str
//    , void(*getLen)(const UriType* uri, int* charsRequired)
//    , void(*toString)(CharType dest, const UriType* uri, int maxChars, int* charsWritten))
//{
//    int charsRequired;
//    int rusult = getLen(uri, &charsRequired);
//    if (rusult != URI_SUCCESS) {
//        return rusult;
//    }
//    charsRequired++;
//    str.resize(charsRequired);
//    rusult = toString(&str[0], uri, charsRequired, &charsRequired);
//    if (rusult != URI_SUCCESS) {
//        return rusult;
//    }
//    charsRequired--;
//    str.resize(charsRequired);
//    return rusult;
//}

static int uriToStringA(const UriUriA* uri, CXTextA& str) {
    int charsRequired;
    int rusult = uriToStringCharsRequiredA(uri, &charsRequired);
    if (rusult != URI_SUCCESS) {
        return rusult;
    }
    charsRequired++;

    str.resize(charsRequired);
    rusult = uriToStringA(&str[0], uri, charsRequired, &charsRequired);
    if (rusult != URI_SUCCESS) {
        return rusult;
    }
    charsRequired--;
    str.resize(charsRequired);
    return rusult;
}

static int uriToStringW(const UriUriW* uri, CXText& str) {
    int charsRequired;
    int rusult = uriToStringCharsRequiredW(uri, &charsRequired);
    if (rusult != URI_SUCCESS) {
        return rusult;
    }
    charsRequired++;

    str.resize(charsRequired);
    rusult = uriToStringW(&str[0], uri, charsRequired, &charsRequired);
    if (rusult != URI_SUCCESS) {
        return rusult;
    }
    charsRequired--;
    str.resize(charsRequired);
    return rusult;
}

static int uriComposeQueryA(const UriQueryListA* queryList, CXTextA& str) {
    int charsRequired;
    int rusult = uriComposeQueryCharsRequiredA(queryList, &charsRequired);
    if (rusult != URI_SUCCESS) {
        return rusult;
    }
    charsRequired++;

    str.resize(charsRequired);
    rusult = uriComposeQueryA(&str[0], queryList, charsRequired, &charsRequired);
    if (rusult != URI_SUCCESS) {
        return rusult;
    }
    charsRequired--;
    str.resize(charsRequired);
    return rusult;
}

static int uriComposeQueryW(const UriQueryListW* queryList, CXText& str) {
    int charsRequired;
    int rusult = uriComposeQueryCharsRequiredW(queryList, &charsRequired);
    if (rusult != URI_SUCCESS) {
        return rusult;
    }
    charsRequired++;

    str.resize(charsRequired);
    rusult = uriComposeQueryW(&str[0], queryList, charsRequired, &charsRequired);
    if (rusult != URI_SUCCESS) {
        return rusult;
    }
    charsRequired--;
    str.resize(charsRequired);
    return rusult;
}
//@隐藏}

/*@声明

//Shared errors 

//@别名 URI_完成
#define URI_SUCCESS                        0

//@别名 URI_错误_语法
#define URI_ERROR_SYNTAX                   1 // Parsed text violates expected format

//@别名 URI_错误_空白
#define URI_ERROR_NULL                     2 // One of the params passed was NULL
                                              //although it mustn't be 

//@别名 URI_错误_分配
#define URI_ERROR_MALLOC                   3 // Requested memory could not be allocated

//@别名 URI_错误_输出过大
#define URI_ERROR_OUTPUT_TOO_LARGE         4 // Some output is to large for the receiving buffer 

//@别名 URI_错误_未实现
#define URI_ERROR_NOT_IMPLEMENTED          8 // The called function is not implemented yet 

//@别名 URI_错误_范围无效
#define URI_ERROR_RANGE_INVALID            9 // The parameters passed contained invalid ranges 

//@别名 URI_错误_内存管理器未完成
#define URI_ERROR_MEMORY_MANAGER_INCOMPLETE  10 // [>=0.9.0] The UriMemoryManager passed does not implement all needed functions 

//@别名 URI_错误_字符串过长
//Errors specific to ToString 
#define URI_ERROR_TOSTRING_TOO_LONG        URI_ERROR_OUTPUT_TOO_LARGE /* Deprecated, test for URI_ERROR_OUTPUT_TOO_LARGE instead 

// Errors specific to AddBaseUri
#define URI_ERROR_ADDBASE_REL_BASE         5 // Given base is not absolute 

// Errors specific to RemoveBaseUri
#define URI_ERROR_REMOVEBASE_REL_BASE      6 // Given base is not absolute 
#define URI_ERROR_REMOVEBASE_REL_SOURCE    7 // Given base is not absolute 


//@别名 URI_错误_内存管理器故障
// Error specific to uriTestMemoryManager
#define URI_ERROR_MEMORY_MANAGER_FAULTY   11 // [>=0.9.0] The UriMemoryManager given did not pass the test suite 



//@别名 UriIPv4
//Holds an IPv4 address.
struct UriIp4 {

    //@别名 数据
    unsigned char data[4]; // Each octet in one byte
};


//@别名 UriIPv6
//Holds an IPv6 address.
struct UriIp6 {

    //@别名 数据
     unsigned char data[16]; // Each quad in two bytes
 };

*/

/*@声明

//@别名 Uri统一资源标识符A
struct UriUriA {

    //@别名 方案
    UriTextRangeA scheme; // Scheme (e.g. "http")

    //@别名 用户信息
    UriTextRangeA userInfo; // User info (e.g. "user:pass")

    //@别名 主机文本
    UriTextRangeA hostText; // Host text (set for all hosts, excluding square brackets) 

    //@别名 主机数据
    UriHostDataA hostData; // Structured host type specific data 

    //@别名 端口文本
    UriTextRangeA portText; // Port (e.g. "80") 

    //@别名 路径头
    UriPathSegmentA* pathHead; // Head of a linked list of path segments

    //@别名 路径尾
    UriPathSegmentA* pathTail; // Tail of the list behind pathHead

    //@别名 查询
    UriTextRangeA query; // Query without leading "?" 

    //@别名 片段
    UriTextRangeA fragment; // Query without leading "#" 
    
    //@别名 绝对路径
    UriBool absolutePath; // Absolute path flag, distincting "a" and "/a"; always  URI_FALSE  for URIs with host

    //@别名 所有者
    UriBool owner; // Memory owner flag 

    //@别名 保留
    void* reserved; // Reserved to the parser
}; 

//@别名 Uri文本范围A
struct UriTextRangeA {

    //@别名 首
    const char* first; // Pointer to first character 

    //@别名 尾
    const char* afterLast; // Pointer to character after the last one still in 
};

//@别名 Uri主机数据A
struct UriHostDataA{
    UriIp4 * ip4; // IPv4 address
    UriIp6* ip6; // IPv6 address 
    UriTextRangeA ipFuture; // IPvFuture address
};

//@别名 Uri路径段A
struct UriPathSegmentA {

    //@别名 文本
    UriTextRangeA text; // Path segment name

    //@别名 下一个
    UriPathSegmentA* next; // Pointer to the next path segment in the list, can be NULL if last already

    //@别名 保留
    void* reserved; // Reserved to the parser
};

//@别名 Uri查询列表A
struct UriQueryListA {

    //@别名 键
    const char* key; // Key of the query element

    //@别名 值
    const char* value; // Value of the query element, can be NULL

    //@别名 下一个
    UriQueryListA* next; // Pointer to the next key/value pair in the list, can be NULL if last already
};

//@别名 uri解析单个UriA(uri,文本,错误位置)
int uriParseSingleUriA(UriUriA* uri, const char* text, const char ** errorPos);

//@别名 uri释放Uri成员A()
void uriFreeUriMembersA(UriUriA* uri);

//@别名 uri文本范围到文本A(uri文本范围)
CXTextA uriTextRangeToStringA(UriTextRangeA range);

//@别名 uri分配查询列表A(目标,项目数,范围首,范围尾)
int uriDissectQueryMallocA(UriQueryListA** dest, int* itemCount, const char* first, const char * afterLast);

//@别名 uri释放查询列表A(查询列表)
void uriFreeQueryListA(UriQueryListA* queryList);

//@别名 uri统一资源标识符到文本A()
int uriToStringA(const UriUriA* uri, CXTextA& str);

//@别名 uri查询列表到文本A()
int uriComposeQueryA(const UriQueryListA* queryList, CXTextA& str);
*/


/*@声明

//@别名 Uri统一资源标识符
struct UriUriW {

    //@别名 方案
    UriTextRangeW scheme; // Scheme (e.g. "http")

    //@别名 用户信息
    UriTextRangeW userInfo; // User info (e.g. "user:pass")

    //@别名 主机文本
    UriTextRangeW hostText; // Host text (set for all hosts, excluding square brackets)

    //@别名 主机数据
    UriHostDataW hostData; // Structured host type specific data

    //@别名 端口文本
    UriTextRangeW portText; // Port (e.g. "80")

    //@别名 路径头
    UriPathSegmentW* pathHead; // Head of a linked list of path segments

    //@别名 路径尾
    UriPathSegmentW* pathTail; // Tail of the list behind pathHead

    //@别名 查询
    UriTextRangeW query; // Query without leading "?"

    //@别名 片段
    UriTextRangeW fragment; // Query without leading "#"

    //@别名 绝对路径
    UriBool absolutePath; // Wbsolute path flag, distincting "a" and "/a"; always  URI_FWLSE  for URIs with host

    //@别名 所有者
    UriBool owner; // Memory owner flag

    //@别名 保留
    void* reserved; // Reserved to the parser
};

//@别名 Uri文本范围
struct UriTextRangeW {

    //@别名 首
    const wchar_t* first; // Pointer to first wchar_tacter

    //@别名 尾
    const wchar_t* afterLast; // Pointer to wchar_tacter after the last one still in
};

//@别名 Uri主机数据
struct UriHostDataW{
    UriIp4 * ip4; // IPv4 address
    UriIp6* ip6; // IPv6 address
    UriTextRangeW ipFuture; // IPvFuture address
};

//@别名 Uri路径段
struct UriPathSegmentW {

    //@别名 文本
    UriTextRangeW text; // Path segment name 

    //@别名 下一个
    UriPathSegmentW* next; // Pointer to the next path segment in the list, can be NULL if last already

    //@别名 保留
    void* reserved; // Reserved to the parser 
};

//@别名 Uri查询列表
struct UriQueryListW {

    //@别名 键
    const wchar_t* key; // Key of the query element

    //@别名 值
    const wchar_t* value; // Value of the query element, can be NULL

    //@别名 下一个
    UriQueryListW* next; // Pointer to the next key/value pair in the list, can be NULL if last already
};

//@别名 uri解析单个Uri(uri,文本,错误位置)
int uriParseSingleUriW(UriUriW* uri, const wchar_t* text, const wchar_t ** errorPos);

//@别名 uri释放Uri成员()
void uriFreeUriMembersW(UriUriW* uri);

//@别名 uri文本范围到文本(uri文本范围)
CXText uriTextRangeToStringW(UriTextRangeW range);

//@别名 uri分配查询列表(目标,项目数,范围首,范围尾)
int uriDissectQueryMallocW(UriQueryListW** dest, int* itemCount, const wchar_t* first, const wchar_t * afterLast);

//@别名 uri释放查询列表(查询列表)
void uriFreeQueryListW(UriQueryListW* queryList);

//@别名 uri统一资源标识符到文本()
int uriToStringW(const UriUriW* uri, CXText& str);

//@别名 uri查询列表到文本()
int uriComposeQueryW(const UriQueryListW* queryList, CXText& str);
*/