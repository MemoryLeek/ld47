#include "Context.h"

Context::Context(sf::RenderWindow& window, const sf::Texture& tileset)
	: m_window(window)
	, m_tileset(tileset)
{
}

sf::RenderWindow& Context::window() const
{
	return m_window;
}

const sf::Texture& Context::tileset() const
{
	return m_tileset;
}