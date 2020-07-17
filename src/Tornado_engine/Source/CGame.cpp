/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Codigo Fuente de Clase Juego                               *
 * Archivo Fuente: CGame.cpp                                          *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CGame.h"
#include "CMath.h"

#include <iostream>
#include <string>
#include <time.h>


#include "CSystem.h"
#include "SVideoConfig.h"
#include "Version.h"
#if !defined(WIN32)
#include <stddef.h>
#include <inttypes.h>
#endif
namespace Tornado {

	//! Título de la ventana
	wchar_t CGame::__Title_Window[ __TORNADO_PATH_LENGTH ] = L"Tornado_engine Demo";

	//! Nombre del Programa
	wchar_t CGame::__Title_Software[ __TORNADO_PATH_LENGTH ] = L"Tornado Demo";

	//! Nombre del Equipo de Desarrollo
	wchar_t CGame::__Title_Team[ __TORNADO_PATH_LENGTH ] = L"FrostDisk";

	//! Versión del Juego
	wchar_t CGame::__Software_Version[ __TORNADO_PATH_LENGTH ] = L"1.0.0";

	/**
	 * \brief Registra los campos globales de configuracion del juego
	 */
	void CGame::RegisterGlobalConfig(void)
	{
		Config.RegisterConfigElement(L"video",L"driver",L"1");
		Config.RegisterConfigElement(L"video",L"bpp",L"16");
		Config.RegisterConfigElement(L"video",L"aa",L"false");
		Config.RegisterConfigElement(L"video",L"fs",L"false");
		Config.RegisterConfigElement(L"video",L"vsync",L"false");
		Config.RegisterConfigElement(L"video",L"stencil",L"false");
		Config.RegisterConfigElement(L"video",L"anaglyph",L"false");
		Config.RegisterConfigElement(L"video",L"width",L"800");
		Config.RegisterConfigElement(L"video",L"height",L"600");
		Config.RegisterConfigElement(L"audio",L"music",L"50");
		Config.RegisterConfigElement(L"audio",L"sound",L"40");
	}

	/**
	 * \brief Carga los campos globales de configuracion del juego
	 */
	void CGame::PrepareGlobalConfig(void)
	{
		SVideoConfig auxVideoConfig;
		SAudioConfig auxAudioConfig;
		wchar_t *auxValue;
		#if !defined(WIN32)
		#warning Notar que GetConfigElements pide memoria luego de usarla devolverla o recliclarla...
		#endif

		if( (auxValue = Config.GetConfigElement(L"video",L"driver"))!=NULL)
		{
			auxVideoConfig.Driver = CMath::Wtoi( auxValue );
			//CSystem::Free( auxValue , sizeof(auxValue) );
		}
		if( (auxValue = Config.GetConfigElement(L"video",L"bpp"))!=NULL)
		{
			auxVideoConfig.Bits = CMath::Wtoi( auxValue );
		}

		if( (auxValue = Config.GetConfigElement(L"video",L"aa"))!=NULL)
		{
			auxVideoConfig.Antialiasing = !wcscmp(auxValue,L"true") ? true : false ;
		}

		if( (auxValue = Config.GetConfigElement(L"video",L"fs"))!=NULL)
		{
			auxVideoConfig.Fullscreen = !wcscmp(auxValue,L"true") ? true : false ;
		}

		if( (auxValue = Config.GetConfigElement(L"video",L"vsync"))!=NULL)
		{
			auxVideoConfig.VerticalSync = !wcscmp(auxValue,L"true") ? true : false ;
		}

		if( (auxValue = Config.GetConfigElement(L"video",L"stencil"))!=NULL)
		{
			auxVideoConfig.StencilShadow = !wcscmp(auxValue,L"true") ? true : false ;
		}

		if( (auxValue = Config.GetConfigElement(L"video",L"anaglyph"))!=NULL)
		{
			auxVideoConfig.AnaglyphMode = !wcscmp(auxValue,L"true") ? true : false ;
		}

		if( (auxValue = Config.GetConfigElement(L"video",L"width"))!=NULL)
		{
			auxVideoConfig.Width = CMath::Wtoi( auxValue );
    	}

		if( (auxValue = Config.GetConfigElement(L"video",L"height"))!=NULL)
		{
			auxVideoConfig.Height = CMath::Wtoi( auxValue );
		}

		if( (auxValue = Config.GetConfigElement(L"audio",L"music"))!=NULL)
		{
			auxAudioConfig.Music = CMath::Wtoi( auxValue );
		}
		if( (auxValue = Config.GetConfigElement(L"audio",L"sound"))!=NULL)
		{
			auxAudioConfig.Sound = CMath::Wtoi( auxValue );
		}

		Video.SetVideoConfig( &auxVideoConfig );
		Audio.SetAudioConfig( &auxAudioConfig );
	}

