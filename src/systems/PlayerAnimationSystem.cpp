#include "PlayerAnimationSystem.h"

sf::Animation PlayerAnimationSystem::animationIdle;
sf::Animation PlayerAnimationSystem::animationUp;
sf::Animation PlayerAnimationSystem::animationDown;
sf::Animation PlayerAnimationSystem::animationLeft;
sf::Animation PlayerAnimationSystem::animationRight;
sf::Animation PlayerAnimationSystem::animationAttack;

void PlayerAnimationSystem::initialize(const sf::Texture& tileset)
{
	animationIdle.setSpriteSheet(tileset);
	animationIdle.addFrame(sf::IntRect(12*32, 32, 32, 32));
	animationUp.setSpriteSheet(tileset);
	animationUp.addFrame(sf::IntRect(13*32, 0, 32, 32));
	animationUp.addFrame(sf::IntRect(14*32, 0, 32, 32));
	animationDown.setSpriteSheet(tileset);
	animationDown.addFrame(sf::IntRect(13*32, 32, 32, 32));
	animationDown.addFrame(sf::IntRect(14*32, 32, 32, 32));
	animationLeft.setSpriteSheet(tileset);
	animationLeft.addFrame(sf::IntRect(13*32, 96, 32, 32));
	animationLeft.addFrame(sf::IntRect(14*32, 96, 32, 32));
	animationRight.setSpriteSheet(tileset);
	animationRight.addFrame(sf::IntRect(13*32, 64, 32, 32));
	animationRight.addFrame(sf::IntRect(14*32, 64, 32, 32));
	animationAttack.setSpriteSheet(tileset);
	animationAttack.addFrame(sf::IntRect(13*32, 2*32, 32, 32));
	animationAttack.addFrame(sf::IntRect(14*32, 2*32, 32, 32));
}

void PlayerAnimationSystem::run(flecs::entity e, const PlayerInput& playerInput, AnimatedSprite& animatedSprite, const Position& pos)
{
	animatedSprite.sprite.setPosition(pos.position);

	if(playerInput.attacking)
	{
		animatedSprite.sprite.play(animationAttack);
	}
	else if(playerInput.direction.x > 0)
	{
		animatedSprite.sprite.play(animationRight);
	}
	else if(playerInput.direction.x < 0)
	{
		animatedSprite.sprite.play(animationLeft);
	}
	else if(playerInput.direction.y < 0)
	{
		animatedSprite.sprite.play(animationUp);
	}
	else if(playerInput.direction.y > 0)
	{
		animatedSprite.sprite.play(animationDown);
	}
	else
	{
		animatedSprite.sprite.play(animationIdle);
	}

	animatedSprite.sprite.update(sf::seconds(e.delta_time()));
}
