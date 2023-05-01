#ifndef COURSEWORKSECONDCOURSE_TESTMANAGER_H
#define COURSEWORKSECONDCOURSE_TESTMANAGER_H

#include "TestContainer.h"
#include "../Code/AVLTree.h"
#include "../Code/SkipList.h"

template <class K>
class TestManager {
public:
    explicit TestManager(std::string logSuffix) {
        prepareTests();
        prepareLoggers(logSuffix);
    }

    void startTests();

    ~TestManager() {
        deactivateLoggers();
    }
private:
    std::array<std::ofstream, 2> loggers_;
    std::vector<TestContainer<K>> tests;

    void prepareLoggers(std::string& dataStructureContainType);

    void deactivateLoggers();

    void prepareTests();
};

template <class K>
void TestManager<K>::startTests() {
    for (auto& test : tests) {
        test.startTests(AVLTree<K>());
        loggers_[0] << test.getLog();

        test.startTests(SkipList<K>());
        loggers_[1] << test.getLog();
    }
}

template <class K>
void TestManager<K>::prepareLoggers(std::string& logSuffix) {
    std::vector<std::string> bases = {"../Logs/AVLTree_", "../Logs/SkipList_"};
    for (int i = 0; i < loggers_.size(); ++i) {
        loggers_[i].open(bases[i] + logSuffix + ".csv");
        loggers_[i] << "BatchSize,InsertionOperations,InsertionTimeNs,"
                       "SearchOperations,SearchTimeNs,"
                       "ErasureOperations,ErasureTimeNs\n";
    }
}

template <class K>
void TestManager<K>::deactivateLoggers() {
    for (auto& logger : loggers_) {
        if (logger.is_open()) {
            logger.close();
        }
    }
}

template <class K>
void TestManager<K>::prepareTests() {
    for (auto &batchSize: BATCHES_SIZES) {
        tests.push_back(TestContainer<K>(static_cast<size_t>(batchSize)));
    }
}


#endif //COURSEWORKSECONDCOURSE_TESTMANAGER_H
