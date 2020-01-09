#include "Level.h"

namespace llvl {
	
	int coding_request(int* var) {
		int game_req = *var;
		for (int i = 1; i <= 8; i++) {
			game_req = game_req << 3;
			game_req += *(var + i) & 3;
		}
		int v[9];
		return game_req;
	}

	void decode_request(int var,int* x) {
		for (int i = 0 ; i < 9; i++) {
			*(x + 8 - i) = var & 3;
			var = var >> 3;
		}
	}
}