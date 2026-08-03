#include "../../include/Events/LeaveEvent.h"
#include "../../include/Simulation/Clinic.h"

LeaveEvent::LeaveEvent(int ts, int pid) : timestamp(ts), patientId(pid) {}

int LeaveEvent::getTimestamp() const { return timestamp; }

int LeaveEvent::getPatientId() const { return patientId; }

void LeaveEvent::Execute(Clinic& clinic) {
    clinic.handleLeave(patientId);
}
