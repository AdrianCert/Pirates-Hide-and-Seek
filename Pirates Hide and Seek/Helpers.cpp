#include "Helpers.h"
using namespace sf;
//reseteaza originea unui sprite
void resetOriginSprite(sf::Sprite& sprite)
{
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

//reseteaza originea unui dreptunghi
void resetOriginSprite(sf::RectangleShape& shape)
{
	shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);
}

//reseteaza originea unui text
void resOriginText(sf::Text& text)
{
	text.setOrigin(
		text.getGlobalBounds().left + text.getGlobalBounds().width / 2,
		text.getGlobalBounds().top + text.getGlobalBounds().height / 2);
}

//verifica daca mouse-ul este peste un sprite
bool isHover(sf::Sprite& sprite, sf::Mouse& mouse)
{
	Vector2f mousePos;
	mousePos.x = mouse.getPosition().x;
	mousePos.y = mouse.getPosition().y;
	if (sprite.getGlobalBounds().contains(mousePos))
		return true;
	return false;
}

//verifica daca mouse-ul este peste un dreptunghi
bool isHover(sf::RectangleShape& shape, sf::Mouse& mouse)
{
	Vector2f mousePos;
	mousePos.x = mouse.getPosition().x;
	mousePos.y = mouse.getPosition().y;
	if (shape.getGlobalBounds().contains(mousePos))
		return true;
	return false;
}

//verifica daca mouse-ul este peste un text
bool isHover(sf::Text& text, sf::Mouse& mouse)
{
	Vector2f mousePos;
	mousePos.x = mouse.getPosition().x;
	mousePos.y = mouse.getPosition().y;
	if (text.getGlobalBounds().contains(mousePos))
		return true;
	return false;
}
void DrowVector(SceneManager* sceneManager, sf::RectangleShape** Figures, int FiguresCount) {
	for (int i = 0; i < FiguresCount; i++) {
		sceneManager->RenderWindow->draw(*Figures[i]);
	}
}

void SetOriginCenter(sf::Sprite* sprite) {
		sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
}

void SetOriginCenter(sf::Text* text) {
		text->setOrigin(text->getGlobalBounds().width / 2, text->getGlobalBounds().height / 2);
}

void SetOriginCenter(sf::RectangleShape* shape) {
		shape->setOrigin(shape->getGlobalBounds().width / 2, shape->getGlobalBounds().height / 2);
}
