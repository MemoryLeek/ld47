#pragma once

#include "flecs.h"
#include "components/Position.h"
#include "components/Velocity.h"

class MovementSystem
{
	public:
		static void run(flecs::entity e, Position& pos, const Velocity& vel);
};