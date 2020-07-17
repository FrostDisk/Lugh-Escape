#ifndef ___Tornado__Config__H___
#define ___Tornado__Config__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Configuración                            *
 * Archivo Fuente: CConfig.h                                          *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "Constants.h"
#include <iostream>
#include <list>
#if defined(WIN32)
#include <shlwapi.h>
//! Tamaño máximo para la ruta de archivos
#define __TORNADO_PATH_LENGTH MAX_PATH
#else
#include <limits.h>
#define __TORNADO_PATH_LENGTH PATH_MAX
#endif
#include "COutput.h"
#include "Types.h"
#include "SConfigElement.h"

namespace Tornado
{

	//! Clase Configuración
	class CConfig
	{

	private:

		//! Lista con los elementos de configuración
		std::list< SConfigElement* > ConfigElements;

		//! Nombre del directorio "Equipo"
		wchar_t FolderTeam[ __TORNADO_PATH_LENGTH ];

		//! Nombre del directorio "Aplicación"
		wchar_t FolderSoftware[ __TORNADO_PATH_LENGTH ];

		//! Ruta para el espacio de trabjo
		wchar_t Path_Workspace[ __TORNADO_PATH_LENGTH ];

		//! Ruta para el directorio cache
		wchar_t Path_Cache[ __TORNADO_PATH_LENGTH ];

		//! Ruta para los archivos de salvado
		wchar_t Path_Savedata[ __TORNADO_PATH_LENGTH ];

		//! Ruta del archivo de configuración
		wchar_t File_GlobalConfig[ __TORNADO_PATH_LENGTH ];


	protected:
	public:
		CConfig();
		~CConfig();

		void CreateDefaultConfig(void);

		void CreateFolders(void);

		__TORNADO_DLL_EXPORT bool CreateFilenameProfilePath(wchar_t *Path,const wchar_t *Filename,const uint16 Location);

		/**
		 * \brief Registra un nuevo campo en la lista de configuración
		 * \param Type Tipo de Campo
		 * \param Name Nombre del Campo
		 * \param Default Valor por defecto del Campo
		 */
		__TORNADO_DLL_EXPORT inline void RegisterConfigElement(const wchar_t *Type,const wchar_t *Name,const wchar_t *Default)
		{
			RegisterConfigElement(new std::wstring(Type),new std::wstring(Name),new std::wstring(Default));
		}

		__TORNADO_DLL_EXPORT void RegisterConfigElement(std::wstring *Type,std::wstring *Name,std::wstring *Default);

		/**
		 * \brief Asigna el nombre de los directorios
		 * \param folderSoftware Nombre del directorio 'aplicación'
		 * \param folderTeam Nombre del directorio 'equipo'
		 */
		inline void SetFoldersName( const wchar_t *folderSoftware , const wchar_t *folderTeam )
		{
			COutput::Wcscpy( FolderTeam , __TORNADO_PATH_LENGTH , folderTeam );
			COutput::Wcscpy( FolderSoftware , __TORNADO_PATH_LENGTH , folderSoftware );
		}

		/**
		 * \brief Asigna un valor de campo en la lista de configuracion
		 * \param Type Tipo de Campo
		 * \param Name Nombre del Campo
		 * \param Value Valor del Campo
		 */
		__TORNADO_DLL_EXPORT inline void SetConfigElement(const wchar_t *Type,const wchar_t *Name,const wchar_t *Value)
		{
			SetConfigElement(new std::wstring(Type),new std::wstring(Name),new std::wstring(Value));
		}

		__TORNADO_DLL_EXPORT void SetConfigElement(std::wstring *Type,std::wstring *Name,std::wstring *Value);

		__TORNADO_DLL_EXPORT wchar_t *GetConfigElement(const wchar_t *Type,const wchar_t *Name);

		bool LoadConfigFile(void);
		bool SaveConfigFile(void);

	};

};

#endif
