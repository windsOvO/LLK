#pragma once

#include "CScoreDao.h"
#include "global.h"

class CScoreLogic
{
protected:
	CScoreDao scoreDao;
public:
	CScoreLogic();
	~CScoreLogic();
	bool SaveScore(SCORE& score);//���������Ϣ
	int SearchRank(RankArray rankArray[MAX_RANK_LEVEL], int nModel);//��ȡ���а������Ϣ
private:
	void swapScore(SCORE& score1, SCORE& score2);//����SCORE��Ϣ
};

