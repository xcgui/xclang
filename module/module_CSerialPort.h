// Created by  南小鱼封装 (QQ 128492656)
//
//下面是定义显示的模块名称
//@模块名称  南_串口通讯
//@版本  0.1
//@日期  2023-01-12
//@作者  南小鱼 (QQ 128492656) 封装 
//@模块备注  封装自CSerialPort串口开源跨平台源码  https://github.com/itas109/CSerialPort - V4.2.1.221107
//@依赖   无


#pragma once

//About CSerialPort start
#include  "CSerialPort\SerialPort.h"
#include "CSerialPort\SerialPortInfo.h"

using namespace itas109;

//===========================================
//CSerialPort 源文件 开始

//@src "src\SerialPort.cpp"
//@src "src\SerialPortBase.cpp"
//@src "src\SerialPortInfo.cpp"
//@src "src\SerialPortInfoBase.cpp"
//@src "src\SerialPortInfoWinBase.cpp"
//@src "src\SerialPortWinBase.cpp"
//About CSerialPort end

//CSerialPort 源文件 结束
//===========================================
/*@声明

/////将枚举值 作为全局变量 与结构体 声明到炫语言中去

@别名 串口信息_结构
struct SerialPortInfo
{
	@别名 串口信息_串口名称
    char portName[256];    ///< portName 串口名称
	@别名 串口信息_串口描述
    char description[256]; ///< description 串口描述
	@别名 串口信息_硬件id
    char hardwareId[256];  ///< hardwareId 硬件id
};


@别名 串口操作方式
enum OperateMode
{
	@别名 串口操作方式_异步
    AsynchronousOperate, ///< Asynchronous 异步
	@别名 串口操作方式_同步
    SynchronousOperate   ///< Synchronous 同步
};


// * 因为波特率为数值类型，所以理论上可以为任意值(包括下列定义)

@别名 串口波特率
enum BaudRate
{
	@别名 串口波特率_110
    BaudRate110 = 110,       ///< 110
	@别名 串口波特率_300
    BaudRate300 = 300,       ///< 300
	@别名 串口波特率_600
    BaudRate600 = 600,       ///< 600
	@别名 串口波特率_1200
    BaudRate1200 = 1200,     ///< 1200
	@别名 串口波特率_2400
    BaudRate2400 = 2400,     ///< 2400
	@别名 串口波特率_4800
    BaudRate4800 = 4800,     ///< 4800
	@别名 串口波特率_9600
    BaudRate9600 = 9600,     ///< 9600 recommend 推荐
	@别名 串口波特率_14400
    BaudRate14400 = 14400,   ///< 14400
	@别名 串口波特率_19200
    BaudRate19200 = 19200,   ///< 19200
	@别名 串口波特率_38400
    BaudRate38400 = 38400,   ///< 38400
	@别名 串口波特率_56000
    BaudRate56000 = 56000,   ///< 56000
	@别名 串口波特率_57600
    BaudRate57600 = 57600,   ///< 57600
	@别名 串口波特率_115200
    BaudRate115200 = 115200, ///< 115200
	@别名 串口波特率_921600
    BaudRate921600 = 921600  ///< 921600
};

//**
// * @brief the DataBits enum 数据位
// * @warning
// * by QextSerialPort:\n
// * 5 data bits cannot be used with 2 stop bits 5位数据位不能使用2位停止位\n
// * 1.5 stop bits can only be used with 5 data bits 1.5位停止位不能使用5位数据位\n
// * 8 data bits cannot be used with space parity on POSIX systems POSIX系统8位数据位不能使用0校验
// * @warning windows Number of bits/byte, 4-8 windows数据位范围为4 - 8
// *
 //
 
@别名 串口数据位
enum DataBits
{
	@别名 串口数据位_5
    DataBits5 = 5, ///< 5 data bits 5位数据位
	@别名 串口数据位_6
    DataBits6 = 6, ///< 6 data bits 6位数据位
	@别名 串口数据位_7
    DataBits7 = 7, ///< 7 data bits 7位数据位
	@别名 串口数据位_8
    DataBits8 = 8  ///< 8 data bits 8位数据位
};



@别名 串口校验
enum Parity
{
	@别名 串口校验_无校验
    ParityNone = 0,  ///< No Parity 无校验
	@别名 串口校验_奇校验
    ParityOdd = 1,   ///< Odd Parity 奇校验
	@别名 串口校验_偶校验
    ParityEven = 2,  ///< Even Parity 偶校验
	@别名 串口校验_1校验
    ParityMark = 3,  ///< Mark Parity 1校验
	@别名 串口校验_0校验
    ParitySpace = 4, ///< Space Parity 0校验
};



@别名 串口停止位
enum StopBits
{
	@别名 串口停止位_1
    StopOne = 0,        ///< 1 stop bit 1位停止位
	@别名 串口停止位_1点5
    StopOneAndHalf = 1, ///< 1.5 stop bit 1.5位停止位 - This is only for the Windows platform
	@别名 串口停止位_2
    StopTwo = 2         ///< 2 stop bit 2位停止位
};

@别名 串口流控制
enum FlowControl  //@brief the FlowControl enum 流控制
{
	@别名 串口流控制_无流控制
    FlowNone = 0,     ///< No flow control 无流控制
	@别名 串口流控制_硬件流控制
    FlowHardware = 1, ///< Hardware(RTS / CTS) flow control 硬件流控制
	@别名 串口流控制_软件流控制
    FlowSoftware = 2  ///< Software(XON / XOFF) flow control 软件流控制
};

@别名 串口错误代码
enum SerialPortError    // @brief the SerialPort error code 串口错误代码
{
	@别名 串口错误代码_系统错误
    SystemError = -1,          ///< system error 系统错误(如空指针、内存访问异常等)
	@别名 串口错误代码_没有错误
    NoError = 0,               ///< No error occurred 没有错误
	@别名 串口错误代码_未找到设备
    DeviceNotFoundError,       ///< device not found 未找到设备
	@别名 串口错误代码_权限错误
    PermissionError,           ///< permission error 权限错误
	@别名 串口错误代码_打开串口错误
    OpenError,                 ///< open error 打开串口错误
	@别名 串口错误代码_校验位错误
    ParityError,               ///< parity error 校验位错误
	@别名 串口错误代码_数据帧错误
    FramingError,              ///<
	@别名 串口错误代码_条件断点错误
    BreakConditionError,       ///<
	@别名 串口错误代码_写数据错误
    WriteError,                ///< write error 写数据错误
	@别名 串口错误代码_读数据错误
    ReadError,                 ///< read error 读数据错误
	@别名 串口错误代码_资源错误
    ResourceError,             ///<
	@别名 串口错误代码_不支持操作
    UnsupportedOperationError, ///<
	@别名 串口错误代码_未知错误
    UnknownError,              ///< unknown error 未知错误
	@别名 串口错误代码_超时
    TimeoutError,              ///< time out error 超时
	@别名 串口错误代码_串口未打开
    NotOpenError,              ///< not open serial port error 串口未打开
	@别名 串口错误代码_无效的参数
    InvalidParameterError      ///< invalid parameter error 无效的参数
};

//////串口通信类//// 

///
@别名 串口通信类
class CSerialPort
{
public:


     ///
	@备注  初始化函数,用于设定串口的相关参数
	@ 
	@参数  串口名称  默认 COM1 
	@参数  波特率  默认 9600
	@参数  校验位  默认 无校验
	@参数  数据位  默认 8
	@参数  停止位  默认 1
	@参数  流控制  默认 无流控制
	@参数  读取缓冲区大小 默认4096
	@返回  void  
	@别名  初始化串口(串口名称,波特率,校验位,数据位,停止位,流控制,读取缓冲区大小)
    void init(const char ,
              int baudRate =  BaudRate9600,
               Parity parity =  ParityNone,
               DataBits dataBits =  DataBits8,
               StopBits stopbits =  StopOne,
               FlowControl flowControl =  FlowNone,
              unsigned int readBufferSize = 4096);


	@备注  设置串口操作模式
	@ 同步 或 异步
	@返回  void  
	@别名  置串口操作模式(operateMode)
    void setOperateMode( OperateMode operateMode =  AsynchronousOperate);


    
	
	@备注  打开串口
	@ 
	@参数  
	@参数  
	@返回  逻辑型  
	@别名  打开串口()
	bool open();



     ///
	@备注  关闭串口
	@ 
	@参数  
	@参数  
	@返回  void  
	@别名  关闭串口()
    void close();


	@备注  是否已打开
	@ 
	@参数  
	@参数  
	@返回  逻辑型  
	@别名  是否已打开()
    bool isOpen();



	@备注  连接读取事件  用这个生成一个收到数据事件  
	@ 例子写法m_SerialPort.connectReadEvent(this);
	@ 在源文件中新建一个 类  继承 串口数据返回类  在这个类中 声明一个同名 {函数 虚函数 空类型 onReadEvent(常量 字符型A* portName, 正整型 readBufferLen)   // 串口接收事件}
	@ 在窗口类下面调用这个事件
	@参数  串口监听事件类
	@参数  
	@返回  整型  0 success 成功
	@别名  挂接读取事件(连接读取事件指针)
    int connectReadEvent(CSerialPortListener *event);   //event



	@备注  断开连接读取事件
	@ 
	@参数  
	@参数  
	@返回  整型  0 success 成功
	@别名  断开挂接读取事件()
    int disconnectReadEvent();


	@备注  获取读取缓冲区已使用大小
	@ 
	@参数  
	@参数  
	@返回  整型  返回读取缓冲区已使用大小
	@别名  获取读取缓冲区已使用大小()
    unsigned int getReadBufferUsedLen() const;



	@备注  读取指定长度数据
	@ 
	@参数  读取结果
	@参数  读取长度
	@返回  整型  返回读取缓冲区已使用大小
	@别名  读取数据(读取结果,读取长度)
    int readData(void *data, int size);


	@备注  读取所有数据
	@ 
	@参数  读取结果
	@参数  读取长度
	@返回  整型  返回读取字节数
	@别名  读取全部数据(读取结果)
    int readAllData(void *data);   
	
	
	




	@备注  读取一行数据
	@ 
	@参数  
	@参数  
	@返回  void  
	@别名  读一行数据(data,size)
    int readLineData(void *data, int size);   




	@备注  写入指定长度数据 (发送数据)
	@ 
	@参数  
	@参数  
	@返回  void  
	@别名  写入数据(data, size)
    int writeData(const void *data, int size);     


     ///
	@备注  设置调试模式 
	@ 
	@参数  
	@参数  
	@返回  void  
	@别名  置调试模式(isDebug)
    void setDebugModel(bool isDebug);


 

	@备注  设置读取间隔超时毫秒  使用定时器提高效率
	@ 
	@参数  读取间隔时间，单位：毫秒
	@返回  void  
	@别名  置读取间隔超时(msecs)
    void setReadIntervalTimeout(unsigned int msecs);



     
	@备注  获取读取间隔超时毫秒  使用定时器提高效率
	@ 
	@参数  读取间隔时间，单位：毫秒
	@返回  正整型，单位：毫秒  
	@别名  取读取间隔超时()
    unsigned int getReadIntervalTimeout();    

     



	@备注  置事件触发最小尺寸 读取通知触发最小字节数
	@ 
	@参数  
	@参数  
	@返回  void  
	@别名  置事件触发最小尺寸(minByteReadNotify)
    void setMinByteReadNotify(unsigned int minByteReadNotify = 2);



	@备注  获取最后的错误代码 
	@ 
	@返回  整型  
	@别名  取错误代码()
    int getLastError() const;



	@备注  清除错误信息 
	@ 
	@返回  void  
	@别名  清除错误代码()
    void clearError();


	@备注  设置串口名称 
	@ 
	@返回  void  
	@别名  置串口名称(portName)
    void setPortName(const char *portName);








	@备注  获取串口名称 
	@ 
	@返回  const char *  
	@别名  取串口名称()
    const char *getPortName() const;





	@备注  设置波特率 
	@ 
	@参数  
	@参数  
	@返回  void  
	@别名  置波特率(baudRate)
    void setBaudRate(int baudRate);




	@备注  获取波特率 
	@ 
	@参数  
	@参数  
	@返回  int  
	@别名  取波特率( )
    int getBaudRate() const;




	@备注  设置校验位 
	@ 
	@返回  void  
	@别名  置校验位( parity)
    void setParity( Parity parity);


	@备注  获取校验位 
	@ 
	@返回  Parity  返回校验位
	@别名  取校验位( ) 
	Parity getParity() const;




	@备注  设置数据位 
	@ 
	@参数  
	@参数  
	@返回  DataBits   
	@别名  置数据位( )
    void setDataBits( DataBits dataBits);



	@备注  获取数据位 
	@ 
	@参数  stopbits
	@参数  
	@返回  DataBits   
	@别名  取数据位( )
     DataBits getDataBits() const;




	@备注  设置停止位 
	@ 
	@参数  stopbits
	@参数  
	@返回  void   
	@别名  置停止位( )
    void setStopBits( StopBits stopbits);




	@备注  获取停止位 
	@ 
	@参数  
	@参数  
	@返回  StopBits   
	@别名  取停止位( )
     StopBits getStopBits() const;





	@备注  设置流控制 
	@ 
	@参数  flowControl [in]
	@参数  
	@返回  void   
	@别名  置流控制(串口流控制 )
    void setFlowControl( FlowControl flowControl);





	@备注  获取流控制 
	@ 
	@返回  串口流控制   
	@别名  取流控制( )
     FlowControl getFlowControl() const;




	@备注  设置缓冲区大小 
	@ 
	@返回  正整数   
	@别名  置读取缓冲区大小(size)
    void setReadBufferSize(unsigned int size);




	@备注  获取读取缓冲区大小 
	@ 
	@返回  正整数   
	@别名  取读取缓冲区大小()
    unsigned int getReadBufferSize() const;




	@备注  设置DTR 
	@ 
	@参数  
	@参数  
	@返回  void   
	@别名  置DTR(set)
    void setDtr(bool set = true);




	@备注  设置RTS 
	@ 
	@参数  
	@参数  
	@返回  void   
	@别名  置RTS(set )
    void setRts(bool set = true);




	@备注  设置数据位 
	@ 
	@参数  
	@参数  
	@返回  返回版本信息   const char *
	@别名  取版本信息()
   const char *getVersion();


};
////////////////
@别名 串口数据返回类
class CSerialPortListener
{


     // @brief on read event 响应读取事件
     // @param portName [out] the port name 串口名称 Windows:COM1 Linux:/dev/ttyS0
     // @param readBufferLen [out] read buffer length 读取缓冲区数据长度
     //
    
	@备注  响应串口的返回数据读取事件
	@ 
	@参数  串口名称
	@参数  读取缓冲区数据长度
	@返回  整型  返回读取缓冲区已使用大小
	@别名  响应读取事件()
	virtual void onReadEvent(const char *portName, unsigned int readBufferLen) = 0;
};



*/ // 声明尾部

//@隐藏{
typedef std::vector<itas109::SerialPortInfo> ItasSerialPortInfoList;
//@隐藏}
//

/*@声明
//虚拟一个假接口交给ide,class或者struct看情况修改
//@别名 串口列表信息类
class CSerialPortInfo{



    
     //@brief availablePortInfos 获取串口信息列表
     //@return return available port infolist 返回可用串口名称列表
     //
     @返回  串口信息列表
	 @别名 取可用串口列表()
    static ItasSerialPortInfoList availablePortInfos();
};
*/	
	
	//@brief SerialPortChange 串口列表数据转换到 炫语言动态数组
     //@return  返回可用串口名称列表 炫语言动态数组方式
	 
//@参数  串口信息列表
//@返回  动态数组<串口信息_结构>
//@别名 串口列表到动态数组(串口信息列表,动态数组_串口信息_结构)
inline void SerialPortListChange(ItasSerialPortInfoList&in,CXVector<SerialPortInfo>&out){
out.clear();
out.getVector()->insert(
out.getVector()->end(),
in.begin(),
in.end());
};




