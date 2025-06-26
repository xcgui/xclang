#ifndef HEAD_12D5FE2B_BF30_419f_8CEF_E97E75AE9925
#define HEAD_12D5FE2B_BF30_419f_8CEF_E97E75AE9925
class CQQ;
class CQQ  :  public  CXWindow
{
public:
	CXTree m_列表树;
	HTEMP m_hTemplate_group;
	HTEMP m_hTemplate_item;
	HTEMP m_hTemplate_item_Sel;
	HIMAGE m_hExpand;
	HIMAGE m_hExpandNo;
	HIMAGE m_hVip;
	HIMAGE m_hQZone;
	HIMAGE m_hAvatarLarge;
	HIMAGE m_hAvatarSmall;
	HWINDOW  初始化();
	int  OnTemplateCreate(tree_item_* pItem, int nFlag, BOOL* 是否拦截);
	int  OnTreeTemplateCreateEnd(tree_item_* pItem, int nFlag, BOOL* 是否拦截);
	int  OnDestroy(BOOL* 是否拦截);
};
int WINAPI wWinMain(HINSTANCE 模块句柄, HINSTANCE 先前句柄, wchar_t* 命令行, int 窗口显示标识);
#endif
