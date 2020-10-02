#pragma once

#include "flecs.h"
#include "components/Sprite.h"
#include <SFML/Graphics/Drawable.hpp>

class SpriteSystem
{
public:
	static void run(flecs::entity e, Sprite sprite);
};