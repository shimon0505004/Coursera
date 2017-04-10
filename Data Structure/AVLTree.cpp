#include <iostream>
#include <memory>
#include <vector>


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
    AVLTreeNode<T>* root() { return root; }
    AVLTreeNode<T>* insert(const T& data);
    AVLTreeNode<T>* find(const T& data);
    AVLTreeNode<T>* del(const T& data);
    AVLTreeNode<T>* next(AVLTreeNode<T>* node);
    vector<T> rangeSearch(const T& lowerBound, const T& upperBound);
    
    T getMax();
    T getMin();

    void preOrder() { return preOrder(root); }
    void inOrder() { return inOrder(root); }
    void postOrder() { return postOrder(root);  }

    AVLTreeNode<T>* merge(AVLTree<T>* rightSubtree);

private:
    AVLTreeNode<T>* insert(AVLTreeNode<T>* node,const T& data);
    AVLTreeNode<T>* find(AVLTreeNode<T>* node, const T& data);
    AVLTreeNode<T>* del(AVLTreeNode<T>* node, const T& data);
    AVLTreeNode<T>* leftRotate(AVLTreeNode<T>* node);
    AVLTreeNode<T>* rightRotate(AVLTreeNode<T>* node);

    AVLTreeNode<T>* leftDescendent(AVLTreeNode<T>* node);
    AVLTreeNode<T>* rightDescendent(AVLTreeNode<T>* node);
    AVLTreeNode<T>* rightAncestor(AVLTreeNode<T>* node);

    size_t height(AVLTreeNode<T>* node);
    int getBalance(AVLTreeNode<T>* node);

    void preOrder(AVLTreeNode<T>* node);
    void inOrder(AVLTreeNode<T>* node);
    void postOrder(AVLTreeNode<T>* node);

    int max(int a, int b) { return a>b ? a : b; }
};


template <class T>
AVLTree<T>::AVLTree()
{
    root = nullptr;
}


template<class T>
size_t AVLTree<T>::height(AVLTreeNode<T>* node)
{
    if (node == nullptr)
        return 0;

    return node->m_Height;
}


/*
    T1, T2 and T3 are subtrees of the tree rooted with y (on left side)
    or x (on right side)

             y                                  x
            / \     Right Rotation(y)          /  \
           x   T3   – – – – – – – >           T1   y
          / \       < - - - - - - -               / \
         T1  T2     Left Rotation (x)            T2  T3
    
    Keys in both of the above trees follow the following order
    keys(T1) < key(x) < keys(T2) < key(y) < keys(T3)
    So BST property is not violated anywhere.
*/
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
        cout << node->m_Data << endl;
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

    auto 


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
AVLTreeNode<T>* AVLTree<T>::del(const T& data)
{
    return del(root, data);
}


