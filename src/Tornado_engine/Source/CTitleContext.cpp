/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Codigo Fuente de Clase Contexto de Título                  *
 * Archivo Fuente: CTitleContext.cpp                                  *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/


#include "CTitleContext.h"
#include "CConfig.h"
#include "CVideo.h"
#include "CSceneManager.h"
#include "CGUIEnvironment.h"
#include "COutput.h"
#include "CMath.h"

#include "SVideoMode.h"
#include "EGUITitleControl.h"


namespace Tornado
{

	/**
	 * \brief Muestra la ventana de opciones
	 */
	void CTitleContext::ShowOptionsWindow(void)
	{

		//irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
		//irr::gui::IGUISkin *skin = GameDevices->GUIEnvironment->GetGUISkin();
		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

		irr::gui::IGUIWindow* window = env->addWindow(
			irr::core::rect<irr::s32>(Width/2-150,Height/2-150,Width/2+150,Height/2+215),
			true, // modal?
			L"Opciones");

		// Pestañas
		irr::gui::IGUITabControl *tabs = env->addTabControl(
			irr::core::rect<irr::s32>(5,25,295,305),
			window,false,true
		);
		wchar_t *value;
		irr::gui::IGUITab* tabVideo = tabs->addTab(L"Video");
		irr::gui::IGUITab* tabAudio = tabs->addTab(L"Audio");
		irr::gui::IGUITab* tabAdvanced = tabs->addTab(L"Avanzado");

		// Volumen de Musica
		env->addStaticText(
			L"Volúmen de la Música",
			irr::core::rect<irr::s32>(10,10,200,25),
			false,false,tabAudio,-1,false
		);

		value = GameDevices->Config->GetConfigElement(L"audio",L"music");
		irr::gui::IGUIStaticText *music_txt = env->addStaticText(
			value,
			irr::core::rect<irr::s32>(210,30,250,50),
			false,false,tabAudio,-1,false
		);
		irr::gui::IGUIScrollBar *music = env->addScrollBar(
			true,
			irr::core::rect<irr::s32>(10,30,200,50),
			tabAudio
		);
		music->setID(EGTC_ID_OPTIONS_AUDIO_MUSIC);
		music->setMax(100);
		music->setMin(0);
		music->setPos( CMath::Wtoi(value) );




		// Volumen de Sonidos
		GameDevices->GUIEnvironment->GetGUIEnvironment()->addStaticText(
			L"Volúmen de los Sonidos",
			irr::core::rect<irr::s32>(10,60,200,75),
			false,false,tabAudio,-1,false
		);

		value = GameDevices->Config->GetConfigElement(L"audio",L"sound");
		irr::gui::IGUIStaticText *sound_txt = env->addStaticText(
			value ,
			irr::core::rect<irr::s32>(210,80,250,100),
			false,false,tabAudio,-1,false
		);
		irr::gui::IGUIScrollBar *sound = env->addScrollBar(
			true,
			irr::core::rect<irr::s32>(10,80,200,100),
			tabAudio
		);
		sound->setID(EGTC_ID_OPTIONS_AUDIO_SOUND);
		sound->setMax(100);
		sound->setMin(0);
		sound->setPos( CMath::Wtoi(value) );

		// Check Pantalla Completa
		irr::gui::IGUICheckBox *fullscreen = env->addCheckBox(
			false,
			irr::core::rect<irr::s32>(10,120,200,150),
			tabVideo,EGTC_ID_OPTIONS_VIDEO_FULLSCREEN,L"Full Screen"
		);
		fullscreen->setSubElement(false);
		value = GameDevices->Config->GetConfigElement(L"video",L"fs");
		!wcscmp(value,L"true") ? fullscreen->setChecked(true) : fullscreen->setChecked(false) ;

		// Check Antialiasing
		irr::gui::IGUICheckBox *antialiasing = env->addCheckBox(
			false,
			irr::core::rect<irr::s32>(10,150,200,180),
			tabVideo,EGTC_ID_OPTIONS_VIDEO_ANTIALIASING,L"Antialiasing"
		);
		value = GameDevices->Config->GetConfigElement(L"video",L"aa");
		!wcscmp(value,L"true") ? antialiasing->setChecked(true) : antialiasing->setChecked(false) ;

		// Check Vertical Sync
		irr::gui::IGUICheckBox *verticalsync = env->addCheckBox(
			false,
			irr::core::rect<irr::s32>(10,180,200,210),
			tabVideo,EGTC_ID_OPTIONS_VIDEO_VERTICALSYNC,L"Vertical Sync"
		);
		value = GameDevices->Config->GetConfigElement(L"video",L"vsync");
		!wcscmp(value,L"true") ? verticalsync->setChecked(true) : verticalsync->setChecked(false) ;


		// Check Stencil-Shadow
		/*irr::gui::IGUICheckBox *stencilshadow = env->addCheckBox(
			false,
			irr::core::rect<irr::s32>(10,180,200,210),
			tabAdvanced,EGTC_ID_OPTIONS_VIDEO_STENCILSHADOW,L"Stencil Shadow"
		);
		value = GameDevices->Config->GetConfigElement(L"video",L"stencil");
		!wcscmp(value,L"true") ? stencilshadow->setChecked(true) : stencilshadow->setChecked(false) ;*/

		// Check AnaglyphMode
		/*irr::gui::IGUICheckBox *anaglyphmode = env->addCheckBox(
			false,
			irr::core::rect<irr::s32>(10,210,200,240),
			tabAdvanced,EGTC_ID_OPTIONS_VIDEO_ANAGLYPHMODE,L"Anaglyph Mode"
		);
		value = GameDevices->Config->GetConfigElement(L"video",L"anaglyph");
		!wcscmp(value,L"true") ? anaglyphmode->setChecked(true) : anaglyphmode->setChecked(false) ;*/


		// Menu Resolution de ShadowMap
		env->addStaticText(
			L"ShadowMap Resolution",
			irr::core::rect<irr::s32>(10,10,200,25),
			false,false,tabAdvanced,-1,false
		);
		irr::gui::IGUIComboBox *shadowmapresolution = env->addComboBox(
			irr::core::rect<irr::s32>(10,30,200,50),
			tabAdvanced
		);
		shadowmapresolution->addItem(L"512",1);
		shadowmapresolution->addItem(L"1024",2);
		shadowmapresolution->addItem(L"2048",3);
		shadowmapresolution->addItem(L"4096",4);
		/*value = GameDevices->Config->GetConfigElement(L"shaders",L"res");
		shadowmapresolution->setSelected( CMath::Wtoi(value)-1 );*/

		// Menu Filtro de ShadowMap
		env->addStaticText(
			L"ShadowMap Filtering",
			irr::core::rect<irr::s32>(10,60,200,75),
			false,false,tabAdvanced,-1,false
		);
		irr::gui::IGUIComboBox *shadowmapfiltering = env->addComboBox(
			irr::core::rect<irr::s32>(10,80,200,100),
			tabAdvanced
		);
		shadowmapfiltering->addItem(L"none",0);
		shadowmapfiltering->addItem(L"4 PCF",1);
		shadowmapfiltering->addItem(L"8 PCF",2);
		shadowmapfiltering->addItem(L"12 PCF",3);
		shadowmapfiltering->addItem(L"16 PCF",4);



		// Botón Aceptar
		irr::gui::IGUIButton *accept = env->addButton(
			irr::core::rect<irr::s32>(10,325,100,355),
			window,-1,L"Aceptar"
		);
		accept->setID( EGTC_ID_OPTIONS_ACCEPT );

		// Botón Cancelar
		irr::gui::IGUIButton *cancel = env->addButton(
			irr::core::rect<irr::s32>(110,325,200,355),
			window,-1,L"Cancelar"
		);
		cancel->setID( EGTC_ID_OPTIONS_CANCEL );

		// Menu Dispositivo de Video
		env->addStaticText(
			L"Video Device",
			irr::core::rect<irr::s32>(10,10,200,25),
			false,false,tabVideo,-1,false
		);
		irr::gui::IGUIComboBox *driver = env->addComboBox(
			irr::core::rect<irr::s32>(10,30,200,50),
			tabVideo
		);
		#if defined(WIN32)
		driver->addItem(L"Direct3D 9.0c",1);
		driver->addItem(L"Direct3D 8.1",2);
		driver->addItem(L"OpenGL 1.5",3);
		//driver->addItem(L"Software Renderer",4);
		#else
		driver->addItem(L"OpenGL 1.5",1);
		//driver->addItem(L"Software Renderer",4);
		#endif
		value = GameDevices->Config->GetConfigElement(L"video",L"driver");
		driver->setSelected( CMath::Wtoi(value)-1 );

		// Menu Resolucion
		env->addStaticText(
			L"Resolution",
			irr::core::rect<irr::s32>(10,60,200,75),
			false,false,tabVideo,-1,false
		);
		irr::gui::IGUIComboBox *resolution = env->addComboBox(
			irr::core::rect<irr::s32>(10,80,200,100),
			tabVideo
		);

		std::list<SVideoMode* > *Modes = GameDevices->Video->GetVideoModes();
		value = GameDevices->Config->GetConfigElement(L"video",L"bpp");
		uint32 bits = CMath::Wtoi(value);

		value = GameDevices->Config->GetConfigElement(L"video",L"width");
		uint32 width = CMath::Wtoi(value);

		value = GameDevices->Config->GetConfigElement(L"video",L"height");
		uint32 height = CMath::Wtoi(value);

		uint32 id=0,i=0;
		for(std::list<SVideoMode* >::iterator it = Modes->begin() ; it!=Modes->end() ; it++,i++){
			wchar_t res[512];
			COutput::Wsprintf(res,L"%dx%d %dbits",(*it)->width,(*it)->height,(*it)->bpp);
			resolution->addItem( res , (*it)->id );
			if( bits==(*it)->bpp && width==(*it)->width && height==(*it)->height ){
				id = i;
			}
		}
		resolution->setSelected(id);

		GUITitleElements.OptionsWindow = window;
		GUITitleElements.AntialiasingCheckBox = antialiasing;
		GUITitleElements.FullscreenCheckBox = fullscreen;
		GUITitleElements.VerticalSyncCheckBox = verticalsync;
		//GUITitleElements.StencilShadowCheckBox = stencilshadow;
		//GUITitleElements.AnaglyphModeCheckBox = anaglyphmode;
		GUITitleElements.MusicScrollBar = music;
		GUITitleElements.SoundScrollBar = sound;
		GUITitleElements.MusicStaticText = music_txt;
		GUITitleElements.SoundStaticText = sound_txt;
		GUITitleElements.DriverComboBox = driver;
		GUITitleElements.ShadowMapResolutionComboBox = shadowmapresolution;
		GUITitleElements.ShadowMapFilteringComboBox = shadowmapfiltering;
		GUITitleElements.ResolutionComboBox = resolution;
	}

