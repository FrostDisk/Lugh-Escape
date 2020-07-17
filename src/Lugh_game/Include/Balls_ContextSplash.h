#ifndef ___Balls__ContextSplash__H___
#define ___Balls__ContextSplash__H___

#include <Tornado.h>

using namespace Tornado;

class BallsContextSplash : public CSplashContext
{

private:
protected:
public:
	BallsContextSplash(uint16 Id);
	~BallsContextSplash();

	void Prepare(void);

	bool OnSplashFinishEvent(void);
};

#endif
