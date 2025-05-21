#include "../includes/memento.hpp"

using Snapshot = Memento::Snapshot;

Memento::Memento() = default;
Memento::Memento(const Memento &) = default;
auto Memento::operator=(const Memento &) -> Memento & = default;
Memento::~Memento() = default;

auto Memento::save() -> Snapshot {
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
auto Snapshot::operator=(const Snapshot &rhs) -> Snapshot & {
  if (this != &rhs) {
    dataBuffer = rhs.dataBuffer;
  }
  return *this;
};
Snapshot::~Snapshot() = default;
