/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Codigo Fuente de Clase Contexto de Splash                  *
 * Archivo Fuente: CSplashContext.cpp                                 *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CSplashContext.h"
#include "ESplashStatus.h"
#include "CVideo.h"
#include "CGUIEnvironment.h"
#include "CSceneManager.h"

namespace Tornado
{

	/**
	 * \brief Agrega una imágen a la lista de elementos
	 * \param tmp_Path Ruta de la imágen a crear
	 * \param tmp_AlphaChannel Indicador de si la imágen tiene canal alfa
	 * \param tmp_BgColor Color del Fondo
	 * \param tmp_FadeInColor Color del Desvanecimiento de Entrada
	 * \param tmp_FadeOutColor Color del Desvanecimiento de Salida
	 * \param tmp_AlignType Tipo de alineamiento de la imágen
	 * \param tmp_FadeTime Tiempo de desvanecimiento
	 * \param tmp_WaitTime Tiempo de espera
	 * \return TRUE si el elemento ha sido agregado exitosamente, FALSE en caso contrario
	 */
	bool CSplashContext::AddImageElement(	const wchar_t *imagePath,
											bool haveAlphaChannel,
											irr::video::SColor backgroundColor,
											irr::video::SColor fadeInColor,
											irr::video::SColor fadeOutColor,
											uint16 alignType,
											uint32 fadeTime,
											uint32 waitTime )
	{

		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();

		SSplashElement *Element = new SSplashElement;

		Element->AlphaChannel = haveAlphaChannel;
		Element->FadeTime = fadeTime;
		Element->WaitTime = waitTime;
		Element->BgColor = backgroundColor;
		Element->FadeInColor = fadeInColor;
		Element->FadeOutColor = fadeOutColor;

		if( (Element->Texture = driver->getTexture( imagePath ))==NULL )
		{
			return false;
		}
		if( haveAlphaChannel )
		{
			driver->makeColorKeyTexture( Element->Texture, irr::core::position2d<irr::s32>(0,0));
		}

		irr::core::dimension2d<irr::u32> size = Element->Texture->getOriginalSize();

		Element->Position = irr::core::position2d<irr::s32>( (Width - size.Width)/2 , (Height - size.Height)/2 );
		//Element->SourceRect = irr::core::rect<irr::s32>( 0 , 0 , size.Width , size.Height );

		#if defined(_DEBUG)
		COutput::Wprintf(L"ancho=%d alto=%d\n",size.Width,size.Height);
		COutput::Wprintf(L"posicion= (%d,%d)\n",Element->Position.X,Element->Position.Y);
		#endif

		switch( alignType )
		{

			default:
			case ESET_CENTERED:
			{
				Element->SourceRect = irr::core::rect<irr::s32>( 0 , 0 , size.Width , size.Height );
				Element->DestRect = irr::core::rect<irr::s32>( Element->Position.X , Element->Position.Y , Element->Position.X + size.Width , Element->Position.Y + size.Height );
				break;
			}

			/*case ESET_STRETCHED:
			{
				Element->SourceRect = irr::core::rect<irr::s32>( 0 , 0 , size.Width , size.Height );
				Element->DestRect = irr::core::rect<irr::s32>( 0 , 0 , Width , Height );
				break;
			}

			case ESET_VSCALED:
			{
				//real tX = (real)Height/(real)size.Height * (real)size.Width;
				real tY = (real)Width/(real)size.Width * (real)size.Height;
				real razonY = (tY - Height) / tY ;
				real diffY = size.Height * razonY * 0.5f;

				Element->SourceRect = irr::core::rect<irr::s32>( 0 , (irr::s32)diffY , size.Width , (irr::s32)( (real)size.Height - diffY) );
				Element->DestRect = irr::core::rect<irr::s32>( 0 , 0 , Width , Height );
				break;
			}

			case ESET_HSCALED:
			{
				real tX = (real)Height/(real)size.Height * (real)size.Width;
				//real tY = (real)Width/(real)size.Width * (real)size.Height;
				real razonX = (tX - Width) / tX ;
				real diffX = size.Width * razonX * 0.5f;

				Element->SourceRect = irr::core::rect<irr::s32>( (irr::s32)diffX , 0 , (irr::s32)( (real)size.Width - diffX) , size.Height );
				Element->DestRect = irr::core::rect<irr::s32>( 0 , 0 , Width , Height );
				break;
			}

			case ESET_PROPORTIONAL:
			{

				Element->SourceRect = irr::core::rect<irr::s32>( 0 , 0 , size.Width , size.Height );

				real tX = (real)Height/(real)size.Height * (real)size.Width;
				real tY = (real)Width/(real)size.Width * (real)size.Height;

				if( tY <= (real)Height )
				{
					Element->DestRect = irr::core::rect<irr::s32>( 0 , 0 , Width , (irr::s32)tY );
				}
				else
				{
					Element->DestRect = irr::core::rect<irr::s32>( 0 , 0 , (irr::s32)tX , Height );
				}
				break;
			}*/
		}

		Elements.push_back( Element );
		return true;
	}

