#include <SFML/System.hpp>

#include "components/PlayerInput.h"
#include "Context.h"

#include "InputSystem.h"

void InputSystem::run(flecs::iter& it, flecs::column<PlayerInput> p)
{
	auto context = static_cast<Context*>(it.world().get_context());

	sf::Vector2i direction;

	// TODO - handle input mapping, or at least make it better
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction.x -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction.x += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		direction.y += 1;
	}

	// Update all components with this info
	for (auto i : it)
	{
		p[i].direction = direction;
	}
}
