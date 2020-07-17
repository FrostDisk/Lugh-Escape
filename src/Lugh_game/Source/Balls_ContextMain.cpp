#include "Balls_ContextMain.h"
#include "Balls_Contexts.h"
#include "Balls_Status.h"
#include "Balls_Flags.h"
#include "Balls_GUIControl.h"
#include <time.h>

uint16 BallsContextMain::Level = 1;
uint16 BallsContextMain::BossLevel = 1;
uint32 BallsContextMain::Puntaje = 0;
uint16 BallsContextMain::RemainingBombs = 3;
real BallsContextMain::RemainingTime = 60.0f;
irr::s32 BallsContextMain::BallSpeed = 1500;
irr::f32 BallsContextMain::BallRotationSpeed = 1.2f;
bool BallsContextMain::IsBossTime = false;
irr::s32 oldFps = 0;

BallsContextMain::BallsContextMain(uint16 contextId,bool haveLoading) : 
			CContext(contextId,haveLoading),
			AchievementUnlocked(false),
			Resources(),
			Nodes(),
			Variables(),
			Matrix(),
			Scoreboard(10),
			TrophiesManager(),
			Clock(0.0f,true),
			TrophyClock(),
			LoadingClock()
			#if defined(DEBUG_MODE)
			,DebugFPSMode(false),
			DebugDesp(1.0f),
			DebugNode(NULL)
			#endif
{
	srand( (unsigned)time(NULL) );
};

BallsContextMain::~BallsContextMain()
{
	#if defined(_DEBUG)
	COutput::Wprintf(L"Destruyendo BallsContextMain(%d)\n",GetId());
	#endif
}


bool BallsContextMain::Init(void)
{
	#pragma region declaraciones
	// Variables asociadas a los componentes gráficos (referencias directas a Irrlicht)
	irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
	irr::gui::IGUISkin *skin = GameDevices->GUIEnvironment->GetGUISkin();
	irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();
	irr::io::IFileSystem *file = GameDevices->Video->GetVideoDevice()->getFileSystem();
	#pragma endregion declaraciones

	// Creo el archivo scores.xml que contiene los puntajes guardados
	wchar_t Path[ __TORNADO_PATH_LENGTH ];
	if( GameDevices->Config->CreateFilenameProfilePath( Path , L"scores.xml" , EPL_SAVEDATA ) )
	{
		#if defined(_DEBUG)
		COutput::Wprintf(L"Ruta generada: %ls\n",Path);
		#endif
		Scoreboard.SetFilename( Path );
		if( Scoreboard.LoadScoreboard() )
		{
			#if defined(_DEBUG)
			COutput::Wprintf(L"Se terminaron de leer los datos de puntaje\n",Path);
			#endif
		}
	}

	// Creo el archivo trophies.xml que contiene los logros que se han ganado
	if( GameDevices->Config->CreateFilenameProfilePath( Path , L"trophies.xml" , EPL_SAVEDATA ) )
	{
		#if defined(_DEBUG)
		COutput::Wprintf(L"Ruta generada: %ls\n",Path);
		#endif
		TrophiesManager.SetFilename( Path );
		TrophiesManager.InitTrophies();
		if( TrophiesManager.LoadTrophies() )
		{
			#if defined(_DEBUG)
			COutput::Wprintf(L"Se terminaron de leer los datos de trofeos\n",Path);
			#endif
		}
	}

	// Asigno el estado del juego
	GameStatus = STATUS_INIT;

	// Cargo una Fuente
	Resources.Font.HUD = env->getFont(L"font/black28.xml");
	//Resources.Font.StageTitle = env->getFont(L"Media/titlelevel.xml");
	Resources.Font.StageTitle = env->getFont(L"font/orange36.xml");
	Resources.Font.ResultsTotalScore = env->getFont(L"font/orange36.xml");
	Resources.Font.NameEditBox = env->getFont(L"font/scoreName.xml");
	Resources.Font.Text = env->getFont(L"font/fontlucida.png");

	// Cargo los meshes
	Resources.Mesh.LughStand = smgr->getMesh("main/Lugh_full_horizontal01.obj");
	Resources.Mesh.Lugh = smgr->getMesh("main/ball_real.obj");
	Resources.Mesh.Crosshair = smgr->getMesh("main/cuadrado_3d.obj");

	// Las piezas
	Resources.Mesh.Bbox = smgr->getMesh("main/maceta_Zero.obj");
	Resources.Mesh.Maceta[0] = smgr->getMesh("main/maceta_IH.obj");
	Resources.Mesh.Maceta[1] = smgr->getMesh("main/maceta_IV.obj");
	Resources.Mesh.Maceta[2] = smgr->getMesh("main/maceta_X.obj");
	Resources.Mesh.Maceta[3] = smgr->getMesh("main/maceta_LD.obj");
	Resources.Mesh.Maceta[4] = smgr->getMesh("main/maceta_LU.obj");
	Resources.Mesh.Maceta[5] = smgr->getMesh("main/maceta_RD.obj");
	Resources.Mesh.Maceta[6] = smgr->getMesh("main/maceta_RU.obj");


	Resources.Mesh.Init = smgr->getMesh("main/Mesh_de_inicio.obj");
	Resources.Mesh.End = smgr->getMesh("main/llegada.obj");

	Resources.Mesh.BossInit = smgr->getMesh("main/salida.obj");
	Resources.Mesh.BossKey = smgr->getMesh("main/Key_01.obj");
	Resources.Mesh.BossJail = smgr->getMesh("main/Jaula_01.obj");
	Resources.Mesh.BossLughitos = smgr->getMesh("main/isopodos_capturados01.obj");

	Resources.Mesh.BordeEsquina = smgr->getMesh("main/bordeSeparacionEsquina01.obj");
	Resources.Mesh.BordePared = smgr->getMesh("main/bordeSeparacion01.obj");

	Resources.Texture.SkyBoxBackgroundImage[0] = driver->getTexture("bg/irrlicht2_up.jpg");
	Resources.Texture.SkyBoxBackgroundImage[1] = driver->getTexture("bg/irrlicht2_dn.jpg");
	Resources.Texture.SkyBoxBackgroundImage[2] = driver->getTexture("bg/irrlicht2_lf.jpg");
	Resources.Texture.SkyBoxBackgroundImage[3] = driver->getTexture("bg/irrlicht2_rt.jpg");
	Resources.Texture.SkyBoxBackgroundImage[4] = driver->getTexture("bg/irrlicht2_ft.jpg");
	Resources.Texture.SkyBoxBackgroundImage[5] = driver->getTexture("bg/irrlicht2_bk.jpg");

	Resources.Texture.LightBillboardImage = driver->getTexture("main/particlewhite.bmp");

	Resources.Texture.ScreenHUDImage = driver->getTexture("hud/main.png");
	Resources.Texture.ScoreHUDImage = driver->getTexture("hud/hud_1_score.png");

	Resources.Texture.LevelTitleBackgroundImage = driver->getTexture("hud/nivel_X_bg.png");
	Resources.Texture.BossLevelTitleImage = driver->getTexture("hud/salvar_isopodos.png");

	// Cargo las imagenes de victoria/derrota
	Resources.Texture.WinStatusImage = driver->getTexture("hud/nivel_completado.png");
	Resources.Texture.LoseStatusImage = driver->getTexture("hud/game_over_01.png");
	Resources.Texture.BossWinStatusImage = driver->getTexture("hud/nivel_extra_completado.png");
	Resources.Texture.BossLoseStatusImage = driver->getTexture("hud/game_over_01.png");

	Resources.Texture.ResultsTitleImage = driver->getTexture("hud/congrats.png");
	Resources.Texture.ResultsDescriptionImage = driver->getTexture("hud/imagescoretext.png");

	//driver->makeColorKeyTexture(Resources.Texture.WinStatusImage, irr::core::position2d<irr::s32>(0,0));
	//driver->makeColorKeyTexture(Resources.Texture.LoseStatusImage, irr::core::position2d<irr::s32>(0,0));

	Resources.Texture.BombIconNormalImage = driver->getTexture("hud/bomb_normal.png");
	Resources.Texture.BombIconHoverImage = driver->getTexture("hud/bomb_hover.png");
	Resources.Texture.BombIconPressedImage = driver->getTexture("hud/bomb_activate.png");
	Resources.Texture.BombIconPressedHoverImage = driver->getTexture("hud/bomb_activate_hover.png");

	Resources.Texture.ForwardIconNormalImage = driver->getTexture("hud/forwardnormal.png");
	Resources.Texture.ForwardIconHoverImage = driver->getTexture("hud/forwardpressed.png");
	Resources.Texture.ForwardIconPressedImage = driver->getTexture("hud/forwardpressed.png");
	//Resources.Texture.ForwardBackgroundImage = driver->getTexture("hud/forward.png");

	//Resources.Texture.CursorImage = driver->getTexture("Media/cursor_hand.png");
	Resources.Texture.ExtraBombImage = driver->getTexture("hud/bomba_extra.png");

	Resources.Texture.RecordTitleImage = driver->getTexture("hud/nuevo_puntaje_01.png");
	//Resources.Texture.RecordWriteYourNameImage = driver->getTexture("hud/title_recordname.png");

	Resources.Texture.RecordButtonSendNormalImage = driver->getTexture("hud/record_send.png");
	Resources.Texture.RecordButtonSendHoverImage = driver->getTexture("hud/record_send-hover.png");
	Resources.Texture.RecordButtonCancelNormalImage = driver->getTexture("hud/record_cancel.png");
	Resources.Texture.RecordButtonCancelHoverImage = driver->getTexture("hud/record_cancel-hover.png");

	
	Resources.Texture.MacetaActualImage[0] = driver->getTexture("hud/nexticon_0.png");
	Resources.Texture.MacetaActualImage[1] = driver->getTexture("hud/nexticon_1.png");
	Resources.Texture.MacetaActualImage[2] = driver->getTexture("hud/nexticon_2.png");
	Resources.Texture.MacetaActualImage[3] = driver->getTexture("hud/nexticon_3.png");
	Resources.Texture.MacetaActualImage[4] = driver->getTexture("hud/nexticon_4.png");
	Resources.Texture.MacetaActualImage[5] = driver->getTexture("hud/nexticon_5.png");
	Resources.Texture.MacetaActualImage[6] = driver->getTexture("hud/nexticon_6.png");
	

	Resources.Texture.MacetaNextImage[0] = Resources.Texture.MacetaActualImage[0];
	Resources.Texture.MacetaNextImage[1] = Resources.Texture.MacetaActualImage[1];
	Resources.Texture.MacetaNextImage[2] = Resources.Texture.MacetaActualImage[2];
	Resources.Texture.MacetaNextImage[3] = Resources.Texture.MacetaActualImage[3];
	Resources.Texture.MacetaNextImage[4] = Resources.Texture.MacetaActualImage[4];
	Resources.Texture.MacetaNextImage[5] = Resources.Texture.MacetaActualImage[5];
	Resources.Texture.MacetaNextImage[6] = Resources.Texture.MacetaActualImage[6];


	/*
	Resources.Texture.MacetaNextImage[0] = driver->getTexture("hud/nexticon_0.png");
	Resources.Texture.MacetaNextImage[1] = driver->getTexture("hud/nexticon_1.png");
	Resources.Texture.MacetaNextImage[2] = driver->getTexture("hud/nexticon_2.png");
	Resources.Texture.MacetaNextImage[3] = driver->getTexture("hud/nexticon_3.png");
	Resources.Texture.MacetaNextImage[4] = driver->getTexture("hud/nexticon_4.png");
	Resources.Texture.MacetaNextImage[5] = driver->getTexture("hud/nexticon_5.png");
	Resources.Texture.MacetaNextImage[6] = driver->getTexture("hud/nexticon_6.png");
	*/
	
	Resources.Texture.AchievementImage = driver->getTexture("hud/Boton_desbloqueados_normal.png");

	// Cargar las canciones
	Resources.Music.Normal = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("music/lugh.ogg") , true , audiere::FF_OGG );
	Resources.Music.Fast = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("music/lugh_fast.ogg") , true , audiere::FF_OGG );
	Resources.Music.GameOver = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("music/lugh_gameover.ogg") , true , audiere::FF_OGG );
	Resources.Music.Victory = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("music/lugh_youwin.ogg") , true , audiere::FF_OGG );
	Resources.Music.NewRecord = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("music/lugh_losenewrecord.ogg") , true , audiere::FF_OGG );
	Resources.Music.Boss = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("music/lugh_bosstheme.ogg") , true , audiere::FF_OGG );
	Resources.Music.BossDefeated = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("music/lugh_bossdefeaded.ogg") , true , audiere::FF_OGG );
	
	Resources.Sound.MacetaPut = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("sound/colocarbloquelisto.wav") , false , audiere::FF_WAV );
	Resources.Sound.BombExplosion = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("sound/impactobomba.wav") , false , audiere::FF_WAV );
	Resources.Sound.MenuHover = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("sound/mousesobreopcion.wav") , false , audiere::FF_WAV );
	Resources.Sound.MenuPressed = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("sound/opcionmenu.wav") , false , audiere::FF_WAV );
	Resources.Sound.ScoreDetail = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("sound/agarrarllave.wav") , false , audiere::FF_WAV );
	Resources.Sound.ScoreFinal = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("sound/ganasteunabomba.wav") , false , audiere::FF_WAV );
	Resources.Sound.Achievement = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("sound/sonidopuntajes.wav") , false , audiere::FF_WAV );

	Nodes.HUD.VictoryStatusPosition = irr::core::vector2d<irr::s32>( Width/2-218 , Height/2-77 );
	Nodes.HUD.GameOverStatusPosition = irr::core::vector2d<irr::s32>( Width/2-330 , Height/2-100 );
	Nodes.HUD.BossVictoryStatusPosition = irr::core::vector2d<irr::s32>( Width/2-232 , Height/2-73 );
	Nodes.HUD.BossGameOverStatusPosition = irr::core::vector2d<irr::s32>( Width/2-330 , Height/2-100 );
	Nodes.HUD.ResultsTitlePosition = irr::core::vector2d<irr::s32>( Width-370 , Height/2-270 );
	Nodes.HUD.ResultsDescriptionPosition = irr::core::vector2d<irr::s32>( Width-360 , Height/2-145 );
	
	Nodes.HUD.StageTitleTextPosition = irr::core::rect<irr::s32>( Width/2-210 , Height/2-160 , Width/2+210 , Height/2-96 );
	Nodes.HUD.ClockTextPosition = irr::core::rect<irr::s32>(10,100,150,150);//(10,0,150,50);
	Nodes.HUD.ScoreTextPosition = irr::core::rect<irr::s32>(80,45,225,95);//(Width-145,0,Width-5,50);
	Nodes.HUD.BombsTextPosition = irr::core::rect<irr::s32>(63,547,138,600);//(Width-70,Height-50,Width,Height);

	Nodes.HUD.ScreenHUDPosition = irr::core::vector2d<irr::s32>(0,0);
	Nodes.HUD.ScoreHUDPosition = irr::core::vector2d<irr::s32>(0,0);
	Nodes.HUD.LevelTitleBackgroundPosition = irr::core::vector2d<irr::s32>( Width/2-256 , Height/2-256 );
	Nodes.HUD.BossLevelTitlePosition = irr::core::vector2d<irr::s32>( Width/2-285 , Height/2-192 );
	Nodes.HUD.BombsIconPosition = irr::core::vector2d<irr::s32>(5,535);//(Width-128,Height-64);
	Nodes.HUD.ForwardIconPosition = irr::core::vector2d<irr::s32>(Width-162,Height-51);
	//Nodes.HUD.ForwardBackgroundPosition = irr::core::vector2d<irr::s32>(Width-45,Height-45);

	Nodes.HUD.RecordTitlePosition = irr::core::vector2d<irr::s32>( Width/2-272 , Height/2-105 );
	//Nodes.HUD.RecordWriteYourNamePosition = irr::core::vector2d<irr::s32>( Width/2-256 , Height/2-50 );
	Nodes.HUD.RecordButtonSendPosition = irr::core::vector2d<irr::s32>( Width/2-256 , Height/2+100 );
	Nodes.HUD.RecordButtonCancelPosition = irr::core::vector2d<irr::s32>( Width/2+64 , Height/2+100 );
	Nodes.HUD.RecordNameEditBoxPosition = irr::core::rect<irr::s32>( Width/2-175 , Height/2 , Width/2+175 , Height/2+40 );


	Nodes.HUD.MacetaActualPosition = irr::core::vector2d<irr::s32>(2,360);
	Nodes.HUD.MacetaNextPosition = irr::core::vector2d<irr::s32>(2,208);
	Nodes.HUD.ExtraBombPosition = irr::core::vector2d<irr::s32>(Width-280,Height-60);

	Nodes.HUD.AchievementPosition = irr::core::vector2d<irr::s32>( Width-256 , Height-64 );

	// La escena mejor se carga al final
	//Resources.Mesh.Scene = smgr->getMesh("main/world_1.obj");


	Variables.Matrix.Cols = 10;
	Variables.Matrix.Rows = 8;

	Variables.Global.LevelsPerBoss = 4;
	Variables.Global.KeyHeight = 3.0f;
	Variables.Global.BallHeight = 1.0f;
	Variables.Global.CrosshairHeight = -3.0f;
	Variables.Global.InitBallSpeed = 1500;
	Variables.Global.InitBallRotationSpeed = 1.0f;
	Variables.Global.KeyRotationSpeed = 0.5f;
	Variables.Global.FactorSpeedInc = 0.90f;
	

	Variables.Score.FactorLevelScore = 0.5f;
	Variables.Score.FactorBossScore = 1.0f;

	Variables.Score.FactorPasses = 10;
	Variables.Score.FactorUnpasses = 20;
	Variables.Score.FactorBonusTime = 5;
	Variables.Score.FactorBonusBombs = 10;

	Variables.Score.BossFactorPasses = 20;
	Variables.Score.BossFactorUnpasses = 10;
	Variables.Score.BonusBossDefeated = 500;
	Variables.Score.MaxUnpassesBlocks = 10;
	

	Variables.Random.NroMeshes = 7;
	Variables.Random.RandomProbability = 60;

	return true;
}


