#include "../../include/Events/CheckIn.h"

CheckIn::CheckIn(int ts, PatientType type, int id, int branch, int tests)
    : Event(ts), type(type), id(id), branch(branch), tests(tests) {
}

void CheckIn::Execute(Clinic& clinic) {}

Patient* CheckIn::createPatient() {
    return new Patient(id, timestamp, type, tests, branch);
}