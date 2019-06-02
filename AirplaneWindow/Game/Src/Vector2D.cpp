#include "Vector2D.h"

Vector2D::Vector2D()
{
	zero();
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}


Vector2D::~Vector2D()
{
	return;
}

Vector2D & Vector2D::add(const Vector2D & vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D & Vector2D::subtract(const Vector2D & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D & Vector2D::multiply(const Vector2D & vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D & Vector2D::divide(const Vector2D & vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector2D & Vector2D::operator+=(const Vector2D & vec)
{
	return this->add(vec);
}

Vector2D & Vector2D::operator-=(const Vector2D & vec)
{
	return this->subtract(vec);
}

Vector2D & Vector2D::operator*=(const Vector2D & vec)
{
	return this->multiply(vec);
}

Vector2D & Vector2D::operator/=(const Vector2D & vec)
{
	return this->divide(vec);
}

Vector2D & Vector2D::operator*(const int & i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}

Vector2D & Vector2D::zero(void)
{
	this->x = 0.0f;
	this->y = 0.0f;
	return *this;
}

Vector2D & operator+(Vector2D & lhs, const Vector2D & rhs)
{
	return lhs.add(rhs);
}

Vector2D & operator-(Vector2D & lhs, const Vector2D & rhs)
{
	return lhs.subtract(rhs);
}

Vector2D & operator*(Vector2D & lhs, const Vector2D & rhs)
{
	return lhs.multiply(rhs);
}

Vector2D & operator/(Vector2D & lhs, const Vector2D & rhs)
{
	return lhs.divide(rhs);
}

std::ostream & operator<<(std::ostream & stream, const Vector2D & vec)
{
	return stream << "(" << vec.x << "," << vec.y << ")";
}
