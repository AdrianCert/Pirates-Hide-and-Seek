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
		for (int i = 0; i < 9; i++) {
			played_lvl->Request[i] = 0;
		}
		for (int i = 0; i < 8; i++) {
			played_lvl->Request[DescovededP[i]]++;
		}
		played_lvl->Request[0] = 0;
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
	State* CopyState(State* A) {
		State* B = new State();
		B->A.Position = A->A.Position;
		B->B.Position = A->B.Position;
		B->C.Position = A->C.Position;
		B->D.Position = A->D.Position;

		B->A.Relevant = A->A.Relevant;
		B->B.Relevant = A->B.Relevant;
		B->C.Relevant = A->C.Relevant;
		B->D.Relevant = A->D.Relevant;

		B->A.Rotation = A->A.Rotation;
		B->B.Rotation = A->B.Rotation;
		B->C.Rotation = A->C.Rotation;
		B->D.Rotation = A->D.Rotation;

		return B;
	}

	int GetCountDrowedFigures(Level* curentLVL) {
		int suma = curentLVL->Request[0] == 0 ? 0 : 1;
		for (int i = 1; i < 9; i++) {
			suma += curentLVL->Request[i];
		}
		return suma;
	}
	
	sf::RectangleShape** SetUpRequestLVL(sf::Vector2u* size_window, lvl::Level* CurentLevel, int& RequestCount, sf::Texture* FigureTextures[]) {
		RequestCount = lvl::GetCountDrowedFigures(CurentLevel) + 1;
		int size_item = 100;
		sf::RectangleShape** Request = new sf::RectangleShape * [RequestCount];

		// Crearea de Rectangle shapeuri
		Request[0] = new sf::RectangleShape(sf::Vector2f(127, (RequestCount - 1)* size_item + RequestCount * 10));
		for (int i = 1; i < RequestCount; i++) {
			Request[i] = new sf::RectangleShape(sf::Vector2f(100, 100));
		}

		// Umplerea cu texturi corespunzatoare
		int RequestIndex = 1;
		for (int i = 0; i < 9; i++) {
			if (i == 0) {
				if (CurentLevel->Request[0] != 0) {
					if (RequestIndex < RequestCount) {
						Request[RequestIndex]->setTexture(FigureTextures[0]);
						Request[RequestIndex]->setRotation(90 * (CurentLevel->Request[0] - 1));
						Request[RequestIndex]->setOrigin(50, 50);
						RequestIndex++;
					}
				}
			}
			else {
				int tmp = CurentLevel->Request[i];
				while (tmp != 0) {
					// urmatorul if acopera un worning care ne atentioneza cu o posibila depasire
					if (RequestIndex < RequestCount) {
						Request[RequestIndex]->setTexture(FigureTextures[i]);
						Request[RequestIndex]->setOrigin(50, 50);
					}
					RequestIndex++;
					tmp--;
				}
			}
		}

		// Pozitionarea Elementelor din vector
		int poz_X = 60, poz_Y = (*size_window).y / 2 - RequestIndex / 2 * 110;
		if (poz_Y < 60) poz_Y = 60;
		Request[0]->setFillColor(sf::Color(92, 194, 208));
		Request[0]->setPosition(poz_X - 60, poz_Y - 60);
		for (int i = 1; i < RequestCount; i++) {
			Request[i]->setPosition(sf::Vector2f(poz_X, poz_Y));
			poz_Y += size_item + 10;
		}

		return Request;
	}
}