void BallsContextMain::Prepare(void)
{
	irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
	irr::gui::IGUISkin *skin = GameDevices->GUIEnvironment->GetGUISkin();
	irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();
	audiere::AudioDevicePtr audio = GameDevices->Audio->GetAudioDevice();

	XEffects::EffectHandler *effect = GameDevices->Effects->GetEffects();

	smgr->loadScene("main/world_02.irr");
	//GameDevices->Video->SetCursorVisibility(false);



	// Creo las camaras
	//CameraPosition = irr::core::vector3df(55.0f,65.0f,45.0f);
	//CameraTarget = irr::core::vector3df(41.0f,0.0f,45.0f);
	Nodes.Camera.FPS = smgr->addCameraSceneNodeFPS(0,50.0f,0.03f);
	Nodes.Camera.Node = smgr->addCameraSceneNode();


	Nodes.Camera.Position = irr::core::vector3df(51.354607f,82.607285f,33.886436f);
	Nodes.Camera.Target = irr::core::vector3df(29.646530f,-18.081810f,34.004349f);

	Nodes.Camera.Node->setPosition( Nodes.Camera.Position );
	Nodes.Camera.Node->setTarget( Nodes.Camera.Target );
	Nodes.Camera.FPS->setPosition( Nodes.Camera.Position );
	Nodes.Camera.FPS->setTarget( Nodes.Camera.Target );

	if( Resources.Font.NameEditBox )
	{
		skin->setFont( Resources.Font.NameEditBox );
	}

	//cam->setName("camara");

	// Creo el skybox
	smgr->addSkyBoxSceneNode(	Resources.Texture.SkyBoxBackgroundImage[0],
								Resources.Texture.SkyBoxBackgroundImage[1],
								Resources.Texture.SkyBoxBackgroundImage[2],
								Resources.Texture.SkyBoxBackgroundImage[3],
								Resources.Texture.SkyBoxBackgroundImage[4],
								Resources.Texture.SkyBoxBackgroundImage[5] );


	//Nodes.Board.Scene = smgr->addMeshSceneNode( Resources.Mesh.Scene );
	//Nodes.Board.Scene->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	//Nodes.Board.Scene->setPosition( irr::core::vector3df(35.0f,0.0f,45.0f) );
	//Nodes.Board.Scene->setRotation( irr::core::vector3df(0.0f,90.0f,0.0f) );

	#if defined(DEBUG_MODE)
	DebugNode = Nodes.Board.Scene;
	#endif

	//GameDevices->Video->SetCursorVisibility(false);
	irr::scene::IAnimatedMeshSceneNode* node = 0;
	irr::scene::ISceneNode* light = 0;

	effect->setAmbientColor(irr::video::SColor(0xFF, 0xFF, 0xFF, 0xFF));
	effect->setClearColour(irr::video::SColor(0xFFFFFF));
	/*effect->addShadowLight(	XEffects::SShadowLight(
								1,
								512,
								irr::core::vector3df(0, 0, 0),
								irr::core::vector3df(112.29f,0.0f,27.8f),
								irr::video::SColor(0, 0xFF, 0xFF, 0xFF),
								10.0f,
								100.0f,
								90.0f * irr::core::DEGTORAD));*/

	// Creo la luz que gira
	/*light = smgr->addLightSceneNode(0, irr::core::vector3df(0,0,0),
		irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 800.0f);*/

	/*Nodes.Lights.TestLight = smgr->addEmptySceneNode(0);
	irr::scene::ISceneNodeAnimator* anim = 0;
	anim = smgr->createFlyCircleAnimator(irr::core::vector3df(57.9f,44.0f,6.85f),0.0f);
	Nodes.Lights.TestLight->addAnimator(anim);
	anim->drop();*/


	// Creo un billboard para saber la posicion de la luz
	/*light = smgr->addBillboardSceneNode(Nodes.Lights.TestLight, irr::core::dimension2d<irr::f32>(50, 50));
	light->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	light->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	light->setMaterialTexture(0, Resources.Texture.LightBillboardImage);*/

	// Solo para sombras stencil
	//smgr->setShadowColor(irr::video::SColor(0xFF,0x00,0x00,0x00));

	#if defined(_DEBUG)
	COutput::Wprintf(L"Velocidad de la Pelota: %d\n",BallSpeed);
	COutput::Wprintf(L"Velocidad de Rotación de la Pelota: %f\n",BallRotationSpeed);
	#endif

	// A generar la posicion del inicio y fin
	uint16 initBlockDirection,endDir,jailDir;
	irr::core::vector2di init,end,jail;

	uint16 columns_less1 = Variables.Matrix.Cols - 1;
	uint16 rows_less1 = Variables.Matrix.Rows - 1;
	uint16 probabilidad = CSystem::Random() % 101;
	uint16 rdir = CSystem::Random() % 4;
	uint16 rcol = CSystem::Random() % columns_less1 + 1;	// numero entre 1 .. cols-1
	uint16 rrow = CSystem::Random() % rows_less1 + 1;	// numero entre 1 .. rows-1
	bool tooClose = false;

	if( !IsBossTime )
	{
		#if defined(_DEBUG)
		COutput::Wprintf(L"[Random Init] prob=%d rcol=%d rrow=%d\n",probabilidad,rcol,rrow);
		#endif

		if( probabilidad <= 25 )
		{	
			init = irr::core::vector2di(-1,rrow);
			initBlockDirection = BMD_RIGHT;
			#if defined(_DEBUG)
			COutput::Wprintf(L"[Random Init] dir=RIGHT\n");
			#endif
		}
		else if( probabilidad <= 50 )
		{
			init = irr::core::vector2di(Variables.Matrix.Cols,rrow);
			initBlockDirection = BMD_LEFT;
			#if defined(_DEBUG)
			COutput::Wprintf(L"[Random Init] dir=LEFT\n");
			#endif
		}
		else if( probabilidad <= 75 )
		{
			init = irr::core::vector2di(rcol,-1);
			initBlockDirection = BMD_DOWN;
			#if defined(_DEBUG)
			COutput::Wprintf(L"[Random Init] dir=DOWN\n");
			#endif
		}
		else
		{
			init = irr::core::vector2di(rcol,Variables.Matrix.Rows);
			initBlockDirection = BMD_UP;
			#if defined(_DEBUG)
			COutput::Wprintf(L"[Random Init] dir=UP\n");
			#endif
		}

		do
		{
			tooClose = false;
			rdir = CSystem::Random() % 4;
			probabilidad = CSystem::Random() % 101;
			rcol = CSystem::Random() % columns_less1 + 1;
			rrow = CSystem::Random() % rows_less1 + 1;

			#if defined(_DEBUG)
			COutput::Wprintf(L"[Random End] prob=%d rcol=%d rrow=%d\n",probabilidad,rcol,rrow);
			#endif

			if( probabilidad <= 25 )
			{	
				end = irr::core::vector2di(-1,rrow);
				endDir = BMD_RIGHT;	
				#if defined(_DEBUG)
				COutput::Wprintf(L"[Random End] dir=RIGHT\n");
				#endif
			}
			else if( probabilidad <= 50 )
			{
				end = irr::core::vector2di(Variables.Matrix.Cols,rrow);
				endDir = BMD_LEFT;	
				#if defined(_DEBUG)
				COutput::Wprintf(L"[Random End] dir=LEFT\n");
				#endif
			}
			else if( probabilidad <= 75 )
			{
				end = irr::core::vector2di(rcol,-1);
				endDir = BMD_DOWN;
				#if defined(_DEBUG)
				COutput::Wprintf(L"[Random End] dir=DOWN\n");
				#endif
			}
			else
			{
				end = irr::core::vector2di(rcol,Variables.Matrix.Rows);
				endDir = BMD_UP;
				#if defined(_DEBUG)
				COutput::Wprintf(L"[Random End] dir=UP\n");
				#endif
			}

			if( abs(init.X - end.X) < 2 || abs(init.Y - end.Y) < 2 )
			{	
				tooClose = true;	
				#if defined(_DEBUG)
				COutput::Wprintf(L"Nodos muy juntos: (%d,%d) (%d,%d)\n",init.X,init.Y,end.X,end.Y);
				#endif
			}

		} while( init == end || tooClose );
	}

	// Modo Jefe
	else
	{
		bool surrounded;

		do {
			surrounded = false;

			columns_less1 = Variables.Matrix.Cols;
			rows_less1 = Variables.Matrix.Rows;
			probabilidad = CSystem::Random() % 101;
			rdir = CSystem::Random() % 4;
			rcol = CSystem::Random() % columns_less1;	// numero entre 0 .. cols-1
			rrow = CSystem::Random() % rows_less1;	// numero entre 0 .. rows-1

			#if defined(_DEBUG)
			COutput::Wprintf(L"[Random Init] prob=%d rcol=%d rrow=%d\n",probabilidad,rcol,rrow);
			#endif

			init = irr::core::vector2di(rcol,rrow);

			if( probabilidad <= 25 ){		initBlockDirection = BMD_RIGHT;}
			else if( probabilidad <= 50 ){	initBlockDirection = BMD_LEFT;}
			else if( probabilidad <= 75 ){	initBlockDirection = BMD_DOWN;}
			else {					initBlockDirection = BMD_UP;}

			#if defined(_DEBUG)
			switch( initBlockDirection )
			{
				case BMD_RIGHT:{COutput::Wprintf(L"[Random Init] dir=RIGHT\n");break;}
				case BMD_LEFT:{COutput::Wprintf(L"[Random Init] dir=LEFT\n");break;}
				case BMD_DOWN:{COutput::Wprintf(L"[Random Init] dir=DOWN\n");break;}
				case BMD_UP:{COutput::Wprintf(L"[Random Init] dir=UP\n");break;} 
			}
			#endif

			if( (initBlockDirection == BMD_RIGHT && init.X == columns_less1-1)
			 || (initBlockDirection == BMD_LEFT && init.X == 0 )
			 || (initBlockDirection == BMD_DOWN && init.Y == rows_less1-1)
			 || (initBlockDirection == BMD_UP && init.Y == 0 ) )
			{
				surrounded = true;
				#if defined(_DEBUG)
				COutput::Wprintf(L"Nodo encerrado: (%d,%d) [%d]\n",init.X,init.Y,initBlockDirection);
				#endif
			}

		}
		while( surrounded );

		do
		{
			surrounded = false;
			tooClose = false;
			rdir = CSystem::Random() % 4;
			probabilidad = CSystem::Random() % 101;
			rcol = CSystem::Random() % columns_less1;
			rrow = CSystem::Random() % rows_less1;
			
			#if defined(_DEBUG)
			COutput::Wprintf(L"[Random End] prob=%d rcol=%d rrow=%d\n",probabilidad,rcol,rrow);
			#endif

			end = irr::core::vector2di(rcol,rrow);

			if( probabilidad <= 25 ){		endDir = BMD_RIGHT;}
			else if( probabilidad <= 50 ){	endDir = BMD_LEFT;}
			else if( probabilidad <= 75 ){	endDir = BMD_DOWN;}
			else{					endDir = BMD_UP;}

			#if defined(_DEBUG)
			switch( endDir )
			{
				case BMD_RIGHT:{COutput::Wprintf(L"[Random End] dir=RIGHT\n");break;}
				case BMD_LEFT:{COutput::Wprintf(L"[Random End] dir=LEFT\n");break;}
				case BMD_DOWN:{COutput::Wprintf(L"[Random End] dir=DOWN\n");break;}
				case BMD_UP:{COutput::Wprintf(L"[Random End] dir=UP\n");break;} 
			}
			#endif

			if( abs(init.X - end.X) + abs(init.Y - end.Y) < 4 )
			{
				tooClose = true;
				#if defined(_DEBUG)
				COutput::Wprintf(L"Nodos muy juntos: (%d,%d) (%d,%d)\n",init.X,init.Y,end.X,end.Y);
				#endif
			}

			if( (endDir == BMD_RIGHT && end.X == columns_less1-1)
			 || (endDir == BMD_LEFT && end.X == 0 )
			 || (endDir == BMD_DOWN && end.Y == rows_less1-1)
			 || (endDir == BMD_UP && end.Y == 0 ) )
			{
				surrounded = true;
				#if defined(_DEBUG)
				COutput::Wprintf(L"Nodo encerrado: (%d,%d) [%d]\n",end.X,end.Y,endDir);
				#endif
			}

		} while( init == end || tooClose || surrounded );

		do
		{
			rdir = CSystem::Random() % 4;
			probabilidad = CSystem::Random() % 101;
			rcol = CSystem::Random() % columns_less1;
			rrow = CSystem::Random() % rows_less1;
			
			#if defined(_DEBUG)
			COutput::Wprintf(L"[Random Jail] prob=%d rcol=%d rrow=%d\n",probabilidad,rcol,rrow);
			#endif

			jail = irr::core::vector2di(rcol,rrow);

			if( probabilidad <= 25 ){		jailDir = BMD_RIGHT;}
			else if( probabilidad <= 50 ){	jailDir = BMD_LEFT;}
			else if( probabilidad <= 75 ){	jailDir = BMD_DOWN;}
			else{					jailDir = BMD_UP;}

			#if defined(_DEBUG)
			switch( jailDir )
			{
				case BMD_RIGHT:{COutput::Wprintf(L"[Random Jail] dir=RIGHT\n");break;}
				case BMD_LEFT:{COutput::Wprintf(L"[Random Jail] dir=LEFT\n");break;}
				case BMD_DOWN:{COutput::Wprintf(L"[Random Jail] dir=DOWN\n");break;}
				case BMD_UP:{COutput::Wprintf(L"[Random Jail] dir=UP\n");break;} 
			}
			#endif

		} while( jail == init || jail == end );
	}

	Nodes.Board.Crosshair = smgr->addMeshSceneNode( Resources.Mesh.Crosshair );
	Nodes.Board.Crosshair->setVisible(false);
	Nodes.Board.Crosshair->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	//Nodes.Board.Crosshair->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);

	Nodes.Board.Parent = smgr->addEmptySceneNode();

	// Creo el nodo de la pelota
	if ( (Nodes.Board.Lugh = smgr->addAnimatedMeshSceneNode( Resources.Mesh.Lugh , Nodes.Board.Parent ))!=NULL )
	{
		irr::core::vector3df rot;

		Nodes.Board.Lugh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		//Nodes.Board.Lugh->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);

		//BallSceneNode->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);  //this is important to use
		Nodes.Board.Parent->setPosition( irr::core::vector3df( init.Y * 10.0f , Variables.Global.BallHeight , init.X * 10.f));
		
		switch( initBlockDirection )
		{
			case BMD_RIGHT:{rot=irr::core::vector3df(0.0f,-90.0f,0.0f);break;}
			case BMD_LEFT:{rot=irr::core::vector3df(0.0f,90.0f,0.0f);break;}
			//case BMD_DOWN:{rot=irr::core::vector3df(0.0f,0.0f,0.0f);break;}
			case BMD_UP:{rot=irr::core::vector3df(0.0f,180.0f,0.0f);break;}
		}
		Nodes.Board.Parent->setRotation( rot );
		//BallSceneNode->addShadowVolumeSceneNode();

		//effect->addShadowToNode(Nodes.Board.Lugh);
	}

	// Creo el nodo de Lugh de Pie
	if ( (Nodes.Board.LughStand = smgr->addAnimatedMeshSceneNode( Resources.Mesh.LughStand , Nodes.Board.Parent ))!=NULL )
	{
		Nodes.Board.LughStand->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		Nodes.Board.LughStand->setScale(irr::core::vector3df(0.05f,0.05f,0.05f));
		//Nodes.Board.Lugh->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);
		Nodes.Board.LughStand->setVisible(false);

		//effect->addShadowToNode(Nodes.Board.LughStand);
	}

	irr::scene::IAnimatedMesh *InitMesh = IsBossTime ? Resources.Mesh.BossInit : Resources.Mesh.Init;
	irr::scene::IAnimatedMesh *EndMesh = IsBossTime ? Resources.Mesh.BossKey : Resources.Mesh.End;

	// Creo el nodo de Inicio
	if( (node = smgr->addAnimatedMeshSceneNode( InitMesh ))!=NULL )
	{
		switch( initBlockDirection )
		{
			case BMD_RIGHT:{node->setRotation(irr::core::vector3df(0.0f,180.0f,0.0f));break;}
			//case BMD_LEFT:{node->setRotation(irr::core::vector3df(0.0f,0.0f,0.0f));break;}
			case BMD_DOWN:{node->setRotation(irr::core::vector3df(0.0f,-90.0f,0.0f));break;}
			case BMD_UP:{node->setRotation(irr::core::vector3df(0.0f,90.0f,0.0f));break;}
		}

		Matrix.SetStartPosition( irr::core::vector3df( init.Y * 10.0f , Variables.Global.BallHeight ,  init.X * 10.f) );
		node->setPosition( irr::core::vector3df( init.Y * 10.0f , 0.0f , init.X * 10.f) );
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		//node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);
		//node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
		//node->addShadowVolumeSceneNode();

		//effect->addShadowToNode(node);

		node = NULL;

		Nodes.Board.AnimationInitTargetPoint = irr::core::vector3df( init.Y * 10.0f , Variables.Global.BallHeight ,  init.X * 10.f);
	}
	
	// Creo el nodo de Fin
	if( (node = smgr->addAnimatedMeshSceneNode( EndMesh ))!=NULL )
	{
		switch( endDir )
		{
			case BMD_RIGHT:{node->setRotation(irr::core::vector3df(0.0f,180.0f,0.0f));break;}
			//case BMD_LEFT:{node->setRotation(irr::core::vector3df(0.0f,0.0f,0.0f));break;}
			case BMD_DOWN:{node->setRotation(irr::core::vector3df(0.0f,-90.0f,0.0f));break;}
			case BMD_UP:{node->setRotation(irr::core::vector3df(0.0f,90.0f,0.0f));break;}
		}

		real height = IsBossTime ? Variables.Global.KeyHeight : 0.0f ;

		Matrix.SetFinishPosition( irr::core::vector3df( end.Y * 10.0f , Variables.Global.BallHeight ,  end.X * 10.f) );
		node->setPosition( irr::core::vector3df( end.Y * 10.0f , height ,  end.X * 10.f) );
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		//node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);
		//node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
		//node->addShadowVolumeSceneNode();

		//effect->addShadowToNode(node);

		if( IsBossTime )
		{
			Nodes.Board.Key = node;

			irr::scene::ISceneNodeAnimator *anim = smgr->createRotationAnimator( irr::core::vector3df(0.0f,Variables.Global.KeyRotationSpeed,0.0f) );
			if( anim )
			{
				node->addAnimator( anim );
			}
		}
		node = NULL;
	}

	if( IsBossTime )
	{
		if( (node = smgr->addAnimatedMeshSceneNode( Resources.Mesh.BossJail ))!=NULL )
		{
			switch( jailDir )
			{
				case BMD_RIGHT:{node->setRotation(irr::core::vector3df(0.0f,180.0f,0.0f));break;}
				//case BMD_LEFT:{node->setRotation(irr::core::vector3df(0.0f,0.0f,0.0f));break;}
				case BMD_DOWN:{node->setRotation(irr::core::vector3df(0.0f,-90.0f,0.0f));break;}
				case BMD_UP:{node->setRotation(irr::core::vector3df(0.0f,90.0f,0.0f));break;}
			}

			node->setPosition( irr::core::vector3df( jail.Y * 10.0f , 0.0f ,  jail.X * 10.f) );
			node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			//node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);
			//node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
			//node->addShadowVolumeSceneNode();

			//effect->addShadowToNode(node);
			Nodes.Board.Jail = node;

			node = NULL;
		}

		if( (node = smgr->addAnimatedMeshSceneNode( Resources.Mesh.BossLughitos ))!=NULL )
		{
			switch( jailDir )
			{
				case BMD_RIGHT:{node->setRotation(irr::core::vector3df(0.0f,180.0f,0.0f));break;}
				//case BMD_LEFT:{node->setRotation(irr::core::vector3df(0.0f,0.0f,0.0f));break;}
				case BMD_DOWN:{node->setRotation(irr::core::vector3df(0.0f,-90.0f,0.0f));break;}
				case BMD_UP:{node->setRotation(irr::core::vector3df(0.0f,90.0f,0.0f));break;}
			}

			node->setPosition( irr::core::vector3df( jail.Y * 10.0f , 0.0f ,  jail.X * 10.f) );
			node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			//node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);
			//node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
			//node->addShadowVolumeSceneNode();

			//effect->addShadowToNode(node);

			node = NULL;
		}

		Nodes.Board.AnimationInitTargetPoint = irr::core::vector3df( jail.Y * 10.0f , Variables.Global.BallHeight ,  jail.X * 10.f);
	}

	Nodes.Board.AnimationTargetNode = smgr->addEmptySceneNode();
	Nodes.Board.AnimationTargetNode->setPosition( Nodes.Board.AnimationInitTargetPoint );

	// Inicializar la Matriz del Tablero
	Matrix.Init( Variables.Matrix.Cols , Variables.Matrix.Rows , init , end , initBlockDirection , endDir , Nodes.Board.Parent->getRotation() , Variables.Global.BallHeight , IsBossTime );


	if( (node = smgr->addAnimatedMeshSceneNode( Resources.Mesh.BordeEsquina ))!=NULL )
	{
		node->setPosition(irr::core::vector3df( -10.0f , 0.0f, -10.0f));
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		//node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);
		node->setRotation(irr::core::vector3df(0.0f,-90.0f,0.0f));
		//effect->addShadowToNode(node);
	}
	if( (node = smgr->addAnimatedMeshSceneNode( Resources.Mesh.BordeEsquina ))!=NULL )
	{
		node->setPosition(irr::core::vector3df( (irr::f32)Variables.Matrix.Rows*10.0f , 0.0f, -10.0f));
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		//node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);
		node->setRotation(irr::core::vector3df(0.0f,180.0f,0.0f));
		//effect->addShadowToNode(node);
	}
	if( (node = smgr->addAnimatedMeshSceneNode( Resources.Mesh.BordeEsquina ))!=NULL )
	{
		node->setPosition(irr::core::vector3df( -10.0f , 0.0f, (irr::f32)Variables.Matrix.Cols*10.0f ));
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		//node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);
		//node->setRotation(irr::core::vector3df(0.0f,0.0f,0.0f));
		//effect->addShadowToNode(node);
	}
	if( (node = smgr->addAnimatedMeshSceneNode( Resources.Mesh.BordeEsquina ))!=NULL )
	{
		node->setPosition(irr::core::vector3df( (irr::f32)Variables.Matrix.Rows*10.0f , 0.0f, (irr::f32)Variables.Matrix.Cols*10.0f ));
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		//node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);
		node->setRotation(irr::core::vector3df(0.0f,90.0f,0.0f));
		//effect->addShadowToNode(node);
	}

	for(uint16 y=0 ; y<Variables.Matrix.Rows ; y++ )
	{
		if( ( (init != irr::core::vector2di(-1,y)) && (end != irr::core::vector2di(-1,y)) || IsBossTime ) &&
			( node = smgr->addAnimatedMeshSceneNode( Resources.Mesh.BordePared ) )!=NULL )
		{
			node->setPosition(irr::core::vector3df( (irr::f32)y*10.0f , 0.0f, -10.0f ));
			node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			//node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);
			node->setRotation(irr::core::vector3df(0.0f,90.0f,0.0f));
			//effect->addShadowToNode(node);
		}

		if( ( (init != irr::core::vector2di(Variables.Matrix.Cols,y)) && (end != irr::core::vector2di(Variables.Matrix.Cols,y) ) || IsBossTime ) &&
			( node = smgr->addAnimatedMeshSceneNode( Resources.Mesh.BordePared ))!=NULL )
		{
			node->setPosition(irr::core::vector3df( (irr::f32)y*10.0f , 0.0f, (irr::f32)Variables.Matrix.Cols*10.0f ));
			node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			//node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);
			node->setRotation(irr::core::vector3df(0.0f,-90.0f,0.0f));
			//effect->addShadowToNode(node);
		}
	}

	for(uint16 x=0 ; x<Variables.Matrix.Cols ; x++)
	{
		if( ( (init != irr::core::vector2di(x,-1)) && (end != irr::core::vector2di(x,-1)) || IsBossTime ) &&
			(node = smgr->addAnimatedMeshSceneNode( Resources.Mesh.BordePared ))!=NULL )
		{
			node->setPosition(irr::core::vector3df( -10.0f , 0.0f, (irr::f32)x*10.0f ));
			node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			//node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);
			node->setRotation(irr::core::vector3df(0.0f,180.0f,0.0f));
			//effect->addShadowToNode(node);
		}
		if( ( (init != irr::core::vector2di(x,Variables.Matrix.Rows)) && (end != irr::core::vector2di(x,Variables.Matrix.Rows)) || IsBossTime ) &&
			(node = smgr->addAnimatedMeshSceneNode( Resources.Mesh.BordePared ))!=NULL )
		{
			node->setPosition(irr::core::vector3df( (irr::f32)Variables.Matrix.Rows*10.0f , 0.0f, (irr::f32)x*10.0f ));
			node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			//node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);
			//node->setRotation(irr::core::vector3df(0.0f,180.0f,0.0f));
			//effect->addShadowToNode(node);
		}
	}

	// Creo el tablero (x,y) -> (y,0,x)
	for(uint16 y=0 ; y<Variables.Matrix.Rows ; y++)
	{
		for(uint16 x=0 ; x<Variables.Matrix.Cols ; x++)
		{
			// Creo el nodo para la posicion X,Y
			if( ( !IsBossTime || ( (init.X != x || init.Y != y) && (jail.X != x || jail.Y != y) ) )
			 && ( node = smgr->addAnimatedMeshSceneNode( Resources.Mesh.Bbox ))!=NULL )
			{
				wchar_t name[32];

				//node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);  //this is important to use
				node->setPosition(irr::core::vector3df((irr::f32)y*10.0f,0.0f,(irr::f32)x*10.0f));
				Matrix.SetPosition( x , y , node->getPosition() + irr::core::vector3df(0.0f,Variables.Global.BallHeight,0.0f) );
				node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				//node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);
				//node->setMaterialFlag(irr::video::EMF_WIREFRAME,true);
		
				COutput::Wsprintf(name,L"%d",y*Variables.Matrix.Cols+x+1);
				//COutput::Wprintf(L"name='%ls'\n",name);
				node->setName(name);
				//GameDevices->Video->SetAlpha(0x33,node->getMaterial(0).getTexture(0));
				//node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);

				//irr::s32 flags = node->getID();
				//flags = BALL_EMPTYBLOCK | flags;
				node->setID( BALL_EMPTYBLOCK );

				irr::scene::ITriangleSelector *selector;
				selector = smgr->createTriangleSelector( Resources.Mesh.Bbox,node); 
				node->setTriangleSelector(selector);
				//effect->addShadowToNode(node);
				selector->drop();
			}
		}
	}

	Nodes.HUD.ScreenHUD = env->addImage( Resources.Texture.ScreenHUDImage , Nodes.HUD.ScreenHUDPosition , true , 0 );
	Nodes.HUD.ScreenHUD->setVisible( false );

	Nodes.HUD.ScoreHUD = env->addImage( Resources.Texture.ScoreHUDImage , Nodes.HUD.ScoreHUDPosition , true , 0 );
	Nodes.HUD.ScoreHUD->setVisible( false );

	Nodes.HUD.LevelTitleBackground = env->addImage( Resources.Texture.LevelTitleBackgroundImage , Nodes.HUD.LevelTitleBackgroundPosition , true , 0 );
	Nodes.HUD.LevelTitleBackground->setVisible( false );
	Nodes.HUD.BossLevelTitle = env->addImage( Resources.Texture.BossLevelTitleImage , Nodes.HUD.BossLevelTitlePosition , true , 0 );
	Nodes.HUD.BossLevelTitle->setVisible( false );

	Nodes.HUD.BombIconNormal = env->addImage( Resources.Texture.BombIconNormalImage , Nodes.HUD.BombsIconPosition , true , 0 , BGC_BOMBNORMAL );
	Nodes.HUD.BombIconHover = env->addImage( Resources.Texture.BombIconHoverImage , Nodes.HUD.BombsIconPosition , true , 0 , BGC_BOMBHOVER );
	Nodes.HUD.BombIconPressed = env->addImage( Resources.Texture.BombIconPressedImage , Nodes.HUD.BombsIconPosition , true , 0 , BGC_BOMBPRESSED );
	Nodes.HUD.BombIconPressedHover = env->addImage( Resources.Texture.BombIconPressedHoverImage , Nodes.HUD.BombsIconPosition , true , 0 , BGC_BOMBPRESSEDHOVER );
	Nodes.HUD.BombIconNormal->setVisible( false );
	Nodes.HUD.BombIconHover->setVisible( false );
	Nodes.HUD.BombIconPressed->setVisible( false );
	Nodes.HUD.BombIconPressedHover->setVisible( false );

	//Nodes.HUD.ForwardBackground = env->addImage( Resources.Texture.ForwardBackgroundImage , Nodes.HUD.ForwardBackgroundPosition );
	//Nodes.HUD.ForwardBackground->setVisible( false );

	Nodes.HUD.ForwardIconNormal = env->addImage( Resources.Texture.ForwardIconNormalImage , Nodes.HUD.ForwardIconPosition , true , 0 , BGC_FORWARDNORMAL );
	Nodes.HUD.ForwardIconHover = env->addImage( Resources.Texture.ForwardIconHoverImage , Nodes.HUD.ForwardIconPosition , true , 0 , BGC_FORWARDHOVER );
	Nodes.HUD.ForwardIconPressed = env->addImage( Resources.Texture.ForwardIconPressedImage , Nodes.HUD.ForwardIconPosition , true , 0 , BGC_FORWARDPRESSED );
	Nodes.HUD.ForwardIconNormal->setVisible( false );
	Nodes.HUD.ForwardIconHover->setVisible( false );
	Nodes.HUD.ForwardIconPressed->setVisible( false );

	if( !IsBossTime )
	{
		Nodes.HUD.WinStatus = env->addImage( Resources.Texture.WinStatusImage , Nodes.HUD.VictoryStatusPosition );
		Nodes.HUD.LoseStatus = env->addImage( Resources.Texture.LoseStatusImage , Nodes.HUD.GameOverStatusPosition );
	}
	else
	{
		Nodes.HUD.WinStatus = env->addImage( Resources.Texture.BossWinStatusImage , Nodes.HUD.BossVictoryStatusPosition );
		Nodes.HUD.LoseStatus = env->addImage( Resources.Texture.BossLoseStatusImage , Nodes.HUD.BossGameOverStatusPosition );
	}

	Nodes.HUD.ResultsDescription = env->addImage( Resources.Texture.ResultsDescriptionImage , Nodes.HUD.ResultsDescriptionPosition );
	Nodes.HUD.ResultsTitle = env->addImage( Resources.Texture.ResultsTitleImage , Nodes.HUD.ResultsTitlePosition );
	
	Nodes.HUD.WinStatus->setVisible( false );
	Nodes.HUD.LoseStatus->setVisible( false );
	Nodes.HUD.ResultsDescription->setVisible( false );
	Nodes.HUD.ResultsTitle->setVisible( false );

	Nodes.HUD.ExtraBomb = env->addImage( Resources.Texture.ExtraBombImage , Nodes.HUD.ExtraBombPosition );
	Nodes.HUD.ExtraBomb->setVisible( false );
	
	Nodes.HUD.RecordTitle = env->addImage( Resources.Texture.RecordTitleImage , Nodes.HUD.RecordTitlePosition );
	//Nodes.HUD.RecordWriteYourName = env->addImage( Resources.Texture.RecordWriteYourNameImage , Nodes.HUD.RecordWriteYourNamePosition );
	Nodes.HUD.RecordTitle->setVisible( false );
	//Nodes.HUD.RecordWriteYourName->setVisible( false );


	Nodes.HUD.RecordButtonSendNormal = env->addImage( Resources.Texture.RecordButtonSendNormalImage , Nodes.HUD.RecordButtonSendPosition , true , 0 , BGC_SENDNORMAL );
	Nodes.HUD.RecordButtonSendHover = env->addImage( Resources.Texture.RecordButtonSendHoverImage , Nodes.HUD.RecordButtonSendPosition , true , 0 , BGC_SENDHOVER );
	Nodes.HUD.RecordButtonCancelNormal = env->addImage( Resources.Texture.RecordButtonCancelNormalImage , Nodes.HUD.RecordButtonCancelPosition , true , 0 , BGC_CANCELNORMAL );
	Nodes.HUD.RecordButtonCancelHover = env->addImage( Resources.Texture.RecordButtonCancelHoverImage , Nodes.HUD.RecordButtonCancelPosition , true , 0 , BGC_CANCELHOVER );
	Nodes.HUD.RecordButtonSendNormal->setVisible( false );
	Nodes.HUD.RecordButtonSendHover->setVisible( false );
	Nodes.HUD.RecordButtonCancelNormal->setVisible( false );
	Nodes.HUD.RecordButtonCancelHover->setVisible( false );

	Nodes.HUD.RecordNameEditBox = env->addEditBox( L"Nombre" , Nodes.HUD.RecordNameEditBoxPosition );
	Nodes.HUD.RecordNameEditBox->setMax(12);
	Nodes.HUD.RecordNameEditBox->setTextAlignment(irr::gui::EGUIA_CENTER,irr::gui::EGUIA_CENTER);
	Nodes.HUD.RecordNameEditBox->setVisible( false );

	for(uint16 i=0 ; i<7 ; i++)
	{
		Nodes.HUD.MacetaActual[i] = env->addImage( Resources.Texture.MacetaActualImage[i] , Nodes.HUD.MacetaActualPosition );
		Nodes.HUD.MacetaActual[i]->setVisible( false );
		//Nodes.HUD.MacetaActual[i]->setColor( irr::video::SColor(0x33,0xFF,0xFF,0xFF) );

		Nodes.HUD.MacetaNext[i] = env->addImage( Resources.Texture.MacetaNextImage[i] , Nodes.HUD.MacetaNextPosition );
		Nodes.HUD.MacetaNext[i]->setVisible( false );
		//Nodes.HUD.MacetaNext[i]->setColor( irr::video::SColor(0x33,0xFF,0xFF,0xFF) );
	}

	Nodes.HUD.Achievement = env->addImage( Resources.Texture.AchievementImage , Nodes.HUD.AchievementPosition );
	Nodes.HUD.Achievement->setVisible(false);


	real MusicVolume = (real)GameDevices->Audio->GetMusicVolume() * 0.01f;

	if( Resources.Music.Normal )
	{
		Resources.Music.Normal->setVolume( MusicVolume );
		Resources.Music.Normal->setRepeat( true );
		Resources.Music.Normal->setPosition( 0 );
	}
	if( Resources.Music.Fast )
	{
		Resources.Music.Fast->setVolume( MusicVolume );
		Resources.Music.Fast->setRepeat( true );
		Resources.Music.Fast->setPosition( 0 );
		Resources.Music.Fast->stop();
	}
	if( Resources.Music.GameOver )
	{
		Resources.Music.GameOver->setVolume( MusicVolume );
		Resources.Music.GameOver->setRepeat( false );
		Resources.Music.GameOver->setPosition( 0 );
		Resources.Music.GameOver->stop();
	}
	if( Resources.Music.Victory )
	{
		Resources.Music.Victory->setVolume( MusicVolume );
		Resources.Music.Victory->setRepeat( false );
		Resources.Music.Victory->setPosition( 0 );
		Resources.Music.Victory->stop();
	}
	if( Resources.Music.NewRecord )
	{
		Resources.Music.NewRecord->setVolume( MusicVolume );
		Resources.Music.NewRecord->setRepeat( false );
		Resources.Music.NewRecord->setPosition( 0 );
		Resources.Music.NewRecord->stop();
	}
	if( Resources.Music.Boss )
	{
		Resources.Music.Boss->setVolume( MusicVolume );
		Resources.Music.Boss->setRepeat( true );
		Resources.Music.Boss->setPosition( 0 );
	}
	if( Resources.Music.BossDefeated )
	{
		Resources.Music.BossDefeated->setVolume( MusicVolume );
		Resources.Music.BossDefeated->setRepeat( false );
		Resources.Music.BossDefeated->setPosition( 0 );
	}

	if(!IsBossTime)
	{
		Resources.Music.Normal->play();
		Resources.Music.Boss->stop();
	}
	else
	{
		Resources.Music.Normal->stop();
		Resources.Music.Boss->play();
	}
	

/*#if defined(_DEBUG)
	irr::scene::ISceneNode *arrowParent = smgr->addEmptySceneNode( Nodes.Board.Lugh );
	//arrowParent->setPosition(irr::core::vector3df(0, 0, 0));
	irr::scene::ISceneNode *arrow;

	arrow = smgr->addAnimatedMeshSceneNode(	smgr->addArrowMesh(L"Red",irr::video::SColor(0xFF,0xFF,0x00,0x00),irr::video::SColor(0xFF,0xFF,0x00,0x00),4,8,3.0,2),arrowParent);
	arrow->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	arrow->setRotation(irr::core::vector3df(0, 0,-90));
	arrow->setScale(irr::core::vector3df(3,3,3));

	arrow = smgr->addAnimatedMeshSceneNode(	smgr->addArrowMesh(L"Green",irr::video::SColor(0xFF,0x00,0xFF,0x00),irr::video::SColor(0xFF,0x00,0xFF,0x00),4,8,3.0,2),arrowParent);
	arrow->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	arrow->setRotation(irr::core::vector3df(0, 90, 0));
	arrow->setScale(irr::core::vector3df(3,3,3));

	arrow = smgr->addAnimatedMeshSceneNode(	smgr->addArrowMesh(L"Blue",irr::video::SColor(0xFF,0x00,0x00,0xFF),irr::video::SColor(0xFF,0x00,0x00,0xFF),4,8,3.0,2),arrowParent);
	arrow->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	arrow->setRotation(irr::core::vector3df(90, 0, 0));
	arrow->setScale(irr::core::vector3df(3,3,3));
#endif*/

	Variables.Switch.ScoreShowElement[0] = false;
	Variables.Switch.ScoreShowElement[1] = false;
	Variables.Switch.ScoreShowElement[2] = false;
	Variables.Switch.ScoreShowElement[3] = false;
	Variables.Switch.ScoreShowElement[4] = false;

	// Asigno el estado del juego
	GameStatus = STATUS_INIT;
	Variables.Switch.StartBallMoving = false;
	Variables.Switch.InsertMacetaMode = true;
	Variables.Switch.ForwardButtonPressed = false;

	#if defined(_DEBUG)
	DebugFPSMode = false;
	#endif

	irr::core::array<irr::scene::ISceneNode *> nodes;
	smgr->getSceneNodesFromType(irr::scene::ESNT_MESH, nodes); // Find all nodes
	irr::u32 nodeCount = nodes.size();

	for (irr::u32 i=0; i < nodeCount; ++i)
	{
		irr::scene::ISceneNode * node = nodes[i];

		#if defined(_DEBUG)
		COutput::Wprintf(L"Agregando Iluminación Dinámica a Nodo Mesh %s ID=%d\n",node->getName(),node->getID());
		#endif

		effect->addShadowToNode(node);
	}
	nodes.clear();

	smgr->getSceneNodesFromType(irr::scene::ESNT_ANIMATED_MESH, nodes); // Find all nodes
	nodeCount = nodes.size();

	for (irr::u32 i=0; i < nodeCount; ++i)
	{
		irr::scene::ISceneNode * node = nodes[i];

		#if defined(_DEBUG)
		COutput::Wprintf(L"Agregando Iluminación Dinámica a Nodo AnimatedMesh %s ID=%d\n",node->getName(),node->getID());
		#endif

		effect->addShadowToNode(node);
	}
	nodes.clear();

	smgr->getSceneNodesFromType(irr::scene::ESNT_LIGHT, nodes); // Find all nodes
	nodeCount = nodes.size();

	for (irr::u32 i=0; i < nodeCount; ++i)
	{
		irr::scene::ISceneNode* node = nodes[i];
		irr::core::vector3df lightPosition = node->getPosition();
		irr::c8 targetName[256];
		sprintf_s(targetName, 255, "%s_target", node->getName());

		irr::scene::ISceneNode *targetNode = smgr->getSceneNodeFromName(targetName);
		irr::core::vector3df targetPosition = targetNode->getPosition();

		#if defined(_DEBUG)
		COutput::Wprintf(L"Creando Luz en posición [%f,%f,%f] apuntando a [%f,%f,%f]\n",lightPosition.X, lightPosition.Y, lightPosition.Z, targetPosition.X, targetPosition.Y, targetPosition.Z);
		#endif

		effect->addShadowLight(	XEffects::SShadowLight(
								node->getID(), // id
								512, // shadowMapResolution
								lightPosition, // position
								targetPosition, // target
								irr::video::SColor(0, 0xFF, 0xFF, 0xFF), // lightColour
								10.0f, // nearValue
								100.0f, // farValue
								90.0f * irr::core::DEGTORAD)); // fov
	}
	nodes.clear();

	COutput::Wsprintf( Variables.String.Puntaje , L"%06d", Puntaje );
	COutput::Wsprintf( Variables.String.RemainingBombs , L"x%d" , RemainingBombs );

}


