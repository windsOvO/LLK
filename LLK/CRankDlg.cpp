// CRankDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "CRankDlg.h"
#include "afxdialogex.h"
#include "global.h"
#include "CScoreLogic.h"


// CRankDlg 对话框

IMPLEMENT_DYNAMIC(CRankDlg, CDialogEx)

CRankDlg::CRankDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RANK_DIALOG, pParent)
{
	m_nMode = 0;
}

CRankDlg::~CRankDlg()
{
}

void CRankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_RELAX, m_nMode);
	DDX_Control(pDX, IDC_LIST_RANK, m_lstRank);
}


BEGIN_MESSAGE_MAP(CRankDlg, CDialogEx)
END_MESSAGE_MAP()


// CRankDlg 消息处理程序


BOOL CRankDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_lstRank.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_lstRank.InsertColumn(0, _T("排名"), LVCFMT_CENTER, 80, 0);
	m_lstRank.InsertColumn(1, _T("玩家"), LVCFMT_CENTER, 160, 0);
	m_lstRank.InsertColumn(2, _T("得分"), LVCFMT_CENTER, 80, 0);

	((CButton*)GetDlgItem(IDC_RADIO_RELAX))->SetCheck(TRUE);
	displayRank(RELAX);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CRankDlg::displayRank(int nModel)
{
	m_lstRank.DeleteAllItems();
	RankArray rankArray[MAX_RANK_LEVEL];
	// CScoreLogic sLogic;
	int rankNum = 0;
	//根据模式获取展示信息
	// rankNum = sLogic.SearchRank(rankArray, nModel);
	CString cRank;
	CString cGrade;

	for (int i = 0; (i < rankNum) && (i < MAX_RANK_LEVEL); i++)
	{
		cRank.Format(_T("%d"), i + 1);
		m_lstRank.InsertItem(i, cRank);
		m_lstRank.SetItemText(i, 1, rankArray[i].playerName);
		cGrade.Format(_T("%d"), rankArray[i].nGrade);
		m_lstRank.SetItemText(i, 2, cGrade);
	}
}
void CRankDlg::OnClickedRadio(UINT nID)
{
	switch (nID)
	{
		case IDC_RADIO_RELAX:
		{
			displayRank(RELAX);
		}break;
		case IDC_RADIO_LEVEL:
		{
			displayRank(LEVEL);
		}break;
		default:break;
	}
}
