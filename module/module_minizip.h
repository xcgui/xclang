//@模块名称  minizip
//@版本  1.0
//@日期  2025-05-28
//@作者  XCGUI
//@QQ  154460336
//@模块备注  zip解压模块, 支持大于4GB的zip包, https://github.com/zlib-ng/minizip-ng
//因为minizip不支持读写混合操作, 所以根据读写分别封装了 CUnZip(读操作), CSaveZip(写操作)

#pragma once

#include "module_base.h"

#include "minizip/mz.h"
#include "minizip/mz_strm.h"
#include "minizip/mz_strm_mem.h"
#include "minizip/mz_os.h"
#include "minizip/mz_strm_os.h"
#include "minizip/mz_zip.h"
#include "minizip/mz_compat.h"

#ifdef   _WIN64
#pragma comment(lib, "lib/zlibstatic-x64.lib")
#pragma comment(lib, "lib/libminizip-ng-x64.lib")

#else

#ifdef _DEBUG
#pragma comment(lib, "minizip/zlibstaticd.lib")
#pragma comment(lib, "minizip/libminizip-ng-d.lib")
#else
#pragma comment(lib, "minizip/zlibstatic.lib")
#pragma comment(lib, "minizip/libminizip-ng.lib")
#endif

#endif

//@src "module_minizip.cpp"


//@备注  解压进度回调函数格式
//@参数  ZIP句柄
//@参数  文件信息
//@参数  文件路径
//@参数  ZIP未压缩文件总大小
//@参数  当前已解压大小
typedef int (*minizip_progressCallback)(void* handle, mz_zip_file* file_info, const wchar_t* filePath, INT64 totalSize, INT64  curSize);

//@doc  "demo.txt"
//@备注  解压一个ZIP文件到目标位置
//@别名  minizip_解压ZIP(保存位置, ZIP文件名, 密码, 解压进度回调)
BOOL  minizip_unZip(const wchar_t* pSavePath, const wchar_t* pZipFileName, const wchar_t* pPassword = NULL, minizip_progressCallback callback = NULL);

//@doc  "demo.txt"
//@备注  将指定文件夹打包成ZIP保存到目标位置
//@别名  minizip_保存ZIP(保存ZIP文件名, 打包文件夹, 密码)
BOOL  minizip_saveZip(const wchar_t* pSaveZipFileName, const wchar_t* pFloder, const wchar_t* pPassword = NULL);

//@doc  "demo.txt"
//@备注 解压ZIP, 读取操作, 不支持写入操作
class CUnZip
{
public:
    //@隐藏{
	CUnZip();
    ~CUnZip() { CloseZip(); }
	void*   m_zip_stream;
	void*   m_zip_handle;
    std::string  m_zip_password_utf8;
	std::wstring m_savePath;
	minizip_progressCallback  m_funCallback; //进度回调函数
    BOOL   m_bMem;               //是否从内存打开ZIP文件
    BOOL   m_bExtractSingleFile; //提取单个文件
	INT64  m_totalSize;       //总大小
	INT64  m_totalSize_cur;   //当前大小
    //@隐藏}
   
    //@备注  打开指定ZIP文件, 仅支持提取文件, 不支持写入
    //@参数  ZIP文件路径, 完整路径或相对路径
    //@参数  ZIP包密码, 可空
    //@别名  打开ZIP文件(ZIP文件路径, ZIP密码)
    BOOL OpenZip(const wchar_t* pZipFileName, const wchar_t* pPassword = NULL);

    //@备注  打开指定ZIP文件从内存, 仅支持提取文件, 不支持写入
    //@参数  数据地址
    //@参数  数据大小(字节为单位)
    //@参数  ZIP包密码, 可空
    //@别名  打开ZIP从内存(数据地址, 数据大小, 密码)
    BOOL OpenZipMem(const void* data, int length, const wchar_t* pPassword = NULL);

    //@备注  该回调用于获取ZIP解压进度, 当调用 提取文件全部() 时, 此回调才会响应
    //@参数  回调函数, 用于响应解压进度
    //@别名  置解压进度回调(回调函数)
	void  SetProgressCallback(minizip_progressCallback funCallback);

    //@备注  解压ZIP中全部文件, 可设置进度回调
    //@参数  保存路径, ZIP文件将解压到此目录中
    //@别名  提取文件全部(保存路径)
    BOOL  ExtractFileAll(const wchar_t* pSavePath);
    
