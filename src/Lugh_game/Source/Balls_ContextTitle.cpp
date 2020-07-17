#include "Balls_ContextTitle.h"
#include "Balls_Contexts.h"
#include "Balls_GUIControl.h"

BallsContextTitle::BallsContextTitle(uint16 contextId,bool haveLoading,wchar_t *version) : 
											CTitleContext(contextId,haveLoading),
                                                VersioNumber(version),
												TrophiesManager(),
												Image1(NULL),
												Image2(NULL),
												Title(NULL),
												TitlePosition(),
												MiniMessage(NULL),
												MiniMessagePosition(),
												SceneMesh(NULL),
												SceneTexture(NULL),
												TitleMusic(NULL),
												MenuHover(NULL),
												MenuPressed(NULL),
												NewGame(),
												Scoreboard(),
												Options(),
												Quit(),
												ElementosLeft(),
												ElementosRight(),
												FirstLeft(NULL),
												FirstRight(NULL),
												Velocity(10.0f)
{
}

BallsContextTitle::~BallsContextTitle()
{
	#if defined(_DEBUG)
	COutput::Wprintf(L"Destruyendo BallsContextTitle(%d)\n",GetId());
	#endif
}

bool BallsContextTitle::Init(void)
{
	irr::IrrlichtDevice *device = GameDevices->Video->GetVideoDevice();

	irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
	irr::gui::IGUISkin *skin = GameDevices->GUIEnvironment->GetGUISkin();
	irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();
	irr::io::IFileSystem *file = GameDevices->Video->GetVideoDevice()->getFileSystem();

	for(irr::u32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
	{
		irr::video::SColor col = skin->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
		col.setAlpha(0xDD);
		skin->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, col);
	}

	GameDevices->Video->SetVideoColor( irr::video::SColor(0x00,0x00,0x00,0x00) );

	wchar_t Path[ __TORNADO_PATH_LENGTH ];
	if( GameDevices->Config->CreateFilenameProfilePath( Path , L"trophies.xml" , EPL_SAVEDATA ) )
	{
		TrophiesManager.SetFilename( Path );
	}
	TrophiesManager.InitTrophies();

	Font = env->getFont(L"font/fontlucida.png");

	VersionTextPosition = irr::core::rect<irr::s32>(Width-90,0,Width,15);
	VersionTextColor = irr::video::SColor(0xFF,0x00,0x00,0xFF);

	Image1 = driver->getTexture("title/tiled_89.png");
	Image2 = driver->getTexture("title/tiled_99.png");

	Title = driver->getTexture("title/title_01.png");
	TitlePosition = irr::core::vector2d<irr::s32>(Width/2-512,Height/2-400);

	TrophiesNormalImage = driver->getTexture("hud/Boton_desbloqueados_normal.png");
	TrophiesHoverImage = driver->getTexture("hud/Boton_desbloqueados_sobre.png");

	TrophiesPosition = irr::core::vector2d<irr::s32>( 0 , Height-64 );

	//SceneMesh = smgr->getMesh("title/room.3ds");
	//SceneTexture = driver->getTexture("title/room.jpg");

	irr::s32 y1 = (Height/2-190)/2+Height/2;
	irr::s32 x1 = Width/2-256;
	//irr::s32 x2 = (Width/2+250)/2;

	NewGame.Image = driver->getTexture("title/botones_s02.png");
	NewGame.Hover = driver->getTexture("title/botones_s01.png");
	//NewGame.Pressed = driver->getTexture("Media/balls/newgame_pressed.png");
	NewGame.Position = irr::core::vector2d<irr::s32>(x1,y1-64);

	Scoreboard.Image = driver->getTexture("title/botones_s04.png");
	Scoreboard.Hover = driver->getTexture("title/botones_s03.png");
	//Scoreboard.Pressed = driver->getTexture("Media/balls/loadgame_pressed.png");
	Scoreboard.Position = irr::core::vector2d<irr::s32>(x1,y1);

	Options.Image = driver->getTexture("title/botones_s06.png");
	Options.Hover = driver->getTexture("title/botones_s05.png");
	//Options.Pressed = driver->getTexture("Media/balls/options_pressed.png");
	Options.Position = irr::core::vector2d<irr::s32>(x1,y1+64);

	Quit.Image = driver->getTexture("title/botones_s08.png");
	Quit.Hover = driver->getTexture("title/botones_s07.png");
	//Quit.Pressed = driver->getTexture("Media/balls/quit_pressed.png");
	Quit.Position = irr::core::vector2d<irr::s32>(x1,y1+128);

	MiniMessage = driver->getTexture("title/inferior_derecho.png");
	MiniMessagePosition = irr::core::vector2d<irr::s32>(Width-512,Height-64);

	TitleMusic = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("music/lugh_menu.ogg") , true , audiere::FF_OGG );

	MenuHover = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("sound/mousesobreopcion.wav") , false , audiere::FF_WAV );
	MenuPressed = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("sound/opcionmenu.wav") , false , audiere::FF_WAV );

	return true;
}

