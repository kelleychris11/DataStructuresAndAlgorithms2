#include "bintree.h"
std::ostream& operator<< (std::ostream& output, const BinTree & tree)
{
	//check if tree is empty
	if(tree.root == NULL)
	{
		output << "";
	}

	//recursively traverse tree and add NodeData to 'output'
	else
	{
		tree.inorderHelper(output, *tree.root);
	}
	return output;
}

void BinTree::inorderHelper(std::ostream& output, const Node& node) const
{
	if(node.left != NULL)
	{
		inorderHelper(output, *node.left);
	}

	if(node.data != NULL)
	{
		output << *node.data << " ";
	}

	if(node.right!= NULL)
	{
		inorderHelper(output, *node.right);
	}
}

BinTree::BinTree(const BinTree & rhs)
{
	//check if rhs tree is empty
	if (rhs.root == NULL)
	{
		return;
	}

	//recursively traverse lhs and rhs simultaneously
	operatorEqualHelper(root, rhs.root);
}

BinTree::~BinTree()
{
	//delete tree contents
	makeEmpty();
}

bool BinTree::isEmpty() const
{
	if(root == NULL)
	{
		return true;
	}
	return false;
}

void BinTree::makeEmpty()
{
	if(root != NULL)
	{
		//recursively traverse tree deleting all Nodes and NodeData
		makeEmptyHelper(root);
	}
}

void BinTree::makeEmptyHelper(Node*& current)
{
	if(current->left != NULL)
	{
		makeEmptyHelper(current->left);
	}
	if(current->right != NULL)
	{
		makeEmptyHelper(current->right);
	}
	
	//if current Node is a leaf, delete Node and NodeData
	if(current->right == NULL && current->left == NULL)
	{
		delete current->data;
		current->data = NULL;
		delete current;
		current = NULL;
	}
}

BinTree& BinTree::operator= (const BinTree& rhs)
{
	//check if lhsRoot and rhsRoot are the same object
	if(*this == rhs)
	{
		return *this;
	}

	//clear tree of current contents
	makeEmpty();

	//check if rhsRoot is empty
	if(rhs.root == NULL)
	{
		return *this;
	}

	//recursively traverse rhs, creating nodes and copying
	//values in lhs at the same node locations
	operatorEqualHelper(root, rhs.root);
	return *this;
}

void BinTree::operatorEqualHelper(Node*& lhsRoot, const Node* rhsRoot)
{

	//if rhs current Node has a value, copy to lhs current Node
	if(lhsRoot == NULL && rhsRoot != NULL)
	{
		//create new Node and NodeData for lhs current Node
		lhsRoot = new Node;
		lhsRoot->data = new NodeData;
		*lhsRoot->data = *rhsRoot->data;
		lhsRoot->left = NULL;
		lhsRoot->right = NULL;
	}
	//check if more data in left children rhs tree
	if(rhsRoot->left != NULL)
	{
		operatorEqualHelper(lhsRoot->left, rhsRoot->left);
	}

	//check if more data in right children of rhs tree
	if(rhsRoot->right != NULL)
	{
		operatorEqualHelper(lhsRoot->right, rhsRoot->right);
	}
}

bool BinTree::operator== (const BinTree& rhs) const
{
	//check if both sides have the same address
	if(this == &rhs)
	{
		return true;
	}

	//check if both trees are empty
	if(root == NULL && rhs.root == NULL)
	{
		return true;
	}

	//check if lhs tree is empty, but rhs tree is not empty
	if(root == NULL && rhs.root != NULL)
	{
		return false;
	}

	//check if rhs tree is empty, but lhs tree is not empty
	if(root != NULL && rhs.root == NULL)
	{
		return false;
	}

	//if both trees contain data, recursivly traverse both trees
	//simultaneously, comparing each Node and NodeData
	return operatorCompareHelper(root, rhs.root);
}

bool BinTree::operatorCompareHelper(const Node* lhsRoot, const Node* rhsRoot) const
{
	bool isEqual = true;

	//compare NodeData of lhs and rhs Nodes
	if(lhsRoot != NULL && rhsRoot != NULL)
	{
		if(!(*lhsRoot->data == *rhsRoot->data))
		{
			isEqual = false;
		}
	}

	//if both nodes have non-NULL left children, traverse left
	if(lhsRoot->left != NULL && rhsRoot->left != NULL)
	{
		if(!(operatorCompareHelper(rhsRoot->left, lhsRoot->left)))
		{
			isEqual = false;
		}
	}

	//if both nodes have non-NULL right children, traverse right
	if(lhsRoot->right != NULL && rhsRoot->right != NULL)
	{
		if(!(operatorCompareHelper(lhsRoot->right, rhsRoot->right)))
		{
			isEqual = false;
		}
	}

	if(lhsRoot->left == NULL && rhsRoot->left != NULL)
	{
		isEqual = false;
	}
	if(lhsRoot->left != NULL && rhsRoot->left == NULL)
	{
		isEqual = false;
	}
	if(lhsRoot->right == NULL && rhsRoot->right != NULL)
	{
		isEqual = false;
	}
	if (lhsRoot->right != NULL && rhsRoot->right == NULL)
	{
		isEqual = false;
	}
	return isEqual;
}

bool BinTree::operator!= (const BinTree& rhs) const
{
	return !(*this == rhs);
}

bool BinTree::insert(NodeData* newData)
{
	bool success = false;

	//check if new NodeData already exists in tree
	if(!(find(root, *newData)))
	{
		//recursively traverse tree to find place to insert new  NodeData
		success = insertHelper(root, newData);
	}
	return success;
}

