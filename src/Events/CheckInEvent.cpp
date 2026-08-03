#include "../../include/Events/CheckInEvent.h"
#include "../../include/Simulation/Clinic.h"
#include "../../include/Entities/Patient.h"

CheckInEvent::CheckInEvent(int ts, Patient* p) : timestamp(ts), patient(p) {}

int CheckInEvent::getTimestamp() const { return timestamp; }

Patient* CheckInEvent::getPatient() const { return patient; }

void CheckInEvent::Execute(Clinic& clinic) {
    clinic.handleCheckIn(patient);
}