template<class T>
AVLTreeNode<T>* AVLTree<T>::leftDescendent(AVLTreeNode<T>* node)
{
    if (node != nullptr)
    {
        if (node->m_LeftChild == nullptr)
            return node;

        return leftDescendent(node->m_LeftChild);
    }
    return nullptr;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::rightDescendent(AVLTreeNode<T>* node)
{
    if (node != nullptr)
    {
        if (node->m_RightChild == nullptr)
            return node;

        return rightDescendent(node->m_RightChild);
    }
    return nullptr;
}


template<class T>
AVLTreeNode<T>* AVLTree<T>::rightAncestor(AVLTreeNode<T>* node)
{
    if (node->m_Parent != nullptr)
    {
        if (node->m_Data < node->m_Parent->m_Data)
            return node->m_Parent;
        else
            return rightAncestor(node->m_Parent);
    }

    return nullptr;
}


template<class T>
AVLTreeNode<T>* AVLTree<T>::next(AVLTreeNode<T>* node)
{
    if (node != nullptr)
    {
        if (node->m_RightChild != nullptr)
            return leftDescendent(node->m_RightChild);
        else
            return rightAncestor(node);
    }
    return nullptr;
}


template<class T>
AVLTreeNode<T>* AVLTree<T>::del(AVLTreeNode<T>* node, const T& data)
{
    if (node == nullptr)
        return node;

    if (data < node->m_Data)
        node->m_LeftChild = del(node->m_LeftChild, data);
    else if (data > node->m_Data)
        node->m_RightChild = del(node->m_RightChild, data);
    else
    {
        //data is same as node's data.
        //This is the node to be deleted.

        //3 possible cases.
        //1) node has no child : simplest case.
        if (node->m_LeftChild == nullptr && node->m_RightChild == nullptr)
        {
            AVLTreeNode<T>* parent = node->m_Parent;
            if (parent->m_LeftChild == node)
            {
                parent->m_LeftChild = nullptr;
                delete node;
                node = parent->m_LeftChild;
            }
            else
            {
                parent->m_RightChild = nullptr;
                delete node;
                node = parent->m_RightChild;
            }
        }
        else if (node->m_RightChild == nullptr)
        {
            /*
            2) node has one child, on the right
            
                9                               9
                 \                               \
                 15       (delete 15)             20
                   \
                   20

                   or

                9                               9
                 \                               \
                 15       (delete 15)             11
                 /  
               11

               in this case, 
               connect node's parent to the child,
               make child's parent = node's parent,
               delete the node in question,
               return child's pointer.

            */
            AVLTreeNode<T>* parent = node->m_Parent;
            AVLTreeNode<T>* temp = node->m_LeftChild;
            if (parent->m_LeftChild == node)
            {
                parent->m_LeftChild = temp;
                temp->m_Parent = parent;
                delete node;
                node = temp;
            }
            else
            {
                parent->m_RightChild = temp;
                temp->m_Parent = parent;
                delete node;
                node = temp;
            }
        }
        else if (node->m_LeftChild == nullptr)
        {
            /*
            2) node has one child, on the right

                9                               9
               /                               / 
              5       (delete 5)             8
               \
                8

            or

                9                               9
               /                               /
              5       (delete 5)             2
             /
            2

            in this case,
            connect node's parent to the child,
            make child's parent = node's parent,
            delete the node in question,
            return child's pointer.

            */

            AVLTreeNode<T>* parent = node->m_Parent;
            AVLTreeNode<T>* temp = node->m_RightChild;
            if (parent->m_LeftChild == node)
            {
                parent->m_LeftChild = temp;
                temp->m_Parent = parent;
                delete node;
                node = temp;
            }
            else
            {
                parent->m_RightChild = temp;
                temp->m_Parent = parent;
                delete node;
                node = temp;
            }
        }
        else
        {
            /*
                node to be deleted has both leftchild and rightchild.
                In this case, do a regular BST delete.
                In regular BST delete, find the inorder successor N' (smallest in the right subtree). 

                N' may have a right subtree. 

                Copy over N' to N, then delete N'.  
            */

            AVLTreeNode<T>* nodeToReplaceWith = leftDescendent(node->m_RightChild);
            node->m_Data = nodeToReplaceWith->m_Data;
            node->m_RightChild = del(node->m_RightChild, nodeToReplaceWith->m_Data);
        }
    }

    if (node == nullptr)
        return node;

    //STEP 2: update height of current tree
    node->m_Height = max(height(node->m_LeftChild), height(node->m_RightChild)) + 1;

    //STEP 3: check balance factor for this node
    int balance = getBalance(node);

    //If this node becomes unbalanced, there are 4 cases.
    //Left left case
    if (balance > 1 && getBalance(node->m_LeftChild) >= 0)
        return rightRotate(node);

    //Left Right case
    if (balance > 1 && getBalance(node->m_LeftChild) < 0)
    {
        node->m_LeftChild = leftRotate(node->m_LeftChild);
        return rightRotate(node);
    }

    //Right Right case
    if (balance < -1 && getBalance(node->m_RightChild) < 0)
        return leftRotate(node);
   
    //Right Left case
    if (balance < -1 && getBalance(node->m_RightChild) >= 0)
    {
        node->m_RightChild = rightRotate(node->m_RightChild);
        return leftRotate(node);
    }

    return node;
}


template<class T>
AVLTreeNode<T>* AVLTree<T>::find(const T& data)
{
    if (root == nullptr)
        return nullptr;
    else
        return find(root, data);
}


//Find the appropriate node with data in subtree rooted at node* 
//If any node with the given data exists, we will return that node.
//otherwise, return the node where the data should be entered.
template<class T>
AVLTreeNode<T>* AVLTree<T>::find(AVLTreeNode<T>* node, const T& data)
{
    if (node->m_Data > data)
    {
        if (node->m_LeftChild)
            return find(node->m_LeftChild, data);
        return node;
    }
    else if (node->m_Data < data)
    {
        if (node->m_RightChild)
            return find(node->m_RightChild, data);
        return node;
    }
    else
    {
        //(node->m_Data == data)
        return node;
    }
        
}

template<class T>
vector<T> AVLTree<T>::rangeSearch(const T& lowerBound, const T& upperBound)
{
    vector<T> searchResult = vector<T>();
    AVLTreeNode<T>* node = find(lowerBound);
    while (node)
    {
        if(node->m_Data >= lowerBound && node->m_Data <= upperBound)
            searchResult.push_back(node->m_Data);

        node = next(node);
    }

    return searchResult;
}


template<class T>
T AVLTree<T>::getMax()
{
    AVLTreeNode<T>* nodeWithMaxElem = rightDescendent(root);
    return nodeWithMaxElem->m_Data;
}


template<class T>
T AVLTree<T>::getMin()
{
    AVLTreeNode<T>* nodeWithMinElement = leftDescendent(root);
    return nodeWithMinElement->m_Data;
}


//Merge two AVL tree
//All elements in the left subtree will be smaller than 
//all elements in the right subtree
template<class T>
AVLTreeNode<T>* AVLTree<T>::merge(AVLTree<T>* rightSubtree)
{
    if (this->getMax() > rightSubtree->getMin())
    {
        //can not be merged
        return nullptr;
    }

    auto minElement = getMin();
    del(minElement); // deletes node with min element
    AVLTreeNode<T> newRoot(minElement);
    newRoot->m_LeftChild = this->root();
    newRoot->m_RightChild = rightSubtree->root();
    this->root()->m_Parent = newRoot;
    rightSubtree->root()->m_Parent = newRoot;
    this->root = newRoot;

    return this->root();
}


void insert_test()
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
}


