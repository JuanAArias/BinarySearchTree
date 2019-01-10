// Yusuf Pisan pisan@uw.edu
// 15 Jan 2018

// Edit 20 Jan 2018. Added <ItemType> for all cases
// since it was complaining under some compilers but not g++

// BinaryNode to help with BinarySearchTree class
// Uses template so that ItemType can be any type
// getLeftChildPtr and setLeftChildPtr used to get/set child nodes
// getItem/setItem used to set the data stored in this node
// BinarySearchTree requires <, > relationships to be defined for ItemType
// << for  BinaryNode is defined to print the ItemType as [BN: item ]
// binarynode.cpp file is included at the bottom of the .h file
// binarynode.cpp is part of the template, cannot be compiled separately

#ifndef BINARYNODE_H
#define BINARYNODE_H

#include <iostream>

template<class T>
class Node {

  // operator<<
  // Has to be defined in .h and not in cpp since it is not in
  // BinaryNode<ItemType>:: class
  friend std::ostream &operator<<(std::ostream &out, const Node<T> &bn) {
    out << "[BN: " << bn.item << "]";
    return out;
  }

public:

  // constructor setting the data to be stored
  explicit Node<T>(const T &item);

  // destructor to cleanup
  virtual ~Node<T>();

  // true if no children, both left and right child ptrs are nullptr
  bool isLeaf() const;

  // get left child, possibly nullptr
  Node<T>* getLeft() const;

  // set the left child ptr
  void setLeft(Node<T>* child);

  // get right child, possibly nullptr
  Node<T>* getRight() const;

  // set the right child ptr
  void setRight(Node<T>* child);

  // return the item stored
  T getItem() const;

  // set the item stored to a new value
  void setItem(const T &item);

  // get parent ptr
  Node<T>* getParent() const;

  // set parent ptr
  void setParent(Node<T>* parent);

private:

	// default constructor not allowed
	Node<T>();

  // the data that will be stored
  T item;

  // left child
  Node<T>* left;

  // right child
  Node<T>* right;

  // right child
  Node<T>* parent;
};

#include "node.cpp"

#endif // BINARYNODE_H