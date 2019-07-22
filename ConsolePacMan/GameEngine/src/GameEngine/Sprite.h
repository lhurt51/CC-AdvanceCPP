#pragma once

#include <string>
#include <vector>

#include "Renderer/RendererColors.h"


// MUST REVISE THIS SPRITE CLASS TO ALLOW FOR BETTER
// MODIFICATION AND ADDING TO A LIST THROUGH GAME ENGINE
namespace GameEngine
{
	class Sprite
	{
	public:

		Sprite() = default;
		Sprite(int w, int h) { Create(w, h); }
		Sprite(std::wstring sFile) { if (!Load(sFile)) Create(8, 8); }
		Sprite(const Sprite& src) { if (this != &src) { *this = src; } }
		~Sprite();

		inline Sprite& operator=(const Sprite& rhs)
		{
			if (this != &rhs)
			{
				this->nHeight = rhs.nHeight;
				this->nWidth = rhs.nWidth;
				this->m_Glyphs = rhs.m_Glyphs;
				this->m_Colors = rhs.m_Colors;
			}
		}

		void SetGlyph(int x, int y, short c);
		void SetColor(int x, int y, short c);

		short GetGlyph(int x, int y) const;
		short GetColor(int x, int y) const;

		short SampleGlyph(float x, float y);
		short SampleColor(float x, float y);

		bool Save(const std::wstring sFile);
		bool Load(const std::wstring sFile);
		bool Saveb(std::wstring sFile);
		bool Loadb(std::wstring sFile);

	private:

		void Create(int w, int h);

	public:

		int nWidth = 0;
		int nHeight = 0;

	private:

		short* m_Glyphs = nullptr;
		short* m_Colors = nullptr;

	};

	std::vector<std::string>	SplitStr(const std::string& s, char const delimiter);
}

