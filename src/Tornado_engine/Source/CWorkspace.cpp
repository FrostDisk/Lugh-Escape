/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Codigo Fuente de Clase Espacio de Trabajo                  *
 * Archivo Fuente: CWorkspace.cpp                                     *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CWorkspace.h"
#include "EElementPosition.h"
#include "EElementAlign.h"

namespace Tornado
{

	/**
	 * \brief Constructor de Clase
	 */
	CWorkspace::CWorkspace() :
						Width(0),
						Height(0)
	{
	}


	/*
	 * \brief Calcula una posición
	 * \param tmp_RectWidth Ancho del Rectangulo
	 * \param tmp_RectHeight Alto del Rectangulo
	 * \param tmp_Position Posicion donde se espera el rectangulo
	 * \param tmp_Align Alineación donde se espera el rectangulo
	 * \return Rectangulo con la posición en relación al Espacio de Trabajo
	 */
/*	irr::core::rect<irr::s32> &CWorkspace::GetRect(	const uint16 tmp_RectWidth,
													const uint16 tmp_RectHeight,
													const uint16 tmp_Position,
													const uint16 tmp_Align) {*/

/*		irr::core::vector2d<irr::s32> upperLeft;
		irr::core::vector2d<irr::s32> lowerRight;

		switch( tmp_Align ){

			case EEA_CENTER:{
				break;
			}

			case EEA_UPPERLEFT:{
				break;
			}

			case EEA_UPPERRIGHT:{
				break;
			}

			case EEA_UPPERCENTER:{
				break;
			}

			case EEA_DOWNLEFT:{
				break;
			}

			case EEA_DOWNRIGHT:{
				break;
			}

			case EEA_DOWNCENTER:{
				break;
			}

			case EEA_CENTERLEFT:{
				break;
			}

			case EEA_CENTERRIGHT:{
				break;
			}
		}

		switch( tmp_Position ){

			case EEP_CENTER:{

				break;
			}

			case EEP_UPPERLEFT:{
				break;
			}

			case EEP_UPPERRIGHT:{
				break;
			}

			case EEP_UPPERCENTER:{
				break;
			}

			case EEP_DOWNLEFT:{
				break;
			}

			case EEP_DOWNRIGHT:{
				break;
			}

			case EEP_DOWNCENTER:{
				break;
			}

			case EEP_CENTERLEFT:{
				break;
			}

			case EEP_CENTERRIGHT:{
				break;
			}

			default:{
				break;
			}
		}

		return irr::core::rect<irr::s32>( upperLeft , lowerRight );*/
/*		return irr::core::rect<irr::s32>( 0 , 0 , 0 , 0 );
	}*/
}
