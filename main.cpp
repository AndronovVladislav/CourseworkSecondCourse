#include "Testing/TestManager.h"

int main() {
    for (auto& length : STRING_LENGTHS) {
        TestManager<std::string> testManager("string_" + std::to_string(length));
        testManager.startTests();
    }

    TestManager<int> testManagerInt("int");
    testManagerInt.startTests();

    TestManager<double> testManagerDouble("double");
    testManagerDouble.startTests();
    return 0;
}