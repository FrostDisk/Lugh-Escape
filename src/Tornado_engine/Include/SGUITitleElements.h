#ifndef ___Tornado__GUITitleElements__H___
#define ___Tornado__GUITitleElements__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Estructura Elementos de Título de GUI          *
 * Archivo Fuente: SGUITitleElements.h                                *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include <irrlicht.h>

namespace Tornado
{

	//! Estructura Elementos de Menu de GUI
	struct SGUITitleElements
	{
		//! Constructor de Estructura
		SGUITitleElements() :
			OptionsWindow(NULL),
			FullscreenCheckBox(NULL),
			AntialiasingCheckBox(NULL),
			VerticalSyncCheckBox(NULL),
			StencilShadowCheckBox(NULL),
			AnaglyphModeCheckBox(NULL),
			MusicScrollBar(NULL),
			SoundScrollBar(NULL),
			MusicStaticText(NULL),
			SoundStaticText(NULL),
			DriverComboBox(NULL),
			ResolutionComboBox(NULL),
			ShadowMapResolutionComboBox(NULL),
			ShadowMapFilteringComboBox(NULL)
		{
		}

		//! Constructor copia de Estructura
		SGUITitleElements( const SGUITitleElements &pt )
		{
			*this = pt;
		}

		//! Operador = de Estructura
		SGUITitleElements& operator= (const SGUITitleElements &pt)
		{
			this->OptionsWindow = pt.OptionsWindow;
			this->FullscreenCheckBox = pt.FullscreenCheckBox;
			this->AntialiasingCheckBox = pt.AntialiasingCheckBox;
			this->VerticalSyncCheckBox = pt.VerticalSyncCheckBox;
			this->StencilShadowCheckBox = pt.StencilShadowCheckBox;
			this->AnaglyphModeCheckBox = pt.AnaglyphModeCheckBox;
			this->MusicScrollBar = pt.MusicScrollBar;
			this->SoundScrollBar = pt.SoundScrollBar;
			this->MusicStaticText = pt.MusicStaticText;
			this->SoundStaticText = pt.SoundStaticText;
			this->DriverComboBox = pt.DriverComboBox;
			this->ResolutionComboBox = pt.ResolutionComboBox;
			this->ShadowMapResolutionComboBox = pt.ShadowMapResolutionComboBox;
			this->ShadowMapFilteringComboBox = pt.ShadowMapFilteringComboBox;
			return *this;
		}

		//! Ventana de Opciones
		irr::gui::IGUIWindow* OptionsWindow;

		//! Pantalla Completa
		irr::gui::IGUICheckBox *FullscreenCheckBox;

		//! Anti-aliasing
		irr::gui::IGUICheckBox *AntialiasingCheckBox;

		//! VerticalSync
		irr::gui::IGUICheckBox *VerticalSyncCheckBox;

		//! Stencil-Shadow
		irr::gui::IGUICheckBox *StencilShadowCheckBox;

		//! Modo Anaglyph
		irr::gui::IGUICheckBox *AnaglyphModeCheckBox;

		//! Volúmen de la Música
		irr::gui::IGUIScrollBar *MusicScrollBar;

		//! Volúmen de los Sonidos
		irr::gui::IGUIScrollBar *SoundScrollBar;

		//! Texto del Volumen de la Música
		irr::gui::IGUIStaticText *MusicStaticText;

		//! Texto del Volúmen de los Sonidos
		irr::gui::IGUIStaticText *SoundStaticText;

		//! Lista de Dispositivos de Video
		irr::gui::IGUIComboBox *DriverComboBox;

		//! Lista de Resoluciones de Video compatibles
		irr::gui::IGUIComboBox *ResolutionComboBox;

		//! Lista de Resoluciones para el ShadowMap
		irr::gui::IGUIComboBox *ShadowMapResolutionComboBox;

		//! Lista de Filtros para el ShadowMap
		irr::gui::IGUIComboBox *ShadowMapFilteringComboBox;
	};

};

#endif
