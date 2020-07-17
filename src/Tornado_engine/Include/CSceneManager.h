#ifndef ___Tornado__SceneManager__H___
#define ___Tornado__SceneManager__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Manejador de Escena                      *
 * Archivo Fuente: CSceneManager.h                                    *
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

	//! Clase Manejador de Escena
	class CSceneManager
	{

	private:

	protected:

		//! Manejador de Escena
		irr::scene::ISceneManager* SceneManager;

		//! Dispositivo de Video
		irr::IrrlichtDevice* VideoDevice;

	public:
		CSceneManager();
		~CSceneManager();

		/**
		 * \brief Carga la escena usando un archivo .irr
		 * \param Filename Archivo de Escena Irrlicht
		 */
		inline void LoadScene(const wchar_t* Filename)
		{
			SceneManager->clear();
			SceneManager->loadScene( Filename );
		}

		/**
		 * \brief Asigna el Dispositivo de Video
		 * \param Device Puntero a Dispositivo de Video
		 */
		inline void SetVideoDevice(irr::IrrlichtDevice* Device)
		{
			this->VideoDevice = Device;
		}

		/**
		 * \brief Obtiene el manejador de Escena
		 * \return Manejador de Escena
		 */
		inline irr::scene::ISceneManager* GetSceneManager(void)
		{
			return SceneManager;
		}

		/**
		 * \brief Retorna la camara activa
		 * \return Camara activa
		 */
		inline irr::scene::ICameraSceneNode *GetCamera(void)
		{
			return SceneManager->getActiveCamera();
		}

		/**
		 * \brief Inicializa el Manejador de Escena
		 * \return TRUE si el Manejador de Escena ha sido inicializado con éxito, FALSE en caso contrario
		 */
		inline bool Init(void)
		{
			if( VideoDevice != NULL )
			{
				SceneManager = VideoDevice->getSceneManager();
				return SceneManager ? true : false ;
			}
			return false;
		}

		virtual void DrawScene(irr::video::IVideoDriver* Driver);

		virtual void PrepareScene(void);

		/**
		 * \brief Limpia la escena completa (borra todos los nodos)
		 */
		inline void Clear(void)
		{
			SceneManager->clear();
		}

		irr::scene::ICameraSceneNode* CreateAnaglyphCamera(irr::scene::ICameraSceneNode* pPlayerCamera);
	};
};

#endif
