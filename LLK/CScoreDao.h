#pragma once

#include "global.h"
#include <afxstr.h>

class CScoreDao
{
public:
	CScoreDao();
	~CScoreDao();
	bool Save(const CString& filePath, SCORE& score);
	int Read(const CString& filePath, CString mesStr[MAX_RANK_MES]);
	void PraseCString(CString cstr, SCORE& score);
};

