#include <SFML/System.hpp>

#include "Context.h"

#include "EventSystem.h"

void EventSystem::run(flecs::iter& it)
{
	auto context = static_cast<Context*>(it.world().get_context());

	sf::Event event;
	while (context->window().pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				ecs_quit(it.world().c_ptr());
				break;
			default:
				break;
		}
	}
}
