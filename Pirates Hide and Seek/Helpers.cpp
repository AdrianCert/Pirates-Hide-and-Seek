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
	Vector2f mousePos(mouse.getPosition().x, mouse.getPosition().y);
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
	text->setOrigin(
		text->getGlobalBounds().left + text->getGlobalBounds().width / 2,
		text->getGlobalBounds().top + text->getGlobalBounds().height / 2);
	//text->setOrigin(text->getGlobalBounds().left + text->getGlobalBounds().width / 2, text->getGlobalBounds().top + text->getGlobalBounds().height / 2);
}

void SetOriginCenter(sf::RectangleShape* shape) {
		shape->setOrigin(shape->getGlobalBounds().width / 2, shape->getGlobalBounds().height / 2);
}

void RandOrder(int* n) {
	srand((unsigned)time(NULL));
	int frec[] = { 0, 0 , 0 ,0 };
	int k = rand() % 1000;
	if (k < 100) k = rand() % 1000 + 100;
	while (k != 0)
	{
		frec[rand() % 4]++;
		k--;
	}
	k = 4;
	int max = 0;
	int poz_max = -1;
	while (k != 0) {
		max = 0;
		for (int i = 0; i < 4; i++) {
			if (frec[i] > max) {
				max = frec[i];
				poz_max = i;
			}
		}
		n[4-k] = poz_max;
		frec[poz_max] = 0;
		k--;
		poz_max = -1;
	}
}

sf::Vector2f** GetSpacesForIslace(sf::Vector2u size_window, int size_islace) {
	Vector2f** v = new Vector2f * [4];
	int poz_X = size_window.x - size_islace - 40, poz_Y = size_window.y / 2 - size_islace * 1.5 - 15;
	for (int i = 0; i < 4; i++) {
		v[i] = new Vector2f(poz_X, poz_Y);
		poz_Y += size_islace + 10;
	}
	return v;
}
sf::Vector2f** GetPositionForIslaceOnBoard(sf::Vector2u size_window) {
	Vector2f** v = new Vector2f * [4];
	Vector2f CentralRef = Vector2f(size_window.x / 2, size_window.y / 2);
	float disp = 0.8 * 210 * size_window.y / 1024;
	v[0] = new Vector2f(size_window.x / 2 - disp, size_window.y / 2 - disp);
	v[1] = new Vector2f(size_window.x / 2 + disp, size_window.y / 2 - disp);
	v[2] = new Vector2f(size_window.x / 2 - disp, size_window.y / 2 + disp);
	v[3] = new Vector2f(size_window.x / 2 + disp, size_window.y / 2 + disp);
	return v;
}

sf::Vector2f GetIslaceOnBordDimension(sf::Vector2u size_window) {
	return Vector2f(size_window.y * 320 / 1024, size_window.y * 320 / 1024);
}

sf::Vector2f GetIslaceDefaultDimension(sf::Vector2u size_window) {
	return Vector2f(size_window.y * 0.2, size_window.y * 0.2);
}

int GetHoverObject(sf::RectangleShape* object[], int n, sf::Mouse* mouse) {
	Vector2f mousePos(mouse->getPosition().x, mouse->getPosition().y);
	for (int i = 0; i < n; i++) {
		if (object[i]->getGlobalBounds().contains(mousePos)) {
			return i;
		}
	}
	return -1;
}

