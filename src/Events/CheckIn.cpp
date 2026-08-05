#include "../../include/Events/CheckIn.h"
#include "../../include/Simulation/Clinic.h"

CheckIn::CheckIn(int ts, PatientType type, int id, int branch, int tests)
    : Event(ts), type(type), id(id), branch(branch), tests(tests) {
}

void CheckIn::Execute(Clinic& clinic) { clinic.handleCheckIn(createPatient()); }

Patient* CheckIn::createPatient() {
    return new Patient(id, timestamp, type, tests, branch);
}