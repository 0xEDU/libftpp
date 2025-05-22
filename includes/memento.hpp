#ifndef MEMENTO_HPP
#define MEMENTO_HPP

#include "data_buffer.hpp"

class Memento {
protected:
  Memento();
  Memento(const Memento &rhs);
  Memento &operator=(const Memento &rhs);
  ~Memento();

public:
  class Snapshot {
    friend class Memento;

  private:
    DataBuffer dataBuffer;

  public:
    Snapshot();
    Snapshot(const Snapshot &rhs);
    auto operator=(const Snapshot &rhs) -> Snapshot &;
    ~Snapshot();

    template <typename T> Snapshot &operator<<(const T &object) {
      dataBuffer << object;
      return *this;
    };

    template <typename T> Snapshot &operator>>(T &object) {
      dataBuffer >> object;
      return *this;
    };
  };

  Snapshot save();
  void load(const Snapshot &state);

  virtual void _saveToSnapshot(Snapshot &snapshotToFill) const = 0;
  virtual void _loadFromSnapshot(Snapshot &snapshot) = 0;
};

#endif // !MEMENTO_HPP
