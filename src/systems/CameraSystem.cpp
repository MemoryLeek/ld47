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

	auto adjustX = view.getSize().x / 2 - view.getCenter().x;
	if (adjustX > 0)
	{
		view.move(adjustX, 0);
	}

	auto adjustY = view.getSize().y / 2 - view.getCenter().y;
	if (adjustY > 0)
	{
		view.move(0, adjustY);
	}

	const sf::Vector2f mapSize(12 * 32, 12 * 32);

	adjustY = mapSize.y - (view.getSize().y / 2 + view.getCenter().y);
	if (adjustY < 0)
	{
		view.move(0, adjustY);
	}

	adjustX = mapSize.x - (view.getSize().x / 2 + view.getCenter().x);
	if (adjustX < 0)
	{
		view.move(adjustX, 0);
	}

	context->window().setView(view);
}
