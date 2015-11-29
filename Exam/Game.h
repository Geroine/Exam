#pragma once
#include "ProjectHeader.h"

enum eGameState
{
	eGSActive = 0,
	eGSDeactive
};

struct new_GFSurface;
struct MMenu;

struct GameOptions
{
	bool resize;
	new_GFSurface* mainSurface;
	/*
	�������� ����������� ���� ������� ������ ������������, � ���� ����������� - ��� 2� ������ ������, �� �� ���� **GCSurface
	� ������ ����� ������� ��������� ������������ �� ����� � �� �������. ���� ������������ ������ ����, ����� ���������
	����������� ����� �������� �� ������� � "����������" ���� ������� ����. 
	��� ����, ���� ����� �� ����, ������ ��� ����������.
	*/
	int stackSize;
	new_GFSurface* stackSurface; // ��� ��� ���-�� ������� ����...

};

struct GameMenu
{
	MMenu* currentMenu;
	int width;
	int height;
};

struct GameKeyboardSettings
{
	// ���� ������� https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	int vkUp = VK_UP;
	int vkDown = VK_DOWN;
	int vkLeft = VK_LEFT;
	int vkRight = VK_RIGHT;
	int vkEnter = VK_RETURN;
	int vkSpace = VK_SPACE;
	int vkLAlt = VK_MENU;
	int vkRAlt = VK_RMENU;
};

struct GameData
{
	int state;
	GameOptions options;
	GameMenu menu;
};

void initGameData(GameData &data, int winX, int winY);

void pushGameSuface(GameData &data, new_GFSurface &surface);

void destGameData(GameData &data);

void changeGameMenu(GameData &data, MMenu &menu);

int activeGraphic(GameData &data);