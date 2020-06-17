#pragma once


#define BLANK -1 // 该位置空白/已消除


// 定义顶点结构体
typedef struct tagVertex
{
	int row; // 行
	int col; // 列
	int info; // 信息类
	tagVertex()
	{
		row = col = -1;
		info = -1;
	}
}Vertex;

// 积分信息结构体
typedef struct tagScore
{
	int nMode; // 游戏模式，1休闲模式2关卡模式
	int nGrade; // 积分分数
	int nLevel; // 积分等级
	CString strName; // 玩家姓名
}SCORE;

// 排名结构体
typedef struct tagRankArray
{
	CString playerName;//姓名
	int nGrade;//得分
}RankArray;

// 变量间需要满足关系
#define MAX_VERTEX_NUM 80 // 最大点数量
#define MAX_ROW	8	  // 初始行数     // 多个边界！！
#define MAX_COL	10	  // 初始列数
#define MAX_PIC_NUM 10  // 图片花色数
#define REPEAT_NUM 8  // 每种花色图片个数
#define MAP_TOP 50	 // 地图左上角纵坐标
#define MAP_LEFT 50	  // 地图左上角横坐标
#define PIC_WIDTH 40	 // 图片宽度
#define PIC_HEIGHT 40	 // 图片长度

#define GAME_LOSE -1   // 失败
#define GAME_SUCCESS 0 // 获胜
#define GAME_PLAY 1    // 游戏正在进行

#define PLAY_TIMER_ID 1 // 计时器编号

// 模式
#define BASIC 1
#define RELAX 2
#define LEVEL 3

#define MAX_RANK_LEVEL 10 // 最大排行数量
#define MAX_RANK_MES 1000 // 最大信息数量

// 文件路径
#define RANK_FILE_PATH _T("file\\score.txt") // 排名信息