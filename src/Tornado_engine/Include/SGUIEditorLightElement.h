#ifndef ___Tornado__GUIEditorLightElements__H___
#define ___Tornado__GUIEditorLightElements__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Estructura Elementos Luces de Editor de GUI    *
 * Archivo Fuente: SGUIEditorLightElements.h                          *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include <Irrlicht.h>
#include "XEffects\SShadowLight.h"
#include "Types.h"

namespace Tornado
{
	//! Estructura Elemento Luz GUI del Editor
	struct SGUIEditorLightElement
	{
		uint16 Id;

		irr::scene::ISceneNode *Node;

		irr::scene::ISceneNode *Target;

		XEffects::SShadowLight* Light;
	};
};

#endif
