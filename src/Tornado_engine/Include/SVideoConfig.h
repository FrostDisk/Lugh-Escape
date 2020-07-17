#ifndef ___Tornado__VideoConfig__H___
#define ___Tornado__VideoConfig__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Estructura Configuración de Video              *
 * Archivo Fuente: SVideoConfig.h                                     *
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

	//! Estructura Configuracion de Video
	struct SVideoConfig
	{

		//! Constructor de Estructura
		SVideoConfig() :
			Driver(1),
			Bits(16),
			Fullscreen(false),
			Antialiasing(false),
			VerticalSync(false),
			StencilShadow(false),
			AnaglyphMode(false),
			Width(800),
			Height(600)
		{
		}

		//! Constructor copia de Estructura
		SVideoConfig(const SVideoConfig &pt)
		{
			*this = pt;
		}

		//! Operador = de Estructura
		SVideoConfig& operator= (const SVideoConfig &pt)
		{
			Driver = pt.Driver;
			Bits = pt.Bits;
			Fullscreen = pt.Fullscreen;
			Antialiasing = pt.Antialiasing;
			VerticalSync = pt.VerticalSync;
			StencilShadow = pt.StencilShadow;
			AnaglyphMode = pt.AnaglyphMode;
			Width = pt.Width;
			Height = pt.Height;
			return *this;
		}

		//! Tipo de dispositivo
		uint8 Driver;

		//! Profundidad de Bits por pixel
		uint8 Bits;

		//! Especifica si el video estar en Pantalla completa
		bool Fullscreen;

		//! Especifica si el video usará Anti-aliasing
		bool Antialiasing;

		//! Especifica si el video usará sincronización vertical
		bool VerticalSync;

		//! Especifica si el video tendrá sombra stencil
		bool StencilShadow;

		//! Especifica si el video tendrá modo Anaglyph activado
		bool AnaglyphMode;

		//! Especifica el ancho del video
		uint16 Width;

		//! Especifica el alto del video
		uint16 Height;
	};
}

#endif
