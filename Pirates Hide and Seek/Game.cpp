#include "Game.h"
#include "Source.h"
using namespace sf;

bool Game(SceneManager* sceneManager) {

	Texture t_Board,
			t_LandMark,
			t_PirateShip,
			t_ExploratorShip,
			t_RobbedShip,
			t_Treasure,
			t_Island,
			t_Castle,
			t_Octoped,
			t_Shipwrecked,
			t_Islace_A,
			t_Islace_B,
			t_Islace_C,
			t_Islace_D;

	if (!t_Board.loadFromFile(			"Resource/t_board.png")		||
		!t_LandMark.loadFromFile(		"Resource/t_board_mark.png")	||
		!t_PirateShip.loadFromFile(		"Resource/t_board_items.png", IntRect(0,0,130,130))			||				 
		!t_ExploratorShip.loadFromFile(	"Resource/t_board_items.png", IntRect(0,130,130,260))		||				 
		!t_Octoped.loadFromFile(		"Resource/t_board_items.png", IntRect(0,260,130,390))		||				 
		!t_Island.loadFromFile(			"Resource/t_board_items.png", IntRect(130,130,260,260))		||				 
		!t_Castle.loadFromFile(			"Resource/t_board_items.png", IntRect(130,260,260,390))		||				 
		!t_Shipwrecked.loadFromFile(	"Resource/t_board_items.png", IntRect(130,0,260,130))		||				 
		!t_RobbedShip.loadFromFile(		"Resource/t_board_items.png", IntRect(260,0,390,130))		||				 
		!t_Treasure.loadFromFile(		"Resource/t_board_items.png", IntRect(260,130,390,260))		||				 
		!t_Islace_A.loadFromFile(		"Resource/t_board_islace.png", IntRect(0,0,500,500))		||
		!t_Islace_B.loadFromFile(		"Resource/t_board_islace.png", IntRect(500,0,1000,500))		||
		!t_Islace_C.loadFromFile(		"Resource/t_board_islace.png", IntRect(0,500,500,1000))		||
		!t_Islace_D.loadFromFile(		"Resource/t_board_islace.png", IntRect(500,500,1000,1000))	)				 
		return false;

	Vector2f size_window = Vector2f(sceneManager->RenderWindow->getSize().y * 0.8, sceneManager->RenderWindow->getSize().y * 0.8);
	Vector2f size_islace = Vector2f(sceneManager->RenderWindow->getSize().y * 0.2, sceneManager->RenderWindow->getSize().y * 0.2);
	Vector2f size_items = Vector2f(100, 100);

	RectangleShape board(size_window);
	RectangleShape LandMark(size_items);
	RectangleShape PirateShip(size_items);
	RectangleShape ExploratorShip(size_items);
	RectangleShape RobbedShip(size_items);
	RectangleShape Treasure(size_items);
	RectangleShape Island(size_items);
	RectangleShape Castle(size_items);
	RectangleShape Octoped(size_items);
	RectangleShape Shipwrecked(size_items);
	
	RectangleShape Islace_A(size_islace);
	RectangleShape Islace_B(size_islace);
	RectangleShape Islace_C(size_islace);
	RectangleShape Islace_D(size_islace);

	
	Clock time;
	Mouse mouse;

	board.setOrigin(board.getSize().x/2, board.getSize().y / 2);
	board.setPosition(sceneManager->RenderWindow->getSize().x/2, sceneManager->RenderWindow->getSize().y/2);
	board.setTexture(&t_Board);

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
