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
		inline self_type operator++() { ptr_++; return *this; }
		inline self_type operator++(int junk) { self_type i = *this; ptr_++; return i; }
		inline reference operator*() { return *ptr_; }
		inline pointer operator->() { return ptr_; }
		inline bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		inline bool operator!=(const self_type& rhs) { return !operator==(rhs); }

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
		inline self_type operator++() { ptr_++; return *this; }
		inline self_type operator++(int junk) { self_type i = *this; ptr_++; return i; }
		inline const reference operator*() { return *ptr_; }
		inline const pointer operator->() { return ptr_; }
		inline bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		inline bool operator!=(const self_type& rhs) { return !operator==(rhs); }

	};
	//using const_iterator = ConstTreeSetIter

private:

	size_type size_;
	std::unique_ptr<T[]> m_set;

public:

	TreeSet() = default;

	TreeSet(size_type size);

	TreeSet(std::initializer_list<T> list);

	~TreeSet();

	inline size_type size() const { return size_; }

	inline T& operator[](size_type index)
	{
		assert(index < size_);
		return m_set.get()[index];
	}

	inline const T& operator[](size_type index) const
	{
		assert(index < size_);
		return m_set.get()[index];
	}

	inline bool operator==(const TreeSet& rhs) const
	{
		if (size_ != rhs.size())
			return false;
		for (int i = 0; i < size_; i++)
		{
			if (this[i] != rhs[i])
				return false;
		}
		return true;
	}

	inline bool operator!=(const TreeSet& rhs) const
	{
		return !operator==(rhs);
	}

	// Resize is broken right now
	T& Resize(size_type size);

	inline iterator begin() { return iterator(std::next(m_set.get(), 0)); }
	inline iterator end() { return iterator(std::next(m_set.get(), size_)); }

	inline const_iterator cbegin() const { return const_iterator(std::next(m_set.get(), 0)); }
	inline const_iterator cend() const { return const_iterator(std::next(m_set.get(), size_)); }

};

template<typename T>
extern void Qsort(T* tmp, size_t len, size_t start);
