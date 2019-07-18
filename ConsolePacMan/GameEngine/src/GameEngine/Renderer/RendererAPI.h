#pragma once

#include <glm/glm.hpp>

#include "GameEngine/Sprite.h"

#include "RendererColors.h"

namespace GameEngine
{
	class RendererAPI
	{
	public:

		enum class API
		{
			None = 0,
			WindowsConsole = 1
		};

	public:

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		// virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		virtual void DrawChar(const glm::vec2& pos, short c, short col) = 0;
		virtual void Fill(const glm::vec2& startPos, const glm::vec2& endPos, short c, short col) = 0;
		virtual void DrawString(const glm::vec2& pos, std::wstring c, short col) = 0;
		virtual void DrawStringAlpha(const glm::vec2& pos, std::wstring c, short col) = 0;
		virtual void DrawLine(const glm::vec2& startPos, const glm::vec2& endPos, short c, short col) = 0;
		virtual void DrawTriangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, short c, short col) = 0;
		virtual void FillTriangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, short c, short col) = 0;
		virtual void DrawCircle(const glm::vec2& pos, int r, short c, short col) = 0;
		virtual void FillCircle(const glm::vec2& pos, int r, short c, short col) = 0;
		virtual void DrawSprite(const glm::vec2& pos, const Sprite& sprite) = 0;
		virtual void DrawPartialSprite(const glm::vec2& pos, const Sprite& sprite, const glm::vec2& opos, const glm::vec2& size) = 0;
		virtual void DrawWireFrameModel(const std::vector<glm::vec2>& vecModelCoordinates, const glm::vec2& pos, float r, float s, short col, short c) = 0;
		

		inline static API GetAPI() { return s_API; }

	private:

		static API s_API;

	};
}

