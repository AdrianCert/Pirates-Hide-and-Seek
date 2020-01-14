// struct/hardcoder map 6x6 m
#include "GameMatrix.h"

void getMatriceTabla(int v[6][6])
{
	//cadran 1
	v[0][0] = 0;							v[0][1] = GameEnum::Shipwrecked;	v[0][2] = GameEnum::RobbedShip;
	v[1][0] = GameEnum::ExploratorShip;		v[1][1] = 0;						v[1][2] = GameEnum::Treasure;
	v[2][0] = GameEnum::Octoped;			v[2][1] = 0;						v[2][2] = 0;
	//cadran 3
	v[3][0] = GameEnum::Shipwrecked;		v[3][1] = GameEnum::RobbedShip;		v[3][2] = GameEnum::PirateShip;
	v[4][0] = GameEnum::ExploratorShip;		v[4][1] = GameEnum::Treasure;		v[4][2] = 0;
	v[5][0] = GameEnum::PirateShip;			v[5][1] = GameEnum::Castle;			v[5][2] = GameEnum::Island;
	//cadran 2
	v[0][3] = GameEnum::Shipwrecked;		v[0][4] = GameEnum::Castle;			v[0][5] = 0;
	v[1][3] = 0;							v[1][4] = GameEnum::ExploratorShip; v[1][5] = GameEnum::Treasure;
	v[2][3] = GameEnum::Octoped;			v[2][4] = GameEnum::PirateShip;		v[2][5] = 0;
	//cadran 4
	v[3][3] = 0;							v[3][4] = 0;						v[3][5] = 0;
	v[4][3] = GameEnum::Castle;				v[4][4] = GameEnum::Shipwrecked;	v[4][5] = GameEnum::Island;
	v[5][3] = GameEnum::ExploratorShip;		v[5][4] = GameEnum::PirateShip;		v[5][5] = GameEnum::Treasure;
	
}

void afisareMatrice()
{
	//int v[6][6];
	int c[3][3];
	//getMatriceTabla(v);
	GetIslaceMat(1,c);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			std::cout << c[i][j] << ' ';
		std::cout << std::endl;
	}
	setRotation(c,1);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
 			std::cout << c[i][j] << ' ';
		std::cout << std::endl;
	}
	
}

void GetIslaceMat(int Islace, int v[3][3]) {
	
	switch (Islace % 4)
	{
	//PIESA A
	case 0:
		v[0][0] = 1; v[0][1] = 1; v[0][2] = 0;
		v[1][0] = 1; v[1][1] = 1; v[1][2] = 1;
		v[2][0] = 1; v[2][1] = 0; v[2][2] = 1;
		break;
	//PIESA B
	case 1:
		v[0][0] = 1; v[0][1] = 1; v[0][2] = 1;
		v[1][0] = 1; v[1][1] = 0; v[1][2] = 1;
		v[2][0] = 1; v[2][1] = 0; v[2][2] = 1;
		break;
	//PIESA C
	case 2:
		v[0][0] = 1; v[0][1] = 0; v[0][2] = 1;
		v[1][0] = 1; v[1][1] = 1; v[1][2] = 1;
		v[2][0] = 1; v[2][1] = 0; v[2][2] = 1;
		break;
	//PIESA D
	case 3:
		v[0][0] = 1; v[0][1] = 1; v[0][2] = 0;
		v[1][0] = 1; v[1][1] = 1; v[1][2] = 1;
		v[2][0] = 0; v[2][1] = 1; v[2][2] = 1;
		break;

	default:
		break;
	}


}void GetCadran(int pos, int v[3][3]) {
	
	switch (pos % 4)
	{
	case 0:
		v[0][0] = 0;							v[0][1] = GameEnum::Shipwrecked;	v[0][2] = GameEnum::RobbedShip;
		v[1][0] = GameEnum::ExploratorShip;		v[1][1] = 0;						v[1][2] = GameEnum::Treasure;
		v[2][0] = GameEnum::Octoped;			v[2][1] = 0;						v[2][2] = 0;
		break;
	case 1:
		v[0][0] = GameEnum::Shipwrecked;		v[0][1] = GameEnum::Castle;			v[0][2] = 0;
		v[1][0] = 0;							v[1][1] = GameEnum::ExploratorShip; v[1][2] = GameEnum::Treasure;
		v[2][0] = GameEnum::Octoped;			v[2][1] = GameEnum::PirateShip;		v[2][2] = 0;
		break;
	case 2:
		v[0][0] = GameEnum::Shipwrecked;		v[0][1] = GameEnum::RobbedShip;		v[0][2] = GameEnum::PirateShip;
		v[1][0] = GameEnum::ExploratorShip;		v[1][1] = GameEnum::Treasure;		v[1][2] = 0;
		v[2][0] = GameEnum::PirateShip;			v[2][1] = GameEnum::Castle;			v[2][2] = GameEnum::Island;
		break;
	case 3:
		v[0][0] = 0;							v[0][1] = 0;						v[0][2] = 0;
		v[1][0] = GameEnum::Castle;				v[1][1] = GameEnum::Shipwrecked;	v[1][2] = GameEnum::Island;
		v[2][0] = GameEnum::ExploratorShip;		v[2][1] = GameEnum::PirateShip;		v[2][2] = GameEnum::Treasure;
		break;

	default:
		break;
	}
}

