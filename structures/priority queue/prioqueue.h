#include <iostream>

#ifndef PRIOQUEUE_H
#define PRIOQUEUE_H

class Node
{
public:
    float priority;
    int value;
    Node(){}
    Node(float priority, int value) : priority(priority), value(value) {}
};

class Queue
{
private:
    Node** tab;
    std::size_t max_size;
    std::size_t current_size;
    void heapifyUp(std::size_t idx);
    void heapifyDown(std::size_t idx);
    inline std::size_t getParentIdx(std::size_t idx);
    inline std::size_t getLeftIdx(std::size_t idx);
    inline std::size_t getRightIdx(std::size_t idx);
    inline void swapNodes(std::size_t idx1, std::size_t idx2);

public:
    Queue(std::size_t size) : max_size(size), current_size(0)
    {
        tab = new Node*[max_size];
    }
    inline bool isEmpty();
    inline void print();
    void insert(int value, float priority);
    void priority(int, float);
    int pop();
    int top();
    //Node& operator[](std::size_t index) { if (index < current_size) return tab[index]; }
    ~Queue();
};

Queue::~Queue()
{
    delete[] tab;
}

inline bool
Queue::isEmpty()
{
    return current_size == 0;
}

inline void
Queue::print()
{
    for (auto a = 0; a < current_size; a++)
    {
        std::cout << "(" << tab[a]->value << ", " << tab[a]->priority << ") ";
    }
    std::cout << std::endl;
}

inline std::size_t
Queue::getParentIdx(std::size_t idx)
{
    if (idx == 0)   return 0;
    return (idx - 1) / 2;
}

inline std::size_t
Queue::getLeftIdx(std::size_t idx)
{
    return 2*idx + 1;
}

inline std::size_t
Queue::getRightIdx(std::size_t idx)
{
    return 2*idx + 2;
}

inline void
Queue::swapNodes(std::size_t idx1, std::size_t idx2)
{
    auto priority = tab[idx1]->priority;
    auto value = tab[idx1]->value;
    tab[idx1]->priority = tab[idx2]->priority;
    tab[idx1]->value = tab[idx2]->value;
    tab[idx2]->priority = priority;
    tab[idx2]->value = value;
}
#endif // PRIOQUEUE_H
