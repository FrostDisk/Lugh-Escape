#ifndef ___Tornado__GUIEditorViewportControl__H___
#define ___Tornado__GUIEditorViewportControl__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Enumeración Control GUI de Editor Viewport     *
 * Archivo Fuente: EGUIEditorViewportControl.h                        *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

namespace Tornado
{
	//! Enumeración Control GUI Editor
	enum EGUIEditorViewportControl
	{
		//! Botón Arriba
		EGEVC_ID_BUTTON_UP,

		//! Botón Frente
		EGEVC_ID_BUTTON_FRONT,

		//! Botón Lado
		EGEVC_ID_BUTTON_SIDE,

		//! Botón Perspectiva
		EGEVC_ID_BUTTON_PERSP,

		//! Botón Ortogonal
		EGEVC_ID_BUTTON_ORTHO,
	};
};

#endif