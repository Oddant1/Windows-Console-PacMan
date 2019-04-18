#include "stdafx.h"
#include "PacMan.h"
#include "Player.h"

#include <conio.h>

// Movement handling
char Input(wchar_t *screen);
bool Collision(char cDir, wchar_t *screen);

// Eating handler
int Eating(wchar_t *screen, int nPlayerXPrev, int nPlayerYPrev, int nScore);

// Character movement variables
char cDir = '\0';
char cPrev = '\0';

void InitializePlayer(wchar_t *screen)
{
	nPlayerXPos = 14; // Initialize player x
	nPlayerYPos = 24; // Initialize player y

	screen[nPlayerXPos + (nPlayerYPos * nMapWidth)] = '@';
}

int MovePlayer(wchar_t *screen, int nScore)
{
	int nPlayerXPrev = nPlayerXPos; // Set previous x to x before movement
	int nPlayerYPrev = nPlayerYPos; // Set previous y to y before movement

	// If there is keyboard input handle it otherwise keep moving
	if (_kbhit())
		cDir = Input(screen);
	else
		cDir = cPrev;

	// Move the player based on input
	switch (cDir)
	{
	case 'w':
		nPlayerYPos--;
		break;
	case 'd':
		nPlayerXPos++;
		break;
	case 's':
		nPlayerYPos++;
		break;
	case 'a':
		nPlayerXPos--;
		break;
	case 'null':
		break;
	}

	// Handle teleporting the player at the map edges
	if (nPlayerXPos < 0 && cDir == 'a')
		nPlayerXPos = nMapWidth - 1;
	if (nPlayerXPos == nMapWidth && cDir == 'd')
		nPlayerXPos = 0;

	// Don't move if there is a collision
	if (screen[nPlayerXPos + (nPlayerYPos * nMapWidth)] == '#')
	{
		nPlayerXPos = nPlayerXPrev;
		nPlayerYPos = nPlayerYPrev;
	}

	// If player moved check if they ate a pellet and make sure there is a space
	if (nPlayerXPos != nPlayerXPrev || nPlayerYPos != nPlayerYPrev)
	{
		nScore = Eating(screen, nPlayerXPrev, nPlayerYPrev, nScore);
		screen[nPlayerXPrev + (nPlayerYPrev * nMapWidth)] = ' ';
	}
	
	// Reprint player
	screen[nPlayerXPos + (nPlayerYPos * nMapWidth)] = '@';

	return nScore;
}

char Input(wchar_t *screen)
{
	cDir = _getch();
    if (cDir == '\0')
        cDir = cPrev;

	// Check for collision
	bool bCollision = Collision(cDir, screen);

	if (bCollision && cDir != cPrev)
		cDir = cPrev;
	else if (bCollision)
		cDir = 'null';

	cPrev = cDir;
	return cDir;
}

bool Collision(char cDir, wchar_t *screen)
{
	// Determine if the player collided with a wall
	switch (cDir)
	{
	case 'w':
		if (screen[nPlayerXPos + ((nPlayerYPos - 1) * nMapWidth)] == '#')
			return true;
		return false;
	case 'd':
		if (screen[(nPlayerXPos + 1) + (nPlayerYPos * nMapWidth)] == '#')
			return true;
		return false;
	case 's':
		if (screen[nPlayerXPos + ((nPlayerYPos + 1) * nMapWidth)] == '#')
			return true;
		return false;
	case 'a':
		if (screen[(nPlayerXPos - 1) + (nPlayerYPos * nMapWidth)] == '#')
			return true;
		return false;
	case 'null':
		return false;
	}

	return false;
}

int Eating(wchar_t *screen, int nPlayerXPrev, int nPlayerYPrev, int nScore)
{
	char cEaten = screen[nPlayerXPos + (nPlayerYPos* nMapWidth)];

	// Increment score based on what was eaten
	if (cEaten == '.')
		nScore += 10;
	else if (cEaten == 'O')
		nScore += 50;

	return nScore;
}