#ifndef ___Tornado__GUITitleControl__H___
#define ___Tornado__GUITitleControl__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Enumeración Control GUI de Título              *
 * Archivo Fuente: EGUITitleControl.h                                 *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

namespace Tornado
{
	//! Enumeración Control GUI
	enum EGUITitleControl
	{
		EGTC_ID_NEW_GAME = 0x1111,
		EGTC_ID_LOAD_GAME,
		EGTC_ID_LOAD_SELECT,
		EGTC_ID_LOAD_DELETE,
		EGTC_ID_LOAD_CANCEL,
		EGTC_ID_OPTIONS,
		EGTC_ID_OPTIONS_ACCEPT,
		EGTC_ID_OPTIONS_CONFIRM,
		EGTC_ID_OPTIONS_CANCEL,
		EGTC_ID_OPTIONS_VIDEO_DRIVER,
		EGTC_ID_OPTIONS_VIDEO_RESOLUTION,
		EGTC_ID_OPTIONS_VIDEO_FULLSCREEN,
		EGTC_ID_OPTIONS_VIDEO_ANTIALIASING,
		EGTC_ID_OPTIONS_VIDEO_VERTICALSYNC,
		EGTC_ID_OPTIONS_VIDEO_STENCILSHADOW,
		EGTC_ID_OPTIONS_VIDEO_ANAGLYPHMODE,
		EGTC_ID_OPTIONS_AUDIO_MUSIC,
		EGTC_ID_OPTIONS_AUDIO_SOUND,
		EGTC_ID_QUIT,
		EGTC_ID_CUSTOM
	};
};

#endif
