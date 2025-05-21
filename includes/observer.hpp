#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <functional>

using func = std::function<void()>;
using functionVec = std::vector<func>;

template <typename TEvent> class Observer {
private:
  std::unordered_map<TEvent, functionVec> eventsCallbacks;

public:
  Observer() = default;
  Observer(const Observer &rhs) = delete;
  Observer(Observer &&rhs) = delete;
  auto operator=(const Observer &rhs) -> Observer & = delete;
  ~Observer() = default;

  void subscribe(const TEvent &event, const std::function<void()> &lambda) {
    auto eventIt = eventsCallbacks.find(event);
    if (eventIt != eventsCallbacks.end()) {
      eventIt->second.push_back(lambda);
    } else {
      functionVec vec;
      vec.push_back(lambda);
      eventsCallbacks.insert({event, vec});
    }
  }

  void notify(const TEvent &event) {
    auto eventIt = eventsCallbacks.find(event);
    if (eventIt != eventsCallbacks.end()) {
      for (const auto &callback : eventIt->second) {
        callback();
      }
    }
  }
};

#endif // !OBSERVER_HPP
