/*
* avltree.cpp
*
* AVLTree implementations
*
*/

#include <cassert>

/*
* Virtual desctructor
*/
template <class T>
AVLTree<T>::~AVLTree() {
	
	this->clear();
}

/*
* Constructor
*/
template<class T>
AVLTree<T>::AVLTree() :root(nullptr) {

}

/*
* Constructor setting the data to be stored
*/
template<class T>
AVLTree<T>::AVLTree(const T& item) :root(new AVLNode(item)) {

}

/*
* Copy constructor
* @param bst The other tree to copy
*/
template<class T>
AVLTree<T>::AVLTree(const AVLTree<T>& other) :root(nullptr) {

	*this = other;
}

/*
* Assignment operator overload, makes this a deep copy of other
* @param other The other tree to copy
* @return this by reference
*/
template<class T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& other) {

	if (this != &other) {
		
		this->clear();

		// new copy node method
	}

	return *this;
}

/*
* Checks if tree is empty
* @return true if rootPtr == nullptr, false otherwise
*/
template<class T>
bool AVLTree<T>::isEmpty() const {

	return this->root == nullptr;
}

/*
* Gets the height of the tree
* @return the height of the tree
*/
template<class T>
int AVLTree<T>::getHeight() const {

	return this->root->getHeight();
}

/*
* Adds a given item to the tree, if not duplicate
* @param item The item to add
* @return true if item added, false otherwise
*/
template<class T>
bool AVLTree<T>::add(const T& item) {
	
	bool added{false};

	if (!this->contains(item)) {
		
		if (this->root == nullptr) {
			
			this->root = new AVLNode(item);

		} else {

			AVLTree::addNode(this->root, nullptr, item);
		}

		added = true;
	}

	return added;
}

/*
* Checks for membership of given item
* @param item The item to check for
* @return true if tree contains item, false otherwise
*/
template<class T>
bool AVLTree<T>::contains(const T& item) const {

	return BinarySearchTree<T>::getNode(this->root, item) != nullptr;
}

/*
* Creates a dynamic array, copies all items to the array
* and then reads the array to re-balance this tree
*/
template<class T>
void AVLTree<T>::rebalance() {

}

/*
* Deletes all nodes in the tree
*/
template<class T>
void AVLTree<T>::clear() {
	 
	BinarySearchTree<T>::deleteNodes(this->root);
}

/*
* Prints the tree sideways
*/
template<class T>
void AVLTree<T>::displaySideways() const {

	BinarySearchTree<T>::sideways(this->root, 0);
}

/*
* Adds new node
*/
template<class T>
void AVLTree<T>::addNode(AVLNode* curr, AVLNode* parent, const T& item) {

	if (curr == nullptr) {
		
		curr = new AVLNode(item);
		
		curr->setParent(parent);
		
		if (parent != nullptr) {
			if (item == 10) { std::cout << "parent " << *parent << "\n"; }
			if (parent->getItem() < item) {
				
				parent->setRight(curr);

			} else {
				
				parent->setLeft(curr);
			}
		}

		this->updateHeights(parent);

	} else if (curr->getItem() < item) {
		
		AVLNode* right = static_cast<AVLNode*>(curr->getRight());

		AVLTree::addNode(right, curr, item);

	} else {

		AVLNode* left = static_cast<AVLNode*>(curr->getLeft());

		AVLTree::addNode(left, curr, item);
	}
}

/*
* Adds new node
*/
template<class T>
void AVLTree<T>::updateHeights(AVLNode* curr) {
	
	while (curr != nullptr) {
		
		AVLNode*  left = static_cast<AVLNode*>(curr->getLeft()),
			   * right = static_cast<AVLNode*>(curr->getRight());
		
		int leftHeight =  left != nullptr ?  left->getHeight() : 0,
		   rightHeight = right != nullptr ? right->getHeight() : 0;

		if (leftHeight - rightHeight > 1) {

			AVLTree::leftRotation(curr, left);

			this->root = (this->root == curr) ? left : this->root;

			break;

		} else if (rightHeight - leftHeight > 1) {
			
			AVLTree::rightRotation(curr, right);

			this->root = (this->root == curr) ? right : this->root;

			break;

		} else if (leftHeight != rightHeight) {
			
			++(*curr);

			curr = static_cast<AVLNode*>(curr->getParent());

		} else {
			
			break;
		}
	}
}

/*
* Left AVL rotation
*/
template<class T>
void AVLTree<T>::leftRotation(AVLNode* curr, AVLNode* left) {

	AVLNode*  leftLeft = static_cast<AVLNode*>(left->getLeft()),
		   * leftRight = static_cast<AVLNode*>(left->getRight());

	int  leftLeftHeight =  leftLeft != nullptr ?  leftLeft->getHeight() : 0,
		leftRightHeight = leftRight != nullptr ? leftRight->getHeight() : 0;

	if (leftRightHeight > leftLeftHeight) {
		
		AVLTree::rightRotation(left, leftRight);
	}

	left->setParent(curr->getParent());
	curr->setLeft(left->getRight());
	left->setRight(curr);
	curr->setParent(left);
	
	--(*curr);
}

/*
* Right AVL rotation
*/
template<class T>
void AVLTree<T>::rightRotation(AVLNode* curr, AVLNode* right) {

	AVLNode*  rightLeft = static_cast<AVLNode*>(right->getLeft()),
		   * rightRight = static_cast<AVLNode*>(right->getRight());

	int  rightLeftHeight =  rightLeft != nullptr ?  rightLeft->getHeight() : 0,
		rightRightHeight = rightRight != nullptr ? rightRight->getHeight() : 0;

	if (rightLeftHeight > rightRightHeight) {

		AVLTree::leftRotation(right, rightLeft);
	}

	right->setParent(curr->getParent());
	curr->setRight(right->getLeft());
	right->setLeft(curr);
	curr->setParent(right);

	--(*curr);
}

///////////////////////////////////////////////////////////////////////////////
/////////////// NODES NODES NODES NODES NODES NODES ///////////////////////////
///////////////////////////////////////////////////////////////////////////////

/*
*  constructor setting the data to be stored
*/
template<class T>
AVLTree<T>::AVLNode::AVLNode(const T& item) :Node<T>(item) {

	this->height = 1;
}

/*
* Get the height of the Node
* @return height of the Node
*/
template<class T>
int AVLTree<T>::AVLNode::getHeight() const {

	return this->height;
}

/*
* Increment operator overload
* increments height of Node
*/
template<class T>
void AVLTree<T>::AVLNode::operator++() {

	++this->height;
}

/*
* Decrement operator overload
* decrements height of Node
*/
template<class T>
void AVLTree<T>::AVLNode::operator--() {

	--this->height;
}
