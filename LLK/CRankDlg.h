#pragma once


// CRankDlg 对话框

class CRankDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRankDlg)

public:
	CRankDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRankDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RANK_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nMode;
	CListCtrl m_lstRank; // 列表控制类
	// 显示列表
	void displayRank(int nModel);

	virtual BOOL OnInitDialog();
	afx_msg void OnClickedRadio(UINT nID);
};
