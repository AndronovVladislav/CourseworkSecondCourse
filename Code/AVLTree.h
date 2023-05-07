#ifndef COURSEWORKSECONDCOURSE_AVLTREE_H
#define COURSEWORKSECONDCOURSE_AVLTREE_H

#include "../common.h"

template <class T>
struct TreeNode {
    T data;
    size_t height;
    TreeNode *left;
    TreeNode *right;

    explicit TreeNode(T key) : left(nullptr), right(nullptr), data(key), height(1) {};
};

template <class T>
class AVLTree {
public:

    AVLTree() : root_(nullptr), size_(0) {};

    void insert(T key, int64_t& operations);

    TreeNode<T>* find(T key, int64_t& operations);

    void erase(T key, int64_t& operations);

    void print();

    size_t getSize() {
        return size_ * sizeof(TreeNode<T>);
    }

    void destroy(TreeNode<T>* node, int64_t& operations);

    void destroy(int64_t& operations);

    ~AVLTree() {
        int64_t filler;
        destroy(filler);
    }

private:
    TreeNode<T> *root_;
    size_t size_;

    int height(TreeNode<T>* node, int64_t& operations);

    int balanceFactor(TreeNode<T>* node, int64_t& operations);

    void updateHeight(TreeNode<T>* node, int64_t& operations);

    TreeNode<T>* rightRotation(TreeNode<T>* node, int64_t& operations);

    TreeNode<T>* leftRotation(TreeNode<T>* node, int64_t& operations);

    TreeNode<T>* balancing(TreeNode<T>* node, int64_t& operations);

    TreeNode<T>* insert(TreeNode<T>* node, T key, int64_t& operations);

    TreeNode<T>* find(TreeNode<T>* node, T key, int64_t& operations);

    TreeNode<T>* findMin(TreeNode<T>* node, int64_t& operations);

    TreeNode<T>* erase(TreeNode<T>* node, T key, int64_t& operations);

    TreeNode<T>* eraseMin(TreeNode<T>* node, int64_t& operations);

    void print(TreeNode<T>* node, size_t level);
};

template <class T>
void AVLTree<T>::insert(T key, int64_t& operations) {
    operations += 2;
    root_ = insert(root_, key, operations);
}

template <class T>
TreeNode<T>* AVLTree<T>::find(T key, int64_t& operations) {
    operations += 5; // инициализация + присваивание + вызов функции + логика + возврат
    TreeNode<T> *res = find(root_, key, operations);
    return res ? res : nullptr;
}

template <class T>
void AVLTree<T>::erase(T key, int64_t& operations) {
    operations += 2;
    root_ = erase(root_, key, operations);
}

template <class T>
void AVLTree<T>::print() {
    print(root_, 0);
}

template <class T>
int AVLTree<T>::height(TreeNode<T>* node, int64_t& operations) {
    operations += 1;
    if (node) {
        operations += 2;
        return node->height;
    }
    operations += 1;
    return 0;
}

template <class T>
int AVLTree<T>::balanceFactor(TreeNode<T>* node, int64_t& operations) {
    operations += 4;
    return height(node->left, operations) - height(node->right, operations);
}

template <class T>
void AVLTree<T>::updateHeight(TreeNode<T>* node, int64_t& operations) {
    operations += 10; // присваивание, 3 вызова функций, 4 обращения, арифметика, логика
    node->height =
            (height(node->left, operations) > height(node->right, operations) ?
                height(node->left, operations) :
                height(node->right, operations)
            ) + 1;
}

template <class T>
TreeNode<T>* AVLTree<T>::rightRotation(TreeNode<T>* node, int64_t& operations) {
    operations += 8;
    TreeNode<T> *left_child = node->left;
    node->left = left_child->right;
    left_child->right = node;

    operations += 2;
    updateHeight(node, operations);
    updateHeight(left_child, operations);

    operations += 1;
    return left_child;
}

template <class T>
TreeNode<T>* AVLTree<T>::leftRotation(TreeNode<T>* node, int64_t& operations) {
    operations += 8;
    TreeNode<T>* right_child = node->right;
    node->right = right_child->left;
    right_child->left = node;

    operations += 2;
    updateHeight(node, operations);
    updateHeight(right_child, operations);

    operations += 1;
    return right_child;
}

