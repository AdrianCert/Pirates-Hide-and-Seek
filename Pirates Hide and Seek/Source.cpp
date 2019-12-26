#include <SFML/Graphics.hpp>
#include "Configuration.h"
#include "menu.h"

using namespace sf;



int main()
{
	
	int gameWidth = 800;
	int gameHeight = 600;
	RenderWindow window(VideoMode(200, 200), "SFML works!");
	CircleShape shape(100.f);
	shape.setFillColor(Color::Green);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed ||
				event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
				window.close();
				break;
			}

		}
    //Y2
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}