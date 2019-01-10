/*
* ass2.cpp
* 
* @author Juan Arias
* 
* Unit tests for BinarySearchTree class
* 
* Public member functions tested are:
*	
*	- empty, rootData and copy constructors
*	- isEmpty
*	- getHeight
*	- getNumberOfNodes
*	- contains
*	- add
*	- inorderTraverse
*	- rebalance
*	- clear
*	- readTree
*	- operator overloads == and !=
*/
#include <cassert>
#include "avltree.h"

/*
* Unit test for all constructors and destructor
*/
void constructor() {

	BinarySearchTree<char>* tree1 = new BinarySearchTree<char>;
	
	BinarySearchTree<std::string> tree2("Fifty Eight J's");

	BinarySearchTree<std::string> tree3(tree2);

	delete tree1;
}

/* 
* Unit test for isEmpty
*/
void empty() {

	BinarySearchTree<double> tree1(5.67);
	assert(!(tree1.isEmpty()));

	BinarySearchTree<std::string> tree2("Fifty Eight J's");
	assert(!(tree2.isEmpty()));

	BinarySearchTree<std::string> tree3(tree2);
	assert(!(tree3.isEmpty()));

	BinarySearchTree<int> tree4;
	assert(tree4.isEmpty());
}

/*
* Unit test for contains
*/
void contains() {

	BinarySearchTree<double> tree1(5.67);
	assert((tree1.contains(5.67)) &&  !(tree1.contains(5.6)));

	BinarySearchTree<std::string> tree2("Fifty Eight J's");
	assert((tree2.contains("Fifty Eight J's")) && !(tree2.contains("other")));

	BinarySearchTree<std::string> tree3(tree2);
	assert((tree3.contains("Fifty Eight J's")) && !(tree3.contains("other")));

	BinarySearchTree<int> tree4;
	assert(!(tree4.contains(4)));
}

/*
* Unit test for add and copy constructor to validate deep copying
*/
void add() {

	BinarySearchTree<double> tree1(5.67);
	assert(tree1.add(3.8)  && tree1.contains(3.8));
	assert(tree1.add(2.3)  && tree1.contains(2.3));
	assert(tree1.add(4.4)  && tree1.contains(4.4));
	assert(tree1.add(6.3)  && tree1.contains(6.3));
	assert(tree1.add(6.01) && tree1.contains(6.01));
	assert(tree1.add(10.3) && tree1.contains(10.3));

	BinarySearchTree<std::string> tree2("Killa");
	assert(tree2.add("Desus")	&& tree2.contains("Desus"));
	assert(tree2.add("Bool")    && tree2.contains("Bool"));
	assert(tree2.add("Fifty J") && tree2.contains("Fifty J"));

	assert(tree2.add("Quarter")	&& tree2.contains("Quarter"));
	assert(tree2.add("Zoo")		&& tree2.contains("Zoo"));
	assert(tree2.add("More")	&& tree2.contains("More"));
	
	// assert deep copying from copy constructor
	BinarySearchTree<std::string> tree3(tree2);
	
	assert(tree3.add("Not over") && tree3.contains("Not over") &&
								   !tree2.contains("Not over"));

	BinarySearchTree<int> tree4;
	assert(tree4.add(76)  && tree4.contains(76));
	assert(tree4.add(34)  && tree4.contains(34));
	assert(tree4.add(20)  && tree4.contains(20));
	assert(tree4.add(55)  && tree4.contains(55));
	assert(tree4.add(98)  && tree4.contains(98));
	assert(tree4.add(81)  && tree4.contains(81));
	assert(tree4.add(190) && tree4.contains(190));
}

/*
* Unit test for both getHeight public methods
*/
void getHeight() {

	BinarySearchTree<int> tree;
	assert(tree.getHeight() == 0);

	assert(tree.add(76)  && tree.contains(76));
	assert(tree.add(34)  && tree.contains(34));
	assert(tree.add(20)  && tree.contains(20));
	assert(tree.add(55)  && tree.contains(55));
	assert(tree.add(98)  && tree.contains(98));
	assert(tree.add(81)  && tree.contains(81));
	assert(tree.add(190) && tree.contains(190));

	assert(tree.getHeight() == 3);

	assert(tree.add(632) && tree.contains(632));

	assert(tree.getHeight() == 4);

	BinarySearchTree<char> tree2;

	char arr[9];

	for (int i(0); i < 9; ++i) {

		arr[i] = i + 'A';
	}

	tree2.readTree(arr, 9);

	assert(tree2.getHeight('E') == 4);
	assert(tree2.getHeight('B') == 3);
	assert(tree2.getHeight('G') == 3);
	assert(tree2.getHeight('C') == 2);
	assert(tree2.getHeight('H') == 2);
	assert(tree2.getHeight('A') == 1);
	assert(tree2.getHeight('F') == 1);
	assert(tree2.getHeight('D') == 1);
	assert(tree2.getHeight('I') == 1);
	assert(tree2.getHeight('X') == 0);
	assert(tree2.getHeight('Y') == 0);
	assert(tree2.getHeight('Z') == 0);
	
	tree2.clear();

	for (int i(0); i < 9; ++i) {

		tree2.add(arr[i]);
	}

	assert(tree2.getHeight(arr[0]) == tree2.getHeight());
	assert(tree2.getHeight(arr[0]) == 9);
}

