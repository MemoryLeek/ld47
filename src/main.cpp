#include <SFML/Graphics.hpp>

#include "flecs.h"

#include "Context.h"
#include "Ecs.h"

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(960, 540), "LD47");

	Context ctx(window);

	flecs::world ecs;
	ecs.set_context(&ctx);

	ecs::registerComponents(ecs);
	ecs::registerSystems(ecs);

	sf::Clock clock;
	while (ecs.progress(clock.restart().asSeconds()))
	{
	}

	return 0;
}
