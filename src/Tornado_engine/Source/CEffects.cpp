/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Codigo Fuente de Clase Efectos                             *
 * Archivo Fuente: CEffects.cpp                                       *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CEffects.h"

namespace Tornado
{

	/**
	 * \brief Constructor de Clase
	 */
	CEffects::CEffects() :
			Effects(NULL),
			VideoDevice(NULL),
			UseVSMShadows(false),
			UseRoundSpotLights(false),
			Use32BitDepthBuffers(false)
	{
	}

	/**
	 * \brief Destructor de Clase
	 */
	CEffects::~CEffects()
	{
	}
}