	/**
	 * \brief Inicializa el Video
	 * \return TRUE si el Video ha sido inicializado con éxito, FALSE en caso contrario.
	 */
	inline bool CGame::InitVideo(void)
	{
		#if defined(WIN32)
		if( Win32Mode && !Video.InitWin32( __Title_Window ) )
		{
			return false;
		}
		#endif
		return Video.Init( __Title_Window , ResizableWindow );
	}

	/**
	 * \brief Inicializa el Audio
	 * \return TRUE si el Audio ha sido inicializado con éxito, FALSE en caso contrario.
	 */
	inline bool CGame::InitAudio(void)
	{
		return Audio.Init();
	}

	/**
	 * \brief Inicializa la Máquina
	 * \return TRUE si la Máquina ha sido inicializada con éxito, FALSE en caso contrario.
	 */
	inline bool CGame::InitMachine(void)
	{
		Video.SetEventReceiver( &Machine );

		SGameDevices *Devices = new SGameDevices;
		Devices->Config = &Config;
		Devices->Audio = &Audio;
		Devices->Video = &Video;
		Devices->Effects = XEffects ? &Effects : NULL;
		Devices->AudioManager = &AudioManager; 
		Devices->SceneManager = &SceneManager;
		Devices->GUIEnvironment = &GUIEnvironment;

		Machine.SetGameDevices( Devices );
		return Machine.Init();
	}

	/**
	 * \brief Inicializa los Efectos
	 * \return TRUE si los Efectos han sido inicializados con éxito, FALSE en caso contrario.
	 */
	inline bool CGame::InitEffects(void)
	{
		Effects.SetVideoDevice( Video.GetVideoDevice() );
		return Effects.Init();
	}

	/**
	 * \brief Inicializa el Manejador de Audio
	 * \return TRUE si el Manejador de Audio ha sido inicializado con éxito, FALSE en caso contrario.
	 */
	inline bool CGame::InitAudioManager(void)
	{
		AudioManager.SetAudioDevice( Audio.GetAudioDevice() );
		AudioManager.SetFileSystem( Video.GetVideoDevice()->getFileSystem() );
		return AudioManager.Init();
	}

	/**
	 * \brief Inicializa el Manejador de Escena
	 * \return TRUE si el Manejador de Escena ha sido inicializado con éxito, FALSE en caso contrario.
	 */
	inline bool CGame::InitSceneManager(void)
	{
		SceneManager.SetVideoDevice( Video.GetVideoDevice() );
		return SceneManager.Init();
	}

	/**
	 * \brief Inicializa el Ambiente de GUI
	 * \return TRUE si el Ambiente de GUI ha sido inicializado con éxito, FALSE en caso contrario.
	 */
	inline bool CGame::InitGUIEnvironment(void)
	{
		GUIEnvironment.SetVideoDevice( Video.GetVideoDevice() );
		return GUIEnvironment.Init();
	}

	/**
	 * \brief Inicializa los contextos del juego
	 * \return TRUE si los contextos del juego han sido inicializados con éxito, FALSE en caso contrario.
	 */
	bool CGame::InitContexts(void)
	{
		return true;
	}

	/**
	 * \brief Ciclo de procesamiento
	 */
	void CGame::Bucle(void)
	{
		uint32 then = Video.GetTime();

		//int lastFPS = -1;

		/*std::wstring str = TITLE_WINDOW;
		str += driver->getName();
		str += " FPS:";
		str += fps;*/

		// Dispositivo de video
		//irr::video::IVideoDriver* driver = Video.GetVideoDevice()->getVideoDriver();

		while( Video.Run() )
		{
			// Calculando el delta entre frames
			const uint32 now = Video.GetTime();
			const real deltaTime = (real)(now - then) * 0.001f; // Time in seconds
			then = now;

			// Comienza el dibujado de escena
			Video.BeginScene();

			// Dibujar todos los elementos
			if( !Machine.Run( deltaTime ) && !Machine.Update() )
			{
				Video.Close();
			}

			// Termina el dibujado de escena
			Video.EndScene();
		}
	}

