#ifndef MEMENTO_HPP
#define MEMENTO_HPP

#include "data_buffer.hpp"

class Memento {
protected:
  Memento();
  Memento(const Memento &);
  auto operator=(const Memento &) -> Memento &;
  ~Memento();

public:
  class Snapshot {
    friend class Memento;

  private:
    DataBuffer dataBuffer;

  public:
    Snapshot();
    Snapshot(const Snapshot &);
    auto operator=(const Snapshot &) -> Snapshot &;
    ~Snapshot();

    template <typename T> auto operator<<(const T &object) -> Snapshot & {
      dataBuffer << object;
      return *this;
    };

    template <typename T> auto operator>>(T &object) -> Snapshot & {
      dataBuffer >> object;
      return *this;
    };
  };

  auto save() -> Snapshot;
  void load(const Snapshot &state);

  virtual void _saveToSnapshot(Snapshot &snapshotToFill) const = 0;
  virtual void _loadFromSnapshot(Snapshot &snapshot) = 0;
};

#endif // !MEMENTO_HPP
