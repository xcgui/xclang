
函数 测试_AES_CBC()
	字节集  data = A"47CB94B87D984551"
	字节集  key = A"8EA7D2370B44C70B"
	字节集  iv = A"0000000000000000"
	字节集  ret = 校验_AES加密_CBC(data, key, iv, X_AES_PKCS7_PADDING)
	调试输出(ret.到十六进制文本A())
	
	如果 ret.到十六进制文本A(FALSE) == A"1a0ee160c2f0ddd18c14bae52b931ac0108f27b69d42d7f94ae2853809daaca8"
		调试输出("结果 正确")
	否则
		调试输出("结果错误")
	
	调试输出("-------解密-------------")
	ret = 校验_AES解密_CBC(ret, key, iv, X_AES_PKCS7_PADDING)
	调试输出(ret.取文本指针A())

函数 测试_AES_ECB()
	字节集  data = A"47CB94B87D984551"
	字节集  key = A"8EA7D2370B44C70B"
	字节集  ret = 校验_AES加密_ECB(data, key, X_AES_PKCS7_PADDING)
	调试输出(ret.到十六进制文本A())
	
	如果 ret.到十六进制文本A() == A"EA6C9CE848B7742F246B07F3EC926800C17E880405FD4F17E6AF0C30EC4AF271"
		调试输出("结果 正确")
	否则
		调试输出("结果错误")
	
	调试输出("-------解密-------------")
	ret = 校验_AES解密_ECB(ret, key, X_AES_PKCS7_PADDING)
	调试输出(ret.取文本指针A())

函数 整型 入口函数_窗口() //窗口程序入口函数, 程序启动优先进入此函数
	测试_AES_CBC()
	调试输出("==========================")
	测试_AES_ECB()
	返回 0


