#include "EntityFactory.h"
#include "components/AnimatedSprite.h"
#include "components/Position.h"
#include "components/Velocity.h"
#include "components/Size.h"
#include "components/PlayerInput.h"
#include "components/Collidable.h"
#include "components/DynamicCollidable.h"
#include "components/Facing.h"
#include "components/Player.h"
#include "Context.h"

void EntityFactory::spawnPlayer(flecs::world& ecs, const sf::Vector2f& position)
{
	auto context = static_cast<Context*>(ecs.get_context());
	auto& tileset = context->tileset();

	AnimationCollection animations;
	animations.animationIdle.setSpriteSheet(tileset);
	animations.animationIdle.addFrame(sf::IntRect(12*32, 0, 32, 32));
	animations.animationUp.setSpriteSheet(tileset);
	animations.animationUp.addFrame(sf::IntRect(13*32, 0, 32, 32));
	animations.animationUp.addFrame(sf::IntRect(14*32, 0, 32, 32));
	animations.animationUpIdle.setSpriteSheet(tileset);
	animations.animationUpIdle.addFrame(sf::IntRect(12*32, 0, 32, 32));
	animations.animationDown.setSpriteSheet(tileset);
	animations.animationDown.addFrame(sf::IntRect(13*32, 32, 32, 32));
	animations.animationDown.addFrame(sf::IntRect(14*32, 32, 32, 32));
	animations.animationDownIdle.setSpriteSheet(tileset);
	animations.animationDownIdle.addFrame(sf::IntRect(12*32, 32, 32, 32));
	animations.animationLeft.setSpriteSheet(tileset);
	animations.animationLeft.addFrame(sf::IntRect(13*32, 96, 32, 32));
	animations.animationLeft.addFrame(sf::IntRect(14*32, 96, 32, 32));
	animations.animationLeftIdle.setSpriteSheet(tileset);
	animations.animationLeftIdle.addFrame(sf::IntRect(12*32, 96, 32, 32));
	animations.animationRight.setSpriteSheet(tileset);
	animations.animationRight.addFrame(sf::IntRect(13*32, 64, 32, 32));
	animations.animationRight.addFrame(sf::IntRect(14*32, 64, 32, 32));
	animations.animationRightIdle.setSpriteSheet(tileset);
	animations.animationRightIdle.addFrame(sf::IntRect(12*32, 64, 32, 32));
	animations.animationAttack.setSpriteSheet(tileset);
	animations.animationAttack.addFrame(sf::IntRect(15*32, 0*32, 32, 32));
	animations.animationAttack.addFrame(sf::IntRect(16*32, 0*32, 32, 32));
	animations.animationAttack.addFrame(sf::IntRect(17*32, 0*32, 32, 32));
	animations.animationAttack.addFrame(sf::IntRect(18*32, 0*32, 32, 32));
	animations.animationAttack.addFrame(sf::IntRect(17*32, 2*32, 32, 32));
	animations.animationAttack.addFrame(sf::IntRect(16*32, 1*32, 32, 32));
	animations.animationAttack.addFrame(sf::IntRect(17*32, 1*32, 32, 32));
	animations.animationAttack.addFrame(sf::IntRect(18*32, 1*32, 32, 32));
	animations.animationAttack.addFrame(sf::IntRect(17*32, 3*32, 32, 32));
	animations.animationAttackUp.setSpriteSheet(tileset);
	animations.animationAttackUp.addFrame(sf::IntRect(15*32, 0*32, 32, 32));
	animations.animationAttackUp.addFrame(sf::IntRect(16*32, 0*32, 32, 32));
	animations.animationAttackUp.addFrame(sf::IntRect(17*32, 0*32, 32, 32));
	animations.animationAttackUp.addFrame(sf::IntRect(18*32, 0*32, 32, 32));
	animations.animationAttackDown.setSpriteSheet(tileset);
	animations.animationAttackDown.addFrame(sf::IntRect(15*32, 1*32, 32, 32));
	animations.animationAttackDown.addFrame(sf::IntRect(16*32, 1*32, 32, 32));
	animations.animationAttackDown.addFrame(sf::IntRect(17*32, 1*32, 32, 32));
	animations.animationAttackDown.addFrame(sf::IntRect(18*32, 1*32, 32, 32));
	animations.animationAttackLeft.setSpriteSheet(tileset);
	animations.animationAttackLeft.addFrame(sf::IntRect(15*32, 3*32, 32, 32));
	animations.animationAttackLeft.addFrame(sf::IntRect(16*32, 3*32, 32, 32));
	animations.animationAttackLeft.addFrame(sf::IntRect(17*32, 3*32, 32, 32));
	animations.animationAttackLeft.addFrame(sf::IntRect(18*32, 3*32, 32, 32));
	animations.animationAttackRight.setSpriteSheet(tileset);
	animations.animationAttackRight.addFrame(sf::IntRect(15*32, 2*32, 32, 32));
	animations.animationAttackRight.addFrame(sf::IntRect(16*32, 2*32, 32, 32));
	animations.animationAttackRight.addFrame(sf::IntRect(17*32, 2*32, 32, 32));
	animations.animationAttackRight.addFrame(sf::IntRect(18*32, 2*32, 32, 32));

	auto player = ecs.entity("Player")
		.set<AnimatedSprite>({.sprite = sf::AnimatedSprite(), .animations = animations})
		.set<Position>({.position = position})
		.set<Velocity>({})
		.set<Size>({.size = sf::Vector2f(32.0f, 32.0f)})
		.add<PlayerInput>()
		.add<tag::Collidable>()
		.add<tag::DynamicCollidable>()
		.add<tag::Player>()
		.add<Facing>()
		;
}

