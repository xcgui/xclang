//@模块名称 格式日志
//@版本 0.1.1
//@日期 2022-11-26
//@作者 欧阳逸洛
//@模块备注 低延迟的高性能异步日志记录库
//注意事项：需要C++17
//包装源：https://github.com/MengRao/fmtlog license: MIT
//包装源：https://gitee.com/ouyang-yiluo/fmtlog license: MIT

//@依赖 module_base.h
//@依赖 module_cpp_std.h
//@依赖 module_wrapper_tools.h
//@依赖 module_fmt.h

//@隐藏{
#pragma once
#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max
#include "fmtlog.h"
#pragma pop_macro("min")
#pragma pop_macro("max")


//@隐藏}
//@src "fmtlog.cc"

//@别名 日志文件模式
enum LogFileMode {
    //@别名 日志文件模式_追加
    LogFileMode_Append = 0,
    //@别名 日志文件模式_截断
    LogFileMode_Truncate = 1,
};


//@隐藏{
#define LogLevel_DBG fmtlogW::DBG
#define LogLevel_INF fmtlogW::INF
#define LogLevel_WRN fmtlogW::WRN
#define LogLevel_ERR fmtlogW::ERR
#define LogLevel_OFF fmtlogW::OFF
using LogLevel = fmtlogW::LogLevel;
//@隐藏}

/*@声明
//@别名 日志级别
enum LogLevel
{
    //@别名 日志级别_调试
    LogLevel_DBG = 0,
    //@别名 日志级别_信息
    LogLevel_INF = 1,
    //@别名 日志级别_警告
    LogLevel_WRN = 2,
    //@别名 日志级别_错误
    LogLevel_ERR = 3,
    //@别名 日志级别_关闭
    LogLevel_OFF = 4
};
*/


//@别名 日志回调函数指针(纳秒,日志级别,地点,基本位置,线程名,消息,主体位置,日志文件位置)
typedef void (*LogCallbackFuncPtr)(int64_t ns, LogLevel level, fmt_wstring_view location, size_t basePos,
    fmt_wstring_view threadName, fmt_wstring_view msg, size_t bodyPos,
    size_t logFilePos);

//@别名 日志队列队满回调函数指针(用户数据)
typedef void (*LogQueueFullCallbackFuncPtr)(void* userData);

//@隐藏{
#define __FMTLOGW_S1(x) L ## x
#define __FMTLOGW_S2(x) __FMTLOGW_S1(x)
#define __FMTLOGW_LOCATION __FMTLOGW_S2(__FILE__ ":" __FMTLOG_S2(__LINE__))

