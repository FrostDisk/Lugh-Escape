#ifndef ___Tornado__EventReceiver__H___
#define ___Tornado__EventReceiver__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Receptor de Eventos                      *
 * Archivo Fuente: CEventReceiver.h                                   *
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

	struct SGameDevices;

	//! Clase Receptor de Eventos
	class CEventReceiver : public irr::IEventReceiver
	{

	private:

	protected:

		//! Dispositivos de Juego
		SGameDevices *GameDevices;

	public:
		CEventReceiver();
		~CEventReceiver();

		virtual bool OnGUIEvent(const irr::SEvent::SGUIEvent &Event);
		virtual bool OnJoystickEvent(const irr::SEvent::SJoystickEvent &Event);
		virtual bool OnKeyInput(const irr::SEvent::SKeyInput &Event);
		virtual bool OnMouseInput(const irr::SEvent::SMouseInput &Event);
		virtual bool OnUserEvent(const irr::SEvent::SUserEvent &Event);

		bool OnEvent(const irr::SEvent& event);

	};
};

#endif
