#pragma once
#include "module_base.h"
#include "zip.h"

//@模块名称 libzip
//@版本  1.0
//@日期  2025-06-13
//@作者  kyozy
//@QQ 75602718
//@模块备注  Copyright (C) 1999-2025 Dieter Baron and Thomas Klausner
//The authors can be contacted at info@libzip.org
//一个用于创建、读取和修改 ZIP 压缩文件的开源库.
//支持大文件, 支持进度


//@依赖  module_base.h
//@包含目录  @当前模块路径 "libzip\include"

#ifdef _WIN64

#ifdef _DEBUG
//@lib "libzip\lib\x64\Debug\zip.lib"
#else
//@lib "libzip\lib\x64\Release\zip.lib"
#endif

#else
#ifdef _DEBUG
//@lib "libzip\lib\Win32\Debug\zip.lib"
#else
//@lib "libzip\lib\Win32\Release\zip.lib"
#endif

#endif

//@src "module_kyozy_libzip.cpp"


namespace libzip
{
	
	//@分组{  类型

	typedef time_t 时间戳;
	typedef zip_int8_t 整数8;
	typedef zip_uint8_t 正整数8;
	typedef zip_int16_t 整数16;	
	typedef zip_uint16_t 正整数16;	
	typedef zip_int32_t 整数32;	
	typedef zip_uint32_t 正整数32;
	typedef zip_int64_t 整数64;	
	typedef zip_uint64_t 正整数64;

	//@别名 进度回调
	//@参数 archive 压缩包指针
	//@参数 progress 进度
	//@参数 ud 用户数据
	typedef void (*进度回调函数)(LPVOID archive, double progress, void* ud); 

	//@别名 取消回调
	//@参数 archive 压缩包指针
	//@参数 ud 用户数据
	//@返回 非0表示取消
	typedef int (*取消回调函数)(LPVOID archive, void* ud);
	/*@声明

	*/
	
	//@分组} 类型

	//@分组{ 枚举常量

	//@备注 压缩包::打开 方法使用的标志
	enum 打开选项
	{
		//@备注 没有任何选项
		打开选项_无 = 0,	
		//@备注 如果压缩包不存在，创建压缩包。
		打开选项_创建 = ZIP_CREATE,
		//@备注 配合 打开选项_创建 使用, 若压缩包存在则报错。
		打开选项_不存在 = ZIP_EXCL,
		//@备注 对压缩包执行其他更严格的一致性检查，如果检查失败，则出错。
		打开选项_检查一致性 = ZIP_CHECKCONS,
		//@备注 如果压缩包存在，则忽略其当前内容。换句话说，像处理空压缩包一样处理它。
		打开选项_截断 = ZIP_TRUNCATE,
		//@备注 以只读模式打开压缩包。
		打开选项_只读 = ZIP_RDONLY
	};


	enum 错误系统类型
	{
		错误系统类型_无 = ZIP_ET_NONE,
		错误系统类型_系统 = ZIP_ET_SYS,
		错误系统类型_ZLIB = ZIP_ET_ZLIB,
		错误系统类型_LIBZIP = ZIP_ET_LIBZIP,
	};

	enum 标志
	{
		标志_只读 = ZIP_AFL_RDONLY,
		标志_TORRENTZIP = ZIP_AFL_IS_TORRENTZIP,
		标志_期望TORRENTZIP = ZIP_AFL_WANT_TORRENTZIP,
		标志_创建或保留文件以空存档 = ZIP_AFL_CREATE_OR_KEEP_FILE_FOR_EMPTY_ARCHIVE
	};

	enum 文件标志
	{
		文件标志_无 = 0,
		//@备注 名称查找时忽略大小写
		文件标志_忽略大小写 = ZIP_FL_NOCASE,
		//@备注 忽略目录组件
		文件标志_忽略目录 = ZIP_FL_NODIR,
		//@备注 读取压缩数据
		文件标志_压缩 = ZIP_FL_COMPRESSED,
		//@备注 获取加密数据
		文件标志_未改变 = ZIP_FL_UNCHANGED,
		//@备注 读取加密数据（隐含 文件标志_压缩）
		文件标志_加密 = ZIP_FL_ENCRYPTED,
		//@备注 猜测字符串编码（默认）
		文件标志_编码猜测 = ZIP_FL_ENC_GUESS,
		//@备注 获取未修改的字符串
		文件标志_编码原始 = ZIP_FL_ENC_RAW,
		//@备注 严格遵循规范
		文件标志_编码严格 = ZIP_FL_ENC_STRICT,
		//@备注 字符串是 UTF-8 编码的
		文件标志_编码UTF8 = ZIP_FL_ENC_UTF_8,
		//@备注 字符串是 CP437 编码的
		文件标志_编码CP437 = ZIP_FL_ENC_CP437,
		//@备注 在本地标头中
		文件标志_本地头 = ZIP_FL_LOCAL,
		//@备注 在中央目录中
		文件标志_中心目录 = ZIP_FL_CENTRAL,
		//@备注 压缩包::添加文件：如果存在 name 的文件，则覆盖 （替换） 它
		文件标志_覆盖 = ZIP_FL_OVERWRITE
	};

	//@备注 压缩包使用的加密方法
	enum 加密方法
	{
		加密方法_无 = ZIP_EM_NONE,					//@备注 未加密
		加密方法_TRAD_PKWARE = ZIP_EM_TRAD_PKWARE,	//@备注 传统的 PKWARE 加密
		加密方法_AES128 = ZIP_EM_AES_128,			//@备注 Winzip AES 加密
		加密方法_AES192 = ZIP_EM_AES_192,
		加密方法_AES256 = ZIP_EM_AES_256
	};

	//@备注 压缩包使用的压缩方法
	enum 压缩方法
	{
		压缩方法_默认 = ZIP_CM_DEFAULT,		//@备注 默认值压缩
		压缩方法_储存 = ZIP_CM_STORE,		//@备注 保存未压缩的文件
		压缩方法_BZIP2 = ZIP_CM_BZIP2,		//@备注 使用bzip2压缩文件 算法。
		压缩方法_DEFLATE = ZIP_CM_DEFLATE,	//@备注 使用zlib压缩文件 算法和默认选项。
		压缩方法_XZ = ZIP_CM_XZ,				//@备注 使用xz算法 压缩
		压缩方法_ZSTD = ZIP_CM_ZSTD			//@备注 使用zstd算法 压缩
	};

