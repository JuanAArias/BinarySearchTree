/*
* binarysearchtree.cpp
*
* @author Juan Arias
*
* Implementations for BinarySearchTree class.
*
* A BinarySearchTree is a binary tree where all values to the right of a node
* are greater and all values left a node are lesser. It is able to locate a
* a node in O(logn) time. Operations include:
*
*	- checking if empty
*	- getting height
*	- getting number of nodes
*	- checking for an item
*	- adding an item
*	- displaying the tree sideways
*	- visiting each item inorder with a function parameter
*	- rebalancing
*	- clearing
*	- creating itself from an array
*	- equality and non equality operator overloads
*/

#include <algorithm>
#include <string>
#include "bst.h"

/*
* Constructs empty tree
*/
template<class T>
BinarySearchTree<T>::BinarySearchTree() :rootPtr(nullptr) {}

/*
* Constructs tree with given item for root node
* @param rootItem The item for the root node
*/
template<class T>
BinarySearchTree<T>::BinarySearchTree(const T& item)

	:rootPtr(new Node<T>(item)) {}

/*
* Copy constructor
* @param bst The other tree to copy
*/
template<class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& other)

	:rootPtr(nullptr) {

	*this = other;
}

/*
* Destroys tree and deallocates all dynamic memory
*/
template<class T>
BinarySearchTree<T>::~BinarySearchTree() {

	this->clear();
}

/*
* Assignment operator overload, makes this a deep copy of other
* @param other The other tree to copy
* @return this by reference
*/
template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& other) {

	if (this != &other) {

		this->clear();

		this->rootPtr = BinarySearchTree<T>::copyNode(this->rootPtr, nullptr, other.rootPtr);
	}

	return *this;
}

/*
* Checks if tree is empty
* @return true if rootPtr == nullptr, false otherwise
*/
template<class T>
bool BinarySearchTree<T>::isEmpty() const {

	return this->rootPtr == nullptr;
}

/*
* Gets the height of the tree
* @return the height of the tree
*/
template<class T>
int BinarySearchTree<T>::getHeight() const {

	return BinarySearchTree<T>::getHeight(this->rootPtr);
}

/*
* Gets the amount of nodes in the tree
* @return the amount of nodes in the tree
*/
template<class T>
int BinarySearchTree<T>::getNumberOfNodes() const {

	return BinarySearchTree<T>::getNodes(this->rootPtr);
}

/*
* Adds a given item to the tree, if not duplicate
* @param item The item to add
* @return true if item added, false otherwise
*/
template<class T>
bool BinarySearchTree<T>::add(const T& item) {

	bool added(false);

	if (!this->contains(item)) {

		this->rootPtr = BinarySearchTree<T>::addNode(this->rootPtr, nullptr, item);

		added = true;
	}

	return added;
}

/*
* Removes a given item from the tree if there
* @param item The item to remove
* @return true if item removed, false otherwise
*/
template <class T>
bool BinarySearchTree<T>::remove(const T& item) {

	bool removed(false);

	if (this->contains(item)) {

		this->rootPtr = BinarySearchTree<T>::removeItem(this->rootPtr, nullptr, item);

		removed = true;
	}


	return removed;
}

/*
* Deletes all nodes in the tree
*/
template<class T>
void BinarySearchTree<T>::clear() {

	this->rootPtr = BinarySearchTree<T>::deleteNodes(this->rootPtr);
}

/*
* Checks for membership of given item
* @param item The item to check for
* @return true if tree contains item, false otherwise
*/
template<class T>
bool BinarySearchTree<T>::contains(const T& item) const {

	return BinarySearchTree<T>::getNode(this->rootPtr, item) != nullptr;
}

/*
* Prints the tree sideways
*/
template<class T>
void BinarySearchTree<T>::displaySideways() const {

	BinarySearchTree<T>::sideways(this->rootPtr, 0);
}

/*
* Inorder traversal: left-root-right
* The function can modify the data in tree, but the
* tree structure is not changed
* @param visit The function to visit on each node
*/
template<class T>
void BinarySearchTree<T>::inorderTraverse(void visit(T& item)) const {

	BinarySearchTree<T>::inorder(this->rootPtr, visit);
}

/*
* Creates a dynamic array, copies all items to the array
* and then reads the array to re-balance this tree
*/
template<class T>
void BinarySearchTree<T>::rebalance() {

	int n(this->getNumberOfNodes());

	T* arr = new T[n];

	int index(0);

	BinarySearchTree<T>::toArray(arr, this->rootPtr, &index);

	this->readTree(arr, n);

	delete[] arr;
}

