// CSettingDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "CSettingDlg.h"
#include "afxdialogex.h"


// CSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_DIALOG, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SETTING, m_tabSetting);
}



BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
END_MESSAGE_MAP()


// CSettingDlg 消息处理程序


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 为各标签页添加标题
	m_tabSetting.InsertItem(0, _T("主题设置"));
	m_tabSetting.InsertItem(1, _T("音效设置"));

	// m_dlgTheme.setConfig(pConfig);
	m_dlgTheme.Create(IDD_CONFIG_THEME, &m_tabSetting);

	// 获取并初始化显示位置
	CRect dlgRect;
	m_tabSetting.GetClientRect(&dlgRect);

	dlgRect.top += 20;
	dlgRect.left += 1;
	dlgRect.right -= 1;

	// 设置显示位置
	m_dlgTheme.MoveWindow(dlgRect);
	// 设置标签页0为显示
	m_dlgTheme.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
