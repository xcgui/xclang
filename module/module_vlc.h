
#pragma once

#include "module_base.h"

//@模块名称  VLC媒体播放器
//@版本  1.0
//@日期  2024-10-31
//@作者  易团雪/hxznhf
//@QQ 568415950
//@模块备注  VLC 是一款自由、开源的跨平台多媒体播放器及框架，可播放大多数多媒体文件
// 以及 DVD、音频 CD、VCD 及各类流媒体协议。
// 调用模块时需要将VLC依赖插件（plugins文件夹）复制到对应项目调试或运行目录下
// 依赖插件去官网：https://www.videolan.org/vlc/  从安装包提取“plugins”文件夹
//@依赖  module_xcgui.h 

#include "vlc/vlc.h"
#include "vlc/libvlc_media_player.h"

#ifdef _WIN64
//@复制文件 @当前模块路径 "lib64\libvlc.dll"
//@复制文件 @当前模块路径 "lib64\libvlccore.dll"
//@lib "lib64\\libvlc.lib"
//@lib "lib64\\libvlccore.lib"
#else
//@复制文件 @当前模块路径 "lib32\libvlc.dll"
//@复制文件 @当前模块路径 "lib32\libvlccore.dll"
//@lib "lib32\\libvlc.lib"
//@lib "lib32\\libvlccore.lib"

#endif

//@src "module_vlc.cpp"

#include "module_xcgui.h"

//@隐藏{
#include <windows.h>
#include <atlhost.h>
LRESULT CALLBACK WindowsProc_vlcParent(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);

// vlc容器窗口必须在其样式中设置 WS_CLIPCHILDREN。

class VLC_WindowBox
{
public:
    HWND hWnd= NULL;
    HELE LayEle = NULL;

    int onLayoutSizeChanged(HELE 来源句柄, BOOL *canceled)
    {

        int 宽度 = XEle_GetWidth(来源句柄);
        int 高度 = XEle_GetHeight(来源句柄);
        RECT rect;
        XEle_GetRect(来源句柄, &rect);
        MoveWindow(hWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);

        return 0;
    }
    int onLayoutShowed(HELE 来源句柄, BOOL show, BOOL *canceled)
    {
        ShowWindow(hWnd, show ? SW_SHOW : SW_HIDE);
        return 0;
    }

    BOOL Create(HWND 句柄, HELE 布局元素, int w, int h)
    {

        LayEle = 布局元素;
        XEle_RegEventCPP1(布局元素, XE_SIZE, (&VLC_WindowBox::onLayoutSizeChanged));
        XEle_RegEventCPP1(布局元素, XE_SHOW, (&VLC_WindowBox::onLayoutShowed));

        WNDCLASSEXW wc{};
        wc.hInstance = 0;
        wc.lpszClassName = TEXT("VLC_ParentHWND");
        wc.lpfnWndProc = WindowsProc_vlcParent;
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.cbSize = sizeof(WNDCLASSEXW);
        // 设置 wc.hbrBackground 黑色
        wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));

        // wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
        if (!RegisterClassExW(&wc))
        {
            return false;
        }
        int xpos = 0;
        int ypos = 0;
        hWnd = CreateWindowExW(0, TEXT("VLC_ParentHWND"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, xpos, ypos, w, h, (HWND)句柄, NULL, NULL, NULL);

        return hWnd == NULL;
    }

    void Redraw()
    {

        RECT m_rect;
        GetClientRect(hWnd, &m_rect);
        InvalidateRect(hWnd, &m_rect, true);
    }

    void Destroy()
    {

        if (LayEle)
        {
            XEle_RemoveEventCPP(LayEle, XE_SIZE, (&VLC_WindowBox::onLayoutSizeChanged));
            XEle_RemoveEventCPP(LayEle, XE_SHOW, (&VLC_WindowBox::onLayoutShowed));
        }
        if (hWnd)
        {
            DestroyWindow(hWnd);
            UnregisterClassW(TEXT("VLC_ParentHWND"), NULL);
        }
        LayEle = NULL;
        hWnd = NULL;
    }
};

//@隐藏}

