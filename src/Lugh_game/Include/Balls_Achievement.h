#ifndef ___Balls__Achievement__H___
#define ___Balls__Achievement__H___

#include <Tornado.h>
#include "Balls_Constants.h"

using namespace Tornado;

struct BallsAchievement
{
	wchar_t Key[ KEY_SIZE ];

	wchar_t Hash[ HASH_SIZE ];

	uint16 Id;

	bool Unlocked;
};

#endif
