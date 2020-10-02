#include <SFML/System.hpp>

#include "Context.h"

#include "InputSystem.h"

void InputSystem::run(flecs::iter& it)
{
	auto context = static_cast<Context*>(it.world().get_context());

	sf::Event event;
	while (context->window().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			ecs_quit(it.world().c_ptr());
		}
	}
}