	//@备注 压缩包操作返回的错误代码
	enum 错误代码
	{
		错误代码_成功 = ZIP_ER_OK,
		//@备注 不支持多磁盘 zip 存档
		错误代码_多磁盘 = ZIP_ER_MULTIDISK,
		//@备注 重命名临时文件失败
		错误代码_重命名 = ZIP_ER_RENAME,
		//@备注 关闭 zip 存档失败
		错误代码_关闭 = ZIP_ER_CLOSE,
		//@备注 移动读写位置错误
		错误代码_移动 = ZIP_ER_SEEK,
		//@备注 读取错误
		错误代码_读取 = ZIP_ER_READ,
		//@备注 写入错误
		错误代码_写入 = ZIP_ER_WRITE,
		//@备注 CRC错误
		错误代码_CRC = ZIP_ER_CRC,
		//@备注 包含 zip 存档已关闭
		错误代码_ZIP已关闭 = ZIP_ER_ZIPCLOSED,
		//@备注 没有这样的条目
		错误代码_无条目 = ZIP_ER_NOENT,
		//@备注 文件已存在
		错误代码_已存在 = ZIP_ER_EXISTS,
		//@备注 无法打开文件
		错误代码_打开 = ZIP_ER_OPEN,
		//@备注 无法创建临时文件
		错误代码_临时文件打开 = ZIP_ER_TMPOPEN,
		//@备注 ZLIB错误
		错误代码_ZLIB = ZIP_ER_ZLIB,
		//@备注 申请内存失败
		错误代码_内存 = ZIP_ER_MEMORY,
		//@备注 条目已更改
		错误代码_已改变 = ZIP_ER_CHANGED,
		//@备注 不支持压缩方法
		错误代码_压缩不支持 = ZIP_ER_COMPNOTSUPP,
		//@备注 文件提前结束
		错误代码_文件尾 = ZIP_ER_EOF,
		//@备注 无效参数
		错误代码_无效参数 = ZIP_ER_INVAL,
		//@备注 不是 zip 压缩包
		错误代码_不是ZIP = ZIP_ER_NOZIP,
		//@备注 内部错误
		错误代码_内部 = ZIP_ER_INTERNAL,
		//@备注 Zip 压缩包不一致
		错误代码_不一致 = ZIP_ER_INCONS,
		//@备注 无法删除文件
		错误代码_移除 = ZIP_ER_REMOVE,
		//@备注 无法删除文件
		错误代码_已删除 = ZIP_ER_DELETED,
		//@备注 加密方法不受支持
		错误代码_加密不支持 = ZIP_ER_ENCRNOTSUPP,
		//@备注 只读压缩包
		错误代码_只读 = ZIP_ER_RDONLY,
		//@备注 未提供密码
		错误代码_无密码 = ZIP_ER_NOPASSWD,
		//@备注 提供的密码错误
		错误代码_错误密码 = ZIP_ER_WRONGPASSWD,
		//@备注 不支持该操作
		错误代码_操作不支持 = ZIP_ER_OPNOTSUPP,
		//@备注 资源仍在使用中
		错误代码_在使用 = ZIP_ER_INUSE,
		//@备注 取读写位置错误
		错误代码_取位置 = ZIP_ER_TELL,
		//@备注 压缩数据无效
		错误代码_压缩数据 = ZIP_ER_COMPRESSED_DATA,
		//@备注 操作取消
		错误代码_已取消 = ZIP_ER_CANCELLED,
		//@备注 数据长度异常
		错误代码_数据长度 = ZIP_ER_DATA_LENGTH,
		//@备注 torrentzip 中不允许
		错误代码_不允许 = ZIP_ER_NOT_ALLOWED,
		//@备注 压缩包可能被截断或损坏
		错误代码_截断ZIP = ZIP_ER_TRUNCATED_ZIP
	};

	/*@声明
	
	#define ZIP_OPSYS_DOS 0x00u
	#define ZIP_OPSYS_AMIGA 0x01u
	#define ZIP_OPSYS_OPENVMS 0x02u
	#define ZIP_OPSYS_UNIX 0x03u
	#define ZIP_OPSYS_VM_CMS 0x04u
	#define ZIP_OPSYS_ATARI_ST 0x05u
	#define ZIP_OPSYS_OS_2 0x06u
	#define ZIP_OPSYS_MACINTOSH 0x07u
	#define ZIP_OPSYS_Z_SYSTEM 0x08u
	#define ZIP_OPSYS_CPM 0x09u
	#define ZIP_OPSYS_WINDOWS_NTFS 0x0au
	#define ZIP_OPSYS_MVS 0x0bu
	#define ZIP_OPSYS_VSE 0x0cu
	#define ZIP_OPSYS_ACORN_RISC 0x0du
	#define ZIP_OPSYS_VFAT 0x0eu
	#define ZIP_OPSYS_ALTERNATE_MVS 0x0fu
	#define ZIP_OPSYS_BEOS 0x10u
	#define ZIP_OPSYS_TANDEM 0x11u
	#define ZIP_OPSYS_OS_400 0x12u
	#define ZIP_OPSYS_OS_X 0x13u

	#define ZIP_OPSYS_DEFAULT ZIP_OPSYS_UNIX

	*/
	
	const zip_int64_t 长度_到结尾 = ZIP_LENGTH_TO_END;
	const zip_int64_t 长度_不检查 = ZIP_LENGTH_UNCHECKED;

	const zip_uint16_t 额外字段_全部 = ZIP_EXTRA_FIELD_ALL;
	const zip_uint16_t 额外字段_新建 = ZIP_EXTRA_FIELD_NEW;

	enum 移动位置
	{
		移动位置_文件首 = SEEK_SET,
		移动位置_当前 = SEEK_CUR,
		移动位置_文件尾 = SEEK_END,
	};


	//@分组} 枚举常量

	//@分组{ 全局函数

	//@备注 获取版本信息
	const char* 取版本();

	//@备注 是否支持压缩或解压方法
	//@参数 method 压缩方法
	//@参数 compress 0. 表示压缩; 1. 表示解压
	//@返回 
	BOOL 是否支持压缩方法(__in 压缩方法 method, __in int compress);

	//@备注 是否支持加密或解密方法
	//@参数 method 加密方法
	//@参数 encrypt 0. 表示加密; 1. 表示解密
	//@返回 
	BOOL 是否支持加密方法(__in 加密方法 method, __in int encrypt);

	//@分组} 全局函数

	//@隐藏{
	class 压缩包;
	class 数据源;
	//@隐藏}

	//@分组{ 类

	//@备注 表示有关错误的信息。
	class 错误 : public zip_error_t
	{
	public:
		错误();

		//@隐藏{

		错误(const 错误&) = delete;
		错误& operator=(const 错误&) = delete;
		~错误();
		//@隐藏}
		