	#if defined(WIN32)
	/**
	 * \brief Ciclo de procesamiento para Modo Win32
	 */
	void CGame::BucleWin32(void)
	{
		Video.Show();
		Video.Update();

		uint32 then = Video.GetTime();
		real elapsed = 0;

		// Dispositivo de video
		irr::video::IVideoDriver* driver = Video.GetVideoDevice()->getVideoDriver();

		while( Video.Run() )
		{
			// Calculando el delta entre frames
			const uint32 now = Video.GetTime();
			const real deltaTime = (real)(now - then) * 0.001f; // Time in seconds
			then = now;

			// Comienza el dibujado de escena
			Video.BeginScene();

			// Dibujar todos los elementos
			if( !Machine.Run( deltaTime ) && !Machine.Update() )
			{
				Video.Close();
			}

			// Termina el dibujado de escena
			Video.EndScene();
		}
	}
	#endif


	/**
	 * \brief Ciclo de procesamiento para Modo 3D-Anaglyph
	 * \bug <b>[leve]</b> Los cálculos de cámara son incorrectos y la visualización es complemante erronea.
	 */
	void CGame::BucleAnaglyph3D(void)
	{
		uint32 then = Video.GetTime();

		COutput::Wprintf(L"Modo 3D-Anaglyph\n");

		// Dispositivo de video
		irr::video::IVideoDriver* driver = Video.GetVideoDevice()->getVideoDriver();

		while( Video.Run() )
		{
			// Calculando el delta entre frames
			const uint32 now = Video.GetTime();
			const real deltaTime = (real)(now - then) * 0.001f; // Time in seconds
			then = now;

			irr::scene::ICameraSceneNode *camera = SceneManager.GetCamera();

			if( camera )
			{
				irr::core::vector3df oldPosition = camera->getPosition();
				irr::core::vector3df oldTarget = camera->getTarget();

				irr::core::matrix4 startMatrix = camera->getAbsoluteTransformation();

				irr::core::vector3df focusPoint = ( camera->getTarget() - camera->getAbsolutePosition() ).setLength(1) + camera->getAbsolutePosition() ;

				//Left eye...
				irr::core::vector3df leftEye;
				irr::core::matrix4 leftMove;
				leftMove.setTranslation( irr::core::vector3df(-0.01f,0.0f,0.0f) );
				leftEye = (startMatrix * leftMove).getTranslation();


				driver->beginScene(true,true,irr::video::SColor(0,0xC8,0xC8,0xFF));

				driver->getOverrideMaterial().Material.ColorMask = irr::video::ECP_RED;
				driver->getOverrideMaterial().EnableFlags = irr::video::EMF_COLOR_MASK;
				driver->getOverrideMaterial().EnablePasses = irr::scene::ESNRP_SKY_BOX + irr::scene::ESNRP_SOLID + irr::scene::ESNRP_TRANSPARENT + irr::scene::ESNRP_TRANSPARENT_EFFECT + irr::scene::ESNRP_SHADOW;

				camera->setPosition( leftEye );
				camera->setTarget( focusPoint );

				Machine.Draw();

				//Right eye...
				irr::core::vector3df rightEye;
				irr::core::matrix4 rightMove;
				rightMove.setTranslation ( irr::core::vector3df(0.01f,0.0f,0.0f) );
				rightEye = (startMatrix * rightMove).getTranslation();

				//clear the depth buffer
				driver->clearZBuffer();

				driver->getOverrideMaterial().Material.ColorMask = irr::video::ECP_GREEN + irr::video::ECP_BLUE;
				driver->getOverrideMaterial().EnableFlags = irr::video::EMF_COLOR_MASK;
				driver->getOverrideMaterial().EnablePasses = irr::scene::ESNRP_SKY_BOX + irr::scene::ESNRP_SOLID + irr::scene::ESNRP_TRANSPARENT + irr::scene::ESNRP_TRANSPARENT_EFFECT + irr::scene::ESNRP_SHADOW;

				camera->setPosition( rightEye );
				camera->setTarget( focusPoint );

				Machine.Draw();

				driver->endScene();

				driver->getOverrideMaterial().Material.ColorMask = irr::video::ECP_ALL;
				driver->getOverrideMaterial().EnableFlags = 0;
				driver->getOverrideMaterial().EnablePasses = 0;

				camera->setPosition( oldPosition );
				camera->setTarget( oldTarget );
			}

			// Dibujar todos los elementos
			if( !Machine.Next( deltaTime ) )
			{
				Machine.Update();
			}
		}
	}

