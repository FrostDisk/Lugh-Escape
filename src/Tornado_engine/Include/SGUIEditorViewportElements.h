#ifndef ___Tornado__GUIEditorViewportElements__H___
#define ___Tornado__GUIEditorViewportElements__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Estructura Elementos de Editor de Viewport GUI *
 * Archivo Fuente: SGUIEditorViewportElements.h                       *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include <irrlicht.h>

namespace Tornado
{
	//! Estructura Elementos de Menu de Viewport GUI
	struct SGUIEditorViewportElements
	{
		//! Ventana de Viewport
		irr::gui::IGUIWindow* Window;

		//! Botón Arriba
		irr::gui::IGUIButton* Up;

		//! Botón Frente
		irr::gui::IGUIButton* Front;

		//! Botón Lado
		irr::gui::IGUIButton* Side;

		//! Botón Perspectiva
		irr::gui::IGUIButton* Persp;

		//! Botón Ortogonal
		irr::gui::IGUIButton* Ortho;
	};
};

#endif