		//@备注 通常不需要自己调用
		void 释放();

		//@备注 要找出报告了这个错误的系统，请使用 取系统类型（）。
		//@返回 返回错误的系统特定部分。
		int 取代码系统() const;

		//@返回 返回 错误 中系统特定部分的类型
		错误系统类型 取系统类型() const;

		//@返回 返回 libzip 特定的错误部分。
		错误代码 取代码() const;

		//@返回 返回错误消息文本
		const char* 取文本() const;
	};

	//@备注  压缩包中条目的一些基本信息
	class 条目信息 : public zip_stat_t
	{
	public:
		条目信息();

		//@备注 获取条目名称, 如果是目录以/结尾
		const char* 取名称() const;
		//@备注 获取条目索引
		zip_uint64_t 取索引() const;

		//@备注 获取未压缩字节大小
		zip_uint64_t 取大小() const;
		//@备注 获取压缩后字节大小
		zip_uint64_t 取压缩大小() const;

		//@备注 获取最后修改时间
		time_t 取修改时间() const;

		//@备注 获取文件CRC
		zip_uint32_t 取CRC() const;

		//@备注 获取文件压缩方法
		压缩方法 取压缩方法() const;

		//@备注 获取文件加密方法
		加密方法 取加密方法() const;
	};



	//@备注 用于加载文件或内存数据的统一处理的类
	class 数据源
	{
		//@隐藏{
		friend class 压缩包;
		
	private:
		zip_source_t* m_zip_src;
		//@隐藏}
	public:
		数据源(__in LPVOID src = NULL);
		~数据源();

		//@隐藏{
		数据源(const 数据源& other);
		数据源& operator=(const 数据源& other);
		
		数据源(数据源&& other) noexcept;
			
		数据源& operator=(数据源&& other) noexcept;
		
		operator bool();
		//@隐藏}

		//@备注 获取内部指针
		const LPVOID 取指针() const;

		//@备注 增加引用计数, 一般别用
		void 增加引用();

		//@备注 从内存创建
		//@参数 data 内存指针
		//@参数 len 内存长度
		//@参数 isCopy 是否复制内存, 如果为真，则内部会拷贝一份副本, 否则数据必须保证生命周期。
		//@参数 error 错误对象
		BOOL 创建自内存(__in const void* data, __in zip_uint64_t len, __in BOOL isCopy = FALSE, __in 错误* error = NULL);

		//@备注 从字节集创建
		//@参数 bytes 字节集
		//@参数 isCopy 是否复制内存, 如果 isCopy 为真，则内部会拷贝一份副本, 否则数据必须在创建的源的整个生命周期内保持有效。
		//@参数 error 错误对象
		BOOL 创建自字节集(__in const CXBytes& bytes, __in BOOL isCopy = FALSE, __in 错误* error = NULL);

		//@备注 从文件创建.
		//@参数 filename 文件名,UTF-8
		//@参数 start 起始偏移位置
		//@参数 len 长度, 如果传递 长度到结尾, 则到文件末尾; 如果传递 长度_不检查 表示长度未知.
		//@参数 如果源文件在创建时已知其大小，libzip 可以进行各种优化，因此 长度_到结尾 是更佳选择。
		//@参数 如果您处理的文件在处理过程中可能会发生变化，则可以使用效率较低的 长度_不检查。
		//@参数 error 错误对象指针
		BOOL 创建自文件名U8(__in const char* filename, __in zip_uint64_t start = 0, __in zip_int64_t len = 长度_到结尾, __in 错误* error = NULL);

		//@备注 从文件创建.
		//@参数 filep 文件对象
		//@参数 start 起始偏移位置
		//@参数 len 长度, 如果传递 长度_到结尾, 则到文件末尾; 如果传递 长度_不检查 表示长度未知.
		//@参数 如果源文件在创建时已知其大小，libzip 可以进行各种优化，因此 长度_到结尾 是更佳选择。
		//@参数 如果您处理的文件在处理过程中可能会发生变化，则可以使用效率较低的 长度_不检查。
		//@参数 error 错误对象指针
		BOOL 创建自文件(__in CXFile& filep, __in zip_uint64_t start = 0, __in zip_int64_t len = 长度_到结尾, __in 错误* error = NULL);

		//@备注 从文件创建.
		//@参数 hFile Windows 文件句柄
		//@参数 start 起始偏移位置
		//@参数 len 长度, 如果传递 长度_到结尾, 则到文件末尾; 如果传递 长度_不检查 表示长度未知.
		//@参数 如果源文件在创建时已知其大小，libzip 可以进行各种优化，因此 长度_到结尾 是更佳选择。
		//@参数 如果您处理的文件在处理过程中可能会发生变化，则可以使用效率较低的 长度_不检查。
		//@参数 error 错误对象指针
		BOOL 创建自文件句柄(__in void* hFile, __in zip_uint64_t start = 0, __in zip_int64_t len = 长度_到结尾, __in 错误* error = NULL);

		//@备注 从 Windows ANSI 文件名创建数据源
		//@参数 filename 文件名, Window Ansi编码
		//@参数 start 起始偏移位置
		//@参数 len 长度, 如果传递 长度_到结尾, 则到文件末尾; 如果传递 长度_不检查 表示长度未知.
		//@参数 如果源文件在创建时已知其大小，libzip 可以进行各种优化，因此 长度_到结尾 是更佳选择。
		//@参数 如果您处理的文件在处理过程中可能会发生变化，则可以使用效率较低的 长度_不检查。
		//@参数 error 错误对象指针
		BOOL 创建自文件名A(__in const char* filename, __in zip_uint64_t start = 0, __in zip_int64_t len = 长度_到结尾, __in 错误* error = NULL);

		//@备注 从 Windows Unicode 文件名创建数据源
		//@参数 filename 文件名
		//@参数 start 起始偏移位置
		//@参数 len 长度, 如果传递 长度_到结尾, 则到文件末尾; 如果传递 长度_不检查 表示长度未知.
		//@参数 如果源文件在创建时已知其大小，libzip 可以进行各种优化，因此 长度_到结尾 是更佳选择。
		//@参数 如果您处理的文件在处理过程中可能会发生变化，则可以使用效率较低的 长度_不检查。
		//@参数 error 错误对象指针
		BOOL 创建自文件名(__in const wchar_t* filename, __in zip_uint64_t start = 0, __in zip_int64_t len = 长度_到结尾, __in 错误* error = NULL);

		


		//@备注 减少引用计数, 如果已经加入到 zip , 则不要释放. 也就是说, zip.添加(zip数据源) 失败时, 才释放
		void 释放();

