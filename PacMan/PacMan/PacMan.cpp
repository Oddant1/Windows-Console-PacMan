// PacMan.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Player.h"
#include "PacMan.h"

#define SCORE_START 7

using namespace std;

// Screen buffer/console
#include <Windows.h>

// Get the console
HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

void UpdateScore(wchar_t *screen, int nScore);
// Function to disable cursor
void showConsoleCursor(bool showFlag);

int main()
{
	showConsoleCursor(false);     // Disable cursor

	// Create screen buffer
	wchar_t *screen = new wchar_t[nMapWidth * nMapHeight];
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	// Initialize map
	string map;
	
	// Initialize the score
	int nScore = 0;

	// Initialize map
	map += "Score: 0                     ";
	map += "#############################";
	map += "#............###............#";
	map += "#.##########.###.#####.####.#";
	map += "#O##########.###.#####.####O#";
	map += "#.##########.###.#####.####.#";
	map += "#...........................#";
	map += "#.####.#.###########.#.####.#";
	map += "#.####.#.###########.#.####.#";
	map += "#......#.###########.#......#";
	map += "######.#....#####....#.######";
	map += "######.#### ##### ####.######";
	map += "######.#             #.######";
	map += "######.# ####   #### #.######";
	map += "######.# #         # #.######";
	map += "      .  #         # #.      ";
	map += "######.# #         # #.######";
	map += "######.# #         # #.######";
	map += "######.# ########### #.######";
	map += "######.#             #.######";
	map += "######.# ########### #.######";
	map += "#.............#.............#";
	map += "#.####.######.#.######.####.#";
	map += "#.####.######.#.######.####.#";
	map += "#O..##........ ........##..O#";
	map += "###.##.##.#########.##.##.###";
	map += "###.##.##.#########.##.##.###";
	map += "#......##.#########.##......#";
	map += "#.#######....###....#######.#";
	map += "#.##########.###.##########.#";
	map += "#.##########.###.##########.#";
	map += "#...........................#";
	map += "#############################";
	map += "                             ";

	for (int i = 0; i < nMapWidth * nMapHeight; i++)
		screen[i] = map[i];
	
	// Initialize player
	InitializePlayer(screen);
	InitializeGhosts(screen);
	WriteConsoleOutputCharacter(hConsole, screen, nMapWidth * nMapHeight, { 0,0 }, &dwBytesWritten);

	// Continue loop while game is not over
	while (!bGameOver)
	{
		Sleep(150);
		nScore = MovePlayer(screen, nScore);
		UpdateScore(screen, nScore);
		WriteConsoleOutputCharacter(hConsole, screen, nMapWidth * nMapHeight, { 0,0 }, &dwBytesWritten);
	}
	
	// Delete the allocated memory
	delete screen;

    return 0;
}

// Update score on screem
void UpdateScore(wchar_t *screen, int nScore)
{
	// Convert sore to string 
	string sScore = to_string(nScore);
	int nLength = sScore.length();
	
	// Add the score to the screen
	for (int i = SCORE_START; i < SCORE_START + nLength; i++)
		screen[i] = sScore[i - SCORE_START];
}

// Disable the console cursor
void showConsoleCursor(bool showFlag)
{
	CONSOLE_CURSOR_INFO cursorInfo;

	// Get cursor
	GetConsoleCursorInfo(hConsole, &cursorInfo);

	// set the cursor visibility
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}