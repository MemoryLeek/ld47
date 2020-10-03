#pragma once

#include <SFML/System.hpp>

#include "flecs.h"

struct Collision
{
	flecs::entity entity;
	sf::Vector2i overlap;
};
