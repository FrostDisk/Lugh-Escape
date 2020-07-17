#ifndef ___Tornado__GameDevices__H___
#define ___Tornado__GameDevices__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Estructura Dispositivos de Juego               *
 * Archivo Fuente: SGameDevices.h                                     *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

namespace Tornado
{
	class CConfig;
	class CAudio;
	class CVideo;
	class CWorld;
	class CEffects;
	class CAudioManager;
	class CSceneManager;
	class CGUIEnvironment;

	//! Estructura Dispositivos de Juego
	struct SGameDevices
	{

		//! Constructor de Estructura
		SGameDevices() :
			Config(NULL),
			Audio(NULL),
			Video(NULL),
			World(NULL),
			Effects(NULL),
			AudioManager(NULL),
			SceneManager(NULL),
			GUIEnvironment(NULL)
		{
		}

		//! Constructor copia de Estructura
		SGameDevices( const SGameDevices &pt )
		{
			*this = pt;
		}

		//! Operador = de Estructura
		SGameDevices& operator= (const SGameDevices &pt)
		{
			Config = pt.Config;
			Audio = pt.Audio;
			Video = pt.Video;
			World = pt.World;
			Effects = pt.Effects;
			AudioManager = pt.AudioManager;
			SceneManager = pt.SceneManager;
			GUIEnvironment = pt.GUIEnvironment;
			return *this;
		}

		//! Configuración
		CConfig *Config;

		//! Audio
		CAudio *Audio;

		//! Video
		CVideo *Video;

		//! Mundo
		CWorld *World;

		//! Efectos
		CEffects *Effects;

		//! Manejador de Audio
		CAudioManager *AudioManager;

		//! Manejador de Escena
		CSceneManager *SceneManager;

		//! Ambiente GUI
		CGUIEnvironment *GUIEnvironment;
	};
};

#endif
