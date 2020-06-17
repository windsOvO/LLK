#include "pch.h"
#include "CGameLevel.h"

CGameLevel::CGameLevel()
{
	level = 1;
}

CGameLevel::~CGameLevel()
{

}

void CGameLevel::startGame()
{
	CGameLogic gameLogic;
	gameLogic.initMap(gameMap);
}

int CGameLevel::isWin(int time)
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

bool CGameLevel::help(Vertex path[], int& vexNum)
{
	CGameLogic logic;
	//����һ����Ч����ʾ·��
	if (logic.searchValidPath(gameMap))
	{
		//����·������
		vexNum = logic.getVexPath(path);
		return true;
	}
	return false;
}

void CGameLevel::reset()
{
	CGameLogic logic;
	logic.resetMap(gameMap);
}

bool CGameLevel::link(Vertex path[], int& vexNum)
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
	// �Ƿ��������
	CGameLogic gameLogic;
	if (gameLogic.isLink(gameMap, firstPoint, secondPoint))
	{
		// ����
		gameLogic.clear(gameMap, firstPoint, secondPoint);
		// ����·������
		vexNum = gameLogic.getVexPath(path);
		return true;
	}
	return false;
}

int CGameLevel::getLevel()
{
	return level;
}

void CGameLevel::levelUp()
{
	level++;
}