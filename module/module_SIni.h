//@模块名称 SIni
//@版本 0.1.1
//@日期 2022-11-13
//@作者 欧阳逸洛
//@QQ  欧阳逸洛
//@模块备注 ini文件读写操作
//包装源：https://github.com/brofield/simpleini

//@依赖 module_base.h, module_wrapper_tools.h
 
//@隐藏{
#pragma once

#include "SimpleIni.h"
#include <functional>
//@隐藏}

//@别名 SIni_编码
enum SIni_Encode {
	//@别名 SIni_编码_当前
	SIni_Encode_Curr,
	//@别名 SIni_编码_ANSI
	SIni_Encode_ANSI,
	//@别名 SIni_编码_UTF8
	SIni_Encode_UTF8,
	//@别名 SIni_编码_UTF16
	SIni_Encode_UTF16,
};

//@别名 SIni_错误
typedef int SIni_Error;

//@别名 SIni_成功
#define SIni_OK  0        //!< No error
//@别名 SIni_已更新
#define SIni_UPDATED  1   //!< An existing value was updated
//@别名 SIni_已插入
#define SIni_INSERTED  2  //!< A new value was inserted

				// note: test for any error with (retval < 0)
//@别名 SIni_失败
#define SIni_FAIL  -1     //!< Generic failure
//@别名 SIni_内存错误
#define SIni_NOMEM  -2   //!< Out of memory error
//@别名 SIni_文件错误
#define SIni_FILE  -3     //!< File error (see errno for detail error)
/*@声明

//@别名 SIni_条目
struct SIni_Entry {
	//@别名 项
	const wchar_t * pItem;
	//@别名 注释
	const wchar_t * pComment;
	//@别名 命令
	int             nOrder;
};

*/
//@隐藏{
using SIni_Entry = CSimpleIniW::Entry;
//@隐藏}