void BallsContextMain::Next(real delta)
{
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();
	irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
	XEffects::EffectHandler *effect = GameDevices->Effects->GetEffects();

	//irr::video::IVideoDriver *driver = GameDevices->Video->GetVideoDriver();
	//irr::IrrlichtDevice *device = GameDevices->Video->GetVideoDevice();

	//effect->getShadowLight(0).setPosition(Nodes.Lights.TestLight->getPosition());
	//effect->getShadowLight(0).setTarget(irr::core::vector3df(112.29f,0.0f,27.8f));

	switch( GameStatus )
	{
		case STATUS_ANIMATION:{
			Nodes.Camera.Node->setTarget( Nodes.Board.AnimationTargetNode->getPosition() );

			if( Clock.WaitTimer() )
			{
				//COutput::Wprintf(L"Tiempo: %f\n",RemainingTime);
				Clock.EnableTimer(RemainingTime);
				Clock.SetTime(RemainingTime);
				GameStatus = STATUS_BEGIN;

				Nodes.HUD.ScreenHUD->setVisible( true );
				Nodes.HUD.BombIconNormal->setVisible( true );
				Nodes.HUD.ForwardIconNormal->setVisible( true );
				//Nodes.HUD.ForwardBackground->setVisible( true );

				// Creo un nodo aleatorio para empezar
				CreateRandomMaceta( true );

				Nodes.HUD.MacetaActual[ Variables.Random.RandomMesh ]->setVisible( true );
				Nodes.HUD.MacetaNext[ Variables.Random.RandomMeshNext ]->setVisible( true );
			}
			break;
		}
		case STATUS_BEGIN:
		{
			if( Matrix.IsFinish )
			{
				if( Matrix.IsGameOver )
				{
					if( IsBossTime && Resources.Music.Boss )
					{
						Resources.Music.Boss->stop();
					}
					if( Resources.Music.Fast )
					{
						Resources.Music.Fast->stop();
					}
					if( Resources.Music.GameOver )
					{
						Resources.Music.GameOver->play();
					}

					GameStatus = STATUS_GAMEOVER;
					Nodes.HUD.ScreenHUD->setVisible( false );
					Nodes.HUD.LoseStatus->setVisible( true );
					Nodes.HUD.BombIconNormal->setVisible( false );
					Nodes.HUD.BombIconHover->setVisible( false );
					Nodes.HUD.BombIconPressed->setVisible( false );
					Nodes.HUD.BombIconPressedHover->setVisible( false );
					Nodes.HUD.ForwardIconNormal->setVisible( false );
					Nodes.HUD.ForwardIconHover->setVisible( false );
					Nodes.HUD.ForwardIconPressed->setVisible( false );
					//Nodes.HUD.ForwardBackground->setVisible( false );
				}
				else
				{
					if( IsBossTime )
					{
						if( Resources.Music.Boss )
						{
							Resources.Music.Boss->stop();
						}
						if( Resources.Music.BossDefeated )
						{
							Resources.Music.BossDefeated->play();
						}
					}
					else 
					{
						if( Resources.Music.Fast )
						{
							Resources.Music.Fast->stop();
						}
						if( Resources.Music.Victory )
						{
							Resources.Music.Victory->play();
						}
					}

					if( IsBossTime )
					{
						//Nodes.Board.Jail->setVisible( false );
						Nodes.Board.Key->setVisible( false );
					}


					if( Level == 10 )
					{
						UnlockTrophy(TROPHY_LUGH);
					}
					if( Puntaje > 1000 )
					{
						UnlockTrophy(TROPHY_JOE);
					}
					if( IsBossTime && BossLevel == 2 )
					{
						UnlockTrophy(TROPHY_SARGE);
					}
					if( Puntaje > 4000 )
					{
						UnlockTrophy(TROPHY_MASHI);
					}
					if( RemainingBombs > 5 )
					{
						UnlockTrophy(TROPHY_RETRO);
					}
					if( IsBossTime && BossLevel == 4 )
					{
						UnlockTrophy(TROPHY_BALL);
					}

					GameStatus = STATUS_VICTORY;
					Nodes.HUD.ScreenHUD->setVisible( false );
					Nodes.HUD.WinStatus->setVisible( true );
					Nodes.HUD.BombIconNormal->setVisible( false );
					Nodes.HUD.BombIconHover->setVisible( false );
					Nodes.HUD.BombIconPressed->setVisible( false );
					Nodes.HUD.BombIconPressedHover->setVisible( false );
					Nodes.HUD.ForwardIconNormal->setVisible( false );
					Nodes.HUD.ForwardIconHover->setVisible( false );
					Nodes.HUD.ForwardIconPressed->setVisible( false );
					//Nodes.HUD.ForwardBackground->setVisible( false );
				}
				Nodes.HUD.MacetaActual[ Variables.Random.RandomMesh ]->setVisible( false );
				Nodes.HUD.MacetaNext[ Variables.Random.RandomMeshNext ]->setVisible( false );
			}
			// Espero que el temporizador termine
			else if( Clock.WaitTimer() )
			{
				if( !Variables.Switch.StartBallMoving ){

					if( Resources.Music.Normal )
					{
						Resources.Music.Normal->stop();
					}
					if( !IsBossTime && Resources.Music.Fast )
					{
						Resources.Music.Fast->play();
					}
					StartBallAnimation();
					Nodes.Board.Lugh->setVisible(true);
					Nodes.Board.LughStand->setVisible(false);
					Nodes.HUD.ForwardIconNormal->setVisible(false);
					Nodes.HUD.ForwardIconHover->setVisible(false);
					Nodes.HUD.ForwardIconPressed->setVisible(true);
				}
				MoveBall();
			}
			break;
		}
		case STATUS_SCORE:
		{
			if( Clock.WaitTimer() && Variables.Global.IndexShowElement < 5 )
			{
				Variables.Switch.ScoreShowElement[ Variables.Global.IndexShowElement ] = true;
				Variables.Global.IndexShowElement += 1;
				Clock.EnableTimer( 0.5f );

				if( Variables.Global.IndexShowElement < 5)
				{
					if( Resources.Sound.ScoreDetail )
					{
						Resources.Sound.ScoreDetail->stop();
						Resources.Sound.ScoreDetail->setPosition(0);
						Resources.Sound.ScoreDetail->play();
					}
				}
				else
				{
					if( Resources.Sound.ScoreFinal )
					{
						Resources.Sound.ScoreFinal->stop();
						Resources.Sound.ScoreFinal->setPosition(0);
						Resources.Sound.ScoreFinal->play();
					}
					Nodes.HUD.ScoreHUD->setVisible( true );
				}
			}
			break;
		}
	}

	if( TrophyClock.WaitTimer() && AchievementUnlocked )
	{
		Nodes.HUD.Achievement->setVisible(false);
		AchievementUnlocked = false;
	}

	Clock.Next(delta);
	TrophyClock.Next(delta);
}


