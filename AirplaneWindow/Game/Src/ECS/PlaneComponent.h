#pragma once

#include "Components.h"

#include <math.h>

class PlaneComponent : public Component
{

	TransformComponent* transform;

public:

	PlaneComponent() = default;

	~PlaneComponent()
	{}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = Vector2D(1, 0);
	}

};