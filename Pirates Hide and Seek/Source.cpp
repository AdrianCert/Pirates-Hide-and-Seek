#include "Source.h"

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
		|| !GetParm(configuration, "gameSSyle", gameSSyle))
		return EXIT_FAILURE;

	RenderWindow window(VideoMode(gameWidth, gameHeight), gameName, gameSSyle);

	SceneManager* sceneManager = new SceneManager();
	sceneManager->RenderWindow = &window;
	sceneManager->CurentFrame = GameEnum::GameFrame::Menu;
	sceneManager->Configurator = configuration;
	
	while (window.isOpen())
	{
		switch (sceneManager->CurentFrame)
		{
		case GameEnum::GameFrame::Intro:
			//code for Intro
			break;
		case GameEnum::GameFrame::Menu:
			Menu(sceneManager);
			break;
		case GameEnum::GameFrame::Game:
			//code for Intro
			break;
		case GameEnum::GameFrame::Option:
			//code for Intro
			break;
		case GameEnum::GameFrame::Exit:
			window.close();
			break;
		default:
			break;
		}
	}

	return EXIT_SUCCESS;
}