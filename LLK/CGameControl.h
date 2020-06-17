#pragma once

#include "global.h"
#include "CGameLogic.h"
#include "CGraph.h"

// ��Ϸ������
class CGameControl
{
protected:

	// CGameLogic gameLogic; ��Ϊ��ʼ������������Ϊȫ�֡���֤ÿ��num�ȶ�Ϊ0

	// ��Ϸ��ͼ
	CGraph gameMap;
	// ÿ��ѡ��ĵ�һ���͵ڶ�����
	Vertex firstPoint;
	Vertex secondPoint;
public:
	// ����
	CGameControl();
	~CGameControl();

	// ���ܺ���
	// ��ʼ��Ϸ
	virtual void startGame() = 0;
	// �ж���Ϸ�Ƿ�ʤ��
	virtual int isWin(int time) = 0;  // int����BOOL��������
	virtual bool help(Vertex path[], int& vexNum) = 0;
	virtual void reset() = 0;
	virtual bool link(Vertex path[], int& vexNum) = 0;

	// ��������
	// ��ȡ��λ�õ�ͼƬ���
	int getElement(int row, int col);
	// ��Ϊ��һ��/�ڶ�����
	void  setFirstPoint(int row, int col);
	void  setSecondPoint(int row, int col);
	// ���Ӻ���������ֵ��ʾ�Ƿ����ӳɹ��������������ӳɹ�ʱ��������Ϣ
	/// ����������ʱ������ָ�����ȣ�����ά���������������һά����ʡ��
	/// ��������Ƚ���������ʶ�����廹��Ҫ����length����
	// bool link(Vertex path[], int& vexNum);

	// ����
	virtual void award();
	virtual int getScore();
	virtual void useGadget();
	virtual int getLevel();
	virtual void levelUp();
};

