
/*  
    Author: Veronika Dmytryk
    Date: Fall 2019
    Description: A implementation of Binary Search Tree
*/
#include <iostream>
using namespace std;

template <class T>
struct treeNode{
    T data;
    treeNode<T> * right;
    treeNode<T> * left;

    // operator== overriding
    bool operator==(const treeNode& node) const{
        return (data == node.data);
    }

    ~treeNode(){
        delete left;
        delete right;
        left = NULL;
        right = NULL;
    }
};

template <class T>
class BinarySearchTree{
    private:
        treeNode<T> * root;
        void _insert(treeNode<T> * &node, const T& item);
        void _remove(treeNode<T> * &node, T item);
        bool _search(treeNode<T> * node, T item);
        T* _searchNode(treeNode<T> * node, T item);
        void _printInOrder(treeNode<T> * node);
        void _printPostOrder(treeNode<T> * node);
        void _printPreOrder(treeNode<T> * node);
        int _height(treeNode<T> * node);
        T _max(treeNode<T> * node);
        T _min(treeNode<T> * node);
        int findMaxInt(int a, int b);
        void destroy();
        void _destroy(treeNode<T> * &node);
        treeNode<T> * copy() const;
        void _copy(treeNode<T> * &node, treeNode<T> * otherNode) const;
    public:
        BinarySearchTree();
        BinarySearchTree(BinarySearchTree<T>& other);
        void insert(const T& item);
        void printInOrder();
        void printPostOrder();
        void printPreOrder();
        int height();
        T max();
        T min();
        T* searchNode(T item);
        bool search(T item);
        void remove(T item);
        BinarySearchTree<T>& operator=(const BinarySearchTree<T>&);
        ~BinarySearchTree(){
            destroy();
        }; 
};

// constructor
template <class T>
BinarySearchTree<T>::BinarySearchTree(){
    root = NULL;
};

// copy constuctor
template <class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>& other){
    cout<<"CopyConstructor is called"<<endl;
    root = other.copy();
}


// the fucntion copies one node to another
template <class T>
void BinarySearchTree<T>::_copy(treeNode<T> * &node, treeNode<T> * otherNode) const{
    if(otherNode == NULL){
        node = NULL;
        return;
    }
    node = new treeNode<T>();
    node->data = otherNode->data;
    _copy(node->left, otherNode->left);
    _copy(node->right, otherNode->right);
};

// the function copys and returns a new tree
template <class T>
treeNode<T> * BinarySearchTree<T>::copy() const{
    if(root == NULL){
        return nullptr;
    }
    treeNode<T> *newNode = new treeNode<T>();
    _copy(newNode, root);
    return newNode;
};



// Inserts an item into binary search tree - helper function
template <class T>
void BinarySearchTree<T>::_insert(treeNode<T> * &node, const T& item){
    if(node == NULL){
        node = new treeNode<T>();
        node->data = item;
        node->right = NULL;
        node->left = NULL;
    } else if (item < node->data){
        _insert(node->left, item);
    }
    else if (item > node->data){
        _insert(node->right, item);
    }
};

// Inserts an item into binary search tree
template <class T>
void BinarySearchTree<T>::insert(const T& item){
    _insert(root, item);
};


// Prints the values of binary search tree in order - helper function
template <class T>
void BinarySearchTree<T>::_printInOrder(treeNode<T> * node){
    if(node != NULL){
        _printInOrder(node->left);
        cout<<node->data<<" ";
        _printInOrder(node->right);
    }
};

// Prints the values of binary search tree in order
template <class T>
void BinarySearchTree<T>::printInOrder(){
    _printInOrder(root);
};

// Prints the values of binary search tree in pre order - helper function
template <class T>
void BinarySearchTree<T>::_printPreOrder(treeNode<T> * node){
    if(node != NULL){
        cout<<node->data<<" ";
        _printPreOrder(node->left);
        _printPreOrder(node->right);
    }
};

// Prints the values of binary search tree in pre order
template <class T>
void BinarySearchTree<T>::printPreOrder(){
    _printPreOrder(root);
}

// Prints the values of binary search tree in post order - helper function
template <class T>
void BinarySearchTree<T>::_printPostOrder(treeNode<T> * node){
    if(node != NULL){
        _printPostOrder(node->left);
        _printPostOrder(node->right);
        cout<<node->data<<" ";
    }
};

