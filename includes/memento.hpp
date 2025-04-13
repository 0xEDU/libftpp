#ifndef MEMENTO_HPP
#define MEMENTO_HPP

#include "data_buffer.hpp"

class Memento {
protected:
  Memento();
  Memento(const Memento &);
  Memento &operator=(const Memento &);
  ~Memento();

public:
  class Snapshot {
    friend class Memento;

  private:
    DataBuffer dataBuffer;

  public:
    Snapshot();
    Snapshot(const Snapshot &);
    Snapshot &operator=(const Snapshot &);
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

  virtual void _saveToSnapshot(Snapshot &snapshotToFill) = 0;
  virtual void _loadFromSnapshot(Snapshot &snapshot) = 0;
};

#endif // !MEMENTO_HPP
