#ifndef ___Tornado__SplashElementType__H___
#define ___Tornado__SplashElementType__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Enumeración Tipo de Elemento de Splash         *
 * Archivo Fuente: ESplashElementType.h                               *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

namespace Tornado
{
	//! Enumeración Tipo de Elemento de Splash
	enum ESplashElementType
	{
		//! Centrado
		ESET_CENTERED,

		//! Estirado
		ESET_STRETCHED,

		//! Escalado Verticalmente
		ESET_VSCALED,

		//! Escalado Horizontalmente
		ESET_HSCALED,

		//! Escalado Proporcional
		ESET_PROPORTIONAL
	};
};

#endif
