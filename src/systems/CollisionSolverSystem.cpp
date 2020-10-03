#include <cmath>

#include "CollisionSolverSystem.h"

void CollisionSolverSystem::run(flecs::entity e
	, Position& position
	, tag::DynamicCollidable dc
	)
{
	for (auto children : e.children())
	{
		for (auto i : children)
		{
			auto ce = children.entity(i);
			if (ce.has<Collision>())
			{
				auto overlap = ce.get<Collision>()->overlap;

				if (abs(overlap.x) < abs(overlap.y))
				{
					position.position.x = (int)(position.position.x - overlap.x);
				}

				if (abs(overlap.y) < abs(overlap.x))
				{
					position.position.y = (int)(position.position.y - overlap.y);
				}

				std::cout
					<< "Solved collision for [" << e.name() << "] "
					<< "with overlap "
					<< "{ " << overlap.x << ", " << overlap.y << " } "
					<< "resulting in new position of "
					<< "{ " << position.position.x << ", " << position.position.y << " }"
					<< std::endl;

				ce.remove<Collision>();
			}
		}
	}
}
