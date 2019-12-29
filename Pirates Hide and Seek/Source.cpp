#include <SFML/Graphics.hpp>
#include <sstream>
#include "Configuration.h"
#include "menu.h"

using namespace sf;

int main()
{
	int gameWidth, gameHeight, gameSSyle;
	std::string gameName;
	cfg::dictionaty* configuration = new cfg::dictionaty();
	if (!ReadConfiguration(configuration, "Resource/ConfigureFile.txt")) return EXIT_FAILURE;
	if (!GetParm(configuration, "gameWidth", gameWidth)
		|| !GetParm(configuration, "gameHeight", gameHeight)
		|| !GetParm(configuration, "gameName", gameName)
		|| !GetParm(configuration, "gameSSyle", gameSSyle))
		return EXIT_FAILURE;
	/* Explemple of overwriting pharms * /
	cfg::SetParm(configuration, "gameWidth", VideoMode::getDesktopMode().width);
	cfg::SetParm(configuration, "gameHeight", VideoMode::getDesktopMode().height);
	cfg::WriteConfiguration(configuration, "Resource/ConfigureFile.txt");
	/**/
	std::stringstream sri;
	VariableName(sri, gameSSyle);
	std::cout << sri.str();
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