void SetPostionForState(sf::Vector2u* size_window, lvl::State* state, sf::RectangleShape** shapes, int skip) {
	float dimension(shapes[0]->getSize().x);
	if (!state->A.Relevant) dimension = shapes[0]->getSize().x;
	if (!state->B.Relevant) dimension = shapes[1]->getSize().x;
	if (!state->C.Relevant) dimension = shapes[2]->getSize().x;
	if (!state->D.Relevant) dimension = shapes[3]->getSize().x;

	Vector2f** SpacesForIslace = GetSpacesForIslace(*size_window, dimension);
	Vector2f** PositionForIslaceOnBoard = GetPositionForIslaceOnBoard(*size_window);
	int Oder[] = { 2, 1, 0, 3 };
	int FreeSpace = 0;
	if (skip != 0) {
		if (state->A.Relevant) {
			shapes[0]->setSize(GetIslaceOnBordDimension(*size_window));
			SetOriginCenter(shapes[0]);
			shapes[0]->setPosition(*PositionForIslaceOnBoard[state->A.Position]);
			shapes[0]->setRotation(state->A.Rotation * 90);
		}
		else {
			shapes[0]->setSize(GetIslaceDefaultDimension(*size_window));
			SetOriginCenter(shapes[0]);
			shapes[0]->setPosition(*SpacesForIslace[FreeSpace++]);
			shapes[0]->setRotation(0);
		}
	}
	if (skip != 1) {
		if (state->B.Relevant) {
			shapes[1]->setSize(GetIslaceOnBordDimension(*size_window));
			SetOriginCenter(shapes[1]);
			shapes[1]->setPosition(*PositionForIslaceOnBoard[state->B.Position]);
			shapes[1]->setRotation(state->B.Rotation * 90);
		}
		else {
			shapes[1]->setSize(GetIslaceDefaultDimension(*size_window));
			SetOriginCenter(shapes[1]);
			shapes[1]->setPosition(*SpacesForIslace[FreeSpace++]);
			shapes[1]->setRotation(0);
		}
	}
	if (skip != 2) {
		if (state->C.Relevant) {
			shapes[2]->setSize(GetIslaceOnBordDimension(*size_window));
			SetOriginCenter(shapes[2]);
			shapes[2]->setPosition(*PositionForIslaceOnBoard[state->C.Position]);
			shapes[2]->setRotation(state->C.Rotation * 90);
		}
		else {
			shapes[2]->setSize(GetIslaceDefaultDimension(*size_window));
			SetOriginCenter(shapes[2]);
			shapes[2]->setPosition(*SpacesForIslace[FreeSpace++]);
			shapes[2]->setRotation(0);
		}
	}
	if (skip != 3) {
		if (state->D.Relevant) {
			shapes[3]->setSize(GetIslaceOnBordDimension(*size_window));
			SetOriginCenter(shapes[3]);
			shapes[3]->setPosition(*PositionForIslaceOnBoard[state->D.Position]);
			shapes[3]->setRotation(state->D.Rotation * 90);
		}
		else {
			shapes[3]->setSize(GetIslaceDefaultDimension(*size_window));
			SetOriginCenter(shapes[3]);
			shapes[3]->setPosition(*SpacesForIslace[FreeSpace++]);
			shapes[3]->setRotation(0);
		}
	}
}

int GetPosition(sf::Vector2u* size_window, sf::Mouse* mouse, int precision) {
	Vector2f** PositionForIslaceOnBoard = GetPositionForIslaceOnBoard(*size_window);
	int X_point = mouse->getPosition().x;
	int Y_point = mouse->getPosition().y;
	for (int i = 0; i < 4; i++) {
		if (abs(PositionForIslaceOnBoard[i]->x - X_point) < precision
			&& abs(PositionForIslaceOnBoard[i]->y - Y_point) < precision)
			return i;
	}
	return -1;
}

int UInterogationWindowForConfirm(sf::RenderWindow* window, std::string question) {
	Text Question;
	Text Yes;
	Text No;
	Text Cancel;
	RectangleShape Frame;
	Font font;
	Mouse mouse;
	if (!font.loadFromFile("Resource/fontTitlu.ttf")) return -1;

	Frame.setFillColor(sf::Color(92, 194, 208));
	Frame.setSize(Vector2f(window->getSize().x / 2, window->getSize().y / 3));
	SetOriginCenter(&Frame);
	Frame.setPosition(Vector2f(window->getSize().x / 2, window->getSize().y / 2));

	Question.setFont(font);
	Question.setString(question);
	Question.setCharacterSize(50);
	Question.setFillColor(sf::Color::Black);
	resOriginText(No);
	Question.setPosition(Frame.getGlobalBounds().left + 50, Frame.getGlobalBounds().top + 100);

	Cancel.setFont(font);
	Cancel.setString("x");
	Cancel.setCharacterSize(40);
	Cancel.setFillColor(sf::Color::Black);
	resOriginText(Yes);
	Cancel.setPosition(Frame.getGlobalBounds().left + Frame.getGlobalBounds().width - 50, Frame.getGlobalBounds().top + 10);

	Yes.setFont(font);
	Yes.setString("yes");
	Yes.setCharacterSize(50);
	Yes.setFillColor(sf::Color::Black);
	resOriginText(Yes);
	Yes.setPosition(window->getSize().x / 2 - Frame.getGlobalBounds().width / 3, Frame.getGlobalBounds().top + Frame.getGlobalBounds().height - 50);

	No.setFont(font);
	No.setString("no");
	No.setCharacterSize(50);
	No.setFillColor(sf::Color::Black);
	resOriginText(No);
	No.setPosition(window->getSize().x / 2 + Frame.getGlobalBounds().width / 3, Frame.getGlobalBounds().top + Frame.getGlobalBounds().height - 50);

	while (1) {
		Event event;
		while (window->pollEvent(event)) {

			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (isHover(Yes, mouse)) {
					return 1;
				}
				if (isHover(No, mouse)) {
					return 0;
				}
				if (isHover(Cancel, mouse)) {
					return -1;
				}
				if (!isHover(Frame, mouse)) {
					return -1;
				}
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
				return -1;
			}
		}
		window->clear(Color(255, 204, 102));
		window->draw(Frame);
		window->draw(Cancel);
		window->draw(Question);
		window->draw(Yes);
		window->draw(No);
		window->display();
	}

}