#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
		LandMark,
		PirateShip,
		ExploratorShip,
		RobbedShip,
		Treasure,
		Island,
		Castle,
		Octoped,
		Shipwrecked,//Naufragiat
		COUNT
	};
}

struct SceneManager
{
	int CurentFrame = GameEnum::GameFrame::Intro;
	int LevelState = 0;
	sf::RenderWindow* RenderWindow = 0;
	cfg::dictionaty* Configurator = 0;
	sf::Music** djValy;
};

#endif
