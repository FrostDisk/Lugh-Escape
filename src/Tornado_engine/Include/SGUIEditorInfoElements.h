#ifndef ___Tornado__GUIEditorInfoElements__H___
#define ___Tornado__GUIEditorInfoElements__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Estructura Elementos de Editor de Info GUI     *
 * Archivo Fuente: SGUIEditorInfoElements.h                           *
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
	struct SGUIEditorInfoElements
	{
		//! Ventana de Viewport
		irr::gui::IGUIWindow* Window;

		//! Ventana Visible
		bool VisibleWindow;

		struct
		{
			irr::gui::IGUIEditBox *X,*Y,*Z;

		} Pos,Sca,Rot;

	};
};

#endif
