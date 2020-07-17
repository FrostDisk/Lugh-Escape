#ifndef ___Tornado__ContextElement__H___
#define ___Tornado__ContextElement__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Estructura Elemento de Context                 *
 * Archivo Fuente: SContextElement.h                                  *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "COutput.h"

namespace Tornado
{

	class CContext;

	//! Estructura Elemento de Contexto
	struct SContextElement
	{

		//! Constructor de Estructura
		SContextElement() :
			Id(0),
			Context(NULL),
			Back(NULL),
			Next(NULL)
		{
			//COutput::Wprintf(L"Construyendo Estructura\n");
		}

		//! Constructor copia de Estructura
		SContextElement(const SContextElement &pt)
		{
			*this = pt;
		}

		//! Destructor de Estructura
		~SContextElement()
		{
			//COutput::Wprintf(L"Destruyendo Estructura(%d)\n",Id);
			Context = NULL;
			Back = NULL;
			Next = NULL;
		}

		//! Operador = de Estructura
		SContextElement& operator= (const SContextElement &pt)
		{
			Id = pt.Id;
			Context = pt.Context;
			return *this;
		}

		//! ID de Contexto
		uint16 Id;

		//! Referencia a Contexto
		CContext *Context;

		//! Referencia al anterior contexto
		SContextElement *Back;

		//! Referencia al siguiente contexto
		SContextElement *Next;

	};
}

#endif
