
// LLKDlg.h: 头文件
//

#pragma once


// CLLKDlg 对话框
class CLLKDlg : public CDialogEx
{
// 构造
public:
	CLLKDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LLK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	// 背景图形设备环境缓存
	CDC m_dcMem;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	// 初始化背景
	void initBackground();

public:
	afx_msg void OnClickedButtonBasic();
	afx_msg void OnClickedButtonHelp();
	afx_msg void OnClickedButtonRelax();
	afx_msg void OnClickedButtonLevel();
	afx_msg void OnClickedButtonRank();
	afx_msg void OnClickedButtonSetting();
};
