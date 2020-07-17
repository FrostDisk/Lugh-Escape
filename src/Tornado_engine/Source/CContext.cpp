/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Codigo Fuente de Clase Contexto                            *
 * Archivo Fuente: CContext.cpp                                       *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CContext.h"
#include "COutput.h"
#include "CVideo.h"

namespace Tornado
{

	/**
	 * \brief Constructor de Clase
	 * \param tmp_id ID de Contexto
	 * \param tmp_haveloading Indicador de si el Contexto tiene Tiempo de Carga
	 */
	CContext::CContext( uint16 contextId ,
						bool haveLoading ) :
									Id( contextId ),
									Finished( false ),
									Initialized( false ),
									HaveLoading( haveLoading ),
									LoadingInitialized( false ),
									LoadingFinished( false ),
									LoadingPercent( 0 ),
									NextContext( 0 ),
									GameDevices( NULL ),
									Width( 0 ),
									Height( 0 )
	{
	}

	/**
	 * \brief Destructor de Clase
	 */
	CContext::~CContext()
	{
		#if defined(_DEBUG)
		COutput::Wprintf(L"Destruyendo CContext(%d)\n",Id);
		#endif
		GameDevices = NULL;
	}

	/**
	 * \brief Inicializa las variables del Contexto
	 */
	bool CContext::Init(void)
	{

		return false;
	}

	/**
	 * \brief Muestra el primer cuadro
	 */
	void CContext::Prepare(void)
	{
	}

	/**
	 * \brief Calcula el siguiente cuadro
	 */
	void CContext::Next(real Delta)
	{
	}

	/**
	 * \brief Dibuja los elementos del contexto
	 */
	void CContext::Draw(void)
	{
	}

	/**
	 * \brief Termina el Contexto (se llama durante el cambio de Contexto)
	 */
	void CContext::End(void)
	{
	}

	/**
	 * \brief Prepara la escena de Tiempo de Carga
	 */
	bool CContext::LoadingInit(void)
	{
		return true;
	}

	/**
	 * \brief Prepara la escena de Tiempo de Carga
	 */
	void CContext::LoadingPrepare(void)
	{
	}

	/**
	 * \brief Calcula el siguiente cuadro del Tiempo de Carga
	 */
	void CContext::LoadingNext(real delta)
	{
	}

	/**
	 * \brief Dibuja la escena de Tiempo de Carga
	 */
	void CContext::LoadingDraw(void)
	{
	}

	/**
	 * \brief Se termina el Tiempo de Carga
	 */
	void CContext::LoadingEnd(void)
	{
	}

	/**
	 * \brief Cierra el contexto (cuando se termina el programa)
	 */
	void CContext::Close(void)
	{
	}

	/**
	 * \brief Inicializa las variables globales del contexto
	 */
	void CContext::SetGlobalVariables(void)
	{
		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
		//irr::gui::IGUISkin *skin = GameDevices->GUIEnvironment->GetGUISkin();
		//irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
		irr::core::rect<irr::s32> viewport = driver->getViewPort();

		Width = viewport.getWidth();
		Height = viewport.getHeight();
	}

	/**
	 * \brief Evento de GUI
	 * \param tmp_Caller Elemento que llamó el evento
	 * \param tmp_Element Si el Evento tiene que ver con otro elemento, será este puntero
	 * \param tmp_EventType Tipo de Evento
	 * \return FALSE
	 */
	bool CContext::OnGUIEvent(	irr::gui::IGUIElement *caller,
								irr::gui::IGUIElement *element,
								const uint16 &eventType )
	{
		return false;
	}

	/*bool CContext::OnJoystickEvent(const irr::SEvent::SJoystickEvent &Event){

		return true;
	}*/

	/**
	 * \brief Evento de Teclado
	 * \param tmp_Key Tecla presionada
	 * \param tmp_Char Código de tecla presionada
	 * \param tmp_isCtrl Si se presionó la tecla Ctrl
	 * \param tmp_isShift Si se presionó la tecla Shift
	 * \param tmp_isPressedDown Si se presionó o se soltó la tecla
	 * \return TRUE
	 */
	bool CContext::OnKeyInput(	const uint16 &key,
								const wchar_t &keyChar,
								const bool isCtrl,
								const bool isShift,
								const bool isPressedDown )
	{
		return false;
	}

	/**
	 * \brief Evento de Mouse
	 * \param tmp_EventType Evento
	 * \param tmp_X Posición X del Cursor
	 * \param tmp_Y Posición Y del Cursor
	 * \param tmp_Wheel Movimiento de la rueda
	 * \param tmp_isLeft Si se presionó el botón izquierdo
	 * \param tmp_isMiddle Si se presionó el botón central
	 * \param tmp_isRight Si se presionó el botón derecho
	 * \param tmp_isCtrl Si se presionó la tecla Ctrl
	 * \param tmp_isShift Si se presionó la tecla Shift
	 * \return TRUE
	 */
	bool CContext::OnMouseInput(const uint16 &eventType,
								const sint32 &mouseX,
								const sint32 &mouseY,
								const real &wheel,
								const bool isLeft,
								const bool isMiddle,
								const bool isRight,
								const bool isCtrl,
								const bool isShift)
	{
		return false;
	}

	/**
	 * \brief Evento de Usuario
	 * \param tmp_UserData1 Dato de usuario 1
	 * \param tmp_UserData2 Dato de usuario 2
	 * \return TRUE
	 */
	bool CContext::OnUserEvent(	const sint32 &userData1,
								const sint32 &userData2)
	{
		return false;
	}
};
