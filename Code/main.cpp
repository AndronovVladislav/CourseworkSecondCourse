#include "SkipList.h"
#include "AVLTree.h"

int main() {
    SkipList<int> skipList;
//    AVLTree<int> avlTree;

    for (int i = 0; i < 16; ++i) {
        skipList.insert(i);
//        avlTree.insert(i);
    }

    for (int i = 8; i < 24; ++i) {
        auto res1 = skipList.find(i);
        if (res1) {
            std::cout << res1->data << std::endl;
        }
//        auto res2 = avlTree.find(i);
//        printf("%p\n", res2);
//        if (res2) {
//            std::cout << res2->data << std::endl;
//        }
    }

    for (int i = 0; i < 24; ++i) {
        skipList.erase(i);
        skipList.print();
//        avlTree.print();
//        avlTree.erase(i);
        std::cout << std::endl << std::endl;
    }

    return 0;
}