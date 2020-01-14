#include "Switch.h";

int VerPoz(int newPoz, lvl::State* state)
{
	//daca pe casuta se afla aceeasi piesa 
	//returneaza numarul aceleasi piese
	if (state->A.Relevant && state->A.Position == newPoz)
		return 0;
	if (state->B.Relevant && state->B.Position == newPoz)
		return 1;
	if (state->C.Relevant && state->C.Position == newPoz)
		return 2;
	if (state->D.Relevant && state->D.Position == newPoz)
		return 3;
	//daca a ajuns aici atunci nu se afla nimic in casuta
	return -1;
}


//verifica daca o piesa este sau nu pe tabla
bool isRelevant(int islace, lvl::State* state)
{
	switch (islace)
	{
	case 0:
		return state->A.Relevant;
	case 1:
		return state->B.Relevant;
	case 2:
		return state->C.Relevant;
	case 3:
		return state->D.Relevant;
	default:
		break;
	}
}

void GetMove(int islace, int newPoz, lvl::State* state)
{
	int isPosition; //retine daca in pozitie se afla sau nu ceva
	isPosition = VerPoz(newPoz, state);
	bool relevance; //retine daca piesa este sau nu pe tabla
	relevance = isRelevant(islace, state);

	switch (islace)
	{
	case 0:
		if (isRelevant(islace, state) == false && newPoz == -1)
			return ;
	case 1:
		if (isRelevant(islace, state) == false && newPoz == -1)
			return ;
	case 2:
		if (isRelevant(islace, state) == false && newPoz == -1)
			return ;
	case 3:
		if (isRelevant(islace, state) == false && newPoz == -1)
			return ;

	default:
		break;
	}

	switch (islace)
	{
	case 0:
		if (isRelevant(islace, state) == false && newPoz != -1 && isPosition == -1)
		{
			state->A.Position = newPoz;
			state->A.Relevant = true;
			
		}
	case 1:
		if (isRelevant(islace, state) == false && newPoz != -1 && isPosition == -1)
		{
			state->B.Position = newPoz;
			state->B.Relevant = true;
			
		}
	case 2:
		if (isRelevant(islace, state) == false && newPoz != -1 && isPosition == -1)
		{
			state->C.Position = newPoz;
			state->C.Relevant = true;
			
		}
	case 3:
		if (isRelevant(islace, state) == false && newPoz != -1 && isPosition == -1)
		{
			state->D.Position = newPoz;
			state->D.Relevant = true;
			
		}
	default:
		break;
	}

	switch (islace)
	{
	case 0:
		if (isRelevant(islace, state) == true && newPoz == -1)
		{
			state->A.Position = newPoz;
			state->A.Relevant = false;

		}
	case 1:
		if (isRelevant(islace, state) == true && newPoz == -1)
		{
			state->B.Position = newPoz;
			state->B.Relevant = false;

		}
	case 2:
		if (isRelevant(islace, state) == true && newPoz == -1)
		{
			state->C.Position = newPoz;
			state->C.Relevant = false;

		}
	case 3:
		if (isRelevant(islace, state) == true && newPoz == -1)
		{
			state->D.Position = newPoz;
			state->D.Relevant = false;

		}
	default:
		break;
	}

	///////////////////////////////////////////////////////////////////////
	//																     //
	//	trebuie verificate cazurile:									 //
	//	-daca rel == false si newPoz == -1								 //
	//				nu se intampla nimic								 //
	//	-daca rel == false si newPoz != -1								 //	
	//				-daca newPoz este gol								 //				
	//					state.islace(A, B, C, D).position = newPoz		 //
	//				-daca newPoz nu este gol							 //
	//					state.pozIslace(A, B, C, D).position = -1		 //
	//					state.islace(A, B, C, D).position = newPoz		 //
	//	-daca rel == true si newPoz == -1								 //
	//				state.islace(A, B, C, D).position = -1				 //
	//	-daca rel == true si newPoz != -1								 //
	//			interschimb pozitiile pieselor							 //
	//				aux = state.islace.position						     //
	//				state.islace.position = state.pozIslace.position	 //
	//				state.poZIslace.position = aux						 //
	//																	 //
	//				PLUS INCA NISTE MICI CONDITII LA FIECARE CAZ		 //
	//								PROBABIL							 //
	///////////////////////////////////////////////////////////////////////
}



