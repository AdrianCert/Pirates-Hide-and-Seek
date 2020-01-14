#include "GameVariable.h"
#include "Level.h"

#ifndef SWITCH_H
#define SWITCH_H

int VerPoz(int newPoz, lvl::State* state);
bool isRelevant(int islace, lvl::State* state);
void GetMove(int islace, int newPoz, lvl::State* state);

#endif // !SWITCH_H
