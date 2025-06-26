//@模块名称 Win吐司通知
//@版本 0.2.0
//@日期 2022-10-31
//@作者 欧阳逸洛
//@模块备注 Windows吐司通知
//仓库地址：
//问题反馈：
//包装源：https://github.com/mohabouje/WinToast/ https://www.codeproject.com/Articles/5286393/Cplusplus-Windows-Toast-Notification
//包装源许可证： MIT

//@依赖 module_base.h
//@依赖 module_wrapper_tools.h


//@隐藏{
#pragma once

#include "src/wintoastlib.h"
//@隐藏}
//@src "src/wintoastlib.cpp"

//@隐藏{
using WinToastLib::WinToast;
using WinToastError = WinToast::WinToastError;
#define WinToastError_NoError WinToast::WinToastError::NoError
#define WinToastError_NotInitialized WinToast::WinToastError::NotInitialized
#define WinToastError_SystemNotSupported WinToast::WinToastError::SystemNotSupported
#define WinToastError_ShellLinkNotCreated WinToast::WinToastError::ShellLinkNotCreated
#define WinToastError_InvalidAppUserModelID WinToast::WinToastError::InvalidAppUserModelID
#define WinToastError_InvalidParameters WinToast::WinToastError::InvalidParameters
#define WinToastError_InvalidHandler WinToast::WinToastError::InvalidHandler
#define WinToastError_NotDisplayed WinToast::WinToastError::NotDisplayed
#define WinToastError_UnknownError WinToast::WinToastError::UnknownError
//@隐藏}
/*@声明
 //@别名 Win吐司错误
 enum WinToastError {

    //@别名 Win吐司错误_无错误
    WinToastError_NoError = 0,
    
    //@别名 Win吐司错误_未初始化
    WinToastError_NotInitialized,
    
    //@别名 Win吐司错误_系统不支持
    WinToastError_SystemNotSupported,
    
    //@别名 Win吐司错误_未创建ShellLink
    WinToastError_ShellLinkNotCreated,
    
    //@别名 Win吐司错误_无效应用ID
    WinToastError_InvalidAppUserModelID,
    
    //@别名 Win吐司错误_无效参数
    WinToastError_InvalidParameters,
    
    //@别名 Win吐司错误_无效处理程序
    WinToastError_InvalidHandler,
    
    //@别名 Win吐司错误_未显示
    WinToastError_NotDisplayed,
    
    //@别名 Win吐司错误_未知错误
    WinToastError_UnknownError
};
*/


//@隐藏{
using WinToastLib::WinToast;
using WinToastShortcutResult = WinToast;
#define WinToastShortcutResult_UNCHANGED WinToastShortcutResult::SHORTCUT_UNCHANGED
#define WinToastShortcutResult_WAS_CHANGED WinToastShortcutResult::SHORTCUT_WAS_CHANGED
#define WinToastShortcutResult_WAS_CREATED WinToastShortcutResult::SHORTCUT_WAS_CREATED
#define WinToastShortcutResult_MISSING_PARAMETERS WinToastShortcutResult::SHORTCUT_MISSING_PARAMETERS
#define WinToastShortcutResult_INCOMPATIBLE_OS WinToastShortcutResult::SHORTCUT_INCOMPATIBLE_OS
#define WinToastShortcutResult_COM_INIT_FAILURE WinToastShortcutResult::SHORTCUT_COM_INIT_FAILURE
#define WinToastShortcutResult_CREATE_FAILED WinToastShortcutResult::SHORTCUT_CREATE_FAILED

//@隐藏}
/*@声明
//@别名 Win吐司快捷方式结果
enum WinToastShortcutResult {

    //@别名 Win吐司快捷方式结果_未更改
    WinToastShortcutResult_UNCHANGED = 0,

    //@别名 Win吐司快捷方式结果_已更改
    WinToastShortcutResult_WAS_CHANGED,

    //@别名 Win吐司快捷方式结果_已创建
    WinToastShortcutResult_WAS_CREATED,

    //@别名 Win吐司快捷方式结果_缺少参数
    WinToastShortcutResult_MISSING_PARAMETERS,
    
    //@别名 Win吐司快捷方式结果_操作系统不兼容
    WinToastShortcutResult_INCOMPATIBLE_OS,
    
    //@别名 Win吐司快捷方式结果_COM初始化失败
    WinToastShortcutResult_COM_INIT_FAILURE,
    
    //@别名 Win吐司快捷方式结果_创建失败
    WinToastShortcutResult_CREATE_FAILED
};
*/


