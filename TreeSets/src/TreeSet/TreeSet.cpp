/*******************************************************************************\
* Programmer Name:																*
* Liam Hurt																		*
*																				*
* Date:																			*
* 06/08/2019																	*
*																				*
* Assignment Requirement:														*
* 	Tree sets and Initializer Lists												*
*	Since C++11, the STL collections support initialization from a list of		*
*		values, like this:														*
*																				*
*	// Initialize a vector of 7 integer values									*
*	vector<int> v = {1, 1, 2, 3, 5, 8, 13};										*
*																				*
*	// This syntax also works:													*
*	vector<int> v{1, 1, 2, 3, 5, 8, 13};										*
*	You can add list-initialization like this to your own classes by using the	*
*		std::initializer_list<T> type, declared in the <initializer_list> C++	*
*		standard header file. Just make a constructor that takes an				*
*		initializer-list of values of the appropriate type, and you will also	*
*		be able to initialize your tree-set like this:							*
*																				*
*	TreeSet s1 = {2, 3, 5};														*
*	TreeSet s2{2, 3, 5};														*
*	TreeSet Iteration															*
*	In-order tree traversal is not terribly difficult to implement, but it		*
*		is made more complicated by the standard C++ iterator abstraction,		*
*		which allows one to access the current element, or advance to the		*
*		next element. Your TreeSet class will need to provide functionality		*
*		similar to the C++ iterator abstraction, like this:						*
*																				*
*	TreeSet s{3, 5, 2, 1};														*
*																				*
*	TreeSet::iterator it = s.begin();											*
*	while (it != s.end()) {														*
*		cout << ' ' << *it;														*
*		it++;  // or ++it;														*
*	}																			*
*	This should print out the result "1 2 3 5"; in other words, the values are	*
*	traversed in increasing order.												*
*																				*
\*******************************************************************************/

#include "TreeSet.hpp"

#include <algorithm>

template<typename T>
TreeSet<T>::TreeSet(size_type size) : size_(size)
{
	// Creating space for the array
	m_set = std::make_unique<T[]>(size_);
}

template<typename T>
TreeSet<T>::TreeSet(std::initializer_list<T> list) : size_(list.size())
{
	// Using the list to fill out m_set
	size_type k = 0;
	m_set = std::make_unique<T[]>(size_);
	for (auto it = list.begin(); it != list.end(); it++)
	{
		m_set[k++] = *it;
	}
	// Sorting the set
	Qsort<T>(m_set.get(), size_ - 1, 0);
}

template<typename T>
TreeSet<T>::TreeSet(const TreeSet& src)
{
	*this = src;
}

template<typename T>
TreeSet<T>::~TreeSet()
{
	//m_set.reset(nullptr);
}

template<typename T>
bool TreeSet<T>::CheckForDup(T val, const std::vector<T>& intersects) const
{
	for (int l = 0; l < intersects.size(); l++)
	{
		if (intersects[l] == val)
			return true;
	}
	return false;
}

template<typename T>
TreeSet<T> TreeSet<T>::Intersects(const TreeSet& s) const
{
	std::vector<T> intersects;
	for (int i = 0; i < size_; i++)
	{
		for (int j = 0; j < s.size(); j++)
		{
			if (m_set[i] == s[j] && !CheckForDup(s[j], intersects))
			{
				intersects.push_back(s[j]);
			}
		}
	}
	TreeSet<T> rtn(intersects.size());
	for (int i = 0; i < intersects.size(); i++)
	{
		rtn[i] = intersects[i];
	}
	Qsort<T>(rtn.m_set.get(), rtn.size() - 1, 0);
	return rtn;
}

template<typename T>
TreeSet<T> TreeSet<T>::Plus(const TreeSet& s) const
{
	std::vector<T> plus;
	for (int i = 0; i < std::max(size_, s.size()); i++)
	{
		if (i < size_ && i < s.size())
			plus.push_back(m_set[i] + s[i]);
		else if (i < size_ && i >= s.size())
			plus.push_back(m_set[i]);
		else if (i >= size_ && i < s.size())
			plus.push_back(s[i]);
	}
	TreeSet<T> rtn(plus.size());
	for (int i = 0; i < plus.size(); i++)
	{
		rtn[i] = plus[i];
	}
	Qsort<T>(rtn.m_set.get(), rtn.size() - 1, 0);
	return rtn;
}

template<typename T>
TreeSet<T> TreeSet<T>::Minus(const TreeSet& s) const
{
	std::vector<T> minus;
	for (int i = 0; i < std::max(size_, s.size()); i++)
	{
		if (i < size_ && i < s.size())
			minus.push_back(m_set[i] - s[i]);
		else if (i < size_ && i >= s.size())
			minus.push_back(m_set[i] - T(0));
		else if (i >= size_ && i < s.size())
			minus.push_back(T(0) - s[i]);
	}
	TreeSet<T> rtn(minus.size());
	for (int i = 0; i < minus.size(); i++)
	{
		rtn[i] = minus[i];
	}
	Qsort<T>(rtn.m_set.get(), rtn.size() - 1, 0);
	return rtn;
}

template<typename T>
T& TreeSet<T>::Resize(size_type size)
{
	std::unique_ptr<T[]> tmp = std::make_unique<T[]>(size);
	tmp.swap(m_set);
	for (int j = 0; j < size_; j++)
		std::swap(m_set[j], tmp[j]);
	size_ = size;
	Qsort<T>(m_set.get(), size_ - 1, 0);
	return *m_set.get();
}

template<typename T>
void Qsort(T* tmp, size_t len, size_t start)
{
	size_t piv;
	size_t i;
	size_t j;

	if (start < len)
	{
		piv = start;
		i = start;
		j = len;
		while (i < j)
		{
			while (tmp[i] <= tmp[piv] && i <= len)
				i++;
			while (tmp[j] > tmp[piv] && j > 0)
				j--;
			if (i < j)
			{
				std::swap(tmp[i], tmp[j]);
			}
		}
		std::swap(tmp[piv], tmp[j]);
		Qsort<T>(tmp, (((int)(j - 1) < 0) ? 0 : j - 1), start);
		Qsort<T>(tmp, len, j + 1);
	}
}