	/**
	 * \brief Crea una GUI por defecto con botones
	 */
	void CTitleContext::PrepareDefaultGUI(void)
	{

		GameDevices->Video->SetCursorVisibility(true);
		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
		irr::gui::IGUISkin *skin = GameDevices->GUIEnvironment->GetGUISkin();
		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

		/*irr::core::rect<irr::s32> viewport = driver->getViewPort();

		Width = viewport.getWidth();
		Height = viewport.getHeight();*/

		skin->setFont( env->getBuiltInFont(), irr::gui::EGDF_WINDOW  );

		irr::gui::IGUIFont* font = env->getFont(L"media/fontlucida.png");
		if (font)
		{
			skin->setFont(font);
		}

		//wchar_t title[512];
		//COutput::Wsprintf(title,L"%ls® 2011",TITLE_TEAM);

		//irr::gui::IGUIStaticText *text = env->addStaticText( title ,
		//	irr::core::rect<irr::s32>( Width-200,Height-20,Width,Height),false,false);

		//text->setOverrideColor(irr::video::SColor(0x66,0xFF,0xFF,0xFF));

		//skin->setFont( env->getBuiltInFont(), irr::gui::EGDF_WINDOW  );

		irr::s32 y1 = (Height/2-190)/2+Height/2;
		irr::s32 x1 = (Width/2-250)/2;
		irr::s32 x2 = (Width/2+250)/2;

		if( !NewGameElement.Active )
		{
			env->addButton( irr::core::rect<irr::s32>(
					x1 , y1 , x2 , y1+40 ),
					0, EGTC_ID_NEW_GAME,
					L"Nuevo Juego", L"Comenzar un juego nuevo");
		}

		if( !LoadGameElement.Active )
		{
			env->addButton( irr::core::rect<irr::s32>(
					x1 , y1+50 , x2 , y1+90 ),
					0, EGTC_ID_LOAD_GAME,
					L"Cargar Partida", L"Cargar una partida salvada");
		}

		if( !OptionsElement.Active )
		{
			env->addButton( irr::core::rect<irr::s32>(
					x1 , y1+100 , x2 , y1+140 ),
					0, EGTC_ID_OPTIONS,
					L"Opciones", L"Cambiar opciones del juego");
		}

		if( !QuitGameElement.Active )
		{
			env->addButton( irr::core::rect<irr::s32>(
					x1 , y1+150 , x2 , y1+190 ),
					0, EGTC_ID_QUIT,
					L"Salir", L"Salir del Juego");
		}
	}

