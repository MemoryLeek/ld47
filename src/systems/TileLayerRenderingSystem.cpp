#include "Context.h"

#include "TileLayerRenderingSystem.h"

void TileLayerRenderingSystem::run(flecs::entity e, const TileLayer& tl)
{
	auto context = static_cast<Context*>(e.world().get_context());

	context->window().draw(tl.vbo, sf::RenderStates(tl.texture));
}
