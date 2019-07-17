#include "gepch.h"
#include "ConsoleRendererAPI.h"

#include "GameEngine/Application.h"
#include "Platform/Windows/WindowsWindow.h"

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
		const WindowsWindow::WindowData* data = (const WindowsWindow::WindowData*)Application::Get().GetWindow().GetWindowInfo();
		if (pos.x >= 0 && pos.x <  data->Width && pos.y >= 0 && pos.y < data->Height)
		{
			data->m_bufScreen[(int)(pos.y * data->Width + pos.x)].Char.UnicodeChar = c;
			data->m_bufScreen[(int)(pos.y * data->Width + pos.x)].Attributes = col;
		}
	}

	void ConsoleRendererAPI::Fill(const glm::vec2& startPos, const glm::vec2& endPos, short c, short col)
	{
		glm::vec2 tmp1 = startPos;
		glm::vec2 tmp2 = endPos;
		Clip(tmp1);
		Clip(tmp2);
		for (int x = tmp1.x; x < tmp2.x; x++)
			for (int y = tmp1.y; y < tmp2.y; y++)
				DrawChar({ x, y }, c, col);
	}

	void ConsoleRendererAPI::DrawString(const glm::vec2& pos, std::wstring c, short col)
	{
		const WindowsWindow::WindowData* data = (const WindowsWindow::WindowData*)Application::Get().GetWindow().GetWindowInfo();
		for (size_t i = 0; i < c.size(); i++)
		{
			data->m_bufScreen[(int)(pos.y * data->Width + pos.x + i)].Char.UnicodeChar = c[i];
			data->m_bufScreen[(int)(pos.y * data->Width + pos.x + i)].Attributes = col;
		}
	}

	void ConsoleRendererAPI::DrawStringAlpha(const glm::vec2& pos, std::wstring c, short col)
	{
		const WindowsWindow::WindowData* data = (const WindowsWindow::WindowData*)Application::Get().GetWindow().GetWindowInfo();
		for (size_t i = 0; i < c.size(); i++)
		{
			if (c[i] != L' ')
			{
				data->m_bufScreen [(int)(pos.y * data->Width + pos.x + i)].Char.UnicodeChar = c[i];
				data->m_bufScreen [(int)(pos.y * data->Width + pos.x + i)].Attributes = col;
			}
		}
	}

	void ConsoleRendererAPI::DrawLine(const glm::vec2& startPos, const glm::vec2& endPos, short c, short col)
	{
		int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

		dx = endPos.x - startPos.x;
		dy = endPos.y - startPos.y;
		dx1 = abs(dx);
		dy1 = abs(dy);
		px = 2 * dy1 - dx1;
		py = 2 * dx1 - dy1;

		if (dy1 <= dx1)
		{
			if (dx >= 0)
			{
				x = startPos.x;
				y = startPos.y;
				xe = endPos.x;
			}
			else
			{
				x = endPos.x;
				y = endPos.y;
				xe = startPos.x;
			}

			DrawChar({ x, y }, c, col);

			for (i = 0; x < xe; i++)
			{
				x = x + 1;
				if (px < 0)
					px = px + 2 * dy1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
						y = y + 1;
					else
						y = y - 1;
					px = px + 2 * (dy1 - dx1);
				}
				DrawChar({ x, y }, c, col);
			}
		}
		else
		{
			if (dy >= 0)
			{
				x = startPos.x;
				y = startPos.y;
				ye = endPos.y;
			}
			else
			{
				x = endPos.x;
				y = endPos.y;
				ye = startPos.y;
			}
			DrawChar({ x, y }, c, col);

			for (i = 0; y < ye; i++)
			{
				y = y + 1;
				if (py <= 0)
					py = py + 2 * dx1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
						x = x + 1;
					else
						x = x - 1;
					py = py + 2 * (dx1 - dy1);
				}
				DrawChar({ x, y }, c, col);
			}
		}
	}

	void ConsoleRendererAPI::DrawTriangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, short c, short col)
	{
		DrawLine(p1, p2, c, col);
		DrawLine(p2, p3, c, col);
		DrawLine(p3, p1, c, col);
	}

	// https://www.avrfreaks.net/sites/default/files/triangles.c
	void ConsoleRendererAPI::FillTriangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, short c, short col)
	{
		auto SWAP = [](float& x, float& y) { float t = x; x = y; y = t; };
		auto drawline = [&](int sx, int ex, int ny) { for (int i = sx; i <= ex; i++) DrawChar({ i, ny }, c, col); };

		int t1x, t2x, y, minx, maxx, t1xp, t2xp;
		bool changed1 = false;
		bool changed2 = false;
		int signx1, signx2, dx1, dy1, dx2, dy2;
		int e1, e2;

		glm::vec2 tmp1 = p1;
		glm::vec2 tmp2 = p2;
		glm::vec2 tmp3 = p3;

		// Sort vertices
		if (tmp1.y > tmp2.y) { SWAP(tmp1.y, tmp2.y); SWAP(tmp1.x, tmp2.x); }
		if (tmp1.y > tmp3.y) { SWAP(tmp1.y, tmp3.y); SWAP(tmp1.x, tmp3.x); }
		if (tmp2.y > tmp3.y) { SWAP(tmp2.y, tmp3.y); SWAP(tmp2.x, tmp3.x); }

		t1x = t2x = tmp1.x; y = tmp1.y;   // Starting points
		dx1 = (int)(tmp2.x - tmp1.x); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (int)(tmp2.y - tmp1.y);

		dx2 = (int)(tmp3.x - tmp1.x); if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
		else signx2 = 1;
		dy2 = (int)(tmp3.y - tmp1.y);

		if (dy1 > dx1) {   // swap values
			SWAP((float&)dx1, (float&)dy1);
			changed1 = true;
		}
		if (dy2 > dx2) {   // swap values
			SWAP((float&)dy2, (float&)dx2);
			changed2 = true;
		}

		e2 = (int)(dx2 >> 1);
		// Flat top, just process the second half
		if (tmp1.y == tmp2.y) goto next;
		e1 = (int)(dx1 >> 1);

		for (int i = 0; i < dx1;) {
			t1xp = 0; t2xp = 0;
			if (t1x < t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			// process first line until y value is about to change
			while (i < dx1) {
				i++;
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) t1xp = signx1;//t1x += signx1;
					else          goto next1;
				}
				if (changed1) break;
				else t1x += signx1;
			}
			// Move line
		next1:
			// process second line until y value is about to change
			while (1) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;//t2x += signx2;
					else          goto next2;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next2:
			if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;
			if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;
			drawline(minx, maxx, y);    // Draw line from min to max points found on the y
										 // Now increase y
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y == tmp2.y) break;

		}
	next:
		// Second half
		dx1 = (int)(tmp3.x - tmp2.x); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (int)(tmp3.y - tmp2.y);
		t1x = tmp2.x;

		if (dy1 > dx1) {   // swap values
			SWAP((float&)dy1, (float&)dx1);
			changed1 = true;
		}
		else changed1 = false;

		e1 = (int)(dx1 >> 1);

		for (int i = 0; i <= dx1; i++) {
			t1xp = 0; t2xp = 0;
			if (t1x < t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			// process first line until y value is about to change
			while (i < dx1) {
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) { t1xp = signx1; break; }//t1x += signx1;
					else          goto next3;
				}
				if (changed1) break;
				else   	   	  t1x += signx1;
				if (i < dx1) i++;
			}
		next3:
			// process second line until y value is about to change
			while (t2x != tmp3.x) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;
					else          goto next4;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next4:

			if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;
			if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;
			drawline(minx, maxx, y);
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y > tmp3.y) return;
		}
	}

	void ConsoleRendererAPI::DrawCircle(const glm::vec2& pos, int r, short c, short col)
	{
		int x = 0;
		int y = r;
		int p = 3 - 2 * r;

		if (!r) return;
		while (y >= x)
		{
			DrawChar({ pos.x - x, pos.y - y }, c, col); // Upper left left
			DrawChar({ pos.x - y, pos.y - x }, c, col); // Upper upper left
			DrawChar({ pos.x + y, pos.y - x }, c, col); // Upper upper right
			DrawChar({ pos.x + x, pos.y - y }, c, col); // Upper right right
			DrawChar({ pos.x - x, pos.y + y }, c, col); // Lower left left
			DrawChar({ pos.x - y, pos.y + x }, c, col); // Lower lower left
			DrawChar({ pos.x + y, pos.y + x }, c, col); // Lower lower right
			DrawChar({ pos.x + x, pos.y + y }, c, col); // Lower right right
			if (p < 0) p += 4 * x++ + 6;
			else p += 4 * (x++ - y--) + 10;
		}
	}

	void ConsoleRendererAPI::FillCircle(const glm::vec2& pos, int r, short c, short col)
	{
		int x = 0;
		int y = r;
		int p = 3 - 2 * r;

		if (!r) return;
		auto drawline = [&](int sx, int ex, int ny)
		{
			for (int i = sx; i <= ex; i++)
				DrawChar({ i, ny }, c, col);
		};

		// Draws by using scan-lines
		while (y >= x)
		{
			drawline(pos.x - x, pos.x + x, pos.y - y);
			drawline(pos.x - y, pos.x + y, pos.y - x);
			drawline(pos.x - x, pos.x + x, pos.y + y);
			drawline(pos.x - y, pos.x + y, pos.y + x);
			if (p < 0) p += 4 * x++ + 6;
			else p += 4 * (x++ - y--) + 10;
		}
	}

	void ConsoleRendererAPI::DrawSprite(const glm::vec2& pos, const Sprite& sprite)
	{
		for (int i = 0; i < sprite.nWidth; i++)
		{
			for (int j = 0; j < sprite.nHeight; j++)
			{
				if (sprite.GetGlyph(i, j) != L' ')
					DrawChar({ pos.x + i, pos.y + j }, sprite.GetGlyph(i, j), sprite.GetColor(i, j));
			}
		}
	}

	void ConsoleRendererAPI::DrawPartialSprite(const glm::vec2& pos, const Sprite& sprite, const glm::vec2& opos, const glm::vec2& size)
	{
	}

	void ConsoleRendererAPI::DrawWireFrameModel(const std::vector<glm::vec2>& vecModelCoordinates, const glm::vec2& pos, float r, float s, short col, short c)
	{
	}

	void ConsoleRendererAPI::Clip(glm::vec2& pos)
	{
		const WindowsWindow::WindowData* data = (const WindowsWindow::WindowData*)Application::Get().GetWindow().GetWindowInfo();
		if (pos.x < 0) pos.x = 0;
		if (pos.x > data->Width) pos.x = data->Width;
		if (pos.y < 0) pos.y = 0;
		if (pos.y > data->Height) pos.y = data->Height;
	}

}