	/**
	 * \brief Crea una imágen para usarla de botón en el título
	 * \param Position Posición donde se colocará la imágen
	 * \param Image Imágen del botón
	 * \param Hover Imágen para el estado hover
	 * \param Pressed Imágen para el estado pressed
	 * \return TRUE si la imágen ha sido creada con éxito, FALSE en caso contrario
	 */
	bool CTitleContext::CreateNewGameImageElement(	irr::core::vector2di imagePosition,
													const wchar_t *defaultImagePath,
													const wchar_t *hoverImagePath,
													const wchar_t *pressedImagePath )
	{
		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

		NewGameElement.Active = true;
		//NewGameElement.Type = Element;
		NewGameElement.Image = env->addImage(driver->getTexture( defaultImagePath ) , imagePosition );
		NewGameElement.Image->setID( EGTC_ID_NEW_GAME );
		if( hoverImagePath )
		{
			NewGameElement.Hover = env->addImage(driver->getTexture( hoverImagePath ) , imagePosition );
			NewGameElement.Hover->setID( EGTC_ID_NEW_GAME );
			NewGameElement.Hover->setVisible(false);
		}
		if( pressedImagePath )
		{
			NewGameElement.Pressed = env->addImage(driver->getTexture( pressedImagePath ) , imagePosition );
			NewGameElement.Pressed->setID( EGTC_ID_NEW_GAME );
			NewGameElement.Pressed->setVisible(false);
		}
		return false;
	}

	/**
	 * \brief Crea una imágen para usarla de botón en el título
	 * \param Position Posición donde se colocará la imágen
	 * \param Image Imágen del botón
	 * \param Hover Imágen para el estado hover
	 * \param Pressed Imágen para el estado pressed
	 * \return TRUE si la imágen ha sido creada con éxito, FALSE en caso contrario
	 */
	bool CTitleContext::CreateLoadGameImageElement(	irr::core::vector2di imagePosition,
													const wchar_t *defaultImagePath,
													const wchar_t *hoverImagePath,
													const wchar_t *pressedImagePath )
	{
		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

		LoadGameElement.Active = true;
		//LoadGameElement.Type = Element;
		LoadGameElement.Image = env->addImage(driver->getTexture( defaultImagePath ) , imagePosition );
		LoadGameElement.Image->setID( EGTC_ID_LOAD_GAME );
		if( hoverImagePath )
		{
			LoadGameElement.Hover = env->addImage(driver->getTexture( hoverImagePath ) , imagePosition );
			LoadGameElement.Hover->setID( EGTC_ID_LOAD_GAME );
			LoadGameElement.Hover->setVisible(false);
		}
		if( pressedImagePath )
		{
			LoadGameElement.Pressed = env->addImage(driver->getTexture( pressedImagePath ) , imagePosition );
			LoadGameElement.Pressed->setID( EGTC_ID_LOAD_GAME );
			LoadGameElement.Pressed->setVisible(false);
		}
		return false;
	}

