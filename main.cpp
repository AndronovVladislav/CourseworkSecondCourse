#include "Testing/TestManager.h"

int main() {
//    for (auto& length : STRING_LENGTHS) {
//        TestManager<std::string> testManager("string_" + std::to_string(length));
//        testManager.startTests();
//    }

    TestManager<int> testManagerInt("int");
    testManagerInt.startTests();

//    TestManager<double> testManagerDouble("double");
//    testManagerDouble.startTests();

//    SkipList<int> skipList;
//
//    int64_t filler;
//    for (int i = 0; i < 100; ++i) {
//      skipList.insert(i, filler);
//    }
//
//    skipList.print();
//    std::cout << skipList.getSize() << " " << sizeof(ListNode<int>);

    return 0;
}