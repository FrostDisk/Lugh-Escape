#ifndef ___Tornado__Effects__H___
#define ___Tornado__Effects__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Efectos                                  *
 * Archivo Fuente: CEffects.h                                         *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include <irrlicht.h>
#include <XEffects\XEffects.h>

namespace Tornado
{
	//! Clase Efectos
	class CEffects
	{

	private:

		//! Manejador de Efectos
		XEffects::EffectHandler* Effects;

		//! Dispositivo de Video
		irr::IrrlichtDevice* VideoDevice;

		//! Activar Sombras VSM
		bool UseVSMShadows;
		
		//! Luces Spot Redondas
		bool UseRoundSpotLights;
		
		//! Buffer de profundidad de 32bit
		bool Use32BitDepthBuffers;

	protected:
	public:
		CEffects();
		~CEffects();

		/**
		 * \brief Establece los parámetros para XEffects
		 * \param useVSMShadows Activar Sombras VSM
		 * \param useRoundSpotLights Activar Sombras Spot redondeadas
		 * \param use32BitDepthBuffers Activar Buffer de profundidad de 32bit
		 */
		inline void SetParameters(	bool useVSMShadows = false ,
									bool useRoundSpotLights = false ,
									bool use32BitDepthBuffers = false )
		{
			this->UseVSMShadows = useVSMShadows ;
			this->UseRoundSpotLights = useRoundSpotLights ;
			this->Use32BitDepthBuffers = use32BitDepthBuffers ;
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
		 * \brief Inicializa los Efectos
		 * \return TRUE si los Efectos han sido inicializados con éxito, FALSE en caso contrario
		 */
		inline bool Init(void)
		{
			if( VideoDevice )
			{
				Effects = new XEffects::EffectHandler( VideoDevice , VideoDevice->getVideoDriver()->getScreenSize() , UseVSMShadows , UseRoundSpotLights , Use32BitDepthBuffers  );
				return Effects != NULL ;
			}
			return false;
		}

		/**
		 * \brief Actualiza los efectos
		 */
		inline void Update(void)
		{
			if( Effects )
			{
				Effects->update();
			}
		}

		/**
		 * \brief Retorna los Efectos
		 * \return Referencia a los Efectos
		 */
		inline XEffects::EffectHandler* GetEffects(void)
		{
			return Effects;
		}

		/**
		 * \brief Termina los Efectos
		 */
		inline void Clear(void)
		{
			if( Effects )
			{
				Effects->removeAllShadowLights();
			}
		}

	};
};

#endif
