#include "AnimationSystem.h"

#include <iostream>

void AnimationSystem::run(flecs::entity e, AnimatedSprite& animatedSprite, const Position& pos, tag::Attacking* attacking, const Facing& facing, const Velocity& velocity)
{
	animatedSprite.sprite.setPosition(pos.position);

	sf::Animation& animation = animatedSprite.animations.animationIdle;
	float frameTime = 0.2;

	bool walking = velocity.velocity != sf::Vector2f(0.f, 0.f);

	if(attacking)
	{
		frameTime = 0.04;
		switch(facing.direction)
		{
		case Direction::Right:
			animation = animatedSprite.animations.animationAttackRight;
			break;
		case Direction::Left:
			animation = animatedSprite.animations.animationAttackLeft;
			break;
		case Direction::Up:
			animation = animatedSprite.animations.animationAttackUp;
			break;
		case Direction::Down:
			animation = animatedSprite.animations.animationAttackDown;
			break;
		}
	}
	else if(walking)
	{
		frameTime = 0.13;
		switch(facing.direction)
		{
		case Direction::Right:
			animation = animatedSprite.animations.animationRight;
			break;
		case Direction::Left:
			animation = animatedSprite.animations.animationLeft;
			break;
		case Direction::Up:
			animation = animatedSprite.animations.animationUp;
			break;
		case Direction::Down:
			animation = animatedSprite.animations.animationDown;
			break;
		}
	}
	else
	{
		switch(facing.direction)
		{
		case Direction::Right:
			animation = animatedSprite.animations.animationRightIdle;
			break;
		case Direction::Left:
			animation = animatedSprite.animations.animationLeftIdle;
			break;
		case Direction::Up:
			animation = animatedSprite.animations.animationUpIdle;
			break;
		case Direction::Down:
			animation = animatedSprite.animations.animationDownIdle;
			break;
		}
	}

	animatedSprite.sprite.play(animation);
	animatedSprite.sprite.setFrameTime(sf::seconds(frameTime));

	animatedSprite.sprite.update(sf::seconds(e.delta_time()));
}