void BallsContextTitle::Prepare(void)
{
	//COutput::Wprintf(L"Cambio de Contexto\n");

	irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
	irr::gui::IGUISkin *skin = GameDevices->GUIEnvironment->GetGUISkin();
	irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();

	GameDevices->Video->SetCursorVisibility(true);

	smgr->loadScene("main/world_02.irr");

	if( Font )
	{
		skin->setFont( Font );
	}

	if( TrophiesManager.LoadTrophies() )
	{
		#if defined(_DEBUG)
		COutput::Wprintf(L"Se terminaron de leer los datos de trofeos\n");
		#endif
	}

	/*RowScroll *auxScroll;
	uint16 max = Height / 64;
	if( Height % 64 > 1 )max++;
	for(int i=0;i<max+1;i++)
	{
		//env->addImage( Image1 , irr::core::vector2d<irr::s32>(0,i*64) );
		//env->addImage( Image2 , irr::core::vector2d<irr::s32>(Width-256,i*64) );

		#if defined(_DEBUG)
		COutput::Wprintf(L"(%d,%d) (%d,%d)\n",0,64*(i-1),Width-256,64*(i-1));
		#endif
		auxScroll = new RowScroll();
		auxScroll->position = irr::core::vector2d<irr::s32>(0,64*(i-1));
		auxScroll->image = env->addImage( Image1 , auxScroll->position );
		auxScroll->height = 64;
		auxScroll->offset = (real)auxScroll->position.Y;
		FirstLeft = FirstLeft ? FirstLeft : auxScroll;
		ElementosLeft.push_back( auxScroll );

		auxScroll = new RowScroll();
		auxScroll->position = irr::core::vector2d<irr::s32>(Width-256,64*(i-1));
		auxScroll->image = env->addImage( Image2 , auxScroll->position );
		auxScroll->height = 64;
		auxScroll->offset = (real)auxScroll->position.Y;
		FirstRight = FirstRight ? FirstRight : auxScroll;
		ElementosRight.push_back( auxScroll );
	}*/

	env->addImage( Title , TitlePosition );
	env->addImage( MiniMessage , MiniMessagePosition );

	CreateNewGameImageElement( NewGame.Position , NewGame.Image , NewGame.Hover );
	CreateLoadGameImageElement( Scoreboard.Position , Scoreboard.Image , Scoreboard.Hover );
	CreateOptionsImageElement( Options.Position , Options.Image , Options.Hover );
	CreateQuitGameImageElement( Quit.Position , Quit.Image , Quit.Hover );

	TrophiesNormal = env->addImage( TrophiesNormalImage , TrophiesPosition , true , 0 , BGC_TROPHYNORMAL );
	TrophiesHover = env->addImage( TrophiesHoverImage , TrophiesPosition , true , 0 , BGC_TROPHYHOVER );
	TrophiesNormal->setVisible(false);
	TrophiesHover->setVisible(false);

	if( TrophiesManager.GetUnlockedNumber()>0 )
	{
		TrophiesNormal->setVisible(true);
	}

	VersionText = GameDevices->GUIEnvironment->GetGUIEnvironment()->addStaticText(VersioNumber,VersionTextPosition,false,false);
	VersionText->setOverrideColor(VersionTextColor);



	//smgr->getMeshManipulator()->makePlanarTextureMapping( SceneMesh->getMesh(0), 0.004f);

	irr::scene::ISceneNode* node = 0;
	//node = smgr->addAnimatedMeshSceneNode( SceneMesh );
	//node->setMaterialTexture(0, SceneTexture );
	//node->getMaterial(0).SpecularColor.set(0,0,0,0);
	//node->setMaterialFlag(irr::video::EMF_LIGHTING, false);


	irr::scene::ICameraSceneNode* cam = smgr->addCameraSceneNode();
	node = smgr->addLightSceneNode( cam , irr::core::vector3df(0,0,0),
		irr::video::SColorf(1.0f, 0.8f, 0.8f, 1.0f), 100.0f);

	/*node = smgr->addLightSceneNode( 0 , irr::core::vector3df(0,0,0),
		irr::video::SColorf(1.0f, 0.8f, 0.8f, 1.0f), 800.0f);*/
	irr::scene::ISceneNodeAnimator* anim = 0;

	/*anim = smgr->createFlyCircleAnimator (irr::core::vector3df(0,150,0),250.0f);
	node->addAnimator(anim);
	anim->drop();*/



	/*E_FILTER_TYPE filterType = (E_FILTER_TYPE)irr::core::clamp<irr::u32>(0, 0, 4);
	effect->addShadowToNode( node , filterType);*/

	// Set a global ambient color. A very dark gray.
	
	//effect->setAmbientColor(irr::video::SColor(255, 32, 32, 32));


	// attach billboard to light

	/*node = smgr->addBillboardSceneNode(node, irr::core::dimension2d<irr::f32>(50, 50));
	node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	node->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	node->setMaterialTexture(0, driver->getTexture("Media/balls/particlewhite.bmp"));*/

	cam->setTarget(irr::core::vector3df(33.402851f,28.036221f,-11.625000f));

	anim = smgr->createFlyCircleAnimator( irr::core::vector3df(0.0f,50.0f,0.0f) , 100.0f , 0.00003f);
	cam->addAnimator(anim);
	anim->drop();

	real MusicVolume = (real)GameDevices->Audio->GetMusicVolume() * 0.01f;
	real SoundVolume = (real)GameDevices->Audio->GetSoundVolume() * 0.01f;

	if( TitleMusic )
	{
		TitleMusic->setVolume( MusicVolume );
		TitleMusic->setRepeat( true );
		TitleMusic->setPosition( 0 );
		TitleMusic->play();
	}

	if( MenuHover )
	{
		MenuHover->setVolume( SoundVolume );
		MenuHover->setRepeat( false );
		MenuHover->setPosition( 0 );
	}

	if( MenuPressed )
	{
		MenuPressed->setVolume( SoundVolume );
		MenuPressed->setRepeat( false );
		MenuPressed->setPosition( 0 );
	}
	//PrepareDefaultGUI();
}

