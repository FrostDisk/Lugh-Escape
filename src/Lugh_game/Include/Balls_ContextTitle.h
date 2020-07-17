#ifndef ___Balls__ContextTitle__H___
#define ___Balls__ContextTitle__H___

#include <Tornado.h>

#include "Balls_TrophiesManager.h"

using namespace Tornado;

class BallsContextTitle : public CTitleContext
{

private:

	wchar_t *VersioNumber;

	BallsTrophiesManager TrophiesManager;

	irr::gui::IGUIFont *Font;

	irr::gui::IGUIStaticText *VersionText;
	irr::core::rect<irr::s32> VersionTextPosition;
	irr::video::SColor VersionTextColor;

	//EffectHandler* effect;
	irr::video::ITexture *Image1;
	irr::video::ITexture *Image2;

	irr::video::ITexture *Title;
	irr::core::vector2d<irr::s32> TitlePosition;

	irr::video::ITexture *TrophiesNormalImage;
	irr::video::ITexture *TrophiesHoverImage;

	irr::gui::IGUIImage *TrophiesNormal;
	irr::gui::IGUIImage *TrophiesHover;

	irr::core::vector2d<irr::s32> TrophiesPosition;

	irr::video::ITexture *MiniMessage;
	irr::core::vector2d<irr::s32> MiniMessagePosition;

	irr::scene::IAnimatedMesh* SceneMesh;
	irr::video::ITexture *SceneTexture;

	audiere::OutputStreamPtr TitleMusic;

	audiere::OutputStreamPtr MenuHover;
	audiere::OutputStreamPtr MenuPressed;

	struct {
		irr::video::ITexture *Image;
		irr::video::ITexture *Hover;
		irr::video::ITexture *Pressed;

		irr::core::vector2di Position;

	} NewGame,Scoreboard,Options,Quit;

	struct RowScroll {
		irr::gui::IGUIImage *image;
		irr::core::vector2d<irr::s32> position;
		irr::s32 height;
		real offset;
	};

	std::list<RowScroll *> ElementosLeft;
	std::list<RowScroll *> ElementosRight;
	RowScroll *FirstLeft;
	RowScroll *FirstRight;
	real Velocity;
	
	uint16 ActualPig;
	CClock LoadingClock; // Reloj para Loading
	irr::video::ITexture *LoadingBackgroundImage;// Imagen de Fondo del Tiempo de Carga
	irr::video::ITexture *LoadingTextImage;// Imagen de "Cargando"
	irr::video::ITexture *LoadingLughImage[24];// Imagenes del Chanchito girando
	irr::core::rect<irr::s32> BgRect;
	irr::core::vector2d<irr::s32> BgPosition;
	irr::core::rect<irr::s32> PigRect;
	irr::core::vector2d<irr::s32> PigPosition;
	irr::core::rect<irr::s32> TextRect;
	irr::core::vector2d<irr::s32> TextPosition;

protected:
public:
	BallsContextTitle(uint16 Id,bool HaveLoading,wchar_t *versionNumber);
	~BallsContextTitle();

	bool Init(void);
	void Prepare(void);
	void Next(real Delta);
	void End(void);

	bool LoadingInit(void);
	void LoadingPrepare(void);
	void LoadingNext(real Delta);
	void LoadingDraw(void);
	void LoadingEnd(void);

	bool OnHoverElement(void);
	bool OnPressedElement(void);

	bool OnGUICustomEvent(irr::gui::IGUIElement *Caller,irr::gui::IGUIElement *Element,const uint16 &EventType);
	bool OnNewGameEvent(void);
	bool OnLoadGameEvent(void);
	bool OnQuitGameEvent(void);
};

#endif