#pragma once

#include <iostream>
#include <memory>
#include <iterator>
#include <cassert>
#include <cstdarg>
#include <initializer_list>
#include <vector>

/*
// Cannot seem to make the unique pointer use my custom deleter
auto deleter = [](auto p) { delete[] p; };
*/

template <typename T>
class TreeSet
{

public:

	// Creating an easy what for people to change the size type
	typedef size_t size_type;

	// Creating an iterator class for the set
	class iterator
	{
	public:

		// typedefs for ease
		typedef iterator self_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;

	private:

		pointer ptr_;

	public:

		// constructor
		iterator(pointer ptr) : ptr_(ptr) {}
		// operator overloads
		inline self_type& operator++() { ptr_++; return *this; }
		inline self_type operator++(int) { self_type i = *this; ptr_++; return i; }
		inline reference operator*() { return *ptr_; }
		inline pointer operator->() { return ptr_; }
		inline bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		inline bool operator!=(const self_type& rhs) { return !operator==(rhs); }

	};
	// Making it so you can use TreeSetIter or iterator
	using TreeSetIter = iterator;

	// Creating an const_iterator class for the set
	class const_iterator
	{
	public:

		// typedefs for ease
		typedef const_iterator self_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;

	private:

		pointer ptr_;

	public:

		// constructor
		const_iterator(pointer ptr) : ptr_(ptr) {}
		// operator overloads
		inline self_type& operator++() { ptr_++; return *this; }
		inline self_type operator++(int) { self_type i = *this; ptr_++; return i; }
		inline const reference operator*() { return *ptr_; }
		inline const pointer operator->() { return ptr_; }
		inline bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		inline bool operator!=(const self_type& rhs) { return !operator==(rhs); }

	};
	// Making it so you can use ConstTreeSetIter or const_iterator
	using ConstTreeSetIter = const_iterator;

private:

	// Storing array size
	size_type size_;
	// Storing a unique pointer to set
	std::unique_ptr<T[]> m_set;

public:

	// Default constructor
	TreeSet() = default;

	// Constructor with size
	TreeSet(size_type size);

	// Initializer list constructor
	TreeSet(std::initializer_list<T> list);

	// Copy constructor
	TreeSet(const TreeSet& src);

	// Default deconstructor
	~TreeSet();

	// size getter
	inline size_type size() const { return size_; }

	// operator overloads
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

	inline TreeSet& operator=(const TreeSet& rhs)
	{
		if (this != &rhs)
		{
			size_ = rhs.size();
			m_set.reset(nullptr);
			m_set = std::make_unique<T[]>(size_);
			for (int i = 0; i < size_; i++)
			{
				m_set[i] = rhs[i]; 
			}
		}
		return *this;
	}

	inline bool operator==(const TreeSet& rhs) const
	{
		if (size_ != rhs.size())
			return false;
		for (int i = 0; i < size_; i++)
		{
			if (m_set[i] != rhs[i])
				return false;
		}
		return true;
	}

	inline bool operator!=(const TreeSet& rhs) const
	{
		return !operator==(rhs);
	}

	// Function for intersects to check if the value is in the array or not
	bool CheckForDup(T val, const std::vector<T>& intersects) const;

	// Returns the common values of the two sets
	TreeSet<T> Intersects(const TreeSet& s) const;

	// Adding the two sets
	TreeSet<T> Plus(const TreeSet& s) const;

	// Subtracting the two sets
	TreeSet<T> Minus(const TreeSet& s) const;

	// Resize is broken right now
	T& Resize(size_type size);

	// The iterator functions for looping
	inline iterator begin() { return iterator(std::next(m_set.get(), 0)); }
	inline iterator end() { return iterator(std::next(m_set.get(), size_)); }

	// The const_iterator functions for looping
	inline const_iterator cbegin() const { return const_iterator(std::next(m_set.get(), 0)); }
	inline const_iterator cend() const { return const_iterator(std::next(m_set.get(), size_)); }

	// Output overload for printing
	inline friend std::ostream& operator<<(std::ostream& o, const TreeSet& set) { o << "["; for (int i = 0; i < set.size(); i++) { o << set.m_set[i] << ((i + 1 >= set.size()) ? "" : ", "); } return o << "]"; }

};

// My own quick sort for efficiency
template<typename T>
extern void Qsort(T* tmp, size_t len, size_t start);
