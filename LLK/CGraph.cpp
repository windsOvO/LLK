#include "pch.h"
#include "CGraph.h"

#include "global.h"

CGraph::CGraph()
{
	initGraph();
}

CGraph::~CGraph()
{

}

// 初始化图
void CGraph::initGraph()
{
	vexNum = 0;
	edgeNum = 0;
	// 初始化顶点
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		vertices[i] = -1;
	}
	// 初始化边
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			adjMatrix[i][j] = false;
		}
	}
}

// 清空图
void CGraph::clearGraph()
{
	initGraph();
}

// 获取顶点数量
int CGraph::getVexNum()
{
	return vexNum;
}

// 添加顶点
void CGraph::addVertex(int info)
{
	if (this->vexNum >= MAX_VERTEX_NUM)
		return;
	vertices[vexNum] = info;
	vexNum++;
}

// 获取点
int CGraph::getVertex(int index)
{
	return vertices[index];
}

// 更新边
void CGraph::updateVertex(int index, int info)
{
	vertices[index] = info;
}

// 添加边
void CGraph::addEdge(int index1, int index2)
{
	adjMatrix[index1][index2] = true;
	adjMatrix[index2][index1] = true;
}

// 获取边
int CGraph::getEdge(int index1, int index2)
{
	return adjMatrix[index1][index2];
}

// 交换点
void CGraph::swapVertex(int index1, int index2)
{
	int tmp = vertices[index1];
	vertices[index1] = vertices[index2];
	vertices[index2] = tmp;
}

// 序号转坐标
void CGraph::indexToCoordinate(int index, int& row, int& col)
{
	row = index / MAX_COL;
	col = index % MAX_COL;
}