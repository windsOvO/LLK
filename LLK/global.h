#pragma once


#define BLANK -1 // ��λ�ÿհ�/������


// ���嶥��ṹ��
typedef struct tagVertex
{
	int row; // ��
	int col; // ��
	int info; // ��Ϣ��
	tagVertex()
	{
		row = col = -1;
		info = -1;
	}
}Vertex;

// ������Ϣ�ṹ��
typedef struct tagScore
{
	int nMode; // ��Ϸģʽ��1����ģʽ2�ؿ�ģʽ
	int nGrade; // ���ַ���
	int nLevel; // ���ֵȼ�
	CString strName; // �������
}SCORE;

// �����ṹ��
typedef struct tagRankArray
{
	CString playerName;//����
	int nGrade;//�÷�
}RankArray;

// ��������Ҫ�����ϵ
#define MAX_VERTEX_NUM 80 // ��������
#define MAX_ROW	8	  // ��ʼ����     // ����߽磡��
#define MAX_COL	10	  // ��ʼ����
#define MAX_PIC_NUM 10  // ͼƬ��ɫ��
#define REPEAT_NUM 8  // ÿ�ֻ�ɫͼƬ����
#define MAP_TOP 50	 // ��ͼ���Ͻ�������
#define MAP_LEFT 50	  // ��ͼ���ϽǺ�����
#define PIC_WIDTH 40	 // ͼƬ���
#define PIC_HEIGHT 40	 // ͼƬ����

#define GAME_LOSE -1   // ʧ��
#define GAME_SUCCESS 0 // ��ʤ
#define GAME_PLAY 1    // ��Ϸ���ڽ���

#define PLAY_TIMER_ID 1 // ��ʱ�����

// ģʽ
#define BASIC 1
#define RELAX 2
#define LEVEL 3

#define MAX_RANK_LEVEL 10 // �����������
#define MAX_RANK_MES 1000 // �����Ϣ����

// �ļ�·��
#define RANK_FILE_PATH _T("file\\score.txt") // ������Ϣ