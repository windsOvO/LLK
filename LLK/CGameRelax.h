#pragma once
#include "CGameControl.h"
class CGameRelax :
    public CGameControl
{
protected:
	// ����ģʽ�÷�
	int score;
	// �������� - ֻҪ��ͨ������
	int gadget;
	// ��ǰ�Ƿ�ʹ�õ���
	bool isUseGadget;

public:
	// ����
	CGameRelax();
	~CGameRelax();

	// ���ܺ���
	void startGame();
	int isWin(int time);
	bool help(Vertex path[], int& vexNum);
	void reset();
	bool link(Vertex path[], int& vexNum);

	// ��ĺ���
	void award();
	int getScore();
	void useGadget();
};

