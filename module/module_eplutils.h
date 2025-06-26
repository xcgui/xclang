///  写在前面的话,为什么没有使用headonly 首先是代码复杂度，其次是编译时长,为什么使用C++20,优秀的标准库以及三大编译器的基本适配


#ifndef  XC_EPL_H
//@隐藏{


//stl的引用
#pragma region import_stl
#include <optional>
#include <string_view>
#include <array>
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <bitset>
#include <vector>
#include <numeric>
#include <filesystem>

#include <ShlObj.h>
#include <VersionHelpers.h>
#pragma endregion


#define  XC_EPL_H
//@隐藏}


//@模块名称  易语言核心支持库
//@版本  1.0
//@QQ  80805777
//@日期  2024-6-27
//@作者  AlongsCode
//@模块备注  易语言系统核心支持库
//仅支持c++20标准及以上

//@依赖  eplpinyin.hpp
//@依赖  module_base.h
//-----------------//@src "XCDatabase.cpp"



//@模块信息结束

/*********************************************基本定义类型******************************************/

#define 空参数  std::nullopt
#define 空字节集  {}


//@隐藏{
#ifdef CPP20
#define fn constexpr auto
#else
#define fn inline auto
#endif
namespace _imp_proname_help {
    fn u82u16(const char* u8str) {
        if (u8str == nullptr) 
            return std::wstring{};
        int len = MultiByteToWideChar(CP_UTF8, 0, u8str, -1, nullptr, 0);
        if (len == 0) 
            return std::wstring{};
        std::wstring wstr(len, L'\0');
        MultiByteToWideChar(CP_UTF8, 0, u8str, -1, &wstr[0], len);
        wstr.resize(len - 1);
        return wstr;
    }
}
#define __passnop 
#define __impeplthiself() this
#define EPL_GET_FUNCTION_NAME() \
    CXText(_imp_proname_help::u82u16(__FUNCTION__))

#define EPL_GET_FILENAME_XC() \
    CXText(std::filesystem::path(__FILEW__).filename().replace_extension(L"").wstring())

#define EPL_GET_PARENT_DIR_AND_PROJ() \
    CXText(std::filesystem::path(__FILEW__).parent_path().parent_path().parent_path().parent_path().wstring() + L"\\" + \
           std::filesystem::path(__FILEW__).parent_path().parent_path().parent_path().parent_path().filename().wstring() + \
           L".xcproj")

#define EPL_GET_GRANDPARENT_DIR_PROJ() \
    CXText(std::filesystem::path(__FILEW__).parent_path().parent_path().parent_path().parent_path().filename().wstring() + \
           L".xcproj")

#define EPL_GET_EMPTY() \
    CXText(L"")

#define EPL_GET_GRANDPARENT_DIR_NAME() \
    CXText(std::filesystem::path(__FILEW__).parent_path().parent_path().parent_path().parent_path().filename().wstring())

#define EPL_GET_UNKNOWN_TYPE() \
    CXText(L"未知类型")

#define EPL_GET_PROGRAM_NAME(type) \
    (type == 1 ? EPL_GET_FUNCTION_NAME() : \
     type == 2 ? EPL_GET_FILENAME_XC() : \
     type == 3 ? EPL_GET_PARENT_DIR_AND_PROJ() : \
     type == 4 ? EPL_GET_GRANDPARENT_DIR_PROJ() : \
     type == 5 ? EPL_GET_EMPTY() : \
     type == 6 ? EPL_GET_GRANDPARENT_DIR_NAME() : EPL_GET_UNKNOWN_TYPE())

// 
//@隐藏}

#if XC_MOUDLE
#include "module_base.h"
#else
#include "D:\ide\炫彩IDE-3.3.9-(2024-06-24)\data\XC-Module\核心\基础模块\module_base.h"
#endif
//@隐藏{

namespace krnln {
    namespace datetime {
        struct EPLDATATIME : public std::tm {};
    }
}
using EPLKRNLNDATATIME_T = krnln::datetime::EPLDATATIME;

namespace epl_runtime_systype {
    /*对于C风格字符串的包装,而非C++字符串*/
    /*易语言字符串*/
    class eplstring {
        using CharType = char;
        using SizeType = std::size_t;

        //定义迭代器
        class eplstring_iterator
        {
            using value_type = CharType;
            using difference_type = ptrdiff_t;
            using pointer = value_type*;
            using reference = value_type&;
        private:
            pointer m_p{ nullptr };
        public:
            eplstring_iterator(CharType* p) : m_p(p) {}
            eplstring_iterator(const eplstring_iterator& other) : m_p(other.m_p) {}
            [[nodiscard]] constexpr reference operator*() const noexcept {
                return *m_p;
            }

            [[nodiscard]] pointer operator->() const noexcept {
                auto c = **this;
                return std::pointer_traits<pointer>::pointer_to(**this);
            }
            eplstring_iterator& operator=(const eplstring_iterator& other) {
                m_p = other.m_p;
                return *this;
            }
            [[nodiscard]] constexpr operator pointer() const
            {
                return m_p;
            }
            constexpr eplstring_iterator& operator++() noexcept {
                ++m_p;
                return *this;
            }

            eplstring_iterator operator++(int) noexcept {
                eplstring_iterator _Tmp{ *this };
                ++*this;
                return _Tmp;
            }

            constexpr eplstring_iterator& operator--() noexcept {
                --m_p;
                return *this;
            }

            eplstring_iterator operator--(int) noexcept {
                eplstring_iterator _Tmp{ *this };
                --*this;
                return _Tmp;
            }


            constexpr eplstring_iterator& operator+=(const difference_type _Off) noexcept {
                m_p += _Off;
                return *this;
            }

            [[nodiscard]] eplstring_iterator operator+(const difference_type _Off) const noexcept {
                eplstring_iterator _Tmp{ *this };
                _Tmp += _Off;
                return _Tmp;
            }

            [[nodiscard]] friend  eplstring_iterator operator+(
                const difference_type _Off, eplstring_iterator _Next) noexcept {
                _Next += _Off;
                return _Next;
            }

            constexpr eplstring_iterator& operator-=(const difference_type _Off) noexcept {
                return *this += -_Off;
            }

            [[nodiscard]] eplstring_iterator operator-(const difference_type _Off) const noexcept {
                eplstring_iterator _Tmp{ *this };
                _Tmp -= _Off;
                return _Tmp;
            }


            [[nodiscard]] constexpr
                const difference_type operator-
                (const eplstring_iterator& other) const
            {
                return m_p - other.m_p;
            }
            /*下标引用*/
            [[nodiscard]] constexpr
                reference operator[]
                (const difference_type _Off) const noexcept
            {
                return *(*this + _Off);
            }

            [[nodiscard]]
            constexpr std::strong_ordering operator<=>
                (const eplstring_iterator& _Right) const noexcept {
                return this->m_p <=> _Right.m_p;
            }
        };
    private:
        eplstring_iterator m_pData{ nullptr };//起始位置
        eplstring_iterator m_pDataEnd{ nullptr }; //结束位置
    public:
        /// <summary>
        /// 来自STL字符串的构造函数
        /// </summary>
        /// <param name="stlstring"></param>
        eplstring(const ::std::basic_string<CharType>& stlstring) {
            auto nSize{ stlstring.size() };
            m_pData = new CharType[nSize + 1]{ '\0' };
            m_pDataEnd = m_pData + nSize;
            ::std::copy(stlstring.begin(), stlstring.end(), m_pData);
        };
        /*构造函数*/
        eplstring(const CharType* text) {
            auto nSize{ std::strlen(text) };
            m_pData = new CharType[nSize + 1]{ '\0' };
            m_pDataEnd = m_pData + nSize;
            std::copy(text, text + nSize, m_pData);
        }
        /*构造函数*/
        eplstring(const CharType* text, const SizeType nSize) {
            m_pData = new CharType[nSize + 1]{ '\0' };
            m_pDataEnd = m_pData + nSize;
            std::copy(text, text + nSize, m_pData);
        }

        /*复制构造*/
        eplstring(const eplstring& other) {
            auto nSize{ other.size() };
            m_pData = new CharType[nSize + 1]{ '\0' };
            m_pDataEnd = m_pData + nSize;
            std::copy(other.begin(), other.end(), m_pData);
        }
        /*析构函数*/
        ~eplstring() {
            delete[] m_pData;
        }
        [[nodiscard]] fn operator=(const eplstring& other) -> eplstring& {
            auto nSize{ other.size() };
            auto pNewData = new CharType[nSize + 1]{ '\0' };
            std::copy(other.begin(), other.end(), pNewData);
            if (m_pData)
                delete[] m_pData;
            m_pData = pNewData;
            m_pDataEnd = m_pData + nSize;
            return *this;
        }
        [[nodiscard]] fn data()const -> const CharType* {
            return m_pData;
        }
        [[nodiscard]] fn empty()const -> bool {
            return !m_pData || !*m_pData;
        }
        [[nodiscard]] fn begin()const -> eplstring_iterator {
            return m_pData;
        }
        [[nodiscard]] fn end()const -> eplstring_iterator {
            return m_pDataEnd;
        }
        [[nodiscard]] fn begin() -> eplstring_iterator {
            return m_pData;
        }
        [[nodiscard]] fn end() -> eplstring_iterator {
            return m_pDataEnd;
        }
        [[nodiscard]] fn operator[](SizeType index) -> CharType& {
            return m_pData[index];
        }
        [[nodiscard]] fn operator[](SizeType index)const -> const CharType& {
            return m_pData[index];
        }
        [[nodiscard]] fn operator==(const eplstring& other)const -> bool {

        }
        [[nodiscard]] fn operator+=(const eplstring& other) -> eplstring& {
            auto nSize{ other.size() };
            auto pNewData = new CharType[size() + nSize];
            std::copy(m_pData, m_pDataEnd, pNewData);
            std::copy(other.begin(), other.end(), pNewData + size());
            delete[] m_pData;
            m_pData = pNewData;
            m_pDataEnd = m_pData + size() + nSize;
        }
        //是否相似
        bool like(const eplstring& other) {
            // 获取str2的长度
            const auto& str2Length = other.size();
            const CharType* str2 = other.m_pData;
            // 用于遍历str1的指针
            auto pStr1 = m_pData;
            // 如果str2的长度小于或等于str1的长度
            if (str2Length <= size()) {
                // 如果str2为空，则返回true
                if (str2Length == 0)
                    return true;
                // 循环比较字符，直到str2的末尾
                while (*pStr1) {
                    // 如果字符不匹配，则返回false
                    if (*pStr1++ != *str2++)
                        return false;
                }
                // 比较两个字符串的最后一个字符
                if (*(--pStr1) == *(--str2))
                    return true;
            }
            return false;
        }
        fn size()const -> SizeType {
            return m_pDataEnd - m_pData;
        }
    };
    /*易语言数组*/
    class eplarray
    {
        using T = char;
        std::vector<size_t> m_nElementCount{ 0 };//记录每一个维数的长度
        std::vector<T> m_pData;//记录每一个维数的长度
    public:
        eplarray() {
            m_nElementCount = { 0 };

        };//默认为一维数组
        eplarray(std::initializer_list<size_t> args) {
            m_nElementCount = args;
            auto size = std::accumulate(m_nElementCount.begin(), m_nElementCount.end(), 1, std::multiplies<size_t>());
            m_pData = std::vector<T>(size);
        }
        ~eplarray() = default;
        eplarray(const eplarray& other) {
            m_nElementCount = other.m_nElementCount;
            m_pData = std::vector<T>(size());
            std::copy(other.m_pData.begin(), other.m_pData.end(), m_pData.begin());
        }
        [[nodiscard]] fn operator=(const eplarray& other) -> eplarray& {
            m_nElementCount = other.m_nElementCount;
            m_pData = std::vector<T>(size());
            std::copy(other.m_pData.begin(), other.m_pData.end(), m_pData.begin());
            return *this;
        }
        [[nodiscard]] fn data()const -> const T* {}
        [[nodiscard]] fn operator[](size_t index) -> T& {
            index--;
            checkIndex(index, m_pData.size());
            return m_pData[index];
        }
        [[nodiscard]] fn operator[](size_t index)const -> const T& {
            index--;
            checkIndex(index, m_pData.size());
            return m_pData[index];
        }
        [[nodiscard]] fn size()const -> size_t {
            return m_pData.size();
        }


        /*多维情况使用*/
        template <typename... Args>
        [[nodiscard]]
        fn fnGet(Args... args) -> T& {


            if (sizeof...(args) != m_nElementCount.size() && sizeof...(args) != 1)
            {
                // eplsysapi::PutRuntimeError(L"数组维数不为1且数组维数不匹配");
                exit(-1);
            }

            //对于多维数组的索引例如 a[2][2][3]这种,当对于索引a[1][1][0]时,其实际上是第9个元素a[8]同样，即为a[1*2*3+1*3+0]
            //对于宽窄转换例如参数为 int,long long, float,double等类型时，会自动转换为size_t类型
            std::vector<size_t> off;
            push_arg(off, args...);

            if (off.size() == 1)
            {
                auto f = --off[0];
                checkIndex(f, m_pData.size());
                return m_pData[f];
            }


            //验证索引是否越界,并转换添加到off中
            for (size_t i = 0; i < off.size(); i++)
            {
                off[i]--;
                checkIndex(off[i], m_nElementCount[i]);
            }


            //开始计算偏移量
            size_t nOff = 0;
            for (size_t i = 0; i < off.size(); i++)
            {
                size_t n = 1;
                for (size_t j = i + 1; j < off.size(); j++)
                {
                    n *= m_nElementCount[j];
                }
                nOff += off[i] * n;
            }
            checkIndex(nOff, m_pData.size());
            return m_pData[nOff];

        }
        template <typename... Args>
        [[nodiscard]]
        fn fnGet(Args... args) const ->const T& {
            if (sizeof...(args) != m_nElementCount.size() && sizeof...(args) != 1)
            {
                //eplsysapi::PutRuntimeError(L"数组维数不为1且数组维数不匹配");
                exit(-1);
            }

            //对于多维数组的索引例如 a[2][2][3]这种,当对于索引a[1][1][0]时,其实际上是第9个元素a[8]同样，即为a[1*2*3+1*3+0]
            //对于宽窄转换例如参数为 int,long long, float,double等类型时，会自动转换为size_t类型
            std::vector<size_t> off;
            push_arg(off, args...);
            if (off.size() == 1)
            {
                auto f = --off[0];
                checkIndex(f, m_pData.size());
                return m_pData[f];
            }


            //验证索引是否越界,并转换添加到off中
            for (size_t i = 0; i < off.size(); i++)
            {
                off[i]--;
                checkIndex(off[i], m_nElementCount[i]);
            }


            //开始计算偏移量
            size_t nOff = 0;
            for (size_t i = 0; i < off.size(); i++)
            {
                size_t n = 1;
                for (size_t j = i + 1; j < off.size(); j++)
                {
                    n *= m_nElementCount[j];
                }
                nOff += off[i] * n;
            }
            checkIndex(nOff, m_pData.size());
            return m_pData[nOff];
        }

    private:
        void checkIndex(size_t index, size_t max) const {
            if (index >= max)
            {
                // eplsysapi::PutRuntimeError(L"数组索引越界");
                exit(-1);
            }
        }

        //出口
        void push_arg(std::vector<size_t>& v) {};

        template <typename N, typename... T>
        void push_arg(std::vector<size_t>& v, N s, T... arg) {
            //判断是否为数值类型
            static_assert (std::is_arithmetic_v<N>, R"(来自易语言标准运行时的警告:“数组索引”必须为数值类型)");
            v.push_back(static_cast<size_t>(s));
            push_arg(v, arg...);
        }
    };



}
namespace epldatatype {
    class MemBin
    {
    public:
        using byte_type = unsigned char;
        using byte_poiter = byte_type*;
        using const_byte_poiter = const byte_type*;
        using reference = byte_type&;
        using const_reference = const byte_type&;
        using size_type = size_t;

        //内部常量迭代器
        class const_iterator
        {
            using __traits_type = std::iterator_traits<const_byte_poiter>;
        public:
            typedef typename __traits_type::iterator_category iterator_category;
            typedef typename __traits_type::value_type  	value_type;
            typedef typename __traits_type::difference_type 	difference_type;
            typedef typename __traits_type::reference 	reference;
            typedef typename __traits_type::pointer   	pointer;

            constexpr const_iterator() noexcept
                : _M_current(const_byte_poiter()) { }

            constexpr
                const_iterator(const const_byte_poiter& __i) noexcept
                : _M_current(__i) { }

            /*    constexpr
                    const_iterator(const void*& __i) noexcept
                    : _M_current(static_cast<const const_byte_poiter>(__i)) { }*/
                    // 输入迭代器
            constexpr
                reference
                operator*() const noexcept
            {
                return *_M_current;
            }

            constexpr
                pointer
                operator->() const noexcept
            {
                return _M_current;
            }

            constexpr
                const_iterator&
                operator++()  noexcept
            {
                ++_M_current;
                return *this;
            }

            constexpr
                const_iterator
                operator++(int)  noexcept
            {
                return const_iterator(_M_current++);
            }

            // 双向迭代器
            constexpr
                const_iterator&
                operator--() noexcept
            {
                --_M_current;
                return *this;
            }

            constexpr
                const_iterator
                operator--(int) noexcept
            {
                return const_iterator(_M_current--);
            }

            // 随机访问迭代器
            constexpr
                reference
                operator[](difference_type __n) const noexcept
            {
                return _M_current[__n];
            }

            constexpr
                const_iterator&
                operator+=(difference_type __n) noexcept
            {
                _M_current += __n; return *this;
            }

            constexpr
                const_iterator
                operator+(difference_type __n) const noexcept
            {
                return const_iterator(_M_current + __n);
            }

            constexpr
                const_iterator&
                operator-=(difference_type __n) noexcept
            {
                _M_current -= __n; return *this;
            }

            constexpr
                const_iterator
                operator-(difference_type __n) const noexcept
            {
                return const_iterator(_M_current - __n);
            }

            constexpr
                const const_byte_poiter&
                base() const noexcept
            {
                return _M_current;
            }
            constexpr
                operator const_byte_poiter() const noexcept {
                return _M_current;
            }
            constexpr
                difference_type
                operator-(const const_iterator& _X) const noexcept
            {
                return std::distance(_X._M_current, _M_current);
            }

            constexpr
                bool
                operator==(const const_iterator& __x) const noexcept
            {
                return _M_current == __x._M_current;
            }

            constexpr
                bool
                operator!=(const const_iterator& __x) const noexcept
            {
                return _M_current != __x._M_current;
            }

            constexpr
                std::strong_ordering
                operator<=>(const const_iterator& __x) const noexcept
            {
                return _M_current <=> __x._M_current;
            }
        private:
            const_byte_poiter _M_current{ nullptr };
        };
        //内部迭代器
        class iterator
        {
            using __traits_type = std::iterator_traits<byte_poiter>;
        public:
            typedef typename __traits_type::iterator_category iterator_category;
            typedef typename __traits_type::value_type  	value_type;
            typedef typename __traits_type::difference_type 	difference_type;
            typedef typename __traits_type::reference 	reference;
            typedef typename __traits_type::pointer   	pointer;

            constexpr iterator() noexcept
                : _M_current(nullptr) { }

            constexpr
                iterator(const byte_poiter& __i) noexcept
                : _M_current(__i) { }
            /*  constexpr
                  iterator(void*& __i) noexcept
                  : _M_current(static_cast<byte_poiter>(__i)) { }*/

                  // 输入迭代器
            constexpr
                reference
                operator*() const noexcept
            {
                return *_M_current;
            }

            constexpr
                pointer
                operator->() const noexcept
            {
                return _M_current;
            }
            //指针重载
            constexpr
                operator pointer() const noexcept
            {
                return _M_current;
            }

            constexpr
                iterator&
                operator++()  noexcept
            {
                ++_M_current;
                return *this;
            }

            constexpr
                iterator
                operator++(int)  noexcept
            {
                return iterator(_M_current++);
            }

            // 双向迭代器
            constexpr
                iterator&
                operator--() noexcept
            {
                --_M_current;
                return *this;
            }

            constexpr
                iterator
                operator--(int) noexcept
            {
                return iterator(_M_current--);
            }

            // 随机访问迭代器
            constexpr
                reference
                operator[](difference_type __n) const noexcept
            {
                return _M_current[__n];
            }

            constexpr
                iterator&
                operator+=(difference_type __n) noexcept
            {
                _M_current += __n; return *this;
            }

            constexpr
                iterator
                operator+(difference_type __n) const noexcept
            {
                return iterator(_M_current + __n);
            }

            constexpr
                iterator&
                operator-=(difference_type __n) noexcept
            {
                _M_current -= __n; return *this;
            }

            constexpr
                iterator
                operator-(difference_type __n) const noexcept
            {
                return iterator(_M_current - __n);
            }

            constexpr
                const byte_poiter&
                base() const noexcept
            {
                return _M_current;
            }

