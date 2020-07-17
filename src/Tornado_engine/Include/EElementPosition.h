#ifndef ___Tornado__ElementPosition__H___
#define ___Tornado__ElementPosition__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Cabecera de Enumeración Posición de Elemento               *
 * Archivo Fuente: EElementPosition.h                                 *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

namespace Tornado
{
	//! Enumeracion Posicion de Elemento
	enum EElementPosition
	{

		//! Centrado
		/* +-------+
		 * |       |
		 * |   X   |
		 * |       |
		 * +-------+ */
		EEP_CENTER,

		//! Superior-Izquierda
		/* +---+---+
		 * | X |   |
		 * +---+---+
		 * |   |   |
		 * +---+---+ */
		EEP_UPPERLEFT,

		//! Superior-Derecha
		/* +---+---+
		 * |   | X |
		 * +---+---+
		 * |   |   |
		 * +---+---+ */
		EEP_UPPERRIGHT,

		//! Superior-Centrado
		/* +-------+
		 * |   X   |
		 * +---+---+
		 * |   |   |
		 * +---+---+ */
		EEP_UPPERCENTER,

		//! Inferior-Izquierda
		/* +---+---+
		 * |   |   |
		 * +---+---+
		 * | X |   |
		 * +---+---+ */
		EEP_DOWNLEFT,

		//! Inferior-Derecha
		/* +---+---+
		 * |   |   |
		 * +---+---+
		 * |   | X |
		 * +---+---+ */
		EEP_DOWNRIGHT,

		//! Inferior-Centrado
		/* +---+---+
		 * |   |   |
		 * +---+---+
		 * |   X   |
		 * +-------+ */
		EEP_DOWNCENTER,

		//! Centrado-Izquierda
		/* +---+---+
		 * |   |   |
		 * | X +---+
		 * |   |   |
		 * +---+---+ */
		EEP_CENTERLEFT,

		//! Centrado-Derecha
		/* +---+---+
		 * |   |   |
		 * +---+ X |
		 * |   |   |
		 * +---+---+ */
		EEP_CENTERRIGHT,

		//! Fija
		/* +-------+
		 * |       |
		 * |  X?   |
		 * |       |
		 * +-------+ */
		EEP_FIXED
	};
};

#endif
