/*
* binarysearchtree.h
* 
* @author Yusuf Pisan & Juan Arias
*
* Specifiactions for BinarySearchTree class.
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

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <vector>
#include "node.h"

template<class T>
class BinarySearchTree {

public:

	/*
	* Constructs empty tree
	*/
	BinarySearchTree<T>();

	/*
	* Constructs tree with given item for root node
	* @param item The item for the root node
	*/
	explicit BinarySearchTree<T>(const T& item);

	/*
	* Copy constructor
	* @param bst The other tree to copy
	*/
	BinarySearchTree<T>(const BinarySearchTree<T>& other);

	/*
	* Destroys tree and deallocates all dynamic memory
	*/
	virtual ~BinarySearchTree<T>();

	/*
	* Assignment operator overload, makes this a deep copy of other
	* @param other The other tree to copy
	* @return this by reference
	*/
	BinarySearchTree<T>& operator=(const BinarySearchTree<T>& other);

	/*
	* Checks if tree is empty
	* @return true if rootPtr == nullptr, false otherwise
	*/
	virtual bool isEmpty() const;

	/*
	* Gets the height of the tree
	* @return the height of the tree
	*/
	virtual int getHeight() const;

	/*
	* Gets the amount of nodes in the tree
	* @return the amount of nodes in the tree
	*/
	virtual int getNumberOfNodes() const;

	/*
	* Adds a given item to the tree, if not duplicate
	* @param item The item to add
	* @return true if item added, false otherwise
	*/
	virtual bool add(const T& item);

	/*
	* Removes a given item from the tree if there
	* @param item The item to remove
	* @return true if item removed, false otherwise
	*/
	bool remove(const T& item);

	/*
	* Deletes all nodes in the tree
	*/
	virtual void clear();

	/*
	* Checks for membership of given item
	* @param item The item to check for
	* @return true if tree contains item, false otherwise
	*/
	virtual bool contains(const T& item) const;

	/*
	* Prints the tree sideways
	*/
	virtual void displaySideways() const;

	/*
	* Inorder traversal: left-root-right
	* The function can modify the data in tree, but the
    * tree structure is not changed
	* @param visit The function to visit on each node
	*/
	void inorderTraverse(void visit(T& item)) const;

	/* 
	* Creates a dynamic array, copies all items to the array
	* and then reads the array to re-balance this tree
	*/
	virtual void rebalance();


	/* 
	* Clears the tree and then uses the given array of length n
	* to create this tree with items from the array at minimum height
	* @param arr The given array of elements
	* @param n The size of the array
	*/
	bool readTree(const T arr[], int n);

	/*
	* Equality operator overload
	* @param other The other tree to compare to
	* @return true if all nodes have same value and structure, false otherwise
	*/
	bool operator==(const BinarySearchTree<T>& other) const;

	/*
	* Inequality operator overload
	* @param other The other tree to compare to
	* @return true if nodes have different value or structure, false otherwise
	*/
	bool operator!=(const BinarySearchTree<T>& other) const;

	/*
	* Get cousins of Node with item
	*/
	std::vector<T> getCousins(const T& item) const;

	/*
	* Height is defined by number of nodes to leaf.
	* Height is zero if the item is not found.
	* @param item The item in the Node to get the height of
	* @return height of Node that stores item
	*/
	int getHeight(const T& item) const;

	/*
	* Mystery quiz question
	* @return mystery number
	*/
	int mystery() const;

protected:

	/*
	* Static helper function for add, adds new node in the tree
	* @param curr The current node in the tree
	* @param item The item to add in a new node
	* @return the current node after the new node is added
	*/
	static Node<T>* addNode(Node<T>* curr, Node<T>* parent, const T& item);

	/*
	* Static helper function, finds the node in the tree with the target item
	* @param curr The current node in the tree
	* @param target The target item
	* @return pointer to node with target item or nullptr if item not in tree
	*/
	static Node<T>* getNode(Node<T>* curr, const T& target);

	/*
	* Static helper function for displaySideways
	* @param curr The current node in the tree
	* @param level The current level in the tree
	*/
	static void sideways(Node<T>* curr, int level);

	/*
	* Static helper function for clear
	* Deletes a nodes children and then deletes node (postorder traversal)
	* @param curr The current node in the tree
	* @return nullptr after all nodes deleted
	*/
	static Node<T>* deleteNodes(Node<T>* curr);

