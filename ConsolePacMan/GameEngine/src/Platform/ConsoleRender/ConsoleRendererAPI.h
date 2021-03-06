#pragma once

#include "GameEngine/Renderer/RendererAPI.h"

namespace GameEngine
{
	class ConsoleRendererAPI : public RendererAPI
	{
	public:

		virtual void SetClearColor(COLOR color) override;
		virtual void Clear() override;

		virtual void DrawChar(const glm::vec2& pos, short c, short col) override;
		virtual void Fill(const glm::vec2& startPos, const glm::vec2& endPos, short c, short col) override;
		virtual void DrawString(const glm::vec2& pos, std::wstring c, short col) override;
		virtual void DrawStringAlpha(const glm::vec2& pos, std::wstring c, short col) override;
		virtual void DrawLine(const glm::vec2& startPos, const glm::vec2& endPos, short c, short col) override;
		virtual void DrawTriangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, short c, short col) override;
		virtual void FillTriangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, short c, short col) override;
		virtual void DrawCircle(const glm::vec2& pos, int r, short c, short col) override;
		virtual void FillCircle(const glm::vec2& pos, int r, short c, short col) override;
		virtual void DrawSprite(const glm::vec2& pos, const SpriteInfo& sprite) override;
		virtual void DrawPartialSprite(const glm::vec2& pos, const SpriteInfo& sprite, const glm::vec2& opos, const glm::vec2& size) override;
		virtual void DrawWireFrameModel(const std::vector<glm::vec2>& vecModelCoordinates, const glm::vec2& pos, float r, float s, short col, short c) override;

	private:

		void Clip(glm::vec2& pos);

	private:

		COLOR m_Color = BG_BLACK;

	};
}

