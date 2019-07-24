#include "gepch.h"
#include "SpriteManager.h"

#include <fstream>

namespace GameEngine
{

	void SpriteInfo::Init(size_t width, size_t height)
	{
		size_t totalSize = width * height;
		size.x = width;
		size.y = height;
		glyphs = std::vector<short>(totalSize);
		colors = std::vector<short>(totalSize);

		for (int i = 0; i < totalSize; i++)
		{
			glyphs[i] = L' ';
			colors[i] = FG_BLUE;
		}
	}

	void SpriteInfo::SetGlyph(int x, int y, short c)
	{
		if (x < 0 || x >= size.x || y < 0 || y >= size.y)
			return;
		else
			glyphs[(y * (int)(size.y) + x)] = c;
	}

	void SpriteInfo::SetColor(int x, int y, short c)
	{
		if (x < 0 || x >= size.y || y < 0 || y >= size.y)
			return;
		else
			colors[(y * (int)(size.y) + x)] = c;
	}

	short SpriteInfo::GetGlyph(int x, int y) const
	{
		if (x < 0 || x >= size.x || y < 0 || y >= size.y)
			return L' ';
		else
			return glyphs[(y * (int)(size.y) + x)];
	}

	short SpriteInfo::GetColor(int x, int y) const
	{
		if (x < 0 || x >= size.x || y < 0 || y >= size.y)
			return FG_BLACK;
		else
			return colors[(y * (int)(size.y) + x)];
	}

	short SpriteInfo::SampleGlyph(float x, float y)
	{
		int sx = (int)(x * size.x);
		int sy = (int)(y * size.y - 1.0f);

		if (sx < 0 || sx >= size.x || sy < 0 || sy >= size.y)
			return L' ';
		else
			glyphs[(sy * (int)(size.y) + sx)];
	}

	short SpriteInfo::SampleColor(float x, float y)
	{
		int sx = (int)(x * size.x);
		int sy = (int)(y * size.y - 1.0f);

		if (sx < 0 || sx >= size.x || sy < 0 || sy >= size.y)
			return FG_BLACK;
		else
			return colors[(sy * (int)(size.y) + sx)];
	}

	// Global function to help me split strings
	std::vector<std::string>	SplitStr(const std::string& s, char const delimiter)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);

		while (std::getline(tokenStream, token, delimiter))
			tokens.push_back(token);
		return tokens;
	}

	SpriteInfo* SpriteManager::LoadSprite(std::wstring fileName)
	{
		std::ifstream myfile(fileName);

		if (myfile.is_open())
		{
			size_t lineNum = 0;
			std::string line;

			SpriteInfo* spriteInfo = new SpriteInfo();
			spriteInfo->size = { 0 };

			while (std::getline(myfile, line))
			{
				if (lineNum == 0 && line.size() < 2) break;
				if (lineNum == 0)
				{
					std::vector<std::string> components = SplitStr(line, ' ');
					spriteInfo->Init(std::stoi(components[0]), std::stoi(components[1]));
				}
				else if (lineNum <= spriteInfo->size.y + 1)
				{
					size_t cNum = 0;
					for (char const& c : line)
					{
						spriteInfo->glyphs[(lineNum - 1) * spriteInfo->size.x + cNum++] = (wchar_t)c;
					}
				}
				else if (lineNum <= spriteInfo->size.y * 2 + 1)
				{
					size_t cNum = 0;
					for (char const& c : line)
					{
						spriteInfo->glyphs[(lineNum / 2 - 1) * spriteInfo->size.x + cNum++] = (wchar_t)c;
					}
				}
				lineNum++;
			}
			myfile.close();
			return spriteInfo;
		}
		else
			GE_CORE_ASSERT(nullptr, "File '{0}' was not able to be opened!", std::string(fileName.begin(), fileName.end()));
		return nullptr;
	}

	void SpriteManager::Draw(const SpriteInfo& sprite)
	{

	}

}