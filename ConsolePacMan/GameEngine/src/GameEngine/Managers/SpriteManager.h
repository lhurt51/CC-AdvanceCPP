#pragma once

#include "GameEngine/Sprite.h"

#include <glm/glm.hpp>

namespace GameEngine
{
	struct SpriteInfo
	{
		glm::vec3 size;
		std::vector<glm::vec3> verticies;
		std::vector<short> glyphs;
		std::vector<short> colors;
	};

	class SpriteManager
	{
	public:

		static Sprite* LoadSprite(std::wstring fileName);
		static void Draw(const SpriteInfo& sprite);

	};
}

