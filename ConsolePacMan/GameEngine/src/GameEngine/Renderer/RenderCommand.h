#pragma once

#include "RendererAPI.h"

namespace GameEngine
{
	class RenderCommand
	{
	public:

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawChar(const glm::vec2& pos, short c, short col)
		{
			s_RendererAPI->DrawChar(pos, c, col);
		}

		inline static void Fill(const glm::vec2& startPos, const glm::vec2& endPos, short c, short col)
		{
			s_RendererAPI->Fill(startPos, endPos, c, col);
		}

		inline void DrawString(const glm::vec2& pos, std::wstring c, short col)
		{
			s_RendererAPI->DrawString(pos, c, col);
		}

		inline void DrawStringAlpha(const glm::vec2& pos, std::wstring c, short col)
		{
			s_RendererAPI->DrawStringAlpha(pos, c, col);
		}

		inline void DrawLine(const glm::vec2& startPos, const glm::vec2& endPos, short c, short col)
		{
			s_RendererAPI->DrawLine(startPos, endPos, c, col);
		}

		inline void DrawTriangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, short c, short col)
		{
			s_RendererAPI->DrawTriangle(p1, p2, p3, c, col);
		}

		inline void FillTriangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, short c, short col)
		{
			s_RendererAPI->FillTriangle(p1, p2, p3, c, col);
		}

		inline void DrawCircle(const glm::vec2& pos, int r, short c, short col)
		{
			s_RendererAPI->DrawCircle(pos, r, c, col);
		}

		inline void FillCircle(const glm::vec2& pos, int r, short c, short col)
		{
			s_RendererAPI->FillCircle(pos, r, c, col);
		}

		inline void DrawSprite(const glm::vec2& pos, const Sprite& sprite)
		{
			s_RendererAPI->DrawSprite(pos, sprite);
		}

		inline void DrawPartialSprite(const glm::vec2& pos, const Sprite& sprite, const glm::vec2& opos, const glm::vec2& size)
		{
			s_RendererAPI->DrawPartialSprite(pos, sprite, opos, size);
		}

		inline void DrawWireFrameModel(const std::vector<glm::vec2>& vecModelCoordinates, const glm::vec2& pos, float r, float s, short col, short c)
		{
			s_RendererAPI->DrawWireFrameModel(vecModelCoordinates, pos, r, s, col, c);
		}

	private:

		static RendererAPI* s_RendererAPI;

	};
}

