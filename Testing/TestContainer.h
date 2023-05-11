#ifndef COURSEWORKSECONDCOURSE_TESTCONTAINER_H
#define COURSEWORKSECONDCOURSE_TESTCONTAINER_H

#include "Utils.h"

template <class T>
class TestContainer {
public:
    TestContainer(size_t batchSize, std::string containedType) :
        counters_(9, 0), containedType_(std::move(containedType)) {
        initState_ = createTestsBatch<T>(batchSize);
    };

    template <class K>
    void startTests(K dataStructure) {
        fillDS(dataStructure);

        for (int i = 0; i < TESTS_AMOUNT; ++i) {
            startInsertionTest(dataStructure);
            startSearchTest(dataStructure);
            startErasureTest(dataStructure);
        }

        for (int i = 0; i < 6; ++i) {
            counters_[i] /= TESTS_AMOUNT;
        }

        destroyDS(dataStructure);
    }

    template <class K>
    void fillDS(K& dataStructure) {
        auto start = std::chrono::high_resolution_clock::now();

        for (auto& elem : initState_) {
            dataStructure.insert(elem, counters_[6]);
        }

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        counters_[6] += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();

        auto parsedContainedType = Utils::split({containedType_}, "_");
        counters_[8] = dataStructure.getSize();
        if (parsedContainedType[0] == "string") {
            counters_[8] += initState_.size() * atoi(parsedContainedType[1].c_str());
        }
    }

    template <class K>
    void destroyDS(K& dataStructure) {
        auto start = std::chrono::high_resolution_clock::now();

        dataStructure.destroy();

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        counters_[7] += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    }

    template <class K>
    void startInsertionTest(K& dataStructure) {
        auto start = std::chrono::high_resolution_clock::now();
        dataStructure.insert(testingElement_, counters_[0]);

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        counters_[1] += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    }

    template <class K>
    void startSearchTest(K& dataStructure) {
        auto start = std::chrono::high_resolution_clock::now();
        dataStructure.find(testingElement_, counters_[2]);

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        counters_[3] += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    }

    template <class K>
    void startErasureTest(K& dataStructure) {
        auto start = std::chrono::high_resolution_clock::now();
        dataStructure.erase(testingElement_, counters_[4]);

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        counters_[5] += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    }

    std::string getLog();
    
private:
    std::vector<int64_t> counters_;    // 0 - insertionOperations
                                       // 1 - insertionTime
                                       // 2 - searchOperations
                                       // 3 - searchTime
                                       // 4 - erasureOperations
                                       // 5 - erasureTime
                                       // 6 - initializationTime
                                       // 7 - destructionTime
                                       // 8 - memoryUsed
    std::vector<T> initState_;
    std::string containedType_;
    T testingElement_;

    template <class K>
    std::vector<K> createTestsBatch(size_t batchSize) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<K> numericalDistribution(std::numeric_limits<K>::min(), std::numeric_limits<K>::max());

        std::vector<K> testsBatch(batchSize);
        std::generate(testsBatch.begin(), testsBatch.end(), [&](){ return numericalDistribution(gen); });
        testingElement_ = numericalDistribution(gen);
        return testsBatch;
    }

    template <>
    std::vector<std::string> createTestsBatch<std::string>(size_t batchSize) {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::vector<std::string> testsBatch;
        std::uniform_int_distribution<char> charDistribution(65, 122);
        auto parsedContainedType = Utils::split({containedType_}, "_");
        size_t length = std::stoi(parsedContainedType[parsedContainedType.size() - 1]);

        for (int i = 0; i < batchSize; ++i) {
            std::string testElement(length, ' ');
            std::generate(testElement.begin(), testElement.end(), [&](){ return charDistribution(gen); });
            testsBatch.push_back(testElement);
        }

        testingElement_.resize(length);
        std::generate(testingElement_.begin(), testingElement_.end(), [&](){ return charDistribution(gen); });
        return testsBatch;
    }
};

template <class T>
std::string TestContainer<T>::getLog() {
    std::vector<std::string> res({std::to_string(initState_.size())});

    for (auto& counter : counters_) {
        res.push_back(std::to_string(counter));
        counter = 0;
    }

    return Utils::join(res, ",");
}

#endif //COURSEWORKSECONDCOURSE_TESTCONTAINER_H