            constexpr
                difference_type
                operator-(const iterator& _X) const noexcept
            {
                return std::distance(_X._M_current, _M_current);
            }

            constexpr
                bool
                operator==(const iterator& __x) const noexcept
            {
                return _M_current == __x._M_current;
            }

            constexpr
                bool
                operator!=(const iterator& __x) const noexcept
            {
                return _M_current != __x._M_current;
            }

            constexpr
                std::strong_ordering
                operator<=>(const iterator& __x) const noexcept
            {
                return _M_current <=> __x._M_current;
            }
        private:
            byte_poiter _M_current{ nullptr };
        };
        //反向迭代器类型
        using reverse_iterator = std::reverse_iterator<iterator>;
        //常量反向迭代器类型
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    public:
        MemBin() = default;
        ~MemBin();


        /*explicit
            MemBin(size_type __n)
        {
            this->m_pData = new byte_type[__n]{};
            this->m_nSize = this->m_nMaxSize = __n;
        }*/
        MemBin(std::initializer_list<byte_type> __l)
        {
            const size_type __n = __l.size();
            this->m_pData = new byte_type[__n];
            this->m_nSize = this->m_nMaxSize = __n;
            std::copy(__l.begin(), __l.end(), this->m_pData);
        }

        //template <typename T>
        //MemBin(std::initializer_list<T> __l)
        //{
        //    const size_type __n = __l.size();
        //    this->m_pData = new byte_type[__n];
        //    this->m_nSize = this->m_nMaxSize = __n;

        //    std::unique_ptr<T[]> p = std::make_unique<T[]>(__n);
        //    std::copy(__l.begin(), __l.end(), p.get());
        //    for (size_t i = 0; i < __n; i++)
        //        this->m_pData[i] = static_cast<byte_type>(p[i]);
        //}


        MemBin(const void* _p, size_type _size)
        {
            if (_p != nullptr && _size != 0)
            {
                this->m_pData = new byte_type[_size];
                this->m_nSize = this->m_nMaxSize = _size;
                memcpy(this->m_pData, _p, _size);
            }

        }

        template <typename T>
        explicit  MemBin(T&& val) :MemBin(&val, sizeof(T)) {};


        explicit MemBin(const char* val) :MemBin(val, strlen(val)) {};
        explicit MemBin(const wchar_t* val) :MemBin(val, wcslen(val) * sizeof(char)) {};
        template <typename CharType>
        explicit MemBin(std::basic_string<CharType>&& val) :MemBin(val.data(), val.size() * sizeof(CharType)) {};


        MemBin(const MemBin& __x)
        {
            const size_type __n = __x.size();
            this->m_pData = new byte_type[__n];
            this->m_nSize = this->m_nMaxSize = __n;
            std::copy(__x.begin(), __x.end(), this->m_pData);
        }
    public://迭代器部分


        //读写迭代器-返回指向第一个字节的迭代器
        iterator
            begin()  noexcept
        {
            return iterator(this->m_pData);
        }

        //只读迭代器-返回指向第一个字节的迭代器
        const_iterator
            begin() const noexcept
        {
            return const_iterator(this->m_pData);
        }
        //读写迭代器-返回指向最后一个字节的迭代器
        iterator
            end() noexcept
        {
            return iterator(this->m_pData + this->m_nSize);
        }
        //只读迭代器-返回指向最后一个字节的迭代器
        const_iterator
            end() const noexcept
        {
            return const_iterator(this->m_pData + this->m_nSize);
        }
        //读写反向迭代器-返回指向最后一个字节的迭代器
        reverse_iterator
            rbegin() noexcept
        {
            return reverse_iterator(end());
        }

        //只读反向迭代器-返回指向最后一个字节的迭代器
        const_reverse_iterator
            rbegin() const noexcept
        {
            return const_reverse_iterator(end());
        }

        //读写反向迭代器-返回指向第一个字节的迭代器
        reverse_iterator
            rend() noexcept
        {
            return reverse_iterator(begin());
        }

        //只读反向迭代器-返回指向第一个字节的迭代器
        const_reverse_iterator
            rend() const noexcept
        {
            return const_reverse_iterator(begin());
        }

        //只读迭代器-返回指向第一个字节的迭代器
        const_iterator
            cbegin() const noexcept
        {
            return const_iterator(this->m_pData);
        }

        //只读迭代器-返回指向最后一个字节的迭代器
        const_iterator
            cend() const noexcept
        {
            return const_iterator(this->m_pData + this->m_nSize);
        }

        //只读反向迭代器-返回指向最后一个字节的迭代器
        const_reverse_iterator
            crbegin() const noexcept
        {
            return const_reverse_iterator(end());
        }

        //只读反向迭代器-返回指向第一个字节的迭代器
        const_reverse_iterator
            crend() const noexcept
        {
            return const_reverse_iterator(begin());
        }
        reference front()
        {
            return *begin();
        }
        const_reference front() const
        {
            return *begin();
        }
        reference back()
        {
            return *(end() - 1);
        }
        const_reference back() const
        {
            return *(end() - 1);
        }
        void pop_back()
        {
            if (m_nSize > 0)
                m_nSize--;
        }
    public:

        void reserve(size_type _N);
        void resize(size_type nNewSize);
        byte_poiter data() {
            return m_pData;
        }
        const_byte_poiter data() const {
            return m_pData;
        }
        size_type size() const
        {
            return m_pData == nullptr ? 0 : m_nSize;
        }
        bool empty() const
        {
            return (size() == 0);
        }
        size_type capacity() const
        {
            return m_pData == nullptr ? 0 : m_nMaxSize;
        }

    private://辅助算法

        static void make_delta1(size_t* delta1, unsigned char* pat, size_t patlen) noexcept {
            for (size_t i = 0; i < 256; i++) {
                delta1[i] = patlen;
            }
            for (size_t i = 0; i < patlen - 1; i++) {
                delta1[pat[i]] = patlen - 1 - i;
            }
        }
        static bool is_prefix(unsigned char* word, size_t wordlen, size_t pos) noexcept {
            if (wordlen < pos)
                return true;
            auto suffixlen = wordlen - pos;
            for (size_t i = 0; i < suffixlen; i++) {
                if (word[i] != word[pos + i]) {
                    return false;
                }
            }
            return true;
        }
        static size_t suffix_length(unsigned char* word, size_t wordlen, size_t pos) noexcept {
            size_t length = 0;
            if (pos >= wordlen) return 0;
            for (size_t i = 0; i < pos; i++) {
                if (word[pos - i] != word[wordlen - 1 - i]) {
                    break;
                }
                length++;
            }

            return length;
        }
        static void make_delta2(size_t* delta2, unsigned char* pat, size_t patlen) noexcept {
            size_t last_prefix_index = 1;
            for (size_t p = patlen; p != 0; p--) {
                if (is_prefix(pat, patlen, p)) {
                    last_prefix_index = p;
                }
                delta2[p - 1] = patlen - p + last_prefix_index;
            }
            for (size_t p = 0; p < patlen - 1; p++) {
                const auto slen = suffix_length(pat, patlen, p);
                if (pat[p - slen] != pat[patlen - 1 - slen]) {
                    delta2[patlen - 1 - slen] = patlen - 1 - p + slen;
                }
            }
        }
        size_t boyer_moore(unsigned char* string, size_t stringlen, unsigned char* pat, size_t patlen) const noexcept {

            size_t delta1[256];
            std::unique_ptr<size_t[]> delta2 = std::make_unique<size_t[]>(patlen);
            if (!delta2)
                return -1;
            make_delta1(delta1, pat, patlen);
            make_delta2(delta2.get(), pat, patlen);
            size_t n_shifts = 0;
            for (size_t i = patlen - 1; i < stringlen;) {
                ptrdiff_t j = patlen - 1;
                while (j >= 0 && (string[i] == pat[j])) {
                    --i;
                    --j;
                }
                if (j < 0)
                    return i + 1;

                i += delta1[string[i]] > delta2[j] ? delta1[string[i]] : delta2[j];
            }
            return -1;
        }



    public:


        template<typename Val>
        Val to_value(size_type off = 0) const {
            std::unique_ptr<Val> p = std::make_unique<Val>();
            *p = 0;
            auto nSize = size() - off < sizeof(Val) ? size() - off : sizeof(Val);
            memcpy(p.get(), data() + off, nSize);
            return *reinterpret_cast<Val*>(p.get());
        }

        template<typename charType>
        std::basic_string<charType> to_string(size_type off = 0) const {
            if (empty() || off > size())
                return {};
            const auto pData = begin() + off;
            const size_type nSize = end() - pData;
            const auto needSize = nSize + sizeof(charType) * 2;//最少两个结束符,防止小众语言的变成收尾碰撞问题;
            std::unique_ptr<unsigned char[]> p = std::make_unique<unsigned char[]>(needSize);
            std::fill_n(p.get(), needSize, 0);
            memcpy(p.get(), pData, nSize);
            return reinterpret_cast<charType*>(p.get());
        }
        MemBin& append(const MemBin& src)
        {
            const auto nOldSize = m_nSize;
            resize(m_nSize + src.m_nSize);
            memcpy(m_pData + nOldSize, src.m_pData, src.m_nSize);
            return *this;
        }
        template <typename T>
        MemBin& append(std::initializer_list<T> src) {
            auto size = src.size();
            if (size == 0)
            {
                return *this;
            }
            const auto nOldSize = m_nSize;
            resize(m_nSize + size);
            auto begin = m_pData + nOldSize;
            std::unique_ptr<T[]> p = std::make_unique<T[]>(size);
            std::copy(src.begin(), src.end(), p.get());
            for (size_t i = 0; i < size; i++)
                begin[i] = static_cast<byte_type>(p[i]);
            return *this;
        };

        void insert(size_type nIndex, const void* newElement, size_type nCount) {
            if (newElement == nullptr || nCount == 0)
            {
                return;
            }
            if (nIndex >= m_nSize)
            {
                resize(nIndex + nCount);
            }
            else
            {
                const auto nOldSize = m_nSize;
                resize(m_nSize + nCount);
                memmove(m_pData + nIndex + nCount, m_pData + nIndex,
                    nOldSize - nIndex);
            }
            std::copy_n(static_cast<const_byte_poiter>(newElement), nCount, m_pData + nIndex);
        };
        void insert(size_type nStartIndex, const MemBin& pNewArray) {
            if (pNewArray.size() > 0)
            {
                insert(nStartIndex, pNewArray.data(), pNewArray.size());
            }
        };
        void swap(MemBin& _X)
        {
            std::swap(m_pData, _X.m_pData);
            std::swap(m_nMaxSize, _X.m_nMaxSize);
            std::swap(m_nSize, _X.m_nSize);
        }

    public:
        static const size_type nops = size_type(-1);
        [[nodiscard]]
        size_type find(const MemBin& sub, size_type off = 0)  const noexcept {
            auto nLen = size(), nSubLen = sub.size();
            auto pSrc = m_pData + off;

            if (nLen <= off || nSubLen == 0)
                return nops;
            //实际需求长度
            nLen -= off;
            if (nSubLen > nLen)
                return nops;
            auto  pDes = sub.m_pData;


            switch (nSubLen) {
            case 1: {
                auto lpsz = static_cast<const unsigned char*>(std::memchr(pSrc, *pDes, nLen));
                return (lpsz == nullptr) ? nops : (lpsz - pSrc);
            }
            case 2: {
                for (size_t i = 0; i < nLen - 1; i++) {
                    if (*reinterpret_cast<const short*>(pSrc + i) == *reinterpret_cast<const short*>(pDes))
                        return i + off;
                }
                return nops;
            }
            case 3: {
                for (size_t i = 0; i < nLen - 2; i++) {
                    if (*reinterpret_cast<const short*>(pSrc + i) == *reinterpret_cast<const short*>(pDes)) {
                        if (pSrc[i + 2] == pDes[2]) {
                            return i + off;
                        }
                    }
                }
                return nops;
            }
            case 4: {
                for (size_t i = 0; i < nLen - 3; i++) {
                    if (*reinterpret_cast<const int*>(pSrc + i) == *reinterpret_cast<const int*>(pDes))
                        return i + off;
                }
                return nops;
            }
            case 5: {
                for (size_t i = 0; i < nLen - 4; i++) {
                    if (*reinterpret_cast<const int*>(pSrc + i) == *reinterpret_cast<const int*>(pDes)) {
                        if (pSrc[i + 4] == pDes[4])
                            return i + off;
                    }
                }
                return nops;
            }
            case 6: {
                for (size_t i = 0; i < nLen - 5; i++) {
                    if (*reinterpret_cast<const int*>(pSrc + i) == *reinterpret_cast<const int*>(pDes)) {
                        if (*reinterpret_cast<const short*>(pSrc + i + 4) == *reinterpret_cast<const short*>(pDes + 4))
                            return i + off;
                    }
                }
                return nops;
            }
            default: {
                size_t naddr = boyer_moore(pSrc, nLen, pDes, nSubLen);
                if (naddr != nops)
                    return naddr + off;
                return nops;
            }
            }
        }
        [[nodiscard]]
        size_type rfind(const MemBin& sub)const noexcept {
            auto nLen = size(), nSubLen = sub.size();
            if (nLen < nSubLen)
                return nops;
            size_type off = nLen - nSubLen;

            const auto pSrc = data();
            const auto pDes = sub.data();


            //起始迭代器
            auto it = const_reverse_iterator(this->begin() + off);


            if (nSubLen == 1)
            {
                const auto c = *pDes;
                for (; it != this->rend(); ++it) {
                    if (*it == c)
                        return std::distance(begin(), it.base());
                }
                return nops;
            }
            else if (nSubLen == 2) {
                const auto need = sub.to_value<short>();
                // 迭代器指向容器末尾的前两个元素
                for (; it != this->rend(); ++it) {
                    // 比较连续的两个元素是否与子序列相匹配
                    if (*reinterpret_cast<const short*>(static_cast<const unsigned char*>(it.base().base())) == need)
                        return std::distance(begin(), it.base());

                }
                return nops;
            }
            else if (nSubLen == 3) {
                const auto need = sub.to_value<short>();
                const auto c = sub.back();
                // 迭代器指向容器末尾的前两个元素
                for (; it != this->rend(); ++it) {
                    // 比较连续的两个元素是否与子序列相匹配
                    if (*reinterpret_cast<const short*>(static_cast<const unsigned char*>(it.base().base())) == need) {
                        if (c == *std::next(it, 2).base())
                            return std::distance(begin(), it.base());
                    }
                }
                return nops;
            }
            else if (nSubLen == 4) {
                const auto need = sub.to_value<int>();
                // 迭代器指向容器末尾的前两个元素
                for (; it != this->rend(); ++it) {
                    // 比较连续的两个元素是否与子序列相匹配
                    if (*reinterpret_cast<const int*>(static_cast<const unsigned char*>(it.base())) == need) {
                        return std::distance(begin(), it.base());
                    }

                }
                return nops;
            }
            else if (nSubLen == 5) {
                const auto need = sub.to_value<int>();
                const auto c = sub.back();
                // 迭代器指向容器末尾的前两个元素
                for (; it != this->rend(); ++it) {
                    // 比较连续的两个元素是否与子序列相匹配
                    if (*reinterpret_cast<const int*>(static_cast<const unsigned char*>(it.base().base())) == need) {
                        if (c == *std::next(it, 4).base())
                            return std::distance(begin(), it.base());
                    }
                }
                return nops;
            }
            else if (nSubLen == 6) {
                const auto need = sub.to_value<int>();
                const auto c = sub.to_value<short>(3);
                // 迭代器指向容器末尾的前两个元素
                for (; it != this->rend(); ++it) {
                    // 比较连续的两个元素是否与子序列相匹配
                    if (*reinterpret_cast<const int*>(static_cast<const unsigned char*>(it.base().base())) == need) {
                        if (c == *std::next(it, 4).base())
                            return std::distance(begin(), it.base());
                    }
                }
                return nops;
            }

            std::array<size_type, 256> next;
            for (auto& c : next)
                c = nSubLen;
            for (size_t i = nSubLen; i > 0; i--)
                next[pDes[i - 1]] = i;


            const unsigned char* naddr = pSrc + off;
            for (; naddr >= pSrc; naddr -= next[naddr[-1]])
                if (memcmp(naddr, pDes, nSubLen) == 0)
                    return naddr - pSrc;
            return nops;
        }
        [[nodiscard]]
        size_type rfind(const MemBin& sub, size_type off) const noexcept {
            auto nLen = size(), nSubLen = sub.size();
            if (nLen < nSubLen)
                return nops;


            if (off < nLen)
                nLen = off + 1;

            if (nLen < nSubLen)
                return nops;
            off = nLen - nSubLen;

            const auto pSrc = data();
            const auto pDes = sub.data();


            //起始迭代器
            auto it = const_reverse_iterator(this->begin() + off);


            if (nSubLen == 1)
            {
                const auto c = *pDes;
                for (; it != this->rend(); ++it) {
                    if (*it == c)
                        return std::distance(begin(), it.base());
                }
                return nops;
            }
            else if (nSubLen == 2) {
                const auto need = sub.to_value<short>();
                // 迭代器指向容器末尾的前两个元素
                for (; it != this->rend(); ++it) {
                    // 比较连续的两个元素是否与子序列相匹配
                    if (*reinterpret_cast<const short*>(static_cast<const unsigned char*>(it.base().base())) == need)
                        return std::distance(begin(), it.base());

                }
                return nops;
            }
            else if (nSubLen == 3) {
                const auto need = sub.to_value<short>();
                const auto c = sub.back();
                // 迭代器指向容器末尾的前两个元素
                for (; it != this->rend(); ++it) {
                    // 比较连续的两个元素是否与子序列相匹配
                    if (*reinterpret_cast<const short*>(static_cast<const unsigned char*>(it.base().base())) == need) {
                        if (c == *std::next(it, 2).base())
                            return std::distance(begin(), it.base());
                    }
                }
                return nops;
            }
            else if (nSubLen == 4) {
                const auto need = sub.to_value<int>();
                // 迭代器指向容器末尾的前两个元素
                for (; it != this->rend(); ++it) {
                    // 比较连续的两个元素是否与子序列相匹配
                    if (*reinterpret_cast<const int*>(static_cast<const unsigned char*>(it.base().base())) == need) {
                        return std::distance(begin(), it.base());
                    }

                }
                return nops;
            }
            else if (nSubLen == 5) {
                const auto need = sub.to_value<int>();
                const auto c = sub.back();
                // 迭代器指向容器末尾的前两个元素
                for (; it != this->rend(); ++it) {
                    // 比较连续的两个元素是否与子序列相匹配
                    if (*reinterpret_cast<const int*>(static_cast<const unsigned char*>(it.base().base())) == need) {
                        if (c == *std::next(it, 4).base())
                            return std::distance(begin(), it.base());
                    }
                }
                return nops;
            }
            else if (nSubLen == 6) {
                const auto need = sub.to_value<int>();
                const auto c = sub.to_value<short>(3);
                // 迭代器指向容器末尾的前两个元素
                for (; it != this->rend(); ++it) {
                    // 比较连续的两个元素是否与子序列相匹配
                    if (*reinterpret_cast<const int*>(static_cast<const unsigned char*>(it.base().base())) == need) {
                        if (c == *std::next(it, 4).base())
                            return std::distance(begin(), it.base());
                    }
                }
                return nops;
            }

            std::array<size_type, 256> next;
            for (auto& c : next)
                c = nSubLen;
            for (size_t i = nSubLen; i > 0; i--)
                next[pDes[i - 1]] = i;


            const unsigned char* naddr = pSrc + off;
            for (; naddr >= pSrc; naddr -= next[naddr[-1]])
                if (memcmp(naddr, pDes, nSubLen) == 0)
                    return naddr - pSrc;
            return nops;
        }
        [[nodiscard]]
        MemBin replace(size_type nStart, size_type  nRpLen, const MemBin& sub = {}) const noexcept {
            if (empty())
                return {};
            auto pBin = data(), pSubBin = sub.data();;
            auto nSubLen = sub.size(), nLen = this->size();;


            if (nStart > nLen)
                nStart = nLen - 1;

            if (nStart + nRpLen > nLen) nRpLen = nLen - nStart;
            auto nNewLen = nLen - nRpLen + nSubLen;
            if (nNewLen <= 0) return {};


            if (nStart == 0)
            {
                if (nSubLen == 0)
                    return { pBin + nRpLen, nNewLen };
                MemBin pTemp;
                pTemp.resize(nNewLen);
                memcpy(pTemp.data(), pSubBin, nSubLen);
                memcpy(pTemp.data() + nSubLen, pBin + nRpLen, nLen - nRpLen);
                return pTemp;
            }
            else if (nStart >= nLen)
            {
                if (nSubLen == 0)
                    return { pBin, nNewLen };

                MemBin pTemp;
                pTemp.resize(nNewLen);
                memcpy(pTemp.data(), pBin, nLen);
                memcpy(pTemp.data() + nLen, pSubBin, nSubLen);
                return pTemp;
            }

            MemBin pTemp;
            pTemp.resize(nNewLen);

            memcpy(pTemp.data(), pBin, nStart);
            auto p = pTemp.data() + nStart;
            if (nSubLen > 0)
            {
                memcpy(p, pSubBin, nSubLen);
                p += nSubLen;
            }
            if (nStart + nSubLen < nNewLen)
                memcpy(p, pBin + nStart + nRpLen, nLen - nStart - nRpLen);
            return pTemp;

        }
    public:
        MemBin& operator=(const MemBin& src) {
            resize(src.m_nSize);
            memcpy(m_pData, src.m_pData, src.m_nSize);
            return *this;
        }