	/**
	 * \brief Crea una imágen para usarla de botón en el título
	 * \param Position Posición donde se colocará la imágen
	 * \param Image Imágen del botón
	 * \param Hover Imágen para el estado hover
	 * \param Pressed Imágen para el estado pressed
	 * \return TRUE si la imágen ha sido creada con éxito, FALSE en caso contrario
	 */
	bool CTitleContext::CreateOptionsImageElement(	irr::core::vector2di imagePosition,
													const wchar_t *defaultImagePath,
													const wchar_t *hoverImagePath,
													const wchar_t *pressedImagePath )
	{
		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

		OptionsElement.Active = true;
		//OptionsElement.Type = Element;
		OptionsElement.Image = env->addImage(driver->getTexture( defaultImagePath ) , imagePosition );
		OptionsElement.Image->setID( EGTC_ID_OPTIONS );
		if( hoverImagePath )
		{
			OptionsElement.Hover = env->addImage(driver->getTexture( hoverImagePath ) , imagePosition );
			OptionsElement.Hover->setID( EGTC_ID_OPTIONS );
			OptionsElement.Hover->setVisible(false);
		}
		if( pressedImagePath )
		{
			OptionsElement.Pressed = env->addImage(driver->getTexture( pressedImagePath ) , imagePosition );
			OptionsElement.Pressed->setID( EGTC_ID_OPTIONS );
			OptionsElement.Pressed->setVisible(false);
		}
		return false;
	}

	/**
	 * \brief Crea una imágen para usarla de botón en el título
	 * \param Position Posición donde se colocará la imágen
	 * \param Image Imágen del botón
	 * \param Hover Imágen para el estado hover
	 * \param Pressed Imágen para el estado pressed
	 * \return TRUE si la imágen ha sido creada con éxito, FALSE en caso contrario
	 */
	bool CTitleContext::CreateQuitGameImageElement(	irr::core::vector2di imagePosition,
													const wchar_t *defaultImagePath,
													const wchar_t *hoverImagePath,
													const wchar_t *pressedImagePath )
	{
		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

		QuitGameElement.Active = true;
		//QuitGameElement.Type = Element;
		QuitGameElement.Image = env->addImage(driver->getTexture( defaultImagePath ) , imagePosition );
		QuitGameElement.Image->setID( EGTC_ID_QUIT );
		if( hoverImagePath )
		{
			QuitGameElement.Hover = env->addImage(driver->getTexture( hoverImagePath ) , imagePosition );
			QuitGameElement.Hover->setID( EGTC_ID_QUIT );
			QuitGameElement.Hover->setVisible(false);
		}
		if( pressedImagePath )
		{
			QuitGameElement.Pressed = env->addImage(driver->getTexture( pressedImagePath ) , imagePosition );
			QuitGameElement.Pressed->setID( EGTC_ID_QUIT );
			QuitGameElement.Pressed->setVisible(false);
		}
		return false;
	}

	/**
	 * \brief Crea una imágen para usarla de botón en el título
	 * \param Element Elemento a crear
	 * \param Position Posición donde se colocará la imágen
	 * \param Image Imágen del botón
	 * \param Hover Imágen para el estado hover
	 * \param Pressed Imágen para el estado pressed
	 * \return TRUE si la imágen ha sido creada con éxito, FALSE en caso contrario
	 */
	bool CTitleContext::CreateCustomImageElement(	uint16 elementId,
													irr::core::vector2di imagePosition,
													const wchar_t *defaultImagePath,
													const wchar_t *hoverImagePath,
													const wchar_t *pressedImagePath )
	{
		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

		STitleElement *sElement = new STitleElement;

		sElement->Active = true;
		sElement->Type = elementId;
		sElement->Image = env->addImage(driver->getTexture( defaultImagePath ) , imagePosition );
		sElement->Image->setID( EGTC_ID_CUSTOM );
		if( hoverImagePath )
		{
			sElement->Hover = env->addImage(driver->getTexture( hoverImagePath ) , imagePosition );
			sElement->Hover->setID( EGTC_ID_CUSTOM );
			sElement->Hover->setVisible(false);
		}
		if( pressedImagePath )
		{
			sElement->Pressed = env->addImage(driver->getTexture( pressedImagePath ) , imagePosition );
			sElement->Pressed->setID( EGTC_ID_CUSTOM );
			sElement->Pressed->setVisible(false);
		}
		CustomTitleElements.push_back( sElement );
		return false;
	}





	/**
	 * \brief Crea una imágen para usarla de botón en el título
	 * \param Position Posición donde se colocará la imágen
	 * \param Image Imágen del botón
	 * \param Hover Imágen para el estado hover
	 * \param Pressed Imágen para el estado pressed
	 * \return TRUE si la imágen ha sido creada con éxito, FALSE en caso contrario
	 */
	bool CTitleContext::CreateNewGameImageElement(	irr::core::vector2di imagePosition,
													irr::video::ITexture *defaultImageTexture,
													irr::video::ITexture *hoverImageTexture,
													irr::video::ITexture *pressedImageTexture )
	{
		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

		NewGameElement.Active = true;
		//NewGameElement.Type = Element;
		NewGameElement.Image = env->addImage( defaultImageTexture , imagePosition );
		NewGameElement.Image->setID( EGTC_ID_NEW_GAME ); 
		if( hoverImageTexture )
		{
			NewGameElement.Hover = env->addImage( hoverImageTexture , imagePosition );
			NewGameElement.Hover->setID( EGTC_ID_NEW_GAME );
			NewGameElement.Hover->setVisible(false);
		}
		if( pressedImageTexture )
		{
			NewGameElement.Pressed = env->addImage( pressedImageTexture , imagePosition );
			NewGameElement.Pressed->setID( EGTC_ID_NEW_GAME );
			NewGameElement.Pressed->setVisible(false);
		}
		return false;
	}

