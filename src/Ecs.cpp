#include "Ecs.h"

#include "components/Collidable.h"
#include "components/Attacking.h"
#include "components/Collision.h"
#include "components/DynamicCollidable.h"
#include "components/Velocity.h"
#include "components/Facing.h"
#include "components/Position.h"
#include "components/Map.h"
#include "components/MapLoadRequest.h"
#include "components/MapChangeTrigger.h"
#include "components/TileLayer.h"
#include "components/PlayerInput.h"
#include "components/Sprite.h"
#include "systems/EventSystem.h"
#include "systems/InputSystem.h"
#include "systems/MovementSystem.h"
#include "systems/SpriteSystem.h"
#include "systems/TileLayerRenderingSystem.h"
#include "systems/AnimationSystem.h"
#include "systems/CameraSystem.h"
#include "systems/CollisionSystem.h"
#include "systems/CollisionSolverSystem.h"
#include "systems/MapChangeSystem.h"
#include "Context.h"

namespace ecs
{
	void registerComponents(flecs::world& ecs)
	{
		ecs.component<Map>();
		ecs.component<MapLoadRequest>();
		ecs.component<AnimatedSprite>();
		ecs.component<TileLayer>();
		ecs.component<PlayerInput>();
		ecs.component<Position>();
		ecs.component<Velocity>();
		ecs.component<Sprite>();
		ecs.component<Collision>();
		ecs.component<tag::Collidable>();
		ecs.component<tag::DynamicCollidable>();
		ecs.component<tag::Attacking>();
	}

	void registerSystems(flecs::world& ecs)
	{
		// --- PreFrame ---

		ecs.system<>()
			.kind(flecs::PreFrame)
			.action(EventSystem::run);

		ecs.system<PlayerInput, Facing>()
			.kind(flecs::PreFrame)
			.action(InputSystem::run);

		ecs.system<>()
			.kind(flecs::PreFrame)
			.action([](flecs::iter& it)
			{
				auto context = static_cast<Context*>(it.world().get_context());
				context->window().clear();
			});

		// --- PreUpdate ---

		ecs.system<Position, const Velocity>()
			.kind(flecs::PreUpdate)
			.each(MovementSystem::run);

		ecs.system<const Position, const Size, tag::DynamicCollidable>()
			.kind(flecs::PreUpdate)
			.action(CollisionSystem::run);

		ecs.system<const PlayerInput&, Velocity&>()
			.kind(flecs::PreUpdate)
			.each([](flecs::entity e, const PlayerInput& playerInput, Velocity& velocity)
			{
				velocity.velocity = sf::Vector2f(playerInput.direction);

				if(playerInput.attacking)
				{
					if(!e.has<tag::Attacking>())
					{
						e.add<tag::Attacking>();
					}
				}
				else
				{
					if(e.has<tag::Attacking>())
					{
						e.remove<tag::Attacking>();
					}
				}
			});

		// --- OnUpdate ---

		ecs.system<AnimatedSprite&, const Position&, tag::Attacking*, const Facing&, const Velocity&>()
			.each(AnimationSystem::run);

		// --- PostUpdate ---

		ecs.system<const Position, const Size, const MapChangeTrigger>()
			.kind(flecs::PostUpdate)
			.each(MapChangeSystem::run);

		ecs.system<Position, tag::DynamicCollidable>()
			.kind(flecs::PostUpdate)
			.each(CollisionSolverSystem::run);

		ecs.system<const Position&, const Size&, tag::Player>()
			.kind(flecs::PostUpdate)
			.each(CameraSystem::run);

		// --- OnStore ---

		ecs.system<const TileLayer>()
			.kind(flecs::OnStore)
			.each(TileLayerRenderingSystem::run);

		ecs.system<Sprite>()
			.kind(flecs::OnStore)
			.each(SpriteSystem::run<Sprite>);

		ecs.system<AnimatedSprite>()
			.kind(flecs::OnStore)
			.each(SpriteSystem::run<AnimatedSprite>);

		// --- PostFrame ---

		ecs.system<>()
			.kind(flecs::PostFrame)
			.action([](flecs::iter& it)
			{
				auto context = static_cast<Context*>(it.world().get_context());
				context->window().display();
			});
	}
}