	/**
	 * \brief Prepara los elementos para mostrarlos
	 */
	bool CSplashContext::BeginSplashAnimation(void)
	{

		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

		if( Elements.size()>0 )
		{

			ActualStatus = ESS_START;
			IndexActualElement = Elements.begin();

			Clock.Stop();
			//GameDevices->Video->SetVideoColor( irr::video::SColor(0xFF,0x00,0x00,0x00) );
			//wprintf(L"Fondo=%02x%02x%02x\n",(*IndexActualElement)->BgColor.getRed(),(*IndexActualElement)->BgColor.getGreen(),(*IndexActualElement)->BgColor.getBlue());

			/*SplashImage = env->addImage(	(*IndexActualElement)->Texture , 
											(*IndexActualElement)->Position ,
											(*IndexActualElement)->AlphaChannel );*/

			SplashFader = env->addInOutFader();
			SplashFader->setColor( (*IndexActualElement)->BgColor );
			SplashFader->fadeOut( 0 );
			return true;
		}
		return false;
	}

	/**
	 * \brief Constructor de Clase
	 * \param tmp_id ID de Contexto
	 * \param tmp_haveloading Indicador de si el Contexto tiene Tiempo de Carga
	 */
	CSplashContext::CSplashContext(	uint16 contextId,
									bool haveLoading ) :
										CContext( contextId , haveLoading ),
										Clock(),
										ActualStatus(0),
										Elements(),
										IndexActualElement()
	{
	}

	/**
	 * \brief Destructor de Clase
	 */
	CSplashContext::~CSplashContext()
	{
		#if defined(_DEBUG)
		COutput::Wprintf(L"Destruyendo CSplashContext(%d)\n",GetId());
		#endif
	}

	/**
	 * \brief Inicializa las variables del Contexto
	 */
	bool CSplashContext::Init(void)
	{

		return false;
	}

	/**
	 * \brief Muestra el primer cuadro
	 */
	void CSplashContext::Prepare(void)
	{

	}

	/**
	 * \brief Calcula el siguiente cuadro
	 */
	void CSplashContext::Next(real delta)
	{

		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

		Clock.Next(delta);

		switch( ActualStatus )
		{

			case ESS_START:
			{
				if( SplashFader->isReady() )
				{

					ActualStatus = ESS_FADEIN;
					GameDevices->Video->SetVideoColor( (*IndexActualElement)->BgColor );
					//wprintf(L"Fondo=%02x%02x%02x\n",(*IndexActualElement)->BgColor.getRed(),(*IndexActualElement)->BgColor.getGreen(),(*IndexActualElement)->BgColor.getBlue());
					//SplashImage->remove();

					SplashImage = env->addImage(	(*IndexActualElement)->Texture , 
													(*IndexActualElement)->Position ,
													(*IndexActualElement)->AlphaChannel );

					SplashFader = env->addInOutFader();
					SplashFader->setColor( (*IndexActualElement)->FadeInColor );
					SplashFader->fadeIn( (*IndexActualElement)->FadeTime );
				}
				break;
			}

			case ESS_WAITING:
			{
				if( Clock.WaitTimer() )
				{

					ActualStatus = ESS_FADEPREOUT;
					Clock.Stop();

					//GameDevices->Video->SetVideoColor( (*IndexActualElement)->BgColor );

					SplashFader = env->addInOutFader();
					SplashFader->setColor( (*IndexActualElement)->FadeOutColor );
					SplashFader->fadeOut( (*IndexActualElement)->FadeTime );
				}
				break;
			}

			case ESS_FADEIN:
			{
				if( SplashFader->isReady() )
				{

					ActualStatus = ESS_WAITING;
					Clock.Start();
					Clock.EnableTimer( ( (real)(*IndexActualElement)->WaitTime ) / 1000.0f );

					/*SplashFader = env->addInOutFader();
					SplashFader->setColor( (*IndexActualElement)->BgColor );
					SplashFader->fadeOut( 0 );*/
				}
				break;
			}

			case ESS_FADEOUT:
			{
				if( SplashFader->isReady() )
				{

					//IndexActualElement++;
					//if( IndexActualElement != Elements.end() )
					//{

						ActualStatus = ESS_FADEIN;
						//GameDevices->Video->SetVideoColor( (*IndexActualElement)->BgColor );
						//wprintf(L"Fondo=%02x%02x%02x\n",(*IndexActualElement)->BgColor.getRed(),(*IndexActualElement)->BgColor.getGreen(),(*IndexActualElement)->BgColor.getBlue());
						SplashImage->remove();

						SplashImage = env->addImage(	(*IndexActualElement)->Texture , 
														(*IndexActualElement)->Position ,
														(*IndexActualElement)->AlphaChannel );

						SplashFader = env->addInOutFader();
						SplashFader->setColor( (*IndexActualElement)->FadeInColor );
						SplashFader->fadeIn( (*IndexActualElement)->FadeTime );
					//}
					/*else {
						OnSplashFinishEvent();
					}*/
				}
				break;
			}

			case ESS_FADEPREOUT:
			{
				if( SplashFader->isReady() )
				{
					//GameDevices->Video->SetVideoColor( (*IndexActualElement)->BgColor );
					IndexActualElement++;
					if( IndexActualElement != Elements.end() )
					{

						ActualStatus = ESS_FADEOUT;
						SplashFader = env->addInOutFader();
						SplashFader->setColor( (*IndexActualElement)->BgColor );
						SplashFader->fadeOut( 0 );
					}
					else 
					{
						OnSplashFinishEvent();
					}
				}
				break;
			}

			default:{
				break;
			}
		}
	}

