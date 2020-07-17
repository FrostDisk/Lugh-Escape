/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Código Fuente de Clase Video                               *
 * Archivo Fuente: CVideo.cpp                                         *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CVideo.h"
#include "COutput.h"
#include "SVideoConfig.h"
#include "SVideoMode.h"
#include "Constants.h"

#if defined(WIN32)
#include <Strsafe.h>
#endif

namespace Tornado
{

	#if defined(WIN32)

	/**
	 * \brief Procedimiento de ventana basico
	 * \param hWnd Manejador de Ventana
	 * \param message Mensaje recibido
	 * \param wParam Parámetro W
	 * \param lParam Parámetro L
	 */
    LRESULT CALLBACK CVideo::CustomWndProc(HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
    #endif

	/**
	 * \brief Constructor de Clase
	 */
	CVideo::CVideo() :	VideoDevice(NULL),
						VideoDriver(NULL),
						VideoDevice__loaded(false),
						#if defined(WIN32)
						Win32Device(),
						Win32IrrHandle(),
						Win32Device__loaded(false),
						#endif
						VideoConfig(),
						VideoModes_list(),
						VideoModes_num(0),
						VideoColor()
	{
	}

	/**
	 * \brief Destructor de Clase
	 */
	CVideo::~CVideo()
	{
		VideoDevice = NULL;
	}

	#if defined(WIN32)
	/**
	 * \brief Inicializa el Video en Modo Win32
	 * \param TitleWindow Titulo de la Ventana
	 * \return TRUE si el Video ha sido inicializado con éxito, FALSE en caso contrario.
	 */
	bool CVideo::InitWin32( const wchar_t *windowTitle )
	{

		HINSTANCE hInstance = 0;
		// create dialog

		const wchar_t* Win32ClassName = L"C_TornadoDialog";

		WNDCLASSEX wcex;
		wcex.cbSize             = sizeof(WNDCLASSEX);
		wcex.style              = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc        = (WNDPROC)CVideo::CustomWndProc;
		wcex.cbClsExtra         = 0;
		wcex.cbWndExtra         = DLGWINDOWEXTRA;
		wcex.hInstance          = hInstance;
		wcex.hIcon              = 0L;
		wcex.hCursor            = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground      = (HBRUSH)(COLOR_WINDOW);
		wcex.lpszMenuName       = 0;
		wcex.lpszClassName      = Win32ClassName;
		wcex.hIconSm            = 0;

		RegisterClassEx(&wcex);

		DWORD style = WS_SYSMENU | WS_BORDER | WS_CAPTION |
				WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_MINIMIZEBOX;

		Win32Device = CreateWindow(	Win32ClassName,windowTitle,
									style,
									100,100,
									VideoConfig.Width,VideoConfig.Height,
									0L,0L,
									hInstance,0L);

		if( !Win32Device )
		{
			ShowLastError();
			return false;
		}

		RECT clientRect;
		GetClientRect(Win32Device,&clientRect);
		int windowWidth = clientRect.right;
		int windowHeight = clientRect.bottom;


		// create window to put irrlicht in
		Win32IrrHandle = CreateWindow(	L"BUTTON", L"",
										WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
										0,0,
										windowWidth, windowHeight,
										Win32Device,0L,
										hInstance,0L);

		if( !Win32IrrHandle )
		{
			ShowLastError();
			return false;
		}

		Win32Device__loaded = true;

		return true;
	}
	#endif

	/**
	 * \brief Inicializa el Video
	 * \param TitleWindow Titulo de la Ventana
	 * \param ResizableWindow Ventana de tamaño variable
	 * \return TRUE si el Video ha sido inicializado con éxito, FALSE en caso contrario.
	 */
	bool CVideo::Init( const wchar_t *titleWindow , bool resizableWindow )
	{

		irr::SIrrlichtCreationParameters deviceConfig;

		switch( VideoConfig.Driver )
		{

			default:
			#if defined(WIN32)
			case 1:deviceConfig.DriverType = irr::video::EDT_DIRECT3D9;break;
			case 2:deviceConfig.DriverType = irr::video::EDT_DIRECT3D8;break;
			case 3:deviceConfig.DriverType = irr::video::EDT_OPENGL;break;
			//case 4:deviceConfig.DriverType = irr::video::EDT_SOFTWARE;break;
			#else
			case 1:deviceConfig.DriverType = irr::video::EDT_OPENGL;break;
			//case 2:deviceConfig.DriverType = irr::video::EDT_SOFTWARE;break;
			#endif
			//case 5:deviceConfig.DriverType = irr::video::EDT_NULL;break;
			//case 6:deviceConfig.DriverType = irr::video::EDT_BURNINGSVIDEO;break;
		}

		// Cargar irrlicht como Ventana Win32
		#if defined(WIN32)
		if( Win32Device__loaded )
		{
			deviceConfig.WindowId = reinterpret_cast<void*>(Win32IrrHandle);
		}
		else 
		{
		#endif

			deviceConfig.Bits = VideoConfig.Bits;
			deviceConfig.AntiAlias = VideoConfig.Antialiasing;
			deviceConfig.Fullscreen = VideoConfig.Fullscreen;
			deviceConfig.WindowSize = irr::core::dimension2d<irr::s32>(	VideoConfig.Width , VideoConfig.Height );
			deviceConfig.Stencilbuffer = VideoConfig.StencilShadow;
			deviceConfig.Vsync = VideoConfig.VerticalSync;

		#if defined(WIN32)
		}
		#endif
		//deviceConfig.EventReceiver = NULL;

		if( ( VideoDevice = irr::createDeviceEx( deviceConfig ) ) )
		{

			VideoDevice->setWindowCaption( titleWindow );
			VideoDevice->setResizable( resizableWindow );
			/*#if !defined(_DEBUG) && defined(WIN32)
			if( Win32Device__loaded )
			{
				VideoDevice->setWindowCaption( TITLE_WINDOW );
			}
			#endif*/

			VideoDriver = VideoDevice->getVideoDriver();
			VideoDevice__loaded = true;

			return true;
		}
		#if defined(_DEBUG)
		COutput::Wprintf(L"There was a problem initializing Video\n");
		#endif
		return false;
	}

	#if defined(WIN32)
	/**
	 * \brief Muestra el último error de WinAPI
	 */
	void CVideo::ShowLastError(void)
	{

		LPVOID lpMsgBuf;
		LPVOID lpDisplayBuf;
		DWORD dw = GetLastError(); 

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpMsgBuf,
			0, NULL );

	    // Display the error message and exit the process
		lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
			(lstrlen((LPCTSTR)lpMsgBuf) + 55) * sizeof(TCHAR)); 
		StringCchPrintf((LPTSTR)lpDisplayBuf, 
			LocalSize(lpDisplayBuf) / sizeof(TCHAR),
			TEXT("TornadoWin32 failed with error %d: %s"), 
			dw, lpMsgBuf); 
		MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);
		ExitProcess(dw); 
	}
	#endif

	/**
	 * \brief Guarda en una lista los modos de video disponibles
	 */
	void CVideo::RegisterVideoModes(void)
	{

		irr::IrrlichtDevice* device = irr::createDevice(irr::video::EDT_NULL);

		irr::video::IVideoModeList *IrrVideoModes = device->getVideoModeList();
		VideoModes_num = 0;

		for( int i=0 ; i<IrrVideoModes->getVideoModeCount() ; i++ )
		{

			irr::core::dimension2d< irr::s32 > dimension;
			dimension = IrrVideoModes->getVideoModeResolution(i);
			int depth = IrrVideoModes->getVideoModeDepth(i);

			if( dimension.Width>=800 && depth>=16 )
			{

				SVideoMode *tempMode = new SVideoMode();

				tempMode->id = i;
				tempMode->width = dimension.Width;
				tempMode->height = dimension.Height;
				tempMode->bpp = depth;

				VideoModes_list.push_back( tempMode );
				VideoModes_num += 1;
			}
		}
	}

	/**
	 * \brief Genera una captura de pantalla del video
	 * \todo Hay que optimizar esta función
	 */
	void CVideo::CreateScreenshot(void)
	{

		/*
		irr::video::IVideoDriver* driver = VideoDevice->getVideoDriver();

		irr::video::IImage* image = driver->createScreenShot();

		uint16 Number = 0;

		// Esta función debe ser modificada para que utilice
		// la ruta de directorio generada por la clase CConfig
		if(image){
			FILE *f = NULL;
			wchar_t buf[256];
			// Optimizar esto
			do {
				_snwprintf_s(buf, 256, L"capture%04d.jpg",++Number);
			} while( _wfopen_s(&f,buf,L"r")==0 );

			driver->writeImageToFile(image, buf, 85 );
			image->drop();
		}
		*/
	}

	/**
	 * \brief Cambia la configuracion de video
	 */
	void CVideo::SetVideoConfig(SVideoConfig *videoConfig)
	{
		if( videoConfig!=NULL )
		{
			VideoConfig.Driver = videoConfig->Driver;
			VideoConfig.Bits = videoConfig->Bits;
			VideoConfig.Antialiasing = videoConfig->Antialiasing;
			VideoConfig.Fullscreen = videoConfig->Fullscreen;
			VideoConfig.VerticalSync = videoConfig->VerticalSync;
			VideoConfig.StencilShadow = videoConfig->StencilShadow;
			VideoConfig.AnaglyphMode = videoConfig->AnaglyphMode;
			VideoConfig.Width = videoConfig->Width;
			VideoConfig.Height = videoConfig->Height;
		}
	}
};
