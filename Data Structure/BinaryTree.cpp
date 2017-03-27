#include<iostream>
#include<vector>
#include<stack>

using namespace std;

struct BinaryTreeNode
{
	int key;
	int leftIndex;
	int rightIndex;
	int size;
	int parent;

	BinaryTreeNode() 
	{
		this->key = -1;
		this->leftIndex = -1;
		this->rightIndex = -1;
		this->size = -1;
		this->parent = -1;
	};

	BinaryTreeNode(int key, int leftIndex, int rightIndex)
	{
		this->key = key;
		this->leftIndex = leftIndex;
		this->rightIndex = rightIndex;
		this->size = -1;
		this->parent = -1;
	}
};

class BinaryTree
{
public:
	BinaryTree(int numberOfNodes = 0);
	int add_node(int atIndex, int key, int leftIndex, int rightIndex);
	void inorder_recursive(int rootIndex = 0);
	void preorder_recursive(int rootIndex = 0);
	void postorder_recursive(int rootIndex = 0);
	bool is_bst(vector<BinaryTreeNode>& list, int rootIndex = 0);
	/*
	void inorder_iterative(int rootIndex = 0);
	void preorder_iterative(int rootIndex = 0);
	void postorder_iterative(int rootIndex = 0);
	*/

private:
	vector<BinaryTreeNode> mBinarySearchTree;
};

BinaryTree::BinaryTree(int numberOfNodes)
	:mBinarySearchTree(numberOfNodes)
{
}

int BinaryTree::add_node(int atIndex, int key, int leftIndex, int rightIndex) 
{
	if (atIndex >= mBinarySearchTree.size())
		return -1;

	mBinarySearchTree.at(atIndex).key = key;
	mBinarySearchTree.at(atIndex).leftIndex = leftIndex;
	mBinarySearchTree.at(atIndex).rightIndex = rightIndex;

	if(leftIndex>=0 && leftIndex< mBinarySearchTree.size())
		mBinarySearchTree.at(leftIndex).parent = atIndex;

	if (rightIndex >= 0 && rightIndex< mBinarySearchTree.size())
		mBinarySearchTree.at(rightIndex).parent = atIndex;

	return atIndex;
}

void BinaryTree::inorder_recursive(int rootIndex)
{
	//if index = -1, return
	//call inorder_recursive on leftindex
	//print root, 
	//then call inorder_recursive on rightindex

	if (rootIndex < 0 || rootIndex >= mBinarySearchTree.size())
		return;
	else
	{
		auto node = mBinarySearchTree.at(rootIndex);
		inorder_recursive(node.leftIndex);
		cout << node.key << " ";
		inorder_recursive(node.rightIndex);
	}
}

void BinaryTree::preorder_recursive(int rootIndex)
{
	// if index == -1 then return
	// else
	// print(rootIndex)
	// preorder_recursive(rootIndex->left)
	// preorder_recursive(rootIndex->right)

	if (rootIndex < 0 || rootIndex >= mBinarySearchTree.size())
		return;
	else
	{
		auto node = mBinarySearchTree.at(rootIndex);
		cout << node.key << " ";
		preorder_recursive(node.leftIndex);
		preorder_recursive(node.rightIndex);
	}
}

void BinaryTree::postorder_recursive(int rootIndex)
{
	// if index == -1 then return
	// else 
	// postorder_recursive(rootIndex->left)
	// postorder_recursive(rootIndex->right)
	// print(rootIndex)

	if (rootIndex < 0 || rootIndex >= mBinarySearchTree.size())
		return;
	else
	{
		auto node = mBinarySearchTree.at(rootIndex);
		postorder_recursive(node.leftIndex);
		postorder_recursive(node.rightIndex);
		cout << node.key << " ";
	}
}

bool BinaryTree::is_bst(vector<BinaryTreeNode>& list, int rootIndex)
{
	if (rootIndex < 0 || rootIndex >= mBinarySearchTree.size())
		return true;
	else
	{
		auto node = mBinarySearchTree.at(rootIndex);
		auto retval1 = is_bst(list,node.leftIndex);
		if (!retval1)
			return false;

		if (list.size() > 0)
		{
			if (list.back().key > node.key)
				return false;
			else if (list.back().key == node.key)
			{
				if (list.back().parent == rootIndex)
					if (node.leftIndex != -1 && mBinarySearchTree.at(node.leftIndex).key == list.back().key)
						return false;
			}
		}
		list.push_back(node);

		auto retval3 = is_bst(list,node.rightIndex);
		if (!retval3)
			return false;
	}
}

void test_binary_tree()
{
	int numberOfNodes;
	cin >> numberOfNodes;
	BinaryTree tree(numberOfNodes);
	for (int index = 0; index < numberOfNodes; index++)
	{
		int key, left_index, right_index;
		cin >> key >> left_index >> right_index;
		tree.add_node(index, key, left_index, right_index);
	}

	tree.inorder_recursive();
	cout  << endl;
	tree.preorder_recursive();
	cout << endl;
	tree.postorder_recursive();
	cout << endl;
}


void test_if_binary_search_tree()
{
	int numberOfNodes;
	cin >> numberOfNodes;
	BinaryTree tree(numberOfNodes);
	for (int index = 0; index < numberOfNodes; index++)
	{
		int key, left_index, right_index;
		cin >> key >> left_index >> right_index;
		tree.add_node(index, key, left_index, right_index);
	}
	vector<BinaryTreeNode> sortedList(0);
	if (tree.is_bst(sortedList))
		cout << "CORRECT" << endl;
	else
		cout << "INCORRECT" << endl;
}

int main(void)
{
	test_if_binary_search_tree();
	return 0;
}
