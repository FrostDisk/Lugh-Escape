#ifndef ___Tornado_XEffects__ScreenQuad__H___
#define ___Tornado_XEffects__ScreenQuad__H___

// Based on "CBaseFilter" by ItIsFree.
// Original thread: http://irrlicht.sourceforge.net/phpBB2/viewtopic.php?t=9857

#include <irrlicht.h>

namespace Tornado
{
	namespace XEffects
	{
		class CScreenQuad
		{
		public:
			CScreenQuad();

			virtual void render(irr::video::IVideoDriver* driver);

			virtual irr::video::SMaterial& getMaterial();

			irr::video::ITexture* rt[2];

		private:
			irr::video::S3DVertex Vertices[6];
			irr::video::SMaterial Material;
		};
	}
}
#endif
