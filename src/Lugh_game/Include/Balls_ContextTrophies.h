#ifndef ___Balls__ContextTrophies__H___
#define ___Balls__ContextTrophies__H___

#include <Tornado.h>

#include "Balls_TrophiesManager.h"

using namespace Tornado;

class BallsContextTrophies : public CContext
{

private:
	BallsTrophiesManager TrophiesManager;

	bool TrophiesUnlocked[6];
	bool ViewMode;
	uint16 TrophySelected;
	//irr::video::ITexture *BackgroundImage;

	irr::video::ITexture *TrophiesTitleImage;
	irr::video::ITexture *TrophiesBackgroundImage[6];
	irr::video::ITexture *TrophiesCardsImage[6];
	irr::video::ITexture *TrophiesHiddenImage;
	irr::video::ITexture *TrophiesCrosshairImage;
	irr::video::ITexture *BackNormalImage;
	irr::video::ITexture *BackHoverImage;

	irr::scene::IAnimatedMesh *LughsMesh[6];

	irr::gui::IGUIImage *TrophiesTitle;
	irr::gui::IGUIImage *TrophiesBackground[6];
	irr::gui::IGUIImage *TrophiesCards[6];
	irr::gui::IGUIImage *TrophiesHidden[6];
	irr::gui::IGUIImage *TrophiesCrosshair;

	irr::gui::IGUIImage *BackNormal;
	irr::gui::IGUIImage *BackHover;

	irr::core::vector2d<irr::s32> TrophiesTitlePosition;
	irr::core::vector2d<irr::s32> TrophiesBackgroundPosition;
	irr::core::vector2d<irr::s32> TrophiesCardsPosition[6];
	irr::core::vector2d<irr::s32> BackPosition;

	irr::scene::IAnimatedMeshSceneNode *Lughs[6];

	//irr::core::vector2d<irr::s32> BackgroundPosition;
	//irr::core::rect<irr::s32> BackgroundRect;

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
	BallsContextTrophies(uint16 Id,bool HaveLoading);
	~BallsContextTrophies();

	bool Init(void);

	void Prepare(void);
	void Next(real Delta);
	void Draw(void);
	void End(void);

	bool LoadingInit(void);
	void LoadingPrepare(void);
	void LoadingNext(real Delta);
	void LoadingDraw(void);
	void LoadingEnd(void);

	void Close(void);

	bool OnGUIEvent(irr::gui::IGUIElement *Caller,irr::gui::IGUIElement *Element,const uint16 &EventType );
	bool OnKeyInput(const uint16 &Key,const wchar_t &Char,const bool isCtrl,const bool isShift,const bool isPressedDown);
	bool OnMouseInput(const uint16 &EventType,const sint32 &X,const sint32 &Y,const real &Wheel,const bool isLeft,const bool isMiddle,const bool isRight,const bool isCtrl,const bool isShift);

};

#endif