void delete_test()
{
    AVLTree<int> tree;
    tree.insert(9);
    tree.insert(5);
    tree.insert(10);
    tree.insert(0);
    tree.insert(6);
    tree.insert(11);
    tree.insert(-1);
    tree.insert(1);
    tree.insert(2);

    cout << "Preorder traversal of constructed tree is : ";
    tree.preOrder();
    cout << endl;

    tree.del(10);

    cout << "Preorder traversal of constructed tree is : ";
    tree.preOrder();
    cout << endl;
}


void find_test()
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

    auto node = tree.find(20);
    if (node)
    {
        cout << "Data: " << node->m_Data << endl;
        if(node->m_Parent)
            cout << "Parent: " << node->m_Parent->m_Data << endl;
    }

    node = tree.find(100);
    if (node)
    {
        cout << "Data: " << node->m_Data << endl;
        if (node->m_Parent)
            cout << "Parent: " << node->m_Parent->m_Data << endl;
    }
}


void next_test()
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

    auto node = tree.find(20);
    auto nextnode = tree.next(node);
    if (node)
    {
        cout << "Data: " << node->m_Data << endl;
        if (node->m_Parent)
            cout << "Parent: " << node->m_Parent->m_Data << endl;
    }

    if (nextnode)
    {
        cout << "Data: " << nextnode->m_Data << endl;
        if (node->m_Parent)
            cout << "Parent: " << nextnode->m_Parent->m_Data << endl;
    }
}


void range_test()
{
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    auto range = tree.rangeSearch(11, 42);
    cout << range.at(0) << endl;
}


void min_test()
{
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    cout << tree.getMin() << endl;
}


void max_test()
{
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    cout << tree.getMax() << endl;
}


int main()
{
    insert_test();
    delete_test();
    find_test();
    next_test();
    range_test();
    min_test();
    max_test();

    return 0;
}
