#include "Level.h"

namespace llvl {
	
	int CodingRequest(int* var) {
		int game_req = 0;
		for (int i = 1; i <= GameEnum::Figures::COUNT; i++) {
			game_req = game_req << 3;
			game_req += *(var + GameEnum::Figures::COUNT - i) & 7;
		}
		return game_req;
	}

	void DecodeRequest(int var,int* x) {
		for (int i = 0 ; i < GameEnum::Figures::COUNT; i++) {
			int tmp = var & 7;
			*(x + i) = var & 7;
			var = var >> 3;
		}
	}

	int CodingSolution(int* var) {
		int game_req = *var;
		for (int i = 0; i < 4; i++) {
			game_req = game_req << 5;
			game_req += *(var + i) & 63;
		}
		return game_req;
	}
	void DecodeSolution(int var, int* x) {
		for (int i = 0; i < 4; i++) {
			*(x + 3 - i) = var & 63;
			var = var >> 5;
		}
	}
}

namespace lvl {

	bool LoadLevel(int requested_lvl, Level* played_lvl) {
		int Request = GetRequest(requested_lvl);
		if (Request == -1)
			return false;
		int Solution[] = { 0,0,0,0 };
		llvl::DecodeRequest(Request, played_lvl->Request);
		llvl::DecodeSolution(Request, Solution);
		played_lvl->Solution.A.Relevant = (bool)Solution[0] & 32;
		played_lvl->Solution.A.Position = Solution[0] & 12;
		played_lvl->Solution.A.Rotation = Solution[0] & 3;

		played_lvl->Solution.B.Relevant = (bool)Solution[0] & 32;
		played_lvl->Solution.B.Position = Solution[0] & 12;
		played_lvl->Solution.B.Rotation = Solution[0] & 3;

		played_lvl->Solution.C.Relevant = (bool)Solution[0] & 32;
		played_lvl->Solution.C.Position = Solution[0] & 12;
		played_lvl->Solution.C.Rotation = Solution[0] & 3;

		played_lvl->Solution.D.Relevant = (bool)Solution[0] & 32;
		played_lvl->Solution.D.Position = Solution[0] & 12;
		played_lvl->Solution.D.Rotation = Solution[0] & 3;
		return true;
	}
	bool LoadLevelSeed(int seed, int* n) {
		return true;
	}
	int GetRequest(int var) {
		int StorageLVL[] = { 33,		//1
							16388,		//2
							258,		//3
							67108868,	//4
							705,		//5
							2097347,	//6
							33817601,	//7
							262339,		//8
							154,		//9
							263297,		//10
							37748803,	//11
							20975627,	//12
							40964,		//13
							50397186,	//14
							2392580,	//15
							274434,		//16
							4104,		//17
							50331656,	//18
							32896,		//19
							33620032,	//20
							2105352,	//21
							8216,		//22
							2102288,	//23
							267392,		//24
							2098264,	//25
							37120,		//26
							274448,		//27
							2359312,	//28
							2106376,	//29
							4312,		//30
							50335768,	//31
							18874456,	//32
							16810000,	//33
							2130632,	//34
							2363400,	//35
							17301528,	//36
							18944576,	//37
							2101376,	//38
							2629760,	//39
							33587224,	//40
							33562624,	//41
							32912,		//42
							2392584,	//43
							2634240,	//44
							2363408,	//45
							528512,		//46
							17302016,	//47
							34079296,	//48
							144,		//49
							266368,		//50
							35652104,	//51
							17043456,	//52
							295040,		//53
							19136584,	//54
							36175888,	//55
							18911232,	//56
							532496,		//57
							18911744,	//58
							19136528,	//59
							270400	};	//60
		int CountLVL = (int) sizeof(StorageLVL)/sizeof(int);
		if (var > CountLVL || var == 0)
			return -1;
		return StorageLVL[var - 1];
	}
	// temporary storage
	int GetSolutuon(int var) {
		int StorageLVL[] = { 33,	16388,	258,	67108868 };
		int CountLVL = (int) sizeof(StorageLVL) / sizeof(int);
		if (var > CountLVL)
			return -1;
		return StorageLVL[var - 1];
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////
	/// Funtion dedicated for drow request lvl                                                      ///
	///////////////////////////////////////////////////////////////////////////////////////////////////
	int GetCountDrowedFigures(Level* curentLVL) {
		int suma = curentLVL->Request[0] == 0 ? 0 : 1;
		for (int i = 1; i < 9; i++) {
			suma += curentLVL->Request[i];
		}
		return suma;
	}
}