#include "GameVariable.h"
#ifndef HELPER_H
#define HELPER_H
//resetare origini
void resetOriginSprite(sf::Sprite& sprite);
void resetOriginSprite(sf::RectangleShape& shape);
void resOriginText(sf::Text& text);
//verificare mouse
bool isHover(sf::Sprite& sprite, sf::Mouse& mouse);
bool isHover(sf::RectangleShape& shape, sf::Mouse& mouse);
bool isHover(sf::Text& text, sf::Mouse& mouse);



#endif // !HELPER_H

