#include "bst.h"



template<typename T>
BinarySearchTree<T>::BinarySearchTree()
{
    root = nullptr;
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    //std::cerr << "Destroying tree" << std::endl;
    clean_tree(this->root);
    //std::cerr << "Done destroying tree" << std::endl;

}

template<typename T>
void
BinarySearchTree<T>::clean_tree(Node<T> *root)
{
    if (root == nullptr)
        return;
    if (root->left != nullptr)
        clean_tree(root->left);
    if (root->right != nullptr)
        clean_tree(root->right);
    delete root;

}

template<typename T>
bool BinarySearchTree<T>::load(const std::string filename)
{
    counter.loads++;

    std::ifstream file(filename);
    if (!file.is_open()) return false;
    std::string value;
    while (file >> value) this->insert(value);
    return true;
}

template<typename T>
Node<T>*
BinarySearchTree<T>::find(Node<T> *root, T value)
{
    counter.searches++;

    while (root != nullptr   && root->value != value)
    {
        root = (value < root->value) ? root->left : root->right;
    }

    return root;
}

template<typename T>
bool BinarySearchTree<T>::find(T value)
{
    auto result = find(this->root, value);
    std::cout << (result == nullptr ? 0 : 1) << std::endl;
    return result == nullptr ? 0 : 1;
}

template<typename T>
T
BinarySearchTree<T>::min(Node<T> *root)
{
    counter.mins++;
    if (root == nullptr)
    {
        std::cout << std::endl;
        return "";
    }

    auto node = root;

    while (node->left)
        node = node->left;

    std::cout << node->value << std::endl;

    return node->value;
}

template<typename T>
T
BinarySearchTree<T>::min()
{
    auto result = min(this->root);
    return result;
}

template<typename T>
T
BinarySearchTree<T>::max(Node<T> *root)
{
    counter.maxes++;

    if (root == nullptr)
    {
        std::cout << std::endl;
        return "";
    }

    auto node = root;

    while (node->right)
        node = node->right;



    std::cout << node->value << std::endl;

    return node->value;

}

template<typename T>
T
BinarySearchTree<T>::max()
{
    auto result = max(this->root);

    return result;
}

template<typename T>
Node<T>*
BinarySearchTree<T>::successor(T value)
{
    counter.successors++;
    auto node = find(this->root, value);

    if (node == nullptr)
    {
        std::cout << std::endl;
        return nullptr;
    }

    if (node->right)
    {
        node = node->right;
        while (node->left) node = node->left;

        std::cout << node->value << std::endl;
        return node;
    }

    Node<T> *child;

    do
    {
        child = node;
        node = node->parent;
    } while (node && (node->left != child));

    if (node == nullptr)
    {
        std::cout << std::endl;
        return nullptr;
    }

    std::cout << node->value << std::endl;
    return node;
}

template<typename T>
Node<T>*
BinarySearchTree<T>::remove(Node<T> *root, Node<T> *node)
{
    if (node == nullptr)
        return nullptr;
    auto parent = node->parent;

    Node<T> *tmp;


    if ((node->left != nullptr) && (node->right != nullptr))
    {
        tmp = this->remove(root, successor(node->value));
        tmp->left = node->left;
        if (tmp->left != nullptr)
            tmp->left->parent = tmp;
        if (tmp->right != nullptr)
            tmp->right->parent = tmp;
    }
    else
    {
        tmp = (node->left != nullptr) ? node->left : node->right;
    }

    if (tmp != nullptr)
        tmp->parent = parent;
    if (parent == nullptr)
        root = tmp;
    else
        if (parent->left == node)
            parent->left = tmp;
        else
            parent->right = tmp;

    return node;
}

template<typename T>
void
BinarySearchTree<T>::remove(T value)
{
    counter.deletions++;

    auto node = this->find(this->root, value);
    remove(this->root, node);
}

template<typename T>
Node<T>*
BinarySearchTree<T>::insert(Node<T>* root, Node<T> *node)
{
    if (root == nullptr)
        return node;

    if (node->value < root->value)
    {
        root->left = insert(root->left, node);
        root->left->parent = root;
    }
    else if (node->value >= root->value)
    {
        root->right = insert(root->right, node);
        root->right->parent = root;
    }

    return root;
}

template<typename T>
void
BinarySearchTree<T>::insert(T value)
{
    counter.insertions++;

    if (!((value[0] >= 'A' && value[0] <= 'Z') || (value[0] >= 'a' && value[0] <= 'z')))
        value.erase(0, 1);
    if (!((value[value.length() - 1] >= 'A' && value[value.length() - 1] <= 'Z')
          || (value[value.length() - 1] >= 'a' && value[value.length() - 1] <= 'z')))
        value.erase(value.length() - 1, 1);

    auto node = new Node<std::string>(value);
    root = insert(root, node);
}


template<typename T>
void BinarySearchTree<T>::inorder(const Node<T>* root)
{
    if (root == nullptr)
        return;
    inorder(root->left);
    std::cout << root->value << " ";
    inorder(root->right);
}

template<typename T>
void BinarySearchTree<T>::inorder()
{
    counter.inorders++;
    inorder(this->root);
    std::cout << std::endl;
}
