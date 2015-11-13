#pragma once
#include "ProjectHeader.h"

typedef int(*mainFuctionType)(GameData& options);

enum eTaskAnswer
{
	eDeleteSelf = -1,
	eActive = 0,
	ePauseSelf,
	eRepeatSelf
};

struct Tasker
{
	int memSize;
	mainFuctionType* activeFunctions;
};

void processPush(Tasker &tasker, mainFuctionType function);

void processIterator(GameData &options, Tasker &tasker);