#pragma once
#include <iostream>
#include <windows.h>
#include <map>
#include <io.h>
#include <fcntl.h>



using namespace std;



struct Gomoku
{
	const int WIDTH = 19;
	const int HEIGHT = 19;
	const int SIZE = WIDTH * HEIGHT;
	wchar_t Map[19*19];

	int GameState;

	int cursorLZ;
	int cursorX;
	int cursorY;


	bool round;//0=bai 1=hei
	int w_MoveTimes;
	int b_MoveTimes;

	int w_WinTimes;
	int b_WinTimes;


	wchar_t BLACK; wchar_t WHITE;


	                            //0        1   2      3     4       5 
	const wchar_t boardTiles[14] = { L'╋', L'┏', L'┓', L'┗', L'┛'   , L'┳', L'┻', L'┣', L'┫', L'○',    L'●', L'◎', L'☆', L'★' };

	void GameRun();
	void Init();
	void Draw();
	bool Input();
	void Update();
	bool Reset();

};
