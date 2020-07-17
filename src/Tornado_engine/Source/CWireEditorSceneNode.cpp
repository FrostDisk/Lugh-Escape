/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Código Fuente de Clase Nodo Editor Malla                   *
 * Archivo Fuente: CWireEditorSceneNode.cpp                           *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CWireEditorSceneNode.h"

namespace Tornado
{
	/**
	 * \brief Constructor de Clase
	 * \param tmp_Parent Nodo Padre
	 * \param tmp_SceneManager Manejador de Escena
	 * \param tmp_Id ID de Nodo
	 */
	CWireEditorSceneNode::CWireEditorSceneNode(	irr::scene::ISceneNode* parentSceneNode,
												irr::scene::ISceneManager* sceneManager,
												irr::s32 nodeId) :
													irr::scene::ISceneNode(parentSceneNode,sceneManager,nodeId)
	{
		Material.Wireframe = false;
		Material.Lighting = false;

		/*for( irr::s32 i=-20.0f ; i<20.0f ; i+=1.0f )
		{
			for( irr::s32 j=-20.0f ; j<20.0f ; j+=1.0f )
			{
				Vertices[ i*20.0f + j ] = irr::video::S3DVertex( i,0,j, 1,1,0,
											irr::video::SColor(255,0,255,255), 0, 1);
			}
		}*/

		Vertices[0] = irr::video::S3DVertex(0,0,10, 1,1,0,
						irr::video::SColor(255,0,255,255), 0, 1);
		Vertices[1] = irr::video::S3DVertex(10,0,-10, 1,0,0,
						irr::video::SColor(255,255,0,255), 1, 1);
		Vertices[2] = irr::video::S3DVertex(0,20,0, 0,1,1,
						irr::video::SColor(255,255,255,0), 1, 0);
		Vertices[3] = irr::video::S3DVertex(-10,0,-10, 0,0,1,
						irr::video::SColor(255,0,255,0), 0, 0);

		Box.reset(Vertices[0].Pos);
		for (irr::s32 i=1; i<4; ++i)
		{
			Box.addInternalPoint(Vertices[i].Pos);
		}

	}

	/**
	 * \brief Registra el Nodo en el Manejador de Escena
	 */
	void CWireEditorSceneNode::OnRegisterSceneNode(void)
	{
		if (IsVisible)
		{
			SceneManager->registerNodeForRendering(this);
		}

		ISceneNode::OnRegisterSceneNode();
	}

	/**
	 * \brief Dibuja el Nodo
	 */
	void CWireEditorSceneNode::render(void)
	{
		irr::u16 indices[] = {       0,2,3, 2,1,3, 1,0,3, 2,0,1      };
		irr::video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setMaterial(Material);
		driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);
		driver->drawVertexPrimitiveList(&Vertices[0], 4, &indices[0], 4, irr::video::EVT_STANDARD, irr::scene::EPT_TRIANGLES, irr::video::EIT_16BIT);
	}

}