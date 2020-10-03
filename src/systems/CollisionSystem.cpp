#include <SFML/Graphics.hpp>

#include "components/Collision.h"
#include "CollisionSystem.h"

void CollisionSystem::run(flecs::iter& it
	, flecs::column<const Position> position
	, flecs::column<const Size> size
	, flecs::column<tag::DynamicCollidable> c
	)
{
	auto q = it.world()
		.query<const Position, const Size, tag::Collidable>();

	for (auto i : it)
	{
		auto entity = it.entity(i);
		sf::FloatRect boundingBox(position[i].position, size[i].size);

		for (auto oit : q)
		{
			flecs::column<const Position> p(oit, 1);
			flecs::column<const Size> s(oit, 2);

			for (auto oi : oit)
			{
				auto otherEntity = oit.entity(oi);
				if (entity.id() == otherEntity.id()) // No self collision pls
				{
					continue;
				}

				auto otherBoundingBox = sf::FloatRect(p[oi].position, s[oi].size);
				if (boundingBox.intersects(otherBoundingBox))
				{
					// std::cout << "Adding collision to "
					// 	<< entity.name()
					// 	<< " with object at "
					// 	<< "{ " << p[oi].position.x << ", " << p[oi].position.y << " }"
					// 	<< " of size "
					// 	<< "{ " << s[oi].size.x << ", " << s[oi].size.y << " }"
					// 	<< std::endl;

					it.world()
						.entity("Collision")
						.add_childof(entity)
						.set<Collision>(
						{
							.entity = otherEntity,
							.overlap = getOverlap(boundingBox, otherBoundingBox),
						});
				}
			}

		}
	}
}

sf::Vector2i CollisionSystem::getOverlap(const sf::FloatRect& a, const sf::FloatRect& b)
{
	int x = (a.left > b.left) ? -(b.left + b.width  - a.left) : a.left + a.width  - b.left;
	int y = (a.top > b.top)   ? -(b.top  + b.height - a.top)  : a.top  + a.height - b.top;
	return sf::Vector2i(x, y);
}
