#include "Balls_ContextSplash.h"
#include "Balls_Contexts.h"

using namespace Tornado;

BallsContextSplash::BallsContextSplash(uint16 contextId) : CSplashContext(contextId)
{
}

BallsContextSplash::~BallsContextSplash()
{
	#if defined(_DEBUG)
	COutput::Wprintf(L"Destruyendo BallsContextSplash(%d)\n",GetId());
	#endif
}


void BallsContextSplash::Prepare(void)
{
	AddImageElement(L"Media/frostdisk_logo.png");
	//AddImageElement(L"Media/tornado_logo.png");

	BeginSplashAnimation();
}

bool BallsContextSplash::OnSplashFinishEvent(void)
{
	Finalize(ID_TITLE);
	return false;
}