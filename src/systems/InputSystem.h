#pragma once

#include "flecs.h"

class InputSystem
{
	public:
		static void run(flecs::iter& it, flecs::column<PlayerInput> p);
};
