#ifndef ___Tornado__Context__H___
#define ___Tornado__Context__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Clase Contexto                                 *
 * Archivo Fuente: CContext.h                                         *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

//#include <pthread.h> 

#include "CEventReceiver.h"
#include "SGameDevices.h"
#include "Types.h"

namespace Tornado
{

	class CMachine;

	//! Clase Contexto
	class CContext
	{

	private:

		//! ID del Contexto (único)
		uint16 Id;

		//! Indicador si el Contexto esta activo
		bool Finished;

		//! Indicador si el Contexto ha sido inicializado
		bool Initialized;

		//! Indicador de si el Contexto tiene Tiempo de Carga
		bool HaveLoading;

		//! Indicador si el Tiempo de Carga del Contexto ha sido inicializado
		bool LoadingInitialized;

		//! Indicador si el Tiempo de Carga ha terminado
		bool LoadingFinished;

		//! Porcentaje de Carga del Loading
		uint16 LoadingPercent;

		//! ID del próximo Contexto
		uint16 NextContext;

		// CMachine puede acceder al contexto directamente
		friend class CMachine;

	protected:

		//! Ancho de la ventana
		irr::s32 Width;

		//! Alto de la ventana
		irr::s32 Height;

		//! Dispositivos de Juego
		SGameDevices *GameDevices;

		/**
		 * \brief Finaliza el Contexto y asigna el ID del siguiente
		 * \param Next ID del Siguiente Contexto
		 */
		inline void Finalize(uint16 Next,bool fullFinalize = false)
		{
			Finished = true;
			NextContext = Next;
			Initialized = !fullFinalize;
		}


		/**
		 * \brief Reinicia el Contexto
		 * \param fullRestart Indicador de si se hace un reinicio completo o sencillo
		 */
		inline void Restart(bool fullRestart = true)
		{
			Finished = true;
			NextContext = Id;
			Initialized = !fullRestart;
			LoadingInitialized = !fullRestart;
		}

	public:
		__TORNADO_DLL_EXPORT CContext(uint16 Id,bool HaveLoading = false);
		__TORNADO_DLL_EXPORT ~CContext();

		__TORNADO_DLL_EXPORT virtual bool Init(void);
		__TORNADO_DLL_EXPORT virtual void Prepare(void);
		__TORNADO_DLL_EXPORT virtual void Next(real Delta);
		__TORNADO_DLL_EXPORT virtual void Draw(void);
		__TORNADO_DLL_EXPORT virtual void End(void);

		__TORNADO_DLL_EXPORT virtual bool LoadingInit(void);
		__TORNADO_DLL_EXPORT virtual void LoadingPrepare(void);
		__TORNADO_DLL_EXPORT virtual void LoadingNext(real Delta);
		__TORNADO_DLL_EXPORT virtual void LoadingDraw(void);
		__TORNADO_DLL_EXPORT virtual void LoadingEnd(void);

		__TORNADO_DLL_EXPORT virtual void Close(void);

		void SetGlobalVariables(void);

		/**
		 * \brief Asigna los dispositivos de juego
		 * \param Devices Puntero a dispositivos de video
		 */
		inline void SetGameDevices(SGameDevices *Devices)
		{
			GameDevices = Devices;
		}

		/**
		 * \brief Retorna el ID del Contexto
		 * \return ID de contexto
		 */
		inline uint16 GetId(void)
		{
			return Id;
		}

		/**
		 * \brief Pregunta si el contexto ha finalizado o no
		 * \return TRUE si el contexto está finalizado, FALSE en caso contrario
		 */
		inline bool IsFinished(void)
		{
			return Finished;
		}

		/**
		 * \brief Pregunta si el contexto ha sido inicializado o no
		 * \return TRUE si el contexto está inicializado, FALSE en caso contrario
		 */
		inline bool IsInitialized(void)
		{
			return Initialized;
		}

		/**
		 * \brief Pregunta el ID del próximo contexto
		 * \return ID del próximo contexto
		 */
		inline uint16 GetNextContext(void)
		{
			return NextContext;
		}

		__TORNADO_DLL_EXPORT virtual bool OnGUIEvent(irr::gui::IGUIElement *Caller,irr::gui::IGUIElement *Element,const uint16 &EventType);
		//__TORNADO_DLL_EXPORT virtual bool OnJoystickEvent(const irr::SEvent::SJoystickEvent &Event);
		__TORNADO_DLL_EXPORT virtual bool OnKeyInput(const uint16 &Key,const wchar_t &Char,const bool isCtrl,const bool isShift,const bool isPressedDown);
		__TORNADO_DLL_EXPORT virtual bool OnMouseInput(const uint16 &EventType,const sint32 &X,const sint32 &Y,const real &Wheel,const bool isLeft,const bool isMiddle,const bool isRight,const bool isCtrl,const bool isShift);
		__TORNADO_DLL_EXPORT virtual bool OnUserEvent(const sint32 &UserData1,const sint32 &UserData2);
	};
};

#endif
