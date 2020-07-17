#ifndef ___Tornado__SplashContext__H___
#define ___Tornado__SplashContext__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Contexto de Splash                       *
 * Archivo Fuente: CSplashContext.h                                   *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CContext.h"
#include "SSplashElement.h"
#include "ESplashElementType.h"
#include "CClock.h"
#include <list>

namespace Tornado
{

	//! Clase Contexto de Splash
	class CSplashContext : public CContext
	{

	private:

		//! Reloj
		CClock Clock;

		//! Estado Actual
		uint16 ActualStatus;

		//! Imagen
		irr::gui::IGUIImage *SplashImage;

		//! Desvanecedor
		irr::gui::IGUIInOutFader* SplashFader;

		//! Imágenes que se mostrarán en el splash
		std::list< SSplashElement* > Elements;

		//! Elemento actual que se está mostrando
		std::list< SSplashElement* >::iterator IndexActualElement;

	protected:

		__TORNADO_DLL_EXPORT bool AddImageElement(	const wchar_t *Path,
													bool AlphaChannel = false,
													irr::video::SColor BgColor = irr::video::SColor(0xFF,0xFF,0xFF,0xFF),
													irr::video::SColor FadeInColor = irr::video::SColor(0xFF,0x00,0x00,0x00),
													irr::video::SColor FadeOutColor = irr::video::SColor(0xFF,0x00,0x00,0x00),
													uint16 AlignType = ESET_CENTERED,
													uint32 FadeTime = 1000,
													uint32 WaitTime = 4000 );

		__TORNADO_DLL_EXPORT bool BeginSplashAnimation(void);

	public:
		__TORNADO_DLL_EXPORT CSplashContext(uint16 Id,bool HaveLoading = false);
		__TORNADO_DLL_EXPORT ~CSplashContext();

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

		__TORNADO_DLL_EXPORT virtual bool OnSplashFinishEvent(void);
		__TORNADO_DLL_EXPORT bool OnGUIEvent(irr::gui::IGUIElement *Caller,irr::gui::IGUIElement *Element,const uint16 &EventType);
		__TORNADO_DLL_EXPORT bool OnKeyInput(const uint16 &Key,const wchar_t &Char,const bool isCtrl,const bool isShift,const bool isPressedDown);
		__TORNADO_DLL_EXPORT bool OnMouseInput(const uint16 &EventType,const sint32 &X,const sint32 &Y,const real &Wheel,const bool isLeft,const bool isMiddle,const bool isRight,const bool isCtrl,const bool isShift);
	};
};

#endif
