#pragma once

#include "flecs.h"

#include "components/Collision.h"
#include "components/MapChangeTrigger.h"
#include "components/Player.h"

class MapChangeSystem
{
	public:
		static void run(flecs::entity e
			, const Position& position
			, const Size& size
			, const MapChangeTrigger& trigger
			);
};
