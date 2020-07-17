#ifndef ___Tornado_XEffects__ShadowLight__H___
#define ___Tornado_XEffects__ShadowLight__H___

namespace Tornado
{
	namespace XEffects
	{
		struct SShadowLight
		{
			/// Shadow light constructor. The first parameter is the square shadow map resolution.
			/// This should be a power of 2 number, and within reasonable size to achieve optimal
			/// performance and quality. Recommended sizes are 512 to 4096 subject to your target
			/// hardware and quality requirements. The next two parameters are position and target,
			/// the next one is the light color. The next two are very important parameters,
			/// the far value and the near value. The higher the near value, and the lower the
			/// far value, the better the depth precision of the shadows will be, however it will
			/// cover a smaller volume. The next is the FOV, if the light was to be considered
			/// a camera, this would be similar to setting the camera's field of view. The last
			/// parameter is whether the light is directional or not, if it is, an orthogonal
			/// projection matrix will be created instead of a perspective one.
			SShadowLight(	const irr::u32 id,
							const irr::u32 shadowMapResolution,
							const irr::core::vector3df& position, 
							const irr::core::vector3df& target,
							irr::video::SColorf lightColour = irr::video::SColor(0xffffffff), 
							irr::f32 nearValue = 10.0,
							irr::f32 farValue = 100.0,
							irr::f32 fov = 90.0 * irr::core::DEGTORAD64,
							bool directional = false ) :
									pos(position),
									tar(target),
									farPlane(directional ? 1.0f : farValue),
									diffuseColour(lightColour), 
									mapRes(shadowMapResolution),
									lightId(id)
			{
				nearValue = nearValue <= 0.0f ? 0.1f : nearValue;

				updateViewMatrix();

				if(directional)
					projMat.buildProjectionMatrixOrthoLH(fov, fov, nearValue, farValue);
				else
					projMat.buildProjectionMatrixPerspectiveFovLH(fov, 1.0f, nearValue, farValue);
			}

			/// Sets the light's position.
			inline void setPosition(const irr::core::vector3df& position)
			{
				pos = position;
				updateViewMatrix();
			}

			inline void setId( const irr::u32 id )
			{
				lightId = id;
			}

			/// Sets the light's target.
			inline void setTarget(const irr::core::vector3df& target)
			{
				tar = target;
				updateViewMatrix();
			}

			/// Gets the light's position.
			inline const irr::core::vector3df& getPosition() const
			{
				return pos;
			}

			/// Gets the light's target.
			inline const irr::core::vector3df& getTarget()  const
			{
				return tar;
			}

			/// Sets the light's view matrix.
			inline void setViewMatrix(const irr::core::matrix4& matrix)
			{
				viewMat = matrix;
				irr::core::matrix4 vInverse;
				viewMat.getInverse(vInverse);
				pos = vInverse.getTranslation();
			}

			/// Sets the light's projection matrix.
			inline void setProjectionMatrix(const irr::core::matrix4& matrix)
			{
				projMat = matrix;
			}

			/// Gets the light's view matrix.
			inline irr::core::matrix4& getViewMatrix()
			{
				return viewMat;
			}

			/// Gets the light's projection matrix.
			inline irr::core::matrix4& getProjectionMatrix()
			{
				return projMat;
			}

			/// Gets the light's far value.
			inline irr::f32 getFarValue() const
			{
				return farPlane;
			}

			/// Gets the light's color.
			inline const irr::video::SColorf& getLightColor() const
			{
				return diffuseColour;
			}

			/// Gets the light's Id
			inline irr::u32 getId() const
			{
				return lightId;
			}

			/// Sets the light's color.
			inline void setLightColor(const irr::video::SColorf& lightColour) 
			{
				diffuseColour = lightColour;
			}

			/// Sets the shadow map resolution for this light.
			inline void setShadowMapResolution(const irr::u32 shadowMapResolution)
			{
				mapRes = shadowMapResolution;
			}

			/// Gets the shadow map resolution for this light.
			inline const irr::u32 getShadowMapResolution() const
			{
				return mapRes;
			}

		private:

			inline void updateViewMatrix()
			{
				viewMat.buildCameraLookAtMatrixLH(pos, tar,
					(pos - tar).dotProduct(irr::core::vector3df(1.0f, 0.0f, 1.0f)) == 0.0f ?
					irr::core::vector3df(0.0f, 0.0f, 1.0f) : irr::core::vector3df(0.0f, 1.0f, 0.0f)); 
			}

			irr::video::SColorf diffuseColour;
			irr::core::vector3df pos, tar;
			irr::f32 farPlane;
			irr::core::matrix4 viewMat, projMat;
			irr::u32 mapRes;
			irr::u32 lightId;
		};
	}
}

#endif
