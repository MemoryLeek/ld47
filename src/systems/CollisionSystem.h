#pragma once

#include <SFML/System.hpp>

#include "flecs.h"

#include "components/Collidable.h"
#include "components/DynamicCollidable.h"
#include "components/Position.h"
#include "components/Size.h"

class CollisionSystem
{
	public:
		static void run(flecs::iter& it
			, flecs::column<const Position> position
			, flecs::column<const Size> size
			, flecs::column<tag::DynamicCollidable> c
			);

	private:
		static sf::Vector2i getOverlap(const sf::FloatRect& a, const sf::FloatRect& b);
};
