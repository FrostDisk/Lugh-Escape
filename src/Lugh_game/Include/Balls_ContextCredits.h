#ifndef ___Balls__ContextCredits__H___
#define ___Balls__ContextCredits__H___

#include <Tornado.h>

using namespace Tornado;

class BallsContextCredits : public CContext
{

private:

	irr::video::ITexture *CreditsBackground;

	irr::video::ITexture *CreditsTitle;
	irr::video::ITexture *CreditsDetail;
	irr::video::ITexture *CreditsThanks;

	irr::core::vector2d<irr::s32> CreditsBackgroundPosition;
	irr::core::rect<irr::s32> CreditsBackgroundRect;

	irr::core::vector2d<irr::s32> CreditsTitlePosition;
	irr::core::vector2d<irr::s32> CreditsDetailPosition;
	irr::core::vector2d<irr::s32> CreditsThanksPosition;
	

	audiere::OutputStreamPtr Music;

protected:
public:
	BallsContextCredits(uint16 Id);
	~BallsContextCredits();

	bool Init(void);

	void Prepare(void);
	void Next(real Delta);
	void Draw(void);
	void Close(void);
	void End(void);

	bool OnKeyInput(const uint16 &Key,const wchar_t &Char,const bool isCtrl,const bool isShift,const bool isPressedDown);
	bool OnMouseInput(const uint16 &EventType,const sint32 &X,const sint32 &Y,const real &Wheel,const bool isLeft,const bool isMiddle,const bool isRight,const bool isCtrl,const bool isShift);

};

#endif
