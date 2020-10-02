#pragma once

#include <SFML/Graphics.hpp>

class Context
{
	public:
		Context(sf::RenderWindow& window, const sf::Texture& tileset);

		sf::RenderWindow& window() const;
		const sf::Texture& tileset() const;

	private:
		sf::RenderWindow& m_window;
		const sf::Texture& m_tileset;
};
