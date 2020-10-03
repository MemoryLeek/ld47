#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "tmxlite/Tileset.hpp"
#include "flecs.h"

class MapLoader
{
	public:
		MapLoader(flecs::world& ecs, const sf::Texture& tileset);

		void loadFromFile(const std::string& path) const;
		void deleteMapEntities(flecs::world& ecs) const;

	private:
		void loadTileLayer(const tmx::Map& map, const tmx::TileLayer& layer, flecs::entity& mapEntity) const;
		void loadObjectLayer(const tmx::Map& map, const tmx::ObjectGroup& layer, flecs::entity& mapEntity) const;

		static size_t getActiveTileCount(const tmx::TileLayer& layer);
		static std::array<sf::Vector2f, 6> calculateTilePosition(const unsigned int tx, const unsigned int ty, const tmx::Vector2u tileSize);
		static std::array<sf::Vector2f, 6> calculateTexturePosition(const unsigned int tid, const tmx::Tileset& tileset);
		static std::array<sf::Vector2f, 6> convertRectToTriangleVertices(const sf::Rect<float>& rect);

		flecs::world& m_ecs;
		const sf::Texture& m_tileset;
};
