#pragma once

#include "vec2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "shape.h"

struct Body
{
	Vec2 position;
	Vec2 velocity;
	Vec2 acceleration;

	Vec2 sumForces;

	float mass;
	float invMass;
	float I;
	float invI;


	Shape* shape;

	Body(const Shape& shape, float x, float y, float mass);
	~Body();

	bool IsStatic() const;

	void AddForce(const Vec2& force);
	void ClearForces();

	void ApplyImpulseLinear(const Vec2& j);

	void IntegrateForces(const float dt);
	void IntegrateVelocities(const float dt);
};
