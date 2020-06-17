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
	//判断是否图中所有点为空
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
	//查找一个有效的提示路径
	if (logic.searchValidPath(gameMap))
	{
		//返回路径顶点
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
	// 判断是否选择了同一元素
	if (firstPoint.row == secondPoint.row && firstPoint.col == secondPoint.col)
		return false;
	// 是否同一种图片
	else if (getElement(firstPoint.row, firstPoint.col) != getElement(secondPoint.row, secondPoint.col))
		return false;
	// 都不是空
	else if (getElement(firstPoint.row, firstPoint.col) == BLANK || getElement(secondPoint.row, secondPoint.col) == BLANK)
		return false;
	// 是否可以连接
	CGameLogic gameLogic;
	if (gameLogic.isLink(gameMap, firstPoint, secondPoint))
	{
		// 消子
		gameLogic.clear(gameMap, firstPoint, secondPoint);
		// 返回路径顶点
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