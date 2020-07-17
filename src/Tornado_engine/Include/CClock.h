#ifndef ___Tornado__Clock__H___
#define ___Tornado__Clock__H___

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

#include "Types.h"
#include "COutput.h"

namespace Tornado
{

	//! Clase Reloj
	class CClock
	{

	private:

		//! Modo Reversa
		bool Reverse;

		//! Reloj Activo
		bool Active;

		//! Suma de Tiempo
		real Time;

		//! Tiempo Guardado temporalmente
		real SavedTime;

		//! Velocidad de avance del tiempo
		real Speed;

		//! Horas
		int Hours;

		//! Minutos
		int Minutes;

		//! Segundos
		int Seconds;

		//! Milisegundos
		int Milliseconds;

		//! Horas guardadas
		int SavedHours;

		//! Minutos guardados
		int SavedMinutes;

		//! Segundos guardados
		int SavedSeconds;

		//! Milisegundos guardados
		int SavedMilliseconds;

		//! Indicador para temporizador
		bool IsTimerActive;

		//! Contador para temporizador
		real TimerCounter;

		__TORNADO_DLL_EXPORT void UpdateTime(void);
		__TORNADO_DLL_EXPORT void UpdateSavedTime(void);

	protected:
	public:
		__TORNADO_DLL_EXPORT CClock(real InitTime = 0.0f,bool Reverse = false,real Speed = 1.0f);

		/**
		 * \brief Actualiza el Reloj
		 * \param Delta Tiempo transcurrido
		 */
		inline void Next(real Delta)
		{
			if( Active ){
				Time += Speed * ( Reverse ? -Delta : Delta ) ;
				TimerCounter += Speed * ( IsTimerActive ? -Delta : 0.0f ) ;
				UpdateTime();
			}
		}

		/**
		 * \brief Inicia el Reloj
		 */
		inline void Start(void)
		{
			Active = true;
		}

		/**
		 * \brief Detiene el Reloj
		 */
		inline void Stop(void)
		{
			Active = false;
		}

		/**
		 * \brief Habilita el Temporizador
		 * \param seconds Segundos que estará activo el temporizador
		 */
		inline void EnableTimer( real seconds )
		{
		   IsTimerActive = true;
		   TimerCounter = seconds;
		}


		/**
		 * \brief Avisa cuando el Temporizador llegó a cero o no
		 * \return TRUE si el temporizador llegó a 0, FALSE en caso contrario
		 */
		inline bool WaitTimer( void )
		{
			return IsTimerActive && TimerCounter < 0.0f ? true : false ;
		}

		/**
		 * \brief Desactiva el temporizador
		 */
		inline void StopTimer(void)
		{
		   IsTimerActive = false;
		   TimerCounter = 0.0f;
		}

		/**
		 * \brief Guarda el Tiempo actual en una variable temporal
		 * \return Tiempo guardado
		 */
		inline real SaveTime(void)
		{
			SavedTime = Time ;
			UpdateSavedTime() ;
			return SavedTime ;
		}

		/**
		 * \brief Asigna el tiempo
		 */
		inline void SetTime(real time)
		{
			Time = time;
			UpdateTime();
		}

		/**
		 * \brief Asigna la velocidad del reloj
		 */
		inline void SetSpeed(real speed)
		{
			Speed = speed;
		}

		/**
		 * \brief Retorna si el reloj está activo
		 * \return TRUE si el reloj está activo, FALSE en caso contrario
		 */
		inline bool IsActive(void){
			return Active;
		}

		/**
		 * \brief Retorna un string con el tiempo formateado
		 * \return String con tiempo formateado HH:MM:SS.ms
		 */
		inline wchar_t *GetFullFormattedTime(void)
		{
			wchar_t *time = new wchar_t[13];
			COutput::Wsprintf( time , L"%02d:%02d:%02d.%03d" , Hours , Minutes , Seconds , Milliseconds );
			//COutput::Wprintf( L"%s\n", time );
			return time;
		}

		/**
		 * \brief Retorna un string con el tiempo formateado
		 * \return String con tiempo formateado HH:MM:SS
		 */
		inline wchar_t *GetNormalFormattedTime(void)
		{
			wchar_t *time = new wchar_t[13];
			COutput::Wsprintf( time , L"%02d:%02d:%02d" , Hours , Minutes , Seconds );
			//COutput::Wprintf( L"%s\n", time );
			return time;
		}

