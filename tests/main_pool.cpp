#include "../includes/pool.hpp"
#include "../includes/test_helper.hpp"
#include <iostream>

class TestObject {
  int counter = 0;

public:
  TestObject() { std::cout << "TestObject default constructor" << '\n'; }
  TestObject(int value) {
    std::cout << "TestObject constructor with value [" << value << "]" << '\n';
  }
  ~TestObject() { std::cout << "TestObject destructor" << '\n'; }

  void increase() { counter++; }

  int getCounter() { return counter; }
};

int main() {
  TestHelper testHelper;

  // Create a Pool for TestObject
  Pool<TestObject> myPool;

  // Resize the pool to pre-allocate 5 objects
  // Should output the 5 "TestObject constructor"
  myPool.resize(5);

  // Acquire an object from the pool
  Pool<TestObject>::Object obj1 = myPool.acquire(15);
  obj1->increase();
  obj1->increase();
  obj1->increase();
  testHelper.expectTrue(obj1->getCounter() == 3, "Counter should be 3");

  {
    // Acquire another object in a different scope
    Pool<TestObject>::Object obj2 = myPool.acquire();
    obj2->increase();
    obj2->increase();
    testHelper.expectTrue(obj2->getCounter() == 2, "Counter should be 2");

    // obj2 is released back to the pool when it goes out of scope
  }

  // Acquire another object; this should give us the object that obj2 pointed to
  Pool<TestObject>::Object obj3 = myPool.acquire();
  obj3->increase();
  testHelper.expectTrue(obj3->getCounter() == 1, "Counter should be 1");

  // obj1 and obj3 are released back to the pool when the program ends
  return 0;
}
