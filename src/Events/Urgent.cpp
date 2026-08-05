#include "../../include/Events/Urgent.h"

Urgent::Urgent(int ts, int id) : Event(ts), id(id) {}
void Urgent::Execute(Clinic& clinic) {}
int Urgent::getId() const { return id; }