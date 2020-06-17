#pragma once

#include "global.h"

// typedef <Ԫ�����͹ؼ���><����������>[<�������ʽ>]
typedef int Vertices[MAX_VERTEX_NUM];
// bool-���ޱ�
typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

// ���ݽṹ��
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

// ���ݽṹӦ���߼�
// ÿ��ͼ��һ������
// �����ڿ�ƥ��ģ�������һ����
// ��ʼ��Ϸʱ�����������ұߵ�����ΪԪ����ͬ�����ڣ����˱߽磩