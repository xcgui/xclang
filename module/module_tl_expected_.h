//@模块名称 tl_expected
//@版本  0.1.0
//@日期  2022-11-23
//@作者  欧阳逸洛

//@隐藏{
#pragma once
//@隐藏}


//@隐藏{
using tl_unexpected_int = tl::unexpected<int>;
//@隐藏}
/*@声明
#define tl_unexpected_int tl_unexpected_int;
*/


//@隐藏{
using tl_expected_int_int = tl::expected<int, int>;
//@隐藏}
/*@声明
class tl_expected_int_int
{
public:
    bool has_value();
    int& value();
    const int& error();
};
*/

//@隐藏{
using tl_expected_CXText_int = tl::expected<CXText, int>;
//@隐藏}
/*@声明
class tl_expected_CXText_int
{
public:
    bool has_value();
    CXText& value();
    const int& error();
};
*/