void setRotation(int v[3][3], int r)
{
	r = r % 4;
	int aux;
	if (r == 0)
		return;	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j > i)
			{
				aux = v[i][3-j-1];
				v[i][3-j-1] = v[j][i];
				v[j][i] = aux;
			}
		}
	}	
	setRotation(v, r-1);
	
}

//returneaza cele 2 piese descoperite din cadran
void CompareCadran(int piesa[3][3], int cadran[3][3], int s[2])
{
	int contor = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (piesa[i][j] == 0)
				s[contor++] = cadran[i][j];
}

void GetUncoveredItems(lvl::State* x, int* v)
{
	
	//Piesa A
	if (x->A.Relevant)
	{
		int pieseCadran[2];
		int piesa[3][3];
		int cadran[3][3];
		GetIslaceMat(0, piesa);
		setRotation(piesa, x->A.Rotation);
		GetCadran(x->A.Position, cadran);
		CompareCadran(piesa, cadran, pieseCadran);
		v[0] = pieseCadran[0];
		v[1] = pieseCadran[1];

	}

	//Piesa B
	if (x->B.Relevant)
	{
		int pieseCadran[2];
		int piesa[3][3];
		int cadran[3][3];
		GetIslaceMat(1, piesa);
		setRotation(piesa, x->B.Rotation);
		GetCadran(x->B.Position, cadran);
		CompareCadran(piesa, cadran, pieseCadran);
		v[2] = pieseCadran[0];
		v[3] = pieseCadran[1];

	}

	//Piesa C
	if (x->C.Relevant)
	{
		int pieseCadran[2];
		int piesa[3][3];
		int cadran[3][3];
		GetIslaceMat(2, piesa);
		setRotation(piesa, x->C.Rotation);
		GetCadran(x->C.Position, cadran);
		CompareCadran(piesa, cadran, pieseCadran);
		v[4] = pieseCadran[0];
		v[5] = pieseCadran[1];

	}

	//Piesa D
	if (x->D.Relevant)
	{
		int pieseCadran[2];
		int piesa[3][3];
		int cadran[3][3];
		GetIslaceMat(3, piesa);
		setRotation(piesa, x->D.Rotation);
		GetCadran(x->D.Position, cadran);
		CompareCadran(piesa, cadran, pieseCadran);
		v[6] = pieseCadran[0];
		v[7] = pieseCadran[1];

	}
}
