//author: Tobias Bittl

#include <iostream>
#include <string>
//using namespace std;

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"


class RocketChallenge : public olc::PixelGameEngine
{

public:
	RocketChallenge()
	{
		sAppName = "RocketChallange";
	}

private:

	float rPosition = 0.0f;
	float rVelocity = 0.0f;
	float rAcceleration = 0.0f;
	float rPosition = 0.0f;

	float rSectionWidth;
	std::list<int> listSection;

	bool rHasCollided = false;
	bool rResetGame = false;

	int nAttemptCount = 0;
	int nCrashCount = 0;
	int nMaxCrachCount = 0;


protected:
	// Called by olcConsoleGameEngine
	virtual bool OnUserCreate()
	{
   		listSection = { 0, 0, 0, 0 };
		rResetGame = true;
		rSectionWidth = (float)ScreenWidth() / (float)(listSection.size() - 1);
		return true;
	}

	// Called by olcConsoleGameEngine
	virtual bool OnUserUpdate(float fElapsedTime)
	{
		if (rResetGame)
		{
			rHasCollided = false;
			rResetGame = false;
			listSection = { 0, 0, 0, 0 };
			rBirdAcceleration = 0.0f;
			rBirdVelocity = 0.0f;
			rBirdPosition = ScreenHeight() / 2.0f;
			nCrashCount = 0;
			nAttemptCount++;
		}

		// Game
		if (rHasCollided)
		{
			// Does nothing until user releases space
			if (GetKey(olc::Key::SPACE).bReleased)
				bResetGame = true;
		}
		else
		{

			if (GetKey(olc::Key::SPACE).bPressed && rBirdVelocity >= rGravity / 10.0f)
			{
				rAcceleration = 0.0f;
				nCrashCount++;
				if (nCrashCount > nMaxCrashCount)
					nMaxCrashCount = nCrashCount;
			}
			else
				rBirdAcceleration += rGravity * fElapsedTime;

			if (rBirdAcceleration >= rGravity)
				rBirdAcceleration = rGravity;

			rBirdVelocity += rBirdAcceleration * fElapsedTime;
			rBirdPosition += rBirdVelocity * fElapsedTime;
			rLevelPosition += 14.0f * 8.0f * fElapsedTime;

			if (rLevelPosition > fSectionWidth)
			{
				rLevelPosition -= fSectionWidth;
				listSection.pop_front();
				int i = rand() % (ScreenHeight() - 20 * 8);
				if (i <= 10 * 8) i = 0;
				listSection.push_back(i);
			}

			// Display
			FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

			// Draw Sections
			int nSection = 0;
			for (auto s : listSection)
			{
				if (s != 0)
				{
					FillRect(nSection * fSectionWidth + 10 * 8 - rLevelPosition, ScreenHeight() - s, 5 * 8, s, olc::GREEN);
					FillRect(nSection * fSectionWidth + 10 * 8 - rLevelPosition, 0, 5 * 8, ScreenHeight() - s - (15 * 8), olc::GREEN );
				}
				nSection++;
			}

			int nRocketX = (int)(ScreenWidth() / 3.0f);

            // Collision detection

            // grab screen sprite pointer
            olc::Sprite *screenSprite = GetDrawTarget();
            // work out rocket collision box
            int nLt = nRocketX - 1;
            int nRt = nRocketX + 6 * 8;
            int nUp = (int)(r +  0);
            int nDn = (int)(r + 16);
            // check against screen boundaries and against non black pixels
            rHasCollided = r < 16 || r > ScreenHeight() - 16 ||
                    screenSprite->GetPixel( nLt, nUp ) != olc::BLACK ||
                    screenSprite->GetPixel( nLt, nDn ) != olc::BLACK ||
                    screenSprite->GetPixel( nRt, nUp ) != olc::BLACK ||
                    screenSprite->GetPixel( nRt, nDn ) != olc::BLACK ;

			// Draw rocket

				DrawString(nBirdX, r + 0, "-------\\");
				DrawString(nBirdX, r + 8, "-------/");
			}

			DrawString(8, 8, "Attempt: " + std::to_string(nAttemptCount) + " Score: " + std::to_string(nChrashCount) + " High Score: " + std::to_stCrash));
		}

		return true;
};



int main()
{
	
	RocketChallenge game;
	if (game.Construct(640, 300, 2, 2))
        game.Start();

	return 0;
}