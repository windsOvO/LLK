#include "pch.h"
#include "CGameControl.h"

#include "CGameLogic.h"
#include "global.h"


CGameControl::CGameControl()
{

}

CGameControl::~CGameControl()
{

}

int CGameControl::getElement(int row, int col)
{
	return gameMap.getVertex(row * MAX_COL + col);
}

void CGameControl::setFirstPoint(int row, int col)
{
	firstPoint.row = row;
	firstPoint.col = col;
}

void CGameControl::setSecondPoint(int row, int col)
{
	secondPoint.row = row;
	secondPoint.col = col;
}

void CGameControl::award() {}
int CGameControl::getScore() { return 0; }
void CGameControl::useGadget() {}
int CGameControl::getLevel() { return 0; }
void CGameControl::levelUp() {}