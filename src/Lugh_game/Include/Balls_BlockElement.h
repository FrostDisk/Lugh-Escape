#ifndef ___Balls__BlockElement__H___
#define ___Balls__BlockElement__H___

enum BallsBlockElement
{

	/* +---+
	 * | x |
	 * +---+ */
	BBE_EMPTY,

	/* +---+
	 * |   |
	 * +   + */
	BBE_DOWN,

	/* +---+
	 *     |
	 * +---+ */
	BBE_LEFT,

	/* +   +
	 * |   |
	 * +---+ */
	BBE_UP,

	/* +---+
	 * |   
	 * +---+ */
	BBE_RIGHT,

	/*
	 * o¬¬
	 */
	BBE_KEY
};

#endif
