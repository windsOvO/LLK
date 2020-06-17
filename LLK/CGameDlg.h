#pragma once

#include "global.h"
#include "CGameControl.h"

// CGameDlg 对话框
class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(int mode, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	// 游戏控制类
	int gameMode;
	CGameControl *gameControl;
	// 是否正在游戏——是否能开始游戏
	bool bePlaying;
	// 是否正在暂停
	bool bePause;
	// 计时模式时间
	int timeCount;

	// 视频内存
	CDC m_dcMem;
	// 游戏背景
	CDC m_dcBg;
	// 掩盖游戏地图
	CDC m_dcCover;
	//游戏矩形大小
	CRect m_gameRect;
	// 元素图标
	CDC m_dcElement;
	CDC m_dcMask; // 掩码

	// 游戏起始点坐标
	CPoint m_ptGameTop;
	CSize m_sizeElem;
	// 选择元素时，是否为第一次选中
	bool isFirstSelect;


protected:

	void updateMap();
	void updateWindow();

	void initElement();
	void initBackground();
	void drawGameTime();

	void judgeWin();

	// 辅助函数
	void drawTipFrame(int row, int col);
	void drawTipLine(Vertex path[], int vexNum);


public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedButtonStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedButtonHint();
	afx_msg void OnClickedButtonReset();
	CProgressCtrl gameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickedButtonPause();
	afx_msg void OnClickedButtonHelp2();
	afx_msg void OnClickedButtonGadget();
};
