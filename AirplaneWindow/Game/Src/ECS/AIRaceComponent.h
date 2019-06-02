#pragma once

#include "Components.h"

class AIRaceComponent : public Component
{
	TransformComponent* transform;

	Vector2D velocity;
	int range;
	int distance;
	int speed;

public:

	AIRaceComponent(Vector2D vel, int r, int sp) : velocity(vel), range(r), speed(sp)
	{}

	~AIRaceComponent()
	{}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void update() override
	{
		distance += speed;

		if (distance > range)
		{
			transform->velocity = Vector2D(0, 0);
		}
	}

};
