#include "MovementSystem.h"

void MovementSystem::run(flecs::entity e, Position pos, Velocity vel)
{
	pos.position.x += vel.velocity.x * e.delta_time() * 10;
	pos.position.y += vel.velocity.y * e.delta_time() * 10;
}