		//@备注 准备写入源文件。这通常涉及创建临时文件或分配缓冲区。
		//@返回 
		BOOL 开始写入();

		//@备注 准备写入源文件。在 提交写入() 之前, 不会覆盖原始数据
		//@参数 offset 源数据源的偏移
		//@返回 
		BOOL 开始写入克隆(__in zip_uint64_t offset = 0);

		//@备注 打开数据源进行读
		//@返回 
		BOOL 打开();

		//@备注 关闭打开的数据源
		//@返回 
		BOOL 关闭();

		//@备注 完成将数据写入源，并用新写入的数据替换原始数据。
		//@返回 
		BOOL 提交写入();

		//@备注 还原写入源的更改，恢复调用 开始写入() 之前的数据。通常，这会删除临时文件或释放缓冲区。
		void 回滚写入();

		//@备注 返回数据源源的 zip 错误。
		//@返回 
		const 错误* 取错误() const;

		//@备注 例如，当从 zip 存档中删除所有条目时，就会发生这种情况。
		//@返回 
		BOOL 是否已删除();

		//@备注 检测数据源, 是否支持移动读写位置
		//@返回 
		BOOL 是否可移动();

		//@备注 在当前读取偏移量处读取最多 len 字节的数据到缓冲区数据中。
		//@备注 必须先调用 打开（） 打开源以供读取。
		//@参数 data 缓冲区
		//@参数 len 缓冲区大小
		//@返回 成功完成后，将返回读取的字节数。当在到达文件末尾后调用时，将返回 0。
		//@返回 否则，返回 -1，并设置 数据源 中的错误信息以指示错误。
		zip_int64_t 读取(__out void* data, __in zip_uint64_t len);

		//@备注 将缓冲区数据中的 len 字节写入当前写入偏移量的 zip数据源。
		//@备注 zip 源码必须首先调用 开始写入() 来准备写入。
		//@参数 data 缓冲区
		//@参数 len 缓冲区大小
		//@返回 返回实际写入大小, -1 表示错误
		zip_int64_t 写入(__in const void* data, __in zip_uint64_t len);

		//@备注 一次读取全部数据
		//@参数 data 保存读取的数据
		//@返回 成功返回 true
		BOOL 读取数据(__out CXBytes& data);

		//@备注 一次读取全部数据
		//@参数 str 保存读取的数据
		//@返回 成功返回 true
		BOOL 读取文本(__out CXTextA& str);

		//@备注 一次写入全部数据
		//@参数 data 要写入的数据指针
		//@参数 len 要写入的数据长度
		//@返回 成功返回 true
		BOOL 写入数据(__in const void* data, __in zip_uint64_t len);

		//@备注 一次写入全部数据
		//@参数 str 要写入的字符串
		//@返回 成功返回 true
		BOOL 写入文本(__in const CXTextA& str);

		//@备注 设置 数据源 的当前读取偏移量。
		//@参数 offset 偏移
		//@参数 whence 
		//@返回 
		BOOL 移动读位置(__in zip_int64_t offset, __in 移动位置 whence = 移动位置_文件首);

		//@备注 返回 数据源 的当前读取偏移量。
		//@返回 
		zip_int64_t 取读位置() const;

		//@备注 设置 数据源 的当前写入偏移量。
		//@参数 offset 偏移
		//@参数 whence 
		//@返回 
		BOOL 移动写位置(__in zip_int64_t offset, __in 移动位置 whence = 移动位置_文件首);

		//@备注 返回 数据源 的当前写入偏移量。
		//@返回 
		zip_int64_t 取写位置() const;

		//@备注 获取源的信息
		//@参数 sb 
		//@返回 
		BOOL 取信息(__out 条目信息* sb);

		//@备注 获取数据源的部分, 返回新的数据源
		数据源 取子数据源(__in zip_uint64_t start, __in zip_int64_t len = -1, __in 错误* error = NULL);
	};

	//@备注 表示压缩包中文件的对象
	class 文件
	{
		//@隐藏{
	private:
		zip_file_t* m_file;
		//@隐藏}
	public:
		文件(LPVOID pfile = NULL);

		~文件();

		//@隐藏{
		operator bool();

		//@隐藏}

		//@备注 获取内部指针
		const LPVOID 取指针() const;

		
		//@备注 关闭文件, 一定要手动关闭
		BOOL 关闭();

		/// @备注 从文件中的当前位置读取最多 nbytes 字节的文件到 buf 中。读取后，当前位置将按读取的字节数更新。
		/// @参数 buf 缓冲区
		/// @参数 nbytes 字节数
		/// @返回 如果成功，则返回实际读取的字节数。当在到达文件末尾后调用时，将返回 0。如果出现错误，则返回 -1。
		zip_int64_t 读取(__out void* buf, __in zip_uint64_t nbytes);

		/// @备注 从当前位置读取到末尾
		/// @param data 用于保存数据的字节集
		/// @return 
		BOOL 读取数据(__out CXBytes& data);

		/// @备注 从当前位置读取到末尾
		/// @参数 str 用于保存数据的文本
		/// @返回 
		BOOL 读取文本(__out CXTextA& str);

		/// @备注 仅适用于未压缩（存储）、未加密的数据。当对压缩或加密数据调用时，它将返回错误。
		/// @参数 offset 偏移
		/// @参数 whence 从何处
		/// @返回 
		BOOL 移动位置(__in zip_int64_t offset, __in 移动位置 whence = 移动位置_文件首);

		/// @备注 检查是否支持移动读取位置
		/// @返回 
		BOOL 是否可移动() const;

		/// @备注 获取当前读取位置
		/// @返回 
		zip_int64_t 取位置() const;

		/// @备注 获取错误
		/// @返回 
		const 错误* 取错误() const;

		/// @备注 清除错误状态
		void 清除错误();

		/// @备注 获取错误文本
		/// @返回 
		const char* 取错误文本() const;
	};


	//@备注 zip 压缩包操作类
	class 压缩包
	{
		//@隐藏{
		friend class 数据源;
	private:
		zip_t* m_zip;
		//@隐藏}
	public:
		压缩包(LPVOID pZip = NULL);

		//@隐藏{
		压缩包(const 压缩包&) = delete;
		压缩包& operator=(const 压缩包&) = delete;
		operator bool();
		//@隐藏}

		//@备注 获取内部指针
		const LPVOID 取指针() const;

		

		//@备注 函数打开由 zipPath 指定的 zip 存档，用于操作存档。
		//@参数 zipPath 压缩包路径, UTF8 编码
		//@参数 flags 这些标志是通过 or 来指定的。
		//@参数 error_code 错误代码
		//@返回 
		BOOL 打开U8(__in const char* zipPath, __in int flags = 打开选项_只读, __in int* error_code = NULL);

