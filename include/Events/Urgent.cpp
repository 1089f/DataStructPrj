#include "Urgent.h"

Urgent::Urgent(int ts, int id) : Event(ts), id(id) {}
void Urgent::Execute() {}
int Urgent::getId() const { return id; }