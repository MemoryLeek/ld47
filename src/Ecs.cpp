#include "Ecs.h"

#include "components/Velocity.h"
#include "components/Position.h"
#include "components/Map.h"
#include "components/TileLayer.h"
#include "components/PlayerInput.h"
#include "components/Sprite.h"
#include "systems/EventSystem.h"
#include "systems/InputSystem.h"
#include "systems/MovementSystem.h"
#include "systems/SpriteSystem.h"
#include "systems/TileLayerRenderingSystem.h"
#include "Context.h"

namespace ecs
{
	void registerComponents(flecs::world& ecs)
	{
		ecs.component<Map>();
		ecs.component<TileLayer>();
		ecs.component<PlayerInput>();
		ecs.component<Position>();
		ecs.component<Velocity>();
		ecs.component<Sprite>();
	}

	void registerSystems(flecs::world& ecs)
	{
		ecs.system<>()
			.kind(flecs::PreFrame)
			.action(EventSystem::run);

		ecs.system<PlayerInput>()
			.kind(flecs::PreFrame)
			.action(InputSystem::run);

		ecs.system<Position, const Velocity>()
			.each(MovementSystem::run);

		ecs.system<const TileLayer>()
			.kind(flecs::OnStore)
			.each(TileLayerRenderingSystem::run);

		ecs.system<Sprite>()
			.kind(flecs::OnStore)
			.each(SpriteSystem::run);

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