	/**
	 * \brief Dibuja los elementos del contexto
	 */
	void CSplashContext::Draw(void)
	{

		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();

		GameDevices->SceneManager->DrawScene( driver );
		GameDevices->GUIEnvironment->DrawGUI( driver );

		/*driver->enableMaterial2D();
		driver->draw2DImage(	(*IndexActualElement)->Image ,
								(*IndexActualElement)->DestRect ,
								(*IndexActualElement)->SourceRect );,
								0 ,
								&(*IndexActualElement)->BgColor ,
								false );
		driver->enableMaterial2D(false);*/

		/*driver->draw2DImage(	(*IndexActualElement)->Image ,
								(*IndexActualElement)->DestRect ,
								(*IndexActualElement)->SourceRect ,
								0 ,
								&(*IndexActualElement)->BgColor ,
								false );*/
	}

	/**
	 * \brief Termina el Contexto (se llama al terminar la aplicación)
	 */
	void CSplashContext::End(void)
	{
	}

	/**
	 * \brief Prepara la escena de Tiempo de Carga
	 */
	bool CSplashContext::LoadingInit(void)
	{
		return true;
	}

	/**
	 * \brief Prepara la escena de Tiempo de Carga
	 */
	void CSplashContext::LoadingPrepare(void)
	{
	}

	/**
	 * \brief Calcula el siguiente cuadro del Tiempo de Carga
	 */
	void CSplashContext::LoadingNext(real Delta)
	{
	}

	/**
	 * \brief Dibuja la escena de Tiempo de Carga
	 */
	void CSplashContext::LoadingDraw(void)
	{
	}

	/**
	 * \brief Se termina el Tiempo de Carga
	 */
	void CSplashContext::LoadingEnd(void)
	{
	}

	/**
	 * \brief Cierra el contexto (se llama al hacer cambio de contextos)
	 */
	void CSplashContext::Close(void)
	{
	}


	/**
	 * \brief Evento de finalización de animación splash
	 * \return FALSE
	 */
	bool CSplashContext::OnSplashFinishEvent(void)
	{

		return false;
	}

	/**
	 * \brief Evento de GUI
	 * \param tmp_Caller Elemento que llamó el evento
	 * \param tmp_Element Si el Evento tiene que ver con otro elemento, será este puntero
	 * \param tmp_EventType Tipo de Evento
	 * \return FALSE
	 */
	bool CSplashContext::OnGUIEvent(	irr::gui::IGUIElement *tmp_Caller,
										irr::gui::IGUIElement *tmp_Element,
										const uint16 &tmp_EventType )
	{
		return false;
	}

	/**
	 * \brief Evento de Teclado
	 * \param tmp_Key Tecla presionada
	 * \param tmp_Char Código de tecla presionada
	 * \param tmp_isCtrl Si se presionó la tecla Ctrl
	 * \param tmp_isShift Si se presionó la tecla Shift
	 * \param tmp_isPressedDown Si se presionó o se soltó la tecla
	 * \return TRUE
	 */
	bool CSplashContext::OnKeyInput(	const uint16 &tmp_Key,
										const wchar_t &tmp_Char,
										const bool tmp_isCtrl,
										const bool tmp_isShift,
										const bool tmp_isPressedDown )
	{
		return false;
	}

	/**
	 * \brief Evento de Mouse
	 * \param tmp_EventType Evento
	 * \param tmp_X Posición X del Cursor
	 * \param tmp_Y Posición Y del Cursor
	 * \param tmp_Wheel Movimiento de la rueda
	 * \param tmp_isLeft Si se presionó el botón izquierdo
	 * \param tmp_isMiddle Si se presionó el botón central
	 * \param tmp_isRight Si se presionó el botón derecho
	 * \param tmp_isCtrl Si se presionó la tecla Ctrl
	 * \param tmp_isShift Si se presionó la tecla Shift
	 * \return TRUE
	 */
	bool CSplashContext::OnMouseInput(	const uint16 &tmp_EventType,
										const sint32 &tmp_X,
										const sint32 &tmp_Y,
										const real &tmp_Wheel,
										const bool tmp_isLeft,
										const bool tmp_isMiddle,
										const bool tmp_isRight,
										const bool tmp_isCtrl,
										const bool tmp_isShift)
	{
		return false;
	}
};
