#pragma once

#include "flecs.h"
#include "components/Sprite.h"
#include <SFML/Graphics/Drawable.hpp>
#include "Context.h"

class SpriteSystem
{
public:
	template <typename T>
	static void run(flecs::entity e, T sprite)
	{
		auto context = static_cast<Context *>(e.world().get_context());
		context->window().draw(sprite.sprite);
	}
};
