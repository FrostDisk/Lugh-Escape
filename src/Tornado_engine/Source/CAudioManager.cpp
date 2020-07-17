/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Codigo Fuente de Clase Manejador de Audio                  *
 * Archivo Fuente: CAudioManager.cpp                                  *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CAudioManager.h"
#include "CSystem.h"

namespace Tornado
{

	/**
	 * \brief Constructor de Clase
	 */
	CAudioManager::CAudioManager() : 
			AudioDevice(NULL),
			FileSystem(NULL)
	{
	}

	/**
	 * \brief Destructor de Clase
	 */
	CAudioManager::~CAudioManager()
	{
		AudioDevice = NULL;
		FileSystem = NULL;
	}

	/**
	 * \brief Inicializa el Manejador de Audio
	 * \return TRUE si el Manejador de Audio ha sido inicializado con éxito, FALSE en caso contrario.
	 */
	bool CAudioManager::Init(void)
	{
		return true;
	}

	/**
	 * \brief Crea un sonido
	 * \param tmp_File Ruta del Archivo
	 * \param tmp_Streaming Archivo de Streaming
	 * \param tmp_Format Formato de Archivo
	 * \return Referencia al Sonido creado
	 */
	audiere::OutputStream *CAudioManager::CreateOutputStream(	const char *streamPath ,
																bool isStreaming ,
																audiere::FileFormat fileFormat )
	{
		return audiere::OpenSound( AudioDevice , streamPath , isStreaming , fileFormat );
	}

	/**
	 * \brief Crea un sonido
	 * \param tmp_File Archivo a abrir
	 * \param tmp_Streaming Archivo de Streaming
	 * \param tmp_Format Formato de Archivo
	 * \return Referencia al Sonido creado
	 */
	audiere::OutputStream *CAudioManager::CreateOutputStream(	irr::io::IReadFile *streamPath ,
																bool isStreaming ,
																audiere::FileFormat fileFormat  )
	{
		if( !streamPath )
		{
			return NULL;
		}

		void* buffer = CSystem::Alloc( streamPath->getSize() );

		streamPath->read( buffer , streamPath->getSize() );

		// you need to create a mem file first
		audiere::FilePtr memFile = audiere::CreateMemoryFile( buffer, streamPath->getSize() );
		free( buffer );

		//tmp_File->drop();

		return audiere::OpenSound( AudioDevice , memFile, isStreaming , fileFormat );

	}
};
