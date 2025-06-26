函数 整型 解压进度回调函数(void* handle, mz_zip_file* file_info, const wchar_t* path, INT64 totalSize, INT64 curSize)
	浮点型 f = (浮点型)curSize / totalSize * 100.0f
	调试输出格式化("解压进度: %0.2f\n", f)
	返回 0

函数 测试_解压ZIP()
	CUnZip  unZip
	unZip.打开ZIP文件("D:\\Test\\abc.zip")
	unZip.置解压进度回调(解压进度回调函数)
	unZip.提取文件全部("C:\\Test\\AAA")

函数 测试_打包ZIP()
	CSaveZip  saveZip
	saveZip.创建ZIP("D:\\Test\\bbb.zip")
	saveZip.添加目录("D:\\Test\\ccc")
	saveZip.添加文件("D:\\Test\\111.txt", "aaa\\111.txt")

函数 测试_从ZIP中读取指定文件()
	CUnZip  unZip
	unZip.打开ZIP文件("D:\\Test\\abc.zip")

	unZip.提取文件单个("aaa\\111.txt", "D:\\Test\\111.txt")

	字节集  数据
	unZip.提取文件单个数据("aaa\\111.txt", 数据)

函数 测试_简化版接口()
	minizip_解压ZIP("D:\\Test\\AAA", "D:\\Test\\abc.zip")
	minizip_保存ZIP("D:\\Test\\abc.zip", "D:\\Test\\ccc")

函数 整型 入口函数_窗口() //窗口程序入口函数, 程序启动优先进入此函数
	测试_简化版接口()
	//测试_解压ZIP()
	//测试_打包ZIP()
	//测试_从ZIP中读取指定文件()
	返回 0