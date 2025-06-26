//@模块名称 大整数
//@版本  0.1.2
//@日期  2022-10-31
//@作者  欧阳逸洛
//@模块备注 大整数计算
//仓库地址：
//问题反馈：
//包装源：https://github.com/faheel/BigInt
//包装源许可证： MIT

//@依赖 module_base.h
//@src "BigInt.cpp"
//@隐藏{
#pragma once

#include "BigInt.hpp"

BigInt abs(const BigInt& num);
BigInt pow(const BigInt& base, int exp);
BigInt pow(const long long& base, int exp);
BigInt pow(const std::string& base, int exp);
BigInt pow(const std::wstring& base, int exp);
BigInt sqrt(const BigInt& num);
BigInt gcd(const BigInt& num1, const BigInt& num2);
BigInt gcd(const BigInt& num1, const long long& num2);
BigInt gcd(const BigInt& num1, const std::string& num2);
BigInt gcd(const BigInt& num1, const std::wstring& num2);
BigInt gcd(const long long& num1, const BigInt& num2);
BigInt gcd(const std::string& num1, const BigInt& num2);
BigInt gcd(const std::wstring& num1, const BigInt& num2);
BigInt lcm(const BigInt& num1, const BigInt& num2);
BigInt lcm(const BigInt& num1, const long long& num2);
BigInt lcm(const BigInt& num1, const std::string& num2);
BigInt lcm(const BigInt& num1, const std::wstring& num2);
BigInt lcm(const long long& num1, const BigInt& num2);
BigInt lcm(const std::string& num1, const BigInt& num2);
BigInt lcm(const std::wstring& num1, const BigInt& num2);

BigInt big_pow10(size_t exp);
BigInt big_random(size_t num_digit);
//@隐藏}


/*@声明
//@别名 大整数
class BigInt {
public:

        //@别名 到文本A();
        std::string to_string() const;
        
        //@别名 到文本();
        std::wstring to_wstring() const;

        //@别名 到整型();
        int to_int() const;

        //@别名 到长整型();
        int64_t to_long_long() const;

};
*/



