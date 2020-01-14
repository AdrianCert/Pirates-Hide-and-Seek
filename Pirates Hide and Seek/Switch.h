#include "GameVariable.h"
#include "Level.h"

#ifndef SWITCH_H
#define SWITCH_H

int VerPoz(int newPoz, lvl::State* state);
bool isRelevant(int islace, lvl::State* state);
void GetMove(int islace, int newPoz, lvl::State* state);
void GetRotation(int islace, lvl::State* state);
bool CompareState(lvl::State* a, lvl::State* b);
#endif // !SWITCH_H
