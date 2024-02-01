//
// Created by Maryam Baig on 21/12/23.
//

#ifndef BST_AND_HASH_SEARCH_ENGINE_BSTSEARCHTREE_H
#define BST_AND_HASH_SEARCH_ENGINE_BSTSEARCHTREE_H
#include <iostream>

using namespace std;
struct DocumentItem {
    string documentName;
    int count;
};

struct WordItem {
    string word;

    vector<DocumentItem> documents;
};
template <class Key, class Value>
class BSTsearchTree{
private:
    struct Node{
        Key key;
        Value* value;
        int height;
        Node * left;
        Node * right;
        Node(Key k, Value* v){
            key=k;
            value=v;
            height=-0;
            left=NULL;
            right=NULL;
        }
    };
    Node * root=NULL;

    int Height(Node* x){
        if(x==NULL){
            return -1;
        }
        return x->height;
    }

    Node * insert2( const Key & x, Value* v ,Node * t ){
        if(t == NULL)
        {
            //cout << "Inserting new node with key: " << x << endl;
            return new Node(x,v);
        }
        else if(x < t->key)
        {
            t->left = insert2(x, v,t->left);

        }
        else if(x > t->key)
        {
            t->right = insert2(x, v,t->right);

        }

        t->height = max(Height(t->left), Height(t->right))+1;
        //cout << "Inserting new node with key: " << x << endl;
        return t;
    }
    Node * remove2( const Key & x, Value* v ,Node * t ){
        Node* temp;

        // Element not found
        if(t == NULL)
            return NULL;

            // Searching for element
        else if(x < t->key)
            t->left = remove2(x, v,t->left);
        else if(x > t->key)
            t->right = remove2(x, v,t->right);

            // Element found
            // With 2 children
        else if(t->left && t->right)
        {
            Key d;
            Value * r;
            d = findMin(t->right);
            r= wItem(d);
            t->key = d;
            t->value =r;
            t->right = remove2(t->key,t->value, t->right);
        }
            // With one or zero child
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        if(t == NULL)
            return t;

        t->height = max(Height(t->left), Height(t->right))+1;

        return t;
    }

public:


    BSTsearchTree(Key k , Value* v);
    ~BSTsearchTree();

    const Key  findMin( Node* x) const;
    const Key  findMax( Node* x) const;
    bool find( const Key & x) const;

    Value * wItem(const Key & x) const;

    void makeEmpty(Node* x );
    void inOrderPrint(Node* node) const;
    void printTree( ) const;

    void insert( const Key & x, Value* v );

    void remove( const Key & x, Value* v );

    //const AvlTree & operator=( const AvlTree & rhs );

};

#endif //MARYAM_BAIG_BAIG_MARYAM_HW2_AVLSEARCHTREE_H
template <class Key,class Value>
BSTsearchTree<Key , Value >::BSTsearchTree(Key k, Value* v)
{
    //initialize root as first node
    root=insert2(k,v,root);

}

template <class Key,class Value>
BSTsearchTree<Key , Value >::~BSTsearchTree()
{
    makeEmpty(root);
}


template <class Key,class Value>
const Key BSTsearchTree<Key , Value >::findMin(Node * x)const
{
    Key k="!"; //dummy object of key type
    if(x == NULL)
        //return NULL;instead of null, dummy key type value?
        return k;
    else if(x->left == NULL)
        return x->key;
    else
        return findMin(x->left);
}

template <class Key,class Value>
const Key BSTsearchTree<Key , Value >::findMax(Node * x)const
{
    Key k="!"; //dummy object of key type
    if(x == NULL)
        //return NULL;instead of null, dummy key type value?
        return k;
    else if(x->right == NULL)
        return x->key;
    else
        return findMax(x->right->key);
}

template <class Key,class Value>
bool BSTsearchTree<Key , Value >::find(const Key & x) const
{
    Node *temp = root;

    while (temp != NULL) {
        if (temp->key == x) {
            return true;
        } else if (temp->key > x) {
            // If the x is smaller, move to the left subtree
            temp = temp->left;
        } else {
            // If the x is larger, move to the right subtree
            temp = temp->right;
        }
    }
    return false;
}

//returns the value (WordItem *) of that specific word
template <class Key,class Value>
Value * BSTsearchTree<Key , Value >::wItem(const Key & x) const {
    Node *temp = root;

    while (temp != NULL) {
        if (temp->key == x) {
            return temp->value;
        } else if (temp->key > x) {
            // If the x is smaller, move to the left subtree
            temp = temp->left;
        } else {
            // If the x is larger, move to the right subtree
            temp = temp->right;
        }
    }
    return NULL;
}

template <class Key, class Value>
void BSTsearchTree<Key, Value>::inOrderPrint(Node* node) const {
    if (node != NULL) {
        inOrderPrint(node->left);
        cout << "Key: " << node->key << ", Height: " << node->height << endl;
        inOrderPrint(node->right);
    }
}

template <class Key, class Value>
void BSTsearchTree<Key, Value>::printTree() const {
    cout << "Printing AVL Tree:" << endl;
    inOrderPrint(root);
}

template <class Key,class Value>
void BSTsearchTree<Key , Value >::makeEmpty(Node * x)
{
    if(x == NULL)
        return;
    makeEmpty(x->left);
    makeEmpty(x->right);
    delete x;
}

template <class Key,class Value>
void BSTsearchTree<Key , Value >::insert( const Key & x, Value* v)
{
    //because i need to refer to a pointer inside the tree i need another insert function that works within the class itself
    // since i cant ask plug that in as a parameter in the main
    root = insert2(x, v,root);
}

template <class Key,class Value>
void BSTsearchTree<Key , Value >::remove( const Key & x, Value* v )
{
    root = remove2(x, v,root);
}