	/**
	 * \brief Registra los campos miscelaneos de configuracion del juego
	 */
	void CGame::RegisterMiscConfig(void)
	{

	}

	/**
	 * \brief Carga los campos miscelaneos de configuracion del juego
	 */
	void CGame::PrepareMiscConfig(void)
	{

	}

	/**
	 * \brief Prepara todos los elementos del juego
	 */
	void CGame::PrepareAll(void)
	{
	}

	/**
	 * \brief Constructor de Clase
	 */
	CGame::CGame() :
		Config(),
		Video(),
		Audio(),
		Machine(),
		Effects(),
		AudioManager(),
		SceneManager(),
		GUIEnvironment(),
		XEffects(false),
		Anaglyph3DMode(false),
		#if defined(WIN32)
		Win32Mode(false),
		#endif
		ResizableWindow(false)
	{
		// Esto parece que no funciona bien
		srand( (unsigned)time(NULL) );
	}

	/**
	 * \brief Destructor de Clase
	 */
	CGame::~CGame()
	{
	}

	/**
	 * \brief Inicializa los elementos del Juego
	 */
	void CGame::Begin(void)
	{

		#if defined(_DEBUG)
		COutput::Wprintf(L"%ls\n",__Copyright);
		COutput::Wprintf(L"%ls\n",__Version);
		#endif

		// Configuración
		RegisterGlobalConfig();
		RegisterMiscConfig();
		Video.RegisterVideoModes();
		Config.SetFoldersName( __Title_Software , __Title_Team );
		Config.CreateDefaultConfig();
		Config.LoadConfigFile();
		PrepareGlobalConfig();
		PrepareMiscConfig();
		Config.SaveConfigFile();

		// Elementos propios de juego
		if( !InitVideo() ||
			!InitAudio() )
		{
			#if defined(_DEBUG)
			COutput::Wprintf(L"There was a problem initializing Tornado's Core\n");
			#endif
			return;
		}

		// Elementos especiales de juego
		if( !InitAudioManager() ||
			!InitSceneManager() ||
			!InitGUIEnvironment() )
		{
			#if defined(_DEBUG)
			COutput::Wprintf(L"There was a problem initializing Components\n");
			#endif
			return;
		}

		// Inicializar XEffects
		if( XEffects &&
			!InitEffects() )
		{
			#if defined(_DEBUG)
			COutput::Wprintf(L"There was a problem initializing XEffects module\n");
			#endif
			return;
		}

		// Elementos personalizados
		PrepareAll();

		// Elementos personalizados
		if( !InitContexts() ||
			!InitMachine() )
		{
			#if defined(_DEBUG)
			COutput::Wprintf(L"There was a problem initializing Contexts Machine\n");
			#endif
			return;
		}

		if( Anaglyph3DMode )
		{
			BucleAnaglyph3D();
		}
		else 
		{
			#if defined(WIN32)
			Win32Mode ?	BucleWin32() : Bucle();
			#else
			Bucle();
			#endif
		}

		// Proceso de cerrado y liberado de memoria
		Machine.Close();

		AudioManager.Clear();
		SceneManager.Clear();
		GUIEnvironment.Clear();
		Effects.Clear();

		Video.End();
		Audio.End();
	}

	/**
	 * \brief Asigna el Título de la ventana
	 * \param Title Título a asignar
	 */
	void CGame::SetTitleWindow( const wchar_t *windowTitle )
	{
		COutput::Wcscpy( __Title_Window , __TORNADO_PATH_LENGTH , windowTitle );
	}

	/**
	 * \brief Asigna el Título de la aplicación
	 * \param Title Título a asignar
	 */
	void CGame::SetTitleSoftware( const wchar_t *softwareTitle )
	{
		COutput::Wcscpy( __Title_Software , __TORNADO_PATH_LENGTH , softwareTitle );
	}

	/**
	 * \brief Asigna el Título del equipo
	 * \param Title Título a asignar
	 */
	void CGame::SetTitleTeam( const wchar_t *teamTitle )
	{
		COutput::Wcscpy( __Title_Team , __TORNADO_PATH_LENGTH , teamTitle );
	}

	/**
	 * \brief Asigna la versión del juego
	 * \param Version Versión a asignar
	 */
	void CGame::SetSoftwareVersion( const wchar_t *softwareVersion )
	{
		COutput::Wcscpy( __Software_Version , __TORNADO_PATH_LENGTH , softwareVersion );
	}

	wchar_t *CGame::GetSoftwareVersion(void)
	{
		return __Software_Version;
	}
}

