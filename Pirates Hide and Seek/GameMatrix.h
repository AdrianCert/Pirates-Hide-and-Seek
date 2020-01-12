#include "GameVariable.h"
#include "Level.h"

#ifndef GAMEMATRIX_H
#define GAMEMATRIX_H

void getMatriceTabla(int v[6][6]);
void afisareMatrice();
void GetIslaceMat(int Islace, int V[3][3]);
void setRotation(int v[3][3], int r);
void CompareCadran(int piesa[3][3], int cadran[3][3], int s[2]);
void GetUncoveredItems(lvl::State* x, int* v);
#endif // !GAMEMATRIX_H

