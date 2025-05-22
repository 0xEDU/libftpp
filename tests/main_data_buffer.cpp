#include "../includes/data_buffer.hpp"
#include "../includes/test_helper.hpp"
#include <cassert>
#include <exception>
#include <iostream>
#include <string>

class TestObject {
public:
  int x;
  std::string y;

  friend DataBuffer &operator<<(DataBuffer &p_buffer,
                                const TestObject &p_object) {
    p_buffer << p_object.x << p_object.y;
    return p_buffer;
  }

  friend DataBuffer &operator>>(DataBuffer &p_buffer, TestObject &p_object) {
    p_buffer >> p_object.x >> p_object.y;
    return p_buffer;
  }
};

int main() {
  TestHelper testHelper;
  DataBuffer myBuffer;

  TestObject obj1;
  obj1.x = 42;
  obj1.y = "Hello";

  TestObject obj2;
  obj2.x = 99;
  obj2.y = "World";

  myBuffer << obj1 << obj2;
  testHelper.expectTrue(myBuffer.data() != nullptr,
                        "Buffer should not be null after serialization");

  TestObject deserializedObj1, deserializedObj2, deserializedObj3;

  testHelper.expectNotThrow(
      [&]() {
        myBuffer >> deserializedObj1 >> deserializedObj2;
        std::cout << "Deserialized obj1: x = " << deserializedObj1.x
                  << ", y = " << deserializedObj1.y << '\n';
        std::cout << "Deserialized obj2: x = " << deserializedObj2.x
                  << ", y = " << deserializedObj2.y << '\n';
      },
      "Deserialization should not throw an exception");

  testHelper.expectThrow(
      [&]() {
        myBuffer >> deserializedObj3;
        std::cout << "Deserialized obj3: x = " << deserializedObj3.x
                  << ", y = " << deserializedObj3.y << '\n';
      },
      "Deserialization should throw an exception");

  return 0;
}
