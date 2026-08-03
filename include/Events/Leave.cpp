#include "Leave.h"

Leave::Leave(int ts, int id) : Event(ts), id(id) {}
void Leave::Execute() {}
int Leave::getId() const { return id; }