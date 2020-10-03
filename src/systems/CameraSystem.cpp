#include "CameraSystem.h"
#include "Context.h"

void CameraSystem::run(flecs::entity e
	, const Position& pos
	, const Size& size
	, tag::Player player
	)
{
	auto context = static_cast<Context *>(e.world().get_context());

	auto view = context->window().getDefaultView();
	view.setCenter(pos.position + size.size / 2.f);
	view.zoom(0.25);
	context->window().setView(view);
}
