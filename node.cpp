
// Yusuf Pisan pisan@uw.edu
// 15 Jan 2018

// DO NOT compile this file
// This file is included in the binarynode.h file via #include statement
// Allows us to keep the templated class header and implementation separate

// BinaryNode to help with BinarySearchTree class
// Uses template so that ItemType can be any type
// getLeftChildPtr and setLeftChildPtr used to get/set child nodes
// getItem/setItem used to set the data stored in this node
// BinarySearchTree requires <, > relationships to be defined for ItemType
// << for  BinaryNode is defined to print the ItemType as [BN: item ]
// binarynode.cpp file is included at the bottom of the .h file
// binarynode.cpp is part of the template, cannot be compiled separately


// default constructor, children set to nullptr as default
// item contained is undefined
template<class T>
Node<T>::Node() :left{nullptr}, right{nullptr}, parent{nullptr} {}

// destructor
template<class T>
Node<T>::~Node() {
  // If suffering from memory leaks, uncomment next line
 //  std::cout << "Deleting " << *this << std::endl;
}

// constructor setting item
// left and right childPtr set to nullptr as default
template<class T>
Node<T>::Node(const T &item) :item{item}, left{nullptr}, right{nullptr}, parent{nullptr}{}

// true if no children, both leftPtr and rightPtr are nullptrs
template<class T>
bool Node<T>::isLeaf() const {

  return this->left == nullptr && this->right == nullptr;
}

// getter for left child
template<class T>
Node<T> *Node<T>::getLeft() const {

  return this->left;
}

// setter for left child
template<class T>
void Node<T>::setLeft(Node<T> *childPtr) {

  this->left = childPtr;
}

// getter for right child
template<class T>
Node<T> *Node<T>::getRight() const {

  return this->right;
}

// setter for left child
template<class T>
void Node<T>::setRight(Node<T> *childPtr) {

  this->right = childPtr;
}

// getter for item stored at node
template<class T>
T Node<T>::getItem() const {

  return this->item;
}

// setter for item stored at node
template<class T>
void Node<T>::setItem(const T &item) {
  this->item = item;
}

// get parent ptr
template<class T>
Node<T>* Node<T>::getParent() const {

	return this->parent;
}

// set parent ptr
template<class T>
void Node<T>::setParent(Node<T>* parent) {

	this->parent = parent;
}
