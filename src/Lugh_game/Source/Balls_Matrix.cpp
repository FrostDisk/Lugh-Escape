#include "Balls_Matrix.h"

BallsMatrix::BallsMatrix() : 
					IsFinish(false),
					IsGameOver(false),
					rows(0),
					cols(0),					
					StartIndex(),
					FinishIndex(),
					StartPosition(),
					FinishPosition(),
					RealPosition(),
					InitFlyStraight(),
					EndFlyStraight(),
					RotationVector(),
					OldRotationVector(),
					ActualIndex(),
					NextIndex(),
					actualDirection(BMD_START),
					nextDirection(BMD_START),
					dimension(0),
					nroMoves(0),
					matrix(0)
{
}

/*
 * estructura matriz
 * 
 *  x  0   1   2   3
 * y +---+---+---+---+
   0 | 0 | 1 | 2 | 3 |
     +---+---+---+---+
   1 | 4 | 5 | 6 | 7 |
     +---+---+---+---+
   2 | 8 | 9 | 10| 11|
     +---+---+---+---+
 */
bool BallsMatrix::Init(	const uint16 matrixCols,
						const uint16 matrixRows,
						const irr::core::vector2di &start,
						const irr::core::vector2di &finish,
						const uint16 initialDirection,
						const uint16 finalDirection,
						const irr::core::vector3df &rotation,
						const real height,
						const bool isBoss )
{
	#if defined(_DEBUG)
	COutput::Wprintf(L"Inicializando Matriz (%d,%d)\n",matrixRows,matrixCols);
	COutput::Wprintf(L"Posicion Inicio: (%d,%d)\n",start.X,start.Y);
	COutput::Wprintf(L"Posicion Final: (%d,%d)\n",finish.X,finish.Y);
	COutput::Wprintf(L"Rotation: (%f,%f,%f)\n",rotation.X,rotation.Y,rotation.Z);
	#endif

	if( !matrix ) delete matrix;

	IsFinish = false;
	IsGameOver = false;
	IsBossMode = isBoss;

	cols = matrixCols;
	rows = matrixRows;
	StartIndex = start;
	FinishIndex = finish;
	InitFlyStraight = EndFlyStraight = irr::core::vector3df((irr::f32)start.Y*10.0f,height,(irr::f32)start.X*10.0f);
	RotationVector = OldRotationVector = rotation;
	/*switch( initialDirection )
	{
		case BMD_LEFT:{	RotationVector = irr::core::vector3df(  0.0f,0.0f, 0.0f );break;}
		case BMD_DOWN:{	RotationVector = irr::core::vector3df(  0.0f,0.0f, 0.0f );break;}
		case BMD_UP:{	RotationVector = irr::core::vector3df(  0.0f,0.0f, 0.0f );break;}
		case BMD_RIGHT:{RotationVector = irr::core::vector3df(  0.0f,0.0f, 0.0f );break;}
		case BMD_START:
		case BMD_STOP:
		case BMD_FALL:{RotationVector = irr::core::vector3df( 0.0f,0.0f,0.0f );break;}
	}*/

	ActualIndex = NextIndex = start;
	actualDirection = nextDirection = initialDirection;
	dimension = matrixRows * matrixCols;
	nroMoves = 0;

	matrix = new SBlock[ dimension + 1 ];

	for(uint16 i=0 ; i<dimension ; i++ )
	{
		matrix[i].passes = 0 ;
		matrix[i].x = i % matrixRows ;
		matrix[i].y = i / matrixRows ;
		#if defined(_DEBUG)
		//COutput::Wprintf(L"x=%d y=%d\n",matrix[i].x,matrix[i].y);
		#endif
		matrix[i].block = BBD_EMPTY;
		matrix[i].info = BBE_EMPTY;

		if( StartIndex.X == matrix[i].x && StartIndex.Y == matrix[i].y )
		{
			switch( initialDirection )
			{
				case BMD_LEFT:{	matrix[i].info = BBE_LEFT;break;}
				case BMD_DOWN:{	matrix[i].info = BBE_DOWN;break;}
				case BMD_UP:{	matrix[i].info = BBE_UP;break;}
				case BMD_RIGHT:{matrix[i].info = BBE_RIGHT;break;}
			}
		}

		if( FinishIndex.X == matrix[i].x && FinishIndex.Y == matrix[i].y )
		{
			switch( finalDirection )
			{
				case BMD_LEFT:{	matrix[i].info = BBE_LEFT;break;}
				case BMD_DOWN:{	matrix[i].info = BBE_DOWN;break;}
				case BMD_UP:{	matrix[i].info = BBE_UP;break;}
				case BMD_RIGHT:{matrix[i].info = BBE_RIGHT;break;}
			}
		}
	}

	return true;
}


