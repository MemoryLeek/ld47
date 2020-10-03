#include <SFML/Graphics.hpp>

#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"

#include "components/Map.h"
#include "components/MapChangeTrigger.h"
#include "components/TileLayer.h"
#include "components/Position.h"
#include "components/Size.h"
#include "components/Collidable.h"
#include "components/Player.h"

#include "EntityFactory.h"
#include "MapLoader.h"

MapLoader::MapLoader(flecs::world& ecs, const sf::Texture& tileset)
	: m_ecs(ecs)
	, m_tileset(tileset)
{
}

void MapLoader::loadFromFile(const std::string& path) const
{
	std::cout << "[tmx] Loading map: " << path << std::endl;

	tmx::Map map;
	map.load(path);

	auto mapEntity = m_ecs.entity()
		.set<Map>({});

	for (const auto& layer : map.getLayers())
	{
		const auto type = layer->getType();

		switch (type)
		{
			case tmx::Layer::Type::Tile:
				std::cout << "[tmx] Loading tile layer: " << layer->getName() << std::endl;
				loadTileLayer(map
					, layer->getLayerAs<tmx::TileLayer>()
					, mapEntity
					);
				break;
			case tmx::Layer::Type::Object:
				std::cout << "[tmx] Loading object layer: " << layer->getName() << std::endl;
				loadObjectLayer(map
					, layer->getLayerAs<tmx::ObjectGroup>()
					, mapEntity
					);
				break;
			default:
				std::cout << "Unhandled layer type: " << static_cast<int>(type) << std::endl;
		}
	}
}

void MapLoader::deleteMapEntities(flecs::world& ecs) const
{
	auto filter = flecs::filter(m_ecs)
		.include<Map>();

	for (auto it : m_ecs.filter(filter))
	{
		for (auto i : it)
		{
			auto map = it.entity(i);
			map.destruct();
		}
	}
}

void MapLoader::loadTileLayer(const tmx::Map& map, const tmx::TileLayer& layer, flecs::entity& mapEntity) const
{
	const auto& tileSize = map.getTileSize();
	const auto& tileset = map.getTilesets().at(0); // TODO - support more than one tileset?
	const auto& tileCount = map.getTileCount();
	const auto& tiles = layer.getTiles();

	std::vector<sf::Vertex> vertices(getActiveTileCount(layer) * 6);
	size_t vertexIndex = 0;

	for (int y = 0; y < map.getTileCount().y; y++)
	{
		for (int x = 0; x < map.getTileCount().x; x++)
		{
			const auto& tile = tiles[x + tileCount.x * y];
			if (tile.ID == 0)
			{
				continue;
			}

			const auto& tileVertices = calculateTilePosition(x, y, tileSize);
			const auto& textureVertices = calculateTexturePosition(tile.ID, tileset);

			for (size_t i = 0; i < 6; i++)
			{
				vertices[vertexIndex].position = tileVertices[i];
				vertices[vertexIndex].texCoords = textureVertices[i];
				vertexIndex++;
			}
		}
	}

	sf::VertexBuffer vbo(sf::PrimitiveType::Triangles, sf::VertexBuffer::Usage::Static);
	vbo.create(vertices.size());
	vbo.update(vertices.data());

	auto tileLayerEntity = m_ecs.entity()
		.add_childof(mapEntity)
		.set<TileLayer>(
		{
			.vbo = vbo,
			.texture = &m_tileset,
		});
}