		//@备注 从数据源打开
		//@参数 source 压缩包数据源
		//@参数 flags 这些标志是通过 or 来指定的。
		//@参数 error 错误对象指针
		//@返回 
		BOOL 打开自数据源(__in 数据源& source, __in int flags = 打开选项_只读, __in 错误* error = NULL);

		//@备注 从内存中打开
		//@参数 data 压缩包数据指针
		//@参数 len 压缩包数据长度
		//@参数 isCopy 是否拷贝内存, 如果为真则内部会拷贝一份副本, 假则必须保证你的指针的生命周期在压缩包关闭前有效
		//@参数 flags 这些标志是通过 or 来指定的。
		//@参数 error 错误对象指针
		//@返回 
		BOOL 打开自内存(__in const void* data, __in zip_uint64_t len, __in BOOL isCopy = FALSE, __in int flags = 打开选项_只读, __in 错误* error = NULL);

		//@备注 从字节集中打开
		//@参数 bytes 压缩包数据字节集
		//@参数 isCopy 是否拷贝内存, 如果为真则内部会拷贝一份副本, 假则必须保证你的指针的生命周期在压缩包关闭前有效
		//@参数 flags 这些标志是通过 or 来指定的。
		//@参数 error 错误对象指针
		//@返回 
		BOOL 打开自字节集(__in const CXBytes& bytes, __in BOOL isCopy = FALSE, __in int flags = 打开选项_只读, __in 错误* error = NULL);

		//@备注 从文件打开
		//@参数 source 压缩包数据源
		//@参数 flags 这些标志是通过 or 来指定的。
		//@参数 error 错误对象指针
		//@返回 
		BOOL 打开(__in const wchar_t* zipPath, __in int flags = 打开选项_只读, __in 错误* error = NULL);

		//@备注 从文件打开
		//@参数 source 压缩包数据源
		//@参数 flags 这些标志是通过 or 来指定的。
		//@参数 error 错误对象指针
		//@返回 
		BOOL 打开A(__in const char* zipPath, __in int flags = 打开选项_只读, __in 错误* error = NULL);

		//@备注 函数将对存档所做的任何更改写入磁盘。如果 存档 不包含任何文件，
		//@备注 则完全删除该文件（不会写入空 存档），除非设置了 存档 标志::创建或保留文件以空存档。
		//@备注 如果成功，则释放存档。
		//@备注 否则，存档将保持不变，仍必须释放。
		//@返回 返回错误代码
		错误代码 关闭();

		//@备注 关闭存档并释放为其分配的内存。对存档所做的任何更改都不会写入磁盘并丢弃。
		void 丢弃();

		//@备注 为 zip 中的加密文件设置默认密码.
		//@备注 应该在添加文件 或 读取文件 之前调用
		//@参数 password 密码
		//@返回 
		BOOL 置默认密码(__in const char* password);

		//@备注 将文件添加到 zip 压缩包
		//@参数 name 在压缩包中的名称
		//@参数 source 被添加的数据源, 添加后此数据源对象将无法操作(内部已经将指针 = NULL)
		//@参数 flags 添加标志. 支持以下标志:
		// 文件标志_覆盖
		// 文件标志_编码猜测
		// 文件标志_编码UTF8
		// 文件标志_编码CP437
		// 成功返回新文件的索引，失败返回 -1
		zip_int64_t 添加文件自数据源(__in const char* name, __in 数据源& source, __in int flags = 文件标志_编码UTF8 | 文件标志_覆盖);

		//@备注 将文件添加到 zip 压缩包
		//@参数 name 在压缩包中的名称. UTF-8编码
		//@参数 fileName 被添加的文件名
		//@参数 flags 添加标志. 支持以下标志:
		// 文件标志_覆盖
		// 文件标志_编码猜测
		// 文件标志_编码UTF8
		// 文件标志_编码CP437
		//@参数 error 错误对象指针
		//@返回 成功返回新文件的索引，失败返回 -1
		zip_int64_t 添加文件(__in const char* name, __in const wchar_t* fileName, __in int flags = 文件标志_编码UTF8 | 文件标志_覆盖, __in 错误* error = NULL);

		//@备注 将文件添加到 zip 压缩包
		//@参数 name 在压缩包中的名称. UTF-8编码
		//@参数 fileName 被添加的文件名, utf8编码
		//@参数 flags 添加标志. 支持以下标志:
		// 文件标志_覆盖
		// 文件标志_编码猜测
		// 文件标志_编码UTF8
		// 文件标志_编码CP437
		//@参数 error 错误对象指针
		//@返回 成功返回新文件的索引，失败返回 -1
		zip_int64_t 添加文件U8(__in const char* name, __in const char* fileName, __in int flags = 文件标志_编码UTF8 | 文件标志_覆盖, __in 错误* error = NULL);

		//@备注 将文件添加到 zip 压缩包
		//@参数 name 在压缩包中的名称.UTF-8编码
		//@参数 fileName 被添加的文件名, Windows Ansi 编码
		//@参数 flags 添加标志. 支持以下标志:
		// 文件标志_覆盖
		// 文件标志_编码猜测
		// 文件标志_编码UTF8
		// 文件标志_编码CP437
		//@参数 error 错误对象指针
		//@返回 成功返回新文件的索引，失败返回 -1
		zip_int64_t 添加文件A(__in const char* name, __in const char* fileName, __in int flags = 文件标志_编码UTF8 | 文件标志_覆盖, __in 错误* error = NULL);

		//@备注 将内存数据添加到 zip 压缩包
		//@参数 name 在压缩包中的名称.UTF-8编码
		//@参数 data 要添加的数据指针
		//@参数 len 数据长度
		//@参数 isCopy 是否复制内存, 如果为真，则内部会拷贝一份副本, 否则数据必须保证生命周期。
		//@参数 flags 添加标志. 支持以下标志:
		// 文件标志_覆盖
		// 文件标志_编码猜测
		// 文件标志_编码UTF8
		// 文件标志_编码CP437
		//@参数 error 错误对象指针
		//@返回 
		zip_int64_t 添加文件自内存(__in const char* name, __in const void* data, __in zip_uint64_t len, BOOL isCopy = FALSE, int flags = 文件标志_编码UTF8 | 文件标志_覆盖, __in 错误* error = NULL);

