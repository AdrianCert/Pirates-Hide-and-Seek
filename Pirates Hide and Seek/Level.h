#include "GameVariable.h"
#ifndef LEVEL_H
#define LEVEL_H

namespace llvl {

	struct Level
	{
		// Request is structured by bits in this way 000000xxxaaabbbcccdddeeefffggghhh
		// Where each group of letter representing the count an element from GameEnum::Figures
		// In that group of 3 bit abc or xxx:
		//						xxx --> rotation of mark
		//								00 : top
		//								01 : right
		//								10 : down
		//								11 : left
		//						abc --> count of the item (figures) 
		//								000 : 0
		//								001 : 1
		//								010 : 2
		//								011 : 3
		//								100 : 4
		int Request;
		// Solution are structured by bits in this way 000000000000aaaaabbbbbcccccddddd
		// Where each group of letter representing each "islaces" acording have good solution
		// In that group of 5 bit abcde:
		//						a --> Relevant islace 
		//								1 : the next 4 bits are not relevant
		//								0 : the next 4 bits are relevant
		//						bc --> The corresponding dial
		//								00 : the islace is in top left dial
		//								01 : the islace is in top right dial
		//								10 : the islace is in buttom left dial
		//								11 : the islace is in buttom right dial
		//						de --> The Rotation of islace
		//								00 : the islace is rotated 000 degrees
		//								01 : the islace is rotated 090 degrees
		//								10 : the islace is rotated 180 degrees
		//								11 : the islace is rotated 270 degrees
		int Solution;
	};

	int coding_request(int* var);
	void decode_request(int var, int* x);
}

#endif // !LEVEL_H

