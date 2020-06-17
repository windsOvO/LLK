#include "pch.h"

#include "CGraph.h"
#include "CGameLogic.h"
#include "global.h"

#include <queue>
#include <stack>
using namespace std;

CGameLogic::CGameLogic()
{
	vexNum = 0;
	cornerNum = 0;
}

CGameLogic::~CGameLogic()
{

}

bool CGameLogic::isExist(int v)
{
	for (int i = 0; i < vexNum; i++)
	{
		if (path[i] == v)
			return true;
	}
	return false;
}

// �ж����µĵ��Ƿ��γɹյ�
bool CGameLogic::isCorner()
{
	if (vexNum >= 3)
	{
		// �Ȳ������ж�
		if ((path[vexNum - 1] + path[vexNum - 3]) / 2 != path[vexNum - 2])
		{
			return true;
		}
	}
	return false;
}

// �ѵ��ĵ�ѹջ
void CGameLogic::pushVertex(int v)
{
	path[vexNum] = v;
	vexNum++;
	// �ж��Ƿ��γ��µĹյ�
	if (isCorner())
	{
		cornerNum++;
	}
}

// ���ջ
void CGameLogic::popVertex()
{
	// �ж��Ƿ��γɹյ㣬���ٹյ���
	if (isCorner())
	{
		cornerNum--;
	}
	vexNum--;
}

// ��������������ж�v1 v2�Ƿ���ͨ
bool CGameLogic::searchPath(CGraph& map, int v1, int v2)
{
	int num = map.getVexNum();
	//����ͼ�е�0�У��ӵ�0�е�num�У�������ֵΪtrue�ĵ�
	for (int vi = 0; vi < num; vi++)
	{
		if (map.getEdge(v1, vi) && !isExist(vi))
		{
			// ѹ�붥�㣬����Ϊ·����һ����Ч����
			pushVertex(vi);
			// ���յ�������2ʱ�������õ�
			if (cornerNum > 2)
			{
				popVertex(); //ȡ��ѹ��Ķ���
				continue;
			}
			// û���յ㣬��������
			if (vi != v2)
			{
				// ��Ϊ��ʱ��ʾ����·����ͨ
				if (map.getVertex(vi) != BLANK)
				{
					popVertex();
					continue;
				}
				// Ϊ��ʱ�������жϣ�vi��v2���Ƿ���ͨ
				if (searchPath(map, vi, v2))
				{
					// ��� == true,��ʾ�Ѿ��ҵ�һ����ͨ·�����򷵻�true
					// ֱ��β������
					return true;
				}
			}
			else // vi == v2�ҵ�
			{
				return true;
			}
			// ����
			popVertex();
		}
	}
	return false;
}

// ��ȡ·��-������ȡ���������ֵΪ����
int CGameLogic::getVexPath(Vertex path[])
{
	Vertex v;
	for (int i = 0; i < vexNum; i++)
	{
		for (v.col = 0; v.col < MAX_COL; v.col++)
		{
			for (v.row = 0; v.row < MAX_ROW; v.row++)
			{
				if (v.row * MAX_COL + v.col == this->path[i]) //��Ŵ���
				{
					path[i] = v;
				}
			}
		}
	}
	return vexNum;
}

// ��ʼ����ͼ����
void CGameLogic::initMap(CGraph& map)
{
	// �̶���ʼ��
	// int tmp[4][4] = { 2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3 };
	//������ɵ�ͼ
	int tmp[MAX_VERTEX_NUM];
	memset(tmp, 0, sizeof(tmp)); // ��ʼ��
	//���ٻ�ɫ
	for (int i = 0; i < MAX_PIC_NUM; i++)
	{
		//�ظ���
		for (int j = 0; j < REPEAT_NUM; j++)
		{
			tmp[i * REPEAT_NUM + j] = i;
		}
	}
	//��������
	srand((int)time(NULL));
	// �������������
	for (int i = 0; i < 200; i++)
	{
		//����õ���������
		int index1 = rand() % MAX_VERTEX_NUM;
		int index2 = rand() % MAX_VERTEX_NUM;
		//����������ֵ
		int swapTmp = tmp[index1];
		tmp[index1] = tmp[index2];
		tmp[index2] = swapTmp;
	}
	// ͼ��ʼ��
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		map.addVertex(tmp[i]);
	}
	// ����һȦ�߽�
	/*
	*/
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			updateEdge(map, i, j);
		}
	}
}

