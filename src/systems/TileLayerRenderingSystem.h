#pragma once

#include "flecs.h"
#include "components/TileLayer.h"

class TileLayerRenderingSystem
{
	public:
		static void run(flecs::entity e, const TileLayer& tl);
};
