#include "Ecs.h"

#include "systems/InputSystem.h"
#include "Context.h"

namespace ecs
{
	void registerComponents(flecs::world& ecs)
	{

	}

	void registerSystems(flecs::world& ecs)
	{
		ecs.system<>()
			.action(InputSystem::run);

		// TODO - Move to system file
		ecs.system<>()
			.kind(flecs::PreFrame)
			.action([](flecs::iter& it)
			{
				auto context = static_cast<Context*>(it.world().get_context());
				context->window().clear();
			});

		// TODO - Move to system file
		ecs.system<>()
			.kind(flecs::PostFrame)
			.action([](flecs::iter& it)
			{
				auto context = static_cast<Context*>(it.world().get_context());
				context->window().display();
			});
	}
}
