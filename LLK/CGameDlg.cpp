// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include "CHelpDlg.h"
#include "resource.h"

#include "CGameBasic.h"
#include "CGameRelax.h"
#include "CGameLevel.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(int mode, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	// 初始化起始点坐标
	m_ptGameTop.x = MAP_LEFT;
	m_ptGameTop.y = MAP_TOP;
	// 初始化大小
	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;
	// 初始是第一次选
	isFirstSelect = true;
	// 确定游戏界面大小
	m_gameRect.left = m_ptGameTop.x;
	m_gameRect.top = m_ptGameTop.y;
	m_gameRect.right = m_gameRect.left + m_sizeElem.cx * MAX_COL;
	m_gameRect.bottom = m_gameRect.top + m_sizeElem.cy * MAX_ROW;

	bePlaying = false;
	bePause = false;
	
	// 模式
	gameMode = mode;
	if (gameMode == BASIC)
		gameControl = new CGameBasic;
	else if (gameMode == RELAX)
		gameControl = new CGameRelax;
	else if (gameMode == LEVEL)
		gameControl = new CGameLevel;
}

CGameDlg::~CGameDlg()
{
	delete gameControl;
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, gameProgress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &CGameDlg::OnClickedButtonStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_HINT, &CGameDlg::OnClickedButtonHint)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CGameDlg::OnClickedButtonReset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CGameDlg::OnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_HELP2, &CGameDlg::OnClickedButtonHelp2)
	ON_BN_CLICKED(IDC_BUTTON_GADGET, &CGameDlg::OnClickedButtonGadget)
END_MESSAGE_MAP()

void CGameDlg::initBackground()
{
	// 获取当前对话框的视频内存
	CClientDC dc(this);
	// 加载图片资源
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\china_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 创建于视频内存兼容的内存DC
	m_dcBg.CreateCompatibleDC(&dc);
	// 将位图资源选进DC
	m_dcBg.SelectObject(bmp);

	//初始化视频内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);
	//绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 800,600, &m_dcBg, 0, 0, SRCCOPY);

	// 加载掩盖图片
	// 加载BMP图片资源
	HANDLE bmpCover = ::LoadImage(NULL, _T("theme\\picture\\china_pause.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	m_dcCover.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcCover.SelectObject(bmpCover);
}

void CGameDlg::drawGameTime()
{
	/*
	CDC较繁琐
	*/
}


void CGameDlg::updateMap()
{
	// 绘制内容
	int left = m_ptGameTop.x;
	int top = m_ptGameTop.y;
	int elemWidth = m_sizeElem.cx;
	int elemHeight = m_sizeElem.cy;
	// mem现在的视频内存，bg背景内存，所以不能加载原来的，要替换
	m_dcMem.BitBlt(m_gameRect.left, m_gameRect.top, m_gameRect.Width(), m_gameRect.Height(),
		&m_dcBg, m_gameRect.left, m_gameRect.top, SRCCOPY);
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			// 没有掩码绘制
			// m_dcMem.BitBlt(left + j * elemWidth, top + i * elemHeight, elemWidth, elemHeight,
			//	&m_dcElement, 0, m_anMap[i][j] * elemHeight, SRCCOPY);
			// 注意是x是横坐标，y是纵坐标
			int info = gameControl->getElement(i, j);
			m_dcMem.BitBlt(left + j * elemWidth, top + i * elemHeight, elemWidth, elemHeight,
				&m_dcMask, 0, info * elemHeight, SRCPAINT);
			m_dcMem.BitBlt(left + j * elemWidth, top + i * elemHeight, elemWidth, elemHeight,
				&m_dcElement, 0, info * elemHeight, SRCAND);
		}
	}
}

void CGameDlg::updateWindow()
{
	// 调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	// 标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	// 设置窗口大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	CenterWindow();
}


// CGameDlg 消息处理程序

