#include "pch.h"
#include "CGameBasic.h"

CGameBasic::CGameBasic()
{

}

CGameBasic::~CGameBasic()
{

}

// ��ʼ��Ϸ
void CGameBasic::startGame()
{
	CGameLogic gameLogic;
	gameLogic.initMap(gameMap);
}

// ��ʾ
bool CGameBasic::help(Vertex path[], int& vexNum)
{
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

// ����
void CGameBasic::reset()
{
	CGameLogic logic;
	logic.resetMap(gameMap);
}

// �ж���Ϸ�Ƿ�ʤ�� - ����ɾ��
/*bool CGameControl::isWin()
{
	CGameLogic logic;
	if (logic.isBlank(gameMap) == true) {
		gameMap.clearGraph(); // ����ͼ�ṹ
		return true;
	}
	return false;
}*/
int CGameBasic::isWin(int ti)
{
	CGameLogic logic;
	//�ж���Ϸʱ��
	if (ti <= 0)
	{
		gameMap.clearGraph();
		return GAME_LOSE;
	}
	//�ж��Ƿ�ͼ�����е�Ϊ��
	if (logic.isBlank(gameMap) == true)
	{
		gameMap.clearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

// ���Ӻ���������1Ϊ·����2Ϊ·���ϵ�����������
bool CGameBasic::link(Vertex path[], int& vexNum)
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