void BallsContextMain::Draw(void)
{
	irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();
	XEffects::EffectHandler *effect = GameDevices->Effects->GetEffects();

	GameDevices->Effects->Update();

	//GameDevices->SceneManager->DrawScene( driver );
	GameDevices->GUIEnvironment->DrawGUI( driver );

	switch( GameStatus )
	{
		case STATUS_INIT:
		{
			irr::scene::ISceneNodeAnimator *anim = smgr->createFlyCircleAnimator(	Nodes.Board.AnimationInitTargetPoint + irr::core::vector3df(0.0f,10.0f,0.0f) ,
																					20.0f , 0.0005f ,
																					irr::core::vector3df(0.0f,1.0f,0.0f),
																					-90.0f);
			if( anim )
			{
				Nodes.Camera.Node->setTarget( Nodes.Board.AnimationInitTargetPoint );
				Nodes.Camera.Node->addAnimator( anim );
				anim->drop();
			}		

			if( IsBossTime )
			{
				Nodes.HUD.BossLevelTitle->setVisible( true );	
			}
			else 
			{
				Nodes.HUD.LevelTitleBackground->setVisible( true );
			}
			GameStatus = STATUS_WAITING;
			break;
		}

		case STATUS_WAITING:
		{
			if( !IsBossTime )
			{
				wchar_t level[10];
				COutput::Wsprintf( level , L"Nivel %d",Level);
				Resources.Font.StageTitle->draw( level , Nodes.HUD.StageTitleTextPosition , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) , true , true );
			}
			break;
		}

		case STATUS_BEGIN:
		{
			wchar_t time[15];
			// Si el contador llega a cero, imprimir solo ceros
			if( Variables.Switch.StartBallMoving )
			{
				COutput::Wsprintf( time , L"00:00" );
			}
			else
			{
				COutput::Wsprintf( time , Clock.GetShortNormalFormattedTime() );
			}

			// Dibujar el contador de tiempo
			Resources.Font.HUD->draw( time , Nodes.HUD.ClockTextPosition , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );
			Resources.Font.HUD->draw( Variables.String.Puntaje , Nodes.HUD.ScoreTextPosition , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );
			Resources.Font.HUD->draw( Variables.String.RemainingBombs , Nodes.HUD.BombsTextPosition , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );

			//irr::core::position2d<irr::s32> m = GameDevices->Video->GetVideoDevice()->getCursorControl()->getPosition();
			//driver->draw2DImage( Resources.Texture.CursorImage , irr::core::vector2d<irr::s32>(m.X-32, m.Y-56) ,irr::core::rect<irr::s32>(0,0,64,64),0,irr::video::SColor(0xFF,0xFF,0xFF,0xFF),true);

			/*if( Variables.Switch.InsertMacetaMode )
			{
				Resources.Font.HUD->draw( L"Modo: Agregar" , irr::core::rect<irr::s32>(10,Height-60,150,Height) , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );
			}
			else
			{
				Resources.Font.HUD->draw( L"Modo: Eliminar" , irr::core::rect<irr::s32>(10,Height-60,150,Height) , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );
			}*/
			break;
		}

		case STATUS_GAMEOVER:
		{
			/*driver->draw2DImage( Resources.Texture.LoseImage, Nodes.HUD.StatusImagePosition,
				irr::core::rect<irr::s32>(0,0,512,128), 0,
				irr::video::SColor(255,255,255,255), true);*/
			break;
		}

		case STATUS_VICTORY:
		{
			/*driver->draw2DImage( Resources.Texture.VictoryImage, Nodes.HUD.StatusImagePosition,
				irr::core::rect<irr::s32>(0,0,512,128), 0,
				irr::video::SColor(255,255,255,255), true);*/
			break;
		}

		case STATUS_SCORE:
		{
			//wchar_t text[128];

			if( Variables.Switch.ScoreShowElement[0] )
			{
				//COutput::Wsprintf( text , L"100");
				Resources.Font.HUD->draw( Variables.String.PuntajePiezas , irr::core::rect<irr::s32>(Width-190,Height/2-123,Width,Height/2-153) , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );
			}

			if( Variables.Switch.ScoreShowElement[1] )
			{
				//COutput::Wsprintf( text , L"100");
				Resources.Font.HUD->draw( Variables.String.PuntajeSobras , irr::core::rect<irr::s32>(Width-190,Height/2-48,Width,Height/2-78) , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );
			}

			if( Variables.Switch.ScoreShowElement[2] )
			{
				//COutput::Wsprintf( text , L"100");
				Resources.Font.HUD->draw( Variables.String.PuntajeBonus , irr::core::rect<irr::s32>(Width-190,Height/2+28,Width,Height/2+58) , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );
			}

			if( Variables.Switch.ScoreShowElement[3] )
			{
				//COutput::Wsprintf( text , L"100");
				Resources.Font.HUD->draw( Variables.String.PuntajeTotal , irr::core::rect<irr::s32>(Width-190,Height/2+100,Width,Height/2+130) , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );
			}

			if( Variables.Switch.ScoreShowElement[4] )
			{
				//COutput::Wsprintf( text , L"100");
				Resources.Font.HUD->draw( Variables.String.Puntaje , Nodes.HUD.ScoreTextPosition , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );

				//irr::core::position2d<irr::s32> m = GameDevices->Video->GetVideoDevice()->getCursorControl()->getPosition();
				//driver->draw2DImage( Resources.Texture.CursorImage , irr::core::vector2d<irr::s32>(m.X-32, m.Y-56) ,irr::core::rect<irr::s32>(0,0,64,64),0,irr::video::SColor(0xFF,0xFF,0xFF,0xFF),true);
			}

			//Resources.Font.HUD->draw( L"¡Felicidades! Has pasado al siguiente nivel" , irr::core::rect<irr::s32>(Width/2-380,100,Width/2+380,160) , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );

			/*COutput::Wsprintf( text , L"Bloques usados: %2d x %2d = %3d",10,Variables.Global.FactorPasses,10*Variables.Global.FactorPasses);
			Resources.Font.HUD->draw( text , irr::core::rect<irr::s32>(Width/2-380,200,Width/2+380,260) , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );

			COutput::Wsprintf( text , L"Bloques sobrantes: %2d x %2d = %3d",5,FactorUnpassed,5*FactorUnpassed);
			Resources.Font.HUD->draw( text , irr::core::rect<irr::s32>(Width/2-380,300,Width/2+380,360) , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );

			COutput::Wsprintf( text , L"Bonus loops: %2d x %2d = %3d",2,10,20);
			Resources.Font.HUD->draw( text , irr::core::rect<irr::s32>(Width/2-380,400,Width/2+380,460) , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );

			COutput::Wsprintf( text , L"        Total: %3d",110);
			Resources.Font.HUD->draw( text , irr::core::rect<irr::s32>(Width/2-380,500,Width/2+380,560) , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );

			Resources.Font.HUD->draw( PuntajeText , irr::core::rect<irr::s32>(Width-150,0,Width-10,50) , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );*/
			break;
		}

		case STATUS_INPUTSCORE:
		{
			//irr::core::position2d<irr::s32> m = GameDevices->Video->GetVideoDevice()->getCursorControl()->getPosition();
			//driver->draw2DImage( Resources.Texture.CursorImage , irr::core::vector2d<irr::s32>(m.X-32, m.Y-56) ,irr::core::rect<irr::s32>(0,0,64,64),0,irr::video::SColor(0xFF,0xFF,0xFF,0xFF),true);
			break;
		}

		default:
		{
			break;
		}
	}
}