//@隐藏{
using WinToastLib::WinToast;
using WinToastShortcutPolicy = WinToast;
#define WinToastShortcutPolicy_IGNORE WinToastShortcutPolicy::SHORTCUT_POLICY_IGNORE
#define WinToastShortcutPolicy_WAS_CHANGED WinToastShortcutPolicy::SHORTCUT_POLICY_REQUIRE_NO_CREATE
#define WinToastShortcutPolicy_WAS_CREATED WinToastShortcutPolicy::SHORTCUT_POLICY_REQUIRE_CREATE

//@隐藏}
/*@声明
//@别名 Win吐司快捷方式策略
enum WinToastShortcutPolicy {

    //@别名 Win吐司快捷方式策略_保持现状
    WinToastShortcutPolicy_IGNORE = 0,

    //@别名 Win吐司快捷方式策略_无需创建
    WinToastShortcutPolicy_WAS_CHANGED,

    //@别名 Win吐司快捷方式策略_需要创建
    WinToastShortcutPolicy_WAS_CREATED
};
*/



//@隐藏{
using WinToastLib::WinToastTemplate;
using WinToastTemplateScenario = WinToastTemplate;
#define WinToastTemplateScenario_Default WinToastTemplateScenario::Default
#define WinToastTemplateScenario_Alarm WinToastTemplateScenario::Alarm
#define WinToastTemplateScenario_IncomingCall WinToastTemplateScenario::IncomingCall
#define WinToastTemplateScenario_Reminder WinToastTemplateScenario::Reminder

//@隐藏}
/*@声明
//@别名 Win吐司模板情景
enum WinToastTemplateScenario {

    //@别名 Win吐司模板情景_默认
    WinToastTemplateScenario_Default = 0,

    //@别名 Win吐司模板情景_警报
    WinToastTemplateScenario_Alarm,

    //@别名 Win吐司模板情景_来电
    WinToastTemplateScenario_IncomingCall,

    //@别名 Win吐司模板情景_提醒
    WinToastTemplateScenario_Reminder,
};
*/



//@隐藏{
using WinToastLib::WinToastTemplate;
using WinToastTemplateCropHint = WinToastTemplate;
#define WinToastTemplateCropHint_Square WinToastTemplateCropHint::Square
#define WinToastTemplateCropHint_Circle WinToastTemplateCropHint::Circle

//@隐藏}
/*@声明
//@别名 Win吐司模板裁剪方式
enum WinToastTemplateCropHint {

    //@别名 Win吐司模板裁剪方式_正方形
    WinToastTemplateCropHint_Square = 0,

    //@别名 Win吐司模板裁剪方式_圆形
    WinToastTemplateCropHint_Circle
};
*/

//@隐藏{
using WinToastLib::WinToastTemplate;
using WinToastTemplateDuration = WinToastTemplate;
#define WinToastTemplateDuration_System WinToastTemplateDuration::System
#define WinToastTemplateDuration_Short WinToastTemplateDuration::Short
#define WinToastTemplateDuration_Long WinToastTemplateDuration::Long

//@隐藏}
/*@声明
//@别名 Win吐司模板持续时间
enum WinToastTemplateDuration {

    //@别名Win吐司模板持续时间_系统
    WinToastTemplateDuration_System = 0,

    //@别名 Win吐司模板持续时间_短
    WinToastTemplateDuration_Short,

    //@别名 Win吐司模板持续时间_长
    WinToastTemplateDuration_Long
};
*/

//@隐藏{
using WinToastLib::WinToastTemplate;
using WinToastTemplateAudioOption = WinToastTemplate;
#define WinToastTemplateAudioOption_Default WinToastTemplateAudioOption::Default
#define WinToastTemplateAudioOption_Silent WinToastTemplateAudioOption::Silent
#define WinToastTemplateAudioOption_Loop WinToastTemplateAudioOption::Loop

//@隐藏}
/*@声明
//@别名 Win吐司模板音频选项
enum WinToastTemplateAudioOption {

    //@别名 Win吐司模板音频选项_默认
    WinToastTemplateAudioOption_Default = 0,

    //@别名 Win吐司模板音频选项_静音
    WinToastTemplateAudioOption_Silent,

    //@别名 Win吐司模板音频选项_循环
    WinToastTemplateAudioOption_Loop
};
*/


