#include "Balls_ContextTrophies.h"
#include "Balls_Contexts.h"
#include "Balls_GUIControl.h"

using namespace Tornado;

BallsContextTrophies::BallsContextTrophies(uint16 contextId,bool haveLoading) :
				CContext(contextId,haveLoading),
				TrophiesManager(),
				ViewMode(false),
				TrophySelected(0),
				TrophiesTitleImage(NULL),
				//TrophiesBackgroundImage(NULL),
				//TrophiesCardsImage(NULL),
				TrophiesHiddenImage(NULL),
				TrophiesCrosshairImage(NULL),
				BackNormalImage(NULL),
				BackHoverImage(NULL),
				//LughMesh(NULL),
				TrophiesTitle(NULL),
				//TrophiesBackground(NULL),
				//TrophiesCards(NULL),
				//TrophiesHidden(NULL),
				TrophiesCrosshair(NULL),
				BackNormal(NULL),
				BackHover(NULL),
				TrophiesTitlePosition(),
				TrophiesBackgroundPosition(),
				//TrophiesCardsPosition(),
				BackPosition()
				//Lughs(NULL)
{
}

BallsContextTrophies::~BallsContextTrophies()
{
	#if defined(_DEBUG)
	COutput::Wprintf(L"Destruyendo BallsContextTrophies(%d)\n",GetId());
	#endif
}

bool BallsContextTrophies::Init(void)
{
	irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();
	irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

	wchar_t Path[ __TORNADO_PATH_LENGTH ];
	if( GameDevices->Config->CreateFilenameProfilePath( Path , L"trophies.xml" , EPL_SAVEDATA ) )
	{
		TrophiesManager.SetFilename( Path );
	}
	TrophiesManager.InitTrophies();

	TrophiesTitleImage = driver->getTexture("trophies/texto_desbloqueables.png");

	TrophiesBackgroundImage[0] = driver->getTexture("trophies/texto1.png");
	TrophiesBackgroundImage[1] = driver->getTexture("trophies/texto2.png");
	TrophiesBackgroundImage[2] = driver->getTexture("trophies/texto3.png");
	TrophiesBackgroundImage[3] = driver->getTexture("trophies/texto4.png");
	TrophiesBackgroundImage[4] = driver->getTexture("trophies/texto5.png");
	TrophiesBackgroundImage[5] = driver->getTexture("trophies/texto6.png");

	TrophiesCardsImage[0] = driver->getTexture("trophies/secret01.png");
	TrophiesCardsImage[1] = driver->getTexture("trophies/secret02.png");
	TrophiesCardsImage[2] = driver->getTexture("trophies/secret03.png");
	TrophiesCardsImage[3] = driver->getTexture("trophies/secret04.png");
	TrophiesCardsImage[4] = driver->getTexture("trophies/secret05.png");
	TrophiesCardsImage[5] = driver->getTexture("trophies/secret06.png");

	TrophiesHiddenImage = driver->getTexture("trophies/secret00_base.png");
	TrophiesCrosshairImage = driver->getTexture("trophies/cubre_desbloqueable_desbloqueado.png");
	BackNormalImage = driver->getTexture("trophies/Boton_Volver_normal.png");
	BackHoverImage = driver->getTexture("trophies/Boton_Volver_sobre.png");

	LughsMesh[0] = smgr->getMesh("main/Lugh_full_posicion_01.obj");
	LughsMesh[1] = smgr->getMesh("main/LughIndy.obj");
	LughsMesh[2] = smgr->getMesh("main/2d_lugh.obj");
	LughsMesh[3] = smgr->getMesh("main/lughBolitaGrande.obj");
	LughsMesh[4] = smgr->getMesh("main/LughSwat.obj");
	LughsMesh[5] = smgr->getMesh("main/LughTengen.obj");

	TrophiesTitlePosition = irr::core::vector2d<irr::s32>( Width/2-140,Height/2-290 );
	TrophiesBackgroundPosition = irr::core::vector2d<irr::s32>( Width/2-400 , Height/2-300 );

	TrophiesCardsPosition[0] = irr::core::vector2d<irr::s32>( Width/2-320 , Height/2-200 );
	TrophiesCardsPosition[1] = irr::core::vector2d<irr::s32>( Width/2-64 , Height/2-200 );
	TrophiesCardsPosition[2] = irr::core::vector2d<irr::s32>( Width/2+192 , Height/2-200 );
	TrophiesCardsPosition[3] = irr::core::vector2d<irr::s32>( Width/2-320 , Height/2+50 );
	TrophiesCardsPosition[4] = irr::core::vector2d<irr::s32>( Width/2-64 , Height/2+50 );
	TrophiesCardsPosition[5] = irr::core::vector2d<irr::s32>( Width/2+192 , Height/2+50 );

	BackPosition = irr::core::vector2d<irr::s32>( Width-256 , Height-64 );

	//BackgroundPosition = irr::core::vector2d<irr::s32>( 0 , 0 );
	//BackgroundRect = irr::core::rect<irr::s32>( 0 , 0 , Width , Height );
	return true;
}