void BallsContextMain::End(void)
{
	XEffects::EffectHandler *effect = GameDevices->Effects->GetEffects();

	Resources.Music.Normal->stop();
	Resources.Music.Fast->stop();
	Resources.Music.GameOver->stop();
	Resources.Music.Victory->stop();
	Resources.Music.NewRecord->stop();

	Nodes.Board.Lugh = NULL;
	Nodes.Board.Maceta = NULL;
	Nodes.Board.SelectedMaceta = NULL;
	Nodes.Camera.FPS = NULL;
	Nodes.Camera.Node = NULL;

	effect->removeAllShadowLights();
	effect->removeAllShadowNodes();
}


bool BallsContextMain::LoadingInit(void)
{
	irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
	irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

	Resources.Texture.LoadingBackgroundImage = driver->getTexture(L"loading/tiled_99.jpg");
	Resources.Texture.LoadingTextImage = driver->getTexture(L"loading/cargando.png");

	wchar_t texturePath[64];

	for( uint16 i=0 ; i<24 ; i++ )
	{
		COutput::Wsprintf( texturePath , L"loading/roundillo_s%02d.png", i+1 );
		Resources.Texture.LoadingLughImage[ i ] = driver->getTexture( texturePath );
	}
	Nodes.Loading.BgRect = irr::core::rect<irr::s32>( 0 , 0 , Width , Height );
	Nodes.Loading.BgPosition = irr::core::vector2d<irr::s32>( 0 , 0 );

	Nodes.Loading.PigRect = irr::core::rect<irr::s32>( 0 , 0 , 64 , 64 );
	Nodes.Loading.PigPosition = irr::core::vector2d<irr::s32>( Width - 80 , Height - 80 );

	Nodes.Loading.TextRect = irr::core::rect<irr::s32>( 0 , 0 , 256 , 64 );
	Nodes.Loading.TextPosition = irr::core::vector2d<irr::s32>( Width - 336 , Height - 80 );

	return true;
}

void BallsContextMain::LoadingPrepare(void)
{
	Variables.Loading.ActualPig = 0;
	LoadingClock.EnableTimer( 0.033f );
}

