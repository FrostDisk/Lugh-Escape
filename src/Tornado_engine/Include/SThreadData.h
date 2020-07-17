#ifndef ___Tornado__ThreadData__H___
#define ___Tornado__ThreadData__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Estructura Datos de Hebra                      *
 * Archivo Fuente: SThreadData.h                                      *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

namespace Tornado
{
	class CContext;

	//! Estructura Datos de Hebra
	struct SThreadData
	{
		//! Constructor de Estructura
		SThreadData() :
			ActiveContext(NULL)
		{
		}

		//! Referencia a Contexto Activo
		CContext *ActiveContext;
	};
};

#endif