    //@备注  从ZIP包中提取一个文件
    //@参数  在ZIP包中的文件名, 例如: "test\\abc.txt"
    //@参数  保存在磁盘中的文件名, 例如: "D:\\test\\abc.txt"
    //@别名  提取文件单个(文件名, 保存路径)
    BOOL  ExtractFile(const wchar_t* pFileName, const wchar_t* pSaveFileName);  //提取单个文件

    //@备注  提取到内存
    //@参数  在ZIP包中的文件名, 例如: "test\\abc.txt"
    //@参数  接收返回的文件数据
    //@别名  提取文件单个数据(文件名, 返回文件数据)
    BOOL  ExtractFileData(const wchar_t* pFileName, CXBytes &ret_data);

    //@备注  当不使用时关闭ZIP,  当类析构时会自动调用 CloseZip()
    //@别名  关闭ZIP()
	void  CloseZip();

private:
	BOOL    calculate_total_size();
	int32_t extract_currentfile();
    int32_t extract_currentfile_data(CXBytes& ret_data);
};

//@doc  "demo.txt"
//@备注 打包ZIP, 写入操作, 不支持读取操作
class CSaveZip
{
public:
    //@隐藏{
    CSaveZip();
    ~CSaveZip() { CloseZip(); }
    void* m_zip_stream;
    void* m_zip_handle;
    int16_t  m_compress_level;
    int16_t  m_compress_method;
    std::string   m_password_utf8;
    std::string   m_dir_utf8;
    //@隐藏}

    //@备注  创建一个ZIP文件, 仅支持写入操作, 不支持读取
    //@参数  完整路径或相对路径, 例如: "D:\\Test\\abc.zip", "abc.zip"
    //@别名  创建ZIP(ZIP文件名)
    BOOL CreateZip(const wchar_t* pZipFileName);

    //@备注  为ZIP设置一个密码
    //@别名  置密码(密码字符串)
    void SetPassword(const wchar_t* pPassword);

    //@备注  将指定文件目录添加到ZIP, 会自动扫描目录内所有文件; 全路径, 例如: "D:\\Test\\AAA"
    //@参数  文件夹路径
    //@别名  添加目录(目录路径)
    BOOL AddDir(const wchar_t* pFloder);

    //@备注  将指定文件添加到ZIP
    //@参数  文件名, 完整路径或相对路径, 例如: "D:\\Test\\abc.txt"
    //@参数  在ZIP中的相对路径及文件名, 例如: "Test\\abc.txt"
    //@别名  添加文件(文件路径, 在ZIP中路径和文件名)
    BOOL AddFile(const wchar_t* pFileName, const wchar_t* pPathInZip);

    //@备注  当不使用时关闭ZIP, 当类析构时会自动调用 CloseZip()
    //@别名  关闭ZIP()
    void CloseZip();
private:
    int32_t minizip_add_dir(const char* path_utf8);
    int32_t minizip_add_file(const char* path_utf8, const char* filenameinzip);
};


/*@声明
typedef struct mz_zip_file_s {
    uint16_t version_madeby;            // version made by 
    uint16_t version_needed;            // version needed to extract 
    uint16_t flag;                      // general purpose bit flag 
    uint16_t compression_method;        // compression method 
    time_t   modified_date;             // last modified date in unix time 
    time_t   accessed_date;             // last accessed date in unix time
    time_t   creation_date;             // creation date in unix time 
    uint32_t crc;                       // crc-32 
    int64_t  compressed_size;           // compressed size 
    int64_t  uncompressed_size;         // uncompressed size
    uint16_t filename_size;             // filename length
    uint16_t extrafield_size;           // extra field length
    uint16_t comment_size;              // file comment length
    uint32_t disk_number;               // disk number start
    int64_t  disk_offset;               // relative offset of local header 
    uint16_t internal_fa;               // internal file attributes
    uint32_t external_fa;               // external file attributes

    const char* filename;               // filename utf8 null-terminated string
    const uint8_t* extrafield;          // extrafield data
    const char* comment;                // comment utf8 null-terminated string
    const char* linkname;               // sym-link filename utf8 null-terminated string
                                        //
    uint16_t zip64;                     // zip64 extension mode
    uint16_t aes_version;               // winzip aes extension if not 0
    uint8_t  aes_encryption_mode;       // winzip aes encryption mode
    uint16_t pk_verify;                 // pkware encryption verifier

} mz_zip_file, mz_zip_entry;

*/