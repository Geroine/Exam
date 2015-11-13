#include "ProjectHeader.h"


int test(GameData &options)
{
	static int counter = 0;
	counter++;
	cout << "test is calling" << endl;
	if (counter > 20) return -1;
	return 0;
}
int test2(GameData &options)
{
	cout << "            test2 is calling" << endl;
	return 0;
}

int main(int argc, char* args[])
{
	bool active = true;
	GameData jack;
	Tasker taskBase;
	processPush(taskBase, test);

	for (int i = 0; i < 10; i++)
	{
		processIterator(jack, taskBase);
	}
	processPush(taskBase, test2);
	for (int i = 0; i < 20; i++)
	{
		processIterator(jack, taskBase);
	}

	return 0;
}