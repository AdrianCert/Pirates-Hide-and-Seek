#include "Menu.h"
#include <SFML/Graphics.hpp>

using namespace sf;

bool Menu(SceneManager* sceneManager) {
	
	//creare fereastra meniu
	//latimea si inaltimea ferestrei
	float latimew, inaltimew;
	latimew = sceneManager->RenderWindow->getSize().x;
	inaltimew = sceneManager->RenderWindow->getSize().y;
	
	//declarare butoane
	RectangleShape play(Vector2f(449.0f, 150.0f)), settings(Vector2f(449.0f, 150.0f)), exit(Vector2f(449.0f, 150.0f));
	
	//resetare origine la fiecare buton
	play.setOrigin(449.0f / 2, 150.0f / 2);
	settings.setOrigin(449.0f / 2, 150.0f / 2);
	exit.setOrigin(449.0f / 2, 150.0f / 2);

	//pozitionare butoane
	play.setPosition(latimew / 2, inaltimew / 2 - 250);
	settings.setPosition(latimew / 2, inaltimew / 2);
	exit.setPosition(latimew / 2, inaltimew / 2 + 250);

	//incarcare texturi buton
	Texture menuButton;
	menuButton.loadFromFile("Textures/butonjoc.png");
	play.setTexture(&menuButton);
	settings.setTexture(&menuButton);
	exit.setTexture(&menuButton);

	//fereastra meniu este deschisa
	while (sceneManager->CurentFrame == GameEnum::GameFrame::Menu)
	{
		Event event;
		while (sceneManager->RenderWindow->pollEvent(event))
		{
			switch (event.type)
			{
				//inchidere fereastra
			case Event::Closed:
				sceneManager->RenderWindow->close();
				break;
			case Event::KeyPressed:
				//inchidere fereastra daca se apasa ESC
				if (event.key.code == Keyboard::Enter) {
					sceneManager->CurentFrame = GameEnum::GameFrame::Game;
					break;
				}

				if (event.key.code == Keyboard::Escape)
					sceneManager->CurentFrame = GameEnum::GameFrame::Exit;
				else
					//fullscreen -> windowed
					if (event.key.code == Keyboard::F10)
					{
						sceneManager->RenderWindow->create(VideoMode(1366, 768), "Pirates Hide and Seek", Style::Close);
						//resetare inaltime butoane
						latimew = sceneManager->RenderWindow->getSize().x;
						inaltimew = sceneManager->RenderWindow->getSize().y;
						play.setPosition(latimew / 2, inaltimew / 2 - 250);
						settings.setPosition(latimew / 2, inaltimew / 2);
						exit.setPosition(latimew / 2, inaltimew / 2 + 250);
					}
					else
						//windowed -> fullscreen
						if (event.key.code == Keyboard::F11)
						{
							sceneManager->RenderWindow->create(VideoMode(1080, 920), "Pirates Hide and Seek", Style::Close | Style::Fullscreen);
							//resetare pozitie butoane
							latimew = sceneManager->RenderWindow->getSize().x;
							inaltimew = sceneManager->RenderWindow->getSize().y;
							play.setPosition(latimew / 2, inaltimew / 2 - 250);
							settings.setPosition(latimew / 2, inaltimew / 2);
							exit.setPosition(latimew / 2, inaltimew / 2 + 250);
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