函数 空类型 测试_MD5() //使用openssl 原生API 测试
	字节型   md_value[EVP_MAX_MD_SIZE] //保存输出的摘要值的数组
	正整型   md_len
	单字符型 msg1[] = A"Test Message1"	//待计算摘要的消息1
	单字符型 msg2[] = A"Test Message2"	//待计算摘要的消息2
	
	EVP_MD_CTX* mdctx = EVP_MD_CTX_new()   //EVP消息摘要结构体
	EVP_DigestInit_ex(mdctx, EVP_md5(), NULL)  //设置摘要算法和密码算法引擎，这里密码算法使用MD5，算法引擎使用OpenSSL默认引擎即软算法
	EVP_DigestUpdate(mdctx, msg1, strlen(msg1)) //调用摘要UpDate计算msg1的摘要
	EVP_DigestUpdate(mdctx, msg2, strlen(msg2)) //调用摘要UpDate计算msg2的摘要	
	EVP_DigestFinal_ex(mdctx, md_value, &md_len) //摘要结束，输出摘要值	
	EVP_MD_CTX_free(mdctx) //释放内存

	计次循环 正整型 i = 0; md_len
		控制台格式输出("%02x ", md_value[i])

函数 空类型 测试_摘要算法()
	单文本型  strMsg = A"Test Message1"
	字节集 encrypt_data1 = openssl_摘要(strMsg.取地址(), strMsg.取大小(), EVP_md5())
	字节集 encrypt_data2 = openssl_摘要(strMsg.取地址(), strMsg.取大小(), EVP_sha1())
	
函数 空类型 测试_加解密()
	单文本型  strMsg = A"Test Message1"
	单字符型 key[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }
	单字符型 iv[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }
	//AES加密
	字节集 encrypt_data = openssl_加解密(strMsg.取地址(), strMsg.取大小(), key, iv, 1, EVP_aes_128_cbc())
	单文本型 textHex3 = encrypt_data.到十六进制文本A()
	//AES解密
	字节集 decrypt_data = openssl_加解密(encrypt_data.取文本指针A(), encrypt_data.取大小(), key, iv, 0, EVP_aes_128_cbc())
	调试输出2(A"AES解密:", decrypt_data)
	//DES加密
	encrypt_data = openssl_加解密(strMsg.取地址(), strMsg.取大小(), key, iv, 1, EVP_des_ede_cbc())
	单文本型 textHex5 = encrypt_data.到十六进制文本A()
	//DES解密
	decrypt_data = openssl_加解密(encrypt_data.取文本指针A(), encrypt_data.取大小(), key, iv, 0, EVP_des_ede_cbc())
	调试输出2(A"DES解密", decrypt_data)

函数 空类型 测试_RSA()
	//RSA生成KEY
	EVP_PKEY* pKey = openssl_rsa_生成密钥对(512)
	如果 NULL == pKey
		返回
	单文本型  strMsg = A"Test Message1"
	//打印KEY
	单文本型 keyStr = openssl_rsa_key_打印(pKey, TRUE)
	调试输出2(keyStr)
	//加密
	字节集 encrypt_data = openssl_rsa_加密(pKey, strMsg.取地址(), strMsg.取大小())
	//解密
	字节集 decrypt_data = openssl_rsa_解密(pKey, encrypt_data.取文本指针A(), encrypt_data.取大小())
	//到PEM格式
	单文本型 keyPemStr = openssl_rsa_key_pem(pKey, TRUE, A"AES-256-CBC", A"my password")
	EVP_PKEY_free(pKey)
	
	//从PEM 中获取 KEY
	EVP_PKEY* pkey_pem = openssl_rsa_pem_取密钥(keyPemStr.取地址(), keyPemStr.取大小(), TRUE, A"my password")
	如果 pkey_pem
		keyStr = openssl_rsa_key_打印(pkey_pem, TRUE)
		EVP_PKEY_free(pkey_pem)

函数 整型 入口函数()
	测试_MD5()   //使用openssl 原生API 测试
	测试_摘要算法()
	测试_加解密()
	测试_RSA()
	控制台暂停()
	返回 0
