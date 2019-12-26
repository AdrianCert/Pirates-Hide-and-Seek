#include <SFML/Graphics.hpp>
#include "Configuration.h"
#include "menu.h"

using namespace sf;

int main()
{
	int gameWidth, gameHeight, gameSSyle;
	std::string gameName;
	dictionaty* configuration = new dictionaty();
	if (!configuration->ReadConfiguration("Resource/ConfigureFile.txt")) return EXIT_FAILURE;
	if (!configuration->GetParm("gameWidth", gameWidth)
		|| !configuration->GetParm("gameHeight", gameHeight)
		|| !configuration->GetParm("gameName", gameName)
		|| !configuration->GetParm("gameSSyle", gameSSyle)) 
		return EXIT_FAILURE;

	RenderWindow window(VideoMode(gameWidth, gameHeight), gameName,gameSSyle);
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