#ifndef ___Tornado__Console__H___
#define ___Tornado__Console__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Salida                                   *
 * Archivo Fuente: COutput.h                                          *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <cstdlib>
#include <string.h>

namespace Tornado
{

	//! Clase Salida
	class COutput
	{

	private:
	protected:
	public:

		/**
		 * \brief Convierte de char* a wchar_t*
		 * \param Out String de salida
		 * \param Size Tamaño del string de entrada
		 * \param In String a convertir
		 * \param Count Numero de Caracteres a convertir
		 * \return 0 si la conversión fué con éxito
		 * \todo Esta función no está implementada en Linux
		 */
		inline static int MbsToWcs( wchar_t *Out , size_t Size , const char *In , size_t Count )
		{
			#if defined(WIN32)
			size_t *pReturnValue = NULL;
			return mbstowcs_s( pReturnValue , Out, Size , In , Count );
			#else
			#warning "COutput::MbsToWcs() No implementado en Linux"
			return 0;
			#endif
		}

		/**
		 * \brief Convierte de wchar_t* a char*
		 * \param Out String de salida
		 * \param Size Tamaño del string de entrada
		 * \param In String a convertir
		 * \param Count Numero de Caracteres a convertir
		 * \return 0 si la conversión fué con éxito
		 * \todo Esta función no está implementada en Linux
		 */
		inline static int WcsToMbs( char *Out , size_t Size , const wchar_t *In , size_t Count )
		{
			#if defined(WIN32)
			size_t *pReturnValue = NULL;
			return wcstombs_s( pReturnValue , Out , Size , In , Count );
			#else
			#warning "COutput::WcsToMbs() No implementado en Linux"
			return 0;
			#endif
		}

		/**
		 * \brief Abre un archivo
		 * \param File Puntero al puntero de archivo que recibirá el puntero del archivo abierto
		 * \param Path Nombre del archivo
		 * \param Mode Modo del Archivo
		 * \return 0 si el archivo ha sido abierto exitósamente
		 * \todo Esta función no está implementada en Linux
		 */
		inline static int Wfopen( FILE* File , const wchar_t *Path , const wchar_t *Mode )
		{
			#if defined(WIN32)
			return _wfopen_s( &File , Path , Mode );
			#else
			#warning "COutput::Wfopen() No implementado en Linux"
			return 0;
			#endif
		}

		/**
		 * \brief Cierra un archivo
		 * \param File Puntero al archivo
		 * \return 0 si el archivo ha sido cerrado exitosamente
		 * \todo Esta función no está implementada en Linux
		 */
		inline static int Fclose( FILE *File )
		{
			#if defined(WIN32)
			return fclose( File );
			#else
			#warning "COutput::Fclose() No implementado en Linux"
			return 0;
			#endif
		}

		/**
		 * \brief Vacia la memoria de un archivo
		 * \param File Puntero al archivo
		 * \return 0 si el archivo ha sido vaciado exitosamente
		 * \todo Esta función no está implementada en Linux
		 */
		inline static int Fflush( FILE *File )
		{
			#if defined(WIN32)
			return fflush( File );
			#else
			#warning "COutput::Fflush() No implementado en Linux"
			return 0;
			#endif
		}

		/**
		 * \brief Lee información de un archivo
		 * \param Buffer Lugar donde se guardarla la información leída
		 * \param Size Tamaño de la información en bytes
		 * \param Count Máximo número de veces que será leída la información
		 * \param Stream Puntero al archivo
		 * \return Número de elementos leídos
		 * \todo Esta función no está implementada en Linux
		 */
		inline static size_t Fread( void *Buffer , size_t Size , size_t Count , FILE *Stream )
		{
			#if defined(WIN32)
			return fread( Buffer , Size , Count , Stream );
			#else
			#warning "COutput::Fread() No implementado en Linux"
			return 0;
			#endif
		}

