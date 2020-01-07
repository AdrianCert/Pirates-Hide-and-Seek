#include "Intro.h"

bool Intro(SceneManager* sceneManager) {
	float angle(0.f);
	sf::Clock time;
	sf::Vector2f scalable = sf::Vector2f(1,1);
	while (time.getElapsedTime() <= sf::seconds(100)
		&& angle <= 45) {
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(100, 100));
		rectangle.setFillColor(sf::Color::Blue);
		rectangle.setOrigin(50,50);
		rectangle.setPosition(sceneManager->RenderWindow->getSize().x/2, sceneManager->RenderWindow->getSize().y/2);
		rectangle.setRotation(angle);
		rectangle.scale(scalable);
		angle += 0.01f;
		scalable.x += 0.001f;
		scalable.y += 0.001f;
		sceneManager->RenderWindow->clear();
		sceneManager->RenderWindow->draw(rectangle);
		sceneManager->RenderWindow->display();
	}
	sceneManager->CurentFrame = GameEnum::GameFrame::Menu;
	return true;
}