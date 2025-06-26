#pragma once

//@模块名称  Detours钩子库
//@版本  1.0.0
//@日期  2023-03-29
//@作者  Bestkakkoii (QQ: 1642687802)
//@模块备注 封装自微软开源项目 Detours
//@依赖  module_base.h

#ifdef _WIN64
#ifdef _DEBUG
//@lib "lib\x64\Debug\detours.lib"
#else
//@lib "lib\x64\Release\detours.lib"
#endif
#else
#ifdef _DEBUG
//@lib "lib\x86\Debug\detours.lib"
#else
//@lib "lib\x86\Release\detours.lib"
#endif
#endif

//  Core Detours Functionality (detours.h of detours.lib)
//
//  Microsoft Research Detours Package, Version 4.0.1
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//


#include <SDKDDKVer.h>
#include <windows.h>
#include <type_traits>
#include "include/detver.h"
#include "include/detours.h"
#include "include/syelog.h"

/*@声明

//@分组{ 钩子调试日誌工具
#define SYELOG_MAXIMUM_MESSAGE  4086    // 4096 - sizeof(header stuff)

typedef struct _SYELOG_MESSAGE
{
    USHORT      nBytes;
    BYTE        nFacility;
    BYTE        nSeverity;
    DWORD       nProcessId;
    FILETIME    ftOccurance;
    BOOL        fTerminate;
    CHAR        szMessage[SYELOG_MAXIMUM_MESSAGE];
} SYELOG_MESSAGE, *PSYELOG_MESSAGE;


// Facility Codes.
//
#define SYELOG_FACILITY_KERNEL          0x10            // OS Kernel
#define SYELOG_FACILITY_SECURITY        0x20            // OS Security
#define SYELOG_FACILITY_LOGGING         0x30            // OS Logging-internal
#define SYELOG_FACILITY_SERVICE         0x40            // User-mode system daemon
#define SYELOG_FACILITY_APPLICATION     0x50            // User-mode application
#define SYELOG_FACILITY_USER            0x60            // User self-generated.
#define SYELOG_FACILITY_LOCAL0          0x70            // Locally defined.
#define SYELOG_FACILITY_LOCAL1          0x71            // Locally defined.
#define SYELOG_FACILITY_LOCAL2          0x72            // Locally defined.
#define SYELOG_FACILITY_LOCAL3          0x73            // Locally defined.
#define SYELOG_FACILITY_LOCAL4          0x74            // Locally defined.
#define SYELOG_FACILITY_LOCAL5          0x75            // Locally defined.
#define SYELOG_FACILITY_LOCAL6          0x76            // Locally defined.
#define SYELOG_FACILITY_LOCAL7          0x77            // Locally defined.
#define SYELOG_FACILITY_LOCAL8          0x78            // Locally defined.
#define SYELOG_FACILITY_LOCAL9          0x79            // Locally defined.

// Severity Codes.
//
#define SYELOG_SEVERITY_FATAL           0x00            // System is dead.
#define SYELOG_SEVERITY_ALERT           0x10            // Take action immediately.
#define SYELOG_SEVERITY_CRITICAL        0x20            // Critical condition.
#define SYELOG_SEVERITY_ERROR           0x30            // Error
#define SYELOG_SEVERITY_WARNING         0x40            // Warning
#define SYELOG_SEVERITY_NOTICE          0x50            // Significant condition.
#define SYELOG_SEVERITY_INFORMATION     0x60            // Informational
#define SYELOG_SEVERITY_AUDIT_FAIL      0x66            // Audit Failed
#define SYELOG_SEVERITY_AUDIT_PASS      0x67            // Audit Succeeeded
#define SYELOG_SEVERITY_DEBUG           0x70            // Debugging

// Logging Functions.
//

//@备注 打开Syelog记录器，开始记录信息
//@参数 pszIdentifier 字符串指针，指定用于标识日志记录器的名称
//@参数 nFacility 表示日志记录的设施代码，用于标识日志来源
//@返回 无返回值
//@别名 Sye打开日誌(记录器的名称, 日志来源标识)
VOID SyelogOpen(PCSTR pszIdentifier, BYTE nFacility);

//@备注 记录日志信息
//@参数 nSeverity 表示日志记录的严重性
//@参数 pszMsgf 字符串指针，指定日志信息的格式
//@参数 ... 可变参数，指定日志信息的参数
//@返回 无返回值
//@别名 Sye记录日誌(日志严重性, 日志信息格式, 其他参数)
VOID Syelog(BYTE nSeverity, PCSTR pszMsgf, ...);

//@备注 记录日志信息
//@参数 nSeverity 表示日志记录的严重性
//@参数 pszMsgf 字符串指针，指定日志信息的格式
//@参数 args 可变参数，指定日志信息的参数
//@返回 无返回值
//@别名 Sye记录日誌V(日志严重性, 日志信息格式, 其他参数)
VOID SyelogV(BYTE nSeverity, PCSTR pszMsgf, va_list args);

//@备注 关闭Syelog记录器，停止记录信息
//@参数 fTerminate 表示是否终止记录器
//@返回 无返回值
//@别名 Sye关闭日誌(是否终止)
VOID SyelogClose(BOOL fTerminate);

//@分组}

//@分组{ 宏定义

//@备注 钩子库版本号
//@别名 钩子库版本号
#define DETOURS_VERSION     0x4c0c1   // 0xMAJORcMINORcPATCH

#if defined(_X86_)
#define DETOURS_X86
#define DETOURS_OPTION_BITS 64

#elif defined(_AMD64_)
#define DETOURS_X64
#define DETOURS_OPTION_BITS 32

#elif defined(_IA64_)
#define DETOURS_IA64
#define DETOURS_OPTION_BITS 32

#ifdef _WIN64
#undef DETOURS_32BIT
#define DETOURS_64BIT 1
#define DETOURS_BITS 64
// If all 64bit kernels can run one and only one 32bit architecture.
//#define DETOURS_OPTION_BITS 32
#else
#define DETOURS_32BIT 1
#undef DETOURS_64BIT
#define DETOURS_BITS 32
// If all 64bit kernels can run one and only one 32bit architecture.
//#define DETOURS_OPTION_BITS 32
#endif
#endif
//@分组}

///////////////////////////////////////////////// SAL 2.0 Annotations w/o SAL.   SAL (Source-code Annotation Language)
//@分组{ 免除SAL2.0宏定义

//
//  These definitions are include so that Detours will build even if the
//  compiler doesn't have full SAL 2.0 support.
//
#ifndef DETOURS_DONT_REMOVE_SAL_20

#ifdef DETOURS_TEST_REMOVE_SAL_20
#undef _Analysis_assume_
#undef _Benign_race_begin_
#undef _Benign_race_end_
#undef _Field_range_
#undef _Field_size_
#undef __in
#undef _In_bytecount_
#undef _In_count_
#undef __in_ecount
#undef _In_opt_
#undef _In_opt_bytecount_
#undef _In_opt_count_
#undef _In_opt_z_
#undef _In_range_
#undef _In_reads_
#undef _In_reads_bytes_
#undef _In_reads_opt_
#undef _In_reads_opt_bytes_
#undef _In_reads_or_z_
#undef _In_z_
#undef __in_out
#undef __in_outopt_
#undef __in_outz_count_
#undef __out
#undef __out
#undef __outwrites_
#undef _Outptr_result_maybenull_
#undef _Readable_bytes_
#undef _Success_
#undef _Writable_bytes_
#undef _Pre_notnull_
#endif

#if defined(_Deref__outz_) && !defined(_Outptr_result_maybenull_)
#define _Outptr_result_maybenull_ _Deref__outz_
#endif

#if defined(_In_count_) && !defined(_In_reads_)
#define _In_reads_(x) _In_count_(x)
#endif

#if defined(_In_opt_count_) && !defined(_In_reads_opt_)
#define _In_reads_opt_(x) _In_opt_count_(x)
#endif

#if defined(_In_opt_bytecount_) && !defined(_In_reads_opt_bytes_)
#define _In_reads_opt_bytes_(x) _In_opt_bytecount_(x)
#endif

#if defined(_In_bytecount_) && !defined(_In_reads_bytes_)
#define _In_reads_bytes_(x) _In_bytecount_(x)
#endif

#ifndef __in
#define __in
#endif

#ifndef _In_bytecount_
#define _In_bytecount_(x)
#endif

#ifndef _In_count_
#define _In_count_(x)
#endif

#ifndef __in_ecount
#define __in_ecount(x)
#endif

#ifndef _In_opt_
#define _In_opt_
#endif

#ifndef _In_opt_bytecount_
#define _In_opt_bytecount_(x)
#endif

#ifndef _In_opt_count_
#define _In_opt_count_(x)
#endif

#ifndef _In_opt_z_
#define _In_opt_z_
#endif

#ifndef _In_range_
#define _In_range_(x,y)
#endif

#ifndef _In_reads_
#define _In_reads_(x)
#endif

#ifndef _In_reads_bytes_
#define _In_reads_bytes_(x)
#endif

#ifndef _In_reads_opt_
#define _In_reads_opt_(x)
#endif

#ifndef _In_reads_opt_bytes_
#define _In_reads_opt_bytes_(x)
#endif

#ifndef _In_reads_or_z_
#define _In_reads_or_z_
#endif

#ifndef _In_z_
#define _In_z_
#endif

#ifndef __in_out
#define __in_out
#endif

#ifndef __in_outopt_
#define __in_outopt_
#endif

#ifndef __in_outz_count_
#define __in_outz_count_(x)
#endif

#ifndef __out
#define __out
#endif

#ifndef __out
#define __out
#endif

#ifndef __outwrites_
#define __outwrites_(x)
#endif

#ifndef _Outptr_result_maybenull_
#define _Outptr_result_maybenull_
#endif

#ifndef _Writable_bytes_
#define _Writable_bytes_(x)
#endif

#ifndef _Readable_bytes_
#define _Readable_bytes_(x)
#endif

#ifndef _Success_
#define _Success_(x)
#endif

#ifndef _Pre_notnull_
#define _Pre_notnull_
#endif

#ifdef DETOURS_INTERNAL

#pragma warning(disable:4615) // unknown warning type (suppress with older compilers)

#ifndef _Benign_race_begin_
#define _Benign_race_begin_
#endif

#ifndef _Benign_race_end_
#define _Benign_race_end_
#endif

#ifndef _Field_size_
#define _Field_size_(x)
#endif

#ifndef _Field_range_
#define _Field_range_(x,y)
#endif

#ifndef _Analysis_assume_
#define _Analysis_assume_(x)
#endif

#endif // DETOURS_INTERNAL
#endif // DETOURS_DONT_REMOVE_SAL_20
//@分组}

/////////////////////////////////////////////////////////////// Helper Macros.

//@分组{ 辅助程序宏定义
#define DETOURS_STRINGIFY_(x)    #x
#define DETOURS_STRINGIFY(x)    DETOURS_STRINGIFY_(x)

#define VER_DETOURS_BITS    DETOURS_STRINGIFY(DETOURS_BITS)
//@分组}

extern "C" {
    //@分组{ 指令目标结构和宏定义
//@备注 表示指令不是一个分支指令
#define DETOUR_INSTRUCTION_TARGET_NONE          ((PVOID)0)
//@备注 表示指令的目标地址是一个在运行时才能确定的位置
#define DETOUR_INSTRUCTION_TARGET_DYNAMIC       ((PVOID)(LONG_PTR)-1)
//@备注 表示用于标识DETOUR_SECTION_HEADER结构的标志
#define DETOUR_SECTION_HEADER_SIGNATURE         0x00727444   // "Dtr\0"

//@备注 表示用于标识DETOUR_TRAMPOLINE结构的标志
#define DETOUR_TRAMPOLINE_SIGNATURE             0x21727444  // Dtr!

//@备注 表示一段跳转代码的结构体
typedef struct _DETOUR_TRAMPOLINE DETOUR_TRAMPOLINE, * PDETOUR_TRAMPOLINE;

#ifndef DETOUR_MAX_SUPPORTED_IMAGE_SECTION_HEADERS
//@备注 表示定义每个映像文件支持的最大节表头数量的最大值
#define DETOUR_MAX_SUPPORTED_IMAGE_SECTION_HEADERS      32
#endif // !DETOUR_MAX_SUPPORTED_IMAGE_SECTION_HEADERS

    /////////////////////////////////////////////////////////// Binary Structures.

    //@分组}

        //@分组{ 结构体
#pragma pack(push, 8)

    //@备注 用于描述一个节表头的结构体
    typedef struct _DETOUR_SECTION_HEADER
    {
        DWORD       cbHeaderSize;
        DWORD       nSignature;
        DWORD       nDataOffset;
        DWORD       cbDataSize;

        DWORD       nOriginalImportVirtualAddress;
        DWORD       nOriginalImportSize;
        DWORD       nOriginalBoundImportVirtualAddress;
        DWORD       nOriginalBoundImportSize;

        DWORD       nOriginalIatVirtualAddress;
        DWORD       nOriginalIatSize;
        DWORD       nOriginalSizeOfImage;
        DWORD       cbPrePE;

        DWORD       nOriginalClrFlags;
        DWORD       reserved1;
        DWORD       reserved2;
        DWORD       reserved3;

        // Followed by cbPrePE bytes of data.
    } DETOUR_SECTION_HEADER, * PDETOUR_SECTION_HEADER;

    //@备注 用于描述一个代码段节（section）的信息
    typedef struct _DETOUR_SECTION_RECORD
    {
        DWORD       cbBytes;
        DWORD       nReserved;
        GUID        guid;
    } DETOUR_SECTION_RECORD, * PDETOUR_SECTION_RECORD;

    //@备注 是用于存储 CLR 模块头部信息的结构体
    typedef struct _DETOUR_CLR_HEADER
    {
        // Header versioning
        ULONG                   cb;
        USHORT                  MajorRuntimeVersion;
        USHORT                  MinorRuntimeVersion;

        // Symbol table and startup information
        IMAGE_DATA_DIRECTORY    MetaData;
        ULONG                   Flags;

        // Followed by the rest of the IMAGE_COR20_HEADER
    } DETOUR_CLR_HEADER, * PDETOUR_CLR_HEADER;

    //@备注 用于记录修补过的可执行档的还原点。当使用 Detours 库修补可执行档
    typedef struct _DETOUR_EXE_RESTORE
    {
        DWORD               cb;
        DWORD               cbidh;
        DWORD               cbinh;
        DWORD               cbclr;

        PBYTE               pidh;
        PBYTE               pinh;
        PBYTE               pclr;

        IMAGE_DOS_HEADER    idh;
        IMAGE_NT_HEADERS    inh;        // all environments have this
        DETOUR_CLR_HEADER   clr;

    } DETOUR_EXE_RESTORE, * PDETOUR_EXE_RESTORE;

    //@备注 用于保存注入进程的帮助进程信息的结构体
    typedef struct _DETOUR_EXE_HELPER
    {
        DWORD               cb;
        DWORD               pid;
        DWORD               nDlls;
        CHAR                rDlls[4];
    } DETOUR_EXE_HELPER, * PDETOUR_EXE_HELPER;

#pragma pack(pop)

//@备注 指定一个存储挂钩信息的 PE 文件节的头部信息 可以方便地创建一个 DETOUR_SECTION_HEADER 结构
#define DETOUR_SECTION_HEADER_DECLARE(cbSectionSize) { sizeof(DETOUR_SECTION_HEADER),DETOUR_SECTION_HEADER_SIGNATURE,sizeof(DETOUR_SECTION_HEADER),(cbSectionSize),0,0,0,0,0,0,0,0, }
    //@分组}

    ///////////////////////////////////////////////////////////// Binary Typedefs.

    //@分组{ 回调函数定义
    typedef BOOL(CALLBACK* PF_DETOUR_BINARY_BYWAY_CALLBACK)(
        _In_opt_ PVOID pContext,
        _In_opt_ LPCSTR pszFile,
        _Outptr_result_maybenull_ LPCSTR* ppszOutFile);

    typedef BOOL(CALLBACK* PF_DETOUR_BINARY_FILE_CALLBACK)(
        _In_opt_ PVOID pContext,
        __in LPCSTR pszOrigFile,
        __in LPCSTR pszFile,
        _Outptr_result_maybenull_ LPCSTR* ppszOutFile);

    typedef BOOL(CALLBACK* PF_DETOUR_BINARY_SYMBOL_CALLBACK)(
        _In_opt_ PVOID pContext,
        __in ULONG nOrigOrdinal,
        __in ULONG nOrdinal,
        __out ULONG* pnOutOrdinal,
        _In_opt_ LPCSTR pszOrigSymbol,
        _In_opt_ LPCSTR pszSymbol,
        _Outptr_result_maybenull_ LPCSTR* ppszOutSymbol);

    typedef BOOL(CALLBACK* PF_DETOUR_BINARY_COMMIT_CALLBACK)(
        _In_opt_ PVOID pContext);

    typedef BOOL(CALLBACK* PF_DETOUR_ENUMERATE_EXPORT_CALLBACK)(_In_opt_ PVOID pContext,
        __in ULONG nOrdinal,
        _In_opt_ LPCSTR pszName,
        _In_opt_ PVOID pCode);

    typedef BOOL(CALLBACK* PF_DETOUR_IMPORT_FILE_CALLBACK)(_In_opt_ PVOID pContext,
        _In_opt_ HMODULE hModule,
        _In_opt_ LPCSTR pszFile);

    typedef BOOL(CALLBACK* PF_DETOUR_IMPORT_FUNC_CALLBACK)(_In_opt_ PVOID pContext,
        __in DWORD nOrdinal,
        _In_opt_ LPCSTR pszFunc,
        _In_opt_ PVOID pvFunc);

    // Same as PF_DETOUR_IMPORT_FUNC_CALLBACK but extra indirection on last parameter.
    typedef BOOL(CALLBACK* PF_DETOUR_IMPORT_FUNC_CALLBACK_EX)(_In_opt_ PVOID pContext,
        __in DWORD nOrdinal,
        _In_opt_ LPCSTR pszFunc,
        _In_opt_ PVOID* ppvFunc);

    typedef VOID* PDETOUR_BINARY;
    typedef VOID* PDETOUR_LOADED_BINARY;
    //@分组}

        //////////////////////////////////////////////////////////// Transaction APIs.

    //@分组{ 基本钩子操作函数

 //@备注 DetourTransactionBegin 函数用于开始一个新的事务
    //@返回 长整型(LONG), 表示函数执行成功或失败。
    //@别名 钩子事务开始(无参数)
    LONG WINAPI DetourTransactionBegin(VOID);

    //@备注 DetourTransactionAbort 函数用于放弃当前的事务
    //@返回 长整型(LONG), 表示函数执行成功或失败。
    //@别名 钩子事务放弃(无参数)
    LONG WINAPI DetourTransactionAbort(VOID);

    //@备注 DetourTransactionCommit 函数用于提交当前的事务，将所有的修改应用到目标函数中。
    //@返回 长整型(LONG), 表示函数执行成功或失败。
    //@别名 钩子事务提交(无参数)
    LONG WINAPI DetourTransactionCommit(VOID);

    //@备注 DetourUpdateThread 函数用于更新指定线程的挂钩
    //@参数 hThread 输入参数, 需要更新挂钩的线程句柄
    //@返回 长整型(LONG), 表示函数执行成功或失败。
    //@别名 钩子更新线程(线程句柄)
    LONG WINAPI DetourTransactionCommitEx(__out PVOID** pppFailedPointer);

    //@备注 更新指定线程的挂钩
    //@参数 hThread 输入参数，指向待更新挂钩的线程句柄
    //@返回 返回一个长整型值，表示操作是否成功
    //@别名 钩子线程更新(有参数)
    LONG WINAPI DetourUpdateThread(__in HANDLE hThread);

    //@备注 DetourAttach 函数用于将挂钩函数附加到指定的指针上。
    //@参数 ppPointer 输入/输出参数, 指向待挂钩的函数指针
    //@参数 pDetour 输入参数, 指向挂钩的函数指针
    //@返回 长整型(LONG), 表示函数执行成功或失败。
    //@别名 钩子附加(原始函数指针的指针, 新函数指针)
    LONG WINAPI DetourAttach(__in_out PVOID* ppPointer,
        __in PVOID pDetour);

    //@备注 DetourAttachEx 函数用于将挂钩函数附加到指定的指针上，并可返回实际的跳板、目标和挂钩函数指针地址。
    //@参数 ppPointer 输入/输出参数, 指向待挂钩的函数指针
    //@参数 pDetour 输入参数, 指向挂钩的函数指针
    //@参数 ppRealTrampoline 输出参数, 可选参数, 返回实际的跳板指针地址
    //@参数 ppRealTarget 输出参数, 可选参数, 返回实际的目标指针地址
    //@参数 ppRealDetour 输出参数, 可选参数, 返回实际的挂钩函数指针地址
    //@返回 长整型(LONG), 表示函数执行成功或失败。
    //@别名 钩子附加扩展(原始函数指针的指针, 新函数指针, 实际跳板, 实际目标, 实际挂钩函数)
    LONG WINAPI DetourAttachEx(__in_out PVOID* ppPointer,
        __in PVOID pDetour,
        __out PDETOUR_TRAMPOLINE* ppRealTrampoline,
        __out PVOID* ppRealTarget,
        __out PVOID* ppRealDetour);

    //@备注 DetourDetach 函数用于从指定的指针上解除挂钩函数
    //@参数 ppPointer 输入/输出参数, 指向待解除挂钩的函数指针
    //@参数 pDetour 输入参数, 指向之前挂钩的函数指针
    //@返回 长整型(LONG), 表示函数执行成功或失败。
    //@别名 钩子卸载(原始函数指针的指针, 新函数指针)
    LONG WINAPI DetourDetach(__in_out PVOID* ppPointer,
        __in PVOID pDetour);

    //@备注 DetourSetIgnoreTooSmall 函数用于设置是否忽略太小的函数来避免不必要的挂钩
    //@参数 fIgnore 输入参数, 设置是否忽略太小的函数，若忽略则返回TRUE，否则返回FALSE
    //@返回 布尔型(BOOL), 表示函数执行成功或失败。
    //@别名 钩子设置忽略太小函数(是否忽略)
    BOOL WINAPI DetourSetIgnoreTooSmall(__in BOOL fIgnore);

    //@备注 DetourSetRetainRegions 函数用于设置是否保留原始代码和数据的内存区域，以便在解除挂钩后恢复它们
    //@参数 fRetain 输入参数, 设置是否保留原始代码和数据的内存区域，若保留则返回TRUE，否则返回FALSE
    //@返回 布尔型(BOOL), 表示函数执行成功或失败。
    //@别名 钩子设置保留区域(是否保留)
    BOOL WINAPI DetourSetRetainRegions(__in BOOL fRetain);

    //@备注 DetourSetSystemRegionLowerBound 函数用于设置系统区域的下边界
    //@参数 pSystemRegionLowerBound 输入参数, 指向系统区域下边界的指针
    //@返回 指针(PVOID), 返回指向新的系统区域下边界的指针
    //@别名 钩子设置系统区域下边界(新下边界指针)
    PVOID WINAPI DetourSetSystemRegionLowerBound(__in PVOID pSystemRegionLowerBound);

    //@备注 DetourSetSystemRegionUpperBound 函数用于设置系统区域的上边界
    //@参数 pSystemRegionUpperBound 输入参数, 指向系统区域上边界的指针
    //@返回 指针(PVOID), 返回指向新的系统区域上边界的指针
    //@别名 钩子设置系统区域上边界(新上边界指针)
    PVOID WINAPI DetourSetSystemRegionUpperBound(__in PVOID pSystemRegionUpperBound);
   
    //@分组}

       ////////////////////////////////////////////////////////////// Code Functions.

    //@分组{ 指令码函数

    //@备注 DetourFindFunction 函数用于查找指定模块中的函数地址
    //@参数 pszModule 输入参数, 指向模块名称字符串的指针
    //@参数 pszFunction 输入参数, 指向函数名称字符串的指针
    //@返回 指针(PVOID), 返回指向函数地址的指针，若未找到则返回NULL
    //@别名 钩子查找函数(模块名称, 函数名称)
    PVOID WINAPI DetourFindFunction(__in LPCSTR pszModule,
        __in LPCSTR pszFunction);

    //@备注 DetourCodeFromPointer 函数用于返回指向指定指针所在的代码地址
    //@参数 pPointer 输入参数, 指向目标指针的指针
    //@参数 ppGlobals 输出参数, 可选参数，指向全局指针的指针
    //@返回 指针(PVOID), 返回指向代码地址的指针
    //@别名 钩子代码从指针(指针, 全局指针的指针)
    PVOID WINAPI DetourCodeFromPointer(__in PVOID pPointer,
        __out PVOID* ppGlobals);

    //@备注 DetourCopyInstruction 函数用于将源指令复制到目标地址，并返回额外的长度信息
    //@参数 pDst 输入/输出参数, 指向目标地址的指针
    //@参数 ppDstPool 输入/输出参数, 可选参数，指向目标地址所在的池的指针
    //@参数 pSrc 输入参数, 指向源指令的指针
    //@参数 ppTarget 输出参数, 可选参数，指向目标地址的指针
    //@参数 plExtra 输出参数, 可选参数，返回源指令的额外长度信息
    //@返回 指针(PVOID), 返回指向目标地址的指针
    //@别名 钩子複製指令(目标地址, 目标池, 源指令, 目标指针, 额外长度)
    PVOID WINAPI DetourCopyInstruction(_In_opt_ PVOID pDst,
        __in_outopt_ PVOID* ppDstPool,
        __in PVOID pSrc,
        __out PVOID* ppTarget,
        __out LONG* plExtra);

    //@备注 DetourSetCodeModule 函数用于设置代码模块，并决定是否限制引用仅限于该模块
    //@参数 hModule 输入参数, 指向模块句柄的指针
    //@参数 fLimitReferencesToModule 输入参数, 设置是否限制引用仅限于该模块，若限制则返回TRUE，否则返回FALSE
    //@返回 布尔型(BOOL), 表示函数执行成功或失败。
    //@别名 钩子设置代码模块(模块句柄, 是否限制引用)
    BOOL WINAPI DetourSetCodeModule(__in HMODULE hModule,
        __in BOOL fLimitReferencesToModule);

    //@备注 DetourAllocateRegionWithinJumpBounds 函数用于在跳转边界内分配一块内存
    //@参数 pbTarget 输入参数, 指向目标函数地址的指针
    //@参数 pcbAllocatedSize 输出参数, 指向分配大小的指针
    //@返回 指针(PVOID), 返回指向分配内存的指针，若分配失败则返回NULL
    //@别名 钩子在跳转边界内分配区域(目标函数地址, 分配大小指针)
    PVOID WINAPI DetourAllocateRegionWithinJumpBounds(__in LPCVOID pbTarget,
        __out PDWORD pcbAllocatedSize);

    //@备注 DetourIsFunctionImported 函数用于确定指定的地址是否是导入函数的地址
    //@参数 pbCode 输入参数, 指向要检查的代码地址的指针
    //@参数 pbAddress 输入参数, 指向要检查的地址的指针
    //@返回 布尔型(BOOL), 表示指定的地址是否是导入函数的地址
    //@别名 钩子函数是否被导入(代码地址, 要检查的地址)
    BOOL WINAPI DetourIsFunctionImported(__in PBYTE pbCode,
        __in PBYTE pbAddress);
    //@分组}

    ///////////////////////////////////////////////////// Loaded Binary Functions.

    //@分组{ 加载映像函数

    //@备注 DetourGetContainingModule 函数用于返回包含指定地址的模块的句柄
    //@参数 pvAddr 输入参数, 指向目标地址的指针
    //@返回 模块句柄(HMODULE), 返回包含指定地址的模块的句柄，若未找到则返回NULL
    //@别名 钩子获取包含模块(地址)
    HMODULE WINAPI DetourGetContainingModule(__in PVOID pvAddr);

    //@备注 DetourEnumerateModules 函数用于枚举系统中的模块
    //@参数 hModuleLast 输入参数, 可选参数，上次检索到的模块的句柄
    //@返回 模块句柄(HMODULE), 返回下一个枚举到的模块的句柄，若无更多模块，则返回NULL
    //@别名 钩子枚举模块(上次模块句柄)
    HMODULE WINAPI DetourEnumerateModules(_In_opt_ HMODULE hModuleLast);

    //@备注 DetourGetEntryPoint 函数用于返回指定模块的入口点地址
    //@参数 hModule 输入参数, 指向目标模块的句柄
    //@返回 指针(PVOID), 返回指向入口点地址的指针
    //@别名 钩子获取入口点(模块句柄)
    PVOID WINAPI DetourGetEntryPoint(_In_opt_ HMODULE hModule);

    //@备注 DetourGetModuleSize 函数用于返回指定模块的大小
    //@参数 hModule 输入参数, 指向目标模块的句柄
    //@返回 无符号长整型(ULONG), 表示模块的大小，单位为字节
    //@别名 钩子获取模块大小(模块句柄)
    ULONG WINAPI DetourGetModuleSize(_In_opt_ HMODULE hModule);

    //@备注 DetourEnumerateExports 函数用于枚举指定模块中的导出函数
    //@参数 hModule 输入参数, 指向目标模块的句柄
    //@参数 pContext 输入参数, 可选参数，上下文数据
    //@参数 pfExport 输入参数, 指向枚举回调函数的指针
    //@返回 布尔型(BOOL), 表示函数执行成功或失败。
    //@别名 钩子枚举导出(模块句柄, 上下文, 导出回调函数)
    BOOL WINAPI DetourEnumerateExports(__in HMODULE hModule,
        _In_opt_ PVOID pContext,
        __in PF_DETOUR_ENUMERATE_EXPORT_CALLBACK pfExport);

    //@备注 DetourEnumerateImports 函数用于枚举指定模块中的导入函数
    //@参数 hModule 输入参数, 指向目标模块的句柄
    //@参数 pContext 输入参数, 可选参数，上下文数据
    //@参数 pfImportFile 输入参数, 可选参数，指向导入文件回调函数的指针
    //@参数 pfImportFunc 输入参数, 可选参数，指向导入函数回调函数的指针
    //@返回 布尔型(BOOL), 表示函数执行成功或失败。
    //@别名 钩子枚举导入(模块句柄, 上下文, 导入文件回调函数, 导入函数回调函数)
    BOOL WINAPI DetourEnumerateImports(_In_opt_ HMODULE hModule,
        _In_opt_ PVOID pContext,
        _In_opt_ PF_DETOUR_IMPORT_FILE_CALLBACK pfImportFile,
        _In_opt_ PF_DETOUR_IMPORT_FUNC_CALLBACK pfImportFunc);

    //@备注 DetourEnumerateImportsEx 函数用于枚举指定模块中的导入函数，并提供更多的导入信息
    //@参数 hModule 输入参数, 指向目标模块的句柄
    //@参数 pContext 输入参数, 可选参数，上下文数据
    //@参数 pfImportFile 输入参数, 可选参数，指向导入文件回调函数的指针
    //@参数 pfImportFuncEx 输入参数, 可选参数，指向导入函数回调函数的指针，提供更多的导入信息
    //@返回 布尔型(BOOL), 表示函数执行成功或失败。
    //@别名 钩子枚举导入Ex(模块句柄, 上下文, 导入文件回调函数, 导入函数回调函数)
    BOOL WINAPI DetourEnumerateImportsEx(_In_opt_ HMODULE hModule,
        _In_opt_ PVOID pContext,
        _In_opt_ PF_DETOUR_IMPORT_FILE_CALLBACK pfImportFile,
        _In_opt_ PF_DETOUR_IMPORT_FUNC_CALLBACK_EX pfImportFuncEx);

    //@备注 DetourFindPayload 函数用于查找指定GUID的有效负载数据，如果找到，则返回指向该负载数据的指针和其大小
    //@参数 hModule 输入参数, 可选参数，指向目标模块的句柄
    //@参数 rguid 输入参数, 指向GUID的指针，指定要查找的负载
    //@参数 pcbData 输出参数, 可选参数，指向负载数据大小的指针
    //@返回 指针(PVOID), 返回指向有效负载数据的指针，若未找到则返回NULL
    //@别名 钩子查找有效负载(模块句柄, GUID, 负载大小指针)
    PVOID WINAPI DetourFindPayload(_In_opt_ HMODULE hModule,
        __in REFGUID rguid,
        __out DWORD* pcbData);

    //@备注 DetourFindPayloadEx 函数用于查找指定GUID的有效负载数据，如果找到，则返回指向该负载数据的指针和其大小
    //@参数 rguid 输入参数, 指向GUID的指针，指定要查找的负载
    //@参数 pcbData 输出参数, 可选参数，指向负载数据大小的指针
    //@返回 指针(PVOID), 返回指向有效负载数据的指针，若未找到则返回NULL
    //@别名 钩子查找有效负载Ex(GUID, 负载大小指针)
    PVOID WINAPI DetourFindPayloadEx(__in REFGUID rguid,
        __out DWORD* pcbData);

    //@备注 DetourGetSizeOfPayloads 函数用于返回所有有效负载的总大小
    //@参数 hModule 输入参数, 可选参数，指向目标模块的句柄
    //@返回 无符号长整型(DWORD), 表示所有有效负载的总大小，单位为字节
    //@别名 钩子获取有效负载大小(模块句柄)
    DWORD WINAPI DetourGetSizeOfPayloads(_In_opt_ HMODULE hModule);

    //@备注 DetourFreePayload 函数用于释放有效负载的内存
    //@参数 pvData 输入参数, 指向有效负载数据的指针
    //@返回 布尔型(BOOL), 表示函数执行成功或失败。
    //@别名 钩子释放有效负载(数据指针)
    BOOL WINAPI DetourFreePayload(__in PVOID pvData);
    //@分组}

 ///////////////////////////////////////////////// Persistent Binary Functions.

    //@分组{ 二进制文件处理函数

    //@备注 DetourBinaryOpen 函数用于打开指定的二进制文件并创建一个 PDETOUR_BINARY 句柄
    //@参数 hFile 输入参数, 一个句柄，指向要打开的文件的文件句柄
    //@返回 指针(PDETOUR_BINARY), 如果成功则返回指向 PDETOUR_BINARY 的指针，否则返回 NULL
    //@别名 钩子二进制文件打开(文件句柄)
    PDETOUR_BINARY WINAPI DetourBinaryOpen(__in HANDLE hFile);

    //@备注 DetourBinaryEnumeratePayloads 函数用于枚举指定的 PDETOUR_BINARY 中的有效负载
    //@参数 pBinary 输入参数, 指向 PDETOUR_BINARY 句柄的指针
    //@参数 pGuid 输出参数, 可选参数，指向 GUID 的指针，如果不为 NULL，则返回有效负载的 GUID
    //@参数 pcbData 输出参数, 指向 DWORD 的指针，用于返回有效负载数据的大小
    //@参数 pnIterator 输入/输出参数, 指向 DWORD 的指针，用于在有效负载之间循环迭代
    //@返回 指针(PVOID), 返回指向有效负载数据的指针，如果没有更多的负载，则返回 NULL
    //@别名 钩子二进制枚举有效负载(PDETOUR_BINARY, GUID, 负载大小, 迭代器)
    PVOID WINAPI DetourBinaryEnumeratePayloads(__in PDETOUR_BINARY pBinary,
        __out GUID* pGuid,
        __out DWORD* pcbData,
        __in_out DWORD* pnIterator);

    //@备注 DetourBinaryFindPayload 函数用于查找指定 GUID 的有效负载数据
    //@参数 pBinary 输入参数, 指向 PDETOUR_BINARY 句柄的指针
    //@参数 rguid 输入参数, 指向 GUID 的指针，指定要查找的负载
    //@参数 pcbData 输出参数, 指向 DWORD 的指针，用于返回有效负载数据的大小
    //@返回 指针(PVOID), 返回指向有效负载数据的指针，若未找到则返回NULL
    //@别名 钩子二进制查找有效负载(PDETOUR_BINARY, GUID, 负载大小指针)
    PVOID WINAPI DetourBinaryFindPayload(__in PDETOUR_BINARY pBinary,
        __in REFGUID rguid,
        __out DWORD* pcbData);

    //@备注 DetourBinarySetPayload 函数用于设置指定的 PDETOUR_BINARY 中的有效负载
    //@参数 pBinary 输入参数, 指向 PDETOUR_BINARY 句柄的指针
    //@参数 rguid 输入参数, 指向 GUID 的指针，指定要设置的负载
    //@参数 pData 输入参数, 指向要设置的有效负载数据的指针
    //@参数 cbData 输入参数, DWORD 值，指定有效负载数据的大小
    //@返回 指针(PVOID), 如果成功，则返回指向有效负载数据的指针，否则返回 NULL
    //@别名 钩子二进制设置有效负载(PDETOUR_BINARY, GUID, 负载数据指针, 负载大小)
    PVOID WINAPI DetourBinarySetPayload(__in PDETOUR_BINARY pBinary,
        __in REFGUID rguid,
        __in PVOID pData,
        __in DWORD cbData);

    //@备注 DetourBinaryDeletePayload 函数用于删除指定的 PDETOUR_BINARY 中的有效负载
    //@参数 pBinary 输入参数, 指向 PDETOUR_BINARY 句柄的指针
    //@参数 rguid 输入参数, 指向 GUID 的指针，指定要删除的负载
    //@返回 布尔型(BOOL), 表示函数执行成功或失败。
    //@别名 钩子删除有效负载(PDETOUR_BINARY, GUID)
    BOOL WINAPI DetourBinaryDeletePayload(__in PDETOUR_BINARY pBinary, __in REFGUID rguid);

    //@备注 DetourBinaryPurgePayloads 函数用于清空指定 PDETOUR_BINARY 中的所有有效负载
    //@参数 pBinary 输入参数, 指向 PDETOUR_BINARY 句柄的指针
    //@返回 布尔型(BOOL), 表示函数执行成功或失败。
    //@别名 钩子清空有效负载(PDETOUR_BINARY)
    BOOL WINAPI DetourBinaryPurgePayloads(__in PDETOUR_BINARY pBinary);

    //@备注 DetourBinaryResetImports 函数用于重置指定 PDETOUR_BINARY 中的导入表
    //@参数 pBinary 输入参数, 指向 PDETOUR_BINARY 句柄的指针
    //@返回 布尔型(BOOL), 表示函数执行成功或失败。
    //@别名 钩子重置导入表(PDETOUR_BINARY)
    BOOL WINAPI DetourBinaryResetImports(__in PDETOUR_BINARY pBinary);

    //@备注 DetourBinaryEditImports 函数用于修改指定 PDETOUR_BINARY 中的导入表
    //@参数 pBinary 输入参数, 指向 PDETOUR_BINARY 句柄的指针
    //@参数 pContext 输入参数, 可选参数，指向上下文数据的指针，用于在回调函数之间传递状态
    //@参数 pfByway 输入参数, 可选参数，指向 PF_DETOUR_BINARY_BYWAY_CALLBACK 回调函数的指针
    //@参数 pfFile 输入参数, 可选参数，指向 PF_DETOUR_BINARY_FILE_CALLBACK 回调函数的指针
    //@参数 pfSymbol 输入参数, 可选参数，指向 PF_DETOUR_BINARY_SYMBOL_CALLBACK 回调函数的指针
    //@参数 pfCommit 输入参数, 可选参数，指向 PF_DETOUR_BINARY_COMMIT_CALLBACK 回调函数的指针
    //@返回 布尔型(BOOL), 表示函数执行成功或失败。
    //@别名 钩子修改导入表(PDETOUR_BINARY, 上下文, Byway回调, 文件回调, 符号回调, 提交回调)
    BOOL WINAPI DetourBinaryEditImports(__in PDETOUR_BINARY pBinary,
        _In_opt_ PVOID pContext,
        _In_opt_ PF_DETOUR_BINARY_BYWAY_CALLBACK pfByway,
        _In_opt_ PF_DETOUR_BINARY_FILE_CALLBACK pfFile,
        _In_opt_ PF_DETOUR_BINARY_SYMBOL_CALLBACK pfSymbol,
        _In_opt_ PF_DETOUR_BINARY_COMMIT_CALLBACK pfCommit);

    //@备注 DetourBinaryWrite 函数用于将修改过的 PDETOUR_BINARY 写回到磁盘文件中
    //@参数 pBinary 输入参数, 指向 PDETOUR_BINARY 句柄的指针
    //@参数 hFile 输入参数, 指向要写入的文件句柄的指针
    //@返回 布尔型(BOOL), 表示函数执行成功或失败。
    //@别名 钩子写入文件(PDETOUR_BINARY, 文件句柄)
    BOOL WINAPI DetourBinaryWrite(__in PDETOUR_BINARY pBinary, __in HANDLE hFile);

    //@备注 DetourBinaryClose 函数用于释放指定的 PDETOUR_BINARY 句柄及相关资源
    //@参数 pBinary 输入参数, 指向 PDETOUR_BINARY 句柄的指针
    //@返回 布尔型(BOOL), 表示函数执行成功或失败。
    //@别名 钩子关闭文件(PDETOUR_BINARY)
    BOOL WINAPI DetourBinaryClose(__in PDETOUR_BINARY pBinary);
    //@分组}

    /////////////////////////////////////////////////// Create Process & Load Dll.

    //@分组{ 进程注入函数

    //@备注 DetourFindRemotePayload 函数用于在指定的进程中查找指定的 GUID 对应的有效负载。
    //@参数 hProcess 输入参数, 指定要查找的进程句柄。
    //@参数 rguid 输入参数, 指向 GUID 的指针，指定要查找的负载。
    //@参数 pcbData 输出参数, 指向一个 DWORD 的指针，用于接收有效负载的大小。
    //@返回 指针类型(PVOID), 返回指向有效负载数据的指针。如果查找失败，则返回 NULL。
    //@别名 钩子查找远端有效负载(进程句柄, GUID, 有效负载大小)
    PVOID WINAPI DetourFindRemotePayload(__in HANDLE hProcess,
        __in REFGUID rguid,
        __out DWORD* pcbData);

    //@备注 ANSI钩子创建进程回调函数指针A
    typedef BOOL(WINAPI* PDETOUR_CREATE_PROCESS_ROUTINEA)(
        _In_opt_ LPCSTR lpApplicationName,
        __in_outopt_ LPSTR lpCommandLine,
        _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
        _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
        __in BOOL bInheritHandles,
        __in DWORD dwCreationFlags,
        _In_opt_ LPVOID lpEnvironment,
        _In_opt_ LPCSTR lpCurrentDirectory,
        __in LPSTARTUPINFOA lpStartupInfo,
        __out LPPROCESS_INFORMATION lpProcessInformation);

    //@备注 UNICODE钩子创建进程回调函数指针W
    typedef BOOL(WINAPI* PDETOUR_CREATE_PROCESS_ROUTINEW)(
        _In_opt_ LPCWSTR lpApplicationName,
        __in_outopt_ LPWSTR lpCommandLine,
        _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
        _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
        __in BOOL bInheritHandles,
        __in DWORD dwCreationFlags,
        _In_opt_ LPVOID lpEnvironment,
        _In_opt_ LPCWSTR lpCurrentDirectory,
        __in LPSTARTUPINFOW lpStartupInfo,
        __out LPPROCESS_INFORMATION lpProcessInformation);

    //@备注 DetourCreateProcessWithDllA 函数用于启动一个进程，并在其地址空间中加载指定的 DLL 文件。
    //@参数 lpApplicationName 输入参数, 指定要启动的可执行文件路径，可以为 NULL。
    //@参数 lpCommandLine 输入/输出参数, 指定启动进程时的命令行参数，也可以为 NULL。
    //@参数 lpProcessAttributes 输入参数, 指定进程的安全属性，也可以为 NULL。
    //@参数 lpThreadAttributes 输入参数, 指定线程的安全属性，也可以为 NULL。
    //@参数 bInheritHandles 输入参数, 指定是否从父进程继承句柄。
    //@参数 dwCreationFlags 输入参数, 指定进程创建标志。
    //@参数 lpEnvironment 输入参数, 指定环境变量指针，也可以为 NULL。
    //@参数 lpCurrentDirectory 输入参数, 指定当前工作目录，也可以为 NULL。
    //@参数 lpStartupInfo 输入参数, 指向 STARTUPINFO 结构的指针，也可以为 NULL。
    //@参数 lpProcessInformation 输出参数, 指向 PROCESS_INFORMATION 结构的指针，用于返回有关新进程和主线程的信息。
    //@参数 lpDllName 输入参数, 指定要注入的 DLL 文件路径。
    //@参数 pfCreateProcessA 输入参数, 指向 PDETOUR_CREATE_PROCESS_ROUTINEA 函数的指针，也可以为 NULL。
    //@返回 布尔型(BOOL), 表示函数执行成功或失败。
    //@别名 钩子创建进程并注入动态库A(可执行文件路径, 命令行参数, 进程安全属性, 线程安全属性, 是否继承句柄, 进程创建标志, 环境变量指针, 当前工作目录, STARTUPINFO结构的指针, PROCESS_INFORMATION结构的指针, 要注入的DLL文件路径, 函数指针)
    BOOL WINAPI DetourCreateProcessWithDllA(_In_opt_ LPCSTR lpApplicationName,
        __in_outopt_ LPSTR lpCommandLine,
        _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
        _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
        __in BOOL bInheritHandles,
        __in DWORD dwCreationFlags,
        _In_opt_ LPVOID lpEnvironment,
        _In_opt_ LPCSTR lpCurrentDirectory,
        __in LPSTARTUPINFOA lpStartupInfo,
        __out LPPROCESS_INFORMATION lpProcessInformation,
        __in LPCSTR lpDllName,
        _In_opt_ PDETOUR_CREATE_PROCESS_ROUTINEA pfCreateProcessA);

    //@备注 DetourCreateProcessWithDllW 函数用于启动一个进程，并在其地址空间中加载指定的 DLL 文件。
    //@参数 lpApplicationName 输入参数, 指定要启动的可执行文件路径，可以为 NULL。
    //@参数 lpCommandLine 输入/输出参数, 指定启动进程时的命令行参数，也可以为 NULL。
    //@参数 lpProcessAttributes 输入参数, 指定进程的安全属性，也可以为 NULL。
    //@参数 lpThreadAttributes 输入参数, 指定线程的安全属性，也可以为 NULL。
    //@参数 bInheritHandles 输入参数, 指定是否从父进程继承句柄。
    //@参数 dwCreationFlags 输入参数, 指定进程创建标志。
    //@参数 lpEnvironment 输入参数, 指定环境变量指针，也可以为 NULL。
    //@参数 lpCurrentDirectory 输入参数, 指定当前工作目录，也可以为 NULL。
    //@参数 lpStartupInfo 输入参数, 指向 STARTUPINFO 结构的指针，也可以为 NULL。
    //@参数 lpProcessInformation 输出参数, 指向 PROCESS_INFORMATION 结构的指针，用于返回有关新进程和主线程的信息。
    //@参数 lpDllName 输入参数, 指定要注入的 DLL 文件路径。
    //@参数 pfCreateProcessW 输入参数, 指向 PDETOUR_CREATE_PROCESS_ROUTINEW 函数的指针，也可以为 NULL。
    //@返回 布尔型(BOOL), 表示函数执行成功或失败。
    //@别名 钩子创建进程并注入动态库W(可执行文件路径, 命令行参数, 进程安全属性, 线程安全属性, 是否继承句柄, 进程创建标志, 环境变量指针, 当前工作目录, STARTUPINFO结构的指针, PROCESS_INFORMATION结构的指针, 要注入的DLL文件路径, 函数指针)
    BOOL WINAPI DetourCreateProcessWithDllW(_In_opt_ LPCWSTR lpApplicationName,
        __in_outopt_ LPWSTR lpCommandLine,
        _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
        _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
        __in BOOL bInheritHandles,
        __in DWORD dwCreationFlags,
        _In_opt_ LPVOID lpEnvironment,
        _In_opt_ LPCWSTR lpCurrentDirectory,
        __in LPSTARTUPINFOW lpStartupInfo,
        __out LPPROCESS_INFORMATION lpProcessInformation,
        __in LPCSTR lpDllName,
        _In_opt_ PDETOUR_CREATE_PROCESS_ROUTINEW pfCreateProcessW);

#ifdef UNICODE
//@备注 UNICODE
//@别名 钩子创建进程并注入动态库
#define DetourCreateProcessWithDll      DetourCreateProcessWithDllW
//@备注 UNICODE
//@别名 钩子创建进程回调函数指针
#define PDETOUR_CREATE_PROCESS_ROUTINE  PDETOUR_CREATE_PROCESS_ROUTINEW
#else
//@备注 ANSI
//@别名 钩子创建进程并注入动态库
#define DetourCreateProcessWithDll      DetourCreateProcessWithDllA
//@备注 ANSI
//@别名 钩子创建进程回调函数指针
#define PDETOUR_CREATE_PROCESS_ROUTINE  PDETOUR_CREATE_PROCESS_ROUTINEA
#endif // !UNICODE

    //@备注 创建新进程并注入动态链接库(DLL)到新进程中的指定可执行文件中。
    //@参数 lpApplicationName: 字符串指针，指定要创建的进程的可执行文件名称，可以是完整路径。
    //@参数 lpCommandLine: 字符串指针，指定要传递给新进程的命令行参数。
    //@参数 lpProcessAttributes: 指向SECURITY_ATTRIBUTES结构的指针，用于指定新进程的安全属性。可以为NULL，表示使用默认的进程安全属性。
    //@参数 lpThreadAttributes: 指向SECURITY_ATTRIBUTES结构的指针，用于指定新线程的安全属性。可以为NULL，表示使用默认的线程安全属性。
    //@参数 bInheritHandles: 布尔值，指示新进程是否应该从父进程继承句柄。为TRUE，表示新进程继承句柄；为FALSE，表示不继承句柄。
    //@参数 dwCreationFlags: 标志位，指定新进程的创建标志。
    //@参数 lpEnvironment: 指向环境变量块的指针，用于指定新进程的环境变量。为NULL，表示使用当前进程的环境变量。
    //@参数 lpCurrentDirectory: 字符串指针，指定新进程的当前工作目录。
    //@参数 lpStartupInfo: 指向STARTUPINFO结构的指针，用于指定新进程的启动信息。
    //@参数 lpProcessInformation: 指向PROCESS_INFORMATION结构的指针，用于接收新进程的信息。
    //@参数 lpDllName: 字符串指针，指定要注入到新进程中的动态链接库(DLL)的名称。可以是完整路径。
    //@参数 pfCreateProcessA: 指向PDETOUR_CREATE_PROCESS_ROUTINEA类型函数的指针，用于创建新进程。如果为NULL，则默认使用CreateProcessA函数。
    //@返回 布尔值，表示函数执行成功或失败。
    //@别名 钩子创建进程并注入动态链接库扩展A(可执行文件路径, 命令行参数, 进程安全属性, 线程安全属性, 是否继承句柄, 进程创建标志, 环境变量指针, 当前工作目录, STARTUPINFO结构的指针, PROCESS_INFORMATION结构的指针, 要注入的DLL文件名称, 函数指针)
    BOOL WINAPI DetourCreateProcessWithDllExA(_In_opt_ LPCSTR lpApplicationName,
        __in_outopt_ LPSTR lpCommandLine,
        _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
        _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
        __in BOOL bInheritHandles,
        __in DWORD dwCreationFlags,
        _In_opt_ LPVOID lpEnvironment,
        _In_opt_ LPCSTR lpCurrentDirectory,
        __in LPSTARTUPINFOA lpStartupInfo,
        __out LPPROCESS_INFORMATION lpProcessInformation,
        __in LPCSTR lpDllName,
        _In_opt_ PDETOUR_CREATE_PROCESS_ROUTINEA pfCreateProcessA);

    //@备注 创建新进程并注入动态链接库(DLL)到新进程中的指定可执行文件中。
    //@参数 lpApplicationName: 字符串指针，指定要创建的进程的可执行文件名称，可以是完整路径。
    //@参数 lpCommandLine: 字符串指针，指定要传递给新进程的命令行参数。
    //@参数 lpProcessAttributes: 指向SECURITY_ATTRIBUTES结构的指针，用于指定新进程的安全属性。可以为NULL，表示使用默认的进程安全属性。
    //@参数 lpThreadAttributes: 指向SECURITY_ATTRIBUTES结构的指针，用于指定新线程的安全属性。可以为NULL，表示使用默认的线程安全属性。
    //@参数 bInheritHandles: 布尔值，指示新进程是否应该从父进程继承句柄。为TRUE，表示新进程继承句柄；为FALSE，表示不继承句柄。
    //@参数 dwCreationFlags: 标志位，指定新进程的创建标志。
    //@参数 lpEnvironment: 指向环境变量块的指针，用于指定新进程的环境变量。为NULL，表示使用当前进程的环境变量。
    //@参数 lpCurrentDirectory: 字符串指针，指定新进程的当前工作目录。
    //@参数 lpStartupInfo: 指向STARTUPINFO结构的指针，用于指定新进程的启动信息。
    //@参数 lpProcessInformation: 指向PROCESS_INFORMATION结构的指针，用于接收新进程的信息。
    //@参数 lpDllName: 字符串指针，指定要注入到新进程中的动态链接库(DLL)的名称。可以是完整路径。
    //@参数 pfCreateProcessA: 指向PDETOUR_CREATE_PROCESS_ROUTINEA类型函数的指针，用于创建新进程。如果为NULL，则默认使用CreateProcessA函数。
    //@返回 布尔值，表示函数执行成功或失败。
    //@别名 钩子创建进程并注入动态链接库扩展W(可执行文件路径, 命令行参数, 进程安全属性, 线程安全属性, 是否继承句柄, 进程创建标志, 环境变量指针, 当前工作目录, STARTUPINFO结构的指针, PROCESS_INFORMATION结构的指针, 要注入的DLL文件名称, 函数指针)
    BOOL WINAPI DetourCreateProcessWithDllExW(_In_opt_ LPCWSTR lpApplicationName,
        __in_outopt_  LPWSTR lpCommandLine,
        _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
        _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
        __in BOOL bInheritHandles,
        __in DWORD dwCreationFlags,
        _In_opt_ LPVOID lpEnvironment,
        _In_opt_ LPCWSTR lpCurrentDirectory,
        __in LPSTARTUPINFOW lpStartupInfo,
        __out LPPROCESS_INFORMATION lpProcessInformation,
        __in LPCSTR lpDllName,
        _In_opt_ PDETOUR_CREATE_PROCESS_ROUTINEW pfCreateProcessW);

#ifdef UNICODE
//@备注 UNICODE
//@别名 钩子创建进程并注入动态库扩展
#define DetourCreateProcessWithDllEx    DetourCreateProcessWithDllExW
#else
//@备注 ANSI
//@别名 钩子创建进程并注入动态库扩展
#define DetourCreateProcessWithDllEx    DetourCreateProcessWithDllExA
#endif // !UNICODE

    //@备注 以挂钩方式在创建进程之前注入多个动态链接库
    //@参数 lpApplicationName 字符串指针，指向待创建进程的可执行文件路径
    //@参数 lpCommandLine 字符串指针，指向传递给可执行文件的命令行参数
    //@参数 lpProcessAttributes 指向SECURITY_ATTRIBUTES结构的指针，用于设置新进程的安全属性
    //@参数 lpThreadAttributes 指向SECURITY_ATTRIBUTES结构的指针，用于设置新线程的安全属性
    //@参数 bInheritHandles 布尔值，指定是否从父进程继承句柄
    //@参数 dwCreationFlags DWORD值，用于指定新进程的创建标志
    //@参数 lpEnvironment 字符串指针，指向新进程的环境块
    //@参数 lpCurrentDirectory 字符串指针，指向新进程的当前工作目录
    //@参数 lpStartupInfo 指向STARTUPINFO结构的指针，用于指定新进程的启动信息
    //@参数 lpProcessInformation 指向PROCESS_INFORMATION结构的指针，用于接收新进程的相关信息
    //@参数 nDlls DWORD值，指定要注入的动态链接库的数量
    //@参数 rlpDlls 字符串指针数组，指定要注入的动态链接库的路径
    //@参数 pfCreateProcessA 指向PDETOUR_CREATE_PROCESS_ROUTINEA函数的指针，用于调用CreateProcess函数创建新进程
    //@返回 布尔值，表示函数是否执行成功
    //@别名 钩子创建进程并注入多个动态链接库W(可执行文件路径, 命令行参数, 进程安全属性, 线程安全属性, 是否继承句柄, 进程创建标志, 环境变量指针, 当前工作目录, STARTUPINFO结构的指针, PROCESS_INFORMATION结构的指针, 动态链接库数量, 动态链接库路径指针数组, 函数指针)
    BOOL WINAPI DetourCreateProcessWithDllsA(_In_opt_ LPCSTR lpApplicationName,
        __in_outopt_ LPSTR lpCommandLine,
        _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
        _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
        __in BOOL bInheritHandles,
        __in DWORD dwCreationFlags,
        _In_opt_ LPVOID lpEnvironment,
        _In_opt_ LPCSTR lpCurrentDirectory,
        __in LPSTARTUPINFOA lpStartupInfo,
        __out LPPROCESS_INFORMATION lpProcessInformation,
        __in DWORD nDlls,
        __in LPCSTR* rlpDlls,
        _In_opt_ PDETOUR_CREATE_PROCESS_ROUTINEA pfCreateProcessA);

//@备注 以挂钩方式在创建进程之前注入多个动态链接库
    //@参数 lpApplicationName 字符串指针，指向待创建进程的可执行文件路径
    //@参数 lpCommandLine 字符串指针，指向传递给可执行文件的命令行参数
    //@参数 lpProcessAttributes 指向SECURITY_ATTRIBUTES结构的指针，用于设置新进程的安全属性
    //@参数 lpThreadAttributes 指向SECURITY_ATTRIBUTES结构的指针，用于设置新线程的安全属性
    //@参数 bInheritHandles 布尔值，指定是否从父进程继承句柄
    //@参数 dwCreationFlags DWORD值，用于指定新进程的创建标志
    //@参数 lpEnvironment 字符串指针，指向新进程的环境块
    //@参数 lpCurrentDirectory 字符串指针，指向新进程的当前工作目录
    //@参数 lpStartupInfo 指向STARTUPINFO结构的指针，用于指定新进程的启动信息
    //@参数 lpProcessInformation 指向PROCESS_INFORMATION结构的指针，用于接收新进程的相关信息
    //@参数 nDlls DWORD值，指定要注入的动态链接库的数量
    //@参数 rlpDlls 字符串指针数组，指定要注入的动态链接库的路径
    //@参数 pfCreateProcessA 指向PDETOUR_CREATE_PROCESS_ROUTINEA函数的指针，用于调用CreateProcess函数创建新进程
    //@返回 布尔值，表示函数是否执行成功
    //@别名 钩子创建进程并注入多个动态链接库A(可执行文件路径, 命令行参数, 进程安全属性, 线程安全属性, 是否继承句柄, 进程创建标志, 环境变量指针, 当前工作目录, STARTUPINFO结构的指针, PROCESS_INFORMATION结构的指针, 动态链接库数量, 动态链接库路径指针数组, 函数指针)
    BOOL WINAPI DetourCreateProcessWithDllsW(_In_opt_ LPCWSTR lpApplicationName,
        __in_outopt_ LPWSTR lpCommandLine,
        _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
        _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
        __in BOOL bInheritHandles,
        __in DWORD dwCreationFlags,
        _In_opt_ LPVOID lpEnvironment,
        _In_opt_ LPCWSTR lpCurrentDirectory,
        __in LPSTARTUPINFOW lpStartupInfo,
        __out LPPROCESS_INFORMATION lpProcessInformation,
        __in DWORD nDlls,
        __in LPCSTR* rlpDlls,
        _In_opt_ PDETOUR_CREATE_PROCESS_ROUTINEW pfCreateProcessW);

#ifdef UNICODE
//@备注 UNICODE
//@别名 钩子创建进程并注入多个动态链接库
#define DetourCreateProcessWithDlls     DetourCreateProcessWithDllsW
#else
//@备注 ANSI
//@别名 钩子创建进程并注入多个动态链接库
#define DetourCreateProcessWithDlls     DetourCreateProcessWithDllsA
#endif // !UNICODE

    //@备注 以挂钩方式注入一个动态链接库到指定进程中，并使用指定的创建进程函数来启动目标进程
    //@参数 dwTargetPid DWORD值，指定要注入的进程的ID
    //@参数 lpDllName 字符串指针，指向要注入的动态链接库的路径
    //@参数 pfCreateProcessA 指向PDETOUR_CREATE_PROCESS_ROUTINEA函数的指针，用于调用CreateProcess函数或者其他可选的创建进程函数来启动目标进程
    //@返回 布尔值，表示函数是否执行成功
    //@别名 钩子辅助进程在目标进程注入动态库A(目标进程ID, 动态链接库路径, 函数指针)
    BOOL WINAPI DetourProcessViaHelperA(__in DWORD dwTargetPid,
        __in LPCSTR lpDllName,
        __in PDETOUR_CREATE_PROCESS_ROUTINEA pfCreateProcessA);

    //@备注 以挂钩方式注入一个动态链接库到指定进程中，并使用指定的创建进程函数来启动目标进程
    //@参数 dwTargetPid DWORD值，指定要注入的进程的ID
    //@参数 lpDllName 字符串指针，指向要注入的动态链接库的路径
    //@参数 pfCreateProcessA 指向PDETOUR_CREATE_PROCESS_ROUTINEA函数的指针，用于调用CreateProcess函数或者其他可选的创建进程函数来启动目标进程
    //@返回 布尔值，表示函数是否执行成功
    //@别名 钩子辅助进程在目标进程注入动态库W(目标进程ID, 动态链接库路径, 函数指针)
    BOOL WINAPI DetourProcessViaHelperW(__in DWORD dwTargetPid,
        __in LPCSTR lpDllName,
        __in PDETOUR_CREATE_PROCESS_ROUTINEW pfCreateProcessW);

#ifdef UNICODE
//@备注 UNICODE
//@别名 钩子辅助进程在目标进程注入动态库
#define DetourProcessViaHelper          DetourProcessViaHelperW
#else
//@备注 UNICODE
//@别名 钩子辅助进程在目标进程注入动态库
#define DetourProcessViaHelper          DetourProcessViaHelperA
#endif // !UNICODE

    //@备注 通过辅助进程在目标进程注入多个动态链接库
    //@参数 dwTargetPid DWORD值，目标进程的进程ID
    //@参数 nDlls DWORD值，指定要注入的动态链接库的数量
    //@参数 rlpDlls 字符串指针数组，指定要注入的动态链接库的路径
    //@参数 pfCreateProcessA 指向PDETOUR_CREATE_PROCESS_ROUTINEA函数的指针，用于在助手进程中调用CreateProcess函数创建新进程
    //@返回 布尔值，表示函数是否执行成功
    //@别名 钩子辅助进程在目标进程注入多个动态库A(目标进程ID, 动态链接库数量, 动态链接库路径指针数组, 函数指针) 通过助手进程在目标进程之前注入多个动态链接库
    BOOL WINAPI DetourProcessViaHelperDllsA(__in DWORD dwTargetPid,
        __in DWORD nDlls,
        __in LPCSTR* rlpDlls,
        __in PDETOUR_CREATE_PROCESS_ROUTINEA pfCreateProcessA);

    //@备注 通过辅助进程在目标进程注入多个动态链接库
    //@参数 dwTargetPid DWORD值，目标进程的进程ID
    //@参数 nDlls DWORD值，指定要注入的动态链接库的数量
    //@参数 rlpDlls 字符串指针数组，指定要注入的动态链接库的路径
    //@参数 pfCreateProcessA 指向PDETOUR_CREATE_PROCESS_ROUTINEA函数的指针，用于在助手进程中调用CreateProcess函数创建新进程
    //@返回 布尔值，表示函数是否执行成功
    //@别名 钩子辅助进程在目标进程注入多个动态库W(目标进程ID, 动态链接库数量, 动态链接库路径指针数组, 函数指针) 通过助手进程在目标进程之前注入多个动态链接库
    BOOL WINAPI DetourProcessViaHelperDllsW(__in DWORD dwTargetPid,
        __in DWORD nDlls,
        __in LPCSTR* rlpDlls,
        __in PDETOUR_CREATE_PROCESS_ROUTINEW pfCreateProcessW);

#ifdef UNICODE
//@备注 UNICODE
//@别名 钩子辅助进程在目标进程注入多个动态库
#define DetourProcessViaHelperDlls      DetourProcessViaHelperDllsW
#else
//@备注 ANSI
//@别名 钩子辅助进程在目标进程注入多个动态库
#define DetourProcessViaHelperDlls      DetourProcessViaHelperDllsA
#endif // !UNICODE

    //@备注 更新指定进程的动态链接库列表
    //@参数 hProcess 进程句柄，指定需要更新的目标进程
    //@参数 rlpDlls 字符串指针数组，指定要更新的动态链接库路径
    //@参数 nDlls DWORD值，指定要更新的动态链接库数量
    //@返回 布尔值，表示函数是否执行成功
    //@别名 钩子更新进程的动态链接库列表(Handle, 动态链接库路径指针数组, 动态链接库数量)
    BOOL WINAPI DetourUpdateProcessWithDll(__in HANDLE hProcess,
        __in LPCSTR* rlpDlls,
        __in DWORD nDlls);

    //@备注 在指定进程的上下文中更新动态链接库列表
    //@参数 hProcess 进程句柄，指定需要更新的目标进程
    //@参数 hImage 模块句柄，指定模块的基地址
    //@参数 bIs32Bit 布尔值，指示模块是32位还是64位
    //@参数 rlpDlls 字符串指针数组，指定要更新的动态链接库路径
    //@参数 nDlls DWORD值，指定要更新的动态链接库数量
    //@返回 布尔值，表示函数是否执行成功
    //@别名 钩子更新进程的动态链接库列表扩展(Handle, 模块句柄, 是否32位, 动态链接库路径指针数组, 动态链接库数量)
    BOOL WINAPI DetourUpdateProcessWithDllEx(__in HANDLE hProcess,
        __in HMODULE hImage,
        __in BOOL bIs32Bit,
        __in LPCSTR* rlpDlls,
        __in DWORD nDlls);

    //@备注 用于将负载数据拷贝到指定进程中
    //@参数 hProcess 进程句柄，用于指定目标进程
    //@参数 rguid 唯一标识符GUID，用于指定负载
    //@参数 pvData 用于存储负载数据的指针
    //@参数 cbData 负载数据的字节数
    //@返回 布尔值，表示函数是否执行成功
    //@别名 钩子将负载数据拷贝到指定进程中(Handle, GUID, 数据指针, 数据字节数)
    BOOL WINAPI DetourCopyPayloadToProcess(__in HANDLE hProcess,
        __in REFGUID rguid,
        __in LPCVOID pvData,
        __in DWORD cbData);

    //@备注 用于将payload数据拷贝到指定进程中，返回分配的内存地址
    //@参数 hProcess 进程句柄，用于指定目标进程
    //@参数 rguid 唯一标识符GUID，用于指定payload
    //@参数 pvData 用于存储payload数据的指针
    //@参数 cbData payload数据的字节数
    //@返回 分配的内存地址，如果操作失败则返回NULL
    //@别名 钩子将负载数据拷贝到指定进程中扩展(Handle, GUID, 数据指针, 数据字节数)
    PVOID WINAPI DetourCopyPayloadToProcessEx(__in HANDLE hProcess,
        __in REFGUID rguid,
        __in LPCVOID pvData,
        __in DWORD cbData);

    //@备注 恢复被挂钩函数的原始版本，用于结束DetourAttach、DetourAttachEx和DetourAttachEx辅助进程
    //@参数 无
    //@返回 布尔值，表示函数是否执行成功
    //@别名 钩子恢復被挂钩函数的原始版本(无参数)
    BOOL WINAPI DetourRestoreAfterWith(VOID);

    //@备注 恢复被挂钩函数的原始版本，用于结束DetourAttach、DetourAttachEx和DetourAttachEx辅助进程
    //@参数 pvData 用于存储被挂钩函数的原始版本的指针
    //@参数 cbData 被挂钩函数的原始版本的字节数
    //@返回 布尔值，表示函数是否执行成功
    //@别名 钩子恢復被挂钩函数的原始版本扩展(数据指针, 数据字节数)
    BOOL WINAPI DetourRestoreAfterWithEx(__in PVOID pvData,
        __in DWORD cbData);

    //@备注 用于判断当前进程是否为辅助进程
    //@参数 无
    //@返回 布尔值，表示当前进程是否为辅助进程
    //@别名 钩子判断当前进程是否为辅助进程(无参数)
    BOOL WINAPI DetourIsHelperProcess(VOID);

    //@备注 回调函数，用于判断当前进程是否为辅助进程
    VOID CALLBACK DetourFinishHelperProcess(__in HWND,
        __in HINSTANCE,
        __in LPSTR,
        __in INT);
    //@分组}
};

//////////////////////////////////////////////////////////////////////////////

    //@分组{ 系统类型补充
@别名 回调函数
#define CALLBACK    __stdcall
@别名 系统函数
#define WINAPI      __stdcall
#define WINAPIV     __cdecl
#define APIENTRY    WINAPI
#define APIPRIVATE  __stdcall
#define PASCAL      __stdcall

#define CONST               const
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL                *PBOOL;
typedef BOOL                *LPBOOL;
typedef BYTE                *PBYTE;
typedef BYTE                *LPBYTE;
typedef int                 *PINT;
typedef int                 *LPINT;
typedef WORD                *PWORD;
typedef WORD                *LPWORD;
typedef long                *LPLONG;
typedef DWORD               *PDWORD;
typedef DWORD               *LPDWORD;
typedef void                *LPVOID;
typedef CONST void          *LPCVOID;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;

#ifndef BASETYPES
#define BASETYPES
typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef char *PSZ;
#endif

#ifdef _WIN64
typedef IMAGE_NT_HEADERS64                  IMAGE_NT_HEADERS;
typedef PIMAGE_NT_HEADERS64                 PIMAGE_NT_HEADERS;
#else
typedef IMAGE_NT_HEADERS32                  IMAGE_NT_HEADERS;
typedef PIMAGE_NT_HEADERS32                 PIMAGE_NT_HEADERS;
#endif


#ifdef _WIN64
    typedef __int64 INT_PTR, *PINT_PTR;
    typedef unsigned __int64 UINT_PTR, *PUINT_PTR;

    typedef __int64 LONG_PTR, *PLONG_PTR;
    typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;

    #define __int3264   __int64

#else
    typedef int INT_PTR, *PINT_PTR;
    typedef unsigned int UINT_PTR, *PUINT_PTR;

    typedef long LONG_PTR, *PLONG_PTR;
    typedef unsigned long ULONG_PTR, *PULONG_PTR;

    #define __int3264   __int32

#endif

typedef struct _IMAGE_DOS_HEADER {      // DOS .EXE header
    WORD   e_magic;                     // Magic number
    WORD   e_cblp;                      // Bytes on last page of file
    WORD   e_cp;                        // Pages in file
    WORD   e_crlc;                      // Relocations
    WORD   e_cparhdr;                   // Size of header in paragraphs
    WORD   e_minalloc;                  // Minimum extra paragraphs needed
    WORD   e_maxalloc;                  // Maximum extra paragraphs needed
    WORD   e_ss;                        // Initial (relative) SS value
    WORD   e_sp;                        // Initial SP value
    WORD   e_csum;                      // Checksum
    WORD   e_ip;                        // Initial IP value
    WORD   e_cs;                        // Initial (relative) CS value
    WORD   e_lfarlc;                    // File address of relocation table
    WORD   e_ovno;                      // Overlay number
    WORD   e_res[4];                    // Reserved words
    WORD   e_oemid;                     // OEM identifier (for e_oeminfo)
    WORD   e_oeminfo;                   // OEM information; e_oemid specific
    WORD   e_res2[10];                  // Reserved words
    LONG   e_lfanew;                    // File address of new exe header
  } IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

typedef struct _GUID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[ 8 ];
} GUID;

typedef struct _PROCESS_INFORMATION {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD dwProcessId;
    DWORD dwThreadId;
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;

typedef struct _STARTUPINFOA {
    DWORD   cb;
    LPSTR   lpReserved;
    LPSTR   lpDesktop;
    LPSTR   lpTitle;
    DWORD   dwX;
    DWORD   dwY;
    DWORD   dwXSize;
    DWORD   dwYSize;
    DWORD   dwXCountChars;
    DWORD   dwYCountChars;
    DWORD   dwFillAttribute;
    DWORD   dwFlags;
    WORD    wShowWindow;
    WORD    cbReserved2;
    LPBYTE  lpReserved2;
    HANDLE  hStdInput;
    HANDLE  hStdOutput;
    HANDLE  hStdError;
} STARTUPINFOA, *LPSTARTUPINFOA;
typedef struct _STARTUPINFOW {
    DWORD   cb;
    LPWSTR  lpReserved;
    LPWSTR  lpDesktop;
    LPWSTR  lpTitle;
    DWORD   dwX;
    DWORD   dwY;
    DWORD   dwXSize;
    DWORD   dwYSize;
    DWORD   dwXCountChars;
    DWORD   dwYCountChars;
    DWORD   dwFillAttribute;
    DWORD   dwFlags;
    WORD    wShowWindow;
    WORD    cbReserved2;
    LPBYTE  lpReserved2;
    HANDLE  hStdInput;
    HANDLE  hStdOutput;
    HANDLE  hStdError;
} STARTUPINFOW, *LPSTARTUPINFOW;
#ifdef UNICODE
typedef STARTUPINFOW STARTUPINFO;
typedef LPSTARTUPINFOW LPSTARTUPINFO;

typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef struct _IMAGE_DATA_DIRECTORY {
    DWORD   VirtualAddress;
    DWORD   Size;
} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16

#define MAX_UCSCHAR (0x0010FFFF)

typedef UCSCHAR *PUCSCHAR;
typedef const UCSCHAR *PCUCSCHAR;

typedef UCSCHAR *PUCSSTR;
typedef UCSCHAR *PUUCSSTR;

typedef const UCSCHAR *PCUCSSTR;
typedef const UCSCHAR *PCUUCSSTR;

typedef UCSCHAR *PUUCSCHAR;
typedef const UCSCHAR *PCUUCSCHAR;

#endif // _WIN32_WINNT >= 0x0600


//
// ANSI (Multi-byte Character) types
//
typedef CHAR *PCHAR, *LPCH, *PCH;
typedef CONST CHAR *LPCCH, *PCCH;

typedef CHAR *NPSTR, *LPSTR, *PSTR;
typedef PSTR *PZPSTR;
typedef CONST PSTR *PCZPSTR;
typedef CONST CHAR *LPCSTR, *PCSTR;
typedef PCSTR *PZPCSTR;
typedef CONST PCSTR *PCZPCSTR;

typedef CHAR *PZZSTR;
typedef CONST CHAR *PCZZSTR;

typedef  CHAR *PNZCH;
typedef  CONST CHAR *PCNZCH;

//
// Neutral ANSI/UNICODE types and macros
//
#ifdef  UNICODE                     // r_winnt

#ifndef _TCHAR_DEFINED
typedef WCHAR TCHAR, *PTCHAR;
typedef WCHAR TBYTE , *PTBYTE ;
#define _TCHAR_DEFINED
#endif

typedef LPWCH LPTCH, PTCH;
typedef LPCWCH LPCTCH, PCTCH;
//typedef LPWSTR PTSTR, LPTSTR;
//typedef LPCWSTR PCTSTR, LPCTSTR;
//typedef LPUWSTR PUTSTR, LPUTSTR;
//typedef LPCUWSTR PCUTSTR, LPCUTSTR;
typedef LPWSTR LP;
typedef PZZWSTR PZZTSTR;
typedef PCZZWSTR PCZZTSTR;
typedef PUZZWSTR PUZZTSTR;
typedef PCUZZWSTR PCUZZTSTR;
typedef PZPWSTR PZPTSTR;
typedef PNZWCH PNZTCH;
typedef PCNZWCH PCNZTCH;
typedef PUNZWCH PUNZTCH;
typedef PCUNZWCH PCUNZTCH;
#define __TEXT(quote) L##quote      // r_winnt

#else                // r_winnt

#ifndef _TCHAR_DEFINED
typedef char TCHAR, *PTCHAR;
typedef unsigned char TBYTE , *PTBYTE ;
#define _TCHAR_DEFINED
#endif

typedef LPCH LPTCH, PTCH;
typedef LPCCH LPCTCH, PCTCH;
typedef LPSTR PTSTR, LPTSTR, PUTSTR, LPUTSTR;
typedef LPCSTR PCTSTR, LPCTSTR, PCUTSTR, LPCUTSTR;
typedef PZZSTR PZZTSTR, PUZZTSTR;
typedef PCZZSTR PCZZTSTR, PCUZZTSTR;
typedef PZPSTR PZPTSTR;
typedef PNZCH PNZTCH, PUNZTCH;
typedef PCNZCH PCNZTCH, PCUNZTCH;
#define __TEXT(quote) quote         // r_winnt

#endif                // r_winnt
#define TEXT(quote) __TEXT(quote)   // r_winnt


typedef SHORT *PSHORT;
typedef LONG *PLONG;

#define ALL_PROCESSOR_GROUPS        0xffff

typedef void *PVOID;
typedef void *HANDLE;
#if 0 && (_MSC_VER > 1000)
#define DECLARE_HANDLE(name) struct name##__; typedef struct name##__ *name
#else
#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
#endif


typedef HANDLE *PHANDLE;

typedef WORD                ATOM;   //BUGBUG - might want to remove this from minwin

struct HKEY__ {
    int unused;
}; typedef struct HKEY__* HKEY;
typedef HKEY* PHKEY;
struct HMETAFILE__ {
    int unused;
}; typedef struct HMETAFILE__* HMETAFILE;
struct HINSTANCE__ {
    int unused;
}; typedef struct HINSTANCE__* HINSTANCE;
typedef HINSTANCE HMODULE;
struct HRGN__ {
    int unused;
}; typedef struct HRGN__* HRGN;
struct HRSRC__ {
    int unused;
}; typedef struct HRSRC__* HRSRC;
struct HSPRITE__ {
    int unused;
}; typedef struct HSPRITE__* HSPRITE;
struct HLSURF__ {
    int unused;
}; typedef struct HLSURF__* HLSURF;
struct HSTR__ {
    int unused;
}; typedef struct HSTR__* HSTR;
struct HTASK__ {
    int unused;
}; typedef struct HTASK__* HTASK;
struct HWINSTA__ {
    int unused;
}; typedef struct HWINSTA__* HWINSTA;
struct HKL__ {
    int unused;
}; typedef struct HKL__* HKL;
    //@分组}
*/
