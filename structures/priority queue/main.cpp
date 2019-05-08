#include <iostream>
#include "prioqueue.h"
#include "prioqueue.cpp"
#include <string>
#include <limits>

int main(void)
{
    std::cout << "main" << std::endl;
    Queue queue(100);
    int n;
    std::cin >> n;
    std::string command;
    for (int i = 0; i < n; i++)
    {
        std::cin >> command;
        if (command == "print")
        {
            queue.print();
            continue;
        }
        if (command == "insert")
        {
            int value;
            float priority;
            std::cin >> value >> priority;
            queue.insert(value, priority);
            continue;
        }
        if (command == "empty")
        {
            std::cout << queue.isEmpty() << std::endl;
            continue;
        }
        if (command == "top")
        {
            auto arg = queue.top();
            if (arg != INT_MIN)
                std::cout << arg;
            std::cout << std::endl;
        }
        if (command == "pop")
        {
            auto arg = queue.pop();
            if (arg != INT_MIN)
                std::cout << arg;
            std::cout << std::endl;
        }
        if (command == "priority")
        {
            int value;
            float priority;
            std::cin >> value >> priority;
            queue.priority(value, priority);
        }
    }
    return 0;
}