		//@备注 将内存数据添加到 zip 压缩包
		//@参数 name 在压缩包中的名称.UTF-8编码
		//@参数 data 要添加的数据
		//@参数 isCopy 是否复制内存, 如果为真，则内部会拷贝一份副本, 否则数据必须保证生命周期。
		//@参数 flags 添加标志. 支持以下标志:
		// 文件标志_覆盖
		// 文件标志_编码猜测
		// 文件标志_编码UTF8
		// 文件标志_编码CP437
		//@参数 error 错误对象指针
		//@返回 
		zip_int64_t 添加文件自字节集(__in const char* name, __in const CXBytes& data, BOOL isCopy = FALSE, int flags = 文件标志_编码UTF8 | 文件标志_覆盖, __in 错误* error = NULL);

		

		//@备注 将数据源替换到 zip 压缩包中的指定条目
		//@参数 index 压缩包中的条目索引
		//@参数 source 数据源
		//@参数 flags 替换标志.支持以下标志:
		// 文件标志_覆盖
		// 文件标志_编码猜测
		// 文件标志_编码UTF8
		// 文件标志_编码CP437
		//@返回 
		BOOL 替换文件自数据源(zip_uint64_t index, 数据源& source, int flags = 文件标志_编码UTF8);

		//@备注 将文件替换到 zip 压缩包中的指定条目
		//@参数 index 压缩包中的条目索引
		//@参数 fileName 用作替换的文件名
		//@参数 flags 替换标志支持以下标志:
		// 文件标志_覆盖
		// 文件标志_编码猜测
		// 文件标志_编码UTF8
		// 文件标志_编码CP437
		//@参数 error 错误对象指针
		//@返回 
		BOOL 替换文件(__in zip_uint64_t index, __in const wchar_t* fileName, __in int flags = 文件标志_编码UTF8, __in 错误* error = NULL);

		//@备注 将文件替换到 zip 压缩包中的指定条目
		//@参数 index 压缩包中的条目索引
		//@参数 fileName 用作替换的文件名, 编码 utf8
		//@参数 flags 替换标志. 支持以下标志:
		// 文件标志_覆盖
		// 文件标志_编码猜测
		// 文件标志_编码UTF8
		// 文件标志_编码CP437
		//@参数 error 错误对象指针
		//@返回 
		BOOL 替换文件U8(__in zip_uint64_t index, __in const char* fileName, __in int flags = 文件标志_编码UTF8, __in 错误* error = NULL);

		//@备注 将内存数据替换到 zip 压缩包中的指定条目
		//@参数 index 压缩包中的条目索引
		//@参数 data 数据指针
		//@参数 len 数据长度
		//@参数 isCopy 是否复制内存, 如果为真，则内部会拷贝一份副本, 否则数据必须保证生命周期。
		//@参数 flags 替换标志. 支持以下标志:
		// 文件标志_覆盖
		// 文件标志_编码猜测
		// 文件标志_编码UTF8
		// 文件标志_编码CP437
		//@参数 error 错误对象指针
		//@返回 
		BOOL 替换文件自内存(__in zip_uint64_t index, __in const void* data, __in zip_uint64_t len, __in BOOL isCopy = FALSE, __in int flags = 文件标志_编码UTF8, __in 错误* error = NULL);

		//@备注 将内存数据替换到 zip 压缩包中的指定条目
		//@参数 index 压缩包中的条目索引
		//@参数 data 数据
		//@参数 isCopy 是否复制内存, 如果为真，则内部会拷贝一份副本, 否则数据必须保证生命周期。
		//@参数 flags 替换标志. 支持以下标志:
		// 文件标志_覆盖
		// 文件标志_编码猜测
		// 文件标志_编码UTF8
		// 文件标志_编码CP437
		//@参数 error 错误对象指针
		//@返回 
		BOOL 替换文件自字节集(__in zip_uint64_t index, __in const CXBytes& data, __in BOOL isCopy = FALSE, __in int flags = 文件标志_编码UTF8, __in 错误* error = NULL);

		//@备注 将文件替换到 zip 压缩包中的指定条目
		//@参数 index 压缩包中的条目索引
		//@参数 fileName 用作替换的文件名,编码 Windows Ansi
		//@参数 flags 替换标志. 支持以下标志:
		// 文件标志_覆盖
		// 文件标志_编码猜测
		// 文件标志_编码UTF8
		// 文件标志_编码CP437
		//@参数 error 错误对象指针
		//@返回 
		BOOL 替换文件A(__in zip_uint64_t index, __in const char* fileName, __in int flags = 文件标志_编码UTF8, __in 错误* error = NULL);

		//@备注 添加目录到压缩包
		//@参数 name 在压缩包中的名称
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_编码猜测
		// 文件标志_编码UTF8
		// 文件标志_编码CP437
		//@返回 
		zip_int64_t 添加目录(__in const char* name, __in int flags = 文件标志_编码UTF8);

		//@备注 从 zip 压缩包中删除文件
		//@参数 index 索引
		//@返回 
		BOOL 删除(__in zip_uint64_t index);

		//@备注 撤消对 zip 压缩包中的文件的更改
		//@参数 index 
		//@返回 
		BOOL 撤销改变(__in zip_uint64_t index);

		//@备注 撤消 zip 压缩包中的所有文件更改
		//@返回 
		BOOL 撤销全部改变();

		//@备注 撤消对 zip 压缩包的全局更改
		//@返回 
		BOOL 撤销压缩包();

		//@备注 函数清除 zip 压缩包文件的错误状态。
		void 清除错误();

		//@备注 从当前zip提取某个文件(或文件片段)为数据源
		//@参数 srcidx 源条目索引
		//@参数 pTargetZip 目标zip, 后续加入到此zip中. 如果为 NULL 则为当前压缩包
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_压缩
		// 文件标志_加密
		// 文件标志_未改变
		//@参数 start 起始偏移
		//@参数 length 长度, -1 表示整个文件
		//@参数 password 加密文件的解压密码
		//@返回 
		数据源 取文件源2(__in zip_uint64_t srcidx, __in const 压缩包* pTargetZip = NULL, __in int flags = 文件标志_无, __in zip_uint64_t start = 0, __in zip_int64_t length = -1, __in const char* password = NULL);

		//@备注 从当前zip提取某个文件(或文件片段)为数据源
		//@参数 srcidx 源条目索引
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_压缩
		// 文件标志_加密
		//@参数 start 起始偏移
		//@参数 length 长度, -1 表示整个文件
		//@参数 password 加密文件的解压密码
		//@参数 error 错误对象指针
		//@返回 
		数据源 取文件源(__in zip_uint64_t srcidx, __in int flags = 文件标志_无, __in zip_uint64_t start = 0, __in zip_int64_t length = -1, __in const char* password = NULL, __in 错误* error = NULL);

