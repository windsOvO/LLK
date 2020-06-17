// CThemeOptionDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "CThemeOptionDlg.h"
#include "afxdialogex.h"


// CThemeOptionDlg 对话框

IMPLEMENT_DYNAMIC(CThemeOptionDlg, CDialogEx)

CThemeOptionDlg::CThemeOptionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONFIG_THEME, pParent)
{

}

CThemeOptionDlg::~CThemeOptionDlg()
{
}

void CThemeOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CThemeOptionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_STATIC_DIY, &CThemeOptionDlg::OnBnClickedStaticDiy)
END_MESSAGE_MAP()


// CThemeOptionDlg 消息处理程序


void CThemeOptionDlg::OnBnClickedStaticDiy()
{
	// TODO: 在此添加控件通知处理程序代码
}
