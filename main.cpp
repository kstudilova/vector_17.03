#include <iostream>
#include <iomanip>
#include "vector.hpp"

bool testEmptyVector() {
    topit::Vector< int > v;
    return v.isEmpty();
}

bool testNotEmptyVector() {
    topit::Vector< int > v;
    v.pushBack(7);
    return !v.isEmpty() && v.getSize() == 1;
}

bool testSizeAfterPushBacks() {
    topit::Vector< int > v;
    v.pushBack(10);
    v.pushBack(20);
    v.pushBack(30);
    return v.getSize() == 3;
}

bool testSizeAfterPopBack() {
    topit::Vector< int > v;
    v.pushBack(10);
    v.pushBack(20);
    v.pushBack(30);
    v.popBack();
    return v.getSize() == 2;
}

bool testGetCapacity() {
    topit::Vector< int > v;
    v.pushBack(1);
    bool test1 = v.getCapacity() == 1;
    v.pushBack(2);
    bool test2 = v.getCapacity() == 2;
    v.pushBack(3);
    bool test3 = v.getCapacity() == 4;
    return test1 && test2 && test3;
}

bool testPopBackOnEmpty() {
    topit::Vector<int> v;
    v.popBack();
    return v.isEmpty() && v.getSize() == 0;
}

bool testCapacityAfterPopBack() {
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.pushBack(4);
    size_t capAfterPush = v.getCapacity();
    v.popBack();
    v.popBack();
    return v.getCapacity() == capAfterPush;
}

bool testManyPushBack() {
    topit::Vector<int> v;
    for (int i = 0; i < 100; ++i) {
        v.pushBack(i);
    }
    return v.getSize() == 100 && v.getCapacity() >= 100;
}

int main() {
    using test_t = std::pair< const char *, bool(*)() >;
    test_t tests[] = {
        { "Empty vector", testEmptyVector },
        { "Not empty vector", testNotEmptyVector },
        { "Size after pushBacks", testSizeAfterPushBacks },
        { "Size after popBack", testSizeAfterPopBack },
        { "Get capacity growth", testGetCapacity },
        { "PopBack on empty vector", testPopBackOnEmpty },
        { "Capacity after popBack", testCapacityAfterPopBack },
        { "Many pushBack", testManyPushBack }
    };

    const size_t count = sizeof(tests) / sizeof(test_t);

    std::cout << std::boolalpha;
    bool pass = true;

    for (size_t i = 0; i < count; ++i) {
        bool res = tests[i].second();
        std::cout << tests[i].first << ": " << res << "\n";
        pass = pass & res;
    }

    std::cout << "RESULT: " << pass << "\n";
    return 0;
}