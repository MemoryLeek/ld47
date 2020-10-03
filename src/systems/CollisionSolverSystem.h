#pragma once

#include "flecs.h"

#include "components/Collision.h"
#include "components/DynamicCollidable.h"
#include "components/Position.h"

class CollisionSolverSystem
{
	public:
		static void run(flecs::entity e
			, Position& position
			, tag::DynamicCollidable dc
			);
};