void BallsContextMain::LoadingNext(real delta)
{
	LoadingClock.Next( delta );

	if( LoadingClock.WaitTimer() )
	{
		Variables.Loading.ActualPig += 1;
		Variables.Loading.ActualPig %= 24;
		LoadingClock.EnableTimer( 0.033f );
	}
}

void BallsContextMain::LoadingDraw(void)
{
	irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();

	driver->draw2DImage(	Resources.Texture.LoadingBackgroundImage  ,
							Nodes.Loading.BgPosition ,
							Nodes.Loading.BgRect );

	driver->draw2DImage(	Resources.Texture.LoadingLughImage[ Variables.Loading.ActualPig ] ,
							Nodes.Loading.PigPosition , 
							Nodes.Loading.PigRect , 
							0 , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) , true );

	driver->draw2DImage(	Resources.Texture.LoadingTextImage ,
							Nodes.Loading.TextPosition , 
							Nodes.Loading.TextRect , 
							0 , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) , true );
}

void BallsContextMain::LoadingEnd(void)
{
}


void BallsContextMain::Close(void)
{

}


bool BallsContextMain::OnGUIEvent(	irr::gui::IGUIElement *caller,
									irr::gui::IGUIElement *element,
									const uint16 &eventType )
{
	irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
	irr::gui::IGUISkin *skin = GameDevices->GUIEnvironment->GetGUISkin();

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

				case BGC_BOMBNORMAL:
				{
					if( RemainingBombs > 0 )
					{
						Nodes.HUD.BombIconNormal->setVisible( false );
						Nodes.HUD.BombIconHover->setVisible( true );
						Nodes.HUD.BombIconPressed->setVisible( false );
						Nodes.HUD.BombIconPressedHover->setVisible( false );
					}
					break;
				}

				/*case BGC_BOMBHOVER:
				{
					Nodes.HUD.BombIconNormal->setVisible( false );
					Nodes.HUD.BombIconHover->setVisible( true );
					Nodes.HUD.BombIconPressed->setVisible( false );
					Nodes.HUD.BombIconPressedHover->setVisible( false );
					break;
				}*/

				case BGC_BOMBPRESSED:
				{
					Nodes.HUD.BombIconNormal->setVisible( false );
					Nodes.HUD.BombIconHover->setVisible( false );
					Nodes.HUD.BombIconPressed->setVisible( false );
					Nodes.HUD.BombIconPressedHover->setVisible( true );
					break;
				}

				/*case BGC_BOMBPRESSEDHOVER:
				{
					Nodes.HUD.BombIconNormal->setVisible( false );
					Nodes.HUD.BombIconHover->setVisible( false );
					Nodes.HUD.BombIconPressed->setVisible( false );
					Nodes.HUD.BombIconPressedHover->setVisible( true );
					break;
				}*/

				case BGC_FORWARDNORMAL:
				{
					if( !Variables.Switch.ForwardButtonPressed && !Variables.Switch.StartBallMoving )
					{
						Nodes.HUD.ForwardIconNormal->setVisible( false );
						Nodes.HUD.ForwardIconHover->setVisible( true );
						Nodes.HUD.ForwardIconPressed->setVisible( false );
					}
					break;
				}

				case BGC_SENDNORMAL:
				{
					Nodes.HUD.RecordButtonSendNormal->setVisible( false );
					Nodes.HUD.RecordButtonSendHover->setVisible( true );
					if( Resources.Sound.MenuHover )
					{
						Resources.Sound.MenuHover->stop();
						Resources.Sound.MenuHover->setPosition(0);
						Resources.Sound.MenuHover->play();
					}
					break;
				}

				case BGC_CANCELNORMAL:
				{
					Nodes.HUD.RecordButtonCancelNormal->setVisible( false );
					Nodes.HUD.RecordButtonCancelHover->setVisible( true );
					if( Resources.Sound.MenuHover )
					{
						Resources.Sound.MenuHover->stop();
						Resources.Sound.MenuHover->setPosition(0);
						Resources.Sound.MenuHover->play();
					}
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

				/*case BGC_BOMBNORMAL:
				{
					Nodes.HUD.BombIconNormal->setVisible( true );
					Nodes.HUD.BombIconHover->setVisible( false );
					Nodes.HUD.BombIconPressed->setVisible( false );
					Nodes.HUD.BombIconPressedHover->setVisible( false );
					break;
				}*/

				case BGC_BOMBHOVER:
				{
					Nodes.HUD.BombIconNormal->setVisible( true );
					Nodes.HUD.BombIconHover->setVisible( false );
					Nodes.HUD.BombIconPressed->setVisible( false );
					Nodes.HUD.BombIconPressedHover->setVisible( false );
					break;
				}

				/*case BGC_BOMBPRESSED:
				{
					Nodes.HUD.BombIconNormal->setVisible( false );
					Nodes.HUD.BombIconHover->setVisible( false );
					Nodes.HUD.BombIconPressed->setVisible( true );
					Nodes.HUD.BombIconPressedHover->setVisible( false );
					break;
				}*/

				case BGC_BOMBPRESSEDHOVER:
				{
					Nodes.HUD.BombIconNormal->setVisible( false );
					Nodes.HUD.BombIconHover->setVisible( false );
					Nodes.HUD.BombIconPressed->setVisible( true );
					Nodes.HUD.BombIconPressedHover->setVisible( false );
					break;
				}

				case BGC_FORWARDHOVER:
				{
					if( !Variables.Switch.ForwardButtonPressed && !Variables.Switch.StartBallMoving )
					{
						Nodes.HUD.ForwardIconNormal->setVisible( true );
						Nodes.HUD.ForwardIconHover->setVisible( false );
						Nodes.HUD.ForwardIconPressed->setVisible( false );
					}
					break;
				}

				case BGC_SENDHOVER:
				{
					Nodes.HUD.RecordButtonSendNormal->setVisible( true );
					Nodes.HUD.RecordButtonSendHover->setVisible( false );
					break;
				}

				case BGC_CANCELHOVER:
				{
					Nodes.HUD.RecordButtonCancelNormal->setVisible( true );
					Nodes.HUD.RecordButtonCancelHover->setVisible( false );
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

				/*case BGC_BOMBNORMAL:
				{
					Nodes.HUD.BombIconNormal->setVisible( false );
					Nodes.HUD.BombIconHover->setVisible( false );
					Nodes.HUD.BombIconPressed->setVisible( true );
					Nodes.HUD.BombIconPressedHover->setVisible( false );
					break;
				}*/

				case BGC_BOMBHOVER:
				{
					Nodes.HUD.BombIconNormal->setVisible( false );
					Nodes.HUD.BombIconHover->setVisible( false );
					Nodes.HUD.BombIconPressed->setVisible( true );
					Nodes.HUD.BombIconPressedHover->setVisible( false );
					Variables.Switch.InsertMacetaMode = false;
					break;
				}

				/*case BGC_BOMBPRESSED:
				{
					Nodes.HUD.BombIconNormal->setVisible( true );
					Nodes.HUD.BombIconHover->setVisible( false );
					Nodes.HUD.BombIconPressed->setVisible( false );
					Nodes.HUD.BombIconPressedHover->setVisible( false );
					break;
				}*/

				case BGC_BOMBPRESSEDHOVER:
				{
					Nodes.HUD.BombIconNormal->setVisible( true );
					Nodes.HUD.BombIconHover->setVisible( false );
					Nodes.HUD.BombIconPressed->setVisible( false );
					Nodes.HUD.BombIconPressedHover->setVisible( false );
					Variables.Switch.InsertMacetaMode = true;
					break;
				}

				case BGC_FORWARDHOVER:
				{
					if( !Variables.Switch.ForwardButtonPressed && !Variables.Switch.StartBallMoving )
					{
						Nodes.HUD.ForwardIconNormal->setVisible( false );
						Nodes.HUD.ForwardIconHover->setVisible( false );
						Nodes.HUD.ForwardIconPressed->setVisible( true );
						Variables.Switch.ForwardButtonPressed = true;

						if( !IsBossTime )
						{
							if( Resources.Music.Normal )
							{
								Resources.Music.Normal->stop();
							}
							if( Resources.Music.Fast )
							{
								Resources.Music.Fast->play();
							}
						}
						MoveBall(true);
						StartBallAnimation();
						Nodes.Board.Lugh->setVisible(true);
						Nodes.Board.LughStand->setVisible(false);
					}
					break;
				}

				case BGC_SENDHOVER:
				{
					if( COutput::Wcslen( Nodes.HUD.RecordNameEditBox->getText() ) > 0 )
					{
						Scoreboard.AddScoreData( Nodes.HUD.RecordNameEditBox->getText() , Puntaje , Level );
						Scoreboard.SaveScoreboard();
					}

					Finalize(ID_SCOREBOARD);
					Level = 1;
					Puntaje = 0;
					RemainingTime = 60.0f;
					RemainingBombs = 3;
					BallSpeed = Variables.Global.InitBallSpeed;
					

					Nodes.HUD.RecordTitle->setVisible( false );
					//Nodes.HUD.RecordWriteYourName->setVisible( false );
					Nodes.HUD.RecordButtonSendNormal->setVisible( false );
					Nodes.HUD.RecordButtonCancelNormal->setVisible( false );
					Nodes.HUD.RecordButtonSendHover->setVisible( false );
					Nodes.HUD.RecordButtonCancelHover->setVisible( false );
					Nodes.HUD.RecordNameEditBox->setVisible( false );

					if( Resources.Sound.MenuPressed )
					{
						Resources.Sound.MenuPressed->stop();
						Resources.Sound.MenuPressed->setPosition(0);
						Resources.Sound.MenuPressed->play();
					}
					break;
				}

				case BGC_CANCELHOVER:
				{
					Finalize(ID_TITLE);
					Level = 1;
					Puntaje = 0;
					RemainingTime = 60.0f;
					RemainingBombs = 3;
					BallSpeed = Variables.Global.InitBallSpeed;

					Nodes.HUD.RecordTitle->setVisible( false );
					//Nodes.HUD.RecordWriteYourName->setVisible( false );
					Nodes.HUD.RecordButtonSendNormal->setVisible( false );
					Nodes.HUD.RecordButtonCancelNormal->setVisible( false );
					Nodes.HUD.RecordButtonSendHover->setVisible( false );
					Nodes.HUD.RecordButtonCancelHover->setVisible( false );
					Nodes.HUD.RecordNameEditBox->setVisible( false );

					if( Resources.Sound.MenuPressed )
					{
						Resources.Sound.MenuPressed->stop();
						Resources.Sound.MenuPressed->setPosition(0);
						Resources.Sound.MenuPressed->play();
					}
					break;
				}
			}
			break;
		}
	}
	return false;
}

