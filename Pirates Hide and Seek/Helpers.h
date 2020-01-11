#include "GameVariable.h"
#ifndef HELPERS_H
#define HELPERS_H

void DrowVector(SceneManager* sceneManager, sf::RectangleShape** Figures, int FiguresCount);
void SetOriginCenter(sf::Sprite* sprite);
void SetOriginCenter(sf::Text* text);
void SetOriginCenter(sf::RectangleShape* shape);
// resetarea origini
void resetOriginSprite(sf::Sprite& sprite);
void resetOriginSprite(sf::RectangleShape& shape);
void resOriginText(sf::Text& text);
//verificare mouse
bool isHover(sf::Sprite& sprite, sf::Mouse& mouse);
bool isHover(sf::RectangleShape& shape, sf::Mouse& mouse);
bool isHover(sf::Text& text, sf::Mouse& mouse);


#endif // !HELPERS_H
