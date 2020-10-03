#include "PlayerAnimationSystem.h"

sf::Animation PlayerAnimationSystem::animationIdle;
sf::Animation PlayerAnimationSystem::animationUp;
sf::Animation PlayerAnimationSystem::animationDown;
sf::Animation PlayerAnimationSystem::animationLeft;
sf::Animation PlayerAnimationSystem::animationRight;

void PlayerAnimationSystem::initialize(const sf::Texture& tileset)
{
	animationIdle.setSpriteSheet(tileset);
	animationIdle.addFrame(sf::IntRect(5*32, 32, 32, 32));
	animationUp.setSpriteSheet(tileset);
	animationUp.addFrame(sf::IntRect(6*32, 0, 32, 32));
	animationUp.addFrame(sf::IntRect(7*32, 0, 32, 32));
	animationDown.setSpriteSheet(tileset);
	animationDown.addFrame(sf::IntRect(6*32, 32, 32, 32));
	animationDown.addFrame(sf::IntRect(7*32, 32, 32, 32));
	animationLeft.setSpriteSheet(tileset);
	animationLeft.addFrame(sf::IntRect(6*32, 96, 32, 32));
	animationLeft.addFrame(sf::IntRect(7*32, 96, 32, 32));
	animationRight.setSpriteSheet(tileset);
	animationRight.addFrame(sf::IntRect(6*32, 64, 32, 32));
	animationRight.addFrame(sf::IntRect(7*32, 64, 32, 32));
}

void PlayerAnimationSystem::run(flecs::entity e, const PlayerInput& playerInput, AnimatedSprite& animatedSprite, const Position& pos)
{
	animatedSprite.sprite.setPosition(pos.position);

	if(playerInput.direction.x > 0)
	{
		animatedSprite.sprite.play(PlayerAnimationSystem::animationRight);
	}
	else if(playerInput.direction.x < 0)
	{
		animatedSprite.sprite.play(PlayerAnimationSystem::animationLeft);
	}
	else if(playerInput.direction.y < 0)
	{
		animatedSprite.sprite.play(PlayerAnimationSystem::animationUp);
	}
	else if(playerInput.direction.y > 0)
	{
		animatedSprite.sprite.play(PlayerAnimationSystem::animationDown);
	}
	else
	{
		animatedSprite.sprite.play(PlayerAnimationSystem::animationIdle);
	}

	animatedSprite.sprite.update(sf::seconds(e.delta_time()));
}
