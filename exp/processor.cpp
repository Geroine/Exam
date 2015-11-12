#include <iostream>
#include <vector>
using namespace std;

typedef int(*funp)(void);

void processor(funp item = NULL)
{
	static vector<funp> items;
	static int size = 0;

	if (item)
	{
		items.push_back(item);
		size++;
		return;
	}

	for (int i = 0; i < size; i++)
	{
		if (items[i]() == -1)
		{
			items.erase(items.begin() + i);
			size--;
		}
	}
}

int testfunction2()
{
	static int i = 0;
	i++;
	cout << "test 2" << endl;
	if (i > 20)
	{
		i = 0;
		return -1;
	}
	return 0;
}

int testfunction1()
{
	static int i = 0;
	i++;
	cout << "          test 1" << endl;
	if (i > 10) 
	{
		i = 0;
		return -1;
	}
	return 0;
}
int testfunction3()
{
	static int i = 0;
	i++;
	cout << "                    test 3" << endl;
	if (i > 10) return -1;
	return 0;
}



void main2()
{
	processor(testfunction1);
	processor(testfunction2);
	int i = 0;
	while (i++<50)
	{
		processor();
	}
	processor(testfunction2);
	processor(testfunction3);
	i = 0;
	while (i++<50)
	{
		processor();
	}
}
