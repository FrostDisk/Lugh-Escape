#ifndef ___Tornado__ElementAlign__H___
#define ___Tornado__ElementAlign__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Enumeración Alineamiento de Elemento           *
 * Archivo Fuente: EElementAlign.h                                    *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

namespace Tornado
{
	//! Enumeracion Alineamiento de Elemento
	enum EElementAlign
	{
		//! Centrado
		/* +-------+
		 * |       |
		 * |   X   |
		 * |       |
		 * +-------+ */
		EEA_CENTER,

		//! Superior-Izquierda
		/* +---+---+
		 * | X |   |
		 * +---+---+
		 * |   |   |
		 * +---+---+ */
		EEA_UPPERLEFT,

		//! Superior-Derecha
		/* +---+---+
		 * |   | X |
		 * +---+---+
		 * |   |   |
		 * +---+---+ */
		EEA_UPPERRIGHT,

		//! Superior-Centrado
		/* +-------+
		 * |   X   |
		 * +---+---+
		 * |   |   |
		 * +---+---+ */
		EEA_UPPERCENTER,

		//! Inferior-Izquierda
		/* +---+---+
		 * |   |   |
		 * +---+---+
		 * | X |   |
		 * +---+---+ */
		EEA_DOWNLEFT,

		//! Inferior-Derecha
		/* +---+---+
		 * |   |   |
		 * +---+---+
		 * |   | X |
		 * +---+---+ */
		EEA_DOWNRIGHT,

		//! Inferior-Centrado
		/* +---+---+
		 * |   |   |
		 * +---+---+
		 * |   X   |
		 * +-------+ */
		EEA_DOWNCENTER,

		//! Centrado-Izquierda
		/* +---+---+
		 * |   |   |
		 * | X +---+
		 * |   |   |
		 * +---+---+ */
		EEA_CENTERLEFT,

		//! Centrado-Derecha
		/* +---+---+
		 * |   |   |
		 * +---+ X |
		 * |   |   |
		 * +---+---+ */
		EEA_CENTERRIGHT,

		//! Fija
		/* +-------+
		 * |       |
		 * |  X?   |
		 * |       |
		 * +-------+ */
		EEA_FIXED
	};
};

#endif
