#include "hashmap.h"
#include <iostream>

template <typename T>
Color getColor(RBNode<T> *node)
{
    if (node == nullptr)
        return BLACK;
    return node->color;
}

template <typename T>
void
setColor(RBNode<T> *&node, Color color) {
    if (node == nullptr)
        return;

    node->color = color;
}

template <typename T>
RBTree<T>::RBTree()
{
    root = nullptr;
}

template <typename T>
RBTree<T>::~RBTree()
{
    clean_tree(this->root);
}

template<typename T>
void
RBTree<T>::clean_tree(RBNode<T> *root)
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
bool
RBTree<T>::load(const std::string filename)
{
    counter.loads++;

    std::ifstream file(filename);
    if (!file.is_open()) return false;
    std::string value;
    while (file >> value) this->insert(value);
    return true;
}

template <typename T>
void
RBTree<T>::fix_delete(RBNode<T> *node)
{
    auto parent = node->parent;

    while(node != root && getColor(node) == BLACK)
    {
        RBNode<T> *tmp;
        if(node == node->parent->left)
        {
            tmp = parent->right;
            if (getColor(tmp) == RED)
            {
                std::cout<< "case 1 1" << std::endl;
                tmp->color = BLACK;
                parent->color = RED;
                left_rotate(parent);
                tmp= parent->right;
            }

            if (getColor(tmp->left) == BLACK && getColor(tmp->right) == BLACK)
            {
                std::cout<< "case 1 2" << std::endl;
                tmp->color = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (getColor(tmp->right) == BLACK)
                {
                    std::cout<< "case 1 3" << std::endl;
                    tmp->left->color = BLACK;
                    tmp->color = RED;
                    right_rotate(tmp);
                    tmp = parent->right;
                }
                std::cout<< "case 1 4" << std::endl;
                tmp->color = parent->color;
                parent->color = BLACK;
                if (tmp->right != nullptr)
                    tmp->right->color = BLACK;
                left_rotate(parent);
                node = root;
                parent = nullptr;
            }
        } else
        {
            tmp = parent->left;
            if (getColor(tmp) == RED)
            {
                std::cout<< "case 2 1" << std::endl;
                tmp->color = BLACK;
                parent->color = RED;
                right_rotate(parent);
                tmp= parent->left;
            }

            if (getColor(tmp->left) == BLACK && getColor(tmp->right) == BLACK)
            {
                std::cout<< "case 2 2" << std::endl;
                tmp->color = RED;
                node = node->parent;
                parent = node->parent;
            }
            else
            {
                if (getColor(tmp->left) == BLACK)
                {
                    std::cout<< "case 2 3" << std::endl;
                    tmp->right->color = BLACK;
                    tmp->color = RED;
                    left_rotate(tmp);
                    tmp = parent->left;
                }
                std::cout<< "case 2 4" << std::endl;
                tmp->color = parent->color;
                node->parent->color = BLACK;
                if (tmp->left != nullptr)
                    tmp->left->color = BLACK;
                right_rotate(node->parent);
                node = root;
            }
        }
    }

    setColor(root, BLACK);
}

template<typename T>
RBNode<T> *
RBTree<T>::remove(RBNode<T> *root, RBNode<T> *node)
{
    if (node == nullptr)
    {
        //std::cout << "hi";
        return node;
    }
    RBNode<T> *tmp;
    if (node->left == nullptr || node->right == nullptr)
    {
        tmp = node;
    }
    else
    {
        tmp = successor(node->value);
    }

    RBNode<T> *leaf = nullptr;

    if (tmp->left != nullptr)
        leaf = tmp->left;
    else
        leaf = tmp->right;

    if (leaf != nullptr)
        leaf->parent = tmp->parent;

    if (tmp->parent == nullptr)
        root = leaf;
    else if (tmp == tmp->parent->left)
    {
        tmp->parent->left = leaf;
    }
    else
    {
        tmp->parent->right = leaf;
    }

    if (tmp != node)
        node->value = tmp->value;

    if(!getColor(tmp) == RED)
        fix_delete(leaf);

    return tmp;
}

template<typename T>
void
RBTree<T>::remove(T value)
{
    counter.deletions++;

    auto node = remove(this->root, find(root, value));

    delete node;

}

template <typename T>
RBNode<T> *
RBTree<T>::find(RBNode<T> *root, T value)
{
    if(root == nullptr)
        return nullptr;
    if (root->value == value)
        return root;
    auto r1 = find(root->left, value);
    auto r2 = find(root->right, value);

    //while (root != nullptr   && root->value != value)
    //{
    //root = (value < root->value) ? root->left : root->right;
    //}
    if (r1 != nullptr)
        return r1;
    if (r2 != nullptr)
        return r2;

    return nullptr;
}

template <typename T>
bool
RBTree<T>::find(T value)
{
    counter.searches++;
    auto result = find(this->root, value);
    std::cout << (result == nullptr ? 0 : 1) << std::endl;
    return result == nullptr ? 0 : 1;
}

template <typename T>
RBNode<T>*
RBTree<T>::min(RBNode<T> *root)
{
    counter.mins++;
    if (root == nullptr)
    {
        std::cout << std::endl;
        return nullptr;
    }

    auto node = root;

    while (node->left)
        node = node->left;

    return node;
}

