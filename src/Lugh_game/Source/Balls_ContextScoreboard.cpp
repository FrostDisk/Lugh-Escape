#include "Balls_ContextScoreboard.h"
#include "Balls_Contexts.h"

using namespace Tornado;

BallsContextScoreboard::BallsContextScoreboard(uint16 contextId) : CContext(contextId),
				Scoreboard(10),
				Clock(),
				HUD(NULL),
				NameFont(NULL),
				ScoreMusic(NULL),
				BackgroundImage(NULL),
				TitleImage(NULL),
				TableNameImage(NULL),
				TableScoreImage(NULL),
				TableLevelImage(NULL),
				TableLineImage(NULL),
				BackgroundPosition(),
				BackgroundRect(),
				TitlePosition(),
				TableNamePosition(),
				TableScorePosition(),
				TableLevelPosition(),
				TableLinePosition()
{
}

BallsContextScoreboard::~BallsContextScoreboard()
{
	#if defined(_DEBUG)
	COutput::Wprintf(L"Destruyendo BallsContextScoreboard(%d)\n",GetId());
	#endif
}

bool BallsContextScoreboard::Init(void)
{
	irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
	irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
	irr::io::IFileSystem *file = GameDevices->Video->GetVideoDevice()->getFileSystem();

	HUD = env->getFont(L"font/fontpuntaje.xml");

	wchar_t Path[ __TORNADO_PATH_LENGTH ];
	if( GameDevices->Config->CreateFilenameProfilePath( Path , L"scores.xml" , EPL_SAVEDATA ) )
	{
		Scoreboard.SetFilename( Path );
	}

	uint16 w2 = Width/2;
	uint16 h2 = Height/2;

	for(irr::s32 i=0 ; i<10 ; i++)
	{
		//60 x 35
		Positions[i].Id = irr::core::rect<irr::s32>( w2-320 , h2-170 + i*45 , w2-255 , h2-140 + i*45 );

		// 200 x 35
		Positions[i].Name = irr::core::rect<irr::s32>( w2-232 , h2-170 + i*45 , w2-32 , h2-140 + i*45 );

		// 130 x 35
		Positions[i].Score = irr::core::rect<irr::s32>( w2+10 , h2-170 + i*45 , w2+140 , h2-140 + i*45 );

		// 130 x 35
		Positions[i].Level = irr::core::rect<irr::s32>( w2+200 , h2-170 + i*45 , w2+230 , h2-140 + i*45 );
	}

	ScoreMusic = GameDevices->AudioManager->CreateOutputStream( file->createAndOpenFile("music/lugh_scoreboard.ogg") , true , audiere::FF_OGG );

	BackgroundImage = driver->getTexture("loading/tiled_99.jpg");
	TitleImage = driver->getTexture("score/puntajes_maximos_01.png");
	//TableNameImage = driver->getTexture("score/ranking_name.png");
	//TableScoreImage = driver->getTexture("score/ranking_score.png");
	//TableLevelImage = driver->getTexture("score/ranking_level.png");
	//TableLineImage = driver->getTexture("score/ranking_line.png");

	BackgroundPosition = irr::core::vector2d<irr::s32>( 0 , 0 );
	BackgroundRect = irr::core::rect<irr::s32>( 0 , 0 , Width , Height );

	TitlePosition = irr::core::vector2d<irr::s32>( w2-372 , h2-280 );
	//TableNamePosition = irr::core::vector2d<irr::s32>( w2-260 , h2-235 );
	//TableScorePosition = irr::core::vector2d<irr::s32>( w2-15 , h2-235 );
	//TableLevelPosition = irr::core::vector2d<irr::s32>( w2+180 , h2-235 );
	//TableLinePosition = irr::core::vector2d<irr::s32>( w2-384 , h2-187 );

	return true;
}

void BallsContextScoreboard::Prepare(void)
{
	irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
	irr::gui::IGUISkin *skin = GameDevices->GUIEnvironment->GetGUISkin();

	GameDevices->Video->SetVideoColor( irr::video::SColor(0xFF,0x99,0x99,0x99) );
	GameDevices->Video->SetCursorVisibility(true);


	if( Scoreboard.LoadScoreboard() )
	{
		#if defined(_DEBUG)
		COutput::Wprintf(L"Se terminaron de leer los datos de puntaje\n");
		#endif
	}

	env->addImage( TitleImage , TitlePosition );
	//env->addImage( TableNameImage , TableNamePosition );
	//env->addImage( TableScoreImage , TableScorePosition );
	//env->addImage( TableLevelImage , TableLevelPosition );
	//env->addImage( TableLineImage , TableLinePosition );

	if( ScoreMusic )
	{
		ScoreMusic->stop();
		ScoreMusic->setPosition(0);
		ScoreMusic->play();
	}
}

void BallsContextScoreboard::Next(real delta)
{
}

void BallsContextScoreboard::Draw(void)
{
	irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;

	driver->draw2DImage(	BackgroundImage  ,
							BackgroundPosition ,
							BackgroundRect );

	GameDevices->SceneManager->DrawScene( driver );
	GameDevices->GUIEnvironment->DrawGUI( driver );

	wchar_t Name[ BUFFER_SIZE ];
	uint16 Score=0,Level=0,i=0;

	Scoreboard.BeginFetch();
	while( Scoreboard.GetItem( Name , &Score , &Level ) ){

		wchar_t String[ BUFFER_SIZE ];
		COutput::Wsprintf( String , L"%d." , i+1 );
		HUD->draw( String , Positions[i].Id , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );

		//COutput::Wsprintf( String , L"%ls" , Name );
		HUD->draw( Name , Positions[i].Name , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );

		COutput::Wsprintf( String , L"%06d" , Score );
		HUD->draw( String , Positions[i].Score , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );

		COutput::Wsprintf( String , L"%3d" , Level );
		HUD->draw( String , Positions[i].Level , irr::video::SColor(0xFF,0xFF,0xFF,0xFF) );

		i++;
	}
}

void BallsContextScoreboard::Close(void)
{
}

void BallsContextScoreboard::End(void)
{
	if( ScoreMusic )
	{
		ScoreMusic->stop();
	}
}


bool BallsContextScoreboard::OnKeyInput(	const uint16 &key,
											const wchar_t &keyChar,
											const bool isCtrl,
											const bool isShift,
											const bool isPressedDown )
{
	/*if( tmp_isPressedDown ){
		Finalize(ID_TITLE);
	}*/
	return false;
}

bool BallsContextScoreboard::OnMouseInput(	const uint16 &eventType,
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
		Finalize(ID_TITLE);
	}
	return false;
}
