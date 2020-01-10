#include "Game.h"
#include "Source.h"
using namespace sf;

bool Game(SceneManager* sceneManager) {

	//declarare texturi
	Texture t_Board,
			t_PirateShip,
			t_ExploratorShip,
			t_RobbedShip,
			t_Treasure,
			t_Island,
			t_Castle,
			t_Octoped,
			t_Shipwrecked;

	//incarcare texturi din fisiere
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
	Mouse mouse;
	//asezare plansa joc
	board.setOrigin(board.getSize().x/2, board.getSize().y / 2);
	board.setPosition(sceneManager->RenderWindow->getSize().x/2, sceneManager->RenderWindow->getSize().y/2);
	board.setTexture(&t_Board);

	//incarcare font
	sf::Font font;
	if (!font.loadFromFile("Resource/fontTitlu.ttf"))
		EXIT_FAILURE;

	Text b_Back;
	b_Back.setFont(font);
	b_Back.setString("back");
	b_Back.setCharacterSize(50);
	b_Back.setFillColor(sf::Color::Black);
	//resOriginText(b_Back);
	b_Back.setPosition(10, 10);


	while (sceneManager->CurentFrame == GameEnum::GameFrame::Game) {
		Event event;
		while (sceneManager->RenderWindow->pollEvent(event)) {
				
			if (isHover(b_Back, mouse) && Mouse::isButtonPressed(Mouse::Left))
				sceneManager->CurentFrame = GameEnum::GameFrame::Menu;

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
				default:
					break;
				}
			}
		}
		sceneManager->RenderWindow->clear(Color(255, 204, 102));
		sceneManager->RenderWindow->draw(board);
		sceneManager->RenderWindow->draw(b_Back);
		sceneManager->RenderWindow->display();
	}
	//Saving before game leave
	return true;
}
