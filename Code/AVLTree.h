#ifndef COURSEWORKSECONDCOURSE_AVLTREE_H
#define COURSEWORKSECONDCOURSE_AVLTREE_H

#include "common.h"

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

    void insert(T key) {
        root_ = insert(root_, key);
    }

    TreeNode<T>* find(T key) {
        TreeNode<T> *res = recursiveFind(root_, key);
        return res ? res : nullptr;
    }

    void erase(T key) {
        root_ = erase(root_, key);
    }

    void print() {
        print(root_, 0);
    }

    ~AVLTree() {
        destroy(root_);
        root_ = nullptr;
        size_ = 0;
    }

private:
    TreeNode<T> *root_;
    int size_;

    int height(TreeNode<T>* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(TreeNode<T>* node) {
        return height(node->left) - height(node->right);
    }

    void updateHeight(TreeNode<T>* node) {
        node->height =
                (height(node->left) > height(node->right) ? height(node->left) : height(node->right)) +
                1;
    }

    TreeNode<T>* rightRotation(TreeNode<T>* node) {
        TreeNode<T> *left_child = node->left;
        node->left = left_child->right;
        left_child->right = node;

        updateHeight(node);
        updateHeight(left_child);

        return left_child;
    }

    TreeNode<T>* leftRotation(TreeNode<T>* node) {
        TreeNode<T>* right_child = node->right;
        node->right = right_child->left;
        right_child->left = node;

        updateHeight(node);
        updateHeight(right_child);

        return right_child;
    }

    TreeNode<T>* balancing(TreeNode<T>* node) {
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

    TreeNode<T>* insert(TreeNode<T>* node, T key) {
        if (!node) {
            ++size_;
            return new TreeNode<T>(key);
        }

        if (key < node->data) {
            node->left = insert(node->left, key);
        } else if (key > node->data) {
            node->right = insert(node->right, key);
        }

        return balancing(node);
    }

    TreeNode<T>* findMin(TreeNode<T>* node) {
        return node->left ? findMin(node->left) : node;
    }

    TreeNode<T>* eraseMin(TreeNode<T>* node) {
        if (!node->left) {
            return node->right;
        }

        node->left = eraseMin(node->left);
        return balancing(node);
    }

    TreeNode<T>* erase(TreeNode<T>* node, T key) {
        if (!node) {
            return nullptr;
        }

        if (key < node->data) {
            node->left = erase(node->left, key);
        } else if (key > node->data) {
            node->right = erase(node->right, key);
        } else {
            --size_;
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

    TreeNode<T>* recursiveFind(TreeNode<T>* node, T key) {
        if (!node) {
            return nullptr;
        } else if (node->data == key) {
            return node;
        } else if (node->data < key) {
            return recursiveFind(node->right, key);
        } else {
            return recursiveFind(node->left, key);
        }
    }

    void print(TreeNode<T>* node, size_t level) {
        if (!node) {
            return;
        }

        print(node->right, level + 1);
        std::cout << std::setw(level * 4) << "" << node->data << "\n";
        print(node->left, level + 1);
    }

    void destroy(TreeNode<T>* node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
};

#endif //COURSEWORKSECONDCOURSE_AVLTREE_H
