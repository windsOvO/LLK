#include "pch.h"
#include "CScoreLogic.h"

#include "global.h"

CScoreLogic::CScoreLogic()
{
}


CScoreLogic::~CScoreLogic()
{
}

bool CScoreLogic::SaveScore(SCORE& score)
{
	if (score.nGrade < 500)
	{
		score.nLevel = 1;
	}
	else if ((score.nGrade >= 500) && (score.nGrade < 1000))
	{
		score.nLevel = 2;
	}
	else if (score.nGrade >= 1000)
	{
		score.nLevel = 3;
	}
	score.strName.Format(_T("2018062215540000"));

	return scoreDao.Save(RANK_FILE_PATH, score);
}

int CScoreLogic::SearchRank(RankArray rankArray[MAX_RANK_MES], int nModel)
{
	//调用文件层处理函数获取信息
//	pCStr pStr = (pCStr)malloc(sizeof(CStr));
	CString mesStr[MAX_RANK_MES];
	//读取文件信息
	int mesNum;
	mesNum = scoreDao.Read(RANK_FILE_PATH, mesStr);
	//解析文件信息
	SCORE* score = new SCORE[mesNum];//信息存储
	for (int i = 0; i < mesNum; i++)
	{
		scoreDao.PraseCString(mesStr[i], score[i]);
	}
	// 进行排序
	for (int i = 0; i < mesNum - 1; i++)
	{
		for (int j = 0; j < mesNum - i; j++)
		{
			if (score[j].nGrade < score[j + 1].nGrade)
			{
				swapScore(score[j], score[j + 1]);
			}
		}
	}
	int modelMesNum = 0;
	// 将排序后的结果保存在RankArray数组中
	for (int i = 0; (i < mesNum) && (i < MAX_RANK_LEVEL); i++)
	{
		if (score[i].nMode == nModel)
		{
			rankArray[i].playerName.Format(L"%s", score[i].strName);
			rankArray[i].nGrade = score[i].nGrade;
			modelMesNum++;
		}
	}
	// 返回积分数量
	return modelMesNum;
}

void CScoreLogic::swapScore(SCORE& score1, SCORE& score2)
{
	int tempGrade;
	int tempModel;
	int tempLevel;
	CString tempName;

	tempGrade = score1.nGrade;
	tempModel = score1.nMode;
	tempLevel = score1.nLevel;
	tempName.Format(L"%s", score1.strName);

	score1.nGrade = score2.nGrade;
	score1.nLevel = score2.nLevel;
	score1.nMode = score2.nMode;
	score1.strName.Format(L"%s", score2.strName);

	score2.nGrade = tempGrade;
	score2.nLevel = tempLevel;
	score2.nMode = tempModel;
	score2.strName.Format(L"%s", tempName);
}