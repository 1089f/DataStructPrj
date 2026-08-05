#include "../../include/Events/Urgent.h"
#include "../../include/Simulation/Clinic.h"

Urgent::Urgent(int ts, int id) : Event(ts), id(id) {}
void Urgent::Execute(Clinic& clinic) { clinic.handleEscalate(id); }
int Urgent::getId() const { return id; }