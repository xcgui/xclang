﻿类 我的主窗口类 继承 窗口类
	[绑定信息] //IDE生成的UI绑定信息(UI变量,事件), 支持手动修改, 可收缩隐藏
		[窗口事件]
			[WM_PAINT, 事件_绘制, 1]
		
	//窗口句柄  _句柄
	//窗口类初始化, 自动处理关联的布局文件及绑定变量和注册事件
	函数 整型 运行(文本型 窗口布局文件 = "main.xml", 炫彩句柄 父句柄=0)
		//窗口_启用绘制背景(_句柄,真)
		显示(TRUE)
		
		返回 0

	函数 整型  事件_绘制(窗口句柄 句柄, 绘图句柄 hDraw, 逻辑型* 是否拦截)
		绘制(hDraw)
		GP图形类 图形

		//绘制_置画刷颜色(hDraw, 浅粉红)
		//结构_矩形 rc = {50,1,10+50,10+1 }
		//绘制_填充矩形(hDraw, &rc)
		整型 x
		整型 y
		绘制_取偏移(hDraw,&x,&y)
		图形.创建自场景句柄(绘制_取HDC(hDraw))
		图形.置平滑模式(GP平滑模式_抗锯齿)
		GP画笔类 画笔
		//GPColor 颜色操作
		画笔.创建自颜色(颜色_红色,10)
		//调试输出(绘制_取HDC(hDraw),图形.取句柄(),(int)图形.取最后状态())
		//画笔.置线帽(GP线帽_圆锚头帽,GP线帽_方锚头帽,GP虚线帽_三角线帽)
		图形.画直线(画笔, 193+x, 10+y, 360+x , 10+y)
		画笔.置起点线帽(GP线帽_三角线帽)
		
		图形.画直线I(画笔, 20 + x, 35, 20 + x, 150)
		画笔.置颜色(颜色_亮天蓝色)
		画笔.置宽度(2)
		图形.画圆弧(画笔, 170, 35, 50, 50, 1, 220)

		图形.画贝塞尔曲线(画笔,35,50,80,160,120,3,251,100)
		图形.画矩形(画笔, 32, 35, 50, 50)
		图形.画椭圆(画笔, 100, 35, 50, 50)
		图形.画饼(画笔, 240, 35, 50, 50, 10, 320)
		GP坐标类 坐标[3] //= new GP坐标类[3]
		坐标[0].X = 300
		坐标[0].Y = 40
		坐标[1].X = 350
		坐标[1].Y = 40
		坐标[2].X = 350
		坐标[2].Y = 88
		图形.画多边形I(画笔, 坐标, 3)
		图形.画曲线I(画笔,坐标,3)
		GP纯色画刷类 画刷
		画刷.创建(颜色_取ARGB(255,0, 0, 255))
		图形.填充矩形(画刷, 32, 100, 50, 50)
		画刷.置颜色(颜色_中宝石碧绿)
		图形.填充矩形(画刷, 100, 100, 50, 50)
		坐标[0].X = 300
		坐标[0].Y = 100
		坐标[1].X = 350
		坐标[1].Y = 100
		坐标[2].X = 350
		坐标[2].Y = 150
		画刷.置颜色(颜色_中紫罗兰红)
		图形.填充多边形I(画刷, 坐标,3,GP填充模式_交替)
		图形.填充椭圆(画刷,170, 100, 50, 50)
		图形.填充饼(画刷, 240, 100, 50, 50, 10, 320)
		文本型 wb = "炫彩绘制文本"
		GP字体类 字体
		GP矩形F类 jx = {10, 160, 200, 40}
		字体.创建自名称("微软雅黑",30,GP字体风格_加粗倾斜,GP单位_世界坐标)
		图形.画文本(wb, &字体, &画刷, &jx)
		GP文本格式类 文本格式
		GP矩形F类 测量矩形
		图形.测量文本矩形(wb, 字体, jx, 文本格式, &测量矩形)
		调试输出(测量矩形.Height, 测量矩形.Width)
		GP图像类 图像
		图像.创建自文件("大图标 (1).png", 假)
		图形.画图像部分(图像, 10, 200, 10, 30, 420, 100)
		GP图像属性类 图像属性
		调试输出((int)图像属性.置环绕模式(GP环绕模式_平铺))
		图形.DrawImageRectRect(图像, 360, 100, 200, 200, 0, 0, 48, 48, GP单位_像素, 图像属性)
		
		//GP矩形类 矩形
		//GP图像类 h
		//图像.取图像缩略图(10, 10, h, 空)
		//h.保存到文件("xc2.png", ImageFormatPNG)

		* 是否拦截 = 真
		返回 0
函数 整型 入口函数_窗口()
	炫彩_初始化(假)
	炫彩_加载资源文件("resource.res")

	我的主窗口类  我的主窗口
	我的主窗口.运行()

	炫彩_运行()
	炫彩_退出()
	返回 0

//炫语言手册:   http://www.xcgui.com/doc/

//动态库入口函数参考: https://docs.microsoft.com/zh-cn/windows/win32/dlls/dllmain?redirectedfrom=MSDN

//调试快捷键:   F5: 编译和调试, F7: 编译, F9:下断点, F10: 单步, F11: 步入
//函数参数展开: Ctrl+回车: 展开收缩, 表格内回车:收缩, ESC: 取消展开
//TAB:          缩进
//TAB + SHIFT: 减少缩进
//"/":      注释/取消注释
//Ctrl + G: 跳转到指定行
//Ctrl + F: 搜索和替换
//F12:      跳转到定义
//Alt + ↑: 向上交换行
//Alt + ↓: 向下交换行
//home:     移到光标到行首
//end:      移动光标到行尾
//双击打开项目: 系统设置->关联炫彩文件类型

//关于文本编码
//  首先你确定他是一个字符串
//  如果你是二进制数据存在字节集里, 那么显示字符串是乱码的
//  取地址 是单字符型;
//  首先你要指定你字节集里存的是不是文本
//  是单字节 的 还是双字节的
//  文本文件 读到内存 都是单字节字符串 char*;
//  你需要把他转换为 unicode 双字节字符串 wchar_t*
//  调试输出A 是单字节文本
//  你用 单文本型
//  不然你要转换下
//  文本文件一般都是单字节
//  A 与 W 转换
//  ascii和unicode都不清楚的吗
//  A2W()
//  W2A()
//  我一般都用 双字节 字符处理, 比较简单
//  因为中文 如果单字节 会占多个字节
//  还得判断
//
//  文本型    双字节字符串  =  A2W_(data.取地址(),-1)
//  A2W() 就是把易那种字符串 转换为 unicode
//  分割文本, 你就用宽字符串  w wchar_t
//  
//  A =  char  =  单字节
//  w = wchar_t = 双字节 = UNICODE
//
//  你看系统API 都有两个版本
//  CreateWindowA()
//  CreateWindowW()
//  
//  炫语言代码文件是utf-8, 默认编译没有加utf-8选项, 所以ascii文本运行输入任然是ascii文本
//
//  两个文件中结构体类型互相包含导致冲突, 请将结构体定义移动到一个独立文件中