//@隐藏{
using WinToastLib::WinToastTemplate;
using WinToastTemplateTextField = WinToastTemplate;
#define WinToastTemplateTextField_FirstLine WinToastTemplateTextField::FirstLine
#define WinToastTemplateTextField_SecondLine WinToastTemplateTextField::SecondLine
#define WinToastTemplateTextField_ThirdLine WinToastTemplateTextField::ThirdLine

//@隐藏}
/*@声明
//@别名 Win吐司模板文本字段
enum WinToastTemplateTextField {

    //@别名 Win吐司模板文本字段_第一行
    WinToastTemplateTextField_FirstLine = 0,

    //@别名 Win吐司模板文本字段_第二行
    WinToastTemplateTextField_SecondLine,

    //@别名 Win吐司模板文本字段_第三行
    WinToastTemplateTextField_ThirdLine
};
*/

//@隐藏{
using WinToastLib::WinToastTemplate;
using WinToastTemplateType = WinToastTemplate;


#define WinToastTemplateType_ImageAndText01 WinToastTemplateType::ImageAndText01
#define WinToastTemplateType_ImageAndText02 WinToastTemplateType::ImageAndText02
#define WinToastTemplateType_ImageAndText03 WinToastTemplateType::ImageAndText03
#define WinToastTemplateType_ImageAndText04 WinToastTemplateType::ImageAndText04
#define WinToastTemplateType_Text01 WinToastTemplateType::Text01
#define WinToastTemplateType_Text02 WinToastTemplateType::Text02
#define WinToastTemplateType_Text03 WinToastTemplateType::Text03
#define WinToastTemplateType_Text04 WinToastTemplateType::Text04
#define WinToastTemplateType_HeroImageAndImageAndText01 WinToastTemplateType::HeroImageAndImageAndText01
#define WinToastTemplateType_HeroImageAndImageAndText02 WinToastTemplateType::HeroImageAndImageAndText02
#define WinToastTemplateType_HeroImageAndImageAndText03 WinToastTemplateType::HeroImageAndImageAndText03
#define WinToastTemplateType_HeroImageAndImageAndText04 WinToastTemplateType::HeroImageAndImageAndText04
#define WinToastTemplateType_HeroImageAndText01 WinToastTemplateType::HeroImageAndText01
#define WinToastTemplateType_HeroImageAndText02 WinToastTemplateType::HeroImageAndText02
#define WinToastTemplateType_HeroImageAndText03 WinToastTemplateType::HeroImageAndText03
#define WinToastTemplateType_HeroImageAndText04 WinToastTemplateType::HeroImageAndText04
//@隐藏}

/*@声明
//@别名 Win吐司模板类型
enum WinToastTemplateType {

//@别名 Win吐司模板类型_图片和文本01
WinToastTemplateType_ImageAndText01 = 0,

//@别名 Win吐司模板类型_图片和文本02
WinToastTemplateType_ImageAndText02,

//@别名 Win吐司模板类型_图片和文本03
WinToastTemplateType_ImageAndText03,

//@别名 Win吐司模板类型_图片和文本04
WinToastTemplateType_ImageAndText04,

//@别名 Win吐司模板类型_文本01
WinToastTemplateType_Text01,

//@别名 Win吐司模板类型_文本02
WinToastTemplateType_Text02,

//@别名 Win吐司模板类型_文本03
WinToastTemplateType_Text03,

//@别名 Win吐司模板类型_文本04
WinToastTemplateType_Text04,

//@别名 Win吐司模板类型_英雄图片和图片和文本01
WinToastTemplateType_HeroImageAndImageAndText01,

//@别名 Win吐司模板类型_英雄图片和图片和文本02
WinToastTemplateType_HeroImageAndImageAndText02,

//@别名 Win吐司模板类型_英雄图片和图片和文本03
WinToastTemplateType_HeroImageAndImageAndText03,

//@别名 Win吐司模板类型_英雄图片和图片和文本04
WinToastTemplateType_HeroImageAndImageAndText04,

//@别名 Win吐司模板类型_英雄图片和文本01
WinToastTemplateType_HeroImageAndText01,

//@别名 Win吐司模板类型_英雄图片和文本02
WinToastTemplateType_HeroImageAndText02,

//@别名 Win吐司模板类型_英雄图片和文本03
WinToastTemplateType_HeroImageAndText03,

//@别名 Win吐司模板类型_英雄图片和文本04
WinToastTemplateType_HeroImageAndText04
};
*/


