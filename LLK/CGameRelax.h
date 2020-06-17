#pragma once
#include "CGameControl.h"
class CGameRelax :
    public CGameControl
{
protected:
	// 休闲模式得分
	int score;
	// 道具数量 - 只要相通就能消
	int gadget;
	// 当前是否使用道具
	bool isUseGadget;

public:
	// 函数
	CGameRelax();
	~CGameRelax();

	// 功能函数
	void startGame();
	int isWin(int time);
	bool help(Vertex path[], int& vexNum);
	void reset();
	bool link(Vertex path[], int& vexNum);

	// 多的函数
	void award();
	int getScore();
	void useGadget();
};

