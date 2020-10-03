#include <SFML/Graphics.hpp>

#include "flecs.h"

#include "Context.h"
#include "Ecs.h"
#include "MapLoader.h"
#include "components/AnimatedSprite.h"
#include "systems/AnimationSystem.h"
#include "components/Velocity.h"
#include "components/Facing.h"
#include "components/Size.h"
#include "components/Collidable.h"
#include "components/DynamicCollidable.h"
#include "components/Collision.h"
#include "components/Player.h"
#include "components/Map.h"
#include "components/TileLayer.h"
#include "components/MapLoadRequest.h"

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(960, 540), "LD47");

	auto view = window.getDefaultView();
	window.setView(view);

	sf::Texture tileset;
	tileset.loadFromFile("assets/tileset.png");

	Context ctx(window, tileset);

	flecs::world ecs;
	ecs.set_context(&ctx);

	ecs::registerComponents(ecs);
	ecs::registerSystems(ecs);

	MapLoader mapLoader(ecs, tileset);
	mapLoader.loadFromFile("assets/map.tmx");

	auto mapChangeRequestQuery = ecs
		.query<MapLoadRequest>();

	sf::Clock clock;
	while (ecs.progress(clock.restart().asSeconds()))
	{
		for (auto it : mapChangeRequestQuery)
		{
			flecs::column<MapLoadRequest> request(it, 1);

			for (auto row : it)
			{
				auto path = request[row].path;
				mapLoader.deleteMapEntities(ecs);
				mapLoader.loadFromFile(path);
				it.entity(row).remove<MapLoadRequest>();
			}
		}
	}

	return 0;
}
