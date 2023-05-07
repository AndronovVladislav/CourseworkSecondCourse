#ifndef COURSEWORKSECONDCOURSE_TESTMANAGER_H
#define COURSEWORKSECONDCOURSE_TESTMANAGER_H

#include "TestContainer.h"
#include "../Code/AVLTree.h"
#include "../Code/SkipList.h"

template <class K>
class TestManager {
public:
    explicit TestManager(std::string logSuffix) : containedType_(logSuffix), INIT_SIZES({100, 300, 500, 700, 900,
                                                                                         1000, 3000, 5000, 7000, 9000,
                                                                                         10000, 30000, 50000, 70000, 90000,
                                                                                         100000, 300000, 500000, 700000, 900000,
                                                                                         1000000, 3000000, 5000000, 7000000, 9000000})
                                                                                         {
        prepareLoggers(logSuffix);
    }

    void startTests();

    ~TestManager() {
        deactivateLoggers();
    }
private:
    std::array<std::ofstream, 2> loggers_;
    std::string containedType_;
    std::vector<TestContainer<K>> tests;
    std::vector<int> INIT_SIZES;

    void prepareLoggers(std::string& logSuffix);

    void deactivateLoggers();
};

template <class K>
void TestManager<K>::startTests() {
    for (int i = 0; i < INIT_SIZES.size(); ++i) {
        std::cout << (100 * static_cast<double>(i) / INIT_SIZES.size()) << "% tests of " << containedType_ << " completed!\n";
        auto test = TestContainer<K>(static_cast<size_t>(INIT_SIZES[i]), containedType_);

        test.startTests(AVLTree<K>());
        loggers_[0] << test.getLog();

        test.startTests(SkipList<K>());
        loggers_[1] << test.getLog();
    }

    std::cout << "100% tests of " << containedType_ << " completed!\n";
}

template <class K>
void TestManager<K>::prepareLoggers(std::string& logSuffix) {
    std::vector<std::string> bases = {"../Logs/AVLTree_", "../Logs/SkipList_"};
    for (int i = 0; i < loggers_.size(); ++i) {
        loggers_[i].open(bases[i] + logSuffix + ".csv");
        loggers_[i] << "InitSize," <<
                       "InsertionOperations,InsertionTimeNs,"
                       "SearchOperations,SearchTimeNs,"
                       "ErasureOperations,ErasureTimeNs,"
                       "InitializationOperations,InitializationTimeNs,"
                       "DestructionOperations,DestructionTimeNs,MemoryUsed\n";
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


#endif //COURSEWORKSECONDCOURSE_TESTMANAGER_H
