#include "../../include/Events/UrgentEvent.h"
#include "../../include/Simulation/Clinic.h"

UrgentEvent::UrgentEvent(int ts, int pid) : timestamp(ts), patientId(pid) {}

int UrgentEvent::getTimestamp() const { return timestamp; }

int UrgentEvent::getPatientId() const { return patientId; }

void UrgentEvent::Execute(Clinic& clinic) {
    clinic.handleEscalate(patientId);
}
