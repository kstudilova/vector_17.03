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

bool testMoveConstructor() {
  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
    
  size_t old_size = v.getSize();
  topit::Vector<int> moved(std::move(v));
    
  return (moved.getSize() == old_size) && (moved[0] == 1) && (moved[1] == 2) && (moved[2] == 3);
}

bool testMoveAssignment() {
  topit::Vector<int> v1{1, 2, 3};
  topit::Vector<int> v2{10, 20};
    
  v2 = std::move(v1);
    
  return (v2.getSize() == 3) && (v2[0] == 1) && (v2[1] == 2) && (v2[2] == 3);
}

bool testOperatorEqualSameVectors() {
  topit::Vector<int> v1{1, 2, 3};
  topit::Vector<int> v2{1, 2, 3};
  return (v1 == v2);
}

bool testOperatorEqualDifferentVectors() {
  topit::Vector<int> v1{1, 2, 3};
  topit::Vector<int> v2{1, 2, 4};
  return !(v1 == v2);
}

bool testOperatorEqualDifferentSizes() {
  topit::Vector<int> v1{1, 2};
  topit::Vector<int> v2{1, 2, 3};
  return !(v1 == v2);
}

bool testInsertSingleAtBeginning() {
  topit::Vector<int> v{1, 2, 3};
  v.insert(0, 0);
  return (v.getSize() == 4) && (v[0] == 0) && (v[1] == 1) && (v[2] == 2) && (v[3] == 3);
}

bool testInsertSingleAtEnd() {
  topit::Vector<int> v{1, 2, 3};
  v.insert(3, 4);
  return (v.getSize() == 4) && (v[3] == 4);
}

bool testEraseFromMiddle() {
  topit::Vector<int> v{1, 2, 3, 4};
  v.erase(1);
  return (v.getSize() == 3) && (v[0] == 1) && (v[1] == 3) && (v[2] == 4);
}

bool testEraseLastElement() {
  topit::Vector<int> v{1, 2, 3};
  v.erase(2);
  return (v.getSize() == 2) && (v[0] == 1) && (v[1] == 2);
}

bool testInsertRangeFromAnotherVector() {
  topit::Vector<int> v{1, 2, 5};
  topit::Vector<int> src{3, 4};
  v.insert(2, src, 0, 2);
  return (v.getSize() == 5) && (v[2] == 3) && (v[3] == 4) && (v[4] == 5);
}

bool testInsertEmptyRange() {
  topit::Vector<int> v{1, 2, 3};
  topit::Vector<int> src{10, 20};
  v.insert(1, src, 1, 1);
  return (v.getSize() == 3) && (v[0] == 1) && (v[1] == 2) && (v[2] == 3);
}

bool testInsertRangeAtBeginning() {
  topit::Vector<int> v{3, 4};
  topit::Vector<int> src{1, 2};
  v.insert(0, src, 0, 2);
  return (v.getSize() == 4) && (v[0] == 1) && (v[1] == 2) && (v[2] == 3) && (v[3] == 4);
}

bool testEraseRangeFromMiddle() {
  topit::Vector<int> v{1, 2, 3, 4, 5};
  v.erase(1, 3);
  return (v.getSize() == 3) && (v[0] == 1) && (v[1] == 4) && (v[2] == 5);
}

bool testEraseFullRange() {
  topit::Vector<int> v{1, 2, 3};
  v.erase(0, 3);
  return v.isEmpty();
}

bool testEraseEmptyRange() {
  topit::Vector<int> v{1, 2, 3};
  v.erase(1, 1);
  return (v.getSize() == 3) && (v[0] == 1) && (v[1] == 2) && (v[2] == 3);
}

bool testInitializerList() {
  topit::Vector< int > v {1, 2};
  return v.getSize() == 2 && (v[0] == 1) && (v[1] == 2);
}

bool testInsertIterValueAtBeginning() {
  topit::Vector<int> v{1, 2, 3};
  auto it = v.insert(v.begin(), 0);
  return (v.getSize() == 4) && (*it == 0) && (v[0] == 0) && (v[1] == 1);
}

bool testInsertIterValueAtEnd() {
  topit::Vector<int> v{1, 2, 3};
  auto it = v.insert(v.end(), 4);
  return (v.getSize() == 4) && (*it == 4) && (v[3] == 4);
}

bool testInsertIterRangeFromVector() {
  topit::Vector<int> v{1, 2, 5};
  topit::Vector<int> src{3, 4};
  auto it = v.insert(v.begin() + 2, src.begin(), src.end());
  return (v.getSize() == 5) && (*it == 3) && (v[2] == 3) && (v[3] == 4) && (v[4] == 5);
}

bool testInsertIterEmptyRange() {
    topit::Vector<int> v{1, 2, 3};
    topit::Vector<int> src{10, 20};
    auto it = v.insert(v.begin() + 1, src.begin(), src.begin());
    return (v.getSize() == 3) && (it == v.begin() + 1);
}

