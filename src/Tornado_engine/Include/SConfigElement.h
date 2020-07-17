#ifndef ___Tornado__ConfigElement__H___
#define ___Tornado__ConfigElement__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Estructura Elemento de Configuración           *
 * Archivo Fuente: SConfigElement.h                                   *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include <iostream>
#include <string>

namespace Tornado
{
	//! Estructura Elemento de Configuración
	struct SConfigElement
	{

		//! Constructor de Estructura
		SConfigElement() :
			Type(),
			Name(),
			Value(),
			Default()
		{
		}

		//! Constructor copia de Estructura
		SConfigElement( const SConfigElement &pt )
		{
			*this = pt;
		}

		//! Operador = de Estructura
		SConfigElement& operator= (const SConfigElement &pt)
		{
			Type = pt.Type;
			Name = pt.Name;
			Value = pt.Value;
			Default = pt.Default;
			return *this;
		}

		//! Sección
		std::wstring* Type;

		//! Nombre
		std::wstring* Name;

		//! Valor
		std::wstring* Value;

		//! Valor por defecto
		std::wstring* Default;

	};
};

#endif
