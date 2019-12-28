#include "menu.h"
#include <SFML/Graphics.hpp>

using namespace sf;

bool Menu() {
	float latime, inaltime;
	latime = VideoMode::getDesktopMode().width;  //latime ecran	
	inaltime = VideoMode::getDesktopMode().height;  //inaltime ecran
	
	//creare fereastra meniu
	RenderWindow winMenu(VideoMode(latime, inaltime), "Pirates Hide and Seek", Style::Close | Style::Fullscreen);

	//latimea si inaltimea ferestrei
	float latimew, inaltimew;
	latimew = winMenu.getSize().x;
	inaltimew = winMenu.getSize().y;
	
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
	while (winMenu.isOpen())
	{
		Event event;
		while (winMenu.pollEvent(event))
		{
			switch (event.type)
			{
				//inchidere fereastra
			case Event::Closed:
				winMenu.close();
				break;
			case Event::KeyPressed:
				//inchidere fereastra daca se apasa ESC
				if (event.key.code == Keyboard::Escape)
					winMenu.close();
				else
					//fullscreen -> windowed
					if (event.key.code == Keyboard::F10)
					{
						winMenu.create(VideoMode(1366, 768), "Pirates Hide and Seek", Style::Close);
						//resetare inaltime butoane
						latimew = winMenu.getSize().x;
						inaltimew = winMenu.getSize().y;
						play.setPosition(latimew / 2, inaltimew / 2 - 250);
						settings.setPosition(latimew / 2, inaltimew / 2);
						exit.setPosition(latimew / 2, inaltimew / 2 + 250);
					}
					else
						//windowed -> fullscreen
						if (event.key.code == Keyboard::F11)
						{
							winMenu.create(VideoMode(latime, inaltime), "Pirates Hide and Seek", Style::Close | Style::Fullscreen);
							//resetare pozitie butoane
							latimew = winMenu.getSize().x;
							inaltimew = winMenu.getSize().y;
							play.setPosition(latimew / 2, inaltimew / 2 - 250);
							settings.setPosition(latimew / 2, inaltimew / 2);
							exit.setPosition(latimew / 2, inaltimew / 2 + 250);
						}

			}
		}

		winMenu.clear(Color(255, 204, 102)); //culoare funalului 
		winMenu.draw(play);
		winMenu.draw(settings);
		winMenu.draw(exit);
		winMenu.display();
	}
	return true;
}