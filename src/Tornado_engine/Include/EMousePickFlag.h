#ifndef ___Tornado__MousePickFlag__H___
#define ___Tornado__MousePickFlag__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Enumeración Bandera de MousePick               *
 * Archivo Fuente: EMousePickFlag.h                                   *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

namespace Tornado
{
	//! Enumeración Bandera de MousePick
    enum EMousePickFlag
	{
		//! No Seleccionable
        EMPF_NOTPICKABLE = 0x0,	// 0000000000000000

		//! Seleccionable
        EMPF_PICKABLE = 0xF800,	// 1111100000000000

		//! Mesh
		EMPF_MESH = 0x8000,		// 1000000000000000

		//! Terreno
		EMPF_TERRAIN = 0x4000,	// 0100000000000000

		//! Luz
		EMPF_LIGHT = 0x2000,	// 0010000000000000

		//! Objetivo
		EMPF_TARGET = 0x1000,	// 0001000000000000

		//! Empty Node
		EMPF_NULL =	0x0800		// 0000100000000000
    };
}


#endif