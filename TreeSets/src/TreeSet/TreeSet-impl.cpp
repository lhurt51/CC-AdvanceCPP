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

#include "TreeSet.cpp"

template class TreeSet<int>;
template class TreeSet<unsigned int>;
template class TreeSet<float>;
template class TreeSet<double>;

template void Qsort(int* tmp, size_t len, size_t start);
template void Qsort(unsigned int* tmp, size_t len, size_t start);
template void Qsort(float* tmp, size_t len, size_t start);
template void Qsort(double* tmp, size_t len, size_t start);