void EntityFactory::spawnKitten(flecs::world& ecs, const sf::Vector2f& position)
{
	std::cout << "[EntityFactory] Spawning kitten at "
		<< "{ " << position.x << ", " << position.y << " }"
		<< std::endl;

	auto context = static_cast<Context*>(ecs.get_context());
	auto& tileset = context->tileset();

	AnimationCollection animations;
	animations.animationIdle.setSpriteSheet(tileset);
	animations.animationIdle.addFrame(sf::IntRect(12*32, 32, 32, 32));
	animations.animationUp.setSpriteSheet(tileset);
	animations.animationUp.addFrame(sf::IntRect(13*32, 0, 32, 32));
	animations.animationUp.addFrame(sf::IntRect(14*32, 0, 32, 32));
	animations.animationUpIdle.setSpriteSheet(tileset);
	animations.animationUpIdle.addFrame(sf::IntRect(12*32, 0, 32, 32));
	animations.animationDown.setSpriteSheet(tileset);
	animations.animationDown.addFrame(sf::IntRect(13*32, 32, 32, 32));
	animations.animationDown.addFrame(sf::IntRect(14*32, 32, 32, 32));
	animations.animationDownIdle.setSpriteSheet(tileset);
	animations.animationDownIdle.addFrame(sf::IntRect(12*32, 32, 32, 32));
	animations.animationLeft.setSpriteSheet(tileset);
	animations.animationLeft.addFrame(sf::IntRect(13*32, 96, 32, 32));
	animations.animationLeft.addFrame(sf::IntRect(14*32, 96, 32, 32));
	animations.animationLeftIdle.setSpriteSheet(tileset);
	animations.animationLeftIdle.addFrame(sf::IntRect(12*32, 96, 32, 32));
	animations.animationRight.setSpriteSheet(tileset);
	animations.animationRight.addFrame(sf::IntRect(13*32, 64, 32, 32));
	animations.animationRight.addFrame(sf::IntRect(14*32, 64, 32, 32));
	animations.animationRightIdle.setSpriteSheet(tileset);
	animations.animationRightIdle.addFrame(sf::IntRect(12*32, 64, 32, 32));
	animations.animationAttack.setSpriteSheet(tileset);
	animations.animationAttack.addFrame(sf::IntRect(15*32, 0*32, 32, 32));
	animations.animationAttack.addFrame(sf::IntRect(16*32, 0*32, 32, 32));
	animations.animationAttack.addFrame(sf::IntRect(17*32, 0*32, 32, 32));
	animations.animationAttack.addFrame(sf::IntRect(18*32, 0*32, 32, 32));
	animations.animationAttack.addFrame(sf::IntRect(17*32, 2*32, 32, 32));
	animations.animationAttack.addFrame(sf::IntRect(16*32, 1*32, 32, 32));
	animations.animationAttack.addFrame(sf::IntRect(17*32, 1*32, 32, 32));
	animations.animationAttack.addFrame(sf::IntRect(18*32, 1*32, 32, 32));
	animations.animationAttack.addFrame(sf::IntRect(17*32, 3*32, 32, 32));
	animations.animationAttackUp.setSpriteSheet(tileset);
	animations.animationAttackUp.addFrame(sf::IntRect(15*32, 0*32, 32, 32));
	animations.animationAttackUp.addFrame(sf::IntRect(16*32, 0*32, 32, 32));
	animations.animationAttackUp.addFrame(sf::IntRect(17*32, 0*32, 32, 32));
	animations.animationAttackUp.addFrame(sf::IntRect(18*32, 0*32, 32, 32));
	animations.animationAttackDown.setSpriteSheet(tileset);
	animations.animationAttackDown.addFrame(sf::IntRect(15*32, 1*32, 32, 32));
	animations.animationAttackDown.addFrame(sf::IntRect(16*32, 1*32, 32, 32));
	animations.animationAttackDown.addFrame(sf::IntRect(17*32, 1*32, 32, 32));
	animations.animationAttackDown.addFrame(sf::IntRect(18*32, 1*32, 32, 32));
	animations.animationAttackLeft.setSpriteSheet(tileset);
	animations.animationAttackLeft.addFrame(sf::IntRect(15*32, 3*32, 32, 32));
	animations.animationAttackLeft.addFrame(sf::IntRect(16*32, 3*32, 32, 32));
	animations.animationAttackLeft.addFrame(sf::IntRect(17*32, 3*32, 32, 32));
	animations.animationAttackLeft.addFrame(sf::IntRect(18*32, 3*32, 32, 32));
	animations.animationAttackRight.setSpriteSheet(tileset);
	animations.animationAttackRight.addFrame(sf::IntRect(15*32, 2*32, 32, 32));
	animations.animationAttackRight.addFrame(sf::IntRect(16*32, 2*32, 32, 32));
	animations.animationAttackRight.addFrame(sf::IntRect(17*32, 2*32, 32, 32));
	animations.animationAttackRight.addFrame(sf::IntRect(18*32, 2*32, 32, 32));

	auto kitten = ecs.entity("Kitten")
		.set<AnimatedSprite>({.sprite = sf::AnimatedSprite(), .animations = animations})
		// .set<AnimationCollection>({})
		.set<Position>({.position = position})
		.set<Velocity>({})
		.set<Size>({.size = sf::Vector2f(32.0f, 32.0f)})
		.add<tag::Collidable>()
		.add<tag::DynamicCollidable>()
		.add<Facing>()
		;
}