//@隐藏{
using WinToastLib::WinToastTemplate;
using WinToastTemplateAudioSystemFile = WinToastTemplate;
#define WinToastTemplateAudioSystemFile_DefaultSound WinToastTemplateAudioSystemFile::DefaultSound
#define WinToastTemplateAudioSystemFile_IM WinToastTemplateAudioSystemFile::IM
#define WinToastTemplateAudioSystemFile_Mail WinToastTemplateAudioSystemFile::Mail
#define WinToastTemplateAudioSystemFile_Reminder WinToastTemplateAudioSystemFile::Reminder
#define WinToastTemplateAudioSystemFile_SMS WinToastTemplateAudioSystemFile::SMS
#define WinToastTemplateAudioSystemFile_Alarm WinToastTemplateAudioSystemFile::Alarm
#define WinToastTemplateAudioSystemFile_Alarm2 WinToastTemplateAudioSystemFile::Alarm2
#define WinToastTemplateAudioSystemFile_Alarm3 WinToastTemplateAudioSystemFile::Alarm3
#define WinToastTemplateAudioSystemFile_Alarm4 WinToastTemplateAudioSystemFile::Alarm4
#define WinToastTemplateAudioSystemFile_Alarm5 WinToastTemplateAudioSystemFile::Alarm5
#define WinToastTemplateAudioSystemFile_Alarm6 WinToastTemplateAudioSystemFile::Alarm6
#define WinToastTemplateAudioSystemFile_Alarm7 WinToastTemplateAudioSystemFile::Alarm7
#define WinToastTemplateAudioSystemFile_Alarm8 WinToastTemplateAudioSystemFile::Alarm8
#define WinToastTemplateAudioSystemFile_Alarm9 WinToastTemplateAudioSystemFile::Alarm9
#define WinToastTemplateAudioSystemFile_Alarm10 WinToastTemplateAudioSystemFile::Alarm10
#define WinToastTemplateAudioSystemFile_Call WinToastTemplateAudioSystemFile::Call
#define WinToastTemplateAudioSystemFile_Call1 WinToastTemplateAudioSystemFile::Call1
#define WinToastTemplateAudioSystemFile_Call2 WinToastTemplateAudioSystemFile::Call2
#define WinToastTemplateAudioSystemFile_Call3 WinToastTemplateAudioSystemFile::Call3
#define WinToastTemplateAudioSystemFile_Call4 WinToastTemplateAudioSystemFile::Call4
#define WinToastTemplateAudioSystemFile_Call5 WinToastTemplateAudioSystemFile::Call5
#define WinToastTemplateAudioSystemFile_Call6 WinToastTemplateAudioSystemFile::Call6
#define WinToastTemplateAudioSystemFile_Call7 WinToastTemplateAudioSystemFile::Call7
#define WinToastTemplateAudioSystemFile_Call8 WinToastTemplateAudioSystemFile::Call8
#define WinToastTemplateAudioSystemFile_Call9 WinToastTemplateAudioSystemFile::Call9
#define WinToastTemplateAudioSystemFile_Call10 WinToastTemplateAudioSystemFile::Call10

