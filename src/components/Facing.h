#pragma once

#include <SFML/System.hpp>

enum Direction
{
	None,
	Left,
	Right,
	Up,
	Down
};

struct Facing
{
	Direction direction;
};