#define FMTLOGW(level, format, ...)                       \
  do {                                                    \
    using char_type = wchar_t;                            \
    static uint32_t logId = 0;                            \
    if (!fmtlogT<char_type>::checkLogLevel(level)) break; \
    fmtlogWrapper<char_type>::impl.log(logId,fmtlogWrapper<char_type>::impl.tscns.rdtsc(),__FMTLOGW_LOCATION, level, format, ##__VA_ARGS__); \
  } while (0)


#define FMTLOGW_LIMIT(min_interval, level, format, ...)              \
  do {                                                               \
    using char_type = wchar_t;                                       \
    static uint32_t logId = 0;                                       \
    static int64_t limitNs = 0;                                      \
    if (!fmtlogT<char_type>::checkLogLevel(level)) break; \
    int64_t tsc = fmtlogWrapper<char_type>::impl.tscns.rdtsc();      \
    int64_t ns = fmtlogWrapper<char_type>::impl.tscns.tsc2ns(tsc);   \
    if (ns < limitNs) break;                                         \
    limitNs = ns + min_interval;                                     \
    fmtlogWrapper<char_type>::impl.log(logId, tsc,__FMTLOGW_LOCATION, level, format, ##__VA_ARGS__);\
  } while (0)


#define FMTLOGW_ONCE(level, format, ...)                                                    \
  do {                                                                                      \
    using char_type = wchar_t;                                                               \
    if (!fmtlogT<char_type>::checkLogLevel(level)) break;                         \
    fmtlogWrapper<char_type>::impl.logOnce(__FMTLOGW_LOCATION, level, format, ##__VA_ARGS__);\
  } while (0)

#define Log_Log(level, format, ...) FMTLOGW(level, format, ##__VA_ARGS__)
#define Log_LogOnce(level, format, ...) FMTLOGW_ONCE(level, format, ##__VA_ARGS__)
#define Log_LogLimit(min_interval, level, format, ...)    FMTLOGW_LIMIT(min_interval, level, format, ##__VA_ARGS__)


#if FMTLOG_ACTIVE_LEVEL <= FMTLOG_LEVEL_DBG
#define Log_LogDBG(format, ...) FMTLOGW(fmtlogW::DBG, format, ##__VA_ARGS__)
#define Log_LogOnceDBG(format, ...) FMTLOGW_ONCE(fmtlogW::DBG, format, ##__VA_ARGS__)
#define Log_LogLimitDBG(min_interval, format, ...) FMTLOGW_LIMIT(min_interval, fmtlogW::DBG, format, ##__VA_ARGS__)
#else
#define Log_LogDBG(format, ...) (void)0
#define Log_LogOnceDBG(format, ...) (void)0
#define Log_LogLimitDBG(min_interval, format, ...) (void)0
#endif

#if FMTLOG_ACTIVE_LEVEL <= FMTLOG_LEVEL_INF
#define Log_LogINF(format, ...) FMTLOGW(fmtlogW::INF, format, ##__VA_ARGS__)
#define Log_LogOnceINF(format, ...) FMTLOGW_ONCE(fmtlogW::INF, format, ##__VA_ARGS__)
#define Log_LogLimitINF(min_interval, format, ...) FMTLOGW_LIMIT(min_interval, fmtlogW::INF, format, ##__VA_ARGS__)
#else
#define Log_LogINF(format, ...) (void)0
#define Log_LogOnceINF(format, ...) (void)0
#define Log_LogLimitINF(min_interval, format, ...) (void)0
#endif

#if FMTLOG_ACTIVE_LEVEL <= FMTLOG_LEVEL_WRN
#define Log_LogWRN(format, ...) FMTLOGW(fmtlogW::WRN, format, ##__VA_ARGS__)
#define Log_LogOnceWRN(format, ...) FMTLOGW_ONCE(fmtlogW::WRN, format, ##__VA_ARGS__)
#define Log_LogLimitWRN(min_interval, format, ...) FMTLOGW_LIMIT(min_interval, fmtlogW::WRN, format, ##__VA_ARGS__)
#else
#define Log_LogWRN(format, ...) (void)0
#define Log_LogOnceWRN(format, ...) (void)0
#define Log_LogLimitWRN(min_interval, format, ...) (void)0
#endif

#if FMTLOG_ACTIVE_LEVEL <= FMTLOG_LEVEL_ERR
#define Log_LogERR(format, ...) FMTLOG(fmtlogW::ERR, format, ##__VA_ARGS__)
#define Log_LogOnceERR(format, ...) FMTLOG_ONCE(fmtlogW::ERR, format, ##__VA_ARGS__)
#define Log_LogLimitERR(min_interval, format, ...) FMTLOG_LIMIT(min_interval, fmtlogW::ERR, format, ##__VA_ARGS__)
#else
#define Log_LogERR(format, ...) (void)0
#define Log_LogOnceERR(format, ...) (void)0
#define Log_LogLimitERR(min_interval, format, ...) (void)0
#endif

//@隐藏}


/*@声明

//@别名 日志_记录(日志级别,格式文本,替换数据)
//@参数 LogLevel 日志级别_XX
void Log_Log(LogLevel level, const wchar_t* format, ...);

//@别名 日志_记录调试(格式文本,替换数据)
//@备注 日志级别为调试。
void Log_LogDBG(const wchar_t* format, ...);

//@别名 日志_记录信息(格式文本,替换数据)
//@备注 日志级别为信息。
void Log_LogINF(const wchar_t* format, ...);

//@别名 日志_记录警告(格式文本,替换数据)
//@备注 日志级别为警告。
void Log_LogWRN(const wchar_t* format, ...);

//@别名 日志_记录错误(格式文本,替换数据)
//@备注 日志级别为错误。
void Log_LogERR(const wchar_t* format, ...);


//@别名 日志_限制记录(最小间隔限制_ns,日志级别,格式文本,替换数据)
//@备注 限制日志消息的记录频率，低于最小间隔的日志将被丢弃。
//@参数 LogLevel 日志级别_XX
void Log_LogLimit(int64_t limitNs, LogLevel level, const wchar_t* format, ...);

//@别名 日志_限制记录调试(最小间隔限制_ns,格式文本,替换数据)
//@备注 日志级别为调试，限制日志消息的记录频率，低于最小间隔的日志将被丢弃。
void Log_LogLimitDBG(int64_t limitNs, const wchar_t* format, ...);

//@别名 日志_限制记录信息(最小间隔限制_ns,格式文本,替换数据)
//@备注 日志级别为信息，限制日志消息的记录频率，低于最小间隔的日志将被丢弃。
void Log_LogLimitINF(int64_t limitNs, const wchar_t* format, ...);

//@别名 日志_限制记录警告(最小间隔限制_ns,格式文本,替换数据)
//@备注 日志级别为警告，限制日志消息的记录频率，低于最小间隔的日志将被丢弃。
void Log_LogLimitWRN(int64_t limitNs, const wchar_t* format, ...);

//@别名 日志_限制记录错误(最小间隔限制_ns,格式文本,替换数据)
//@备注 日志级别为错误，限制日志消息的记录频率，低于最小间隔的日志将被丢弃。
void Log_LogLimitERR(int64_t limitNs, const wchar_t* format, ...);

//@别名 日志_纯记录(日志级别,格式文本,替换数据)
//@备注 禁用静态信息优化，减少每个日志语句消耗的运行时内存，适用于那些不频繁且对延迟不敏感的日志（例如程序初始化信息）。
//@参数 LogLevel 日志级别_XX
void Log_LogOnce(LogLevel level, const wchar_t* format, ...);

//@别名 日志_纯记录调试(格式文本,替换数据)
//@备注 日志级别为调试，禁用静态信息优化，减少每个日志语句消耗的运行时内存，适用于那些不频繁且对延迟不敏感的日志（例如程序初始化信息）。注意，不支持通过指针传递参数。
void Log_LogOnceDBG(const wchar_t* format, ...);

//@别名 日志_纯记录信息(格式文本,替换数据)
//@备注 日志级别为信息，禁用静态信息优化，减少每个日志语句消耗的运行时内存，适用于那些不频繁且对延迟不敏感的日志（例如程序初始化信息）。注意，不支持通过指针传递参数。
void Log_LogOnceINF(const wchar_t* format, ...);

//@别名 日志_纯记录警告(格式文本,替换数据)
//@备注 日志级别为警告，禁用静态信息优化，减少每个日志语句消耗的运行时内存，适用于那些不频繁且对延迟不敏感的日志（例如程序初始化信息）。注意，不支持通过指针传递参数。
void Log_LogOnceWRN(const wchar_t* format, ...);

//@别名 日志_纯记录错误(格式文本,替换数据)
//@备注 日志级别为错误，禁用静态信息优化，减少每个日志语句消耗的运行时内存，适用于那些不频繁且对延迟不敏感的日志（例如程序初始化信息）。注意，不支持通过指针传递参数。
void Log_LogOnceERR(const wchar_t* format, ...);
*/

//@隐藏{
#define Log_setLogFile(...) fmtlogW::setLogFile(__VA_ARGS__)
#define Log_poll(...) fmtlogW::poll(__VA_ARGS__)
#define Log_setFlushDelay(...) fmtlogW::setFlushDelay(__VA_ARGS__)
#define Log_setFlushLogLevel(...) fmtlogW::flushOn(__VA_ARGS__)
#define Log_setFlushBufSize(...) fmtlogW::setFlushBufSize(__VA_ARGS__)
#define Log_setLogCallback(...) fmtlogW::setLogCB(__VA_ARGS__)
#define Log_setLogQueueFullCallback(...) fmtlogW::setLogQFullCB(__VA_ARGS__)
#define Log_closeLogFile() fmtlogW::closeLogFile()
#define Log_setHeaderPattern(...) fmtlogW::setHeaderPattern(__VA_ARGS__)
#define Log_setThreadName(...) fmtlogW::setThreadName(__VA_ARGS__)
#define Log_setLogLevel(...) fmtlogW::setLogLevel(__VA_ARGS__)
#define Log_getLogLevel() fmtlogW::getLogLevel()
#define Log_checkLogLevel(...) fmtlogW::checkLogLevel(__VA_ARGS__)
#define Log_startPollingThread(...) fmtlogW::startPollingThread(__VA_ARGS__)
#define Log_stopPollingThread() fmtlogW::stopPollingThread()
//@隐藏}

/*@声明
//@别名 日志_置日志文件(文件名, 日志文件模式)
//@参数 truncate 参数为 真 时，如果文件已存在则清空文件，否则在文件尾部追加。

void Log_setLogFile(const wchar_t* filename, LogFileMode = LogFileMode_Append);

//@别名 日志_轮询(强制刷新)
//@备注 收集所有线程的日志信息并写入日志文件。如果未使用 日志_启动轮询线程()，用户需要重复调用 日志_轮询()。
//@参数 立即刷新内部的文件缓冲区并写出到日志文件。
void Log_poll(bool forceFlush = false);

//@别名 日志_置刷新触发日志级别(日志级别)
//@备注 如果当前消息的日志级别大于等于刷新触发日志级别，将触发刷新。
void Log_setFlushLogLevel(LogLevel logLevel);

//@别名 日志_置刷新缓冲区大小(字节数)
//@备注 如果文件缓冲区超过了指定的字节数，将触发刷新。
void Log_setFlushBufSize(uint32_t sizeByte);

//@别名 日志_置日志回调(回调函数指针,最低日志级别)
//@备注 为所有日志级别大于等于最低日志级别的日志消息设置一个回调函数。
void Log_setLogCallback(LogCallbackFuncPtr cb, LogLevel minCBLogLevel);

//@别名 日志_置日志队满回调(回调函数指针,用户数据)
//@备注 当日志队列已满时会调用回调函数
void Log_setLogQueueFullCallback(LogQueueFullCallbackFuncPtr cb, void* userData);

//@别名 日志_关闭日志文件()
//@备注 后续的日志消息不会写入文件，仍可使用回调函数。
void Log_closeLogFile();

//@别名 日志_置日志头格式(格式文本)
//@备注 格式参考 https://github.com/MengRao/fmtlog#format
void Log_setHeaderPattern(const wchar_t* pattern);

//@别名 日志_置线程名称(名称)
//@备注 为当前线程设置一个名称，它将显示在日志头的{t}部分。
void Log_setThreadName(const char* name);

//@别名 日志_置日志级别(日志级别)
//@备注 设置当前的日志级别，低于此级别的日志消息将被丢弃。
void Log_setLogLevel(LogLevel logLevel);

//@别名 日志_取日志级别()
static LogLevel Log_getLogLevel();

//@别名 日志_启动轮询线程(轮询间隔_纳秒)
//@备注 在后台启动一个轮询线程, 按指定的间隔周期式执行轮询。注意用户在线程运行时不能自己调用 日志_轮询()
void Log_startPollingThread(int64_t pollInterval_ns = 1000000);

//@别名 日志_停止轮询线程()
void Log_stopPollingThread();
*/