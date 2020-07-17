#ifndef ___Tornado__Audio__H___
#define ___Tornado__Audio__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Audio                                    *
 * Archivo Fuente: CAudio.h                                           *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include <audiere.h>

#include "SAudioConfig.h"

namespace Tornado
{

	//! Clase Audio
	class CAudio
	{

	private:

		//! Dispositivo de Audio
		audiere::AudioDevicePtr AudioDevice;

		//! Indicador de estado de Dispositivo
		bool AudioDevice__loaded;

		//! Configuración de audio
		SAudioConfig AudioConfig;

	protected:
	public:
		CAudio();
		~CAudio();

		bool Init(void);

		void SetAudioConfig(SAudioConfig *Config);

		/**
		 * \brief Retorna un puntero al Dispositivo de Audio
		 * \return Puntero al Dispositivo de Audio
		 * \author NioZero
		 */
		inline audiere::AudioDevicePtr GetAudioDevice(void)
		{
			return AudioDevice;
		}

		/**
		 * \brief Retorna la configuración de volumen de la música
		 * \return Volumen de la música configurada
		 */
		inline uint16 GetMusicVolume(void)
		{
			return AudioConfig.Music;
		}

		/**
		 * \brief Retorna la configuración de volumen de los sonidos
		 * \return Volumen de los sonidos configurado
		 */
		inline uint16 GetSoundVolume(void)
		{
			return AudioConfig.Sound;
		}

		/**
		 * \brief Cierra el Dispositivo de Audio
		 */
		inline void End(void)
		{
		};
	};

};

#endif
