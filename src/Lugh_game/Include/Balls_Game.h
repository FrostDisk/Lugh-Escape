#ifndef ___Balls__Game__H___
#define ___Balls__Game__H___

#include <Tornado.h>
#include "Balls_ContextSplash.h"
#include "Balls_ContextTitle.h"
#include "Balls_ContextMain.h"
#include "Balls_ContextScoreboard.h"
#include "Balls_ContextCredits.h"
#include "Balls_ContextTrophies.h"

using namespace Tornado;

class BallsGame : public CGame
{

private:

	BallsContextSplash cSplash;
	BallsContextTitle cTitle;
	BallsContextMain cMain;
	BallsContextScoreboard cScoreboard;
	BallsContextCredits cCredits;
	BallsContextTrophies cTrophies;

	bool InitContexts(void);

protected:
	
	void RegisterMiscConfig(void);
	void PrepareMiscConfig(void);
	void PrepareAll(void);

public:
	BallsGame();
};

#endif
