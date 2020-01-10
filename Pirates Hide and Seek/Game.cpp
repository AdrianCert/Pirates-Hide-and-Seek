#include "Game.h"
#include "Menu.h"
using namespace sf;

bool Game(SceneManager* sceneManager) {

	
	Texture t_Board,
			t_PirateShip,
			t_ExploratorShip,
			t_RobbedShip,
			t_Treasure,
			t_Island,
			t_Castle,
			t_Octoped,
			t_Shipwrecked;
	if (!t_Board.loadFromFile(			"Resource/_board.png") ||												 
		!t_PirateShip.loadFromFile(		"Resource/_board_items.png", IntRect(0,0,130,130))		||				 
		!t_ExploratorShip.loadFromFile(	"Resource/_board_items.png", IntRect(0,130,130,260))	||				 
		!t_Octoped.loadFromFile(		"Resource/_board_items.png", IntRect(0,260,130,390))	||				 
		!t_Island.loadFromFile(			"Resource/_board_items.png", IntRect(130,130,260,260))	||				 
		!t_Castle.loadFromFile(			"Resource/_board_items.png", IntRect(130,260,260,390))	||				 
		!t_Shipwrecked.loadFromFile(	"Resource/_board_items.png", IntRect(130,0,260,130))	||				 
		!t_RobbedShip.loadFromFile(		"Resource/_board_items.png", IntRect(260,0,390,130))	||				 
		!t_Treasure.loadFromFile(		"Resource/_board_items.png", IntRect(260,130,390,260))	)				 
		return false;

	RectangleShape board(sf::Vector2f(sceneManager->RenderWindow->getSize().y * 0.8, sceneManager->RenderWindow->getSize().y * 0.8));
	
	Clock time;

	board.setOrigin(board.getSize().x/2, board.getSize().y / 2);
	board.setPosition(sceneManager->RenderWindow->getSize().x/2, sceneManager->RenderWindow->getSize().y/2);
	board.setTexture(&t_Board);

	Mouse mouse;
	Sprite shiot(t_PirateShip);
	shiot.setScale(.75, .75);
	shiot.setPosition(sceneManager->RenderWindow->getSize().x / 2, sceneManager->RenderWindow->getSize().y / 2);
	
	while (sceneManager->CurentFrame == GameEnum::GameFrame::Game) {
		Event event;
		while (sceneManager->RenderWindow->pollEvent(event)) {
			
			if (isHover(shiot, mouse) &&
				Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sceneManager->CurentFrame = GameEnum::GameFrame::Menu;
				break;
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
				case Keyboard::F10:
					sceneManager->RenderWindow->create(VideoMode(std::stoi(cfg::GetElement(sceneManager->Configurator,"gameWidth")) - 500, std::stoi(cfg::GetElement(sceneManager->Configurator, "gameHeight")) - 500), "Pirates Hide and Seek", Style::Close);
					return true;
					break;
				case Keyboard::F11:
					sceneManager->RenderWindow->create(VideoMode(std::stoi(cfg::GetElement(sceneManager->Configurator, "gameWidth")), std::stoi(cfg::GetElement(sceneManager->Configurator, "gameHeight"))), "Pirates Hide and Seek", Style::Close | Style::Fullscreen);
					return true;
					break;
				default:
					break;
				}
			}
		}
		sceneManager->RenderWindow->clear(Color(255, 204, 102));
		sceneManager->RenderWindow->draw(board);
		sceneManager->RenderWindow->draw(shiot);
		sceneManager->RenderWindow->display();
	}
	//Saving before game leave
	return true;
}
