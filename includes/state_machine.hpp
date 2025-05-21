#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <functional>
#include <map>
#include <memory>
#include <set>
#include <stdexcept>

template <typename TState> class StateMachine {
private:
  std::unique_ptr<TState> currentState = nullptr;
  std::set<TState> states;
  std::map<TState, std::function<void()>> actions;
  std::map<TState, std::map<TState, std::function<void()>>> transitions;

  void executeAction(const TState &state) {
    auto actionIt = actions.find(state);
    if (actionIt != actions.end()) {
      actionIt->second();
    }
  }

  void executeTransition(const TState &state) {
    auto transitionIt = transitions.find(state);
    if (transitionIt != transitions.end()) {
      for (const auto &pair : transitionIt->second) {
        pair.second();
      }
    }
  }

public:
  StateMachine() = default;
  StateMachine(const StateMachine &) = delete;
  StateMachine &operator=(const StateMachine &) = delete;
  ~StateMachine() = default;

  void addState(const TState &state) {
    if (currentState == nullptr) {
      currentState = std::make_unique<TState>(state);
    }
    states.insert(state);
  }

  void addTransition(const TState &startState, const TState &finalState,
                     const std::function<void()> &lambda) {
    if (states.find(startState) == states.end() ||
        states.find(finalState) == states.end()) {
      throw std::invalid_argument("State not found");
    }
    transitions[startState][finalState] = lambda;
  }

  void addAction(const TState &state, const std::function<void()> &lambda) {
    if (states.find(state) == states.end()) {
      throw std::invalid_argument("State not found");
    }
    actions[state] = lambda;
  }

  void transitionTo(const TState &state) {
    // Check if transition is valid
    auto transitionIt = transitions.find(*currentState);
    if (transitionIt == transitions.end() ||
        transitionIt->second.find(state) == transitionIt->second.end()) {
      throw std::invalid_argument("Invalid transition");
    }
    if (*currentState == state)
      return;

    executeTransition(*currentState);
    currentState = std::make_unique<TState>(state);
  }

  void update() {
    if (states.find(*currentState) == states.end()) {
      throw std::invalid_argument("State not found");
    }
    executeAction(*currentState);
  }
};

#endif // !STATE_MACHINE_HPP
