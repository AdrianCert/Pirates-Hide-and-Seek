#include "Source.h"
#include "Level.h"

using namespace sf;

int main()
{
	int gameWidth, gameHeight, gameSSyle;

	std::string gameName;
	cfg::dictionaty* configuration = new cfg::dictionaty();
	if (!ReadConfiguration(configuration, "Resource/ConfigureFile.txt")) return EXIT_FAILURE;
	if (!GetParm(configuration, "gameWidth", gameWidth)
		|| !GetParm(configuration, "gameHeight", gameHeight)
		|| !GetParm(configuration, "gameName", gameName)
		|| !GetParm(configuration, "gameSSyle", gameSSyle)
		)
		return EXIT_FAILURE;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::Music music1, music2, music3, music4;
	if (!music1.openFromFile("Resource/song1.ogg") ||
		!music2.openFromFile("Resource/song2.ogg") ||
		!music3.openFromFile("Resource/song3.ogg") ||
		!music4.openFromFile("Resource/song4.ogg") )
		return EXIT_FAILURE; // error
	

	sf::Music* music[4] = {&music1, &music2, &music3, &music4 };
	int* user_settings = new int[GameEnum::OptionField::OptionFieldCount];
	GetParm(configuration, "music", user_settings[GameEnum::OptionField::Music]);
	GetParm(configuration, "sfx", user_settings[GameEnum::OptionField::SFX]);
	
	RenderWindow window(VideoMode(gameWidth, gameHeight), gameName, gameSSyle, settings);
	window.setFramerateLimit(120);

	SceneManager* sceneManager = new SceneManager();
	sceneManager->RenderWindow = &window;
	sceneManager->CurentFrame = GameEnum::GameFrame::Intro;
	sceneManager->Configurator = configuration;
	sceneManager->LevelState = 0;
	sceneManager->djValy = music;
	sceneManager->Settings = user_settings;

  while (window.isOpen())
	{
		bool gameContinue = false;
		switch (sceneManager->CurentFrame)
		{
		case GameEnum::GameFrame::Intro:
			gameContinue = Intro(sceneManager);
			break;
		case GameEnum::GameFrame::GameSelection:
			gameContinue = GameSelect(sceneManager);
			break;
		case GameEnum::GameFrame::Menu:
			gameContinue = Menu(sceneManager);
			break;
		case GameEnum::GameFrame::Game:
			gameContinue = Game(sceneManager);
			break;
		case GameEnum::GameFrame::Option:
			gameContinue = Option(sceneManager);
			break;
		case GameEnum::GameFrame::Exit:
			window.close();
			break;
		case GameEnum::GameFrame::HowToPlay:
			gameContinue = howto(sceneManager);
			break;
		default:
			break;
		}
		if(!gameContinue) sceneManager->CurentFrame = GameEnum::GameFrame::Exit;
		
	}

	

	return EXIT_SUCCESS;
}