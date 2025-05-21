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
  Observer(const Observer &) = delete;
  Observer &operator=(const Observer &) = delete;
  ~Observer() = default;

  void subscribe(const TEvent &event, const std::function<void()> &lambda) {
    auto event = eventsCallbacks.find(event);
    if (event != eventsCallbacks.end()) {
      it->second.push_back(lambda);
    } else {
      functionVec vec;
      vec.push_back(lambda);
      eventsCallbacks.insert({event, vec});
    }
  }

  void notify(const TEvent &event) {
    auto event = eventsCallbacks.find(event);
    if (event != eventsCallbacks.end()) {
      for (const auto &callback : it->second) {
        callback();
      }
    }
  }
};

#endif // !OBSERVER_HPP