void MapLoader::loadObjectLayer(const tmx::Map& map, const tmx::ObjectGroup& layer, flecs::entity& mapEntity) const
{
	const auto& layerProperties = layer.getProperties();
	const auto isLayerCollidable = std::find_if(layerProperties.begin()
		, layerProperties.end()
		, [](auto p)
		{
			return p.getType() == tmx::Property::Type::Boolean
				&& p.getBoolValue()
				&& p.getName() == "collidable"
				;
		}
		) != layerProperties.end();

	for (const auto& object : layer.getObjects())
	{
		const auto& objectProperties = object.getProperties();
		const auto& aabb = object.getAABB();

		if (isLayerCollidable)
		{
			m_ecs.entity()
				.add_childof(mapEntity)
				.add<tag::Collidable>()
				.set<Position>(
				{
					.position = sf::Vector2f(aabb.left, aabb.top),
				})
				.set<Size>(
				{
					.size = sf::Vector2f(aabb.width, aabb.height),
				})
				;
		}

		const auto isMapChangeTrigger = std::find_if(objectProperties.begin()
			, objectProperties.end()
			, [](auto p)
			{
				return p.getType() == tmx::Property::Type::String
					&& p.getName() == "type"
					&& p.getStringValue() == "mapChange"
					;
			}
			) != objectProperties.end();

		if (isMapChangeTrigger)
		{
			const auto& path = std::find_if(objectProperties.begin()
				, objectProperties.end()
				, [](auto p)
				{
					return p.getType() == tmx::Property::Type::String
						&& p.getName() == "path"
						;
				}
				)->getStringValue();

			std::cout << "[tmx] Map change trigger to ["
				<< path
				<< "] loaded"
				<< std::endl;

			m_ecs.entity()
				.add_childof(mapEntity)
				.set<Position>(
				{
					.position = sf::Vector2f(aabb.left, aabb.top),
				})
				.set<Size>(
				{
					.size = sf::Vector2f(aabb.width, aabb.height),
				})
				.set<MapChangeTrigger>(
				{
					.path = path,
				})
				;
		}

		const auto typeIter = std::find_if(objectProperties.begin()
			, objectProperties.end()
			, [](auto p)
			{
				return p.getType() == tmx::Property::Type::String
					&& p.getName() == "type"
					;
			}
			);

		const auto type = typeIter != objectProperties.end()
			? typeIter->getStringValue()
			: "";

		if (type == "enemy")
		{
			const auto& enemy = std::find_if(objectProperties.begin()
				, objectProperties.end()
				, [](auto p)
				{
					return p.getType() == tmx::Property::Type::String
						&& p.getName() == "enemy"
						;
				}
				)->getStringValue();

			if (enemy == "kitten")
			{
				EntityFactory::spawnKitten(m_ecs, sf::Vector2f(aabb.left, aabb.top));
			}
			else
			{
				std::cout << "[MapLoader] Undefined enemy type " << enemy << std::endl;
			}

		}

		if (type == "spawn")
		{
			EntityFactory::spawnPlayer(m_ecs, sf::Vector2f(aabb.left, aabb.top));


			// auto filter = flecs::filter(m_ecs)
			// 	.include<Position>()
			// 	.include<tag::Player>();

			// for (auto it : m_ecs.filter(filter))
			// {
			// 	auto pos = it.table_column<Position>();

			// 	for (auto i : it)
			// 	{
			// 		std::cout
			// 			<< "[MapLoader] Moving player to spawn "
			// 			<< "{ " << aabb.left << ", " << aabb.top << " }"
			// 			<< std::endl;

			// 		pos[i].position = sf::Vector2f(aabb.left, aabb.top);
			// 	}
			// }
		}
	}
}

size_t MapLoader::getActiveTileCount(const tmx::TileLayer& layer)
{
	size_t count = 0;
	for (const auto& tile : layer.getTiles())
	{
		if (tile.ID == 0)
		{
			continue;
		}

		count++;
	}
	return count;
}

std::array<sf::Vector2f, 6> MapLoader::calculateTilePosition(const unsigned int tx, const unsigned int ty, const tmx::Vector2u tileSize)
{
	const auto px = tx * tileSize.x;
	const auto py = ty * tileSize.y;

	return convertRectToTriangleVertices(sf::Rect<float>(px, py, tileSize.x, tileSize.y));
}

std::array<sf::Vector2f, 6> MapLoader::calculateTexturePosition(const unsigned int tid, const tmx::Tileset& tileset)
{
	const auto tile = tileset.getTile(tid);
	const auto& pos = tile->imagePosition;
	const auto& size = tile->imageSize;

	return convertRectToTriangleVertices(sf::Rect<float>(pos.x, pos.y, size.x, size.y));
}

std::array<sf::Vector2f, 6> MapLoader::convertRectToTriangleVertices(const sf::Rect<float>& rect)
{
	return {{
		// Top left
		{
			rect.left,
			rect.top
		},
		// Bottom left
		{
			rect.left,
			rect.top + rect.height
		},
		// Top right
		{
			rect.left + rect.width,
			rect.top
		},
		// Top right
		{
			rect.left + rect.width,
			rect.top
		},
		// Bottom left
		{
			rect.left,
			rect.top + rect.height
		},
		// Bottom right
		{
			rect.left + rect.width,
			rect.top + rect.height
		},
	}};
}
