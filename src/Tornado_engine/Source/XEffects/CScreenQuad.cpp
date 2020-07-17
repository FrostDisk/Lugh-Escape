#include "XEffects\CScreenQuad.h"

namespace Tornado
{
	namespace XEffects 
	{
		CScreenQuad::CScreenQuad()
		{
			Material.Wireframe = false;
			Material.Lighting = false;
			Material.ZWriteEnable = false;

			Vertices[0] = irr::video::S3DVertex(-1.0f,-1.0f,0.0f,0,0,1,irr::video::SColor(0x0),0.0f,1.0f);
			Vertices[1] = irr::video::S3DVertex(-1.0f, 1.0f,0.0f,0,0,1,irr::video::SColor(0x0),0.0f,0.0f);
			Vertices[2] = irr::video::S3DVertex( 1.0f, 1.0f,0.0f,0,0,1,irr::video::SColor(0x0),1.0f,0.0f);
			Vertices[3] = irr::video::S3DVertex( 1.0f,-1.0f,0.0f,0,0,1,irr::video::SColor(0x0),1.0f,1.0f);
			Vertices[4] = irr::video::S3DVertex(-1.0f,-1.0f,0.0f,0,0,1,irr::video::SColor(0x0),0.0f,1.0f);
			Vertices[5] = irr::video::S3DVertex( 1.0f, 1.0f,0.0f,0,0,1,irr::video::SColor(0x0),1.0f,0.0f);
		}

		void CScreenQuad::render(irr::video::IVideoDriver* driver)
		{
			irr::u16 indices[6] = {0, 1, 2, 3, 4, 5};

			driver->setMaterial(Material);
			driver->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
			driver->drawIndexedTriangleList(&Vertices[0], 6, &indices[0], 2);
		}

		irr::video::SMaterial& CScreenQuad::getMaterial()
		{
			return Material;
		}   
	};
};
