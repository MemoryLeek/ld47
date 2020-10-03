#pragma once

#include <SFML/System.hpp>
#include "graphics/AnimatedSprite.h"
#include "graphics/AnimationCollection.h"

struct AnimatedSprite
{
	sf::AnimatedSprite sprite;
	AnimationCollection animations;
};
