#include "Ecs.h"

#include "components/PlayerInput.h"
#include "systems/EventSystem.h"
#include "systems/InputSystem.h"
#include "Context.h"

namespace ecs
{
	void registerComponents(flecs::world& ecs)
	{
		ecs.component<PlayerInput>();
	}

	void registerSystems(flecs::world& ecs)
	{
		ecs.system<>()
			.kind(flecs::PreFrame)
			.action(EventSystem::run);

		ecs.system<PlayerInput>()
			.kind(flecs::PreFrame)
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
