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
	bool SaveScore(SCORE& score);//储存分数信息
	int SearchRank(RankArray rankArray[MAX_RANK_LEVEL], int nModel);//获取排行榜分数信息
private:
	void swapScore(SCORE& score1, SCORE& score2);//交换SCORE信息
};

