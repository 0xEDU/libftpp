#ifndef POOL_HPP
#define POOL_HPP

#include <algorithm>
#include <cstddef>
#include <memory>
#include <vector>

template <typename TType> class Pool {
  std::vector<std::shared_ptr<TType>> objectRawPool;

public:
  Pool() = default;
  Pool(const Pool &) = delete;            // Prevent copying
  Pool &operator=(const Pool &) = delete; // Prevent assignment
  ~Pool() = default;

  void resize(const size_t &numberOfObjectStored) {
    objectRawPool.resize(numberOfObjectStored);
    for (size_t i = 0; i < numberOfObjectStored; ++i) {
      objectRawPool[i] = std::make_shared<TType>();
    }
  };

  class Object {
  private:
    std::shared_ptr<TType> object = nullptr;

  public:
    Object() = default;
    ~Object() = default;
    Object(std::shared_ptr<TType> p) : object(std::move(p)) {}

    TType *operator->() { return object.get(); };
  };

  template <typename... TArgs> Pool::Object acquire(TArgs &&...p_args) {
    auto objectIt = std::find_if(objectRawPool.begin(), objectRawPool.end(),
                                 [](const std::shared_ptr<TType> &p_object) {
                                   return p_object.use_count() < 2;
                                 });
    if (objectIt != objectRawPool.end()) {
      *(*objectIt) = TType(std::forward<TArgs>(p_args)...);
      return Object(*objectIt);
    } else {
      *objectIt = std::make_shared<TType>(std::forward<TArgs>(p_args)...);
      objectRawPool.push_back(*objectIt);
      return Object(*objectIt);
    }
  }
};

#endif // !POOL_HPP
