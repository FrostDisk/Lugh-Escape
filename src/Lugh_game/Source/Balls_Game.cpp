#include "Balls_Game.h"
#include "Balls_Contexts.h"

// Inicializa los Contextos
bool BallsGame::InitContexts(void)
{
	Machine.AddContext( &cSplash );
	Machine.AddContext( &cTitle );
	Machine.AddContext( &cMain );
	Machine.AddContext( &cScoreboard );
	Machine.AddContext( &cCredits );
	Machine.AddContext( &cTrophies );
#if defined(_DEBUG)
	Machine.SetTitleContext( &cTitle );
#else
	Machine.SetTitleContext( &cSplash );
#endif
	

	return true;
}
// Registra la Configuracion Opcional
void BallsGame::RegisterMiscConfig(void)
{
}

// Registra la Configuracion Opcional
void BallsGame::PrepareMiscConfig(void)
{
}

// Prepara todos los elementos
void BallsGame::PrepareAll(void)
{
	//#if defined(_DEBUG)
	Video.AddFileArchive("./data/",irr::io::EFAT_FOLDER);
	//#else
	//Video.AddFileArchive("Lugh.data",irr::io::EFAT_ZIP);
	//#endif
}

// Constructor de Clase
BallsGame::BallsGame() :	cSplash(ID_SPLASH),
							#if defined(_DEBUG)
							cTitle(ID_TITLE, true, GetSoftwareVersion()),
							cMain(ID_MAIN, true),
							cScoreboard(ID_SCOREBOARD),
							cCredits(ID_CREDITS),
							cTrophies(ID_TROPHIES, true)
							#else
							cTitle(ID_TITLE, true, GetSoftwareVersion()),
							cMain(ID_MAIN, true),
							cScoreboard(ID_SCOREBOARD),
							cCredits(ID_CREDITS),
							cTrophies(ID_TROPHIES, true)
							#endif
{
}
