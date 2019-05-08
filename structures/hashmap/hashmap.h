#include <string>
#include "bst.h"
#ifndef HASHMAP_H
#define HASHMAP_H

template <typename V>
class HashNode
{
public:
    V value;
    HashNode<V> *next;
    HashNode(V value) : value(value) {next = nullptr; }
    ~HashNode() {   }
};

template <typename V>
class HashBucket
{
public:
    int size= 0;
    bool isTree = false;
    virtual void print();
    virtual void insert(V value);
    virtual bool find(V value);
    virtual void remove(V value);
    virtual HashNode<V> *getRoot();
    HashBucket();
};

template <typename V>
class HashListBucket : public HashBucket<V>
{
public:
    HashNode<V> *head;
    void insert(V value);
    void print();
    bool find(V value);
    void remove(V value);
    HashNode<V> *getRoot() { return head; }
    HashListBucket() { head = nullptr; }
    ~HashListBucket();
};

template <typename V>
class HashTable
{
public:
    int size;
    int max_list_size;
    HashBucket<V> **buckets;
    Counter counter;

    int hash(V value);
    void insert(V value);
    void print();
    bool find(V value);
    void remove(V value);
    void successor(V value);
    void inorder();
    void min();
    void max();
    bool load(std::string filename);


    HashTable(int size, int max_list_size):size(size), max_list_size(max_list_size)
    {
        buckets = new HashBucket<V>*[size];
        for (auto a = 0; a < size; a++)
        {
            buckets[a] = nullptr;
        }
    }
    ~HashTable();
};



enum Color {RED = 'R', BLACK = 'B', DOUBLE_BLACK = 'D'};
typedef enum Color Color;

template<typename T>
class RBNode
{
public:
    T value;
    Color color;
    RBNode<T> *left;
    RBNode<T> *right;
    RBNode<T> *parent;

    RBNode(T _value):value(_value) { left= right = parent = nullptr; color = RED; }
    ~RBNode() { }

};

template<typename T>
class RBTree : public HashBucket<T>
{
private:
    RBNode<T>* find(RBNode<T> *root, T value);
    RBNode<T> *insert(RBNode<T> *&root, RBNode<T> *&node);
    void fix_insert(RBNode<T> *&node);
    void fix_delete(RBNode<T> *node);
    void inorder(const RBNode<T> *root);
    void left_rotate(RBNode<T> *&node);
    void right_rotate(RBNode<T> *&node);
    RBNode<T>* min(RBNode<T> *root);
    T max(RBNode<T> *root);
    RBNode<T>* remove(RBNode<T> *root, RBNode<T> *node);
    void clean_tree(RBNode<T> *root);
public:
    HashNode<T> *getRoot() {}

    RBNode<T> *root;
    Counter counter;

    bool load(const std::string filename);
    bool find(T value);
    void insert(T value);
    void inorder();
    void remove(T value);
    void print() { inorder(); }
    T min();
    T max();
    RBNode<T>* successor(T value);
    RBNode<T>* predecessor(T value);


    RBTree();
    ~RBTree();
};

#endif // HASHMAP_H
