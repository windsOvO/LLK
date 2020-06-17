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

// 判断最新的点是否形成拐点
bool CGameLogic::isCorner()
{
	if (vexNum >= 3)
	{
		// 等差数列判断
		if ((path[vexNum - 1] + path[vexNum - 3]) / 2 != path[vexNum - 2])
		{
			return true;
		}
	}
	return false;
}

// 搜到的点压栈
void CGameLogic::pushVertex(int v)
{
	path[vexNum] = v;
	vexNum++;
	// 判断是否形成新的拐点
	if (isCorner())
	{
		cornerNum++;
	}
}

// 点出栈
void CGameLogic::popVertex()
{
	// 判断是否形成拐点，减少拐点数
	if (isCorner())
	{
		cornerNum--;
	}
	vexNum--;
}

// 深度优先搜索，判断v1 v2是否连通
bool CGameLogic::searchPath(CGraph& map, int v1, int v2)
{
	int num = map.getVexNum();
	//遍历图中第0行，从第0列到num列，所连边值为true的点
	for (int vi = 0; vi < num; vi++)
	{
		if (map.getEdge(v1, vi) && !isExist(vi))
		{
			// 压入顶点，假设为路径的一个有效顶点
			pushVertex(vi);
			// 当拐点数大于2时，放弃该点
			if (cornerNum > 2)
			{
				popVertex(); //取出压入的顶点
				continue;
			}
			// 没到终点，继续搜索
			if (vi != v2)
			{
				// 不为空时表示该条路径不通
				if (map.getVertex(vi) != BLANK)
				{
					popVertex();
					continue;
				}
				// 为空时，继续判断（vi，v2）是否连通
				if (searchPath(map, vi, v2))
				{
					// 如果 == true,表示已经找到一条连通路径，则返回true
					// 直接尾部回溯
					return true;
				}
			}
			else // vi == v2找到
			{
				return true;
			}
			// 回溯
			popVertex();
		}
	}
	return false;
}

// 获取路径-参数获取结果，返回值为个数
int CGameLogic::getVexPath(Vertex path[])
{
	Vertex v;
	for (int i = 0; i < vexNum; i++)
	{
		for (v.col = 0; v.col < MAX_COL; v.col++)
		{
			for (v.row = 0; v.row < MAX_ROW; v.row++)
			{
				if (v.row * MAX_COL + v.col == this->path[i]) //编号存在
				{
					path[i] = v;
				}
			}
		}
	}
	return vexNum;
}

// 初始化地图函数
void CGameLogic::initMap(CGraph& map)
{
	// 固定初始化
	// int tmp[4][4] = { 2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3 };
	//随机生成地图
	int tmp[MAX_VERTEX_NUM];
	memset(tmp, 0, sizeof(tmp)); // 初始化
	//多少花色
	for (int i = 0; i < MAX_PIC_NUM; i++)
	{
		//重复数
		for (int j = 0; j < REPEAT_NUM; j++)
		{
			tmp[i * REPEAT_NUM + j] = i;
		}
	}
	//设置种子
	srand((int)time(NULL));
	// 随机交换，打乱
	for (int i = 0; i < 200; i++)
	{
		//随机得到两个坐标
		int index1 = rand() % MAX_VERTEX_NUM;
		int index2 = rand() % MAX_VERTEX_NUM;
		//交换两个数值
		int swapTmp = tmp[index1];
		tmp[index1] = tmp[index2];
		tmp[index2] = swapTmp;
	}
	// 图初始化
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		map.addVertex(tmp[i]);
	}
	// 外面一圈边界
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

// 重排，对已有点打乱
void CGameLogic::resetMap(CGraph& map)
{
	// 随机交换顶点数组中两个顶点的值
	for (int i = 0; i < 200; i++)
	{
		// 随机得到两个坐标
		int index1 = rand() % MAX_VERTEX_NUM;
		int index2 = rand() % MAX_VERTEX_NUM;
		// 交换坐标
		map.swapVertex(index1, index2);
	}
	// 更新弧信息
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			updateEdge(map, i, j);
		}
	}
}

// 根据已有的点信息更新边
void CGameLogic::updateEdge(CGraph& map, int row, int col)
{
	int index1 = row * MAX_COL + col; // 行*MAX_COL+列 bug！！！！
	int index2;
	int info1 = map.getVertex(index1);
	int info2;
	if (col > 0) // 左边
	{
		index2 = index1 - 1;
		info2 = map.getVertex(index2);
		if (info1 == info2 || info1 == BLANK || info2 == BLANK)
			map.addEdge(index1, index2);
	}
	if (col < MAX_COL - 1) // 右边
	{
		index2 = index1 + 1;
		info2 = map.getVertex(index2);
		if (info1 == info2 || info1 == BLANK || info2 == BLANK)
			map.addEdge(index1, index2);
	}
	if (row < MAX_ROW - 1) // 下边
	{
		index2 = index1 + MAX_COL;
		info2 = map.getVertex(index2);
		if (info1 == info2 || info1 == BLANK || info2 == BLANK)
			map.addEdge(index1, index2);
	}
	if (row > 0) // 上边
	{
		index2 = index1 - MAX_COL;
		info2 = map.getVertex(index2);
		if (info1 == info2 || info1 == BLANK || info2 == BLANK)
			map.addEdge(index1, index2);
	}
}

