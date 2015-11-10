#include "ProjectHeader.h"

int main(int argc, char* args[])
{
	bool active = true;
	int LeftP = 0, LeftH = 0;
	int RightP = 0, RightH = 0;
	int size = 5;
	double* mass = new double[size];
	for (int i = 0; i < size; i++)
	{
		mass[i] = i * 3;
		cout << mass[i] << ' ';
	}
	cout << endl;
	removeElement(mass, size, 0);
	for (int i = 0; i < size; i++)
	{
		cout << mass[i] << ' ';
	}
	cout << size;

	//while (active)
	//{
	//	if (_kbhit())
	//	{
	//		if (KB_Hit(VK_LEFT)) LeftH++;
	//		if (KB_Hit(VK_RIGHT)) RightH++;
	//		if (KB_Pressed(VK_LEFT)) LeftP++;
	//		if (KB_Pressed(VK_RIGHT)) RightP++;
	//		if (KB_Hit(VK_UP))
	//		{
	//			system("cls");
	//			cout << LeftP << ' ' << RightP << endl;
	//			cout << LeftH << ' ' << RightH << endl;
	//		}
	//	}
	//}
	return 0;
}