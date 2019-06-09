# Tree Sets

tree sets and Initializer Lists
Since C++11, the STL collections support initialization from a list of values, like this:

// Initialize a vector of 7 integer values
vector<int> v = {1, 1, 2, 3, 5, 8, 13};

// This syntax also works:
vector<int> v{1, 1, 2, 3, 5, 8, 13};
You can add list-initialization like this to your own classes by using the std::initializer_list<T> type, declared in the <initializer_list> C++ standard header file. Just make a constructor that takes an initializer-list of values of the appropriate type, and you will also be able to initialize your tree-set like this:

TreeSet s1 = {2, 3, 5};
TreeSet s2{2, 3, 5};
TreeSet Iteration
In-order tree traversal is not terribly difficult to implement, but it is made more complicated by the standard C++ iterator abstraction, which allows one to access the current element, or advance to the next element. Your TreeSet class will need to provide functionality similar to the C++ iterator abstraction, like this:

TreeSet s{3, 5, 2, 1};

TreeSet::iterator it = s.begin();
while (it != s.end()) {
    cout << ' ' << *it;
    it++;  // or ++it;
}
This should print out the result "1 2 3 5"; in other words, the values are traversed in increasing order.

TreeSetIter Functionality
The TreeSetIter class must provide the following operations:

Initialization. You do not have to provide copy-initialization or move-initialization; as long as you are not heap-allocating anything (why would you anyway?), the default implementations should suffice.

TreeSetIter & operator++() (pre-increment operator) - advance the iterator to the next node in the binary search tree. The operator should return a reference to the iterator that was incremented, not a copy.

TreeSetIter operator++(int) (post-increment operator) - advance the iterator to the next node in the binary search tree. The operator should return a copy of the iterator before it was incremented.

int operator*() (dereference) - the iterator "points to" the current int value, and dereferencing the iterator should return the int value itself. For this operation the iterator may simply return the value out of the tree node.

bool operator==(const TreeSetIter &rhs) const - return true if the rhs iterator references the same tree-node that this iterator references. Note that you are not comparing the values in the tree-nodes; you are comparing the pointers to the tree-nodes.

bool operator!=(const TreeSetIter &rhs) const - inverse of ==

TreeSet Iterator Functionality
The TreeSet class itself must provide the following operations:

TreeSetIter begin() const - return an iterator to the first value in the tree-set

TreeSetIter end() const - return an iterator "past the end" of the tree-set. A good approach would be to initialize a TreeSetIter object with an empty node-pointer.

A public declaration of the TreeSet::iterator type. Like STL collections, this allows the TreeSet to provide a more "standard" name for the iterator type, rather than requiring users to know internal implementation details. This can be done easily with a line like this in your TreeSet class' public section:

using iterator = TreeSetIter;

Once these features are provided, you should be able to iterate over the contents of a TreeSet in order. Exciting times.

Additional TreeSet Features
Once the iteration is complete, many other tree-set features become straightforward to write. Implement these member functions for your TreeSet class, using your iterator implementation:

bool operator==(const TreeSet &rhs) const - return true if the rhs set contains the same values as this set. Note that the two sets may have different internal tree structures and still compare as equal.

bool operator!=(const TreeSet &rhs) const - inverse of ==

TreeSet TreeSet::plus(const TreeSet &s) const - compute the set-union of this set and the provided set s, returning a separate set containing the result.

Note: This is called plus() and not union() because union is a C++ keyword.

Note: A more generalized data structure would also provide + and += operators, etc. We are not requiring these operations because it starts to get tedious to implement and test all these operations. However, feel free to provide them if you wish.

TreeSet TreeSet::intersect(const TreeSet &s) const - compute the set-intersection of this set and the provided set s, returning a separate set containing the result.

TreeSet TreeSet::minus(const TreeSet &s) const - compute the set-difference of this set and the provided set s, returning a separate set containing the result.

Note: A more generalized data structure would also provide - and -= operators, etc. We are not requiring these operations because it starts to get tedious to implement and test all these operations. However, feel free to provide them if you wish.

A stream-output operator << for your TreeSet type, which outputs the contents of the set in this format: "[1,2,3,4]"

Note that the stream-output operator must not output a "\n" character, or any whitespace.

An empty set would be output as: "[]"