	/**
	 * \brief Crea una imágen para usarla de botón en el título
	 * \param Position Posición donde se colocará la imágen
	 * \param Image Imágen del botón
	 * \param Hover Imágen para el estado hover
	 * \param Pressed Imágen para el estado pressed
	 * \return TRUE si la imágen ha sido creada con éxito, FALSE en caso contrario
	 */
	bool CTitleContext::CreateLoadGameImageElement(	irr::core::vector2di imagePosition,
													irr::video::ITexture *defaultImageTexture,
													irr::video::ITexture *hoverImageTexture,
													irr::video::ITexture *pressedImageTexture )
	{
		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

		LoadGameElement.Active = true;
		//LoadGameElement.Type = Element;
		LoadGameElement.Image = env->addImage( defaultImageTexture , imagePosition );
		LoadGameElement.Image->setID( EGTC_ID_LOAD_GAME );
		if( hoverImageTexture )
		{
			LoadGameElement.Hover = env->addImage( hoverImageTexture , imagePosition );
			LoadGameElement.Hover->setID( EGTC_ID_LOAD_GAME );
			LoadGameElement.Hover->setVisible(false);
		}
		if( pressedImageTexture )
		{
			LoadGameElement.Pressed = env->addImage( pressedImageTexture , imagePosition );
			LoadGameElement.Pressed->setID( EGTC_ID_LOAD_GAME );
			LoadGameElement.Pressed->setVisible(false);
		}
		return false;
	}

	/**
	 * \brief Crea una imágen para usarla de botón en el título
	 * \param Position Posición donde se colocará la imágen
	 * \param Image Imágen del botón
	 * \param Hover Imágen para el estado hover
	 * \param Pressed Imágen para el estado pressed
	 * \return TRUE si la imágen ha sido creada con éxito, FALSE en caso contrario
	 */
	bool CTitleContext::CreateOptionsImageElement(	irr::core::vector2di imagePosition,
													irr::video::ITexture *defaultImageTexture,
													irr::video::ITexture *hoverImageTexture,
													irr::video::ITexture *pressedImageTexture )
	{
		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

		OptionsElement.Active = true;
		//OptionsElement.Type = Element;
		OptionsElement.Image = env->addImage( defaultImageTexture , imagePosition );
		OptionsElement.Image->setID( EGTC_ID_OPTIONS );
		if( hoverImageTexture )
		{
			OptionsElement.Hover = env->addImage( hoverImageTexture , imagePosition );
			OptionsElement.Hover->setID( EGTC_ID_OPTIONS );
			OptionsElement.Hover->setVisible(false);
		}
		if( pressedImageTexture )
		{
			OptionsElement.Pressed = env->addImage( pressedImageTexture , imagePosition );
			OptionsElement.Pressed->setID( EGTC_ID_OPTIONS );
			OptionsElement.Pressed->setVisible(false);
		}
		return false;
	}

	/**
	 * \brief Crea una imágen para usarla de botón en el título
	 * \param Position Posición donde se colocará la imágen
	 * \param Image Imágen del botón
	 * \param Hover Imágen para el estado hover
	 * \param Pressed Imágen para el estado pressed
	 * \return TRUE si la imágen ha sido creada con éxito, FALSE en caso contrario
	 */
	bool CTitleContext::CreateQuitGameImageElement(	irr::core::vector2di imagePosition,
													irr::video::ITexture *defaultImageTexture,
													irr::video::ITexture *hoverImageTexture,
													irr::video::ITexture *pressedImageTexture )
	{
		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

		QuitGameElement.Active = true;
		//QuitGameElement.Type = Element;
		QuitGameElement.Image = env->addImage( defaultImageTexture , imagePosition );
		QuitGameElement.Image->setID( EGTC_ID_QUIT );
		if( hoverImageTexture )
		{
			QuitGameElement.Hover = env->addImage( hoverImageTexture , imagePosition );
			QuitGameElement.Hover->setID( EGTC_ID_QUIT );
			QuitGameElement.Hover->setVisible(false);
		}
		if( pressedImageTexture )
		{
			QuitGameElement.Pressed = env->addImage( pressedImageTexture , imagePosition );
			QuitGameElement.Pressed->setID( EGTC_ID_QUIT );
			QuitGameElement.Pressed->setVisible(false);
		}
		return false;
	}

	/**
	 * \brief Crea una imágen para usarla de botón en el título
	 * \param Element Elemento a crear
	 * \param Position Posición donde se colocará la imágen
	 * \param Image Imágen del botón
	 * \param Hover Imágen para el estado hover
	 * \param Pressed Imágen para el estado pressed
	 * \return TRUE si la imágen ha sido creada con éxito, FALSE en caso contrario
	 */
	bool CTitleContext::CreateCustomImageElement(	uint16 elementId,
													irr::core::vector2di imagePosition,
													irr::video::ITexture *defaultImageTexture,
													irr::video::ITexture *hoverImageTexture,
													irr::video::ITexture *pressedImageTexture )
	{
		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

		STitleElement *sElement = new STitleElement;

		sElement->Active = true;
		sElement->Type = elementId;
		sElement->Image = env->addImage( defaultImageTexture , imagePosition );
		sElement->Image->setID( EGTC_ID_CUSTOM );
		if( hoverImageTexture )
		{
			sElement->Hover = env->addImage( hoverImageTexture , imagePosition );
			sElement->Hover->setID( EGTC_ID_CUSTOM );
			sElement->Hover->setVisible(false);
		}
		if( pressedImageTexture )
		{
			sElement->Pressed = env->addImage( pressedImageTexture , imagePosition );
			sElement->Pressed->setID( EGTC_ID_CUSTOM );
			sElement->Pressed->setVisible(false);
		}
		CustomTitleElements.push_back( sElement );
		return false;
	}

	void CTitleContext::SetGuiVisibility( bool visibility )
	{
		
	}

	/**
	 * \brief Constructor de Clase
	 * \param tmp_id ID de Contexto
	 * \param tmp_haveloading Indicador de si el Contexto tiene Tiempo de Carga
	 */
	CTitleContext::CTitleContext(	uint16 contextId,
									bool haveLoading ) :
										CContext(contextId,haveLoading),
										GUITitleElements(),
										NewGameElement(),
										LoadGameElement(),
										OptionsElement(),
										QuitGameElement(),
										CustomTitleElements()
	{
	}

