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

    void destroy(TreeNode<T>* node);

    void destroy();

    ~AVLTree() {
        destroy();
    }

private:
    TreeNode<T> *root_;
    size_t size_;

    int height(TreeNode<T>* node);

    int balanceFactor(TreeNode<T>* node);

    void updateHeight(TreeNode<T>* node);

    TreeNode<T>* rightRotation(TreeNode<T>* node);

    TreeNode<T>* leftRotation(TreeNode<T>* node);

    TreeNode<T>* balancing(TreeNode<T>* node);

    TreeNode<T>* insert(TreeNode<T>* node, T key, int64_t& operations);

    TreeNode<T>* find(TreeNode<T>* node, T key, int64_t& operations);

    TreeNode<T>* findMin(TreeNode<T>* node);

    TreeNode<T>* erase(TreeNode<T>* node, T key, int64_t& operations);

    TreeNode<T>* eraseMin(TreeNode<T>* node);

    void print(TreeNode<T>* node, size_t level);
};

template <class T>
void AVLTree<T>::insert(T key, int64_t& operations) {
    root_ = insert(root_, key, operations);
}

template <class T>
TreeNode<T>* AVLTree<T>::find(T key, int64_t& operations) {
    TreeNode<T> *res = find(root_, key, operations);
    return res ? res : nullptr;
}

template <class T>
void AVLTree<T>::erase(T key, int64_t& operations) {
    root_ = erase(root_, key, operations);
}

template <class T>
void AVLTree<T>::print() {
    print(root_, 0);
}

template <class T>
int AVLTree<T>::height(TreeNode<T>* node) {
    return node ? node->height : 0;
}

template <class T>
int AVLTree<T>::balanceFactor(TreeNode<T>* node) {
    return height(node->left) - height(node->right);
}

template <class T>
void AVLTree<T>::updateHeight(TreeNode<T>* node) {
    node->height = (height(node->left) > height(node->right) ?
                        height(node->left) :
                        height(node->right))
                    + 1;
}

template <class T>
TreeNode<T>* AVLTree<T>::rightRotation(TreeNode<T>* node) {
    TreeNode<T> *left_child = node->left;
    node->left = left_child->right;
    left_child->right = node;

    updateHeight(node);
    updateHeight(left_child);

    return left_child;
}

template <class T>
TreeNode<T>* AVLTree<T>::leftRotation(TreeNode<T>* node) {
    TreeNode<T>* right_child = node->right;
    node->right = right_child->left;
    right_child->left = node;

    updateHeight(node);
    updateHeight(right_child);

    return right_child;
}

template <class T>
TreeNode<T>* AVLTree<T>::balancing(TreeNode<T>* node) {
    updateHeight(node);

    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->left) < 0) {
            node->left = leftRotation(node->left);
        }
        return rightRotation(node);
    } else if (balanceFactor(node) == -2) {
        if (balanceFactor(node->right) > 0) {
            node->right = rightRotation(node->right);
        }
        return leftRotation(node);
    }

    return node;
}

template <class T>
TreeNode<T>* AVLTree<T>::insert(TreeNode<T>* node, T key, int64_t& operations) {
    if (!node) {
        size_ += 1;
        return new TreeNode<T>(key);
    }

    if (key < node->data) {
        operations += 1;
        node->left = insert(node->left, key, operations);
    } else if (key > node->data) {
        operations += 2;
        node->right = insert(node->right, key, operations);
    } else {
        operations += 2;
    }

    return balancing(node);
}

template <class T>
TreeNode<T>* AVLTree<T>::findMin(TreeNode<T>* node) {
    if (node->left) {
        return findMin(node->left);
    }
    return node;
}

template <class T>
TreeNode<T>* AVLTree<T>::eraseMin(TreeNode<T>* node) {
    if (!node->left) {
        return node->right;
    }

    node->left = eraseMin(node->left);
    return balancing(node);
}

template <class T>
TreeNode<T>* AVLTree<T>::erase(TreeNode<T>* node, T key, int64_t& operations) {
    if (!node) {
        return nullptr;
    }

    if (key < node->data) {
        operations += 1;
        node->left = erase(node->left, key, operations);
    } else if (key > node->data) {
        operations += 2;
        node->right = erase(node->right, key, operations);
    } else {
        operations += 2;
        size_ -= 1;
        if (!node->left && !node->right) {
            // leaf
            delete node;
            node = nullptr;
            return nullptr;
        } else if ((!node->left && node->right) || (node->left && !node->right)) {
            // one child
            if (node->left) {
                node->data = node->left->data;
                delete node->left;
                node->left = nullptr;
            } else {
                node->data = node->right->data;
                delete node->right;
                node->right = nullptr;
            }

            return balancing(node);
        } else {
            // two children
            TreeNode<T>* true_deleting = findMin(node->right);
            node->data = true_deleting->data;

            if (true_deleting->right) {
                true_deleting->data = true_deleting->right->data;
                delete true_deleting->right;
                true_deleting->right = nullptr;
            }

            return balancing(true_deleting);
        }
    }

    return balancing(node);
}

template <class T>
TreeNode<T>* AVLTree<T>::find(TreeNode<T>* node, T key, int64_t& operations) {
    if (!node) {
        return nullptr;
    } else if (node->data == key) {
        operations += 1;
        return node;
    } else if (node->data < key) {
        operations += 2;
        return find(node->right, key, operations);
    } else {
        operations += 2;
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
void AVLTree<T>::destroy(TreeNode<T>* node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

template <class T>
void AVLTree<T>::destroy() {
    destroy(root_);
    root_ = nullptr;
}


#endif //COURSEWORKSECONDCOURSE_AVLTREE_H
