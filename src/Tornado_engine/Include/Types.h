#ifndef ___Tornado__Types__H___
#define ___Tornado__Types__H___
#include "Constants.h"
/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Tipos de Datos del motor                                   *
 * Archivo Fuente: Types.h                                            *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

namespace Tornado
{

	//! Tipo caracter sin signo
	typedef unsigned char	uchar;

	//! Tipo entero chico sin signo
	typedef unsigned short	ushort;

	//! Tipo entero normal sin signo
	typedef unsigned int	uint;

	//! Tipo entero largo sin signo
	typedef unsigned long	ulong;

	//! Tipo entero sin signo de 8-bits
	#ifdef _MSC_VER
	typedef unsigned __int8 uint8;
	#else
	typedef unsigned char uint8;
	#endif

	//! Tipo entero con signo de 8-bits
	#ifdef _MSC_VER
	typedef __int8 sint8;
	#else
	typedef signed char sint8;
	#endif

	//! Tipo entero sin signo de 16-bits
	#ifdef _MSC_VER
	typedef unsigned __int16 uint16;
	#else
	typedef unsigned short uint16;
	#endif

	//! Tipo entero con signo de 16-bits
	#ifdef _MSC_VER
	typedef __int16 sint16;
	#else
	typedef signed short sint16;
	#endif

	//! Tipo entero sin signo de 32-bits
	#ifdef _MSC_VER
	typedef unsigned __int32 uint32;
	#else
	typedef unsigned int uint32;
	#endif

	//! Tipo entero con signo de 32-bits
	#ifdef _MSC_VER
	typedef __int32 sint32;
	#else
	typedef signed int sint32;
	#endif

	//! Tipo Numero Real
	#if TORNADO_DOUBLE_PRECISION == 1
	typedef double real;
	#else
	typedef float real;
	#endif

};
#endif
