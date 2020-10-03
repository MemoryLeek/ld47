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

class AnimationSystem
{
public:
	static void run(flecs::entity e, AnimatedSprite& animatedSprite, const Position& pos, tag::Attacking* attacking, const Facing& facing, const Velocity& velocity);
};