// 初始化函数
BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	initBackground();
	initElement();

	// 调用更新窗口函数
	updateWindow();

	// 关闭按钮
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(0);
	GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(0);
	GetDlgItem(IDC_BUTTON_HINT)->EnableWindow(0);

	if (gameMode == BASIC)
	{
		GetDlgItem(IDC_STATIC_LEVEL)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON_GADGET)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_SCORE)->ShowWindow(FALSE);
	}
	else if (gameMode == RELAX)
	{
		GetDlgItem(IDC_STATIC_LEVEL)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PAUSE)->ShowWindow(FALSE);
		GetDlgItem(IDC_GAME_TIME)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_TIME)->ShowWindow(FALSE);
	}
	else if (gameMode == LEVEL)
	{
		GetDlgItem(IDC_BUTTON_PAUSE)->ShowWindow(FALSE);
		GetDlgItem(IDC_GAME_TIME)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_TIME)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON_GADGET)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_SCORE)->ShowWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

void CGameDlg::initElement()
{
	// 获取当前对话框的视频内存
	CClientDC dc(this);
	// 加载图片资源
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\landscape_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 创建于视频内存兼容的内存DC
	m_dcElement.CreateCompatibleDC(&dc);
	// 将位图资源选进DC
	m_dcElement.SelectObject(bmp);

	// 掩码
	HANDLE bmpMask = ::LoadImage(NULL, _T("theme\\picture\\landscape_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 创建于视频内存兼容的内存DC
	m_dcMask.CreateCompatibleDC(&dc);
	// 将位图资源选进DC
	m_dcMask.SelectObject(bmpMask);
}


void CGameDlg::OnClickedButtonStart()
{
	gameControl->startGame();
	// 游戏中不能点击
	bePlaying = true;
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(1);
	GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(1);
	GetDlgItem(IDC_BUTTON_HINT)->EnableWindow(1);

	// 初始时间是300
	timeCount = 120;

	// 进度条
	gameProgress.SetRange(0, timeCount);
	gameProgress.SetStep(-1);
	gameProgress.SetPos(timeCount);
	// 启动计时器
	this->SetTimer(PLAY_TIMER_ID, 1000, NULL); // NULL即默认回调函数OnTimer
	// 单独显示一次
	CString str;
	str.Format(_T("%d"), timeCount);
	SetDlgItemText(IDC_EDIT_TIME, str);
	timeCount--; // 修正进度条延缓的bug
	// 绘制当前秒数
	// drawGameTime();

	// 调用绘制地图函数
	updateMap();
	// 客户区无效，重新绘制
	// false不擦书背景
	Invalidate(FALSE);
}


void CGameDlg::OnClickedButtonHint()
{
	// 没有进行游戏，则返回
	if (bePlaying == false || bePause == true)
		return;
	// 如果能够连通，绘制提示框和连接线并更新游戏地图
	Vertex path[MAX_VERTEX_NUM];
	int num = 0;
	if (gameControl->help(path, num))
	{
		//画第一个点的提示框
		drawTipFrame(path[0].row, path[0].col);
		//画第一个点的提示框
		drawTipFrame(path[num - 1].row, path[num - 1].col);
		//画提示线
		drawTipLine(path, num);

		updateMap();	//更新地图
		Sleep(1000);    //延迟
		InvalidateRect(m_gameRect, FALSE);    //局部矩形更新
	}
}


void CGameDlg::OnClickedButtonReset()
{
	// 没有进行游戏，则返回
	if (bePlaying == false || bePause == true)
		return;
	gameControl->reset();
	// 更新界面显示
	updateMap();
	// 通知界面重绘
	InvalidateRect(m_gameRect, FALSE);    //局部矩形更新
}


// 鼠标的消息——获取选取的图片信息，并保证别的选不到
void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y) // 鼠标位置和图顶点位置比较
		return CDialogEx::OnLButtonUp(nFlags, point);
	
	int col = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	int row = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	if (row >= MAX_ROW || col >= MAX_COL)
		return CDialogEx::OnLButtonUp(nFlags, point);
	// 空就不标记
	if (gameControl->getElement(row, col) == BLANK)
		return;
	if (isFirstSelect)
	{
		// x是横轴，y是纵轴
		drawTipFrame(row, col);
		gameControl->setFirstPoint(row, col);
	}
	else
	{
		drawTipFrame(row, col);
		gameControl->setSecondPoint(row, col);
		// 记录路径
		Vertex path[MAX_VERTEX_NUM];
		int num;
		// 判断是否是相同图片
		if (gameControl->link(path, num))
		{
			// 提示线
			drawTipLine(path, num);
			// 更新地图
			updateMap();
		}
		Sleep(200); // 视觉延迟
		InvalidateRect(m_gameRect, FALSE); // 局部更新
		// 判断游戏胜利
		judgeWin();
		/*if (gameControl.isWin())
		{
			MessageBox(_T("获胜!"));
			this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
			return;
		}*/
		// 刷新得分
		if (gameMode == RELAX)
		{
			CString str;
			str.Format(_T("%d"), gameControl->getScore());
			SetDlgItemText(IDC_EDIT_SCORE, str);

			UpdateData(false);
		}
	}
	isFirstSelect = !isFirstSelect;
}

