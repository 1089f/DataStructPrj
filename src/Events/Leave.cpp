#include "../../include/Events/Leave.h"

Leave::Leave(int ts, int id) : Event(ts), id(id) {}
void Leave::Execute(Clinic& clinic) {}
int Leave::getId() const { return id; }