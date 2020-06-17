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

// ��ʼ��ͼ
void CGraph::initGraph()
{
	vexNum = 0;
	edgeNum = 0;
	// ��ʼ������
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		vertices[i] = -1;
	}
	// ��ʼ����
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			adjMatrix[i][j] = false;
		}
	}
}

// ���ͼ
void CGraph::clearGraph()
{
	initGraph();
}

// ��ȡ��������
int CGraph::getVexNum()
{
	return vexNum;
}

// ��Ӷ���
void CGraph::addVertex(int info)
{
	if (this->vexNum >= MAX_VERTEX_NUM)
		return;
	vertices[vexNum] = info;
	vexNum++;
}

// ��ȡ��
int CGraph::getVertex(int index)
{
	return vertices[index];
}

// ���±�
void CGraph::updateVertex(int index, int info)
{
	vertices[index] = info;
}

// ��ӱ�
void CGraph::addEdge(int index1, int index2)
{
	adjMatrix[index1][index2] = true;
	adjMatrix[index2][index1] = true;
}

// ��ȡ��
int CGraph::getEdge(int index1, int index2)
{
	return adjMatrix[index1][index2];
}

// ������
void CGraph::swapVertex(int index1, int index2)
{
	int tmp = vertices[index1];
	vertices[index1] = vertices[index2];
	vertices[index2] = tmp;
}

// ���ת����
void CGraph::indexToCoordinate(int index, int& row, int& col)
{
	row = index / MAX_COL;
	col = index % MAX_COL;
}