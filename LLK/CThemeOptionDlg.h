#pragma once


// CThemeOptionDlg 对话框

class CThemeOptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThemeOptionDlg)

public:
	CThemeOptionDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CThemeOptionDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_THEME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStaticDiy();
};
