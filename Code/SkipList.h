#include <iostream>

template <typename T>
struct Node {
    Node<T> *next, *down;
    T data;

    Node(Node<T> *next, Node<T> *down, T data) : next(next), down(down), data(data) {};
    Node() : next(nullptr), down(nullptr), data(-1) {};
};

template <typename T>
class LinkedList {
public:
//    LinkedList(Node<T> *defHead, Node<T> *defTail) : head(defHead), tail(defTail) {
//        head->next = tail;
//    }

    LinkedList() : size(0) {
        head = new Node<T>();
        tail = new Node<T>();
        head->next = tail;
        placeToInsert = head;
    }

    ~LinkedList() {
        auto toDelete = head;
        while (head) {
            head = head->next;
            delete toDelete;
            toDelete = head;
        }

//        auto headDown = head->down;
//        while (head) {
//            auto headCopy = head;
//            auto toDelete = headCopy;
//            while (toDelete) {
//                headCopy = headCopy->next;
//                delete toDelete;
//                toDelete = headCopy;
//            }
//            head = headDown;
//            headDown = head->down;
//        }
    }

    void insert(T defData) {
        placeToInsert->next = new Node<T>(nullptr, nullptr, defData);
        placeToInsert->next->next = tail;
        placeToInsert = placeToInsert->next;
        size += 1;
    }

    void print() {
        auto headCopy = head;
        while (headCopy) {
            auto to_print = headCopy;
            while (to_print) {
                std::cout << to_print->data << " " << (to_print->down ? (std::to_string(to_print->data).length() > 1 && to_print != headCopy  ? " " : "  ") : "");
                to_print = to_print->next;
            }
            std::cout << std::endl;
            headCopy = headCopy->down;
        }
    }

    Node<T> *head;
    Node<T> *tail;
    Node<T> *placeToInsert;
    size_t size;
};

template <typename T>
LinkedList<T>* buildLvl(LinkedList<T>* list) {
    auto upperList = new LinkedList<int>();
    upperList->head->down = list->head;
    upperList->tail->down = list->tail;
    Node<T> *i = list->head->next->next;
//    Node<T> *cur = upperList->head;

    while (i && i->next) {
        upperList->insert(i->data);
        upperList->placeToInsert->down = i;
//        cur->next = new Node<T>(cur->next, i, i->data);
//        cur = cur->next;
        i = i->next->next;
//        upperList.size += 1;
    }
    return upperList;
}

template <typename T>
LinkedList<T>* skipList(LinkedList<T>* l) {
//    LinkedList<T> lvl;
//    auto i = l.head;
//    auto j = lvl.head;
//    while (j && j != l.tail) {
//        i->next = new Node<T>(j->next, nullptr, j->data);
//        i = i->next;
//        j = j->next;
//    }
    while (l->size > 2) {
        l->print();
        l = buildLvl(l);
    }
    return l;
}