		//@备注 重命名文件
		//@参数 index 索引
		//@参数 name 新名称
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_编码猜测
		// 文件标志_编码UTF8
		// 文件标志_编码CP437
		//@返回 
		BOOL 重命名(__in zip_uint64_t index, __in const char* name, __in int flags = 文件标志_编码UTF8);

		//@备注 获取压缩包中指定名称的条目信息
		//@参数 fname 名称
		//@参数 sb 信息指针
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_忽略大小写
		// 文件标志_忽略目录
		// 文件标志_编码猜测
		// 文件标志_编码原始
		// 文件标志_编码严格
		// 文件标志_编码CP437
		// 文件标志_编码UTF8
		// 文件标志_未改变
		//@返回 
		BOOL 取信息自名称(__in const char* fname, __out 条目信息* sb, int flags = 文件标志_编码UTF8);

		//@备注 获取压缩包中指定索引的条目信息
		//@参数 index 索引
		//@参数 sb 信息指针
		//@参数 flags 标志. 支持以下标志:
		//@参数 zip_文件标志_未改变
		//@返回 
		BOOL 取信息(__in zip_uint64_t index, __out 条目信息* sb, int flags = 文件标志_编码UTF8);

		//@备注 获取条目数
		//@参数 flags 如果设置了 zip_文件标志_未改变, 则返回最初打开时的条目数量（忽略任何未保存的更改，即忽略内存中尚未写入的添加或删除操作）。
		//@返回 
		zip_int64_t 取条目数(__in int flags = 文件标志_无);

		//@备注 获取条目名称
		//@参数 index 索引
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_编码原始
		// 文件标志_编码猜测
		// 文件标志_编码严格
		// 文件标志_未改变
		//@返回 
		const char* 取名称(__in zip_uint64_t index, __in int flags = 文件标志_编码猜测);

		//@备注 返回 压缩包 中名为 fname 的文件的索引。
		//@参数 fname 名称
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_忽略大小写
		// 文件标志_忽略目录
		// 文件标志_编码猜测
		// 文件标志_编码原始
		// 文件标志_编码严格
		// 文件标志_编码CP437
		// 文件标志_编码UTF8
		//@返回 失败返回 -1
		zip_int64_t 取索引(__in const char* fname, __in int flags = 文件标志_编码UTF8);


		//@备注 打开 zip 压缩包中的加密文件以供读取
		//@参数 fname 文件名
		//@参数 password 密码
		//@参数 flags 标志.支持以下标志:
		// 文件标志_忽略大小写
		// 文件标志_忽略目录
		// 文件标志_编码猜测
		// 文件标志_编码原始
		// 文件标志_编码严格
		// 文件标志_编码CP437
		// 文件标志_编码UTF8
		// 文件标志_压缩
		// 文件标志_未改变
		//@返回 
		文件 打开文件自名称(__in const char* fname, __in const char* password = NULL, __in int flags = 文件标志_编码UTF8);

		//@备注 打开 zip 压缩包中的加密文件以供读取
		//@参数 index 文件索引
		//@参数 password 密码
		//@参数 flags 标志.支持以下标志:
		// 文件标志_压缩
		// 文件标志_未改变
		//@返回 
		文件 打开文件(__in zip_uint64_t index, __in const char* password = NULL, __in int flags = 文件标志_编码UTF8);

		//@备注 删除文件额外字段
		//@参数 index 文件索引
		//@参数 extra_field_index 额外字段索引, 额外字段_全部 表示删除全部
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_本地头
		// 文件标志_中心目录
		//@返回 
		BOOL 删除文件额外字段(__in zip_uint64_t index, __in zip_uint16_t extra_field_index = 额外字段_全部, __in int flags = 文件标志_无);

		//@备注 删除文件额外字段自ID
		//@参数 index 文件索引
		//@参数 extra_field_id 额外字段ID
		//@参数 extra_field_index 额外字段索引, 额外字段_全部 表示删除全部
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_本地头
		// 文件标志_中心目录
		//@返回 
		BOOL 删除文件额外字段自ID(__in zip_uint64_t index, __in zip_uint16_t extra_field_id, __in zip_uint16_t extra_field_index = 额外字段_全部, __in int flags = 文件标志_无);

		//@备注 获取文件额外字段
		//@参数 index 文件索引
		//@参数 extra_field_index 额外字段索引
		//@参数 idp 如果提供指针, 则保存字段ID
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_本地头
		// 文件标志_中心目录
		// 文件标志_未改变
		//@返回 额外字段的数据
		CXBytes 取文件额外字段(__in zip_uint64_t index, __in zip_uint16_t extra_field_index, __out zip_uint16_t* idp = NULL, __in int flags = 文件标志_无);

		//@备注 获取文件额外字段自ID
		//@参数 index 文件索引
		//@参数 extra_field_id 额外字段ID
		//@参数 extra_field_index 额外字段索引
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_本地头
		// 文件标志_中心目录
		// 文件标志_未改变
		//@返回 额外字段的数据
		CXBytes 取文件额外字段自ID(__in zip_uint64_t index, __in zip_uint16_t extra_field_id, __in zip_uint16_t extra_field_index, __in int flags = 文件标志_无);

		//@备注 在 zip 压缩包中 index 位置为文件设置 ID 为 （双字节签名） extra_field_id 和 index extra_field_index的额外字段。额外字段的数据将设置为 extra_field_data 。如果应追加新条目，请将 extra_field_index 设置为 额外字段_新建。
		//@参数 index 文件索引
		//@参数 extra_field_id 额外字段ID
		//@参数 extra_field_index 额外字段索引
		//@参数 extra_field_data 额外字段数据
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_本地头
		// 文件标志_中心目录
		//@返回 
		BOOL 置文件额外字段(__in zip_uint64_t index, __in zip_uint16_t extra_field_id, __in zip_uint16_t extra_field_index, __in const CXBytes& extra_field_data, __in int flags = 文件标志_无);

		//@备注 获取额外字段数
		//@参数 index 文件索引
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_本地头
		// 文件标志_中心目录
		// 文件标志_未改变
		//@返回 额外字段数
		zip_int16_t 取文件额外字段数(__in zip_uint64_t index, __in int flags = 文件标志_无);

		//@备注 获取额外字段数
		//@参数 index 文件索引
		//@参数 extra_field_id 额外字段ID
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_本地头
		// 文件标志_中心目录
		// 文件标志_未改变
		//@返回 额外字段数
		zip_int16_t 取文件额外字段数2(__in zip_uint64_t index, __in zip_uint16_t extra_field_id, __in int flags = 文件标志_无);