        MemBin& operator=(std::initializer_list<unsigned char> src) {
            resize(src.size());
            memcpy(m_pData, src.begin(), src.size());
            return *this;
        }
        bool operator==(const MemBin& src) const {
            if (src.empty() && empty())
                return true;
            if (src.size() != size())
                return false;
            return memcmp(m_pData, src.m_pData, size()) == 0;
        }

        MemBin& operator+=(
            const MemBin& other) {
            append(other);
            return *this;
        }
        [[nodiscard]]
        const_reference operator[](const size_type _P) const noexcept
        {
            return *(m_pData + _P);
        }
        [[nodiscard]]
        reference operator[](const size_type _P) noexcept {
            return	*(m_pData + _P);
        };
    public:
        //到十进制文本
        template <typename T>
        std::basic_string<T> to_byte_str() const {
            if (empty()) {
                return std::basic_string<T>();
            }

            const size_t length = size();
            //std::basic_string <T> buffer(length * 4 + sizeof("{}"));
            std::unique_ptr<T[]>buffer = std::make_unique<T[]>(length * 4 + sizeof("{}"));
            size_t buffer_index = 0;
            buffer[buffer_index++] = T('{');

            for (const auto byte : *this) {
                auto hundreds = byte / 100;
                auto tens = byte % 100 / 10;
                auto ones = byte % 10;

                if (hundreds > 0) {
                    buffer[buffer_index++] = hundreds + T('0');
                    buffer[buffer_index++] = tens + T('0');
                }
                else if (tens > 0) {
                    buffer[buffer_index++] = tens + T('0');
                }
                buffer[buffer_index++] = ones + T('0');
                buffer[buffer_index++] = ',';
            }
            buffer[buffer_index - 1] = '}';

            return std::basic_string<T>(buffer.get(), buffer_index);
        }
        MemBin left(size_t nDataSize) {
            if (empty() || nDataSize == 0)
                return {};
            if (nDataSize > size())
                nDataSize = size();
            return { begin(),nDataSize };
        }
        MemBin mid(size_type nStart, size_t nObjLen) {
            if (empty() || nObjLen == 0)
                return {};
            auto nDataSize = size();
            if (nStart > nDataSize)
                return {};

            if (nStart + nObjLen >= nDataSize)
                nObjLen = nDataSize - nStart;
            nDataSize = nObjLen;
            return { begin() + nStart,nDataSize };
        }
        MemBin right(size_t nCount) {
            if (empty() || nCount <= 0)
                return {};
            if (nCount >= size())
                return *this;
            auto nOffset = size() - nCount;

            return { begin() + nOffset ,nCount };
        }

    private:
        byte_poiter m_pData{ nullptr }; //起始指针  
        size_t m_nSize{ 0 };     //长度
        size_t m_nMaxSize{ 0 };  //容量
        //因为字节集类对于迭代器要求非常低,所以对于迭代要求比较小

    };

    inline MemBin operator+(const MemBin& left,
        const MemBin& other) {
        MemBin temp{ left };
        return temp.append(other);
    }
    template <typename T>
    inline MemBin operator+(const MemBin& left,
        std::initializer_list<T> other) {
        MemBin temp{ left };
        return temp.append(other);
    }

    namespace __in_core {

        //标准库沟通函数
        template <class _Elem, class _Traits>
        std::basic_ostream<_Elem, _Traits>& MemBinput_str(std::basic_ostream<_Elem, _Traits>& ostr, const _Elem* const data, const size_t size) {
            using OStreamType = std::basic_ostream<_Elem, _Traits>;
            typename OStreamType::iostate state = OStreamType::goodbit; // 初始化状态

            size_t pad_count;
            // 计算需要填充的数量
            if (ostr.width() <= 0 || static_cast<size_t>(ostr.width()) <= size) {
                pad_count = 0; // 不需要填充
            }
            else {
                pad_count = static_cast<size_t>(ostr.width()) - size; // 计算填充的数量
            }

            const typename OStreamType::sentry ok(ostr); // sentry 用于检查流的状态是否正常

            if (!ok) {
                state |= OStreamType::badbit; // 如果流的状态不正常，设置坏位并返回
            }
            else { // 如果流的状态正常，进行字符插入和填充
                if ((ostr.flags() & OStreamType::adjustfield) != OStreamType::left) {
                    // 如果不是左对齐，则在左边进行填充
                    for (; pad_count > 0; --pad_count) {
                        if (OStreamType::traits_type::eq_int_type(OStreamType::traits_type::eof(), ostr.rdbuf()->sputc(ostr.fill()))) {
                            state |= OStreamType::badbit; // 插入失败，设置坏位并退出
                            break;
                        }
                    }
                }

                // 插入字符序列
                if (state == OStreamType::goodbit &&
                    ostr.rdbuf()->sputn(data, static_cast<std::streamsize>(size)) != static_cast<std::streamsize>(size)) {
                    state |= OStreamType::badbit; // 如果插入失败，设置坏位
                }
                else {
                    // 如果插入成功且仍有剩余填充，则在右边进行填充
                    for (; pad_count > 0; --pad_count) {
                        if (OStreamType::traits_type::eq_int_type(OStreamType::traits_type::eof(), ostr.rdbuf()->sputc(ostr.fill()))) {
                            state |= OStreamType::badbit; // 插入失败，设置坏位并退出
                            break;
                        }
                    }
                }

                ostr.width(0); // 重置填充宽度为0，避免影响后续插入操作
            }

            ostr.setstate(state); // 设置流的状态
            return ostr; // 返回修改后的输出流对象
        }

    }

    template <class _Elem, class _Traits>
    std::basic_ostream<_Elem, _Traits>& operator<<(
        std::basic_ostream<_Elem, _Traits>& _Ostr, const MemBin& mem) {

        std::basic_string<_Elem> _Str{ mem.to_byte_str<_Elem>() };
        return __in_core::MemBinput_str(_Ostr, _Str.data(), _Str.size());
    }







    inline MemBin::~MemBin()
    {
        if (m_pData)
            delete[] m_pData;
    }
    inline void MemBin::reserve(size_type nNewSize)
    {
        if (capacity() < nNewSize)
        {
            if (m_pData == nullptr)
            {
                m_pData = new byte_type[nNewSize]{};
                m_nMaxSize = nNewSize;
            }
            else {
                auto p{ new byte_type[nNewSize]{} };
                std::copy_n(m_pData, m_nSize, p);
                delete[] m_pData;
                m_pData = p;
                m_nMaxSize = nNewSize;
            }

        }
    }
    inline void MemBin::resize(size_type nNewSize)
    {

        if (nNewSize == 0)
        {
            if (m_pData)
                delete[] m_pData;
            m_pData = nullptr;
            m_nSize = m_nMaxSize = 0;
        }
        else if (m_pData == nullptr)
        {

            m_pData = new byte_type[nNewSize]{};
            m_nSize = m_nMaxSize = nNewSize;
        }
        else if (nNewSize <= m_nMaxSize)
        {
            if (nNewSize > m_nSize)
                std::fill_n(m_pData + m_nSize, nNewSize - m_nSize, 0);
            m_nSize = nNewSize;
        }
        else
        {
            //最小两倍当前长度的扩容,因为容量肯定会预设特别大
            size_type nNewMax = nNewSize < m_nSize * 2 ? m_nSize * 2 : nNewSize;
            byte_poiter pNewData = new byte_type[nNewMax];
            std::copy_n(m_pData, m_nSize, pNewData);
            std::fill_n(pNewData + m_nSize, nNewSize - m_nSize, 0);
            delete[]m_pData;
            m_pData = pNewData;
            m_nSize = nNewSize;
            m_nMaxSize = nNewMax;

        }
    }



}

namespace krnln {

    namespace helper {
        //#define formarg(x) formatText(const std::wstring& text, std::reference_wrapper<x> output)
        //#define formintegral(x) formatText(const std::wstring& text, std::reference_wrapper<x> output){ output.get() = static_cast<x>(_wtoi(text.c_str())); }
        //        fn formarg(CXText) {
        //            output.get() = text;
        //        }
        //        fn formintegral(unsigned char) 
        //        fn formintegral(int)
        //        fn formintegral(short)


        template <typename T>
        inline void formatText(const std::wstring& text, std::reference_wrapper<T> output) {
            using BaseType = std::remove_cv_t<std::remove_reference_t<T>>;

            if constexpr (std::is_same_v<BaseType, CXText>) {
                output.get() = text;
            }
            else if constexpr (std::is_integral_v<BaseType>) {
                if constexpr (sizeof(BaseType) <= sizeof(std::int32_t)) {
                    output.get() = static_cast<BaseType>(std::wcstol(text.c_str(), nullptr, 10));
                }
                else {
                    output.get() = static_cast<BaseType>(std::wcstoll(text.c_str(), nullptr, 10));
                }
            }
            else if constexpr (std::is_floating_point_v<BaseType>) {
                output.get() = static_cast<BaseType>(std::wcstod(text.c_str(), nullptr));
            }
            else {
                static_assert(std::is_same_v<BaseType, BaseType>, "Unsupported type for text formatting");
            }
        }

    }




    fn ErrorMsgBox(const std::wstring& filePath, const std::wstring& msg) {
#ifdef _WIN32
#
        std::wstring fileName{ PathFindFileNameW(filePath.c_str()) };/*路径不会为空*/
        std::wstring error_msg{ L"出现运行时异常,已被核心支持库拦截(编译后不会出现该提示，但同样会处理异常操作,防止重大错误引起崩溃!)\n出错文件：" + fileName + L"\n错误信息:" + msg };
        int result = ::MessageBoxW(GetDesktopWindow(), error_msg.c_str(), L"出现重大错误", MB_OK | MB_ICONERROR);
#endif
        constexpr auto eplruntimeerror{ 0x23416 };
        throw eplruntimeerror;
    }


}
#ifdef _DEBUG
#define put_errmsg(x) krnln::ErrorMsgBox(__FILEW__,x)
#else
#define put_errmsg(x)
#endif // DEBUG
#define XCL_ToText(X) krnln::helper::to_string(X)
#define text_replace(...) krnln::str::replace(__VA_ARGS__)
using  StrArray = CXVector<CXText>;

/********************拼音处理部分依赖(用不到的话并不会链接进入代码)*********************/
#include "eplpinyin.hpp"

/********************拼音处理部分依赖(用不到的话并不会链接进入代码)*********************/


/********************数据库处理部分依赖(用不到的话并不会链接进入代码)*********************/
//#include "XCDBFileBase.h"

/********************数据库处理部分依赖(用不到的话并不会链接进入代码)*********************/


namespace krnln {
    namespace helper {
        template<typename T, typename U>
        void assign_values(T&& value, U& variable) {
            variable = std::forward<T>(value);
        }
        template<typename T, typename First, typename... Rest>
        void assign_values(T&& value, First& first, Rest&... rest) {
            assign_values(std::forward<T>(value), first); 
            assign_values(std::forward<T>(value), rest...); 
        }
        //连续赋值
        template<typename T, typename... U>
        void assign_values(T&& value, U&... variables) {
            assign_values(std::forward<T>(value), variables...);
        }
        //多项选择
        template<typename T, typename... Args>
        T choose(int index, T firstOption, Args... otherOptions) {
            std::vector<T> options = { firstOption, otherOptions... };

            if (index < 1 || index > static_cast<int>(options.size())) {
                put_errmsg(L"多项选择的索引值参数小于一或超出了所提供参数表范围");
                throw std::out_of_range("多项选择的索引值参数小于一或超出了所提供参数表范围");
            }

            return options[index - 1];
        }
        // 检查类型T是否可以构造为指定字符类型CharType的basic_string_view
        template<typename CharType, typename Type>
        struct is_basic_string_constructible : std::is_constructible<std::basic_string_view<CharType>, Type> {};

        /// <summary>
        /// 是否可以构造为指定的字符类型
        /// </summary>
        /// <typeparam name="CharType">字符类型</typeparam>
        /// <typeparam name="Type">待检测的类型</typeparam>
        template<typename CharType, typename Type>
        constexpr bool is_be_text_v = is_basic_string_constructible<CharType, std::remove_cvref_t<Type>>::value || std::is_same_v<CharType, std::remove_cvref_t<Type>>;

        // 默认情况下，类型不能转换为文本
        template<typename Type, typename = void>
        struct is_to_text_impl : std::false_type {};

        // 检查类型T是否可以通过std::to_wstring转换为文本
        template<typename Type>
        struct is_to_text_impl<Type, std::void_t<decltype(std::to_wstring(std::declval<Type>()))>> : std::true_type {};

        /// <summary>
        /// 是否可以转换为文本类型
        /// </summary>
        /// <typeparam name="Type">待检测的类型</typeparam>
        template<typename Type>
        constexpr bool is_to_text_v = is_to_text_impl<Type>::value;

        // 转换为CXText（字符串类）类型
        inline auto to_string() -> CXText {
            return {};
        }
        inline auto to_string(const CXText& text) -> CXText {
            return text;
        }

        inline auto to_string(const CXTextA& textA) -> CXText {
            return textA.getPtr();
        }
        inline auto to_string(bool booleanValue) -> CXText {
            return booleanValue ? L"真" : L"假";
        }

        /// <summary>
        /// 将任意类型格式化为CXText（字符串类）
        /// </summary>
        /// <typeparam name="Type">待转换的类型</typeparam>
        /// <param name="value">待转换的值</param>
        /// <returns>转换后的字符串</returns>
        template<typename Type>
        auto to_string(Type&& value) -> CXText {
            using ValueType = std::remove_cvref_t<Type>;

            if constexpr (is_be_text_v<char, ValueType>) {
                if constexpr (std::is_same_v<char, ValueType>) {
                    const wchar_t wc[]{ value, L'\0' };
                    return wc;
                }
                else {
                    return std::string_view{ value }.data();
                }
            }
            else if constexpr (std::is_same_v<krnln::datetime::EPLDATATIME, ValueType>)
            {
                std::wostringstream oss;
                int year = value.tm_year + 1900;
                int month = value.tm_mon + 1;
                int day = value.tm_mday;
                int hour = value.tm_hour;
                int minute = value.tm_min;
                int second = value.tm_sec;
                oss << year << L"年" << month << L"月" << day << L"日";
                if (second != 0 || oss.str().empty()) {
                    oss << hour << L"时" << minute << L"分" << second << L"秒";
                }
                else if (minute != 0) {
                    oss << hour << L"时" << minute << L"分";
                }
                else if (hour != 0) {
                    oss << hour << L"时";
                }
                return oss.str();
            }
            else if constexpr (is_be_text_v<wchar_t, ValueType>) {
                if constexpr (std::is_same_v<wchar_t, ValueType>) {
                    const wchar_t wc[]{ value, L'\0' };
                    return wc;
                }
                else {
                    return std::wstring_view{ value }.data();
                }
            }
            else if constexpr (is_to_text_v<ValueType>) {
                return std::to_wstring(value).data();
            }
            else if constexpr (std::is_same_v<CXBytes, ValueType>) {
                CXText result;
                result.resize(value.size() + 1);
                std::memcpy(std::addressof(result[0]), value.getPtr(), value.size());
                result.resize(wcslen(result.getPtr()));
                return result;
            }
            else {
                put_errmsg(L"选择了无法转换为文本的类型");
                return {};
            }
        }
    }
}

namespace krnln {
    namespace math {
        // 位非运算
        template <typename Type>
        inline auto bnot(Type&& value) {
            return ~value;
        }

        // 左移运算
        inline auto shl(auto&& value, auto&& shift) {
            return value << shift;
        }

        // 右移运算
        inline auto shr(auto&& value, auto&& shift) {
            return value >> shift;
        }

        // 位与运算（出口）
        constexpr inline auto band() {
            return 0;
        }

        // 位与运算（单个参数）
        template <typename Type>
        Type band(Type value) {
            return value;
        }

        // 位与运算（多个参数）
        template <typename Type, typename... Rest>
        Type band(Type value, Rest... rest) {
            return value & band(rest...);
        }

        // 位或运算（出口）
        constexpr inline auto bor() {
            return 0;
        }

        // 位或运算（单个参数）
        template <typename Type>
        Type bor(Type value) {
            return value;
        }

        // 位或运算（多个参数）
        template <typename Type, typename... Rest>
        Type bor(Type value, Rest... rest) {
            return value | bor(rest...);
        }

        // 位异或运算（出口）
        constexpr inline auto bxor() {
            return 0;
        }

        // 位异或运算（单个参数）
        template <typename Type>
        Type bxor(Type value) {
            return value;
        }

        // 位异或运算（多个参数）
        template <typename Type, typename... Rest>
        Type bxor(Type value, Rest... rest) {
            return value ^ bxor(rest...);
        }

        // 合并两个16位无符号整数为32位有符号整数
        inline auto merge_numerical(std::uint16_t a, std::uint16_t b) -> std::int32_t {
            constexpr auto max_size{ 65535 };
            constexpr auto bits_int{ 16 };
            return static_cast<std::int32_t>((a & max_size) | (static_cast<int>(b & max_size) << bits_int));
        }

        inline auto pow(auto value, auto num) {
            static_assert(std::is_arithmetic_v<decltype(value)>, "欲求其某次方的数值必须为数值型");
            static_assert(std::is_arithmetic_v<decltype(num)>, "对欲求次方数值的运算指数必须为数值型");
            return ::std::pow(value, num);
        }
    }

    namespace str {
        // 获取字符串长度
        fn wcslen(const CXText& text)  {
            return text.size();
        }

        // 获取字符串的左侧指定长度的子串
        fn leftstr(const CXText& text, int count) -> CXText {
            return const_cast<CXText&>(text).substr(0, count);
        }

        // 获取字符串的右侧指定长度的子串
        fn rightstr(const CXText& text, int count) -> CXText {
            const auto actual_count = text.size() < count ? text.size() : count;
            if (actual_count <= 0)
                return {};
            return { text.getPtr() + text.size() - actual_count };
        }

        // 获取字符串的指定位置和长度的子串
        inline auto substr(const CXText& text, size_t offset, size_t count) -> CXText {
            if (text.empty() || offset < 1 || offset > static_cast<size_t>(text.size()))
                return {};

            const auto start_pos = offset - 1;
            const auto actual_count = (text.size() - start_pos < count) ? text.size() - start_pos : count;
            if (actual_count <= 0) {
                put_errmsg(L"取文本中间出现不可能的情况!");
            }
            CXText result;
            result.getString()->assign(text.getPtr() + start_pos, actual_count);
            return result;
        }

        // 根据字符创建字符串
        inline auto chr(const wchar_t& character) -> CXText {
            return { character };
        }

        // 获取字符串指定位置的字符的utf16代码
        inline auto unic(const CXText& text, size_t position = 1) -> int {
            if (text.empty() || position < 1 || position > static_cast<size_t>(text.size()))
                return {};
            return text[position - 1];
        }

        // 查找子字符串在指定文本中的位置
        inline auto findstr(const CXText& text, const CXText& subText, size_t position = 1, bool ignore_case = true) -> ptrdiff_t {
            if (text.empty() || subText.empty() || subText.size() > text.size())
                return -1;
            if (position < 1 || position > static_cast<size_t>(text.size()))
                return -1;
            position--;
            const auto result_ptr{
                ignore_case ?
                [](
                    const wchar_t* haystack,
                    const wchar_t* needle) -> const wchar_t* {
                    const wchar_t* needle_cur = needle;
                    if (!*needle) {
                        return haystack + wcslen(haystack);
                    }
                    for (const wchar_t* haystack_cur = haystack; *haystack_cur; haystack_cur++) {
                        if (towlower(*haystack_cur) == towlower(*needle_cur)) {
                            needle_cur++;
                            if (!*needle_cur) {
                                return haystack_cur - wcslen(needle) + 1;
                            }
                        }
                        else {
                            needle_cur = needle;
                        }
                    }
                    return nullptr;
                }(text.getPtr() + position, subText.getPtr()) // 忽略大小写
                    :
                    wcsstr(text.getPtr() + position, subText.getPtr()) // 区分大小写
            };
            if (result_ptr && result_ptr != text.getPtr())
                return std::distance(text.getPtr(), result_ptr) + 1;
            return -1;
        }
        /// <summary>
        /// 内部函数空间
        /// </summary>
        namespace _imp {

