#include <windows.h>
#include "Balls.h"

#if !defined(_DEBUG) && defined(WIN32)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hpre, LPSTR cmd, int cc)
#else 
int main(int argc,char **argv)
#endif
{
	BallsGame Juego;

	//Crear la ventana como WinAPI
	//Juego.EnableWin32Mode();

	//Activar efectos especiales
	Juego.EnableXEffects();

	//Característica experimental
	//Juego.EnableAnaglyph3DMode();

	wchar_t version[15];
	wchar_t title[50];

	#if defined(_DEBUG)
	COutput::Wsprintf( version , L"%d.%d.%d-debug", __BALLS_VERSION_MAJOR, __BALLS_VERSION_MINOR, __BALLS_VERSION_REVISION);
	COutput::Wsprintf( title , L"El Escape de Lugh [%s]", version);
	#else
	COutput::Wsprintf( version , L"%d.%d.%d", __BALLS_VERSION_MAJOR, __BALLS_VERSION_MINOR, __BALLS_VERSION_REVISION);
	COutput::Wsprintf( title , L"El Escape de Lugh [%s]", version);
	#endif
	Juego.SetTitleWindow( title );
	Juego.SetTitleSoftware(L"Lugh Escape");
	Juego.SetTitleTeam(L"FrostDisk");
	Juego.SetSoftwareVersion( version );
	
	Juego.Begin();
}
