#ifndef ___Tornado__GUIEditorElements__H___
#define ___Tornado__GUIEditorElements__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Estructura Elementos de Editor de GUI          *
 * Archivo Fuente: SGUIEditorElements.h                               *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include <irrlicht.h>
#include "CWireEditorSceneNode.h"

namespace Tornado
{
	//! Estructura Elementos GUI del Editor
	struct SGUIEditorElements
	{
		//! Estructura Elementos GUI Globales del Editor
		struct SGUIEditorGlobal 
		{
			//! Constructor de Estructura
			SGUIEditorGlobal() :
				Camera(NULL),
				Font(NULL),
				Wire(NULL)
			{
			}

			//! Cámara del visualizador
			irr::scene::ICameraSceneNode *Camera;

			//! Fuente del Editor
			irr::gui::IGUIFont* Font;

			//! Malla
			CWireEditorSceneNode *Wire;

		} Global;

		//! Estructura Elementos GUI Mouse del Editor
		struct SGUIEditorMouse
		{
			SGUIEditorMouse() :
				Xold(0),
				Yold(0),
				Xrel(0),
				Yrel(0)
			{
			}

			//! Posición X anterior
			sint32 Xold;

			//! Posición Y anterior
			sint32 Yold;

			//! Posición X relativa
			sint32 Xrel;

			//! Posición Y relativa
			sint32 Yrel;
		} Mouse;

		//! Estructura Elementos GUI Ventanas del Editor
		struct SGUIEditorWindows
		{
			//! Constructor de Estructura
			SGUIEditorWindows() :
				Properties(NULL)
			{
			}
			
			//! Ventana Propiedades
			irr::gui::IGUIWindow *Properties;

			//! Ventana Insertar Luz
			irr::gui::IGUIWindow *InsertLight;
		} Windows;

		//! Estructura Elementos GUI Vista del Editor
		struct SGUIEditorViewport
		{

		} Viewport;

		//! Estructura Elementos GUI Ejes Coordenados del Editor
		struct SGUIEditorArrowAxis
		{
			//! Constructor de Estructura
			SGUIEditorArrowAxis() :
				Parent(NULL),
				XAxi(NULL),
				YAxi(NULL),
				ZAxi(NULL)
			{
			}

			//! Nodo Posición Ejes
			irr::scene::ISceneNode *Parent;

			//! Nodo Flecha Eje-X
			irr::scene::ISceneNode *XAxi;

			//! Nodo Flecha Eje-Y
			irr::scene::ISceneNode *YAxi;

			//! Nodo Flecha Eje-Z
			irr::scene::ISceneNode *ZAxi;

		} ArrowAxis;

	};
};

#endif