void BallsContextTrophies::Prepare(void)
{
	irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();
	irr::gui::IGUISkin *skin = GameDevices->GUIEnvironment->GetGUISkin();

	GameDevices->Video->SetVideoColor( irr::video::SColor(0xFF,0x00,0x99,0x33) );
	GameDevices->Video->SetCursorVisibility(true);

	if( TrophiesManager.LoadTrophies() )
	{
		#if defined(_DEBUG)
		COutput::Wprintf(L"Se terminaron de leer los datos de trofeos\n");
		#endif
	}

	irr::scene::ICameraSceneNode *cam = smgr->addCameraSceneNode();//FPS(0,50.0f,0.03f);
	cam->setPosition( irr::core::vector3df(-24.265377f,13.920190f,68.093254f));
	cam->setTarget( irr::core::vector3df(16.691845f,16.768436f,6.989529f));

	TrophiesCrosshair = env->addImage(TrophiesCrosshairImage,irr::core::vector2d<irr::s32>(0,0));
	TrophiesCrosshair->setVisible(false);

	for(int i=0;i<6;i++)
	{
		TrophiesBackground[i] = env->addImage( TrophiesBackgroundImage[i] , TrophiesBackgroundPosition );
		TrophiesBackground[i]->setVisible(false);

		TrophiesCards[i] = env->addImage( TrophiesCardsImage[i] , TrophiesCardsPosition[i] , true , 0 , 100 + i );
		TrophiesCards[i]->setVisible(false);

		TrophiesHidden[i] = env->addImage( TrophiesHiddenImage , TrophiesCardsPosition[i] , true , 0 , 50 + i);
		TrophiesHidden[i]->setVisible(true);

		Lughs[i] = smgr->addAnimatedMeshSceneNode( LughsMesh[i] );
		Lughs[i]->setMaterialFlag( irr::video::EMF_LIGHTING , false );
		Lughs[i]->setRotation( irr::core::vector3df(0.0f,180.0f,0.0f));
		Lughs[i]->setVisible(false);

		irr::scene::ISceneNodeAnimator *anim = smgr->createRotationAnimator(irr::core::vector3df(0.0f,0.2f,0.0f));
		if( anim )
		{
			Lughs[i]->addAnimator( anim );
		}
	}

	if( (TrophiesUnlocked[0] = TrophiesManager.IsUnlockedTrophy(TROPHY_LUGH)) ){ TrophiesCards[0]->setVisible(true);TrophiesHidden[0]->setVisible(false); }
	if( (TrophiesUnlocked[1] = TrophiesManager.IsUnlockedTrophy(TROPHY_JOE)) ){ TrophiesCards[1]->setVisible(true);TrophiesHidden[1]->setVisible(false); }
	if( (TrophiesUnlocked[2] = TrophiesManager.IsUnlockedTrophy(TROPHY_RETRO)) ){ TrophiesCards[2]->setVisible(true);TrophiesHidden[2]->setVisible(false); }
	if( (TrophiesUnlocked[3] = TrophiesManager.IsUnlockedTrophy(TROPHY_BALL)) ){ TrophiesCards[3]->setVisible(true);TrophiesHidden[3]->setVisible(false); }
	if( (TrophiesUnlocked[4] = TrophiesManager.IsUnlockedTrophy(TROPHY_SARGE)) ){ TrophiesCards[4]->setVisible(true);TrophiesHidden[4]->setVisible(false); }
	if( (TrophiesUnlocked[5] = TrophiesManager.IsUnlockedTrophy(TROPHY_MASHI)) ){ TrophiesCards[5]->setVisible(true);TrophiesHidden[5]->setVisible(false); }

	TrophiesTitle = env->addImage(TrophiesTitleImage,TrophiesTitlePosition);

	BackNormal = env->addImage(BackNormalImage,BackPosition,true,0,BGC_BACKNORMAL);
	BackHover = env->addImage(BackHoverImage,BackPosition,true,0,BGC_BACKHOVER);

	BackNormal->setVisible(false);
	BackHover->setVisible(false);
}