	/**
	 * \brief Destructor de Clase
	 */
	CTitleContext::~CTitleContext()
	{
		#if defined(_DEBUG)
		COutput::Wprintf(L"Destruyendo CTitleContext(%d)\n",GetId());
		#endif
	}

	/**
	 * \brief Inicializa las variables del Contexto
	 */
	bool CTitleContext::Init(void)
	{
		return false;
	}

	/**
	 * \brief Prepara la GUI de Inicio
	 */
	void CTitleContext::Prepare(void)
	{
		PrepareDefaultGUI();
	}

	/**
	 * \brief Calcula el siguiente cuadro
	 */
	void CTitleContext::Next(real delta)
	{
	}

	/**
	 * \brief Dibuja la GUI
	 */
	void CTitleContext::Draw(void)
	{

		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;

		GameDevices->SceneManager->DrawScene( driver );
		GameDevices->GUIEnvironment->DrawGUI( driver );

	}

	/**
	 * \brief Termina el Contexto (se llama durante el cambio de Contexto)
	 */
	void CTitleContext::End(void)
	{
	}

	/**
	 * \brief Prepara la escena de Tiempo de Carga
	 */
	bool CTitleContext::LoadingInit(void)
	{
		return true;
	}

	/**
	 * \brief Prepara la escena de Tiempo de Carga
	 */
	void CTitleContext::LoadingPrepare(void)
	{
	}

	/**
	 * \brief Calcula el siguiente cuadro del Tiempo de Carga
	 */
	void CTitleContext::LoadingNext(real delta)
	{
	}

	/**
	 * \brief Dibuja la escena de Tiempo de Carga
	 */
	void CTitleContext::LoadingDraw(void)
	{
	}

	/**
	 * \brief Se termina el Tiempo de Carga
	 */
	void CTitleContext::LoadingEnd(void)
	{
	}

	/**
	 * \brief Cierra el contexto (cuando se termina el programa)
	 */
	void CTitleContext::Close(void)
	{
	}

	/**
	 * \brief Evento de Colocar Mouse sobre un elemento
	 */
	bool CTitleContext::OnHoverElement(void)
	{
		return false;
	}

	/**
	 * \brief Evento de Hacer clic sobre algun elemento
	 */
	bool CTitleContext::OnPressedElement(void)
	{
		return false;
	}

	/**
	 * \brief Evento Personalizado de GUI
	 * \param Caller Elemento que llamó el evento
	 * \param Element Si el Evento tiene que ver con otro elemento, será este puntero
	 * \param EventType Tipo de Evento
	 * \return FALSE
	 */
	bool CTitleContext::OnGUICustomEvent(	irr::gui::IGUIElement *caller,
											irr::gui::IGUIElement *element,
											const uint16 &eventType )
	{
		return false;
	}

	/**
	 * \brief Evento Nuevo Juego
	 * \return FALSE
	 */
	bool CTitleContext::OnNewGameEvent(void)
	{
		Finalize(-1);
		return false;
	}

	/**
	 * \brief Evento Cargar Juego
	 * \return FALSE
	 */
	bool CTitleContext::OnLoadGameEvent(void)
	{
		Finalize(-1);
		return false;
	}

	/**
	 * \brief Evento Salir Juego
	 * \return FALSE
	 */
	bool CTitleContext::OnQuitGameEvent(void)
	{
		Finalize(-1);
		return false;
	}

