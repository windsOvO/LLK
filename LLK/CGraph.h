#pragma once

#include "global.h"

// typedef <元素类型关键字><数组类型名>[<常量表达式>]
typedef int Vertices[MAX_VERTEX_NUM];
// bool-有无边
typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

// 数据结构类
class CGraph
{
protected:
	Vertices vertices;
	int vexNum;
	AdjMatrix adjMatrix;
	int edgeNum;
public:
	CGraph();
	~CGraph();
	void initGraph();
	void clearGraph();
	int getVexNum();
	void addVertex(int info);
	int getVertex(int index);
	void indexToCoordinate(int index, int& row, int& col);
	void updateVertex(int index, int info);
	void addEdge(int index1, int index2);
	int getEdge(int index1, int index2);
	void swapVertex(int index1, int index2);
};

// 数据结构应用逻辑
// 每张图是一个顶点
// 若存在可匹配的，都连有一条边
// 开始游戏时，两个顶点右边的条件为元素相同且相邻（除了边界）