bool BallsContextMain::OnKeyInput(	const uint16 &key,
									const wchar_t &keyChar,
									const bool isCtrl,
									const bool isShift,
									const bool isPressedDown )
{
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();

	if( isPressedDown )
	{
		switch( GameStatus )
		{
			case STATUS_BEGIN:
			{
				switch( key )
				{

					#if defined(DEBUG_MODE)
					case irr::KEY_F1:
					{
						if( Clock.IsActive() ){
							#if defined(_DEBUG)
							COutput::Wprintf(L"Reloj Detenido...\n");
							#endif
							Clock.Stop();
						}
						else {
							#if defined(_DEBUG)
							COutput::Wprintf(L"Reloj Corriendo...\n");
							#endif
							Clock.Start();
						}
						break;
					}

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


					/*case irr::KEY_F3:
					{
						irr::core::vector3df position = DebugNode->getPosition();
						irr::core::vector3df rotation = DebugNode->getRotation();
						#if defined(_DEBUG)
						COutput::Wprintf(L"DebugNode Posicion: (%f,%f,%f)\n",position.X,position.Y,position.Z);
						COutput::Wprintf(L"DebugNode Rotacion: (%f,%f,%f)\n",rotation.X,rotation.Y,rotation.Z);
						#endif
						break;
					}*/

					/*case irr::KEY_F3:
					{
						uint16 nrand = CSystem::Random() % Variables.Random.NroMeshes;
						#if defined(_DEBUG)
						COutput::Wprintf(L"Numero Aleatorio: %d\n",nrand);
						#endif
						CreateMacetaNode( nrand );
						SelectEmptyMacetaNode(MousePosition.X,MousePosition.Y);
						break;
					}*/

					/*case irr::KEY_F4:
					{
						Variables.Switch.InsertMacetaMode = !Variables.Switch.InsertMacetaMode;
						break;
					}*/

					case irr::KEY_F4:
					{
						if( DebugFPSMode )
						{
							Nodes.Camera.Node->setPosition( Nodes.Camera.FPS->getPosition() );
							Nodes.Camera.Node->setTarget( Nodes.Camera.FPS->getTarget() );
							smgr->setActiveCamera( Nodes.Camera.Node );
							#if defined(_DEBUG)
							COutput::Wprintf(L"Activado Modo FPS\n");
							#endif
							DebugFPSMode = false;
						}
						else
						{
							Nodes.Camera.FPS->setPosition( Nodes.Camera.Node->getPosition() );
							Nodes.Camera.FPS->setTarget( Nodes.Camera.Node->getTarget() );
							smgr->setActiveCamera( Nodes.Camera.FPS );
							#if defined(_DEBUG)
							COutput::Wprintf(L"Desactivado Modo FPS\n");
							#endif
							DebugFPSMode = true;
						}
						break;
					}

					case irr::KEY_F5:
					{
						RemainingBombs += 1;
						COutput::Wsprintf( Variables.String.RemainingBombs , L"x%d" , RemainingBombs );
						break;
					}

					case irr::KEY_F6:
					{
						if( !Variables.Switch.StartBallMoving )
						{
							if( Resources.Music.Normal )
							{
								Resources.Music.Normal->stop();
							}
							if( !IsBossTime && Resources.Music.Fast )
							{
								Resources.Music.Fast->play();
							}
							StartBallAnimation();
							MoveBall(true);
						}
						break;
					}


					/*case irr::KEY_F10:
					{
						Restart(false);
						break;
					}*/

					case irr::KEY_KEY_1:{CreateMacetaNode( 0 );SelectEmptyMacetaNode(MousePosition.X,MousePosition.Y);break;}
					case irr::KEY_KEY_2:{CreateMacetaNode( 1 );SelectEmptyMacetaNode(MousePosition.X,MousePosition.Y);break;}
					case irr::KEY_KEY_3:{CreateMacetaNode( 2 );SelectEmptyMacetaNode(MousePosition.X,MousePosition.Y);break;}
					case irr::KEY_KEY_4:{CreateMacetaNode( 3 );SelectEmptyMacetaNode(MousePosition.X,MousePosition.Y);break;}
					case irr::KEY_KEY_5:{CreateMacetaNode( 4 );SelectEmptyMacetaNode(MousePosition.X,MousePosition.Y);break;}
					case irr::KEY_KEY_6:{CreateMacetaNode( 5 );SelectEmptyMacetaNode(MousePosition.X,MousePosition.Y);break;}
					case irr::KEY_KEY_7:{CreateMacetaNode( 6 );SelectEmptyMacetaNode(MousePosition.X,MousePosition.Y);break;}


					case irr::KEY_KEY_Z:
					{
						DebugDesp -= 0.1f;
						#if defined(_DEBUG)
						COutput::Wprintf(L"offset: %f\n",DebugDesp);
						#endif
						break;
					}

					case irr::KEY_KEY_X:
					{
						DebugDesp += 0.1f;
						#if defined(_DEBUG)
						COutput::Wprintf(L"offset: %f\n",DebugDesp);
						#endif
						break;
					}

					case irr::KEY_KEY_C:
					{
						DebugDesp -= 0.001f;
						#if defined(_DEBUG)
						COutput::Wprintf(L"offset: %f\n",DebugDesp);
						#endif
						break;
					}

					case irr::KEY_KEY_V:
					{
						DebugDesp += 0.001f;
						#if defined(_DEBUG)
						COutput::Wprintf(L"offset: %f\n",DebugDesp);
						#endif
						break;
					}


					case irr::KEY_KEY_W:
					{
						if( DebugNode )
						{
							irr::core::vector3df position = DebugNode->getPosition();
							position += irr::core::vector3df(0.0f,0.0f,-DebugDesp);
							DebugNode->setPosition( position );
							#if defined(_DEBUG)
							COutput::Wprintf(L"Position: (%f,%f,%f)\n",position.X,position.Y,position.Z);
							#endif
						}
						break;
					}

					case irr::KEY_KEY_S:
					{
						if( DebugNode )
						{
							irr::core::vector3df position = DebugNode->getPosition();
							position += irr::core::vector3df(0.0f,0.0f,DebugDesp);
							DebugNode->setPosition( position );
							#if defined(_DEBUG)
							COutput::Wprintf(L"Position: (%f,%f,%f)\n",position.X,position.Y,position.Z);
							#endif
						}
						break;
					}

					case irr::KEY_KEY_A:
					{
						if( DebugNode )
						{
							irr::core::vector3df position = DebugNode->getPosition();
							position += irr::core::vector3df(-DebugDesp,0.0f,0.0f);
							DebugNode->setPosition( position );
							#if defined(_DEBUG)
							COutput::Wprintf(L"Position: (%f,%f,%f)\n",position.X,position.Y,position.Z);
							#endif
						}
						break;
					}

					case irr::KEY_KEY_D:
					{
						if( DebugNode )
						{
							irr::core::vector3df position = DebugNode->getPosition();
							position += irr::core::vector3df(DebugDesp,0.0f,0.0f);
							DebugNode->setPosition( position );
							#if defined(_DEBUG)
							COutput::Wprintf(L"Position: (%f,%f,%f)\n",position.X,position.Y,position.Z);
							#endif
						}
						break;
					}

					case irr::KEY_KEY_Q:
					{
						if( DebugNode )
						{
							irr::core::vector3df position = DebugNode->getPosition();
							position += irr::core::vector3df(0.0f,-DebugDesp,0.0f);
							DebugNode->setPosition( position );
							#if defined(_DEBUG)
							COutput::Wprintf(L"Position: (%f,%f,%f)\n",position.X,position.Y,position.Z);
							#endif
						}
						break;
					}

					case irr::KEY_KEY_E:
					{
						if( DebugNode )
						{
							irr::core::vector3df position = DebugNode->getPosition();
							position += irr::core::vector3df(0.0f,DebugDesp,0.0f);
							DebugNode->setPosition( position );
							#if defined(_DEBUG)
							COutput::Wprintf(L"Position: (%f,%f,%f)\n",position.X,position.Y,position.Z);
							#endif
						}
						break;
					}








					case irr::KEY_KEY_T:
					{
						if( DebugNode )
						{
							irr::core::vector3df position = DebugNode->getRotation();
							position += irr::core::vector3df(0.0f,0.0f,-DebugDesp);
							DebugNode->setRotation( position );
							#if defined(_DEBUG)
							COutput::Wprintf(L"Rotation: (%f,%f,%f)\n",position.X,position.Y,position.Z);
							#endif
						}
						break;
					}

					case irr::KEY_KEY_G:
					{
						if( DebugNode )
						{
							irr::core::vector3df position = DebugNode->getRotation();
							position += irr::core::vector3df(0.0f,0.0f,DebugDesp);
							DebugNode->setRotation( position );
							#if defined(_DEBUG)
							COutput::Wprintf(L"Rotation: (%f,%f,%f)\n",position.X,position.Y,position.Z);
							#endif
						}
						break;
					}

					case irr::KEY_KEY_F:
					{
						if( DebugNode )
						{
							irr::core::vector3df position = DebugNode->getRotation();
							position += irr::core::vector3df(-DebugDesp,0.0f,0.0f);
							DebugNode->setRotation( position );
							#if defined(_DEBUG)
							COutput::Wprintf(L"Rotation: (%f,%f,%f)\n",position.X,position.Y,position.Z);
							#endif
						}
						break;
					}

					case irr::KEY_KEY_H:
					{
						if( DebugNode )
						{
							irr::core::vector3df position = DebugNode->getRotation();
							position += irr::core::vector3df(DebugDesp,0.0f,0.0f);
							DebugNode->setRotation( position );
							#if defined(_DEBUG)
							COutput::Wprintf(L"Rotation: (%f,%f,%f)\n",position.X,position.Y,position.Z);
							#endif
						}
						break;
					}

					case irr::KEY_KEY_R:
					{
						if( DebugNode )
						{
							irr::core::vector3df position = DebugNode->getRotation();
							position += irr::core::vector3df(0.0f,-DebugDesp,0.0f);
							DebugNode->setRotation( position );
							#if defined(_DEBUG)
							COutput::Wprintf(L"Rotation: (%f,%f,%f)\n",position.X,position.Y,position.Z);
							#endif
						}
						break;
					}

					case irr::KEY_KEY_Y:
					{
						if( DebugNode )
						{
							irr::core::vector3df position = DebugNode->getRotation();
							position += irr::core::vector3df(0.0f,DebugDesp,0.0f);
							DebugNode->setRotation( position );
							#if defined(_DEBUG)
							COutput::Wprintf(L"Rotation: (%f,%f,%f)\n",position.X,position.Y,position.Z);
							#endif
						}
						break;
					}
					#endif


					default:
					{
						break;
					}
				}
				break;
			}
		}
	}
	return false;
}

bool BallsContextMain::OnMouseInput(const uint16 &eventType,
									const sint32 &mouseX,
									const sint32 &mouseY,
									const real &wheel,
									const bool isLeft,
									const bool isMiddle,
									const bool isRight,
									const bool isCtrl,
									const bool isShift )
{

	irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();

	switch( GameStatus )
	{
		case STATUS_WAITING:
		{
			switch( eventType )
			{

				case irr::EMIE_LMOUSE_PRESSED_DOWN:
				{
					irr::scene::ISceneNodeAnimator* anim = smgr->createFlyStraightAnimator( Nodes.Board.AnimationInitTargetPoint , Nodes.Camera.Target , 1500 );
					if( anim )
					{
						Nodes.Board.AnimationTargetNode->addAnimator( anim );
						anim->drop();
						anim = NULL;
					}
					anim = smgr->createFlyStraightAnimator( Nodes.Camera.Node->getPosition() , Nodes.Camera.Position , 1500 );
					if( anim )
					{
						Nodes.Camera.Node->addAnimator( anim );
						anim->drop();
					}
					if( IsBossTime )
					{
						Nodes.HUD.BossLevelTitle->setVisible( false );
					}
					else
					{
						Nodes.HUD.LevelTitleBackground->setVisible( false );
					}

					Clock.EnableTimer(1.5f);
					GameStatus = STATUS_ANIMATION;
					break;
				}
			}
			break;
		}

		case STATUS_BEGIN:
		{
			switch( eventType )
			{
				case irr::EMIE_LMOUSE_PRESSED_DOWN:
				{
					if( Variables.Switch.InsertMacetaMode )
					{
						if( PutMacetaNode() && Resources.Sound.MacetaPut )
						{
							Resources.Sound.MacetaPut->stop();
							Resources.Sound.MacetaPut->setPosition(0);
							Resources.Sound.MacetaPut->play();
						}
					}
					else if( DeleteMacetaNode() )
					{
						Nodes.HUD.BombIconNormal->setVisible( true );
						Nodes.HUD.BombIconHover->setVisible( false );
						Nodes.HUD.BombIconPressed->setVisible( false );
						Nodes.HUD.BombIconPressedHover->setVisible( false );
						Variables.Switch.InsertMacetaMode = true;

						if( Resources.Sound.BombExplosion )
						{
							Resources.Sound.BombExplosion->stop();
							Resources.Sound.BombExplosion->setPosition(0);
							Resources.Sound.BombExplosion->play();
						}
					}
					break;
				}

				case irr::EMIE_MOUSE_MOVED:
				{
					MousePosition = irr::core::vector2di(mouseX,mouseY);
					Variables.Switch.InsertMacetaMode ? SelectEmptyMacetaNode(mouseX,mouseY) : SelectPutMacetaNode(mouseX,mouseY);
					break;
				}

			} //-- fin switch()
			break;
		}

		case STATUS_GAMEOVER:
		{
			switch( eventType )
			{
				case irr::EMIE_LMOUSE_PRESSED_DOWN:
				{
					if( Puntaje>0 && Scoreboard.VerifyScore( Puntaje ) )
					{
						if( Resources.Music.GameOver )
						{
							Resources.Music.GameOver->stop();
						}
						if( Resources.Music.NewRecord )
						{
							Resources.Music.NewRecord->play();
						}
						GameStatus = STATUS_INPUTSCORE;
						Nodes.HUD.LoseStatus->setVisible( false );

						Nodes.HUD.RecordTitle->setVisible( true );
						//Nodes.HUD.RecordWriteYourName->setVisible( true );
						Nodes.HUD.RecordButtonSendNormal->setVisible( true );
						Nodes.HUD.RecordButtonCancelNormal->setVisible( true );
						Nodes.HUD.RecordNameEditBox->setVisible( true );
					}
					else 
					{
						Finalize(ID_TITLE);
						Level = 1;
						Puntaje = 0;
						RemainingTime = 60.0f;
						RemainingBombs = 3;
						BallSpeed = Variables.Global.InitBallSpeed;
						BallRotationSpeed = Variables.Global.InitBallRotationSpeed ;

						Nodes.HUD.LoseStatus->setVisible( false );
					}
					break;
				}
			}
			break;
		}

		case STATUS_VICTORY:
		{
			switch( eventType )
			{

				case irr::EMIE_LMOUSE_PRESSED_DOWN:
				{
					uint16 n1 = Matrix.GetBlockPasses();
					uint16 n2 = Matrix.GetBlockUnpasses();

					uint16 PuntajePiezas;
					uint16 PuntajeSobras;
					uint16 PuntajeBonus;

					if( !IsBossTime )
					{
						PuntajePiezas = (uint16) ( (real)n1 * (real)Variables.Score.FactorPasses * (real)Level * Variables.Score.FactorLevelScore );
						PuntajeSobras = n2 > Variables.Score.MaxUnpassesBlocks ? 0 : (uint16)( (real)( Variables.Score.MaxUnpassesBlocks - n2 ) * (real)Variables.Score.FactorUnpasses * (real)Level * Variables.Score.FactorLevelScore );
						PuntajeBonus = (uint16) ( ( Clock.GetSavedTime() * (real)Variables.Score.FactorBonusTime + (real)RemainingBombs * (real)Variables.Score.FactorBonusBombs ) * (real)Level * Variables.Score.FactorLevelScore );
					}
					else
					{
						PuntajePiezas = (uint16) ( (real)n1 * (real)Variables.Score.BossFactorPasses * (real)BossLevel * Variables.Score.FactorBossScore );
						PuntajeSobras = n2 > Variables.Score.MaxUnpassesBlocks ? 0 : (uint16)( (real)( Variables.Score.MaxUnpassesBlocks - n2 ) * (real)Variables.Score.BossFactorUnpasses * (real)BossLevel * Variables.Score.FactorBossScore );
						PuntajeBonus = (uint16) ( (real)Variables.Score.BonusBossDefeated * (real)BossLevel * Variables.Score.FactorBossScore );
					}

					//uint16 PuntajeBonus = (uint16) z;
					uint16 PuntajeTotal;
					
					PuntajeTotal = PuntajePiezas + PuntajeSobras + PuntajeBonus;
					Puntaje += PuntajeTotal;
					COutput::Wsprintf(Variables.String.PuntajePiezas,L"%05d",PuntajePiezas);
					COutput::Wsprintf(Variables.String.PuntajeSobras,L"%05d",PuntajeSobras );
					COutput::Wsprintf(Variables.String.PuntajeBonus,L"%05d",PuntajeBonus);
					COutput::Wsprintf(Variables.String.PuntajeTotal,L"%05d",PuntajeTotal);
					COutput::Wsprintf(Variables.String.Puntaje,L"%06d",Puntaje);

					GameStatus = STATUS_SCORE;
					Nodes.HUD.ResultsTitle->setVisible( true );
					Nodes.HUD.ResultsDescription->setVisible( true );
					Nodes.HUD.WinStatus->setVisible( false );
					Clock.EnableTimer( 0.5f );

					if( !IsBossTime )
					{
						BallSpeed = (irr::s32) ( (real)BallSpeed * Variables.Global.FactorSpeedInc );
						BallRotationSpeed = BallRotationSpeed * (2.0f - Variables.Global.FactorSpeedInc );
					}
					break;
				}
			}
			break;
		}

		case STATUS_SCORE:
		{
			switch( eventType )
			{
				case irr::EMIE_LMOUSE_PRESSED_DOWN:
				{
					if( Variables.Global.IndexShowElement < 5 )
					{
						do
						{
							Variables.Switch.ScoreShowElement[ Variables.Global.IndexShowElement ] = true;
							Variables.Global.IndexShowElement += 1;
						}
						while( Variables.Global.IndexShowElement < 5 );

						if( Resources.Sound.ScoreFinal )
						{
							Resources.Sound.ScoreFinal->stop();
							Resources.Sound.ScoreFinal->setPosition(0);
							Resources.Sound.ScoreFinal->play();
						}
						Nodes.HUD.ScoreHUD->setVisible( true );
					}
					else
					{
						Restart(false);
						if( !IsBossTime )
						{
							Level += 1;
							if( !(Level % Variables.Global.LevelsPerBoss) )
							{
								IsBossTime = true;
							}
						}
						else 
						{
							BossLevel += 1;
							RemainingBombs += 2;
							IsBossTime = false;
						}

						//RemainingTime -= 5.0f;
						Variables.Global.IndexShowElement = 0;
						Nodes.HUD.ResultsTitle->setVisible( false );
						Nodes.HUD.ResultsDescription->setVisible( false );
					}
					break;
				}
			}
			break;
		}
	}
	return false;
}


