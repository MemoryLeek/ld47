#include <SFML/Graphics.hpp>

#include "components/Position.h"
#include "components/Size.h"
#include "components/Player.h"
#include "components/MapLoadRequest.h"

#include "MapChangeSystem.h"

void MapChangeSystem::run(flecs::entity e
	, const Position& position
	, const Size& size
	, const MapChangeTrigger& trigger
	)
{
	const auto rect = sf::FloatRect(position.position, size.size);

	auto q = e.world()
		.query<const Position, const Size, tag::Player>();

	for (auto it : q)
	{
		flecs::column<const Position> p(it, 1);
		flecs::column<const Size> s(it, 2);

		for (auto i : it)
		{
			if (rect.intersects(sf::FloatRect(p[i].position, s[i].size)))
			{
				std::cout << "[MapChangeSystem] Changing map to [" << trigger.path << "]" << std::endl;
				e.set<MapLoadRequest>(
				{
					.path = trigger.path,
				});
			}
		}
	}
}
