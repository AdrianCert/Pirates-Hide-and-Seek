#include "GameSelect.h"
using namespace sf;

bool GameSelect(SceneManager* sceneManager) {
	Mouse mouse;
	Font font;
	Vector2u SizeWindow  = sceneManager->RenderWindow->getSize();
	float SizeWindowX = sceneManager->RenderWindow->getSize().x;
	float SizeWindowY = sceneManager->RenderWindow->getSize().y;

	float Ratio = SizeWindowY / SizeWindowX;
		//SizeWindow.y / SizeWindow.x;
		//(float)sceneManager->RenderWindow->getSize().y / (float)sceneManager->RenderWindow->getSize().x;

	Texture t_button, t_cursor;
	if (!t_button.loadFromFile(	"Resource/t_butonjoc.png")	||
		!t_cursor.loadFromFile(	"Resource/t_cursor.png")	||
		!font.loadFromFile		("Resource/fontTitlu.ttf")	)
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

	T_NewGame.setFont(font);
	T_NewGame.setString("New Game");
	T_NewGame.setFillColor(Color::Black);
	T_NewGame.setCharacterSize(46);
	//T_NewGame.setScale(Ratio, Ratio);
	B_NewGame.setScale(Ratio, Ratio);
	SetOriginCenter(&T_NewGame);
	T_NewGame.setPosition(SizeWindow.x / 2, SizeWindow.y / 2 - 300 * Ratio);
	B_NewGame.setPosition(SizeWindow.x / 2, SizeWindow.y / 2 - 300 * Ratio);

	T_ContinueGame.setFont(font);
	T_ContinueGame.setString("Continue Game");
	T_ContinueGame.setFillColor(Color::Black);
	T_ContinueGame.setCharacterSize(46);
	//T_ContinueGame.setScale(Ratio, Ratio);
	B_ContinueGame.setScale(Ratio, Ratio);
	SetOriginCenter(&T_ContinueGame);
	T_ContinueGame.setPosition(SizeWindow.x / 2, SizeWindow.y / 2 );
	B_ContinueGame.setPosition(SizeWindow.x / 2, SizeWindow.y / 2 );

	T_CustomGame.setFont(font);
	T_CustomGame.setString("Quick Game");
	T_CustomGame.setFillColor(Color::Black);
	T_CustomGame.setCharacterSize(46);
	//T_CustomGame.setScale(Ratio, Ratio);
	B_CustomGame.setScale(Ratio, Ratio);
	SetOriginCenter(&T_CustomGame);
	T_CustomGame.setPosition(SizeWindow.x / 2, SizeWindow.y / 2 + 300 * Ratio);
	B_CustomGame.setPosition(SizeWindow.x / 2, SizeWindow.y / 2 + 300 * Ratio);

	while (sceneManager->CurentFrame == GameEnum::GameFrame::GameSelection)
	{

		Event event;
		while (sceneManager->RenderWindow->pollEvent(event))
		{
			// Logica butoanelor
			if (Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (isHover(B_NewGame, mouse)) // get lvl by random from storage
					sceneManager->CurentFrame = GameEnum::GameFrame::Game;
				if (isHover(B_ContinueGame, mouse)) // swich on lvl selector 
					sceneManager->CurentFrame = GameEnum::GameFrame::Game;
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
					sceneManager->CurentFrame = GameEnum::GameFrame::Exit;
					break;
				case Keyboard::Enter:
					sceneManager->CurentFrame = GameEnum::GameFrame::Game;
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