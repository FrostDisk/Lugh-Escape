#ifndef ___Balls__BlockDirection__H___
#define ___Balls__BlockDirection__H___

enum BallsBlockDirection
{

	/* +---+
	 * | x |
	 * +---+ */
	BBD_EMPTY,

	/* +   +
	 * |   |
	 * +   + */
	BBD_VERTICAL,

	/* +---+
	 *     
	 * +---+ */
	BBD_HORIZONTAL,

	/* +   +
	 *     
	 * +   + */
	BBD_CROSS,

	/* +---+
	 * |   
	 * +   + */
	BBD_RIGHTDOWN,

	/* +---+
	 *     |
	 * +   + */
	BBD_LEFTDOWN,

	/* +   +
	 * |    
	 * +---+ */
	BBD_DOWNRIGHT,

	/* +   +
	 *     | 
	 * +---+ */
	BBD_DOWNLEFT
};

#endif
