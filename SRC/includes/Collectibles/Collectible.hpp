#pragma once
#include "StaticEntity.hpp"
#include "Player.hpp"

class Collectible : public StaticEntity
{
public:
	bool collected;

	Collectible(const Vector2& pos)
		: StaticEntity(pos, { 1.0, 1.0 }, false), collected(false) {
	}

	//Called when the player touches the collectible
	virtual void applyEffect(Player& player) = 0;

	// Collectibles do not update logic unless we want animations
	void update(double dt) override {}

	// Draw the collectible only if not collected
	void draw(Viewport& camera) override
	{
		if (!collected)
		{
			// Sprite rendering here
		}
	}

	virtual ~Collectible() {}
};
