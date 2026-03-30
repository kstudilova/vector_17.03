#include <iostream>
#include <iomanip>
#include "vector.hpp"

bool testEmptyVector() {
    std::cout << "__func__" << "\n";
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

bool testInboundElementAccess() {
    topit::Vector< int > v;
    v.pushBack(1);
    try {
        const int & val = v.at(0);
        return val == 1;
    } catch(...) {
        return false;
    }
}

bool testElementOutOfboundAccess() {
    topit::Vector< int > v;
    try {
        const int & val = v.at(0);
        return false;
    } catch (const std::out_of_range &) {
        return true;
    } catch (...) {
        return false;
    }
}

bool testInboundElementConstAccess() {
    topit::Vector< int > v;
    v.pushBack(1);
    const topit::Vector<int> & rv = v;
    try {
        const int & val = v.at(0);
        return val == 1;
    } catch(...) {
        return false;
    }
}

bool testElementOutOfboundConstAccess() {
    const topit::Vector< int > v;
    try {
        v.at(0);
        return false;
    } catch (const std::out_of_range &) {
        return true;
    } catch (...) {
        return false;
    }
}

bool testCopyConstructorForEmpty() {
    topit::Vector< int > v;
    topit::Vector< int > yav = v;
    return v == yav;
}

bool testCopyConstructorForNonEmpty() {
    topit::Vector< int > v;
    v.pushBack(1);
    topit::Vector< int > yav = v;
    try {
        return yav.getSize() == v.getSize() && yav.at(0) == v.at(0);
    }
    catch (...) {  
        return false;
    }
}

bool testInsertSingleAtBeginning()
{
    topit::Vector<int> v{1, 2, 3};
    v.insert(0, 0);
    return (v.getSize() == 4) && (v[0] == 0) && (v[1] == 1) && (v[2] == 2) && (v[3] == 3);
}

bool testInsertSingleAtEnd()
{
    topit::Vector<int> v{1, 2, 3};
    v.insert(3, 4);
    return (v.getSize() == 4) && (v[3] == 4);
}

bool testInitializerList() {
    topit::Vector< int > v {1, 2};
    return v.getSize() == 2 && (v[0] == 1) && (v[1] == 2);
}

//тесты для operator==

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
        { "Many pushBack", testManyPushBack },
        { "Inbound access", testInboundElementAccess},
        { "Out of bound access", testElementOutOfboundAccess},
        { "Inbount const access", testInboundElementConstAccess},
        { "Out of bound const access", testElementOutOfboundConstAccess},
        { "Copy constructor for empty vector", testCopyConstructorForEmpty},
        { "Copy constructor for non empty vector", testCopyConstructorForNonEmpty},
        {"Insert single element at beginning", testInsertSingleAtBeginning},
        {"Insert single element at end", testInsertSingleAtEnd},
        { "Non-empty vector for non-empty initializer list", testInitializerList }
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
    //Подсчёт пройденных/не пройденных тестов
    //Выводить только не прошедшие тесты
    return 0;
}