#ifndef ___Tornado_XEffects__ShadowShaderCB__H___
#define ___Tornado_XEffects__ShadowShaderCB__H___

#include "EffectHandler.h"

namespace Tornado
{
	namespace XEffects
	{
		class ShadowShaderCB : public irr::video::IShaderConstantSetCallBack
		{
		public:
			ShadowShaderCB(EffectHandler* effectIn) : effect(effectIn) {};

			virtual void OnSetMaterial(const irr::video::SMaterial& material) {}

			virtual void OnSetConstants(irr::video::IMaterialRendererServices* services, irr::s32 userData)
			{
				irr::video::IVideoDriver* driver = services->getVideoDriver();

				irr::core::matrix4 worldViewProj = driver->getTransform(irr::video::ETS_PROJECTION);			
				worldViewProj *= driver->getTransform(irr::video::ETS_VIEW);
				worldViewProj *= driver->getTransform(irr::video::ETS_WORLD);
				services->setVertexShaderConstant("mWorldViewProj", worldViewProj.pointer(), 16);

				worldViewProj = ProjLink;			
				worldViewProj *= ViewLink;
				worldViewProj *= driver->getTransform(irr::video::ETS_WORLD);
				services->setVertexShaderConstant("mWorldViewProj2", worldViewProj.pointer(), 16);

				driver->getTransform(irr::video::ETS_WORLD).getInverse(invWorld);
				irr::core::vector3df lightPosOS = LightLink;
				invWorld.transformVect(lightPosOS); 
				services->setVertexShaderConstant("LightPos", reinterpret_cast<irr::f32*>(&lightPosOS.X), 4);
				
				services->setVertexShaderConstant("MaxD", reinterpret_cast<irr::f32*>(&FarLink), 1);
				services->setVertexShaderConstant("MAPRES", &MapRes, 1);

				services->setPixelShaderConstant("LightColour", reinterpret_cast<irr::f32*>(&LightColour.r), 4);
			}

			EffectHandler* effect;
			irr::core::matrix4 invWorld;

			irr::video::SColorf LightColour;
			irr::core::matrix4 ProjLink;
			irr::core::matrix4 ViewLink;
			irr::core::vector3df LightLink;
			irr::f32 FarLink, MapRes;
		};
	}
}

#endif
