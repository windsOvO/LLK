// CHelpDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "CHelpDlg.h"
#include "afxdialogex.h"
#include "Resource.h"


// CHelpDlg 对话框

IMPLEMENT_DYNAMIC(CHelpDlg, CDialogEx)

CHelpDlg::CHelpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HELP_DIALOG, pParent)
{

}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialogEx)
	ON_WM_VSCROLL()
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_STATIC_HELP, &CHelpDlg::OnStnClickedStaticHelp)
END_MESSAGE_MAP()


// CHelpDlg 消息处理程序


BOOL CHelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CClientDC dc(this);
	// 加载Help图片资源
	// 加载BMP图片资源
	HANDLE hBmpHelp = ::LoadImage(NULL, _T("theme\\picture\\basic_help.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内容兼容的内存DC
	m_dcHelp.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcHelp.SelectObject(hBmpHelp);

	// 创建内存DC大小
	CRect rtClient;
	this->GetWindowRect(&rtClient);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, rtClient.Width(), rtClient.Height());
	m_dcMem.SelectObject(&bmpMem);

	// 绘制白色背景
	m_dcMem.BitBlt(0, 0, rtClient.Width(), rtClient.Height(), NULL, 0, 0, WHITENESS);

	// 绘制帮助信息显示区域
	this->GetDlgItem(IDC_STATIC_HELP)->GetWindowRect(&m_rtHelp);
	this->ScreenToClient(&m_rtHelp);
	// 绘制帮助
	updateHelp(0);
	// 设置滚动条范围
	CBitmap bmpHelp;
	bmpHelp.Attach(hBmpHelp);
	BITMAP bmpInfo;
	bmpHelp.GetBitmap(&bmpInfo);

	// 设置滚动条的范围
	((CScrollBar*)this->GetDlgItem(IDC_SCROLLBAR_HELP))->SetScrollRange(0, bmpInfo.bmHeight);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CHelpDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos = pScrollBar->GetScrollPos();
	int nMinPos;
	int nMaxPos;
	pScrollBar->GetScrollRange(&nMinPos, &nMaxPos);    //得到滚动条的范围
	// 不同情况
	switch (nSBCode)
	{
	case SB_LINEUP:           //点击向上按钮
		pos -= 1;
		break;
	case SB_LINEDOWN:         //点击向下按钮
		pos += 1;
		break;
	case SB_PAGEUP:           //向上翻页
		pos -= 10;
		break;
	case SB_PAGEDOWN:         //向下翻页
		pos += 10;
		break;
	case SB_TOP:              //顶部
		pos = nMinPos;
		break;
	case SB_BOTTOM:           //底部
		pos = nMaxPos;
		break;
	case SB_THUMBPOSITION:    //点击在滑块上
		pos = nPos;
		break;
	default:
		break;
	}
	//设置滚动条当前点的值
	pScrollBar->SetScrollPos(pos, TRUE);
	//更新帮助信息
	updateHelp(pos);

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CHelpDlg::updateHelp(int pos)
{
	// 将重绘区，绘制成白色
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(),
		m_rtHelp.Height(), NULL, 0, 0, WHITENESS);
	// 绘制当前点的帮助信息
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(),
		m_rtHelp.Height(), &m_dcHelp, 0, pos, SRCCOPY);
	// 更新界面
	InvalidateRect(m_rtHelp, FALSE);
}

void CHelpDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
				   // TODO: 在此处添加消息处理程序代码
				   // 不为绘图消息调用 CDialogEx::OnPaint()
	//绘制背景图片
	dc.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcMem, 0, 0, SRCCOPY);
	CDialogEx::OnPaint();
}


void CHelpDlg::OnStnClickedStaticHelp()
{
	// TODO: 在此添加控件通知处理程序代码
}
