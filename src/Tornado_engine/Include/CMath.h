#ifndef ___Tornado__Math__H___
#define ___Tornado__Math__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Matemática                               *
 * Archivo Fuente: CMath.h                                            *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/
#if defined(LINUX)
#include <stddef.h>
#include <inttypes.h>
#endif

namespace Tornado
{

	//! Clase Matemática
	class CMath
	{

	private:
	protected:
	public:

		/**
		 * \brief Convertir una cadena de texto a nmero
		 * \param Str String a convertir
		 * \return Número que representa el string, 0 en caso de no ser número
		 */
		static inline int Wtoi( const wchar_t *Str )
		{
			#if defined(WIN32)
			return _wtoi( Str );
			#else
			return ((int) wcstoimax ( Str , (wchar_t **)NULL, 10));
			#endif
		}

		/**
		 * \brief Calcula el valor absoluto de un valor
		 * \param Value Número
		 * \return Valor Absoluto del número
		 * \todo Esta función no está implementada en Linux
		 */
		static inline real Fabs( const real Value )
		{
			#if defined(WIN32)
			return fabs( Value );
			#else
			#warning "COutput::Fabs() No implementado en Linux"
			return 0;
			#endif
		}
	};
};

#endif