// Prints the values of binary search tree in post order
template <class T>
void BinarySearchTree<T>::printPostOrder(){
    _printPostOrder(root);
};

// Returns the maximum value of the binary search tree - helper function
template <class T>
T BinarySearchTree<T>::_max(treeNode<T> * node){
    if(node->right != NULL){
        return _max(node->right);
    } else {
        return node->data;
    }
};

// Returns the maximum value of the binary search tree
template <class T>
T BinarySearchTree<T>::max(){
    if(root != NULL){
       return _max(root);
    } else {
        return NULL;
    }
};

// Returns the minimum value of the binary search tree - helper function
template <class T>
T BinarySearchTree<T>::_min(treeNode<T> * node){
    if(node->left != NULL){
        return _min(node->left);
    } else {
        return node->data;
    }
};

// Returns the minimum value of the binary search tree
template <class T>
T BinarySearchTree<T>::min(){
    if(root != NULL){
        return _min(root);
    } else {
        return NULL;
    }
};

// Returns maximum integer - helper function
template <class T>
int BinarySearchTree<T>::findMaxInt(int a, int b){
    return (a < b)?b:a;
};

// Returns the hieght of the binary search tree - helper function
template <class T>
int BinarySearchTree<T>::_height(treeNode<T> * node){
    if(node == NULL){
        return 0;
    } else {
        return 1 + findMaxInt(_height(node->left), _height(node->right));
    }
};
// Returns the hieght of the binary search tree
template <class T>
int BinarySearchTree<T>::height(){
    return _height(root) - 1;
};


// Searches an item from binary search tree - helper function
template <class T>
T* BinarySearchTree<T>::_searchNode(treeNode<T> * node, T item){
    if(node == NULL){
        return nullptr;
    }
    if(item == node->data){
        return &(node->data);
    }
    if(item < node->data){
        return _searchNode(node->left, item);
    } else if (item > node->data){
        return _searchNode(node->right, item);
    }
    return nullptr;
};

// Searches an item from binary search tree
template <class T>
T* BinarySearchTree<T>::searchNode(T item){
    return _searchNode(root, item);
}


// Searches an item from binary search tree - helper function
template <class T>
bool BinarySearchTree<T>::_search(treeNode<T> * node, T item){
    if(node == NULL){
        return false;
    }
    if(item == node->data){
        return true;
    }
    if(item < node->data){
        return _search(node->left, item);
    } else if (item > node->data){
        return _search(node->right, item);
    }
    return false;
};

// Searches an item from binary search tree
template <class T>
bool BinarySearchTree<T>::search(T item){
    return _search(root, item);
}

// Removes an item from binary search tree - helper function
template <class T>
void BinarySearchTree<T>::_remove(treeNode<T> * &node, T item){
    if(node != NULL){
        if(item == node->data){
            treeNode<T> *p = node;
            // deleting leaf
            if(node->left == NULL && node->right == NULL){
                node = NULL;
                delete p;
            }
            // deleting a node without left subtree
            else if(node->left == NULL){
                node = node->right;
                delete p;
            }
            // deleting a node without right subtree
            else if(node->right == NULL){
                node = node->left;
                delete p;
            }
            // deleting a node with both subtrees
            else {
                int maxNodeData = _max(node->left);
                node->data = maxNodeData;
                _remove(node->left, maxNodeData);
            }
        } else if (item < node->data){
            _remove(node->left, item);
        } else {
            _remove(node->right, item);
        }
    }
};

// Removes an item from binary search tree
template <class T>
void BinarySearchTree<T>::remove(T item){
    _remove(root, item);
};


// assignment operator overloading
template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& other){
    cout<<"Assignment operator is called"<<endl;
    if(this != &other){
        destroy();
        root = other.copy();
    }
    return *this;
}

// helper function for destroying the tree
template <class T>
void BinarySearchTree<T>::_destroy(treeNode<T> * &node){
    if(node != NULL){
        // cout<<"destructor is called for node: "<<node->data<<endl;
        _destroy(node->left);
        _destroy(node->right);
        delete node;
        node = NULL;
    }
}

// function for destroying the free
template <class T>
void BinarySearchTree<T>::destroy(){
    _destroy(root);
}

