#ifndef ___Balls__Matrix__H___
#define ___Balls__Matrix__H___

#include <Tornado.h>

#include "Balls_BlockDirection.h"
#include "Balls_BlockElement.h"
#include "Balls_MoveDirection.h"

using namespace Tornado;

class BallsContextMain;

class BallsMatrix
{

private:

	// ¿Está finalizado?
	bool IsFinish;

	// ¿Perdió?
	bool IsGameOver;

	// ¿Es modo Jefe?
	bool IsBossMode;

	//-----------------------------------------------------

	// Columnas de la matriz
	uint16 cols;

	// Filas de la matriz
	uint16 rows;

	//-----------------------------------------------------

	// Posicion inicial del tablero
	irr::core::vector2di StartIndex;

	// Posicion final del tablero
	irr::core::vector2di FinishIndex;

	// Posicion del inicio del tablero
	irr::core::vector3df StartPosition;

	// Posicion del final del tablero
	irr::core::vector3df FinishPosition;

	//-----------------------------------------------------

	// Posicion 'real' actual de la pelota
	irr::core::vector3df RealPosition;

	//-----------------------------------------------------

	// Posicion inicial del 'desplazamiento'
	irr::core::vector3df InitFlyStraight;

	// Posicion final del 'desplazamiento'
	irr::core::vector3df EndFlyStraight;

	// Vector de Rotación de la pelota
	irr::core::vector3df RotationVector;

	// Vector de Rotacion de la iteracion anterior
	irr::core::vector3df OldRotationVector;

	//-----------------------------------------------------

	// Posicion actual dentro de la matriz
	irr::core::vector2di ActualIndex;

	// Posicion siguiente dentro de la matriz
	irr::core::vector2di NextIndex;

	// Movimiento actual
	uint16 actualDirection;

	// Siguiente movimiento en la matriz
	uint16 nextDirection;

	// Dimension de la matriz
	uint16 dimension;

	// Numero de movimientos
	uint16 nroMoves;

	//-----------------------------------------------------

	struct SBlock
	{
		// Veces que ha pasado la pelota
		uint16 passes;

		// Indice Matriz
		uint16 x,y;

		// Tipo de Bloque
		uint16 block;

		// Información del Bloque
		uint16 info;

		// Posicion 'real' del bloque
		irr::core::vector3df position;

	} *matrix;

	friend class BallsContextMain;

protected:
public:
	BallsMatrix();

	bool Init(	const uint16 cols,
				const uint16 rows,
				const irr::core::vector2di &start,
				const irr::core::vector2di &finish,
				const uint16 initialDirection,
				const uint16 finalDirection,
				const irr::core::vector3df &rotation,
				const real height,
				const bool isboss );

	bool NextMove(void);

	uint16 GetBlockPasses(void);
	uint16 GetBlockUnpasses(void);


	inline void SetStartPosition(const irr::core::vector3df &position)
	{
		StartPosition = position;
	}

	inline void SetFinishPosition(const irr::core::vector3df &position)
	{
		FinishPosition = position;
	}

	inline void SetRealPosition(const irr::core::vector3df &position)
	{
		RealPosition = position;
	}

	// Asigna una posicion de la matriz
	inline void SetPosition(const uint16 index,const irr::core::vector3df &position,const uint16 block=BBD_EMPTY)
	{
		if( index < rows * cols )
		{
			matrix[ index ].position = position;
			matrix[ index ].block = block;
		}
	}

	// Asigna una posicion de la matriz
	inline void SetPosition(const uint16 tmp_cols,const uint16 tmp_rows,const irr::core::vector3df &position,const uint16 block=BBD_EMPTY)
	{
		SetPosition( tmp_rows * cols + tmp_cols , position , block );
	}

	// Asigna el tipo de bloque de un indice de la matriz
	inline void SetBlockType(const uint16 index,const uint16 block)
	{
		if( index < dimension ){
			matrix[ index ].block = block;
		}
	}

	// Asigna el tipo de bloque de un indice de la matriz
	inline void SetBlockType(const uint16 tmp_cols,const uint16 tmp_rows,const uint16 tmp_block)
	{
		SetBlockType( tmp_rows * cols + tmp_cols , tmp_block );
	}

	#if defined(_DEBUG)
	void PrintMatrix(void);
	#endif
};

#endif

