#ifndef ___Tornado__AudioConfig__H___
#define ___Tornado__AudioConfig__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Estructura Configuración de Audio              *
 * Archivo Fuente: SAudioConfig.h                                     *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "Types.h"

namespace Tornado
{

	//! Estructura Configuracion de Audio
	struct SAudioConfig
	{

		//! Constructor de Estructura
		SAudioConfig() :
			Music(50),
			Sound(40)
		{
		}

		//! Constructor copia de Estructura
		SAudioConfig(const SAudioConfig &pt)
		{
			*this = pt;
		}

		//! Operador = de Estructura
		SAudioConfig& operator= (const SAudioConfig &pt)
		{
			Music = pt.Music;
			Sound = pt.Sound;
			return *this;
		}

		//! Volumen de la musica
		uint16 Music;

		//! Volumen de los sonidos
		uint16 Sound;

	};
}

#endif
