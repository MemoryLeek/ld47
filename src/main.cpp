#include <SFML/Graphics.hpp>

#include "flecs.h"

#include "Context.h"
#include "Ecs.h"
#include "MapLoader.h"
#include "components/AnimatedSprite.h"
#include "systems/PlayerAnimationSystem.h"
#include "components/Velocity.h"
#include "components/Size.h"
#include "components/Collidable.h"
#include "components/DynamicCollidable.h"
#include "components/Collision.h"
#include "components/Player.h"

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(960, 540), "LD47");

	auto view = window.getDefaultView();
	window.setView(view);

	sf::Texture tileset;
	tileset.loadFromFile("assets/tileset.png");

	PlayerAnimationSystem::initialize(tileset);

	Context ctx(window, tileset);

	flecs::world ecs;
	ecs.set_context(&ctx);

	ecs::registerComponents(ecs);
	ecs::registerSystems(ecs);

	MapLoader mapLoader(ecs, tileset);
	mapLoader.loadFromFile("assets/map.tmx");

	auto player = ecs.entity("Player")
		.set<AnimatedSprite>({.sprite = sf::AnimatedSprite()})
		.set<Position>({})
		.set<Velocity>({})
		.set<Size>({.size = sf::Vector2f(32.0f, 32.0f)})
		.add<PlayerInput>()
		.add<tag::Collidable>()
		.add<tag::DynamicCollidable>()
		.add<tag::Player>()
		;

	sf::Clock clock;
	while (ecs.progress(clock.restart().asSeconds()))
	{
	}

	return 0;
}
