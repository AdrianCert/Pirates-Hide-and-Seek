#include "GameSelect.h"
using namespace sf;

bool Option(SceneManager* sceneManager) {
	Mouse mouse;
	Font font;

	

	Vector2u SizeWindow = sceneManager->RenderWindow->getSize();
	float SizeWindowX = sceneManager->RenderWindow->getSize().x;
	float SizeWindowY = sceneManager->RenderWindow->getSize().y;

	Texture t_button, t_cursor;
	if(!font.loadFromFile("Resource/fontTitlu.ttf"))
		return false;

	Sprite	B_NewGame(t_button),
		B_ContinueGame(t_button),
		B_CustomGame(t_button);

	Text	T_NewGame,
		T_ContinueGame,
		T_CustomGame;

	SetOriginCenter(&B_NewGame);
	SetOriginCenter(&B_ContinueGame);
	SetOriginCenter(&B_CustomGame);

	while (sceneManager->CurentFrame == GameEnum::GameFrame::GameSelection)
	{

		Event event;
		while (sceneManager->RenderWindow->pollEvent(event))
		{
			// Logica butoanelor
			if (Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (isHover(B_NewGame, mouse)) { // continue_campanie
					//sceneManager->LevelState = PlayerLvl;
					sceneManager->CurentFrame = GameEnum::GameFrame::Game;
				}
				if (isHover(B_ContinueGame, mouse)) { // get_new_random Game 
					sceneManager->LevelState = 0;
					sceneManager->CurentFrame = GameEnum::GameFrame::Game;
				}
				if (isHover(B_CustomGame, mouse)) // frame:: enter seed
					sceneManager->CurentFrame = GameEnum::GameFrame::Game;
			}

			switch (event.type)
			{
			case Event::Closed:
				sceneManager->CurentFrame = GameEnum::GameFrame::Exit;
				break;

			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::Escape:
					sceneManager->CurentFrame = GameEnum::GameFrame::Menu;
					break;
				case Keyboard::Enter:
					sceneManager->CurentFrame = GameEnum::GameFrame::Game;
					//sceneManager->LevelState = PlayerLvl;
					break;
				case Keyboard::O:
					sceneManager->CurentFrame = GameEnum::GameFrame::Option;
					break;
				default:
					break;
				}
			default:
				break;
			}
		}

		sceneManager->RenderWindow->clear(Color(255, 204, 102));
		sceneManager->RenderWindow->draw(B_NewGame);
		sceneManager->RenderWindow->draw(B_ContinueGame);
		sceneManager->RenderWindow->draw(B_CustomGame);
		sceneManager->RenderWindow->draw(T_NewGame);
		sceneManager->RenderWindow->draw(T_ContinueGame);
		sceneManager->RenderWindow->draw(T_CustomGame);
		sceneManager->RenderWindow->display();

	}
	return true;
}