// 绘制边界提示框
void CGameDlg::drawTipFrame(int row, int col)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + col * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + row * m_sizeElem.cy;	
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}

// 胜负判断函数
void CGameDlg::judgeWin()
{
	//游戏胜负判断
	int gameStatus = gameControl->isWin(gameProgress.GetPos()); // int 不能bool！！！
	//判断是否继续游戏
	if (gameStatus == GAME_PLAY)
		return;
	else
	{
		// 将游戏标识改为false
		bePlaying = false;
		// 关闭定时器
		KillTimer(PLAY_TIMER_ID);
		// 窗口提示获胜
		CString strTitle;
		this->GetWindowTextW(strTitle);
		if (gameStatus == GAME_SUCCESS)
		{
			MessageBox(_T("获胜！"), strTitle);
			if (gameMode == LEVEL) // 过关
			{
				gameControl->levelUp();
				CString str;
				str.Format(_T("第%d关"), gameControl->getLevel());
				SetDlgItemText(IDC_STATIC_LEVEL, str);
				UpdateData(false);
			}
		}
		else if (gameStatus == GAME_LOSE)
		{
			MessageBox(_T("很遗憾！"), strTitle);
		}
		// 还原开始游戏按钮，使用按钮可以点击
		this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(0);
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(0);
		GetDlgItem(IDC_BUTTON_HINT)->EnableWindow(0);
	}
}


// 绘制消子连线
void CGameDlg::drawTipLine(Vertex path[], int vexNum)
{
	// 获取dc
	CClientDC dc(this);
	// 设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	// 将画笔选入dc
	CPen* pOldPen = dc.SelectObject(&penLine);
	// 循环，逐个连接线
	for (int i = 0; i < vexNum - 1; i++)
	{
		dc.MoveTo(m_ptGameTop.x + path[i].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + path[i].row * m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.LineTo(m_ptGameTop.x + path[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + path[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	dc.SelectObject(pOldPen);
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// 每一秒都需要判断胜利与否
	judgeWin();
	if (nIDEvent == PLAY_TIMER_ID && bePlaying && bePause == false)
	{
		//游戏时间减一秒
		if (timeCount > -1)
		{
			// 更新时间文本框，CDC太繁琐
			CString str;
			str.Format(_T("%d"), timeCount);
			SetDlgItemText(IDC_EDIT_TIME, str);

			UpdateData(false);
			timeCount--;

			gameProgress.StepIt();
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg::OnClickedButtonPause()
{
	CClientDC dc(this);
	//游戏没在进行时，直接返回
	if (bePlaying == false)
		return;
	//如果游戏没有暂停
	if (bePause == false)
	{
		//hu绘制背景到内存DC中
		m_dcMem.BitBlt(MAP_LEFT, MAP_TOP, 640, 400, &m_dcCover, 0, 0, SRCCOPY);
		GetDlgItem(IDC_BUTTON_HINT)->EnableWindow(0);
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(0);
		InvalidateRect(m_gameRect, FALSE);    //局部矩形更新
		this->GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowTextW(_T("继续游戏"));
	}
	//如果游戏暂停
	else if (bePause == true)
	{
		updateMap();
		GetDlgItem(IDC_BUTTON_HINT)->EnableWindow(1); // 直接禁用更好
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(1);
		InvalidateRect(m_gameRect, FALSE);    //局部矩形更新
		this->GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowTextW(_T("暂停游戏"));
	}
	bePause = !bePause;
}


void CGameDlg::OnClickedButtonHelp2()
{
	CHelpDlg dlg;
	dlg.DoModal();
}


void CGameDlg::OnClickedButtonGadget()
{
	gameControl->useGadget();
}
