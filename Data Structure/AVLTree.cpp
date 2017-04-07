#include <iostream>
#include <memory>

using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Code for Self-balancing AVL binary search tree
//for any node in AVL tree, difference between left subtree and right subtree at the node is atmost 1
//to implement AVL tree, we need to keep track of height at each node.
///////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
struct AVLTreeNode
{
    T m_Data;
    AVLTreeNode<T>* m_Parent;
    AVLTreeNode<T>* m_LeftChild;
    AVLTreeNode<T>* m_RightChild;
    size_t m_Height;

    AVLTreeNode(T data)
    {
        m_Data = data;
        m_Parent = nullptr;
        m_LeftChild = nullptr;
        m_RightChild = nullptr;
        m_Height = 1;
    }
};


template <class T>
class AVLTree
{
private:
    AVLTreeNode<T>* root = nullptr;

public:
    AVLTree();
    AVLTreeNode<T>* insert(const T& data);
    AVLTreeNode<T>* find(T data);
    //bool del(T data);
    size_t height(AVLTreeNode<T>* node);
    int getBalance(AVLTreeNode<T>* node);
    int max(int a, int b) { return a>b ? a : b; }

    void preOrder() { return preOrder(root); }
    void inOrder() { return inOrder(root); }
    void postOrder() { return postOrder(root);  }

private:
    AVLTreeNode<T>* insert(AVLTreeNode<T>* node,const T& data);
    AVLTreeNode<T>* leftRotate(AVLTreeNode<T>* node);
    AVLTreeNode<T>* rightRotate(AVLTreeNode<T>* node);

    void preOrder(AVLTreeNode<T>* node);
    void inOrder(AVLTreeNode<T>* node);
    void postOrder(AVLTreeNode<T>* node);
};


template <class T>
AVLTree<T>::AVLTree()
{
    root = nullptr;
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::insert(const T& data)
{
    if (root == nullptr)
    {
        AVLTreeNode<T>* newNode = new AVLTreeNode<T>(data);
        root = newNode;
        return root;
    }

    return insert(root, data);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* node, const T& data)
{
    AVLTreeNode<T>* addedNode = nullptr;

    if (data < node->m_Data)
    {
        if (node->m_LeftChild != nullptr)
            addedNode = insert(node->m_LeftChild, data);
        else
        {
            AVLTreeNode<T>* newNode = new AVLTreeNode<T>(data);
            newNode->m_Parent = node;
            node->m_LeftChild = newNode;
            addedNode = newNode;
        }
    }
    else if (data > node->m_Data)
    {
        if (node->m_RightChild != nullptr)
            addedNode = insert(node->m_RightChild, data);
        else
        {
            AVLTreeNode<T>* newNode = new AVLTreeNode<T>(data);
            newNode->m_Parent = node;
            node->m_RightChild = newNode;
            addedNode = newNode;
        }
    }
    else
    {
        //we are not adding anything, simply returning it.
        addedNode = node;
        return addedNode;
    }

    node->m_Height = 1 + max(height(node->m_LeftChild), height(node->m_RightChild));

    int balance = getBalance(node);

    //There are 4 possible cases.
    
    if (balance > 1 && data < node->m_LeftChild->m_Data)
    {
        //Left Left
        return rightRotate(node);
    }

    if (balance < -1 && data > node->m_RightChild->m_Data)
    {
        //Right Right
        return leftRotate(node);
    }

    if (balance > 1 && data > node->m_LeftChild->m_Data)
    {
        //Left Right
        node->m_LeftChild = leftRotate(node->m_LeftChild);
        return rightRotate(node);
    }

    if (balance < -1 && data < node->m_RightChild->m_Data)
    {
        //Right Left
        node->m_RightChild = rightRotate(node->m_RightChild);
        return leftRotate(node);
    }

    return node;
}


template<class T>
size_t AVLTree<T>::height(AVLTreeNode<T>* node)
{
    if (node == nullptr)
        return 0;

    return node->m_Height;
}


/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
template<class T>
AVLTreeNode<T>* AVLTree<T>::leftRotate(AVLTreeNode<T>* node)
{
    auto parent = node->m_Parent;
    auto newNode = node->m_RightChild;
    auto leftSubTreeOfRightChild = newNode->m_LeftChild;

    node->m_RightChild = leftSubTreeOfRightChild;
    if(leftSubTreeOfRightChild != nullptr)
        leftSubTreeOfRightChild->m_Parent = node;

    newNode->m_LeftChild = node;
    node->m_Parent = newNode;

    newNode->m_Parent = parent;
    if (parent)
    {
        //update parent child link;
        if (parent->m_LeftChild == node)
            parent->m_LeftChild = newNode;
        else
            parent->m_RightChild = newNode;
    }
    else
        root = newNode;

    node->m_Height = max(height(node->m_LeftChild), height(node->m_RightChild)) + 1;
    newNode->m_Height = max(height(newNode->m_LeftChild), height(node->m_RightChild)) + 1;

    return newNode;
}


template<class T>
AVLTreeNode<T>* AVLTree<T>::rightRotate(AVLTreeNode<T>* node)
{
    auto parent = node->m_Parent;
    auto newNode = node->m_LeftChild;
    auto rightSubtreeOfLeftChild = newNode->m_RightChild;

    node->m_LeftChild = rightSubtreeOfLeftChild;
    if(rightSubtreeOfLeftChild != nullptr)
        rightSubtreeOfLeftChild->m_Parent = node;

    newNode->m_RightChild = node;
    node->m_Parent = newNode;

    newNode->m_Parent = parent;

    if (parent)
    {
        //update parent child link;
        if (parent->m_LeftChild == node)
            parent->m_LeftChild = newNode;
        else
            parent->m_RightChild = newNode;
    }
    else
        root = newNode;

    node->m_Height = max(height(node->m_LeftChild), height(node->m_RightChild)) + 1;
    newNode->m_Height = max(height(newNode->m_LeftChild), height(node->m_RightChild)) + 1;

    return newNode;
}


/////////////////////////////////////////////////////////
// Get the balance factor for node in AVL tree
////////////////////////////////////////////////////////
template<class T>
int AVLTree<T>::getBalance(AVLTreeNode<T>* node)
{
    if (node == nullptr)
        return 0;

    return height(node->m_LeftChild) - height(node->m_RightChild);
}


template<class T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* node)
{
    if (node != nullptr)
    {
        cout << node->m_Data << " ";
        preOrder(node->m_LeftChild);
        preOrder(node->m_RightChild);
    }
}


template<class T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* node)
{
    if (node != nullptr)
    {
        inOrder(node->m_LeftChild);
        cout << node->m_Data << " ";
        inOrder(node->m_RightChild);
    }
}


template<class T>
void AVLTree<T>::postOrder(AVLTreeNode<T>* node)
{
    if (node != nullptr)
    {
        postOrder(node->m_LeftChild);
        postOrder(node->m_RightChild);
        cout << node->m_Data << " ";
    }
}

int main()
{
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    tree.preOrder();
    cout << endl;
    tree.inOrder();
    cout << endl;
    tree.postOrder();
    cout << endl;


    return 0;
}
