#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <functional>

// What's the difference between transition and action?
// Maps might be a good option here
template <typename TState> class StateMachine {
public:
  StateMachine() = default;
  StateMachine(const StateMachine &) = delete;
  StateMachine &operator=(const StateMachine &) = delete;
  ~StateMachine() = default;

  void addState(const TState &state);

  void addTransition(const TState &startState, const TState &finalState,
                     const std::function<void()> &lambda);

	void addAction(const TState& state, const std::function<void()>& lambda);

  void transitionTo(const TState &state);

	void update();
};

#endif // !STATE_MACHINE_HPP
