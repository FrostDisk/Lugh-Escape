#ifndef ___Tornado__Video__H___
#define ___Tornado__Video__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Video                                    *
 * Archivo Fuente: CVideo.h                                           *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include <irrlicht.h>
#include "Constants.h"
#if defined(WIN32)
#include <windows.h>
#endif
#include <iostream>
#include <list>
#include "SVideoConfig.h"

namespace Tornado
{

	struct SVideoMode;
	class CEventReceiver;

	//! Clase Video
	class CVideo
	{

	private:

		//! Dispositivo de Video
		irr::IrrlichtDevice* VideoDevice;

		//! Controlador de Video
		irr::video::IVideoDriver* VideoDriver;

		//! Indicador si el Dispositivo de video ha sido inicializado
		bool VideoDevice__loaded;

		#if defined(WIN32)

		//! Dispositivo Win32
        HWND Win32Device;

		//! Manejador Win32 Irrlicht
		HWND Win32IrrHandle;

		//! Indicador si el Dispositivo Win32 ha sido inicializado
		bool Win32Device__loaded;
		#endif

		//! Configuración de Video
		SVideoConfig VideoConfig;

		//! Lista con los modos de video compatibles
		std::list<SVideoMode*> VideoModes_list;

		//! Número de modos de video compatibles
		uint16 VideoModes_num;

		//! Color de Video
		irr::video::SColor VideoColor;

		#if defined(WIN32)
		static LRESULT CALLBACK CustomWndProc(HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam);
		#endif

	protected:

	public:
		CVideo();
		~CVideo();

		#if defined(WIN32)
		bool InitWin32( const wchar_t *title );
		#endif

		bool Init( const wchar_t *title , bool resizable );

		/**
		 * \brief Retorna el Dispositivo de Video
		 * \return Dispositivo de Video
		 */
		inline irr::IrrlichtDevice *GetVideoDevice(void)
		{
			return VideoDevice;
		}

		/**
		 * \brief Retorna el Controlador de Video
		 * \return Controlador de Video
		 */
		inline irr::video::IVideoDriver *GetVideoDriver(void)
		{
			return VideoDriver;
		}

		/**
		 * \brief Retorna el tiempo actual de ejecución
		 * \return Tiempo actual de ejecución
		 */
		inline uint32 GetTime(void)
		{
			return VideoDevice->getTimer()->getTime();
		}

		/**
		 * \brief Recupera los modos de video compatibles
		 * \return Lista con los modos de video compatibles
		 */
		inline std::list<SVideoMode* > *GetVideoModes(void)
		{
			return &VideoModes_list;
		}

		/**
		 * \brief Comienza el dibujado de escena
		 */
		inline void BeginScene(void)
		{
			VideoDriver->beginScene(true,true,VideoColor);
		}

		/**
		 * \brief Termina el dibujado de escena
		 */
		inline void EndScene(void)
		{
			VideoDriver->endScene();
		}

		/**
		 * \brief Ejecuta el Video
		 */
		inline bool Run(void)
		{
			return VideoDevice->run();
		}

		/**
		 * \brief Pregunta si la ventana esta activa/visible
		 * \return TRUE si la ventana está activa, FALSE en caso contrario
		 */
		inline bool IsWindowActive(void)
		{
			return VideoDevice->isWindowActive();
		}

		/**
		 * \brief Pausa la ejecución del Video
		 */
		inline void Pause(void)
		{
			return VideoDevice->yield();
		}

		#if defined(WIN32)
		/**
		 * \brief Muestra la ventana Win32
		 */
		inline void Show(void)
		{
			if( Win32Device__loaded )
			{
				ShowWindow(Win32Device, SW_SHOW);
			}
		}

		/**
		 * \brief Actualiza la ventana Win32
		 */
		inline void Update(void)
		{
			if( Win32Device__loaded )
			{
				UpdateWindow(Win32Device);
			}
		}

		void ShowLastError(void);
		#endif

		/**
		 * \brief Cierra el Dispositivo de Video
		 */
		inline void Close(void)
		{
			VideoDevice->closeDevice();
		}


		/**
		 * \brief Finaliza el Dispositivo de Video
		 */
		inline void End(void)
		{
			VideoDevice->drop();
		}

		void RegisterVideoModes(void);
		__TORNADO_DLL_EXPORT void CreateScreenshot(void);
		void SetVideoConfig(SVideoConfig *Config);

		/**
		 * \brief Cambia el color de video
		 * \param Color Nuevo color del video
		 */
		inline void SetVideoColor(irr::video::SColor Color)
		{
			VideoColor = Color;
		}

		/**
		 * \brief Asigna el Receptor de Eventos actual
		 * \param EventReceiver Receptor de Eventos a asignar
		 */
		inline void SetEventReceiver(CEventReceiver *EventReceiver)
		{
			VideoDevice->setEventReceiver( reinterpret_cast<irr::IEventReceiver*>(EventReceiver) );
		}

		/**
		 * \brief Indica la visibilidad del cursor
		 * \param Visibility TRUE activar visibilidad, FALSE en caso contrario
		 */
		inline void SetCursorVisibility(bool Visibility)
		{
			VideoDevice->getCursorControl()->setVisible( Visibility );
		}


		/**
		 * \brief Agrega un Elemento al Sistema de Archivo
		 * \param Path Ruta del Elemento
		 * \param ArchiveType Tipo de Elemento
		 * \param Password Contraseña del Elemento
		 */
		inline bool AddFileArchive(	const irr::io::path Path,
									irr::io::E_FILE_ARCHIVE_TYPE ArchiveType,
									const irr::core::stringc& Password = "")
		{
			return VideoDevice->getFileSystem()->addFileArchive(Path,true,true,ArchiveType,Password);
		}
	};
};

#endif
