﻿
类 我的吐司通知事件处理 继承 Win吐司事件处理接口
	函数 吐司已激活()常量 重写
		调试输出("吐司已激活")
	函数 吐司已激活(整型 操作按钮索引)常量 重写
		调试输出("吐司已激活, 操作按钮索引 = ", 操作按钮索引)
	函数 吐司被关闭(Win吐司关闭原因 状态)常量 重写
		调试输出("吐司被关闭,状态 =  ", 状态)
	函数 吐司失败()常量 重写
		调试输出("吐司失败")

函数 空类型 f()
	Win吐司::实例()->置应用程序名称("Windows吐司通知")
	文本型 应用id = Win吐司::配置应用程序ID("Windows", "吐司通知")
	Win吐司::实例()->置应用程序ID(应用id)
	Win吐司* wt = Win吐司::实例()->
	Win吐司错误 err = Win吐司错误_无错误
	如果 ! Win吐司::实例()->初始化(&err)
		调试输出("初始化失败 ", (int)err)
		返回

	Win吐司模板 wtt;
	如果 Win吐司::是否Win10周年纪念日版或更高()
		wtt = Win吐司模板(Win吐司模板类型_英雄图片和图片和文本02);
		wtt.置英雄图片路径(R"(C:\Users\Jin\Desktop\TestToast\res\hero.jpg)", 假)
	否则
		wtt = Win吐司模板(Win吐司模板类型_图片和文本02);
	wtt.置图片路径(R"(C:\Users\Jin\Desktop\TestToast\res\gal.jpg)", Win吐司模板裁剪方式_圆形)
	
	
	wtt.置字段文本("这是一条吐司通知", Win吐司模板文本字段_第一行)
	wtt.置字段文本("问好?", Win吐司模板文本字段_第二行)
	wtt.添加操作按钮("是")
	wtt.添加操作按钮("否")

	wtt.置持续时间(Win吐司模板持续时间_短)

	wtt.置音频选项(Win吐司模板音频选项_默认)

	wtt.置音频路径_从系统音频(Win吐司模板系统音频文件_呼叫)
	
	我的吐司通知事件处理* ptr = new 我的吐司通知事件处理  //不要delete, 显示吐司()处理
	如果 Win吐司::实例()->显示吐司(wtt, ptr) == -1
		调试输出("显示吐司失败")
		返回
	
	

函数 整型 入口函数()
	控制台置中文编码()
	f()
	延迟(1000)
	控制台暂停()
	返回 0
