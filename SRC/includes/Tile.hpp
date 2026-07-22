#pragma once
#include "StaticEntity.hpp"

class Tile : public StaticEntity
{
public:
	char symbol; // The character from the map file
	
	bool solid;  // Whether the tile blocks movement
	bool hazard;  // Spike/Trap
	bool collectable;  // Coin/Heart
	bool goal;  // Level/Goal
	bool air;  // Air

	Tile(char symbol, Vec2 position, Vec2 size) 
		: StaticEntity(position, size), symbol(symbol)
	{
		solid = (symbol == '#');
		hazard = (symbol == '^');
		collectable = (symbol == 'C' || symbol == 'H');
		goal = (symbol == 'G');
		air = (symbol == '.');
	}

	void draw(ViewPort& camera) override;

};

Tile::Tile(char symbol, Vector2 position, Vector2 size)
	: StaticEntity(position, size), symbol(symbol)
{
	solid = (symbol == '#');
	hazard = (symbol == '^');
	collectable = (symbol == 'C' || symbol == 'H');
	goal = (symbol == 'G');
}

void Tile::draw(ViewPort& camera)
{
	//Choose texture based on symbol
	std::string textID;

	switch (symbol)
	{
	case '#': textID = "tile_solid"; break;
	case '^': textID = "tile_spike"; break;
	case 'C': textID = "tile_coin"; break;
	case 'H': textID = "tile_heart"; break;
	case 'G': textID = "tile_goal"; break;
	default: textID = "tile_empty"; break;
	}

	//Render using the exsiting sprites system
	camera.setInViewport(game, sprites[textID], position, size);
}