		/**
		 * \brief Lee información de un archivo
		 * \param Buffer Puntero a la información a escribir
		 * \param Size Tamaño de la información en bytes
		 * \param Count Máximo número de veces que será escrita la información
		 * \param Stream Puntero al archivo
		 * \return Número de elementos leídos
		 * \todo Esta función no está implementada en Linux
		 */
		inline static size_t Fwrite( const void *Buffer , size_t Size , size_t Count , FILE *Stream )
		{
			#if defined(WIN32)
			return fwrite( Buffer , Size , Count , Stream );
			#else
			#warning "COutput::Fwrite() No implementado en Linux"
			return 0;
			#endif
		}

		/**
		 * \brief Funcion equivalente a sprintf
		 * \param Out Cadena de caracteres de salida
		 * \param Format Cadena de caracteres con el formato
		 * \return El largo de la cadena generada
		 * \author NioZero, egyware
		 * \bug <b>[normal]</b> La función envia un SIGABRT que causa que se caiga en la versión Linux
		 */
		inline static int Wsprintf( wchar_t *Out , const wchar_t *Format , ... )
		{
			va_list args;
			int len;

			va_start( args, Format );

			#if defined(WIN32)

			// _vscprintf doesn't count terminating '\0'
			len = _vscwprintf( Format , args ) + 1 ;

			// Copiar el string formateado en la salida
			vswprintf_s( Out , len , Format , args );

			#else

			#warning TODO FIX BUG puse el valor 1024 para que no lanze SIGABRT seguir este error
			len = vswprintf( Out, 1024 , Format, args );

			#endif
            va_end( args );

			return len;
		}

		/**
		 * \brief Funcion equivalente a printf
		 * \param Format Cadena de caracteres con el formato
		 * \return El largo de la cadena generada
		 * \author NioZero
		 * \todo Esta función no está implementada en Linux
		 */
		inline static int Wprintf( const wchar_t *Format , ... )
		{
			va_list args;
			int len;
			va_start( args , Format );

			#if defined(WIN32)

			// Imprimir String formateado
			len = vwprintf_s( Format , args );

			#else
			#warning "COutput::Wprintf() No implementado en Linux"

			#endif
            va_end( args );

			return len;
		}

		/**
		 * \brief Copia un String
		 * \param Destination String Destino
		 * \param Elements Número de caracteres a copiar
		 * \param Source String Origen
		 * \author NioZero
		 * \return 0 Si el String se copió sin problemas, otro número en caso de error
		 * \todo Esta función no está implementada en Linux
		 */
		inline static int Wcscpy( wchar_t *Destination , size_t Elements , const wchar_t *Source )
		{
			#if defined(WIN32)
			return wcscpy_s( Destination , Elements , Source );
			#else
			#warning "COutput::Wcscpy() No implementado en Linux"
			return NULL;
			#endif
		}

		/**
		 * \brief Retorna el largo de un string
		 * \param String String a revisar
		 * \author NioZero
		 * \return Número de caracteres del string
		 * \todo Esta función no está implementada en Linux
		 */
		inline static size_t Wcslen( const wchar_t *String )
		{
			#if defined(WIN32)
			return wcslen( String );
			#else
			#warning "COutput::Wcscpy() No implementado en Linux"
			return NULL;
			#endif
		}

		/**
		 * \brief Compara un string con otro
		 * \param String1 String para comparar
		 * \param String2 String para comparar
		 * \return 0 si los string son iguales, <0 si String1 es menor a String2, >0 si String1 es mayor a String2
		 * \todo Esta función no está implementada en Linux
		 */
		inline static int Wstrcmp( const wchar_t *String1 , const wchar_t *String2 )
		{
			#if defined(WIN32)
			return wcscmp( String1 , String2 );
			#else
			#warning "COutput::Wstrcmp() No implementado en Linux"
			return 0;
			#endif
		}
	};
};

#endif
