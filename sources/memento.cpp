#include "../includes/memento.hpp"

using Snapshot = Memento::Snapshot;

Memento::Memento() = default;
Memento::Memento(const Memento &) = default;
Memento &Memento::operator=(const Memento &) = default;
Memento::~Memento() = default;

Memento::Snapshot Memento::save() {
  Snapshot snapshot;
  _saveToSnapshot(snapshot);
  return snapshot;
};

void Memento::load(const Snapshot &state) {
  Snapshot snapshot(state);
  _loadFromSnapshot(snapshot);
};

Snapshot::Snapshot() = default;
Snapshot::Snapshot(const Snapshot &rhs) { *this = rhs; };
Snapshot &Snapshot::operator=(const Snapshot &rhs) {
  if (this != &rhs) {
    dataBuffer = rhs.dataBuffer;
  }
  return *this;
};
Snapshot::~Snapshot() = default;
