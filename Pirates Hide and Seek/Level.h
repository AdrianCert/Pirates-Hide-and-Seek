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
	struct Islace {
		bool Relevant = false;
		int Position = 0;
		int Rotation = 0;
	};
	struct State {
		Islace A;
		Islace B;
		Islace C;
		Islace D;
	};
	struct Level
	{
		int Request[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		State Solution;
		State Stash;
	};

	bool LoadLevel(int requested_lvl, Level* played_lvl);
	bool LoadLevelGenerated(Level* played_lvl, bool useMarkHint = true);
	int GetRequest(int var);
	int GetSolution(int var);
	int GetStorageLVL(int* v, int box);
	State* CopyState(State* A);
	///////////////////////////////////////////////////////////////////////////////////////////////////
	/// Funtion dedicated for drow request lvl                                                      ///
	///////////////////////////////////////////////////////////////////////////////////////////////////
	int GetCountDrowedFigures(Level* curentLVL);
	sf::RectangleShape** SetUpRequestLVL(sf::Vector2u* size_window, lvl::Level* CurentLevel, int& RequestCount, sf::Texture* FigureTextures[]);

}

#endif // !LEVEL_H

