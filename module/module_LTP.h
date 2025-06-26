//@模块名称 LTP
//@版本 0.1.0
//@日期 2022-12-14
//@作者 欧阳逸洛
//@模块备注 对中文文本进行分词、词性标注、句法分析
//注意事项：因模块上传大小限制，需要手动下载模型文件。从 https://huggingface.co/LTP/legacy/tree/main下载模型文件，放到 模块目录\legacy 目录中。
//包装源：https://github.com/HIT-SCIR/ltp
//包装源许可证： https://github.com/HIT-SCIR/ltp#%E5%BC%80%E6%BA%90%E5%8D%8F%E8%AE%AE

//@依赖 module_base.h
////@依赖 module_wrapper_tools.h

#ifdef _WIN64 //x64
//@lib "x64/ltp.dll.lib"
//@复制文件 @当前模块路径 "x64/ltp.dll"

#else // x86 
//@lib "x86/ltp.dll.lib"
//@复制文件 @当前模块路径 "x86/ltp.dll"
#endif

//@复制文件 @当前模块路径 "legacy/cws_model.bin"
//@复制文件 @当前模块路径 "legacy/pos_model.bin"
//@复制文件 @当前模块路径 "legacy/ner_model.bin"
//@隐藏{
#pragma once

#ifdef _WIN64 //x64
#ifdef XC_MODULE_DEV
#pragma comment(lib,"x64/ltp.dll.lib")
#endif //XC_MODULE_DEV

#else // x86 
#ifdef XC_MODULE_DEV
#pragma comment(lib,"x86/ltp.dll.lib")
#endif //XC_MODULE_DEV
#endif

//@隐藏}

//@src "module_LTP.cpp"

//@隐藏{
namespace ltp {
    struct Model;
    struct ModelDeleter {
        void operator()(Model* model);
    };
    using Model_unique_ptr = std::unique_ptr<Model, ModelDeleter>;
}
//@隐藏}`


CXText ltp_Utf8ToUtf16le(const CXTextA& str);
CXTextA ltp_Utf16leToUtf8(const CXText& str);


//@别名 ltp_分词模型
class ltp_CWSModel
{
public:
    //@隐藏{
    ltp_CWSModel() = default;

    // movable:
    ltp_CWSModel(ltp_CWSModel&& rhs) noexcept;
    ltp_CWSModel& operator=(ltp_CWSModel&& rhs) noexcept;

    // and copyable
    ltp_CWSModel(const ltp_CWSModel& rhs) = delete;
    ltp_CWSModel& operator=(const ltp_CWSModel& rhs) = delete;
    //@隐藏}

    //@别名 载入(模型文件路径)
    bool load(const wchar_t* model_path);

    //@别名 预测(句子文本)
    //@备注 utf8编码
    CXVector<CXTextA> predict(const CXTextA& sentence);

    //@别名 预测W(句子文本)
    //@备注 utf16le编码
    CXVector<CXText> wpredict(const CXText& sentence);

private:
    ltp::Model_unique_ptr m_model;
};

//@别名 ltp_词性标注模型
class ltp_POSModel
{
public:
    //@隐藏{
    ltp_POSModel() = default;

    // movable:
    ltp_POSModel(ltp_POSModel&& rhs) noexcept;
    ltp_POSModel& operator=(ltp_POSModel&& rhs) noexcept;

    // and copyable
    ltp_POSModel(const ltp_POSModel& rhs) = delete;
    ltp_POSModel& operator=(const ltp_POSModel& rhs) = delete;
    //@隐藏}

    //@别名 载入(模型文件路径)
    bool load(const wchar_t* model_path);

    //@别名 预测(分词结果)
    //@备注 utf8编码
    CXVector<CXTextA> predict(const CXVector<CXTextA>& words);

private:
    ltp::Model_unique_ptr m_model;
};

//@别名 ltp_命名实体识别模型
class ltp_NERModel
{
public:
    //@隐藏{
    ltp_NERModel() = default;

    // movable:
    ltp_NERModel(ltp_NERModel&& rhs) noexcept;
    ltp_NERModel& operator=(ltp_NERModel&& rhs) noexcept;

    // and copyable
    ltp_NERModel(const ltp_NERModel& rhs) = delete;
    ltp_NERModel& operator=(const ltp_NERModel& rhs) = delete;
    //@隐藏}
 
    //@别名 载入(模型文件路径)
    bool load(const wchar_t* model_path);

    //@别名 预测(分词结果,词性标注结果)
    //@备注 utf8编码
    CXVector<CXTextA> predict(const CXVector<CXTextA>& words, const CXVector<CXTextA>& poses);

private:
    ltp::Model_unique_ptr m_model;
};