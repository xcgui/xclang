//@模块名称 cpp_std
//@版本  0.1.0
//@日期  2022-11-28
//@作者  欧阳逸洛

//@依赖 module_base.h
//@隐藏{
#pragma once
#include <string>
//@隐藏}



//@隐藏{
#if _HAS_CXX17
//@隐藏}

//@解析头文件
#include "cpp_std\xc_cpp_17.h"

//@隐藏{
#endif
//@隐藏}

//@隐藏{
#define std_move(v) std::move(v)
//@隐藏}
/*@声明
//@别名 std_移动()
T&& std_move(T&);
*/

/*@声明
//@别名 空指针
#define nullptr nullptr;
typedef int8_t int8_t;
typedef int16_t int16_t;
typedef int32_t int32_t;
typedef int64_t int64_t;
typedef uint8_t uint8_t;
typedef uint16_t uint16_t;
typedef uint32_t uint32_t;
typedef uint64_t uint64_t;
typedef size_t size_t;
*/


#define STD_MAKE_PAIR(Type,V1,V2) make_pair<Type>(V1,V2);

//@隐藏{
using std_pair_CXTextA_CXTextA = std::pair<CXTextA, CXTextA>;
//@隐藏}
/*@声明
typedef std_pair_CXTextA_CXTextA std_pair_CXTextA_CXTextA;
*/