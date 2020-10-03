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
			auto e = children.entity(i);
			if (e.has<Collision>())
			{
				auto overlap = e.get<Collision>()->overlap;

				if (abs(overlap.x) <= abs(overlap.y))
				{
					position.position.x = (int)(position.position.x - overlap.x);
				}

				if (abs(overlap.y) <= abs(overlap.x))
				{
					position.position.y = (int)(position.position.y - overlap.y);
				}

				std::cout
					<< "{ " << overlap.x << ", " << overlap.y << " } "
					<< "{ " << position.position.x << ", " << position.position.y << " }"
					<< std::endl;

				e.remove<Collision>();
			}
		}
	}
}
