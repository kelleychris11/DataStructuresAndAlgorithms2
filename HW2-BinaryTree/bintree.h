#ifndef BINTREE_H
#define BINTREE_H
#include "nodedata.h"

class BinTree
{
	//displays tree using inorder traversal
	friend std::ostream& operator << (std::ostream &, const BinTree &);

public:

	//default constructor
	BinTree() {}

	//copy constructor
	BinTree(const BinTree &);

	//destructor, calls makeEmpty
	~BinTree();

	//returns true if tree is empty (root is NULL)
	bool isEmpty() const;

	//empties the tree, deletes all nodes (root is NULL)
	//recurively traverses through all non-NULL nodes
	//deletes children, then root nodes
	void makeEmpty();

	//overriden operator = 
	//copies lhs to rhs
	//recursively traverses through all non-NULL nodes of rhs 
	//and copies values of NodeData to newly created nodes on
	//the lhs in the same position as rhs.
	BinTree& operator=(const BinTree &);

	//return true if both trees contain the same NodeData values
	//in the same node locations.
	//Recursively traverses through both rhs and lhs simultaneously
	//and compares each rhs node to each lhs node. If any node is not
	//the same in both trees, the trees are not equal
	bool operator==(const BinTree &) const;

	//return true if a minimum of one node is not equal in both rhs and lhs
	//utilizes the operator == function
	bool operator!=(const BinTree &) const;

	//inserts a new node into the tree containing the specified NodeData.
	//recursivly traverses the tree comparing the current Node's NodeData
	//with the provided NodeData. If NodeData parameter is less than a Node's
	//NodeData, the new Node is placed to the left of the current node.
	//If NodeData is greater than the current Node's NodeData, the new Node
	//is placed to the right of the current Node.
	bool insert(NodeData*);

	//returns true if the NodeData data of the first parameter is contained
	//in the tree. If found, the addressed is copied to the second NodeData
	//parameter.
	//Recursively traverses the tree comparing each current Node's NodeData
	//to the specified NodeData. 
	bool retrieve(const NodeData &, NodeData* &) const;

	//Displays the tree sideways. 
	//Recursively traverses tree to find and print values.
	void displaySideways() const;

	//return height of tree. The tree root is at height 1.
	//return 0 if parameter value not found.
	//Recursively traverses tree searching for parameter NodeData,
	//tracking each Node height as the tree is traverses.
	int getHeight(const NodeData &) const;

	//fill the paramater NodeData array with values from this tree
	//Uses inorder traveral of the tree.
	//Leaves tree empty.
	//assumes a staticaly allocated array of 100 NULL elements.
	//No error checking
	void bstreeToArray(NodeData*[]);
	
	//builds a balaced BinTree from the provided NodeData* array
	//leaves the array filled with NULLs. 
	//root (recursively) is at (low + high) / 2 where low is the lowest
	//subscript of the array range and high is the highest
	void arrayToBSTree(NodeData*[]);

private:
	struct Node
	{
		NodeData* data;
		Node* left;
		Node* right;
	};
	Node* root = NULL;

	//utility functions

	//recursively searches tree for the specified NodeData key.
	//If found, true is returned.
	bool find(Node * currentRoot, const NodeData& key) const;

	//helps overloaded operator <<
	//traverses tree and adds tree data to 'output' parameter
	void inorderHelper(std::ostream& output, const Node& node) const;

	//helps displaySideways method
	//recursively traverses tree and prints tree data sideways
	void sideways(Node*, int) const;

	//helps insert method
	//inserts a new node into the tree containing the specified NodeData.
	//recursivly traverses the tree comparing the current Node's NodeData
	//with the provided NodeData. If NodeData parameter is less than a Node's
	//NodeData, the new Node is placed to the left of the current node.
	//If NodeData is greater than the current Node's NodeData, the new Node
	//is placed to the right of the current Node.
	bool insertHelper(Node*& root, NodeData*& newData);

	//helps retrieve method
	//Recursively traverses the tree comparing each current Node's NodeData
	//to the specified NodeData. 
	bool retrieveHelper(Node* root, const NodeData& key, NodeData*& reference) const;

	//helps getHeight method
	//Recursively traverses tree searching for parameter NodeData,
	//tracking each Node height as the tree is traverses.
	int getHeightHelper(Node* node, const NodeData& key, int level) const;

	//helps makeEmpty method
	//recurively traverses through all non-NULL nodes
	//deletes children, then root nodes
	void makeEmptyHelper(Node*& root);

	//helps bstreeToArray method.
	//uses recursive, inorder traversal of tree.
	//copies contents of tree to provided array.
	//leaves tree empty.
	void bstreeToArrayHelper(Node*& current, NodeData* dataArray[]);

	//helps arraytoBSTree method
	//root (recursively) is at (low + high) / 2 where low is the lowest
	//subscript of the array range and high is the highest.
	//leaves array filled with NULL values
	void arrayToBSTreeHelper(NodeData* dataArray[], int low, int high);

	//helps overriden operator ==
	//Recursively traverses through both rhs and lhs simultaneously
	//and compares each rhs node to each lhs node. If any node is not
	//the same in both trees, the trees are not equal
	bool operatorCompareHelper(const Node* lhsRoot, const Node* rhsRoot) const;

	//helps overriden operator =
	//recursively traverses through all non-NULL nodes of rhs 
	//and copies values of NodeData to newly created nodes on
	//the lhs in the same position as rhs.
	void operatorEqualHelper(Node*& lhs, const Node* rhs);
};
#endif

