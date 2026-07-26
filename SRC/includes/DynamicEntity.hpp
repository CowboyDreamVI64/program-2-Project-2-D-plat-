#pragma once
#include "DynamicEntity.hpp"
#include "vec2.hpp"

class DynamicEntity : public Entity
{
public:
	Vector2 velocity;
	Vector2 acceleration;

	DynamicEntity(const Vector2& pos, const Vector2& size)
		: Entity(pos, size), velocity({ 0,0 }), acceleration({ 0,0 }) {}

	// Movement physics (gravity, friction, jumping, etc)
	virtual void tickPhysics(double dt) = 0;

	// Game logic (AI, input, animation)
	virtual void update(double dt) override = 0;

	// Rendering
	virtual void draw(ViewPort& camera) override = 0;

	virtual ~DynamicEntity() {}

};