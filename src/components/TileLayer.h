#pragma once

#include <SFML/Graphics.hpp>

struct TileLayer
{
	sf::VertexBuffer vbo;
	const sf::Texture* texture;
};
