#include "Context.h"

Context::Context(sf::RenderWindow& window)
	: m_window(window)
{
}

sf::RenderWindow& Context::window()
{
	return m_window;
}
