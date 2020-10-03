#include <SFML/System.hpp>

#include "components/PlayerInput.h"
#include "Context.h"

#include "InputSystem.h"

void InputSystem::run(flecs::iter& it, flecs::column<PlayerInput> p, flecs::column<Facing> facing)
{
	auto context = static_cast<Context*>(it.world().get_context());

	sf::Vector2i direction;
	Direction facingDirection = Direction::None;

	// TODO - handle input mapping, or at least make it better
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction.x -= 1;
		facingDirection = Direction::Left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction.x += 1;
		facingDirection = Direction::Right;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		direction.y -= 1;
		facingDirection = Direction::Up;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		direction.y += 1;
		facingDirection = Direction::Down;
	}

	bool attacking = sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z);

	// Update all components with this info
	for (auto i : it)
	{
		p[i].direction = direction;
		p[i].attacking = attacking;

		if (facingDirection != Direction::None)
		{
			facing[i].direction = facingDirection;
		}
	}
}
