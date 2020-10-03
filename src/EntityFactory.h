#pragma once

#include <SFML/System.hpp>

#include "flecs.h"

class EntityFactory
{
	public:
		static void spawnKitten(flecs::world& ecs, const sf::Vector2f& position);
};