		/**
		 * \brief Retorna un string con el tiempo formateado
		 * \return String con tiempo formateado HH:MM
		 */
		inline wchar_t *GetTinyFormattedTime(void)
		{
			wchar_t *time = new wchar_t[13];
			COutput::Wsprintf( time , L"%02d:%02d" , Hours , Minutes );
			//COutput::Wprintf( L"%s\n", time );
			return time;
		}


		/**
		 * \brief Retorna un string con el tiempo formateado
		 * \return String con tiempo formateado HH:MM:SS.ms
		 */
		inline wchar_t *GetFullFormattedSavedTime(void)
		{
			wchar_t *time = new wchar_t[13];
			COutput::Wsprintf( time , L"%02d:%02d:%02d.%03d" , SavedHours , SavedMinutes , SavedSeconds , SavedMilliseconds );
			//COutput::Wprintf( L"%s\n", time );
			return time;
		}

		/**
		 * \brief Retorna un string con el tiempo formateado
		 * \return String con tiempo formateado HH:MM:SS
		 */
		inline wchar_t *GetNormalFormattedSavedTime(void)
		{
			wchar_t *time = new wchar_t[13];
			COutput::Wsprintf( time , L"%02d:%02d:%02d" , SavedHours , SavedMinutes , SavedSeconds );
			//COutput::Wprintf( L"%s\n", time );
			return time;
		}

		/**
		 * \brief Retorna un string con el tiempo formateado
		 * \return String con tiempo formateado HH:MM
		 */
		inline wchar_t *GetTinyFormattedSavedTime(void)
		{
			wchar_t *time = new wchar_t[13];
			COutput::Wsprintf( time , L"%02d:%02d" , SavedHours , SavedMinutes );
			//COutput::Wprintf( L"%s\n", time );
			return time;
		}

		/**
		 * \brief Retorna un string con el tiempo formateado
		 * \return String con tiempo formateado MM:SS.ms
		 */
		inline wchar_t *GetShortFullFormattedTime(void)
		{
			wchar_t *time = new wchar_t[13];
			COutput::Wsprintf( time , L"%02d:%02d.%03d" , Minutes , Seconds , Milliseconds );
			//COutput::Wprintf( L"%s\n", time );
			return time;
		}

		/**
		 * \brief Retorna un string con el tiempo formateado
		 * \return String con tiempo formateado MM:SS
		 */
		inline wchar_t *GetShortNormalFormattedTime(void)
		{
			wchar_t *time = new wchar_t[13];
			COutput::Wsprintf( time , L"%02d:%02d" , Minutes , Seconds );
			//COutput::Wprintf( L"%s\n", time );
			return time;
		}

		/**
		 * \brief Retorna un string con el tiempo formateado
		 * \return String con tiempo formateado MM
		 */
		inline wchar_t *GetShortTinyFormattedTime(void)
		{
			wchar_t *time = new wchar_t[13];
			COutput::Wsprintf( time , L"%02d" , Minutes );
			//COutput::Wprintf( L"%s\n", time );
			return time;
		}


		/**
		 * \brief Retorna un string con el tiempo formateado
		 * \return String con tiempo formateado MM:SS.ms
		 */
		inline wchar_t *GetShortFullFormattedSavedTime(void)
		{
			wchar_t *time = new wchar_t[13];
			COutput::Wsprintf( time , L"%02d:%02d.%03d" , SavedMinutes , SavedSeconds , SavedMilliseconds );
			//COutput::Wprintf( L"%s\n", time );
			return time;
		}

		/**
		 * \brief Retorna un string con el tiempo formateado
		 * \return String con tiempo formateado MM:SS
		 */
		inline wchar_t *GetShortNormalFormattedSavedTime(void)
		{
			wchar_t *time = new wchar_t[13];
			COutput::Wsprintf( time , L"%02d:%02d" , SavedMinutes , SavedSeconds );
			//COutput::Wprintf( L"%s\n", time );
			return time;
		}

		/**
		 * \brief Retorna un string con el tiempo formateado
		 * \return String con tiempo formateado MM
		 */
		inline wchar_t *GetShortTinyFormattedSavedTime(void)
		{
			wchar_t *time = new wchar_t[13];
			COutput::Wsprintf( time , L"%02d" , SavedMinutes );
			//COutput::Wprintf( L"%s\n", time );
			return time;
		}


		/**
		 * \brief Retorna el tiempo actual
		 * \return Tiempo actual
		 */
		inline real GetRealTime(void)
		{
			return Time;
		}

		/**
		 * \brief Retorna el Tiempo guardado
		 * \return Tiempo guardado
		 */
		inline real GetSavedTime(void)
		{
			return SavedTime;
		}
	};
};

#endif