bool BallsMatrix::NextMove(void)
{
	if( !IsFinish )
	{
		uint16 index;
		actualDirection = nextDirection;
		InitFlyStraight = EndFlyStraight;
		ActualIndex = NextIndex;
		OldRotationVector = RotationVector;

		#if defined(_DEBUG)
		switch( nextDirection )
		{
			case BMD_START:COutput::Wprintf(L"Ahora... START\n");break;
			case BMD_LEFT:COutput::Wprintf(L"Ahora... LEFT <-\n");break;
			case BMD_DOWN:COutput::Wprintf(L"Ahora... DOWN\n");break;
			case BMD_UP:COutput::Wprintf(L"Ahora... UP\n");break;
			case BMD_RIGHT:COutput::Wprintf(L"Ahora... RIGHT ->\n");break;
			case BMD_STOP:COutput::Wprintf(L"Ahora... STOP X\n");break;
			case BMD_FALL:COutput::Wprintf(L"Ahora... FALL O\n");break;
		}
		#endif

		if( (FinishIndex.X == ActualIndex.X) && (FinishIndex.Y == ActualIndex.Y) )
		{
			#if defined(_DEBUG)
			COutput::Wprintf(L"Termino la partida\n");
			#endif

			nextDirection = BMD_STOP;
			IsFinish = true;

			index = ActualIndex.Y * cols + ActualIndex.X;
			if( IsBossMode && matrix[ index ].block == BBD_EMPTY )
			{
				IsGameOver = true;
				#if defined(_DEBUG)
				COutput::Wprintf(L"GAME OVER\n");
				#endif
			}
		}
		else 
		{
			if( nroMoves > 0 )
			{
				index = ActualIndex.Y * cols + ActualIndex.X;
				COutput::Wprintf(L"index = %d\n",index);
				matrix[ index ].passes += 1;
			}
			switch( actualDirection )
			{
				case BMD_LEFT:
				{
					index = ActualIndex.Y * cols + ActualIndex.X - 1;
					#if defined(_DEBUG)
					COutput::Wprintf(L"IndiceMatrix: %d\n",index);
					#endif
					if( (FinishIndex.X == ActualIndex.X - 1) && (FinishIndex.Y == ActualIndex.Y) )
					{
						NextIndex.X -= 1;
						nextDirection= BMD_LEFT;
						EndFlyStraight = FinishPosition;
					}
					else if( ActualIndex.X - 1 >= 0 )
					{
						NextIndex.X -= 1;
						EndFlyStraight = matrix[ index ].position;
						switch( matrix[ index ].block )
						{
							default:
							case BBD_EMPTY:{	nextDirection = BMD_FALL;break;}
							case BBD_VERTICAL:{	nextDirection = BMD_STOP;IsFinish=IsGameOver=true;break;}
							case BBD_HORIZONTAL:{nextDirection= BMD_LEFT;break;}
							case BBD_CROSS:{	nextDirection = BMD_LEFT;break;}
							case BBD_RIGHTDOWN:{nextDirection = BMD_DOWN;break;}
							case BBD_LEFTDOWN:{	nextDirection = BMD_STOP;IsFinish=IsGameOver=true;break;}
							case BBD_DOWNRIGHT:{nextDirection = BMD_UP;break;}
							case BBD_DOWNLEFT:{	nextDirection = BMD_STOP;IsFinish=IsGameOver=true;break;}
						}
						switch( nextDirection )
						{
							default:{		/*RotationVector = irr::core::vector3df( 0.0f,0.0f, 0.0f );*/break;}
							case BMD_DOWN:{	RotationVector += irr::core::vector3df(  0.0f,-90.0f,0.0f );break;}
							case BMD_UP:{	RotationVector += irr::core::vector3df(  0.0f,90.0f, 0.0f );break;}
							case BMD_RIGHT:{RotationVector += irr::core::vector3df(  0.0f,180.0f, 0.0f );break;}
						}
						#if defined(_DEBUG)
						switch( matrix[ index ].block )
						{
							default:
							case BBD_EMPTY:{	COutput::Wprintf(L"Found: VACIO\n");break;}
							case BBD_VERTICAL:{	COutput::Wprintf(L"Found: VERTICAL\n");break;}
							case BBD_HORIZONTAL:{COutput::Wprintf(L"Found: HORIZONTAL\n");break;}
							case BBD_CROSS:{	COutput::Wprintf(L"Found: CROSS\n");break;}
							case BBD_RIGHTDOWN:{COutput::Wprintf(L"Found: RIGHTDOWN\n");break;}
							case BBD_LEFTDOWN:{	COutput::Wprintf(L"Found: LEFTDOWN\n");break;}
							case BBD_DOWNRIGHT:{COutput::Wprintf(L"Found: DOWNRIGHT\n");break;}
							case BBD_DOWNLEFT:{	COutput::Wprintf(L"Found: DOWNLEFT\n");break;}
						}
						#endif
					}
					else
					{
						nextDirection = BMD_STOP;
						IsFinish = true;
						IsGameOver = true;
					}
					break;
				}
				case BMD_DOWN:
				{
					index = ( ActualIndex.Y + 1 ) * cols + ActualIndex.X;
					#if defined(_DEBUG)
					COutput::Wprintf(L"IndiceMatrix: %d\n",index);
					#endif
					if( (FinishIndex.X == ActualIndex.X) && (FinishIndex.Y == ActualIndex.Y + 1) )
					{
						NextIndex.Y += 1;
						nextDirection= BMD_DOWN;
						EndFlyStraight = FinishPosition;
					}
					else if( ActualIndex.Y + 1 < rows )
					{
						NextIndex.Y += 1;
						EndFlyStraight = matrix[ index ].position;
						switch( matrix[ index ].block )
						{
							default:
							case BBD_EMPTY:{	nextDirection = BMD_FALL;break;}
							case BBD_VERTICAL:{	nextDirection = BMD_DOWN;break;}
							case BBD_HORIZONTAL:{nextDirection= BMD_STOP;IsFinish=IsGameOver=true;break;}
							case BBD_CROSS:{	nextDirection = BMD_DOWN;break;}
							case BBD_RIGHTDOWN:{nextDirection = BMD_STOP;IsFinish=IsGameOver=true;break;}
							case BBD_LEFTDOWN:{	nextDirection = BMD_STOP;IsFinish=IsGameOver=true;break;}
							case BBD_DOWNRIGHT:{nextDirection = BMD_RIGHT;break;}
							case BBD_DOWNLEFT:{	nextDirection = BMD_LEFT;break;}
						}
						switch( nextDirection )
						{
							default:{	/*RotationVector = irr::core::vector3df( 0.0f,0.0f, 0.0f );*/break;}
							case BMD_LEFT:{	RotationVector += irr::core::vector3df(  0.0f,90.0f,0.0f );break;}
							case BMD_UP:{	RotationVector += irr::core::vector3df(  0.0f,180.0f, 0.0f );break;}
							case BMD_RIGHT:{RotationVector += irr::core::vector3df(  0.0f,-90.0f, 0.0f );break;}
						}
						#if defined(_DEBUG)
						switch( matrix[ index ].block )
						{
							default:
							case BBD_EMPTY:{	COutput::Wprintf(L"Found: VACIO\n");break;}
							case BBD_VERTICAL:{	COutput::Wprintf(L"Found: VERTICAL\n");break;}
							case BBD_HORIZONTAL:{COutput::Wprintf(L"Found: HORIZONTAL\n");break;}
							case BBD_CROSS:{	COutput::Wprintf(L"Found: CROSS\n");break;}
							case BBD_RIGHTDOWN:{COutput::Wprintf(L"Found: RIGHTDOWN\n");break;}
							case BBD_LEFTDOWN:{	COutput::Wprintf(L"Found: LEFTDOWN\n");break;}
							case BBD_DOWNRIGHT:{COutput::Wprintf(L"Found: DOWNRIGHT\n");break;}
							case BBD_DOWNLEFT:{	COutput::Wprintf(L"Found: DOWNLEFT\n");break;}
						}
						#endif
					}
					else
					{
						nextDirection = BMD_STOP;
						IsFinish = true;
						IsGameOver = true;
					}
					break;
				}
				case BMD_UP:
				{
					index = ( ActualIndex.Y - 1 ) * cols + ActualIndex.X;
					#if defined(_DEBUG)
					COutput::Wprintf(L"IndiceMatrix: %d\n",index);
					#endif
					if( (FinishIndex.X == ActualIndex.X) && (FinishIndex.Y == ActualIndex.Y - 1) )
					{
						NextIndex.Y -= 1;
						nextDirection= BMD_UP;
						EndFlyStraight = FinishPosition;
					}
					else if( ActualIndex.Y - 1 >= 0 )
					{
						NextIndex.Y -= 1;
						EndFlyStraight = matrix[ index ].position;
						switch( matrix[ index ].block )
						{
							default:
							case BBD_EMPTY:{	nextDirection = BMD_FALL;break;}
							case BBD_VERTICAL:{	nextDirection = BMD_UP;break;}
							case BBD_HORIZONTAL:{nextDirection= BMD_STOP;IsFinish=IsGameOver=true;break;}
							case BBD_CROSS:{	nextDirection = BMD_UP;break;}
							case BBD_RIGHTDOWN:{nextDirection = BMD_RIGHT;break;}
							case BBD_LEFTDOWN:{	nextDirection = BMD_LEFT;break;}
							case BBD_DOWNRIGHT:{nextDirection = BMD_STOP;IsFinish=IsGameOver=true;break;}
							case BBD_DOWNLEFT:{	nextDirection = BMD_STOP;IsFinish=IsGameOver=true;break;}
						}
						switch( nextDirection )
						{
							default:{	/*RotationVector = irr::core::vector3df( 0.0f,0.0f, 0.0f );*/break;}
							case BMD_DOWN:{	RotationVector += irr::core::vector3df(  0.0f,180.0f,0.0f );break;}
							case BMD_LEFT:{	RotationVector += irr::core::vector3df(  0.0f,-90.0f, 0.0f );break;}
							case BMD_RIGHT:{RotationVector += irr::core::vector3df(  0.0f,90.0f, 0.0f );break;}
						}
						#if defined(_DEBUG)
						switch( matrix[ index ].block )
						{
							default:
							case BBD_EMPTY:{	COutput::Wprintf(L"Found: VACIO\n");break;}
							case BBD_VERTICAL:{	COutput::Wprintf(L"Found: VERTICAL\n");break;}
							case BBD_HORIZONTAL:{COutput::Wprintf(L"Found: HORIZONTAL\n");break;}
							case BBD_CROSS:{	COutput::Wprintf(L"Found: CROSS\n");break;}
							case BBD_RIGHTDOWN:{COutput::Wprintf(L"Found: RIGHTDOWN\n");break;}
							case BBD_LEFTDOWN:{	COutput::Wprintf(L"Found: LEFTDOWN\n");break;}
							case BBD_DOWNRIGHT:{COutput::Wprintf(L"Found: DOWNRIGHT\n");break;}
							case BBD_DOWNLEFT:{	COutput::Wprintf(L"Found: DOWNLEFT\n");break;}
						}
						#endif
					}
					else
					{
						nextDirection = BMD_STOP;
						IsFinish = true;
						IsGameOver = true;
					}
					break;
				}
				case BMD_RIGHT:
				{
					index = ActualIndex.Y * cols + ActualIndex.X + 1;
					#if defined(_DEBUG)
					COutput::Wprintf(L"IndiceMatrix: %d\n",index);
					#endif
					if( (FinishIndex.X == ActualIndex.X + 1) && (FinishIndex.Y == ActualIndex.Y) )
					{
						NextIndex.X += 1;
						nextDirection= BMD_RIGHT;
						EndFlyStraight = FinishPosition;
					}
					else if( ActualIndex.X + 1 < cols )
					{
						NextIndex.X += 1;
						EndFlyStraight = matrix[ index ].position;
						switch( matrix[ index ].block )
						{
							default:
							case BBD_EMPTY:{	nextDirection = BMD_FALL;break;}
							case BBD_VERTICAL:{	nextDirection = BMD_STOP;IsFinish=IsGameOver=true;break;}
							case BBD_HORIZONTAL:{nextDirection= BMD_RIGHT;break;}
							case BBD_CROSS:{	nextDirection = BMD_RIGHT;break;}
							case BBD_RIGHTDOWN:{nextDirection = BMD_STOP;IsFinish=IsGameOver=true;break;}
							case BBD_LEFTDOWN:{	nextDirection = BMD_DOWN;break;}
							case BBD_DOWNRIGHT:{nextDirection = BMD_STOP;IsFinish=IsGameOver=true;break;}
							case BBD_DOWNLEFT:{	nextDirection = BMD_UP;break;}
						}
						switch( nextDirection )
						{
							default:{	/*RotationVector = irr::core::vector3df( 0.0f,0.0f, 0.0f );*/break;}
							case BMD_DOWN:{	RotationVector += irr::core::vector3df(  0.0f,90.0f,0.0f );break;}
							case BMD_UP:{	RotationVector += irr::core::vector3df(  0.0f,-90.0f, 0.0f );break;}
							case BMD_LEFT:{RotationVector += irr::core::vector3df(  0.0f,180.0f, 0.0f );break;}
						}
						#if defined(_DEBUG)
						switch( matrix[ index ].block )
						{
							default:
							case BBD_EMPTY:{	COutput::Wprintf(L"Found: VACIO\n");break;}
							case BBD_VERTICAL:{	COutput::Wprintf(L"Found: VERTICAL\n");break;}
							case BBD_HORIZONTAL:{COutput::Wprintf(L"Found: HORIZONTAL\n");break;}
							case BBD_CROSS:{	COutput::Wprintf(L"Found: CROSS\n");break;}
							case BBD_RIGHTDOWN:{COutput::Wprintf(L"Found: RIGHTDOWN\n");break;}
							case BBD_LEFTDOWN:{	COutput::Wprintf(L"Found: LEFTDOWN\n");break;}
							case BBD_DOWNRIGHT:{COutput::Wprintf(L"Found: DOWNRIGHT\n");break;}
							case BBD_DOWNLEFT:{	COutput::Wprintf(L"Found: DOWNLEFT\n");break;}
						}
						#endif
					}
					else
					{
						nextDirection = BMD_STOP;
						IsFinish = true;
						IsGameOver = true;
						RotationVector = irr::core::vector3df( 0.0f,0.0f, 0.0f );
					}
					break;
				}
				case BMD_STOP:
				{
					IsFinish = true;
					IsGameOver = true;
					return true;
					break;
				}
				case BMD_FALL:
				{
					IsFinish = true;
					IsGameOver = true;
					return true;
					break;
				}
			}
		}
	}

	/*switch( actualDirection )
	{
		case BMD_LEFT:{	RotationVector = irr::core::vector3df( -90.0f,0.0f, 0.0f );break;}
		case BMD_DOWN:{	RotationVector = irr::core::vector3df(  0.0f,0.0f,-90.0f );break;}
		case BMD_UP:{	RotationVector = irr::core::vector3df(  0.0f,0.0f, 1.0f );break;}
		case BMD_RIGHT:{RotationVector = irr::core::vector3df(  1.0f,0.0f, 0.0f );break;}
		case BMD_START:
		case BMD_STOP:
		case BMD_FALL:{	RotationVector = irr::core::vector3df( 0.0f,0.0f,0.0f );break;}
	}*/

	#if defined(_DEBUG)
	switch( nextDirection )
	{
		case BMD_START:COutput::Wprintf(L"Despues... START\n");break;
		case BMD_LEFT:COutput::Wprintf(L"Despues... LEFT <-\n");break;
		case BMD_DOWN:COutput::Wprintf(L"Despues... DOWN\n");break;
		case BMD_UP:COutput::Wprintf(L"Despues... UP\n");break;
		case BMD_RIGHT:COutput::Wprintf(L"Despues... RIGHT ->\n");break;
		case BMD_STOP:COutput::Wprintf(L"Despues... STOP X\n");break;
		case BMD_FALL:COutput::Wprintf(L"Despues... FALL O\n");break;
	}
	#endif

	nroMoves += 1;

	return false;
}

