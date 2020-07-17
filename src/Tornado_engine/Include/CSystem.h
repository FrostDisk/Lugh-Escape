#ifndef ___Tornado__System__H___
#define ___Tornado__System__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electronico: frostdisk@gmail.com                            *
 * Módulo: Cabecera de Clase Sistema                                  *
 * Archivo Fuente: CSystem.h                                          *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CConfig.h"
#if defined(LINUX)
#include <cstdio>
#include <wchar.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

#if defined(WIN32)
#include <windows.h>
#endif

#include <stdlib.h>


namespace Tornado
{

	//! Clase Sistema
	class CSystem
	{

	private:
	protected:
	public:

		/**
		 * \brief Crea un directorio en la ruta asignada
		 * \param Path Ruta del directorio a crear
		 * \return Numero indicando si el directorio ha sido creado o no
		 */
		inline static int Mkdir(const wchar_t *Path)
		{
			#if defined(WIN32)
			return _wmkdir( Path );
			#else
            char Path_char[ __TORNADO_PATH_LENGTH ];
			sprintf(Path_char,"%ls",Path);
			return mkdir( Path_char , S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			#endif
		}

		/**
		 * \brief Verifica si una ruta de directorio existe
		 * \param Path Ruta de directorio a verificar
		 * \return TRUE si la ruta de directorio existe, FALSE en caso contrario
		 */
		inline static int CheckPath(const wchar_t *Path)
		{
			#if defined(WIN32)
			return PathFileExists( Path );
			#else
            struct stat stat_p;
            char filename[ __TORNADO_PATH_LENGTH ];
            sprintf(filename,"%ls",Path);
            stat (filename, &stat_p);
            return S_ISREG(stat_p.st_mode);
            #endif
		}

		/**
		 * \brief Obtiene el valor de un elemento de un archivo INI
		 * \param AppName Nombre de la sección
		 * \param KeyName Nombre de la clave
		 * \param Default Valor por defecto en caso de no existir
		 * \param Value Variable donde se guardará el valor obtenido
		 * \param size Tamaño del valor a obtener
		 * \param Filename Archivo INI a leer
		 * \todo Esta función no ha sido implementada en Linux
		 */
		inline static void GetIniItem(	const wchar_t *AppName,
										const wchar_t *KeyName,
										const wchar_t *Default,
										wchar_t *Value,
										int size,
										const wchar_t *Filename )
		{
			#if defined(WIN32)
			GetPrivateProfileString( AppName , KeyName , Default , Value , size , Filename );
			#else
			#warning "CSystem::GetIniItem() No implementado en Linux"
			#endif
		}

		/**
		 * \brief Guarda el valor de un elemento en un archivo INI
		 * \param AppName Nombre de la sección
		 * \param KeyName Nombre de la clave
		 * \param Value Variable donde se guardará el valor obtenido
		 * \param Filename Archivo INI a leer
		 * \return Estado de guardado
		 * \todo Esta función no ha sido implementada en Linux
		 */
		inline static int WriteIniItem(	const wchar_t *AppName,
										const wchar_t *KeyName,
										wchar_t *Value,
										const wchar_t *Filename )
		{
			#if defined(WIN32)
			return WritePrivateProfileString( AppName , KeyName , Value , Filename );
			#else
			#warning "CSystem::WriteIniItem() No implementado en Linux"
			return 0;
			#endif
		}

		/**
		 * \brief Concatena una ruta con otra
		 * \param Path Ruta original
		 * \param More Ruta a concatenar
		 * \return estado de la concatenación
		 * \todo Esta función no ha sido implementada en Linux
		 */
		inline static int Append( wchar_t *Path , const wchar_t *More )
		{
			#if defined(WIN32)
			return PathAppend( Path , More );
			#else
			#warning "CSystem::Append() No implementado en Linux"
			return 0;
			#endif
		}

		/**
		 * \brief Genera un número aleatorio
		 * \return Número aleatorio generado
		 * \todo Esta función no ha sido implementada en Linux
		 */
		inline static int Random( void )
		{
			#if defined(WIN32)
			return rand();
			#else
			#warning "CSystem::Random() No implementado en Linux"
			return 0;
			#endif
		}

		/**
		 * \brief Pide memoria al sistema
		 * \param size Tamaño de memoria a pedir
		 * \return Sector de memoria
		 */
		inline static void *Alloc(int size)
		{
			return malloc(size);
		}

		/**
		 * \brief Libera memoria del sistema
		 * \param ptr Sector de memoria a liberar
		 * \param size Tamaño del sector de memoria
		 */
		inline static void Free(void *ptr,int size)
		{
			free(ptr);
		}
	};
};

#endif