/*
* Unit test for getNumberOfNodes
*/
void getNumberOfNodes() {

	BinarySearchTree<float> tree;
	assert(tree.getNumberOfNodes() == 0);

	assert(tree.add(76)  && tree.contains(76));
	assert(tree.add(34)  && tree.contains(34));
	assert(tree.add(20)  && tree.contains(20));
	assert(tree.add(55)  && tree.contains(55));
	assert(tree.add(98)  && tree.contains(98));
	assert(tree.add(81)  && tree.contains(81));
	assert(tree.add(190) && tree.contains(190));

	assert(tree.getNumberOfNodes() == 7);

	assert(tree.add(632) && tree.contains(632));

	assert(tree.getNumberOfNodes() == 8);
}

/*
* Unit test for clear
*/
void clear() {

	BinarySearchTree<char> tree1('L');
	BinarySearchTree<char> tree2;
	tree2 = tree1;

	tree1.clear();
	assert(!tree1.contains('L')    && tree2.contains('L') &&
		    tree1.getHeight() == 0 &&  tree1.getNumberOfNodes() == 0);

	char arr[5] {'C', 'A', 'G', 'X', 'Z'};

	for (char c : arr) {

		assert(tree1.add(c) && tree1.contains(c));
	}

	tree1.clear();

	for (char c : arr) {

		assert(!tree1.contains(c));
	}

	assert(tree1.getHeight() == 0 && tree1.getNumberOfNodes() == 0);
}

/*
* Unit test for equality and inequality operator overloads
*/
void equalityOperators() {

	BinarySearchTree<std::string> tree1, tree2;
	assert(tree1 == tree2);

	assert(tree1.add("The first line of text") &&
		   tree1.contains("The first line of text"));

	assert(tree1 != tree2);

	assert(tree2.add("The first line of text") &&
		   tree2.contains("The first line of text"));

	assert(tree1 == tree2);

	assert(tree1.add("Extra1") && tree1.contains("Extra1"));
	assert(tree1.add("Ace")    && tree1.contains("Ace"));

	assert(tree2.add("Ace")    && tree2.contains("Ace"));
	assert(tree2.add("Extra1") && tree2.contains("Extra1"));

	assert(tree1 != tree2);
}

/*
* Visit function to test inorderTraverse
* Prints the double of all elements (sorted because inorder)
*/
void intVisit(int& x) {

	std::cout << (x *= 2) << std::endl;
}

/*
* Unit test for inorderTraverse
*/
void inorderTraverse() {

	BinarySearchTree<int> tree(76);

	assert(tree.add(34)  && tree.contains(34));
	assert(tree.add(20)  && tree.contains(20));
	assert(tree.add(55)  && tree.contains(55));
	assert(tree.add(98)  && tree.contains(98));
	assert(tree.add(81)  && tree.contains(81));
	assert(tree.add(190) && tree.contains(190));

	tree.inorderTraverse(intVisit);
}

/*
* Unit test for readTree
*/
void readTree() {

	BinarySearchTree<int> tree(76);

	int arr1[6] {34, 20, 55, 98, 81, 190};

	for (int num : arr1) {

		assert(tree.add(num) && tree.contains(num));
	}

	int arr2[9] {0, 2, 12, 25, 50, 75, 87, 97, 100};
	tree.readTree(arr2, 9);

	for (int num : arr1) {

		assert(!tree.contains(num));
	}

	BinarySearchTree<int> temp;

	for (int num : arr2) {

		assert(tree.contains(num));

		assert(temp.add(num) && temp.contains(num));
	}

	assert(tree != temp && tree.getNumberOfNodes() == temp.getNumberOfNodes()
						&& tree.getHeight() == 4);
}

/*
* Unit test for rebalance
*/
void rebalance() {
	
	BinarySearchTree<char> tree;

	char alphabet[26];

	for (int i(0); i < 26; ++i) {
		
		alphabet[i] = static_cast<char>(i + 65);

		tree.add(alphabet[i]);
	}

	BinarySearchTree<char> temp(tree);

	tree.rebalance();

	assert(tree != temp && tree.getNumberOfNodes() == temp.getNumberOfNodes()
					    && tree.getHeight() == 5);
}

