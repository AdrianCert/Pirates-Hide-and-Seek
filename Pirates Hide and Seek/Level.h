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
		//								000 : NOMARK
		//								001 : top
		//								010 : right
		//								011 : down
		//								100 : left
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

	int CodingRequest(int* var);
	void DecodeRequest(int var, int* x);
	int CodingSolution(int* var);
	void DecodeSolution(int var, int* x);
}

namespace lvl {
	bool GetIslaceMath(int Islace, int V[][3]) {
		switch (Islace%4)
		{
		case 0:
				V[0 ][0] = 1; V[0][1] = 1; V[0][2] = 1;
				V[1 ][0] = 1; V[1][1] = 0; V[1][2] = 1;
				V[2 ][0] = 1; V[2][1] = 0; V[2][2] = 1;
			break;
		default:
			break;
		}
		int MatIslace_B[3][3] = {
			1, 1, 1,
			1, 0, 1,
			1, 0, 1
		};

	}
	struct Islace {
		bool Relevant;
		int Position : 2;
		int Rotation : 2;
		int M[3][3];
	};
	struct State {
		Islace A;
		Islace B;
		Islace C;
		Islace D;
	};
	struct Level
	{
		int Request[9];
		State Solution;
		State Stash;
	};

	bool LoadLevel(int requested_lvl, Level* played_lvl);
	int GetRequest(int var);
	// Graphish Helper Funtion
	int GetCountDrowedFigures(Level* curentLVL);
}

#endif // !LEVEL_H

