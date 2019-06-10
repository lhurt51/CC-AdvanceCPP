#pragma once

#include <iostream>
#include <memory>
#include <iterator>
#include <cassert>
#include <cstdarg>
#include <initializer_list>

/*
// Cannot seem to make the unique pointer use my custom deleter
auto deleter = [](auto p) { delete[] p; };

// Issues aliasing the iterators
template<typename T>
using iterator = TreeSetIter<T>;

template<typename T>
class TreeSetIter
{
public:

	typedef iterator self_type;
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef std::forward_iterator_tag iterator_category;
	typedef int difference_type;

private:

	pointer ptr_;

public:

	iterator(pointer ptr) : ptr_(ptr) {}
	self_type operator++() { ptr_++; return *this; }
	self_type operator++(int junk) { self_type i = *this; ptr_++; return i; }
	reference operator*() { return *ptr_; }
	pointer operator->() { return ptr_; }
	bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
	bool operator!=(const self_type& rhs) { return !operator==(rhs); }

};
*/

template<typename T> void Qsort(T& tmp, size_t len, size_t start);

template <typename T>
class TreeSet
{

public:

	typedef size_t size_type;

	class iterator
	{
	public:

		typedef iterator self_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;

	private:

		pointer ptr_;

	public:

		iterator(pointer ptr) : ptr_(ptr) {}
		self_type operator++() { ptr_++; return *this; }
		self_type operator++(int junk) { self_type i = *this; ptr_++; return i; }
		reference operator*() { return *ptr_; }
		pointer operator->() { return ptr_; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return !operator==(rhs); }

	};
	//using iterator = TreeSetIter;

	class const_iterator
	{
	public:

		typedef const_iterator self_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;

	private:

		pointer ptr_;

	public:

		const_iterator(pointer ptr) : ptr_(ptr) {}
		self_type operator++() { ptr_++; return *this; }
		self_type operator++(int junk) { self_type i = *this; ptr_++; return i; }
		const reference operator*() { return *ptr_; }
		const pointer operator->() { return ptr_; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return !operator==(rhs); }

	};
	//using const_iterator = ConstTreeSetIter

private:

	size_type size_;
	std::unique_ptr<T[]> m_set;

public:

	TreeSet() = default;

	TreeSet(size_type size) : size_(size)
	{
		m_set = std::make_unique<T[]>(size_);
	}

	TreeSet(std::initializer_list<T> list) : size_(list.size())
	{
		size_type i = 0;
		m_set = std::make_unique<T[]>(size_);
		for (auto it = list.begin(); it != list.end(); it++)
		{
			m_set[i++] = *it;
		}
		Qsort<T>(m_set.get(), size_ - 1, 0);
	}

	~TreeSet()
	{
		//m_set.reset(nullptr);
	}

	size_type size() const { return size_; }

	T& operator[](size_type index)
	{
		assert(index < size_);
		return m_set.get()[index];
	}

	const T& operator[](size_type index) const
	{
		assert(index < size_);
		return m_set.get()[index];
	}



	// Resize is broken right now
	T& resize(size_type size)
	{
		std::unique_ptr<T[]> tmp = std::make_unique<T[]>(size);
		tmp.swap(m_set);
		for (int j = 0; j < size_; j++)
			std::swap(m_set[j], tmp[j]);
		size_ = size;
		Qsort<T>(m_set.get(), size_ - 1, 0);
		//tmp.reset(nullptr);
		return *m_set.get();
	}

	iterator begin()
	{
		return iterator(std::next(m_set.get(), 0));
	}

	iterator end()
	{
		return iterator(std::next(m_set.get(), size_));
	}

	const_iterator cbegin() const
	{
		return const_iterator(std::next(m_set.get(), 0));
	}

	const_iterator cend() const
	{
		return const_iterator(std::next(m_set.get(), size_));
	}

};

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
			while (tmp[j] > tmp[piv])
				j--;
			if (i < j)
			{
				std::swap(tmp[i], tmp[j]);
			}
		}
		std::swap(tmp[piv], tmp[j]);
		Qsort<T>(tmp, j - 1, start);
		Qsort<T>(tmp, len, j + 1);
	}
}