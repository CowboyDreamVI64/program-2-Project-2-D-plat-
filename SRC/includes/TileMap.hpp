#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include "Tile.hpp"

class Tilemap
{
public:
	std::vector<std::vector<Tile>> tiles;
	size_t width;
	size_t height;

	Tilemap() : width(0), height(0) {}

	void loadFromFile(const std::string& path);

	bool isSolid(int x, int y) const;
	bool isHazard(int x, int y) const;
	bool isCollectible(int x, int y) const;
	bool isGoal(int x, int y) const;
	char getSymbol(int x, int y) const;
	void clearTile(int x, int y);

	void draw(ViewPort& camera);
};