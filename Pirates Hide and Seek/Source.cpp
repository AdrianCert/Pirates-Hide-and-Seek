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
	sceneManager->CurentFrame = GameEnum::GameFrame::Intro;
	sceneManager->Configurator = configuration;
	
	while (window.isOpen())
	{
		bool gameContinue = false;
		switch (sceneManager->CurentFrame)
		{
		case GameEnum::GameFrame::Intro:
			gameContinue = Intro(sceneManager);
			break;
		case GameEnum::GameFrame::Menu:
			gameContinue = Menu(sceneManager);
			break;
		case GameEnum::GameFrame::Game:
			gameContinue = Game(sceneManager);
			break;
		case GameEnum::GameFrame::Option:
			break;
		case GameEnum::GameFrame::Exit:
			window.close();
			break;
		default:
			break;
		}
		if(!gameContinue) sceneManager->CurentFrame = GameEnum::GameFrame::Exit;
	}

	return EXIT_SUCCESS;
}