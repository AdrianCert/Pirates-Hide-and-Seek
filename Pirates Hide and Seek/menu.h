#include "GameVariable.h"
#ifndef MENU_H
#define MENU_H

bool Menu(SceneManager* sceneManager);
void resetOriginSprite(sf::Sprite &sprite);
void resetOriginSprite(sf::RectangleShape& sprite);
bool isHover(Sprite& sprite, Mouse& mouse);

#endif