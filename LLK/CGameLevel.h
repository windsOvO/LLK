#pragma once
#include "CGameControl.h"
class CGameLevel :
    public CGameControl
{
protected:
	int level;

public:
	// ����
	CGameLevel();
	~CGameLevel();

	// ���ܺ���
	void startGame();
	int isWin(int time);
	bool help(Vertex path[], int& vexNum);
	void reset();
	bool link(Vertex path[], int& vexNum);
	int getLevel();
	void levelUp();
};

