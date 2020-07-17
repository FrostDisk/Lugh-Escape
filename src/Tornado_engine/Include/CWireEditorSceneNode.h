#ifndef ___Tornado__WireEditorSceneNode__H___
#define ___Tornado__WireEditorSceneNode__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Nodo Editor Malla                        *
 * Archivo Fuente: CWireEditorSceneNode.h                             *
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
	//! Clase Nodo Editor Malla
	class CWireEditorSceneNode : public irr::scene::ISceneNode
	{
	private:

		//! Caja de Colisión
		irr::core::aabbox3d<irr::f32> Box;

		//! Vértices
		irr::video::S3DVertex Vertices[4];

		//! Material
		irr::video::SMaterial Material;

	protected:
	public:
		CWireEditorSceneNode(irr::scene::ISceneNode* Parent, irr::scene::ISceneManager* SceneManager, irr::s32 Id);

		virtual void OnRegisterSceneNode();

		virtual void render();

		/**
		 * \brief Obtiene la Caja de Colisión
		 * \return Caja de Colisión
		 */
		virtual inline const irr::core::aabbox3d<irr::f32>& getBoundingBox() const
        {
			return Box;
        }

		/**
		 * \brief Obtiene el número de materiales
		 * \return Número de Materiales
		 */
		virtual inline irr::u32 getMaterialCount() const
        {
			return 1;
        }

		/**
		 * \brief Obtiene un Material
		 * \param i Id de material
		 * \return Material
		 */
		virtual inline irr::video::SMaterial& getMaterial(irr::u32 i)
        {
			return Material;
        }
	};
}

#endif