void BallsContextMain::CreateRandomMaceta(bool both)
{
	uint16 nrand;
	uint16 probability;

	if( both )
	{
		Variables.Random.RandomMesh = CSystem::Random() % Variables.Random.NroMeshes;
		do 
		{
			probability = CSystem::Random() % 101;
			nrand = CSystem::Random() % Variables.Random.NroMeshes;
		}
		while( probability < Variables.Random.RandomProbability && nrand == Variables.Random.RandomMesh );

		Variables.Random.RandomMeshNext = nrand;

		#if defined(_DEBUG)
		COutput::Wprintf(L"Numero Aleatorio: actual=%d next=%d\n",Variables.Random.RandomMesh,Variables.Random.RandomMeshNext);
		#endif
	}
	else
	{
		Nodes.HUD.MacetaActual[ Variables.Random.RandomMesh ]->setVisible( false );
		Nodes.HUD.MacetaNext[ Variables.Random.RandomMeshNext ]->setVisible( false );
		do 
		{
			probability = CSystem::Random() % 101;
			nrand = CSystem::Random() % Variables.Random.NroMeshes;
		}
		while( probability < Variables.Random.RandomProbability && nrand == Variables.Random.RandomMeshNext );

		Variables.Random.RandomMesh = Variables.Random.RandomMeshNext;
		Variables.Random.RandomMeshNext = nrand;

		#if defined(_DEBUG)
		COutput::Wprintf(L"Numero Aleatorio: actual=%d next=%d\n",Variables.Random.RandomMesh,Variables.Random.RandomMeshNext);
		#endif

		Nodes.HUD.MacetaActual[ Variables.Random.RandomMesh ]->setVisible( true );
		Nodes.HUD.MacetaNext[ Variables.Random.RandomMeshNext ]->setVisible( true );
	}

	CreateMacetaNode( Variables.Random.RandomMesh );
}

void BallsContextMain::StartBallAnimation(void)
{
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();

	irr::core::vector3df Rotation = irr::core::vector3df(0.0f,0.0f,-1.0f) * BallRotationSpeed;
	irr::scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator( Rotation );
	#if defined(_DEBUG)
	COutput::Wprintf( L"rotacion=(%f,%f,%f)\n",Rotation.X,Rotation.Y,Rotation.Z);
	#endif
	if( anim )
	{
		Nodes.Board.Lugh->addAnimator( anim );
		anim->drop();
	}
	Variables.Switch.StartBallMoving = true;
}


void BallsContextMain::MoveBall(bool saveClockTime)
{
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();

	if( saveClockTime )
	{
		Clock.SaveTime();
	}

	Clock.SetTime( 0.0f );

	Nodes.Board.Parent->removeAnimators();

	// Activo un nuevo temporizador
	Clock.EnableTimer( (real)( BallSpeed ) * 0.001f );

	// Calculo la siguiente posicion para la pelota
	Matrix.NextMove();

	//Puntaje += 10;
	//COutput::Wsprintf( Variables.String.Puntaje , L"%05d", Puntaje );

	// Creo la animacion de movimiento de la pelota
	irr::scene::ISceneNodeAnimator* anim = smgr->createFlyStraightAnimator( Matrix.InitFlyStraight , Matrix.EndFlyStraight , BallSpeed );
	if( anim )
	{
		Nodes.Board.Parent->addAnimator( anim );
		anim->drop();
	}

	Nodes.Board.Parent->setRotation( Matrix.OldRotationVector );
	COutput::Wprintf( L"rotacion=(%f,%f,%f)\n",Matrix.OldRotationVector.X,Matrix.OldRotationVector.Y,Matrix.OldRotationVector.Z);
	//COutput::Wprintf(L"Paso el tiempo\n");
}


void BallsContextMain::SelectEmptyMacetaNode(const sint32 &macetaPositionX,const sint32 &macetaPositionY)
{
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();
	irr::scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager(); //Colision Manager

	//wprintf(L"EmptyMacetaNode(%d,%d)\n",tmp_X,tmp_Y);

	//Declaro una linea de intersección
	irr::core::line3d<irr::f32> ray;
	//Con esto creo una linea en 3D usando las coordenadas del mouse y la camara activa
	ray = collMan->getRayFromScreenCoordinates(irr::core::position2d<irr::s32>(macetaPositionX,macetaPositionY));

	//No se si se utilizara esto...
	// Tracks the current intersection point with the level or a mesh
	irr::core::vector3df intersection;

	// Used to show with triangle has been hit
	irr::core::triangle3df hitTriangle;


	//Deselecciono lo que selecione previamente
	if( Nodes.Board.SelectedMaceta )
	{
		if( Nodes.Board.SelectedMaceta->getID() == BALL_EMPTYBLOCK )
		{
			Nodes.Board.SelectedMaceta->setVisible(true);
			//SelectedSceneNode->setDebugDataVisible(irr::scene::EDS_OFF);

			if( Nodes.Board.Maceta && Nodes.Board.Maceta->isVisible() )
			{
				Nodes.Board.Maceta->setVisible(false);
				Nodes.Board.Crosshair->setVisible(false);
			}
		}
		else
		{
			Nodes.Board.Crosshair->setVisible(false);
			//Nodes.Board.SelectedMaceta->setDebugDataVisible(irr::scene::EDS_OFF);
		}
	}

	//Chequeo colision
	Nodes.Board.SelectedMaceta = collMan->getSceneNodeAndCollisionPointFromRay(ray,intersection,hitTriangle,BALL_EMPTYBLOCK,0);

	//Seleccionar lo que seleccione
	if( Nodes.Board.SelectedMaceta )
	{
		uint16 nro = atoi( Nodes.Board.SelectedMaceta->getName() );

		//COutput::Wprintf(L"id=%d\n",nro);

		//SelectedSceneNode->setDebugDataVisible(irr::scene::EDS_BBOX);
		Nodes.Board.SelectedMaceta->setVisible(false);
		//GUIEditorMode = EGEM_MESH_PICKED;

		if( Nodes.Board.Maceta )
		{
			Nodes.Board.Maceta->setVisible(true);
			Nodes.Board.Maceta->setPosition( Nodes.Board.SelectedMaceta->getPosition() );

			//Nodes.Board.Crosshair->setPosition( Nodes.Board.SelectedMaceta->getPosition() + irr::core::vector3df(0.0f,Variables.Global.CrosshairHeight,0.0f) );
			//Nodes.Board.Crosshair->setVisible(true);
		}
	}
}




void BallsContextMain::SelectPutMacetaNode(const sint32 &macetaPositionX,const sint32 &macetaPositionY)
{
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();
	irr::scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager(); //Colision Manager

	//wprintf(L"PutMacetaNode(%d,%d)\n",tmp_X,tmp_Y);

	//Declaro una linea de intersección
	irr::core::line3d<irr::f32> ray;
	//Con esto creo una linea en 3D usando las coordenadas del mouse y la camara activa
	ray = collMan->getRayFromScreenCoordinates(irr::core::position2d<irr::s32>(macetaPositionX,macetaPositionY));

	//No se si se utilizara esto...
	// Tracks the current intersection point with the level or a mesh
	irr::core::vector3df intersection;

	// Used to show with triangle has been hit
	irr::core::triangle3df hitTriangle;

	//Deselecciono lo que selecione previamente
	if( Nodes.Board.SelectedMaceta )
	{
		if( Nodes.Board.SelectedMaceta->getID() == BALL_EMPTYBLOCK )
		{
			Nodes.Board.SelectedMaceta->setVisible(true);
			//SelectedSceneNode->setDebugDataVisible(irr::scene::EDS_OFF);

			if( Nodes.Board.Maceta && Nodes.Board.Maceta->isVisible() )
			{
				Nodes.Board.Maceta->setVisible(false);
			}
		}
		else
		{
			//Nodes.Board.SelectedMaceta->setDebugDataVisible(irr::scene::EDS_OFF);
			Nodes.Board.Crosshair->setVisible(false);
		}
	}

	//Chequeo colision
	Nodes.Board.SelectedMaceta = collMan->getSceneNodeAndCollisionPointFromRay(ray,intersection,hitTriangle,BALL_SELECTEDBLOCK,0);

	//Seleccionar lo que seleccione
	if( Nodes.Board.SelectedMaceta )
	{
		//uint16 nro = atoi( SelectedSceneNode->getName() );

		//COutput::Wprintf(L"id=%d\n",nro);
		//Nodes.Board.SelectedMaceta->setDebugDataVisible(irr::scene::EDS_HALF_TRANSPARENCY);
		//SelectedSceneNode->setVisible(false);
		//GUIEditorMode = EGEM_MESH_PICKED;
		Nodes.Board.Crosshair->setPosition( Nodes.Board.SelectedMaceta->getPosition() + irr::core::vector3df(0.0f,Variables.Global.CrosshairHeight,0.0f) );
		Nodes.Board.Crosshair->setVisible(true);
	}
}

bool BallsContextMain::DeleteMacetaNode(void)
{
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();

	if( Nodes.Board.SelectedMaceta && Nodes.Board.SelectedMaceta->getID() == BALL_SELECTEDBLOCK && RemainingBombs>0 )
	{
		uint16 index = atoi( Nodes.Board.SelectedMaceta->getName() )-1;

		//uint16 tx = index % MatrixRows ;
		//uint16 ty = index / MatrixCols ;

		RemainingBombs -= 1;
		COutput::Wsprintf( Variables.String.RemainingBombs , L"x%d", RemainingBombs);

		irr::scene::IAnimatedMeshSceneNode* node = 0;

		if( (node = smgr->addAnimatedMeshSceneNode( Resources.Mesh.Bbox ))!=NULL )
		{
			node->setPosition( Nodes.Board.SelectedMaceta->getPosition() );
			//Matrix.SetPosition( tx , ty , Nodes.Board.SelectedMaceta->getPosition() + irr::core::vector3df(0.0f,Variables.Global.BallHeight,0.0f));
			node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			node->setName( Nodes.Board.SelectedMaceta->getName() );
			node->setID( BALL_EMPTYBLOCK );

			Matrix.SetBlockType( index , BBD_EMPTY );

			irr::scene::ITriangleSelector *selector;
			selector = smgr->createTriangleSelector( Resources.Mesh.Bbox,node); 
			node->setTriangleSelector(selector);
			selector->drop();

			Nodes.Board.SelectedMaceta->setVisible(false);
			Nodes.Board.SelectedMaceta->setDebugDataVisible(irr::scene::EDS_OFF);
			//Nodes.Board.SelectedMaceta->removeAll();
			Nodes.Board.SelectedMaceta->remove();
			Nodes.Board.SelectedMaceta = NULL;
		}
		return true;
	}
	return false;
}

bool BallsContextMain::PutMacetaNode(void)
{
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();

	XEffects::EffectHandler *effect = GameDevices->Effects->GetEffects();

	if( Nodes.Board.SelectedMaceta )
	{
		irr::scene::IAnimatedMeshSceneNode* node = 0;

		irr::core::vector3df position = Nodes.Board.SelectedMaceta->getPosition();
		#if defined(_DEBUG)
		COutput::Wprintf(L"PosicionNodo: (%f,%f,%f)\n",position.X,position.Y,position.Z);
		#endif

		if( (node = smgr->addAnimatedMeshSceneNode( Resources.Mesh.Maceta[ Variables.Random.RandomMesh ] ))!=NULL )
		{
			//node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);  //this is important to use
			node->setPosition( Nodes.Board.SelectedMaceta->getPosition() );
			node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			//node->addShadowVolumeSceneNode();

			//irr::s32 flags = node->getID();
			//flags = BALL_SELECTEDBLOCK | flags;
			node->setID( BALL_SELECTEDBLOCK );
			node->setName( Nodes.Board.SelectedMaceta->getName() );

			irr::scene::ITriangleSelector *selector;
			selector = smgr->createTriangleSelector( Resources.Mesh.Maceta[ Variables.Random.RandomMesh ] , node ); 
			node->setTriangleSelector(selector);

			effect->addShadowToNode(node);

			selector->drop();

			uint16 index = atoi( Nodes.Board.SelectedMaceta->getName() )-1;
			
			#if defined(_DEBUG)
			printf("Nodo:%s\n",Nodes.Board.SelectedMaceta->getName());
			COutput::Wprintf(L"IndiceName:%d\n",index);
			#endif
			uint16 type;
			switch( Variables.Random.RandomMesh )
			{
				case 0:{ type=BBD_VERTICAL;break; };
				case 1:{ type=BBD_HORIZONTAL;break; };
				case 2:{ type=BBD_CROSS;break; };
				case 3:{ type=BBD_RIGHTDOWN;break; };
				case 4:{ type=BBD_LEFTDOWN;break; };
				case 5:{ type=BBD_DOWNRIGHT;break; };
				case 6:{ type=BBD_DOWNLEFT;break; };
			}

			Matrix.SetBlockType( index , type );
			#if defined(_DEBUG)
			Matrix.PrintMatrix();
			#endif

			Nodes.Board.SelectedMaceta->setVisible(false);
			Nodes.Board.SelectedMaceta->setDebugDataVisible(irr::scene::EDS_OFF);
			//Nodes.Board.SelectedMaceta->removeAll();

			effect->removeShadowFromNode(Nodes.Board.SelectedMaceta);

			Nodes.Board.SelectedMaceta->remove();
			Nodes.Board.SelectedMaceta = NULL;

			// Cambio el mesh siguiente
			CreateRandomMaceta();
		}
		return true;
	}
	return false;
}

void BallsContextMain::CreateMacetaNode(uint16 macetaId)
{
	irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();

	if( Nodes.Board.Maceta )
	{
		Nodes.Board.Maceta->setVisible(false);
		Nodes.Board.Maceta->setDebugDataVisible(irr::scene::EDS_OFF);
		Nodes.Board.Maceta->remove();
	}

	if ( (Nodes.Board.Maceta = smgr->addAnimatedMeshSceneNode( Resources.Mesh.Maceta[ macetaId ] ))!=NULL )
	{
		Nodes.HUD.MacetaActual[ Variables.Random.RandomMesh ]->setVisible( false );
		Nodes.HUD.MacetaActual[ macetaId ]->setVisible( true );
		Variables.Random.RandomMesh = macetaId;
		
		#if defined(_DEBUG)
		switch( macetaId )
		{
			case 0:{ COutput::Wprintf(L"Random: VERTICAL\n");break; };
			case 1:{ COutput::Wprintf(L"Random: HORIZONTAL\n");break; };
			case 2:{ COutput::Wprintf(L"Random: CROSS\n");break; };
			case 3:{ COutput::Wprintf(L"Random: RIGHTDOWN\n");break; };
			case 4:{ COutput::Wprintf(L"Random: LEFTDOWN\n");break; };
			case 5:{ COutput::Wprintf(L"Random: DOWNRIGHT\n");break; };
			case 6:{ COutput::Wprintf(L"Random: DOWNLEFT\n");break; };
		}
		#endif
		Nodes.Board.Maceta->setVisible(false);
		//Nodes.Board.Maceta->setDebugDataVisible(irr::scene::EDS_HALF_TRANSPARENCY);
		Nodes.Board.Maceta->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}
}
void BallsContextMain::UnlockTrophy(uint16 trophyId)
{
	if( !TrophiesManager.IsUnlockedTrophy(trophyId) )
	{
		AchievementUnlocked = true;
		TrophiesManager.UnlockTrophy(trophyId);
		TrophyClock.EnableTimer(4.0f);
		Nodes.HUD.Achievement->setVisible(true);
		if( Resources.Sound.Achievement )
		{
			Resources.Sound.Achievement->stop();
			Resources.Sound.Achievement->setPosition(0);
			Resources.Sound.Achievement->play();
		}
		TrophiesManager.SaveTrophies();
	}
}