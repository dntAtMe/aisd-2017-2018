#include "prioqueue.h"
#include "limits.h"

void
Queue::heapifyUp(std::size_t idx)
{
    if (idx == 0)     return;
    auto parentIdx = this->getParentIdx(idx);

    if (tab[parentIdx]->priority > tab[idx]->priority)
    {
        swapNodes(parentIdx, idx);
        heapifyUp(parentIdx);
    }
}

void
Queue::heapifyDown(std::size_t idx)
{
    auto largest = idx;

    auto left = getLeftIdx(idx);
    auto right = getRightIdx(idx);

    if (left < current_size && tab[left]->priority < tab[idx]->priority)
        largest = left;
    if (right < current_size && tab[right]->priority < tab[largest]->priority)
        largest = right;

    if (largest != idx)
    {
        swapNodes(idx, largest);
        heapifyDown(largest);
    }
}

void
Queue::insert(int value, float priority)
{
    if (priority < 0)
        return;
    auto i = current_size;
    current_size++;
    auto node = new Node(priority, value);
    tab[i] = node;
    heapifyUp(i);
}

void
Queue::priority(int value, float priority)
{
    for (auto a = 0; a < current_size; a++)
    {
        if (tab[a]->value == value && tab[a]->priority > priority)
            tab[a]->priority = priority;
    }
}

int
Queue::pop()
{
    if (current_size == 0)
        return INT_MIN;

    auto max = tab[0]->value;
    delete tab[0];
    tab[0] = tab[current_size-1];

    current_size--;
    heapifyDown(0);

    return max;
}

int
Queue::top()
{
    if (current_size == 0)
        return INT_MIN;

    return tab[0]->value;
}
