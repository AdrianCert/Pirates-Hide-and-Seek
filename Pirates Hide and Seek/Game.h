#include "GameVariable.h"
#include "Level.h"
#ifndef GAME_H
#define GAME_H
struct HistoryGame {
	lvl::State* State;
	HistoryGame* Undo;
	int UndoLVL = 0;
};

void RecordState(HistoryGame*& CurentHistory, lvl::State* NewMove);
void UndoGame(HistoryGame*& CurentHistory);
bool Game(SceneManager* sceneManager);	

#endif // !GAME_H