//@隐藏}
/*@声明
//@别名 Win吐司模板系统音频文件
enum WinToastTemplateAudioSystemFile {

    //@别名 Win吐司模板系统音频文件_默认声音
    WinToastTemplateAudioSystemFile_DefaultSound = 0,
    
    //@别名 Win吐司模板系统音频文件_通讯消息
    WinToastTemplateAudioSystemFile_IM,
    
    //@别名 Win吐司模板系统音频文件_邮件
    WinToastTemplateAudioSystemFile_Mail,
    
    //@别名 Win吐司模板系统音频文件_提醒
    WinToastTemplateAudioSystemFile_Reminder,
    
    //@别名 Win吐司模板系统音频文件_短信
    WinToastTemplateAudioSystemFile_SMS,
    
    //@别名 Win吐司模板系统音频文件_警报
    WinToastTemplateAudioSystemFile_Alarm,
    
    //@别名 Win吐司模板系统音频文件_警报2
    WinToastTemplateAudioSystemFile_Alarm2,
    
    //@别名 Win吐司模板系统音频文件_警报3
    WinToastTemplateAudioSystemFile_Alarm3,
    
    //@别名 Win吐司模板系统音频文件_警报4
    WinToastTemplateAudioSystemFile_Alarm4,
    
    //@别名 Win吐司模板系统音频文件_警报5
    WinToastTemplateAudioSystemFile_Alarm5,
    
    //@别名 Win吐司模板系统音频文件_警报6
    WinToastTemplateAudioSystemFile_Alarm6,
    
    //@别名 Win吐司模板系统音频文件_警报7
    WinToastTemplateAudioSystemFile_Alarm7,
    
    //@别名 Win吐司模板系统音频文件_警报8
    WinToastTemplateAudioSystemFile_Alarm8,
    
    //@别名 Win吐司模板系统音频文件_警报9
    WinToastTemplateAudioSystemFile_Alarm9,
    
    //@别名 Win吐司模板系统音频文件_警报10
    WinToastTemplateAudioSystemFile_Alarm10,
    
    //@别名 Win吐司模板系统音频文件_呼叫
    WinToastTemplateAudioSystemFile_Call,
    
    //@别名 Win吐司模板系统音频文件_呼叫1
    WinToastTemplateAudioSystemFile_Call1,
    
    //@别名 Win吐司模板系统音频文件_呼叫2
    WinToastTemplateAudioSystemFile_Call2,

    //@别名 Win吐司模板系统音频文件_呼叫3
    WinToastTemplateAudioSystemFile_Call3,
    
    //@别名 Win吐司模板系统音频文件_呼叫4
    WinToastTemplateAudioSystemFile_Call4,
    
    //@别名 Win吐司模板系统音频文件_呼叫5
    WinToastTemplateAudioSystemFile_Call5,
    
    //@别名 Win吐司模板系统音频文件_呼叫6
    WinToastTemplateAudioSystemFile_Call6,
    
    //@别名 Win吐司模板系统音频文件_呼叫7
    WinToastTemplateAudioSystemFile_Call7,
    
    //@别名 Win吐司模板系统音频文件_呼叫8
    WinToastTemplateAudioSystemFile_Call8,
    
    //@别名 Win吐司模板系统音频文件_呼叫9
    WinToastTemplateAudioSystemFile_Call9,
    
    //@别名 Win吐司模板系统音频文件_呼叫10
    WinToastTemplateAudioSystemFile_Call10
};
*/


//@隐藏{
using WinToastLib::IWinToastHandler;
using WinToastDismissalReason = IWinToastHandler;
#define WinToastDismissalReason_UserCanceled WinToastDismissalReason::UserCanceled
#define WinToastDismissalReason_ApplicationHidden WinToastDismissalReason::ApplicationHidden
#define WinToastDismissalReason_TimedOut WinToastDismissalReason::TimedOut

//@隐藏}
/*@声明
//@别名 Win吐司关闭原因
enum WinToastDismissalReason {

    //@别名 Win吐司关闭原因_用户取消
    WinToastDismissalReason_UserCanceled = 0,

    //@别名 Win吐司关闭原因_主动隐藏
    WinToastDismissalReason_ApplicationHidden,

    //@别名 Win吐司关闭原因_超时
    WinToastDismissalReason_TimedOut
};
*/


