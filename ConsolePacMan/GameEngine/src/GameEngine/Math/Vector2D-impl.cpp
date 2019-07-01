#include "gepch.h"
#include "Vector.cpp"

namespace GameEngine
{
	// All the template implementations so I can use all arithmetic data types
	template class							Vector2D<int>;
	template class							Vector2D<unsigned int>;
	template class							Vector2D<short>;
	template class							Vector2D<unsigned short>;
	template class							Vector2D<long>;
	template class							Vector2D<unsigned long>;
	template class							Vector2D<long long>;
	template class							Vector2D<unsigned long long>;
	template class							Vector2D<double>;
	template class							Vector2D<float>;
	template int							DotProduct(const Vector2D<int>& a, const Vector2D<int>& b);
	template unsigned int					DotProduct(const Vector2D<unsigned int>& a, const Vector2D<unsigned int>& b);
	template short							DotProduct(const Vector2D<short>& a, const Vector2D<short>& b);
	template unsigned short					DotProduct(const Vector2D<unsigned short>& a, const Vector2D<unsigned short>& b);
	template long							DotProduct(const Vector2D<long>& a, const Vector2D<long>& b);
	template unsigned long					DotProduct(const Vector2D<unsigned long>& a, const Vector2D<unsigned long>& b);
	template long long						DotProduct(const Vector2D<long long>& a, const Vector2D<long long>& b);
	template unsigned long long				DotProduct(const Vector2D<unsigned long long>& a, const Vector2D<unsigned long long>& b);
	template double							DotProduct(const Vector2D<double>& a, const Vector2D<double>& b);
	template float							DotProduct(const Vector2D<float>& a, const Vector2D<float>& b);
	template int							CrossProduct(const Vector2D<int>& a, const Vector2D<int>& b);
	template unsigned int					CrossProduct(const Vector2D<unsigned int>& a, const Vector2D<unsigned int>& b);
	template short							CrossProduct(const Vector2D<short>& a, const Vector2D<short>& b);
	template unsigned short					CrossProduct(const Vector2D<unsigned short>& a, const Vector2D<unsigned short>& b);
	template long							CrossProduct(const Vector2D<long>& a, const Vector2D<long>& b);
	template unsigned long					CrossProduct(const Vector2D<unsigned long>& a, const Vector2D<unsigned long>& b);
	template long long						CrossProduct(const Vector2D<long long>& a, const Vector2D<long long>& b);
	template unsigned long long				CrossProduct(const Vector2D<unsigned long long>& a, const Vector2D<unsigned long long>& b);
	template double							CrossProduct(const Vector2D<double>& a, const Vector2D<double>& b);
	template float							CrossProduct(const Vector2D<float>& a, const Vector2D<float>& b);
	template float							EuclideanNorm(const Vector2D<float>& v);
	template Vector2D<float>				Normal(const Vector2D<float>& v);
	template Vector2D<int>					Perpendicular(const Vector2D<int>& v);
	template Vector2D<unsigned int>			Perpendicular(const Vector2D<unsigned int>& v);
	template Vector2D<short>				Perpendicular(const Vector2D<short>& v);
	template Vector2D<unsigned short>		Perpendicular(const Vector2D<unsigned short>& v);
	template Vector2D<long>					Perpendicular(const Vector2D<long>& v);
	template Vector2D<unsigned long>		Perpendicular(const Vector2D<unsigned long>& v);
	template Vector2D<long long>			Perpendicular(const Vector2D<long long>& v);
	template Vector2D<unsigned long long>	Perpendicular(const Vector2D<unsigned long long>& v);
	template Vector2D<double>				Perpendicular(const Vector2D<double>& v);
	template Vector2D<float>				Perpendicular(const Vector2D<float>& v);
	template bool							Inersect(const Vector2D<int>& line1A, const Vector2D<int>& line1B, const Vector2D<int>& line2A, const Vector2D<int>& line2B);
	template bool							Inersect(const Vector2D<unsigned int>& line1A, const Vector2D<unsigned int>& line1B, const Vector2D<unsigned int>& line2A, const Vector2D<unsigned int>& line2B);
	template bool							Inersect(const Vector2D<short>& line1A, const Vector2D<short>& line1B, const Vector2D<short>& line2A, const Vector2D<short>& line2B);
	template bool							Inersect(const Vector2D<unsigned short>& line1A, const Vector2D<unsigned short>& line1B, const Vector2D<unsigned short>& line2A, const Vector2D<unsigned short>& line2B);
	template bool							Inersect(const Vector2D<long>& line1A, const Vector2D<long>& line1B, const Vector2D<long>& line2A, const Vector2D<long>& line2B);
	template bool							Inersect(const Vector2D<unsigned long>& line1A, const Vector2D<unsigned long>& line1B, const Vector2D<unsigned long>& line2A, const Vector2D<unsigned long>& line2B);
	template bool							Inersect(const Vector2D<long long>& line1A, const Vector2D<long long>& line1B, const Vector2D<long long>& line2A, const Vector2D<long long>& line2B);
	template bool							Inersect(const Vector2D<unsigned long long>& line1A, const Vector2D<unsigned long long>& line1B, const Vector2D<unsigned long long>& line2A, const Vector2D<unsigned long long>& line2B);
	template bool							Inersect(const Vector2D<double>& line1A, const Vector2D<double>& line1B, const Vector2D<double>& line2A, const Vector2D<double>& line2B);
	template bool							Inersect(const Vector2D<float>& line1A, const Vector2D<float>& line1B, const Vector2D<float>& line2A, const Vector2D<float>& line2B);
	template Vector2D<int>					GetInersect(const Vector2D<int>& line1A, const Vector2D<int>& line1B, const Vector2D<int>& line2A, const Vector2D<int>& line2B);
	template Vector2D<unsigned int>			GetInersect(const Vector2D<unsigned int>& line1A, const Vector2D<unsigned int>& line1B, const Vector2D<unsigned int>& line2A, const Vector2D<unsigned int>& line2B);
	template Vector2D<short>				GetInersect(const Vector2D<short>& line1A, const Vector2D<short>& line1B, const Vector2D<short>& line2A, const Vector2D<short>& line2B);
	template Vector2D<unsigned short>		GetInersect(const Vector2D<unsigned short>& line1A, const Vector2D<unsigned short>& line1B, const Vector2D<unsigned short>& line2A, const Vector2D<unsigned short>& line2B);
	template Vector2D<long>					GetInersect(const Vector2D<long>& line1A, const Vector2D<long>& line1B, const Vector2D<long>& line2A, const Vector2D<long>& line2B);
	template Vector2D<unsigned long>		GetInersect(const Vector2D<unsigned long>& line1A, const Vector2D<unsigned long>& line1B, const Vector2D<unsigned long>& line2A, const Vector2D<unsigned long>& line2B);
	template Vector2D<long long>			GetInersect(const Vector2D<long long>& line1A, const Vector2D<long long>& line1B, const Vector2D<long long>& line2A, const Vector2D<long long>& line2B);
	template Vector2D<unsigned long long>	GetInersect(const Vector2D<unsigned long long>& line1A, const Vector2D<unsigned long long>& line1B, const Vector2D<unsigned long long>& line2A, const Vector2D<unsigned long long>& line2B);
	template Vector2D<double>				GetInersect(const Vector2D<double>& line1A, const Vector2D<double>& line1B, const Vector2D<double>& line2A, const Vector2D<double>& line2B);
	template Vector2D<float>				GetInersect(const Vector2D<float>& line1A, const Vector2D<float>& line1B, const Vector2D<float>& line2A, const Vector2D<float>& line2B);
}
