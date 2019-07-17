#include "gepch.h"
#include "ConsoleRendererAPI.h"

namespace GameEngine
{

	void ConsoleRendererAPI::SetClearColor(const glm::vec4& color)
	{
	}

	void ConsoleRendererAPI::Clear()
	{
	}

	void ConsoleRendererAPI::DrawChar(const glm::vec2& pos, short c, short col)
	{
	}

	void ConsoleRendererAPI::Fill(const glm::vec2& startPos, const glm::vec2& endPos, short c, short col)
	{
	}

	void ConsoleRendererAPI::DrawString(const glm::vec2& pos, std::wstring c, short col)
	{
	}

	void ConsoleRendererAPI::DrawStringAlpha(const glm::vec2& pos, std::wstring c, short col)
	{
	}

	void ConsoleRendererAPI::DrawLine(const glm::vec2& startPos, const glm::vec2& endPos, short c, short col)
	{
	}

	void ConsoleRendererAPI::DrawTriangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, short c, short col)
	{
	}

	void ConsoleRendererAPI::FillTriangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, short c, short col)
	{
	}

	void ConsoleRendererAPI::DrawCircle(const glm::vec2& pos, int r, short c, short col)
	{
	}

	void ConsoleRendererAPI::FillCircle(const glm::vec2& pos, int r, short c, short col)
	{
	}

	void ConsoleRendererAPI::DrawSprite(const glm::vec2& pos, const Sprite& sprite)
	{
	}

	void ConsoleRendererAPI::DrawPartialSprite(const glm::vec2& pos, const Sprite& sprite, const glm::vec2& opos, const glm::vec2& size)
	{
	}

	void ConsoleRendererAPI::DrawWireFrameModel(const std::vector<glm::vec2>& vecModelCoordinates, const glm::vec2& pos, float r, float s, short col, short c)
	{
	}

}