#include "gepch.h"
#include "SpriteManager.h"

#include <fstream>

namespace GameEngine
{

	void SpriteManager::Create(size_t width, size_t height, SpriteInfo& spriteInfo)
	{
		int size = width * height;
		spriteInfo.size.x = width;
		spriteInfo.size.y = height;
		spriteInfo.glyphs = std::vector<short>(size);
		spriteInfo.colors = std::vector<short>(size);

		for (int i = 0; i < size; i++)
		{
			spriteInfo.glyphs[i] = L' ';
			spriteInfo.colors[i] = FG_BLUE;
		}
	}

	SpriteInfo* SpriteManager::LoadSprite(std::wstring fileName)
	{
		std::ifstream myfile(fileName);

		/*
		if (myfile.is_open())
		{
			size_t lineNum = 0;
			std::string line;

			size_t nWidth = 0;
			size_t nHeight = 0;

			SpriteInfo* spriteInfo = new SpriteInfo();

			while (std::getline(myfile, line))
			{
				if (lineNum == 0 && line.size() < 2) break;
				if (lineNum == 0)
				{
					std::vector<std::string> components;
					components = SplitStr(line, ' ');
					nWidth = std::stoi(components[0]);
					nHeight = std::stoi(components[1]);
					Create(nWidth, nHeight, *spriteInfo);
				}
				else if (lineNum <= nHeight + 1)
				{
					size_t cNum = 0;
					for (char const& c : line)
					{
						spriteInfo->glyphs[(lineNum - 1) * nWidth + cNum++] = c;
					}
				}
				else if (lineNum <= nHeight * 2 + 1)
				{
					size_t cNum = 0;
					for (char const& c : line)
					{
						spriteInfo->glyphs[(lineNum / 2 - 1) * nWidth + cNum++] = c;
					}
				}
				lineNum++;
			}
			myfile.close();
			return spriteInfo;
		}
		else
			GE_CORE_ASSERT(nullptr, "File '{0}' was not able to be opened!", fileName);
		*/
		return nullptr;
	}

	void SpriteManager::Draw(const SpriteInfo& sprite)
	{

	}

}