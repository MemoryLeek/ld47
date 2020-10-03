#include "CameraSystem.h"
#include "Context.h"

void CameraSystem::run(flecs::entity e, const Position& pos, const Size& size)
{
	auto context = static_cast<Context *>(e.world().get_context());
	context->window().setView(sf::View(pos.position + size.size / 2.f, sf::Vector2f(300.f, 200.f)));
}