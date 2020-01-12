#include <SFML/Graphics.hpp>
#include "Configuration.h"
#ifndef GAME_VAR_H
#define GAME_VAR_H

namespace GameEnum {

	enum GameFrame {
		Intro,
		Menu,
		GameSelection,
		Game,
		Option,
		Exit,
		MaxFrame
	};

	enum Figures {
		LandMark,			//0
		PirateShip,			//1
		ExploratorShip,		//2
		RobbedShip,			//3
		Treasure,			//4
		Island,				//5
		Castle,				//6
		Octoped,			//7
		Shipwrecked,//Naufragiat
		COUNT
	};
}

struct SceneManager
{
	int CurentFrame = GameEnum::GameFrame::Intro;
	sf::RenderWindow* RenderWindow = 0;
	cfg::dictionaty* Configurator = 0;
};

#endif