/*@声明
     //@别名 VLC事件类型
    struct libvlc_event_t
    {
        //@别名 事件类型
        int   type; //< Event type (see @ref libvlc_event_e)
        //@别名 事件对象
        void *p_obj; //< Object emitting the event
        //@别名 事件数据
        //@备注 联合体类型，请用 取事件数据 函数获取数据
        void* u;
    };



    //@别名 播放状态
    enum libvlc_state_t
    {
        //@别名 播放状态_未指定
        libvlc_NothingSpecial = 0,
        //@别名 播放状态_打开
        libvlc_Opening,
        //@别名 播放状态_正在缓冲
        libvlc_Buffering,
        //@别名 播放状态_正在播放
        libvlc_Playing,
        //@别名 播放状态_暂停
        libvlc_Paused,
        //@别名 播放状态_停止
        libvlc_Stopped,
        //@别名 播放状态_结束
        libvlc_Ended,
        //@别名 播放状态_错误
        libvlc_Error
    };



    //@别名 VLC事件
    enum libvlc_event_e {

    //@别名 VLC事件_媒体元数据更改
    libvlc_MediaMetaChanged=0,
    //@别名 VLC事件_媒体子项添加
    libvlc_MediaSubItemAdded,
    //@别名 VLC事件_媒体时长更改
    libvlc_MediaDurationChanged,
    //@别名 VLC事件_媒体解析完成
    libvlc_MediaParsedChanged,
    //@别名 VLC事件_媒体释放
    libvlc_MediaFreed,
    //@别名 VLC事件_媒体状态更改
    libvlc_MediaStateChanged,
    //@别名 VLC事件_媒体子项树添加
    libvlc_MediaSubItemTreeAdded,

    //@别名 VLC事件_媒体播放器状态更改
    libvlc_MediaPlayerMediaChanged=0x100,

    libvlc_MediaPlayerNothingSpecial,
    //@别名 VLC事件_媒体播放器打开
    libvlc_MediaPlayerOpening,
    //@别名 VLC事件_媒体播放器缓冲
    libvlc_MediaPlayerBuffering,
    //@别名 VLC事件_媒体播放器播放
    libvlc_MediaPlayerPlaying,
    //@别名 VLC事件_媒体播放器暂停
    libvlc_MediaPlayerPaused,
    //@别名 VLC事件_媒体播放器停止
    libvlc_MediaPlayerStopped,

    libvlc_MediaPlayerForward,
    libvlc_MediaPlayerBackward,

    libvlc_MediaPlayerEndReached,
    libvlc_MediaPlayerEncounteredError,
    //@别名 VLC事件_媒体播放器时间改变
    libvlc_MediaPlayerTimeChanged,
    //@别名 VLC事件_媒体播放器进度改变
    libvlc_MediaPlayerPositionChanged,
    libvlc_MediaPlayerSeekableChanged,
    libvlc_MediaPlayerPausableChanged,
    libvlc_MediaPlayerTitleChanged,
    libvlc_MediaPlayerSnapshotTaken,
    libvlc_MediaPlayerLengthChanged,
    libvlc_MediaPlayerVout,
    libvlc_MediaPlayerScrambledChanged,
    libvlc_MediaPlayerESAdded,
    libvlc_MediaPlayerESDeleted,
    libvlc_MediaPlayerESSelected,
    libvlc_MediaPlayerCorked,
    libvlc_MediaPlayerUncorked,
    libvlc_MediaPlayerMuted,
    libvlc_MediaPlayerUnmuted,
    libvlc_MediaPlayerAudioVolume,
    libvlc_MediaPlayerAudioDevice,
    libvlc_MediaPlayerChapterChanged,

    };



    */

//@别名 VLC播放器
class vlcPlayer
{
private:
    libvlc_instance_t *Instance = nullptr;
    libvlc_media_player_t *Media_Player = nullptr;
    libvlc_media_t *Media = nullptr;
    libvlc_event_manager_t *Event_Manager = nullptr;

    HWND Currenthwnd = NULL;
    HWND Parenthwnd = NULL;
    VLC_WindowBox Prarent;

    void DisplayError(const wchar_t *msg);


public:
    //@别名 事件_媒体通知回调
    void *event_MediaCallBack = nullptr;
    //@别名 事件_播放器通知回调
    void *event_MediaPlayerCallBack = nullptr;
    vlcPlayer()
    {
    }
    ~vlcPlayer()
    {
        Destroy();
    }

    //@别名 置插件目录(路径)
    //@参数 插件目录的绝对路径
    //@备注 指定VLC依赖的插件目录，用于播放器解码相关等等功能，如果未指定，则使用默认目录（运行目录\plugins）
    // 插件区分32位和64位，请按需指定
    void SetPluginPath(const CXText &path);

    //@别名 创建(炫彩元素)
    BOOL Create(HELE element);

    //@别名 销毁()
    void Destroy();

    //@别名 取HWND()
    void GetCreatehwnd();

    //@别名 打开本地媒体(路径)
    BOOL Openlocalmedia(const CXText &path);

    //@别名 打开URL媒体(URL)
    BOOL OpenUrlmedia(const CXText &Urlpath);

    //@别名 播放()
    BOOL play();

    //@别名 暂停()
    void pause();

    //@别名 停止()
    void stop();

    //@别名 取音量()
    //@返回 音量，0为静音，100为最大
    int getVolume();

    //@别名 置音量(音量)
    //@参数 音量，0为静音，100为最大
    void setVolume(int value);

    //@别名 取静音状态()
    bool getMute();

    //@别名 置静音状态(状态)
    void setMute(bool status);

    //@别名 取播放速率()
    float getrate();

    //@别名 置播放速率(倍数)
    // 参数 播放速率，1.0为正常播放，<1.0为慢速播放，>1.0为快速播放
    void setrate(float rate);

    //@别名 取播放进度()
    // 返回 播放进度，0.0为开始，1.0为结束
    float getProgress();

    //@别名 置播放进度(百分比)
    // 参数 播放进度，0.0为开始，1.0为结束
    void setProgress(float percent);

    //@别名 取视频长度()
    int getDuration();

    //@别名 置播放时间(毫秒)
    void setPlayTime(int ms);

    //@别名 取播放状态()
    int getState();

    //@别名 取音轨数量()
    int getAudioTrackCount();
    //@别名 取音轨名称(索引)
    CXText getAudioTrackName(int index);

    //@别名 置音轨(索引)
    void setAudioTrack(int index);

    //@别名 注册播放器事件(事件类型,事件函数)
    //@参数 事件类型，常量 VLC事件_媒体播放器XXX
    void registEvent(int eventtype, void *event);

    //@别名 取事件数据(事件,数据)
    //@备注 请用 取事件数据 函数获取VLC事件数据，暂时只处理了播放进度和播放时间的事件参数值
    void getEventData(const libvlc_event_t *event, void *data);
};
