#pragma once

#include <SFML/Graphics.hpp>

class Context
{
	public:
		Context(sf::RenderWindow& window);

		sf::RenderWindow& window();

	private:
		sf::RenderWindow& m_window;
};
