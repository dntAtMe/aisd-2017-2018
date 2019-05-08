#include "hashmap.h"
#include <boost/crc.hpp>
#include <boost/cstdint.hpp>
#include <iostream>

template <typename V>
HashBucket<V>::HashBucket()
{

}

template <typename V>
void
HashBucket<V>::insert(V value)
{

}

template <typename V>
HashNode<V> *
HashBucket<V>::getRoot()
{

}

template <typename V>
void
HashBucket<V>::remove(V value)
{

}

template <typename V>
void
HashBucket<V>::print()
{

}

template <typename V>
bool
HashBucket<V>::find(V value)
{

}

template <typename V>
void
HashListBucket<V>::remove(V value)
{
    if (head == nullptr)
        return;
    auto node = head;
    if (node->value == value)
    {
        this->size--;
        delete(node);
        head = node->next;
        return;
    }
    while(node->next)
    {
        if (node->next->value == value)
        {
            this->size--;
            auto toRemove = node->next;
            node->next = toRemove->next;
            delete(toRemove);
            return;
        }
    }

}

template <typename V>
bool
HashListBucket<V>::find(V value)
{
    if (head == nullptr)
        return false;
    auto node = head;

    while(node)
    {
        if (node->value == value)
        {
            return true;
        }
        node = node->next;
    }

    return false;
}

template <typename V>
void
HashListBucket<V>::insert(V value)
{
    if (head == nullptr)
    {
        head = new HashNode<V>(value);

        return;
    }

    auto node = this->head;
    while(node->next != nullptr)
        node = node->next;

    node->next = new HashNode<V>(value);

}

template <typename V>
void
HashListBucket<V>::print()
{
    auto node = head;

    while(node != nullptr)
    {
        std::cout << node->value << " ";
        node = node->next;
    }
}

template <typename V>
HashTable<V>::~HashTable()
{

}

template <typename V>
bool
HashTable<V>::load(std::string filename)
{
    counter.loads++;

    std::ifstream file(filename);
    if (!file.is_open()) return false;
    std::string value;
    while (file >> value) this->insert(value);
    return true;
}

template <typename V>
void
HashTable<V>::successor(V value)
{
    std::cout << std::endl;
}

template <typename V>
void
HashTable<V>::inorder()
{
    std::cout << std::endl;
}

template <typename V>
void
HashTable<V>::min()
{
    std::cout << std::endl;
}

template <typename V>
void
HashTable<V>::max()
{
    std::cout << std::endl;
}

template <typename V>
bool
HashTable<V>::find(V value)
{
    counter.searches++;
    int key = hash(value);
    bool result = false;
    if (buckets[key] != nullptr)
        result = buckets[key]->find(value);
    std::cout << result << std::endl;
    return result;
}

template <typename V>
void
HashTable<V>::remove(V value)
{
    counter.deletions++;
    int key = hash(value);
    if (buckets[key] != nullptr)
        buckets[key]->remove(value);
}

template <typename V>
void
HashTable<V>::print()
{
    for (auto a = 0; a < this->size; a++)
    {
        if (this->buckets[a] == nullptr)
            continue;
        this->buckets[a]->print();
        std::cout << std::endl;
    }
}

template<>
int
HashTable<std::string>::hash(std::string value)
{
    boost::crc_32_type result;
    result.process_bytes(value.data(), value.length() );
    return result.checksum() % this->size;
}

template <typename V>
void
HashTable<V>::insert(V value)
{
    counter.insertions++;
    if (!((value[0] >= 'A' && value[0] <= 'Z') || (value[0] >= 'a' && value[0] <= 'z')))
        value.erase(0, 1);
    if (!((value[value.length() - 1] >= 'A' && value[value.length() - 1] <= 'Z')
          || (value[value.length() - 1] >= 'a' && value[value.length() - 1] <= 'z')))
        value.erase(value.length() - 1, 1);

    auto key = hash(value);
    if (this->buckets[key] == nullptr)
    {
        std::cout <<"inserting new bucket key "<< key << " value " << value << std::endl;
        this->buckets[key] = new HashListBucket<V>();
    }
        this->buckets[key]->insert(value);
        this->buckets[key]->size++;

    if (this->buckets[key]->size > 2 && this->buckets[key]->isTree == false)
    {
        RBTree<V> *tree = new RBTree<V>;
        auto head = this->buckets[key]->getRoot();
        while(head != nullptr)
        {
            tree->insert(head->value);
            head = head->next;
        }
        tree->size = this->buckets[key]->size;
        tree->isTree = true;
        delete(this->buckets[key]);
        this->buckets[key] = tree;
    }

}

