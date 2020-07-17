#ifndef ___Tornado__PathLocation__H___
#define ___Tornado__PathLocation__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Enumeración Ubicación de Ruta                  *
 * Archivo Fuente: EPathLocation.h                                    *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

namespace Tornado
{
	//! Enumeración Ubicación de Ruta
    enum EPathLocation
	{
		//! Ubicación por defecto
		EPL_DEFAULT,

		//! Ubicación directorio cache
		EPL_CACHE,

		//! Ubicación directorio save
		EPL_SAVEDATA
    };
}


#endif