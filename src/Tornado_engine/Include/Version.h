#ifndef ___Tornado__Version__H___
#define ___Tornado__Version__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Variables de versión del motor                             *
 * Archivo Fuente: Version.h                                          *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

//! Número de Version Mayor del Engine
#define __TORNADO_VERSION_MAJOR 0
//! Número de Version Menor del Engine
#define __TORNADO_VERSION_MINOR 5
//! Número de Revisión del Engine
#define __TORNADO_VERSION_REVISION 6

namespace Tornado
{
	//! Texto de Versión del Engine
	static const wchar_t* const __Version =		L"Version 0.5.6-custom";

	//! Texto de Copyright del Engine
	static const wchar_t* const __Copyright =	L"Tornado Engine (c) 2009-2011 FrostDisk";
}

#endif
