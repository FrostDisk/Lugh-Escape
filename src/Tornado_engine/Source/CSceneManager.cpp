/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Código Fuente de Clase Manejador de Escena                 *
 * Archivo Fuente: CSceneManager.h                                    *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CSceneManager.h"

namespace Tornado
{

	/**
	 * \brief Constructor de Clase
	 */
	CSceneManager::CSceneManager() :
		VideoDevice(NULL)
	{
	}

	/**
	 * \brief Destructor de Clase
	 */
	CSceneManager::~CSceneManager()
	{
		SceneManager = NULL;
		VideoDevice = NULL;
	}

	/**
	 * \brief Dibuja la escena
	 * \param driver Dispositivo de Video
	 */
	void CSceneManager::DrawScene(irr::video::IVideoDriver* videoDriver)
	{
		if( SceneManager )
		{

			// Dibujar todos los elementos del escenario
			SceneManager->drawAll();
		}
	}

	/**
	 * \brief Prepara la escena principal a cargar
	 */
	void CSceneManager::PrepareScene(void)
	{
		//irr::video::IVideoDriver* Driver = VideoDevice->getVideoDriver();
	}

	/**
	 * \brief Crea una cámara 3d-anaglyph
	 * \param pPlayerCamera Camara normal que se usa de referencia
	 * \return Referencia a la nueva cámara 3d-anaglyph
	 */
	irr::scene::ICameraSceneNode* CSceneManager::CreateAnaglyphCamera(irr::scene::ICameraSceneNode* pPlayerCamera)
	{
		irr::scene::ICameraSceneNode* pAnaglyphCamera;

		pAnaglyphCamera = SceneManager->addCameraSceneNode();
		pAnaglyphCamera->setInputReceiverEnabled(false);
		pAnaglyphCamera->setScale( pPlayerCamera->getScale());
		pAnaglyphCamera->setNearValue( pPlayerCamera->getNearValue());
		pAnaglyphCamera->setFarValue( pPlayerCamera->getFarValue());
		pAnaglyphCamera->setAspectRatio( pPlayerCamera->getAspectRatio());

		return pAnaglyphCamera;
	} 
};
