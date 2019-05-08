#include <memory>
#include <fstream>
#include <string>
#include <iostream>

#ifndef BSTREE_H
#define BSTREE_H

class Counter
{
public:
        long insertions = 0;
        long loads = 0;
        long deletions = 0;
        long searches = 0;
        long mins = 0;
        long maxes = 0;
        long successors = 0;
        long inorders = 0;
};

template<typename T>
class Node
{
public:
        T value;
        Node<T> *left;
        Node<T> *right;
        Node<T> *parent;

        Node(T value);
        ~Node();
};

template<typename T>
inline Node<T>::Node(T value)
{
        this->value = value;
        left = right = parent = nullptr;
}

template<typename T>
inline Node<T>::~Node()
{
        //std::cerr << "Destroying node " << this->value << std::endl;
}


template<typename T>
class BinarySearchTree
{
private:
        Node<T>* find(Node<T> *root, T value);
        Node<T>* insert(Node<T>* root, Node<T>* node);
        void inorder(const Node<T> *root);
        T min(Node<T> *root);
        T max(Node<T> *root);
        Node<T>* remove(Node<T> *root, Node<T> *node);
        void clean_tree(Node<T> *root);
public:
        Node<T> *root;
        Counter counter;

        bool load(const std::string filename);
        bool find(T value);
        void insert(T value);
        void inorder();
        void remove(T value);
        T min();
        T max();
        Node<T>* successor(T value);
        BinarySearchTree();
        ~BinarySearchTree();
};




#endif BSTREE_H
