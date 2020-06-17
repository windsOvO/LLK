#pragma once
#include "CGameControl.h"
class CGameLevel :
    public CGameControl
{
protected:
	int level;

public:
	// 函数
	CGameLevel();
	~CGameLevel();

	// 功能函数
	void startGame();
	int isWin(int time);
	bool help(Vertex path[], int& vexNum);
	void reset();
	bool link(Vertex path[], int& vexNum);
	int getLevel();
	void levelUp();
};

