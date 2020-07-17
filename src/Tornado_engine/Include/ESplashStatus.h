#ifndef ___Tornado__SplashStatus__H___
#define ___Tornado__SplashStatus__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Enumeración Estado de Splash                   *
 * Archivo Fuente: ESplashStatus.h                                    *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

namespace Tornado
{

	//! Enumeración Estado de Splash
	enum ESplashStatus
	{
		//! Estado de Inicio
		ESS_START = 10,

		//! Estado de Espera
		ESS_WAITING,

		//! Estado Desvanecimiento Entrada
		ESS_FADEIN,

		//! Estado Desvanecimiento Salida
		ESS_FADEOUT,

		//! Estado Desvanecimiento Entrada-Pre
		ESS_FADEPREOUT
	};
};

#endif
