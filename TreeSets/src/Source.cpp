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

#include "TreeSet/TreeSet.hpp"

#include <vector>

int main(int argc, char** argv)
{
	std::cout << "Program Initilized" << std::endl;

	// Temp code to make testing with your own args easier
#ifdef TESTCODE
	std::cout << "Test" << std::endl;
	for (int i = 1; i < argc; ++i) 
		std::cout << argv[i] << std::endl;
#else
	argc = 0;
	argv = nullptr;
#endif

	// Initializing the tree set with an initializer list
	TreeSet<float> treeSet = { 3.5f, 7.5f, 1.45f, 45.12f, 32.0f };
	/*
	Alternatively you can assign each index and construct with size
	TreeSet<float> treeSet(6);
	treeSet[0] = 3.5f;
	treeSet[1] = 7.5f;
	treeSet[2] = 1.45f;
	treeSet[3] = 45.12f;
	treeSet[4] = 32.0f;
	treeSet[5] = 13.456f;
	*/

	// Printing out the array with const iterators
	for (TreeSet<float>::const_iterator i = treeSet.cbegin(); i != treeSet.cend(); i++)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	// Resizing the array to add two 0 values to the array
	treeSet.Resize(7);

	// Looping through using itterators to add 10 to each value
	for (TreeSet<float>::iterator i = treeSet.begin(); i != treeSet.end(); i++)
	{
		*i += 10.0f;
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	// Expanding array works but compressing array does not work
	// treeSet.Resize(5);

	// Copying the array to an std::vector called set
	std::vector<float> set;
	std::copy(treeSet.cbegin(), treeSet.cend(), std::back_inserter(set));

	// Printing out the vector just to make sure the conversion is correct
	for (std::vector<float>::const_iterator i = set.begin(); i != set.end(); i++)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	std::cout << "Program Destroyed" << std::endl;

	return 0;
}