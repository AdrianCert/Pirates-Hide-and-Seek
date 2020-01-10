#include "Menu.h"
#include <SFML/Graphics.hpp>

using namespace sf;

void resetOriginSprite(Sprite &sprite)
{
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

bool Menu(SceneManager* sceneManager) {
	
	//creare fereastra meniu
	//latimea si inaltimea ferestrei
	float latimew, inaltimew, raportRez, ok=0;
	latimew = sceneManager->RenderWindow->getSize().x;
	inaltimew = sceneManager->RenderWindow->getSize().y;
	
	//incarcare texturi buton
	Texture menuButton,
		t_cursor;
	if (!menuButton.loadFromFile("Textures/butonjoc.png")
		|| !t_cursor.loadFromFile("Resource/cursor.png"))
		EXIT_FAILURE;

	//declarare sprites
	Sprite play(menuButton),
		   settings(menuButton),
		   exit(menuButton),
		   cursor(t_cursor);
	
	cursor.setScale(.1, .1);
	cursor.setOrigin(100, 10);

	//resetare origine butoane
	raportRez = inaltimew / latimew;
	resetOriginSprite(play);
	resetOriginSprite(settings);
	resetOriginSprite(exit);
	
	//modificare marime butoane
	play.setScale(raportRez, raportRez );
	settings.setScale(raportRez,raportRez );
	exit.setScale(raportRez, raportRez);

	//pozitionare butoane
	
	play.setPosition(latimew / 2, inaltimew / 2 - 300 * raportRez);
	settings.setPosition(latimew / 2, inaltimew / 2);
	exit.setPosition(latimew / 2, inaltimew / 2 + 300 * raportRez);
	

	
	
	//fereastra meniu este deschisa
	while (sceneManager->CurentFrame == GameEnum::GameFrame::Menu)
	{
		cursor.setPosition(Mouse::getPosition().x, Mouse::getPosition().y);
		Event event;
		while (sceneManager->RenderWindow->pollEvent(event))
		{
			Mouse mouse;
			Vector2f mousePos;
			mousePos.x = mouse.getPosition().x;
			mousePos.y = mouse.getPosition().y;
			
			if (play.getGlobalBounds().contains(mousePos) &&
				Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sceneManager->CurentFrame = GameEnum::GameFrame::Game;
				break;
			}

			switch (event.type)
			{
				//inchidere fereastra
			case Event::Closed:
				sceneManager->RenderWindow->close();
				break;
			
			case Event::KeyPressed:
				//inchidere fereastra daca se apasa ESC
				if (event.key.code == Keyboard::Escape)
					sceneManager->CurentFrame = GameEnum::GameFrame::Exit;
				else
					//fullscreen -> windowed
					if (event.key.code == Keyboard::F10 && ok==0)
					{
						sceneManager->RenderWindow->create(VideoMode(1366, 768), "Pirates Hide and Seek", Style::Close);	
						ok = 1;
					}
					else
					//windowed -> fullscreen
					if (event.key.code == Keyboard::F10 && ok==1)
					{
						sceneManager->RenderWindow->create(VideoMode(1920, 1080), "Pirates Hide and Seek", Style::Close | Style::Fullscreen);
						ok = 0;
					}

			}
		}

		sceneManager->RenderWindow->clear(Color(255, 204, 102)); //culoare funalului 		
		sceneManager->RenderWindow->draw(play);
		sceneManager->RenderWindow->draw(settings);
		sceneManager->RenderWindow->draw(exit); 
		sceneManager->RenderWindow->draw(cursor);
		sceneManager->RenderWindow->display();
	}
	return true;
}