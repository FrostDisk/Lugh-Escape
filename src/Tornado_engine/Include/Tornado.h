#ifndef ___Tornado_Engine__H___
#define ___Tornado_Engine__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera global del motor                                  *
 * Archivo Fuente: Tornado.h                                          *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

//! Espacio de Nombre de Tornado_engine
namespace Tornado
{
	struct SAudioConfig;
	struct SConfigElement;
	struct SContextElement;
	struct SGameDevices;
	struct SGUIEditorElements;
	struct SGUIEditorInfoElements;
	struct SGUIEditorViewportElements;
	struct SGUITitleElements;
	struct SSplashElement;
	struct STitleElement;
	struct SVideoConfig;
	struct SVideoMode;

	//enum EElementAlign;
	//enum EElementPosition;
	//enum EGUIEditorControl;
	//enum EGUIEditorFunction;
	//enum EGUIEditorMode;
	//enum EGUIEditorViewportControl;
	//enum EGUITitleControl;
	//enum EMousePickFlag;
	//enum EPathLocation;
	//enum ESplashElementType;
	//enum ESplashStatus;
	//enum ETitleElementType;

	class CAudio;
	class CAudioManager;
	class CClock;
	class CConfig;
	class CContext;
	class CEffects;
	class CEventReceiver;
	class CGame;
	class CGUIEnvironment;
	class CMachine;
	class CMath;
	class COutput;
	class CSceneManager;
	class CSystem;
	class CVideo;
	
	class CEditorContext;
	class CErrorContext;
	class CSplashContext;
	class CTitleContext;

	class CWireEditorSceneNode;
	class CScrollParallaxNode;
};

#include "Types.h"
#include "Constants.h"

#include "SAudioConfig.h"
#include "SConfigElement.h"
#include "SContextElement.h"
#include "SGameDevices.h"
#include "SGUIEditorElements.h"
#include "SGUIEditorInfoElements.h"
#include "SGUIEditorViewportElements.h"
#include "SGUITitleElements.h"
#include "SSplashElement.h"
#include "STitleElement.h"
#include "SVideoConfig.h"
#include "SVideoMode.h"

#include "EElementAlign.h"
#include "EElementPosition.h"
#include "EGUIEditorControl.h"
#include "EGUIEditorFunction.h"
#include "EGUIEditorMode.h"
#include "EGUIEditorViewportControl.h"
#include "EGUITitleControl.h"
#include "EMousePickFlag.h"
#include "EPathLocation.h"
#include "ESplashElementType.h"
#include "ESplashStatus.h"
#include "ETitleElementType.h"

#include "CAudio.h"
#include "CAudioManager.h"
#include "CClock.h"
#include "CConfig.h"
#include "CContext.h"
#include "CEffects.h"
#include "CEventReceiver.h"
#include "CGame.h"
#include "CGUIEnvironment.h"
#include "CMachine.h"
#include "CMath.h"
#include "COutput.h"
#include "CSceneManager.h"
#include "CSystem.h"
#include "CVideo.h"

#include "CEditorContext.h"
#include "CErrorContext.h"
#include "CSplashContext.h"
#include "CTitleContext.h"

#include "CWireEditorSceneNode.h"
#include "CScrollParallaxNode.h"

#endif