bool testInsertInitListAtBeginning() {
    topit::Vector<int> v{3, 4, 5};
    auto it = v.insert(v.begin(), {1, 2});
    return (v.getSize() == 5) && (*it == 1) && (v[0] == 1) && (v[1] == 2) && (v[2] == 3);
}

bool testInsertInitListAtEnd() {
    topit::Vector<int> v{1, 2};
    auto it = v.insert(v.end(), {3, 4, 5});
    return (v.getSize() == 5) && (*it == 3) && (v[2] == 3) && (v[3] == 4) && (v[4] == 5);
}

bool testEraseIterMiddle() {
    topit::Vector<int> v{1, 2, 3, 4};
    auto it = v.erase(v.begin() + 1);
    return (v.getSize() == 3) && (v[0] == 1) && (v[1] == 3) && (*it == 3);
}

bool testEraseIterLast() {
    topit::Vector<int> v{1, 2, 3};
    auto it = v.erase(v.end() - 1);
    return (v.getSize() == 2) && (v[0] == 1) && (v[1] == 2) && (it == v.end());
}

bool testEraseIterRange() {
    topit::Vector<int> v{1, 2, 3, 4, 5};
    auto it = v.erase(v.begin() + 1, v.begin() + 3);
    return (v.getSize() == 3) && (v[0] == 1) && (v[1] == 4) && (*it == 4);
}

bool testEraseIterAll() {
    topit::Vector<int> v{1, 2, 3};
    auto it = v.erase(v.begin(), v.end()); 
    return v.isEmpty() && (it == v.end());
}

bool testRemoveIfOdd() {
  topit::Vector<int> v{1, 2, 3, 4, 5, 6};
  v.remove_if([](int x) { return x % 2 != 0; });  // удаляем нечётные
  topit::Vector<int> yav{2, 4, 6};
  return v == yav;
}

bool testRemoveIfGreaterThanTen() {
  topit::Vector<int> v{5, 15, 8, 20, 3, 12};
  v.remove_if([](int x) { return x > 10; });  // удаляем > 10
  topit::Vector<int> yav{5, 8, 3};
  return v == yav;
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
    { "Many pushBack", testManyPushBack },
    { "Inbound access", testInboundElementAccess},
    { "Out of bound access", testElementOutOfboundAccess},
    { "Inbount const access", testInboundElementConstAccess},
    { "Out of bound const access", testElementOutOfboundConstAccess},
    { "Copy constructor for empty vector", testCopyConstructorForEmpty},
    { "Copy constructor for non empty vector", testCopyConstructorForNonEmpty},
    {"Move constructor", testMoveConstructor},
    {"Move assignment", testMoveAssignment},   
    {"Operator== same vectors", testOperatorEqualSameVectors},
    {"Operator== different vectors", testOperatorEqualDifferentVectors},
    {"Operator== different sizes", testOperatorEqualDifferentSizes},
    {"Insert single element at beginning", testInsertSingleAtBeginning},
    {"Insert single element at end", testInsertSingleAtEnd},
    {"Erase element from middle", testEraseFromMiddle},
    {"Erase last element", testEraseLastElement},
    {"Insert range from another vector", testInsertRangeFromAnotherVector},
    {"Insert empty range", testInsertEmptyRange},
    {"Insert range at beginning", testInsertRangeAtBeginning},
    {"Erase range from middle", testEraseRangeFromMiddle},
    {"Erase full range", testEraseFullRange},
    {"Erase empty range", testEraseEmptyRange},
    { "Non-empty vector for non-empty initializer list", testInitializerList },
    {"Insert iterator value at beginning", testInsertIterValueAtBeginning},
    {"Insert iterator value at end", testInsertIterValueAtEnd},
    {"Insert iterator range from vector", testInsertIterRangeFromVector},
    {"Insert iterator empty range", testInsertIterEmptyRange},
    {"Insert initializer list at beginning", testInsertInitListAtBeginning},
    {"Insert initializer list at end", testInsertInitListAtEnd},
    {"Erase iterator middle", testEraseIterMiddle},
    {"Erase iterator last", testEraseIterLast},
    {"Erase iterator range", testEraseIterRange},
    {"Erase iterator all", testEraseIterAll},
    {"RemoveIf odd numbers", testRemoveIfOdd},
    {"RemoveIf greater than 10", testRemoveIfGreaterThanTen},
  };

  const size_t count = sizeof(tests) / sizeof(test_t);

  std::cout << std::boolalpha;
  size_t passed = 0;
  size_t failed = 0;

  for (size_t i = 0; i < count; ++i) {
    bool res = tests[i].second();
    if (res) {
      ++passed;
    } else {
      std::cout << "FAILED: " << tests[i].first << "\n";
      ++failed;
    }
  }

  std::cout << "Total: " << count << "\n";
  std::cout << "Passed:  " << passed << "\n";
  std::cout << "Failed:  " << failed << "\n";
  std::cout << "RESULT: " << (failed == 0) << "\n";
  return (failed == 0) ? 0 : 1;
}