void BallsContextTrophies::Next(real Delta)
{
}

void BallsContextTrophies::Draw(void)
{
	irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;

	/*driver->draw2DImage(	BackgroundImage  ,
							BackgroundPosition ,
							BackgroundRect );*/

	GameDevices->GUIEnvironment->DrawGUI( driver );
	GameDevices->SceneManager->DrawScene( driver );

}

void BallsContextTrophies::End(void)
{
}

bool BallsContextTrophies::LoadingInit(void)
{
	irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
	irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

	LoadingBackgroundImage = driver->getTexture(L"loading/tiled_99.jpg");
	LoadingTextImage = driver->getTexture(L"loading/cargando.png");

	wchar_t texturePath[64];

	for( uint16 i=0 ; i<24 ; i++ )
	{
		COutput::Wsprintf( texturePath , L"loading/roundillo_s%02d.png", i+1 );
		LoadingLughImage[ i ] = driver->getTexture( texturePath );
	}
	BgRect = irr::core::rect<irr::s32>( 0 , 0 , Width , Height );
	BgPosition = irr::core::vector2d<irr::s32>( 0 , 0 );

	PigRect = irr::core::rect<irr::s32>( 0 , 0 , 64 , 64 );
	PigPosition = irr::core::vector2d<irr::s32>( Width - 80 , Height - 80 );

	TextRect = irr::core::rect<irr::s32>( 0 , 0 , 256 , 64 );
	TextPosition = irr::core::vector2d<irr::s32>( Width - 336 , Height - 80 );

	return true;
}

void BallsContextTrophies::LoadingPrepare(void)
{
	ActualPig = 0;
	LoadingClock.EnableTimer( 0.033f );
}

void BallsContextTrophies::LoadingNext(real delta)
{
	LoadingClock.Next( delta );

	if( LoadingClock.WaitTimer() )
	{
		ActualPig += 1;
		ActualPig %= 24;
		LoadingClock.EnableTimer( 0.033f );
	}
}

void BallsContextTrophies::LoadingDraw(void)
{
	irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();

	driver->draw2DImage(	LoadingBackgroundImage  ,
							BgPosition ,
							BgRect );

	driver->draw2DImage(	LoadingLughImage[ ActualPig ] ,
							PigPosition , 
							PigRect , 
							0 , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) , true );

	driver->draw2DImage(	LoadingTextImage ,
							TextPosition , 
							TextRect , 
							0 , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) , true );
}

void BallsContextTrophies::LoadingEnd(void)
{
}

void BallsContextTrophies::Close(void)
{
}