/*
* Asserts that item is removed from tree and displays to check in case of
* inorder succesor replacement
* @param tree The tree to call remove on
* @param item The item to remove
*/
template <class T>
void assertRemoveDisplay(BinarySearchTree<T>* treePtr, const T& item) {
	
	assert(treePtr->remove(item) && !treePtr->contains(item));
	treePtr->displaySideways();
	std::cout << std::endl << std::endl << std::endl;
}

/*
* Unit test for remove (not part of assignment)
*/
void remove() {

	BinarySearchTree<long> tree;

	long arr[9] {3400, 3750, 4560, 4981, 5560, 6109, 6600, 8001, 9000};

	tree.readTree(arr, 9);

	tree.displaySideways(); std::cout << std::endl << std::endl << std::endl;

	assertRemoveDisplay(&tree, arr[4]);
	assertRemoveDisplay(&tree, arr[7]);
	assertRemoveDisplay(&tree, arr[1]);
	assertRemoveDisplay(&tree, arr[0]);
	assertRemoveDisplay(&tree, arr[5]);
	assertRemoveDisplay(&tree, arr[3]);
	assertRemoveDisplay(&tree, arr[6]);
	assertRemoveDisplay(&tree, arr[2]);
	assertRemoveDisplay(&tree, arr[8]);
}

/*
* Unit test for getCousins
*/
void getCuddies() {
	
	BinarySearchTree<int> tree;
	int arr[9]{3400, 3750, 4560, 4981, 5560, 6109, 6600, 8001, 9000};
	tree.readTree(arr, 9);

	tree.displaySideways();

	std::vector<int> cuddies = tree.getCousins(5560);
	assert(cuddies.empty());

	cuddies = tree.getCousins(6600);
	assert(cuddies.empty());

	cuddies = tree.getCousins(3750);
	assert(cuddies.empty());

	cuddies = tree.getCousins(3400);
	assert(cuddies[0] == 6109 && cuddies[1] == 8001 && cuddies.size() == 2);

	cuddies = tree.getCousins(4560);
	assert(cuddies[0] == 6109 && cuddies[1] == 8001 && cuddies.size() == 2);

	cuddies = tree.getCousins(6109);
	assert(cuddies[0] == 3400 && cuddies[1] == 4560 && cuddies.size() == 2);

	cuddies = tree.getCousins(8001);
	assert(cuddies[0] == 3400 && cuddies[1] == 4560 && cuddies.size() == 2);

	cuddies = tree.getCousins(4981);
	assert(cuddies.empty());

	cuddies = tree.getCousins(9000);
	assert(cuddies.empty());
}

/*
* See the mystery function
*/
void mystery() {
	
	std::cout << "MYSTERY\n";

	BinarySearchTree<char> tree;

	tree.add('E');
	tree.add('B');
	tree.add('A');
	tree.add('C');
	tree.add('D');
	tree.add('G');
	tree.add('I');
	tree.add('H');

	int result = tree.mystery();

	assert(result == 16);

	std::cout << "Final: " << result << std::endl;
}

/*
* Runs all BST unit tests in order
*/
void BSTTests() {
	
	constructor();
	empty();
	contains();
	add();
	getHeight();
	getNumberOfNodes();
	clear();
	equalityOperators();
	inorderTraverse();
	readTree();
	rebalance();
	remove();
	getCuddies();
	mystery();
}

/*
* Unit test for contains
*/
void AVLcontains() {
	
	BinarySearchTree<int>* avl = new AVLTree<int>(4);

	assert(avl->contains(4));
}

/*
* Unit test for add
*/
void AVLadd() {
	
	BinarySearchTree<int>* avl = new AVLTree<int>(100);

	assert(avl->add(150) && avl->contains(150));
	avl->displaySideways();
	std::cout << "\n\n";

	assert(avl->add(200) && avl->contains(200));
	avl->displaySideways();
	std::cout << "\n\n";

	assert(avl->getHeight() == 2);

	assert(avl->add(50) && avl->contains(50));
	avl->displaySideways();
	std::cout << "\n\n";

	assert(avl->add(10) && avl->contains(10));
	avl->displaySideways();
	std::cout << "\n\n";

	assert(avl->getHeight() == 3);
}

/*
* Runs all AVL unit tests in order
*/
void AVLTests() {

	AVLcontains();
	AVLadd();
	
}

/*
* Begins unit testing
*/
int main() {
	
	//BSTTests();

	AVLTests();

	std::cout << "Success!" << std::endl;

	return 0;
}
