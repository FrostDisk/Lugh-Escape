/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Codigo Fuente de Clase Receptor de Evento                  *
 * Archivo Fuente: CEventReceiver.cpp                                 *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CEventReceiver.h"

#if !defined(WIN32)
#include <stddef.h>
#include <inttypes.h>
#include <wchar.h>
#endif

namespace Tornado
{

	/**
	 * \brief Constructor de Clase
	 */
	CEventReceiver::CEventReceiver() : irr::IEventReceiver(), GameDevices(NULL)
	{
	}

	/**
	 * \brief Destructor de Clase
	 */
	CEventReceiver::~CEventReceiver()
	{
		GameDevices = NULL;
	}

	/**
	 * \brief Evento de GUI
	 * \param Event Evento
	 * \return FALSE
	 */
	bool CEventReceiver::OnGUIEvent(const irr::SEvent::SGUIEvent &guiEvent)
	{
		return false;
	}

	/**
	 * \brief Evento de Joystick
	 * \param Event Evento
	 * \return FALSE
	 */
	bool CEventReceiver::OnJoystickEvent(const irr::SEvent::SJoystickEvent &joystickEvent)
	{
		return false;
	}

	/**
	 * \brief Evento de Teclado
	 * \param Event Evento
	 * \return FALSE
	 */
	bool CEventReceiver::OnKeyInput(const irr::SEvent::SKeyInput &keyInputEvent)
	{
		return false;
	}

	/**
	 * \brief Evento de Mouse
	 * \param Event Evento
	 * \return FALSE
	 */
	bool CEventReceiver::OnMouseInput(const irr::SEvent::SMouseInput &mouseInputEvent)
	{
		return false;
	}

	/**
	 * \brief Evento de Usuario
	 * \param Event Evento
	 * \return FALSE
	 */
	bool CEventReceiver::OnUserEvent(const irr::SEvent::SUserEvent &userEvent)
	{
		return false;
	}

	/**
	 * \brief Cualquier Evento
	 * \param Event Evento
	 * \return FALSE
	 */
	bool CEventReceiver::OnEvent(const irr::SEvent& anyEvent)
	{

		//COutput::Wprintf(L"Evento: %d\n",Event.EventType);

		// Tipo de Evento
		switch(anyEvent.EventType)
		{

			default:
			{
				//COutput::Wprintf(L"Otro Evento\n");
				break;
			}

			// Evento de GUI
			case irr::EET_GUI_EVENT:
			{
				//COutput::Wprintf(L"Evento de GUI\n");
				return OnGUIEvent( anyEvent.GUIEvent );
				break;
			}

			case irr::EET_JOYSTICK_INPUT_EVENT:
			{
				//COutput::Wprintf(L"Evento de Joystick\n");
				return OnJoystickEvent( anyEvent.JoystickEvent );
				break;
			}

			case irr::EET_KEY_INPUT_EVENT:
			{
				//COutput::Wprintf(L"Evento de Teclado\n");
				switch( anyEvent.KeyInput.Key )
				{
					default:
					{
						break;
					}

					case irr::KEY_ESCAPE:
					{
						//GameDevices->Video->GetVideoDevice()->closeDevice();
						break;
					}

					case irr::KEY_F12:
					{
						//GameDevices->Video->CreateScreenshot();
						break;
					}
				}
				return OnKeyInput( anyEvent.KeyInput );
				break;
			}

			case irr::EET_MOUSE_INPUT_EVENT:
			{
				//COutput::Wprintf(L"Evento de Mouse\n");
				return OnMouseInput( anyEvent.MouseInput );
				break;
			}

			case irr::EET_USER_EVENT:
			{
				//COutput::Wprintf(L"Evento de Usuario\n");
				return OnUserEvent( anyEvent.UserEvent );
				break;
			}
		}
		return false;
	}
};
