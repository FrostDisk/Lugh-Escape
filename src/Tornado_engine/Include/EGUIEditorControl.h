#ifndef ___Tornado__GUIEditorControl__H___
#define ___Tornado__GUIEditorControl__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Enumeración Control GUI de Editor              *
 * Archivo Fuente: EGUIEditorControl.h                                *
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
	enum EGUIEditorControl
	{
		EGEC_ID_MENU_CONTEXT_NEW,
		EGEC_ID_MENU_CONTEXT_OPEN,
		EGEC_ID_MENU_CONTEXT_SAVE,
		EGEC_ID_MENU_CONTEXT_SAVEAS,
		EGEC_ID_MENU_CONTEXT_CLOSEEDITOR,
		EGEC_ID_MENU_CONTEXT_IMPORT_IRRFILE,
		EGEC_ID_MENU_EDIT_UNDO,
		EGEC_ID_MENU_EDIT_REDO,
		EGEC_ID_MENU_EDIT_CLONE,
		EGEC_ID_MENU_EDIT_DELETE,
		EGEC_ID_MENU_INSERT_OBJECT_CUBE,
		EGEC_ID_MENU_INSERT_OBJECT_SPHERE,
		EGEC_ID_MENU_INSERT_OBJECT_TERRAIN,
		EGEC_ID_MENU_INSERT_OBJECT_SKYBOX,
		EGEC_ID_MENU_INSERT_OBJECT_OCTREE,
		EGEC_ID_MENU_INSERT_OBJECT_MESH,
		EGEC_ID_MENU_INSERT_OBJECT_LIGHT,
		EGEC_ID_MENU_INSERT_OBJECT_EMPTYSCENENODE,
		EGEC_ID_MENU_INSERT_OBJECT_CAMERA,
		EGEC_ID_MENU_INSERT_OBJECT_BILLBOARD,
		EGEC_ID_MENU_INSERT_OBJECT_ANIMATEDMESH,
		EGEC_ID_MENU_INSERT_OBJECT_PARTICLESYSTEM,
		EGEC_ID_MENU_INSERT_BBOX_SPHERE,
		EGEC_ID_MENU_INSERT_BBOX_BOX,
		EGEC_ID_MENU_INSERT_BBOX_CAPSULE,
		EGEC_ID_MENU_INSERT_BBOX_CYLINDER,
		EGEC_ID_MENU_INSERT_BBOX_CONE,
		EGEC_ID_MENU_INSERT_BBOX_CHAMFERCYLINDER,
		EGEC_ID_MENU_INSERT_BBOX_NULL,
		EGEC_ID_MENU_INSERT_BBOX_COMPOUND,
		EGEC_ID_MENU_INSERT_BBOX_CONVEXHULL,
		EGEC_ID_MENU_INSERT_LIGHT,
		EGEC_ID_MENU_TOOLS_PREFERENCES,
		EGEC_ID_MENU_VIEW_SHOWTOOLS,
		EGEC_ID_MENU_VIEW_UPDATEGUI,

		EGEC_ID_WINDOW_IMPORT_IRRFILE,

		EGEC_ID_WINDOW_INSERT_OBJECT_CUBE_EXAMINE,
		EGEC_ID_BUTTON_INSERT_OBJECT_CUBE_EXAMINE,
		EGEC_ID_BUTTON_INSERT_OBJECT_CUBE_ACCEPT,
		EGEC_ID_BUTTON_INSERT_OBJECT_CUBE_CANCEL,

		EGEC_ID_WINDOW_INSERT_OBJECT_MESH,
		EGEC_ID_WINDOW_INSERT_OBJECT_ANIMATEDMESH
	};
};

#endif