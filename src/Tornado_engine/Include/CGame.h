#ifndef ___Tornado__Game__H___
#define ___Tornado__Game__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Juego                                    *
 * Archivo Fuente: CGame.h                                            *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CConfig.h"
#include "CVideo.h"
#include "CAudio.h"
#include "CMachine.h"
#include "CEffects.h"
#include "CAudioManager.h"
#include "CSceneManager.h"
#include "CGUIEnvironment.h"

namespace Tornado
{
	//! Clase Juego
	class CGame
	{

	private:

		//! Título de la ventana
		static wchar_t __Title_Window[ __TORNADO_PATH_LENGTH ];

		//! Nombre del Programa
		static wchar_t __Title_Software[ __TORNADO_PATH_LENGTH ];

		//! Nombre del Equipo de Desarrollo
		static wchar_t __Title_Team[ __TORNADO_PATH_LENGTH ];

		//! Versión del Juego
		static wchar_t __Software_Version[ __TORNADO_PATH_LENGTH ];

		//! Activar XEffects
		bool XEffects;

		//! Modo 3D-Anaglyph
		bool Anaglyph3DMode;

		#if defined(WIN32)
		//! Modo Windows 32-bit (WINAPI)
		bool Win32Mode;
		#endif

		//! Modo Ventana de tamaño variable
		bool ResizableWindow;

		void RegisterGlobalConfig(void);
		void PrepareGlobalConfig(void);

		bool InitVideo(void);
		bool InitAudio(void);
		bool InitMachine(void);
		bool InitEffects(void);
		bool InitAudioManager(void);
		bool InitSceneManager(void);
		bool InitGUIEnvironment(void);
		virtual bool InitContexts(void);
		
		void Bucle(void);
		#if defined(WIN32)
		void BucleWin32(void);
		#endif
		void BucleAnaglyph3D(void);

	protected:

		//! Configuración
		CConfig Config;

		//! Video
		CVideo Video;

		//! Audio
		CAudio Audio;

		//! Máquina de Contextos
		CMachine Machine;

		//! Efectos
		CEffects Effects;

		//! Manejador de Audio
		CAudioManager AudioManager;

		//! Manejador de Escena
		CSceneManager SceneManager;

		//! Ambiente GUI
		CGUIEnvironment GUIEnvironment;

		virtual void RegisterMiscConfig(void);
		virtual void PrepareMiscConfig(void);

		virtual void PrepareAll(void);

	public:
		__TORNADO_DLL_EXPORT CGame();
		__TORNADO_DLL_EXPORT ~CGame();

		__TORNADO_DLL_EXPORT void Begin(void);

		/**
		 * \brief Activa el Modo 3D-Anaglyph
		 * \note Este modo es experimental y no funciona como debe
		 */
		inline void EnableAnaglyph3DMode(void)
		{
			#if defined(_DEBUG)
			COutput::Wprintf(L"This is an experimental feature\n");
			#endif
			Anaglyph3DMode = true;
		}

		/**
		 * \brief Activar el sistema XEffects para iluminación y shaders
		 */
		inline void EnableXEffects(void)
		{
			XEffects = true;
		}

		#if defined(WIN32)
		/**
		 * \brief Activa el Modo Win32 (sólo Windows)
		 * \note Sólo funcionará si se realiza antes de inicializar el Video
		 */
		inline void EnableWin32Mode(void)
		{
			Win32Mode = true;
		}
		#endif

		/**
		 * \brief Activa la ventana para tamaño variable (sólo en ventana)
		 */
		inline void EnableResizableWindow(void)
		{
			ResizableWindow = true;
		}

		/**
		 * \brief Establece los parámetros para XEffects
		 * \param useVSMShadows Activar Sombras VSM
		 * \param useRoundSpotLights Activar Sombras Spot redondeadas
		 * \param use32BitDepthBuffers Activar Buffer de profundidad de 32bit
		 */
		inline void SetXEffectsParameters(	bool useVSMShadows ,
											bool useRoundSpotLights ,
											bool use32BitDepthBuffers )
		{
			Effects.SetParameters( useVSMShadows , useRoundSpotLights , use32BitDepthBuffers );
		}

		__TORNADO_DLL_EXPORT void SetTitleWindow(const wchar_t *title);

		__TORNADO_DLL_EXPORT void SetTitleSoftware(const wchar_t *title);

		__TORNADO_DLL_EXPORT void SetTitleTeam(const wchar_t *title);

		__TORNADO_DLL_EXPORT void SetSoftwareVersion(const wchar_t *version);

		__TORNADO_DLL_EXPORT wchar_t *GetSoftwareVersion(void);
	};
};

#endif
