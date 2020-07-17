#ifndef ___Tornado__TitleContext__H___
#define ___Tornado__TitleContext__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Contexto de Título                       *
 * Archivo Fuente: CTitleContext.h                                    *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include <list>
#include "CContext.h"
#include "SGUITitleElements.h"
#include "ETitleElementType.h"
#include "STitleElement.h"

namespace Tornado
{

	//! Clase Contexto Titulo de GUI
	class CTitleContext : public CContext
	{
	
	private:

		//! Elementos de Menu de Título
		SGUITitleElements GUITitleElements;

		//! Elemento Nuevo Juego
		STitleElement NewGameElement;

		//! Elemento Cargar Juego
		STitleElement LoadGameElement;

		//! Elemento Opciones
		STitleElement OptionsElement;

		//! Elemento Salir
		STitleElement QuitGameElement;

		//! Otros Elementos del Título
		std::list<STitleElement *> CustomTitleElements;

		void ShowOptionsWindow(void);

	protected:

		__TORNADO_DLL_EXPORT void PrepareDefaultGUI(void);

		__TORNADO_DLL_EXPORT bool CreateNewGameImageElement(irr::core::vector2di Position,const wchar_t *Image,const wchar_t *Hover = NULL,const wchar_t *Pressed = NULL);
		__TORNADO_DLL_EXPORT bool CreateLoadGameImageElement(irr::core::vector2di Position,const wchar_t *Image,const wchar_t *Hover = NULL,const wchar_t *Pressed = NULL);
		__TORNADO_DLL_EXPORT bool CreateOptionsImageElement(irr::core::vector2di Position,const wchar_t *Image,const wchar_t *Hover = NULL,const wchar_t *Pressed = NULL);
		__TORNADO_DLL_EXPORT bool CreateQuitGameImageElement(irr::core::vector2di Position,const wchar_t *Image,const wchar_t *Hover = NULL,const wchar_t *Pressed = NULL);
		__TORNADO_DLL_EXPORT bool CreateCustomImageElement(uint16 Element,irr::core::vector2di Position,const wchar_t *Image,const wchar_t *Hover = NULL,const wchar_t *Pressed = NULL);

		__TORNADO_DLL_EXPORT bool CreateNewGameImageElement(irr::core::vector2di Position,irr::video::ITexture *Image,irr::video::ITexture *Hover = NULL,irr::video::ITexture *Pressed = NULL);
		__TORNADO_DLL_EXPORT bool CreateLoadGameImageElement(irr::core::vector2di Position,irr::video::ITexture *Image,irr::video::ITexture *Hover = NULL,irr::video::ITexture *Pressed = NULL);
		__TORNADO_DLL_EXPORT bool CreateOptionsImageElement(irr::core::vector2di Position,irr::video::ITexture *Image,irr::video::ITexture *Hover = NULL,irr::video::ITexture *Pressed = NULL);
		__TORNADO_DLL_EXPORT bool CreateQuitGameImageElement(irr::core::vector2di Position,irr::video::ITexture *Image,irr::video::ITexture *Hover = NULL,irr::video::ITexture *Pressed = NULL);
		__TORNADO_DLL_EXPORT bool CreateCustomImageElement(uint16 Element,irr::core::vector2di Position,irr::video::ITexture *Image,irr::video::ITexture *Hover = NULL,irr::video::ITexture *Pressed = NULL);

		__TORNADO_DLL_EXPORT void SetGuiVisibility(bool visibility);

	public:
		__TORNADO_DLL_EXPORT CTitleContext(uint16 Id,bool HaveLoading = false);
		__TORNADO_DLL_EXPORT ~CTitleContext();

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

		__TORNADO_DLL_EXPORT virtual bool OnHoverElement(void);
		__TORNADO_DLL_EXPORT virtual bool OnPressedElement(void);

		__TORNADO_DLL_EXPORT virtual bool OnGUICustomEvent(irr::gui::IGUIElement *Caller,irr::gui::IGUIElement *Element,const uint16 &EventType);
		__TORNADO_DLL_EXPORT virtual bool OnNewGameEvent(void);
		__TORNADO_DLL_EXPORT virtual bool OnLoadGameEvent(void);
		__TORNADO_DLL_EXPORT virtual bool OnQuitGameEvent(void);
		__TORNADO_DLL_EXPORT bool OnGUIEvent(irr::gui::IGUIElement *Caller,irr::gui::IGUIElement *Element,const uint16 &EventType);

	};
};

#endif

