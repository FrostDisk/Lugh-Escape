#ifndef ___Tornado__SplashElement__H___
#define ___Tornado__SplashElement__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Estructura Elemento de Splash                  *
 * Archivo Fuente: SSplashElement.h                                   *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include <irrlicht.h>

namespace Tornado
{

	//! Estructura Elemento de Splash
	struct SSplashElement
	{

		//! Constructor de estructura
		SSplashElement() :
				AlphaChannel(false),
				FadeTime(0),
				WaitTime(0),
				BgColor(),
				FadeInColor(),
				FadeOutColor(),
				Texture(NULL),
				Position(),
				SourceRect(),
				DestRect()
		{
		}

		//! Indicador de si la imagen tiene canal alfa
		bool AlphaChannel;

		//! Tiempo de desvanecimiento
		uint32 FadeTime;

		//! Tiempo de espera
		uint32 WaitTime;

		//! Color del Fondo
		irr::video::SColor BgColor;

		//! Color del Desvanecimiento 
		irr::video::SColor FadeInColor;

		//! Color del Desvanecimiento
		irr::video::SColor FadeOutColor;

		//! Textura
		irr::video::ITexture *Texture;

		//! Posición de la imágen
		irr::core::position2d<irr::s32> Position;

		//! Tamaño de la imágen
		irr::core::rect<irr::s32> SourceRect;

		//! Tamaño de la imágen
		irr::core::rect<irr::s32> DestRect;
	};
};

#endif
