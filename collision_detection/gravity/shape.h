#pragma once

enum ShapeType {
	CIRCLE,
	POLYGON,
	BOX
};

struct Shape {
	virtual ~Shape() = default;
	virtual ShapeType GetType() const = 0;
	virtual Shape* Clone() const = 0;
	virtual float GetMomentOfInertia() const = 0;
};

struct CircleShape : public Shape
{
	float radius;

	CircleShape(const float radius);
	virtual ~CircleShape();
	virtual ShapeType GetType() const override;
	virtual Shape* Clone() const override;
	virtual float GetMomentOfInertia() const override;
};
