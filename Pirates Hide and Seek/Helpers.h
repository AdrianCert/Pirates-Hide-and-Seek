#include "GameVariable.h"
#include "Level.h"
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
void RandOrder(int* n);


sf::Vector2f** GetSpacesForIslace(sf::Vector2u size_window, int size_islace);
sf::Vector2f** GetPositionForIslaceOnBoard(sf::Vector2u size_window);
sf::Vector2f GetIslaceOnBordDimension(sf::Vector2u size_window);
sf::Vector2f GetIslaceDefaultDimension(sf::Vector2u size_window);
int GetHoverObject(sf::RectangleShape* object[], int n, sf::Mouse* mouse);
void SetPostionForState(sf::Vector2u* size_window, lvl::State* state, sf::RectangleShape** shapes, int skip);
int GetPosition(sf::Vector2u* size_window, sf::Mouse* mouse, int precision);
int UInterogationWindowForConfirm(sf::RenderWindow* window, std::string question);

#endif // !HELPERS_H
