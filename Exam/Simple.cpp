#include "Simple.h"

int average(int a, int b)
{
	return (a + b) / 2;
}

void bufclean()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
}