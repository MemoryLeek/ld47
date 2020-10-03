#pragma once

#include <SFML/Graphics.hpp>

#include "flecs.h"
#include "components/PlayerInput.h"
#include "graphics/Animation.h"
#include "components/AnimatedSprite.h"
#include "components/Position.h"

class PlayerAnimationSystem
{
private:
	static sf::Animation animationDown, animationUp, animationLeft, animationRight, animationIdle;
public:
	static void initialize(const sf::Texture& tileset);
	static void run(flecs::entity e, const PlayerInput& playerInput, AnimatedSprite& animatedSprite, const Position& pos);
};