bool BallsContextTrophies::OnGUIEvent(	irr::gui::IGUIElement *caller,
										irr::gui::IGUIElement *element,
										const uint16 &eventType )
{
	if( ViewMode )
	{
		// Presionar un Boton de la GUI
		switch( eventType )
		{
			default:
			{
				break;
			}

			// Mouse sobre un elemento
			case irr::gui::EGET_ELEMENT_HOVERED:
			{
				irr::s32 id = caller->getID();

				switch(id)
				{
					default:
					{
						break;
					}

					case BGC_BACKNORMAL:
					{
						BackNormal->setVisible(false);
						BackHover->setVisible(true);
						break;
					}
				}
				break;
			}

			// Fuera de un elemento
			case irr::gui::EGET_ELEMENT_LEFT:
			{
				irr::s32 id = caller->getID();

				switch(id)
				{

					default:
					{
						break;
					}

					case BGC_BACKHOVER:
					{
						BackNormal->setVisible(true);
						BackHover->setVisible(false);
						break;
					}
				}
				break;
			}

			// Clic de un elemento
			case irr::gui::EGET_ELEMENT_FOCUSED:
			{
				irr::s32 id = caller->getID();

				switch(id)
				{

					default:
					{
						break;
					}

					case BGC_BACKHOVER:
					{
						BackNormal->setVisible(false);
						BackHover->setVisible(false);

						for(int j=0;j<6;j++)
						{
							if( TrophiesUnlocked[j] )
							{
								TrophiesCards[j]->setVisible(true);
							}
							else
							{
								TrophiesHidden[j]->setVisible(true);
							}
						}

						TrophiesBackground[TrophySelected]->setVisible(false);
						Lughs[TrophySelected]->setVisible(false);
						TrophiesTitle->setVisible(true);
						ViewMode = false;
						break;
					}
				}
				break;
			}
		}
	}
	else
	{
		for(int i=0;i<6;i++)
		{
			irr::s32 id = caller->getID();

			if( id == 100+i )
			{
				// Presionar un Boton de la GUI
				switch( eventType )
				{
					default:
					{
						break;
					}

					// Mouse sobre un elemento
					case irr::gui::EGET_ELEMENT_HOVERED:
					{	
						irr::core::rect<irr::s32> position = TrophiesCards[i]->getRelativePosition() + irr::core::vector2d<irr::s32>(-5,-5);
						TrophiesCrosshair->setVisible(true);
						TrophiesCrosshair->setRelativePosition( position.UpperLeftCorner );
						break;
					}

					// Fuera de un elemento
					case irr::gui::EGET_ELEMENT_LEFT:
					{
						TrophiesCrosshair->setVisible(false);
						break;
					}

					// Clic de un elemento
					case irr::gui::EGET_ELEMENT_FOCUSED:
					{
						for(int j=0;j<6;j++)
						{
							TrophiesCards[j]->setVisible(false);
							TrophiesHidden[j]->setVisible(false);
						}

						TrophiesBackground[i]->setVisible(true);
						Lughs[i]->setVisible(true);
						BackNormal->setVisible(true);
						BackHover->setVisible(false);
						TrophiesTitle->setVisible(false);

						TrophySelected = i;

						ViewMode = true;
					}
				}
			}
		}
	}
	return false;
}

bool BallsContextTrophies::OnKeyInput(	const uint16 &key,
										const wchar_t &keyChar,
										const bool isCtrl,
										const bool isShift,
										const bool isPressedDown )
{
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();

	if( isPressedDown )
	{
		switch( key )
		{
			case irr::KEY_ESCAPE:
			{
				if( !ViewMode )
				{
					Finalize(ID_TITLE);
				}
				break;
			}

			#if defined(_DEBUG)
			case irr::KEY_F2:
			{
				irr::scene::ICameraSceneNode *camera = smgr->getActiveCamera();
				irr::core::vector3df position = camera->getPosition();
				irr::core::vector3df target = camera->getTarget();
				#if defined(_DEBUG)
				COutput::Wprintf(L"Camara Posicion: (%f,%f,%f)\n",position.X,position.Y,position.Z);
				COutput::Wprintf(L"Camara Objetivo: (%f,%f,%f)\n",target.X,target.Y,target.Z);
				#endif
				break;
			}
			#endif

			default:
			{
			}
		}
	}
	return false;
}

bool BallsContextTrophies::OnMouseInput(	const uint16 &eventType,
										const sint32 &mouseX,
										const sint32 &mouseY,
										const real &wheel,
										const bool isLeft,
										const bool isMiddle,
										const bool isRight,
										const bool isCtrl,
										const bool isShift )
{
	return false;
}
