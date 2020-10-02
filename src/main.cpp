#include <SFML/Graphics.hpp>

#include "flecs.h"

#include "Context.h"
#include "Ecs.h"
#include "MapLoader.h"
#include "components/AnimatedSprite.h"
#include "systems/PlayerAnimationSystem.h"
#include "components/Velocity.h"

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(960, 540), "LD47");

	auto view = window.getDefaultView();
	// view.zoom(0.25f);
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

	auto player = ecs.entity()
		.set<AnimatedSprite>({.sprite = sf::AnimatedSprite()})
		.set<Position>({})
		.set<Velocity>({})
		.set<PlayerInput>({});

	sf::Clock clock;
	while (ecs.progress(clock.restart().asSeconds()))
	{
	}

	return 0;
}
