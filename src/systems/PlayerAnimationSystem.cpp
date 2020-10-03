#include "PlayerAnimationSystem.h"

#include <iostream>

sf::Animation PlayerAnimationSystem::animationIdle;
sf::Animation PlayerAnimationSystem::animationUp;
sf::Animation PlayerAnimationSystem::animationUpIdle;
sf::Animation PlayerAnimationSystem::animationDown;
sf::Animation PlayerAnimationSystem::animationDownIdle;
sf::Animation PlayerAnimationSystem::animationLeft;
sf::Animation PlayerAnimationSystem::animationLeftIdle;
sf::Animation PlayerAnimationSystem::animationRight;
sf::Animation PlayerAnimationSystem::animationRightIdle;
sf::Animation PlayerAnimationSystem::animationAttack;
sf::Animation PlayerAnimationSystem::animationAttackLeft;
sf::Animation PlayerAnimationSystem::animationAttackRight;
sf::Animation PlayerAnimationSystem::animationAttackUp;
sf::Animation PlayerAnimationSystem::animationAttackDown;

void PlayerAnimationSystem::initialize(const sf::Texture& tileset)
{
	animationIdle.setSpriteSheet(tileset);
	animationIdle.addFrame(sf::IntRect(12*32, 32, 32, 32));
	animationUp.setSpriteSheet(tileset);
	animationUp.addFrame(sf::IntRect(13*32, 0, 32, 32));
	animationUp.addFrame(sf::IntRect(14*32, 0, 32, 32));
	animationUpIdle.setSpriteSheet(tileset);
	animationUpIdle.addFrame(sf::IntRect(12*32, 0, 32, 32));
	animationDown.setSpriteSheet(tileset);
	animationDown.addFrame(sf::IntRect(13*32, 32, 32, 32));
	animationDown.addFrame(sf::IntRect(14*32, 32, 32, 32));
	animationDownIdle.setSpriteSheet(tileset);
	animationDownIdle.addFrame(sf::IntRect(12*32, 32, 32, 32));
	animationLeft.setSpriteSheet(tileset);
	animationLeft.addFrame(sf::IntRect(13*32, 96, 32, 32));
	animationLeft.addFrame(sf::IntRect(14*32, 96, 32, 32));
	animationLeftIdle.setSpriteSheet(tileset);
	animationLeftIdle.addFrame(sf::IntRect(12*32, 96, 32, 32));
	animationRight.setSpriteSheet(tileset);
	animationRight.addFrame(sf::IntRect(13*32, 64, 32, 32));
	animationRight.addFrame(sf::IntRect(14*32, 64, 32, 32));
	animationRightIdle.setSpriteSheet(tileset);
	animationRightIdle.addFrame(sf::IntRect(12*32, 64, 32, 32));
	animationAttack.setSpriteSheet(tileset);
	animationAttack.addFrame(sf::IntRect(15*32, 0*32, 32, 32));
	animationAttack.addFrame(sf::IntRect(16*32, 0*32, 32, 32));
	animationAttack.addFrame(sf::IntRect(17*32, 0*32, 32, 32));
	animationAttack.addFrame(sf::IntRect(18*32, 0*32, 32, 32));
	animationAttack.addFrame(sf::IntRect(17*32, 2*32, 32, 32));
	animationAttack.addFrame(sf::IntRect(16*32, 1*32, 32, 32));
	animationAttack.addFrame(sf::IntRect(17*32, 1*32, 32, 32));
	animationAttack.addFrame(sf::IntRect(18*32, 1*32, 32, 32));
	animationAttack.addFrame(sf::IntRect(17*32, 3*32, 32, 32));
	animationAttackUp.setSpriteSheet(tileset);
	animationAttackUp.addFrame(sf::IntRect(15*32, 0*32, 32, 32));
	animationAttackUp.addFrame(sf::IntRect(16*32, 0*32, 32, 32));
	animationAttackUp.addFrame(sf::IntRect(17*32, 0*32, 32, 32));
	animationAttackUp.addFrame(sf::IntRect(18*32, 0*32, 32, 32));
	animationAttackDown.setSpriteSheet(tileset);
	animationAttackDown.addFrame(sf::IntRect(15*32, 1*32, 32, 32));
	animationAttackDown.addFrame(sf::IntRect(16*32, 1*32, 32, 32));
	animationAttackDown.addFrame(sf::IntRect(17*32, 1*32, 32, 32));
	animationAttackDown.addFrame(sf::IntRect(18*32, 1*32, 32, 32));
	animationAttackLeft.setSpriteSheet(tileset);
	animationAttackLeft.addFrame(sf::IntRect(15*32, 3*32, 32, 32));
	animationAttackLeft.addFrame(sf::IntRect(16*32, 3*32, 32, 32));
	animationAttackLeft.addFrame(sf::IntRect(17*32, 3*32, 32, 32));
	animationAttackLeft.addFrame(sf::IntRect(18*32, 3*32, 32, 32));
	animationAttackRight.setSpriteSheet(tileset);
	animationAttackRight.addFrame(sf::IntRect(15*32, 2*32, 32, 32));
	animationAttackRight.addFrame(sf::IntRect(16*32, 2*32, 32, 32));
	animationAttackRight.addFrame(sf::IntRect(17*32, 2*32, 32, 32));
	animationAttackRight.addFrame(sf::IntRect(18*32, 2*32, 32, 32));
}

void PlayerAnimationSystem::run(flecs::entity e, const PlayerInput& playerInput, AnimatedSprite& animatedSprite, const Position& pos, tag::Attacking* attacking, const Facing& facing, const Velocity& velocity)
{
	// std::cout << &animatedSprite.sprite << std::endl;

	animatedSprite.sprite.setPosition(pos.position);
	// animatedSprite.sprite.setFrameTime(sf::seconds(0.13));

	sf::Animation* animation = &animationIdle;
	float frameTime = 0.2;

	bool walking = velocity.velocity != sf::Vector2f(0.f, 0.f);

	if(attacking)
	{
		frameTime = 0.04;
		switch(facing.direction)
		{
		case Direction::Right:
			animation = &animationAttackRight;
			break;
		case Direction::Left:
			animation = &animationAttackLeft;
			break;
		case Direction::Up:
			animation = &animationAttackUp;
			break;
		case Direction::Down:
			animation = &animationAttackDown;
			break;
		}
	}
	else if(walking)
	{
		frameTime = 0.13;
		switch(facing.direction)
		{
		case Direction::Right:
			animation = &animationRight;
			break;
		case Direction::Left:
			animation = &animationLeft;
			break;
		case Direction::Up:
			animation = &animationUp;
			break;
		case Direction::Down:
			animation = &animationDown;
			break;
		}
	}
	else
	{
		switch(facing.direction)
		{
		case Direction::Right:
			animation = &animationRightIdle;
			break;
		case Direction::Left:
			animation = &animationLeftIdle;
			break;
		case Direction::Up:
			animation = &animationUpIdle;
			break;
		case Direction::Down:
			animation = &animationDownIdle;
			break;
		}
	}

	animatedSprite.sprite.play(*animation);
	animatedSprite.sprite.setFrameTime(sf::seconds(frameTime));

	animatedSprite.sprite.update(sf::seconds(e.delta_time()));
}
