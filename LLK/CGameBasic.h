#pragma once
#include "CGameControl.h"
class CGameBasic :
    public CGameControl
{
public:
	// 函数
	CGameBasic();
	~CGameBasic();

	// 功能函数
	void startGame();
	int isWin(int time);
	bool help(Vertex path[], int& vexNum);
	void reset();
	bool link(Vertex path[], int& vexNum);
};