bool BinTree::insertHelper(Node*& node, NodeData*& newData)
{
	bool success = false;

	//if current node is empty, inserrt new Node with new NodeData
	if (node == NULL)
	{
		node = new Node;
		node->data = newData;
		node->left = NULL;
		node->right = NULL;
		success = true;
	}

	//if new NodeData is less than the current Node's NodeData
	//traverse left
	else if (*newData < *node->data)
	{
		success =  insertHelper(node->left, newData);
	}

	//if new NodeData is greater than the current Node's NodeData
	//traverse right
	else
	{
		success = insertHelper(node->right, newData);
	}
	return success;
}

bool BinTree::retrieve(const NodeData& key, NodeData* & keyReference) const
{
	bool success = false;

	//recursively traverse tree to find if 'key' exists in tree
	success = retrieveHelper(root, key, keyReference);

	return success;
}
bool BinTree::retrieveHelper(Node* node, const NodeData& key, NodeData*& keyReference) const
{
	bool success = false;

	if(node == NULL)
	{
		success = false;
	}

	//check if current node's NodeData is equal to 'key'
	else if (*(node->data) == key)
	{
		success = true;
		keyReference = node->data;
	}

	//if key not found and key is less than current node's NodeData
	//traverse left
	else if(*(node->data) > key)
	{
		success = retrieveHelper(node->left, key, keyReference);
	}

	//if key not found and key is greater than current node's NodeData
	//traverse right
	else
	{
		success = retrieveHelper(node->right, key, keyReference);
	}
	return success;
}

int BinTree::getHeight(const NodeData& key) const
{
	int level = 0;

	//check if tree is empty
	if(!(root == NULL))
	{
		//recursively traverse tree to find key
		level = getHeightHelper(root, key, level);
	}
	return level;
}

int BinTree::getHeightHelper(Node* node, const NodeData& key, int level) const
{
	level++;
	if(*node->data == key)
	{
		return level;
	}
	
	//if key is less than current node's NodeData, traverse left
	else if(*node->data > key && node->left != NULL)
	{
		return getHeightHelper(node->left, key, level);
	}

	//if key is greater than current node's NodeData, traverse right
	else if(node->right != NULL)
	{
		return getHeightHelper(node->right, key, level);
	}

	//key not found
	else
	{
		return 0;
	}
}

void BinTree::bstreeToArray(NodeData* dataArray [])
{
	//recursive, inorder traversal of tree
	bstreeToArrayHelper(root, dataArray);

	//empty tree once data has been copied to array
	makeEmpty();
}

void BinTree::bstreeToArrayHelper(Node*& current, NodeData* dataArray[])
{
	int count = 0;
	if(current == NULL)
	{
		return;
	}

	//check if left traversal possible
	if(current->left != NULL)
	{
		bstreeToArrayHelper(current->left, dataArray);
	}

	//find next empty index in array to put value
	while(dataArray[count] != NULL)
	{
		count++;
	}

	dataArray[count] = new NodeData;
	*dataArray[count] = *current->data;

	//check if right traversal possible
	if(current->right != NULL)
	{
		bstreeToArrayHelper(current->right, dataArray);
	}
}

void BinTree::arrayToBSTree(NodeData* dataArray[])
{
	int count = 0;

	//check if array is empty
	if (dataArray[0] == NULL)
	{
		return;
	}

	//clear tree if it has existing data
	makeEmpty();

	//find size of array
	while (dataArray[count + 1] != NULL)
	{
		count++;
	}
	
	//recursively traverse array 
	arrayToBSTreeHelper(dataArray, 0, count);
	
	//sets array values to NULL
	for(int i = 0; i < count; i++)
	{
		dataArray[i] = NULL;
	}
}

void BinTree::arrayToBSTreeHelper(NodeData* dataArray[], int low, int high)
{
	int rootIndex = (low + high) / 2;

	//find if dataArray[rootIndex] value already exists in array
	if(!(find(root, *dataArray[rootIndex])))
	{
		insert(dataArray[rootIndex]);
	}

	//while low index is less than high index, continue dividing array
	//and copying values to tree
	if(low < high)
	{
		arrayToBSTreeHelper(dataArray, low, rootIndex);
		arrayToBSTreeHelper(dataArray, rootIndex + 1, high);
	}
}

void BinTree::displaySideways() const
{
	sideways(root, 0);
}

void BinTree::sideways(Node* current, int level) const
{
	//while right child has non-NULL node, continue recursive traversal
	if(current->right != NULL) 
	{
		sideways(current->right, level + 1); 
	}

	//indent for readability, 4 spaces per depth level
	for(int i = level; i >= 0; i--)
	{
		cout << "    ";
	}
		cout << *current->data << endl;

	//while left child has non-NULL node, continue recursive traversal
	if(current->left != NULL)
	{
		sideways(current->left, level + 1);
	}
}

bool BinTree::find(Node * currentRoot, const NodeData& key) const
{
	bool success = false;

	//value not found
	if (currentRoot == NULL)
	{
		success = false;
	}
	else if (*(currentRoot->data) == key)
	{
		success = true;
	}

	//if current Node's NodeData is greater than key, traverse left
	else if (*(currentRoot->data) > key)
	{
		success = find(currentRoot->left, key);
	}

	//if current Node's NodeData is less than key, traverse right
	else
	{
		success = find(currentRoot->right, key);
	}
	return success;
}
