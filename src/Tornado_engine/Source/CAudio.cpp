/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Codigo Fuente de Clase Audio                               *
 * Archivo Fuente: CAudio.cpp                                         *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CAudio.h"

namespace Tornado {

	/**
	 * \brief Constructor de Clase
	 */
	CAudio::CAudio() :
		AudioDevice__loaded(false)
	{
	}

	/**
	 * \brief Destructor de Clase
	 */
	CAudio::~CAudio()
	{
	}

	/**
	 * \brief Inicializa el Dispositivo de Audio
	 * \return TRUE si el dispositivo ha sido inicializado con éxito, FALSE en caso contrario
	 */
	bool CAudio::Init(void)
	{
		AudioDevice = audiere::OpenDevice();

		return AudioDevice__loaded = !AudioDevice ? false : true ;
	}

	/**
	 * \brief Cambia la configuracion de audio
	 * \param tmp_config Puntero a configuración de audio
	 */
	void CAudio::SetAudioConfig(SAudioConfig *audioConfig)
	{
		if( audioConfig!=NULL )
		{
			AudioConfig.Music = audioConfig->Music;
			AudioConfig.Sound = audioConfig->Sound;
		}
	}

};
