#include "Game.h"
#include "Source.h"
#include "Level.h"
using namespace sf;

struct HistoryGame {
	lvl::State* State = 0;
	HistoryGame* Undo = 0;
	int UndoLVL = 0;
};

void RecordState(HistoryGame* &CurentHistory, lvl::State* NewMove) {
	HistoryGame* HistoryRecord = new HistoryGame();
	HistoryRecord->State = NewMove;
	HistoryRecord->Undo = CurentHistory;
	HistoryRecord->UndoLVL = CurentHistory->UndoLVL + 1;
	CurentHistory = HistoryRecord;
}

void UndoGame(HistoryGame* &CurentHistory) {
	if (CurentHistory->Undo != NULL) {
		HistoryGame* NOW = CurentHistory;
		HistoryGame* NEW = CurentHistory->Undo;
		free(NOW->State);
		free(NOW);
		CurentHistory = NEW;
	}
}

bool Game(SceneManager* sceneManager) {
	Text T_Menu, T_Undo, T_Hint;
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
	
	Texture* FigureTextures[9] = { &t_LandMark, &t_PirateShip, &t_ExploratorShip, &t_RobbedShip, &t_Treasure, &t_Island, &t_Castle, &t_Octoped, &t_Shipwrecked };

	lvl::Level* CurentLevel = new lvl::Level();
	if (!lvl::LoadLevel(sceneManager->LevelState, CurentLevel)) {
		int userAnswer = UInterogationWindowForConfirm(sceneManager->RenderWindow,"Do you wont mark hint?");
		if (userAnswer == -1) {
			sceneManager->CurentFrame = GameEnum::GameFrame::Menu;
			return true;
		}
		if(userAnswer == 0)
			lvl::LoadLevelGenerated(CurentLevel,false);
		if(userAnswer == 1)
			lvl::LoadLevelGenerated(CurentLevel,true);
	}

	lvl::State* CurentState = new lvl::State();
	HistoryGame* CurentHistory = new HistoryGame();
	CurentHistory->State = CurentState;
	CurentHistory->Undo = NULL;

	Vector2u size_window = sceneManager->RenderWindow->getSize();
	Vector2f size_islace = Vector2f(sceneManager->RenderWindow->getSize().y * 0.2, sceneManager->RenderWindow->getSize().y * 0.2);
	Vector2f size_items = Vector2f(100, 100);
	int RequestCount = 0;
	

	RectangleShape MainBoard(Vector2f(size_window.y * 0.8, size_window.y * 0.8));
	RectangleShape Islace_A(size_islace);
	RectangleShape Islace_B(size_islace);
	RectangleShape Islace_C(size_islace);
	RectangleShape Islace_D(size_islace);
	RectangleShape* Islace[4] = { &Islace_A, &Islace_B, &Islace_C, &Islace_D };
	sf::RectangleShape** Request = lvl::SetUpRequestLVL(&size_window, CurentLevel, RequestCount, FigureTextures);

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

	T_Menu.setFont(font);
	T_Menu.setString("menu");
	T_Menu.setCharacterSize(40);
	T_Menu.setFillColor(sf::Color::Black);
	T_Menu.setPosition(sceneManager->RenderWindow->getSize().x/2 - 350, sceneManager->RenderWindow->getSize().y - 50);

	T_Undo.setFont(font);
	T_Undo.setString("undo");
	T_Undo.setCharacterSize(40);
	T_Undo.setFillColor(sf::Color::Black);
	T_Undo.setPosition(sceneManager->RenderWindow->getSize().x / 2, sceneManager->RenderWindow->getSize().y - 50);

	T_Hint.setFont(font);
	T_Hint.setString("hint");
	T_Hint.setCharacterSize(40);
	T_Hint.setFillColor(sf::Color::Black);
	T_Hint.setPosition(sceneManager->RenderWindow->getSize().x / 2 + 350, sceneManager->RenderWindow->getSize().y -50);

	int DragOgjectIdentificator = -1;
	bool DragState = false;
	lvl::State* NewMove;
	while (sceneManager->CurentFrame == GameEnum::GameFrame::Game) {
		Event event;
		while (sceneManager->RenderWindow->pollEvent(event)) {
			
			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (isHover(T_Menu, mouse)) {
					sceneManager->CurentFrame = GameEnum::GameFrame::GameSelection;
				}
				if (isHover(T_Undo, mouse)) {
					UndoGame(CurentHistory);
				}
				if (!DragState) {
					DragOgjectIdentificator = GetHoverObject(Islace, 4,&mouse);
					if (DragOgjectIdentificator != -1) {
						DragState = true;
					}
				}
				else {
					Islace[DragOgjectIdentificator]->setPosition(mouse.getPosition().x, mouse.getPosition().y);
				}
			}
			else {
				if(DragOgjectIdentificator != -1) {
					int NewPosition = GetPosition(&size_window, &mouse, 70);
					NewMove = lvl::CopyState(CurentHistory->State);
					GetMove(DragOgjectIdentificator, NewPosition, NewMove);
					//if(Conmparestate) // apel funtie care compara staturile
					//{
					RecordState(CurentHistory, NewMove);
					//}
				}
				DragOgjectIdentificator = -1;
				DragState = false;
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
					sceneManager->CurentFrame = GameEnum::GameFrame::GameSelection;
					break;
				case Keyboard::W:
					CurentHistory->State = &CurentLevel->Solution;
					break;
				default:
					break;
				}
			}
		}

		SetPostionForState(&size_window, CurentHistory->State, Islace, DragOgjectIdentificator);
		
		// Daca elemenut dragibil exista 
		// urmareste pozitia mouseulului
		// scaleaza la marimea lui
		// animatie de scalare

		// funtie de tranzitie pentru a duce obiecte intr-un punc sau altul
		// from curent 0,0 10,20 in time x seconds

		// deseneaza folosind state obiectele cu exceptia celui care este drag and drop

		// stash; mutarile;
		//if (ifCompleted(LVL));
		sceneManager->RenderWindow->clear(Color(255, 204, 102));
		sceneManager->RenderWindow->draw(MainBoard);
		sceneManager->RenderWindow->draw(T_Menu);
		sceneManager->RenderWindow->draw(T_Undo);
		sceneManager->RenderWindow->draw(T_Hint);
		DrowVector(sceneManager, Request, RequestCount);
		DrowVector(sceneManager, Islace, 4);
		sceneManager->RenderWindow->display();
	}
	// pop window .. you ar sure u wont to exit
	//Saving before game leave
	return true;
}
