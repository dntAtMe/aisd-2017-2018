
#include <string>
#include "bst.h"
#include "bst.cpp"
#include <ctime>

int main()
{
        auto start_s = clock();
        BinarySearchTree<std::string> tree;

        int n;

        std::cin >> n;

        std::string line;
        std::string command;
        std::string arg;
        for (auto a = 0; a < n; a++)
        {
                std::cin >> command;

                if (command == "insert")
                {
                        std::cin >> arg;
                        tree.insert(arg);
                        continue;
                }
                if (command == "load")
                {
                        std::cin >> arg;
                        tree.load(arg);
                        continue;
                }
                if (command == "delete")
                {
                        std::cin >> arg;
                        tree.remove(arg);
                        continue;
                }
                if (command == "find")
                {
                        std::cin >> arg;
                        tree.find(arg);
                        continue;
                }
                if (command == "min")
                {
                        tree.min();
                        continue;
                }
                if (command == "max")
                {
                        tree.max();
                        continue;
                }
                if (command == "successor")
                {
                        std::cin >> arg;
                        tree.successor(arg);
                        continue;
                }
                if (command == "inorder")
                {
                        tree.inorder();
                        continue;
                }

        }

        auto stop_s = clock();
        std::cerr << "time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC)*1000 << "ms" << std::endl;
        std::cerr << "#insert: " << tree.counter.insertions << std::endl;
        std::cerr << "#load: " << tree.counter.loads << std::endl;
        std::cerr << "#delete: " << tree.counter.deletions << std::endl;
        std::cerr << "#find: " << tree.counter.searches << std::endl;
        std::cerr << "#min: " << tree.counter.mins << std::endl;
        std::cerr << "#max: " << tree.counter.maxes << std::endl;
        std::cerr << "#successor: " << tree.counter.successors << std::endl;
        std::cerr << "#inorder: " << tree.counter.inorders << std::endl;
        return 0;
}