/*@声明

//@别名 Win吐司事件处理接口
class IWinToastHandler
{
public:
    //virtual ~IWinToastHandler() = default;
    virtual void 吐司已激活()  = 0;
    virtual void 吐司已激活(int 操作按钮索引)  = 0;
    virtual void 吐司被关闭(WinToastDismissalReason 状态)  = 0;
    virtual void 吐司失败()  = 0;
};




//@别名 Win吐司
class WinToast
{
public:
    //@别名 实例()
	static WinToast* instance();

    //@别名 是否兼容()
    static bool isCompatible();

    //@别名 是否支持现代功能()
    static bool isSupportingModernFeatures();

    //@别名 是否Win10周年纪念日版或更高()
    static bool isWin10AnniversaryOrHigher();

    //@别名 配置应用程序ID(公司名称,产品名称,子产品名称,版本信息)
    static CXText configureAUMI_XC(const CXText& companyName, 
                                 const CXText& productName, 
                                 const CXText& subProductName = L"", 
                                 const CXText& versionInformation = L"");
    
    //@别名 错误文本(错误)
    static const CXText strerror_XC(WinToastError error);

    //@别名 初始化(错误)
	virtual bool initialize(WinToastError* error = nullptr);

    //@别名 已初始化()
    virtual bool isInitialized() const;

    //@别名 隐藏吐司()
    virtual bool hideToast(INT64 id);

    //@别名 显示吐司(Win吐司模板,事件处理程序,错误)
    virtual INT64 showToast(const WinToastTemplate& toast, IWinToastHandler* eventHandler, WinToastError* error = nullptr);

    //@别名 清除()
    virtual void clear();    

    //@别名 创建快捷方式()
    virtual WinToastShortcutResult createShortcut();

    //@别名 应用程序名称()
    const CXText& appName_XC() const;

    //@别名 应用程序ID()
    const CXText& appUserModelId_XC() const;

    //@别名 置应用程序ID()
    void setAppUserModelId_XC(const CXText& aumi);

    //@别名 置应用程序名称(名称)
    void setAppName_XC(const CXText& appName);

    //@别名 置快捷方式策略(策略)
    void setShortcutPolicy(WinToastShortcutPolicy policy);
};


//@别名 Win吐司模板
 class WinToastTemplate {
public:
    //@别名 置第一行(文本)
    void setFirstLine_XC(const CXText& text);
    
    //@别名 置第二行(文本)
    void setSecondLine_XC(const CXText& text);
    
    //@别名 置第三行(文本)
    void setThirdLine_XC(const CXText& text);
    
    //@别名 置字段文本(文本,位置)
    void setTextField_XC(const CXText& txt, WinToastTemplateTextField pos);
    
    //@别名 置归属文本(归属文本)
    void setAttributionText_XC(const CXText& attributionText);
    
    //@别名 置图片路径(图片路径,图片裁剪方式)
    void setImagePath_XC(const CXText& imgPath, WinToastTemplateCropHint cropHint = WinToastTemplateCropHint_Square);
    
    //@别名 置英雄图片路径(图片路径,内联图片)
    void setHeroImagePath_XC(const CXText& imgPath, bool inlineImage);
    
    //@别名 置音频路径_从系统音频(路径)
    void setAudioPath(WinToastTemplateAudioSystemFile audio);
    
    //@别名 置音频路径_从文件(路径)
    void setAudioPath_XC(const CXText& audioPath);
    
    //@别名 置音频选项(选项)
    void setAudioOption(WinToastTemplateAudioOption audioOption);
    
    //@别名 置持续时间(持续时间)
    void setDuration(WinToastTemplateDuration duration);
    
    //@别名 置过期时间(毫秒数)
    void setExpiration(INT64 millisecondsFromNow);
    
    //@别名 置情景
    void setScenario(WinToastTemplateScenario scenario);
    
    //@别名 添加操作按钮(标题)
    void addAction_XC(const CXText& label);

    //@别名 文本字段数量()
    size_t textFieldsCount() const;
    
    //@别名 操作按钮数量()
    size_t actionsCount() const;
    
    //@别名 有图片()
    bool hasImage() const;
    
    //@别名 有英雄图片()
    bool hasHeroImage() const;
    
    //@别名 所有字段文本()
    const CXVector<CXText>& textFields_XC() const;
    
    //@别名 字段文本(位置)
    const CXText& textField_XC(WinToastTemplateTextField pos) const;
    
    //@别名 操作按钮标题(位置)
    const CXText& actionLabel_XC(size_t pos) const;
    
    //@别名 图片路径()
    const CXText& imagePath_XC() const;
    
    //@别名 英雄图片路径()
    const CXText& heroImagePath_XC() const;
    
    //@别名 音频路径()
    const CXText& audioPath_XC() const ;
    
    //@别名 归属文本()
    const CXText& attributionText_XC() const ;
    
    //@别名 情景()
    const CXText& scenario_XC() const ;

    //@别名 过期时间()
    INT64 expiration() const;
   
    //@别名 类型()
    WinToastTemplateType type() const;
    
    //@别名 音频选项()
    WinToastTemplateAudioOption audioOption() const;
   
    //@别名 持续时间()
    WinToastTemplateDuration duration() const;
    
    //@别名 为通用吐司()
    bool isToastGeneric() const;
    
    //@别名 为内联英雄图片()
    bool isInlineHeroImage() const;
    
    //@别名 为圆形裁剪方式()
    bool isCropHintCircle() const;
 };



*/

/*@声明
    



*/