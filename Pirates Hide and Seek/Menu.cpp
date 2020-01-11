#include "Menu.h"
#include "Source.h"
#include <SFML/Graphics.hpp>

using namespace sf;

bool Menu(SceneManager* sceneManager) {
	
	//creare fereastra meniu
	//latimea si inaltimea ferestrei
	float latimew, inaltimew, raportRez, ok=0;
	Mouse mouse;
	latimew = sceneManager->RenderWindow->getSize().x;
	inaltimew = sceneManager->RenderWindow->getSize().y;
	
	Font font;

	//incarcare textura butoane si font
	Texture menuButton, t_cursor;
	if (!menuButton.loadFromFile("Resource/t_butonjoc.png") ||
	    !font.loadFromFile("Resource/fontTitlu.ttf"))
      return false;
	latimew = sceneManager->RenderWindow->getSize().x;
	inaltimew = sceneManager->RenderWindow->getSize().y;

	//declarare sprites
	Sprite play(menuButton),
		settings(menuButton),
		exit(menuButton);
	//declarare text
	Text t_play,
		t_settings,
		t_exit;

	//aplicare font text
	t_play.setFont(font);
	t_settings.setFont(font);
	t_exit.setFont(font);

	//text
	t_play.setString("play");
	t_settings.setString("settings");
	t_exit.setString("exit");

	//culoare text
	t_play.setFillColor(Color::Black);
	t_settings.setFillColor(Color::Black);
	t_exit.setFillColor(Color::Black);

	//marime font
	t_play.setCharacterSize(75);
	t_settings.setCharacterSize(75);
	t_exit.setCharacterSize(75);
		   
	//resetare origine butoane si text
	raportRez = inaltimew / latimew;
	resetOriginSprite(play);
	resetOriginSprite(settings);
	resetOriginSprite(exit);
	resOriginText(t_play);
	resOriginText(t_settings);
	resOriginText(t_exit);
	
	//modificare marime butoane
	play.setScale(raportRez, raportRez );
	settings.setScale(raportRez,raportRez );
	exit.setScale(raportRez, raportRez);

	//pozitionare butoane
	
	play.setPosition(latimew / 2, inaltimew / 2 - 300 * raportRez);
	settings.setPosition(latimew / 2, inaltimew / 2);
	exit.setPosition(latimew / 2, inaltimew / 2 + 300 * raportRez);
	t_play.setPosition(latimew / 2, inaltimew / 2 - 300 * raportRez);
	t_settings.setPosition(latimew / 2, inaltimew / 2);
	t_exit.setPosition(latimew / 2, inaltimew / 2 + 300 * raportRez);


	
	
	//fereastra meniu este deschisa
	while (sceneManager->CurentFrame == GameEnum::GameFrame::Menu)
	{
		
		Event event;
		while (sceneManager->RenderWindow->pollEvent(event))
		{
			// Logica butoanelor
			if (Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (isHover(play, mouse)) 
					sceneManager->CurentFrame = GameEnum::GameFrame::GameSelection;
				if (isHover(exit, mouse))
					sceneManager->CurentFrame = GameEnum::GameFrame::Exit;
				if(isHover(settings, mouse))
					sceneManager->CurentFrame = GameEnum::GameFrame::Option;
			}

			switch (event.type)
			{
				//inchidere fereastra
			case Event::Closed:
				sceneManager->RenderWindow->close();
				break;
			
			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::Escape:
					sceneManager->CurentFrame = GameEnum::GameFrame::Exit;
					break;
				case Keyboard::Enter:
					sceneManager->CurentFrame = GameEnum::GameFrame::GameSelection;
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

		sceneManager->RenderWindow->clear(Color(255, 204, 102)); //culoare funalului 		
		sceneManager->RenderWindow->draw(play);
		sceneManager->RenderWindow->draw(settings);
		sceneManager->RenderWindow->draw(exit);
		sceneManager->RenderWindow->draw(t_play);
		sceneManager->RenderWindow->draw(t_settings);
		sceneManager->RenderWindow->draw(t_exit);
		sceneManager->RenderWindow->display();
		
	}
	return true;
}