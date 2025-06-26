#ifndef HEAD_0DC09AC7_4B83_4a8c_9DE3_99FE33FB669D
#define HEAD_0DC09AC7_4B83_4a8c_9DE3_99FE33FB669D
class 主窗口类;
class 主窗口类  :  public  CXWindow
{
public:
	CXButton _百度一下;
	CXButton _按钮_回到顶部;
	CXEdit _搜索框;
	CXButton _按钮_新闻;
	CXText _布局文件= L"main.xml";
	int  运行();
	int  按钮点击_新闻(BOOL* 是否拦截);
	int  按钮点击_百度一下(BOOL* 是否拦截);
	int  编辑框_内容改变(BOOL* 是否拦截);
	int  按钮点击_回到顶部(BOOL* 是否拦截);
};
int WINAPI wWinMain(HINSTANCE 模块句柄, HINSTANCE 先前句柄, wchar_t* 命令行, int 窗口显示标识);
#endif
