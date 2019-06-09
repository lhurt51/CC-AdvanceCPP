#include "TreeSet/TreeSet.hpp"

#include <vector>

int main(int argc, char** argv)
{

	std::cout << "Program Initilized" << std::endl;

#ifdef TESTCODE
	std::cout << "Test" << std::endl;
	for (int i = 1; i < argc; ++i) 
		std::cout << argv[i] << std::endl;
#else
	argc = 0;
	argv = nullptr;
#endif

	TreeSet<float> treeSet(6);
	treeSet[0] = 3.5f;
	treeSet[1] = 7.5f;
	treeSet[2] = 1.45f;
	treeSet[3] = 45.12f;
	treeSet[4] = 32.0f;
	treeSet[5] = 13.456f;

	for (TreeSet<float>::const_iterator i = treeSet.cbegin(); i != treeSet.cend(); i++)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	treeSet.resize(7);

	for (TreeSet<float>::iterator i = treeSet.begin(); i != treeSet.end(); i++)
	{
		*i += 10.0f;
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	treeSet.resize(5);

	std::vector<float> set;
	std::copy(treeSet.cbegin(), treeSet.cend(), std::back_inserter(set));

	for (std::vector<float>::const_iterator i = set.begin(); i != set.end(); i++)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	std::cout << "Program Destroyed" << std::endl;

	return 0;
}