		//@备注 获取文件注释
		//@参数 index 文件索引
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_编码原始
		// 文件标志_编码猜测
		// 文件标志_编码严格
		//@返回 
		CXTextA 取文件注释(__in zip_uint64_t index, __in int flags = 文件标志_编码猜测);

		//@备注 设置文件注释
		//@参数 index 文件索引
		//@参数 comment 注释文本
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_编码猜测
		// 文件标志_编码UTF8
		// 文件标志_编码CP437
		//@返回 
		BOOL 置文件注释(__in zip_uint64_t index, __in const char* comment, __in int flags = 文件标志_编码猜测);

		//@备注 获取zip格式文件的额外属性
		//@参数 index 文件索引
		//@参数 opsys 返回的操作系统标识代码, "ZIP_OPSYS_" 开头常量
		//@参数 attributes 返回的文件属性
		//@参数 flags 标志. 支持以下标志:
		// 文件标志_未改变
		//@返回 
		BOOL 取文件额外属性(__in zip_uint64_t index, __out zip_uint8_t* opsys, __out zip_uint32_t* attributes, __in int flags = 文件标志_无);

		//@备注 设置zip格式文件的额外属性
		//@参数 index 文件索引
		//@参数 opsys 操作系统标识代码, "ZIP_OPSYS_" 开头常量
		//@参数 attributes 文件属性
		//@参数 flags 标志. 
		//@返回 
		BOOL 置文件额外属性(__in zip_uint64_t index, __in zip_uint8_t opsys, __in zip_uint32_t attributes, __in int flags = 文件标志_无);

		//@备注 设置 ZIP 中文件的上次修改时间 （MTIME）
		//@参数 index 文件索引
		//@参数 dostime DOS时间
		//@参数 dosdate DOS日期
		//@参数 flags 标志. 目前不支持任何标志
		//@备注 时间字节的值定义如下：
		// 0 - 4
		// 秒除以 2 （1 - 2 = 1， 3 - 4 = 2， ...）
		// 5 - 10
		// 分钟 （0 - 59）
		// 11 - 15
		// 小时 （0 - 23）
		// 日期字节的值定义如下：
		// 0 - 4
		// 每月的某天 （1 - 31）
		// 5 - 8
		// 月（1 月 = 1, 2 月 = 2，...）
		// 9 - 15
		// 与 1980 年的偏移年份 （1980 = 0， 1981 = 1， ...）
		//@返回 
		BOOL 置文件修改时间DOS(__in zip_uint64_t index, __in zip_uint16_t dostime, __in zip_uint16_t dosdate, __in int flags = 文件标志_无);

		//@备注 设置 ZIP 中文件的上次修改时间 （MTIME）
		//@参数 index 文件索引
		//@参数 mtime time_t
		//@参数 flags 标志. 目前不支持任何标志
		//@返回 
		BOOL 置文件修改时间(__in zip_uint64_t index, __in time_t mtime, __in int flags = 文件标志_无);

		//@备注 为 zip 中的文件设置加密方法
		//@参数 index 文件索引
		//@参数 method 加密方法
		//@参数 password 密码, 如果为 NULL, 则使用 置默认密码() 设置的密码
		//@返回 
		BOOL 置文件加密方法(__in zip_uint64_t index, __in 加密方法 method, __in const char* password = NULL);

		//@备注 获取错误描述文本
		//@返回 
		const char* 取错误文本() const;

		//@备注 获取错误
		//@返回 
		const 错误* 取错误() const;

		//@备注 获取zip压缩包注释
		//@参数 flags 标志. 支持以下标志:
		//@参数 zip_文件标志_编码猜测
		//@参数 zip_文件标志_编码UTF8
		//@参数 zip_文件标志_编码CP437
		//@参数 zip_文件标志_未改变
		//@返回 
		CXTextA 取注释(__in int flags = 文件标志_编码猜测);

		//@备注 设置zip压缩包注释
		//@参数 comment 注释
		//@返回 
		BOOL 置注释(__in const char* comment);

		//@备注 获取zip压缩包标志
		//@参数 flag 要检查的标志
		//@参数 flags 查询行为标志, 可以是: zip_文件标志_未改变
		//@返回 返回 true 表示有此标志
		BOOL 取标志(__in int flag, __in int flags = 文件标志_无);

		//@备注 设置zip压缩包标志
		//@参数 flag 要设置的标志
		//@参数 value 0 表示取消, 1 表示设置
		//@返回 
		BOOL 置标志(__in int flag, __in int value);

		//@备注 设置 zip 中文件的压缩方法
		//@参数 index 文件索引
		//@参数 comp 压缩方法
		//@参数 comp_flags 参数定义压缩级别。此值取决于压缩算法。
		//@备注 通常，数字越低表示解压/压缩速度越快，数字越高表示解压/压缩速度越慢。
		//@备注 对于 BZIP、DEFLATE 和 XZ，1 表示压缩速度最快，9 表示压缩速度最佳，0 表示默认压缩。
		//@备注 对于 ZSTD，可能的值为 ZSTD_minCLevel(3) 至 ZSTD_maxCLevel(3)；负值必须转换为 zip_uint32_t 类型。
		//@返回 
		BOOL 置文件压缩方式(__in zip_uint64_t index, __in 压缩方法 comp, __in zip_uint32_t comp_flags = 0);

		//@备注 注册在压缩包 关闭() 时的回调函数, 可用于取消压缩包的写入
		//@参数 callback 当回调函数返回非零值时，写入将被取消，并且 zip_close（3） 将返回错误。
		//@参数 ud_free 用于释放用户数据的函数, 会定期调用（在每个 zip 存档条目完全写入磁盘之后，以及为条目写入数据时）。
		//@参数 ud 用户数据
		void 注册取消回调(取消回调函数 callback, void (*ud_free)(void*) = NULL, void* ud = NULL);

		//@备注 注册处理回调函数(在每个完全写入磁盘的 zip 存档条目之后，以及为条目写入数据时）定期调用
		//@参数 precision 精度 是 0.00 到 1.0 范围内的双精度值，用于定义应调用回调的最小更改（以避免过于频繁的调用）. 简单来说如果设置为 0.01 则每处理1%就触发, 0.1 就处理10%才触发回调
		//@参数 callback 回调函数
		//@参数 ud_free 用于释放用户数据的函数, 会定期调用
		//@参数 ud 用户数据
		void 注册进度回调(double precision, 进度回调函数 callback, void (*ud_free)(void*) = NULL, void* ud = NULL);
	};

	//@分组} 类
}

