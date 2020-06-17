#include "pch.h"
#include "CGameRelax.h"


CGameRelax::CGameRelax()
{
	score = 0;
	isUseGadget = false;
	gadget = 0;
}

CGameRelax::~CGameRelax()
{

}

void CGameRelax::startGame()
{
	CGameLogic gameLogic;
	gameLogic.initMap(gameMap);
}

int CGameRelax::isWin(int time)
{
	CGameLogic logic;
	//�ж��Ƿ�ͼ�����е�Ϊ��
	if (logic.isBlank(gameMap) == true)
	{
		gameMap.clearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

bool CGameRelax::help(Vertex path[], int& vexNum)
{
	// �۳�20���֣����߲���
	if (score >= 20)
		score -= 20;
	else
		return false;
	CGameLogic logic;
	//�ж��Ƿ�Ϊ��
	if (logic.isBlank(gameMap) == true)
	{
		return false;
	}
	//����һ����Ч����ʾ·��
	if (logic.searchValidPath(gameMap))
	{
		//����·������
		vexNum = logic.getVexPath(path);
		return true;
	}
	return false;
}

void CGameRelax::reset()
{
	// �۳�50���֣����߲���
	if (score >= 50)
		score -= 50;
	else
		return;
	CGameLogic logic;
	logic.resetMap(gameMap);
}

// ���Ӻ���������1Ϊ·����2Ϊ·���ϵ�����������
bool CGameRelax::link(Vertex path[], int& vexNum)
{
	// �ж��Ƿ�ѡ����ͬһԪ��
	if (firstPoint.row == secondPoint.row && firstPoint.col == secondPoint.col)
		return false;
	// �Ƿ�ͬһ��ͼƬ
	else if (getElement(firstPoint.row, firstPoint.col) != getElement(secondPoint.row, secondPoint.col))
		return false;
	// �����ǿ�
	else if (getElement(firstPoint.row, firstPoint.col) == BLANK || getElement(secondPoint.row, secondPoint.col) == BLANK)
		return false;
	// ʹ�õ���
	CGameLogic gameLogic;
	if (isUseGadget)
	{
		if (gadget > 0)
		{
			gadget--;
			isUseGadget = false;
			gameLogic.clear(gameMap, firstPoint, secondPoint);
			return true;
		}
	}
	// �Ƿ��������
	if (gameLogic.isLink(gameMap, firstPoint, secondPoint))
	{
		// ����
		gameLogic.clear(gameMap, firstPoint, secondPoint);
		// ����·������
		vexNum = gameLogic.getVexPath(path);
		award(); // �÷�
		return true;
	}
	return false;
}

void CGameRelax::award()
{
	score += 10; // ƥ��һ��+10��
	if (score % 100)
		gadget++; // ÿһ�ٷֶ�һ�ε���
}

int CGameRelax::getScore()
{
	return score;
}

void CGameRelax::useGadget()
{
	isUseGadget = true;
}