#ifndef ___Tornado__Machine__H___
#define ___Tornado__Machine__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Maquina                                  *
 * Archivo Fuente: CMachine.h                                         *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include <list>
#include <irrlicht.h>
#if defined(WIN32)
#include <windows.h>
#endif
#include "CContext.h"
#include "CTitleContext.h"
#include "SGameDevices.h"
#include "SContextElement.h"

namespace Tornado
{

	//! Clase Máquina
	class CMachine : public CEventReceiver
	{

	private:


		//! Dispositivos de Juego
		SGameDevices *GameDevices;

		//! Contexto activo
		CContext *ActiveContext;

		//! Contexto de Menu de GUI
		CContext *TitleContext;

		//! Primer Contexto
		SContextElement *First;

		//! Último Contexto
		SContextElement *Last;

		//! Lista de Contextos 
		//std::list<SContextElement *> Contexts;

		#if defined(WIN32)

		//! ID de hebra
		DWORD ThreadId;

		//! Hebra manejadora
		HANDLE ThreadHandle;

		static bool ThreadIsActive;

		#endif

	protected:
	public:
		CMachine();
		~CMachine();

		bool Init(void);
		bool Update(void);
		void Draw(void);
		bool Next(real Delta);
		bool Run(real Delta);
		void Close(void);

		#if defined(WIN32)
		static DWORD WINAPI ThreadProc( LPVOID Param );
		#endif


		__TORNADO_DLL_EXPORT bool AddContext(CContext *newContext);
		bool SetNextContext(uint16 Id);

		/**
		 * \brief Asigna el Contexto del Título
		 * \param titleContext Contexto de título a asignar
		 * \return TRUE si el contexto de título ha sido asignado, FALSE en caso contrario
		 */
		inline bool SetTitleContext(CContext *titleContext)
		{
			if( titleContext )
			{
				TitleContext = titleContext;
				return AddContext( titleContext );
			}
			return false;
		}

		/**
		 * \brief Asigna los dispositivos de juego
		 * \param Devices Puntero a dispositivos de video
		 */
		inline void SetGameDevices(SGameDevices *Devices)
		{
			GameDevices = Devices;
		}


		bool OnGUIEvent(const irr::SEvent::SGUIEvent &Event);
		bool OnJoystickEvent(const irr::SEvent::SJoystickEvent &Event);
		bool OnKeyInput(const irr::SEvent::SKeyInput &Event);
		bool OnMouseInput(const irr::SEvent::SMouseInput &Event);
		bool OnUserEvent(const irr::SEvent::SUserEvent &Event);
	};
};

#endif
