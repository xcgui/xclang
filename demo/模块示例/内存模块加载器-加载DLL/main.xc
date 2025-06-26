#函数类型  空类型(*Fn_DoSomething)()
函数 整型 入口函数() 
	控制台置中文编码()
	文件类 f1
	//先编译dll1
	如果 f1.打开(R"(..\内存模块加载器-dll1\Debug\内存模块加载器-dll1.dll)")
		字节集 data = f1.读取到字节集()
		控制台格式输出("dll大小 %d\n", data.取大小())
		如果 data.取大小()
			内存模块_模块句柄 h = 内存模块_加载(data)
			如果 h
				Fn_DoSomething DoSomething = (Fn_DoSomething)内存模块_取函数地址(h, A"DoSomething")
				如果 DoSomething
					DoSomething()
				否则
					控制台格式输出("失败 DoSomething函数指针为空\n")
			否则
				控制台格式输出("失败 模块句柄空\n")
		否则
			控制台格式输出("失败 文件为空\n")
	否则
		控制台格式输出("失败 无法打开文件\n")
	f1.关闭()
					
	控制台暂停()
	返回 0
