#include "ProcessManager.h"

void processPrepair(Tasker &tasker)
{
	tasker.activeFunctions = NULL;
	tasker.memSize = 0;
}

void processPush(Tasker &tasker, mainFuctionType function)
{
	addElement(tasker.activeFunctions, tasker.memSize, function);
}

void processIterator(GameData &options, Tasker &tasker)
{
	for (int i = 0; i < tasker.memSize; i++)
	{
		int result = tasker.activeFunctions[i](options);
		if (result == -1)
		{
			removeElement(tasker.activeFunctions, tasker.memSize, i);
		}
	}
}