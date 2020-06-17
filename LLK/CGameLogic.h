#pragma once

#include "global.h"
#include "CGraph.h"

// 游戏逻辑类
class CGameLogic
{
protected:
	// 连通路径的顶点索引
	int path[MAX_VERTEX_NUM]; // 路径- 顶点编号
	int vexNum; // 路径数组中包含的点数量
	int cornerNum; // 拐角的数量

	bool isExist(int v);
	bool isCorner();
	void pushVertex(int v);
	void popVertex();
	bool searchPath(CGraph& map, int v1, int v2);
public:
	int getVexPath(Vertex path[]);

public:
	CGameLogic();
	~CGameLogic();
	// 功能函数
	void initMap(CGraph& map);
	void resetMap(CGraph& map);
	void updateEdge(CGraph& map, int row, int col);
	bool isLink(CGraph& map, Vertex v1, Vertex v2);
	void clear(CGraph& map, Vertex v1, Vertex v2);
	bool isBlank(CGraph& map);
	bool searchValidPath(CGraph& map);
};

/* 迭代删除函数
	// 各种情况的消子判断
	bool lineX(CGraph& map, int row, int col1, int col2);
	bool lineY(CGraph& map, int col, int row1, int row2);
	bool linkInRow(CGraph& map, Vertex v1, Vertex v2);
	bool linkInCol(CGraph& map, Vertex v1, Vertex v2);
	bool linkOnCorner(CGraph& map, Vertex v1, Vertex v2);
	bool linkOnTwoCorner(CGraph& map, Vertex v1, Vertex v2);
	// 路径顶点操作函数
	void addVertex(Vertex v);
	void deleteVertex();
	int getPath(Vertex path[]);
*/