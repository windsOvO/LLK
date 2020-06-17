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
	//�����ļ��㴦������ȡ��Ϣ
//	pCStr pStr = (pCStr)malloc(sizeof(CStr));
	CString mesStr[MAX_RANK_MES];
	//��ȡ�ļ���Ϣ
	int mesNum;
	mesNum = scoreDao.Read(RANK_FILE_PATH, mesStr);
	//�����ļ���Ϣ
	SCORE* score = new SCORE[mesNum];//��Ϣ�洢
	for (int i = 0; i < mesNum; i++)
	{
		scoreDao.PraseCString(mesStr[i], score[i]);
	}
	// ��������
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
	// �������Ľ��������RankArray������
	for (int i = 0; (i < mesNum) && (i < MAX_RANK_LEVEL); i++)
	{
		if (score[i].nMode == nModel)
		{
			rankArray[i].playerName.Format(L"%s", score[i].strName);
			rankArray[i].nGrade = score[i].nGrade;
			modelMesNum++;
		}
	}
	// ���ػ�������
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