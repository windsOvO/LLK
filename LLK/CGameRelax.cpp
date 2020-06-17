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
	//判断是否图中所有点为空
	if (logic.isBlank(gameMap) == true)
	{
		gameMap.clearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

bool CGameRelax::help(Vertex path[], int& vexNum)
{
	// 扣除20积分，或者不行
	if (score >= 20)
		score -= 20;
	else
		return false;
	CGameLogic logic;
	//判断是否为空
	if (logic.isBlank(gameMap) == true)
	{
		return false;
	}
	//查找一个有效的提示路径
	if (logic.searchValidPath(gameMap))
	{
		//返回路径顶点
		vexNum = logic.getVexPath(path);
		return true;
	}
	return false;
}

void CGameRelax::reset()
{
	// 扣除50积分，或者不行
	if (score >= 50)
		score -= 50;
	else
		return;
	CGameLogic logic;
	logic.resetMap(gameMap);
}

// 连接函数，参数1为路径，2为路径上点数量的引用
bool CGameRelax::link(Vertex path[], int& vexNum)
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
	// 使用道具
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
	// 是否可以连接
	if (gameLogic.isLink(gameMap, firstPoint, secondPoint))
	{
		// 消子
		gameLogic.clear(gameMap, firstPoint, secondPoint);
		// 返回路径顶点
		vexNum = gameLogic.getVexPath(path);
		award(); // 得分
		return true;
	}
	return false;
}

void CGameRelax::award()
{
	score += 10; // 匹配一对+10分
	if (score % 100)
		gadget++; // 每一百分多一次道具
}

int CGameRelax::getScore()
{
	return score;
}

void CGameRelax::useGadget()
{
	isUseGadget = true;
}