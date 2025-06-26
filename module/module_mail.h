#ifndef XC_SENDMAIL_H

//@隐藏{
#define XC_SENDMAIL_H

#include <string>
#include <vector>
#include <winsock2.h>
#include "util.hpp"

//@隐藏}

//@模块名称  Smtp邮件
//@版本  1.1
//@日期  2025-1-5
//@作者  peerless
//@QQ    598762663
//@模块备注 发送邮件封装
// 简化了操作流程,支持纯文本和附件
// 目前测试163邮箱成功

//@隐藏{

const int MAX_BUFFER_SIZE = 255;                       
const int SERVICE_PORT = 25; 

typedef std::vector<std::string> RECEIVERS;
//@隐藏}

//@别名 发送邮件类
class CSendMail
{
public:
//@隐藏{
    CSendMail();
    ~CSendMail();
//@隐藏}
    //@备注  smtp服务器地址，例：smtp.163.com
	//@别名 设置服务器()
    void setServerName(const char* server_name);     
	//@备注 设置用来发送邮件的邮箱账户
	//@别名 设置用户名()        
    void setUserName(const char* user_name);
	//@备注 设置用来发送邮件的邮箱授权码
	//@别名 设置授权码()   
    void setUserPwd(const char* user_pwd);
	//@备注 设置发送者的名字
	//@别名 设置发送者名称()   
    void setSenderName(const char* sender_name);       
	//@备注 设置发送者的邮箱(mail form:) 格式：邮箱地址。
	//@别名 设置发送邮箱()  
    void setSenderAddress(const char* sender_addr);   
	//@备注 添加接收者邮箱(mail to:) 格式：邮箱地址。支持多个
	//@别名 添加接收者()  
    void addReceiver(const char* address);
	//@备注 清空接收者邮箱
	//@别名 清空接收者()  
    void clearReceiver();
	//@备注 添加发送邮件的附件，文件全路径
	//@参数 路径  附件全路径
	//@别名 添加附件() 
    void AddFilePath(const char* path);
	//@备注 发送邮件前，需要先连接邮件服务器
	//@返回 返回bool结果
	//@别名 连接服务器() 
    bool Connent();
	//@备注 发送邮件
	//@返回 返回bool结果
	//@参数 标题  发送邮件标题
	//@参数 文本  发送邮件内容(宽字符)
	//@别名 发送邮件(标题,文本) 
    bool SendMail(const char* mail_title, const wchar_t* send_content); 
	//@备注 是否开启日志输出 exe当前目录LOG.tx文件
	//@参数 开关  是否开启日志
	//@别名 日志(开关) 
	void OutputLog(bool enable);
private:

    inline std::string& replace_all(std::string& str, const std::string& old_value, const std::string& new_value);       
    std::string GetFileName(std::string& szFilePath);        
    std::string GetFileData(std::string szFilePath);        
    std::string Base64Encode(std::string in_str);            
    int  sendRequest(const std::string content);                
    bool rcvResponse(const std::string expected_response);    

    bool CReateSocket();                                    
    bool Logon();                                            

    bool SendHead();
    bool SendTextOnly();                                        
    bool SendWithFileBody();                                    
    bool SendEnd();                                            

    SOCKET _socket;
    LogInfo m_logInfo;									
 
    std::string                    m_ServerName;       
    std::string                    m_UserName;           
    std::string                    m_UserPwd;           
    std::string                    m_SenderName;     
    std::string                    m_SenderAddr;        
    std::string                    m_MailTitle;        
    std::wstring                   m_TextBody;         

    RECEIVERS                      m_Receivers;       
    std::string                    m_FilePath;        

};

//@src "mail.cpp"

#endif
