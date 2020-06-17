#pragma once

#include "CThemeOptionDlg.h"

// CSettingDlg 对话框

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSettingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CThemeOptionDlg m_dlgTheme ;// 主题设置对话框

	CTabCtrl m_tabSetting; // 页控制类

	virtual BOOL OnInitDialog();
};