/*
* Clears the tree and then uses the given array of length n
* to create this tree with items from the array at minimum height
* Assumes array is sorted
* @param arr The given array of elements
* @param n The size of the array
* @return true
*/
template<class T>
bool BinarySearchTree<T>::readTree(const T arr[], int n) {

	bool read(false);

	if (n > 0) {

		this->clear();

		BinarySearchTree<T>::readHelper(arr, 0, n - 1);

		read = true;
	}

	return read;
}

/*
* Equality operator overload
* @param other The other tree to compare to
* @return true if all nodes have same value, false otherwise
*/
template<class T>
bool BinarySearchTree<T>::operator==(const BinarySearchTree<T>& other) const {

	return BinarySearchTree<T>::equalNode(this->rootPtr, other.rootPtr);
}

/*
* Inequality operator overload
* @param other The other tree to compare to
* @return true if nodes have different value or structure, false otherwise
*/
template<class T>
bool BinarySearchTree<T>::operator!=(const BinarySearchTree<T>& other) const {

	return !(*this == other);
}

/*
* Get cousins of Node with item
*/
template<class T>
std::vector<T> BinarySearchTree<T>::getCousins(const T& item) const {

	std::vector<T> vec;

	Node<T>* curr = BinarySearchTree<T>::getNode(this->rootPtr, item);

	if (curr != nullptr && curr->getParent() != nullptr && curr->getParent()->getParent() != nullptr) {
	
		Node<T>* grandpa = curr->getParent()->getParent();

		Node<T>* uncle = (curr->getParent() != grandpa->getLeft()) ? grandpa->getLeft() : grandpa->getRight();

		if (uncle->getLeft() != nullptr) {
			
			vec.push_back(uncle->getLeft()->getItem());
		}
		if (uncle->getRight() != nullptr) {

			vec.push_back(uncle->getRight()->getItem());
		}
	}

	return vec;
}

/*
* Height is defined by number of nodes to leaf.
* Height is zero if the item is not found.
* @param item The item in the Node to get the height of
* @return height of Node that stores item
*/
template<class T>
int BinarySearchTree<T>::getHeight(const T& item) const {

	Node<T>* curr = BinarySearchTree::getNode(this->rootPtr, item);

	return this->getHeight(curr);
}

/*
* Mystery quiz question
* @return mystery number
*/
template<class T>
int BinarySearchTree<T>::mystery() const {

	int n(0);

	return BinarySearchTree::helper(this->rootPtr, n);
}

/*
* Helper function for readTree, recursively adds each item
* in the array by finding the middle item for the next node
* @param arr The array of items
* @param first The first index to use in the array/subarray
* @param last  The  last index to use in the array/subarray
*/
template<class T>
void BinarySearchTree<T>::readHelper(const T arr[], int first, int last) {

	if (first <= last) {

		int mid = (first + last) / 2;

		this->add(arr[mid]);

		this->readHelper(arr, first, mid - 1);
		this->readHelper(arr, mid + 1, last);
	}
}

/*
* Static helper function for add, adds new node in the tree
* @param curr The current node in the tree
* @param item  The item to add in a new node
* @return the current node after the new node is added
*/
template<class T>
Node<T>* BinarySearchTree<T>::addNode(Node<T>* curr, Node<T>* parent, const T& item) {

	if (curr == nullptr) {

		curr = new Node<T>(item);
		curr->setParent(parent);

	} else if (curr->getItem() < item) {

		Node<T>* right = curr->getRight();
		right = BinarySearchTree<T>::addNode(right, curr, item);
		curr->setRight(right);

	} else {

		Node<T>* left = curr->getLeft();
		left = BinarySearchTree<T>::addNode(left, curr, item);
		curr->setLeft(left);
	}

	return curr;
}

/*
* Static helper function
* Finds the node in the tree with the target item
* @param curr The current node in the tree
* @param target The target item
* @return pointer to node with target item or nullptr if item not in tree
*/
template<class T>
Node<T>* BinarySearchTree<T>::getNode(Node<T>* curr,
											const T& target) {

	if (curr != nullptr && curr->getItem() != target) {

		if (curr->getItem() < target) {

			Node<T>* right = curr->getRight();
			curr = BinarySearchTree<T>::getNode(right, target);

		} else {

			Node<T>* left = curr->getLeft();
			curr = BinarySearchTree<T>::getNode(left, target);
		}
	}

	return curr;
}

