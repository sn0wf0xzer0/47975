//This struct will store information about the player's moves so that Cat may move accordingly.
//File: CatStrat.h
//Author: John Palacios

#include <string>
using namespace std;

#ifndef CATSTRAT_H
#define CATSTRAT_H

struct CatStrat
{
	char opener;
	bool numOpYeX;
	bool numYeqEx;
	bool numConst;
	bool numUndef;
	bool blkOpYeX;
	bool blkYeEx;
	bool blkConst;
	bool blkUndef;
	int constBlkd;
	int undefBlkd;
	int posConst;
	int posUndef;
	int humanFstX;
	int humanFstY;
	int fstPlayX;
	int fstPlayY;
	int nextMoveX;
	int nextMoveY;
};

#endif /* CATSTRAT_H */