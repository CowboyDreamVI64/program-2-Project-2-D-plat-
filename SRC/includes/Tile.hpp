#pragma once
#include "StaticEntity.hpp"
#include "textures.hpp"
#include "sprites.hpp"

class Tile : public StaticEntity
{
public:
	char symbol; // The character from the map file
	bool solid;  // Whether the tile blocks movement
	bool hazard;  // Spike/Trap
	bool collectable;  // Coin/Heart
	bool goal;  // Level/Goal

	Tile(char symbol, Vector2 position, Vector2 size);

	void draw(ViewPort& camera) override;

};