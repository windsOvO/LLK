#pragma once
#include "CGameControl.h"
class CGameBasic :
    public CGameControl
{
public:
	// ����
	CGameBasic();
	~CGameBasic();

	// ���ܺ���
	void startGame();
	int isWin(int time);
	bool help(Vertex path[], int& vexNum);
	void reset();
	bool link(Vertex path[], int& vexNum);
};

