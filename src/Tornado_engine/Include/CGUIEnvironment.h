#ifndef ___Tornado__GUIEnvironment__H___
#define ___Tornado__GUIEnvironment__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Ambiente GUI                             *
 * Archivo Fuente: CGUIEnvironment.h                                  *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include <irrlicht.h>

namespace Tornado
{

	//! Clase Ambiente GUI
	class CGUIEnvironment
	{

	private:

	protected:

		//! Puntero a Ambiente GUI
		irr::gui::IGUIEnvironment* GUIEnvironment;

		//! Dispositivo de Video
		irr::IrrlichtDevice* VideoDevice;

		//! Skin de GUI
		irr::gui::IGUISkin *GUISkin;


	public:
		CGUIEnvironment();
		~CGUIEnvironment();

		/**
		 * \brief Asigna el Dispositivo de Video
		 * \param Device Puntero a Dispositivo de Video
		 */
		inline void SetVideoDevice(irr::IrrlichtDevice* Device)
		{
			this->VideoDevice = Device;
		}

		/**
		 * \brief Inicializa el Ambiente GUI
		 * \return TRUE si el Ambiente GUI ha sido inicializado con éxito, FALSE en caso contrario
		 */
		inline bool Init(void)
		{
			if( VideoDevice != NULL )
			{
				GUIEnvironment = VideoDevice->getGUIEnvironment();
				GUISkin = GUIEnvironment->getSkin();
				return true;
			}
			return false;
		}

		/**
		 * \brief Retorna un Puntero al Ambiente GUI
		 * \return Puntero a Ambiente GUI
		 */
		inline irr::gui::IGUIEnvironment* GetGUIEnvironment(void)
		{
			return GUIEnvironment;
		}

		/**
		 * \brief Retorna un Puntero al Skin GUI
		 * \return Puntero a Skin GUI
		 */
		inline irr::gui::IGUISkin* GetGUISkin(void)
		{
			return GUISkin;
		}


		/**
		 * \brief Dibuja la GUI
		 * \param Driver Puntero a Dispositivo de Video
		 */
		inline void DrawGUI(irr::video::IVideoDriver* Driver)
		{
			if( GUIEnvironment )
			{
				GUIEnvironment->drawAll();
			}
		}

		virtual void PrepareGUI(void);

		/**
		 * \brief Limpia la GUI
		 */
		inline void Clear(void)
		{
			GUIEnvironment->clear();
		}
	};
};

#endif
