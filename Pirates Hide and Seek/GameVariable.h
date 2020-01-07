#include <SFML/Graphics.hpp>
#include "Configuration.h"
#ifndef GAME_VAR_H
#define GAME_VAR_H

namespace GameEnum {

	enum GameFrame {
		Intro,
		Menu,
		Game,
		Option,
		Exit
	};

	enum Figures {
		PirateShip,
		ExploratorShip,
		RobbedShip,
		Treasure,
		Island,
		Castle,
		Octoped,
		Shipwrecked
	};
}

struct SceneManager
{
	int CurentFrame = GameEnum::GameFrame::Intro;
	sf::RenderWindow* RenderWindow = 0;
	cfg::dictionaty* Configurator = 0;
};

#endif
