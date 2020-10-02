#include <SFML/Graphics.hpp>

#include "flecs.h"

#include "Context.h"
#include "Ecs.h"
#include "MapLoader.h"

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(960, 540), "LD47");

	auto view = window.getDefaultView();
	view.zoom(0.25f);
	window.setView(view);

	Context ctx(window);

	flecs::world ecs;
	ecs.set_context(&ctx);

	ecs::registerComponents(ecs);
	ecs::registerSystems(ecs);

	sf::Texture tileset;
	tileset.loadFromFile("assets/tileset.png");

	MapLoader mapLoader(ecs, tileset);
	mapLoader.loadFromFile("assets/map.tmx");

	sf::Clock clock;
	while (ecs.progress(clock.restart().asSeconds()))
	{
	}

	return 0;
}
