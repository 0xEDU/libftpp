#include "../includes/state_machine.hpp"
#include "../includes/test_helper.hpp"
#include <iostream>

enum class State { Idle, Running, Paused, Stopped };

int main() {
  TestHelper testHelper;
  StateMachine<State> sm;
  int idle, running, paused;

  sm.addState(State::Idle);
  sm.addState(State::Running);
  sm.addState(State::Paused);
  sm.addState(State::Stopped);

  sm.addAction(State::Idle, [&] {
    idle = 1;
    std::cout << "System is idle." << '\n';
  });
  sm.addAction(State::Running, [&] {
    running = 1;
    std::cout << "System is running." << '\n';
  });
  sm.addAction(State::Paused, [&] {
    paused = 1;
    std::cout << "System is paused." << '\n';
  });
  // No addAction for State::Stopped, it will use the default empty lambda

  sm.addTransition(State::Idle, State::Running, [&] {
    idle = 0;
    running = 1;
    std::cout << "Transitioning from Idle to Running." << '\n';
  });
  sm.addTransition(State::Running, State::Paused, [&] {
    running = 0;
    paused = 1;
    std::cout << "Transitioning from Running to Paused." << '\n';
  });
  sm.addTransition(State::Paused, State::Running, [&] {
    paused = 0;
    running = 1;
    std::cout << "Transitioning from Paused to Running." << '\n';
  });
  // No addTransition for State::Stopped

  sm.update();
  testHelper.expectTrue(idle == 1, "Initial state should be Idle (1)");

  sm.transitionTo(
      State::Running); // Should print: "Transitioning from Idle to Running."
  testHelper.expectTrue(
      running == 1 && idle == 0,
      "State should be Running (1) after transition from Idle to Running.");

  sm.update(); // Should print: "System is running."
  testHelper.expectTrue(
      running == 1 && idle == 0,
      "State should be Running (1) after update from Idle to Running.");

  sm.transitionTo(
      State::Paused); // Should print: "Transitioning from Running to Paused."
  testHelper.expectTrue(
      running == 0 && paused == 1,
      "State should be Paused (1) after transition from Running to Paused.");

  sm.update(); // Should print: "System is paused."
  testHelper.expectTrue(
      paused == 1 && running == 0,
      "State should be Paused (1) after update from Running to Paused.");

  testHelper.expectTrue(
      paused == 1 && running == 0 && idle == 0,
      "Last state should be Paused (1) after update from Running to Paused.");

  // Transitioning to and from the new State::Stopped
  testHelper.expectThrow(
      [&] {
        sm.transitionTo(State::Stopped); // Should not print anything, default
                                         // empty lambda is executed
      },
      "Transition to Stopped should not throw an exception");

  return 0;
}