            inline auto wcsrfind(const wchar_t* haystack, size_t haystack_len, size_t start_pos, const wchar_t* needle, size_t needle_len, bool case_insensitive) -> ptrdiff_t
            {
                // 检查输入字符串是否为空
                if (!haystack || !needle)
                    return -1;

                // 检查子字符串长度是否有效
                if (needle_len == 0 || needle_len > haystack_len)
                    return -1;

                // 计算实际的搜索起始位置
                size_t search_start = start_pos;
                if (haystack_len - needle_len < start_pos)
                    search_start = haystack_len - needle_len;

                const wchar_t* search_ptr = haystack + search_start;

                while (search_ptr >= haystack)
                {
                    bool match = true;

                    for (size_t i = 0; i < needle_len; ++i)
                    {
                        wchar_t haystack_char = case_insensitive ? towupper(search_ptr[i]) : search_ptr[i];
                        wchar_t needle_char = case_insensitive ? towupper(needle[i]) : needle[i];

                        if (haystack_char != needle_char)
                        {
                            match = false;
                            break;
                        }
                    }

                    if (match)
                        return search_ptr - haystack + 1;

                    --search_ptr;
                }

                return -1;
            };

        }

        inline auto rfindstr(const  CXText& pText, const  CXText& pSubStr, std::optional<size_t> off = std::nullopt, bool  case_insensitive = true) -> ptrdiff_t {
            if (pText.empty() || pSubStr.empty() || pSubStr.size() > pText.size())
                return -1;
            auto pos{ off.value_or(pText.size()) };
            if (pos < 1 || pos > static_cast<size_t>(pText.size()))
                return -1;
            pos--;
            return _imp::wcsrfind(pText.getPtr(), pText.size(), pos, pSubStr.getPtr(), pSubStr.size(), case_insensitive);
        }

        inline CXText lowcase(const  CXText& pText) {
            CXText ret(pText);
            std::transform(pText.getPtr(), pText.getPtr() + pText.size(), std::addressof(ret[0]), towlower);
            return  ret;
        }
        inline CXText upcase(const  CXText& pText) {
            CXText ret(pText);
            std::transform(pText.getPtr(), pText.getPtr() + pText.size(), std::addressof(ret[0]), towupper);
            return ret;
        }
        inline CXText lefttrim(const  CXText& str) {
            auto& pText = *const_cast<CXText&>(str).getString();
            auto it = std::find_if_not(pText.begin(), pText.end(), ::iswspace);


            return (it != pText.end()) ? std::wstring(it, pText.end()) : CXText{};

        }
        inline CXText righttrim(const  CXText& str) {
            auto& pText = *const_cast<CXText&>(str).getString();
            auto rit = std::find_if_not(pText.rbegin(), pText.rend(), ::iswspace);
            return (rit != pText.rend()) ? std::wstring(pText.begin(), rit.base()) : CXText{};

        }
        inline CXText lrtrim(const CXText& str) {
            auto trimmedLeft = lefttrim(str);
            return righttrim(trimmedLeft);
        }


        inline CXText alltrim(const  CXText& str) {
            CXText copy_obj{ str };
            auto& trimmed{ *copy_obj.getString() };
            std::erase_if(trimmed, [](wchar_t c) {
                return iswspace(c);
                });
            return copy_obj;
        }


        inline CXText replace(const  CXText& pText, size_t off, size_t lenth, const  CXText& pstr) {
            if (off < 1 || off > static_cast<size_t>(pText.size()))
                return pText;
            CXText copy_obj{ pText };
            auto& self = *copy_obj.getString();
            return self.replace(off - 1, lenth, pstr.getPtr());
        }
        inline CXText subreplace(const CXText& pText, const CXText& pSubText, const std::optional<CXText>& pReplaceText = std::nullopt, std::optional<size_t> off = std::nullopt, std::optional<size_t> count = std::nullopt, bool dx = true) {
            // 起始位置参数规范
            size_t startOffset = off.value_or(1);
            if (startOffset < 1 || startOffset >static_cast<size_t>(pText.size())) {
                return pText;
            }


            // 最大替换次数规范
            constexpr auto maxReplacements = (std::numeric_limits<size_t>::max)();
            size_t replaceCount = count.value_or(0) == 0 ? maxReplacements : count.value();

            if (pSubText.empty() || pSubText.size() > pText.size()) {
                return pText;
            }

            const wchar_t* replacement = pReplaceText.has_value() ? pReplaceText.value().getPtr() : L"";
            CXText result(pText);
            ptrdiff_t pos = 0;
            size_t subTextSize = pSubText.size();
            size_t replacementSize = std::wcslen(replacement);

            do {
                pos = findstr(result, pSubText, startOffset, dx);
                if (pos == -1) {
                    break;
                }
                result.getString()->replace(pos - 1, subTextSize, replacement);
                pos += replacementSize;
                --replaceCount;
            } while (pos > 0 && replaceCount > 0);

            return result;
        }
        inline CXText tofull(const  CXText& pText) {
            if (pText.empty())
                return {};

            auto& s{ *const_cast<CXText&>(pText).getString() };

            CXText result;
            auto& str{ *result.getString() };
            str.reserve(s.size());


            for (const auto& c : s)
            {
                if (c == L' ')
                    str.push_back(wchar_t{ 0x3000 });
                else if (c >= 33 && c <= 126)
                    str.push_back(c + 65248);
                else
                    str.push_back(c);
            }

            return result;
        };

        inline CXText tohalf(const  CXText& pText) {
            if (pText.empty())
                return {};

            auto& s{ *const_cast<CXText&>(pText).getString() };

            CXText result;
            auto& str{ *result.getString() };
            str.reserve(s.size());


            for (const auto& upChar : s)
            {
                if (upChar == 0x3000)
                    str.push_back(L' ');
                else if (upChar >= 65281 && upChar <= 65374)
                    str.push_back(upChar - 65248);
                else
                    str.push_back(upChar);
            }
            return result;

        };

        inline CXText  space_str(int count) {
            return  std::wstring(count, L' ');
        }
        inline CXText  string_str(int nCount, const CXText& desStr) {
            if (desStr.empty() || nCount == 0)
                return {};

            CXText  str;
            str.reserve(desStr.size() * nCount);
            for (size_t i = 0; i < nCount; ++i)
                str.append(desStr);

            return str;
        }


        inline auto strcomp(const  CXText& str1, const  CXText& str2, bool case_insensitive) -> int {
            return case_insensitive ? _wcsicmp(str1, str2) : wcscmp(str1, str2);
        }
        inline StrArray split(const  CXText& ps,
            const std::optional<CXText>& pSplit = std::nullopt,
            const std::optional<int>& maxCount = std::nullopt) {
            StrArray strary; // 用于存储分割后的子文本
            std::wstring_view sv(ps); // 创建 std::wstring_view 以避免不必要的拷贝
            std::wstring delimiter = *pSplit.value_or(CXText{ L"," }).getString(); // 获取分隔符，默认为逗号

            // 如果 maxCount 被指定且小于等于 0，则返回空的结果
            if (maxCount.has_value() && *maxCount <= 0) {
                return {};
            }

            // 如果分隔符为空字符串，直接返回整个字符串作为单个元素
            if (delimiter.empty()) {
                strary.add(ps);
                return strary;
            }



            size_t start = 0; // 起始位置
            size_t end = sv.find_first_of(delimiter); // 查找第一个分隔符的位置

            // 循环处理每个分隔符
            while (end != std::wstring_view::npos) {
                std::wstring_view token = sv.substr(start, end - start); // 提取子文本
                if (!token.empty()) {
                    // 删去子文本首尾的空白字符
                    auto first = std::find_if_not(token.begin(), token.end(), ::iswspace);
                    auto last = std::find_if_not(token.rbegin(), token.rend(), ::iswspace).base();
                    if (first < last) {
                        strary.add(std::wstring{ first, last }); // 添加到结果数组中
                    }
                }
                start = end + 1; // 更新起始位置，跳过当前分隔符
                end = sv.find_first_of(delimiter, start); // 查找下一个分隔符的位置

                // 如果达到最大子文本数量，则停止处理
                if (maxCount && strary.size() >= *maxCount) {
                    break;
                }
            }

            // 处理最后一个子文本
            std::wstring_view token = sv.substr(start);
            if (!token.empty()) {
                auto first = std::find_if_not(token.begin(), token.end(), ::iswspace);
                auto last = std::find_if_not(token.rbegin(), token.rend(), ::iswspace).base();
                if (first < last) {
                    strary.add(std::wstring{ first, last }); // 添加到结果数组中
                }
            }

            // 如果结果数组的大小超过了 maxCount，则调整其大小,正常情况下不会走到这
            if (maxCount && strary.size() > *maxCount) {
                strary.resize(*maxCount);
            }

            return strary; // 返回分割后的结果数组
        }


    }
    namespace pinyin {

        inline auto __PyToLow(const std::wstring_view& text)
        {
            std::wstring ret(text);
            std::transform(text.begin(), text.end(), ret.begin(), tolower);
            return ret;
        }
        inline auto& __PyRemoveTrim(std::wstring& text) {
            std::wstring mark = L" ";
            size_t nSize = mark.size();
            if (text.empty() || text == L"") {
                return text;
            }
            while (1)
            {
                size_t pos = text.find(mark);    //  尤其是这里
                if (pos == std::wstring::npos)
                {
                    return text;
                }
                text.erase(pos, nSize);
            }
        }
        inline bool comp_pinyin(const CXText& str1, const CXText& str2, bool  IsFuzzy = false)
        {
            if (IsFuzzy)
                return  __PyToLow(::eplpinyin::GetStrPinyinFirst(str1.get())) == __PyToLow(::eplpinyin::GetStrPinyinFirst(str2.get()));
            return (__PyToLow(::eplpinyin::GetStrPinyinNoNop(str1.get())) == __PyToLow(::eplpinyin::GetStrPinyinNoNop(str2.get())));
        }

        inline bool comp_text(const CXText& a1, const CXText& a2)
        {

            auto IsFuzzy = eplpinyin::IsAllSpelled(a1.get());
            if (IsFuzzy) {

                auto str1 = eplpinyin::GetStrPinyinNoNop(a1.get());
                auto str2 = eplpinyin::GetStrPinyinNoNop(a2.get());
                auto py1 = __PyToLow(str1), py2 = __PyToLow(str2);
                return (__PyRemoveTrim(py1) == __PyRemoveTrim(py2));
            }

            auto str1 = eplpinyin::GetStrPinyinFirst(a1.get());
            auto str2 = eplpinyin::GetStrPinyinFirst(a2.get());
            auto py1 = __PyToLow(str1), py2 = __PyToLow(str2);
            return (__PyRemoveTrim(py1) == __PyRemoveTrim(py2));
        }
    }

    namespace syspro {

        namespace inputbox {

            class MyDlg
            {
                struct DlgData
                {
                    std::wstring m_text;
                    bool m_bRet = false;

                };

                inline static BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
                {
                    switch (uMsg)
                    {
                    case WM_INITDIALOG:
                        ::SetWindowLongPtrW(hDlg, GWLP_USERDATA, lParam);
                        SetFocus(GetDlgItem(hDlg, 58570));
                        return FALSE;
                    case WM_COMMAND:
                    {
                        INT nID = wParam & 0xffff;
                        if (nID == IDCANCEL)
                            DestroyWindow(hDlg);
                        else if (nID == IDOK) {

                            auto pDlgData = reinterpret_cast<DlgData*>(::GetWindowLongPtrW(hDlg, GWLP_USERDATA));
                            auto hEdit = GetDlgItem(hDlg, 58570);
                            INT nLen = ::GetWindowTextLengthW(hEdit);
                            if (nLen > 0)
                            {
                                WCHAR* pText = new WCHAR[nLen + 1]{ 0 };
                                GetWindowTextW(hEdit, pText, nLen + 1);
                                pDlgData->m_text = pText;
                                delete[]pText;
                            }
                            pDlgData->m_bRet = true;
                            DestroyWindow(hDlg);
                        }
                    }
                    break;
                    case WM_CLOSE:
                        DestroyWindow(hDlg);
                        break;
                    case WM_DESTROY:
                        PostMessage(hDlg, WM_QUIT, 0, 0);
                        break;
                    default:
                        return FALSE;

                    }
                    return TRUE;
                }
#pragma pack(push, 1)  
#pragma warning(disable:4200)
                struct DLGTEMPLATEEX // Already defined in Win SDK
                {
                    WORD        dlgVer;    // must be 0x0001
                    WORD        signature; // must be 0xFFFF
                    DWORD       helpID;
                    DWORD       exStyle;
                    DWORD       style;
                    WORD        cDlgItems;
                    short       x;
                    short       y;
                    short       cx;
                    short       cy;
                    short menu;
                    short windowClass;
                    WCHAR     title[];

                };
                //#if (style & (DS_SETFONT|DS_SHELLFONT))
                struct FONTDLG
                {
                    WORD      pointsize = 9;
                    WORD      weight = 0;
                    BYTE      italic = 0;
                    BYTE      charset = 0;
                    WCHAR     typeface[19] = L"Microsoft YaHei UI";
                };
                struct DLGITEMTEMPLATEEX
                {
                    DWORD       helpID;
                    DWORD       exStyle;
                    DWORD       style;
                    short       x;
                    short       y;
                    short       cx;
                    short       cy;
                    DWORD       id;
                    WORD must;
                    WORD windowClass;
                    WCHAR title[];
                    //其后跟随
                    //WORD      extraCount;

                };
#pragma pack(pop) 
            public:
                /*添加控件*/
                inline void Add(const std::wstring& title,
                    DWORD style,
                    short       x,
                    short       y,
                    short       cx,
                    short       cy,
                    DWORD       id,
                    WORD windowClass
                ) {
                    constexpr size_t  gitem_size = sizeof(DLGITEMTEMPLATEEX) + sizeof(WORD);
                    auto lenth = (title.size() + 1) * sizeof(wchar_t);
                    size_t cbTotal = lenth + gitem_size;
                    if (cbTotal % 4)
                        cbTotal += 2;
                    auto dlg_template = reinterpret_cast<DLGITEMTEMPLATEEX*>(new char[cbTotal] { 0 });
                    dlg_template->cx = cx;
                    dlg_template->cy = cy;
                    dlg_template->x = x;
                    dlg_template->y = y;
                    dlg_template->helpID = 0;
                    dlg_template->id = id;;
                    dlg_template->style = style;
                    dlg_template->must = 0xffff;//表示系统控件
                    dlg_template->windowClass = windowClass;

                    if (!title.empty())
                    {
                        wcscpy_s(dlg_template->title, title.size() + 1, title.c_str());
                    }

                    m_pData.insert(m_pData.end(),
                        reinterpret_cast<unsigned char*>(dlg_template),
                        reinterpret_cast<unsigned char*>(dlg_template) + cbTotal);
                    delete[]reinterpret_cast<char*>(dlg_template);
                    m_Count++;
                }
                inline HWND Create(short x, short y, short cx, short cy, const std::wstring title, HWND hParent) {
                    DLGTEMPLATEEX Head;
                    Head.dlgVer = 0x0001;
                    Head.signature = 0xFFFF;
                    Head.helpID = 0;
                    Head.cDlgItems = m_Count;
                    Head.cx = cx;
                    Head.cy = cy;
                    Head.x = x;
                    Head.y = y;
                    Head.menu = 0;
                    Head.style = 2160593096;
                    Head.exStyle = 0;
                    Head.windowClass = 0;
                    FONTDLG Font{  };
                    m_pData.insert(m_pData.begin(),
                        reinterpret_cast<unsigned char*>(&Font),
                        reinterpret_cast<unsigned char*>(&Font) + sizeof(Font));
                    if (title.size() % 2)
                        m_pData.insert(m_pData.begin() + sizeof(Font), { 0,0 });
                    if (!title.empty())
                    {
                        m_pData.insert(m_pData.begin(),
                            const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(title.c_str())),
                            const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(title.c_str())) + (title.size() + 1) * sizeof(wchar_t));
                    }
                    else
                    {
                        const auto emptystr = L"";
                        m_pData.insert(m_pData.begin(), const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(emptystr)), const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(emptystr) + sizeof(wchar_t)));

                    }
                    m_pData.insert(m_pData.begin(),
                        reinterpret_cast<unsigned char*>(&Head),
                        reinterpret_cast<unsigned char*>(&Head) + sizeof(Head));

                    m_hDlg = CreateDialogIndirectParamW(GetModuleHandleW(nullptr), (DLGTEMPLATE*)m_pData.data(), hParent, (DLGPROC)DlgProc, reinterpret_cast<LPARAM>(&m_DlgData));

