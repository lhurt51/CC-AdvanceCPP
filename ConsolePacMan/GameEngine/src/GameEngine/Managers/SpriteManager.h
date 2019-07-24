#pragma once

#include "GameEngine/Renderer/RendererColors.h"

#include <glm/glm.hpp>

namespace GameEngine
{
	struct SpriteInfo
	{
		glm::vec2 size;
		std::vector<glm::vec3> verts;
		std::vector<short> glyphs;
		std::vector<short> colors;

		void Init(size_t width, size_t height);

		void SetGlyph(int x, int y, short c);
		void SetColor(int x, int y, short c);

		short GetGlyph(int x, int y) const;
		short GetColor(int x, int y) const;

		short SampleGlyph(float x, float y);
		short SampleColor(float x, float y);

	};

	class SpriteManager
	{
	public:

		static SpriteInfo* LoadSprite(std::wstring fileName);
		static void Draw(const SpriteInfo& sprite);

	};
}

