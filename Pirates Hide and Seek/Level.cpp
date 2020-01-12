#include "Level.h"
#include "Helpers.h"
#include "GameMatrix.h"

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
		if (Request == -1) return false;
		int Solution_ENCODED = GetSolution(requested_lvl);
		int Solution[] = { 0, 0, 0, 0 };
		llvl::DecodeRequest(Request, played_lvl->Request);
		llvl::DecodeSolution(Request, Solution);
		played_lvl->Solution.A.Relevant = Solution[0] & 32;
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

	bool LoadLevelGenerated(Level* played_lvl, bool useMarkHint) {
		int Order[4];
		State* GeneratedSolution = new State();
		GeneratedSolution->A.Relevant = true;
		GeneratedSolution->B.Relevant = true;
		GeneratedSolution->C.Relevant = true;
		GeneratedSolution->D.Relevant = true;
		RandOrder(Order);
		GeneratedSolution->A.Position  = Order[0];
		GeneratedSolution->B.Position  = Order[1];
		GeneratedSolution->C.Position  = Order[2];
		GeneratedSolution->D.Position  = Order[3];
		
		srand((unsigned)time(NULL));
		GeneratedSolution->A.Rotation  = abs( rand() % 4);
		GeneratedSolution->B.Rotation  = abs( rand() % 4);
		GeneratedSolution->C.Rotation  = abs( rand() % 4);
		GeneratedSolution->D.Rotation  = abs( rand() % 4);

		int DescovededP[] = { 0, 0, 0 , 0, 0, 0, 0, 0 };
		GetUncoveredItems(GeneratedSolution, DescovededP);
		for (int i = 0; i < 9; i++)
			played_lvl->Request[i] = 0;
		for (int i = 0; i < 8; i++)
			played_lvl->Request[DescovededP[i]]++;
		if(useMarkHint) played_lvl->Request[0] = GeneratedSolution->A.Rotation + 1;

		played_lvl->Solution = *GeneratedSolution;

		return true;
	}

	int GetRequest(int var) {
		int capacity = GetStorageLVL(NULL, 0);
		if (var > capacity || var <= 0)
			return -1;
		int* v = new int[capacity];
		GetStorageLVL(v, 0);
		return v[var - 1];
	}

	int GetSolution(int var) {
		int capacity = GetStorageLVL(NULL,1);
		if (var > capacity || var <= 0)
			return -1;
		int *v = new int[capacity];
		GetStorageLVL(v,1);
		return v[var - 1];
	}

	int GetStorageLVL(int* v, int box) {
		int StorageLVL[] ={ 33,	16388,	258,	67108868 };
		int StorageSOL[] = { 33,	16388,	258,	67108868 };
		int CountLVL = (int) sizeof(StorageLVL) / sizeof(int);
		int CountSOL = (int) sizeof(StorageSOL) / sizeof(int);
		switch (box)
		{
		case 0:
			if (v != NULL) {
				for (int i = 0; i < CountLVL; i++) {
					v[i] = StorageLVL[i];
				}
			}
			return CountLVL;
			break;
		case 1:
			if (v != NULL) {
				for (int i = 0; i < CountLVL; i++) {
					v[i] = StorageLVL[i];
				}
			}
			return CountSOL;
			break;
		}
		return 0;
	}

	int GetCountDrowedFigures(Level* curentLVL) {
		int suma = curentLVL->Request[0] == 0 ? 0 : 1;
		for (int i = 1; i < 9; i++) {
			suma += curentLVL->Request[i];
		}
		return suma;
	}
}