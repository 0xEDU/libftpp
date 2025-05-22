#include "../includes/singleton.hpp"
#include "../includes/test_helper.hpp"
#include <iostream>

class MyClass {
  int answer = 0;
public:
  MyClass(int value) {
    std::cout << "MyClass constructor, with value [" << value << "]" << '\n';
    answer = value;
  }

  auto theAnswer() -> int { return answer; }
};

int main() {
  TestHelper testHelper;

  testHelper.expectThrow([](){
    Singleton<MyClass>::instance();
  }, "Singleton should throw an exception if instance is not created");

  Singleton<MyClass>::instantiate(42); // Setting up the instance

  int answer = Singleton<MyClass>::instance()
      ->theAnswer(); // Output: "Hello from MyClass"
  testHelper.expectTrue(answer == 42,
                "Singleton instance should execute functions correctly");

  testHelper.expectThrow([](){
    Singleton<MyClass>::instantiate(100);
  }, "Singleton should throw an exception if instance is already created");

  return 0;
}
