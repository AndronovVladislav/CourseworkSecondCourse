#ifndef COURSEWORKSECONDCOURSE_SKIPLIST_H
#define COURSEWORKSECONDCOURSE_SKIPLIST_H

#include "../common.h"

template <class T>
struct ListNode {
    ListNode<T> *next, *down;
    T data;

    ListNode(ListNode<T> *next, ListNode<T> *down, T data) : next(next), down(down), data(data) {};
    ListNode(ListNode<T> *next, ListNode<T> *down) : next(next), down(down)/*, data(-1)*/ {};
    ListNode() : next(nullptr), down(nullptr)/*, data(-1)*/ {};
};

template <class T>
class SkipList {
public:
    SkipList() : size_(2) {
        tail = new ListNode<T>();
        head = new ListNode<T>(tail, nullptr);
    }

    void insert(T key, int64_t& operations);

    ListNode<T>* find(T key, int64_t& operations);

    void erase(T key, int64_t& operations);

    void print();

    size_t getSize() {
        return size_ * sizeof(ListNode<T>);
    }

    void destroy();

    ~SkipList() {
        destroy();
    }

private:
    ListNode<T> *head;
    ListNode<T> *tail;
    size_t size_;

    bool coinFlip();

    ListNode<T>* insert(ListNode<T> *res, T key, int64_t& operations);

    ListNode<T>* find(ListNode<T>* res, T key, int64_t& operations);

    void erase(ListNode<T>* res, T key, int64_t& operations);
};


template <class T>
void SkipList<T>::insert(T key, int64_t& operations) {
    ListNode<T> *res = insert(head, key, operations);

    if (res) {
        size_ += 3;
        auto newLvlTail = new ListNode<T>(nullptr, tail);
        auto newLvlHead = new ListNode<T>(newLvlTail, head);
        newLvlHead->next = new ListNode(newLvlHead->next, res, key);

        head = newLvlHead;
        tail = newLvlTail;
    }
}

template <class T>
ListNode<T>* SkipList<T>::find(T key, int64_t& operations) {
    auto result = find(head, key, operations)->next;

    operations += 1;
    if (result->data == key && result->next) {
        return result;
    }

    return nullptr;
}

template <class T>
void SkipList<T>::erase(T key, int64_t& operations) {
    erase(head, key, operations);
}

template <class T>
void SkipList<T>::print() {
    auto headCopy = head;
    while (headCopy) {
        auto to_print = headCopy;
        while (to_print) {
            std::cout << to_print->data << " ";
            to_print = to_print->next;
        }
        std::cout << std::endl;
        headCopy = headCopy->down;
    }
}

template <class T>
bool SkipList<T>::coinFlip() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution distribution(0., 1.);

    return distribution(gen) < 0.5;
}

template <class T>
ListNode<T>* SkipList<T>::insert(ListNode<T> *res, T key, int64_t& operations) {
    while (res->next && res->next->next && res->next->data < key) {
        res = res->next;
        operations += 1;
    }

    operations += 1;
    if (res->next->data == key) {
        return nullptr;
    }

    ListNode<T>* downListNode = res->down ? insert(res->down, key, operations) : nullptr;
    if (downListNode || !res->down) {
        size_ += 1;
        res->next = new ListNode(res->next, downListNode, key);
        return coinFlip() ? res->next : nullptr;
    }

    return nullptr;
}

template <class T>
ListNode<T>* SkipList<T>::find(ListNode<T>* res, T key, int64_t& operations) {
    while (res->next && res->next->next && res->next->data < key) {
        res = res->next;
        operations += 1;
    }

    return !res->down ? res : find(res->down, key, operations);
}

template <class T>
void SkipList<T>::erase(ListNode<T>* res, T key, int64_t& operations) {
    while (res->next && res->next->next && res->next->data < key) {
        res = res->next;
        operations += 1;
    }

    if (res->down) {
        erase(res->down, key, operations);
    }

    if (res->next && res->next->data == key) {
        operations += 1;

        auto toDelete = res->next;
        res->next = res->next->next;
        delete toDelete;

        size_ -= 1;
    }
}

template <class T>
void SkipList<T>::destroy() {
    auto headDown = head->down;

    while (headDown) {
        auto headCopy = head;
        auto toDelete = headCopy;

        while (toDelete) {
            headCopy = headCopy->next;
            delete toDelete;
            toDelete = headCopy;
        }

        head = headDown;
        headDown = head->down;
    }
}

#endif //COURSEWORKSECONDCOURSE_SKIPLIST_H
