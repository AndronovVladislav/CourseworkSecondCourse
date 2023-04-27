#include "SkipList.h"

int main() {
    auto list = new LinkedList<int>();

    for (int i = 0; i < 9; ++i) {
        list->insert(i);
    }
//    list.print();

    auto tryToBuildNewLevel = skipList(list);
    tryToBuildNewLevel->print();
    return 0;
}