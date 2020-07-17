#ifndef ___Tornado__VideoMode__H___
#define ___Tornado__VideoMode__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Estructura Modo de Video                       *
 * Archivo Fuente: SVideoMode.h                                       *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

namespace Tornado
{

	//! Estructura Modo de Video
	struct SVideoMode
	{

		//! Constructor de Estructura
		SVideoMode() :
			id(0),
			width(0),
			height(0),
			bpp(0)
		{
		}

		//! Constructor copia de Estructura
		SVideoMode(const SVideoMode &pt)
		{
			*this = pt;
		}

		//! Operador = de Estructura
		SVideoMode& operator= (const SVideoMode &pt)
		{
			id = pt.id;
			width = pt.width;
			height = pt.height;
			bpp = pt.bpp;
			return *this;
		}

		//! Identificador de modo de video
		sint32 id;

		//! Ancho en pixeles del modo de video
		sint32 width;

		//! Alto en pixeles del modo de video
		sint32 height;

		//! Profundidad de bits del modo de video
		sint32 bpp;

	};
};

#endif
