#include "../includes/observer.hpp"
#include "../includes/test_helper.hpp"
#include <iostream>

enum class EventType { EVENT_ONE, EVENT_TWO, EVENT_THREE };

int main() {
  TestHelper testHelper;
  Observer<EventType> observer;
  int eventCount = 0;

  // Subscribe to EVENT_ONE
  observer.subscribe(EventType::EVENT_ONE, [&]() {
    std::cout << BLUE << "Event One triggered" << RESET << '\n';
    eventCount++;
  });

  // Subscribe first lambda to EVENT_TWO
  observer.subscribe(EventType::EVENT_TWO, [&]() {
    std::cout << PURPLE << "Event Two triggered (First subscriber)" << RESET << '\n';
    eventCount++;
  });

  // Subscribe second lambda to EVENT_TWO
  observer.subscribe(EventType::EVENT_TWO, [&]() {
    std::cout << PURPLE << "Event Two triggered (Second subscriber)" << RESET << '\n';
    eventCount++;
  });

  // Triggering EVENT_ONE
  std::cout << WHITE << "Notify " << BLUE << "EVENT_ONE" << RESET << '\n';
  observer.notify(EventType::EVENT_ONE); // Output: "Event One triggered"
  testHelper.expectTrue(eventCount == 1,
                        "EVENT_ONE should trigger the first subscriber");

  // Triggering EVENT_TWO
  // Output:
  // "Event Two triggered (First subscriber)"
  // "Event Two triggered (Second subscriber)"
  // The order may differ
  std::cout << WHITE << "Notify " << PURPLE << "EVENT_TWO" << RESET << '\n';
  observer.notify(EventType::EVENT_TWO);
  testHelper.expectTrue(eventCount == 3,
                        "EVENT_TWO should trigger both subscribers (2 times)");

  // Triggering EVENT_THREE (No subscriber)
  // Output: None, as there are no subscribers
  std::cout << WHITE << "Notify " << YELLOW << "EVENT_THREE" << RESET << '\n';
  observer.notify(EventType::EVENT_THREE);
  testHelper.expectTrue(eventCount == 3,
                        "EVENT_THREE should not trigger any subscribers");

  return 0;
}
