/*
* avltree.h
*
* AVLTree specs
*
*/

#ifndef AVLTREE_H
#define AVLTREE_H

#include "bst.h"

/*
* Self balancing BST
*
* @author Juan Arias
*
*/
template <class T>
class AVLTree : public BinarySearchTree<T> {

public:

	/*
	* Virtual desctructor
	*/
	virtual ~AVLTree();

	/*
	* Constructor
	*/
	AVLTree();

	/*
	* Constructor setting the data to be stored
	*/
	explicit AVLTree(const T& item);

	/*
	* Copy constructor
	* @param bst The other tree to copy
	*/
	AVLTree(const AVLTree<T>& other);

	/*
	* Assignment operator overload, makes this a deep copy of other
	* @param other The other tree to copy
	* @return this by reference
	*/
	AVLTree<T>& operator=(const AVLTree<T>& other);

	/*
	* Checks if tree is empty
	* @return true if rootPtr == nullptr, false otherwise
	*/
	bool isEmpty() const override;

	/*
	* Gets the height of the tree
	* @return the height of the tree
	*/
	int getHeight() const override;

	/*
	* Adds a given item to the tree, if not duplicate
	* @param item The item to add
	* @return true if item added, false otherwise
	*/
	bool add(const T& item) override;

	/*
	* Checks for membership of given item
	* @param item The item to check for
	* @return true if tree contains item, false otherwise
	*/
	bool contains(const T& item) const override;

	/*
	* Creates a dynamic array, copies all items to the array
	* and then reads the array to re-balance this tree
	*/
	void rebalance() override;

	/*
	* Deletes all nodes in the tree
	*/
	void clear() override;

	/*
	* Prints the tree sideways
	*/
	void displaySideways() const override;

private:

	/*
	* Nodes that will store height for self balancing
	*/
	class AVLNode : public Node<T> {

	public:

		/*
		* Constructor setting the data to be stored
		*/
		explicit AVLNode(const T& item);

		/*
		* Get the height of the Node
		* @return height of the Node
		*/
		int getHeight() const;

		/*
		* Increment operator overload
		* increments height of Node
		*/
		void operator++();

		/*
		* Decrement operator overload
		* decrements height of Node
		*/
		void operator--();

	private:

		/*
		* Default constructor not allowed
		*/
		AVLNode();

		/* Keep track of height for rebalancing */
		int height;
	};

	/* Root of AVLTree*/
	AVLNode* root;

	/*
	* Adds new Node
	*/
	void addNode(AVLNode* curr, AVLNode* parent, const T& item);

	/*
	* Update heights after adding Node
	*/
	void updateHeights(AVLNode* curr);

	/*
	* Left AVL rotation
	*/
	static void leftRotation(AVLNode* curr, AVLNode* left);

	/*
	* Right AVL rotation
	*/
	static void rightRotation(AVLNode* curr, AVLNode* right);
};

#include "avltree.cpp"
#endif // AVLTREE_H
