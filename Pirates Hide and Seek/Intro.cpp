#include "Intro.h"

void resPozText(sf::Text &text)
{
	text.setOrigin(
		text.getGlobalBounds().left + text.getGlobalBounds().width / 2,
		text.getGlobalBounds().top + text.getGlobalBounds().height / 2);
}

bool Intro(SceneManager* sceneManager) {
	
	sceneManager->RenderWindow->setMouseCursorVisible(false);
	float angle(0.f);
	sf::Clock time;
	sf::Vector2f scalable = sf::Vector2f(1,1);

	sf::Font font;
	if (!font.loadFromFile("Resource/fontTitlu.ttf"))
		EXIT_FAILURE;

	while (time.getElapsedTime() <= sf::seconds(5.3))
	{
		//Titlu Joc
		sf::Text titlu;
		titlu.setFont(font);
		titlu.setString("PIRATES HIDE N' SEEK");
		titlu.setCharacterSize(100);
		titlu.setFillColor(sf::Color::Black);
		resPozText(titlu);
		titlu.setPosition(sceneManager->RenderWindow->getSize().x /2, sceneManager->RenderWindow->getSize().y / 2);
		

		//Patrat Incarcare
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(100, 100));
		rectangle.setFillColor(sf::Color::Color(255, 204, 102));
		rectangle.setOrigin(50,50);
		rectangle.setPosition(sceneManager->RenderWindow->getSize().x/2, sceneManager->RenderWindow->getSize().y/2);
		rectangle.setRotation(angle);
		rectangle.scale(scalable);
		angle += 0.02f;
		scalable.x += 0.0022f;
		scalable.y += 0.0022f;


		sceneManager->RenderWindow->clear();
		sceneManager->RenderWindow->draw(rectangle);
		sceneManager->RenderWindow->draw(titlu);
		sceneManager->RenderWindow->display();
	}

	sceneManager->CurentFrame = GameEnum::GameFrame::Menu;
	
	return true;
}