private:

	// Root of the tree
	Node<T>* rootPtr;

	/*
	* Helper function for readTree, recursively adds each item
	* in the array by finding the middle item for the next node
	* @param arr The array of items
	* @param first The first index to use in the array/subarray
	* @param last  The  last index to use in the array/subarray
	*/
	void readHelper(const T arr[], int first, int last);

	/*
	* Static helper function for remove, finds the node to remove and returns
	* nullptr, nodes child or inorder successor to take its place
	* @param curr The current node in the tree
	* @param target The target item to remove
	* @return curr after node has been deleted
	*/
	static Node<T>* removeItem(Node<T>* curr, Node<T>* parent, const T& target);

	/*
	* Static helper function for removeItem, deletes curr and returns nullptr,
	* curr's child or curr's inorder successor to take its place
	* @param curr The current node in the tree
	* @return curr after node has been deleted and replaced
	*/
	static Node<T>* removeNode(Node<T>* curr, Node<T>* parent);

	/*
	* Static helper function for removeNode, gets the inorderSuccesor item
	* to replace in node and deletes inorderSuccesor node
	* @param curr The current node in the tree
	* @param newItem The new item for the node
	*/
	static Node<T>* removeLeftMost(Node<T>* curr, Node<T>* parent, T* newItem);

	/*
	* Static helper function for removeNode to check
	* if curr has both children
	* @param curr The current node in the tree
	* @return true if has both children, false otherwise
	*/
	static bool hasTwoChild(Node<T>* curr);

	/*
	* Static helper function for removeNode to get only child of curr
	* @param curr The current node in the tree
	* @return the only child of curr
	*/
	static Node<T>* only(Node<T>* curr);

	/*
	* Static helper function for copy constructor,
	* copies a given node and all its children (preorder traversal)
	* @param curr The current node in the first tree
	* @param other the current node in the second tree to copy
	* @return curr after all nodes have been copied
	*/
	static Node<T>* copyNode(Node<T>* curr, Node<T>* currParent, Node<T>* other);

	/*
	* Static helper function for equality operator overload,
	* compares nodes for equal items
	* @param curr The current node in the first tree
	* @param other The current node in the second tree
	*/
	static bool equalNode(Node<T>* curr, Node<T>* other);

	/*
	* Static helper function for getHeight,
	* counts the height recursively by adding 1 at each lower level
	* @param curr The current node in the tree
	* @return the height of the tree as an int
	*/
	static int getHeight(Node<T>* curr);

	/*
	* Static helper function for getNumberOfNodes,
	* counts the nodes by adding one at each node in postorder traversal
	* @param curr The current node in the tree
	* @return the number of nodes in the tree as an int
	*/
	static int getNodes(Node<T>* curr);

	/*
	* Static helper function for inorder traverse
	* @param curr The current node in the tree
	* @param visit The visiting function on each item in tree
	*/
	static void inorder(Node<T>* curr, void visit(T& item));

	/*
	* Static helper function for rebalance, fills array with all items
	* in sorted order with inorder traversal
	* @param arr The array to fill
	* @param curr The current node in the tree
	* @param index The current index to insert in the array
	*/
	static void toArray(T arr[], Node<T>* curr, int* index);

	/*
	* Helper for mystery function
	* @param curr The current Node in the Tree
	* @param n A mystery number
	* @return mystery number
	*/
	static int helper(Node<T>* curr, int& n);
};

#include "bst.cpp"
#endif  // BINARYSEARCHTREE_H
