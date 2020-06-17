﻿
// LLKDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "LLK.h"
#include "LLKDlg.h"
#include "afxdialogex.h"
#include "CGameDlg.h"
#include "CHelpDlg.h"
#include "CRankDlg.h"
#include "CSettingDlg.h"
// #include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLLKDlg 对话框



CLLKDlg::CLLKDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LLK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLLKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLLKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON2, &CLLKDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_BASIC, &CLLKDlg::OnClickedButtonBasic)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CLLKDlg::OnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_RELAX, &CLLKDlg::OnClickedButtonRelax)
	ON_BN_CLICKED(IDC_BUTTON_LEVEL, &CLLKDlg::OnClickedButtonLevel)
	ON_BN_CLICKED(IDC_BUTTON_RANK, &CLLKDlg::OnClickedButtonRank)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CLLKDlg::OnClickedButtonSetting)
END_MESSAGE_MAP()


// CLLKDlg 消息处理程序

BOOL CLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	initBackground();//位图加载至内存中

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLLKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		// 位拷贝函数,将位图从位图内存拷贝纸视频内存中去
		dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 位图放入位图内存DC中
void CLLKDlg::initBackground()
{
	// 加载位图
	CBitmap bmpMain;
	bmpMain.LoadBitmap(IDB_MAIN_BG);

	// 创建兼容DC
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);

	// 将位图选进DC
	m_dcMem.SelectObject(&bmpMain);
}


// 进入基本模式对话框
void CLLKDlg::OnClickedButtonBasic()
{
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg(BASIC);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void CLLKDlg::OnClickedButtonRelax()
{
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg(RELAX);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void CLLKDlg::OnClickedButtonLevel()
{
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg(LEVEL);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}

void CLLKDlg::OnClickedButtonHelp()
{
	CHelpDlg dlg;
	dlg.DoModal();
}

void CLLKDlg::OnClickedButtonRank()
{
	CRankDlg dlg;
	dlg.DoModal();
}


void CLLKDlg::OnClickedButtonSetting()
{
	CSettingDlg dlg;
	dlg.DoModal();
}
