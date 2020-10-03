#pragma once

#include "flecs.h"
#include "components/Facing.h"

class InputSystem
{
	public:
		static void run(flecs::iter& it, flecs::column<PlayerInput> p, flecs::column<Facing> facing);
};
