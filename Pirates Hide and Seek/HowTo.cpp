#include "HowTo.h"

bool howto(SceneManager* sceneManager)
{
	sf::Texture tut1, tut2;
	sf::Font font;
	if (!font.loadFromFile("Resource/fontTitlu.ttf") ||
		!tut1.loadFromFile("Resource/tut1.jpg")      ||
		!tut2.loadFromFile("Resource/tut2.jpg"))
		return false;

	sf::Text tutorial;
	tutorial.setFont(font);
	tutorial.setString("1.Choose a challenge either by pressing \"Campaign\" or \"Random Level\"\n\n\n2.Arrange the four puzzle pieces on the game board so that all the\n images are covered except the ones shown in the challenge.");
	tutorial.setCharacterSize(40);
	tutorial.setFillColor(sf::Color::Black);
	tutorial.setPosition(100,100);

	sf::Text back;
	back.setFont(font);
	back.setString("x");
	back.setCharacterSize(30);
	back.setFillColor(sf::Color::Black);
	back.setPosition(5, 5);

	sf::Sprite img1(tut1),
			   img2(tut2);

	img1.setScale(.5,.5);
	img2.setScale(.5, .5);

	img1.setPosition(150, 500);
	img2.setPosition(600, 500);

	sf::Mouse mouse;

	while (sceneManager->CurentFrame == GameEnum::GameFrame::HowToPlay)
	{

		sf::Event event;
		while (sceneManager->RenderWindow->pollEvent(event))
		{
			// Logica butoanelor
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (isHover(back, mouse))
				{
					sceneManager->CurentFrame = GameEnum::GameFrame::Menu;
					return true;
				}

			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				sceneManager->CurentFrame = GameEnum::GameFrame::Menu;
				return true;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I) {
				sceneManager->CurentFrame = GameEnum::GameFrame::Intro;
				return true;
			}
		}
		sceneManager->RenderWindow->clear(sf::Color(255, 204, 102));
		sceneManager->RenderWindow->draw(tutorial);
		sceneManager->RenderWindow->draw(img1);
		sceneManager->RenderWindow->draw(img2);
		sceneManager->RenderWindow->draw(back);
		sceneManager->RenderWindow->display();
	}
	return true;
}