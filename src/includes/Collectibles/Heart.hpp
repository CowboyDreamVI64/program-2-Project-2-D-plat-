<<<<<<< HEAD
#pragma
#include "Collectible.hpp"
#include "Player.hpp"

class Heart : public Collectible
{
	int healAmount;

	Heart(const Vector2& pos, int healAmount = 1)
		: Collectible(pos), (healAmount) {}

	// What happens when the player touches the heart
	void applyEffect(Player& player) override
	{
		player.health += healAmount;
		collected = true;
	}

	// Draw only if not collected
	void draw(ViewPort& camera) override
	{
		if (!collected)
		{
			// Replace with the sprite system
		}
	}

=======
#pragma
#include "Collectible.hpp"
#include "Player.hpp"

class Heart : public Collectible
{
	int healAmount;

	Heart(const Vector2& pos, int healAmount = 1)
		: Collectible(pos), (healAmount) {}

	// What happens when the player touches the heart
	void applyEffect(Player& player) override
	{
		player.health += healAmount;
		collected = true;
	}

	// Draw only if not collected
	void draw(ViewPort& camera) override
	{
		if (!collected)
		{
			// Replace with the sprite system
		}
	}

>>>>>>> origin
};