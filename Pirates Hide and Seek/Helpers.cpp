#include "Helpers.h"

void DrowVector(SceneManager* sceneManager, sf::RectangleShape* Figures[], int FiguresCount) {
	for (int i = 0; i < FiguresCount; i++) {
		sceneManager->RenderWindow->draw(*Figures[i]);
	}
}