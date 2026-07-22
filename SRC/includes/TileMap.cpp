#include "TileMap.hpp"
#include <fstream>

/*
Need to add:

Enemy spawner

Player spawn logic

Collectible logic

Goal logic
*/

void Tilemap::loadFromFile(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to load tilemap: " + path);
	}
	std::string line;
	size_t y = 0;

	while (std::getline(file, line))
	{
		std::vector<Tile> row;

		for (size_t x = 0; x < line.size(); x++)
		{
			char symbol = line[x];
			Vector2 pos = { (double)x,(double)y };
			row.emplace_back(Tile(symbol, pos, Vector2{ 1.0,1.0 }));
		}

		tiles.push_back(row);
		y++;
	}
	height = tiles.size();
	width = tiles[0].size();
}

bool Tilemap::isSolid(int x, int y) const
{
	if (x < 0 || y < 0 || y >= height || x >= width) return true;
	return tiles[y][x].solid;
}
bool Tilemap::isHazard(int x, int y) const
{
	if (x < 0 || y < 0 || y >= height || x >= width) return false;
	return tiles[y][x].hazard;
}

void Tilemap::draw(ViewPort& camera)
{
	for (auto& row : tiles)
	{
		for (auto& tile : row)
		{
			tile.draw(camera);
		}
	}
}


