#pragma once

#include "global.h"
#include "CGraph.h"

// ��Ϸ�߼���
class CGameLogic
{
protected:
	// ��ͨ·���Ķ�������
	int path[MAX_VERTEX_NUM]; // ·��- ������
	int vexNum; // ·�������а����ĵ�����
	int cornerNum; // �սǵ�����

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
	// ���ܺ���
	void initMap(CGraph& map);
	void resetMap(CGraph& map);
	void updateEdge(CGraph& map, int row, int col);
	bool isLink(CGraph& map, Vertex v1, Vertex v2);
	void clear(CGraph& map, Vertex v1, Vertex v2);
	bool isBlank(CGraph& map);
	bool searchValidPath(CGraph& map);
};

/* ����ɾ������
	// ��������������ж�
	bool lineX(CGraph& map, int row, int col1, int col2);
	bool lineY(CGraph& map, int col, int row1, int row2);
	bool linkInRow(CGraph& map, Vertex v1, Vertex v2);
	bool linkInCol(CGraph& map, Vertex v1, Vertex v2);
	bool linkOnCorner(CGraph& map, Vertex v1, Vertex v2);
	bool linkOnTwoCorner(CGraph& map, Vertex v1, Vertex v2);
	// ·�������������
	void addVertex(Vertex v);
	void deleteVertex();
	int getPath(Vertex path[]);
*/