#include "Balls_ContextCredits.h"
#include "Balls_Contexts.h"

using namespace Tornado;

BallsContextCredits::BallsContextCredits(uint16 contextId) : CContext(contextId),
				CreditsBackground(NULL),
				CreditsTitle(NULL),
				CreditsDetail(NULL),
				CreditsThanks(NULL),
				CreditsBackgroundPosition(),
				CreditsBackgroundRect(),
				CreditsTitlePosition(),
				CreditsDetailPosition(),
				CreditsThanksPosition(),
				Music(NULL)
{
}

BallsContextCredits::~BallsContextCredits()
{
	#if defined(_DEBUG)
	COutput::Wprintf(L"Destruyendo BallsContextCredits(%d)\n",GetId());
	#endif
}

bool BallsContextCredits::Init(void)
{
	irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
	irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
	irr::io::IFileSystem *file = GameDevices->Video->GetVideoDevice()->getFileSystem();

	CreditsBackground = driver->getTexture("loading/tiled_99.jpg");

	CreditsTitle = driver->getTexture("creditos/creditos_txt.png");
	CreditsDetail = driver->getTexture("creditos/creditos.png");
	CreditsThanks = driver->getTexture("creditos/gracias_x_jugar.png");

	CreditsBackgroundPosition = irr::core::vector2d<irr::s32>( 0 , 0 );
	CreditsBackgroundRect = irr::core::rect<irr::s32>( 0 , 0 , Width , Height );

	CreditsTitlePosition = irr::core::vector2d<irr::s32>( Width/2-390 , Height/2-290 );
	CreditsDetailPosition = irr::core::vector2d<irr::s32>( Width/2-390 , Height/2-190 );
	CreditsThanksPosition = irr::core::vector2d<irr::s32>( Width/2-197 , Height/2+200 );

	Music = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("music/lugh_creditos.ogg") , true , audiere::FF_OGG );

	return true;
}

void BallsContextCredits::Prepare(void)
{
	irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
	irr::gui::IGUISkin *skin = GameDevices->GUIEnvironment->GetGUISkin();

	GameDevices->Video->SetVideoColor( irr::video::SColor(0xFF,0x00,0x00,0x00) );
	GameDevices->Video->SetCursorVisibility(false);

	env->addImage( CreditsTitle , CreditsTitlePosition );
	env->addImage( CreditsDetail , CreditsDetailPosition );
	env->addImage( CreditsThanks , CreditsThanksPosition );

	if( Music )
	{
		Music->stop();
		Music->setPosition(0);
		Music->play();
	}
}

void BallsContextCredits::Next(real delta)
{
}

void BallsContextCredits::Draw(void)
{
	irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;

	driver->draw2DImage(	CreditsBackground  ,
							CreditsBackgroundPosition ,
							CreditsBackgroundRect );

	GameDevices->SceneManager->DrawScene( driver );
	GameDevices->GUIEnvironment->DrawGUI( driver );

}

void BallsContextCredits::Close(void)
{
}

void BallsContextCredits::End(void)
{
	if( Music )
	{
		Music->stop();
	}
}


bool BallsContextCredits::OnKeyInput(	const uint16 &key,
										const wchar_t &keyChar,
										const bool isCtrl,
										const bool isShift,
										const bool isPressedDown )
{
	/*if( tmp_isPressedDown ){
		Finalize(-1);
	}*/
	return false;
}

bool BallsContextCredits::OnMouseInput(	const uint16 &eventType,
										const sint32 &mouseX,
										const sint32 &mouseY,
										const real &wheel,
										const bool isLeft,
										const bool isMiddle,
										const bool isRight,
										const bool isCtrl,
										const bool isShift )
{
	if( eventType == irr::EMIE_LMOUSE_PRESSED_DOWN ){
		Finalize(-1);
	}
	return false;
}