                    return m_hDlg;
                }
                inline bool MessageLoop(bool nType) const {
                    if (m_hDlg) {
                        ShowWindow(m_hDlg, SW_SHOW);
                        UpdateWindow(m_hDlg);
                        MSG msg;
                        while (GetMessageW(&msg, NULL, 0, 0))
                        {
                            if (msg.hwnd == GetDlgItem(m_hDlg, 58570) && msg.message == WM_CHAR) {
                                if (msg.wParam == 13)
                                    ::SendMessage(m_hDlg, WM_COMMAND, IDOK, 0);
                                else if (nType) {
                                    if (!(msg.wParam == '-' || (msg.wParam >= '0' && msg.wParam <= '9') || msg.wParam == '.'))
                                        continue;
                                }

                            }
                            if (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE)
                                PostMessageW(m_hDlg, WM_COMMAND, MAKEWPARAM(IDCANCEL, BN_CLICKED), (LPARAM)GetDlgItem(m_hDlg, IDOK));
                            if (!IsDialogMessageW(m_hDlg, &msg))
                            {
                                TranslateMessage(&msg);
                                DispatchMessageW(&msg);
                            }
                        }
                    }
                    return m_DlgData.m_bRet;
                }

                inline const std::wstring& GetText() const {
                    return m_DlgData.m_text;
                }
            private:
                DlgData  m_DlgData{};
                HWND m_hDlg = NULL;
                WORD m_Count = 0;
                std::vector<unsigned char> m_pData;
            };
        }

        template <typename T>
        fn _imp_InputBox(const std::optional<const CXText>& OppromptMessage = std::nullopt, const std::optional<const CXText>& OpwindowTitle = std::nullopt, const std::optional<const CXText>& OpinitialText = std::nullopt, std::optional <std::reference_wrapper<T>> OpvariableToStoreInput = std::nullopt, const std::optional<int>& OpinputType = std::nullopt, const std::optional<HWND>& parentWindow = std::nullopt, bool bMultiLineAdd = false)->bool {

            auto promptMessage = OppromptMessage.value_or(L"");
            auto hParent = parentWindow.value_or(GetActiveWindow());
            auto windowTitle = OpwindowTitle.value_or(L"");
            auto initialText = OpinitialText.value_or(L"");
            auto inputType = OpinputType.value_or(1);
            short MultiLineAdd = bMultiLineAdd ? 12 : 0;



            if (inputType < 1 || inputType > 5)
                inputType = 1;



            DWORD dwStyleEdit = 1350631552;
            if (bMultiLineAdd)
            {
                dwStyleEdit &= ~ES_AUTOHSCROLL;
                dwStyleEdit |= (ES_MULTILINE | ES_AUTOVSCROLL);
            }
            if (inputType == 4)
            {
                /*密码模式*/
                dwStyleEdit |= ES_PASSWORD;
            }
            else if (inputType == 2)
            {
                /*数字模式*/
                dwStyleEdit |= ES_NUMBER;
            }

            BOOL bWndEnabled = IsWindowEnabled(reinterpret_cast<HWND>(hParent));
            if (bWndEnabled && hParent)
                EnableWindow(reinterpret_cast<HWND>(hParent), FALSE);
            /*动态对话框模板,网上一点B资料没有*/
            inputbox::MyDlg Dlg;
            if (!promptMessage.empty())
            {
                /*按钮*/
                Dlg.Add(L"确认输入(&O)", 1342242816, 63, 66 + MultiLineAdd, 55, 19, IDOK, 0x0080);
                Dlg.Add(L"取消(&C)", 1342242816, 134, 66 + MultiLineAdd, 55, 19, IDCANCEL, 0x0080);

                Dlg.Add(*initialText.getString(), dwStyleEdit, 7, 45, 238, 12 + MultiLineAdd, 58570, 0x0081);
                /*提示框*/
                Dlg.Add(*promptMessage.getString(), 1342312448, 7, 7, 238, 35, 0, 0x0082);
                /*创建*/
                Dlg.Create(0, 0, 252, 92 + MultiLineAdd, *windowTitle.getString(), hParent);
            }
            else
            {	/*无提示文本,窗口需要调整一下*/
                    /*按钮*/
                Dlg.Add(L"确认输入(&O)", 1342242816, 82, 30 + MultiLineAdd, 55, 19, IDOK, 0x0080);
                Dlg.Add(L"取消(&C)", 1342242816, 151, 30 + MultiLineAdd, 55, 19, IDCANCEL, 0x0080);
                /////*输入框 */
                Dlg.Add(*initialText.getString(), dwStyleEdit, 7, 7, 200, 12 + MultiLineAdd, 58570, 0x0081);
                /*创建*/
                Dlg.Create(0, 0, 214, 56 + MultiLineAdd, *windowTitle.getString(), hParent);

            }
            auto ret = Dlg.MessageLoop(inputType == 3);
            if (bWndEnabled && hParent)
                EnableWindow(hParent, TRUE);
            if (hParent)
                SetActiveWindow(hParent);
            if (OpvariableToStoreInput.has_value())
            {
                auto& refthing{ *OpvariableToStoreInput };
                helper::formatText(Dlg.GetText(), refthing);
            }
            return ret;
        }

        inline bool InputBox(const std::optional<const CXText>& OppromptMessage = std::nullopt,
            const std::optional<const CXText>& OpwindowTitle = std::nullopt,
            const std::optional<const CXText>& OpinitialText = std::nullopt,
            std::nullopt_t OpvariableToStoreInput = std::nullopt,
            const std::optional<int>& OpinputType = std::nullopt,
            const std::optional<HWND>& parentWindow = std::nullopt,
            bool bMultiLineAdd = false) {
            return _imp_InputBox<int>(OppromptMessage, OpwindowTitle, OpinitialText, std::nullopt, OpinputType, parentWindow, bMultiLineAdd);
        }
        template <typename T>
        bool InputBox(const std::optional<const CXText>& OppromptMessage,
            const std::optional<const CXText>& OpwindowTitle,
            const std::optional<const CXText>& OpinitialText,
            T& OpvariableToStoreInput,
            const std::optional<int>& OpinputType = std::nullopt,
            const std::optional<HWND>& parentWindow = std::nullopt,
            bool bMultiLineAdd = false) {
            return _imp_InputBox<T>(OppromptMessage, OpwindowTitle, OpinitialText, OpvariableToStoreInput, OpinputType, parentWindow, bMultiLineAdd);
        }

        fn  SetClipboardText(const CXText& clip_text) ->bool
        {

            if (!::OpenClipboard(nullptr))
                return false;
            ::EmptyClipboard();
            if (!clip_text.empty())
            {
                const auto npSize = (clip_text.size() + 1) * sizeof(WCHAR);
                auto hMem = ::GlobalAlloc(GMEM_MOVEABLE, npSize);
                if (hMem != nullptr)
                {
                    ::memcpy(GlobalLock(hMem), clip_text, npSize);
                    ::GlobalUnlock(hMem);
                    ::SetClipboardData(CF_UNICODETEXT, hMem);
                }
            }
            return ::CloseClipboard();
        }
        fn IsClipboardHasText() {
            return ::IsClipboardFormatAvailable(CF_UNICODETEXT) || ::IsClipboardFormatAvailable(CF_TEXT);//实际获取时会根据本地编码自动转换的
        }
        fn GetCurrentClipboardText()->CXText
        {

            if (!::OpenClipboard(nullptr) || !IsClipboardFormatAvailable(CF_UNICODETEXT))
                return {};
            HANDLE  hClipboardData = ::GetClipboardData(CF_UNICODETEXT);
            if (hClipboardData == nullptr) {
                CloseClipboard();
                return {};
            }
            std::vector<wchar_t> ret(::GlobalSize(hClipboardData) + 1);//防止其他软件不规范每增加结束符导致的移除
            std::memcpy(ret.data(), ::GlobalLock(hClipboardData), ::GlobalSize(hClipboardData));
            ::GlobalUnlock(hClipboardData);
            ::CloseClipboard();
            return ret.data();
        }
        inline bool Run(const CXText& com_line, bool bwait = false, int showMode = 2)
        {
            if (com_line.empty())
                return false;
            if (showMode > 6 || showMode <= 0)
                showMode = 2;
            STARTUPINFOW infStartup{};
            infStartup.cb = sizeof(infStartup);
            infStartup.dwFlags = STARTF_USESHOWWINDOW;
            infStartup.wShowWindow = showMode;
            PROCESS_INFORMATION pi{};
            if (!CreateProcessW(nullptr, const_cast<wchar_t*>(com_line.get()), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &infStartup, &pi))
                return false;
            bwait ? WaitForSingleObject(pi.hProcess, INFINITE) : WaitForInputIdle(pi.hProcess, 500);
            return   CloseHandle(pi.hThread) && CloseHandle(pi.hProcess);
        }

        fn OpenFileManyDialogW(
            const std::optional<const CXText>& title = std::nullopt,
            const CXText& _filter = L"",
            int initFilter = 0,
            const std::optional<const CXText>& initDir = std::nullopt,
            bool noChangeDir = false,
            HWND parentWnd = nullptr
        ) ->StrArray
        {
            IFileOpenDialog* pfod{};
            struct CO {
                CO() { cc = CoInitialize(nullptr); };
                ~CO() {
                    if (cc == S_OK) //本线程中从该函数创建成功的,因为是单线程同步执行,不会存在初始化竞争
                        CoUninitialize();
                }
                HRESULT cc{ S_FALSE };
            };
            const CO _IMP{};


            if (FAILED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfod))))
                return {};

            pfod->SetTitle(title.value_or(L"请输入欲打开的文件："));
            if (!_filter.empty())
            {
                auto filter = _filter;//拷贝一下

                std::vector<COMDLG_FILTERSPEC> vFilter{};
                vFilter.push_back({ filter.get() });
                int i{};
                while (auto p = (WCHAR*)wcschr(filter, L'|'))
                {
                    *p = L'\0';
                    if (i == 0)
                    {
                        vFilter.back().pszSpec = p + 1;
                        i = 1;
                    }
                    else
                    {
                        vFilter.push_back({ p + 1 });
                        i = 0;
                    }
                }
                pfod->SetFileTypes((UINT)vFilter.size(), vFilter.data());
            }
            pfod->SetFileTypeIndex(initFilter);

            const auto pidl = ILCreateFromPathW(initDir.value_or(std::filesystem::current_path().wstring().c_str()));
            IShellItem* pItem;
            SHCreateItemFromIDList(pidl, IID_PPV_ARGS(&pItem));
            pfod->SetFolder(pItem);
            ILFree(pidl);
            pItem->Release();

            UINT uFlags{ FOS_CREATEPROMPT | FOS_OVERWRITEPROMPT | FOS_ALLOWMULTISELECT };
            if (noChangeDir)
                uFlags |= FOS_NOCHANGEDIR;
            pfod->SetOptions(uFlags);
            if (FAILED(pfod->Show(parentWnd)))
                return {};

            IShellItemArray* pItemArray;
            DWORD c;
            if (SUCCEEDED(pfod->GetResults(&pItemArray)))
            {
                if (SUCCEEDED(pItemArray->GetCount(&c)))
                {
                    StrArray vRet{  };
                    vRet.resize(c);
                    for (UINT i = 0; i < c; i++)
                    {
                        IShellItem* pItem;
                        if (SUCCEEDED(pItemArray->GetItemAt(i, &pItem)))
                        {
                            PWSTR pszFilePath;
                            if (SUCCEEDED(pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath)))
                            {
                                vRet[i] = pszFilePath;
                                CoTaskMemFree(pszFilePath);
                            }
                            pItem->Release();
                        }
                    }
                    pItemArray->Release();
                    return vRet;
                }
                pItemArray->Release();
            }


            return {};
        }
        fn GetSystemMetricsW() {
            return ::GetSystemMetrics(SM_CXSCREEN);
        }
        fn GetSystemMetricsH() {
            return ::GetSystemMetrics(SM_CYSCREEN);
        }
        fn EmptyClipboard() {
            if (::OpenClipboard(nullptr))
            {
                ::EmptyClipboard();
                ::CloseClipboard();
            }
        }
        template <typename T>
        constexpr auto gettypeid(T&& tyepe) -> size_t {
            using ValueType = std::remove_cvref_t<T>;
            ValueType t{};
            const std::type_info& ti = typeid(t);
            return  ti.hash_code();
        }
        fn GetCurssX() {
            POINT ptCursor{};
            ::GetCursorPos(&ptCursor);
            return ptCursor.x;
        }
        fn GetCurssY() {
            POINT ptCursor{};
            ::GetCursorPos(&ptCursor);
            return ptCursor.y;
        }
        fn GetColorCount() {
            const HDC hDC = ::GetDC(nullptr);
            const auto nNumColors = std::pow(2.0, ::GetDeviceCaps(hDC, BITSPIXEL) * ::GetDeviceCaps(hDC, PLANES));
            ::ReleaseDC(nullptr, hDC);
            return static_cast<int>(nNumColors);
        }

        fn GetRegRootVal(int rootDir) {
            switch (rootDir) {
            case 1: return HKEY_CLASSES_ROOT;
            case 2: return HKEY_CURRENT_CONFIG;
            case 3: return HKEY_CURRENT_USER;
            case 4: return HKEY_LOCAL_MACHINE;
            case 5: return HKEY_USERS;
            default: return static_cast<HKEY>(nullptr);
            }
        }
        

        fn GetTextRegItem(INT rootDir, const CXText& fullPath, const CXText& defaultString = L"")->CXText {
            HKEY hRootKey = GetRegRootVal(rootDir);

            if (hRootKey == nullptr || fullPath.empty())
                return false;
            std::wstring result{ defaultString };
       
            std::wstring copy{ fullPath };
            size_t lastBackslashPos = copy.find_last_of(L'\\');
            if (lastBackslashPos == std::wstring::npos) {
                return result;
            }
            // 分离路径和项名
            std::wstring path = copy.substr(0, lastBackslashPos);
            std::wstring itemName = copy.substr(lastBackslashPos + 1);

            HKEY hKey;
            if (::RegOpenKeyExW(hRootKey, path.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
                return result;
            }
            DWORD dwType, dwDataSize = 0;
            if (::RegQueryValueExW(hKey, itemName.c_str(), nullptr, &dwType, nullptr, &dwDataSize) == ERROR_SUCCESS &&
                (dwType == REG_SZ || dwType == REG_EXPAND_SZ)) {
                //为了安全处理末尾
                std::vector<unsigned char> buffer(dwDataSize + sizeof(WCHAR)), buffer2{};
                if (::RegQueryValueExW(hKey, itemName.c_str(), nullptr, nullptr, buffer.data(), &dwDataSize) == ERROR_SUCCESS) {
                    buffer.push_back(0); buffer.push_back(0);
                    const WCHAR* value = reinterpret_cast<WCHAR*>(buffer.data());
                    // 如果类型是 REG_EXPAND_SZ，则展开环境变量
                    if (dwType == REG_EXPAND_SZ) {
                        const auto npReqNumChars = ::ExpandEnvironmentStringsW(value, nullptr, 0) + 1;
                        buffer2.resize((npReqNumChars + 1) * sizeof(WCHAR));
                        ::ExpandEnvironmentStringsW(value, reinterpret_cast<WCHAR*>(buffer2.data()), npReqNumChars);
                        buffer2.push_back(0); buffer2.push_back(0);
                        value = reinterpret_cast<WCHAR*>(buffer2.data());
                    }
                    result = value;
                }
            }

            ::RegCloseKey(hKey);
            return result;
        }

        fn GetNumRegItem(INT rootDir, const CXText& fullPath, const DWORD& DefaultNumber = 0)->DWORD {
            HKEY hRootKey = GetRegRootVal(rootDir);
            if (hRootKey == nullptr || fullPath.empty())
                return false;

            DWORD result{ DefaultNumber };
            std::wstring copy{ fullPath };
            size_t lastBackslashPos = copy.find_last_of(L'\\');
            if (lastBackslashPos == std::wstring::npos) {
                return result;
            }
            // 分离路径和项名
            std::wstring path = copy.substr(0, lastBackslashPos);
            std::wstring itemName = copy.substr(lastBackslashPos + 1);

            HKEY hKey;
            if (::RegOpenKeyExW(hRootKey, path.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
                return result;
            }
            DWORD dwType, dwDataSize = 0;
            if (::RegQueryValueExW(hKey, itemName.c_str(), nullptr, &dwType, nullptr, &dwDataSize) == ERROR_SUCCESS &&
                dwType == REG_DWORD && sizeof(DWORD)) {

                DWORD dw = 0;
                if (::RegQueryValueExW(hKey, itemName.c_str(), nullptr, nullptr, reinterpret_cast<LPBYTE>(&dw), &dwDataSize) == ERROR_SUCCESS)
                    result = dw;

            }
            ::RegCloseKey(hKey);
            return result;
        }

        fn GetBinRegItem(INT rootDir, const CXText& fullPath, const CXBytes& defaultString = {})->CXBytes {

            HKEY hRootKey = GetRegRootVal(rootDir);
            if (hRootKey == nullptr || fullPath.empty())
                return false;

            CXBytes result{ defaultString };
            std::wstring copy{ fullPath };
            size_t lastBackslashPos = copy.find_last_of(L'\\');
            if (lastBackslashPos == std::wstring::npos) {
                return result;
            }
            // 分离路径和项名
            std::wstring path = copy.substr(0, lastBackslashPos);
            std::wstring itemName = copy.substr(lastBackslashPos + 1);

            HKEY hKey;
            if (::RegOpenKeyExW(hRootKey, path.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
                return result;
            }
            DWORD dwType, dwDataSize = 0;
            // 查询项的类型和数据大小
            if (::RegQueryValueExW(hKey, itemName.c_str(), nullptr, &dwType, nullptr, &dwDataSize) == ERROR_SUCCESS &&
                dwType == REG_BINARY) {
                if (dwDataSize == 0)//空注册项,不可返回默认数据,因为他是有这个注册项的
                    return {};
                std::vector<unsigned char> buffer(dwDataSize);
                if (::RegQueryValueExW(hKey, itemName.c_str(), nullptr, nullptr, buffer.data(), &dwDataSize) == ERROR_SUCCESS) {
                    result.add(buffer.data(), dwDataSize);
                }
            }
            ::RegCloseKey(hKey); // 关闭注册表键句柄
            return result;
        }

        // 特化几个有效类型
        template<typename Type>
        bool SetRegValueData(Type&& value, DWORD& dwType, DWORD& dwLen, LPBYTE& pData) {
            using ValueType = std::remove_cvref_t<Type>;
            if constexpr (std::is_arithmetic_v<ValueType>)  //数值类型
            {
                DWORD newValue = static_cast<DWORD>(value);
                dwType = REG_DWORD;
                dwLen = sizeof(newValue);
                pData = reinterpret_cast<LPBYTE>(&newValue);
            }
            else if constexpr (std::is_same_v<CXText, ValueType>)
            {
                dwType = REG_SZ;
                dwLen = static_cast<DWORD>(value.size() + 1);
                pData = reinterpret_cast<LPBYTE>(const_cast<wchar_t*>(value.get()));
            }
            else if constexpr (std::is_same_v<CXBytes, ValueType>)
            {
                dwType = REG_BINARY;
                dwLen = static_cast<DWORD>(value.size());
                pData = const_cast<LPBYTE>(value.get());
            }
            else {
                put_errmsg(L"说实话，你易语言里这样用也是错的，回去看看易语言代码没写错吧\r""Unsupported type for registry value.");
                return false;
            }
            return true;
        };

        template<typename T>
        bool SaveRegItem(INT rootDir, const CXText& fullPath, T&& value) {
            auto hRootKey = GetRegRootVal(rootDir);

            if (hRootKey == nullptr || fullPath.empty())
                return false;

            DWORD dwType, dwLen;
            LPBYTE pData;
            bool result{ false };
            if (!SetRegValueData(value, dwType, dwLen, pData))
                return false;

            std::wstring copy{ fullPath };
            size_t lastBackslashPos = copy.find_last_of(L'\\');
            if (lastBackslashPos == std::wstring::npos) {
                return result;
            }
            // 分离路径和项名
            std::wstring path = copy.substr(0, lastBackslashPos);
            std::wstring itemName = copy.substr(lastBackslashPos + 1);

            HKEY hKey;

            if (::RegOpenKeyExW(hRootKey, path.c_str(), 0, KEY_WRITE, &hKey) == ERROR_SUCCESS ||
                ::RegCreateKeyExW(hRootKey, path.c_str(), 0, NULL, 0, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS ||
                ::RegCreateKeyW(hRootKey, path.c_str(), &hKey) == ERROR_SUCCESS) {
                result = ::RegSetValueExW(hKey, itemName.c_str(), 0, dwType, pData, dwLen) == ERROR_SUCCESS;
                ::RegCloseKey(hKey);
            }
            return result;
        }

        fn DeleteRegItem(int rootDir, const CXText& fullPath) ->bool {
            HKEY hRootKey = GetRegRootVal(rootDir);
            if (hRootKey == nullptr || fullPath.empty()) {
                return false;
            }

            std::wstring subkey(fullPath);
            auto pos = subkey.find_last_of(L'\\');
            std::wstring keyname;

            if (pos != std::wstring::npos) {
                keyname = subkey.substr(pos + 1);
                subkey = subkey.substr(0, pos);
            }

            HKEY hKey;
            if (::RegOpenKeyExW(hRootKey, subkey.c_str(), 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
                bool succeeded = keyname.empty() ?
                    (::RegDeleteKeyW(hKey, subkey.c_str()) == ERROR_SUCCESS) :
                    (::RegDeleteValueW(hKey, keyname.c_str()) == ERROR_SUCCESS);
                ::RegCloseKey(hKey);
                return succeeded;
            }

            return ::RegDeleteKeyW(hRootKey, fullPath) == ERROR_SUCCESS;
        }
        fn GetSysColor() {
            return ::GetSysColor(COLOR_BTNFACE);
        }
        fn Beep() { ::MessageBeep(0); };
        namespace _imp {
            class  CursorWait
            {
            public:
                static  auto& GetHandle() {
                    static CursorWait hanlde;
                    return hanlde;
                }
                void Wait() {
                    if (m_hCur == nullptr)
                        m_hCur = ::SetCursor(::LoadCursorW(nullptr, IDC_WAIT));
                }
                void Restroe() {
                    if (m_hCur != nullptr)
                    {
                        ::SetCursor(m_hCur);
                        m_hCur = nullptr;
                    }
                }
            private:
                CursorWait() {};
                ~CursorWait() {//程序结束前回复
                    Restroe();
                };
                HCURSOR m_hCur{ nullptr };
            };
        }
        fn SetWaitCursor() {
            _imp::CursorWait::GetHandle().Wait();
        }
        fn RestroeCursor() {
            _imp::CursorWait::GetHandle().Restroe();
        }


        fn IsRegItemExist(int rootDir, const CXText& fullPath)->bool {
            HKEY hRootKey = GetRegRootVal(rootDir);
            if (hRootKey == nullptr || fullPath.empty()) {
                return false;
            }

            std::wstring subkey(fullPath);
            auto pos = subkey.find_last_of(L'\\');
            std::wstring keyname;
            if (pos != std::wstring::npos) {
                keyname = subkey.substr(pos + 1);
                subkey = subkey.substr(0, pos);
            }

            HKEY hKey;
            if (::RegOpenKeyExW(hRootKey, keyname.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
                DWORD dwType, dwDataSize;
                auto blpExist = (::RegQueryValueExW(hKey, subkey.c_str(), NULL, &dwType, NULL, &dwDataSize) == ERROR_SUCCESS);
                ::RegCloseKey(hKey);
                return blpExist;
            }
            return false;
        }

        fn GetSysVer2() {


            if (IsWindows10OrGreater()) {
                if (IsWindowsServer()) {
                    return 6; // Windows Server 2016 or greater
                }
                return 5; // Windows 10 or greater
            }
            else if (IsWindows8Point1OrGreater()) {
                if (IsWindowsServer()) {
                    return 8; // Windows Server 2012 R2
                }
                return 7; // Windows 8.1
            }
            else if (IsWindows8OrGreater()) {
                if (IsWindowsServer()) {
                    return 10; // Windows Server 2012
                }
                return 9; // Windows 8
            }
            else if (IsWindows7OrGreater()) {
                if (IsWindowsServer()) {
                    return 12; // Windows Server 2008 R2
                }
                return 11; // Windows 7
            }
            else if (IsWindowsVistaOrGreater()) {
                if (IsWindowsServer()) {
                    return 13; // Windows Server 2008
                }
                return 14; // Windows Vista
            }
            else if (IsWindowsXPOrGreater()) {
                return 3; // Windows XP or other NT-based systems
            }
            else {
                return 0; // win9x win32s不用想，不可能的,跑不起来
            }
        }
        fn GetSysVer()->int
        {
            OSVERSIONINFOEXW osvi = {};
            osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
            osvi.dwMajorVersion = 10;
            osvi.dwMinorVersion = 0;

            DWORDLONG dwlConditionMask = VerSetConditionMask(
                VerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL),
                VER_MINORVERSION, VER_GREATER_EQUAL);

            if (VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION, dwlConditionMask))
            {
                return 3; // Windows NT 及更高版本（例如 Windows 10）
            }
            //用炫语言已经没办法支持鼓噪版本了
            return 0; // 无法确定系统版本
        }
        fn GetSectionText(const CXText& configFile, const CXText& sectionName, const CXText& itemName, const CXText& defaultString = L"")->CXText {
            if (configFile.empty() && sectionName.empty() && itemName.empty())
                return{};

            std::vector<wchar_t> buffer(10240);
            DWORD nLen{ 0 };
            CXText ret{};
            while (true) {
                nLen = GetPrivateProfileStringW(sectionName, itemName, defaultString, buffer.data(), static_cast<int>(buffer.size()), configFile);
                if (nLen < static_cast<DWORD>(buffer.size()) - 1) {
                    break;
                }
                buffer.resize(buffer.size() * 2);
            }
            if (nLen > 0)
                ret.append2(buffer.data(), nLen);
            return ret;
        }
        fn SetSectionText(const CXText& configFile, const CXText& sectionName, const CXText& itemName, const CXText& defaultString )->bool {
           return WritePrivateProfileStringW(sectionName, itemName, defaultString, configFile)==TRUE;
        }
        fn  GetSectionNames(const CXText& configFile)->StrArray {
            std::vector<wchar_t> buffer(2048); // 初始缓冲区大小
            DWORD nRet{ 0 };

            while (true) {
                nRet = GetPrivateProfileSectionNamesW(buffer.data(), static_cast<DWORD>(buffer.size()), configFile);

                // 如果缓冲区足够，则退出循环
                if (nRet < static_cast<DWORD>(buffer.size()) - 2) {
                    break;
                }

                // 缓冲区不够大，扩大缓冲区
                buffer.resize(buffer.size() * 2);
            }

            StrArray sectionNames;
            if (nRet > 0) {
                const wchar_t* pText = buffer.data();
                const wchar_t* pEnd = pText + nRet;

                while (*pText != L'\0' && pText < pEnd) {
                    sectionNames.add(pText);
                    pText += wcslen(pText) + 1;
                }
            }

            return sectionNames;
        }

        template<typename Type>
        int MsgBox(Type&& Prompt, DWORD CommandButton = MB_OK, const std::optional<const CXText>& Caption = std::nullopt, HWND hParent = nullptr) {
            return MessageBoxW(hParent, krnln::helper::to_string(Prompt), Caption.value_or(L"信息"), CommandButton) - 1;//真优雅
        }
        template <typename T1, typename T2>
        void stdswap(T1&& a, T2&& b) {
            //走到这就断
            static_assert(!std::is_same_v<std::decay_t<T1>, std::decay_t<T2>>,
                "[来自易语言支持库编译期的提示]交换常量?我在想你单纯的测试支持库");
            static_assert(std::is_same_v<std::decay_t<T1>, std::decay_t<T2>>,
                "[来自易语言支持库编译期的提示]交换常量?我在想你单纯的测试支持库");
        }

        template <typename T1, typename T2>
        void stdswap(T1& a, T2& b) {
            
            static_assert(std::is_same_v<std::decay_t<T1>, std::decay_t<T2>>,
                "[来自易语言支持库编译期的提示]难以置信,交换两个不搭噶的变量？");

           
            static_assert(!std::is_pointer_v<std::decay_t<T1>> && !std::is_pointer_v<std::decay_t<T2>>,
                "[来自易语言支持库编译期的提示]说实话,交换指针类型的变量并不是很安全。我不希望你这样操作!");

            std::swap(std::forward<std::decay_t<T1>&>(a), std::forward<std::decay_t<T1>&>(b));
        }
        template <typename T1, typename T2>
        void swap(T1& a, T2& b) {
            T1 temp{ a };
            a = *reinterpret_cast<T1*>(&b);
            b = *reinterpret_cast<T2*>(&temp);
        }
    }

    namespace  envaccess {
        fn get_current_path() {
            return std::filesystem::current_path().wstring();
        }

        fn get_env(const CXText& env_name)->CXText {
            WCHAR buffer[MAX_PATH]{};
            const auto nRet = GetEnvironmentVariableW(env_name.get(), buffer, MAX_PATH);
            if (nRet > MAX_PATH) {//缓冲区不足,动态申请
                std::vector<WCHAR> ret(nRet);
                GetEnvironmentVariableW(env_name.get(), const_cast<LPWSTR>(ret.data()), nRet);
                return  ret.data();
            }

            return buffer;
        }

    }
    namespace datetime {



        // 常量定义
        constexpr int MIN_YEAR = 100;
        constexpr int MAX_YEAR = 9999;
        constexpr int MIN_MONTH = 1;
        constexpr int MAX_MONTH = 12;
        constexpr int MIN_DAY = 1;
        constexpr int MAX_DAY = 31;
        constexpr int MIN_HOUR = 0;
        constexpr int MAX_HOUR = 23;
        constexpr int MIN_MINUTE = 0;
        constexpr int MAX_MINUTE = 59;
        constexpr int MIN_SECOND = 0;
        constexpr int MAX_SECOND = 60;
        constexpr double MAX_DAYS_SPAN = 3615897.0;

        inline bool isLeapYear(int year) {
            return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        }

        //------------------------注意此下三个代码的区别-------------------------
        inline int GetDaysOfMonth(int year, int month) {
            static const int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

            if (year < MIN_YEAR || year > MAX_YEAR || month < MIN_MONTH || month > MAX_MONTH)
                return 0;

            int days = daysInMonth[month - 1];
            if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
                days = 29; // Leap year
            }
            return days;
        }
        inline int GetculateDayOfYear(int year, int month, int day) {
            int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

            if (isLeapYear(year)) {
                daysInMonth[1] = 29; // 闰年2月29天
            }

            int dayOfYear = 0;
            for (int i = 0; i < month - 1; ++i) {
                dayOfYear += daysInMonth[i];
            }
            dayOfYear += day;

            return dayOfYear - 1; // 0-based
        }
        inline int GetculateWeekDay(int year, int month, int day) {
            // 1900年1月1日是星期一
            int days = 0;
            for (int y = 1900; y < year; ++y) {
                days += isLeapYear(y) ? 366 : 365;
            }
            days += GetculateDayOfYear(year, month, day);

            // 计算相对于星期一（1900年1月1日）的偏移量
            return (days + 1) % 7; // 1 represents Monday
        }
        //-------------------------------------------------
        inline EPLDATATIME makeRealTime(EPLDATATIME stime) {
            auto year = std::clamp(stime.tm_year + 1900, MIN_YEAR, MAX_YEAR);
            auto month = std::clamp(stime.tm_mon + 1, MIN_MONTH, MAX_MONTH);
            auto day = std::clamp(stime.tm_mday, MIN_DAY, GetDaysOfMonth(year, month));
            auto hour = std::clamp(stime.tm_hour, MIN_HOUR, MAX_HOUR);
            auto minute = std::clamp(stime.tm_min, MIN_MINUTE, MAX_MINUTE);
            auto second = std::clamp(stime.tm_sec, MIN_SECOND, MAX_SECOND);

            std::tm dateTime{};
            dateTime.tm_year = static_cast<WORD>(year) - 1900;
            dateTime.tm_mon = static_cast<WORD>(month) - 1;
            dateTime.tm_mday = static_cast<WORD>(day);
            dateTime.tm_hour = static_cast<WORD>(hour);
            dateTime.tm_min = static_cast<WORD>(minute);
            dateTime.tm_sec = static_cast<WORD>(second);
            dateTime.tm_isdst = -1;

            if (dateTime.tm_year > 70) {
                auto temp = std::mktime(reinterpret_cast<std::tm*>(&dateTime));
                if (temp == -1) {
                    put_errmsg(std::format(L"发生了难以置信的错误,规范化时间无法规范化时间，传入的时间为{}年{}月{}日{}时{}分{}秒",
                        dateTime.tm_year,
                        dateTime.tm_mon,
                        dateTime.tm_mday,
                        dateTime.tm_hour,
                        dateTime.tm_min,
                        dateTime.tm_sec));
                    return {};
                }
                std::tm now{};
                gmtime_s(&now, &temp);
                return *reinterpret_cast<EPLDATATIME*>(&now);
            }
            else {
                // 处理1970年之前的日期
                stime.tm_yday = GetculateDayOfYear(year, month, day);
                stime.tm_wday = GetculateWeekDay(year, month, day);
                return stime;
            }
        }

        inline EPLDATATIME makeRealTime(int year, int month = 1, int day = 1, int hour = 0, int minute = 0, int second = 0) {


            year = std::clamp(year, MIN_YEAR, MAX_YEAR);
            month = std::clamp(month, MIN_MONTH, MAX_MONTH);
            day = std::clamp(day, MIN_DAY, GetDaysOfMonth(year, month));
            hour = std::clamp(hour, MIN_HOUR, MAX_HOUR);
            minute = std::clamp(minute, MIN_MINUTE, MAX_MINUTE);
            second = std::clamp(second, MIN_SECOND, MAX_SECOND);

            EPLDATATIME dateTime{};
            dateTime.tm_year = static_cast<WORD>(year) - 1900;
            dateTime.tm_mon = static_cast<WORD>(month) - 1;
            dateTime.tm_mday = static_cast<WORD>(day);
            dateTime.tm_hour = static_cast<WORD>(hour);
            dateTime.tm_min = static_cast<WORD>(minute);
            dateTime.tm_sec = static_cast<WORD>(second);

            return makeRealTime(dateTime);
        }

        inline double ToDate(int year, int month, int day, int hour, int minute, int second, double failedValue) {
            year = std::clamp(year, MIN_YEAR, MAX_YEAR);
            month = std::clamp(month, MIN_MONTH, MAX_MONTH);
            day = std::clamp(day, MIN_DAY, GetDaysOfMonth(year, month));
            hour = std::clamp(hour, MIN_HOUR, MAX_HOUR);
            minute = std::clamp(minute, MIN_MINUTE, MAX_MINUTE);
            second = std::clamp(second, MIN_SECOND, MAX_SECOND);

            SYSTEMTIME st = { 0 };
            st.wYear = static_cast<WORD>(year);
            st.wMonth = static_cast<WORD>(month);
            st.wDay = static_cast<WORD>(day);
            st.wHour = static_cast<WORD>(hour);
            st.wMinute = static_cast<WORD>(minute);
            st.wSecond = static_cast<WORD>(second);

            double date;
            return (::SystemTimeToVariantTime(&st, &date) == FALSE) ? failedValue : date;
        }

        inline double ClipToRange(double value, double min, double max) {
            return (std::max)(min, (std::min)(value, max));
        }

        inline double GetDateTimeSpan(int days, int hours, int minutes, int seconds, int64_t milliseconds) {
            double span = days + hours / 24.0 + minutes / (24.0 * 60) + seconds / (24.0 * 60 * 60) +
                milliseconds / (24.0 * 60 * 60 * 1000.0);
            return ClipToRange(span, -MAX_DAYS_SPAN, MAX_DAYS_SPAN);
        }

        inline  EPLDATATIME AdjustDateTime(EPLDATATIME dateTime, int timeField, long long addValue) {
            switch (timeField) {
            case 1: //年
                dateTime.tm_year += static_cast<int>(addValue);
                break;
            case 2: //季度
                addValue *= 3;
            case 3: //月
                dateTime.tm_mon += static_cast<int>(addValue);
                while (dateTime.tm_mon < 0) {
                    dateTime.tm_mon += 12;
                    dateTime.tm_year--;
                }
                while (dateTime.tm_mon > 11) {
                    dateTime.tm_mon -= 12;
                    dateTime.tm_year++;
                }
                break;
            case 4: // Week
                addValue *= 7;
            case 5: // Day
            case 6: // Hour
            case 7: // Minute
            case 8: // Second
                auto tempDate = ToDate(dateTime.tm_year + 1900, dateTime.tm_mon + 1, dateTime.tm_mday,
                    dateTime.tm_hour, dateTime.tm_min, dateTime.tm_sec, 0);
                tempDate += (addValue > 0 ? GetDateTimeSpan(static_cast<int>(addValue), 0, 0, 0, 0) :
                    -GetDateTimeSpan(static_cast<int>(-addValue), 0, 0, 0, 0));
                SYSTEMTIME st = { 0 };
                if (::VariantTimeToSystemTime(tempDate, &st) == FALSE)
                    return dateTime;

                dateTime.tm_year = st.wYear - 1900;
                dateTime.tm_mon = st.wMonth - 1;
                dateTime.tm_mday = st.wDay;
                dateTime.tm_hour = st.wHour;
                dateTime.tm_min = st.wMinute;
                dateTime.tm_sec = st.wSecond;
                break;
            }
            return dateTime;
        }

        // 日期时间字符串转换函数

        inline CXText TimeToText(const EPLDATATIME& dateTime, int convertPart = 1, bool cnFormat = true) {
            std::wostringstream oss;
            int year = dateTime.tm_year + 1900;
            int month = dateTime.tm_mon + 1;
            int day = dateTime.tm_mday;
            int hour = dateTime.tm_hour;
            int minute = dateTime.tm_min;
            int second = dateTime.tm_sec;

            if (cnFormat) {
                if (convertPart != 3) {
                    oss << year << L"年" << month << L"月" << day << L"日";
                }
                if (convertPart != 2) {
                    if (second != 0 || oss.str().empty()) {
                        oss << hour << L"时" << minute << L"分" << second << L"秒";
                    }
                    else if (minute != 0) {
                        oss << hour << L"时" << minute << L"分";
                    }
                    else if (hour != 0) {
                        oss << hour << L"时";
                    }
                }
            }
            else {
                if (convertPart != 3) {
                    oss << month << L"/" << day << L"/" << year;
                }
                if (convertPart != 2) {
                    if (second != 0) {
                        oss << (convertPart == 0 ? L" " : L"") << hour << L":" << minute << L":" << second;
                    }
                    else if (minute != 0) {
                        oss << (convertPart == 0 ? L" " : L"") << hour << L":" << minute;
                    }
                    else if (hour != 0) {
                        oss << (convertPart == 0 ? L" " : L"") << hour;
                    }
                }
            }
            return oss.str();
        }

        inline EPLDATATIME GetCurrentDateTime() {
            SYSTEMTIME st;
            ::GetLocalTime(&st);
            EPLDATATIME localTime = {};
            localTime.tm_year = st.wYear - 1900;
            localTime.tm_mon = st.wMonth - 1;
            localTime.tm_mday = st.wDay;
            localTime.tm_hour = st.wHour;
            localTime.tm_min = st.wMinute;
            localTime.tm_sec = st.wSecond;
            return makeRealTime(localTime);
        }

        inline EPLDATATIME TimeChg(EPLDATATIME dateTime, int timeField, long long addValue) {
            auto adjustedTime = AdjustDateTime(dateTime, timeField, addValue);
            adjustedTime.tm_year = std::clamp(adjustedTime.tm_year, -1800, 8099);
            return adjustedTime;
        }


        inline EPLDATATIME ToTime(const CXText& szDateTimeText) {
            if (szDateTimeText.empty()) {
                EPLDATATIME nulltm{};
                nulltm.tm_year = -1800;
                return nulltm;
            }

            const wchar_t* ps = szDateTimeText.get();
            int npYear = 0, npMonth = 0, npDay = 0;
            int npHour = 0, npMinute = 0, npSecond = 0;

            auto parseInt = [&](int& value, int maxDigits) {
                for (int npIndex = 0; npIndex < maxDigits; ++npIndex) {
                    wchar_t ch = *ps;
                    if (ch == 0 || ch < L'0' || ch > L'9') break;
                    ps++;
                    value = value * 10 + (ch - L'0');
                }
                };
            auto skipSeparators = [&](std::wstring_view separators) {
                if (separators.find(*ps) != std::wstring_view::npos) {
                    ps++;
                }
                };


            parseInt(npYear, 4);
            skipSeparators(L"/-:.年月日时分");
            parseInt(npMonth, 2);
            skipSeparators(L"/-:.月");
            parseInt(npDay, 2);
            skipSeparators(L"/-:.日 ");
            parseInt(npHour, 2);
            skipSeparators(L"/-:.时");
            parseInt(npMinute, 2);
            skipSeparators(L"/-:.分");
            parseInt(npSecond, 2);

            if (*ps != 0 && *ps != L'秒') {
                EPLDATATIME nulltm;
                nulltm.tm_year = -1800;
                return nulltm;
            }

            return makeRealTime(npYear, npMonth, npDay, npHour, npMinute, npSecond);
        }
        // 计算两个时间之间的秒数
        inline double secondsBetween(const EPLDATATIME& time1, const EPLDATATIME& time2) {
            auto copy1{ time1 }, copy2{ time2 };

            return std::difftime(std::mktime(reinterpret_cast<std::tm*>(&copy1)), std::mktime(reinterpret_cast<std::tm*>(&copy2)));
        }

        // 计算两个时间之间的年份
        inline int yearsBetween(const EPLDATATIME& time1, const EPLDATATIME& time2) {
            // 检查日期是否合法
            if (time1.tm_mon < 1 || time1.tm_mon > 12 ||
                time1.tm_mday < 1 || time1.tm_mday > 31 ||
                time2.tm_mon < 1 || time2.tm_mon > 12 ||
                time2.tm_mday < 1 || time2.tm_mday > 31) {
                return 0; // 返回0
            }
            const int START_YEAR = 1900;
            int ygap = 0;
            if (time1.tm_year > time2.tm_year) {
                // 计算 time1 到 time2 的年数差
                ygap = time1.tm_year - time2.tm_year;

                //// 计算 time1 到 time2 的天数差
                //int days1 = 0;
                //for (int i = time2.tm_year; i < time1.tm_year; i++) {
                //    if (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0)) {
                //        // 闰年
                //        days1 += 366;
                //    }
                //    else {
                //        // 平年
                //        days1 += 365;
                //    }
                //}
                //days1 += time1.tm_yday - time2.tm_yday;

                //// 如果天数差小于一年，则减少一年
                //if (days1 < 365) {
                //    ygap--;
                //}
            }
            else if (time1.tm_year < time2.tm_year) {
                // 计算 time2 到 time1 的年数差
                ygap = time2.tm_year - time1.tm_year;

                //// 计算 time2 到 time1 的天数差
                //int days2 = 0;
                //for (int i = time1.tm_year; i < time2.tm_year; i++) {
                //    if (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0)) {
                //        // 闰年
                //        days2 += 366;
                //    }
                //    else {
                //        // 平年
                //        days2 += 365;
                //    }
                //}
                //days2 += time2.tm_yday - time1.tm_yday;
                //// 如果天数差小于一年，则减少一年
                //if (days2 < 365) {
                //    ygap--;
                //}
            }

            return ygap;
        }

        // 计算两个时间之间的季度
        inline double quartersBetween(const EPLDATATIME& time1, const EPLDATATIME& time2) {
            int gap = 12 * (time1.tm_year - time2.tm_year) + time1.tm_mon - time2.tm_mon;
            return std::ceil(gap / 3.0);
        }

        // 计算两个时间之间的月份
        inline int monthsBetween(const EPLDATATIME& time1, const EPLDATATIME& time2) {
            int gap = 12 * (time1.tm_year - time2.tm_year) + time1.tm_mon - time2.tm_mon;

            //// 判断时间差距是否足一个月份
            //if (time1.tm_mday < time2.tm_mday) {
            //    gap--;
            //}
            return gap;
        }

        // 计算两个时间之间的周数
        inline double weeksBetween(const EPLDATATIME& time1, const EPLDATATIME& time2) {
            double seconds = secondsBetween(time1, time2);
            puts(std::to_string(seconds / (604800)).c_str());
            return std::floor(seconds / (604800));
        }

        // 计算两个时间之间的天数
        inline double daysBetween(const EPLDATATIME& time1, const EPLDATATIME& time2) {
            double seconds = secondsBetween(time1, time2);
            return seconds / 86400.0;
        }

        // 计算两个时间之间的小时数
        inline  double hoursBetween(const EPLDATATIME& time1, const EPLDATATIME& time2) {
            double seconds = secondsBetween(time1, time2);
            return seconds / 3600.0;
        }

        // 计算两个时间之间的分钟数
        inline double minutesBetween(const EPLDATATIME& time1, const EPLDATATIME& time2) {
            double seconds = secondsBetween(time1, time2);
            return seconds / 60.0;
        }


        // 计算两个时间之间的间隔
        inline  double TimeDiff(const EPLDATATIME& time1, const EPLDATATIME& time2, int interval) {
            switch (interval) {
            case 1: return yearsBetween(time1, time2);
            case 2: return quartersBetween(time1, time2);
            case 3: return monthsBetween(time1, time2);
            case 4: return weeksBetween(time1, time2);
            case 5: return daysBetween(time1, time2);
            case 6: return hoursBetween(time1, time2);
            case 7: return minutesBetween(time1, time2);
            default: return secondsBetween(time1, time2);//其余情况默认返回秒数
            }
        }

        inline int TimePart(const EPLDATATIME& _time, int type) {
            const auto time{ makeRealTime(_time) };
            int ret = 0;
            switch (type) {
            case 1: // 年份
                ret = time.tm_year + 1900; // tm_year 存储的是年份减去 1900 的值
                break;
            case 2: // 季度
                //OutputDebugStringA(std::to_string((time.tm_mon + 1 / 3.0)).c_str());
                ret = static_cast<int>(std::ceil((time.tm_mon + 1) / 3.0));// tm_mon 存储的是月份减去 1 的值
                break;
            case 3: // 月份
                ret = time.tm_mon + 1; // tm_mon 存储的是月份减去 1 的值
                break;
            case 4: // 自年首周数
                ret = static_cast<int>(std::ceil(time.tm_yday / 7.0)); // tm_yday 存储的是当前日期是从一年开始的第几天
                break;
            case 5: // 日
                ret = time.tm_mday;
                break;
            case 6: // 小时
                ret = time.tm_hour;
                break;
            case 7: // 分钟
                ret = time.tm_min;
                break;
            case 8: // 秒
                ret = time.tm_sec;
                break;
            case 9: // 星期几
                ret = time.tm_wday + 1; // tm_wday 存储的是星期几减去 1 的值
                break;
            case 10: // 自年首天数
                ret = time.tm_yday + 1; // tm_yday 存储的是当前日期是从一年开始的第几天
                break;
            }
            return ret;
        }
        inline int GetYear(const EPLDATATIME& time) {
            return std::clamp(time.tm_year + 1900, MIN_YEAR, MAX_YEAR);
        }
        inline int GetMoon(const EPLDATATIME& time) {
            return std::clamp(time.tm_mon + 1, 1, 12);
        }
        inline int GetDay(const EPLDATATIME& time) {
            return std::clamp(time.tm_mday, MIN_DAY, GetDaysOfMonth(std::clamp(time.tm_year + 1900, MIN_YEAR, MAX_YEAR), time.tm_mday));;
        }
        inline int GetWeakDay(const EPLDATATIME& time) {
            return std::clamp(time.tm_hour, MIN_HOUR, MAX_HOUR);
        }
        inline int GetHour(const EPLDATATIME& time) {
            return std::clamp(time.tm_wday + 1, 1, 7);
        }
        inline int GetMinute(const EPLDATATIME& time) {
            return std::clamp(time.tm_min, MIN_MINUTE, MAX_MINUTE);
        }
        inline int GetSec(const EPLDATATIME& time) {
            return  std::clamp(time.tm_sec, MIN_SECOND, MAX_SECOND);
        }


        inline bool SetSysTime(const EPLDATATIME& tm)
        {
            SYSTEMTIME now = { 0 };
            now.wYear = tm.tm_year + 1900;
            now.wMonth = tm.tm_mon + 1;
            now.wDay = tm.tm_mday;
            now.wHour = tm.tm_hour;
            now.wMinute = tm.tm_min;
            now.wSecond = tm.tm_sec;
            now.wMilliseconds = 0;
            return SetLocalTime(&now);
        }

        inline EPLDATATIME GetDatePart(EPLDATATIME tm) {
            tm.tm_hour = 0;
            tm.tm_min = 0;
            tm.tm_sec = 0;
            return tm;
        }
        inline EPLDATATIME GetTimePart(EPLDATATIME tm) {
            tm.tm_year = 100;
            tm.tm_mon = 0;
            tm.tm_mday = 1;
            return tm;
        }
    }
}




//@隐藏}








//@分组{ 算术运算
/*@声明
//@备注 将指定数值每一个比特位的值取反后返回。
//@别名  位取反(数)
数值类型  krnln::math::bnot(数值类型&& t);
//@备注  如两个数值有某共同比特位为1，则返回值的对应位也为1，否则为0。返回计算后的结果。
//@参数  位运算数值一
//@参数  位运算数值二
//@别名    位与(位运算数值一，位运算数值二、、、)
T krnln::math::band (...);
//@别名    位或(位运算数值一，位运算数值二、、、)
T krnln::math::bor (...);
//@别名    位异或(位运算数值一，位运算数值二、、、)
T krnln::math::bxor (...);
//@别名    左移(欲移动的整数，欲移动的位数)
auto krnln::math::shl (...);
//@别名    右移(欲移动的整数，欲移动的位数)
auto krnln::math::shr (...);
//@别名    合并整数()
int krnln::math::merge_numerical (short a,short b);
//@别名    求次方()
T krnln::math::pow (数值类型 欲求次方数值,数值类型 次方数);
*/
//@分组}








//@分组{ 文本操作
/*@声明
//@备注 取文本型数据的长度，不包含结束0。
//@参数 参数值指定欲检查其长度的文本数据。
//@别名 取文本长度(文本数据)
size_t  krnln::str::wcslen(const CXText& str);
//@备注  返回一个文本，其中包含指定文本中从左边算起指定数量的字符。
//@参数  欲取其部分的文本
//@参数  欲取出字符的数目
//@别名  取文本左边(欲取其部分的文本,欲取出字符的数目)
CXText krnln::str::leftstr(const CXText& str,size_t count);
//@备注 返回一个文本，其中包含指定文本中从右边算起指定数量的字符。
//@别名 取文本右边(欲取其部分的文本,欲取出字符的数目)
CXText  krnln::str::rightstr(const CXText& str,size_t count);
//@备注 返回一个文本，其中包含指定文本中从指定位置算起指定数量的字符。
//@参数  欲取其部分的文本
//@参数  起始取出位置,索引从1开始
//@参数  起欲取出字符的数目
//@别名  取文本中间(欲取其部分的文本, 起始取出位置, 欲取出字符的数目)
CXText  krnln::str::substr(const CXText& str, size_t pos1, size_t count);
//@备注  返回一个文本，其中包含有与指定字符代码相关的字符。
//@别名  字符(欲取其字符的字符代码)
CXText  krnln::str::chr(wchar_t 欲取其字符的字符代码);
//@备注  返回文本中指定位置处字符的代码。如果指定位置超出文本长度，返回0。
//@参数  欲取其部分的文本
//@参数  起始取出位置,索引从1开始
//@别名  取代码(欲取其部分的文本,  欲取出字符的索引)
CXText  krnln::str::unic(const  CXText& str, size_t pos );
//@备注   返回一个整数值，指定一文本在另一文本中最先出现的位置，位置值从 1 开始。如果未找到，返回-1。
//@参数 被搜寻的文本
//@参数 欲寻找的文本
//@参数 起始搜寻位置 可以被省略。位置值从 1 开始。如果本参数被省略，默认为 1 。
//@参数 是否不区分大小写，初始值为“假”。为真不区分大小写，为假区分。
//@别名 寻找文本(被搜寻的文本, 欲寻找的文本, 起始搜寻位置, 是否不区分大小写)
ptrdiff_t  krnln::str::findstr(const  CXText& pText, const  CXText& pSubStr, size_t pos=1, bool dx=true);
//@备注   返回一个整数值，指定一文本在另一文本中最先出现的位置，位置值从 1 开始。如果未找到，返回-1。
//@参数 被搜寻的文本
//@参数 欲寻找的文本
//@参数 位置值从 1 开始。如果本参数被省略，默认为从被搜寻文本的尾部开始。
//@参数 是否不区分大小写，初始值为“假”。为真不区分大小写，为假区分。
//@别名 倒找文本(被搜寻的文本, 欲寻找的文本, 起始搜寻位置, 是否不区分大小写)
ptrdiff_t  krnln::str::rfindstr(const  CXText& pText, const  CXText& pSubStr, size_t pos=空参数, bool dx=true);
//@备注  将文本中的小写英文字母变换为大写，返回变换后的结果文本。
//@别名  到大写(欲变换的文本)
CXText  krnln::str::upcase(const  CXText& pText);
//@备注  将文本中的大写英文字母变换为小写，返回变换后的结果文本。
//@别名  到小写(欲变换的文本)
CXText  krnln::str::lowcase(const  CXText& pText);
//@备注  返回一个文本，代表指定数值、逻辑值或日期时间被转换后的结果。如果为文本数据，将被直接返回。
//@别名  到文本(欲转为文本的数据)
CXText krnln::help::to_string(any 欲转为文本的数据);
//@备注 返回一个文本，其中包含被删除了首部全角或半角空格或制表符的指定文本。
//@别名 删首空(欲删除空格的文本)
CXText krnln::str::lefttrim(const  CXText& pText);
//@备注 返回一个文本，其中包含被删除了尾部全角或半角空格格或制表符的指定文本。
//@别名 删尾空(欲删除空格的文本)
CXText krnln::str::righttrim(const  CXText& pText);
//@备注 返回一个文本，其中包含被删除了首部及尾部全角或半角空格的指定文本。
//@别名  删首尾空(欲删除空格的文本)
CXText krnln::str::lrtrim(const  CXText& pText);
//@备注  返回一个文本，其中包含被删除了所有全角或半角空格的指定文本。
//@别名  删全部空(欲删除空格的文本)
CXText krnln::str::alltrim(const  CXText& pText);
//@备注  将指定文本的某一部分用其它的文本替换。
//@参数
//@参数  替换的起始位置，1为首位置，2为第2个位置，如此类推。
//@参数
//@参数  可以被省略。如果本参数被省略，则删除文本中的指定部分。
//@别名  文本替换(欲被替换的文本, 起始替换位置, 替换长度, 用作替换的文本)
CXText krnln::str::replace(const  CXText& pText,size_t off,size_t lenth,const  CXText&  pstr=L"");
//@备注  返回一个文本，该文本中指定的子文本已被替换成另一子文本，并且替换发生的次数也是被指定的。
//@参数
//@参数
//@参数  可以被省略。如果本参数被省略，默认为空文本。
//@参数  可以被省略。参数值指定被替换子文本的起始搜索位置。如果省略，默认从 1 开始。
//@参数  可以被省略。参数值指定对子文本进行替换的次数。如果省略，默认进行所有可能的替换。
//@参数  初始值为“真”。为真区分大小写，为假不区分。
//@别名  子文本替换(欲被替换的文本, 欲被替换的子文本, 用作替换的子文本, 进行替换的起始位置, 替换进行的次数, 是否区分大小写)
CXText krnln::str::subreplace(const  CXText& pText,const  CXText& pSubText,const  CXText& pReplaceText=空参数,size_t off=空参数,size_t count=空参数,bool dx =true);
//@备注  将文本中的半角字母、空格或数字变换为全角，返回变换后的结果文本。
//@别名  到全角(欲变换的文本)
CXText	krnln::str::tofull(const  CXText& pText);
//@备注  将文本中的全角字母、空格或数字变换为半角，返回变换后的结果文本。
//@别名  到半角(欲变换的文本)
CXText krnln::str::tohalf(const  CXText& pText);
//@备注 返回具有指定数目半角空格的文本。
//@别名  取空白文本(大小);
CXText  krnln::str::space_str(size_t count);
//@备注  返回一个文本，其中包含指定次数的文本重复结果。
//@参数
//@参数  该文本将用于建立返回的文本。如果为空，将返回一个空文本。
//@别名  取重复文本(重复次数, 待重复文本)
CXText  krnln::str::string_str(size_t count,const  CXText& pText);
//@备注  如果返回值小于0，表示文本一小于文本二；如果等于0，表示文本一等于文本二；如果大于0，表示文本一大于文本二。如果比较时区分大小写，也可以使用比较运算符进行同样的操作。
//@参数
//@参数
//@参数  初始值为“真”。为真区分大小写，为假不区分。
//@别名  文本比较 (待比较文本一, 待比较文本二, 是否区分大小写)
int krnln::str::strcomp(const  CXText& str1, const  CXText& str2, bool case_insensitive);

//@备注  将指定文本进行分割，返回分割后的一维文本数组。
//@参数  如果参数值是一个长度为零的文本，则返回一个空数组，即没有任何成员的数组。
//@参数  可以被省略。参数值用于标识子文本边界。如果被省略，则默认使用半角逗号字符作为分隔符。如果是一个长度为零的文本，则返回的数组仅包含一个成员，即完整的“待分割文本”。
//@参数  可以被省略。如果被省略，则默认返回所有的子文本。
//@别名  分割文本(待分割文本, 用作分割的文本, 要返回的子文本数目)
StrArray krnln::str::split(const  CXText& pText, const  std::optional<CXText>& pSplit=空参数, std::optional<int> count=空参数);

*/
//@分组}





//@分组{ 拼音处理
/*@声明
//@备注  返回包含指定汉字所有拼音编码的文本数组（支持多音字）。
//@参数  只取用文本首部的第一个汉字，如果该文本首部不为汉字，命令将返回一个成员数目为0的空文本数组。
//@别名  取所有发音  (欲取其拼音的汉字)
StrArray  eplpinyin::XCGetAllPinyin(const CXText& ch);

//@备注  返回包含指定汉字指定拼音编码的声母部分文本。如果指定拼音编码不存在或该汉字此发音无声母，将返回空文本。
//@参数  只取用文本首部的第一个汉字
//@参数  应该在 1 到该汉字的发音数目之间。汉字的发音数目可以使用“取发音数目”命令取得。
//@别名  取声母  (欲取其拼音的汉字,欲取拼音编码的索引)
CXText eplpinyin::XCGetSm(const CXText& ch,int index=1);

//@备注  返回包含指定汉字指定拼音编码的韵母部分文本。如果指定拼音编码不存在或该汉字此发音无声母，将返回空文本。
//@参数  只取用文本首部的第一个汉字
//@别名  取韵母  (欲取其拼音的汉字,欲取拼音编码的索引)
CXText eplpinyin::XCGetYm(const CXText& str, int index=1);

//@备注  返回指定汉字的发音数目。
//@参数  只取用文本首部的第一个汉字
//@参数  应该在 1 到该汉字的发音数目之间。汉字的发音数目可以使用“取发音数目”命令取得。
//@别名  取发音数目  (欲取其发音数目的汉字)
CXText eplpinyin::XCGetPinyinCount(const CXText& str);

//@备注  返回包含指定汉字的指定拼音编码的文本。如果该指定拼音编码不存在，将返回空文本。目前仅支持国标汉字。多音字的第一个发音为常用音。
//@参数  只取用文本首部的第一个汉字
//@别名  取拼音  (欲取其拼音的汉字,欲取拼音编码的索引)
CXText eplpinyin::XCGetPinyin(const CXText& str, int index=1);

//@备注  比较两段文本的发音，如果发音相同返回真，否则返回假。对于文本中的非汉字部分，将仅进行简单的值比较。
//@参数
//@参数
//@参数  本参数为真时，当待比较文本一的发音在待比较文本二的首部被包容时即认为比较通过。如果被省略，默认值为假。
//@别名  发音比较  (待比较文本一,待比较文本二,是否为模糊比较)
bool     krnln::pinyin::comp_pinyin(const CXText& str1, const CXText& str2, bool  IsFuzzy = false);


//@备注  比较两段文本的发音，如果发音相同返回真，否则返回假。对于文本中的非汉字部分，将仅进行简单的值比较。
//@参数  系统自动判别该输入字具体是首拼方式还是全拼方式,非拼音部分按照英文大小写同音,全角数字；如：“jsjA”可以匹配“计算机a”“计算机A”,“jsj”可以匹配“计算机”“jisuanji”也可以匹配“计算机”“j算j1”也可以匹配“计算机1”“jsj1”匹配“计算机1”。
//@别名  输入字比较  (待比较拼音输入字,待比较普通文本)
bool  krnln::pinyin::comp_text(const CXText& a1, const CXText& a2);
*/
//@分组}





//@分组{ 环境存取
/*@声明
//@备注  它关连于一个操作系统环境变量。成功时返回所取得的值，失败则返回空文本。本命令为初级命令。
//@参数
//@别名  读环境变量();
CXText krnln::envaccess::get_env(const CXText& 环境变量名称) ;


//@备注  修改或建立指定的操作系统环境变量。成功返回真，失败返回假。本命令为初级命令。
//@参数
//@参数
//@别名  写环境变量(环境变量名称,欲写入内容);
bool SetEnvironmentVariableW(const CXText& ,const CXText& ) ;

*/
//@分组}

//@分组{时间操作
/*@声明

//@备注  日期时间接口
//@别名  日期时间型
typedef krnln::datetime::EPLDATATIME EPLKRNLNDATATIME_T;


//@备注 将指定文本转换为时间并返回。如果给定文本不符合书写格式要求或者时间值错误导致不能进行转换，将返回100年1月1日。如 果给定参数本身就是时间数据，将直接返回该时间
//@参数 文本内容应按以下格式之一提供，年份后的时间部分可以省略：1、1973年11月15日12时30分25秒 2、1973/11/15 12:30:25 3、1973/11/15/12/30/25 4、1973/11/15/12:30:25 5、1973-11-15-12-30-25 6、1973-11-15-12:30:25 7、1973.11.15 12:30:25 8、19731115123025
//@别名 到时间(欲转换的文本);
EPLKRNLNDATATIME_T  krnln::datetime::ToTime(const CXText& szDateTimeText);


//@备注 返回一个时间，这一时间被加上或减去了一段间隔。如果改变后的时间无效，将自动靠近最近的有效时间
//@参数 时间
//@参数 被增加部分 参数值指定增加或减少时间的哪一部分，可以为以下常量： 1、#年份； 2、#季度； 3、#月份； 4、#周； 5、#日； 6、#小时； 7、#分钟； 8、#秒
//@参数 增加值 相对于被增加部分的增加或减少数值
//@别名 增减时间(时间,被增加部分,增加值);
EPLKRNLNDATATIME_T krnln::datetime::TimeChg(EPLKRNLNDATATIME_T dateTime, int timeField, long long addValue) ;

//@备注 返回一个数值，表示“时间1”减去“时间2”之后的间隔数目。注意：每个星期以星期天为第一天
//@参数 时间1
//@参数 时间2
//@参数 取间隔部分 参数值指定取时间间隔的单位，可以为以下常量： 1、#年份； 2、#季度； 3、#月份； 4、#周； 5、#日； 6、# 小时； 7、#分钟； 8、#秒
//@别名 取时间间隔(时间1,时间2,取间隔部分);
double krnln::datetime::TimeDiff(const EPLKRNLNDATATIME_T& time1, const EPLKRNLNDATATIME_T& time2, int interval);


//@备注 返回指定月份所包含的天数。如果给定的月份无效，返回0
//@参数 年份 参数值从 100 到 9999
//@参数 月份 参数值从 1 到 12
//@别名 取某月天数(年份,月份);
int krnln::datetime::GetDaysOfMonth(int year, int month);


//@备注 将指定时间转换为文本并返回
//@参数 欲转换到文本的时间
//@参数 转换部分 参数值可以为以下常量： 1、#全部转换； 2、#日期部分； 3、#时间部分。如果省略了本参数，默认为“#全部转换 ”
//@别名 时间到文本(欲转换到文本的时间,转换部分);
CXText krnln::datetime::TimeToText(const EPLKRNLNDATATIME_T& dateTime, int convertPart = 1);

//@备注 返回一个包含已知时间指定部分的整数
//@参数 欲取其部分的时间
//@参数 欲取的时间部分 参数值可以为以下常量： 1、#年份； 2、#季度； 3、#月份； 4、#自年首周数； 5、#日； 6、#小时； 7、#分钟； 8、#秒； 9、#星期几； 10、#自年首天数。其中：自年首周数、自年首天数均从 1 开始
//@别名 取时间部分(欲取其部分的时间,欲取的时间部分);
int krnln::datetime::TimePart(const EPLKRNLNDATATIME_T& _time, int type);

//@备注 返回一个值为 100 到 9999 之间的整数，表示指定时间中的年份
//@参数 时间
//@别名 取年份(时间);
int krnln::datetime::GetYear(const EPLKRNLNDATATIME_T& time);

//@备注 返回一个值为 1 到 12 之间的整数，表示指定时间中的月份
//@参数 时间
//@别名 取月份(时间);
int krnln::datetime::GetMoon(const EPLKRNLNDATATIME_T& time);

//@备注 返回一个值为 1 到 31 之间的整数，表示一个月中的某一日
//@参数 时间
//@别名 取日(时间);
int krnln::datetime::GetDay(const EPLKRNLNDATATIME_T& time);

//@备注 返回一个值为 1 到 7 之间的整数，表示一个星期中的某一日。星期日为 1，星期一为 2，依此类推
//@参数 时间
//@别名 取星期几(时间);
int krnln::datetime::GetWeakDay(const EPLKRNLNDATATIME_T& time);

//@备注 返回一个值为 0 到 23 之间的整数，表示一天中的某一小时
//@参数 时间
//@别名 取小时(时间);
int krnln::datetime::GetHour(const EPLKRNLNDATATIME_T& time);

//@备注 返回一个值为 0 到 59 之间的整数，表示一小时中的某一分钟
//@参数 时间
//@别名 取分钟(时间);
int krnln::datetime::GetMinute(const EPLKRNLNDATATIME_T& time);

//@备注 返回一个值为 0 到 59 之间的整数，表示一分钟中的某一秒
//@参数 时间
//@别名 取秒(时间);
int krnln::datetime::GetSec(const EPLKRNLNDATATIME_T& time);

//@备注 返回包含指定年、月、日、小时、分、秒的时间。如果指定了无效时间，将自动使用最相近的有效时间代替
//@参数 年
//@参数 月 如果本参数被省略，默认为 1 月
//@参数 日 如果本参数被省略，默认为 1 日
//@参数 小时 如果本参数被省略，默认为 0 时
//@参数 分钟 如果本参数被省略，默认为 0 分钟
//@参数 秒 如果本参数被省略，默认为 0 秒
//@别名 指定时间(年,月,日,小时,分钟,秒);
EPLKRNLNDATATIME_T krnln::datetime::makeRealTime(int year, int month=1, int day=1, int hour=0, int minute=0, int second=0);

//@备注 返回当前系统日期及时间
//@别名 取现行时间();
EPLKRNLNDATATIME_T krnln::datetime::GetCurrentDateTime();

//@备注 设置当前系统日期及时间。成功返回真，失败返回假
//@参数 欲设置的时间
//@别名 置现行时间(欲设置的时间);
bool krnln::datetime::SetSysTime(const EPLKRNLNDATATIME_T& tm);

//@备注 返回一个日期时间型数据的日期部分，其小时、分钟、秒被固定设置为0时0分0秒
//@参数 时间
//@别名 取日期(时间);
EPLKRNLNDATATIME_T krnln::datetime::GetDatePart(EPLKRNLNDATATIME_T tm);

//@备注 返回一个日期时间型数据的时间部分，其年、月、日被固定设置为2000年1月1日
//@参数 时间
//@别名 取时间(时间);
EPLKRNLNDATATIME_T krnln::datetime::GetTimePart(EPLKRNLNDATATIME_T tm);

*/
//}

//@分组{系统处理
/*@声明
//@备注 本命令运行指定的可执行文件或者外部命令。如果成功，返回真，否则返回假
//@参数 欲运行的命令行
//@参数 是否等待程序运行完毕
//@参数 被运行程序窗口显示方式 参数值可以为以下常量之一：1、#隐藏窗口； 2、#普通激活； 3、#最小化激活； 4、#最大化激活； 5、#普通不激活； 6、#最小化不激活。如果省略本参数，默认为“普通激活”方式
//@别名 运行(欲运行的命令行,是否等待程序运行完毕,被运行程序窗口显示方式)
bool krnln::syspro::Run(const CXText& com_line, bool bwait=false, int showMode = 2);


//@备注 返回存放于当前 Windows 系统剪辑板中的文本。如果当前剪辑板中无文本数据，将返回空文本
//@别名 取剪辑板文本();
CXText krnln::syspro::GetCurrentClipboardText();

//@备注 将指定文本存放到当前 Windows 系统剪辑板中去，剪辑板中的原有内容被覆盖。成功返回真，失败返回假
//@参数 准备置入剪辑板的文本
//@别名 置剪辑板文本(准备置入剪辑板的文本);
bool krnln::syspro::SetClipboardText(const CXText& ClipText);

//@备注 如果当前 Windows 系统剪辑板中有文本数据，则返回真，否则返回假
//@别名 剪辑板中可有文本();
bool krnln::syspro::IsClipboardHasText();

//@备注 清除当前 Windows 系统剪辑板中的所有数据
//@别名 清除剪辑板();
bool krnln::syspro::EmptyClipboard();

//@备注 返回屏幕当前显示区域的宽度，单位为像素点
//@别名 取屏幕宽度();
int  krnln::syspro::GetSystemMetricsW ();

//@备注 返回屏幕当前显示区域的高度，单位为像素点
//@别名 取屏幕高度();
int  krnln::syspro::GetSystemMetricsH ();

//@备注 返回鼠标指针的当前水平位置，单位为像素点，相对于屏幕左边
//@别名 取鼠标水平位置();
int  krnln::syspro::GetCurssX();

//@备注 返回鼠标指针的当前垂直位置，单位为像素点，相对于屏幕顶边
//@别名 取鼠标垂直位置();
int krnln::syspro::GetCurssY();

//@备注 返回当前显示方式所提供的最大颜色显示数目
//@别名 取颜色数();
int krnln::syspro::GetColorCount();


//@备注 在对话框中显示信息，等待用户单击按钮，并返回一个整数告诉用户单击哪一个按钮。该整数为以下常量值之一： 0、#确认钮 ； 1、#取消钮； 2、#放弃钮； 3、#重试钮； 4、#忽略钮； 5、#是钮； 6、#否钮。如果对话框有“取消”按钮，则按下 ESC 键与单 击“取消”按钮的效果相同
//@参数 提示信息 提示信息只能为文本、数值、逻辑值或日期时间。如果提示信息为文本且包含多行，可在各行之间用回车符 (即“字 符 (13)”)、换行符 (即“字符 (10)”) 或回车换行符的组合 (即：“字符 (13) + 字符 (10)”) 来分隔
//@参数 按钮 始值为“0”。参数值由以下几组常量值组成，在将这些常量值相加以生成参数值时，每组值只能取用一个数字（第五组除外）：   第一组（描述对话框中显示按钮的类型与数目）：    0、#确认钮； 1、#确认取消钮； 2、#放弃重试忽略钮； 3、#取消是否钮；     4、#是否钮； 5、#重试取消钮  第二组（描述图标的样式）：    16、#错误图标； 32、#询问图标； 48、#警告图标； 64、#信息图标  第三组（说明哪一个按钮是缺省默认值）：   0、#默认按钮一； 256、#默认按钮二； 512、#默认按钮三； 768、#默认按钮四  第四组（决定如何等待消息框结束）：    0、#程序等待； 4096、#系统等待  第五组（其它）：   65536、#位于前台； 524288、#文本右对齐
//@参数 窗口标题 参数值指定显示在对话框标题栏中的文本。如果省略，默认为文本“信息：”
//@参数 父窗口 指定信息框的父窗口,可以是一个"窗口"类型数据或者一个整数型窗口句柄.如果被省略,默认为无.
//@别名 信息框(提示信息,按钮,窗口标题,父窗口);
int krnln::syspro::MsgBox(任意可格式化为文本的类型 Prompt, DWORD CommandButton = MB_OK, const std::optional<const CXText&>& Caption = 空参数, HWND hParent = nullptr);

//@备注 通过计算机媒体设备或者喇叭发出一个声音
//@别名 鸣叫();
void krnln::syspro::Beep();

//@备注 返回自 Windows 系统启动后到现在为止所经历过的毫秒数
//@别名 取启动时间();
ULONGLONG ::GetTickCount64 ();

//@备注 本命令恢复现行鼠标的原有形状，用作与“置等待鼠标”命令配对使用
//@别名 恢复鼠标();
void krnln::syspro::RestroeCursor();

//@备注 本命令设置现行鼠标的形状为沙漏形，用作在即将长时间执行程序前提示操作者
//@别名 置等待鼠标();
void krnln::syspro::SetWaitCursor();



//@备注 本命令暂停当前程序的运行并等待指定的时间
//@参数 欲等待的时间 本参数指定欲暂停程序执行的时间，单位为毫秒
//@别名 延时(欲等待的时间);
void ::Sleep(DWORD time);

//@备注 在 Windows 注册表中返回指定的文本类型注册表项值。如欲读取注册项默认值，请在项目名后加“\”号，如“test\”。
//@参数 根目录 可以为以下常量值之一： 1、#根类； 2、#现行设置； 3、#现行用户； 4、#本地机器； 5、#所有用户
//@参数 全路径注册项名
//@参数 默认文本 如果指定的注册表项不存在，将返回此默认文本。如果指定的注册表项不存在且本参数被省略，将返回一个长度为 0 的空文本
//@别名 取文本注册项(根目录,全路径注册项名,默认文本);
CXText krnln::syspro::GetTextRegItem(INT rootDir, const CXText& fullPath, const CXText& defaultString = L"");

//@备注 在 Windows 注册表中返回指定的数值类型注册表项值。如欲读取注册项默认值，请在项目名后加“\”号，如“test\”。
//@参数 根目录 可以为以下常量值之一： 1、#根类； 2、#现行设置； 3、#现行用户； 4、#本地机器； 5、#所有用户
//@参数 全路径注册项名
//@参数 默认数值 如果指定的注册表项不存在，将返回此默认数值。如果指定的注册表项不存在且本参数被省略，将返回数值 0
//@别名 取数值注册项(根目录,全路径注册项名,默认数值);
DWORD  krnln::syspro::GetNumRegItem(INT rootDir, const CXText& fullPath, const DWORD& DefaultNumber = 0);

//@备注 在 Windows 注册表中返回指定的字节集类型注册表项值。如欲读取注册项默认值，请在项目名后加“\”号，如“test\”。
//@参数 根目录 可以为以下常量值之一： 1、#根类； 2、#现行设置； 3、#现行用户； 4、#本地机器； 5、#所有用户
//@参数 全路径注册项名
//@参数 默认字节集 如果指定的注册表项不存在，将返回此默认字节集。如果指定的注册表项不存在且本参数被省略，将返回空字节集
//@别名 取字节集注册项(根目录,全路径注册项名,默认字节集);
CXBytes  krnln::syspro::GetBinRegItem(INT rootDir, const CXText& fullPath, const CXBytes& defaultBytes=空字节集);

//@备注 在 Windows 注册表中保存或建立指定的注册表项。如欲写入注册项默认值，请在项目名后加“\”号，如“test\”。成功返回 真，否则返回假。
//@参数 根目录 可以为以下常量值之一： 1、#根类； 2、#现行设置； 3、#现行用户； 4、#本地机器； 5、#所有用户
//@参数 全路径注册项名
//@参数 欲写入值 参数值指定欲写入到指定注册表项中的值，只能为数值、文本或者字节集，否则命令将失败
//@别名 写注册项(根目录,全路径注册项名,欲写入值);
bool krnln::syspro::SaveRegItem(INT rootDir, const CXText& fullPath, T&& value);

//@备注 在 Windows 注册表中删除指定注册表项或注册表目录。如欲删除注册项默认值，请在项目名后加“\”号，如“test\”。成功 返回真，否则返回假。注意在删除目录之前必须先删除该目录下所有的项目
//@参数 根目录 可以为以下常量值之一： 1、#根类； 2、#现行设置； 3、#现行用户； 4、#本地机器； 5、#所有用户
//@参数 全路径注册项名
//@别名 删除注册项(根目录,全路径注册项名);
bool  krnln::syspro::DeleteRegItem(int rootDir, const CXText& fullPath);

//@备注 如果指定注册表项存在，返回真，否则返回假。如欲检查注册项是否有默认值，请在项目名后加“\”号，如“test\”
//@参数 根目录 可以为以下常量值之一： 1、#根类； 2、#现行设置； 3、#现行用户； 4、#本地机器； 5、#所有用户
//@参数 全路径注册项名
//@别名 注册项是否存在(根目录,全路径注册项名);
bool krnln::syspro::IsRegItemExist(int rootDir, const CXText& fullPath);


//@备注 取回Windows系统的默认窗口背景颜色
//@别名 取默认底色();
DWORD krnln::syspro::GetSysColor();

//@备注 捕获指定窗口或屏幕上所有现有显示内容，返回相应图片数据。如果失败，返回空字节集
//@参数 窗口句柄 指定欲捕获其显示内容的窗口。如果被省略，默认为捕获屏幕显示内容
//@参数 输出宽度 指定图片的输出宽度。如果小于0，参数值指定的是最终图片输出宽度相对于所取得图片宽度的百分比（最小为10%） ；如果等于0，则按图片原宽度输出；如果大于0，指定输出图片的绝对宽度。如果本参数被省略，默认值为0
//@参数 输出高度 指定图片的输出高度。如果小于0，参数值指定的是最终图片输出高度相对于所取得图片高度的百分比（最小为10%） ；如果等于0，则按图片原高度输出；如果大于0，指定输出图片的绝对高度。如果本参数被省略，默认值为0
//@别名 快照(窗口句柄,输出宽度,输出高度);

//@备注 读取指定配置文件中指定项目的文本内容
//@参数 配置文件名 指定配置文件的名称，通常以.ini作为文件名后缀
//@参数 节名称 包含欲读入配置项所处节的名称
//@参数 配置项名称 参数值指定欲读入配置项在其节中的名称
//@参数 默认文本 如果指定配置项不存在，将返回此默认文本。如果指定配置项不存在且本参数被省略，将返回空文本
//@别名 读配置项(配置文件名,节名称,配置项名称,默认文本);
CXText krnln::syspro::GetSectionText(const CXText& configFile, const CXText& sectionName, const CXText& itemName, const CXText& defaultString = L"");


//@备注 将指定文本内容写入指定配置项中或者删除指定的配置项或节，如果指定配置文件不存在，将会自动创建。成功返回真，失败返回假
//@参数 配置文件名 指定配置文件的名称，通常以.ini作为文件名后缀
//@参数 节名称 包含欲写入配置项所处节的名称
//@参数 配置项名称 参数值指定欲写入配置项在其节中的名称。如果参数值被省略，则删除指定节及其下的所有配置项
//@参数 欲写入值 参数值指定欲写入到指定配置项中的文本。如果参数值被省略，则删除所指定配置项
//@别名 写配置项(配置文件名,节名称,配置项名称,欲写入值);
bool krnln::syspro::SetSectionText(const CXText& configFile, const CXText& sectionName, const CXText& itemName, const CXText& defaultString );

//@备注 返回指定配置文件中所有已有节名的文本数组
//@参数 配置文件名 指定配置文件的名称，通常以.ini作为文件名后缀
//@别名 取配置节名(配置文件名);
StrArray krnln::syspro::GetSectionNames(const CXText& configFile);

//@备注 返回当前操作系统的版本类别。返回值为以下值之一：0、未知； 1、Windows 32S； 2、Windows 9X (包含Win95、Win98、WinME等)； 3、Windows NT (包含WinNT、Win2000、WinXP等)； 4、Linux
//@别名 取操作系统类别();
int krnln::syspro::GetSysVer();

//@备注  在一对话框中显示提示，等待用户输入正文并按下按钮。如果用户在确认输入后（按下“确认输入”按钮或回车键）退出，返回真，否则返回假。本命令为初级命令。
//@参数  可以被省略。如果提示信息包含多行，可在各行之间用回车符 (即“字符 (13)”)、换行符 (即“字符 (10)”) 或回车换行符的组合 (即：“字符 (13) + 字符 (10)”) 来分隔。如果提示信息太长或行数过多，超过部分将不会被显示出来。
//@参数  可以被省略。参数值指定显示在对话框标题栏中的文本。如果省略，默认为文本“请输入：”。
//@参数  可以被省略。参数值指定初始设置到对话框输入文本框中的内容。
//@参数  提供参数数据时只能提供变量。参数值所指定的变量可以为数值或文本型，用于以不同的数据类型取回输入内容。
//@参数  可以被省略。参数值可以为以下常量值： 1、#输入文本； 2、#输入整数； 3、#输入小数； 4、#输入密码。如果省略本参数，默认为“#输入文本”。
//@参数  可以被省略。指定输入框的父窗口,可以是一个"窗口"类型数据或者一个整数型窗口句柄.如果被省略,默认为无.
//@参数  可以被省略。指定输入方式是否为多行.
//@别名  输入框  (提示信息,窗口标题, 初始文本,存放输入内容的变量,输入方式,父窗口,是否多行)
bool krnln::syspro::InputBox(const std::optional<const CXText>& OppromptMessage = 空参数, const std::optional<const CXText>& OpwindowTitle = 空参数, const std::optional<const CXText>& OpinitialText = 空参数, std::optional <std::reference_wrapper<typename T>> OpvariableToStoreInput = 空参数, const std::optional<int>& OpinputType = 空参数, const std::optional<HWND>& parentWindow = 空参数, bool bMultiLineAdd = false) ;


//@备注  在一对话框中显示提示，等待用户输入正文并按下按钮。如果用户在确认输入后（按下“确认输入”按钮或回车键）退出，返回真，否则返回假。本命令为初级命令。
//@参数 <1>的名称为“标题”，类型为“文本型（text）”，可以被省略。指定文件打开对话框的标题，如果被省略，则默认为“请输入欲打开的文件：”。
//@参数 <2>的名称为“过滤器”，类型为“文本型（text）”，可以被省略。过滤器文本由单个或多个成对的文本串组成，每对文本串的第一个描述显示形式，如：“文本文件（*.txt）”；第二个指定实际的过滤匹配符，如：“*.txt”，所有各文本串之间用“|”号隔开。如果被省略，则默认没有过滤器。
//@参数 <3>的名称为“初始过滤器”，类型为“整数型（int）”，可以被省略。如果上一参数提供了有效的过滤器文本，则本参数用作指定初始的过滤器，0为第一个过滤器。如果被省略，则默认值为0。
//@参数 <4>的名称为“初始目录”，类型为“文本型（text）”，可以被省略。指定当打开对话框时所自动跳转到的目录，如果被省略，则默认为当前目录。
//@参数 <5>的名称为“不改变目录”，类型为“逻辑型（bool）”，可以被省略。指定在对话框关闭后是否自动返回到进入对话框前的文件目录，如果被省略，则默认值为假。
//@参数 <6>的名称为“父窗口”，类型为“通用型（all）”，可以被省略。指定对话框的父窗口,可以是一个"窗口"类型数据或者一个整数型窗口句柄.如果被省略,默认为无.
//@别名  多文件对话框  (标题,过滤器, 初始过滤器,初始目录,不改变目录,父窗口)
strArray krnln::syspro::OpenFileManyDialogW( const std::optional<const CXText>& title= 空参数, const CXText& _filter=L"",  int initFilter=0,const std::optional<const CXText>& initDir= 空参数,bool noChangeDir=false, HWND parentWnd=nullptr );


//@备注 返回所指定类型的程序名称. 本命令为编译预处理命令.
//@参数 欲取的程序名称类型 1:当前语句所处子程序名称; 2:当前语句所处程序集名称; 3:当前语句所处易语言程序的全路径文件名称(注意如果编译时易语言程序没有保存,将为空); 4:当前语句所处程序配置信息中的程序名称;  5:当前语句所处程序配置信息中的作者名 称; 6:当前语句所处易语言程序的无路径和后缀文件名称(注意如果编译时易语言程序没有保存,将为空)
//@别名 取程序名称(欲取的程序名称类型);
CXText EPL_GET_PROGRAM_NAME(int type);


//@备注 快速交换两个变量的内容. 本命令对于文本、字节集、自定义数据类型不会进行值数据拷贝,仅交换其指针值,因此速度要比通过赋值命令间接交换快得多.本命令要求这两个变量的数据类型必须完全一致,为编译预处理命令.
//@参数 变量1 欲将其内容交换到变量2的变量1
//@参数 变量2 欲将其内容交换到变量1的变量2
//@别名 交换变量(变量1,变量2);
void krnln::syspro::stdswap(任意类型,任意类型);



//@备注 快速交换两个变量的内容. 本命令对于文本、字节集、自定义数据类型不会进行值数据拷贝,仅交换其指针值,因此速度要比通过赋值命令间接交换快得多.本命令与"交换变量"不同的是: 本命令仅要求这两个变量的数据尺寸必须一致,但是不对数据类型进行检查,因 此调用方必须确保交换后的变量能正常使用. 用户可以使用本命令进行类似强制类型转换这样的操作. 本命令为编译预处理命令.
//@参数 变量1 欲将其内容交换到变量2的变量1
//@参数 变量2 欲将其内容交换到变量1的变量2
//@别名 强制交换变量(变量1,变量2);
void krnln::syspro::swap(任意类型,任意类型);

//@备注 返回所提供参数的运行时数据类型值. 注意: 如果该数据类型是在除系统核心支持库外的其它支持库中定义的,那么每一次程序 启动后该数据类型值可能会发生变化(因为载入程序时重定位操作的原因),不过在程序运行过程中该值是不会变化的.除开此特例外,其它 数据的数据类型在任何时候均始终是一个恒定值.
//@参数 欲取其数据类型的数据 欲取其运行时数据类型的数据
//@别名 取运行时数据类型(欲取其数据类型的数据);
size_t krnln::syspro::gettypeid(任意数据类型 欲取其数据类型的数据 );

//@备注 只能在类方法中使用本命令,用作返回存储有指向本对象自身数据指针的变量地址.
//@别名 类自身();
__passnop __impeplthiself();


//@备注 返回当前操作系统的版本类别。返回值为以下值之一：0、未知； 1、Windows 32S； 2、Windows 9X (包含Win95、Win98、WinME等)； 3、其它Windows NT操作系统(不包括后面列出的)； 4、Linux； 5、Windows 10； 6、Windows Server 2016 Technical Preview； 7、Windows 8.1； 8、Windows Server 2012 R2； 9、Windows 8； 10、Windows Server 2012； 11、Windows 7； 12、Windows Server 2008 R2； 13、Windows Server 2008； 14、Windows Vista
//@别名 取操作系统类别2();
int krnln::syspro::GetSysVer2();


//@备注 调用操作系统的GetLastError函数,返回该API函数被调用后的返回值.
//@别名 取最后错误();
DWORD ::GetLastError();


*/
//}


















#undef put_errmsg
#endif


