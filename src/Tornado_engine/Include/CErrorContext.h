#ifndef ___Tornado__ErrorContext__H___
#define ___Tornado__ErrorContext__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Contexto de Error                        *
 * Archivo Fuente: CErrorContext.h                                    *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CContext.h"
#include "Constants.h"
#include "Types.h"

namespace Tornado
{
	//! Clase Contexto Titulo de GUI
	class CErrorContext : public CContext
	{
	
	private:

	protected:

	public:
		__TORNADO_DLL_EXPORT CErrorContext(uint16 Id,bool HaveLoading = false);
		__TORNADO_DLL_EXPORT ~CErrorContext();

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

	};
};

#endif

