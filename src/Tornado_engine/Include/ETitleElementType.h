#ifndef ___Tornado__TitleElementType__H___
#define ___Tornado__TitleElementType__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Enumeración Tipo de Elemento de Titulo         *
 * Archivo Fuente: ETitleElementType.h                                *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

namespace Tornado
{

	//! Enumeración Elemento de Titulo
	enum ETitleElementType
	{
		//! Nuevo Juego
		ETET_NEWGAME,

		//! Cargar Juego
		ETET_LOADGAME,

		//! Opciones
		ETET_OPTIONS,

		//! Salir
		ETET_QUIT,

		//! Personalizado
		ETET_CUSTOM
	};
};

#endif
