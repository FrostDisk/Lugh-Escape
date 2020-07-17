#ifndef ___Balls__ScoreData__H___
#define ___Balls__ScoreData__H___

#include <Tornado.h>
#include "Balls_Constants.h"

using namespace Tornado;

struct BallsScoreData
{
	BallsScoreData() :
				//Name(),
				Score(0),
				Level(0)
	{
	}

	wchar_t Name[ BUFFER_SIZE ];

	uint32 Score;

	uint16 Level;
};

#endif
