#ifndef ___Tornado__Workspace__H___
#define ___Tornado__Workspace__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Espacio de Trabajo                       *
 * Archivo Fuente: CWorkspace.h                                       *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include <irrlicht.h>
#include "Types.h"

namespace Tornado
{
	//! Clase Espacio de Trabajo
	class CWorkspace
	{

	private:

		//! Ancho del Espacio de Trabajo
		uint16 Width;

		//! Alto del Espacio de Trabajo
		uint16 Height;

		//! Mitad del Ancho del Espacio de Trabajo
		uint16 WidthSplit2;

		//! Mitad del Alto del Espacio de Trabajo
		uint16 HeightSplit2;

	protected:
	public:

		CWorkspace();

		/**
		 * \brief Asigna las variables del Espacio de Trabajo
		 * \param tmp_Width Ancho del Espacio de Trabajo
		 * \param tmp_Height Alto del Espacio de Trabajo
		 */
		inline void SetWorkspace(const uint16 tmp_Width,const uint16 tmp_Height)
		{
			Width = tmp_Width;
			Height = tmp_Height;
			WidthSplit2 = (uint16) ( (real)tmp_Width * 0.5 );
			HeightSplit2 = (uint16) ( (real)tmp_Height * 0.5 );
		}

		//irr::core::rect<irr::s32> &GetRect(const uint16 RectWidth,const uint16 RectHeight,const uint16 Position,const uint16 Align);
	};
};

#endif
