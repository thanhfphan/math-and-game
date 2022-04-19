#include "shape.h"
#include <iostream>

CircleShape::CircleShape(float radius)
{
	this->radius = radius;
	std::cout << "CircleShape constructor called!" << std::endl;
}
CircleShape::~CircleShape()
{
	std::cout << "CircleShape destructor called!" << std::endl;
}

ShapeType CircleShape::GetType() const 
{
	return CIRCLE;
}

Shape* CircleShape::Clone() const 
{
	return new CircleShape(radius);
}

float CircleShape::GetMomentOfInertia() const
{
	return 0.5 * (radius * radius);
}