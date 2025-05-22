#include "../includes/memento.hpp"
#include "../includes/test_helper.hpp"
#include <iostream>

class TestClass : public Memento {
  friend class Memento;

public:
  int x;
  std::string y;

private:
  void _saveToSnapshot(Snapshot &snapshotToFill) const override {
    snapshotToFill << x << y;
  }

  void _loadFromSnapshot(Snapshot &snapshot) override { snapshot >> x >> y; }
};

int main() {
  TestHelper testHelper;
  TestClass myObject;
  myObject.x = 42;
  myObject.y = "Hello";

  // Save the current state
  TestClass::Snapshot savedState = myObject.save();

  // Modify the object
  myObject.x = 100;
  myObject.y = "World";

  // Output the modified object
  std::cout << "Current state: x = " << myObject.x << ", y = " << myObject.y
            << '\n';
  testHelper.expectTrue(
      myObject.x == 100 && myObject.y == "World",
      "Object should be modified to x = 100, y = World");

  // Restore the object to its saved state
  myObject.load(savedState);

  // Output the restored object
  std::cout << "Restored state: x = " << myObject.x << ", y = " << myObject.y
            << '\n';
  testHelper.expectTrue(
      myObject.x == 42 && myObject.y == "Hello",
      "Object should be restored to x = 42, y = Hello");

  return 0;
}
