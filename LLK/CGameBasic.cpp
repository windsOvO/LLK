#include "pch.h"
#include "CGameBasic.h"

CGameBasic::CGameBasic()
{

}

CGameBasic::~CGameBasic()
{

}

// 开始游戏
void CGameBasic::startGame()
{
	CGameLogic gameLogic;
	gameLogic.initMap(gameMap);
}

// 提示
bool CGameBasic::help(Vertex path[], int& vexNum)
{
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

// 重拍
void CGameBasic::reset()
{
	CGameLogic logic;
	logic.resetMap(gameMap);
}

// 判断游戏是否胜利 - 迭代删除
/*bool CGameControl::isWin()
{
	CGameLogic logic;
	if (logic.isBlank(gameMap) == true) {
		gameMap.clearGraph(); // 清理图结构
		return true;
	}
	return false;
}*/
int CGameBasic::isWin(int ti)
{
	CGameLogic logic;
	//判断游戏时间
	if (ti <= 0)
	{
		gameMap.clearGraph();
		return GAME_LOSE;
	}
	//判断是否图中所有点为空
	if (logic.isBlank(gameMap) == true)
	{
		gameMap.clearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

// 连接函数，参数1为路径，2为路径上点数量的引用
bool CGameBasic::link(Vertex path[], int& vexNum)
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