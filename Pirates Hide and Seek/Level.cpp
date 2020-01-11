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
		int StorageLVL[] = {	33,	16388,	258,	67108868	};
		int CountLVL = (int) sizeof(StorageLVL)/sizeof(int);
		if (var > CountLVL)
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