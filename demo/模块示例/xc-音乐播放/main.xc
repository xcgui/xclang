#include <thread> 

类 CMainFrame
	HWINDOW m_hWindow
	播放音频 mp3
	整型 播放句柄 
	整型 播放位置 = 0
	整型 音量=50
	函数 整型 Run()
		BOOL bRes = XC_LoadResource("resource.res")
		m_hWindow = (HWINDOW)XC_LoadLayout("main.xml", 0)
		XEle_RegEventCPP(XC_GetObjectByName("btn3"), XE_BNCLICK, &CMainFrame::OnBtnClick3)
		XEle_RegEventCPP(XC_GetObjectByName("btn2"), XE_BNCLICK, &CMainFrame::OnBtnClick2)
		XEle_RegEventCPP(XC_GetObjectByName("btn1"), XE_BNCLICK, &CMainFrame::OnBtnClick)
		XEle_RegEventCPP(XC_GetObjectByName("ylzj"), XE_BNCLICK, &CMainFrame::OnBtnClick4)
		XEle_RegEventCPP(XC_GetObjectByName("yljx"), XE_BNCLICK, &CMainFrame::OnBtnClick5)
		//EVENT
		XWnd_AdjustLayout(m_hWindow)
		XWnd_ShowWindow(m_hWindow, SW_SHOW)
		返回 0
	
	函数 int  OnBtnClick4(BOOL *pbHandled)
		mp3.置音量(播放句柄,音量+10)
		返回 0
	函数 int  OnBtnClick5(BOOL *pbHandled)
		mp3.置音量(播放句柄,音量-10)
		返回 0
		
	函数 int  OnBtnClick3(BOOL *pbHandled)
		mp3.停止(播放句柄)
		返回 0
	函数 int  OnBtnClick2(BOOL *pbHandled)
		
		播放位置 = mp3.取播放位置(播放句柄)
		mp3.暂停(播放句柄)
		调试输出(播放位置)
		返回 0
	函数 int  OnBtnClick(BOOL *pbHandled)
		确认播放文件(播放位置)
		播放句柄 = mp3.置本地音频文件("中国人.mp3", 播放位置)
		mp3.置音量(播放句柄,音量)
		#嵌入代码
		std::thread t1(&CMainFrame::播放yinyue,mp3,播放句柄);
		t1.detach();
		#嵌入代码_结束
		返回 0
		
	函数 void 确认播放文件(int 播放位置)
		mp3.初始化()
		调试输出(播放位置)
		
		
	函数 静态 void 播放yinyue(播放音频 mp3,int 播放句柄)
	
		调试输出(播放句柄)
		mp3.播放(播放句柄, 1)
		整型 长度 = mp3.取音乐长度(播放句柄)
		调试输出(长度)	
		
		循环 mp3.取播放位置(播放句柄) < 长度
			//调试输出(mp3.取播放位置(播放句柄) )
			pass
			
函数 整型  入口函数_窗口()
	XInitXCGUI(真)
	CMainFrame  MainFrame
	MainFrame.Run()
	XRunXCGUI()
	XExitXCGUI()
	返回 0
