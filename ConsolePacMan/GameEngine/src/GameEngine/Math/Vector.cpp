#include "gepch.h"
#include "Vector.h"

namespace GameEngine
{

	// Initialize the vector to 0, 0
	template<typename T>
	Vector2D<T>::Vector2D(void) : x(T(0)), y(T(0))
	{
		return;
	}

	// Initializes the vector to be the int provided
	template<typename T>
	Vector2D<T>::Vector2D(const T& xyIn) : x(xyIn), y(xyIn)
	{
		return;
	}

	// Uses input to assign the values x, y as the vector
	template<typename T>
	Vector2D<T>::Vector2D(const T& xIn, const T& yIn) : x(xIn), y(yIn)
	{
		return;
	}

	// Only uses first two elements not catches for wrong initialization
	template<typename T>
	Vector2D<T>::Vector2D(std::initializer_list<T> list)
	{
		int size = 0;
		for (auto it = list.begin(); it != list.end(); it++)
			if (size < 2)
				((size++ == 0) ? x : y) = *it;
			else
				break;
		if (size < 1)
			x = 0;
		if (size < 2)
			y = 0;
		return;
	}

	// Copying another vector into this one
	template<typename T>
	Vector2D<T>::Vector2D(const Vector2D& src)
	{
		*this = src;
	}

	// Overload operators --
	template<typename T>
	Vector2D<T>& Vector2D<T>::operator=(const Vector2D& v) {
		if (this != &v) {
			x = v.x;
			y = v.y;
		}
		return *this;
	}

	template<typename T>
	Vector2D<T>& Vector2D<T>::operator+=(const Vector2D& v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	template<typename T>
	Vector2D<T>& Vector2D<T>::operator-=(const Vector2D& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	template<typename T>
	Vector2D<T>& Vector2D<T>::operator*=(const Vector2D& v) {
		x *= v.x;
		y *= v.y;
		return *this;
	}

	template<typename T>
	Vector2D<T>& Vector2D<T>::operator/=(const Vector2D& v) {
		x /= v.x;
		y /= v.y;
		return *this;
	}

	template<typename T>
	Vector2D<T>& Vector2D<T>::operator*=(const T& s) {
		x *= s;
		y *= s;
		return *this;
	}

	template<typename T>
	Vector2D<T>& Vector2D<T>::operator/=(const T& s) {
		x /= s;
		y /= s;
		return *this;
	}

	// Utility Functions
	template<typename T>
	T				DotProduct(const Vector2D<T>& a, const Vector2D<T>& b) {
		return ((a.x * b.x) + (a.y + b.y));
	}

	template<typename T>
	T				CrossProduct(const Vector2D<T>& a, const Vector2D<T>& b) {
		return ((a.x * b.y) - (a.y * b.x));
	}


	template<typename T>
	T				EuclideanNorm(const Vector2D<T>& v) {
		return std::sqrt((v.x * v.x) + (v.y * v.y));
	}

	template<typename T>
	Vector2D<T>		Normal(const Vector2D<T>& v) {
		float magnitude = EuclideanNorm(v);
		return Vector2D<T>(v.x / magnitude, v.y / magnitude);
	}

	template<typename T>
	Vector2D<T>		Perpendicular(const Vector2D<T>& v) {
		return Vector2D<T>(v.y, -v.x);
	}

	template<typename T>
	bool			Inersect(const Vector2D<T>& line1A, const Vector2D<T>& line1B, const Vector2D<T>& line2A, const Vector2D<T>& line2B) {
		Vector2D<T> p = line1A;
		Vector2D<T> r = line1B - line1A;
		Vector2D<T> q = line2A;
		Vector2D<T> s = line2B - line2A;

		float t = CrossProduct((q - p), s) / CrossProduct(r, s);
		float u = CrossProduct((q - p), r) / CrossProduct(r, s);

		return (0.0 <= t && t <= 1.0) && (0.0 <= u && u <= 1.0);
	}

	template<typename T>
	Vector2D<T>		GetInersect(const Vector2D<T>& line1A, const Vector2D<T>& line1B, const Vector2D<T>& line2A, const Vector2D<T>& line2B) {
		float pX = CrossProduct(line1A, line1B) * (line2A.x - line2B.x) -
			CrossProduct(line2A, line2B) * (line1A.x - line1B.x);
		float pY = CrossProduct(line1A, line1B) * (line2A.y - line2B.y) -
			CrossProduct(line2A, line2B) * (line1A.y - line1B.y);
		float denom = (line1A.x - line1B.x) * (line2A.y - line2B.y) -
			(line1A.y - line1B.y) * (line2A.x - line2B.x);
		return Vector2D<T>(pX / denom, pY / denom);
	}

}