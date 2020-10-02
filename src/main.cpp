#include <SFML/Graphics.hpp>

#include "flecs.h"

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(960, 540), "LD47");

	flecs::world ecs;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		window.display();
	}

	return 0;
}
