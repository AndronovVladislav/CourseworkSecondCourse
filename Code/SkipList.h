#ifndef COURSEWORKSECONDCOURSE_SKIPLIST_H
#define COURSEWORKSECONDCOURSE_SKIPLIST_H

#include "common.h"

template <class T>
struct ListNode {
    ListNode<T> *next, *down;
    T data;

    ListNode(ListNode<T> *next, ListNode<T> *down, T data) : next(next), down(down), data(data) {};
    ListNode(ListNode<T> *next, ListNode<T> *down) : next(next), down(down), data(-1) {};
    ListNode() : next(nullptr), down(nullptr), data(-1) {};
};

template <class T>
class SkipList {
public:
    SkipList() : size(0) {
        tail = new ListNode<T>();
        head = new ListNode<T>(tail, nullptr);
    }

    void insert(T key) {
        ListNode<T> *res = insert(head, key);
        if (res) {
            auto newLvlTail = new ListNode<T>(nullptr, tail);
            auto newLvlHead = new ListNode<T>(newLvlTail, head);
            newLvlHead->next = new ListNode(newLvlHead->next, res, key);

            head = newLvlHead;
            tail = newLvlTail;
        }
//        print();
//        std::cout << "\n\n";
    }

    ListNode<T>* find(T key) {
        auto result = find(head, key)->next;
//        std::cout << result->data << " " << key << std::endl;
        return result->data == key && result->next ? result : nullptr;
    }

    void erase(T key) {
        erase(head, key);
    }

    void print() {
        auto headCopy = head;
        while (headCopy) {
            auto to_print = headCopy;
            while (to_print) {
                std::cout << to_print->data << " ";
//                std::cout << to_print->data << " " << (to_print->down ? (std::to_string(to_print->data).length() > 1 && to_print != headCopy  ? " " : "  ") : "");
                to_print = to_print->next;
            }
            std::cout << std::endl;
            headCopy = headCopy->down;
        }
    }

    ~SkipList() {
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

private:
    ListNode<T> *head;
    ListNode<T> *tail;
    size_t size;

    bool coinFlip() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<double> distribution(0, 1);
        return distribution(gen) < 0.5;
    }

    ListNode<T>* insert(ListNode<T> *res, T key) {
        while (res->next && res->next->next && res->next->data < key) {
            res = res->next;
        }

        ListNode<T>* downListNode = res->down ? insert(res->down, key) : nullptr;
        if (downListNode || !res->down) {
            res->next = new ListNode(res->next, downListNode, key);
            return coinFlip() ? res->next : nullptr;
        }
        return nullptr;
    }

    ListNode<T>* find(ListNode<T>* res, T key) {
        while (res->next && res->next->next && res->next->data < key) {
            res = res->next;
        }
        return !res->down ? res : find(res->down, key);
    }

    void erase(ListNode<T>* res, T key) {
        while (res->next && res->next->next && res->next->data < key) {
            res = res->next;
        }

        if (res->down) {
            erase(res->down, key);
        }

        if (res->next && res->next->data == key) {
            auto toDelete = res->next;
            res->next = res->next->next;
            delete toDelete;
        }
    }
};


#endif //COURSEWORKSECONDCOURSE_SKIPLIST_H