// ���ţ������е����
void CGameLogic::resetMap(CGraph& map)
{
	// ��������������������������ֵ
	for (int i = 0; i < 200; i++)
	{
		// ����õ���������
		int index1 = rand() % MAX_VERTEX_NUM;
		int index2 = rand() % MAX_VERTEX_NUM;
		// ��������
		map.swapVertex(index1, index2);
	}
	// ���»���Ϣ
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			updateEdge(map, i, j);
		}
	}
}

// �������еĵ���Ϣ���±�
void CGameLogic::updateEdge(CGraph& map, int row, int col)
{
	int index1 = row * MAX_COL + col; // ��*MAX_COL+�� bug��������
	int index2;
	int info1 = map.getVertex(index1);
	int info2;
	if (col > 0) // ���
	{
		index2 = index1 - 1;
		info2 = map.getVertex(index2);
		if (info1 == info2 || info1 == BLANK || info2 == BLANK)
			map.addEdge(index1, index2);
	}
	if (col < MAX_COL - 1) // �ұ�
	{
		index2 = index1 + 1;
		info2 = map.getVertex(index2);
		if (info1 == info2 || info1 == BLANK || info2 == BLANK)
			map.addEdge(index1, index2);
	}
	if (row < MAX_ROW - 1) // �±�
	{
		index2 = index1 + MAX_COL;
		info2 = map.getVertex(index2);
		if (info1 == info2 || info1 == BLANK || info2 == BLANK)
			map.addEdge(index1, index2);
	}
	if (row > 0) // �ϱ�
	{
		index2 = index1 - MAX_COL;
		info2 = map.getVertex(index2);
		if (info1 == info2 || info1 == BLANK || info2 == BLANK)
			map.addEdge(index1, index2);
	}
}

// �����жϺ���
bool CGameLogic::isLink(CGraph& map, Vertex v1, Vertex v2)
{
	int index1 = v1.row * MAX_COL + v1.col;
	int index2 = v2.row * MAX_COL + v2.col;

	pushVertex(index1);
	// ������ͨ·��
	if (searchPath(map, index1, index2))
	{
		return true;
	}
	// �ж���Ȧ������ ���� �ĵ�ͼ
	/*	if (v1.row == v2.row) {
		if (v1.row == 0 || v1.row == MAX_ROW - 1) {
			return true;
		}
	}
	if (v1.col == v2.col) {
		if (v1.col == 0 || v1.col == MAX_COL - 1) {
			return true;
		}
	}*/
	popVertex();
	return false;
}

// ���Ӻ���
void CGameLogic::clear(CGraph& map, Vertex v1, Vertex v2)
{
	// map[v1.row][v1.col] = BLANK; ����ɾ��
	// map[v2.row][v2.col] = BLANK;

	int index1 = v1.row * MAX_COL + v1.col;
	int index2 = v2.row * MAX_COL + v2.col;
	// ���¶���
	map.updateVertex(index1, BLANK);
	map.updateVertex(index2, BLANK);
	// ���±�
	updateEdge(map, v1.row, v1.col);
	updateEdge(map, v2.row, v2.col);
	
}

// �ж��Ƿ�ȫΪ��
bool CGameLogic::isBlank(CGraph& map)
{
	int num = map.getVexNum();
	for (int i = 0; i < num; i++)
	{
		if (map.getVertex(i) != BLANK)
		{
			return false;
		}
	}
	return true;
}

// ��ʾ������������·��
bool CGameLogic::searchValidPath(CGraph& map)
{
	int num = map.getVexNum();
	for (int i = 0; i < num; i++)
	{
		// �õ���һ���ǿն���
		if (map.getVertex(i) == BLANK)
		{
			continue;
		}
		// �����õ��ڶ���ͬɫ����
		for (int j = 0; j < num; j++)
		{
			if (i != j)
			{
				//�����i����͵�j����ͬɫ
				if (map.getVertex(i) == map.getVertex(j))
				{
					//ѹ���һ����
					pushVertex(i);
					if (searchPath(map, i, j) == true)
					{
						return true;
					}
					//ȡ��ѹ��Ķ���
					popVertex();
				}
			}
		}
	}
	return false;
}

