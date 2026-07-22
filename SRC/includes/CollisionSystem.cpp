#include "CollisionSystem.hpp"
#include <cmath>

/*
Enemies and items can use the same system
collision.resolve(enemy, tilemap);
collision.resolve(coin, tilemap);
collision.resolve(heart, tilemap);

Inside physics loop:
player.tickPhysics(tps);
collision.resolve(player, tilemap);

DynamicEntity Additons (Required for collision)
int health;
Inventory inventory;
bool reachedGoal;

*/

void CollisionSystem::resolve(DynamicEntity& entity, Tilemap& tilemap)
{
	// Horizontal Movement
	entity.position.x += entity.velocity.x;

	int tileX = floor(entity.position.x);
	int tileY = floor(entity.position.y);

	if (tilemap.isSolid(tileX, tileY))
	{
		// Undo Movement
		entity.position.x -= entity.velocity.x;
		entity.velocity.x = 0;
	}

	// Vertical Movement
	entity.postion.y += entity.velocity.y;

	tileX = floor(entity.postion.x);
	tileY = floor(entity.position.y);

	if (tilemap.isSolid(tileX, tileY))
	{
		// Undo Movement
		entity.position.y -= entity.velocity.y;
		entity.velocity.y = 0;
	}

	// Hazards
	if (tilemap.isHazard(tileX, tileY))
	{
		entity.health -= 1;
	}

	// Collectables
	if (tilemap.isCollectible(tileX, tileY))
	{
		entity.inventory.add(tilemap.getSymbol(tileX, tileY));
		tilemap.clearTile(tileX, tileY);
	}

	// Goal
	if (tilemap.isGoal(tileX, tileY))
	{
		entity.reachedGoal = true;
	}

}