template <typename T>
T
RBTree<T>::min()
{
    auto node = min(this->root);
    std::cout << (node != nullptr ? node->value : "") << std::endl;
    T result;
    return result;
}

template <typename T>
T
RBTree<T>::max(RBNode<T> *root)
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

template <typename T>
T
RBTree<T>::max()
{
    auto result = max(this->root);
    return result;
}

template <typename T>
RBNode<T> *
RBTree<T>::predecessor(T value)
{
    counter.successors++;
    auto node = find(this->root, value);

    if (node == nullptr)
    {
        std::cout << std::endl;
        return nullptr;
    }

    if (node->left)
    {
        node = node->left;
        while (node->right) node = node->right;

        std::cout << node->value << std::endl;
        return node;
    }

    RBNode<T> *child;

    do
    {
        child = node;
        node = node->parent;
    } while (node && (node->right != child));

    if (node == nullptr)
    {
        std::cout << std::endl;
        return nullptr;
    }

    std::cout << node->value << std::endl;
    return node;
}

template <typename T>
RBNode<T> *
RBTree<T>::successor(T value)
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

    RBNode<T> *child;

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

template <typename T>
void
RBTree<T>::inorder(const RBNode<T> *root)
{
    if (root == nullptr)
        return;
    inorder(root->left);
    std::cout << root->value << "(" << colorToString(root->color) << ")" << " ";
    inorder(root->right);
}

std::string
colorToString(Color color)
{
    switch (color)
    {
    case RED:
        return "R";
    case BLACK:
        return "B";
    case DOUBLE_BLACK:
        return "D";
    }

    return "";
}

template <typename T>
void
RBTree<T>::inorder()
{
    counter.inorders++;
    inorder(this->root);
    std::cout << std::endl;
}

template <typename T>
void
RBTree<T>::left_rotate(RBNode<T> *&node)
{
    if (node == nullptr)
        return;

    auto right = node->right;
   // if(node->right == nullptr)
   //     return;
    node->right = right->left;

    if (node->right != nullptr)
        node->right->parent = node;

    right->parent = node->parent;

    if (node->parent == nullptr)
        root = right;
    else if (node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;

    right->left = node;
    node->parent = right;
}

template <typename T>
void
RBTree<T>::right_rotate(RBNode<T> *&node)
{
    auto left = node->left;
    node->left = left->right;

    if (node->left != nullptr)
        node->left->parent = node;

    left->parent = node->parent;

    if (node->parent == nullptr)
        root = left;
    else if (node == node->parent->left)
        node->parent->left = left;
    else
        node->parent->right = left;

    left->right = node;
    node->parent = left;
}

template <typename T>
void
RBTree<T>::fix_insert(RBNode<T> *&node)
{
    RBNode<T> *parent = nullptr;
    RBNode<T> *grandparent = nullptr;
    RBNode<T> *uncle = nullptr;
    while(node != this->root &&  getColor(node) == RED && getColor(node->parent) == RED)
    {
        parent = node->parent;
        grandparent = node->parent->parent;
        if (parent == grandparent->left)
        {
            uncle = grandparent->right;
            if (getColor(uncle) == RED)
            {
                std::cout<< "case 1 1" << std::endl;
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                node = grandparent;
            } else {
                if (node == parent->right)
                {
                    std::cout<< "case 1 2" << std::endl;
                    left_rotate(parent);
                    node = parent;
                    parent = node->parent;
                }
                std::cout<< "case 1 3" << std::endl;
                right_rotate(grandparent);
                auto tmp = getColor(parent);
                setColor(parent, getColor(grandparent) );
                setColor(grandparent, tmp);
                node = parent;
            }
        } else
        {
            uncle = grandparent->left;
            if (getColor(uncle) == RED)
            {
                std::cout<< "case 2 1" << std::endl;
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                node = grandparent;
            } else {
                if (node == parent->left)
                {
                    std::cout<< "case 2 2" << std::endl;
                    right_rotate(parent);
                    node = parent;
                    parent = node->parent;
                }
                std::cout<< "case 2 3" << std::endl;
                left_rotate(grandparent);
                auto tmp = getColor(parent);
                setColor(parent, getColor(grandparent) ) ;
                setColor(grandparent, tmp);
                node = parent;
            }
        }
    }

    setColor(root, BLACK);

}

template <typename T>
RBNode<T>*
RBTree<T>::insert(RBNode<T> *&root, RBNode<T> *&node)
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

template <typename T>
void RBTree<T>::insert(T value)
{
    counter.insertions++;

    if (!((value[0] >= 'A' && value[0] <= 'Z') || (value[0] >= 'a' && value[0] <= 'z')))
        value.erase(0, 1);
    if (!((value[value.length() - 1] >= 'A' && value[value.length() - 1] <= 'Z')
          || (value[value.length() - 1] >= 'a' && value[value.length() - 1] <= 'z')))
        value.erase(value.length() - 1, 1);

    auto node = new RBNode<T>(value);
    root = insert(root, node);
    fix_insert(node);
}

