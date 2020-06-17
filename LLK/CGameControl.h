#pragma once

#include "global.h"
#include "CGameLogic.h"
#include "CGraph.h"

// 游戏控制类
class CGameControl
{
protected:

	// CGameLogic gameLogic; 因为初始化，不能设置为全局。保证每次num等都为0

	// 游戏地图
	CGraph gameMap;
	// 每次选择的第一个和第二个点
	Vertex firstPoint;
	Vertex secondPoint;
public:
	// 函数
	CGameControl();
	~CGameControl();

	// 功能函数
	// 开始游戏
	virtual void startGame() = 0;
	// 判断游戏是否胜利
	virtual int isWin(int time) = 0;  // int代替BOOL！！！！
	virtual bool help(Vertex path[], int& vexNum) = 0;
	virtual void reset() = 0;
	virtual bool link(Vertex path[], int& vexNum) = 0;

	// 辅助函数
	// 获取该位置的图片编号
	int getElement(int row, int col);
	// 设为第一个/第二个点
	void  setFirstPoint(int row, int col);
	void  setSecondPoint(int row, int col);
	// 连接函数，返回值表示是否连接成功，参数返回连接成功时两个的信息
	/// 数组做参数时，可以指定长度，而二维数组做参数，最后一维不能省略
	/// 但这个长度仅仅用来标识。具体还需要新增length参数
	// bool link(Vertex path[], int& vexNum);

	// 附加
	virtual void award();
	virtual int getScore();
	virtual void useGadget();
	virtual int getLevel();
	virtual void levelUp();
};

