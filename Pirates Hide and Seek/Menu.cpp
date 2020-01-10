#include "Menu.h"
#include "Source.h"
#include <SFML/Graphics.hpp>

using namespace sf;

void resetOriginSprite(Sprite &sprite)
{
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

void resetOriginSprite(sf::RectangleShape& sprite)
{

}

bool isHover(Sprite& sprite, Mouse& mouse)
{
	Vector2f mousePos;
	mousePos.x = mouse.getPosition().x;
	mousePos.y = mouse.getPosition().y;
	if (sprite.getGlobalBounds().contains(mousePos))
		return true;
	return false;
}

bool Menu(SceneManager* sceneManager) {
	
	//creare fereastra meniu
	//latimea si inaltimea ferestrei
	float latimew, inaltimew, raportRez, ok=0;
	latimew = sceneManager->RenderWindow->getSize().x;
	inaltimew = sceneManager->RenderWindow->getSize().y;
	
	//incarcare texturi buton
	Texture menuButton;
	if (!menuButton.loadFromFile("Textures/butonjoc.png"))
		EXIT_FAILURE;

	//declarare sprites
	Sprite play(menuButton),
		settings(menuButton),
		exit(menuButton);
		   
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
		
		Event event;
		while (sceneManager->RenderWindow->pollEvent(event))
		{
			Mouse mouse;
						
			if (isHover(play, mouse) &&
				Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sceneManager->CurentFrame = GameEnum::GameFrame::Game;
				break;
			}
			else
			if (isHover(exit, mouse) &&
				Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sceneManager->CurentFrame = GameEnum::GameFrame::Exit;
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
						sceneManager->RenderWindow->create(VideoMode(1280, 720), "Pirates Hide and Seek", Style::Close);

						//resetare latime, inaltime si raport rezolutie
						latimew = 1280;
						inaltimew = 720;
						raportRez = inaltimew / latimew;

						//resetare marime sprite
						play.setScale(raportRez, raportRez);
						settings.setScale(raportRez, raportRez);
						exit.setScale(raportRez, raportRez);

						//resetare pozitie sprite
						play.setPosition(latimew / 2, inaltimew / 2 - 300 * raportRez);
						settings.setPosition(latimew / 2, inaltimew / 2);
						exit.setPosition(latimew / 2, inaltimew / 2 + 300 * raportRez);

						ok = 1;
					}
					else
					//windowed -> fullscreen
					if (event.key.code == Keyboard::F10 && ok==1)
					{
						sceneManager->RenderWindow->create(VideoMode(1920, 1080), "Pirates Hide and Seek", Style::Close | Style::Fullscreen);
						
						//resetare latime, inaltime si raport rezolutie
						latimew = 1920;
						inaltimew = 1080;
						raportRez = inaltimew / latimew;

						//resetare marime sprite
						play.setScale(raportRez, raportRez);
						settings.setScale(raportRez, raportRez);
						exit.setScale(raportRez, raportRez);

						//resetare pozitie sprite
						play.setPosition(latimew / 2, inaltimew / 2 - 300 * raportRez);
						settings.setPosition(latimew / 2, inaltimew / 2);
						exit.setPosition(latimew / 2, inaltimew / 2 + 300 * raportRez);

						ok = 0;
					}

			}
		}

		sceneManager->RenderWindow->clear(Color(255, 204, 102)); //culoare funalului 		
		sceneManager->RenderWindow->draw(play);
		sceneManager->RenderWindow->draw(settings);
		sceneManager->RenderWindow->draw(exit); 
		sceneManager->RenderWindow->display();
	}
	return true;
}