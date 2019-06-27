#include "gepch.h"
#include "Sprite.h"

namespace GameEngine
{
	void Sprite::SetGlyph(int x, int y, short c)
	{
		if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
			return;
		else
			m_Glyphs[y * nWidth + x] = c;
	}

	void Sprite::SetColor(int x, int y, short c)
	{
		if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
			return;
		else
			m_Colors[y * nWidth + x] = c;
	}

	short Sprite::GetGlyph(int x, int y)
	{
		if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
			return L' ';
		else
			return m_Glyphs[y * nWidth + x];
	}

	short Sprite::GetColor(int x, int y)
	{
		if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
			return FG_BLACK;
		else
			return m_Colors[y * nWidth + x];
	}

	short Sprite::SampleGlyph(float x, float y)
	{
		int sx = (int)(x * (float)nWidth);
		int sy = (int)(y * (float)nHeight - 1.0f);

		if (sx < 0 || sx >= nWidth || sy < 0 || sy >= nHeight)
			return L' ';
		else
			m_Glyphs[sy * nWidth + sx];
	}

	short Sprite::SampleColor(float x, float y)
	{
		int sx = (int)(x * (float)nWidth);
		int sy = (int)(y * (float)nHeight - 1.0f);

		if (sx < 0 || sx >= nWidth || sy < 0 || sy >= nHeight)
			return FG_BLACK;
		else
			return m_Colors[sy * nWidth + sx];
	}

	bool Sprite::Save(std::wstring sFile)
	{
		FILE* f = nullptr;
		_wfopen_s(&f, sFile.c_str(), L"wb");
		if (f == nullptr) return false;

		int size = nWidth * nHeight;

		fwrite(&nWidth, sizeof(int), 1, f);
		fwrite(&nHeight, sizeof(int), 1, f);
		fwrite(m_Colors, sizeof(short), size, f);
		fwrite(m_Glyphs, sizeof(short), size, f);

		fclose(f);

		return true;
	}

	bool Sprite::Load(std::wstring sFile)
	{
		delete[] m_Glyphs;
		delete[] m_Colors;
		nWidth = 0;
		nHeight = 0;

		FILE* f = nullptr;
		_wfopen_s(&f, sFile.c_str(), L"rb");
		if (f == nullptr) return false;

		std::fread(&nWidth, sizeof(int), 1, f);
		std::fread(&nHeight, sizeof(int), 1, f);

		Create(nWidth, nHeight);

		int size = nWidth * nHeight;
		std::fread(m_Colors, sizeof(short), size, f);
		std::fread(m_Glyphs, sizeof(short), size, f);

		std::fclose(f);
		return true;
	}

	void Sprite::Create(int w, int h)
	{
		int size = w * h;
		nWidth = w;
		nHeight = h;
		m_Glyphs = new short[size];
		m_Colors = new short[size];

		for (int i = 0; i < size; i++)
		{
			m_Glyphs[i] = L' ';
			m_Colors[i] = FG_BLACK;
		}
	}

}
