#pragma once

#include "Components.h"

#include <math.h>

class PlaneComponent : public Component
{
	TransformComponent* transform;

	int range;
	Vector2D lastPos;
	Vector2D distance;

public:

	PlaneComponent(int r) : transform(nullptr), range(r) , lastPos(Vector2D()), distance(Vector2D())
	{}

	~PlaneComponent()
	{}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
		lastPos = transform->position;
	}

	void update() override
	{
		if (lastPos != transform->position) distance += lastPos - transform->position;

		if (distance.x > range)
		{
			transform->velocity = Vector2D(0, 0);
		}
	}

};