// 连接判断函数
bool CGameLogic::isLink(CGraph& map, Vertex v1, Vertex v2)
{
	int index1 = v1.row * MAX_COL + v1.col;
	int index2 = v2.row * MAX_COL + v2.col;

	pushVertex(index1);
	// 搜索连通路径
	if (searchPath(map, index1, index2))
	{
		return true;
	}
	// 判断外圈可连接 —— 改地图
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

// 消子函数
void CGameLogic::clear(CGraph& map, Vertex v1, Vertex v2)
{
	// map[v1.row][v1.col] = BLANK; 迭代删除
	// map[v2.row][v2.col] = BLANK;

	int index1 = v1.row * MAX_COL + v1.col;
	int index2 = v2.row * MAX_COL + v2.col;
	// 更新顶点
	map.updateVertex(index1, BLANK);
	map.updateVertex(index2, BLANK);
	// 更新边
	updateEdge(map, v1.row, v1.col);
	updateEdge(map, v2.row, v2.col);
	
}

// 判断是否全为空
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

// 提示——搜索存在路径
bool CGameLogic::searchValidPath(CGraph& map)
{
	int num = map.getVexNum();
	for (int i = 0; i < num; i++)
	{
		// 得到第一个非空顶点
		if (map.getVertex(i) == BLANK)
		{
			continue;
		}
		// 遍历得到第二个同色顶点
		for (int j = 0; j < num; j++)
		{
			if (i != j)
			{
				//如果第i个点和第j个点同色
				if (map.getVertex(i) == map.getVertex(j))
				{
					//压入第一个点
					pushVertex(i);
					if (searchPath(map, i, j) == true)
					{
						return true;
					}
					//取出压入的顶点
					popVertex();
				}
			}
		}
	}
	return false;
}

/* 迭代删除代码

// 连接判断函数
bool CGameLogic::isLink(CGraph& map, Vertex v1, Vertex v2)
{
	// 开始连接前
	vertexNum = 0;
	// 一条直线连通
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
	// 两条直线连通
	if (linkOnCorner(map, v1, v2))
	{
		addVertex(v2);
		return true;
	}
	// 三条直线连通
	if (linkOnTwoCorner(map, v1, v2))
	{
		addVertex(v2);
		return true;
	}
	return false;
}

// 判断一行上是否都是空-需要1<2
// 如果单纯逻辑会出现2*2拐角部分无法检测的bug，所以该函数需要检测全部是否为空
bool CGameLogic::lineX(int map[][4], int row, int col1, int col2)
{
	for (int i = col1; i <= col2; i++)
	{
		if (map[row][i] != BLANK)
			return false;
	}
	return true;
}
// 判断一列上是否都是空--需要1<2
bool CGameLogic::lineY(int map[][4], int col, int row1, int row2)
{
	for (int i = row1; i <= row2; i++)
	{
		if (map[i][col] != BLANK)
			return false;
	}
	return true;
}

// 同一行连通判断
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

// 同一列连通判断
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

// 一个拐角判断
bool CGameLogic::linkOnCorner(int map[][4], Vertex v1, Vertex v2)
{
	int row1, row2, col1, col2;
	// 使1在左边，2在右边
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
	// 1在2的左上方
	if (col1 < col2)
	{
		// 上拐角
		if (lineX(map, row1, col1 + 1, col2) && lineY(map, col2, row2 + 1, row1))
		{
			tmp.col = col2;
			tmp.row = row1;
			addVertex(tmp);
			return true;
		}
		// 下拐角
		if (lineY(map, col1, row1 + 1, row2) && lineX(map, row2, col1, col2 - 1))
		{
			tmp.col = col1;
			tmp.row = row2;
			addVertex(tmp);
			return true;
		}
	}
	// 1在2的左下方
	else
	{
		// 上拐角
		if (lineY(map, col1, row2, row1 + 1) && lineX(map, row2, col1, col2  - 1))
		{
			tmp.col = col1;
			tmp.row = row2;
			addVertex(tmp);
			return true;
		}
		// 下拐角
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

// 两个拐角判断
bool CGameLogic::linkOnTwoCorner(int map[][4], Vertex v1, Vertex v2)
{
	return false;
}

// 添加路径
void CGameLogic::addVertex(Vertex v)
{
	path[vertexNum] = v;
	vertexNum++;
}
// 删除路径
void CGameLogic::deleteVertex()
{
	vertexNum--;
}
*/