/*
* Static helper function for displaySideways
* @param curr The current node in the tree
* @param level The current level in the tree
*/
template<class T>
void BinarySearchTree<T>::sideways(Node<T>* curr, int level) {

	if (curr != NULL) {

		++level;

		BinarySearchTree<T>::sideways(curr->getRight(), level);

		for (int i(level); i >= 0; --i) {

			std::cout << "    ";
		}

		std::cout << curr->getItem() << std::endl;

		BinarySearchTree<T>::sideways(curr->getLeft(), level);
	}
}

/*
* Static helper function for clear
* Deletes a nodes children and then deletes node (postorder traversal)
* @param curr The current node in the tree
* @return nullptr after all nodes deleted
*/
template<class T>
Node<T>* BinarySearchTree<T>::deleteNodes(Node<T>* curr) {

	if (curr != nullptr) {

		if (!curr->isLeaf()) {

			Node<T>* left  = curr->getLeft(),
						 * right = curr->getRight();

			left  = BinarySearchTree<T>::deleteNodes(left);
			right = BinarySearchTree<T>::deleteNodes(right);

			curr->setLeft(left);
			curr->setRight(right);
		}

		delete curr;
		curr = nullptr;
	}

	return curr;
}

/*
* Static helper function for remove, deletes and replaces it with nullptr
* or node to retain BST properties
* @param curr The current node in the tree
* @return curr after node has been deleted
*/
template<class T>
Node<T>* BinarySearchTree<T>::removeItem(Node<T>* curr, Node<T>* parent, const T& target) {

	if (curr->getItem() == target) {

		curr = BinarySearchTree<T>::removeNode(curr, parent);

	} else if (curr->getItem() < target) {

		Node<T>* right = curr->getRight();
		right = BinarySearchTree<T>::removeItem(right, curr, target);
		curr->setRight(right);

	} else {

		Node<T>* left = curr->getLeft();
		left = BinarySearchTree<T>::removeItem(left, curr, target);
		curr->setLeft(left);
	}

	return curr;
}

/*
* Static helper function for removeItem, deletes curr and returns nullptr,
* curr's child or curr's inorder successor to take its place
* @param curr The current node in the tree
* @return curr after node has been deleted and replaced
*/
template<class T>
Node<T>* BinarySearchTree<T>::removeNode(Node<T>* curr, Node<T>* parent) {

	if (!BinarySearchTree<T>::hasTwoChild(curr)) {

		Node<T>* temp = curr;
		
		if (curr->isLeaf()) {
			
			curr = nullptr;

		} else {

			curr = BinarySearchTree<T>::only(curr);

			curr->setParent(parent);
		}

		delete temp;

	} else {

		T inorderSuccesor;

		Node<T>* right = curr->getRight();
		right = BinarySearchTree<T>::removeLeftMost(right, parent, &inorderSuccesor);

		curr->setRight(right);
		curr->setItem(inorderSuccesor);
	}

	return curr;
}

/*
* Static helper function for removeNode, gets the inorderSuccesor item
* to replace in node and deletes inorderSuccesor node
* @param curr The current node in the tree
* @param newItem The new item for the node
*/
template<class T>
Node<T>* BinarySearchTree<T>::removeLeftMost(Node<T>* curr, Node<T>* parent, T* newItem) {

	if (curr->getLeft() == nullptr) {

		*newItem = curr->getItem();

		curr = BinarySearchTree<T>::removeNode(curr, parent);

	} else {

		Node<T>* left = curr->getLeft();
		left = BinarySearchTree<T>::removeLeftMost(left, curr, newItem);
		curr->setLeft(left);
	}

	return curr;
}

/*
* Static helper function for removeNode to check
* if curr has both children
* @param curr The current node in the tree
* @return true if has both children, false otherwise
*/
template <class T>
bool BinarySearchTree<T>::hasTwoChild(Node<T>* curr) {
	
	return curr->getLeft()  != nullptr &&
		   curr->getRight() != nullptr;
}

/*
* Static helper function for removeNode to get only child of curr
* @param curr The current node in the tree
* @return the only child of curr
*/
template<class T>
Node<T>* BinarySearchTree<T>::only(Node<T>* curr) {

	Node<T>* left  = curr->getLeft(),
				 * right = curr->getRight();

	return (left != nullptr) ? left : right;
}

