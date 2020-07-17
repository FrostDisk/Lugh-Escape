#ifndef ___Tornado__TitleElement__H___
#define ___Tornado__TitleElement__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Estructura Elemento de Título                  *
 * Archivo Fuente: STitleElement.h                                    *
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

	//! Estructura Elemento de Título
	struct STitleElement
	{

		//! Constructor de estructura
		STitleElement() :
			Active(false),
			Type(0),
			Image(NULL),
			Hover(NULL),
			Pressed(NULL)
		{
		}

		//! Elemento Activo
		bool Active;

		//! Tipo de Elemento
		uint16 Type;

		//! Imagen
		irr::gui::IGUIImage *Image;

		//! Imagen estado hover
		irr::gui::IGUIImage *Hover;

		//! Imagen estado pressed
		irr::gui::IGUIImage *Pressed;
	};
};

#endif
