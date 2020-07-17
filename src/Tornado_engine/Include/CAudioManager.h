#ifndef ___Tornado__AudioManager__H___
#define ___Tornado__AudioManager__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Manejador de Audio                       *
 * Archivo Fuente: CAudioManager.h                                    *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include <audiere.h>
#include <irrlicht.h>
#include "Constants.h"

namespace Tornado
{

	//! Clase Manejador de Audio
	class CAudioManager
	{
	private:
	protected:

		//! Puntero a Dispositivo de Audio
		audiere::AudioDevicePtr AudioDevice;

		//! Sistema de archivos de Irrlicht
		irr::io::IFileSystem *FileSystem;

	public:
		CAudioManager();
		~CAudioManager();

		bool Init(void);

		/**
		 * \brief Asigna el Dispositivo de Audio 
		 * \param Device Dispositivo a asignar
		 */
		inline void SetAudioDevice( audiere::AudioDevicePtr Device )
		{
			this->AudioDevice = Device;
		}

		/**
		 * \brief Asigna el Sistema de Archivos
		 * \param System Sistema de Archivos
		 */
		inline void SetFileSystem( irr::io::IFileSystem *System )
		{
			this->FileSystem = System;
		}

		__TORNADO_DLL_EXPORT audiere::OutputStream *CreateOutputStream(	const char *File ,
																		bool Streaming = false ,
																		audiere::FileFormat Format = audiere::FF_AUTODETECT );

		__TORNADO_DLL_EXPORT audiere::OutputStream *CreateOutputStream(	irr::io::IReadFile *File ,
																		bool Streaming = false ,
																		audiere::FileFormat Format = audiere::FF_AUTODETECT );


		/**
		 * \brief Limpia todas los recursos de audio
		 */
		inline void Clear(void)
		{
		}
	};
};

#endif