void BallsContextTitle::Next(real delta)
{
	/*std::list<RowScroll *>::iterator it;
	for(it=ElementosLeft.begin();it!=ElementosLeft.end();it++)
	{
		(*it)->offset += Velocity * Delta;
		(*it)->position.Y = (irr::s32)(*it)->offset;

		if( (*it)->position.Y > Height )
		{
			(*it)->offset = FirstLeft->offset - (real)(*it)->height + Velocity*Delta;
			(*it)->position.Y = (irr::s32)(*it)->offset;
			FirstLeft = (*it);
		}
		(*it)->image->setRelativePosition( (*it)->position );
	}

	for(it=ElementosRight.begin();it!=ElementosRight.end();it++)
	{
		(*it)->offset += Velocity * Delta;
		(*it)->position.Y = (irr::s32)(*it)->offset;

		if( (*it)->position.Y > Height )
		{
			(*it)->offset = FirstRight->offset - (real)(*it)->height + Velocity*Delta;
			(*it)->position.Y = (irr::s32)(*it)->offset;
			FirstRight = (*it);
		}
		(*it)->image->setRelativePosition( (*it)->position );
	}*/
}

void BallsContextTitle::End(void)
{
	if( TitleMusic )
	{
		TitleMusic->stop();
	}
}

bool BallsContextTitle::LoadingInit(void)
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

void BallsContextTitle::LoadingPrepare(void)
{
	ActualPig = 0;
	LoadingClock.EnableTimer( 0.033f );
}

void BallsContextTitle::LoadingNext(real delta)
{
	LoadingClock.Next( delta );

	if( LoadingClock.WaitTimer() )
	{
		ActualPig += 1;
		ActualPig %= 24;
		LoadingClock.EnableTimer( 0.033f );
	}
}

void BallsContextTitle::LoadingDraw(void)
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

void BallsContextTitle::LoadingEnd(void)
{
}



bool BallsContextTitle::OnHoverElement(void)
{
	if( MenuHover )
	{
		MenuHover->stop();
		MenuHover->setPosition(0);
		MenuHover->play();
	}
	return false;
}

bool BallsContextTitle::OnPressedElement(void){

	if( MenuPressed )
	{
		MenuPressed->play();
	}
	return false;
}

bool BallsContextTitle::OnGUICustomEvent(	irr::gui::IGUIElement *caller,
											irr::gui::IGUIElement *element,
											const uint16 &eventType )
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

				case BGC_TROPHYNORMAL:
				{
					TrophiesNormal->setVisible(false);
					TrophiesHover->setVisible(true);
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

				case BGC_TROPHYHOVER:
				{
					TrophiesNormal->setVisible(true);
					TrophiesHover->setVisible(false);
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

				case BGC_TROPHYHOVER:
				{
					Finalize(ID_TROPHIES);
					break;
				}
			}
			break;
		}
	}
	return false;
}

bool BallsContextTitle::OnNewGameEvent(void)
{
	Finalize(ID_MAIN);
	return false;
}

bool BallsContextTitle::OnLoadGameEvent(void)
{
	Finalize(ID_SCOREBOARD);
	return false;
}

bool BallsContextTitle::OnQuitGameEvent(void)
{
	//#if defined(_DEBUG)
	//Finalize(-1);
	//#else
	Finalize(ID_CREDITS);
	//#endif
	return false;
}
