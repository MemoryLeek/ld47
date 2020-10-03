#pragma once

#include <SFML/Graphics.hpp>

#include "flecs.h"
#include "components/PlayerInput.h"
#include "graphics/Animation.h"
#include "components/AnimatedSprite.h"
#include "components/Position.h"
#include "components/Attacking.h"
#include "components/Velocity.h"
#include "components/Facing.h"

class PlayerAnimationSystem
{
private:
	static sf::Animation
		animationDown,
		animationDownIdle,
		animationUp,
		animationUpIdle,
		animationLeft,
		animationLeftIdle,
		animationRight,
		animationRightIdle,
		animationIdle,
		animationAttack,
		animationAttackLeft,
		animationAttackRight,
		animationAttackUp,
		animationAttackDown;
public:
	static void initialize(const sf::Texture& tileset);
	static void run(flecs::entity e, const PlayerInput& playerInput, AnimatedSprite& animatedSprite, const Position& pos, tag::Attacking* attacking, const Facing& facing, const Velocity& velocity);
};
