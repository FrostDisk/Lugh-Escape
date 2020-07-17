/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Codigo Fuente de Clase Contexto de Título                  *
 * Archivo Fuente: CErrorContext.cpp                                  *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/


#include "CErrorContext.h"
#include "COutput.h"

namespace Tornado
{
	/**
	 * \brief Constructor de Clase
	 * \param tmp_id ID de Contexto
	 * \param tmp_haveloading Indicador de si el Contexto tiene Tiempo de Carga
	 */
	CErrorContext::CErrorContext(	uint16 contextId,
									bool haveLoading ) :
										CContext(contextId,haveLoading)
	{
	}

	/**
	 * \brief Destructor de Clase
	 */
	CErrorContext::~CErrorContext()
	{
		#if defined(_DEBUG)
		COutput::Wprintf(L"Destruyendo CErrorContext(%d)\n",GetId());
		#endif
	}

	/**
	 * \brief Inicializa las variables del Contexto
	 */
	bool CErrorContext::Init(void)
	{
		return false;
	}

	/**
	 * \brief Prepara la GUI de Inicio
	 */
	void CErrorContext::Prepare(void)
	{
	}

	/**
	 * \brief Calcula el siguiente cuadro
	 */
	void CErrorContext::Next(real delta)
	{
	}

	/**
	 * \brief Dibuja la GUI
	 */
	void CErrorContext::Draw(void)
	{
	}

	/**
	 * \brief Termina el Contexto (se llama durante el cambio de Contexto)
	 */
	void CErrorContext::End(void)
	{
	}

	/**
	 * \brief Prepara la escena de Tiempo de Carga
	 */
	bool CErrorContext::LoadingInit(void)
	{
		return true;
	}

	/**
	 * \brief Prepara la escena de Tiempo de Carga
	 */
	void CErrorContext::LoadingPrepare(void)
	{
	}

	/**
	 * \brief Calcula el siguiente cuadro del Tiempo de Carga
	 */
	void CErrorContext::LoadingNext(real delta)
	{
	}

	/**
	 * \brief Dibuja la escena de Tiempo de Carga
	 */
	void CErrorContext::LoadingDraw(void)
	{
	}

	/**
	 * \brief Se termina el Tiempo de Carga
	 */
	void CErrorContext::LoadingEnd(void)
	{
	}

	/**
	 * \brief Cierra el contexto (cuando se termina el programa)
	 */
	void CErrorContext::Close(void)
	{
	}

	/**
	 * \brief Evento de GUI
	 * \param Caller Elemento que llamó el evento
	 * \param Element Si el Evento tiene que ver con otro elemento, será este puntero
	 * \param EventType Tipo de Evento
	 * \return FALSE
	 */
	bool CErrorContext::OnGUIEvent(	irr::gui::IGUIElement *caller,
									irr::gui::IGUIElement *element,
									const uint16 &eventType )
	{
		return false;
	}
};
