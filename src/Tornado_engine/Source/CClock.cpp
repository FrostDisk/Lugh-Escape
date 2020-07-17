/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Reloj                                    *
 * Archivo Fuente: CClock.h                                           *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CClock.h"

namespace Tornado
{
	//! Constante factor Horas
	static const real FactorHours = 1.f / 3600.f ;

	//! Constante factor Minutos
	static const real FactorMinutes  = 1.f / 60.f ;

	/**
	 * \brief Calcula el tiempo
	 */
	void CClock::UpdateTime(void)
	{
		uint16 mTemp;

		Hours = (uint16)( Time * FactorHours );
		mTemp = Hours * 3600;

		Minutes = (uint16)( ( Time - (real)( mTemp ) ) * FactorMinutes );
		mTemp += Minutes * 60;

		Seconds = (uint16)( Time - (real)( mTemp ) );
		Milliseconds = (uint16)( ( Time - (real)( mTemp + Seconds ) ) * 1000 );

		//COutput::Wprintf(L"%d:%d:%d.%d\n",Hours,Minutes,Seconds,Milliseconds);
	}

	/**
	 * \brief Calcula el tiempo guardado
	 */
	void CClock::UpdateSavedTime(void)
	{
		uint16 mTemp;

		SavedHours = (uint16)( SavedTime * FactorHours );
		mTemp = SavedHours * 3600;

		SavedMinutes = (uint16)( ( SavedTime - (real)( mTemp ) ) * FactorMinutes );
		mTemp += SavedMinutes * 60;

		SavedSeconds = (uint16)( SavedTime - (real)( mTemp ) );
		SavedMilliseconds = (uint16)( ( SavedTime - (real)( mTemp + SavedSeconds ) ) * 1000 );

		//COutput::Wprintf(L"%d:%d:%d.%d\n",Hours,Minutes,Seconds,Milliseconds);
	}

	/**
	 * \brief Constructor de Clase
	 * \param tmp_InitTime Tiempo inicial
	 * \param tmp_Reverse Si el reloj va hacia adelante o hacia atrás
	 * \param tmp_Speed Velocidad en la que se mueve el reloj
	 */
	CClock::CClock(	real initTime,
					bool isReverse,
					real clockSpeed ) :
						Active( true ),
						Reverse(isReverse),
						Time( initTime ),
						SavedTime( 0.0f ),
						Speed( clockSpeed ),
						Hours(0),
						Minutes(0),
						Seconds(0),
						Milliseconds(0),
						SavedHours(0),
						SavedMinutes(0),
						SavedSeconds(0),
						SavedMilliseconds(0),
						IsTimerActive(false),
						TimerCounter(0)
	{
		UpdateTime();
	}




};

