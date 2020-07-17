#ifndef ___Tornado__EditorContext__H___
#define ___Tornado__EditorContext__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Contexto de Editor                       *
 * Archivo Fuente: CEditorContext.h                                   *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include <list>
#include "CContext.h"

#include "SGUIEditorElements.h"
#include "SGUIEditorViewportElements.h"
#include "SGUIEditorInfoElements.h"
#include "SGUIEditorLightElement.h"

#include "EMousePickFlag.h"
#include "EGUIEditorMode.h"
#include "EGUIEditorFunction.h"
#include "EGUIEditorTransform.h"

namespace Tornado
{

	//! Clase Contexto de Editor
	class CEditorContext : public CContext
	{

	private:

		//! Último ID de Nodo
		irr::s32 LastNodeId;

		//! Último ID de Luz
		irr::s32 LastLightId;

		//! Elementos de la GUI
		SGUIEditorElements Elements;

		//! Nodo previamente seleccionado
		irr::scene::ISceneNode *SelectedSceneNode;

		//! Luz previamente seleccionado
		SGUIEditorLightElement *SelectedLight;

		//! Lista de Nodos en la escena
		std::list<irr::scene::ISceneNode *> Nodes;

		//! Lista de Luces en la escena
		std::list<SGUIEditorLightElement *> Lights;

		//! Modo de Editor de GUI
		EGUIEditorMode Mode;

		//! Función de Editor de GUI
		EGUIEditorFunction Function;

		//! Función de Transformación de Editor de GUI
		EGUIEditorTransform Transform;

		//! Vector de Transformación
		irr::core::vector3df TransformVector;

		//! Vector Salvado de Transformación
		irr::core::vector3df SavedVector;

		//! Vector Centro de la pantalla
		irr::core::vector2df Center;

	protected:

		__TORNADO_DLL_EXPORT bool InitResources(void);
		__TORNADO_DLL_EXPORT void ShowArrowAxis(irr::core::vector3df Position);
		__TORNADO_DLL_EXPORT void PrepareGUI(void);
		__TORNADO_DLL_EXPORT void SceneNodeMousePick(irr::s32 X,irr::s32 Y);

	public:
		__TORNADO_DLL_EXPORT CEditorContext(uint16 Id,bool HaveLoading = false);
		__TORNADO_DLL_EXPORT ~CEditorContext();

		__TORNADO_DLL_EXPORT virtual bool Init(void);
		__TORNADO_DLL_EXPORT virtual void Prepare(void);
		__TORNADO_DLL_EXPORT virtual void Next(real Delta);
		__TORNADO_DLL_EXPORT virtual void Draw(void);
		__TORNADO_DLL_EXPORT virtual void End(void);

		__TORNADO_DLL_EXPORT virtual bool LoadingInit(void);
		__TORNADO_DLL_EXPORT virtual void LoadingPrepare(void);
		__TORNADO_DLL_EXPORT virtual void LoadingNext(real Delta);
		__TORNADO_DLL_EXPORT virtual void LoadingDraw(void);
		__TORNADO_DLL_EXPORT virtual void LoadingEnd(void);

		__TORNADO_DLL_EXPORT virtual void Close(void);

		__TORNADO_DLL_EXPORT bool OnGUIEvent(irr::gui::IGUIElement *Caller,irr::gui::IGUIElement *Element,const uint16 &EventType);
		__TORNADO_DLL_EXPORT virtual bool OnKeyInput(const uint16 &Key,const wchar_t &Char,const bool isCtrl,const bool isShift,const bool isPressedDown);
		__TORNADO_DLL_EXPORT bool OnMouseInput(const uint16 &EventType,const sint32 &X,const sint32 &Y,const real &Wheel,const bool isLeft,const bool isMiddle,const bool isRight,const bool isCtrl,const bool isShift);

		__TORNADO_DLL_EXPORT void CreateAndSetTriangleSelector(irr::scene::IMesh *Mesh,irr::scene::ISceneNode *Node);
		__TORNADO_DLL_EXPORT void CreateAndSetLightTriangleSelector(irr::scene::ISceneNode *Node,irr::scene::ISceneNode *Target);
		__TORNADO_DLL_EXPORT void CreateAndSetTerrainTriangleSelector(irr::scene::ITerrainSceneNode *Terrain );


};
};
#endif