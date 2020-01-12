#include "Game.h"
#include "Source.h"
#include "Level.h"
using namespace sf;

bool Game(SceneManager* sceneManager) {
	Text Text_Back;
	Font font;
	Clock time;
	Mouse mouse;
	Texture t_Board,
			t_BoardEmpty,
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
		!t_LandMark.loadFromFile(		"Resource/t_board_mark.png")||
		!t_PirateShip.loadFromFile(		"Resource/t_board_items.png", IntRect(0,0,130,130))			||				 
		!t_ExploratorShip.loadFromFile(	"Resource/t_board_items.png", IntRect(0,130,130,130))		||				 
		!t_Octoped.loadFromFile(		"Resource/t_board_items.png", IntRect(0,260,130,130))		||				 
		!t_Island.loadFromFile(			"Resource/t_board_items.png", IntRect(130,130,130,130))		||				 
		!t_Castle.loadFromFile(			"Resource/t_board_items.png", IntRect(130,260,130,130))		||				 
		!t_Shipwrecked.loadFromFile(	"Resource/t_board_items.png", IntRect(130,0,130,130))		||				 
		!t_RobbedShip.loadFromFile(		"Resource/t_board_items.png", IntRect(260,0,130,130))		||				 
		!t_Treasure.loadFromFile(		"Resource/t_board_items.png", IntRect(260,130,130,130))		||				 
		!t_Islace_A.loadFromFile(		"Resource/t_board_islace.png", IntRect(0,0,500,500))		||
		!t_Islace_B.loadFromFile(		"Resource/t_board_islace.png", IntRect(500,0,500,500))		||
		!t_Islace_C.loadFromFile(		"Resource/t_board_islace.png", IntRect(0,500,500,500))		||
		!t_Islace_D.loadFromFile(		"Resource/t_board_islace.png", IntRect(500,500,500,500))	||				 
		!font.loadFromFile(				"Resource/fontTitlu.ttf"))
		return false;

	Vector2u size_window = sceneManager->RenderWindow->getSize();
	Vector2f size_islace = Vector2f(sceneManager->RenderWindow->getSize().y * 0.2, sceneManager->RenderWindow->getSize().y * 0.2);
	Vector2f size_items = Vector2f(100, 100);
	
	Texture* FigureTextures[9] = { &t_LandMark, &t_PirateShip, &t_ExploratorShip, &t_RobbedShip, &t_Treasure, &t_Island, &t_Castle, &t_Octoped, &t_Shipwrecked };

	RectangleShape MainBoard(Vector2f(size_window.y * 0.8, size_window.y * 0.8));
	
	RectangleShape Islace_A(size_islace);
	RectangleShape Islace_B(size_islace);
	RectangleShape Islace_C(size_islace);
	RectangleShape Islace_D(size_islace);

	RectangleShape* Islace[4] = { &Islace_A, &Islace_B, &Islace_C, &Islace_D };

	MainBoard.setOrigin(MainBoard.getSize().x/2, MainBoard.getSize().y / 2);
	MainBoard.setPosition(sceneManager->RenderWindow->getSize().x/2, sceneManager->RenderWindow->getSize().y/2);
	MainBoard.setTexture(&t_Board);
	
	Islace_A.setTexture(&t_Islace_A);
	SetOriginCenter(&Islace_A);
	Islace_B.setTexture(&t_Islace_B);
	SetOriginCenter(&Islace_B);
	Islace_C.setTexture(&t_Islace_C);
	SetOriginCenter(&Islace_C);
	Islace_D.setTexture(&t_Islace_D);
	SetOriginCenter(&Islace_D);

	Text_Back.setFont(font);
	Text_Back.setString("back");
	Text_Back.setCharacterSize(50);
	Text_Back.setFillColor(sf::Color::Black);
	Text_Back.setPosition(10, 10);

	lvl::Level* CurentLevel = new lvl::Level();
	if (!lvl::LoadLevel(sceneManager->LevelState, CurentLevel)) {
		lvl::LoadLevelGenerated(CurentLevel,true);
	}

	int RequestCount = lvl::GetCountDrowedFigures(CurentLevel);
	int RequestIndex = 0;

	RectangleShape** Request = new RectangleShape*[RequestCount];
	RectangleShape RequestBoard = RectangleShape(Vector2f(127,RequestCount*127));

	for (int i = 0; i < RequestCount; i++) {
		Request[i] = new RectangleShape(size_items);
	}
	RequestBoard.setFillColor( Color(92,194,208));
	RequestBoard.setOrigin(0, RequestBoard.getSize().y/2);
	RequestBoard.setPosition(0, size_window.y / 2);
	Request[RequestIndex]->setTexture(FigureTextures[0]);
	Request[RequestIndex]->setOrigin(50,50);
	Request[RequestIndex]->setRotation(90 * (CurentLevel->Request[0] - 1));
	for (int i = 1; i < 9; i++) {
		int tmp = CurentLevel->Request[i];
		while (tmp !=0)
		{
			RequestIndex++;
			Request[RequestIndex]->setTexture(FigureTextures[i]);
			Request[RequestIndex]->setOrigin(50,50);
			tmp--;
		}
	}
	int poz_X = 60, poz_Y = size_window.y/2 - RequestIndex/2 * 110 ;
	for (int i = 0; i < RequestCount; i++) {
		Request[i]->setPosition(Vector2f(poz_X,poz_Y));
		poz_Y += 120;
	}
	int xx = 0;
	while (sceneManager->CurentFrame == GameEnum::GameFrame::Game) {
		Event event;
		while (sceneManager->RenderWindow->pollEvent(event)) {
				
			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (isHover(Text_Back, mouse)) {
					sceneManager->CurentFrame = GameEnum::GameFrame::Menu;
				}
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
				default:
					break;
				}
			}
		}
		// stash; mutarile;
		//if (ifCompleted(LVL));
		sceneManager->RenderWindow->clear(Color(255, 204, 102));
		sceneManager->RenderWindow->draw(MainBoard);
		sceneManager->RenderWindow->draw(RequestBoard);
		sceneManager->RenderWindow->draw(Text_Back);
		DrowVector(sceneManager, Request, RequestCount);
		sceneManager->RenderWindow->display();
	}
	//Saving before game leave
	return true;
}
