#pragma once
#include "TileMap.hpp"
#include "DynamicEntity.hpp"

class CollisionSystem
{
public:
	void resolve(DynamicEntity& entity, Tilemap& tilemap);
};