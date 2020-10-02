#include "flecs.h"
#include "Context.h"
#include "SpriteSystem.h"
#include "components/Sprite.h"

void SpriteSystem::run(flecs::entity e, Sprite sprite)
{
	auto context = static_cast<Context*>(e.world().get_context());
	context->window().draw(sprite.sprite);
}