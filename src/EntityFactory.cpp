#include "EntityFactory.h"

void EntityFactory::spawnKitten(flecs::world& ecs, const sf::Vector2f& position)
{
	std::cout << "[EntityFactory] Spawning kitten at "
		<< "{ " << position.x << ", " << position.y << " }"
		<< std::endl;
}
