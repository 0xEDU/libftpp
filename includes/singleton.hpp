#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <memory>
#include <stdexcept>

template <typename TType> class Singleton {
  static std::unique_ptr<TType> instancePtr;

public:
  // Delete copy constructor and assignment operator
  Singleton() = default;
  Singleton(const Singleton &rhs) = delete;
  Singleton(Singleton &&rhs) = delete;
  auto operator=(Singleton &&rhs) -> Singleton & = delete;
  auto operator=(const Singleton &rhs) -> Singleton & = delete;
  ~Singleton() = default;

  static auto instance() -> TType * {
    if (instancePtr == nullptr) {
      throw std::runtime_error("Instance not yet created");
    }
    return instancePtr.get();
  }

  template <typename... TArgs> static void instantiate(TArgs &&...p_args) {
    if (instancePtr != nullptr) {
      throw std::runtime_error("Instance already created");
    }

    instancePtr = std::make_unique<TType>(p_args...);
  }
};

template <typename TType>
std::unique_ptr<TType> Singleton<TType>::instancePtr = nullptr;

#endif // !SINGLETON_HPP
