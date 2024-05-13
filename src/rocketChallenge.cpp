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

	float rocketPosition = 0.0f;
	float rocketVelocity = 0.0f;
	float rocketAcceleration = 0.0f;

protected:
	// Called by olcConsoleGameEngine
	virtual bool OnUserCreate()
	{
        //tbd
		return true;
	}

	// Called by olcConsoleGameEngine
	virtual bool OnUserUpdate(float fElapsedTime)
	{
        //tbd
        return true;
    }

}


int main()
{
	// Use olcConsoleGameEngine derived app
	RocketChallenge game;
	if (game.Construct(640, 300, 2, 2))
        game.Start();

	return 0;
}