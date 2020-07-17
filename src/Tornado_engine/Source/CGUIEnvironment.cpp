/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Código Fuente de Clase Ambiente GUI                        *
 * Archivo Fuente: CGUIEnvironment.cpp                                *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CGUIEnvironment.h"
#include "Constants.h"
#include "Types.h"
#include "COutput.h"

namespace Tornado {

	/**
	 * \brief Constructor de Clase
	 */
	CGUIEnvironment::CGUIEnvironment() :
		VideoDevice(NULL)
	{
	}

	/**
	 * \brief Destructor de Clase
	 */
	CGUIEnvironment::~CGUIEnvironment()
	{
		GUIEnvironment = NULL;
		VideoDevice = NULL;
		GUISkin = NULL;
	}

	/**
	 * \brief Prepara la GUI
	 */
	void CGUIEnvironment::PrepareGUI(void)
	{
	}

};