class SIni 
	//@隐藏{
	: public CSimpleIniW //修改为虚析构函数
	//@隐藏}
{
public:
	//@隐藏{
	using CSimpleIniW::CSimpleIniW;
	SIni():CSimpleIniW() {
		this->SetUnicode(true);
	}
	//@隐藏}
	/*@声明
	//@别名 清空()
	void Reset();

	//@别名 为空()
	bool IsEmpty();

	//@别名 取节数量()
	int GetSectionSize(const wchar_t * pSection);
	//@别名 节存在(节名)
	bool SectionExists(const wchar_t * pSection);
	//@别名 键存在(节名,键名)
	bool KeyExists(const wchar_t * pSection,const wchar_t * pKey);

	//@别名 取文本(节名,键名,默认值,有多个)
	const wchar_t *GetValue(const wchar_t * pSection,const wchar_t * pKey, const wchar_t * pDefault, bool* pHasMultiple = nullptr);

	//@别名 取整型 (节名,键名,默认值,有多个)
	long GetLongValue(const wchar_t * pSection,const wchar_t * pKey,long nDefault, bool* pHasMultiple = nullptr);

	//@别名 取双浮点 (节名,键名,默认值,有多个)
	double GetDoubleValue(const wchar_t * pSection,const wchar_t * pKey, double nDefault, bool* pHasMultiple = nullptr);

	//@别名 取逻辑 (节名,键名,默认值,有多个)
	bool GetBoolValue(const wchar_t * pSection,const wchar_t * pKey, bool bDefault, bool* pHasMultiple = nullptr);

	//@别名 置文本(值_节名,键名,值,注释,强制替换)
	SIni_Error SetValue(const wchar_t * pSection,const wchar_t * pKey, const wchar_t * pValue, const wchar_t * pComment = nullptr, bool bForceReplace = false);

	//@别名 置整型 (节名,键名,值,注释,使用十六进制,强制替换)
	SIni_Error SetLongValue(const wchar_t * pSection,const wchar_t * pKey, long nValue, const wchar_t *  pComment = nullptr, bool bUseHex = false, bool bForceReplace = false);

	//@别名 置双浮点 (节名,键名,值,注释,强制替换)
	SIni_Error SetDoubleValue(const wchar_t * pSection,const wchar_t * pKey, double nValue,const wchar_t *  pComment = nullptr, bool bForceReplace = false);

	//@别名 置逻辑 (节名,键名,值,注释,强制替换)
	SIni_Error SetBoolValue(const wchar_t * pSection,const wchar_t * pKey, bool bValue,const wchar_t *  pComment = nullptr, bool bForceReplace = false);

	//@别名 删除 (节名,键名,移除空)
	bool Delete(const wchar_t * pSection, const wchar_t * pKey, bool bRemoveEmpty = false);

	//@别名 删除值 (节名,键名,值,移除空)
	bool DeleteValue(const wchar_t * pSection, const wchar_t * pKey, const wchar_t * pValue, bool bRemoveEmpty = false);
	*/


	//@别名 置编码 (编码)
	SIni_Encode SetEncode(SIni_Encode encode) {
		if (encode != SIni_Encode_Curr) {
			m_encode = encode;
		}
		return m_encode;
	}

	//@别名 取编码 ()
	SIni_Encode GetEncode() {
		return m_encode;
	}

	//@别名 载入_从文本 (文本)
	SIni_Error LoadDataFromText(const CXText& text) {
		LoadInit();
		SetEncode(SIni_Encode_UTF16);
		return this->LoadData(CnvEncode::UnicodeToUtf8(xc_wrapper::utils::GetRaw(text)));
	}

	//@别名 载入_从文本A (文本,编码)
	SIni_Error LoadDataFromTextA(const CXTextA& text, SIni_Encode encode = SIni_Encode_Curr) {
		LoadInit();
		auto& raw = xc_wrapper::utils::GetRaw(text);
		switch (SetEncode(encode)) {
		case SIni_Encode_ANSI: {
			return this->LoadData(CnvEncode::AnsiToUtf8(xc_wrapper::utils::GetRaw(text)));
		}
		case SIni_Encode_UTF8: {
			return this->LoadData(xc_wrapper::utils::GetRaw(text));
		}
		case SIni_Encode_UTF16: {
			return SIni_FAIL;
		}
		default:
			return SIni_FAIL;
		}
	}

	//@别名 载入_从字节集 (字节集,编码)
	SIni_Error LoadDataFromBytes(const CXBytes& bytes, SIni_Encode encode = SIni_Encode_Curr) {
		LoadInit();
		switch (SetEncode(encode)) {
		case SIni_Encode_ANSI: {
			return this->LoadData(CnvEncode::AnsiToUtf8({ (const char*)bytes.get(), static_cast<size_t>(bytes.size()) }));;
		}
		case SIni_Encode_UTF8: {
			return this->LoadData((const char*)bytes.get(), bytes.size());
		}
		case SIni_Encode_UTF16: {
			return this->LoadData(CnvEncode::UnicodeToUtf8({ (const wchar_t*)bytes.get(), static_cast<size_t>(bytes.size() / sizeof(wchar_t)) }));;
		}
		default:
			return SIni_FAIL;
		}
	}

	////@别名 载入_从指针 (指针,长度)
	//SIni_Error LoadDataFromPointer(const BYTE* byte, int size) {
	//	return this->LoadData((const char*)byte, size);
	//}

	//@别名 载入_从文件 (文件路径,编码)
	SIni_Error LoadDataFromFile(const wchar_t* path, SIni_Encode encode = SIni_Encode_Curr) {
		CXFile file;
		if (file.openRead(path)) {
			file.seekBegin();
			auto bytes = file.readDataBytes();
			return this->LoadDataFromBytes(bytes, encode);
		}
		return SIni_FILE;
	}

	//@别名 另存为_文本A (输出,编码,添加签名)
	SIni_Error SaveToTextA(CXTextA& output, SIni_Encode encode = SIni_Encode_Curr, bool addSignature = false) {
		switch (SetEncode(encode)) {
		case SIni_Encode_ANSI: {
			std::string buf;
			auto err = this->Save(buf, false);
			xc_wrapper::utils::GetRaw(output) = CnvEncode::Utf8ToAnsi(buf);
			return err;
		}
		case SIni_Encode_UTF8: {
			return this->Save(xc_wrapper::utils::GetRaw(output), addSignature);
		}
		case SIni_Encode_UTF16: {
			return SIni_FAIL;
		}
		default:
			return SIni_FAIL;
		}
	}

	//@别名 另存为_文本 (输出,添加签名)
	SIni_Error SaveToText(CXText& output, bool addSignature = false) {
		std::string buf;
		SIni_Error err = this->Save(buf, addSignature);
		if (err == SIni_OK)
			xc_wrapper::utils::GetRaw(output) = CnvEncode::Utf8ToUnicode(buf);
		return err;
	}

	//@别名 另存为_字节集 (输出,编码,添加签名)
	SIni_Error SaveAsBytes(CXBytes& output, SIni_Encode encode = SIni_Encode_Curr, bool addSignature = false) {
		return SaveAsCallback(encode, addSignature, 
			[&](const void* data, size_t size) ->SIni_Error
			{
				output.set(data, static_cast<int>(size));
				return SIni_OK;
			});
	}

	//@别名 另存为_文件 (文件路径,编码,添加签名)
	SIni_Error SaveAsFile(const wchar_t* path, SIni_Encode encode = SIni_Encode_Curr, bool addSignature = true) {
		return SaveAsCallback(encode, addSignature,
			[&](const void* data, size_t size)->SIni_Error
			{
				if (xc_wrapper::utils::CreateAndWriteFile(path, data, size))
					return SIni_OK;
				else
					return SIni_FILE;
			});
	}

	//@别名 取所有节名 ()
	CXVector<CXText> GetAllSectionsToXVec() {
		CSimpleIniW::TNamesDepend sections;
		this->GetAllSections(sections);
		CXVector<CXText> result;
		for (auto& section : sections)
			result.add(section.pItem);
		return result;
	}

	//@别名 取所有键名 (节名)
	CXVector<CXText> GetAllKeysToXVec(const wchar_t* section) {
		CSimpleIniW::TNamesDepend keys;
		this->GetAllKeys(section, keys);
		CXVector<CXText> result;
		for (auto& key : keys)
			result.add(key.pItem);
		return result;
	}

	//@别名 取所有节条目 ()
	CXVector<SIni_Entry> GetAllSectionsToEntrys() {
		CSimpleIniW::TNamesDepend sections;
		this->GetAllSections(sections);
		return xc_wrapper::utils::ToCXVector(sections);
	}

	//@别名 取所有键条目 (节名)
	CXVector<SIni_Entry> GetAllKeysToEntrys(const wchar_t* section) {
		CSimpleIniW::TNamesDepend keys;
		this->GetAllKeys(section, keys);
		return xc_wrapper::utils::ToCXVector(keys);
	}

	//@隐藏{
private:
	SIni_Encode m_encode = SetEncode(SIni_Encode_UTF8);

	void LoadInit() {
		this->Reset();
		this->SetUnicode(true);
	}

	SIni_Error SaveAsCallback(SIni_Encode encode, bool addSignature, std::function<SIni_Error(const void* data, size_t size)> callback) {
		switch (SetEncode(encode)) {
		case SIni_Encode_ANSI: {
			std::string buf;
			auto err = this->Save(buf, false);
			if (err == SIni_OK) {
				auto result = CnvEncode::Utf8ToAnsi(buf);
				err = callback(result.data(), result.size());
			}
			return err;
		}
		case SIni_Encode_UTF8: {
			std::string result;
			auto err = this->Save(result, addSignature);
			if (err == SIni_OK) {
				err = callback(result.data(), result.size());
			}
			return err;
		}
		case SIni_Encode_UTF16: {
			std::string buf;
			auto err = this->Save(buf, addSignature);
			if (err == SIni_OK) {
				auto result = CnvEncode::Utf8ToUnicode(buf);
				err = callback(result.data(), result.size() * sizeof(wchar_t));
			}
			return err;
		}
		default:
			return SIni_FAIL;
		}
	}
	//@隐藏}
};

