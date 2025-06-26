#include "common__.h"
#include "main__.h"
HWINDOW CQQ::初始化()
{
	BOOL bRes = XC_LoadResource(L"resource.res");
	m_hWindow = (HWINDOW)XC_LoadLayout(L"main.xml", 0);
	m_列表树.m_hEle = (HELE)XC_GetObjectByName(L"tree");
	xcl_log(m_列表树.m_hEle);
	m_列表树.EnableConnectLine(FALSE, FALSE);
	m_列表树.ShowSBarH(FALSE);
	m_列表树.SetIndentation(0);
	m_列表树.SetItemHeightDefault(28, 54);
	m_列表树.EnableTemplateReuse(TRUE);
	m_hTemplate_item = XTemp_Load(listItemTemp_type_tree, L"xml-template\\Tree_Item_friend.xml");
	m_hTemplate_item_Sel = XTemp_Load(listItemTemp_type_tree, L"xml-template\\Tree_Item_friend_sel.xml");
	m_hTemplate_group = XTemp_Load(listItemTemp_type_tree, L"xml-template\\Tree_Item_group.xml");
	m_hVip = XImage_LoadFile(L"image\\SuperVIP_LIGHT.png");
	m_hQZone = XImage_LoadFile(L"image\\QQZone.png");
	m_hAvatarSmall = XImage_LoadFile(L"image\\avatar_small.png");
	m_hAvatarLarge = XImage_LoadFile(L"image\\avatar_large.png");
	m_hExpand = XImage_LoadFile(L"image\\expand.png");
	m_hExpandNo = XImage_LoadFile(L"image\\expandno.png");
	XImage_EnableAutoDestroy(m_hExpandNo, FALSE);
	XImage_EnableAutoDestroy(m_hExpand, FALSE);
	CXAdapterTree 适配器;
	适配器.Create();
	适配器.AddColumn(L"name1");
	适配器.AddColumn(L"name2");
	适配器.AddColumn(L"name3");
	适配器.AddColumn(L"name4");
	适配器.AddColumn(L"name5");
	适配器.AddColumn(L"name6");
	m_列表树.BindAdapter(适配器.m_hAdapter);
	int nGroupID = 0;
	int nItemID = 0;
	{int iGroup = 0; auto __var_for_count__2 = iGroup + 3;
	for (;iGroup<__var_for_count__2;iGroup++)
	{
		CXText text = xcl_mkStr(L"好友分组 - ", iGroup);
		nGroupID = m_列表树.InsertItemText(text, XC_ID_ROOT, XC_ID_LAST);
		m_列表树.SetItemHeight(nGroupID, 26, 26);
		{int i = 0; auto __var_for_count__3 = i + 5;
		for (;i<__var_for_count__3;i++)
		{
			text = xcl_mkStr(L"我的好友-", i);
			nItemID = m_列表树.InsertItemText(text, nGroupID, XC_ID_LAST);
			m_列表树.SetItemTextEx(nItemID, L"name2", L"我的个性签签名");
			m_列表树.SetItemImageEx(nItemID, L"name5", m_hVip);
			m_列表树.SetItemImageEx(nItemID, L"name6", m_hQZone);
			m_列表树.SetItemImageEx(nItemID, L"name3", m_hAvatarSmall);
			m_列表树.SetItemImageEx(nItemID, L"name4", m_hAvatarLarge);
		}}
	}}
	XEle_RegEventCPP(m_列表树.m_hEle, XE_TREE_TEMP_CREATE, &CQQ::OnTemplateCreate);
	XEle_RegEventCPP(m_列表树.m_hEle, XE_TREE_TEMP_CREATE_END, &CQQ::OnTreeTemplateCreateEnd);
	XEle_RegEventCPP(m_列表树.m_hEle, XE_DESTROY, &CQQ::OnDestroy);
	AdjustLayout();
	Show(SW_SHOW);
	return m_hWindow;
}
int CQQ::OnTemplateCreate(tree_item_* pItem, int nFlag, BOOL* 是否拦截)
{
	xcl_log(L"OnTemplateCreate(): id:", pItem->nID, L", nFlag:", nFlag);
	if(XC_ID_ERROR != m_列表树.GetFirstChildItem(pItem->nID))
	{
		pItem->hTemp = m_hTemplate_group;
	}
	else if(tree_item_state_select == pItem->nState)
	{
		pItem->hTemp = m_hTemplate_item_Sel;
	}
	else
	{
		pItem->hTemp = m_hTemplate_item;
	}
	return 0;
}
int CQQ::OnTreeTemplateCreateEnd(tree_item_* pItem, int nFlag, BOOL* 是否拦截)
{
	xcl_log(L"OnTreeTemplateCreateEnd(): id:", pItem->nID, L", nFlag:", nFlag);
	if(1 == nFlag )
	{
		HELE hButtonExpand = (HELE)m_列表树.GetTemplateObject(pItem->nID, 1);
		if(hButtonExpand && XC_IsHELE(hButtonExpand))
		{
			if(m_hExpandNo)
			{
				XEle_AddBkImage(hButtonExpand, button_state_flag_leave|button_state_flag_check_no, m_hExpandNo);
				XEle_AddBkImage(hButtonExpand, button_state_flag_stay|button_state_flag_check_no, m_hExpandNo);
				XEle_AddBkImage(hButtonExpand, button_state_flag_down|button_state_flag_check_no, m_hExpandNo);
			}
			if(m_hExpand)
			{
				XEle_AddBkImage(hButtonExpand, button_state_flag_check, m_hExpand);
			}
			XEle_EnableBkTransparent(hButtonExpand, TRUE);
			XUI_SetStyle(hButtonExpand, button_style_default);
			XEle_EnableFocus(hButtonExpand, FALSE);
		}
	}
	return 0;
}
int CQQ::OnDestroy(BOOL* 是否拦截)
{
	xcl_log(L"OnDestroy()");
	if(m_hTemplate_group)
	{
	}
	XTemp_Destroy(m_hTemplate_group);
	if(m_hExpand)
	{
	}
	XImage_Destroy(m_hExpand);
	if(m_hExpandNo)
	{
	}
	XImage_Destroy(m_hExpandNo);
	if(m_hVip)
	{
	}
	XImage_Destroy(m_hVip);
	if(m_hQZone)
	{
	}
	XImage_Destroy(m_hQZone);
	if(m_hAvatarSmall)
	{
	}
	XImage_Destroy(m_hAvatarSmall);
	if(m_hAvatarLarge)
	{
	}
	XImage_Destroy(m_hAvatarLarge);
	return 0;
}
int WINAPI wWinMain(HINSTANCE 模块句柄, HINSTANCE 先前句柄, wchar_t* 命令行, int 窗口显示标识)
{
	XInitXCGUI(TRUE) ;
	CQQ qq;
	qq.初始化();
	XRunXCGUI();
	XExitXCGUI();
	return 0;
}
