#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#include "olcConsoleGameEngine.h"

class BreakOut : public olcConsoleGameEngine
{
public:
	BreakOut()
	{
		m_sAppName = L"Break  Out";
	}
	virtual bool OnUserCreate()
	{
		level += "################";
		level += "#..............#";
		level += "#...11111111...#";
		level += "#...11111111...#";
		level += "#...11111111...#";
		level += "#...11111111...#";
		level += "#..............#";
		level += "#..............#";
		level += "#..............#";
		level += "#..............#";
		level += "#..............#";
		level += "#..............#";
		level += "#..............#";
		level += "#..............#";
		level += "#..............#";

		//float fAngle = ((float)rand() / (float)(RAND_MAX)) * 2 * 3.14;
		
		return true;
	}



	virtual bool OnUserUpdate(float fElapsedTime)
	{
		
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');
		float fSpeed = 60.0f;

		if (GetKey(VK_LEFT).bHeld) fBat -= 30.0f *fElapsedTime;
		if (GetKey(VK_RIGHT).bHeld) fBat += 30.0f *fElapsedTime;

		// This will ensure bath within the fields 
		if (fBat - nBatWidth < nBlock)
			fBat = nBlock + nBatWidth;

		if (fBat + nBatWidth > (nWidth - 1)* nBlock)
			fBat = (nWidth - 1)* nBlock - nBatWidth;

		float fOldX = fBallX;
		float fOldY = fBallY;

		fBallX += fBallDX * fElapsedTime *fSpeed;
		fBallY += fBallDY * fElapsedTime *fSpeed;
		

		int nCellOldX = ((int)fOldX) / nBlock;
		int nCellOldY = ((int)fOldY) / nBlock;
		int nCellNewX = ((int)fBallX) / nBlock;
		int nCellNewY = ((int)fBallY) / nBlock;

		char newCell = level[nCellNewY*nWidth + nCellNewX];
		char oldCell = level[nCellOldY*nWidth + nCellOldX];

		if (newCell != '.')
		{
			if (newCell == '1')
				level[nCellNewY*nWidth + nCellNewX] = '.';

			if (nCellNewX != nCellOldX) fBallDX *= -1;
			if (nCellNewY != nCellOldY) fBallDY *= -1;

			
		}

		if (fBallY > nHeight*nBlock - 2)
		{
			if (fBallX > (fBat-nBatWidth) && fBallX < (fBat + nBatWidth))
			{
				fBallDY *= -1;
			}
			else
			{
				//Dead
				fBallX = (nWidth *nBlock) / 2;
				fBallY = (nHeight *nBlock) / 2;
				float fAngle = 0.6f;
				float fBallDX = cosf(fAngle);
				float fBallDY = sinf(fAngle);

			}
		}

		for (int y = 0; y < nHeight; y++)
		{
			for (int x = 0; x < nWidth; x++)
			{
				switch (level[y*nWidth + x])
				{
				case '.':
					Fill(x*nBlock, y*nBlock, (x + 1)*nBlock, (y + 1)*nBlock, PIXEL_SOLID, FG_BLACK);
						break;
				case '#':
					Fill(x*nBlock, y*nBlock, (x + 1)*nBlock, (y + 1)*nBlock, PIXEL_SOLID, FG_WHITE);
					break;
				case '1':
					Fill(x*nBlock, y*nBlock, (x + 1)*nBlock, (y + 1)*nBlock, PIXEL_SOLID, FG_GREEN);
					break;

				}
			}
		}
		FillCircle(fBallX, fBallY, 2.0f, PIXEL_SOLID, FG_YELLOW);
		DrawLine(fBat - nBatWidth, nHeight*nBlock - 2, fBat + nBatWidth, nHeight*nBlock - 2, PIXEL_SOLID, FG_WHITE);

		return true;
	}
	
	string level;
	int nWidth = 16;
	int nHeight = 15;
	int nBlock = 8;
	int nBatWidth = 10;
	float fBat = 60;
	float fBallX = 64.0f;
	float fBallY = 64.0f;
	float fAngle = 0.6f;
	float fBallDX = cosf(fAngle);
	float fBallDY = sinf(fAngle);
};

int main()
{
	BreakOut game;
	game.ConstructConsole(160, 160, 4, 4);
	//game.ConstructConsole(256, 240, 4, 4);---------> This is throwing error 
	game.Start();
	return 0;
}