/* ����ɾ������

// �����жϺ���
bool CGameLogic::isLink(CGraph& map, Vertex v1, Vertex v2)
{
	// ��ʼ����ǰ
	vertexNum = 0;
	// һ��ֱ����ͨ
	addVertex(v1);
	if (v1.row == v2.row)
	{
		if (linkInRow(map, v1, v2))
		{
			addVertex(v2);
			return true;
		}
	}
	if (v1.col == v2.col)
	{
		if (linkInCol(map, v1, v2))
		{
			addVertex(v2);
			return true;
		}
	}
	// ����ֱ����ͨ
	if (linkOnCorner(map, v1, v2))
	{
		addVertex(v2);
		return true;
	}
	// ����ֱ����ͨ
	if (linkOnTwoCorner(map, v1, v2))
	{
		addVertex(v2);
		return true;
	}
	return false;
}

// �ж�һ�����Ƿ��ǿ�-��Ҫ1<2
// ��������߼������2*2�սǲ����޷�����bug�����Ըú�����Ҫ���ȫ���Ƿ�Ϊ��
bool CGameLogic::lineX(int map[][4], int row, int col1, int col2)
{
	for (int i = col1; i <= col2; i++)
	{
		if (map[row][i] != BLANK)
			return false;
	}
	return true;
}
// �ж�һ�����Ƿ��ǿ�--��Ҫ1<2
bool CGameLogic::lineY(int map[][4], int col, int row1, int row2)
{
	for (int i = row1; i <= row2; i++)
	{
		if (map[i][col] != BLANK)
			return false;
	}
	return true;
}

// ͬһ����ͨ�ж�
bool CGameLogic::linkInRow(int map[][4], Vertex v1, Vertex v2)
{
	int row = v1.row;
	int col1 = v1.col;
	int col2 = v2.col;
	if (col1 > col2)
	{
		int tmp = col1;
		col1 = col2;
		col2 = tmp;
	}
	return lineX(map, row, col1 + 1, col2 - 1);
}

// ͬһ����ͨ�ж�
bool CGameLogic::linkInCol(int map[][4], Vertex v1, Vertex v2)
{
	int row1 = v1.row;
	int row2 = v2.row;
	int col = v1.col;
	if (row1 > row2)
	{
		int tmp = row1;
		row1 = row2;
		row2 = tmp;
	}
	return lineY(map, col, row1 + 1, row2 - 1);
}

// һ���ս��ж�
bool CGameLogic::linkOnCorner(int map[][4], Vertex v1, Vertex v2)
{
	int row1, row2, col1, col2;
	// ʹ1����ߣ�2���ұ�
	if (v1.col < v2.col)
	{
		row1 = v1.row;
		row2 = v2.row;
		col1 = v1.col;
		col2 = v2.col;
	}
	else
	{
		row2 = v1.row;
		row1 = v2.row;
		col2 = v1.col;
		col1 = v2.col;
	}
	Vertex tmp;
	// 1��2�����Ϸ�
	if (col1 < col2)
	{
		// �Ϲս�
		if (lineX(map, row1, col1 + 1, col2) && lineY(map, col2, row2 + 1, row1))
		{
			tmp.col = col2;
			tmp.row = row1;
			addVertex(tmp);
			return true;
		}
		// �¹ս�
		if (lineY(map, col1, row1 + 1, row2) && lineX(map, row2, col1, col2 - 1))
		{
			tmp.col = col1;
			tmp.row = row2;
			addVertex(tmp);
			return true;
		}
	}
	// 1��2�����·�
	else
	{
		// �Ϲս�
		if (lineY(map, col1, row2, row1 + 1) && lineX(map, row2, col1, col2  - 1))
		{
			tmp.col = col1;
			tmp.row = row2;
			addVertex(tmp);
			return true;
		}
		// �¹ս�
		if (lineX(map, row1, col1 + 1, col2) && lineY(map, col2, row2 + 1, row1))
		{
			tmp.col = col2;
			tmp.row = row1;
			addVertex(tmp);
			return true;
		}
	}
	return false;
}

// �����ս��ж�
bool CGameLogic::linkOnTwoCorner(int map[][4], Vertex v1, Vertex v2)
{
	return false;
}

// ���·��
void CGameLogic::addVertex(Vertex v)
{
	path[vertexNum] = v;
	vertexNum++;
}
// ɾ��·��
void CGameLogic::deleteVertex()
{
	vertexNum--;
}
*/