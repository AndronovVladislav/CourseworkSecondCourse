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

    void destroy(int64_t& operations);

    ~SkipList() {
        int64_t filler;
        destroy(filler);
    }

private:
    ListNode<T> *head;
    ListNode<T> *tail;
    size_t size_;

    bool coinFlip(int64_t& operations);

    ListNode<T>* insert(ListNode<T> *res, T key, int64_t& operations);

    ListNode<T>* find(ListNode<T>* res, T key, int64_t& operations);

    void erase(ListNode<T>* res, T key, int64_t& operations);
};


template <class T>
void SkipList<T>::insert(T key, int64_t& operations) {
    operations += 3;
    ListNode<T> *res = insert(head, key, operations);

    operations += 1;
    if (res) {
        operations += 19;
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
    operations += 4;
    auto result = find(head, key, operations)->next;

    operations += 2;
    if (result->data == key && result->next) {
        operations += 2;
        return result;
    }

    operations += 1;
    return nullptr;
}

template <class T>
void SkipList<T>::erase(T key, int64_t& operations) {
    operations += 1;
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
bool SkipList<T>::coinFlip(int64_t& operations) {
    // не считаем время на выделение этих переменных, так как они
    // выделяются единожды на весь экземпляр класса
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<double> distribution(0, 1);

    operations += 3;
    return distribution(gen) < 0.5;
}

template <class T>
ListNode<T>* SkipList<T>::insert(ListNode<T> *res, T key, int64_t& operations) {
    operations += 6;
    while (res->next && res->next->next && res->next->data < key) {
        res = res->next;
        operations += 7;
    }

    operations += 3;
    if (res->next->data == key) {
        return nullptr;
    }

    operations += 2; // инициализация + обращение
    ListNode<T>* downListNode;
    if (res->down) {
        operations += 3;
        downListNode = insert(res->down, key, operations);
    } else {
        operations += 1;
        downListNode = nullptr;
    }

    operations += 1;
    if (downListNode) {
        operations += 7;

        size_ += 1;
        res->next = new ListNode(res->next, downListNode, key);

        operations += 1;
        if (coinFlip(operations)) {
            operations += 2;
            return res->next;
        } else {
            operations += 1;
            return nullptr;
        }
    } else if (!res->down) {
        operations += 9; // всё как в прошлой ветке +2 за обращение и инверсию
        size_ += 1;
        res->next = new ListNode(res->next, downListNode, key);

        operations += 1;
        if (coinFlip(operations)) {
            operations += 2;
            return res->next;
        } else {
            operations += 1;
            return nullptr;
        }
    }

    operations += 1;
    return nullptr;
}

template <class T>
ListNode<T>* SkipList<T>::find(ListNode<T>* res, T key, int64_t& operations) {
    operations += 8;
    while (res->next && res->next->next && res->next->data < key) {
        res = res->next;
        operations += 10;
    }

    operations += 2;
    if (!res->down) {
        operations += 1;
        return res;
    } else {
        operations += 2;
        return find(res->down, key, operations);
    }
}

template <class T>
void SkipList<T>::erase(ListNode<T>* res, T key, int64_t& operations) {
    operations += 6;
    while (res->next && res->next->next && res->next->data < key) {
        res = res->next;
        operations += 7;
    }

    operations += 1;
    if (res->down) {
        operations += 1;
        erase(res->down, key, operations);
    }

    operations += 1;
    if (res->next && res->next->data == key) {
        operations += 12; // 4 за вторую часть условия
        auto toDelete = res->next;
        res->next = res->next->next;
        size_ -= 1;
        delete toDelete;
    }
}

template <class T>
void SkipList<T>::destroy(int64_t &operations) {
    operations += 3;
    auto headDown = head->down;

    operations += 1;
    while (headDown) {
        operations += 6;
        auto headCopy = head;
        auto toDelete = headCopy;

        operations += 1;
        while (toDelete) {
            operations += 6;
            headCopy = headCopy->next;
            delete toDelete;
            toDelete = headCopy;

            operations += 1;
        }

        operations += 5;
        head = headDown;
        headDown = head->down;

        operations += 1;
    }
}

#endif //COURSEWORKSECONDCOURSE_SKIPLIST_H
