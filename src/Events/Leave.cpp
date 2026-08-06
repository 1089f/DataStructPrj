#include "../../include/Events/Leave.h"
#include "../../include/Simulation/Clinic.h"

Leave::Leave(int ts, int id) : Event(ts), id(id) {}

void Leave::Execute(Clinic& clinic) {
    clinic.handleLeave(id);
}

int Leave::getId() const { return id; }
