/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Codigo Fuente de Clase Maquina                             *
 * Archivo Fuente: CMachine.cpp                                       *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CMachine.h"
#include "CSceneManager.h"
#include "CGUIEnvironment.h"
#include "CAudioManager.h"
#include "CEffects.h"
#include "SThreadData.h"

namespace Tornado
{
	bool CMachine::ThreadIsActive = false;

	/**
	 * \brief Constructor de Clase
	 */
	CMachine::CMachine() : CEventReceiver(),
					GameDevices(NULL),
					ActiveContext(NULL),
					TitleContext(NULL),
					First(NULL),
					Last(NULL)/*,
					Contexts()*/
	{
	}

	/**
	 * \brief Destructor de Clase
	 */
	CMachine::~CMachine()
	{
		#if defined(_DEBUG)
		COutput::Wprintf(L"Destruyendo CMachine()\n");
		#endif
		
		GameDevices = NULL;
		ActiveContext = NULL;
		TitleContext = NULL;

		SContextElement *Active = First;

		while( First!=NULL )
		{
			Active = Active->Next;
			delete First;
			First = Active;
		}

		#if defined(_DEBUG)
		COutput::Wprintf(L"Limpiando Lista\n");
		#endif

		// Aqui esta el bug, porque los contextos ya han sido liberados de memoria
		//Contexts.clear();

		#if defined(_DEBUG)
		COutput::Wprintf(L"Lista limpia\n");
		#endif
	}

	/**
	 * \brief Inicializa la Máquina de Contextos
	 * \return TRUE si la Máquina de Contextos ha sido inicializada con éxito, FALSE en caso contrario.
	 */
	bool CMachine::Init(void)
	{
		if( !TitleContext )
		{
			TitleContext = new CTitleContext(0);
			COutput::Wprintf(L"No hay título\n");
		}

		ActiveContext = TitleContext;
		ActiveContext->SetGameDevices( GameDevices );
		ActiveContext->SetGlobalVariables();
		ActiveContext->Finished = false;

		if( !ActiveContext->Initialized )
		{
			ActiveContext->Initialized = ActiveContext->Init();
		}

		ActiveContext->Prepare();

		return true;
	}

	/**
	 * \brief Actualiza la máquina de contextos
	 * \return TRUE si la Máquina se ha actualizado con éxito, FALSE en caso contrario
	 */
	bool CMachine::Update(void)
	{
		uint16 id = 0;

		if( ActiveContext && ( id=ActiveContext->NextContext )!=0 )
		{
		
			// Cierro el contexto actual
			ActiveContext->End();

			// Cambiar al siguiente contexto
			if( SetNextContext(id) )
			{

				// Limpiar los elementos actuales
				if( GameDevices->SceneManager ) GameDevices->SceneManager->Clear();
				if( GameDevices->GUIEnvironment ) GameDevices->GUIEnvironment->Clear();
				if( GameDevices->AudioManager ) GameDevices->AudioManager->Clear();
				if( GameDevices->Effects ) GameDevices->Effects->Clear();

				// Asigno los dispositivos de juego
				ActiveContext->SetGameDevices( GameDevices );
				ActiveContext->SetGlobalVariables();
				ActiveContext->Finished = false;
				ActiveContext->LoadingFinished = false;

				#if defined(WIN32)
				if( ActiveContext->HaveLoading )
				{
					// Inicializo si es que no se ha hecho
					if( !ActiveContext->Initialized )
					{
						// Allocate memory for thread data.
						SThreadData *Data = (SThreadData*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(SThreadData));

						if( Data==NULL )
						{
							#if defined(_DEBUG)
							COutput::Wprintf(L"Heap allocation failure\n");
							#endif

							// If the array allocation fails, the system is out of memory
							// so there is no point in trying to print an error message.
							// Just terminate execution.
							ExitProcess(2);
						}

						Data->ActiveContext = ActiveContext;

						#if defined(_DEBUG)
						COutput::Wprintf(L"Creating thread\n");
						#endif

						// Creo la hebra donde se realizará el procesamiento Init()
						ThreadHandle = CreateThread( NULL , 0 , &CMachine::ThreadProc , Data , 0 , &ThreadId);
						
						// Check the return value for success.
						// If CreateThread fails, terminate execution. 
						// This will automatically clean up threads and memory. 
						if( ThreadHandle == NULL)
						{
							#if defined(_DEBUG)
							COutput::Wprintf(L"Threat creation error\n");
							#endif

							ExitProcess(3);
						}

						// Inicializo el Tiempo de Carga
						if( !ActiveContext->LoadingInitialized )
						{
							ActiveContext->LoadingInitialized = ActiveContext->LoadingInit();	
						}
					}

					// Preparo la escena de Tiempo de Carga
					ActiveContext->LoadingPrepare();
				}
				else 
				{
				#endif
					// Inicializo si es que no se ha hecho
					if( !ActiveContext->Initialized )
					{
						ActiveContext->Initialized = ActiveContext->Init();
					}
					// Preparo el siguiente contexto
					ActiveContext->Prepare();
				#if defined(WIN32)
				}
				#endif
				return true;
			}
		}
		return false;
	}