	/**
	 * \brief Evento de GUI
	 * \param Caller Elemento que llamó el evento
	 * \param Element Si el Evento tiene que ver con otro elemento, será este puntero
	 * \param EventType Tipo de Evento
	 * \return FALSE
	 */
	bool CTitleContext::OnGUIEvent(	irr::gui::IGUIElement *caller,
									irr::gui::IGUIElement *element,
									const uint16 &eventType )
	{

		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();

		// Presionar un Boton de la GUI
		switch(eventType)
		{

			default:
			{
				return OnGUICustomEvent( caller , element , eventType );
				break;
			}

			// Mouse sobre un elemento
			case irr::gui::EGET_ELEMENT_HOVERED:
			{
				irr::s32 id = caller->getID();

				switch(id)
				{

					default:
					{
						return OnGUICustomEvent( caller , element , eventType );
						break;
					}

					case EGTC_ID_NEW_GAME:
					{
						if( NewGameElement.Active )
						{
							//COutput::Wprintf(L"EGET_ELEMENT_HOVERED [new game]\n");
							NewGameElement.Image->setVisible(false);
							if( NewGameElement.Hover )
							{
								NewGameElement.Hover->setVisible(true);
							}
							if( NewGameElement.Pressed )
							{
								NewGameElement.Pressed->setVisible(false);
							}
							OnHoverElement();
						}
						break;
					}

					case EGTC_ID_LOAD_GAME:
					{
						if( LoadGameElement.Active )
						{
							//COutput::Wprintf(L"EGET_ELEMENT_HOVERED [load game]\n");
							LoadGameElement.Image->setVisible(false);
							if( LoadGameElement.Hover )
							{
								LoadGameElement.Hover->setVisible(true);
							}
							if( LoadGameElement.Pressed )
							{
								LoadGameElement.Pressed->setVisible(false);
							}
							OnHoverElement();
						}
						break;
					}

					case EGTC_ID_OPTIONS:
					{
						if( OptionsElement.Active )
						{
							//COutput::Wprintf(L"EGET_ELEMENT_HOVERED [options]\n");
							OptionsElement.Image->setVisible(false);
							if( OptionsElement.Hover )
							{
								OptionsElement.Hover->setVisible(true);
							}
							if( OptionsElement.Pressed )
							{
								OptionsElement.Pressed->setVisible(false);
							}
							OnHoverElement();
						}
						break;
					}

					case EGTC_ID_QUIT:
					{
						if( QuitGameElement.Active )
						{
							//COutput::Wprintf(L"EGET_ELEMENT_HOVERED [quit]\n");
							QuitGameElement.Image->setVisible(false);
							if( QuitGameElement.Hover )
							{
								QuitGameElement.Hover->setVisible(true);
							}
							if( QuitGameElement.Pressed )
							{
								QuitGameElement.Pressed->setVisible(false);
							}
							OnHoverElement();
						}
						break;
					}
				}
				break;
			}
					
			// Fuera de un elemento
			case irr::gui::EGET_ELEMENT_LEFT:
			{
				irr::s32 id = caller->getID();

				switch(id)
				{

					default:
					{
						return OnGUICustomEvent( caller , element , eventType );
						break;
					}

					case EGTC_ID_NEW_GAME:
					{
						if( NewGameElement.Active )
						{
							//COutput::Wprintf(L"EGET_ELEMENT_LEFT [new game]\n");
							NewGameElement.Image->setVisible(true);
							if( NewGameElement.Hover )
							{
								NewGameElement.Hover->setVisible(false);
							}
							if( NewGameElement.Pressed )
							{
								NewGameElement.Pressed->setVisible(false);
							}
						}
						break;
					}

					case EGTC_ID_LOAD_GAME:
					{
						if( LoadGameElement.Active )
						{
							//COutput::Wprintf(L"EGET_ELEMENT_LEFT [load game]\n");
							LoadGameElement.Image->setVisible(true);
							if( LoadGameElement.Hover )
							{
								LoadGameElement.Hover->setVisible(false);
							}
							if( LoadGameElement.Pressed )
							{
								LoadGameElement.Pressed->setVisible(false);
							}
						}
						break;
					}

					case EGTC_ID_OPTIONS:
					{
						if( OptionsElement.Active )
						{
							//COutput::Wprintf(L"EGET_ELEMENT_LEFT [options]\n");
							OptionsElement.Image->setVisible(true);
							if( OptionsElement.Hover )
							{
								OptionsElement.Hover->setVisible(false);
							}
							if( OptionsElement.Pressed )
							{
								OptionsElement.Pressed->setVisible(false);
							}
						}
						break;
					}

					case EGTC_ID_QUIT:
					{
						if( QuitGameElement.Active )
						{
							//COutput::Wprintf(L"EGET_ELEMENT_LEFT [quit]\n");
							QuitGameElement.Image->setVisible(true);
							if( QuitGameElement.Hover )
							{
								QuitGameElement.Hover->setVisible(false);
							}
							if( QuitGameElement.Pressed )
							{
								QuitGameElement.Pressed->setVisible(false);
							}
						}
						break;
					}
				}
				break;
			}

			// Clic de un elemento
			case irr::gui::EGET_ELEMENT_FOCUSED:
			{
				irr::s32 id = caller->getID();

				switch(id)
				{

					default:
					{
						return OnGUICustomEvent( caller , element , eventType );
						break;
					}

					case EGTC_ID_NEW_GAME:
					{
						if( NewGameElement.Active )
						{
							//COutput::Wprintf(L"EGET_ELEMENT_FOCUSED [new game]\n");
							NewGameElement.Image->setVisible(false);
							if( NewGameElement.Hover )
							{
								NewGameElement.Hover->setVisible(false);
							}
							if( NewGameElement.Pressed )
							{
								NewGameElement.Pressed->setVisible(true);
							}
							OnPressedElement();
							return OnNewGameEvent();
						}
						break;
					}

					case EGTC_ID_LOAD_GAME:
					{
						if( LoadGameElement.Active )
						{
							//COutput::Wprintf(L"EGET_ELEMENT_FOCUSED [load game]\n");
							LoadGameElement.Image->setVisible(false);
							if( LoadGameElement.Hover )
							{
								LoadGameElement.Hover->setVisible(false);
							}
							if( LoadGameElement.Pressed )
							{
								LoadGameElement.Pressed->setVisible(true);
							}
							OnPressedElement();
							return OnLoadGameEvent();
						}
						break;
					}

					case EGTC_ID_OPTIONS:
					{
						if( OptionsElement.Active )
						{
							//COutput::Wprintf(L"EGET_ELEMENT_FOCUSED [options]\n");
							OptionsElement.Image->setVisible(false);
							if( OptionsElement.Hover )
							{
								OptionsElement.Hover->setVisible(false);
							}
							if( OptionsElement.Pressed )
							{
								OptionsElement.Pressed->setVisible(true);
							}
							OnPressedElement();
							ShowOptionsWindow();
						}
						break;
					}

					case EGTC_ID_QUIT:
					{
						if( QuitGameElement.Active )
						{
							//COutput::Wprintf(L"EGET_ELEMENT_FOCUSED [options]\n");
							QuitGameElement.Image->setVisible(false);
							if( QuitGameElement.Hover )
							{
								QuitGameElement.Hover->setVisible(false);
							}
							if( QuitGameElement.Pressed )
							{
								QuitGameElement.Pressed->setVisible(true);
							}
							OnPressedElement();
							return OnQuitGameEvent();
						}
						break;
					}
				}
				break;
			}

			case irr::gui::EGET_CHECKBOX_CHANGED:
			{

				irr::s32 id = caller->getID();
				switch(id)
				{

					default:
					{
						return OnGUICustomEvent( caller , element , eventType );
						break;
					}

					case EGTC_ID_OPTIONS_VIDEO_STENCILSHADOW:
					{
						if( GUITitleElements.StencilShadowCheckBox->isChecked() )
						{
							GameDevices->GUIEnvironment->GetGUIEnvironment()->addMessageBox(
								L"Aviso",
								L"Esta opción reduce considerablemente el rendimiento",
								true);
						}
						break;
					}

					case EGTC_ID_OPTIONS_VIDEO_ANAGLYPHMODE:
					{
						GameDevices->GUIEnvironment->GetGUIEnvironment()->addMessageBox(
							L"Aviso",
							L"Esta característica es experimental y no está disponible por el momento",
							true);
						GUITitleElements.AnaglyphModeCheckBox->setChecked(false);
						break;
					}
				}
				break;
			}

			case irr::gui::EGET_SCROLL_BAR_CHANGED:
			{

				irr::s32 id = caller->getID();
				switch(id)
				{

					default:
					{
						return OnGUICustomEvent( caller , element , eventType );
						break;
					}

					case EGTC_ID_OPTIONS_AUDIO_MUSIC:
					{
						irr::s32 pos = GUITitleElements.MusicScrollBar->getPos();
						wchar_t value[512];
						COutput::Wsprintf(value,L"%d",pos);
						GUITitleElements.MusicStaticText->setText(value);
						break;
					}

					case EGTC_ID_OPTIONS_AUDIO_SOUND:
					{
						irr::s32 pos = GUITitleElements.SoundScrollBar->getPos();
						wchar_t value[512];
                        COutput::Wsprintf(value,L"%d",pos);
						GUITitleElements.SoundStaticText->setText(value);
						break;
					}
				}
			};

			case irr::gui::EGET_BUTTON_CLICKED:
			{

				irr::s32 id = caller->getID();
				switch(id)
				{

					default:
					{
						return OnGUICustomEvent( caller , element , eventType );
						break;
					}

					case EGTC_ID_NEW_GAME:
					{
						return OnNewGameEvent();
						//env->addFileOpenDialog(L"Seleccione el archivo .irr");
						break;
					}

					case EGTC_ID_LOAD_GAME:
					{
						return OnLoadGameEvent();
						//env->addFileOpenDialog(L"Seleccione el archivo .irr");
						break;
					}

					case EGTC_ID_OPTIONS:
					{
						ShowOptionsWindow();
						break;
					}

					case EGTC_ID_OPTIONS_ACCEPT:
					{

						GameDevices->GUIEnvironment->GetGUIEnvironment()->addMessageBox(
							L"Aviso",
							L"Debes reiniciar el juego para efectuar los cambios",
							true);

						irr::s32 music = GUITitleElements.MusicScrollBar->getPos();
						irr::s32 sound = GUITitleElements.SoundScrollBar->getPos();
						bool fullscreen = GUITitleElements.FullscreenCheckBox->isChecked();
						bool antialiasing = GUITitleElements.AntialiasingCheckBox->isChecked();
						//bool stencilshadow = GUITitleElements.StencilShadowCheckBox->isChecked();
						//bool anaglyphmode = GUITitleElements.AnaglyphModeCheckBox->isChecked();
						irr::s32 driver = GUITitleElements.DriverComboBox->getSelected();
						irr::s32 resolution = GUITitleElements.ResolutionComboBox->getSelected();

						std::list<SVideoMode* > *Modes = GameDevices->Video->GetVideoModes();
						std::list<SVideoMode* >::iterator it;
						for(it = Modes->begin() ; resolution>0 ; it++,resolution--);
						uint32 width = (*it)->width;
						uint32 height = (*it)->height;
						uint32 bpp = (*it)->bpp;

						wchar_t value[512];
						COutput::Wsprintf(value,L"%d",music);
						GameDevices->Config->SetConfigElement(L"audio",L"music",value);
                        COutput::Wsprintf(value,L"%d",sound);
						GameDevices->Config->SetConfigElement(L"audio",L"sound",value);

                        fullscreen ? COutput::Wsprintf(value,L"true") : COutput::Wsprintf(value,L"false");
						GameDevices->Config->SetConfigElement(L"video",L"fs",value);
                        antialiasing ? COutput::Wsprintf(value,L"true") : COutput::Wsprintf(value,L"false");
						GameDevices->Config->SetConfigElement(L"video",L"aa",value);
                        //stencilshadow ? COutput::Wsprintf(value,L"true") : COutput::Wsprintf(value,L"false");
						//GameDevices->Config->SetConfigElement(L"video",L"stencil",value);
                        //anaglyphmode ? COutput::Wsprintf(value,L"true") : COutput::Wsprintf(value,L"false");
						//GameDevices->Config->SetConfigElement(L"video",L"anaglyph",value);

                        COutput::Wsprintf(value,L"%d",driver+1);
						GameDevices->Config->SetConfigElement(L"video",L"driver",value);

                        COutput::Wsprintf(value,L"%d",width);
						GameDevices->Config->SetConfigElement(L"video",L"width",value);

                        COutput::Wsprintf(value,L"%d",height);
						GameDevices->Config->SetConfigElement(L"video",L"height",value);

                        COutput::Wsprintf(value,L"%d",bpp);
						GameDevices->Config->SetConfigElement(L"video",L"bpp",value);

						GameDevices->Config->SaveConfigFile();

						caller->getParent()->remove();
						break;
					}

					case EGTC_ID_OPTIONS_CANCEL:
					{
						caller->getParent()->remove();
						break;
					}

					case EGTC_ID_QUIT:
					{
						return OnQuitGameEvent();
						break;
					}
				}
				break;
			}
		}
		return false;
	}
};
