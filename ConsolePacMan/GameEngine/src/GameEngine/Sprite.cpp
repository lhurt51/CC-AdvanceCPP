#include "gepch.h"
#include "Sprite.h"

#include <fstream>

namespace GameEngine
{
	Sprite::~Sprite()
	{
		if (m_Glyphs) delete[] m_Glyphs;
		if (m_Colors) delete[] m_Colors;
	}

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

	bool Sprite::Save(const std::wstring sFile)
	{
		return false;
	}

	bool Sprite::Load(const std::wstring sFile)
	{
		size_t lineNum = 0;
		std::string line;
		std::ifstream myfile(sFile);

		if (m_Glyphs) delete[] m_Glyphs;
		if (m_Colors) delete[] m_Colors;
		nWidth = 0;
		nHeight = 0;

		if (myfile.is_open())
		{
			while (std::getline(myfile, line))
			{
				//if (line.size() < 2) break;
				
				if (lineNum == 0)
				{
					std::vector<std::string> components;
					components = SplitStr(line, ' ');
					nWidth = std::stoi(components[0]);
					nHeight = std::stoi(components[1]);
					Create(nWidth, nHeight);
				}
				else if (lineNum <= (size_t)(nHeight + 1))
				{
					size_t cNum = 0;
					for (char const &c : line)
					{
						m_Glyphs[(lineNum - 1) * nWidth + cNum++] = c;
					}
				}
				else if (lineNum <= (size_t)(nHeight * 2 + 1))
				{
					size_t cNum = 0;
					for (char const& c : line)
					{
						m_Glyphs[(lineNum / 2 - 1) * nWidth + cNum++] = c;
					}
				}
				lineNum++;
			}
			myfile.close();
			return true;
		}
		else std::cout << "Unable to open file" << std::endl;
		return false;
	}

	bool Sprite::Saveb(std::wstring sFile)
	{
		FILE* f = nullptr;
		_wfopen_s(&f, sFile.c_str(), L"wb");
		if (f == nullptr)
		{
			perror("fopen");
			exit(EXIT_FAILURE);
			return false;
		}

		int size = nWidth * nHeight;

		fwrite(&nWidth, sizeof(int), 1, f);
		fwrite(&nHeight, sizeof(int), 1, f);
		fwrite(m_Colors, sizeof(short), size, f);
		fwrite(m_Glyphs, sizeof(short), size, f);

		fclose(f);
		return true;
	}

	bool Sprite::Loadb(std::wstring sFile)
	{
		delete[] m_Glyphs;
		delete[] m_Colors;
		nWidth = 0;
		nHeight = 0;

		FILE* f = nullptr;
		_wfopen_s(&f, sFile.c_str(), L"rb");
		if (f == nullptr)
		{
			perror("fopen");
			exit(EXIT_FAILURE);
			return false;
		}

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
			m_Colors[i] = FG_BLUE;
		}
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

}
