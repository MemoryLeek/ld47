#pragma once

#include "flecs.h"
#include "components/Position.h"
#include "components/Size.h"
#include "components/Player.h"

class CameraSystem
{
	public:
		static void run(flecs::entity e, const Position& pos, const Size& size, tag::Player player);
};
