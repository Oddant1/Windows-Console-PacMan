#include "stdafx.h"

class Ghost_c {
		int nXPos, nYPos;
		int nXPrev, nYPrev;
		int nDir = 0;

		char cCovering = 'null';

	public:
		Ghost_c(int x, int y, wchar_t *screen)
		{
			nXPos = x;
			nYPos = y;

			screen[nXPos + (nYPos * nMapWidth)] = 'G';
		}

		void MoveGhost(wchar_t * screen);
};

void InitializeGhosts(wchar_t *screen)
{
	Ghost_c g_FirstGhost(13, 15, screen);
	Ghost_c g_SecondGhost(15, 15, screen);
	Ghost_c g_ThirdGhost(13, 16, screen);
	Ghost_c g_FourthGhost(15, 16, screen);
}

void Ghost_c::MoveGhost(wchar_t *screen)
{
	nXPrev = nXPos;
	nYPrev = nYPos;

	cCovering = screen[nXPos + (nYPos * nMapWidth)];

	switch (nDir)
	{
		case 1: nYPos--;
			break;
		case 2: nXPos++;
			break;
		case 3: nYPos++;
			break;
		case 4: nXPos--;
			break;
		case 0: break;
	}
}