// Retorna el número de bloques que atravesó la pelota
uint16 BallsMatrix::GetBlockPasses(void)
{
	uint16 counter = 0;
	for(uint16 y=0 ; y<rows ; y++ )
	{
		for(uint16 x=0 ; x<cols ; x++ )
		{
			uint16 index = y * cols + x;
			if( matrix[index].block!=0 && matrix[index].passes>0 )
			{
				counter += matrix[index].passes;
			}
		}
	}
	return counter;
}

// Retorna el número de bloques que no-atravesó la pelota
uint16 BallsMatrix::GetBlockUnpasses(void)
{
	uint16 counter = 0;
	for(uint16 y=0 ; y<rows ; y++ )
	{
		for(uint16 x=0 ; x<cols ; x++ )
		{
			uint16 index = y * cols + x;
			if( matrix[index].block!=0 && matrix[index].passes==0 )
			{
				counter += 1;
			}
		}
	}
	return counter;
}

#if defined(_DEBUG)
// Imprime la matriz (solo DEBUG)
void BallsMatrix::PrintMatrix(void)
{
	for(uint16 y=0 ; y<rows ; y++ )
	{
		COutput::Wprintf(L"| ");
		for(uint16 x=0 ; x<cols ; x++ )
		{
			COutput::Wprintf( L"%d " , matrix[ y * cols + x ].block );
		}
		COutput::Wprintf(L"|\n");
	}
	COutput::Wprintf(L"\n\n");

	/*for(uint16 y=0 ; y<rows ; y++ )
	{
		COutput::Wprintf(L"| ");
		for(uint16 x=0 ; x<cols ; x++ )
		{
			COutput::Wprintf( L"%d " , matrix[ y * cols + x ].passes );
		}
		COutput::Wprintf(L"|\n");
	}
	COutput::Wprintf(L"\n");*/
}
#endif