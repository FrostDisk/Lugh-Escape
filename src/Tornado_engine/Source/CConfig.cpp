/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Codigo Fuente de Clase Configuración                       *
 * Archivo Fuente: CConfig.cpp                                        *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "Constants.h"
#include "CConfig.h"
#include "EPathLocation.h"
#include "Types.h"
#if defined(WIN32)
#include <shlobj.h>
#include <direct.h>
#else
#include <stdlib.h>
#include <string.h>
#endif
#include "CSystem.h"
#include "COutput.h"


namespace Tornado
{

    /**
	 * \brief Constructor de Clase
	 */
	CConfig::CConfig()
	{
	}

	/**
	 * \brief Destructor de Clase
	 */
	CConfig::~CConfig()
	{
	}

	/**
	 * \brief Crea la lista con los campos por defectos de las configuraciones
	 */
	void CConfig::CreateDefaultConfig(void)
	{
		for(std::list< SConfigElement* >::iterator it = ConfigElements.begin() ; it != ConfigElements.end() ; it++ )
		{
			(*it)->Value = (*it)->Default;
		}
	}

    // Anexar ruta de acceso especifica del programa
	/**
	 * \brief Crea los directorios temporales para el proyecto
	 * \todo Esta función no ha sido probada totalmente en Linux
	 */
	void CConfig::CreateFolders(void)
	{
		wchar_t szPath[ __TORNADO_PATH_LENGTH ];

		// Directorios que se crearan para este programa
		#if !defined(WIN32)
		#warning TODO recordar que TITLE_TEAM aqui debe ir oculto y con un '.'
		#endif
		wchar_t szFolder[2][ __TORNADO_PATH_LENGTH ];
		COutput::Wcscpy( szFolder[0] , __TORNADO_PATH_LENGTH , FolderTeam );
		COutput::Wcscpy( szFolder[1] , __TORNADO_PATH_LENGTH , FolderSoftware );

		// Obtener la ruta de acceso de cada usuario (itinerante).
		#if defined(WIN32)
		if ( SUCCEEDED( SHGetFolderPath( NULL, CSIDL_APPDATA, NULL, 0,szPath ) ) ) {
        #else
        char *home = getenv("HOME");
        if ( home != NULL)
		{
        #warning TODO Hay que reemplazar COutput::Wsprintf
        swprintf(szPath,__TORNADO_PATH_LENGTH,L"%s",home); //SIGABRT ? que sucede =S | FIXED con el tamaño de szPath
        #endif
        // Anexar ruta de acceso especifica del programa
			for( int i=0;i<2;i++)
			{
				CSystem::Append( szPath , szFolder[i] );
				if( CSystem::Mkdir( szPath ) == 0 )
				{
					#if defined(_DEBUG)
					COutput::Wprintf(L"Directory '%s' created.\n",szFolder[i]);
					#endif
				}
			}

			CSystem::Append( Path_Workspace , szPath );

			CSystem::Append( Path_Cache , Path_Workspace );
			CSystem::Append( Path_Cache , FOLDER_CACHE );
			if( CSystem::Mkdir( Path_Cache ) == 0 )
			{
				#if defined(_DEBUG)
				COutput::Wprintf(L"Directory '%s' created.\n",FOLDER_CACHE);
				#endif
			}

			CSystem::Append( Path_Savedata , Path_Workspace );
			CSystem::Append( Path_Savedata , FOLDER_SAVE );
			if( CSystem::Mkdir( Path_Savedata ) == 0 )
			{
				#if defined(_DEBUG)
				COutput::Wprintf(L"Directory '%s' created.\n",FOLDER_SAVE);
				#endif
			}

			CSystem::Append( File_GlobalConfig , Path_Workspace );
			CSystem::Append( File_GlobalConfig , FILE_CONFIG );

		}
	}

	/**
	 * \brief Crea una ruta de archivo en la carpeta de perfil de usuario
	 * \param Path String donde se guardara la ruta generada
	 * \param Filename Nombre de archivo a crear
	 * \param Location Ubicación en la que se quiere guardar el archivo
	 * \return TRUE si la ruta ha sido creada con éxito, FALSE en caso contrario
	 */
	bool CConfig::CreateFilenameProfilePath(wchar_t *outputPath,const wchar_t *fileName,const uint16 locationType){

		wchar_t szPath[ __TORNADO_PATH_LENGTH ];

		switch( locationType ){

			default:
			{
				return false;
				break;
			}

			// ruta por defecto del perfil
			case EPL_DEFAULT:
			{
				CSystem::Append( szPath , Path_Workspace );
				CSystem::Append( szPath , fileName );
				if( outputPath )
				{
					COutput::Wsprintf( outputPath , szPath );
					#if defined(_DEBUG)
					COutput::Wprintf( L"Path generated: %ls\n",outputPath);
					#endif
					return true;
				}
				return false;
				break;
			}

			// ruta del directorio 'cache' del perfil
			case EPL_CACHE:
			{
				CSystem::Append( szPath , Path_Cache );
				CSystem::Append( szPath , fileName );
				if( outputPath )
				{
					COutput::Wsprintf( outputPath , szPath );
					#if defined(_DEBUG)
					COutput::Wprintf( L"Path generated: %ls\n",outputPath);
					#endif
					return true;
				}
				return false;
				break;
			}

			// ruta del directorio 'save' del perfil
			case EPL_SAVEDATA:
			{
				CSystem::Append( szPath , Path_Savedata );
				CSystem::Append( szPath , fileName );
				if( outputPath )
				{
					COutput::Wsprintf( outputPath , szPath );
					#if defined(_DEBUG)
					COutput::Wprintf( L"Path generated: %ls\n",outputPath);
					#endif
					return true;
				}
				return false;
				break;
			}
		}

	}

	/**
	 * \brief Registra un nuevo campo en la lista de configuración de Video
	 * \param tmp_type Tipo de Campo
	 * \param tmp_name Nombre del Campo
	 * \param tmp_default Valor por defecto del Campo
	 */
	void CConfig::RegisterConfigElement(std::wstring *configType,std::wstring *configKeyName,std::wstring *configDefaultValue)
	{
		for(std::list< SConfigElement* >::iterator it = ConfigElements.begin() ; it != ConfigElements.end() ; it++ )
		{
			if( !wcscmp((*it)->Name->c_str(),configKeyName->c_str()) && !wcscmp((*it)->Type->c_str(),configType->c_str()) )
			{
				ConfigElements.erase( it );
				break;
			}
		}

		SConfigElement *auxConfigElement = new SConfigElement();

		auxConfigElement->Type = configType;
		auxConfigElement->Name = configKeyName;
		auxConfigElement->Default = configDefaultValue;

		ConfigElements.push_back( auxConfigElement );
	}

	/**
	 * \brief Asigna un valor de campo en la lista de configuracion de Video
	 * \param tmp_type Tipo de Campo
	 * \param tmp_name Nombre del Campo
	 * \param tmp_value Valor del Campo
	 */
	void CConfig::SetConfigElement(std::wstring *configType,std::wstring *configKeyName,std::wstring *configDefaultValue)
	{
		for(std::list< SConfigElement* >::iterator it = ConfigElements.begin() ; it != ConfigElements.end() ; it++ )
		{
			if( !wcscmp((*it)->Name->c_str(),configKeyName->c_str()) && !wcscmp((*it)->Type->c_str(),configType->c_str()) )
			{
				ConfigElements.erase( it );
				break;
			}
		}

		SConfigElement *auxConfigElement = new SConfigElement();

		auxConfigElement->Type = configType;
		auxConfigElement->Name = configKeyName;
		auxConfigElement->Value = configDefaultValue;

		ConfigElements.push_back( auxConfigElement );
	}

    /**
	 * \brief Retorna un elemento de configuracion
	 * \param tmp_type Tipo del Campo
	 * \param tmp_name Nombre del Campo
	 * \return Valor del Campo
	 */
	wchar_t *CConfig::GetConfigElement(const wchar_t *configType,const wchar_t *configKeyName)
	{
		for(std::list< SConfigElement* >::iterator it = ConfigElements.begin() ; it != ConfigElements.end() ; it++ )
		{
			if( !wcscmp((*it)->Name->c_str(),configKeyName) && !wcscmp((*it)->Type->c_str(),configType) )
			{
                wchar_t *value = (wchar_t*)CSystem::Alloc( sizeof(wchar_t) * 512 );
                COutput::Wsprintf( value , L"%ls", (*it)->Value->c_str() );
				return value;
			}
		}
		return NULL;
	}

	/**
	 * \brief Carga los datos guardados en el archivo de configuracion
	 * \return TRUE si los datos han sido cargados con éxito, FALSE en caso contrario
	 * \todo Esta función no ha sido implementada en Linux
	 */
    bool CConfig::LoadConfigFile(void)
	{
		CreateFolders();

		//#ifdef _DEBUG
		//printf("Archivo de Configuracion de lectura: %s\n",fileConfigPath);
		//#endif

		// Verificar que el archivo exista
		if( !CSystem::CheckPath( File_GlobalConfig ) )
		{
        	return false;
		}

		std::list< SConfigElement* > auxConfigElements;

		for(std::list< SConfigElement* >::iterator it = ConfigElements.begin() ; it != ConfigElements.end() ; it++ )
		{
			wchar_t auxType[512];
			wchar_t auxName[512];
			wchar_t auxValue[512];
			wchar_t auxDefault[512];
            COutput::Wsprintf( auxType , L"%ls" , (*it)->Type->c_str() );
			COutput::Wsprintf( auxName , L"%ls" , (*it)->Name->c_str() );
			COutput::Wsprintf( auxDefault , L"%ls" , (*it)->Default->c_str() );
            //CSystem::GetIniItem(auxType , auxName , auxDefault , auxValue , 512 , File_GlobalConfig);
			#if defined(WIN32)
            GetPrivateProfileString( auxType , auxName , auxDefault , auxValue , 512 , File_GlobalConfig );
            #else
            #warning CConfig::LoadConfigFile No implementado en Linux
            #endif


            CSystem::GetIniItem( auxType , auxName , auxDefault , auxValue , 512 , File_GlobalConfig );

			SConfigElement *auxElement = new SConfigElement;
			auxElement->Type = new std::wstring(auxType);
			auxElement->Name = new std::wstring(auxName);
			auxElement->Value = new std::wstring(auxValue);
			auxElement->Default = new std::wstring(auxDefault);
			auxConfigElements.push_back(auxElement);
		}
		ConfigElements.clear();
		for(std::list< SConfigElement* >::iterator it = auxConfigElements.begin() ; it != auxConfigElements.end() ; it++ )
		{
			ConfigElements.push_back( (*it) );
		}
		auxConfigElements.clear();

		return true;
	}

	/**
	 * \brief Salva los datos guardados en el archivo de configuracion
	 * \return TRUE si los datos han sido salvados con éxito, FALSE en caso contrario
	 */
    bool CConfig::SaveConfigFile(void)
	{
		CreateFolders();

		//#ifdef _DEBUG
		//printf("Archivo de Configuracion de escritura: '%s'\n",fileConfigPath);
		//#endif

		for(std::list< SConfigElement* >::iterator it = ConfigElements.begin() ; it != ConfigElements.end() ; it++ )
		{
			wchar_t auxType[512];
			wchar_t auxName[512];
			wchar_t auxValue[512];

            COutput::Wsprintf( auxType , L"%ls", (*it)->Type->c_str() );
			COutput::Wsprintf( auxName , L"%ls" , (*it)->Name->c_str() );
			COutput::Wsprintf( auxValue , L"%ls" , (*it)->Value->c_str() );

			/*int ret = */CSystem::WriteIniItem( auxType , auxName , auxValue , File_GlobalConfig );

			/*#ifdef _DEBUG
			if( ret )
			{
				printf("Escrito %s=%s\n",auxName,auxValue);
			}
			else
			{
				printf("No se pudo escribir '%s'\n",auxName);
			}
			#endif*/
		}

		return true;
	}

};