/*
* Static helper function for assingment operator overload,
* copies a given node and all its children (preorder traversal)
* @param curr The current node in the first tree
* @param other the current node in the other tree to copy
* @return curr after all nodes have been copied
*/
template<class T>
Node<T>* BinarySearchTree<T>::copyNode(Node<T>* curr, Node<T>* currParent, Node<T>* other) {

	if (other != nullptr) {

		curr = new Node<T>(other->getItem());

		Node<T>* left = other->getLeft(),
			   * right = other->getRight();

		left  = BinarySearchTree<T>::copyNode(nullptr, curr, left);
		right = BinarySearchTree<T>::copyNode(nullptr, curr, right);

		curr->setLeft(left);
		curr->setRight(right);
		curr->setParent(currParent);
	}

	return curr;
}

/*
* Static helper function for equality operator overload, compares nodes for
* equal items
* @param curr The current node in the first tree
* @param other The current node in the second tree
*/
template<class T>
bool BinarySearchTree<T>::equalNode(Node<T>* curr, Node<T>* other) {

	bool equal(false);

	if (curr == nullptr && other == nullptr) {

		equal = true;

	} else if (curr != nullptr && other != nullptr &&
			   curr->getItem() == other->getItem()) {

		Node<T>* currLeft   = curr->getLeft(),
					 * currRight  = curr->getRight(),
					 * otherLeft  = other->getLeft(),
					 * otherRight = other->getRight();

		equal = BinarySearchTree<T>::equalNode(currLeft, otherLeft) &&
				BinarySearchTree<T>::equalNode(currRight, otherRight);
	}

	return equal;
}

/*
* Static helper function for getHeight,
* counts the height recursively by adding 1 at each lower level
* @param curr The current node in the tree
* @return the height of the tree as an int
*/
template<class T>
int BinarySearchTree<T>::getHeight(Node<T>* curr) {

	int height(0);

	if (curr != nullptr) {

		Node<T>* left  = curr->getLeft(),
			   * right = curr->getRight();

		int  leftHeight(BinarySearchTree<T>::getHeight(left));
		int rightHeight(BinarySearchTree<T>::getHeight(right));

		height = 1 + std::max(leftHeight, rightHeight);
	}

	return height;
}

/*
* Static helper function for getNumberOfNodes,
* counts the nodes by adding one at each node in postorder traversal
* @param curr The current node in the tree
* @return the number of nodes in the tree as an int
*/
template<class T>
int BinarySearchTree<T>::getNodes(Node<T>* curr) {

	int nodes(0);

	if (curr != nullptr) {

		Node<T>* left  = curr->getLeft(),
					 * right = curr->getRight();

		int  leftNodes(BinarySearchTree<T>::getNodes(left));
		int rightNodes(BinarySearchTree<T>::getNodes(right));

		nodes = 1 + leftNodes + rightNodes;
	}

	return nodes;
}

/*
* Static helper function for inorder traverse
* @param curr The current node in the tree
* @param visit The visiting function on each item in tree
*/
template<class T>
void BinarySearchTree<T>::inorder(Node<T>* curr, void visit(T& item)) {

	if (curr != nullptr) {

		Node<T>* left  = curr->getLeft(),
					 * right = curr->getRight();

		BinarySearchTree<T>::inorder(left, visit);

		T currItem(curr->getItem());
		visit(currItem);

		BinarySearchTree<T>::inorder(right, visit);
	}
}

/*
* Static helper function for rebalance, fills array with all items
* in sorted order with inorder traversal
* @param arr The array to fill
* @param curr The current node in the tree
* @param index The current index to insert in the array
*/
template<class T>
void BinarySearchTree<T>::toArray(T arr[], Node<T>* curr, int* index) {

	if (curr != nullptr) {

		Node<T>* left  = curr->getLeft(),
					 * right = curr->getRight();

		BinarySearchTree<T>::toArray(arr, left, index);

		arr[(*index)++] = curr->getItem();

		BinarySearchTree<T>::toArray(arr, right, index);
	}
}

/*
* Helper for mystery function
* @param curr The current Node in the Tree
* @param n A mystery number
* @return mystery number
*/
template<class T>
int BinarySearchTree<T>::helper(Node<T>* curr, int& n) {

	std::cout << "M: " << n << " ";

	if (curr == nullptr) {

		std::cout << "NULL" << std::endl;

	} else {

		std::cout << curr->getItem() << std::endl;
	}

	n++;

	if (curr == nullptr) {

		return n;
	}
	if (curr->getRight() == nullptr) {

		return 1;
	}
	
	return helper(curr->getLeft(), n) + helper(curr->getRight(), n);
}
