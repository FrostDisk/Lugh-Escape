#ifndef ___Balls__ContextScoreboard__H___
#define ___Balls__ContextScoreboard__H___

#include <Tornado.h>

#include "Balls_Scoreboard.h"

using namespace Tornado;

class BallsContextScoreboard : public CContext
{

private:
	BallsScoreboard Scoreboard;

	CClock Clock;

	irr::gui::IGUIFont* HUD;// Fuente usada para la HUD
	irr::gui::IGUIFont* NameFont;//Fuente usa para el 'nombre'

	audiere::OutputStreamPtr ScoreMusic;

	irr::video::ITexture *BackgroundImage;
	irr::video::ITexture *TitleImage;
	irr::video::ITexture *TableNameImage;
	irr::video::ITexture *TableScoreImage;
	irr::video::ITexture *TableLevelImage;
	irr::video::ITexture *TableLineImage;

	irr::core::vector2d<irr::s32> BackgroundPosition;
	irr::core::rect<irr::s32> BackgroundRect;

	irr::core::vector2d<irr::s32> TitlePosition;
	irr::core::vector2d<irr::s32> TableNamePosition;
	irr::core::vector2d<irr::s32> TableScorePosition;
	irr::core::vector2d<irr::s32> TableLevelPosition;
	irr::core::vector2d<irr::s32> TableLinePosition;

	struct
	{
		irr::core::rect<irr::s32> Id,Name,Score,Level;
	} Positions[10];
	

protected:
public:
	BallsContextScoreboard(uint16 Id);
	~BallsContextScoreboard();

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
