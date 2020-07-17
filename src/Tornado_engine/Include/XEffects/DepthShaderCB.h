#ifndef ___Tornado_XEffects__DepthShaderCB__H___
#define ___Tornado_XEffects__DepthShaderCB__H___

#include "EffectHandler.h"

namespace Tornado
{
	namespace XEffects
	{
		class DepthShaderCB : public irr::video::IShaderConstantSetCallBack
		{
		public:
			DepthShaderCB(EffectHandler* effectIn) : effect(effectIn) {};

			virtual void OnSetConstants(irr::video::IMaterialRendererServices* services, irr::s32 userData)
			{
				irr::video::IVideoDriver* driver = services->getVideoDriver();

				worldViewProj = driver->getTransform(irr::video::ETS_PROJECTION);			
				worldViewProj *= driver->getTransform(irr::video::ETS_VIEW);
				worldViewProj *= driver->getTransform(irr::video::ETS_WORLD);

				services->setVertexShaderConstant("mWorldViewProj", worldViewProj.pointer(), 16);
				
				services->setVertexShaderConstant("MaxD", &FarLink, 1);
			}

			EffectHandler* effect;
			irr::f32 FarLink;
			irr::core::matrix4 worldViewProj;
		};
	}
}

#endif
