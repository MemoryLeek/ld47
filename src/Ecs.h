#pragma once

#include "flecs.h"

namespace ecs
{
	void registerComponents(flecs::world& ecs);
	void registerSystems(flecs::world& ecs);
}
