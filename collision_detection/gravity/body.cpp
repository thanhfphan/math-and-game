#include "body.h"
#include <iostream>

Body::Body(const Shape &shape, float x, float y, float mass)
{
	this->shape = shape.Clone();
	this->position = Vec2(x, y);
	this->velocity = Vec2(0, 0);
	this->acceleration = Vec2(0, 0);
	this->sumForces = Vec2(0, 0);
	this->mass = mass;
	if (mass != 0.0)
	{
		this->invMass = 1.0 / mass;
	}
	else
	{
		this->invMass = 0.0;
	}

	I = shape.GetMomentOfInertia() * mass;
	if (I != 0.0)
	{
		this->invI = 1.0 / I;
	}
	else
	{
		this->invI = 0.0;
	}
	std::cout << "Body constructor called!" << std::endl;
}

Body::~Body()
{
	std::cout << "Body destructor called!" << std::endl;
}

bool Body::IsStatic() const
{
	const float epsilon = 0.005f;
	return fabs(invMass - 0.0) < epsilon;
}

void Body::AddForce(const Vec2 &force)
{
	sumForces += force;
}

void Body::ClearForces()
{
	sumForces = Vec2(0.0, 0.0);
}

void Body::ApplyImpulseLinear(const Vec2 &j)
{
	if (IsStatic())
	{
		return;
	}
	velocity += j * invMass;
}

void Body::IntegrateForces(const float dt)
{
	if (IsStatic())
	{
		return;
	}

	acceleration = sumForces * invMass;
	velocity += acceleration * dt;

	ClearForces();
}

void Body::IntegrateVelocities(const float dt)
{
	if (IsStatic())
	{
		return;
	}

	position += velocity * dt;
}