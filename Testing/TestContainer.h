#ifndef COURSEWORKSECONDCOURSE_TESTCONTAINER_H
#define COURSEWORKSECONDCOURSE_TESTCONTAINER_H

#include "Utils.h"

template <class T>
class TestContainer {
public:
    explicit TestContainer(size_t batchSize) :
        data_({0, 0, 0, 0, 0, 0}) {
        tests = createTestsBatch<T>(batchSize);
    };

    template <class K>
    void startTests(K dataStructure) {
        for (int i = 0; i < TESTS_AMOUNT; ++i) {
            startInsertionTest(dataStructure);
            startSearchTest(dataStructure);
            startErasureTest(dataStructure);
        }

        // хз как будет реализован подсчёт операций, так что возможно их тоже надо будет делить
        for (auto& i : {1, 3, 5}) {
            data_[i] /= TESTS_AMOUNT;
        }
    }

    template <class K>
    void startInsertionTest(K& dataStructure) {
        auto start = std::chrono::high_resolution_clock::now();
        for (auto& element : tests) {
            dataStructure.insert(element, data_[0]);
        }

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        data_[1] += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    }

    template <class K>
    void startSearchTest(K& dataStructure) {
        auto start = std::chrono::high_resolution_clock::now();
        for (auto& element : tests) {
            dataStructure.find(element, data_[2]);
        }

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        data_[3] += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    }

    template <class K>
    void startErasureTest(K& dataStructure) {
        auto start = std::chrono::high_resolution_clock::now();
        for (auto& element : tests) {
            dataStructure.erase(element, data_[4]);
        }

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        data_[5] += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    }

    std::string getLog();
    
private:
    std::array<int64_t, 6> data_; // 0 - insertionOperations
                                  // 1 - insertionTime
                                  // 2 - searchOperations
                                  // 3 - searchTime
                                  // 4 - erasureOperations
                                  // 5 - erasureTime
    std::vector<T> tests;

    template <class K>
    std::vector<K> createTestsBatch(size_t batchSize) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<K> numericalDistribution(std::numeric_limits<K>::min(), std::numeric_limits<K>::max());

        std::vector<K> testsBatch(batchSize);
        std::generate(testsBatch.begin(), testsBatch.end(), [&](){ return numericalDistribution(gen); });
        return testsBatch;
    }

    template <>
    std::vector<std::string> createTestsBatch<std::string>(size_t batchSize) {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::vector<std::string> testsBatch;
        std::uniform_int_distribution<size_t> lenDistribution(1, 256);
        std::uniform_int_distribution<char> charDistribution(65, 122);

        for (int i = 0; i < batchSize; ++i) {
            std::string testElement(lenDistribution(gen), ' ');
            std::generate(testElement.begin(), testElement.end(), [&](){ return charDistribution(gen); });
            testsBatch.push_back(testElement);
        }

        return testsBatch;
    }
};

template <class T>
std::string TestContainer<T>::getLog() {
    std::vector<std::string> res({std::to_string(tests.size())});

    for (auto& item : data_) {
        res.push_back(std::to_string(item));
        item = 0;
    }

    return Utils::join(res, ",");
}

#endif //COURSEWORKSECONDCOURSE_TESTCONTAINER_H