template <class T>
TreeNode<T>* AVLTree<T>::balancing(TreeNode<T>* node, int64_t& operations) {
    operations += 1;
    updateHeight(node, operations);

    if (balanceFactor(node, operations) == 2) {
        operations += 4;
        if (balanceFactor(node->left, operations) < 0) {
            operations += 4;
            node->left = leftRotation(node->left, operations);
        }
        operations += 2;
        return rightRotation(node, operations);
    } else if (balanceFactor(node, operations) == -2) {
        operations += 4;
        if (balanceFactor(node->right, operations) > 0) {
            operations += 4;
            node->right = rightRotation(node->right, operations);
        }
        operations += 2;
        return leftRotation(node, operations);
    }

    operations += 2; // 2 "неудачных" сравнения
    return node;
}

template <class T>
TreeNode<T>* AVLTree<T>::insert(TreeNode<T>* node, T key, int64_t& operations) {
    operations += 1;
    if (!node) {
        operations += 7; // возврат + выделение + вызов конструктора + инициализация 4 полей
        size_ += 1;
        return new TreeNode<T>(key);
    }

    if (key < node->data) {
        operations += 5;
        node->left = insert(node->left, key, operations);
    } else if (key > node->data) {
        operations += 5;
        node->right = insert(node->right, key, operations);
    } else {
        operations += 2;
    }

    operations += 1;
    return balancing(node, operations);
}

template <class T>
TreeNode<T>* AVLTree<T>::findMin(TreeNode<T>* node, int64_t& operations) {
    operations += 1;
    if (node->left) {
        operations += 2;
        return findMin(node->left, operations);
    }
    operations += 1;
    return node;
}

template <class T>
TreeNode<T>* AVLTree<T>::eraseMin(TreeNode<T>* node, int64_t& operations) {
    operations += 2;
    if (!node->left) {
        operations += 2;
        return node->right;
    }

    operations += 6;
    node->left = eraseMin(node->left);
    return balancing(node, operations);
}

template <class T>
TreeNode<T>* AVLTree<T>::erase(TreeNode<T>* node, T key, int64_t& operations) {
    operations += 1;
    if (!node) {
        operations += 1;
        return nullptr;
    }

    if (key < node->data) {
        operations += 6;
        node->left = erase(node->left, key, operations);
    } else if (key > node->data) {
        operations += 8;
        node->right = erase(node->right, key, operations);
    } else {
        operations += 6;
        if (!node->left && !node->right) {
            operations += 5;
            // leaf
            size_ -= 1;
            delete node;
            node = nullptr;
            return nullptr;
        } else if ((!node->left && node->right) || (node->left && !node->right)) {
            operations += 10;
            // one child
            if (node->left) {
                operations += 8;
                node->data = node->left->data;
                delete node->left;
                node->left = nullptr;
            } else {
                operations += 8;
                node->data = node->right->data;
                size_ -= 1;
                delete node->right;
                node->right = nullptr;
            }

            operations += 1;
            return balancing(node, operations);
        } else {
            // two children
            operations += 18;
            TreeNode<T>* true_deleting = findMin(node->right, operations);
            node->data = true_deleting->data;

            operations += 1;
            if (true_deleting->right) {
                operations += 8;
                true_deleting->data = true_deleting->right->data;
                size_ -= 1;
                delete true_deleting->right;
                true_deleting->right = nullptr;
            }

            operations += 1;
            return balancing(true_deleting, operations);
        }
    }

    operations += 1;
    return balancing(node, operations);
}

template <class T>
TreeNode<T>* AVLTree<T>::find(TreeNode<T>* node, T key, int64_t& operations) {
    operations += 1;
    if (!node) {
        operations += 1;
        return nullptr;
    } else if (node->data == key) {
        operations += 3;
        return node;
    } else if (node->data < key) {
        operations += 7;
        return find(node->right, key, operations);
    } else {
        operations += 7;
        return find(node->left, key, operations);
    }
}

template <class T>
void AVLTree<T>::print(TreeNode<T>* node, size_t level) {
    if (!node) {
        return;
    }

    print(node->right, level + 1);
    std::cout << std::setw(level * 4) << "" << node->data << "\n";
    print(node->left, level + 1);
}

template <class T>
void AVLTree<T>::destroy(TreeNode<T>* node, int64_t& operations) {
    operations += 1;
    if (node) {
        operations += 7;
        destroy(node->left, operations);
        destroy(node->right, operations);
        delete node;
    }
}

template <class T>
void AVLTree<T>::destroy(int64_t& operations) {
    destroy(root_, operations);
    root_ = nullptr;
}


#endif //COURSEWORKSECONDCOURSE_AVLTREE_H