	/**
	 * \brief Llama a la función de dibujado del Contexto Actual
	 */
	void CMachine::Draw( void )
	{
		// Sólo ejecuto si el contexto está activo y no-finalizado
		if( ActiveContext && !ActiveContext->Finished )
		{
			ActiveContext->Draw();
		}
	}

	/**
	 * \brief Calcula el siguiente cuadro de la máquina de Contexto
	 * \param Delta Tiempo entre frame
	 * \return FALSE si la máquina ha terminado el contexto actual, TRUE en caso contrario
	 */
	bool CMachine::Next( real delta )
	{
		// Sólo ejecuto si el contexto está activo y no-finalizado
		if( ActiveContext && !ActiveContext->Finished )
		{
			ActiveContext->Next(delta);

			return true;
		}
		return false;
	}

	/**
	 * \brief Ejecuta la máquina de Contextos
	 * \param Delta Desfase de tiempo entre cuadros de dibujado
	 * \return FALSE si la máquina ha terminado el contexto actual, TRUE en caso contrario
	 */
	bool CMachine::Run( real delta )
	{
		// Sólo ejecuto si el contexto está activo y no-finalizado
		if( ActiveContext )
		{
			#if defined(WIN32)
			if( !ActiveContext->LoadingFinished && ActiveContext->HaveLoading )
			{
				DWORD ExitCode = 0;
				GetExitCodeThread( ThreadHandle , &ExitCode );

				//if( ExitCode == STILL_ACTIVE)
				if( ThreadIsActive )
				{
					ActiveContext->LoadingDraw();

					ActiveContext->LoadingNext( delta );
				}
				else
				{
					ActiveContext->LoadingFinished = true;

					ActiveContext->LoadingEnd();

					ActiveContext->Prepare();
				}
				return true;
			}
			#endif

			if( !ActiveContext->Finished )
			{
				ActiveContext->Draw();

				ActiveContext->Next( delta );
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}

	/**
	 * \brief Termina la ejecución de la máquina de contexto
	 */
	void CMachine::Close(void)
	{
		SContextElement *Active = First;

		while( Active != NULL )
		{
			Active->Context->Close();
			Active = Active->Next;
		}
	}

	#if defined(WIN32)
	DWORD WINAPI CMachine::ThreadProc( LPVOID threadParam )
	{
		#if defined(_DEBUG)
		COutput::Wprintf(L"Thread started\n");
		#endif

		ThreadIsActive = false;

		SThreadData *Data = (SThreadData*)threadParam;

		Data->ActiveContext->Initialized = Data->ActiveContext->Init();

		#if defined(_DEBUG)
		COutput::Wprintf(L"Thread finished\n");
		#endif

		ThreadIsActive = true;

		return 0;
	}
	#endif

	/**
	 * \brief Agrega un nuevo Contexto a la lista
	 * \param newContext Nuevo contexto a agregar
	 * \return TRUE si el contexto ha sido agregado, FALSE en caso contrario
	 */
	bool CMachine::AddContext(CContext *newContext)
	{
		if( newContext )
		{
			SContextElement *sContext = new SContextElement;

			sContext->Context = newContext;
			sContext->Id = newContext->GetId();
			sContext->Next = NULL;
			sContext->Back = Last;

			if( !First )
			{
				First = sContext;
			}
			if( Last )
			{
				Last->Next = sContext;
			}
			Last = sContext;

			//Contexts.push_back( sContext );
			return true;
		}
		return false;
	}

	/**
	 * \brief Asigna el puntero al siguiente Contexto
	 * \param tmp_id ID del siguiente Contexto
	 * \return TRUE si el contexto ha sido cambiado, FALSE en caso contrario
	 */
	bool CMachine::SetNextContext(uint16 nextContextId)
	{
		COutput::Wprintf(L"Cambio de Context\n");

		SContextElement *Active = First;

		while( Active != NULL && Active->Id != nextContextId )
		{
			//COutput::Wprintf(L"ID=%d\n",Active->Id);
			Active = Active->Next;
		}

		if( Active )
		{
			ActiveContext = Active->Context;
			return true;
		}

		return false;

		/*std::list<SContextElement *>::iterator it;

		for(it=Contexts.begin() ; it!=Contexts.end() ; it++)
		{
			if( (*it)->Id == tmp_id )
			{
				ActiveContext = (*it)->Context;
				return true;
			}
		}
		return false;*/
	}

	/**
	 * \brief Evento de GUI
	 * \param Event Evento
	 * \return TRUE
	 */
	inline bool CMachine::OnGUIEvent(const irr::SEvent::SGUIEvent &guiEvent)
	{
		if( ActiveContext )
		{
			return ActiveContext->OnGUIEvent(	guiEvent.Caller ,
												guiEvent.Element,
												guiEvent.EventType );
		}
		return false;
	}

	/**
	 * \brief Evento de Joystick
	 * \param Event Evento
	 * \return TRUE
	 */
	inline bool CMachine::OnJoystickEvent(const irr::SEvent::SJoystickEvent &joystickEvent)
	{
		return false;
	}

	/**
	 * \brief Evento de Teclado
	 * \param Event Evento
	 * \return TRUE
	 */
	inline bool CMachine::OnKeyInput(const irr::SEvent::SKeyInput &keyInputEvent)
	{
		if( ActiveContext )
		{
			return ActiveContext->OnKeyInput(	keyInputEvent.Key ,
												keyInputEvent.Char ,
												keyInputEvent.Control,
												keyInputEvent.Shift,
												keyInputEvent.PressedDown );
		}
		return false;
	}

	/**
	 * \brief Evento de Mouse
	 * \param Event Evento
	 * \return TRUE
	 */
	inline bool CMachine::OnMouseInput(const irr::SEvent::SMouseInput &mouseInputEvent)
	{
		if( ActiveContext )
		{
			return ActiveContext->OnMouseInput( mouseInputEvent.Event ,
												mouseInputEvent.X,
												mouseInputEvent.Y,
												mouseInputEvent.Wheel,
												mouseInputEvent.isLeftPressed(),
												mouseInputEvent.isMiddlePressed(),
												mouseInputEvent.isRightPressed(),
												mouseInputEvent.Control,
												mouseInputEvent.Shift );
		}
		return false;
	}

	/**
	 * \brief Evento de Usuario
	 * \param Event Evento
	 * \return TRUE
	 */
	inline bool CMachine::OnUserEvent(const irr::SEvent::SUserEvent &userEvent)
	{
		if( ActiveContext )
		{
			return ActiveContext->OnUserEvent(	userEvent.UserData1,
												userEvent.UserData2 );
		}
		return false;
	}
};
