<<<<<<< HEAD
#pragma once
#include "Collectible.hpp"
#include "Player.hpp"

class Coin : public Collectible
{
	int value;

	Coin(const Vector2& pos, int value = 1)
		: Collectible(pos), value(value) {}

	// What happens when the player touches the coin
	void applyEffect(Player& player) override
	{
		player.coins += value;
		collected = true;
	}

	// Draw only if not collected
	void draw(ViewPort& camera) override
	{
		if (!collected)
		{
			// Replace this with sprite system
			// An example would be like sprites.add("coin", position, camera);
		}
	}

=======
#pragma once
#include "Collectible.hpp"
#include "Player.hpp"

class Coin : public Collectible
{
	int value;

	Coin(const Vector2& pos, int value = 1)
		: Collectible(pos), value(value) {}

	// What happens when the player touches the coin
	void applyEffect(Player& player) override
	{
		player.coins += value;
		collected = true;
	}

	// Draw only if not collected
	void draw(ViewPort& camera) override
	{
		if (!collected)
		{
			// Replace this with sprite system
			// An example would be like sprites.add("coin", position, camera);
		}
	}

>>>>>>> origin
};