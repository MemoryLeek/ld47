#include "MovementSystem.h"
#include <SFML/Graphics/View.hpp>
#include "Context.h"
#include <SFML/System.hpp>

void MovementSystem::run(flecs::entity e, Position& pos, const Velocity& vel)
{
	pos.position.x += vel.velocity.x * e.delta_time() * 150;
	pos.position.y += vel.velocity.y * e.delta_time() * 150;
}
